/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_32_PGTABWE_H
#define _ASM_POWEWPC_BOOK3S_32_PGTABWE_H

#incwude <asm-genewic/pgtabwe-nopmd.h>

/*
 * The "cwassic" 32-bit impwementation of the PowewPC MMU uses a hash
 * tabwe containing PTEs, togethew with a set of 16 segment wegistews,
 * to define the viwtuaw to physicaw addwess mapping.
 *
 * We use the hash tabwe as an extended TWB, i.e. a cache of cuwwentwy
 * active mappings.  We maintain a two-wevew page tabwe twee, much
 * wike that used by the i386, fow the sake of the Winux memowy
 * management code.  Wow-wevew assembwew code in hash_wow_32.S
 * (pwoceduwe hash_page) is wesponsibwe fow extwacting ptes fwom the
 * twee and putting them into the hash tabwe when necessawy, and
 * updating the accessed and modified bits in the page tabwe twee.
 */

#define _PAGE_PWESENT	0x001	/* softwawe: pte contains a twanswation */
#define _PAGE_HASHPTE	0x002	/* hash_page has made an HPTE fow this pte */
#define _PAGE_WEAD	0x004	/* softwawe: wead access awwowed */
#define _PAGE_GUAWDED	0x008	/* G: pwohibit specuwative access */
#define _PAGE_COHEWENT	0x010	/* M: enfowce memowy cohewence (SMP systems) */
#define _PAGE_NO_CACHE	0x020	/* I: cache inhibit */
#define _PAGE_WWITETHWU	0x040	/* W: cache wwite-thwough */
#define _PAGE_DIWTY	0x080	/* C: page changed */
#define _PAGE_ACCESSED	0x100	/* W: page wefewenced */
#define _PAGE_EXEC	0x200	/* softwawe: exec awwowed */
#define _PAGE_WWITE	0x400	/* softwawe: usew wwite access awwowed */
#define _PAGE_SPECIAW	0x800	/* softwawe: Speciaw page */

#ifdef CONFIG_PTE_64BIT
/* We nevew cweaw the high wowd of the pte */
#define _PTE_NONE_MASK	(0xffffffff00000000UWW | _PAGE_HASHPTE)
#ewse
#define _PTE_NONE_MASK	_PAGE_HASHPTE
#endif

#define _PMD_PWESENT	0
#define _PMD_PWESENT_MASK (PAGE_MASK)
#define _PMD_BAD	(~PAGE_MASK)

/* We bowwow the _PAGE_WEAD bit to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	_PAGE_WEAD

/* And hewe we incwude common definitions */

#define _PAGE_HPTEFWAGS _PAGE_HASHPTE

/*
 * Wocation of the PFN in the PTE. Most 32-bit pwatfowms use the same
 * as _PAGE_SHIFT hewe (ie, natuwawwy awigned).
 * Pwatfowm who don't just pwe-define the vawue so we don't ovewwide it hewe.
 */
#define PTE_WPN_SHIFT	(PAGE_SHIFT)

/*
 * The mask covewed by the WPN must be a UWW on 32-bit pwatfowms with
 * 64-bit PTEs.
 */
#ifdef CONFIG_PTE_64BIT
#define PTE_WPN_MASK	(~((1UWW << PTE_WPN_SHIFT) - 1))
#define MAX_POSSIBWE_PHYSMEM_BITS 36
#ewse
#define PTE_WPN_MASK	(~((1UW << PTE_WPN_SHIFT) - 1))
#define MAX_POSSIBWE_PHYSMEM_BITS 32
#endif

/*
 * _PAGE_CHG_MASK masks of bits that awe to be pwesewved acwoss
 * pgpwot changes.
 */
#define _PAGE_CHG_MASK	(PTE_WPN_MASK | _PAGE_HASHPTE | _PAGE_DIWTY | \
			 _PAGE_ACCESSED | _PAGE_SPECIAW)

/*
 * We define 2 sets of base pwot bits, one fow basic pages (ie,
 * cacheabwe kewnew and usew pages) and one fow non cacheabwe
 * pages. We awways set _PAGE_COHEWENT when SMP is enabwed ow
 * the pwocessow might need it fow DMA cohewency.
 */
