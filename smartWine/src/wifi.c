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
 * wifi.c
 *
 * Created on: Jul 26, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#define _GNU_SOURCE
#include "network_thread.h"
#include "wifi.h"
#include "zelib-files.h"

#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <strings.h>

struct kv_pair {
    char	       *keyword;
    unsigned int	value;
};

static ssp_err_t ParseProvisioningFile(sf_wifi_provisioning_t *prov, unsigned char *info, unsigned int count);
static struct kv_pair *LookupKeyword(char *keyword, struct kv_pair *table, int cnt);

/* from synergy/ssp/inc/framework/api/sf_wifi_api.h */
static struct kv_pair provisioning_keywords[] = {
    { "client",		SF_WIFI_INTERFACE_MODE_CLIENT },
    { "ap",		SF_WIFI_INTERFACE_MODE_AP },
    { "auto",		SF_WIFI_ENCRYPTION_TYPE_AUTO },
    { "ccmp",		SF_WIFI_ENCRYPTION_TYPE_CCMP },
    { "tkip",		SF_WIFI_ENCRYPTION_TYPE_TKIP },
    { "wep-shared-key",	SF_WIFI_SECURITY_TYPE_WEP128_SHARED_HEX },
    { "open", 		SF_WIFI_SECURITY_TYPE_OPEN },
    { "wpa2", 		SF_WIFI_SECURITY_TYPE_WPA2 },
    { "wpa", 		SF_WIFI_SECURITY_TYPE_WPA },
};
#define number_provisioning_keywords (sizeof(provisioning_keywords) / sizeof(provisioning_keywords[0]))

static struct kv_pair *LookupKeyword(char *keyword, struct kv_pair *table, int cnt)
{
    int i;

    for (i = 0 ; i < cnt ; i++)
	if (strncasecmp(table[i].keyword, keyword, strlen(table[i].keyword)) == 0)
	    return (&table[i]);
    return NULL;
}

#define FILE_BUFFER_SIZE (1 << 16)
static UCHAR file_buffer[FILE_BUFFER_SIZE];
static ULONG file_size;

static struct kv_pair *FindKeyword(char *keyword, unsigned char *info)
{
    char *p = strcasestr((const char *) info, keyword);
    
    if (p == NULL)
	return NULL;

    return LookupKeyword(p + strlen(keyword), provisioning_keywords, number_provisioning_keywords);
}

static ssp_err_t ParseProvisioningFile(sf_wifi_provisioning_t *prov, unsigned char *info, unsigned int count)
{
    struct kv_pair *kvp;
    char *p;

    kvp = FindKeyword("mode=", info);
    if (kvp != NULL)
	prov->mode = kvp->value;

    kvp = FindKeyword("encryption=", info);
    if (kvp != NULL)
	prov->encryption = kvp->value;

    kvp = FindKeyword("security=", info);
    if (kvp != NULL)
	prov->security = kvp->value;

    p = strcasestr((const char *) info, "ssid=");
    if (p != NULL) {
	 char *d = ( char *) prov->ssid;
	p += strlen("ssid=");


	    while ((*p != '\0') && !isspace((unsigned char)*p) && (*p != '\r') && (*p != '\n')) {
	    *d = *p;
	    d++;
	    p++;
	    count++;

	}
	*d = '\0';

    }

    p = strcasestr((const char *) info, "key=");
    if (p != NULL) {
	char *d = ( char *)prov->key;
	p += strlen("key=");


	while ((*p != '\0') && !isspace((unsigned char)*p) && (*p != '\r') && (*p != '\n')) {
	    *d = *p;
	    d++;
	    p++;
	}
	*d = '\0';
	count = 0;
    }

    return SSP_SUCCESS;
}

ssp_err_t WiFi_LoadProvisioning(sf_wifi_provisioning_t *prov, char *filename)
{
    /* set "reasonable" defaults */
    prov->mode = SF_WIFI_INTERFACE_MODE_CLIENT;
    prov->encryption = SF_WIFI_ENCRYPTION_TYPE_AUTO;
    prov->security = SF_WIFI_SECURITY_TYPE_WEP128_SHARED_HEX;
  //  strcpy((char *) (prov->ssid), (signed char *)"" );
  //  strcpy((char *) (prov->key), (signed char *) "");

    strcpy((char *) (prov->ssid), "" );
       strcpy((char *) (prov->key), "");



      file_size = ze_LoadFile(filename, file_buffer, FILE_BUFFER_SIZE);

    return ParseProvisioningFile(prov, file_buffer, file_size);
}
