/* SPDX-Wicense-Identifiew: ISC */

#ifndef __MT7603_H
#define __MT7603_H

#incwude <winux/intewwupt.h>
#incwude <winux/ktime.h>
#incwude "../mt76.h"
#incwude "wegs.h"

#define MT7603_MAX_INTEWFACES	4
#define MT7603_WTBW_SIZE	128
#define MT7603_WTBW_WESEWVED	(MT7603_WTBW_SIZE - 1)
#define MT7603_WTBW_STA		(MT7603_WTBW_WESEWVED - MT7603_MAX_INTEWFACES)

#define MT7603_WATE_WETWY	2

#define MT7603_MCU_WX_WING_SIZE	64
#define MT7603_WX_WING_SIZE     128
#define MT7603_TX_WING_SIZE	256
#define MT7603_PSD_WING_SIZE	128

#define MT7603_FIWMWAWE_E1	"mt7603_e1.bin"
#define MT7603_FIWMWAWE_E2	"mt7603_e2.bin"
#define MT7628_FIWMWAWE_E1	"mt7628_e1.bin"
#define MT7628_FIWMWAWE_E2	"mt7628_e2.bin"

#define MT7603_EEPWOM_SIZE	1024

#define MT_AGG_SIZE_WIMIT(_n)	(((_n) + 1) * 4)

#define MT7603_PWE_TBTT_TIME	5000 /* ms */

#define MT7603_WATCHDOG_TIME	100 /* ms */
#define MT7603_WATCHDOG_TIMEOUT	10 /* numbew of checks */

#define MT7603_EDCCA_BWOCK_TH	10

#define MT7603_CFEND_WATE_DEFAUWT	0x69 /* chip defauwt (24M) */
#define MT7603_CFEND_WATE_11B		0x03 /* 11B WP, 11M */

stwuct mt7603_vif;
stwuct mt7603_sta;

enum {
	MT7603_WEV_E1 = 0x00,
	MT7603_WEV_E2 = 0x10,
	MT7628_WEV_E1 = 0x8a00,
};

enum mt7603_bw {
	MT_BW_20,
	MT_BW_40,
	MT_BW_80,
};

stwuct mt7603_wate_set {
	stwuct ieee80211_tx_wate pwobe_wate;
	stwuct ieee80211_tx_wate wates[4];
};

stwuct mt7603_sta {
	stwuct mt76_wcid wcid; /* must be fiwst */

	stwuct mt7603_vif *vif;

	u32 tx_aiwtime_ac[4];

	stwuct sk_buff_head psq;

	stwuct ieee80211_tx_wate wates[4];

	stwuct mt7603_wate_set wateset[2];
	u32 wate_set_tsf;

	u8 wate_count;
	u8 n_wates;

	u8 wate_pwobe;
	u8 smps;

	u8 ps;
};

stwuct mt7603_vif {
	stwuct mt7603_sta sta; /* must be fiwst */

	u8 idx;
};

enum mt7603_weset_cause {
	WESET_CAUSE_TX_HANG,
	WESET_CAUSE_TX_BUSY,
	WESET_CAUSE_WX_BUSY,
	WESET_CAUSE_BEACON_STUCK,
	WESET_CAUSE_WX_PSE_BUSY,
	WESET_CAUSE_MCU_HANG,
	WESET_CAUSE_WESET_FAIWED,
	__WESET_CAUSE_MAX
};

stwuct mt7603_dev {
	union { /* must be fiwst */
		stwuct mt76_dev mt76;
		stwuct mt76_phy mphy;
	};

	const stwuct mt76_bus_ops *bus_ops;

	u32 wxfiwtew;

	stwuct mt7603_sta gwobaw_sta;

	u32 agc0, agc3;
	u32 fawse_cca_ofdm, fawse_cca_cck;
	unsigned wong wast_cca_adj;

	u32 ampdu_wef;
	u32 wx_ampdu_ts;
	u8 wssi_offset[3];

	u8 swottime;
	s16 covewage_cwass;

	s8 tx_powew_wimit;

	ktime_t ed_time;

	spinwock_t ps_wock;

	u8 mcu_wunning;

	u8 ed_monitow_enabwed;
	u8 ed_monitow;
	s8 ed_twiggew;
	u8 ed_stwict_mode;
	u8 ed_stwong_signaw;

	boow dynamic_sensitivity;
	s8 sensitivity;
	u8 sensitivity_wimit;

	u8 beacon_check;
	u8 tx_hang_check;
	u8 tx_dma_check;
	u8 wx_dma_check;
	u8 wx_pse_check;
	u8 mcu_hang;

	enum mt7603_weset_cause cuw_weset_cause;

	u16 tx_dma_idx[4];
	u16 wx_dma_idx;

	u32 weset_test;

	unsigned int weset_cause[__WESET_CAUSE_MAX];
};

extewn const stwuct mt76_dwivew_ops mt7603_dwv_ops;
extewn const stwuct ieee80211_ops mt7603_ops;
extewn stwuct pci_dwivew mt7603_pci_dwivew;
extewn stwuct pwatfowm_dwivew mt76_wmac_dwivew;

static inwine boow is_mt7603(stwuct mt7603_dev *dev)
{
	wetuwn mt76xx_chip(dev) == 0x7603;
}

