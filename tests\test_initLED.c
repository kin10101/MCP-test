/* test_initLED.c - SELF-CONTAINED */

#include "unity.h"
#include "mock_config.h"
#include <string.h>

/* ========================================================================
   INLINE MACROS - Extracted from JSON DefinedConstants
   ======================================================================== */
#define LED &MODULE_P00, 5
#define WAIT_TIME 500
#define IfxPort_OutputMode_pushPull ((uint8)0)
#define IfxPort_OutputIdx_general   ((uint8)0)

/* ========================================================================
   INLINE RESOURCES
   ======================================================================== */
static Ifx_P MODULE_P00 = {0};

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Only for dependencies of initLED
   ======================================================================== */

typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
    uint8 last_mode;
    uint8 last_idx;
} mock_IfxPort_setPinModeOutput_state_t;
static mock_IfxPort_setPinModeOutput_state_t mock_IfxPort_setPinModeOutput = {0};

__attribute__((weak)) void IfxPort_setPinModeOutput(Ifx_P *port, uint8 pin, uint8 mode, uint8 idx) {
    mock_IfxPort_setPinModeOutput.call_count++;
    mock_IfxPort_setPinModeOutput.last_port = port;
    mock_IfxPort_setPinModeOutput.last_pin = pin;
    mock_IfxPort_setPinModeOutput.last_mode = mode;
    mock_IfxPort_setPinModeOutput.last_idx = idx;
}

uint32 mock_get_IfxPort_setPinModeOutput_call_count(void) {
    return mock_IfxPort_setPinModeOutput.call_count;
}


typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_setPinHigh_state_t;
static mock_IfxPort_setPinHigh_state_t mock_IfxPort_setPinHigh = {0};

__attribute__((weak)) void IfxPort_setPinHigh(Ifx_P *port, uint8 pin) {
    mock_IfxPort_setPinHigh.call_count++;
    mock_IfxPort_setPinHigh.last_port = port;
    mock_IfxPort_setPinHigh.last_pin = pin;
}

uint32 mock_get_IfxPort_setPinHigh_call_count(void) {
    return mock_IfxPort_setPinHigh.call_count;
}

void mock_reset_all(void) {
    memset(&mock_IfxPort_setPinModeOutput, 0, sizeof(mock_IfxPort_setPinModeOutput));
    memset(&mock_IfxPort_setPinHigh, 0, sizeof(mock_IfxPort_setPinHigh));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST - From JSON Functions[]
   ======================================================================== */
void initLED(void) {
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinHigh(LED);
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) {
    mock_reset_all();
}

void tearDown(void) {}

void test_initLED_configures_push_pull_output(void) {
    initLED();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxPort_setPinModeOutput_call_count());
    TEST_ASSERT_TRUE(mock_IfxPort_setPinModeOutput.last_port == &MODULE_P00);
    TEST_ASSERT_EQUAL_UINT8(5, mock_IfxPort_setPinModeOutput.last_pin);
    TEST_ASSERT_EQUAL_UINT8(IfxPort_OutputMode_pushPull, mock_IfxPort_setPinModeOutput.last_mode);
    TEST_ASSERT_EQUAL_UINT8(IfxPort_OutputIdx_general, mock_IfxPort_setPinModeOutput.last_idx);
}

void test_initLED_sets_pin_high_off_state(void) {
    initLED();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxPort_setPinHigh_call_count());
    TEST_ASSERT_TRUE(mock_IfxPort_setPinHigh.last_port == &MODULE_P00);
    TEST_ASSERT_EQUAL_UINT8(5, mock_IfxPort_setPinHigh.last_pin);
}

void test_initLED_multiple_calls_increment_counts(void) {
    initLED();
    initLED();
    TEST_ASSERT_EQUAL_UINT32(2, mock_get_IfxPort_setPinModeOutput_call_count());
    TEST_ASSERT_EQUAL_UINT32(2, mock_get_IfxPort_setPinHigh_call_count());
    TEST_ASSERT_TRUE(mock_IfxPort_setPinModeOutput.last_port == &MODULE_P00);
    TEST_ASSERT_EQUAL_UINT8(5, mock_IfxPort_setPinModeOutput.last_pin);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_initLED_configures_push_pull_output);
    RUN_TEST(test_initLED_sets_pin_high_off_state);
    RUN_TEST(test_initLED_multiple_calls_increment_counts);
    return UNITY_END();
}
