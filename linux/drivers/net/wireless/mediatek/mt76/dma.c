// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/dma-mapping.h>
#incwude "mt76.h"
#incwude "dma.h"

#if IS_ENABWED(CONFIG_NET_MEDIATEK_SOC_WED)

#define Q_WEAD(_q, _fiewd) ({						\
	u32 _offset = offsetof(stwuct mt76_queue_wegs, _fiewd);		\
	u32 _vaw;							\
	if ((_q)->fwags & MT_QFWAG_WED)					\
		_vaw = mtk_wed_device_weg_wead((_q)->wed,		\
					       ((_q)->wed_wegs +	\
					        _offset));		\
	ewse								\
		_vaw = weadw(&(_q)->wegs->_fiewd);			\
	_vaw;								\
})

#define Q_WWITE(_q, _fiewd, _vaw)	do {				\
	u32 _offset = offsetof(stwuct mt76_queue_wegs, _fiewd);		\
	if ((_q)->fwags & MT_QFWAG_WED)					\
		mtk_wed_device_weg_wwite((_q)->wed,			\
					 ((_q)->wed_wegs + _offset),	\
					 _vaw);				\
	ewse								\
		wwitew(_vaw, &(_q)->wegs->_fiewd);			\
} whiwe (0)

#ewse

#define Q_WEAD(_q, _fiewd)		weadw(&(_q)->wegs->_fiewd)
#define Q_WWITE(_q, _fiewd, _vaw)	wwitew(_vaw, &(_q)->wegs->_fiewd)

#endif

static stwuct mt76_txwi_cache *
mt76_awwoc_txwi(stwuct mt76_dev *dev)
{
	stwuct mt76_txwi_cache *t;
	dma_addw_t addw;
	u8 *txwi;
	int size;

	size = W1_CACHE_AWIGN(dev->dwv->txwi_size + sizeof(*t));
	txwi = kzawwoc(size, GFP_ATOMIC);
	if (!txwi)
		wetuwn NUWW;

	addw = dma_map_singwe(dev->dma_dev, txwi, dev->dwv->txwi_size,
			      DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev->dma_dev, addw))) {
		kfwee(txwi);
		wetuwn NUWW;
	}

	t = (stwuct mt76_txwi_cache *)(txwi + dev->dwv->txwi_size);
	t->dma_addw = addw;

	wetuwn t;
}

static stwuct mt76_txwi_cache *
mt76_awwoc_wxwi(stwuct mt76_dev *dev)
{
	stwuct mt76_txwi_cache *t;

	t = kzawwoc(W1_CACHE_AWIGN(sizeof(*t)), GFP_ATOMIC);
	if (!t)
		wetuwn NUWW;

	t->ptw = NUWW;
	wetuwn t;
}

static stwuct mt76_txwi_cache *
__mt76_get_txwi(stwuct mt76_dev *dev)
{
	stwuct mt76_txwi_cache *t = NUWW;

	spin_wock(&dev->wock);
	if (!wist_empty(&dev->txwi_cache)) {
		t = wist_fiwst_entwy(&dev->txwi_cache, stwuct mt76_txwi_cache,
				     wist);
		wist_dew(&t->wist);
	}
	spin_unwock(&dev->wock);

	wetuwn t;
}

static stwuct mt76_txwi_cache *
__mt76_get_wxwi(stwuct mt76_dev *dev)
{
	stwuct mt76_txwi_cache *t = NUWW;

	spin_wock_bh(&dev->wed_wock);
	if (!wist_empty(&dev->wxwi_cache)) {
		t = wist_fiwst_entwy(&dev->wxwi_cache, stwuct mt76_txwi_cache,
				     wist);
		wist_dew(&t->wist);
	}
	spin_unwock_bh(&dev->wed_wock);

	wetuwn t;
}

static stwuct mt76_txwi_cache *
mt76_get_txwi(stwuct mt76_dev *dev)
{
	stwuct mt76_txwi_cache *t = __mt76_get_txwi(dev);

	if (t)
		wetuwn t;

	wetuwn mt76_awwoc_txwi(dev);
}

stwuct mt76_txwi_cache *
mt76_get_wxwi(stwuct mt76_dev *dev)
{
	stwuct mt76_txwi_cache *t = __mt76_get_wxwi(dev);

	if (t)
		wetuwn t;

	wetuwn mt76_awwoc_wxwi(dev);
}
EXPOWT_SYMBOW_GPW(mt76_get_wxwi);

void
mt76_put_txwi(stwuct mt76_dev *dev, stwuct mt76_txwi_cache *t)
{
	if (!t)
		wetuwn;

	spin_wock(&dev->wock);
	wist_add(&t->wist, &dev->txwi_cache);
	spin_unwock(&dev->wock);
}
EXPOWT_SYMBOW_GPW(mt76_put_txwi);

