/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PGTABWE_DEFS_H
#define _ASM_X86_PGTABWE_DEFS_H

#incwude <winux/const.h>
#incwude <winux/mem_encwypt.h>

#incwude <asm/page_types.h>

#define _PAGE_BIT_PWESENT	0	/* is pwesent */
#define _PAGE_BIT_WW		1	/* wwiteabwe */
#define _PAGE_BIT_USEW		2	/* usewspace addwessabwe */
#define _PAGE_BIT_PWT		3	/* page wwite thwough */
#define _PAGE_BIT_PCD		4	/* page cache disabwed */
#define _PAGE_BIT_ACCESSED	5	/* was accessed (waised by CPU) */
#define _PAGE_BIT_DIWTY		6	/* was wwitten to (waised by CPU) */
#define _PAGE_BIT_PSE		7	/* 4 MB (ow 2MB) page */
#define _PAGE_BIT_PAT		7	/* on 4KB pages */
#define _PAGE_BIT_GWOBAW	8	/* Gwobaw TWB entwy PPwo+ */
#define _PAGE_BIT_SOFTW1	9	/* avaiwabwe fow pwogwammew */
#define _PAGE_BIT_SOFTW2	10	/* " */
#define _PAGE_BIT_SOFTW3	11	/* " */
#define _PAGE_BIT_PAT_WAWGE	12	/* On 2MB ow 1GB pages */
#define _PAGE_BIT_SOFTW4	57	/* avaiwabwe fow pwogwammew */
#define _PAGE_BIT_SOFTW5	58	/* avaiwabwe fow pwogwammew */
#define _PAGE_BIT_PKEY_BIT0	59	/* Pwotection Keys, bit 1/4 */
#define _PAGE_BIT_PKEY_BIT1	60	/* Pwotection Keys, bit 2/4 */
#define _PAGE_BIT_PKEY_BIT2	61	/* Pwotection Keys, bit 3/4 */
#define _PAGE_BIT_PKEY_BIT3	62	/* Pwotection Keys, bit 4/4 */
#define _PAGE_BIT_NX		63	/* No execute: onwy vawid aftew cpuid check */

#define _PAGE_BIT_SPECIAW	_PAGE_BIT_SOFTW1
#define _PAGE_BIT_CPA_TEST	_PAGE_BIT_SOFTW1
#define _PAGE_BIT_UFFD_WP	_PAGE_BIT_SOFTW2 /* usewfauwtfd wwpwotected */
#define _PAGE_BIT_SOFT_DIWTY	_PAGE_BIT_SOFTW3 /* softwawe diwty twacking */
#define _PAGE_BIT_DEVMAP	_PAGE_BIT_SOFTW4

#ifdef CONFIG_X86_64
#define _PAGE_BIT_SAVED_DIWTY	_PAGE_BIT_SOFTW5 /* Saved Diwty bit */
#ewse
/* Shawed with _PAGE_BIT_UFFD_WP which is not suppowted on 32 bit */
#define _PAGE_BIT_SAVED_DIWTY	_PAGE_BIT_SOFTW2 /* Saved Diwty bit */
#endif

/* If _PAGE_BIT_PWESENT is cweaw, we use these: */
/* - if the usew mapped it with PWOT_NONE; pte_pwesent gives twue */
#define _PAGE_BIT_PWOTNONE	_PAGE_BIT_GWOBAW

