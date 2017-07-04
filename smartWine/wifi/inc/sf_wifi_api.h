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
* File Name    : sf_wifi_api.h
* Description  : This layer provides APIs to manage Wi-Fi device driver.
***********************************************************************************************************************/

#ifndef SF_WIFI_API_H
#define SF_WIFI_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/** Version of the API defined in this file */
#define SF_WIFI_API_VERSION_MAJOR (1)
#define SF_WIFI_API_VERSION_MINOR (0)

#define SF_WIFI_SSID_LENGTH                 (32)
#define SF_WIFI_SECURITY_KEY_LENGTH         (128)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** IP address version */
typedef enum e_sf_wifi_ip_addr_version
{
    SF_WIFI_IP_ADDR_VERSION_4,     ///< IPv4 address
    SF_WIFI_IP_ADDR_VERSION_6      ///< IPv6 address
} sf_wifi_ip_addr_version_t;

typedef enum e_sf_wifi_interface_mode
{
    SF_WIFI_INTERFACE_MODE_AP,        ///< Access Point mode 
    SF_WIFI_INTERFACE_MODE_CLIENT     ///< Station Mode 
} sf_wifi_interface_mode_t;

typedef enum e_sf_wifi_wep_key_format
{
    SF_WIFI_WEP_KEY_FORMAT_ASCII,       ///< WEP Key in ASCII
    SF_WIFI_WEP_KEY_FORMAT_HEX,         ///< WEP Key in Hex
} sf_wifi_wep_key_format_t;

typedef enum e_sf_wifi_security_type
{
    SF_WIFI_SECURITY_TYPE_OPEN,                 ///< Open. No encryption used.
    SF_WIFI_SECURITY_TYPE_WEP40_SHARED_HEX,     ///< 40-bit WEP SHARED HEX
    SF_WIFI_SECURITY_TYPE_WEP40_SHARED_ASCII,   ///< 40-bit WEP SHARED ASCII
    SF_WIFI_SECURITY_TYPE_WEP128_SHARED_HEX,    ///< 128-bit WEP SHARED HEX
    SF_WIFI_SECURITY_TYPE_WEP128_SHARED_ASCII,  ///< 128-bit WEP SHARED ASCII
    SF_WIFI_SECURITY_TYPE_WEP40_PSK_HEX,        ///< 40-bit WEP PSK HEX
    SF_WIFI_SECURITY_TYPE_WEP40_PSK_ASCII,      ///< 40-bit WEP PSK ASCII
    SF_WIFI_SECURITY_TYPE_WEP128_PSK_HEX,       ///< 128-bit WEP PSK HEX
    SF_WIFI_SECURITY_TYPE_WEP128_PSK_ASCII,     ///< 128-bit WEP PSK ASCII
    SF_WIFI_SECURITY_TYPE_WEP40_OPEN_HEX,       ///< 40-bit WEP OPEN HEX
    SF_WIFI_SECURITY_TYPE_WEP40_OPEN_ASCII,     ///< 40-bit WEP OPEN ASCII
    SF_WIFI_SECURITY_TYPE_WEP128_OPEN_HEX,      ///< 128-bit WEP OPEN HEX
    SF_WIFI_SECURITY_TYPE_WEP128_OPEN_ASCII,    ///< 128-bit WEP OPEN ASCII
    SF_WIFI_SECURITY_TYPE_WPA,                  ///< Wi-Fi Protected Access
    SF_WIFI_SECURITY_TYPE_WPA2                  ///< Wi-Fi Protected Access v2
} sf_wifi_security_type_t;

typedef enum e_sf_wifi_encryption_type
{
    SF_WIFI_ENCRYPTION_TYPE_AUTO,     ///< Automatic selection of encryption protocol. 
    SF_WIFI_ENCRYPTION_TYPE_TKIP,     ///< Temporal Key Integrity Protocol. Used by WPA. 
    SF_WIFI_ENCRYPTION_TYPE_CCMP      ///< CTR mode with CBC-MAC Protocol. Used by WPA2 
} sf_wifi_encryption_type_t;

typedef enum e_sf_wifi_interface_hw_mode
{
    SF_WIFI_INTERFACE_HW_MODE_11A,        ///< 802.11a 
    SF_WIFI_INTERFACE_HW_MODE_11B,        ///< 802.11b 
    SF_WIFI_INTERFACE_HW_MODE_11G,        ///< 802.11g 
    SF_WIFI_INTERFACE_HW_MODE_11N         ///< 802.11n 
} sf_wifi_interface_hw_mode_t;

