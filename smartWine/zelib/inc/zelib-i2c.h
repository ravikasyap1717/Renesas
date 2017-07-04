/*
 * zelib_i2c.h
 *
 * Created on: Jun 23, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _ZELIB_I2C_H_
#define _ZELIB_I2C_H_

#include "zelib.h"
#include "r_sci_i2c.h"

typedef struct _ze_i2c_ctrl ze_i2c_ctrl_t;
typedef struct _ze_i2c_cfg ze_i2c_cfg_t;
typedef struct _ze_i2c_api ze_i2c_api_t;
typedef struct _ze_i2c_instance ze_i2c_instance_t;

#define _ZE_I2C_CTRL_BASE_PROTO_ \
    _ZE_CTRL_BASE_PROTO_  \
    const i2c_master_instance_t *hw_interface; 

struct _ze_i2c_ctrl {
    _ZE_I2C_CTRL_BASE_PROTO_
};

#define _ZE_I2C_CFG_BASE_PROTO_ \
    _ZE_CFG_BASE_PROTO_ \
    const i2c_master_instance_t * const hw_interface; 

struct _ze_i2c_cfg {
    _ZE_I2C_CFG_BASE_PROTO_
};

#define _ZE_I2C_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE) 

struct _ze_i2c_api {
    _ZE_I2C_API_BASE_PROTO_(ze_i2c_instance_t, ze_device_api_t)
};

extern ze_i2c_api_t g_ze_i2c_api;

struct _ze_i2c_instance {
    ze_i2c_ctrl_t * p_ctrl;
    ze_i2c_cfg_t const * const p_cfg;
    ze_i2c_api_t const * const p_api;
};

#endif /* _ZELIB_I2C_H_ */
