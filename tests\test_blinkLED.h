/* Test header for blinkLED */
#ifndef TEST_BLINKLED_H
#define TEST_BLINKLED_H

#include "unity.h"
#include "mocks.h"

void test_blinkLED_toggles_pin_and_waits_500ms(void);
void test_blinkLED_waits_zero_ticks_when_converter_returns_zero(void);
void test_blinkLED_uses_converted_ticks_value(void);

#endif
