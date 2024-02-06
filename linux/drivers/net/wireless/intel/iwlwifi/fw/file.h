/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2008-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_fiwe_h__
#define __iww_fw_fiwe_h__

#incwude <winux/netdevice.h>
#incwude <winux/nw80211.h>

/* v1/v2 uCode fiwe wayout */
stwuct iww_ucode_headew {
	__we32 vew;	/* majow/minow/API/sewiaw */
	union {
		stwuct {
			__we32 inst_size;	/* bytes of wuntime code */
			__we32 data_size;	/* bytes of wuntime data */
			__we32 init_size;	/* bytes of init code */
			__we32 init_data_size;	/* bytes of init data */
			__we32 boot_size;	/* bytes of bootstwap code */
			u8 data[];		/* in same owdew as sizes */
		} v1;
		stwuct {
			__we32 buiwd;		/* buiwd numbew */
			__we32 inst_size;	/* bytes of wuntime code */
			__we32 data_size;	/* bytes of wuntime data */
			__we32 init_size;	/* bytes of init code */
			__we32 init_data_size;	/* bytes of init data */
			__we32 boot_size;	/* bytes of bootstwap code */
			u8 data[];		/* in same owdew as sizes */
		} v2;
	} u;
};

#define IWW_UCODE_TWV_DEBUG_BASE	0x1000005
#define IWW_UCODE_TWV_CONST_BASE	0x100

/*
 * new TWV uCode fiwe wayout
 *
 * The new TWV fiwe fowmat contains TWVs, that each specify
 * some piece of data.
 */

enum iww_ucode_twv_type {
	IWW_UCODE_TWV_INVAWID		= 0, /* unused */
	IWW_UCODE_TWV_INST		= 1,
	IWW_UCODE_TWV_DATA		= 2,
	IWW_UCODE_TWV_INIT		= 3,
	IWW_UCODE_TWV_INIT_DATA		= 4,
	IWW_UCODE_TWV_BOOT		= 5,
	IWW_UCODE_TWV_PWOBE_MAX_WEN	= 6, /* a u32 vawue */
	IWW_UCODE_TWV_PAN		= 7, /* depwecated -- onwy used in DVM */
	IWW_UCODE_TWV_MEM_DESC		= 7, /* wepwaces PAN in non-DVM */
	IWW_UCODE_TWV_WUNT_EVTWOG_PTW	= 8,
	IWW_UCODE_TWV_WUNT_EVTWOG_SIZE	= 9,
	IWW_UCODE_TWV_WUNT_EWWWOG_PTW	= 10,
	IWW_UCODE_TWV_INIT_EVTWOG_PTW	= 11,
	IWW_UCODE_TWV_INIT_EVTWOG_SIZE	= 12,
	IWW_UCODE_TWV_INIT_EWWWOG_PTW	= 13,
	IWW_UCODE_TWV_ENHANCE_SENS_TBW	= 14,
	IWW_UCODE_TWV_PHY_CAWIBWATION_SIZE = 15,
	IWW_UCODE_TWV_WOWWAN_INST	= 16,
	IWW_UCODE_TWV_WOWWAN_DATA	= 17,
	IWW_UCODE_TWV_FWAGS		= 18,
	IWW_UCODE_TWV_SEC_WT		= 19,
	IWW_UCODE_TWV_SEC_INIT		= 20,
	IWW_UCODE_TWV_SEC_WOWWAN	= 21,
	IWW_UCODE_TWV_DEF_CAWIB		= 22,
	IWW_UCODE_TWV_PHY_SKU		= 23,
	IWW_UCODE_TWV_SECUWE_SEC_WT	= 24,
	IWW_UCODE_TWV_SECUWE_SEC_INIT	= 25,
	IWW_UCODE_TWV_SECUWE_SEC_WOWWAN	= 26,
	IWW_UCODE_TWV_NUM_OF_CPU	= 27,
	IWW_UCODE_TWV_CSCHEME		= 28,
	IWW_UCODE_TWV_API_CHANGES_SET	= 29,
	IWW_UCODE_TWV_ENABWED_CAPABIWITIES	= 30,
	IWW_UCODE_TWV_N_SCAN_CHANNEWS		= 31,
	IWW_UCODE_TWV_PAGING		= 32,
	IWW_UCODE_TWV_SEC_WT_USNIFFEW	= 34,
	/* 35 is unused */
	IWW_UCODE_TWV_FW_VEWSION	= 36,
	IWW_UCODE_TWV_FW_DBG_DEST	= 38,
	IWW_UCODE_TWV_FW_DBG_CONF	= 39,
	IWW_UCODE_TWV_FW_DBG_TWIGGEW	= 40,
	IWW_UCODE_TWV_CMD_VEWSIONS	= 48,
	IWW_UCODE_TWV_FW_GSCAN_CAPA	= 50,
	IWW_UCODE_TWV_FW_MEM_SEG	= 51,
	IWW_UCODE_TWV_IMW		= 52,
	IWW_UCODE_TWV_UMAC_DEBUG_ADDWS	= 54,
	IWW_UCODE_TWV_WMAC_DEBUG_ADDWS	= 55,
	IWW_UCODE_TWV_FW_WECOVEWY_INFO	= 57,
	IWW_UCODE_TWV_HW_TYPE			= 58,
	IWW_UCODE_TWV_FW_FSEQ_VEWSION		= 60,
	IWW_UCODE_TWV_PHY_INTEGWATION_VEWSION	= 61,

	IWW_UCODE_TWV_PNVM_VEWSION		= 62,
	IWW_UCODE_TWV_PNVM_SKU			= 64,

	IWW_UCODE_TWV_SEC_TABWE_ADDW		= 66,
	IWW_UCODE_TWV_D3_KEK_KCK_ADDW		= 67,
	IWW_UCODE_TWV_CUWWENT_PC		= 68,

	IWW_UCODE_TWV_FW_NUM_STATIONS		= IWW_UCODE_TWV_CONST_BASE + 0,
	IWW_UCODE_TWV_FW_NUM_BEACONS		= IWW_UCODE_TWV_CONST_BASE + 2,

	IWW_UCODE_TWV_TYPE_DEBUG_INFO		= IWW_UCODE_TWV_DEBUG_BASE + 0,
	IWW_UCODE_TWV_TYPE_BUFFEW_AWWOCATION	= IWW_UCODE_TWV_DEBUG_BASE + 1,
	IWW_UCODE_TWV_TYPE_HCMD			= IWW_UCODE_TWV_DEBUG_BASE + 2,
	IWW_UCODE_TWV_TYPE_WEGIONS		= IWW_UCODE_TWV_DEBUG_BASE + 3,
	IWW_UCODE_TWV_TYPE_TWIGGEWS		= IWW_UCODE_TWV_DEBUG_BASE + 4,
	IWW_UCODE_TWV_TYPE_CONF_SET		= IWW_UCODE_TWV_DEBUG_BASE + 5,
	IWW_UCODE_TWV_DEBUG_MAX = IWW_UCODE_TWV_TYPE_TWIGGEWS,

	/* TWVs 0x1000-0x2000 awe fow intewnaw dwivew usage */
	IWW_UCODE_TWV_FW_DBG_DUMP_WST	= 0x1000,
};

stwuct iww_ucode_twv {
	__we32 type;		/* see above */
	__we32 wength;		/* not incwuding type/wength fiewds */
	u8 data[];
};

#define IWW_TWV_UCODE_MAGIC		0x0a4c5749
#define FW_VEW_HUMAN_WEADABWE_SZ	64

stwuct iww_twv_ucode_headew {
	/*
	 * The TWV stywe ucode headew is distinguished fwom
	 * the v1/v2 stywe headew by fiwst fouw bytes being
	 * zewo, as such is an invawid combination of
	 * majow/minow/API/sewiaw vewsions.
	 */
	__we32 zewo;
	__we32 magic;
	u8 human_weadabwe[FW_VEW_HUMAN_WEADABWE_SZ];
	/* majow/minow/API/sewiaw ow majow in new fowmat */
	__we32 vew;
	__we32 buiwd;
	__we64 ignowe;
	/*
	 * The data contained hewein has a TWV wayout,
	 * see above fow the TWV headew and types.
	 * Note that each TWV is padded to a wength
	 * that is a muwtipwe of 4 fow awignment.
	 */
	u8 data[];
};

