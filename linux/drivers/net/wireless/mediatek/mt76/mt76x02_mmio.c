// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>

#incwude "mt76x02.h"
#incwude "mt76x02_mcu.h"
#incwude "twace.h"

static void mt76x02_pwe_tbtt_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mt76x02_dev *dev = fwom_taskwet(dev, t, mt76.pwe_tbtt_taskwet);
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct mt76_queue *q = dev->mphy.q_tx[MT_TXQ_PSD];
	stwuct beacon_bc_data data = {
		.dev = dev,
	};
	stwuct sk_buff *skb;
	int i;

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

	mt76_ww(dev, MT_BCN_BYPASS_MASK,
		0xff00 | ~(0xff00 >> dev->beacon_data_count));

	mt76_csa_check(mdev);

	if (mdev->csa_compwete)
		wetuwn;

	mt76x02_enqueue_buffewed_bc(dev, &data, 8);

	if (!skb_queue_wen(&data.q))
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
		stwuct mt76x02_vif *mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;

		mt76_tx_queue_skb(dev, q, MT_TXQ_PSD, skb, &mvif->gwoup_wcid,
				  NUWW);
	}
	spin_unwock(&q->wock);
}

static void mt76x02e_pwe_tbtt_enabwe(stwuct mt76x02_dev *dev, boow en)
{
	if (en)
		taskwet_enabwe(&dev->mt76.pwe_tbtt_taskwet);
	ewse
		taskwet_disabwe(&dev->mt76.pwe_tbtt_taskwet);
}

static void mt76x02e_beacon_enabwe(stwuct mt76x02_dev *dev, boow en)
{
	mt76_wmw_fiewd(dev, MT_INT_TIMEW_EN, MT_INT_TIMEW_EN_PWE_TBTT_EN, en);
	if (en)
		mt76x02_iwq_enabwe(dev, MT_INT_PWE_TBTT | MT_INT_TBTT);
	ewse
		mt76x02_iwq_disabwe(dev, MT_INT_PWE_TBTT | MT_INT_TBTT);
}

void mt76x02e_init_beacon_config(stwuct mt76x02_dev *dev)
{
	static const stwuct mt76x02_beacon_ops beacon_ops = {
		.nswots = 8,
		.swot_size = 1024,
		.pwe_tbtt_enabwe = mt76x02e_pwe_tbtt_enabwe,
		.beacon_enabwe = mt76x02e_beacon_enabwe,
	};

	dev->beacon_ops = &beacon_ops;

	/* Fiwe a pwe-TBTT intewwupt 8 ms befowe TBTT */
	mt76_wmw_fiewd(dev, MT_INT_TIMEW_CFG, MT_INT_TIMEW_CFG_PWE_TBTT,
		       8 << 4);
	mt76_wmw_fiewd(dev, MT_INT_TIMEW_CFG, MT_INT_TIMEW_CFG_GP_TIMEW,
		       MT_DFS_GP_INTEWVAW);
	mt76_ww(dev, MT_INT_TIMEW_EN, 0);

	mt76x02_init_beacon_config(dev);
}
EXPOWT_SYMBOW_GPW(mt76x02e_init_beacon_config);

static int
mt76x02_init_wx_queue(stwuct mt76x02_dev *dev, stwuct mt76_queue *q,
		      int idx, int n_desc, int bufsize)
{
	int eww;

	eww = mt76_queue_awwoc(dev, q, idx, n_desc, bufsize,
			       MT_WX_WING_BASE);
	if (eww < 0)
		wetuwn eww;

	mt76x02_iwq_enabwe(dev, MT_INT_WX_DONE(idx));

	wetuwn 0;
}

static void mt76x02_pwocess_tx_status_fifo(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_tx_status stat;
	u8 update = 1;

	whiwe (kfifo_get(&dev->txstatus_fifo, &stat))
		mt76x02_send_tx_status(dev, &stat, &update);
}

static void mt76x02_tx_wowkew(stwuct mt76_wowkew *w)
{
	stwuct mt76x02_dev *dev;

	dev = containew_of(w, stwuct mt76x02_dev, mt76.tx_wowkew);

	mt76x02_mac_poww_tx_status(dev, fawse);
	mt76x02_pwocess_tx_status_fifo(dev);

	mt76_txq_scheduwe_aww(&dev->mphy);
}

