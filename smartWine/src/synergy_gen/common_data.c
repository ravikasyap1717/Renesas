/* generated common source file - do not edit */
#include "common_data.h"
dac_ctrl_t g_dac0_ctrl;
const dac_cfg_t g_dac0_cfg =
{ .channel = 0, .ad_da_synchronized = false, .data_format = DAC_DATA_FORMAT_FLUSH_RIGHT, .output_amplifier_enabled =
          false,
  .p_extend = NULL };
/* Instance structure to use this module. */
const dac_instance_t g_dac0 =
{ .p_ctrl = &g_dac0_ctrl, .p_cfg = &g_dac0_cfg, .p_api = &g_dac_on_dac };
#if TIMER_ON_GPT_CALLBACK_USED_g_audio_timer
#if defined(__ICCARM__)
#define NULL_WEAK_ATTRIBUTE
#pragma weak NULL                            = NULL_internal
#elif defined(__GNUC__)
#define NULL_WEAK_ATTRIBUTE       __attribute__ ((weak, alias("NULL_internal")))
#endif
void NULL(timer_callback_args_t * p_args) NULL_WEAK_ATTRIBUTE;
#endif
static timer_ctrl_t g_audio_timer_ctrl;
static const timer_on_gpt_cfg_t g_audio_timer_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW } };
static const timer_cfg_t g_audio_timer_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 5063, .unit = TIMER_UNIT_FREQUENCY_HZ, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 0, .autostart = false, .p_callback = NULL, .p_context = &g_audio_timer, .p_extend = &g_audio_timer_extend };
/* Instance structure to use this module. */
const timer_instance_t g_audio_timer =
{ .p_ctrl = &g_audio_timer_ctrl, .p_cfg = &g_audio_timer_cfg, .p_api = &g_timer_on_gpt };

#if TIMER_ON_GPT_CALLBACK_USED_g_audio_timer
/*******************************************************************************************************************//**
 * @brief      This is a weak example callback function.  It should be overridden by defining a user callback function 
 *             with the prototype below.
 *               - void NULL(timer_callback_args_t * p_args)
 *
 * @param[in]  p_args  Callback arguments used to identify what caused the callback.
 **********************************************************************************************************************/
void NULL_internal(timer_callback_args_t * p_args);
void NULL_internal(timer_callback_args_t * p_args)
{
    /** Do nothing. */
    SSP_PARAMETER_NOT_USED(p_args);
}
#endif
#ifdef NULL
#define DTC_CALLBACK_USED_g_audio_transfer (0)
#else
#define DTC_CALLBACK_USED_g_audio_transfer (1)
#endif
#if DTC_CALLBACK_USED_g_audio_transfer
void NULL(transfer_callback_args_t * p_args);
#endif
transfer_ctrl_t g_audio_transfer_ctrl;
transfer_info_t g_audio_transfer_info =
{ .dest_addr_mode = TRANSFER_ADDR_MODE_FIXED, .repeat_area = TRANSFER_REPEAT_AREA_SOURCE, .irq = TRANSFER_IRQ_END,
  .chain_mode = TRANSFER_CHAIN_MODE_DISABLED, .src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED, .size =
          TRANSFER_SIZE_2_BYTE,
  .mode = TRANSFER_MODE_NORMAL, .p_dest = (void *) &R_DAC->DADRn[0], .p_src = (void const *) NULL, .num_blocks = 0,
  .length = 0, };
const transfer_cfg_t g_audio_transfer_cfg =
{ .p_info = &g_audio_transfer_info, .activation_source = ELC_EVENT_GPT0_COUNTER_OVERFLOW, .auto_enable = false,
  .p_callback = NULL, .p_context = &g_audio_transfer, };
/* Instance structure to use this module. */
const transfer_instance_t g_audio_transfer =
{ .p_ctrl = &g_audio_transfer_ctrl, .p_cfg = &g_audio_transfer_cfg, .p_api = &g_transfer_on_dtc };
static sf_audio_playback_hw_ctrl_t g_sf_audio_playback_hw_ctrl;
static sf_audio_playback_hw_dac_ctrl_t g_sf_audio_playback_hw_extend;
static const sf_audio_playback_hw_dac_cfg_t g_sf_audio_playback_hw_cfg_extend =
{ .p_lower_lvl_timer = &g_audio_timer, .p_lower_lvl_dac = &g_dac0, .p_lower_lvl_transfer = &g_audio_transfer, .p_ctrl =
          &g_sf_audio_playback_hw_extend, };
