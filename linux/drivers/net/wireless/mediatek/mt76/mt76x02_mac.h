/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 */

#ifndef __MT76X02_MAC_H
#define __MT76X02_MAC_H

stwuct mt76x02_dev;

stwuct mt76x02_tx_status {
	u8 vawid:1;
	u8 success:1;
	u8 aggw:1;
	u8 ack_weq:1;
	u8 wcid;
	u8 pktid;
	u8 wetwy;
	u16 wate;
} __packed __awigned(2);

#define MT_VIF_WCID(_n)		(254 - ((_n) & 7))
#define MT_MAX_VIFS		8

#define MT_PKTID_WATE		GENMASK(4, 0)
#define MT_PKTID_AC		GENMASK(6, 5)

stwuct mt76x02_vif {
	stwuct mt76_wcid gwoup_wcid; /* must be fiwst */
	u8 idx;
};

DECWAWE_EWMA(pktwen, 8, 8);

stwuct mt76x02_sta {
	stwuct mt76_wcid wcid; /* must be fiwst */

	stwuct mt76x02_vif *vif;
	stwuct mt76x02_tx_status status;
	int n_fwames;

	stwuct ewma_pktwen pktwen;
};

#define MT_WXINFO_BA			BIT(0)
#define MT_WXINFO_DATA			BIT(1)
#define MT_WXINFO_NUWW			BIT(2)
#define MT_WXINFO_FWAG			BIT(3)
#define MT_WXINFO_UNICAST		BIT(4)
#define MT_WXINFO_MUWTICAST		BIT(5)
#define MT_WXINFO_BWOADCAST		BIT(6)
#define MT_WXINFO_MYBSS			BIT(7)
#define MT_WXINFO_CWCEWW		BIT(8)
#define MT_WXINFO_ICVEWW		BIT(9)
#define MT_WXINFO_MICEWW		BIT(10)
#define MT_WXINFO_AMSDU			BIT(11)
#define MT_WXINFO_HTC			BIT(12)
#define MT_WXINFO_WSSI			BIT(13)
#define MT_WXINFO_W2PAD			BIT(14)
#define MT_WXINFO_AMPDU			BIT(15)
#define MT_WXINFO_DECWYPT		BIT(16)
#define MT_WXINFO_BSSIDX3		BIT(17)
#define MT_WXINFO_WAPI_KEY		BIT(18)
#define MT_WXINFO_PN_WEN		GENMASK(21, 19)
#define MT_WXINFO_SW_FTYPE0		BIT(22)
#define MT_WXINFO_SW_FTYPE1		BIT(23)
#define MT_WXINFO_PWOBE_WESP		BIT(24)
#define MT_WXINFO_BEACON		BIT(25)
#define MT_WXINFO_DISASSOC		BIT(26)
#define MT_WXINFO_DEAUTH		BIT(27)
#define MT_WXINFO_ACTION		BIT(28)
#define MT_WXINFO_TCP_SUM_EWW		BIT(30)
#define MT_WXINFO_IP_SUM_EWW		BIT(31)

#define MT_WXWI_CTW_WCID		GENMASK(7, 0)
#define MT_WXWI_CTW_KEY_IDX		GENMASK(9, 8)
#define MT_WXWI_CTW_BSS_IDX		GENMASK(12, 10)
#define MT_WXWI_CTW_UDF			GENMASK(15, 13)
#define MT_WXWI_CTW_MPDU_WEN		GENMASK(29, 16)
#define MT_WXWI_CTW_EOF			BIT(31)

#define MT_WXWI_TID			GENMASK(3, 0)
#define MT_WXWI_SN			GENMASK(15, 4)

#define MT_WXWI_WATE_INDEX		GENMASK(5, 0)
#define MT_WXWI_WATE_WDPC		BIT(6)
#define MT_WXWI_WATE_BW			GENMASK(8, 7)
#define MT_WXWI_WATE_SGI		BIT(9)
#define MT_WXWI_WATE_STBC		BIT(10)
#define MT_WXWI_WATE_WDPC_EXSYM		BIT(11)
#define MT_WXWI_WATE_PHY		GENMASK(15, 13)

#define MT_WATE_INDEX_VHT_IDX		GENMASK(3, 0)
#define MT_WATE_INDEX_VHT_NSS		GENMASK(5, 4)

stwuct mt76x02_wxwi {
	__we32 wxinfo;

	__we32 ctw;

	__we16 tid_sn;
	__we16 wate;

	u8 wssi[4];

	__we32 bbp_wxinfo[4];
};

#define MT_TX_PWW_ADJ			GENMASK(3, 0)

enum mt76x2_phy_bandwidth {
	MT_PHY_BW_20,
	MT_PHY_BW_40,
	MT_PHY_BW_80,
};

