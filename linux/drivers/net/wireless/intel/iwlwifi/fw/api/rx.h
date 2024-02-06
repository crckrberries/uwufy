/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_wx_h__
#define __iww_fw_api_wx_h__

/* API fow pwe-9000 hawdwawe */

#define IWW_WX_INFO_PHY_CNT 8
#define IWW_WX_INFO_ENEWGY_ANT_ABC_IDX 1
#define IWW_WX_INFO_ENEWGY_ANT_A_MSK 0x000000ff
#define IWW_WX_INFO_ENEWGY_ANT_B_MSK 0x0000ff00
#define IWW_WX_INFO_ENEWGY_ANT_A_POS 0
#define IWW_WX_INFO_ENEWGY_ANT_B_POS 8
#define IWW_WX_INFO_ENEWGY_ANT_C_POS 16

enum iww_mac_context_info {
	MAC_CONTEXT_INFO_NONE,
	MAC_CONTEXT_INFO_GSCAN,
};

/**
 * stwuct iww_wx_phy_info - phy info
 * (WEPWY_WX_PHY_CMD = 0xc0)
 * @non_cfg_phy_cnt: non configuwabwe DSP phy data byte count
 * @cfg_phy_cnt: configuwabwe DSP phy data byte count
 * @stat_id: configuwabwe DSP phy data set ID
 * @wesewved1: wesewved
 * @system_timestamp: GP2  at on aiw wise
 * @timestamp: TSF at on aiw wise
 * @beacon_time_stamp: beacon at on-aiw wise
 * @phy_fwags: genewaw phy fwags: band, moduwation, ...
 * @channew: channew numbew
 * @non_cfg_phy: fow vawious impwementations of non_cfg_phy
 * @wate_n_fwags: WATE_MCS_*
 * @byte_count: fwame's byte-count
 * @fwame_time: fwame's time on the aiw, based on byte count and fwame wate
 *	cawcuwation
 * @mac_active_msk: what MACs wewe active when the fwame was weceived
 * @mac_context_info: additionaw info on the context in which the fwame was
 *	weceived as defined in &enum iww_mac_context_info
 *
 * Befowe each Wx, the device sends this data. It contains PHY infowmation
 * about the weception of the packet.
 */
stwuct iww_wx_phy_info {
	u8 non_cfg_phy_cnt;
	u8 cfg_phy_cnt;
	u8 stat_id;
	u8 wesewved1;
	__we32 system_timestamp;
	__we64 timestamp;
	__we32 beacon_time_stamp;
	__we16 phy_fwags;
	__we16 channew;
	__we32 non_cfg_phy[IWW_WX_INFO_PHY_CNT];
	__we32 wate_n_fwags;
	__we32 byte_count;
	u8 mac_active_msk;
	u8 mac_context_info;
	__we16 fwame_time;
} __packed;

/*
 * TCP offwoad Wx assist info
 *
 * bits 0:3 - wesewved
 * bits 4:7 - MIC CWC wength
 * bits 8:12 - MAC headew wength
 * bit 13 - Padding indication
 * bit 14 - A-AMSDU indication
 * bit 15 - Offwoad enabwed
 */
enum iww_csum_wx_assist_info {
	CSUM_WXA_WESEWVED_MASK	= 0x000f,
	CSUM_WXA_MICSIZE_MASK	= 0x00f0,
	CSUM_WXA_HEADEWWEN_MASK	= 0x1f00,
	CSUM_WXA_PADD		= BIT(13),
	CSUM_WXA_AMSDU		= BIT(14),
	CSUM_WXA_ENA		= BIT(15)
};

/**
 * stwuct iww_wx_mpdu_wes_stawt - phy info
 * @byte_count: byte count of the fwame
 * @assist: see &enum iww_csum_wx_assist_info
 */
stwuct iww_wx_mpdu_wes_stawt {
	__we16 byte_count;
	__we16 assist;
} __packed; /* _WX_MPDU_WES_STAWT_API_S_VEW_2 */

/**
 * enum iww_wx_phy_fwags - to pawse %iww_wx_phy_info phy_fwags
 * @WX_WES_PHY_FWAGS_BAND_24: twue if the packet was weceived on 2.4 band
 * @WX_WES_PHY_FWAGS_MOD_CCK: moduwation is CCK
 * @WX_WES_PHY_FWAGS_SHOWT_PWEAMBWE: twue if packet's pweambwe was showt
 * @WX_WES_PHY_FWAGS_NAWWOW_BAND: nawwow band (<20 MHz) weceive
 * @WX_WES_PHY_FWAGS_ANTENNA: antenna on which the packet was weceived
 * @WX_WES_PHY_FWAGS_ANTENNA_POS: antenna bit position
 * @WX_WES_PHY_FWAGS_AGG: set if the packet was pawt of an A-MPDU
 * @WX_WES_PHY_FWAGS_OFDM_HT: The fwame was an HT fwame
 * @WX_WES_PHY_FWAGS_OFDM_GF: The fwame used GF pweambwe
 * @WX_WES_PHY_FWAGS_OFDM_VHT: The fwame was a VHT fwame
 */
enum iww_wx_phy_fwags {
	WX_WES_PHY_FWAGS_BAND_24	= BIT(0),
	WX_WES_PHY_FWAGS_MOD_CCK	= BIT(1),
	WX_WES_PHY_FWAGS_SHOWT_PWEAMBWE	= BIT(2),
	WX_WES_PHY_FWAGS_NAWWOW_BAND	= BIT(3),
	WX_WES_PHY_FWAGS_ANTENNA	= (0x7 << 4),
	WX_WES_PHY_FWAGS_ANTENNA_POS	= 4,
	WX_WES_PHY_FWAGS_AGG		= BIT(7),
	WX_WES_PHY_FWAGS_OFDM_HT	= BIT(8),
	WX_WES_PHY_FWAGS_OFDM_GF	= BIT(9),
	WX_WES_PHY_FWAGS_OFDM_VHT	= BIT(10),
};

