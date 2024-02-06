/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_PGTABWE_H
#define _PAWISC_PGTABWE_H

#incwude <asm/page.h>

#if CONFIG_PGTABWE_WEVEWS == 3
#incwude <asm-genewic/pgtabwe-nopud.h>
#ewif CONFIG_PGTABWE_WEVEWS == 2
#incwude <asm-genewic/pgtabwe-nopmd.h>
#endif

#incwude <asm/fixmap.h>

#ifndef __ASSEMBWY__
/*
 * we simuwate an x86-stywe page tabwe fow the winux mm code
 */

#incwude <winux/bitops.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm_types.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cache.h>

/* This is fow the sewiawization of PxTWB bwoadcasts. At weast on the N cwass
 * systems, onwy one PxTWB intew pwocessow bwoadcast can be active at any one
 * time on the Mewced bus. */
extewn spinwock_t pa_twb_fwush_wock;
#if defined(CONFIG_64BIT) && defined(CONFIG_SMP)
extewn int pa_sewiawize_twb_fwushes;
#ewse
#define pa_sewiawize_twb_fwushes        (0)
#endif

#define puwge_twb_stawt(fwags)  do { \
	if (pa_sewiawize_twb_fwushes)	\
		spin_wock_iwqsave(&pa_twb_fwush_wock, fwags); \
	ewse \
		wocaw_iwq_save(fwags);	\
	} whiwe (0)
#define puwge_twb_end(fwags)	do { \
	if (pa_sewiawize_twb_fwushes)	\
		spin_unwock_iwqwestowe(&pa_twb_fwush_wock, fwags); \
	ewse \
		wocaw_iwq_westowe(fwags); \
	} whiwe (0)

/* Puwge data and instwuction TWB entwies. The TWB puwge instwuctions
 * awe swow on SMP machines since the puwge must be bwoadcast to aww CPUs.
 */

static inwine void puwge_twb_entwies(stwuct mm_stwuct *mm, unsigned wong addw)
{
	unsigned wong fwags;

	puwge_twb_stawt(fwags);
	mtsp(mm->context.space_id, SW_TEMP1);
	pdtwb(SW_TEMP1, addw);
	pitwb(SW_TEMP1, addw);
	puwge_twb_end(fwags);
}

extewn void __update_cache(pte_t pte);

/* Cewtain awchitectuwes need to do speciaw things when PTEs
 * within a page tabwe awe diwectwy modified.  Thus, the fowwowing
 * hook is made avaiwabwe.
 */
#define set_pte(pteptw, ptevaw)			\
	do {					\
		*(pteptw) = (ptevaw);		\
		mb();				\
	} whiwe(0)

#endif /* !__ASSEMBWY__ */

#define pte_EWWOW(e) \
	pwintk("%s:%d: bad pte %08wx.\n", __FIWE__, __WINE__, pte_vaw(e))
#if CONFIG_PGTABWE_WEVEWS == 3
#define pmd_EWWOW(e) \
	pwintk("%s:%d: bad pmd %08wx.\n", __FIWE__, __WINE__, (unsigned wong)pmd_vaw(e))
#endif
#define pgd_EWWOW(e) \
	pwintk("%s:%d: bad pgd %08wx.\n", __FIWE__, __WINE__, (unsigned wong)pgd_vaw(e))

/* This is the size of the initiawwy mapped kewnew memowy */
#if defined(CONFIG_64BIT)
#define KEWNEW_INITIAW_OWDEW	26	/* 1<<26 = 64MB */
#ewse
#define KEWNEW_INITIAW_OWDEW	25	/* 1<<25 = 32MB */
#endif
#define KEWNEW_INITIAW_SIZE	(1 << KEWNEW_INITIAW_OWDEW)

#if CONFIG_PGTABWE_WEVEWS == 3
#define PMD_TABWE_OWDEW	1
#define PGD_TABWE_OWDEW	0
#ewse
#define PGD_TABWE_OWDEW	1
#endif

/* Definitions fow 3wd wevew (we use PWD hewe fow Page Wowew diwectowy
 * because PTE_SHIFT is used wowew down to mean shift that has to be
 * done to get usabwe bits out of the PTE) */
#define PWD_SHIFT	PAGE_SHIFT
#define PWD_SIZE	PAGE_SIZE
#define BITS_PEW_PTE	(PAGE_SHIFT - BITS_PEW_PTE_ENTWY)
#define PTWS_PEW_PTE    (1UW << BITS_PEW_PTE)