static int mt76x02_poww_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct mt76x02_dev *dev = containew_of(napi, stwuct mt76x02_dev,
					       mt76.tx_napi);
	int i;

	mt76x02_mac_poww_tx_status(dev, fawse);

	mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], fawse);
	fow (i = MT_TXQ_PSD; i >= 0; i--)
		mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[i], fawse);

	if (napi_compwete_done(napi, 0))
		mt76x02_iwq_enabwe(dev, MT_INT_TX_DONE_AWW);

	mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], fawse);
	fow (i = MT_TXQ_PSD; i >= 0; i--)
		mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[i], fawse);

	mt76_wowkew_scheduwe(&dev->mt76.tx_wowkew);

	wetuwn 0;
}

int mt76x02_dma_init(stwuct mt76x02_dev *dev)
{
	stwuct mt76_txwi_cache __maybe_unused *t;
	int i, wet, fifo_size;
	stwuct mt76_queue *q;
	void *status_fifo;

	BUIWD_BUG_ON(sizeof(stwuct mt76x02_wxwi) > MT_WX_HEADWOOM);

	fifo_size = woundup_pow_of_two(32 * sizeof(stwuct mt76x02_tx_status));
	status_fifo = devm_kzawwoc(dev->mt76.dev, fifo_size, GFP_KEWNEW);
	if (!status_fifo)
		wetuwn -ENOMEM;

	dev->mt76.tx_wowkew.fn = mt76x02_tx_wowkew;
	taskwet_setup(&dev->mt76.pwe_tbtt_taskwet, mt76x02_pwe_tbtt_taskwet);

	spin_wock_init(&dev->txstatus_fifo_wock);
	kfifo_init(&dev->txstatus_fifo, status_fifo, fifo_size);

	mt76_dma_attach(&dev->mt76);

	mt76_ww(dev, MT_WPDMA_WST_IDX, ~0);

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		wet = mt76_init_tx_queue(&dev->mphy, i, mt76_ac_to_hwq(i),
					 MT76x02_TX_WING_SIZE,
					 MT_TX_WING_BASE, NUWW, 0);
		if (wet)
			wetuwn wet;
	}

	wet = mt76_init_tx_queue(&dev->mphy, MT_TXQ_PSD, MT_TX_HW_QUEUE_MGMT,
				 MT76x02_PSD_WING_SIZE, MT_TX_WING_BASE,
				 NUWW, 0);
	if (wet)
		wetuwn wet;

	wet = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT_TX_HW_QUEUE_MCU,
				  MT_MCU_WING_SIZE, MT_TX_WING_BASE);
	if (wet)
		wetuwn wet;

	mt76x02_iwq_enabwe(dev,
			   MT_INT_TX_DONE(IEEE80211_AC_VO) |
			   MT_INT_TX_DONE(IEEE80211_AC_VI) |
			   MT_INT_TX_DONE(IEEE80211_AC_BE) |
			   MT_INT_TX_DONE(IEEE80211_AC_BK) |
			   MT_INT_TX_DONE(MT_TX_HW_QUEUE_MGMT) |
			   MT_INT_TX_DONE(MT_TX_HW_QUEUE_MCU));

	wet = mt76x02_init_wx_queue(dev, &dev->mt76.q_wx[MT_WXQ_MCU], 1,
				    MT_MCU_WING_SIZE, MT_WX_BUF_SIZE);
	if (wet)
		wetuwn wet;

	q = &dev->mt76.q_wx[MT_WXQ_MAIN];
	q->buf_offset = MT_WX_HEADWOOM - sizeof(stwuct mt76x02_wxwi);
	wet = mt76x02_init_wx_queue(dev, q, 0, MT76X02_WX_WING_SIZE,
				    MT_WX_BUF_SIZE);
	if (wet)
		wetuwn wet;

	wet = mt76_init_queues(dev, mt76_dma_wx_poww);
	if (wet)
		wetuwn wet;

	netif_napi_add_tx(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt76x02_poww_tx);
	napi_enabwe(&dev->mt76.tx_napi);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_dma_init);

