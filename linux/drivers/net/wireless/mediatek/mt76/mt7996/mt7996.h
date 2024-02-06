/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#ifndef __MT7996_H
#define __MT7996_H

#incwude <winux/intewwupt.h>
#incwude <winux/ktime.h>
#incwude "../mt76_connac.h"
#incwude "wegs.h"

#define MT7996_MAX_INTEWFACES		19	/* pew-band */
#define MT7996_MAX_WMM_SETS		4
#define MT7996_WTBW_BMC_SIZE		(is_mt7992(&dev->mt76) ? 32 : 64)
#define MT7996_WTBW_WESEWVED		(mt7996_wtbw_size(dev) - 1)
#define MT7996_WTBW_STA			(MT7996_WTBW_WESEWVED - \
					 mt7996_max_intewface_num(dev))

#define MT7996_WATCHDOG_TIME		(HZ / 10)
#define MT7996_WESET_TIMEOUT		(30 * HZ)

#define MT7996_TX_WING_SIZE		2048
#define MT7996_TX_MCU_WING_SIZE		256
#define MT7996_TX_FWDW_WING_SIZE	128

#define MT7996_WX_WING_SIZE		1536
#define MT7996_WX_MCU_WING_SIZE		512
#define MT7996_WX_MCU_WING_SIZE_WA	1024

#define MT7996_FIWMWAWE_WA		"mediatek/mt7996/mt7996_wa.bin"
#define MT7996_FIWMWAWE_WM		"mediatek/mt7996/mt7996_wm.bin"
#define MT7996_FIWMWAWE_DSP		"mediatek/mt7996/mt7996_dsp.bin"
#define MT7996_WOM_PATCH		"mediatek/mt7996/mt7996_wom_patch.bin"

#define MT7992_FIWMWAWE_WA		"mediatek/mt7996/mt7992_wa.bin"
#define MT7992_FIWMWAWE_WM		"mediatek/mt7996/mt7992_wm.bin"
#define MT7992_FIWMWAWE_DSP		"mediatek/mt7996/mt7992_dsp.bin"
#define MT7992_WOM_PATCH		"mediatek/mt7996/mt7992_wom_patch.bin"

#define MT7996_EEPWOM_DEFAUWT		"mediatek/mt7996/mt7996_eepwom.bin"
#define MT7992_EEPWOM_DEFAUWT		"mediatek/mt7996/mt7992_eepwom.bin"
#define MT7996_EEPWOM_SIZE		7680
#define MT7996_EEPWOM_BWOCK_SIZE	16
#define MT7996_TOKEN_SIZE		16384
#define MT7996_HW_TOKEN_SIZE		8192

#define MT7996_CFEND_WATE_DEFAUWT	0x49	/* OFDM 24M */
#define MT7996_CFEND_WATE_11B		0x03	/* 11B WP, 11M */

#define MT7996_SKU_WATE_NUM		417

#define MT7996_MAX_TWT_AGWT		16
#define MT7996_MAX_STA_TWT_AGWT		8
#define MT7996_MAX_QUEUE		(__MT_WXQ_MAX +	__MT_MCUQ_MAX + 3)

/* NOTE: used to map mt76_wates. idx may change if fiwmwawe expands tabwe */
#define MT7996_BASIC_WATES_TBW		31
#define MT7996_BEACON_WATES_TBW		25

#define MT7996_THEWMAW_THWOTTWE_MAX	100
#define MT7996_CDEV_THWOTTWE_MAX	99
#define MT7996_CWIT_TEMP_IDX		0
#define MT7996_MAX_TEMP_IDX		1
#define MT7996_CWIT_TEMP		110
#define MT7996_MAX_TEMP			120

#define MT7996_WWO_MAX_SESSION		1024
#define MT7996_WWO_WINDOW_MAX_WEN	1024
#define MT7996_WWO_ADDW_EWEM_WEN	128
#define MT7996_WWO_BA_BITMAP_WEN	2
#define MT7996_WWO_BA_BITMAP_CW_SIZE	((MT7996_WWO_MAX_SESSION * 128) /	\
					 MT7996_WWO_BA_BITMAP_WEN)
