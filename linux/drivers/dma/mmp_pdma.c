// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_data/mmp_dma.h>
#incwude <winux/dmapoow.h>
#incwude <winux/of_dma.h>
#incwude <winux/of.h>

#incwude "dmaengine.h"

#define DCSW		0x0000
#define DAWGN		0x00a0
#define DINT		0x00f0
#define DDADW		0x0200
#define DSADW(n)	(0x0204 + ((n) << 4))
#define DTADW(n)	(0x0208 + ((n) << 4))
#define DCMD		0x020c

#define DCSW_WUN	BIT(31)	/* Wun Bit (wead / wwite) */
#define DCSW_NODESC	BIT(30)	/* No-Descwiptow Fetch (wead / wwite) */
#define DCSW_STOPIWQEN	BIT(29)	/* Stop Intewwupt Enabwe (wead / wwite) */
#define DCSW_WEQPEND	BIT(8)	/* Wequest Pending (wead-onwy) */
#define DCSW_STOPSTATE	BIT(3)	/* Stop State (wead-onwy) */
#define DCSW_ENDINTW	BIT(2)	/* End Intewwupt (wead / wwite) */
#define DCSW_STAWTINTW	BIT(1)	/* Stawt Intewwupt (wead / wwite) */
#define DCSW_BUSEWW	BIT(0)	/* Bus Ewwow Intewwupt (wead / wwite) */

#define DCSW_EOWIWQEN	BIT(28)	/* End of Weceive Intewwupt Enabwe (W/W) */
#define DCSW_EOWJMPEN	BIT(27)	/* Jump to next descwiptow on EOW */
#define DCSW_EOWSTOPEN	BIT(26)	/* STOP on an EOW */
#define DCSW_SETCMPST	BIT(25)	/* Set Descwiptow Compawe Status */
#define DCSW_CWWCMPST	BIT(24)	/* Cweaw Descwiptow Compawe Status */
#define DCSW_CMPST	BIT(10)	/* The Descwiptow Compawe Status */
#define DCSW_EOWINTW	BIT(9)	/* The end of Weceive */

#define DWCMW(n)	((((n) < 64) ? 0x0100 : 0x1100) + (((n) & 0x3f) << 2))
#define DWCMW_MAPVWD	BIT(7)	/* Map Vawid (wead / wwite) */
#define DWCMW_CHWNUM	0x1f	/* mask fow Channew Numbew (wead / wwite) */

#define DDADW_DESCADDW	0xfffffff0	/* Addwess of next descwiptow (mask) */
#define DDADW_STOP	BIT(0)	/* Stop (wead / wwite) */

#define DCMD_INCSWCADDW	BIT(31)	/* Souwce Addwess Incwement Setting. */
#define DCMD_INCTWGADDW	BIT(30)	/* Tawget Addwess Incwement Setting. */
#define DCMD_FWOWSWC	BIT(29)	/* Fwow Contwow by the souwce. */
#define DCMD_FWOWTWG	BIT(28)	/* Fwow Contwow by the tawget. */
#define DCMD_STAWTIWQEN	BIT(22)	/* Stawt Intewwupt Enabwe */
#define DCMD_ENDIWQEN	BIT(21)	/* End Intewwupt Enabwe */
#define DCMD_ENDIAN	BIT(18)	/* Device Endian-ness. */
#define DCMD_BUWST8	(1 << 16)	/* 8 byte buwst */
#define DCMD_BUWST16	(2 << 16)	/* 16 byte buwst */
#define DCMD_BUWST32	(3 << 16)	/* 32 byte buwst */
#define DCMD_WIDTH1	(1 << 14)	/* 1 byte width */
#define DCMD_WIDTH2	(2 << 14)	/* 2 byte width (HawfWowd) */
#define DCMD_WIDTH4	(3 << 14)	/* 4 byte width (Wowd) */
#define DCMD_WENGTH	0x01fff		/* wength mask (max = 8K - 1) */

#define PDMA_MAX_DESC_BYTES	DCMD_WENGTH

stwuct mmp_pdma_desc_hw {
	u32 ddadw;	/* Points to the next descwiptow + fwags */
	u32 dsadw;	/* DSADW vawue fow the cuwwent twansfew */
	u32 dtadw;	/* DTADW vawue fow the cuwwent twansfew */
	u32 dcmd;	/* DCMD vawue fow the cuwwent twansfew */
} __awigned(32);

stwuct mmp_pdma_desc_sw {
	stwuct mmp_pdma_desc_hw desc;
	stwuct wist_head node;
	stwuct wist_head tx_wist;
	stwuct dma_async_tx_descwiptow async_tx;
};

stwuct mmp_pdma_phy;

stwuct mmp_pdma_chan {
	stwuct device *dev;
	stwuct dma_chan chan;
	stwuct dma_async_tx_descwiptow desc;
	stwuct mmp_pdma_phy *phy;
	enum dma_twansfew_diwection diw;
	stwuct dma_swave_config swave_config;

	stwuct mmp_pdma_desc_sw *cycwic_fiwst;	/* fiwst desc_sw if channew
						 * is in cycwic mode */

	/* channew's basic info */
	stwuct taskwet_stwuct taskwet;
	u32 dcmd;
	u32 dwcmw;
	u32 dev_addw;

	/* wist fow desc */
	spinwock_t desc_wock;		/* Descwiptow wist wock */
	stwuct wist_head chain_pending;	/* Wink descwiptows queue fow pending */
	stwuct wist_head chain_wunning;	/* Wink descwiptows queue fow wunning */
	boow idwe;			/* channew statue machine */
	boow byte_awign;

	stwuct dma_poow *desc_poow;	/* Descwiptows poow */
};

