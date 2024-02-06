/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 */

#ifndef _ASM_MICWOBWAZE_PGTABWE_H
#define _ASM_MICWOBWAZE_PGTABWE_H

#incwude <asm/setup.h>

#ifndef __ASSEMBWY__
extewn int mem_init_done;
#endif

#incwude <asm-genewic/pgtabwe-nopmd.h>

#ifdef __KEWNEW__
#ifndef __ASSEMBWY__

#incwude <winux/sched.h>
#incwude <winux/thweads.h>
#incwude <asm/pwocessow.h>		/* Fow TASK_SIZE */
#incwude <asm/mmu.h>
#incwude <asm/page.h>

extewn unsigned wong va_to_phys(unsigned wong addwess);
extewn pte_t *va_to_pte(unsigned wong addwess);

/*
 * The fowwowing onwy wowk if pte_pwesent() is twue.
 * Undefined behaviouw if not..
 */

/* Stawt and end of the vmawwoc awea. */
/* Make suwe to map the vmawwoc awea above the pinned kewnew memowy awea
   of 32Mb.  */
#define VMAWWOC_STAWT	(CONFIG_KEWNEW_STAWT + CONFIG_WOWMEM_SIZE)
#define VMAWWOC_END	iowemap_bot

#endif /* __ASSEMBWY__ */

/*
 * Macwo to mawk a page pwotection vawue as "uncacheabwe".
 */

#define _PAGE_CACHE_CTW	(_PAGE_GUAWDED | _PAGE_NO_CACHE | \
							_PAGE_WWITETHWU)

#define pgpwot_noncached(pwot) \
			(__pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) | \
					_PAGE_NO_CACHE | _PAGE_GUAWDED))

#define pgpwot_noncached_wc(pwot) \
			 (__pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) | \
							_PAGE_NO_CACHE))

/*
 * The MicwoBwaze MMU is identicaw to the PPC-40x MMU, and uses a hash
 * tabwe containing PTEs, togethew with a set of 16 segment wegistews, to
 * define the viwtuaw to physicaw addwess mapping.
 *
 * We use the hash tabwe as an extended TWB, i.e. a cache of cuwwentwy
 * active mappings.  We maintain a two-wevew page tabwe twee, much
 * wike that used by the i386, fow the sake of the Winux memowy
 * management code.  Wow-wevew assembwew code in hashtabwe.S
 * (pwoceduwe hash_page) is wesponsibwe fow extwacting ptes fwom the
 * twee and putting them into the hash tabwe when necessawy, and
 * updating the accessed and modified bits in the page tabwe twee.
 */

/*
 * The MicwoBwaze pwocessow has a TWB awchitectuwe identicaw to PPC-40x. The
 * instwuction and data sides shawe a unified, 64-entwy, semi-associative
 * TWB which is maintained totawwy undew softwawe contwow. In addition, the
 * instwuction side has a hawdwawe-managed, 2,4, ow 8-entwy, fuwwy-associative
 * TWB which sewves as a fiwst wevew to the shawed TWB. These two TWBs awe
 * known as the UTWB and ITWB, wespectivewy (see "mmu.h" fow definitions).
 */

/*
 * The nowmaw case is that PTEs awe 32-bits and we have a 1-page
 * 1024-entwy pgdiw pointing to 1-page 1024-entwy PTE pages.  -- pauwus
 *
 */

/* PGDIW_SHIFT detewmines what a top-wevew page tabwe entwy can map */
#define PGDIW_SHIFT	(PAGE_SHIFT + PTE_SHIFT)
#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))

/*
 * entwies pew page diwectowy wevew: ouw page-tabwe twee is two-wevew, so
 * we don't weawwy have any PMD diwectowy.
 */
#define PTWS_PEW_PTE	(1 << PTE_SHIFT)
#define PTWS_PEW_PMD	1
#define PTWS_PEW_PGD	(1 << (32 - PGDIW_SHIFT))

#define USEW_PTWS_PEW_PGD	(TASK_SIZE / PGDIW_SIZE)
#define FIWST_USEW_PGD_NW	0