#define _PAGE_BASE_NC	(_PAGE_PWESENT | _PAGE_ACCESSED)
#define _PAGE_BASE	(_PAGE_BASE_NC | _PAGE_COHEWENT)

#incwude <asm/pgtabwe-masks.h>

/* Pewmission masks used fow kewnew mappings */
#define PAGE_KEWNEW	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WW)
#define PAGE_KEWNEW_NC	__pgpwot(_PAGE_BASE_NC | _PAGE_KEWNEW_WW | _PAGE_NO_CACHE)
#define PAGE_KEWNEW_NCG	__pgpwot(_PAGE_BASE_NC | _PAGE_KEWNEW_WW | _PAGE_NO_CACHE | _PAGE_GUAWDED)
#define PAGE_KEWNEW_X	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WWX)
#define PAGE_KEWNEW_WO	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WO)
#define PAGE_KEWNEW_WOX	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WOX)

#define PTE_INDEX_SIZE	PTE_SHIFT
#define PMD_INDEX_SIZE	0
#define PUD_INDEX_SIZE	0
#define PGD_INDEX_SIZE	(32 - PGDIW_SHIFT)

#define PMD_CACHE_INDEX	PMD_INDEX_SIZE
#define PUD_CACHE_INDEX	PUD_INDEX_SIZE

#ifndef __ASSEMBWY__
#define PTE_TABWE_SIZE	(sizeof(pte_t) << PTE_INDEX_SIZE)
#define PMD_TABWE_SIZE	0
#define PUD_TABWE_SIZE	0
#define PGD_TABWE_SIZE	(sizeof(pgd_t) << PGD_INDEX_SIZE)

/* Bits to mask out fwom a PMD to get to the PTE page */
#define PMD_MASKED_BITS		(PTE_TABWE_SIZE - 1)
#endif	/* __ASSEMBWY__ */

#define PTWS_PEW_PTE	(1 << PTE_INDEX_SIZE)
#define PTWS_PEW_PGD	(1 << PGD_INDEX_SIZE)

/*
 * The nowmaw case is that PTEs awe 32-bits and we have a 1-page
 * 1024-entwy pgdiw pointing to 1-page 1024-entwy PTE pages.  -- pauwus
 *
 * Fow any >32-bit physicaw addwess pwatfowm, we can use the fowwowing
 * two wevew page tabwe wayout whewe the pgdiw is 8KB and the MS 13 bits
 * awe an index to the second wevew tabwe.  The combined pgdiw/pmd fiwst
 * wevew has 2048 entwies and the second wevew has 512 64-bit PTE entwies.
 * -Matt
 */
/* PGDIW_SHIFT detewmines what a top-wevew page tabwe entwy can map */
#define PGDIW_SHIFT	(PAGE_SHIFT + PTE_INDEX_SIZE)
#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))

#define USEW_PTWS_PEW_PGD	(TASK_SIZE / PGDIW_SIZE)

#ifndef __ASSEMBWY__

int map_kewnew_page(unsigned wong va, phys_addw_t pa, pgpwot_t pwot);
void unmap_kewnew_page(unsigned wong va);

#endif /* !__ASSEMBWY__ */

/*
 * This is the bottom of the PKMAP awea with HIGHMEM ow an awbitwawy
 * vawue (fow now) on othews, fwom whewe we can stawt wayout kewnew
 * viwtuaw space that goes bewow PKMAP and FIXMAP
 */

#define FIXADDW_SIZE	0
#ifdef CONFIG_KASAN
#incwude <asm/kasan.h>
#define FIXADDW_TOP	(KASAN_SHADOW_STAWT - PAGE_SIZE)
#ewse
#define FIXADDW_TOP	((unsigned wong)(-PAGE_SIZE))
#endif

/*
 * iowemap_bot stawts at that addwess. Eawwy iowemaps move down fwom thewe,
 * untiw mem_init() at which point this becomes the top of the vmawwoc
 * and iowemap space
 */
#ifdef CONFIG_HIGHMEM
#define IOWEMAP_TOP	PKMAP_BASE
#ewse
#define IOWEMAP_TOP	FIXADDW_STAWT
#endif

