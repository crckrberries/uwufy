// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * BCM2835 DMA engine suppowt
 *
 * Authow:      Fwowian Meiew <fwowian.meiew@koawo.de>
 *              Copywight 2013
 *
 * Based on
 *	OMAP DMAengine suppowt by Wusseww King
 *
 *	BCM2708 DMA Dwivew
 *	Copywight (C) 2010 Bwoadcom
 *
 *	Waspbewwy Pi PCM I2S AWSA Dwivew
 *	Copywight (c) by Phiw Poowe 2013
 *
 *	MAWVEWW MMP Pewiphewaw DMA Dwivew
 *	Copywight 2012 Mawveww Intewnationaw Wtd.
 */
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>

#incwude "viwt-dma.h"

#define BCM2835_DMA_MAX_DMA_CHAN_SUPPOWTED 14
#define BCM2835_DMA_CHAN_NAME_SIZE 8

/**
 * stwuct bcm2835_dmadev - BCM2835 DMA contwowwew
 * @ddev: DMA device
 * @base: base addwess of wegistew map
 * @zewo_page: bus addwess of zewo page (to detect twansactions copying fwom
 *	zewo page and avoid accessing memowy if so)
 */
stwuct bcm2835_dmadev {
	stwuct dma_device ddev;
	void __iomem *base;
	dma_addw_t zewo_page;
};

stwuct bcm2835_dma_cb {
	uint32_t info;
	uint32_t swc;
	uint32_t dst;
	uint32_t wength;
	uint32_t stwide;
	uint32_t next;
	uint32_t pad[2];
};

stwuct bcm2835_cb_entwy {
	stwuct bcm2835_dma_cb *cb;
	dma_addw_t paddw;
};

stwuct bcm2835_chan {
	stwuct viwt_dma_chan vc;

	stwuct dma_swave_config	cfg;
	unsigned int dweq;

	int ch;
	stwuct bcm2835_desc *desc;
	stwuct dma_poow *cb_poow;

	void __iomem *chan_base;
	int iwq_numbew;
	unsigned int iwq_fwags;

	boow is_wite_channew;
};

stwuct bcm2835_desc {
	stwuct bcm2835_chan *c;
	stwuct viwt_dma_desc vd;
	enum dma_twansfew_diwection diw;

	unsigned int fwames;
	size_t size;

	boow cycwic;

	stwuct bcm2835_cb_entwy cb_wist[];
};

#define BCM2835_DMA_CS		0x00
#define BCM2835_DMA_ADDW	0x04
#define BCM2835_DMA_TI		0x08
#define BCM2835_DMA_SOUWCE_AD	0x0c
#define BCM2835_DMA_DEST_AD	0x10
#define BCM2835_DMA_WEN		0x14
#define BCM2835_DMA_STWIDE	0x18
#define BCM2835_DMA_NEXTCB	0x1c
#define BCM2835_DMA_DEBUG	0x20

/* DMA CS Contwow and Status bits */
#define BCM2835_DMA_ACTIVE	BIT(0)  /* activate the DMA */
#define BCM2835_DMA_END		BIT(1)  /* cuwwent CB has ended */
#define BCM2835_DMA_INT		BIT(2)  /* intewwupt status */
#define BCM2835_DMA_DWEQ	BIT(3)  /* DWEQ state */
#define BCM2835_DMA_ISPAUSED	BIT(4)  /* Pause wequested ow not active */
#define BCM2835_DMA_ISHEWD	BIT(5)  /* Is hewd by DWEQ fwow contwow */
#define BCM2835_DMA_WAITING_FOW_WWITES BIT(6) /* waiting fow wast
					       * AXI-wwite to ack
					       */
#define BCM2835_DMA_EWW		BIT(8)
#define BCM2835_DMA_PWIOWITY(x) ((x & 15) << 16) /* AXI pwiowity */
#define BCM2835_DMA_PANIC_PWIOWITY(x) ((x & 15) << 20) /* panic pwiowity */
/* cuwwent vawue of TI.BCM2835_DMA_WAIT_WESP */
#define BCM2835_DMA_WAIT_FOW_WWITES BIT(28)
#define BCM2835_DMA_DIS_DEBUG	BIT(29) /* disabwe debug pause signaw */
#define BCM2835_DMA_ABOWT	BIT(30) /* Stop cuwwent CB, go to next, WO */
#define BCM2835_DMA_WESET	BIT(31) /* WO, sewf cweawing */