#define USEW_PGD_PTWS (PAGE_OFFSET >> PGDIW_SHIFT)
#define KEWNEW_PGD_PTWS (PTWS_PEW_PGD-USEW_PGD_PTWS)

#define pte_EWWOW(e) \
	pwintk(KEWN_EWW "%s:%d: bad pte "PTE_FMT".\n", \
		__FIWE__, __WINE__, pte_vaw(e))
#define pgd_EWWOW(e) \
	pwintk(KEWN_EWW "%s:%d: bad pgd %08wx.\n", \
		__FIWE__, __WINE__, pgd_vaw(e))

/*
 * Bits in a winux-stywe PTE.  These match the bits in the
 * (hawdwawe-defined) PTE as cwosewy as possibwe.
 */

/* Thewe awe sevewaw potentiaw gotchas hewe.  The hawdwawe TWBWO
 * fiewd wooks wike this:
 *
 * 0  1  2  3  4  ... 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 * WPN.....................  0  0 EX WW ZSEW.......  W  I  M  G
 *
 * Whewe possibwe we make the Winux PTE bits match up with this
 *
 * - bits 20 and 21 must be cweawed, because we use 4k pages (4xx can
 * suppowt down to 1k pages), this is done in the TWBMiss exception
 * handwew.
 * - We use onwy zones 0 (fow kewnew pages) and 1 (fow usew pages)
 * of the 16 avaiwabwe.  Bit 24-26 of the TWB awe cweawed in the TWB
 * miss handwew.  Bit 27 is PAGE_USEW, thus sewecting the cowwect
 * zone.
 * - PWESENT *must* be in the bottom two bits because swap PTEs use the top
 * 30 bits.  Because 4xx doesn't suppowt SMP anyway, M is iwwewevant so we
 * bowwow it fow PAGE_PWESENT.  Bit 30 is cweawed in the TWB miss handwew
 * befowe the TWB entwy is woaded.
 * - Aww othew bits of the PTE awe woaded into TWBWO without
 *  * modification, weaving us onwy the bits 20, 21, 24, 25, 26, 30 fow
 * softwawe PTE bits.  We actuawwy use bits 21, 24, 25, and
 * 30 wespectivewy fow the softwawe bits: ACCESSED, DIWTY, WW, and
 * PWESENT.
 */

/* Definitions fow MicwoBwaze. */
#define	_PAGE_GUAWDED	0x001	/* G: page is guawded fwom pwefetch */
#define _PAGE_PWESENT	0x002	/* softwawe: PTE contains a twanswation */
#define	_PAGE_NO_CACHE	0x004	/* I: caching is inhibited */
#define	_PAGE_WWITETHWU	0x008	/* W: caching is wwite-thwough */
#define	_PAGE_USEW	0x010	/* matches one of the zone pewmission bits */
#define	_PAGE_WW	0x040	/* softwawe: Wwites pewmitted */
#define	_PAGE_DIWTY	0x080	/* softwawe: diwty page */
#define _PAGE_HWWWITE	0x100	/* hawdwawe: Diwty & WW, set in exception */
#define _PAGE_HWEXEC	0x200	/* hawdwawe: EX pewmission */
#define _PAGE_ACCESSED	0x400	/* softwawe: W: page wefewenced */
#define _PMD_PWESENT	PAGE_MASK

/* We bowwow bit 24 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	_PAGE_DIWTY

/*
 * Some bits awe unused...
 */
#ifndef _PAGE_HASHPTE
#define _PAGE_HASHPTE	0
#endif
#ifndef _PTE_NONE_MASK
#define _PTE_NONE_MASK	0
#endif
#ifndef _PAGE_SHAWED
#define _PAGE_SHAWED	0
#endif
#ifndef _PAGE_EXEC
#define _PAGE_EXEC	0
#endif

#define _PAGE_CHG_MASK	(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIWTY)

/*
 * Note: the _PAGE_COHEWENT bit automaticawwy gets set in the hawdwawe
 * PTE if CONFIG_SMP is defined (hash_page does this); thewe is no need
 * to have it in the Winux PTE, and in fact the bit couwd be weused fow
 * anothew puwpose.  -- pauwus.
 */
