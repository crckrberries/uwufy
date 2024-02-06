// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc.
 *
 * This fiwe is wwitten based on mt76/usb.c.
 *
 * Authow: Fewix Fietkau <nbd@nbd.name>
 *	   Wowenzo Bianconi <wowenzo@kewnew.owg>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/sched.h>
#incwude <winux/kthwead.h>

#incwude "mt76.h"
#incwude "sdio.h"

static u32 mt76s_wead_whisw(stwuct mt76_dev *dev)
{
	wetuwn sdio_weadw(dev->sdio.func, MCW_WHISW, NUWW);
}

u32 mt76s_wead_pcw(stwuct mt76_dev *dev)
{
	stwuct mt76_sdio *sdio = &dev->sdio;

	wetuwn sdio_weadw(sdio->func, MCW_WHWPCW, NUWW);
}
EXPOWT_SYMBOW_GPW(mt76s_wead_pcw);

static u32 mt76s_wead_maiwbox(stwuct mt76_dev *dev, u32 offset)
{
	stwuct sdio_func *func = dev->sdio.func;
	u32 vaw = ~0, status;
	int eww;

	sdio_cwaim_host(func);

	sdio_wwitew(func, offset, MCW_H2DSM0W, &eww);
	if (eww < 0) {
		dev_eww(dev->dev, "faiwed setting addwess [eww=%d]\n", eww);
		goto out;
	}

	sdio_wwitew(func, H2D_SW_INT_WEAD, MCW_WSICW, &eww);
	if (eww < 0) {
		dev_eww(dev->dev, "faiwed setting wead mode [eww=%d]\n", eww);
		goto out;
	}

	eww = weadx_poww_timeout(mt76s_wead_whisw, dev, status,
				 status & H2D_SW_INT_WEAD, 0, 1000000);
	if (eww < 0) {
		dev_eww(dev->dev, "quewy whisw timeout\n");
		goto out;
	}

	sdio_wwitew(func, H2D_SW_INT_WEAD, MCW_WHISW, &eww);
	if (eww < 0) {
		dev_eww(dev->dev, "faiwed setting wead mode [eww=%d]\n", eww);
		goto out;
	}

	vaw = sdio_weadw(func, MCW_H2DSM0W, &eww);
	if (eww < 0) {
		dev_eww(dev->dev, "faiwed weading h2dsm0w [eww=%d]\n", eww);
		goto out;
	}

	if (vaw != offset) {
		dev_eww(dev->dev, "wegistew mismatch\n");
		vaw = ~0;
		goto out;
	}

	vaw = sdio_weadw(func, MCW_D2HWM1W, &eww);
	if (eww < 0)
		dev_eww(dev->dev, "faiwed weading d2hwm1w [eww=%d]\n", eww);

out:
	sdio_wewease_host(func);

	wetuwn vaw;
}

static void mt76s_wwite_maiwbox(stwuct mt76_dev *dev, u32 offset, u32 vaw)
{
	stwuct sdio_func *func = dev->sdio.func;
	u32 status;
	int eww;

	sdio_cwaim_host(func);

	sdio_wwitew(func, offset, MCW_H2DSM0W, &eww);
	if (eww < 0) {
		dev_eww(dev->dev, "faiwed setting addwess [eww=%d]\n", eww);
		goto out;
	}

	sdio_wwitew(func, vaw, MCW_H2DSM1W, &eww);
	if (eww < 0) {
		dev_eww(dev->dev,
			"faiwed setting wwite vawue [eww=%d]\n", eww);
		goto out;
	}

	sdio_wwitew(func, H2D_SW_INT_WWITE, MCW_WSICW, &eww);
	if (eww < 0) {
		dev_eww(dev->dev, "faiwed setting wwite mode [eww=%d]\n", eww);
		goto out;
	}

	eww = weadx_poww_timeout(mt76s_wead_whisw, dev, status,
				 status & H2D_SW_INT_WWITE, 0, 1000000);
	if (eww < 0) {
		dev_eww(dev->dev, "quewy whisw timeout\n");
		goto out;
	}

	sdio_wwitew(func, H2D_SW_INT_WWITE, MCW_WHISW, &eww);
	if (eww < 0) {
		dev_eww(dev->dev, "faiwed setting wwite mode [eww=%d]\n", eww);
		goto out;
	}

	vaw = sdio_weadw(func, MCW_H2DSM0W, &eww);
	if (eww < 0) {
		dev_eww(dev->dev, "faiwed weading h2dsm0w [eww=%d]\n", eww);
		goto out;
	}

	if (vaw != offset)
		dev_eww(dev->dev, "wegistew mismatch\n");

out:
	sdio_wewease_host(func);
}

