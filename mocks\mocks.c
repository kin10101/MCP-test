#include "mocks.h"
#include <string.h>

/* Port definitions */
Ifx_P MODULE_P00 = {0};

/* EVADC module definition */
Ifx_EVADC MODULE_EVADC = {0};

/* ASCLIN pin mappings used by project */
const IfxAsclin_Asc_PinMapping IfxAsclin0_RXA_P14_1_IN = { (void*)0x12340001 };
const IfxAsclin_Asc_PinMapping IfxAsclin0_TX_P14_0_OUT = { (void*)0x12340002 };

/* Global variables from project */
IfxCpu_syncEvent g_cpuSyncEvent = 0U;
IfxEvadc_Adc g_evadc = {0};
IfxEvadc_Adc_Group g_adcGroup = {0};
IfxEvadc_Adc_Channel g_adcChannel[3] = { {0}, {0}, {0} };
uint8 g_grp8channels[3] = { 7U, 6U, 5U };
Ifx_EVADC_G_RES g_results[3] = {0};
IfxAsclin_Asc g_asc = {0};
uint8 g_ascTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8U] = {0};

/* ======================= Mock states ======================= */

typedef struct {
    uint32 call_count;
    IfxAsclin_Asc *last_asc;
} mock_IfxAsclin_Asc_isrTransmit_t;
static mock_IfxAsclin_Asc_isrTransmit_t mock_IfxAsclin_Asc_isrTransmit = {0};

__attribute__((weak)) void IfxAsclin_Asc_isrTransmit(IfxAsclin_Asc *asc) {
    mock_IfxAsclin_Asc_isrTransmit.call_count++;
    mock_IfxAsclin_Asc_isrTransmit.last_asc = asc;
}

uint32 mock_get_IfxAsclin_Asc_isrTransmit_call_count(void) { return mock_IfxAsclin_Asc_isrTransmit.call_count; }


typedef struct {
    uint32 call_count;
    IfxAsclin_Asc_Config *last_cfg;
    void *last_module;
} mock_IfxAsclin_Asc_initModuleConfig_t;
static mock_IfxAsclin_Asc_initModuleConfig_t mock_IfxAsclin_Asc_initModuleConfig = {0};

__attribute__((weak)) void IfxAsclin_Asc_initModuleConfig(IfxAsclin_Asc_Config *cfg, void *module) {
    mock_IfxAsclin_Asc_initModuleConfig.call_count++;
    mock_IfxAsclin_Asc_initModuleConfig.last_cfg = cfg;
    mock_IfxAsclin_Asc_initModuleConfig.last_module = module;
}

uint32 mock_get_IfxAsclin_Asc_initModuleConfig_call_count(void) { return mock_IfxAsclin_Asc_initModuleConfig.call_count; }


typedef struct {
    uint32 call_count;
    IfxAsclin_Asc *last_asc;
    IfxAsclin_Asc_Config *last_cfg;
    boolean return_value;
} mock_IfxAsclin_Asc_initModule_t;
static mock_IfxAsclin_Asc_initModule_t mock_IfxAsclin_Asc_initModule = {0};

__attribute__((weak)) boolean IfxAsclin_Asc_initModule(IfxAsclin_Asc *asc, IfxAsclin_Asc_Config *cfg) {
    mock_IfxAsclin_Asc_initModule.call_count++;
    mock_IfxAsclin_Asc_initModule.last_asc = asc;
    mock_IfxAsclin_Asc_initModule.last_cfg = cfg;
    if (mock_IfxAsclin_Asc_initModule.return_value != FALSE) {
        return mock_IfxAsclin_Asc_initModule.return_value;
    }
    return TRUE;
}

void mock_set_IfxAsclin_Asc_initModule_return(boolean value) { mock_IfxAsclin_Asc_initModule.return_value = value; }
uint32 mock_get_IfxAsclin_Asc_initModule_call_count(void) { return mock_IfxAsclin_Asc_initModule.call_count; }


typedef struct {
    uint32 call_count;
    IfxAsclin_Asc *last_asc;
    uint8 *last_data;
    uint32 last_len_value;
    uint32 *last_len_ptr;
    uint32 last_timeout;
} mock_IfxAsclin_Asc_write_t;
static mock_IfxAsclin_Asc_write_t mock_IfxAsclin_Asc_write = {0};

