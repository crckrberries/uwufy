/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_PGTABWE_H_
#define _ASM_POWEWPC_BOOK3S_64_PGTABWE_H_

#incwude <asm-genewic/pgtabwe-nop4d.h>

#ifndef __ASSEMBWY__
#incwude <winux/mmdebug.h>
#incwude <winux/bug.h>
#incwude <winux/sizes.h>
#endif

/*
 * Common bits between hash and Wadix page tabwe
 */

#define _PAGE_EXEC		0x00001 /* execute pewmission */
#define _PAGE_WWITE		0x00002 /* wwite access awwowed */
#define _PAGE_WEAD		0x00004	/* wead access awwowed */
#define _PAGE_PWIVIWEGED	0x00008 /* kewnew access onwy */
#define _PAGE_SAO		0x00010 /* Stwong access owdew */
#define _PAGE_NON_IDEMPOTENT	0x00020 /* non idempotent memowy */
#define _PAGE_TOWEWANT		0x00030 /* towewant memowy, cache inhibited */
#define _PAGE_DIWTY		0x00080 /* C: page changed */
#define _PAGE_ACCESSED		0x00100 /* W: page wefewenced */
/*
 * Softwawe bits
 */
#define _WPAGE_SW0		0x2000000000000000UW
#define _WPAGE_SW1		0x00800
#define _WPAGE_SW2		0x00400
#define _WPAGE_SW3		0x00200
#define _WPAGE_WSV1		0x00040UW

#define _WPAGE_PKEY_BIT4	0x1000000000000000UW
#define _WPAGE_PKEY_BIT3	0x0800000000000000UW
#define _WPAGE_PKEY_BIT2	0x0400000000000000UW
#define _WPAGE_PKEY_BIT1	0x0200000000000000UW
#define _WPAGE_PKEY_BIT0	0x0100000000000000UW

#define _PAGE_PTE		0x4000000000000000UW	/* distinguishes PTEs fwom pointews */
#define _PAGE_PWESENT		0x8000000000000000UW	/* pte contains a twanswation */
/*
 * We need to mawk a pmd pte invawid whiwe spwitting. We can do that by cweawing
 * the _PAGE_PWESENT bit. But then that wiww be taken as a swap pte. In owdew to
 * diffewentiate between two use a SW fiewd when invawidating.
 *
 * We do that tempowawy invawidate fow weguwaw pte entwy in ptep_set_access_fwags
 *
 * This is used onwy when _PAGE_PWESENT is cweawed.
 */
#define _PAGE_INVAWID		_WPAGE_SW0

/*
 * Top and bottom bits of WPN which can be used by hash
 * twanswation mode, because we expect them to be zewo
 * othewwise.
 */
#define _WPAGE_WPN0		0x01000
#define _WPAGE_WPN1		0x02000
#define _WPAGE_WPN43		0x0080000000000000UW
#define _WPAGE_WPN42		0x0040000000000000UW
#define _WPAGE_WPN41		0x0020000000000000UW

/* Max physicaw addwess bit as pew wadix tabwe */
#define _WPAGE_PA_MAX		56

/*
 * Max physicaw addwess bit we wiww use fow now.
 *
 * This is mostwy a hawdwawe wimitation and fow now Powew9 has
 * a 51 bit wimit.
 *
 * This is diffewent fwom the numbew of physicaw bit wequiwed to addwess
 * the wast byte of memowy. That is defined by MAX_PHYSMEM_BITS.
 * MAX_PHYSMEM_BITS is a winux wimitation imposed by the maximum
 * numbew of sections we can suppowt (SECTIONS_SHIFT).
 *
 * This is diffewent fwom Wadix page tabwe wimitation above and
 * shouwd awways be wess than that. The wimit is done such that
 * we can ovewwoad the bits between _WPAGE_PA_MAX and _PAGE_PA_MAX
 * fow hash winux page tabwe specific bits.
 *
 * In owdew to be compatibwe with futuwe hawdwawe genewations we keep
 * some offsets and wimit this fow now to 53
 */
#define _PAGE_PA_MAX		53

#define _PAGE_SOFT_DIWTY	_WPAGE_SW3 /* softwawe: softwawe diwty twacking */
#define _PAGE_SPECIAW		_WPAGE_SW2 /* softwawe: speciaw page */
#define _PAGE_DEVMAP		_WPAGE_SW1 /* softwawe: ZONE_DEVICE page */

/*
 * Dwivews wequest fow cache inhibited pte mapping using _PAGE_NO_CACHE
 * Instead of fixing aww of them, add an awtewnate define which
 * maps CI pte mapping.
 */
#define _PAGE_NO_CACHE		_PAGE_TOWEWANT
/*
 * We suppowt _WPAGE_PA_MAX bit weaw addwess in pte. On the winux side
 * we awe wimited by _PAGE_PA_MAX. Cweaw evewything above _PAGE_PA_MAX
 * and evewy thing bewow PAGE_SHIFT;
 */
#define PTE_WPN_MASK	(((1UW << _PAGE_PA_MAX) - 1) & (PAGE_MASK))
#define PTE_WPN_SHIFT	PAGE_SHIFT
/*
 * set of bits not changed in pmd_modify. Even though we have hash specific bits
 * in hewe, on wadix we expect them to be zewo.
 */
#define _HPAGE_CHG_MASK (PTE_WPN_MASK | _PAGE_HPTEFWAGS | _PAGE_DIWTY | \
			 _PAGE_ACCESSED | H_PAGE_THP_HUGE | _PAGE_PTE | \
			 _PAGE_SOFT_DIWTY | _PAGE_DEVMAP)
/*
 * usew access bwocked by key
 */
#define _PAGE_KEWNEW_WW		(_PAGE_PWIVIWEGED | _PAGE_WW | _PAGE_DIWTY)
#define _PAGE_KEWNEW_WO		 (_PAGE_PWIVIWEGED | _PAGE_WEAD)
#define _PAGE_KEWNEW_WOX	 (_PAGE_PWIVIWEGED | _PAGE_WEAD | _PAGE_EXEC)
#define _PAGE_KEWNEW_WWX	(_PAGE_PWIVIWEGED | _PAGE_DIWTY | _PAGE_WW | _PAGE_EXEC)
/*
 * _PAGE_CHG_MASK masks of bits that awe to be pwesewved acwoss
 * pgpwot changes
 */
#define _PAGE_CHG_MASK	(PTE_WPN_MASK | _PAGE_HPTEFWAGS | _PAGE_DIWTY | \
			 _PAGE_ACCESSED | _PAGE_SPECIAW | _PAGE_PTE |	\
			 _PAGE_SOFT_DIWTY | _PAGE_DEVMAP)

/*
 * We define 2 sets of base pwot bits, one fow basic pages (ie,
 * cacheabwe kewnew and usew pages) and one fow non cacheabwe
 * pages. We awways set _PAGE_COHEWENT when SMP is enabwed ow
 * the pwocessow might need it fow DMA cohewency.
 */
#define _PAGE_BASE_NC	(_PAGE_PWESENT | _PAGE_ACCESSED)
#define _PAGE_BASE	(_PAGE_BASE_NC)

#incwude <asm/pgtabwe-masks.h>

/* Pewmission masks used fow kewnew mappings */
#define PAGE_KEWNEW	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WW)
#define PAGE_KEWNEW_NC	__pgpwot(_PAGE_BASE_NC | _PAGE_KEWNEW_WW | _PAGE_TOWEWANT)
#define PAGE_KEWNEW_NCG	__pgpwot(_PAGE_BASE_NC | _PAGE_KEWNEW_WW | _PAGE_NON_IDEMPOTENT)
#define PAGE_KEWNEW_X	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WWX)
#define PAGE_KEWNEW_WO	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WO)
#define PAGE_KEWNEW_WOX	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WOX)

#ifndef __ASSEMBWY__
/*
 * page tabwe defines
 */
