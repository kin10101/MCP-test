#ifndef MOCK_CONFIG_H
#define MOCK_CONFIG_H

/* Basic Infineon types (minimal set for unit testing) */
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

/* Alignment macro used by some project globals */
#ifndef IFX_ALIGN
#define IFX_ALIGN(n) __attribute__((aligned(n)))
#endif

/* Minimal port/timer structures available for tests */
typedef struct { uint32 dummy; } Ifx_P;
typedef struct { uint32 dummy; } Ifx_STM;
typedef unsigned int IfxCpu_syncEvent;

/* Minimal IfxPort enums used by project code */
typedef enum {
    IfxPort_Mode_inputNoPullDevice = 0x00U,
    IfxPort_Mode_outputPushPullGeneral = 0x80U
} IfxPort_Mode;

typedef enum {
    IfxPort_State_low = 0,
    IfxPort_State_high = 1
} IfxPort_State;

typedef enum {
    IfxPort_OutputMode_pushPull = 0x10U
} IfxPort_OutputMode;

typedef enum {
    IfxPort_OutputIdx_general = 0
} IfxPort_OutputIdx;

#endif /* MOCK_CONFIG_H */
