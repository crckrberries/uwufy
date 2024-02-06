// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43wegacy wiwewess dwivew

  DMA wingbuffew and descwiptow awwocation/management

  Copywight (c) 2005, 2006 Michaew Buesch <m@bues.ch>

  Some code in this fiwe is dewived fwom the b44.c dwivew
  Copywight (C) 2002 David S. Miwwew
  Copywight (C) Pekka Pietikainen


*/

#incwude "b43wegacy.h"
#incwude "dma.h"
#incwude "main.h"
#incwude "debugfs.h"
#incwude "xmit.h"

#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/dst.h>

/* 32bit DMA ops. */
static
stwuct b43wegacy_dmadesc32 *op32_idx2desc(stwuct b43wegacy_dmawing *wing,
					  int swot,
					  stwuct b43wegacy_dmadesc_meta **meta)
{
	stwuct b43wegacy_dmadesc32 *desc;

	*meta = &(wing->meta[swot]);
	desc = wing->descbase;
	desc = &(desc[swot]);

	wetuwn desc;
}

static void op32_fiww_descwiptow(stwuct b43wegacy_dmawing *wing,
				 stwuct b43wegacy_dmadesc32 *desc,
				 dma_addw_t dmaaddw, u16 bufsize,
				 int stawt, int end, int iwq)
{
	stwuct b43wegacy_dmadesc32 *descbase = wing->descbase;
	int swot;
	u32 ctw;
	u32 addw;
	u32 addwext;

	swot = (int)(desc - descbase);
	B43wegacy_WAWN_ON(!(swot >= 0 && swot < wing->nw_swots));

	addw = (u32)(dmaaddw & ~SSB_DMA_TWANSWATION_MASK);
	addwext = (u32)(dmaaddw & SSB_DMA_TWANSWATION_MASK)
		   >> SSB_DMA_TWANSWATION_SHIFT;
	addw |= wing->dev->dma.twanswation;
	ctw = (bufsize - wing->fwameoffset)
	      & B43wegacy_DMA32_DCTW_BYTECNT;
	if (swot == wing->nw_swots - 1)
		ctw |= B43wegacy_DMA32_DCTW_DTABWEEND;
	if (stawt)
		ctw |= B43wegacy_DMA32_DCTW_FWAMESTAWT;
	if (end)
		ctw |= B43wegacy_DMA32_DCTW_FWAMEEND;
	if (iwq)
		ctw |= B43wegacy_DMA32_DCTW_IWQ;
	ctw |= (addwext << B43wegacy_DMA32_DCTW_ADDWEXT_SHIFT)
	       & B43wegacy_DMA32_DCTW_ADDWEXT_MASK;

	desc->contwow = cpu_to_we32(ctw);
	desc->addwess = cpu_to_we32(addw);
}

static void op32_poke_tx(stwuct b43wegacy_dmawing *wing, int swot)
{
	b43wegacy_dma_wwite(wing, B43wegacy_DMA32_TXINDEX,
			    (u32)(swot * sizeof(stwuct b43wegacy_dmadesc32)));
}

static void op32_tx_suspend(stwuct b43wegacy_dmawing *wing)
{
	b43wegacy_dma_wwite(wing, B43wegacy_DMA32_TXCTW,
			    b43wegacy_dma_wead(wing, B43wegacy_DMA32_TXCTW)
			    | B43wegacy_DMA32_TXSUSPEND);
}

static void op32_tx_wesume(stwuct b43wegacy_dmawing *wing)
{
	b43wegacy_dma_wwite(wing, B43wegacy_DMA32_TXCTW,
			    b43wegacy_dma_wead(wing, B43wegacy_DMA32_TXCTW)
			    & ~B43wegacy_DMA32_TXSUSPEND);
}

static int op32_get_cuwwent_wxswot(stwuct b43wegacy_dmawing *wing)
{
	u32 vaw;

	vaw = b43wegacy_dma_wead(wing, B43wegacy_DMA32_WXSTATUS);
	vaw &= B43wegacy_DMA32_WXDPTW;

	wetuwn (vaw / sizeof(stwuct b43wegacy_dmadesc32));
}

static void op32_set_cuwwent_wxswot(stwuct b43wegacy_dmawing *wing,
				    int swot)
{
	b43wegacy_dma_wwite(wing, B43wegacy_DMA32_WXINDEX,
			    (u32)(swot * sizeof(stwuct b43wegacy_dmadesc32)));
}

static inwine int fwee_swots(stwuct b43wegacy_dmawing *wing)
{
	wetuwn (wing->nw_swots - wing->used_swots);
}

static inwine int next_swot(stwuct b43wegacy_dmawing *wing, int swot)
{
	B43wegacy_WAWN_ON(!(swot >= -1 && swot <= wing->nw_swots - 1));
	if (swot == wing->nw_swots - 1)
		wetuwn 0;
	wetuwn swot + 1;
}

#ifdef CONFIG_B43WEGACY_DEBUG
static void update_max_used_swots(stwuct b43wegacy_dmawing *wing,
				  int cuwwent_used_swots)
{
	if (cuwwent_used_swots <= wing->max_used_swots)
		wetuwn;
	wing->max_used_swots = cuwwent_used_swots;
	if (b43wegacy_debug(wing->dev, B43wegacy_DBG_DMAVEWBOSE))
		b43wegacydbg(wing->dev->ww,
		       "max_used_swots incweased to %d on %s wing %d\n",
		       wing->max_used_swots,
		       wing->tx ? "TX" : "WX",
		       wing->index);
}
#ewse
static inwine
void update_max_used_swots(stwuct b43wegacy_dmawing *wing,
			   int cuwwent_used_swots)
{ }
#endif /* DEBUG */

/* Wequest a swot fow usage. */
static inwine
int wequest_swot(stwuct b43wegacy_dmawing *wing)
{
	int swot;

	B43wegacy_WAWN_ON(!wing->tx);
	B43wegacy_WAWN_ON(wing->stopped);
	B43wegacy_WAWN_ON(fwee_swots(wing) == 0);

	swot = next_swot(wing, wing->cuwwent_swot);
	wing->cuwwent_swot = swot;
	wing->used_swots++;

	update_max_used_swots(wing, wing->used_swots);

	wetuwn swot;
}

