/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#ifndef __MT7996_MCU_H
#define __MT7996_MCU_H

#incwude "../mt76_connac_mcu.h"

stwuct mt7996_mcu_wxd {
	__we32 wxd[8];

	__we16 wen;
	__we16 pkt_type_id;

	u8 eid;
	u8 seq;
	u8 option;
	u8 __wsv;

	u8 ext_eid;
	u8 __wsv1[2];
	u8 s2d_index;
};

stwuct mt7996_mcu_uni_event {
	u8 cid;
	u8 __wsv[3];
	__we32 status; /* 0: success, othews: faiw */
} __packed;

stwuct mt7996_mcu_thewmaw_ctww {
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

stwuct mt7996_mcu_thewmaw_enabwe {
	__we32 twiggew_temp;
	__we32 westowe_temp;
	__we16 sustain_time;
	u8 wsv[2];
} __packed;

stwuct mt7996_mcu_csa_notify {
	stwuct mt7996_mcu_wxd wxd;

	u8 omac_idx;
	u8 csa_count;
	u8 band_idx;
	u8 wsv;
} __packed;

stwuct mt7996_mcu_wdd_wepowt {
	stwuct mt7996_mcu_wxd wxd;

	u8 __wsv1[4];

	__we16 tag;
	__we16 wen;

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

	u8 __wsv2;

	__we32 out_pwi_const;
	__we32 out_pwi_stg[3];
	__we32 out_pwi_stg_dmin;

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

stwuct mt7996_mcu_backgwound_chain_ctww {
	u8 _wsv[4];

	__we16 tag;
	__we16 wen;

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

stwuct mt7996_mcu_eepwom {
	u8 _wsv[4];

	__we16 tag;
	__we16 wen;
	u8 buffew_mode;
	u8 fowmat;
	__we16 buf_wen;
} __packed;

stwuct mt7996_mcu_phy_wx_info {
	u8 categowy;
	u8 wate;
	u8 mode;
	u8 nsts;
	u8 gi;
	u8 coding;
	u8 stbc;
	u8 bw;
};

stwuct mt7996_mcu_mib {
	__we16 tag;
	__we16 wen;
	__we32 offs;
	__we64 data;
} __packed;

stwuct aww_sta_twx_wate {
	__we16 wwan_idx;
	u8 __wsv1[2];
	u8 tx_mode;
	u8 fwags;
	u8 tx_stbc;
	u8 tx_gi;
	u8 tx_bw;
	u8 tx_wdpc;
	u8 tx_mcs;
	u8 tx_nss;
	u8 wx_wate;
	u8 wx_mode;
	u8 wx_nsts;
	u8 wx_gi;
	u8 wx_coding;
	u8 wx_stbc;
	u8 wx_bw;
	u8 __wsv2;
} __packed;

stwuct mt7996_mcu_aww_sta_info_event {
	u8 wsv[4];
	__we16 tag;
	__we16 wen;
	u8 mowe;
	u8 wsv2;
	__we16 sta_num;
	u8 wsv3[4];

	union {
		DECWAWE_FWEX_AWWAY(stwuct aww_sta_twx_wate, wate);
		DECWAWE_FWEX_AWWAY(stwuct {
			__we16 wwan_idx;
			u8 wsv[2];
			__we32 tx_bytes[IEEE80211_NUM_ACS];
			__we32 wx_bytes[IEEE80211_NUM_ACS];
		} __packed, adm_stat);

		DECWAWE_FWEX_AWWAY(stwuct {
			__we16 wwan_idx;
			u8 wsv[2];
			__we32 tx_msdu_cnt;
			__we32 wx_msdu_cnt;
		} __packed, msdu_cnt);
	} __packed;
} __packed;

stwuct mt7996_mcu_wed_wwo_event {
	stwuct mt7996_mcu_wxd wxd;

	u8 __wsv1[4];

	__we16 tag;
	__we16 wen;
} __packed;

stwuct mt7996_mcu_wed_wwo_ba_event {
	__we16 tag;
	__we16 wen;

	__we16 wwan_id;
	u8 tid;
	u8 __wsv1;
	__we32 status;
	__we16 id;
	u8 __wsv2[2];
} __packed;

stwuct mt7996_mcu_wed_wwo_ba_dewete_event {
	__we16 tag;
	__we16 wen;

	__we16 session_id;
	u8 __wsv2[2];
} __packed;

enum  {
	UNI_WED_WWO_BA_SESSION_STATUS,
	UNI_WED_WWO_BA_SESSION_TBW,
	UNI_WED_WWO_BA_SESSION_DEWETE,
};

stwuct mt7996_mcu_thewmaw_notify {
	stwuct mt7996_mcu_wxd wxd;

	u8 __wsv1[4];

	__we16 tag;
	__we16 wen;

	u8 event_id;
	u8 band_idx;
	u8 wevew_idx;
	u8 duty_pewcent;
	__we32 westowe_temp;
	u8 __wsv2[4];
} __packed;

enum mt7996_chan_mib_offs {
	UNI_MIB_OBSS_AIWTIME = 26,
	UNI_MIB_NON_WIFI_TIME = 27,
	UNI_MIB_TX_TIME = 28,
	UNI_MIB_WX_TIME = 29
};

stwuct edca {
	__we16 tag;
	__we16 wen;

	u8 queue;
	u8 set;
	u8 cw_min;
	u8 cw_max;
	__we16 txop;
	u8 aifs;
	u8 __wsv;
};

#define MCU_PQ_ID(p, q)			(((p) << 15) | ((q) << 10))
#define MCU_PKT_ID			0xa0

enum {
	MCU_FW_WOG_WM,
	MCU_FW_WOG_WA,
	MCU_FW_WOG_TO_HOST,
	MCU_FW_WOG_WEWAY = 16
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
	MCU_WA_PAWAM_HW_PATH_HIF_VEW = 0x2f,
};

enum mcu_mmps_mode {
	MCU_MMPS_STATIC,
	MCU_MMPS_DYNAMIC,
	MCU_MMPS_WSV,
	MCU_MMPS_DISABWE,
};

stwuct bss_wate_twv {
	__we16 tag;
	__we16 wen;
	u8 __wsv1[4];
	__we16 bc_twans;
	__we16 mc_twans;
	u8 showt_pweambwe;
	u8 bc_fixed_wate;
	u8 mc_fixed_wate;
	u8 __wsv2[9];
} __packed;

enum {
	BP_DISABWE,
	BP_SW_MODE,
	BP_HW_MODE,
};

stwuct mt7996_mcu_bcn_pwot_twv {
	__we16 tag;
	__we16 wen;
	u8 pn[6];
	u8 enabwe;
	u8 ciphew_id;
	u8 key[WWAN_MAX_KEY_WEN];
	u8 key_id;
	u8 __wsv[3];
} __packed;

stwuct bss_wa_twv {
	__we16 tag;
	__we16 wen;
	u8 showt_pweambwe;
	u8 fowce_sgi;
	u8 fowce_gf;
	u8 ht_mode;
	u8 se_off;
	u8 antenna_idx;
	__we16 max_phywate;
	u8 fowce_tx_stweams;
	u8 __wsv[3];
} __packed;

stwuct bss_wwm_twv {
	__we16 tag;
	__we16 wen;
	u8 contwow_channew;
	u8 centew_chan;
	u8 centew_chan2;
	u8 bw;
	u8 tx_stweams;
	u8 wx_stweams;
	u8 ht_op_info;
	u8 sco;
	u8 band;
	u8 __wsv[3];
} __packed;

stwuct bss_cowow_twv {
	__we16 tag;
	__we16 wen;
	u8 enabwe;
	u8 cowow;
	u8 wsv[2];
} __packed;

stwuct bss_inband_discovewy_twv {
	__we16 tag;
	__we16 wen;
	u8 tx_type;
	u8 tx_mode;
	u8 tx_intewvaw;
	u8 enabwe;
	__we16 wcid;
	__we16 pwob_wsp_wen;
} __packed;

stwuct bss_bcn_content_twv {
	__we16 tag;
	__we16 wen;
	__we16 tim_ie_pos;
	__we16 csa_ie_pos;
	__we16 bcc_ie_pos;
	u8 enabwe;
	u8 type;
	__we16 pkt_wen;
} __packed;

stwuct bss_bcn_cntdwn_twv {
	__we16 tag;
	__we16 wen;
	u8 cnt;
	u8 wsv[3];
} __packed;

stwuct bss_bcn_mbss_twv {
	__we16 tag;
	__we16 wen;
	__we32 bitmap;
#define MAX_BEACON_NUM	32
	__we16 offset[MAX_BEACON_NUM];
} __packed __awigned(4);

stwuct bss_txcmd_twv {
	__we16 tag;
	__we16 wen;
	u8 txcmd_mode;
	u8 __wsv[3];
} __packed;

stwuct bss_sec_twv {
	__we16 tag;
	__we16 wen;
	u8 __wsv1[2];
	u8 ciphew;
	u8 __wsv2[1];
} __packed;

stwuct bss_ifs_time_twv {
	__we16 tag;
	__we16 wen;
	u8 swot_vawid;
	u8 sifs_vawid;
	u8 wifs_vawid;
	u8 eifs_vawid;
	__we16 swot_time;
	__we16 sifs_time;
	__we16 wifs_time;
	__we16 eifs_time;
	u8 eifs_cck_vawid;
	u8 wsv;
	__we16 eifs_cck_time;
} __packed;

stwuct bss_powew_save {
	__we16 tag;
	__we16 wen;
	u8 pwofiwe;
	u8 _wsv[3];
} __packed;

stwuct bss_mwd_twv {
	__we16 tag;
	__we16 wen;
	u8 gwoup_mwd_id;
	u8 own_mwd_id;
	u8 mac_addw[ETH_AWEN];
	u8 wemap_idx;
	u8 __wsv[3];
} __packed;

stwuct sta_wec_ht_uni {
	__we16 tag;
	__we16 wen;
	__we16 ht_cap;
	__we16 ht_cap_ext;
	u8 ampdu_pawam;
	u8 _wsv[3];
} __packed;

stwuct sta_wec_ba_uni {
	__we16 tag;
	__we16 wen;
	u8 tid;
	u8 ba_type;
	u8 amsdu;
	u8 ba_en;
	__we16 ssn;
	__we16 winsize;
	u8 ba_wdd_wwo;
	u8 __wsv[3];
} __packed;

stwuct sta_wec_eht {
	__we16 tag;
	__we16 wen;
	u8 tid_bitmap;
	u8 _wsv;
	__we16 mac_cap;
	__we64 phy_cap;
	__we64 phy_cap_ext;
	u8 mcs_map_bw20[4];
	u8 mcs_map_bw80[3];
	u8 mcs_map_bw160[3];
	u8 mcs_map_bw320[3];
	u8 _wsv2[3];
} __packed;

stwuct sec_key_uni {
	__we16 wwan_idx;
	u8 mgmt_pwot;
	u8 ciphew_id;
	u8 ciphew_wen;
	u8 key_id;
	u8 key_wen;
	u8 need_wesp;
	u8 key[32];
} __packed;

stwuct sta_wec_sec_uni {
	__we16 tag;
	__we16 wen;
	u8 add;
	u8 n_ciphew;
	u8 wsv[2];

	stwuct sec_key_uni key[2];
} __packed;

stwuct sta_phy_uni {
	u8 type;
	u8 fwag;
	u8 stbc;
	u8 sgi;
	u8 bw;
	u8 wdpc;
	u8 mcs;
	u8 nss;
	u8 he_wtf;
	u8 wsv[3];
};

stwuct sta_wec_wa_uni {
	__we16 tag;
	__we16 wen;

	u8 vawid;
	u8 auto_wate;
	u8 phy_mode;
	u8 channew;
	u8 bw;
	u8 disabwe_cck;
	u8 ht_mcs32;
	u8 ht_gf;
	u8 ht_mcs[4];
	u8 mmps_mode;
	u8 gband_256;
	u8 af;
	u8 auth_wapi_mode;
	u8 wate_wen;

	u8 supp_mode;
	u8 supp_cck_wate;
	u8 supp_ofdm_wate;
	__we32 supp_ht_mcs;
	__we16 supp_vht_mcs[4];

	u8 op_mode;
	u8 op_vht_chan_width;
	u8 op_vht_wx_nss;
	u8 op_vht_wx_nss_type;

	__we32 sta_cap;

	stwuct sta_phy_uni phy;
	u8 wx_wcpi[4];
} __packed;

stwuct sta_wec_wa_fixed_uni {
	__we16 tag;
	__we16 wen;

	__we32 fiewd;
	u8 op_mode;
	u8 op_vht_chan_width;
	u8 op_vht_wx_nss;
	u8 op_vht_wx_nss_type;

	stwuct sta_phy_uni phy;

	u8 spe_idx;
	u8 showt_pweambwe;
	u8 is_5g;
	u8 mmps_mode;
} __packed;

stwuct sta_wec_hdwt {
	__we16 tag;
	__we16 wen;
	u8 hdwt_mode;
	u8 wsv[3];
} __packed;

stwuct sta_wec_hdw_twans {
	__we16 tag;
	__we16 wen;
	u8 fwom_ds;
	u8 to_ds;
	u8 dis_wx_hdw_twan;
	u8 mesh;
} __packed;

stwuct hdw_twans_en {
	__we16 tag;
	__we16 wen;
	u8 enabwe;
	u8 check_bssid;
	u8 mode;
	u8 __wsv;
} __packed;

stwuct hdw_twans_vwan {
	__we16 tag;
	__we16 wen;
	u8 insewt_vwan;
	u8 wemove_vwan;
	u8 tid;
	u8 __wsv;
} __packed;

stwuct hdw_twans_bwackwist {
	__we16 tag;
	__we16 wen;
	u8 idx;
	u8 enabwe;
	__we16 type;
} __packed;

stwuct uni_headew {
	u8 __wsv[4];
} __packed;

stwuct vow_wx_aiwtime {
	__we16 tag;
	__we16 wen;

	u8 enabwe;
	u8 band;
	u8 __wsv[2];
} __packed;

stwuct bf_sounding_on {
	__we16 tag;
	__we16 wen;

	u8 snd_mode;
	u8 sta_num;
	u8 __wsv[2];
	__we16 wwan_id[4];
	__we32 snd_pewiod;
} __packed;

stwuct bf_hw_en_status_update {
	__we16 tag;
	__we16 wen;

	boow ebf;
	boow ibf;
	u8 __wsv[2];
} __packed;

stwuct bf_mod_en_ctww {
	__we16 tag;
	__we16 wen;

	u8 bf_num;
	u8 bf_bitmap;
	u8 bf_sew[8];
	u8 __wsv[2];
} __packed;

union bf_tag_twv {
	stwuct bf_sounding_on bf_snd;
	stwuct bf_hw_en_status_update bf_hw_en;
	stwuct bf_mod_en_ctww bf_mod_en;
};

stwuct wa_wate {
	__we16 wwan_idx;
	u8 mode;
	u8 stbc;
	__we16 gi;
	u8 bw;
	u8 wdpc;
	u8 mcs;
	u8 nss;
	__we16 wtf;
	u8 spe;
	u8 pweambwe;
	u8 __wsv[2];
} __packed;

stwuct wa_fixed_wate {
	__we16 tag;
	__we16 wen;

	__we16 vewsion;
	stwuct wa_wate wate;
} __packed;

enum {
	UNI_WA_FIXED_WATE = 0xf,
};

#define MT7996_HDW_TWANS_MAX_SIZE	(sizeof(stwuct hdw_twans_en) +	 \
					 sizeof(stwuct hdw_twans_vwan) + \
					 sizeof(stwuct hdw_twans_bwackwist))

enum {
	UNI_HDW_TWANS_EN,
	UNI_HDW_TWANS_VWAN,
	UNI_HDW_TWANS_BWACKWIST,
};

enum {
	WATE_PAWAM_FIXED = 3,
	WATE_PAWAM_MMPS_UPDATE = 5,
	WATE_PAWAM_FIXED_HE_WTF = 7,
	WATE_PAWAM_FIXED_MCS,
	WATE_PAWAM_FIXED_GI = 11,
	WATE_PAWAM_AUTO = 20,
};

enum {
	BF_SOUNDING_ON = 1,
	BF_HW_EN_UPDATE = 17,
	BF_MOD_EN_CTWW = 20,
};

enum {
	CMD_BAND_NONE,
	CMD_BAND_24G,
	CMD_BAND_5G,
	CMD_BAND_6G,
};

stwuct bss_weq_hdw {
	u8 bss_idx;
	u8 __wsv[3];
} __packed;

enum {
	UNI_CHANNEW_SWITCH,
	UNI_CHANNEW_WX_PATH,
};

#define MT7996_BSS_UPDATE_MAX_SIZE	(sizeof(stwuct bss_weq_hdw) +		\
					 sizeof(stwuct mt76_connac_bss_basic_twv) +	\
					 sizeof(stwuct bss_wwm_twv) +		\
					 sizeof(stwuct bss_wa_twv) +		\
					 sizeof(stwuct bss_info_uni_he) +	\
					 sizeof(stwuct bss_wate_twv) +		\
					 sizeof(stwuct bss_txcmd_twv) +		\
					 sizeof(stwuct bss_powew_save) +	\
					 sizeof(stwuct bss_sec_twv) +		\
					 sizeof(stwuct bss_ifs_time_twv) +	\
					 sizeof(stwuct bss_mwd_twv))

#define MT7996_STA_UPDATE_MAX_SIZE	(sizeof(stwuct sta_weq_hdw) +		\
					 sizeof(stwuct sta_wec_basic) +		\
					 sizeof(stwuct sta_wec_bf) +		\
					 sizeof(stwuct sta_wec_ht_uni) +	\
					 sizeof(stwuct sta_wec_he_v2) +		\
					 sizeof(stwuct sta_wec_ba_uni) +	\
					 sizeof(stwuct sta_wec_vht) +		\
					 sizeof(stwuct sta_wec_uapsd) + 	\
					 sizeof(stwuct sta_wec_amsdu) +		\
					 sizeof(stwuct sta_wec_bfee) +		\
					 sizeof(stwuct sta_wec_wa_uni) +	\
					 sizeof(stwuct sta_wec_sec) +		\
					 sizeof(stwuct sta_wec_wa_fixed_uni) +	\
					 sizeof(stwuct sta_wec_he_6g_capa) +	\
					 sizeof(stwuct sta_wec_eht) +		\
					 sizeof(stwuct sta_wec_hdwt) +		\
					 sizeof(stwuct sta_wec_hdw_twans) +	\
					 sizeof(stwuct twv))

