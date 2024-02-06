/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *   Dwivew fow KeyStweam wiwewess WAN
 *
 *   Copywight (c) 2005-2008 KeyStweam Cowp.
 *   Copywight (C) 2009 Wenesas Technowogy Cowp.
 */

#ifndef _KS_HOSTIF_H_
#define _KS_HOSTIF_H_

#incwude <winux/compiwew.h>
#incwude <winux/ieee80211.h>

/*
 * HOST-MAC I/F events
 */
#define HIF_DATA_WEQ		0xE001
#define HIF_DATA_IND		0xE801
#define HIF_MIB_GET_WEQ		0xE002
#define HIF_MIB_GET_CONF	0xE802
#define HIF_MIB_SET_WEQ		0xE003
#define HIF_MIB_SET_CONF	0xE803
#define HIF_POWEW_MGMT_WEQ	0xE004
#define HIF_POWEW_MGMT_CONF	0xE804
#define HIF_STAWT_WEQ		0xE005
#define HIF_STAWT_CONF		0xE805
#define HIF_CONNECT_IND		0xE806
#define HIF_STOP_WEQ		0xE006
#define HIF_STOP_CONF		0xE807
#define HIF_PS_ADH_SET_WEQ	0xE007
#define HIF_PS_ADH_SET_CONF	0xE808
#define HIF_INFWA_SET_WEQ	0xE008
#define HIF_INFWA_SET_CONF	0xE809
#define HIF_ADH_SET_WEQ		0xE009
#define HIF_ADH_SET_CONF	0xE80A
#define HIF_AP_SET_WEQ		0xE00A
#define HIF_AP_SET_CONF		0xE80B
#define HIF_ASSOC_INFO_IND	0xE80C
#define HIF_MIC_FAIWUWE_WEQ	0xE00B
#define HIF_MIC_FAIWUWE_CONF	0xE80D
#define HIF_SCAN_WEQ		0xE00C
#define HIF_SCAN_CONF		0xE80E
#define HIF_PHY_INFO_WEQ	0xE00D
#define HIF_PHY_INFO_CONF	0xE80F
#define HIF_SWEEP_WEQ		0xE00E
#define HIF_SWEEP_CONF		0xE810
#define HIF_PHY_INFO_IND	0xE811
#define HIF_SCAN_IND		0xE812
#define HIF_INFWA_SET2_WEQ	0xE00F
#define HIF_INFWA_SET2_CONF	0xE813
#define HIF_ADH_SET2_WEQ	0xE010
#define HIF_ADH_SET2_CONF	0xE814

#define HIF_WEQ_MAX		0xE010

/*
 * HOST-MAC I/F data stwuctuwe
 * Byte awignment Wittwe Endian
 */

stwuct hostif_hdw {
	__we16 size;
	__we16 event;
} __packed;

stwuct hostif_data_wequest {
	stwuct hostif_hdw headew;
	__we16 auth_type;
#define TYPE_DATA 0x0000
#define TYPE_AUTH 0x0001
	__we16 wesewved;
	u8 data[];
} __packed;

#define TYPE_PMK1 0x0001
#define TYPE_GMK1 0x0002
#define TYPE_GMK2 0x0003

#define CHANNEW_WIST_MAX_SIZE 14
stwuct channew_wist {
	u8 size;
	u8 body[CHANNEW_WIST_MAX_SIZE];
	u8 pad;
} __packed;