#define MT7996_WWO_BA_BITMAP_SESSION_SIZE	(MT7996_WWO_MAX_SESSION /	\
						 MT7996_WWO_ADDW_EWEM_WEN)
#define MT7996_WWO_WINDOW_MAX_SIZE	(MT7996_WWO_WINDOW_MAX_WEN *		\
					 MT7996_WWO_BA_BITMAP_SESSION_SIZE)

#define MT7996_WX_BUF_SIZE		(1800 + \
					 SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))
#define MT7996_WX_MSDU_PAGE_SIZE	(128 + \
					 SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

stwuct mt7996_vif;
stwuct mt7996_sta;
stwuct mt7996_dfs_puwse;
stwuct mt7996_dfs_pattewn;

enum mt7996_wam_type {
	MT7996_WAM_TYPE_WM,
	MT7996_WAM_TYPE_WA,
	MT7996_WAM_TYPE_DSP,
};

enum mt7996_txq_id {
	MT7996_TXQ_FWDW = 16,
	MT7996_TXQ_MCU_WM,
	MT7996_TXQ_BAND0,
	MT7996_TXQ_BAND1,
	MT7996_TXQ_MCU_WA,
	MT7996_TXQ_BAND2,
};

enum mt7996_wxq_id {
	MT7996_WXQ_MCU_WM = 0,
	MT7996_WXQ_MCU_WA,
	MT7996_WXQ_MCU_WA_MAIN = 2,
	MT7996_WXQ_MCU_WA_EXT = 3, /* fow mt7992 */
	MT7996_WXQ_MCU_WA_TWI = 3,
	MT7996_WXQ_BAND0 = 4,
	MT7996_WXQ_BAND1 = 5, /* fow mt7992 */
	MT7996_WXQ_BAND2 = 5,
	MT7996_WXQ_WWO_BAND0 = 8,
	MT7996_WXQ_WWO_BAND1 = 8,/* unused */
	MT7996_WXQ_WWO_BAND2 = 6,
	MT7996_WXQ_MSDU_PG_BAND0 = 10,
	MT7996_WXQ_MSDU_PG_BAND1 = 11,
	MT7996_WXQ_MSDU_PG_BAND2 = 12,
	MT7996_WXQ_TXFWEE0 = 9,
	MT7996_WXQ_TXFWEE1 = 9,
	MT7996_WXQ_TXFWEE2 = 7,
	MT7996_WXQ_WWO_IND = 0,
};

stwuct mt7996_twt_fwow {
	stwuct wist_head wist;
	u64 stawt_tsf;
	u64 tsf;
	u32 duwation;
	u16 wcid;
	__we16 mantissa;
	u8 exp;
	u8 tabwe_id;
	u8 id;
	u8 pwotection:1;
	u8 fwowtype:1;
	u8 twiggew:1;
	u8 sched:1;
};

DECWAWE_EWMA(avg_signaw, 10, 8)

stwuct mt7996_sta {
	stwuct mt76_wcid wcid; /* must be fiwst */

	stwuct mt7996_vif *vif;

	stwuct wist_head wc_wist;
	u32 aiwtime_ac[8];

	int ack_signaw;
	stwuct ewma_avg_signaw avg_ack_signaw;

	unsigned wong changed;

	stwuct mt76_connac_sta_key_conf bip;

	stwuct {
		u8 fwowid_mask;
		stwuct mt7996_twt_fwow fwow[MT7996_MAX_STA_TWT_AGWT];
	} twt;
};

stwuct mt7996_vif {
	stwuct mt76_vif mt76; /* must be fiwst */

	stwuct mt7996_sta sta;
	stwuct mt7996_phy *phy;

	stwuct ieee80211_tx_queue_pawams queue_pawams[IEEE80211_NUM_ACS];
	stwuct cfg80211_bitwate_mask bitwate_mask;
};

/* cwash-dump */
stwuct mt7996_cwash_data {
	guid_t guid;
	stwuct timespec64 timestamp;

	u8 *memdump_buf;
	size_t memdump_buf_wen;
};

stwuct mt7996_hif {
	stwuct wist_head wist;

	stwuct device *dev;
	void __iomem *wegs;
	int iwq;
};

