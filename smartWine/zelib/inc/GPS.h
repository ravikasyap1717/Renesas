/*
 * gps.h
 *
 * Created on: Aug 3, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _GPS_H_
#define _GPS_H_

#include "zelib-uart.h"
#include "tx_api.h"

#define ZE_GPS_LATITUDE		0
#define ZE_GPS_LONGITUDE	1
#define ZE_GPS_ALTITUDE		2
#define ZE_GPS_TIMESTAMP	3
#define ZE_GPS_DATE		4
#define ZE_GPS_VALID		5

typedef struct _ze_gps_instance ze_gps_instance_t;

#define ZE_GPS_TIMESTAMP_LENGTH		32
#define ZE_GPS_DATE_LENGTH		32
#define ZE_GPS_MAX_NMEA_LINE_LENGTH	256
#define ZE_GPS_MAX_NMEA_ARG_COUNT	32

#define _ZE_GPS_CTRL_BASE_PROTO_ \
    _ZE_UART_CTRL_BASE_PROTO_ \
    double latitude; \
    double longitude; \
    double altitude; \
    char timestamp[ZE_GPS_TIMESTAMP_LENGTH]; \
    char date[ZE_GPS_DATE_LENGTH]; \
    int valid; \
    char buffer[ZE_GPS_MAX_NMEA_LINE_LENGTH]; \
    char *argv[ZE_GPS_MAX_NMEA_ARG_COUNT]; \
    int argc;

typedef struct {
    _ZE_GPS_CTRL_BASE_PROTO_
} ze_gps_ctrl_t;

#define _ZE_GPS_CFG_BASE_PROTO_ \
    _ZE_UART_CFG_BASE_PROTO_

typedef struct {
    _ZE_GPS_CFG_BASE_PROTO_
} ze_gps_cfg_t;

#define _ZE_GPS_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE)	\
    _ZE_UART_API_BASE_PROTO_(INSTANCE_TYPE, SUPER_TYPE) 

typedef struct {
    _ZE_GPS_API_BASE_PROTO_(ze_gps_instance_t, ze_uart_api_t)
} ze_gps_api_t;

extern ze_gps_api_t g_ze_gps_api;

struct _ze_gps_instance{
    ze_gps_ctrl_t * p_ctrl;
    ze_gps_cfg_t const * const p_cfg;
    ze_gps_api_t const * const p_api;
};

#endif /* _GPS_H_ */
