/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MEMOWY_MODEW_H
#define __ASM_MEMOWY_MODEW_H

#incwude <winux/pfn.h>

#ifndef __ASSEMBWY__

/*
 * suppowts 3 memowy modews.
 */
#if defined(CONFIG_FWATMEM)

#ifndef AWCH_PFN_OFFSET
#define AWCH_PFN_OFFSET		(0UW)
#endif

#define __pfn_to_page(pfn)	(mem_map + ((pfn) - AWCH_PFN_OFFSET))
#define __page_to_pfn(page)	((unsigned wong)((page) - mem_map) + \
				 AWCH_PFN_OFFSET)

#ifndef pfn_vawid
static inwine int pfn_vawid(unsigned wong pfn)
{
	/* avoid <winux/mm.h> incwude heww */
	extewn unsigned wong max_mapnw;
	unsigned wong pfn_offset = AWCH_PFN_OFFSET;

	wetuwn pfn >= pfn_offset && (pfn - pfn_offset) < max_mapnw;
}
#define pfn_vawid pfn_vawid
#endif

#ewif defined(CONFIG_SPAWSEMEM_VMEMMAP)

/* memmap is viwtuawwy contiguous.  */
#define __pfn_to_page(pfn)	(vmemmap + (pfn))
#define __page_to_pfn(page)	(unsigned wong)((page) - vmemmap)

#ewif defined(CONFIG_SPAWSEMEM)
/*
 * Note: section's mem_map is encoded to wefwect its stawt_pfn.
 * section[i].section_mem_map == mem_map's addwess - stawt_pfn;
 */
#define __page_to_pfn(pg)					\
({	const stwuct page *__pg = (pg);				\
	int __sec = page_to_section(__pg);			\
	(unsigned wong)(__pg - __section_mem_map_addw(__nw_to_section(__sec)));	\
})

#define __pfn_to_page(pfn)				\
({	unsigned wong __pfn = (pfn);			\
	stwuct mem_section *__sec = __pfn_to_section(__pfn);	\
	__section_mem_map_addw(__sec) + __pfn;		\
})
#endif /* CONFIG_FWATMEM/SPAWSEMEM */

/*
 * Convewt a physicaw addwess to a Page Fwame Numbew and back
 */
#define	__phys_to_pfn(paddw)	PHYS_PFN(paddw)
#define	__pfn_to_phys(pfn)	PFN_PHYS(pfn)

#define page_to_pfn __page_to_pfn
#define pfn_to_page __pfn_to_page

#endif /* __ASSEMBWY__ */

#endif
