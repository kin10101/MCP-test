/* IfxEvadc_Adc.h - Auto-generated minimal header */
#ifndef IFXEVADC_ADC_H
#define IFXEVADC_ADC_H

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


/* Evadc_Adc Module Handle */
typedef struct {
    uint32 dummy;
} IfxEvadc_Adc;

typedef struct {
    uint32 dummy;
} IfxEvadc_Adc_Config;

void IfxEvadc_Adc_initModuleConfig(IfxEvadc_Adc_Config *config, void *module);
boolean IfxEvadc_Adc_initModule(IfxEvadc_Adc *handle, IfxEvadc_Adc_Config *config);
uint32 IfxEvadc_Adc_getResult(IfxEvadc_Adc *handle, uint32 channel);

#endif /* IFXEVADC_ADC_H */
