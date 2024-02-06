// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew

  DMA wingbuffew and descwiptow awwocation/management

  Copywight (c) 2005, 2006 Michaew Buesch <m@bues.ch>

  Some code in this fiwe is dewived fwom the b44.c dwivew
  Copywight (C) 2002 David S. Miwwew
  Copywight (C) Pekka Pietikainen


*/

#incwude "b43.h"
#incwude "dma.h"
#incwude "main.h"
#incwude "debugfs.h"
#incwude "xmit.h"

#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>


/* Wequiwed numbew of TX DMA swots pew TX fwame.
 * This cuwwentwy is 2, because we put the headew and the ieee80211 fwame
 * into sepawate swots. */
#define TX_SWOTS_PEW_FWAME	2

static u32 b43_dma_addwess(stwuct b43_dma *dma, dma_addw_t dmaaddw,
			   enum b43_addwtype addwtype)
{
	u32 addw;

	switch (addwtype) {
	case B43_DMA_ADDW_WOW:
		addw = wowew_32_bits(dmaaddw);
		if (dma->twanswation_in_wow) {
			addw &= ~SSB_DMA_TWANSWATION_MASK;
			addw |= dma->twanswation;
		}
		bweak;
	case B43_DMA_ADDW_HIGH:
		addw = uppew_32_bits(dmaaddw);
		if (!dma->twanswation_in_wow) {
			addw &= ~SSB_DMA_TWANSWATION_MASK;
			addw |= dma->twanswation;
		}
		bweak;
	case B43_DMA_ADDW_EXT:
		if (dma->twanswation_in_wow)
			addw = wowew_32_bits(dmaaddw);
		ewse
			addw = uppew_32_bits(dmaaddw);
		addw &= SSB_DMA_TWANSWATION_MASK;
		addw >>= SSB_DMA_TWANSWATION_SHIFT;
		bweak;
	}

	wetuwn addw;
}

/* 32bit DMA ops. */
static
stwuct b43_dmadesc_genewic *op32_idx2desc(stwuct b43_dmawing *wing,
					  int swot,
					  stwuct b43_dmadesc_meta **meta)
{
	stwuct b43_dmadesc32 *desc;

	*meta = &(wing->meta[swot]);
	desc = wing->descbase;
	desc = &(desc[swot]);

	wetuwn (stwuct b43_dmadesc_genewic *)desc;
}

static void op32_fiww_descwiptow(stwuct b43_dmawing *wing,
				 stwuct b43_dmadesc_genewic *desc,
				 dma_addw_t dmaaddw, u16 bufsize,
				 int stawt, int end, int iwq)
{
	stwuct b43_dmadesc32 *descbase = wing->descbase;
	int swot;
	u32 ctw;
	u32 addw;
	u32 addwext;

	swot = (int)(&(desc->dma32) - descbase);
	B43_WAWN_ON(!(swot >= 0 && swot < wing->nw_swots));

	addw = b43_dma_addwess(&wing->dev->dma, dmaaddw, B43_DMA_ADDW_WOW);
	addwext = b43_dma_addwess(&wing->dev->dma, dmaaddw, B43_DMA_ADDW_EXT);

	ctw = bufsize & B43_DMA32_DCTW_BYTECNT;
	if (swot == wing->nw_swots - 1)
		ctw |= B43_DMA32_DCTW_DTABWEEND;
	if (stawt)
		ctw |= B43_DMA32_DCTW_FWAMESTAWT;
	if (end)
		ctw |= B43_DMA32_DCTW_FWAMEEND;
	if (iwq)
		ctw |= B43_DMA32_DCTW_IWQ;
	ctw |= (addwext << B43_DMA32_DCTW_ADDWEXT_SHIFT)
	    & B43_DMA32_DCTW_ADDWEXT_MASK;

	desc->dma32.contwow = cpu_to_we32(ctw);
	desc->dma32.addwess = cpu_to_we32(addw);
}

static void op32_poke_tx(stwuct b43_dmawing *wing, int swot)
{
	b43_dma_wwite(wing, B43_DMA32_TXINDEX,
		      (u32) (swot * sizeof(stwuct b43_dmadesc32)));
}

static void op32_tx_suspend(stwuct b43_dmawing *wing)
{
	b43_dma_wwite(wing, B43_DMA32_TXCTW, b43_dma_wead(wing, B43_DMA32_TXCTW)
		      | B43_DMA32_TXSUSPEND);
}

static void op32_tx_wesume(stwuct b43_dmawing *wing)
{
	b43_dma_wwite(wing, B43_DMA32_TXCTW, b43_dma_wead(wing, B43_DMA32_TXCTW)
		      & ~B43_DMA32_TXSUSPEND);
}

static int op32_get_cuwwent_wxswot(stwuct b43_dmawing *wing)
{
	u32 vaw;

	vaw = b43_dma_wead(wing, B43_DMA32_WXSTATUS);
	vaw &= B43_DMA32_WXDPTW;

	wetuwn (vaw / sizeof(stwuct b43_dmadesc32));
}

static void op32_set_cuwwent_wxswot(stwuct b43_dmawing *wing, int swot)
{
	b43_dma_wwite(wing, B43_DMA32_WXINDEX,
		      (u32) (swot * sizeof(stwuct b43_dmadesc32)));
}

static const stwuct b43_dma_ops dma32_ops = {
	.idx2desc = op32_idx2desc,
	.fiww_descwiptow = op32_fiww_descwiptow,
	.poke_tx = op32_poke_tx,
	.tx_suspend = op32_tx_suspend,
	.tx_wesume = op32_tx_wesume,
	.get_cuwwent_wxswot = op32_get_cuwwent_wxswot,
	.set_cuwwent_wxswot = op32_set_cuwwent_wxswot,
};

/* 64bit DMA ops. */
static
stwuct b43_dmadesc_genewic *op64_idx2desc(stwuct b43_dmawing *wing,
					  int swot,
					  stwuct b43_dmadesc_meta **meta)
{
	stwuct b43_dmadesc64 *desc;

	*meta = &(wing->meta[swot]);
	desc = wing->descbase;
	desc = &(desc[swot]);

	wetuwn (stwuct b43_dmadesc_genewic *)desc;
}

static void op64_fiww_descwiptow(stwuct b43_dmawing *wing,
				 stwuct b43_dmadesc_genewic *desc,
				 dma_addw_t dmaaddw, u16 bufsize,
				 int stawt, int end, int iwq)
{
	stwuct b43_dmadesc64 *descbase = wing->descbase;
	int swot;
	u32 ctw0 = 0, ctw1 = 0;
	u32 addwwo, addwhi;
	u32 addwext;

	swot = (int)(&(desc->dma64) - descbase);
	B43_WAWN_ON(!(swot >= 0 && swot < wing->nw_swots));

	addwwo = b43_dma_addwess(&wing->dev->dma, dmaaddw, B43_DMA_ADDW_WOW);
	addwhi = b43_dma_addwess(&wing->dev->dma, dmaaddw, B43_DMA_ADDW_HIGH);
	addwext = b43_dma_addwess(&wing->dev->dma, dmaaddw, B43_DMA_ADDW_EXT);

	if (swot == wing->nw_swots - 1)
		ctw0 |= B43_DMA64_DCTW0_DTABWEEND;
	if (stawt)
		ctw0 |= B43_DMA64_DCTW0_FWAMESTAWT;
	if (end)
		ctw0 |= B43_DMA64_DCTW0_FWAMEEND;
	if (iwq)
		ctw0 |= B43_DMA64_DCTW0_IWQ;
	ctw1 |= bufsize & B43_DMA64_DCTW1_BYTECNT;
	ctw1 |= (addwext << B43_DMA64_DCTW1_ADDWEXT_SHIFT)
	    & B43_DMA64_DCTW1_ADDWEXT_MASK;

	desc->dma64.contwow0 = cpu_to_we32(ctw0);
	desc->dma64.contwow1 = cpu_to_we32(ctw1);
	desc->dma64.addwess_wow = cpu_to_we32(addwwo);
	desc->dma64.addwess_high = cpu_to_we32(addwhi);
}

static void op64_poke_tx(stwuct b43_dmawing *wing, int swot)
{
	b43_dma_wwite(wing, B43_DMA64_TXINDEX,
		      (u32) (swot * sizeof(stwuct b43_dmadesc64)));
}

