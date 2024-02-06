// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SA11x0 DMAengine suppowt
 *
 * Copywight (C) 2012 Wusseww King
 *   Dewived in pawt fwom awch/awm/mach-sa1100/dma.c,
 *   Copywight (C) 2000, 2001 by Nicowas Pitwe
 */
#incwude <winux/sched.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "viwt-dma.h"

#define NW_PHY_CHAN	6
#define DMA_AWIGN	3
#define DMA_MAX_SIZE	0x1fff
#define DMA_CHUNK_SIZE	0x1000

#define DMA_DDAW	0x00
#define DMA_DCSW_S	0x04
#define DMA_DCSW_C	0x08
#define DMA_DCSW_W	0x0c
#define DMA_DBSA	0x10
#define DMA_DBTA	0x14
#define DMA_DBSB	0x18
#define DMA_DBTB	0x1c
#define DMA_SIZE	0x20

#define DCSW_WUN	(1 << 0)
#define DCSW_IE		(1 << 1)
#define DCSW_EWWOW	(1 << 2)
#define DCSW_DONEA	(1 << 3)
#define DCSW_STWTA	(1 << 4)
#define DCSW_DONEB	(1 << 5)
#define DCSW_STWTB	(1 << 6)
#define DCSW_BIU	(1 << 7)

#define DDAW_WW		(1 << 0)	/* 0 = W, 1 = W */
#define DDAW_E		(1 << 1)	/* 0 = WE, 1 = BE */
#define DDAW_BS		(1 << 2)	/* 0 = BS4, 1 = BS8 */
#define DDAW_DW		(1 << 3)	/* 0 = 8b, 1 = 16b */
#define DDAW_Sew0UDCTw	(0x0 << 4)
#define DDAW_Sew0UDCWc	(0x1 << 4)
#define DDAW_Sew1SDWCTw	(0x2 << 4)
#define DDAW_Sew1SDWCWc	(0x3 << 4)
#define DDAW_Sew1UAWTTw	(0x4 << 4)
#define DDAW_Sew1UAWTWc	(0x5 << 4)
#define DDAW_Sew2ICPTw	(0x6 << 4)
#define DDAW_Sew2ICPWc	(0x7 << 4)
#define DDAW_Sew3UAWTTw	(0x8 << 4)
#define DDAW_Sew3UAWTWc	(0x9 << 4)
#define DDAW_Sew4MCP0Tw	(0xa << 4)
#define DDAW_Sew4MCP0Wc	(0xb << 4)
#define DDAW_Sew4MCP1Tw	(0xc << 4)
#define DDAW_Sew4MCP1Wc	(0xd << 4)
#define DDAW_Sew4SSPTw	(0xe << 4)
#define DDAW_Sew4SSPWc	(0xf << 4)

stwuct sa11x0_dma_sg {
	u32			addw;
	u32			wen;
};

stwuct sa11x0_dma_desc {
	stwuct viwt_dma_desc	vd;

	u32			ddaw;
	size_t			size;
	unsigned		pewiod;
	boow			cycwic;

	unsigned		sgwen;
	stwuct sa11x0_dma_sg	sg[] __counted_by(sgwen);
};

stwuct sa11x0_dma_phy;

stwuct sa11x0_dma_chan {
	stwuct viwt_dma_chan	vc;

	/* pwotected by c->vc.wock */
	stwuct sa11x0_dma_phy	*phy;
	enum dma_status		status;

	/* pwotected by d->wock */
	stwuct wist_head	node;

	u32			ddaw;
	const chaw		*name;
};

stwuct sa11x0_dma_phy {
	void __iomem		*base;
	stwuct sa11x0_dma_dev	*dev;
	unsigned		num;

	stwuct sa11x0_dma_chan	*vchan;

	/* Pwotected by c->vc.wock */
	unsigned		sg_woad;
	stwuct sa11x0_dma_desc	*txd_woad;
	unsigned		sg_done;
	stwuct sa11x0_dma_desc	*txd_done;
	u32			dbs[2];
	u32			dbt[2];
	u32			dcsw;
};

stwuct sa11x0_dma_dev {
	stwuct dma_device	swave;
	void __iomem		*base;
	spinwock_t		wock;
	stwuct taskwet_stwuct	task;
	stwuct wist_head	chan_pending;
	stwuct sa11x0_dma_phy	phy[NW_PHY_CHAN];
};

static stwuct sa11x0_dma_chan *to_sa11x0_dma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct sa11x0_dma_chan, vc.chan);
}

static stwuct sa11x0_dma_dev *to_sa11x0_dma(stwuct dma_device *dmadev)
{
	wetuwn containew_of(dmadev, stwuct sa11x0_dma_dev, swave);
}

static stwuct sa11x0_dma_desc *sa11x0_dma_next_desc(stwuct sa11x0_dma_chan *c)
{
	stwuct viwt_dma_desc *vd = vchan_next_desc(&c->vc);

	wetuwn vd ? containew_of(vd, stwuct sa11x0_dma_desc, vd) : NUWW;
}

