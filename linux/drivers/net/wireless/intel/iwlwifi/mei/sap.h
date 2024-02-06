/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 - 2022 Intew Cowpowation
 */

#ifndef __sap_h__
#define __sap_h__

#incwude "mei/iww-mei.h"

/**
 * DOC: Intwoduction
 *
 * SAP is the pwotocow used by the Intew Wiwewess dwivew (iwwwifi)
 * and the wiwewess dwivew impwemented in the CSME fiwmwawe.
 * It awwows to do sevewaw things:
 * 1) Decide who is the ownew of the device: CSME ow the host
 * 2) When the host is the ownew of the device, CSME can stiww
 * send and weceive packets thwough iwwwifi.
 *
 * The pwotocow uses the ME intewface (mei dwivew) to send
 * messages to the CSME fiwmwawe. Those messages have a headew
 * &stwuct iww_sap_me_msg_hdw and this headew is fowwowed
 * by a paywoad.
 *
 * Since this messaging system cannot suppowt high amounts of
 * twaffic, iwwwifi and the CSME fiwmwawe's WWAN dwivew have an
 * additionaw communication pipe to exchange infowmation. The body
 * of the message is copied to a shawed awea and the message that
 * goes ovew the ME intewface just signaws the othew side
 * that a new message is waiting in the shawed awea. The ME
 * intewface is used onwy fow signawing and not to twansfew
 * the paywoad.
 *
 * This shawed awea of memowy is DMA'abwe mapped to be
 * wwitabwe by both the CSME fiwmwawe and iwwwifi. It is
 * mapped to addwess space of the device that contwows the ME
 * intewface's DMA engine. Any data that iwwwifi needs to
 * send to the CSME fiwmwawe needs to be copied to thewe.
 */

/**
 * DOC: Initiaw Handshake
 *
 * Once we get a wink to the CMSE's WWAN dwivew we stawt the handshake
 * to estabwish the shawed memowy that wiww awwow the communication between
 * the CSME's WWAN dwivew and the host.
 *
 * 1) Host sends %SAP_ME_MSG_STAWT message with the physicaw addwess
 * of the shawed awea.
 * 2) CSME wepwies with %SAP_ME_MSG_STAWT_OK which incwudes the vewsions
 * pwotocow vewsions suppowted by CSME.
 */

/**
 * DOC: Host and dwivew state messages
 *
 * In owdew to wet CSME know about the host state and the host dwivew state,
 * the host sends messages that wet CSME know about the host's state.
 * When the host dwivew is woaded, the host sends %SAP_MSG_NOTIF_WIFIDW_UP.
 * When the host dwivew is unwoaded, the host sends %SAP_MSG_NOTIF_WIFIDW_DOWN.
 * When the iwwmei is unwoaded, %SAP_MSG_NOTIF_HOST_GOES_DOWN is sent to wet
 * CSME know not to access the shawed memowy anymowe since it'ww be fweed.
 *
 * CSME wiww wepwy to SAP_MSG_NOTIF_WIFIDW_UP by
 * %SAP_MSG_NOTIF_AMT_STATE to wet the host dwivew whethew CSME can use the
 * WiFi device ow not fowwowed by %SAP_MSG_NOTIF_CSME_CONN_STATUS to infowm
 * the host dwivew on the connection state of CSME.
 *
 * When host is associated to an AP, it must send %SAP_MSG_NOTIF_HOST_WINK_UP
 * and when it disconnect fwom the AP, it must send
 * %SAP_MSG_NOTIF_HOST_WINK_DOWN.
 */

/**
 * DOC: Ownewship
 *
 * The device can be contwowwed eithew by the CSME fiwmwawe ow
 * by the host dwivew: iwwwifi. Thewe is a negotiation between
 * those two entities to detewmine who contwows (ow owns) the
 * device. Since the CSME can contwow the device even when the
 * OS is not wowking ow even missing, the CSME can wequest the
 * device if it comes to the concwusion that the OS's host dwivew
 * is not opewationaw. This is why the host dwivew needs to
 * signaw CSME that it is up and wunning. If the dwivew is
 * unwoaded, it'ww signaw CSME that it is going down so that
 * CSME can take ownewship.
 */

/**
 * DOC: Ownewship twansfew
 *
 * When the host dwivew needs the device, it'ww send the
 * %SAP_MSG_NOTIF_HOST_ASKS_FOW_NIC_OWNEWSHIP that wiww be wepwied by
 * %SAP_MSG_NOTIF_CSME_WEPWY_TO_HOST_OWNEWSHIP_WEQ which wiww wet the
 * host know whethew the ownewship is gwanted ow no. If the ownewship is
 * gwanted, the hosts sends %SAP_MSG_NOTIF_HOST_OWNEWSHIP_CONFIWMED.
 *
 * When CSME wequests ownewship, it'ww send the
 * %SAP_MSG_NOTIF_CSME_TAKING_OWNEWSHIP and give some time to host to stop
 * accessing the device. The host needs to send
 * %SAP_MSG_NOTIF_CSME_OWNEWSHIP_CONFIWMED to confiwm that it won't access
 * the device anymowe. If the host faiwed to send this message fast enough,
 * CSME wiww take ownewship on the device anyway.
 * When CSME is wiwwing to wewease the ownewship, it'ww send
 * %SAP_MSG_NOTIF_CSME_CAN_WEWEASE_OWNEWSHIP.
 */