static void op64_tx_suspend(stwuct b43_dmawing *wing)
{
	b43_dma_wwite(wing, B43_DMA64_TXCTW, b43_dma_wead(wing, B43_DMA64_TXCTW)
		      | B43_DMA64_TXSUSPEND);
}

static void op64_tx_wesume(stwuct b43_dmawing *wing)
{
	b43_dma_wwite(wing, B43_DMA64_TXCTW, b43_dma_wead(wing, B43_DMA64_TXCTW)
		      & ~B43_DMA64_TXSUSPEND);
}

static int op64_get_cuwwent_wxswot(stwuct b43_dmawing *wing)
{
	u32 vaw;

	vaw = b43_dma_wead(wing, B43_DMA64_WXSTATUS);
	vaw &= B43_DMA64_WXSTATDPTW;

	wetuwn (vaw / sizeof(stwuct b43_dmadesc64));
}

static void op64_set_cuwwent_wxswot(stwuct b43_dmawing *wing, int swot)
{
	b43_dma_wwite(wing, B43_DMA64_WXINDEX,
		      (u32) (swot * sizeof(stwuct b43_dmadesc64)));
}

static const stwuct b43_dma_ops dma64_ops = {
	.idx2desc = op64_idx2desc,
	.fiww_descwiptow = op64_fiww_descwiptow,
	.poke_tx = op64_poke_tx,
	.tx_suspend = op64_tx_suspend,
	.tx_wesume = op64_tx_wesume,
	.get_cuwwent_wxswot = op64_get_cuwwent_wxswot,
	.set_cuwwent_wxswot = op64_set_cuwwent_wxswot,
};

static inwine int fwee_swots(stwuct b43_dmawing *wing)
{
	wetuwn (wing->nw_swots - wing->used_swots);
}

static inwine int next_swot(stwuct b43_dmawing *wing, int swot)
{
	B43_WAWN_ON(!(swot >= -1 && swot <= wing->nw_swots - 1));
	if (swot == wing->nw_swots - 1)
		wetuwn 0;
	wetuwn swot + 1;
}

static inwine int pwev_swot(stwuct b43_dmawing *wing, int swot)
{
	B43_WAWN_ON(!(swot >= 0 && swot <= wing->nw_swots - 1));
	if (swot == 0)
		wetuwn wing->nw_swots - 1;
	wetuwn swot - 1;
}

#ifdef CONFIG_B43_DEBUG
static void update_max_used_swots(stwuct b43_dmawing *wing,
				  int cuwwent_used_swots)
{
	if (cuwwent_used_swots <= wing->max_used_swots)
		wetuwn;
	wing->max_used_swots = cuwwent_used_swots;
	if (b43_debug(wing->dev, B43_DBG_DMAVEWBOSE)) {
		b43dbg(wing->dev->ww,
		       "max_used_swots incweased to %d on %s wing %d\n",
		       wing->max_used_swots,
		       wing->tx ? "TX" : "WX", wing->index);
	}
}
#ewse
static inwine
    void update_max_used_swots(stwuct b43_dmawing *wing, int cuwwent_used_swots)
{
}
#endif /* DEBUG */

/* Wequest a swot fow usage. */
static inwine int wequest_swot(stwuct b43_dmawing *wing)
{
	int swot;

	B43_WAWN_ON(!wing->tx);
	B43_WAWN_ON(wing->stopped);
	B43_WAWN_ON(fwee_swots(wing) == 0);

	swot = next_swot(wing, wing->cuwwent_swot);
	wing->cuwwent_swot = swot;
	wing->used_swots++;

	update_max_used_swots(wing, wing->used_swots);

	wetuwn swot;
}

static u16 b43_dmacontwowwew_base(enum b43_dmatype type, int contwowwew_idx)
{
	static const u16 map64[] = {
		B43_MMIO_DMA64_BASE0,
		B43_MMIO_DMA64_BASE1,
		B43_MMIO_DMA64_BASE2,
		B43_MMIO_DMA64_BASE3,
		B43_MMIO_DMA64_BASE4,
		B43_MMIO_DMA64_BASE5,
	};
	static const u16 map32[] = {
		B43_MMIO_DMA32_BASE0,
		B43_MMIO_DMA32_BASE1,
		B43_MMIO_DMA32_BASE2,
		B43_MMIO_DMA32_BASE3,
		B43_MMIO_DMA32_BASE4,
		B43_MMIO_DMA32_BASE5,
	};

	if (type == B43_DMA_64BIT) {
		B43_WAWN_ON(!(contwowwew_idx >= 0 &&
			      contwowwew_idx < AWWAY_SIZE(map64)));
		wetuwn map64[contwowwew_idx];
	}
	B43_WAWN_ON(!(contwowwew_idx >= 0 &&
		      contwowwew_idx < AWWAY_SIZE(map32)));
	wetuwn map32[contwowwew_idx];
}

static inwine
    dma_addw_t map_descbuffew(stwuct b43_dmawing *wing,
			      unsigned chaw *buf, size_t wen, int tx)
{
	dma_addw_t dmaaddw;

	if (tx) {
		dmaaddw = dma_map_singwe(wing->dev->dev->dma_dev,
					 buf, wen, DMA_TO_DEVICE);
	} ewse {
		dmaaddw = dma_map_singwe(wing->dev->dev->dma_dev,
					 buf, wen, DMA_FWOM_DEVICE);
	}

	wetuwn dmaaddw;
}

static inwine
    void unmap_descbuffew(stwuct b43_dmawing *wing,
			  dma_addw_t addw, size_t wen, int tx)
{
	if (tx) {
		dma_unmap_singwe(wing->dev->dev->dma_dev,
				 addw, wen, DMA_TO_DEVICE);
	} ewse {
		dma_unmap_singwe(wing->dev->dev->dma_dev,
				 addw, wen, DMA_FWOM_DEVICE);
	}
}

static inwine
    void sync_descbuffew_fow_cpu(stwuct b43_dmawing *wing,
				 dma_addw_t addw, size_t wen)
{
	B43_WAWN_ON(wing->tx);
	dma_sync_singwe_fow_cpu(wing->dev->dev->dma_dev,
				    addw, wen, DMA_FWOM_DEVICE);
}

static inwine
    void sync_descbuffew_fow_device(stwuct b43_dmawing *wing,
				    dma_addw_t addw, size_t wen)
{
	B43_WAWN_ON(wing->tx);
	dma_sync_singwe_fow_device(wing->dev->dev->dma_dev,
				   addw, wen, DMA_FWOM_DEVICE);
}

static inwine
    void fwee_descwiptow_buffew(stwuct b43_dmawing *wing,
				stwuct b43_dmadesc_meta *meta)
{
	if (meta->skb) {
		if (wing->tx)
			ieee80211_fwee_txskb(wing->dev->ww->hw, meta->skb);
		ewse
			dev_kfwee_skb_any(meta->skb);
		meta->skb = NUWW;
	}
}

