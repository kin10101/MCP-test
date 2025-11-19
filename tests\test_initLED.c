/* test_initLED.c - SELF-CONTAINED */

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

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Weak functions to avoid linker conflicts
   ======================================================================== */

typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
    IfxPort_OutputMode last_mode;
    IfxPort_OutputIdx last_idx;
} mock_IfxPort_setPinModeOutput_state_t;
static mock_IfxPort_setPinModeOutput_state_t mock_IfxPort_setPinModeOutput = {0};

__attribute__((weak)) void IfxPort_setPinModeOutput(Ifx_P *port, uint8 pin, IfxPort_OutputMode mode, IfxPort_OutputIdx idx)
{
    mock_IfxPort_setPinModeOutput.call_count++;
    mock_IfxPort_setPinModeOutput.last_port = port;
    mock_IfxPort_setPinModeOutput.last_pin = pin;
    mock_IfxPort_setPinModeOutput.last_mode = mode;
    mock_IfxPort_setPinModeOutput.last_idx = idx;
}

uint32 mock_get_IfxPort_setPinModeOutput_call_count(void) { return mock_IfxPort_setPinModeOutput.call_count; }
Ifx_P *mock_get_IfxPort_setPinModeOutput_last_port(void) { return mock_IfxPort_setPinModeOutput.last_port; }
uint8 mock_get_IfxPort_setPinModeOutput_last_pin(void) { return mock_IfxPort_setPinModeOutput.last_pin; }
uint32 mock_get_IfxPort_setPinModeOutput_last_mode(void) { return (uint32)mock_IfxPort_setPinModeOutput.last_mode; }
uint32 mock_get_IfxPort_setPinModeOutput_last_idx(void) { return (uint32)mock_IfxPort_setPinModeOutput.last_idx; }


typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_setPinHigh_state_t;
static mock_IfxPort_setPinHigh_state_t mock_IfxPort_setPinHigh = {0};

__attribute__((weak)) void IfxPort_setPinHigh(Ifx_P *port, uint8 pin)
{
    mock_IfxPort_setPinHigh.call_count++;
    mock_IfxPort_setPinHigh.last_port = port;
    mock_IfxPort_setPinHigh.last_pin = pin;
}

uint32 mock_get_IfxPort_setPinHigh_call_count(void) { return mock_IfxPort_setPinHigh.call_count; }
Ifx_P *mock_get_IfxPort_setPinHigh_last_port(void) { return mock_IfxPort_setPinHigh.last_port; }
uint8 mock_get_IfxPort_setPinHigh_last_pin(void) { return mock_IfxPort_setPinHigh.last_pin; }


void mock_reset_all(void)
{
    memset(&mock_IfxPort_setPinModeOutput, 0, sizeof(mock_IfxPort_setPinModeOutput));
    memset(&mock_IfxPort_setPinHigh, 0, sizeof(mock_IfxPort_setPinHigh));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST - From JSON Functions[]
   ======================================================================== */
void initLED(void)
{
    /* Configure LED pin as push-pull output and set high (active-low LED off) */
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinHigh(LED);
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) { mock_reset_all(); }
void tearDown(void) {}

void test_initLED_calls_gpio_config_and_high(void)
{
    initLED();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxPort_setPinModeOutput_call_count());
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxPort_setPinHigh_call_count());
}

void test_initLED_sets_pushpull_and_general_idx_on_LED_portpin(void)
{
    initLED();
    TEST_ASSERT_EQUAL_PTR(&MODULE_P00, mock_get_IfxPort_setPinModeOutput_last_port());
    TEST_ASSERT_EQUAL_UINT8(5, mock_get_IfxPort_setPinModeOutput_last_pin());
    TEST_ASSERT_EQUAL_UINT32((uint32)IfxPort_OutputMode_pushPull, mock_get_IfxPort_setPinModeOutput_last_mode());
    TEST_ASSERT_EQUAL_UINT32((uint32)IfxPort_OutputIdx_general, mock_get_IfxPort_setPinModeOutput_last_idx());
}

void test_initLED_sets_LED_pin_high(void)
{
    initLED();
    TEST_ASSERT_EQUAL_PTR(&MODULE_P00, mock_get_IfxPort_setPinHigh_last_port());
    TEST_ASSERT_EQUAL_UINT8(5, mock_get_IfxPort_setPinHigh_last_pin());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_initLED_calls_gpio_config_and_high);
    RUN_TEST(test_initLED_sets_pushpull_and_general_idx_on_LED_portpin);
    RUN_TEST(test_initLED_sets_LED_pin_high);
    return UNITY_END();
}
