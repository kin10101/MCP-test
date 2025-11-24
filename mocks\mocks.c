#include "mocks.h"
#include <string.h>

/* Port definitions (extracted from JSON constant LED = &MODULE_P00,5) */
Ifx_P MODULE_P00 = {0};

/* BSP resources */
Ifx_STM g_mock_timer = {0};
Ifx_STM *BSP_DEFAULT_TIMER = &g_mock_timer;

/* Mock state structures */
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
    return mock_IfxStm_getTicksFromMilliseconds.return_value; /* default 0 if not set */
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


typedef struct {
    uint32 call_count;
    uint16 return_value;
} mock_IfxScuWdt_getCpuWatchdogPassword_state_t;
static mock_IfxScuWdt_getCpuWatchdogPassword_state_t mock_IfxScuWdt_getCpuWatchdogPassword = {0};

__attribute__((weak)) uint16 IfxScuWdt_getCpuWatchdogPassword(void) {
    mock_IfxScuWdt_getCpuWatchdogPassword.call_count++;
    return mock_IfxScuWdt_getCpuWatchdogPassword.return_value; /* default 0 if not set */
}

uint32 mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count(void) {
    return mock_IfxScuWdt_getCpuWatchdogPassword.call_count;
}

void mock_set_IfxScuWdt_getCpuWatchdogPassword_return(uint16 value) {
    mock_IfxScuWdt_getCpuWatchdogPassword.return_value = value;
}


typedef struct {
    uint32 call_count;
    uint16 last_password;
} mock_IfxScuWdt_disableCpuWatchdog_state_t;
static mock_IfxScuWdt_disableCpuWatchdog_state_t mock_IfxScuWdt_disableCpuWatchdog = {0};

__attribute__((weak)) void IfxScuWdt_disableCpuWatchdog(uint16 password) {
    mock_IfxScuWdt_disableCpuWatchdog.call_count++;
    mock_IfxScuWdt_disableCpuWatchdog.last_password = password;
}

uint32 mock_get_IfxScuWdt_disableCpuWatchdog_call_count(void) {
    return mock_IfxScuWdt_disableCpuWatchdog.call_count;
}


typedef struct {
    uint32 call_count;
    uint16 return_value;
} mock_IfxScuWdt_getSafetyWatchdogPassword_state_t;
static mock_IfxScuWdt_getSafetyWatchdogPassword_state_t mock_IfxScuWdt_getSafetyWatchdogPassword = {0};

__attribute__((weak)) uint16 IfxScuWdt_getSafetyWatchdogPassword(void) {
    mock_IfxScuWdt_getSafetyWatchdogPassword.call_count++;
    return mock_IfxScuWdt_getSafetyWatchdogPassword.return_value; /* default 0 if not set */
}

uint32 mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count(void) {
    return mock_IfxScuWdt_getSafetyWatchdogPassword.call_count;
}

void mock_set_IfxScuWdt_getSafetyWatchdogPassword_return(uint16 value) {
    mock_IfxScuWdt_getSafetyWatchdogPassword.return_value = value;
}


typedef struct {
    uint32 call_count;
    uint16 last_password;
} mock_IfxScuWdt_disableSafetyWatchdog_state_t;
static mock_IfxScuWdt_disableSafetyWatchdog_state_t mock_IfxScuWdt_disableSafetyWatchdog = {0};

__attribute__((weak)) void IfxScuWdt_disableSafetyWatchdog(uint16 password) {
    mock_IfxScuWdt_disableSafetyWatchdog.call_count++;
    mock_IfxScuWdt_disableSafetyWatchdog.last_password = password;
}

uint32 mock_get_IfxScuWdt_disableSafetyWatchdog_call_count(void) {
    return mock_IfxScuWdt_disableSafetyWatchdog.call_count;
}


typedef struct {
    uint32 call_count;
} mock_IfxCpu_enableInterrupts_state_t;
static mock_IfxCpu_enableInterrupts_state_t mock_IfxCpu_enableInterrupts = {0};

__attribute__((weak)) void IfxCpu_enableInterrupts(void) {
    mock_IfxCpu_enableInterrupts.call_count++;
}

uint32 mock_get_IfxCpu_enableInterrupts_call_count(void) {
    return mock_IfxCpu_enableInterrupts.call_count;
}


typedef struct {
    uint32 call_count;
    IfxCpu_syncEvent *last_event;
} mock_IfxCpu_emitEvent_state_t;
static mock_IfxCpu_emitEvent_state_t mock_IfxCpu_emitEvent = {0};

__attribute__((weak)) void IfxCpu_emitEvent(IfxCpu_syncEvent *event) {
    mock_IfxCpu_emitEvent.call_count++;
    mock_IfxCpu_emitEvent.last_event = event;
}

uint32 mock_get_IfxCpu_emitEvent_call_count(void) {
    return mock_IfxCpu_emitEvent.call_count;
}


typedef struct {
    uint32 call_count;
    IfxCpu_syncEvent *last_event;
    uint32 last_count;
} mock_IfxCpu_waitEvent_state_t;
static mock_IfxCpu_waitEvent_state_t mock_IfxCpu_waitEvent = {0};

__attribute__((weak)) void IfxCpu_waitEvent(IfxCpu_syncEvent *event, uint32 count) {
    mock_IfxCpu_waitEvent.call_count++;
    mock_IfxCpu_waitEvent.last_event = event;
    mock_IfxCpu_waitEvent.last_count = count;
}

uint32 mock_get_IfxCpu_waitEvent_call_count(void) {
    return mock_IfxCpu_waitEvent.call_count;
}


void mock_reset_all(void) {
    memset(&mock_IfxPort_setPinModeOutput, 0, sizeof(mock_IfxPort_setPinModeOutput));
    memset(&mock_IfxPort_setPinHigh, 0, sizeof(mock_IfxPort_setPinHigh));
    memset(&mock_IfxPort_togglePin, 0, sizeof(mock_IfxPort_togglePin));
    memset(&mock_IfxStm_getTicksFromMilliseconds, 0, sizeof(mock_IfxStm_getTicksFromMilliseconds));
    memset(&mock_waitTime, 0, sizeof(mock_waitTime));
    memset(&mock_IfxScuWdt_getCpuWatchdogPassword, 0, sizeof(mock_IfxScuWdt_getCpuWatchdogPassword));
    memset(&mock_IfxScuWdt_disableCpuWatchdog, 0, sizeof(mock_IfxScuWdt_disableCpuWatchdog));
    memset(&mock_IfxScuWdt_getSafetyWatchdogPassword, 0, sizeof(mock_IfxScuWdt_getSafetyWatchdogPassword));
    memset(&mock_IfxScuWdt_disableSafetyWatchdog, 0, sizeof(mock_IfxScuWdt_disableSafetyWatchdog));
    memset(&mock_IfxCpu_enableInterrupts, 0, sizeof(mock_IfxCpu_enableInterrupts));
    memset(&mock_IfxCpu_emitEvent, 0, sizeof(mock_IfxCpu_emitEvent));
    memset(&mock_IfxCpu_waitEvent, 0, sizeof(mock_IfxCpu_waitEvent));
}