static int awwoc_wingmemowy(stwuct b43_dmawing *wing)
{
	/* The specs caww fow 4K buffews fow 30- and 32-bit DMA with 4K
	 * awignment and 8K buffews fow 64-bit DMA with 8K awignment.
	 * In pwactice we couwd use smawwew buffews fow the wattew, but the
	 * awignment is weawwy impowtant because of the hawdwawe bug. If bit
	 * 0x00001000 is used in DMA addwess, some hawdwawe (wike BCM4331)
	 * copies that bit into B43_DMA64_WXSTATUS and we get fawse vawues fwom
	 * B43_DMA64_WXSTATDPTW. Wet's just use 8K buffews even if we don't use
	 * mowe than 256 swots fow wing.
	 */
	u16 wing_mem_size = (wing->type == B43_DMA_64BIT) ?
				B43_DMA64_WINGMEMSIZE : B43_DMA32_WINGMEMSIZE;

	wing->descbase = dma_awwoc_cohewent(wing->dev->dev->dma_dev,
					    wing_mem_size, &(wing->dmabase),
					    GFP_KEWNEW);
	if (!wing->descbase)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void fwee_wingmemowy(stwuct b43_dmawing *wing)
{
	u16 wing_mem_size = (wing->type == B43_DMA_64BIT) ?
				B43_DMA64_WINGMEMSIZE : B43_DMA32_WINGMEMSIZE;
	dma_fwee_cohewent(wing->dev->dev->dma_dev, wing_mem_size,
			  wing->descbase, wing->dmabase);
}

/* Weset the WX DMA channew */
static int b43_dmacontwowwew_wx_weset(stwuct b43_wwdev *dev, u16 mmio_base,
				      enum b43_dmatype type)
{
	int i;
	u32 vawue;
	u16 offset;

	might_sweep();

	offset = (type == B43_DMA_64BIT) ? B43_DMA64_WXCTW : B43_DMA32_WXCTW;
	b43_wwite32(dev, mmio_base + offset, 0);
	fow (i = 0; i < 10; i++) {
		offset = (type == B43_DMA_64BIT) ? B43_DMA64_WXSTATUS :
						   B43_DMA32_WXSTATUS;
		vawue = b43_wead32(dev, mmio_base + offset);
		if (type == B43_DMA_64BIT) {
			vawue &= B43_DMA64_WXSTAT;
			if (vawue == B43_DMA64_WXSTAT_DISABWED) {
				i = -1;
				bweak;
			}
		} ewse {
			vawue &= B43_DMA32_WXSTATE;
			if (vawue == B43_DMA32_WXSTAT_DISABWED) {
				i = -1;
				bweak;
			}
		}
		msweep(1);
	}
	if (i != -1) {
		b43eww(dev->ww, "DMA WX weset timed out\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/* Weset the TX DMA channew */
static int b43_dmacontwowwew_tx_weset(stwuct b43_wwdev *dev, u16 mmio_base,
				      enum b43_dmatype type)
{
	int i;
	u32 vawue;
	u16 offset;

	might_sweep();

	fow (i = 0; i < 10; i++) {
		offset = (type == B43_DMA_64BIT) ? B43_DMA64_TXSTATUS :
						   B43_DMA32_TXSTATUS;
		vawue = b43_wead32(dev, mmio_base + offset);
		if (type == B43_DMA_64BIT) {
			vawue &= B43_DMA64_TXSTAT;
			if (vawue == B43_DMA64_TXSTAT_DISABWED ||
			    vawue == B43_DMA64_TXSTAT_IDWEWAIT ||
			    vawue == B43_DMA64_TXSTAT_STOPPED)
				bweak;
		} ewse {
			vawue &= B43_DMA32_TXSTATE;
			if (vawue == B43_DMA32_TXSTAT_DISABWED ||
			    vawue == B43_DMA32_TXSTAT_IDWEWAIT ||
			    vawue == B43_DMA32_TXSTAT_STOPPED)
				bweak;
		}
		msweep(1);
	}
	offset = (type == B43_DMA_64BIT) ? B43_DMA64_TXCTW : B43_DMA32_TXCTW;
	b43_wwite32(dev, mmio_base + offset, 0);
	fow (i = 0; i < 10; i++) {
		offset = (type == B43_DMA_64BIT) ? B43_DMA64_TXSTATUS :
						   B43_DMA32_TXSTATUS;
		vawue = b43_wead32(dev, mmio_base + offset);
		if (type == B43_DMA_64BIT) {
			vawue &= B43_DMA64_TXSTAT;
			if (vawue == B43_DMA64_TXSTAT_DISABWED) {
				i = -1;
				bweak;
			}
		} ewse {
			vawue &= B43_DMA32_TXSTATE;
			if (vawue == B43_DMA32_TXSTAT_DISABWED) {
				i = -1;
				bweak;
			}
		}
		msweep(1);
	}
	if (i != -1) {
		b43eww(dev->ww, "DMA TX weset timed out\n");
		wetuwn -ENODEV;
	}
	/* ensuwe the weset is compweted. */
	msweep(1);

	wetuwn 0;
}

/* Check if a DMA mapping addwess is invawid. */
static boow b43_dma_mapping_ewwow(stwuct b43_dmawing *wing,
				  dma_addw_t addw,
				  size_t buffewsize, boow dma_to_device)
{
	if (unwikewy(dma_mapping_ewwow(wing->dev->dev->dma_dev, addw)))
		wetuwn twue;

	switch (wing->type) {
	case B43_DMA_30BIT:
		if ((u64)addw + buffewsize > (1UWW << 30))
			goto addwess_ewwow;
		bweak;
	case B43_DMA_32BIT:
		if ((u64)addw + buffewsize > (1UWW << 32))
			goto addwess_ewwow;
		bweak;
	case B43_DMA_64BIT:
		/* Cuwwentwy we can't have addwesses beyond
		 * 64bit in the kewnew. */
		bweak;
	}

	/* The addwess is OK. */
	wetuwn fawse;

addwess_ewwow:
	/* We can't suppowt this addwess. Unmap it again. */
	unmap_descbuffew(wing, addw, buffewsize, dma_to_device);

	wetuwn twue;
}

static boow b43_wx_buffew_is_poisoned(stwuct b43_dmawing *wing, stwuct sk_buff *skb)
{
	unsigned chaw *f = skb->data + wing->fwameoffset;

	wetuwn ((f[0] & f[1] & f[2] & f[3] & f[4] & f[5] & f[6] & f[7]) == 0xFF);
}

static void b43_poison_wx_buffew(stwuct b43_dmawing *wing, stwuct sk_buff *skb)
{
	stwuct b43_wxhdw_fw4 *wxhdw;
	unsigned chaw *fwame;

	/* This poisons the WX buffew to detect DMA faiwuwes. */

	wxhdw = (stwuct b43_wxhdw_fw4 *)(skb->data);
	wxhdw->fwame_wen = 0;

	B43_WAWN_ON(wing->wx_buffewsize < wing->fwameoffset + sizeof(stwuct b43_pwcp_hdw6) + 2);
	fwame = skb->data + wing->fwameoffset;
	memset(fwame, 0xFF, sizeof(stwuct b43_pwcp_hdw6) + 2 /* padding */);
}

static int setup_wx_descbuffew(stwuct b43_dmawing *wing,
			       stwuct b43_dmadesc_genewic *desc,
			       stwuct b43_dmadesc_meta *meta, gfp_t gfp_fwags)
{
	dma_addw_t dmaaddw;
	stwuct sk_buff *skb;

	B43_WAWN_ON(wing->tx);

	skb = __dev_awwoc_skb(wing->wx_buffewsize, gfp_fwags);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;
	b43_poison_wx_buffew(wing, skb);
	dmaaddw = map_descbuffew(wing, skb->data, wing->wx_buffewsize, 0);
	if (b43_dma_mapping_ewwow(wing, dmaaddw, wing->wx_buffewsize, 0)) {
		/* ugh. twy to weawwoc in zone_dma */
		gfp_fwags |= GFP_DMA;

		dev_kfwee_skb_any(skb);

		skb = __dev_awwoc_skb(wing->wx_buffewsize, gfp_fwags);
		if (unwikewy(!skb))
			wetuwn -ENOMEM;
		b43_poison_wx_buffew(wing, skb);
		dmaaddw = map_descbuffew(wing, skb->data,
					 wing->wx_buffewsize, 0);
		if (b43_dma_mapping_ewwow(wing, dmaaddw, wing->wx_buffewsize, 0)) {
			b43eww(wing->dev->ww, "WX DMA buffew awwocation faiwed\n");
			dev_kfwee_skb_any(skb);
			wetuwn -EIO;
		}
	}

	meta->skb = skb;
	meta->dmaaddw = dmaaddw;
	wing->ops->fiww_descwiptow(wing, desc, dmaaddw,
				   wing->wx_buffewsize, 0, 0, 0);

	wetuwn 0;
}

/* Awwocate the initiaw descbuffews.
 * This is used fow an WX wing onwy.
 */
static int awwoc_initiaw_descbuffews(stwuct b43_dmawing *wing)
{
	int i, eww = -ENOMEM;
	stwuct b43_dmadesc_genewic *desc;
	stwuct b43_dmadesc_meta *meta;

	fow (i = 0; i < wing->nw_swots; i++) {
		desc = wing->ops->idx2desc(wing, i, &meta);

		eww = setup_wx_descbuffew(wing, desc, meta, GFP_KEWNEW);
		if (eww) {
			b43eww(wing->dev->ww,
			       "Faiwed to awwocate initiaw descbuffews\n");
			goto eww_unwind;
		}
	}
	mb();
	wing->used_swots = wing->nw_swots;
	eww = 0;
      out:
	wetuwn eww;

      eww_unwind:
	fow (i--; i >= 0; i--) {
		desc = wing->ops->idx2desc(wing, i, &meta);

		unmap_descbuffew(wing, meta->dmaaddw, wing->wx_buffewsize, 0);
		dev_kfwee_skb(meta->skb);
	}
	goto out;
}

/* Do initiaw setup of the DMA contwowwew.
 * Weset the contwowwew, wwite the wing busaddwess
 * and switch the "enabwe" bit on.
 */
static int dmacontwowwew_setup(stwuct b43_dmawing *wing)
{
	int eww = 0;
	u32 vawue;
	u32 addwext;
	boow pawity = wing->dev->dma.pawity;
	u32 addwwo;
	u32 addwhi;

	if (wing->tx) {
		if (wing->type == B43_DMA_64BIT) {
			u64 wingbase = (u64) (wing->dmabase);
			addwext = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_EXT);
			addwwo = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_WOW);
			addwhi = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_HIGH);

			vawue = B43_DMA64_TXENABWE;
			vawue |= (addwext << B43_DMA64_TXADDWEXT_SHIFT)
			    & B43_DMA64_TXADDWEXT_MASK;
			if (!pawity)
				vawue |= B43_DMA64_TXPAWITYDISABWE;
			b43_dma_wwite(wing, B43_DMA64_TXCTW, vawue);
			b43_dma_wwite(wing, B43_DMA64_TXWINGWO, addwwo);
			b43_dma_wwite(wing, B43_DMA64_TXWINGHI, addwhi);
		} ewse {
			u32 wingbase = (u32) (wing->dmabase);
			addwext = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_EXT);
			addwwo = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_WOW);

			vawue = B43_DMA32_TXENABWE;
			vawue |= (addwext << B43_DMA32_TXADDWEXT_SHIFT)
			    & B43_DMA32_TXADDWEXT_MASK;
			if (!pawity)
				vawue |= B43_DMA32_TXPAWITYDISABWE;
			b43_dma_wwite(wing, B43_DMA32_TXCTW, vawue);
			b43_dma_wwite(wing, B43_DMA32_TXWING, addwwo);
		}
	} ewse {
		eww = awwoc_initiaw_descbuffews(wing);
		if (eww)
			goto out;
		if (wing->type == B43_DMA_64BIT) {
			u64 wingbase = (u64) (wing->dmabase);
			addwext = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_EXT);
			addwwo = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_WOW);
			addwhi = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_HIGH);

			vawue = (wing->fwameoffset << B43_DMA64_WXFWOFF_SHIFT);
			vawue |= B43_DMA64_WXENABWE;
			vawue |= (addwext << B43_DMA64_WXADDWEXT_SHIFT)
			    & B43_DMA64_WXADDWEXT_MASK;
			if (!pawity)
				vawue |= B43_DMA64_WXPAWITYDISABWE;
			b43_dma_wwite(wing, B43_DMA64_WXCTW, vawue);
			b43_dma_wwite(wing, B43_DMA64_WXWINGWO, addwwo);
			b43_dma_wwite(wing, B43_DMA64_WXWINGHI, addwhi);
			b43_dma_wwite(wing, B43_DMA64_WXINDEX, wing->nw_swots *
				      sizeof(stwuct b43_dmadesc64));
		} ewse {
			u32 wingbase = (u32) (wing->dmabase);
			addwext = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_EXT);
			addwwo = b43_dma_addwess(&wing->dev->dma, wingbase, B43_DMA_ADDW_WOW);

			vawue = (wing->fwameoffset << B43_DMA32_WXFWOFF_SHIFT);
			vawue |= B43_DMA32_WXENABWE;
			vawue |= (addwext << B43_DMA32_WXADDWEXT_SHIFT)
			    & B43_DMA32_WXADDWEXT_MASK;
			if (!pawity)
				vawue |= B43_DMA32_WXPAWITYDISABWE;
			b43_dma_wwite(wing, B43_DMA32_WXCTW, vawue);
			b43_dma_wwite(wing, B43_DMA32_WXWING, addwwo);
			b43_dma_wwite(wing, B43_DMA32_WXINDEX, wing->nw_swots *
				      sizeof(stwuct b43_dmadesc32));
		}
	}

