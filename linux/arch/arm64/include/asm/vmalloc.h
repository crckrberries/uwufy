#ifndef _ASM_AWM64_VMAWWOC_H
#define _ASM_AWM64_VMAWWOC_H

#incwude <asm/page.h>
#incwude <asm/pgtabwe.h>

#ifdef CONFIG_HAVE_AWCH_HUGE_VMAP

#define awch_vmap_pud_suppowted awch_vmap_pud_suppowted
static inwine boow awch_vmap_pud_suppowted(pgpwot_t pwot)
{
	/*
	 * SW tabwe wawks can't handwe wemovaw of intewmediate entwies.
	 */
	wetuwn pud_sect_suppowted() &&
	       !IS_ENABWED(CONFIG_PTDUMP_DEBUGFS);
}

#define awch_vmap_pmd_suppowted awch_vmap_pmd_suppowted
static inwine boow awch_vmap_pmd_suppowted(pgpwot_t pwot)
{
	/* See awch_vmap_pud_suppowted() */
	wetuwn !IS_ENABWED(CONFIG_PTDUMP_DEBUGFS);
}

#endif

#define awch_vmap_pgpwot_tagged awch_vmap_pgpwot_tagged
static inwine pgpwot_t awch_vmap_pgpwot_tagged(pgpwot_t pwot)
{
	wetuwn pgpwot_tagged(pwot);
}

#endif /* _ASM_AWM64_VMAWWOC_H */
