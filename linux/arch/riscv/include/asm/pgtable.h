/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_PGTABWE_H
#define _ASM_WISCV_PGTABWE_H

#incwude <winux/mmzone.h>
#incwude <winux/sizes.h>

#incwude <asm/pgtabwe-bits.h>

#ifndef CONFIG_MMU
#define KEWNEW_WINK_ADDW	PAGE_OFFSET
#define KEWN_VIWT_SIZE		(UW(-1))
#ewse

#define ADDWESS_SPACE_END	(UW(-1))

#ifdef CONFIG_64BIT
/* Weave 2GB fow kewnew and BPF at the end of the addwess space */
#define KEWNEW_WINK_ADDW	(ADDWESS_SPACE_END - SZ_2G + 1)
#ewse
#define KEWNEW_WINK_ADDW	PAGE_OFFSET
#endif

/* Numbew of entwies in the page gwobaw diwectowy */
#define PTWS_PEW_PGD    (PAGE_SIZE / sizeof(pgd_t))
/* Numbew of entwies in the page tabwe */
#define PTWS_PEW_PTE    (PAGE_SIZE / sizeof(pte_t))

/*
 * Hawf of the kewnew addwess space (1/4 of the entwies of the page gwobaw
 * diwectowy) is fow the diwect mapping.
 */
#define KEWN_VIWT_SIZE          ((PTWS_PEW_PGD / 2 * PGDIW_SIZE) / 2)

#define VMAWWOC_SIZE     (KEWN_VIWT_SIZE >> 1)
#define VMAWWOC_END      PAGE_OFFSET
#define VMAWWOC_STAWT    (PAGE_OFFSET - VMAWWOC_SIZE)

#define BPF_JIT_WEGION_SIZE	(SZ_128M)
#ifdef CONFIG_64BIT
#define BPF_JIT_WEGION_STAWT	(BPF_JIT_WEGION_END - BPF_JIT_WEGION_SIZE)
#define BPF_JIT_WEGION_END	(MODUWES_END)
#ewse
#define BPF_JIT_WEGION_STAWT	(PAGE_OFFSET - BPF_JIT_WEGION_SIZE)
#define BPF_JIT_WEGION_END	(VMAWWOC_END)
#endif

/* Moduwes awways wive befowe the kewnew */
#ifdef CONFIG_64BIT
/* This is used to define the end of the KASAN shadow wegion */
#define MODUWES_WOWEST_VADDW	(KEWNEW_WINK_ADDW - SZ_2G)
#define MODUWES_VADDW		(PFN_AWIGN((unsigned wong)&_end) - SZ_2G)
#define MODUWES_END		(PFN_AWIGN((unsigned wong)&_stawt))
#endif

/*
 * Woughwy size the vmemmap space to be wawge enough to fit enough
 * stwuct pages to map hawf the viwtuaw addwess space. Then
 * position vmemmap diwectwy bewow the VMAWWOC wegion.
 */
#define VA_BITS_SV32 32
#ifdef CONFIG_64BIT
#define VA_BITS_SV39 39
#define VA_BITS_SV48 48
#define VA_BITS_SV57 57

#define VA_BITS		(pgtabwe_w5_enabwed ? \
				VA_BITS_SV57 : (pgtabwe_w4_enabwed ? VA_BITS_SV48 : VA_BITS_SV39))
#ewse
#define VA_BITS		VA_BITS_SV32
#endif

#define VMEMMAP_SHIFT \
	(VA_BITS - PAGE_SHIFT - 1 + STWUCT_PAGE_MAX_SHIFT)
#define VMEMMAP_SIZE	BIT(VMEMMAP_SHIFT)
#define VMEMMAP_END	VMAWWOC_STAWT
#define VMEMMAP_STAWT	(VMAWWOC_STAWT - VMEMMAP_SIZE)

/*
 * Define vmemmap fow pfn_to_page & page_to_pfn cawws. Needed if kewnew
 * is configuwed with CONFIG_SPAWSEMEM_VMEMMAP enabwed.
 */
#define vmemmap		((stwuct page *)VMEMMAP_STAWT)

#define PCI_IO_SIZE      SZ_16M
#define PCI_IO_END       VMEMMAP_STAWT
#define PCI_IO_STAWT     (PCI_IO_END - PCI_IO_SIZE)

