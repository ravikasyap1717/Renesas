/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "r_dac.h"
#include "r_dac_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_dtc.h"
#include "r_transfer_api.h"
#include "sf_audio_playback_hw_dac.h"
#include "sf_message.h"
#include "sf_message_payloads.h"
#include "sf_audio_playback.h"
#include "r_jpeg_decode.h"
#include "sf_jpeg_decode.h"
#include "r_glcd.h"
#include "r_display_api.h"
#include "sf_el_gx.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** DAC on DAC Instance. */
extern const dac_instance_t g_dac0;
/** Timer on GPT Instance. */
extern const timer_instance_t g_audio_timer;
#ifdef NULL
#define TIMER_ON_GPT_CALLBACK_USED_g_audio_timer (0)
#else
#define TIMER_ON_GPT_CALLBACK_USED_g_audio_timer (1)
#endif
#if TIMER_ON_GPT_CALLBACK_USED_g_audio_timer
void NULL(timer_callback_args_t * p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_audio_transfer;
extern const sf_audio_playback_hw_instance_t g_sf_audio_playback_hw;
extern void g_message_init(void);

/* SF Message on SF Message Instance. */
extern const sf_message_instance_t g_sf_message;
extern const jpeg_decode_instance_t g_jpeg_decode0;
extern const jpeg_decode_cfg_t g_jpeg_decode0_cfg;
#ifdef NULL
#define JPEG_DECODE_CALLBACK_USED_g_jpeg_decode0 (0)
#else
#define JPEG_DECODE_CALLBACK_USED_g_jpeg_decode0 (1)
#endif
#if JPEG_DECODE_CALLBACK_USED_g_jpeg_decode0
void NULL(jpeg_decode_callback_args_t * p_args);
#endif
extern const sf_jpeg_decode_instance_t g_sf_jpeg_decode0;
/* Display on GLCD Instance. */
extern const display_instance_t g_display0;
extern display_runtime_cfg_t g_display0_runtime_cfg_fg;
extern display_runtime_cfg_t g_display0_runtime_cfg_bg;
#if (false)
extern display_clut_cfg_t g_display0_clut_cfg_glcd;
#endif
#if !defined(NULL)
#define DISPLAY_ON_GLCD_CALLBACK_USED
#endif
#if defined(DISPLAY_ON_GLCD_CALLBACK_USED)
void NULL(display_callback_args_t * p_args);
#endif
#if (true)
#define DISPLAY_IN_FORMAT_16BITS_RGB565_0
#if defined (DISPLAY_IN_FORMAT_32BITS_RGB888_0) || defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_0)
#define DISPLAY_BITS_PER_PIXEL_INPUT0 (32)
#elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_0) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB1555_0) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB4444_0)
#define DISPLAY_BITS_PER_PIXEL_INPUT0 (16)
#elif defined (DISPLAY_IN_FORMAT_CLUT8_0)
#define DISPLAY_BITS_PER_PIXEL_INPUT0 (8)
#elif defined (DISPLAY_IN_FORMAT_CLUT4_0)
#define DISPLAY_BITS_PER_PIXEL_INPUT0 (4)
#else
#define DISPLAY_BITS_PER_PIXEL_INPUT0 (1)
#endif
extern uint8_t g_display0_fb_background[1][((256 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT0) >> 3];
#endif
#if (false)
#define DISPLAY_IN_FORMAT_16BITS_RGB565_1
#if defined (DISPLAY_IN_FORMAT_32BITS_RGB888_1) || defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_1)
#define DISPLAY_BITS_PER_PIXEL_INPUT1 (32)
#elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_1) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB1555_1) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB4444_1)
#define DISPLAY_BITS_PER_PIXEL_INPUT1 (16)
#elif defined (DISPLAY_IN_FORMAT_CLUT8_1)
#define DISPLAY_BITS_PER_PIXEL_INPUT1 (8)
#elif defined (DISPLAY_IN_FORMAT_CLUT4_1)
#define DISPLAY_BITS_PER_PIXEL_INPUT1 (4)
#else
#define DISPLAY_BITS_PER_PIXEL_INPUT1 (1)
#endif
extern uint8_t g_display0_fb_foreground[1][((256 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT1) >> 3];
#endif
#ifndef NULL
extern void NULL(sf_el_gx_callback_args_t * p_arg);
#endif
extern sf_el_gx_instance_t g_sf_el_gx;
void g_common_init(void);
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* COMMON_DATA_H_ */