__attribute__((weak)) uint32 IfxAsclin_Asc_write(IfxAsclin_Asc *asc, uint8 *data, uint32 *len, uint32 timeout) {
    mock_IfxAsclin_Asc_write.call_count++;
    mock_IfxAsclin_Asc_write.last_asc = asc;
    mock_IfxAsclin_Asc_write.last_data = data;
    mock_IfxAsclin_Asc_write.last_len_ptr = len;
    mock_IfxAsclin_Asc_write.last_timeout = timeout;
    mock_IfxAsclin_Asc_write.last_len_value = (len != NULL) ? *len : 0U;
    return mock_IfxAsclin_Asc_write.last_len_value;
}

uint32 mock_get_IfxAsclin_Asc_write_call_count(void) { return mock_IfxAsclin_Asc_write.call_count; }


typedef struct {
    uint32 call_count;
    uint32 last_coreIndex;
    uint32 return_value;
} mock_IfxCpu_Irq_getTos_t;
static mock_IfxCpu_Irq_getTos_t mock_IfxCpu_Irq_getTos = {0};

__attribute__((weak)) uint32 IfxCpu_Irq_getTos(uint32 coreIndex) {
    mock_IfxCpu_Irq_getTos.call_count++;
    mock_IfxCpu_Irq_getTos.last_coreIndex = coreIndex;
    if (mock_IfxCpu_Irq_getTos.return_value != 0U) {
        return mock_IfxCpu_Irq_getTos.return_value;
    }
    return 0U;
}

void mock_set_IfxCpu_Irq_getTos_return(uint32 value) { mock_IfxCpu_Irq_getTos.return_value = value; }
uint32 mock_get_IfxCpu_Irq_getTos_call_count(void) { return mock_IfxCpu_Irq_getTos.call_count; }


typedef struct {
    uint32 call_count;
    uint32 return_value;
} mock_IfxCpu_getCoreIndex_t;
static mock_IfxCpu_getCoreIndex_t mock_IfxCpu_getCoreIndex = {0};

__attribute__((weak)) uint32 IfxCpu_getCoreIndex(void) {
    mock_IfxCpu_getCoreIndex.call_count++;
    if (mock_IfxCpu_getCoreIndex.return_value != 0U) {
        return mock_IfxCpu_getCoreIndex.return_value;
    }
    return 0U;
}

void mock_set_IfxCpu_getCoreIndex_return(uint32 value) { mock_IfxCpu_getCoreIndex.return_value = value; }
uint32 mock_get_IfxCpu_getCoreIndex_call_count(void) { return mock_IfxCpu_getCoreIndex.call_count; }


typedef struct {
    uint32 call_count;
} mock_IfxCpu_enableInterrupts_t;
static mock_IfxCpu_enableInterrupts_t mock_IfxCpu_enableInterrupts = {0};

__attribute__((weak)) void IfxCpu_enableInterrupts(void) {
    mock_IfxCpu_enableInterrupts.call_count++;
}

uint32 mock_get_IfxCpu_enableInterrupts_call_count(void) { return mock_IfxCpu_enableInterrupts.call_count; }

/* EVADC init chain */
typedef struct {
    uint32 call_count;
    IfxEvadc_Adc_Config *last_cfg;
    Ifx_EVADC *last_module;
} mock_IfxEvadc_Adc_initModuleConfig_t;
static mock_IfxEvadc_Adc_initModuleConfig_t mock_IfxEvadc_Adc_initModuleConfig = {0};

__attribute__((weak)) void IfxEvadc_Adc_initModuleConfig(IfxEvadc_Adc_Config *cfg, Ifx_EVADC *module) {
    mock_IfxEvadc_Adc_initModuleConfig.call_count++;
    mock_IfxEvadc_Adc_initModuleConfig.last_cfg = cfg;
    mock_IfxEvadc_Adc_initModuleConfig.last_module = module;
}

uint32 mock_get_IfxEvadc_Adc_initModuleConfig_call_count(void) { return mock_IfxEvadc_Adc_initModuleConfig.call_count; }


typedef struct {
    uint32 call_count;
    IfxEvadc_Adc *last_adc;
    IfxEvadc_Adc_Config *last_cfg;
    boolean return_value;
} mock_IfxEvadc_Adc_initModule_t;
static mock_IfxEvadc_Adc_initModule_t mock_IfxEvadc_Adc_initModule = {0};