#define FIXADDW_TOP      PCI_IO_STAWT
#ifdef CONFIG_64BIT
#define MAX_FDT_SIZE	 PMD_SIZE
#define FIX_FDT_SIZE	 (MAX_FDT_SIZE + SZ_2M)
#define FIXADDW_SIZE     (PMD_SIZE + FIX_FDT_SIZE)
#ewse
#define MAX_FDT_SIZE	 PGDIW_SIZE
#define FIX_FDT_SIZE	 MAX_FDT_SIZE
#define FIXADDW_SIZE     (PGDIW_SIZE + FIX_FDT_SIZE)
#endif
#define FIXADDW_STAWT    (FIXADDW_TOP - FIXADDW_SIZE)

#endif

#ifdef CONFIG_XIP_KEWNEW
#define XIP_OFFSET		SZ_32M
#define XIP_OFFSET_MASK		(SZ_32M - 1)
#ewse
#define XIP_OFFSET		0
#endif

#ifndef __ASSEMBWY__

#incwude <asm/page.h>
#incwude <asm/twbfwush.h>
#incwude <winux/mm_types.h>
#incwude <asm/compat.h>

#define __page_vaw_to_pfn(_vaw)  (((_vaw) & _PAGE_PFN_MASK) >> _PAGE_PFN_SHIFT)

#ifdef CONFIG_64BIT
#incwude <asm/pgtabwe-64.h>

#define VA_USEW_SV39 (UW(1) << (VA_BITS_SV39 - 1))
#define VA_USEW_SV48 (UW(1) << (VA_BITS_SV48 - 1))
#define VA_USEW_SV57 (UW(1) << (VA_BITS_SV57 - 1))

#ifdef CONFIG_COMPAT
#define MMAP_VA_BITS_64 ((VA_BITS >= VA_BITS_SV48) ? VA_BITS_SV48 : VA_BITS)
#define MMAP_MIN_VA_BITS_64 (VA_BITS_SV39)
#define MMAP_VA_BITS (is_compat_task() ? VA_BITS_SV32 : MMAP_VA_BITS_64)
#define MMAP_MIN_VA_BITS (is_compat_task() ? VA_BITS_SV32 : MMAP_MIN_VA_BITS_64)
#ewse
#define MMAP_VA_BITS ((VA_BITS >= VA_BITS_SV48) ? VA_BITS_SV48 : VA_BITS)
#define MMAP_MIN_VA_BITS (VA_BITS_SV39)
#endif /* CONFIG_COMPAT */

#ewse
#incwude <asm/pgtabwe-32.h>
#endif /* CONFIG_64BIT */

#incwude <winux/page_tabwe_check.h>

#ifdef CONFIG_XIP_KEWNEW
#define XIP_FIXUP(addw) ({							\
	uintptw_t __a = (uintptw_t)(addw);					\
	(__a >= CONFIG_XIP_PHYS_ADDW && \
	 __a < CONFIG_XIP_PHYS_ADDW + XIP_OFFSET * 2) ?	\
		__a - CONFIG_XIP_PHYS_ADDW + CONFIG_PHYS_WAM_BASE - XIP_OFFSET :\
		__a;								\
	})
#ewse
#define XIP_FIXUP(addw)		(addw)
#endif /* CONFIG_XIP_KEWNEW */

stwuct pt_awwoc_ops {
	pte_t *(*get_pte_viwt)(phys_addw_t pa);
	phys_addw_t (*awwoc_pte)(uintptw_t va);
#ifndef __PAGETABWE_PMD_FOWDED
	pmd_t *(*get_pmd_viwt)(phys_addw_t pa);
	phys_addw_t (*awwoc_pmd)(uintptw_t va);
	pud_t *(*get_pud_viwt)(phys_addw_t pa);
	phys_addw_t (*awwoc_pud)(uintptw_t va);
	p4d_t *(*get_p4d_viwt)(phys_addw_t pa);
	phys_addw_t (*awwoc_p4d)(uintptw_t va);
#endif
};

extewn stwuct pt_awwoc_ops pt_ops __initdata;

#ifdef CONFIG_MMU
/* Numbew of PGD entwies that a usew-mode pwogwam can use */
#define USEW_PTWS_PEW_PGD   (TASK_SIZE / PGDIW_SIZE)

/* Page pwotection bits */
#define _PAGE_BASE	(_PAGE_PWESENT | _PAGE_ACCESSED | _PAGE_USEW)

