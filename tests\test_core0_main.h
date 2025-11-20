/* Test header for core0_main */
#ifndef TEST_CORE0_MAIN_H
#define TEST_CORE0_MAIN_H

#include "unity.h"
#include "mocks.h"

void test_core0_main_invokes_startup_sequence_and_blink_loop(void);
void test_core0_main_watchdog_password_zero(void);
void test_core0_main_called_twice_accumulates_blinks(void);

#endif
