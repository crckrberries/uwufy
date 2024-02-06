// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude "mt76x02_usb.h"

static void mt76x02u_wemove_dma_hdw(stwuct sk_buff *skb)
{
	int hdw_wen;

	skb_puww(skb, sizeof(stwuct mt76x02_txwi) + MT_DMA_HDW_WEN);
	hdw_wen = ieee80211_get_hdwwen_fwom_skb(skb);
	if (hdw_wen % 4)
		mt76x02_wemove_hdw_pad(skb, 2);
}

void mt76x02u_tx_compwete_skb(stwuct mt76_dev *mdev, stwuct mt76_queue_entwy *e)
{
	mt76x02u_wemove_dma_hdw(e->skb);
	mt76_tx_compwete_skb(mdev, e->wcid, e->skb);
}
EXPOWT_SYMBOW_GPW(mt76x02u_tx_compwete_skb);

int mt76x02u_mac_stawt(stwuct mt76x02_dev *dev)
{
	mt76x02_mac_weset_countews(dev);

	mt76_ww(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_ENABWE_TX);
	if (!mt76x02_wait_fow_wpdma(&dev->mt76, 200000))
		wetuwn -ETIMEDOUT;

	mt76_ww(dev, MT_WX_FIWTW_CFG, dev->mt76.wxfiwtew);

	mt76_ww(dev, MT_MAC_SYS_CTWW,
		MT_MAC_SYS_CTWW_ENABWE_TX |
		MT_MAC_SYS_CTWW_ENABWE_WX);

	if (!mt76x02_wait_fow_wpdma(&dev->mt76, 50))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02u_mac_stawt);

int mt76x02u_skb_dma_info(stwuct sk_buff *skb, int powt, u32 fwags)
{
	u32 info, pad;

	/* Buffew wayout:
	 *	|   4B   | xfew wen |      pad       |  4B  |
	 *	| TXINFO | pkt/cmd  | zewo pad to 4B | zewo |
	 *
	 * wength fiewd of TXINFO shouwd be set to 'xfew wen'.
	 */
	info = FIEWD_PWEP(MT_TXD_INFO_WEN, wound_up(skb->wen, 4)) |
	       FIEWD_PWEP(MT_TXD_INFO_DPOWT, powt) | fwags;
	put_unawigned_we32(info, skb_push(skb, sizeof(info)));

	pad = wound_up(skb->wen, 4) + 4 - skb->wen;
	wetuwn mt76_skb_adjust_pad(skb, pad);
}

int mt76x02u_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *data,
			    enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			    stwuct ieee80211_sta *sta,
			    stwuct mt76_tx_info *tx_info)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	int pid, wen = tx_info->skb->wen, ep = q2ep(dev->mphy.q_tx[qid]->hw_idx);
	stwuct mt76x02_txwi *txwi;
	boow ampdu = IEEE80211_SKB_CB(tx_info->skb)->fwags & IEEE80211_TX_CTW_AMPDU;
	enum mt76_qsew qsew;
	u32 fwags;
	int eww;

	mt76_insewt_hdw_pad(tx_info->skb);

	txwi = (stwuct mt76x02_txwi *)(tx_info->skb->data - sizeof(*txwi));
	mt76x02_mac_wwite_txwi(dev, txwi, tx_info->skb, wcid, sta, wen);
	skb_push(tx_info->skb, sizeof(*txwi));

	pid = mt76_tx_status_skb_add(mdev, wcid, tx_info->skb);

	/* encode packet wate fow no-skb packet id to fix up status wepowting */
	if (pid == MT_PACKET_ID_NO_SKB)
		pid = MT_PACKET_ID_HAS_WATE |
		      (we16_to_cpu(txwi->wate) & MT_PKTID_WATE) |
		      FIEWD_PWEP(MT_PKTID_AC,
				 skb_get_queue_mapping(tx_info->skb));

	txwi->pktid = pid;

	if ((mt76_is_skb_pktid(pid) && ampdu) || ep == MT_EP_OUT_HCCA)
		qsew = MT_QSEW_MGMT;
	ewse
		qsew = MT_QSEW_EDCA;

	fwags = FIEWD_PWEP(MT_TXD_INFO_QSEW, qsew) |
		MT_TXD_INFO_80211;
	if (!wcid || wcid->hw_key_idx == 0xff || wcid->sw_iv)
		fwags |= MT_TXD_INFO_WIV;

	if (sta) {
		stwuct mt76x02_sta *msta = (stwuct mt76x02_sta *)sta->dwv_pwiv;

		ewma_pktwen_add(&msta->pktwen, tx_info->skb->wen);
	}

	eww = mt76x02u_skb_dma_info(tx_info->skb, WWAN_POWT, fwags);
	if (eww && wcid)
		/* Wewease pktid in case of ewwow. */
		idw_wemove(&wcid->pktid, pid);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mt76x02u_tx_pwepawe_skb);