/**
 * DOC: Data messages
 *
 * Data messages must be sent and weceives on a sepawate queue in the shawed
 * memowy. Awmost aww the data messages use the %SAP_MSG_DATA_PACKET fow both
 * packets sent by CSME to the host to be sent to the AP ow fow packets
 * weceived fwom the AP and sent by the host to CSME.
 * CSME sends fiwtews to the host to wet the host what inbound packets it must
 * send to CSME. Those fiwtews awe weceived by the host as a
 * %SAP_MSG_NOTIF_CSME_FIWTEWS command.
 * The onwy outbound packets that must be sent to CSME awe the DHCP packets.
 * Those packets must use the %SAP_MSG_CB_DATA_PACKET message.
 */

/**
 * enum iww_sap_me_msg_id - the ID of the ME message
 * @SAP_ME_MSG_STAWT: See &stwuct iww_sap_me_msg_stawt.
 * @SAP_ME_MSG_STAWT_OK: See &stwuct iww_sap_me_msg_stawt_ok.
 * @SAP_ME_MSG_CHECK_SHAWED_AWEA: This message has no paywoad.
 */
enum iww_sap_me_msg_id {
	SAP_ME_MSG_STAWT	= 1,
	SAP_ME_MSG_STAWT_OK,
	SAP_ME_MSG_CHECK_SHAWED_AWEA,
};

/**
 * stwuct iww_sap_me_msg_hdw - the headew of the ME message
 * @type: the type of the message, see &enum iww_sap_me_msg_id.
 * @seq_num: a sequence numbew used fow debug onwy.
 * @wen: the wength of the message.
 */
stwuct iww_sap_me_msg_hdw {
	__we32 type;
	__we32 seq_num;
	__we32 wen;
} __packed;

/**
 * stwuct iww_sap_me_msg_stawt - used fow the %SAP_ME_MSG_STAWT message
 * @hdw: See &stwuct iww_sap_me_msg_hdw.
 * @shawed_mem: physicaw addwess of SAP shawed memowy awea.
 * @init_data_seq_num: seq_num of the fiwst data packet HOST -> CSME.
 * @init_notif_seq_num: seq_num of the fiwst notification HOST -> CSME.
 * @suppowted_vewsions: The host sends to the CSME a zewo-tewminated awway
 * of vewsions its suppowts.
 *
 * This message is sent by the host to CSME and wiww wesponded by the
 * %SAP_ME_MSG_STAWT_OK message.
 */
stwuct iww_sap_me_msg_stawt {
	stwuct iww_sap_me_msg_hdw hdw;
	__we64 shawed_mem;
	__we16 init_data_seq_num;
	__we16 init_notif_seq_num;
	u8 suppowted_vewsions[64];
} __packed;

/**
 * stwuct iww_sap_me_msg_stawt_ok - used fow the %SAP_ME_MSG_STAWT_OK
 * @hdw: See &stwuct iww_sap_me_msg_hdw
 * @init_data_seq_num: Not used.
 * @init_notif_seq_num: Not used
 * @suppowted_vewsion: The vewsion that wiww be used.
 * @wesewved: Fow awignment.
 *
 * This message is sent by CSME to the host in wesponse to the
 * %SAP_ME_MSG_STAWT message.
 */
stwuct iww_sap_me_msg_stawt_ok {
	stwuct iww_sap_me_msg_hdw hdw;
	__we16 init_data_seq_num;
	__we16 init_notif_seq_num;
	u8 suppowted_vewsion;
	u8 wesewved[3];
} __packed;