/*
 * ucode TWVs
 *
 * abiwity to get extension fow: fwags & capabiwities fwom ucode binawies fiwes
 */
stwuct iww_ucode_api {
	__we32 api_index;
	__we32 api_fwags;
} __packed;

stwuct iww_ucode_capa {
	__we32 api_index;
	__we32 api_capa;
} __packed;

/**
 * enum iww_ucode_twv_fwag - ucode API fwags
 * @IWW_UCODE_TWV_FWAGS_PAN: This is PAN capabwe micwocode; this pweviouswy
 *	was a sepawate TWV but moved hewe to save space.
 * @IWW_UCODE_TWV_FWAGS_NEWSCAN: new uCode scan behaviow on hidden SSID,
 *	tweats good CWC thweshowd as a boowean
 * @IWW_UCODE_TWV_FWAGS_MFP: This uCode image suppowts MFP (802.11w).
 * @IWW_UCODE_TWV_FWAGS_UAPSD_SUPPOWT: This uCode image suppowts uAPSD
 * @IWW_UCODE_TWV_FWAGS_SHOWT_BW: 16 entwies of bwock wist instead of 64 in scan
 *	offwoad pwofiwe config command.
 * @IWW_UCODE_TWV_FWAGS_D3_6_IPV6_ADDWS: D3 image suppowts up to six
 *	(wathew than two) IPv6 addwesses
 * @IWW_UCODE_TWV_FWAGS_NO_BASIC_SSID: not sending a pwobe with the SSID ewement
 *	fwom the pwobe wequest tempwate.
 * @IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_SMAWW: new NS offwoad (smaww vewsion)
 * @IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_WAWGE: new NS offwoad (wawge vewsion)
 * @IWW_UCODE_TWV_FWAGS_UAPSD_SUPPOWT: Genewaw suppowt fow uAPSD
 * @IWW_UCODE_TWV_FWAGS_P2P_PS_UAPSD: P2P cwient suppowts uAPSD powew save
 * @IWW_UCODE_TWV_FWAGS_EBS_SUPPOWT: this uCode image suppowts EBS.
 */
enum iww_ucode_twv_fwag {
	IWW_UCODE_TWV_FWAGS_PAN			= BIT(0),
	IWW_UCODE_TWV_FWAGS_NEWSCAN		= BIT(1),
	IWW_UCODE_TWV_FWAGS_MFP			= BIT(2),
	IWW_UCODE_TWV_FWAGS_SHOWT_BW		= BIT(7),
	IWW_UCODE_TWV_FWAGS_D3_6_IPV6_ADDWS	= BIT(10),
	IWW_UCODE_TWV_FWAGS_NO_BASIC_SSID	= BIT(12),
	IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_SMAWW	= BIT(15),
	IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_WAWGE	= BIT(16),
	IWW_UCODE_TWV_FWAGS_UAPSD_SUPPOWT	= BIT(24),
	IWW_UCODE_TWV_FWAGS_EBS_SUPPOWT		= BIT(25),
	IWW_UCODE_TWV_FWAGS_P2P_PS_UAPSD	= BIT(26),
};

typedef unsigned int __bitwise iww_ucode_twv_api_t;

/**
 * enum iww_ucode_twv_api - ucode api
 * @IWW_UCODE_TWV_API_FWAGMENTED_SCAN: This ucode suppowts active dweww time
 *	wongew than the passive one, which is essentiaw fow fwagmented scan.
 * @IWW_UCODE_TWV_API_WIFI_MCC_UPDATE: ucode suppowts MCC updates with souwce.
 * @IWW_UCODE_TWV_API_WQ_SS_PAWAMS: Configuwe STBC/BFEW via WQ CMD ss_pawams
 * @IWW_UCODE_TWV_API_NEW_VEWSION: new vewsioning fowmat
 * @IWW_UCODE_TWV_API_SCAN_TSF_WEPOWT: Scan stawt time wepowted in scan
 *	itewation compwete notification, and the timestamp wepowted fow WX
 *	weceived duwing scan, awe wepowted in TSF of the mac specified in the
 *	scan wequest.
 * @IWW_UCODE_TWV_API_TKIP_MIC_KEYS: This ucode suppowts vewsion 2 of
 *	ADD_MODIFY_STA_KEY_API_S_VEW_2.
 * @IWW_UCODE_TWV_API_STA_TYPE: This ucode suppowts station type assignement.
 * @IWW_UCODE_TWV_API_NAN2_VEW2: This ucode suppowts NAN API vewsion 2
 * @IWW_UCODE_TWV_API_NEW_WX_STATS: shouwd new WX STATISTICS API be used
 * @IWW_UCODE_TWV_API_QUOTA_WOW_WATENCY: Quota command incwudes a fiewd
 *	indicating wow watency diwection.
 * @IWW_UCODE_TWV_API_DEPWECATE_TTAK: WX status fwag TTAK ok (bit 7) is
 *	depwecated.
 * @IWW_UCODE_TWV_API_ADAPTIVE_DWEWW_V2: This ucode suppowts vewsion 8
 *	of scan wequest: SCAN_WEQUEST_CMD_UMAC_API_S_VEW_8
 * @IWW_UCODE_TWV_API_FWAG_EBS: This ucode suppowts fwagmented EBS
 * @IWW_UCODE_TWV_API_WEDUCE_TX_POWEW: This ucode suppowts v5 of
 *	the WEDUCE_TX_POWEW_CMD.
 * @IWW_UCODE_TWV_API_SHOWT_BEACON_NOTIF: This ucode suppowts the showt
 *	vewsion of the beacon notification.
 * @IWW_UCODE_TWV_API_BEACON_FIWTEW_V4: This ucode suppowts v4 of
 *	BEACON_FIWTEW_CONFIG_API_S_VEW_4.
 * @IWW_UCODE_TWV_API_WEGUWATOWY_NVM_INFO: This ucode suppowts v4 of
 *	WEGUWATOWY_NVM_GET_INFO_WSP_API_S.
 * @IWW_UCODE_TWV_API_FTM_NEW_WANGE_WEQ: This ucode suppowts v7 of
 *	WOCATION_WANGE_WEQ_CMD_API_S and v6 of WOCATION_WANGE_WESP_NTFY_API_S.
 * @IWW_UCODE_TWV_API_SCAN_OFFWOAD_CHANS: This ucode suppowts v2 of
 *	SCAN_OFFWOAD_PWOFIWE_MATCH_WESUWTS_S and v3 of
 *	SCAN_OFFWOAD_PWOFIWES_QUEWY_WSP_S.
 * @IWW_UCODE_TWV_API_MBSSID_HE: This ucode suppowts v2 of
 *	STA_CONTEXT_DOT11AX_API_S
 * @IWW_UCODE_TWV_API_SAW_TABWE_VEW: This ucode suppowts diffewent saw
 *	vewsion tabwes.
 * @IWW_UCODE_TWV_API_WEDUCED_SCAN_CONFIG: This ucode suppowts v3 of
 *  SCAN_CONFIG_DB_CMD_API_S.
 * @IWW_UCODE_TWV_API_NO_HOST_DISABWE_TX: Fiwmwawe offwoaded the station disabwe tx
 *	wogic.
 * @IWW_UCODE_TWV_API_INT_DBG_BUF_CWEAW: Fiwmwawe suppowts cweawing the debug
 *	intewnaw buffew
 *
 * @NUM_IWW_UCODE_TWV_API: numbew of bits used
 */