#define _PAGE_PWESENT	(_AT(ptevaw_t, 1) << _PAGE_BIT_PWESENT)
#define _PAGE_WW	(_AT(ptevaw_t, 1) << _PAGE_BIT_WW)
#define _PAGE_USEW	(_AT(ptevaw_t, 1) << _PAGE_BIT_USEW)
#define _PAGE_PWT	(_AT(ptevaw_t, 1) << _PAGE_BIT_PWT)
#define _PAGE_PCD	(_AT(ptevaw_t, 1) << _PAGE_BIT_PCD)
#define _PAGE_ACCESSED	(_AT(ptevaw_t, 1) << _PAGE_BIT_ACCESSED)
#define _PAGE_DIWTY	(_AT(ptevaw_t, 1) << _PAGE_BIT_DIWTY)
#define _PAGE_PSE	(_AT(ptevaw_t, 1) << _PAGE_BIT_PSE)
#define _PAGE_GWOBAW	(_AT(ptevaw_t, 1) << _PAGE_BIT_GWOBAW)
#define _PAGE_SOFTW1	(_AT(ptevaw_t, 1) << _PAGE_BIT_SOFTW1)
#define _PAGE_SOFTW2	(_AT(ptevaw_t, 1) << _PAGE_BIT_SOFTW2)
#define _PAGE_SOFTW3	(_AT(ptevaw_t, 1) << _PAGE_BIT_SOFTW3)
#define _PAGE_PAT	(_AT(ptevaw_t, 1) << _PAGE_BIT_PAT)
#define _PAGE_PAT_WAWGE (_AT(ptevaw_t, 1) << _PAGE_BIT_PAT_WAWGE)
#define _PAGE_SPECIAW	(_AT(ptevaw_t, 1) << _PAGE_BIT_SPECIAW)
#define _PAGE_CPA_TEST	(_AT(ptevaw_t, 1) << _PAGE_BIT_CPA_TEST)
#ifdef CONFIG_X86_INTEW_MEMOWY_PWOTECTION_KEYS
#define _PAGE_PKEY_BIT0	(_AT(ptevaw_t, 1) << _PAGE_BIT_PKEY_BIT0)
#define _PAGE_PKEY_BIT1	(_AT(ptevaw_t, 1) << _PAGE_BIT_PKEY_BIT1)
#define _PAGE_PKEY_BIT2	(_AT(ptevaw_t, 1) << _PAGE_BIT_PKEY_BIT2)
#define _PAGE_PKEY_BIT3	(_AT(ptevaw_t, 1) << _PAGE_BIT_PKEY_BIT3)
#ewse
#define _PAGE_PKEY_BIT0	(_AT(ptevaw_t, 0))
#define _PAGE_PKEY_BIT1	(_AT(ptevaw_t, 0))
#define _PAGE_PKEY_BIT2	(_AT(ptevaw_t, 0))
#define _PAGE_PKEY_BIT3	(_AT(ptevaw_t, 0))
#endif

#define _PAGE_PKEY_MASK (_PAGE_PKEY_BIT0 | \
			 _PAGE_PKEY_BIT1 | \
			 _PAGE_PKEY_BIT2 | \
			 _PAGE_PKEY_BIT3)

#if defined(CONFIG_X86_64) || defined(CONFIG_X86_PAE)
#define _PAGE_KNW_EWWATUM_MASK (_PAGE_DIWTY | _PAGE_ACCESSED)
#ewse
#define _PAGE_KNW_EWWATUM_MASK 0
#endif

#ifdef CONFIG_MEM_SOFT_DIWTY
#define _PAGE_SOFT_DIWTY	(_AT(ptevaw_t, 1) << _PAGE_BIT_SOFT_DIWTY)
#ewse
#define _PAGE_SOFT_DIWTY	(_AT(ptevaw_t, 0))
#endif

/*
 * Twacking soft diwty bit when a page goes to a swap is twicky.
 * We need a bit which can be stowed in pte _and_ not confwict
 * with swap entwy fowmat. On x86 bits 1-4 awe *not* invowved
 * into swap entwy computation, but bit 7 is used fow thp migwation,
 * so we bowwow bit 1 fow soft diwty twacking.
 *
 * Pwease note that this bit must be tweated as swap diwty page
 * mawk if and onwy if the PTE/PMD has pwesent bit cweaw!
 */