typedef enum e_sf_wifi_rts
{
    SF_WIFI_RTS_DISABLE,                    ///< Disable RTS/CTS handshake
    SF_WIFI_RTS_ENABLE,                     ///< Enable RTS/CTS handshake
} sf_wifi_rts_t;

typedef enum e_sf_wifi_preamble
{
    SF_WIFI_PREAMBLE_SHORT,                     ///< Use short preamble
    SF_WIFI_PREAMBLE_LONG,                      ///< Use long preamble
} sf_wifi_preamble_t;

typedef enum e_sf_wifi_wmm
{
    SF_WIFI_WMM_DISABLE,                    ///< Disable WMM
    SF_WIFI_WMM_ENABLE,                     ///< Enable WMM
} sf_wifi_wmm_t;

typedef enum e_sf_wifi_high_throughput
{
    SF_WIFI_HIGH_THROUGHPUT_DISABLE,                    ///< Disable high throughput mode
    SF_WIFI_HIGH_THROUGHPUT_ENABLE,                     ///< Enable high throughput mode. Also requires WMM to be enabled.
} sf_wifi_high_throughput_t;

typedef enum e_sf_wifi_ssid_broadcast
{
    SF_WIFI_SSID_BROADCAST_DISABLE,                 ///< Disable SSID Broadcast
    SF_WIFI_SSID_BROADCAST_ENABLE,                  ///< Enable SSID Broadcast
} sf_wifi_ssid_broadcast_t;

typedef enum e_sf_wifi_wds
{
    SF_WIFI_WDS_DISABLE,                    ///< Disable WDS
    SF_WIFI_WDS_ENABLE,                     ///< Enable WDS
} sf_wifi_wds_t;

typedef enum e_sf_wifi_mandatory_high_throughput
{
    SF_WIFI_MANDATORY_HIGH_THROUGHPUT_DISABLE,                  ///< Disable Mandatory HT requirement
    SF_WIFI_MANDATORY_HIGH_THROUGHPUT_ENABLE,                   ///< Enable mandatory HT requirement
} sf_wifi_mandatory_high_throughput_t;

typedef enum e_sf_wifi_auto_negotiation
{
    SF_WIFI_AUTO_NEGOTIATION_DISABLE,                   ///< Auto negotiation disable
    SF_WIFI_AUTO_NEGOTIATION_ENABLE,                    ///< Auto negotiation enable
} sf_wifi_auto_negotiation_t;

/** Wi-Fi Framework AccessContol mode */
typedef enum e_sf_wifi_access_control
{
    SF_WIFI_ACCESS_CONTROL_DISABLE,                  ///< Disable MAC address matching
    SF_WIFI_ACCESS_CONTROL_DENY,                     ///< Deny association to stations on the MAC list.
    SF_WIFI_ACCESS_CONTROL_ALLOW,                    ///< Allow association to stations on the MAC list.
} sf_wifi_access_control_t;

/** Wi-Fi Provisioning parameters */
typedef struct st_sf_wifi_provisioning
{
    sf_wifi_interface_mode_t    mode;                               ///< Select AP or Client mode
    uint8_t                     channel;                            ///< RF Channel number
    uint8_t                     ssid[SF_WIFI_SSID_LENGTH];          ///< SSID
    sf_wifi_security_type_t     security;                           ///< Security type
    sf_wifi_encryption_type_t   encryption;                         ///< Encryption type
    uint8_t                     key[SF_WIFI_SECURITY_KEY_LENGTH];   ///< Pre-shared key
} sf_wifi_provisioning_t;

/** IP address information */
typedef struct st_sf_wifi_ip_addr
{
    sf_wifi_ip_addr_version_t version;  ///< IP Address Version : v4 or v6
    union                               ///< Union that holds either IPv4 or IPv6 address
    {
        uint32_t v4;
        uint32_t v6[4];
    } addr;                             ///< IP address
} sf_wifi_ip_addr_t;

/** Configuration about underlying device driver. */
typedef struct st_sf_wifi_info
{
    uint8_t         * p_chipset;    ///< Pointer to sting showing Wi-Fi chipset/driver information
    uint16_t          rssi;         ///< Received signal strength indication
    uint16_t          noise_level;  ///< Signal to noise ratio
    uint16_t          link_quality; ///< Signal strength / quality
} sf_wifi_info_t;

/** Wi-Fi Framework event codes */
typedef enum e_sf_wifi_event
{
    SF_WIFI_EVENT_RX    = (1 << 0),                       ///< Packet received event
} sf_wifi_event_t;