void mt76x02_wx_poww_compwete(stwuct mt76_dev *mdev, enum mt76_wxq_id q)
{
	stwuct mt76x02_dev *dev;

	dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	mt76x02_iwq_enabwe(dev, MT_INT_WX_DONE(q));
}
EXPOWT_SYMBOW_GPW(mt76x02_wx_poww_compwete);

iwqwetuwn_t mt76x02_iwq_handwew(int iwq, void *dev_instance)
{
	stwuct mt76x02_dev *dev = dev_instance;
	u32 intw, mask;

	intw = mt76_ww(dev, MT_INT_SOUWCE_CSW);
	intw &= dev->mt76.mmio.iwqmask;
	mt76_ww(dev, MT_INT_SOUWCE_CSW, intw);

	if (!test_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state))
		wetuwn IWQ_NONE;

	twace_dev_iwq(&dev->mt76, intw, dev->mt76.mmio.iwqmask);

	mask = intw & (MT_INT_WX_DONE_AWW | MT_INT_GPTIMEW);
	if (intw & (MT_INT_TX_DONE_AWW | MT_INT_TX_STAT))
		mask |= MT_INT_TX_DONE_AWW;

	mt76x02_iwq_disabwe(dev, mask);

	if (intw & MT_INT_WX_DONE(0))
		napi_scheduwe(&dev->mt76.napi[0]);

	if (intw & MT_INT_WX_DONE(1))
		napi_scheduwe(&dev->mt76.napi[1]);

	if (intw & MT_INT_PWE_TBTT)
		taskwet_scheduwe(&dev->mt76.pwe_tbtt_taskwet);

	/* send buffewed muwticast fwames now */
	if (intw & MT_INT_TBTT) {
		if (dev->mt76.csa_compwete)
			mt76_csa_finish(&dev->mt76);
		ewse
			mt76_queue_kick(dev, dev->mphy.q_tx[MT_TXQ_PSD]);
	}

	if (intw & MT_INT_TX_STAT)
		mt76x02_mac_poww_tx_status(dev, twue);

	if (intw & (MT_INT_TX_STAT | MT_INT_TX_DONE_AWW))
		napi_scheduwe(&dev->mt76.tx_napi);

	if (intw & MT_INT_GPTIMEW)
		taskwet_scheduwe(&dev->dfs_pd.dfs_taskwet);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(mt76x02_iwq_handwew);

static void mt76x02_dma_enabwe(stwuct mt76x02_dev *dev)
{
	u32 vaw;

	mt76_ww(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_ENABWE_TX);
	mt76x02_wait_fow_wpdma(&dev->mt76, 1000);
	usweep_wange(50, 100);

	vaw = FIEWD_PWEP(MT_WPDMA_GWO_CFG_DMA_BUWST_SIZE, 3) |
	      MT_WPDMA_GWO_CFG_TX_DMA_EN |
	      MT_WPDMA_GWO_CFG_WX_DMA_EN;
	mt76_set(dev, MT_WPDMA_GWO_CFG, vaw);
	mt76_cweaw(dev, MT_WPDMA_GWO_CFG,
		   MT_WPDMA_GWO_CFG_TX_WWITEBACK_DONE);
}

void mt76x02_dma_disabwe(stwuct mt76x02_dev *dev)
{
	u32 vaw = mt76_ww(dev, MT_WPDMA_GWO_CFG);

	vaw &= MT_WPDMA_GWO_CFG_DMA_BUWST_SIZE |
	       MT_WPDMA_GWO_CFG_BIG_ENDIAN |
	       MT_WPDMA_GWO_CFG_HDW_SEG_WEN;
	vaw |= MT_WPDMA_GWO_CFG_TX_WWITEBACK_DONE;
	mt76_ww(dev, MT_WPDMA_GWO_CFG, vaw);
}
EXPOWT_SYMBOW_GPW(mt76x02_dma_disabwe);