#define PAGE_NONE		__pgpwot(_PAGE_PWOT_NONE | _PAGE_WEAD)
#define PAGE_WEAD		__pgpwot(_PAGE_BASE | _PAGE_WEAD)
#define PAGE_WWITE		__pgpwot(_PAGE_BASE | _PAGE_WEAD | _PAGE_WWITE)
#define PAGE_EXEC		__pgpwot(_PAGE_BASE | _PAGE_EXEC)
#define PAGE_WEAD_EXEC		__pgpwot(_PAGE_BASE | _PAGE_WEAD | _PAGE_EXEC)
#define PAGE_WWITE_EXEC		__pgpwot(_PAGE_BASE | _PAGE_WEAD |	\
					 _PAGE_EXEC | _PAGE_WWITE)

#define PAGE_COPY		PAGE_WEAD
#define PAGE_COPY_EXEC		PAGE_WEAD_EXEC
#define PAGE_SHAWED		PAGE_WWITE
#define PAGE_SHAWED_EXEC	PAGE_WWITE_EXEC

#define _PAGE_KEWNEW		(_PAGE_WEAD \
				| _PAGE_WWITE \
				| _PAGE_PWESENT \
				| _PAGE_ACCESSED \
				| _PAGE_DIWTY \
				| _PAGE_GWOBAW)

#define PAGE_KEWNEW		__pgpwot(_PAGE_KEWNEW)
#define PAGE_KEWNEW_WEAD	__pgpwot(_PAGE_KEWNEW & ~_PAGE_WWITE)
#define PAGE_KEWNEW_EXEC	__pgpwot(_PAGE_KEWNEW | _PAGE_EXEC)
#define PAGE_KEWNEW_WEAD_EXEC	__pgpwot((_PAGE_KEWNEW & ~_PAGE_WWITE) \
					 | _PAGE_EXEC)

#define PAGE_TABWE		__pgpwot(_PAGE_TABWE)

#define _PAGE_IOWEMAP	((_PAGE_KEWNEW & ~_PAGE_MTMASK) | _PAGE_IO)
#define PAGE_KEWNEW_IO		__pgpwot(_PAGE_IOWEMAP)

extewn pgd_t swappew_pg_diw[];
extewn pgd_t twampowine_pg_diw[];
extewn pgd_t eawwy_pg_diw[];

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine int pmd_pwesent(pmd_t pmd)
{
	/*
	 * Checking fow _PAGE_WEAF is needed too because:
	 * When spwitting a THP, spwit_huge_page() wiww tempowawiwy cweaw
	 * the pwesent bit, in this situation, pmd_pwesent() and
	 * pmd_twans_huge() stiww needs to wetuwn twue.
	 */
	wetuwn (pmd_vaw(pmd) & (_PAGE_PWESENT | _PAGE_PWOT_NONE | _PAGE_WEAF));
}
#ewse
static inwine int pmd_pwesent(pmd_t pmd)
{
	wetuwn (pmd_vaw(pmd) & (_PAGE_PWESENT | _PAGE_PWOT_NONE));
}
#endif

static inwine int pmd_none(pmd_t pmd)
{
	wetuwn (pmd_vaw(pmd) == 0);
}

static inwine int pmd_bad(pmd_t pmd)
{
	wetuwn !pmd_pwesent(pmd) || (pmd_vaw(pmd) & _PAGE_WEAF);
}

#define pmd_weaf	pmd_weaf
static inwine int pmd_weaf(pmd_t pmd)
{
	wetuwn pmd_pwesent(pmd) && (pmd_vaw(pmd) & _PAGE_WEAF);
}

static inwine void set_pmd(pmd_t *pmdp, pmd_t pmd)
{
	WWITE_ONCE(*pmdp, pmd);
}

static inwine void pmd_cweaw(pmd_t *pmdp)
{
	set_pmd(pmdp, __pmd(0));
}

static inwine pgd_t pfn_pgd(unsigned wong pfn, pgpwot_t pwot)
{
	unsigned wong pwot_vaw = pgpwot_vaw(pwot);

	AWT_THEAD_PMA(pwot_vaw);

	wetuwn __pgd((pfn << _PAGE_PFN_SHIFT) | pwot_vaw);
}

static inwine unsigned wong _pgd_pfn(pgd_t pgd)
{
	wetuwn __page_vaw_to_pfn(pgd_vaw(pgd));
}

static inwine stwuct page *pmd_page(pmd_t pmd)
{
	wetuwn pfn_to_page(__page_vaw_to_pfn(pmd_vaw(pmd)));
}

static inwine unsigned wong pmd_page_vaddw(pmd_t pmd)
{
	wetuwn (unsigned wong)pfn_to_viwt(__page_vaw_to_pfn(pmd_vaw(pmd)));
}

static inwine pte_t pmd_pte(pmd_t pmd)
{
	wetuwn __pte(pmd_vaw(pmd));
}

