/* test_send_ADC_results_UART.c - SELF-CONTAINED */
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
static Ifx_EVADC_G_RES g_results[CHANNELS_NUM];

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Dependencies
   ======================================================================== */

typedef struct { uint32 call_count; char messages[8][64]; } mock_uart_send_string_t;
static mock_uart_send_string_t mock_uart_send_string = {0};
static uint32 local_strlen(const char *s) { uint32 n = 0U; while (s && s[n] != '\0') { n++; } return n; }
static void local_strcpy(char *dst, const char *src) { uint32 i = 0U; while (src && src[i] != '\0') { dst[i] = src[i]; i++; } dst[i] = '\0'; }

__attribute__((weak)) void uart_send_string(const char* msg) {
    if (mock_uart_send_string.call_count < 8U) {
        local_strcpy(mock_uart_send_string.messages[mock_uart_send_string.call_count], msg ? msg : "");
    }
    mock_uart_send_string.call_count++;
}

static void mock_reset_all(void) { memset(&mock_uart_send_string, 0, sizeof(mock_uart_send_string)); }

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
static void send_ADC_results_UART(void) {
    char buf[64];
    for (uint8 i = 0U; i < CHANNELS_NUM; i++) {
        /* Format: "CH%u = %u\r\n" without stdio */
        uint32 pos = 0U; buf[pos++] = 'C'; buf[pos++] = 'H';
        /* write channel index */
        char tmp[8]; uint32 ti = 0U; uint32 val = i; if (val == 0U) { tmp[ti++] = '0'; }
        char rev[8]; uint32 ri = 0U; while (val > 0U) { rev[ri++] = (char)('0' + (val % 10U)); val /= 10U; }
        while (ri > 0U) { tmp[ti++] = rev[--ri]; }
        for (uint32 k = 0U; k < ti; k++) { buf[pos++] = tmp[k]; }
        buf[pos++] = ' '; buf[pos++] = '='; buf[pos++] = ' ';
        /* write result */
        ti = 0U; val = g_results[i].B.RESULT; if (val == 0U) { tmp[ti++] = '0'; }
        ri = 0U; while (val > 0U) { rev[ri++] = (char)('0' + (val % 10U)); val /= 10U; }
        while (ri > 0U) { tmp[ti++] = rev[--ri]; }
        for (uint32 k = 0U; k < ti; k++) { buf[pos++] = tmp[k]; }
        buf[pos++] = '\r'; buf[pos++] = '\n'; buf[pos] = '\0';
        uart_send_string(buf);
    }
    uart_send_string("--------------------\r\n");
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) { mock_reset_all(); }
void tearDown(void) {}

void test_send_ADC_results_UART_formats_and_sends_all(void) {
    g_results[0].B.RESULT = 10U; g_results[1].B.RESULT = 20U; g_results[2].B.RESULT = 30U;
    send_ADC_results_UART();
    TEST_ASSERT_EQUAL_UINT32(CHANNELS_NUM + 1U, mock_uart_send_string.call_count);
    TEST_ASSERT_EQUAL_STRING("CH0 = 10\r\n", mock_uart_send_string.messages[0]);
    TEST_ASSERT_EQUAL_STRING("CH1 = 20\r\n", mock_uart_send_string.messages[1]);
    TEST_ASSERT_EQUAL_STRING("CH2 = 30\r\n", mock_uart_send_string.messages[2]);
    TEST_ASSERT_EQUAL_STRING("--------------------\r\n", mock_uart_send_string.messages[3]);
}

void test_send_ADC_results_UART_zero_results_boundary(void) {
    g_results[0].B.RESULT = 0U; g_results[1].B.RESULT = 0U; g_results[2].B.RESULT = 0U;
    send_ADC_results_UART();
    TEST_ASSERT_EQUAL_STRING("CH0 = 0\r\n", mock_uart_send_string.messages[0]);
    TEST_ASSERT_EQUAL_STRING("CH1 = 0\r\n", mock_uart_send_string.messages[1]);
    TEST_ASSERT_EQUAL_STRING("CH2 = 0\r\n", mock_uart_send_string.messages[2]);
}

void test_send_ADC_results_UART_order_and_separator(void) {
    g_results[0].B.RESULT = 5U; g_results[1].B.RESULT = 6U; g_results[2].B.RESULT = 7U;
    send_ADC_results_UART();
    TEST_ASSERT_EQUAL_STRING("--------------------\r\n", mock_uart_send_string.messages[3]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_send_ADC_results_UART_formats_and_sends_all);
    RUN_TEST(test_send_ADC_results_UART_zero_results_boundary);
    RUN_TEST(test_send_ADC_results_UART_order_and_separator);
    return UNITY_END();
}