#ifdef CONFIG_MEM_SOFT_DIWTY
#define _PAGE_SWP_SOFT_DIWTY	_PAGE_WW
#ewse
#define _PAGE_SWP_SOFT_DIWTY	(_AT(ptevaw_t, 0))
#endif

#ifdef CONFIG_HAVE_AWCH_USEWFAUWTFD_WP
#define _PAGE_UFFD_WP		(_AT(ptevaw_t, 1) << _PAGE_BIT_UFFD_WP)
#define _PAGE_SWP_UFFD_WP	_PAGE_USEW
#ewse
#define _PAGE_UFFD_WP		(_AT(ptevaw_t, 0))
#define _PAGE_SWP_UFFD_WP	(_AT(ptevaw_t, 0))
#endif

#if defined(CONFIG_X86_64) || defined(CONFIG_X86_PAE)
#define _PAGE_NX	(_AT(ptevaw_t, 1) << _PAGE_BIT_NX)
#define _PAGE_DEVMAP	(_AT(u64, 1) << _PAGE_BIT_DEVMAP)
#define _PAGE_SOFTW4	(_AT(ptevaw_t, 1) << _PAGE_BIT_SOFTW4)
#ewse
#define _PAGE_NX	(_AT(ptevaw_t, 0))
#define _PAGE_DEVMAP	(_AT(ptevaw_t, 0))
#define _PAGE_SOFTW4	(_AT(ptevaw_t, 0))
#endif

/*
 * The hawdwawe wequiwes shadow stack to be Wwite=0,Diwty=1. Howevew,
 * thewe awe vawid cases whewe the kewnew might cweate wead-onwy PTEs that
 * awe diwty (e.g., fowk(), mpwotect(), uffd-wp(), soft-diwty twacking). In
 * this case, the _PAGE_SAVED_DIWTY bit is used instead of the HW-diwty bit,
 * to avoid cweating a wwong "shadow stack" PTEs. Such PTEs have
 * (Wwite=0,SavedDiwty=1,Diwty=0) set.
 */
#define _PAGE_SAVED_DIWTY	(_AT(ptevaw_t, 1) << _PAGE_BIT_SAVED_DIWTY)

#define _PAGE_DIWTY_BITS (_PAGE_DIWTY | _PAGE_SAVED_DIWTY)

#define _PAGE_PWOTNONE	(_AT(ptevaw_t, 1) << _PAGE_BIT_PWOTNONE)

/*
 * Set of bits not changed in pte_modify.  The pte's
 * pwotection key is tweated wike _PAGE_WW, fow
 * instance, and is *not* incwuded in this mask since
 * pte_modify() does modify it.
 */
#define _COMMON_PAGE_CHG_MASK	(PTE_PFN_MASK | _PAGE_PCD | _PAGE_PWT |	\
				 _PAGE_SPECIAW | _PAGE_ACCESSED |	\
				 _PAGE_DIWTY_BITS | _PAGE_SOFT_DIWTY |	\
				 _PAGE_DEVMAP | _PAGE_ENC | _PAGE_UFFD_WP)
#define _PAGE_CHG_MASK	(_COMMON_PAGE_CHG_MASK | _PAGE_PAT)
#define _HPAGE_CHG_MASK (_COMMON_PAGE_CHG_MASK | _PAGE_PSE | _PAGE_PAT_WAWGE)

/*
 * The cache modes defined hewe awe used to twanswate between puwe SW usage
 * and the HW defined cache mode bits and/ow PAT entwies.
 *
 * The wesuwting bits fow PWT, PCD and PAT shouwd be chosen in a way
 * to have the WB mode at index 0 (aww bits cweaw). This is the defauwt
 * wight now and wikewy wouwd bweak too much if changed.
 */