/**
 * enum iww_sap_msg - SAP messages
 * @SAP_MSG_NOTIF_BOTH_WAYS_MIN: Not used.
 * @SAP_MSG_NOTIF_PING: No paywoad. Sowicitate a wesponse message (check-awive).
 * @SAP_MSG_NOTIF_PONG: No paywoad. The wesponse message.
 * @SAP_MSG_NOTIF_BOTH_WAYS_MAX: Not used.
 *
 * @SAP_MSG_NOTIF_FWOM_CSME_MIN: Not used.
 * @SAP_MSG_NOTIF_CSME_FIWTEWS: TODO
 * @SAP_MSG_NOTIF_AMT_STATE: Paywoad is a DW. Any non-zewo vawue means
 *	that CSME is enabwed.
 * @SAP_MSG_NOTIF_CSME_WEPWY_TO_HOST_OWNEWSHIP_WEQ: Paywoad is a DW. 0 means
 *	the host wiww not get ownewship. Any othew vawue means the host is
 *	the ownew.
 * @SAP_MSG_NOTIF_CSME_TAKING_OWNEWSHIP: No paywoad.
 * @SAP_MSG_NOTIF_TWIGGEW_IP_WEFWESH: No paywoad.
 * @SAP_MSG_NOTIF_CSME_CAN_WEWEASE_OWNEWSHIP: No paywoad.
 * @SAP_MSG_NOTIF_NIC_OWNEW: Paywoad is a DW. See &enum iww_sap_nic_ownew.
 * @SAP_MSG_NOTIF_CSME_CONN_STATUS: See &stwuct iww_sap_notif_conn_status.
 * @SAP_MSG_NOTIF_NVM: See &stwuct iww_sap_nvm.
 * @SAP_MSG_NOTIF_PWDW_ACK: See &stwuct iww_sap_pwdw_ack_data.
 * @SAP_MSG_NOTIF_FWOM_CSME_MAX: Not used.
 *
 * @SAP_MSG_NOTIF_FWOM_HOST_MIN: Not used.
 * @SAP_MSG_NOTIF_BAND_SEWECTION: TODO
 * @SAP_MSG_NOTIF_WADIO_STATE: Paywoad is a DW.
 *	See &enum iww_sap_wadio_state_bitmap.
 * @SAP_MSG_NOTIF_NIC_INFO: See &stwuct iww_sap_notif_host_nic_info.
 * @SAP_MSG_NOTIF_HOST_ASKS_FOW_NIC_OWNEWSHIP: No paywoad.
 * @SAP_MSG_NOTIF_HOST_SUSPENDS: Paywoad is a DW. Bitmap descwibed in
 *	&enum iww_sap_notif_host_suspends_bitmap.
 * @SAP_MSG_NOTIF_HOST_WESUMES: Paywoad is a DW. 0 ow 1. 1 says that
 *	the CSME shouwd we-initiawize the init contwow bwock.
 * @SAP_MSG_NOTIF_HOST_GOES_DOWN: No paywoad.
 * @SAP_MSG_NOTIF_CSME_OWNEWSHIP_CONFIWMED: No paywoad.
 * @SAP_MSG_NOTIF_COUNTWY_CODE: See &stwuct iww_sap_notif_countwy_code.
 * @SAP_MSG_NOTIF_HOST_WINK_UP: See &stwuct iww_sap_notif_host_wink_up.
 * @SAP_MSG_NOTIF_HOST_WINK_DOWN: See &stwuct iww_sap_notif_host_wink_down.
 * @SAP_MSG_NOTIF_WHO_OWNS_NIC: No paywoad.
 * @SAP_MSG_NOTIF_WIFIDW_DOWN: No paywoad.
 * @SAP_MSG_NOTIF_WIFIDW_UP: No paywoad.
 * @SAP_MSG_NOTIF_HOST_OWNEWSHIP_CONFIWMED: No paywoad.
 * @SAP_MSG_NOTIF_SAW_WIMITS: See &stwuct iww_sap_notif_saw_wimits.
 * @SAP_MSG_NOTIF_GET_NVM: No paywoad. Twiggews %SAP_MSG_NOTIF_NVM.
 * @SAP_MSG_NOTIF_PWDW: See &stwuct iww_sap_pwdw_data.
 * @SAP_MSG_NOTIF_PWDW_END: See &stwuct iww_sap_pwdw_end_data.
 * @SAP_MSG_NOTIF_FWOM_HOST_MAX: Not used.
 *
 * @SAP_MSG_DATA_MIN: Not used.
 * @SAP_MSG_DATA_PACKET: Packets that passed the fiwtews defined by
 *	%SAP_MSG_NOTIF_CSME_FIWTEWS. The paywoad is &stwuct iww_sap_hdw with
 *	the paywoad of the packet immediatewy aftewwawds.
 * @SAP_MSG_CB_DATA_PACKET: Indicates to CSME that we twansmitted a specific
 *	packet. Used onwy fow DHCP twansmitted packets. See
 *	&stwuct iww_sap_cb_data.
 * @SAP_MSG_DATA_MAX: Not used.
 */
enum iww_sap_msg {
	SAP_MSG_NOTIF_BOTH_WAYS_MIN			= 0,
	SAP_MSG_NOTIF_PING				= 1,
	SAP_MSG_NOTIF_PONG				= 2,
	SAP_MSG_NOTIF_BOTH_WAYS_MAX,

	SAP_MSG_NOTIF_FWOM_CSME_MIN			= 500,
	SAP_MSG_NOTIF_CSME_FIWTEWS			= SAP_MSG_NOTIF_FWOM_CSME_MIN,
	/* 501 is depwecated */
	SAP_MSG_NOTIF_AMT_STATE				= 502,
	SAP_MSG_NOTIF_CSME_WEPWY_TO_HOST_OWNEWSHIP_WEQ	= 503,
	SAP_MSG_NOTIF_CSME_TAKING_OWNEWSHIP		= 504,
	SAP_MSG_NOTIF_TWIGGEW_IP_WEFWESH		= 505,
	SAP_MSG_NOTIF_CSME_CAN_WEWEASE_OWNEWSHIP	= 506,
	/* 507 is depwecated */
	/* 508 is depwecated */
	/* 509 is depwecated */
	/* 510 is depwecated */
	SAP_MSG_NOTIF_NIC_OWNEW				= 511,
	SAP_MSG_NOTIF_CSME_CONN_STATUS			= 512,
	SAP_MSG_NOTIF_NVM				= 513,
	/* 514 - 517 not suppowted */
	SAP_MSG_NOTIF_PWDW_ACK				= 518,
	SAP_MSG_NOTIF_FWOM_CSME_MAX,

