/* generated common header file - do not edit */
#ifndef WIFI_COMMON_DATA_H_
#define WIFI_COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "r_rspi.h"
#include "r_spi_api.h"
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "sf_wifi_api.h"
#include "sf_wifi_gt202.h"
#if !SF_WIFI_GT202_CFG_ONCHIP_STACK_SUPPORT
#include "sf_wifi_nsal_api.h"
#endif
#include "nx_api.h"
#include "sf_wifi_nsal_nx.h"

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
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq_pmoda;
#ifdef custom_hw_irq_isr
#define EXTERNAL_IRQ_ON_ICU_CALLBACK_USED_g_external_irq_pmoda (0)
#else
#define EXTERNAL_IRQ_ON_ICU_CALLBACK_USED_g_external_irq_pmoda (1)
#endif
#if EXTERNAL_IRQ_ON_ICU_CALLBACK_USED_g_external_irq_pmoda
void custom_hw_irq_isr(external_irq_callback_args_t * p_args);
#endif
/** sf_wifi on GT202 Wi-Fi Driver instance */
extern sf_wifi_instance_t g_sf_wifi0;
#ifdef NULL
#define SF_WIFI_ON_WIFI_GT202_CALLBACK_USED_g_sf_wifi0 (0)
#else
#define SF_WIFI_ON_WIFI_GT202_CALLBACK_USED_g_sf_wifi0 (1)
#endif
#if SF_WIFI_ON_WIFI_GT202_CALLBACK_USED_g_sf_wifi0
/** Declaration of user callback function. This function MUST be defined in the user application.*/
void NULL(sf_wifi_callback_args_t * p_args);
#endif
#endif /* COMMON_DATA_H_ */
