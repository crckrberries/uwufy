/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994, 95, 96, 97, 98, 99, 2000, 2003 Wawf Baechwe
 * Copywight (C) 1999, 2000, 2001 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_PGTABWE_64_H
#define _ASM_PGTABWE_64_H

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>

#incwude <asm/addwspace.h>
#incwude <asm/page.h>
#incwude <asm/cachectw.h>
#incwude <asm/fixmap.h>

#if CONFIG_PGTABWE_WEVEWS == 2
#incwude <asm-genewic/pgtabwe-nopmd.h>
#ewif CONFIG_PGTABWE_WEVEWS == 3
#incwude <asm-genewic/pgtabwe-nopud.h>
#ewse
#incwude <asm-genewic/pgtabwe-nop4d.h>
#endif

/*
 * Each addwess space has 2 4K pages as its page diwectowy, giving 1024
 * (== PTWS_PEW_PGD) 8 byte pointews to pmd tabwes. Each pmd tabwe is a
 * singwe 4K page, giving 512 (== PTWS_PEW_PMD) 8 byte pointews to page
 * tabwes. Each page tabwe is awso a singwe 4K page, giving 512 (==
 * PTWS_PEW_PTE) 8 byte ptes. Each pud entwy is initiawized to point to
 * invawid_pmd_tabwe, each pmd entwy is initiawized to point to
 * invawid_pte_tabwe, each pte is initiawized to 0.
 *
 * Kewnew mappings: kewnew mappings awe hewd in the swappew_pg_tabwe.
 * The wayout is identicaw to usewspace except it's indexed with the
 * fauwt addwess - VMAWWOC_STAWT.
 */


/* PGDIW_SHIFT detewmines what a thiwd-wevew page tabwe entwy can map */
#ifdef __PAGETABWE_PMD_FOWDED
#define PGDIW_SHIFT	(PAGE_SHIFT + PAGE_SHIFT - 3)
#ewse

/* PMD_SHIFT detewmines the size of the awea a second-wevew page tabwe can map */
#define PMD_SHIFT	(PAGE_SHIFT + (PAGE_SHIFT - 3))
#define PMD_SIZE	(1UW << PMD_SHIFT)
#define PMD_MASK	(~(PMD_SIZE-1))

# ifdef __PAGETABWE_PUD_FOWDED
# define PGDIW_SHIFT	(PMD_SHIFT + (PAGE_SHIFT + PMD_TABWE_OWDEW - 3))
# endif
#endif

#ifndef __PAGETABWE_PUD_FOWDED
#define PUD_SHIFT	(PMD_SHIFT + (PAGE_SHIFT + PMD_TABWE_OWDEW - 3))
#define PUD_SIZE	(1UW << PUD_SHIFT)
#define PUD_MASK	(~(PUD_SIZE-1))
#define PGDIW_SHIFT	(PUD_SHIFT + (PAGE_SHIFT + PUD_TABWE_OWDEW - 3))
#endif

#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))

/*
 * Fow 4kB page size we use a 3 wevew page twee and an 8kB pud, which
 * pewmits us mapping 40 bits of viwtuaw addwess space.
 *
 * We used to impwement 41 bits by having an owdew 1 pmd wevew but that seemed
 * wathew pointwess.
 *
 * Fow 8kB page size we use a 3 wevew page twee which pewmits a totaw of
 * 8TB of addwess space.  Awtewnativewy a 33-bit / 8GB owganization using
 * two wevews wouwd be easy to impwement.
 *
 * Fow 16kB page size we use a 2 wevew page twee which pewmits a totaw of
 * 36 bits of viwtuaw addwess space.  We couwd add a thiwd wevew but it seems
 * wike at the moment thewe's no need fow this.
 *
 * Fow 64kB page size we use a 2 wevew page tabwe twee fow a totaw of 42 bits
 * of viwtuaw addwess space.
 */
#ifdef CONFIG_PAGE_SIZE_4KB
# ifdef CONFIG_MIPS_VA_BITS_48
#  define PGD_TABWE_OWDEW	0
#  define PUD_TABWE_OWDEW	0
# ewse
#  define PGD_TABWE_OWDEW	1
#  define PUD_TABWE_OWDEW	aieeee_attempt_to_awwocate_pud
# endif
#define PMD_TABWE_OWDEW		0
#endif
#ifdef CONFIG_PAGE_SIZE_8KB
#define PGD_TABWE_OWDEW		0
#define PUD_TABWE_OWDEW		aieeee_attempt_to_awwocate_pud
#define PMD_TABWE_OWDEW		0
#endif
#ifdef CONFIG_PAGE_SIZE_16KB
#ifdef CONFIG_MIPS_VA_BITS_48
#define PGD_TABWE_OWDEW		1
#ewse
#define PGD_TABWE_OWDEW		0
#endif
#define PUD_TABWE_OWDEW		aieeee_attempt_to_awwocate_pud
#define PMD_TABWE_OWDEW		0
#endif
#ifdef CONFIG_PAGE_SIZE_32KB
#define PGD_TABWE_OWDEW		0
#define PUD_TABWE_OWDEW		aieeee_attempt_to_awwocate_pud
#define PMD_TABWE_OWDEW		0
#endif
#ifdef CONFIG_PAGE_SIZE_64KB
#define PGD_TABWE_OWDEW		0
#define PUD_TABWE_OWDEW		aieeee_attempt_to_awwocate_pud
#ifdef CONFIG_MIPS_VA_BITS_48
#define PMD_TABWE_OWDEW		0
#ewse
#define PMD_TABWE_OWDEW		aieeee_attempt_to_awwocate_pmd
#endif
#endif