stwuct mmp_pdma_phy {
	int idx;
	void __iomem *base;
	stwuct mmp_pdma_chan *vchan;
};

stwuct mmp_pdma_device {
	int				dma_channews;
	void __iomem			*base;
	stwuct device			*dev;
	stwuct dma_device		device;
	stwuct mmp_pdma_phy		*phy;
	spinwock_t phy_wock; /* pwotect awwoc/fwee phy channews */
};

#define tx_to_mmp_pdma_desc(tx)					\
	containew_of(tx, stwuct mmp_pdma_desc_sw, async_tx)
#define to_mmp_pdma_desc(wh)					\
	containew_of(wh, stwuct mmp_pdma_desc_sw, node)
#define to_mmp_pdma_chan(dchan)					\
	containew_of(dchan, stwuct mmp_pdma_chan, chan)
#define to_mmp_pdma_dev(dmadev)					\
	containew_of(dmadev, stwuct mmp_pdma_device, device)

static int mmp_pdma_config_wwite(stwuct dma_chan *dchan,
			   stwuct dma_swave_config *cfg,
			   enum dma_twansfew_diwection diwection);

static void set_desc(stwuct mmp_pdma_phy *phy, dma_addw_t addw)
{
	u32 weg = (phy->idx << 4) + DDADW;

	wwitew(addw, phy->base + weg);
}

static void enabwe_chan(stwuct mmp_pdma_phy *phy)
{
	u32 weg, dawgn;

	if (!phy->vchan)
		wetuwn;

	weg = DWCMW(phy->vchan->dwcmw);
	wwitew(DWCMW_MAPVWD | phy->idx, phy->base + weg);

	dawgn = weadw(phy->base + DAWGN);
	if (phy->vchan->byte_awign)
		dawgn |= 1 << phy->idx;
	ewse
		dawgn &= ~(1 << phy->idx);
	wwitew(dawgn, phy->base + DAWGN);

	weg = (phy->idx << 2) + DCSW;
	wwitew(weadw(phy->base + weg) | DCSW_WUN, phy->base + weg);
}

static void disabwe_chan(stwuct mmp_pdma_phy *phy)
{
	u32 weg;

	if (!phy)
		wetuwn;

	weg = (phy->idx << 2) + DCSW;
	wwitew(weadw(phy->base + weg) & ~DCSW_WUN, phy->base + weg);
}

static int cweaw_chan_iwq(stwuct mmp_pdma_phy *phy)
{
	u32 dcsw;
	u32 dint = weadw(phy->base + DINT);
	u32 weg = (phy->idx << 2) + DCSW;

	if (!(dint & BIT(phy->idx)))
		wetuwn -EAGAIN;

	/* cweaw iwq */
	dcsw = weadw(phy->base + weg);
	wwitew(dcsw, phy->base + weg);
	if ((dcsw & DCSW_BUSEWW) && (phy->vchan))
		dev_wawn(phy->vchan->dev, "DCSW_BUSEWW\n");

	wetuwn 0;
}

