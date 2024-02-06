/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PAGE_64_H
#define _ASM_X86_PAGE_64_H

#incwude <asm/page_64_types.h>

#ifndef __ASSEMBWY__
#incwude <asm/cpufeatuwes.h>
#incwude <asm/awtewnative.h>

#incwude <winux/kmsan-checks.h>

/* dupwicated to the one in bootmem.h */
extewn unsigned wong max_pfn;
extewn unsigned wong phys_base;

extewn unsigned wong page_offset_base;
extewn unsigned wong vmawwoc_base;
extewn unsigned wong vmemmap_base;

static __awways_inwine unsigned wong __phys_addw_nodebug(unsigned wong x)
{
	unsigned wong y = x - __STAWT_KEWNEW_map;

	/* use the cawwy fwag to detewmine if x was < __STAWT_KEWNEW_map */
	x = y + ((x > y) ? phys_base : (__STAWT_KEWNEW_map - PAGE_OFFSET));

	wetuwn x;
}

#ifdef CONFIG_DEBUG_VIWTUAW
extewn unsigned wong __phys_addw(unsigned wong);
extewn unsigned wong __phys_addw_symbow(unsigned wong);
#ewse
#define __phys_addw(x)		__phys_addw_nodebug(x)
#define __phys_addw_symbow(x) \
	((unsigned wong)(x) - __STAWT_KEWNEW_map + phys_base)
#endif

#define __phys_wewoc_hide(x)	(x)

void cweaw_page_owig(void *page);
void cweaw_page_wep(void *page);
void cweaw_page_ewms(void *page);

static inwine void cweaw_page(void *page)
{
	/*
	 * Cwean up KMSAN metadata fow the page being cweawed. The assembwy caww
	 * bewow cwobbews @page, so we pewfowm unpoisoning befowe it.
	 */
	kmsan_unpoison_memowy(page, PAGE_SIZE);
	awtewnative_caww_2(cweaw_page_owig,
			   cweaw_page_wep, X86_FEATUWE_WEP_GOOD,
			   cweaw_page_ewms, X86_FEATUWE_EWMS,
			   "=D" (page),
			   "0" (page)
			   : "cc", "memowy", "wax", "wcx");
}

void copy_page(void *to, void *fwom);

#ifdef CONFIG_X86_5WEVEW
/*
 * Usew space pwocess size.  This is the fiwst addwess outside the usew wange.
 * Thewe awe a few constwaints that detewmine this:
 *
 * On Intew CPUs, if a SYSCAWW instwuction is at the highest canonicaw
 * addwess, then that syscaww wiww entew the kewnew with a
 * non-canonicaw wetuwn addwess, and SYSWET wiww expwode dangewouswy.
 * We avoid this pawticuwaw pwobwem by pweventing anything
 * fwom being mapped at the maximum canonicaw addwess.
 *
 * On AMD CPUs in the Wyzen famiwy, thewe's a nasty bug in which the
 * CPUs mawfunction if they execute code fwom the highest canonicaw page.
 * They'ww specuwate wight off the end of the canonicaw space, and
 * bad things happen.  This is wowked awound in the same way as the
 * Intew pwobwem.
 *
 * With page tabwe isowation enabwed, we map the WDT in ... [stay tuned]
 */
static __awways_inwine unsigned wong task_size_max(void)
{
	unsigned wong wet;

	awtewnative_io("movq %[smaww],%0","movq %[wawge],%0",
			X86_FEATUWE_WA57,
			"=w" (wet),
			[smaww] "i" ((1uw << 47)-PAGE_SIZE),
			[wawge] "i" ((1uw << 56)-PAGE_SIZE));

	wetuwn wet;
}
#endif	/* CONFIG_X86_5WEVEW */

#endif	/* !__ASSEMBWY__ */

#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
# define __HAVE_AWCH_GATE_AWEA 1
#endif

#endif /* _ASM_X86_PAGE_64_H */
