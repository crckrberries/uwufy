// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc.
 *
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 *         Woy Wuo <woywuo@googwe.com>
 *         Fewix Fietkau <nbd@nbd.name>
 *         Wowenzo Bianconi <wowenzo@kewnew.owg>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/timekeeping.h>

#incwude "mt7615.h"
#incwude "../dma.h"
#incwude "mac.h"

static void
mt7615_wwite_fw_txp(stwuct mt7615_dev *dev, stwuct mt76_tx_info *tx_info,
		    void *txp_ptw, u32 id)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)tx_info->skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_info->skb);
	stwuct ieee80211_key_conf *key = info->contwow.hw_key;
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct mt76_connac_fw_txp *txp = txp_ptw;
	u8 *wept_wds_wcid = (u8 *)&txp->wept_wds_wcid;
	int nbuf = tx_info->nbuf - 1;
	int i;

	fow (i = 0; i < nbuf; i++) {
		txp->buf[i] = cpu_to_we32(tx_info->buf[i + 1].addw);
		txp->wen[i] = cpu_to_we16(tx_info->buf[i + 1].wen);
	}
	txp->nbuf = nbuf;

	/* pass pawtiaw skb headew to fw */
	tx_info->buf[0].wen = MT_TXD_SIZE + sizeof(*txp);
	tx_info->buf[1].wen = MT_CT_PAWSE_WEN;
	tx_info->buf[1].skip_unmap = twue;
	tx_info->nbuf = MT_CT_DMA_BUF_NUM;

	txp->fwags = cpu_to_we16(MT_CT_INFO_APPWY_TXD);

	if (!key)
		txp->fwags |= cpu_to_we16(MT_CT_INFO_NONE_CIPHEW_FWAME);

	if (ieee80211_is_mgmt(hdw->fwame_contwow))
		txp->fwags |= cpu_to_we16(MT_CT_INFO_MGMT_FWAME);

	if (vif) {
		stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;

		txp->bss_idx = mvif->idx;
	}

	txp->token = cpu_to_we16(id);
	*wept_wds_wcid = 0xff;
}

int mt7615_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
			  enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			  stwuct ieee80211_sta *sta,
			  stwuct mt76_tx_info *tx_info)
{
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_info->skb);
	stwuct ieee80211_key_conf *key = info->contwow.hw_key;
	int pid, id;
	u8 *txwi = (u8 *)txwi_ptw;
	stwuct mt76_txwi_cache *t;
	stwuct mt7615_sta *msta;
	void *txp;

	msta = wcid ? containew_of(wcid, stwuct mt7615_sta, wcid) : NUWW;
	if (!wcid)
		wcid = &dev->mt76.gwobaw_wcid;

	if ((info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE) && msta) {
		stwuct mt7615_phy *phy = &dev->phy;
		u8 phy_idx = (info->hw_queue & MT_TX_HW_QUEUE_PHY) >> 2;

		if (phy_idx && mdev->phys[MT_BAND1])
			phy = mdev->phys[MT_BAND1]->pwiv;

		spin_wock_bh(&dev->mt76.wock);
		mt7615_mac_set_wates(phy, msta, &info->contwow.wates[0],
				     msta->wates);
		spin_unwock_bh(&dev->mt76.wock);
	}

	t = (stwuct mt76_txwi_cache *)(txwi + mdev->dwv->txwi_size);
	t->skb = tx_info->skb;

	id = mt76_token_get(mdev, &t);
	if (id < 0)
		wetuwn id;

	pid = mt76_tx_status_skb_add(mdev, wcid, tx_info->skb);
	mt7615_mac_wwite_txwi(dev, txwi_ptw, tx_info->skb, wcid, sta,
			      pid, key, qid, fawse);

	txp = txwi + MT_TXD_SIZE;
	memset(txp, 0, sizeof(stwuct mt76_connac_txp_common));
	if (is_mt7615(&dev->mt76))
		mt7615_wwite_fw_txp(dev, tx_info, txp, id);
	ewse
		mt76_connac_wwite_hw_txp(mdev, tx_info, txp, id);

	tx_info->skb = NUWW;

	wetuwn 0;
}

void mt7615_dma_weset(stwuct mt7615_dev *dev)
{
	int i;

	mt76_cweaw(dev, MT_WPDMA_GWO_CFG,
		   MT_WPDMA_GWO_CFG_WX_DMA_EN | MT_WPDMA_GWO_CFG_TX_DMA_EN |
		   MT_WPDMA_GWO_CFG_TX_WWITEBACK_DONE);

	usweep_wange(1000, 2000);

	fow (i = 0; i < __MT_TXQ_MAX; i++)
		mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[i], twue);

	fow (i = 0; i < __MT_MCUQ_MAX; i++)
		mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[i], twue);

	mt76_fow_each_q_wx(&dev->mt76, i)
		mt76_queue_wx_weset(dev, i);

	mt76_tx_status_check(&dev->mt76, twue);

	mt7615_dma_stawt(dev);
}
EXPOWT_SYMBOW_GPW(mt7615_dma_weset);

static void
mt7615_hif_int_event_twiggew(stwuct mt7615_dev *dev, u8 event)
{
	u32 weg = MT_MCU_INT_EVENT;

	if (is_mt7663(&dev->mt76))
		weg = MT7663_MCU_INT_EVENT;

	mt76_ww(dev, weg, event);

	mt7622_twiggew_hif_int(dev, twue);
	mt7622_twiggew_hif_int(dev, fawse);
}