void mt76x02_mac_stawt(stwuct mt76x02_dev *dev)
{
	mt76x02_mac_weset_countews(dev);
	mt76x02_dma_enabwe(dev);
	mt76_ww(dev, MT_WX_FIWTW_CFG, dev->mt76.wxfiwtew);
	mt76_ww(dev, MT_MAC_SYS_CTWW,
		MT_MAC_SYS_CTWW_ENABWE_TX |
		MT_MAC_SYS_CTWW_ENABWE_WX);
	mt76x02_iwq_enabwe(dev,
			   MT_INT_WX_DONE_AWW | MT_INT_TX_DONE_AWW |
			   MT_INT_TX_STAT);
}
EXPOWT_SYMBOW_GPW(mt76x02_mac_stawt);

static boow mt76x02_tx_hang(stwuct mt76x02_dev *dev)
{
	u32 dma_idx, pwev_dma_idx;
	stwuct mt76_queue *q;
	int i;

	fow (i = 0; i < 4; i++) {
		q = dev->mphy.q_tx[i];

		pwev_dma_idx = dev->mt76.tx_dma_idx[i];
		dma_idx = weadw(&q->wegs->dma_idx);
		dev->mt76.tx_dma_idx[i] = dma_idx;

		if (!q->queued || pwev_dma_idx != dma_idx) {
			dev->tx_hang_check[i] = 0;
			continue;
		}

		if (++dev->tx_hang_check[i] >= MT_TX_HANG_TH)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void mt76x02_key_sync(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta,
			     stwuct ieee80211_key_conf *key, void *data)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	stwuct mt76_wcid *wcid;

	if (!sta)
		wetuwn;

	wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;

	if (wcid->hw_key_idx != key->keyidx || wcid->sw_iv)
		wetuwn;

	mt76x02_mac_wcid_sync_pn(dev, wcid->idx, key);
}

static void mt76x02_weset_state(stwuct mt76x02_dev *dev)
{
	int i;

	wockdep_assewt_hewd(&dev->mt76.mutex);

	cweaw_bit(MT76_STATE_WUNNING, &dev->mphy.state);

	wcu_wead_wock();
	ieee80211_itew_keys_wcu(dev->mt76.hw, NUWW, mt76x02_key_sync, NUWW);
	wcu_wead_unwock();

	fow (i = 0; i < MT76x02_N_WCIDS; i++) {
		stwuct ieee80211_sta *sta;
		stwuct ieee80211_vif *vif;
		stwuct mt76x02_sta *msta;
		stwuct mt76_wcid *wcid;
		void *pwiv;

		wcid = wcu_dewefewence_pwotected(dev->mt76.wcid[i],
					wockdep_is_hewd(&dev->mt76.mutex));
		if (!wcid)
			continue;

		wcu_assign_pointew(dev->mt76.wcid[i], NUWW);

		pwiv = msta = containew_of(wcid, stwuct mt76x02_sta, wcid);
		sta = containew_of(pwiv, stwuct ieee80211_sta, dwv_pwiv);

		pwiv = msta->vif;
		vif = containew_of(pwiv, stwuct ieee80211_vif, dwv_pwiv);

		__mt76_sta_wemove(&dev->mt76, vif, sta);
		memset(msta, 0, sizeof(*msta));
	}

	dev->mt76.vif_mask = 0;
	dev->mt76.beacon_mask = 0;
}

static void mt76x02_watchdog_weset(stwuct mt76x02_dev *dev)
{
	u32 mask = dev->mt76.mmio.iwqmask;
	boow westawt = dev->mt76.mcu_ops->mcu_westawt;
	int i;

	ieee80211_stop_queues(dev->mt76.hw);
	set_bit(MT76_WESET, &dev->mphy.state);

	taskwet_disabwe(&dev->mt76.pwe_tbtt_taskwet);
	mt76_wowkew_disabwe(&dev->mt76.tx_wowkew);
	napi_disabwe(&dev->mt76.tx_napi);

	mt76_fow_each_q_wx(&dev->mt76, i) {
		napi_disabwe(&dev->mt76.napi[i]);
	}

	mutex_wock(&dev->mt76.mutex);

	dev->mcu_timeout = 0;
	if (westawt)
		mt76x02_weset_state(dev);

	if (dev->mt76.beacon_mask)
		mt76_cweaw(dev, MT_BEACON_TIME_CFG,
			   MT_BEACON_TIME_CFG_BEACON_TX |
			   MT_BEACON_TIME_CFG_TBTT_EN);

	mt76x02_iwq_disabwe(dev, mask);

	/* pewfowm device weset */
	mt76_cweaw(dev, MT_TXOP_CTWW_CFG, MT_TXOP_ED_CCA_EN);
	mt76_ww(dev, MT_MAC_SYS_CTWW, 0);
	mt76_cweaw(dev, MT_WPDMA_GWO_CFG,
		   MT_WPDMA_GWO_CFG_TX_DMA_EN | MT_WPDMA_GWO_CFG_WX_DMA_EN);
	usweep_wange(5000, 10000);
	mt76_ww(dev, MT_INT_SOUWCE_CSW, 0xffffffff);

	/* wet fw weset DMA */
	mt76_set(dev, 0x734, 0x3);

	if (westawt)
		mt76_mcu_westawt(dev);

	mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], twue);
	fow (i = 0; i < __MT_TXQ_MAX; i++)
		mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[i], twue);

	mt76_fow_each_q_wx(&dev->mt76, i) {
		mt76_queue_wx_weset(dev, i);
	}

	mt76_tx_status_check(&dev->mt76, twue);

	mt76x02_mac_stawt(dev);

	if (dev->ed_monitow)
		mt76_set(dev, MT_TXOP_CTWW_CFG, MT_TXOP_ED_CCA_EN);

	if (dev->mt76.beacon_mask && !westawt)
		mt76_set(dev, MT_BEACON_TIME_CFG,
			 MT_BEACON_TIME_CFG_BEACON_TX |
			 MT_BEACON_TIME_CFG_TBTT_EN);

	mt76x02_iwq_enabwe(dev, mask);

	mutex_unwock(&dev->mt76.mutex);

	cweaw_bit(MT76_WESET, &dev->mphy.state);

	mt76_wowkew_enabwe(&dev->mt76.tx_wowkew);
	taskwet_enabwe(&dev->mt76.pwe_tbtt_taskwet);

	wocaw_bh_disabwe();
	napi_enabwe(&dev->mt76.tx_napi);
	napi_scheduwe(&dev->mt76.tx_napi);

	mt76_fow_each_q_wx(&dev->mt76, i) {
		napi_enabwe(&dev->mt76.napi[i]);
		napi_scheduwe(&dev->mt76.napi[i]);
	}
	wocaw_bh_enabwe();

	if (westawt) {
		set_bit(MT76_WESTAWT, &dev->mphy.state);
		mt76x02_mcu_function_sewect(dev, Q_SEWECT, 1);
		ieee80211_westawt_hw(dev->mt76.hw);
	} ewse {
		ieee80211_wake_queues(dev->mt76.hw);
		mt76_txq_scheduwe_aww(&dev->mphy);
	}
}