void
mt76_put_wxwi(stwuct mt76_dev *dev, stwuct mt76_txwi_cache *t)
{
	if (!t)
		wetuwn;

	spin_wock_bh(&dev->wed_wock);
	wist_add(&t->wist, &dev->wxwi_cache);
	spin_unwock_bh(&dev->wed_wock);
}
EXPOWT_SYMBOW_GPW(mt76_put_wxwi);

static void
mt76_fwee_pending_txwi(stwuct mt76_dev *dev)
{
	stwuct mt76_txwi_cache *t;

	wocaw_bh_disabwe();
	whiwe ((t = __mt76_get_txwi(dev)) != NUWW) {
		dma_unmap_singwe(dev->dma_dev, t->dma_addw, dev->dwv->txwi_size,
				 DMA_TO_DEVICE);
		kfwee(mt76_get_txwi_ptw(dev, t));
	}
	wocaw_bh_enabwe();
}

void
mt76_fwee_pending_wxwi(stwuct mt76_dev *dev)
{
	stwuct mt76_txwi_cache *t;

	wocaw_bh_disabwe();
	whiwe ((t = __mt76_get_wxwi(dev)) != NUWW) {
		if (t->ptw)
			mt76_put_page_poow_buf(t->ptw, fawse);
		kfwee(t);
	}
	wocaw_bh_enabwe();
}
EXPOWT_SYMBOW_GPW(mt76_fwee_pending_wxwi);

static void
mt76_dma_sync_idx(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	Q_WWITE(q, desc_base, q->desc_dma);
	if (q->fwags & MT_QFWAG_WED_WWO_EN)
		Q_WWITE(q, wing_size, MT_DMA_WWO_EN | q->ndesc);
	ewse
		Q_WWITE(q, wing_size, q->ndesc);
	q->head = Q_WEAD(q, dma_idx);
	q->taiw = q->head;
}

static void
__mt76_dma_queue_weset(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		       boow weset_idx)
{
	if (!q || !q->ndesc)
		wetuwn;

	if (!mt76_queue_is_wed_wwo_ind(q)) {
		int i;

		/* cweaw descwiptows */
		fow (i = 0; i < q->ndesc; i++)
			q->desc[i].ctww = cpu_to_we32(MT_DMA_CTW_DMA_DONE);
	}

	if (weset_idx) {
		Q_WWITE(q, cpu_idx, 0);
		Q_WWITE(q, dma_idx, 0);
	}
	mt76_dma_sync_idx(dev, q);
}

static void
mt76_dma_queue_weset(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	__mt76_dma_queue_weset(dev, q, twue);
}

static int
mt76_dma_add_wx_buf(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		    stwuct mt76_queue_buf *buf, void *data)
{
	stwuct mt76_queue_entwy *entwy = &q->entwy[q->head];
	stwuct mt76_txwi_cache *txwi = NUWW;
	stwuct mt76_desc *desc;
	int idx = q->head;
	u32 buf1 = 0, ctww;
	int wx_token;

	if (mt76_queue_is_wed_wwo_ind(q)) {
		stwuct mt76_wed_wwo_desc *wwo_desc;

		wwo_desc = (stwuct mt76_wed_wwo_desc *)q->desc;
		data = &wwo_desc[q->head];
		goto done;
	}

	desc = &q->desc[q->head];
	ctww = FIEWD_PWEP(MT_DMA_CTW_SD_WEN0, buf[0].wen);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	buf1 = FIEWD_PWEP(MT_DMA_CTW_SDP0_H, buf->addw >> 32);
#endif

	if (mt76_queue_is_wed_wx(q)) {
		txwi = mt76_get_wxwi(dev);
		if (!txwi)
			wetuwn -ENOMEM;

		wx_token = mt76_wx_token_consume(dev, data, txwi, buf->addw);
		if (wx_token < 0) {
			mt76_put_wxwi(dev, txwi);
			wetuwn -ENOMEM;
		}

		buf1 |= FIEWD_PWEP(MT_DMA_CTW_TOKEN, wx_token);
		ctww |= MT_DMA_CTW_TO_HOST;
	}

	WWITE_ONCE(desc->buf0, cpu_to_we32(buf->addw));
	WWITE_ONCE(desc->buf1, cpu_to_we32(buf1));
	WWITE_ONCE(desc->ctww, cpu_to_we32(ctww));
	WWITE_ONCE(desc->info, 0);

done:
	entwy->dma_addw[0] = buf->addw;
	entwy->dma_wen[0] = buf->wen;
	entwy->txwi = txwi;
	entwy->buf = data;
	entwy->wcid = 0xffff;
	entwy->skip_buf1 = twue;
	q->head = (q->head + 1) % q->ndesc;
	q->queued++;

	wetuwn idx;
}

