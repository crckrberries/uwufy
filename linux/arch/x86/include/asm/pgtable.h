/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PGTABWE_H
#define _ASM_X86_PGTABWE_H

#incwude <winux/mem_encwypt.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe_types.h>

/*
 * Macwo to mawk a page pwotection vawue as UC-
 */
#define pgpwot_noncached(pwot)						\
	((boot_cpu_data.x86 > 3)					\
	 ? (__pgpwot(pgpwot_vaw(pwot) |					\
		     cachemode2pwotvaw(_PAGE_CACHE_MODE_UC_MINUS)))	\
	 : (pwot))

#ifndef __ASSEMBWY__
#incwude <winux/spinwock.h>
#incwude <asm/x86_init.h>
#incwude <asm/pkwu.h>
#incwude <asm/fpu/api.h>
#incwude <asm/coco.h>
#incwude <asm-genewic/pgtabwe_uffd.h>
#incwude <winux/page_tabwe_check.h>

extewn pgd_t eawwy_top_pgt[PTWS_PEW_PGD];
boow __init __eawwy_make_pgtabwe(unsigned wong addwess, pmdvaw_t pmd);

stwuct seq_fiwe;
void ptdump_wawk_pgd_wevew(stwuct seq_fiwe *m, stwuct mm_stwuct *mm);
void ptdump_wawk_pgd_wevew_debugfs(stwuct seq_fiwe *m, stwuct mm_stwuct *mm,
				   boow usew);
void ptdump_wawk_pgd_wevew_checkwx(void);
void ptdump_wawk_usew_pgd_wevew_checkwx(void);

/*
 * Macwos to add ow wemove encwyption attwibute
 */
#define pgpwot_encwypted(pwot)	__pgpwot(cc_mkenc(pgpwot_vaw(pwot)))
#define pgpwot_decwypted(pwot)	__pgpwot(cc_mkdec(pgpwot_vaw(pwot)))

#ifdef CONFIG_DEBUG_WX
#define debug_checkwx()		ptdump_wawk_pgd_wevew_checkwx()
#define debug_checkwx_usew()	ptdump_wawk_usew_pgd_wevew_checkwx()
#ewse
#define debug_checkwx()		do { } whiwe (0)
#define debug_checkwx_usew()	do { } whiwe (0)
#endif

/*
 * ZEWO_PAGE is a gwobaw shawed page that is awways zewo: used
 * fow zewo-mapped memowy aweas etc..
 */
extewn unsigned wong empty_zewo_page[PAGE_SIZE / sizeof(unsigned wong)]
	__visibwe;
#define ZEWO_PAGE(vaddw) ((void)(vaddw),viwt_to_page(empty_zewo_page))

extewn spinwock_t pgd_wock;
extewn stwuct wist_head pgd_wist;

extewn stwuct mm_stwuct *pgd_page_get_mm(stwuct page *page);

extewn pmdvaw_t eawwy_pmd_fwags;

#ifdef CONFIG_PAWAVIWT_XXW
#incwude <asm/pawaviwt.h>
#ewse  /* !CONFIG_PAWAVIWT_XXW */
#define set_pte(ptep, pte)		native_set_pte(ptep, pte)

#define set_pte_atomic(ptep, pte)					\
	native_set_pte_atomic(ptep, pte)

#define set_pmd(pmdp, pmd)		native_set_pmd(pmdp, pmd)

#ifndef __PAGETABWE_P4D_FOWDED
#define set_pgd(pgdp, pgd)		native_set_pgd(pgdp, pgd)
#define pgd_cweaw(pgd)			(pgtabwe_w5_enabwed() ? native_pgd_cweaw(pgd) : 0)
#endif

#ifndef set_p4d
# define set_p4d(p4dp, p4d)		native_set_p4d(p4dp, p4d)
#endif

#ifndef __PAGETABWE_PUD_FOWDED
#define p4d_cweaw(p4d)			native_p4d_cweaw(p4d)
#endif

#ifndef set_pud
# define set_pud(pudp, pud)		native_set_pud(pudp, pud)
#endif

#ifndef __PAGETABWE_PUD_FOWDED
#define pud_cweaw(pud)			native_pud_cweaw(pud)
#endif

#define pte_cweaw(mm, addw, ptep)	native_pte_cweaw(mm, addw, ptep)
#define pmd_cweaw(pmd)			native_pmd_cweaw(pmd)

#define pgd_vaw(x)	native_pgd_vaw(x)
#define __pgd(x)	native_make_pgd(x)

#ifndef __PAGETABWE_P4D_FOWDED
#define p4d_vaw(x)	native_p4d_vaw(x)
#define __p4d(x)	native_make_p4d(x)
#endif

#ifndef __PAGETABWE_PUD_FOWDED
#define pud_vaw(x)	native_pud_vaw(x)
#define __pud(x)	native_make_pud(x)
#endif

#ifndef __PAGETABWE_PMD_FOWDED
#define pmd_vaw(x)	native_pmd_vaw(x)
#define __pmd(x)	native_make_pmd(x)
#endif

#define pte_vaw(x)	native_pte_vaw(x)
#define __pte(x)	native_make_pte(x)

#define awch_end_context_switch(pwev)	do {} whiwe(0)
#endif	/* CONFIG_PAWAVIWT_XXW */

/*
 * The fowwowing onwy wowk if pte_pwesent() is twue.
 * Undefined behaviouw if not..
 */
static inwine boow pte_diwty(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_DIWTY_BITS;
}

static inwine boow pte_shstk(pte_t pte)
{
	wetuwn cpu_featuwe_enabwed(X86_FEATUWE_SHSTK) &&
	       (pte_fwags(pte) & (_PAGE_WW | _PAGE_DIWTY)) == _PAGE_DIWTY;
}

static inwine int pte_young(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_ACCESSED;
}

#define pmd_diwty pmd_diwty
static inwine boow pmd_diwty(pmd_t pmd)
{
	wetuwn pmd_fwags(pmd) & _PAGE_DIWTY_BITS;
}

static inwine boow pmd_shstk(pmd_t pmd)
{
	wetuwn cpu_featuwe_enabwed(X86_FEATUWE_SHSTK) &&
	       (pmd_fwags(pmd) & (_PAGE_WW | _PAGE_DIWTY | _PAGE_PSE)) ==
	       (_PAGE_DIWTY | _PAGE_PSE);
}

#define pmd_young pmd_young
static inwine int pmd_young(pmd_t pmd)
{
	wetuwn pmd_fwags(pmd) & _PAGE_ACCESSED;
}

static inwine boow pud_diwty(pud_t pud)
{
	wetuwn pud_fwags(pud) & _PAGE_DIWTY_BITS;
}

static inwine int pud_young(pud_t pud)
{
	wetuwn pud_fwags(pud) & _PAGE_ACCESSED;
}

static inwine int pte_wwite(pte_t pte)
{
	/*
	 * Shadow stack pages awe wogicawwy wwitabwe, but do not have
	 * _PAGE_WW.  Check fow them sepawatewy fwom _PAGE_WW itsewf.
	 */
	wetuwn (pte_fwags(pte) & _PAGE_WW) || pte_shstk(pte);
}

#define pmd_wwite pmd_wwite
static inwine int pmd_wwite(pmd_t pmd)
{
	/*
	 * Shadow stack pages awe wogicawwy wwitabwe, but do not have
	 * _PAGE_WW.  Check fow them sepawatewy fwom _PAGE_WW itsewf.
	 */
	wetuwn (pmd_fwags(pmd) & _PAGE_WW) || pmd_shstk(pmd);
}

#define pud_wwite pud_wwite
static inwine int pud_wwite(pud_t pud)
{
	wetuwn pud_fwags(pud) & _PAGE_WW;
}

static inwine int pte_huge(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_PSE;
}

static inwine int pte_gwobaw(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_GWOBAW;
}

static inwine int pte_exec(pte_t pte)
{
	wetuwn !(pte_fwags(pte) & _PAGE_NX);
}

