/* test_readEVADC.c - SELF-CONTAINED */
#include "unity.h"
#include "mock_config.h"

/* ========================================================================
   INLINE MACROS - DefinedConstants from JSON
   ======================================================================== */
#define GROUPID_8 (8U)
#define CHANNELS_NUM (3U)
#define AN39_CHID (7U)
#define AN38_CHID (6U)
#define AN37_CHID (5U)
#define SERIAL_BAUDRATE (115200U)
#define INTPRIO_ASCLIN0_TX (19U)
#define ASC_TX_BUFFER_SIZE (1024U)

/* ASCLIN pin mappings (not used here) */
static const IfxAsclin_Asc_PinMapping IfxAsclin0_RXA_P14_1_IN = { (void*)0x12340001 };
static const IfxAsclin_Asc_PinMapping IfxAsclin0_TX_P14_0_OUT = { (void*)0x12340002 };
#define SERIAL_PIN_RX (IfxAsclin0_RXA_P14_1_IN)
#define SERIAL_PIN_TX (IfxAsclin0_TX_P14_0_OUT)

/* ========================================================================
   GLOBALS REQUIRED BY FUNCTION UNDER TEST
   ======================================================================== */
static IfxEvadc_Adc_Channel g_adcChannel[CHANNELS_NUM] = { {0}, {1}, {2} };
static Ifx_EVADC_G_RES g_results[CHANNELS_NUM];

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Only dependencies of this function
   ======================================================================== */

typedef struct {
    uint32 call_count_total;
    uint32 call_count_per_ch[CHANNELS_NUM];
    uint32 threshold_per_ch[CHANNELS_NUM];
    uint32 result_per_ch[CHANNELS_NUM];
} mock_IfxEvadc_Adc_getResult_t;
static mock_IfxEvadc_Adc_getResult_t mock_IfxEvadc_Adc_getResult = {0};

__attribute__((weak)) Ifx_EVADC_G_RES IfxEvadc_Adc_getResult(IfxEvadc_Adc_Channel *ch) {
    uint8 idx = ch->channelId; /* use channelId as index in this mock */
    mock_IfxEvadc_Adc_getResult.call_count_total++;
    if (idx < CHANNELS_NUM) {
        mock_IfxEvadc_Adc_getResult.call_count_per_ch[idx]++;
        uint32 calls = mock_IfxEvadc_Adc_getResult.call_count_per_ch[idx];
        uint32 thresh = mock_IfxEvadc_Adc_getResult.threshold_per_ch[idx];
        Ifx_EVADC_G_RES r;
        if (calls >= thresh) {
            r.B.VF = 1U;
            r.B.RESULT = mock_IfxEvadc_Adc_getResult.result_per_ch[idx];
        } else {
            r.B.VF = 0U;
            r.B.RESULT = 0U;
        }
        return r;
    }
    Ifx_EVADC_G_RES r; r.B.VF = 1U; r.B.RESULT = 0U; return r;
}

static void mock_set_getResult_threshold(uint8 ch, uint32 threshold_calls, uint32 result_value) {
    if (ch < CHANNELS_NUM) {
        mock_IfxEvadc_Adc_getResult.threshold_per_ch[ch] = threshold_calls;
        mock_IfxEvadc_Adc_getResult.result_per_ch[ch] = result_value;
        mock_IfxEvadc_Adc_getResult.call_count_per_ch[ch] = 0U;
    }
}
static uint32 mock_get_getResult_total_calls(void) { return mock_IfxEvadc_Adc_getResult.call_count_total; }
static void mock_reset_all(void) { memset(&mock_IfxEvadc_Adc_getResult, 0, sizeof(mock_IfxEvadc_Adc_getResult)); }

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
static void readEVADC(void) {
    for (uint8 i = 0U; i < CHANNELS_NUM; i++) {
        Ifx_EVADC_G_RES r;
        do {
            r = IfxEvadc_Adc_getResult(&g_adcChannel[i]);
        } while (r.B.VF == 0U);
        g_results[i] = r;
    }
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) {
    mock_reset_all();
    /* Initialize channel IDs to match indices */
    for (uint8 i = 0U; i < CHANNELS_NUM; i++) { g_adcChannel[i].channelId = i; }
}
void tearDown(void) {}

void test_readEVADC_basic_reads_all_channels(void) {
    mock_set_getResult_threshold(0U, 1U, 100U);
    mock_set_getResult_threshold(1U, 1U, 200U);
    mock_set_getResult_threshold(2U, 1U, 300U);

    readEVADC();

    TEST_ASSERT_EQUAL_UINT32(1U, g_results[0].B.VF);
    TEST_ASSERT_EQUAL_UINT32(1U, g_results[1].B.VF);
    TEST_ASSERT_EQUAL_UINT32(1U, g_results[2].B.VF);
    TEST_ASSERT_EQUAL_UINT32(100U, g_results[0].B.RESULT);
    TEST_ASSERT_EQUAL_UINT32(200U, g_results[1].B.RESULT);
    TEST_ASSERT_EQUAL_UINT32(300U, g_results[2].B.RESULT);
}

void test_readEVADC_poll_multiple_times_per_channel(void) {
    mock_set_getResult_threshold(0U, 3U, 111U);
    mock_set_getResult_threshold(1U, 2U, 222U);
    mock_set_getResult_threshold(2U, 5U, 333U);

    readEVADC();

    TEST_ASSERT_EQUAL_UINT32(111U, g_results[0].B.RESULT);
    TEST_ASSERT_EQUAL_UINT32(222U, g_results[1].B.RESULT);
    TEST_ASSERT_EQUAL_UINT32(333U, g_results[2].B.RESULT);
    /* Total calls should be 3 + 2 + 5 = 10 */
    TEST_ASSERT_EQUAL_UINT32(10U, mock_get_getResult_total_calls());
}

void test_readEVADC_immediate_valid_results(void) {
    mock_set_getResult_threshold(0U, 0U, 7U);
    mock_set_getResult_threshold(1U, 0U, 6U);
    mock_set_getResult_threshold(2U, 0U, 5U);

    readEVADC();

    TEST_ASSERT_EQUAL_UINT32(7U, g_results[0].B.RESULT);
    TEST_ASSERT_EQUAL_UINT32(6U, g_results[1].B.RESULT);
    TEST_ASSERT_EQUAL_UINT32(5U, g_results[2].B.RESULT);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_readEVADC_basic_reads_all_channels);
    RUN_TEST(test_readEVADC_poll_multiple_times_per_channel);
    RUN_TEST(test_readEVADC_immediate_valid_results);
    return UNITY_END();
}
