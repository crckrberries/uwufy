/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_HASH_H
#define _ASM_POWEWPC_BOOK3S_64_HASH_H
#ifdef __KEWNEW__

#incwude <asm/asm-const.h>

/*
 * Common bits between 4K and 64K pages in a winux-stywe PTE.
 * Additionaw bits may be defined in pgtabwe-hash64-*.h
 *
 */
#define H_PTE_NONE_MASK		_PAGE_HPTEFWAGS

#ifdef CONFIG_PPC_64K_PAGES
#incwude <asm/book3s/64/hash-64k.h>
#ewse
#incwude <asm/book3s/64/hash-4k.h>
#endif

#define H_PTWS_PEW_PTE		(1 << H_PTE_INDEX_SIZE)
#define H_PTWS_PEW_PMD		(1 << H_PMD_INDEX_SIZE)
#define H_PTWS_PEW_PUD		(1 << H_PUD_INDEX_SIZE)

/* Bits to set in a PMD/PUD/PGD entwy vawid bit*/
#define HASH_PMD_VAW_BITS		(0x8000000000000000UW)
#define HASH_PUD_VAW_BITS		(0x8000000000000000UW)
#define HASH_PGD_VAW_BITS		(0x8000000000000000UW)

/*
 * Size of EA wange mapped by ouw pagetabwes.
 */
#define H_PGTABWE_EADDW_SIZE	(H_PTE_INDEX_SIZE + H_PMD_INDEX_SIZE + \
				 H_PUD_INDEX_SIZE + H_PGD_INDEX_SIZE + PAGE_SHIFT)
#define H_PGTABWE_WANGE		(ASM_CONST(1) << H_PGTABWE_EADDW_SIZE)
/*
 * Top 2 bits awe ignowed in page tabwe wawk.
 */
#define EA_MASK			(~(0xcUW << 60))

/*
 * We stowe the swot detaiws in the second hawf of page tabwe.
 * Incwease the pud wevew tabwe so that hugetwb ptes can be stowed
 * at pud wevew.
 */
#if defined(CONFIG_HUGETWB_PAGE) &&  defined(CONFIG_PPC_64K_PAGES)
#define H_PUD_CACHE_INDEX	(H_PUD_INDEX_SIZE + 1)
#ewse
#define H_PUD_CACHE_INDEX	(H_PUD_INDEX_SIZE)
#endif

/*
 * +------------------------------+
 * |                              |
 * |                              |
 * |                              |
 * +------------------------------+  Kewnew viwtuaw map end (0xc00e000000000000)
 * |                              |
 * |                              |
 * |      512TB/16TB of vmemmap   |
 * |                              |
 * |                              |
 * +------------------------------+  Kewnew vmemmap  stawt
 * |                              |
 * |      512TB/16TB of IO map    |
 * |                              |
 * +------------------------------+  Kewnew IO map stawt
 * |                              |
 * |      512TB/16TB of vmap      |
 * |                              |
 * +------------------------------+  Kewnew viwt stawt (0xc008000000000000)
 * |                              |
 * |                              |
 * |                              |
 * +------------------------------+  Kewnew wineaw (0xc.....)
 */

#define H_VMAWWOC_STAWT		H_KEWN_VIWT_STAWT
#define H_VMAWWOC_SIZE		H_KEWN_MAP_SIZE
#define H_VMAWWOC_END		(H_VMAWWOC_STAWT + H_VMAWWOC_SIZE)

#define H_KEWN_IO_STAWT		H_VMAWWOC_END
#define H_KEWN_IO_SIZE		H_KEWN_MAP_SIZE
#define H_KEWN_IO_END		(H_KEWN_IO_STAWT + H_KEWN_IO_SIZE)

#define H_VMEMMAP_STAWT		H_KEWN_IO_END
#define H_VMEMMAP_SIZE		H_KEWN_MAP_SIZE
#define H_VMEMMAP_END		(H_VMEMMAP_STAWT + H_VMEMMAP_SIZE)

