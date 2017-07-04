/*******************************************************************************/
/*  This file is auto-generated by GUIX Studio. Do not edit this file by hand. */
/*  Modifications to this file should only be made by running the GUIX Studio  */
/*  application and re-generating the application. For more information please */
/*  refer to the GUIX Studio user's guide, or visit our web site at            */
/*  www.expresslogic.com.                                                      */
/*                                                                             */
/*  GUIX Studio Revision 5.0                                                   */
/*  Date (dd.mm.yyyy):  9. 5.2016   Time (hh:mm): 10:10                        */
/*******************************************************************************/


#define GUIX_STUDIO_GENERATED_FILE
#include "SmartWine_resources.h"
#include "SmartWine_specifications.h"

MAIN_WINDOW_CONTROL_BLOCK main_window;

UINT gx_studio_text_button_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent)
{
    UINT status;
    GX_TEXT_BUTTON *button = (GX_TEXT_BUTTON *) control_block;
    GX_TEXT_BUTTON_PROPERTIES *props = (GX_TEXT_BUTTON_PROPERTIES *) info->properties;
    status = gx_text_button_create(button, info->widget_name, parent, props->string_id, info->style, info->widget_id, &info->size);
    if (status == GX_SUCCESS)
    {
        gx_text_button_font_set(button, props->font_id);
        gx_text_button_text_color_set(button, props->normal_text_color_id, props->selected_text_color_id);
    }
    return status;
}

UINT gx_studio_pixelmap_button_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent)
{
    UINT status;
    GX_PIXELMAP_BUTTON *button = (GX_PIXELMAP_BUTTON *) control_block;
    GX_PIXELMAP_BUTTON_PROPERTIES *props = (GX_PIXELMAP_BUTTON_PROPERTIES *) info->properties;
    status = gx_pixelmap_button_create(button, info->widget_name, parent,
               props->normal_pixelmap_id,
               props->selected_pixelmap_id,
               props->disabled_pixelmap_id,
               info->style, info->widget_id, &info->size);
    return status;
}

UINT gx_studio_prompt_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent)
{
    UINT status;
    GX_PROMPT *prompt = (GX_PROMPT *) control_block;
    GX_PROMPT_PROPERTIES *props = (GX_PROMPT_PROPERTIES *) info->properties;
    status = gx_prompt_create(prompt, info->widget_name, parent, props->string_id, info->style, info->widget_id, &info->size);
    if (status == GX_SUCCESS)
    {
        gx_prompt_font_set(prompt, props->font_id);
        gx_prompt_text_color_set(prompt, props->normal_text_color_id, props->selected_text_color_id);
    }
    return status;
}

UINT gx_studio_window_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent)
{
    UINT status;
    GX_WINDOW *window = (GX_WINDOW *) control_block;
    GX_WINDOW_PROPERTIES *props = (GX_WINDOW_PROPERTIES *) info->properties;
    status = gx_window_create(window, info->widget_name, parent, info->style, info->widget_id, &info->size);
    if (status == GX_SUCCESS)
    {
        if (props->wallpaper_id)
        {
            gx_window_wallpaper_set(window, props->wallpaper_id, info->style & GX_STYLE_TILE_WALLPAPER);
        }
    }
    return status;
}
GX_WINDOW_PROPERTIES main_window_properties =
{
    0                                        /* wallpaper pixelmap id          */
};
GX_PIXELMAP_BUTTON_PROPERTIES main_window_pixelmap_button_1_properties =
{
    GX_PIXELMAP_ID_ZEPHYR_LOGO_TEXT_COLOR_272X105, /* normal pixelmap id       */
    0,                                       /* selected pixelmap id           */
    0                                        /* disabled pixelmap id           */
};
GX_PROMPT_PROPERTIES main_window_title_properties =
{
    GX_STRING_ID_STRING_2,                   /* string id                      */
    GX_FONT_ID_BIG,                          /* font id                        */
    GX_COLOR_ID_TEXT,                        /* normal text color              */
    GX_COLOR_ID_SELECTED_TEXT                /* selected text color            */
};
GX_PROMPT_PROPERTIES main_window_info1_properties =
{
    GX_STRING_ID_STRING_10,                  /* string id                      */
    GX_FONT_ID_MEDIUM,                       /* font id                        */
    GX_COLOR_ID_TEXT,                        /* normal text color              */
    GX_COLOR_ID_SELECTED_TEXT                /* selected text color            */
};
GX_PROMPT_PROPERTIES main_window_info2_properties =
{
    GX_STRING_ID_STRING_11,                  /* string id                      */
    GX_FONT_ID_NORMAL,                       /* font id                        */
    GX_COLOR_ID_TEXT,                        /* normal text color              */
    GX_COLOR_ID_SELECTED_TEXT                /* selected text color            */
};
GX_TEXT_BUTTON_PROPERTIES main_window_AMS_properties =
{
    GX_STRING_ID_STRING_8,                   /* string id                      */
    GX_FONT_ID_MEDIUM,                       /* font id                        */
    GX_COLOR_ID_BTN_TEXT,                    /* normal text color              */
    GX_COLOR_ID_BTN_TEXT                     /* selected text color            */
};
GX_TEXT_BUTTON_PROPERTIES main_window_S7_properties =
{
    GX_STRING_ID_STRING_9,                   /* string id                      */
    GX_FONT_ID_MEDIUM,                       /* font id                        */
    GX_COLOR_ID_BTN_TEXT,                    /* normal text color              */
    GX_COLOR_ID_BTN_TEXT                     /* selected text color            */
};