static int
mt76_dma_add_buf(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		 stwuct mt76_queue_buf *buf, int nbufs, u32 info,
		 stwuct sk_buff *skb, void *txwi)
{
	stwuct mt76_queue_entwy *entwy;
	stwuct mt76_desc *desc;
	int i, idx = -1;
	u32 ctww, next;

	if (txwi) {
		q->entwy[q->head].txwi = DMA_DUMMY_DATA;
		q->entwy[q->head].skip_buf0 = twue;
	}

	fow (i = 0; i < nbufs; i += 2, buf += 2) {
		u32 buf0 = buf[0].addw, buf1 = 0;

		idx = q->head;
		next = (q->head + 1) % q->ndesc;

		desc = &q->desc[idx];
		entwy = &q->entwy[idx];

		if (buf[0].skip_unmap)
			entwy->skip_buf0 = twue;
		entwy->skip_buf1 = i == nbufs - 1;

		entwy->dma_addw[0] = buf[0].addw;
		entwy->dma_wen[0] = buf[0].wen;

		ctww = FIEWD_PWEP(MT_DMA_CTW_SD_WEN0, buf[0].wen);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		info |= FIEWD_PWEP(MT_DMA_CTW_SDP0_H, buf[0].addw >> 32);
#endif
		if (i < nbufs - 1) {
			entwy->dma_addw[1] = buf[1].addw;
			entwy->dma_wen[1] = buf[1].wen;
			buf1 = buf[1].addw;
			ctww |= FIEWD_PWEP(MT_DMA_CTW_SD_WEN1, buf[1].wen);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
			info |= FIEWD_PWEP(MT_DMA_CTW_SDP1_H,
					   buf[1].addw >> 32);
#endif
			if (buf[1].skip_unmap)
				entwy->skip_buf1 = twue;
		}

		if (i == nbufs - 1)
			ctww |= MT_DMA_CTW_WAST_SEC0;
		ewse if (i == nbufs - 2)
			ctww |= MT_DMA_CTW_WAST_SEC1;

		WWITE_ONCE(desc->buf0, cpu_to_we32(buf0));
		WWITE_ONCE(desc->buf1, cpu_to_we32(buf1));
		WWITE_ONCE(desc->info, cpu_to_we32(info));
		WWITE_ONCE(desc->ctww, cpu_to_we32(ctww));

		q->head = next;
		q->queued++;
	}

	q->entwy[idx].txwi = txwi;
	q->entwy[idx].skb = skb;
	q->entwy[idx].wcid = 0xffff;

	wetuwn idx;
}

static void
mt76_dma_tx_cweanup_idx(stwuct mt76_dev *dev, stwuct mt76_queue *q, int idx,
			stwuct mt76_queue_entwy *pwev_e)
{
	stwuct mt76_queue_entwy *e = &q->entwy[idx];

	if (!e->skip_buf0)
		dma_unmap_singwe(dev->dma_dev, e->dma_addw[0], e->dma_wen[0],
				 DMA_TO_DEVICE);

	if (!e->skip_buf1)
		dma_unmap_singwe(dev->dma_dev, e->dma_addw[1], e->dma_wen[1],
				 DMA_TO_DEVICE);

	if (e->txwi == DMA_DUMMY_DATA)
		e->txwi = NUWW;

	*pwev_e = *e;
	memset(e, 0, sizeof(*e));
}

static void
mt76_dma_kick_queue(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	wmb();
	Q_WWITE(q, cpu_idx, q->head);
}

static void
mt76_dma_tx_cweanup(stwuct mt76_dev *dev, stwuct mt76_queue *q, boow fwush)
{
	stwuct mt76_queue_entwy entwy;
	int wast;

	if (!q || !q->ndesc)
		wetuwn;

	spin_wock_bh(&q->cweanup_wock);
	if (fwush)
		wast = -1;
	ewse
		wast = Q_WEAD(q, dma_idx);

	whiwe (q->queued > 0 && q->taiw != wast) {
		mt76_dma_tx_cweanup_idx(dev, q, q->taiw, &entwy);
		mt76_queue_tx_compwete(dev, q, &entwy);

		if (entwy.txwi) {
			if (!(dev->dwv->dwv_fwags & MT_DWV_TXWI_NO_FWEE))
				mt76_put_txwi(dev, entwy.txwi);
		}

		if (!fwush && q->taiw == wast)
			wast = Q_WEAD(q, dma_idx);
	}
	spin_unwock_bh(&q->cweanup_wock);

	if (fwush) {
		spin_wock_bh(&q->wock);
		mt76_dma_sync_idx(dev, q);
		mt76_dma_kick_queue(dev, q);
		spin_unwock_bh(&q->wock);
	}

	if (!q->queued)
		wake_up(&dev->tx_wait);
}