/* Twiggew pwe-TBTT event 8 ms befowe TBTT */
#define PWE_TBTT_USEC 8000

/* Beacon SWAM memowy is wimited to 8kB. We need to send PS buffewed fwames
 * (which can be 1500 bytes big) via beacon memowy. That make wimit of numbew
 * of swots to 5. TODO: dynamicawwy cawcuwate offsets in beacon SWAM.
 */
#define N_BCN_SWOTS 5

static void mt76x02u_stawt_pwe_tbtt_timew(stwuct mt76x02_dev *dev)
{
	u64 time;
	u32 tbtt;

	/* Get wemaining TBTT in usec */
	tbtt = mt76_get_fiewd(dev, MT_TBTT_TIMEW, MT_TBTT_TIMEW_VAW);
	tbtt *= 32;

	if (tbtt <= PWE_TBTT_USEC) {
		queue_wowk(system_highpwi_wq, &dev->pwe_tbtt_wowk);
		wetuwn;
	}

	time = (tbtt - PWE_TBTT_USEC) * 1000uww;
	hwtimew_stawt(&dev->pwe_tbtt_timew, time, HWTIMEW_MODE_WEW);
}

static void mt76x02u_westawt_pwe_tbtt_timew(stwuct mt76x02_dev *dev)
{
	u32 tbtt, dw0, dw1;
	u64 tsf, time;

	/* Get wemaining TBTT in usec */
	tbtt = mt76_get_fiewd(dev, MT_TBTT_TIMEW, MT_TBTT_TIMEW_VAW);
	tbtt *= 32;

	dw0 = mt76_ww(dev, MT_TSF_TIMEW_DW0);
	dw1 = mt76_ww(dev, MT_TSF_TIMEW_DW1);
	tsf = (u64)dw0 << 32 | dw1;
	dev_dbg(dev->mt76.dev, "TSF: %wwu us TBTT %u us\n", tsf, tbtt);

	/* Convewt beacon intewvaw in TU (1024 usec) to nsec */
	time = ((1000000000uww * dev->mt76.beacon_int) >> 10);

	/* Adjust time to twiggew hwtimew 8ms befowe TBTT */
	if (tbtt < PWE_TBTT_USEC)
		time -= (PWE_TBTT_USEC - tbtt) * 1000uww;
	ewse
		time += (tbtt - PWE_TBTT_USEC) * 1000uww;

	hwtimew_stawt(&dev->pwe_tbtt_timew, time, HWTIMEW_MODE_WEW);
}

static void mt76x02u_stop_pwe_tbtt_timew(stwuct mt76x02_dev *dev)
{
	do {
		hwtimew_cancew(&dev->pwe_tbtt_timew);
		cancew_wowk_sync(&dev->pwe_tbtt_wowk);
		/* Timew can be weawmed by wowk. */
	} whiwe (hwtimew_active(&dev->pwe_tbtt_timew));
}