GX_CONST GX_STUDIO_WIDGET main_window_S7_define =
{
    "S7",
    GX_TYPE_TEXT_BUTTON,                     /* widget type                    */
    GX_ID_NONE,                              /* widget id                      */
    #if defined(GX_WIDGET_USER_DATA)
    0,                                       /* user data                      */
    #endif
    GX_STYLE_BORDER_THICK|GX_STYLE_ENABLED|GX_STYLE_TEXT_CENTER,   /* style flags */
    GX_STATUS_ACCEPTS_FOCUS,                 /* status flags                   */
    120,                                     /* control block size             */
    GX_COLOR_ID_BTN_LOWER,                   /* normal color id                */
    GX_COLOR_ID_BTN_UPPER,                   /* selected color id              */
    gx_studio_text_button_create,            /* create function                */
    GX_NULL,                                 /* drawing function override      */
    GX_NULL,                                 /* event function override        */
    {280, 210, 359, 241},                    /* widget size                    */
    GX_NULL,                                 /* no next widget                 */
    GX_NULL,                                 /* no child widgets               */ 
    (GX_WIDGET *) &main_window.main_window_S7, /* control block                */
    (void *) &main_window_S7_properties      /* extended properties            */
};

GX_CONST GX_STUDIO_WIDGET main_window_AMS_define =
{
    "AMS",
    GX_TYPE_TEXT_BUTTON,                     /* widget type                    */
    GX_ID_NONE,                              /* widget id                      */
    #if defined(GX_WIDGET_USER_DATA)
    0,                                       /* user data                      */
    #endif
    GX_STYLE_BORDER_THICK|GX_STYLE_ENABLED|GX_STYLE_TEXT_CENTER,   /* style flags */
    GX_STATUS_ACCEPTS_FOCUS,                 /* status flags                   */
    120,                                     /* control block size             */
    GX_COLOR_ID_BTN_LOWER,                   /* normal color id                */
    GX_COLOR_ID_BTN_UPPER,                   /* selected color id              */
    gx_studio_text_button_create,            /* create function                */
    GX_NULL,                                 /* drawing function override      */
    GX_NULL,                                 /* event function override        */
    {120, 210, 199, 241},                    /* widget size                    */
    &main_window_S7_define,                  /* next widget definition         */
    GX_NULL,                                 /* no child widgets               */ 
    (GX_WIDGET *) &main_window.main_window_AMS, /* control block               */
    (void *) &main_window_AMS_properties     /* extended properties            */
};