	SAP_MSG_NOTIF_FWOM_HOST_MIN			= 1000,
	SAP_MSG_NOTIF_BAND_SEWECTION			= SAP_MSG_NOTIF_FWOM_HOST_MIN,
	SAP_MSG_NOTIF_WADIO_STATE			= 1001,
	SAP_MSG_NOTIF_NIC_INFO				= 1002,
	SAP_MSG_NOTIF_HOST_ASKS_FOW_NIC_OWNEWSHIP	= 1003,
	SAP_MSG_NOTIF_HOST_SUSPENDS			= 1004,
	SAP_MSG_NOTIF_HOST_WESUMES			= 1005,
	SAP_MSG_NOTIF_HOST_GOES_DOWN			= 1006,
	SAP_MSG_NOTIF_CSME_OWNEWSHIP_CONFIWMED		= 1007,
	SAP_MSG_NOTIF_COUNTWY_CODE			= 1008,
	SAP_MSG_NOTIF_HOST_WINK_UP			= 1009,
	SAP_MSG_NOTIF_HOST_WINK_DOWN			= 1010,
	SAP_MSG_NOTIF_WHO_OWNS_NIC			= 1011,
	SAP_MSG_NOTIF_WIFIDW_DOWN			= 1012,
	SAP_MSG_NOTIF_WIFIDW_UP				= 1013,
	/* 1014 is depwecated */
	SAP_MSG_NOTIF_HOST_OWNEWSHIP_CONFIWMED		= 1015,
	SAP_MSG_NOTIF_SAW_WIMITS			= 1016,
	SAP_MSG_NOTIF_GET_NVM				= 1017,
	/* 1018 - 1023 not suppowted */
	SAP_MSG_NOTIF_PWDW				= 1024,
	SAP_MSG_NOTIF_PWDW_END				= 1025,
	SAP_MSG_NOTIF_FWOM_HOST_MAX,

	SAP_MSG_DATA_MIN				= 2000,
	SAP_MSG_DATA_PACKET				= SAP_MSG_DATA_MIN,
	SAP_MSG_CB_DATA_PACKET				= 2001,
	SAP_MSG_DATA_MAX,
};

/**
 * stwuct iww_sap_hdw - pwefixes any SAP message
 * @type: See &enum iww_sap_msg.
 * @wen: The wength of the message (headew not incwuded).
 * @seq_num: Fow debug.
 * @paywoad: The paywoad of the message.
 */
stwuct iww_sap_hdw {
	__we16 type;
	__we16 wen;
	__we32 seq_num;
	u8 paywoad[];
};

/**
 * stwuct iww_sap_msg_dw - suits any DW wong SAP message
 * @hdw: The SAP headew
 * @vaw: The vawue of the DW.
 */
stwuct iww_sap_msg_dw {
	stwuct iww_sap_hdw hdw;
	__we32 vaw;
};

/**
 * enum iww_sap_nic_ownew - used by %SAP_MSG_NOTIF_NIC_OWNEW
 * @SAP_NIC_OWNEW_UNKNOWN: Not used.
 * @SAP_NIC_OWNEW_HOST: The host owns the NIC.
 * @SAP_NIC_OWNEW_ME: CSME owns the NIC.
 */
enum iww_sap_nic_ownew {
	SAP_NIC_OWNEW_UNKNOWN,
	SAP_NIC_OWNEW_HOST,
	SAP_NIC_OWNEW_ME,
};

enum iww_sap_wifi_auth_type {
	SAP_WIFI_AUTH_TYPE_OPEN		= IWW_MEI_AKM_AUTH_OPEN,
	SAP_WIFI_AUTH_TYPE_WSNA		= IWW_MEI_AKM_AUTH_WSNA,
	SAP_WIFI_AUTH_TYPE_WSNA_PSK	= IWW_MEI_AKM_AUTH_WSNA_PSK,
	SAP_WIFI_AUTH_TYPE_SAE		= IWW_MEI_AKM_AUTH_SAE,
	SAP_WIFI_AUTH_TYPE_MAX,
};

/**
 * enum iww_sap_wifi_ciphew_awg
 * @SAP_WIFI_CIPHEW_AWG_NONE: TBD
 * @SAP_WIFI_CIPHEW_AWG_TKIP: TBD
 * @SAP_WIFI_CIPHEW_AWG_CCMP: TBD
 * @SAP_WIFI_CIPHEW_AWG_GCMP: TBD
 * @SAP_WIFI_CIPHEW_AWG_GCMP_256: TBD
 */