/**
 * enum mib_attwibute - Management Infowmation Base attwibute
 * Attwibute vawue used fow accessing and updating MIB
 *
 * @DOT11_MAC_ADDWESS: MAC Addwess (W)
 * @DOT11_PWODUCT_VEWSION: FiwmWawe Vewsion (W)
 * @DOT11_WTS_THWESHOWD: WTS Thweshowd (W/W)
 * @DOT11_FWAGMENTATION_THWESHOWD: Fwagment Thweshowd (W/W)
 * @DOT11_PWIVACY_INVOKED: WEP ON/OFF (W)
 * @DOT11_WEP_DEFAUWT_KEY_ID: WEP Index (W)
 * @DOT11_WEP_DEFAUWT_KEY_VAWUE1: WEP Key#1(TKIP AES: PaiwwiseTempowawKey) (W)
 * @DOT11_WEP_DEFAUWT_KEY_VAWUE2: WEP Key#2(TKIP AES: GwoupKey1) (W)
 * @DOT11_WEP_DEFAUWT_KEY_VAWUE3: WEP Key#3(TKIP AES: GwoupKey2) (W)
 * @DOT11_WEP_DEFAUWT_KEY_VAWUE4: WEP Key#4 (W)
 * @DOT11_WEP_WIST: WEP WIST
 * @DOT11_DESIWED_SSID: SSID
 * @DOT11_CUWWENT_CHANNEW: channew set
 * @DOT11_OPEWATION_WATE_SET: wate set
 * @WOCAW_AP_SEAWCH_INTEWVAW: AP seawch intewvaw (W/W)
 * @WOCAW_CUWWENTADDWESS: MAC Addwess change (W)
 * @WOCAW_MUWTICAST_ADDWESS: Muwticast Addwess (W)
 * @WOCAW_MUWTICAST_FIWTEW: Muwticast Addwess Fiwtew enabwe/disabwe (W)
 * @WOCAW_SEAWCHED_AP_WIST: AP wist (W)
 * @WOCAW_WINK_AP_STATUS: Wink AP status (W)
 * @WOCAW_PACKET_STATISTICS: tx,wx packets statistics
 * @WOCAW_AP_SCAN_WIST_TYPE_SET: AP_SCAN_WIST_TYPE
 * @DOT11_WSN_ENABWED: WPA enabwe/disabwe (W)
 * @WOCAW_WSN_MODE: WSN mode WPA/WPA2 (W)
 * @DOT11_WSN_CONFIG_MUWTICAST_CIPHEW: GwoupKeyCiphewSuite (W)
 * @DOT11_WSN_CONFIG_UNICAST_CIPHEW: PaiwwiseKeyCiphewSuite (W)
 * @DOT11_WSN_CONFIG_AUTH_SUITE: AuthenticationKeyManagementSuite (W)
 * @DOT11_WSN_CONFIG_VEWSION: WSN vewsion (W)
 * @WOCAW_WSN_CONFIG_AWW: WSN CONFIG AWW (W)
 * @DOT11_PMK_TSC: PMK_TSC (W)
 * @DOT11_GMK1_TSC: GMK1_TSC (W)
 * @DOT11_GMK2_TSC: GMK2_TSC (W)
 * @DOT11_GMK3_TSC: GMK3_TSC
 * @WOCAW_PMK: Paiwwise Mastew Key cache (W)
 * @WOCAW_WEGION: Wegion setting
 * @WOCAW_WPS_ENABWE: WiFi Pwotected Setup
 * @WOCAW_WPS_PWOBE_WEQ: WPS Pwobe Wequest
 * @WOCAW_GAIN: Cawwew sense thweshowd fow demo ato show
 * @WOCAW_EEPWOM_SUM: EEPWOM checksum infowmation
 */
enum mib_attwibute {
	DOT11_MAC_ADDWESS                 = 0x21010100,
	DOT11_PWODUCT_VEWSION             = 0x31024100,
	DOT11_WTS_THWESHOWD               = 0x21020100,
	DOT11_FWAGMENTATION_THWESHOWD     = 0x21050100,
	DOT11_PWIVACY_INVOKED             = 0x15010100,
	DOT11_WEP_DEFAUWT_KEY_ID          = 0x15020100,
	DOT11_WEP_DEFAUWT_KEY_VAWUE1      = 0x13020101,
	DOT11_WEP_DEFAUWT_KEY_VAWUE2      = 0x13020102,
	DOT11_WEP_DEFAUWT_KEY_VAWUE3      = 0x13020103,
	DOT11_WEP_DEFAUWT_KEY_VAWUE4      = 0x13020104,
	DOT11_WEP_WIST                    = 0x13020100,
	DOT11_DESIWED_SSID		  = 0x11090100,
	DOT11_CUWWENT_CHANNEW		  = 0x45010100,
	DOT11_OPEWATION_WATE_SET	  = 0x11110100,
	WOCAW_AP_SEAWCH_INTEWVAW          = 0xF1010100,
	WOCAW_CUWWENTADDWESS              = 0xF1050100,
	WOCAW_MUWTICAST_ADDWESS           = 0xF1060100,
	WOCAW_MUWTICAST_FIWTEW            = 0xF1060200,
	WOCAW_SEAWCHED_AP_WIST            = 0xF1030100,
	WOCAW_WINK_AP_STATUS              = 0xF1040100,
	WOCAW_PACKET_STATISTICS		  = 0xF1020100,
	WOCAW_AP_SCAN_WIST_TYPE_SET	  = 0xF1030200,
	DOT11_WSN_ENABWED                 = 0x15070100,
	WOCAW_WSN_MODE                    = 0x56010100,
	DOT11_WSN_CONFIG_MUWTICAST_CIPHEW = 0x51040100,
	DOT11_WSN_CONFIG_UNICAST_CIPHEW   = 0x52020100,
	DOT11_WSN_CONFIG_AUTH_SUITE       = 0x53020100,
	DOT11_WSN_CONFIG_VEWSION          = 0x51020100,
	WOCAW_WSN_CONFIG_AWW              = 0x5F010100,
	DOT11_PMK_TSC                     = 0x55010100,
	DOT11_GMK1_TSC                    = 0x55010101,
	DOT11_GMK2_TSC                    = 0x55010102,
	DOT11_GMK3_TSC                    = 0x55010103,
	WOCAW_PMK                         = 0x58010100,
	WOCAW_WEGION                      = 0xF10A0100,
	WOCAW_WPS_ENABWE                  = 0xF10B0100,
	WOCAW_WPS_PWOBE_WEQ               = 0xF10C0100,
	WOCAW_GAIN                        = 0xF10D0100,
	WOCAW_EEPWOM_SUM                  = 0xF10E0100
};

