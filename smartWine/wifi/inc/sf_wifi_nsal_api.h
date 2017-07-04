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

/***********************************************************************************************************************
* File Name    : sf_wifi_nsal_api.h
* Description  : This file provides configuration used by NSAL.
***********************************************************************************************************************/

#ifndef SF_WIFI_NSAL_API_H
#define SF_WIFI_NSAL_API_H
/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <nx_api.h>

#define SF_WIFI_NSAL_MAC_CHANGED 	(NX_LINK_USER_COMMAND + 1)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_sf_wifi_nsal_zero_copy
{
    SF_WIFI_NSAL_ZERO_COPY_DISABLE,     ///< Zero copy is disabled
    SF_WIFI_NSAL_ZERO_COPY_ENABLE       ///< Zero copy is enabled
} sf_wifi_nsal_zero_copy_t;

/** Define the NSAL configuration parameters */
typedef struct st_sf_wifi_nsal_cfg
{
    sf_wifi_nsal_zero_copy_t    tx_zero_copy;       ///< Transmit path zero copy support
    sf_wifi_nsal_zero_copy_t    rx_zero_copy;       ///< Receive path zero copy support
    uint8_t                   * p_tx_packet_buffer; ///< Pointer to Tx buffer used to consolidate data from chained NetX packets
} sf_wifi_nsal_cfg_t;

/** Define the  NSAL callback arguments */
typedef struct st_sf_wifi_nsal_callback_args
{
    NX_IP               * p_ip;                 ///< Pointer to NetX IP interface
    sf_wifi_nsal_cfg_t  * p_wifi_nsal_cfg;      ///< pointer to NSAL configuration

} sf_wifi_nsal_callback_args_t;

#endif /* SF_WIFI_NSAL_API_H */