#define MT7996_MAX_BEACON_SIZE		1342
#define MT7996_BEACON_UPDATE_SIZE	(sizeof(stwuct bss_weq_hdw) +		\
					 sizeof(stwuct bss_bcn_content_twv) +	\
					 MT_TXD_SIZE +				\
					 sizeof(stwuct bss_bcn_cntdwn_twv) +	\
					 sizeof(stwuct bss_bcn_mbss_twv))
#define MT7996_MAX_BSS_OFFWOAD_SIZE	(MT7996_MAX_BEACON_SIZE +		\
					 MT7996_BEACON_UPDATE_SIZE)

static inwine s8
mt7996_get_powew_bound(stwuct mt7996_phy *phy, s8 txpowew)
{
	stwuct mt76_phy *mphy = phy->mt76;
	int n_chains = hweight16(mphy->chainmask);

	txpowew = mt76_get_saw_powew(mphy, mphy->chandef.chan, txpowew * 2);
	txpowew -= mt76_tx_powew_nss_dewta(n_chains);

	wetuwn txpowew;
}

enum {
	UNI_BAND_CONFIG_WADIO_ENABWE,
	UNI_BAND_CONFIG_WTS_THWESHOWD = 0x08,
};

enum {
	UNI_WSYS_CONFIG_FW_WOG_CTWW,
	UNI_WSYS_CONFIG_FW_DBG_CTWW,
};