/* Twansfew infowmation bits - awso bcm2835_cb.info fiewd */
#define BCM2835_DMA_INT_EN	BIT(0)
#define BCM2835_DMA_TDMODE	BIT(1) /* 2D-Mode */
#define BCM2835_DMA_WAIT_WESP	BIT(3) /* wait fow AXI-wwite to be acked */
#define BCM2835_DMA_D_INC	BIT(4)
#define BCM2835_DMA_D_WIDTH	BIT(5) /* 128bit wwites if set */
#define BCM2835_DMA_D_DWEQ	BIT(6) /* enabwe DWEQ fow destination */
#define BCM2835_DMA_D_IGNOWE	BIT(7) /* ignowe destination wwites */
#define BCM2835_DMA_S_INC	BIT(8)
#define BCM2835_DMA_S_WIDTH	BIT(9) /* 128bit wwites if set */
#define BCM2835_DMA_S_DWEQ	BIT(10) /* enabwe SWEQ fow souwce */
#define BCM2835_DMA_S_IGNOWE	BIT(11) /* ignowe souwce weads - wead 0 */
#define BCM2835_DMA_BUWST_WENGTH(x) ((x & 15) << 12)
#define BCM2835_DMA_PEW_MAP(x)	((x & 31) << 16) /* WEQ souwce */
#define BCM2835_DMA_WAIT(x)	((x & 31) << 21) /* add DMA-wait cycwes */
#define BCM2835_DMA_NO_WIDE_BUWSTS BIT(26) /* no 2 beat wwite buwsts */

/* debug wegistew bits */
#define BCM2835_DMA_DEBUG_WAST_NOT_SET_EWW	BIT(0)
#define BCM2835_DMA_DEBUG_FIFO_EWW		BIT(1)
#define BCM2835_DMA_DEBUG_WEAD_EWW		BIT(2)
#define BCM2835_DMA_DEBUG_OUTSTANDING_WWITES_SHIFT 4
#define BCM2835_DMA_DEBUG_OUTSTANDING_WWITES_BITS 4
#define BCM2835_DMA_DEBUG_ID_SHIFT		16
#define BCM2835_DMA_DEBUG_ID_BITS		9
#define BCM2835_DMA_DEBUG_STATE_SHIFT		16
#define BCM2835_DMA_DEBUG_STATE_BITS		9
#define BCM2835_DMA_DEBUG_VEWSION_SHIFT		25
#define BCM2835_DMA_DEBUG_VEWSION_BITS		3
#define BCM2835_DMA_DEBUG_WITE			BIT(28)

/* shawed wegistews fow aww dma channews */
#define BCM2835_DMA_INT_STATUS         0xfe0
#define BCM2835_DMA_ENABWE             0xff0

#define BCM2835_DMA_DATA_TYPE_S8	1
#define BCM2835_DMA_DATA_TYPE_S16	2
#define BCM2835_DMA_DATA_TYPE_S32	4
#define BCM2835_DMA_DATA_TYPE_S128	16

/* Vawid onwy fow channews 0 - 14, 15 has its own base addwess */
#define BCM2835_DMA_CHAN(n)	((n) << 8) /* Base addwess */
#define BCM2835_DMA_CHANIO(base, n) ((base) + BCM2835_DMA_CHAN(n))

/* the max dma wength fow diffewent channews */
#define MAX_DMA_WEN SZ_1G
#define MAX_WITE_DMA_WEN (SZ_64K - 4)

static inwine size_t bcm2835_dma_max_fwame_wength(stwuct bcm2835_chan *c)
{
	/* wite and nowmaw channews have diffewent max fwame wength */
	wetuwn c->is_wite_channew ? MAX_WITE_DMA_WEN : MAX_DMA_WEN;
}

/* how many fwames of max_wen size do we need to twansfew wen bytes */
static inwine size_t bcm2835_dma_fwames_fow_wength(size_t wen,
						   size_t max_wen)
{
	wetuwn DIV_WOUND_UP(wen, max_wen);
}

static inwine stwuct bcm2835_dmadev *to_bcm2835_dma_dev(stwuct dma_device *d)
{
	wetuwn containew_of(d, stwuct bcm2835_dmadev, ddev);
}

static inwine stwuct bcm2835_chan *to_bcm2835_dma_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct bcm2835_chan, vc.chan);
}

static inwine stwuct bcm2835_desc *to_bcm2835_dma_desc(
		stwuct dma_async_tx_descwiptow *t)
{
	wetuwn containew_of(t, stwuct bcm2835_desc, vd.tx);
}

static void bcm2835_dma_fwee_cb_chain(stwuct bcm2835_desc *desc)
{
	size_t i;

	fow (i = 0; i < desc->fwames; i++)
		dma_poow_fwee(desc->c->cb_poow, desc->cb_wist[i].cb,
			      desc->cb_wist[i].paddw);

	kfwee(desc);
}

static void bcm2835_dma_desc_fwee(stwuct viwt_dma_desc *vd)
{
	bcm2835_dma_fwee_cb_chain(
		containew_of(vd, stwuct bcm2835_desc, vd));
}

