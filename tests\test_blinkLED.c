/* test_blinkLED.c - SELF-CONTAINED */

#include "unity.h"
#include "mock_config.h"

/* ========================================================================
   INLINE MACROS - Extracted from JSON DefinedConstants
   ======================================================================== */
#define LED &MODULE_P00, 5
#define WAIT_TIME 500

/* ========================================================================
   INLINE RESOURCES
   ======================================================================== */
static Ifx_P MODULE_P00 = (Ifx_P){0};
static Ifx_STM g_stm_instance = (Ifx_STM){0};
static Ifx_STM *BSP_DEFAULT_TIMER = &g_stm_instance;

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Only for this function's dependencies
   ======================================================================== */
#include <string.h>

typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_togglePin_t;
static mock_IfxPort_togglePin_t mock_IfxPort_togglePin_state;

__attribute__((weak)) void IfxPort_togglePin(Ifx_P *port, uint8 pin)
{
    mock_IfxPort_togglePin_state.call_count++;
    mock_IfxPort_togglePin_state.last_port = port;
    mock_IfxPort_togglePin_state.last_pin = pin;
}

uint32 mock_get_IfxPort_togglePin_call_count(void)
{
    return mock_IfxPort_togglePin_state.call_count;
}

Ifx_P *mock_get_IfxPort_togglePin_last_port(void)
{
    return mock_IfxPort_togglePin_state.last_port;
}

uint8 mock_get_IfxPort_togglePin_last_pin(void)
{
    return mock_IfxPort_togglePin_state.last_pin;
}


typedef struct {
    uint32 call_count;
    Ifx_STM *last_stm;
    uint32 last_ms;
    uint32 return_value;
} mock_IfxStm_getTicksFromMilliseconds_t;
static mock_IfxStm_getTicksFromMilliseconds_t mock_IfxStm_getTicksFromMilliseconds_state;

__attribute__((weak)) uint32 IfxStm_getTicksFromMilliseconds(Ifx_STM *stm, uint32 ms)
{
    mock_IfxStm_getTicksFromMilliseconds_state.call_count++;
    mock_IfxStm_getTicksFromMilliseconds_state.last_stm = stm;
    mock_IfxStm_getTicksFromMilliseconds_state.last_ms = ms;
    return mock_IfxStm_getTicksFromMilliseconds_state.return_value;
}

uint32 mock_get_IfxStm_getTicksFromMilliseconds_call_count(void)
{
    return mock_IfxStm_getTicksFromMilliseconds_state.call_count;
}

Ifx_STM *mock_get_IfxStm_getTicksFromMilliseconds_last_stm(void)
{
    return mock_IfxStm_getTicksFromMilliseconds_state.last_stm;
}

uint32 mock_get_IfxStm_getTicksFromMilliseconds_last_ms(void)
{
    return mock_IfxStm_getTicksFromMilliseconds_state.last_ms;
}

void mock_set_IfxStm_getTicksFromMilliseconds_return(uint32 value)
{
    mock_IfxStm_getTicksFromMilliseconds_state.return_value = value;
}


typedef struct {
    uint32 call_count;
    uint32 last_ticks;
} mock_waitTime_t;
static mock_waitTime_t mock_waitTime_state;

__attribute__((weak)) void waitTime(uint32 ticks)
{
    mock_waitTime_state.call_count++;
    mock_waitTime_state.last_ticks = ticks;
}

uint32 mock_get_waitTime_call_count(void)
{
    return mock_waitTime_state.call_count;
}

uint32 mock_get_waitTime_last_ticks(void)
{
    return mock_waitTime_state.last_ticks;
}

void mock_reset_all(void)
{
    memset(&mock_IfxPort_togglePin_state, 0, sizeof(mock_IfxPort_togglePin_state));
    memset(&mock_IfxStm_getTicksFromMilliseconds_state, 0, sizeof(mock_IfxStm_getTicksFromMilliseconds_state));
    memset(&mock_waitTime_state, 0, sizeof(mock_waitTime_state));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST - From JSON Functions[]
   ======================================================================== */
void blinkLED(void)
{
    IfxPort_togglePin(LED);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void)
{
    mock_reset_all();
}

void tearDown(void) {}

void test_blinkLED_toggles_and_waits_500ms(void)
{
    mock_set_IfxStm_getTicksFromMilliseconds_return(1000U);

    blinkLED();

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxPort_togglePin_call_count());
    TEST_ASSERT_EQUAL_PTR((void*)&MODULE_P00, (void*)mock_get_IfxPort_togglePin_last_port());
    TEST_ASSERT_EQUAL_UINT8(5, mock_get_IfxPort_togglePin_last_pin());

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxStm_getTicksFromMilliseconds_call_count());
    TEST_ASSERT_EQUAL_PTR((void*)BSP_DEFAULT_TIMER, (void*)mock_get_IfxStm_getTicksFromMilliseconds_last_stm());
    TEST_ASSERT_EQUAL_UINT32(WAIT_TIME, mock_get_IfxStm_getTicksFromMilliseconds_last_ms());

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(1000U, mock_get_waitTime_last_ticks());
}

void test_blinkLED_multiple_calls_with_variable_ticks(void)
{
    mock_set_IfxStm_getTicksFromMilliseconds_return(950U);
    blinkLED();

    mock_set_IfxStm_getTicksFromMilliseconds_return(1050U);
    blinkLED();

    TEST_ASSERT_EQUAL_UINT32(2, mock_get_IfxPort_togglePin_call_count());
    TEST_ASSERT_EQUAL_UINT32(2, mock_get_IfxStm_getTicksFromMilliseconds_call_count());
    TEST_ASSERT_EQUAL_UINT32(WAIT_TIME, mock_get_IfxStm_getTicksFromMilliseconds_last_ms());
    TEST_ASSERT_EQUAL_UINT32(2, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(1050U, mock_get_waitTime_last_ticks());
}

void test_blinkLED_zero_ticks_still_calls_wait(void)
{
    mock_set_IfxStm_getTicksFromMilliseconds_return(0U);
    blinkLED();

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(0U, mock_get_waitTime_last_ticks());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_blinkLED_toggles_and_waits_500ms);
    RUN_TEST(test_blinkLED_multiple_calls_with_variable_ticks);
    RUN_TEST(test_blinkLED_zero_ticks_still_calls_wait);
    return UNITY_END();
}