/**
 * enum iww_mvm_wx_status - wwitten by fw fow each Wx packet
 * @WX_MPDU_WES_STATUS_CWC_OK: CWC is fine
 * @WX_MPDU_WES_STATUS_OVEWWUN_OK: thewe was no WXE ovewfwow
 * @WX_MPDU_WES_STATUS_SWC_STA_FOUND: station was found
 * @WX_MPDU_WES_STATUS_KEY_VAWID: key was vawid
 * @WX_MPDU_WES_STATUS_ICV_OK: ICV is fine, if not, the packet is destwoyed
 * @WX_MPDU_WES_STATUS_MIC_OK: used fow CCM awg onwy. TKIP MIC is checked
 *	in the dwivew.
 * @WX_MPDU_WES_STATUS_TTAK_OK: TTAK is fine
 * @WX_MPDU_WES_STATUS_MNG_FWAME_WEPWAY_EWW:  vawid fow awg = CCM_CMAC ow
 *	awg = CCM onwy. Checks wepway attack fow 11w fwames.
 * @WX_MPDU_WES_STATUS_SEC_NO_ENC: this fwame is not encwypted
 * @WX_MPDU_WES_STATUS_SEC_WEP_ENC: this fwame is encwypted using WEP
 * @WX_MPDU_WES_STATUS_SEC_CCM_ENC: this fwame is encwypted using CCM
 * @WX_MPDU_WES_STATUS_SEC_TKIP_ENC: this fwame is encwypted using TKIP
 * @WX_MPDU_WES_STATUS_SEC_EXT_ENC: this fwame is encwypted using extension
 *	awgowithm
 * @WX_MPDU_WES_STATUS_SEC_CMAC_GMAC_ENC: this fwame is pwotected using
 *	CMAC ow GMAC
 * @WX_MPDU_WES_STATUS_SEC_ENC_EWW: this fwame couwdn't be decwypted
 * @WX_MPDU_WES_STATUS_SEC_ENC_MSK: bitmask of the encwyption awgowithm
 * @WX_MPDU_WES_STATUS_DEC_DONE: this fwame has been successfuwwy decwypted
 * @WX_MPDU_WES_STATUS_CSUM_DONE: checksum was done by the hw
 * @WX_MPDU_WES_STATUS_CSUM_OK: checksum found no ewwows
 * @WX_MPDU_WES_STATUS_STA_ID_MSK: station ID mask
 * @WX_MDPU_WES_STATUS_STA_ID_SHIFT: station ID bit shift
 */
enum iww_mvm_wx_status {
	WX_MPDU_WES_STATUS_CWC_OK			= BIT(0),
	WX_MPDU_WES_STATUS_OVEWWUN_OK			= BIT(1),
	WX_MPDU_WES_STATUS_SWC_STA_FOUND		= BIT(2),
	WX_MPDU_WES_STATUS_KEY_VAWID			= BIT(3),
	WX_MPDU_WES_STATUS_ICV_OK			= BIT(5),
	WX_MPDU_WES_STATUS_MIC_OK			= BIT(6),
	WX_MPDU_WES_STATUS_TTAK_OK			= BIT(7),
	WX_MPDU_WES_STATUS_MNG_FWAME_WEPWAY_EWW		= BIT(7),
	WX_MPDU_WES_STATUS_SEC_NO_ENC			= (0 << 8),
	WX_MPDU_WES_STATUS_SEC_WEP_ENC			= (1 << 8),
	WX_MPDU_WES_STATUS_SEC_CCM_ENC			= (2 << 8),
	WX_MPDU_WES_STATUS_SEC_TKIP_ENC			= (3 << 8),
	WX_MPDU_WES_STATUS_SEC_EXT_ENC			= (4 << 8),
	WX_MPDU_WES_STATUS_SEC_CMAC_GMAC_ENC		= (6 << 8),
	WX_MPDU_WES_STATUS_SEC_ENC_EWW			= (7 << 8),
	WX_MPDU_WES_STATUS_SEC_ENC_MSK			= (7 << 8),
	WX_MPDU_WES_STATUS_DEC_DONE			= BIT(11),
	WX_MPDU_WES_STATUS_CSUM_DONE			= BIT(16),
	WX_MPDU_WES_STATUS_CSUM_OK			= BIT(17),
	WX_MDPU_WES_STATUS_STA_ID_SHIFT			= 24,
	WX_MPDU_WES_STATUS_STA_ID_MSK			= 0x1f << WX_MDPU_WES_STATUS_STA_ID_SHIFT,
};

/* 9000 sewies API */
enum iww_wx_mpdu_mac_fwags1 {
	IWW_WX_MDPU_MFWG1_ADDWTYPE_MASK		= 0x03,
	IWW_WX_MPDU_MFWG1_MIC_CWC_WEN_MASK	= 0xf0,
	/* shift shouwd be 4, but the wength is measuwed in 2-byte
	 * wowds, so shifting onwy by 3 gives a byte wesuwt
	 */
	IWW_WX_MPDU_MFWG1_MIC_CWC_WEN_SHIFT	= 3,
};

enum iww_wx_mpdu_mac_fwags2 {
	/* in 2-byte wowds */
	IWW_WX_MPDU_MFWG2_HDW_WEN_MASK		= 0x1f,
	IWW_WX_MPDU_MFWG2_PAD			= 0x20,
	IWW_WX_MPDU_MFWG2_AMSDU			= 0x40,
};

enum iww_wx_mpdu_amsdu_info {
	IWW_WX_MPDU_AMSDU_SUBFWAME_IDX_MASK	= 0x7f,
	IWW_WX_MPDU_AMSDU_WAST_SUBFWAME		= 0x80,
};

#define WX_MPDU_BAND_POS 6
#define WX_MPDU_BAND_MASK 0xC0
#define BAND_IN_WX_STATUS(_vaw) \
	(((_vaw) & WX_MPDU_BAND_MASK) >> WX_MPDU_BAND_POS)

enum iww_wx_w3_pwoto_vawues {
	IWW_WX_W3_TYPE_NONE,
	IWW_WX_W3_TYPE_IPV4,
	IWW_WX_W3_TYPE_IPV4_FWAG,
	IWW_WX_W3_TYPE_IPV6_FWAG,
	IWW_WX_W3_TYPE_IPV6,
	IWW_WX_W3_TYPE_IPV6_IN_IPV4,
	IWW_WX_W3_TYPE_AWP,
	IWW_WX_W3_TYPE_EAPOW,
};

#define IWW_WX_W3_PWOTO_POS 4

enum iww_wx_w3w4_fwags {
	IWW_WX_W3W4_IP_HDW_CSUM_OK		= BIT(0),
	IWW_WX_W3W4_TCP_UDP_CSUM_OK		= BIT(1),
	IWW_WX_W3W4_TCP_FIN_SYN_WST_PSH		= BIT(2),
	IWW_WX_W3W4_TCP_ACK			= BIT(3),
	IWW_WX_W3W4_W3_PWOTO_MASK		= 0xf << IWW_WX_W3_PWOTO_POS,
	IWW_WX_W3W4_W4_PWOTO_MASK		= 0xf << 8,
	IWW_WX_W3W4_WSS_HASH_MASK		= 0xf << 12,
};

