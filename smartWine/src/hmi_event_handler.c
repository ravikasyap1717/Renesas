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

#include "zelib.h"
#include "ens210.h"

#include "gx_api.h"

#include "guix_gen/SmartWine_resources.h"
#include "guix_gen/SmartWine_specifications.h"

#include <stdio.h>
#include <string.h>
#include "zelib-gpio.h"
#include "zelib-adc.h"
#include "GPS.h"

#define TIME_EVENT_TIMER     (100)

extern char BoardID[];

extern uint32_t ip_address;
extern char SSID[32];
static char pretty_ip_address[24];
extern ze_ens210_instance_t ens210;
extern ze_adc_instance_t Vibration;
extern ze_gps_instance_t gps;

void SendRefresh();
void UpdateGUI();
void UpdateS7Window();
void UpdateAMSWindow();
void SwitchScreens(void *from, void *to);
void DoAlert(int up);

void SendRefresh()
{
    GX_EVENT gxe;

    /** Send event to GUI */
    gxe.gx_event_sender = GX_ID_NONE;
    gxe.gx_event_target = 0;  /* the event is routed to the input focus */
    gxe.gx_event_display_handle = 0;
    gxe.gx_event_type = GX_EVENT_REDRAW;

    gx_system_event_send(&gxe);
}

void SwitchScreens(void *from, void *to)
{
    gx_widget_hide(from);
    gx_widget_show(to);
    gx_system_focus_claim(to);
}

void DoAlert(int up)
{
    GX_BOOL garbage;

    if (up) {
	gx_widget_show(&alert_window);
	gx_widget_front_move(&alert_window, &garbage);
    } else {
	gx_widget_back_move(&alert_window, &garbage);
	gx_widget_hide(&alert_window);
    }
}

void UpdateGUI()
{
    gx_prompt_text_set(&(main_window.main_window_thing), BoardID);
    if (ip_address == 0) {
	pretty_ip_address[0] = '\0';
	gx_prompt_text_set(&(main_window.main_window_info1), "Connecting ...");
	gx_prompt_text_set(&(main_window.main_window_info2), pretty_ip_address);
    } else {
	snprintf(pretty_ip_address, sizeof(pretty_ip_address), "%lu.%lu.%lu.%lu",
		 (ip_address >> 24) & 0xff, (ip_address >> 16) & 0xff,
		 (ip_address >> 8) & 0xff, (ip_address >> 0) & 0xff);
	gx_prompt_text_set(&(main_window.main_window_info1), SSID);
	gx_prompt_text_set(&(main_window.main_window_info2), pretty_ip_address);
    }

/*     if (do_refresh) */
/* 	SendRefresh(); */
}

static char message_buffer[8192];

void ZE_PostErrorMessage(char *format, ...)
{
    va_list ap;
    GX_BOOL garbage;

    va_start(ap, format);
    vsnprintf(message_buffer, sizeof(message_buffer), format, ap);
    va_end(ap);

    gx_multi_line_text_view_text_set(&(warning_window.warning_window_alert), message_buffer);

    gx_widget_show(&warning_window);
    gx_widget_front_move(&warning_window, &garbage);

    tx_thread_sleep(500);

    gx_widget_back_move(&warning_window, &garbage);
    gx_widget_hide(&warning_window);
}

UINT MainWindowEventHandler (GX_WINDOW * widget, GX_EVENT * event_ptr)
{
    switch (event_ptr->gx_event_type) {
    case GX_EVENT_SHOW:
    case GX_EVENT_REDRAW:
	UpdateGUI(0);
        return gx_window_event_process(widget, event_ptr);
        break;

    case GX_EVENT_TIMER:
	break;

    case GX_SIGNAL(IDB_MAIN_AMS_BTN, GX_EVENT_CLICKED):
	SwitchScreens(&main_window, &ams_window);
	break;

#ifdef IDB_MAIN_S7_BTN
    case GX_SIGNAL(IDB_MAIN_S7_BTN, GX_EVENT_CLICKED):
	SwitchScreens(&main_window, &s7_window);
	break;
#endif

    default:
        return gx_window_event_process(widget, event_ptr);
    }
    
    return 0;
}

