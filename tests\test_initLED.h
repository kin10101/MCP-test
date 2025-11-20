/* Test header for initLED */
#ifndef TEST_INITLED_H
#define TEST_INITLED_H

#include "unity.h"
#include "mocks.h"

void test_initLED_configures_pushpull_and_sets_high(void);
void test_initLED_called_twice_updates_counts_and_params(void);
void test_initLED_call_order_mode_before_high(void);

#endif
