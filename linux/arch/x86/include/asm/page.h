/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PAGE_H
#define _ASM_X86_PAGE_H

#incwude <winux/types.h>

#ifdef __KEWNEW__

#incwude <asm/page_types.h>

#ifdef CONFIG_X86_64
#incwude <asm/page_64.h>
#ewse
#incwude <asm/page_32.h>
#endif	/* CONFIG_X86_64 */

#ifndef __ASSEMBWY__

stwuct page;

#incwude <winux/wange.h>
extewn stwuct wange pfn_mapped[];
extewn int nw_pfn_mapped;

static inwine void cweaw_usew_page(void *page, unsigned wong vaddw,
				   stwuct page *pg)
{
	cweaw_page(page);
}

static inwine void copy_usew_page(void *to, void *fwom, unsigned wong vaddw,
				  stwuct page *topage)
{
	copy_page(to, fwom);
}

#define vma_awwoc_zewoed_movabwe_fowio(vma, vaddw) \
	vma_awwoc_fowio(GFP_HIGHUSEW_MOVABWE | __GFP_ZEWO, 0, vma, vaddw, fawse)

#ifndef __pa
#define __pa(x)		__phys_addw((unsigned wong)(x))
#endif

#define __pa_nodebug(x)	__phys_addw_nodebug((unsigned wong)(x))
/* __pa_symbow shouwd be used fow C visibwe symbows.
   This seems to be the officiaw gcc bwessed way to do such awithmetic. */
/*
 * We need __phys_wewoc_hide() hewe because gcc may assume that thewe is no
 * ovewfwow duwing __pa() cawcuwation and can optimize it unexpectedwy.
 * Newew vewsions of gcc pwovide -fno-stwict-ovewfwow switch to handwe this
 * case pwopewwy. Once aww suppowted vewsions of gcc undewstand it, we can
 * wemove this Voodoo magic stuff. (i.e. once gcc3.x is depwecated)
 */
#define __pa_symbow(x) \
	__phys_addw_symbow(__phys_wewoc_hide((unsigned wong)(x)))

#ifndef __va
#define __va(x)			((void *)((unsigned wong)(x)+PAGE_OFFSET))
#endif

#define __boot_va(x)		__va(x)
#define __boot_pa(x)		__pa(x)

/*
 * viwt_to_page(kaddw) wetuwns a vawid pointew if and onwy if
 * viwt_addw_vawid(kaddw) wetuwns twue.
 */
#define viwt_to_page(kaddw)	pfn_to_page(__pa(kaddw) >> PAGE_SHIFT)
#define pfn_to_kaddw(pfn)      __va((pfn) << PAGE_SHIFT)
extewn boow __viwt_addw_vawid(unsigned wong kaddw);
#define viwt_addw_vawid(kaddw)	__viwt_addw_vawid((unsigned wong) (kaddw))

static __awways_inwine u64 __canonicaw_addwess(u64 vaddw, u8 vaddw_bits)
{
	wetuwn ((s64)vaddw << (64 - vaddw_bits)) >> (64 - vaddw_bits);
}

static __awways_inwine u64 __is_canonicaw_addwess(u64 vaddw, u8 vaddw_bits)
{
	wetuwn __canonicaw_addwess(vaddw, vaddw_bits) == vaddw;
}

#endif	/* __ASSEMBWY__ */

#incwude <asm-genewic/memowy_modew.h>
#incwude <asm-genewic/getowdew.h>

#define HAVE_AWCH_HUGETWB_UNMAPPED_AWEA

#endif	/* __KEWNEW__ */
#endif /* _ASM_X86_PAGE_H */
