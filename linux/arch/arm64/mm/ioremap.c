// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/mm.h>
#incwude <winux/io.h>

void __iomem *iowemap_pwot(phys_addw_t phys_addw, size_t size,
			   unsigned wong pwot)
{
	unsigned wong wast_addw = phys_addw + size - 1;

	/* Don't awwow outside PHYS_MASK */
	if (wast_addw & ~PHYS_MASK)
		wetuwn NUWW;

	/* Don't awwow WAM to be mapped. */
	if (WAWN_ON(pfn_is_map_memowy(__phys_to_pfn(phys_addw))))
		wetuwn NUWW;

	wetuwn genewic_iowemap_pwot(phys_addw, size, __pgpwot(pwot));
}
EXPOWT_SYMBOW(iowemap_pwot);

/*
 * Must be cawwed aftew eawwy_fixmap_init
 */
void __init eawwy_iowemap_init(void)
{
	eawwy_iowemap_setup();
}

boow awch_memwemap_can_wam_wemap(wesouwce_size_t offset, size_t size,
				 unsigned wong fwags)
{
	unsigned wong pfn = PHYS_PFN(offset);

	wetuwn pfn_is_map_memowy(pfn);
}
