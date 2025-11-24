/* test_process_light_level.c - SELF-CONTAINED */
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

/* ASCLIN pin mappings */
static const IfxAsclin_Asc_PinMapping IfxAsclin0_RXA_P14_1_IN = { (void*)0x12340001 };
static const IfxAsclin_Asc_PinMapping IfxAsclin0_TX_P14_0_OUT = { (void*)0x12340002 };
#define SERIAL_PIN_RX (IfxAsclin0_RXA_P14_1_IN)
#define SERIAL_PIN_TX (IfxAsclin0_TX_P14_0_OUT)

/* ========================================================================
   GLOBALS REQUIRED BY FUNCTION UNDER TEST
   ======================================================================== */
static Ifx_EVADC_G_RES g_results[CHANNELS_NUM];
static Ifx_P MODULE_P00 = {0};

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Dependencies of this function
   ======================================================================== */

/* uart_send_string mock capturing messages */
typedef struct {
    uint32 call_count;
    char messages[8][64];
} mock_uart_send_string_t;
static mock_uart_send_string_t mock_uart_send_string = {0};

static uint32 local_strlen(const char *s) { uint32 n = 0U; while (s && s[n] != '\0') { n++; } return n; }
static void local_strcpy(char *dst, const char *src) { uint32 i = 0U; while (src && src[i] != '\0') { dst[i] = src[i]; i++; } dst[i] = '\0'; }

__attribute__((weak)) void uart_send_string(const char* msg) {
    if (mock_uart_send_string.call_count < 8U) {
        local_strcpy(mock_uart_send_string.messages[mock_uart_send_string.call_count], msg ? msg : "");
    }
    mock_uart_send_string.call_count++;
}

/* Port control mocks */
typedef struct { uint32 call_count; Ifx_P *last_port; uint8 last_pin; } mock_IfxPort_setPinLow_t;
typedef struct { uint32 call_count; Ifx_P *last_port; uint8 last_pin; } mock_IfxPort_setPinHigh_t;
static mock_IfxPort_setPinLow_t mock_IfxPort_setPinLow = {0};
static mock_IfxPort_setPinHigh_t mock_IfxPort_setPinHigh = {0};

__attribute__((weak)) void IfxPort_setPinLow(Ifx_P *port, uint8 pin) { mock_IfxPort_setPinLow.call_count++; mock_IfxPort_setPinLow.last_port = port; mock_IfxPort_setPinLow.last_pin = pin; }
__attribute__((weak)) void IfxPort_setPinHigh(Ifx_P *port, uint8 pin) { mock_IfxPort_setPinHigh.call_count++; mock_IfxPort_setPinHigh.last_port = port; mock_IfxPort_setPinHigh.last_pin = pin; }