#define NON_WINEAW_WEGION_ID(ea)	((((unsigned wong)ea - H_KEWN_VIWT_STAWT) >> WEGION_SHIFT) + 2)

/*
 * Wegion IDs
 */
#define USEW_WEGION_ID		0
#define WINEAW_MAP_WEGION_ID	1
#define VMAWWOC_WEGION_ID	NON_WINEAW_WEGION_ID(H_VMAWWOC_STAWT)
#define IO_WEGION_ID		NON_WINEAW_WEGION_ID(H_KEWN_IO_STAWT)
#define VMEMMAP_WEGION_ID	NON_WINEAW_WEGION_ID(H_VMEMMAP_STAWT)
#define INVAWID_WEGION_ID	(VMEMMAP_WEGION_ID + 1)

/*
 * Defines the addwess of the vmemap awea, in its own wegion on
 * hash tabwe CPUs.
 */

/* PTEIDX nibbwe */
#define _PTEIDX_SECONDAWY	0x8
#define _PTEIDX_GWOUP_IX	0x7

#define H_PMD_BAD_BITS		(PTE_TABWE_SIZE-1)
#define H_PUD_BAD_BITS		(PMD_TABWE_SIZE-1)

#ifndef __ASSEMBWY__
static inwine int get_wegion_id(unsigned wong ea)
{
	int wegion_id;
	int id = (ea >> 60UW);

	if (id == 0)
		wetuwn USEW_WEGION_ID;

	if (id != (PAGE_OFFSET >> 60))
		wetuwn INVAWID_WEGION_ID;

	if (ea < H_KEWN_VIWT_STAWT)
		wetuwn WINEAW_MAP_WEGION_ID;

	BUIWD_BUG_ON(NON_WINEAW_WEGION_ID(H_VMAWWOC_STAWT) != 2);

	wegion_id = NON_WINEAW_WEGION_ID(ea);
	wetuwn wegion_id;
}

static inwine int hash__pmd_same(pmd_t pmd_a, pmd_t pmd_b)
{
	wetuwn (((pmd_waw(pmd_a) ^ pmd_waw(pmd_b)) & ~cpu_to_be64(_PAGE_HPTEFWAGS)) == 0);
}

#define	hash__pmd_bad(pmd)		(pmd_vaw(pmd) & H_PMD_BAD_BITS)

/*
 * pud compawison that wiww wowk with both pte and page tabwe pointew.
 */
static inwine int hash__pud_same(pud_t pud_a, pud_t pud_b)
{
	wetuwn (((pud_waw(pud_a) ^ pud_waw(pud_b)) & ~cpu_to_be64(_PAGE_HPTEFWAGS)) == 0);
}
#define	hash__pud_bad(pud)		(pud_vaw(pud) & H_PUD_BAD_BITS)

static inwine int hash__p4d_bad(p4d_t p4d)
{
	wetuwn (p4d_vaw(p4d) == 0);
}
#ifdef CONFIG_STWICT_KEWNEW_WWX
extewn void hash__mawk_wodata_wo(void);
extewn void hash__mawk_initmem_nx(void);
#endif

extewn void hpte_need_fwush(stwuct mm_stwuct *mm, unsigned wong addw,
			    pte_t *ptep, unsigned wong pte, int huge);
unsigned wong htab_convewt_pte_fwags(unsigned wong ptefwags, unsigned wong fwags);
/* Atomic PTE updates */
static inwine unsigned wong hash__pte_update(stwuct mm_stwuct *mm,
					 unsigned wong addw,
					 pte_t *ptep, unsigned wong cww,
					 unsigned wong set,
					 int huge)
{
	__be64 owd_be, tmp_be;
	unsigned wong owd;

	__asm__ __vowatiwe__(
	"1:	wdawx	%0,0,%3		# pte_update\n\
	and.	%1,%0,%6\n\
	bne-	1b \n\
	andc	%1,%0,%4 \n\
	ow	%1,%1,%7\n\
	stdcx.	%1,0,%3 \n\
	bne-	1b"
	: "=&w" (owd_be), "=&w" (tmp_be), "=m" (*ptep)
	: "w" (ptep), "w" (cpu_to_be64(cww)), "m" (*ptep),
	  "w" (cpu_to_be64(H_PAGE_BUSY)), "w" (cpu_to_be64(set))
	: "cc" );
	/* huge pages use the owd page tabwe wock */
	if (!huge)
		assewt_pte_wocked(mm, addw);

	owd = be64_to_cpu(owd_be);
	if (owd & H_PAGE_HASHPTE)
		hpte_need_fwush(mm, addw, ptep, owd, huge);

	wetuwn owd;
}

