/* generated thread source file - do not edit */
#include "hmi_thread.h"

TX_THREAD hmi_thread;
void hmi_thread_create(void);
static void hmi_thread_func(ULONG thread_input);
/** Alignment requires using pragma for IAR. GCC is done through attribute. */
#if defined(__ICCARM__)
#pragma data_alignment = BSP_STACK_ALIGNMENT
#endif
static uint8_t hmi_thread_stack[8192] BSP_PLACE_IN_SECTION(".stack.hmi_thread") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
#if spi_on_rspi_CALLBACK_USED_g_spi_lcdc
#if defined(__ICCARM__)
#define g_lcd_spi_callback_WEAK_ATTRIBUTE
#pragma weak g_lcd_spi_callback                            = g_lcd_spi_callback_internal
#elif defined(__GNUC__)
#define g_lcd_spi_callback_WEAK_ATTRIBUTE       __attribute__ ((weak, alias("g_lcd_spi_callback_internal")))
#endif
void g_lcd_spi_callback(spi_callback_args_t * p_args) g_lcd_spi_callback_WEAK_ATTRIBUTE;
#endif
spi_ctrl_t g_spi_lcdc_ctrl;

/** RSPI extended configuration for RSPI HAL driver */
const spi_on_rspi_cfg_t g_spi_lcdc_ext_cfg_t =
{ .rspi_clksyn = RSPI_OPERATION_CLK_SYN, .rspi_comm = RSPI_COMMUNICATION_FULL_DUPLEX, .ssl_polarity.rspi_ssl0 =
          RSPI_SSLP_LOW,
  .ssl_polarity.rspi_ssl1 = RSPI_SSLP_LOW, .ssl_polarity.rspi_ssl2 = RSPI_SSLP_LOW, .ssl_polarity.rspi_ssl3 =
          RSPI_SSLP_LOW,
  .loopback.rspi_loopback1 = RSPI_LOOPBACK1_NORMAL_DATA, .loopback.rspi_loopback2 = RSPI_LOOPBACK2_NORMAL_DATA,
  .mosi_idle.rspi_mosi_idle_fixed_val = RSPI_MOSI_IDLE_FIXED_VAL_LOW, .mosi_idle.rspi_mosi_idle_val_fixing =
          RSPI_MOSI_IDLE_VAL_FIXING_DISABLE,
  .parity.rspi_parity = RSPI_PARITY_STATE_DISABLE, .parity.rspi_parity_mode = RSPI_PARITY_MODE_ODD, .ssl_select =
          RSPI_SSL_SELECT_SSL0,
  .ssl_level_keep = RSPI_SSL_LEVEL_KEEP_NOT, .clock_delay.rspi_clock_delay_count = RSPI_CLOCK_DELAY_COUNT_1,
  .clock_delay.rspi_clock_delay_state = RSPI_CLOCK_DELAY_STATE_DISABLE, .ssl_neg_delay.rspi_ssl_neg_delay_count =
          RSPI_SSL_NEGATION_DELAY_1,
  .ssl_neg_delay.rspi_ssl_neg_delay_state = RSPI_SSL_NEGATION_DELAY_DISABLE,
  .access_delay.rspi_next_access_delay_count = RSPI_NEXT_ACCESS_DELAY_COUNT_1,
  .access_delay.rspi_next_access_delay_state = RSPI_NEXT_ACCESS_DELAY_STATE_DISABLE, };