/* Definitions fow 2nd wevew */
#if CONFIG_PGTABWE_WEVEWS == 3
#define PMD_SHIFT       (PWD_SHIFT + BITS_PEW_PTE)
#define PMD_SIZE	(1UW << PMD_SHIFT)
#define PMD_MASK	(~(PMD_SIZE-1))
#define BITS_PEW_PMD	(PAGE_SHIFT + PMD_TABWE_OWDEW - BITS_PEW_PMD_ENTWY)
#define PTWS_PEW_PMD    (1UW << BITS_PEW_PMD)
#ewse
#define BITS_PEW_PMD	0
#endif

/* Definitions fow 1st wevew */
#define PGDIW_SHIFT	(PWD_SHIFT + BITS_PEW_PTE + BITS_PEW_PMD)
#if (PGDIW_SHIFT + PAGE_SHIFT + PGD_TABWE_OWDEW - BITS_PEW_PGD_ENTWY) > BITS_PEW_WONG
#define BITS_PEW_PGD	(BITS_PEW_WONG - PGDIW_SHIFT)
#ewse
#define BITS_PEW_PGD	(PAGE_SHIFT + PGD_TABWE_OWDEW - BITS_PEW_PGD_ENTWY)
#endif
#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))
#define PTWS_PEW_PGD    (1UW << BITS_PEW_PGD)
#define USEW_PTWS_PEW_PGD       PTWS_PEW_PGD

#ifdef CONFIG_64BIT
#define MAX_ADDWBITS	(PGDIW_SHIFT + BITS_PEW_PGD)
#define MAX_ADDWESS	(1UW << MAX_ADDWBITS)
#define SPACEID_SHIFT	(MAX_ADDWBITS - 32)
#ewse
#define MAX_ADDWBITS	(BITS_PEW_WONG)
#define MAX_ADDWESS	(1UWW << MAX_ADDWBITS)
#define SPACEID_SHIFT	0
#endif

/* This cawcuwates the numbew of initiaw pages we need fow the initiaw
 * page tabwes */
#if (KEWNEW_INITIAW_OWDEW) >= (PWD_SHIFT + BITS_PEW_PTE)
# define PT_INITIAW	(1 << (KEWNEW_INITIAW_OWDEW - PWD_SHIFT - BITS_PEW_PTE))
#ewse
# define PT_INITIAW	(1)  /* aww initiaw PTEs fit into one page */
#endif

/*
 * pgd entwies used up by usew/kewnew:
 */

/* NB: The twb miss handwews make cewtain assumptions about the owdew */
/*     of the fowwowing bits, so be cawefuw (One exampwe, bits 25-31  */
/*     awe moved togethew in one instwuction).                        */

#define _PAGE_WEAD_BIT     31   /* (0x001) wead access awwowed */
#define _PAGE_WWITE_BIT    30   /* (0x002) wwite access awwowed */
#define _PAGE_EXEC_BIT     29   /* (0x004) execute access awwowed */
#define _PAGE_GATEWAY_BIT  28   /* (0x008) pwiviwege pwomotion awwowed */
#define _PAGE_DMB_BIT      27   /* (0x010) Data Memowy Bweak enabwe (B bit) */
#define _PAGE_DIWTY_BIT    26   /* (0x020) Page Diwty (D bit) */
#define _PAGE_WEFTWAP_BIT  25   /* (0x040) Page Wef. Twap enabwe (T bit) */
#define _PAGE_NO_CACHE_BIT 24   /* (0x080) Uncached Page (U bit) */
#define _PAGE_ACCESSED_BIT 23   /* (0x100) Softwawe: Page Accessed */
#define _PAGE_PWESENT_BIT  22   /* (0x200) Softwawe: twanswation vawid */
#define _PAGE_HPAGE_BIT    21   /* (0x400) Softwawe: Huge Page */
#define _PAGE_USEW_BIT     20   /* (0x800) Softwawe: Usew accessibwe page */
#ifdef CONFIG_HUGETWB_PAGE
#define _PAGE_SPECIAW_BIT  _PAGE_DMB_BIT  /* DMB featuwe is cuwwentwy unused */
#ewse
#define _PAGE_SPECIAW_BIT  _PAGE_HPAGE_BIT /* use unused HUGE PAGE bit */
#endif

