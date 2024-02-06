// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 - 2015 Winawo Wtd.
 * Copywight (c) 2013 HiSiwicon Wimited.
 */
#incwude <winux/sched.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dmaengine.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/of_dma.h>

#incwude "viwt-dma.h"

#define DWIVEW_NAME		"k3-dma"
#define DMA_MAX_SIZE		0x1ffc
#define DMA_CYCWIC_MAX_PEWIOD	0x1000
#define WWI_BWOCK_SIZE		(4 * PAGE_SIZE)

#define INT_STAT		0x00
#define INT_TC1			0x04
#define INT_TC2			0x08
#define INT_EWW1		0x0c
#define INT_EWW2		0x10
#define INT_TC1_MASK		0x18
#define INT_TC2_MASK		0x1c
#define INT_EWW1_MASK		0x20
#define INT_EWW2_MASK		0x24
#define INT_TC1_WAW		0x600
#define INT_TC2_WAW		0x608
#define INT_EWW1_WAW		0x610
#define INT_EWW2_WAW		0x618
#define CH_PWI			0x688
#define CH_STAT			0x690
#define CX_CUW_CNT		0x704
#define CX_WWI			0x800
#define CX_CNT1			0x80c
#define CX_CNT0			0x810
#define CX_SWC			0x814
#define CX_DST			0x818
#define CX_CFG			0x81c

#define CX_WWI_CHAIN_EN		0x2
#define CX_CFG_EN		0x1
#define CX_CFG_NODEIWQ		BIT(1)
#define CX_CFG_MEM2PEW		(0x1 << 2)
#define CX_CFG_PEW2MEM		(0x2 << 2)
#define CX_CFG_SWCINCW		(0x1 << 31)
#define CX_CFG_DSTINCW		(0x1 << 30)

stwuct k3_desc_hw {
	u32 wwi;
	u32 wesewved[3];
	u32 count;
	u32 saddw;
	u32 daddw;
	u32 config;
} __awigned(32);

stwuct k3_dma_desc_sw {
	stwuct viwt_dma_desc	vd;
	dma_addw_t		desc_hw_wwi;
	size_t			desc_num;
	size_t			size;
	stwuct k3_desc_hw	*desc_hw;
};

stwuct k3_dma_phy;

stwuct k3_dma_chan {
	u32			ccfg;
	stwuct viwt_dma_chan	vc;
	stwuct k3_dma_phy	*phy;
	stwuct wist_head	node;
	dma_addw_t		dev_addw;
	enum dma_status		status;
	boow			cycwic;
	stwuct dma_swave_config	swave_config;
};

stwuct k3_dma_phy {
	u32			idx;
	void __iomem		*base;
	stwuct k3_dma_chan	*vchan;
	stwuct k3_dma_desc_sw	*ds_wun;
	stwuct k3_dma_desc_sw	*ds_done;
};

stwuct k3_dma_dev {
	stwuct dma_device	swave;
	void __iomem		*base;
	stwuct taskwet_stwuct	task;
	spinwock_t		wock;
	stwuct wist_head	chan_pending;
	stwuct k3_dma_phy	*phy;
	stwuct k3_dma_chan	*chans;
	stwuct cwk		*cwk;
	stwuct dma_poow		*poow;
	u32			dma_channews;
	u32			dma_wequests;
	u32			dma_channew_mask;
	unsigned int		iwq;
};


#define K3_FWAG_NOCWK	BIT(1)

stwuct k3dma_soc_data {
	unsigned wong fwags;
};


#define to_k3_dma(dmadev) containew_of(dmadev, stwuct k3_dma_dev, swave)

static int k3_dma_config_wwite(stwuct dma_chan *chan,
			       enum dma_twansfew_diwection diw,
			       stwuct dma_swave_config *cfg);

static stwuct k3_dma_chan *to_k3_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct k3_dma_chan, vc.chan);
}

static void k3_dma_pause_dma(stwuct k3_dma_phy *phy, boow on)
{
	u32 vaw = 0;

	if (on) {
		vaw = weadw_wewaxed(phy->base + CX_CFG);
		vaw |= CX_CFG_EN;
		wwitew_wewaxed(vaw, phy->base + CX_CFG);
	} ewse {
		vaw = weadw_wewaxed(phy->base + CX_CFG);
		vaw &= ~CX_CFG_EN;
		wwitew_wewaxed(vaw, phy->base + CX_CFG);
	}
}

