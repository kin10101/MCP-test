/* Blinky_LED.c */
#include "Blinky_LED.h"

/* iLLD Libraries - extracted from Dependencies */
#include "Bsp.h"
#include "IfxCpu.h"
#include "IfxPort.h"
#include "IfxScuWdt.h"
#include "IfxStm.h"
#include "Ifx_Types.h"

/* Macros - from Defined Constants */
#define LED &MODULE_P00,5
#define WAIT_TIME 500

/* Global Variables - none defined */

/* Function Implementations - from Functions[] */
void initLED(void)
{
    /* Configure LED pin as push-pull output and set it high (LED off if low-level active) */
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinHigh(LED);
}

void blinkLED(void)
{
    /* Toggle the LED pin */
    IfxPort_togglePin(LED);

    /* Wait for WAIT_TIME milliseconds */
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}