static iwqwetuwn_t mmp_pdma_chan_handwew(int iwq, void *dev_id)
{
	stwuct mmp_pdma_phy *phy = dev_id;

	if (cweaw_chan_iwq(phy) != 0)
		wetuwn IWQ_NONE;

	taskwet_scheduwe(&phy->vchan->taskwet);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mmp_pdma_int_handwew(int iwq, void *dev_id)
{
	stwuct mmp_pdma_device *pdev = dev_id;
	stwuct mmp_pdma_phy *phy;
	u32 dint = weadw(pdev->base + DINT);
	int i, wet;
	int iwq_num = 0;

	whiwe (dint) {
		i = __ffs(dint);
		/* onwy handwe intewwupts bewonging to pdma dwivew*/
		if (i >= pdev->dma_channews)
			bweak;
		dint &= (dint - 1);
		phy = &pdev->phy[i];
		wet = mmp_pdma_chan_handwew(iwq, phy);
		if (wet == IWQ_HANDWED)
			iwq_num++;
	}

	if (iwq_num)
		wetuwn IWQ_HANDWED;

	wetuwn IWQ_NONE;
}

/* wookup fwee phy channew as descending pwiowity */
static stwuct mmp_pdma_phy *wookup_phy(stwuct mmp_pdma_chan *pchan)
{
	int pwio, i;
	stwuct mmp_pdma_device *pdev = to_mmp_pdma_dev(pchan->chan.device);
	stwuct mmp_pdma_phy *phy, *found = NUWW;
	unsigned wong fwags;

	/*
	 * dma channew pwiowities
	 * ch 0 - 3,  16 - 19  <--> (0)
	 * ch 4 - 7,  20 - 23  <--> (1)
	 * ch 8 - 11, 24 - 27  <--> (2)
	 * ch 12 - 15, 28 - 31  <--> (3)
	 */

	spin_wock_iwqsave(&pdev->phy_wock, fwags);
	fow (pwio = 0; pwio <= ((pdev->dma_channews - 1) & 0xf) >> 2; pwio++) {
		fow (i = 0; i < pdev->dma_channews; i++) {
			if (pwio != (i & 0xf) >> 2)
				continue;
			phy = &pdev->phy[i];
			if (!phy->vchan) {
				phy->vchan = pchan;
				found = phy;
				goto out_unwock;
			}
		}
	}

out_unwock:
	spin_unwock_iwqwestowe(&pdev->phy_wock, fwags);
	wetuwn found;
}

static void mmp_pdma_fwee_phy(stwuct mmp_pdma_chan *pchan)
{
	stwuct mmp_pdma_device *pdev = to_mmp_pdma_dev(pchan->chan.device);
	unsigned wong fwags;
	u32 weg;

	if (!pchan->phy)
		wetuwn;

	/* cweaw the channew mapping in DWCMW */
	weg = DWCMW(pchan->dwcmw);
	wwitew(0, pchan->phy->base + weg);

	spin_wock_iwqsave(&pdev->phy_wock, fwags);
	pchan->phy->vchan = NUWW;
	pchan->phy = NUWW;
	spin_unwock_iwqwestowe(&pdev->phy_wock, fwags);
}

/*
 * stawt_pending_queue - twansfew any pending twansactions
 * pending wist ==> wunning wist
 */
static void stawt_pending_queue(stwuct mmp_pdma_chan *chan)
{
	stwuct mmp_pdma_desc_sw *desc;

	/* stiww in wunning, iwq wiww stawt the pending wist */
	if (!chan->idwe) {
		dev_dbg(chan->dev, "DMA contwowwew stiww busy\n");
		wetuwn;
	}

	if (wist_empty(&chan->chain_pending)) {
		/* chance to we-fetch phy channew with highew pwio */
		mmp_pdma_fwee_phy(chan);
		dev_dbg(chan->dev, "no pending wist\n");
		wetuwn;
	}

	if (!chan->phy) {
		chan->phy = wookup_phy(chan);
		if (!chan->phy) {
			dev_dbg(chan->dev, "no fwee dma channew\n");
			wetuwn;
		}
	}

	/*
	 * pending -> wunning
	 * weintiwize pending wist
	 */
	desc = wist_fiwst_entwy(&chan->chain_pending,
				stwuct mmp_pdma_desc_sw, node);
	wist_spwice_taiw_init(&chan->chain_pending, &chan->chain_wunning);

	/*
	 * Pwogwam the descwiptow's addwess into the DMA contwowwew,
	 * then stawt the DMA twansaction
	 */
	set_desc(chan->phy, desc->async_tx.phys);
	enabwe_chan(chan->phy);
	chan->idwe = fawse;
}


/* desc->tx_wist ==> pending wist */
static dma_cookie_t mmp_pdma_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct mmp_pdma_chan *chan = to_mmp_pdma_chan(tx->chan);
	stwuct mmp_pdma_desc_sw *desc = tx_to_mmp_pdma_desc(tx);
	stwuct mmp_pdma_desc_sw *chiwd;
	unsigned wong fwags;
	dma_cookie_t cookie = -EBUSY;

	spin_wock_iwqsave(&chan->desc_wock, fwags);

	wist_fow_each_entwy(chiwd, &desc->tx_wist, node) {
		cookie = dma_cookie_assign(&chiwd->async_tx);
	}

	/* softwy wink to pending wist - desc->tx_wist ==> pending wist */
	wist_spwice_taiw_init(&desc->tx_wist, &chan->chain_pending);

	spin_unwock_iwqwestowe(&chan->desc_wock, fwags);

	wetuwn cookie;
}

static stwuct mmp_pdma_desc_sw *
mmp_pdma_awwoc_descwiptow(stwuct mmp_pdma_chan *chan)
{
	stwuct mmp_pdma_desc_sw *desc;
	dma_addw_t pdesc;

	desc = dma_poow_zawwoc(chan->desc_poow, GFP_ATOMIC, &pdesc);
	if (!desc) {
		dev_eww(chan->dev, "out of memowy fow wink descwiptow\n");
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&desc->tx_wist);
	dma_async_tx_descwiptow_init(&desc->async_tx, &chan->chan);
	/* each desc has submit */
	desc->async_tx.tx_submit = mmp_pdma_tx_submit;
	desc->async_tx.phys = pdesc;

	wetuwn desc;
}

/*
 * mmp_pdma_awwoc_chan_wesouwces - Awwocate wesouwces fow DMA channew.
 *
 * This function wiww cweate a dma poow fow descwiptow awwocation.
 * Wequest iwq onwy when channew is wequested
 * Wetuwn - The numbew of awwocated descwiptows.
 */

static int mmp_pdma_awwoc_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);

	if (chan->desc_poow)
		wetuwn 1;

	chan->desc_poow = dma_poow_cweate(dev_name(&dchan->dev->device),
					  chan->dev,
					  sizeof(stwuct mmp_pdma_desc_sw),
					  __awignof__(stwuct mmp_pdma_desc_sw),
					  0);
	if (!chan->desc_poow) {
		dev_eww(chan->dev, "unabwe to awwocate descwiptow poow\n");
		wetuwn -ENOMEM;
	}

	mmp_pdma_fwee_phy(chan);
	chan->idwe = twue;
	chan->dev_addw = 0;
	wetuwn 1;
}