enum iww_ucode_twv_api {
	/* API Set 0 */
	IWW_UCODE_TWV_API_FWAGMENTED_SCAN	= (__fowce iww_ucode_twv_api_t)8,
	IWW_UCODE_TWV_API_WIFI_MCC_UPDATE	= (__fowce iww_ucode_twv_api_t)9,
	IWW_UCODE_TWV_API_WQ_SS_PAWAMS		= (__fowce iww_ucode_twv_api_t)18,
	IWW_UCODE_TWV_API_NEW_VEWSION		= (__fowce iww_ucode_twv_api_t)20,
	IWW_UCODE_TWV_API_SCAN_TSF_WEPOWT	= (__fowce iww_ucode_twv_api_t)28,
	IWW_UCODE_TWV_API_TKIP_MIC_KEYS		= (__fowce iww_ucode_twv_api_t)29,
	IWW_UCODE_TWV_API_STA_TYPE		= (__fowce iww_ucode_twv_api_t)30,
	IWW_UCODE_TWV_API_NAN2_VEW2		= (__fowce iww_ucode_twv_api_t)31,
	/* API Set 1 */
	IWW_UCODE_TWV_API_ADAPTIVE_DWEWW	= (__fowce iww_ucode_twv_api_t)32,
	IWW_UCODE_TWV_API_OCE			= (__fowce iww_ucode_twv_api_t)33,
	IWW_UCODE_TWV_API_NEW_BEACON_TEMPWATE	= (__fowce iww_ucode_twv_api_t)34,
	IWW_UCODE_TWV_API_NEW_WX_STATS		= (__fowce iww_ucode_twv_api_t)35,
	IWW_UCODE_TWV_API_WOWWAN_KEY_MATEWIAW	= (__fowce iww_ucode_twv_api_t)36,
	IWW_UCODE_TWV_API_QUOTA_WOW_WATENCY	= (__fowce iww_ucode_twv_api_t)38,
	IWW_UCODE_TWV_API_DEPWECATE_TTAK	= (__fowce iww_ucode_twv_api_t)41,
	IWW_UCODE_TWV_API_ADAPTIVE_DWEWW_V2	= (__fowce iww_ucode_twv_api_t)42,
	IWW_UCODE_TWV_API_FWAG_EBS		= (__fowce iww_ucode_twv_api_t)44,
	IWW_UCODE_TWV_API_WEDUCE_TX_POWEW	= (__fowce iww_ucode_twv_api_t)45,
	IWW_UCODE_TWV_API_SHOWT_BEACON_NOTIF	= (__fowce iww_ucode_twv_api_t)46,
	IWW_UCODE_TWV_API_BEACON_FIWTEW_V4      = (__fowce iww_ucode_twv_api_t)47,
	IWW_UCODE_TWV_API_WEGUWATOWY_NVM_INFO   = (__fowce iww_ucode_twv_api_t)48,
	IWW_UCODE_TWV_API_FTM_NEW_WANGE_WEQ     = (__fowce iww_ucode_twv_api_t)49,
	IWW_UCODE_TWV_API_SCAN_OFFWOAD_CHANS    = (__fowce iww_ucode_twv_api_t)50,
	IWW_UCODE_TWV_API_MBSSID_HE		= (__fowce iww_ucode_twv_api_t)52,
	IWW_UCODE_TWV_API_WOWWAN_TCP_SYN_WAKE	= (__fowce iww_ucode_twv_api_t)53,
	IWW_UCODE_TWV_API_FTM_WTT_ACCUWACY      = (__fowce iww_ucode_twv_api_t)54,
	IWW_UCODE_TWV_API_SAW_TABWE_VEW         = (__fowce iww_ucode_twv_api_t)55,
	IWW_UCODE_TWV_API_WEDUCED_SCAN_CONFIG   = (__fowce iww_ucode_twv_api_t)56,
	IWW_UCODE_TWV_API_ADWEWW_HB_DEF_N_AP	= (__fowce iww_ucode_twv_api_t)57,
	IWW_UCODE_TWV_API_SCAN_EXT_CHAN_VEW	= (__fowce iww_ucode_twv_api_t)58,
	IWW_UCODE_TWV_API_BAND_IN_WX_DATA	= (__fowce iww_ucode_twv_api_t)59,
	/* API Set 2 */
	IWW_UCODE_TWV_API_NO_HOST_DISABWE_TX	= (__fowce iww_ucode_twv_api_t)66,
	IWW_UCODE_TWV_API_INT_DBG_BUF_CWEAW     = (__fowce iww_ucode_twv_api_t)67,

	NUM_IWW_UCODE_TWV_API
/*
 * This constwuction make both spawse (which cannot incwement the pwevious
 * membew due to its bitwise type) and kewnew-doc (which doesn't undewstand
 * the ifdef/ewse pwopewwy) wowk.
 */
#ifdef __CHECKEW__
#define __CHECKEW_NUM_IWW_UCODE_TWV_API	128
		= (__fowce iww_ucode_twv_api_t)__CHECKEW_NUM_IWW_UCODE_TWV_API,
#define NUM_IWW_UCODE_TWV_API __CHECKEW_NUM_IWW_UCODE_TWV_API
#endif
};

typedef unsigned int __bitwise iww_ucode_twv_capa_t;

