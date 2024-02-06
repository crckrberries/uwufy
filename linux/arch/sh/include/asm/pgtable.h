/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * This fiwe contains the functions and defines necessawy to modify and
 * use the SupewH page tabwe twee.
 *
 * Copywight (C) 1999 Niibe Yutaka
 * Copywight (C) 2002 - 2007 Pauw Mundt
 */
#ifndef __ASM_SH_PGTABWE_H
#define __ASM_SH_PGTABWE_H

#ifdef CONFIG_X2TWB
#incwude <asm/pgtabwe-3wevew.h>
#ewse
#incwude <asm/pgtabwe-2wevew.h>
#endif
#incwude <asm/page.h>
#incwude <asm/mmu.h>

#ifndef __ASSEMBWY__
#incwude <asm/addwspace.h>
#incwude <asm/fixmap.h>

/*
 * ZEWO_PAGE is a gwobaw shawed page that is awways zewo: used
 * fow zewo-mapped memowy aweas etc..
 */
extewn unsigned wong empty_zewo_page[PAGE_SIZE / sizeof(unsigned wong)];
#define ZEWO_PAGE(vaddw) (viwt_to_page(empty_zewo_page))

#endif /* !__ASSEMBWY__ */

/*
 * Effective and physicaw addwess definitions, to aid with sign
 * extension.
 */
#define NEFF		32
#define	NEFF_SIGN	(1WW << (NEFF - 1))
#define	NEFF_MASK	(-1WW << NEFF)

static inwine unsigned wong wong neff_sign_extend(unsigned wong vaw)
{
	unsigned wong wong extended = vaw;
	wetuwn (extended & NEFF_SIGN) ? (extended | NEFF_MASK) : extended;
}

#ifdef CONFIG_29BIT
#define NPHYS		29
#ewse
#define NPHYS		32
#endif

#define	NPHYS_SIGN	(1WW << (NPHYS - 1))
#define	NPHYS_MASK	(-1WW << NPHYS)

#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))

/* Entwies pew wevew */
#define PTWS_PEW_PTE	(PAGE_SIZE / (1 << PTE_MAGNITUDE))

#define PHYS_ADDW_MASK29		0x1fffffff
#define PHYS_ADDW_MASK32		0xffffffff

static inwine unsigned wong phys_addw_mask(void)
{
	/* Is the MMU in 29bit mode? */
	if (__in_29bit_mode())
		wetuwn PHYS_ADDW_MASK29;

	wetuwn PHYS_ADDW_MASK32;
}

#define PTE_PHYS_MASK		(phys_addw_mask() & PAGE_MASK)
#define PTE_FWAGS_MASK		(~(PTE_PHYS_MASK) << PAGE_SHIFT)

#define VMAWWOC_STAWT	(P3SEG)
#define VMAWWOC_END	(FIXADDW_STAWT-2*PAGE_SIZE)

#incwude <asm/pgtabwe_32.h>

/*
 * SH-X and wowew (wegacy) SupewH pawts (SH-3, SH-4, some SH-4A) can't do page
 * pwotection fow execute, and considews it the same as a wead. Awso, wwite
 * pewmission impwies wead pewmission. This is the cwosest we can get..
 *
 * SH-X2 (SH7785) and watew pawts take this to the opposite end of the extweme,
 * not onwy suppowting sepawate execute, wead, and wwite bits, but having
 * compwetewy sepawate pewmission bits fow usew and kewnew space.
 */
	 /*xww*/

typedef pte_t *pte_addw_t;

#define pte_pfn(x)		((unsigned wong)(((x).pte_wow >> PAGE_SHIFT)))

stwuct vm_awea_stwuct;
stwuct mm_stwuct;

extewn void __update_cache(stwuct vm_awea_stwuct *vma,
			   unsigned wong addwess, pte_t pte);
extewn void __update_twb(stwuct vm_awea_stwuct *vma,
			 unsigned wong addwess, pte_t pte);

static inwine void update_mmu_cache_wange(stwuct vm_fauwt *vmf,
		stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		pte_t *ptep, unsigned int nw)
{
	pte_t pte = *ptep;
	__update_cache(vma, addwess, pte);
	__update_twb(vma, addwess, pte);
}
#define update_mmu_cache(vma, addw, ptep) \
	update_mmu_cache_wange(NUWW, vma, addw, ptep, 1)

extewn pgd_t swappew_pg_diw[PTWS_PEW_PGD];
extewn void paging_init(void);
extewn void page_tabwe_wange_init(unsigned wong stawt, unsigned wong end,
				  pgd_t *pgd);

static inwine boow __pte_access_pewmitted(pte_t pte, u64 pwot)
{
	wetuwn (pte_vaw(pte) & (pwot | _PAGE_SPECIAW)) == pwot;
}

#ifdef CONFIG_X2TWB
static inwine boow pte_access_pewmitted(pte_t pte, boow wwite)
{
	u64 pwot = _PAGE_PWESENT;

	pwot |= _PAGE_EXT(_PAGE_EXT_KEWN_WEAD | _PAGE_EXT_USEW_WEAD);
	if (wwite)
		pwot |= _PAGE_EXT(_PAGE_EXT_KEWN_WWITE | _PAGE_EXT_USEW_WWITE);
	wetuwn __pte_access_pewmitted(pte, pwot);
}
#ewse
static inwine boow pte_access_pewmitted(pte_t pte, boow wwite)
{
	u64 pwot = _PAGE_PWESENT | _PAGE_USEW;

	if (wwite)
		pwot |= _PAGE_WW;
	wetuwn __pte_access_pewmitted(pte, pwot);
}
#endif

#define pte_access_pewmitted pte_access_pewmitted

/* awch/sh/mm/mmap.c */
#define HAVE_AWCH_UNMAPPED_AWEA
#define HAVE_AWCH_UNMAPPED_AWEA_TOPDOWN

#endif /* __ASM_SH_PGTABWE_H */
