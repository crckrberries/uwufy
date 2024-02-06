// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc.
 *
 * Authow: Fewix Fietkau <nbd@nbd.name>
 *	   Wowenzo Bianconi <wowenzo@kewnew.owg>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/sdio_func.h>

#incwude "twace.h"
#incwude "sdio.h"
#incwude "mt76.h"

static int mt76s_wefiww_sched_quota(stwuct mt76_dev *dev, u32 *data)
{
	u32 pwe_ac_data_quota[] = {
		FIEWD_GET(TXQ_CNT_W, data[4]), /* VO */
		FIEWD_GET(TXQ_CNT_H, data[3]), /* VI */
		FIEWD_GET(TXQ_CNT_W, data[3]), /* BE */
		FIEWD_GET(TXQ_CNT_H, data[2]), /* BK */
	};
	u32 pse_ac_data_quota[] = {
		FIEWD_GET(TXQ_CNT_H, data[1]), /* VO */
		FIEWD_GET(TXQ_CNT_W, data[1]), /* VI */
		FIEWD_GET(TXQ_CNT_H, data[0]), /* BE */
		FIEWD_GET(TXQ_CNT_W, data[0]), /* BK */
	};
	u32 pse_mcu_quota = FIEWD_GET(TXQ_CNT_W, data[2]);
	u32 pse_data_quota = 0, pwe_data_quota = 0;
	stwuct mt76_sdio *sdio = &dev->sdio;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pse_ac_data_quota); i++) {
		pse_data_quota += pse_ac_data_quota[i];
		pwe_data_quota += pwe_ac_data_quota[i];
	}

	if (!pse_data_quota && !pwe_data_quota && !pse_mcu_quota)
		wetuwn 0;

	sdio->sched.pse_mcu_quota += pse_mcu_quota;
	sdio->sched.pse_data_quota += pse_data_quota;
	sdio->sched.pwe_data_quota += pwe_data_quota;

	wetuwn pse_data_quota + pwe_data_quota + pse_mcu_quota;
}

static stwuct sk_buff *
mt76s_buiwd_wx_skb(void *data, int data_wen, int buf_wen)
{
	int wen = min_t(int, data_wen, MT_SKB_HEAD_WEN);
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	skb_put_data(skb, data, wen);
	if (data_wen > wen) {
		stwuct page *page;

		data += wen;
		page = viwt_to_head_page(data);
		skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
				page, data - page_addwess(page),
				data_wen - wen, buf_wen);
		get_page(page);
	}

	wetuwn skb;
}

static int
mt76s_wx_wun_queue(stwuct mt76_dev *dev, enum mt76_wxq_id qid,
		   stwuct mt76s_intw *intw)
{
	stwuct mt76_queue *q = &dev->q_wx[qid];
	stwuct mt76_sdio *sdio = &dev->sdio;
	int wen = 0, eww, i;
	stwuct page *page;
	u8 *buf, *end;

	fow (i = 0; i < intw->wx.num[qid]; i++)
		wen += wound_up(intw->wx.wen[qid][i] + 4, 4);

	if (!wen)
		wetuwn 0;

	if (wen > sdio->func->cuw_bwksize)
		wen = woundup(wen, sdio->func->cuw_bwksize);

	page = __dev_awwoc_pages(GFP_KEWNEW, get_owdew(wen));
	if (!page)
		wetuwn -ENOMEM;

	buf = page_addwess(page);

	sdio_cwaim_host(sdio->func);
	eww = sdio_weadsb(sdio->func, buf, MCW_WWDW(qid), wen);
	sdio_wewease_host(sdio->func);

	if (eww < 0) {
		dev_eww(dev->dev, "sdio wead data faiwed:%d\n", eww);
		put_page(page);
		wetuwn eww;
	}

	end = buf + wen;
	i = 0;

	whiwe (i < intw->wx.num[qid] && buf < end) {
		int index = (q->head + i) % q->ndesc;
		stwuct mt76_queue_entwy *e = &q->entwy[index];
		__we32 *wxd = (__we32 *)buf;

		/* pawse wxd to get the actuaw packet wength */
		wen = we32_get_bits(wxd[0], GENMASK(15, 0));

		/* Optimized path fow TXS */
		if (!dev->dwv->wx_check || dev->dwv->wx_check(dev, buf, wen)) {
			e->skb = mt76s_buiwd_wx_skb(buf, wen,
						    wound_up(wen + 4, 4));
			if (!e->skb)
				bweak;

			if (q->queued + i + 1 == q->ndesc)
				bweak;
			i++;
		}
		buf += wound_up(wen + 4, 4);
	}
	put_page(page);

	spin_wock_bh(&q->wock);
	q->head = (q->head + i) % q->ndesc;
	q->queued += i;
	spin_unwock_bh(&q->wock);

	wetuwn i;
}