__attribute__((weak)) boolean IfxEvadc_Adc_initModule(IfxEvadc_Adc *adc, IfxEvadc_Adc_Config *cfg) {
    mock_IfxEvadc_Adc_initModule.call_count++;
    mock_IfxEvadc_Adc_initModule.last_adc = adc;
    mock_IfxEvadc_Adc_initModule.last_cfg = cfg;
    if (mock_IfxEvadc_Adc_initModule.return_value != FALSE) {
        return mock_IfxEvadc_Adc_initModule.return_value;
    }
    return TRUE;
}

void mock_set_IfxEvadc_Adc_initModule_return(boolean value) { mock_IfxEvadc_Adc_initModule.return_value = value; }
uint32 mock_get_IfxEvadc_Adc_initModule_call_count(void) { return mock_IfxEvadc_Adc_initModule.call_count; }


typedef struct {
    uint32 call_count;
    IfxEvadc_Adc_GroupConfig *last_cfg;
    IfxEvadc_Adc *last_adc;
} mock_IfxEvadc_Adc_initGroupConfig_t;
static mock_IfxEvadc_Adc_initGroupConfig_t mock_IfxEvadc_Adc_initGroupConfig = {0};

__attribute__((weak)) void IfxEvadc_Adc_initGroupConfig(IfxEvadc_Adc_GroupConfig *cfg, IfxEvadc_Adc *adc) {
    mock_IfxEvadc_Adc_initGroupConfig.call_count++;
    mock_IfxEvadc_Adc_initGroupConfig.last_cfg = cfg;
    mock_IfxEvadc_Adc_initGroupConfig.last_adc = adc;
}

uint32 mock_get_IfxEvadc_Adc_initGroupConfig_call_count(void) { return mock_IfxEvadc_Adc_initGroupConfig.call_count; }


typedef struct {
    uint32 call_count;
    IfxEvadc_Adc_Group *last_grp;
    IfxEvadc_Adc_GroupConfig *last_cfg;
    boolean return_value;
} mock_IfxEvadc_Adc_initGroup_t;
static mock_IfxEvadc_Adc_initGroup_t mock_IfxEvadc_Adc_initGroup = {0};

__attribute__((weak)) boolean IfxEvadc_Adc_initGroup(IfxEvadc_Adc_Group *grp, IfxEvadc_Adc_GroupConfig *cfg) {
    mock_IfxEvadc_Adc_initGroup.call_count++;
    mock_IfxEvadc_Adc_initGroup.last_grp = grp;
    mock_IfxEvadc_Adc_initGroup.last_cfg = cfg;
    if (mock_IfxEvadc_Adc_initGroup.return_value != FALSE) {
        return mock_IfxEvadc_Adc_initGroup.return_value;
    }
    return TRUE;
}

void mock_set_IfxEvadc_Adc_initGroup_return(boolean value) { mock_IfxEvadc_Adc_initGroup.return_value = value; }
uint32 mock_get_IfxEvadc_Adc_initGroup_call_count(void) { return mock_IfxEvadc_Adc_initGroup.call_count; }


typedef struct {
    uint32 call_count;
    IfxEvadc_Adc_ChannelConfig *last_cfg;
    IfxEvadc_Adc_Group *last_grp;
} mock_IfxEvadc_Adc_initChannelConfig_t;
static mock_IfxEvadc_Adc_initChannelConfig_t mock_IfxEvadc_Adc_initChannelConfig = {0};

__attribute__((weak)) void IfxEvadc_Adc_initChannelConfig(IfxEvadc_Adc_ChannelConfig *cfg, IfxEvadc_Adc_Group *grp) {
    mock_IfxEvadc_Adc_initChannelConfig.call_count++;
    mock_IfxEvadc_Adc_initChannelConfig.last_cfg = cfg;
    mock_IfxEvadc_Adc_initChannelConfig.last_grp = grp;
}

uint32 mock_get_IfxEvadc_Adc_initChannelConfig_call_count(void) { return mock_IfxEvadc_Adc_initChannelConfig.call_count; }


typedef struct {
    uint32 call_count;
    IfxEvadc_Adc_Channel *last_ch;
    IfxEvadc_Adc_ChannelConfig *last_cfg;
    boolean return_value;
} mock_IfxEvadc_Adc_initChannel_t;
static mock_IfxEvadc_Adc_initChannel_t mock_IfxEvadc_Adc_initChannel = {0};

