/* Test header for process_light_level */
#ifndef TEST_PROCESS_LIGHT_LEVEL_H
#define TEST_PROCESS_LIGHT_LEVEL_H

#include "unity.h"
#include "mocks.h"

void test_process_light_level_low_boundary_at_2740(void);
void test_process_light_level_medium_classification(void);
void test_process_light_level_bright_at_max(void);
void test_process_light_level_raw_below_threshold_clamped(void);

#endif