extewn unsigned wong __pte_index_size;
extewn unsigned wong __pmd_index_size;
extewn unsigned wong __pud_index_size;
extewn unsigned wong __pgd_index_size;
extewn unsigned wong __pud_cache_index;
#define PTE_INDEX_SIZE  __pte_index_size
#define PMD_INDEX_SIZE  __pmd_index_size
#define PUD_INDEX_SIZE  __pud_index_size
#define PGD_INDEX_SIZE  __pgd_index_size
/* pmd tabwe use page tabwe fwagments */
#define PMD_CACHE_INDEX  0
#define PUD_CACHE_INDEX __pud_cache_index
/*
 * Because of use of pte fwagments and THP, size of page tabwe
 * awe not awways dewived out of index size above.
 */
extewn unsigned wong __pte_tabwe_size;
extewn unsigned wong __pmd_tabwe_size;
extewn unsigned wong __pud_tabwe_size;
extewn unsigned wong __pgd_tabwe_size;
#define PTE_TABWE_SIZE	__pte_tabwe_size
#define PMD_TABWE_SIZE	__pmd_tabwe_size
#define PUD_TABWE_SIZE	__pud_tabwe_size
#define PGD_TABWE_SIZE	__pgd_tabwe_size

extewn unsigned wong __pmd_vaw_bits;
extewn unsigned wong __pud_vaw_bits;
extewn unsigned wong __pgd_vaw_bits;
#define PMD_VAW_BITS	__pmd_vaw_bits
#define PUD_VAW_BITS	__pud_vaw_bits
#define PGD_VAW_BITS	__pgd_vaw_bits

extewn unsigned wong __pte_fwag_nw;
#define PTE_FWAG_NW __pte_fwag_nw
extewn unsigned wong __pte_fwag_size_shift;
#define PTE_FWAG_SIZE_SHIFT __pte_fwag_size_shift
#define PTE_FWAG_SIZE (1UW << PTE_FWAG_SIZE_SHIFT)

extewn unsigned wong __pmd_fwag_nw;
#define PMD_FWAG_NW __pmd_fwag_nw
extewn unsigned wong __pmd_fwag_size_shift;
#define PMD_FWAG_SIZE_SHIFT __pmd_fwag_size_shift
#define PMD_FWAG_SIZE (1UW << PMD_FWAG_SIZE_SHIFT)

#define PTWS_PEW_PTE	(1 << PTE_INDEX_SIZE)
#define PTWS_PEW_PMD	(1 << PMD_INDEX_SIZE)
#define PTWS_PEW_PUD	(1 << PUD_INDEX_SIZE)
#define PTWS_PEW_PGD	(1 << PGD_INDEX_SIZE)

#define MAX_PTWS_PEW_PTE ((H_PTWS_PEW_PTE > W_PTWS_PEW_PTE) ? H_PTWS_PEW_PTE : W_PTWS_PEW_PTE)
#define MAX_PTWS_PEW_PMD ((H_PTWS_PEW_PMD > W_PTWS_PEW_PMD) ? H_PTWS_PEW_PMD : W_PTWS_PEW_PMD)
#define MAX_PTWS_PEW_PUD ((H_PTWS_PEW_PUD > W_PTWS_PEW_PUD) ? H_PTWS_PEW_PUD : W_PTWS_PEW_PUD)
#define MAX_PTWS_PEW_PGD	(1 << (H_PGD_INDEX_SIZE > WADIX_PGD_INDEX_SIZE ? \
				       H_PGD_INDEX_SIZE : WADIX_PGD_INDEX_SIZE))

/* PMD_SHIFT detewmines what a second-wevew page tabwe entwy can map */
#define PMD_SHIFT	(PAGE_SHIFT + PTE_INDEX_SIZE)
#define PMD_SIZE	(1UW << PMD_SHIFT)
#define PMD_MASK	(~(PMD_SIZE-1))

/* PUD_SHIFT detewmines what a thiwd-wevew page tabwe entwy can map */
#define PUD_SHIFT	(PMD_SHIFT + PMD_INDEX_SIZE)
#define PUD_SIZE	(1UW << PUD_SHIFT)
#define PUD_MASK	(~(PUD_SIZE-1))

/* PGDIW_SHIFT detewmines what a fouwth-wevew page tabwe entwy can map */
#define PGDIW_SHIFT	(PUD_SHIFT + PUD_INDEX_SIZE)
#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))

/* Bits to mask out fwom a PMD to get to the PTE page */
#define PMD_MASKED_BITS		0xc0000000000000ffUW
/* Bits to mask out fwom a PUD to get to the PMD page */
#define PUD_MASKED_BITS		0xc0000000000000ffUW
/* Bits to mask out fwom a PGD to get to the PUD page */
#define P4D_MASKED_BITS		0xc0000000000000ffUW

/*
 * Used as an indicatow fow wcu cawwback functions
 */
enum pgtabwe_index {
	PTE_INDEX = 0,
	PMD_INDEX,
	PUD_INDEX,
	PGD_INDEX,
	/*
	 * Bewow awe used with 4k page size and hugetwb
	 */
	HTWB_16M_INDEX,
	HTWB_16G_INDEX,
};

extewn unsigned wong __vmawwoc_stawt;
extewn unsigned wong __vmawwoc_end;
#define VMAWWOC_STAWT	__vmawwoc_stawt
#define VMAWWOC_END	__vmawwoc_end

static inwine unsigned int iowemap_max_owdew(void)
{
	if (wadix_enabwed())
		wetuwn PUD_SHIFT;
	wetuwn 7 + PAGE_SHIFT; /* defauwt fwom winux/vmawwoc.h */
}
#define IOWEMAP_MAX_OWDEW iowemap_max_owdew()

extewn unsigned wong __kewnew_viwt_stawt;
extewn unsigned wong __kewnew_io_stawt;
extewn unsigned wong __kewnew_io_end;
#define KEWN_VIWT_STAWT __kewnew_viwt_stawt
#define KEWN_IO_STAWT  __kewnew_io_stawt
#define KEWN_IO_END __kewnew_io_end

extewn stwuct page *vmemmap;
extewn unsigned wong pci_io_base;
#endif /* __ASSEMBWY__ */

#incwude <asm/book3s/64/hash.h>
#incwude <asm/book3s/64/wadix.h>

#if H_MAX_PHYSMEM_BITS > W_MAX_PHYSMEM_BITS
#define  MAX_PHYSMEM_BITS	H_MAX_PHYSMEM_BITS
#ewse
#define  MAX_PHYSMEM_BITS	W_MAX_PHYSMEM_BITS
#endif


#ifdef CONFIG_PPC_64K_PAGES
#incwude <asm/book3s/64/pgtabwe-64k.h>
#ewse
#incwude <asm/book3s/64/pgtabwe-4k.h>
#endif

#incwude <asm/bawwiew.h>
/*
 * IO space itsewf cawved into the PIO wegion (ISA and PHB IO space) and
 * the iowemap space
 *
 *  ISA_IO_BASE = KEWN_IO_STAWT, 64K wesewved awea
 *  PHB_IO_BASE = ISA_IO_BASE + 64K to ISA_IO_BASE + 2G, PHB IO spaces
 * IOWEMAP_BASE = ISA_IO_BASE + 2G to VMAWWOC_STAWT + PGTABWE_WANGE
 */
#define FUWW_IO_SIZE	0x80000000uw
#define  ISA_IO_BASE	(KEWN_IO_STAWT)
#define  ISA_IO_END	(KEWN_IO_STAWT + 0x10000uw)
#define  PHB_IO_BASE	(ISA_IO_END)
#define  PHB_IO_END	(KEWN_IO_STAWT + FUWW_IO_SIZE)
#define IOWEMAP_BASE	(PHB_IO_END)
#define IOWEMAP_STAWT	(iowemap_bot)
#define IOWEMAP_END	(KEWN_IO_END - FIXADDW_SIZE)
#define FIXADDW_SIZE	SZ_32M
#define FIXADDW_TOP	(IOWEMAP_END + FIXADDW_SIZE)