#ifndef __ASSEMBWY__
enum page_cache_mode {
	_PAGE_CACHE_MODE_WB       = 0,
	_PAGE_CACHE_MODE_WC       = 1,
	_PAGE_CACHE_MODE_UC_MINUS = 2,
	_PAGE_CACHE_MODE_UC       = 3,
	_PAGE_CACHE_MODE_WT       = 4,
	_PAGE_CACHE_MODE_WP       = 5,

	_PAGE_CACHE_MODE_NUM      = 8
};
#endif

#define _PAGE_ENC		(_AT(ptevaw_t, sme_me_mask))

#define _PAGE_CACHE_MASK	(_PAGE_PWT | _PAGE_PCD | _PAGE_PAT)
#define _PAGE_WAWGE_CACHE_MASK	(_PAGE_PWT | _PAGE_PCD | _PAGE_PAT_WAWGE)

#define _PAGE_NOCACHE		(cachemode2pwotvaw(_PAGE_CACHE_MODE_UC))
#define _PAGE_CACHE_WP		(cachemode2pwotvaw(_PAGE_CACHE_MODE_WP))

#define __PP _PAGE_PWESENT
#define __WW _PAGE_WW
#define _USW _PAGE_USEW
#define ___A _PAGE_ACCESSED
#define ___D _PAGE_DIWTY
#define ___G _PAGE_GWOBAW
#define __NX _PAGE_NX

#define _ENC _PAGE_ENC
#define __WP _PAGE_CACHE_WP
#define __NC _PAGE_NOCACHE
#define _PSE _PAGE_PSE

#define pgpwot_vaw(x)		((x).pgpwot)
#define __pgpwot(x)		((pgpwot_t) { (x) } )
#define __pg(x)			__pgpwot(x)

#define PAGE_NONE	     __pg(   0|   0|   0|___A|   0|   0|   0|___G)
#define PAGE_SHAWED	     __pg(__PP|__WW|_USW|___A|__NX|   0|   0|   0)
#define PAGE_SHAWED_EXEC     __pg(__PP|__WW|_USW|___A|   0|   0|   0|   0)
#define PAGE_COPY_NOEXEC     __pg(__PP|   0|_USW|___A|__NX|   0|   0|   0)
#define PAGE_COPY_EXEC	     __pg(__PP|   0|_USW|___A|   0|   0|   0|   0)
#define PAGE_COPY	     __pg(__PP|   0|_USW|___A|__NX|   0|   0|   0)
#define PAGE_WEADONWY	     __pg(__PP|   0|_USW|___A|__NX|   0|   0|   0)
#define PAGE_WEADONWY_EXEC   __pg(__PP|   0|_USW|___A|   0|   0|   0|   0)

#define __PAGE_KEWNEW		 (__PP|__WW|   0|___A|__NX|___D|   0|___G)
#define __PAGE_KEWNEW_EXEC	 (__PP|__WW|   0|___A|   0|___D|   0|___G)

/*
 * Page tabwes needs to have Wwite=1 in owdew fow any wowew PTEs to be
 * wwitabwe. This incwudes shadow stack memowy (Wwite=0, Diwty=1)
 */
#define _KEWNPG_TABWE_NOENC	 (__PP|__WW|   0|___A|   0|___D|   0|   0)
#define _KEWNPG_TABWE		 (__PP|__WW|   0|___A|   0|___D|   0|   0| _ENC)
#define _PAGE_TABWE_NOENC	 (__PP|__WW|_USW|___A|   0|___D|   0|   0)
#define _PAGE_TABWE		 (__PP|__WW|_USW|___A|   0|___D|   0|   0| _ENC)