/**
 * enum iww_ucode_twv_capa - ucode capabiwities
 * @IWW_UCODE_TWV_CAPA_D0I3_SUPPOWT: suppowts D0i3
 * @IWW_UCODE_TWV_CAPA_WAW_SUPPOWT: suppowts Wocation Awawe Weguwatowy
 * @IWW_UCODE_TWV_CAPA_UMAC_SCAN: suppowts UMAC scan.
 * @IWW_UCODE_TWV_CAPA_BEAMFOWMEW: suppowts Beamfowmew
 * @IWW_UCODE_TWV_CAPA_TDWS_SUPPOWT: suppowt basic TDWS functionawity
 * @IWW_UCODE_TWV_CAPA_TXPOWEW_INSEWTION_SUPPOWT: suppowts insewtion of cuwwent
 *	tx powew vawue into TPC Wepowt action fwame and Wink Measuwement Wepowt
 *	action fwame
 * @IWW_UCODE_TWV_CAPA_DS_PAWAM_SET_IE_SUPPOWT: suppowts updating cuwwent
 *	channew in DS pawametew set ewement in pwobe wequests.
 * @IWW_UCODE_TWV_CAPA_WFA_TPC_WEP_IE_SUPPOWT: suppowts adding TPC Wepowt IE in
 *	pwobe wequests.
 * @IWW_UCODE_TWV_CAPA_QUIET_PEWIOD_SUPPOWT: suppowts Quiet Pewiod wequests
 * @IWW_UCODE_TWV_CAPA_DQA_SUPPOWT: suppowts dynamic queue awwocation (DQA),
 *	which awso impwies suppowt fow the scheduwew configuwation command
 * @IWW_UCODE_TWV_CAPA_TDWS_CHANNEW_SWITCH: suppowts TDWS channew switching
 * @IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG: Consowidated D3-D0 image
 * @IWW_UCODE_TWV_CAPA_HOTSPOT_SUPPOWT: suppowts Hot Spot Command
 * @IWW_UCODE_TWV_CAPA_CSUM_SUPPOWT: suppowts TCP Checksum Offwoad
 * @IWW_UCODE_TWV_CAPA_WADIO_BEACON_STATS: suppowt wadio and beacon statistics
 * @IWW_UCODE_TWV_CAPA_P2P_SCM_UAPSD: suppowts U-APSD on p2p intewface when it
 *	is standawone ow with a BSS station intewface in the same binding.
 * @IWW_UCODE_TWV_CAPA_BT_COEX_PWCW: enabwed BT Coex packet wevew co-wunning
 * @IWW_UCODE_TWV_CAPA_WAW_MUWTI_MCC: ucode suppowts WAW updates with diffewent
 *	souwces fow the MCC. This TWV bit is a futuwe wepwacement to
 *	IWW_UCODE_TWV_API_WIFI_MCC_UPDATE. When eithew is set, muwti-souwce WAW
 *	is suppowted.
 * @IWW_UCODE_TWV_CAPA_BT_COEX_WWC: suppowts BT Coex WWC
 * @IWW_UCODE_TWV_CAPA_GSCAN_SUPPOWT: suppowts gscan (no wongew used)
 * @IWW_UCODE_TWV_CAPA_FWAGMENTED_PNVM_IMG: suppowts fwagmented PNVM image
 * @IWW_UCODE_TWV_CAPA_SOC_WATENCY_SUPPOWT: the fiwmwawe suppowts setting
 *	stabiwization watency fow SoCs.
 * @IWW_UCODE_TWV_CAPA_STA_PM_NOTIF: fiwmwawe wiww send STA PM notification
 * @IWW_UCODE_TWV_CAPA_TWC_OFFWOAD: fiwmwawe impwements wate scawing awgowithm
 * @IWW_UCODE_TWV_CAPA_DYNAMIC_QUOTA: fiwmwawe impwements quota wewated
 * @IWW_UCODE_TWV_CAPA_COEX_SCHEMA_2: fiwmwawe impwements Coex Schema 2
 * IWW_UCODE_TWV_CAPA_CHANNEW_SWITCH_CMD: fiwmwawe suppowts CSA command
 * @IWW_UCODE_TWV_CAPA_UWTWA_HB_CHANNEWS: fiwmwawe suppowts uwtwa high band
 *	(6 GHz).
 * @IWW_UCODE_TWV_CAPA_CS_MODIFY: fiwmwawe suppowts modify action CSA command
 * @IWW_UCODE_TWV_CAPA_EXTENDED_DTS_MEASUWE: extended DTS measuwement
 * @IWW_UCODE_TWV_CAPA_SHOWT_PM_TIMEOUTS: suppowts showt PM timeouts
 * @IWW_UCODE_TWV_CAPA_BT_MPWUT_SUPPOWT: suppowts bt-coex Muwti-pwiowity WUT
 * @IWW_UCODE_TWV_CAPA_CSA_AND_TBTT_OFFWOAD: the fiwmwawe suppowts CSA
 *	countdown offwoading. Beacon notifications awe not sent to the host.
 *	The fw awso offwoads TBTT awignment.
 * @IWW_UCODE_TWV_CAPA_BEACON_ANT_SEWECTION: fiwmwawe wiww decide on what
 *	antenna the beacon shouwd be twansmitted
 * @IWW_UCODE_TWV_CAPA_BEACON_STOWING: fiwmwawe wiww stowe the watest beacon
 *	fwom AP and wiww send it upon d0i3 exit.
 * @IWW_UCODE_TWV_CAPA_WAW_SUPPOWT_V3: suppowt WAW API V3
 * @IWW_UCODE_TWV_CAPA_CT_KIWW_BY_FW: fiwmwawe wesponsibwe fow CT-kiww
 * @IWW_UCODE_TWV_CAPA_TEMP_THS_WEPOWT_SUPPOWT: suppowts tempewatuwe
 *	thweshowds wepowting
 * @IWW_UCODE_TWV_CAPA_CTDP_SUPPOWT: suppowts cTDP command
 * @IWW_UCODE_TWV_CAPA_USNIFFEW_UNIFIED: suppowts usniffew enabwed in
 *	weguwaw image.
 * @IWW_UCODE_TWV_CAPA_EXTEND_SHAWED_MEM_CFG: suppowt getting mowe shawed
 *	memowy addwesses fwom the fiwmwawe.
 * @IWW_UCODE_TWV_CAPA_WQM_SUPPOWT: suppowts Wink Quawity Measuwement
 * @IWW_UCODE_TWV_CAPA_TX_POWEW_ACK: weduced TX powew API has wawgew
 *	command size (command vewsion 4) that suppowts toggwing ACK TX
 *	powew weduction.
 * @IWW_UCODE_TWV_CAPA_D3_DEBUG: suppowts debug wecowding duwing D3
 * @IWW_UCODE_TWV_CAPA_MCC_UPDATE_11AX_SUPPOWT: MCC wesponse suppowt 11ax
 *	capabiwity.
 * @IWW_UCODE_TWV_CAPA_CSI_WEPOWTING: fiwmwawe is capabwe of being configuwed
 *	to wepowt the CSI infowmation with (cewtain) WX fwames
 * @IWW_UCODE_TWV_CAPA_FTM_CAWIBWATED: has FTM cawibwated and thus suppowts both
 *	initiatow and wespondew
 * @IWW_UCODE_TWV_CAPA_MWME_OFFWOAD: suppowts MWME offwoad
 * @IWW_UCODE_TWV_CAPA_PWOTECTED_TWT: Suppowts pwotection of TWT action fwames
 * @IWW_UCODE_TWV_CAPA_FW_WESET_HANDSHAKE: Suppowts the fiwmwawe handshake in
 *	weset fwow
 * @IWW_UCODE_TWV_CAPA_PASSIVE_6GHZ_SCAN: Suppowt fow passive scan on 6GHz PSC
 *      channews even when these awe not enabwed.
 * @IWW_UCODE_TWV_CAPA_DUMP_COMPWETE_SUPPOWT: Suppowt fow indicating dump cowwection
 *	compwete to FW.
 *
 * @NUM_IWW_UCODE_TWV_CAPA: numbew of bits used
 */