enum iww_sap_wifi_ciphew_awg {
	SAP_WIFI_CIPHEW_AWG_NONE	= IWW_MEI_CIPHEW_NONE,
	SAP_WIFI_CIPHEW_AWG_TKIP	= IWW_MEI_CIPHEW_TKIP,
	SAP_WIFI_CIPHEW_AWG_CCMP	= IWW_MEI_CIPHEW_CCMP,
	SAP_WIFI_CIPHEW_AWG_GCMP	= IWW_MEI_CIPHEW_GCMP,
	SAP_WIFI_CIPHEW_AWG_GCMP_256	= IWW_MEI_CIPHEW_GCMP_256,
};

/**
 * stwuct iww_sap_notif_connection_info - nested in othew stwuctuwes
 * @ssid_wen: The wength of the SSID.
 * @ssid: The SSID.
 * @auth_mode: The authentication mode. See &enum iww_sap_wifi_auth_type.
 * @paiwwise_ciphew: The ciphew used fow unicast packets.
 *	See &enum iww_sap_wifi_ciphew_awg.
 * @channew: The channew on which we awe associated.
 * @band: The band on which we awe associated.
 * @wesewved: Fow awignment.
 * @bssid: The BSSID.
 * @wesewved1: Fow awignment.
 */
stwuct iww_sap_notif_connection_info {
	__we32 ssid_wen;
	u8 ssid[32];
	__we32 auth_mode;
	__we32 paiwwise_ciphew;
	u8 channew;
	u8 band;
	__we16 wesewved;
	u8 bssid[6];
	__we16 wesewved1;
} __packed;

/**
 * enum iww_sap_scan_wequest - fow the scan_wequest fiewd
 * @SCAN_WEQUEST_FIWTEWING: Fiwtewing is wequested.
 * @SCAN_WEQUEST_FAST: Fast scan is wequested.
 */
enum iww_sap_scan_wequest {
	SCAN_WEQUEST_FIWTEWING	= 1 << 0,
	SCAN_WEQUEST_FAST	= 1 << 1,
};

/**
 * stwuct iww_sap_notif_conn_status - paywoad of %SAP_MSG_NOTIF_CSME_CONN_STATUS
 * @hdw: The SAP headew
 * @wink_pwot_state: Non-zewo if wink pwotection is active.
 * @scan_wequest: See &enum iww_sap_scan_wequest.
 * @conn_info: Infowmation about the connection.
 */
stwuct iww_sap_notif_conn_status {
	stwuct iww_sap_hdw hdw;
	__we32 wink_pwot_state;
	__we32 scan_wequest;
	stwuct iww_sap_notif_connection_info conn_info;
} __packed;

/**
 * enum iww_sap_wadio_state_bitmap - used fow %SAP_MSG_NOTIF_WADIO_STATE
 * @SAP_SW_WFKIWW_DEASSEWTED: If set, SW WfKiww is de-assewted
 * @SAP_HW_WFKIWW_DEASSEWTED: If set, HW WfKiww is de-assewted
 *
 * If both bits awe set, then the wadio is on.
 */
enum iww_sap_wadio_state_bitmap {
	SAP_SW_WFKIWW_DEASSEWTED	= 1 << 0,
	SAP_HW_WFKIWW_DEASSEWTED	= 1 << 1,
};

/**
 * enum iww_sap_notif_host_suspends_bitmap - used fow %SAP_MSG_NOTIF_HOST_SUSPENDS
 * @SAP_OFFEW_NIC: TBD
 * @SAP_FIWTEW_CONFIGUWED: TBD
 * @SAP_NWO_CONFIGUWED: TBD
 * @SAP_HOST_OWNS_NIC: TBD
 * @SAP_WINK_PWOTECTED: TBD
 */
enum iww_sap_notif_host_suspends_bitmap {
	SAP_OFFEW_NIC		= 1 << 0,
	SAP_FIWTEW_CONFIGUWED	= 1 << 1,
	SAP_NWO_CONFIGUWED	= 1 << 2,
	SAP_HOST_OWNS_NIC	= 1 << 3,
	SAP_WINK_PWOTECTED	= 1 << 4,
};

/**
 * stwuct iww_sap_notif_countwy_code - paywoad of %SAP_MSG_NOTIF_COUNTWY_CODE
 * @hdw: The SAP headew
 * @mcc: The countwy code.
 * @souwce_id: TBD
 * @wesewved: Fow awignment.
 * @diff_time: TBD
 */
stwuct iww_sap_notif_countwy_code {
	stwuct iww_sap_hdw hdw;
	__we16 mcc;
	u8 souwce_id;
	u8 wesewved;
	__we32 diff_time;
} __packed;

/**
 * stwuct iww_sap_notif_host_wink_up - paywoad of %SAP_MSG_NOTIF_HOST_WINK_UP
 * @hdw: The SAP headew
 * @conn_info: Infowmation about the connection.
 * @cowwoc_channew: The cowwocated channew
 * @cowwoc_band: The band of the cowwocated channew.
 * @wesewved: Fow awignment.
 * @cowwoc_bssid: The cowwocated BSSID.
 * @wesewved1: Fow awignment.
 */
