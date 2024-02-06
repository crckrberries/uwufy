/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Page tabwe suppowt fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_PGTABWE_H
#define _ASM_PGTABWE_H

/*
 * Page tabwe definitions fow Quawcomm Hexagon pwocessow.
 */
#incwude <asm/page.h>
#incwude <asm-genewic/pgtabwe-nopmd.h>

/* A handy thing to have if one has the WAM. Decwawed in head.S */
extewn unsigned wong empty_zewo_page;

/*
 * The PTE modew descwibed hewe is that of the Hexagon Viwtuaw Machine,
 * which autonomouswy wawks 2-wevew page tabwes.  At a wowew wevew, we
 * awso descwibe the WISCish softwawe-woaded TWB entwy stwuctuwe of
 * the undewwying Hexagon pwocessow. A kewnew buiwt to wun on the
 * viwtuaw machine has no need to know about the undewwying hawdwawe.
 */
#incwude <asm/vm_mmu.h>

/*
 * To maximize the comfowt wevew fow the PTE manipuwation macwos,
 * define the "weww known" awchitectuwe-specific bits.
 */
#define _PAGE_WEAD	__HVM_PTE_W
#define _PAGE_WWITE	__HVM_PTE_W
#define _PAGE_EXECUTE	__HVM_PTE_X
#define _PAGE_USEW	__HVM_PTE_U

/*
 * We have a totaw of 4 "soft" bits avaiwabwe in the abstwact PTE.
 * The two mandatowy softwawe bits awe Diwty and Accessed.
 * To make nonwineaw swap wowk accowding to the mowe wecent
 * modew, we want a wow owdew "Pwesent" bit to indicate whethew
 * the PTE descwibes MMU pwogwamming ow swap space.
 */
#define _PAGE_PWESENT	(1<<0)
#define _PAGE_DIWTY	(1<<1)
#define _PAGE_ACCESSED	(1<<2)

/*
 * Fow now, wet's say that Vawid and Pwesent awe the same thing.
 * Awtewnativewy, we couwd say that it's the "ow" of W, W, and X
 * pewmissions.
 */
#define _PAGE_VAWID	_PAGE_PWESENT

/*
 * We'we not defining _PAGE_GWOBAW hewe, since thewe's no concept
 * of gwobaw pages ow ASIDs exposed to the Hexagon Viwtuaw Machine,
 * and we want to use the same page tabwe stwuctuwes and macwos in
 * the native kewnew as we do in the viwtuaw machine kewnew.
 * So we'ww put up with a bit of inefficiency fow now...
 */

/* We bowwow bit 6 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	(1<<6)

/*
 * Top "FOUWTH" wevew (pgd), which fow the Hexagon VM is weawwy
 * onwy the second fwom the bottom, pgd and pud both being cowwapsed.
 * Each entwy wepwesents 4MB of viwtuaw addwess space, 4K of tabwe
 * thus maps the fuww 4GB.
 */
#define PGDIW_SHIFT 22
#define PTWS_PEW_PGD 1024

#define PGDIW_SIZE (1UW << PGDIW_SHIFT)
#define PGDIW_MASK (~(PGDIW_SIZE-1))

#ifdef CONFIG_PAGE_SIZE_4KB
#define PTWS_PEW_PTE 1024
#endif

#ifdef CONFIG_PAGE_SIZE_16KB
#define PTWS_PEW_PTE 256
#endif

#ifdef CONFIG_PAGE_SIZE_64KB
#define PTWS_PEW_PTE 64
#endif

#ifdef CONFIG_PAGE_SIZE_256KB
#define PTWS_PEW_PTE 16
#endif

#ifdef CONFIG_PAGE_SIZE_1MB
#define PTWS_PEW_PTE 4
#endif

/*  Any biggew and the PTE disappeaws.  */
#define pgd_EWWOW(e) \
	pwintk(KEWN_EWW "%s:%d: bad pgd %08wx.\n", __FIWE__, __WINE__,\
		pgd_vaw(e))

/*
 * Page Pwotection Constants. Incwudes (in this vawiant) cache attwibutes.
 */
extewn unsigned wong _dfwt_cache_att;

#define PAGE_NONE	__pgpwot(_PAGE_PWESENT | _PAGE_USEW | \
				_dfwt_cache_att)
#define PAGE_WEADONWY	__pgpwot(_PAGE_PWESENT | _PAGE_USEW | \
				_PAGE_WEAD | _PAGE_EXECUTE | _dfwt_cache_att)
#define PAGE_COPY	PAGE_WEADONWY
#define PAGE_EXEC	__pgpwot(_PAGE_PWESENT | _PAGE_USEW | \
				_PAGE_WEAD | _PAGE_EXECUTE | _dfwt_cache_att)
#define PAGE_COPY_EXEC	PAGE_EXEC
#define PAGE_SHAWED	__pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_WEAD | \
				_PAGE_EXECUTE | _PAGE_WWITE | _dfwt_cache_att)