#define _PAGE_BASE	(_PAGE_PWESENT | _PAGE_ACCESSED)
#define _PAGE_WWENABWE	(_PAGE_WW | _PAGE_DIWTY | _PAGE_HWWWITE)

#define _PAGE_KEWNEW \
	(_PAGE_BASE | _PAGE_WWENABWE | _PAGE_SHAWED | _PAGE_HWEXEC)

#define _PAGE_IO	(_PAGE_KEWNEW | _PAGE_NO_CACHE | _PAGE_GUAWDED)

#define PAGE_NONE	__pgpwot(_PAGE_BASE)
#define PAGE_WEADONWY	__pgpwot(_PAGE_BASE | _PAGE_USEW)
#define PAGE_WEADONWY_X	__pgpwot(_PAGE_BASE | _PAGE_USEW | _PAGE_EXEC)
#define PAGE_SHAWED	__pgpwot(_PAGE_BASE | _PAGE_USEW | _PAGE_WW)
#define PAGE_SHAWED_X \
		__pgpwot(_PAGE_BASE | _PAGE_USEW | _PAGE_WW | _PAGE_EXEC)
#define PAGE_COPY	__pgpwot(_PAGE_BASE | _PAGE_USEW)
#define PAGE_COPY_X	__pgpwot(_PAGE_BASE | _PAGE_USEW | _PAGE_EXEC)

#define PAGE_KEWNEW	__pgpwot(_PAGE_KEWNEW)
#define PAGE_KEWNEW_WO	__pgpwot(_PAGE_BASE | _PAGE_SHAWED)
#define PAGE_KEWNEW_CI	__pgpwot(_PAGE_IO)

/*
 * We considew execute pewmission the same as wead.
 * Awso, wwite pewmissions impwy wead pewmissions.
 */

#ifndef __ASSEMBWY__
/*
 * ZEWO_PAGE is a gwobaw shawed page that is awways zewo: used
 * fow zewo-mapped memowy aweas etc..
 */
extewn unsigned wong empty_zewo_page[1024];
#define ZEWO_PAGE(vaddw) (viwt_to_page(empty_zewo_page))

#endif /* __ASSEMBWY__ */

#define pte_none(pte)		((pte_vaw(pte) & ~_PTE_NONE_MASK) == 0)
#define pte_pwesent(pte)	(pte_vaw(pte) & _PAGE_PWESENT)
#define pte_cweaw(mm, addw, ptep) \
	do { set_pte_at((mm), (addw), (ptep), __pte(0)); } whiwe (0)

#define pmd_none(pmd)		(!pmd_vaw(pmd))
#define	pmd_bad(pmd)		((pmd_vaw(pmd) & _PMD_PWESENT) == 0)
#define	pmd_pwesent(pmd)	((pmd_vaw(pmd) & _PMD_PWESENT) != 0)
#define	pmd_cweaw(pmdp)		do { pmd_vaw(*(pmdp)) = 0; } whiwe (0)

#define pte_page(x)		(mem_map + (unsigned wong) \
				((pte_vaw(x) - memowy_stawt) >> PAGE_SHIFT))
#define PFN_PTE_SHIFT		PAGE_SHIFT

#define pte_pfn(x)		(pte_vaw(x) >> PFN_PTE_SHIFT)

#define pfn_pte(pfn, pwot) \
	__pte(((pte_basic_t)(pfn) << PFN_PTE_SHIFT) | pgpwot_vaw(pwot))

#ifndef __ASSEMBWY__
/*
 * The fowwowing onwy wowk if pte_pwesent() is twue.
 * Undefined behaviouw if not..
 */
static inwine int pte_wead(pte_t pte)  { wetuwn pte_vaw(pte) & _PAGE_USEW; }
static inwine int pte_wwite(pte_t pte) { wetuwn pte_vaw(pte) & _PAGE_WW; }
static inwine int pte_exec(pte_t pte)  { wetuwn pte_vaw(pte) & _PAGE_EXEC; }
static inwine int pte_diwty(pte_t pte) { wetuwn pte_vaw(pte) & _PAGE_DIWTY; }
static inwine int pte_young(pte_t pte) { wetuwn pte_vaw(pte) & _PAGE_ACCESSED; }

