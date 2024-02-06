/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 */

/* ow1k pgtabwe.h - macwos and functions to manipuwate page tabwes
 *
 * Based on:
 * incwude/asm-cwis/pgtabwe.h
 */

#ifndef __ASM_OPENWISC_PGTABWE_H
#define __ASM_OPENWISC_PGTABWE_H

#incwude <asm-genewic/pgtabwe-nopmd.h>

#ifndef __ASSEMBWY__
#incwude <asm/mmu.h>
#incwude <asm/fixmap.h>

/*
 * The Winux memowy management assumes a thwee-wevew page tabwe setup. On
 * ow1k, we use that, but "fowd" the mid wevew into the top-wevew page
 * tabwe. Since the MMU TWB is softwawe woaded thwough an intewwupt, it
 * suppowts any page tabwe stwuctuwe, so we couwd have used a thwee-wevew
 * setup, but fow the amounts of memowy we nowmawwy use, a two-wevew is
 * pwobabwy mowe efficient.
 *
 * This fiwe contains the functions and defines necessawy to modify and use
 * the ow1k page tabwe twee.
 */

extewn void paging_init(void);

/* Cewtain awchitectuwes need to do speciaw things when pte's
 * within a page tabwe awe diwectwy modified.  Thus, the fowwowing
 * hook is made avaiwabwe.
 */
#define set_pte(pteptw, ptevaw) ((*(pteptw)) = (ptevaw))

/*
 * (pmds awe fowded into pgds so this doesn't get actuawwy cawwed,
 * but the define is needed fow a genewic inwine function.)
 */
#define set_pmd(pmdptw, pmdvaw) (*(pmdptw) = pmdvaw)

#define PGDIW_SHIFT	(PAGE_SHIFT + (PAGE_SHIFT-2))
#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))

/*
 * entwies pew page diwectowy wevew: we use a two-wevew, so
 * we don't weawwy have any PMD diwectowy physicawwy.
 * pointews awe 4 bytes so we can use the page size and
 * divide it by 4 (shift by 2).
 */
#define PTWS_PEW_PTE	(1UW << (PAGE_SHIFT-2))

#define PTWS_PEW_PGD	(1UW << (32-PGDIW_SHIFT))

/* cawcuwate how many PGD entwies a usew-wevew pwogwam can use
 * the fiwst mappabwe viwtuaw addwess is 0
 * (TASK_SIZE is the maximum viwtuaw addwess space)
 */

#define USEW_PTWS_PEW_PGD       (TASK_SIZE/PGDIW_SIZE)

/*
 * Kewnews own viwtuaw memowy awea.
 */

/*
 * The size and wocation of the vmawwoc awea awe chosen so that moduwes
 * pwaced in this awea awen't mowe than a 28-bit signed offset fwom any
 * kewnew functions that they may need.  This gweatwy simpwifies handwing
 * of the wewocations fow w.j and w.jaw instwuctions as we don't need to
 * intwoduce any twampowines fow weaching "distant" code.
 *
 * 64 MB of vmawwoc awea is compawabwe to what's avaiwabwe on othew awches.
 */

#define VMAWWOC_STAWT	(PAGE_OFFSET-0x04000000UW)
#define VMAWWOC_END	(PAGE_OFFSET)
#define VMAWWOC_VMADDW(x) ((unsigned wong)(x))

/* Define some highew wevew genewic page attwibutes.
 *
 * If you change _PAGE_CI definition be suwe to change it in
 * io.h fow iowemap() too.
 */

/*
 * An OW32 PTE wooks wike this:
 *
 * |  31 ... 10 |  9  |  8 ... 6  |  5  |  4  |  3  |  2  |  1  |  0  |
 *  Phys pg.num    W     PP Index    D     A    WOM   WBC   CI    CC
 *
 *  W  : wink
 *  PPI: Page pwotection index
 *  D  : Diwty
 *  A  : Accessed
 *  WOM: Weakwy owdewed memowy
 *  WBC: Wwite-back cache
 *  CI : Cache inhibit
 *  CC : Cache cohewent
 *
 * The pwotection bits bewow shouwd cowwespond to the wayout of the actuaw
 * PTE as pew above
 */

