/* Test header for blinkLED */
#ifndef TEST_BLINKLED_H
#define TEST_BLINKLED_H

#include "unity.h"
#include "mocks.h"

void test_blinkLED_toggles_and_waits_500ms(void);
void test_blinkLED_multiple_calls_with_variable_ticks(void);
void test_blinkLED_zero_ticks_still_calls_wait(void);

#endif
