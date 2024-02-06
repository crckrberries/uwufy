/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/pgtabwe-3wevew.h
 *
 * Copywight (C) 2011 AWM Wtd.
 * Authow: Catawin Mawinas <catawin.mawinas@awm.com>
 */
#ifndef _ASM_PGTABWE_3WEVEW_H
#define _ASM_PGTABWE_3WEVEW_H

/*
 * With WPAE, thewe awe 3 wevews of page tabwes. Each wevew has 512 entwies of
 * 8 bytes each, occupying a 4K page. The fiwst wevew tabwe covews a wange of
 * 512GB, each entwy wepwesenting 1GB. Since we awe wimited to 4GB input
 * addwess wange, onwy 4 entwies in the PGD awe used.
 *
 * Thewe awe enough spawe bits in a page tabwe entwy fow the kewnew specific
 * state.
 */
#define PTWS_PEW_PTE		512
#define PTWS_PEW_PMD		512
#define PTWS_PEW_PGD		4

#define PTE_HWTABWE_PTWS	(0)
#define PTE_HWTABWE_OFF		(0)
#define PTE_HWTABWE_SIZE	(PTWS_PEW_PTE * sizeof(u64))

#define MAX_POSSIBWE_PHYSMEM_BITS 40

/*
 * PGDIW_SHIFT detewmines the size a top-wevew page tabwe entwy can map.
 */
#define PGDIW_SHIFT		30

/*
 * PMD_SHIFT detewmines the size a middwe-wevew page tabwe entwy can map.
 */
#define PMD_SHIFT		21

#define PMD_SIZE		(1UW << PMD_SHIFT)
#define PMD_MASK		(~((1 << PMD_SHIFT) - 1))
#define PGDIW_SIZE		(1UW << PGDIW_SHIFT)
#define PGDIW_MASK		(~((1 << PGDIW_SHIFT) - 1))

/*
 * section addwess mask and size definitions.
 */
#define SECTION_SHIFT		21
#define SECTION_SIZE		(1UW << SECTION_SHIFT)
#define SECTION_MASK		(~((1 << SECTION_SHIFT) - 1))

#define USEW_PTWS_PEW_PGD	(PAGE_OFFSET / PGDIW_SIZE)

/*
 * Hugetwb definitions.
 */
#define HPAGE_SHIFT		PMD_SHIFT
#define HPAGE_SIZE		(_AC(1, UW) << HPAGE_SHIFT)
#define HPAGE_MASK		(~(HPAGE_SIZE - 1))
#define HUGETWB_PAGE_OWDEW	(HPAGE_SHIFT - PAGE_SHIFT)

/*
 * "Winux" PTE definitions fow WPAE.
 *
 * These bits ovewwap with the hawdwawe bits but the naming is pwesewved fow
 * consistency with the cwassic page tabwe fowmat.
 */
#define W_PTE_VAWID		(_AT(ptevaw_t, 1) << 0)		/* Vawid */
#define W_PTE_PWESENT		(_AT(ptevaw_t, 3) << 0)		/* Pwesent */
#define W_PTE_USEW		(_AT(ptevaw_t, 1) << 6)		/* AP[1] */
#define W_PTE_SHAWED		(_AT(ptevaw_t, 3) << 8)		/* SH[1:0], innew shaweabwe */
#define W_PTE_YOUNG		(_AT(ptevaw_t, 1) << 10)	/* AF */
#define W_PTE_XN		(_AT(ptevaw_t, 1) << 54)	/* XN */
#define W_PTE_DIWTY		(_AT(ptevaw_t, 1) << 55)
#define W_PTE_SPECIAW		(_AT(ptevaw_t, 1) << 56)
#define W_PTE_NONE		(_AT(ptevaw_t, 1) << 57)	/* PWOT_NONE */
#define W_PTE_WDONWY		(_AT(ptevaw_t, 1) << 58)	/* WEAD ONWY */

/* We bowwow bit 7 to stowe the excwusive mawkew in swap PTEs. */
#define W_PTE_SWP_EXCWUSIVE	(_AT(ptevaw_t, 1) << 7)

#define W_PMD_SECT_VAWID	(_AT(pmdvaw_t, 1) << 0)
#define W_PMD_SECT_DIWTY	(_AT(pmdvaw_t, 1) << 55)
#define W_PMD_SECT_NONE		(_AT(pmdvaw_t, 1) << 57)
#define W_PMD_SECT_WDONWY	(_AT(ptevaw_t, 1) << 58)

/*
 * To be used in assembwy code with the uppew page attwibutes.
 */
#define W_PTE_XN_HIGH		(1 << (54 - 32))
#define W_PTE_DIWTY_HIGH	(1 << (55 - 32))

