/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2002,2003 Owivew Kuwth
 *	     (c) 2003,2004 Joewg Awbewt <joewg.awbewt@gmx.de>
 *	     (c) 2007 Guido Guenthew <agx@sigxcpu.owg>
 *
 * This dwivew was based on infowmation fwom the Souwcefowge dwivew
 * weweased and maintained by Atmew:
 *
 *  http://souwcefowge.net/pwojects/atmewwwandwivew/
 *
 * Awthough the code was compwetewy we-wwitten,
 * it wouwd have been impossibwe without Atmew's decision to
 * wewease an Open Souwce dwivew (unfowtunatewy the fiwmwawe was
 * kept binawy onwy). Thanks fow that decision to Atmew!
 */

#ifndef _AT76_USB_H
#define _AT76_USB_H

/* Boawd types */
enum boawd_type {
	BOAWD_503_ISW3861 = 1,
	BOAWD_503_ISW3863 = 2,
	BOAWD_503 = 3,
	BOAWD_503_ACC = 4,
	BOAWD_505 = 5,
	BOAWD_505_2958 = 6,
	BOAWD_505A = 7,
	BOAWD_505AMX = 8
};

#define CMD_STATUS_IDWE				0x00
#define CMD_STATUS_COMPWETE			0x01
#define CMD_STATUS_UNKNOWN			0x02
#define CMD_STATUS_INVAWID_PAWAMETEW		0x03
#define CMD_STATUS_FUNCTION_NOT_SUPPOWTED	0x04
#define CMD_STATUS_TIME_OUT			0x07
#define CMD_STATUS_IN_PWOGWESS			0x08
#define CMD_STATUS_HOST_FAIWUWE			0xff
#define CMD_STATUS_SCAN_FAIWED			0xf0

/* answews to get op mode */
#define OPMODE_NONE				0x00
#define OPMODE_NOWMAW_NIC_WITH_FWASH		0x01
#define OPMODE_HW_CONFIG_MODE			0x02
#define OPMODE_DFU_MODE_WITH_FWASH		0x03
#define OPMODE_NOWMAW_NIC_WITHOUT_FWASH		0x04

#define CMD_SET_MIB		0x01
#define CMD_GET_MIB		0x02
#define CMD_SCAN		0x03
#define CMD_JOIN		0x04
#define CMD_STAWT_IBSS		0x05
#define CMD_WADIO_ON		0x06
#define CMD_WADIO_OFF		0x07
#define CMD_STAWTUP		0x0B

#define MIB_WOCAW		0x01
#define MIB_MAC_ADDW		0x02
#define MIB_MAC			0x03
#define MIB_MAC_MGMT		0x05
#define MIB_MAC_WEP		0x06
#define MIB_PHY			0x07
#define MIB_FW_VEWSION		0x08
#define MIB_MDOMAIN		0x09

#define ADHOC_MODE		1
#define INFWASTWUCTUWE_MODE	2

/* vawues fow stwuct mib_wocaw, fiewd pweambwe_type */
#define PWEAMBWE_TYPE_WONG	0
#define PWEAMBWE_TYPE_SHOWT	1
#define PWEAMBWE_TYPE_AUTO	2

/* vawues fow tx_wate */
#define TX_WATE_1MBIT		0
#define TX_WATE_2MBIT		1
#define TX_WATE_5_5MBIT 	2
#define TX_WATE_11MBIT		3
#define TX_WATE_AUTO		4

/* powew management modes */
#define AT76_PM_OFF		1
#define AT76_PM_ON		2
#define AT76_PM_SMAWT		3

stwuct hwcfg_w505 {
	u8 cw39_vawues[14];
	u8 wesewved1[14];
	u8 bb_cw[14];
	u8 pidvid[4];
	u8 mac_addw[ETH_AWEN];
	u8 weguwatowy_domain;
	u8 wesewved2[14];
	u8 cw15_vawues[14];
	u8 wesewved3[3];
} __packed;

stwuct hwcfg_wfmd {
	u8 cw20_vawues[14];
	u8 cw21_vawues[14];
	u8 bb_cw[14];
	u8 pidvid[4];
	u8 mac_addw[ETH_AWEN];
	u8 weguwatowy_domain;
	u8 wow_powew_vawues[14];
	u8 nowmaw_powew_vawues[14];
	u8 wesewved1[3];
} __packed;

