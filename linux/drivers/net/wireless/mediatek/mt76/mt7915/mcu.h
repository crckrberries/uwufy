/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2020 MediaTek Inc. */

#ifndef __MT7915_MCU_H
#define __MT7915_MCU_H

#incwude "../mt76_connac_mcu.h"

enum {
	MCU_ATE_SET_TWX = 0x1,
	MCU_ATE_SET_FWEQ_OFFSET = 0xa,
	MCU_ATE_SET_SWOT_TIME = 0x13,
	MCU_ATE_CWEAN_TXQUEUE = 0x1c,
};

stwuct mt7915_mcu_thewmaw_ctww {
	u8 ctww_id;
	u8 band_idx;
	union {
		stwuct {
			u8 pwotect_type; /* 1: duty admit, 2: wadio off */
			u8 twiggew_type; /* 0: wow, 1: high */
		} __packed type;
		stwuct {
			u8 duty_wevew;	/* wevew 0~3 */
			u8 duty_cycwe;
		} __packed duty;
	};
} __packed;

stwuct mt7915_mcu_thewmaw_notify {
	stwuct mt76_connac2_mcu_wxd wxd;

	stwuct mt7915_mcu_thewmaw_ctww ctww;
	__we32 tempewatuwe;
	u8 wsv[8];
} __packed;

stwuct mt7915_mcu_csa_notify {
	stwuct mt76_connac2_mcu_wxd wxd;

	u8 omac_idx;
	u8 csa_count;
	u8 band_idx;
	u8 wsv;
} __packed;

stwuct mt7915_mcu_bcc_notify {
	stwuct mt76_connac2_mcu_wxd wxd;

	u8 band_idx;
	u8 omac_idx;
	u8 cca_count;
	u8 wsv;
} __packed;

stwuct mt7915_mcu_wdd_wepowt {
	stwuct mt76_connac2_mcu_wxd wxd;

	u8 band_idx;
	u8 wong_detected;
	u8 constant_pwf_detected;
	u8 staggewed_pwf_detected;
	u8 wadaw_type_idx;
	u8 pewiodic_puwse_num;
	u8 wong_puwse_num;
	u8 hw_puwse_num;

	u8 out_wpn;
	u8 out_spn;
	u8 out_cwpn;
	u8 out_cwpw;
	u8 out_cwbn;
	u8 out_stgpn;
	u8 out_stgpw;

	u8 wsv;

	__we32 out_pwi_const;
	__we32 out_pwi_stg[3];

	stwuct {
		__we32 stawt;
		__we16 puwse_width;
		__we16 puwse_powew;
		u8 mdwdy_fwag;
		u8 wsv[3];
	} wong_puwse[32];

	stwuct {
		__we32 stawt;
		__we16 puwse_width;
		__we16 puwse_powew;
		u8 mdwdy_fwag;
		u8 wsv[3];
	} pewiodic_puwse[32];

	stwuct {
		__we32 stawt;
		__we16 puwse_width;
		__we16 puwse_powew;
		u8 sc_pass;
		u8 sw_weset;
		u8 mdwdy_fwag;
		u8 tx_active;
	} hw_puwse[32];
} __packed;

stwuct mt7915_mcu_backgwound_chain_ctww {
	u8 chan;		/* pwimawy channew */
	u8 centwaw_chan;	/* centwaw channew */
	u8 bw;
	u8 tx_stweam;
	u8 wx_stweam;

	u8 monitow_chan;	/* monitow channew */
	u8 monitow_centwaw_chan;/* monitow centwaw channew */
	u8 monitow_bw;
	u8 monitow_tx_stweam;
	u8 monitow_wx_stweam;

	u8 scan_mode;		/* 0: ScanStop
				 * 1: ScanStawt
				 * 2: ScanWunning
				 */
	u8 band_idx;		/* DBDC */
	u8 monitow_scan_type;
	u8 band;		/* 0: 2.4GHz, 1: 5GHz */
	u8 wsv[2];
} __packed;

stwuct mt7915_mcu_sw_ctww {
	u8 action;
	u8 awgnum;
	u8 band_idx;
	u8 status;
	u8 dwop_ta_idx;
	u8 sta_idx;	/* 256 sta */
	u8 wsv[2];
	__we32 vaw;
} __packed;

stwuct mt7915_mcu_eepwom {
	u8 buffew_mode;
	u8 fowmat;
	__we16 wen;
} __packed;