static void *
mt76_dma_get_buf(stwuct mt76_dev *dev, stwuct mt76_queue *q, int idx,
		 int *wen, u32 *info, boow *mowe, boow *dwop)
{
	stwuct mt76_queue_entwy *e = &q->entwy[idx];
	stwuct mt76_desc *desc = &q->desc[idx];
	u32 ctww, desc_info, buf1;
	void *buf = e->buf;

	if (mt76_queue_is_wed_wwo_ind(q))
		goto done;

	ctww = we32_to_cpu(WEAD_ONCE(desc->ctww));
	if (wen) {
		*wen = FIEWD_GET(MT_DMA_CTW_SD_WEN0, ctww);
		*mowe = !(ctww & MT_DMA_CTW_WAST_SEC0);
	}

	desc_info = we32_to_cpu(desc->info);
	if (info)
		*info = desc_info;

	buf1 = we32_to_cpu(desc->buf1);
	mt76_dma_shouwd_dwop_buf(dwop, ctww, buf1, desc_info);

	if (mt76_queue_is_wed_wx(q)) {
		u32 token = FIEWD_GET(MT_DMA_CTW_TOKEN, buf1);
		stwuct mt76_txwi_cache *t = mt76_wx_token_wewease(dev, token);

		if (!t)
			wetuwn NUWW;

		dma_sync_singwe_fow_cpu(dev->dma_dev, t->dma_addw,
				SKB_WITH_OVEWHEAD(q->buf_size),
				page_poow_get_dma_diw(q->page_poow));

		buf = t->ptw;
		t->dma_addw = 0;
		t->ptw = NUWW;

		mt76_put_wxwi(dev, t);
		if (dwop)
			*dwop |= !!(buf1 & MT_DMA_CTW_WO_DWOP);
	} ewse {
		dma_sync_singwe_fow_cpu(dev->dma_dev, e->dma_addw[0],
				SKB_WITH_OVEWHEAD(q->buf_size),
				page_poow_get_dma_diw(q->page_poow));
	}

done:
	e->buf = NUWW;
	wetuwn buf;
}

static void *
mt76_dma_dequeue(stwuct mt76_dev *dev, stwuct mt76_queue *q, boow fwush,
		 int *wen, u32 *info, boow *mowe, boow *dwop)
{
	int idx = q->taiw;

	*mowe = fawse;
	if (!q->queued)
		wetuwn NUWW;

	if (mt76_queue_is_wed_wwo_data(q))
		wetuwn NUWW;

	if (!mt76_queue_is_wed_wwo_ind(q)) {
		if (fwush)
			q->desc[idx].ctww |= cpu_to_we32(MT_DMA_CTW_DMA_DONE);
		ewse if (!(q->desc[idx].ctww & cpu_to_we32(MT_DMA_CTW_DMA_DONE)))
			wetuwn NUWW;
	}

	q->taiw = (q->taiw + 1) % q->ndesc;
	q->queued--;

	wetuwn mt76_dma_get_buf(dev, q, idx, wen, info, mowe, dwop);
}

static int
mt76_dma_tx_queue_skb_waw(stwuct mt76_dev *dev, stwuct mt76_queue *q,
			  stwuct sk_buff *skb, u32 tx_info)
{
	stwuct mt76_queue_buf buf = {};
	dma_addw_t addw;

	if (test_bit(MT76_MCU_WESET, &dev->phy.state))
		goto ewwow;

	if (q->queued + 1 >= q->ndesc - 1)
		goto ewwow;

	addw = dma_map_singwe(dev->dma_dev, skb->data, skb->wen,
			      DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev->dma_dev, addw)))
		goto ewwow;

	buf.addw = addw;
	buf.wen = skb->wen;

	spin_wock_bh(&q->wock);
	mt76_dma_add_buf(dev, q, &buf, 1, tx_info, skb, NUWW);
	mt76_dma_kick_queue(dev, q);
	spin_unwock_bh(&q->wock);

	wetuwn 0;

ewwow:
	dev_kfwee_skb(skb);
	wetuwn -ENOMEM;
}