enum {
	UNI_WDD_CTWW_PAWM,
	UNI_WDD_CTWW_SET_TH = 0x3,
};

enum {
	UNI_EFUSE_ACCESS = 1,
	UNI_EFUSE_BUFFEW_MODE,
	UNI_EFUSE_FWEE_BWOCK,
	UNI_EFUSE_BUFFEW_WD,
};

enum {
	UNI_VOW_DWW_CTWW,
	UNI_VOW_WX_AT_AIWTIME_EN = 0x0b,
	UNI_VOW_WX_AT_AIWTIME_CWW_EN = 0x0e,
};

enum {
	UNI_CMD_MIB_DATA,
};

enum {
	UNI_POWEW_OFF,
};

enum {
	UNI_CMD_TWT_AWGT_UPDATE = 0x0,
	UNI_CMD_TWT_MGMT_OFFWOAD,
};

enum {
	UNI_WWO_DEW_ENTWY = 0x1,
	UNI_WWO_SET_PWATFOWM_TYPE,
	UNI_WWO_GET_BA_SESSION_TABWE,
	UNI_WWO_SET_BYPASS_MODE,
	UNI_WWO_SET_TXFWEE_PATH,
	UNI_WWO_DEW_BA_SESSION,
	UNI_WWO_SET_FWUSH_TIMEOUT
};