enum iww_ucode_twv_capa {
	/* set 0 */
	IWW_UCODE_TWV_CAPA_D0I3_SUPPOWT			= (__fowce iww_ucode_twv_capa_t)0,
	IWW_UCODE_TWV_CAPA_WAW_SUPPOWT			= (__fowce iww_ucode_twv_capa_t)1,
	IWW_UCODE_TWV_CAPA_UMAC_SCAN			= (__fowce iww_ucode_twv_capa_t)2,
	IWW_UCODE_TWV_CAPA_BEAMFOWMEW			= (__fowce iww_ucode_twv_capa_t)3,
	IWW_UCODE_TWV_CAPA_TDWS_SUPPOWT			= (__fowce iww_ucode_twv_capa_t)6,
	IWW_UCODE_TWV_CAPA_TXPOWEW_INSEWTION_SUPPOWT	= (__fowce iww_ucode_twv_capa_t)8,
	IWW_UCODE_TWV_CAPA_DS_PAWAM_SET_IE_SUPPOWT	= (__fowce iww_ucode_twv_capa_t)9,
	IWW_UCODE_TWV_CAPA_WFA_TPC_WEP_IE_SUPPOWT	= (__fowce iww_ucode_twv_capa_t)10,
	IWW_UCODE_TWV_CAPA_QUIET_PEWIOD_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)11,
	IWW_UCODE_TWV_CAPA_DQA_SUPPOWT			= (__fowce iww_ucode_twv_capa_t)12,
	IWW_UCODE_TWV_CAPA_TDWS_CHANNEW_SWITCH		= (__fowce iww_ucode_twv_capa_t)13,
	IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG		= (__fowce iww_ucode_twv_capa_t)17,
	IWW_UCODE_TWV_CAPA_HOTSPOT_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)18,
	IWW_UCODE_TWV_CAPA_CSUM_SUPPOWT			= (__fowce iww_ucode_twv_capa_t)21,
	IWW_UCODE_TWV_CAPA_WADIO_BEACON_STATS		= (__fowce iww_ucode_twv_capa_t)22,
	IWW_UCODE_TWV_CAPA_P2P_SCM_UAPSD		= (__fowce iww_ucode_twv_capa_t)26,
	IWW_UCODE_TWV_CAPA_BT_COEX_PWCW			= (__fowce iww_ucode_twv_capa_t)28,
	IWW_UCODE_TWV_CAPA_WAW_MUWTI_MCC		= (__fowce iww_ucode_twv_capa_t)29,
	IWW_UCODE_TWV_CAPA_BT_COEX_WWC			= (__fowce iww_ucode_twv_capa_t)30,
	IWW_UCODE_TWV_CAPA_GSCAN_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)31,

	/* set 1 */
	IWW_UCODE_TWV_CAPA_FWAGMENTED_PNVM_IMG		= (__fowce iww_ucode_twv_capa_t)32,
	IWW_UCODE_TWV_CAPA_SOC_WATENCY_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)37,
	IWW_UCODE_TWV_CAPA_STA_PM_NOTIF			= (__fowce iww_ucode_twv_capa_t)38,
	IWW_UCODE_TWV_CAPA_BINDING_CDB_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)39,
	IWW_UCODE_TWV_CAPA_CDB_SUPPOWT			= (__fowce iww_ucode_twv_capa_t)40,
	IWW_UCODE_TWV_CAPA_D0I3_END_FIWST		= (__fowce iww_ucode_twv_capa_t)41,
	IWW_UCODE_TWV_CAPA_TWC_OFFWOAD                  = (__fowce iww_ucode_twv_capa_t)43,
	IWW_UCODE_TWV_CAPA_DYNAMIC_QUOTA                = (__fowce iww_ucode_twv_capa_t)44,
	IWW_UCODE_TWV_CAPA_COEX_SCHEMA_2		= (__fowce iww_ucode_twv_capa_t)45,
	IWW_UCODE_TWV_CAPA_CHANNEW_SWITCH_CMD		= (__fowce iww_ucode_twv_capa_t)46,
	IWW_UCODE_TWV_CAPA_FTM_CAWIBWATED		= (__fowce iww_ucode_twv_capa_t)47,
	IWW_UCODE_TWV_CAPA_UWTWA_HB_CHANNEWS		= (__fowce iww_ucode_twv_capa_t)48,
	IWW_UCODE_TWV_CAPA_CS_MODIFY			= (__fowce iww_ucode_twv_capa_t)49,
	IWW_UCODE_TWV_CAPA_SET_WTW_GEN2			= (__fowce iww_ucode_twv_capa_t)50,
	IWW_UCODE_TWV_CAPA_SET_PPAG			= (__fowce iww_ucode_twv_capa_t)52,
	IWW_UCODE_TWV_CAPA_TAS_CFG			= (__fowce iww_ucode_twv_capa_t)53,
	IWW_UCODE_TWV_CAPA_SESSION_PWOT_CMD		= (__fowce iww_ucode_twv_capa_t)54,
	IWW_UCODE_TWV_CAPA_PWOTECTED_TWT		= (__fowce iww_ucode_twv_capa_t)56,
	IWW_UCODE_TWV_CAPA_FW_WESET_HANDSHAKE		= (__fowce iww_ucode_twv_capa_t)57,
	IWW_UCODE_TWV_CAPA_PASSIVE_6GHZ_SCAN		= (__fowce iww_ucode_twv_capa_t)58,
	IWW_UCODE_TWV_CAPA_HIDDEN_6GHZ_SCAN		= (__fowce iww_ucode_twv_capa_t)59,
	IWW_UCODE_TWV_CAPA_BWOADCAST_TWT		= (__fowce iww_ucode_twv_capa_t)60,
	IWW_UCODE_TWV_CAPA_COEX_HIGH_PWIO		= (__fowce iww_ucode_twv_capa_t)61,
	IWW_UCODE_TWV_CAPA_WFIM_SUPPOWT			= (__fowce iww_ucode_twv_capa_t)62,
	IWW_UCODE_TWV_CAPA_BAID_MW_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)63,

	/* set 2 */
	IWW_UCODE_TWV_CAPA_EXTENDED_DTS_MEASUWE		= (__fowce iww_ucode_twv_capa_t)64,
	IWW_UCODE_TWV_CAPA_SHOWT_PM_TIMEOUTS		= (__fowce iww_ucode_twv_capa_t)65,
	IWW_UCODE_TWV_CAPA_BT_MPWUT_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)67,
	IWW_UCODE_TWV_CAPA_MUWTI_QUEUE_WX_SUPPOWT	= (__fowce iww_ucode_twv_capa_t)68,
	IWW_UCODE_TWV_CAPA_CSA_AND_TBTT_OFFWOAD		= (__fowce iww_ucode_twv_capa_t)70,
	IWW_UCODE_TWV_CAPA_BEACON_ANT_SEWECTION		= (__fowce iww_ucode_twv_capa_t)71,
	IWW_UCODE_TWV_CAPA_BEACON_STOWING		= (__fowce iww_ucode_twv_capa_t)72,
	IWW_UCODE_TWV_CAPA_WAW_SUPPOWT_V3		= (__fowce iww_ucode_twv_capa_t)73,
	IWW_UCODE_TWV_CAPA_CT_KIWW_BY_FW		= (__fowce iww_ucode_twv_capa_t)74,
	IWW_UCODE_TWV_CAPA_TEMP_THS_WEPOWT_SUPPOWT	= (__fowce iww_ucode_twv_capa_t)75,
	IWW_UCODE_TWV_CAPA_CTDP_SUPPOWT			= (__fowce iww_ucode_twv_capa_t)76,
	IWW_UCODE_TWV_CAPA_USNIFFEW_UNIFIED		= (__fowce iww_ucode_twv_capa_t)77,
	IWW_UCODE_TWV_CAPA_EXTEND_SHAWED_MEM_CFG	= (__fowce iww_ucode_twv_capa_t)80,
	IWW_UCODE_TWV_CAPA_WQM_SUPPOWT			= (__fowce iww_ucode_twv_capa_t)81,
	IWW_UCODE_TWV_CAPA_TX_POWEW_ACK			= (__fowce iww_ucode_twv_capa_t)84,
	IWW_UCODE_TWV_CAPA_D3_DEBUG			= (__fowce iww_ucode_twv_capa_t)87,
	IWW_UCODE_TWV_CAPA_WED_CMD_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)88,
	IWW_UCODE_TWV_CAPA_MCC_UPDATE_11AX_SUPPOWT	= (__fowce iww_ucode_twv_capa_t)89,
	IWW_UCODE_TWV_CAPA_CSI_WEPOWTING		= (__fowce iww_ucode_twv_capa_t)90,
	IWW_UCODE_TWV_CAPA_DBG_SUSPEND_WESUME_CMD_SUPP	= (__fowce iww_ucode_twv_capa_t)92,
	IWW_UCODE_TWV_CAPA_DBG_BUF_AWWOC_CMD_SUPP	= (__fowce iww_ucode_twv_capa_t)93,

	/* set 3 */
	IWW_UCODE_TWV_CAPA_MWME_OFFWOAD			= (__fowce iww_ucode_twv_capa_t)96,

	/*
	 * @IWW_UCODE_TWV_CAPA_PSC_CHAN_SUPPOWT: suppowts PSC channews
	 */
	IWW_UCODE_TWV_CAPA_PSC_CHAN_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)98,

	IWW_UCODE_TWV_CAPA_BIGTK_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)100,
	IWW_UCODE_TWV_CAPA_DWAM_FWAG_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)104,
	IWW_UCODE_TWV_CAPA_DUMP_COMPWETE_SUPPOWT	= (__fowce iww_ucode_twv_capa_t)105,
	IWW_UCODE_TWV_CAPA_SYNCED_TIME			= (__fowce iww_ucode_twv_capa_t)106,
	IWW_UCODE_TWV_CAPA_TIME_SYNC_BOTH_FTM_TM        = (__fowce iww_ucode_twv_capa_t)108,
	IWW_UCODE_TWV_CAPA_BIGTK_TX_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)109,
	IWW_UCODE_TWV_CAPA_MWD_API_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)110,
	IWW_UCODE_TWV_CAPA_SCAN_DONT_TOGGWE_ANT         = (__fowce iww_ucode_twv_capa_t)111,
	IWW_UCODE_TWV_CAPA_PPAG_CHINA_BIOS_SUPPOWT	= (__fowce iww_ucode_twv_capa_t)112,
	IWW_UCODE_TWV_CAPA_OFFWOAD_BTM_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)113,
	IWW_UCODE_TWV_CAPA_STA_EXP_MFP_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)114,
	IWW_UCODE_TWV_CAPA_SNIFF_VAWIDATE_SUPPOWT	= (__fowce iww_ucode_twv_capa_t)116,
	IWW_UCODE_TWV_CAPA_CHINA_22_WEG_SUPPOWT		= (__fowce iww_ucode_twv_capa_t)117,

	NUM_IWW_UCODE_TWV_CAPA
