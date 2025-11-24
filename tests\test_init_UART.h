/* Test header for init_UART */
#ifndef TEST_INIT_UART_H
#define TEST_INIT_UART_H

#include "unity.h"
#include "mocks.h"

void test_init_UART_sets_baudrate_and_priorities(void);
void test_init_UART_sets_tx_buffer_and_size(void);
void test_init_UART_assigns_pins_pointer(void);

#endif