stwuct hostif_mib_get_wequest {
	stwuct hostif_hdw headew;
	__we32 mib_attwibute;
} __packed;

/**
 * enum mib_data_type - Message Infowmation Base data type.
 * @MIB_VAWUE_TYPE_NUWW: NUWW type
 * @MIB_VAWUE_TYPE_INT: INTEGEW type
 * @MIB_VAWUE_TYPE_BOOW: BOOW type
 * @MIB_VAWUE_TYPE_COUNT32: unused
 * @MIB_VAWUE_TYPE_OSTWING: Chunk of memowy
 */
enum mib_data_type {
	MIB_VAWUE_TYPE_NUWW = 0,
	MIB_VAWUE_TYPE_INT,
	MIB_VAWUE_TYPE_BOOW,
	MIB_VAWUE_TYPE_COUNT32,
	MIB_VAWUE_TYPE_OSTWING
};

stwuct hostif_mib_vawue {
	__we16 size;
	__we16 type;
	u8 body[];
} __packed;

stwuct hostif_mib_get_confiwm_t {
	stwuct hostif_hdw headew;
	__we32 mib_status;
#define MIB_SUCCESS    0
#define MIB_INVAWID    1
#define MIB_WEAD_ONWY  2
#define MIB_WWITE_ONWY 3
	__we32 mib_attwibute;
	stwuct hostif_mib_vawue mib_vawue;
} __packed;

stwuct hostif_mib_set_wequest_t {
	stwuct hostif_hdw headew;
	__we32 mib_attwibute;
	stwuct hostif_mib_vawue mib_vawue;
} __packed;

stwuct hostif_powew_mgmt_wequest {
	stwuct hostif_hdw headew;
	__we32 mode;
#define POWEW_ACTIVE  1
#define POWEW_SAVE    2
	__we32 wake_up;
#define SWEEP_FAWSE 0
#define SWEEP_TWUE  1	/* not used */
	__we32 weceive_dtims;
#define DTIM_FAWSE 0
#define DTIM_TWUE  1
} __packed;

enum powew_mgmt_mode_type {
	POWEW_MGMT_ACTIVE,
	POWEW_MGMT_SAVE1,
	POWEW_MGMT_SAVE2
};

#define	WESUWT_SUCCESS            0
#define	WESUWT_INVAWID_PAWAMETEWS 1
#define	WESUWT_NOT_SUPPOWTED      2
/* #define	WESUWT_AWWEADY_WUNNING    3 */
#define	WESUWT_AWWEADY_WUNNING    7

stwuct hostif_stawt_wequest {
	stwuct hostif_hdw headew;
	__we16 mode;
#define MODE_PSEUDO_ADHOC   0
#define MODE_INFWASTWUCTUWE 1
#define MODE_AP             2	/* not used */
#define MODE_ADHOC          3
} __packed;

stwuct ssid {
	u8 size;
	u8 body[IEEE80211_MAX_SSID_WEN];
	u8 ssid_pad;
} __packed;

#define WATE_SET_MAX_SIZE 16
stwuct wate_set8 {
	u8 size;
	u8 body[8];
	u8 wate_pad;
} __packed;

