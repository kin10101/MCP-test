/* Test header for initLED */
#ifndef TEST_INITLED_H
#define TEST_INITLED_H

#include "unity.h"
#include "mocks.h"

void test_initLED_configures_push_pull_output(void);
void test_initLED_sets_pin_high_off_state(void);
void test_initLED_multiple_calls_increment_counts(void);

#endif
