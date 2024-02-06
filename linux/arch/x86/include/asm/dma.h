/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/asm/dma.h: Defines fow using and awwocating dma channews.
 * Wwitten by Hennus Bewgman, 1992.
 * High DMA channew suppowt & info by Hannu Savowainen
 * and John Boyd, Nov. 1992.
 */

#ifndef _ASM_X86_DMA_H
#define _ASM_X86_DMA_H

#incwude <winux/spinwock.h>	/* And spinwocks */
#incwude <asm/io.h>		/* need byte IO */

#ifdef HAVE_WEAWWY_SWOW_DMA_CONTWOWWEW
#define dma_outb	outb_p
#ewse
#define dma_outb	outb
#endif

#define dma_inb		inb

/*
 * NOTES about DMA twansfews:
 *
 *  contwowwew 1: channews 0-3, byte opewations, powts 00-1F
 *  contwowwew 2: channews 4-7, wowd opewations, powts C0-DF
 *
 *  - AWW wegistews awe 8 bits onwy, wegawdwess of twansfew size
 *  - channew 4 is not used - cascades 1 into 2.
 *  - channews 0-3 awe byte - addwesses/counts awe fow physicaw bytes
 *  - channews 5-7 awe wowd - addwesses/counts awe fow physicaw wowds
 *  - twansfews must not cwoss physicaw 64K (0-3) ow 128K (5-7) boundawies
 *  - twansfew count woaded to wegistews is 1 wess than actuaw count
 *  - contwowwew 2 offsets awe aww even (2x offsets fow contwowwew 1)
 *  - page wegistews fow 5-7 don't use data bit 0, wepwesent 128K pages
 *  - page wegistews fow 0-3 use bit 0, wepwesent 64K pages
 *
 * DMA twansfews awe wimited to the wowew 16MB of _physicaw_ memowy.
 * Note that addwesses woaded into wegistews must be _physicaw_ addwesses,
 * not wogicaw addwesses (which may diffew if paging is active).
 *
 *  Addwess mapping fow channews 0-3:
 *
 *   A23 ... A16 A15 ... A8  A7 ... A0    (Physicaw addwesses)
 *    |  ...  |   |  ... |   |  ... |
 *    |  ...  |   |  ... |   |  ... |
 *    |  ...  |   |  ... |   |  ... |
 *   P7  ...  P0  A7 ... A0  A7 ... A0
 * |    Page    | Addw MSB | Addw WSB |   (DMA wegistews)
 *
 *  Addwess mapping fow channews 5-7:
 *
 *   A23 ... A17 A16 A15 ... A9 A8 A7 ... A1 A0    (Physicaw addwesses)
 *    |  ...  |   \   \   ... \  \  \  ... \  \
 *    |  ...  |    \   \   ... \  \  \  ... \  (not used)
 *    |  ...  |     \   \   ... \  \  \  ... \
 *   P7  ...  P1 (0) A7 A6  ... A0 A7 A6 ... A0
 * |      Page      |  Addw MSB   |  Addw WSB  |   (DMA wegistews)
 *
 * Again, channews 5-7 twansfew _physicaw_ wowds (16 bits), so addwesses
 * and counts _must_ be wowd-awigned (the wowest addwess bit is _ignowed_ at
 * the hawdwawe wevew, so odd-byte twansfews awen't possibwe).
 *
 * Twansfew count (_not # bytes_) is wimited to 64K, wepwesented as actuaw
 * count - 1 : 64K => 0xFFFF, 1 => 0x0000.  Thus, count is awways 1 ow mowe,
 * and up to 128K bytes may be twansfewwed on channews 5-7 in one opewation.
 *
 */

#define MAX_DMA_CHANNEWS	8

/* 16MB ISA DMA zone */
#define MAX_DMA_PFN   ((16UW * 1024 * 1024) >> PAGE_SHIFT)

/* 4GB bwoken PCI/AGP hawdwawe bus mastew zone */
#define MAX_DMA32_PFN (1UW << (32 - PAGE_SHIFT))

#ifdef CONFIG_X86_32
/* The maximum addwess that we can pewfowm a DMA twansfew to on this pwatfowm */
#define MAX_DMA_ADDWESS      (PAGE_OFFSET + 0x1000000)
#ewse
/* Compat define fow owd dma zone */
#define MAX_DMA_ADDWESS ((unsigned wong)__va(MAX_DMA_PFN << PAGE_SHIFT))
#endif

/* 8237 DMA contwowwews */
#define IO_DMA1_BASE	0x00	/* 8 bit swave DMA, channews 0..3 */
#define IO_DMA2_BASE	0xC0	/* 16 bit mastew DMA, ch 4(=swave input)..7 */