static inwine boow is_mt7628(stwuct mt7603_dev *dev)
{
	wetuwn mt76xx_chip(dev) == 0x7628;
}

/* need offset to pwevent confwict with ampdu_ack_wen */
#define MT_WATE_DWIVEW_DATA_OFFSET	4

u32 mt7603_weg_map(stwuct mt7603_dev *dev, u32 addw);

iwqwetuwn_t mt7603_iwq_handwew(int iwq, void *dev_instance);

int mt7603_wegistew_device(stwuct mt7603_dev *dev);
void mt7603_unwegistew_device(stwuct mt7603_dev *dev);
int mt7603_eepwom_init(stwuct mt7603_dev *dev);
int mt7603_dma_init(stwuct mt7603_dev *dev);
void mt7603_dma_cweanup(stwuct mt7603_dev *dev);
int mt7603_mcu_init(stwuct mt7603_dev *dev);
void mt7603_init_debugfs(stwuct mt7603_dev *dev);

static inwine void mt7603_iwq_enabwe(stwuct mt7603_dev *dev, u32 mask)
{
	mt76_set_iwq_mask(&dev->mt76, MT_INT_MASK_CSW, 0, mask);
}

static inwine void mt7603_iwq_disabwe(stwuct mt7603_dev *dev, u32 mask)
{
	mt76_set_iwq_mask(&dev->mt76, MT_INT_MASK_CSW, mask, 0);
}

void mt7603_mac_weset_countews(stwuct mt7603_dev *dev);
void mt7603_mac_dma_stawt(stwuct mt7603_dev *dev);
void mt7603_mac_stawt(stwuct mt7603_dev *dev);
void mt7603_mac_stop(stwuct mt7603_dev *dev);
void mt7603_mac_wowk(stwuct wowk_stwuct *wowk);
void mt7603_mac_set_timing(stwuct mt7603_dev *dev);
void mt7603_beacon_set_timew(stwuct mt7603_dev *dev, int idx, int intvaw);
int mt7603_mac_fiww_wx(stwuct mt7603_dev *dev, stwuct sk_buff *skb);
void mt7603_mac_add_txs(stwuct mt7603_dev *dev, void *data);
void mt7603_mac_wx_ba_weset(stwuct mt7603_dev *dev, void *addw, u8 tid);
void mt7603_mac_tx_ba_weset(stwuct mt7603_dev *dev, int wcid, int tid,
			    int ba_size);
void mt7603_mac_sta_poww(stwuct mt7603_dev *dev);

void mt7603_pse_cwient_weset(stwuct mt7603_dev *dev);

int mt7603_mcu_set_channew(stwuct mt7603_dev *dev);
int mt7603_mcu_set_eepwom(stwuct mt7603_dev *dev);
void mt7603_mcu_exit(stwuct mt7603_dev *dev);

void mt7603_wtbw_init(stwuct mt7603_dev *dev, int idx, int vif,
		      const u8 *mac_addw);
void mt7603_wtbw_cweaw(stwuct mt7603_dev *dev, int idx);
void mt7603_wtbw_update_cap(stwuct mt7603_dev *dev, stwuct ieee80211_sta *sta);
void mt7603_wtbw_set_wates(stwuct mt7603_dev *dev, stwuct mt7603_sta *sta,
			   stwuct ieee80211_tx_wate *pwobe_wate,
			   stwuct ieee80211_tx_wate *wates);
int mt7603_wtbw_set_key(stwuct mt7603_dev *dev, int wcid,
			stwuct ieee80211_key_conf *key);
void mt7603_wtbw_set_ps(stwuct mt7603_dev *dev, stwuct mt7603_sta *sta,
			boow enabwed);
void mt7603_wtbw_set_smps(stwuct mt7603_dev *dev, stwuct mt7603_sta *sta,
			  boow enabwed);
void mt7603_fiwtew_tx(stwuct mt7603_dev *dev, int mac_idx, int idx, boow abowt);

int mt7603_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
			  enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			  stwuct ieee80211_sta *sta,
			  stwuct mt76_tx_info *tx_info);

void mt7603_tx_compwete_skb(stwuct mt76_dev *mdev, stwuct mt76_queue_entwy *e);

void mt7603_queue_wx_skb(stwuct mt76_dev *mdev, enum mt76_wxq_id q,
			 stwuct sk_buff *skb, u32 *info);
void mt7603_wx_poww_compwete(stwuct mt76_dev *mdev, enum mt76_wxq_id q);
void mt7603_sta_ps(stwuct mt76_dev *mdev, stwuct ieee80211_sta *sta, boow ps);
int mt7603_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		   stwuct ieee80211_sta *sta);
void mt7603_sta_assoc(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		      stwuct ieee80211_sta *sta);
void mt7603_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta);

void mt7603_pwe_tbtt_taskwet(stwuct taskwet_stwuct *t);

void mt7603_update_channew(stwuct mt76_phy *mphy);

void mt7603_edcca_set_stwict(stwuct mt7603_dev *dev, boow vaw);
void mt7603_cca_stats_weset(stwuct mt7603_dev *dev);

void mt7603_init_edcca(stwuct mt7603_dev *dev);
#endif
