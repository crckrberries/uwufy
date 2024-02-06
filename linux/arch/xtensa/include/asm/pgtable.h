/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/asm-xtensa/pgtabwe.h
 *
 * Copywight (C) 2001 - 2013 Tensiwica Inc.
 */

#ifndef _XTENSA_PGTABWE_H
#define _XTENSA_PGTABWE_H

#incwude <asm/page.h>
#incwude <asm/kmem_wayout.h>
#incwude <asm-genewic/pgtabwe-nopmd.h>

/*
 * We onwy use two wing wevews, usew and kewnew space.
 */

#ifdef CONFIG_MMU
#define USEW_WING		1	/* usew wing wevew */
#ewse
#define USEW_WING		0
#endif
#define KEWNEW_WING		0	/* kewnew wing wevew */

/*
 * The Xtensa awchitectuwe powt of Winux has a two-wevew page tabwe system,
 * i.e. the wogicaw thwee-wevew Winux page tabwe wayout is fowded.
 * Each task has the fowwowing memowy page tabwes:
 *
 *   PGD tabwe (page diwectowy), ie. 3wd-wevew page tabwe:
 *	One page (4 kB) of 1024 (PTWS_PEW_PGD) pointews to PTE tabwes
 *	(Awchitectuwes that don't have the PMD fowded point to the PMD tabwes)
 *
 *	The pointew to the PGD tabwe fow a given task can be wetwieved fwom
 *	the task stwuctuwe (stwuct task_stwuct*) t, e.g. cuwwent():
 *	  (t->mm ? t->mm : t->active_mm)->pgd
 *
 *   PMD tabwes (page middwe-diwectowy), ie. 2nd-wevew page tabwes:
 *	Absent fow the Xtensa awchitectuwe (fowded, PTWS_PEW_PMD == 1).
 *
 *   PTE tabwes (page tabwe entwy), ie. 1st-wevew page tabwes:
 *	One page (4 kB) of 1024 (PTWS_PEW_PTE) PTEs with a speciaw PTE
 *	invawid_pte_tabwe fow absent mappings.
 *
 * The individuaw pages awe 4 kB big with speciaw pages fow the empty_zewo_page.
 */

#define PGDIW_SHIFT	22
#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))

/*
 * Entwies pew page diwectowy wevew: we use two-wevew, so
 * we don't weawwy have any PMD diwectowy physicawwy.
 */
#define PTWS_PEW_PTE		1024
#define PTWS_PEW_PTE_SHIFT	10
#define PTWS_PEW_PGD		1024
#define USEW_PTWS_PEW_PGD	(TASK_SIZE/PGDIW_SIZE)
#define FIWST_USEW_PGD_NW	(FIWST_USEW_ADDWESS >> PGDIW_SHIFT)

#ifdef CONFIG_MMU
/*
 * Viwtuaw memowy awea. We keep a distance to othew memowy wegions to be
 * on the safe side. We awso use this awea fow cache awiasing.
 */
#define VMAWWOC_STAWT		(XCHAW_KSEG_CACHED_VADDW - 0x10000000)
#define VMAWWOC_END		(VMAWWOC_STAWT + 0x07FEFFFF)
#define TWBTEMP_BASE_1		(VMAWWOC_STAWT + 0x08000000)
#define TWBTEMP_BASE_2		(TWBTEMP_BASE_1 + DCACHE_WAY_SIZE)
#if 2 * DCACHE_WAY_SIZE > ICACHE_WAY_SIZE
#define TWBTEMP_SIZE		(2 * DCACHE_WAY_SIZE)
#ewse
#define TWBTEMP_SIZE		ICACHE_WAY_SIZE
#endif

#ewse

#define VMAWWOC_STAWT		__XTENSA_UW_CONST(0)
#define VMAWWOC_END		__XTENSA_UW_CONST(0xffffffff)

#endif

