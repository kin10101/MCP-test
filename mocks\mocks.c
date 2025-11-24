#include "mocks.h"
#include <string.h>

/* Unique port definitions extracted from JSON macros */
Ifx_P MODULE_P00 = (Ifx_P){0};

/* BSP timer resource */
static Ifx_STM g_mock_timer = {0};
Ifx_STM *BSP_DEFAULT_TIMER = &g_mock_timer;

/* State structures */
typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
    IfxPort_OutputMode last_mode;
    IfxPort_OutputIdx last_idx;
} mock_IfxPort_setPinModeOutput_t;
static mock_IfxPort_setPinModeOutput_t mock_IfxPort_setPinModeOutput_state = {0};

__attribute__((weak)) void IfxPort_setPinModeOutput(Ifx_P *port, uint8 pin, IfxPort_OutputMode mode, IfxPort_OutputIdx idx) {
    mock_IfxPort_setPinModeOutput_state.call_count++;
    mock_IfxPort_setPinModeOutput_state.last_port = port;
    mock_IfxPort_setPinModeOutput_state.last_pin = pin;
    mock_IfxPort_setPinModeOutput_state.last_mode = mode;
    mock_IfxPort_setPinModeOutput_state.last_idx = idx;
}

uint32 mock_get_IfxPort_setPinModeOutput_call_count(void) {
    return mock_IfxPort_setPinModeOutput_state.call_count;
}


typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_setPinHigh_t;
static mock_IfxPort_setPinHigh_t mock_IfxPort_setPinHigh_state = {0};

__attribute__((weak)) void IfxPort_setPinHigh(Ifx_P *port, uint8 pin) {
    mock_IfxPort_setPinHigh_state.call_count++;
    mock_IfxPort_setPinHigh_state.last_port = port;
    mock_IfxPort_setPinHigh_state.last_pin = pin;
}

uint32 mock_get_IfxPort_setPinHigh_call_count(void) {
    return mock_IfxPort_setPinHigh_state.call_count;
}


typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_togglePin_t;
static mock_IfxPort_togglePin_t mock_IfxPort_togglePin_state = {0};

__attribute__((weak)) void IfxPort_togglePin(Ifx_P *port, uint8 pin) {
    mock_IfxPort_togglePin_state.call_count++;
    mock_IfxPort_togglePin_state.last_port = port;
    mock_IfxPort_togglePin_state.last_pin = pin;
}

uint32 mock_get_IfxPort_togglePin_call_count(void) {
    return mock_IfxPort_togglePin_state.call_count;
}


typedef struct {
    uint32 call_count;
    Ifx_STM *last_stm;
    uint32 last_ms;
    uint32 return_value;
} mock_IfxStm_getTicksFromMilliseconds_t;
static mock_IfxStm_getTicksFromMilliseconds_t mock_IfxStm_getTicksFromMilliseconds_state = {0};

__attribute__((weak)) uint32 IfxStm_getTicksFromMilliseconds(Ifx_STM *stm, uint32 ms) {
    mock_IfxStm_getTicksFromMilliseconds_state.call_count++;
    mock_IfxStm_getTicksFromMilliseconds_state.last_stm = stm;
    mock_IfxStm_getTicksFromMilliseconds_state.last_ms = ms;
    if (mock_IfxStm_getTicksFromMilliseconds_state.return_value != 0U) {
        return mock_IfxStm_getTicksFromMilliseconds_state.return_value;
    }
    return 0U;
}

uint32 mock_get_IfxStm_getTicksFromMilliseconds_call_count(void) {
    return mock_IfxStm_getTicksFromMilliseconds_state.call_count;
}

void mock_set_IfxStm_getTicksFromMilliseconds_return(uint32 value) {
    mock_IfxStm_getTicksFromMilliseconds_state.return_value = value;
}


typedef struct {
    uint32 call_count;
    uint32 last_ticks;
} mock_waitTime_t;
static mock_waitTime_t mock_waitTime_state = {0};

__attribute__((weak)) void waitTime(uint32 ticks) {
    mock_waitTime_state.call_count++;
    mock_waitTime_state.last_ticks = ticks;
}

uint32 mock_get_waitTime_call_count(void) {
    return mock_waitTime_state.call_count;
}


typedef struct { uint32 call_count; } mock_IfxCpu_enableInterrupts_t;
static mock_IfxCpu_enableInterrupts_t mock_IfxCpu_enableInterrupts_state = {0};

__attribute__((weak)) void IfxCpu_enableInterrupts(void) {
    mock_IfxCpu_enableInterrupts_state.call_count++;
}

uint32 mock_get_IfxCpu_enableInterrupts_call_count(void) {
    return mock_IfxCpu_enableInterrupts_state.call_count;
}


typedef struct {
    uint32 call_count;
    uint16 return_value;
} mock_IfxScuWdt_getCpuWatchdogPassword_t;
static mock_IfxScuWdt_getCpuWatchdogPassword_t mock_IfxScuWdt_getCpuWatchdogPassword_state = {0};

__attribute__((weak)) uint16 IfxScuWdt_getCpuWatchdogPassword(void) {
    mock_IfxScuWdt_getCpuWatchdogPassword_state.call_count++;
    if (mock_IfxScuWdt_getCpuWatchdogPassword_state.return_value != 0U) {
        return mock_IfxScuWdt_getCpuWatchdogPassword_state.return_value;
    }
    return 0U;
}

uint32 mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count(void) {
    return mock_IfxScuWdt_getCpuWatchdogPassword_state.call_count;
}

