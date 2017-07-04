/*
 * bmc150acc.h
 *
 * Created on: Aug 16, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _BMC150ACC_H_
#define _BMC150ACC_H_

#include "zelib-i2c.h"

#define ZE_BMC150ACC_TEMPERATURE	0
#define ZE_BMC150ACC_X			1
#define ZE_BMC150ACC_Y			2
#define ZE_BMC150ACC_Z			3

typedef struct _ze_bmc150acc_instance ze_bmc150acc_instance_t;

#define ZE_BMC150ACC_HISTORY_COUNT	5

#define _ZE_BMC150ACC_CTRL_BASE_PROTO_ \
    _ZE_I2C_CTRL_BASE_PROTO_ \
    double temperature; \
    int x_accel; \
    int y_accel; \
    int z_accel; \
    int x_history[ZE_BMC150ACC_HISTORY_COUNT]; \
    int y_history[ZE_BMC150ACC_HISTORY_COUNT]; \
    int z_history[ZE_BMC150ACC_HISTORY_COUNT]; \
    int history_insert;

typedef struct {
    _ZE_BMC150ACC_CTRL_BASE_PROTO_
} ze_bmc150acc_ctrl_t;

#define _ZE_BMC150ACC_CFG_BASE_PROTO_ \
    _ZE_I2C_CFG_BASE_PROTO_ 

typedef struct {
    _ZE_BMC150ACC_CFG_BASE_PROTO_
} ze_bmc150acc_cfg_t;

#define _ZE_BMC150ACC_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_I2C_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE) 

typedef struct {
    _ZE_BMC150ACC_API_BASE_PROTO_(ze_bmc150acc_instance_t, ze_i2c_api_t)
} ze_bmc150acc_api_t;

extern ze_bmc150acc_api_t g_ze_bmc150acc_api;

struct _ze_bmc150acc_instance{
    ze_bmc150acc_ctrl_t * p_ctrl;
    ze_bmc150acc_cfg_t const * const p_cfg;
    ze_bmc150acc_api_t const * const p_api;
};

#endif /* _BMC150ACC_H_ */