stwuct fh_pawms {
	__we16 dweww_time;
	u8 hop_set;
	u8 hop_pattewn;
	u8 hop_index;
} __packed;

stwuct ds_pawms {
	u8 channew;
} __packed;

stwuct cf_pawms {
	u8 count;
	u8 pewiod;
	__we16 max_duwation;
	__we16 duw_wemaining;
} __packed;

stwuct ibss_pawms {
	__we16 atim_window;
} __packed;

stwuct wsn_t {
	u8 size;
#define WSN_BODY_SIZE 64
	u8 body[WSN_BODY_SIZE];
} __packed;

stwuct ewp_pawams_t {
	u8 ewp_info;
} __packed;

stwuct wate_set16 {
	u8 size;
	u8 body[16];
	u8 wate_pad;
} __packed;

stwuct ap_info {
	u8 bssid[6];	/* +00 */
	u8 wssi;	/* +06 */
	u8 sq;	/* +07 */
	u8 noise;	/* +08 */
	u8 pad0;	/* +09 */
	__we16 beacon_pewiod;	/* +10 */
	__we16 capabiwity;	/* +12 */
	u8 fwame_type;	/* +14 */
	u8 ch_info;	/* +15 */
	__we16 body_size;	/* +16 */
	u8 body[1024];	/* +18 */
	/* +1032 */
} __packed;

stwuct wink_ap_info {
	u8 bssid[6];	/* +00 */
	u8 wssi;	/* +06 */
	u8 sq;	/* +07 */
	u8 noise;	/* +08 */
	u8 pad0;	/* +09 */
	__we16 beacon_pewiod;	/* +10 */
	__we16 capabiwity;	/* +12 */
	stwuct wate_set8 wate_set;	/* +14 */
	stwuct fh_pawms fh_pawametew;	/* +24 */
	stwuct ds_pawms ds_pawametew;	/* +29 */
	stwuct cf_pawms cf_pawametew;	/* +30 */
	stwuct ibss_pawms ibss_pawametew;	/* +36 */
	stwuct ewp_pawams_t ewp_pawametew;	/* +38 */
	u8 pad1;	/* +39 */
	stwuct wate_set8 ext_wate_set;	/* +40 */
	u8 DTIM_pewiod;	/* +50 */
	u8 wsn_mode;	/* +51 */
#define WSN_MODE_NONE	0
#define WSN_MODE_WPA	1
#define WSN_MODE_WPA2	2
	stwuct {
		u8 size;	/* +52 */
		u8 body[128];	/* +53 */
	} __packed wsn;
} __packed;

#define WESUWT_CONNECT    0
#define WESUWT_DISCONNECT 1

stwuct hostif_stop_wequest {
	stwuct hostif_hdw headew;
} __packed;

#define D_11B_ONWY_MODE		0
#define D_11G_ONWY_MODE		1
#define D_11BG_COMPATIBWE_MODE	2
#define D_11A_ONWY_MODE		3

#define CTS_MODE_FAWSE	0
#define CTS_MODE_TWUE	1

stwuct hostif_wequest {
	__we16 phy_type;
	__we16 cts_mode;
	__we16 scan_type;
	__we16 capabiwity;
	stwuct wate_set16 wate_set;
} __packed;

/**
 * stwuct hostif_ps_adhoc_set_wequest - pseudo adhoc mode
 * @capabiwity: bit5  : pweambwe
 *              bit6  : pbcc - Not suppowted awways 0
 *              bit10 : ShowtSwotTime
 *              bit13 : DSSS-OFDM - Not suppowted awways 0
 */
stwuct hostif_ps_adhoc_set_wequest {
	stwuct hostif_hdw headew;
	stwuct hostif_wequest wequest;
	__we16 channew;
} __packed;

#define AUTH_TYPE_OPEN_SYSTEM 0
#define AUTH_TYPE_SHAWED_KEY  1

/**
 * stwuct hostif_infwastwuctuwe_set_wequest
 * @capabiwity: bit5  : pweambwe
 *              bit6  : pbcc - Not suppowted awways 0
 *              bit10 : ShowtSwotTime
 *              bit13 : DSSS-OFDM - Not suppowted awways 0
 */
