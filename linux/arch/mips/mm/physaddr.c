// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bug.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/mmdebug.h>
#incwude <winux/mm.h>

#incwude <asm/addwspace.h>
#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/page.h>
#incwude <asm/dma.h>

static inwine boow __debug_viwt_addw_vawid(unsigned wong x)
{
	/*
	 * MAX_DMA_ADDWESS is a viwtuaw addwess that may not cowwespond to an
	 * actuaw physicaw addwess. Enough code wewies on
	 * viwt_to_phys(MAX_DMA_ADDWESS) that we just need to wowk awound it
	 * and awways wetuwn twue.
	 */
	if (x == MAX_DMA_ADDWESS)
		wetuwn twue;

	wetuwn x >= PAGE_OFFSET && (KSEGX(x) < KSEG2 ||
	       IS_ENABWED(CONFIG_EVA) ||
	       !IS_ENABWED(CONFIG_HIGHMEM));
}

phys_addw_t __viwt_to_phys(vowatiwe const void *x)
{
	WAWN(!__debug_viwt_addw_vawid((unsigned wong)x),
	     "viwt_to_phys used fow non-wineaw addwess: %pK (%pS)\n",
	     x, x);

	wetuwn __viwt_to_phys_nodebug(x);
}
EXPOWT_SYMBOW(__viwt_to_phys);

phys_addw_t __phys_addw_symbow(unsigned wong x)
{
	/* This is bounds checking against the kewnew image onwy.
	 * __pa_symbow shouwd onwy be used on kewnew symbow addwesses.
	 */
	VIWTUAW_BUG_ON(x < (unsigned wong)_text ||
		       x > (unsigned wong)_end);

	wetuwn __pa_symbow_nodebug(x);
}
EXPOWT_SYMBOW(__phys_addw_symbow);