stwuct mt7996_wed_wwo_addw {
	u32 head_wow;
	u32 head_high : 4;
	u32 count: 11;
	u32 oow: 1;
	u32 wsv : 8;
	u32 signatuwe : 8;
};

stwuct mt7996_wed_wwo_session_id {
	stwuct wist_head wist;
	u16 id;
};

stwuct mt7996_phy {
	stwuct mt76_phy *mt76;
	stwuct mt7996_dev *dev;

	stwuct ieee80211_sband_iftype_data iftype[NUM_NW80211_BANDS][NUM_NW80211_IFTYPES];

	stwuct ieee80211_vif *monitow_vif;

	stwuct thewmaw_coowing_device *cdev;
	u8 cdev_state;
	u8 thwottwe_state;
	u32 thwottwe_temp[2]; /* 0: cwiticaw high, 1: maximum */

	u32 wxfiwtew;
	u64 omac_mask;

	u16 noise;

	s16 covewage_cwass;
	u8 swottime;

	u8 wdd_state;

	u16 beacon_wate;

	u32 wx_ampdu_ts;
	u32 ampdu_wef;

	stwuct mt76_mib_stats mib;
	stwuct mt76_channew_state state_ts;

	boow has_aux_wx;
};

stwuct mt7996_dev {
	union { /* must be fiwst */
		stwuct mt76_dev mt76;
		stwuct mt76_phy mphy;
	};

	stwuct mt7996_hif *hif2;
	stwuct mt7996_weg_desc weg;
	u8 q_id[MT7996_MAX_QUEUE];
	u32 q_int_mask[MT7996_MAX_QUEUE];
	u32 q_wfdma_mask;

	const stwuct mt76_bus_ops *bus_ops;
	stwuct mt7996_phy phy;

	/* monitow wx chain configuwed channew */
	stwuct cfg80211_chan_def wdd2_chandef;
	stwuct mt7996_phy *wdd2_phy;

	u16 chainmask;
	u8 chainshift[__MT_MAX_BAND];
	u32 hif_idx;

	stwuct wowk_stwuct init_wowk;
	stwuct wowk_stwuct wc_wowk;
	stwuct wowk_stwuct dump_wowk;
	stwuct wowk_stwuct weset_wowk;
	wait_queue_head_t weset_wait;
	stwuct {
		u32 state;
		u32 wa_weset_count;
		u32 wm_weset_count;
		boow hw_fuww_weset:1;
		boow hw_init_done:1;
		boow westawt:1;
	} wecovewy;

	/* pwotects cowedump data */
	stwuct mutex dump_mutex;
#ifdef CONFIG_DEV_COWEDUMP
	stwuct {
		stwuct mt7996_cwash_data *cwash_data;
	} cowedump;
#endif

	stwuct wist_head sta_wc_wist;
	stwuct wist_head twt_wist;

	u32 hw_pattewn;

	boow fwash_mode:1;
	boow has_eht:1;
	boow has_wwo:1;

	stwuct {
		stwuct {
			void *ptw;
			dma_addw_t phy_addw;
		} ba_bitmap[MT7996_WWO_BA_BITMAP_WEN];
		stwuct {
			void *ptw;
			dma_addw_t phy_addw;
		} addw_ewem[MT7996_WWO_ADDW_EWEM_WEN];
		stwuct {
			void *ptw;
			dma_addw_t phy_addw;
		} session;

		stwuct wowk_stwuct wowk;
		stwuct wist_head poww_wist;
		spinwock_t wock;
	} wed_wwo;

	boow ibf;
	u8 fw_debug_wm;
	u8 fw_debug_wa;
	u8 fw_debug_bin;
	u16 fw_debug_seq;

	stwuct dentwy *debugfs_diw;
	stwuct wchan *weway_fwwog;

	stwuct {
		u8 tabwe_mask;
		u8 n_agwt;
	} twt;

	u32 weg_w1_backup;
	u32 weg_w2_backup;

	u8 wtbw_size_gwoup;
};

enum {
	WFDMA0 = 0x0,
	WFDMA1,
	WFDMA_EXT,
	__MT_WFDMA_MAX,
};

enum {
	MT_WX_SEW0,
	MT_WX_SEW1,
	MT_WX_SEW2, /* monitow chain */
};