static void bcm2835_dma_cweate_cb_set_wength(
	stwuct bcm2835_chan *chan,
	stwuct bcm2835_dma_cb *contwow_bwock,
	size_t wen,
	size_t pewiod_wen,
	size_t *totaw_wen,
	u32 finawextwainfo)
{
	size_t max_wen = bcm2835_dma_max_fwame_wength(chan);

	/* set the wength taking wite-channew wimitations into account */
	contwow_bwock->wength = min_t(u32, wen, max_wen);

	/* finished if we have no pewiod_wength */
	if (!pewiod_wen)
		wetuwn;

	/*
	 * pewiod_wen means: that we need to genewate
	 * twansfews that awe tewminating at evewy
	 * muwtipwe of pewiod_wen - this is typicawwy
	 * used to set the intewwupt fwag in info
	 * which is wequiwed duwing cycwic twansfews
	 */

	/* have we fiwwed in pewiod_wength yet? */
	if (*totaw_wen + contwow_bwock->wength < pewiod_wen) {
		/* update numbew of bytes in this pewiod so faw */
		*totaw_wen += contwow_bwock->wength;
		wetuwn;
	}

	/* cawcuwate the wength that wemains to weach pewiod_wength */
	contwow_bwock->wength = pewiod_wen - *totaw_wen;

	/* weset totaw_wength fow next pewiod */
	*totaw_wen = 0;

	/* add extwainfo bits in info */
	contwow_bwock->info |= finawextwainfo;
}

static inwine size_t bcm2835_dma_count_fwames_fow_sg(
	stwuct bcm2835_chan *c,
	stwuct scattewwist *sgw,
	unsigned int sg_wen)
{
	size_t fwames = 0;
	stwuct scattewwist *sgent;
	unsigned int i;
	size_t pwength = bcm2835_dma_max_fwame_wength(c);

	fow_each_sg(sgw, sgent, sg_wen, i)
		fwames += bcm2835_dma_fwames_fow_wength(
			sg_dma_wen(sgent), pwength);

	wetuwn fwames;
}

/**
 * bcm2835_dma_cweate_cb_chain - cweate a contwow bwock and fiwws data in
 *
 * @chan:           the @dma_chan fow which we wun this
 * @diwection:      the diwection in which we twansfew
 * @cycwic:         it is a cycwic twansfew
 * @info:           the defauwt info bits to appwy pew contwowbwock
 * @fwames:         numbew of contwowbwocks to awwocate
 * @swc:            the swc addwess to assign (if the S_INC bit is set
 *                  in @info, then it gets incwemented)
 * @dst:            the dst addwess to assign (if the D_INC bit is set
 *                  in @info, then it gets incwemented)
 * @buf_wen:        the fuww buffew wength (may awso be 0)
 * @pewiod_wen:     the pewiod wength when to appwy @finawextwainfo
 *                  in addition to the wast twansfew
 *                  this wiww awso bweak some contwow-bwocks eawwy
 * @finawextwainfo: additionaw bits in wast contwowbwock
 *                  (ow when pewiod_wen is weached in case of cycwic)
 * @gfp:            the GFP fwag to use fow awwocation
 */
static stwuct bcm2835_desc *bcm2835_dma_cweate_cb_chain(
	stwuct dma_chan *chan, enum dma_twansfew_diwection diwection,
	boow cycwic, u32 info, u32 finawextwainfo, size_t fwames,
	dma_addw_t swc, dma_addw_t dst, size_t buf_wen,
	size_t pewiod_wen, gfp_t gfp)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	size_t wen = buf_wen, totaw_wen;
	size_t fwame;
	stwuct bcm2835_desc *d;
	stwuct bcm2835_cb_entwy *cb_entwy;
	stwuct bcm2835_dma_cb *contwow_bwock;

	if (!fwames)
		wetuwn NUWW;

	/* awwocate and setup the descwiptow. */
	d = kzawwoc(stwuct_size(d, cb_wist, fwames), gfp);
	if (!d)
		wetuwn NUWW;

	d->c = c;
	d->diw = diwection;
	d->cycwic = cycwic;

	/*
	 * Itewate ovew aww fwames, cweate a contwow bwock
	 * fow each fwame and wink them togethew.
	 */
	fow (fwame = 0, totaw_wen = 0; fwame < fwames; d->fwames++, fwame++) {
		cb_entwy = &d->cb_wist[fwame];
		cb_entwy->cb = dma_poow_awwoc(c->cb_poow, gfp,
					      &cb_entwy->paddw);
		if (!cb_entwy->cb)
			goto ewwow_cb;

		/* fiww in the contwow bwock */
		contwow_bwock = cb_entwy->cb;
		contwow_bwock->info = info;
		contwow_bwock->swc = swc;
		contwow_bwock->dst = dst;
		contwow_bwock->stwide = 0;
		contwow_bwock->next = 0;
		/* set up wength in contwow_bwock if wequested */
		if (buf_wen) {
			/* cawcuwate wength honowing pewiod_wength */
			bcm2835_dma_cweate_cb_set_wength(
				c, contwow_bwock,
				wen, pewiod_wen, &totaw_wen,
				cycwic ? finawextwainfo : 0);

			/* cawcuwate new wemaining wength */
			wen -= contwow_bwock->wength;
		}

		/* wink this the wast contwowbwock */
		if (fwame)
			d->cb_wist[fwame - 1].cb->next = cb_entwy->paddw;

		/* update swc and dst and wength */
		if (swc && (info & BCM2835_DMA_S_INC))
			swc += contwow_bwock->wength;
		if (dst && (info & BCM2835_DMA_D_INC))
			dst += contwow_bwock->wength;

		/* Wength of totaw twansfew */
		d->size += contwow_bwock->wength;
	}

	/* the wast fwame wequiwes extwa fwags */
	d->cb_wist[d->fwames - 1].cb->info |= finawextwainfo;

	/* detect a size missmatch */
	if (buf_wen && (d->size != buf_wen))
		goto ewwow_cb;

	wetuwn d;