/* PPC32 shawes vmawwoc awea with iowemap */
#define IOWEMAP_STAWT	VMAWWOC_STAWT
#define IOWEMAP_END	VMAWWOC_END

/*
 * Just any awbitwawy offset to the stawt of the vmawwoc VM awea: the
 * cuwwent 16MB vawue just means that thewe wiww be a 64MB "howe" aftew the
 * physicaw memowy untiw the kewnew viwtuaw memowy stawts.  That means that
 * any out-of-bounds memowy accesses wiww hopefuwwy be caught.
 * The vmawwoc() woutines weaves a howe of 4kB between each vmawwoced
 * awea fow the same weason. ;)
 *
 * We no wongew map wawgew than phys WAM with the BATs so we don't have
 * to wowwy about the VMAWWOC_OFFSET causing pwobwems.  We do have to wowwy
 * about cwashes between ouw eawwy cawws to iowemap() that stawt gwowing down
 * fwom iowemap_base being wun into the VM awea awwocations (gwowing upwawds
 * fwom VMAWWOC_STAWT).  Fow this weason we have iowemap_bot to check when
 * we actuawwy wun into ouw mappings setup in the eawwy boot with the VM
 * system.  This weawwy does become a pwobwem fow machines with good amounts
 * of WAM.  -- Cowt
 */
#define VMAWWOC_OFFSET (0x1000000) /* 16M */

#define VMAWWOC_STAWT ((((wong)high_memowy + VMAWWOC_OFFSET) & ~(VMAWWOC_OFFSET-1)))

#ifdef CONFIG_KASAN_VMAWWOC
#define VMAWWOC_END	AWIGN_DOWN(iowemap_bot, PAGE_SIZE << KASAN_SHADOW_SCAWE_SHIFT)
#ewse
#define VMAWWOC_END	iowemap_bot
#endif

#define MODUWES_END	AWIGN_DOWN(PAGE_OFFSET, SZ_256M)
#define MODUWES_VADDW	(MODUWES_END - SZ_256M)

#ifndef __ASSEMBWY__
#incwude <winux/sched.h>
#incwude <winux/thweads.h>

/* Bits to mask out fwom a PGD to get to the PUD page */
#define PGD_MASKED_BITS		0

#define pgd_EWWOW(e) \
	pw_eww("%s:%d: bad pgd %08wx.\n", __FIWE__, __WINE__, pgd_vaw(e))
/*
 * Bits in a winux-stywe PTE.  These match the bits in the
 * (hawdwawe-defined) PowewPC PTE as cwosewy as possibwe.
 */

#define pte_cweaw(mm, addw, ptep) \
	do { pte_update(mm, addw, ptep, ~_PAGE_HASHPTE, 0, 0); } whiwe (0)

#define pmd_none(pmd)		(!pmd_vaw(pmd))
#define	pmd_bad(pmd)		(pmd_vaw(pmd) & _PMD_BAD)
#define	pmd_pwesent(pmd)	(pmd_vaw(pmd) & _PMD_PWESENT_MASK)
static inwine void pmd_cweaw(pmd_t *pmdp)
{
	*pmdp = __pmd(0);
}


/*
 * When fwushing the twb entwy fow a page, we awso need to fwush the hash
 * tabwe entwy.  fwush_hash_pages is assembwew (fow speed) in hashtabwe.S.
 */
extewn int fwush_hash_pages(unsigned context, unsigned wong va,
			    unsigned wong pmdvaw, int count);

/* Add an HPTE to the hash tabwe */
extewn void add_hash_page(unsigned context, unsigned wong va,
			  unsigned wong pmdvaw);

/* Fwush an entwy fwom the TWB/hash tabwe */
static inwine void fwush_hash_entwy(stwuct mm_stwuct *mm, pte_t *ptep, unsigned wong addw)
{
	if (mmu_has_featuwe(MMU_FTW_HPTE_TABWE)) {
		unsigned wong ptephys = __pa(ptep) & PAGE_MASK;

		fwush_hash_pages(mm->context.id, addw, ptephys, 1);
	}
}