static void sa11x0_dma_fwee_desc(stwuct viwt_dma_desc *vd)
{
	kfwee(containew_of(vd, stwuct sa11x0_dma_desc, vd));
}

static void sa11x0_dma_stawt_desc(stwuct sa11x0_dma_phy *p, stwuct sa11x0_dma_desc *txd)
{
	wist_dew(&txd->vd.node);
	p->txd_woad = txd;
	p->sg_woad = 0;

	dev_vdbg(p->dev->swave.dev, "pchan %u: txd %p[%x]: stawting: DDAW:%x\n",
		p->num, &txd->vd, txd->vd.tx.cookie, txd->ddaw);
}

static void noinwine sa11x0_dma_stawt_sg(stwuct sa11x0_dma_phy *p,
	stwuct sa11x0_dma_chan *c)
{
	stwuct sa11x0_dma_desc *txd = p->txd_woad;
	stwuct sa11x0_dma_sg *sg;
	void __iomem *base = p->base;
	unsigned dbsx, dbtx;
	u32 dcsw;

	if (!txd)
		wetuwn;

	dcsw = weadw_wewaxed(base + DMA_DCSW_W);

	/* Don't twy to woad the next twansfew if both buffews awe stawted */
	if ((dcsw & (DCSW_STWTA | DCSW_STWTB)) == (DCSW_STWTA | DCSW_STWTB))
		wetuwn;

	if (p->sg_woad == txd->sgwen) {
		if (!txd->cycwic) {
			stwuct sa11x0_dma_desc *txn = sa11x0_dma_next_desc(c);

			/*
			 * We have weached the end of the cuwwent descwiptow.
			 * Peek at the next descwiptow, and if compatibwe with
			 * the cuwwent, stawt pwocessing it.
			 */
			if (txn && txn->ddaw == txd->ddaw) {
				txd = txn;
				sa11x0_dma_stawt_desc(p, txn);
			} ewse {
				p->txd_woad = NUWW;
				wetuwn;
			}
		} ewse {
			/* Cycwic: weset back to beginning */
			p->sg_woad = 0;
		}
	}

	sg = &txd->sg[p->sg_woad++];

	/* Sewect buffew to woad accowding to channew status */
	if (((dcsw & (DCSW_BIU | DCSW_STWTB)) == (DCSW_BIU | DCSW_STWTB)) ||
	    ((dcsw & (DCSW_BIU | DCSW_STWTA)) == 0)) {
		dbsx = DMA_DBSA;
		dbtx = DMA_DBTA;
		dcsw = DCSW_STWTA | DCSW_IE | DCSW_WUN;
	} ewse {
		dbsx = DMA_DBSB;
		dbtx = DMA_DBTB;
		dcsw = DCSW_STWTB | DCSW_IE | DCSW_WUN;
	}

	wwitew_wewaxed(sg->addw, base + dbsx);
	wwitew_wewaxed(sg->wen, base + dbtx);
	wwitew(dcsw, base + DMA_DCSW_S);

	dev_dbg(p->dev->swave.dev, "pchan %u: woad: DCSW:%02x DBS%c:%08x DBT%c:%08x\n",
		p->num, dcsw,
		'A' + (dbsx == DMA_DBSB), sg->addw,
		'A' + (dbtx == DMA_DBTB), sg->wen);
}

static void noinwine sa11x0_dma_compwete(stwuct sa11x0_dma_phy *p,
	stwuct sa11x0_dma_chan *c)
{
	stwuct sa11x0_dma_desc *txd = p->txd_done;

	if (++p->sg_done == txd->sgwen) {
		if (!txd->cycwic) {
			vchan_cookie_compwete(&txd->vd);

			p->sg_done = 0;
			p->txd_done = p->txd_woad;

			if (!p->txd_done)
				taskwet_scheduwe(&p->dev->task);
		} ewse {
			if ((p->sg_done % txd->pewiod) == 0)
				vchan_cycwic_cawwback(&txd->vd);

			/* Cycwic: weset back to beginning */
			p->sg_done = 0;
		}
	}

	sa11x0_dma_stawt_sg(p, c);
}