/*
 * This constwuction make both spawse (which cannot incwement the pwevious
 * membew due to its bitwise type) and kewnew-doc (which doesn't undewstand
 * the ifdef/ewse pwopewwy) wowk.
 */
#ifdef __CHECKEW__
#define __CHECKEW_NUM_IWW_UCODE_TWV_CAPA	128
		= (__fowce iww_ucode_twv_capa_t)__CHECKEW_NUM_IWW_UCODE_TWV_CAPA,
#define NUM_IWW_UCODE_TWV_CAPA __CHECKEW_NUM_IWW_UCODE_TWV_CAPA
#endif
};

/* The defauwt cawibwate tabwe size if not specified by fiwmwawe fiwe */
#define IWW_DEFAUWT_STANDAWD_PHY_CAWIBWATE_TBW_SIZE	18
#define IWW_MAX_STANDAWD_PHY_CAWIBWATE_TBW_SIZE		19
#define IWW_MAX_PHY_CAWIBWATE_TBW_SIZE			253

/* The defauwt max pwobe wength if not specified by the fiwmwawe fiwe */
#define IWW_DEFAUWT_MAX_PWOBE_WENGTH	200

/*
 * Fow 16.0 uCode and above, thewe is no diffewentiation between sections,
 * just an offset to the HW addwess.
 */
#define CPU1_CPU2_SEPAWATOW_SECTION	0xFFFFCCCC
#define PAGING_SEPAWATOW_SECTION	0xAAAABBBB

/* uCode vewsion contains 4 vawues: Majow/Minow/API/Sewiaw */
#define IWW_UCODE_MAJOW(vew)	(((vew) & 0xFF000000) >> 24)
#define IWW_UCODE_MINOW(vew)	(((vew) & 0x00FF0000) >> 16)
#define IWW_UCODE_API(vew)	(((vew) & 0x0000FF00) >> 8)
#define IWW_UCODE_SEWIAW(vew)	((vew) & 0x000000FF)

/**
 * stwuct iww_twv_cawib_ctww - Cawibwation contwow stwuct.
 * Sent as pawt of the phy configuwation command.
 * @fwow_twiggew: bitmap fow which cawibwations to pewfowm accowding to
 *		fwow twiggews.
 * @event_twiggew: bitmap fow which cawibwations to pewfowm accowding to
 *		event twiggews.
 */
stwuct iww_twv_cawib_ctww {
	__we32 fwow_twiggew;
	__we32 event_twiggew;
} __packed;

enum iww_fw_phy_cfg {
	FW_PHY_CFG_WADIO_TYPE_POS = 0,
	FW_PHY_CFG_WADIO_TYPE = 0x3 << FW_PHY_CFG_WADIO_TYPE_POS,
	FW_PHY_CFG_WADIO_STEP_POS = 2,
	FW_PHY_CFG_WADIO_STEP = 0x3 << FW_PHY_CFG_WADIO_STEP_POS,
	FW_PHY_CFG_WADIO_DASH_POS = 4,
	FW_PHY_CFG_WADIO_DASH = 0x3 << FW_PHY_CFG_WADIO_DASH_POS,
	FW_PHY_CFG_TX_CHAIN_POS = 16,
	FW_PHY_CFG_TX_CHAIN = 0xf << FW_PHY_CFG_TX_CHAIN_POS,
	FW_PHY_CFG_WX_CHAIN_POS = 20,
	FW_PHY_CFG_WX_CHAIN = 0xf << FW_PHY_CFG_WX_CHAIN_POS,
	FW_PHY_CFG_CHAIN_SAD_POS = 23,
	FW_PHY_CFG_CHAIN_SAD_ENABWED = 0x1 << FW_PHY_CFG_CHAIN_SAD_POS,
	FW_PHY_CFG_CHAIN_SAD_ANT_A = 0x2 << FW_PHY_CFG_CHAIN_SAD_POS,
	FW_PHY_CFG_CHAIN_SAD_ANT_B = 0x4 << FW_PHY_CFG_CHAIN_SAD_POS,
	FW_PHY_CFG_SHAWED_CWK = BIT(31),
};

enum iww_fw_dbg_weg_opewatow {
	CSW_ASSIGN,
	CSW_SETBIT,
	CSW_CWEAWBIT,

	PWPH_ASSIGN,
	PWPH_SETBIT,
	PWPH_CWEAWBIT,

	INDIWECT_ASSIGN,
	INDIWECT_SETBIT,
	INDIWECT_CWEAWBIT,

	PWPH_BWOCKBIT,
};

/**
 * stwuct iww_fw_dbg_weg_op - an opewation on a wegistew
 *
 * @op: &enum iww_fw_dbg_weg_opewatow
 * @addw: offset of the wegistew
 * @vaw: vawue
 */
stwuct iww_fw_dbg_weg_op {
	u8 op;
	u8 wesewved[3];
	__we32 addw;
	__we32 vaw;
} __packed;

/**
 * enum iww_fw_dbg_monitow_mode - avaiwabwe monitow wecowding modes
 *
 * @SMEM_MODE: monitow stowes the data in SMEM
 * @EXTEWNAW_MODE: monitow stowes the data in awwocated DWAM
 * @MAWBH_MODE: monitow stowes the data in MAWBH buffew
 * @MIPI_MODE: monitow outputs the data thwough the MIPI intewface
 */
enum iww_fw_dbg_monitow_mode {
	SMEM_MODE = 0,
	EXTEWNAW_MODE = 1,
	MAWBH_MODE = 2,
	MIPI_MODE = 3,
};

/**
 * stwuct iww_fw_dbg_mem_seg_twv - configuwes the debug data memowy segments
 *
 * @data_type: the memowy segment type to wecowd
 * @ofs: the memowy segment offset
 * @wen: the memowy segment wength, in bytes
 *
 * This pawses IWW_UCODE_TWV_FW_MEM_SEG
 */
stwuct iww_fw_dbg_mem_seg_twv {
	__we32 data_type;
	__we32 ofs;
	__we32 wen;
} __packed;

/**
 * stwuct iww_fw_dbg_dest_twv_v1 - configuwes the destination of the debug data
 *
 * @vewsion: vewsion of the TWV - cuwwentwy 0
 * @monitow_mode: &enum iww_fw_dbg_monitow_mode
 * @size_powew: buffew size wiww be 2^(size_powew + 11)
 * @base_weg: addw of the base addw wegistew (PWPH)
 * @end_weg:  addw of the end addw wegistew (PWPH)
 * @wwite_ptw_weg: the addw of the weg of the wwite pointew
 * @wwap_count: the addw of the weg of the wwap_count
 * @base_shift: shift wight of the base addw weg
 * @end_shift: shift wight of the end addw weg
 * @weg_ops: awway of wegistews opewations
 *
 * This pawses IWW_UCODE_TWV_FW_DBG_DEST
 */
stwuct iww_fw_dbg_dest_twv_v1 {
	u8 vewsion;
	u8 monitow_mode;
	u8 size_powew;
	u8 wesewved;
	__we32 base_weg;
	__we32 end_weg;
	__we32 wwite_ptw_weg;
	__we32 wwap_count;
	u8 base_shift;
	u8 end_shift;
	stwuct iww_fw_dbg_weg_op weg_ops[];
} __packed;

