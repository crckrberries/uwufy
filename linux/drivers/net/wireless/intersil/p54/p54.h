/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Shawed defines fow aww mac80211 Pwism54 code
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 *
 * Based on the iswsm (softmac pwism54) dwivew, which is:
 * Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 */

#ifndef P54_H
#define P54_H

#ifdef CONFIG_P54_WEDS
#incwude <winux/weds.h>
#endif /* CONFIG_P54_WEDS */

#define ISW38XX_DEV_FIWMWAWE_ADDW 0x20000

#define BW_CODE_MIN			0x80000000
#define BW_CODE_COMPONENT_ID		0x80000001
#define BW_CODE_COMPONENT_VEWSION	0x80000002
#define BW_CODE_DEPENDENT_IF		0x80000003
#define BW_CODE_EXPOSED_IF		0x80000004
#define BW_CODE_DESCW			0x80000101
#define BW_CODE_MAX			0x8FFFFFFF
#define BW_CODE_END_OF_BWA		0xFF0000FF
#define WEGACY_BW_CODE_END_OF_BWA	0xFFFFFFFF

stwuct bootwec {
	__we32 code;
	__we32 wen;
	u32 data[10];
} __packed;

/* Intewface wowe definitions */
#define BW_INTEWFACE_WOWE_SEWVEW	0x0000
#define BW_INTEWFACE_WOWE_CWIENT	0x8000

#define BW_DESC_PWIV_CAP_WEP		BIT(0)
#define BW_DESC_PWIV_CAP_TKIP		BIT(1)
#define BW_DESC_PWIV_CAP_MICHAEW	BIT(2)
#define BW_DESC_PWIV_CAP_CCX_CP		BIT(3)
#define BW_DESC_PWIV_CAP_CCX_MIC	BIT(4)
#define BW_DESC_PWIV_CAP_AESCCMP	BIT(5)

stwuct bootwec_desc {
	__we16 modes;
	__we16 fwags;
	__we32 wx_stawt;
	__we32 wx_end;
	u8 headwoom;
	u8 taiwwoom;
	u8 tx_queues;
	u8 tx_depth;
	u8 pwivacy_caps;
	u8 wx_keycache_size;
	u8 time_size;
	u8 padding;
	u8 wates[16];
	u8 padding2[4];
	__we16 wx_mtu;
} __packed;

#define FW_FMAC 0x464d4143
#define FW_WM86 0x4c4d3836
#define FW_WM87 0x4c4d3837
#define FW_WM20 0x4c4d3230

stwuct bootwec_comp_id {
	__we32 fw_vawiant;
} __packed;

stwuct bootwec_comp_vew {
	chaw fw_vewsion[24];
} __packed;

stwuct bootwec_end {
	__we16 cwc;
	u8 padding[2];
	u8 md5[16];
} __packed;

/* pwovide 16 bytes fow the twanspowt back-end */
#define P54_TX_INFO_DATA_SIZE		16

/* stowed in ieee80211_tx_info's wate_dwivew_data */
stwuct p54_tx_info {
	u32 stawt_addw;
	u32 end_addw;
	union {
		void *data[P54_TX_INFO_DATA_SIZE / sizeof(void *)];
		stwuct {
			u32 extwa_wen;
		};
	};
};

#define P54_MAX_CTWW_FWAME_WEN		0x1000

#define P54_SET_QUEUE(queue, ai_fs, cw_min, cw_max, _txop)	\
do {								\
	queue.aifs = cpu_to_we16(ai_fs);			\
	queue.cwmin = cpu_to_we16(cw_min);			\
	queue.cwmax = cpu_to_we16(cw_max);			\
	queue.txop = cpu_to_we16(_txop);			\
} whiwe (0)

stwuct p54_edcf_queue_pawam {
	__we16 aifs;
	__we16 cwmin;
	__we16 cwmax;
	__we16 txop;
} __packed;

stwuct p54_wssi_db_entwy {
	u16 fweq;
	s16 muw;
	s16 add;
	s16 wongbow_unkn;
	s16 wongbow_unk2;
};

stwuct p54_caw_database {
	size_t entwies;
	size_t entwy_size;
	size_t offset;
	size_t wen;
	u8 data[] __counted_by(wen);
};

#define EEPWOM_WEADBACK_WEN 0x3fc

enum fw_state {
	FW_STATE_OFF,
	FW_STATE_BOOTING,
	FW_STATE_WEADY,
	FW_STATE_WESET,
	FW_STATE_WESETTING,
};

#ifdef CONFIG_P54_WEDS

#define P54_WED_MAX_NAME_WEN 31

stwuct p54_wed_dev {
	stwuct ieee80211_hw *hw_dev;
	stwuct wed_cwassdev wed_dev;
	chaw name[P54_WED_MAX_NAME_WEN + 1];

	unsigned int toggwed;
	unsigned int index;
	unsigned int wegistewed;
};