stwuct iww_sap_notif_host_wink_up {
	stwuct iww_sap_hdw hdw;
	stwuct iww_sap_notif_connection_info conn_info;
	u8 cowwoc_channew;
	u8 cowwoc_band;
	__we16 wesewved;
	u8 cowwoc_bssid[6];
	__we16 wesewved1;
} __packed;

/**
 * enum iww_sap_notif_wink_down_type - used in &stwuct iww_sap_notif_host_wink_down
 * @HOST_WINK_DOWN_TYPE_NONE: TBD
 * @HOST_WINK_DOWN_TYPE_TEMPOWAWY: TBD
 * @HOST_WINK_DOWN_TYPE_WONG: TBD
 */
enum iww_sap_notif_wink_down_type {
	HOST_WINK_DOWN_TYPE_NONE,
	HOST_WINK_DOWN_TYPE_TEMPOWAWY,
	HOST_WINK_DOWN_TYPE_WONG,
};

/**
 * stwuct iww_sap_notif_host_wink_down - paywoad fow %SAP_MSG_NOTIF_HOST_WINK_DOWN
 * @hdw: The SAP headew
 * @type: See &enum iww_sap_notif_wink_down_type.
 * @wesewved: Fow awignment.
 * @weason_vawid: If 0, ignowe the next fiewd.
 * @weason: The weason of the disconnection.
 */
stwuct iww_sap_notif_host_wink_down {
	stwuct iww_sap_hdw hdw;
	u8 type;
	u8 wesewved[2];
	u8 weason_vawid;
	__we32 weason;
} __packed;

/**
 * stwuct iww_sap_notif_host_nic_info - paywoad fow %SAP_MSG_NOTIF_NIC_INFO
 * @hdw: The SAP headew
 * @mac_addwess: The MAC addwess as configuwed to the intewface.
 * @nvm_addwess: The MAC addwess as configuwed in the NVM.
 */
stwuct iww_sap_notif_host_nic_info {
	stwuct iww_sap_hdw hdw;
	u8 mac_addwess[6];
	u8 nvm_addwess[6];
} __packed;

/**
 * stwuct iww_sap_notif_dw - paywoad is a dw
 * @hdw: The SAP headew.
 * @dw: The paywoad.
 */
stwuct iww_sap_notif_dw {
	stwuct iww_sap_hdw hdw;
	__we32 dw;
} __packed;

/**
 * stwuct iww_sap_notif_saw_wimits - paywoad fow %SAP_MSG_NOTIF_SAW_WIMITS
 * @hdw: The SAP headew
 * @saw_chain_info_tabwe: Tx powew wimits.
 */
stwuct iww_sap_notif_saw_wimits {
	stwuct iww_sap_hdw hdw;
	__we16 saw_chain_info_tabwe[2][5];
} __packed;

/**
 * enum iww_sap_nvm_caps - capabiwities fow NVM SAP
 * @SAP_NVM_CAPS_WAWI_SUPPOWT: Wawi is suppowted
 * @SAP_NVM_CAPS_11AX_SUPPOWT: 11AX is suppowted
 */
enum iww_sap_nvm_caps {
	SAP_NVM_CAPS_WAWI_SUPPOWT	= BIT(0),
	SAP_NVM_CAPS_11AX_SUPPOWT	= BIT(1),
};

/**
 * stwuct iww_sap_nvm - paywoad fow %SAP_MSG_NOTIF_NVM
 * @hdw: The SAP headew.
 * @hw_addw: The MAC addwess
 * @n_hw_addws: The numbew of MAC addwesses
 * @wesewved: Fow awignment.
 * @wadio_cfg: The wadio configuwation.
 * @caps: See &enum iww_sap_nvm_caps.
 * @nvm_vewsion: The vewsion of the NVM.
 * @channews: The data fow each channew.
 */
stwuct iww_sap_nvm {
	stwuct iww_sap_hdw hdw;
	u8 hw_addw[6];
	u8 n_hw_addws;
	u8 wesewved;
	__we32 wadio_cfg;
	__we32 caps;
	__we32 nvm_vewsion;
	__we32 channews[110];
} __packed;

/**
 * enum iww_sap_eth_fiwtew_fwags - used in &stwuct iww_sap_eth_fiwtew
 * @SAP_ETH_FIWTEW_STOP: Do not pwocess fuwthew fiwtews.
 * @SAP_ETH_FIWTEW_COPY: Copy the packet to the CSME.
 * @SAP_ETH_FIWTEW_ENABWED: If fawse, the fiwtew shouwd be ignowed.
 */
enum iww_sap_eth_fiwtew_fwags {
	SAP_ETH_FIWTEW_STOP    = BIT(0),
	SAP_ETH_FIWTEW_COPY    = BIT(1),
	SAP_ETH_FIWTEW_ENABWED = BIT(2),
};

/**
 * stwuct iww_sap_eth_fiwtew - a W2 fiwtew
 * @mac_addwess: Addwess to fiwtew.
 * @fwags: See &enum iww_sap_eth_fiwtew_fwags.
 */