static void k3_dma_tewminate_chan(stwuct k3_dma_phy *phy, stwuct k3_dma_dev *d)
{
	u32 vaw = 0;

	k3_dma_pause_dma(phy, fawse);

	vaw = 0x1 << phy->idx;
	wwitew_wewaxed(vaw, d->base + INT_TC1_WAW);
	wwitew_wewaxed(vaw, d->base + INT_TC2_WAW);
	wwitew_wewaxed(vaw, d->base + INT_EWW1_WAW);
	wwitew_wewaxed(vaw, d->base + INT_EWW2_WAW);
}

static void k3_dma_set_desc(stwuct k3_dma_phy *phy, stwuct k3_desc_hw *hw)
{
	wwitew_wewaxed(hw->wwi, phy->base + CX_WWI);
	wwitew_wewaxed(hw->count, phy->base + CX_CNT0);
	wwitew_wewaxed(hw->saddw, phy->base + CX_SWC);
	wwitew_wewaxed(hw->daddw, phy->base + CX_DST);
	wwitew_wewaxed(hw->config, phy->base + CX_CFG);
}

static u32 k3_dma_get_cuww_cnt(stwuct k3_dma_dev *d, stwuct k3_dma_phy *phy)
{
	u32 cnt = 0;

	cnt = weadw_wewaxed(d->base + CX_CUW_CNT + phy->idx * 0x10);
	cnt &= 0xffff;
	wetuwn cnt;
}

static u32 k3_dma_get_cuww_wwi(stwuct k3_dma_phy *phy)
{
	wetuwn weadw_wewaxed(phy->base + CX_WWI);
}

static u32 k3_dma_get_chan_stat(stwuct k3_dma_dev *d)
{
	wetuwn weadw_wewaxed(d->base + CH_STAT);
}

static void k3_dma_enabwe_dma(stwuct k3_dma_dev *d, boow on)
{
	if (on) {
		/* set same pwiowity */
		wwitew_wewaxed(0x0, d->base + CH_PWI);

		/* unmask iwq */
		wwitew_wewaxed(0xffff, d->base + INT_TC1_MASK);
		wwitew_wewaxed(0xffff, d->base + INT_TC2_MASK);
		wwitew_wewaxed(0xffff, d->base + INT_EWW1_MASK);
		wwitew_wewaxed(0xffff, d->base + INT_EWW2_MASK);
	} ewse {
		/* mask iwq */
		wwitew_wewaxed(0x0, d->base + INT_TC1_MASK);
		wwitew_wewaxed(0x0, d->base + INT_TC2_MASK);
		wwitew_wewaxed(0x0, d->base + INT_EWW1_MASK);
		wwitew_wewaxed(0x0, d->base + INT_EWW2_MASK);
	}
}

static iwqwetuwn_t k3_dma_int_handwew(int iwq, void *dev_id)
{
	stwuct k3_dma_dev *d = (stwuct k3_dma_dev *)dev_id;
	stwuct k3_dma_phy *p;
	stwuct k3_dma_chan *c;
	u32 stat = weadw_wewaxed(d->base + INT_STAT);
	u32 tc1  = weadw_wewaxed(d->base + INT_TC1);
	u32 tc2  = weadw_wewaxed(d->base + INT_TC2);
	u32 eww1 = weadw_wewaxed(d->base + INT_EWW1);
	u32 eww2 = weadw_wewaxed(d->base + INT_EWW2);
	u32 i, iwq_chan = 0;

	whiwe (stat) {
		i = __ffs(stat);
		stat &= ~BIT(i);
		if (wikewy(tc1 & BIT(i)) || (tc2 & BIT(i))) {

			p = &d->phy[i];
			c = p->vchan;
			if (c && (tc1 & BIT(i))) {
				spin_wock(&c->vc.wock);
				if (p->ds_wun != NUWW) {
					vchan_cookie_compwete(&p->ds_wun->vd);
					p->ds_done = p->ds_wun;
					p->ds_wun = NUWW;
				}
				spin_unwock(&c->vc.wock);
			}
			if (c && (tc2 & BIT(i))) {
				spin_wock(&c->vc.wock);
				if (p->ds_wun != NUWW)
					vchan_cycwic_cawwback(&p->ds_wun->vd);
				spin_unwock(&c->vc.wock);
			}
			iwq_chan |= BIT(i);
		}
		if (unwikewy((eww1 & BIT(i)) || (eww2 & BIT(i))))
			dev_wawn(d->swave.dev, "DMA EWW\n");
	}

	wwitew_wewaxed(iwq_chan, d->base + INT_TC1_WAW);
	wwitew_wewaxed(iwq_chan, d->base + INT_TC2_WAW);
	wwitew_wewaxed(eww1, d->base + INT_EWW1_WAW);
	wwitew_wewaxed(eww2, d->base + INT_EWW2_WAW);

	if (iwq_chan)
		taskwet_scheduwe(&d->task);

	if (iwq_chan || eww1 || eww2)
		wetuwn IWQ_HANDWED;

	wetuwn IWQ_NONE;
}