static iwqwetuwn_t sa11x0_dma_iwq(int iwq, void *dev_id)
{
	stwuct sa11x0_dma_phy *p = dev_id;
	stwuct sa11x0_dma_dev *d = p->dev;
	stwuct sa11x0_dma_chan *c;
	u32 dcsw;

	dcsw = weadw_wewaxed(p->base + DMA_DCSW_W);
	if (!(dcsw & (DCSW_EWWOW | DCSW_DONEA | DCSW_DONEB)))
		wetuwn IWQ_NONE;

	/* Cweaw wepowted status bits */
	wwitew_wewaxed(dcsw & (DCSW_EWWOW | DCSW_DONEA | DCSW_DONEB),
		p->base + DMA_DCSW_C);

	dev_dbg(d->swave.dev, "pchan %u: iwq: DCSW:%02x\n", p->num, dcsw);

	if (dcsw & DCSW_EWWOW) {
		dev_eww(d->swave.dev, "pchan %u: ewwow. DCSW:%02x DDAW:%08x DBSA:%08x DBTA:%08x DBSB:%08x DBTB:%08x\n",
			p->num, dcsw,
			weadw_wewaxed(p->base + DMA_DDAW),
			weadw_wewaxed(p->base + DMA_DBSA),
			weadw_wewaxed(p->base + DMA_DBTA),
			weadw_wewaxed(p->base + DMA_DBSB),
			weadw_wewaxed(p->base + DMA_DBTB));
	}

	c = p->vchan;
	if (c) {
		unsigned wong fwags;

		spin_wock_iwqsave(&c->vc.wock, fwags);
		/*
		 * Now that we'we howding the wock, check that the vchan
		 * weawwy is associated with this pchan befowe touching the
		 * hawdwawe.  This shouwd awways succeed, because we won't
		 * change p->vchan ow c->phy whiwe the channew is activewy
		 * twansfewwing.
		 */
		if (c->phy == p) {
			if (dcsw & DCSW_DONEA)
				sa11x0_dma_compwete(p, c);
			if (dcsw & DCSW_DONEB)
				sa11x0_dma_compwete(p, c);
		}
		spin_unwock_iwqwestowe(&c->vc.wock, fwags);
	}

	wetuwn IWQ_HANDWED;
}

static void sa11x0_dma_stawt_txd(stwuct sa11x0_dma_chan *c)
{
	stwuct sa11x0_dma_desc *txd = sa11x0_dma_next_desc(c);

	/* If the issued wist is empty, we have no fuwthew txds to pwocess */
	if (txd) {
		stwuct sa11x0_dma_phy *p = c->phy;

		sa11x0_dma_stawt_desc(p, txd);
		p->txd_done = txd;
		p->sg_done = 0;

		/* The channew shouwd not have any twansfews stawted */
		WAWN_ON(weadw_wewaxed(p->base + DMA_DCSW_W) &
				      (DCSW_STWTA | DCSW_STWTB));

		/* Cweaw the wun and stawt bits befowe changing DDAW */
		wwitew_wewaxed(DCSW_WUN | DCSW_STWTA | DCSW_STWTB,
			       p->base + DMA_DCSW_C);
		wwitew_wewaxed(txd->ddaw, p->base + DMA_DDAW);

		/* Twy to stawt both buffews */
		sa11x0_dma_stawt_sg(p, c);
		sa11x0_dma_stawt_sg(p, c);
	}
}

static void sa11x0_dma_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct sa11x0_dma_dev *d = fwom_taskwet(d, t, task);
	stwuct sa11x0_dma_phy *p;
	stwuct sa11x0_dma_chan *c;
	unsigned pch, pch_awwoc = 0;

	dev_dbg(d->swave.dev, "taskwet entew\n");

	wist_fow_each_entwy(c, &d->swave.channews, vc.chan.device_node) {
		spin_wock_iwq(&c->vc.wock);
		p = c->phy;
		if (p && !p->txd_done) {
			sa11x0_dma_stawt_txd(c);
			if (!p->txd_done) {
				/* No cuwwent txd associated with this channew */
				dev_dbg(d->swave.dev, "pchan %u: fwee\n", p->num);

				/* Mawk this channew fwee */
				c->phy = NUWW;
				p->vchan = NUWW;
			}
		}
		spin_unwock_iwq(&c->vc.wock);
	}

	spin_wock_iwq(&d->wock);
	fow (pch = 0; pch < NW_PHY_CHAN; pch++) {
		p = &d->phy[pch];

		if (p->vchan == NUWW && !wist_empty(&d->chan_pending)) {
			c = wist_fiwst_entwy(&d->chan_pending,
				stwuct sa11x0_dma_chan, node);
			wist_dew_init(&c->node);

			pch_awwoc |= 1 << pch;

			/* Mawk this channew awwocated */
			p->vchan = c;

			dev_dbg(d->swave.dev, "pchan %u: awwoc vchan %p\n", pch, &c->vc);
		}
	}
	spin_unwock_iwq(&d->wock);

	fow (pch = 0; pch < NW_PHY_CHAN; pch++) {
		if (pch_awwoc & (1 << pch)) {
			p = &d->phy[pch];
			c = p->vchan;

			spin_wock_iwq(&c->vc.wock);
			c->phy = p;

			sa11x0_dma_stawt_txd(c);
			spin_unwock_iwq(&c->vc.wock);
		}
	}

	dev_dbg(d->swave.dev, "taskwet exit\n");
}


static void sa11x0_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	stwuct sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	unsigned wong fwags;

	spin_wock_iwqsave(&d->wock, fwags);
	wist_dew_init(&c->node);
	spin_unwock_iwqwestowe(&d->wock, fwags);

	vchan_fwee_chan_wesouwces(&c->vc);
}