static const sf_audio_playback_hw_cfg_t g_sf_audio_playback_hw_cfg =
{ .p_extend = &g_sf_audio_playback_hw_cfg_extend };
const sf_audio_playback_hw_instance_t g_sf_audio_playback_hw =
{ .p_api = &g_sf_audio_playback_hw_on_sf_audio_playback_hw_dac, .p_ctrl = &g_sf_audio_playback_hw_ctrl, .p_cfg =
          &g_sf_audio_playback_hw_cfg, };
extern sf_message_subscriber_list_t * p_subscriber_lists[];
sf_message_ctrl_t g_sf_message_ctrl;
static uint8_t g_sf_message_work_buffer[2048];
/* Configures the messaging framework */
sf_message_cfg_t g_sf_message_cfg =
{ .p_work_memory_start = &g_sf_message_work_buffer, .work_memory_size_bytes = 2048, .buffer_size =
          sizeof(sf_message_payload_t),
  .pp_subscriber_lists = p_subscriber_lists, .p_block_pool_name = (uint8_t *) "sf_msg_blk_pool" };
/* Instance structure to use this module. */
const sf_message_instance_t g_sf_message =
{ .p_ctrl = &g_sf_message_ctrl, .p_cfg = &g_sf_message_cfg, .p_api = &g_sf_message_on_sf_message };
extern TX_QUEUE alert_thread_message_queue;
extern const sf_message_instance_t g_sf_message;
sf_audio_playback_common_ctrl_t g_sf_audio_playback_common;
const sf_audio_playback_common_cfg_t g_sf_audio_playback_common_cfg =
{ .p_lower_lvl_hw = &g_sf_audio_playback_hw, .priority = 3, .p_message = &g_sf_message, .p_queue =
          &alert_thread_message_queue, };
#if JPEG_DECODE_CALLBACK_USED_g_jpeg_decode0
#if defined(__ICCARM__)
#define NULL_WEAK_ATTRIBUTE
#pragma weak NULL = NULL_internal
#elif defined(__GNUC__)
#define NULL_WEAK_ATTRIBUTE __attribute__ ((weak, alias("NULL_internal")))
#endif
void NULL(jpeg_decode_callback_args_t * p_args) NULL_WEAK_ATTRIBUTE;
#endif

static jpeg_decode_ctrl_t g_jpeg_decode0_ctrl;
const jpeg_decode_cfg_t g_jpeg_decode0_cfg =
{ .input_data_format = JPEG_DECODE_DATA_FORMAT_NORMAL, .output_data_format = JPEG_DECODE_DATA_FORMAT_NORMAL,
  .pixel_format = JPEG_DECODE_PIXEL_FORMAT_RGB565, .alpha_value = 255, .p_callback = NULL, };
const jpeg_decode_instance_t g_jpeg_decode0 =
{ .p_api = (jpeg_decode_api_t const *) &g_jpeg_decode_on_jpeg_decode, .p_ctrl = &g_jpeg_decode0_ctrl, .p_cfg =
          &g_jpeg_decode0_cfg };

#if JPEG_DECODE_CALLBACK_USED_g_jpeg_decode0
/*******************************************************************************************************************//**
 * @brief      This is a weak example callback function for JPEG Decode HAL Driver. It should be overridden by defining
 *             a user callback function with the prototype below.
 *               - void NULL(jpeg_decode_callback_args_t * p_args)
 *
 * @param[in]  p_args  Callback arguments used to identify what caused the callback.
 **********************************************************************************************************************/
void NULL_internal(jpeg_decode_callback_args_t * p_args)
{
    /** Do nothing. */
}
#endif
static sf_jpeg_decode_ctrl_t g_sf_jpeg_decode0_ctrl;

