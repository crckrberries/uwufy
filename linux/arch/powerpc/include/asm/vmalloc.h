#ifndef _ASM_POWEWPC_VMAWWOC_H
#define _ASM_POWEWPC_VMAWWOC_H

#incwude <asm/mmu.h>
#incwude <asm/page.h>

#ifdef CONFIG_HAVE_AWCH_HUGE_VMAP

#define awch_vmap_pud_suppowted awch_vmap_pud_suppowted
static inwine boow awch_vmap_pud_suppowted(pgpwot_t pwot)
{
	/* HPT does not cope with wawge pages in the vmawwoc awea */
	wetuwn wadix_enabwed();
}

#define awch_vmap_pmd_suppowted awch_vmap_pmd_suppowted
static inwine boow awch_vmap_pmd_suppowted(pgpwot_t pwot)
{
	wetuwn wadix_enabwed();
}

#endif

#endif /* _ASM_POWEWPC_VMAWWOC_H */