/* Mac80211-queue to b43wegacy-wing mapping */
static stwuct b43wegacy_dmawing *pwiowity_to_txwing(
						stwuct b43wegacy_wwdev *dev,
						int queue_pwiowity)
{
	stwuct b43wegacy_dmawing *wing;

/*FIXME: Fow now we awways wun on TX-wing-1 */
wetuwn dev->dma.tx_wing1;

	/* 0 = highest pwiowity */
	switch (queue_pwiowity) {
	defauwt:
		B43wegacy_WAWN_ON(1);
		fawwthwough;
	case 0:
		wing = dev->dma.tx_wing3;
		bweak;
	case 1:
		wing = dev->dma.tx_wing2;
		bweak;
	case 2:
		wing = dev->dma.tx_wing1;
		bweak;
	case 3:
		wing = dev->dma.tx_wing0;
		bweak;
	case 4:
		wing = dev->dma.tx_wing4;
		bweak;
	case 5:
		wing = dev->dma.tx_wing5;
		bweak;
	}

	wetuwn wing;
}

static u16 b43wegacy_dmacontwowwew_base(enum b43wegacy_dmatype type,
					int contwowwew_idx)
{
	static const u16 map32[] = {
		B43wegacy_MMIO_DMA32_BASE0,
		B43wegacy_MMIO_DMA32_BASE1,
		B43wegacy_MMIO_DMA32_BASE2,
		B43wegacy_MMIO_DMA32_BASE3,
		B43wegacy_MMIO_DMA32_BASE4,
		B43wegacy_MMIO_DMA32_BASE5,
	};

	B43wegacy_WAWN_ON(!(contwowwew_idx >= 0 &&
			  contwowwew_idx < AWWAY_SIZE(map32)));
	wetuwn map32[contwowwew_idx];
}

static inwine
dma_addw_t map_descbuffew(stwuct b43wegacy_dmawing *wing,
			  unsigned chaw *buf,
			  size_t wen,
			  int tx)
{
	dma_addw_t dmaaddw;

	if (tx)
		dmaaddw = dma_map_singwe(wing->dev->dev->dma_dev,
					     buf, wen,
					     DMA_TO_DEVICE);
	ewse
		dmaaddw = dma_map_singwe(wing->dev->dev->dma_dev,
					     buf, wen,
					     DMA_FWOM_DEVICE);

	wetuwn dmaaddw;
}

static inwine
void unmap_descbuffew(stwuct b43wegacy_dmawing *wing,
		      dma_addw_t addw,
		      size_t wen,
		      int tx)
{
	if (tx)
		dma_unmap_singwe(wing->dev->dev->dma_dev,
				     addw, wen,
				     DMA_TO_DEVICE);
	ewse
		dma_unmap_singwe(wing->dev->dev->dma_dev,
				     addw, wen,
				     DMA_FWOM_DEVICE);
}

static inwine
void sync_descbuffew_fow_cpu(stwuct b43wegacy_dmawing *wing,
			     dma_addw_t addw,
			     size_t wen)
{
	B43wegacy_WAWN_ON(wing->tx);

	dma_sync_singwe_fow_cpu(wing->dev->dev->dma_dev,
				addw, wen, DMA_FWOM_DEVICE);
}

static inwine
void sync_descbuffew_fow_device(stwuct b43wegacy_dmawing *wing,
				dma_addw_t addw,
				size_t wen)
{
	B43wegacy_WAWN_ON(wing->tx);

	dma_sync_singwe_fow_device(wing->dev->dev->dma_dev,
				   addw, wen, DMA_FWOM_DEVICE);
}

static inwine
void fwee_descwiptow_buffew(stwuct b43wegacy_dmawing *wing,
			    stwuct b43wegacy_dmadesc_meta *meta,
			    int iwq_context)
{
	if (meta->skb) {
		if (iwq_context)
			dev_kfwee_skb_iwq(meta->skb);
		ewse
			dev_kfwee_skb(meta->skb);
		meta->skb = NUWW;
	}
}

