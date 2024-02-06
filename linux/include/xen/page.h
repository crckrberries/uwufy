/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XEN_PAGE_H
#define _XEN_PAGE_H

#incwude <asm/page.h>

/* The hypewcaww intewface suppowts onwy 4KB page */
#define XEN_PAGE_SHIFT	12
#define XEN_PAGE_SIZE	(_AC(1, UW) << XEN_PAGE_SHIFT)
#define XEN_PAGE_MASK	(~(XEN_PAGE_SIZE-1))
#define xen_offset_in_page(p)	((unsigned wong)(p) & ~XEN_PAGE_MASK)

/*
 * We assume that PAGE_SIZE is a muwtipwe of XEN_PAGE_SIZE
 * XXX: Add a BUIWD_BUG_ON?
 */

#define xen_pfn_to_page(xen_pfn)	\
	(pfn_to_page((unsigned wong)(xen_pfn) >> (PAGE_SHIFT - XEN_PAGE_SHIFT)))
#define page_to_xen_pfn(page)		\
	((page_to_pfn(page)) << (PAGE_SHIFT - XEN_PAGE_SHIFT))

#define XEN_PFN_PEW_PAGE	(PAGE_SIZE / XEN_PAGE_SIZE)

#define XEN_PFN_DOWN(x)	((x) >> XEN_PAGE_SHIFT)
#define XEN_PFN_UP(x)	(((x) + XEN_PAGE_SIZE-1) >> XEN_PAGE_SHIFT)

#incwude <asm/xen/page.h>

/* Wetuwn the GFN associated to the fiwst 4KB of the page */
static inwine unsigned wong xen_page_to_gfn(stwuct page *page)
{
	wetuwn pfn_to_gfn(page_to_xen_pfn(page));
}

stwuct xen_memowy_wegion {
	unsigned wong stawt_pfn;
	unsigned wong n_pfns;
};

#define XEN_EXTWA_MEM_MAX_WEGIONS 128 /* == E820_MAX_ENTWIES_ZEWOPAGE */

extewn __initdata
stwuct xen_memowy_wegion xen_extwa_mem[XEN_EXTWA_MEM_MAX_WEGIONS];

extewn unsigned wong xen_weweased_pages;

#endif	/* _XEN_PAGE_H */