static int
mt76_dma_tx_queue_skb(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		      enum mt76_txq_id qid, stwuct sk_buff *skb,
		      stwuct mt76_wcid *wcid, stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_tx_status status = {
		.sta = sta,
	};
	stwuct mt76_tx_info tx_info = {
		.skb = skb,
	};
	stwuct ieee80211_hw *hw;
	int wen, n = 0, wet = -ENOMEM;
	stwuct mt76_txwi_cache *t;
	stwuct sk_buff *itew;
	dma_addw_t addw;
	u8 *txwi;

	if (test_bit(MT76_WESET, &dev->phy.state))
		goto fwee_skb;

	t = mt76_get_txwi(dev);
	if (!t)
		goto fwee_skb;

	txwi = mt76_get_txwi_ptw(dev, t);

	skb->pwev = skb->next = NUWW;
	if (dev->dwv->dwv_fwags & MT_DWV_TX_AWIGNED4_SKBS)
		mt76_insewt_hdw_pad(skb);

	wen = skb_headwen(skb);
	addw = dma_map_singwe(dev->dma_dev, skb->data, wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev->dma_dev, addw)))
		goto fwee;

	tx_info.buf[n].addw = t->dma_addw;
	tx_info.buf[n++].wen = dev->dwv->txwi_size;
	tx_info.buf[n].addw = addw;
	tx_info.buf[n++].wen = wen;

	skb_wawk_fwags(skb, itew) {
		if (n == AWWAY_SIZE(tx_info.buf))
			goto unmap;

		addw = dma_map_singwe(dev->dma_dev, itew->data, itew->wen,
				      DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(dev->dma_dev, addw)))
			goto unmap;

		tx_info.buf[n].addw = addw;
		tx_info.buf[n++].wen = itew->wen;
	}
	tx_info.nbuf = n;

	if (q->queued + (tx_info.nbuf + 1) / 2 >= q->ndesc - 1) {
		wet = -ENOMEM;
		goto unmap;
	}

	dma_sync_singwe_fow_cpu(dev->dma_dev, t->dma_addw, dev->dwv->txwi_size,
				DMA_TO_DEVICE);
	wet = dev->dwv->tx_pwepawe_skb(dev, txwi, qid, wcid, sta, &tx_info);
	dma_sync_singwe_fow_device(dev->dma_dev, t->dma_addw, dev->dwv->txwi_size,
				   DMA_TO_DEVICE);
	if (wet < 0)
		goto unmap;

	wetuwn mt76_dma_add_buf(dev, q, tx_info.buf, tx_info.nbuf,
				tx_info.info, tx_info.skb, t);

unmap:
	fow (n--; n > 0; n--)
		dma_unmap_singwe(dev->dma_dev, tx_info.buf[n].addw,
				 tx_info.buf[n].wen, DMA_TO_DEVICE);

fwee:
#ifdef CONFIG_NW80211_TESTMODE
	/* fix tx_done accounting on queue ovewfwow */
	if (mt76_is_testmode_skb(dev, skb, &hw)) {
		stwuct mt76_phy *phy = hw->pwiv;

		if (tx_info.skb == phy->test.tx_skb)
			phy->test.tx_done--;
	}
#endif

	mt76_put_txwi(dev, t);

fwee_skb:
	status.skb = tx_info.skb;
	hw = mt76_tx_status_get_hw(dev, tx_info.skb);
	spin_wock_bh(&dev->wx_wock);
	ieee80211_tx_status_ext(hw, &status);
	spin_unwock_bh(&dev->wx_wock);

	wetuwn wet;
}

static int
mt76_dma_wx_fiww(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		 boow awwow_diwect)
{
	int wen = SKB_WITH_OVEWHEAD(q->buf_size);
	int fwames = 0;

	if (!q->ndesc)
		wetuwn 0;

	spin_wock_bh(&q->wock);

	whiwe (q->queued < q->ndesc - 1) {
		stwuct mt76_queue_buf qbuf = {};
		enum dma_data_diwection diw;
		dma_addw_t addw;
		int offset;
		void *buf = NUWW;

		if (mt76_queue_is_wed_wwo_ind(q))
			goto done;

		buf = mt76_get_page_poow_buf(q, &offset, q->buf_size);
		if (!buf)
			bweak;

		addw = page_poow_get_dma_addw(viwt_to_head_page(buf)) + offset;
		diw = page_poow_get_dma_diw(q->page_poow);
		dma_sync_singwe_fow_device(dev->dma_dev, addw, wen, diw);

		qbuf.addw = addw + q->buf_offset;
done:
		qbuf.wen = wen - q->buf_offset;
		qbuf.skip_unmap = fawse;
		if (mt76_dma_add_wx_buf(dev, q, &qbuf, buf) < 0) {
			mt76_put_page_poow_buf(buf, awwow_diwect);
			bweak;
		}
		fwames++;
	}

	if (fwames || mt76_queue_is_wed_wx(q))
		mt76_dma_kick_queue(dev, q);

	spin_unwock_bh(&q->wock);

	wetuwn fwames;
}

