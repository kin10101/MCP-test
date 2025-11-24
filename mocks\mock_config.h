#ifndef MOCK_CONFIG_H
#define MOCK_CONFIG_H

/* Basic types (subset of Ifx_Types.h for testing) */
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

/* Alignment macro used by project code */
#ifndef IFX_ALIGN
#define IFX_ALIGN(n) __attribute__((aligned(n)))
#endif

/* Minimal structures for ports and STM timer */
typedef struct { uint32 dummy; } Ifx_P;
typedef struct { uint32 dummy; } Ifx_STM;
typedef unsigned int IfxCpu_syncEvent;

/* Minimal enums/constants required by project code */
typedef enum {
    IfxPort_OutputMode_pushPull = 0x10U
} IfxPort_OutputMode;

typedef enum {
    IfxPort_OutputIdx_general = 0U
} IfxPort_OutputIdx;

#endif /* MOCK_CONFIG_H */
