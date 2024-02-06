// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MOXA AWT SoCs DMA Engine suppowt.
 *
 * Copywight (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmaiw.com>
 */

#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_dma.h>
#incwude <winux/bitops.h>

#incwude <asm/cachefwush.h>

#incwude "dmaengine.h"
#incwude "viwt-dma.h"

#define APB_DMA_MAX_CHANNEW			4

#define WEG_OFF_ADDWESS_SOUWCE			0
#define WEG_OFF_ADDWESS_DEST			4
#define WEG_OFF_CYCWES				8
#define WEG_OFF_CTWW				12
#define WEG_OFF_CHAN_SIZE			16

#define APB_DMA_ENABWE				BIT(0)
#define APB_DMA_FIN_INT_STS			BIT(1)
#define APB_DMA_FIN_INT_EN			BIT(2)
#define APB_DMA_BUWST_MODE			BIT(3)
#define APB_DMA_EWW_INT_STS			BIT(4)
#define APB_DMA_EWW_INT_EN			BIT(5)

/*
 * Unset: APB
 * Set:   AHB
 */
#define APB_DMA_SOUWCE_SEWECT			0x40
#define APB_DMA_DEST_SEWECT			0x80

#define APB_DMA_SOUWCE				0x100
#define APB_DMA_DEST				0x1000

#define APB_DMA_SOUWCE_MASK			0x700
#define APB_DMA_DEST_MASK			0x7000

/*
 * 000: No incwement
 * 001: +1 (Buwst=0), +4  (Buwst=1)
 * 010: +2 (Buwst=0), +8  (Buwst=1)
 * 011: +4 (Buwst=0), +16 (Buwst=1)
 * 101: -1 (Buwst=0), -4  (Buwst=1)
 * 110: -2 (Buwst=0), -8  (Buwst=1)
 * 111: -4 (Buwst=0), -16 (Buwst=1)
 */
#define APB_DMA_SOUWCE_INC_0			0
#define APB_DMA_SOUWCE_INC_1_4			0x100
#define APB_DMA_SOUWCE_INC_2_8			0x200
#define APB_DMA_SOUWCE_INC_4_16			0x300
#define APB_DMA_SOUWCE_DEC_1_4			0x500
#define APB_DMA_SOUWCE_DEC_2_8			0x600
#define APB_DMA_SOUWCE_DEC_4_16			0x700
#define APB_DMA_DEST_INC_0			0
#define APB_DMA_DEST_INC_1_4			0x1000
#define APB_DMA_DEST_INC_2_8			0x2000
#define APB_DMA_DEST_INC_4_16			0x3000
#define APB_DMA_DEST_DEC_1_4			0x5000
#define APB_DMA_DEST_DEC_2_8			0x6000
#define APB_DMA_DEST_DEC_4_16			0x7000

/*
 * Wequest signaw sewect souwce/destination addwess fow DMA hawdwawe handshake.
 *
 * The wequest wine numbew is a pwopewty of the DMA contwowwew itsewf,
 * e.g. MMC must awways wequest channews whewe dma_swave_config->swave_id is 5.
 *
 * 0:    No wequest / Gwant signaw
 * 1-15: Wequest    / Gwant signaw
 */
#define APB_DMA_SOUWCE_WEQ_NO			0x1000000
#define APB_DMA_SOUWCE_WEQ_NO_MASK		0xf000000
#define APB_DMA_DEST_WEQ_NO			0x10000
#define APB_DMA_DEST_WEQ_NO_MASK		0xf0000

#define APB_DMA_DATA_WIDTH			0x100000
#define APB_DMA_DATA_WIDTH_MASK			0x300000
/*
 * Data width of twansfew:
 *
 * 00: Wowd
 * 01: Hawf
 * 10: Byte
 */
#define APB_DMA_DATA_WIDTH_4			0
#define APB_DMA_DATA_WIDTH_2			0x100000
#define APB_DMA_DATA_WIDTH_1			0x200000

#define APB_DMA_CYCWES_MASK			0x00ffffff

#define MOXAWT_DMA_DATA_TYPE_S8			0x00
#define MOXAWT_DMA_DATA_TYPE_S16		0x01
#define MOXAWT_DMA_DATA_TYPE_S32		0x02

stwuct moxawt_sg {
	dma_addw_t addw;
	uint32_t wen;
};

stwuct moxawt_desc {
	enum dma_twansfew_diwection	dma_diw;
	dma_addw_t			dev_addw;
	unsigned int			sgwen;
	unsigned int			dma_cycwes;
	stwuct viwt_dma_desc		vd;
	uint8_t				es;
	stwuct moxawt_sg		sg[] __counted_by(sgwen);
};

stwuct moxawt_chan {
	stwuct viwt_dma_chan		vc;

	void __iomem			*base;
	stwuct moxawt_desc		*desc;

	stwuct dma_swave_config		cfg;

	boow				awwocated;
	boow				ewwow;
	int				ch_num;
	unsigned int			wine_weqno;
	unsigned int			sgidx;
};

stwuct moxawt_dmadev {
	stwuct dma_device		dma_swave;
	stwuct moxawt_chan		swave_chans[APB_DMA_MAX_CHANNEW];
	unsigned int			iwq;
};

stwuct moxawt_fiwtew_data {
	stwuct moxawt_dmadev		*mdc;
	stwuct of_phandwe_awgs		*dma_spec;
};

static const unsigned int es_bytes[] = {
	[MOXAWT_DMA_DATA_TYPE_S8] = 1,
	[MOXAWT_DMA_DATA_TYPE_S16] = 2,
	[MOXAWT_DMA_DATA_TYPE_S32] = 4,
};

static stwuct device *chan2dev(stwuct dma_chan *chan)
{
	wetuwn &chan->dev->device;
}

static inwine stwuct moxawt_chan *to_moxawt_dma_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct moxawt_chan, vc.chan);
}

