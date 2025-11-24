/* Test header for blinkLED */
#ifndef TEST_BLINKLED_H
#define TEST_BLINKLED_H

#include "unity.h"
#include "mocks.h"

void test_blinkLED_toggles_pin_and_waits_converted_ticks(void);
void test_blinkLED_handles_zero_ticks_boundary(void);
void test_blinkLED_handles_nonstandard_ticks_boundary(void);

#endif