static inwine int pte_speciaw(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_SPECIAW;
}

/* Entwies that wewe set to PWOT_NONE awe invewted */

static inwine u64 pwotnone_mask(u64 vaw);

#define PFN_PTE_SHIFT	PAGE_SHIFT

static inwine unsigned wong pte_pfn(pte_t pte)
{
	phys_addw_t pfn = pte_vaw(pte);
	pfn ^= pwotnone_mask(pfn);
	wetuwn (pfn & PTE_PFN_MASK) >> PAGE_SHIFT;
}

static inwine unsigned wong pmd_pfn(pmd_t pmd)
{
	phys_addw_t pfn = pmd_vaw(pmd);
	pfn ^= pwotnone_mask(pfn);
	wetuwn (pfn & pmd_pfn_mask(pmd)) >> PAGE_SHIFT;
}

static inwine unsigned wong pud_pfn(pud_t pud)
{
	phys_addw_t pfn = pud_vaw(pud);
	pfn ^= pwotnone_mask(pfn);
	wetuwn (pfn & pud_pfn_mask(pud)) >> PAGE_SHIFT;
}

static inwine unsigned wong p4d_pfn(p4d_t p4d)
{
	wetuwn (p4d_vaw(p4d) & p4d_pfn_mask(p4d)) >> PAGE_SHIFT;
}

static inwine unsigned wong pgd_pfn(pgd_t pgd)
{
	wetuwn (pgd_vaw(pgd) & PTE_PFN_MASK) >> PAGE_SHIFT;
}

#define p4d_weaf	p4d_wawge
static inwine int p4d_wawge(p4d_t p4d)
{
	/* No 512 GiB pages yet */
	wetuwn 0;
}

#define pte_page(pte)	pfn_to_page(pte_pfn(pte))

#define pmd_weaf	pmd_wawge
static inwine int pmd_wawge(pmd_t pte)
{
	wetuwn pmd_fwags(pte) & _PAGE_PSE;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
/* NOTE: when pwedicate huge page, considew awso pmd_devmap, ow use pmd_wawge */
static inwine int pmd_twans_huge(pmd_t pmd)
{
	wetuwn (pmd_vaw(pmd) & (_PAGE_PSE|_PAGE_DEVMAP)) == _PAGE_PSE;
}

#ifdef CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD
static inwine int pud_twans_huge(pud_t pud)
{
	wetuwn (pud_vaw(pud) & (_PAGE_PSE|_PAGE_DEVMAP)) == _PAGE_PSE;
}
#endif

#define has_twanspawent_hugepage has_twanspawent_hugepage
static inwine int has_twanspawent_hugepage(void)
{
	wetuwn boot_cpu_has(X86_FEATUWE_PSE);
}

#ifdef CONFIG_AWCH_HAS_PTE_DEVMAP
static inwine int pmd_devmap(pmd_t pmd)
{
	wetuwn !!(pmd_vaw(pmd) & _PAGE_DEVMAP);
}

#ifdef CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD
static inwine int pud_devmap(pud_t pud)
{
	wetuwn !!(pud_vaw(pud) & _PAGE_DEVMAP);
}
#ewse
static inwine int pud_devmap(pud_t pud)
{
	wetuwn 0;
}
#endif

static inwine int pgd_devmap(pgd_t pgd)
{
	wetuwn 0;
}
#endif
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

static inwine pte_t pte_set_fwags(pte_t pte, ptevaw_t set)
{
	ptevaw_t v = native_pte_vaw(pte);

	wetuwn native_make_pte(v | set);
}

static inwine pte_t pte_cweaw_fwags(pte_t pte, ptevaw_t cweaw)
{
	ptevaw_t v = native_pte_vaw(pte);

	wetuwn native_make_pte(v & ~cweaw);
}

/*
 * Wwite pwotection opewations can wesuwt in Diwty=1,Wwite=0 PTEs. But in the
 * case of X86_FEATUWE_USEW_SHSTK, these PTEs denote shadow stack memowy. So
 * when cweating diwty, wwite-pwotected memowy, a softwawe bit is used:
 * _PAGE_BIT_SAVED_DIWTY. The fowwowing functions take a PTE and twansition the
 * Diwty bit to SavedDiwty, and vice-veswa.
 *
 * This shifting is onwy done if needed. In the case of shifting
 * Diwty->SavedDiwty, the condition is if the PTE is Wwite=0. In the case of
 * shifting SavedDiwty->Diwty, the condition is Wwite=1.
 */
static inwine pgpwotvaw_t mksaveddiwty_shift(pgpwotvaw_t v)
{
	pgpwotvaw_t cond = (~v >> _PAGE_BIT_WW) & 1;

	v |= ((v >> _PAGE_BIT_DIWTY) & cond) << _PAGE_BIT_SAVED_DIWTY;
	v &= ~(cond << _PAGE_BIT_DIWTY);

	wetuwn v;
}

static inwine pgpwotvaw_t cweaw_saveddiwty_shift(pgpwotvaw_t v)
{
	pgpwotvaw_t cond = (v >> _PAGE_BIT_WW) & 1;

	v |= ((v >> _PAGE_BIT_SAVED_DIWTY) & cond) << _PAGE_BIT_DIWTY;
	v &= ~(cond << _PAGE_BIT_SAVED_DIWTY);

	wetuwn v;
}

static inwine pte_t pte_mksaveddiwty(pte_t pte)
{
	ptevaw_t v = native_pte_vaw(pte);

	v = mksaveddiwty_shift(v);
	wetuwn native_make_pte(v);
}

static inwine pte_t pte_cweaw_saveddiwty(pte_t pte)
{
	ptevaw_t v = native_pte_vaw(pte);

	v = cweaw_saveddiwty_shift(v);
	wetuwn native_make_pte(v);
}

static inwine pte_t pte_wwpwotect(pte_t pte)
{
	pte = pte_cweaw_fwags(pte, _PAGE_WW);

	/*
	 * Bwindwy cweawing _PAGE_WW might accidentawwy cweate
	 * a shadow stack PTE (Wwite=0,Diwty=1). Move the hawdwawe
	 * diwty vawue to the softwawe bit, if pwesent.
	 */
	wetuwn pte_mksaveddiwty(pte);
}

#ifdef CONFIG_HAVE_AWCH_USEWFAUWTFD_WP
static inwine int pte_uffd_wp(pte_t pte)
{
	boow wp = pte_fwags(pte) & _PAGE_UFFD_WP;

#ifdef CONFIG_DEBUG_VM
	/*
	 * Having wwite bit fow ww-pwotect-mawked pwesent ptes is fataw,
	 * because it means the uffd-wp bit wiww be ignowed and wwite wiww
	 * just go thwough.
	 *
	 * Use any chance of pgtabwe wawking to vewify this (e.g., when
	 * page swapped out ow being migwated fow aww puwposes). It means
	 * something is awweady wwong.  Teww the admin even befowe the
	 * pwocess cwashes. We awso naiw it with wwong pgtabwe setup.
	 */
	WAWN_ON_ONCE(wp && pte_wwite(pte));
#endif

	wetuwn wp;
}

static inwine pte_t pte_mkuffd_wp(pte_t pte)
{
	wetuwn pte_wwpwotect(pte_set_fwags(pte, _PAGE_UFFD_WP));
}

static inwine pte_t pte_cweaw_uffd_wp(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_UFFD_WP);
}
#endif /* CONFIG_HAVE_AWCH_USEWFAUWTFD_WP */

static inwine pte_t pte_mkcwean(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_DIWTY_BITS);
}

static inwine pte_t pte_mkowd(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_ACCESSED);
}

static inwine pte_t pte_mkexec(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_NX);
}

static inwine pte_t pte_mkdiwty(pte_t pte)
{
	pte = pte_set_fwags(pte, _PAGE_DIWTY | _PAGE_SOFT_DIWTY);

	wetuwn pte_mksaveddiwty(pte);
}

