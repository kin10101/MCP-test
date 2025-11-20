/* test_blinkLED.c - SELF-CONTAINED */

#include "unity.h"
#include "mock_config.h"

/* ========================================================================
   INLINE MACROS - From JSON DefinedConstants
   ======================================================================== */
#define LED &MODULE_P00,5
#define WAIT_TIME 500U

/* ========================================================================
   INLINE RESOURCES
   ======================================================================== */
static Ifx_P MODULE_P00 = {0};
static Ifx_STM g_default_timer = {0};
static Ifx_STM *BSP_DEFAULT_TIMER = &g_default_timer;

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Weak functions and state
   ======================================================================== */

typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8  last_pin;
} mock_IfxPort_togglePin_state_t;
static mock_IfxPort_togglePin_state_t mock_IfxPort_togglePin = {0};

typedef struct {
    uint32 call_count;
    Ifx_STM *last_timer;
    uint32 last_ms;
    uint32 return_value;
} mock_IfxStm_getTicksFromMilliseconds_state_t;
static mock_IfxStm_getTicksFromMilliseconds_state_t mock_IfxStm_getTicksFromMilliseconds = {0};

typedef struct {
    uint32 call_count;
    uint32 last_ticks;
} mock_waitTime_state_t;
static mock_waitTime_state_t mock_waitTime = {0};

__attribute__((weak)) void IfxPort_togglePin(Ifx_P *port, uint8 pin)
{
    mock_IfxPort_togglePin.call_count++;
    mock_IfxPort_togglePin.last_port = port;
    mock_IfxPort_togglePin.last_pin  = pin;
}

__attribute__((weak)) uint32 IfxStm_getTicksFromMilliseconds(Ifx_STM *timer, uint32 ms)
{
    mock_IfxStm_getTicksFromMilliseconds.call_count++;
    mock_IfxStm_getTicksFromMilliseconds.last_timer = timer;
    mock_IfxStm_getTicksFromMilliseconds.last_ms    = ms;
    return mock_IfxStm_getTicksFromMilliseconds.return_value;
}

__attribute__((weak)) void waitTime(uint32 ticks)
{
    mock_waitTime.call_count++;
    mock_waitTime.last_ticks = ticks;
}

/* Helpers */
static uint32 mock_get_IfxPort_togglePin_call_count(void) { return mock_IfxPort_togglePin.call_count; }
static Ifx_P* mock_get_IfxPort_togglePin_last_port(void) { return mock_IfxPort_togglePin.last_port; }
static uint8  mock_get_IfxPort_togglePin_last_pin(void)  { return mock_IfxPort_togglePin.last_pin; }
static uint32 mock_get_IfxStm_getTicksFromMilliseconds_call_count(void) { return mock_IfxStm_getTicksFromMilliseconds.call_count; }
static Ifx_STM* mock_get_IfxStm_getTicksFromMilliseconds_last_timer(void) { return mock_IfxStm_getTicksFromMilliseconds.last_timer; }
static uint32 mock_get_IfxStm_getTicksFromMilliseconds_last_ms(void) { return mock_IfxStm_getTicksFromMilliseconds.last_ms; }
static void   mock_set_IfxStm_getTicksFromMilliseconds_return(uint32 value) { mock_IfxStm_getTicksFromMilliseconds.return_value = value; }
static uint32 mock_get_waitTime_call_count(void) { return mock_waitTime.call_count; }
static uint32 mock_get_waitTime_last_ticks(void) { return mock_waitTime.last_ticks; }

static void mock_reset_all(void)
{
    mock_IfxPort_togglePin.call_count = 0U;
    mock_IfxPort_togglePin.last_port  = (Ifx_P*)0;
    mock_IfxPort_togglePin.last_pin   = 0U;

    mock_IfxStm_getTicksFromMilliseconds.call_count   = 0U;
    mock_IfxStm_getTicksFromMilliseconds.last_timer   = (Ifx_STM*)0;
    mock_IfxStm_getTicksFromMilliseconds.last_ms      = 0U;
    mock_IfxStm_getTicksFromMilliseconds.return_value = 0U;

    mock_waitTime.call_count = 0U;
    mock_waitTime.last_ticks = 0U;
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
void blinkLED(void)
{
    IfxPort_togglePin(LED);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) { mock_reset_all(); }
void tearDown(void) {}

void test_blinkLED_toggles_and_waits_500ms(void)
{
    mock_set_IfxStm_getTicksFromMilliseconds_return(1000U);
    blinkLED();
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxPort_togglePin_call_count());
    TEST_ASSERT_EQUAL_PTR(&MODULE_P00, mock_get_IfxPort_togglePin_last_port());
    TEST_ASSERT_EQUAL_UINT8(5U, mock_get_IfxPort_togglePin_last_pin());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxStm_getTicksFromMilliseconds_call_count());
    TEST_ASSERT_EQUAL_PTR(BSP_DEFAULT_TIMER, mock_get_IfxStm_getTicksFromMilliseconds_last_timer());
    TEST_ASSERT_EQUAL_UINT32(WAIT_TIME, mock_get_IfxStm_getTicksFromMilliseconds_last_ms());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(1000U, mock_get_waitTime_last_ticks());
}

void test_blinkLED_boundary_450ms_ticks(void)
{
    mock_set_IfxStm_getTicksFromMilliseconds_return(450U);
    blinkLED();
    TEST_ASSERT_EQUAL_UINT32(WAIT_TIME, mock_get_IfxStm_getTicksFromMilliseconds_last_ms());
    TEST_ASSERT_EQUAL_UINT32(450U, mock_get_waitTime_last_ticks());
}

void test_blinkLED_exception_zero_ticks(void)
{
    mock_set_IfxStm_getTicksFromMilliseconds_return(0U);
    blinkLED();
    TEST_ASSERT_EQUAL_UINT32(0U, mock_get_waitTime_last_ticks());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_blinkLED_toggles_and_waits_500ms);
    RUN_TEST(test_blinkLED_boundary_450ms_ticks);
    RUN_TEST(test_blinkLED_exception_zero_ticks);
    return UNITY_END();
}