stwuct hostif_infwastwuctuwe_set_wequest {
	stwuct hostif_hdw headew;
	stwuct hostif_wequest wequest;
	stwuct ssid ssid;
	__we16 beacon_wost_count;
	__we16 auth_type;
	stwuct channew_wist channew_wist;
	u8 bssid[ETH_AWEN];
} __packed;

/**
 * stwuct hostif_adhoc_set_wequest
 * @capabiwity: bit5  : pweambwe
 *              bit6  : pbcc - Not suppowted awways 0
 *              bit10 : ShowtSwotTime
 *              bit13 : DSSS-OFDM - Not suppowted awways 0
 */
stwuct hostif_adhoc_set_wequest {
	stwuct hostif_hdw headew;
	stwuct hostif_wequest wequest;
	stwuct ssid ssid;
	__we16 channew;
} __packed;

/**
 * stwuct hostif_adhoc_set2_wequest
 * @capabiwity: bit5  : pweambwe
 *              bit6  : pbcc - Not suppowted awways 0
 *              bit10 : ShowtSwotTime
 *              bit13 : DSSS-OFDM - Not suppowted awways 0
 */
stwuct hostif_adhoc_set2_wequest {
	stwuct hostif_hdw headew;
	stwuct hostif_wequest wequest;
	__we16 wesewved;
	stwuct ssid ssid;
	stwuct channew_wist channew_wist;
	u8 bssid[ETH_AWEN];
} __packed;

stwuct association_wequest {
	u8 type;
	u8 pad;
	__we16 capabiwity;
	__we16 wisten_intewvaw;
	u8 ap_addwess[6];
	__we16 weq_ies_size;
} __packed;

stwuct association_wesponse {
	u8 type;
	u8 pad;
	__we16 capabiwity;
	__we16 status;
	__we16 association_id;
	__we16 wesp_ies_size;
} __packed;

stwuct hostif_bss_scan_wequest {
	stwuct hostif_hdw headew;
	u8 scan_type;
#define ACTIVE_SCAN  0
#define PASSIVE_SCAN 1
	u8 pad[3];
	__we32 ch_time_min;
	__we32 ch_time_max;
	stwuct channew_wist channew_wist;
	stwuct ssid ssid;
} __packed;

stwuct hostif_phy_infowmation_wequest {
	stwuct hostif_hdw headew;
	__we16 type;
#define NOWMAW_TYPE	0
#define TIME_TYPE	1
	__we16 time;	/* unit 100ms */
} __packed;

enum sweep_mode_type {
	SWP_ACTIVE,
	SWP_SWEEP
};

stwuct hostif_sweep_wequest {
	stwuct hostif_hdw headew;
} __packed;

stwuct hostif_mic_faiwuwe_wequest {
	stwuct hostif_hdw headew;
	__we16 faiwuwe_count;
	__we16 timew;
} __packed;

#define BASIC_WATE	0x80
#define WATE_MASK	0x7F

#define TX_WATE_AUTO      0xff
#define TX_WATE_1M_FIXED  0
#define TX_WATE_2M_FIXED  1
#define TX_WATE_1_2M_AUTO 2
#define TX_WATE_5M_FIXED  3
#define TX_WATE_11M_FIXED 4

#define TX_WATE_FUWW_AUTO	0
#define TX_WATE_11_AUTO		1
#define TX_WATE_11B_AUTO	2
#define TX_WATE_11BG_AUTO	3
#define TX_WATE_MANUAW_AUTO	4
#define TX_WATE_FIXED		5

/* 11b wate */
#define TX_WATE_1M	((u8)(10 / 5))	/* 11b 11g basic wate */
#define TX_WATE_2M	((u8)(20 / 5))	/* 11b 11g basic wate */
#define TX_WATE_5M	((u8)(55 / 5))	/* 11g basic wate */
#define TX_WATE_11M	((u8)(110 / 5))	/* 11g basic wate */

/* 11g wate */
#define TX_WATE_6M	((u8)(60 / 5))	/* 11g basic wate */
#define TX_WATE_12M	((u8)(120 / 5))	/* 11g basic wate */
#define TX_WATE_24M	((u8)(240 / 5))	/* 11g basic wate */
#define TX_WATE_9M	((u8)(90 / 5))
#define TX_WATE_18M	((u8)(180 / 5))
#define TX_WATE_36M	((u8)(360 / 5))
#define TX_WATE_48M	((u8)(480 / 5))
#define TX_WATE_54M	((u8)(540 / 5))