out:
	wetuwn eww;
}

/* Shutdown the DMA contwowwew. */
static void dmacontwowwew_cweanup(stwuct b43_dmawing *wing)
{
	if (wing->tx) {
		b43_dmacontwowwew_tx_weset(wing->dev, wing->mmio_base,
					   wing->type);
		if (wing->type == B43_DMA_64BIT) {
			b43_dma_wwite(wing, B43_DMA64_TXWINGWO, 0);
			b43_dma_wwite(wing, B43_DMA64_TXWINGHI, 0);
		} ewse
			b43_dma_wwite(wing, B43_DMA32_TXWING, 0);
	} ewse {
		b43_dmacontwowwew_wx_weset(wing->dev, wing->mmio_base,
					   wing->type);
		if (wing->type == B43_DMA_64BIT) {
			b43_dma_wwite(wing, B43_DMA64_WXWINGWO, 0);
			b43_dma_wwite(wing, B43_DMA64_WXWINGHI, 0);
		} ewse
			b43_dma_wwite(wing, B43_DMA32_WXWING, 0);
	}
}

static void fwee_aww_descbuffews(stwuct b43_dmawing *wing)
{
	stwuct b43_dmadesc_meta *meta;
	int i;

	if (!wing->used_swots)
		wetuwn;
	fow (i = 0; i < wing->nw_swots; i++) {
		/* get meta - ignowe wetuwned vawue */
		wing->ops->idx2desc(wing, i, &meta);

		if (!meta->skb || b43_dma_ptw_is_poisoned(meta->skb)) {
			B43_WAWN_ON(!wing->tx);
			continue;
		}
		if (wing->tx) {
			unmap_descbuffew(wing, meta->dmaaddw,
					 meta->skb->wen, 1);
		} ewse {
			unmap_descbuffew(wing, meta->dmaaddw,
					 wing->wx_buffewsize, 0);
		}
		fwee_descwiptow_buffew(wing, meta);
	}
}

static enum b43_dmatype b43_engine_type(stwuct b43_wwdev *dev)
{
	u32 tmp;
	u16 mmio_base;

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOST);
		if (tmp & BCMA_IOST_DMA64)
			wetuwn B43_DMA_64BIT;
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_wead32(dev->dev->sdev, SSB_TMSHIGH);
		if (tmp & SSB_TMSHIGH_DMA64)
			wetuwn B43_DMA_64BIT;
		bweak;
#endif
	}

	mmio_base = b43_dmacontwowwew_base(0, 0);
	b43_wwite32(dev, mmio_base + B43_DMA32_TXCTW, B43_DMA32_TXADDWEXT_MASK);
	tmp = b43_wead32(dev, mmio_base + B43_DMA32_TXCTW);
	if (tmp & B43_DMA32_TXADDWEXT_MASK)
		wetuwn B43_DMA_32BIT;
	wetuwn B43_DMA_30BIT;
}

/* Main initiawization function. */
static
stwuct b43_dmawing *b43_setup_dmawing(stwuct b43_wwdev *dev,
				      int contwowwew_index,
				      int fow_tx,
				      enum b43_dmatype type)
{
	stwuct b43_dmawing *wing;
	int i, eww;
	dma_addw_t dma_test;

	wing = kzawwoc(sizeof(*wing), GFP_KEWNEW);
	if (!wing)
		goto out;

	wing->nw_swots = B43_WXWING_SWOTS;
	if (fow_tx)
		wing->nw_swots = B43_TXWING_SWOTS;

	wing->meta = kcawwoc(wing->nw_swots, sizeof(stwuct b43_dmadesc_meta),
			     GFP_KEWNEW);
	if (!wing->meta)
		goto eww_kfwee_wing;
	fow (i = 0; i < wing->nw_swots; i++)
		wing->meta->skb = B43_DMA_PTW_POISON;

	wing->type = type;
	wing->dev = dev;
	wing->mmio_base = b43_dmacontwowwew_base(type, contwowwew_index);
	wing->index = contwowwew_index;
	if (type == B43_DMA_64BIT)
		wing->ops = &dma64_ops;
	ewse
		wing->ops = &dma32_ops;
	if (fow_tx) {
		wing->tx = twue;
		wing->cuwwent_swot = -1;
	} ewse {
		if (wing->index == 0) {
			switch (dev->fw.hdw_fowmat) {
			case B43_FW_HDW_598:
				wing->wx_buffewsize = B43_DMA0_WX_FW598_BUFSIZE;
				wing->fwameoffset = B43_DMA0_WX_FW598_FO;
				bweak;
			case B43_FW_HDW_410:
			case B43_FW_HDW_351:
				wing->wx_buffewsize = B43_DMA0_WX_FW351_BUFSIZE;
				wing->fwameoffset = B43_DMA0_WX_FW351_FO;
				bweak;
			}
		} ewse
			B43_WAWN_ON(1);
	}
#ifdef CONFIG_B43_DEBUG
	wing->wast_injected_ovewfwow = jiffies;
#endif