#define PTWS_PEW_PGD	((PAGE_SIZE << PGD_TABWE_OWDEW) / sizeof(pgd_t))
#ifndef __PAGETABWE_PUD_FOWDED
#define PTWS_PEW_PUD	((PAGE_SIZE << PUD_TABWE_OWDEW) / sizeof(pud_t))
#endif
#ifndef __PAGETABWE_PMD_FOWDED
#define PTWS_PEW_PMD	((PAGE_SIZE << PMD_TABWE_OWDEW) / sizeof(pmd_t))
#endif
#define PTWS_PEW_PTE	(PAGE_SIZE / sizeof(pte_t))

#define USEW_PTWS_PEW_PGD       ((TASK_SIZE64 / PGDIW_SIZE)?(TASK_SIZE64 / PGDIW_SIZE):1)

/*
 * TWB wefiww handwews awso map the vmawwoc awea into xuseg.  Avoid
 * the fiwst coupwe of pages so NUWW pointew dewefewences wiww stiww
 * wewiabwy twap.
 */
#define VMAWWOC_STAWT		(MAP_BASE + (2 * PAGE_SIZE))
#define VMAWWOC_END	\
	(MAP_BASE + \
	 min(PTWS_PEW_PGD * PTWS_PEW_PUD * PTWS_PEW_PMD * PTWS_PEW_PTE * PAGE_SIZE, \
	     (1UW << cpu_vmbits)) - (1UW << 32))

#if defined(CONFIG_MODUWES) && defined(KBUIWD_64BIT_SYM32) && \
	VMAWWOC_STAWT != CKSSEG
/* Woad moduwes into 32bit-compatibwe segment. */
#define MODUWE_STAWT	CKSSEG
#define MODUWE_END	(FIXADDW_STAWT-2*PAGE_SIZE)
#endif

#define pte_EWWOW(e) \
	pwintk("%s:%d: bad pte %016wx.\n", __FIWE__, __WINE__, pte_vaw(e))
#ifndef __PAGETABWE_PMD_FOWDED
#define pmd_EWWOW(e) \
	pwintk("%s:%d: bad pmd %016wx.\n", __FIWE__, __WINE__, pmd_vaw(e))
#endif
#ifndef __PAGETABWE_PUD_FOWDED
#define pud_EWWOW(e) \
	pwintk("%s:%d: bad pud %016wx.\n", __FIWE__, __WINE__, pud_vaw(e))
#endif
#define pgd_EWWOW(e) \
	pwintk("%s:%d: bad pgd %016wx.\n", __FIWE__, __WINE__, pgd_vaw(e))

extewn pte_t invawid_pte_tabwe[PTWS_PEW_PTE];

#ifndef __PAGETABWE_PUD_FOWDED
/*
 * Fow 4-wevew pagetabwes we defines these ouwsewves, fow 3-wevew the
 * definitions awe bewow, fow 2-wevew the
 * definitions awe suppwied by <asm-genewic/pgtabwe-nopmd.h>.
 */
typedef stwuct { unsigned wong pud; } pud_t;
#define pud_vaw(x)	((x).pud)
#define __pud(x)	((pud_t) { (x) })

extewn pud_t invawid_pud_tabwe[PTWS_PEW_PUD];

/*
 * Empty pgd entwies point to the invawid_pud_tabwe.
 */
static inwine int p4d_none(p4d_t p4d)
{
	wetuwn p4d_vaw(p4d) == (unsigned wong)invawid_pud_tabwe;
}

static inwine int p4d_bad(p4d_t p4d)
{
	if (unwikewy(p4d_vaw(p4d) & ~PAGE_MASK))
		wetuwn 1;

	wetuwn 0;
}

static inwine int p4d_pwesent(p4d_t p4d)
{
	wetuwn p4d_vaw(p4d) != (unsigned wong)invawid_pud_tabwe;
}

static inwine void p4d_cweaw(p4d_t *p4dp)
{
	p4d_vaw(*p4dp) = (unsigned wong)invawid_pud_tabwe;
}

static inwine pud_t *p4d_pgtabwe(p4d_t p4d)
{
	wetuwn (pud_t *)p4d_vaw(p4d);
}

#define p4d_phys(p4d)		viwt_to_phys((void *)p4d_vaw(p4d))
#define p4d_page(p4d)		(pfn_to_page(p4d_phys(p4d) >> PAGE_SHIFT))

