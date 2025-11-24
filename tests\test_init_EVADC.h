/* Test header for init_EVADC */
#ifndef TEST_INIT_EVADC_H
#define TEST_INIT_EVADC_H

#include "unity.h"
#include "mocks.h"

void test_init_EVADC_calls_init_chain_once(void);
void test_init_EVADC_adds_channels_to_queue(void);
void test_init_EVADC_starts_queue0_once(void);

#endif
