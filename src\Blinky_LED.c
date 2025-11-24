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
    /* Configure LED pin as push-pull output and set to high (LED off if low-active) */
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinHigh(LED);
}

void blinkLED(void)
{
    /* Toggle LED state */
    IfxPort_togglePin(LED);

    /* Wait for WAIT_TIME milliseconds */
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}