static void mock_reset_all(void) {
    memset(&mock_uart_send_string, 0, sizeof(mock_uart_send_string));
    memset(&mock_IfxPort_setPinLow, 0, sizeof(mock_IfxPort_setPinLow));
    memset(&mock_IfxPort_setPinHigh, 0, sizeof(mock_IfxPort_setPinHigh));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
static void process_light_level(void) {
    uint32 raw = g_results[0].B.RESULT;
    /* Fixed-point normalization to tenths of percent (avoid float) */
    sint32 diff = (sint32)raw - 2740; if (diff < 0) diff = 0; /* below threshold */
    uint32 tenths = (uint32)(((uint32)diff * 1000U) / 1355U); /* 100.0% => 1000 tenths */
    if (tenths < 10U) tenths = 10U; /* clamp to 1.0% */
    if (tenths > 1000U) tenths = 1000U; /* clamp to 100.0% */

    char msg[64];
    uint32 intPart = tenths / 10U;
    uint32 decPart = tenths % 10U;
    /* Format: "Normalized light = X.Y\r\n" */
    uint32 pos = 0U; const char *prefix = "Normalized light = ";
    while (prefix[pos] != '\0') { msg[pos] = prefix[pos]; pos++; }
    /* convert intPart */
    char tmp[16]; uint32 ti = 0U; uint32 val = intPart; if (val == 0U) { tmp[ti++] = '0'; }
    char rev[16]; uint32 ri = 0U; while (val > 0U) { rev[ri++] = (char)('0' + (val % 10U)); val /= 10U; }
    while (ri > 0U) { tmp[ti++] = rev[--ri]; }
    for (uint32 i = 0U; i < ti; i++) { msg[pos++] = tmp[i]; }
    msg[pos++] = '.'; msg[pos++] = (char)('0' + decPart);
    msg[pos++] = '\r'; msg[pos++] = '\n'; msg[pos] = '\0';
    uart_send_string(msg);

    if (tenths < 400U) { /* < 40.0% */
        uart_send_string("Low light\r\n");
        IfxPort_setPinLow(&MODULE_P00, 5U);
    } else if (tenths <= 600U) { /* 40.0%..60.0% */
        uart_send_string("Medium light\r\n");
        IfxPort_setPinHigh(&MODULE_P00, 5U);
    } else {
        uart_send_string("Bright light\r\n");
        IfxPort_setPinHigh(&MODULE_P00, 5U);
    }
    uart_send_string("--------------------\r\n");
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) { mock_reset_all(); }
void tearDown(void) {}

void test_process_light_level_low_boundary_at_2740(void) {
    g_results[0].B.RESULT = 2740U;
    process_light_level();
    TEST_ASSERT_EQUAL_UINT32(3U, mock_uart_send_string.call_count); /* normalized + class + separator */
    TEST_ASSERT_EQUAL_UINT32(1U, mock_IfxPort_setPinLow.call_count);
    TEST_ASSERT_EQUAL_UINT32(0U, mock_IfxPort_setPinHigh.call_count);
    TEST_ASSERT_EQUAL_STRING("Low light\r\n", mock_uart_send_string.messages[1]);
}

void test_process_light_level_medium_classification(void) {
    g_results[0].B.RESULT = 3420U; /* ~50% */
    process_light_level();
    TEST_ASSERT_EQUAL_UINT32(3U, mock_uart_send_string.call_count);
    TEST_ASSERT_EQUAL_UINT32(0U, mock_IfxPort_setPinLow.call_count);
    TEST_ASSERT_EQUAL_UINT32(1U, mock_IfxPort_setPinHigh.call_count);
    TEST_ASSERT_EQUAL_STRING("Medium light\r\n", mock_uart_send_string.messages[1]);
}

void test_process_light_level_bright_at_max(void) {
    g_results[0].B.RESULT = 4095U;
    process_light_level();
    TEST_ASSERT_EQUAL_UINT32(3U, mock_uart_send_string.call_count);
    TEST_ASSERT_EQUAL_UINT32(0U, mock_IfxPort_setPinLow.call_count);
    TEST_ASSERT_EQUAL_UINT32(1U, mock_IfxPort_setPinHigh.call_count);
    TEST_ASSERT_EQUAL_STRING("Bright light\r\n", mock_uart_send_string.messages[1]);
}

void test_process_light_level_raw_below_threshold_clamped(void) {
    g_results[0].B.RESULT = 0U; /* below 2740, clamps to 1% */
    process_light_level();
    TEST_ASSERT_EQUAL_UINT32(3U, mock_uart_send_string.call_count);
    TEST_ASSERT_EQUAL_UINT32(1U, mock_IfxPort_setPinLow.call_count);
    TEST_ASSERT_EQUAL_STRING("Low light\r\n", mock_uart_send_string.messages[1]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_process_light_level_low_boundary_at_2740);
    RUN_TEST(test_process_light_level_medium_classification);
    RUN_TEST(test_process_light_level_bright_at_max);
    RUN_TEST(test_process_light_level_raw_below_threshold_clamped);
    return UNITY_END();
}