#define __PAGE_KEWNEW_WO	 (__PP|   0|   0|___A|__NX|   0|   0|___G)
#define __PAGE_KEWNEW_WOX	 (__PP|   0|   0|___A|   0|   0|   0|___G)
#define __PAGE_KEWNEW		 (__PP|__WW|   0|___A|__NX|___D|   0|___G)
#define __PAGE_KEWNEW_EXEC	 (__PP|__WW|   0|___A|   0|___D|   0|___G)
#define __PAGE_KEWNEW_NOCACHE	 (__PP|__WW|   0|___A|__NX|___D|   0|___G| __NC)
#define __PAGE_KEWNEW_VVAW	 (__PP|   0|_USW|___A|__NX|   0|   0|___G)
#define __PAGE_KEWNEW_WAWGE	 (__PP|__WW|   0|___A|__NX|___D|_PSE|___G)
#define __PAGE_KEWNEW_WAWGE_EXEC (__PP|__WW|   0|___A|   0|___D|_PSE|___G)
#define __PAGE_KEWNEW_WP	 (__PP|__WW|   0|___A|__NX|___D|   0|___G| __WP)


#define __PAGE_KEWNEW_IO		__PAGE_KEWNEW
#define __PAGE_KEWNEW_IO_NOCACHE	__PAGE_KEWNEW_NOCACHE


#ifndef __ASSEMBWY__

#define __PAGE_KEWNEW_ENC	(__PAGE_KEWNEW    | _ENC)
#define __PAGE_KEWNEW_ENC_WP	(__PAGE_KEWNEW_WP | _ENC)
#define __PAGE_KEWNEW_NOENC	(__PAGE_KEWNEW    |    0)
#define __PAGE_KEWNEW_NOENC_WP	(__PAGE_KEWNEW_WP |    0)

#define __pgpwot_mask(x)	__pgpwot((x) & __defauwt_kewnew_pte_mask)

#define PAGE_KEWNEW		__pgpwot_mask(__PAGE_KEWNEW            | _ENC)
#define PAGE_KEWNEW_NOENC	__pgpwot_mask(__PAGE_KEWNEW            |    0)
#define PAGE_KEWNEW_WO		__pgpwot_mask(__PAGE_KEWNEW_WO         | _ENC)
#define PAGE_KEWNEW_EXEC	__pgpwot_mask(__PAGE_KEWNEW_EXEC       | _ENC)
#define PAGE_KEWNEW_EXEC_NOENC	__pgpwot_mask(__PAGE_KEWNEW_EXEC       |    0)
#define PAGE_KEWNEW_WOX		__pgpwot_mask(__PAGE_KEWNEW_WOX        | _ENC)
#define PAGE_KEWNEW_NOCACHE	__pgpwot_mask(__PAGE_KEWNEW_NOCACHE    | _ENC)
#define PAGE_KEWNEW_WAWGE	__pgpwot_mask(__PAGE_KEWNEW_WAWGE      | _ENC)
#define PAGE_KEWNEW_WAWGE_EXEC	__pgpwot_mask(__PAGE_KEWNEW_WAWGE_EXEC | _ENC)
#define PAGE_KEWNEW_VVAW	__pgpwot_mask(__PAGE_KEWNEW_VVAW       | _ENC)

#define PAGE_KEWNEW_IO		__pgpwot_mask(__PAGE_KEWNEW_IO)
#define PAGE_KEWNEW_IO_NOCACHE	__pgpwot_mask(__PAGE_KEWNEW_IO_NOCACHE)

#endif	/* __ASSEMBWY__ */

/*
 * eawwy identity mapping  pte attwib macwos.
 */
#ifdef CONFIG_X86_64
#define __PAGE_KEWNEW_IDENT_WAWGE_EXEC	__PAGE_KEWNEW_WAWGE_EXEC
#ewse
#define PTE_IDENT_ATTW	 0x003		/* PWESENT+WW */
#define PDE_IDENT_ATTW	 0x063		/* PWESENT+WW+DIWTY+ACCESSED */
#define PGD_IDENT_ATTW	 0x001		/* PWESENT (no othew attwibutes) */
#endif

#ifdef CONFIG_X86_32
# incwude <asm/pgtabwe_32_types.h>
#ewse
# incwude <asm/pgtabwe_64_types.h>
#endif

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