static const sf_jpeg_decode_cfg_t g_sf_jpeg_decode0_cfg =
{ .p_lower_lvl_jpeg_decode = (jpeg_decode_instance_t const *) &g_jpeg_decode0 };
const sf_jpeg_decode_instance_t g_sf_jpeg_decode0 =
{ .p_api = &g_sf_jpeg_decode_on_sf_jpeg_decode, .p_ctrl = &g_sf_jpeg_decode0_ctrl, .p_cfg =
          (sf_jpeg_decode_cfg_t const *) &g_sf_jpeg_decode0_cfg };
#if defined(DISPLAY_ON_GLCD_CALLBACK_USED)
#if defined(__ICCARM__)
#define NULL_WEAK_ATTRIBUTE
#pragma weak NULL                            = NULL_internal
#elif defined(__GNUC__)
#define NULL_WEAK_ATTRIBUTE       __attribute__ ((weak, alias("NULL_internal")))
void NULL(display_callback_args_t * p_args) NULL_WEAK_ATTRIBUTE;
#endif
#endif
/** Display frame buffer */
#if (true)
#ifdef __GNUC__
uint8_t g_display0_fb_background[1][((256 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT0) >> 3] __attribute__ ((aligned(64), section(".bss")));
#else /* __ICCARM__ */
#pragma data_alignment = 64
#pragma location = ".bss"
uint8_t g_display0_fb_background[1][((256 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT0) >> 3];
#endif
#else
/** Graphics screen1 is specified not to be used when starting */
#endif
#if (false)
#ifdef __GNUC__
uint8_t g_display0_fb_foreground[1][((256 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT1) >> 3] __attribute__ ((aligned(64), section(".bss")));
#else /* __ICCARM__ */
#pragma data_alignment = 64
#pragma location = ".bss"
uint8_t g_display0_fb_foreground[1][((256 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT1) >> 3];
#endif
#else
/** Graphics screen2 is specified not to be used when starting */
#endif

#if (false)
/** Display CLUT buffer to be used for updating CLUT */
static uint32_t CLUT_buffer[256];

/** Display CLUT configuration(only used if using CLUT format) */
display_clut_cfg_t g_display0_clut_cfg_glcd =
{
    .p_base = (uint32_t *)CLUT_buffer,
    .start = 0, /* User have to update this setting when using */
    .size = 256 /* User have to update this setting when using */
};
#else
/** CLUT is specified not to be used */
#endif

#if (false | false | false)
/** Display interface configuration */
static const display_gamma_correction_t g_display0_gamma_cfg =
{
    .r =
    {
        .enable = false,
        .gain =
        {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        .threshold =
        {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    },
    .g =
    {
        .enable = false,
        .gain =
        {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        .threshold =
        {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    },
    .b =
    {
        .enable = false,
        .gain =
        {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        .threshold =
        {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    }
};
#endif

/** Display device extended configuration */
static const glcd_cfg_t g_display0_extend_cfg =
{ .tcon_hsync = GLCD_TCON_PIN_2, .tcon_vsync = GLCD_TCON_PIN_1, .tcon_de = GLCD_TCON_PIN_0, .correction_proc_order =
          GLCD_CORRECTION_PROC_ORDER_BRIGHTNESS_CONTRAST2GAMMA,
  .clksrc = GLCD_CLK_SRC_INTERNAL, .clock_div_ratio = GLCD_PANEL_CLK_DIVISOR_32, .dithering_mode =
          GLCD_DITHERING_MODE_TRUNCATE,
  .dithering_pattern_A = GLCD_DITHERING_PATTERN_11, .dithering_pattern_B = GLCD_DITHERING_PATTERN_11,
  .dithering_pattern_C = GLCD_DITHERING_PATTERN_11, .dithering_pattern_D = GLCD_DITHERING_PATTERN_11 };

/** Display control block instance */
display_ctrl_t g_display0_ctrl;

/** Display interface configuration */
const display_cfg_t g_display0_cfg =
{
/** Input1(Graphics1 screen) configuration */
.input[0] =
{
#if (true)
  .p_base = (uint32_t *)&g_display0_fb_background[0],
#else
  .p_base = NULL,
#endif
  .hsize = 240,
  .vsize = 320, .hstride = 256, .format = DISPLAY_IN_FORMAT_16BITS_RGB565, .line_descending_enable = false,
  .lines_repeat_enable = false, .lines_repeat_times = 0 },

  /** Input2(Graphics2 screen) configuration */
  .input[1] =
  {
#if (false)
    .p_base = (uint32_t *)&g_display0_fb_foreground[0],
#else
    .p_base = NULL,
#endif
    .hsize = 240,
    .vsize = 320, .hstride = 256, .format = DISPLAY_IN_FORMAT_16BITS_RGB565, .line_descending_enable = false,
    .lines_repeat_enable = false, .lines_repeat_times = 0 },

  /** Input1(Graphics1 screen) layer configuration */
  .layer[0] =
  { .coordinate =
  { .x = 0, .y = 0 },
    .bg_color =
    { .byte =
    { .a = 255, .r = 0, .g = 0, .b = 255 } },
    .fade_control = DISPLAY_FADE_CONTROL_NONE, .fade_speed = 0 },

  /** Input2(Graphics2 screen) layer configuration */
  .layer[1] =
  { .coordinate =
  { .x = 0, .y = 0 },
    .bg_color =
    { .byte =
    { .a = 255, .r = 255, .g = 0, .b = 0 } },
    .fade_control = DISPLAY_FADE_CONTROL_NONE, .fade_speed = 0 },

  /** Output configuration */
  .output =
  { .htiming =
  { .total_cyc = 320, .display_cyc = 240, .back_porch = 6, .sync_width = 4, .sync_polarity =
            DISPLAY_SIGNAL_POLARITY_LOACTIVE },
    .vtiming =
    { .total_cyc = 328, .display_cyc = 320, .back_porch = 4, .sync_width = 4, .sync_polarity =
              DISPLAY_SIGNAL_POLARITY_LOACTIVE },
    .format = DISPLAY_OUT_FORMAT_16BITS_RGB565, .endian = DISPLAY_ENDIAN_LITTLE, .color_order = DISPLAY_COLOR_ORDER_RGB,
    .data_enable_polarity = DISPLAY_SIGNAL_POLARITY_HIACTIVE, .sync_edge = DISPLAY_SIGNAL_SYNC_EDGE_RISING, .bg_color =
    { .byte =
    { .a = 255, .r = 0, .g = 0, .b = 0 } },
    .brightness =
    { .enable = false, .r = 512, .g = 512, .b = 512 },
    .contrast =
    { .enable = false, .r = 128, .g = 128, .b = 128 },
#if (false | false | false)
    .p_gamma_correction = (display_gamma_correction_t *)(&g_display0_gamma_cfg),
#else
    .p_gamma_correction = NULL,
#endif
    .dithering_on = false },

  /** Display device callback function pointer */
  .p_callback = NULL,
  .p_context = (void *) &g_display0,

  /** Display device extended configuration */
  .p_extend = (void *) (&g_display0_extend_cfg) };

#if (true)
/** Display on GLCD run-time configuration(for the graphics1 screen) */
display_runtime_cfg_t g_display0_runtime_cfg_bg =
{
    .input =
    {
#if (true)
        .p_base = (uint32_t *)&g_display0_fb_background[0],
#else
        .p_base = NULL,
#endif
        .hsize = 240,
        .vsize = 320,
        .hstride = 256,
        .format = DISPLAY_IN_FORMAT_16BITS_RGB565,
        .line_descending_enable = false,
        .lines_repeat_enable = false,
        .lines_repeat_times = 0
    },
    .layer =
    {
        .coordinate =
        {
            .x = 0,
            .y = 0
        },
        .bg_color =
        {
            .byte =
            {
                .a = 255,
                .r = 0,
                .g = 0,
                .b = 255
            }
        },
        .fade_control = DISPLAY_FADE_CONTROL_NONE,
        .fade_speed = 0
    }
};
#endif
#if (false)
/** Display on GLCD run-time configuration(for the graphics2 screen) */
display_runtime_cfg_t g_display0_runtime_cfg_fg =
{
    .input =
    {
#if (false)
        .p_base = (uint32_t *)&g_display0_fb_foreground[0],
#else
        .p_base = NULL,
#endif
        .hsize = 240,
        .vsize = 320,
        .hstride = 256,
        .format = DISPLAY_IN_FORMAT_16BITS_RGB565,
        .line_descending_enable = false,
        .lines_repeat_enable = false,
        .lines_repeat_times = 0
    },
    .layer =
    {
        .coordinate =
        {
            .x = 0,
            .y = 0
        },
        .bg_color =
        {
            .byte =
            {
                .a = 255,
                .r = 255,
                .g = 0,
                .b = 0
            }
        },
        .fade_control = DISPLAY_FADE_CONTROL_NONE,
        .fade_speed = 0
    }
};
#endif

/* Instance structure to use this module. */
const display_instance_t g_display0 =
        { .p_ctrl = &g_display0_ctrl, .p_cfg = (display_cfg_t *) &g_display0_cfg, .p_api =
                  (display_api_t *) &g_display_on_glcd };

#if defined(DISPLAY_ON_GLCD_CALLBACK_USED)
/*******************************************************************************************************************//**
 * @brief      This is a weak example callback function.  It should be overridden by defining a user callback function 
 *             with the prototype below.
 *               - void NULL(display_callback_args_t * p_args)
 *
 * @param[in]  p_args  Callback arguments used to identify what caused the callback.
 **********************************************************************************************************************/
void NULL_internal(display_callback_args_t * p_args);
void NULL_internal(display_callback_args_t * p_args)
{
    /** Do nothing. */
    SSP_PARAMETER_NOT_USED(p_args);
}
#endif
/** GUIX Canvas Buffer */
#if false
#ifdef __GNUC__
uint8_t g_sf_el_gx_canvas[sizeof(g_display0_fb_background[0])] __attribute__ ((aligned(4), section(".bss")));
#else /* __ICCARM__ */
#pragma data_alignment = 4
#pragma location = ".bss"
uint8_t g_sf_el_gx_canvas[sizeof(g_display0_fb_background[0])];
#endif
#endif

/** JPEG Work Buffer */
#ifdef GX_USE_SYNERGY_JPEG
#if (16536)
#ifdef __GNUC__
uint8_t g_sf_el_gx_jpegbuffer[16536] __attribute__ ((aligned(64), section(".bss")));
#else /* __ICCARM__ */
#pragma data_alignment = 64
#pragma location = ".bss"
uint8_t g_sf_el_gx_jpegbuffer[16536];
#endif
#endif
#endif

/** GUIX Port module control block instance */
static sf_el_gx_ctrl_t g_sf_el_gx_ctrl;

/** GUIX Port module configuration */
static const sf_el_gx_cfg_t g_sf_el_gx_cfg =
{ .p_display_instance = (display_instance_t *) &g_display0, .p_display_runtime_cfg = &g_display0_runtime_cfg_bg,
#if false
  .p_canvas = g_sf_el_gx_canvas,
#else
  .p_canvas = NULL,
#endif
  .p_framebuffer_a = g_display0_fb_background[0],
  .p_framebuffer_b = NULL, .p_callback = NULL,
#ifdef GX_USE_SYNERGY_JPEG
  .p_jpegbuffer = g_sf_el_gx_jpegbuffer,
  .jpegbuffer_size = 16536,
#else
  .p_jpegbuffer = NULL,
  .jpegbuffer_size = 0,
#endif
  .rotation_angle = 0 };

/** GUIX Port module instance */
sf_el_gx_instance_t g_sf_el_gx =
{ .p_api = &sf_el_gx_on_guix, .p_ctrl = &g_sf_el_gx_ctrl, .p_cfg = &g_sf_el_gx_cfg };
void g_common_init(void)
{
    ssp_err_t err_g_sf_message;

    /* Initializes Messaging Framework Queues */
    g_message_init ();

    /* Opens the messaging framework */
    err_g_sf_message = g_sf_message.p_api->open (g_sf_message.p_ctrl, g_sf_message.p_cfg);
    if (SSP_SUCCESS != err_g_sf_message)
    {
        /* Error returns, check the cause. */
        while (1)
            ;
    }
}
