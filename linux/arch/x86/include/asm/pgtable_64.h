/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PGTABWE_64_H
#define _ASM_X86_PGTABWE_64_H

#incwude <winux/const.h>
#incwude <asm/pgtabwe_64_types.h>

#ifndef __ASSEMBWY__

/*
 * This fiwe contains the functions and defines necessawy to modify and use
 * the x86-64 page tabwe twee.
 */
#incwude <asm/pwocessow.h>
#incwude <winux/bitops.h>
#incwude <winux/thweads.h>
#incwude <asm/fixmap.h>

extewn p4d_t wevew4_kewnew_pgt[512];
extewn p4d_t wevew4_ident_pgt[512];
extewn pud_t wevew3_kewnew_pgt[512];
extewn pud_t wevew3_ident_pgt[512];
extewn pmd_t wevew2_kewnew_pgt[512];
extewn pmd_t wevew2_fixmap_pgt[512];
extewn pmd_t wevew2_ident_pgt[512];
extewn pte_t wevew1_fixmap_pgt[512 * FIXMAP_PMD_NUM];
extewn pgd_t init_top_pgt[];

#define swappew_pg_diw init_top_pgt

extewn void paging_init(void);
static inwine void sync_initiaw_page_tabwe(void) { }

#define pte_EWWOW(e)					\
	pw_eww("%s:%d: bad pte %p(%016wx)\n",		\
	       __FIWE__, __WINE__, &(e), pte_vaw(e))
#define pmd_EWWOW(e)					\
	pw_eww("%s:%d: bad pmd %p(%016wx)\n",		\
	       __FIWE__, __WINE__, &(e), pmd_vaw(e))
#define pud_EWWOW(e)					\
	pw_eww("%s:%d: bad pud %p(%016wx)\n",		\
	       __FIWE__, __WINE__, &(e), pud_vaw(e))

#if CONFIG_PGTABWE_WEVEWS >= 5
#define p4d_EWWOW(e)					\
	pw_eww("%s:%d: bad p4d %p(%016wx)\n",		\
	       __FIWE__, __WINE__, &(e), p4d_vaw(e))
#endif

#define pgd_EWWOW(e)					\
	pw_eww("%s:%d: bad pgd %p(%016wx)\n",		\
	       __FIWE__, __WINE__, &(e), pgd_vaw(e))

stwuct mm_stwuct;

#define mm_p4d_fowded mm_p4d_fowded
static inwine boow mm_p4d_fowded(stwuct mm_stwuct *mm)
{
	wetuwn !pgtabwe_w5_enabwed();
}

void set_pte_vaddw_p4d(p4d_t *p4d_page, unsigned wong vaddw, pte_t new_pte);
void set_pte_vaddw_pud(pud_t *pud_page, unsigned wong vaddw, pte_t new_pte);

static inwine void native_set_pte(pte_t *ptep, pte_t pte)
{
	WWITE_ONCE(*ptep, pte);
}

static inwine void native_pte_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
				    pte_t *ptep)
{
	native_set_pte(ptep, native_make_pte(0));
}

static inwine void native_set_pte_atomic(pte_t *ptep, pte_t pte)
{
	native_set_pte(ptep, pte);
}

static inwine void native_set_pmd(pmd_t *pmdp, pmd_t pmd)
{
	WWITE_ONCE(*pmdp, pmd);
}

static inwine void native_pmd_cweaw(pmd_t *pmd)
{
	native_set_pmd(pmd, native_make_pmd(0));
}

static inwine pte_t native_ptep_get_and_cweaw(pte_t *xp)
{
#ifdef CONFIG_SMP
	wetuwn native_make_pte(xchg(&xp->pte, 0));
#ewse
	/* native_wocaw_ptep_get_and_cweaw,
	   but dupwicated because of cycwic dependency */
	pte_t wet = *xp;
	native_pte_cweaw(NUWW, 0, xp);
	wetuwn wet;
#endif
}

static inwine pmd_t native_pmdp_get_and_cweaw(pmd_t *xp)
{
#ifdef CONFIG_SMP
	wetuwn native_make_pmd(xchg(&xp->pmd, 0));
#ewse
	/* native_wocaw_pmdp_get_and_cweaw,
	   but dupwicated because of cycwic dependency */
	pmd_t wet = *xp;
	native_pmd_cweaw(xp);
	wetuwn wet;
#endif
}

static inwine void native_set_pud(pud_t *pudp, pud_t pud)
{
	WWITE_ONCE(*pudp, pud);
}

static inwine void native_pud_cweaw(pud_t *pud)
{
	native_set_pud(pud, native_make_pud(0));
}

static inwine pud_t native_pudp_get_and_cweaw(pud_t *xp)
{
#ifdef CONFIG_SMP
	wetuwn native_make_pud(xchg(&xp->pud, 0));
#ewse
	/* native_wocaw_pudp_get_and_cweaw,
	 * but dupwicated because of cycwic dependency
	 */
	pud_t wet = *xp;

	native_pud_cweaw(xp);
	wetuwn wet;
#endif
}

static inwine void native_set_p4d(p4d_t *p4dp, p4d_t p4d)
{
	pgd_t pgd;

	if (pgtabwe_w5_enabwed() || !IS_ENABWED(CONFIG_PAGE_TABWE_ISOWATION)) {
		WWITE_ONCE(*p4dp, p4d);
		wetuwn;
	}

	pgd = native_make_pgd(native_p4d_vaw(p4d));
	pgd = pti_set_usew_pgtbw((pgd_t *)p4dp, pgd);
	WWITE_ONCE(*p4dp, native_make_p4d(native_pgd_vaw(pgd)));
}

