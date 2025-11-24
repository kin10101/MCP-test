/* test_core0_main.c - SELF-CONTAINED */

#include "unity.h"
#include "mock_config.h"

/* ========================================================================
   INLINE MACROS AND GLOBALS - From JSON
   ======================================================================== */
#define CORE0_MAIN_LOOP_ITERATIONS ((uint8)3U) /* Limit infinite loop for unit testing */
IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0U;

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Weak functions and state
   ======================================================================== */

typedef struct { uint32 call_count; } mock_IfxCpu_enableInterrupts_state_t;
static mock_IfxCpu_enableInterrupts_state_t mock_IfxCpu_enableInterrupts = {0};

typedef struct { uint32 call_count; uint16 return_value; } mock_IfxScuWdt_getCpuWatchdogPassword_state_t;
static mock_IfxScuWdt_getCpuWatchdogPassword_state_t mock_IfxScuWdt_getCpuWatchdogPassword = {0};

typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableCpuWatchdog_state_t;
static mock_IfxScuWdt_disableCpuWatchdog_state_t mock_IfxScuWdt_disableCpuWatchdog = {0};

typedef struct { uint32 call_count; uint16 return_value; } mock_IfxScuWdt_getSafetyWatchdogPassword_state_t;
static mock_IfxScuWdt_getSafetyWatchdogPassword_state_t mock_IfxScuWdt_getSafetyWatchdogPassword = {0};

typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableSafetyWatchdog_state_t;
static mock_IfxScuWdt_disableSafetyWatchdog_state_t mock_IfxScuWdt_disableSafetyWatchdog = {0};

typedef struct { uint32 call_count; IfxCpu_syncEvent *last_event; } mock_IfxCpu_emitEvent_state_t;
static mock_IfxCpu_emitEvent_state_t mock_IfxCpu_emitEvent = {0};

typedef struct { uint32 call_count; IfxCpu_syncEvent *last_event; uint32 last_count; } mock_IfxCpu_waitEvent_state_t;
static mock_IfxCpu_waitEvent_state_t mock_IfxCpu_waitEvent = {0};

/* Project function dependencies */
typedef struct { uint32 call_count; } mock_initLED_state_t;
static mock_initLED_state_t mock_initLED = {0};

typedef struct { uint32 call_count; } mock_blinkLED_state_t;
static mock_blinkLED_state_t mock_blinkLED = {0};

__attribute__((weak)) void IfxCpu_enableInterrupts(void)
{
    mock_IfxCpu_enableInterrupts.call_count++;
}

__attribute__((weak)) uint16 IfxScuWdt_getCpuWatchdogPassword(void)
{
    mock_IfxScuWdt_getCpuWatchdogPassword.call_count++;
    return mock_IfxScuWdt_getCpuWatchdogPassword.return_value;
}

__attribute__((weak)) void IfxScuWdt_disableCpuWatchdog(uint16 password)
{
    mock_IfxScuWdt_disableCpuWatchdog.call_count++;
    mock_IfxScuWdt_disableCpuWatchdog.last_password = password;
}

__attribute__((weak)) uint16 IfxScuWdt_getSafetyWatchdogPassword(void)
{
    mock_IfxScuWdt_getSafetyWatchdogPassword.call_count++;
    return mock_IfxScuWdt_getSafetyWatchdogPassword.return_value;
}

__attribute__((weak)) void IfxScuWdt_disableSafetyWatchdog(uint16 password)
{
    mock_IfxScuWdt_disableSafetyWatchdog.call_count++;
    mock_IfxScuWdt_disableSafetyWatchdog.last_password = password;
}

__attribute__((weak)) void IfxCpu_emitEvent(IfxCpu_syncEvent *event)
{
    mock_IfxCpu_emitEvent.call_count++;
    mock_IfxCpu_emitEvent.last_event = event;
}

__attribute__((weak)) void IfxCpu_waitEvent(IfxCpu_syncEvent *event, uint32 count)
{
    mock_IfxCpu_waitEvent.call_count++;
    mock_IfxCpu_waitEvent.last_event = event;
    mock_IfxCpu_waitEvent.last_count = count;
}

__attribute__((weak)) void initLED(void)
{
    mock_initLED.call_count++;
}

__attribute__((weak)) void blinkLED(void)
{
    mock_blinkLED.call_count++;
}

/* Helpers */
static uint32 mock_get_IfxCpu_enableInterrupts_call_count(void) { return mock_IfxCpu_enableInterrupts.call_count; }
static uint32 mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count(void) { return mock_IfxScuWdt_getCpuWatchdogPassword.call_count; }
static uint32 mock_get_IfxScuWdt_disableCpuWatchdog_call_count(void) { return mock_IfxScuWdt_disableCpuWatchdog.call_count; }
static uint16 mock_get_IfxScuWdt_disableCpuWatchdog_last_password(void) { return mock_IfxScuWdt_disableCpuWatchdog.last_password; }
static uint32 mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count(void) { return mock_IfxScuWdt_getSafetyWatchdogPassword.call_count; }
static uint32 mock_get_IfxScuWdt_disableSafetyWatchdog_call_count(void) { return mock_IfxScuWdt_disableSafetyWatchdog.call_count; }
static uint16 mock_get_IfxScuWdt_disableSafetyWatchdog_last_password(void) { return mock_IfxScuWdt_disableSafetyWatchdog.last_password; }
static uint32 mock_get_IfxCpu_emitEvent_call_count(void) { return mock_IfxCpu_emitEvent.call_count; }
static IfxCpu_syncEvent* mock_get_IfxCpu_emitEvent_last_event(void) { return mock_IfxCpu_emitEvent.last_event; }
static uint32 mock_get_IfxCpu_waitEvent_call_count(void) { return mock_IfxCpu_waitEvent.call_count; }
static IfxCpu_syncEvent* mock_get_IfxCpu_waitEvent_last_event(void) { return mock_IfxCpu_waitEvent.last_event; }
static uint32 mock_get_IfxCpu_waitEvent_last_count(void) { return mock_IfxCpu_waitEvent.last_count; }
static uint32 mock_get_initLED_call_count(void) { return mock_initLED.call_count; }
static uint32 mock_get_blinkLED_call_count(void) { return mock_blinkLED.call_count; }
static void   mock_set_IfxScuWdt_getCpuWatchdogPassword_return(uint16 value) { mock_IfxScuWdt_getCpuWatchdogPassword.return_value = value; }
static void   mock_set_IfxScuWdt_getSafetyWatchdogPassword_return(uint16 value) { mock_IfxScuWdt_getSafetyWatchdogPassword.return_value = value; }