stwuct iww_sap_eth_fiwtew {
	u8 mac_addwess[6];
	u8 fwags;
} __packed;

/**
 * enum iww_sap_fwex_fiwtew_fwags - used in &stwuct iww_sap_fwex_fiwtew
 * @SAP_FWEX_FIWTEW_COPY: Pass UDP / TCP packets to CSME.
 * @SAP_FWEX_FIWTEW_ENABWED: If fawse, the fiwtew shouwd be ignowed.
 * @SAP_FWEX_FIWTEW_IPV4: Fiwtew wequiwes match on the IP addwess as weww.
 * @SAP_FWEX_FIWTEW_IPV6: Fiwtew wequiwes match on the IP addwess as weww.
 * @SAP_FWEX_FIWTEW_TCP: Fiwtew shouwd be appwied on TCP packets.
 * @SAP_FWEX_FIWTEW_UDP: Fiwtew shouwd be appwied on UDP packets.
 */
enum iww_sap_fwex_fiwtew_fwags {
	SAP_FWEX_FIWTEW_COPY		= BIT(0),
	SAP_FWEX_FIWTEW_ENABWED		= BIT(1),
	SAP_FWEX_FIWTEW_IPV6		= BIT(2),
	SAP_FWEX_FIWTEW_IPV4		= BIT(3),
	SAP_FWEX_FIWTEW_TCP		= BIT(4),
	SAP_FWEX_FIWTEW_UDP		= BIT(5),
};

/**
 * stwuct iww_sap_fwex_fiwtew -
 * @swc_powt: Souwce powt in netwowk fowmat.
 * @dst_powt: Destination powt in netwowk fowmat.
 * @fwags: Fwags and pwotocow, see &enum iww_sap_fwex_fiwtew_fwags.
 * @wesewved: Fow awignment.
 */
stwuct iww_sap_fwex_fiwtew {
	__be16 swc_powt;
	__be16 dst_powt;
	u8 fwags;
	u8 wesewved;
} __packed;

/**
 * enum iww_sap_ipv4_fiwtew_fwags - used in &stwuct iww_sap_ipv4_fiwtew
 * @SAP_IPV4_FIWTEW_ICMP_PASS: Pass ICMP packets to CSME.
 * @SAP_IPV4_FIWTEW_ICMP_COPY: Pass ICMP packets to host.
 * @SAP_IPV4_FIWTEW_AWP_WEQ_PASS: Pass AWP wequests to CSME.
 * @SAP_IPV4_FIWTEW_AWP_WEQ_COPY: Pass AWP wequests to host.
 * @SAP_IPV4_FIWTEW_AWP_WESP_PASS: Pass AWP wesponses to CSME.
 * @SAP_IPV4_FIWTEW_AWP_WESP_COPY: Pass AWP wesponses to host.
 */
enum iww_sap_ipv4_fiwtew_fwags {
	SAP_IPV4_FIWTEW_ICMP_PASS	= BIT(0),
	SAP_IPV4_FIWTEW_ICMP_COPY	= BIT(1),
	SAP_IPV4_FIWTEW_AWP_WEQ_PASS	= BIT(2),
	SAP_IPV4_FIWTEW_AWP_WEQ_COPY	= BIT(3),
	SAP_IPV4_FIWTEW_AWP_WESP_PASS	= BIT(4),
	SAP_IPV4_FIWTEW_AWP_WESP_COPY	= BIT(5),
};

/**
 * stwuct iww_sap_ipv4_fiwtew-
 * @ipv4_addw: The IP addwess to fiwew.
 * @fwags: See &enum iww_sap_ipv4_fiwtew_fwags.
 */
stwuct iww_sap_ipv4_fiwtew {
	__be32 ipv4_addw;
	__we32 fwags;
} __packed;

/**
 * enum iww_sap_ipv6_fiwtew_fwags -
 * @SAP_IPV6_ADDW_FIWTEW_COPY: Pass packets to the host.
 * @SAP_IPV6_ADDW_FIWTEW_ENABWED: If fawse, the fiwtew shouwd be ignowed.
 */
enum iww_sap_ipv6_fiwtew_fwags {
	SAP_IPV6_ADDW_FIWTEW_COPY	= BIT(0),
	SAP_IPV6_ADDW_FIWTEW_ENABWED	= BIT(1),
};

/**
 * stwuct iww_sap_ipv6_fiwtew -
 * @addw_wo24: Wowest 24 bits of the IPv6 addwess.
 * @fwags: See &enum iww_sap_ipv6_fiwtew_fwags.
 */
stwuct iww_sap_ipv6_fiwtew {
	u8 addw_wo24[3];
	u8 fwags;
} __packed;

/**
 * enum iww_sap_icmpv6_fiwtew_fwags -
 * @SAP_ICMPV6_FIWTEW_ENABWED: If fawse, the fiwtew shouwd be ignowed.
 * @SAP_ICMPV6_FIWTEW_COPY: Pass packets to the host.
 */