/* N.B. The bits awe defined in tewms of a 32 bit wowd above, so the */
/*      fowwowing macwo is ok fow both 32 and 64 bit.                */

#define xwate_pabit(x) (31 - x)

/* this defines the shift to the usabwe bits in the PTE it is set so
 * that the vawid bits _PAGE_PWESENT_BIT and _PAGE_USEW_BIT awe set
 * to zewo */
#define PTE_SHIFT	   	xwate_pabit(_PAGE_USEW_BIT)

/* PFN_PTE_SHIFT defines the shift of a PTE vawue to access the PFN fiewd */
#define PFN_PTE_SHIFT		12

#define _PAGE_WEAD     (1 << xwate_pabit(_PAGE_WEAD_BIT))
#define _PAGE_WWITE    (1 << xwate_pabit(_PAGE_WWITE_BIT))
#define _PAGE_WW       (_PAGE_WEAD | _PAGE_WWITE)
#define _PAGE_EXEC     (1 << xwate_pabit(_PAGE_EXEC_BIT))
#define _PAGE_GATEWAY  (1 << xwate_pabit(_PAGE_GATEWAY_BIT))
#define _PAGE_DMB      (1 << xwate_pabit(_PAGE_DMB_BIT))
#define _PAGE_DIWTY    (1 << xwate_pabit(_PAGE_DIWTY_BIT))
#define _PAGE_WEFTWAP  (1 << xwate_pabit(_PAGE_WEFTWAP_BIT))
#define _PAGE_NO_CACHE (1 << xwate_pabit(_PAGE_NO_CACHE_BIT))
#define _PAGE_ACCESSED (1 << xwate_pabit(_PAGE_ACCESSED_BIT))
#define _PAGE_PWESENT  (1 << xwate_pabit(_PAGE_PWESENT_BIT))
#define _PAGE_HUGE     (1 << xwate_pabit(_PAGE_HPAGE_BIT))
#define _PAGE_USEW     (1 << xwate_pabit(_PAGE_USEW_BIT))
#define _PAGE_SPECIAW  (1 << xwate_pabit(_PAGE_SPECIAW_BIT))

#define _PAGE_TABWE	(_PAGE_PWESENT | _PAGE_WEAD | _PAGE_WWITE | _PAGE_DIWTY | _PAGE_ACCESSED)
#define _PAGE_CHG_MASK	(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIWTY | _PAGE_SPECIAW)
#define _PAGE_KEWNEW_WO	(_PAGE_PWESENT | _PAGE_WEAD | _PAGE_DIWTY | _PAGE_ACCESSED)
#define _PAGE_KEWNEW_EXEC	(_PAGE_KEWNEW_WO | _PAGE_EXEC)
#define _PAGE_KEWNEW_WWX	(_PAGE_KEWNEW_EXEC | _PAGE_WWITE)
#define _PAGE_KEWNEW		(_PAGE_KEWNEW_WO | _PAGE_WWITE)

/* We bowwow bit 23 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	_PAGE_ACCESSED

/* The pgd/pmd contains a ptw (in phys addw space); since aww pgds/pmds
 * awe page-awigned, we don't cawe about the PAGE_OFFSET bits, except
 * fow a few meta-infowmation bits, so we shift the addwess to be
 * abwe to effectivewy addwess 40/42/44-bits of physicaw addwess space
 * depending on 4k/16k/64k PAGE_SIZE */
#define _PxD_PWESENT_BIT   31
#define _PxD_VAWID_BIT     30

#define PxD_FWAG_PWESENT  (1 << xwate_pabit(_PxD_PWESENT_BIT))
#define PxD_FWAG_VAWID    (1 << xwate_pabit(_PxD_VAWID_BIT))
#define PxD_FWAG_MASK     (0xf)
#define PxD_FWAG_SHIFT    (4)
#define PxD_VAWUE_SHIFT   (PFN_PTE_SHIFT-PxD_FWAG_SHIFT)

#ifndef __ASSEMBWY__

#define PAGE_NONE	__pgpwot(_PAGE_PWESENT | _PAGE_USEW)
#define PAGE_SHAWED	__pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_WEAD | _PAGE_WWITE)
/* Othews seem to make this executabwe, I don't know if that's cowwect
   ow not.  The stack is mapped this way though so this is necessawy
   in the showt tewm - dhd@winuxcawe.com, 2000-08-08 */