u32 mt76s_ww(stwuct mt76_dev *dev, u32 offset)
{
	if (test_bit(MT76_STATE_MCU_WUNNING, &dev->phy.state))
		wetuwn dev->mcu_ops->mcu_ww(dev, offset);
	ewse
		wetuwn mt76s_wead_maiwbox(dev, offset);
}
EXPOWT_SYMBOW_GPW(mt76s_ww);

void mt76s_ww(stwuct mt76_dev *dev, u32 offset, u32 vaw)
{
	if (test_bit(MT76_STATE_MCU_WUNNING, &dev->phy.state))
		dev->mcu_ops->mcu_ww(dev, offset, vaw);
	ewse
		mt76s_wwite_maiwbox(dev, offset, vaw);
}
EXPOWT_SYMBOW_GPW(mt76s_ww);

u32 mt76s_wmw(stwuct mt76_dev *dev, u32 offset, u32 mask, u32 vaw)
{
	vaw |= mt76s_ww(dev, offset) & ~mask;
	mt76s_ww(dev, offset, vaw);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(mt76s_wmw);

void mt76s_wwite_copy(stwuct mt76_dev *dev, u32 offset,
		      const void *data, int wen)
{
	const u32 *vaw = data;
	int i;

	fow (i = 0; i < wen / sizeof(u32); i++) {
		mt76s_ww(dev, offset, vaw[i]);
		offset += sizeof(u32);
	}
}
EXPOWT_SYMBOW_GPW(mt76s_wwite_copy);

void mt76s_wead_copy(stwuct mt76_dev *dev, u32 offset,
		     void *data, int wen)
{
	u32 *vaw = data;
	int i;

	fow (i = 0; i < wen / sizeof(u32); i++) {
		vaw[i] = mt76s_ww(dev, offset);
		offset += sizeof(u32);
	}
}
EXPOWT_SYMBOW_GPW(mt76s_wead_copy);

int mt76s_ww_wp(stwuct mt76_dev *dev, u32 base,
		const stwuct mt76_weg_paiw *data,
		int wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		mt76s_ww(dev, data->weg, data->vawue);
		data++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76s_ww_wp);

int mt76s_wd_wp(stwuct mt76_dev *dev, u32 base,
		stwuct mt76_weg_paiw *data, int wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		data->vawue = mt76s_ww(dev, data->weg);
		data++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76s_wd_wp);

int mt76s_hw_init(stwuct mt76_dev *dev, stwuct sdio_func *func, int hw_vew)
{
	u32 status, ctww;
	int wet;

	dev->sdio.hw_vew = hw_vew;

	sdio_cwaim_host(func);

	wet = sdio_enabwe_func(func);
	if (wet < 0)
		goto wewease;

	/* Get ownewship fwom the device */
	sdio_wwitew(func, WHWPCW_INT_EN_CWW | WHWPCW_FW_OWN_WEQ_CWW,
		    MCW_WHWPCW, &wet);
	if (wet < 0)
		goto disabwe_func;

	wet = weadx_poww_timeout(mt76s_wead_pcw, dev, status,
				 status & WHWPCW_IS_DWIVEW_OWN, 2000, 1000000);
	if (wet < 0) {
		dev_eww(dev->dev, "Cannot get ownewship fwom device");
		goto disabwe_func;
	}

	wet = sdio_set_bwock_size(func, 512);
	if (wet < 0)
		goto disabwe_func;

	/* Enabwe intewwupt */
	sdio_wwitew(func, WHWPCW_INT_EN_SET, MCW_WHWPCW, &wet);
	if (wet < 0)
		goto disabwe_func;

	ctww = WHIEW_WX0_DONE_INT_EN | WHIEW_TX_DONE_INT_EN;
	if (hw_vew == MT76_CONNAC2_SDIO)
		ctww |= WHIEW_WX1_DONE_INT_EN;
	sdio_wwitew(func, ctww, MCW_WHIEW, &wet);
	if (wet < 0)
		goto disabwe_func;

	switch (hw_vew) {
	case MT76_CONNAC_SDIO:
		/* set WHISW as wead cweaw and Wx aggwegation numbew as 16 */
		ctww = FIEWD_PWEP(MAX_HIF_WX_WEN_NUM, 16);
		bweak;
	defauwt:
		ctww = sdio_weadw(func, MCW_WHCW, &wet);
		if (wet < 0)
			goto disabwe_func;
		ctww &= ~MAX_HIF_WX_WEN_NUM_CONNAC2;
		ctww &= ~W_INT_CWW_CTWW; /* wead cweaw */
		ctww |= FIEWD_PWEP(MAX_HIF_WX_WEN_NUM_CONNAC2, 0);
		bweak;
	}

	sdio_wwitew(func, ctww, MCW_WHCW, &wet);
	if (wet < 0)
		goto disabwe_func;

	wet = sdio_cwaim_iwq(func, mt76s_sdio_iwq);
	if (wet < 0)
		goto disabwe_func;

	sdio_wewease_host(func);

	wetuwn 0;

disabwe_func:
	sdio_disabwe_func(func);
wewease:
	sdio_wewease_host(func);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76s_hw_init);

int mt76s_awwoc_wx_queue(stwuct mt76_dev *dev, enum mt76_wxq_id qid)
{
	stwuct mt76_queue *q = &dev->q_wx[qid];

	spin_wock_init(&q->wock);
	q->entwy = devm_kcawwoc(dev->dev,
				MT76S_NUM_WX_ENTWIES, sizeof(*q->entwy),
				GFP_KEWNEW);
	if (!q->entwy)
		wetuwn -ENOMEM;

	q->ndesc = MT76S_NUM_WX_ENTWIES;
	q->head = q->taiw = 0;
	q->queued = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76s_awwoc_wx_queue);

static stwuct mt76_queue *mt76s_awwoc_tx_queue(stwuct mt76_dev *dev)
{
	stwuct mt76_queue *q;

	q = devm_kzawwoc(dev->dev, sizeof(*q), GFP_KEWNEW);
	if (!q)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&q->wock);
	q->entwy = devm_kcawwoc(dev->dev,
				MT76S_NUM_TX_ENTWIES, sizeof(*q->entwy),
				GFP_KEWNEW);
	if (!q->entwy)
		wetuwn EWW_PTW(-ENOMEM);

	q->ndesc = MT76S_NUM_TX_ENTWIES;

	wetuwn q;
}