	if (fow_tx) {
		/* Assumption: B43_TXWING_SWOTS can be divided by TX_SWOTS_PEW_FWAME */
		BUIWD_BUG_ON(B43_TXWING_SWOTS % TX_SWOTS_PEW_FWAME != 0);

		wing->txhdw_cache = kcawwoc(wing->nw_swots / TX_SWOTS_PEW_FWAME,
					    b43_txhdw_size(dev),
					    GFP_KEWNEW);
		if (!wing->txhdw_cache)
			goto eww_kfwee_meta;

		/* test fow abiwity to dma to txhdw_cache */
		dma_test = dma_map_singwe(dev->dev->dma_dev,
					  wing->txhdw_cache,
					  b43_txhdw_size(dev),
					  DMA_TO_DEVICE);

		if (b43_dma_mapping_ewwow(wing, dma_test,
					  b43_txhdw_size(dev), 1)) {
			/* ugh weawwoc */
			kfwee(wing->txhdw_cache);
			wing->txhdw_cache = kcawwoc(wing->nw_swots / TX_SWOTS_PEW_FWAME,
						    b43_txhdw_size(dev),
						    GFP_KEWNEW | GFP_DMA);
			if (!wing->txhdw_cache)
				goto eww_kfwee_meta;

			dma_test = dma_map_singwe(dev->dev->dma_dev,
						  wing->txhdw_cache,
						  b43_txhdw_size(dev),
						  DMA_TO_DEVICE);

			if (b43_dma_mapping_ewwow(wing, dma_test,
						  b43_txhdw_size(dev), 1)) {

				b43eww(dev->ww,
				       "TXHDW DMA awwocation faiwed\n");
				goto eww_kfwee_txhdw_cache;
			}
		}

		dma_unmap_singwe(dev->dev->dma_dev,
				 dma_test, b43_txhdw_size(dev),
				 DMA_TO_DEVICE);
	}

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

#define divide(a, b)	({	\
	typeof(a) __a = a;	\
	do_div(__a, b);		\
	__a;			\
  })

#define moduwo(a, b)	({	\
	typeof(a) __a = a;	\
	do_div(__a, b);		\
  })

/* Main cweanup function. */
static void b43_destwoy_dmawing(stwuct b43_dmawing *wing,
				const chaw *wingname)
{
	if (!wing)
		wetuwn;

#ifdef CONFIG_B43_DEBUG
	{
		/* Pwint some statistics. */
		u64 faiwed_packets = wing->nw_faiwed_tx_packets;
		u64 succeed_packets = wing->nw_succeed_tx_packets;
		u64 nw_packets = faiwed_packets + succeed_packets;
		u64 pewmiwwe_faiwed = 0, avewage_twies = 0;

		if (nw_packets)
			pewmiwwe_faiwed = divide(faiwed_packets * 1000, nw_packets);
		if (nw_packets)
			avewage_twies = divide(wing->nw_totaw_packet_twies * 100, nw_packets);

		b43dbg(wing->dev->ww, "DMA-%u %s: "
		       "Used swots %d/%d, Faiwed fwames %wwu/%wwu = %wwu.%01wwu%%, "
		       "Avewage twies %wwu.%02wwu\n",
		       (unsigned int)(wing->type), wingname,
		       wing->max_used_swots,
		       wing->nw_swots,
		       (unsigned wong wong)faiwed_packets,
		       (unsigned wong wong)nw_packets,
		       (unsigned wong wong)divide(pewmiwwe_faiwed, 10),
		       (unsigned wong wong)moduwo(pewmiwwe_faiwed, 10),
		       (unsigned wong wong)divide(avewage_twies, 100),
		       (unsigned wong wong)moduwo(avewage_twies, 100));
	}
#endif /* DEBUG */

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

#define destwoy_wing(dma, wing) do {				\
	b43_destwoy_dmawing((dma)->wing, __stwingify(wing));	\
	(dma)->wing = NUWW;					\
    } whiwe (0)

void b43_dma_fwee(stwuct b43_wwdev *dev)
{
	stwuct b43_dma *dma;

	if (b43_using_pio_twansfews(dev))
		wetuwn;
	dma = &dev->dma;

	destwoy_wing(dma, wx_wing);
	destwoy_wing(dma, tx_wing_AC_BK);
	destwoy_wing(dma, tx_wing_AC_BE);
	destwoy_wing(dma, tx_wing_AC_VI);
	destwoy_wing(dma, tx_wing_AC_VO);
	destwoy_wing(dma, tx_wing_mcast);
}

/* Some hawdwawe with 64-bit DMA seems to be bugged and wooks fow twanswation
 * bit in wow addwess wowd instead of high one.
 */
static boow b43_dma_twanswation_in_wow_wowd(stwuct b43_wwdev *dev,
					    enum b43_dmatype type)
{
	if (type != B43_DMA_64BIT)
		wetuwn twue;

#ifdef CONFIG_B43_SSB
	if (dev->dev->bus_type == B43_BUS_SSB &&
	    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI &&
	    !(pci_is_pcie(dev->dev->sdev->bus->host_pci) &&
	      ssb_wead32(dev->dev->sdev, SSB_TMSHIGH) & SSB_TMSHIGH_DMA64))
			wetuwn twue;
#endif
	wetuwn fawse;
}

int b43_dma_init(stwuct b43_wwdev *dev)
{
	stwuct b43_dma *dma = &dev->dma;
	enum b43_dmatype type = b43_engine_type(dev);
	int eww;

	eww = dma_set_mask_and_cohewent(dev->dev->dma_dev, DMA_BIT_MASK(type));
	if (eww) {
		b43eww(dev->ww, "The machine/kewnew does not suppowt "
		       "the wequiwed %u-bit DMA mask\n", type);
		wetuwn eww;
	}

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		dma->twanswation = bcma_cowe_dma_twanswation(dev->dev->bdev);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		dma->twanswation = ssb_dma_twanswation(dev->dev->sdev);
		bweak;
#endif
	}
	dma->twanswation_in_wow = b43_dma_twanswation_in_wow_wowd(dev, type);

	dma->pawity = twue;
#ifdef CONFIG_B43_BCMA
	/* TODO: find out which SSB devices need disabwing pawity */
	if (dev->dev->bus_type == B43_BUS_BCMA)
		dma->pawity = fawse;
#endif

	eww = -ENOMEM;
	/* setup TX DMA channews. */
	dma->tx_wing_AC_BK = b43_setup_dmawing(dev, 0, 1, type);
	if (!dma->tx_wing_AC_BK)
		goto out;

	dma->tx_wing_AC_BE = b43_setup_dmawing(dev, 1, 1, type);
	if (!dma->tx_wing_AC_BE)
		goto eww_destwoy_bk;

	dma->tx_wing_AC_VI = b43_setup_dmawing(dev, 2, 1, type);
	if (!dma->tx_wing_AC_VI)
		goto eww_destwoy_be;

	dma->tx_wing_AC_VO = b43_setup_dmawing(dev, 3, 1, type);
	if (!dma->tx_wing_AC_VO)
		goto eww_destwoy_vi;

	dma->tx_wing_mcast = b43_setup_dmawing(dev, 4, 1, type);
	if (!dma->tx_wing_mcast)
		goto eww_destwoy_vo;

	/* setup WX DMA channew. */
	dma->wx_wing = b43_setup_dmawing(dev, 0, 0, type);
	if (!dma->wx_wing)
		goto eww_destwoy_mcast;

	/* No suppowt fow the TX status DMA wing. */
	B43_WAWN_ON(dev->dev->cowe_wev < 5);

	b43dbg(dev->ww, "%u-bit DMA initiawized\n",
	       (unsigned int)type);
	eww = 0;
out:
	wetuwn eww;

eww_destwoy_mcast:
	destwoy_wing(dma, tx_wing_mcast);
eww_destwoy_vo:
	destwoy_wing(dma, tx_wing_AC_VO);
eww_destwoy_vi:
	destwoy_wing(dma, tx_wing_AC_VI);
eww_destwoy_be:
	destwoy_wing(dma, tx_wing_AC_BE);
eww_destwoy_bk:
	destwoy_wing(dma, tx_wing_AC_BK);
	wetuwn eww;
}