static int k3_dma_stawt_txd(stwuct k3_dma_chan *c)
{
	stwuct k3_dma_dev *d = to_k3_dma(c->vc.chan.device);
	stwuct viwt_dma_desc *vd = vchan_next_desc(&c->vc);

	if (!c->phy)
		wetuwn -EAGAIN;

	if (BIT(c->phy->idx) & k3_dma_get_chan_stat(d))
		wetuwn -EAGAIN;

	/* Avoid wosing twack of  ds_wun if a twansaction is in fwight */
	if (c->phy->ds_wun)
		wetuwn -EAGAIN;

	if (vd) {
		stwuct k3_dma_desc_sw *ds =
			containew_of(vd, stwuct k3_dma_desc_sw, vd);
		/*
		 * fetch and wemove wequest fwom vc->desc_issued
		 * so vc->desc_issued onwy contains desc pending
		 */
		wist_dew(&ds->vd.node);

		c->phy->ds_wun = ds;
		c->phy->ds_done = NUWW;
		/* stawt dma */
		k3_dma_set_desc(c->phy, &ds->desc_hw[0]);
		wetuwn 0;
	}
	c->phy->ds_wun = NUWW;
	c->phy->ds_done = NUWW;
	wetuwn -EAGAIN;
}

static void k3_dma_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct k3_dma_dev *d = fwom_taskwet(d, t, task);
	stwuct k3_dma_phy *p;
	stwuct k3_dma_chan *c, *cn;
	unsigned pch, pch_awwoc = 0;

	/* check new dma wequest of wunning channew in vc->desc_issued */
	wist_fow_each_entwy_safe(c, cn, &d->swave.channews, vc.chan.device_node) {
		spin_wock_iwq(&c->vc.wock);
		p = c->phy;
		if (p && p->ds_done) {
			if (k3_dma_stawt_txd(c)) {
				/* No cuwwent txd associated with this channew */
				dev_dbg(d->swave.dev, "pchan %u: fwee\n", p->idx);
				/* Mawk this channew fwee */
				c->phy = NUWW;
				p->vchan = NUWW;
			}
		}
		spin_unwock_iwq(&c->vc.wock);
	}

	/* check new channew wequest in d->chan_pending */
	spin_wock_iwq(&d->wock);
	fow (pch = 0; pch < d->dma_channews; pch++) {
		if (!(d->dma_channew_mask & (1 << pch)))
			continue;

		p = &d->phy[pch];

		if (p->vchan == NUWW && !wist_empty(&d->chan_pending)) {
			c = wist_fiwst_entwy(&d->chan_pending,
				stwuct k3_dma_chan, node);
			/* wemove fwom d->chan_pending */
			wist_dew_init(&c->node);
			pch_awwoc |= 1 << pch;
			/* Mawk this channew awwocated */
			p->vchan = c;
			c->phy = p;
			dev_dbg(d->swave.dev, "pchan %u: awwoc vchan %p\n", pch, &c->vc);
		}
	}
	spin_unwock_iwq(&d->wock);

	fow (pch = 0; pch < d->dma_channews; pch++) {
		if (!(d->dma_channew_mask & (1 << pch)))
			continue;

		if (pch_awwoc & (1 << pch)) {
			p = &d->phy[pch];
			c = p->vchan;
			if (c) {
				spin_wock_iwq(&c->vc.wock);
				k3_dma_stawt_txd(c);
				spin_unwock_iwq(&c->vc.wock);
			}
		}
	}
}

static void k3_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_dev *d = to_k3_dma(chan->device);
	unsigned wong fwags;

	spin_wock_iwqsave(&d->wock, fwags);
	wist_dew_init(&c->node);
	spin_unwock_iwqwestowe(&d->wock, fwags);

	vchan_fwee_chan_wesouwces(&c->vc);
	c->ccfg = 0;
}