GX_CONST GX_STUDIO_WIDGET main_window_info2_define =
{
    "info2",
    GX_TYPE_PROMPT,                          /* widget type                    */
    IDB_INFO_TEXT,                           /* widget id                      */
    #if defined(GX_WIDGET_USER_DATA)
    0,                                       /* user data                      */
    #endif
    GX_STYLE_BORDER_NONE|GX_STYLE_ENABLED|GX_STYLE_TEXT_CENTER,   /* style flags */
    GX_STATUS_ACCEPTS_FOCUS,                 /* status flags                   */
    116,                                     /* control block size             */
    GX_COLOR_ID_SELECTED_TEXT,               /* normal color id                */
    GX_COLOR_ID_SELECTED_FILL,               /* selected color id              */
    gx_studio_prompt_create,                 /* create function                */
    GX_NULL,                                 /* drawing function override      */
    GX_NULL,                                 /* event function override        */
    {40, 244, 439, 267},                     /* widget size                    */
    &main_window_AMS_define,                 /* next widget definition         */
    GX_NULL,                                 /* no child widgets               */ 
    (GX_WIDGET *) &main_window.main_window_info2, /* control block             */
    (void *) &main_window_info2_properties   /* extended properties            */
};

GX_CONST GX_STUDIO_WIDGET main_window_info1_define =
{
    "info1",
    GX_TYPE_PROMPT,                          /* widget type                    */
    IDB_INFO_TEXT,                           /* widget id                      */
    #if defined(GX_WIDGET_USER_DATA)
    0,                                       /* user data                      */
    #endif
    GX_STYLE_BORDER_NONE|GX_STYLE_ENABLED|GX_STYLE_TEXT_CENTER,   /* style flags */
    GX_STATUS_ACCEPTS_FOCUS,                 /* status flags                   */
    116,                                     /* control block size             */
    GX_COLOR_ID_SELECTED_TEXT,               /* normal color id                */
    GX_COLOR_ID_SELECTED_FILL,               /* selected color id              */
    gx_studio_prompt_create,                 /* create function                */
    GX_NULL,                                 /* drawing function override      */
    GX_NULL,                                 /* event function override        */
    {40, 180, 439, 203},                     /* widget size                    */
    &main_window_info2_define,               /* next widget definition         */
    GX_NULL,                                 /* no child widgets               */ 
    (GX_WIDGET *) &main_window.main_window_info1, /* control block             */
    (void *) &main_window_info1_properties   /* extended properties            */
};

GX_CONST GX_STUDIO_WIDGET main_window_title_define =
{
    "title",
    GX_TYPE_PROMPT,                          /* widget type                    */
    GX_ID_NONE,                              /* widget id                      */
    #if defined(GX_WIDGET_USER_DATA)
    0,                                       /* user data                      */
    #endif
    GX_STYLE_BORDER_NONE|GX_STYLE_ENABLED|GX_STYLE_TEXT_CENTER,   /* style flags */
    GX_STATUS_ACCEPTS_FOCUS,                 /* status flags                   */
    116,                                     /* control block size             */
    GX_COLOR_ID_SELECTED_TEXT,               /* normal color id                */
    GX_COLOR_ID_SELECTED_FILL,               /* selected color id              */
    gx_studio_prompt_create,                 /* create function                */
    GX_NULL,                                 /* drawing function override      */
    GX_NULL,                                 /* event function override        */
    {140, 140, 339, 171},                    /* widget size                    */
    &main_window_info1_define,               /* next widget definition         */
    GX_NULL,                                 /* no child widgets               */ 
    (GX_WIDGET *) &main_window.main_window_title, /* control block             */
    (void *) &main_window_title_properties   /* extended properties            */
};