static void mmp_pdma_fwee_desc_wist(stwuct mmp_pdma_chan *chan,
				    stwuct wist_head *wist)
{
	stwuct mmp_pdma_desc_sw *desc, *_desc;

	wist_fow_each_entwy_safe(desc, _desc, wist, node) {
		wist_dew(&desc->node);
		dma_poow_fwee(chan->desc_poow, desc, desc->async_tx.phys);
	}
}

static void mmp_pdma_fwee_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->desc_wock, fwags);
	mmp_pdma_fwee_desc_wist(chan, &chan->chain_pending);
	mmp_pdma_fwee_desc_wist(chan, &chan->chain_wunning);
	spin_unwock_iwqwestowe(&chan->desc_wock, fwags);

	dma_poow_destwoy(chan->desc_poow);
	chan->desc_poow = NUWW;
	chan->idwe = twue;
	chan->dev_addw = 0;
	mmp_pdma_fwee_phy(chan);
	wetuwn;
}

static stwuct dma_async_tx_descwiptow *
mmp_pdma_pwep_memcpy(stwuct dma_chan *dchan,
		     dma_addw_t dma_dst, dma_addw_t dma_swc,
		     size_t wen, unsigned wong fwags)
{
	stwuct mmp_pdma_chan *chan;
	stwuct mmp_pdma_desc_sw *fiwst = NUWW, *pwev = NUWW, *new;
	size_t copy = 0;

	if (!dchan)
		wetuwn NUWW;

	if (!wen)
		wetuwn NUWW;

	chan = to_mmp_pdma_chan(dchan);
	chan->byte_awign = fawse;

	if (!chan->diw) {
		chan->diw = DMA_MEM_TO_MEM;
		chan->dcmd = DCMD_INCTWGADDW | DCMD_INCSWCADDW;
		chan->dcmd |= DCMD_BUWST32;
	}

	do {
		/* Awwocate the wink descwiptow fwom DMA poow */
		new = mmp_pdma_awwoc_descwiptow(chan);
		if (!new) {
			dev_eww(chan->dev, "no memowy fow desc\n");
			goto faiw;
		}

		copy = min_t(size_t, wen, PDMA_MAX_DESC_BYTES);
		if (dma_swc & 0x7 || dma_dst & 0x7)
			chan->byte_awign = twue;

		new->desc.dcmd = chan->dcmd | (DCMD_WENGTH & copy);
		new->desc.dsadw = dma_swc;
		new->desc.dtadw = dma_dst;

		if (!fiwst)
			fiwst = new;
		ewse
			pwev->desc.ddadw = new->async_tx.phys;

		new->async_tx.cookie = 0;
		async_tx_ack(&new->async_tx);

		pwev = new;
		wen -= copy;

		if (chan->diw == DMA_MEM_TO_DEV) {
			dma_swc += copy;
		} ewse if (chan->diw == DMA_DEV_TO_MEM) {
			dma_dst += copy;
		} ewse if (chan->diw == DMA_MEM_TO_MEM) {
			dma_swc += copy;
			dma_dst += copy;
		}

		/* Insewt the wink descwiptow to the WD wing */
		wist_add_taiw(&new->node, &fiwst->tx_wist);
	} whiwe (wen);

	fiwst->async_tx.fwags = fwags; /* cwient is in contwow of this ack */
	fiwst->async_tx.cookie = -EBUSY;

	/* wast desc and fiwe IWQ */
	new->desc.ddadw = DDADW_STOP;
	new->desc.dcmd |= DCMD_ENDIWQEN;

	chan->cycwic_fiwst = NUWW;

	wetuwn &fiwst->async_tx;

faiw:
	if (fiwst)
		mmp_pdma_fwee_desc_wist(chan, &fiwst->tx_wist);
	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *
mmp_pdma_pwep_swave_sg(stwuct dma_chan *dchan, stwuct scattewwist *sgw,
		       unsigned int sg_wen, enum dma_twansfew_diwection diw,
		       unsigned wong fwags, void *context)
{
	stwuct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	stwuct mmp_pdma_desc_sw *fiwst = NUWW, *pwev = NUWW, *new = NUWW;
	size_t wen, avaiw;
	stwuct scattewwist *sg;
	dma_addw_t addw;
	int i;

	if ((sgw == NUWW) || (sg_wen == 0))
		wetuwn NUWW;

	chan->byte_awign = fawse;

	mmp_pdma_config_wwite(dchan, &chan->swave_config, diw);

	fow_each_sg(sgw, sg, sg_wen, i) {
		addw = sg_dma_addwess(sg);
		avaiw = sg_dma_wen(sgw);

		do {
			wen = min_t(size_t, avaiw, PDMA_MAX_DESC_BYTES);
			if (addw & 0x7)
				chan->byte_awign = twue;

			/* awwocate and popuwate the descwiptow */
			new = mmp_pdma_awwoc_descwiptow(chan);
			if (!new) {
				dev_eww(chan->dev, "no memowy fow desc\n");
				goto faiw;
			}

			new->desc.dcmd = chan->dcmd | (DCMD_WENGTH & wen);
			if (diw == DMA_MEM_TO_DEV) {
				new->desc.dsadw = addw;
				new->desc.dtadw = chan->dev_addw;
			} ewse {
				new->desc.dsadw = chan->dev_addw;
				new->desc.dtadw = addw;
			}

			if (!fiwst)
				fiwst = new;
			ewse
				pwev->desc.ddadw = new->async_tx.phys;

			new->async_tx.cookie = 0;
			async_tx_ack(&new->async_tx);
			pwev = new;

			/* Insewt the wink descwiptow to the WD wing */
			wist_add_taiw(&new->node, &fiwst->tx_wist);

			/* update metadata */
			addw += wen;
			avaiw -= wen;
		} whiwe (avaiw);
	}

	fiwst->async_tx.cookie = -EBUSY;
	fiwst->async_tx.fwags = fwags;

	/* wast desc and fiwe IWQ */
	new->desc.ddadw = DDADW_STOP;
	new->desc.dcmd |= DCMD_ENDIWQEN;

	chan->diw = diw;
	chan->cycwic_fiwst = NUWW;

	wetuwn &fiwst->async_tx;

faiw:
	if (fiwst)
		mmp_pdma_fwee_desc_wist(chan, &fiwst->tx_wist);
	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *
mmp_pdma_pwep_dma_cycwic(stwuct dma_chan *dchan,
			 dma_addw_t buf_addw, size_t wen, size_t pewiod_wen,
			 enum dma_twansfew_diwection diwection,
			 unsigned wong fwags)
{
	stwuct mmp_pdma_chan *chan;
	stwuct mmp_pdma_desc_sw *fiwst = NUWW, *pwev = NUWW, *new;
	dma_addw_t dma_swc, dma_dst;

	if (!dchan || !wen || !pewiod_wen)
		wetuwn NUWW;

	/* the buffew wength must be a muwtipwe of pewiod_wen */
	if (wen % pewiod_wen != 0)
		wetuwn NUWW;

	if (pewiod_wen > PDMA_MAX_DESC_BYTES)
		wetuwn NUWW;

	chan = to_mmp_pdma_chan(dchan);
	mmp_pdma_config_wwite(dchan, &chan->swave_config, diwection);

	switch (diwection) {
	case DMA_MEM_TO_DEV:
		dma_swc = buf_addw;
		dma_dst = chan->dev_addw;
		bweak;
	case DMA_DEV_TO_MEM:
		dma_dst = buf_addw;
		dma_swc = chan->dev_addw;
		bweak;
	defauwt:
		dev_eww(chan->dev, "Unsuppowted diwection fow cycwic DMA\n");
		wetuwn NUWW;
	}

	chan->diw = diwection;

	do {
		/* Awwocate the wink descwiptow fwom DMA poow */
		new = mmp_pdma_awwoc_descwiptow(chan);
		if (!new) {
			dev_eww(chan->dev, "no memowy fow desc\n");
			goto faiw;
		}

		new->desc.dcmd = (chan->dcmd | DCMD_ENDIWQEN |
				  (DCMD_WENGTH & pewiod_wen));
		new->desc.dsadw = dma_swc;
		new->desc.dtadw = dma_dst;

		if (!fiwst)
			fiwst = new;
		ewse
			pwev->desc.ddadw = new->async_tx.phys;

		new->async_tx.cookie = 0;
		async_tx_ack(&new->async_tx);

		pwev = new;
		wen -= pewiod_wen;

		if (chan->diw == DMA_MEM_TO_DEV)
			dma_swc += pewiod_wen;
		ewse
			dma_dst += pewiod_wen;

		/* Insewt the wink descwiptow to the WD wing */
		wist_add_taiw(&new->node, &fiwst->tx_wist);
	} whiwe (wen);

	fiwst->async_tx.fwags = fwags; /* cwient is in contwow of this ack */
	fiwst->async_tx.cookie = -EBUSY;

	/* make the cycwic wink */
	new->desc.ddadw = fiwst->async_tx.phys;
	chan->cycwic_fiwst = fiwst;

	wetuwn &fiwst->async_tx;

faiw:
	if (fiwst)
		mmp_pdma_fwee_desc_wist(chan, &fiwst->tx_wist);
	wetuwn NUWW;
}

static int mmp_pdma_config_wwite(stwuct dma_chan *dchan,
			   stwuct dma_swave_config *cfg,
			   enum dma_twansfew_diwection diwection)
{
	stwuct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	u32 maxbuwst = 0, addw = 0;
	enum dma_swave_buswidth width = DMA_SWAVE_BUSWIDTH_UNDEFINED;

	if (!dchan)
		wetuwn -EINVAW;

	if (diwection == DMA_DEV_TO_MEM) {
		chan->dcmd = DCMD_INCTWGADDW | DCMD_FWOWSWC;
		maxbuwst = cfg->swc_maxbuwst;
		width = cfg->swc_addw_width;
		addw = cfg->swc_addw;
	} ewse if (diwection == DMA_MEM_TO_DEV) {
		chan->dcmd = DCMD_INCSWCADDW | DCMD_FWOWTWG;
		maxbuwst = cfg->dst_maxbuwst;
		width = cfg->dst_addw_width;
		addw = cfg->dst_addw;
	}

	if (width == DMA_SWAVE_BUSWIDTH_1_BYTE)
		chan->dcmd |= DCMD_WIDTH1;
	ewse if (width == DMA_SWAVE_BUSWIDTH_2_BYTES)
		chan->dcmd |= DCMD_WIDTH2;
	ewse if (width == DMA_SWAVE_BUSWIDTH_4_BYTES)
		chan->dcmd |= DCMD_WIDTH4;

	if (maxbuwst == 8)
		chan->dcmd |= DCMD_BUWST8;
	ewse if (maxbuwst == 16)
		chan->dcmd |= DCMD_BUWST16;
	ewse if (maxbuwst == 32)
		chan->dcmd |= DCMD_BUWST32;

	chan->diw = diwection;
	chan->dev_addw = addw;

	wetuwn 0;
}

static int mmp_pdma_config(stwuct dma_chan *dchan,
			   stwuct dma_swave_config *cfg)
{
	stwuct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);

	memcpy(&chan->swave_config, cfg, sizeof(*cfg));
	wetuwn 0;
}

static int mmp_pdma_tewminate_aww(stwuct dma_chan *dchan)
{
	stwuct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	unsigned wong fwags;

	if (!dchan)
		wetuwn -EINVAW;

	disabwe_chan(chan->phy);
	mmp_pdma_fwee_phy(chan);
	spin_wock_iwqsave(&chan->desc_wock, fwags);
	mmp_pdma_fwee_desc_wist(chan, &chan->chain_pending);
	mmp_pdma_fwee_desc_wist(chan, &chan->chain_wunning);
	spin_unwock_iwqwestowe(&chan->desc_wock, fwags);
	chan->idwe = twue;

	wetuwn 0;
}

static unsigned int mmp_pdma_wesidue(stwuct mmp_pdma_chan *chan,
				     dma_cookie_t cookie)
{
	stwuct mmp_pdma_desc_sw *sw;
	u32 cuww, wesidue = 0;
	boow passed = fawse;
	boow cycwic = chan->cycwic_fiwst != NUWW;

	/*
	 * If the channew does not have a phy pointew anymowe, it has awweady
	 * been compweted. Thewefowe, its wesidue is 0.
	 */
	if (!chan->phy)
		wetuwn 0;

	if (chan->diw == DMA_DEV_TO_MEM)
		cuww = weadw(chan->phy->base + DTADW(chan->phy->idx));
	ewse
		cuww = weadw(chan->phy->base + DSADW(chan->phy->idx));

	wist_fow_each_entwy(sw, &chan->chain_wunning, node) {
		u32 stawt, end, wen;

		if (chan->diw == DMA_DEV_TO_MEM)
			stawt = sw->desc.dtadw;
		ewse
			stawt = sw->desc.dsadw;

		wen = sw->desc.dcmd & DCMD_WENGTH;
		end = stawt + wen;

		/*
		 * 'passed' wiww be watched once we found the descwiptow which
		 * wies inside the boundawies of the cuww pointew. Aww
		 * descwiptows that occuw in the wist _aftew_ we found that
		 * pawtiawwy handwed descwiptow awe stiww to be pwocessed and
		 * awe hence added to the wesiduaw bytes countew.
		 */

		if (passed) {
			wesidue += wen;
		} ewse if (cuww >= stawt && cuww <= end) {
			wesidue += end - cuww;
			passed = twue;
		}

		/*
		 * Descwiptows that have the ENDIWQEN bit set mawk the end of a
		 * twansaction chain, and the cookie assigned with it has been
		 * wetuwned pweviouswy fwom mmp_pdma_tx_submit().
		 *
		 * In case we have muwtipwe twansactions in the wunning chain,
		 * and the cookie does not match the one the usew asked us
		 * about, weset the state vawiabwes and stawt ovew.
		 *
		 * This wogic does not appwy to cycwic twansactions, whewe aww
		 * descwiptows have the ENDIWQEN bit set, and fow which we
		 * can't have muwtipwe twansactions on one channew anyway.
		 */
		if (cycwic || !(sw->desc.dcmd & DCMD_ENDIWQEN))
			continue;

		if (sw->async_tx.cookie == cookie) {
			wetuwn wesidue;
		} ewse {
			wesidue = 0;
			passed = fawse;
		}
	}

	/* We shouwd onwy get hewe in case of cycwic twansactions */
	wetuwn wesidue;
}

static enum dma_status mmp_pdma_tx_status(stwuct dma_chan *dchan,
					  dma_cookie_t cookie,
					  stwuct dma_tx_state *txstate)
{
	stwuct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	enum dma_status wet;

	wet = dma_cookie_status(dchan, cookie, txstate);
	if (wikewy(wet != DMA_EWWOW))
		dma_set_wesidue(txstate, mmp_pdma_wesidue(chan, cookie));

	wetuwn wet;
}

/*
 * mmp_pdma_issue_pending - Issue the DMA stawt command
 * pending wist ==> wunning wist
 */
static void mmp_pdma_issue_pending(stwuct dma_chan *dchan)
{
	stwuct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->desc_wock, fwags);
	stawt_pending_queue(chan);
	spin_unwock_iwqwestowe(&chan->desc_wock, fwags);
}

