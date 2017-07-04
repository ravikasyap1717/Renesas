/*
 * zelib.h
 *
 * Created on: Jun 23, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _ZELIB_H_
#define _ZELIB_H_

#include <stdarg.h>
#include "bsp_api.h"
#include "r_timer_api.h"
#include "zelib-properties.h"

#define ZE_TIMER_TICKS_PER_SECOND	100
extern volatile uint32_t ze_timer_ticks;

typedef struct _ze_device_ctrl ze_device_ctrl_t;
typedef struct _ze_device_cfg ze_device_cfg_t;
typedef struct _ze_device_api ze_device_api_t;
typedef struct _ze_device_instance ze_device_instance_t;

#define _ZE_CTRL_BASE_PROTO_ \
    char const * name; 

struct _ze_device_ctrl {
    _ZE_CTRL_BASE_PROTO_
};

#define _ZE_CFG_BASE_PROTO_ \
    char const * const name; 

struct _ze_device_cfg {
    _ZE_CFG_BASE_PROTO_
};

#define _ZE_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)  \
    SUPER_TYPE *superclass; \
    ssp_err_t (* open)(INSTANCE_TYPE *this); \
    ssp_err_t (* close)(INSTANCE_TYPE *this); \
    char const * (* name)(INSTANCE_TYPE *this); \
    char const * (* type)(INSTANCE_TYPE *this); \
    char const * (* description)(INSTANCE_TYPE *this); \
    void (* update)(INSTANCE_TYPE *this); \
    unsigned int (* numberProperties)(INSTANCE_TYPE *this); \
    ze_property_type_t (* propertyType)(INSTANCE_TYPE *this, unsigned int index); \
    ze_property_access_t (* propertyAccess)(INSTANCE_TYPE *this, unsigned int index); \
    char const * (* propertyName)(INSTANCE_TYPE *this, unsigned int index); \
    unsigned int (* propertyCount)(INSTANCE_TYPE *this, unsigned int index); \
    ssp_err_t (* getProperty)(INSTANCE_TYPE *this, unsigned int index, void *data); \
    ssp_err_t (* setProperty)(INSTANCE_TYPE *this, unsigned int index, void *data);

struct _ze_device_api {
    _ZE_API_BASE_PROTO_(ze_device_instance_t, void)
};

extern ze_device_api_t g_ze_device_api;

struct _ze_device_instance {
    ze_device_ctrl_t * p_ctrl;
    ze_device_cfg_t const * const p_cfg;
    ze_device_api_t const * const p_api;
};

char *ZE_Property_GetAsString(ze_device_instance_t *this, unsigned int index);
char *ZE_Property_GetAsJSON(ze_device_instance_t *this, unsigned int index);
ssp_err_t _ZE_Property_GetInternal(ze_device_instance_t *thing, ze_property_entry_t *prop, void *data);

void ZE_PostErrorMessage(char *format, ...);

char *ZE_JSON_FindObject(char *name, char *json);

void ZE_Timer_Callback(timer_callback_args_t *args);

#endif /* _ZELIB_H_ */
