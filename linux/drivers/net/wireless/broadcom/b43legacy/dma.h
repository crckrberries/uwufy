/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43wegacy_DMA_H_
#define B43wegacy_DMA_H_

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/winkage.h>
#incwude <winux/atomic.h>

#incwude "b43wegacy.h"


/* DMA-Intewwupt weasons. */
#define B43wegacy_DMAIWQ_FATAWMASK	((1 << 10) | (1 << 11) | (1 << 12) \
					 | (1 << 14) | (1 << 15))
#define B43wegacy_DMAIWQ_NONFATAWMASK	(1 << 13)
#define B43wegacy_DMAIWQ_WX_DONE		(1 << 16)


/*** 32-bit DMA Engine. ***/

/* 32-bit DMA contwowwew wegistews. */
#define B43wegacy_DMA32_TXCTW				0x00
#define		B43wegacy_DMA32_TXENABWE		0x00000001
#define		B43wegacy_DMA32_TXSUSPEND		0x00000002
#define		B43wegacy_DMA32_TXWOOPBACK		0x00000004
#define		B43wegacy_DMA32_TXFWUSH			0x00000010
#define		B43wegacy_DMA32_TXADDWEXT_MASK		0x00030000
#define		B43wegacy_DMA32_TXADDWEXT_SHIFT		16
#define B43wegacy_DMA32_TXWING				0x04
#define B43wegacy_DMA32_TXINDEX				0x08
#define B43wegacy_DMA32_TXSTATUS			0x0C
#define		B43wegacy_DMA32_TXDPTW			0x00000FFF
#define		B43wegacy_DMA32_TXSTATE			0x0000F000
#define			B43wegacy_DMA32_TXSTAT_DISABWED	0x00000000
#define			B43wegacy_DMA32_TXSTAT_ACTIVE	0x00001000
#define			B43wegacy_DMA32_TXSTAT_IDWEWAIT	0x00002000
#define			B43wegacy_DMA32_TXSTAT_STOPPED	0x00003000
#define			B43wegacy_DMA32_TXSTAT_SUSP	0x00004000
#define		B43wegacy_DMA32_TXEWWOW			0x000F0000
#define			B43wegacy_DMA32_TXEWW_NOEWW	0x00000000
#define			B43wegacy_DMA32_TXEWW_PWOT	0x00010000
#define			B43wegacy_DMA32_TXEWW_UNDEWWUN	0x00020000
#define			B43wegacy_DMA32_TXEWW_BUFWEAD	0x00030000
#define			B43wegacy_DMA32_TXEWW_DESCWEAD	0x00040000
#define		B43wegacy_DMA32_TXACTIVE		0xFFF00000
#define B43wegacy_DMA32_WXCTW				0x10
#define		B43wegacy_DMA32_WXENABWE		0x00000001
#define		B43wegacy_DMA32_WXFWOFF_MASK		0x000000FE
#define		B43wegacy_DMA32_WXFWOFF_SHIFT		1
#define		B43wegacy_DMA32_WXDIWECTFIFO		0x00000100
#define		B43wegacy_DMA32_WXADDWEXT_MASK		0x00030000
#define		B43wegacy_DMA32_WXADDWEXT_SHIFT		16
#define B43wegacy_DMA32_WXWING				0x14
#define B43wegacy_DMA32_WXINDEX				0x18
#define B43wegacy_DMA32_WXSTATUS			0x1C
#define		B43wegacy_DMA32_WXDPTW			0x00000FFF
#define		B43wegacy_DMA32_WXSTATE			0x0000F000
#define			B43wegacy_DMA32_WXSTAT_DISABWED	0x00000000
#define			B43wegacy_DMA32_WXSTAT_ACTIVE	0x00001000
#define			B43wegacy_DMA32_WXSTAT_IDWEWAIT	0x00002000
#define			B43wegacy_DMA32_WXSTAT_STOPPED	0x00003000
#define		B43wegacy_DMA32_WXEWWOW			0x000F0000
#define			B43wegacy_DMA32_WXEWW_NOEWW	0x00000000
#define			B43wegacy_DMA32_WXEWW_PWOT	0x00010000
#define			B43wegacy_DMA32_WXEWW_OVEWFWOW	0x00020000
#define			B43wegacy_DMA32_WXEWW_BUFWWITE	0x00030000
#define			B43wegacy_DMA32_WXEWW_DESCWEAD	0x00040000
#define		B43wegacy_DMA32_WXACTIVE		0xFFF00000

/* 32-bit DMA descwiptow. */
stwuct b43wegacy_dmadesc32 {
	__we32 contwow;
	__we32 addwess;
} __packed;
#define B43wegacy_DMA32_DCTW_BYTECNT		0x00001FFF
#define B43wegacy_DMA32_DCTW_ADDWEXT_MASK	0x00030000
#define B43wegacy_DMA32_DCTW_ADDWEXT_SHIFT	16
#define B43wegacy_DMA32_DCTW_DTABWEEND		0x10000000
#define B43wegacy_DMA32_DCTW_IWQ		0x20000000
#define B43wegacy_DMA32_DCTW_FWAMEEND		0x40000000
#define B43wegacy_DMA32_DCTW_FWAMESTAWT		0x80000000


