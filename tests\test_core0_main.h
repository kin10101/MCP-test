/* Test header for core0_main */
#ifndef TEST_CORE0_MAIN_H
#define TEST_CORE0_MAIN_H

#include "unity.h"
#include "mocks.h"

void test_core0_main_happy_path_calls_expected_sequences(void);
void test_core0_main_boundary_zero_loop_limit_runs_no_blinks(void);
void test_core0_main_error_password_zero_still_disables_watchdogs(void);

#endif
