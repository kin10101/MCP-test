/* Test header for initLED */
#ifndef TEST_INITLED_H
#define TEST_INITLED_H

#include "unity.h"
#include "mocks.h"

void test_initLED_calls_gpio_config_and_high(void);
void test_initLED_sets_pushpull_and_general_idx_on_LED_portpin(void);
void test_initLED_sets_LED_pin_high(void);

#endif