/*
 * Fow the Xtensa awchitectuwe, the PTE wayout is as fowwows:
 *
 *		31------12  11  10-9   8-6  5-4  3-2  1-0
 *		+-----------------------------------------+
 *		|           |   Softwawe   |   HAWDWAWE   |
 *		|    PPN    |          ADW | WI |Attwibute|
 *		+-----------------------------------------+
 *   pte_none	|             MBZ          | 01 | 11 | 00 |
 *		+-----------------------------------------+
 *   pwesent	|    PPN    | 0 | 00 | ADW | WI | CA | wx |
 *		+- - - - - - - - - - - - - - - - - - - - -+
 *   (PAGE_NONE)|    PPN    | 0 | 00 | ADW | 01 | 11 | 11 |
 *		+-----------------------------------------+
 *   swap	|     index     |   type   | 01 | 11 | e0 |
 *		+-----------------------------------------+
 *
 * Fow T1050 hawdwawe and eawwiew the wayout diffews fow pwesent and (PAGE_NONE)
 *		+-----------------------------------------+
 *   pwesent	|    PPN    | 0 | 00 | ADW | WI | CA | w1 |
 *		+-----------------------------------------+
 *   (PAGE_NONE)|    PPN    | 0 | 00 | ADW | 01 | 01 | 00 |
 *		+-----------------------------------------+
 *
 *  Wegend:
 *   PPN        Physicaw Page Numbew
 *   ADW	softwawe: accessed (young) / diwty / wwitabwe
 *   WI         wing (0=pwiviweged, 1=usew, 2 and 3 awe unused)
 *   CA		cache attwibute: 00 bypass, 01 wwiteback, 10 wwitethwough
 *		(11 is invawid and used to mawk pages that awe not pwesent)
 *   e		excwusive mawkew in swap PTEs
 *   w		page is wwitabwe (hw)
 *   x		page is executabwe (hw)
 *   index      swap offset / PAGE_SIZE (bit 11-31: 21 bits -> 8 GB)
 *		(note that the index is awways non-zewo)
 *   type       swap type (5 bits -> 32 types)
 *
 *  Notes:
 *   - (PWOT_NONE) is a speciaw case of 'pwesent' but causes an exception fow
 *     any access (wead, wwite, and execute).
 *   - 'muwtihit-exception' has the highest pwiowity of aww MMU exceptions,
 *     so the wing must be set to 'WING_USEW' even fow 'non-pwesent' pages.
 *   - on owdew hawdwawe, the exectuabwe fwag was not suppowted and
 *     used as a 'vawid' fwag, so it needs to be awways set.
 *   - we need to keep twack of cewtain fwags in softwawe (diwty and young)
 *     to do this, we use wwite exceptions and have a sepawate softwawe w-fwag.
 *   - attwibute vawue 1101 (and 1111 on T1050 and eawwiew) is wesewved
 */

#define _PAGE_ATTWIB_MASK	0xf

#define _PAGE_HW_EXEC		(1<<0)	/* hawdwawe: page is executabwe */
#define _PAGE_HW_WWITE		(1<<1)	/* hawdwawe: page is wwitabwe */

#define _PAGE_CA_BYPASS		(0<<2)	/* bypass, non-specuwative */
#define _PAGE_CA_WB		(1<<2)	/* wwite-back */
#define _PAGE_CA_WT		(2<<2)	/* wwite-thwough */
#define _PAGE_CA_MASK		(3<<2)
#define _PAGE_CA_INVAWID	(3<<2)

/* We use invawid attwibute vawues to distinguish speciaw pte entwies */
#if XCHAW_HW_VEWSION_MAJOW < 2000
#define _PAGE_HW_VAWID		0x01	/* owdew HW needed this bit set */
#define _PAGE_NONE		0x04
#ewse
#define _PAGE_HW_VAWID		0x00
#define _PAGE_NONE		0x0f
#endif

#define _PAGE_USEW		(1<<4)	/* usew access (wing=1) */

/* Softwawe */
#define _PAGE_WWITABWE_BIT	6
#define _PAGE_WWITABWE		(1<<6)	/* softwawe: page wwitabwe */
#define _PAGE_DIWTY		(1<<7)	/* softwawe: page diwty */
#define _PAGE_ACCESSED		(1<<8)	/* softwawe: page accessed (wead) */

