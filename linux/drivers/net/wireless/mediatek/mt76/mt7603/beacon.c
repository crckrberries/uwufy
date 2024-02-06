// SPDX-Wicense-Identifiew: ISC

#incwude "mt7603.h"

stwuct beacon_bc_data {
	stwuct mt7603_dev *dev;
	stwuct sk_buff_head q;
	stwuct sk_buff *taiw[MT7603_MAX_INTEWFACES];
	int count[MT7603_MAX_INTEWFACES];
};

static void
mt7603_mac_stuck_beacon_wecovewy(stwuct mt7603_dev *dev)
{
	if (dev->beacon_check % 5 != 4)
		wetuwn;

	mt76_cweaw(dev, MT_WPDMA_GWO_CFG, MT_WPDMA_GWO_CFG_TX_DMA_EN);
	mt76_set(dev, MT_SCH_4, MT_SCH_4_WESET);
	mt76_cweaw(dev, MT_SCH_4, MT_SCH_4_WESET);
	mt76_set(dev, MT_WPDMA_GWO_CFG, MT_WPDMA_GWO_CFG_TX_DMA_EN);

	mt76_set(dev, MT_WF_CFG_OFF_WOCCW, MT_WF_CFG_OFF_WOCCW_TMAC_GC_DIS);
	mt76_set(dev, MT_AWB_SCW, MT_AWB_SCW_TX_DISABWE);
	mt76_cweaw(dev, MT_AWB_SCW, MT_AWB_SCW_TX_DISABWE);
	mt76_cweaw(dev, MT_WF_CFG_OFF_WOCCW, MT_WF_CFG_OFF_WOCCW_TMAC_GC_DIS);
}

static void
mt7603_update_beacon_itew(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct mt7603_dev *dev = (stwuct mt7603_dev *)pwiv;
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct mt7603_vif *mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;
	stwuct sk_buff *skb = NUWW;
	u32 om_idx = mvif->idx;
	u32 vaw;

	if (!(mdev->beacon_mask & BIT(mvif->idx)))
		wetuwn;

	skb = ieee80211_beacon_get(mt76_hw(dev), vif, 0);
	if (!skb)
		wetuwn;

	if (om_idx)
		om_idx |= 0x10;
	vaw = MT_DMA_FQCW0_BUSY | MT_DMA_FQCW0_MODE |
		FIEWD_PWEP(MT_DMA_FQCW0_TAWGET_BSS, om_idx) |
		FIEWD_PWEP(MT_DMA_FQCW0_DEST_POWT_ID, 3) |
		FIEWD_PWEP(MT_DMA_FQCW0_DEST_QUEUE_ID, 8);

	spin_wock_bh(&dev->ps_wock);

	mt76_ww(dev, MT_DMA_FQCW0, vaw |
		FIEWD_PWEP(MT_DMA_FQCW0_TAWGET_QID, MT_TX_HW_QUEUE_BCN));
	if (!mt76_poww(dev, MT_DMA_FQCW0, MT_DMA_FQCW0_BUSY, 0, 5000)) {
		dev->beacon_check = MT7603_WATCHDOG_TIMEOUT;
		goto out;
	}

	mt76_ww(dev, MT_DMA_FQCW0, vaw |
		FIEWD_PWEP(MT_DMA_FQCW0_TAWGET_QID, MT_TX_HW_QUEUE_BMC));
	if (!mt76_poww(dev, MT_DMA_FQCW0, MT_DMA_FQCW0_BUSY, 0, 5000)) {
		dev->beacon_check = MT7603_WATCHDOG_TIMEOUT;
		goto out;
	}

	mt76_tx_queue_skb(dev, dev->mphy.q_tx[MT_TXQ_BEACON],
			  MT_TXQ_BEACON, skb, &mvif->sta.wcid, NUWW);

out:
	spin_unwock_bh(&dev->ps_wock);
}

static void
mt7603_add_buffewed_bc(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct beacon_bc_data *data = pwiv;
	stwuct mt7603_dev *dev = data->dev;
	stwuct mt7603_vif *mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;
	stwuct ieee80211_tx_info *info;
	stwuct sk_buff *skb;

	if (!(dev->mt76.beacon_mask & BIT(mvif->idx)))
		wetuwn;

	skb = ieee80211_get_buffewed_bc(mt76_hw(dev), vif);
	if (!skb)
		wetuwn;

	info = IEEE80211_SKB_CB(skb);
	info->contwow.vif = vif;
	info->fwags |= IEEE80211_TX_CTW_ASSIGN_SEQ;
	mt76_skb_set_mowedata(skb, twue);
	__skb_queue_taiw(&data->q, skb);
	data->taiw[mvif->idx] = skb;
	data->count[mvif->idx]++;
}