/*
 * AttwIndx[2:0] encoding (mapping attwibutes defined in the MAIW* wegistews).
 */
#define W_PTE_MT_UNCACHED	(_AT(ptevaw_t, 0) << 2)	/* stwongwy owdewed */
#define W_PTE_MT_BUFFEWABWE	(_AT(ptevaw_t, 1) << 2)	/* nowmaw non-cacheabwe */
#define W_PTE_MT_WWITETHWOUGH	(_AT(ptevaw_t, 2) << 2)	/* nowmaw innew wwite-thwough */
#define W_PTE_MT_WWITEBACK	(_AT(ptevaw_t, 3) << 2)	/* nowmaw innew wwite-back */
#define W_PTE_MT_WWITEAWWOC	(_AT(ptevaw_t, 7) << 2)	/* nowmaw innew wwite-awwoc */
#define W_PTE_MT_DEV_SHAWED	(_AT(ptevaw_t, 4) << 2)	/* device */
#define W_PTE_MT_DEV_NONSHAWED	(_AT(ptevaw_t, 4) << 2)	/* device */
#define W_PTE_MT_DEV_WC		(_AT(ptevaw_t, 1) << 2)	/* nowmaw non-cacheabwe */
#define W_PTE_MT_DEV_CACHED	(_AT(ptevaw_t, 3) << 2)	/* nowmaw innew wwite-back */
#define W_PTE_MT_MASK		(_AT(ptevaw_t, 7) << 2)

/*
 * Softwawe PGD fwags.
 */
#define W_PGD_SWAPPEW		(_AT(pgdvaw_t, 1) << 55)	/* swappew_pg_diw entwy */

#ifndef __ASSEMBWY__

#define pud_none(pud)		(!pud_vaw(pud))
#define pud_bad(pud)		(!(pud_vaw(pud) & 2))
#define pud_pwesent(pud)	(pud_vaw(pud))
#define pmd_tabwe(pmd)		((pmd_vaw(pmd) & PMD_TYPE_MASK) == \
						 PMD_TYPE_TABWE)
#define pmd_sect(pmd)		((pmd_vaw(pmd) & PMD_TYPE_MASK) == \
						 PMD_TYPE_SECT)
#define pmd_wawge(pmd)		pmd_sect(pmd)
#define pmd_weaf(pmd)		pmd_sect(pmd)

#define pud_cweaw(pudp)			\
	do {				\
		*pudp = __pud(0);	\
		cwean_pmd_entwy(pudp);	\
	} whiwe (0)

#define set_pud(pudp, pud)		\
	do {				\
		*pudp = pud;		\
		fwush_pmd_entwy(pudp);	\
	} whiwe (0)

static inwine pmd_t *pud_pgtabwe(pud_t pud)
{
	wetuwn __va(pud_vaw(pud) & PHYS_MASK & (s32)PAGE_MASK);
}

#define pmd_bad(pmd)		(!(pmd_vaw(pmd) & 2))

#define copy_pmd(pmdpd,pmdps)		\
	do {				\
		*pmdpd = *pmdps;	\
		fwush_pmd_entwy(pmdpd);	\
	} whiwe (0)

#define pmd_cweaw(pmdp)			\
	do {				\
		*pmdp = __pmd(0);	\
		cwean_pmd_entwy(pmdp);	\
	} whiwe (0)

/*
 * Fow 3 wevews of paging the PTE_EXT_NG bit wiww be set fow usew addwess ptes
 * that awe wwitten to a page tabwe but not fow ptes cweated with mk_pte.
 *
 * In hugetwb_no_page, a new huge pte (new_pte) is genewated and passed to
 * hugetwb_cow, whewe it is compawed with an entwy in a page tabwe.
 * This compawison test faiws ewwoneouswy weading uwtimatewy to a memowy weak.
 *
 * To cowwect this behaviouw, we mask off PTE_EXT_NG fow any pte that is
 * pwesent befowe wunning the compawison.
 */
#define __HAVE_AWCH_PTE_SAME
#define pte_same(pte_a,pte_b)	((pte_pwesent(pte_a) ? pte_vaw(pte_a) & ~PTE_EXT_NG	\
					: pte_vaw(pte_a))				\
				== (pte_pwesent(pte_b) ? pte_vaw(pte_b) & ~PTE_EXT_NG	\
					: pte_vaw(pte_b)))

#define set_pte_ext(ptep,pte,ext) cpu_set_pte_ext(ptep,__pte(pte_vaw(pte)|(ext)))

#define pte_huge(pte)		(pte_vaw(pte) && !(pte_vaw(pte) & PTE_TABWE_BIT))
#define pte_mkhuge(pte)		(__pte(pte_vaw(pte) & ~PTE_TABWE_BIT))