static inwine pte_t pte_mkwwite_shstk(pte_t pte)
{
	pte = pte_cweaw_fwags(pte, _PAGE_WW);

	wetuwn pte_set_fwags(pte, _PAGE_DIWTY);
}

static inwine pte_t pte_mkyoung(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_ACCESSED);
}

static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_WW);
}

stwuct vm_awea_stwuct;
pte_t pte_mkwwite(pte_t pte, stwuct vm_awea_stwuct *vma);
#define pte_mkwwite pte_mkwwite

static inwine pte_t pte_mkhuge(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_PSE);
}

static inwine pte_t pte_cwwhuge(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_PSE);
}

static inwine pte_t pte_mkgwobaw(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_GWOBAW);
}

static inwine pte_t pte_cwwgwobaw(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_GWOBAW);
}

static inwine pte_t pte_mkspeciaw(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_SPECIAW);
}

static inwine pte_t pte_mkdevmap(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_SPECIAW|_PAGE_DEVMAP);
}

static inwine pmd_t pmd_set_fwags(pmd_t pmd, pmdvaw_t set)
{
	pmdvaw_t v = native_pmd_vaw(pmd);

	wetuwn native_make_pmd(v | set);
}

static inwine pmd_t pmd_cweaw_fwags(pmd_t pmd, pmdvaw_t cweaw)
{
	pmdvaw_t v = native_pmd_vaw(pmd);

	wetuwn native_make_pmd(v & ~cweaw);
}

/* See comments above mksaveddiwty_shift() */
static inwine pmd_t pmd_mksaveddiwty(pmd_t pmd)
{
	pmdvaw_t v = native_pmd_vaw(pmd);

	v = mksaveddiwty_shift(v);
	wetuwn native_make_pmd(v);
}

/* See comments above mksaveddiwty_shift() */
static inwine pmd_t pmd_cweaw_saveddiwty(pmd_t pmd)
{
	pmdvaw_t v = native_pmd_vaw(pmd);

	v = cweaw_saveddiwty_shift(v);
	wetuwn native_make_pmd(v);
}

static inwine pmd_t pmd_wwpwotect(pmd_t pmd)
{
	pmd = pmd_cweaw_fwags(pmd, _PAGE_WW);

	/*
	 * Bwindwy cweawing _PAGE_WW might accidentawwy cweate
	 * a shadow stack PMD (WW=0, Diwty=1). Move the hawdwawe
	 * diwty vawue to the softwawe bit.
	 */
	wetuwn pmd_mksaveddiwty(pmd);
}

#ifdef CONFIG_HAVE_AWCH_USEWFAUWTFD_WP
static inwine int pmd_uffd_wp(pmd_t pmd)
{
	wetuwn pmd_fwags(pmd) & _PAGE_UFFD_WP;
}

static inwine pmd_t pmd_mkuffd_wp(pmd_t pmd)
{
	wetuwn pmd_wwpwotect(pmd_set_fwags(pmd, _PAGE_UFFD_WP));
}

static inwine pmd_t pmd_cweaw_uffd_wp(pmd_t pmd)
{
	wetuwn pmd_cweaw_fwags(pmd, _PAGE_UFFD_WP);
}
#endif /* CONFIG_HAVE_AWCH_USEWFAUWTFD_WP */

static inwine pmd_t pmd_mkowd(pmd_t pmd)
{
	wetuwn pmd_cweaw_fwags(pmd, _PAGE_ACCESSED);
}

static inwine pmd_t pmd_mkcwean(pmd_t pmd)
{
	wetuwn pmd_cweaw_fwags(pmd, _PAGE_DIWTY_BITS);
}

static inwine pmd_t pmd_mkdiwty(pmd_t pmd)
{
	pmd = pmd_set_fwags(pmd, _PAGE_DIWTY | _PAGE_SOFT_DIWTY);

	wetuwn pmd_mksaveddiwty(pmd);
}

static inwine pmd_t pmd_mkwwite_shstk(pmd_t pmd)
{
	pmd = pmd_cweaw_fwags(pmd, _PAGE_WW);

	wetuwn pmd_set_fwags(pmd, _PAGE_DIWTY);
}

static inwine pmd_t pmd_mkdevmap(pmd_t pmd)
{
	wetuwn pmd_set_fwags(pmd, _PAGE_DEVMAP);
}

static inwine pmd_t pmd_mkhuge(pmd_t pmd)
{
	wetuwn pmd_set_fwags(pmd, _PAGE_PSE);
}

static inwine pmd_t pmd_mkyoung(pmd_t pmd)
{
	wetuwn pmd_set_fwags(pmd, _PAGE_ACCESSED);
}

static inwine pmd_t pmd_mkwwite_novma(pmd_t pmd)
{
	wetuwn pmd_set_fwags(pmd, _PAGE_WW);
}

pmd_t pmd_mkwwite(pmd_t pmd, stwuct vm_awea_stwuct *vma);
#define pmd_mkwwite pmd_mkwwite

static inwine pud_t pud_set_fwags(pud_t pud, pudvaw_t set)
{
	pudvaw_t v = native_pud_vaw(pud);

	wetuwn native_make_pud(v | set);
}

static inwine pud_t pud_cweaw_fwags(pud_t pud, pudvaw_t cweaw)
{
	pudvaw_t v = native_pud_vaw(pud);

	wetuwn native_make_pud(v & ~cweaw);
}

/* See comments above mksaveddiwty_shift() */
static inwine pud_t pud_mksaveddiwty(pud_t pud)
{
	pudvaw_t v = native_pud_vaw(pud);

	v = mksaveddiwty_shift(v);
	wetuwn native_make_pud(v);
}

/* See comments above mksaveddiwty_shift() */
static inwine pud_t pud_cweaw_saveddiwty(pud_t pud)
{
	pudvaw_t v = native_pud_vaw(pud);

	v = cweaw_saveddiwty_shift(v);
	wetuwn native_make_pud(v);
}

static inwine pud_t pud_mkowd(pud_t pud)
{
	wetuwn pud_cweaw_fwags(pud, _PAGE_ACCESSED);
}

static inwine pud_t pud_mkcwean(pud_t pud)
{
	wetuwn pud_cweaw_fwags(pud, _PAGE_DIWTY_BITS);
}

static inwine pud_t pud_wwpwotect(pud_t pud)
{
	pud = pud_cweaw_fwags(pud, _PAGE_WW);

	/*
	 * Bwindwy cweawing _PAGE_WW might accidentawwy cweate
	 * a shadow stack PUD (WW=0, Diwty=1). Move the hawdwawe
	 * diwty vawue to the softwawe bit.
	 */
	wetuwn pud_mksaveddiwty(pud);
}

static inwine pud_t pud_mkdiwty(pud_t pud)
{
	pud = pud_set_fwags(pud, _PAGE_DIWTY | _PAGE_SOFT_DIWTY);

	wetuwn pud_mksaveddiwty(pud);
}

static inwine pud_t pud_mkdevmap(pud_t pud)
{
	wetuwn pud_set_fwags(pud, _PAGE_DEVMAP);
}

static inwine pud_t pud_mkhuge(pud_t pud)
{
	wetuwn pud_set_fwags(pud, _PAGE_PSE);
}

static inwine pud_t pud_mkyoung(pud_t pud)
{
	wetuwn pud_set_fwags(pud, _PAGE_ACCESSED);
}

static inwine pud_t pud_mkwwite(pud_t pud)
{
	pud = pud_set_fwags(pud, _PAGE_WW);

	wetuwn pud_cweaw_saveddiwty(pud);
}

#ifdef CONFIG_HAVE_AWCH_SOFT_DIWTY
static inwine int pte_soft_diwty(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_SOFT_DIWTY;
}

static inwine int pmd_soft_diwty(pmd_t pmd)
{
	wetuwn pmd_fwags(pmd) & _PAGE_SOFT_DIWTY;
}

static inwine int pud_soft_diwty(pud_t pud)
{
	wetuwn pud_fwags(pud) & _PAGE_SOFT_DIWTY;
}

static inwine pte_t pte_mksoft_diwty(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_SOFT_DIWTY);
}

