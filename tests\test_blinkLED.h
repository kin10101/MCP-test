/* Test header for blinkLED */
#ifndef TEST_BLINKLED_H
#define TEST_BLINKLED_H

#include "unity.h"
#include "mocks.h"

void test_blinkLED_toggles_and_waits_500ms(void);
void test_blinkLED_boundary_450ms_ticks(void);
void test_blinkLED_exception_zero_ticks(void);

#endif