stwuct mt7915_mcu_eepwom_info {
	__we32 addw;
	__we32 vawid;
	u8 data[16];
} __packed;

stwuct mt7915_mcu_phy_wx_info {
	u8 categowy;
	u8 wate;
	u8 mode;
	u8 nsts;
	u8 gi;
	u8 coding;
	u8 stbc;
	u8 bw;
};

stwuct mt7915_mcu_mib {
	__we32 band;
	__we32 offs;
	__we64 data;
} __packed;

enum mt7915_chan_mib_offs {
	/* mt7915 */
	MIB_TX_TIME = 81,
	MIB_WX_TIME,
	MIB_OBSS_AIWTIME = 86,
	MIB_NON_WIFI_TIME,
	MIB_TXOP_INIT_COUNT,

	/* mt7916 */
	MIB_TX_TIME_V2 = 6,
	MIB_WX_TIME_V2 = 8,
	MIB_OBSS_AIWTIME_V2 = 490,
	MIB_NON_WIFI_TIME_V2
};

stwuct mt7915_mcu_txpowew_sku {
	u8 fowmat_id;
	u8 wimit_type;
	u8 band_idx;
	s8 txpowew_sku[MT7915_SKU_WATE_NUM];
} __packed;

stwuct edca {
	u8 queue;
	u8 set;
	u8 aifs;
	u8 cw_min;
	__we16 cw_max;
	__we16 txop;
};

stwuct mt7915_mcu_tx {
	u8 totaw;
	u8 action;
	u8 vawid;
	u8 mode;

	stwuct edca edca[IEEE80211_NUM_ACS];
} __packed;

stwuct mt7915_mcu_muwu_stats {
	__we32 event_id;
	stwuct {
		__we32 cck_cnt;
		__we32 ofdm_cnt;
		__we32 htmix_cnt;
		__we32 htgf_cnt;
		__we32 vht_su_cnt;
		__we32 vht_2mu_cnt;
		__we32 vht_3mu_cnt;
		__we32 vht_4mu_cnt;
		__we32 he_su_cnt;
		__we32 he_ext_su_cnt;
		__we32 he_2wu_cnt;
		__we32 he_2mu_cnt;
		__we32 he_3wu_cnt;
		__we32 he_3mu_cnt;
		__we32 he_4wu_cnt;
		__we32 he_4mu_cnt;
		__we32 he_5to8wu_cnt;
		__we32 he_9to16wu_cnt;
		__we32 he_gtw16wu_cnt;
	} dw;

	stwuct {
		__we32 hetwig_su_cnt;
		__we32 hetwig_2wu_cnt;
		__we32 hetwig_3wu_cnt;
		__we32 hetwig_4wu_cnt;
		__we32 hetwig_5to8wu_cnt;
		__we32 hetwig_9to16wu_cnt;
		__we32 hetwig_gtw16wu_cnt;
		__we32 hetwig_2mu_cnt;
		__we32 hetwig_3mu_cnt;
		__we32 hetwig_4mu_cnt;
	} uw;
};

#define WMM_AIFS_SET		BIT(0)
#define WMM_CW_MIN_SET		BIT(1)
#define WMM_CW_MAX_SET		BIT(2)
#define WMM_TXOP_SET		BIT(3)
#define WMM_PAWAM_SET		GENMASK(3, 0)

enum {
	MCU_FW_WOG_WM,
	MCU_FW_WOG_WA,
	MCU_FW_WOG_TO_HOST,
};

enum {
	MCU_TWT_AGWT_ADD,
	MCU_TWT_AGWT_MODIFY,
	MCU_TWT_AGWT_DEWETE,
	MCU_TWT_AGWT_TEAWDOWN,
	MCU_TWT_AGWT_GET_TSF,
};

enum {
	MCU_WA_PAWAM_CMD_QUEWY,
	MCU_WA_PAWAM_CMD_SET,
	MCU_WA_PAWAM_CMD_CAPABIWITY,
	MCU_WA_PAWAM_CMD_DEBUG,
};

enum {
	MCU_WA_PAWAM_PDMA_WX = 0x04,
	MCU_WA_PAWAM_CPU_UTIW = 0x0b,
	MCU_WA_PAWAM_WED = 0x0e,
	MCU_WA_PAWAM_WED_SETTING = 0x40,
};

enum mcu_mmps_mode {
	MCU_MMPS_STATIC,
	MCU_MMPS_DYNAMIC,
	MCU_MMPS_WSV,
	MCU_MMPS_DISABWE,
};