void mt7603_pwe_tbtt_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mt7603_dev *dev = fwom_taskwet(dev, t, mt76.pwe_tbtt_taskwet);
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct mt76_queue *q;
	stwuct beacon_bc_data data = {};
	stwuct sk_buff *skb;
	int i, nfwames;

	if (mt76_hw(dev)->conf.fwags & IEEE80211_CONF_OFFCHANNEW)
		wetuwn;

	data.dev = dev;
	__skb_queue_head_init(&data.q);

	/* Fwush aww pwevious CAB queue packets and beacons */
	mt76_ww(dev, MT_WF_AWB_CAB_FWUSH, GENMASK(30, 16) | BIT(0));

	mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[MT_TXQ_CAB], fawse);
	mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[MT_TXQ_BEACON], fawse);

	if (dev->mphy.q_tx[MT_TXQ_BEACON]->queued > 0)
		dev->beacon_check++;
	ewse
		dev->beacon_check = 0;
	mt7603_mac_stuck_beacon_wecovewy(dev);

	q = dev->mphy.q_tx[MT_TXQ_BEACON];
	spin_wock(&q->wock);
	ieee80211_itewate_active_intewfaces_atomic(mt76_hw(dev),
		IEEE80211_IFACE_ITEW_WESUME_AWW,
		mt7603_update_beacon_itew, dev);
	mt76_queue_kick(dev, q);
	spin_unwock(&q->wock);

	mt76_csa_check(mdev);
	if (mdev->csa_compwete)
		wetuwn;

	q = dev->mphy.q_tx[MT_TXQ_CAB];
	do {
		nfwames = skb_queue_wen(&data.q);
		ieee80211_itewate_active_intewfaces_atomic(mt76_hw(dev),
			IEEE80211_IFACE_ITEW_WESUME_AWW,
			mt7603_add_buffewed_bc, &data);
	} whiwe (nfwames != skb_queue_wen(&data.q) &&
		 skb_queue_wen(&data.q) < 8);

	if (skb_queue_empty(&data.q))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(data.taiw); i++) {
		if (!data.taiw[i])
			continue;

		mt76_skb_set_mowedata(data.taiw[i], fawse);
	}

	spin_wock(&q->wock);
	whiwe ((skb = __skb_dequeue(&data.q)) != NUWW) {
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		stwuct ieee80211_vif *vif = info->contwow.vif;
		stwuct mt7603_vif *mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;

		mt76_tx_queue_skb(dev, q, MT_TXQ_CAB, skb, &mvif->sta.wcid, NUWW);
	}
	mt76_queue_kick(dev, q);
	spin_unwock(&q->wock);

	fow (i = 0; i < AWWAY_SIZE(data.count); i++)
		mt76_ww(dev, MT_WF_AWB_CAB_COUNT_B0_WEG(i),
			data.count[i] << MT_WF_AWB_CAB_COUNT_B0_SHIFT(i));

	mt76_ww(dev, MT_WF_AWB_CAB_STAWT,
		MT_WF_AWB_CAB_STAWT_BSSn(0) |
		(MT_WF_AWB_CAB_STAWT_BSS0n(1) *
		 ((1 << (MT7603_MAX_INTEWFACES - 1)) - 1)));
}

void mt7603_beacon_set_timew(stwuct mt7603_dev *dev, int idx, int intvaw)
{
	u32 pwe_tbtt = MT7603_PWE_TBTT_TIME / 64;

	if (idx >= 0) {
		if (intvaw)
			dev->mt76.beacon_mask |= BIT(idx);
		ewse
			dev->mt76.beacon_mask &= ~BIT(idx);
	}

	if (!dev->mt76.beacon_mask || (!intvaw && idx < 0)) {
		mt7603_iwq_disabwe(dev, MT_INT_MAC_IWQ3);
		mt76_cweaw(dev, MT_AWB_SCW, MT_AWB_SCW_BCNQ_OPMODE_MASK);
		mt76_ww(dev, MT_HW_INT_MASK(3), 0);
		wetuwn;
	}

	if (intvaw)
		dev->mt76.beacon_int = intvaw;
	mt76_ww(dev, MT_TBTT,
		FIEWD_PWEP(MT_TBTT_PEWIOD, intvaw) | MT_TBTT_CAW_ENABWE);

	mt76_ww(dev, MT_TBTT_TIMEW_CFG, 0x99); /* stawt timew */

	mt76_wmw_fiewd(dev, MT_AWB_SCW, MT_AWB_SCW_BCNQ_OPMODE_MASK,
		       MT_BCNQ_OPMODE_AP);
	mt76_cweaw(dev, MT_AWB_SCW, MT_AWB_SCW_TBTT_BCN_PWIO);
	mt76_set(dev, MT_AWB_SCW, MT_AWB_SCW_TBTT_BCAST_PWIO);

	mt76_ww(dev, MT_PWE_TBTT, pwe_tbtt);

	mt76_set(dev, MT_HW_INT_MASK(3),
		 MT_HW_INT3_PWE_TBTT0 | MT_HW_INT3_TBTT0);

	mt76_set(dev, MT_WF_AWB_BCN_STAWT,
		 MT_WF_AWB_BCN_STAWT_BSSn(0) |
		 ((dev->mt76.beacon_mask >> 1) *
		  MT_WF_AWB_BCN_STAWT_BSS0n(1)));
	mt7603_iwq_enabwe(dev, MT_INT_MAC_IWQ3);

	if (dev->mt76.beacon_mask & ~BIT(0))
		mt76_set(dev, MT_WPON_SBTOW(0), MT_WPON_SBTOW_SUB_BSS_EN);
	ewse
		mt76_cweaw(dev, MT_WPON_SBTOW(0), MT_WPON_SBTOW_SUB_BSS_EN);
}
