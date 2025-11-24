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
    
    RUN_TEST(test_initLED_configures_push_pull_and_sets_high);
    RUN_TEST(test_initLED_called_twice_accumulates_calls);
    RUN_TEST(test_initLED_pin_and_mode_values_are_correct_each_call);
    RUN_TEST(test_blinkLED_toggles_and_waits_500ms);
    RUN_TEST(test_blinkLED_multiple_calls_with_variable_ticks);
    RUN_TEST(test_blinkLED_zero_ticks_still_calls_wait);
    RUN_TEST(test_core0_main_happy_path_calls_expected_sequences);
    RUN_TEST(test_core0_main_boundary_zero_loop_limit_runs_no_blinks);
    RUN_TEST(test_core0_main_error_password_zero_still_disables_watchdogs);
    
    return UNITY_END();
}
