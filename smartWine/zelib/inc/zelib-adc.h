/*
 * zelib_adc.h
 *
 * Created on: Aug 17, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _ZELIB_ADC_H_
#define _ZELIB_ADC_H_

#include "zelib.h"
#include "tx_api.h"
#include "r_adc.h"
#include "r_adc_api.h"

#define ZE_ADC_VALUE		0
#define ZE_ADC_CHANNEL		1

typedef struct _ze_adc_ctrl ze_adc_ctrl_t;
typedef struct _ze_adc_cfg ze_adc_cfg_t;
typedef struct _ze_adc_api ze_adc_api_t;
typedef struct _ze_adc_instance ze_adc_instance_t;

#define _ZE_ADC_CTRL_BASE_PROTO_ \
    _ZE_CTRL_BASE_PROTO_  \
    TX_SEMAPHORE lock; \
    const adc_instance_t *hw_interface;  \
    adc_register_t channel; \
    adc_data_size_t value;

struct _ze_adc_ctrl {
    _ZE_ADC_CTRL_BASE_PROTO_
};

#define _ZE_ADC_CFG_BASE_PROTO_ \
    _ZE_CFG_BASE_PROTO_ \
    const adc_instance_t * const hw_interface; \
    adc_register_t channel;

struct _ze_adc_cfg {
    _ZE_ADC_CFG_BASE_PROTO_
};

#define _ZE_ADC_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE) 

struct _ze_adc_api {
    _ZE_ADC_API_BASE_PROTO_(ze_adc_instance_t, ze_device_api_t)
};

extern ze_adc_api_t g_ze_adc_api;

struct _ze_adc_instance {
    ze_adc_ctrl_t * p_ctrl;
    ze_adc_cfg_t const * const p_cfg;
    ze_adc_api_t const * const p_api;
};

#endif /* _ZELIB_ADC_H_ */