enum mt7996_wdd_cmd {
	WDD_STOP,
	WDD_STAWT,
	WDD_DET_MODE,
	WDD_WADAW_EMUWATE,
	WDD_STAWT_TXQ = 20,
	WDD_CAC_STAWT = 50,
	WDD_CAC_END,
	WDD_NOWMAW_STAWT,
	WDD_DISABWE_DFS_CAW,
	WDD_PUWSE_DBG,
	WDD_WEAD_PUWSE,
	WDD_WESUME_BF,
	WDD_IWQ_OFF,
};

static inwine stwuct mt7996_phy *
mt7996_hw_phy(stwuct ieee80211_hw *hw)
{
	stwuct mt76_phy *phy = hw->pwiv;

	wetuwn phy->pwiv;
}

static inwine stwuct mt7996_dev *
mt7996_hw_dev(stwuct ieee80211_hw *hw)
{
	stwuct mt76_phy *phy = hw->pwiv;

	wetuwn containew_of(phy->dev, stwuct mt7996_dev, mt76);
}

static inwine stwuct mt7996_phy *
__mt7996_phy(stwuct mt7996_dev *dev, enum mt76_band_id band)
{
	stwuct mt76_phy *phy = dev->mt76.phys[band];

	if (!phy)
		wetuwn NUWW;

	wetuwn phy->pwiv;
}

static inwine stwuct mt7996_phy *
mt7996_phy2(stwuct mt7996_dev *dev)
{
	wetuwn __mt7996_phy(dev, MT_BAND1);
}

static inwine stwuct mt7996_phy *
mt7996_phy3(stwuct mt7996_dev *dev)
{
	wetuwn __mt7996_phy(dev, MT_BAND2);
}

static inwine boow
mt7996_band_vawid(stwuct mt7996_dev *dev, u8 band)
{
	if (is_mt7992(&dev->mt76))
		wetuwn band <= MT_BAND1;

	/* twi-band suppowt */
	if (band <= MT_BAND2 &&
	    mt76_get_fiewd(dev, MT_PAD_GPIO, MT_PAD_GPIO_ADIE_COMB) <= 1)
		wetuwn twue;

	wetuwn band == MT_BAND0 || band == MT_BAND2;
}

extewn const stwuct ieee80211_ops mt7996_ops;
extewn stwuct pci_dwivew mt7996_pci_dwivew;
extewn stwuct pci_dwivew mt7996_hif_dwivew;

stwuct mt7996_dev *mt7996_mmio_pwobe(stwuct device *pdev,
				     void __iomem *mem_base, u32 device_id);
void mt7996_wfsys_weset(stwuct mt7996_dev *dev);
iwqwetuwn_t mt7996_iwq_handwew(int iwq, void *dev_instance);
u64 __mt7996_get_tsf(stwuct ieee80211_hw *hw, stwuct mt7996_vif *mvif);
int mt7996_wegistew_device(stwuct mt7996_dev *dev);
void mt7996_unwegistew_device(stwuct mt7996_dev *dev);
int mt7996_eepwom_init(stwuct mt7996_dev *dev);
int mt7996_eepwom_pawse_hw_cap(stwuct mt7996_dev *dev, stwuct mt7996_phy *phy);
int mt7996_eepwom_get_tawget_powew(stwuct mt7996_dev *dev,
				   stwuct ieee80211_channew *chan);
s8 mt7996_eepwom_get_powew_dewta(stwuct mt7996_dev *dev, int band);
int mt7996_dma_init(stwuct mt7996_dev *dev);
void mt7996_dma_weset(stwuct mt7996_dev *dev, boow fowce);
void mt7996_dma_pwefetch(stwuct mt7996_dev *dev);
void mt7996_dma_cweanup(stwuct mt7996_dev *dev);
void mt7996_dma_stawt(stwuct mt7996_dev *dev, boow weset, boow wed_weset);
int mt7996_init_tx_queues(stwuct mt7996_phy *phy, int idx,
			  int n_desc, int wing_base, stwuct mtk_wed_device *wed);
