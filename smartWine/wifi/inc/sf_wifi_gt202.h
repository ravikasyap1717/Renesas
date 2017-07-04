/***********************************************************************************************************************
 * Copyright [2015] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * File Name    : sf_wifi_gt202.h
 * Description  : RTOS-integrated Wi-Fi Framework example. Implementation is Atheros Wi-Fi Driver interface.
 **********************************************************************************************************************/

#ifndef SF_WIFI_GT202_H
#define SF_WIFI_GT202_H

/*******************************************************************************************************************//**
 * @ingroup SF_Library
 * @defgroup SF_WIFI_GT202 Wi-Fi Framework Example using Atheros
 * @brief RTOS-integrated Wi-Fi Framework example. Implementation of Atheros Wi-Fi Driver.
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <sf_wifi_gt202_cfg.h>
#include "r_ioport_api.h"
#include "r_spi_api.h"
#include "r_external_irq_api.h"
/** Wi-Fi Interface. */
#include "sf_wifi_api.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/** Version of code that implements the API defined in this file */
#define SF_WIFI_GT202_CODE_VERSION_MAJOR (1)
#define SF_WIFI_GT202_CODE_VERSION_MINOR (0)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Extension structure for this Implementation. Each implementation can have its own extension structure. For example
    one implementation may use RSPI for communicating with the Wi-Fi chip while another may use SDIO. */
typedef struct st_sf_wifi_on_gt202_cfg
{
    spi_instance_t          const * p_lower_lvl_spi;       ///< SPI Interface used for Wi-Fi communications
    external_irq_instance_t const * p_lower_lvl_icu;       ///< ICU Interface used for Wi-Fi communications
    ioport_port_pin_t               pin_reset;             ///< Port pin used for resetting chipset
    ioport_port_pin_t               pin_slave_select;      ///< Port pin used for SPI slave select
    uint32_t                      	driver_task_priority;  ///< Driver task thread priority, should be high priority
} sf_wifi_on_gt202_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const sf_wifi_api_t g_sf_wifi_on_sf_wifi_gt202;
/** @endcond */

/*******************************************************************************************************************//**
 * @} (end defgroup SF_WIFI_GT202)
 **********************************************************************************************************************/
#endif /* SF_WIFI_GT202_H */