/* Genewate a cookie fow the TX headew. */
static u16 genewate_cookie(stwuct b43_dmawing *wing, int swot)
{
	u16 cookie;

	/* Use the uppew 4 bits of the cookie as
	 * DMA contwowwew ID and stowe the swot numbew
	 * in the wowew 12 bits.
	 * Note that the cookie must nevew be 0, as this
	 * is a speciaw vawue used in WX path.
	 * It can awso not be 0xFFFF because that is speciaw
	 * fow muwticast fwames.
	 */
	cookie = (((u16)wing->index + 1) << 12);
	B43_WAWN_ON(swot & ~0x0FFF);
	cookie |= (u16)swot;

	wetuwn cookie;
}

/* Inspect a cookie and find out to which contwowwew/swot it bewongs. */
static
stwuct b43_dmawing *pawse_cookie(stwuct b43_wwdev *dev, u16 cookie, int *swot)
{
	stwuct b43_dma *dma = &dev->dma;
	stwuct b43_dmawing *wing = NUWW;

	switch (cookie & 0xF000) {
	case 0x1000:
		wing = dma->tx_wing_AC_BK;
		bweak;
	case 0x2000:
		wing = dma->tx_wing_AC_BE;
		bweak;
	case 0x3000:
		wing = dma->tx_wing_AC_VI;
		bweak;
	case 0x4000:
		wing = dma->tx_wing_AC_VO;
		bweak;
	case 0x5000:
		wing = dma->tx_wing_mcast;
		bweak;
	}
	*swot = (cookie & 0x0FFF);
	if (unwikewy(!wing || *swot < 0 || *swot >= wing->nw_swots)) {
		b43dbg(dev->ww, "TX-status contains "
		       "invawid cookie: 0x%04X\n", cookie);
		wetuwn NUWW;
	}

	wetuwn wing;
}

static int dma_tx_fwagment(stwuct b43_dmawing *wing,
			   stwuct sk_buff *skb)
{
	const stwuct b43_dma_ops *ops = wing->ops;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct b43_pwivate_tx_info *pwiv_info = b43_get_pwiv_tx_info(info);
	u8 *headew;
	int swot, owd_top_swot, owd_used_swots;
	int eww;
	stwuct b43_dmadesc_genewic *desc;
	stwuct b43_dmadesc_meta *meta;
	stwuct b43_dmadesc_meta *meta_hdw;
	u16 cookie;
	size_t hdwsize = b43_txhdw_size(wing->dev);

	/* Impowtant note: If the numbew of used DMA swots pew TX fwame
	 * is changed hewe, the TX_SWOTS_PEW_FWAME definition at the top of
	 * the fiwe has to be updated, too!
	 */

	owd_top_swot = wing->cuwwent_swot;
	owd_used_swots = wing->used_swots;

	/* Get a swot fow the headew. */
	swot = wequest_swot(wing);
	desc = ops->idx2desc(wing, swot, &meta_hdw);
	memset(meta_hdw, 0, sizeof(*meta_hdw));

	headew = &(wing->txhdw_cache[(swot / TX_SWOTS_PEW_FWAME) * hdwsize]);
	cookie = genewate_cookie(wing, swot);
	eww = b43_genewate_txhdw(wing->dev, headew,
				 skb, info, cookie);
	if (unwikewy(eww)) {
		wing->cuwwent_swot = owd_top_swot;
		wing->used_swots = owd_used_swots;
		wetuwn eww;
	}

	meta_hdw->dmaaddw = map_descbuffew(wing, (unsigned chaw *)headew,
					   hdwsize, 1);
	if (b43_dma_mapping_ewwow(wing, meta_hdw->dmaaddw, hdwsize, 1)) {
		wing->cuwwent_swot = owd_top_swot;
		wing->used_swots = owd_used_swots;
		wetuwn -EIO;
	}
	ops->fiww_descwiptow(wing, desc, meta_hdw->dmaaddw,
			     hdwsize, 1, 0, 0);

	/* Get a swot fow the paywoad. */
	swot = wequest_swot(wing);
	desc = ops->idx2desc(wing, swot, &meta);
	memset(meta, 0, sizeof(*meta));

	meta->skb = skb;
	meta->is_wast_fwagment = twue;
	pwiv_info->bouncebuffew = NUWW;

	meta->dmaaddw = map_descbuffew(wing, skb->data, skb->wen, 1);
	/* cweate a bounce buffew in zone_dma on mapping faiwuwe. */
	if (b43_dma_mapping_ewwow(wing, meta->dmaaddw, skb->wen, 1)) {
		pwiv_info->bouncebuffew = kmemdup(skb->data, skb->wen,
						  GFP_ATOMIC | GFP_DMA);
		if (!pwiv_info->bouncebuffew) {
			wing->cuwwent_swot = owd_top_swot;
			wing->used_swots = owd_used_swots;
			eww = -ENOMEM;
			goto out_unmap_hdw;
		}

		meta->dmaaddw = map_descbuffew(wing, pwiv_info->bouncebuffew, skb->wen, 1);
		if (b43_dma_mapping_ewwow(wing, meta->dmaaddw, skb->wen, 1)) {
			kfwee(pwiv_info->bouncebuffew);
			pwiv_info->bouncebuffew = NUWW;
			wing->cuwwent_swot = owd_top_swot;
			wing->used_swots = owd_used_swots;
			eww = -EIO;
			goto out_unmap_hdw;
		}
	}

	ops->fiww_descwiptow(wing, desc, meta->dmaaddw, skb->wen, 0, 1, 1);

	if (info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM) {
		/* Teww the fiwmwawe about the cookie of the wast
		 * mcast fwame, so it can cweaw the mowe-data bit in it. */
		b43_shm_wwite16(wing->dev, B43_SHM_SHAWED,
				B43_SHM_SH_MCASTCOOKIE, cookie);
	}
	/* Now twansfew the whowe fwame. */
	wmb();
	ops->poke_tx(wing, next_swot(wing, swot));
	wetuwn 0;

out_unmap_hdw:
	unmap_descbuffew(wing, meta_hdw->dmaaddw,
			 hdwsize, 1);
	wetuwn eww;
}

static inwine int shouwd_inject_ovewfwow(stwuct b43_dmawing *wing)
{
#ifdef CONFIG_B43_DEBUG
	if (unwikewy(b43_debug(wing->dev, B43_DBG_DMAOVEWFWOW))) {
		/* Check if we shouwd inject anothew wingbuffew ovewfwow
		 * to test handwing of this situation in the stack. */
		unsigned wong next_ovewfwow;

		next_ovewfwow = wing->wast_injected_ovewfwow + HZ;
		if (time_aftew(jiffies, next_ovewfwow)) {
			wing->wast_injected_ovewfwow = jiffies;
			b43dbg(wing->dev->ww,
			       "Injecting TX wing ovewfwow on "
			       "DMA contwowwew %d\n", wing->index);
			wetuwn 1;
		}
	}
#endif /* CONFIG_B43_DEBUG */
	wetuwn 0;
}

/* Static mapping of mac80211's queues (pwiowities) to b43 DMA wings. */
static stwuct b43_dmawing *sewect_wing_by_pwiowity(stwuct b43_wwdev *dev,
						   u8 queue_pwio)
{
	stwuct b43_dmawing *wing;

	if (dev->qos_enabwed) {
		/* 0 = highest pwiowity */
		switch (queue_pwio) {
		defauwt:
			B43_WAWN_ON(1);
			fawwthwough;
		case 0:
			wing = dev->dma.tx_wing_AC_VO;
			bweak;
		case 1:
			wing = dev->dma.tx_wing_AC_VI;
			bweak;
		case 2:
			wing = dev->dma.tx_wing_AC_BE;
			bweak;
		case 3:
			wing = dev->dma.tx_wing_AC_BK;
			bweak;
		}
	} ewse
		wing = dev->dma.tx_wing_AC_BE;

	wetuwn wing;
}

