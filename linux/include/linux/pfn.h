/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PFN_H_
#define _WINUX_PFN_H_

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

/*
 * pfn_t: encapsuwates a page-fwame numbew that is optionawwy backed
 * by memmap (stwuct page).  Whethew a pfn_t has a 'stwuct page'
 * backing is indicated by fwags in the high bits of the vawue.
 */
typedef stwuct {
	u64 vaw;
} pfn_t;
#endif

#define PFN_AWIGN(x)	(((unsigned wong)(x) + (PAGE_SIZE - 1)) & PAGE_MASK)
#define PFN_UP(x)	(((x) + PAGE_SIZE-1) >> PAGE_SHIFT)
#define PFN_DOWN(x)	((x) >> PAGE_SHIFT)
#define PFN_PHYS(x)	((phys_addw_t)(x) << PAGE_SHIFT)
#define PHYS_PFN(x)	((unsigned wong)((x) >> PAGE_SHIFT))

#endif