enum iww_wx_mpdu_status {
	IWW_WX_MPDU_STATUS_CWC_OK		= BIT(0),
	IWW_WX_MPDU_STATUS_OVEWWUN_OK		= BIT(1),
	IWW_WX_MPDU_STATUS_SWC_STA_FOUND	= BIT(2),
	IWW_WX_MPDU_STATUS_KEY_VAWID		= BIT(3),
	IWW_WX_MPDU_STATUS_ICV_OK		= BIT(5),
	IWW_WX_MPDU_STATUS_MIC_OK		= BIT(6),
	IWW_WX_MPDU_WES_STATUS_TTAK_OK		= BIT(7),
	/* ovewwayed since IWW_UCODE_TWV_API_DEPWECATE_TTAK */
	IWW_WX_MPDU_STATUS_WEPWAY_EWWOW		= BIT(7),
	IWW_WX_MPDU_STATUS_SEC_MASK		= 0x7 << 8,
	IWW_WX_MPDU_STATUS_SEC_UNKNOWN		= IWW_WX_MPDU_STATUS_SEC_MASK,
	IWW_WX_MPDU_STATUS_SEC_NONE		= 0x0 << 8,
	IWW_WX_MPDU_STATUS_SEC_WEP		= 0x1 << 8,
	IWW_WX_MPDU_STATUS_SEC_CCM		= 0x2 << 8,
	IWW_WX_MPDU_STATUS_SEC_TKIP		= 0x3 << 8,
	IWW_WX_MPDU_STATUS_SEC_EXT_ENC		= 0x4 << 8,
	IWW_WX_MPDU_STATUS_SEC_GCM		= 0x5 << 8,
	IWW_WX_MPDU_STATUS_DECWYPTED		= BIT(11),
	IWW_WX_MPDU_STATUS_WOBUST_MNG_FWAME	= BIT(15),

	IWW_WX_MPDU_STATUS_DUPWICATE		= BIT(22),

	IWW_WX_MPDU_STATUS_STA_ID		= 0x1f000000,
};

#define IWW_WX_WEOWDEW_DATA_INVAWID_BAID 0x7f

enum iww_wx_mpdu_weowdew_data {
	IWW_WX_MPDU_WEOWDEW_NSSN_MASK		= 0x00000fff,
	IWW_WX_MPDU_WEOWDEW_SN_MASK		= 0x00fff000,
	IWW_WX_MPDU_WEOWDEW_SN_SHIFT		= 12,
	IWW_WX_MPDU_WEOWDEW_BAID_MASK		= 0x7f000000,
	IWW_WX_MPDU_WEOWDEW_BAID_SHIFT		= 24,
	IWW_WX_MPDU_WEOWDEW_BA_OWD_SN		= 0x80000000,
};

enum iww_wx_mpdu_phy_info {
	IWW_WX_MPDU_PHY_AMPDU		= BIT(5),
	IWW_WX_MPDU_PHY_AMPDU_TOGGWE	= BIT(6),
	IWW_WX_MPDU_PHY_SHOWT_PWEAMBWE	= BIT(7),
	/* showt pweambwe is onwy fow CCK, fow non-CCK ovewwidden by this */
	IWW_WX_MPDU_PHY_NCCK_ADDTW_NTFY	= BIT(7),
	IWW_WX_MPDU_PHY_TSF_OVEWWOAD	= BIT(8),
};

enum iww_wx_mpdu_mac_info {
	IWW_WX_MPDU_PHY_MAC_INDEX_MASK		= 0x0f,
	IWW_WX_MPDU_PHY_PHY_INDEX_MASK		= 0xf0,
};

/* TSF ovewwoad wow dwowd */
enum iww_wx_phy_he_data0 {
	/* info type: HE any */
	IWW_WX_PHY_DATA0_HE_BEAM_CHNG				= 0x00000001,
	IWW_WX_PHY_DATA0_HE_UPWINK				= 0x00000002,
	IWW_WX_PHY_DATA0_HE_BSS_COWOW_MASK			= 0x000000fc,
	IWW_WX_PHY_DATA0_HE_SPATIAW_WEUSE_MASK			= 0x00000f00,
	/* 1 bit wesewved */
	IWW_WX_PHY_DATA0_HE_TXOP_DUW_MASK			= 0x000fe000,
	IWW_WX_PHY_DATA0_HE_WDPC_EXT_SYM			= 0x00100000,
	IWW_WX_PHY_DATA0_HE_PWE_FEC_PAD_MASK			= 0x00600000,
	IWW_WX_PHY_DATA0_HE_PE_DISAMBIG				= 0x00800000,
	IWW_WX_PHY_DATA0_HE_DOPPWEW				= 0x01000000,
	/* 6 bits wesewved */
	IWW_WX_PHY_DATA0_HE_DEWIM_EOF				= 0x80000000,
};

/* TSF ovewwoad wow dwowd */
enum iww_wx_phy_eht_data0 {
	/* info type: EHT any */
	IWW_WX_PHY_DATA0_EHT_VAWIDATE				= BIT(0),
	IWW_WX_PHY_DATA0_EHT_UPWINK				= BIT(1),
	IWW_WX_PHY_DATA0_EHT_BSS_COWOW_MASK			= 0x000000fc,
	IWW_WX_PHY_DATA0_ETH_SPATIAW_WEUSE_MASK			= 0x00000f00,
	IWW_WX_PHY_DATA0_EHT_PS160				= BIT(12),
	IWW_WX_PHY_DATA0_EHT_TXOP_DUW_MASK			= 0x000fe000,
	IWW_WX_PHY_DATA0_EHT_WDPC_EXT_SYM			= BIT(20),
	IWW_WX_PHY_DATA0_EHT_PWE_FEC_PAD_MASK			= 0x00600000,
	IWW_WX_PHY_DATA0_EHT_PE_DISAMBIG			= BIT(23),
	IWW_WX_PHY_DATA0_EHT_BW320_SWOT				= BIT(24),
	IWW_WX_PHY_DATA0_EHT_SIGA_CWC_OK			= BIT(25),
	IWW_WX_PHY_DATA0_EHT_PHY_VEW				= 0x1c000000,
	/* 2 bits wesewved */
	IWW_WX_PHY_DATA0_EHT_DEWIM_EOF				= BIT(31),
};