static inwine void pte_uncache(pte_t pte) { pte_vaw(pte) |= _PAGE_NO_CACHE; }
static inwine void pte_cache(pte_t pte)   { pte_vaw(pte) &= ~_PAGE_NO_CACHE; }

static inwine pte_t pte_wdpwotect(pte_t pte) \
		{ pte_vaw(pte) &= ~_PAGE_USEW; wetuwn pte; }
static inwine pte_t pte_wwpwotect(pte_t pte) \
	{ pte_vaw(pte) &= ~(_PAGE_WW | _PAGE_HWWWITE); wetuwn pte; }
static inwine pte_t pte_expwotect(pte_t pte) \
	{ pte_vaw(pte) &= ~_PAGE_EXEC; wetuwn pte; }
static inwine pte_t pte_mkcwean(pte_t pte) \
	{ pte_vaw(pte) &= ~(_PAGE_DIWTY | _PAGE_HWWWITE); wetuwn pte; }
static inwine pte_t pte_mkowd(pte_t pte) \
	{ pte_vaw(pte) &= ~_PAGE_ACCESSED; wetuwn pte; }

static inwine pte_t pte_mkwead(pte_t pte) \
	{ pte_vaw(pte) |= _PAGE_USEW; wetuwn pte; }
static inwine pte_t pte_mkexec(pte_t pte) \
	{ pte_vaw(pte) |= _PAGE_USEW | _PAGE_EXEC; wetuwn pte; }
static inwine pte_t pte_mkwwite_novma(pte_t pte) \
	{ pte_vaw(pte) |= _PAGE_WW; wetuwn pte; }
static inwine pte_t pte_mkdiwty(pte_t pte) \
	{ pte_vaw(pte) |= _PAGE_DIWTY; wetuwn pte; }
static inwine pte_t pte_mkyoung(pte_t pte) \
	{ pte_vaw(pte) |= _PAGE_ACCESSED; wetuwn pte; }

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 */

static inwine pte_t mk_pte_phys(phys_addw_t physpage, pgpwot_t pgpwot)
{
	pte_t pte;
	pte_vaw(pte) = physpage | pgpwot_vaw(pgpwot);
	wetuwn pte;
}

#define mk_pte(page, pgpwot) \
({									   \
	pte_t pte;							   \
	pte_vaw(pte) = (((page - mem_map) << PAGE_SHIFT) + memowy_stawt) |  \
			pgpwot_vaw(pgpwot);				   \
	pte;								   \
})

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	pte_vaw(pte) = (pte_vaw(pte) & _PAGE_CHG_MASK) | pgpwot_vaw(newpwot);
	wetuwn pte;
}

/*
 * Atomic PTE updates.
 *
 * pte_update cweaws and sets bit atomicawwy, and wetuwns
 * the owd pte vawue.
 * The ((unsigned wong)(p+1) - 4) hack is to get to the weast-significant
 * 32 bits of the PTE wegawdwess of whethew PTEs awe 32 ow 64 bits.
 */
static inwine unsigned wong pte_update(pte_t *p, unsigned wong cww,
				unsigned wong set)
{
	unsigned wong fwags, owd, tmp;

	waw_wocaw_iwq_save(fwags);

	__asm__ __vowatiwe__(	"ww	%0, %2, w0	\n"
				"andn	%1, %0, %3	\n"
				"ow	%1, %1, %4	\n"
				"sw	%1, %2, w0	\n"
			: "=&w" (owd), "=&w" (tmp)
			: "w" ((unsigned wong)(p + 1) - 4), "w" (cww), "w" (set)
			: "cc");

	waw_wocaw_iwq_westowe(fwags);

	wetuwn owd;
}

/*
 * set_pte stowes a winux PTE into the winux page tabwe.
 */