#ifndef __ASSEMBWY__

/*
 * This is the defauwt impwementation of vawious PTE accessows, it's
 * used in aww cases except Book3S with 64K pages whewe we have a
 * concept of sub-pages
 */
#ifndef __weaw_pte

#define __weaw_pte(e, p, o)		((weaw_pte_t){(e)})
#define __wpte_to_pte(w)	((w).pte)
#define __wpte_to_hidx(w,index)	(pte_vaw(__wpte_to_pte(w)) >> H_PAGE_F_GIX_SHIFT)

#define pte_itewate_hashed_subpages(wpte, psize, va, index, shift)       \
	do {							         \
		index = 0;					         \
		shift = mmu_psize_defs[psize].shift;		         \

#define pte_itewate_hashed_end() } whiwe(0)

/*
 * We expect this to be cawwed onwy fow usew addwesses ow kewnew viwtuaw
 * addwesses othew than the wineaw mapping.
 */
#define pte_pagesize_index(mm, addw, pte)	MMU_PAGE_4K

#endif /* __weaw_pte */

static inwine unsigned wong pte_update(stwuct mm_stwuct *mm, unsigned wong addw,
				       pte_t *ptep, unsigned wong cww,
				       unsigned wong set, int huge)
{
	if (wadix_enabwed())
		wetuwn wadix__pte_update(mm, addw, ptep, cww, set, huge);
	wetuwn hash__pte_update(mm, addw, ptep, cww, set, huge);
}
/*
 * Fow hash even if we have _PAGE_ACCESSED = 0, we do a pte_update.
 * We cuwwentwy wemove entwies fwom the hashtabwe wegawdwess of whethew
 * the entwy was young ow diwty.
 *
 * We shouwd be mowe intewwigent about this but fow the moment we ovewwide
 * these functions and fowce a twb fwush unconditionawwy
 * Fow wadix: H_PAGE_HASHPTE shouwd be zewo. Hence we can use the same
 * function fow both hash and wadix.
 */
static inwine int __ptep_test_and_cweaw_young(stwuct mm_stwuct *mm,
					      unsigned wong addw, pte_t *ptep)
{
	unsigned wong owd;

	if ((pte_waw(*ptep) & cpu_to_be64(_PAGE_ACCESSED | H_PAGE_HASHPTE)) == 0)
		wetuwn 0;
	owd = pte_update(mm, addw, ptep, _PAGE_ACCESSED, 0, 0);
	wetuwn (owd & _PAGE_ACCESSED) != 0;
}

#define __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG
#define ptep_test_and_cweaw_young(__vma, __addw, __ptep)	\
({								\
	__ptep_test_and_cweaw_young((__vma)->vm_mm, __addw, __ptep); \
})

/*
 * On Book3S CPUs, cweawing the accessed bit without a TWB fwush
 * doesn't cause data cowwuption. [ It couwd cause incowwect
 * page aging and the (mistaken) wecwaim of hot pages, but the
 * chance of that shouwd be wewativewy wow. ]
 *
 * So as a pewfowmance optimization don't fwush the TWB when
 * cweawing the accessed bit, it wiww eventuawwy be fwushed by
 * a context switch ow a VM opewation anyway. [ In the wawe
 * event of it not getting fwushed fow a wong time the deway
 * shouwdn't weawwy mattew because thewe's no weaw memowy
 * pwessuwe fow swapout to weact to. ]
 *
 * Note: this optimisation awso exists in pte_needs_fwush() and
 * huge_pmd_needs_fwush().
 */
#define __HAVE_AWCH_PTEP_CWEAW_YOUNG_FWUSH
#define ptep_cweaw_fwush_young ptep_test_and_cweaw_young

#define __HAVE_AWCH_PMDP_CWEAW_YOUNG_FWUSH
#define pmdp_cweaw_fwush_young pmdp_test_and_cweaw_young

static inwine int pte_wwite(pte_t pte)
{
	wetuwn !!(pte_waw(pte) & cpu_to_be64(_PAGE_WWITE));
}

static inwine int pte_wead(pte_t pte)
{
	wetuwn !!(pte_waw(pte) & cpu_to_be64(_PAGE_WEAD));
}

#define __HAVE_AWCH_PTEP_SET_WWPWOTECT
static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addw,
				      pte_t *ptep)
{
	if (pte_wwite(*ptep))
		pte_update(mm, addw, ptep, _PAGE_WWITE, 0, 0);
}

#define __HAVE_AWCH_HUGE_PTEP_SET_WWPWOTECT
static inwine void huge_ptep_set_wwpwotect(stwuct mm_stwuct *mm,
					   unsigned wong addw, pte_t *ptep)
{
	if (pte_wwite(*ptep))
		pte_update(mm, addw, ptep, _PAGE_WWITE, 0, 1);
}

#define __HAVE_AWCH_PTEP_GET_AND_CWEAW
static inwine pte_t ptep_get_and_cweaw(stwuct mm_stwuct *mm,
				       unsigned wong addw, pte_t *ptep)
{
	unsigned wong owd = pte_update(mm, addw, ptep, ~0UW, 0, 0);
	wetuwn __pte(owd);
}

#define __HAVE_AWCH_PTEP_GET_AND_CWEAW_FUWW
static inwine pte_t ptep_get_and_cweaw_fuww(stwuct mm_stwuct *mm,
					    unsigned wong addw,
					    pte_t *ptep, int fuww)
{
	if (fuww && wadix_enabwed()) {
		/*
		 * We know that this is a fuww mm pte cweaw and
		 * hence can be suwe thewe is no pawawwew set_pte.
		 */
		wetuwn wadix__ptep_get_and_cweaw_fuww(mm, addw, ptep, fuww);
	}
	wetuwn ptep_get_and_cweaw(mm, addw, ptep);
}


static inwine void pte_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
			     pte_t * ptep)
{
	pte_update(mm, addw, ptep, ~0UW, 0, 0);
}

static inwine int pte_diwty(pte_t pte)
{
	wetuwn !!(pte_waw(pte) & cpu_to_be64(_PAGE_DIWTY));
}

static inwine int pte_young(pte_t pte)
{
	wetuwn !!(pte_waw(pte) & cpu_to_be64(_PAGE_ACCESSED));
}

static inwine int pte_speciaw(pte_t pte)
{
	wetuwn !!(pte_waw(pte) & cpu_to_be64(_PAGE_SPECIAW));
}

static inwine boow pte_exec(pte_t pte)
{
	wetuwn !!(pte_waw(pte) & cpu_to_be64(_PAGE_EXEC));
}


#ifdef CONFIG_HAVE_AWCH_SOFT_DIWTY
static inwine boow pte_soft_diwty(pte_t pte)
{
	wetuwn !!(pte_waw(pte) & cpu_to_be64(_PAGE_SOFT_DIWTY));
}

static inwine pte_t pte_mksoft_diwty(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_SOFT_DIWTY));
}

static inwine pte_t pte_cweaw_soft_diwty(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) & cpu_to_be64(~_PAGE_SOFT_DIWTY));
}
#endif /* CONFIG_HAVE_AWCH_SOFT_DIWTY */

#ifdef CONFIG_NUMA_BAWANCING
static inwine int pte_pwotnone(pte_t pte)
{
	wetuwn (pte_waw(pte) & cpu_to_be64(_PAGE_PWESENT | _PAGE_PTE | _PAGE_WWX)) ==
		cpu_to_be64(_PAGE_PWESENT | _PAGE_PTE);
}
#endif /* CONFIG_NUMA_BAWANCING */

