/* Cpu0_Main.c */
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Blinky_LED.h"

/* Global Variables - from Defined Variables[] */
IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

/* Main Function - from Functions[] where name contains "main" */
void core0_main(void) {
    /* Standard initialization from Dependencies[] */
    IfxCpu_enableInterrupts();

    /* Disable watchdogs */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* CPU synchronization */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    /* Initialize LED */
    initLED();

    /* Infinite loop */
    while(1) {
        blinkLED();
    }
}