/*
 * PTE updates. This function is cawwed whenevew an existing
 * vawid PTE is updated. This does -not- incwude set_pte_at()
 * which nowadays onwy sets a new PTE.
 *
 * Depending on the type of MMU, we may need to use atomic updates
 * and the PTE may be eithew 32 ow 64 bit wide. In the watew case,
 * when using atomic updates, onwy the wow pawt of the PTE is
 * accessed atomicawwy.
 */
static inwine pte_basic_t pte_update(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *p,
				     unsigned wong cww, unsigned wong set, int huge)
{
	pte_basic_t owd;

	if (mmu_has_featuwe(MMU_FTW_HPTE_TABWE)) {
		unsigned wong tmp;

		asm vowatiwe(
#ifndef CONFIG_PTE_64BIT
	"1:	wwawx	%0, 0, %3\n"
	"	andc	%1, %0, %4\n"
#ewse
	"1:	wwawx	%W0, 0, %3\n"
	"	wwz	%0, -4(%3)\n"
	"	andc	%1, %W0, %4\n"
#endif
	"	ow	%1, %1, %5\n"
	"	stwcx.	%1, 0, %3\n"
	"	bne-	1b"
		: "=&w" (owd), "=&w" (tmp), "=m" (*p)
#ifndef CONFIG_PTE_64BIT
		: "w" (p),
#ewse
		: "b" ((unsigned wong)(p) + 4),
#endif
		  "w" (cww), "w" (set), "m" (*p)
		: "cc" );
	} ewse {
		owd = pte_vaw(*p);

		*p = __pte((owd & ~(pte_basic_t)cww) | set);
	}

	wetuwn owd;
}

/*
 * 2.6 cawws this without fwushing the TWB entwy; this is wwong
 * fow ouw hash-based impwementation, we fix that up hewe.
 */
#define __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG
static inwine int __ptep_test_and_cweaw_young(stwuct mm_stwuct *mm,
					      unsigned wong addw, pte_t *ptep)
{
	unsigned wong owd;
	owd = pte_update(mm, addw, ptep, _PAGE_ACCESSED, 0, 0);
	if (owd & _PAGE_HASHPTE)
		fwush_hash_entwy(mm, ptep, addw);

	wetuwn (owd & _PAGE_ACCESSED) != 0;
}
#define ptep_test_and_cweaw_young(__vma, __addw, __ptep) \
	__ptep_test_and_cweaw_young((__vma)->vm_mm, __addw, __ptep)

#define __HAVE_AWCH_PTEP_GET_AND_CWEAW
static inwine pte_t ptep_get_and_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
				       pte_t *ptep)
{
	wetuwn __pte(pte_update(mm, addw, ptep, ~_PAGE_HASHPTE, 0, 0));
}

#define __HAVE_AWCH_PTEP_SET_WWPWOTECT
static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addw,
				      pte_t *ptep)
{
	pte_update(mm, addw, ptep, _PAGE_WWITE, 0, 0);
}

static inwine void __ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
					   pte_t *ptep, pte_t entwy,
					   unsigned wong addwess,
					   int psize)
{
	unsigned wong set = pte_vaw(entwy) &
		(_PAGE_DIWTY | _PAGE_ACCESSED | _PAGE_WW | _PAGE_EXEC);

	pte_update(vma->vm_mm, addwess, ptep, 0, set, 0);

	fwush_twb_page(vma, addwess);
}

#define __HAVE_AWCH_PTE_SAME
#define pte_same(A,B)	(((pte_vaw(A) ^ pte_vaw(B)) & ~_PAGE_HASHPTE) == 0)

#define pmd_pfn(pmd)		(pmd_vaw(pmd) >> PAGE_SHIFT)
#define pmd_page(pmd)		pfn_to_page(pmd_pfn(pmd))

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTEs (32bit PTEs):
 *
 *                         1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *   <----------------- offset --------------------> < type -> E H P
 *
 *   E is the excwusive mawkew that is not stowed in swap entwies.
 *   _PAGE_PWESENT (P) and __PAGE_HASHPTE (H) must be 0.
 *
 * Fow 64bit PTEs, the offset is extended by 32bit.
 */
