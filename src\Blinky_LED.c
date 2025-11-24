/* Blinky_LED.c */
#include "project.h"

/* iLLD Libraries - from Dependencies[].Library */
#include "IfxPort.h"
#include "IfxScuWdt.h"
#include "Ifx_Types.h"

/* Macros - from Defined Variables[] where Type == "Macro" */
/* (No macros defined in JSON) */

/* Global Variables - from Defined Variables[] where Type != "Macro" */
/* (No global variables defined in JSON) */

/* Function Implementations - from Functions[] */
void initLED(void)
{
    uint16 password = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_disableCpuWatchdog(password);

    /* Configure P00.5 as push-pull output and set inactive state (active-low LED → drive high) */
    IfxPort_setPinMode(&MODULE_P00, 5, IfxPort_Mode_outputPushPull);
    IfxPort_setPinHigh(&MODULE_P00, 5);

    IfxScuWdt_enableCpuWatchdog(password);
}

void blinkLED(unsigned int ms)
{
    /* Active-low LED: drive low to turn ON for 'ms' milliseconds */
    IfxPort_setPinLow(&MODULE_P00, 5);
    for (unsigned int i = 0; i < ms; ++i)
    {
        volatile unsigned int j;
        for (j = 0; j < 10000U; ++j)
        {
            /* Busy-wait loop */
        }
    }

    /* Inter-symbol spacing: drive high (LED OFF) for 'ms' milliseconds */
    IfxPort_setPinHigh(&MODULE_P00, 5);
    for (unsigned int i = 0; i < ms; ++i)
    {
        volatile unsigned int j;
        for (j = 0; j < 10000U; ++j)
        {
            /* Busy-wait loop */
        }
    }
}

void blinkChar(char c)
{
    /* Use local buffer as specified */
    char msgBuffer[128];
    const char *pattern = 0;

    /* Normalize to uppercase without ctype.h */
    if ((c >= 'a') && (c <= 'z'))
    {
        c = (char)(c - 'a' + 'A');
    }

    /* International Morse Code patterns for A–Z and 0–9 */
    switch (c)
    {
        case 'A': pattern = ".-"; break;
        case 'B': pattern = "-..."; break;
        case 'C': pattern = "-.-."; break;
        case 'D': pattern = "-.."; break;
        case 'E': pattern = "."; break;
        case 'F': pattern = "..-."; break;
        case 'G': pattern = "--."; break;
        case 'H': pattern = "...."; break;
        case 'I': pattern = ".."; break;
        case 'J': pattern = ".---"; break;
        case 'K': pattern = "-.-"; break;
        case 'L': pattern = ".-.."; break;
        case 'M': pattern = "--"; break;
        case 'N': pattern = "-."; break;
        case 'O': pattern = "---"; break;
        case 'P': pattern = ".--."; break;
        case 'Q': pattern = "--.-"; break;
        case 'R': pattern = ".-."; break;
        case 'S': pattern = "..."; break;
        case 'T': pattern = "-"; break;
        case 'U': pattern = "..-"; break;
        case 'V': pattern = "...-"; break;
        case 'W': pattern = ".--"; break;
        case 'X': pattern = "-..-"; break;
        case 'Y': pattern = "-.--"; break;
        case 'Z': pattern = "--.."; break;
        case '0': pattern = "-----"; break;
        case '1': pattern = ".----"; break;
        case '2': pattern = "..---"; break;
        case '3': pattern = "...--"; break;
        case '4': pattern = "....-"; break;
        case '5': pattern = "....."; break;
        case '6': pattern = "-...."; break;
        case '7': pattern = "--..."; break;
        case '8': pattern = "---.."; break;
        case '9': pattern = "----."; break;
        default:
            pattern = 0;
            break;
    }

    /* Copy pattern to local buffer (as required) and blink */
    if (pattern != 0)
    {
        unsigned int baseMs = 500U; /* Base unit (ms) */
        unsigned int idx = 0U;
        while ((pattern[idx] != '\0') && (idx < (sizeof(msgBuffer) - 1U)))
        {
            msgBuffer[idx] = pattern[idx];
            ++idx;
        }
        msgBuffer[idx] = '\0';

        /* Emit Morse: dot = 1 unit, dash = 3 units; inter-symbol handled inside blinkLED */
        for (unsigned int i = 0U; msgBuffer[i] != '\0'; ++i)
        {
            if (msgBuffer[i] == '.')
            {
                blinkLED(baseMs);
            }
            else if (msgBuffer[i] == '-')
            {
                blinkLED(baseMs * 3U);
            }
            else
            {
                /* Ignore unexpected characters in pattern */
            }
        }
    }
}

void blinkMessage(const char *msg)
{
    /* Use local buffer for safe, bounded processing */
    char msgBuffer[128];
    unsigned int baseMs = 500U; /* Base unit (ms) */

    /* Bounded copy and normalization to uppercase */
    unsigned int i = 0U;
    while ((msg != 0) && (msg[i] != '\0') && (i < (sizeof(msgBuffer) - 1U)))
    {
        char c = msg[i];
        if ((c >= 'a') && (c <= 'z'))
        {
            c = (char)(c - 'a' + 'A');
        }
        msgBuffer[i] = c;
        ++i;
    }
    msgBuffer[i] = '\0';

    /* Iterate characters and emit Morse */
    for (unsigned int k = 0U; msgBuffer[k] != '\0'; ++k)
    {
        char c = msgBuffer[k];
        if (c == ' ')
        {
            /* Word spacing: ensure LED OFF, wait 7 units */
            IfxPort_setPinHigh(&MODULE_P00, 5);
            for (unsigned int w = 0U; w < (baseMs * 7U); ++w)
            {
                volatile unsigned int j;
                for (j = 0U; j < 10000U; ++j)
                {
                    /* Busy-wait */
                }
            }
        }
        else
        {
            blinkChar(c);

            /* Letter spacing: ensure LED OFF, wait 3 units */
            IfxPort_setPinHigh(&MODULE_P00, 5);
            for (unsigned int l = 0U; l < (baseMs * 3U); ++l)
            {
                volatile unsigned int j;
                for (j = 0U; j < 10000U; ++j)
                {
                    /* Busy-wait */
                }
            }
        }
    }
}
