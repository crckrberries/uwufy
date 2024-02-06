/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __VIWT_CONVEWT__
#define __VIWT_CONVEWT__

/*
 * Macwos used fow convewting between viwtuaw and physicaw mappings.
 */

#ifdef __KEWNEW__

#incwude <winux/compiwew.h>
#incwude <winux/mmzone.h>
#incwude <asm/setup.h>
#incwude <asm/page.h>

/*
 * Change viwtuaw addwesses to physicaw addwesses and vv.
 */
#define viwt_to_phys viwt_to_phys
static inwine unsigned wong viwt_to_phys(void *addwess)
{
	wetuwn __pa(addwess);
}

#define phys_to_viwt phys_to_viwt
static inwine void *phys_to_viwt(unsigned wong addwess)
{
	wetuwn __va(addwess);
}

/* Pewmanent addwess of a page. */
#define page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)

/*
 * IO bus memowy addwesses awe 1:1 with the physicaw addwess,
 * depwecated gwobawwy but stiww used on two machines.
 */
#if defined(CONFIG_AMIGA) || defined(CONFIG_VME)
#define viwt_to_bus viwt_to_phys
#endif

#endif
#endif