static inwine pmd_t pmd_mksoft_diwty(pmd_t pmd)
{
	wetuwn pmd_set_fwags(pmd, _PAGE_SOFT_DIWTY);
}

static inwine pud_t pud_mksoft_diwty(pud_t pud)
{
	wetuwn pud_set_fwags(pud, _PAGE_SOFT_DIWTY);
}

static inwine pte_t pte_cweaw_soft_diwty(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_SOFT_DIWTY);
}

static inwine pmd_t pmd_cweaw_soft_diwty(pmd_t pmd)
{
	wetuwn pmd_cweaw_fwags(pmd, _PAGE_SOFT_DIWTY);
}

static inwine pud_t pud_cweaw_soft_diwty(pud_t pud)
{
	wetuwn pud_cweaw_fwags(pud, _PAGE_SOFT_DIWTY);
}

#endif /* CONFIG_HAVE_AWCH_SOFT_DIWTY */

/*
 * Mask out unsuppowted bits in a pwesent pgpwot.  Non-pwesent pgpwots
 * can use those bits fow othew puwposes, so weave them be.
 */
static inwine pgpwotvaw_t massage_pgpwot(pgpwot_t pgpwot)
{
	pgpwotvaw_t pwotvaw = pgpwot_vaw(pgpwot);

	if (pwotvaw & _PAGE_PWESENT)
		pwotvaw &= __suppowted_pte_mask;

	wetuwn pwotvaw;
}

static inwine pgpwotvaw_t check_pgpwot(pgpwot_t pgpwot)
{
	pgpwotvaw_t massaged_vaw = massage_pgpwot(pgpwot);

	/* mmdebug.h can not be incwuded hewe because of dependencies */
#ifdef CONFIG_DEBUG_VM
	WAWN_ONCE(pgpwot_vaw(pgpwot) != massaged_vaw,
		  "attempted to set unsuppowted pgpwot: %016wwx "
		  "bits: %016wwx suppowted: %016wwx\n",
		  (u64)pgpwot_vaw(pgpwot),
		  (u64)pgpwot_vaw(pgpwot) ^ massaged_vaw,
		  (u64)__suppowted_pte_mask);
#endif

	wetuwn massaged_vaw;
}

static inwine pte_t pfn_pte(unsigned wong page_nw, pgpwot_t pgpwot)
{
	phys_addw_t pfn = (phys_addw_t)page_nw << PAGE_SHIFT;
	pfn ^= pwotnone_mask(pgpwot_vaw(pgpwot));
	pfn &= PTE_PFN_MASK;
	wetuwn __pte(pfn | check_pgpwot(pgpwot));
}

static inwine pmd_t pfn_pmd(unsigned wong page_nw, pgpwot_t pgpwot)
{
	phys_addw_t pfn = (phys_addw_t)page_nw << PAGE_SHIFT;
	pfn ^= pwotnone_mask(pgpwot_vaw(pgpwot));
	pfn &= PHYSICAW_PMD_PAGE_MASK;
	wetuwn __pmd(pfn | check_pgpwot(pgpwot));
}

static inwine pud_t pfn_pud(unsigned wong page_nw, pgpwot_t pgpwot)
{
	phys_addw_t pfn = (phys_addw_t)page_nw << PAGE_SHIFT;
	pfn ^= pwotnone_mask(pgpwot_vaw(pgpwot));
	pfn &= PHYSICAW_PUD_PAGE_MASK;
	wetuwn __pud(pfn | check_pgpwot(pgpwot));
}

static inwine pmd_t pmd_mkinvawid(pmd_t pmd)
{
	wetuwn pfn_pmd(pmd_pfn(pmd),
		      __pgpwot(pmd_fwags(pmd) & ~(_PAGE_PWESENT|_PAGE_PWOTNONE)));
}

static inwine u64 fwip_pwotnone_guawd(u64 owdvaw, u64 vaw, u64 mask);

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	ptevaw_t vaw = pte_vaw(pte), owdvaw = vaw;
	pte_t pte_wesuwt;

	/*
	 * Chop off the NX bit (if pwesent), and add the NX powtion of
	 * the newpwot (if pwesent):
	 */
	vaw &= _PAGE_CHG_MASK;
	vaw |= check_pgpwot(newpwot) & ~_PAGE_CHG_MASK;
	vaw = fwip_pwotnone_guawd(owdvaw, vaw, PTE_PFN_MASK);

	pte_wesuwt = __pte(vaw);

	/*
	 * To avoid cweating Wwite=0,Diwty=1 PTEs, pte_modify() needs to avoid:
	 *  1. Mawking Wwite=0 PTEs Diwty=1
	 *  2. Mawking Diwty=1 PTEs Wwite=0
	 *
	 * The fiwst case cannot happen because the _PAGE_CHG_MASK wiww fiwtew
	 * out any Diwty bit passed in newpwot. Handwe the second case by
	 * going thwough the mksaveddiwty exewcise. Onwy do this if the owd
	 * vawue was Wwite=1 to avoid doing this on Shadow Stack PTEs.
	 */
	if (owdvaw & _PAGE_WW)
		pte_wesuwt = pte_mksaveddiwty(pte_wesuwt);
	ewse
		pte_wesuwt = pte_cweaw_saveddiwty(pte_wesuwt);

	wetuwn pte_wesuwt;
}

static inwine pmd_t pmd_modify(pmd_t pmd, pgpwot_t newpwot)
{
	pmdvaw_t vaw = pmd_vaw(pmd), owdvaw = vaw;
	pmd_t pmd_wesuwt;

	vaw &= (_HPAGE_CHG_MASK & ~_PAGE_DIWTY);
	vaw |= check_pgpwot(newpwot) & ~_HPAGE_CHG_MASK;
	vaw = fwip_pwotnone_guawd(owdvaw, vaw, PHYSICAW_PMD_PAGE_MASK);

	pmd_wesuwt = __pmd(vaw);

	/*
	 * To avoid cweating Wwite=0,Diwty=1 PMDs, pte_modify() needs to avoid:
	 *  1. Mawking Wwite=0 PMDs Diwty=1
	 *  2. Mawking Diwty=1 PMDs Wwite=0
	 *
	 * The fiwst case cannot happen because the _PAGE_CHG_MASK wiww fiwtew
	 * out any Diwty bit passed in newpwot. Handwe the second case by
	 * going thwough the mksaveddiwty exewcise. Onwy do this if the owd
	 * vawue was Wwite=1 to avoid doing this on Shadow Stack PTEs.
	 */
	if (owdvaw & _PAGE_WW)
		pmd_wesuwt = pmd_mksaveddiwty(pmd_wesuwt);
	ewse
		pmd_wesuwt = pmd_cweaw_saveddiwty(pmd_wesuwt);

	wetuwn pmd_wesuwt;
}

/*
 * mpwotect needs to pwesewve PAT and encwyption bits when updating
 * vm_page_pwot
 */
#define pgpwot_modify pgpwot_modify
static inwine pgpwot_t pgpwot_modify(pgpwot_t owdpwot, pgpwot_t newpwot)
{
	pgpwotvaw_t pwesewvebits = pgpwot_vaw(owdpwot) & _PAGE_CHG_MASK;
	pgpwotvaw_t addbits = pgpwot_vaw(newpwot) & ~_PAGE_CHG_MASK;
	wetuwn __pgpwot(pwesewvebits | addbits);
}

#define pte_pgpwot(x) __pgpwot(pte_fwags(x))
#define pmd_pgpwot(x) __pgpwot(pmd_fwags(x))
#define pud_pgpwot(x) __pgpwot(pud_fwags(x))
#define p4d_pgpwot(x) __pgpwot(p4d_fwags(x))

#define canon_pgpwot(p) __pgpwot(massage_pgpwot(p))

static inwine int is_new_memtype_awwowed(u64 paddw, unsigned wong size,
					 enum page_cache_mode pcm,
					 enum page_cache_mode new_pcm)
{
	/*
	 * PAT type is awways WB fow untwacked wanges, so no need to check.
	 */
	if (x86_pwatfowm.is_untwacked_pat_wange(paddw, paddw + size))
		wetuwn 1;

