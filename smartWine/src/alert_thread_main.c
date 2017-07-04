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
 * alert_thread_entry.c
 *
 *  Created on: June 1, 2016
 *      Author: Mike McDonald @ KISStek.com
 */

#include "alert_thread.h"
#include "tmd3782.h"
#include "zelib-files.h"

#include "ux_api.h"
#include "fx_api.h"
#include "ux_system.h"
#include "ux_utility.h"
#include "ux_host_class_storage.h"
#include "ux_host_class_hub.h"
#include "ux_hcd_rx.h"

void alert_thread_main(void);
void DoAlert(int up);
UINT WaitForThumbDrive(void);

#define PROXIMITY_ACTIVATE_THRESHOLD	300
#define PROXIMITY_DEACTIVATE_THRESHOLD	200

#define SONG_BUFFER_SIZE (1 << 16)
static UCHAR song_buffer[SONG_BUFFER_SIZE];
static ULONG song_size;
extern ze_tmd3782_instance_t tmd3782;

/* Alert Thread entry function */
void alert_thread_main(void)
{
    uint16_t proximity;
    ssp_err_t err;
    sf_audio_playback_data_t playback_data;
    sf_audio_playback_data_t *ppd = &playback_data;
    sf_message_acquire_cfg_t cfg_acquire;
    extern volatile uint32_t hmi_initialization_completed;

    while (hmi_initialization_completed == 0)
	tx_thread_sleep(100);

    song_size = ze_LoadFile("red_alert.wav", song_buffer, SONG_BUFFER_SIZE);
    if (song_size == 0) {
	ZE_PostErrorMessage("Cannot open \"red_alert.wav\" on the USB drive\n");
    }

    cfg_acquire.buffer_keep = false;

    err = g_sf_message.p_api->bufferAcquire(g_sf_message.p_ctrl,
					    (sf_message_header_t **) &ppd,
					    &cfg_acquire,
					    TX_WAIT_FOREVER);
    if (err != SSP_SUCCESS) __BKPT();

    ppd->type.scale_bits_max = 16;
    ppd->type.is_signed = 0;
    ppd->p_data = song_buffer;		// BUG - need to skip over the WAV header 
    ppd->size_bytes = song_size;	// BUG - subtract the WAV header size
    ppd->loop_timeout = TX_WAIT_FOREVER;
    ppd->stream_end = true;

    if (song_size > 0) {
	err = g_sf_audio_playback.p_api->start(g_sf_audio_playback.p_ctrl, ppd, TX_NO_WAIT);
	if (err != SSP_SUCCESS) {
	    __BKPT();
	    song_size = 0;
	}
    }

    if (song_size > 0) {
	err = g_sf_audio_playback.p_api->pause(g_sf_audio_playback.p_ctrl);
	if (err != SSP_SUCCESS) {
	    __BKPT();
	    song_size = 0;
	}
    }

    while (1) {
	while (1) {
	    tmd3782.p_api->getProperty(&tmd3782, ZE_TMD3782_PROXIMITY, &proximity);
	    if (proximity > PROXIMITY_ACTIVATE_THRESHOLD)
		break;
	    tx_thread_sleep(50);
	}

	/* pop up alert window in GUIX */
	DoAlert(1);
	if (song_size > 0) {
	    err = g_sf_audio_playback.p_api->resume(g_sf_audio_playback.p_ctrl);
	    if (err != SSP_SUCCESS) __BKPT();
	}

	while (1) {
	    tmd3782.p_api->getProperty(&tmd3782, ZE_TMD3782_PROXIMITY, &proximity);
	    if (proximity < PROXIMITY_DEACTIVATE_THRESHOLD)
		break;
	    tx_thread_sleep(50);
	}

	/* pop down alert window in GUIX */
	DoAlert(0);
	if (song_size > 0) {
	    err = g_sf_audio_playback.p_api->pause(g_sf_audio_playback.p_ctrl);
	    if (err != SSP_SUCCESS) __BKPT();
	}
    }
}
