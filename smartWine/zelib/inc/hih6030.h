/*
 * hih6030.h
 *
 * Created on: Aug 15, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _HIH6030_H_
#define _HIH6030_H_

#include "zelib-i2c.h"

#define ZE_HIH6030_TEMPERATURE	0
#define ZE_HIH6030_HUMIDITY	1

typedef struct _ze_hih6030_instance ze_hih6030_instance_t;

#define _ZE_HIH6030_CTRL_BASE_PROTO_ \
    _ZE_I2C_CTRL_BASE_PROTO_ \
    double temperature; \
    double humidity;

typedef struct {
    _ZE_HIH6030_CTRL_BASE_PROTO_
} ze_hih6030_ctrl_t;

#define _ZE_HIH6030_CFG_BASE_PROTO_ \
    _ZE_I2C_CFG_BASE_PROTO_ 

typedef struct {
    _ZE_HIH6030_CFG_BASE_PROTO_
} ze_hih6030_cfg_t;

#define _ZE_HIH6030_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_I2C_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE) 

typedef struct {
    _ZE_HIH6030_API_BASE_PROTO_(ze_hih6030_instance_t, ze_i2c_api_t)
} ze_hih6030_api_t;

extern ze_hih6030_api_t g_ze_hih6030_api;

struct _ze_hih6030_instance{
    ze_hih6030_ctrl_t * p_ctrl;
    ze_hih6030_cfg_t const * const p_cfg;
    ze_hih6030_api_t const * const p_api;
};

#endif /* _HIH6030_H_ */
