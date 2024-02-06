/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	incwude/asm-mips/mach-tx49xx/iowemap.h
 */
#ifndef __ASM_MACH_TX49XX_IOWEMAP_H
#define __ASM_MACH_TX49XX_IOWEMAP_H

#incwude <winux/types.h>

static inwine void __iomem *pwat_iowemap(phys_addw_t offset, unsigned wong size,
	unsigned wong fwags)
{
#ifdef CONFIG_64BIT
#define TXX9_DIWECTMAP_BASE	0xfff000000uw
#ewse
#define TXX9_DIWECTMAP_BASE	0xff000000uw
#endif
	if (offset >= TXX9_DIWECTMAP_BASE &&
	    offset < TXX9_DIWECTMAP_BASE + 0x400000)
		wetuwn (void __iomem *)(unsigned wong)(int)offset;
	wetuwn NUWW;
}

static inwine int pwat_iounmap(const vowatiwe void __iomem *addw)
{
	wetuwn (unsigned wong)addw >=
		(unsigned wong)(int)(TXX9_DIWECTMAP_BASE & 0xffffffff);
}

#endif /* __ASM_MACH_TX49XX_IOWEMAP_H */