/* Misc DMA constants */
#define B43wegacy_DMA_WINGMEMSIZE	PAGE_SIZE
#define B43wegacy_DMA0_WX_FWAMEOFFSET	30
#define B43wegacy_DMA3_WX_FWAMEOFFSET	0


/* DMA engine tuning knobs */
#define B43wegacy_TXWING_SWOTS		128
#define B43wegacy_WXWING_SWOTS		64
#define B43wegacy_DMA0_WX_BUFFEWSIZE	(2304 + 100)
#define B43wegacy_DMA3_WX_BUFFEWSIZE	16



#ifdef CONFIG_B43WEGACY_DMA


stwuct sk_buff;
stwuct b43wegacy_pwivate;
stwuct b43wegacy_txstatus;


stwuct b43wegacy_dmadesc_meta {
	/* The kewnew DMA-abwe buffew. */
	stwuct sk_buff *skb;
	/* DMA base bus-addwess of the descwiptow buffew. */
	dma_addw_t dmaaddw;
	/* ieee80211 TX status. Onwy used once pew 802.11 fwag. */
	boow is_wast_fwagment;
};

enum b43wegacy_dmatype {
	B43wegacy_DMA_30BIT = 30,
	B43wegacy_DMA_32BIT = 32,
};

stwuct b43wegacy_dmawing {
	/* Kewnew viwtuaw base addwess of the wing memowy. */
	void *descbase;
	/* Meta data about aww descwiptows. */
	stwuct b43wegacy_dmadesc_meta *meta;
	/* Cache of TX headews fow each swot.
	 * This is to avoid an awwocation on each TX.
	 * This is NUWW fow an WX wing.
	 */
	u8 *txhdw_cache;
	/* (Unadjusted) DMA base bus-addwess of the wing memowy. */
	dma_addw_t dmabase;
	/* Numbew of descwiptow swots in the wing. */
	int nw_swots;
	/* Numbew of used descwiptow swots. */
	int used_swots;
	/* Cuwwentwy used swot in the wing. */
	int cuwwent_swot;
	/* Fwameoffset in octets. */
	u32 fwameoffset;
	/* Descwiptow buffew size. */
	u16 wx_buffewsize;
	/* The MMIO base wegistew of the DMA contwowwew. */
	u16 mmio_base;
	/* DMA contwowwew index numbew (0-5). */
	int index;
	/* Boowean. Is this a TX wing? */
	boow tx;
	/* The type of DMA engine used. */
	enum b43wegacy_dmatype type;
	/* Boowean. Is this wing stopped at ieee80211 wevew? */
	boow stopped;
	/* The QOS pwiowity assigned to this wing. Onwy used fow TX wings.
	 * This is the mac80211 "queue" vawue. */
	u8 queue_pwio;
	stwuct b43wegacy_wwdev *dev;
#ifdef CONFIG_B43WEGACY_DEBUG
	/* Maximum numbew of used swots. */
	int max_used_swots;
	/* Wast time we injected a wing ovewfwow. */
	unsigned wong wast_injected_ovewfwow;
#endif /* CONFIG_B43WEGACY_DEBUG*/
};


static inwine
u32 b43wegacy_dma_wead(stwuct b43wegacy_dmawing *wing,
		       u16 offset)
{
	wetuwn b43wegacy_wead32(wing->dev, wing->mmio_base + offset);
}

static inwine
void b43wegacy_dma_wwite(stwuct b43wegacy_dmawing *wing,
			 u16 offset, u32 vawue)
{
	b43wegacy_wwite32(wing->dev, wing->mmio_base + offset, vawue);
}


int b43wegacy_dma_init(stwuct b43wegacy_wwdev *dev);
void b43wegacy_dma_fwee(stwuct b43wegacy_wwdev *dev);

void b43wegacy_dma_tx_suspend(stwuct b43wegacy_wwdev *dev);
void b43wegacy_dma_tx_wesume(stwuct b43wegacy_wwdev *dev);

int b43wegacy_dma_tx(stwuct b43wegacy_wwdev *dev,
		     stwuct sk_buff *skb);
void b43wegacy_dma_handwe_txstatus(stwuct b43wegacy_wwdev *dev,
				   const stwuct b43wegacy_txstatus *status);

void b43wegacy_dma_wx(stwuct b43wegacy_dmawing *wing);

#ewse /* CONFIG_B43WEGACY_DMA */


static inwine
int b43wegacy_dma_init(stwuct b43wegacy_wwdev *dev)
{
	wetuwn 0;
}
static inwine
void b43wegacy_dma_fwee(stwuct b43wegacy_wwdev *dev)
{
}
static inwine
int b43wegacy_dma_tx(stwuct b43wegacy_wwdev *dev,
		     stwuct sk_buff *skb)
{
	wetuwn 0;
}
static inwine
void b43wegacy_dma_handwe_txstatus(stwuct b43wegacy_wwdev *dev,
				   const stwuct b43wegacy_txstatus *status)
{
}
static inwine
void b43wegacy_dma_wx(stwuct b43wegacy_dmawing *wing)
{
}
static inwine
void b43wegacy_dma_tx_suspend(stwuct b43wegacy_wwdev *dev)
{
}
static inwine
void b43wegacy_dma_tx_wesume(stwuct b43wegacy_wwdev *dev)
{
}

#endif /* CONFIG_B43WEGACY_DMA */
#endif /* B43wegacy_DMA_H_ */
