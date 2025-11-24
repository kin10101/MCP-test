/* Test header for asclin0_Tx_ISR */
#ifndef TEST_ASCLIN0_TX_ISR_H
#define TEST_ASCLIN0_TX_ISR_H

#include "unity.h"
#include "mocks.h"

void test_asclin0_Tx_ISR_invokes_driver_isr_once(void);
void test_asclin0_Tx_ISR_multiple_invocations_increment_count(void);
void test_asclin0_Tx_ISR_asc_pointer_consistency(void);

#endif