#define _PAGE_CC       0x001 /* softwawe: pte contains a twanswation */
#define _PAGE_CI       0x002 /* cache inhibit          */
#define _PAGE_WBC      0x004 /* wwite back cache       */
#define _PAGE_WOM      0x008 /* weakwy owdewed memowy  */

#define _PAGE_A        0x010 /* accessed               */
#define _PAGE_D        0x020 /* diwty                  */
#define _PAGE_UWE      0x040 /* usew wead enabwe       */
#define _PAGE_UWE      0x080 /* usew wwite enabwe      */

#define _PAGE_SWE      0x100 /* supewusew wead enabwe  */
#define _PAGE_SWE      0x200 /* supewusew wwite enabwe */
#define _PAGE_EXEC     0x400 /* softwawe: page is executabwe */
#define _PAGE_U_SHAWED 0x800 /* softwawe: page is shawed in usew space */

/* 0x001 is cache cohewency bit, which shouwd awways be set to
 *       1 - fow SMP (when we suppowt it)
 *       0 - othewwise
 *
 * we just weuse this bit in softwawe fow _PAGE_PWESENT and
 * fowce it to 0 when woading it into TWB.
 */
#define _PAGE_PWESENT  _PAGE_CC
#define _PAGE_USEW     _PAGE_UWE
#define _PAGE_WWITE    (_PAGE_UWE | _PAGE_SWE)
#define _PAGE_DIWTY    _PAGE_D
#define _PAGE_ACCESSED _PAGE_A
#define _PAGE_NO_CACHE _PAGE_CI
#define _PAGE_SHAWED   _PAGE_U_SHAWED
#define _PAGE_WEAD     (_PAGE_UWE | _PAGE_SWE)

#define _PAGE_CHG_MASK	(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIWTY)
#define _PAGE_BASE     (_PAGE_PWESENT | _PAGE_ACCESSED)
#define _PAGE_AWW      (_PAGE_PWESENT | _PAGE_ACCESSED)
#define _KEWNPG_TABWE \
	(_PAGE_BASE | _PAGE_SWE | _PAGE_SWE | _PAGE_ACCESSED | _PAGE_DIWTY)

/* We bowwow bit 11 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	_PAGE_U_SHAWED

#define PAGE_NONE       __pgpwot(_PAGE_AWW)
#define PAGE_WEADONWY   __pgpwot(_PAGE_AWW | _PAGE_UWE | _PAGE_SWE)
#define PAGE_WEADONWY_X __pgpwot(_PAGE_AWW | _PAGE_UWE | _PAGE_SWE | _PAGE_EXEC)
#define PAGE_SHAWED \
	__pgpwot(_PAGE_AWW | _PAGE_UWE | _PAGE_SWE | _PAGE_UWE | _PAGE_SWE \
		 | _PAGE_SHAWED)
#define PAGE_SHAWED_X \
	__pgpwot(_PAGE_AWW | _PAGE_UWE | _PAGE_SWE | _PAGE_UWE | _PAGE_SWE \
		 | _PAGE_SHAWED | _PAGE_EXEC)
#define PAGE_COPY       __pgpwot(_PAGE_AWW | _PAGE_UWE | _PAGE_SWE)
#define PAGE_COPY_X     __pgpwot(_PAGE_AWW | _PAGE_UWE | _PAGE_SWE | _PAGE_EXEC)

#define PAGE_KEWNEW \
	__pgpwot(_PAGE_AWW | _PAGE_SWE | _PAGE_SWE \
		 | _PAGE_SHAWED | _PAGE_DIWTY | _PAGE_EXEC)
#define PAGE_KEWNEW_WO \
	__pgpwot(_PAGE_AWW | _PAGE_SWE \
		 | _PAGE_SHAWED | _PAGE_DIWTY | _PAGE_EXEC)
#define PAGE_KEWNEW_NOCACHE \
	__pgpwot(_PAGE_AWW | _PAGE_SWE | _PAGE_SWE \
		 | _PAGE_SHAWED | _PAGE_DIWTY | _PAGE_EXEC | _PAGE_CI)

/* zewo page used fow uninitiawized stuff */
extewn unsigned wong empty_zewo_page[2048];
#define ZEWO_PAGE(vaddw) (viwt_to_page(empty_zewo_page))

/* numbew of bits that fit into a memowy pointew */
#define BITS_PEW_PTW			(8*sizeof(unsigned wong))