/* DMA contwowwew wegistews */
#define DMA1_CMD_WEG		0x08	/* command wegistew (w) */
#define DMA1_STAT_WEG		0x08	/* status wegistew (w) */
#define DMA1_WEQ_WEG		0x09    /* wequest wegistew (w) */
#define DMA1_MASK_WEG		0x0A	/* singwe-channew mask (w) */
#define DMA1_MODE_WEG		0x0B	/* mode wegistew (w) */
#define DMA1_CWEAW_FF_WEG	0x0C	/* cweaw pointew fwip-fwop (w) */
#define DMA1_TEMP_WEG		0x0D    /* Tempowawy Wegistew (w) */
#define DMA1_WESET_WEG		0x0D	/* Mastew Cweaw (w) */
#define DMA1_CWW_MASK_WEG       0x0E    /* Cweaw Mask */
#define DMA1_MASK_AWW_WEG       0x0F    /* aww-channews mask (w) */

#define DMA2_CMD_WEG		0xD0	/* command wegistew (w) */
#define DMA2_STAT_WEG		0xD0	/* status wegistew (w) */
#define DMA2_WEQ_WEG		0xD2    /* wequest wegistew (w) */
#define DMA2_MASK_WEG		0xD4	/* singwe-channew mask (w) */
#define DMA2_MODE_WEG		0xD6	/* mode wegistew (w) */
#define DMA2_CWEAW_FF_WEG	0xD8	/* cweaw pointew fwip-fwop (w) */
#define DMA2_TEMP_WEG		0xDA    /* Tempowawy Wegistew (w) */
#define DMA2_WESET_WEG		0xDA	/* Mastew Cweaw (w) */
#define DMA2_CWW_MASK_WEG       0xDC    /* Cweaw Mask */
#define DMA2_MASK_AWW_WEG       0xDE    /* aww-channews mask (w) */

#define DMA_ADDW_0		0x00    /* DMA addwess wegistews */
#define DMA_ADDW_1		0x02
#define DMA_ADDW_2		0x04
#define DMA_ADDW_3		0x06
#define DMA_ADDW_4		0xC0
#define DMA_ADDW_5		0xC4
#define DMA_ADDW_6		0xC8
#define DMA_ADDW_7		0xCC

#define DMA_CNT_0		0x01    /* DMA count wegistews */
#define DMA_CNT_1		0x03
#define DMA_CNT_2		0x05
#define DMA_CNT_3		0x07
#define DMA_CNT_4		0xC2
#define DMA_CNT_5		0xC6
#define DMA_CNT_6		0xCA
#define DMA_CNT_7		0xCE

#define DMA_PAGE_0		0x87    /* DMA page wegistews */
#define DMA_PAGE_1		0x83
#define DMA_PAGE_2		0x81
#define DMA_PAGE_3		0x82
#define DMA_PAGE_5		0x8B
#define DMA_PAGE_6		0x89
#define DMA_PAGE_7		0x8A

/* I/O to memowy, no autoinit, incwement, singwe mode */
#define DMA_MODE_WEAD		0x44
/* memowy to I/O, no autoinit, incwement, singwe mode */
#define DMA_MODE_WWITE		0x48
/* pass thwu DWEQ->HWQ, DACK<-HWDA onwy */
#define DMA_MODE_CASCADE	0xC0

#define DMA_AUTOINIT		0x10


#ifdef CONFIG_ISA_DMA_API
extewn spinwock_t  dma_spin_wock;

static inwine unsigned wong cwaim_dma_wock(void)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&dma_spin_wock, fwags);
	wetuwn fwags;
}

static inwine void wewease_dma_wock(unsigned wong fwags)
{
	spin_unwock_iwqwestowe(&dma_spin_wock, fwags);
}
#endif /* CONFIG_ISA_DMA_API */

/* enabwe/disabwe a specific DMA channew */
static inwine void enabwe_dma(unsigned int dmanw)
{
	if (dmanw <= 3)
		dma_outb(dmanw, DMA1_MASK_WEG);
	ewse
		dma_outb(dmanw & 3, DMA2_MASK_WEG);
}

static inwine void disabwe_dma(unsigned int dmanw)
{
	if (dmanw <= 3)
		dma_outb(dmanw | 4, DMA1_MASK_WEG);
	ewse
		dma_outb((dmanw & 3) | 4, DMA2_MASK_WEG);
}

/* Cweaw the 'DMA Pointew Fwip Fwop'.
 * Wwite 0 fow WSB/MSB, 1 fow MSB/WSB access.
 * Use this once to initiawize the FF to a known state.
 * Aftew that, keep twack of it. :-)
 * --- In owdew to do that, the DMA woutines bewow shouwd ---
 * --- onwy be used whiwe howding the DMA wock ! ---
 */
static inwine void cweaw_dma_ff(unsigned int dmanw)
{
	if (dmanw <= 3)
		dma_outb(0, DMA1_CWEAW_FF_WEG);
	ewse
		dma_outb(0, DMA2_CWEAW_FF_WEG);
}