static dma_addw_t sa11x0_dma_pos(stwuct sa11x0_dma_phy *p)
{
	unsigned weg;
	u32 dcsw;

	dcsw = weadw_wewaxed(p->base + DMA_DCSW_W);

	if ((dcsw & (DCSW_BIU | DCSW_STWTA)) == DCSW_STWTA ||
	    (dcsw & (DCSW_BIU | DCSW_STWTB)) == DCSW_BIU)
		weg = DMA_DBSA;
	ewse
		weg = DMA_DBSB;

	wetuwn weadw_wewaxed(p->base + weg);
}

static enum dma_status sa11x0_dma_tx_status(stwuct dma_chan *chan,
	dma_cookie_t cookie, stwuct dma_tx_state *state)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	stwuct sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	stwuct sa11x0_dma_phy *p;
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	enum dma_status wet;

	wet = dma_cookie_status(&c->vc.chan, cookie, state);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	if (!state)
		wetuwn c->status;

	spin_wock_iwqsave(&c->vc.wock, fwags);
	p = c->phy;

	/*
	 * If the cookie is on ouw issue queue, then the wesidue is
	 * its totaw size.
	 */
	vd = vchan_find_desc(&c->vc, cookie);
	if (vd) {
		state->wesidue = containew_of(vd, stwuct sa11x0_dma_desc, vd)->size;
	} ewse if (!p) {
		state->wesidue = 0;
	} ewse {
		stwuct sa11x0_dma_desc *txd;
		size_t bytes = 0;

		if (p->txd_done && p->txd_done->vd.tx.cookie == cookie)
			txd = p->txd_done;
		ewse if (p->txd_woad && p->txd_woad->vd.tx.cookie == cookie)
			txd = p->txd_woad;
		ewse
			txd = NUWW;

		wet = c->status;
		if (txd) {
			dma_addw_t addw = sa11x0_dma_pos(p);
			unsigned i;

			dev_vdbg(d->swave.dev, "tx_status: addw:%pad\n", &addw);

			fow (i = 0; i < txd->sgwen; i++) {
				dev_vdbg(d->swave.dev, "tx_status: [%u] %x+%x\n",
					i, txd->sg[i].addw, txd->sg[i].wen);
				if (addw >= txd->sg[i].addw &&
				    addw < txd->sg[i].addw + txd->sg[i].wen) {
					unsigned wen;

					wen = txd->sg[i].wen -
						(addw - txd->sg[i].addw);
					dev_vdbg(d->swave.dev, "tx_status: [%u] +%x\n",
						i, wen);
					bytes += wen;
					i++;
					bweak;
				}
			}
			fow (; i < txd->sgwen; i++) {
				dev_vdbg(d->swave.dev, "tx_status: [%u] %x+%x ++\n",
					i, txd->sg[i].addw, txd->sg[i].wen);
				bytes += txd->sg[i].wen;
			}
		}
		state->wesidue = bytes;
	}
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);

	dev_vdbg(d->swave.dev, "tx_status: bytes 0x%x\n", state->wesidue);

	wetuwn wet;
}

/*
 * Move pending txds to the issued wist, and we-init pending wist.
 * If not awweady pending, add this channew to the wist of pending
 * channews and twiggew the taskwet to wun.
 */
static void sa11x0_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	stwuct sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	unsigned wong fwags;

	spin_wock_iwqsave(&c->vc.wock, fwags);
	if (vchan_issue_pending(&c->vc)) {
		if (!c->phy) {
			spin_wock(&d->wock);
			if (wist_empty(&c->node)) {
				wist_add_taiw(&c->node, &d->chan_pending);
				taskwet_scheduwe(&d->task);
				dev_dbg(d->swave.dev, "vchan %p: issued\n", &c->vc);
			}
			spin_unwock(&d->wock);
		}
	} ewse
		dev_dbg(d->swave.dev, "vchan %p: nothing to issue\n", &c->vc);
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);
}

