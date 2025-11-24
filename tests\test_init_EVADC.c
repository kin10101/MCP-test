/* test_init_EVADC.c - SELF-CONTAINED */
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

/* EVADC group channels mapping */
static uint8 g_grp8channels[CHANNELS_NUM] = { AN39_CHID, AN38_CHID, AN37_CHID };

/* ========================================================================
   GLOBALS REQUIRED BY FUNCTION UNDER TEST
   ======================================================================== */
static Ifx_EVADC MODULE_EVADC = {0};
static IfxEvadc_Adc g_evadc = {0};
static IfxEvadc_Adc_Group g_adcGroup = {0};
static IfxEvadc_Adc_Channel g_adcChannel[CHANNELS_NUM];

/* ========================================================================
   INLINE MOCK IMPLEMENTATIONS - Dependencies chain
   ======================================================================== */

typedef struct { uint32 call_count; IfxEvadc_Adc_Config *last_cfg; Ifx_EVADC *last_module; } mock_initModuleConfig_t;
typedef struct { uint32 call_count; IfxEvadc_Adc *last_adc; IfxEvadc_Adc_Config *last_cfg; } mock_initModule_t;
typedef struct { uint32 call_count; IfxEvadc_Adc_GroupConfig *last_cfg; IfxEvadc_Adc *last_adc; } mock_initGroupConfig_t;
typedef struct { uint32 call_count; IfxEvadc_Adc_Group *last_grp; IfxEvadc_Adc_GroupConfig *last_cfg; } mock_initGroup_t;
typedef struct { uint32 call_count; IfxEvadc_Adc_ChannelConfig *last_cfg; IfxEvadc_Adc_Group *last_grp; } mock_initChannelConfig_t;
typedef struct { uint32 call_count; IfxEvadc_Adc_Channel *last_ch; IfxEvadc_Adc_ChannelConfig *last_cfg; } mock_initChannel_t;
typedef struct { uint32 call_count; IfxEvadc_Adc_Channel *last_ch; uint32 last_requestSource; uint32 last_refill; } mock_addToQueue_t;
typedef struct { uint32 call_count; IfxEvadc_Adc_Group *last_grp; uint32 last_requestSource; } mock_startQueue_t;

static mock_initModuleConfig_t m_initModuleConfig = {0};
static mock_initModule_t       m_initModule       = {0};
static mock_initGroupConfig_t  m_initGroupConfig  = {0};
static mock_initGroup_t        m_initGroup        = {0};
static mock_initChannelConfig_t m_initChannelConfig = {0};
static mock_initChannel_t      m_initChannel      = {0};
static mock_addToQueue_t       m_addToQueue       = {0};
static mock_startQueue_t       m_startQueue       = {0};

__attribute__((weak)) void IfxEvadc_Adc_initModuleConfig(IfxEvadc_Adc_Config *cfg, Ifx_EVADC *module) { m_initModuleConfig.call_count++; m_initModuleConfig.last_cfg = cfg; m_initModuleConfig.last_module = module; }
__attribute__((weak)) boolean IfxEvadc_Adc_initModule(IfxEvadc_Adc *adc, IfxEvadc_Adc_Config *cfg) { m_initModule.call_count++; m_initModule.last_adc = adc; m_initModule.last_cfg = cfg; return TRUE; }
__attribute__((weak)) void IfxEvadc_Adc_initGroupConfig(IfxEvadc_Adc_GroupConfig *cfg, IfxEvadc_Adc *adc) { m_initGroupConfig.call_count++; m_initGroupConfig.last_cfg = cfg; m_initGroupConfig.last_adc = adc; }
__attribute__((weak)) boolean IfxEvadc_Adc_initGroup(IfxEvadc_Adc_Group *grp, IfxEvadc_Adc_GroupConfig *cfg) { m_initGroup.call_count++; m_initGroup.last_grp = grp; m_initGroup.last_cfg = cfg; return TRUE; }
__attribute__((weak)) void IfxEvadc_Adc_initChannelConfig(IfxEvadc_Adc_ChannelConfig *cfg, IfxEvadc_Adc_Group *grp) { m_initChannelConfig.call_count++; m_initChannelConfig.last_cfg = cfg; m_initChannelConfig.last_grp = grp; }
__attribute__((weak)) boolean IfxEvadc_Adc_initChannel(IfxEvadc_Adc_Channel *ch, IfxEvadc_Adc_ChannelConfig *cfg) { m_initChannel.call_count++; m_initChannel.last_ch = ch; m_initChannel.last_cfg = cfg; return TRUE; }
__attribute__((weak)) boolean IfxEvadc_Adc_addToQueue(IfxEvadc_Adc_Channel *ch, uint32 requestSource, uint32 refill) { m_addToQueue.call_count++; m_addToQueue.last_ch = ch; m_addToQueue.last_requestSource = requestSource; m_addToQueue.last_refill = refill; return TRUE; }
__attribute__((weak)) boolean IfxEvadc_Adc_startQueue(IfxEvadc_Adc_Group *grp, uint32 requestSource) { m_startQueue.call_count++; m_startQueue.last_grp = grp; m_startQueue.last_requestSource = requestSource; return TRUE; }