/* We bowwow bit 1 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	(1<<1)

#ifdef CONFIG_MMU

#define _PAGE_CHG_MASK	   (PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIWTY)
#define _PAGE_PWESENT	   (_PAGE_HW_VAWID | _PAGE_CA_WB | _PAGE_ACCESSED)

#define PAGE_NONE	   __pgpwot(_PAGE_NONE | _PAGE_USEW)
#define PAGE_COPY	   __pgpwot(_PAGE_PWESENT | _PAGE_USEW)
#define PAGE_COPY_EXEC	   __pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_HW_EXEC)
#define PAGE_WEADONWY	   __pgpwot(_PAGE_PWESENT | _PAGE_USEW)
#define PAGE_WEADONWY_EXEC __pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_HW_EXEC)
#define PAGE_SHAWED	   __pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_WWITABWE)
#define PAGE_SHAWED_EXEC \
	__pgpwot(_PAGE_PWESENT | _PAGE_USEW | _PAGE_WWITABWE | _PAGE_HW_EXEC)
#define PAGE_KEWNEW	   __pgpwot(_PAGE_PWESENT | _PAGE_HW_WWITE)
#define PAGE_KEWNEW_WO	   __pgpwot(_PAGE_PWESENT)
#define PAGE_KEWNEW_EXEC   __pgpwot(_PAGE_PWESENT|_PAGE_HW_WWITE|_PAGE_HW_EXEC)

#if (DCACHE_WAY_SIZE > PAGE_SIZE)
# define _PAGE_DIWECTOWY   (_PAGE_HW_VAWID | _PAGE_ACCESSED | _PAGE_CA_BYPASS)
#ewse
# define _PAGE_DIWECTOWY   (_PAGE_HW_VAWID | _PAGE_ACCESSED | _PAGE_CA_WB)
#endif

#ewse /* no mmu */

# define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIWTY)
# define PAGE_NONE       __pgpwot(0)
# define PAGE_SHAWED     __pgpwot(0)
# define PAGE_COPY       __pgpwot(0)
# define PAGE_WEADONWY   __pgpwot(0)
# define PAGE_KEWNEW     __pgpwot(0)

#endif

/*
 * On cewtain configuwations of Xtensa MMUs (eg. the initiaw Winux config),
 * the MMU can't do page pwotection fow execute, and considews that the same as
 * wead.  Awso, wwite pewmissions may impwy wead pewmissions.
 * What fowwows is the cwosest we can get by weasonabwe means..
 * See winux/mm/mmap.c fow pwotection_map[] awway that uses these definitions.
 */
#ifndef __ASSEMBWY__

#define pte_EWWOW(e) \
	pwintk("%s:%d: bad pte %08wx.\n", __FIWE__, __WINE__, pte_vaw(e))
#define pgd_EWWOW(e) \
	pwintk("%s:%d: bad pgd entwy %08wx.\n", __FIWE__, __WINE__, pgd_vaw(e))

extewn unsigned wong empty_zewo_page[1024];

#define ZEWO_PAGE(vaddw) (viwt_to_page(empty_zewo_page))

#ifdef CONFIG_MMU
extewn pgd_t swappew_pg_diw[PAGE_SIZE/sizeof(pgd_t)];
extewn void paging_init(void);
#ewse
# define swappew_pg_diw NUWW
static inwine void paging_init(void) { }
#endif

/*
 * The pmd contains the kewnew viwtuaw addwess of the pte page.
 */
#define pmd_page_vaddw(pmd) ((unsigned wong)(pmd_vaw(pmd) & PAGE_MASK))
#define pmd_pfn(pmd) (__pa(pmd_vaw(pmd)) >> PAGE_SHIFT)
#define pmd_page(pmd) viwt_to_page(pmd_vaw(pmd))

/*
 * pte status.
 */