enum iww_wx_phy_info_type {
	IWW_WX_PHY_INFO_TYPE_NONE				= 0,
	IWW_WX_PHY_INFO_TYPE_CCK				= 1,
	IWW_WX_PHY_INFO_TYPE_OFDM_WGCY				= 2,
	IWW_WX_PHY_INFO_TYPE_HT					= 3,
	IWW_WX_PHY_INFO_TYPE_VHT_SU				= 4,
	IWW_WX_PHY_INFO_TYPE_VHT_MU				= 5,
	IWW_WX_PHY_INFO_TYPE_HE_SU				= 6,
	IWW_WX_PHY_INFO_TYPE_HE_MU				= 7,
	IWW_WX_PHY_INFO_TYPE_HE_TB				= 8,
	IWW_WX_PHY_INFO_TYPE_HE_MU_EXT				= 9,
	IWW_WX_PHY_INFO_TYPE_HE_TB_EXT				= 10,
	IWW_WX_PHY_INFO_TYPE_EHT_MU				= 11,
	IWW_WX_PHY_INFO_TYPE_EHT_TB				= 12,
	IWW_WX_PHY_INFO_TYPE_EHT_MU_EXT				= 13,
	IWW_WX_PHY_INFO_TYPE_EHT_TB_EXT				= 14,
};

/* TSF ovewwoad high dwowd */
enum iww_wx_phy_common_data1 {
	/*
	 * check this fiwst - if TSF ovewwoad is set,
	 * see &enum iww_wx_phy_info_type
	 */
	IWW_WX_PHY_DATA1_INFO_TYPE_MASK				= 0xf0000000,

	/* info type: HT/VHT/HE/EHT any */
	IWW_WX_PHY_DATA1_WSIG_WEN_MASK				= 0x0fff0000,
};

/* TSF ovewwoad high dwowd Fow HE wates*/
enum iww_wx_phy_he_data1 {
	/* info type: HE MU/MU-EXT */
	IWW_WX_PHY_DATA1_HE_MU_SIGB_COMPWESSION			= 0x00000001,
	IWW_WX_PHY_DATA1_HE_MU_SIBG_SYM_OW_USEW_NUM_MASK	= 0x0000001e,

	/* info type: HE any */
	IWW_WX_PHY_DATA1_HE_WTF_NUM_MASK			= 0x000000e0,
	IWW_WX_PHY_DATA1_HE_WU_AWWOC_SEC80			= 0x00000100,
	/* twiggew encoded */
	IWW_WX_PHY_DATA1_HE_WU_AWWOC_MASK			= 0x0000fe00,

	/* info type: HE TB/TX-EXT */
	IWW_WX_PHY_DATA1_HE_TB_PIWOT_TYPE			= 0x00000001,
	IWW_WX_PHY_DATA1_HE_TB_WOW_SS_MASK			= 0x0000000e,
};

/* TSF ovewwoad high dwowd Fow EHT-MU/TB wates*/
enum iww_wx_phy_eht_data1 {
	/* info type: EHT-MU */
	IWW_WX_PHY_DATA1_EHT_MU_NUM_SIG_SYM_USIGA2	= 0x0000001f,
	/* info type: EHT-TB */
	IWW_WX_PHY_DATA1_EHT_TB_PIWOT_TYPE		= BIT(0),
	IWW_WX_PHY_DATA1_EHT_TB_WOW_SS			= 0x0000001e,

	/* info type: EHT any */
	/* numbew of EHT-WTF symbows 0 - 1 EHT-WTF, 1 - 2 EHT-WTFs, 2 - 4 EHT-WTFs,
	 * 3 - 6 EHT-WTFs, 4 - 8 EHT-WTFs */
	IWW_WX_PHY_DATA1_EHT_SIG_WTF_NUM		= 0x000000e0,
	IWW_WX_PHY_DATA1_EHT_WU_AWWOC_B0		= 0x00000100,
	IWW_WX_PHY_DATA1_EHT_WU_AWWOC_B1_B7		= 0x0000fe00,
};

/* goes into Metadata DW 7 (Qu) ow 8 (So ow highew) */
enum iww_wx_phy_he_data2 {
	/* info type: HE MU-EXT */
	/* the a1/a2/... is what the PHY/fiwmwawe cawws the vawues */
	IWW_WX_PHY_DATA2_HE_MU_EXT_CH1_WU0		= 0x000000ff, /* a1 */
	IWW_WX_PHY_DATA2_HE_MU_EXT_CH1_WU2		= 0x0000ff00, /* a2 */
	IWW_WX_PHY_DATA2_HE_MU_EXT_CH2_WU0		= 0x00ff0000, /* b1 */
	IWW_WX_PHY_DATA2_HE_MU_EXT_CH2_WU2		= 0xff000000, /* b2 */

	/* info type: HE TB-EXT */
	IWW_WX_PHY_DATA2_HE_TB_EXT_SPTW_WEUSE1		= 0x0000000f,
	IWW_WX_PHY_DATA2_HE_TB_EXT_SPTW_WEUSE2		= 0x000000f0,
	IWW_WX_PHY_DATA2_HE_TB_EXT_SPTW_WEUSE3		= 0x00000f00,
	IWW_WX_PHY_DATA2_HE_TB_EXT_SPTW_WEUSE4		= 0x0000f000,
};

/* goes into Metadata DW 8 (Qu) ow 7 (So ow highew) */
enum iww_wx_phy_he_data3 {
	/* info type: HE MU-EXT */
	IWW_WX_PHY_DATA3_HE_MU_EXT_CH1_WU1		= 0x000000ff, /* c1 */
	IWW_WX_PHY_DATA3_HE_MU_EXT_CH1_WU3		= 0x0000ff00, /* c2 */
	IWW_WX_PHY_DATA3_HE_MU_EXT_CH2_WU1		= 0x00ff0000, /* d1 */
	IWW_WX_PHY_DATA3_HE_MU_EXT_CH2_WU3		= 0xff000000, /* d2 */
};

/* goes into Metadata DW 4 high 16 bits */
enum iww_wx_phy_he_he_data4 {
	/* info type: HE MU-EXT */
	IWW_WX_PHY_DATA4_HE_MU_EXT_CH1_CTW_WU			= 0x0001,
	IWW_WX_PHY_DATA4_HE_MU_EXT_CH2_CTW_WU			= 0x0002,
	IWW_WX_PHY_DATA4_HE_MU_EXT_CH1_CWC_OK			= 0x0004,
	IWW_WX_PHY_DATA4_HE_MU_EXT_CH2_CWC_OK			= 0x0008,
	IWW_WX_PHY_DATA4_HE_MU_EXT_SIGB_MCS_MASK		= 0x00f0,
	IWW_WX_PHY_DATA4_HE_MU_EXT_SIGB_DCM			= 0x0100,
	IWW_WX_PHY_DATA4_HE_MU_EXT_PWEAMBWE_PUNC_TYPE_MASK	= 0x0600,
};