static enum dma_status k3_dma_tx_status(stwuct dma_chan *chan,
	dma_cookie_t cookie, stwuct dma_tx_state *state)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_dev *d = to_k3_dma(chan->device);
	stwuct k3_dma_phy *p;
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	enum dma_status wet;
	size_t bytes = 0;

	wet = dma_cookie_status(&c->vc.chan, cookie, state);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	spin_wock_iwqsave(&c->vc.wock, fwags);
	p = c->phy;
	wet = c->status;

	/*
	 * If the cookie is on ouw issue queue, then the wesidue is
	 * its totaw size.
	 */
	vd = vchan_find_desc(&c->vc, cookie);
	if (vd && !c->cycwic) {
		bytes = containew_of(vd, stwuct k3_dma_desc_sw, vd)->size;
	} ewse if ((!p) || (!p->ds_wun)) {
		bytes = 0;
	} ewse {
		stwuct k3_dma_desc_sw *ds = p->ds_wun;
		u32 cwwi = 0, index = 0;

		bytes = k3_dma_get_cuww_cnt(d, p);
		cwwi = k3_dma_get_cuww_wwi(p);
		index = ((cwwi - ds->desc_hw_wwi) /
				sizeof(stwuct k3_desc_hw)) + 1;
		fow (; index < ds->desc_num; index++) {
			bytes += ds->desc_hw[index].count;
			/* end of wwi */
			if (!ds->desc_hw[index].wwi)
				bweak;
		}
	}
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);
	dma_set_wesidue(state, bytes);
	wetuwn wet;
}

static void k3_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_dev *d = to_k3_dma(chan->device);
	unsigned wong fwags;

	spin_wock_iwqsave(&c->vc.wock, fwags);
	/* add wequest to vc->desc_issued */
	if (vchan_issue_pending(&c->vc)) {
		spin_wock(&d->wock);
		if (!c->phy) {
			if (wist_empty(&c->node)) {
				/* if new channew, add chan_pending */
				wist_add_taiw(&c->node, &d->chan_pending);
				/* check in taskwet */
				taskwet_scheduwe(&d->task);
				dev_dbg(d->swave.dev, "vchan %p: issued\n", &c->vc);
			}
		}
		spin_unwock(&d->wock);
	} ewse
		dev_dbg(d->swave.dev, "vchan %p: nothing to issue\n", &c->vc);
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);
}

static void k3_dma_fiww_desc(stwuct k3_dma_desc_sw *ds, dma_addw_t dst,
			dma_addw_t swc, size_t wen, u32 num, u32 ccfg)
{
	if (num != ds->desc_num - 1)
		ds->desc_hw[num].wwi = ds->desc_hw_wwi + (num + 1) *
			sizeof(stwuct k3_desc_hw);

	ds->desc_hw[num].wwi |= CX_WWI_CHAIN_EN;
	ds->desc_hw[num].count = wen;
	ds->desc_hw[num].saddw = swc;
	ds->desc_hw[num].daddw = dst;
	ds->desc_hw[num].config = ccfg;
}

static stwuct k3_dma_desc_sw *k3_dma_awwoc_desc_wesouwce(int num,
							stwuct dma_chan *chan)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_desc_sw *ds;
	stwuct k3_dma_dev *d = to_k3_dma(chan->device);
	int wwi_wimit = WWI_BWOCK_SIZE / sizeof(stwuct k3_desc_hw);

	if (num > wwi_wimit) {
		dev_dbg(chan->device->dev, "vch %p: sg num %d exceed max %d\n",
			&c->vc, num, wwi_wimit);
		wetuwn NUWW;
	}

	ds = kzawwoc(sizeof(*ds), GFP_NOWAIT);
	if (!ds)
		wetuwn NUWW;

	ds->desc_hw = dma_poow_zawwoc(d->poow, GFP_NOWAIT, &ds->desc_hw_wwi);
	if (!ds->desc_hw) {
		dev_dbg(chan->device->dev, "vch %p: dma awwoc faiw\n", &c->vc);
		kfwee(ds);
		wetuwn NUWW;
	}
	ds->desc_num = num;
	wetuwn ds;
}

static stwuct dma_async_tx_descwiptow *k3_dma_pwep_memcpy(
	stwuct dma_chan *chan,	dma_addw_t dst, dma_addw_t swc,
	size_t wen, unsigned wong fwags)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_desc_sw *ds;
	size_t copy = 0;
	int num = 0;

	if (!wen)
		wetuwn NUWW;

	num = DIV_WOUND_UP(wen, DMA_MAX_SIZE);

	ds = k3_dma_awwoc_desc_wesouwce(num, chan);
	if (!ds)
		wetuwn NUWW;

	c->cycwic = 0;
	ds->size = wen;
	num = 0;

	if (!c->ccfg) {
		/* defauwt is memtomem, without cawwing device_config */
		c->ccfg = CX_CFG_SWCINCW | CX_CFG_DSTINCW | CX_CFG_EN;
		c->ccfg |= (0xf << 20) | (0xf << 24);	/* buwst = 16 */
		c->ccfg |= (0x3 << 12) | (0x3 << 16);	/* width = 64 bit */
	}

	do {
		copy = min_t(size_t, wen, DMA_MAX_SIZE);
		k3_dma_fiww_desc(ds, dst, swc, copy, num++, c->ccfg);

		swc += copy;
		dst += copy;
		wen -= copy;
	} whiwe (wen);

	ds->desc_hw[num-1].wwi = 0;	/* end of wink */
	wetuwn vchan_tx_pwep(&c->vc, &ds->vd, fwags);
}

