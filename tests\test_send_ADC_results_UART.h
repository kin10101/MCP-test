/* Test header for send_ADC_results_UART */
#ifndef TEST_SEND_ADC_RESULTS_UART_H
#define TEST_SEND_ADC_RESULTS_UART_H

#include "unity.h"
#include "mocks.h"

void test_send_ADC_results_UART_formats_and_sends_all(void);
void test_send_ADC_results_UART_zero_results_boundary(void);
void test_send_ADC_results_UART_order_and_separator(void);

#endif
