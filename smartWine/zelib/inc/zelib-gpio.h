/*
 * zelib_gpio.h
 *
 * Created on: Aug 17, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _ZELIB_GPIO_H_
#define _ZELIB_GPIO_H_

#include "zelib.h"
#include "tx_api.h"
#include "r_ioport.h"
#include "r_ioport_api.h"

#define ZE_GPIO_STATE		0
#define ZE_GPIO_PIN		1
#define ZE_GPIO_DIRECTION	2
#define ZE_GPIO_HIGH_LEVEL	3

typedef struct _ze_gpio_ctrl ze_gpio_ctrl_t;
typedef struct _ze_gpio_cfg ze_gpio_cfg_t;
typedef struct _ze_gpio_api ze_gpio_api_t;
typedef struct _ze_gpio_instance ze_gpio_instance_t;

#define _ZE_GPIO_CTRL_BASE_PROTO_ \
    _ZE_CTRL_BASE_PROTO_  \
    TX_SEMAPHORE lock; \
    uint32_t state; \
    ioport_port_pin_t pin; \
    ioport_direction_t direction; \
    ioport_level_t high; \
    ioport_level_t low;

struct _ze_gpio_ctrl {
    _ZE_GPIO_CTRL_BASE_PROTO_
};

#define _ZE_GPIO_CFG_BASE_PROTO_ \
    _ZE_CFG_BASE_PROTO_ \
    ioport_port_pin_t pin; \
    ioport_direction_t direction; \
    ioport_level_t high;

struct _ze_gpio_cfg {
    _ZE_GPIO_CFG_BASE_PROTO_
};

#define _ZE_GPIO_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE) 

struct _ze_gpio_api {
    _ZE_GPIO_API_BASE_PROTO_(ze_gpio_instance_t, ze_device_api_t)
};

extern ze_gpio_api_t g_ze_gpio_api;

struct _ze_gpio_instance {
    ze_gpio_ctrl_t * p_ctrl;
    ze_gpio_cfg_t const * const p_cfg;
    ze_gpio_api_t const * const p_api;
};

#endif /* _ZELIB_GPIO_H_ */