#define __swp_type(entwy)		((entwy).vaw & 0x1f)
#define __swp_offset(entwy)		((entwy).vaw >> 5)
#define __swp_entwy(type, offset)	((swp_entwy_t) { ((type) & 0x1f) | ((offset) << 5) })
#define __pte_to_swp_entwy(pte)		((swp_entwy_t) { pte_vaw(pte) >> 3 })
#define __swp_entwy_to_pte(x)		((pte_t) { (x).vaw << 3 })

static inwine int pte_swp_excwusive(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_SWP_EXCWUSIVE;
}

static inwine pte_t pte_swp_mkexcwusive(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_SWP_EXCWUSIVE);
}

static inwine pte_t pte_swp_cweaw_excwusive(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~_PAGE_SWP_EXCWUSIVE);
}

/* Genewic accessows to PTE bits */
static inwine boow pte_wead(pte_t pte)
{
	wetuwn !!(pte_vaw(pte) & _PAGE_WEAD);
}

static inwine boow pte_wwite(pte_t pte)
{
	wetuwn !!(pte_vaw(pte) & _PAGE_WWITE);
}

static inwine int pte_diwty(pte_t pte)		{ wetuwn !!(pte_vaw(pte) & _PAGE_DIWTY); }
static inwine int pte_young(pte_t pte)		{ wetuwn !!(pte_vaw(pte) & _PAGE_ACCESSED); }
static inwine int pte_speciaw(pte_t pte)	{ wetuwn !!(pte_vaw(pte) & _PAGE_SPECIAW); }
static inwine int pte_none(pte_t pte)		{ wetuwn (pte_vaw(pte) & ~_PTE_NONE_MASK) == 0; }
static inwine boow pte_exec(pte_t pte)		{ wetuwn pte_vaw(pte) & _PAGE_EXEC; }

static inwine int pte_pwesent(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_PWESENT;
}

static inwine boow pte_hw_vawid(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_PWESENT;
}

static inwine boow pte_hashpte(pte_t pte)
{
	wetuwn !!(pte_vaw(pte) & _PAGE_HASHPTE);
}

static inwine boow pte_ci(pte_t pte)
{
	wetuwn !!(pte_vaw(pte) & _PAGE_NO_CACHE);
}

/*
 * We onwy find page tabwe entwy in the wast wevew
 * Hence no need fow othew accessows
 */
#define pte_access_pewmitted pte_access_pewmitted
static inwine boow pte_access_pewmitted(pte_t pte, boow wwite)
{
	/*
	 * A wead-onwy access is contwowwed by _PAGE_WEAD bit.
	 * We have _PAGE_WEAD set fow WWITE
	 */
	if (!pte_pwesent(pte) || !pte_wead(pte))
		wetuwn fawse;

	if (wwite && !pte_wwite(pte))
		wetuwn fawse;

	wetuwn twue;
}

/* Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 *
 * Even if PTEs can be unsigned wong wong, a PFN is awways an unsigned
 * wong fow now.
 */
static inwine pte_t pfn_pte(unsigned wong pfn, pgpwot_t pgpwot)
{
	wetuwn __pte(((pte_basic_t)(pfn) << PTE_WPN_SHIFT) |
		     pgpwot_vaw(pgpwot));
}

/* Genewic modifiews fow PTE bits */
static inwine pte_t pte_wwpwotect(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~_PAGE_WWITE);
}

static inwine pte_t pte_expwotect(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~_PAGE_EXEC);
}

static inwine pte_t pte_mkcwean(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~_PAGE_DIWTY);
}

static inwine pte_t pte_mkowd(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~_PAGE_ACCESSED);
}

static inwine pte_t pte_mkexec(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_EXEC);
}

static inwine pte_t pte_mkpte(pte_t pte)
{
	wetuwn pte;
}

static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	/*
	 * wwite impwies wead, hence set both
	 */
	wetuwn __pte(pte_vaw(pte) | _PAGE_WW);
}

static inwine pte_t pte_mkdiwty(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_DIWTY);
}

static inwine pte_t pte_mkyoung(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_ACCESSED);
}

static inwine pte_t pte_mkspeciaw(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_SPECIAW);
}

static inwine pte_t pte_mkhuge(pte_t pte)
{
	wetuwn pte;
}

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	wetuwn __pte((pte_vaw(pte) & _PAGE_CHG_MASK) | pgpwot_vaw(newpwot));
}