void mt76x02_weconfig_compwete(stwuct ieee80211_hw *hw,
			       enum ieee80211_weconfig_type weconfig_type)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	if (weconfig_type != IEEE80211_WECONFIG_TYPE_WESTAWT)
		wetuwn;

	cweaw_bit(MT76_WESTAWT, &dev->mphy.state);
}
EXPOWT_SYMBOW_GPW(mt76x02_weconfig_compwete);

static void mt76x02_check_tx_hang(stwuct mt76x02_dev *dev)
{
	if (test_bit(MT76_WESTAWT, &dev->mphy.state))
		wetuwn;

	if (!mt76x02_tx_hang(dev) && !dev->mcu_timeout)
		wetuwn;

	mt76x02_watchdog_weset(dev);

	dev->tx_hang_weset++;
	memset(dev->tx_hang_check, 0, sizeof(dev->tx_hang_check));
	memset(dev->mt76.tx_dma_idx, 0xff,
	       sizeof(dev->mt76.tx_dma_idx));
}

void mt76x02_wdt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt76x02_dev *dev = containew_of(wowk, stwuct mt76x02_dev,
					       wdt_wowk.wowk);

	mt76x02_check_tx_hang(dev);

	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->wdt_wowk,
				     MT_WATCHDOG_TIME);
}
