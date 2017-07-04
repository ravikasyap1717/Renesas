/*
 * zelib-uart.h
 *
 * Created on: Jun 23, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _ZELIB_UART_H_
#define _ZELIB_UART_H_

#include "zelib.h"
#include "r_uart_api.h"
#include <setjmp.h>

typedef struct _ze_uart_ctrl ze_uart_ctrl_t;
typedef struct _ze_uart_cfg ze_uart_cfg_t;
typedef struct _ze_uart_api ze_uart_api_t;
typedef struct _ze_uart_instance ze_uart_instance_t;

#ifndef ZE_CIRCBUF_BUFSIZE
#define ZE_CIRCBUF_BUFSIZE	4096
#endif

#ifndef ZE_UART_READ_TIMEOUT_SECONDS
#define ZE_UART_READ_TIMEOUT_SECONDS	5
#endif

typedef struct {
    uint8_t data[ZE_CIRCBUF_BUFSIZE];
    uint16_t in;
    uint16_t out;
    uint32_t dropped;
} ze_circbuf_t;

void ze_CircBufInit(ze_circbuf_t *cb);
int ze_CircBufIsEmpty(ze_circbuf_t *cb);
int ze_CircBufEnque(ze_circbuf_t *cb, uint8_t x);
int ze_CircBufDequeue(ze_circbuf_t *cb, uint8_t *x);

#define _ZE_UART_CFG_BASE_PROTO_ \
    _ZE_CFG_BASE_PROTO_ \
    uart_instance_t * const hw_interface;  \
    ioport_port_pin_t rts;

struct _ze_uart_cfg {
    _ZE_UART_CFG_BASE_PROTO_
};

/*
  We have to change some of the uart_cfg_t fields before calling open. Since SSP 
   defines the uart_config_t instance as const, we have to make our own copy
   that we can change.
   */
#define _ZE_UART_CTRL_BASE_PROTO_ \
    _ZE_CTRL_BASE_PROTO_ \
    ze_uart_cfg_t my_cfg; \
    uart_cfg_t uart_cfg; \
    uart_ctrl_t uart_ctrl; \
    ze_circbuf_t cb; \
    volatile uint8_t tx_busy; \
    jmp_buf timeout_env; \
    int timeout_set; \
    uint32_t rx_overflow_cnt;

struct _ze_uart_ctrl {
    _ZE_UART_CTRL_BASE_PROTO_
};

#define _ZE_UART_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)				     \
    size_t (*read)(INSTANCE_TYPE *this, void *buffer, size_t count); \
    size_t (*write)(INSTANCE_TYPE *this, void *buffer, size_t count); \
    size_t (*readable)(INSTANCE_TYPE *this); \
    char *(*gets)(INSTANCE_TYPE *this, char *buffer, size_t count);

struct _ze_uart_api {
    _ZE_UART_API_BASE_PROTO_(ze_uart_instance_t, ze_device_api_t)
};

extern ze_uart_api_t g_ze_uart_api;

struct _ze_uart_instance {
    ze_uart_ctrl_t * const p_ctrl;
    ze_uart_cfg_t const * const p_cfg;
    ze_uart_api_t const * const p_api;
};

void ZE_Uart_RTS(uint32_t channel, uint32_t level);

#endif /* _ZELIB_UART_H_ */
