/* IfxPort.h - Auto-generated minimal header */
#ifndef IFXPORT_H
#define IFXPORT_H

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


/* Port Mode Enums */
typedef enum {
    IfxPort_InputMode_noPull = 0,
    IfxPort_InputMode_pullDown = 1,
    IfxPort_InputMode_pullUp = 2
} IfxPort_InputMode;

typedef enum {
    IfxPort_OutputMode_pushPull = 0,
    IfxPort_OutputMode_openDrain = 1
} IfxPort_OutputMode;

typedef enum {
    IfxPort_PadDriver_cmosAutomotiveSpeed1 = 0,
    IfxPort_PadDriver_cmosAutomotiveSpeed2 = 1,
    IfxPort_PadDriver_cmosAutomotiveSpeed3 = 2,
    IfxPort_PadDriver_cmosAutomotiveSpeed4 = 3
} IfxPort_PadDriver;

void IfxPort_setPinMode(Ifx_P *port, uint8 pin, uint8 mode);
void IfxPort_setPinState(Ifx_P *port, uint8 pin, uint8 state);
uint8 IfxPort_getPinState(Ifx_P *port, uint8 pin);

#endif /* IFXPORT_H */