GX_CONST GX_STUDIO_WIDGET main_window_pixelmap_button_1_define =
{
    "pixelmap_button_1",
    GX_TYPE_PIXELMAP_BUTTON,                 /* widget type                    */
    GX_ID_NONE,                              /* widget id                      */
    #if defined(GX_WIDGET_USER_DATA)
    0,                                       /* user data                      */
    #endif
    GX_STYLE_BORDER_NONE|GX_STYLE_ENABLED,   /* style flags                    */
    GX_STATUS_ACCEPTS_FOCUS,                 /* status flags                   */
    112,                                     /* control block size             */
    GX_COLOR_ID_BTN_LOWER,                   /* normal color id                */
    GX_COLOR_ID_BTN_UPPER,                   /* selected color id              */
    gx_studio_pixelmap_button_create,        /* create function                */
    GX_NULL,                                 /* drawing function override      */
    GX_NULL,                                 /* event function override        */
    {104, 20, 375, 124},                     /* widget size                    */
    &main_window_title_define,               /* next widget definition         */
    GX_NULL,                                 /* no child widgets               */ 
    (GX_WIDGET *) &main_window.main_window_pixelmap_button_1, /* control block */
    (void *) &main_window_pixelmap_button_1_properties /* extended properties  */
};

GX_CONST GX_STUDIO_WIDGET main_window_define =
{
    "main_window",
    GX_TYPE_WINDOW,                          /* widget type                    */
    GX_ID_NONE,                              /* widget id                      */
    #if defined(GX_WIDGET_USER_DATA)
    0,                                       /* user data                      */
    #endif
    GX_STYLE_BORDER_NONE,                    /* style flags                    */
    GX_STATUS_ACCEPTS_FOCUS,                 /* status flags                   */
    132,                                     /* control block size             */
    GX_COLOR_ID_SELECTED_TEXT,               /* normal color id                */
    GX_COLOR_ID_SELECTED_FILL,               /* selected color id              */
    gx_studio_window_create,                 /* create function                */
    GX_NULL,                                 /* drawing function override      */
    (UINT (*)(GX_WIDGET *, GX_EVENT *)) MainWindowEventHandler, /* event function override */
    {0, 0, 479, 271},                        /* widget size                    */
    GX_NULL,                                 /* next widget                    */
    &main_window_pixelmap_button_1_define,   /* child widget                   */
    (GX_WIDGET *) &main_window,              /* control block                  */
    (void *) &main_window_properties         /* extended properties            */
};
GX_CONST GX_STUDIO_WIDGET *SmartWine_widget_table[] =
{
    &main_window_define,
    GX_NULL
};

GX_WIDGET *gx_studio_widget_create(GX_CONST GX_STUDIO_WIDGET *definition, GX_WIDGET *parent)
{
    UINT status = GX_SUCCESS;
    GX_WIDGET *widget = GX_NULL;

    while(definition && status == GX_SUCCESS)
    {
        if (definition->create_function)
        {
            if (definition->style & GX_STYLE_DYNAMICALLY_ALLOCATED)
            {
                status = gx_widget_allocate(&widget, definition->control_block_size);
                if (status != GX_SUCCESS)
                {
                    return GX_NULL;
                }
            }
            else
            {
                widget = definition->control_block;
            }
            status = definition->create_function(definition, widget, parent);

            if (status == GX_SUCCESS)
            {
                gx_widget_fill_color_set(widget, definition->normal_fill_color_id, definition->selected_fill_color_id);

                if (!(definition->status & GX_STATUS_ACCEPTS_FOCUS))
                {
                    gx_widget_status_remove(widget, GX_STATUS_ACCEPTS_FOCUS);
                }

                if (definition->draw_function)
                {
                    gx_widget_draw_set(widget, definition->draw_function);
                }
                if (definition->event_function)
                {
                    gx_widget_event_process_set(widget, definition->event_function);
                }

                #if defined(GX_WIDGET_USER_DATA)
                widget->gx_widget_user_data = definition->user_data;
                #endif

                if (definition->child_widget)
                {
                    gx_studio_widget_create(definition->child_widget, widget);
                }
            }
        }
        definition = definition->next_widget;
    }
    return widget;
}

UINT gx_studio_named_widget_create(char *name, GX_WIDGET *parent, GX_WIDGET **new_widget)
{
    UINT status = GX_FAILURE;
    UINT index = 0;
    GX_CONST GX_STUDIO_WIDGET *entry;
    GX_WIDGET *control_block = GX_NULL;

    while(1)
    {
        entry =  SmartWine_widget_table[index];
        if (!entry)
        {
            break;
        }
        if (!strcmp(name, entry->widget_name))
        {
            control_block = gx_studio_widget_create(entry, parent);
            break;
        }
        index++;
    }

    if (new_widget)
    {
        *new_widget = control_block;
    }
    if (control_block != GX_NULL)
    {
        status = GX_SUCCESS;
    }

    return status;
}