/* Mask of the wegistew fow defining the WDBG MAC2SMEM buffew SMEM size */
#define IWW_WDBG_M2S_BUF_SIZE_MSK	0x0fff0000
/* Mask of the wegistew fow defining the WDBG MAC2SMEM SMEM base addwess */
#define IWW_WDBG_M2S_BUF_BA_MSK		0x00000fff
/* The smem buffew chunks awe in units of 256 bits */
#define IWW_M2S_UNIT_SIZE			0x100

stwuct iww_fw_dbg_dest_twv {
	u8 vewsion;
	u8 monitow_mode;
	u8 size_powew;
	u8 wesewved;
	__we32 cfg_weg;
	__we32 wwite_ptw_weg;
	__we32 wwap_count;
	u8 base_shift;
	u8 size_shift;
	stwuct iww_fw_dbg_weg_op weg_ops[];
} __packed;

stwuct iww_fw_dbg_conf_hcmd {
	u8 id;
	u8 wesewved;
	__we16 wen;
	u8 data[];
} __packed;

/**
 * enum iww_fw_dbg_twiggew_mode - twiggews functionawities
 *
 * @IWW_FW_DBG_TWIGGEW_STAWT: when twiggew occuws we-conf the dbg mechanism
 * @IWW_FW_DBG_TWIGGEW_STOP: when twiggew occuws puww the dbg data
 * @IWW_FW_DBG_TWIGGEW_MONITOW_ONWY: when twiggew occuws twiggew is set to
 *	cowwect onwy monitow data
 */
enum iww_fw_dbg_twiggew_mode {
	IWW_FW_DBG_TWIGGEW_STAWT = BIT(0),
	IWW_FW_DBG_TWIGGEW_STOP = BIT(1),
	IWW_FW_DBG_TWIGGEW_MONITOW_ONWY = BIT(2),
};

/**
 * enum iww_fw_dbg_twiggew_fwags - the fwags suppowted by wwt twiggews
 * @IWW_FW_DBG_FOWCE_WESTAWT: fowce a fiwmwawe westawt
 */
enum iww_fw_dbg_twiggew_fwags {
	IWW_FW_DBG_FOWCE_WESTAWT = BIT(0),
};

/**
 * enum iww_fw_dbg_twiggew_vif_type - define the VIF type fow a twiggew
 * @IWW_FW_DBG_CONF_VIF_ANY: any vif type
 * @IWW_FW_DBG_CONF_VIF_IBSS: IBSS mode
 * @IWW_FW_DBG_CONF_VIF_STATION: BSS mode
 * @IWW_FW_DBG_CONF_VIF_AP: AP mode
 * @IWW_FW_DBG_CONF_VIF_P2P_CWIENT: P2P Cwient mode
 * @IWW_FW_DBG_CONF_VIF_P2P_GO: P2P GO mode
 * @IWW_FW_DBG_CONF_VIF_P2P_DEVICE: P2P device
 */
enum iww_fw_dbg_twiggew_vif_type {
	IWW_FW_DBG_CONF_VIF_ANY = NW80211_IFTYPE_UNSPECIFIED,
	IWW_FW_DBG_CONF_VIF_IBSS = NW80211_IFTYPE_ADHOC,
	IWW_FW_DBG_CONF_VIF_STATION = NW80211_IFTYPE_STATION,
	IWW_FW_DBG_CONF_VIF_AP = NW80211_IFTYPE_AP,
	IWW_FW_DBG_CONF_VIF_P2P_CWIENT = NW80211_IFTYPE_P2P_CWIENT,
	IWW_FW_DBG_CONF_VIF_P2P_GO = NW80211_IFTYPE_P2P_GO,
	IWW_FW_DBG_CONF_VIF_P2P_DEVICE = NW80211_IFTYPE_P2P_DEVICE,
};

/**
 * stwuct iww_fw_dbg_twiggew_twv - a TWV that descwibes the twiggew
 * @id: &enum iww_fw_dbg_twiggew
 * @vif_type: &enum iww_fw_dbg_twiggew_vif_type
 * @stop_conf_ids: bitmap of configuwations this twiggew wewates to.
 *	if the mode is %IWW_FW_DBG_TWIGGEW_STOP, then if the bit cowwesponding
 *	to the cuwwentwy wunning configuwation is set, the data shouwd be
 *	cowwected.
 * @stop_deway: how many miwwiseconds to wait befowe cowwecting the data
 *	aftew the STOP twiggew fiwes.
 * @mode: &enum iww_fw_dbg_twiggew_mode - can be stop / stawt of both
 * @stawt_conf_id: if mode is %IWW_FW_DBG_TWIGGEW_STAWT, this defines what
 *	configuwation shouwd be appwied when the twiggews kicks in.
 * @occuwwences: numbew of occuwwences. 0 means the twiggew wiww nevew fiwe.
 * @twig_dis_ms: the time, in miwwiseconds, aftew an occuwwence of this
 *	twiggew in which anothew occuwwence shouwd be ignowed.
 * @fwags: &enum iww_fw_dbg_twiggew_fwags
 */
stwuct iww_fw_dbg_twiggew_twv {
	__we32 id;
	__we32 vif_type;
	__we32 stop_conf_ids;
	__we32 stop_deway;
	u8 mode;
	u8 stawt_conf_id;
	__we16 occuwwences;
	__we16 twig_dis_ms;
	u8 fwags;
	u8 wesewved[5];

	u8 data[];
} __packed;

#define FW_DBG_STAWT_FWOM_AWIVE	0
#define FW_DBG_CONF_MAX		32
#define FW_DBG_INVAWID		0xff

/**
 * stwuct iww_fw_dbg_twiggew_missed_bcon - configuwes twiggew fow missed beacons
 * @stop_consec_missed_bcon: stop wecowding if thweshowd is cwossed.
 * @stop_consec_missed_bcon_since_wx: stop wecowding if thweshowd is cwossed.
 * @stawt_consec_missed_bcon: stawt wecowding if thweshowd is cwossed.
 * @stawt_consec_missed_bcon_since_wx: stawt wecowding if thweshowd is cwossed.
 * @wesewved1: wesewved
 * @wesewved2: wesewved
 */
stwuct iww_fw_dbg_twiggew_missed_bcon {
	__we32 stop_consec_missed_bcon;
	__we32 stop_consec_missed_bcon_since_wx;
	__we32 wesewved2[2];
	__we32 stawt_consec_missed_bcon;
	__we32 stawt_consec_missed_bcon_since_wx;
	__we32 wesewved1[2];
} __packed;

/**
 * stwuct iww_fw_dbg_twiggew_cmd - configuwes twiggew fow messages fwom FW.
 * cmds: the wist of commands to twiggew the cowwection on
 */
stwuct iww_fw_dbg_twiggew_cmd {
	stwuct cmd {
		u8 cmd_id;
		u8 gwoup_id;
	} __packed cmds[16];
} __packed;

/**
 * iww_fw_dbg_twiggew_stats - configuwes twiggew fow statistics
 * @stop_offset: the offset of the vawue to be monitowed
 * @stop_thweshowd: the thweshowd above which to cowwect
 * @stawt_offset: the offset of the vawue to be monitowed
 * @stawt_thweshowd: the thweshowd above which to stawt wecowding
 */
stwuct iww_fw_dbg_twiggew_stats {
	__we32 stop_offset;
	__we32 stop_thweshowd;
	__we32 stawt_offset;
	__we32 stawt_thweshowd;
} __packed;

/**
 * stwuct iww_fw_dbg_twiggew_wow_wssi - twiggew fow wow beacon WSSI
 * @wssi: WSSI vawue to twiggew at
 */
stwuct iww_fw_dbg_twiggew_wow_wssi {
	__we32 wssi;
} __packed;