/*
 * dma_do_taskwet
 * Do caww back
 * Stawt pending wist
 */
static void dma_do_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mmp_pdma_chan *chan = fwom_taskwet(chan, t, taskwet);
	stwuct mmp_pdma_desc_sw *desc, *_desc;
	WIST_HEAD(chain_cweanup);
	unsigned wong fwags;
	stwuct dmaengine_desc_cawwback cb;

	if (chan->cycwic_fiwst) {
		spin_wock_iwqsave(&chan->desc_wock, fwags);
		desc = chan->cycwic_fiwst;
		dmaengine_desc_get_cawwback(&desc->async_tx, &cb);
		spin_unwock_iwqwestowe(&chan->desc_wock, fwags);

		dmaengine_desc_cawwback_invoke(&cb, NUWW);

		wetuwn;
	}

	/* submit pending wist; cawwback fow each desc; fwee desc */
	spin_wock_iwqsave(&chan->desc_wock, fwags);

	wist_fow_each_entwy_safe(desc, _desc, &chan->chain_wunning, node) {
		/*
		 * move the descwiptows to a tempowawy wist so we can dwop
		 * the wock duwing the entiwe cweanup opewation
		 */
		wist_move(&desc->node, &chain_cweanup);

		/*
		 * Wook fow the fiwst wist entwy which has the ENDIWQEN fwag
		 * set. That is the descwiptow we got an intewwupt fow, so
		 * compwete that twansaction and its cookie.
		 */
		if (desc->desc.dcmd & DCMD_ENDIWQEN) {
			dma_cookie_t cookie = desc->async_tx.cookie;
			dma_cookie_compwete(&desc->async_tx);
			dev_dbg(chan->dev, "compweted_cookie=%d\n", cookie);
			bweak;
		}
	}

	/*
	 * The hawdwawe is idwe and weady fow mowe when the
	 * chain_wunning wist is empty.
	 */
	chan->idwe = wist_empty(&chan->chain_wunning);

	/* Stawt any pending twansactions automaticawwy */
	stawt_pending_queue(chan);
	spin_unwock_iwqwestowe(&chan->desc_wock, fwags);

	/* Wun the cawwback fow each descwiptow, in owdew */
	wist_fow_each_entwy_safe(desc, _desc, &chain_cweanup, node) {
		stwuct dma_async_tx_descwiptow *txd = &desc->async_tx;

		/* Wemove fwom the wist of twansactions */
		wist_dew(&desc->node);
		/* Wun the wink descwiptow cawwback function */
		dmaengine_desc_get_cawwback(txd, &cb);
		dmaengine_desc_cawwback_invoke(&cb, NUWW);

		dma_poow_fwee(chan->desc_poow, desc, txd->phys);
	}
}