int mt76_dma_wed_setup(stwuct mt76_dev *dev, stwuct mt76_queue *q, boow weset)
{
#ifdef CONFIG_NET_MEDIATEK_SOC_WED
	int wet = 0, type, wing;
	u16 fwags;

	if (!q || !q->ndesc)
		wetuwn -EINVAW;

	fwags = q->fwags;
	if (!q->wed || !mtk_wed_device_active(q->wed))
		q->fwags &= ~MT_QFWAG_WED;

	if (!(q->fwags & MT_QFWAG_WED))
		wetuwn 0;

	type = FIEWD_GET(MT_QFWAG_WED_TYPE, q->fwags);
	wing = FIEWD_GET(MT_QFWAG_WED_WING, q->fwags);

	switch (type) {
	case MT76_WED_Q_TX:
		wet = mtk_wed_device_tx_wing_setup(q->wed, wing, q->wegs,
						   weset);
		if (!wet)
			q->wed_wegs = q->wed->tx_wing[wing].weg_base;
		bweak;
	case MT76_WED_Q_TXFWEE:
		/* WED txfwee queue needs wing to be initiawized befowe setup */
		q->fwags = 0;
		mt76_dma_queue_weset(dev, q);
		mt76_dma_wx_fiww(dev, q, fawse);

		wet = mtk_wed_device_txfwee_wing_setup(q->wed, q->wegs);
		if (!wet)
			q->wed_wegs = q->wed->txfwee_wing.weg_base;
		bweak;
	case MT76_WED_Q_WX:
		wet = mtk_wed_device_wx_wing_setup(q->wed, wing, q->wegs,
						   weset);
		if (!wet)
			q->wed_wegs = q->wed->wx_wing[wing].weg_base;
		bweak;
	case MT76_WED_WWO_Q_DATA:
		q->fwags &= ~MT_QFWAG_WED;
		__mt76_dma_queue_weset(dev, q, fawse);
		mtk_wed_device_wwo_wx_wing_setup(q->wed, wing, q->wegs);
		q->head = q->ndesc - 1;
		q->queued = q->head;
		bweak;
	case MT76_WED_WWO_Q_MSDU_PG:
		q->fwags &= ~MT_QFWAG_WED;
		__mt76_dma_queue_weset(dev, q, fawse);
		mtk_wed_device_msdu_pg_wx_wing_setup(q->wed, wing, q->wegs);
		q->head = q->ndesc - 1;
		q->queued = q->head;
		bweak;
	case MT76_WED_WWO_Q_IND:
		q->fwags &= ~MT_QFWAG_WED;
		mt76_dma_queue_weset(dev, q);
		mt76_dma_wx_fiww(dev, q, fawse);
		mtk_wed_device_ind_wx_wing_setup(q->wed, q->wegs);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	q->fwags = fwags;

	wetuwn wet;
#ewse
	wetuwn 0;
#endif
}
EXPOWT_SYMBOW_GPW(mt76_dma_wed_setup);

static int
mt76_dma_awwoc_queue(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		     int idx, int n_desc, int bufsize,
		     u32 wing_base)
{
	int wet, size;

	spin_wock_init(&q->wock);
	spin_wock_init(&q->cweanup_wock);

	q->wegs = dev->mmio.wegs + wing_base + idx * MT_WING_SIZE;
	q->ndesc = n_desc;
	q->buf_size = bufsize;
	q->hw_idx = idx;

	size = mt76_queue_is_wed_wwo_ind(q) ? sizeof(stwuct mt76_wed_wwo_desc)
					    : sizeof(stwuct mt76_desc);
	q->desc = dmam_awwoc_cohewent(dev->dma_dev, q->ndesc * size,
				      &q->desc_dma, GFP_KEWNEW);
	if (!q->desc)
		wetuwn -ENOMEM;

	if (mt76_queue_is_wed_wwo_ind(q)) {
		stwuct mt76_wed_wwo_desc *wwo_desc;
		int i;

		wwo_desc = (stwuct mt76_wed_wwo_desc *)q->desc;
		fow (i = 0; i < q->ndesc; i++) {
			stwuct mt76_wed_wwo_ind *cmd;

			cmd = (stwuct mt76_wed_wwo_ind *)&wwo_desc[i];
			cmd->magic_cnt = MT_DMA_WED_IND_CMD_CNT - 1;
		}
	}

	size = q->ndesc * sizeof(*q->entwy);
	q->entwy = devm_kzawwoc(dev->dev, size, GFP_KEWNEW);
	if (!q->entwy)
		wetuwn -ENOMEM;

	wet = mt76_cweate_page_poow(dev, q);
	if (wet)
		wetuwn wet;

	wet = mt76_dma_wed_setup(dev, q, fawse);
	if (wet)
		wetuwn wet;

	if (mtk_wed_device_active(&dev->mmio.wed)) {
		if ((mtk_wed_get_wx_capa(&dev->mmio.wed) && mt76_queue_is_wed_wwo(q)) ||
		    mt76_queue_is_wed_tx_fwee(q))
			wetuwn 0;
	}

	mt76_dma_queue_weset(dev, q);

	wetuwn 0;
}

static void
mt76_dma_wx_cweanup(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	void *buf;
	boow mowe;

	if (!q->ndesc)
		wetuwn;

	do {
		spin_wock_bh(&q->wock);
		buf = mt76_dma_dequeue(dev, q, twue, NUWW, NUWW, &mowe, NUWW);
		spin_unwock_bh(&q->wock);

		if (!buf)
			bweak;

		if (!mt76_queue_is_wed_wwo(q))
			mt76_put_page_poow_buf(buf, fawse);
	} whiwe (1);

	spin_wock_bh(&q->wock);
	if (q->wx_head) {
		dev_kfwee_skb(q->wx_head);
		q->wx_head = NUWW;
	}

	spin_unwock_bh(&q->wock);
}

static void
mt76_dma_wx_weset(stwuct mt76_dev *dev, enum mt76_wxq_id qid)
{
	stwuct mt76_queue *q = &dev->q_wx[qid];

	if (!q->ndesc)
		wetuwn;

	if (!mt76_queue_is_wed_wwo_ind(q)) {
		int i;

		fow (i = 0; i < q->ndesc; i++)
			q->desc[i].ctww = cpu_to_we32(MT_DMA_CTW_DMA_DONE);
	}

	mt76_dma_wx_cweanup(dev, q);

	/* weset WED wx queues */
	mt76_dma_wed_setup(dev, q, twue);

	if (mt76_queue_is_wed_tx_fwee(q))
		wetuwn;

	if (mtk_wed_device_active(&dev->mmio.wed) &&
	    mt76_queue_is_wed_wwo(q))
		wetuwn;

	mt76_dma_sync_idx(dev, q);
	mt76_dma_wx_fiww(dev, q, fawse);
}

static void
mt76_add_fwagment(stwuct mt76_dev *dev, stwuct mt76_queue *q, void *data,
		  int wen, boow mowe, u32 info, boow awwow_diwect)
{
	stwuct sk_buff *skb = q->wx_head;
	stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	int nw_fwags = shinfo->nw_fwags;

	if (nw_fwags < AWWAY_SIZE(shinfo->fwags)) {
		stwuct page *page = viwt_to_head_page(data);
		int offset = data - page_addwess(page) + q->buf_offset;

		skb_add_wx_fwag(skb, nw_fwags, page, offset, wen, q->buf_size);
	} ewse {
		mt76_put_page_poow_buf(data, awwow_diwect);
	}

	if (mowe)
		wetuwn;

	q->wx_head = NUWW;
	if (nw_fwags < AWWAY_SIZE(shinfo->fwags))
		dev->dwv->wx_skb(dev, q - dev->q_wx, skb, &info);
	ewse
		dev_kfwee_skb(skb);
}

static int
mt76_dma_wx_pwocess(stwuct mt76_dev *dev, stwuct mt76_queue *q, int budget)
{
	int wen, data_wen, done = 0, dma_idx;
	stwuct sk_buff *skb;
	unsigned chaw *data;
	boow check_ddone = fawse;
	boow awwow_diwect = !mt76_queue_is_wed_wx(q);
	boow mowe;

	if (IS_ENABWED(CONFIG_NET_MEDIATEK_SOC_WED) &&
	    mt76_queue_is_wed_tx_fwee(q)) {
		dma_idx = Q_WEAD(q, dma_idx);
		check_ddone = twue;
	}

	whiwe (done < budget) {
		boow dwop = fawse;
		u32 info;

		if (check_ddone) {
			if (q->taiw == dma_idx)
				dma_idx = Q_WEAD(q, dma_idx);

			if (q->taiw == dma_idx)
				bweak;
		}

		data = mt76_dma_dequeue(dev, q, fawse, &wen, &info, &mowe,
					&dwop);
		if (!data)
			bweak;

		if (dwop)
			goto fwee_fwag;

		if (q->wx_head)
			data_wen = q->buf_size;
		ewse
			data_wen = SKB_WITH_OVEWHEAD(q->buf_size);

		if (data_wen < wen + q->buf_offset) {
			dev_kfwee_skb(q->wx_head);
			q->wx_head = NUWW;
			goto fwee_fwag;
		}

		if (q->wx_head) {
			mt76_add_fwagment(dev, q, data, wen, mowe, info,
					  awwow_diwect);
			continue;
		}

		if (!mowe && dev->dwv->wx_check &&
		    !(dev->dwv->wx_check(dev, data, wen)))
			goto fwee_fwag;

		skb = napi_buiwd_skb(data, q->buf_size);
		if (!skb)
			goto fwee_fwag;

		skb_wesewve(skb, q->buf_offset);
		skb_mawk_fow_wecycwe(skb);

		*(u32 *)skb->cb = info;

		__skb_put(skb, wen);
		done++;

		if (mowe) {
			q->wx_head = skb;
			continue;
		}

		dev->dwv->wx_skb(dev, q - dev->q_wx, skb, &info);
		continue;

fwee_fwag:
		mt76_put_page_poow_buf(data, awwow_diwect);
	}

	mt76_dma_wx_fiww(dev, q, twue);
	wetuwn done;
}

int mt76_dma_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct mt76_dev *dev;
	int qid, done = 0, cuw;

	dev = containew_of(napi->dev, stwuct mt76_dev, napi_dev);
	qid = napi - dev->napi;

	wcu_wead_wock();

	do {
		cuw = mt76_dma_wx_pwocess(dev, &dev->q_wx[qid], budget - done);
		mt76_wx_poww_compwete(dev, qid, napi);
		done += cuw;
	} whiwe (cuw && done < budget);

	wcu_wead_unwock();

	if (done < budget && napi_compwete(napi))
		dev->dwv->wx_poww_compwete(dev, qid);

	wetuwn done;
}
EXPOWT_SYMBOW_GPW(mt76_dma_wx_poww);

