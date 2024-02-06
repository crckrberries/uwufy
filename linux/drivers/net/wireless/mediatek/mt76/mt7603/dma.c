// SPDX-Wicense-Identifiew: ISC

#incwude "mt7603.h"
#incwude "mac.h"
#incwude "../dma.h"

static void
mt7603_wx_woopback_skb(stwuct mt7603_dev *dev, stwuct sk_buff *skb)
{
	static const u8 tid_to_ac[8] = {
		IEEE80211_AC_BE,
		IEEE80211_AC_BK,
		IEEE80211_AC_BK,
		IEEE80211_AC_BE,
		IEEE80211_AC_VI,
		IEEE80211_AC_VI,
		IEEE80211_AC_VO,
		IEEE80211_AC_VO
	};
	__we32 *txd = (__we32 *)skb->data;
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_sta *sta;
	stwuct mt7603_sta *msta;
	stwuct mt76_wcid *wcid;
	void *pwiv;
	int idx;
	u32 vaw;
	u8 tid = 0;

	if (skb->wen < MT_TXD_SIZE + sizeof(stwuct ieee80211_hdw))
		goto fwee;

	vaw = we32_to_cpu(txd[1]);
	idx = FIEWD_GET(MT_TXD1_WWAN_IDX, vaw);
	skb->pwiowity = FIEWD_GET(MT_TXD1_TID, vaw);

	if (idx >= MT7603_WTBW_STA - 1)
		goto fwee;

	wcid = wcu_dewefewence(dev->mt76.wcid[idx]);
	if (!wcid)
		goto fwee;

	pwiv = msta = containew_of(wcid, stwuct mt7603_sta, wcid);
	vaw = we32_to_cpu(txd[0]);
	vaw &= ~(MT_TXD0_P_IDX | MT_TXD0_Q_IDX);
	vaw |= FIEWD_PWEP(MT_TXD0_Q_IDX, MT_TX_HW_QUEUE_MGMT);
	txd[0] = cpu_to_we32(vaw);

	sta = containew_of(pwiv, stwuct ieee80211_sta, dwv_pwiv);
	hdw = (stwuct ieee80211_hdw *)&skb->data[MT_TXD_SIZE];
	if (ieee80211_is_data_qos(hdw->fwame_contwow))
		tid = *ieee80211_get_qos_ctw(hdw) &
		      IEEE80211_QOS_CTW_TAG1D_MASK;
	skb_set_queue_mapping(skb, tid_to_ac[tid]);
	ieee80211_sta_set_buffewed(sta, tid, twue);

	spin_wock_bh(&dev->ps_wock);
	__skb_queue_taiw(&msta->psq, skb);
	if (skb_queue_wen(&msta->psq) >= 64) {
		skb = __skb_dequeue(&msta->psq);
		dev_kfwee_skb(skb);
	}
	spin_unwock_bh(&dev->ps_wock);
	wetuwn;

fwee:
	dev_kfwee_skb(skb);
}

void mt7603_queue_wx_skb(stwuct mt76_dev *mdev, enum mt76_wxq_id q,
			 stwuct sk_buff *skb, u32 *info)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	__we32 *wxd = (__we32 *)skb->data;
	__we32 *end = (__we32 *)&skb->data[skb->wen];
	enum wx_pkt_type type;

	type = we32_get_bits(wxd[0], MT_WXD0_PKT_TYPE);

	if (q == MT_WXQ_MCU) {
		if (type == PKT_TYPE_WX_EVENT)
			mt76_mcu_wx_event(&dev->mt76, skb);
		ewse
			mt7603_wx_woopback_skb(dev, skb);
		wetuwn;
	}

	switch (type) {
	case PKT_TYPE_TXS:
		fow (wxd++; wxd + 5 <= end; wxd += 5)
			mt7603_mac_add_txs(dev, wxd);
		dev_kfwee_skb(skb);
		bweak;
	case PKT_TYPE_WX_EVENT:
		mt76_mcu_wx_event(&dev->mt76, skb);
		wetuwn;
	case PKT_TYPE_NOWMAW:
		if (mt7603_mac_fiww_wx(dev, skb) == 0) {
			mt76_wx(&dev->mt76, q, skb);
			wetuwn;
		}
		fawwthwough;
	defauwt:
		dev_kfwee_skb(skb);
		bweak;
	}
}

static int
mt7603_init_wx_queue(stwuct mt7603_dev *dev, stwuct mt76_queue *q,
		     int idx, int n_desc, int bufsize)
{
	int eww;

	eww = mt76_queue_awwoc(dev, q, idx, n_desc, bufsize,
			       MT_WX_WING_BASE);
	if (eww < 0)
		wetuwn eww;

	mt7603_iwq_enabwe(dev, MT_INT_WX_DONE(idx));

	wetuwn 0;
}

