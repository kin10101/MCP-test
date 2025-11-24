/* test_blinkLED.c - SELF-CONTAINED */

#include "unity.h"
#include "mock_config.h"
#include <string.h>

/* ========================================================================
   INLINE MACROS - Extracted from JSON DefinedConstants
   ======================================================================== */
#define LED &MODULE_P00, 5
#define WAIT_TIME 500

/* ========================================================================
   INLINE RESOURCES
   ======================================================================== */
static Ifx_P MODULE_P00 = {0};
static Ifx_STM g_timer = {0};
static Ifx_STM *BSP_DEFAULT_TIMER = &g_timer;

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Only for dependencies of blinkLED
   ======================================================================== */

typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_togglePin_state_t;
static mock_IfxPort_togglePin_state_t mock_IfxPort_togglePin = {0};

__attribute__((weak)) void IfxPort_togglePin(Ifx_P *port, uint8 pin) {
    mock_IfxPort_togglePin.call_count++;
    mock_IfxPort_togglePin.last_port = port;
    mock_IfxPort_togglePin.last_pin = pin;
}

uint32 mock_get_IfxPort_togglePin_call_count(void) {
    return mock_IfxPort_togglePin.call_count;
}


typedef struct {
    uint32 call_count;
    Ifx_STM *last_timer;
    uint32 last_milliseconds;
    uint32 return_value;
} mock_IfxStm_getTicksFromMilliseconds_state_t;
static mock_IfxStm_getTicksFromMilliseconds_state_t mock_IfxStm_getTicksFromMilliseconds = {0};

__attribute__((weak)) uint32 IfxStm_getTicksFromMilliseconds(Ifx_STM *timer, uint32 milliseconds) {
    mock_IfxStm_getTicksFromMilliseconds.call_count++;
    mock_IfxStm_getTicksFromMilliseconds.last_timer = timer;
    mock_IfxStm_getTicksFromMilliseconds.last_milliseconds = milliseconds;
    return mock_IfxStm_getTicksFromMilliseconds.return_value;
}

uint32 mock_get_IfxStm_getTicksFromMilliseconds_call_count(void) {
    return mock_IfxStm_getTicksFromMilliseconds.call_count;
}

void mock_set_IfxStm_getTicksFromMilliseconds_return(uint32 value) {
    mock_IfxStm_getTicksFromMilliseconds.return_value = value;
}


typedef struct {
    uint32 call_count;
    uint32 last_ticks;
} mock_waitTime_state_t;
static mock_waitTime_state_t mock_waitTime = {0};

__attribute__((weak)) void waitTime(uint32 ticks) {
    mock_waitTime.call_count++;
    mock_waitTime.last_ticks = ticks;
}

uint32 mock_get_waitTime_call_count(void) {
    return mock_waitTime.call_count;
}

void mock_reset_all(void) {
    memset(&mock_IfxPort_togglePin, 0, sizeof(mock_IfxPort_togglePin));
    memset(&mock_IfxStm_getTicksFromMilliseconds, 0, sizeof(mock_IfxStm_getTicksFromMilliseconds));
    memset(&mock_waitTime, 0, sizeof(mock_waitTime));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST - From JSON Functions[]
   ======================================================================== */
void blinkLED(void) {
    IfxPort_togglePin(LED);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) {
    mock_reset_all();
}

void tearDown(void) {}

void test_blinkLED_toggles_pin_and_waits_500ms(void) {
    mock_set_IfxStm_getTicksFromMilliseconds_return(1000);
    blinkLED();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxPort_togglePin_call_count());
    TEST_ASSERT_TRUE(mock_IfxPort_togglePin.last_port == &MODULE_P00);
    TEST_ASSERT_EQUAL_UINT8(5, mock_IfxPort_togglePin.last_pin);

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxStm_getTicksFromMilliseconds_call_count());
    TEST_ASSERT_TRUE(mock_IfxStm_getTicksFromMilliseconds.last_timer == BSP_DEFAULT_TIMER);
    TEST_ASSERT_EQUAL_UINT32(WAIT_TIME, mock_IfxStm_getTicksFromMilliseconds.last_milliseconds);

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(1000, mock_waitTime.last_ticks);
}

void test_blinkLED_waits_zero_ticks_when_converter_returns_zero(void) {
    mock_set_IfxStm_getTicksFromMilliseconds_return(0);
    blinkLED();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(0, mock_waitTime.last_ticks);
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxStm_getTicksFromMilliseconds_call_count());
}

void test_blinkLED_uses_converted_ticks_value(void) {
    uint32 ticks = 123456789u;
    mock_set_IfxStm_getTicksFromMilliseconds_return(ticks);
    blinkLED();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_waitTime_call_count());
    TEST_ASSERT_EQUAL_UINT32(ticks, mock_waitTime.last_ticks);
    TEST_ASSERT_EQUAL_UINT32(WAIT_TIME, mock_IfxStm_getTicksFromMilliseconds.last_milliseconds);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_blinkLED_toggles_pin_and_waits_500ms);
    RUN_TEST(test_blinkLED_waits_zero_ticks_when_converter_returns_zero);
    RUN_TEST(test_blinkLED_uses_converted_ticks_value);
    return UNITY_END();
}