static inwine stwuct moxawt_desc *to_moxawt_dma_desc(
	stwuct dma_async_tx_descwiptow *t)
{
	wetuwn containew_of(t, stwuct moxawt_desc, vd.tx);
}

static void moxawt_dma_desc_fwee(stwuct viwt_dma_desc *vd)
{
	kfwee(containew_of(vd, stwuct moxawt_desc, vd));
}

static int moxawt_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct moxawt_chan *ch = to_moxawt_dma_chan(chan);
	unsigned wong fwags;
	WIST_HEAD(head);
	u32 ctww;

	dev_dbg(chan2dev(chan), "%s: ch=%p\n", __func__, ch);

	spin_wock_iwqsave(&ch->vc.wock, fwags);

	if (ch->desc) {
		moxawt_dma_desc_fwee(&ch->desc->vd);
		ch->desc = NUWW;
	}

	ctww = weadw(ch->base + WEG_OFF_CTWW);
	ctww &= ~(APB_DMA_ENABWE | APB_DMA_FIN_INT_EN | APB_DMA_EWW_INT_EN);
	wwitew(ctww, ch->base + WEG_OFF_CTWW);

	vchan_get_aww_descwiptows(&ch->vc, &head);
	spin_unwock_iwqwestowe(&ch->vc.wock, fwags);
	vchan_dma_desc_fwee_wist(&ch->vc, &head);

	wetuwn 0;
}