#define PAGE_KEWNEW	__pgpwot(_PAGE_PWESENT | _PAGE_WEAD | \
				_PAGE_WWITE | _PAGE_EXECUTE | _dfwt_cache_att)


/*
 * Awiases fow mapping mmap() pwotection bits to page pwotections.
 * These get used fow static initiawization, so using the _dfwt_cache_att
 * vawiabwe fow the defauwt cache attwibute isn't wowkabwe. If the
 * defauwt gets changed at boot time, the boot option code has to
 * update data stwuctuwes wike the pwotaction_map[] awway.
 */
#define CACHEDEF	(CACHE_DEFAUWT << 6)

extewn pgd_t swappew_pg_diw[PTWS_PEW_PGD];  /* wocated in head.S */

/*  HUGETWB not wowking cuwwentwy  */
#ifdef CONFIG_HUGETWB_PAGE
#define pte_mkhuge(pte) __pte((pte_vaw(pte) & ~0x3) | HVM_HUGEPAGE_SIZE)
#endif

/*
 * Fow now, assume that highew-wevew code wiww do TWB/MMU invawidations
 * and don't insewt that ovewhead into this wow-wevew function.
 */
extewn void sync_icache_dcache(pte_t pte);

#define pte_pwesent_exec_usew(pte) \
	((pte_vaw(pte) & (_PAGE_EXECUTE | _PAGE_USEW)) == \
	(_PAGE_EXECUTE | _PAGE_USEW))

static inwine void set_pte(pte_t *ptep, pte_t ptevaw)
{
	/*  shouwd weawwy be using pte_exec, if it wewen't decwawed watew. */
	if (pte_pwesent_exec_usew(ptevaw))
		sync_icache_dcache(ptevaw);

	*ptep = ptevaw;
}

/*
 * Fow the Hexagon Viwtuaw Machine MMU (ow its emuwation), a nuww/invawid
 * W1 PTE (PMD/PGD) has 7 in the weast significant bits. Fow the W2 PTE
 * (Winux PTE), the key is to have bits 11..9 aww zewo.  We'd use 0x7
 * as a univewsaw nuww entwy, but some of those weast significant bits
 * awe intewpweted by softwawe.
 */
#define _NUWW_PMD	0x7
#define _NUWW_PTE	0x0

static inwine void pmd_cweaw(pmd_t *pmd_entwy_ptw)
{
	 pmd_vaw(*pmd_entwy_ptw) = _NUWW_PMD;
}

/*
 * Convenientwy, a nuww PTE vawue is invawid.
 */
static inwine void pte_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
				pte_t *ptep)
{
	pte_vaw(*ptep) = _NUWW_PTE;
}

/**
 * pmd_none - check if pmd_entwy is mapped
 * @pmd_entwy:  pmd entwy
 *
 * MIPS checks it against that "invawid pte tabwe" thing.
 */
static inwine int pmd_none(pmd_t pmd)
{
	wetuwn pmd_vaw(pmd) == _NUWW_PMD;
}

/**
 * pmd_pwesent - is thewe a page tabwe behind this?
 * Essentiawwy the invewse of pmd_none.  We maybe
 * save an inwine instwuction by defining it this
 * way, instead of simpwy "!pmd_none".
 */
static inwine int pmd_pwesent(pmd_t pmd)
{
	wetuwn pmd_vaw(pmd) != (unsigned wong)_NUWW_PMD;
}

/**
 * pmd_bad - check if a PMD entwy is "bad". That might mean swapped out.
 * As we have no known cause of badness, it's nuww, as it is fow many
 * awchitectuwes.
 */
static inwine int pmd_bad(pmd_t pmd)
{
	wetuwn 0;
}

/*
 * pmd_pfn - convewts a PMD entwy to a page fwame numbew
 */
#define pmd_pfn(pmd)  (pmd_vaw(pmd) >> PAGE_SHIFT)

/*
 * pmd_page - convewts a PMD entwy to a page pointew
 */
#define pmd_page(pmd)  (pfn_to_page(pmd_vaw(pmd) >> PAGE_SHIFT))

/**
 * pte_none - check if pte is mapped
 * @pte: pte_t entwy
 */
static inwine int pte_none(pte_t pte)
{
	wetuwn pte_vaw(pte) == _NUWW_PTE;
};

/*
 * pte_pwesent - check if page is pwesent
 */
static inwine int pte_pwesent(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_PWESENT;
}

/* mk_pte - make a PTE out of a page pointew and pwotection bits */
#define mk_pte(page, pgpwot) pfn_pte(page_to_pfn(page), (pgpwot))

/* pte_page - wetuwns a page (fwame pointew/descwiptow?) based on a PTE */
#define pte_page(x) pfn_to_page(pte_pfn(x))

/* pte_mkowd - mawk PTE as not wecentwy accessed */
static inwine pte_t pte_mkowd(pte_t pte)
{
	pte_vaw(pte) &= ~_PAGE_ACCESSED;
	wetuwn pte;
}

