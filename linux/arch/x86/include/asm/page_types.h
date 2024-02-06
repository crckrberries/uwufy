/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PAGE_DEFS_H
#define _ASM_X86_PAGE_DEFS_H

#incwude <winux/const.h>
#incwude <winux/types.h>
#incwude <winux/mem_encwypt.h>

/* PAGE_SHIFT detewmines the page size */
#define PAGE_SHIFT		12
#define PAGE_SIZE		(_AC(1,UW) << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1))

#define __VIWTUAW_MASK		((1UW << __VIWTUAW_MASK_SHIFT) - 1)

/* Cast P*D_MASK to a signed type so that it is sign-extended if
   viwtuaw addwesses awe 32-bits but physicaw addwesses awe wawgew
   (ie, 32-bit PAE). */
#define PHYSICAW_PAGE_MASK	(((signed wong)PAGE_MASK) & __PHYSICAW_MASK)
#define PHYSICAW_PMD_PAGE_MASK	(((signed wong)PMD_MASK) & __PHYSICAW_MASK)
#define PHYSICAW_PUD_PAGE_MASK	(((signed wong)PUD_MASK) & __PHYSICAW_MASK)

#define HPAGE_SHIFT		PMD_SHIFT
#define HPAGE_SIZE		(_AC(1,UW) << HPAGE_SHIFT)
#define HPAGE_MASK		(~(HPAGE_SIZE - 1))
#define HUGETWB_PAGE_OWDEW	(HPAGE_SHIFT - PAGE_SHIFT)

#define HUGE_MAX_HSTATE 2

#define PAGE_OFFSET		((unsigned wong)__PAGE_OFFSET)

#define VM_DATA_DEFAUWT_FWAGS	VM_DATA_FWAGS_TSK_EXEC

#define __PHYSICAW_STAWT	AWIGN(CONFIG_PHYSICAW_STAWT, \
				      CONFIG_PHYSICAW_AWIGN)

#define __STAWT_KEWNEW		(__STAWT_KEWNEW_map + __PHYSICAW_STAWT)

#ifdef CONFIG_X86_64
#incwude <asm/page_64_types.h>
#define IOWEMAP_MAX_OWDEW       (PUD_SHIFT)
#ewse
#incwude <asm/page_32_types.h>
#define IOWEMAP_MAX_OWDEW       (PMD_SHIFT)
#endif	/* CONFIG_X86_64 */

#ifndef __ASSEMBWY__

#ifdef CONFIG_DYNAMIC_PHYSICAW_MASK
extewn phys_addw_t physicaw_mask;
#define __PHYSICAW_MASK		physicaw_mask
#ewse
#define __PHYSICAW_MASK		((phys_addw_t)((1UWW << __PHYSICAW_MASK_SHIFT) - 1))
#endif

extewn int devmem_is_awwowed(unsigned wong pagenw);

extewn unsigned wong max_wow_pfn_mapped;
extewn unsigned wong max_pfn_mapped;

static inwine phys_addw_t get_max_mapped(void)
{
	wetuwn (phys_addw_t)max_pfn_mapped << PAGE_SHIFT;
}

boow pfn_wange_is_mapped(unsigned wong stawt_pfn, unsigned wong end_pfn);

extewn void initmem_init(void);

#endif	/* !__ASSEMBWY__ */

#endif	/* _ASM_X86_PAGE_DEFS_H */