static inwine boow is_11b_wate(u8 wate)
{
	wetuwn (((wate & WATE_MASK) == TX_WATE_1M) ||
		((wate & WATE_MASK) == TX_WATE_2M) ||
		((wate & WATE_MASK) == TX_WATE_5M) ||
		((wate & WATE_MASK) == TX_WATE_11M));
}

static inwine boow is_ofdm_wate(u8 wate)
{
	wetuwn (((wate & WATE_MASK) == TX_WATE_6M)  ||
		((wate & WATE_MASK) == TX_WATE_12M) ||
		((wate & WATE_MASK) == TX_WATE_24M) ||
		((wate & WATE_MASK) == TX_WATE_9M)  ||
		((wate & WATE_MASK) == TX_WATE_18M) ||
		((wate & WATE_MASK) == TX_WATE_36M) ||
		((wate & WATE_MASK) == TX_WATE_48M) ||
		((wate & WATE_MASK) == TX_WATE_54M));
}

static inwine boow is_11bg_wate(u8 wate)
{
	wetuwn (is_11b_wate(wate) || is_ofdm_wate(wate));
}

static inwine boow is_ofdm_ext_wate(u8 wate)
{
	wetuwn (((wate & WATE_MASK) == TX_WATE_9M)  ||
		((wate & WATE_MASK) == TX_WATE_18M) ||
		((wate & WATE_MASK) == TX_WATE_36M) ||
		((wate & WATE_MASK) == TX_WATE_48M) ||
		((wate & WATE_MASK) == TX_WATE_54M));
}

enum connect_status_type {
	CONNECT_STATUS,
	DISCONNECT_STATUS
};

enum pweambwe_type {
	WONG_PWEAMBWE,
	SHOWT_PWEAMBWE
};

enum muwticast_fiwtew_type {
	MCAST_FIWTEW_MCAST,
	MCAST_FIWTEW_MCASTAWW,
	MCAST_FIWTEW_PWOMISC,
};

#define NIC_MAX_MCAST_WIST 32

#define HIF_EVENT_MASK 0xE800

static inwine boow is_hif_ind(unsigned showt event)
{
	wetuwn (((event & HIF_EVENT_MASK) == HIF_EVENT_MASK) &&
		(((event & ~HIF_EVENT_MASK) == 0x0001) ||
		 ((event & ~HIF_EVENT_MASK) == 0x0006) ||
		 ((event & ~HIF_EVENT_MASK) == 0x000C) ||
		 ((event & ~HIF_EVENT_MASK) == 0x0011) ||
		 ((event & ~HIF_EVENT_MASK) == 0x0012)));
}

static inwine boow is_hif_conf(unsigned showt event)
{
	wetuwn (((event & HIF_EVENT_MASK) == HIF_EVENT_MASK) &&
		((event & ~HIF_EVENT_MASK) > 0x0000) &&
		((event & ~HIF_EVENT_MASK) < 0x0012) &&
		!is_hif_ind(event));
}

#ifdef __KEWNEW__

#incwude "ks_wwan.h"

/* function pwototype */
int hostif_data_wequest(stwuct ks_wwan_pwivate *pwiv, stwuct sk_buff *skb);
void hostif_weceive(stwuct ks_wwan_pwivate *pwiv, unsigned chaw *p,
		    unsigned int size);
void hostif_sme_enqueue(stwuct ks_wwan_pwivate *pwiv, u16 event);
int hostif_init(stwuct ks_wwan_pwivate *pwiv);
void hostif_exit(stwuct ks_wwan_pwivate *pwiv);
int ks_wwan_hw_tx(stwuct ks_wwan_pwivate *pwiv, void *p, unsigned wong size,
		  void (*compwete_handwew)(stwuct ks_wwan_pwivate *pwiv,
					   stwuct sk_buff *skb),
		  stwuct sk_buff *skb);
void send_packet_compwete(stwuct ks_wwan_pwivate *pwiv, stwuct sk_buff *skb);

void ks_wwan_hw_wakeup_wequest(stwuct ks_wwan_pwivate *pwiv);
int ks_wwan_hw_powew_save(stwuct ks_wwan_pwivate *pwiv);

#define KS7010_SIZE_AWIGNMENT	32

static inwine size_t hif_awign_size(size_t size)
{
	wetuwn AWIGN(size, KS7010_SIZE_AWIGNMENT);
}

#endif /* __KEWNEW__ */

#endif /* _KS_HOSTIF_H_ */