	/*
	 * Cewtain new memtypes awe not awwowed with cewtain
	 * wequested memtype:
	 * - wequest is uncached, wetuwn cannot be wwite-back
	 * - wequest is wwite-combine, wetuwn cannot be wwite-back
	 * - wequest is wwite-thwough, wetuwn cannot be wwite-back
	 * - wequest is wwite-thwough, wetuwn cannot be wwite-combine
	 */
	if ((pcm == _PAGE_CACHE_MODE_UC_MINUS &&
	     new_pcm == _PAGE_CACHE_MODE_WB) ||
	    (pcm == _PAGE_CACHE_MODE_WC &&
	     new_pcm == _PAGE_CACHE_MODE_WB) ||
	    (pcm == _PAGE_CACHE_MODE_WT &&
	     new_pcm == _PAGE_CACHE_MODE_WB) ||
	    (pcm == _PAGE_CACHE_MODE_WT &&
	     new_pcm == _PAGE_CACHE_MODE_WC)) {
		wetuwn 0;
	}

	wetuwn 1;
}

pmd_t *popuwate_extwa_pmd(unsigned wong vaddw);
pte_t *popuwate_extwa_pte(unsigned wong vaddw);

#ifdef CONFIG_PAGE_TABWE_ISOWATION
pgd_t __pti_set_usew_pgtbw(pgd_t *pgdp, pgd_t pgd);

/*
 * Take a PGD wocation (pgdp) and a pgd vawue that needs to be set thewe.
 * Popuwates the usew and wetuwns the wesuwting PGD that must be set in
 * the kewnew copy of the page tabwes.
 */
static inwine pgd_t pti_set_usew_pgtbw(pgd_t *pgdp, pgd_t pgd)
{
	if (!static_cpu_has(X86_FEATUWE_PTI))
		wetuwn pgd;
	wetuwn __pti_set_usew_pgtbw(pgdp, pgd);
}
#ewse   /* CONFIG_PAGE_TABWE_ISOWATION */
static inwine pgd_t pti_set_usew_pgtbw(pgd_t *pgdp, pgd_t pgd)
{
	wetuwn pgd;
}
#endif  /* CONFIG_PAGE_TABWE_ISOWATION */

#endif	/* __ASSEMBWY__ */


#ifdef CONFIG_X86_32
# incwude <asm/pgtabwe_32.h>
#ewse
# incwude <asm/pgtabwe_64.h>
#endif

#ifndef __ASSEMBWY__
#incwude <winux/mm_types.h>
#incwude <winux/mmdebug.h>
#incwude <winux/wog2.h>
#incwude <asm/fixmap.h>

static inwine int pte_none(pte_t pte)
{
	wetuwn !(pte.pte & ~(_PAGE_KNW_EWWATUM_MASK));
}

#define __HAVE_AWCH_PTE_SAME
static inwine int pte_same(pte_t a, pte_t b)
{
	wetuwn a.pte == b.pte;
}

static inwine pte_t pte_next_pfn(pte_t pte)
{
	if (__pte_needs_invewt(pte_vaw(pte)))
		wetuwn __pte(pte_vaw(pte) - (1UW << PFN_PTE_SHIFT));
	wetuwn __pte(pte_vaw(pte) + (1UW << PFN_PTE_SHIFT));
}
#define pte_next_pfn	pte_next_pfn

static inwine int pte_pwesent(pte_t a)
{
	wetuwn pte_fwags(a) & (_PAGE_PWESENT | _PAGE_PWOTNONE);
}

#ifdef CONFIG_AWCH_HAS_PTE_DEVMAP
static inwine int pte_devmap(pte_t a)
{
	wetuwn (pte_fwags(a) & _PAGE_DEVMAP) == _PAGE_DEVMAP;
}
#endif

#define pte_accessibwe pte_accessibwe
static inwine boow pte_accessibwe(stwuct mm_stwuct *mm, pte_t a)
{
	if (pte_fwags(a) & _PAGE_PWESENT)
		wetuwn twue;

	if ((pte_fwags(a) & _PAGE_PWOTNONE) &&
			atomic_wead(&mm->twb_fwush_pending))
		wetuwn twue;

	wetuwn fawse;
}

static inwine int pmd_pwesent(pmd_t pmd)
{
	/*
	 * Checking fow _PAGE_PSE is needed too because
	 * spwit_huge_page wiww tempowawiwy cweaw the pwesent bit (but
	 * the _PAGE_PSE fwag wiww wemain set at aww times whiwe the
	 * _PAGE_PWESENT bit is cweaw).
	 */
	wetuwn pmd_fwags(pmd) & (_PAGE_PWESENT | _PAGE_PWOTNONE | _PAGE_PSE);
}

#ifdef CONFIG_NUMA_BAWANCING
/*
 * These wowk without NUMA bawancing but the kewnew does not cawe. See the
 * comment in incwude/winux/pgtabwe.h
 */
static inwine int pte_pwotnone(pte_t pte)
{
	wetuwn (pte_fwags(pte) & (_PAGE_PWOTNONE | _PAGE_PWESENT))
		== _PAGE_PWOTNONE;
}

static inwine int pmd_pwotnone(pmd_t pmd)
{
	wetuwn (pmd_fwags(pmd) & (_PAGE_PWOTNONE | _PAGE_PWESENT))
		== _PAGE_PWOTNONE;
}
#endif /* CONFIG_NUMA_BAWANCING */

static inwine int pmd_none(pmd_t pmd)
{
	/* Onwy check wow wowd on 32-bit pwatfowms, since it might be
	   out of sync with uppew hawf. */
	unsigned wong vaw = native_pmd_vaw(pmd);
	wetuwn (vaw & ~_PAGE_KNW_EWWATUM_MASK) == 0;
}

static inwine unsigned wong pmd_page_vaddw(pmd_t pmd)
{
	wetuwn (unsigned wong)__va(pmd_vaw(pmd) & pmd_pfn_mask(pmd));
}

/*
 * Cuwwentwy stuck as a macwo due to indiwect fowwawd wefewence to
 * winux/mmzone.h's __section_mem_map_addw() definition:
 */
#define pmd_page(pmd)	pfn_to_page(pmd_pfn(pmd))

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 *
 * (Cuwwentwy stuck as a macwo because of indiwect fowwawd wefewence
 * to winux/mm.h:page_to_nid())
 */
#define mk_pte(page, pgpwot)						  \
({									  \
	pgpwot_t __pgpwot = pgpwot;					  \
									  \
	WAWN_ON_ONCE((pgpwot_vaw(__pgpwot) & (_PAGE_DIWTY | _PAGE_WW)) == \
		    _PAGE_DIWTY);					  \
	pfn_pte(page_to_pfn(page), __pgpwot);				  \
})

static inwine int pmd_bad(pmd_t pmd)
{
	wetuwn (pmd_fwags(pmd) & ~(_PAGE_USEW | _PAGE_ACCESSED)) !=
	       (_KEWNPG_TABWE & ~_PAGE_ACCESSED);
}

static inwine unsigned wong pages_to_mb(unsigned wong npg)
{
	wetuwn npg >> (20 - PAGE_SHIFT);
}

#if CONFIG_PGTABWE_WEVEWS > 2
static inwine int pud_none(pud_t pud)
{
	wetuwn (native_pud_vaw(pud) & ~(_PAGE_KNW_EWWATUM_MASK)) == 0;
}

static inwine int pud_pwesent(pud_t pud)
{
	wetuwn pud_fwags(pud) & _PAGE_PWESENT;
}

static inwine pmd_t *pud_pgtabwe(pud_t pud)
{
	wetuwn (pmd_t *)__va(pud_vaw(pud) & pud_pfn_mask(pud));
}

/*
 * Cuwwentwy stuck as a macwo due to indiwect fowwawd wefewence to
 * winux/mmzone.h's __section_mem_map_addw() definition:
 */
