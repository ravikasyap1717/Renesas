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

#include "dweet.h"
#include "network_thread.h"
#include "wifi.h"

#include   "nx_api.h"
#include   "nx_dhcp.h"
#include   "nx_dns.h"

#define LED_ON(led)	g_ioport.p_api->pinWrite(led, IOPORT_LEVEL_LOW)
#define LED_OFF(led)	g_ioport.p_api->pinWrite(led, IOPORT_LEVEL_HIGH)

#define YELLOW_LED	IOPORT_PORT_06_PIN_02
#define RED_LED		IOPORT_PORT_06_PIN_01
#define GREEN_LED	IOPORT_PORT_06_PIN_00

#define TRAP_ON_ERROR(a)     if(a) {\
	LED_OFF(YELLOW_LED);\
	LED_ON(RED_LED);\
	LED_OFF(GREEN_LED);\
	__BKPT();\
	while (1) ; }

#ifndef DEFAULT_DNS_SERVER_ADDRESS
#define DEFAULT_DNS_SERVER_ADDRESS	IP_ADDRESS(8,8,8,8)
#endif

#define SERVER_IP_ADDRESS IP_ADDRESS(0,0,0,0)

NX_PACKET_POOL pool_0;
NX_IP ip_0;
NX_DHCP dhcp_0;
NX_DNS dns_0;
uint32_t ip_address = 0;
char SSID[32];

static char netx_ip_stack[0x4000] __attribute__ ((aligned(64)));
static char netx_arp_stack[0x1000] __attribute__ ((aligned(64)));
static ULONG packet_pool_area[((1536 + 32 + sizeof(NX_PACKET)) * 50) / sizeof(ULONG)];

void network_thread_main(void);

static sf_wifi_provisioning_t prov;
VOID g_sf_wifi_nsal_nx0(NX_IP_DRIVER*);
//static sf_wifi_scan_t g_scanned_ssids[20];

#if 0
VOID nx_ether_driver_eth1(NX_IP_DRIVER*);
static VOID nx_ether_driver_eth1_wrapper(NX_IP_DRIVER *driver);

static VOID nx_ether_driver_eth1_wrapper(NX_IP_DRIVER *driver)
{
    nx_ether_driver_eth1(driver);
    if (driver->nx_ip_driver_command == NX_LINK_INITIALIZE) {
	extern uint16_t BoardID_checksum16;
	driver->nx_ip_driver_interface->nx_interface_physical_address_lsw &= 0xffff0000;
	driver->nx_ip_driver_interface->nx_interface_physical_address_lsw |= BoardID_checksum16;
	R_ETHERC1->MALR = BoardID_checksum16;
    }
}
#endif

/* SSP1.1.X incorrectly returns the DNS server IP in network byte order. This swaps
 * the bytes around so the IP address can be used with the rest of the NX calls.
 */
static uint32_t nx2hl(UINT x)
{
    return (((x >> 24) & 0xff) << 0) | (((x >> 16) & 0xff) << 8) | (((x >> 8) & 0xff) << 16) | (((x >> 0) & 0xff) << 24);
}

void network_thread_main(void)
{
    UINT status = 0;
    ULONG ip_mask, ip_mtu, ip_mac1, ip_mac0, ip_status = 0;
    char *ip_name;
    void UpdateGUI(int do_refresh);
    ULONG link_status;
    UINT server_ip;
    UINT server_ip_size = sizeof(server_ip);
    extern volatile uint32_t hmi_initialization_completed;
    
    LED_ON(YELLOW_LED);
    LED_OFF(RED_LED);
    LED_OFF(GREEN_LED);

    while (hmi_initialization_completed == 0)
	tx_thread_sleep(100);

    nx_system_initialize();

    status =  nx_packet_pool_create(&pool_0, "NetX Main Packet Pool", 
				    (1536 + 32), packet_pool_area, sizeof(packet_pool_area));
    TRAP_ON_ERROR(status);

    status = nx_ip_create(&ip_0, "NetX IP Instance 0", 
			  SERVER_IP_ADDRESS, 0xFFFFFF00UL, 
			  &pool_0, g_sf_wifi_nsal_nx0,
			  netx_ip_stack, sizeof(netx_ip_stack), 2);
    TRAP_ON_ERROR(status);

    status = nx_ip_fragment_enable(&ip_0);
    TRAP_ON_ERROR(status);

    status =  nx_arp_enable(&ip_0, (void *) netx_arp_stack, sizeof(netx_arp_stack));
    TRAP_ON_ERROR(status);

    status =  nx_tcp_enable(&ip_0);
    TRAP_ON_ERROR(status);

    status =  nx_udp_enable(&ip_0);
    TRAP_ON_ERROR(status);

    status =  nx_icmp_enable(&ip_0);
    TRAP_ON_ERROR(status);

    /* Wait for init to finish. */
    status = nx_ip_interface_status_check(&ip_0, 0, NX_IP_LINK_ENABLED, &link_status, NX_WAIT_FOREVER);
    TRAP_ON_ERROR(status);
    
#if 0
    /** Scan SSIDs. */
    status = g_sf_wifi0.p_api->scan(g_sf_wifi0.p_ctrl, 
				    g_scanned_ssids, 
				    sizeof(g_scanned_ssids)/sizeof(g_scanned_ssids[0]));
    TRAP_ON_ERROR(status);
#endif

    WiFi_LoadProvisioning(&prov, "wifi.txt");

    status = g_sf_wifi0.p_api->provisioningSet(g_sf_wifi0.p_ctrl, &prov);
    TRAP_ON_ERROR(status);

    strcpy(SSID, ( const char *)prov.ssid);

    status = nx_dhcp_create(&dhcp_0, &ip_0, "DHCP");
    TRAP_ON_ERROR(status);

    status = nx_dhcp_start(&dhcp_0);
    TRAP_ON_ERROR(status);

    while (ip_status == 0) {
	nx_ip_status_check(&ip_0, NX_IP_ADDRESS_RESOLVED, &ip_status, 100);
    }

    /*     nx_ip_address_get(&ip_0, &ip_address, &ip_mask); */
    while (ip_address == 0)
	nx_ip_interface_info_get(&ip_0, 0, 
				 &ip_name, &ip_address, &ip_mask, &ip_mtu, 
				 &ip_mac1, &ip_mac0);

    status = nx_dhcp_user_option_retrieve(&dhcp_0, NX_DHCP_OPTION_DNS_SVR, 
					  (UCHAR *) &server_ip, &server_ip_size);

    /* BUG: SSP1.1.X returns server IP address in network order, not host order */
    server_ip = nx2hl(server_ip);

    if (status != NX_SUCCESS)
	server_ip = DEFAULT_DNS_SERVER_ADDRESS;
    
    /* Create a DNS instance for the Client.  Note this function will create
       the DNS Client packet pool for creating DNS message packets intended
       for querying its DNS server. */
    status = nx_dns_create(&dns_0, &ip_0, (UCHAR *)"DNS Client");

    /* Add the IPv4 server address of the same DNS server to the Client list. */
    status = nx_dns_server_add(&dns_0, server_ip);

    ZE_Dweet_Use_Ethernet(&ip_0, &dns_0, &pool_0);

    LED_OFF(YELLOW_LED);
    LED_OFF(RED_LED);
    LED_ON(GREEN_LED);

    UpdateGUI(1);

    /* ZE_Dweet_Main_Loop shouldn't return */
    ZE_Dweet_Main_Loop();

    while (1)
        tx_thread_sleep(100);
}
