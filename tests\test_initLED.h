/* Test header for initLED */
#ifndef TEST_INITLED_H
#define TEST_INITLED_H

#include "unity.h"
#include "mocks.h"

void test_initLED_configures_push_pull_and_sets_high(void);
void test_initLED_called_twice_accumulates_calls(void);
void test_initLED_pin_and_mode_values_are_correct_each_call(void);

#endif