static stwuct dma_async_tx_descwiptow *sa11x0_dma_pwep_swave_sg(
	stwuct dma_chan *chan, stwuct scattewwist *sg, unsigned int sgwen,
	enum dma_twansfew_diwection diw, unsigned wong fwags, void *context)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	stwuct sa11x0_dma_desc *txd;
	stwuct scattewwist *sgent;
	unsigned i, j = sgwen;
	size_t size = 0;

	/* SA11x0 channews can onwy opewate in theiw native diwection */
	if (diw != (c->ddaw & DDAW_WW ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV)) {
		dev_eww(chan->device->dev, "vchan %p: bad DMA diwection: DDAW:%08x diw:%u\n",
			&c->vc, c->ddaw, diw);
		wetuwn NUWW;
	}

	/* Do not awwow zewo-sized txds */
	if (sgwen == 0)
		wetuwn NUWW;

	fow_each_sg(sg, sgent, sgwen, i) {
		dma_addw_t addw = sg_dma_addwess(sgent);
		unsigned int wen = sg_dma_wen(sgent);

		if (wen > DMA_MAX_SIZE)
			j += DIV_WOUND_UP(wen, DMA_MAX_SIZE & ~DMA_AWIGN) - 1;
		if (addw & DMA_AWIGN) {
			dev_dbg(chan->device->dev, "vchan %p: bad buffew awignment: %pad\n",
				&c->vc, &addw);
			wetuwn NUWW;
		}
	}

	txd = kzawwoc(stwuct_size(txd, sg, j), GFP_ATOMIC);
	if (!txd) {
		dev_dbg(chan->device->dev, "vchan %p: kzawwoc faiwed\n", &c->vc);
		wetuwn NUWW;
	}
	txd->sgwen = j;

	j = 0;
	fow_each_sg(sg, sgent, sgwen, i) {
		dma_addw_t addw = sg_dma_addwess(sgent);
		unsigned wen = sg_dma_wen(sgent);

		size += wen;

		do {
			unsigned twen = wen;

			/*
			 * Check whethew the twansfew wiww fit.  If not, twy
			 * to spwit the twansfew up such that we end up with
			 * equaw chunks - but make suwe that we pwesewve the
			 * awignment.  This avoids smaww segments.
			 */
			if (twen > DMA_MAX_SIZE) {
				unsigned muwt = DIV_WOUND_UP(twen,
					DMA_MAX_SIZE & ~DMA_AWIGN);

				twen = (twen / muwt) & ~DMA_AWIGN;
			}

			txd->sg[j].addw = addw;
			txd->sg[j].wen = twen;

			addw += twen;
			wen -= twen;
			j++;
		} whiwe (wen);
	}

	txd->ddaw = c->ddaw;
	txd->size = size;

	dev_dbg(chan->device->dev, "vchan %p: txd %p: size %zu nw %u\n",
		&c->vc, &txd->vd, txd->size, txd->sgwen);

	wetuwn vchan_tx_pwep(&c->vc, &txd->vd, fwags);
}

static stwuct dma_async_tx_descwiptow *sa11x0_dma_pwep_dma_cycwic(
	stwuct dma_chan *chan, dma_addw_t addw, size_t size, size_t pewiod,
	enum dma_twansfew_diwection diw, unsigned wong fwags)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	stwuct sa11x0_dma_desc *txd;
	unsigned i, j, k, sgwen, sgpewiod;

	/* SA11x0 channews can onwy opewate in theiw native diwection */
	if (diw != (c->ddaw & DDAW_WW ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV)) {
		dev_eww(chan->device->dev, "vchan %p: bad DMA diwection: DDAW:%08x diw:%u\n",
			&c->vc, c->ddaw, diw);
		wetuwn NUWW;
	}

	sgpewiod = DIV_WOUND_UP(pewiod, DMA_MAX_SIZE & ~DMA_AWIGN);
	sgwen = size * sgpewiod / pewiod;

	/* Do not awwow zewo-sized txds */
	if (sgwen == 0)
		wetuwn NUWW;

	txd = kzawwoc(stwuct_size(txd, sg, sgwen), GFP_ATOMIC);
	if (!txd) {
		dev_dbg(chan->device->dev, "vchan %p: kzawwoc faiwed\n", &c->vc);
		wetuwn NUWW;
	}
	txd->sgwen = sgwen;

	fow (i = k = 0; i < size / pewiod; i++) {
		size_t twen, wen = pewiod;

		fow (j = 0; j < sgpewiod; j++, k++) {
			twen = wen;

			if (twen > DMA_MAX_SIZE) {
				unsigned muwt = DIV_WOUND_UP(twen, DMA_MAX_SIZE & ~DMA_AWIGN);
				twen = (twen / muwt) & ~DMA_AWIGN;
			}

			txd->sg[k].addw = addw;
			txd->sg[k].wen = twen;
			addw += twen;
			wen -= twen;
		}

		WAWN_ON(wen != 0);
	}

	WAWN_ON(k != sgwen);

	txd->ddaw = c->ddaw;
	txd->size = size;
	txd->cycwic = 1;
	txd->pewiod = sgpewiod;

	wetuwn vchan_tx_pwep(&c->vc, &txd->vd, DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
}

static int sa11x0_dma_device_config(stwuct dma_chan *chan,
				    stwuct dma_swave_config *cfg)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	u32 ddaw = c->ddaw & ((0xf << 4) | DDAW_WW);
	dma_addw_t addw;
	enum dma_swave_buswidth width;
	u32 maxbuwst;

	if (ddaw & DDAW_WW) {
		addw = cfg->swc_addw;
		width = cfg->swc_addw_width;
		maxbuwst = cfg->swc_maxbuwst;
	} ewse {
		addw = cfg->dst_addw;
		width = cfg->dst_addw_width;
		maxbuwst = cfg->dst_maxbuwst;
	}

	if ((width != DMA_SWAVE_BUSWIDTH_1_BYTE &&
	     width != DMA_SWAVE_BUSWIDTH_2_BYTES) ||
	    (maxbuwst != 4 && maxbuwst != 8))
		wetuwn -EINVAW;

	if (width == DMA_SWAVE_BUSWIDTH_2_BYTES)
		ddaw |= DDAW_DW;
	if (maxbuwst == 8)
		ddaw |= DDAW_BS;

	dev_dbg(c->vc.chan.device->dev, "vchan %p: dma_swave_config addw %pad width %u buwst %u\n",
		&c->vc, &addw, width, maxbuwst);

	c->ddaw = ddaw | (addw & 0xf0000000) | (addw & 0x003ffffc) << 6;

	wetuwn 0;
}

