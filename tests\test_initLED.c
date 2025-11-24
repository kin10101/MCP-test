/* test_initLED.c - SELF-CONTAINED */

#include "unity.h"
#include "mock_config.h"

/* ========================================================================
   INLINE MACROS - From JSON DefinedConstants
   ======================================================================== */
#define LED &MODULE_P00,5
#define WAIT_TIME 500U
/* Define numeric macros for modes used by initLED to avoid unknown enums */
#define IfxPort_OutputMode_pushPull ((uint8)0U)
#define IfxPort_OutputIdx_general  ((uint8)0U)

/* ========================================================================
   INLINE RESOURCES
   ======================================================================== */
static Ifx_P MODULE_P00 = {0};

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Weak functions and state
   ======================================================================== */
static uint32 g_call_sequence = 0U;

typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8  last_pin;
    uint8  last_mode;
    uint8  last_idx;
    uint32 seq;
} mock_IfxPort_setPinModeOutput_state_t;
static mock_IfxPort_setPinModeOutput_state_t mock_IfxPort_setPinModeOutput = {0};

typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8  last_pin;
    uint32 seq;
} mock_IfxPort_setPinHigh_state_t;
static mock_IfxPort_setPinHigh_state_t mock_IfxPort_setPinHigh = {0};

__attribute__((weak)) void IfxPort_setPinModeOutput(Ifx_P *port, uint8 pin, uint8 mode, uint8 idx)
{
    mock_IfxPort_setPinModeOutput.call_count++;
    mock_IfxPort_setPinModeOutput.last_port = port;
    mock_IfxPort_setPinModeOutput.last_pin  = pin;
    mock_IfxPort_setPinModeOutput.last_mode = mode;
    mock_IfxPort_setPinModeOutput.last_idx  = idx;
    g_call_sequence++;
    mock_IfxPort_setPinModeOutput.seq = g_call_sequence;
}

__attribute__((weak)) void IfxPort_setPinHigh(Ifx_P *port, uint8 pin)
{
    mock_IfxPort_setPinHigh.call_count++;
    mock_IfxPort_setPinHigh.last_port = port;
    mock_IfxPort_setPinHigh.last_pin  = pin;
    g_call_sequence++;
    mock_IfxPort_setPinHigh.seq = g_call_sequence;
}

/* Helpers */
static uint32 mock_get_IfxPort_setPinModeOutput_call_count(void) { return mock_IfxPort_setPinModeOutput.call_count; }
static uint32 mock_get_IfxPort_setPinHigh_call_count(void) { return mock_IfxPort_setPinHigh.call_count; }
static Ifx_P* mock_get_IfxPort_setPinModeOutput_last_port(void) { return mock_IfxPort_setPinModeOutput.last_port; }
static uint8  mock_get_IfxPort_setPinModeOutput_last_pin(void)  { return mock_IfxPort_setPinModeOutput.last_pin; }
static uint8  mock_get_IfxPort_setPinModeOutput_last_mode(void) { return mock_IfxPort_setPinModeOutput.last_mode; }
static uint8  mock_get_IfxPort_setPinModeOutput_last_idx(void)  { return mock_IfxPort_setPinModeOutput.last_idx; }
static Ifx_P* mock_get_IfxPort_setPinHigh_last_port(void) { return mock_IfxPort_setPinHigh.last_port; }
static uint8  mock_get_IfxPort_setPinHigh_last_pin(void)  { return mock_IfxPort_setPinHigh.last_pin; }
static uint32 mock_get_IfxPort_setPinModeOutput_seq(void) { return mock_IfxPort_setPinModeOutput.seq; }
static uint32 mock_get_IfxPort_setPinHigh_seq(void) { return mock_IfxPort_setPinHigh.seq; }

static void mock_reset_all(void)
{
    g_call_sequence = 0U;
    mock_IfxPort_setPinModeOutput.call_count = 0U;
    mock_IfxPort_setPinModeOutput.last_port = (Ifx_P*)0;
    mock_IfxPort_setPinModeOutput.last_pin  = 0U;
    mock_IfxPort_setPinModeOutput.last_mode = 0U;
    mock_IfxPort_setPinModeOutput.last_idx  = 0U;
    mock_IfxPort_setPinModeOutput.seq       = 0U;

    mock_IfxPort_setPinHigh.call_count = 0U;
    mock_IfxPort_setPinHigh.last_port = (Ifx_P*)0;
    mock_IfxPort_setPinHigh.last_pin  = 0U;
    mock_IfxPort_setPinHigh.seq       = 0U;
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
void initLED(void)
{
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinHigh(LED);
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) { mock_reset_all(); }
void tearDown(void) {}

void test_initLED_configures_pushpull_and_sets_high(void)
{
    initLED();
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxPort_setPinModeOutput_call_count());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxPort_setPinHigh_call_count());
    TEST_ASSERT_EQUAL_PTR(&MODULE_P00, mock_get_IfxPort_setPinModeOutput_last_port());
    TEST_ASSERT_EQUAL_UINT8(5U, mock_get_IfxPort_setPinModeOutput_last_pin());
    TEST_ASSERT_EQUAL_UINT8(IfxPort_OutputMode_pushPull, mock_get_IfxPort_setPinModeOutput_last_mode());
    TEST_ASSERT_EQUAL_UINT8(IfxPort_OutputIdx_general,  mock_get_IfxPort_setPinModeOutput_last_idx());
    TEST_ASSERT_EQUAL_PTR(&MODULE_P00, mock_get_IfxPort_setPinHigh_last_port());
    TEST_ASSERT_EQUAL_UINT8(5U, mock_get_IfxPort_setPinHigh_last_pin());
}

void test_initLED_called_twice_updates_counts_and_params(void)
{
    initLED();
    initLED();
    TEST_ASSERT_EQUAL_UINT32(2U, mock_get_IfxPort_setPinModeOutput_call_count());
    TEST_ASSERT_EQUAL_UINT32(2U, mock_get_IfxPort_setPinHigh_call_count());
    TEST_ASSERT_EQUAL_PTR(&MODULE_P00, mock_get_IfxPort_setPinModeOutput_last_port());
    TEST_ASSERT_EQUAL_UINT8(5U, mock_get_IfxPort_setPinModeOutput_last_pin());
    TEST_ASSERT_EQUAL_PTR(&MODULE_P00, mock_get_IfxPort_setPinHigh_last_port());
    TEST_ASSERT_EQUAL_UINT8(5U, mock_get_IfxPort_setPinHigh_last_pin());
}

void test_initLED_call_order_mode_before_high(void)
{
    initLED();
    TEST_ASSERT_TRUE(mock_get_IfxPort_setPinModeOutput_seq() < mock_get_IfxPort_setPinHigh_seq());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_initLED_configures_pushpull_and_sets_high);
    RUN_TEST(test_initLED_called_twice_updates_counts_and_params);
    RUN_TEST(test_initLED_call_order_mode_before_high);
    return UNITY_END();
}