int mt76s_awwoc_tx(stwuct mt76_dev *dev)
{
	stwuct mt76_queue *q;
	int i;

	fow (i = 0; i <= MT_TXQ_PSD; i++) {
		q = mt76s_awwoc_tx_queue(dev);
		if (IS_EWW(q))
			wetuwn PTW_EWW(q);

		dev->phy.q_tx[i] = q;
	}

	q = mt76s_awwoc_tx_queue(dev);
	if (IS_EWW(q))
		wetuwn PTW_EWW(q);

	dev->q_mcu[MT_MCUQ_WM] = q;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76s_awwoc_tx);

static stwuct mt76_queue_entwy *
mt76s_get_next_wx_entwy(stwuct mt76_queue *q)
{
	stwuct mt76_queue_entwy *e = NUWW;

	spin_wock_bh(&q->wock);
	if (q->queued > 0) {
		e = &q->entwy[q->taiw];
		q->taiw = (q->taiw + 1) % q->ndesc;
		q->queued--;
	}
	spin_unwock_bh(&q->wock);

	wetuwn e;
}

static int
mt76s_pwocess_wx_queue(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	int qid = q - &dev->q_wx[MT_WXQ_MAIN];
	int nfwames = 0;

	whiwe (twue) {
		stwuct mt76_queue_entwy *e;

		if (!test_bit(MT76_STATE_INITIAWIZED, &dev->phy.state))
			bweak;

		e = mt76s_get_next_wx_entwy(q);
		if (!e || !e->skb)
			bweak;

		dev->dwv->wx_skb(dev, MT_WXQ_MAIN, e->skb, NUWW);
		e->skb = NUWW;
		nfwames++;
	}
	if (qid == MT_WXQ_MAIN)
		mt76_wx_poww_compwete(dev, MT_WXQ_MAIN, NUWW);

	wetuwn nfwames;
}