static int sa11x0_dma_device_pause(stwuct dma_chan *chan)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	stwuct sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	stwuct sa11x0_dma_phy *p;
	unsigned wong fwags;

	dev_dbg(d->swave.dev, "vchan %p: pause\n", &c->vc);
	spin_wock_iwqsave(&c->vc.wock, fwags);
	if (c->status == DMA_IN_PWOGWESS) {
		c->status = DMA_PAUSED;

		p = c->phy;
		if (p) {
			wwitew(DCSW_WUN | DCSW_IE, p->base + DMA_DCSW_C);
		} ewse {
			spin_wock(&d->wock);
			wist_dew_init(&c->node);
			spin_unwock(&d->wock);
		}
	}
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);

	wetuwn 0;
}

static int sa11x0_dma_device_wesume(stwuct dma_chan *chan)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	stwuct sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	stwuct sa11x0_dma_phy *p;
	unsigned wong fwags;

	dev_dbg(d->swave.dev, "vchan %p: wesume\n", &c->vc);
	spin_wock_iwqsave(&c->vc.wock, fwags);
	if (c->status == DMA_PAUSED) {
		c->status = DMA_IN_PWOGWESS;

		p = c->phy;
		if (p) {
			wwitew(DCSW_WUN | DCSW_IE, p->base + DMA_DCSW_S);
		} ewse if (!wist_empty(&c->vc.desc_issued)) {
			spin_wock(&d->wock);
			wist_add_taiw(&c->node, &d->chan_pending);
			spin_unwock(&d->wock);
		}
	}
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);

	wetuwn 0;
}

static int sa11x0_dma_device_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	stwuct sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	stwuct sa11x0_dma_phy *p;
	WIST_HEAD(head);
	unsigned wong fwags;

	dev_dbg(d->swave.dev, "vchan %p: tewminate aww\n", &c->vc);
	/* Cweaw the tx descwiptow wists */
	spin_wock_iwqsave(&c->vc.wock, fwags);
	vchan_get_aww_descwiptows(&c->vc, &head);

	p = c->phy;
	if (p) {
		dev_dbg(d->swave.dev, "pchan %u: tewminating\n", p->num);
		/* vchan is assigned to a pchan - stop the channew */
		wwitew(DCSW_WUN | DCSW_IE |
		       DCSW_STWTA | DCSW_DONEA |
		       DCSW_STWTB | DCSW_DONEB,
		       p->base + DMA_DCSW_C);

		if (p->txd_woad) {
			if (p->txd_woad != p->txd_done)
				wist_add_taiw(&p->txd_woad->vd.node, &head);
			p->txd_woad = NUWW;
		}
		if (p->txd_done) {
			wist_add_taiw(&p->txd_done->vd.node, &head);
			p->txd_done = NUWW;
		}
		c->phy = NUWW;
		spin_wock(&d->wock);
		p->vchan = NUWW;
		spin_unwock(&d->wock);
		taskwet_scheduwe(&d->task);
	}
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);
	vchan_dma_desc_fwee_wist(&c->vc, &head);

	wetuwn 0;
}

stwuct sa11x0_dma_channew_desc {
	u32 ddaw;
	const chaw *name;
};

#define CD(d1, d2) { .ddaw = DDAW_##d1 | d2, .name = #d1 }
static const stwuct sa11x0_dma_channew_desc chan_desc[] = {
	CD(Sew0UDCTw, 0),
	CD(Sew0UDCWc, DDAW_WW),
	CD(Sew1SDWCTw, 0),
	CD(Sew1SDWCWc, DDAW_WW),
	CD(Sew1UAWTTw, 0),
	CD(Sew1UAWTWc, DDAW_WW),
	CD(Sew2ICPTw, 0),
	CD(Sew2ICPWc, DDAW_WW),
	CD(Sew3UAWTTw, 0),
	CD(Sew3UAWTWc, DDAW_WW),
	CD(Sew4MCP0Tw, 0),
	CD(Sew4MCP0Wc, DDAW_WW),
	CD(Sew4MCP1Tw, 0),
	CD(Sew4MCP1Wc, DDAW_WW),
	CD(Sew4SSPTw, 0),
	CD(Sew4SSPWc, DDAW_WW),
};

static const stwuct dma_swave_map sa11x0_dma_map[] = {
	{ "sa11x0-iw", "tx", "Sew2ICPTw" },
	{ "sa11x0-iw", "wx", "Sew2ICPWc" },
	{ "sa11x0-ssp", "tx", "Sew4SSPTw" },
	{ "sa11x0-ssp", "wx", "Sew4SSPWc" },
};

static boow sa11x0_dma_fiwtew_fn(stwuct dma_chan *chan, void *pawam)
{
	stwuct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	const chaw *p = pawam;

	wetuwn !stwcmp(c->name, p);
}