/** Wi-Fi framework callback parameter definition */
typedef struct st_sf_wifi_callback_arg
{
    sf_wifi_event_t         event;                        ///< Event code
    uint8_t               * p_data;                       ///< Packet data
    uint32_t                length;                       ///< Packet Data length
    void const            * p_context;                    ///< Context provided to user during callback
} sf_wifi_callback_args_t;

/** Define the Wi-Fi configuration parameters */
typedef struct st_sf_wifi_cfg
{
    uint8_t                             mac_addr[6];                ///< MAC address of Wi-Fi Device
    sf_wifi_interface_hw_mode_t         hw_mode;                    ///< Modulation type: 11a/b/g/n
    uint8_t                             tx_power;                   ///< Sets transmit power in dBm
    sf_wifi_rts_t                       rts;                        ///< RTS/CTS handshake flag
    uint16_t                            fragmentation;              ///< Fragmentation threshold
    uint8_t                             dtim;                       ///< Delivery traffic indication message interval
    sf_wifi_high_throughput_t           high_throughput;            ///< High-throughput mode. Only valid for 802.11n
    sf_wifi_preamble_t                  preamble;                   ///< Preamble type
    sf_wifi_wmm_t                       wmm;                        ///< Wi-Fi Multimedia Mode flag. If enabled, also requires
                                                                    ///< enabling WMM.
    uint8_t                             max_stations;               ///< Maximum permitted stations. Valid in AP mode only.
    sf_wifi_ssid_broadcast_t            ssid_broadcast;             ///< SSID broadcast flag. Valid in AP mode only.
    sf_wifi_access_control_t            access_control;             ///< Mode of access control MAC list
    uint32_t                            beacon;                     ///< Beacon interval. Valid in AP mode only
    uint32_t                            station_inactivity_timeout; ///< Station inactivity timeout value. Valid in AP mode only.
    sf_wifi_wds_t                       wds;                        ///< WDS flag. Valid in AP mode only.
    void                              * p_buffer_pool_rx;           ///< Pointer to Network stack Rx buffer pool
    sf_wifi_mandatory_high_throughput_t req_high_throughput;        ///< Only allow HT mode. Valid in AP mode only
    void                             (* p_callback)(sf_wifi_callback_args_t * p_args);          ///< Pointer to callback function
    void                        const * p_context;                  ///< User defined context passed into callback function
    void                        const * p_extend;                   ///< Instance specific configuration
} sf_wifi_cfg_t;

/** Define the statistic and error counters for this IP instance. */
typedef struct st_sf_wifi_stats
{    
   uint32_t rx_pkts;        ///< Packets received successfully 
   uint32_t tx_pkts;        ///< Packets transmitted successfully 
   uint32_t rx_bytes;       ///< Bytes received 
   uint32_t tx_bytes;       ///< Bytes transmitted 
   uint32_t rx_drop;        ///< Packets dropped during reception 
   uint32_t tx_drop;        ///< Packets dropped during transmission 
   uint32_t rx_err;         ///< Receive errors 
   uint32_t tx_err;         ///< Transmit errors 
   uint32_t rx_ovr;         ///< Receive overruns 
   uint32_t tx_orv;         ///< Transmit overruns 
   uint32_t rx_frame;       ///< Receive frame errors 
   uint32_t tx_carrier;     ///< Transmit carrier errors 
} sf_wifi_stats_t;

/** Define the structure to store the SSID scan information */
typedef struct st_sf_wifi_scan
{
    sf_wifi_interface_hw_mode_t hw_mode;         ///< Hardware mode 802.11a/b/g/n
    uint8_t                     tx_power;        ///< Transmit power
    uint8_t                     rssi;            ///< RSSI
    uint8_t                     noise_level;     ///< Noise level 
    uint8_t                     link_quality;    ///< Link quality
    uint8_t                     ssid[32];        ///< SSID name
} sf_wifi_scan_t;

/** Wi-Fi Framework control structure */
typedef struct st_sf_wifi_ctrl
{
    /** Storage for information needed for each Wi-Fi device driver in the system. */
    void                    * p_driver_handle;
} sf_wifi_ctrl_t;

