/* test_asclin0_Tx_ISR.c - SELF-CONTAINED */
#include "unity.h"
#include "mock_config.h"

/* ========================================================================
   INLINE MACROS - DefinedConstants and ISR macro
   ======================================================================== */
#define GROUPID_8 (8U)
#define CHANNELS_NUM (3U)
#define AN39_CHID (7U)
#define AN38_CHID (6U)
#define AN37_CHID (5U)
#define SERIAL_BAUDRATE (115200U)
#define INTPRIO_ASCLIN0_TX (19U)
#define ASC_TX_BUFFER_SIZE (1024U)
#define IFX_INTERRUPT(name, cpu, prio)

/* ASCLIN pin mappings (not used here) */
static const IfxAsclin_Asc_PinMapping IfxAsclin0_RXA_P14_1_IN = { (void*)0x12340001 };
static const IfxAsclin_Asc_PinMapping IfxAsclin0_TX_P14_0_OUT = { (void*)0x12340002 };
#define SERIAL_PIN_RX (IfxAsclin0_RXA_P14_1_IN)
#define SERIAL_PIN_TX (IfxAsclin0_TX_P14_0_OUT)

/* ========================================================================
   GLOBALS REQUIRED BY FUNCTION UNDER TEST
   ======================================================================== */
static IfxAsclin_Asc g_asc = {0};

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Dependencies
   ======================================================================== */

typedef struct { uint32 call_count; IfxAsclin_Asc *last_asc; } mock_isrTransmit_t;
static mock_isrTransmit_t m_isrTransmit = {0};

__attribute__((weak)) void IfxAsclin_Asc_isrTransmit(IfxAsclin_Asc *asc) { m_isrTransmit.call_count++; m_isrTransmit.last_asc = asc; }
static void mock_reset_all(void) { memset(&m_isrTransmit, 0, sizeof(m_isrTransmit)); }

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
IFX_INTERRUPT(asclin0_Tx_ISR, 0, INTPRIO_ASCLIN0_TX);
static void asclin0_Tx_ISR(void) {
    IfxAsclin_Asc_isrTransmit(&g_asc);
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) { mock_reset_all(); }
void tearDown(void) {}

void test_asclin0_Tx_ISR_invokes_driver_isr_once(void) {
    asclin0_Tx_ISR();
    TEST_ASSERT_EQUAL_UINT32(1U, m_isrTransmit.call_count);
    TEST_ASSERT_EQUAL_PTR(&g_asc, m_isrTransmit.last_asc);
}

void test_asclin0_Tx_ISR_multiple_invocations_increment_count(void) {
    asclin0_Tx_ISR(); asclin0_Tx_ISR();
    TEST_ASSERT_EQUAL_UINT32(2U, m_isrTransmit.call_count);
}

void test_asclin0_Tx_ISR_asc_pointer_consistency(void) {
    asclin0_Tx_ISR();
    TEST_ASSERT_NOT_NULL(m_isrTransmit.last_asc);
    TEST_ASSERT_EQUAL_PTR(&g_asc, m_isrTransmit.last_asc);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_asclin0_Tx_ISR_invokes_driver_isr_once);
    RUN_TEST(test_asclin0_Tx_ISR_multiple_invocations_increment_count);
    RUN_TEST(test_asclin0_Tx_ISR_asc_pointer_consistency);
    return UNITY_END();
}
