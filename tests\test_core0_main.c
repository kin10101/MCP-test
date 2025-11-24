/* test_core0_main.c - SELF-CONTAINED */

#include "unity.h"
#include "mock_config.h"

/* ========================================================================
   INLINE MACROS - Extracted from JSON and test-control macro
   ======================================================================== */
#define LED &MODULE_P00, 5
#define WAIT_TIME 500

/* Test control: limit the infinite loop iterations in unit tests */
static uint32 g_unit_test_loop_limit = 3U;
#define UNIT_TEST_LIMIT_LOOP g_unit_test_loop_limit

/* ========================================================================
   INLINE RESOURCES
   ======================================================================== */
static Ifx_P MODULE_P00 = (Ifx_P){0};
IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0U;

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Only for this function's dependencies
   ======================================================================== */
#include <string.h>

/* CPU interrupt enable */
typedef struct { uint32 call_count; } mock_IfxCpu_enableInterrupts_t;
static mock_IfxCpu_enableInterrupts_t mock_IfxCpu_enableInterrupts_state;
__attribute__((weak)) void IfxCpu_enableInterrupts(void)
{
    mock_IfxCpu_enableInterrupts_state.call_count++;
}
uint32 mock_get_IfxCpu_enableInterrupts_call_count(void)
{
    return mock_IfxCpu_enableInterrupts_state.call_count;
}

/* Watchdog passwords and disables */
typedef struct { uint32 call_count; uint16 return_value; } mock_IfxScuWdt_getCpuWatchdogPassword_t;
static mock_IfxScuWdt_getCpuWatchdogPassword_t mock_IfxScuWdt_getCpuWatchdogPassword_state;
__attribute__((weak)) uint16 IfxScuWdt_getCpuWatchdogPassword(void)
{
    mock_IfxScuWdt_getCpuWatchdogPassword_state.call_count++;
    return mock_IfxScuWdt_getCpuWatchdogPassword_state.return_value;
}
uint32 mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count(void)
{
    return mock_IfxScuWdt_getCpuWatchdogPassword_state.call_count;
}
void mock_set_IfxScuWdt_getCpuWatchdogPassword_return(uint16 value)
{
    mock_IfxScuWdt_getCpuWatchdogPassword_state.return_value = value;
}

typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableCpuWatchdog_t;
static mock_IfxScuWdt_disableCpuWatchdog_t mock_IfxScuWdt_disableCpuWatchdog_state;
__attribute__((weak)) void IfxScuWdt_disableCpuWatchdog(uint16 password)
{
    mock_IfxScuWdt_disableCpuWatchdog_state.call_count++;
    mock_IfxScuWdt_disableCpuWatchdog_state.last_password = password;
}
uint32 mock_get_IfxScuWdt_disableCpuWatchdog_call_count(void)
{
    return mock_IfxScuWdt_disableCpuWatchdog_state.call_count;
}
uint16 mock_get_IfxScuWdt_disableCpuWatchdog_last_password(void)
{
    return mock_IfxScuWdt_disableCpuWatchdog_state.last_password;
}

typedef struct { uint32 call_count; uint16 return_value; } mock_IfxScuWdt_getSafetyWatchdogPassword_t;
static mock_IfxScuWdt_getSafetyWatchdogPassword_t mock_IfxScuWdt_getSafetyWatchdogPassword_state;
__attribute__((weak)) uint16 IfxScuWdt_getSafetyWatchdogPassword(void)
{
    mock_IfxScuWdt_getSafetyWatchdogPassword_state.call_count++;
    return mock_IfxScuWdt_getSafetyWatchdogPassword_state.return_value;
}
uint32 mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count(void)
{
    return mock_IfxScuWdt_getSafetyWatchdogPassword_state.call_count;
}
void mock_set_IfxScuWdt_getSafetyWatchdogPassword_return(uint16 value)
{
    mock_IfxScuWdt_getSafetyWatchdogPassword_state.return_value = value;
}

typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableSafetyWatchdog_t;
static mock_IfxScuWdt_disableSafetyWatchdog_t mock_IfxScuWdt_disableSafetyWatchdog_state;
__attribute__((weak)) void IfxScuWdt_disableSafetyWatchdog(uint16 password)
{
    mock_IfxScuWdt_disableSafetyWatchdog_state.call_count++;
    mock_IfxScuWdt_disableSafetyWatchdog_state.last_password = password;
}
uint32 mock_get_IfxScuWdt_disableSafetyWatchdog_call_count(void)
{
    return mock_IfxScuWdt_disableSafetyWatchdog_state.call_count;
}
uint16 mock_get_IfxScuWdt_disableSafetyWatchdog_last_password(void)
{
    return mock_IfxScuWdt_disableSafetyWatchdog_state.last_password;
}

/* CPU sync events */
typedef struct { uint32 call_count; IfxCpu_syncEvent *last_event; } mock_IfxCpu_emitEvent_t;
static mock_IfxCpu_emitEvent_t mock_IfxCpu_emitEvent_state;
__attribute__((weak)) void IfxCpu_emitEvent(IfxCpu_syncEvent *event)
{
    mock_IfxCpu_emitEvent_state.call_count++;
    mock_IfxCpu_emitEvent_state.last_event = event;
}
uint32 mock_get_IfxCpu_emitEvent_call_count(void)
{
    return mock_IfxCpu_emitEvent_state.call_count;
}
IfxCpu_syncEvent *mock_get_IfxCpu_emitEvent_last_event(void)
{
    return mock_IfxCpu_emitEvent_state.last_event;
}

typedef struct { uint32 call_count; IfxCpu_syncEvent *last_event; uint32 last_count; } mock_IfxCpu_waitEvent_t;
static mock_IfxCpu_waitEvent_t mock_IfxCpu_waitEvent_state;
__attribute__((weak)) void IfxCpu_waitEvent(IfxCpu_syncEvent *event, uint32 count)
{
    mock_IfxCpu_waitEvent_state.call_count++;
    mock_IfxCpu_waitEvent_state.last_event = event;
    mock_IfxCpu_waitEvent_state.last_count = count;
}
uint32 mock_get_IfxCpu_waitEvent_call_count(void)
{
    return mock_IfxCpu_waitEvent_state.call_count;
}
IfxCpu_syncEvent *mock_get_IfxCpu_waitEvent_last_event(void)
{
    return mock_IfxCpu_waitEvent_state.last_event;
}
uint32 mock_get_IfxCpu_waitEvent_last_count(void)
{
    return mock_IfxCpu_waitEvent_state.last_count;
}

/* Project functions used by core0_main */
typedef struct { uint32 call_count; } mock_initLED_t;
static mock_initLED_t mock_initLED_state;
__attribute__((weak)) void initLED(void)
{
    mock_initLED_state.call_count++;
}
uint32 mock_get_initLED_call_count(void)
{
    return mock_initLED_state.call_count;
}

typedef struct { uint32 call_count; } mock_blinkLED_t;
static mock_blinkLED_t mock_blinkLED_state;
__attribute__((weak)) void blinkLED(void)
{
    mock_blinkLED_state.call_count++;
}
uint32 mock_get_blinkLED_call_count(void)
{
    return mock_blinkLED_state.call_count;
}