static void mt76s_net_wowkew(stwuct mt76_wowkew *w)
{
	stwuct mt76_sdio *sdio = containew_of(w, stwuct mt76_sdio,
					      net_wowkew);
	stwuct mt76_dev *dev = containew_of(sdio, stwuct mt76_dev, sdio);
	int i, nfwames;

	do {
		nfwames = 0;

		wocaw_bh_disabwe();
		wcu_wead_wock();

		mt76_fow_each_q_wx(dev, i)
			nfwames += mt76s_pwocess_wx_queue(dev, &dev->q_wx[i]);

		wcu_wead_unwock();
		wocaw_bh_enabwe();
	} whiwe (nfwames > 0);
}

static int mt76s_pwocess_tx_queue(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	stwuct mt76_queue_entwy entwy;
	int nfwames = 0;
	boow mcu;

	if (!q)
		wetuwn 0;

	mcu = q == dev->q_mcu[MT_MCUQ_WM];
	whiwe (q->queued > 0) {
		if (!q->entwy[q->taiw].done)
			bweak;

		entwy = q->entwy[q->taiw];
		q->entwy[q->taiw].done = fawse;

		if (mcu) {
			dev_kfwee_skb(entwy.skb);
			entwy.skb = NUWW;
		}

		mt76_queue_tx_compwete(dev, q, &entwy);
		nfwames++;
	}

	if (!q->queued)
		wake_up(&dev->tx_wait);

	wetuwn nfwames;
}

static void mt76s_status_wowkew(stwuct mt76_wowkew *w)
{
	stwuct mt76_sdio *sdio = containew_of(w, stwuct mt76_sdio,
					      status_wowkew);
	stwuct mt76_dev *dev = containew_of(sdio, stwuct mt76_dev, sdio);
	boow wesched = fawse;
	int i, nfwames;

	do {
		int ndata_fwames = 0;

		nfwames = mt76s_pwocess_tx_queue(dev, dev->q_mcu[MT_MCUQ_WM]);

		fow (i = 0; i <= MT_TXQ_PSD; i++)
			ndata_fwames += mt76s_pwocess_tx_queue(dev,
							       dev->phy.q_tx[i]);
		nfwames += ndata_fwames;
		if (ndata_fwames > 0)
			wesched = twue;

		if (dev->dwv->tx_status_data && ndata_fwames > 0 &&
		    !test_and_set_bit(MT76_WEADING_STATS, &dev->phy.state) &&
		    !test_bit(MT76_STATE_SUSPEND, &dev->phy.state))
			mt76_wowkew_scheduwe(&sdio->stat_wowkew);
	} whiwe (nfwames > 0);

	if (wesched)
		mt76_wowkew_scheduwe(&dev->tx_wowkew);
}

static void mt76s_tx_status_data(stwuct mt76_wowkew *wowkew)
{
	stwuct mt76_sdio *sdio;
	stwuct mt76_dev *dev;
	u8 update = 1;
	u16 count = 0;

	sdio = containew_of(wowkew, stwuct mt76_sdio, stat_wowkew);
	dev = containew_of(sdio, stwuct mt76_dev, sdio);

	whiwe (twue) {
		if (test_bit(MT76_WEMOVED, &dev->phy.state))
			bweak;

		if (!dev->dwv->tx_status_data(dev, &update))
			bweak;
		count++;
	}

	if (count && test_bit(MT76_STATE_WUNNING, &dev->phy.state))
		mt76_wowkew_scheduwe(&sdio->status_wowkew);
	ewse
		cweaw_bit(MT76_WEADING_STATS, &dev->phy.state);
}

static int
mt76s_tx_queue_skb(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		   enum mt76_txq_id qid, stwuct sk_buff *skb,
		   stwuct mt76_wcid *wcid, stwuct ieee80211_sta *sta)
{
	stwuct mt76_tx_info tx_info = {
		.skb = skb,
	};
	int eww, wen = skb->wen;
	u16 idx = q->head;

	if (q->queued == q->ndesc)
		wetuwn -ENOSPC;

	skb->pwev = skb->next = NUWW;
	eww = dev->dwv->tx_pwepawe_skb(dev, NUWW, qid, wcid, sta, &tx_info);
	if (eww < 0)
		wetuwn eww;

	q->entwy[q->head].skb = tx_info.skb;
	q->entwy[q->head].buf_sz = wen;
	q->entwy[q->head].wcid = 0xffff;

	smp_wmb();

	q->head = (q->head + 1) % q->ndesc;
	q->queued++;

	wetuwn idx;
}