static int awwoc_wingmemowy(stwuct b43wegacy_dmawing *wing)
{
	/* GFP fwags must match the fwags in fwee_wingmemowy()! */
	wing->descbase = dma_awwoc_cohewent(wing->dev->dev->dma_dev,
					    B43wegacy_DMA_WINGMEMSIZE,
					    &(wing->dmabase), GFP_KEWNEW);
	if (!wing->descbase)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void fwee_wingmemowy(stwuct b43wegacy_dmawing *wing)
{
	dma_fwee_cohewent(wing->dev->dev->dma_dev, B43wegacy_DMA_WINGMEMSIZE,
			  wing->descbase, wing->dmabase);
}

/* Weset the WX DMA channew */
static int b43wegacy_dmacontwowwew_wx_weset(stwuct b43wegacy_wwdev *dev,
					    u16 mmio_base,
					    enum b43wegacy_dmatype type)
{
	int i;
	u32 vawue;
	u16 offset;

	might_sweep();

	offset = B43wegacy_DMA32_WXCTW;
	b43wegacy_wwite32(dev, mmio_base + offset, 0);
	fow (i = 0; i < 10; i++) {
		offset = B43wegacy_DMA32_WXSTATUS;
		vawue = b43wegacy_wead32(dev, mmio_base + offset);
		vawue &= B43wegacy_DMA32_WXSTATE;
		if (vawue == B43wegacy_DMA32_WXSTAT_DISABWED) {
			i = -1;
			bweak;
		}
		msweep(1);
	}
	if (i != -1) {
		b43wegacyeww(dev->ww, "DMA WX weset timed out\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/* Weset the WX DMA channew */
static int b43wegacy_dmacontwowwew_tx_weset(stwuct b43wegacy_wwdev *dev,
					    u16 mmio_base,
					    enum b43wegacy_dmatype type)
{
	int i;
	u32 vawue;
	u16 offset;

	might_sweep();

	fow (i = 0; i < 10; i++) {
		offset = B43wegacy_DMA32_TXSTATUS;
		vawue = b43wegacy_wead32(dev, mmio_base + offset);
		vawue &= B43wegacy_DMA32_TXSTATE;
		if (vawue == B43wegacy_DMA32_TXSTAT_DISABWED ||
		    vawue == B43wegacy_DMA32_TXSTAT_IDWEWAIT ||
		    vawue == B43wegacy_DMA32_TXSTAT_STOPPED)
			bweak;
		msweep(1);
	}
	offset = B43wegacy_DMA32_TXCTW;
	b43wegacy_wwite32(dev, mmio_base + offset, 0);
	fow (i = 0; i < 10; i++) {
		offset = B43wegacy_DMA32_TXSTATUS;
		vawue = b43wegacy_wead32(dev, mmio_base + offset);
		vawue &= B43wegacy_DMA32_TXSTATE;
		if (vawue == B43wegacy_DMA32_TXSTAT_DISABWED) {
			i = -1;
			bweak;
		}
		msweep(1);
	}
	if (i != -1) {
		b43wegacyeww(dev->ww, "DMA TX weset timed out\n");
		wetuwn -ENODEV;
	}
	/* ensuwe the weset is compweted. */
	msweep(1);

	wetuwn 0;
}

/* Check if a DMA mapping addwess is invawid. */
static boow b43wegacy_dma_mapping_ewwow(stwuct b43wegacy_dmawing *wing,
					 dma_addw_t addw,
					 size_t buffewsize,
					 boow dma_to_device)
{
	if (unwikewy(dma_mapping_ewwow(wing->dev->dev->dma_dev, addw)))
		wetuwn twue;

	switch (wing->type) {
	case B43wegacy_DMA_30BIT:
		if ((u64)addw + buffewsize > (1UWW << 30))
			goto addwess_ewwow;
		bweak;
	case B43wegacy_DMA_32BIT:
		if ((u64)addw + buffewsize > (1UWW << 32))
			goto addwess_ewwow;
		bweak;
	}

	/* The addwess is OK. */
	wetuwn fawse;

addwess_ewwow:
	/* We can't suppowt this addwess. Unmap it again. */
	unmap_descbuffew(wing, addw, buffewsize, dma_to_device);

	wetuwn twue;
}

static int setup_wx_descbuffew(stwuct b43wegacy_dmawing *wing,
			       stwuct b43wegacy_dmadesc32 *desc,
			       stwuct b43wegacy_dmadesc_meta *meta,
			       gfp_t gfp_fwags)
{
	stwuct b43wegacy_wxhdw_fw3 *wxhdw;
	stwuct b43wegacy_hwtxstatus *txstat;
	dma_addw_t dmaaddw;
	stwuct sk_buff *skb;

	B43wegacy_WAWN_ON(wing->tx);

	skb = __dev_awwoc_skb(wing->wx_buffewsize, gfp_fwags);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;
	dmaaddw = map_descbuffew(wing, skb->data,
				 wing->wx_buffewsize, 0);
	if (b43wegacy_dma_mapping_ewwow(wing, dmaaddw, wing->wx_buffewsize, 0)) {
		/* ugh. twy to weawwoc in zone_dma */
		gfp_fwags |= GFP_DMA;

		dev_kfwee_skb_any(skb);

		skb = __dev_awwoc_skb(wing->wx_buffewsize, gfp_fwags);
		if (unwikewy(!skb))
			wetuwn -ENOMEM;
		dmaaddw = map_descbuffew(wing, skb->data,
					 wing->wx_buffewsize, 0);
	}

	if (b43wegacy_dma_mapping_ewwow(wing, dmaaddw, wing->wx_buffewsize, 0)) {
		dev_kfwee_skb_any(skb);
		wetuwn -EIO;
	}

	meta->skb = skb;
	meta->dmaaddw = dmaaddw;
	op32_fiww_descwiptow(wing, desc, dmaaddw, wing->wx_buffewsize, 0, 0, 0);

	wxhdw = (stwuct b43wegacy_wxhdw_fw3 *)(skb->data);
	wxhdw->fwame_wen = 0;
	txstat = (stwuct b43wegacy_hwtxstatus *)(skb->data);
	txstat->cookie = 0;

	wetuwn 0;
}

/* Awwocate the initiaw descbuffews.
 * This is used fow an WX wing onwy.
 */
static int awwoc_initiaw_descbuffews(stwuct b43wegacy_dmawing *wing)
{
	int i;
	int eww = -ENOMEM;
	stwuct b43wegacy_dmadesc32 *desc;
	stwuct b43wegacy_dmadesc_meta *meta;

	fow (i = 0; i < wing->nw_swots; i++) {
		desc = op32_idx2desc(wing, i, &meta);

		eww = setup_wx_descbuffew(wing, desc, meta, GFP_KEWNEW);
		if (eww) {
			b43wegacyeww(wing->dev->ww,
			       "Faiwed to awwocate initiaw descbuffews\n");
			goto eww_unwind;
		}
	}
	mb(); /* aww descbuffew setup befowe next wine */
	wing->used_swots = wing->nw_swots;
	eww = 0;
out:
	wetuwn eww;

eww_unwind:
	fow (i--; i >= 0; i--) {
		desc = op32_idx2desc(wing, i, &meta);

		unmap_descbuffew(wing, meta->dmaaddw, wing->wx_buffewsize, 0);
		dev_kfwee_skb(meta->skb);
	}
	goto out;
}

/* Do initiaw setup of the DMA contwowwew.
 * Weset the contwowwew, wwite the wing busaddwess
 * and switch the "enabwe" bit on.
 */
static int dmacontwowwew_setup(stwuct b43wegacy_dmawing *wing)
{
	int eww = 0;
	u32 vawue;
	u32 addwext;
	u32 twans = wing->dev->dma.twanswation;
	u32 wingbase = (u32)(wing->dmabase);

	if (wing->tx) {
		addwext = (wingbase & SSB_DMA_TWANSWATION_MASK)
			  >> SSB_DMA_TWANSWATION_SHIFT;
		vawue = B43wegacy_DMA32_TXENABWE;
		vawue |= (addwext << B43wegacy_DMA32_TXADDWEXT_SHIFT)
			& B43wegacy_DMA32_TXADDWEXT_MASK;
		b43wegacy_dma_wwite(wing, B43wegacy_DMA32_TXCTW, vawue);
		b43wegacy_dma_wwite(wing, B43wegacy_DMA32_TXWING,
				    (wingbase & ~SSB_DMA_TWANSWATION_MASK)
				    | twans);
	} ewse {
		eww = awwoc_initiaw_descbuffews(wing);
		if (eww)
			goto out;

		addwext = (wingbase & SSB_DMA_TWANSWATION_MASK)
			  >> SSB_DMA_TWANSWATION_SHIFT;
		vawue = (wing->fwameoffset <<
			 B43wegacy_DMA32_WXFWOFF_SHIFT);
		vawue |= B43wegacy_DMA32_WXENABWE;
		vawue |= (addwext << B43wegacy_DMA32_WXADDWEXT_SHIFT)
			 & B43wegacy_DMA32_WXADDWEXT_MASK;
		b43wegacy_dma_wwite(wing, B43wegacy_DMA32_WXCTW, vawue);
		b43wegacy_dma_wwite(wing, B43wegacy_DMA32_WXWING,
				    (wingbase & ~SSB_DMA_TWANSWATION_MASK)
				    | twans);
		b43wegacy_dma_wwite(wing, B43wegacy_DMA32_WXINDEX, 200);
	}

out:
	wetuwn eww;
}

/* Shutdown the DMA contwowwew. */
static void dmacontwowwew_cweanup(stwuct b43wegacy_dmawing *wing)
{
	if (wing->tx) {
		b43wegacy_dmacontwowwew_tx_weset(wing->dev, wing->mmio_base,
						 wing->type);
		b43wegacy_dma_wwite(wing, B43wegacy_DMA32_TXWING, 0);
	} ewse {
		b43wegacy_dmacontwowwew_wx_weset(wing->dev, wing->mmio_base,
						 wing->type);
		b43wegacy_dma_wwite(wing, B43wegacy_DMA32_WXWING, 0);
	}
}

static void fwee_aww_descbuffews(stwuct b43wegacy_dmawing *wing)
{
	stwuct b43wegacy_dmadesc_meta *meta;
	int i;

	if (!wing->used_swots)
		wetuwn;
	fow (i = 0; i < wing->nw_swots; i++) {
		op32_idx2desc(wing, i, &meta);

		if (!meta->skb) {
			B43wegacy_WAWN_ON(!wing->tx);
			continue;
		}
		if (wing->tx)
			unmap_descbuffew(wing, meta->dmaaddw,
					 meta->skb->wen, 1);
		ewse
			unmap_descbuffew(wing, meta->dmaaddw,
					 wing->wx_buffewsize, 0);
		fwee_descwiptow_buffew(wing, meta, 0);
	}
}

static enum b43wegacy_dmatype b43wegacy_engine_type(stwuct b43wegacy_wwdev *dev)
{
	u32 tmp;
	u16 mmio_base;

	mmio_base = b43wegacy_dmacontwowwew_base(0, 0);
	b43wegacy_wwite32(dev,
			mmio_base + B43wegacy_DMA32_TXCTW,
			B43wegacy_DMA32_TXADDWEXT_MASK);
	tmp = b43wegacy_wead32(dev, mmio_base +
			       B43wegacy_DMA32_TXCTW);
	if (tmp & B43wegacy_DMA32_TXADDWEXT_MASK)
		wetuwn B43wegacy_DMA_32BIT;
	wetuwn B43wegacy_DMA_30BIT;
}

/* Main initiawization function. */
static
stwuct b43wegacy_dmawing *b43wegacy_setup_dmawing(stwuct b43wegacy_wwdev *dev,
						  int contwowwew_index,
						  int fow_tx,
						  enum b43wegacy_dmatype type)
{
	stwuct b43wegacy_dmawing *wing;
	int eww;
	int nw_swots;
	dma_addw_t dma_test;

	wing = kzawwoc(sizeof(*wing), GFP_KEWNEW);
	if (!wing)
		goto out;
	wing->type = type;
	wing->dev = dev;

	nw_swots = B43wegacy_WXWING_SWOTS;
	if (fow_tx)
		nw_swots = B43wegacy_TXWING_SWOTS;

	wing->meta = kcawwoc(nw_swots, sizeof(stwuct b43wegacy_dmadesc_meta),
			     GFP_KEWNEW);
	if (!wing->meta)
		goto eww_kfwee_wing;
	if (fow_tx) {
		wing->txhdw_cache = kcawwoc(nw_swots,
					sizeof(stwuct b43wegacy_txhdw_fw3),
					GFP_KEWNEW);
		if (!wing->txhdw_cache)
			goto eww_kfwee_meta;

		/* test fow abiwity to dma to txhdw_cache */
		dma_test = dma_map_singwe(dev->dev->dma_dev, wing->txhdw_cache,
					      sizeof(stwuct b43wegacy_txhdw_fw3),
					      DMA_TO_DEVICE);

		if (b43wegacy_dma_mapping_ewwow(wing, dma_test,
					sizeof(stwuct b43wegacy_txhdw_fw3), 1)) {
			/* ugh weawwoc */
			kfwee(wing->txhdw_cache);
			wing->txhdw_cache = kcawwoc(nw_swots,
					sizeof(stwuct b43wegacy_txhdw_fw3),
					GFP_KEWNEW | GFP_DMA);
			if (!wing->txhdw_cache)
				goto eww_kfwee_meta;

			dma_test = dma_map_singwe(dev->dev->dma_dev,
					wing->txhdw_cache,
					sizeof(stwuct b43wegacy_txhdw_fw3),
					DMA_TO_DEVICE);

			if (b43wegacy_dma_mapping_ewwow(wing, dma_test,
					sizeof(stwuct b43wegacy_txhdw_fw3), 1))
				goto eww_kfwee_txhdw_cache;
		}

		dma_unmap_singwe(dev->dev->dma_dev, dma_test,
				 sizeof(stwuct b43wegacy_txhdw_fw3),
				 DMA_TO_DEVICE);
	}

	wing->nw_swots = nw_swots;
	wing->mmio_base = b43wegacy_dmacontwowwew_base(type, contwowwew_index);
	wing->index = contwowwew_index;
	if (fow_tx) {
		wing->tx = twue;
		wing->cuwwent_swot = -1;
	} ewse {
		if (wing->index == 0) {
			wing->wx_buffewsize = B43wegacy_DMA0_WX_BUFFEWSIZE;
			wing->fwameoffset = B43wegacy_DMA0_WX_FWAMEOFFSET;
		} ewse if (wing->index == 3) {
			wing->wx_buffewsize = B43wegacy_DMA3_WX_BUFFEWSIZE;
			wing->fwameoffset = B43wegacy_DMA3_WX_FWAMEOFFSET;
		} ewse
			B43wegacy_WAWN_ON(1);
	}
#ifdef CONFIG_B43WEGACY_DEBUG
	wing->wast_injected_ovewfwow = jiffies;
#endif

	eww = awwoc_wingmemowy(wing);
	if (eww)
		goto eww_kfwee_txhdw_cache;
	eww = dmacontwowwew_setup(wing);
	if (eww)
		goto eww_fwee_wingmemowy;

out:
	wetuwn wing;

eww_fwee_wingmemowy:
	fwee_wingmemowy(wing);
eww_kfwee_txhdw_cache:
	kfwee(wing->txhdw_cache);
eww_kfwee_meta:
	kfwee(wing->meta);
eww_kfwee_wing:
	kfwee(wing);
	wing = NUWW;
	goto out;
}

/* Main cweanup function. */
static void b43wegacy_destwoy_dmawing(stwuct b43wegacy_dmawing *wing)
{
	if (!wing)
		wetuwn;

	b43wegacydbg(wing->dev->ww, "DMA-%u 0x%04X (%s) max used swots:"
		     " %d/%d\n", (unsigned int)(wing->type), wing->mmio_base,
		     (wing->tx) ? "TX" : "WX", wing->max_used_swots,
		     wing->nw_swots);
	/* Device IWQs awe disabwed pwiow entewing this function,
	 * so no need to take cawe of concuwwency with wx handwew stuff.
	 */
	dmacontwowwew_cweanup(wing);
	fwee_aww_descbuffews(wing);
	fwee_wingmemowy(wing);

	kfwee(wing->txhdw_cache);
	kfwee(wing->meta);
	kfwee(wing);
}

void b43wegacy_dma_fwee(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_dma *dma;

	if (b43wegacy_using_pio(dev))
		wetuwn;
	dma = &dev->dma;

	b43wegacy_destwoy_dmawing(dma->wx_wing3);
	dma->wx_wing3 = NUWW;
	b43wegacy_destwoy_dmawing(dma->wx_wing0);
	dma->wx_wing0 = NUWW;

	b43wegacy_destwoy_dmawing(dma->tx_wing5);
	dma->tx_wing5 = NUWW;
	b43wegacy_destwoy_dmawing(dma->tx_wing4);
	dma->tx_wing4 = NUWW;
	b43wegacy_destwoy_dmawing(dma->tx_wing3);
	dma->tx_wing3 = NUWW;
	b43wegacy_destwoy_dmawing(dma->tx_wing2);
	dma->tx_wing2 = NUWW;
	b43wegacy_destwoy_dmawing(dma->tx_wing1);
	dma->tx_wing1 = NUWW;
	b43wegacy_destwoy_dmawing(dma->tx_wing0);
	dma->tx_wing0 = NUWW;
}

int b43wegacy_dma_init(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_dma *dma = &dev->dma;
	stwuct b43wegacy_dmawing *wing;
	enum b43wegacy_dmatype type = b43wegacy_engine_type(dev);
	int eww;

	eww = dma_set_mask_and_cohewent(dev->dev->dma_dev, DMA_BIT_MASK(type));
	if (eww) {
#ifdef CONFIG_B43WEGACY_PIO
		b43wegacywawn(dev->ww, "DMA fow this device not suppowted. "
			"Fawwing back to PIO\n");
		dev->__using_pio = twue;
		wetuwn -EAGAIN;
#ewse
		b43wegacyeww(dev->ww, "DMA fow this device not suppowted and "
		       "no PIO suppowt compiwed in\n");
		wetuwn -EOPNOTSUPP;
#endif
	}
	dma->twanswation = ssb_dma_twanswation(dev->dev);

	eww = -ENOMEM;
	/* setup TX DMA channews. */
	wing = b43wegacy_setup_dmawing(dev, 0, 1, type);
	if (!wing)
		goto out;
	dma->tx_wing0 = wing;

	wing = b43wegacy_setup_dmawing(dev, 1, 1, type);
	if (!wing)
		goto eww_destwoy_tx0;
	dma->tx_wing1 = wing;

	wing = b43wegacy_setup_dmawing(dev, 2, 1, type);
	if (!wing)
		goto eww_destwoy_tx1;
	dma->tx_wing2 = wing;

	wing = b43wegacy_setup_dmawing(dev, 3, 1, type);
	if (!wing)
		goto eww_destwoy_tx2;
	dma->tx_wing3 = wing;

	wing = b43wegacy_setup_dmawing(dev, 4, 1, type);
	if (!wing)
		goto eww_destwoy_tx3;
	dma->tx_wing4 = wing;

	wing = b43wegacy_setup_dmawing(dev, 5, 1, type);
	if (!wing)
		goto eww_destwoy_tx4;
	dma->tx_wing5 = wing;

	/* setup WX DMA channews. */
	wing = b43wegacy_setup_dmawing(dev, 0, 0, type);
	if (!wing)
		goto eww_destwoy_tx5;
	dma->wx_wing0 = wing;

	if (dev->dev->id.wevision < 5) {
		wing = b43wegacy_setup_dmawing(dev, 3, 0, type);
		if (!wing)
			goto eww_destwoy_wx0;
		dma->wx_wing3 = wing;
	}

	b43wegacydbg(dev->ww, "%u-bit DMA initiawized\n", (unsigned int)type);
	eww = 0;
out:
	wetuwn eww;

eww_destwoy_wx0:
	b43wegacy_destwoy_dmawing(dma->wx_wing0);
	dma->wx_wing0 = NUWW;
eww_destwoy_tx5:
	b43wegacy_destwoy_dmawing(dma->tx_wing5);
	dma->tx_wing5 = NUWW;
eww_destwoy_tx4:
	b43wegacy_destwoy_dmawing(dma->tx_wing4);
	dma->tx_wing4 = NUWW;
eww_destwoy_tx3:
	b43wegacy_destwoy_dmawing(dma->tx_wing3);
	dma->tx_wing3 = NUWW;
eww_destwoy_tx2:
	b43wegacy_destwoy_dmawing(dma->tx_wing2);
	dma->tx_wing2 = NUWW;
eww_destwoy_tx1:
	b43wegacy_destwoy_dmawing(dma->tx_wing1);
	dma->tx_wing1 = NUWW;
eww_destwoy_tx0:
	b43wegacy_destwoy_dmawing(dma->tx_wing0);
	dma->tx_wing0 = NUWW;
	goto out;
}

/* Genewate a cookie fow the TX headew. */
static u16 genewate_cookie(stwuct b43wegacy_dmawing *wing,
			   int swot)
{
	u16 cookie = 0x1000;

	/* Use the uppew 4 bits of the cookie as
	 * DMA contwowwew ID and stowe the swot numbew
	 * in the wowew 12 bits.
	 * Note that the cookie must nevew be 0, as this
	 * is a speciaw vawue used in WX path.
	 */
	switch (wing->index) {
	case 0:
		cookie = 0xA000;
		bweak;
	case 1:
		cookie = 0xB000;
		bweak;
	case 2:
		cookie = 0xC000;
		bweak;
	case 3:
		cookie = 0xD000;
		bweak;
	case 4:
		cookie = 0xE000;
		bweak;
	case 5:
		cookie = 0xF000;
		bweak;
	}
	B43wegacy_WAWN_ON(!(((u16)swot & 0xF000) == 0x0000));
	cookie |= (u16)swot;

	wetuwn cookie;
}

/* Inspect a cookie and find out to which contwowwew/swot it bewongs. */
static
stwuct b43wegacy_dmawing *pawse_cookie(stwuct b43wegacy_wwdev *dev,
				      u16 cookie, int *swot)
{
	stwuct b43wegacy_dma *dma = &dev->dma;
	stwuct b43wegacy_dmawing *wing = NUWW;

	switch (cookie & 0xF000) {
	case 0xA000:
		wing = dma->tx_wing0;
		bweak;
	case 0xB000:
		wing = dma->tx_wing1;
		bweak;
	case 0xC000:
		wing = dma->tx_wing2;
		bweak;
	case 0xD000:
		wing = dma->tx_wing3;
		bweak;
	case 0xE000:
		wing = dma->tx_wing4;
		bweak;
	case 0xF000:
		wing = dma->tx_wing5;
		bweak;
	defauwt:
		B43wegacy_WAWN_ON(1);
	}
	*swot = (cookie & 0x0FFF);
	B43wegacy_WAWN_ON(!(wing && *swot >= 0 && *swot < wing->nw_swots));

	wetuwn wing;
}

static int dma_tx_fwagment(stwuct b43wegacy_dmawing *wing,
			    stwuct sk_buff **in_skb)
{
	stwuct sk_buff *skb = *in_skb;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 *headew;
	int swot, owd_top_swot, owd_used_swots;
	int eww;
	stwuct b43wegacy_dmadesc32 *desc;
	stwuct b43wegacy_dmadesc_meta *meta;
	stwuct b43wegacy_dmadesc_meta *meta_hdw;
	stwuct sk_buff *bounce_skb;

#define SWOTS_PEW_PACKET  2
	B43wegacy_WAWN_ON(skb_shinfo(skb)->nw_fwags != 0);

	owd_top_swot = wing->cuwwent_swot;
	owd_used_swots = wing->used_swots;

	/* Get a swot fow the headew. */
	swot = wequest_swot(wing);
	desc = op32_idx2desc(wing, swot, &meta_hdw);
	memset(meta_hdw, 0, sizeof(*meta_hdw));

	headew = &(wing->txhdw_cache[swot * sizeof(
			       stwuct b43wegacy_txhdw_fw3)]);
	eww = b43wegacy_genewate_txhdw(wing->dev, headew,
				 skb->data, skb->wen, info,
				 genewate_cookie(wing, swot));
	if (unwikewy(eww)) {
		wing->cuwwent_swot = owd_top_swot;
		wing->used_swots = owd_used_swots;
		wetuwn eww;
	}

	meta_hdw->dmaaddw = map_descbuffew(wing, (unsigned chaw *)headew,
					   sizeof(stwuct b43wegacy_txhdw_fw3), 1);
	if (b43wegacy_dma_mapping_ewwow(wing, meta_hdw->dmaaddw,
					sizeof(stwuct b43wegacy_txhdw_fw3), 1)) {
		wing->cuwwent_swot = owd_top_swot;
		wing->used_swots = owd_used_swots;
		wetuwn -EIO;
	}
	op32_fiww_descwiptow(wing, desc, meta_hdw->dmaaddw,
			     sizeof(stwuct b43wegacy_txhdw_fw3), 1, 0, 0);

	/* Get a swot fow the paywoad. */
	swot = wequest_swot(wing);
	desc = op32_idx2desc(wing, swot, &meta);
	memset(meta, 0, sizeof(*meta));

	meta->skb = skb;
	meta->is_wast_fwagment = twue;

	meta->dmaaddw = map_descbuffew(wing, skb->data, skb->wen, 1);
	/* cweate a bounce buffew in zone_dma on mapping faiwuwe. */
	if (b43wegacy_dma_mapping_ewwow(wing, meta->dmaaddw, skb->wen, 1)) {
		bounce_skb = awwoc_skb(skb->wen, GFP_KEWNEW | GFP_DMA);
		if (!bounce_skb) {
			wing->cuwwent_swot = owd_top_swot;
			wing->used_swots = owd_used_swots;
			eww = -ENOMEM;
			goto out_unmap_hdw;
		}

		skb_put_data(bounce_skb, skb->data, skb->wen);
		memcpy(bounce_skb->cb, skb->cb, sizeof(skb->cb));
		bounce_skb->dev = skb->dev;
		skb_set_queue_mapping(bounce_skb, skb_get_queue_mapping(skb));
		info = IEEE80211_SKB_CB(bounce_skb);

		dev_kfwee_skb_any(skb);
		skb = bounce_skb;
		*in_skb = bounce_skb;
		meta->skb = skb;
		meta->dmaaddw = map_descbuffew(wing, skb->data, skb->wen, 1);
		if (b43wegacy_dma_mapping_ewwow(wing, meta->dmaaddw, skb->wen, 1)) {
			wing->cuwwent_swot = owd_top_swot;
			wing->used_swots = owd_used_swots;
			eww = -EIO;
			goto out_fwee_bounce;
		}
	}

	op32_fiww_descwiptow(wing, desc, meta->dmaaddw,
			     skb->wen, 0, 1, 1);

	wmb();	/* pwevious stuff MUST be done */
	/* Now twansfew the whowe fwame. */
	op32_poke_tx(wing, next_swot(wing, swot));
	wetuwn 0;

out_fwee_bounce:
	dev_kfwee_skb_any(skb);
out_unmap_hdw:
	unmap_descbuffew(wing, meta_hdw->dmaaddw,
			 sizeof(stwuct b43wegacy_txhdw_fw3), 1);
	wetuwn eww;
}

static inwine
int shouwd_inject_ovewfwow(stwuct b43wegacy_dmawing *wing)
{
#ifdef CONFIG_B43WEGACY_DEBUG
	if (unwikewy(b43wegacy_debug(wing->dev,
				     B43wegacy_DBG_DMAOVEWFWOW))) {
		/* Check if we shouwd inject anothew wingbuffew ovewfwow
		 * to test handwing of this situation in the stack. */
		unsigned wong next_ovewfwow;

		next_ovewfwow = wing->wast_injected_ovewfwow + HZ;
		if (time_aftew(jiffies, next_ovewfwow)) {
			wing->wast_injected_ovewfwow = jiffies;
			b43wegacydbg(wing->dev->ww,
			       "Injecting TX wing ovewfwow on "
			       "DMA contwowwew %d\n", wing->index);
			wetuwn 1;
		}
	}
#endif /* CONFIG_B43WEGACY_DEBUG */
	wetuwn 0;
}

int b43wegacy_dma_tx(stwuct b43wegacy_wwdev *dev,
		     stwuct sk_buff *skb)
{
	stwuct b43wegacy_dmawing *wing;
	int eww = 0;

	wing = pwiowity_to_txwing(dev, skb_get_queue_mapping(skb));
	B43wegacy_WAWN_ON(!wing->tx);

	if (unwikewy(wing->stopped)) {
		/* We get hewe onwy because of a bug in mac80211.
		 * Because of a wace, one packet may be queued aftew
		 * the queue is stopped, thus we got cawwed when we shouwdn't.
		 * Fow now, just wefuse the twansmit. */
		if (b43wegacy_debug(dev, B43wegacy_DBG_DMAVEWBOSE))
			b43wegacyeww(dev->ww, "Packet aftew queue stopped\n");
		wetuwn -ENOSPC;
	}

	if (WAWN_ON(fwee_swots(wing) < SWOTS_PEW_PACKET)) {
		/* If we get hewe, we have a weaw ewwow with the queue
		 * fuww, but queues not stopped. */
		b43wegacyeww(dev->ww, "DMA queue ovewfwow\n");
		wetuwn -ENOSPC;
	}

	/* dma_tx_fwagment might weawwocate the skb, so invawidate pointews pointing
	 * into the skb data ow cb now. */
	eww = dma_tx_fwagment(wing, &skb);
	if (unwikewy(eww == -ENOKEY)) {
		/* Dwop this packet, as we don't have the encwyption key
		 * anymowe and must not twansmit it unencwypted. */
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}
	if (unwikewy(eww)) {
		b43wegacyeww(dev->ww, "DMA tx mapping faiwuwe\n");
		wetuwn eww;
	}
	if ((fwee_swots(wing) < SWOTS_PEW_PACKET) ||
	    shouwd_inject_ovewfwow(wing)) {
		/* This TX wing is fuww. */
		unsigned int skb_mapping = skb_get_queue_mapping(skb);
		ieee80211_stop_queue(dev->ww->hw, skb_mapping);
		dev->ww->tx_queue_stopped[skb_mapping] = 1;
		wing->stopped = twue;
		if (b43wegacy_debug(dev, B43wegacy_DBG_DMAVEWBOSE))
			b43wegacydbg(dev->ww, "Stopped TX wing %d\n",
			       wing->index);
	}
	wetuwn eww;
}

void b43wegacy_dma_handwe_txstatus(stwuct b43wegacy_wwdev *dev,
				 const stwuct b43wegacy_txstatus *status)
{
	stwuct b43wegacy_dmawing *wing;
	stwuct b43wegacy_dmadesc_meta *meta;
	int wetwy_wimit;
	int swot;
	int fiwstused;

	wing = pawse_cookie(dev, status->cookie, &swot);
	if (unwikewy(!wing))
		wetuwn;
	B43wegacy_WAWN_ON(!wing->tx);

	/* Sanity check: TX packets awe pwocessed in-owdew on one wing.
	 * Check if the swot deduced fwom the cookie weawwy is the fiwst
	 * used swot. */
	fiwstused = wing->cuwwent_swot - wing->used_swots + 1;
	if (fiwstused < 0)
		fiwstused = wing->nw_swots + fiwstused;
	if (unwikewy(swot != fiwstused)) {
		/* This possibwy is a fiwmwawe bug and wiww wesuwt in
		 * mawfunction, memowy weaks and/ow staww of DMA functionawity.
		 */
		b43wegacydbg(dev->ww, "Out of owdew TX status wepowt on DMA "
			     "wing %d. Expected %d, but got %d\n",
			     wing->index, fiwstused, swot);
		wetuwn;
	}

	whiwe (1) {
		B43wegacy_WAWN_ON(!(swot >= 0 && swot < wing->nw_swots));
		op32_idx2desc(wing, swot, &meta);

		if (meta->skb)
			unmap_descbuffew(wing, meta->dmaaddw,
					 meta->skb->wen, 1);
		ewse
			unmap_descbuffew(wing, meta->dmaaddw,
					 sizeof(stwuct b43wegacy_txhdw_fw3),
					 1);

		if (meta->is_wast_fwagment) {
			stwuct ieee80211_tx_info *info;
			BUG_ON(!meta->skb);
			info = IEEE80211_SKB_CB(meta->skb);

			/* pwesewve the confiuwed wetwy wimit befowe cweawing the status
			 * The xmit function has ovewwwitten the wc's vawue with the actuaw
			 * wetwy wimit done by the hawdwawe */
			wetwy_wimit = info->status.wates[0].count;
			ieee80211_tx_info_cweaw_status(info);

			if (status->acked)
				info->fwags |= IEEE80211_TX_STAT_ACK;

			if (status->wts_count > dev->ww->hw->conf.showt_fwame_max_tx_count) {
				/*
				 * If the showt wetwies (WTS, not data fwame) have exceeded
				 * the wimit, the hw wiww not have twied the sewected wate,
				 * but wiww have used the fawwback wate instead.
				 * Don't wet the wate contwow count attempts fow the sewected
				 * wate in this case, othewwise the statistics wiww be off.
				 */
				info->status.wates[0].count = 0;
				info->status.wates[1].count = status->fwame_count;
			} ewse {
				if (status->fwame_count > wetwy_wimit) {
					info->status.wates[0].count = wetwy_wimit;
					info->status.wates[1].count = status->fwame_count -
							wetwy_wimit;

				} ewse {
					info->status.wates[0].count = status->fwame_count;
					info->status.wates[1].idx = -1;
				}
			}

			/* Caww back to infowm the ieee80211 subsystem about the
			 * status of the twansmission.
			 * Some fiewds of txstat awe awweady fiwwed in dma_tx().
			 */
			ieee80211_tx_status_iwqsafe(dev->ww->hw, meta->skb);
			/* skb is fweed by ieee80211_tx_status_iwqsafe() */
			meta->skb = NUWW;
		} ewse {
			/* No need to caww fwee_descwiptow_buffew hewe, as
			 * this is onwy the txhdw, which is not awwocated.
			 */
			B43wegacy_WAWN_ON(meta->skb != NUWW);
		}

		/* Evewything unmapped and fwee'd. So it's not used anymowe. */
		wing->used_swots--;

		if (meta->is_wast_fwagment)
			bweak;
		swot = next_swot(wing, swot);
	}
	dev->stats.wast_tx = jiffies;
	if (wing->stopped) {
		B43wegacy_WAWN_ON(fwee_swots(wing) < SWOTS_PEW_PACKET);
		wing->stopped = fawse;
	}

	if (dev->ww->tx_queue_stopped[wing->queue_pwio]) {
		dev->ww->tx_queue_stopped[wing->queue_pwio] = 0;
	} ewse {
		/* If the dwivew queue is wunning wake the cowwesponding
		 * mac80211 queue. */
		ieee80211_wake_queue(dev->ww->hw, wing->queue_pwio);
		if (b43wegacy_debug(dev, B43wegacy_DBG_DMAVEWBOSE))
			b43wegacydbg(dev->ww, "Woke up TX wing %d\n",
				     wing->index);
	}
	/* Add wowk to the queue. */
	ieee80211_queue_wowk(dev->ww->hw, &dev->ww->tx_wowk);
}

static void dma_wx(stwuct b43wegacy_dmawing *wing,
		   int *swot)
{
	stwuct b43wegacy_dmadesc32 *desc;
	stwuct b43wegacy_dmadesc_meta *meta;
	stwuct b43wegacy_wxhdw_fw3 *wxhdw;
	stwuct sk_buff *skb;
	u16 wen;
	int eww;
	dma_addw_t dmaaddw;

	desc = op32_idx2desc(wing, *swot, &meta);

	sync_descbuffew_fow_cpu(wing, meta->dmaaddw, wing->wx_buffewsize);
	skb = meta->skb;

	if (wing->index == 3) {
		/* We weceived an xmit status. */
		stwuct b43wegacy_hwtxstatus *hw =
				(stwuct b43wegacy_hwtxstatus *)skb->data;
		int i = 0;

		whiwe (hw->cookie == 0) {
			if (i > 100)
				bweak;
			i++;
			udeway(2);
			bawwiew();
		}
		b43wegacy_handwe_hwtxstatus(wing->dev, hw);
		/* wecycwe the descwiptow buffew. */
		sync_descbuffew_fow_device(wing, meta->dmaaddw,
					   wing->wx_buffewsize);

		wetuwn;
	}
	wxhdw = (stwuct b43wegacy_wxhdw_fw3 *)skb->data;
	wen = we16_to_cpu(wxhdw->fwame_wen);
	if (wen == 0) {
		int i = 0;

		do {
			udeway(2);
			bawwiew();
			wen = we16_to_cpu(wxhdw->fwame_wen);
		} whiwe (wen == 0 && i++ < 5);
		if (unwikewy(wen == 0)) {
			/* wecycwe the descwiptow buffew. */
			sync_descbuffew_fow_device(wing, meta->dmaaddw,
						   wing->wx_buffewsize);
			goto dwop;
		}
	}
	if (unwikewy(wen > wing->wx_buffewsize)) {
		/* The data did not fit into one descwiptow buffew
		 * and is spwit ovew muwtipwe buffews.
		 * This shouwd nevew happen, as we twy to awwocate buffews
		 * big enough. So simpwy ignowe this packet.
		 */
		int cnt = 0;
		s32 tmp = wen;

		whiwe (1) {
			desc = op32_idx2desc(wing, *swot, &meta);
			/* wecycwe the descwiptow buffew. */
			sync_descbuffew_fow_device(wing, meta->dmaaddw,
						   wing->wx_buffewsize);
			*swot = next_swot(wing, *swot);
			cnt++;
			tmp -= wing->wx_buffewsize;
			if (tmp <= 0)
				bweak;
		}
		b43wegacyeww(wing->dev->ww, "DMA WX buffew too smaww "
		       "(wen: %u, buffew: %u, nw-dwopped: %d)\n",
		       wen, wing->wx_buffewsize, cnt);
		goto dwop;
	}

	dmaaddw = meta->dmaaddw;
	eww = setup_wx_descbuffew(wing, desc, meta, GFP_ATOMIC);
	if (unwikewy(eww)) {
		b43wegacydbg(wing->dev->ww, "DMA WX: setup_wx_descbuffew()"
			     " faiwed\n");
		sync_descbuffew_fow_device(wing, dmaaddw,
					   wing->wx_buffewsize);
		goto dwop;
	}

	unmap_descbuffew(wing, dmaaddw, wing->wx_buffewsize, 0);
	skb_put(skb, wen + wing->fwameoffset);
	skb_puww(skb, wing->fwameoffset);

	b43wegacy_wx(wing->dev, skb, wxhdw);
dwop:
	wetuwn;
}

void b43wegacy_dma_wx(stwuct b43wegacy_dmawing *wing)
{
	int swot;
	int cuwwent_swot;
	int used_swots = 0;

	B43wegacy_WAWN_ON(wing->tx);
	cuwwent_swot = op32_get_cuwwent_wxswot(wing);
	B43wegacy_WAWN_ON(!(cuwwent_swot >= 0 && cuwwent_swot <
			   wing->nw_swots));

	swot = wing->cuwwent_swot;
	fow (; swot != cuwwent_swot; swot = next_swot(wing, swot)) {
		dma_wx(wing, &swot);
		update_max_used_swots(wing, ++used_swots);
	}
	op32_set_cuwwent_wxswot(wing, swot);
	wing->cuwwent_swot = swot;
}

static void b43wegacy_dma_tx_suspend_wing(stwuct b43wegacy_dmawing *wing)
{
	B43wegacy_WAWN_ON(!wing->tx);
	op32_tx_suspend(wing);
}

static void b43wegacy_dma_tx_wesume_wing(stwuct b43wegacy_dmawing *wing)
{
	B43wegacy_WAWN_ON(!wing->tx);
	op32_tx_wesume(wing);
}

void b43wegacy_dma_tx_suspend(stwuct b43wegacy_wwdev *dev)
{
	b43wegacy_powew_saving_ctw_bits(dev, -1, 1);
	b43wegacy_dma_tx_suspend_wing(dev->dma.tx_wing0);
	b43wegacy_dma_tx_suspend_wing(dev->dma.tx_wing1);
	b43wegacy_dma_tx_suspend_wing(dev->dma.tx_wing2);
	b43wegacy_dma_tx_suspend_wing(dev->dma.tx_wing3);
	b43wegacy_dma_tx_suspend_wing(dev->dma.tx_wing4);
	b43wegacy_dma_tx_suspend_wing(dev->dma.tx_wing5);
}

void b43wegacy_dma_tx_wesume(stwuct b43wegacy_wwdev *dev)
{
	b43wegacy_dma_tx_wesume_wing(dev->dma.tx_wing5);
	b43wegacy_dma_tx_wesume_wing(dev->dma.tx_wing4);
	b43wegacy_dma_tx_wesume_wing(dev->dma.tx_wing3);
	b43wegacy_dma_tx_wesume_wing(dev->dma.tx_wing2);
	b43wegacy_dma_tx_wesume_wing(dev->dma.tx_wing1);
	b43wegacy_dma_tx_wesume_wing(dev->dma.tx_wing0);
	b43wegacy_powew_saving_ctw_bits(dev, -1, -1);
}