__attribute__((weak)) boolean IfxEvadc_Adc_initChannel(IfxEvadc_Adc_Channel *ch, IfxEvadc_Adc_ChannelConfig *cfg) {
    mock_IfxEvadc_Adc_initChannel.call_count++;
    mock_IfxEvadc_Adc_initChannel.last_ch = ch;
    mock_IfxEvadc_Adc_initChannel.last_cfg = cfg;
    if (mock_IfxEvadc_Adc_initChannel.return_value != FALSE) {
        return mock_IfxEvadc_Adc_initChannel.return_value;
    }
    return TRUE;
}

void mock_set_IfxEvadc_Adc_initChannel_return(boolean value) { mock_IfxEvadc_Adc_initChannel.return_value = value; }
uint32 mock_get_IfxEvadc_Adc_initChannel_call_count(void) { return mock_IfxEvadc_Adc_initChannel.call_count; }


typedef struct {
    uint32 call_count;
    IfxEvadc_Adc_Channel *last_ch;
    uint32 last_requestSource;
    uint32 last_refill;
    boolean return_value;
} mock_IfxEvadc_Adc_addToQueue_t;
static mock_IfxEvadc_Adc_addToQueue_t mock_IfxEvadc_Adc_addToQueue = {0};

__attribute__((weak)) boolean IfxEvadc_Adc_addToQueue(IfxEvadc_Adc_Channel *ch, uint32 requestSource, uint32 refill) {
    mock_IfxEvadc_Adc_addToQueue.call_count++;
    mock_IfxEvadc_Adc_addToQueue.last_ch = ch;
    mock_IfxEvadc_Adc_addToQueue.last_requestSource = requestSource;
    mock_IfxEvadc_Adc_addToQueue.last_refill = refill;
    if (mock_IfxEvadc_Adc_addToQueue.return_value != FALSE) {
        return mock_IfxEvadc_Adc_addToQueue.return_value;
    }
    return TRUE;
}

void mock_set_IfxEvadc_Adc_addToQueue_return(boolean value) { mock_IfxEvadc_Adc_addToQueue.return_value = value; }
uint32 mock_get_IfxEvadc_Adc_addToQueue_call_count(void) { return mock_IfxEvadc_Adc_addToQueue.call_count; }


typedef struct {
    uint32 call_count;
    IfxEvadc_Adc_Group *last_grp;
    uint32 last_requestSource;
    boolean return_value;
} mock_IfxEvadc_Adc_startQueue_t;
static mock_IfxEvadc_Adc_startQueue_t mock_IfxEvadc_Adc_startQueue = {0};

__attribute__((weak)) boolean IfxEvadc_Adc_startQueue(IfxEvadc_Adc_Group *grp, uint32 requestSource) {
    mock_IfxEvadc_Adc_startQueue.call_count++;
    mock_IfxEvadc_Adc_startQueue.last_grp = grp;
    mock_IfxEvadc_Adc_startQueue.last_requestSource = requestSource;
    if (mock_IfxEvadc_Adc_startQueue.return_value != FALSE) {
        return mock_IfxEvadc_Adc_startQueue.return_value;
    }
    return TRUE;
}

void mock_set_IfxEvadc_Adc_startQueue_return(boolean value) { mock_IfxEvadc_Adc_startQueue.return_value = value; }
uint32 mock_get_IfxEvadc_Adc_startQueue_call_count(void) { return mock_IfxEvadc_Adc_startQueue.call_count; }


typedef struct {
    uint32 call_count;
    IfxEvadc_Adc_Channel *last_ch;
    Ifx_EVADC_G_RES return_value;
} mock_IfxEvadc_Adc_getResult_t;
static mock_IfxEvadc_Adc_getResult_t mock_IfxEvadc_Adc_getResult = {0};

__attribute__((weak)) Ifx_EVADC_G_RES IfxEvadc_Adc_getResult(IfxEvadc_Adc_Channel *ch) {
    mock_IfxEvadc_Adc_getResult.call_count++;
    mock_IfxEvadc_Adc_getResult.last_ch = ch;
    if (mock_IfxEvadc_Adc_getResult.return_value.B.VF != 0U || mock_IfxEvadc_Adc_getResult.return_value.B.RESULT != 0U) {
        return mock_IfxEvadc_Adc_getResult.return_value;
    }
    Ifx_EVADC_G_RES r;
    r.B.VF = 1U;
    r.B.RESULT = 1234U;
    return r;
}

