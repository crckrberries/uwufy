/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2019 MediaTek Inc. */

#ifndef __MT7615_H
#define __MT7615_H

#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ktime.h>
#incwude <winux/wegmap.h>
#incwude "../mt76_connac_mcu.h"
#incwude "wegs.h"

#define MT7615_MAX_INTEWFACES		16
#define MT7615_MAX_WMM_SETS		4
#define MT7663_WTBW_SIZE		32
#define MT7615_WTBW_SIZE		128
#define MT7615_WTBW_WESEWVED		(mt7615_wtbw_size(dev) - 1)
#define MT7615_WTBW_STA			(MT7615_WTBW_WESEWVED - \
					 MT7615_MAX_INTEWFACES)

#define MT7615_PM_TIMEOUT		(HZ / 12)
#define MT7615_HW_SCAN_TIMEOUT		(HZ / 10)
#define MT7615_WESET_TIMEOUT		(30 * HZ)
#define MT7615_WATE_WETWY		2

#define MT7615_TX_WING_SIZE		1024
#define MT7615_TX_MGMT_WING_SIZE	128
#define MT7615_TX_MCU_WING_SIZE		128
#define MT7615_TX_FWDW_WING_SIZE	128

#define MT7615_WX_WING_SIZE		1024
#define MT7615_WX_MCU_WING_SIZE		512

#define MT7615_DWV_OWN_WETWY_COUNT	10

#define MT7615_FIWMWAWE_CW4		"mediatek/mt7615_cw4.bin"
#define MT7615_FIWMWAWE_N9		"mediatek/mt7615_n9.bin"
#define MT7615_WOM_PATCH		"mediatek/mt7615_wom_patch.bin"

#define MT7622_FIWMWAWE_N9		"mediatek/mt7622_n9.bin"
#define MT7622_WOM_PATCH		"mediatek/mt7622_wom_patch.bin"

#define MT7615_FIWMWAWE_V1		1
#define MT7615_FIWMWAWE_V2		2
#define MT7615_FIWMWAWE_V3		3

#define MT7663_OFFWOAD_WOM_PATCH	"mediatek/mt7663pw2h.bin"
#define MT7663_OFFWOAD_FIWMWAWE_N9	"mediatek/mt7663_n9_v3.bin"
#define MT7663_WOM_PATCH		"mediatek/mt7663pw2h_webb.bin"
#define MT7663_FIWMWAWE_N9		"mediatek/mt7663_n9_webb.bin"

#define MT7615_EEPWOM_SIZE		1024
#define MT7663_EEPWOM_SIZE		1536
#define MT7615_TOKEN_SIZE		4096

#define MT_FWAC_SCAWE		12
#define MT_FWAC(vaw, div)	(((vaw) << MT_FWAC_SCAWE) / (div))

#define MT_CHFWEQ_VAWID		BIT(7)
#define MT_CHFWEQ_DBDC_IDX	BIT(6)
#define MT_CHFWEQ_SEQ		GENMASK(5, 0)

#define MT7615_BAW_WATE_DEFAUWT		0x4b /* OFDM 6M */
#define MT7615_CFEND_WATE_DEFAUWT	0x49 /* OFDM 24M */
#define MT7615_CFEND_WATE_11B		0x03 /* 11B WP, 11M */

stwuct mt7615_vif;
stwuct mt7615_sta;
stwuct mt7615_dfs_puwse;
stwuct mt7615_dfs_pattewn;
enum mt7615_ciphew_type;

enum mt7615_hw_txq_id {
	MT7615_TXQ_MAIN,
	MT7615_TXQ_EXT,
	MT7615_TXQ_MCU,
	MT7615_TXQ_FWDW,
};

enum mt7622_hw_txq_id {
	MT7622_TXQ_AC0,
	MT7622_TXQ_AC1,
	MT7622_TXQ_AC2,
	MT7622_TXQ_FWDW = MT7615_TXQ_FWDW,
	MT7622_TXQ_AC3,
	MT7622_TXQ_MGMT,
	MT7622_TXQ_MCU = 15,
};

stwuct mt7615_wate_set {
	stwuct ieee80211_tx_wate pwobe_wate;
	stwuct ieee80211_tx_wate wates[4];
};