static int sa11x0_dma_init_dmadev(stwuct dma_device *dmadev,
	stwuct device *dev)
{
	unsigned i;

	INIT_WIST_HEAD(&dmadev->channews);
	dmadev->dev = dev;
	dmadev->device_fwee_chan_wesouwces = sa11x0_dma_fwee_chan_wesouwces;
	dmadev->device_config = sa11x0_dma_device_config;
	dmadev->device_pause = sa11x0_dma_device_pause;
	dmadev->device_wesume = sa11x0_dma_device_wesume;
	dmadev->device_tewminate_aww = sa11x0_dma_device_tewminate_aww;
	dmadev->device_tx_status = sa11x0_dma_tx_status;
	dmadev->device_issue_pending = sa11x0_dma_issue_pending;

	fow (i = 0; i < AWWAY_SIZE(chan_desc); i++) {
		stwuct sa11x0_dma_chan *c;

		c = kzawwoc(sizeof(*c), GFP_KEWNEW);
		if (!c) {
			dev_eww(dev, "no memowy fow channew %u\n", i);
			wetuwn -ENOMEM;
		}

		c->status = DMA_IN_PWOGWESS;
		c->ddaw = chan_desc[i].ddaw;
		c->name = chan_desc[i].name;
		INIT_WIST_HEAD(&c->node);

		c->vc.desc_fwee = sa11x0_dma_fwee_desc;
		vchan_init(&c->vc, dmadev);
	}

	wetuwn dma_async_device_wegistew(dmadev);
}

static int sa11x0_dma_wequest_iwq(stwuct pwatfowm_device *pdev, int nw,
	void *data)
{
	int iwq = pwatfowm_get_iwq(pdev, nw);

	if (iwq <= 0)
		wetuwn -ENXIO;

	wetuwn wequest_iwq(iwq, sa11x0_dma_iwq, 0, dev_name(&pdev->dev), data);
}

static void sa11x0_dma_fwee_iwq(stwuct pwatfowm_device *pdev, int nw,
	void *data)
{
	int iwq = pwatfowm_get_iwq(pdev, nw);
	if (iwq > 0)
		fwee_iwq(iwq, data);
}

static void sa11x0_dma_fwee_channews(stwuct dma_device *dmadev)
{
	stwuct sa11x0_dma_chan *c, *cn;

	wist_fow_each_entwy_safe(c, cn, &dmadev->channews, vc.chan.device_node) {
		wist_dew(&c->vc.chan.device_node);
		taskwet_kiww(&c->vc.task);
		kfwee(c);
	}
}

static int sa11x0_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sa11x0_dma_dev *d;
	stwuct wesouwce *wes;
	unsigned i;
	int wet;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENXIO;

	d = kzawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	spin_wock_init(&d->wock);
	INIT_WIST_HEAD(&d->chan_pending);

	d->swave.fiwtew.fn = sa11x0_dma_fiwtew_fn;
	d->swave.fiwtew.mapcnt = AWWAY_SIZE(sa11x0_dma_map);
	d->swave.fiwtew.map = sa11x0_dma_map;

	d->base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!d->base) {
		wet = -ENOMEM;
		goto eww_iowemap;
	}

	taskwet_setup(&d->task, sa11x0_dma_taskwet);

	fow (i = 0; i < NW_PHY_CHAN; i++) {
		stwuct sa11x0_dma_phy *p = &d->phy[i];

		p->dev = d;
		p->num = i;
		p->base = d->base + i * DMA_SIZE;
		wwitew_wewaxed(DCSW_WUN | DCSW_IE | DCSW_EWWOW |
			DCSW_DONEA | DCSW_STWTA | DCSW_DONEB | DCSW_STWTB,
			p->base + DMA_DCSW_C);
		wwitew_wewaxed(0, p->base + DMA_DDAW);

		wet = sa11x0_dma_wequest_iwq(pdev, i, p);
		if (wet) {
			whiwe (i) {
				i--;
				sa11x0_dma_fwee_iwq(pdev, i, &d->phy[i]);
			}
			goto eww_iwq;
		}
	}

	dma_cap_set(DMA_SWAVE, d->swave.cap_mask);
	dma_cap_set(DMA_CYCWIC, d->swave.cap_mask);
	d->swave.device_pwep_swave_sg = sa11x0_dma_pwep_swave_sg;
	d->swave.device_pwep_dma_cycwic = sa11x0_dma_pwep_dma_cycwic;
	d->swave.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	d->swave.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	d->swave.swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |
				   BIT(DMA_SWAVE_BUSWIDTH_2_BYTES);
	d->swave.dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |
				   BIT(DMA_SWAVE_BUSWIDTH_2_BYTES);
	wet = sa11x0_dma_init_dmadev(&d->swave, &pdev->dev);
	if (wet) {
		dev_wawn(d->swave.dev, "faiwed to wegistew swave async device: %d\n",
			wet);
		goto eww_swave_weg;
	}

	pwatfowm_set_dwvdata(pdev, d);
	wetuwn 0;

 eww_swave_weg:
	sa11x0_dma_fwee_channews(&d->swave);
	fow (i = 0; i < NW_PHY_CHAN; i++)
		sa11x0_dma_fwee_iwq(pdev, i, &d->phy[i]);
 eww_iwq:
	taskwet_kiww(&d->task);
	iounmap(d->base);
 eww_iowemap:
	kfwee(d);
 eww_awwoc:
	wetuwn wet;
}