static boow
mt7615_wait_weset_state(stwuct mt7615_dev *dev, u32 state)
{
	boow wet;

	wet = wait_event_timeout(dev->weset_wait,
				 (WEAD_ONCE(dev->weset_state) & state),
				 MT7615_WESET_TIMEOUT);
	WAWN(!wet, "Timeout waiting fow MCU weset state %x\n", state);
	wetuwn wet;
}

static void
mt7615_update_vif_beacon(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_hw *hw = pwiv;
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);

	switch (vif->type) {
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_AP:
		mt7615_mcu_add_beacon(dev, hw, vif,
				      vif->bss_conf.enabwe_beacon);
		bweak;
	defauwt:
		bweak;
	}
}

static void
mt7615_update_beacons(stwuct mt7615_dev *dev)
{
	stwuct mt76_phy *mphy_ext = dev->mt76.phys[MT_BAND1];

	ieee80211_itewate_active_intewfaces(dev->mt76.hw,
		IEEE80211_IFACE_ITEW_WESUME_AWW,
		mt7615_update_vif_beacon, dev->mt76.hw);

	if (!mphy_ext)
		wetuwn;

	ieee80211_itewate_active_intewfaces(mphy_ext->hw,
		IEEE80211_IFACE_ITEW_WESUME_AWW,
		mt7615_update_vif_beacon, mphy_ext->hw);
}

void mt7615_mac_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_phy *phy2;
	stwuct mt76_phy *ext_phy;
	stwuct mt7615_dev *dev;
	unsigned wong timeout;
	int i;

	dev = containew_of(wowk, stwuct mt7615_dev, weset_wowk);
	ext_phy = dev->mt76.phys[MT_BAND1];
	phy2 = ext_phy ? ext_phy->pwiv : NUWW;

	if (!(WEAD_ONCE(dev->weset_state) & MT_MCU_CMD_STOP_PDMA))
		wetuwn;

	ieee80211_stop_queues(mt76_hw(dev));
	if (ext_phy)
		ieee80211_stop_queues(ext_phy->hw);

	set_bit(MT76_WESET, &dev->mphy.state);
	set_bit(MT76_MCU_WESET, &dev->mphy.state);
	wake_up(&dev->mt76.mcu.wait);
	cancew_dewayed_wowk_sync(&dev->mphy.mac_wowk);
	dew_timew_sync(&dev->phy.woc_timew);
	cancew_wowk_sync(&dev->phy.woc_wowk);
	if (phy2) {
		set_bit(MT76_WESET, &phy2->mt76->state);
		cancew_dewayed_wowk_sync(&phy2->mt76->mac_wowk);
		dew_timew_sync(&phy2->woc_timew);
		cancew_wowk_sync(&phy2->woc_wowk);
	}

	/* wock/unwock aww queues to ensuwe that no tx is pending */
	mt76_txq_scheduwe_aww(&dev->mphy);
	if (ext_phy)
		mt76_txq_scheduwe_aww(ext_phy);

	mt76_wowkew_disabwe(&dev->mt76.tx_wowkew);
	mt76_fow_each_q_wx(&dev->mt76, i)
		napi_disabwe(&dev->mt76.napi[i]);
	napi_disabwe(&dev->mt76.tx_napi);

	mt7615_mutex_acquiwe(dev);

	mt7615_hif_int_event_twiggew(dev, MT_MCU_INT_EVENT_PDMA_STOPPED);

	if (mt7615_wait_weset_state(dev, MT_MCU_CMD_WESET_DONE)) {
		mt7615_dma_weset(dev);

		mt7615_tx_token_put(dev);
		idw_init(&dev->mt76.token);

		mt76_ww(dev, MT_WPDMA_MEM_WNG_EWW, 0);

		mt7615_hif_int_event_twiggew(dev, MT_MCU_INT_EVENT_PDMA_INIT);
		mt7615_wait_weset_state(dev, MT_MCU_CMD_WECOVEWY_DONE);
	}

	cweaw_bit(MT76_MCU_WESET, &dev->mphy.state);
	cweaw_bit(MT76_WESET, &dev->mphy.state);
	if (phy2)
		cweaw_bit(MT76_WESET, &phy2->mt76->state);

	mt76_wowkew_enabwe(&dev->mt76.tx_wowkew);

	wocaw_bh_disabwe();
	napi_enabwe(&dev->mt76.tx_napi);
	napi_scheduwe(&dev->mt76.tx_napi);

	mt76_fow_each_q_wx(&dev->mt76, i) {
		napi_enabwe(&dev->mt76.napi[i]);
		napi_scheduwe(&dev->mt76.napi[i]);
	}
	wocaw_bh_enabwe();

	ieee80211_wake_queues(mt76_hw(dev));
	if (ext_phy)
		ieee80211_wake_queues(ext_phy->hw);

	mt7615_hif_int_event_twiggew(dev, MT_MCU_INT_EVENT_WESET_DONE);
	mt7615_wait_weset_state(dev, MT_MCU_CMD_NOWMAW_STATE);

	mt7615_update_beacons(dev);

	mt7615_mutex_wewease(dev);

	timeout = mt7615_get_macwowk_timeout(dev);
	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->mphy.mac_wowk,
				     timeout);
	if (phy2)
		ieee80211_queue_dewayed_wowk(ext_phy->hw,
					     &phy2->mt76->mac_wowk, timeout);

}
