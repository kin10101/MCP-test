#ifndef MOCKS_H
#define MOCKS_H

#include "mock_config.h"

/* Port externs (auto-detected) */
extern Ifx_P MODULE_P00;

/* EVADC module extern to satisfy init call */
extern Ifx_EVADC MODULE_EVADC;

/* ASCLIN pin macros used by project */
extern const IfxAsclin_Asc_PinMapping IfxAsclin0_RXA_P14_1_IN;
extern const IfxAsclin_Asc_PinMapping IfxAsclin0_TX_P14_0_OUT;

/* Global variables from project (defined in mocks.c) */
extern IfxCpu_syncEvent g_cpuSyncEvent;
extern IfxEvadc_Adc g_evadc;
extern IfxEvadc_Adc_Group g_adcGroup;
extern IfxEvadc_Adc_Channel g_adcChannel[3];
extern uint8 g_grp8channels[3];
extern Ifx_EVADC_G_RES g_results[3];
extern IfxAsclin_Asc g_asc;
extern uint8 g_ascTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8U];

/* Mocked function declarations */
__attribute__((weak)) void IfxAsclin_Asc_isrTransmit(IfxAsclin_Asc *asc);
__attribute__((weak)) void IfxAsclin_Asc_initModuleConfig(IfxAsclin_Asc_Config *cfg, void *module);
__attribute__((weak)) boolean IfxAsclin_Asc_initModule(IfxAsclin_Asc *asc, IfxAsclin_Asc_Config *cfg);
__attribute__((weak)) uint32 IfxAsclin_Asc_write(IfxAsclin_Asc *asc, uint8 *data, uint32 *len, uint32 timeout);

__attribute__((weak)) uint32 IfxCpu_Irq_getTos(uint32 coreIndex);
__attribute__((weak)) uint32 IfxCpu_getCoreIndex(void);
__attribute__((weak)) void IfxCpu_enableInterrupts(void);

__attribute__((weak)) void IfxEvadc_Adc_initModuleConfig(IfxEvadc_Adc_Config *cfg, Ifx_EVADC *module);
__attribute__((weak)) boolean IfxEvadc_Adc_initModule(IfxEvadc_Adc *adc, IfxEvadc_Adc_Config *cfg);
__attribute__((weak)) void IfxEvadc_Adc_initGroupConfig(IfxEvadc_Adc_GroupConfig *cfg, IfxEvadc_Adc *adc);
__attribute__((weak)) boolean IfxEvadc_Adc_initGroup(IfxEvadc_Adc_Group *grp, IfxEvadc_Adc_GroupConfig *cfg);
__attribute__((weak)) void IfxEvadc_Adc_initChannelConfig(IfxEvadc_Adc_ChannelConfig *cfg, IfxEvadc_Adc_Group *grp);
__attribute__((weak)) boolean IfxEvadc_Adc_initChannel(IfxEvadc_Adc_Channel *ch, IfxEvadc_Adc_ChannelConfig *cfg);
__attribute__((weak)) boolean IfxEvadc_Adc_addToQueue(IfxEvadc_Adc_Channel *ch, uint32 requestSource, uint32 refill);
__attribute__((weak)) boolean IfxEvadc_Adc_startQueue(IfxEvadc_Adc_Group *grp, uint32 requestSource);
__attribute__((weak)) Ifx_EVADC_G_RES IfxEvadc_Adc_getResult(IfxEvadc_Adc_Channel *ch);

__attribute__((weak)) void IfxPort_setPinMode(Ifx_P *port, uint8 pin, uint8 mode);
__attribute__((weak)) void IfxPort_setPinHigh(Ifx_P *port, uint8 pin);
__attribute__((weak)) void IfxPort_setPinLow(Ifx_P *port, uint8 pin);

__attribute__((weak)) void IfxScuWdt_disableCpuWatchdog(uint16 password);
__attribute__((weak)) void IfxScuWdt_disableSafetyWatchdog(uint16 password);
__attribute__((weak)) uint16 IfxScuWdt_getCpuWatchdogPassword(void);
__attribute__((weak)) uint16 IfxScuWdt_getSafetyWatchdogPassword(void);

/* Helpers: call counters and return setters */
uint32 mock_get_IfxAsclin_Asc_isrTransmit_call_count(void);
uint32 mock_get_IfxAsclin_Asc_initModuleConfig_call_count(void);
uint32 mock_get_IfxAsclin_Asc_initModule_call_count(void);
uint32 mock_get_IfxAsclin_Asc_write_call_count(void);
void   mock_set_IfxAsclin_Asc_initModule_return(boolean value);
uint32 mock_get_IfxCpu_Irq_getTos_call_count(void);
uint32 mock_get_IfxCpu_getCoreIndex_call_count(void);
uint32 mock_get_IfxCpu_enableInterrupts_call_count(void);
void   mock_set_IfxCpu_Irq_getTos_return(uint32 value);
void   mock_set_IfxCpu_getCoreIndex_return(uint32 value);

uint32 mock_get_IfxEvadc_Adc_initModuleConfig_call_count(void);
uint32 mock_get_IfxEvadc_Adc_initModule_call_count(void);
uint32 mock_get_IfxEvadc_Adc_initGroupConfig_call_count(void);
uint32 mock_get_IfxEvadc_Adc_initGroup_call_count(void);
uint32 mock_get_IfxEvadc_Adc_initChannelConfig_call_count(void);
uint32 mock_get_IfxEvadc_Adc_initChannel_call_count(void);
uint32 mock_get_IfxEvadc_Adc_addToQueue_call_count(void);
uint32 mock_get_IfxEvadc_Adc_startQueue_call_count(void);
uint32 mock_get_IfxEvadc_Adc_getResult_call_count(void);
void   mock_set_IfxEvadc_Adc_initModule_return(boolean value);
void   mock_set_IfxEvadc_Adc_initGroup_return(boolean value);
void   mock_set_IfxEvadc_Adc_initChannel_return(boolean value);
void   mock_set_IfxEvadc_Adc_addToQueue_return(boolean value);
void   mock_set_IfxEvadc_Adc_startQueue_return(boolean value);
void   mock_set_IfxEvadc_Adc_getResult_return(Ifx_EVADC_G_RES value);

uint32 mock_get_IfxPort_setPinMode_call_count(void);
uint32 mock_get_IfxPort_setPinHigh_call_count(void);
uint32 mock_get_IfxPort_setPinLow_call_count(void);

uint32 mock_get_IfxScuWdt_disableCpuWatchdog_call_count(void);
uint32 mock_get_IfxScuWdt_disableSafetyWatchdog_call_count(void);
uint32 mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count(void);
uint32 mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count(void);
void   mock_set_IfxScuWdt_getCpuWatchdogPassword_return(uint16 value);
void   mock_set_IfxScuWdt_getSafetyWatchdogPassword_return(uint16 value);

void mock_reset_all(void);

#endif /* MOCKS_H */