/** Framework API structure.  Implementations will use the following API. */
typedef struct st_sf_wifi_api
{
    /**
     * Initializes the network interface for data transfers
     *
     * Initial driver configuration, enable the driver link, enable interrupts and
     * make device ready for data transfer.
     * @par Implemented as
     * - SF_WIFI_BCM43362_Open()
     * - SF_WIFI_BCM4343W_Open()
     * - SF_WIFI_RS9113_Open()
     * - SF_WIFI_GT202_Open()
     *
     * @param[in, out] p_ctrl Pointer to user-provided storage for the control block.
     * @param[in]      p_cfg  Pointer to Wi-Fi configuration structure.
     */
    ssp_err_t (* open)(sf_wifi_ctrl_t * p_ctrl, sf_wifi_cfg_t const * p_cfg);

    /**
     * De-initialize the network interface and may put
	 * it in low power mode or power it off. Close the driver, disable the driver link,
	 * disable interrupt.
     * 
	 * @par Implemented as
     * - SF_WIFI_BCM43362_Close()
     * - SF_WIFI_BCM4343W_Close()
     * - SF_WIFI_RS9113_Close()
     * - SF_WIFI_GT202_Close()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the Wi-Fi module.
     */
    ssp_err_t (* close)(sf_wifi_ctrl_t * p_ctrl);

    /**
     * Add the given IP address to the multicast filter list.
     *
     * @par Implemented as
     * - SF_WIFI_BCM43362_MulticastListAdd()
     * - SF_WIFI_BCM4343W_MulticastListAdd()
     * - SF_WIFI_RS9113_MulticastListAdd()
     * - SF_WIFI_GT202_MulticastListAdd()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_addr  Pointer to the Multicast IP address.
     */
    ssp_err_t (* multicastListAdd)(sf_wifi_ctrl_t * p_ctrl, sf_wifi_ip_addr_t * p_addr);

    /**
     * Delete the given IP address from the multicast filter list.
     *
     * - SF_WIFI_BCM43362_MulticastListDelete()
     * - SF_WIFI_BCM4343W_MulticastListDelete()
     * - SF_WIFI_RS9113_MulticastListDelete()
     * - SF_WIFI_GT202_MulticastListDelete()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_addr  Pointer to the Multicast IP address.
     */
    ssp_err_t (* multicastListDelete)(sf_wifi_ctrl_t * p_ctrl, sf_wifi_ip_addr_t * p_addr);

    /**
     * Get the interface statistics.
     *
     * @par Implemented as
     * - SF_WIFI_BCM43362_StatisticsGet()
     * - SF_WIFI_BCM4343W_StatisticsGet()
     * - SF_WIFI_RS9113_StatisticsGet()
     * - SF_WIFI_GT202_StatisticsGet()
     *
     * @param[in]       p_ctrl              Pointer to the control block for the Wi-Fi module.
     * @param[in, out]  p_wifi_device_stats Pointer to the Wi-Fi module data statistics.
     */
    ssp_err_t (* statisticsGet)(sf_wifi_ctrl_t * p_ctrl, sf_wifi_stats_t  * p_wifi_device_stats);

    /**
     * Transmit data packet
     *
     * @par Implemented as
     * - SF_WIFI_BCM43362_Transmit()
     * - SF_WIFI_BCM4343W_Transmit()
     * - SF_WIFI_RS9113_Transmit()
     * - SF_WIFI_GT202_Transmit()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_buf   Pointer to transmit buffer
     * @param[in]  length  Transmit buffer length
     */
    ssp_err_t (* transmit)(sf_wifi_ctrl_t * p_ctrl, uint8_t * p_buf, uint32_t length);

    /** 
	 * Set Wi-Fi module provisioning which will configure the module in AP or Client mode.
	 *
     * @par Implemented as
     * - SF_WIFI_BCM43362_ProvisioningSet()
     * - SF_WIFI_BCM4343W_ProvisioningSet()
     * - SF_WIFI_RS9113_ProvisioningSet()
     * - SF_WIFI_GT202_ProvisioningSet()
     *
     * @param[in]  p_ctrl               Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_wifi_provisioning  Pointer to Wi-Fi provisioning structure
     */
    ssp_err_t (* provisioningSet)(sf_wifi_ctrl_t * p_ctrl, sf_wifi_provisioning_t * p_wifi_provisioning);

    /** 
	 * Get the provisioning information of Wi-Fi module.
	 *
     * @par Implemented as
     * - SF_WIFI_BCM43362_ProvisioningGet()
     * - SF_WIFI_BCM4343W_ProvisioningGet()
     * - SF_WIFI_RS9113_ProvisioningGet()
     * - SF_WIFI_GT202_ProvisioningGet()
     *
     * @param[in]  p_ctrl               Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_wifi_provisioning  Pointer to Wi-Fi provisioning structure
     */
    ssp_err_t (* provisioningGet)(sf_wifi_ctrl_t * p_ctrl, sf_wifi_provisioning_t * p_wifi_provisioning);

    /** 
	 * Get Wi-Fi module information.
	 *
     * @par Implemented as
     * - SF_WIFI_BCM43362_InfoGet()
     * - SF_WIFI_BCM4343W_InfoGet()
     * - SF_WIFI_RS9113_InfoGet()
     * - SF_WIFI_GT202_InfoGet()
     *
     * @param[in]  p_ctrl       Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_wifi_info  Pointer to Wi-Fi module information structure
     */
    ssp_err_t (* infoGet)(sf_wifi_ctrl_t * p_ctrl, sf_wifi_info_t * p_wifi_info);

    /** 
	 * Scan for Wi-Fi SSIDs.
	 *
     * @par Implemented as
     * - SF_WIFI_BCM43362_Scan()
     * - SF_WIFI_BCM4343W_Scan()
     * - SF_WIFI_RS9113_Scan()
     * - SF_WIFI_GT202_Scan()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_scan  Pointer to structure which will hold scan result. It is the responsibility of the caller
     *                     to ensure that adequate space is available to hold scan results.
     * @param[in]  p_cnt   Pointer to variable which will hold count of scanned SSIDs
     */
    ssp_err_t (* scan)(sf_wifi_ctrl_t * p_ctrl, sf_wifi_scan_t * p_scan, uint8_t * p_cnt);

    /** 
	 * Adds a MAC address to the Access Control List. Valid in AP mode only.
	 * 
     * @par Implemented as
     * - SF_WIFI_BCM43362_AccessControlListAdd()
     * - SF_WIFI_BCM4343W_AccessControlListAdd()
     * - SF_WIFI_RS9113_AccessControlListAdd()
     * - SF_WIFI_GT202_AccessControlListAdd()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_mac   Pointer to MAC address
     */
    ssp_err_t (* accessControlListAdd)(sf_wifi_ctrl_t * p_ctrl, uint8_t * p_mac);

    /**
	 * Deletes a MAC address from Access Control List. Valid in AP mode only..
     * 
	 * @par Implemented as
     * - SF_WIFI_BCM43362_AccessControlListDelete()
     * - SF_WIFI_BCM4343W_AccessControlListDelete()
     * - SF_WIFI_RS9113_AccessControlListDelete()
     * - SF_WIFI_GT202_AccessControlListDelete()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_mac   Pointer to MAC address
     */
    ssp_err_t (* accessControlListDelete)(sf_wifi_ctrl_t * p_ctrl, uint8_t * p_mac);

    /**
     * Get Wi-Fi module MAC address
     *
     * @par Implemented as
     * - SF_WIFI_BCM43362_MACAddressGet()
     * - SF_WIFI_BCM4343W_MACAddressGet()
     * - SF_WIFI_RS9113_MACAddressGet()
     * - SF_WIFI_GT202_MACAddressGet()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_mac   Pointer to MAC address
     */
    ssp_err_t (* macAddressGet)(sf_wifi_ctrl_t * p_ctrl, uint8_t * p_mac);

    /**
     * Set Wi-Fi module MAC address
     *
     * @par Implemented as
     * - SF_WIFI_BCM43362_MACAddressSet()
     * - SF_WIFI_BCM4343W_MACAddressSet()
     * - SF_WIFI_RS9113_MACAddressSet()
     * - SF_WIFI_GT202_MACAddressSet()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the Wi-Fi module.
     * @param[in]  p_mac   Pointer to MAC address
     */
    ssp_err_t (* macAddressSet)(sf_wifi_ctrl_t * p_ctrl, uint8_t * p_mac);

    /** 
	 * Gets version and stores it in provided pointer p_version.
	 *
     * @par Implemented as
     * - SF_WIFI_BCM43362_VersionGet()
     * - SF_WIFI_BCM4343W_VersionGet()
     * - SF_WIFI_RS9113_VersionGet()
     * - SF_WIFI_GT202_VersionGet()
     *
     * @param[out]  p_version pointer to memory location to return version number
     */
    ssp_err_t (* versionGet)(ssp_version_t * const p_version);
} sf_wifi_api_t;

typedef struct st_sf_wifi_instance
{
    sf_wifi_ctrl_t                   * p_ctrl;       ///< Pointer to the control structure for this instance
    sf_wifi_cfg_t              const * p_cfg;        ///< Pointer to the configuration structure for this instance
    sf_wifi_api_t              const * p_api;        ///< Pointer to the API structure for this instance
} sf_wifi_instance_t;

#endif /* SF_WIFI_API_H */