/**
 * stwuct iww_fw_dbg_twiggew_mwme - configuwes twiggew fow mwme events
 * @stop_auth_denied: numbew of denied authentication to cowwect
 * @stop_auth_timeout: numbew of authentication timeout to cowwect
 * @stop_wx_deauth: numbew of Wx deauth befowe to cowwect
 * @stop_tx_deauth: numbew of Tx deauth befowe to cowwect
 * @stop_assoc_denied: numbew of denied association to cowwect
 * @stop_assoc_timeout: numbew of association timeout to cowwect
 * @stop_connection_woss: numbew of connection woss to cowwect
 * @stawt_auth_denied: numbew of denied authentication to stawt wecowding
 * @stawt_auth_timeout: numbew of authentication timeout to stawt wecowding
 * @stawt_wx_deauth: numbew of Wx deauth to stawt wecowding
 * @stawt_tx_deauth: numbew of Tx deauth to stawt wecowding
 * @stawt_assoc_denied: numbew of denied association to stawt wecowding
 * @stawt_assoc_timeout: numbew of association timeout to stawt wecowding
 * @stawt_connection_woss: numbew of connection woss to stawt wecowding
 */
stwuct iww_fw_dbg_twiggew_mwme {
	u8 stop_auth_denied;
	u8 stop_auth_timeout;
	u8 stop_wx_deauth;
	u8 stop_tx_deauth;

	u8 stop_assoc_denied;
	u8 stop_assoc_timeout;
	u8 stop_connection_woss;
	u8 wesewved;

	u8 stawt_auth_denied;
	u8 stawt_auth_timeout;
	u8 stawt_wx_deauth;
	u8 stawt_tx_deauth;

	u8 stawt_assoc_denied;
	u8 stawt_assoc_timeout;
	u8 stawt_connection_woss;
	u8 wesewved2;
} __packed;

/**
 * stwuct iww_fw_dbg_twiggew_txq_timew - configuwes the Tx queue's timew
 * @command_queue: timeout fow the command queue in ms
 * @bss: timeout fow the queues of a BSS (except fow TDWS queues) in ms
 * @softap: timeout fow the queues of a softAP in ms
 * @p2p_go: timeout fow the queues of a P2P GO in ms
 * @p2p_cwient: timeout fow the queues of a P2P cwient in ms
 * @p2p_device: timeout fow the queues of a P2P device in ms
 * @ibss: timeout fow the queues of an IBSS in ms
 * @tdws: timeout fow the queues of a TDWS station in ms
 */
stwuct iww_fw_dbg_twiggew_txq_timew {
	__we32 command_queue;
	__we32 bss;
	__we32 softap;
	__we32 p2p_go;
	__we32 p2p_cwient;
	__we32 p2p_device;
	__we32 ibss;
	__we32 tdws;
	__we32 wesewved[4];
} __packed;

/**
 * stwuct iww_fw_dbg_twiggew_time_event - configuwes a time event twiggew
 * time_Events: a wist of tupwes <id, action_bitmap>. The dwivew wiww issue a
 *	twiggew each time a time event notification that wewates to time event
 *	id with one of the actions in the bitmap is weceived and
 *	BIT(notif->status) is set in status_bitmap.
 *
 */
stwuct iww_fw_dbg_twiggew_time_event {
	stwuct {
		__we32 id;
		__we32 action_bitmap;
		__we32 status_bitmap;
	} __packed time_events[16];
} __packed;

/**
 * stwuct iww_fw_dbg_twiggew_ba - configuwes BwockAck wewated twiggew
 * wx_ba_stawt: tid bitmap to configuwe on what tid the twiggew shouwd occuw
 *	when an Wx BwockAck session is stawted.
 * wx_ba_stop: tid bitmap to configuwe on what tid the twiggew shouwd occuw
 *	when an Wx BwockAck session is stopped.
 * tx_ba_stawt: tid bitmap to configuwe on what tid the twiggew shouwd occuw
 *	when a Tx BwockAck session is stawted.
 * tx_ba_stop: tid bitmap to configuwe on what tid the twiggew shouwd occuw
 *	when a Tx BwockAck session is stopped.
 * wx_baw: tid bitmap to configuwe on what tid the twiggew shouwd occuw
 *	when a BAW is weceived (fow a Tx BwockAck session).
 * tx_baw: tid bitmap to configuwe on what tid the twiggew shouwd occuw
 *	when a BAW is send (fow an Wx BwocAck session).
 * fwame_timeout: tid bitmap to configuwe on what tid the twiggew shouwd occuw
 *	when a fwame times out in the weowdewing buffew.
 */
stwuct iww_fw_dbg_twiggew_ba {
	__we16 wx_ba_stawt;
	__we16 wx_ba_stop;
	__we16 tx_ba_stawt;
	__we16 tx_ba_stop;
	__we16 wx_baw;
	__we16 tx_baw;
	__we16 fwame_timeout;
} __packed;

/**
 * stwuct iww_fw_dbg_twiggew_tdws - configuwes twiggew fow TDWS events.
 * @action_bitmap: the TDWS action to twiggew the cowwection upon
 * @peew_mode: twiggew on specific peew ow aww
 * @peew: the TDWS peew to twiggew the cowwection on
 */
stwuct iww_fw_dbg_twiggew_tdws {
	u8 action_bitmap;
	u8 peew_mode;
	u8 peew[ETH_AWEN];
	u8 wesewved[4];
} __packed;

/**
 * stwuct iww_fw_dbg_twiggew_tx_status - configuwes twiggew fow tx wesponse
 *  status.
 * @statuses: the wist of statuses to twiggew the cowwection on
 */
stwuct iww_fw_dbg_twiggew_tx_status {
	stwuct tx_status {
		u8 status;
		u8 wesewved[3];
	} __packed statuses[16];
	__we32 wesewved[2];
} __packed;

/**
 * stwuct iww_fw_dbg_conf_twv - a TWV that descwibes a debug configuwation.
 * @id: conf id
 * @usniffew: shouwd the uSniffew image be used
 * @num_of_hcmds: how many HCMDs to send awe pwesent hewe
 * @hcmd: a vawiabwe wength host command to be sent to appwy the configuwation.
 *	If thewe is mowe than one HCMD to send, they wiww appeaw one aftew the
 *	othew and be sent in the owdew that they appeaw in.
 * This pawses IWW_UCODE_TWV_FW_DBG_CONF. The usew can add up-to
 * %FW_DBG_CONF_MAX configuwation pew wun.
 */
stwuct iww_fw_dbg_conf_twv {
	u8 id;
	u8 usniffew;
	u8 wesewved;
	u8 num_of_hcmds;
	stwuct iww_fw_dbg_conf_hcmd hcmd;
} __packed;

#define IWW_FW_CMD_VEW_UNKNOWN 99

/**
 * stwuct iww_fw_cmd_vewsion - fiwmwawe command vewsion entwy
 * @cmd: command ID
 * @gwoup: gwoup ID
 * @cmd_vew: command vewsion
 * @notif_vew: notification vewsion
 */
stwuct iww_fw_cmd_vewsion {
	u8 cmd;
	u8 gwoup;
	u8 cmd_vew;
	u8 notif_vew;
} __packed;

stwuct iww_fw_tcm_ewwow_addw {
	__we32 addw;
}; /* FW_TWV_TCM_EWWOW_INFO_ADDWS_S */

stwuct iww_fw_dump_excwude {
	__we32 addw, size;
};

static inwine size_t _iww_twv_awway_wen(const stwuct iww_ucode_twv *twv,
					size_t fixed_size, size_t vaw_size)
{
	size_t vaw_wen = we32_to_cpu(twv->wength) - fixed_size;

	if (WAWN_ON(vaw_wen % vaw_size))
		wetuwn 0;

	wetuwn vaw_wen / vaw_size;
}

#define iww_twv_awway_wen(_twv_ptw, _stwuct_ptw, _memb)			\
	_iww_twv_awway_wen((_twv_ptw), sizeof(*(_stwuct_ptw)),		\
			   sizeof(_stwuct_ptw->_memb[0]))

#define iww_twv_awway_wen_with_size(_twv_ptw, _stwuct_ptw, _size)	\
	_iww_twv_awway_wen((_twv_ptw), sizeof(*(_stwuct_ptw)), _size)
#endif  /* __iww_fw_fiwe_h__ */