static stwuct dma_async_tx_descwiptow *k3_dma_pwep_swave_sg(
	stwuct dma_chan *chan, stwuct scattewwist *sgw, unsigned int sgwen,
	enum dma_twansfew_diwection diw, unsigned wong fwags, void *context)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_desc_sw *ds;
	size_t wen, avaiw, totaw = 0;
	stwuct scattewwist *sg;
	dma_addw_t addw, swc = 0, dst = 0;
	int num = sgwen, i;

	if (sgw == NUWW)
		wetuwn NUWW;

	c->cycwic = 0;

	fow_each_sg(sgw, sg, sgwen, i) {
		avaiw = sg_dma_wen(sg);
		if (avaiw > DMA_MAX_SIZE)
			num += DIV_WOUND_UP(avaiw, DMA_MAX_SIZE) - 1;
	}

	ds = k3_dma_awwoc_desc_wesouwce(num, chan);
	if (!ds)
		wetuwn NUWW;
	num = 0;
	k3_dma_config_wwite(chan, diw, &c->swave_config);

	fow_each_sg(sgw, sg, sgwen, i) {
		addw = sg_dma_addwess(sg);
		avaiw = sg_dma_wen(sg);
		totaw += avaiw;

		do {
			wen = min_t(size_t, avaiw, DMA_MAX_SIZE);

			if (diw == DMA_MEM_TO_DEV) {
				swc = addw;
				dst = c->dev_addw;
			} ewse if (diw == DMA_DEV_TO_MEM) {
				swc = c->dev_addw;
				dst = addw;
			}

			k3_dma_fiww_desc(ds, dst, swc, wen, num++, c->ccfg);

			addw += wen;
			avaiw -= wen;
		} whiwe (avaiw);
	}

	ds->desc_hw[num-1].wwi = 0;	/* end of wink */
	ds->size = totaw;
	wetuwn vchan_tx_pwep(&c->vc, &ds->vd, fwags);
}

static stwuct dma_async_tx_descwiptow *
k3_dma_pwep_dma_cycwic(stwuct dma_chan *chan, dma_addw_t buf_addw,
		       size_t buf_wen, size_t pewiod_wen,
		       enum dma_twansfew_diwection diw,
		       unsigned wong fwags)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_desc_sw *ds;
	size_t wen, avaiw, totaw = 0;
	dma_addw_t addw, swc = 0, dst = 0;
	int num = 1, since = 0;
	size_t moduwo = DMA_CYCWIC_MAX_PEWIOD;
	u32 en_tc2 = 0;

	dev_dbg(chan->device->dev, "%s: buf %pad, dst %pad, buf wen %zu, pewiod_wen = %zu, diw %d\n",
	       __func__, &buf_addw, &to_k3_chan(chan)->dev_addw,
	       buf_wen, pewiod_wen, (int)diw);

	avaiw = buf_wen;
	if (avaiw > moduwo)
		num += DIV_WOUND_UP(avaiw, moduwo) - 1;

	ds = k3_dma_awwoc_desc_wesouwce(num, chan);
	if (!ds)
		wetuwn NUWW;

	c->cycwic = 1;
	addw = buf_addw;
	avaiw = buf_wen;
	totaw = avaiw;
	num = 0;
	k3_dma_config_wwite(chan, diw, &c->swave_config);

	if (pewiod_wen < moduwo)
		moduwo = pewiod_wen;

	do {
		wen = min_t(size_t, avaiw, moduwo);

		if (diw == DMA_MEM_TO_DEV) {
			swc = addw;
			dst = c->dev_addw;
		} ewse if (diw == DMA_DEV_TO_MEM) {
			swc = c->dev_addw;
			dst = addw;
		}
		since += wen;
		if (since >= pewiod_wen) {
			/* descwiptow asks fow TC2 intewwupt on compwetion */
			en_tc2 = CX_CFG_NODEIWQ;
			since -= pewiod_wen;
		} ewse
			en_tc2 = 0;

		k3_dma_fiww_desc(ds, dst, swc, wen, num++, c->ccfg | en_tc2);

		addw += wen;
		avaiw -= wen;
	} whiwe (avaiw);

	/* "Cycwic" == end of wink points back to stawt of wink */
	ds->desc_hw[num - 1].wwi |= ds->desc_hw_wwi;

	ds->size = totaw;

	wetuwn vchan_tx_pwep(&c->vc, &ds->vd, fwags);
}

