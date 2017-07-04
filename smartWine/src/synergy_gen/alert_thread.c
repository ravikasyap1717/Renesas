/* generated thread source file - do not edit */
#include "alert_thread.h"

TX_THREAD alert_thread;
void alert_thread_create(void);
static void alert_thread_func(ULONG thread_input);
/** Alignment requires using pragma for IAR. GCC is done through attribute. */
#if defined(__ICCARM__)
#pragma data_alignment = BSP_STACK_ALIGNMENT
#endif
static uint8_t alert_thread_stack[8192] BSP_PLACE_IN_SECTION(".stack.alert_thread") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
#if SF_AUDIO_PLAYBACK_ON_SF_AUDIO_PLAYBACK_CALLBACK_USED_g_sf_audio_playback
#if defined(__ICCARM__)
#define NULL_WEAK_ATTRIBUTE
#pragma weak NULL                            = NULL_internal
#elif defined(__GNUC__)
#define NULL_WEAK_ATTRIBUTE       __attribute__ ((weak, alias("NULL_internal")))
#endif
void NULL(sf_message_callback_args_t * p_args) NULL_WEAK_ATTRIBUTE;
#endif
sf_audio_playback_ctrl_t g_sf_audio_playback_ctrl;
const sf_audio_playback_cfg_t g_sf_audio_playback_cfg =
{ .p_common_cfg = &g_sf_audio_playback_common_cfg, .p_common_ctrl = &g_sf_audio_playback_common, .class_instance = 0,
  .p_callback = NULL, };
const sf_audio_playback_instance_t g_sf_audio_playback =
{ .p_api = &g_sf_audio_playback_on_sf_audio_playback, .p_ctrl = &g_sf_audio_playback_ctrl, .p_cfg =
          &g_sf_audio_playback_cfg, };

#if SF_AUDIO_PLAYBACK_ON_SF_AUDIO_PLAYBACK_CALLBACK_USED_g_sf_audio_playback
/*******************************************************************************************************************//**
 * @brief      This is a weak example callback function.  It should be overridden by defining a user callback function 
 *             with the prototype below.
 *               - void NULL(sf_message_callback_args_t * p_args)
 *
 * @param[in]  p_args  Callback arguments used to identify what caused the callback.
 **********************************************************************************************************************/
void NULL_internal(sf_message_callback_args_t * p_args)
{
    /** Do nothing. */
}
#endif
TX_QUEUE alert_thread_message_queue;
static uint8_t queue_memory_alert_thread_message_queue[20];
void alert_thread_create(void)
{
    /* Initialize each kernel object. */
    tx_queue_create (&alert_thread_message_queue, (CHAR *) "Audio Queue", 1, &queue_memory_alert_thread_message_queue,
                     sizeof(queue_memory_alert_thread_message_queue));

    tx_thread_create (&alert_thread, (CHAR *) "Alert Thread", alert_thread_func, (ULONG) NULL, &alert_thread_stack,
                      8192, 20, 20, 1, TX_DONT_START);
}

static void alert_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize each module instance. */
    ssp_err_t ssp_err_g_sf_audio_playback;
    ssp_err_g_sf_audio_playback = g_sf_audio_playback.p_api->open (g_sf_audio_playback.p_ctrl,
                                                                   g_sf_audio_playback.p_cfg);
    if (SSP_SUCCESS != ssp_err_g_sf_audio_playback)
    {
        while (1)
            ;
    }

    /* Enter user code for this thread. */
    alert_thread_entry ();
}