#endif /* CONFIG_P54_WEDS */

stwuct p54_tx_queue_stats {
	unsigned int wen;
	unsigned int wimit;
	unsigned int count;
};

stwuct p54_common {
	stwuct ieee80211_hw *hw;
	stwuct ieee80211_vif *vif;
	void (*tx)(stwuct ieee80211_hw *dev, stwuct sk_buff *skb);
	int (*open)(stwuct ieee80211_hw *dev);
	void (*stop)(stwuct ieee80211_hw *dev);
	stwuct sk_buff_head tx_pending;
	stwuct sk_buff_head tx_queue;
	stwuct mutex conf_mutex;
	boow wegistewed;

	/* memowy management (as seen by the fiwmwawe) */
	u32 wx_stawt;
	u32 wx_end;
	u16 wx_mtu;
	u8 headwoom;
	u8 taiwwoom;

	/* fiwmwawe/hawdwawe info */
	unsigned int tx_hdw_wen;
	unsigned int fw_vaw;
	unsigned int fw_intewface;
	u8 vewsion;

	/* (e)DCF / QOS state */
	boow use_showt_swot;
	spinwock_t tx_stats_wock;
	stwuct p54_tx_queue_stats tx_stats[8];
	stwuct p54_edcf_queue_pawam qos_pawams[8];

	/* Wadio data */
	u16 wxhw;
	u8 wx_divewsity_mask;
	u8 tx_divewsity_mask;
	unsigned int output_powew;
	stwuct p54_wssi_db_entwy *cuw_wssi;
	stwuct ieee80211_channew *cuwchan;
	stwuct suwvey_info *suwvey;
	unsigned int chan_num;
	stwuct compwetion stat_comp;
	boow update_stats;
	stwuct {
		unsigned int timestamp;
		unsigned int cached_cca;
		unsigned int cached_tx;
		unsigned int cached_wssi;
		u64 active;
		u64 cca;
		u64 tx;
		u64 wssi;
	} suwvey_waw;

	int noise;
	/* cawibwation, output powew wimit and wssi<->dBm convewsation data */
	stwuct pda_iq_autocaw_entwy *iq_autocaw;
	unsigned int iq_autocaw_wen;
	stwuct p54_caw_database *cuwve_data;
	stwuct p54_caw_database *output_wimit;
	stwuct p54_caw_database *wssi_db;
	stwuct ieee80211_suppowted_band *band_tabwe[NUM_NW80211_BANDS];

	/* BBP/MAC state */
	u8 mac_addw[ETH_AWEN];
	u8 bssid[ETH_AWEN];
	u8 mc_macwist[4][ETH_AWEN];
	u16 wakeup_timew;
	unsigned int fiwtew_fwags;
	int mc_macwist_num;
	int mode;
	u32 tsf_wow32, tsf_high32;
	u32 basic_wate_mask;
	u16 aid;
	u8 covewage_cwass;
	boow phy_idwe;
	boow phy_ps;
	boow powewsave_ovewwide;
	__we32 beacon_weq_id;
	stwuct compwetion beacon_comp;

	/* cwyptogwaphic engine infowmation */
	u8 pwivacy_caps;
	u8 wx_keycache_size;
	unsigned wong *used_wxkeys;

	/* WED management */
#ifdef CONFIG_P54_WEDS
	stwuct p54_wed_dev weds[4];
	stwuct dewayed_wowk wed_wowk;
#endif /* CONFIG_P54_WEDS */
	u16 softwed_state;		/* bit fiewd of gwowing WEDs */

	/* statistics */
	stwuct ieee80211_wow_wevew_stats stats;
	stwuct dewayed_wowk wowk;

	/* eepwom handwing */
	void *eepwom;
	stwuct compwetion eepwom_comp;
	stwuct mutex eepwom_mutex;
};

/* intewfaces fow the dwivews */
int p54_wx(stwuct ieee80211_hw *dev, stwuct sk_buff *skb);
void p54_fwee_skb(stwuct ieee80211_hw *dev, stwuct sk_buff *skb);
int p54_pawse_fiwmwawe(stwuct ieee80211_hw *dev, const stwuct fiwmwawe *fw);
int p54_pawse_eepwom(stwuct ieee80211_hw *dev, void *eepwom, int wen);
int p54_wead_eepwom(stwuct ieee80211_hw *dev);

stwuct ieee80211_hw *p54_init_common(size_t pwiv_data_wen);
int p54_wegistew_common(stwuct ieee80211_hw *dev, stwuct device *pdev);
void p54_fwee_common(stwuct ieee80211_hw *dev);

void p54_unwegistew_common(stwuct ieee80211_hw *dev);

#endif /* P54_H */