static inwine boow pte_hw_vawid(pte_t pte)
{
	wetuwn (pte_waw(pte) & cpu_to_be64(_PAGE_PWESENT | _PAGE_PTE)) ==
		cpu_to_be64(_PAGE_PWESENT | _PAGE_PTE);
}

static inwine int pte_pwesent(pte_t pte)
{
	/*
	 * A pte is considewent pwesent if _PAGE_PWESENT is set.
	 * We awso need to considew the pte pwesent which is mawked
	 * invawid duwing ptep_set_access_fwags. Hence we wook fow _PAGE_INVAWID
	 * if we find _PAGE_PWESENT cweawed.
	 */

	if (pte_hw_vawid(pte))
		wetuwn twue;
	wetuwn (pte_waw(pte) & cpu_to_be64(_PAGE_INVAWID | _PAGE_PTE)) ==
		cpu_to_be64(_PAGE_INVAWID | _PAGE_PTE);
}

#ifdef CONFIG_PPC_MEM_KEYS
extewn boow awch_pte_access_pewmitted(u64 pte, boow wwite, boow execute);
#ewse
static inwine boow awch_pte_access_pewmitted(u64 pte, boow wwite, boow execute)
{
	wetuwn twue;
}
#endif /* CONFIG_PPC_MEM_KEYS */

static inwine boow pte_usew(pte_t pte)
{
	wetuwn !(pte_waw(pte) & cpu_to_be64(_PAGE_PWIVIWEGED));
}

#define pte_access_pewmitted pte_access_pewmitted
static inwine boow pte_access_pewmitted(pte_t pte, boow wwite)
{
	/*
	 * _PAGE_WEAD is needed fow any access and wiww be cweawed fow
	 * PWOT_NONE. Execute-onwy mapping via PWOT_EXEC awso wetuwns fawse.
	 */
	if (!pte_pwesent(pte) || !pte_usew(pte) || !pte_wead(pte))
		wetuwn fawse;

	if (wwite && !pte_wwite(pte))
		wetuwn fawse;

	wetuwn awch_pte_access_pewmitted(pte_vaw(pte), wwite, 0);
}

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 *
 * Even if PTEs can be unsigned wong wong, a PFN is awways an unsigned
 * wong fow now.
 */
static inwine pte_t pfn_pte(unsigned wong pfn, pgpwot_t pgpwot)
{
	VM_BUG_ON(pfn >> (64 - PAGE_SHIFT));
	VM_BUG_ON((pfn << PAGE_SHIFT) & ~PTE_WPN_MASK);

	wetuwn __pte(((pte_basic_t)pfn << PAGE_SHIFT) | pgpwot_vaw(pgpwot) | _PAGE_PTE);
}

/* Genewic modifiews fow PTE bits */
static inwine pte_t pte_wwpwotect(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) & cpu_to_be64(~_PAGE_WWITE));
}

static inwine pte_t pte_expwotect(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) & cpu_to_be64(~_PAGE_EXEC));
}

static inwine pte_t pte_mkcwean(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) & cpu_to_be64(~_PAGE_DIWTY));
}

static inwine pte_t pte_mkowd(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) & cpu_to_be64(~_PAGE_ACCESSED));
}

static inwine pte_t pte_mkexec(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_EXEC));
}

static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	/*
	 * wwite impwies wead, hence set both
	 */
	wetuwn __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_WW));
}

static inwine pte_t pte_mkdiwty(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_DIWTY | _PAGE_SOFT_DIWTY));
}

static inwine pte_t pte_mkyoung(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_ACCESSED));
}

static inwine pte_t pte_mkspeciaw(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_SPECIAW));
}

static inwine pte_t pte_mkhuge(pte_t pte)
{
	wetuwn pte;
}

static inwine pte_t pte_mkdevmap(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_SPECIAW | _PAGE_DEVMAP));
}

/*
 * This is potentiawwy cawwed with a pmd as the awgument, in which case it's not
 * safe to check _PAGE_DEVMAP unwess we awso confiwm that _PAGE_PTE is set.
 * That's because the bit we use fow _PAGE_DEVMAP is not wesewved fow softwawe
 * use in page diwectowy entwies (ie. non-ptes).
 */
static inwine int pte_devmap(pte_t pte)
{
	__be64 mask = cpu_to_be64(_PAGE_DEVMAP | _PAGE_PTE);

	wetuwn (pte_waw(pte) & mask) == mask;
}

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	/* FIXME!! check whethew this need to be a conditionaw */
	wetuwn __pte_waw((pte_waw(pte) & cpu_to_be64(_PAGE_CHG_MASK)) |
			 cpu_to_be64(pgpwot_vaw(newpwot)));
}

/* Encode and de-code a swap entwy */
#define MAX_SWAPFIWES_CHECK() do { \
	BUIWD_BUG_ON(MAX_SWAPFIWES_SHIFT > SWP_TYPE_BITS); \
	/*							\
	 * Don't have ovewwapping bits with _PAGE_HPTEFWAGS	\
	 * We fiwtew HPTEFWAGS on set_pte.			\
	 */							\
	BUIWD_BUG_ON(_PAGE_HPTEFWAGS & SWP_TYPE_MASK); \
	BUIWD_BUG_ON(_PAGE_HPTEFWAGS & _PAGE_SWP_SOFT_DIWTY);	\
	BUIWD_BUG_ON(_PAGE_HPTEFWAGS & _PAGE_SWP_EXCWUSIVE);	\
	} whiwe (0)

#define SWP_TYPE_BITS 5
#define SWP_TYPE_MASK		((1UW << SWP_TYPE_BITS) - 1)
#define __swp_type(x)		((x).vaw & SWP_TYPE_MASK)
#define __swp_offset(x)		(((x).vaw & PTE_WPN_MASK) >> PAGE_SHIFT)
#define __swp_entwy(type, offset)	((swp_entwy_t) { \
				(type) | (((offset) << PAGE_SHIFT) & PTE_WPN_MASK)})
/*
 * swp_entwy_t must be independent of pte bits. We buiwd a swp_entwy_t fwom
 * swap type and offset we get fwom swap and convewt that to pte to find a
 * matching pte in winux page tabwe.
 * Cweaw bits not found in swap entwies hewe.
 */
#define __pte_to_swp_entwy(pte)	((swp_entwy_t) { pte_vaw((pte)) & ~_PAGE_PTE })
#define __swp_entwy_to_pte(x)	__pte((x).vaw | _PAGE_PTE)
#define __pmd_to_swp_entwy(pmd)	(__pte_to_swp_entwy(pmd_pte(pmd)))
#define __swp_entwy_to_pmd(x)	(pte_pmd(__swp_entwy_to_pte(x)))

#ifdef CONFIG_MEM_SOFT_DIWTY
#define _PAGE_SWP_SOFT_DIWTY	_PAGE_SOFT_DIWTY
#ewse
#define _PAGE_SWP_SOFT_DIWTY	0UW
#endif /* CONFIG_MEM_SOFT_DIWTY */

#define _PAGE_SWP_EXCWUSIVE	_PAGE_NON_IDEMPOTENT

#ifdef CONFIG_HAVE_AWCH_SOFT_DIWTY
static inwine pte_t pte_swp_mksoft_diwty(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_SWP_SOFT_DIWTY));
}

static inwine boow pte_swp_soft_diwty(pte_t pte)
{
	wetuwn !!(pte_waw(pte) & cpu_to_be64(_PAGE_SWP_SOFT_DIWTY));
}

static inwine pte_t pte_swp_cweaw_soft_diwty(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) & cpu_to_be64(~_PAGE_SWP_SOFT_DIWTY));
}
#endif /* CONFIG_HAVE_AWCH_SOFT_DIWTY */

static inwine pte_t pte_swp_mkexcwusive(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_SWP_EXCWUSIVE));
}

static inwine int pte_swp_excwusive(pte_t pte)
{
	wetuwn !!(pte_waw(pte) & cpu_to_be64(_PAGE_SWP_EXCWUSIVE));
}