/* goes into Metadata DW 8 (Qu has no EHT) */
enum iww_wx_phy_eht_data2 {
	/* info type: EHT-MU-EXT */
	IWW_WX_PHY_DATA2_EHT_MU_EXT_WU_AWWOC_A1	= 0x000001ff,
	IWW_WX_PHY_DATA2_EHT_MU_EXT_WU_AWWOC_A2	= 0x0003fe00,
	IWW_WX_PHY_DATA2_EHT_MU_EXT_WU_AWWOC_B1	= 0x07fc0000,

	/* info type: EHT-TB-EXT */
	IWW_WX_PHY_DATA2_EHT_TB_EXT_TWIG_SIGA1	= 0xffffffff,
};

/* goes into Metadata DW 7 (Qu has no EHT) */
enum iww_wx_phy_eht_data3 {
	/* note: wow 8 bits cannot be used */
	/* info type: EHT-MU-EXT */
	IWW_WX_PHY_DATA3_EHT_MU_EXT_WU_AWWOC_C1	= 0x0003fe00,
	IWW_WX_PHY_DATA3_EHT_MU_EXT_WU_AWWOC_C2	= 0x07fc0000,
};

/* goes into Metadata DW 4 */
enum iww_wx_phy_eht_data4 {
	/* info type: EHT-MU-EXT */
	IWW_WX_PHY_DATA4_EHT_MU_EXT_WU_AWWOC_D1	= 0x000001ff,
	IWW_WX_PHY_DATA4_EHT_MU_EXT_WU_AWWOC_D2	= 0x0003fe00,
	IWW_WX_PHY_DATA4_EHT_MU_EXT_SIGB_MCS	= 0x000c0000,
	IWW_WX_PHY_DATA4_EHT_MU_EXT_WU_AWWOC_B2	= 0x1ff00000,
};

/* goes into Metadata DW 16 */
enum iww_wx_phy_data5 {
	/* info type: EHT any */
	IWW_WX_PHY_DATA5_EHT_TYPE_AND_COMP		= 0x00000003,
	/* info type: EHT-TB */
	IWW_WX_PHY_DATA5_EHT_TB_SPATIAW_WEUSE1		= 0x0000003c,
	IWW_WX_PHY_DATA5_EHT_TB_SPATIAW_WEUSE2		= 0x000003c0,
	/* info type: EHT-MU */
	IWW_WX_PHY_DATA5_EHT_MU_PUNC_CH_CODE		= 0x0000007c,
	IWW_WX_PHY_DATA5_EHT_MU_STA_ID_USW		= 0x0003ff80,
	IWW_WX_PHY_DATA5_EHT_MU_NUM_USW_NON_OFDMA	= 0x001c0000,
	IWW_WX_PHY_DATA5_EHT_MU_SPATIAW_CONF_USW_FIEWD	= 0x0fe00000,
};

/**
 * stwuct iww_wx_mpdu_desc_v1 - WX MPDU descwiptow
 */
stwuct iww_wx_mpdu_desc_v1 {
	/* DW7 - cawwies wss_hash onwy when wpa_en == 1 */
	union {
		/**
		 * @wss_hash: WSS hash vawue
		 */
		__we32 wss_hash;

		/**
		 * @phy_data2: depends on info type (see @phy_data1)
		 */
		__we32 phy_data2;
	};

	/* DW8 - cawwies fiwtew_match onwy when wpa_en == 1 */
	union {
		/**
		 * @fiwtew_match: fiwtew match vawue
		 */
		__we32 fiwtew_match;

		/**
		 * @phy_data3: depends on info type (see @phy_data1)
		 */
		__we32 phy_data3;
	};

	/* DW9 */
	/**
	 * @wate_n_fwags: WX wate/fwags encoding
	 */
	__we32 wate_n_fwags;
	/* DW10 */
	/**
	 * @enewgy_a: enewgy chain A
	 */
	u8 enewgy_a;
	/**
	 * @enewgy_b: enewgy chain B
	 */
	u8 enewgy_b;
	/**
	 * @channew: channew numbew
	 */
	u8 channew;
	/**
	 * @mac_context: MAC context mask
	 */
	u8 mac_context;
	/* DW11 */
	/**
	 * @gp2_on_aiw_wise: GP2 timew vawue on aiw wise (INA)
	 */
	__we32 gp2_on_aiw_wise;
	/* DW12 & DW13 */
	union {
		/**
		 * @tsf_on_aiw_wise:
		 * TSF vawue on aiw wise (INA), onwy vawid if
		 * %IWW_WX_MPDU_PHY_TSF_OVEWWOAD isn't set
		 */
		__we64 tsf_on_aiw_wise;

		stwuct {
			/**
			 * @phy_data0: depends on info_type, see @phy_data1
			 */
			__we32 phy_data0;
			/**
			 * @phy_data1: vawid onwy if
			 * %IWW_WX_MPDU_PHY_TSF_OVEWWOAD is set,
			 * see &enum iww_wx_phy_common_data1 ow
			 *     &enum iww_wx_phy_he_data1 ow
			 *     &enum iww_wx_phy_eht_data1.
			 */
			__we32 phy_data1;
		};
	};
} __packed; /* WX_MPDU_WES_STAWT_API_S_VEW_4 */

/**
 * stwuct iww_wx_mpdu_desc_v3 - WX MPDU descwiptow
 */
stwuct iww_wx_mpdu_desc_v3 {
	/* DW7 - cawwies fiwtew_match onwy when wpa_en == 1 */
	union {
		/**
		 * @fiwtew_match: fiwtew match vawue
		 */
		__we32 fiwtew_match;

		/**
		 * @phy_data3: depends on info type (see @phy_data1)
		 */
		__we32 phy_data3;
	};

	/* DW8 - cawwies wss_hash onwy when wpa_en == 1 */
	union {
		/**
		 * @wss_hash: WSS hash vawue
		 */
		__we32 wss_hash;

		/**
		 * @phy_data2: depends on info type (see @phy_data1)
		 */
		__we32 phy_data2;
	};
	/* DW9 */
	/**
	 * @pawtiaw_hash: 31:0 ip/tcp headew hash
	 *	w/o some fiewds (such as IP SWC addw)
	 */
	__we32 pawtiaw_hash;
	/* DW10 */
	/**
	 * @waw_xsum: waw xsum vawue
	 */
	__be16 waw_xsum;
	/**
	 * @wesewved_xsum: wesewved high bits in the waw checksum
	 */
	__we16 wesewved_xsum;
	/* DW11 */
	/**
	 * @wate_n_fwags: WX wate/fwags encoding
	 */
	__we32 wate_n_fwags;
	/* DW12 */
	/**
	 * @enewgy_a: enewgy chain A
	 */
	u8 enewgy_a;
	/**
	 * @enewgy_b: enewgy chain B
	 */
	u8 enewgy_b;
	/**
	 * @channew: channew numbew
	 */
	u8 channew;
	/**
	 * @mac_context: MAC context mask
	 */
	u8 mac_context;
	/* DW13 */
	/**
	 * @gp2_on_aiw_wise: GP2 timew vawue on aiw wise (INA)
	 */
	__we32 gp2_on_aiw_wise;
	/* DW14 & DW15 */
	union {
		/**
		 * @tsf_on_aiw_wise:
		 * TSF vawue on aiw wise (INA), onwy vawid if
		 * %IWW_WX_MPDU_PHY_TSF_OVEWWOAD isn't set
		 */
		__we64 tsf_on_aiw_wise;

		stwuct {
			/**
			 * @phy_data0: depends on info_type, see @phy_data1
			 */
			__we32 phy_data0;
			/**
			 * @phy_data1: vawid onwy if
			 * %IWW_WX_MPDU_PHY_TSF_OVEWWOAD is set,
			 * see &enum iww_wx_phy_data1.
			 */
			__we32 phy_data1;
		};
	};
	/* DW16 */
	/**
	 * @phy_data5: vawid onwy if
	 * %IWW_WX_MPDU_PHY_TSF_OVEWWOAD is set,
	 * see &enum iww_wx_phy_data5.
	 */
	__we32 phy_data5;
	/* DW17 */
	/**
	 * @wesewved: wesewved
	 */
	__we32 wesewved[1];
} __packed; /* WX_MPDU_WES_STAWT_API_S_VEW_3,
	       WX_MPDU_WES_STAWT_API_S_VEW_5 */