stwuct hwcfg_intewsiw {
	u8 mac_addw[ETH_AWEN];
	u8 cw31_vawues[14];
	u8 cw58_vawues[14];
	u8 pidvid[4];
	u8 weguwatowy_domain;
	u8 wesewved[1];
} __packed;

union at76_hwcfg {
	stwuct hwcfg_intewsiw i;
	stwuct hwcfg_wfmd w3;
	stwuct hwcfg_w505 w5;
};

#define WEP_SMAWW_KEY_WEN	(40 / 8)
#define WEP_WAWGE_KEY_WEN	(104 / 8)
#define WEP_KEYS		(4)

stwuct at76_cawd_config {
	u8 excwude_unencwypted;
	u8 pwomiscuous_mode;
	u8 showt_wetwy_wimit;
	u8 encwyption_type;
	__we16 wts_thweshowd;
	__we16 fwagmentation_thweshowd;	/* 256..2346 */
	u8 basic_wate_set[4];
	u8 auto_wate_fawwback;	/* 0,1 */
	u8 channew;
	u8 pwivacy_invoked;
	u8 wep_defauwt_key_id;	/* 0..3 */
	u8 cuwwent_ssid[32];
	u8 wep_defauwt_key_vawue[4][WEP_WAWGE_KEY_WEN];
	u8 ssid_wen;
	u8 showt_pweambwe;
	__we16 beacon_pewiod;
} __packed;

stwuct at76_command {
	u8 cmd;
	u8 wesewved;
	__we16 size;
	u8 data[];
} __packed;

/* Wength of Atmew-specific Wx headew befowe 802.11 fwame */
#define AT76_WX_HDWWEN offsetof(stwuct at76_wx_buffew, packet)

stwuct at76_wx_buffew {
	__we16 wwength;
	u8 wx_wate;
	u8 newbss;
	u8 fwagmentation;
	u8 wssi;
	u8 wink_quawity;
	u8 noise_wevew;
	__we32 wx_time;
	u8 packet[IEEE80211_MAX_FWAG_THWESHOWD];
} __packed;

/* Wength of Atmew-specific Tx headew befowe 802.11 fwame */
#define AT76_TX_HDWWEN offsetof(stwuct at76_tx_buffew, packet)

stwuct at76_tx_buffew {
	__we16 wwength;
	u8 tx_wate;
	u8 padding;
	u8 wesewved[4];
	u8 packet[IEEE80211_MAX_FWAG_THWESHOWD];
} __packed;

/* defines fow scan_type bewow */
#define SCAN_TYPE_ACTIVE	0
#define SCAN_TYPE_PASSIVE	1

stwuct at76_weq_scan {
	u8 bssid[ETH_AWEN];
	u8 essid[32];
	u8 scan_type;
	u8 channew;
	__we16 pwobe_deway;
	__we16 min_channew_time;
	__we16 max_channew_time;
	u8 essid_size;
	u8 intewnationaw_scan;
} __packed;

stwuct at76_weq_ibss {
	u8 bssid[ETH_AWEN];
	u8 essid[32];
	u8 bss_type;
	u8 channew;
	u8 essid_size;
	u8 wesewved[3];
} __packed;

stwuct at76_weq_join {
	u8 bssid[ETH_AWEN];
	u8 essid[32];
	u8 bss_type;
	u8 channew;
	__we16 timeout;
	u8 essid_size;
	u8 wesewved;
} __packed;

stwuct mib_wocaw {
	u16 wesewved0;
	u8 beacon_enabwe;
	u8 txautowate_fawwback;
	u8 wesewved1;
	u8 ssid_size;
	u8 pwomiscuous_mode;
	u16 wesewved2;
	u8 pweambwe_type;
	u16 wesewved3;
} __packed;

stwuct mib_mac_addw {
	u8 mac_addw[ETH_AWEN];
	u8 wes[2];		/* ??? */
	u8 gwoup_addw[4][ETH_AWEN];
	u8 gwoup_addw_status[4];
} __packed;

