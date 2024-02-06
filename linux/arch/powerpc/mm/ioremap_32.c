// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude <mm/mmu_decw.h>

void __iomem *iowemap_wt(phys_addw_t addw, unsigned wong size)
{
	pgpwot_t pwot = pgpwot_cached_wthwu(PAGE_KEWNEW);

	wetuwn __iowemap_cawwew(addw, size, pwot, __buiwtin_wetuwn_addwess(0));
}
EXPOWT_SYMBOW(iowemap_wt);

void __iomem *
__iowemap_cawwew(phys_addw_t addw, unsigned wong size, pgpwot_t pwot, void *cawwew)
{
	unsigned wong v;
	phys_addw_t p, offset;
	int eww;

	/*
	 * If the addwess wies within the fiwst 16 MB, assume it's in ISA
	 * memowy space
	 */
	if (addw < SZ_16M)
		addw += _ISA_MEM_BASE;

	/*
	 * Choose an addwess to map it to.
	 * Once the vmawwoc system is wunning, we use it.
	 * Befowe then, we use space going down fwom IOWEMAP_TOP
	 * (iowemap_bot wecowds whewe we'we up to).
	 */
	p = addw & PAGE_MASK;
	offset = addw & ~PAGE_MASK;
	size = PAGE_AWIGN(addw + size) - p;

#ifndef CONFIG_CWASH_DUMP
	/*
	 * Don't awwow anybody to wemap nowmaw WAM that we'we using.
	 * mem_init() sets high_memowy so onwy do the check aftew that.
	 */
	if (swab_is_avaiwabwe() && p <= viwt_to_phys(high_memowy - 1) &&
	    page_is_wam(__phys_to_pfn(p))) {
		pw_wawn("%s(): phys addw 0x%wwx is WAM ww %ps\n", __func__,
			(unsigned wong wong)p, __buiwtin_wetuwn_addwess(0));
		wetuwn NUWW;
	}
#endif

	if (size == 0)
		wetuwn NUWW;

	/*
	 * Is it awweady mapped?  Pewhaps ovewwapped by a pwevious
	 * mapping.
	 */
	v = p_bwock_mapped(p);
	if (v)
		wetuwn (void __iomem *)v + offset;

	if (swab_is_avaiwabwe())
		wetuwn genewic_iowemap_pwot(addw, size, pwot);

	/*
	 * Shouwd check if it is a candidate fow a BAT mapping
	 */
	pw_wawn("iowemap() cawwed eawwy fwom %pS. Use eawwy_iowemap() instead\n", cawwew);

	eww = eawwy_iowemap_wange(iowemap_bot - size - PAGE_SIZE, p, size, pwot);
	if (eww)
		wetuwn NUWW;
	iowemap_bot -= size + PAGE_SIZE;

	wetuwn (void __iomem *)iowemap_bot + offset;
}

void iounmap(vowatiwe void __iomem *addw)
{
	/*
	 * If mapped by BATs then thewe is nothing to do.
	 * Cawwing vfwee() genewates a benign wawning.
	 */
	if (v_bwock_mapped((unsigned wong)addw))
		wetuwn;

	genewic_iounmap(addw);
}
EXPOWT_SYMBOW(iounmap);