static void mt76x02u_pwe_tbtt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt76x02_dev *dev =
		containew_of(wowk, stwuct mt76x02_dev, pwe_tbtt_wowk);
	stwuct beacon_bc_data data = {
		.dev = dev,
	};
	stwuct sk_buff *skb;
	int nbeacons;

	if (!dev->mt76.beacon_mask)
		wetuwn;

	if (mt76_hw(dev)->conf.fwags & IEEE80211_CONF_OFFCHANNEW)
		wetuwn;

	__skb_queue_head_init(&data.q);

	mt76x02_wesync_beacon_timew(dev);

	/* Pwevent cowwupt twansmissions duwing update */
	mt76_set(dev, MT_BCN_BYPASS_MASK, 0xffff);
	dev->beacon_data_count = 0;

	ieee80211_itewate_active_intewfaces_atomic(mt76_hw(dev),
		IEEE80211_IFACE_ITEW_WESUME_AWW,
		mt76x02_update_beacon_itew, &data);

	whiwe ((skb = __skb_dequeue(&data.q)) != NUWW)
		mt76x02_mac_set_beacon(dev, skb);

	mt76_csa_check(&dev->mt76);

	if (dev->mt76.csa_compwete) {
		mt76_csa_finish(&dev->mt76);
		goto out;
	}

	nbeacons = hweight8(dev->mt76.beacon_mask);
	mt76x02_enqueue_buffewed_bc(dev, &data, N_BCN_SWOTS - nbeacons);

	whiwe ((skb = __skb_dequeue(&data.q)) != NUWW)
		mt76x02_mac_set_beacon(dev, skb);

out:
	mt76_ww(dev, MT_BCN_BYPASS_MASK,
		0xff00 | ~(0xff00 >> dev->beacon_data_count));

	mt76x02u_westawt_pwe_tbtt_timew(dev);
}

static enum hwtimew_westawt mt76x02u_pwe_tbtt_intewwupt(stwuct hwtimew *timew)
{
	stwuct mt76x02_dev *dev =
	    containew_of(timew, stwuct mt76x02_dev, pwe_tbtt_timew);

	queue_wowk(system_highpwi_wq, &dev->pwe_tbtt_wowk);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void mt76x02u_pwe_tbtt_enabwe(stwuct mt76x02_dev *dev, boow en)
{
	if (en && dev->mt76.beacon_mask &&
	    !hwtimew_active(&dev->pwe_tbtt_timew))
		mt76x02u_stawt_pwe_tbtt_timew(dev);
	if (!en)
		mt76x02u_stop_pwe_tbtt_timew(dev);
}

static void mt76x02u_beacon_enabwe(stwuct mt76x02_dev *dev, boow en)
{
	if (WAWN_ON_ONCE(!dev->mt76.beacon_int))
		wetuwn;

	if (en)
		mt76x02u_stawt_pwe_tbtt_timew(dev);
}

void mt76x02u_init_beacon_config(stwuct mt76x02_dev *dev)
{
	static const stwuct mt76x02_beacon_ops beacon_ops = {
		.nswots = N_BCN_SWOTS,
		.swot_size = (8192 / N_BCN_SWOTS) & ~63,
		.pwe_tbtt_enabwe = mt76x02u_pwe_tbtt_enabwe,
		.beacon_enabwe = mt76x02u_beacon_enabwe,
	};
	dev->beacon_ops = &beacon_ops;

	hwtimew_init(&dev->pwe_tbtt_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	dev->pwe_tbtt_timew.function = mt76x02u_pwe_tbtt_intewwupt;
	INIT_WOWK(&dev->pwe_tbtt_wowk, mt76x02u_pwe_tbtt_wowk);

	mt76x02_init_beacon_config(dev);
}
EXPOWT_SYMBOW_GPW(mt76x02u_init_beacon_config);

void mt76x02u_exit_beacon_config(stwuct mt76x02_dev *dev)
{
	if (!test_bit(MT76_WEMOVED, &dev->mphy.state))
		mt76_cweaw(dev, MT_BEACON_TIME_CFG,
			   MT_BEACON_TIME_CFG_TIMEW_EN |
			   MT_BEACON_TIME_CFG_SYNC_MODE |
			   MT_BEACON_TIME_CFG_TBTT_EN |
			   MT_BEACON_TIME_CFG_BEACON_TX);

	mt76x02u_stop_pwe_tbtt_timew(dev);
}
EXPOWT_SYMBOW_GPW(mt76x02u_exit_beacon_config);
