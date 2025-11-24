/* test_init_UART.c - SELF-CONTAINED */
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
static IfxAsclin_Asc g_asc = {0};
static uint8 g_ascTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8U] = {0};

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Dependencies
   ======================================================================== */

typedef struct { uint32 call_count; IfxAsclin_Asc_Config *last_cfg; void *last_module; } mock_initModuleConfig_t;
typedef struct { uint32 call_count; IfxAsclin_Asc *last_asc; IfxAsclin_Asc_Config *last_cfg; boolean return_value; } mock_initModule_t;
typedef struct { uint32 call_count; uint32 last_coreIndex; uint32 return_value; } mock_Irq_getTos_t;
typedef struct { uint32 call_count; uint32 return_value; } mock_getCoreIndex_t;

static mock_initModuleConfig_t m_initModuleConfig = {0};
static mock_initModule_t       m_initModule       = {0};
static mock_Irq_getTos_t       m_Irq_getTos       = {0};
static mock_getCoreIndex_t     m_getCoreIndex     = {0};

__attribute__((weak)) void IfxAsclin_Asc_initModuleConfig(IfxAsclin_Asc_Config *cfg, void *module) { m_initModuleConfig.call_count++; m_initModuleConfig.last_cfg = cfg; m_initModuleConfig.last_module = module; }
__attribute__((weak)) boolean IfxAsclin_Asc_initModule(IfxAsclin_Asc *asc, IfxAsclin_Asc_Config *cfg) { m_initModule.call_count++; m_initModule.last_asc = asc; m_initModule.last_cfg = cfg; return (m_initModule.return_value != FALSE) ? m_initModule.return_value : TRUE; }
__attribute__((weak)) uint32 IfxCpu_Irq_getTos(uint32 coreIndex) { m_Irq_getTos.call_count++; m_Irq_getTos.last_coreIndex = coreIndex; return (m_Irq_getTos.return_value != 0U) ? m_Irq_getTos.return_value : 0U; }
__attribute__((weak)) uint32 IfxCpu_getCoreIndex(void) { m_getCoreIndex.call_count++; return (m_getCoreIndex.return_value != 0U) ? m_getCoreIndex.return_value : 0U; }

static void mock_reset_all(void) {
    memset(&m_initModuleConfig, 0, sizeof(m_initModuleConfig));
    memset(&m_initModule, 0, sizeof(m_initModule));
    memset(&m_Irq_getTos, 0, sizeof(m_Irq_getTos));
    memset(&m_getCoreIndex, 0, sizeof(m_getCoreIndex));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
static void init_UART(void) {
    IfxAsclin_Asc_Config cfg;
    IfxAsclin_Asc_initModuleConfig(&cfg, SERIAL_PIN_TX.module);
    cfg.baudrate.baudrate = SERIAL_BAUDRATE;
    cfg.interrupt.txPriority = INTPRIO_ASCLIN0_TX;
    cfg.interrupt.typeOfService = IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());
    cfg.txBuffer = g_ascTxBuffer;
    cfg.txBufferSize = ASC_TX_BUFFER_SIZE;
    /* pins opaque pointer */
    static uint8 pins_dummy = 0U; cfg.pins = &pins_dummy;
    (void)IfxAsclin_Asc_initModule(&g_asc, &cfg);
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) {
    mock_reset_all();
    m_getCoreIndex.return_value = 0U; /* default core index 0 */
    m_Irq_getTos.return_value = 3U;   /* arbitrary TOS value */
}
void tearDown(void) {}

void test_init_UART_sets_baudrate_and_priorities(void) {
    init_UART();
    TEST_ASSERT_EQUAL_UINT32(1U, m_initModuleConfig.call_count);
    TEST_ASSERT_EQUAL_UINT32(1U, m_initModule.call_count);
    TEST_ASSERT_EQUAL_UINT32(SERIAL_BAUDRATE, m_initModule.last_cfg->baudrate.baudrate);
    TEST_ASSERT_EQUAL_UINT32(INTPRIO_ASCLIN0_TX, m_initModule.last_cfg->interrupt.txPriority);
    TEST_ASSERT_EQUAL_UINT32(3U, m_initModule.last_cfg->interrupt.typeOfService);
}

void test_init_UART_sets_tx_buffer_and_size(void) {
    init_UART();
    TEST_ASSERT_EQUAL_PTR(g_ascTxBuffer, m_initModule.last_cfg->txBuffer);
    TEST_ASSERT_EQUAL_UINT32(ASC_TX_BUFFER_SIZE, m_initModule.last_cfg->txBufferSize);
}

void test_init_UART_assigns_pins_pointer(void) {
    init_UART();
    TEST_ASSERT_NOT_NULL(m_initModule.last_cfg->pins);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_init_UART_sets_baudrate_and_priorities);
    RUN_TEST(test_init_UART_sets_tx_buffer_and_size);
    RUN_TEST(test_init_UART_assigns_pins_pointer);
    return UNITY_END();
}
