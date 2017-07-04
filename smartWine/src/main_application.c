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

/*
 * main_application.c
 *
 *  Created on: May 14, 2016
 *      Author: Mike McDonald @ KISStek.com
 */

#include <strings.h>

#include "dweet.h"

#include "bsp_api.h"
#include "r_fmi_api.h"
#include "ux_api.h"
#include "fx_api.h"
#include "ux_system.h"
#include "ux_utility.h"
#include "ux_host_class_storage.h"
#include "ux_host_class_hub.h"
#include "ux_hcd_rx.h"

#include "devices_thread.h"
#include "hmi_thread.h"
#include "network_thread.h"
#include "zelib-files.h"

/* declare the threads as SSP doesn't define them in hte header files like it should */
extern TX_THREAD alert_thread;
extern TX_THREAD devices_thread;
extern TX_THREAD hmi_thread;
extern TX_THREAD network_thread;

char BoardID[64];
uint16_t BoardID_checksum16;

void tx_application_define_user(void *first_unused_memory);
void R_FMI_ProductInfoGet(fmi_product_info_t **);
void bzero(void *, size_t);

void tx_application_define_user(void *first_unused_memory)
{

    fmi_product_info_t *pinfo;
    int i;
    uint16_t *pu16;

    fx_system_initialize();

    ze_InitFiles(first_unused_memory);

    R_FMI_ProductInfoGet(&pinfo);

#ifdef BSP_BOARD_S7G2_SK
#define BoardType "SKS7"
#endif
#ifdef BSP_BOARD_S7G2_DK
#define BoardType "DKS7"
#endif

   /* pu16 = (uint16_t *) (pinfo->unique_id);
    for (i = 0 ; i < 8 ; i++)
         BoardID_checksum16 = (uint16_t)(BoardID_checksum16 + pu16[i]);
    sprintf(BoardID, "%s-%04x", BoardType, BoardID_checksum16);*/

    /* Define here thing space name where you want to post data */
    sprintf(BoardID, "%s", "synergy");

    ZE_Dweet_Init("thingspace.io", 80);
    /* Change the projcet name */
    ZE_Dweet_Register_Global("application", ZE_PROPERTY_TYPE_STRING, "verizonPoc");

    tx_thread_resume(&hmi_thread);
    tx_thread_resume(&devices_thread);
    tx_thread_resume(&alert_thread);
    tx_thread_resume(&network_thread);
}