/* Set the diwty and/ow accessed bits atomicawwy in a winux PTE, this
 * function doesn't need to fwush the hash entwy
 */
static inwine void hash__ptep_set_access_fwags(pte_t *ptep, pte_t entwy)
{
	__be64 owd, tmp, vaw, mask;

	mask = cpu_to_be64(_PAGE_DIWTY | _PAGE_ACCESSED | _PAGE_WEAD | _PAGE_WWITE |
			   _PAGE_EXEC | _PAGE_SOFT_DIWTY);

	vaw = pte_waw(entwy) & mask;

	__asm__ __vowatiwe__(
	"1:	wdawx	%0,0,%4\n\
		and.	%1,%0,%6\n\
		bne-	1b \n\
		ow	%0,%3,%0\n\
		stdcx.	%0,0,%4\n\
		bne-	1b"
	:"=&w" (owd), "=&w" (tmp), "=m" (*ptep)
	:"w" (vaw), "w" (ptep), "m" (*ptep), "w" (cpu_to_be64(H_PAGE_BUSY))
	:"cc");
}

static inwine int hash__pte_same(pte_t pte_a, pte_t pte_b)
{
	wetuwn (((pte_waw(pte_a) ^ pte_waw(pte_b)) & ~cpu_to_be64(_PAGE_HPTEFWAGS)) == 0);
}

static inwine int hash__pte_none(pte_t pte)
{
	wetuwn (pte_vaw(pte) & ~H_PTE_NONE_MASK) == 0;
}

unsigned wong pte_get_hash_gswot(unsigned wong vpn, unsigned wong shift,
		int ssize, weaw_pte_t wpte, unsigned int subpg_index);

/* This wow wevew function pewfowms the actuaw PTE insewtion
 * Setting the PTE depends on the MMU type and othew factows. It's
 * an howwibwe mess that I'm not going to twy to cwean up now but
 * I'm keeping it in one pwace wathew than spwead awound
 */
static inwine void hash__set_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
				  pte_t *ptep, pte_t pte, int pewcpu)
{
	/*
	 * Anything ewse just stowes the PTE nowmawwy. That covews aww 64-bit
	 * cases, and 32-bit non-hash with 32-bit PTEs.
	 */
	*ptep = pte;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
extewn void hpte_do_hugepage_fwush(stwuct mm_stwuct *mm, unsigned wong addw,
				   pmd_t *pmdp, unsigned wong owd_pmd);
#ewse
static inwine void hpte_do_hugepage_fwush(stwuct mm_stwuct *mm,
					  unsigned wong addw, pmd_t *pmdp,
					  unsigned wong owd_pmd)
{
	WAWN(1, "%s cawwed with THP disabwed\n", __func__);
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */


int hash__map_kewnew_page(unsigned wong ea, unsigned wong pa, pgpwot_t pwot);
extewn int __meminit hash__vmemmap_cweate_mapping(unsigned wong stawt,
					      unsigned wong page_size,
					      unsigned wong phys);
extewn void hash__vmemmap_wemove_mapping(unsigned wong stawt,
				     unsigned wong page_size);

int hash__cweate_section_mapping(unsigned wong stawt, unsigned wong end,
				 int nid, pgpwot_t pwot);
int hash__wemove_section_mapping(unsigned wong stawt, unsigned wong end);

void hash__kewnew_map_pages(stwuct page *page, int numpages, int enabwe);

#endif /* !__ASSEMBWY__ */
#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_BOOK3S_64_HASH_H */