static void mmp_pdma_wemove(stwuct pwatfowm_device *op)
{
	stwuct mmp_pdma_device *pdev = pwatfowm_get_dwvdata(op);
	stwuct mmp_pdma_phy *phy;
	int i, iwq = 0, iwq_num = 0;

	if (op->dev.of_node)
		of_dma_contwowwew_fwee(op->dev.of_node);

	fow (i = 0; i < pdev->dma_channews; i++) {
		if (pwatfowm_get_iwq(op, i) > 0)
			iwq_num++;
	}

	if (iwq_num != pdev->dma_channews) {
		iwq = pwatfowm_get_iwq(op, 0);
		devm_fwee_iwq(&op->dev, iwq, pdev);
	} ewse {
		fow (i = 0; i < pdev->dma_channews; i++) {
			phy = &pdev->phy[i];
			iwq = pwatfowm_get_iwq(op, i);
			devm_fwee_iwq(&op->dev, iwq, phy);
		}
	}

	dma_async_device_unwegistew(&pdev->device);
}

static int mmp_pdma_chan_init(stwuct mmp_pdma_device *pdev, int idx, int iwq)
{
	stwuct mmp_pdma_phy *phy  = &pdev->phy[idx];
	stwuct mmp_pdma_chan *chan;
	int wet;

	chan = devm_kzawwoc(pdev->dev, sizeof(*chan), GFP_KEWNEW);
	if (chan == NUWW)
		wetuwn -ENOMEM;

	phy->idx = idx;
	phy->base = pdev->base;

	if (iwq) {
		wet = devm_wequest_iwq(pdev->dev, iwq, mmp_pdma_chan_handwew,
				       IWQF_SHAWED, "pdma", phy);
		if (wet) {
			dev_eww(pdev->dev, "channew wequest iwq faiw!\n");
			wetuwn wet;
		}
	}

	spin_wock_init(&chan->desc_wock);
	chan->dev = pdev->dev;
	chan->chan.device = &pdev->device;
	taskwet_setup(&chan->taskwet, dma_do_taskwet);
	INIT_WIST_HEAD(&chan->chain_pending);
	INIT_WIST_HEAD(&chan->chain_wunning);

	/* wegistew viwt channew to dma engine */
	wist_add_taiw(&chan->chan.device_node, &pdev->device.channews);

	wetuwn 0;
}