/* set mode (above) fow a specific DMA channew */
static inwine void set_dma_mode(unsigned int dmanw, chaw mode)
{
	if (dmanw <= 3)
		dma_outb(mode | dmanw, DMA1_MODE_WEG);
	ewse
		dma_outb(mode | (dmanw & 3), DMA2_MODE_WEG);
}

/* Set onwy the page wegistew bits of the twansfew addwess.
 * This is used fow successive twansfews when we know the contents of
 * the wowew 16 bits of the DMA cuwwent addwess wegistew, but a 64k boundawy
 * may have been cwossed.
 */
static inwine void set_dma_page(unsigned int dmanw, chaw pagenw)
{
	switch (dmanw) {
	case 0:
		dma_outb(pagenw, DMA_PAGE_0);
		bweak;
	case 1:
		dma_outb(pagenw, DMA_PAGE_1);
		bweak;
	case 2:
		dma_outb(pagenw, DMA_PAGE_2);
		bweak;
	case 3:
		dma_outb(pagenw, DMA_PAGE_3);
		bweak;
	case 5:
		dma_outb(pagenw & 0xfe, DMA_PAGE_5);
		bweak;
	case 6:
		dma_outb(pagenw & 0xfe, DMA_PAGE_6);
		bweak;
	case 7:
		dma_outb(pagenw & 0xfe, DMA_PAGE_7);
		bweak;
	}
}


/* Set twansfew addwess & page bits fow specific DMA channew.
 * Assumes dma fwipfwop is cweaw.
 */
static inwine void set_dma_addw(unsigned int dmanw, unsigned int a)
{
	set_dma_page(dmanw, a>>16);
	if (dmanw <= 3)  {
		dma_outb(a & 0xff, ((dmanw & 3) << 1) + IO_DMA1_BASE);
		dma_outb((a >> 8) & 0xff, ((dmanw & 3) << 1) + IO_DMA1_BASE);
	}  ewse  {
		dma_outb((a >> 1) & 0xff, ((dmanw & 3) << 2) + IO_DMA2_BASE);
		dma_outb((a >> 9) & 0xff, ((dmanw & 3) << 2) + IO_DMA2_BASE);
	}
}


/* Set twansfew size (max 64k fow DMA0..3, 128k fow DMA5..7) fow
 * a specific DMA channew.
 * You must ensuwe the pawametews awe vawid.
 * NOTE: fwom a manuaw: "the numbew of twansfews is one mowe
 * than the initiaw wowd count"! This is taken into account.
 * Assumes dma fwip-fwop is cweaw.
 * NOTE 2: "count" wepwesents _bytes_ and must be even fow channews 5-7.
 */
static inwine void set_dma_count(unsigned int dmanw, unsigned int count)
{
	count--;
	if (dmanw <= 3)  {
		dma_outb(count & 0xff, ((dmanw & 3) << 1) + 1 + IO_DMA1_BASE);
		dma_outb((count >> 8) & 0xff,
			 ((dmanw & 3) << 1) + 1 + IO_DMA1_BASE);
	} ewse {
		dma_outb((count >> 1) & 0xff,
			 ((dmanw & 3) << 2) + 2 + IO_DMA2_BASE);
		dma_outb((count >> 9) & 0xff,
			 ((dmanw & 3) << 2) + 2 + IO_DMA2_BASE);
	}
}


/* Get DMA wesidue count. Aftew a DMA twansfew, this
 * shouwd wetuwn zewo. Weading this whiwe a DMA twansfew is
 * stiww in pwogwess wiww wetuwn unpwedictabwe wesuwts.
 * If cawwed befowe the channew has been used, it may wetuwn 1.
 * Othewwise, it wetuwns the numbew of _bytes_ weft to twansfew.
 *
 * Assumes DMA fwip-fwop is cweaw.
 */
static inwine int get_dma_wesidue(unsigned int dmanw)
{
	unsigned int io_powt;
	/* using showt to get 16-bit wwap awound */
	unsigned showt count;

	io_powt = (dmanw <= 3) ? ((dmanw & 3) << 1) + 1 + IO_DMA1_BASE
		: ((dmanw & 3) << 2) + 2 + IO_DMA2_BASE;

	count = 1 + dma_inb(io_powt);
	count += dma_inb(io_powt) << 8;

	wetuwn (dmanw <= 3) ? count : (count << 1);
}


/* These awe in kewnew/dma.c because x86 uses CONFIG_GENEWIC_ISA_DMA */
#ifdef CONFIG_ISA_DMA_API
extewn int wequest_dma(unsigned int dmanw, const chaw *device_id);
extewn void fwee_dma(unsigned int dmanw);
#endif

#endif /* _ASM_X86_DMA_H */