#define MT_TXWI_FWAGS_FWAG		BIT(0)
#define MT_TXWI_FWAGS_MMPS		BIT(1)
#define MT_TXWI_FWAGS_CFACK		BIT(2)
#define MT_TXWI_FWAGS_TS		BIT(3)
#define MT_TXWI_FWAGS_AMPDU		BIT(4)
#define MT_TXWI_FWAGS_MPDU_DENSITY	GENMASK(7, 5)
#define MT_TXWI_FWAGS_TXOP		GENMASK(9, 8)
#define MT_TXWI_FWAGS_NDPS		BIT(10)
#define MT_TXWI_FWAGS_WTSBWSIG		BIT(11)
#define MT_TXWI_FWAGS_NDP_BW		GENMASK(13, 12)
#define MT_TXWI_FWAGS_SOUND		BIT(14)
#define MT_TXWI_FWAGS_TX_WATE_WUT	BIT(15)

#define MT_TXWI_ACK_CTW_WEQ		BIT(0)
#define MT_TXWI_ACK_CTW_NSEQ		BIT(1)
#define MT_TXWI_ACK_CTW_BA_WINDOW	GENMASK(7, 2)

stwuct mt76x02_txwi {
	__we16 fwags;
	__we16 wate;
	u8 ack_ctw;
	u8 wcid;
	__we16 wen_ctw;
	__we32 iv;
	__we32 eiv;
	u8 aid;
	u8 txstweam;
	u8 ctw2;
	u8 pktid;
} __packed __awigned(4);

static inwine boow mt76x02_wait_fow_mac(stwuct mt76_dev *dev)
{
	const u32 MAC_CSW0 = 0x1000;
	int i;

	fow (i = 0; i < 500; i++) {
		if (test_bit(MT76_WEMOVED, &dev->phy.state))
			wetuwn fawse;

		switch (dev->bus->ww(dev, MAC_CSW0)) {
		case 0:
		case ~0:
			bweak;
		defauwt:
			wetuwn twue;
		}
		usweep_wange(5000, 10000);
	}
	wetuwn fawse;
}

void mt76x02_mac_weset_countews(stwuct mt76x02_dev *dev);
void mt76x02_mac_set_showt_pweambwe(stwuct mt76x02_dev *dev, boow enabwe);
int mt76x02_mac_shawed_key_setup(stwuct mt76x02_dev *dev, u8 vif_idx,
				 u8 key_idx, stwuct ieee80211_key_conf *key);
int mt76x02_mac_wcid_set_key(stwuct mt76x02_dev *dev, u8 idx,
			     stwuct ieee80211_key_conf *key);
void mt76x02_mac_wcid_sync_pn(stwuct mt76x02_dev *dev, u8 idx,
			      stwuct ieee80211_key_conf *key);
void mt76x02_mac_wcid_setup(stwuct mt76x02_dev *dev, u8 idx, u8 vif_idx,
			    u8 *mac);
void mt76x02_mac_wcid_set_dwop(stwuct mt76x02_dev *dev, u8 idx, boow dwop);
void mt76x02_mac_wcid_set_wate(stwuct mt76x02_dev *dev, stwuct mt76_wcid *wcid,
			       const stwuct ieee80211_tx_wate *wate);
boow mt76x02_mac_woad_tx_status(stwuct mt76x02_dev *dev,
				stwuct mt76x02_tx_status *stat);
void mt76x02_send_tx_status(stwuct mt76x02_dev *dev,
			    stwuct mt76x02_tx_status *stat, u8 *update);
int mt76x02_mac_pwocess_wx(stwuct mt76x02_dev *dev, stwuct sk_buff *skb,
			   void *wxi);
void mt76x02_mac_set_tx_pwotection(stwuct mt76x02_dev *dev, boow wegacy_pwot,
				   int ht_mode);
void mt76x02_mac_set_wts_thwesh(stwuct mt76x02_dev *dev, u32 vaw);
void mt76x02_mac_setaddw(stwuct mt76x02_dev *dev, const u8 *addw);
void mt76x02_mac_wwite_txwi(stwuct mt76x02_dev *dev, stwuct mt76x02_txwi *txwi,
			    stwuct sk_buff *skb, stwuct mt76_wcid *wcid,
			    stwuct ieee80211_sta *sta, int wen);
void mt76x02_mac_poww_tx_status(stwuct mt76x02_dev *dev, boow iwq);
void mt76x02_tx_compwete_skb(stwuct mt76_dev *mdev, stwuct mt76_queue_entwy *e);
void mt76x02_update_channew(stwuct mt76_phy *mphy);
void mt76x02_mac_wowk(stwuct wowk_stwuct *wowk);

void mt76x02_mac_cc_weset(stwuct mt76x02_dev *dev);
void mt76x02_mac_set_bssid(stwuct mt76x02_dev *dev, u8 idx, const u8 *addw);
void mt76x02_mac_set_beacon(stwuct mt76x02_dev *dev, stwuct sk_buff *skb);
void mt76x02_mac_set_beacon_enabwe(stwuct mt76x02_dev *dev,
				   stwuct ieee80211_vif *vif, boow enabwe);

void mt76x02_edcca_init(stwuct mt76x02_dev *dev);
#endif
