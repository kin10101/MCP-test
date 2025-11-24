/* test_core0_main.c - SELF-CONTAINED */

#include "unity.h"
#include "mock_config.h"
#include <string.h>

/* ========================================================================
   INLINE MACROS AND GLOBALS - From JSON Defined Variables
   ======================================================================== */
#ifndef TEST_MAX_BLINKS
#define TEST_MAX_BLINKS ((uint8)3)
#endif

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Only for dependencies of core0_main
   ======================================================================== */

typedef struct { uint32 call_count; } mock_IfxCpu_enableInterrupts_state_t;
static mock_IfxCpu_enableInterrupts_state_t mock_IfxCpu_enableInterrupts = {0};

__attribute__((weak)) void IfxCpu_enableInterrupts(void) {
    mock_IfxCpu_enableInterrupts.call_count++;
}

uint32 mock_get_IfxCpu_enableInterrupts_call_count(void) {
    return mock_IfxCpu_enableInterrupts.call_count;
}


typedef struct { uint32 call_count; uint16 return_value; } mock_IfxScuWdt_getCpuWatchdogPassword_state_t;
static mock_IfxScuWdt_getCpuWatchdogPassword_state_t mock_IfxScuWdt_getCpuWatchdogPassword = {0};

__attribute__((weak)) uint16 IfxScuWdt_getCpuWatchdogPassword(void) {
    mock_IfxScuWdt_getCpuWatchdogPassword.call_count++;
    return mock_IfxScuWdt_getCpuWatchdogPassword.return_value;
}

uint32 mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count(void) {
    return mock_IfxScuWdt_getCpuWatchdogPassword.call_count;
}

void mock_set_IfxScuWdt_getCpuWatchdogPassword_return(uint16 value) {
    mock_IfxScuWdt_getCpuWatchdogPassword.return_value = value;
}


typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableCpuWatchdog_state_t;
static mock_IfxScuWdt_disableCpuWatchdog_state_t mock_IfxScuWdt_disableCpuWatchdog = {0};

__attribute__((weak)) void IfxScuWdt_disableCpuWatchdog(uint16 password) {
    mock_IfxScuWdt_disableCpuWatchdog.call_count++;
    mock_IfxScuWdt_disableCpuWatchdog.last_password = password;
}

uint32 mock_get_IfxScuWdt_disableCpuWatchdog_call_count(void) {
    return mock_IfxScuWdt_disableCpuWatchdog.call_count;
}


typedef struct { uint32 call_count; uint16 return_value; } mock_IfxScuWdt_getSafetyWatchdogPassword_state_t;
static mock_IfxScuWdt_getSafetyWatchdogPassword_state_t mock_IfxScuWdt_getSafetyWatchdogPassword = {0};

__attribute__((weak)) uint16 IfxScuWdt_getSafetyWatchdogPassword(void) {
    mock_IfxScuWdt_getSafetyWatchdogPassword.call_count++;
    return mock_IfxScuWdt_getSafetyWatchdogPassword.return_value;
}

uint32 mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count(void) {
    return mock_IfxScuWdt_getSafetyWatchdogPassword.call_count;
}

void mock_set_IfxScuWdt_getSafetyWatchdogPassword_return(uint16 value) {
    mock_IfxScuWdt_getSafetyWatchdogPassword.return_value = value;
}


typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableSafetyWatchdog_state_t;
static mock_IfxScuWdt_disableSafetyWatchdog_state_t mock_IfxScuWdt_disableSafetyWatchdog = {0};

__attribute__((weak)) void IfxScuWdt_disableSafetyWatchdog(uint16 password) {
    mock_IfxScuWdt_disableSafetyWatchdog.call_count++;
    mock_IfxScuWdt_disableSafetyWatchdog.last_password = password;
}

uint32 mock_get_IfxScuWdt_disableSafetyWatchdog_call_count(void) {
    return mock_IfxScuWdt_disableSafetyWatchdog.call_count;
}


typedef struct { uint32 call_count; IfxCpu_syncEvent *last_event; } mock_IfxCpu_emitEvent_state_t;
static mock_IfxCpu_emitEvent_state_t mock_IfxCpu_emitEvent = {0};

__attribute__((weak)) void IfxCpu_emitEvent(IfxCpu_syncEvent *event) {
    mock_IfxCpu_emitEvent.call_count++;
    mock_IfxCpu_emitEvent.last_event = event;
}

uint32 mock_get_IfxCpu_emitEvent_call_count(void) {
    return mock_IfxCpu_emitEvent.call_count;
}


typedef struct { uint32 call_count; IfxCpu_syncEvent *last_event; uint32 last_count; } mock_IfxCpu_waitEvent_state_t;
static mock_IfxCpu_waitEvent_state_t mock_IfxCpu_waitEvent = {0};