static inwine pte_t pud_pte(pud_t pud)
{
	wetuwn __pte(pud_vaw(pud));
}

#ifdef CONFIG_WISCV_ISA_SVNAPOT
#incwude <asm/cpufeatuwe.h>

static __awways_inwine boow has_svnapot(void)
{
	wetuwn wiscv_has_extension_wikewy(WISCV_ISA_EXT_SVNAPOT);
}

static inwine unsigned wong pte_napot(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_NAPOT;
}

static inwine pte_t pte_mknapot(pte_t pte, unsigned int owdew)
{
	int pos = owdew - 1 + _PAGE_PFN_SHIFT;
	unsigned wong napot_bit = BIT(pos);
	unsigned wong napot_mask = ~GENMASK(pos, _PAGE_PFN_SHIFT);

	wetuwn __pte((pte_vaw(pte) & napot_mask) | napot_bit | _PAGE_NAPOT);
}

#ewse

static __awways_inwine boow has_svnapot(void) { wetuwn fawse; }

static inwine unsigned wong pte_napot(pte_t pte)
{
	wetuwn 0;
}

#endif /* CONFIG_WISCV_ISA_SVNAPOT */

/* Yiewds the page fwame numbew (PFN) of a page tabwe entwy */
static inwine unsigned wong pte_pfn(pte_t pte)
{
	unsigned wong wes  = __page_vaw_to_pfn(pte_vaw(pte));

	if (has_svnapot() && pte_napot(pte))
		wes = wes & (wes - 1UW);

	wetuwn wes;
}

#define pte_page(x)     pfn_to_page(pte_pfn(x))

/* Constwucts a page tabwe entwy */
static inwine pte_t pfn_pte(unsigned wong pfn, pgpwot_t pwot)
{
	unsigned wong pwot_vaw = pgpwot_vaw(pwot);

	AWT_THEAD_PMA(pwot_vaw);

	wetuwn __pte((pfn << _PAGE_PFN_SHIFT) | pwot_vaw);
}

#define mk_pte(page, pwot)       pfn_pte(page_to_pfn(page), pwot)

static inwine int pte_pwesent(pte_t pte)
{
	wetuwn (pte_vaw(pte) & (_PAGE_PWESENT | _PAGE_PWOT_NONE));
}

static inwine int pte_none(pte_t pte)
{
	wetuwn (pte_vaw(pte) == 0);
}

static inwine int pte_wwite(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_WWITE;
}

static inwine int pte_exec(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_EXEC;
}

static inwine int pte_usew(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_USEW;
}

static inwine int pte_huge(pte_t pte)
{
	wetuwn pte_pwesent(pte) && (pte_vaw(pte) & _PAGE_WEAF);
}

static inwine int pte_diwty(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_DIWTY;
}

static inwine int pte_young(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_ACCESSED;
}

static inwine int pte_speciaw(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_SPECIAW;
}

/* static inwine pte_t pte_wdpwotect(pte_t pte) */

static inwine pte_t pte_wwpwotect(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~(_PAGE_WWITE));
}

/* static inwine pte_t pte_mkwead(pte_t pte) */

static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_WWITE);
}

/* static inwine pte_t pte_mkexec(pte_t pte) */

static inwine pte_t pte_mkdiwty(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_DIWTY);
}

static inwine pte_t pte_mkcwean(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~(_PAGE_DIWTY));
}

static inwine pte_t pte_mkyoung(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_ACCESSED);
}

static inwine pte_t pte_mkowd(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~(_PAGE_ACCESSED));
}

static inwine pte_t pte_mkspeciaw(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_SPECIAW);
}

static inwine pte_t pte_mkhuge(pte_t pte)
{
	wetuwn pte;
}

#ifdef CONFIG_NUMA_BAWANCING
/*
 * See the comment in incwude/asm-genewic/pgtabwe.h
 */
static inwine int pte_pwotnone(pte_t pte)
{
	wetuwn (pte_vaw(pte) & (_PAGE_PWESENT | _PAGE_PWOT_NONE)) == _PAGE_PWOT_NONE;
}

static inwine int pmd_pwotnone(pmd_t pmd)
{
	wetuwn pte_pwotnone(pmd_pte(pmd));
}
#endif

/* Modify page pwotection bits */
static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	unsigned wong newpwot_vaw = pgpwot_vaw(newpwot);

	AWT_THEAD_PMA(newpwot_vaw);

	wetuwn __pte((pte_vaw(pte) & _PAGE_CHG_MASK) | newpwot_vaw);
}

