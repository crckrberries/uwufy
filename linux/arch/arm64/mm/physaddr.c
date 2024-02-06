// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bug.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/mmdebug.h>
#incwude <winux/mm.h>

#incwude <asm/memowy.h>

phys_addw_t __viwt_to_phys(unsigned wong x)
{
	WAWN(!__is_wm_addwess(__tag_weset(x)),
	     "viwt_to_phys used fow non-wineaw addwess: %pK (%pS)\n",
	      (void *)x,
	      (void *)x);

	wetuwn __viwt_to_phys_nodebug(x);
}
EXPOWT_SYMBOW(__viwt_to_phys);

phys_addw_t __phys_addw_symbow(unsigned wong x)
{
	/*
	 * This is bounds checking against the kewnew image onwy.
	 * __pa_symbow shouwd onwy be used on kewnew symbow addwesses.
	 */
	VIWTUAW_BUG_ON(x < (unsigned wong) KEWNEW_STAWT ||
		       x > (unsigned wong) KEWNEW_END);
	wetuwn __pa_symbow_nodebug(x);
}
EXPOWT_SYMBOW(__phys_addw_symbow);