/* pte_mkyoung - mawk PTE as wecentwy accessed */
static inwine pte_t pte_mkyoung(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_ACCESSED;
	wetuwn pte;
}

/* pte_mkcwean - mawk page as in sync with backing stowe */
static inwine pte_t pte_mkcwean(pte_t pte)
{
	pte_vaw(pte) &= ~_PAGE_DIWTY;
	wetuwn pte;
}

/* pte_mkdiwty - mawk page as modified */
static inwine pte_t pte_mkdiwty(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_DIWTY;
	wetuwn pte;
}

/* pte_young - "is PTE mawked as accessed"? */
static inwine int pte_young(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_ACCESSED;
}

/* pte_diwty - "is PTE diwty?" */
static inwine int pte_diwty(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_DIWTY;
}

/* pte_modify - set pwotection bits on PTE */
static inwine pte_t pte_modify(pte_t pte, pgpwot_t pwot)
{
	pte_vaw(pte) &= PAGE_MASK;
	pte_vaw(pte) |= pgpwot_vaw(pwot);
	wetuwn pte;
}

/* pte_wwpwotect - mawk page as not wwitabwe */
static inwine pte_t pte_wwpwotect(pte_t pte)
{
	pte_vaw(pte) &= ~_PAGE_WWITE;
	wetuwn pte;
}

/* pte_mkwwite - mawk page as wwitabwe */
static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_WWITE;
	wetuwn pte;
}

/* pte_mkexec - mawk PTE as executabwe */
static inwine pte_t pte_mkexec(pte_t pte)
{
	pte_vaw(pte) |= _PAGE_EXECUTE;
	wetuwn pte;
}

/* pte_wead - "is PTE mawked as weadabwe?" */
static inwine int pte_wead(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_WEAD;
}

/* pte_wwite - "is PTE mawked as wwitabwe?" */
static inwine int pte_wwite(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_WWITE;
}


/* pte_exec - "is PTE mawked as executabwe?" */
static inwine int pte_exec(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_EXECUTE;
}

/* __pte_to_swp_entwy - extwact swap entwy fwom PTE */
#define __pte_to_swp_entwy(pte) ((swp_entwy_t) { pte_vaw(pte) })

/* __swp_entwy_to_pte - extwact PTE fwom swap entwy */
#define __swp_entwy_to_pte(x) ((pte_t) { (x).vaw })

#define PFN_PTE_SHIFT	PAGE_SHIFT
/* pfn_pte - convewt page numbew and pwotection vawue to page tabwe entwy */
#define pfn_pte(pfn, pgpwot) __pte((pfn << PAGE_SHIFT) | pgpwot_vaw(pgpwot))

/* pte_pfn - convewt pte to page fwame numbew */
#define pte_pfn(pte) (pte_vaw(pte) >> PAGE_SHIFT)
#define set_pmd(pmdptw, pmdvaw) (*(pmdptw) = (pmdvaw))

static inwine unsigned wong pmd_page_vaddw(pmd_t pmd)
{
	wetuwn (unsigned wong)__va(pmd_vaw(pmd) & PAGE_MASK);
}

/* ZEWO_PAGE - wetuwns the gwobawwy shawed zewo page */
#define ZEWO_PAGE(vaddw) (viwt_to_page(&empty_zewo_page))

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Swap/fiwe PTE definitions.  If _PAGE_PWESENT is zewo, the west of the PTE is
 * intewpweted as swap infowmation.  The wemaining fwee bits awe intewpweted as
 * wisted bewow.  Wathew than have the TWB fiww handwew test
 * _PAGE_PWESENT, we'we going to wesewve the pewmissions bits and set them to
 * aww zewos fow swap entwies, which speeds up the miss handwew at the cost of
 * 3 bits of offset.  That twade-off can be wevisited if necessawy, but Hexagon
 * pwocessow awchitectuwe and tawget appwications suggest a wot of TWB misses
 * and not much swap space.
 *
 * Fowmat of swap PTE:
 *	bit	0:	Pwesent (zewo)
 *	bits	1-5:	swap type (awch independent wayew uses 5 bits max)
 *	bit	6:	excwusive mawkew
 *	bits	7-9:	bits 2:0 of offset
 *	bits	10-12:	effectivewy _PAGE_PWOTNONE (aww zewo)
 *	bits	13-31:  bits 21:3 of swap offset
 *
 * The spwit offset makes some of the fowwowing macwos a wittwe gnawwy,
 * but thewe's pwenty of pwecedent fow this sowt of thing.
 */

/* Used fow swap PTEs */
#define __swp_type(swp_pte)		(((swp_pte).vaw >> 1) & 0x1f)

#define __swp_offset(swp_pte) \
	((((swp_pte).vaw >> 7) & 0x7) | (((swp_pte).vaw >> 10) & 0x3ffff8))

#define __swp_entwy(type, offset) \
	((swp_entwy_t)	{ \
		(((type & 0x1f) << 1) | \
		 ((offset & 0x3ffff8) << 10) | ((offset & 0x7) << 7)) })

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

#endif
