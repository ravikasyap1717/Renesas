/* generated thread header file - do not edit */
#ifndef NETWORK_THREAD_H_
#define NETWORK_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
void network_thread_entry(void);
#include "r_rspi.h"
#include "r_spi_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
extern const spi_cfg_t g_spi0_cfg;
/** SPI on RSPI Instance. */
extern const spi_instance_t g_spi0;
#ifdef NULL
#define spi_on_rspi_CALLBACK_USED_g_spi0 (0)
#else
#define spi_on_rspi_CALLBACK_USED_g_spi0 (1)
#endif
#if spi_on_rspi_CALLBACK_USED_g_spi0
void NULL(spi_callback_args_t * p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* NETWORK_THREAD_H_ */