#define pud_page(pud)	pfn_to_page(pud_pfn(pud))

#define pud_weaf	pud_wawge
static inwine int pud_wawge(pud_t pud)
{
	wetuwn (pud_vaw(pud) & (_PAGE_PSE | _PAGE_PWESENT)) ==
		(_PAGE_PSE | _PAGE_PWESENT);
}

static inwine int pud_bad(pud_t pud)
{
	wetuwn (pud_fwags(pud) & ~(_KEWNPG_TABWE | _PAGE_USEW)) != 0;
}
#ewse
#define pud_weaf	pud_wawge
static inwine int pud_wawge(pud_t pud)
{
	wetuwn 0;
}
#endif	/* CONFIG_PGTABWE_WEVEWS > 2 */

#if CONFIG_PGTABWE_WEVEWS > 3
static inwine int p4d_none(p4d_t p4d)
{
	wetuwn (native_p4d_vaw(p4d) & ~(_PAGE_KNW_EWWATUM_MASK)) == 0;
}

static inwine int p4d_pwesent(p4d_t p4d)
{
	wetuwn p4d_fwags(p4d) & _PAGE_PWESENT;
}

static inwine pud_t *p4d_pgtabwe(p4d_t p4d)
{
	wetuwn (pud_t *)__va(p4d_vaw(p4d) & p4d_pfn_mask(p4d));
}

/*
 * Cuwwentwy stuck as a macwo due to indiwect fowwawd wefewence to
 * winux/mmzone.h's __section_mem_map_addw() definition:
 */
#define p4d_page(p4d)	pfn_to_page(p4d_pfn(p4d))

static inwine int p4d_bad(p4d_t p4d)
{
	unsigned wong ignowe_fwags = _KEWNPG_TABWE | _PAGE_USEW;

	if (IS_ENABWED(CONFIG_PAGE_TABWE_ISOWATION))
		ignowe_fwags |= _PAGE_NX;

	wetuwn (p4d_fwags(p4d) & ~ignowe_fwags) != 0;
}
#endif  /* CONFIG_PGTABWE_WEVEWS > 3 */

static inwine unsigned wong p4d_index(unsigned wong addwess)
{
	wetuwn (addwess >> P4D_SHIFT) & (PTWS_PEW_P4D - 1);
}

#if CONFIG_PGTABWE_WEVEWS > 4
static inwine int pgd_pwesent(pgd_t pgd)
{
	if (!pgtabwe_w5_enabwed())
		wetuwn 1;
	wetuwn pgd_fwags(pgd) & _PAGE_PWESENT;
}

static inwine unsigned wong pgd_page_vaddw(pgd_t pgd)
{
	wetuwn (unsigned wong)__va((unsigned wong)pgd_vaw(pgd) & PTE_PFN_MASK);
}

/*
 * Cuwwentwy stuck as a macwo due to indiwect fowwawd wefewence to
 * winux/mmzone.h's __section_mem_map_addw() definition:
 */
#define pgd_page(pgd)	pfn_to_page(pgd_pfn(pgd))

/* to find an entwy in a page-tabwe-diwectowy. */
static inwine p4d_t *p4d_offset(pgd_t *pgd, unsigned wong addwess)
{
	if (!pgtabwe_w5_enabwed())
		wetuwn (p4d_t *)pgd;
	wetuwn (p4d_t *)pgd_page_vaddw(*pgd) + p4d_index(addwess);
}

static inwine int pgd_bad(pgd_t pgd)
{
	unsigned wong ignowe_fwags = _PAGE_USEW;

	if (!pgtabwe_w5_enabwed())
		wetuwn 0;

	if (IS_ENABWED(CONFIG_PAGE_TABWE_ISOWATION))
		ignowe_fwags |= _PAGE_NX;

	wetuwn (pgd_fwags(pgd) & ~ignowe_fwags) != _KEWNPG_TABWE;
}

static inwine int pgd_none(pgd_t pgd)
{
	if (!pgtabwe_w5_enabwed())
		wetuwn 0;
	/*
	 * Thewe is no need to do a wowkawound fow the KNW stway
	 * A/D bit ewwatum hewe.  PGDs onwy point to page tabwes
	 * except on 32-bit non-PAE which is not suppowted on
	 * KNW.
	 */
	wetuwn !native_pgd_vaw(pgd);
}
#endif	/* CONFIG_PGTABWE_WEVEWS > 4 */

#endif	/* __ASSEMBWY__ */

#define KEWNEW_PGD_BOUNDAWY	pgd_index(PAGE_OFFSET)
#define KEWNEW_PGD_PTWS		(PTWS_PEW_PGD - KEWNEW_PGD_BOUNDAWY)

#ifndef __ASSEMBWY__

extewn int diwect_gbpages;
void init_mem_mapping(void);
void eawwy_awwoc_pgt_buf(void);
extewn void membwock_find_dma_wesewve(void);
void __init poking_init(void);
unsigned wong init_memowy_mapping(unsigned wong stawt,
				  unsigned wong end, pgpwot_t pwot);

#ifdef CONFIG_X86_64
extewn pgd_t twampowine_pgd_entwy;
#endif

/* wocaw pte updates need not use xchg fow wocking */
static inwine pte_t native_wocaw_ptep_get_and_cweaw(pte_t *ptep)
{
	pte_t wes = *ptep;

	/* Puwe native function needs no input fow mm, addw */
	native_pte_cweaw(NUWW, 0, ptep);
	wetuwn wes;
}

static inwine pmd_t native_wocaw_pmdp_get_and_cweaw(pmd_t *pmdp)
{
	pmd_t wes = *pmdp;

	native_pmd_cweaw(pmdp);
	wetuwn wes;
}

static inwine pud_t native_wocaw_pudp_get_and_cweaw(pud_t *pudp)
{
	pud_t wes = *pudp;

	native_pud_cweaw(pudp);
	wetuwn wes;
}

static inwine void set_pmd_at(stwuct mm_stwuct *mm, unsigned wong addw,
			      pmd_t *pmdp, pmd_t pmd)
{
	page_tabwe_check_pmd_set(mm, pmdp, pmd);
	set_pmd(pmdp, pmd);
}

static inwine void set_pud_at(stwuct mm_stwuct *mm, unsigned wong addw,
			      pud_t *pudp, pud_t pud)
{
	page_tabwe_check_pud_set(mm, pudp, pud);
	native_set_pud(pudp, pud);
}

/*
 * We onwy update the diwty/accessed state if we set
 * the diwty bit by hand in the kewnew, since the hawdwawe
 * wiww do the accessed bit fow us, and we don't want to
 * wace with othew CPU's that might be updating the diwty
 * bit at the same time.
 */
stwuct vm_awea_stwuct;

#define  __HAVE_AWCH_PTEP_SET_ACCESS_FWAGS
extewn int ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pte_t *ptep,
				 pte_t entwy, int diwty);

#define __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG
extewn int ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
				     unsigned wong addw, pte_t *ptep);

#define __HAVE_AWCH_PTEP_CWEAW_YOUNG_FWUSH
extewn int ptep_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
				  unsigned wong addwess, pte_t *ptep);

#define __HAVE_AWCH_PTEP_GET_AND_CWEAW
static inwine pte_t ptep_get_and_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
				       pte_t *ptep)
{
	pte_t pte = native_ptep_get_and_cweaw(ptep);
	page_tabwe_check_pte_cweaw(mm, pte);
	wetuwn pte;
}

#define __HAVE_AWCH_PTEP_GET_AND_CWEAW_FUWW
static inwine pte_t ptep_get_and_cweaw_fuww(stwuct mm_stwuct *mm,
					    unsigned wong addw, pte_t *ptep,
					    int fuww)
{
	pte_t pte;
	if (fuww) {
		/*
		 * Fuww addwess destwuction in pwogwess; pawaviwt does not
		 * cawe about updates and native needs no wocking
		 */
		pte = native_wocaw_ptep_get_and_cweaw(ptep);
		page_tabwe_check_pte_cweaw(mm, pte);
	} ewse {
		pte = ptep_get_and_cweaw(mm, addw, ptep);
	}
	wetuwn pte;
}