const spi_cfg_t g_spi_lcdc_cfg =
{ .channel = 0, .operating_mode = SPI_MODE_MASTER, .clk_phase = SPI_CLK_PHASE_EDGE_EVEN, .clk_polarity =
          SPI_CLK_POLARITY_HIGH,
  .mode_fault = SPI_MODE_FAULT_ERROR_DISABLE, .bit_order = SPI_BIT_ORDER_MSB_FIRST, .bitrate = 1000000,
#define SYNERGY_NOT_DEFINED (1)            
#if (SYNERGY_NOT_DEFINED == SYNERGY_NOT_DEFINED)
  .p_transfer_tx = NULL,
#else
  .p_transfer_tx = &SYNERGY_NOT_DEFINED,
#endif
#if (SYNERGY_NOT_DEFINED == SYNERGY_NOT_DEFINED)
  .p_transfer_rx = NULL,
#else
  .p_transfer_rx = &SYNERGY_NOT_DEFINED,
#endif
#undef SYNERGY_NOT_DEFINED
  .p_callback = g_lcd_spi_callback,
  .p_context = (void *) &g_spi_lcdc, .p_extend = (void *) &g_spi_lcdc_ext_cfg_t, };
/* Instance structure to use this module. */
const spi_instance_t g_spi_lcdc =
{ .p_ctrl = &g_spi_lcdc_ctrl, .p_cfg = &g_spi_lcdc_cfg, .p_api = &g_spi_on_rspi };

#if spi_on_rspi_CALLBACK_USED_g_spi_lcdc
/*******************************************************************************************************************//**
 * @brief      This is a weak example callback function.  It should be overridden by defining a user callback function 
 *             with the prototype below.
 *               - void g_lcd_spi_callback(spi_callback_args_t * p_args)
 *
 * @param[in]  p_args  Callback arguments used to identify what caused the callback.
 **********************************************************************************************************************/
void g_lcd_spi_callback_internal(spi_callback_args_t * p_args);
void g_lcd_spi_callback_internal(spi_callback_args_t * p_args)
{
    /** Do nothing. */
    SSP_PARAMETER_NOT_USED(p_args);
}
#endif
#if EXTERNAL_IRQ_ON_ICU_CALLBACK_USED_g_external_irq
#if defined(__ICCARM__)
#define NULL_WEAK_ATTRIBUTE
#pragma weak NULL                            = NULL_internal
#elif defined(__GNUC__)
#define NULL_WEAK_ATTRIBUTE       __attribute__ ((weak, alias("NULL_internal")))
#endif
void NULL(external_irq_callback_args_t * p_args) NULL_WEAK_ATTRIBUTE;
#endif
static external_irq_ctrl_t g_external_irq_ctrl;
static const external_irq_cfg_t g_external_irq_cfg =
{ .channel = 9, .trigger = EXTERNAL_IRQ_TRIG_FALLING, .filter_enable = true, .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true, .p_callback = NULL, .p_context = &g_external_irq, .p_extend = NULL };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq =
{ .p_ctrl = &g_external_irq_ctrl, .p_cfg = &g_external_irq_cfg, .p_api = &g_external_irq_on_icu };

#if EXTERNAL_IRQ_ON_ICU_CALLBACK_USED_g_external_irq
/*******************************************************************************************************************//**
 * @brief      This is a weak example callback function.  It should be overridden by defining a user callback function 
 *             with the prototype below.
 *               - void NULL(external_irq_callback_args_t * p_args)
 *
 * @param[in]  p_args  Callback arguments used to identify what caused the callback.
 **********************************************************************************************************************/
void NULL_internal(external_irq_callback_args_t * p_args);
void NULL_internal(external_irq_callback_args_t * p_args)
{
    /** Do nothing. */
    SSP_PARAMETER_NOT_USED(p_args);
}
#endif
sf_external_irq_ctrl_t g_sf_external_irq_ctrl;
const sf_external_irq_cfg_t g_sf_external_irq_cfg =
{ .event = SF_EXTERNAL_IRQ_EVENT_SEMAPHORE_PUT, .p_lower_lvl_irq = &g_external_irq, };
/* Instance structure to use this module. */
const sf_external_irq_instance_t g_sf_external_irq =
{ .p_ctrl = &g_sf_external_irq_ctrl, .p_cfg = &g_sf_external_irq_cfg, .p_api = &g_sf_external_irq_on_sf_external_irq };
#if I2C_CALLBACK_USED_g_i2c
#if defined(__ICCARM__)
#define NULL_WEAK_ATTRIBUTE
#pragma weak NULL                            = NULL_internal
#elif defined(__GNUC__)
#define NULL_WEAK_ATTRIBUTE       __attribute__ ((weak, alias("NULL_internal")))
#endif
void NULL(i2c_callback_args_t * p_args) NULL_WEAK_ATTRIBUTE;
#endif
i2c_ctrl_t g_i2c_ctrl;
const i2c_cfg_t g_i2c_cfg =
{ .channel = 2, .rate = I2C_RATE_STANDARD, .slave = 0x48, .addr_mode = I2C_ADDR_MODE_7BIT, .p_callback = NULL,
  .p_context = (void *) &g_i2c, };