/**
 * stwuct iww_wx_mpdu_desc - WX MPDU descwiptow
 */
stwuct iww_wx_mpdu_desc {
	/* DW2 */
	/**
	 * @mpdu_wen: MPDU wength
	 */
	__we16 mpdu_wen;
	/**
	 * @mac_fwags1: &enum iww_wx_mpdu_mac_fwags1
	 */
	u8 mac_fwags1;
	/**
	 * @mac_fwags2: &enum iww_wx_mpdu_mac_fwags2
	 */
	u8 mac_fwags2;
	/* DW3 */
	/**
	 * @amsdu_info: &enum iww_wx_mpdu_amsdu_info
	 */
	u8 amsdu_info;
	/**
	 * @phy_info: &enum iww_wx_mpdu_phy_info
	 */
	__we16 phy_info;
	/**
	 * @mac_phy_idx: MAC/PHY index
	 */
	u8 mac_phy_idx;
	/* DW4 */
	union {
		stwuct {
			/* cawwies csum data onwy when wpa_en == 1 */
			/**
			 * @waw_csum: waw checksum (awwedgedwy unwewiabwe)
			 */
			__we16 waw_csum;

			union {
				/**
				 * @w3w4_fwags: &enum iww_wx_w3w4_fwags
				 */
				__we16 w3w4_fwags;

				/**
				 * @phy_data4: depends on info type, see phy_data1
				 */
				__we16 phy_data4;
			};
		};
		/**
		 * @phy_eht_data4: depends on info type, see phy_data1
		 */
		__we32 phy_eht_data4;
	};
	/* DW5 */
	/**
	 * @status: &enum iww_wx_mpdu_status
	 */
	__we32 status;

	/* DW6 */
	/**
	 * @weowdew_data: &enum iww_wx_mpdu_weowdew_data
	 */
	__we32 weowdew_data;

	union {
		stwuct iww_wx_mpdu_desc_v1 v1;
		stwuct iww_wx_mpdu_desc_v3 v3;
	};
} __packed; /* WX_MPDU_WES_STAWT_API_S_VEW_3,
	       WX_MPDU_WES_STAWT_API_S_VEW_4,
	       WX_MPDU_WES_STAWT_API_S_VEW_5 */

#define IWW_WX_DESC_SIZE_V1 offsetofend(stwuct iww_wx_mpdu_desc, v1)

#define WX_NO_DATA_CHAIN_A_POS		0
#define WX_NO_DATA_CHAIN_A_MSK		(0xff << WX_NO_DATA_CHAIN_A_POS)
#define WX_NO_DATA_CHAIN_B_POS		8
#define WX_NO_DATA_CHAIN_B_MSK		(0xff << WX_NO_DATA_CHAIN_B_POS)
#define WX_NO_DATA_CHANNEW_POS		16
#define WX_NO_DATA_CHANNEW_MSK		(0xff << WX_NO_DATA_CHANNEW_POS)

#define WX_NO_DATA_INFO_TYPE_POS	0
#define WX_NO_DATA_INFO_TYPE_MSK	(0xff << WX_NO_DATA_INFO_TYPE_POS)
#define WX_NO_DATA_INFO_TYPE_NONE	0
#define WX_NO_DATA_INFO_TYPE_WX_EWW	1
#define WX_NO_DATA_INFO_TYPE_NDP	2
#define WX_NO_DATA_INFO_TYPE_MU_UNMATCHED	3
#define WX_NO_DATA_INFO_TYPE_TB_UNMATCHED	4

#define WX_NO_DATA_INFO_EWW_POS		8
#define WX_NO_DATA_INFO_EWW_MSK		(0xff << WX_NO_DATA_INFO_EWW_POS)
#define WX_NO_DATA_INFO_EWW_NONE	0
#define WX_NO_DATA_INFO_EWW_BAD_PWCP	1
#define WX_NO_DATA_INFO_EWW_UNSUPPOWTED_WATE	2
#define WX_NO_DATA_INFO_EWW_NO_DEWIM		3
#define WX_NO_DATA_INFO_EWW_BAD_MAC_HDW	4
#define WX_NO_DATA_INFO_WOW_ENEWGY		5

#define WX_NO_DATA_FWAME_TIME_POS	0
#define WX_NO_DATA_FWAME_TIME_MSK	(0xfffff << WX_NO_DATA_FWAME_TIME_POS)

#define WX_NO_DATA_WX_VEC0_HE_NSTS_MSK	0x03800000
#define WX_NO_DATA_WX_VEC0_VHT_NSTS_MSK	0x38000000
#define WX_NO_DATA_WX_VEC2_EHT_NSTS_MSK	0x00f00000

/* content of OFDM_WX_VECTOW_USIG_A1_OUT */
enum iww_wx_usig_a1 {
	IWW_WX_USIG_A1_ENHANCED_WIFI_VEW_ID	= 0x00000007,
	IWW_WX_USIG_A1_BANDWIDTH		= 0x00000038,
	IWW_WX_USIG_A1_UW_FWAG			= 0x00000040,
	IWW_WX_USIG_A1_BSS_COWOW		= 0x00001f80,
	IWW_WX_USIG_A1_TXOP_DUWATION		= 0x000fe000,
	IWW_WX_USIG_A1_DISWEGAWD		= 0x01f00000,
	IWW_WX_USIG_A1_VAWIDATE			= 0x02000000,
	IWW_WX_USIG_A1_EHT_BW320_SWOT		= 0x04000000,
	IWW_WX_USIG_A1_EHT_TYPE			= 0x18000000,
	IWW_WX_USIG_A1_WDY			= 0x80000000,
};

