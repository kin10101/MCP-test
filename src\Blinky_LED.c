/* Blinky_LED.c */
#include "Blinky_LED.h"

/* iLLD Libraries - from Dependencies[].Origin */
#include "IfxPort.h"
#include "IfxStm.h"
#include "Bsp.h"

/* Macros - from DefinedConstants */
#define LED &MODULE_P00,5
#define WAIT_TIME 500

/* Global Variables - none defined */

/* Function Implementations - from Functions[] */
void initLED(void)
{
    /* Configure LED pin as push-pull output and set high (LED off if low-level active) */
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinHigh(LED);
}

void blinkLED(void)
{
    /* Toggle LED and wait for WAIT_TIME milliseconds */
    IfxPort_togglePin(LED);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}