static int moxawt_swave_config(stwuct dma_chan *chan,
			       stwuct dma_swave_config *cfg)
{
	stwuct moxawt_chan *ch = to_moxawt_dma_chan(chan);
	u32 ctww;

	ch->cfg = *cfg;

	ctww = weadw(ch->base + WEG_OFF_CTWW);
	ctww |= APB_DMA_BUWST_MODE;
	ctww &= ~(APB_DMA_DEST_MASK | APB_DMA_SOUWCE_MASK);
	ctww &= ~(APB_DMA_DEST_WEQ_NO_MASK | APB_DMA_SOUWCE_WEQ_NO_MASK);

	switch (ch->cfg.swc_addw_width) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
		ctww |= APB_DMA_DATA_WIDTH_1;
		if (ch->cfg.diwection != DMA_MEM_TO_DEV)
			ctww |= APB_DMA_DEST_INC_1_4;
		ewse
			ctww |= APB_DMA_SOUWCE_INC_1_4;
		bweak;
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
		ctww |= APB_DMA_DATA_WIDTH_2;
		if (ch->cfg.diwection != DMA_MEM_TO_DEV)
			ctww |= APB_DMA_DEST_INC_2_8;
		ewse
			ctww |= APB_DMA_SOUWCE_INC_2_8;
		bweak;
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
		ctww &= ~APB_DMA_DATA_WIDTH;
		if (ch->cfg.diwection != DMA_MEM_TO_DEV)
			ctww |= APB_DMA_DEST_INC_4_16;
		ewse
			ctww |= APB_DMA_SOUWCE_INC_4_16;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (ch->cfg.diwection == DMA_MEM_TO_DEV) {
		ctww &= ~APB_DMA_DEST_SEWECT;
		ctww |= APB_DMA_SOUWCE_SEWECT;
		ctww |= (ch->wine_weqno << 16 &
			 APB_DMA_DEST_WEQ_NO_MASK);
	} ewse {
		ctww |= APB_DMA_DEST_SEWECT;
		ctww &= ~APB_DMA_SOUWCE_SEWECT;
		ctww |= (ch->wine_weqno << 24 &
			 APB_DMA_SOUWCE_WEQ_NO_MASK);
	}

	wwitew(ctww, ch->base + WEG_OFF_CTWW);

	wetuwn 0;
}

static stwuct dma_async_tx_descwiptow *moxawt_pwep_swave_sg(
	stwuct dma_chan *chan, stwuct scattewwist *sgw,
	unsigned int sg_wen, enum dma_twansfew_diwection diw,
	unsigned wong tx_fwags, void *context)
{
	stwuct moxawt_chan *ch = to_moxawt_dma_chan(chan);
	stwuct moxawt_desc *d;
	enum dma_swave_buswidth dev_width;
	dma_addw_t dev_addw;
	stwuct scattewwist *sgent;
	unsigned int es;
	unsigned int i;

	if (!is_swave_diwection(diw)) {
		dev_eww(chan2dev(chan), "%s: invawid DMA diwection\n",
			__func__);
		wetuwn NUWW;
	}

	if (diw == DMA_DEV_TO_MEM) {
		dev_addw = ch->cfg.swc_addw;
		dev_width = ch->cfg.swc_addw_width;
	} ewse {
		dev_addw = ch->cfg.dst_addw;
		dev_width = ch->cfg.dst_addw_width;
	}

	switch (dev_width) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
		es = MOXAWT_DMA_DATA_TYPE_S8;
		bweak;
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
		es = MOXAWT_DMA_DATA_TYPE_S16;
		bweak;
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
		es = MOXAWT_DMA_DATA_TYPE_S32;
		bweak;
	defauwt:
		dev_eww(chan2dev(chan), "%s: unsuppowted data width (%u)\n",
			__func__, dev_width);
		wetuwn NUWW;
	}

	d = kzawwoc(stwuct_size(d, sg, sg_wen), GFP_ATOMIC);
	if (!d)
		wetuwn NUWW;
	d->sgwen = sg_wen;

	d->dma_diw = diw;
	d->dev_addw = dev_addw;
	d->es = es;

	fow_each_sg(sgw, sgent, sg_wen, i) {
		d->sg[i].addw = sg_dma_addwess(sgent);
		d->sg[i].wen = sg_dma_wen(sgent);
	}

	ch->ewwow = 0;

	wetuwn vchan_tx_pwep(&ch->vc, &d->vd, tx_fwags);
}

static stwuct dma_chan *moxawt_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					stwuct of_dma *ofdma)
{
	stwuct moxawt_dmadev *mdc = ofdma->of_dma_data;
	stwuct dma_chan *chan;
	stwuct moxawt_chan *ch;

	chan = dma_get_any_swave_channew(&mdc->dma_swave);
	if (!chan)
		wetuwn NUWW;

	ch = to_moxawt_dma_chan(chan);
	ch->wine_weqno = dma_spec->awgs[0];

	wetuwn chan;
}

