/* Test header for core0_main */
#ifndef TEST_CORE0_MAIN_H
#define TEST_CORE0_MAIN_H

#include "unity.h"
#include "mocks.h"

void test_core0_main_disables_watchdogs_and_enables_interrupts(void);
void test_core0_main_emits_and_waits_for_sync_event(void);
void test_core0_main_initializes_and_blinks_led_three_times(void);

#endif