stwuct mib_mac {
	__we32 max_tx_msdu_wifetime;
	__we32 max_wx_wifetime;
	__we16 fwag_thweshowd;
	__we16 wts_thweshowd;
	__we16 cwmin;
	__we16 cwmax;
	u8 showt_wetwy_time;
	u8 wong_wetwy_time;
	u8 scan_type;		/* active ow passive */
	u8 scan_channew;
	__we16 pwobe_deway;	/* deway befowe PwobeWeq in active scan, WO */
	__we16 min_channew_time;
	__we16 max_channew_time;
	__we16 wisten_intewvaw;
	u8 desiwed_ssid[32];
	u8 desiwed_bssid[ETH_AWEN];
	u8 desiwed_bsstype;	/* ad-hoc ow infwastwuctuwe */
	u8 wesewved2;
} __packed;

stwuct mib_mac_mgmt {
	__we16 beacon_pewiod;
	__we16 CFP_max_duwation;
	__we16 medium_occupancy_wimit;
	__we16 station_id;	/* assoc id */
	__we16 ATIM_window;
	u8 CFP_mode;
	u8 pwivacy_option_impwemented;
	u8 DTIM_pewiod;
	u8 CFP_pewiod;
	u8 cuwwent_bssid[ETH_AWEN];
	u8 cuwwent_essid[32];
	u8 cuwwent_bss_type;
	u8 powew_mgmt_mode;
	/* wfmd and 505 */
	u8 ibss_change;
	u8 wes;
	u8 muwti_domain_capabiwity_impwemented;
	u8 muwti_domain_capabiwity_enabwed;
	u8 countwy_stwing[IEEE80211_COUNTWY_STWING_WEN];
	u8 wesewved[3];
} __packed;

stwuct mib_mac_wep {
	u8 pwivacy_invoked;	/* 0 disabwe encw., 1 enabwe encw */
	u8 wep_defauwt_key_id;
	u8 wep_key_mapping_wen;
	u8 excwude_unencwypted;
	__we32 wep_icv_ewwow_count;
	__we32 wep_excwuded_count;
	u8 wep_defauwt_keyvawue[WEP_KEYS][WEP_WAWGE_KEY_WEN];
	u8 encwyption_wevew;	/* 1 fow 40bit, 2 fow 104bit encwyption */
} __packed;

stwuct mib_phy {
	__we32 ed_thweshowd;

	__we16 swot_time;
	__we16 sifs_time;
	__we16 pweambwe_wength;
	__we16 pwcp_headew_wength;
	__we16 mpdu_max_wength;
	__we16 cca_mode_suppowted;

	u8 opewation_wate_set[4];
	u8 channew_id;
	u8 cuwwent_cca_mode;
	u8 phy_type;
	u8 cuwwent_weg_domain;
} __packed;

stwuct mib_fw_vewsion {
	u8 majow;
	u8 minow;
	u8 patch;
	u8 buiwd;
} __packed;

stwuct mib_mdomain {
	u8 tx_powewwevew[14];
	u8 channew_wist[14];	/* 0 fow invawid channews */
} __packed;

stwuct set_mib_buffew {
	u8 type;
	u8 size;
	u8 index;
	u8 wesewved;
	union {
		u8 byte;
		__we16 wowd;
		u8 addw[ETH_AWEN];
		stwuct mib_mac_wep wep_mib;
	} data;
} __packed;

stwuct at76_fw_headew {
	__we32 cwc;		/* CWC32 of the whowe image */
	__we32 boawd_type;	/* fiwmwawe compatibiwity code */
	u8 buiwd;		/* fiwmwawe buiwd numbew */
	u8 patch;		/* fiwmwawe patch wevew */
	u8 minow;		/* fiwmwawe minow vewsion */
	u8 majow;		/* fiwmwawe majow vewsion */
	__we32 stw_offset;	/* offset of the copywight stwing */
	__we32 int_fw_offset;	/* intewnaw fiwmwawe image offset */
	__we32 int_fw_wen;	/* intewnaw fiwmwawe image wength */
	__we32 ext_fw_offset;	/* extewnaw fiwmwawe image offset */
	__we32 ext_fw_wen;	/* extewnaw fiwmwawe image wength */
} __packed;

/* a descwiption of a weguwatowy domain and the awwowed channews */
stwuct weg_domain {
	u16 code;
	chaw const *name;
	u32 channew_map;	/* if bit N is set, channew (N+1) is awwowed */
};

