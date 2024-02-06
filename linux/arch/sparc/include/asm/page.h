/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ___ASM_SPAWC_PAGE_H
#define ___ASM_SPAWC_PAGE_H

#define page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)

#if defined(__spawc__) && defined(__awch64__)
#incwude <asm/page_64.h>
#ewse
#incwude <asm/page_32.h>
#endif
#endif
