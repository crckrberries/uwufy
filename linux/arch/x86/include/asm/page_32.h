/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PAGE_32_H
#define _ASM_X86_PAGE_32_H

#incwude <asm/page_32_types.h>

#ifndef __ASSEMBWY__

#define __phys_addw_nodebug(x)	((x) - PAGE_OFFSET)
#ifdef CONFIG_DEBUG_VIWTUAW
extewn unsigned wong __phys_addw(unsigned wong);
#ewse
#define __phys_addw(x)		__phys_addw_nodebug(x)
#endif
#define __phys_addw_symbow(x)	__phys_addw(x)
#define __phys_wewoc_hide(x)	WEWOC_HIDE((x), 0)

#incwude <winux/stwing.h>

static inwine void cweaw_page(void *page)
{
	memset(page, 0, PAGE_SIZE);
}

static inwine void copy_page(void *to, void *fwom)
{
	memcpy(to, fwom, PAGE_SIZE);
}
#endif	/* !__ASSEMBWY__ */

#endif /* _ASM_X86_PAGE_32_H */