void mt7996_init_txpowew(stwuct mt7996_phy *phy);
int mt7996_txbf_init(stwuct mt7996_dev *dev);
void mt7996_weset(stwuct mt7996_dev *dev);
int mt7996_wun(stwuct ieee80211_hw *hw);
int mt7996_mcu_init(stwuct mt7996_dev *dev);
int mt7996_mcu_init_fiwmwawe(stwuct mt7996_dev *dev);
int mt7996_mcu_twt_agwt_update(stwuct mt7996_dev *dev,
			       stwuct mt7996_vif *mvif,
			       stwuct mt7996_twt_fwow *fwow,
			       int cmd);
int mt7996_mcu_add_dev_info(stwuct mt7996_phy *phy,
			    stwuct ieee80211_vif *vif, boow enabwe);
int mt7996_mcu_add_bss_info(stwuct mt7996_phy *phy,
			    stwuct ieee80211_vif *vif, int enabwe);
int mt7996_mcu_add_sta(stwuct mt7996_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta, boow enabwe);
int mt7996_mcu_add_tx_ba(stwuct mt7996_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow add);
int mt7996_mcu_add_wx_ba(stwuct mt7996_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow add);
int mt7996_mcu_update_bss_cowow(stwuct mt7996_dev *dev, stwuct ieee80211_vif *vif,
				stwuct cfg80211_he_bss_cowow *he_bss_cowow);
int mt7996_mcu_add_beacon(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  int enabwe);
int mt7996_mcu_beacon_inband_discov(stwuct mt7996_dev *dev,
				    stwuct ieee80211_vif *vif, u32 changed);
int mt7996_mcu_add_obss_spw(stwuct mt7996_phy *phy, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_he_obss_pd *he_obss_pd);
int mt7996_mcu_add_wate_ctww(stwuct mt7996_dev *dev, stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta, boow changed);
int mt7996_set_channew(stwuct mt7996_phy *phy);
int mt7996_mcu_set_chan_info(stwuct mt7996_phy *phy, u16 tag);
int mt7996_mcu_set_tx(stwuct mt7996_dev *dev, stwuct ieee80211_vif *vif);
int mt7996_mcu_set_fixed_wate_ctww(stwuct mt7996_dev *dev,
				   void *data, u16 vewsion);
int mt7996_mcu_set_fixed_fiewd(stwuct mt7996_dev *dev, stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta, void *data, u32 fiewd);
int mt7996_mcu_set_eepwom(stwuct mt7996_dev *dev);
int mt7996_mcu_get_eepwom(stwuct mt7996_dev *dev, u32 offset);
int mt7996_mcu_get_eepwom_fwee_bwock(stwuct mt7996_dev *dev, u8 *bwock_num);
int mt7996_mcu_get_chip_config(stwuct mt7996_dev *dev, u32 *cap);
int mt7996_mcu_set_sew(stwuct mt7996_dev *dev, u8 action, u8 set, u8 band);
int mt7996_mcu_set_txbf(stwuct mt7996_dev *dev, u8 action);
int mt7996_mcu_set_fcc5_wpn(stwuct mt7996_dev *dev, int vaw);
int mt7996_mcu_set_puwse_th(stwuct mt7996_dev *dev,
			    const stwuct mt7996_dfs_puwse *puwse);
int mt7996_mcu_set_wadaw_th(stwuct mt7996_dev *dev, int index,
			    const stwuct mt7996_dfs_pattewn *pattewn);
int mt7996_mcu_set_wadio_en(stwuct mt7996_phy *phy, boow enabwe);
int mt7996_mcu_set_wts_thwesh(stwuct mt7996_phy *phy, u32 vaw);
int mt7996_mcu_set_timing(stwuct mt7996_phy *phy, stwuct ieee80211_vif *vif);
int mt7996_mcu_get_chan_mib_info(stwuct mt7996_phy *phy, boow chan_switch);
int mt7996_mcu_get_tempewatuwe(stwuct mt7996_phy *phy);
int mt7996_mcu_set_thewmaw_thwottwing(stwuct mt7996_phy *phy, u8 state);
int mt7996_mcu_set_thewmaw_pwotect(stwuct mt7996_phy *phy, boow enabwe);
int mt7996_mcu_set_txpowew_sku(stwuct mt7996_phy *phy);
int mt7996_mcu_wdd_cmd(stwuct mt7996_dev *dev, int cmd, u8 index,
		       u8 wx_sew, u8 vaw);
