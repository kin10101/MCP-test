/* IfxStm.h - Auto-generated minimal header */
#ifndef IFXSTM_H
#define IFXSTM_H

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


/* Stm Module Handle */
typedef struct {
    uint32 dummy;
} IfxStm_Timer;

typedef struct {
    uint32 dummy;
} IfxStm_Timer_Config;

typedef enum {
    IfxStm_TimerId_0 = 0,
    IfxStm_TimerId_1 = 1
} IfxStm_TimerId;

void IfxStm_Timer_initModuleConfig(IfxStm_Timer_Config *config, void *module);
boolean IfxStm_Timer_initModule(IfxStm_Timer *timer, IfxStm_Timer_Config *config);
void IfxStm_Timer_start(IfxStm_Timer *timer);
void IfxStm_Timer_stop(IfxStm_Timer *timer);

#endif /* IFXSTM_H */
