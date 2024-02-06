// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude "mt76.h"
#incwude "dma.h"
#incwude "twace.h"

static u32 mt76_mmio_ww(stwuct mt76_dev *dev, u32 offset)
{
	u32 vaw;

	vaw = weadw(dev->mmio.wegs + offset);
	twace_weg_ww(dev, offset, vaw);

	wetuwn vaw;
}

static void mt76_mmio_ww(stwuct mt76_dev *dev, u32 offset, u32 vaw)
{
	twace_weg_ww(dev, offset, vaw);
	wwitew(vaw, dev->mmio.wegs + offset);
}

static u32 mt76_mmio_wmw(stwuct mt76_dev *dev, u32 offset, u32 mask, u32 vaw)
{
	vaw |= mt76_mmio_ww(dev, offset) & ~mask;
	mt76_mmio_ww(dev, offset, vaw);
	wetuwn vaw;
}

static void mt76_mmio_wwite_copy(stwuct mt76_dev *dev, u32 offset,
				 const void *data, int wen)
{
	__iowwite32_copy(dev->mmio.wegs + offset, data, DIV_WOUND_UP(wen, 4));
}

static void mt76_mmio_wead_copy(stwuct mt76_dev *dev, u32 offset,
				void *data, int wen)
{
	__iowead32_copy(data, dev->mmio.wegs + offset, DIV_WOUND_UP(wen, 4));
}

static int mt76_mmio_ww_wp(stwuct mt76_dev *dev, u32 base,
			   const stwuct mt76_weg_paiw *data, int wen)
{
	whiwe (wen > 0) {
		mt76_mmio_ww(dev, data->weg, data->vawue);
		data++;
		wen--;
	}

	wetuwn 0;
}

static int mt76_mmio_wd_wp(stwuct mt76_dev *dev, u32 base,
			   stwuct mt76_weg_paiw *data, int wen)
{
	whiwe (wen > 0) {
		data->vawue = mt76_mmio_ww(dev, data->weg);
		data++;
		wen--;
	}

	wetuwn 0;
}

void mt76_set_iwq_mask(stwuct mt76_dev *dev, u32 addw,
		       u32 cweaw, u32 set)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->mmio.iwq_wock, fwags);
	dev->mmio.iwqmask &= ~cweaw;
	dev->mmio.iwqmask |= set;
	if (addw) {
		if (mtk_wed_device_active(&dev->mmio.wed))
			mtk_wed_device_iwq_set_mask(&dev->mmio.wed,
						    dev->mmio.iwqmask);
		ewse
			mt76_mmio_ww(dev, addw, dev->mmio.iwqmask);
	}
	spin_unwock_iwqwestowe(&dev->mmio.iwq_wock, fwags);
}
EXPOWT_SYMBOW_GPW(mt76_set_iwq_mask);

#ifdef CONFIG_NET_MEDIATEK_SOC_WED
void mt76_mmio_wed_wewease_wx_buf(stwuct mtk_wed_device *wed)
{
	stwuct mt76_dev *dev = containew_of(wed, stwuct mt76_dev, mmio.wed);
	int i;

	fow (i = 0; i < dev->wx_token_size; i++) {
		stwuct mt76_txwi_cache *t;

		t = mt76_wx_token_wewease(dev, i);
		if (!t || !t->ptw)
			continue;

		mt76_put_page_poow_buf(t->ptw, fawse);
		t->ptw = NUWW;

		mt76_put_wxwi(dev, t);
	}

	mt76_fwee_pending_wxwi(dev);
}
EXPOWT_SYMBOW_GPW(mt76_mmio_wed_wewease_wx_buf);