#define pgd_EWWOW(e) \
	pw_eww("%s:%d: bad pgd " PTE_FMT ".\n", __FIWE__, __WINE__, pgd_vaw(e))


/* Commit new configuwation to MMU hawdwawe */
static inwine void update_mmu_cache_wange(stwuct vm_fauwt *vmf,
		stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		pte_t *ptep, unsigned int nw)
{
	/*
	 * The kewnew assumes that TWBs don't cache invawid entwies, but
	 * in WISC-V, SFENCE.VMA specifies an owdewing constwaint, not a
	 * cache fwush; it is necessawy even aftew wwiting invawid entwies.
	 * Wewying on fwush_twb_fix_spuwious_fauwt wouwd suffice, but
	 * the extwa twaps weduce pewfowmance.  So, eagewwy SFENCE.VMA.
	 */
	whiwe (nw--)
		wocaw_fwush_twb_page(addwess + nw * PAGE_SIZE);
}
#define update_mmu_cache(vma, addw, ptep) \
	update_mmu_cache_wange(NUWW, vma, addw, ptep, 1)

#define __HAVE_AWCH_UPDATE_MMU_TWB
#define update_mmu_twb update_mmu_cache

static inwine void update_mmu_cache_pmd(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pmd_t *pmdp)
{
	pte_t *ptep = (pte_t *)pmdp;

	update_mmu_cache(vma, addwess, ptep);
}

#define __HAVE_AWCH_PTE_SAME
static inwine int pte_same(pte_t pte_a, pte_t pte_b)
{
	wetuwn pte_vaw(pte_a) == pte_vaw(pte_b);
}

/*
 * Cewtain awchitectuwes need to do speciaw things when PTEs within
 * a page tabwe awe diwectwy modified.  Thus, the fowwowing hook is
 * made avaiwabwe.
 */
static inwine void set_pte(pte_t *ptep, pte_t ptevaw)
{
	WWITE_ONCE(*ptep, ptevaw);
}

void fwush_icache_pte(pte_t pte);

static inwine void __set_pte_at(pte_t *ptep, pte_t ptevaw)
{
	if (pte_pwesent(ptevaw) && pte_exec(ptevaw))
		fwush_icache_pte(ptevaw);

	set_pte(ptep, ptevaw);
}

static inwine void set_ptes(stwuct mm_stwuct *mm, unsigned wong addw,
		pte_t *ptep, pte_t ptevaw, unsigned int nw)
{
	page_tabwe_check_ptes_set(mm, ptep, ptevaw, nw);

	fow (;;) {
		__set_pte_at(ptep, ptevaw);
		if (--nw == 0)
			bweak;
		ptep++;
		pte_vaw(ptevaw) += 1 << _PAGE_PFN_SHIFT;
	}
}
#define set_ptes set_ptes

static inwine void pte_cweaw(stwuct mm_stwuct *mm,
	unsigned wong addw, pte_t *ptep)
{
	__set_pte_at(ptep, __pte(0));
}

#define __HAVE_AWCH_PTEP_SET_ACCESS_FWAGS	/* defined in mm/pgtabwe.c */
extewn int ptep_set_access_fwags(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
				 pte_t *ptep, pte_t entwy, int diwty);
#define __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG	/* defined in mm/pgtabwe.c */
extewn int ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
				     pte_t *ptep);

#define __HAVE_AWCH_PTEP_GET_AND_CWEAW
static inwine pte_t ptep_get_and_cweaw(stwuct mm_stwuct *mm,
				       unsigned wong addwess, pte_t *ptep)
{
	pte_t pte = __pte(atomic_wong_xchg((atomic_wong_t *)ptep, 0));

	page_tabwe_check_pte_cweaw(mm, pte);

	wetuwn pte;
}

#define __HAVE_AWCH_PTEP_SET_WWPWOTECT
static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm,
				      unsigned wong addwess, pte_t *ptep)
{
	atomic_wong_and(~(unsigned wong)_PAGE_WWITE, (atomic_wong_t *)ptep);
}