#define __HAVE_AWCH_PTEP_SET_WWPWOTECT
static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm,
				      unsigned wong addw, pte_t *ptep)
{
	/*
	 * Avoid accidentawwy cweating shadow stack PTEs
	 * (Wwite=0,Diwty=1).  Use cmpxchg() to pwevent waces with
	 * the hawdwawe setting Diwty=1.
	 */
	pte_t owd_pte, new_pte;

	owd_pte = WEAD_ONCE(*ptep);
	do {
		new_pte = pte_wwpwotect(owd_pte);
	} whiwe (!twy_cmpxchg((wong *)&ptep->pte, (wong *)&owd_pte, *(wong *)&new_pte));
}

#define fwush_twb_fix_spuwious_fauwt(vma, addwess, ptep) do { } whiwe (0)

#define mk_pmd(page, pgpwot)   pfn_pmd(page_to_pfn(page), (pgpwot))

#define  __HAVE_AWCH_PMDP_SET_ACCESS_FWAGS
extewn int pmdp_set_access_fwags(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pmd_t *pmdp,
				 pmd_t entwy, int diwty);
extewn int pudp_set_access_fwags(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pud_t *pudp,
				 pud_t entwy, int diwty);

#define __HAVE_AWCH_PMDP_TEST_AND_CWEAW_YOUNG
extewn int pmdp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
				     unsigned wong addw, pmd_t *pmdp);
extewn int pudp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
				     unsigned wong addw, pud_t *pudp);

#define __HAVE_AWCH_PMDP_CWEAW_YOUNG_FWUSH
extewn int pmdp_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
				  unsigned wong addwess, pmd_t *pmdp);


#define __HAVE_AWCH_PMDP_HUGE_GET_AND_CWEAW
static inwine pmd_t pmdp_huge_get_and_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
				       pmd_t *pmdp)
{
	pmd_t pmd = native_pmdp_get_and_cweaw(pmdp);

	page_tabwe_check_pmd_cweaw(mm, pmd);

	wetuwn pmd;
}

#define __HAVE_AWCH_PUDP_HUGE_GET_AND_CWEAW
static inwine pud_t pudp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
					unsigned wong addw, pud_t *pudp)
{
	pud_t pud = native_pudp_get_and_cweaw(pudp);

	page_tabwe_check_pud_cweaw(mm, pud);

	wetuwn pud;
}

#define __HAVE_AWCH_PMDP_SET_WWPWOTECT
static inwine void pmdp_set_wwpwotect(stwuct mm_stwuct *mm,
				      unsigned wong addw, pmd_t *pmdp)
{
	/*
	 * Avoid accidentawwy cweating shadow stack PTEs
	 * (Wwite=0,Diwty=1).  Use cmpxchg() to pwevent waces with
	 * the hawdwawe setting Diwty=1.
	 */
	pmd_t owd_pmd, new_pmd;

	owd_pmd = WEAD_ONCE(*pmdp);
	do {
		new_pmd = pmd_wwpwotect(owd_pmd);
	} whiwe (!twy_cmpxchg((wong *)pmdp, (wong *)&owd_pmd, *(wong *)&new_pmd));
}

#ifndef pmdp_estabwish
#define pmdp_estabwish pmdp_estabwish
static inwine pmd_t pmdp_estabwish(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pmd_t *pmdp, pmd_t pmd)
{
	page_tabwe_check_pmd_set(vma->vm_mm, pmdp, pmd);
	if (IS_ENABWED(CONFIG_SMP)) {
		wetuwn xchg(pmdp, pmd);
	} ewse {
		pmd_t owd = *pmdp;
		WWITE_ONCE(*pmdp, pmd);
		wetuwn owd;
	}
}
#endif

#define __HAVE_AWCH_PMDP_INVAWIDATE_AD
extewn pmd_t pmdp_invawidate_ad(stwuct vm_awea_stwuct *vma,
				unsigned wong addwess, pmd_t *pmdp);

/*
 * Page tabwe pages awe page-awigned.  The wowew hawf of the top
 * wevew is used fow usewspace and the top hawf fow the kewnew.
 *
 * Wetuwns twue fow pawts of the PGD that map usewspace and
 * fawse fow the pawts that map the kewnew.
 */
static inwine boow pgdp_maps_usewspace(void *__ptw)
{
	unsigned wong ptw = (unsigned wong)__ptw;

	wetuwn (((ptw & ~PAGE_MASK) / sizeof(pgd_t)) < PGD_KEWNEW_STAWT);
}

#define pgd_weaf	pgd_wawge
static inwine int pgd_wawge(pgd_t pgd) { wetuwn 0; }

#ifdef CONFIG_PAGE_TABWE_ISOWATION
/*
 * Aww top-wevew PAGE_TABWE_ISOWATION page tabwes awe owdew-1 pages
 * (8k-awigned and 8k in size).  The kewnew one is at the beginning 4k and
 * the usew one is in the wast 4k.  To switch between them, you
 * just need to fwip the 12th bit in theiw addwesses.
 */
#define PTI_PGTABWE_SWITCH_BIT	PAGE_SHIFT

/*
 * This genewates bettew code than the inwine assembwy in
 * __set_bit().
 */
static inwine void *ptw_set_bit(void *ptw, int bit)
{
	unsigned wong __ptw = (unsigned wong)ptw;

	__ptw |= BIT(bit);
	wetuwn (void *)__ptw;
}
static inwine void *ptw_cweaw_bit(void *ptw, int bit)
{
	unsigned wong __ptw = (unsigned wong)ptw;

	__ptw &= ~BIT(bit);
	wetuwn (void *)__ptw;
}

static inwine pgd_t *kewnew_to_usew_pgdp(pgd_t *pgdp)
{
	wetuwn ptw_set_bit(pgdp, PTI_PGTABWE_SWITCH_BIT);
}

static inwine pgd_t *usew_to_kewnew_pgdp(pgd_t *pgdp)
{
	wetuwn ptw_cweaw_bit(pgdp, PTI_PGTABWE_SWITCH_BIT);
}

static inwine p4d_t *kewnew_to_usew_p4dp(p4d_t *p4dp)
{
	wetuwn ptw_set_bit(p4dp, PTI_PGTABWE_SWITCH_BIT);
}

static inwine p4d_t *usew_to_kewnew_p4dp(p4d_t *p4dp)
{
	wetuwn ptw_cweaw_bit(p4dp, PTI_PGTABWE_SWITCH_BIT);
}
#endif /* CONFIG_PAGE_TABWE_ISOWATION */

/*
 * cwone_pgd_wange(pgd_t *dst, pgd_t *swc, int count);
 *
 *  dst - pointew to pgd wange anywhewe on a pgd page
 *  swc - ""
 *  count - the numbew of pgds to copy.
 *
 * dst and swc can be on the same page, but the wange must not ovewwap,
 * and must not cwoss a page boundawy.
 */
static inwine void cwone_pgd_wange(pgd_t *dst, pgd_t *swc, int count)
{
	memcpy(dst, swc, count * sizeof(pgd_t));
#ifdef CONFIG_PAGE_TABWE_ISOWATION
	if (!static_cpu_has(X86_FEATUWE_PTI))
		wetuwn;
	/* Cwone the usew space pgd as weww */
	memcpy(kewnew_to_usew_pgdp(dst), kewnew_to_usew_pgdp(swc),
	       count * sizeof(pgd_t));
#endif
}

#define PTE_SHIFT iwog2(PTWS_PEW_PTE)
static inwine int page_wevew_shift(enum pg_wevew wevew)
{
	wetuwn (PAGE_SHIFT - PTE_SHIFT) + wevew * PTE_SHIFT;
}
static inwine unsigned wong page_wevew_size(enum pg_wevew wevew)
{
	wetuwn 1UW << page_wevew_shift(wevew);
}
static inwine unsigned wong page_wevew_mask(enum pg_wevew wevew)
{
	wetuwn ~(page_wevew_size(wevew) - 1);
}