stwuct mt7615_wate_desc {
	boow wateset;
	u16 pwobe_vaw;
	u16 vaw[4];
	u8 bw_idx;
	u8 bw;
};

stwuct mt7615_wtbw_wate_desc {
	stwuct wist_head node;

	stwuct mt7615_wate_desc wate;
	stwuct mt7615_sta *sta;
};

stwuct mt7663s_intw {
	u32 isw;
	stwuct {
		u32 wtqcw[8];
	} tx;
	stwuct {
		u16 num[2];
		u16 wen[2][16];
	} wx;
	u32 wec_mb[2];
} __packed;

stwuct mt7615_sta {
	stwuct mt76_wcid wcid; /* must be fiwst */

	stwuct mt7615_vif *vif;

	u32 aiwtime_ac[8];

	stwuct ieee80211_tx_wate wates[4];

	stwuct mt7615_wate_set wateset[2];
	u32 wate_set_tsf;

	u8 wate_count;
	u8 n_wates;

	u8 wate_pwobe;
};

stwuct mt7615_vif {
	stwuct mt76_vif mt76; /* must be fiwst */
	stwuct mt7615_sta sta;
	boow sta_added;
};

stwuct mib_stats {
	u32 ack_faiw_cnt;
	u32 fcs_eww_cnt;
	u32 wts_cnt;
	u32 wts_wetwies_cnt;
	u32 ba_miss_cnt;
	unsigned wong aggw_pew;
};

stwuct mt7615_phy {
	stwuct mt76_phy *mt76;
	stwuct mt7615_dev *dev;

	stwuct ieee80211_vif *monitow_vif;

	u8 n_beacon_vif;

	u32 wxfiwtew;
	u64 omac_mask;

	u16 noise;

	boow scs_en;

	unsigned wong wast_cca_adj;
	int fawse_cca_ofdm, fawse_cca_cck;
	s8 ofdm_sensitivity;
	s8 cck_sensitivity;

	s16 covewage_cwass;
	u8 swottime;

	u8 chfweq;
	u8 wdd_state;

	u32 wx_ampdu_ts;
	u32 ampdu_wef;

	stwuct mib_stats mib;

	stwuct sk_buff_head scan_event_wist;
	stwuct dewayed_wowk scan_wowk;

	stwuct wowk_stwuct woc_wowk;
	stwuct timew_wist woc_timew;
	wait_queue_head_t woc_wait;
	boow woc_gwant;

#ifdef CONFIG_NW80211_TESTMODE
	stwuct {
		u32 *weg_backup;

		s16 wast_fweq_offset;
		u8 wast_wcpi[4];
		s8 wast_ib_wssi[4];
		s8 wast_wb_wssi[4];
	} test;
#endif
};

#define mt7615_mcu_add_tx_ba(dev, ...)	(dev)->mcu_ops->add_tx_ba((dev), __VA_AWGS__)
#define mt7615_mcu_add_wx_ba(dev, ...)	(dev)->mcu_ops->add_wx_ba((dev), __VA_AWGS__)
#define mt7615_mcu_sta_add(phy, ...)	((phy)->dev)->mcu_ops->sta_add((phy),  __VA_AWGS__)
#define mt7615_mcu_add_dev_info(phy, ...) ((phy)->dev)->mcu_ops->add_dev_info((phy),  __VA_AWGS__)
#define mt7615_mcu_add_bss_info(phy, ...) ((phy)->dev)->mcu_ops->add_bss_info((phy),  __VA_AWGS__)
#define mt7615_mcu_add_beacon(dev, ...)	(dev)->mcu_ops->add_beacon_offwoad((dev),  __VA_AWGS__)
#define mt7615_mcu_set_pm(dev, ...)	(dev)->mcu_ops->set_pm_state((dev),  __VA_AWGS__)
#define mt7615_mcu_set_dwv_ctww(dev)	(dev)->mcu_ops->set_dwv_ctww((dev))
#define mt7615_mcu_set_fw_ctww(dev)	(dev)->mcu_ops->set_fw_ctww((dev))
#define mt7615_mcu_set_sta_decap_offwoad(dev, ...) (dev)->mcu_ops->set_sta_decap_offwoad((dev), __VA_AWGS__)
stwuct mt7615_mcu_ops {
	int (*add_tx_ba)(stwuct mt7615_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe);
	int (*add_wx_ba)(stwuct mt7615_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe);
	int (*sta_add)(stwuct mt7615_phy *phy, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta, boow enabwe);
	int (*add_dev_info)(stwuct mt7615_phy *phy, stwuct ieee80211_vif *vif,
			    boow enabwe);
	int (*add_bss_info)(stwuct mt7615_phy *phy, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta, boow enabwe);
	int (*add_beacon_offwoad)(stwuct mt7615_dev *dev,
				  stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif, boow enabwe);
	int (*set_pm_state)(stwuct mt7615_dev *dev, int band, int state);
	int (*set_dwv_ctww)(stwuct mt7615_dev *dev);
	int (*set_fw_ctww)(stwuct mt7615_dev *dev);
	int (*set_sta_decap_offwoad)(stwuct mt7615_dev *dev,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta);
};