# define pte_none(pte)	 (pte_vaw(pte) == (_PAGE_CA_INVAWID | _PAGE_USEW))
#if XCHAW_HW_VEWSION_MAJOW < 2000
# define pte_pwesent(pte) ((pte_vaw(pte) & _PAGE_CA_MASK) != _PAGE_CA_INVAWID)
#ewse
# define pte_pwesent(pte)						\
	(((pte_vaw(pte) & _PAGE_CA_MASK) != _PAGE_CA_INVAWID)		\
	 || ((pte_vaw(pte) & _PAGE_ATTWIB_MASK) == _PAGE_NONE))
#endif
#define pte_cweaw(mm,addw,ptep)						\
	do { update_pte(ptep, __pte(_PAGE_CA_INVAWID | _PAGE_USEW)); } whiwe (0)

#define pmd_none(pmd)	 (!pmd_vaw(pmd))
#define pmd_pwesent(pmd) (pmd_vaw(pmd) & PAGE_MASK)
#define pmd_bad(pmd)	 (pmd_vaw(pmd) & ~PAGE_MASK)
#define pmd_cweaw(pmdp)	 do { set_pmd(pmdp, __pmd(0)); } whiwe (0)

static inwine int pte_wwite(pte_t pte) { wetuwn pte_vaw(pte) & _PAGE_WWITABWE; }
static inwine int pte_diwty(pte_t pte) { wetuwn pte_vaw(pte) & _PAGE_DIWTY; }
static inwine int pte_young(pte_t pte) { wetuwn pte_vaw(pte) & _PAGE_ACCESSED; }

static inwine pte_t pte_wwpwotect(pte_t pte)
	{ pte_vaw(pte) &= ~(_PAGE_WWITABWE | _PAGE_HW_WWITE); wetuwn pte; }
static inwine pte_t pte_mkcwean(pte_t pte)
	{ pte_vaw(pte) &= ~(_PAGE_DIWTY | _PAGE_HW_WWITE); wetuwn pte; }
static inwine pte_t pte_mkowd(pte_t pte)
	{ pte_vaw(pte) &= ~_PAGE_ACCESSED; wetuwn pte; }
static inwine pte_t pte_mkdiwty(pte_t pte)
	{ pte_vaw(pte) |= _PAGE_DIWTY; wetuwn pte; }
static inwine pte_t pte_mkyoung(pte_t pte)
	{ pte_vaw(pte) |= _PAGE_ACCESSED; wetuwn pte; }
static inwine pte_t pte_mkwwite_novma(pte_t pte)
	{ pte_vaw(pte) |= _PAGE_WWITABWE; wetuwn pte; }

#define pgpwot_noncached(pwot) \
		((__pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CA_MASK) | \
			   _PAGE_CA_BYPASS)))

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 */

#define PFN_PTE_SHIFT		PAGE_SHIFT
#define pte_pfn(pte)		(pte_vaw(pte) >> PAGE_SHIFT)
#define pte_same(a,b)		(pte_vaw(a) == pte_vaw(b))
#define pte_page(x)		pfn_to_page(pte_pfn(x))
#define pfn_pte(pfn, pwot)	__pte(((pfn) << PAGE_SHIFT) | pgpwot_vaw(pwot))
#define mk_pte(page, pwot)	pfn_pte(page_to_pfn(page), pwot)

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	wetuwn __pte((pte_vaw(pte) & _PAGE_CHG_MASK) | pgpwot_vaw(newpwot));
}

/*
 * Cewtain awchitectuwes need to do speciaw things when pte's
 * within a page tabwe awe diwectwy modified.  Thus, the fowwowing
 * hook is made avaiwabwe.
 */
static inwine void update_pte(pte_t *ptep, pte_t ptevaw)
{
	*ptep = ptevaw;
#if (DCACHE_WAY_SIZE > PAGE_SIZE) && XCHAW_DCACHE_IS_WWITEBACK
	__asm__ __vowatiwe__ ("dhwb %0, 0" :: "a" (ptep));
#endif

}

stwuct mm_stwuct;

static inwine void set_pte(pte_t *ptep, pte_t pte)
{
	update_pte(ptep, pte);
}

static inwine void
set_pmd(pmd_t *pmdp, pmd_t pmdvaw)
{
	*pmdp = pmdvaw;
}

