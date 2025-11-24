/* Cpu0_Main.c */
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxPort.h"
#include "IfxAsclin_Asc.h"
#include "IfxEvadc_Adc.h"
#include "stdio.h"
#include "string.h"
#include "Blinky_LED.h"

/* Defined Constants */
#define GROUPID_8                    IfxEvadc_GroupId_8
#define CHANNELS_NUM                 3
#define AN39_CHID                    7
#define AN38_CHID                    6
#define AN37_CHID                    5
#define SERIAL_BAUDRATE             115200
#define INTPRIO_ASCLIN0_TX           19
#define ASC_TX_BUFFER_SIZE         1024
#define SERIAL_PIN_RX               IfxAsclin0_RXA_P14_1_IN
#define SERIAL_PIN_TX               IfxAsclin0_TX_P14_0_OUT

/* Global Variables - from Defined Variables[] */
IfxCpu_syncEvent g_cpuSyncEvent = 0;
IfxEvadc_Adc g_evadc;
IfxEvadc_Adc_Group g_adcGroup;
IfxEvadc_Adc_Channel g_adcChannel[CHANNELS_NUM];
const uint8 g_grp8channels[CHANNELS_NUM] = {AN39_CHID, AN38_CHID, AN37_CHID};
Ifx_EVADC_G_RES g_results[CHANNELS_NUM];
IfxAsclin_Asc g_asc;
uint8 g_ascTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

/* Function Implementations - from Functions[] */
IFX_INTERRUPT(asclin0_Tx_ISR, 0, INTPRIO_ASCLIN0_TX);
void asclin0_Tx_ISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_asc);
}

void init_UART(void)
{
    IfxAsclin_Asc_Config cfg;
    IfxAsclin_Asc_initModuleConfig(&cfg, SERIAL_PIN_TX.module);

    cfg.baudrate.baudrate = SERIAL_BAUDRATE;
    cfg.interrupt.txPriority = INTPRIO_ASCLIN0_TX;
    cfg.interrupt.typeOfService = IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());

    cfg.txBuffer = g_ascTxBuffer;
    cfg.txBufferSize = ASC_TX_BUFFER_SIZE;

    const IfxAsclin_Asc_Pins pins = {
        NULL_PTR,                         /* cts pin */
        IfxPort_InputMode_pullUp,         /* cts mode */
        &SERIAL_PIN_RX,                   /* rx pin */
        IfxPort_InputMode_pullUp,         /* rx mode */
        NULL_PTR,                         /* rts pin */
        IfxPort_OutputMode_pushPull,      /* rts mode */
        &SERIAL_PIN_TX,                   /* tx pin */
        IfxPort_OutputMode_pushPull,      /* tx mode */
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    cfg.pins = &pins;

    IfxAsclin_Asc_initModule(&g_asc, &cfg);
}

void uart_send_string(const char* msg)
{
    Ifx_SizeT len = (Ifx_SizeT)strlen(msg);
    IfxAsclin_Asc_write(&g_asc, (uint8*)msg, &len, TIME_INFINITE);
}

void init_EVADC(void)
{
    IfxEvadc_Adc_Config moduleCfg;
    IfxEvadc_Adc_initModuleConfig(&moduleCfg, &MODULE_EVADC);
    IfxEvadc_Adc_initModule(&g_evadc, &moduleCfg);

    IfxEvadc_Adc_GroupConfig groupCfg;
    IfxEvadc_Adc_initGroupConfig(&groupCfg, &g_evadc);
    groupCfg.groupId = GROUPID_8;
    groupCfg.master = GROUPID_8;
    groupCfg.arbiter.requestSlotQueue0Enabled = TRUE;
    groupCfg.queueRequest[0].triggerConfig.gatingMode = IfxEvadc_GatingMode_always;
    IfxEvadc_Adc_initGroup(&g_adcGroup, &groupCfg);

    for (uint8 i = 0; i < CHANNELS_NUM; i++)
    {
        IfxEvadc_Adc_ChannelConfig chCfg;
        IfxEvadc_Adc_initChannelConfig(&chCfg, &g_adcGroup);
        chCfg.channelId = g_grp8channels[i];
        chCfg.resultRegister = g_grp8channels[i];
        IfxEvadc_Adc_initChannel(&g_adcChannel[i], &chCfg);
        IfxEvadc_Adc_addToQueue(&g_adcChannel[i], IfxEvadc_RequestSource_queue0, IFXEVADC_QUEUE_REFILL);
    }

    IfxEvadc_Adc_startQueue(&g_adcGroup, IfxEvadc_RequestSource_queue0);
}

void readEVADC(void)
{
    for (uint8 i = 0; i < CHANNELS_NUM; i++)
    {
        Ifx_EVADC_G_RES r;
        do
        {
            r = IfxEvadc_Adc_getResult(&g_adcChannel[i]);
        } while (r.B.VF == 0);
        g_results[i] = r;
    }
}

void send_ADC_results_UART(void)
{
    char buf[64];
    for (uint8 i = 0; i < CHANNELS_NUM; i++)
    {
        (void)sprintf(buf, "CH%u = %u\r\n", (unsigned int)i, (unsigned int)g_results[i].B.RESULT);
        uart_send_string(buf);
    }
    uart_send_string("--------------------\r\n");
}

void process_light_level(void)
{
    unsigned int raw = (unsigned int)g_results[0].B.RESULT;
    float normalized = (raw - 2740.0f) * (100.0f / (4095.0f - 2740.0f));
    if (normalized < 1) normalized = 1;
    if (normalized > 100) normalized = 100;

    char msg[64];
    (void)sprintf(msg, "Normalized light = %.1f\r\n", normalized);
    uart_send_string(msg);

    if (normalized < 40)
    {
        uart_send_string("Low light\r\n");
        IfxPort_setPinLow(&MODULE_P00, 5);  /* LED ON */
    }
    else if (normalized <= 60)
    {
        uart_send_string("Medium light\r\n");
        IfxPort_setPinHigh(&MODULE_P00, 5); /* LED OFF */
    }
    else
    {
        uart_send_string("Bright light\r\n");
        IfxPort_setPinHigh(&MODULE_P00, 5); /* LED OFF */
    }
    uart_send_string("--------------------\r\n");
}

/* Main Function - from Functions[] where name contains "main" */
void core0_main(void)
{
    /* Standard initialization from Dependencies[] */
    IfxCpu_enableInterrupts();

    /* Disable watchdogs */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* CPU synchronization */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    /* Initialize peripherals */
    init_UART();
    init_EVADC();

    /* Configure LED port pin: output push-pull, set high (LED OFF) */
    IfxPort_setPinMode(&MODULE_P00, 5, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinHigh(&MODULE_P00, 5);

    /* Infinite loop */
    while (1)
    {
        readEVADC();
        uart_send_string("i love infineon <3 \r\n");
        send_ADC_results_UART();
        process_light_level();

        for (volatile uint32 d = 0; d < 5000000; d++) { /* busy wait */ }
    }
}
