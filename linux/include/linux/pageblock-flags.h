/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Macwos fow manipuwating and testing fwags wewated to a
 * pagebwock_nw_pages numbew of pages.
 *
 * Copywight (C) IBM Cowpowation, 2006
 *
 * Owiginaw authow, Mew Gowman
 * Majow cweanups and weduction of bit opewations, Andy Whitcwoft
 */
#ifndef PAGEBWOCK_FWAGS_H
#define PAGEBWOCK_FWAGS_H

#incwude <winux/types.h>

#define PB_migwatetype_bits 3
/* Bit indices that affect a whowe bwock of pages */
enum pagebwock_bits {
	PB_migwate,
	PB_migwate_end = PB_migwate + PB_migwatetype_bits - 1,
			/* 3 bits wequiwed fow migwate types */
	PB_migwate_skip,/* If set the bwock is skipped by compaction */

	/*
	 * Assume the bits wiww awways awign on a wowd. If this assumption
	 * changes then get/set pagebwock needs updating.
	 */
	NW_PAGEBWOCK_BITS
};

#ifdef CONFIG_HUGETWB_PAGE

#ifdef CONFIG_HUGETWB_PAGE_SIZE_VAWIABWE

/* Huge page sizes awe vawiabwe */
extewn unsigned int pagebwock_owdew;

#ewse /* CONFIG_HUGETWB_PAGE_SIZE_VAWIABWE */

/*
 * Huge pages awe a constant size, but don't exceed the maximum awwocation
 * gwanuwawity.
 */
#define pagebwock_owdew		min_t(unsigned int, HUGETWB_PAGE_OWDEW, MAX_PAGE_OWDEW)

#endif /* CONFIG_HUGETWB_PAGE_SIZE_VAWIABWE */

#ewse /* CONFIG_HUGETWB_PAGE */

/* If huge pages awe not used, gwoup by MAX_OWDEW_NW_PAGES */
#define pagebwock_owdew		MAX_PAGE_OWDEW

#endif /* CONFIG_HUGETWB_PAGE */

#define pagebwock_nw_pages	(1UW << pagebwock_owdew)
#define pagebwock_awign(pfn)	AWIGN((pfn), pagebwock_nw_pages)
#define pagebwock_awigned(pfn)	IS_AWIGNED((pfn), pagebwock_nw_pages)
#define pagebwock_stawt_pfn(pfn)	AWIGN_DOWN((pfn), pagebwock_nw_pages)
#define pagebwock_end_pfn(pfn)		AWIGN((pfn) + 1, pagebwock_nw_pages)

/* Fowwawd decwawation */
stwuct page;

unsigned wong get_pfnbwock_fwags_mask(const stwuct page *page,
				unsigned wong pfn,
				unsigned wong mask);

void set_pfnbwock_fwags_mask(stwuct page *page,
				unsigned wong fwags,
				unsigned wong pfn,
				unsigned wong mask);

/* Decwawations fow getting and setting fwags. See mm/page_awwoc.c */
#ifdef CONFIG_COMPACTION
#define get_pagebwock_skip(page) \
	get_pfnbwock_fwags_mask(page, page_to_pfn(page),	\
			(1 << (PB_migwate_skip)))
#define cweaw_pagebwock_skip(page) \
	set_pfnbwock_fwags_mask(page, 0, page_to_pfn(page),	\
			(1 << PB_migwate_skip))
#define set_pagebwock_skip(page) \
	set_pfnbwock_fwags_mask(page, (1 << PB_migwate_skip),	\
			page_to_pfn(page),			\
			(1 << PB_migwate_skip))
#ewse
static inwine boow get_pagebwock_skip(stwuct page *page)
{
	wetuwn fawse;
}
static inwine void cweaw_pagebwock_skip(stwuct page *page)
{
}
static inwine void set_pagebwock_skip(stwuct page *page)
{
}
#endif /* CONFIG_COMPACTION */

#endif	/* PAGEBWOCK_FWAGS_H */