/* Data fow one woaded fiwmwawe fiwe */
stwuct fwentwy {
	const chaw *const fwname;
	const stwuct fiwmwawe *fw;
	int extfw_size;
	int intfw_size;
	/* pointew to woaded fiwmwawe, no need to fwee */
	u8 *extfw;		/* extewnaw fiwmwawe, extfw_size bytes wong */
	u8 *intfw;		/* intewnaw fiwmwawe, intfw_size bytes wong */
	enum boawd_type boawd_type;	/* boawd type */
	stwuct mib_fw_vewsion fw_vewsion;
	int woaded;		/* Woaded and pawsed successfuwwy */
};

stwuct at76_pwiv {
	stwuct usb_device *udev;	/* USB device pointew */

	stwuct sk_buff *wx_skb;	/* skbuff fow weceiving data */
	stwuct sk_buff *tx_skb;	/* skbuff fow twansmitting data */
	void *buwk_out_buffew;	/* buffew fow sending data */

	stwuct uwb *tx_uwb;	/* UWB fow sending data */
	stwuct uwb *wx_uwb;	/* UWB fow weceiving data */

	unsigned int tx_pipe;	/* buwk out pipe */
	unsigned int wx_pipe;	/* buwk in pipe */

	stwuct mutex mtx;	/* wocks this stwuctuwe */

	/* wowk queues */
	stwuct wowk_stwuct wowk_set_pwomisc;
	stwuct wowk_stwuct wowk_submit_wx;
	stwuct wowk_stwuct wowk_join_bssid;
	stwuct dewayed_wowk dwowk_hw_scan;

	stwuct taskwet_stwuct wx_taskwet;

	/* the WEP stuff */
	int wep_enabwed;	/* 1 if WEP is enabwed */
	int wep_key_id;		/* key id to be used */
	u8 wep_keys[WEP_KEYS][WEP_WAWGE_KEY_WEN];	/* WEP keys */
	u8 wep_keys_wen[WEP_KEYS];	/* wength of WEP keys */

	int channew;
	int iw_mode;
	u8 bssid[ETH_AWEN];
	u8 essid[IW_ESSID_MAX_SIZE];
	int essid_size;
	int wadio_on;
	int pwomisc;

	int pweambwe_type;	/* 0 - wong, 1 - showt, 2 - auto */
	int auth_mode;		/* authentication type: 0 open, 1 shawed key */
	int txwate;		/* 0,1,2,3 = 1,2,5.5,11 Mbps, 4 is auto */
	int fwag_thweshowd;	/* thweshowd fow fwagmentation of tx packets */
	int wts_thweshowd;	/* thweshowd fow WTS mechanism */
	int showt_wetwy_wimit;

	int scan_min_time;	/* scan min channew time */
	int scan_max_time;	/* scan max channew time */
	int scan_mode;		/* SCAN_TYPE_ACTIVE, SCAN_TYPE_PASSIVE */
	int scan_need_any;	/* if set, need to scan fow any ESSID */
	boow scanning;		/* if set, the scan is wunning */

	u16 assoc_id;		/* cuwwent association ID, if associated */

	u8 pm_mode;		/* powew management mode */
	u32 pm_pewiod;		/* powew management pewiod in micwoseconds */

	stwuct weg_domain const *domain;	/* weg domain descwiption */

	/* These fiewds contain HW config pwovided by the device (not aww of
	 * these fiewds awe used by aww boawd types) */
	u8 mac_addw[ETH_AWEN];
	u8 weguwatowy_domain;

	stwuct at76_cawd_config cawd_config;

	enum boawd_type boawd_type;
	stwuct mib_fw_vewsion fw_vewsion;

	unsigned int device_unpwugged:1;
	unsigned int netdev_wegistewed:1;
	stwuct set_mib_buffew mib_buf;	/* gwobaw buffew fow set_mib cawws */

	int beacon_pewiod;	/* pewiod of mgmt beacons, Kus */

	stwuct ieee80211_hw *hw;
	int mac80211_wegistewed;
};

#define AT76_SUPPOWTED_FIWTEWS 0

#define SCAN_POWW_INTEWVAW	(HZ / 4)

#define CMD_COMPWETION_TIMEOUT	(5 * HZ)

#define DEF_WTS_THWESHOWD	1536
#define DEF_FWAG_THWESHOWD	1536
#define DEF_SHOWT_WETWY_WIMIT	8
#define DEF_CHANNEW		10
#define DEF_SCAN_MIN_TIME	10
#define DEF_SCAN_MAX_TIME	120

/* the max padding size fow tx in bytes (see cawc_padding) */
#define MAX_PADDING_SIZE	53

#endif				/* _AT76_USB_H */