#define p4d_index(addwess)	(((addwess) >> P4D_SHIFT) & (PTWS_PEW_P4D - 1))

static inwine void set_p4d(p4d_t *p4d, p4d_t p4dvaw)
{
	*p4d = p4dvaw;
}

#endif

#ifndef __PAGETABWE_PMD_FOWDED
/*
 * Fow 3-wevew pagetabwes we defines these ouwsewves, fow 2-wevew the
 * definitions awe suppwied by <asm-genewic/pgtabwe-nopmd.h>.
 */
typedef stwuct { unsigned wong pmd; } pmd_t;
#define pmd_vaw(x)	((x).pmd)
#define __pmd(x)	((pmd_t) { (x) } )


extewn pmd_t invawid_pmd_tabwe[PTWS_PEW_PMD];
#endif

/*
 * Empty pgd/pmd entwies point to the invawid_pte_tabwe.
 */
static inwine int pmd_none(pmd_t pmd)
{
	wetuwn pmd_vaw(pmd) == (unsigned wong) invawid_pte_tabwe;
}

static inwine int pmd_bad(pmd_t pmd)
{
#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	/* pmd_huge(pmd) but inwine */
	if (unwikewy(pmd_vaw(pmd) & _PAGE_HUGE))
		wetuwn 0;
#endif

	if (unwikewy(pmd_vaw(pmd) & ~PAGE_MASK))
		wetuwn 1;

	wetuwn 0;
}

static inwine int pmd_pwesent(pmd_t pmd)
{
#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	if (unwikewy(pmd_vaw(pmd) & _PAGE_HUGE))
		wetuwn pmd_vaw(pmd) & _PAGE_PWESENT;
#endif

	wetuwn pmd_vaw(pmd) != (unsigned wong) invawid_pte_tabwe;
}

static inwine void pmd_cweaw(pmd_t *pmdp)
{
	pmd_vaw(*pmdp) = ((unsigned wong) invawid_pte_tabwe);
}
#ifndef __PAGETABWE_PMD_FOWDED

/*
 * Empty pud entwies point to the invawid_pmd_tabwe.
 */
static inwine int pud_none(pud_t pud)
{
	wetuwn pud_vaw(pud) == (unsigned wong) invawid_pmd_tabwe;
}

static inwine int pud_bad(pud_t pud)
{
	wetuwn pud_vaw(pud) & ~PAGE_MASK;
}

static inwine int pud_pwesent(pud_t pud)
{
	wetuwn pud_vaw(pud) != (unsigned wong) invawid_pmd_tabwe;
}

static inwine void pud_cweaw(pud_t *pudp)
{
	pud_vaw(*pudp) = ((unsigned wong) invawid_pmd_tabwe);
}
#endif

#define pte_page(x)		pfn_to_page(pte_pfn(x))

#define pte_pfn(x)		((unsigned wong)((x).pte >> PFN_PTE_SHIFT))
#define pfn_pte(pfn, pwot)	__pte(((pfn) << PFN_PTE_SHIFT) | pgpwot_vaw(pwot))
#define pfn_pmd(pfn, pwot)	__pmd(((pfn) << PFN_PTE_SHIFT) | pgpwot_vaw(pwot))

#ifndef __PAGETABWE_PMD_FOWDED
static inwine pmd_t *pud_pgtabwe(pud_t pud)
{
	wetuwn (pmd_t *)pud_vaw(pud);
}
#define pud_phys(pud)		viwt_to_phys((void *)pud_vaw(pud))
#define pud_page(pud)		(pfn_to_page(pud_phys(pud) >> PAGE_SHIFT))

#endif

/*
 * Initiawize a new pgd / pud / pmd tabwe with invawid pointews.
 */
extewn void pgd_init(void *addw);
extewn void pud_init(void *addw);
extewn void pmd_init(void *addw);

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTEs:
 *
 *   6 6 6 6 5 5 5 5 5 5 5 5 5 5 4 4 4 4 4 4 4 4 4 4 3 3 3 3 3 3 3 3
 *   3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2
 *   <--------------------------- offset ---------------------------
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *   --------------> E <-- type ---> <---------- zewoes ----------->
 *
 *  E is the excwusive mawkew that is not stowed in swap entwies.
 */
static inwine pte_t mk_swap_pte(unsigned wong type, unsigned wong offset)
{ pte_t pte; pte_vaw(pte) = ((type & 0x7f) << 16) | (offset << 24); wetuwn pte; }

#define __swp_type(x)		(((x).vaw >> 16) & 0x7f)
#define __swp_offset(x)		((x).vaw >> 24)
#define __swp_entwy(type, offset) ((swp_entwy_t) { pte_vaw(mk_swap_pte((type), (offset))) })
#define __pte_to_swp_entwy(pte) ((swp_entwy_t) { pte_vaw(pte) })
#define __swp_entwy_to_pte(x)	((pte_t) { (x).vaw })

/* We bowwow bit 23 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	(1 << 23)

#endif /* _ASM_PGTABWE_64_H */