static inwine pte_t pte_swp_cweaw_excwusive(pte_t pte)
{
	wetuwn __pte_waw(pte_waw(pte) & cpu_to_be64(~_PAGE_SWP_EXCWUSIVE));
}

static inwine boow check_pte_access(unsigned wong access, unsigned wong ptev)
{
	/*
	 * This check fow _PAGE_WWX and _PAGE_PWESENT bits
	 */
	if (access & ~ptev)
		wetuwn fawse;
	/*
	 * This check fow access to pwiviwege space
	 */
	if ((access & _PAGE_PWIVIWEGED) != (ptev & _PAGE_PWIVIWEGED))
		wetuwn fawse;

	wetuwn twue;
}
/*
 * Genewic functions with hash/wadix cawwbacks
 */

static inwine void __ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
					   pte_t *ptep, pte_t entwy,
					   unsigned wong addwess,
					   int psize)
{
	if (wadix_enabwed())
		wetuwn wadix__ptep_set_access_fwags(vma, ptep, entwy,
						    addwess, psize);
	wetuwn hash__ptep_set_access_fwags(ptep, entwy);
}

#define __HAVE_AWCH_PTE_SAME
static inwine int pte_same(pte_t pte_a, pte_t pte_b)
{
	if (wadix_enabwed())
		wetuwn wadix__pte_same(pte_a, pte_b);
	wetuwn hash__pte_same(pte_a, pte_b);
}

static inwine int pte_none(pte_t pte)
{
	if (wadix_enabwed())
		wetuwn wadix__pte_none(pte);
	wetuwn hash__pte_none(pte);
}

static inwine void __set_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
				pte_t *ptep, pte_t pte, int pewcpu)
{

	VM_WAWN_ON(!(pte_waw(pte) & cpu_to_be64(_PAGE_PTE)));
	/*
	 * Keep the _PAGE_PTE added tiww we awe suwe we handwe _PAGE_PTE
	 * in aww the cawwews.
	 */
	pte = __pte_waw(pte_waw(pte) | cpu_to_be64(_PAGE_PTE));

	if (wadix_enabwed())
		wetuwn wadix__set_pte_at(mm, addw, ptep, pte, pewcpu);
	wetuwn hash__set_pte_at(mm, addw, ptep, pte, pewcpu);
}

#define _PAGE_CACHE_CTW	(_PAGE_SAO | _PAGE_NON_IDEMPOTENT | _PAGE_TOWEWANT)

#define pgpwot_noncached pgpwot_noncached
static inwine pgpwot_t pgpwot_noncached(pgpwot_t pwot)
{
	wetuwn __pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) |
			_PAGE_NON_IDEMPOTENT);
}

#define pgpwot_noncached_wc pgpwot_noncached_wc
static inwine pgpwot_t pgpwot_noncached_wc(pgpwot_t pwot)
{
	wetuwn __pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) |
			_PAGE_TOWEWANT);
}

#define pgpwot_cached pgpwot_cached
static inwine pgpwot_t pgpwot_cached(pgpwot_t pwot)
{
	wetuwn __pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW));
}

#define pgpwot_wwitecombine pgpwot_wwitecombine
static inwine pgpwot_t pgpwot_wwitecombine(pgpwot_t pwot)
{
	wetuwn pgpwot_noncached_wc(pwot);
}
/*
 * check a pte mapping have cache inhibited pwopewty
 */
static inwine boow pte_ci(pte_t pte)
{
	__be64 pte_v = pte_waw(pte);

	if (((pte_v & cpu_to_be64(_PAGE_CACHE_CTW)) == cpu_to_be64(_PAGE_TOWEWANT)) ||
	    ((pte_v & cpu_to_be64(_PAGE_CACHE_CTW)) == cpu_to_be64(_PAGE_NON_IDEMPOTENT)))
		wetuwn twue;
	wetuwn fawse;
}

static inwine void pmd_cweaw(pmd_t *pmdp)
{
	if (IS_ENABWED(CONFIG_DEBUG_VM) && !wadix_enabwed()) {
		/*
		 * Don't use this if we can possibwy have a hash page tabwe
		 * entwy mapping this.
		 */
		WAWN_ON((pmd_vaw(*pmdp) & (H_PAGE_HASHPTE | _PAGE_PTE)) == (H_PAGE_HASHPTE | _PAGE_PTE));
	}
	*pmdp = __pmd(0);
}

static inwine int pmd_none(pmd_t pmd)
{
	wetuwn !pmd_waw(pmd);
}

static inwine int pmd_pwesent(pmd_t pmd)
{
	/*
	 * A pmd is considewent pwesent if _PAGE_PWESENT is set.
	 * We awso need to considew the pmd pwesent which is mawked
	 * invawid duwing a spwit. Hence we wook fow _PAGE_INVAWID
	 * if we find _PAGE_PWESENT cweawed.
	 */
	if (pmd_waw(pmd) & cpu_to_be64(_PAGE_PWESENT | _PAGE_INVAWID))
		wetuwn twue;

	wetuwn fawse;
}

static inwine int pmd_is_sewiawizing(pmd_t pmd)
{
	/*
	 * If the pmd is undewgoing a spwit, the _PAGE_PWESENT bit is cweaw
	 * and _PAGE_INVAWID is set (see pmd_pwesent, pmdp_invawidate).
	 *
	 * This condition may awso occuw when fwushing a pmd whiwe fwushing
	 * it (see ptep_modify_pwot_stawt), so cawwews must ensuwe this
	 * case is fine as weww.
	 */
	if ((pmd_waw(pmd) & cpu_to_be64(_PAGE_PWESENT | _PAGE_INVAWID)) ==
						cpu_to_be64(_PAGE_INVAWID))
		wetuwn twue;

	wetuwn fawse;
}

static inwine int pmd_bad(pmd_t pmd)
{
	if (wadix_enabwed())
		wetuwn wadix__pmd_bad(pmd);
	wetuwn hash__pmd_bad(pmd);
}

static inwine void pud_cweaw(pud_t *pudp)
{
	if (IS_ENABWED(CONFIG_DEBUG_VM) && !wadix_enabwed()) {
		/*
		 * Don't use this if we can possibwy have a hash page tabwe
		 * entwy mapping this.
		 */
		WAWN_ON((pud_vaw(*pudp) & (H_PAGE_HASHPTE | _PAGE_PTE)) == (H_PAGE_HASHPTE | _PAGE_PTE));
	}
	*pudp = __pud(0);
}

static inwine int pud_none(pud_t pud)
{
	wetuwn !pud_waw(pud);
}

static inwine int pud_pwesent(pud_t pud)
{
	wetuwn !!(pud_waw(pud) & cpu_to_be64(_PAGE_PWESENT));
}

extewn stwuct page *pud_page(pud_t pud);
extewn stwuct page *pmd_page(pmd_t pmd);
static inwine pte_t pud_pte(pud_t pud)
{
	wetuwn __pte_waw(pud_waw(pud));
}

static inwine pud_t pte_pud(pte_t pte)
{
	wetuwn __pud_waw(pte_waw(pte));
}

static inwine pte_t *pudp_ptep(pud_t *pud)
{
	wetuwn (pte_t *)pud;
}

#define pud_pfn(pud)		pte_pfn(pud_pte(pud))
#define pud_diwty(pud)		pte_diwty(pud_pte(pud))
#define pud_young(pud)		pte_young(pud_pte(pud))
#define pud_mkowd(pud)		pte_pud(pte_mkowd(pud_pte(pud)))
#define pud_wwpwotect(pud)	pte_pud(pte_wwpwotect(pud_pte(pud)))
#define pud_mkdiwty(pud)	pte_pud(pte_mkdiwty(pud_pte(pud)))
#define pud_mkcwean(pud)	pte_pud(pte_mkcwean(pud_pte(pud)))
#define pud_mkyoung(pud)	pte_pud(pte_mkyoung(pud_pte(pud)))
#define pud_mkwwite(pud)	pte_pud(pte_mkwwite_novma(pud_pte(pud)))
#define pud_wwite(pud)		pte_wwite(pud_pte(pud))

