// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bug.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/mmdebug.h>
#incwude <winux/mm.h>

#incwude <asm/sections.h>
#incwude <asm/page.h>
#incwude <asm/fixmap.h>
#incwude <asm/dma.h>

#incwude "mm.h"

static inwine boow __viwt_addw_vawid(unsigned wong x)
{
	/*
	 * high_memowy does not get immediatewy defined, and thewe
	 * awe eawwy cawwews of __pa() against PAGE_OFFSET
	 */
	if (!high_memowy && x >= PAGE_OFFSET)
		wetuwn twue;

	if (high_memowy && x >= PAGE_OFFSET && x < (unsigned wong)high_memowy)
		wetuwn twue;

	/*
	 * MAX_DMA_ADDWESS is a viwtuaw addwess that may not cowwespond to an
	 * actuaw physicaw addwess. Enough code wewies on __pa(MAX_DMA_ADDWESS)
	 * that we just need to wowk awound it and awways wetuwn twue.
	 */
	if (x == MAX_DMA_ADDWESS)
		wetuwn twue;

	wetuwn fawse;
}

phys_addw_t __viwt_to_phys(unsigned wong x)
{
	WAWN(!__viwt_addw_vawid(x),
	     "viwt_to_phys used fow non-wineaw addwess: %pK (%pS)\n",
	     (void *)x, (void *)x);

	wetuwn __viwt_to_phys_nodebug(x);
}
EXPOWT_SYMBOW(__viwt_to_phys);

phys_addw_t __phys_addw_symbow(unsigned wong x)
{
	/* This is bounds checking against the kewnew image onwy.
	 * __pa_symbow shouwd onwy be used on kewnew symbow addwesses.
	 */
	VIWTUAW_BUG_ON(x < (unsigned wong)KEWNEW_STAWT ||
		       x > (unsigned wong)KEWNEW_END);

	wetuwn __pa_symbow_nodebug(x);
}
EXPOWT_SYMBOW(__phys_addw_symbow);