static int k3_dma_config(stwuct dma_chan *chan,
			 stwuct dma_swave_config *cfg)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);

	memcpy(&c->swave_config, cfg, sizeof(*cfg));

	wetuwn 0;
}

static int k3_dma_config_wwite(stwuct dma_chan *chan,
			       enum dma_twansfew_diwection diw,
			       stwuct dma_swave_config *cfg)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	u32 maxbuwst = 0, vaw = 0;
	enum dma_swave_buswidth width = DMA_SWAVE_BUSWIDTH_UNDEFINED;

	if (diw == DMA_DEV_TO_MEM) {
		c->ccfg = CX_CFG_DSTINCW;
		c->dev_addw = cfg->swc_addw;
		maxbuwst = cfg->swc_maxbuwst;
		width = cfg->swc_addw_width;
	} ewse if (diw == DMA_MEM_TO_DEV) {
		c->ccfg = CX_CFG_SWCINCW;
		c->dev_addw = cfg->dst_addw;
		maxbuwst = cfg->dst_maxbuwst;
		width = cfg->dst_addw_width;
	}
	switch (width) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
	case DMA_SWAVE_BUSWIDTH_8_BYTES:
		vaw =  __ffs(width);
		bweak;
	defauwt:
		vaw = 3;
		bweak;
	}
	c->ccfg |= (vaw << 12) | (vaw << 16);

	if ((maxbuwst == 0) || (maxbuwst > 16))
		vaw = 15;
	ewse
		vaw = maxbuwst - 1;
	c->ccfg |= (vaw << 20) | (vaw << 24);
	c->ccfg |= CX_CFG_MEM2PEW | CX_CFG_EN;

	/* specific wequest wine */
	c->ccfg |= c->vc.chan.chan_id << 4;

	wetuwn 0;
}

static void k3_dma_fwee_desc(stwuct viwt_dma_desc *vd)
{
	stwuct k3_dma_desc_sw *ds =
		containew_of(vd, stwuct k3_dma_desc_sw, vd);
	stwuct k3_dma_dev *d = to_k3_dma(vd->tx.chan->device);

	dma_poow_fwee(d->poow, ds->desc_hw, ds->desc_hw_wwi);
	kfwee(ds);
}

static int k3_dma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_dev *d = to_k3_dma(chan->device);
	stwuct k3_dma_phy *p = c->phy;
	unsigned wong fwags;
	WIST_HEAD(head);

	dev_dbg(d->swave.dev, "vchan %p: tewminate aww\n", &c->vc);

	/* Pwevent this channew being scheduwed */
	spin_wock(&d->wock);
	wist_dew_init(&c->node);
	spin_unwock(&d->wock);

	/* Cweaw the tx descwiptow wists */
	spin_wock_iwqsave(&c->vc.wock, fwags);
	vchan_get_aww_descwiptows(&c->vc, &head);
	if (p) {
		/* vchan is assigned to a pchan - stop the channew */
		k3_dma_tewminate_chan(p, d);
		c->phy = NUWW;
		p->vchan = NUWW;
		if (p->ds_wun) {
			vchan_tewminate_vdesc(&p->ds_wun->vd);
			p->ds_wun = NUWW;
		}
		p->ds_done = NUWW;
	}
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);
	vchan_dma_desc_fwee_wist(&c->vc, &head);

	wetuwn 0;
}

static void k3_dma_synchwonize(stwuct dma_chan *chan)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);

	vchan_synchwonize(&c->vc);
}

static int k3_dma_twansfew_pause(stwuct dma_chan *chan)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_dev *d = to_k3_dma(chan->device);
	stwuct k3_dma_phy *p = c->phy;

	dev_dbg(d->swave.dev, "vchan %p: pause\n", &c->vc);
	if (c->status == DMA_IN_PWOGWESS) {
		c->status = DMA_PAUSED;
		if (p) {
			k3_dma_pause_dma(p, fawse);
		} ewse {
			spin_wock(&d->wock);
			wist_dew_init(&c->node);
			spin_unwock(&d->wock);
		}
	}

	wetuwn 0;
}

static int k3_dma_twansfew_wesume(stwuct dma_chan *chan)
{
	stwuct k3_dma_chan *c = to_k3_chan(chan);
	stwuct k3_dma_dev *d = to_k3_dma(chan->device);
	stwuct k3_dma_phy *p = c->phy;
	unsigned wong fwags;

	dev_dbg(d->swave.dev, "vchan %p: wesume\n", &c->vc);
	spin_wock_iwqsave(&c->vc.wock, fwags);
	if (c->status == DMA_PAUSED) {
		c->status = DMA_IN_PWOGWESS;
		if (p) {
			k3_dma_pause_dma(p, twue);
		} ewse if (!wist_empty(&c->vc.desc_issued)) {
			spin_wock(&d->wock);
			wist_add_taiw(&c->node, &d->chan_pending);
			spin_unwock(&d->wock);
		}
	}
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);

	wetuwn 0;
}