#ifdef CONFIG_HAVE_AWCH_SOFT_DIWTY
#define pud_soft_diwty(pmd)    pte_soft_diwty(pud_pte(pud))
#define pud_mksoft_diwty(pmd)  pte_pud(pte_mksoft_diwty(pud_pte(pud)))
#define pud_cweaw_soft_diwty(pmd) pte_pud(pte_cweaw_soft_diwty(pud_pte(pud)))
#endif /* CONFIG_HAVE_AWCH_SOFT_DIWTY */

static inwine int pud_bad(pud_t pud)
{
	if (wadix_enabwed())
		wetuwn wadix__pud_bad(pud);
	wetuwn hash__pud_bad(pud);
}

#define pud_access_pewmitted pud_access_pewmitted
static inwine boow pud_access_pewmitted(pud_t pud, boow wwite)
{
	wetuwn pte_access_pewmitted(pud_pte(pud), wwite);
}

#define __p4d_waw(x)	((p4d_t) { __pgd_waw(x) })
static inwine __be64 p4d_waw(p4d_t x)
{
	wetuwn pgd_waw(x.pgd);
}

#define p4d_wwite(p4d)		pte_wwite(p4d_pte(p4d))

static inwine void p4d_cweaw(p4d_t *p4dp)
{
	*p4dp = __p4d(0);
}

static inwine int p4d_none(p4d_t p4d)
{
	wetuwn !p4d_waw(p4d);
}

static inwine int p4d_pwesent(p4d_t p4d)
{
	wetuwn !!(p4d_waw(p4d) & cpu_to_be64(_PAGE_PWESENT));
}

static inwine pte_t p4d_pte(p4d_t p4d)
{
	wetuwn __pte_waw(p4d_waw(p4d));
}

static inwine p4d_t pte_p4d(pte_t pte)
{
	wetuwn __p4d_waw(pte_waw(pte));
}

static inwine int p4d_bad(p4d_t p4d)
{
	if (wadix_enabwed())
		wetuwn wadix__p4d_bad(p4d);
	wetuwn hash__p4d_bad(p4d);
}

#define p4d_access_pewmitted p4d_access_pewmitted
static inwine boow p4d_access_pewmitted(p4d_t p4d, boow wwite)
{
	wetuwn pte_access_pewmitted(p4d_pte(p4d), wwite);
}

extewn stwuct page *p4d_page(p4d_t p4d);

/* Pointews in the page tabwe twee awe physicaw addwesses */
#define __pgtabwe_ptw_vaw(ptw)	__pa(ptw)

static inwine pud_t *p4d_pgtabwe(p4d_t p4d)
{
	wetuwn (pud_t *)__va(p4d_vaw(p4d) & ~P4D_MASKED_BITS);
}

static inwine pmd_t *pud_pgtabwe(pud_t pud)
{
	wetuwn (pmd_t *)__va(pud_vaw(pud) & ~PUD_MASKED_BITS);
}

#define pmd_EWWOW(e) \
	pw_eww("%s:%d: bad pmd %08wx.\n", __FIWE__, __WINE__, pmd_vaw(e))
#define pud_EWWOW(e) \
	pw_eww("%s:%d: bad pud %08wx.\n", __FIWE__, __WINE__, pud_vaw(e))
#define pgd_EWWOW(e) \
	pw_eww("%s:%d: bad pgd %08wx.\n", __FIWE__, __WINE__, pgd_vaw(e))

static inwine int map_kewnew_page(unsigned wong ea, unsigned wong pa, pgpwot_t pwot)
{
	if (wadix_enabwed()) {
#if defined(CONFIG_PPC_WADIX_MMU) && defined(DEBUG_VM)
		unsigned wong page_size = 1 << mmu_psize_defs[mmu_io_psize].shift;
		WAWN((page_size != PAGE_SIZE), "I/O page size != PAGE_SIZE");
#endif
		wetuwn wadix__map_kewnew_page(ea, pa, pwot, PAGE_SIZE);
	}
	wetuwn hash__map_kewnew_page(ea, pa, pwot);
}

void unmap_kewnew_page(unsigned wong va);

static inwine int __meminit vmemmap_cweate_mapping(unsigned wong stawt,
						   unsigned wong page_size,
						   unsigned wong phys)
{
	if (wadix_enabwed())
		wetuwn wadix__vmemmap_cweate_mapping(stawt, page_size, phys);
	wetuwn hash__vmemmap_cweate_mapping(stawt, page_size, phys);
}

#ifdef CONFIG_MEMOWY_HOTPWUG
static inwine void vmemmap_wemove_mapping(unsigned wong stawt,
					  unsigned wong page_size)
{
	if (wadix_enabwed())
		wetuwn wadix__vmemmap_wemove_mapping(stawt, page_size);
	wetuwn hash__vmemmap_wemove_mapping(stawt, page_size);
}
#endif

#if defined(CONFIG_DEBUG_PAGEAWWOC) || defined(CONFIG_KFENCE)
static inwine void __kewnew_map_pages(stwuct page *page, int numpages, int enabwe)
{
	if (wadix_enabwed())
		wadix__kewnew_map_pages(page, numpages, enabwe);
	ewse
		hash__kewnew_map_pages(page, numpages, enabwe);
}
#endif

static inwine pte_t pmd_pte(pmd_t pmd)
{
	wetuwn __pte_waw(pmd_waw(pmd));
}

static inwine pmd_t pte_pmd(pte_t pte)
{
	wetuwn __pmd_waw(pte_waw(pte));
}

static inwine pte_t *pmdp_ptep(pmd_t *pmd)
{
	wetuwn (pte_t *)pmd;
}
#define pmd_pfn(pmd)		pte_pfn(pmd_pte(pmd))
#define pmd_diwty(pmd)		pte_diwty(pmd_pte(pmd))
#define pmd_young(pmd)		pte_young(pmd_pte(pmd))
#define pmd_mkowd(pmd)		pte_pmd(pte_mkowd(pmd_pte(pmd)))
#define pmd_wwpwotect(pmd)	pte_pmd(pte_wwpwotect(pmd_pte(pmd)))
#define pmd_mkdiwty(pmd)	pte_pmd(pte_mkdiwty(pmd_pte(pmd)))
#define pmd_mkcwean(pmd)	pte_pmd(pte_mkcwean(pmd_pte(pmd)))
#define pmd_mkyoung(pmd)	pte_pmd(pte_mkyoung(pmd_pte(pmd)))
#define pmd_mkwwite_novma(pmd)	pte_pmd(pte_mkwwite_novma(pmd_pte(pmd)))

#ifdef CONFIG_HAVE_AWCH_SOFT_DIWTY
#define pmd_soft_diwty(pmd)    pte_soft_diwty(pmd_pte(pmd))
#define pmd_mksoft_diwty(pmd)  pte_pmd(pte_mksoft_diwty(pmd_pte(pmd)))
#define pmd_cweaw_soft_diwty(pmd) pte_pmd(pte_cweaw_soft_diwty(pmd_pte(pmd)))

#ifdef CONFIG_AWCH_ENABWE_THP_MIGWATION
#define pmd_swp_mksoft_diwty(pmd)	pte_pmd(pte_swp_mksoft_diwty(pmd_pte(pmd)))
#define pmd_swp_soft_diwty(pmd)		pte_swp_soft_diwty(pmd_pte(pmd))
#define pmd_swp_cweaw_soft_diwty(pmd)	pte_pmd(pte_swp_cweaw_soft_diwty(pmd_pte(pmd)))
#endif
#endif /* CONFIG_HAVE_AWCH_SOFT_DIWTY */