void mock_set_IfxScuWdt_getCpuWatchdogPassword_return(uint16 value) {
    mock_IfxScuWdt_getCpuWatchdogPassword_state.return_value = value;
}


typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableCpuWatchdog_t;
static mock_IfxScuWdt_disableCpuWatchdog_t mock_IfxScuWdt_disableCpuWatchdog_state = {0};

__attribute__((weak)) void IfxScuWdt_disableCpuWatchdog(uint16 password) {
    mock_IfxScuWdt_disableCpuWatchdog_state.call_count++;
    mock_IfxScuWdt_disableCpuWatchdog_state.last_password = password;
}

uint32 mock_get_IfxScuWdt_disableCpuWatchdog_call_count(void) {
    return mock_IfxScuWdt_disableCpuWatchdog_state.call_count;
}


typedef struct {
    uint32 call_count;
    uint16 return_value;
} mock_IfxScuWdt_getSafetyWatchdogPassword_t;
static mock_IfxScuWdt_getSafetyWatchdogPassword_t mock_IfxScuWdt_getSafetyWatchdogPassword_state = {0};

__attribute__((weak)) uint16 IfxScuWdt_getSafetyWatchdogPassword(void) {
    mock_IfxScuWdt_getSafetyWatchdogPassword_state.call_count++;
    if (mock_IfxScuWdt_getSafetyWatchdogPassword_state.return_value != 0U) {
        return mock_IfxScuWdt_getSafetyWatchdogPassword_state.return_value;
    }
    return 0U;
}

uint32 mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count(void) {
    return mock_IfxScuWdt_getSafetyWatchdogPassword_state.call_count;
}

void mock_set_IfxScuWdt_getSafetyWatchdogPassword_return(uint16 value) {
    mock_IfxScuWdt_getSafetyWatchdogPassword_state.return_value = value;
}


typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableSafetyWatchdog_t;
static mock_IfxScuWdt_disableSafetyWatchdog_t mock_IfxScuWdt_disableSafetyWatchdog_state = {0};

__attribute__((weak)) void IfxScuWdt_disableSafetyWatchdog(uint16 password) {
    mock_IfxScuWdt_disableSafetyWatchdog_state.call_count++;
    mock_IfxScuWdt_disableSafetyWatchdog_state.last_password = password;
}

uint32 mock_get_IfxScuWdt_disableSafetyWatchdog_call_count(void) {
    return mock_IfxScuWdt_disableSafetyWatchdog_state.call_count;
}


typedef struct { uint32 call_count; IfxCpu_syncEvent *last_event; } mock_IfxCpu_emitEvent_t;
static mock_IfxCpu_emitEvent_t mock_IfxCpu_emitEvent_state = {0};

__attribute__((weak)) void IfxCpu_emitEvent(IfxCpu_syncEvent *event) {
    mock_IfxCpu_emitEvent_state.call_count++;
    mock_IfxCpu_emitEvent_state.last_event = event;
}

uint32 mock_get_IfxCpu_emitEvent_call_count(void) {
    return mock_IfxCpu_emitEvent_state.call_count;
}


typedef struct { uint32 call_count; IfxCpu_syncEvent *last_event; uint32 last_count; } mock_IfxCpu_waitEvent_t;
static mock_IfxCpu_waitEvent_t mock_IfxCpu_waitEvent_state = {0};

__attribute__((weak)) void IfxCpu_waitEvent(IfxCpu_syncEvent *event, uint32 count) {
    mock_IfxCpu_waitEvent_state.call_count++;
    mock_IfxCpu_waitEvent_state.last_event = event;
    mock_IfxCpu_waitEvent_state.last_count = count;
}

uint32 mock_get_IfxCpu_waitEvent_call_count(void) {
    return mock_IfxCpu_waitEvent_state.call_count;
}


void mock_reset_all(void) {
    memset(&mock_IfxPort_setPinModeOutput_state, 0, sizeof(mock_IfxPort_setPinModeOutput_state));
    memset(&mock_IfxPort_setPinHigh_state, 0, sizeof(mock_IfxPort_setPinHigh_state));
    memset(&mock_IfxPort_togglePin_state, 0, sizeof(mock_IfxPort_togglePin_state));
    memset(&mock_IfxStm_getTicksFromMilliseconds_state, 0, sizeof(mock_IfxStm_getTicksFromMilliseconds_state));
    memset(&mock_waitTime_state, 0, sizeof(mock_waitTime_state));
    memset(&mock_IfxCpu_enableInterrupts_state, 0, sizeof(mock_IfxCpu_enableInterrupts_state));
    memset(&mock_IfxScuWdt_getCpuWatchdogPassword_state, 0, sizeof(mock_IfxScuWdt_getCpuWatchdogPassword_state));
    memset(&mock_IfxScuWdt_disableCpuWatchdog_state, 0, sizeof(mock_IfxScuWdt_disableCpuWatchdog_state));
    memset(&mock_IfxScuWdt_getSafetyWatchdogPassword_state, 0, sizeof(mock_IfxScuWdt_getSafetyWatchdogPassword_state));
    memset(&mock_IfxScuWdt_disableSafetyWatchdog_state, 0, sizeof(mock_IfxScuWdt_disableSafetyWatchdog_state));
    memset(&mock_IfxCpu_emitEvent_state, 0, sizeof(mock_IfxCpu_emitEvent_state));
    memset(&mock_IfxCpu_waitEvent_state, 0, sizeof(mock_IfxCpu_waitEvent_state));
}