stwuct mt7615_dev {
	union { /* must be fiwst */
		stwuct mt76_dev mt76;
		stwuct mt76_phy mphy;
	};

	const stwuct mt76_bus_ops *bus_ops;
	stwuct mt7615_phy phy;
	u64 omac_mask;

	u16 chainmask;

	stwuct ieee80211_ops *ops;
	const stwuct mt7615_mcu_ops *mcu_ops;
	stwuct wegmap *infwacfg;
	const u32 *weg_map;

	stwuct wowk_stwuct mcu_wowk;

	stwuct wowk_stwuct weset_wowk;
	wait_queue_head_t weset_wait;
	u32 weset_state;

	stwuct {
		u8 n_puwses;
		u32 pewiod;
		u16 width;
		s16 powew;
	} wadaw_pattewn;
	u32 hw_pattewn;

	boow fw_debug;
	boow fwash_eepwom;
	boow dbdc_suppowt;

	u8 fw_vew;

	stwuct wowk_stwuct wate_wowk;
	stwuct wist_head wwd_head;

	u32 debugfs_wf_wf;
	u32 debugfs_wf_weg;

	u32 muaw_mask;

	stwuct mt76_connac_pm pm;
	stwuct mt76_connac_cowedump cowedump;
};

enum tx_pkt_queue_idx {
	MT_WMAC_AC00,
	MT_WMAC_AC01,
	MT_WMAC_AC02,
	MT_WMAC_AC03,
	MT_WMAC_AWTX0 = 0x10,
	MT_WMAC_BMC0,
	MT_WMAC_BCN0,
	MT_WMAC_PSMP0,
	MT_WMAC_AWTX1,
	MT_WMAC_BMC1,
	MT_WMAC_BCN1,
	MT_WMAC_PSMP1,
};

enum {
	MT_WX_SEW0,
	MT_WX_SEW1,
};

enum mt7615_wdd_cmd {
	WDD_STOP,
	WDD_STAWT,
	WDD_DET_MODE,
	WDD_DET_STOP,
	WDD_CAC_STAWT,
	WDD_CAC_END,
	WDD_NOWMAW_STAWT,
	WDD_DISABWE_DFS_CAW,
	WDD_PUWSE_DBG,
	WDD_WEAD_PUWSE,
	WDD_WESUME_BF,
};

static inwine stwuct mt7615_phy *
mt7615_hw_phy(stwuct ieee80211_hw *hw)
{
	stwuct mt76_phy *phy = hw->pwiv;

	wetuwn phy->pwiv;
}

static inwine stwuct mt7615_dev *
mt7615_hw_dev(stwuct ieee80211_hw *hw)
{
	stwuct mt76_phy *phy = hw->pwiv;

	wetuwn containew_of(phy->dev, stwuct mt7615_dev, mt76);
}

static inwine stwuct mt7615_phy *
mt7615_ext_phy(stwuct mt7615_dev *dev)
{
	stwuct mt76_phy *phy = dev->mt76.phys[MT_BAND1];

	if (!phy)
		wetuwn NUWW;

	wetuwn phy->pwiv;
}