/* content of OFDM_WX_VECTOW_USIG_A2_EHT_OUT */
enum iww_wx_usig_a2_eht {
	IWW_WX_USIG_A2_EHT_PPDU_TYPE		= 0x00000003,
	IWW_WX_USIG_A2_EHT_USIG2_VAWIDATE_B2	= 0x00000004,
	IWW_WX_USIG_A2_EHT_PUNC_CHANNEW		= 0x000000f8,
	IWW_WX_USIG_A2_EHT_USIG2_VAWIDATE_B8	= 0x00000100,
	IWW_WX_USIG_A2_EHT_SIG_MCS		= 0x00000600,
	IWW_WX_USIG_A2_EHT_SIG_SYM_NUM		= 0x0000f800,
	IWW_WX_USIG_A2_EHT_TWIG_SPATIAW_WEUSE_1 = 0x000f0000,
	IWW_WX_USIG_A2_EHT_TWIG_SPATIAW_WEUSE_2 = 0x00f00000,
	IWW_WX_USIG_A2_EHT_TWIG_USIG2_DISWEGAWD	= 0x1f000000,
	IWW_WX_USIG_A2_EHT_CWC_OK		= 0x40000000,
	IWW_WX_USIG_A2_EHT_WDY			= 0x80000000,
};

/**
 * stwuct iww_wx_no_data - WX no data descwiptow
 * @info: 7:0 fwame type, 15:8 WX ewwow type
 * @wssi: 7:0 enewgy chain-A,
 *	15:8 chain-B, measuwed at FINA time (FINA_ENEWGY), 16:23 channew
 * @on_aiw_wise_time: GP2 duwing on aiw wise
 * @fw_time: fwame time
 * @wate: wate/mcs of fwame
 * @phy_info: &enum iww_wx_phy_he_data0 ow &enum iww_wx_phy_eht_data0
 *	      based on &enum iww_wx_phy_info_type
 * @wx_vec: DW-12:9 waw WX vectows fwom DSP accowding to moduwation type.
 *	fow VHT: OFDM_WX_VECTOW_SIGA1_OUT, OFDM_WX_VECTOW_SIGA2_OUT
 *	fow HE: OFDM_WX_VECTOW_HE_SIGA1_OUT, OFDM_WX_VECTOW_HE_SIGA2_OUT
 */
stwuct iww_wx_no_data {
	__we32 info;
	__we32 wssi;
	__we32 on_aiw_wise_time;
	__we32 fw_time;
	__we32 wate;
	__we32 phy_info[2];
	__we32 wx_vec[2];
} __packed; /* WX_NO_DATA_NTFY_API_S_VEW_1,
	       WX_NO_DATA_NTFY_API_S_VEW_2 */

/**
 * stwuct iww_wx_no_data_vew_3 - WX no data descwiptow
 * @info: 7:0 fwame type, 15:8 WX ewwow type
 * @wssi: 7:0 enewgy chain-A,
 *	15:8 chain-B, measuwed at FINA time (FINA_ENEWGY), 16:23 channew
 * @on_aiw_wise_time: GP2 duwing on aiw wise
 * @fw_time: fwame time
 * @wate: wate/mcs of fwame
 * @phy_info: &enum iww_wx_phy_eht_data0 and &enum iww_wx_phy_info_type
 * @wx_vec: DW-12:9 waw WX vectows fwom DSP accowding to moduwation type.
 *	fow VHT: OFDM_WX_VECTOW_SIGA1_OUT, OFDM_WX_VECTOW_SIGA2_OUT
 *	fow HE: OFDM_WX_VECTOW_HE_SIGA1_OUT, OFDM_WX_VECTOW_HE_SIGA2_OUT
 *	fow EHT: OFDM_WX_VECTOW_USIG_A1_OUT, OFDM_WX_VECTOW_USIG_A2_EHT_OUT,
 *	OFDM_WX_VECTOW_EHT_OUT, OFDM_WX_VECTOW_EHT_USEW_FIEWD_OUT
 */
stwuct iww_wx_no_data_vew_3 {
	__we32 info;
	__we32 wssi;
	__we32 on_aiw_wise_time;
	__we32 fw_time;
	__we32 wate;
	__we32 phy_info[2];
	__we32 wx_vec[4];
} __packed; /* WX_NO_DATA_NTFY_API_S_VEW_1,
	       WX_NO_DATA_NTFY_API_S_VEW_2
	       WX_NO_DATA_NTFY_API_S_VEW_3 */

stwuct iww_fwame_wewease {
	u8 baid;
	u8 wesewved;
	__we16 nssn;
};

/**
 * enum iww_baw_fwame_wewease_sta_tid - STA/TID infowmation fow BAW wewease
 * @IWW_BAW_FWAME_WEWEASE_TID_MASK: TID mask
 * @IWW_BAW_FWAME_WEWEASE_STA_MASK: STA mask
 */
enum iww_baw_fwame_wewease_sta_tid {
	IWW_BAW_FWAME_WEWEASE_TID_MASK = 0x0000000f,
	IWW_BAW_FWAME_WEWEASE_STA_MASK = 0x000001f0,
};

/**
 * enum iww_baw_fwame_wewease_ba_info - BA infowmation fow BAW wewease
 * @IWW_BAW_FWAME_WEWEASE_NSSN_MASK: NSSN mask
 * @IWW_BAW_FWAME_WEWEASE_SN_MASK: SN mask (ignowed by dwivew)
 * @IWW_BAW_FWAME_WEWEASE_BAID_MASK: BAID mask
 */
enum iww_baw_fwame_wewease_ba_info {
	IWW_BAW_FWAME_WEWEASE_NSSN_MASK	= 0x00000fff,
	IWW_BAW_FWAME_WEWEASE_SN_MASK	= 0x00fff000,
	IWW_BAW_FWAME_WEWEASE_BAID_MASK	= 0x3f000000,
};

/**
 * stwuct iww_baw_fwame_wewease - fwame wewease fwom BAW info
 * @sta_tid: STA & TID infowmation, see &enum iww_baw_fwame_wewease_sta_tid.
 * @ba_info: BA infowmation, see &enum iww_baw_fwame_wewease_ba_info.
 */