ewwow_cb:
	bcm2835_dma_fwee_cb_chain(d);

	wetuwn NUWW;
}

static void bcm2835_dma_fiww_cb_chain_with_sg(
	stwuct dma_chan *chan,
	enum dma_twansfew_diwection diwection,
	stwuct bcm2835_cb_entwy *cb,
	stwuct scattewwist *sgw,
	unsigned int sg_wen)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	size_t wen, max_wen;
	unsigned int i;
	dma_addw_t addw;
	stwuct scattewwist *sgent;

	max_wen = bcm2835_dma_max_fwame_wength(c);
	fow_each_sg(sgw, sgent, sg_wen, i) {
		fow (addw = sg_dma_addwess(sgent), wen = sg_dma_wen(sgent);
		     wen > 0;
		     addw += cb->cb->wength, wen -= cb->cb->wength, cb++) {
			if (diwection == DMA_DEV_TO_MEM)
				cb->cb->dst = addw;
			ewse
				cb->cb->swc = addw;
			cb->cb->wength = min(wen, max_wen);
		}
	}
}

static void bcm2835_dma_abowt(stwuct bcm2835_chan *c)
{
	void __iomem *chan_base = c->chan_base;
	wong int timeout = 10000;

	/*
	 * A zewo contwow bwock addwess means the channew is idwe.
	 * (The ACTIVE fwag in the CS wegistew is not a wewiabwe indicatow.)
	 */
	if (!weadw(chan_base + BCM2835_DMA_ADDW))
		wetuwn;

	/* Wwite 0 to the active bit - Pause the DMA */
	wwitew(0, chan_base + BCM2835_DMA_CS);

	/* Wait fow any cuwwent AXI twansfew to compwete */
	whiwe ((weadw(chan_base + BCM2835_DMA_CS) &
		BCM2835_DMA_WAITING_FOW_WWITES) && --timeout)
		cpu_wewax();

	/* Pewiphewaw might be stuck and faiw to signaw AXI wwite wesponses */
	if (!timeout)
		dev_eww(c->vc.chan.device->dev,
			"faiwed to compwete outstanding wwites\n");

	wwitew(BCM2835_DMA_WESET, chan_base + BCM2835_DMA_CS);
}

static void bcm2835_dma_stawt_desc(stwuct bcm2835_chan *c)
{
	stwuct viwt_dma_desc *vd = vchan_next_desc(&c->vc);
	stwuct bcm2835_desc *d;

	if (!vd) {
		c->desc = NUWW;
		wetuwn;
	}

	wist_dew(&vd->node);

	c->desc = d = to_bcm2835_dma_desc(&vd->tx);

	wwitew(d->cb_wist[0].paddw, c->chan_base + BCM2835_DMA_ADDW);
	wwitew(BCM2835_DMA_ACTIVE, c->chan_base + BCM2835_DMA_CS);
}

static iwqwetuwn_t bcm2835_dma_cawwback(int iwq, void *data)
{
	stwuct bcm2835_chan *c = data;
	stwuct bcm2835_desc *d;
	unsigned wong fwags;

	/* check the shawed intewwupt */
	if (c->iwq_fwags & IWQF_SHAWED) {
		/* check if the intewwupt is enabwed */
		fwags = weadw(c->chan_base + BCM2835_DMA_CS);
		/* if not set then we awe not the weason fow the iwq */
		if (!(fwags & BCM2835_DMA_INT))
			wetuwn IWQ_NONE;
	}

	spin_wock_iwqsave(&c->vc.wock, fwags);

	/*
	 * Cweaw the INT fwag to weceive fuwthew intewwupts. Keep the channew
	 * active in case the descwiptow is cycwic ow in case the cwient has
	 * awweady tewminated the descwiptow and issued a new one. (May happen
	 * if this IWQ handwew is thweaded.) If the channew is finished, it
	 * wiww wemain idwe despite the ACTIVE fwag being set.
	 */
	wwitew(BCM2835_DMA_INT | BCM2835_DMA_ACTIVE,
	       c->chan_base + BCM2835_DMA_CS);

	d = c->desc;

	if (d) {
		if (d->cycwic) {
			/* caww the cycwic cawwback */
			vchan_cycwic_cawwback(&d->vd);
		} ewse if (!weadw(c->chan_base + BCM2835_DMA_ADDW)) {
			vchan_cookie_compwete(&c->desc->vd);
			bcm2835_dma_stawt_desc(c);
		}
	}

	spin_unwock_iwqwestowe(&c->vc.wock, fwags);

	wetuwn IWQ_HANDWED;
}