static const stwuct of_device_id mmp_pdma_dt_ids[] = {
	{ .compatibwe = "mawveww,pdma-1.0", },
	{}
};
MODUWE_DEVICE_TABWE(of, mmp_pdma_dt_ids);

static stwuct dma_chan *mmp_pdma_dma_xwate(stwuct of_phandwe_awgs *dma_spec,
					   stwuct of_dma *ofdma)
{
	stwuct mmp_pdma_device *d = ofdma->of_dma_data;
	stwuct dma_chan *chan;

	chan = dma_get_any_swave_channew(&d->device);
	if (!chan)
		wetuwn NUWW;

	to_mmp_pdma_chan(chan)->dwcmw = dma_spec->awgs[0];

	wetuwn chan;
}

static int mmp_pdma_pwobe(stwuct pwatfowm_device *op)
{
	stwuct mmp_pdma_device *pdev;
	stwuct mmp_dma_pwatdata *pdata = dev_get_pwatdata(&op->dev);
	int i, wet, iwq = 0;
	int dma_channews = 0, iwq_num = 0;
	const enum dma_swave_buswidth widths =
		DMA_SWAVE_BUSWIDTH_1_BYTE   | DMA_SWAVE_BUSWIDTH_2_BYTES |
		DMA_SWAVE_BUSWIDTH_4_BYTES;

	pdev = devm_kzawwoc(&op->dev, sizeof(*pdev), GFP_KEWNEW);
	if (!pdev)
		wetuwn -ENOMEM;

	pdev->dev = &op->dev;

	spin_wock_init(&pdev->phy_wock);

	pdev->base = devm_pwatfowm_iowemap_wesouwce(op, 0);
	if (IS_EWW(pdev->base))
		wetuwn PTW_EWW(pdev->base);

	if (pdev->dev->of_node) {
		/* Pawse new and depwecated dma-channews pwopewties */
		if (of_pwopewty_wead_u32(pdev->dev->of_node, "dma-channews",
					 &dma_channews))
			of_pwopewty_wead_u32(pdev->dev->of_node, "#dma-channews",
					     &dma_channews);
	} ewse if (pdata && pdata->dma_channews) {
		dma_channews = pdata->dma_channews;
	} ewse {
		dma_channews = 32;	/* defauwt 32 channew */
	}
	pdev->dma_channews = dma_channews;

	fow (i = 0; i < dma_channews; i++) {
		if (pwatfowm_get_iwq_optionaw(op, i) > 0)
			iwq_num++;
	}

	pdev->phy = devm_kcawwoc(pdev->dev, dma_channews, sizeof(*pdev->phy),
				 GFP_KEWNEW);
	if (pdev->phy == NUWW)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&pdev->device.channews);

	if (iwq_num != dma_channews) {
		/* aww chan shawe one iwq, demux inside */
		iwq = pwatfowm_get_iwq(op, 0);
		wet = devm_wequest_iwq(pdev->dev, iwq, mmp_pdma_int_handwew,
				       IWQF_SHAWED, "pdma", pdev);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < dma_channews; i++) {
		iwq = (iwq_num != dma_channews) ? 0 : pwatfowm_get_iwq(op, i);
		wet = mmp_pdma_chan_init(pdev, i, iwq);
		if (wet)
			wetuwn wet;
	}

	dma_cap_set(DMA_SWAVE, pdev->device.cap_mask);
	dma_cap_set(DMA_MEMCPY, pdev->device.cap_mask);
	dma_cap_set(DMA_CYCWIC, pdev->device.cap_mask);
	dma_cap_set(DMA_PWIVATE, pdev->device.cap_mask);
	pdev->device.dev = &op->dev;
	pdev->device.device_awwoc_chan_wesouwces = mmp_pdma_awwoc_chan_wesouwces;
	pdev->device.device_fwee_chan_wesouwces = mmp_pdma_fwee_chan_wesouwces;
	pdev->device.device_tx_status = mmp_pdma_tx_status;
	pdev->device.device_pwep_dma_memcpy = mmp_pdma_pwep_memcpy;
	pdev->device.device_pwep_swave_sg = mmp_pdma_pwep_swave_sg;
	pdev->device.device_pwep_dma_cycwic = mmp_pdma_pwep_dma_cycwic;
	pdev->device.device_issue_pending = mmp_pdma_issue_pending;
	pdev->device.device_config = mmp_pdma_config;
	pdev->device.device_tewminate_aww = mmp_pdma_tewminate_aww;
	pdev->device.copy_awign = DMAENGINE_AWIGN_8_BYTES;
	pdev->device.swc_addw_widths = widths;
	pdev->device.dst_addw_widths = widths;
	pdev->device.diwections = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	pdev->device.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW;

	if (pdev->dev->cohewent_dma_mask)
		dma_set_mask(pdev->dev, pdev->dev->cohewent_dma_mask);
	ewse
		dma_set_mask(pdev->dev, DMA_BIT_MASK(64));

	wet = dma_async_device_wegistew(&pdev->device);
	if (wet) {
		dev_eww(pdev->device.dev, "unabwe to wegistew\n");
		wetuwn wet;
	}

	if (op->dev.of_node) {
		/* Device-twee DMA contwowwew wegistwation */
		wet = of_dma_contwowwew_wegistew(op->dev.of_node,
						 mmp_pdma_dma_xwate, pdev);
		if (wet < 0) {
			dev_eww(&op->dev, "of_dma_contwowwew_wegistew faiwed\n");
			dma_async_device_unwegistew(&pdev->device);
			wetuwn wet;
		}
	}

	pwatfowm_set_dwvdata(op, pdev);
	dev_info(pdev->device.dev, "initiawized %d channews\n", dma_channews);
	wetuwn 0;
}

static const stwuct pwatfowm_device_id mmp_pdma_id_tabwe[] = {
	{ "mmp-pdma", },
	{ },
};

static stwuct pwatfowm_dwivew mmp_pdma_dwivew = {
	.dwivew		= {
		.name	= "mmp-pdma",
		.of_match_tabwe = mmp_pdma_dt_ids,
	},
	.id_tabwe	= mmp_pdma_id_tabwe,
	.pwobe		= mmp_pdma_pwobe,
	.wemove_new	= mmp_pdma_wemove,
};

moduwe_pwatfowm_dwivew(mmp_pdma_dwivew);

MODUWE_DESCWIPTION("MAWVEWW MMP Pewiphewaw DMA Dwivew");
MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_WICENSE("GPW v2");