void UpdateAMSWindow()
{
    static char s1[16];
    static char s2[16],s3[16],s4[16],s5[16];

    /* read required sensor value and store in a array buffer*/
    strcpy(s1,  ZE_Property_GetAsString((ze_device_instance_t *) &ens210, ZE_ENS210_TEMPERATURE));
    strcat(s1, " F");
    strcpy(s2,  ZE_Property_GetAsString((ze_device_instance_t *) &ens210, ZE_ENS210_HUMIDITY));
    strcat(s2, " %");
    strcpy(s3,  ZE_Property_GetAsJSON((ze_device_instance_t *) &Vibration, ZE_ADC_VALUE));
    strcpy(s4,  ZE_Property_GetAsJSON((ze_device_instance_t *) &gps, ZE_GPS_LATITUDE));
    strcpy(s5,  ZE_Property_GetAsJSON((ze_device_instance_t *) &gps, ZE_GPS_LONGITUDE));

    /* Display all value on GLCD*/
    gx_prompt_text_set(&(ams_window.ams_window_temperature_value), s1);
    gx_prompt_text_set(&(ams_window.ams_window_humidity_value), s2);
    gx_prompt_text_set(&(ams_window.ams_window_Vibration_value), s3);
    gx_prompt_text_set(&(ams_window.ams_window_Latitude_value), s4);
    gx_prompt_text_set(&(ams_window.ams_window_Longitude_value), s5);

/*     if (do_refresh) */
/* 	SendRefresh(); */
}

UINT AMSWindowEventHandler (GX_WINDOW * widget, GX_EVENT * event_ptr)
{
    switch (event_ptr->gx_event_type) {
    case GX_EVENT_SHOW:
    case GX_EVENT_REDRAW:
	UpdateAMSWindow(0);
	gx_system_timer_start(widget, TIME_EVENT_TIMER, 50, 50);
        return gx_window_event_process(widget, event_ptr);
        break;

    case GX_EVENT_HIDE:
	gx_system_timer_stop(widget, TIME_EVENT_TIMER);
        return gx_window_event_process(widget, event_ptr);

    case GX_EVENT_TIMER:
	UpdateAMSWindow(1);
	break;

    case GX_SIGNAL(IDB_AMS_MAIN_BTN, GX_EVENT_CLICKED):
	SwitchScreens(&ams_window, &main_window);
	break;

#ifdef IDB_AMS_S7_BTN
    case GX_SIGNAL(IDB_AMS_S7_BTN, GX_EVENT_CLICKED):
	SwitchScreens(&ams_window, &s7_window);
	break;
#endif

    default:
        return gx_window_event_process(widget, event_ptr);
    }
    
    return 0;
}

void UpdateS7Window()
{
#if 0
    static char s1[16];
    static char s2[16];
#ifdef  S7G2_SW_Pin3
    static char s3[16];
#endif
    static char a1[16];
    static char a2[16];

    if (Pmod_Ports[S7G2_SW] != NULL && Pmod_Ports[S7G2_SW]->get != NULL) {
	strcpy(s1, Pmod_Ports[S7G2_SW]->get(S7G2_SW, 0));
	gx_prompt_text_set(&(s7_window.s7_window_sw1_count), s1);

	strcpy(s2, Pmod_Ports[S7G2_SW]->get(S7G2_SW, 1));
	gx_prompt_text_set(&(s7_window.s7_window_sw2_count), s2);

#ifdef  S7G2_SW_Pin3
	strcpy(s3, Pmod_Ports[S7G2_SW]->get(S7G2_SW, 2));
	gx_prompt_text_set(&(s7_window.s7_window_sw3_count), s3);
#endif
    }

    if (Pmod_Ports[S7G2_ADC] != NULL && Pmod_Ports[S7G2_ADC]->get != NULL) {
	strcpy(a1, Pmod_Ports[S7G2_ADC]->get(S7G2_ADC, 0));
	gx_prompt_text_set(&(s7_window.s7_window_temp_count), a1);

	strcpy(a2, Pmod_Ports[S7G2_ADC]->get(S7G2_ADC, 1));
	gx_prompt_text_set(&(s7_window.s7_window_uptime_count), a2);
    }
#endif

/*     if (do_refresh) */
/* 	SendRefresh(); */
}