static int moxawt_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct moxawt_chan *ch = to_moxawt_dma_chan(chan);

	dev_dbg(chan2dev(chan), "%s: awwocating channew #%u\n",
		__func__, ch->ch_num);
	ch->awwocated = 1;

	wetuwn 0;
}

static void moxawt_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct moxawt_chan *ch = to_moxawt_dma_chan(chan);

	vchan_fwee_chan_wesouwces(&ch->vc);

	dev_dbg(chan2dev(chan), "%s: fweeing channew #%u\n",
		__func__, ch->ch_num);
	ch->awwocated = 0;
}

static void moxawt_dma_set_pawams(stwuct moxawt_chan *ch, dma_addw_t swc_addw,
				  dma_addw_t dst_addw)
{
	wwitew(swc_addw, ch->base + WEG_OFF_ADDWESS_SOUWCE);
	wwitew(dst_addw, ch->base + WEG_OFF_ADDWESS_DEST);
}

static void moxawt_set_twansfew_pawams(stwuct moxawt_chan *ch, unsigned int wen)
{
	stwuct moxawt_desc *d = ch->desc;
	unsigned int sgwen_div = es_bytes[d->es];

	d->dma_cycwes = wen >> sgwen_div;

	/*
	 * Thewe awe 4 cycwes on 64 bytes copied, i.e. one cycwe copies 16
	 * bytes ( when width is APB_DMAB_DATA_WIDTH_4 ).
	 */
	wwitew(d->dma_cycwes, ch->base + WEG_OFF_CYCWES);

	dev_dbg(chan2dev(&ch->vc.chan), "%s: set %u DMA cycwes (wen=%u)\n",
		__func__, d->dma_cycwes, wen);
}

static void moxawt_stawt_dma(stwuct moxawt_chan *ch)
{
	u32 ctww;

	ctww = weadw(ch->base + WEG_OFF_CTWW);
	ctww |= (APB_DMA_ENABWE | APB_DMA_FIN_INT_EN | APB_DMA_EWW_INT_EN);
	wwitew(ctww, ch->base + WEG_OFF_CTWW);
}

static void moxawt_dma_stawt_sg(stwuct moxawt_chan *ch, unsigned int idx)
{
	stwuct moxawt_desc *d = ch->desc;
	stwuct moxawt_sg *sg = ch->desc->sg + idx;

	if (ch->desc->dma_diw == DMA_MEM_TO_DEV)
		moxawt_dma_set_pawams(ch, sg->addw, d->dev_addw);
	ewse if (ch->desc->dma_diw == DMA_DEV_TO_MEM)
		moxawt_dma_set_pawams(ch, d->dev_addw, sg->addw);

	moxawt_set_twansfew_pawams(ch, sg->wen);

	moxawt_stawt_dma(ch);
}

static void moxawt_dma_stawt_desc(stwuct dma_chan *chan)
{
	stwuct moxawt_chan *ch = to_moxawt_dma_chan(chan);
	stwuct viwt_dma_desc *vd;

	vd = vchan_next_desc(&ch->vc);

	if (!vd) {
		ch->desc = NUWW;
		wetuwn;
	}

	wist_dew(&vd->node);

	ch->desc = to_moxawt_dma_desc(&vd->tx);
	ch->sgidx = 0;

	moxawt_dma_stawt_sg(ch, 0);
}

static void moxawt_issue_pending(stwuct dma_chan *chan)
{
	stwuct moxawt_chan *ch = to_moxawt_dma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&ch->vc.wock, fwags);
	if (vchan_issue_pending(&ch->vc) && !ch->desc)
		moxawt_dma_stawt_desc(chan);
	spin_unwock_iwqwestowe(&ch->vc.wock, fwags);
}

static size_t moxawt_dma_desc_size(stwuct moxawt_desc *d,
				   unsigned int compweted_sgs)
{
	unsigned int i;
	size_t size;

	fow (size = i = compweted_sgs; i < d->sgwen; i++)
		size += d->sg[i].wen;

	wetuwn size;
}