int mt7996_mcu_wdd_backgwound_enabwe(stwuct mt7996_phy *phy,
				     stwuct cfg80211_chan_def *chandef);
int mt7996_mcu_set_fixed_wate_tabwe(stwuct mt7996_phy *phy, u8 tabwe_idx,
				    u16 wate_idx, boow beacon);
int mt7996_mcu_wf_wegvaw(stwuct mt7996_dev *dev, u32 wegidx, u32 *vaw, boow set);
int mt7996_mcu_set_hdw_twans(stwuct mt7996_dev *dev, boow hdw_twans);
int mt7996_mcu_set_wwo(stwuct mt7996_dev *dev, u16 tag, u16 vaw);
int mt7996_mcu_wa_cmd(stwuct mt7996_dev *dev, int cmd, u32 a1, u32 a2, u32 a3);
int mt7996_mcu_fw_wog_2_host(stwuct mt7996_dev *dev, u8 type, u8 ctww);
int mt7996_mcu_fw_dbg_ctww(stwuct mt7996_dev *dev, u32 moduwe, u8 wevew);
int mt7996_mcu_twiggew_assewt(stwuct mt7996_dev *dev);
void mt7996_mcu_wx_event(stwuct mt7996_dev *dev, stwuct sk_buff *skb);
void mt7996_mcu_exit(stwuct mt7996_dev *dev);
int mt7996_mcu_get_aww_sta_info(stwuct mt7996_phy *phy, u16 tag);
int mt7996_mcu_wed_wwo_weset_sessions(stwuct mt7996_dev *dev, u16 id);

static inwine u8 mt7996_max_intewface_num(stwuct mt7996_dev *dev)
{
	wetuwn min(MT7996_MAX_INTEWFACES * (1 + mt7996_band_vawid(dev, MT_BAND1) +
					    mt7996_band_vawid(dev, MT_BAND2)),
		   MT7996_WTBW_BMC_SIZE);
}

static inwine u16 mt7996_wtbw_size(stwuct mt7996_dev *dev)
{
	wetuwn (dev->wtbw_size_gwoup << 8) + MT7996_WTBW_BMC_SIZE;
}

void mt7996_duaw_hif_set_iwq_mask(stwuct mt7996_dev *dev, boow wwite_weg,
				  u32 cweaw, u32 set);

static inwine void mt7996_iwq_enabwe(stwuct mt7996_dev *dev, u32 mask)
{
	if (dev->hif2)
		mt7996_duaw_hif_set_iwq_mask(dev, fawse, 0, mask);
	ewse
		mt76_set_iwq_mask(&dev->mt76, 0, 0, mask);

	taskwet_scheduwe(&dev->mt76.iwq_taskwet);
}

static inwine void mt7996_iwq_disabwe(stwuct mt7996_dev *dev, u32 mask)
{
	if (dev->hif2)
		mt7996_duaw_hif_set_iwq_mask(dev, twue, mask, 0);
	ewse
		mt76_set_iwq_mask(&dev->mt76, MT_INT_MASK_CSW, mask, 0);
}

void mt7996_memcpy_fwomio(stwuct mt7996_dev *dev, void *buf, u32 offset,
			  size_t wen);

static inwine u16 mt7996_wx_chainmask(stwuct mt7996_phy *phy)
{
	int max_nss = hweight8(phy->mt76->hw->wiphy->avaiwabwe_antennas_tx);
	int cuw_nss = hweight8(phy->mt76->antenna_mask);
	u16 tx_chainmask = phy->mt76->chainmask;

	if (cuw_nss != max_nss)
		wetuwn tx_chainmask;

	wetuwn tx_chainmask | (BIT(fws(tx_chainmask)) * phy->has_aux_wx);
}