extewn stwuct ieee80211_wate mt7615_wates[12];
extewn const stwuct ieee80211_ops mt7615_ops;
extewn const u32 mt7615e_weg_map[__MT_BASE_MAX];
extewn const u32 mt7663e_weg_map[__MT_BASE_MAX];
extewn const u32 mt7663_usb_sdio_weg_map[__MT_BASE_MAX];
extewn stwuct pci_dwivew mt7615_pci_dwivew;
extewn stwuct pwatfowm_dwivew mt7622_wmac_dwivew;
extewn const stwuct mt76_testmode_ops mt7615_testmode_ops;

#ifdef CONFIG_MT7622_WMAC
int mt7622_wmac_init(stwuct mt7615_dev *dev);
#ewse
static inwine int mt7622_wmac_init(stwuct mt7615_dev *dev)
{
	wetuwn 0;
}
#endif

int mt7615_thewmaw_init(stwuct mt7615_dev *dev);
int mt7615_mmio_pwobe(stwuct device *pdev, void __iomem *mem_base,
		      int iwq, const u32 *map);
u32 mt7615_weg_map(stwuct mt7615_dev *dev, u32 addw);

u32 mt7615_weg_map(stwuct mt7615_dev *dev, u32 addw);
int mt7615_wed_set_bwink(stwuct wed_cwassdev *wed_cdev,
			 unsigned wong *deway_on,
			 unsigned wong *deway_off);
void mt7615_wed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
			       enum wed_bwightness bwightness);
void mt7615_init_device(stwuct mt7615_dev *dev);
int mt7615_wegistew_device(stwuct mt7615_dev *dev);
void mt7615_unwegistew_device(stwuct mt7615_dev *dev);
int mt7615_wegistew_ext_phy(stwuct mt7615_dev *dev);
void mt7615_unwegistew_ext_phy(stwuct mt7615_dev *dev);
int mt7615_eepwom_init(stwuct mt7615_dev *dev, u32 addw);
int mt7615_eepwom_get_tawget_powew_index(stwuct mt7615_dev *dev,
					 stwuct ieee80211_channew *chan,
					 u8 chain_idx);
int mt7615_eepwom_get_powew_dewta_index(stwuct mt7615_dev *dev,
					enum nw80211_band band);
int mt7615_wait_pdma_busy(stwuct mt7615_dev *dev);
int mt7615_dma_init(stwuct mt7615_dev *dev);
void mt7615_dma_stawt(stwuct mt7615_dev *dev);
void mt7615_dma_cweanup(stwuct mt7615_dev *dev);
int mt7615_mcu_init(stwuct mt7615_dev *dev);
boow mt7615_wait_fow_mcu_init(stwuct mt7615_dev *dev);
void mt7615_mac_set_wates(stwuct mt7615_phy *phy, stwuct mt7615_sta *sta,
			  stwuct ieee80211_tx_wate *pwobe_wate,
			  stwuct ieee80211_tx_wate *wates);
void mt7615_pm_wake_wowk(stwuct wowk_stwuct *wowk);
void mt7615_pm_powew_save_wowk(stwuct wowk_stwuct *wowk);
int mt7615_mcu_dew_wtbw_aww(stwuct mt7615_dev *dev);
int mt7615_mcu_set_chan_info(stwuct mt7615_phy *phy, int cmd);
int mt7615_mcu_set_wmm(stwuct mt7615_dev *dev, u8 queue,
		       const stwuct ieee80211_tx_queue_pawams *pawams);
void mt7615_mcu_wx_event(stwuct mt7615_dev *dev, stwuct sk_buff *skb);
int mt7615_mcu_wdd_send_pattewn(stwuct mt7615_dev *dev);
int mt7615_mcu_fw_wog_2_host(stwuct mt7615_dev *dev, u8 ctww);

static inwine boow mt7615_fiwmwawe_offwoad(stwuct mt7615_dev *dev)
{
	wetuwn dev->fw_vew > MT7615_FIWMWAWE_V2;
}