UINT S7WindowEventHandler (GX_WINDOW * widget, GX_EVENT * event_ptr)
{
    switch (event_ptr->gx_event_type) {
    case GX_EVENT_SHOW:
    case GX_EVENT_REDRAW:
	UpdateS7Window(0);
	gx_system_timer_start(widget, TIME_EVENT_TIMER, 50, 50);
        return gx_window_event_process(widget, event_ptr);
        break;

    case GX_EVENT_HIDE:
	gx_system_timer_stop(widget, TIME_EVENT_TIMER);
        return gx_window_event_process(widget, event_ptr);

    case GX_EVENT_TIMER:
	UpdateS7Window(1);
	break;

    case GX_SIGNAL(IDB_LED1_BTN, GX_EVENT_TOGGLE_ON):
	gx_window_event_process(widget, event_ptr);
//	Pmod_Ports[PmodLED]->set(PmodLED, "LED1", "on");
	break;

    case GX_SIGNAL(IDB_LED1_BTN, GX_EVENT_TOGGLE_OFF):
	gx_window_event_process(widget, event_ptr);
//	Pmod_Ports[PmodLED]->set(PmodLED, "LED1", "off");
	break;

    case GX_SIGNAL(IDB_LED2_BTN, GX_EVENT_TOGGLE_ON):
	gx_window_event_process(widget, event_ptr);
//	Pmod_Ports[PmodLED]->set(PmodLED, "LED2", "on");
	break;

    case GX_SIGNAL(IDB_LED2_BTN, GX_EVENT_TOGGLE_OFF):
	gx_window_event_process(widget, event_ptr);
//	Pmod_Ports[PmodLED]->set(PmodLED, "LED2", "off");
	break;

    case GX_SIGNAL(IDB_LED3_BTN, GX_EVENT_TOGGLE_ON):
	gx_window_event_process(widget, event_ptr);
//	Pmod_Ports[PmodLED]->set(PmodLED, "LED3", "on");
	break;

    case GX_SIGNAL(IDB_LED3_BTN, GX_EVENT_TOGGLE_OFF):
	gx_window_event_process(widget, event_ptr);
//	Pmod_Ports[PmodLED]->set(PmodLED, "LED3", "off");
	break;

    case GX_SIGNAL(IDB_LED_BLINK_BTN, GX_EVENT_TOGGLE_ON):
	gx_window_event_process(widget, event_ptr);
//	Pmod_Ports[PmodLED]->set(PmodLED, "Blink", "on");
	break;

    case GX_SIGNAL(IDB_LED_BLINK_BTN, GX_EVENT_TOGGLE_OFF):
	gx_window_event_process(widget, event_ptr);
//	Pmod_Ports[PmodLED]->set(PmodLED, "Blink", "off");
	break;

    case GX_SIGNAL(IDB_S7_AMS_BTN, GX_EVENT_CLICKED):
	SwitchScreens(&s7_window, &ams_window);
	break;

    case GX_SIGNAL(IDB_S7_MAIN_BTN, GX_EVENT_CLICKED):
	SwitchScreens(&s7_window, &main_window);
	break;

    default:
        return gx_window_event_process(widget, event_ptr);
    }
    
    return 0;
}

UINT AlertWindowEventHandler (GX_WINDOW * widget, GX_EVENT * event_ptr)
{
    switch (event_ptr->gx_event_type) {
    default:
        return gx_window_event_process(widget, event_ptr);
    }
}

UINT SplashEventHandler (GX_WINDOW * widget, GX_EVENT * event_ptr)
{
    switch (event_ptr->gx_event_type) {
    case GX_EVENT_SHOW:
    case GX_EVENT_REDRAW:
	gx_system_timer_start(widget, TIME_EVENT_TIMER, 100, 00);
        return gx_window_event_process(widget, event_ptr);
        break;

    case GX_EVENT_TIMER:
	gx_system_timer_stop(widget, TIME_EVENT_TIMER);
	SwitchScreens(&splash, &main_window);
	break;

    default:
        return gx_window_event_process(widget, event_ptr);
    }
    
    return 0;
}

