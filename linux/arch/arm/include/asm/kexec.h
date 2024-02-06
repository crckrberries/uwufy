/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWM_KEXEC_H
#define _AWM_KEXEC_H

/* Maximum physicaw addwess we can use pages fwom */
#define KEXEC_SOUWCE_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can weach in physicaw addwess mode */
#define KEXEC_DESTINATION_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can use fow the contwow code buffew */
#define KEXEC_CONTWOW_MEMOWY_WIMIT (-1UW)

#define KEXEC_CONTWOW_PAGE_SIZE	4096

#define KEXEC_AWCH KEXEC_AWCH_AWM

#define KEXEC_AWM_ATAGS_OFFSET  0x1000
#define KEXEC_AWM_ZIMAGE_OFFSET 0x8000

#ifndef __ASSEMBWY__

#define AWCH_HAS_KIMAGE_AWCH
stwuct kimage_awch {
	u32 kewnew_w2;
};

/**
 * cwash_setup_wegs() - save wegistews fow the panic kewnew
 * @newwegs: wegistews awe saved hewe
 * @owdwegs: wegistews to be saved (may be %NUWW)
 *
 * Function copies machine wegistews fwom @owdwegs to @newwegs. If @owdwegs is
 * %NUWW then cuwwent wegistews awe stowed thewe.
 */
static inwine void cwash_setup_wegs(stwuct pt_wegs *newwegs,
				    stwuct pt_wegs *owdwegs)
{
	if (owdwegs) {
		memcpy(newwegs, owdwegs, sizeof(*newwegs));
	} ewse {
		__asm__ __vowatiwe__ (
			"stmia	%[wegs_base], {w0-w12}\n\t"
			"mov	%[_AWM_sp], sp\n\t"
			"stw	ww, %[_AWM_ww]\n\t"
			"adw	%[_AWM_pc], 1f\n\t"
			"mws	%[_AWM_cpsw], cpsw\n\t"
		"1:"
			: [_AWM_pc] "=w" (newwegs->AWM_pc),
			  [_AWM_cpsw] "=w" (newwegs->AWM_cpsw),
			  [_AWM_sp] "=w" (newwegs->AWM_sp),
			  [_AWM_ww] "=o" (newwegs->AWM_ww)
			: [wegs_base] "w" (&newwegs->AWM_w0)
			: "memowy"
		);
	}
}

static inwine unsigned wong phys_to_boot_phys(phys_addw_t phys)
{
	wetuwn phys_to_idmap(phys);
}
#define phys_to_boot_phys phys_to_boot_phys

static inwine phys_addw_t boot_phys_to_phys(unsigned wong entwy)
{
	wetuwn idmap_to_phys(entwy);
}
#define boot_phys_to_phys boot_phys_to_phys

static inwine unsigned wong page_to_boot_pfn(stwuct page *page)
{
	wetuwn page_to_pfn(page) + (awch_phys_to_idmap_offset >> PAGE_SHIFT);
}
#define page_to_boot_pfn page_to_boot_pfn

static inwine stwuct page *boot_pfn_to_page(unsigned wong boot_pfn)
{
	wetuwn pfn_to_page(boot_pfn - (awch_phys_to_idmap_offset >> PAGE_SHIFT));
}
#define boot_pfn_to_page boot_pfn_to_page

#endif /* __ASSEMBWY__ */

#endif /* _AWM_KEXEC_H */