static void mock_reset_all(void)
{
    mock_IfxCpu_enableInterrupts.call_count = 0U;

    mock_IfxScuWdt_getCpuWatchdogPassword.call_count = 0U;
    mock_IfxScuWdt_getCpuWatchdogPassword.return_value = 0U;
    mock_IfxScuWdt_disableCpuWatchdog.call_count = 0U;
    mock_IfxScuWdt_disableCpuWatchdog.last_password = 0U;

    mock_IfxScuWdt_getSafetyWatchdogPassword.call_count = 0U;
    mock_IfxScuWdt_getSafetyWatchdogPassword.return_value = 0U;
    mock_IfxScuWdt_disableSafetyWatchdog.call_count = 0U;
    mock_IfxScuWdt_disableSafetyWatchdog.last_password = 0U;

    mock_IfxCpu_emitEvent.call_count = 0U;
    mock_IfxCpu_emitEvent.last_event = (IfxCpu_syncEvent*)0;
    mock_IfxCpu_waitEvent.call_count = 0U;
    mock_IfxCpu_waitEvent.last_event = (IfxCpu_syncEvent*)0;
    mock_IfxCpu_waitEvent.last_count = 0U;

    mock_initLED.call_count = 0U;
    mock_blinkLED.call_count = 0U;
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
void core0_main(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1U);
    initLED();
    for (uint8 i = 0U; i < CORE0_MAIN_LOOP_ITERATIONS; ++i)
    {
        blinkLED();
    }
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) { mock_reset_all(); }
void tearDown(void) {}

void test_core0_main_invokes_startup_sequence_and_blink_loop(void)
{
    mock_set_IfxScuWdt_getCpuWatchdogPassword_return((uint16)0xAAAAU);
    mock_set_IfxScuWdt_getSafetyWatchdogPassword_return((uint16)0x5555U);
    core0_main();
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxCpu_enableInterrupts_call_count());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxScuWdt_disableCpuWatchdog_call_count());
    TEST_ASSERT_EQUAL_UINT16((uint16)0xAAAAU, mock_get_IfxScuWdt_disableCpuWatchdog_last_password());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxScuWdt_disableSafetyWatchdog_call_count());
    TEST_ASSERT_EQUAL_UINT16((uint16)0x5555U, mock_get_IfxScuWdt_disableSafetyWatchdog_last_password());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxCpu_emitEvent_call_count());
    TEST_ASSERT_EQUAL_PTR(&g_cpuSyncEvent, mock_get_IfxCpu_emitEvent_last_event());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxCpu_waitEvent_call_count());
    TEST_ASSERT_EQUAL_PTR(&g_cpuSyncEvent, mock_get_IfxCpu_waitEvent_last_event());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxCpu_waitEvent_last_count());
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_initLED_call_count());
    TEST_ASSERT_EQUAL_UINT32((uint32)CORE0_MAIN_LOOP_ITERATIONS, mock_get_blinkLED_call_count());
}

void test_core0_main_watchdog_password_zero(void)
{
    mock_set_IfxScuWdt_getCpuWatchdogPassword_return((uint16)0U);
    mock_set_IfxScuWdt_getSafetyWatchdogPassword_return((uint16)0U);
    core0_main();
    TEST_ASSERT_EQUAL_UINT16((uint16)0U, mock_get_IfxScuWdt_disableCpuWatchdog_last_password());
    TEST_ASSERT_EQUAL_UINT16((uint16)0U, mock_get_IfxScuWdt_disableSafetyWatchdog_last_password());
}

void test_core0_main_called_twice_accumulates_blinks(void)
{
    mock_set_IfxScuWdt_getCpuWatchdogPassword_return((uint16)0x1111U);
    mock_set_IfxScuWdt_getSafetyWatchdogPassword_return((uint16)0x2222U);
    core0_main();
    core0_main();
    TEST_ASSERT_EQUAL_UINT32(2U, mock_get_initLED_call_count());
    TEST_ASSERT_EQUAL_UINT32((uint32)(CORE0_MAIN_LOOP_ITERATIONS * 2U), mock_get_blinkLED_call_count());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_core0_main_invokes_startup_sequence_and_blink_loop);
    RUN_TEST(test_core0_main_watchdog_password_zero);
    RUN_TEST(test_core0_main_called_twice_accumulates_blinks);
    return UNITY_END();
}
