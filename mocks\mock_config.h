#ifndef MOCK_CONFIG_H
#define MOCK_CONFIG_H

/* Basic types (Infineon Ifx_Types equivalents) */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef signed long long sint64;
typedef unsigned char boolean;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define IFX_ALIGN(n) __attribute__((aligned(n)))
#define NULL_PTR ((void*)0)

/* Common utility types used by project */
typedef unsigned int IfxCpu_syncEvent;
typedef uint32 Ifx_SizeT;

/* TIME_INFINITE for blocking operations */
#ifndef TIME_INFINITE
#define TIME_INFINITE 0xFFFFFFFFU
#endif

/* Minimal hardware placeholder structs */
typedef struct { uint32 dummy; } Ifx_P;
typedef struct { uint32 dummy; } Ifx_STM;

typedef struct { uint32 dummy; } Ifx_EVADC;

typedef struct { uint32 dummy; } Ifx_Fifo;

/* ASCLIN ASC minimal types */
typedef struct {
    uint32 dummy;
} IfxAsclin_Asc;

typedef struct IfxAsclin_Asc_PinMapping {
    void *module; /* Placeholder for underlying module pointer */
} IfxAsclin_Asc_PinMapping;

typedef struct {
    struct { uint32 baudrate; } baudrate;
    struct { uint8 txPriority; uint32 typeOfService; } interrupt;
    uint8 *txBuffer;
    uint32 txBufferSize;
    const void *pins; /* Treat pins as opaque in tests */
} IfxAsclin_Asc_Config;

/* EVADC minimal types */
typedef struct {
    uint32 dummy;
} IfxEvadc_Adc;

typedef struct {
    uint32 dummy;
} IfxEvadc_Adc_Config;

typedef struct {
    uint32 groupId;
    uint32 master;
    struct { boolean requestSlotQueue0Enabled; } arbiter;
    struct { struct { uint32 gatingMode; } triggerConfig; } queueRequest[2];
} IfxEvadc_Adc_GroupConfig;

typedef struct {
    uint32 dummy;
} IfxEvadc_Adc_Group;

typedef struct {
    uint8 channelId;
    uint8 resultRegister;
} IfxEvadc_Adc_ChannelConfig;

typedef struct {
    uint8 channelId;
} IfxEvadc_Adc_Channel;

/* EVADC result structure used in code (r.B.VF and r.B.RESULT) */
typedef struct {
    struct {
        uint8 VF;
        uint32 RESULT;
    } B;
} Ifx_EVADC_G_RES;

/* Port mode constant used in project */
#ifndef IfxPort_Mode_outputPushPullGeneral
#define IfxPort_Mode_outputPushPullGeneral ((uint8)0x80U)
#endif

/* ASCLIN pins config literals use these constants; define minimal values */
#ifndef IfxPort_InputMode_pullUp
#define IfxPort_InputMode_pullUp ((uint8)1U)
#endif
#ifndef IfxPort_OutputMode_pushPull
#define IfxPort_OutputMode_pushPull ((uint8)1U)
#endif
#ifndef IfxPort_PadDriver_cmosAutomotiveSpeed1
#define IfxPort_PadDriver_cmosAutomotiveSpeed1 ((uint8)1U)
#endif

/* EVADC queue/gating constants */
#ifndef IfxEvadc_RequestSource_queue0
#define IfxEvadc_RequestSource_queue0 ((uint32)0U)
#endif
#ifndef IFXEVADC_QUEUE_REFILL
#define IFXEVADC_QUEUE_REFILL ((uint32)1U)
#endif
#ifndef IfxEvadc_GatingMode_always
#define IfxEvadc_GatingMode_always ((uint32)0U)
#endif

/* Fallback for ASC_TX_BUFFER_SIZE if not included from project headers */
#ifndef ASC_TX_BUFFER_SIZE
#define ASC_TX_BUFFER_SIZE (1024U)
#endif

#endif /* MOCK_CONFIG_H */
