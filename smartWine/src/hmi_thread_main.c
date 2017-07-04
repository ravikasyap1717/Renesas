/***********************************************************************************************************************
 * Copyright [2015] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 *
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/* HMI Thread entry function */

#include "hmi_thread.h"

#include "bsp_cfg.h"
#include "bsp_api.h"

#include "guix_gen/SmartWine_resources.h"
#include "guix_gen/SmartWine_specifications.h"
#if defined(BSP_BOARD_S7G2_SK)
void ILI9341V_Init();
#endif

uint32_t hmi_initialization_completed = 0;

GX_WINDOW_ROOT * p_window_root;

void hmi_thread_main(void);
static void hmi_send_touch_message(sf_touch_panel_payload_t * p_payload);
TX_QUEUE hmi_thread_message_queue;

void hmi_thread_main(void)
{
    ssp_err_t err;
    UINT      status = TX_SUCCESS;
    sf_message_header_t * p_message = NULL;

    /* Initializes GUIX. */
    status = gx_system_initialize();
    if(TX_SUCCESS != status)
    {
        while(1);
    }

    /* Initializes GUIX drivers. */
    err = g_sf_el_gx.p_api->open (g_sf_el_gx.p_ctrl, g_sf_el_gx.p_cfg);
    if(SSP_SUCCESS != err)
    {
        while(1);
    }

    gx_studio_display_configure ( DISPLAY_1,
                                  g_sf_el_gx.p_api->setup,
                                  LANGUAGE_ENGLISH,
                                  DISPLAY_1_THEME_1,
                                  &p_window_root );

    err = g_sf_el_gx.p_api->canvasInit(g_sf_el_gx.p_ctrl, p_window_root);
    if(SSP_SUCCESS != err)
    {
        while(1);
    }

    /* create all of the secondary screens */
    gx_studio_named_widget_create("ams_window", (GX_WIDGET *)p_window_root, GX_NULL);
    gx_widget_hide(&ams_window);

    gx_studio_named_widget_create("s7_window", (GX_WIDGET *)p_window_root, GX_NULL);
    gx_widget_hide(&s7_window);

    gx_studio_named_widget_create("alert_window", (GX_WIDGET *)p_window_root, GX_NULL);
    gx_widget_hide(&alert_window);

    gx_studio_named_widget_create("main_window", (GX_WIDGET *)p_window_root, GX_NULL);
    gx_widget_hide(&alert_window);

    gx_studio_named_widget_create("warning_window", (GX_WIDGET *)p_window_root, GX_NULL);
    gx_widget_hide(&warning_window);

    /* Creates the primary screen. */
    status = gx_studio_named_widget_create("splash",
                                           (GX_WIDGET *)p_window_root, GX_NULL);
    if(TX_SUCCESS != status)
    {
        while(1);
    }

    /* Shows the root window to make it and patients screen visible. */
    status = gx_widget_show(p_window_root);
    if(TX_SUCCESS != status)
    {
        while(1);
    }

    /* Lets GUIX run. */
    status = gx_system_start();
    if(TX_SUCCESS != status)
    {
        while(1);
    }

#if defined(BSP_BOARD_S7G2_PE_HMI1)
    /* Controls the GPIO pin for LCD ON. */
    err = g_ioport.p_api->pinWrite(IOPORT_PORT_10_PIN_03, IOPORT_LEVEL_HIGH);
    if (err)
    {
        while(1);
    }
#elif defined(BSP_BOARD_S7G2_DK)
    /* Controls the GPIO pin for LCD ON. */
    err = g_ioport.p_api->pinWrite(IOPORT_PORT_07_PIN_10, IOPORT_LEVEL_HIGH);
    if (err)
    {
        while(1);
    }
    /* Controls the GPIO pin for LCD Backlight ON. */
    err = g_ioport.p_api->pinWrite(IOPORT_PORT_07_PIN_12, IOPORT_LEVEL_HIGH);
    if (err)
    {
        while(1);
    }
#elif defined(BSP_BOARD_S7G2_SK)
    /** Open the SPI driver to initialize the LCD **/
    err = g_spi_lcdc.p_api->open(g_spi_lcdc.p_ctrl, (spi_cfg_t *)g_spi_lcdc.p_cfg);

    /** Setup the ILI9341V **/
    ILI9341V_Init();

    /** Close the SPI driver so other devices can use the RSPI channel **/
    err = g_spi_lcdc.p_api->close(g_spi_lcdc.p_ctrl);
#endif

#if defined(BSP_BOARD_S7G2_PE_HMI1)
    /* Opens PWM driver and controls the TFT panel back light. */
    err = g_pwm_backlight.p_api->open(g_pwm_backlight.p_ctrl, g_pwm_backlight.p_cfg);
    if (err)
    {
        while(1);
    }
#endif

    hmi_initialization_completed = 1;

    while (1) {
        g_sf_message.p_api->pend(g_sf_message.p_ctrl, &hmi_thread_message_queue, (sf_message_header_t **) &p_message, TX_WAIT_FOREVER);
        switch (p_message->event_b.class) {
	case SF_MESSAGE_EVENT_CLASS_TOUCH:
	    if (SF_MESSAGE_EVENT_NEW_DATA == p_message->event_b.code) {
		sf_touch_panel_payload_t * p_touch_message = (sf_touch_panel_payload_t *) p_message;

		/** Translate a touch event into a GUIX event */
		hmi_send_touch_message(p_touch_message);
	    }
	    break;
	default:
	    break;
	}

        /** Message is processed, so release buffer. */
        err = g_sf_message.p_api->bufferRelease(g_sf_message.p_ctrl, (sf_message_header_t *) p_message, SF_MESSAGE_RELEASE_OPTION_NONE);
        if (err) {
	    while(1);
	}
//	tx_thread_sleep(1);
    }
}

static void hmi_send_touch_message(sf_touch_panel_payload_t * p_payload)
{
    bool send_event = true;
    GX_EVENT gxe;

    switch (p_payload->event_type) {
    case SF_TOUCH_PANEL_EVENT_DOWN:
        gxe.gx_event_type = GX_EVENT_PEN_DOWN;
        break;
    case SF_TOUCH_PANEL_EVENT_UP:
        gxe.gx_event_type = GX_EVENT_PEN_UP;
        break;
    case SF_TOUCH_PANEL_EVENT_HOLD:
    case SF_TOUCH_PANEL_EVENT_MOVE:
        gxe.gx_event_type = GX_EVENT_PEN_DRAG;
        break;
    case SF_TOUCH_PANEL_EVENT_INVALID:
        send_event = false;
        break;
    default:
        break;
    }

    if (send_event) {
        /** Send event to GUI */
        gxe.gx_event_sender         = GX_ID_NONE;
        gxe.gx_event_target         = 0;  /* the event to be routed to the widget that has input focus */
        gxe.gx_event_display_handle = 0;

        gxe.gx_event_payload.gx_event_pointdata.gx_point_x = p_payload->x;
#if defined(BSP_BOARD_S7G2_SK)
        gxe.gx_event_payload.gx_event_pointdata.gx_point_y = (GX_VALUE)(320 - p_payload->y);
#else
        gxe.gx_event_payload.gx_event_pointdata.gx_point_y = p_payload->y;
#endif

        gx_system_event_send(&gxe);
    }
}