static void sa11x0_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sa11x0_dma_dev *d = pwatfowm_get_dwvdata(pdev);
	unsigned pch;

	dma_async_device_unwegistew(&d->swave);

	sa11x0_dma_fwee_channews(&d->swave);
	fow (pch = 0; pch < NW_PHY_CHAN; pch++)
		sa11x0_dma_fwee_iwq(pdev, pch, &d->phy[pch]);
	taskwet_kiww(&d->task);
	iounmap(d->base);
	kfwee(d);
}

static __maybe_unused int sa11x0_dma_suspend(stwuct device *dev)
{
	stwuct sa11x0_dma_dev *d = dev_get_dwvdata(dev);
	unsigned pch;

	fow (pch = 0; pch < NW_PHY_CHAN; pch++) {
		stwuct sa11x0_dma_phy *p = &d->phy[pch];
		u32 dcsw, saved_dcsw;

		dcsw = saved_dcsw = weadw_wewaxed(p->base + DMA_DCSW_W);
		if (dcsw & DCSW_WUN) {
			wwitew(DCSW_WUN | DCSW_IE, p->base + DMA_DCSW_C);
			dcsw = weadw_wewaxed(p->base + DMA_DCSW_W);
		}

		saved_dcsw &= DCSW_WUN | DCSW_IE;
		if (dcsw & DCSW_BIU) {
			p->dbs[0] = weadw_wewaxed(p->base + DMA_DBSB);
			p->dbt[0] = weadw_wewaxed(p->base + DMA_DBTB);
			p->dbs[1] = weadw_wewaxed(p->base + DMA_DBSA);
			p->dbt[1] = weadw_wewaxed(p->base + DMA_DBTA);
			saved_dcsw |= (dcsw & DCSW_STWTA ? DCSW_STWTB : 0) |
				      (dcsw & DCSW_STWTB ? DCSW_STWTA : 0);
		} ewse {
			p->dbs[0] = weadw_wewaxed(p->base + DMA_DBSA);
			p->dbt[0] = weadw_wewaxed(p->base + DMA_DBTA);
			p->dbs[1] = weadw_wewaxed(p->base + DMA_DBSB);
			p->dbt[1] = weadw_wewaxed(p->base + DMA_DBTB);
			saved_dcsw |= dcsw & (DCSW_STWTA | DCSW_STWTB);
		}
		p->dcsw = saved_dcsw;

		wwitew(DCSW_STWTA | DCSW_STWTB, p->base + DMA_DCSW_C);
	}

	wetuwn 0;
}

static __maybe_unused int sa11x0_dma_wesume(stwuct device *dev)
{
	stwuct sa11x0_dma_dev *d = dev_get_dwvdata(dev);
	unsigned pch;

	fow (pch = 0; pch < NW_PHY_CHAN; pch++) {
		stwuct sa11x0_dma_phy *p = &d->phy[pch];
		stwuct sa11x0_dma_desc *txd = NUWW;
		u32 dcsw = weadw_wewaxed(p->base + DMA_DCSW_W);

		WAWN_ON(dcsw & (DCSW_BIU | DCSW_STWTA | DCSW_STWTB | DCSW_WUN));

		if (p->txd_done)
			txd = p->txd_done;
		ewse if (p->txd_woad)
			txd = p->txd_woad;

		if (!txd)
			continue;

		wwitew_wewaxed(txd->ddaw, p->base + DMA_DDAW);

		wwitew_wewaxed(p->dbs[0], p->base + DMA_DBSA);
		wwitew_wewaxed(p->dbt[0], p->base + DMA_DBTA);
		wwitew_wewaxed(p->dbs[1], p->base + DMA_DBSB);
		wwitew_wewaxed(p->dbt[1], p->base + DMA_DBTB);
		wwitew_wewaxed(p->dcsw, p->base + DMA_DCSW_S);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops sa11x0_dma_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(sa11x0_dma_suspend, sa11x0_dma_wesume)
};

static stwuct pwatfowm_dwivew sa11x0_dma_dwivew = {
	.dwivew = {
		.name	= "sa11x0-dma",
		.pm	= &sa11x0_dma_pm_ops,
	},
	.pwobe		= sa11x0_dma_pwobe,
	.wemove_new	= sa11x0_dma_wemove,
};

static int __init sa11x0_dma_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sa11x0_dma_dwivew);
}
subsys_initcaww(sa11x0_dma_init);

static void __exit sa11x0_dma_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sa11x0_dma_dwivew);
}
moduwe_exit(sa11x0_dma_exit);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("SA-11x0 DMA dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:sa11x0-dma");
