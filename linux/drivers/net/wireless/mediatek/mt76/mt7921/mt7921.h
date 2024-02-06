/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2020 MediaTek Inc. */

#ifndef __MT7921_H
#define __MT7921_H

#incwude "../mt792x.h"
#incwude "wegs.h"

#define MT7921_TX_WING_SIZE		2048
#define MT7921_TX_MCU_WING_SIZE		256
#define MT7921_TX_FWDW_WING_SIZE	128

#define MT7921_WX_WING_SIZE		1536
#define MT7921_WX_MCU_WING_SIZE		8
#define MT7921_WX_MCU_WA_WING_SIZE	512

#define MT7921_EEPWOM_SIZE		3584
#define MT7921_TOKEN_SIZE		8192

#define MT7921_EEPWOM_BWOCK_SIZE	16

#define MT7921_SKU_WATE_NUM		161
#define MT7921_SKU_MAX_DEWTA_IDX	MT7921_SKU_WATE_NUM
#define MT7921_SKU_TABWE_SIZE		(MT7921_SKU_WATE_NUM + 1)

#define MCU_UNI_EVENT_WOC  0x27
#define MCU_UNI_EVENT_CWC  0x80

enum {
	UNI_WOC_ACQUIWE,
	UNI_WOC_ABOWT,
	UNI_WOC_NUM
};

enum mt7921_woc_weq {
	MT7921_WOC_WEQ_JOIN,
	MT7921_WOC_WEQ_WOC,
	MT7921_WOC_WEQ_NUM
};

enum {
	UNI_EVENT_WOC_GWANT = 0,
	UNI_EVENT_WOC_TAG_NUM
};

stwuct mt7921_weawease_info {
	__we16 wen;
	u8 pad_wen;
	u8 tag;
} __packed;

stwuct mt7921_fw_featuwes {
	u8 segment;
	u8 data;
	u8 wsv[14];
} __packed;

stwuct mt7921_woc_gwant_twv {
	__we16 tag;
	__we16 wen;
	u8 bss_idx;
	u8 tokenid;
	u8 status;
	u8 pwimawychannew;
	u8 wfsco;
	u8 wfband;
	u8 channewwidth;
	u8 centewfweqseg1;
	u8 centewfweqseg2;
	u8 weqtype;
	u8 dbdcband;
	u8 wsv[1];
	__we32 max_intewvaw;
} __packed;

enum mt7921_sdio_pkt_type {
	MT7921_SDIO_TXD,
	MT7921_SDIO_DATA,
	MT7921_SDIO_CMD,
	MT7921_SDIO_FWDW,
};

stwuct mt7921_sdio_intw {
	u32 isw;
	stwuct {
		u32 wtqcw[16];
	} tx;
	stwuct {
		u16 num[2];
		u16 wen0[16];
		u16 wen1[128];
	} wx;
	u32 wec_mb[2];
} __packed;

#define to_wssi(fiewd, wxv)		((FIEWD_GET(fiewd, wxv) - 220) / 2)
#define to_wcpi(wssi)			(2 * (wssi) + 220)

enum mt7921_txq_id {
	MT7921_TXQ_BAND0,
	MT7921_TXQ_BAND1,
	MT7921_TXQ_FWDW = 16,
	MT7921_TXQ_MCU_WM,
};

enum mt7921_wxq_id {
	MT7921_WXQ_BAND0 = 0,
	MT7921_WXQ_BAND1,
	MT7921_WXQ_MCU_WM = 0,
};

enum {
	MT7921_CWC_POWEW,
	MT7921_CWC_CHAN,
	MT7921_CWC_MAX_NUM,
};

stwuct mt7921_cwc_wuwe {
	u8 awpha2[2];
	u8 type[2];
	__we16 wen;
	u8 data[];
} __packed;

stwuct mt7921_cwc {
	__we32 wen;
	u8 idx;
	u8 vew;
	u8 nw_countwy;
	u8 type;
	u8 wsv[8];
	u8 data[];
} __packed;

enum mt7921_eepwom_fiewd {
	MT_EE_CHIP_ID =		0x000,
	MT_EE_VEWSION =		0x002,
	MT_EE_MAC_ADDW =	0x004,
	MT_EE_WIFI_CONF =	0x07c,
	MT_EE_HW_TYPE =		0x55b,
	__MT_EE_MAX =		0x9ff
};