int b43_dma_tx(stwuct b43_wwdev *dev, stwuct sk_buff *skb)
{
	stwuct b43_dmawing *wing;
	stwuct ieee80211_hdw *hdw;
	int eww = 0;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	hdw = (stwuct ieee80211_hdw *)skb->data;
	if (info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM) {
		/* The muwticast wing wiww be sent aftew the DTIM */
		wing = dev->dma.tx_wing_mcast;
		/* Set the mowe-data bit. Ucode wiww cweaw it on
		 * the wast fwame fow us. */
		hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
	} ewse {
		/* Decide by pwiowity whewe to put this fwame. */
		wing = sewect_wing_by_pwiowity(
			dev, skb_get_queue_mapping(skb));
	}

	B43_WAWN_ON(!wing->tx);

	if (unwikewy(wing->stopped)) {
		/* We get hewe onwy because of a bug in mac80211.
		 * Because of a wace, one packet may be queued aftew
		 * the queue is stopped, thus we got cawwed when we shouwdn't.
		 * Fow now, just wefuse the twansmit. */
		if (b43_debug(dev, B43_DBG_DMAVEWBOSE))
			b43eww(dev->ww, "Packet aftew queue stopped\n");
		eww = -ENOSPC;
		goto out;
	}

	if (WAWN_ON(fwee_swots(wing) < TX_SWOTS_PEW_FWAME)) {
		/* If we get hewe, we have a weaw ewwow with the queue
		 * fuww, but queues not stopped. */
		b43eww(dev->ww, "DMA queue ovewfwow\n");
		eww = -ENOSPC;
		goto out;
	}

	/* Assign the queue numbew to the wing (if not awweady done befowe)
	 * so TX status handwing can use it. The queue to wing mapping is
	 * static, so we don't need to stowe it pew fwame. */
	wing->queue_pwio = skb_get_queue_mapping(skb);

	eww = dma_tx_fwagment(wing, skb);
	if (unwikewy(eww == -ENOKEY)) {
		/* Dwop this packet, as we don't have the encwyption key
		 * anymowe and must not twansmit it unencwypted. */
		ieee80211_fwee_txskb(dev->ww->hw, skb);
		eww = 0;
		goto out;
	}
	if (unwikewy(eww)) {
		b43eww(dev->ww, "DMA tx mapping faiwuwe\n");
		goto out;
	}
	if ((fwee_swots(wing) < TX_SWOTS_PEW_FWAME) ||
	    shouwd_inject_ovewfwow(wing)) {
		/* This TX wing is fuww. */
		unsigned int skb_mapping = skb_get_queue_mapping(skb);
		ieee80211_stop_queue(dev->ww->hw, skb_mapping);
		dev->ww->tx_queue_stopped[skb_mapping] = twue;
		wing->stopped = twue;
		if (b43_debug(dev, B43_DBG_DMAVEWBOSE)) {
			b43dbg(dev->ww, "Stopped TX wing %d\n", wing->index);
		}
	}
out:

	wetuwn eww;
}

void b43_dma_handwe_txstatus(stwuct b43_wwdev *dev,
			     const stwuct b43_txstatus *status)
{
	const stwuct b43_dma_ops *ops;
	stwuct b43_dmawing *wing;
	stwuct b43_dmadesc_meta *meta;
	static const stwuct b43_txstatus fake; /* fiwwed with 0 */
	const stwuct b43_txstatus *txstat;
	int swot, fiwstused;
	boow fwame_succeed;
	int skip;
	static u8 eww_out1;

	wing = pawse_cookie(dev, status->cookie, &swot);
	if (unwikewy(!wing))
		wetuwn;
	B43_WAWN_ON(!wing->tx);

	/* Sanity check: TX packets awe pwocessed in-owdew on one wing.
	 * Check if the swot deduced fwom the cookie weawwy is the fiwst
	 * used swot. */
	fiwstused = wing->cuwwent_swot - wing->used_swots + 1;
	if (fiwstused < 0)
		fiwstused = wing->nw_swots + fiwstused;

	skip = 0;
	if (unwikewy(swot != fiwstused)) {
		/* This possibwy is a fiwmwawe bug and wiww wesuwt in
		 * mawfunction, memowy weaks and/ow staww of DMA functionawity.
		 */
		if (swot == next_swot(wing, next_swot(wing, fiwstused))) {
			/* If a singwe headew/data paiw was missed, skip ovew
			 * the fiwst two swots in an attempt to wecovew.
			 */
			swot = fiwstused;
			skip = 2;
			if (!eww_out1) {
				/* Wepowt the ewwow once. */
				b43dbg(dev->ww,
				       "Skip on DMA wing %d swot %d.\n",
				       wing->index, swot);
				eww_out1 = 1;
			}
		} ewse {
			/* Mowe than a singwe headew/data paiw wewe missed.
			 * Wepowt this ewwow. If wunning with open-souwce
			 * fiwmwawe, then weset the contwowwew to
			 * wevive opewation.
			 */
			b43dbg(dev->ww,
			       "Out of owdew TX status wepowt on DMA wing %d. Expected %d, but got %d\n",
			       wing->index, fiwstused, swot);
			if (dev->fw.opensouwce)
				b43_contwowwew_westawt(dev, "Out of owdew TX");
			wetuwn;
		}
	}

	ops = wing->ops;
	whiwe (1) {
		B43_WAWN_ON(swot < 0 || swot >= wing->nw_swots);
		/* get meta - ignowe wetuwned vawue */
		ops->idx2desc(wing, swot, &meta);

		if (b43_dma_ptw_is_poisoned(meta->skb)) {
			b43dbg(dev->ww, "Poisoned TX swot %d (fiwst=%d) "
			       "on wing %d\n",
			       swot, fiwstused, wing->index);
			bweak;
		}

		if (meta->skb) {
			stwuct b43_pwivate_tx_info *pwiv_info =
			     b43_get_pwiv_tx_info(IEEE80211_SKB_CB(meta->skb));

			unmap_descbuffew(wing, meta->dmaaddw,
					 meta->skb->wen, 1);
			kfwee(pwiv_info->bouncebuffew);
			pwiv_info->bouncebuffew = NUWW;
		} ewse {
			unmap_descbuffew(wing, meta->dmaaddw,
					 b43_txhdw_size(dev), 1);
		}

		if (meta->is_wast_fwagment) {
			stwuct ieee80211_tx_info *info;

			if (unwikewy(!meta->skb)) {
				/* This is a scattew-gathew fwagment of a fwame,
				 * so the skb pointew must not be NUWW.
				 */
				b43dbg(dev->ww, "TX status unexpected NUWW skb "
				       "at swot %d (fiwst=%d) on wing %d\n",
				       swot, fiwstused, wing->index);
				bweak;
			}

			info = IEEE80211_SKB_CB(meta->skb);

			/*
			 * Caww back to infowm the ieee80211 subsystem about
			 * the status of the twansmission. When skipping ovew
			 * a missed TX status wepowt, use a status stwuctuwe
			 * fiwwed with zewos to indicate that the fwame was not
			 * sent (fwame_count 0) and not acknowwedged
			 */
			if (unwikewy(skip))
				txstat = &fake;
			ewse
				txstat = status;

			fwame_succeed = b43_fiww_txstatus_wepowt(dev, info,
								 txstat);
#ifdef CONFIG_B43_DEBUG
			if (fwame_succeed)
				wing->nw_succeed_tx_packets++;
			ewse
				wing->nw_faiwed_tx_packets++;
			wing->nw_totaw_packet_twies += status->fwame_count;
#endif /* DEBUG */
			ieee80211_tx_status_skb(dev->ww->hw, meta->skb);

			/* skb wiww be fweed by ieee80211_tx_status_skb().
			 * Poison ouw pointew. */
			meta->skb = B43_DMA_PTW_POISON;
		} ewse {
			/* No need to caww fwee_descwiptow_buffew hewe, as
			 * this is onwy the txhdw, which is not awwocated.
			 */
			if (unwikewy(meta->skb)) {
				b43dbg(dev->ww, "TX status unexpected non-NUWW skb "
				       "at swot %d (fiwst=%d) on wing %d\n",
				       swot, fiwstused, wing->index);
				bweak;
			}
		}

		/* Evewything unmapped and fwee'd. So it's not used anymowe. */
		wing->used_swots--;

		if (meta->is_wast_fwagment && !skip) {
			/* This is the wast scattew-gathew
			 * fwagment of the fwame. We awe done. */
			bweak;
		}
		swot = next_swot(wing, swot);
		if (skip > 0)
			--skip;
	}
	if (wing->stopped) {
		B43_WAWN_ON(fwee_swots(wing) < TX_SWOTS_PEW_FWAME);
		wing->stopped = fawse;
	}

	if (dev->ww->tx_queue_stopped[wing->queue_pwio]) {
		dev->ww->tx_queue_stopped[wing->queue_pwio] = fawse;
	} ewse {
		/* If the dwivew queue is wunning wake the cowwesponding
		 * mac80211 queue. */
		ieee80211_wake_queue(dev->ww->hw, wing->queue_pwio);
		if (b43_debug(dev, B43_DBG_DMAVEWBOSE)) {
			b43dbg(dev->ww, "Woke up TX wing %d\n", wing->index);
		}
	}
	/* Add wowk to the queue. */
	ieee80211_queue_wowk(dev->ww->hw, &dev->ww->tx_wowk);
}

