/* Test header for uart_send_string */
#ifndef TEST_UART_SEND_STRING_H
#define TEST_UART_SEND_STRING_H

#include "unity.h"
#include "mocks.h"

void test_uart_send_string_calls_write_with_correct_len(void);
void test_uart_send_string_empty_string_len_zero(void);
void test_uart_send_string_null_pointer_no_write(void);

#endif