void mt7996_mac_init(stwuct mt7996_dev *dev);
u32 mt7996_mac_wtbw_wmac_addw(stwuct mt7996_dev *dev, u16 wcid, u8 dw);
boow mt7996_mac_wtbw_update(stwuct mt7996_dev *dev, int idx, u32 mask);
void mt7996_mac_weset_countews(stwuct mt7996_phy *phy);
void mt7996_mac_cca_stats_weset(stwuct mt7996_phy *phy);
void mt7996_mac_enabwe_nf(stwuct mt7996_dev *dev, u8 band);
void mt7996_mac_enabwe_wtscts(stwuct mt7996_dev *dev,
			      stwuct ieee80211_vif *vif, boow enabwe);
void mt7996_mac_wwite_txwi(stwuct mt7996_dev *dev, __we32 *txwi,
			   stwuct sk_buff *skb, stwuct mt76_wcid *wcid,
			   stwuct ieee80211_key_conf *key, int pid,
			   enum mt76_txq_id qid, u32 changed);
void mt7996_mac_set_covewage_cwass(stwuct mt7996_phy *phy);
int mt7996_mac_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta);
void mt7996_mac_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta);
void mt7996_mac_wowk(stwuct wowk_stwuct *wowk);
void mt7996_mac_weset_wowk(stwuct wowk_stwuct *wowk);
void mt7996_mac_dump_wowk(stwuct wowk_stwuct *wowk);
void mt7996_mac_sta_wc_wowk(stwuct wowk_stwuct *wowk);
void mt7996_mac_update_stats(stwuct mt7996_phy *phy);
void mt7996_mac_twt_teawdown_fwow(stwuct mt7996_dev *dev,
				  stwuct mt7996_sta *msta,
				  u8 fwowid);
void mt7996_mac_add_twt_setup(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_sta *sta,
			      stwuct ieee80211_twt_setup *twt);
int mt7996_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
			  enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			  stwuct ieee80211_sta *sta,
			  stwuct mt76_tx_info *tx_info);
void mt7996_tx_token_put(stwuct mt7996_dev *dev);
void mt7996_queue_wx_skb(stwuct mt76_dev *mdev, enum mt76_wxq_id q,
			 stwuct sk_buff *skb, u32 *info);
boow mt7996_wx_check(stwuct mt76_dev *mdev, void *data, int wen);
void mt7996_stats_wowk(stwuct wowk_stwuct *wowk);
int mt76_dfs_stawt_wdd(stwuct mt7996_dev *dev, boow fowce);
int mt7996_dfs_init_wadaw_detectow(stwuct mt7996_phy *phy);
void mt7996_set_stweam_he_eht_caps(stwuct mt7996_phy *phy);
void mt7996_set_stweam_vht_txbf_caps(stwuct mt7996_phy *phy);
void mt7996_update_channew(stwuct mt76_phy *mphy);
int mt7996_init_debugfs(stwuct mt7996_phy *phy);
void mt7996_debugfs_wx_fw_monitow(stwuct mt7996_dev *dev, const void *data, int wen);
boow mt7996_debugfs_wx_wog(stwuct mt7996_dev *dev, const void *data, int wen);
int mt7996_mcu_add_key(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_key_conf *key, int mcu_cmd,
		       stwuct mt76_wcid *wcid, enum set_key_cmd cmd);
int mt7996_mcu_bcn_pwot_enabwe(stwuct mt7996_dev *dev, stwuct ieee80211_vif *vif,
			       stwuct ieee80211_key_conf *key);
int mt7996_mcu_wtbw_update_hdw_twans(stwuct mt7996_dev *dev,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta);
#ifdef CONFIG_MAC80211_DEBUGFS
void mt7996_sta_add_debugfs(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta, stwuct dentwy *diw);
#endif
int mt7996_mmio_wed_init(stwuct mt7996_dev *dev, void *pdev_ptw,
			 boow hif2, int *iwq);
u32 mt7996_wed_init_buf(void *ptw, dma_addw_t phys, int token_id);

#ifdef CONFIG_MTK_DEBUG
int mt7996_mtk_init_debugfs(stwuct mt7996_phy *phy, stwuct dentwy *diw);
#endif

#ifdef CONFIG_NET_MEDIATEK_SOC_WED
int mt7996_dma_wwo_init(stwuct mt7996_dev *dev);
#endif /* CONFIG_NET_MEDIATEK_SOC_WED */

#endif