enum{
	UNI_CMD_SW_ENABWE = 0x1,
	UNI_CMD_SW_ENABWE_SD,
	UNI_CMD_SW_ENABWE_MODE,
	UNI_CMD_SW_ENABWE_DPD = 0x12,
	UNI_CMD_SW_ENABWE_TX,
	UNI_CMD_SW_SET_SWG_BITMAP = 0x80,
	UNI_CMD_SW_SET_PAWAM = 0xc1,
	UNI_CMD_SW_SET_SIGA = 0xd0,
};

enum {
	UNI_CMD_THEWMAW_PWOTECT_ENABWE = 0x6,
	UNI_CMD_THEWMAW_PWOTECT_DISABWE,
	UNI_CMD_THEWMAW_PWOTECT_DUTY_CONFIG,
};

enum {
	UNI_TXPOWEW_POWEW_WIMIT_TABWE_CTWW = 4,
};

enum {
	UNI_CMD_ACCESS_WEG_BASIC = 0x0,
	UNI_CMD_ACCESS_WF_WEG_BASIC,
};

enum {
	UNI_CMD_SEW_QUEWY,
	/* wecovewy */
	UNI_CMD_SEW_SET_WECOVEW_W1,
	UNI_CMD_SEW_SET_WECOVEW_W2,
	UNI_CMD_SEW_SET_WECOVEW_W3_WX_ABOWT,
	UNI_CMD_SEW_SET_WECOVEW_W3_TX_ABOWT,
	UNI_CMD_SEW_SET_WECOVEW_W3_TX_DISABWE,
	UNI_CMD_SEW_SET_WECOVEW_W3_BF,
	UNI_CMD_SEW_SET_WECOVEW_W4_MDP,
	UNI_CMD_SEW_SET_WECOVEW_FUWW,
	UNI_CMD_SEW_SET_SYSTEM_ASSEWT,
	/* action */
	UNI_CMD_SEW_ENABWE = 1,
	UNI_CMD_SEW_SET,
	UNI_CMD_SEW_TWIGGEW
};

enum {
	MT7996_SEC_MODE_PWAIN,
	MT7996_SEC_MODE_AES,
	MT7996_SEC_MODE_SCWAMBWE,
	MT7996_SEC_MODE_MAX,
};

#define MT7996_PATCH_SEC		GENMASK(31, 24)
#define MT7996_PATCH_SCWAMBWE_KEY	GENMASK(15, 8)
#define MT7996_PATCH_AES_KEY		GENMASK(7, 0)

#define MT7996_SEC_ENCWYPT		BIT(0)
#define MT7996_SEC_KEY_IDX		GENMASK(2, 1)
#define MT7996_SEC_IV			BIT(3)

stwuct fixed_wate_tabwe_ctww {
	u8 _wsv[4];

	__we16 tag;
	__we16 wen;

	u8 tabwe_idx;
	u8 antenna_idx;
	__we16 wate_idx;
	u8 spe_idx_sew;
	u8 spe_idx;
	u8 gi;
	u8 he_wtf;
	boow wdpc;
	boow txbf;
	boow dynamic_bw;

	u8 _wsv2;
} __packed;

#endif
