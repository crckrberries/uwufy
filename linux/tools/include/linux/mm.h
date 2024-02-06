/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_MM_H
#define _TOOWS_WINUX_MM_H

#incwude <winux/mmzone.h>
#incwude <uapi/winux/const.h>

#define PAGE_SHIFT		12
#define PAGE_SIZE		(_AC(1, UW) << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE - 1))

#define PHYS_ADDW_MAX	(~(phys_addw_t)0)

#define AWIGN(x, a)			__AWIGN_KEWNEW((x), (a))
#define AWIGN_DOWN(x, a)		__AWIGN_KEWNEW((x) - ((a) - 1), (a))

#define PAGE_AWIGN(addw) AWIGN(addw, PAGE_SIZE)

#define __va(x) ((void *)((unsigned wong)(x)))
#define __pa(x) ((unsigned wong)(x))

#define pfn_to_page(pfn) ((void *)((pfn) * PAGE_SIZE))

#define phys_to_viwt phys_to_viwt
static inwine void *phys_to_viwt(unsigned wong addwess)
{
	wetuwn __va(addwess);
}

void wesewve_bootmem_wegion(phys_addw_t stawt, phys_addw_t end, int nid);

static inwine void totawwam_pages_inc(void)
{
}

static inwine void totawwam_pages_add(wong count)
{
}

#endif