GX_DISPLAY display_1_control_block;
GX_CANVAS  display_1_canvas_control_block;
GX_WINDOW_ROOT display_1_root_window;

GX_DISPLAY display_1_control_block;
GX_CANVAS  display_1_canvas_control_block;
GX_WINDOW_ROOT display_1_root_window;
extern GX_CONST GX_THEME *display_1_theme_table[];
extern GX_CONST CHAR **display_1_language_table[];

GX_STUDIO_DISPLAY_INFO SmartWine_display_table[1] =
{
    {
    "display_1",
    "display_1_canvas",
    display_1_theme_table,
    display_1_language_table,
    DISPLAY_1_LANGUAGE_TABLE_SIZE,
    DISPLAY_1_STRING_TABLE_SIZE,
    480,                                     /* x resolution                   */
    272,                                     /* y resolution                   */
    &display_1_control_block,
    &display_1_canvas_control_block,
    &display_1_root_window,
    GX_NULL,                                 /* canvas memory area             */
    261120                                   /* canvas memory size in bytes    */
    }
};

UINT gx_studio_display_configure(USHORT display, UINT (*driver)(GX_DISPLAY *),
    USHORT language, USHORT theme, GX_WINDOW_ROOT **return_root)
{
    GX_CONST GX_THEME *theme_ptr;
    GX_RECTANGLE size;

    GX_STUDIO_DISPLAY_INFO *display_info = &SmartWine_display_table[display];


/* create the requested display                                                */

    gx_display_create(display_info->display,
                      display_info->name,
                      driver,
                      display_info->x_resolution,
                      display_info->y_resolution);


/* install the request theme                                                   */

    theme_ptr = SmartWine_display_table[display].theme_table[theme];
    gx_display_color_table_set(display_info->display, theme_ptr->theme_color_table, theme_ptr->theme_color_table_size);

/* install the color palette if required                                       */
    if (display_info->display->gx_display_driver_palette_set &&
        theme_ptr->theme_palette != NULL)
    {
        display_info->display->gx_display_driver_palette_set(display_info->display, theme_ptr->theme_palette, theme_ptr->theme_palette_size);
    }

    gx_display_font_table_set(display_info->display, theme_ptr->theme_font_table, theme_ptr->theme_font_table_size);
    gx_display_pixelmap_table_set(display_info->display, theme_ptr->theme_pixelmap_table, theme_ptr->theme_pixelmap_table_size);
    gx_system_language_table_set((GX_CHAR ***) display_info->language_table, display_info->language_table_size, display_info->string_table_size);
    gx_system_active_language_set(language);
    gx_system_scroll_appearance_set(theme_ptr->theme_vertical_scroll_style, (GX_SCROLLBAR_APPEARANCE *) &theme_ptr->theme_vertical_scrollbar_appearance);
    gx_system_scroll_appearance_set(theme_ptr->theme_horizontal_scroll_style, (GX_SCROLLBAR_APPEARANCE *) &theme_ptr->theme_horizontal_scrollbar_appearance);

/* create the canvas for this display                                          */

    gx_canvas_create(display_info->canvas,
                     display_info->canvas_name,
                     display_info->display,
                     GX_CANVAS_MANAGED | GX_CANVAS_VISIBLE,
                     display_info->x_resolution,
                     display_info->y_resolution,
                     display_info->canvas_memory,
                     display_info->canvas_memory_size);

/* Create the root window for this canvas                                      */

    gx_utility_rectangle_define(&size,
                                0, 0,
                                display_info->x_resolution - 1,
                                display_info->y_resolution - 1);

    gx_window_root_create(display_info->root_window,
                          display_info->name,
                          display_info->canvas, GX_STYLE_NONE, 0, &size);
    if (return_root)
    {
        *return_root = display_info->root_window;
    }
    return GX_SUCCESS;
}
#undef GUIX_STUDIO_GENERATED_FILE