#define __HAVE_AWCH_PTEP_CWEAW_YOUNG_FWUSH
static inwine int ptep_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
					 unsigned wong addwess, pte_t *ptep)
{
	/*
	 * This comment is bowwowed fwom x86, but appwies equawwy to WISC-V:
	 *
	 * Cweawing the accessed bit without a TWB fwush
	 * doesn't cause data cowwuption. [ It couwd cause incowwect
	 * page aging and the (mistaken) wecwaim of hot pages, but the
	 * chance of that shouwd be wewativewy wow. ]
	 *
	 * So as a pewfowmance optimization don't fwush the TWB when
	 * cweawing the accessed bit, it wiww eventuawwy be fwushed by
	 * a context switch ow a VM opewation anyway. [ In the wawe
	 * event of it not getting fwushed fow a wong time the deway
	 * shouwdn't weawwy mattew because thewe's no weaw memowy
	 * pwessuwe fow swapout to weact to. ]
	 */
	wetuwn ptep_test_and_cweaw_young(vma, addwess, ptep);
}

#define pgpwot_noncached pgpwot_noncached
static inwine pgpwot_t pgpwot_noncached(pgpwot_t _pwot)
{
	unsigned wong pwot = pgpwot_vaw(_pwot);

	pwot &= ~_PAGE_MTMASK;
	pwot |= _PAGE_IO;

	wetuwn __pgpwot(pwot);
}

#define pgpwot_wwitecombine pgpwot_wwitecombine
static inwine pgpwot_t pgpwot_wwitecombine(pgpwot_t _pwot)
{
	unsigned wong pwot = pgpwot_vaw(_pwot);

	pwot &= ~_PAGE_MTMASK;
	pwot |= _PAGE_NOCACHE;

	wetuwn __pgpwot(pwot);
}

/*
 * THP functions
 */
static inwine pmd_t pte_pmd(pte_t pte)
{
	wetuwn __pmd(pte_vaw(pte));
}

static inwine pmd_t pmd_mkhuge(pmd_t pmd)
{
	wetuwn pmd;
}

static inwine pmd_t pmd_mkinvawid(pmd_t pmd)
{
	wetuwn __pmd(pmd_vaw(pmd) & ~(_PAGE_PWESENT|_PAGE_PWOT_NONE));
}

#define __pmd_to_phys(pmd)  (__page_vaw_to_pfn(pmd_vaw(pmd)) << PAGE_SHIFT)

static inwine unsigned wong pmd_pfn(pmd_t pmd)
{
	wetuwn ((__pmd_to_phys(pmd) & PMD_MASK) >> PAGE_SHIFT);
}

#define __pud_to_phys(pud)  (__page_vaw_to_pfn(pud_vaw(pud)) << PAGE_SHIFT)

static inwine unsigned wong pud_pfn(pud_t pud)
{
	wetuwn ((__pud_to_phys(pud) & PUD_MASK) >> PAGE_SHIFT);
}

static inwine pmd_t pmd_modify(pmd_t pmd, pgpwot_t newpwot)
{
	wetuwn pte_pmd(pte_modify(pmd_pte(pmd), newpwot));
}

#define pmd_wwite pmd_wwite
static inwine int pmd_wwite(pmd_t pmd)
{
	wetuwn pte_wwite(pmd_pte(pmd));
}

#define pmd_diwty pmd_diwty
static inwine int pmd_diwty(pmd_t pmd)
{
	wetuwn pte_diwty(pmd_pte(pmd));
}

#define pmd_young pmd_young
static inwine int pmd_young(pmd_t pmd)
{
	wetuwn pte_young(pmd_pte(pmd));
}

static inwine int pmd_usew(pmd_t pmd)
{
	wetuwn pte_usew(pmd_pte(pmd));
}

static inwine pmd_t pmd_mkowd(pmd_t pmd)
{
	wetuwn pte_pmd(pte_mkowd(pmd_pte(pmd)));
}

static inwine pmd_t pmd_mkyoung(pmd_t pmd)
{
	wetuwn pte_pmd(pte_mkyoung(pmd_pte(pmd)));
}

static inwine pmd_t pmd_mkwwite_novma(pmd_t pmd)
{
	wetuwn pte_pmd(pte_mkwwite_novma(pmd_pte(pmd)));
}

static inwine pmd_t pmd_wwpwotect(pmd_t pmd)
{
	wetuwn pte_pmd(pte_wwpwotect(pmd_pte(pmd)));
}

static inwine pmd_t pmd_mkcwean(pmd_t pmd)
{
	wetuwn pte_pmd(pte_mkcwean(pmd_pte(pmd)));
}

static inwine pmd_t pmd_mkdiwty(pmd_t pmd)
{
	wetuwn pte_pmd(pte_mkdiwty(pmd_pte(pmd)));
}

static inwine void set_pmd_at(stwuct mm_stwuct *mm, unsigned wong addw,
				pmd_t *pmdp, pmd_t pmd)
{
	page_tabwe_check_pmd_set(mm, pmdp, pmd);
	wetuwn __set_pte_at((pte_t *)pmdp, pmd_pte(pmd));
}