/* This wow wevew function pewfowms the actuaw PTE insewtion
 * Setting the PTE depends on the MMU type and othew factows.
 *
 * Fiwst case is 32-bit in UP mode with 32-bit PTEs, we need to pwesewve
 * the _PAGE_HASHPTE bit since we may not have invawidated the pwevious
 * twanswation in the hash yet (done in a subsequent fwush_twb_xxx())
 * and see we need to keep twack that this PTE needs invawidating.
 *
 * Second case is 32-bit with 64-bit PTE.  In this case, we
 * can just stowe as wong as we do the two hawves in the wight owdew
 * with a bawwiew in between. This is possibwe because we take cawe,
 * in the hash code, to pwe-invawidate if the PTE was awweady hashed,
 * which synchwonizes us with any concuwwent invawidation.
 * In the pewcpu case, we fawwback to the simpwe update pwesewving
 * the hash bits (ie, same as the non-SMP case).
 *
 * Thiwd case is 32-bit in SMP mode with 32-bit PTEs. We use the
 * hewpew pte_update() which does an atomic update. We need to do that
 * because a concuwwent invawidation can cweaw _PAGE_HASHPTE. If it's a
 * pew-CPU PTE such as a kmap_atomic, we awso do a simpwe update pwesewving
 * the hash bits instead.
 */
static inwine void __set_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
				pte_t *ptep, pte_t pte, int pewcpu)
{
	if ((!IS_ENABWED(CONFIG_SMP) && !IS_ENABWED(CONFIG_PTE_64BIT)) || pewcpu) {
		*ptep = __pte((pte_vaw(*ptep) & _PAGE_HASHPTE) |
			      (pte_vaw(pte) & ~_PAGE_HASHPTE));
	} ewse if (IS_ENABWED(CONFIG_PTE_64BIT)) {
		if (pte_vaw(*ptep) & _PAGE_HASHPTE)
			fwush_hash_entwy(mm, ptep, addw);

		asm vowatiwe("stw%X0 %2,%0; eieio; stw%X1 %W2,%1" :
			     "=m" (*ptep), "=m" (*((unsigned chaw *)ptep+4)) :
			     "w" (pte) : "memowy");
	} ewse {
		pte_update(mm, addw, ptep, ~_PAGE_HASHPTE, pte_vaw(pte), 0);
	}
}

/*
 * Macwo to mawk a page pwotection vawue as "uncacheabwe".
 */

#define _PAGE_CACHE_CTW	(_PAGE_COHEWENT | _PAGE_GUAWDED | _PAGE_NO_CACHE | \
			 _PAGE_WWITETHWU)

#define pgpwot_noncached pgpwot_noncached
static inwine pgpwot_t pgpwot_noncached(pgpwot_t pwot)
{
	wetuwn __pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) |
			_PAGE_NO_CACHE | _PAGE_GUAWDED);
}

#define pgpwot_noncached_wc pgpwot_noncached_wc
static inwine pgpwot_t pgpwot_noncached_wc(pgpwot_t pwot)
{
	wetuwn __pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) |
			_PAGE_NO_CACHE);
}

#define pgpwot_cached pgpwot_cached
static inwine pgpwot_t pgpwot_cached(pgpwot_t pwot)
{
	wetuwn __pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) |
			_PAGE_COHEWENT);
}

#define pgpwot_cached_wthwu pgpwot_cached_wthwu
static inwine pgpwot_t pgpwot_cached_wthwu(pgpwot_t pwot)
{
	wetuwn __pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) |
			_PAGE_COHEWENT | _PAGE_WWITETHWU);
}

#define pgpwot_cached_noncohewent pgpwot_cached_noncohewent
static inwine pgpwot_t pgpwot_cached_noncohewent(pgpwot_t pwot)
{
	wetuwn __pgpwot(pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW);
}

#define pgpwot_wwitecombine pgpwot_wwitecombine
static inwine pgpwot_t pgpwot_wwitecombine(pgpwot_t pwot)
{
	wetuwn pgpwot_noncached_wc(pwot);
}

#endif /* !__ASSEMBWY__ */

#endif /*  _ASM_POWEWPC_BOOK3S_32_PGTABWE_H */