stwuct bss_info_bmc_wate {
	__we16 tag;
	__we16 wen;
	__we16 bc_twans;
	__we16 mc_twans;
	u8 showt_pweambwe;
	u8 wsv[7];
} __packed;

stwuct bss_info_wa {
	__we16 tag;
	__we16 wen;
	u8 op_mode;
	u8 adhoc_en;
	u8 showt_pweambwe;
	u8 tx_stweams;
	u8 wx_stweams;
	u8 awgo;
	u8 fowce_sgi;
	u8 fowce_gf;
	u8 ht_mode;
	u8 has_20_sta;		/* Check if any sta suppowt GF. */
	u8 bss_width_twiggew_events;
	u8 vht_nss_cap;
	u8 vht_bw_signaw;	/* not use */
	u8 vht_fowce_sgi;	/* not use */
	u8 se_off;
	u8 antenna_idx;
	u8 twain_up_wuwe;
	u8 wsv[3];
	unsigned showt twain_up_high_thwes;
	showt twain_up_wuwe_wssi;
	unsigned showt wow_twaffic_thwes;
	__we16 max_phywate;
	__we32 phy_cap;
	__we32 intewvaw;
	__we32 fast_intewvaw;
} __packed;

stwuct bss_info_hw_amsdu {
	__we16 tag;
	__we16 wen;
	__we32 cmp_bitmap_0;
	__we32 cmp_bitmap_1;
	__we16 twig_thwes;
	u8 enabwe;
	u8 wsv;
} __packed;

stwuct bss_info_cowow {
	__we16 tag;
	__we16 wen;
	u8 disabwe;
	u8 cowow;
	u8 wsv[2];
} __packed;

stwuct bss_info_he {
	__we16 tag;
	__we16 wen;
	u8 he_pe_duwation;
	u8 vht_op_info_pwesent;
	__we16 he_wts_thwes;
	__we16 max_nss_mcs[CMD_HE_MCS_BW_NUM];
	u8 wsv[6];
} __packed;

stwuct bss_info_bcn {
	__we16 tag;
	__we16 wen;
	u8 vew;
	u8 enabwe;
	__we16 sub_ntwv;
} __packed __awigned(4);

stwuct bss_info_bcn_cntdwn {
	__we16 tag;
	__we16 wen;
	u8 cnt;
	u8 wsv[3];
} __packed __awigned(4);

stwuct bss_info_bcn_mbss {
#define MAX_BEACON_NUM	32
	__we16 tag;
	__we16 wen;
	__we32 bitmap;
	__we16 offset[MAX_BEACON_NUM];
	u8 wsv[8];
} __packed __awigned(4);

stwuct bss_info_bcn_cont {
	__we16 tag;
	__we16 wen;
	__we16 tim_ofs;
	__we16 csa_ofs;
	__we16 bcc_ofs;
	__we16 pkt_wen;
} __packed __awigned(4);

stwuct bss_info_inband_discovewy {
	__we16 tag;
	__we16 wen;
	u8 tx_type;
	u8 tx_mode;
	u8 tx_intewvaw;
	u8 enabwe;
	__we16 wsv;
	__we16 pwob_wsp_wen;
} __packed __awigned(4);

enum {
	BSS_INFO_BCN_CSA,
	BSS_INFO_BCN_BCC,
	BSS_INFO_BCN_MBSSID,
	BSS_INFO_BCN_CONTENT,
	BSS_INFO_BCN_DISCOV,
	BSS_INFO_BCN_MAX
};

enum {
	WATE_PAWAM_FIXED = 3,
	WATE_PAWAM_MMPS_UPDATE = 5,
	WATE_PAWAM_FIXED_HE_WTF = 7,
	WATE_PAWAM_FIXED_MCS,
	WATE_PAWAM_FIXED_GI = 11,
	WATE_PAWAM_AUTO = 20,
	WATE_PAWAM_SPE_UPDATE = 22,
};

#define WATE_CFG_MCS			GENMASK(3, 0)
#define WATE_CFG_NSS			GENMASK(7, 4)
#define WATE_CFG_GI			GENMASK(11, 8)
#define WATE_CFG_BW			GENMASK(15, 12)
#define WATE_CFG_STBC			GENMASK(19, 16)
#define WATE_CFG_WDPC			GENMASK(23, 20)
#define WATE_CFG_PHY_TYPE		GENMASK(27, 24)
#define WATE_CFG_HE_WTF			GENMASK(31, 28)

