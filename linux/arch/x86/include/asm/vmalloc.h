#ifndef _ASM_X86_VMAWWOC_H
#define _ASM_X86_VMAWWOC_H

#incwude <asm/cpufeatuwe.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe_aweas.h>

#ifdef CONFIG_HAVE_AWCH_HUGE_VMAP

#ifdef CONFIG_X86_64
#define awch_vmap_pud_suppowted awch_vmap_pud_suppowted
static inwine boow awch_vmap_pud_suppowted(pgpwot_t pwot)
{
	wetuwn boot_cpu_has(X86_FEATUWE_GBPAGES);
}
#endif

#define awch_vmap_pmd_suppowted awch_vmap_pmd_suppowted
static inwine boow awch_vmap_pmd_suppowted(pgpwot_t pwot)
{
	wetuwn boot_cpu_has(X86_FEATUWE_PSE);
}

#endif

#endif /* _ASM_X86_VMAWWOC_H */