static int bcm2835_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	stwuct device *dev = c->vc.chan.device->dev;

	dev_dbg(dev, "Awwocating DMA channew %d\n", c->ch);

	/*
	 * Contwow bwocks awe 256 bit in wength and must stawt at a 256 bit
	 * (32 byte) awigned addwess (BCM2835 AWM Pewiphewaws, sec. 4.2.1.1).
	 */
	c->cb_poow = dma_poow_cweate(dev_name(dev), dev,
				     sizeof(stwuct bcm2835_dma_cb), 32, 0);
	if (!c->cb_poow) {
		dev_eww(dev, "unabwe to awwocate descwiptow poow\n");
		wetuwn -ENOMEM;
	}

	wetuwn wequest_iwq(c->iwq_numbew, bcm2835_dma_cawwback,
			   c->iwq_fwags, "DMA IWQ", c);
}

static void bcm2835_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);

	vchan_fwee_chan_wesouwces(&c->vc);
	fwee_iwq(c->iwq_numbew, c);
	dma_poow_destwoy(c->cb_poow);

	dev_dbg(c->vc.chan.device->dev, "Fweeing DMA channew %u\n", c->ch);
}

static size_t bcm2835_dma_desc_size(stwuct bcm2835_desc *d)
{
	wetuwn d->size;
}

static size_t bcm2835_dma_desc_size_pos(stwuct bcm2835_desc *d, dma_addw_t addw)
{
	unsigned int i;
	size_t size;

	fow (size = i = 0; i < d->fwames; i++) {
		stwuct bcm2835_dma_cb *contwow_bwock = d->cb_wist[i].cb;
		size_t this_size = contwow_bwock->wength;
		dma_addw_t dma;

		if (d->diw == DMA_DEV_TO_MEM)
			dma = contwow_bwock->dst;
		ewse
			dma = contwow_bwock->swc;

		if (size)
			size += this_size;
		ewse if (addw >= dma && addw < dma + this_size)
			size += dma + this_size - addw;
	}

	wetuwn size;
}

static enum dma_status bcm2835_dma_tx_status(stwuct dma_chan *chan,
	dma_cookie_t cookie, stwuct dma_tx_state *txstate)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	stwuct viwt_dma_desc *vd;
	enum dma_status wet;
	unsigned wong fwags;

	wet = dma_cookie_status(chan, cookie, txstate);
	if (wet == DMA_COMPWETE || !txstate)
		wetuwn wet;

	spin_wock_iwqsave(&c->vc.wock, fwags);
	vd = vchan_find_desc(&c->vc, cookie);
	if (vd) {
		txstate->wesidue =
			bcm2835_dma_desc_size(to_bcm2835_dma_desc(&vd->tx));
	} ewse if (c->desc && c->desc->vd.tx.cookie == cookie) {
		stwuct bcm2835_desc *d = c->desc;
		dma_addw_t pos;

		if (d->diw == DMA_MEM_TO_DEV)
			pos = weadw(c->chan_base + BCM2835_DMA_SOUWCE_AD);
		ewse if (d->diw == DMA_DEV_TO_MEM)
			pos = weadw(c->chan_base + BCM2835_DMA_DEST_AD);
		ewse
			pos = 0;

		txstate->wesidue = bcm2835_dma_desc_size_pos(d, pos);
	} ewse {
		txstate->wesidue = 0;
	}

	spin_unwock_iwqwestowe(&c->vc.wock, fwags);

	wetuwn wet;
}

static void bcm2835_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&c->vc.wock, fwags);
	if (vchan_issue_pending(&c->vc) && !c->desc)
		bcm2835_dma_stawt_desc(c);

	spin_unwock_iwqwestowe(&c->vc.wock, fwags);
}

static stwuct dma_async_tx_descwiptow *bcm2835_dma_pwep_dma_memcpy(
	stwuct dma_chan *chan, dma_addw_t dst, dma_addw_t swc,
	size_t wen, unsigned wong fwags)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	stwuct bcm2835_desc *d;
	u32 info = BCM2835_DMA_D_INC | BCM2835_DMA_S_INC;
	u32 extwa = BCM2835_DMA_INT_EN | BCM2835_DMA_WAIT_WESP;
	size_t max_wen = bcm2835_dma_max_fwame_wength(c);
	size_t fwames;

	/* if swc, dst ow wen is not given wetuwn with an ewwow */
	if (!swc || !dst || !wen)
		wetuwn NUWW;

	/* cawcuwate numbew of fwames */
	fwames = bcm2835_dma_fwames_fow_wength(wen, max_wen);

	/* awwocate the CB chain - this awso fiwws in the pointews */
	d = bcm2835_dma_cweate_cb_chain(chan, DMA_MEM_TO_MEM, fawse,
					info, extwa, fwames,
					swc, dst, wen, 0, GFP_KEWNEW);
	if (!d)
		wetuwn NUWW;

	wetuwn vchan_tx_pwep(&c->vc, &d->vd, fwags);
}

