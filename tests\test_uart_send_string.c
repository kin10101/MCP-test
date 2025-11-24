/* test_uart_send_string.c - SELF-CONTAINED */
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

/* ASCLIN pin mappings as constants and macros */
static const IfxAsclin_Asc_PinMapping IfxAsclin0_RXA_P14_1_IN = { (void*)0x12340001 };
static const IfxAsclin_Asc_PinMapping IfxAsclin0_TX_P14_0_OUT = { (void*)0x12340002 };
#define SERIAL_PIN_RX (IfxAsclin0_RXA_P14_1_IN)
#define SERIAL_PIN_TX (IfxAsclin0_TX_P14_0_OUT)

/* Port instance for LED (not used in this file but defined for completeness) */
static Ifx_P MODULE_P00 = {0};

/* ========================================================================
   GLOBALS REQUIRED BY FUNCTION UNDER TEST
   ======================================================================== */
static IfxAsclin_Asc g_asc = {0};

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Only dependencies of this function
   ======================================================================== */

typedef struct {
    uint32 call_count;
    IfxAsclin_Asc *last_asc;
    uint8 *last_data;
    uint32 last_len_value;
    uint32 *last_len_ptr;
    uint32 last_timeout;
} mock_IfxAsclin_Asc_write_t;
static mock_IfxAsclin_Asc_write_t mock_IfxAsclin_Asc_write = {0};

__attribute__((weak)) uint32 IfxAsclin_Asc_write(IfxAsclin_Asc *asc, uint8 *data, uint32 *len, uint32 timeout) {
    mock_IfxAsclin_Asc_write.call_count++;
    mock_IfxAsclin_Asc_write.last_asc = asc;
    mock_IfxAsclin_Asc_write.last_data = data;
    mock_IfxAsclin_Asc_write.last_len_ptr = len;
    mock_IfxAsclin_Asc_write.last_timeout = timeout;
    mock_IfxAsclin_Asc_write.last_len_value = (len != NULL) ? *len : 0U;
    return mock_IfxAsclin_Asc_write.last_len_value;
}

static uint32 mock_get_IfxAsclin_Asc_write_call_count(void) { return mock_IfxAsclin_Asc_write.call_count; }
static uint32 mock_get_IfxAsclin_Asc_write_last_len_value(void) { return mock_IfxAsclin_Asc_write.last_len_value; }
static uint32 mock_get_IfxAsclin_Asc_write_last_timeout(void) { return mock_IfxAsclin_Asc_write.last_timeout; }
static IfxAsclin_Asc* mock_get_IfxAsclin_Asc_write_last_asc(void) { return mock_IfxAsclin_Asc_write.last_asc; }
static uint8* mock_get_IfxAsclin_Asc_write_last_data(void) { return mock_IfxAsclin_Asc_write.last_data; }

static void mock_reset_all(void) {
    mock_IfxAsclin_Asc_write.call_count = 0U;
    mock_IfxAsclin_Asc_write.last_asc = NULL_PTR;
    mock_IfxAsclin_Asc_write.last_data = NULL_PTR;
    mock_IfxAsclin_Asc_write.last_len_ptr = NULL_PTR;
    mock_IfxAsclin_Asc_write.last_len_value = 0U;
    mock_IfxAsclin_Asc_write.last_timeout = 0U;
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
static void uart_send_string(const char* msg) {
    if (msg == NULL_PTR) {
        return;
    }
    Ifx_SizeT len = 0U;
    const char *p = msg;
    while (*p != '\0') { len++; p++; }
    uint32 ulen = (uint32)len;
    (void)IfxAsclin_Asc_write(&g_asc, (uint8*)msg, &ulen, TIME_INFINITE);
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) {
    mock_reset_all();
}
void tearDown(void) {}

void test_uart_send_string_calls_write_with_correct_len(void) {
    const char *s = "Hello";
    uart_send_string(s);
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxAsclin_Asc_write_call_count());
    TEST_ASSERT_EQUAL_UINT32(5U, mock_get_IfxAsclin_Asc_write_last_len_value());
    TEST_ASSERT_EQUAL_UINT32(TIME_INFINITE, mock_get_IfxAsclin_Asc_write_last_timeout());
    TEST_ASSERT_EQUAL_PTR(&g_asc, mock_get_IfxAsclin_Asc_write_last_asc());
    TEST_ASSERT_NOT_NULL(mock_get_IfxAsclin_Asc_write_last_data());
    TEST_ASSERT_EQUAL_UINT8('H', mock_get_IfxAsclin_Asc_write_last_data()[0]);
}

void test_uart_send_string_empty_string_len_zero(void) {
    const char *s = "";
    uart_send_string(s);
    TEST_ASSERT_EQUAL_UINT32(1U, mock_get_IfxAsclin_Asc_write_call_count());
    TEST_ASSERT_EQUAL_UINT32(0U, mock_get_IfxAsclin_Asc_write_last_len_value());
}

void test_uart_send_string_null_pointer_no_write(void) {
    uart_send_string(NULL_PTR);
    TEST_ASSERT_EQUAL_UINT32(0U, mock_get_IfxAsclin_Asc_write_call_count());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_uart_send_string_calls_write_with_correct_len);
    RUN_TEST(test_uart_send_string_empty_string_len_zero);
    RUN_TEST(test_uart_send_string_null_pointer_no_write);
    return UNITY_END();
}
