#ifndef MOCK_CONFIG_H
#define MOCK_CONFIG_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef signed long long sint64;
typedef unsigned char boolean;
#define TRUE 1
#define FALSE 0

#define IFX_ALIGN(n) __attribute__((aligned(n)))

/* Minimal structures available in tests */
typedef struct { uint32 dummy; } Ifx_P;
typedef struct { uint32 dummy; } Ifx_STM;
typedef unsigned int IfxCpu_syncEvent;

#endif
