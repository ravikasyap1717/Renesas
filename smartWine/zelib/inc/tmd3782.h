/*
 * tmd3782.h
 *
 * Created on: Jul 23, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _TMD3782_H_
#define _TMD3782_H_

#include "zelib-i2c.h"

#define ZE_TMD3782_CLEAR	0
#define ZE_TMD3782_RED		1
#define ZE_TMD3782_GREEN	2
#define ZE_TMD3782_BLUE		3
#define ZE_TMD3782_PROXIMITY	4

typedef struct _ze_tmd3782_instance ze_tmd3782_instance_t;

#define _ZE_TMD3782_CTRL_BASE_PROTO_ \
    _ZE_I2C_CTRL_BASE_PROTO_	     \
    uint16_t clear; \
    uint16_t red; \
    uint16_t green; \
    uint16_t blue; \
    uint16_t proximity;

typedef struct {
    _ZE_TMD3782_CTRL_BASE_PROTO_
} ze_tmd3782_ctrl_t;

#define _ZE_TMD3782_CFG_BASE_PROTO_ \
    _ZE_I2C_CFG_BASE_PROTO_ 

typedef struct {
    _ZE_TMD3782_CFG_BASE_PROTO_
} ze_tmd3782_cfg_t;

#define _ZE_TMD3782_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_I2C_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE) 

typedef struct {
    _ZE_TMD3782_API_BASE_PROTO_(ze_tmd3782_instance_t, ze_i2c_api_t)
} ze_tmd3782_api_t;

extern ze_tmd3782_api_t g_ze_tmd3782_api;

struct _ze_tmd3782_instance{
    ze_tmd3782_ctrl_t * p_ctrl;
    ze_tmd3782_cfg_t const * const p_cfg;
    ze_tmd3782_api_t const * const p_api;
};

#endif /* _TMD3782_H_ */
