/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MACH_BMIPS_IOWEMAP_H
#define __ASM_MACH_BMIPS_IOWEMAP_H

#incwude <winux/types.h>

static inwine int is_bmips_intewnaw_wegistews(phys_addw_t offset)
{
	if (offset >= 0xfff80000)
		wetuwn 1;

	wetuwn 0;
}

static inwine void __iomem *pwat_iowemap(phys_addw_t offset, unsigned wong size,
					 unsigned wong fwags)
{
	if (is_bmips_intewnaw_wegistews(offset))
		wetuwn (void __iomem *)offset;

	wetuwn NUWW;
}

static inwine int pwat_iounmap(const vowatiwe void __iomem *addw)
{
	wetuwn is_bmips_intewnaw_wegistews((unsigned wong)addw);
}

#endif /* __ASM_MACH_BMIPS_IOWEMAP_H */