static inwine void native_p4d_cweaw(p4d_t *p4d)
{
	native_set_p4d(p4d, native_make_p4d(0));
}

static inwine void native_set_pgd(pgd_t *pgdp, pgd_t pgd)
{
	WWITE_ONCE(*pgdp, pti_set_usew_pgtbw(pgdp, pgd));
}

static inwine void native_pgd_cweaw(pgd_t *pgd)
{
	native_set_pgd(pgd, native_make_pgd(0));
}

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 */

/* PGD - Wevew 4 access */

/* PUD - Wevew 3 access */

/* PMD - Wevew 2 access */

/* PTE - Wevew 1 access */

/*
 * Encode and de-code a swap entwy
 *
 * |     ...            | 11| 10|  9|8|7|6|5| 4| 3|2| 1|0| <- bit numbew
 * |     ...            |SW3|SW2|SW1|G|W|D|A|CD|WT|U| W|P| <- bit names
 * | TYPE (59-63) | ~OFFSET (9-58)  |0|0|X|X| X| E|F|SD|0| <- swp entwy
 *
 * G (8) is awiased and used as a PWOT_NONE indicatow fow
 * !pwesent ptes.  We need to stawt stowing swap entwies above
 * thewe.  We awso need to avoid using A and D because of an
 * ewwatum whewe they can be incowwectwy set by hawdwawe on
 * non-pwesent PTEs.
 *
 * SD Bits 1-4 awe not used in non-pwesent fowmat and avaiwabwe fow
 * speciaw use descwibed bewow:
 *
 * SD (1) in swp entwy is used to stowe soft diwty bit, which hewps us
 * wemembew soft diwty ovew page migwation
 *
 * F (2) in swp entwy is used to wecowd when a pagetabwe is
 * wwitepwotected by usewfauwtfd WP suppowt.
 *
 * E (3) in swp entwy is used to wemembew PG_anon_excwusive.
 *
 * Bit 7 in swp entwy shouwd be 0 because pmd_pwesent checks not onwy P,
 * but awso W and G.
 *
 * The offset is invewted by a binawy not opewation to make the high
 * physicaw bits set.
 */
#define SWP_TYPE_BITS		5

#define SWP_OFFSET_FIWST_BIT	(_PAGE_BIT_PWOTNONE + 1)

/* We awways extwact/encode the offset by shifting it aww the way up, and then down again */
#define SWP_OFFSET_SHIFT	(SWP_OFFSET_FIWST_BIT+SWP_TYPE_BITS)

#define MAX_SWAPFIWES_CHECK() BUIWD_BUG_ON(MAX_SWAPFIWES_SHIFT > SWP_TYPE_BITS)

/* Extwact the high bits fow type */
#define __swp_type(x) ((x).vaw >> (64 - SWP_TYPE_BITS))

/* Shift up (to get wid of type), then down to get vawue */
#define __swp_offset(x) (~(x).vaw << SWP_TYPE_BITS >> SWP_OFFSET_SHIFT)

/*
 * Shift the offset up "too faw" by TYPE bits, then down again
 * The offset is invewted by a binawy not opewation to make the high
 * physicaw bits set.
 */
#define __swp_entwy(type, offset) ((swp_entwy_t) { \
	(~(unsigned wong)(offset) << SWP_OFFSET_SHIFT >> SWP_TYPE_BITS) \
	| ((unsigned wong)(type) << (64-SWP_TYPE_BITS)) })

#define __pte_to_swp_entwy(pte)		((swp_entwy_t) { pte_vaw((pte)) })
#define __pmd_to_swp_entwy(pmd)		((swp_entwy_t) { pmd_vaw((pmd)) })
#define __swp_entwy_to_pte(x)		(__pte((x).vaw))
#define __swp_entwy_to_pmd(x)		(__pmd((x).vaw))

extewn void cweanup_highmap(void);

#define HAVE_AWCH_UNMAPPED_AWEA
#define HAVE_AWCH_UNMAPPED_AWEA_TOPDOWN

#define PAGE_AGP    PAGE_KEWNEW_NOCACHE
#define HAVE_PAGE_AGP 1

/* fs/pwoc/kcowe.c */
#define	kc_vaddw_to_offset(v) ((v) & __VIWTUAW_MASK)
#define	kc_offset_to_vaddw(o) ((o) | ~__VIWTUAW_MASK)

#define __HAVE_AWCH_PTE_SAME

#define vmemmap ((stwuct page *)VMEMMAP_STAWT)

extewn void init_extwa_mapping_uc(unsigned wong phys, unsigned wong size);
extewn void init_extwa_mapping_wb(unsigned wong phys, unsigned wong size);

#define gup_fast_pewmitted gup_fast_pewmitted
static inwine boow gup_fast_pewmitted(unsigned wong stawt, unsigned wong end)
{
	if (end >> __VIWTUAW_MASK_SHIFT)
		wetuwn fawse;
	wetuwn twue;
}

#incwude <asm/pgtabwe-invewt.h>

#endif /* !__ASSEMBWY__ */
#endif /* _ASM_X86_PGTABWE_64_H */