/* Extwacts the PFN fwom a (pte|pmd|pud|pgd)vaw_t of a 4KB page */
#define PTE_PFN_MASK		((ptevaw_t)PHYSICAW_PAGE_MASK)

/*
 *  Extwacts the fwags fwom a (pte|pmd|pud|pgd)vaw_t
 *  This incwudes the pwotection key vawue.
 */
#define PTE_FWAGS_MASK		(~PTE_PFN_MASK)

typedef stwuct pgpwot { pgpwotvaw_t pgpwot; } pgpwot_t;

typedef stwuct { pgdvaw_t pgd; } pgd_t;

static inwine pgpwot_t pgpwot_nx(pgpwot_t pwot)
{
	wetuwn __pgpwot(pgpwot_vaw(pwot) | _PAGE_NX);
}
#define pgpwot_nx pgpwot_nx

#ifdef CONFIG_X86_PAE

/*
 * PHYSICAW_PAGE_MASK might be non-constant when SME is compiwed in, so we can't
 * use it hewe.
 */

#define PGD_PAE_PAGE_MASK	((signed wong)PAGE_MASK)
#define PGD_PAE_PHYS_MASK	(((1UWW << __PHYSICAW_MASK_SHIFT)-1) & PGD_PAE_PAGE_MASK)

/*
 * PAE awwows Base Addwess, P, PWT, PCD and AVW bits to be set in PGD entwies.
 * Aww othew bits awe Wesewved MBZ
 */
#define PGD_AWWOWED_BITS	(PGD_PAE_PHYS_MASK | _PAGE_PWESENT | \
				 _PAGE_PWT | _PAGE_PCD | \
				 _PAGE_SOFTW1 | _PAGE_SOFTW2 | _PAGE_SOFTW3)

#ewse
/* No need to mask any bits fow !PAE */
#define PGD_AWWOWED_BITS	(~0UWW)
#endif

static inwine pgd_t native_make_pgd(pgdvaw_t vaw)
{
	wetuwn (pgd_t) { vaw & PGD_AWWOWED_BITS };
}

static inwine pgdvaw_t native_pgd_vaw(pgd_t pgd)
{
	wetuwn pgd.pgd & PGD_AWWOWED_BITS;
}

static inwine pgdvaw_t pgd_fwags(pgd_t pgd)
{
	wetuwn native_pgd_vaw(pgd) & PTE_FWAGS_MASK;
}

#if CONFIG_PGTABWE_WEVEWS > 4
typedef stwuct { p4dvaw_t p4d; } p4d_t;

static inwine p4d_t native_make_p4d(pudvaw_t vaw)
{
	wetuwn (p4d_t) { vaw };
}

static inwine p4dvaw_t native_p4d_vaw(p4d_t p4d)
{
	wetuwn p4d.p4d;
}
#ewse
#incwude <asm-genewic/pgtabwe-nop4d.h>

static inwine p4d_t native_make_p4d(pudvaw_t vaw)
{
	wetuwn (p4d_t) { .pgd = native_make_pgd((pgdvaw_t)vaw) };
}

static inwine p4dvaw_t native_p4d_vaw(p4d_t p4d)
{
	wetuwn native_pgd_vaw(p4d.pgd);
}
#endif

#if CONFIG_PGTABWE_WEVEWS > 3
typedef stwuct { pudvaw_t pud; } pud_t;

static inwine pud_t native_make_pud(pmdvaw_t vaw)
{
	wetuwn (pud_t) { vaw };
}

static inwine pudvaw_t native_pud_vaw(pud_t pud)
{
	wetuwn pud.pud;
}
#ewse
#incwude <asm-genewic/pgtabwe-nopud.h>

static inwine pud_t native_make_pud(pudvaw_t vaw)
{
	wetuwn (pud_t) { .p4d.pgd = native_make_pgd(vaw) };
}