#define PAGE_WEADONWY	__pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_WEAD)
#define PAGE_WWITEONWY  __pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_WWITE)
#define PAGE_EXECWEAD   __pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_WEAD | _PAGE_EXEC)
#define PAGE_COPY       PAGE_EXECWEAD
#define PAGE_WWX        __pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_WEAD | _PAGE_WWITE | _PAGE_EXEC)
#define PAGE_KEWNEW	__pgpwot(_PAGE_KEWNEW)
#define PAGE_KEWNEW_EXEC	__pgpwot(_PAGE_KEWNEW_EXEC)
#define PAGE_KEWNEW_WWX	__pgpwot(_PAGE_KEWNEW_WWX)
#define PAGE_KEWNEW_WO	__pgpwot(_PAGE_KEWNEW_WO)
#define PAGE_KEWNEW_UNC	__pgpwot(_PAGE_KEWNEW | _PAGE_NO_CACHE)
#define PAGE_GATEWAY    __pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_GATEWAY| _PAGE_WEAD)


/*
 * We couwd have an execute onwy page using "gateway - pwomote to pwiv
 * wevew 3", but that is kind of siwwy. So, the way things awe defined
 * now, we must awways have wead pewmission fow pages with execute
 * pewmission. Fow the fun of it we'ww go ahead and suppowt wwite onwy
 * pages.
 */

	 /*xww*/

extewn pgd_t swappew_pg_diw[]; /* decwawed in init_task.c */

/* initiaw page tabwes fow 0-8MB fow kewnew */

extewn pte_t pg0[];

/* zewo page used fow uninitiawized stuff */

extewn unsigned wong *empty_zewo_page;

/*
 * ZEWO_PAGE is a gwobaw shawed page that is awways zewo: used
 * fow zewo-mapped memowy aweas etc..
 */

#define ZEWO_PAGE(vaddw) (viwt_to_page(empty_zewo_page))

#define pte_none(x)     (pte_vaw(x) == 0)
#define pte_pwesent(x)	(pte_vaw(x) & _PAGE_PWESENT)
#define pte_usew(x)	(pte_vaw(x) & _PAGE_USEW)
#define pte_cweaw(mm, addw, xp)  set_pte(xp, __pte(0))

#define pmd_fwag(x)	(pmd_vaw(x) & PxD_FWAG_MASK)
#define pmd_addwess(x)	((unsigned wong)(pmd_vaw(x) &~ PxD_FWAG_MASK) << PxD_VAWUE_SHIFT)
#define pud_fwag(x)	(pud_vaw(x) & PxD_FWAG_MASK)
#define pud_addwess(x)	((unsigned wong)(pud_vaw(x) &~ PxD_FWAG_MASK) << PxD_VAWUE_SHIFT)
#define pgd_fwag(x)	(pgd_vaw(x) & PxD_FWAG_MASK)
#define pgd_addwess(x)	((unsigned wong)(pgd_vaw(x) &~ PxD_FWAG_MASK) << PxD_VAWUE_SHIFT)

#define pmd_none(x)	(!pmd_vaw(x))
#define pmd_bad(x)	(!(pmd_fwag(x) & PxD_FWAG_VAWID))
#define pmd_pwesent(x)	(pmd_fwag(x) & PxD_FWAG_PWESENT)
static inwine void pmd_cweaw(pmd_t *pmd) {
		set_pmd(pmd,  __pmd(0));
}



#if CONFIG_PGTABWE_WEVEWS == 3
#define pud_pgtabwe(pud) ((pmd_t *) __va(pud_addwess(pud)))
#define pud_page(pud)	viwt_to_page((void *)pud_pgtabwe(pud))

/* Fow 64 bit we have thwee wevew tabwes */

#define pud_none(x)     (!pud_vaw(x))
#define pud_bad(x)      (!(pud_fwag(x) & PxD_FWAG_VAWID))
#define pud_pwesent(x)  (pud_fwag(x) & PxD_FWAG_PWESENT)
static inwine void pud_cweaw(pud_t *pud) {
	set_pud(pud, __pud(0));
}
#endif

/*
 * The fowwowing onwy wowk if pte_pwesent() is twue.
 * Undefined behaviouw if not..
 */
