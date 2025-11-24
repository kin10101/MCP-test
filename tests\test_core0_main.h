/* Test header for core0_main */
#ifndef TEST_CORE0_MAIN_H
#define TEST_CORE0_MAIN_H

#include "unity.h"
#include "mocks.h"

void test_core0_main_initialization_and_watchdog_handling(void);
void test_core0_main_emits_and_waits_cpu_sync_event(void);
void test_core0_main_calls_blinkLED_expected_times(void);

#endif