static void mock_reset_all(void) {
    memset(&m_initModuleConfig, 0, sizeof(m_initModuleConfig));
    memset(&m_initModule, 0, sizeof(m_initModule));
    memset(&m_initGroupConfig, 0, sizeof(m_initGroupConfig));
    memset(&m_initGroup, 0, sizeof(m_initGroup));
    memset(&m_initChannelConfig, 0, sizeof(m_initChannelConfig));
    memset(&m_initChannel, 0, sizeof(m_initChannel));
    memset(&m_addToQueue, 0, sizeof(m_addToQueue));
    memset(&m_startQueue, 0, sizeof(m_startQueue));
}

/* ========================================================================
   INLINE FUNCTION UNDER TEST
   ======================================================================== */
static void init_EVADC(void) {
    IfxEvadc_Adc_Config moduleCfg; IfxEvadc_Adc_initModuleConfig(&moduleCfg, &MODULE_EVADC);
    (void)IfxEvadc_Adc_initModule(&g_evadc, &moduleCfg);

    IfxEvadc_Adc_GroupConfig groupCfg; IfxEvadc_Adc_initGroupConfig(&groupCfg, &g_evadc);
    groupCfg.groupId = GROUPID_8; groupCfg.master = GROUPID_8;
    groupCfg.arbiter.requestSlotQueue0Enabled = TRUE;
    groupCfg.queueRequest[0].triggerConfig.gatingMode = IfxEvadc_GatingMode_always;
    (void)IfxEvadc_Adc_initGroup(&g_adcGroup, &groupCfg);

    for (uint8 i = 0U; i < CHANNELS_NUM; i++) {
        IfxEvadc_Adc_ChannelConfig chCfg; IfxEvadc_Adc_initChannelConfig(&chCfg, &g_adcGroup);
        chCfg.channelId = g_grp8channels[i]; chCfg.resultRegister = g_grp8channels[i];
        (void)IfxEvadc_Adc_initChannel(&g_adcChannel[i], &chCfg);
        (void)IfxEvadc_Adc_addToQueue(&g_adcChannel[i], IfxEvadc_RequestSource_queue0, IFXEVADC_QUEUE_REFILL);
    }
    (void)IfxEvadc_Adc_startQueue(&g_adcGroup, IfxEvadc_RequestSource_queue0);
}

/* ========================================================================
   UNITY TEST CASES
   ======================================================================== */
void setUp(void) { mock_reset_all(); }
void tearDown(void) {}

void test_init_EVADC_calls_init_chain_once(void) {
    init_EVADC();
    TEST_ASSERT_EQUAL_UINT32(1U, m_initModuleConfig.call_count);
    TEST_ASSERT_EQUAL_UINT32(1U, m_initModule.call_count);
    TEST_ASSERT_EQUAL_UINT32(1U, m_initGroupConfig.call_count);
    TEST_ASSERT_EQUAL_UINT32(1U, m_initGroup.call_count);
    TEST_ASSERT_EQUAL_UINT32(CHANNELS_NUM, m_initChannelConfig.call_count);
    TEST_ASSERT_EQUAL_UINT32(CHANNELS_NUM, m_initChannel.call_count);
}

void test_init_EVADC_adds_channels_to_queue(void) {
    init_EVADC();
    TEST_ASSERT_EQUAL_UINT32(CHANNELS_NUM, m_addToQueue.call_count);
    TEST_ASSERT_EQUAL_UINT32(IfxEvadc_RequestSource_queue0, m_addToQueue.last_requestSource);
    TEST_ASSERT_EQUAL_UINT32(IFXEVADC_QUEUE_REFILL, m_addToQueue.last_refill);
}

void test_init_EVADC_starts_queue0_once(void) {
    init_EVADC();
    TEST_ASSERT_EQUAL_UINT32(1U, m_startQueue.call_count);
    TEST_ASSERT_EQUAL_UINT32(IfxEvadc_RequestSource_queue0, m_startQueue.last_requestSource);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_init_EVADC_calls_init_chain_once);
    RUN_TEST(test_init_EVADC_adds_channels_to_queue);
    RUN_TEST(test_init_EVADC_starts_queue0_once);
    return UNITY_END();
}