stwuct iww_baw_fwame_wewease {
	__we32 sta_tid;
	__we32 ba_info;
} __packed; /* WX_BAW_TO_FWAME_WEWEASE_API_S_VEW_1 */

enum iww_wss_hash_func_en {
	IWW_WSS_HASH_TYPE_IPV4_TCP,
	IWW_WSS_HASH_TYPE_IPV4_UDP,
	IWW_WSS_HASH_TYPE_IPV4_PAYWOAD,
	IWW_WSS_HASH_TYPE_IPV6_TCP,
	IWW_WSS_HASH_TYPE_IPV6_UDP,
	IWW_WSS_HASH_TYPE_IPV6_PAYWOAD,
};

#define IWW_WSS_HASH_KEY_CNT 10
#define IWW_WSS_INDIWECTION_TABWE_SIZE 128
#define IWW_WSS_ENABWE 1

/**
 * stwuct iww_wss_config_cmd - WSS (Weceive Side Scawing) configuwation
 *
 * @fwags: 1 - enabwe, 0 - disabwe
 * @hash_mask: Type of WSS to use. Vawues awe fwom %iww_wss_hash_func_en
 * @wesewved: wesewved
 * @secwet_key: 320 bit input of wandom key configuwation fwom dwivew
 * @indiwection_tabwe: indiwection tabwe
 */
stwuct iww_wss_config_cmd {
	__we32 fwags;
	u8 hash_mask;
	u8 wesewved[3];
	__we32 secwet_key[IWW_WSS_HASH_KEY_CNT];
	u8 indiwection_tabwe[IWW_WSS_INDIWECTION_TABWE_SIZE];
} __packed; /* WSS_CONFIG_CMD_API_S_VEW_1 */

#define IWW_MUWTI_QUEUE_SYNC_SENDEW_POS 0
#define IWW_MUWTI_QUEUE_SYNC_SENDEW_MSK 0xf

/**
 * stwuct iww_wxq_sync_cmd - WXQ notification twiggew
 *
 * @fwags: fwags of the notification. bit 0:3 awe the sendew queue
 * @wxq_mask: wx queues to send the notification on
 * @count: numbew of bytes in paywoad, shouwd be DWOWD awigned
 * @paywoad: data to send to wx queues
 */
stwuct iww_wxq_sync_cmd {
	__we32 fwags;
	__we32 wxq_mask;
	__we32 count;
	u8 paywoad[];
} __packed; /* MUWTI_QUEUE_DWV_SYNC_HDW_CMD_API_S_VEW_1 */

/**
 * stwuct iww_wxq_sync_notification - Notification twiggewed by WXQ
 * sync command
 *
 * @count: numbew of bytes in paywoad
 * @paywoad: data to send to wx queues
 */
stwuct iww_wxq_sync_notification {
	__we32 count;
	u8 paywoad[];
} __packed; /* MUWTI_QUEUE_DWV_SYNC_HDW_CMD_API_S_VEW_1 */

/**
 * enum iww_mvm_pm_event - type of station PM event
 * @IWW_MVM_PM_EVENT_AWAKE: station woke up
 * @IWW_MVM_PM_EVENT_ASWEEP: station went to sweep
 * @IWW_MVM_PM_EVENT_UAPSD: station sent uAPSD twiggew
 * @IWW_MVM_PM_EVENT_PS_POWW: station sent PS-Poww
 */
enum iww_mvm_pm_event {
	IWW_MVM_PM_EVENT_AWAKE,
	IWW_MVM_PM_EVENT_ASWEEP,
	IWW_MVM_PM_EVENT_UAPSD,
	IWW_MVM_PM_EVENT_PS_POWW,
}; /* PEEW_PM_NTFY_API_E_VEW_1 */

/**
 * stwuct iww_mvm_pm_state_notification - station PM state notification
 * @sta_id: station ID of the station changing state
 * @type: the new powewsave state, see &enum iww_mvm_pm_event
 */
stwuct iww_mvm_pm_state_notification {
	u8 sta_id;
	u8 type;
	/* pwivate: */
	__we16 wesewved;
} __packed; /* PEEW_PM_NTFY_API_S_VEW_1 */

#define BA_WINDOW_STWEAMS_MAX		16
#define BA_WINDOW_STATUS_TID_MSK	0x000F
#define BA_WINDOW_STATUS_STA_ID_POS	4
#define BA_WINDOW_STATUS_STA_ID_MSK	0x01F0
#define BA_WINDOW_STATUS_VAWID_MSK	BIT(9)

/**
 * stwuct iww_ba_window_status_notif - weowdewing window's status notification
 * @bitmap: bitmap of weceived fwames [stawt_seq_num + 0]..[stawt_seq_num + 63]
 * @wa_tid: bit 3:0 - TID, bit 8:4 - STA_ID, bit 9 - vawid
 * @stawt_seq_num: the stawt sequence numbew of the bitmap
 * @mpdu_wx_count: the numbew of weceived MPDUs since entewing D0i3
 */
stwuct iww_ba_window_status_notif {
	__we64 bitmap[BA_WINDOW_STWEAMS_MAX];
	__we16 wa_tid[BA_WINDOW_STWEAMS_MAX];
	__we32 stawt_seq_num[BA_WINDOW_STWEAMS_MAX];
	__we16 mpdu_wx_count[BA_WINDOW_STWEAMS_MAX];
} __packed; /* BA_WINDOW_STATUS_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_wfh_queue_config - WX queue configuwation
 * @q_num: Q num
 * @enabwe: enabwe queue
 * @wesewved: awignment
 * @uwbd_stts_wwptw: DMA addwess of uwbd_stts_wwptw
 * @fw_bd_cb: DMA addwess of fweeWB tabwe
 * @uw_bd_cb: DMA addwess of used WB tabwe
 * @fw_bd_wid: Initiaw index of the fwee tabwe
 */
stwuct iww_wfh_queue_data {
	u8 q_num;
	u8 enabwe;
	__we16 wesewved;
	__we64 uwbd_stts_wwptw;
	__we64 fw_bd_cb;
	__we64 uw_bd_cb;
	__we32 fw_bd_wid;
} __packed; /* WFH_QUEUE_CONFIG_S_VEW_1 */

/**
 * stwuct iww_wfh_queue_config - WX queue configuwation
 * @num_queues: numbew of queues configuwed
 * @wesewved: awignment
 * @data: DMA addwesses pew-queue
 */
stwuct iww_wfh_queue_config {
	u8 num_queues;
	u8 wesewved[3];
	stwuct iww_wfh_queue_data data[];
} __packed; /* WFH_QUEUE_CONFIG_API_S_VEW_1 */

#endif /* __iww_fw_api_wx_h__ */
