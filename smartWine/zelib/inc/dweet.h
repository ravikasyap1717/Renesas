/*
 * dweet.h
 *
 * Created on: Jul 21, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _DWEET_H_
#define _DWEET_H_

#include "zelib.h"
#include "CAT1.h"

#include "nx_api.h"
#include "nx_dns.h"

ssp_err_t ZE_Dweet_Register_Instance(ze_device_instance_t * const this);
ssp_err_t ZE_Dweet_Register_Global(char *name, ze_property_type_t type, void *ptr);

void ZE_Dweet_Init(char *hostname, unsigned int port);
void ZE_Dweet_Use_Modem(ze_cat1_instance_t *modem);
void ZE_Dweet_Use_Ethernet(NX_IP *enet, NX_DNS *dns, NX_PACKET_POOL *pool);
void ZE_Dweet_Main_Loop();
void ZE_Dweet_Upload();
int ZE_Dweet_GetLatestFor(char *thingname, char *buffer, size_t length);

#endif /* _DWEET_H_ */