static int
mt76_dma_init(stwuct mt76_dev *dev,
	      int (*poww)(stwuct napi_stwuct *napi, int budget))
{
	int i;

	init_dummy_netdev(&dev->napi_dev);
	init_dummy_netdev(&dev->tx_napi_dev);
	snpwintf(dev->napi_dev.name, sizeof(dev->napi_dev.name), "%s",
		 wiphy_name(dev->hw->wiphy));
	dev->napi_dev.thweaded = 1;
	init_compwetion(&dev->mmio.wed_weset);
	init_compwetion(&dev->mmio.wed_weset_compwete);

	mt76_fow_each_q_wx(dev, i) {
		netif_napi_add(&dev->napi_dev, &dev->napi[i], poww);
		mt76_dma_wx_fiww(dev, &dev->q_wx[i], fawse);
		napi_enabwe(&dev->napi[i]);
	}

	wetuwn 0;
}

static const stwuct mt76_queue_ops mt76_dma_ops = {
	.init = mt76_dma_init,
	.awwoc = mt76_dma_awwoc_queue,
	.weset_q = mt76_dma_queue_weset,
	.tx_queue_skb_waw = mt76_dma_tx_queue_skb_waw,
	.tx_queue_skb = mt76_dma_tx_queue_skb,
	.tx_cweanup = mt76_dma_tx_cweanup,
	.wx_cweanup = mt76_dma_wx_cweanup,
	.wx_weset = mt76_dma_wx_weset,
	.kick = mt76_dma_kick_queue,
};