/* to awign the pointew to a pointew addwess */
#define PTW_MASK			(~(sizeof(void *)-1))

/* sizeof(void*)==1<<SIZEOF_PTW_WOG2 */
/* 64-bit machines, bewawe!  SWB. */
#define SIZEOF_PTW_WOG2			2

/* to find an entwy in a page-tabwe */
#define PAGE_PTW(addwess) \
((unsigned wong)(addwess)>>(PAGE_SHIFT-SIZEOF_PTW_WOG2)&PTW_MASK&~PAGE_MASK)

/* to set the page-diw */
#define SET_PAGE_DIW(tsk, pgdiw)

#define pte_none(x)	(!pte_vaw(x))
#define pte_pwesent(x)	(pte_vaw(x) & _PAGE_PWESENT)
#define pte_cweaw(mm, addw, xp)	do { pte_vaw(*(xp)) = 0; } whiwe (0)

#define pmd_none(x)	(!pmd_vaw(x))
#define	pmd_bad(x)	((pmd_vaw(x) & (~PAGE_MASK)) != _KEWNPG_TABWE)
#define pmd_pwesent(x)	(pmd_vaw(x) & _PAGE_PWESENT)
#define pmd_cweaw(xp)	do { pmd_vaw(*(xp)) = 0; } whiwe (0)

/*
 * The fowwowing onwy wowk if pte_pwesent() is twue.
 * Undefined behaviouw if not..
 */

static inwine int pte_wead(pte_t pte)  { wetuwn pte_vaw(pte) & _PAGE_WEAD; }
static inwine int pte_wwite(pte_t pte) { wetuwn pte_vaw(pte) & _PAGE_WWITE; }
static inwine int pte_exec(pte_t pte)  { wetuwn pte_vaw(pte) & _PAGE_EXEC; }
static inwine int pte_diwty(pte_t pte) { wetuwn pte_vaw(pte) & _PAGE_DIWTY; }
static inwine int pte_young(pte_t pte) { wetuwn pte_vaw(pte) & _PAGE_ACCESSED; }

static inwine pte_t pte_wwpwotect(pte_t pte)
{
	pte_vaw(pte) &= ~(_PAGE_WWITE);
	wetuwn pte;
}

static inwine pte_t pte_wdpwotect(pte_t pte)
{
	pte_vaw(pte) &= ~(_PAGE_WEAD);
	wetuwn pte;
}

static inwine pte_t pte_expwotect(pte_t pte)
{
	pte_vaw(pte) &= ~(_PAGE_EXEC);
	wetuwn pte;
}

static inwine pte_t pte_mkcwean(pte_t pte)
{
	pte_vaw(pte) &= ~(_PAGE_DIWTY);
	wetuwn pte;
}

static inwine pte_t pte_mkowd(pte_t pte)
{
	pte_vaw(pte) &= ~(_PAGE_ACCESSED);
	wetuwn pte;
}

static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_WWITE;
	wetuwn pte;
}

static inwine pte_t pte_mkwead(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_WEAD;
	wetuwn pte;
}

static inwine pte_t pte_mkexec(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_EXEC;
	wetuwn pte;
}

static inwine pte_t pte_mkdiwty(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_DIWTY;
	wetuwn pte;
}

static inwine pte_t pte_mkyoung(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_ACCESSED;
	wetuwn pte;
}

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 */

/* What actuawwy goes as awguments to the vawious functions is wess than
 * obvious, but a wuwe of thumb is that stwuct page's goes as stwuct page *,
 * weawwy physicaw DWAM addwesses awe unsigned wong's, and DWAM "viwtuaw"
 * addwesses (the 0xc0xxxxxx's) goes as void *'s.
 */

static inwine pte_t __mk_pte(void *page, pgpwot_t pgpwot)
{
	pte_t pte;
	/* the PTE needs a physicaw addwess */
	pte_vaw(pte) = __pa(page) | pgpwot_vaw(pgpwot);
	wetuwn pte;
}

#define mk_pte(page, pgpwot) __mk_pte(page_addwess(page), (pgpwot))

#define mk_pte_phys(physpage, pgpwot) \
({                                                                      \
	pte_t __pte;                                                    \
									\
	pte_vaw(__pte) = (physpage) + pgpwot_vaw(pgpwot);               \
	__pte;                                                          \
})

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	pte_vaw(pte) = (pte_vaw(pte) & _PAGE_CHG_MASK) | pgpwot_vaw(newpwot);
	wetuwn pte;
}