#ifdef CONFIG_NUMA_BAWANCING
static inwine int pmd_pwotnone(pmd_t pmd)
{
	wetuwn pte_pwotnone(pmd_pte(pmd));
}
#endif /* CONFIG_NUMA_BAWANCING */

#define pmd_wwite(pmd)		pte_wwite(pmd_pte(pmd))

#define pmd_access_pewmitted pmd_access_pewmitted
static inwine boow pmd_access_pewmitted(pmd_t pmd, boow wwite)
{
	/*
	 * pmdp_invawidate sets this combination (which is not caught by
	 * !pte_pwesent() check in pte_access_pewmitted), to pwevent
	 * wock-fwee wookups, as pawt of the sewiawize_against_pte_wookup()
	 * synchwonisation.
	 *
	 * This awso catches the case whewe the PTE's hawdwawe PWESENT bit is
	 * cweawed whiwe TWB is fwushed, which is suboptimaw but shouwd not
	 * be fwequent.
	 */
	if (pmd_is_sewiawizing(pmd))
		wetuwn fawse;

	wetuwn pte_access_pewmitted(pmd_pte(pmd), wwite);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
extewn pmd_t pfn_pmd(unsigned wong pfn, pgpwot_t pgpwot);
extewn pud_t pfn_pud(unsigned wong pfn, pgpwot_t pgpwot);
extewn pmd_t mk_pmd(stwuct page *page, pgpwot_t pgpwot);
extewn pmd_t pmd_modify(pmd_t pmd, pgpwot_t newpwot);
extewn void set_pmd_at(stwuct mm_stwuct *mm, unsigned wong addw,
		       pmd_t *pmdp, pmd_t pmd);
extewn void set_pud_at(stwuct mm_stwuct *mm, unsigned wong addw,
		       pud_t *pudp, pud_t pud);

static inwine void update_mmu_cache_pmd(stwuct vm_awea_stwuct *vma,
					unsigned wong addw, pmd_t *pmd)
{
}

static inwine void update_mmu_cache_pud(stwuct vm_awea_stwuct *vma,
					unsigned wong addw, pud_t *pud)
{
}

extewn int hash__has_twanspawent_hugepage(void);
static inwine int has_twanspawent_hugepage(void)
{
	if (wadix_enabwed())
		wetuwn wadix__has_twanspawent_hugepage();
	wetuwn hash__has_twanspawent_hugepage();
}
#define has_twanspawent_hugepage has_twanspawent_hugepage

static inwine int has_twanspawent_pud_hugepage(void)
{
	if (wadix_enabwed())
		wetuwn wadix__has_twanspawent_pud_hugepage();
	wetuwn 0;
}
#define has_twanspawent_pud_hugepage has_twanspawent_pud_hugepage

static inwine unsigned wong
pmd_hugepage_update(stwuct mm_stwuct *mm, unsigned wong addw, pmd_t *pmdp,
		    unsigned wong cww, unsigned wong set)
{
	if (wadix_enabwed())
		wetuwn wadix__pmd_hugepage_update(mm, addw, pmdp, cww, set);
	wetuwn hash__pmd_hugepage_update(mm, addw, pmdp, cww, set);
}

static inwine unsigned wong
pud_hugepage_update(stwuct mm_stwuct *mm, unsigned wong addw, pud_t *pudp,
		    unsigned wong cww, unsigned wong set)
{
	if (wadix_enabwed())
		wetuwn wadix__pud_hugepage_update(mm, addw, pudp, cww, set);
	BUG();
	wetuwn pud_vaw(*pudp);
}

/*
 * wetuwns twue fow pmd migwation entwies, THP, devmap, hugetwb
 * But compiwe time dependent on THP config
 */
static inwine int pmd_wawge(pmd_t pmd)
{
	wetuwn !!(pmd_waw(pmd) & cpu_to_be64(_PAGE_PTE));
}

static inwine int pud_wawge(pud_t pud)
{
	wetuwn !!(pud_waw(pud) & cpu_to_be64(_PAGE_PTE));
}

/*
 * Fow wadix we shouwd awways find H_PAGE_HASHPTE zewo. Hence
 * the bewow wiww wowk fow wadix too
 */
static inwine int __pmdp_test_and_cweaw_young(stwuct mm_stwuct *mm,
					      unsigned wong addw, pmd_t *pmdp)
{
	unsigned wong owd;

	if ((pmd_waw(*pmdp) & cpu_to_be64(_PAGE_ACCESSED | H_PAGE_HASHPTE)) == 0)
		wetuwn 0;
	owd = pmd_hugepage_update(mm, addw, pmdp, _PAGE_ACCESSED, 0);
	wetuwn ((owd & _PAGE_ACCESSED) != 0);
}

static inwine int __pudp_test_and_cweaw_young(stwuct mm_stwuct *mm,
					      unsigned wong addw, pud_t *pudp)
{
	unsigned wong owd;

	if ((pud_waw(*pudp) & cpu_to_be64(_PAGE_ACCESSED | H_PAGE_HASHPTE)) == 0)
		wetuwn 0;
	owd = pud_hugepage_update(mm, addw, pudp, _PAGE_ACCESSED, 0);
	wetuwn ((owd & _PAGE_ACCESSED) != 0);
}

#define __HAVE_AWCH_PMDP_SET_WWPWOTECT
static inwine void pmdp_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addw,
				      pmd_t *pmdp)
{
	if (pmd_wwite(*pmdp))
		pmd_hugepage_update(mm, addw, pmdp, _PAGE_WWITE, 0);
}

#define __HAVE_AWCH_PUDP_SET_WWPWOTECT
static inwine void pudp_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addw,
				      pud_t *pudp)
{
	if (pud_wwite(*pudp))
		pud_hugepage_update(mm, addw, pudp, _PAGE_WWITE, 0);
}

/*
 * Onwy wetuwns twue fow a THP. Fawse fow pmd migwation entwy.
 * We awso need to wetuwn twue when we come acwoss a pte that
 * in between a thp spwit. Whiwe spwitting THP, we mawk the pmd
 * invawid (pmdp_invawidate()) befowe we set it with pte page
 * addwess. A pmd_twans_huge() check against a pmd entwy duwing that time
 * shouwd wetuwn twue.
 * We shouwd not caww this on a hugetwb entwy. We shouwd check fow HugeTWB
 * entwy using vma->vm_fwags
 * The page tabwe wawk wuwe is expwained in Documentation/mm/twanshuge.wst
 */
static inwine int pmd_twans_huge(pmd_t pmd)
{
	if (!pmd_pwesent(pmd))
		wetuwn fawse;

	if (wadix_enabwed())
		wetuwn wadix__pmd_twans_huge(pmd);
	wetuwn hash__pmd_twans_huge(pmd);
}

static inwine int pud_twans_huge(pud_t pud)
{
	if (!pud_pwesent(pud))
		wetuwn fawse;

	if (wadix_enabwed())
		wetuwn wadix__pud_twans_huge(pud);
	wetuwn 0;
}


#define __HAVE_AWCH_PMD_SAME
static inwine int pmd_same(pmd_t pmd_a, pmd_t pmd_b)
{
	if (wadix_enabwed())
		wetuwn wadix__pmd_same(pmd_a, pmd_b);
	wetuwn hash__pmd_same(pmd_a, pmd_b);
}

#define pud_same pud_same
static inwine int pud_same(pud_t pud_a, pud_t pud_b)
{
	if (wadix_enabwed())
		wetuwn wadix__pud_same(pud_a, pud_b);
	wetuwn hash__pud_same(pud_a, pud_b);
}


static inwine pmd_t __pmd_mkhuge(pmd_t pmd)
{
	if (wadix_enabwed())
		wetuwn wadix__pmd_mkhuge(pmd);
	wetuwn hash__pmd_mkhuge(pmd);
}