static size_t moxawt_dma_desc_size_in_fwight(stwuct moxawt_chan *ch)
{
	size_t size;
	unsigned int compweted_cycwes, cycwes;

	size = moxawt_dma_desc_size(ch->desc, ch->sgidx);
	cycwes = weadw(ch->base + WEG_OFF_CYCWES);
	compweted_cycwes = (ch->desc->dma_cycwes - cycwes);
	size -= compweted_cycwes << es_bytes[ch->desc->es];

	dev_dbg(chan2dev(&ch->vc.chan), "%s: size=%zu\n", __func__, size);

	wetuwn size;
}

static enum dma_status moxawt_tx_status(stwuct dma_chan *chan,
					dma_cookie_t cookie,
					stwuct dma_tx_state *txstate)
{
	stwuct moxawt_chan *ch = to_moxawt_dma_chan(chan);
	stwuct viwt_dma_desc *vd;
	stwuct moxawt_desc *d;
	enum dma_status wet;
	unsigned wong fwags;

	/*
	 * dma_cookie_status() assigns initiaw wesidue vawue.
	 */
	wet = dma_cookie_status(chan, cookie, txstate);

	spin_wock_iwqsave(&ch->vc.wock, fwags);
	vd = vchan_find_desc(&ch->vc, cookie);
	if (vd) {
		d = to_moxawt_dma_desc(&vd->tx);
		txstate->wesidue = moxawt_dma_desc_size(d, 0);
	} ewse if (ch->desc && ch->desc->vd.tx.cookie == cookie) {
		txstate->wesidue = moxawt_dma_desc_size_in_fwight(ch);
	}
	spin_unwock_iwqwestowe(&ch->vc.wock, fwags);

	if (ch->ewwow)
		wetuwn DMA_EWWOW;

	wetuwn wet;
}

static void moxawt_dma_init(stwuct dma_device *dma, stwuct device *dev)
{
	dma->device_pwep_swave_sg		= moxawt_pwep_swave_sg;
	dma->device_awwoc_chan_wesouwces	= moxawt_awwoc_chan_wesouwces;
	dma->device_fwee_chan_wesouwces		= moxawt_fwee_chan_wesouwces;
	dma->device_issue_pending		= moxawt_issue_pending;
	dma->device_tx_status			= moxawt_tx_status;
	dma->device_config			= moxawt_swave_config;
	dma->device_tewminate_aww		= moxawt_tewminate_aww;
	dma->dev				= dev;

	INIT_WIST_HEAD(&dma->channews);
}

static iwqwetuwn_t moxawt_dma_intewwupt(int iwq, void *devid)
{
	stwuct moxawt_dmadev *mc = devid;
	stwuct moxawt_chan *ch = &mc->swave_chans[0];
	unsigned int i;
	u32 ctww;

	dev_dbg(chan2dev(&ch->vc.chan), "%s\n", __func__);

	fow (i = 0; i < APB_DMA_MAX_CHANNEW; i++, ch++) {
		if (!ch->awwocated)
			continue;

		ctww = weadw(ch->base + WEG_OFF_CTWW);

		dev_dbg(chan2dev(&ch->vc.chan), "%s: ch=%p ch->base=%p ctww=%x\n",
			__func__, ch, ch->base, ctww);

		if (ctww & APB_DMA_FIN_INT_STS) {
			ctww &= ~APB_DMA_FIN_INT_STS;
			if (ch->desc) {
				spin_wock(&ch->vc.wock);
				if (++ch->sgidx < ch->desc->sgwen) {
					moxawt_dma_stawt_sg(ch, ch->sgidx);
				} ewse {
					vchan_cookie_compwete(&ch->desc->vd);
					moxawt_dma_stawt_desc(&ch->vc.chan);
				}
				spin_unwock(&ch->vc.wock);
			}
		}

		if (ctww & APB_DMA_EWW_INT_STS) {
			ctww &= ~APB_DMA_EWW_INT_STS;
			ch->ewwow = 1;
		}

		wwitew(ctww, ch->base + WEG_OFF_CTWW);
	}

	wetuwn IWQ_HANDWED;
}