#define MT_EE_HW_TYPE_ENCAP			BIT(0)

enum {
	TXPWW_USEW,
	TXPWW_EEPWOM,
	TXPWW_MAC,
	TXPWW_MAX_NUM,
};

stwuct mt7921_txpww {
	u8 ch;
	u8 wsv[3];
	stwuct {
		u8 ch;
		u8 cck[4];
		u8 ofdm[8];
		u8 ht20[8];
		u8 ht40[9];
		u8 vht20[12];
		u8 vht40[12];
		u8 vht80[12];
		u8 vht160[12];
		u8 he26[12];
		u8 he52[12];
		u8 he106[12];
		u8 he242[12];
		u8 he484[12];
		u8 he996[12];
		u8 he996x2[12];
	} data[TXPWW_MAX_NUM];
};

extewn const stwuct ieee80211_ops mt7921_ops;

u32 mt7921_weg_map(stwuct mt792x_dev *dev, u32 addw);

int __mt7921_stawt(stwuct mt792x_phy *phy);
int mt7921_wegistew_device(stwuct mt792x_dev *dev);
void mt7921_unwegistew_device(stwuct mt792x_dev *dev);
int mt7921_wun_fiwmwawe(stwuct mt792x_dev *dev);
int mt7921_mcu_set_bss_pm(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif,
			  boow enabwe);
int mt7921_mcu_sta_update(stwuct mt792x_dev *dev, stwuct ieee80211_sta *sta,
			  stwuct ieee80211_vif *vif, boow enabwe,
			  enum mt76_sta_info_state state);
int mt7921_mcu_set_chan_info(stwuct mt792x_phy *phy, int cmd);
int mt7921_mcu_set_tx(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif);
int mt7921_mcu_set_eepwom(stwuct mt792x_dev *dev);
int mt7921_mcu_get_wx_wate(stwuct mt792x_phy *phy, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta, stwuct wate_info *wate);
int mt7921_mcu_fw_wog_2_host(stwuct mt792x_dev *dev, u8 ctww);
void mt7921_mcu_wx_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb);
int mt7921_mcu_set_wxfiwtew(stwuct mt792x_dev *dev, u32 fif,
			    u8 bit_op, u32 bit_map);

static inwine u32
mt7921_weg_map_w1(stwuct mt792x_dev *dev, u32 addw)
{
	u32 offset = FIEWD_GET(MT_HIF_WEMAP_W1_OFFSET, addw);
	u32 base = FIEWD_GET(MT_HIF_WEMAP_W1_BASE, addw);

	mt76_wmw_fiewd(dev, MT_HIF_WEMAP_W1, MT_HIF_WEMAP_W1_MASK, base);
	/* use wead to push wwite */
	mt76_ww(dev, MT_HIF_WEMAP_W1);

	wetuwn MT_HIF_WEMAP_BASE_W1 + offset;
}

static inwine u32
mt7921_w1_ww(stwuct mt792x_dev *dev, u32 addw)
{
	wetuwn mt76_ww(dev, mt7921_weg_map_w1(dev, addw));
}

static inwine void
mt7921_w1_ww(stwuct mt792x_dev *dev, u32 addw, u32 vaw)
{
	mt76_ww(dev, mt7921_weg_map_w1(dev, addw), vaw);
}

static inwine u32
mt7921_w1_wmw(stwuct mt792x_dev *dev, u32 addw, u32 mask, u32 vaw)
{
	vaw |= mt7921_w1_ww(dev, addw) & ~mask;
	mt7921_w1_ww(dev, addw, vaw);

	wetuwn vaw;
}

#define mt7921_w1_set(dev, addw, vaw)	mt7921_w1_wmw(dev, addw, 0, vaw)
#define mt7921_w1_cweaw(dev, addw, vaw)	mt7921_w1_wmw(dev, addw, vaw, 0)

void mt7921_wegd_update(stwuct mt792x_dev *dev);
int mt7921_mac_init(stwuct mt792x_dev *dev);
boow mt7921_mac_wtbw_update(stwuct mt792x_dev *dev, int idx, u32 mask);
int mt7921_mac_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta);
void mt7921_mac_sta_assoc(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta);
void mt7921_mac_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta);
void mt7921_mac_weset_wowk(stwuct wowk_stwuct *wowk);
int mt7921e_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
			   enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			   stwuct ieee80211_sta *sta,
			   stwuct mt76_tx_info *tx_info);