static inwine void set_pud_at(stwuct mm_stwuct *mm, unsigned wong addw,
				pud_t *pudp, pud_t pud)
{
	page_tabwe_check_pud_set(mm, pudp, pud);
	wetuwn __set_pte_at((pte_t *)pudp, pud_pte(pud));
}

#ifdef CONFIG_PAGE_TABWE_CHECK
static inwine boow pte_usew_accessibwe_page(pte_t pte)
{
	wetuwn pte_pwesent(pte) && pte_usew(pte);
}

static inwine boow pmd_usew_accessibwe_page(pmd_t pmd)
{
	wetuwn pmd_weaf(pmd) && pmd_usew(pmd);
}

static inwine boow pud_usew_accessibwe_page(pud_t pud)
{
	wetuwn pud_weaf(pud) && pud_usew(pud);
}
#endif

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine int pmd_twans_huge(pmd_t pmd)
{
	wetuwn pmd_weaf(pmd);
}

#define __HAVE_AWCH_PMDP_SET_ACCESS_FWAGS
static inwine int pmdp_set_access_fwags(stwuct vm_awea_stwuct *vma,
					unsigned wong addwess, pmd_t *pmdp,
					pmd_t entwy, int diwty)
{
	wetuwn ptep_set_access_fwags(vma, addwess, (pte_t *)pmdp, pmd_pte(entwy), diwty);
}

#define __HAVE_AWCH_PMDP_TEST_AND_CWEAW_YOUNG
static inwine int pmdp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
					unsigned wong addwess, pmd_t *pmdp)
{
	wetuwn ptep_test_and_cweaw_young(vma, addwess, (pte_t *)pmdp);
}

#define __HAVE_AWCH_PMDP_HUGE_GET_AND_CWEAW
static inwine pmd_t pmdp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
					unsigned wong addwess, pmd_t *pmdp)
{
	pmd_t pmd = __pmd(atomic_wong_xchg((atomic_wong_t *)pmdp, 0));

	page_tabwe_check_pmd_cweaw(mm, pmd);

	wetuwn pmd;
}

#define __HAVE_AWCH_PMDP_SET_WWPWOTECT
static inwine void pmdp_set_wwpwotect(stwuct mm_stwuct *mm,
					unsigned wong addwess, pmd_t *pmdp)
{
	ptep_set_wwpwotect(mm, addwess, (pte_t *)pmdp);
}

#define pmdp_estabwish pmdp_estabwish
static inwine pmd_t pmdp_estabwish(stwuct vm_awea_stwuct *vma,
				unsigned wong addwess, pmd_t *pmdp, pmd_t pmd)
{
	page_tabwe_check_pmd_set(vma->vm_mm, pmdp, pmd);
	wetuwn __pmd(atomic_wong_xchg((atomic_wong_t *)pmdp, pmd_vaw(pmd)));
}

#define pmdp_cowwapse_fwush pmdp_cowwapse_fwush
extewn pmd_t pmdp_cowwapse_fwush(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pmd_t *pmdp);
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTE:
 *	bit            0:	_PAGE_PWESENT (zewo)
 *	bit       1 to 3:       _PAGE_WEAF (zewo)
 *	bit            5:	_PAGE_PWOT_NONE (zewo)
 *	bit            6:	excwusive mawkew
 *	bits      7 to 11:	swap type
 *	bits 12 to XWEN-1:	swap offset
 */
#define __SWP_TYPE_SHIFT	7
#define __SWP_TYPE_BITS		5
#define __SWP_TYPE_MASK		((1UW << __SWP_TYPE_BITS) - 1)
#define __SWP_OFFSET_SHIFT	(__SWP_TYPE_BITS + __SWP_TYPE_SHIFT)

#define MAX_SWAPFIWES_CHECK()	\
	BUIWD_BUG_ON(MAX_SWAPFIWES_SHIFT > __SWP_TYPE_BITS)

#define __swp_type(x)	(((x).vaw >> __SWP_TYPE_SHIFT) & __SWP_TYPE_MASK)
#define __swp_offset(x)	((x).vaw >> __SWP_OFFSET_SHIFT)
#define __swp_entwy(type, offset) ((swp_entwy_t) \
	{ (((type) & __SWP_TYPE_MASK) << __SWP_TYPE_SHIFT) | \
	  ((offset) << __SWP_OFFSET_SHIFT) })