/* Instance structure to use this module. */
const i2c_master_instance_t g_i2c =
{ .p_ctrl = &g_i2c_ctrl, .p_cfg = &g_i2c_cfg, .p_api = &g_i2c_master_on_riic };

#if I2C_CALLBACK_USED_g_i2c
/*******************************************************************************************************************//**
 * @brief      This is a weak example callback function.  It should be overridden by defining a user callback function 
 *             with the prototype below.
 *               - void NULL(i2c_callback_args_t * p_args)
 *
 * @param[in]  p_args  Callback arguments used to identify what caused the callback.
 **********************************************************************************************************************/
void NULL_internal(i2c_callback_args_t * p_args);
void NULL_internal(i2c_callback_args_t * p_args)
{
    /** Do nothing. */
    SSP_PARAMETER_NOT_USED(p_args);
}
#endif
static sf_touch_panel_i2c_ctrl_t g_sf_touch_panel_i2c_extend;
sf_touch_panel_ctrl_t g_sf_touch_panel_i2c_ctrl;
const sf_touch_panel_i2c_cfg_t g_sf_touch_panel_i2c_cfg_extend =
{ .p_lower_lvl_i2c = &g_i2c, .p_lower_lvl_ctrl = &g_sf_touch_panel_i2c_extend, .p_lower_lvl_irq = &g_sf_external_irq,
  .pin = IOPORT_PORT_06_PIN_09, .p_chip = &g_sf_touch_panel_i2c_chip_sx8654, };
const sf_touch_panel_cfg_t g_sf_touch_panel_i2c_cfg =
{ .hsize_pixels = 240, .vsize_pixels = 320, .priority = 3, .update_hz = 10, .p_message = &g_sf_message, .p_extend =
          &g_sf_touch_panel_i2c_cfg_extend,
  .event_class_instance = 0 };
/* Instance structure to use this module. */
const sf_touch_panel_instance_t g_sf_touch_panel_i2c =
{ .p_ctrl = &g_sf_touch_panel_i2c_ctrl, .p_cfg = &g_sf_touch_panel_i2c_cfg, .p_api =
          &g_sf_touch_panel_on_sf_touch_panel_i2c };
TX_QUEUE g_sf_touch_panel_queue;
static uint8_t queue_memory_g_sf_touch_panel_queue[20];
void hmi_thread_create(void)
{
    /* Initialize each kernel object. */
    tx_queue_create (&g_sf_touch_panel_queue, (CHAR *) "Touch Panel Queue", 1, &queue_memory_g_sf_touch_panel_queue,
                     sizeof(queue_memory_g_sf_touch_panel_queue));

    tx_thread_create (&hmi_thread, (CHAR *) "HMI Thread", hmi_thread_func, (ULONG) NULL, &hmi_thread_stack, 8192, 5, 5,
                      1, TX_DONT_START);
}

static void hmi_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize each module instance. */
    ssp_err_t ssp_err_g_sf_touch_panel_i2c;
    ssp_err_g_sf_touch_panel_i2c = g_sf_touch_panel_i2c.p_api->open (g_sf_touch_panel_i2c.p_ctrl,
                                                                     g_sf_touch_panel_i2c.p_cfg);
    if (SSP_SUCCESS != ssp_err_g_sf_touch_panel_i2c)
    {
        while (1)
            ;
    }

    /* Enter user code for this thread. */
    hmi_thread_entry ();
}