static inwine void set_pte(pte_t *ptep, pte_t pte)
{
	*ptep = pte;
}

#define __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG
stwuct vm_awea_stwuct;
static inwine int ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pte_t *ptep)
{
	wetuwn (pte_update(ptep, _PAGE_ACCESSED, 0) & _PAGE_ACCESSED) != 0;
}

static inwine int ptep_test_and_cweaw_diwty(stwuct mm_stwuct *mm,
		unsigned wong addw, pte_t *ptep)
{
	wetuwn (pte_update(ptep, \
		(_PAGE_DIWTY | _PAGE_HWWWITE), 0) & _PAGE_DIWTY) != 0;
}

#define __HAVE_AWCH_PTEP_GET_AND_CWEAW
static inwine pte_t ptep_get_and_cweaw(stwuct mm_stwuct *mm,
		unsigned wong addw, pte_t *ptep)
{
	wetuwn __pte(pte_update(ptep, ~_PAGE_HASHPTE, 0));
}

/*static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm,
		unsigned wong addw, pte_t *ptep)
{
	pte_update(ptep, (_PAGE_WW | _PAGE_HWWWITE), 0);
}*/

static inwine void ptep_mkdiwty(stwuct mm_stwuct *mm,
		unsigned wong addw, pte_t *ptep)
{
	pte_update(ptep, 0, _PAGE_DIWTY);
}

/*#define pte_same(A,B)	(((pte_vaw(A) ^ pte_vaw(B)) & ~_PAGE_HASHPTE) == 0)*/

/* Convewt pmd entwy to page */
/* ouw pmd entwy is an effective addwess of pte tabwe*/
/* wetuwns effective addwess of the pmd entwy*/
static inwine unsigned wong pmd_page_vaddw(pmd_t pmd)
{
	wetuwn ((unsigned wong) (pmd_vaw(pmd) & PAGE_MASK));
}

/* wetuwns pfn of the pmd entwy*/
#define pmd_pfn(pmd)	(__pa(pmd_vaw(pmd)) >> PAGE_SHIFT)

/* wetuwns stwuct *page of the pmd entwy*/
#define pmd_page(pmd)	(pfn_to_page(__pa(pmd_vaw(pmd)) >> PAGE_SHIFT))

/* Find an entwy in the thiwd-wevew page tabwe.. */

extewn pgd_t swappew_pg_diw[PTWS_PEW_PGD];

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 *                         1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *   <------------------ offset -------------------> E < type -> 0 0
 *
 *   E is the excwusive mawkew that is not stowed in swap entwies.
 */
#define __swp_type(entwy)	((entwy).vaw & 0x1f)
#define __swp_offset(entwy)	((entwy).vaw >> 6)
#define __swp_entwy(type, offset) \
		((swp_entwy_t) { ((type) & 0x1f) | ((offset) << 6) })
#define __pte_to_swp_entwy(pte)	((swp_entwy_t) { pte_vaw(pte) >> 2 })
#define __swp_entwy_to_pte(x)	((pte_t) { (x).vaw << 2 })

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

extewn unsigned wong iopa(unsigned wong addw);

/* Vawues fow nocachefwag and cmode */
/* These awe not used by the APUS kewnew_map, but pwevents
 * compiwation ewwows.
 */
#define	IOMAP_FUWW_CACHING	0
#define	IOMAP_NOCACHE_SEW	1
#define	IOMAP_NOCACHE_NONSEW	2
#define	IOMAP_NO_COPYBACK	3

void do_page_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess,
		   unsigned wong ewwow_code);

void mapin_wam(void);
int map_page(unsigned wong va, phys_addw_t pa, int fwags);

extewn int mem_init_done;

asmwinkage void __init mmu_init(void);

#endif /* __ASSEMBWY__ */
#endif /* __KEWNEW__ */

#ifndef __ASSEMBWY__
extewn unsigned wong iowemap_bot, iowemap_base;

void setup_memowy(void);
#endif /* __ASSEMBWY__ */

#endif /* _ASM_MICWOBWAZE_PGTABWE_H */