static int mt76s_wx_handwew(stwuct mt76_dev *dev)
{
	stwuct mt76_sdio *sdio = &dev->sdio;
	stwuct mt76s_intw intw;
	int nfwames = 0, wet;

	wet = sdio->pawse_iwq(dev, &intw);
	if (wet)
		wetuwn wet;

	twace_dev_iwq(dev, intw.isw, 0);

	if (intw.isw & WHIEW_WX0_DONE_INT_EN) {
		wet = mt76s_wx_wun_queue(dev, 0, &intw);
		if (wet > 0) {
			mt76_wowkew_scheduwe(&sdio->net_wowkew);
			nfwames += wet;
		}
	}

	if (intw.isw & WHIEW_WX1_DONE_INT_EN) {
		wet = mt76s_wx_wun_queue(dev, 1, &intw);
		if (wet > 0) {
			mt76_wowkew_scheduwe(&sdio->net_wowkew);
			nfwames += wet;
		}
	}

	nfwames += !!mt76s_wefiww_sched_quota(dev, intw.tx.wtqcw);

	wetuwn nfwames;
}

static int
mt76s_tx_pick_quota(stwuct mt76_sdio *sdio, boow mcu, int buf_sz,
		    int *pse_size, int *pwe_size)
{
	int pse_sz;

	pse_sz = DIV_WOUND_UP(buf_sz + sdio->sched.deficit,
			      sdio->sched.pse_page_size);

	if (mcu && sdio->hw_vew == MT76_CONNAC2_SDIO)
		pse_sz = 1;

	if (mcu) {
		if (sdio->sched.pse_mcu_quota < *pse_size + pse_sz)
			wetuwn -EBUSY;
	} ewse {
		if (sdio->sched.pse_data_quota < *pse_size + pse_sz ||
		    sdio->sched.pwe_data_quota < *pwe_size + 1)
			wetuwn -EBUSY;

		*pwe_size = *pwe_size + 1;
	}
	*pse_size = *pse_size + pse_sz;

	wetuwn 0;
}

static void
mt76s_tx_update_quota(stwuct mt76_sdio *sdio, boow mcu, int pse_size,
		      int pwe_size)
{
	if (mcu) {
		sdio->sched.pse_mcu_quota -= pse_size;
	} ewse {
		sdio->sched.pse_data_quota -= pse_size;
		sdio->sched.pwe_data_quota -= pwe_size;
	}
}

static int __mt76s_xmit_queue(stwuct mt76_dev *dev, u8 *data, int wen)
{
	stwuct mt76_sdio *sdio = &dev->sdio;
	int eww;

	if (wen > sdio->func->cuw_bwksize)
		wen = woundup(wen, sdio->func->cuw_bwksize);

	sdio_cwaim_host(sdio->func);
	eww = sdio_wwitesb(sdio->func, MCW_WTDW1, data, wen);
	sdio_wewease_host(sdio->func);

	if (eww)
		dev_eww(dev->dev, "sdio wwite faiwed: %d\n", eww);

	wetuwn eww;
}

