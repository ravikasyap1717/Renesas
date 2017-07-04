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

#include "devices_thread.h"
#include "ens210.h"
#include"tmd3782.h"
#include "dweet.h"
#include "GPS.h"
#include "hih6030.h"
#include "ms5637.h"
#include "bmc150acc.h"
#include "bmc150mag.h"
#include "GPS.h"
#include "zelib-gpio.h"
#include "zelib-adc.h"

uint32_t number_steps;
char buddy_thingname[32]; // = "SKS7-b5e3";
uint32_t buddy_step_count;

void devices_thread_entry(void);

/*Configure Devices with All sensor*/

ze_ens210_ctrl_t ens210_ctrl;
ze_ens210_cfg_t ens210_cfg = {
    .name = "PmodB:ENS210",
    .hw_interface = &pmodB,
};
ze_ens210_instance_t ens210 = {
    .p_ctrl = &ens210_ctrl,
    .p_cfg = &ens210_cfg,
    .p_api = &g_ze_ens210_api,
};

ze_tmd3782_ctrl_t tmd3782_ctrl;
ze_tmd3782_cfg_t tmd3782_cfg = {
    .name = "PmodB:TMD3782",
    .hw_interface = &pmodB,
};
ze_tmd3782_instance_t tmd3782 = {
    .p_ctrl = &tmd3782_ctrl,
    .p_cfg = &tmd3782_cfg,
    .p_api = &g_ze_tmd3782_api,
};

ze_gps_ctrl_t gps_ctrl;
ze_gps_cfg_t gps_cfg = {
    .name       = "Arduino:GPS",
    .hw_interface   = &arduino_uart,
};
ze_gps_instance_t gps = {
    .p_ctrl     = &gps_ctrl,
    .p_cfg      = &gps_cfg,
    .p_api      = &g_ze_gps_api,
};

ze_hih6030_ctrl_t hih6030_ctrl;
ze_hih6030_cfg_t hih6030_cfg = {
    .name = "Arduino:HIH6030",
    .hw_interface = &arduino_i2c,
};
ze_hih6030_instance_t hih6030 = {
    .p_ctrl = &hih6030_ctrl,
    .p_cfg = &hih6030_cfg,
    .p_api = &g_ze_hih6030_api,
};

ze_ms5637_ctrl_t ms5637_ctrl;
ze_ms5637_cfg_t ms5637_cfg = {
    .name = "Arduino:MS5637",
    .hw_interface = &arduino_i2c,
};
ze_ms5637_instance_t ms5637 = {
    .p_ctrl = &ms5637_ctrl,
    .p_cfg = &ms5637_cfg,
    .p_api = &g_ze_ms5637_api,
};

ze_bmc150acc_ctrl_t bmc150acc_ctrl;
ze_bmc150acc_cfg_t bmc150acc_cfg = {
    .name = "Arduino:BMC150ACC",
    .hw_interface = &arduino_i2c,
};
ze_bmc150acc_instance_t bmc150acc = {
    .p_ctrl = &bmc150acc_ctrl,
    .p_cfg = &bmc150acc_cfg,
    .p_api = &g_ze_bmc150acc_api,
};

ze_bmc150mag_ctrl_t bmc150mag_ctrl;
ze_bmc150mag_cfg_t bmc150mag_cfg = {
    .name = "Arduino:BMC150MAG",
    .hw_interface = &arduino_i2c,
};
ze_bmc150mag_instance_t bmc150mag = {
    .p_ctrl = &bmc150mag_ctrl,
    .p_cfg = &bmc150mag_cfg,
    .p_api = &g_ze_bmc150mag_api,
};

/*
 * Adc channel 1 for Vibration Sensor
 * Plug Vibration Sensor on Arduino shield on A0
 * */

ze_adc_ctrl_t Vibration_ctrl;
ze_adc_cfg_t Vibration_cfg = {
    .name = "Arduino:Vibration",
    .hw_interface = &g_adc0,
    .channel = ADC_REG_CHANNEL_1,
};
ze_adc_instance_t Vibration = {
    .p_ctrl = &Vibration_ctrl,
    .p_cfg = &Vibration_cfg,
    .p_api = &g_ze_adc_api,
};

/* Devices Thread entry function */
void devices_thread_entry(void)
{
    extern volatile uint32_t hmi_initialization_completed;
    uint16_t vibration;
    ssp_err_t status;

    while (hmi_initialization_completed == 0)
	tx_thread_sleep(100);

    status = ze_timer2.p_api->open(ze_timer2.p_ctrl, ze_timer2.p_cfg);
        if (status != SSP_SUCCESS)
        __BKPT();

        ZE_Dweet_Register_Global("ticks", ZE_PROPERTY_TYPE_UINT, (void *) (&ze_timer_ticks));
        ZE_Dweet_Register_Global("step-count", ZE_PROPERTY_TYPE_UINT, (void *) (&number_steps));
        ZE_Dweet_Register_Global("buddy-thingname", ZE_PROPERTY_TYPE_STRING, (void *) buddy_thingname);

       /* Open all sensor api for read*/
      ens210.p_api->open(&ens210);
      tmd3782.p_api->open(&tmd3782);
      gps.p_api->open(&gps);
      hih6030.p_api->open(&hih6030);
      ms5637.p_api->open(&ms5637);
      bmc150acc.p_api->open(&bmc150acc);
      bmc150mag.p_api->open(&bmc150mag);
      Vibration.p_api->open(&Vibration);

     /* Resister the device*/
    ZE_Dweet_Register_Instance((ze_device_instance_t *) &ens210);
    ZE_Dweet_Register_Instance((ze_device_instance_t *) &tmd3782);
    ZE_Dweet_Register_Instance((ze_device_instance_t *) &gps);
    ZE_Dweet_Register_Instance((ze_device_instance_t *) &hih6030);
    ZE_Dweet_Register_Instance((ze_device_instance_t *) &ms5637);
    ZE_Dweet_Register_Instance((ze_device_instance_t *) &bmc150acc);
    ZE_Dweet_Register_Instance((ze_device_instance_t *) &bmc150mag);
    ZE_Dweet_Register_Instance((ze_device_instance_t *) &Vibration);


    while (1) {
        tx_thread_sleep (100); // thread sleep

    /*update sensor value in API control*/
	ens210.p_api->update(&ens210);
	tmd3782.p_api->update(&tmd3782);
	gps.p_api->update(&gps);
	hih6030.p_api->update(&hih6030);
	ms5637.p_api->update(&ms5637);
	bmc150acc.p_api->update(&bmc150acc);
	bmc150mag.p_api->update(&bmc150mag);
	Vibration.p_api->update(&Vibration);

	/* read vibration adc value*/
    Vibration.p_api->getProperty(&Vibration, ZE_ADC_VALUE, &vibration);
    vibration = vibration /10; // some mathematical calculation
    Vibration.p_ctrl->value = vibration ; // update the vibration value
	//Vibration.p_api->setProperty(&Vibration, ZE_ADC_VALUE, &vibration);



    }
}