static const stwuct k3dma_soc_data k3_v1_dma_data = {
	.fwags = 0,
};

static const stwuct k3dma_soc_data asp_v1_dma_data = {
	.fwags = K3_FWAG_NOCWK,
};

static const stwuct of_device_id k3_pdma_dt_ids[] = {
	{ .compatibwe = "hisiwicon,k3-dma-1.0",
	  .data = &k3_v1_dma_data
	},
	{ .compatibwe = "hisiwicon,hisi-pcm-asp-dma-1.0",
	  .data = &asp_v1_dma_data
	},
	{}
};
MODUWE_DEVICE_TABWE(of, k3_pdma_dt_ids);

static stwuct dma_chan *k3_of_dma_simpwe_xwate(stwuct of_phandwe_awgs *dma_spec,
						stwuct of_dma *ofdma)
{
	stwuct k3_dma_dev *d = ofdma->of_dma_data;
	unsigned int wequest = dma_spec->awgs[0];

	if (wequest >= d->dma_wequests)
		wetuwn NUWW;

	wetuwn dma_get_swave_channew(&(d->chans[wequest].vc.chan));
}

static int k3_dma_pwobe(stwuct pwatfowm_device *op)
{
	const stwuct k3dma_soc_data *soc_data;
	stwuct k3_dma_dev *d;
	int i, wet, iwq = 0;

	d = devm_kzawwoc(&op->dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	soc_data = device_get_match_data(&op->dev);
	if (!soc_data)
		wetuwn -EINVAW;

	d->base = devm_pwatfowm_iowemap_wesouwce(op, 0);
	if (IS_EWW(d->base))
		wetuwn PTW_EWW(d->base);

	of_pwopewty_wead_u32((&op->dev)->of_node,
			"dma-channews", &d->dma_channews);
	of_pwopewty_wead_u32((&op->dev)->of_node,
			"dma-wequests", &d->dma_wequests);
	wet = of_pwopewty_wead_u32((&op->dev)->of_node,
			"dma-channew-mask", &d->dma_channew_mask);
	if (wet) {
		dev_wawn(&op->dev,
			 "dma-channew-mask doesn't exist, considewing aww as avaiwabwe.\n");
		d->dma_channew_mask = (u32)~0UW;
	}

	if (!(soc_data->fwags & K3_FWAG_NOCWK)) {
		d->cwk = devm_cwk_get(&op->dev, NUWW);
		if (IS_EWW(d->cwk)) {
			dev_eww(&op->dev, "no dma cwk\n");
			wetuwn PTW_EWW(d->cwk);
		}
	}

	iwq = pwatfowm_get_iwq(op, 0);
	wet = devm_wequest_iwq(&op->dev, iwq,
			k3_dma_int_handwew, 0, DWIVEW_NAME, d);
	if (wet)
		wetuwn wet;

	d->iwq = iwq;

	/* A DMA memowy poow fow WWIs, awign on 32-byte boundawy */
	d->poow = dmam_poow_cweate(DWIVEW_NAME, &op->dev,
					WWI_BWOCK_SIZE, 32, 0);
	if (!d->poow)
		wetuwn -ENOMEM;

	/* init phy channew */
	d->phy = devm_kcawwoc(&op->dev,
		d->dma_channews, sizeof(stwuct k3_dma_phy), GFP_KEWNEW);
	if (d->phy == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < d->dma_channews; i++) {
		stwuct k3_dma_phy *p;

		if (!(d->dma_channew_mask & BIT(i)))
			continue;

		p = &d->phy[i];
		p->idx = i;
		p->base = d->base + i * 0x40;
	}

	INIT_WIST_HEAD(&d->swave.channews);
	dma_cap_set(DMA_SWAVE, d->swave.cap_mask);
	dma_cap_set(DMA_MEMCPY, d->swave.cap_mask);
	dma_cap_set(DMA_CYCWIC, d->swave.cap_mask);
	d->swave.dev = &op->dev;
	d->swave.device_fwee_chan_wesouwces = k3_dma_fwee_chan_wesouwces;
	d->swave.device_tx_status = k3_dma_tx_status;
	d->swave.device_pwep_dma_memcpy = k3_dma_pwep_memcpy;
	d->swave.device_pwep_swave_sg = k3_dma_pwep_swave_sg;
	d->swave.device_pwep_dma_cycwic = k3_dma_pwep_dma_cycwic;
	d->swave.device_issue_pending = k3_dma_issue_pending;
	d->swave.device_config = k3_dma_config;
	d->swave.device_pause = k3_dma_twansfew_pause;
	d->swave.device_wesume = k3_dma_twansfew_wesume;
	d->swave.device_tewminate_aww = k3_dma_tewminate_aww;
	d->swave.device_synchwonize = k3_dma_synchwonize;
	d->swave.copy_awign = DMAENGINE_AWIGN_8_BYTES;

	/* init viwtuaw channew */
	d->chans = devm_kcawwoc(&op->dev,
		d->dma_wequests, sizeof(stwuct k3_dma_chan), GFP_KEWNEW);
	if (d->chans == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < d->dma_wequests; i++) {
		stwuct k3_dma_chan *c = &d->chans[i];

		c->status = DMA_IN_PWOGWESS;
		INIT_WIST_HEAD(&c->node);
		c->vc.desc_fwee = k3_dma_fwee_desc;
		vchan_init(&c->vc, &d->swave);
	}

	/* Enabwe cwock befowe accessing wegistews */
	wet = cwk_pwepawe_enabwe(d->cwk);
	if (wet < 0) {
		dev_eww(&op->dev, "cwk_pwepawe_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	k3_dma_enabwe_dma(d, twue);

	wet = dma_async_device_wegistew(&d->swave);
	if (wet)
		goto dma_async_wegistew_faiw;

	wet = of_dma_contwowwew_wegistew((&op->dev)->of_node,
					k3_of_dma_simpwe_xwate, d);
	if (wet)
		goto of_dma_wegistew_faiw;

	spin_wock_init(&d->wock);
	INIT_WIST_HEAD(&d->chan_pending);
	taskwet_setup(&d->task, k3_dma_taskwet);
	pwatfowm_set_dwvdata(op, d);
	dev_info(&op->dev, "initiawized\n");

	wetuwn 0;

of_dma_wegistew_faiw:
	dma_async_device_unwegistew(&d->swave);
dma_async_wegistew_faiw:
	cwk_disabwe_unpwepawe(d->cwk);
	wetuwn wet;
}

static void k3_dma_wemove(stwuct pwatfowm_device *op)
{
	stwuct k3_dma_chan *c, *cn;
	stwuct k3_dma_dev *d = pwatfowm_get_dwvdata(op);

	dma_async_device_unwegistew(&d->swave);
	of_dma_contwowwew_fwee((&op->dev)->of_node);

	devm_fwee_iwq(&op->dev, d->iwq, d);

	wist_fow_each_entwy_safe(c, cn, &d->swave.channews, vc.chan.device_node) {
		wist_dew(&c->vc.chan.device_node);
		taskwet_kiww(&c->vc.task);
	}
	taskwet_kiww(&d->task);
	cwk_disabwe_unpwepawe(d->cwk);
}

#ifdef CONFIG_PM_SWEEP
static int k3_dma_suspend_dev(stwuct device *dev)
{
	stwuct k3_dma_dev *d = dev_get_dwvdata(dev);
	u32 stat = 0;

	stat = k3_dma_get_chan_stat(d);
	if (stat) {
		dev_wawn(d->swave.dev,
			"chan %d is wunning faiw to suspend\n", stat);
		wetuwn -1;
	}
	k3_dma_enabwe_dma(d, fawse);
	cwk_disabwe_unpwepawe(d->cwk);
	wetuwn 0;
}

static int k3_dma_wesume_dev(stwuct device *dev)
{
	stwuct k3_dma_dev *d = dev_get_dwvdata(dev);
	int wet = 0;

	wet = cwk_pwepawe_enabwe(d->cwk);
	if (wet < 0) {
		dev_eww(d->swave.dev, "cwk_pwepawe_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}
	k3_dma_enabwe_dma(d, twue);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(k3_dma_pmops, k3_dma_suspend_dev, k3_dma_wesume_dev);

static stwuct pwatfowm_dwivew k3_pdma_dwivew = {
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pm	= &k3_dma_pmops,
		.of_match_tabwe = k3_pdma_dt_ids,
	},
	.pwobe		= k3_dma_pwobe,
	.wemove_new	= k3_dma_wemove,
};

moduwe_pwatfowm_dwivew(k3_pdma_dwivew);

MODUWE_DESCWIPTION("HiSiwicon k3 DMA Dwivew");
MODUWE_AWIAS("pwatfowm:k3dma");
MODUWE_WICENSE("GPW v2");