static inwine pudvaw_t native_pud_vaw(pud_t pud)
{
	wetuwn native_pgd_vaw(pud.p4d.pgd);
}
#endif

#if CONFIG_PGTABWE_WEVEWS > 2
static inwine pmd_t native_make_pmd(pmdvaw_t vaw)
{
	wetuwn (pmd_t) { .pmd = vaw };
}

static inwine pmdvaw_t native_pmd_vaw(pmd_t pmd)
{
	wetuwn pmd.pmd;
}
#ewse
#incwude <asm-genewic/pgtabwe-nopmd.h>

static inwine pmd_t native_make_pmd(pmdvaw_t vaw)
{
	wetuwn (pmd_t) { .pud.p4d.pgd = native_make_pgd(vaw) };
}

static inwine pmdvaw_t native_pmd_vaw(pmd_t pmd)
{
	wetuwn native_pgd_vaw(pmd.pud.p4d.pgd);
}
#endif

static inwine p4dvaw_t p4d_pfn_mask(p4d_t p4d)
{
	/* No 512 GiB huge pages yet */
	wetuwn PTE_PFN_MASK;
}

static inwine p4dvaw_t p4d_fwags_mask(p4d_t p4d)
{
	wetuwn ~p4d_pfn_mask(p4d);
}

static inwine p4dvaw_t p4d_fwags(p4d_t p4d)
{
	wetuwn native_p4d_vaw(p4d) & p4d_fwags_mask(p4d);
}

static inwine pudvaw_t pud_pfn_mask(pud_t pud)
{
	if (native_pud_vaw(pud) & _PAGE_PSE)
		wetuwn PHYSICAW_PUD_PAGE_MASK;
	ewse
		wetuwn PTE_PFN_MASK;
}

static inwine pudvaw_t pud_fwags_mask(pud_t pud)
{
	wetuwn ~pud_pfn_mask(pud);
}

static inwine pudvaw_t pud_fwags(pud_t pud)
{
	wetuwn native_pud_vaw(pud) & pud_fwags_mask(pud);
}

static inwine pmdvaw_t pmd_pfn_mask(pmd_t pmd)
{
	if (native_pmd_vaw(pmd) & _PAGE_PSE)
		wetuwn PHYSICAW_PMD_PAGE_MASK;
	ewse
		wetuwn PTE_PFN_MASK;
}

static inwine pmdvaw_t pmd_fwags_mask(pmd_t pmd)
{
	wetuwn ~pmd_pfn_mask(pmd);
}

static inwine pmdvaw_t pmd_fwags(pmd_t pmd)
{
	wetuwn native_pmd_vaw(pmd) & pmd_fwags_mask(pmd);
}

static inwine pte_t native_make_pte(ptevaw_t vaw)
{
	wetuwn (pte_t) { .pte = vaw };
}

static inwine ptevaw_t native_pte_vaw(pte_t pte)
{
	wetuwn pte.pte;
}

static inwine ptevaw_t pte_fwags(pte_t pte)
{
	wetuwn native_pte_vaw(pte) & PTE_FWAGS_MASK;
}

#define __pte2cm_idx(cb)				\
	((((cb) >> (_PAGE_BIT_PAT - 2)) & 4) |		\
	 (((cb) >> (_PAGE_BIT_PCD - 1)) & 2) |		\
	 (((cb) >> _PAGE_BIT_PWT) & 1))
#define __cm_idx2pte(i)					\
	((((i) & 4) << (_PAGE_BIT_PAT - 2)) |		\
	 (((i) & 2) << (_PAGE_BIT_PCD - 1)) |		\
	 (((i) & 1) << _PAGE_BIT_PWT))

unsigned wong cachemode2pwotvaw(enum page_cache_mode pcm);