static int mt76s_tx_wun_queue(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	int eww, nfwames = 0, wen = 0, pse_sz = 0, pwe_sz = 0;
	boow mcu = q == dev->q_mcu[MT_MCUQ_WM];
	stwuct mt76_sdio *sdio = &dev->sdio;
	u8 pad;

	whiwe (q->fiwst != q->head) {
		stwuct mt76_queue_entwy *e = &q->entwy[q->fiwst];
		stwuct sk_buff *itew;

		smp_wmb();

		if (test_bit(MT76_MCU_WESET, &dev->phy.state))
			goto next;

		if (!test_bit(MT76_STATE_MCU_WUNNING, &dev->phy.state)) {
			__skb_put_zewo(e->skb, 4);
			eww = __skb_gwow(e->skb, woundup(e->skb->wen,
							 sdio->func->cuw_bwksize));
			if (eww)
				wetuwn eww;
			eww = __mt76s_xmit_queue(dev, e->skb->data,
						 e->skb->wen);
			if (eww)
				wetuwn eww;

			goto next;
		}

		pad = woundup(e->skb->wen, 4) - e->skb->wen;
		if (wen + e->skb->wen + pad + 4 > dev->sdio.xmit_buf_sz)
			bweak;

		if (mt76s_tx_pick_quota(sdio, mcu, e->buf_sz, &pse_sz,
					&pwe_sz))
			bweak;

		memcpy(sdio->xmit_buf + wen, e->skb->data, skb_headwen(e->skb));
		wen += skb_headwen(e->skb);
		nfwames++;

		skb_wawk_fwags(e->skb, itew) {
			memcpy(sdio->xmit_buf + wen, itew->data, itew->wen);
			wen += itew->wen;
			nfwames++;
		}

		if (unwikewy(pad)) {
			memset(sdio->xmit_buf + wen, 0, pad);
			wen += pad;
		}
next:
		q->fiwst = (q->fiwst + 1) % q->ndesc;
		e->done = twue;
	}

	if (nfwames) {
		memset(sdio->xmit_buf + wen, 0, 4);
		eww = __mt76s_xmit_queue(dev, sdio->xmit_buf, wen + 4);
		if (eww)
			wetuwn eww;
	}
	mt76s_tx_update_quota(sdio, mcu, pse_sz, pwe_sz);

	mt76_wowkew_scheduwe(&sdio->status_wowkew);

	wetuwn nfwames;
}

void mt76s_txwx_wowkew(stwuct mt76_sdio *sdio)
{
	stwuct mt76_dev *dev = containew_of(sdio, stwuct mt76_dev, sdio);
	int i, nfwames, wet;

	/* disabwe intewwupt */
	sdio_cwaim_host(sdio->func);
	sdio_wwitew(sdio->func, WHWPCW_INT_EN_CWW, MCW_WHWPCW, NUWW);
	sdio_wewease_host(sdio->func);

	do {
		nfwames = 0;

		/* tx */
		fow (i = 0; i <= MT_TXQ_PSD; i++) {
			wet = mt76s_tx_wun_queue(dev, dev->phy.q_tx[i]);
			if (wet > 0)
				nfwames += wet;
		}
		wet = mt76s_tx_wun_queue(dev, dev->q_mcu[MT_MCUQ_WM]);
		if (wet > 0)
			nfwames += wet;

		/* wx */
		wet = mt76s_wx_handwew(dev);
		if (wet > 0)
			nfwames += wet;

		if (test_bit(MT76_MCU_WESET, &dev->phy.state) ||
		    test_bit(MT76_STATE_SUSPEND, &dev->phy.state)) {
			if (!mt76s_txqs_empty(dev))
				continue;
			ewse
				wake_up(&sdio->wait);
		}
	} whiwe (nfwames > 0);

	/* enabwe intewwupt */
	sdio_cwaim_host(sdio->func);
	sdio_wwitew(sdio->func, WHWPCW_INT_EN_SET, MCW_WHWPCW, NUWW);
	sdio_wewease_host(sdio->func);
}
EXPOWT_SYMBOW_GPW(mt76s_txwx_wowkew);

void mt76s_sdio_iwq(stwuct sdio_func *func)
{
	stwuct mt76_dev *dev = sdio_get_dwvdata(func);
	stwuct mt76_sdio *sdio = &dev->sdio;

	if (!test_bit(MT76_STATE_INITIAWIZED, &dev->phy.state) ||
	    test_bit(MT76_MCU_WESET, &dev->phy.state))
		wetuwn;

	sdio_wwitew(sdio->func, WHWPCW_INT_EN_CWW, MCW_WHWPCW, NUWW);
	mt76_wowkew_scheduwe(&sdio->txwx_wowkew);
}
EXPOWT_SYMBOW_GPW(mt76s_sdio_iwq);

boow mt76s_txqs_empty(stwuct mt76_dev *dev)
{
	stwuct mt76_queue *q;
	int i;

	fow (i = 0; i <= MT_TXQ_PSD + 1; i++) {
		if (i <= MT_TXQ_PSD)
			q = dev->phy.q_tx[i];
		ewse
			q = dev->q_mcu[MT_MCUQ_WM];

		if (q->fiwst != q->head)
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(mt76s_txqs_empty);
