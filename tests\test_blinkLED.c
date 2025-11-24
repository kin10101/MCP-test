/* test_blinkLED.c - SELF-CONTAINED */

#include "unity.h"
#include "mock_config.h"
#include <string.h>

/* ========================================================================
   INLINE MACROS - From JSON DefinedConstants
   ======================================================================== */
#define LED &MODULE_P00,5
#define WAIT_TIME 500

/* ========================================================================
   INLINE RESOURCE DEFINITIONS
   ======================================================================== */
static Ifx_P MODULE_P00 = (Ifx_P){0};
static Ifx_STM g_timer = (Ifx_STM){0};
Ifx_STM *BSP_DEFAULT_TIMER = &g_timer;

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Weak functions to avoid linker conflicts
   ======================================================================== */

typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_togglePin_state_t;
static mock_IfxPort_togglePin_state_t mock_IfxPort_togglePin = {0};

__attribute__((weak)) void IfxPort_togglePin(Ifx_P *port, uint8 pin)
{
    mock_IfxPort_togglePin.call_count++;
    mock_IfxPort_togglePin.last_port = port;
    mock_IfxPort_togglePin.last_pin = pin;
}

uint32 mock_get_IfxPort_togglePin_call_count(void) { return mock_IfxPort_togglePin.call_count; }
Ifx_P *mock_get_IfxPort_togglePin_last_port(void) { return mock_IfxPort_togglePin.last_port; }
uint8 mock_get_IfxPort_togglePin_last_pin(void) { return mock_IfxPort_togglePin.last_pin; }


typedef struct {
    uint32 call_count;
    Ifx_STM *last_stm;
    uint32 last_ms;
    uint32 return_value;
} mock_IfxStm_getTicksFromMilliseconds_state_t;
static mock_IfxStm_getTicksFromMilliseconds_state_t mock_IfxStm_getTicksFromMilliseconds = {0};

__attribute__((weak)) uint32 IfxStm_getTicksFromMilliseconds(Ifx_STM *stm, uint32 ms)
{
    mock_IfxStm_getTicksFromMilliseconds.call_count++;
    mock_IfxStm_getTicksFromMilliseconds.last_stm = stm;
    mock_IfxStm_getTicksFromMilliseconds.last_ms = ms;
    return mock_IfxStm_getTicksFromMilliseconds.return_value;
}

uint32 mock_get_IfxStm_getTicksFromMilliseconds_call_count(void) { return mock_IfxStm_getTicksFromMilliseconds.call_count; }
Ifx_STM *mock_get_IfxStm_getTicksFromMilliseconds_last_stm(void) { return mock_IfxStm_getTicksFromMilliseconds.last_stm; }
uint32 mock_get_IfxStm_getTicksFromMilliseconds_last_ms(void) { return mock_IfxStm_getTicksFromMilliseconds.last_ms; }
void mock_set_IfxStm_getTicksFromMilliseconds_return(uint32 value) { mock_IfxStm_getTicksFromMilliseconds.return_value = value; }


typedef struct {
    uint32 call_count;
    uint32 last_ticks;
} mock_waitTime_state_t;
static mock_waitTime_state_t mock_waitTime = {0};

__attribute__((weak)) void waitTime(uint32 ticks)
{
    mock_waitTime.call_count++;
    mock_waitTime.last_ticks = ticks;
}

uint32 mock_get_waitTime_call_count(void) { return mock_waitTime.call_count; }
uint32 mock_get_waitTime_last_ticks(void) { return mock_waitTime.last_ticks; }


void mock_reset_all(void)
{
    memset(&mock_IfxPort_togglePin, 0, sizeof(mock_IfxPort_togglePin));
    memset(&mock_IfxStm_getTicksFromMilliseconds, 0, sizeof(mock_IfxStm_getTicksFromMilliseconds));
    memset(&mock_waitTime, 0, sizeof(mock_waitTime));
    memset(&g_timer, 0, sizeof(g_timer));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST - From JSON Functions[]
   ======================================================================== */
void blinkLED(void)
{
    /* Toggle LED and wait for WAIT_TIME milliseconds */
    IfxPort_togglePin(LED);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) { mock_reset_all(); }
void tearDown(void) {}

void test_blinkLED_toggles_pin_and_waits_converted_ticks(void)
{
    mock_set_IfxStm_getTicksFromMilliseconds_return(1000U);
    blinkLED();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxPort_togglePin_call_count());
    TEST_ASSERT_EQUAL_PTR(&MODULE_P00, mock_get_IfxPort_togglePin_last_port());
    TEST_ASSERT_EQUAL_UINT8(5, mock_get_IfxPort_togglePin_last_pin());

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxStm_getTicksFromMilliseconds_call_count());
    TEST_ASSERT_EQUAL_PTR(BSP_DEFAULT_TIMER, mock_get_IfxStm_getTicksFromMilliseconds_last_stm());
    TEST_ASSERT_EQUAL_UINT32(WAIT_TIME, mock_get_IfxStm_getTicksFromMilliseconds_last_ms());

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(1000U, mock_get_waitTime_last_ticks());
}

void test_blinkLED_handles_zero_ticks_boundary(void)
{
    mock_set_IfxStm_getTicksFromMilliseconds_return(0U);
    blinkLED();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(0U, mock_get_waitTime_last_ticks());
}

void test_blinkLED_handles_nonstandard_ticks_boundary(void)
{
    mock_set_IfxStm_getTicksFromMilliseconds_return(550U);
    blinkLED();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(550U, mock_get_waitTime_last_ticks());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_blinkLED_toggles_pin_and_waits_converted_ticks);
    RUN_TEST(test_blinkLED_handles_zero_ticks_boundary);
    RUN_TEST(test_blinkLED_handles_nonstandard_ticks_boundary);
    return UNITY_END();
}
