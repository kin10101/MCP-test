#ifndef MOCKS_H
#define MOCKS_H

#include "mock_config.h"

/* Externs for unique ports (auto-detected) */
extern Ifx_P MODULE_P00;

/* BSP resource extern (from Bsp.h usage) */
extern Ifx_STM *BSP_DEFAULT_TIMER;

/* iLLD/BSP function declarations (mocked) */
void IfxPort_setPinModeOutput(Ifx_P *port, uint8 pin, IfxPort_OutputMode mode, IfxPort_OutputIdx idx);
void IfxPort_setPinHigh(Ifx_P *port, uint8 pin);
void IfxPort_togglePin(Ifx_P *port, uint8 pin);

uint32 IfxStm_getTicksFromMilliseconds(Ifx_STM *stm, uint32 ms);
void waitTime(uint32 ticks);

void IfxCpu_enableInterrupts(void);

uint16 IfxScuWdt_getCpuWatchdogPassword(void);
void IfxScuWdt_disableCpuWatchdog(uint16 password);
uint16 IfxScuWdt_getSafetyWatchdogPassword(void);
void IfxScuWdt_disableSafetyWatchdog(uint16 password);

void IfxCpu_emitEvent(IfxCpu_syncEvent *event);
void IfxCpu_waitEvent(IfxCpu_syncEvent *event, uint32 count);

/* Helper functions for unit tests */
uint32 mock_get_IfxPort_setPinModeOutput_call_count(void);
uint32 mock_get_IfxPort_setPinHigh_call_count(void);
uint32 mock_get_IfxPort_togglePin_call_count(void);

uint32 mock_get_IfxStm_getTicksFromMilliseconds_call_count(void);
void mock_set_IfxStm_getTicksFromMilliseconds_return(uint32 value);

uint32 mock_get_waitTime_call_count(void);

uint32 mock_get_IfxCpu_enableInterrupts_call_count(void);

uint32 mock_get_IfxScuWdt_getCpuWatchdogPassword_call_count(void);
void mock_set_IfxScuWdt_getCpuWatchdogPassword_return(uint16 value);
uint32 mock_get_IfxScuWdt_disableCpuWatchdog_call_count(void);

uint32 mock_get_IfxScuWdt_getSafetyWatchdogPassword_call_count(void);
void mock_set_IfxScuWdt_getSafetyWatchdogPassword_return(uint16 value);
uint32 mock_get_IfxScuWdt_disableSafetyWatchdog_call_count(void);

uint32 mock_get_IfxCpu_emitEvent_call_count(void);
uint32 mock_get_IfxCpu_waitEvent_call_count(void);

void mock_reset_all(void);

#endif /* MOCKS_H */