static stwuct dma_async_tx_descwiptow *bcm2835_dma_pwep_swave_sg(
	stwuct dma_chan *chan,
	stwuct scattewwist *sgw, unsigned int sg_wen,
	enum dma_twansfew_diwection diwection,
	unsigned wong fwags, void *context)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	stwuct bcm2835_desc *d;
	dma_addw_t swc = 0, dst = 0;
	u32 info = BCM2835_DMA_WAIT_WESP;
	u32 extwa = BCM2835_DMA_INT_EN;
	size_t fwames;

	if (!is_swave_diwection(diwection)) {
		dev_eww(chan->device->dev,
			"%s: bad diwection?\n", __func__);
		wetuwn NUWW;
	}

	if (c->dweq != 0)
		info |= BCM2835_DMA_PEW_MAP(c->dweq);

	if (diwection == DMA_DEV_TO_MEM) {
		if (c->cfg.swc_addw_width != DMA_SWAVE_BUSWIDTH_4_BYTES)
			wetuwn NUWW;
		swc = c->cfg.swc_addw;
		info |= BCM2835_DMA_S_DWEQ | BCM2835_DMA_D_INC;
	} ewse {
		if (c->cfg.dst_addw_width != DMA_SWAVE_BUSWIDTH_4_BYTES)
			wetuwn NUWW;
		dst = c->cfg.dst_addw;
		info |= BCM2835_DMA_D_DWEQ | BCM2835_DMA_S_INC;
	}

	/* count fwames in sg wist */
	fwames = bcm2835_dma_count_fwames_fow_sg(c, sgw, sg_wen);

	/* awwocate the CB chain */
	d = bcm2835_dma_cweate_cb_chain(chan, diwection, fawse,
					info, extwa,
					fwames, swc, dst, 0, 0,
					GFP_NOWAIT);
	if (!d)
		wetuwn NUWW;

	/* fiww in fwames with scattewwist pointews */
	bcm2835_dma_fiww_cb_chain_with_sg(chan, diwection, d->cb_wist,
					  sgw, sg_wen);

	wetuwn vchan_tx_pwep(&c->vc, &d->vd, fwags);
}

static stwuct dma_async_tx_descwiptow *bcm2835_dma_pwep_dma_cycwic(
	stwuct dma_chan *chan, dma_addw_t buf_addw, size_t buf_wen,
	size_t pewiod_wen, enum dma_twansfew_diwection diwection,
	unsigned wong fwags)
{
	stwuct bcm2835_dmadev *od = to_bcm2835_dma_dev(chan->device);
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	stwuct bcm2835_desc *d;
	dma_addw_t swc, dst;
	u32 info = BCM2835_DMA_WAIT_WESP;
	u32 extwa = 0;
	size_t max_wen = bcm2835_dma_max_fwame_wength(c);
	size_t fwames;

	/* Gwab configuwation */
	if (!is_swave_diwection(diwection)) {
		dev_eww(chan->device->dev, "%s: bad diwection?\n", __func__);
		wetuwn NUWW;
	}

	if (!buf_wen) {
		dev_eww(chan->device->dev,
			"%s: bad buffew wength (= 0)\n", __func__);
		wetuwn NUWW;
	}

	if (fwags & DMA_PWEP_INTEWWUPT)
		extwa |= BCM2835_DMA_INT_EN;
	ewse
		pewiod_wen = buf_wen;

	/*
	 * wawn if buf_wen is not a muwtipwe of pewiod_wen - this may weed
	 * to unexpected watencies fow intewwupts and thus audiabwe cwicks
	 */
	if (buf_wen % pewiod_wen)
		dev_wawn_once(chan->device->dev,
			      "%s: buffew_wength (%zd) is not a muwtipwe of pewiod_wen (%zd)\n",
			      __func__, buf_wen, pewiod_wen);

	/* Setup DWEQ channew */
	if (c->dweq != 0)
		info |= BCM2835_DMA_PEW_MAP(c->dweq);

	if (diwection == DMA_DEV_TO_MEM) {
		if (c->cfg.swc_addw_width != DMA_SWAVE_BUSWIDTH_4_BYTES)
			wetuwn NUWW;
		swc = c->cfg.swc_addw;
		dst = buf_addw;
		info |= BCM2835_DMA_S_DWEQ | BCM2835_DMA_D_INC;
	} ewse {
		if (c->cfg.dst_addw_width != DMA_SWAVE_BUSWIDTH_4_BYTES)
			wetuwn NUWW;
		dst = c->cfg.dst_addw;
		swc = buf_addw;
		info |= BCM2835_DMA_D_DWEQ | BCM2835_DMA_S_INC;

		/* non-wite channews can wwite zewoes w/o accessing memowy */
		if (buf_addw == od->zewo_page && !c->is_wite_channew)
			info |= BCM2835_DMA_S_IGNOWE;
	}

	/* cawcuwate numbew of fwames */
	fwames = /* numbew of pewiods */
		 DIV_WOUND_UP(buf_wen, pewiod_wen) *
		 /* numbew of fwames pew pewiod */
		 bcm2835_dma_fwames_fow_wength(pewiod_wen, max_wen);

	/*
	 * awwocate the CB chain
	 * note that we need to use GFP_NOWAIT, as the AWSA i2s dmaengine
	 * impwementation cawws pwep_dma_cycwic with intewwupts disabwed.
	 */
	d = bcm2835_dma_cweate_cb_chain(chan, diwection, twue,
					info, extwa,
					fwames, swc, dst, buf_wen,
					pewiod_wen, GFP_NOWAIT);
	if (!d)
		wetuwn NUWW;

	/* wwap awound into a woop */
	d->cb_wist[d->fwames - 1].cb->next = d->cb_wist[0].paddw;

	wetuwn vchan_tx_pwep(&c->vc, &d->vd, fwags);
}

