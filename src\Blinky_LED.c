/* Blinky_LED.c */
#include "Blinky_LED.h"

/* iLLD Libraries - from Dependencies[].Origin */
#include "IfxPort.h"
#include "IfxStm.h"
#include "Bsp.h"

/* Macros - from Defined Variables[] where Type == "Macro" */
#define LED &MODULE_P00,5
#define WAIT_TIME 500

/* Global Variables - from Defined Variables[] where Type != "Macro" */

/* Function Implementations - from Functions[] */
void initLED(void)
{
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinHigh(LED);
}

void blinkLED(void)
{
    IfxPort_togglePin(LED);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}