void mock_reset_all(void)
{
    memset(&mock_IfxCpu_enableInterrupts_state, 0, sizeof(mock_IfxCpu_enableInterrupts_state));
    memset(&mock_IfxScuWdt_getCpuWatchdogPassword_state, 0, sizeof(mock_IfxScuWdt_getCpuWatchdogPassword_state));
    memset(&mock_IfxScuWdt_disableCpuWatchdog_state, 0, sizeof(mock_IfxScuWdt_disableCpuWatchdog_state));
    memset(&mock_IfxScuWdt_getSafetyWatchdogPassword_state, 0, sizeof(mock_IfxScuWdt_getSafetyWatchdogPassword_state));
    memset(&mock_IfxScuWdt_disableSafetyWatchdog_state, 0, sizeof(mock_IfxScuWdt_disableSafetyWatchdog_state));
    memset(&mock_IfxCpu_emitEvent_state, 0, sizeof(mock_IfxCpu_emitEvent_state));
    memset(&mock_IfxCpu_waitEvent_state, 0, sizeof(mock_IfxCpu_waitEvent_state));
    memset(&mock_initLED_state, 0, sizeof(mock_initLED_state));
    memset(&mock_blinkLED_state, 0, sizeof(mock_blinkLED_state));
    g_unit_test_loop_limit = 3U;
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST - From JSON Functions[]
   ======================================================================== */
void core0_main(void)
{
    IfxCpu_enableInterrupts();

    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1U);

    initLED();

#if defined(UNIT_TEST_LIMIT_LOOP)
    for (uint32 i = 0U; i < UNIT_TEST_LIMIT_LOOP; ++i)
    {
        blinkLED();
    }
#else
    while (1)
    {
        blinkLED();
    }
#endif
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void)
{
    mock_reset_all();
}

void tearDown(void) {}

void test_core0_main_happy_path_calls_expected_sequences(void)
{
    mock_set_IfxScuWdt_getCpuWatchdogPassword_return((uint16)0x1234U);
    mock_set_IfxScuWdt_getSafetyWatchdogPassword_return((uint16)0xABCDU);
    g_unit_test_loop_limit = 3U;

    core0_main();

    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxCpu_enableInterrupts_call_count());

    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxScuWdt_disableCpuWatchdog_call_count());
    TEST_ASSERT_EQUAL_UINT16((uint16)0x1234U, mock_get_IfxScuWdt_disableCpuWatchdog_last_password());

    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxScuWdt_disableSafetyWatchdog_call_count());
    TEST_ASSERT_EQUAL_UINT16((uint16)0xABCDU, mock_get_IfxScuWdt_disableSafetyWatchdog_last_password());

    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxCpu_emitEvent_call_count());
    TEST_ASSERT_EQUAL_PTR((void*)&g_cpuSyncEvent, (void*)mock_get_IfxCpu_emitEvent_last_event());

    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxCpu_waitEvent_call_count());
    TEST_ASSERT_EQUAL_PTR((void*)&g_cpuSyncEvent, (void*)mock_get_IfxCpu_waitEvent_last_event());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxCpu_waitEvent_last_count());

    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_initLED_call_count());
    TEST_ASSERT_EQUAL_UINT32(3U, mock_get_blinkLED_call_count());
}

void test_core0_main_boundary_zero_loop_limit_runs_no_blinks(void)
{
    mock_set_IfxScuWdt_getCpuWatchdogPassword_return((uint16)0x0001U);
    mock_set_IfxScuWdt_getSafetyWatchdogPassword_return((uint16)0x0002U);
    g_unit_test_loop_limit = 0U;

    core0_main();

    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_initLED_call_count());
    TEST_ASSERT_EQUAL_UINT32(0U, mock_get_blinkLED_call_count());
}

void test_core0_main_error_password_zero_still_disables_watchdogs(void)
{
    mock_set_IfxScuWdt_getCpuWatchdogPassword_return((uint16)0x0000U);
    mock_set_IfxScuWdt_getSafetyWatchdogPassword_return((uint16)0x0000U);
    g_unit_test_loop_limit = 1U;

    core0_main();

    TEST_ASSERT_EQUAL_UINT16((uint16)0x0000U, mock_get_IfxScuWdt_disableCpuWatchdog_last_password());
    TEST_ASSERT_EQUAL_UINT16((uint16)0x0000U, mock_get_IfxScuWdt_disableSafetyWatchdog_last_password());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_core0_main_happy_path_calls_expected_sequences);
    RUN_TEST(test_core0_main_boundary_zero_loop_limit_runs_no_blinks);
    RUN_TEST(test_core0_main_error_password_zero_still_disables_watchdogs);
    return UNITY_END();
}