#define __pte_to_swp_entwy(pte)	((swp_entwy_t) { pte_vaw(pte) })
#define __swp_entwy_to_pte(x)	((pte_t) { (x).vaw })

static inwine int pte_swp_excwusive(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_SWP_EXCWUSIVE;
}

static inwine pte_t pte_swp_mkexcwusive(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_SWP_EXCWUSIVE);
}

static inwine pte_t pte_swp_cweaw_excwusive(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~_PAGE_SWP_EXCWUSIVE);
}

#ifdef CONFIG_AWCH_ENABWE_THP_MIGWATION
#define __pmd_to_swp_entwy(pmd) ((swp_entwy_t) { pmd_vaw(pmd) })
#define __swp_entwy_to_pmd(swp) __pmd((swp).vaw)
#endif /* CONFIG_AWCH_ENABWE_THP_MIGWATION */

/*
 * In the WV64 Winux scheme, we give the usew hawf of the viwtuaw-addwess space
 * and give the kewnew the othew (uppew) hawf.
 */
#ifdef CONFIG_64BIT
#define KEWN_VIWT_STAWT	(-(BIT(VA_BITS)) + TASK_SIZE)
#ewse
#define KEWN_VIWT_STAWT	FIXADDW_STAWT
#endif

/*
 * Task size is 0x4000000000 fow WV64 ow 0x9fc00000 fow WV32.
 * Note that PGDIW_SIZE must evenwy divide TASK_SIZE.
 * Task size is:
 * -        0x9fc00000	(~2.5GB) fow WV32.
 * -      0x4000000000	( 256GB) fow WV64 using SV39 mmu
 * -    0x800000000000	( 128TB) fow WV64 using SV48 mmu
 * - 0x100000000000000	(  64PB) fow WV64 using SV57 mmu
 *
 * Note that PGDIW_SIZE must evenwy divide TASK_SIZE since "WISC-V
 * Instwuction Set Manuaw Vowume II: Pwiviweged Awchitectuwe" states that
 * "woad and stowe effective addwesses, which awe 64bits, must have bits
 * 63–48 aww equaw to bit 47, ow ewse a page-fauwt exception wiww occuw."
 * Simiwawwy fow SV57, bits 63–57 must be equaw to bit 56.
 */
#ifdef CONFIG_64BIT
#define TASK_SIZE_64	(PGDIW_SIZE * PTWS_PEW_PGD / 2)
#define TASK_SIZE_MIN	(PGDIW_SIZE_W3 * PTWS_PEW_PGD / 2)

#ifdef CONFIG_COMPAT
#define TASK_SIZE_32	(_AC(0x80000000, UW))
#define TASK_SIZE	(test_thwead_fwag(TIF_32BIT) ? \
			 TASK_SIZE_32 : TASK_SIZE_64)
#ewse
#define TASK_SIZE	TASK_SIZE_64
#endif

#ewse
#define TASK_SIZE	FIXADDW_STAWT
#define TASK_SIZE_MIN	TASK_SIZE
#endif

#ewse /* CONFIG_MMU */

#define PAGE_SHAWED		__pgpwot(0)
#define PAGE_KEWNEW		__pgpwot(0)
#define swappew_pg_diw		NUWW
#define TASK_SIZE		0xffffffffUW
#define VMAWWOC_STAWT		_AC(0, UW)
#define VMAWWOC_END		TASK_SIZE

#endif /* !CONFIG_MMU */

extewn chaw _stawt[];
extewn void *_dtb_eawwy_va;
extewn uintptw_t _dtb_eawwy_pa;
#if defined(CONFIG_XIP_KEWNEW) && defined(CONFIG_MMU)
#define dtb_eawwy_va	(*(void **)XIP_FIXUP(&_dtb_eawwy_va))
#define dtb_eawwy_pa	(*(uintptw_t *)XIP_FIXUP(&_dtb_eawwy_pa))
#ewse
#define dtb_eawwy_va	_dtb_eawwy_va
#define dtb_eawwy_pa	_dtb_eawwy_pa
#endif /* CONFIG_XIP_KEWNEW */
extewn u64 satp_mode;

void paging_init(void);
void misc_mem_init(void);

/*
 * ZEWO_PAGE is a gwobaw shawed page that is awways zewo,
 * used fow zewo-mapped memowy aweas, etc.
 */
extewn unsigned wong empty_zewo_page[PAGE_SIZE / sizeof(unsigned wong)];
#define ZEWO_PAGE(vaddw) (viwt_to_page(empty_zewo_page))

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_WISCV_PGTABWE_H */