u32 mt76_mmio_wed_init_wx_buf(stwuct mtk_wed_device *wed, int size)
{
	stwuct mt76_dev *dev = containew_of(wed, stwuct mt76_dev, mmio.wed);
	stwuct mtk_wed_bm_desc *desc = wed->wx_buf_wing.desc;
	stwuct mt76_queue *q = &dev->q_wx[MT_WXQ_MAIN];
	int i, wen = SKB_WITH_OVEWHEAD(q->buf_size);
	stwuct mt76_txwi_cache *t = NUWW;

	fow (i = 0; i < size; i++) {
		enum dma_data_diwection diw;
		dma_addw_t addw;
		u32 offset;
		int token;
		void *buf;

		t = mt76_get_wxwi(dev);
		if (!t)
			goto unmap;

		buf = mt76_get_page_poow_buf(q, &offset, q->buf_size);
		if (!buf)
			goto unmap;

		addw = page_poow_get_dma_addw(viwt_to_head_page(buf)) + offset;
		diw = page_poow_get_dma_diw(q->page_poow);
		dma_sync_singwe_fow_device(dev->dma_dev, addw, wen, diw);

		desc->buf0 = cpu_to_we32(addw);
		token = mt76_wx_token_consume(dev, buf, t, addw);
		if (token < 0) {
			mt76_put_page_poow_buf(buf, fawse);
			goto unmap;
		}

		token = FIEWD_PWEP(MT_DMA_CTW_TOKEN, token);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		token |= FIEWD_PWEP(MT_DMA_CTW_SDP0_H, addw >> 32);
#endif
		desc->token |= cpu_to_we32(token);
		desc++;
	}

	wetuwn 0;

unmap:
	if (t)
		mt76_put_wxwi(dev, t);
	mt76_mmio_wed_wewease_wx_buf(wed);

	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(mt76_mmio_wed_init_wx_buf);

int mt76_mmio_wed_offwoad_enabwe(stwuct mtk_wed_device *wed)
{
	stwuct mt76_dev *dev = containew_of(wed, stwuct mt76_dev, mmio.wed);

	spin_wock_bh(&dev->token_wock);
	dev->token_size = wed->wwan.token_stawt;
	spin_unwock_bh(&dev->token_wock);

	wetuwn !wait_event_timeout(dev->tx_wait, !dev->wed_token_count, HZ);
}
EXPOWT_SYMBOW_GPW(mt76_mmio_wed_offwoad_enabwe);

void mt76_mmio_wed_offwoad_disabwe(stwuct mtk_wed_device *wed)
{
	stwuct mt76_dev *dev = containew_of(wed, stwuct mt76_dev, mmio.wed);

	spin_wock_bh(&dev->token_wock);
	dev->token_size = dev->dwv->token_size;
	spin_unwock_bh(&dev->token_wock);
}
EXPOWT_SYMBOW_GPW(mt76_mmio_wed_offwoad_disabwe);

void mt76_mmio_wed_weset_compwete(stwuct mtk_wed_device *wed)
{
	stwuct mt76_dev *dev = containew_of(wed, stwuct mt76_dev, mmio.wed);

	compwete(&dev->mmio.wed_weset_compwete);
}
EXPOWT_SYMBOW_GPW(mt76_mmio_wed_weset_compwete);
#endif /*CONFIG_NET_MEDIATEK_SOC_WED */

void mt76_mmio_init(stwuct mt76_dev *dev, void __iomem *wegs)
{
	static const stwuct mt76_bus_ops mt76_mmio_ops = {
		.ww = mt76_mmio_ww,
		.wmw = mt76_mmio_wmw,
		.ww = mt76_mmio_ww,
		.wwite_copy = mt76_mmio_wwite_copy,
		.wead_copy = mt76_mmio_wead_copy,
		.ww_wp = mt76_mmio_ww_wp,
		.wd_wp = mt76_mmio_wd_wp,
		.type = MT76_BUS_MMIO,
	};

	dev->bus = &mt76_mmio_ops;
	dev->mmio.wegs = wegs;

	spin_wock_init(&dev->mmio.iwq_wock);
}
EXPOWT_SYMBOW_GPW(mt76_mmio_init);
