/* test_initLED.c - SELF-CONTAINED */

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

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Only for this function's dependencies
   ======================================================================== */
#include <string.h>

typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
    IfxPort_OutputMode last_mode;
    IfxPort_OutputIdx last_idx;
} mock_IfxPort_setPinModeOutput_t;
static mock_IfxPort_setPinModeOutput_t mock_IfxPort_setPinModeOutput_state;

__attribute__((weak)) void IfxPort_setPinModeOutput(Ifx_P *port, uint8 pin, IfxPort_OutputMode mode, IfxPort_OutputIdx idx)
{
    mock_IfxPort_setPinModeOutput_state.call_count++;
    mock_IfxPort_setPinModeOutput_state.last_port = port;
    mock_IfxPort_setPinModeOutput_state.last_pin = pin;
    mock_IfxPort_setPinModeOutput_state.last_mode = mode;
    mock_IfxPort_setPinModeOutput_state.last_idx = idx;
}

uint32 mock_get_IfxPort_setPinModeOutput_call_count(void)
{
    return mock_IfxPort_setPinModeOutput_state.call_count;
}

Ifx_P *mock_get_IfxPort_setPinModeOutput_last_port(void)
{
    return mock_IfxPort_setPinModeOutput_state.last_port;
}

uint8 mock_get_IfxPort_setPinModeOutput_last_pin(void)
{
    return mock_IfxPort_setPinModeOutput_state.last_pin;
}

IfxPort_OutputMode mock_get_IfxPort_setPinModeOutput_last_mode(void)
{
    return mock_IfxPort_setPinModeOutput_state.last_mode;
}

IfxPort_OutputIdx mock_get_IfxPort_setPinModeOutput_last_idx(void)
{
    return mock_IfxPort_setPinModeOutput_state.last_idx;
}


typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_setPinHigh_t;
static mock_IfxPort_setPinHigh_t mock_IfxPort_setPinHigh_state;

__attribute__((weak)) void IfxPort_setPinHigh(Ifx_P *port, uint8 pin)
{
    mock_IfxPort_setPinHigh_state.call_count++;
    mock_IfxPort_setPinHigh_state.last_port = port;
    mock_IfxPort_setPinHigh_state.last_pin = pin;
}

uint32 mock_get_IfxPort_setPinHigh_call_count(void)
{
    return mock_IfxPort_setPinHigh_state.call_count;
}

Ifx_P *mock_get_IfxPort_setPinHigh_last_port(void)
{
    return mock_IfxPort_setPinHigh_state.last_port;
}

uint8 mock_get_IfxPort_setPinHigh_last_pin(void)
{
    return mock_IfxPort_setPinHigh_state.last_pin;
}

void mock_reset_all(void)
{
    memset(&mock_IfxPort_setPinModeOutput_state, 0, sizeof(mock_IfxPort_setPinModeOutput_state));
    memset(&mock_IfxPort_setPinHigh_state, 0, sizeof(mock_IfxPort_setPinHigh_state));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST - From JSON Functions[]
   ======================================================================== */
void initLED(void)
{
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinHigh(LED);
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void)
{
    mock_reset_all();
}

void tearDown(void) {}

void test_initLED_configures_push_pull_and_sets_high(void)
{
    initLED();

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxPort_setPinModeOutput_call_count());
    TEST_ASSERT_EQUAL_PTR((void*)&MODULE_P00, (void*)mock_get_IfxPort_setPinModeOutput_last_port());
    TEST_ASSERT_EQUAL_UINT8(5, mock_get_IfxPort_setPinModeOutput_last_pin());
    TEST_ASSERT_EQUAL_UINT32((uint32)IfxPort_OutputMode_pushPull, (uint32)mock_get_IfxPort_setPinModeOutput_last_mode());
    TEST_ASSERT_EQUAL_UINT32((uint32)IfxPort_OutputIdx_general, (uint32)mock_get_IfxPort_setPinModeOutput_last_idx());

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxPort_setPinHigh_call_count());
    TEST_ASSERT_EQUAL_PTR((void*)&MODULE_P00, (void*)mock_get_IfxPort_setPinHigh_last_port());
    TEST_ASSERT_EQUAL_UINT8(5, mock_get_IfxPort_setPinHigh_last_pin());
}

void test_initLED_called_twice_accumulates_calls(void)
{
    initLED();
    initLED();

    TEST_ASSERT_EQUAL_UINT32(2, mock_get_IfxPort_setPinModeOutput_call_count());
    TEST_ASSERT_EQUAL_UINT32(2, mock_get_IfxPort_setPinHigh_call_count());
}

void test_initLED_pin_and_mode_values_are_correct_each_call(void)
{
    initLED();

    TEST_ASSERT_EQUAL_PTR((void*)&MODULE_P00, (void*)mock_get_IfxPort_setPinModeOutput_last_port());
    TEST_ASSERT_EQUAL_UINT8(5, mock_get_IfxPort_setPinModeOutput_last_pin());
    TEST_ASSERT_EQUAL_UINT32((uint32)IfxPort_OutputMode_pushPull, (uint32)mock_get_IfxPort_setPinModeOutput_last_mode());
    TEST_ASSERT_EQUAL_UINT32((uint32)IfxPort_OutputIdx_general, (uint32)mock_get_IfxPort_setPinModeOutput_last_idx());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_initLED_configures_push_pull_and_sets_high);
    RUN_TEST(test_initLED_called_twice_accumulates_calls);
    RUN_TEST(test_initLED_pin_and_mode_values_are_correct_each_call);
    return UNITY_END();
}