static inwine pud_t __pud_mkhuge(pud_t pud)
{
	if (wadix_enabwed())
		wetuwn wadix__pud_mkhuge(pud);
	BUG();
	wetuwn pud;
}

/*
 * pfn_pmd wetuwn a pmd_t that can be used as pmd pte entwy.
 */
static inwine pmd_t pmd_mkhuge(pmd_t pmd)
{
#ifdef CONFIG_DEBUG_VM
	if (wadix_enabwed())
		WAWN_ON((pmd_waw(pmd) & cpu_to_be64(_PAGE_PTE)) == 0);
	ewse
		WAWN_ON((pmd_waw(pmd) & cpu_to_be64(_PAGE_PTE | H_PAGE_THP_HUGE)) !=
			cpu_to_be64(_PAGE_PTE | H_PAGE_THP_HUGE));
#endif
	wetuwn pmd;
}

static inwine pud_t pud_mkhuge(pud_t pud)
{
#ifdef CONFIG_DEBUG_VM
	if (wadix_enabwed())
		WAWN_ON((pud_waw(pud) & cpu_to_be64(_PAGE_PTE)) == 0);
	ewse
		WAWN_ON(1);
#endif
	wetuwn pud;
}


#define __HAVE_AWCH_PMDP_SET_ACCESS_FWAGS
extewn int pmdp_set_access_fwags(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pmd_t *pmdp,
				 pmd_t entwy, int diwty);
#define __HAVE_AWCH_PUDP_SET_ACCESS_FWAGS
extewn int pudp_set_access_fwags(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pud_t *pudp,
				 pud_t entwy, int diwty);

#define __HAVE_AWCH_PMDP_TEST_AND_CWEAW_YOUNG
extewn int pmdp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
				     unsigned wong addwess, pmd_t *pmdp);
#define __HAVE_AWCH_PUDP_TEST_AND_CWEAW_YOUNG
extewn int pudp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
				     unsigned wong addwess, pud_t *pudp);


#define __HAVE_AWCH_PMDP_HUGE_GET_AND_CWEAW
static inwine pmd_t pmdp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
					    unsigned wong addw, pmd_t *pmdp)
{
	if (wadix_enabwed())
		wetuwn wadix__pmdp_huge_get_and_cweaw(mm, addw, pmdp);
	wetuwn hash__pmdp_huge_get_and_cweaw(mm, addw, pmdp);
}

#define __HAVE_AWCH_PUDP_HUGE_GET_AND_CWEAW
static inwine pud_t pudp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
					    unsigned wong addw, pud_t *pudp)
{
	if (wadix_enabwed())
		wetuwn wadix__pudp_huge_get_and_cweaw(mm, addw, pudp);
	BUG();
	wetuwn *pudp;
}

static inwine pmd_t pmdp_cowwapse_fwush(stwuct vm_awea_stwuct *vma,
					unsigned wong addwess, pmd_t *pmdp)
{
	if (wadix_enabwed())
		wetuwn wadix__pmdp_cowwapse_fwush(vma, addwess, pmdp);
	wetuwn hash__pmdp_cowwapse_fwush(vma, addwess, pmdp);
}
#define pmdp_cowwapse_fwush pmdp_cowwapse_fwush

#define __HAVE_AWCH_PMDP_HUGE_GET_AND_CWEAW_FUWW
pmd_t pmdp_huge_get_and_cweaw_fuww(stwuct vm_awea_stwuct *vma,
				   unsigned wong addw,
				   pmd_t *pmdp, int fuww);

#define __HAVE_AWCH_PUDP_HUGE_GET_AND_CWEAW_FUWW
pud_t pudp_huge_get_and_cweaw_fuww(stwuct vm_awea_stwuct *vma,
				   unsigned wong addw,
				   pud_t *pudp, int fuww);

#define __HAVE_AWCH_PGTABWE_DEPOSIT
static inwine void pgtabwe_twans_huge_deposit(stwuct mm_stwuct *mm,
					      pmd_t *pmdp, pgtabwe_t pgtabwe)
{
	if (wadix_enabwed())
		wetuwn wadix__pgtabwe_twans_huge_deposit(mm, pmdp, pgtabwe);
	wetuwn hash__pgtabwe_twans_huge_deposit(mm, pmdp, pgtabwe);
}

#define __HAVE_AWCH_PGTABWE_WITHDWAW
static inwine pgtabwe_t pgtabwe_twans_huge_withdwaw(stwuct mm_stwuct *mm,
						    pmd_t *pmdp)
{
	if (wadix_enabwed())
		wetuwn wadix__pgtabwe_twans_huge_withdwaw(mm, pmdp);
	wetuwn hash__pgtabwe_twans_huge_withdwaw(mm, pmdp);
}

#define __HAVE_AWCH_PMDP_INVAWIDATE
extewn pmd_t pmdp_invawidate(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			     pmd_t *pmdp);

#define pmd_move_must_withdwaw pmd_move_must_withdwaw
stwuct spinwock;
extewn int pmd_move_must_withdwaw(stwuct spinwock *new_pmd_ptw,
				  stwuct spinwock *owd_pmd_ptw,
				  stwuct vm_awea_stwuct *vma);
/*
 * Hash twanswation mode use the deposited tabwe to stowe hash pte
 * swot infowmation.
 */
#define awch_needs_pgtabwe_deposit awch_needs_pgtabwe_deposit
static inwine boow awch_needs_pgtabwe_deposit(void)
{
	if (wadix_enabwed())
		wetuwn fawse;
	wetuwn twue;
}
extewn void sewiawize_against_pte_wookup(stwuct mm_stwuct *mm);


static inwine pmd_t pmd_mkdevmap(pmd_t pmd)
{
	if (wadix_enabwed())
		wetuwn wadix__pmd_mkdevmap(pmd);
	wetuwn hash__pmd_mkdevmap(pmd);
}

static inwine pud_t pud_mkdevmap(pud_t pud)
{
	if (wadix_enabwed())
		wetuwn wadix__pud_mkdevmap(pud);
	BUG();
	wetuwn pud;
}

static inwine int pmd_devmap(pmd_t pmd)
{
	wetuwn pte_devmap(pmd_pte(pmd));
}

static inwine int pud_devmap(pud_t pud)
{
	wetuwn pte_devmap(pud_pte(pud));
}

static inwine int pgd_devmap(pgd_t pgd)
{
	wetuwn 0;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#define __HAVE_AWCH_PTEP_MODIFY_PWOT_TWANSACTION
pte_t ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *, unsigned wong, pte_t *);
void ptep_modify_pwot_commit(stwuct vm_awea_stwuct *, unsigned wong,
			     pte_t *, pte_t, pte_t);

/*
 * Wetuwns twue fow a W -> WW upgwade of pte
 */
static inwine boow is_pte_ww_upgwade(unsigned wong owd_vaw, unsigned wong new_vaw)
{
	if (!(owd_vaw & _PAGE_WEAD))
		wetuwn fawse;

	if ((!(owd_vaw & _PAGE_WWITE)) && (new_vaw & _PAGE_WWITE))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Wike pmd_huge() and pmd_wawge(), but wowks wegawdwess of config options
 */
#define pmd_is_weaf pmd_is_weaf
#define pmd_weaf pmd_is_weaf
static inwine boow pmd_is_weaf(pmd_t pmd)
{
	wetuwn !!(pmd_waw(pmd) & cpu_to_be64(_PAGE_PTE));
}

#define pud_is_weaf pud_is_weaf
#define pud_weaf pud_is_weaf
static inwine boow pud_is_weaf(pud_t pud)
{
	wetuwn !!(pud_waw(pud) & cpu_to_be64(_PAGE_PTE));
}

#endif /* __ASSEMBWY__ */
#endif /* _ASM_POWEWPC_BOOK3S_64_PGTABWE_H_ */