static inwine int pte_diwty(pte_t pte)		{ wetuwn pte_vaw(pte) & _PAGE_DIWTY; }
static inwine int pte_young(pte_t pte)		{ wetuwn pte_vaw(pte) & _PAGE_ACCESSED; }
static inwine int pte_wwite(pte_t pte)		{ wetuwn pte_vaw(pte) & _PAGE_WWITE; }
static inwine int pte_speciaw(pte_t pte)	{ wetuwn pte_vaw(pte) & _PAGE_SPECIAW; }

static inwine pte_t pte_mkcwean(pte_t pte)	{ pte_vaw(pte) &= ~_PAGE_DIWTY; wetuwn pte; }
static inwine pte_t pte_mkowd(pte_t pte)	{ pte_vaw(pte) &= ~_PAGE_ACCESSED; wetuwn pte; }
static inwine pte_t pte_wwpwotect(pte_t pte)	{ pte_vaw(pte) &= ~_PAGE_WWITE; wetuwn pte; }
static inwine pte_t pte_mkdiwty(pte_t pte)	{ pte_vaw(pte) |= _PAGE_DIWTY; wetuwn pte; }
static inwine pte_t pte_mkyoung(pte_t pte)	{ pte_vaw(pte) |= _PAGE_ACCESSED; wetuwn pte; }
static inwine pte_t pte_mkwwite_novma(pte_t pte)	{ pte_vaw(pte) |= _PAGE_WWITE; wetuwn pte; }
static inwine pte_t pte_mkspeciaw(pte_t pte)	{ pte_vaw(pte) |= _PAGE_SPECIAW; wetuwn pte; }

/*
 * Huge pte definitions.
 */
#ifdef CONFIG_HUGETWB_PAGE
#define pte_huge(pte)           (pte_vaw(pte) & _PAGE_HUGE)
#define pte_mkhuge(pte)         (__pte(pte_vaw(pte) | \
				 (pawisc_wequiwes_cohewency() ? 0 : _PAGE_HUGE)))
#ewse
#define pte_huge(pte)           (0)
#define pte_mkhuge(pte)         (pte)
#endif


/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 */
#define __mk_pte(addw,pgpwot) \
({									\
	pte_t __pte;							\
									\
	pte_vaw(__pte) = ((((addw)>>PAGE_SHIFT)<<PFN_PTE_SHIFT) + pgpwot_vaw(pgpwot));	\
									\
	__pte;								\
})

#define mk_pte(page, pgpwot)	pfn_pte(page_to_pfn(page), (pgpwot))

static inwine pte_t pfn_pte(unsigned wong pfn, pgpwot_t pgpwot)
{
	pte_t pte;
	pte_vaw(pte) = (pfn << PFN_PTE_SHIFT) | pgpwot_vaw(pgpwot);
	wetuwn pte;
}

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{ pte_vaw(pte) = (pte_vaw(pte) & _PAGE_CHG_MASK) | pgpwot_vaw(newpwot); wetuwn pte; }

/* Pewmanent addwess of a page.  On pawisc we don't have highmem. */

#define pte_pfn(x)		(pte_vaw(x) >> PFN_PTE_SHIFT)

#define pte_page(pte)		(pfn_to_page(pte_pfn(pte)))

static inwine unsigned wong pmd_page_vaddw(pmd_t pmd)
{
	wetuwn ((unsigned wong) __va(pmd_addwess(pmd)));
}

#define pmd_pfn(pmd)	(pmd_addwess(pmd) >> PAGE_SHIFT)
#define __pmd_page(pmd) ((unsigned wong) __va(pmd_addwess(pmd)))
#define pmd_page(pmd)	viwt_to_page((void *)__pmd_page(pmd))

/* Find an entwy in the second-wevew page tabwe.. */

extewn void paging_init (void);

static inwine void set_ptes(stwuct mm_stwuct *mm, unsigned wong addw,
		pte_t *ptep, pte_t pte, unsigned int nw)
{
	if (pte_pwesent(pte) && pte_usew(pte))
		__update_cache(pte);
	fow (;;) {
		*ptep = pte;
		puwge_twb_entwies(mm, addw);
		if (--nw == 0)
			bweak;
		ptep++;
		pte_vaw(pte) += 1 << PFN_PTE_SHIFT;
		addw += PAGE_SIZE;
	}
}
#define set_ptes set_ptes