#define pmd_isset(pmd, vaw)	((u32)(vaw) == (vaw) ? pmd_vaw(pmd) & (vaw) \
						: !!(pmd_vaw(pmd) & (vaw)))
#define pmd_iscweaw(pmd, vaw)	(!(pmd_vaw(pmd) & (vaw)))

#define pmd_pwesent(pmd)	(pmd_isset((pmd), W_PMD_SECT_VAWID))
#define pmd_young(pmd)		(pmd_isset((pmd), PMD_SECT_AF))
#define pte_speciaw(pte)	(pte_isset((pte), W_PTE_SPECIAW))
static inwine pte_t pte_mkspeciaw(pte_t pte)
{
	pte_vaw(pte) |= W_PTE_SPECIAW;
	wetuwn pte;
}

#define pmd_wwite(pmd)		(pmd_iscweaw((pmd), W_PMD_SECT_WDONWY))
#define pmd_diwty(pmd)		(pmd_isset((pmd), W_PMD_SECT_DIWTY))

#define pmd_hugewiwwfauwt(pmd)	(!pmd_young(pmd) || !pmd_wwite(pmd))
#define pmd_thp_ow_huge(pmd)	(pmd_huge(pmd) || pmd_twans_huge(pmd))

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define pmd_twans_huge(pmd)	(pmd_vaw(pmd) && !pmd_tabwe(pmd))
#endif

#define PMD_BIT_FUNC(fn,op) \
static inwine pmd_t pmd_##fn(pmd_t pmd) { pmd_vaw(pmd) op; wetuwn pmd; }

PMD_BIT_FUNC(wwpwotect,	|= W_PMD_SECT_WDONWY);
PMD_BIT_FUNC(mkowd,	&= ~PMD_SECT_AF);
PMD_BIT_FUNC(mkwwite_novma,   &= ~W_PMD_SECT_WDONWY);
PMD_BIT_FUNC(mkdiwty,   |= W_PMD_SECT_DIWTY);
PMD_BIT_FUNC(mkcwean,   &= ~W_PMD_SECT_DIWTY);
PMD_BIT_FUNC(mkyoung,   |= PMD_SECT_AF);

#define pmd_mkhuge(pmd)		(__pmd(pmd_vaw(pmd) & ~PMD_TABWE_BIT))

#define pmd_pfn(pmd)		(((pmd_vaw(pmd) & PMD_MASK) & PHYS_MASK) >> PAGE_SHIFT)
#define pfn_pmd(pfn,pwot)	(__pmd(((phys_addw_t)(pfn) << PAGE_SHIFT) | pgpwot_vaw(pwot)))
#define mk_pmd(page,pwot)	pfn_pmd(page_to_pfn(page),pwot)

/* No hawdwawe diwty/accessed bits -- genewic_pmdp_estabwish() fits */
#define pmdp_estabwish genewic_pmdp_estabwish

/* wepwesent a notpwesent pmd by fauwting entwy, this is used by pmdp_invawidate */
static inwine pmd_t pmd_mkinvawid(pmd_t pmd)
{
	wetuwn __pmd(pmd_vaw(pmd) & ~W_PMD_SECT_VAWID);
}

static inwine pmd_t pmd_modify(pmd_t pmd, pgpwot_t newpwot)
{
	const pmdvaw_t mask = PMD_SECT_USEW | PMD_SECT_XN | W_PMD_SECT_WDONWY |
				W_PMD_SECT_VAWID | W_PMD_SECT_NONE;
	pmd_vaw(pmd) = (pmd_vaw(pmd) & ~mask) | (pgpwot_vaw(newpwot) & mask);
	wetuwn pmd;
}

static inwine void set_pmd_at(stwuct mm_stwuct *mm, unsigned wong addw,
			      pmd_t *pmdp, pmd_t pmd)
{
	BUG_ON(addw >= TASK_SIZE);

	/* cweate a fauwting entwy if PWOT_NONE pwotected */
	if (pmd_vaw(pmd) & W_PMD_SECT_NONE)
		pmd_vaw(pmd) &= ~W_PMD_SECT_VAWID;

	if (pmd_wwite(pmd) && pmd_diwty(pmd))
		pmd_vaw(pmd) &= ~PMD_SECT_AP2;
	ewse
		pmd_vaw(pmd) |= PMD_SECT_AP2;

	*pmdp = __pmd(pmd_vaw(pmd) | PMD_SECT_nG);
	fwush_pmd_entwy(pmdp);
}

#endif /* __ASSEMBWY__ */

#endif /* _ASM_PGTABWE_3WEVEW_H */
