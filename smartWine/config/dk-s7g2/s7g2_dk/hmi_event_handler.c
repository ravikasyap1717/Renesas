
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

void UpdateGUI(int do_refresh)
{
    GX_EVENT gxe;

    gx_prompt_text_set(&(main_window.main_window_info1), BoardID);
    if (ip_address == 0)
	pretty_ip_address[0] = '\0';
    else
	snprintf(pretty_ip_address, sizeof(pretty_ip_address), "%d.%d.%d.%d",
		 (ip_address >> 24) & 0xff, (ip_address >> 16) & 0xff,
		 (ip_address >> 8) & 0xff, (ip_address >> 0) & 0xff);
    gx_prompt_text_set(&(main_window.main_window_info2), pretty_ip_address);

    if (do_refresh) {
	/** Send event to GUI */
	gxe.gx_event_sender = GX_ID_NONE;
	gxe.gx_event_target = 0;  /* the event is routed to the input focus */
	gxe.gx_event_display_handle = 0;
	gxe.gx_event_type = GX_EVENT_REDRAW;

	gx_system_event_send(&gxe);
    }
}

UINT MainWindowEventHandler (GX_WINDOW * widget, GX_EVENT * event_ptr)
{
    static int do_timer = 1;

    switch (event_ptr->gx_event_type) {
    case GX_EVENT_SHOW:
    case GX_EVENT_REDRAW:
	UpdateGUI(0);
        return gx_window_event_process(widget, event_ptr);
        break;

    case GX_EVENT_TIMER:
	break;

    default:
        return gx_window_event_process(widget, event_ptr);
    }
    
    return 0;
}