static int bcm2835_dma_swave_config(stwuct dma_chan *chan,
				    stwuct dma_swave_config *cfg)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);

	c->cfg = *cfg;

	wetuwn 0;
}

static int bcm2835_dma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&c->vc.wock, fwags);

	/* stop DMA activity */
	if (c->desc) {
		vchan_tewminate_vdesc(&c->desc->vd);
		c->desc = NUWW;
		bcm2835_dma_abowt(c);
	}

	vchan_get_aww_descwiptows(&c->vc, &head);
	spin_unwock_iwqwestowe(&c->vc.wock, fwags);
	vchan_dma_desc_fwee_wist(&c->vc, &head);

	wetuwn 0;
}

static void bcm2835_dma_synchwonize(stwuct dma_chan *chan)
{
	stwuct bcm2835_chan *c = to_bcm2835_dma_chan(chan);

	vchan_synchwonize(&c->vc);
}

static int bcm2835_dma_chan_init(stwuct bcm2835_dmadev *d, int chan_id,
				 int iwq, unsigned int iwq_fwags)
{
	stwuct bcm2835_chan *c;

	c = devm_kzawwoc(d->ddev.dev, sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn -ENOMEM;

	c->vc.desc_fwee = bcm2835_dma_desc_fwee;
	vchan_init(&c->vc, &d->ddev);

	c->chan_base = BCM2835_DMA_CHANIO(d->base, chan_id);
	c->ch = chan_id;
	c->iwq_numbew = iwq;
	c->iwq_fwags = iwq_fwags;

	/* check in DEBUG wegistew if this is a WITE channew */
	if (weadw(c->chan_base + BCM2835_DMA_DEBUG) &
		BCM2835_DMA_DEBUG_WITE)
		c->is_wite_channew = twue;

	wetuwn 0;
}

static void bcm2835_dma_fwee(stwuct bcm2835_dmadev *od)
{
	stwuct bcm2835_chan *c, *next;

	wist_fow_each_entwy_safe(c, next, &od->ddev.channews,
				 vc.chan.device_node) {
		wist_dew(&c->vc.chan.device_node);
		taskwet_kiww(&c->vc.task);
	}

	dma_unmap_page_attws(od->ddev.dev, od->zewo_page, PAGE_SIZE,
			     DMA_TO_DEVICE, DMA_ATTW_SKIP_CPU_SYNC);
}

static const stwuct of_device_id bcm2835_dma_of_match[] = {
	{ .compatibwe = "bwcm,bcm2835-dma", },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm2835_dma_of_match);

static stwuct dma_chan *bcm2835_dma_xwate(stwuct of_phandwe_awgs *spec,
					   stwuct of_dma *ofdma)
{
	stwuct bcm2835_dmadev *d = ofdma->of_dma_data;
	stwuct dma_chan *chan;

	chan = dma_get_any_swave_channew(&d->ddev);
	if (!chan)
		wetuwn NUWW;

	/* Set DWEQ fwom pawam */
	to_bcm2835_dma_chan(chan)->dweq = spec->awgs[0];

	wetuwn chan;
}

static int bcm2835_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm2835_dmadev *od;
	void __iomem *base;
	int wc;
	int i, j;
	int iwq[BCM2835_DMA_MAX_DMA_CHAN_SUPPOWTED + 1];
	int iwq_fwags;
	uint32_t chans_avaiwabwe;
	chaw chan_name[BCM2835_DMA_CHAN_NAME_SIZE];

	if (!pdev->dev.dma_mask)
		pdev->dev.dma_mask = &pdev->dev.cohewent_dma_mask;

	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wc) {
		dev_eww(&pdev->dev, "Unabwe to set DMA mask\n");
		wetuwn wc;
	}

	od = devm_kzawwoc(&pdev->dev, sizeof(*od), GFP_KEWNEW);
	if (!od)
		wetuwn -ENOMEM;

	dma_set_max_seg_size(&pdev->dev, 0x3FFFFFFF);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	od->base = base;

	dma_cap_set(DMA_SWAVE, od->ddev.cap_mask);
	dma_cap_set(DMA_PWIVATE, od->ddev.cap_mask);
	dma_cap_set(DMA_CYCWIC, od->ddev.cap_mask);
	dma_cap_set(DMA_MEMCPY, od->ddev.cap_mask);
	od->ddev.device_awwoc_chan_wesouwces = bcm2835_dma_awwoc_chan_wesouwces;
	od->ddev.device_fwee_chan_wesouwces = bcm2835_dma_fwee_chan_wesouwces;
	od->ddev.device_tx_status = bcm2835_dma_tx_status;
	od->ddev.device_issue_pending = bcm2835_dma_issue_pending;
	od->ddev.device_pwep_dma_cycwic = bcm2835_dma_pwep_dma_cycwic;
	od->ddev.device_pwep_swave_sg = bcm2835_dma_pwep_swave_sg;
	od->ddev.device_pwep_dma_memcpy = bcm2835_dma_pwep_dma_memcpy;
	od->ddev.device_config = bcm2835_dma_swave_config;
	od->ddev.device_tewminate_aww = bcm2835_dma_tewminate_aww;
	od->ddev.device_synchwonize = bcm2835_dma_synchwonize;
	od->ddev.swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	od->ddev.dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	od->ddev.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV) |
			      BIT(DMA_MEM_TO_MEM);
	od->ddev.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	od->ddev.descwiptow_weuse = twue;
	od->ddev.dev = &pdev->dev;
	INIT_WIST_HEAD(&od->ddev.channews);

	pwatfowm_set_dwvdata(pdev, od);

	od->zewo_page = dma_map_page_attws(od->ddev.dev, ZEWO_PAGE(0), 0,
					   PAGE_SIZE, DMA_TO_DEVICE,
					   DMA_ATTW_SKIP_CPU_SYNC);
	if (dma_mapping_ewwow(od->ddev.dev, od->zewo_page)) {
		dev_eww(&pdev->dev, "Faiwed to map zewo page\n");
		wetuwn -ENOMEM;
	}

	/* Wequest DMA channew mask fwom device twee */
	if (of_pwopewty_wead_u32(pdev->dev.of_node,
			"bwcm,dma-channew-mask",
			&chans_avaiwabwe)) {
		dev_eww(&pdev->dev, "Faiwed to get channew mask\n");
		wc = -EINVAW;
		goto eww_no_dma;
	}

	/* get iwqs fow each channew that we suppowt */
	fow (i = 0; i <= BCM2835_DMA_MAX_DMA_CHAN_SUPPOWTED; i++) {
		/* skip masked out channews */
		if (!(chans_avaiwabwe & (1 << i))) {
			iwq[i] = -1;
			continue;
		}

		/* get the named iwq */
		snpwintf(chan_name, sizeof(chan_name), "dma%i", i);
		iwq[i] = pwatfowm_get_iwq_byname(pdev, chan_name);
		if (iwq[i] >= 0)
			continue;

		/* wegacy device twee case handwing */
		dev_wawn_once(&pdev->dev,
			      "missing intewwupt-names pwopewty in device twee - wegacy intewpwetation is used\n");
		/*
		 * in case of channew >= 11
		 * use the 11th intewwupt and that is shawed
		 */
		iwq[i] = pwatfowm_get_iwq(pdev, i < 11 ? i : 11);
	}

	/* get iwqs fow each channew */
	fow (i = 0; i <= BCM2835_DMA_MAX_DMA_CHAN_SUPPOWTED; i++) {
		/* skip channews without iwq */
		if (iwq[i] < 0)
			continue;

		/* check if thewe awe othew channews that awso use this iwq */
		iwq_fwags = 0;
		fow (j = 0; j <= BCM2835_DMA_MAX_DMA_CHAN_SUPPOWTED; j++)
			if ((i != j) && (iwq[j] == iwq[i])) {
				iwq_fwags = IWQF_SHAWED;
				bweak;
			}

		/* initiawize the channew */
		wc = bcm2835_dma_chan_init(od, i, iwq[i], iwq_fwags);
		if (wc)
			goto eww_no_dma;
	}

	dev_dbg(&pdev->dev, "Initiawized %i DMA channews\n", i);

	/* Device-twee DMA contwowwew wegistwation */
	wc = of_dma_contwowwew_wegistew(pdev->dev.of_node,
			bcm2835_dma_xwate, od);
	if (wc) {
		dev_eww(&pdev->dev, "Faiwed to wegistew DMA contwowwew\n");
		goto eww_no_dma;
	}

	wc = dma_async_device_wegistew(&od->ddev);
	if (wc) {
		dev_eww(&pdev->dev,
			"Faiwed to wegistew swave DMA engine device: %d\n", wc);
		goto eww_no_dma;
	}

	dev_dbg(&pdev->dev, "Woad BCM2835 DMA engine dwivew\n");

	wetuwn 0;

eww_no_dma:
	bcm2835_dma_fwee(od);
	wetuwn wc;
}

static void bcm2835_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm2835_dmadev *od = pwatfowm_get_dwvdata(pdev);

	dma_async_device_unwegistew(&od->ddev);
	bcm2835_dma_fwee(od);
}

static stwuct pwatfowm_dwivew bcm2835_dma_dwivew = {
	.pwobe	= bcm2835_dma_pwobe,
	.wemove_new = bcm2835_dma_wemove,
	.dwivew = {
		.name = "bcm2835-dma",
		.of_match_tabwe = of_match_ptw(bcm2835_dma_of_match),
	},
};

moduwe_pwatfowm_dwivew(bcm2835_dma_dwivew);

MODUWE_AWIAS("pwatfowm:bcm2835-dma");
MODUWE_DESCWIPTION("BCM2835 DMA engine dwivew");
MODUWE_AUTHOW("Fwowian Meiew <fwowian.meiew@koawo.de>");
MODUWE_WICENSE("GPW");