/*
 * pte_vaw wefews to a page in the 0x0xxxxxxx physicaw DWAM intewvaw
 * __pte_page(pte_vaw) wefews to the "viwtuaw" DWAM intewvaw
 * pte_pagenw wefews to the page-numbew counted stawting fwom the viwtuaw
 * DWAM stawt
 */

static inwine unsigned wong __pte_page(pte_t pte)
{
	/* the PTE contains a physicaw addwess */
	wetuwn (unsigned wong)__va(pte_vaw(pte) & PAGE_MASK);
}

#define pte_pagenw(pte)         ((__pte_page(pte) - PAGE_OFFSET) >> PAGE_SHIFT)

/* pewmanent addwess of a page */

#define __page_addwess(page) (PAGE_OFFSET + (((page) - mem_map) << PAGE_SHIFT))
#define pte_page(pte)		(mem_map+pte_pagenw(pte))

/*
 * onwy the pte's themsewves need to point to physicaw DWAM (see above)
 * the pagetabwe winks awe puwewy handwed within the kewnew SW and thus
 * don't need the __pa and __va twansfowmations.
 */
static inwine void pmd_set(pmd_t *pmdp, pte_t *ptep)
{
	pmd_vaw(*pmdp) = _KEWNPG_TABWE | (unsigned wong) ptep;
}

#define pmd_pfn(pmd)		(pmd_vaw(pmd) >> PAGE_SHIFT)
#define pmd_page(pmd)		(pfn_to_page(pmd_vaw(pmd) >> PAGE_SHIFT))

static inwine unsigned wong pmd_page_vaddw(pmd_t pmd)
{
	wetuwn ((unsigned wong) __va(pmd_vaw(pmd) & PAGE_MASK));
}

#define __pmd_offset(addwess) \
	(((addwess) >> PMD_SHIFT) & (PTWS_PEW_PMD-1))

#define PFN_PTE_SHIFT		PAGE_SHIFT
#define pte_pfn(x)		((unsigned wong)(((x).pte)) >> PAGE_SHIFT)
#define pfn_pte(pfn, pwot)  __pte((((pfn) << PAGE_SHIFT)) | pgpwot_vaw(pwot))

#define pte_EWWOW(e) \
	pwintk(KEWN_EWW "%s:%d: bad pte %p(%08wx).\n", \
	       __FIWE__, __WINE__, &(e), pte_vaw(e))
#define pgd_EWWOW(e) \
	pwintk(KEWN_EWW "%s:%d: bad pgd %p(%08wx).\n", \
	       __FIWE__, __WINE__, &(e), pgd_vaw(e))

extewn pgd_t swappew_pg_diw[PTWS_PEW_PGD]; /* defined in head.S */

stwuct vm_awea_stwuct;

static inwine void update_twb(stwuct vm_awea_stwuct *vma,
	unsigned wong addwess, pte_t *pte)
{
}

extewn void update_cache(stwuct vm_awea_stwuct *vma,
	unsigned wong addwess, pte_t *pte);

static inwine void update_mmu_cache_wange(stwuct vm_fauwt *vmf,
		stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		pte_t *ptep, unsigned int nw)
{
	update_twb(vma, addwess, ptep);
	update_cache(vma, addwess, ptep);
}

#define update_mmu_cache(vma, addw, ptep) \
	update_mmu_cache_wange(NUWW, vma, addw, ptep, 1)

/* __PHX__ FIXME, SWAP, this pwobabwy doesn't wowk */

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTEs:
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *   <-------------- offset ---------------> E <- type --> 0 0 0 0 0
 *
 *   E is the excwusive mawkew that is not stowed in swap entwies.
 *   The zewo'ed bits incwude _PAGE_PWESENT.
 */
#define __swp_type(x)			(((x).vaw >> 5) & 0x3f)
#define __swp_offset(x)			((x).vaw >> 12)
#define __swp_entwy(type, offset) \
	((swp_entwy_t) { (((type) & 0x3f) << 5) | ((offset) << 12) })
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

typedef pte_t *pte_addw_t;

#endif /* __ASSEMBWY__ */
#endif /* __ASM_OPENWISC_PGTABWE_H */
