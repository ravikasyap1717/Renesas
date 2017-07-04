/*
 * ms5637.h
 *
 * Created on: Aug 15, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _MS5637_H_
#define _MS5637_H_

#include "zelib-i2c.h"

#define ZE_MS5637_TEMPERATURE	0
#define ZE_MS5637_PRESSURE	1

typedef struct _ze_ms5637_instance ze_ms5637_instance_t;

#define _ZE_MS5637_CTRL_BASE_PROTO_ \
    _ZE_I2C_CTRL_BASE_PROTO_ \
    double temperature; \
    double pressure; \
    uint64_t C[7];

typedef struct {
    _ZE_MS5637_CTRL_BASE_PROTO_
} ze_ms5637_ctrl_t;

#define _ZE_MS5637_CFG_BASE_PROTO_ \
    _ZE_I2C_CFG_BASE_PROTO_ 

typedef struct {
    _ZE_MS5637_CFG_BASE_PROTO_
} ze_ms5637_cfg_t;

#define _ZE_MS5637_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_I2C_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE) 

typedef struct {
    _ZE_MS5637_API_BASE_PROTO_(ze_ms5637_instance_t, ze_i2c_api_t)
} ze_ms5637_api_t;

extern ze_ms5637_api_t g_ze_ms5637_api;

struct _ze_ms5637_instance{
    ze_ms5637_ctrl_t * p_ctrl;
    ze_ms5637_cfg_t const * const p_cfg;
    ze_ms5637_api_t const * const p_api;
};

#endif /* _MS5637_H_ */