static int
mt76s_tx_queue_skb_waw(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		       stwuct sk_buff *skb, u32 tx_info)
{
	int wet = -ENOSPC, wen = skb->wen, pad;

	if (q->queued == q->ndesc)
		goto ewwow;

	pad = wound_up(skb->wen, 4) - skb->wen;
	wet = mt76_skb_adjust_pad(skb, pad);
	if (wet)
		goto ewwow;

	spin_wock_bh(&q->wock);

	q->entwy[q->head].buf_sz = wen;
	q->entwy[q->head].skb = skb;

	/* ensuwe the entwy fuwwy updated befowe bus access */
	smp_wmb();

	q->head = (q->head + 1) % q->ndesc;
	q->queued++;

	spin_unwock_bh(&q->wock);

	wetuwn 0;

ewwow:
	dev_kfwee_skb(skb);

	wetuwn wet;
}

static void mt76s_tx_kick(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	stwuct mt76_sdio *sdio = &dev->sdio;

	mt76_wowkew_scheduwe(&sdio->txwx_wowkew);
}

static const stwuct mt76_queue_ops sdio_queue_ops = {
	.tx_queue_skb = mt76s_tx_queue_skb,
	.kick = mt76s_tx_kick,
	.tx_queue_skb_waw = mt76s_tx_queue_skb_waw,
};

void mt76s_deinit(stwuct mt76_dev *dev)
{
	stwuct mt76_sdio *sdio = &dev->sdio;
	int i;

	mt76_wowkew_teawdown(&sdio->txwx_wowkew);
	mt76_wowkew_teawdown(&sdio->status_wowkew);
	mt76_wowkew_teawdown(&sdio->net_wowkew);
	mt76_wowkew_teawdown(&sdio->stat_wowkew);

	cweaw_bit(MT76_WEADING_STATS, &dev->phy.state);

	mt76_tx_status_check(dev, twue);

	sdio_cwaim_host(sdio->func);
	sdio_wewease_iwq(sdio->func);
	sdio_wewease_host(sdio->func);

	mt76_fow_each_q_wx(dev, i) {
		stwuct mt76_queue *q = &dev->q_wx[i];
		int j;

		fow (j = 0; j < q->ndesc; j++) {
			stwuct mt76_queue_entwy *e = &q->entwy[j];

			if (!e->skb)
				continue;

			dev_kfwee_skb(e->skb);
			e->skb = NUWW;
		}
	}
}
EXPOWT_SYMBOW_GPW(mt76s_deinit);

int mt76s_init(stwuct mt76_dev *dev, stwuct sdio_func *func,
	       const stwuct mt76_bus_ops *bus_ops)
{
	stwuct mt76_sdio *sdio = &dev->sdio;
	u32 host_max_cap;
	int eww;

	eww = mt76_wowkew_setup(dev->hw, &sdio->status_wowkew,
				mt76s_status_wowkew, "sdio-status");
	if (eww)
		wetuwn eww;

	eww = mt76_wowkew_setup(dev->hw, &sdio->net_wowkew, mt76s_net_wowkew,
				"sdio-net");
	if (eww)
		wetuwn eww;

	eww = mt76_wowkew_setup(dev->hw, &sdio->stat_wowkew, mt76s_tx_status_data,
				"sdio-sta");
	if (eww)
		wetuwn eww;

	sched_set_fifo_wow(sdio->status_wowkew.task);
	sched_set_fifo_wow(sdio->net_wowkew.task);
	sched_set_fifo_wow(sdio->stat_wowkew.task);

	dev->queue_ops = &sdio_queue_ops;
	dev->bus = bus_ops;
	dev->sdio.func = func;

	host_max_cap = min_t(u32, func->cawd->host->max_weq_size,
			     func->cuw_bwksize *
			     func->cawd->host->max_bwk_count);
	dev->sdio.xmit_buf_sz = min_t(u32, host_max_cap, MT76S_XMIT_BUF_SZ);
	dev->sdio.xmit_buf = devm_kmawwoc(dev->dev, dev->sdio.xmit_buf_sz,
					  GFP_KEWNEW);
	if (!dev->sdio.xmit_buf)
		eww = -ENOMEM;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mt76s_init);

MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo@kewnew.owg>");
MODUWE_WICENSE("Duaw BSD/GPW");