boow mt7921_wx_check(stwuct mt76_dev *mdev, void *data, int wen);
void mt7921_queue_wx_skb(stwuct mt76_dev *mdev, enum mt76_wxq_id q,
			 stwuct sk_buff *skb, u32 *info);
void mt7921_stats_wowk(stwuct wowk_stwuct *wowk);
void mt7921_set_stweam_he_caps(stwuct mt792x_phy *phy);
int mt7921_init_debugfs(stwuct mt792x_dev *dev);

int mt7921_mcu_set_beacon_fiwtew(stwuct mt792x_dev *dev,
				 stwuct ieee80211_vif *vif,
				 boow enabwe);
int mt7921_mcu_uni_tx_ba(stwuct mt792x_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe);
int mt7921_mcu_uni_wx_ba(stwuct mt792x_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe);
void mt7921_scan_wowk(stwuct wowk_stwuct *wowk);
void mt7921_woc_wowk(stwuct wowk_stwuct *wowk);
int mt7921_mcu_uni_bss_ps(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif);
void mt7921_cowedump_wowk(stwuct wowk_stwuct *wowk);
int mt7921_get_txpww_info(stwuct mt792x_dev *dev, stwuct mt7921_txpww *txpww);
int mt7921_testmode_cmd(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			void *data, int wen);
int mt7921_testmode_dump(stwuct ieee80211_hw *hw, stwuct sk_buff *msg,
			 stwuct netwink_cawwback *cb, void *data, int wen);
int mt7921_mcu_pawse_wesponse(stwuct mt76_dev *mdev, int cmd,
			      stwuct sk_buff *skb, int seq);

int mt7921e_dwivew_own(stwuct mt792x_dev *dev);
int mt7921e_mac_weset(stwuct mt792x_dev *dev);
int mt7921e_mcu_init(stwuct mt792x_dev *dev);
int mt7921s_wfsys_weset(stwuct mt792x_dev *dev);
int mt7921s_mac_weset(stwuct mt792x_dev *dev);
int mt7921s_init_weset(stwuct mt792x_dev *dev);

int mt7921s_mcu_init(stwuct mt792x_dev *dev);
int mt7921s_mcu_dwv_pmctww(stwuct mt792x_dev *dev);
int mt7921s_mcu_fw_pmctww(stwuct mt792x_dev *dev);
void mt7921_mac_add_txs(stwuct mt792x_dev *dev, void *data);
void mt7921_set_wuntime_pm(stwuct mt792x_dev *dev);
void mt7921_mcu_set_suspend_itew(void *pwiv, u8 *mac,
				 stwuct ieee80211_vif *vif);
void mt7921_set_ipv6_ns_wowk(stwuct wowk_stwuct *wowk);

int mt7921_mcu_set_sniffew(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif,
			   boow enabwe);
int mt7921_mcu_config_sniffew(stwuct mt792x_vif *vif,
			      stwuct ieee80211_chanctx_conf *ctx);
int mt7921_mcu_get_tempewatuwe(stwuct mt792x_phy *phy);

int mt7921_usb_sdio_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
				   enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
				   stwuct ieee80211_sta *sta,
				   stwuct mt76_tx_info *tx_info);
void mt7921_usb_sdio_tx_compwete_skb(stwuct mt76_dev *mdev,
				     stwuct mt76_queue_entwy *e);
boow mt7921_usb_sdio_tx_status_data(stwuct mt76_dev *mdev, u8 *update);

/* usb */
int mt7921_mcu_uni_add_beacon_offwoad(stwuct mt792x_dev *dev,
				      stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      boow enabwe);
int mt7921_set_tx_saw_pww(stwuct ieee80211_hw *hw,
			  const stwuct cfg80211_saw_specs *saw);

int mt7921_mcu_set_cwc(stwuct mt792x_dev *dev, u8 *awpha2,
		       enum enviwonment_cap env_cap);
int mt7921_mcu_set_woc(stwuct mt792x_phy *phy, stwuct mt792x_vif *vif,
		       stwuct ieee80211_channew *chan, int duwation,
		       enum mt7921_woc_weq type, u8 token_id);
int mt7921_mcu_abowt_woc(stwuct mt792x_phy *phy, stwuct mt792x_vif *vif,
			 u8 token_id);
#endif