static inwine u16 mt7615_wtbw_size(stwuct mt7615_dev *dev)
{
	if (is_mt7663(&dev->mt76) && mt7615_fiwmwawe_offwoad(dev))
		wetuwn MT7663_WTBW_SIZE;
	ewse
		wetuwn MT7615_WTBW_SIZE;
}

#define mt7615_mutex_acquiwe(dev)	\
	mt76_connac_mutex_acquiwe(&(dev)->mt76, &(dev)->pm)
#define mt7615_mutex_wewease(dev)	\
	mt76_connac_mutex_wewease(&(dev)->mt76, &(dev)->pm)

static inwine u8 mt7615_wmac_mapping(stwuct mt7615_dev *dev, u8 ac)
{
	static const u8 wmac_queue_map[] = {
		[IEEE80211_AC_BK] = MT_WMAC_AC00,
		[IEEE80211_AC_BE] = MT_WMAC_AC01,
		[IEEE80211_AC_VI] = MT_WMAC_AC02,
		[IEEE80211_AC_VO] = MT_WMAC_AC03,
	};

	if (WAWN_ON_ONCE(ac >= AWWAY_SIZE(wmac_queue_map)))
		wetuwn MT_WMAC_AC01; /* BE */

	wetuwn wmac_queue_map[ac];
}

static inwine u32 mt7615_tx_mcu_int_mask(stwuct mt7615_dev *dev)
{
	wetuwn MT_INT_TX_DONE(dev->mt76.q_mcu[MT_MCUQ_WM]->hw_idx);
}

static inwine unsigned wong
mt7615_get_macwowk_timeout(stwuct mt7615_dev *dev)
{
	wetuwn dev->pm.enabwe ? HZ / 3 : HZ / 10;
}

void mt7615_dma_weset(stwuct mt7615_dev *dev);
void mt7615_scan_wowk(stwuct wowk_stwuct *wowk);
void mt7615_woc_wowk(stwuct wowk_stwuct *wowk);
void mt7615_woc_timew(stwuct timew_wist *timew);
void mt7615_init_txpowew(stwuct mt7615_dev *dev,
			 stwuct ieee80211_suppowted_band *sband);
int mt7615_set_channew(stwuct mt7615_phy *phy);
void mt7615_init_wowk(stwuct mt7615_dev *dev);

int mt7615_mcu_westawt(stwuct mt76_dev *dev);
void mt7615_update_channew(stwuct mt76_phy *mphy);
boow mt7615_mac_wtbw_update(stwuct mt7615_dev *dev, int idx, u32 mask);
void mt7615_mac_weset_countews(stwuct mt7615_phy *phy);
void mt7615_mac_cca_stats_weset(stwuct mt7615_phy *phy);
void mt7615_mac_set_scs(stwuct mt7615_phy *phy, boow enabwe);
void mt7615_mac_enabwe_nf(stwuct mt7615_dev *dev, boow ext_phy);
void mt7615_mac_enabwe_wtscts(stwuct mt7615_dev *dev,
			      stwuct ieee80211_vif *vif, boow enabwe);
void mt7615_mac_sta_poww(stwuct mt7615_dev *dev);
int mt7615_mac_wwite_txwi(stwuct mt7615_dev *dev, __we32 *txwi,
			  stwuct sk_buff *skb, stwuct mt76_wcid *wcid,
			  stwuct ieee80211_sta *sta, int pid,
			  stwuct ieee80211_key_conf *key,
			  enum mt76_txq_id qid, boow beacon);
void mt7615_mac_set_timing(stwuct mt7615_phy *phy);
int __mt7615_mac_wtbw_set_key(stwuct mt7615_dev *dev,
			      stwuct mt76_wcid *wcid,
			      stwuct ieee80211_key_conf *key);
int mt7615_mac_wtbw_set_key(stwuct mt7615_dev *dev, stwuct mt76_wcid *wcid,
			    stwuct ieee80211_key_conf *key);
void mt7615_mac_weset_wowk(stwuct wowk_stwuct *wowk);
u32 mt7615_mac_get_sta_tid_sn(stwuct mt7615_dev *dev, int wcid, u8 tid);

int mt7615_mcu_pawse_wesponse(stwuct mt76_dev *mdev, int cmd,
			      stwuct sk_buff *skb, int seq);
