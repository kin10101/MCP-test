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
    
    RUN_TEST(test_initLED_configures_pushpull_and_sets_high);
    RUN_TEST(test_initLED_called_twice_updates_counts_and_params);
    RUN_TEST(test_initLED_call_order_mode_before_high);
    RUN_TEST(test_blinkLED_toggles_and_waits_500ms);
    RUN_TEST(test_blinkLED_boundary_450ms_ticks);
    RUN_TEST(test_blinkLED_exception_zero_ticks);
    RUN_TEST(test_core0_main_invokes_startup_sequence_and_blink_loop);
    RUN_TEST(test_core0_main_watchdog_password_zero);
    RUN_TEST(test_core0_main_called_twice_accumulates_blinks);
    
    return UNITY_END();
}
