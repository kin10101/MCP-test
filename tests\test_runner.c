/* Unity Test Runner */
#include "unity.h"
#include "mocks.h"

#include "test_initLED.h"
#include "test_blinkLED.h"
#include "test_core0_main.h"

void setUp(void) {
    mock_reset_all();
}

void tearDown(void) {
    /* Cleanup after each test */
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_initLED_calls_gpio_config_and_high);
    RUN_TEST(test_initLED_sets_pushpull_and_general_idx_on_LED_portpin);
    RUN_TEST(test_initLED_sets_LED_pin_high);
    RUN_TEST(test_blinkLED_toggles_pin_and_waits_converted_ticks);
    RUN_TEST(test_blinkLED_handles_zero_ticks_boundary);
    RUN_TEST(test_blinkLED_handles_nonstandard_ticks_boundary);
    RUN_TEST(test_core0_main_disables_watchdogs_and_enables_interrupts);
    RUN_TEST(test_core0_main_emits_and_waits_for_sync_event);
    RUN_TEST(test_core0_main_initializes_and_blinks_led_three_times);
    
    return UNITY_END();
}
