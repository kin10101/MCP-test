/* Unity Test Runner */
#include "unity.h"
#include "mocks.h"

#include "test_uart_send_string.h"
#include "test_readEVADC.h"
#include "test_process_light_level.h"
#include "test_init_EVADC.h"
#include "test_send_ADC_results_UART.h"
#include "test_init_UART.h"
#include "test_asclin0_Tx_ISR.h"

void setUp(void) {
    mock_reset_all();
}

void tearDown(void) {
    /* Cleanup after each test */
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_uart_send_string_calls_write_with_correct_len);
    RUN_TEST(test_uart_send_string_empty_string_len_zero);
    RUN_TEST(test_uart_send_string_null_pointer_no_write);
    RUN_TEST(test_readEVADC_basic_reads_all_channels);
    RUN_TEST(test_readEVADC_poll_multiple_times_per_channel);
    RUN_TEST(test_readEVADC_immediate_valid_results);
    RUN_TEST(test_process_light_level_low_boundary_at_2740);
    RUN_TEST(test_process_light_level_medium_classification);
    RUN_TEST(test_process_light_level_bright_at_max);
    RUN_TEST(test_process_light_level_raw_below_threshold_clamped);
    RUN_TEST(test_init_EVADC_calls_init_chain_once);
    RUN_TEST(test_init_EVADC_adds_channels_to_queue);
    RUN_TEST(test_init_EVADC_starts_queue0_once);
    RUN_TEST(test_send_ADC_results_UART_formats_and_sends_all);
    RUN_TEST(test_send_ADC_results_UART_zero_results_boundary);
    RUN_TEST(test_send_ADC_results_UART_order_and_separator);
    RUN_TEST(test_init_UART_sets_baudrate_and_priorities);
    RUN_TEST(test_init_UART_sets_tx_buffer_and_size);
    RUN_TEST(test_init_UART_assigns_pins_pointer);
    RUN_TEST(test_asclin0_Tx_ISR_invokes_driver_isr_once);
    RUN_TEST(test_asclin0_Tx_ISR_multiple_invocations_increment_count);
    RUN_TEST(test_asclin0_Tx_ISR_asc_pointer_consistency);
    
    return UNITY_END();
}
