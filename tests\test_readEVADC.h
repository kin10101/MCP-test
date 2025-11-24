/* Test header for readEVADC */
#ifndef TEST_READEVADC_H
#define TEST_READEVADC_H

#include "unity.h"
#include "mocks.h"

void test_readEVADC_basic_reads_all_channels(void);
void test_readEVADC_poll_multiple_times_per_channel(void);
void test_readEVADC_immediate_valid_results(void);

#endif