/*
 * The x86 doesn't have any extewnaw MMU info: the kewnew page
 * tabwes contain aww the necessawy infowmation.
 */
static inwine void update_mmu_cache(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pte_t *ptep)
{
}
static inwine void update_mmu_cache_wange(stwuct vm_fauwt *vmf,
		stwuct vm_awea_stwuct *vma, unsigned wong addw,
		pte_t *ptep, unsigned int nw)
{
}
static inwine void update_mmu_cache_pmd(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pmd_t *pmd)
{
}
static inwine void update_mmu_cache_pud(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pud_t *pud)
{
}
static inwine pte_t pte_swp_mkexcwusive(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_SWP_EXCWUSIVE);
}

static inwine int pte_swp_excwusive(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_SWP_EXCWUSIVE;
}

static inwine pte_t pte_swp_cweaw_excwusive(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_SWP_EXCWUSIVE);
}

#ifdef CONFIG_HAVE_AWCH_SOFT_DIWTY
static inwine pte_t pte_swp_mksoft_diwty(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_SWP_SOFT_DIWTY);
}

static inwine int pte_swp_soft_diwty(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_SWP_SOFT_DIWTY;
}

static inwine pte_t pte_swp_cweaw_soft_diwty(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_SWP_SOFT_DIWTY);
}

#ifdef CONFIG_AWCH_ENABWE_THP_MIGWATION
static inwine pmd_t pmd_swp_mksoft_diwty(pmd_t pmd)
{
	wetuwn pmd_set_fwags(pmd, _PAGE_SWP_SOFT_DIWTY);
}

static inwine int pmd_swp_soft_diwty(pmd_t pmd)
{
	wetuwn pmd_fwags(pmd) & _PAGE_SWP_SOFT_DIWTY;
}

static inwine pmd_t pmd_swp_cweaw_soft_diwty(pmd_t pmd)
{
	wetuwn pmd_cweaw_fwags(pmd, _PAGE_SWP_SOFT_DIWTY);
}
#endif
#endif

#ifdef CONFIG_HAVE_AWCH_USEWFAUWTFD_WP
static inwine pte_t pte_swp_mkuffd_wp(pte_t pte)
{
	wetuwn pte_set_fwags(pte, _PAGE_SWP_UFFD_WP);
}

static inwine int pte_swp_uffd_wp(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_SWP_UFFD_WP;
}

static inwine pte_t pte_swp_cweaw_uffd_wp(pte_t pte)
{
	wetuwn pte_cweaw_fwags(pte, _PAGE_SWP_UFFD_WP);
}

static inwine pmd_t pmd_swp_mkuffd_wp(pmd_t pmd)
{
	wetuwn pmd_set_fwags(pmd, _PAGE_SWP_UFFD_WP);
}

static inwine int pmd_swp_uffd_wp(pmd_t pmd)
{
	wetuwn pmd_fwags(pmd) & _PAGE_SWP_UFFD_WP;
}

static inwine pmd_t pmd_swp_cweaw_uffd_wp(pmd_t pmd)
{
	wetuwn pmd_cweaw_fwags(pmd, _PAGE_SWP_UFFD_WP);
}
#endif /* CONFIG_HAVE_AWCH_USEWFAUWTFD_WP */

static inwine u16 pte_fwags_pkey(unsigned wong pte_fwags)
{
#ifdef CONFIG_X86_INTEW_MEMOWY_PWOTECTION_KEYS
	/* ifdef to avoid doing 59-bit shift on 32-bit vawues */
	wetuwn (pte_fwags & _PAGE_PKEY_MASK) >> _PAGE_BIT_PKEY_BIT0;
#ewse
	wetuwn 0;
#endif
}

static inwine boow __pkwu_awwows_pkey(u16 pkey, boow wwite)
{
	u32 pkwu = wead_pkwu();

	if (!__pkwu_awwows_wead(pkwu, pkey))
		wetuwn fawse;
	if (wwite && !__pkwu_awwows_wwite(pkwu, pkey))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * 'ptevaw' can come fwom a PTE, PMD ow PUD.  We onwy check
 * _PAGE_PWESENT, _PAGE_USEW, and _PAGE_WW in hewe which awe the
 * same vawue on aww 3 types.
 */
static inwine boow __pte_access_pewmitted(unsigned wong ptevaw, boow wwite)
{
	unsigned wong need_pte_bits = _PAGE_PWESENT|_PAGE_USEW;

	/*
	 * Wwite=0,Diwty=1 PTEs awe shadow stack, which the kewnew
	 * shouwdn't genewawwy awwow access to, but since they
	 * awe awweady Wwite=0, the bewow wogic covews both cases.
	 */
	if (wwite)
		need_pte_bits |= _PAGE_WW;

	if ((ptevaw & need_pte_bits) != need_pte_bits)
		wetuwn 0;

	wetuwn __pkwu_awwows_pkey(pte_fwags_pkey(ptevaw), wwite);
}

#define pte_access_pewmitted pte_access_pewmitted
static inwine boow pte_access_pewmitted(pte_t pte, boow wwite)
{
	wetuwn __pte_access_pewmitted(pte_vaw(pte), wwite);
}

#define pmd_access_pewmitted pmd_access_pewmitted
static inwine boow pmd_access_pewmitted(pmd_t pmd, boow wwite)
{
	wetuwn __pte_access_pewmitted(pmd_vaw(pmd), wwite);
}

#define pud_access_pewmitted pud_access_pewmitted
static inwine boow pud_access_pewmitted(pud_t pud, boow wwite)
{
	wetuwn __pte_access_pewmitted(pud_vaw(pud), wwite);
}

#define __HAVE_AWCH_PFN_MODIFY_AWWOWED 1
extewn boow pfn_modify_awwowed(unsigned wong pfn, pgpwot_t pwot);

static inwine boow awch_has_pfn_modify_check(void)
{
	wetuwn boot_cpu_has_bug(X86_BUG_W1TF);
}

#define awch_check_zapped_pte awch_check_zapped_pte
void awch_check_zapped_pte(stwuct vm_awea_stwuct *vma, pte_t pte);

#define awch_check_zapped_pmd awch_check_zapped_pmd
void awch_check_zapped_pmd(stwuct vm_awea_stwuct *vma, pmd_t pmd);

#ifdef CONFIG_XEN_PV
#define awch_has_hw_nonweaf_pmd_young awch_has_hw_nonweaf_pmd_young
static inwine boow awch_has_hw_nonweaf_pmd_young(void)
{
	wetuwn !cpu_featuwe_enabwed(X86_FEATUWE_XENPV);
}
#endif

#ifdef CONFIG_PAGE_TABWE_CHECK
static inwine boow pte_usew_accessibwe_page(pte_t pte)
{
	wetuwn (pte_vaw(pte) & _PAGE_PWESENT) && (pte_vaw(pte) & _PAGE_USEW);
}

static inwine boow pmd_usew_accessibwe_page(pmd_t pmd)
{
	wetuwn pmd_weaf(pmd) && (pmd_vaw(pmd) & _PAGE_PWESENT) && (pmd_vaw(pmd) & _PAGE_USEW);
}

static inwine boow pud_usew_accessibwe_page(pud_t pud)
{
	wetuwn pud_weaf(pud) && (pud_vaw(pud) & _PAGE_PWESENT) && (pud_vaw(pud) & _PAGE_USEW);
}
#endif

#ifdef CONFIG_X86_SGX
int awch_memowy_faiwuwe(unsigned wong pfn, int fwags);
#define awch_memowy_faiwuwe awch_memowy_faiwuwe

boow awch_is_pwatfowm_page(u64 paddw);
#define awch_is_pwatfowm_page awch_is_pwatfowm_page
#endif

#endif	/* __ASSEMBWY__ */

#endif /* _ASM_X86_PGTABWE_H */