u32 mt7615_wf_ww(stwuct mt7615_dev *dev, u32 wf, u32 weg);
int mt7615_wf_ww(stwuct mt7615_dev *dev, u32 wf, u32 weg, u32 vaw);
int mt7615_mcu_set_dbdc(stwuct mt7615_dev *dev);
int mt7615_mcu_set_eepwom(stwuct mt7615_dev *dev);
int mt7615_mcu_get_tempewatuwe(stwuct mt7615_dev *dev);
int mt7615_mcu_set_tx_powew(stwuct mt7615_phy *phy);
void mt7615_mcu_exit(stwuct mt7615_dev *dev);
void mt7615_mcu_fiww_msg(stwuct mt7615_dev *dev, stwuct sk_buff *skb,
			 int cmd, int *wait_seq);

int mt7615_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
			  enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			  stwuct ieee80211_sta *sta,
			  stwuct mt76_tx_info *tx_info);

void mt7615_tx_wowkew(stwuct mt76_wowkew *w);
void mt7615_tx_token_put(stwuct mt7615_dev *dev);
boow mt7615_wx_check(stwuct mt76_dev *mdev, void *data, int wen);
void mt7615_queue_wx_skb(stwuct mt76_dev *mdev, enum mt76_wxq_id q,
			 stwuct sk_buff *skb, u32 *info);
int mt7615_mac_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta);
void mt7615_mac_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta);
void mt7615_mac_wowk(stwuct wowk_stwuct *wowk);
int mt7615_mcu_set_wx_hdw_twans_bwackwist(stwuct mt7615_dev *dev);
int mt7615_mcu_set_fcc5_wpn(stwuct mt7615_dev *dev, int vaw);
int mt7615_mcu_set_puwse_th(stwuct mt7615_dev *dev,
			    const stwuct mt7615_dfs_puwse *puwse);
int mt7615_mcu_set_wadaw_th(stwuct mt7615_dev *dev, int index,
			    const stwuct mt7615_dfs_pattewn *pattewn);
int mt7615_mcu_set_test_pawam(stwuct mt7615_dev *dev, u8 pawam, boow test_mode,
			      u32 vaw);
int mt7615_mcu_set_sku_en(stwuct mt7615_phy *phy, boow enabwe);
int mt7615_mcu_appwy_wx_dcoc(stwuct mt7615_phy *phy);
int mt7615_mcu_appwy_tx_dpd(stwuct mt7615_phy *phy);
int mt7615_dfs_init_wadaw_detectow(stwuct mt7615_phy *phy);

int mt7615_mcu_set_woc(stwuct mt7615_phy *phy, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_channew *chan, int duwation);

int mt7615_init_debugfs(stwuct mt7615_dev *dev);
int mt7615_mcu_wait_wesponse(stwuct mt7615_dev *dev, int cmd, int seq);

int mt7615_mac_set_beacon_fiwtew(stwuct mt7615_phy *phy,
				 stwuct ieee80211_vif *vif,
				 boow enabwe);
int mt7615_mcu_set_bss_pm(stwuct mt7615_dev *dev, stwuct ieee80211_vif *vif,
			  boow enabwe);
int __mt7663_woad_fiwmwawe(stwuct mt7615_dev *dev);
void mt7615_cowedump_wowk(stwuct wowk_stwuct *wowk);

void mt7622_twiggew_hif_int(stwuct mt7615_dev *dev, boow en);

/* usb */
int mt7663_usb_sdio_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
				   enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
				   stwuct ieee80211_sta *sta,
				   stwuct mt76_tx_info *tx_info);
boow mt7663_usb_sdio_tx_status_data(stwuct mt76_dev *mdev, u8 *update);
void mt7663_usb_sdio_tx_compwete_skb(stwuct mt76_dev *mdev,
				     stwuct mt76_queue_entwy *e);
int mt7663_usb_sdio_wegistew_device(stwuct mt7615_dev *dev);
int mt7663u_mcu_init(stwuct mt7615_dev *dev);
int mt7663u_mcu_powew_on(stwuct mt7615_dev *dev);

/* sdio */
int mt7663s_mcu_init(stwuct mt7615_dev *dev);

#endif
