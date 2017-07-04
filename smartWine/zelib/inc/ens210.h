/*
 * ens210.h
 *
 * Created on: Jun 23, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _ENS210_H_
#define _ENS210_H_

#include "zelib-i2c.h"

#define ZE_ENS210_TEMPERATURE	0
#define ZE_ENS210_HUMIDITY	1

typedef struct _ze_ens210_instance ze_ens210_instance_t;

#define _ZE_ENS210_CTRL_BASE_PROTO_ \
    _ZE_I2C_CTRL_BASE_PROTO_ \
    double temperature; \
    double humidity;

typedef struct {
    _ZE_ENS210_CTRL_BASE_PROTO_
} ze_ens210_ctrl_t;

#define _ZE_ENS210_CFG_BASE_PROTO_ \
    _ZE_I2C_CFG_BASE_PROTO_ 

typedef struct {
    _ZE_ENS210_CFG_BASE_PROTO_
} ze_ens210_cfg_t;

#define _ZE_ENS210_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_I2C_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE) 

typedef struct {
    _ZE_ENS210_API_BASE_PROTO_(ze_ens210_instance_t, ze_i2c_api_t)
} ze_ens210_api_t;

extern ze_ens210_api_t g_ze_ens210_api;

struct _ze_ens210_instance{
    ze_ens210_ctrl_t * p_ctrl;
    ze_ens210_cfg_t const * const p_cfg;
    ze_ens210_api_t const * const p_api;
};

#endif /* _ENS210_H_ */