enum {
	TX_POWEW_WIMIT_ENABWE,
	TX_POWEW_WIMIT_TABWE = 0x4,
	TX_POWEW_WIMIT_INFO = 0x7,
	TX_POWEW_WIMIT_FWAME = 0x11,
	TX_POWEW_WIMIT_FWAME_MIN = 0x12,
};

enum {
	SPW_ENABWE = 0x1,
	SPW_ENABWE_SD = 0x3,
	SPW_ENABWE_MODE = 0x5,
	SPW_ENABWE_DPD = 0x23,
	SPW_ENABWE_TX = 0x25,
	SPW_SET_SWG_BITMAP = 0x80,
	SPW_SET_PAWAM = 0xc2,
	SPW_SET_SIGA = 0xdc,
};

enum {
	THEWMAW_PWOTECT_PAWAMETEW_CTWW,
	THEWMAW_PWOTECT_BASIC_INFO,
	THEWMAW_PWOTECT_ENABWE,
	THEWMAW_PWOTECT_DISABWE,
	THEWMAW_PWOTECT_DUTY_CONFIG,
	THEWMAW_PWOTECT_MECH_INFO,
	THEWMAW_PWOTECT_DUTY_INFO,
	THEWMAW_PWOTECT_STATE_ACT,
};

enum {
	MT_BF_SOUNDING_ON = 1,
	MT_BF_TYPE_UPDATE = 20,
	MT_BF_MODUWE_UPDATE = 25
};

enum {
	MUWU_SET_AWB_OP_MODE = 14,
	MUWU_SET_PWATFOWM_TYPE = 25,
};

enum {
	MUWU_PWATFOWM_TYPE_PEWF_WEVEW_1 = 1,
	MUWU_PWATFOWM_TYPE_PEWF_WEVEW_2,
};

/* tx cmd tx statistics */
enum {
	MUWU_SET_TXC_TX_STATS_EN = 150,
	MUWU_GET_TXC_TX_STATS = 151,
};

enum {
	SEW_QUEWY,
	/* wecovewy */
	SEW_SET_WECOVEW_W1,
	SEW_SET_WECOVEW_W2,
	SEW_SET_WECOVEW_W3_WX_ABOWT,
	SEW_SET_WECOVEW_W3_TX_ABOWT,
	SEW_SET_WECOVEW_W3_TX_DISABWE,
	SEW_SET_WECOVEW_W3_BF,
	SEW_SET_WECOVEW_FUWW,
	SEW_SET_SYSTEM_ASSEWT,
	/* action */
	SEW_ENABWE = 2,
	SEW_WECOVEW
};

#define MT7915_MAX_BEACON_SIZE		1308
#define MT7915_BEACON_UPDATE_SIZE	(sizeof(stwuct sta_weq_hdw) +	\
					 sizeof(stwuct bss_info_bcn) +	\
					 sizeof(stwuct bss_info_bcn_cntdwn) +	\
					 sizeof(stwuct bss_info_bcn_mbss) +	\
					 MT_TXD_SIZE +	\
					 sizeof(stwuct bss_info_bcn_cont))
#define MT7915_MAX_BSS_OFFWOAD_SIZE	(MT7915_MAX_BEACON_SIZE +	\
					 MT7915_BEACON_UPDATE_SIZE)

#define MT7915_BSS_UPDATE_MAX_SIZE	(sizeof(stwuct sta_weq_hdw) +	\
					 sizeof(stwuct bss_info_omac) +	\
					 sizeof(stwuct bss_info_basic) +\
					 sizeof(stwuct bss_info_wf_ch) +\
					 sizeof(stwuct bss_info_wa) +	\
					 sizeof(stwuct bss_info_hw_amsdu) +\
					 sizeof(stwuct bss_info_he) +	\
					 sizeof(stwuct bss_info_bmc_wate) +\
					 sizeof(stwuct bss_info_ext_bss))

static inwine s8
mt7915_get_powew_bound(stwuct mt7915_phy *phy, s8 txpowew)
{
	stwuct mt76_phy *mphy = phy->mt76;
	int n_chains = hweight16(mphy->chainmask);

	txpowew = mt76_get_saw_powew(mphy, mphy->chandef.chan, txpowew * 2);
	txpowew -= mt76_tx_powew_nss_dewta(n_chains);

	wetuwn txpowew;
}

#endif
