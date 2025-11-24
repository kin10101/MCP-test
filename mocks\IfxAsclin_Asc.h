/* IfxAsclin_Asc.h - Auto-generated minimal header */
#ifndef IFXASCLIN_ASC_H
#define IFXASCLIN_ASC_H

/* Basic type definitions */
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

#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif

/* Port structure */
typedef struct {
    uint32 dummy;
} Ifx_P;

/* FIFO structure for buffer management */
typedef struct {
    uint32 dummy;
} Ifx_Fifo;


/* Asclin Module Handle */
typedef struct {
    uint32 dummy;
} IfxAsclin_Asc;

/* Pin Mapping Structure - GENERIC for all peripherals */
typedef struct {
    void *module;
} IfxAsclin_Asc_PinMapping;

/* Pin Sub-Structure (matches iLLD layout) */
typedef struct {
    const IfxAsclin_Asc_PinMapping *pin;  /* Pointer to pin macro */
    uint32 mode;                          /* IfxPort_InputMode or OutputMode */
    uint32 padDriver;                     /* IfxPort_PadDriver */
} IfxAsclin_Asc_Pin;

/* CRITICAL: Pin Structure (complete iLLD-compatible) */
typedef struct {
    IfxAsclin_Asc_Pin cts;      /* Clear to send (optional) */
    IfxAsclin_Asc_Pin rx;       /* Receive pin */
    IfxAsclin_Asc_Pin rts;      /* Request to send (optional) */
    IfxAsclin_Asc_Pin tx;       /* Transmit pin */
    uint32 padDriver;           /* Global pad driver for all pins */
} IfxAsclin_Asc_Pins;

/* Asclin Configuration Structure */
typedef struct {
    struct {
        uint32 baudrate;
    } baudrate;
    
    struct {
        uint32 txPriority;
        uint32 rxPriority;
        uint32 typeOfService;
    } interrupt;
    
    uint8 *txBuffer;
    uint32 txBufferSize;
    uint8 *rxBuffer;
    uint32 rxBufferSize;
    
    IfxAsclin_Asc_Pins *pins;  /* ✅ FIXED: Pointer to typed Pins structure */
} IfxAsclin_Asc_Config;

/* Timeout constant */
#ifndef TIME_INFINITE
#define TIME_INFINITE 0xFFFFFFFF
#endif

/* Port mode enums (if not already defined) */
#ifndef IFXPORT_INPUTMODE_DEFINED
#define IFXPORT_INPUTMODE_DEFINED
typedef enum {
    IfxPort_InputMode_noPull = 0,
    IfxPort_InputMode_pullDown = 1,
    IfxPort_InputMode_pullUp = 2
} IfxPort_InputMode;
#endif

#ifndef IFXPORT_OUTPUTMODE_DEFINED
#define IFXPORT_OUTPUTMODE_DEFINED
typedef enum {
    IfxPort_OutputMode_pushPull = 0x10U,
    IfxPort_OutputMode_openDrain = 0x18U
} IfxPort_OutputMode;
#endif

#ifndef IFXPORT_PADDRIVER_DEFINED
#define IFXPORT_PADDRIVER_DEFINED
typedef enum {
    IfxPort_PadDriver_cmosAutomotiveSpeed1 = 0,
    IfxPort_PadDriver_cmosAutomotiveSpeed2 = 1,
    IfxPort_PadDriver_cmosAutomotiveSpeed3 = 2,
    IfxPort_PadDriver_cmosAutomotiveSpeed4 = 3
} IfxPort_PadDriver;
#endif

/* Generic Communication Functions */
void IfxAsclin_Asc_initModuleConfig(IfxAsclin_Asc_Config *config, void *module);
boolean IfxAsclin_Asc_initModule(IfxAsclin_Asc *handle, IfxAsclin_Asc_Config *config);
void IfxAsclin_Asc_write(IfxAsclin_Asc *handle, uint8 *data, uint32 *count, uint32 timeout);
void IfxAsclin_Asc_read(IfxAsclin_Asc *handle, uint8 *data, uint32 *count, uint32 timeout);
void IfxAsclin_Asc_isrTransmit(IfxAsclin_Asc *handle);
void IfxAsclin_Asc_isrReceive(IfxAsclin_Asc *handle);

#endif /* IFXASCLIN_ASC_H */
