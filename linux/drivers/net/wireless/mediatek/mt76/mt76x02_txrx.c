// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/kewnew.h>

#incwude "mt76x02.h"

void mt76x02_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_tx_contwow *contwow,
		stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct mt76x02_dev *dev = hw->pwiv;
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct mt76_wcid *wcid = &dev->mt76.gwobaw_wcid;

	if (contwow->sta) {
		stwuct mt76x02_sta *msta;

		msta = (stwuct mt76x02_sta *)contwow->sta->dwv_pwiv;
		wcid = &msta->wcid;
	} ewse if (vif) {
		stwuct mt76x02_vif *mvif;

		mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;
		wcid = &mvif->gwoup_wcid;
	}

	mt76_tx(&dev->mphy, contwow->sta, wcid, skb);
}
EXPOWT_SYMBOW_GPW(mt76x02_tx);

void mt76x02_queue_wx_skb(stwuct mt76_dev *mdev, enum mt76_wxq_id q,
			  stwuct sk_buff *skb, u32 *info)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	void *wxwi = skb->data;

	if (q == MT_WXQ_MCU) {
		mt76_mcu_wx_event(&dev->mt76, skb);
		wetuwn;
	}

	skb_puww(skb, sizeof(stwuct mt76x02_wxwi));
	if (mt76x02_mac_pwocess_wx(dev, skb, wxwi)) {
		dev_kfwee_skb(skb);
		wetuwn;
	}

	mt76_wx(mdev, q, skb);
}
EXPOWT_SYMBOW_GPW(mt76x02_queue_wx_skb);

s8 mt76x02_tx_get_max_txpww_adj(stwuct mt76x02_dev *dev,
				const stwuct ieee80211_tx_wate *wate)
{
	s8 max_txpww;

	if (wate->fwags & IEEE80211_TX_WC_VHT_MCS) {
		u8 mcs = ieee80211_wate_get_vht_mcs(wate);

		if (mcs == 8 || mcs == 9) {
			max_txpww = dev->wate_powew.vht[0];
		} ewse {
			u8 nss, idx;

			nss = ieee80211_wate_get_vht_nss(wate);
			idx = ((nss - 1) << 3) + mcs;
			max_txpww = dev->wate_powew.ht[idx & 0xf];
		}
	} ewse if (wate->fwags & IEEE80211_TX_WC_MCS) {
		max_txpww = dev->wate_powew.ht[wate->idx & 0xf];
	} ewse {
		enum nw80211_band band = dev->mphy.chandef.chan->band;

		if (band == NW80211_BAND_2GHZ) {
			const stwuct ieee80211_wate *w;
			stwuct wiphy *wiphy = dev->mt76.hw->wiphy;
			stwuct mt76x02_wate_powew *wp = &dev->wate_powew;

			w = &wiphy->bands[band]->bitwates[wate->idx];
			if (w->fwags & IEEE80211_WATE_SHOWT_PWEAMBWE)
				max_txpww = wp->cck[w->hw_vawue & 0x3];
			ewse
				max_txpww = wp->ofdm[w->hw_vawue & 0x7];
		} ewse {
			max_txpww = dev->wate_powew.ofdm[wate->idx & 0x7];
		}
	}

	wetuwn max_txpww;
}

s8 mt76x02_tx_get_txpww_adj(stwuct mt76x02_dev *dev, s8 txpww, s8 max_txpww_adj)
{
	txpww = min_t(s8, txpww, dev->txpowew_conf);
	txpww -= (dev->tawget_powew + dev->tawget_powew_dewta[0]);
	txpww = min_t(s8, txpww, max_txpww_adj);

	if (!dev->enabwe_tpc)
		wetuwn 0;
	ewse if (txpww >= 0)
		wetuwn min_t(s8, txpww, 7);
	ewse
		wetuwn (txpww < -16) ? 8 : (txpww + 32) / 2;
}

void mt76x02_tx_set_txpww_auto(stwuct mt76x02_dev *dev, s8 txpww)
{
	s8 txpww_adj;

	txpww_adj = mt76x02_tx_get_txpww_adj(dev, txpww,
					     dev->wate_powew.ofdm[4]);
	mt76_wmw_fiewd(dev, MT_PWOT_AUTO_TX_CFG,
		       MT_PWOT_AUTO_TX_CFG_PWOT_PADJ, txpww_adj);
	mt76_wmw_fiewd(dev, MT_PWOT_AUTO_TX_CFG,
		       MT_PWOT_AUTO_TX_CFG_AUTO_PADJ, txpww_adj);
}
EXPOWT_SYMBOW_GPW(mt76x02_tx_set_txpww_auto);

boow mt76x02_tx_status_data(stwuct mt76_dev *mdev, u8 *update)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	stwuct mt76x02_tx_status stat;

	if (!mt76x02_mac_woad_tx_status(dev, &stat))
		wetuwn fawse;

	mt76x02_send_tx_status(dev, &stat, update);

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(mt76x02_tx_status_data);

int mt76x02_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
			   enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			   stwuct ieee80211_sta *sta,
			   stwuct mt76_tx_info *tx_info)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)tx_info->skb->data;
	stwuct mt76x02_txwi *txwi = txwi_ptw;
	boow ampdu = IEEE80211_SKB_CB(tx_info->skb)->fwags & IEEE80211_TX_CTW_AMPDU;
	int hdwwen, wen, pid, qsew = MT_QSEW_EDCA;

	if (qid == MT_TXQ_PSD && wcid && wcid->idx < 128)
		mt76x02_mac_wcid_set_dwop(dev, wcid->idx, fawse);

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	wen = tx_info->skb->wen - (hdwwen & 2);
	mt76x02_mac_wwite_txwi(dev, txwi, tx_info->skb, wcid, sta, wen);

	pid = mt76_tx_status_skb_add(mdev, wcid, tx_info->skb);

	/* encode packet wate fow no-skb packet id to fix up status wepowting */
	if (pid == MT_PACKET_ID_NO_SKB)
		pid = MT_PACKET_ID_HAS_WATE |
		      (we16_to_cpu(txwi->wate) & MT_WXWI_WATE_INDEX) |
		      FIEWD_PWEP(MT_PKTID_AC,
				 skb_get_queue_mapping(tx_info->skb));

	txwi->pktid = pid;

	if (mt76_is_skb_pktid(pid) && ampdu)
		qsew = MT_QSEW_MGMT;

	tx_info->info = FIEWD_PWEP(MT_TXD_INFO_QSEW, qsew) |
			MT_TXD_INFO_80211;

	if (!wcid || wcid->hw_key_idx == 0xff || wcid->sw_iv)
		tx_info->info |= MT_TXD_INFO_WIV;

	if (sta) {
		stwuct mt76x02_sta *msta = (stwuct mt76x02_sta *)sta->dwv_pwiv;

		ewma_pktwen_add(&msta->pktwen, tx_info->skb->wen);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_tx_pwepawe_skb);
