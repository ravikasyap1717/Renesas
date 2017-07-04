/*
 * cat1.h
 *
 * Created on: Jun 23, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _CAT1_H_
#define _CAT1_H_

#include "zelib-uart.h"
#include "tx_api.h"

#define ZE_CAT1_STRENGTH	0
#define ZE_CAT1_READY		1
#define ZE_CAT1_ERRORS		2
#define ZE_CAT1_TIMEOUTS	3

typedef struct _ze_cat1_instance ze_cat1_instance_t;

#define _ZE_CAT1_CTRL_BASE_PROTO_ \
    _ZE_UART_CTRL_BASE_PROTO_ \
    int strength; \
    bool modem_ready; \
    TX_SEMAPHORE lock; \
    char buffer[512]; \
    int error_count; \
    bool connected; \
    char SIS_buffer[128]; \
    uint32_t recv_timeout_cnt; \
    uint32_t wait4_timeout_cnt;

typedef struct {
    _ZE_CAT1_CTRL_BASE_PROTO_
} ze_cat1_ctrl_t;

#define _ZE_CAT1_CFG_BASE_PROTO_ \
    _ZE_UART_CFG_BASE_PROTO_ \
    ioport_port_pin_t power; \
    ioport_port_pin_t reset; \
    ioport_port_pin_t dtr;

typedef struct {
    _ZE_CAT1_CFG_BASE_PROTO_
} ze_cat1_cfg_t;

#define _ZE_CAT1_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_UART_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)			       \
    ssp_err_t (*connect)(INSTANCE_TYPE *this, char *server, unsigned int port); \
    int (*send)(INSTANCE_TYPE *this, char *buffer, size_t length); \
    int (*recv)(INSTANCE_TYPE *this, char *buffer, size_t length); \
    ssp_err_t (*disconnect)(INSTANCE_TYPE *this); \
    char * (*stars)(INSTANCE_TYPE *this);

typedef struct {
    _ZE_CAT1_API_BASE_PROTO_(ze_cat1_instance_t, ze_uart_api_t)
} ze_cat1_api_t;

extern ze_cat1_api_t g_ze_cat1_api;

struct _ze_cat1_instance{
    ze_cat1_ctrl_t * p_ctrl;
    ze_cat1_cfg_t const * const p_cfg;
    ze_cat1_api_t const * const p_api;
};

#endif /* _CAT1_H_ */
