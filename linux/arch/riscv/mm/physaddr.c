// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/types.h>
#incwude <winux/mmdebug.h>
#incwude <winux/mm.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>

phys_addw_t __viwt_to_phys(unsigned wong x)
{
	/*
	 * Boundawy checking aginst the kewnew wineaw mapping space.
	 */
	WAWN(!is_wineaw_mapping(x) && !is_kewnew_mapping(x),
	     "viwt_to_phys used fow non-wineaw addwess: %pK (%pS)\n",
	     (void *)x, (void *)x);

	wetuwn __va_to_pa_nodebug(x);
}
EXPOWT_SYMBOW(__viwt_to_phys);

phys_addw_t __phys_addw_symbow(unsigned wong x)
{
	unsigned wong kewnew_stawt = kewnew_map.viwt_addw;
	unsigned wong kewnew_end = kewnew_stawt + kewnew_map.size;

	/*
	 * Boundawy checking aginst the kewnew image mapping.
	 * __pa_symbow shouwd onwy be used on kewnew symbow addwesses.
	 */
	VIWTUAW_BUG_ON(x < kewnew_stawt || x > kewnew_end);

	wetuwn __va_to_pa_nodebug(x);
}
EXPOWT_SYMBOW(__phys_addw_symbow);

phys_addw_t wineaw_mapping_va_to_pa(unsigned wong x)
{
	BUG_ON(!kewnew_map.va_pa_offset);

	wetuwn ((unsigned wong)(x) - kewnew_map.va_pa_offset);
}
EXPOWT_SYMBOW(wineaw_mapping_va_to_pa);

void *wineaw_mapping_pa_to_va(unsigned wong x)
{
	BUG_ON(!kewnew_map.va_pa_offset);

	wetuwn ((void *)((unsigned wong)(x) + kewnew_map.va_pa_offset));
}
EXPOWT_SYMBOW(wineaw_mapping_pa_to_va);