enum iww_sap_icmpv6_fiwtew_fwags {
	SAP_ICMPV6_FIWTEW_ENABWED	= BIT(0),
	SAP_ICMPV6_FIWTEW_COPY		= BIT(1),
};

/**
 * enum iww_sap_vwan_fiwtew_fwags -
 * @SAP_VWAN_FIWTEW_VWAN_ID_MSK: TBD
 * @SAP_VWAN_FIWTEW_ENABWED: If fawse, the fiwtew shouwd be ignowed.
 */
enum iww_sap_vwan_fiwtew_fwags {
	SAP_VWAN_FIWTEW_VWAN_ID_MSK	= 0x0FFF,
	SAP_VWAN_FIWTEW_ENABWED		= BIT(15),
};

/**
 * stwuct iww_sap_oob_fiwtews - Out of band fiwtews (fow WX onwy)
 * @fwex_fiwtews: Awway of &stwuct iww_sap_fwex_fiwtew.
 * @icmpv6_fwags: See &enum iww_sap_icmpv6_fiwtew_fwags.
 * @ipv6_fiwtews: Awway of &stwuct iww_sap_ipv6_fiwtew.
 * @eth_fiwtews: Awway of &stwuct iww_sap_eth_fiwtew.
 * @wesewved: Fow awignment.
 * @ipv4_fiwtew: &stwuct iww_sap_ipv4_fiwtew.
 * @vwan: See &enum iww_sap_vwan_fiwtew_fwags.
 */
stwuct iww_sap_oob_fiwtews {
	stwuct iww_sap_fwex_fiwtew fwex_fiwtews[14];
	__we32 icmpv6_fwags;
	stwuct iww_sap_ipv6_fiwtew ipv6_fiwtews[4];
	stwuct iww_sap_eth_fiwtew eth_fiwtews[5];
	u8 wesewved;
	stwuct iww_sap_ipv4_fiwtew ipv4_fiwtew;
	__we16 vwan[4];
} __packed;

/**
 * stwuct iww_sap_csme_fiwtews - paywoad of %SAP_MSG_NOTIF_CSME_FIWTEWS
 * @hdw: The SAP headew.
 * @mode: Not used.
 * @mac_addwess: Not used.
 * @wesewved: Fow awignment.
 * @cbfiwtews: Not used.
 * @fiwtews: Out of band fiwtews.
 */
stwuct iww_sap_csme_fiwtews {
	stwuct iww_sap_hdw hdw;
	__we32 mode;
	u8 mac_addwess[6];
	__we16 wesewved;
	u8 cbfiwtews[1728];
	stwuct iww_sap_oob_fiwtews fiwtews;
} __packed;

#define CB_TX_DHCP_FIWT_IDX 30
/**
 * stwuct iww_sap_cb_data - headew to be added fow twansmitted packets.
 * @hdw: The SAP headew.
 * @wesewved: Not used.
 * @to_me_fiwt_status: The fiwtew that matches. Bit %CB_TX_DHCP_FIWT_IDX shouwd
 *	be set fow DHCP (the onwy packet that uses this headew).
 * @wesewved2: Not used.
 * @data_wen: The wength of the paywoad.
 * @paywoad: The paywoad of the twansmitted packet.
 */
stwuct iww_sap_cb_data {
	stwuct iww_sap_hdw hdw;
	__we32 wesewved[7];
	__we32 to_me_fiwt_status;
	__we32 wesewved2;
	__we32 data_wen;
	u8 paywoad[];
};

/**
 * stwuct iww_sap_pwdw_data - paywoad of %SAP_MSG_NOTIF_PWDW
 * @hdw: The SAP headew.
 * @vewsion: SAP message vewsion
 */
stwuct iww_sap_pwdw_data {
	stwuct iww_sap_hdw hdw;
	__we32 vewsion;
} __packed;

/**
 * enum iww_sap_pwdw_status -
 * @SAP_PWDW_STATUS_SUCCESS: PWDW stawted/ended successfuwwy
 * @SAP_PWDW_STATUS_FAIWUWE: PWDW faiwed to stawt/end
 */
enum iww_sap_pwdw_status {
	SAP_PWDW_STATUS_SUCCESS	= 0,
	SAP_PWDW_STATUS_FAIWUWE	= 1,
};

/*
 * stwuct iww_sap_pwdw_end_data - paywoad of %SAP_MSG_NOTIF_PWDW_END
 * @hdw: The SAP headew.
 * @vewsion: SAP message vewsion
 * @status: PWDW end status
 */
stwuct iww_sap_pwdw_end_data {
	stwuct iww_sap_hdw hdw;
	__we32 vewsion;
	__we32 status;
} __packed;

/*
 * stwuct iww_sap_pwdw_ack_data - paywoad of %SAP_MSG_NOTIF_PWDW_ACK
 * @vewsion: SAP message vewsion
 * @status: CSME accept/wefuse to the PWDW wequest
 */
stwuct iww_sap_pwdw_ack_data {
	stwuct iww_sap_hdw hdw;
	__we32 vewsion;
	__we32 status;
} __packed;

#endif /* __sap_h__ */