void mock_set_IfxEvadc_Adc_getResult_return(Ifx_EVADC_G_RES value) { mock_IfxEvadc_Adc_getResult.return_value = value; }
uint32 mock_get_IfxEvadc_Adc_getResult_call_count(void) { return mock_IfxEvadc_Adc_getResult.call_count; }

/* Port operations */
typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
    uint8 last_mode;
} mock_IfxPort_setPinMode_t;
static mock_IfxPort_setPinMode_t mock_IfxPort_setPinMode = {0};

__attribute__((weak)) void IfxPort_setPinMode(Ifx_P *port, uint8 pin, uint8 mode) {
    mock_IfxPort_setPinMode.call_count++;
    mock_IfxPort_setPinMode.last_port = port;
    mock_IfxPort_setPinMode.last_pin = pin;
    mock_IfxPort_setPinMode.last_mode = mode;
}

uint32 mock_get_IfxPort_setPinMode_call_count(void) { return mock_IfxPort_setPinMode.call_count; }


typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_setPinHigh_t;
static mock_IfxPort_setPinHigh_t mock_IfxPort_setPinHigh = {0};

__attribute__((weak)) void IfxPort_setPinHigh(Ifx_P *port, uint8 pin) {
    mock_IfxPort_setPinHigh.call_count++;
    mock_IfxPort_setPinHigh.last_port = port;
    mock_IfxPort_setPinHigh.last_pin = pin;
}

uint32 mock_get_IfxPort_setPinHigh_call_count(void) { return mock_IfxPort_setPinHigh.call_count; }


typedef struct {
    uint32 call_count;
    Ifx_P *last_port;
    uint8 last_pin;
} mock_IfxPort_setPinLow_t;
static mock_IfxPort_setPinLow_t mock_IfxPort_setPinLow = {0};

__attribute__((weak)) void IfxPort_setPinLow(Ifx_P *port, uint8 pin) {
    mock_IfxPort_setPinLow.call_count++;
    mock_IfxPort_setPinLow.last_port = port;
    mock_IfxPort_setPinLow.last_pin = pin;
}

uint32 mock_get_IfxPort_setPinLow_call_count(void) { return mock_IfxPort_setPinLow.call_count; }

/* Watchdog functions */
typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableCpuWatchdog_t;
static mock_IfxScuWdt_disableCpuWatchdog_t mock_IfxScuWdt_disableCpuWatchdog = {0};

__attribute__((weak)) void IfxScuWdt_disableCpuWatchdog(uint16 password) {
    mock_IfxScuWdt_disableCpuWatchdog.call_count++;
    mock_IfxScuWdt_disableCpuWatchdog.last_password = password;
}

uint32 mock_get_IfxScuWdt_disableCpuWatchdog_call_count(void) { return mock_IfxScuWdt_disableCpuWatchdog.call_count; }


typedef struct { uint32 call_count; uint16 last_password; } mock_IfxScuWdt_disableSafetyWatchdog_t;
static mock_IfxScuWdt_disableSafetyWatchdog_t mock_IfxScuWdt_disableSafetyWatchdog = {0};

__attribute__((weak)) void IfxScuWdt_disableSafetyWatchdog(uint16 password) {
    mock_IfxScuWdt_disableSafetyWatchdog.call_count++;
    mock_IfxScuWdt_disableSafetyWatchdog.last_password = password;
}

uint32 mock_get_IfxScuWdt_disableSafetyWatchdog_call_count(void) { return mock_IfxScuWdt_disableSafetyWatchdog.call_count; }


typedef struct { uint32 call_count; uint16 return_value; } mock_IfxScuWdt_getCpuWatchdogPassword_t;
static mock_IfxScuWdt_getCpuWatchdogPassword_t mock_IfxScuWdt_getCpuWatchdogPassword = {0};

__attribute__((weak)) uint16 IfxScuWdt_getCpuWatchdogPassword(void) {
    mock_IfxScuWdt_getCpuWatchdogPassword.call_count++;
    if (mock_IfxScuWdt_getCpuWatchdogPassword.return_value != 0U) {
        return mock_IfxScuWdt_getCpuWatchdogPassword.return_value;
    }
    return (uint16)0xF00DU;
}