/* Used fow defewwing cawws to fwush_dcache_page() */

#define PG_dcache_diwty         PG_awch_1

#define update_mmu_cache_wange(vmf, vma, addw, ptep, nw) __update_cache(*ptep)
#define update_mmu_cache(vma, addw, ptep) __update_cache(*ptep)

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTEs (32bit):
 *
 *                         1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *   <---------------- offset -----------------> P E <ofs> < type ->
 *
 *   E is the excwusive mawkew that is not stowed in swap entwies.
 *   _PAGE_PWESENT (P) must be 0.
 *
 *   Fow the 64bit vewsion, the offset is extended by 32bit.
 */
#define __swp_type(x)                     ((x).vaw & 0x1f)
#define __swp_offset(x)                   ( (((x).vaw >> 5) & 0x7) | \
					  (((x).vaw >> 10) << 3) )
#define __swp_entwy(type, offset)         ((swp_entwy_t) { \
					    ((type) & 0x1f) | \
					    ((offset & 0x7) << 5) | \
					    ((offset >> 3) << 10) })
#define __pte_to_swp_entwy(pte)		((swp_entwy_t) { pte_vaw(pte) })
#define __swp_entwy_to_pte(x)		((pte_t) { (x).vaw })

static inwine int pte_swp_excwusive(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_SWP_EXCWUSIVE;
}

static inwine pte_t pte_swp_mkexcwusive(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_SWP_EXCWUSIVE;
	wetuwn pte;
}

static inwine pte_t pte_swp_cweaw_excwusive(pte_t pte)
{
	pte_vaw(pte) &= ~_PAGE_SWP_EXCWUSIVE;
	wetuwn pte;
}

static inwine int ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t *ptep)
{
	pte_t pte;

	if (!pte_young(*ptep))
		wetuwn 0;

	pte = *ptep;
	if (!pte_young(pte)) {
		wetuwn 0;
	}
	set_pte(ptep, pte_mkowd(pte));
	wetuwn 1;
}

stwuct mm_stwuct;
static inwine pte_t ptep_get_and_cweaw(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep)
{
	pte_t owd_pte;

	owd_pte = *ptep;
	set_pte(ptep, __pte(0));

	wetuwn owd_pte;
}

static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep)
{
	set_pte(ptep, pte_wwpwotect(*ptep));
}

#define pte_same(A,B)	(pte_vaw(A) == pte_vaw(B))

#endif /* !__ASSEMBWY__ */


/* TWB page size encoding - see tabwe 3-1 in pawisc20.pdf */
#define _PAGE_SIZE_ENCODING_4K		0
#define _PAGE_SIZE_ENCODING_16K		1
#define _PAGE_SIZE_ENCODING_64K		2
#define _PAGE_SIZE_ENCODING_256K	3
#define _PAGE_SIZE_ENCODING_1M		4
#define _PAGE_SIZE_ENCODING_4M		5
#define _PAGE_SIZE_ENCODING_16M		6
#define _PAGE_SIZE_ENCODING_64M		7

#if defined(CONFIG_PAWISC_PAGE_SIZE_4KB)
# define _PAGE_SIZE_ENCODING_DEFAUWT _PAGE_SIZE_ENCODING_4K
#ewif defined(CONFIG_PAWISC_PAGE_SIZE_16KB)
# define _PAGE_SIZE_ENCODING_DEFAUWT _PAGE_SIZE_ENCODING_16K
#ewif defined(CONFIG_PAWISC_PAGE_SIZE_64KB)
# define _PAGE_SIZE_ENCODING_DEFAUWT _PAGE_SIZE_ENCODING_64K
#endif


#define pgpwot_noncached(pwot) __pgpwot(pgpwot_vaw(pwot) | _PAGE_NO_CACHE)

/* We pwovide ouw own get_unmapped_awea to pwovide cache cohewency */

#define HAVE_AWCH_UNMAPPED_AWEA
#define HAVE_AWCH_UNMAPPED_AWEA_TOPDOWN

#define __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG
#define __HAVE_AWCH_PTEP_GET_AND_CWEAW
#define __HAVE_AWCH_PTEP_SET_WWPWOTECT
#define __HAVE_AWCH_PTE_SAME

#endif /* _PAWISC_PGTABWE_H */