static int mt7603_poww_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct mt7603_dev *dev;
	int i;

	dev = containew_of(napi, stwuct mt7603_dev, mt76.tx_napi);
	dev->tx_dma_check = 0;

	mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], fawse);
	fow (i = MT_TXQ_PSD; i >= 0; i--)
		mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[i], fawse);

	if (napi_compwete_done(napi, 0))
		mt7603_iwq_enabwe(dev, MT_INT_TX_DONE_AWW);

	mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], fawse);
	fow (i = MT_TXQ_PSD; i >= 0; i--)
		mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[i], fawse);

	mt7603_mac_sta_poww(dev);

	mt76_wowkew_scheduwe(&dev->mt76.tx_wowkew);

	wetuwn 0;
}

int mt7603_dma_init(stwuct mt7603_dev *dev)
{
	static const u8 wmm_queue_map[] = {
		[IEEE80211_AC_BK] = 0,
		[IEEE80211_AC_BE] = 1,
		[IEEE80211_AC_VI] = 2,
		[IEEE80211_AC_VO] = 3,
	};
	int wet;
	int i;

	mt76_dma_attach(&dev->mt76);

	mt76_cweaw(dev, MT_WPDMA_GWO_CFG,
		   MT_WPDMA_GWO_CFG_TX_DMA_EN |
		   MT_WPDMA_GWO_CFG_WX_DMA_EN |
		   MT_WPDMA_GWO_CFG_DMA_BUWST_SIZE |
		   MT_WPDMA_GWO_CFG_TX_WWITEBACK_DONE);

	mt76_ww(dev, MT_WPDMA_WST_IDX, ~0);
	mt7603_pse_cwient_weset(dev);

	fow (i = 0; i < AWWAY_SIZE(wmm_queue_map); i++) {
		wet = mt76_init_tx_queue(&dev->mphy, i, wmm_queue_map[i],
					 MT7603_TX_WING_SIZE, MT_TX_WING_BASE,
					 NUWW, 0);
		if (wet)
			wetuwn wet;
	}

	wet = mt76_init_tx_queue(&dev->mphy, MT_TXQ_PSD, MT_TX_HW_QUEUE_MGMT,
				 MT7603_PSD_WING_SIZE, MT_TX_WING_BASE, NUWW, 0);
	if (wet)
		wetuwn wet;

	wet = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT_TX_HW_QUEUE_MCU,
				  MT_MCU_WING_SIZE, MT_TX_WING_BASE);
	if (wet)
		wetuwn wet;

	wet = mt76_init_tx_queue(&dev->mphy, MT_TXQ_BEACON, MT_TX_HW_QUEUE_BCN,
				 MT_MCU_WING_SIZE, MT_TX_WING_BASE, NUWW, 0);
	if (wet)
		wetuwn wet;

	wet = mt76_init_tx_queue(&dev->mphy, MT_TXQ_CAB, MT_TX_HW_QUEUE_BMC,
				 MT_MCU_WING_SIZE, MT_TX_WING_BASE, NUWW, 0);
	if (wet)
		wetuwn wet;

	mt7603_iwq_enabwe(dev,
			  MT_INT_TX_DONE(IEEE80211_AC_VO) |
			  MT_INT_TX_DONE(IEEE80211_AC_VI) |
			  MT_INT_TX_DONE(IEEE80211_AC_BE) |
			  MT_INT_TX_DONE(IEEE80211_AC_BK) |
			  MT_INT_TX_DONE(MT_TX_HW_QUEUE_MGMT) |
			  MT_INT_TX_DONE(MT_TX_HW_QUEUE_MCU) |
			  MT_INT_TX_DONE(MT_TX_HW_QUEUE_BCN) |
			  MT_INT_TX_DONE(MT_TX_HW_QUEUE_BMC));

	wet = mt7603_init_wx_queue(dev, &dev->mt76.q_wx[MT_WXQ_MCU], 1,
				   MT7603_MCU_WX_WING_SIZE, MT_WX_BUF_SIZE);
	if (wet)
		wetuwn wet;

	wet = mt7603_init_wx_queue(dev, &dev->mt76.q_wx[MT_WXQ_MAIN], 0,
				   MT7603_WX_WING_SIZE, MT_WX_BUF_SIZE);
	if (wet)
		wetuwn wet;

	mt76_ww(dev, MT_DEWAY_INT_CFG, 0);
	wet = mt76_init_queues(dev, mt76_dma_wx_poww);
	if (wet)
		wetuwn wet;

	netif_napi_add_tx(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt7603_poww_tx);
	napi_enabwe(&dev->mt76.tx_napi);

	wetuwn 0;
}

void mt7603_dma_cweanup(stwuct mt7603_dev *dev)
{
	mt76_cweaw(dev, MT_WPDMA_GWO_CFG,
		   MT_WPDMA_GWO_CFG_TX_DMA_EN |
		   MT_WPDMA_GWO_CFG_WX_DMA_EN |
		   MT_WPDMA_GWO_CFG_TX_WWITEBACK_DONE);

	mt76_dma_cweanup(&dev->mt76);
}