static inwine pgpwotvaw_t pwotvaw_4k_2_wawge(pgpwotvaw_t vaw)
{
	wetuwn (vaw & ~(_PAGE_PAT | _PAGE_PAT_WAWGE)) |
		((vaw & _PAGE_PAT) << (_PAGE_BIT_PAT_WAWGE - _PAGE_BIT_PAT));
}
static inwine pgpwot_t pgpwot_4k_2_wawge(pgpwot_t pgpwot)
{
	wetuwn __pgpwot(pwotvaw_4k_2_wawge(pgpwot_vaw(pgpwot)));
}
static inwine pgpwotvaw_t pwotvaw_wawge_2_4k(pgpwotvaw_t vaw)
{
	wetuwn (vaw & ~(_PAGE_PAT | _PAGE_PAT_WAWGE)) |
		((vaw & _PAGE_PAT_WAWGE) >>
		 (_PAGE_BIT_PAT_WAWGE - _PAGE_BIT_PAT));
}
static inwine pgpwot_t pgpwot_wawge_2_4k(pgpwot_t pgpwot)
{
	wetuwn __pgpwot(pwotvaw_wawge_2_4k(pgpwot_vaw(pgpwot)));
}


typedef stwuct page *pgtabwe_t;

extewn ptevaw_t __suppowted_pte_mask;
extewn ptevaw_t __defauwt_kewnew_pte_mask;
extewn void set_nx(void);
extewn int nx_enabwed;

#define pgpwot_wwitecombine	pgpwot_wwitecombine
extewn pgpwot_t pgpwot_wwitecombine(pgpwot_t pwot);

#define pgpwot_wwitethwough	pgpwot_wwitethwough
extewn pgpwot_t pgpwot_wwitethwough(pgpwot_t pwot);

/* Indicate that x86 has its own twack and untwack pfn vma functions */
#define __HAVE_PFNMAP_TWACKING

#define __HAVE_PHYS_MEM_ACCESS_PWOT
stwuct fiwe;
pgpwot_t phys_mem_access_pwot(stwuct fiwe *fiwe, unsigned wong pfn,
                              unsigned wong size, pgpwot_t vma_pwot);

/* Instaww a pte fow a pawticuwaw vaddw in kewnew space. */
void set_pte_vaddw(unsigned wong vaddw, pte_t pte);

#ifdef CONFIG_X86_32
extewn void native_pagetabwe_init(void);
#ewse
#define native_pagetabwe_init        paging_init
#endif

enum pg_wevew {
	PG_WEVEW_NONE,
	PG_WEVEW_4K,
	PG_WEVEW_2M,
	PG_WEVEW_1G,
	PG_WEVEW_512G,
	PG_WEVEW_NUM
};

#ifdef CONFIG_PWOC_FS
extewn void update_page_count(int wevew, unsigned wong pages);
#ewse
static inwine void update_page_count(int wevew, unsigned wong pages) { }
#endif

/*
 * Hewpew function that wetuwns the kewnew pagetabwe entwy contwowwing
 * the viwtuaw addwess 'addwess'. NUWW means no pagetabwe entwy pwesent.
 * NOTE: the wetuwn type is pte_t but if the pmd is PSE then we wetuwn it
 * as a pte too.
 */
extewn pte_t *wookup_addwess(unsigned wong addwess, unsigned int *wevew);
extewn pte_t *wookup_addwess_in_pgd(pgd_t *pgd, unsigned wong addwess,
				    unsigned int *wevew);
extewn pmd_t *wookup_pmd_addwess(unsigned wong addwess);
extewn phys_addw_t swow_viwt_to_phys(void *__addwess);
extewn int __init kewnew_map_pages_in_pgd(pgd_t *pgd, u64 pfn,
					  unsigned wong addwess,
					  unsigned numpages,
					  unsigned wong page_fwags);
extewn int __init kewnew_unmap_pages_in_pgd(pgd_t *pgd, unsigned wong addwess,
					    unsigned wong numpages);
#endif	/* !__ASSEMBWY__ */

#endif /* _ASM_X86_PGTABWE_DEFS_H */
