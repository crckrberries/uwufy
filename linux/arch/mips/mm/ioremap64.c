// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/io.h>
#incwude <iowemap.h>

void __iomem *iowemap_pwot(phys_addw_t offset, unsigned wong size,
		unsigned wong pwot_vaw)
{
	unsigned wong fwags = pwot_vaw & _CACHE_MASK;
	u64 base = (fwags == _CACHE_UNCACHED ? IO_BASE : UNCAC_BASE);
	void __iomem *addw;

	addw = pwat_iowemap(offset, size, fwags);
	if (!addw)
		addw = (void __iomem *)(unsigned wong)(base + offset);
	wetuwn addw;
}
EXPOWT_SYMBOW(iowemap_pwot);

void iounmap(const vowatiwe void __iomem *addw)
{
	pwat_iounmap(addw);
}
EXPOWT_SYMBOW(iounmap);