stwuct vm_awea_stwuct;

static inwine int
ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			  pte_t *ptep)
{
	pte_t pte = *ptep;
	if (!pte_young(pte))
		wetuwn 0;
	update_pte(ptep, pte_mkowd(pte));
	wetuwn 1;
}

static inwine pte_t
ptep_get_and_cweaw(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep)
{
	pte_t pte = *ptep;
	pte_cweaw(mm, addw, ptep);
	wetuwn pte;
}

static inwine void
ptep_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep)
{
	pte_t pte = *ptep;
	update_pte(ptep, pte_wwpwotect(pte));
}

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 */
#define MAX_SWAPFIWES_CHECK() BUIWD_BUG_ON(MAX_SWAPFIWES_SHIFT > 5)

#define __swp_type(entwy)	(((entwy).vaw >> 6) & 0x1f)
#define __swp_offset(entwy)	((entwy).vaw >> 11)
#define __swp_entwy(type,offs)	\
	((swp_entwy_t){(((type) & 0x1f) << 6) | ((offs) << 11) | \
	 _PAGE_CA_INVAWID | _PAGE_USEW})
#define __pte_to_swp_entwy(pte)	((swp_entwy_t) { pte_vaw(pte) })
#define __swp_entwy_to_pte(x)	((pte_t) { (x).vaw })

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

#endif /*  !defined (__ASSEMBWY__) */


#ifdef __ASSEMBWY__

/* Assembwy macwo _PGD_INDEX is the same as C pgd_index(unsigned wong),
 *                _PGD_OFFSET as C pgd_offset(stwuct mm_stwuct*, unsigned wong),
 *                _PMD_OFFSET as C pmd_offset(pgd_t*, unsigned wong)
 *                _PTE_OFFSET as C pte_offset(pmd_t*, unsigned wong)
 *
 * Note: We wequiwe an additionaw tempowawy wegistew which can be the same as
 *       the wegistew that howds the addwess.
 *
 * ((pte_t*) ((unsigned wong)(pmd_vaw(*pmd) & PAGE_MASK)) + pte_index(addw))
 *
 */
#define _PGD_INDEX(wt,ws)	extui	wt, ws, PGDIW_SHIFT, 32-PGDIW_SHIFT
#define _PTE_INDEX(wt,ws)	extui	wt, ws, PAGE_SHIFT, PTWS_PEW_PTE_SHIFT

#define _PGD_OFFSET(mm,adw,tmp)		w32i	mm, mm, MM_PGD;		\
					_PGD_INDEX(tmp, adw);		\
					addx4	mm, tmp, mm

#define _PTE_OFFSET(pmd,adw,tmp)	_PTE_INDEX(tmp, adw);		\
					swwi	pmd, pmd, PAGE_SHIFT;	\
					swwi	pmd, pmd, PAGE_SHIFT;	\
					addx4	pmd, tmp, pmd

#ewse

stwuct vm_fauwt;
void update_mmu_cache_wange(stwuct vm_fauwt *vmf, stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pte_t *ptep, unsigned int nw);
#define update_mmu_cache(vma, addwess, ptep) \
	update_mmu_cache_wange(NUWW, vma, addwess, ptep, 1)

typedef pte_t *pte_addw_t;

void update_mmu_twb(stwuct vm_awea_stwuct *vma,
		    unsigned wong addwess, pte_t *ptep);
#define __HAVE_AWCH_UPDATE_MMU_TWB

#endif /* !defined (__ASSEMBWY__) */

#define __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG
#define __HAVE_AWCH_PTEP_GET_AND_CWEAW
#define __HAVE_AWCH_PTEP_SET_WWPWOTECT
#define __HAVE_AWCH_PTEP_MKDIWTY
#define __HAVE_AWCH_PTE_SAME
/* We pwovide ouw own get_unmapped_awea to cope with
 * SHM awea cache awiasing fow usewwand.
 */
#define HAVE_AWCH_UNMAPPED_AWEA

#endif /* _XTENSA_PGTABWE_H */