void mock_set_IfxScuWdt_getCpuWatchdogPassword_return(uint16 value) { mock_IfxScuWdt_getCpuWatchdogPassword.return_value = value; }
uint32 mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count(void) { return mock_IfxScuWdt_getCpuWatchdogPassword.call_count; }


typedef struct { uint32 call_count; uint16 return_value; } mock_IfxScuWdt_getSafetyWatchdogPassword_t;
static mock_IfxScuWdt_getSafetyWatchdogPassword_t mock_IfxScuWdt_getSafetyWatchdogPassword = {0};

__attribute__((weak)) uint16 IfxScuWdt_getSafetyWatchdogPassword(void) {
    mock_IfxScuWdt_getSafetyWatchdogPassword.call_count++;
    if (mock_IfxScuWdt_getSafetyWatchdogPassword.return_value != 0U) {
        return mock_IfxScuWdt_getSafetyWatchdogPassword.return_value;
    }
    return (uint16)0xBEEFU;
}

void mock_set_IfxScuWdt_getSafetyWatchdogPassword_return(uint16 value) { mock_IfxScuWdt_getSafetyWatchdogPassword.return_value = value; }
uint32 mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count(void) { return mock_IfxScuWdt_getSafetyWatchdogPassword.call_count; }

/* Reset all mock states */
void mock_reset_all(void) {
    memset(&mock_IfxAsclin_Asc_isrTransmit, 0, sizeof(mock_IfxAsclin_Asc_isrTransmit));
    memset(&mock_IfxAsclin_Asc_initModuleConfig, 0, sizeof(mock_IfxAsclin_Asc_initModuleConfig));
    memset(&mock_IfxAsclin_Asc_initModule, 0, sizeof(mock_IfxAsclin_Asc_initModule));
    memset(&mock_IfxAsclin_Asc_write, 0, sizeof(mock_IfxAsclin_Asc_write));

    memset(&mock_IfxCpu_Irq_getTos, 0, sizeof(mock_IfxCpu_Irq_getTos));
    memset(&mock_IfxCpu_getCoreIndex, 0, sizeof(mock_IfxCpu_getCoreIndex));
    memset(&mock_IfxCpu_enableInterrupts, 0, sizeof(mock_IfxCpu_enableInterrupts));

    memset(&mock_IfxEvadc_Adc_initModuleConfig, 0, sizeof(mock_IfxEvadc_Adc_initModuleConfig));
    memset(&mock_IfxEvadc_Adc_initModule, 0, sizeof(mock_IfxEvadc_Adc_initModule));
    memset(&mock_IfxEvadc_Adc_initGroupConfig, 0, sizeof(mock_IfxEvadc_Adc_initGroupConfig));
    memset(&mock_IfxEvadc_Adc_initGroup, 0, sizeof(mock_IfxEvadc_Adc_initGroup));
    memset(&mock_IfxEvadc_Adc_initChannelConfig, 0, sizeof(mock_IfxEvadc_Adc_initChannelConfig));
    memset(&mock_IfxEvadc_Adc_initChannel, 0, sizeof(mock_IfxEvadc_Adc_initChannel));
    memset(&mock_IfxEvadc_Adc_addToQueue, 0, sizeof(mock_IfxEvadc_Adc_addToQueue));
    memset(&mock_IfxEvadc_Adc_startQueue, 0, sizeof(mock_IfxEvadc_Adc_startQueue));
    memset(&mock_IfxEvadc_Adc_getResult, 0, sizeof(mock_IfxEvadc_Adc_getResult));

    memset(&mock_IfxPort_setPinMode, 0, sizeof(mock_IfxPort_setPinMode));
    memset(&mock_IfxPort_setPinHigh, 0, sizeof(mock_IfxPort_setPinHigh));
    memset(&mock_IfxPort_setPinLow, 0, sizeof(mock_IfxPort_setPinLow));

    memset(&mock_IfxScuWdt_disableCpuWatchdog, 0, sizeof(mock_IfxScuWdt_disableCpuWatchdog));
    memset(&mock_IfxScuWdt_disableSafetyWatchdog, 0, sizeof(mock_IfxScuWdt_disableSafetyWatchdog));
    memset(&mock_IfxScuWdt_getCpuWatchdogPassword, 0, sizeof(mock_IfxScuWdt_getCpuWatchdogPassword));
    memset(&mock_IfxScuWdt_getSafetyWatchdogPassword, 0, sizeof(mock_IfxScuWdt_getSafetyWatchdogPassword));
}