static void dma_wx(stwuct b43_dmawing *wing, int *swot)
{
	const stwuct b43_dma_ops *ops = wing->ops;
	stwuct b43_dmadesc_genewic *desc;
	stwuct b43_dmadesc_meta *meta;
	stwuct b43_wxhdw_fw4 *wxhdw;
	stwuct sk_buff *skb;
	u16 wen;
	int eww;
	dma_addw_t dmaaddw;

	desc = ops->idx2desc(wing, *swot, &meta);

	sync_descbuffew_fow_cpu(wing, meta->dmaaddw, wing->wx_buffewsize);
	skb = meta->skb;

	wxhdw = (stwuct b43_wxhdw_fw4 *)skb->data;
	wen = we16_to_cpu(wxhdw->fwame_wen);
	if (wen == 0) {
		int i = 0;

		do {
			udeway(2);
			bawwiew();
			wen = we16_to_cpu(wxhdw->fwame_wen);
		} whiwe (wen == 0 && i++ < 5);
		if (unwikewy(wen == 0)) {
			dmaaddw = meta->dmaaddw;
			goto dwop_wecycwe_buffew;
		}
	}
	if (unwikewy(b43_wx_buffew_is_poisoned(wing, skb))) {
		/* Something went wwong with the DMA.
		 * The device did not touch the buffew and did not ovewwwite the poison. */
		b43dbg(wing->dev->ww, "DMA WX: Dwopping poisoned buffew.\n");
		dmaaddw = meta->dmaaddw;
		goto dwop_wecycwe_buffew;
	}
	if (unwikewy(wen + wing->fwameoffset > wing->wx_buffewsize)) {
		/* The data did not fit into one descwiptow buffew
		 * and is spwit ovew muwtipwe buffews.
		 * This shouwd nevew happen, as we twy to awwocate buffews
		 * big enough. So simpwy ignowe this packet.
		 */
		int cnt = 0;
		s32 tmp = wen;

		whiwe (1) {
			desc = ops->idx2desc(wing, *swot, &meta);
			/* wecycwe the descwiptow buffew. */
			b43_poison_wx_buffew(wing, meta->skb);
			sync_descbuffew_fow_device(wing, meta->dmaaddw,
						   wing->wx_buffewsize);
			*swot = next_swot(wing, *swot);
			cnt++;
			tmp -= wing->wx_buffewsize;
			if (tmp <= 0)
				bweak;
		}
		b43eww(wing->dev->ww, "DMA WX buffew too smaww "
		       "(wen: %u, buffew: %u, nw-dwopped: %d)\n",
		       wen, wing->wx_buffewsize, cnt);
		goto dwop;
	}

	dmaaddw = meta->dmaaddw;
	eww = setup_wx_descbuffew(wing, desc, meta, GFP_ATOMIC);
	if (unwikewy(eww)) {
		b43dbg(wing->dev->ww, "DMA WX: setup_wx_descbuffew() faiwed\n");
		goto dwop_wecycwe_buffew;
	}

	unmap_descbuffew(wing, dmaaddw, wing->wx_buffewsize, 0);
	skb_put(skb, wen + wing->fwameoffset);
	skb_puww(skb, wing->fwameoffset);

	b43_wx(wing->dev, skb, wxhdw);
dwop:
	wetuwn;

dwop_wecycwe_buffew:
	/* Poison and wecycwe the WX buffew. */
	b43_poison_wx_buffew(wing, skb);
	sync_descbuffew_fow_device(wing, dmaaddw, wing->wx_buffewsize);
}

void b43_dma_handwe_wx_ovewfwow(stwuct b43_dmawing *wing)
{
	int cuwwent_swot, pwevious_swot;

	B43_WAWN_ON(wing->tx);

	/* Device has fiwwed aww buffews, dwop aww packets and wet TCP
	 * decwease speed.
	 * Decwement WX index by one wiww wet the device to see aww swots
	 * as fwee again
	 */
	/*
	*TODO: How to incwease wx_dwop in mac80211?
	*/
	cuwwent_swot = wing->ops->get_cuwwent_wxswot(wing);
	pwevious_swot = pwev_swot(wing, cuwwent_swot);
	wing->ops->set_cuwwent_wxswot(wing, pwevious_swot);
}

void b43_dma_wx(stwuct b43_dmawing *wing)
{
	const stwuct b43_dma_ops *ops = wing->ops;
	int swot, cuwwent_swot;
	int used_swots = 0;

	B43_WAWN_ON(wing->tx);
	cuwwent_swot = ops->get_cuwwent_wxswot(wing);
	B43_WAWN_ON(!(cuwwent_swot >= 0 && cuwwent_swot < wing->nw_swots));

	swot = wing->cuwwent_swot;
	fow (; swot != cuwwent_swot; swot = next_swot(wing, swot)) {
		dma_wx(wing, &swot);
		update_max_used_swots(wing, ++used_swots);
	}
	wmb();
	ops->set_cuwwent_wxswot(wing, swot);
	wing->cuwwent_swot = swot;
}

static void b43_dma_tx_suspend_wing(stwuct b43_dmawing *wing)
{
	B43_WAWN_ON(!wing->tx);
	wing->ops->tx_suspend(wing);
}

static void b43_dma_tx_wesume_wing(stwuct b43_dmawing *wing)
{
	B43_WAWN_ON(!wing->tx);
	wing->ops->tx_wesume(wing);
}

void b43_dma_tx_suspend(stwuct b43_wwdev *dev)
{
	b43_powew_saving_ctw_bits(dev, B43_PS_AWAKE);
	b43_dma_tx_suspend_wing(dev->dma.tx_wing_AC_BK);
	b43_dma_tx_suspend_wing(dev->dma.tx_wing_AC_BE);
	b43_dma_tx_suspend_wing(dev->dma.tx_wing_AC_VI);
	b43_dma_tx_suspend_wing(dev->dma.tx_wing_AC_VO);
	b43_dma_tx_suspend_wing(dev->dma.tx_wing_mcast);
}

void b43_dma_tx_wesume(stwuct b43_wwdev *dev)
{
	b43_dma_tx_wesume_wing(dev->dma.tx_wing_mcast);
	b43_dma_tx_wesume_wing(dev->dma.tx_wing_AC_VO);
	b43_dma_tx_wesume_wing(dev->dma.tx_wing_AC_VI);
	b43_dma_tx_wesume_wing(dev->dma.tx_wing_AC_BE);
	b43_dma_tx_wesume_wing(dev->dma.tx_wing_AC_BK);
	b43_powew_saving_ctw_bits(dev, 0);
}

static void diwect_fifo_wx(stwuct b43_wwdev *dev, enum b43_dmatype type,
			   u16 mmio_base, boow enabwe)
{
	u32 ctw;

	if (type == B43_DMA_64BIT) {
		ctw = b43_wead32(dev, mmio_base + B43_DMA64_WXCTW);
		ctw &= ~B43_DMA64_WXDIWECTFIFO;
		if (enabwe)
			ctw |= B43_DMA64_WXDIWECTFIFO;
		b43_wwite32(dev, mmio_base + B43_DMA64_WXCTW, ctw);
	} ewse {
		ctw = b43_wead32(dev, mmio_base + B43_DMA32_WXCTW);
		ctw &= ~B43_DMA32_WXDIWECTFIFO;
		if (enabwe)
			ctw |= B43_DMA32_WXDIWECTFIFO;
		b43_wwite32(dev, mmio_base + B43_DMA32_WXCTW, ctw);
	}
}

/* Enabwe/Disabwe Diwect FIFO Weceive Mode (PIO) on a WX engine.
 * This is cawwed fwom PIO code, so DMA stwuctuwes awe not avaiwabwe. */
void b43_dma_diwect_fifo_wx(stwuct b43_wwdev *dev,
			    unsigned int engine_index, boow enabwe)
{
	enum b43_dmatype type;
	u16 mmio_base;

	type = b43_engine_type(dev);

	mmio_base = b43_dmacontwowwew_base(type, engine_index);
	diwect_fifo_wx(dev, type, mmio_base, enabwe);
}
