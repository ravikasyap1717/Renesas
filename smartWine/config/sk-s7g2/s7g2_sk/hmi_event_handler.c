
#include "Pmod.h"

#include "gx_api.h"

#include "SmartWine_resources.h"
#include "SmartWine_specifications.h"

#include <stdio.h>

/** Pointer to the Root window */
extern GX_WINDOW_ROOT * p_window_root;

#define TIME_EVENT_TIMER     (100)

extern char BoardID[];
extern uint32_t ip_address;
static char pretty_ip_address[24];

void SendRefresh();
void UpdateGUI(int do_refresh);
void UpdateS7Window(int do_refresh);
void UpdateAMSWindow(int do_refresh);
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

void UpdateGUI(int do_refresh)
{
    gx_prompt_text_set(&(main_window.main_window_info1), BoardID);
    if (ip_address == 0)
	pretty_ip_address[0] = '\0';
    else
	snprintf(pretty_ip_address, sizeof(pretty_ip_address), "%lu.%lu.%lu.%lu",
		 (ip_address >> 24) & 0xff, (ip_address >> 16) & 0xff,
		 (ip_address >> 8) & 0xff, (ip_address >> 0) & 0xff);
    gx_prompt_text_set(&(main_window.main_window_info2), pretty_ip_address);

    if (do_refresh)
	SendRefresh();
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

    case GX_SIGNAL(IDB_MAIN_S7_BTN, GX_EVENT_CLICKED):
	SwitchScreens(&main_window, &s7_window);
	break;

    default:
        return gx_window_event_process(widget, event_ptr);
    }
    
    return 0;
}

void UpdateAMSWindow(int do_refresh)
{
    static char s1[16];
    static char s2[16];

    if (Pmod_Ports[PmodB] != NULL && Pmod_Ports[PmodB]->get != NULL) {
	sprintf(s1, "%sF", Pmod_Ports[PmodB]->get(PmodB, 0));
	gx_prompt_text_set(&(ams_window.ams_window_temperature_value), s1);

	sprintf(s2, "%s%%", Pmod_Ports[PmodB]->get(PmodB, 1));
	gx_prompt_text_set(&(ams_window.ams_window_humidity_value), s2);
    }

    if (do_refresh)
	SendRefresh();
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

    case GX_SIGNAL(IDB_AMS_S7_BTN, GX_EVENT_CLICKED):
	SwitchScreens(&ams_window, &s7_window);
	break;

    default:
        return gx_window_event_process(widget, event_ptr);
    }
    
    return 0;
}

void UpdateS7Window(int do_refresh)
{
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

    if (do_refresh)
	SendRefresh();
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
	Pmod_Ports[PmodLED]->set(PmodLED, "LED1", "on");
	break;

    case GX_SIGNAL(IDB_LED1_BTN, GX_EVENT_TOGGLE_OFF):
	gx_window_event_process(widget, event_ptr);
	Pmod_Ports[PmodLED]->set(PmodLED, "LED1", "off");
	break;

    case GX_SIGNAL(IDB_LED2_BTN, GX_EVENT_TOGGLE_ON):
	gx_window_event_process(widget, event_ptr);
	Pmod_Ports[PmodLED]->set(PmodLED, "LED2", "on");
	break;

    case GX_SIGNAL(IDB_LED2_BTN, GX_EVENT_TOGGLE_OFF):
	gx_window_event_process(widget, event_ptr);
	Pmod_Ports[PmodLED]->set(PmodLED, "LED2", "off");
	break;

    case GX_SIGNAL(IDB_LED3_BTN, GX_EVENT_TOGGLE_ON):
	gx_window_event_process(widget, event_ptr);
	Pmod_Ports[PmodLED]->set(PmodLED, "LED3", "on");
	break;

    case GX_SIGNAL(IDB_LED3_BTN, GX_EVENT_TOGGLE_OFF):
	gx_window_event_process(widget, event_ptr);
	Pmod_Ports[PmodLED]->set(PmodLED, "LED3", "off");
	break;

    case GX_SIGNAL(IDB_LED_BLINK_BTN, GX_EVENT_TOGGLE_ON):
	gx_window_event_process(widget, event_ptr);
	Pmod_Ports[PmodLED]->set(PmodLED, "Blink", "on");
	break;

    case GX_SIGNAL(IDB_LED_BLINK_BTN, GX_EVENT_TOGGLE_OFF):
	gx_window_event_process(widget, event_ptr);
	Pmod_Ports[PmodLED]->set(PmodLED, "Blink", "off");
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
