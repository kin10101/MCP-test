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
    
    RUN_TEST(test_initLED_configures_push_pull_output);
    RUN_TEST(test_initLED_sets_pin_high_off_state);
    RUN_TEST(test_initLED_multiple_calls_increment_counts);
    RUN_TEST(test_blinkLED_toggles_pin_and_waits_500ms);
    RUN_TEST(test_blinkLED_waits_zero_ticks_when_converter_returns_zero);
    RUN_TEST(test_blinkLED_uses_converted_ticks_value);
    RUN_TEST(test_core0_main_initialization_and_watchdog_handling);
    RUN_TEST(test_core0_main_emits_and_waits_cpu_sync_event);
    RUN_TEST(test_core0_main_calls_blinkLED_expected_times);
    
    return UNITY_END();
}
