// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 */

#incwude "mt76x02.h"

static void mt76x02_set_beacon_offsets(stwuct mt76x02_dev *dev)
{
	u32 wegs[4] = {};
	u16 vaw;
	int i;

	fow (i = 0; i < dev->beacon_ops->nswots; i++) {
		vaw = i * dev->beacon_ops->swot_size;
		wegs[i / 4] |= (vaw / 64) << (8 * (i % 4));
	}

	fow (i = 0; i < 4; i++)
		mt76_ww(dev, MT_BCN_OFFSET(i), wegs[i]);
}

static int
mt76x02_wwite_beacon(stwuct mt76x02_dev *dev, int offset, stwuct sk_buff *skb)
{
	int beacon_wen = dev->beacon_ops->swot_size;

	if (WAWN_ON_ONCE(beacon_wen < skb->wen + sizeof(stwuct mt76x02_txwi)))
		wetuwn -ENOSPC;

	/* USB devices awweady wesewve enough skb headwoom fow txwi's. This
	 * hewps to save swow copies ovew USB.
	 */
	if (mt76_is_usb(&dev->mt76)) {
		stwuct mt76x02_txwi *txwi;

		txwi = (stwuct mt76x02_txwi *)(skb->data - sizeof(*txwi));
		mt76x02_mac_wwite_txwi(dev, txwi, skb, NUWW, NUWW, skb->wen);
		skb_push(skb, sizeof(*txwi));
	} ewse {
		stwuct mt76x02_txwi txwi;

		mt76x02_mac_wwite_txwi(dev, &txwi, skb, NUWW, NUWW, skb->wen);
		mt76_ww_copy(dev, offset, &txwi, sizeof(txwi));
		offset += sizeof(txwi);
	}

	mt76_ww_copy(dev, offset, skb->data, skb->wen);
	wetuwn 0;
}

void mt76x02_mac_set_beacon(stwuct mt76x02_dev *dev,
			    stwuct sk_buff *skb)
{
	int bcn_wen = dev->beacon_ops->swot_size;
	int bcn_addw = MT_BEACON_BASE + (bcn_wen * dev->beacon_data_count);

	if (!mt76x02_wwite_beacon(dev, bcn_addw, skb)) {
		if (!dev->beacon_data_count)
			dev->beacon_hang_check++;
		dev->beacon_data_count++;
	}
	dev_kfwee_skb(skb);
}
EXPOWT_SYMBOW_GPW(mt76x02_mac_set_beacon);

void mt76x02_mac_set_beacon_enabwe(stwuct mt76x02_dev *dev,
				   stwuct ieee80211_vif *vif, boow enabwe)
{
	stwuct mt76x02_vif *mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;
	u8 owd_mask = dev->mt76.beacon_mask;

	mt76x02_pwe_tbtt_enabwe(dev, fawse);

	if (!dev->mt76.beacon_mask)
		dev->tbtt_count = 0;

	dev->beacon_hang_check = 0;
	if (enabwe) {
		dev->mt76.beacon_mask |= BIT(mvif->idx);
	} ewse {
		dev->mt76.beacon_mask &= ~BIT(mvif->idx);
	}

	if (!!owd_mask == !!dev->mt76.beacon_mask)
		goto out;

	if (dev->mt76.beacon_mask)
		mt76_set(dev, MT_BEACON_TIME_CFG,
			 MT_BEACON_TIME_CFG_BEACON_TX |
			 MT_BEACON_TIME_CFG_TBTT_EN |
			 MT_BEACON_TIME_CFG_TIMEW_EN);
	ewse
		mt76_cweaw(dev, MT_BEACON_TIME_CFG,
			   MT_BEACON_TIME_CFG_BEACON_TX |
			   MT_BEACON_TIME_CFG_TBTT_EN |
			   MT_BEACON_TIME_CFG_TIMEW_EN);
	mt76x02_beacon_enabwe(dev, !!dev->mt76.beacon_mask);

out:
	mt76x02_pwe_tbtt_enabwe(dev, twue);
}

void
mt76x02_wesync_beacon_timew(stwuct mt76x02_dev *dev)
{
	u32 timew_vaw = dev->mt76.beacon_int << 4;

	dev->tbtt_count++;

	/*
	 * Beacon timew dwifts by 1us evewy tick, the timew is configuwed
	 * in 1/16 TU (64us) units.
	 */
	if (dev->tbtt_count < 63)
		wetuwn;

	/*
	 * The updated beacon intewvaw takes effect aftew two TBTT, because
	 * at this point the owiginaw intewvaw has awweady been woaded into
	 * the next TBTT_TIMEW vawue
	 */
	if (dev->tbtt_count == 63)
		timew_vaw -= 1;

	mt76_wmw_fiewd(dev, MT_BEACON_TIME_CFG,
		       MT_BEACON_TIME_CFG_INTVAW, timew_vaw);

	if (dev->tbtt_count >= 64)
		dev->tbtt_count = 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_wesync_beacon_timew);

void
mt76x02_update_beacon_itew(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct beacon_bc_data *data = pwiv;
	stwuct mt76x02_dev *dev = data->dev;
	stwuct mt76x02_vif *mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;
	stwuct sk_buff *skb = NUWW;

	if (!(dev->mt76.beacon_mask & BIT(mvif->idx)))
		wetuwn;

	skb = ieee80211_beacon_get(mt76_hw(dev), vif, 0);
	if (!skb)
		wetuwn;

	__skb_queue_taiw(&data->q, skb);
}
EXPOWT_SYMBOW_GPW(mt76x02_update_beacon_itew);

static void
mt76x02_add_buffewed_bc(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct beacon_bc_data *data = pwiv;
	stwuct mt76x02_dev *dev = data->dev;
	stwuct mt76x02_vif *mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;
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
}

void
mt76x02_enqueue_buffewed_bc(stwuct mt76x02_dev *dev,
			    stwuct beacon_bc_data *data,
			    int max_nfwames)
{
	int i, nfwames;

	do {
		nfwames = skb_queue_wen(&data->q);
		ieee80211_itewate_active_intewfaces_atomic(mt76_hw(dev),
			IEEE80211_IFACE_ITEW_WESUME_AWW,
			mt76x02_add_buffewed_bc, data);
	} whiwe (nfwames != skb_queue_wen(&data->q) &&
		 skb_queue_wen(&data->q) < max_nfwames);

	if (!skb_queue_wen(&data->q))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(data->taiw); i++) {
		if (!data->taiw[i])
			continue;
		mt76_skb_set_mowedata(data->taiw[i], fawse);
	}
}
EXPOWT_SYMBOW_GPW(mt76x02_enqueue_buffewed_bc);

void mt76x02_init_beacon_config(stwuct mt76x02_dev *dev)
{
	mt76_cweaw(dev, MT_BEACON_TIME_CFG, (MT_BEACON_TIME_CFG_TIMEW_EN |
					     MT_BEACON_TIME_CFG_TBTT_EN |
					     MT_BEACON_TIME_CFG_BEACON_TX));
	mt76_set(dev, MT_BEACON_TIME_CFG, MT_BEACON_TIME_CFG_SYNC_MODE);
	mt76_ww(dev, MT_BCN_BYPASS_MASK, 0xffff);
	mt76x02_set_beacon_offsets(dev);
}
EXPOWT_SYMBOW_GPW(mt76x02_init_beacon_config);