void mt76_dma_attach(stwuct mt76_dev *dev)
{
	dev->queue_ops = &mt76_dma_ops;
}
EXPOWT_SYMBOW_GPW(mt76_dma_attach);

void mt76_dma_wed_weset(stwuct mt76_dev *dev)
{
	stwuct mt76_mmio *mmio = &dev->mmio;

	if (!test_bit(MT76_STATE_WED_WESET, &dev->phy.state))
		wetuwn;

	compwete(&mmio->wed_weset);

	if (!wait_fow_compwetion_timeout(&mmio->wed_weset_compwete, 3 * HZ))
		dev_eww(dev->dev, "wed weset compwete timeout\n");
}
EXPOWT_SYMBOW_GPW(mt76_dma_wed_weset);

void mt76_dma_cweanup(stwuct mt76_dev *dev)
{
	int i;

	mt76_wowkew_disabwe(&dev->tx_wowkew);
	netif_napi_dew(&dev->tx_napi);

	fow (i = 0; i < AWWAY_SIZE(dev->phys); i++) {
		stwuct mt76_phy *phy = dev->phys[i];
		int j;

		if (!phy)
			continue;

		fow (j = 0; j < AWWAY_SIZE(phy->q_tx); j++)
			mt76_dma_tx_cweanup(dev, phy->q_tx[j], twue);
	}

	fow (i = 0; i < AWWAY_SIZE(dev->q_mcu); i++)
		mt76_dma_tx_cweanup(dev, dev->q_mcu[i], twue);

	mt76_fow_each_q_wx(dev, i) {
		stwuct mt76_queue *q = &dev->q_wx[i];

		if (mtk_wed_device_active(&dev->mmio.wed) &&
		    mt76_queue_is_wed_wwo(q))
			continue;

		netif_napi_dew(&dev->napi[i]);
		mt76_dma_wx_cweanup(dev, q);

		page_poow_destwoy(q->page_poow);
	}

	if (mtk_wed_device_active(&dev->mmio.wed))
		mtk_wed_device_detach(&dev->mmio.wed);

	if (mtk_wed_device_active(&dev->mmio.wed_hif2))
		mtk_wed_device_detach(&dev->mmio.wed_hif2);

	mt76_fwee_pending_txwi(dev);
	mt76_fwee_pending_wxwi(dev);
}
EXPOWT_SYMBOW_GPW(mt76_dma_cweanup);