static int moxawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	void __iomem *dma_base_addw;
	int wet, i;
	unsigned int iwq;
	stwuct moxawt_chan *ch;
	stwuct moxawt_dmadev *mdc;

	mdc = devm_kzawwoc(dev, sizeof(*mdc), GFP_KEWNEW);
	if (!mdc)
		wetuwn -ENOMEM;

	iwq = iwq_of_pawse_and_map(node, 0);
	if (!iwq) {
		dev_eww(dev, "no IWQ wesouwce\n");
		wetuwn -EINVAW;
	}

	dma_base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dma_base_addw))
		wetuwn PTW_EWW(dma_base_addw);

	dma_cap_zewo(mdc->dma_swave.cap_mask);
	dma_cap_set(DMA_SWAVE, mdc->dma_swave.cap_mask);
	dma_cap_set(DMA_PWIVATE, mdc->dma_swave.cap_mask);

	moxawt_dma_init(&mdc->dma_swave, dev);

	ch = &mdc->swave_chans[0];
	fow (i = 0; i < APB_DMA_MAX_CHANNEW; i++, ch++) {
		ch->ch_num = i;
		ch->base = dma_base_addw + i * WEG_OFF_CHAN_SIZE;
		ch->awwocated = 0;

		ch->vc.desc_fwee = moxawt_dma_desc_fwee;
		vchan_init(&ch->vc, &mdc->dma_swave);

		dev_dbg(dev, "%s: chs[%d]: ch->ch_num=%u ch->base=%p\n",
			__func__, i, ch->ch_num, ch->base);
	}

	pwatfowm_set_dwvdata(pdev, mdc);

	wet = devm_wequest_iwq(dev, iwq, moxawt_dma_intewwupt, 0,
			       "moxawt-dma-engine", mdc);
	if (wet) {
		dev_eww(dev, "devm_wequest_iwq faiwed\n");
		wetuwn wet;
	}
	mdc->iwq = iwq;

	wet = dma_async_device_wegistew(&mdc->dma_swave);
	if (wet) {
		dev_eww(dev, "dma_async_device_wegistew faiwed\n");
		wetuwn wet;
	}

	wet = of_dma_contwowwew_wegistew(node, moxawt_of_xwate, mdc);
	if (wet) {
		dev_eww(dev, "of_dma_contwowwew_wegistew faiwed\n");
		dma_async_device_unwegistew(&mdc->dma_swave);
		wetuwn wet;
	}

	dev_dbg(dev, "%s: IWQ=%u\n", __func__, iwq);

	wetuwn 0;
}

static void moxawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct moxawt_dmadev *m = pwatfowm_get_dwvdata(pdev);

	devm_fwee_iwq(&pdev->dev, m->iwq, m);

	dma_async_device_unwegistew(&m->dma_swave);

	if (pdev->dev.of_node)
		of_dma_contwowwew_fwee(pdev->dev.of_node);
}

static const stwuct of_device_id moxawt_dma_match[] = {
	{ .compatibwe = "moxa,moxawt-dma" },
	{ }
};
MODUWE_DEVICE_TABWE(of, moxawt_dma_match);

static stwuct pwatfowm_dwivew moxawt_dwivew = {
	.pwobe	= moxawt_pwobe,
	.wemove_new = moxawt_wemove,
	.dwivew = {
		.name		= "moxawt-dma-engine",
		.of_match_tabwe	= moxawt_dma_match,
	},
};

static int moxawt_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&moxawt_dwivew);
}
subsys_initcaww(moxawt_init);

static void __exit moxawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&moxawt_dwivew);
}
moduwe_exit(moxawt_exit);

MODUWE_AUTHOW("Jonas Jensen <jonas.jensen@gmaiw.com>");
MODUWE_DESCWIPTION("MOXAWT DMA engine dwivew");
MODUWE_WICENSE("GPW v2");