__attribute__((weak)) void IfxCpu_waitEvent(IfxCpu_syncEvent *event, uint32 count) {
    mock_IfxCpu_waitEvent.call_count++;
    mock_IfxCpu_waitEvent.last_event = event;
    mock_IfxCpu_waitEvent.last_count = count;
}

uint32 mock_get_IfxCpu_waitEvent_call_count(void) {
    return mock_IfxCpu_waitEvent.call_count;
}


typedef struct { uint32 call_count; } mock_initLED_state_t;
static mock_initLED_state_t mock_initLED = {0};

__attribute__((weak)) void initLED(void) {
    mock_initLED.call_count++;
}

uint32 mock_get_initLED_call_count(void) {
    return mock_initLED.call_count;
}


typedef struct { uint32 call_count; } mock_blinkLED_state_t;
static mock_blinkLED_state_t mock_blinkLED = {0};

__attribute__((weak)) void blinkLED(void) {
    mock_blinkLED.call_count++;
}

uint32 mock_get_blinkLED_call_count(void) {
    return mock_blinkLED.call_count;
}

void mock_reset_all(void) {
    memset(&mock_IfxCpu_enableInterrupts, 0, sizeof(mock_IfxCpu_enableInterrupts));
    memset(&mock_IfxScuWdt_getCpuWatchdogPassword, 0, sizeof(mock_IfxScuWdt_getCpuWatchdogPassword));
    memset(&mock_IfxScuWdt_disableCpuWatchdog, 0, sizeof(mock_IfxScuWdt_disableCpuWatchdog));
    memset(&mock_IfxScuWdt_getSafetyWatchdogPassword, 0, sizeof(mock_IfxScuWdt_getSafetyWatchdogPassword));
    memset(&mock_IfxScuWdt_disableSafetyWatchdog, 0, sizeof(mock_IfxScuWdt_disableSafetyWatchdog));
    memset(&mock_IfxCpu_emitEvent, 0, sizeof(mock_IfxCpu_emitEvent));
    memset(&mock_IfxCpu_waitEvent, 0, sizeof(mock_IfxCpu_waitEvent));
    memset(&mock_initLED, 0, sizeof(mock_initLED));
    memset(&mock_blinkLED, 0, sizeof(mock_blinkLED));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST - From JSON Functions[] (instrumented with TEST_MAX_BLINKS)
   ======================================================================== */
void core0_main(void) {
    IfxCpu_enableInterrupts();

    uint16 cpuPw = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_disableCpuWatchdog(cpuPw);

    uint16 safetyPw = IfxScuWdt_getSafetyWatchdogPassword();
    IfxScuWdt_disableSafetyWatchdog(safetyPw);

    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    initLED();

    uint8 i;
    for (i = 0; i < TEST_MAX_BLINKS; i++) {
        blinkLED();
    }
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) {
    mock_reset_all();
}

void tearDown(void) {}

void test_core0_main_initialization_and_watchdog_handling(void) {
    mock_set_IfxScuWdt_getCpuWatchdogPassword_return(0xABCD);
    mock_set_IfxScuWdt_getSafetyWatchdogPassword_return(0x1234);

    core0_main();

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxCpu_enableInterrupts_call_count());

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count());
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxScuWdt_disableCpuWatchdog_call_count());
    TEST_ASSERT_EQUAL_UINT16(0xABCD, mock_IfxScuWdt_disableCpuWatchdog.last_password);

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count());
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxScuWdt_disableSafetyWatchdog_call_count());
    TEST_ASSERT_EQUAL_UINT16(0x1234, mock_IfxScuWdt_disableSafetyWatchdog.last_password);

    TEST_ASSERT_EQUAL_UINT32(1, mock_get_initLED_call_count());
}

void test_core0_main_emits_and_waits_cpu_sync_event(void) {
    core0_main();
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxCpu_emitEvent_call_count());
    TEST_ASSERT_EQUAL_UINT32(1, mock_get_IfxCpu_waitEvent_call_count());
    TEST_ASSERT_TRUE(mock_IfxCpu_emitEvent.last_event == &g_cpuSyncEvent);
    TEST_ASSERT_TRUE(mock_IfxCpu_waitEvent.last_event == &g_cpuSyncEvent);
    TEST_ASSERT_EQUAL_UINT32(1, mock_IfxCpu_waitEvent.last_count);
}

void test_core0_main_calls_blinkLED_expected_times(void) {
    core0_main();
    TEST_ASSERT_EQUAL_UINT32(TEST_MAX_BLINKS, mock_get_blinkLED_call_count());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_core0_main_initialization_and_watchdog_handling);
    RUN_TEST(test_core0_main_emits_and_waits_cpu_sync_event);
    RUN_TEST(test_core0_main_calls_blinkLED_expected_times);
    return UNITY_END();
}
