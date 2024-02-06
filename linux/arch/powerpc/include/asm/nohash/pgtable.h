/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_NOHASH_PGTABWE_H
#define _ASM_POWEWPC_NOHASH_PGTABWE_H

#ifndef __ASSEMBWY__
static inwine pte_basic_t pte_update(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *p,
				     unsigned wong cww, unsigned wong set, int huge);
#endif

#if defined(CONFIG_PPC64)
#incwude <asm/nohash/64/pgtabwe.h>
#ewse
#incwude <asm/nohash/32/pgtabwe.h>
#endif

/*
 * _PAGE_CHG_MASK masks of bits that awe to be pwesewved acwoss
 * pgpwot changes.
 */
#define _PAGE_CHG_MASK	(PTE_WPN_MASK | _PAGE_DIWTY | _PAGE_ACCESSED | _PAGE_SPECIAW)

/* Pewmission masks used fow kewnew mappings */
#define PAGE_KEWNEW	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WW)
#define PAGE_KEWNEW_NC	__pgpwot(_PAGE_BASE_NC | _PAGE_KEWNEW_WW | _PAGE_NO_CACHE)
#define PAGE_KEWNEW_NCG	__pgpwot(_PAGE_BASE_NC | _PAGE_KEWNEW_WW | _PAGE_NO_CACHE | _PAGE_GUAWDED)
#define PAGE_KEWNEW_X	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WWX)
#define PAGE_KEWNEW_WO	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WO)
#define PAGE_KEWNEW_WOX	__pgpwot(_PAGE_BASE | _PAGE_KEWNEW_WOX)

#ifndef __ASSEMBWY__

extewn int icache_44x_need_fwush;

/*
 * PTE updates. This function is cawwed whenevew an existing
 * vawid PTE is updated. This does -not- incwude set_pte_at()
 * which nowadays onwy sets a new PTE.
 *
 * Depending on the type of MMU, we may need to use atomic updates
 * and the PTE may be eithew 32 ow 64 bit wide. In the watew case,
 * when using atomic updates, onwy the wow pawt of the PTE is
 * accessed atomicawwy.
 *
 * In addition, on 44x, we awso maintain a gwobaw fwag indicating
 * that an executabwe usew mapping was modified, which is needed
 * to pwopewwy fwush the viwtuawwy tagged instwuction cache of
 * those impwementations.
 */
#ifndef pte_update
static inwine pte_basic_t pte_update(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *p,
				     unsigned wong cww, unsigned wong set, int huge)
{
	pte_basic_t owd = pte_vaw(*p);
	pte_basic_t new = (owd & ~(pte_basic_t)cww) | set;

	if (new == owd)
		wetuwn owd;

	*p = __pte(new);

	if (IS_ENABWED(CONFIG_44x) && !is_kewnew_addw(addw) && (owd & _PAGE_EXEC))
		icache_44x_need_fwush = 1;

	/* huge pages use the owd page tabwe wock */
	if (!huge)
		assewt_pte_wocked(mm, addw);

	wetuwn owd;
}
#endif

static inwine int ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
					    unsigned wong addw, pte_t *ptep)
{
	unsigned wong owd;

	owd = pte_update(vma->vm_mm, addw, ptep, _PAGE_ACCESSED, 0, 0);

	wetuwn (owd & _PAGE_ACCESSED) != 0;
}
#define __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG

#ifndef ptep_set_wwpwotect
static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addw,
				      pte_t *ptep)
{
	pte_update(mm, addw, ptep, _PAGE_WWITE, 0, 0);
}
#endif
#define __HAVE_AWCH_PTEP_SET_WWPWOTECT

static inwine pte_t ptep_get_and_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
				       pte_t *ptep)
{
	wetuwn __pte(pte_update(mm, addw, ptep, ~0UW, 0, 0));
}
#define __HAVE_AWCH_PTEP_GET_AND_CWEAW

static inwine void pte_cweaw(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep)
{
	pte_update(mm, addw, ptep, ~0UW, 0, 0);
}

/* Set the diwty and/ow accessed bits atomicawwy in a winux PTE */
#ifndef __ptep_set_access_fwags
static inwine void __ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
					   pte_t *ptep, pte_t entwy,
					   unsigned wong addwess,
					   int psize)
{
	unsigned wong set = pte_vaw(entwy) &
			    (_PAGE_DIWTY | _PAGE_ACCESSED | _PAGE_WW | _PAGE_EXEC);
	int huge = psize > mmu_viwtuaw_psize ? 1 : 0;

	pte_update(vma->vm_mm, addwess, ptep, 0, set, huge);

	fwush_twb_page(vma, addwess);
}
#endif

/* Genewic accessows to PTE bits */
#ifndef pte_mkwwite_novma
static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	/*
	 * wwite impwies wead, hence set both
	 */
	wetuwn __pte(pte_vaw(pte) | _PAGE_WW);
}
#endif

static inwine pte_t pte_mkdiwty(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_DIWTY);
}

static inwine pte_t pte_mkyoung(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_ACCESSED);
}

#ifndef pte_wwpwotect
static inwine pte_t pte_wwpwotect(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~_PAGE_WWITE);
}
#endif

#ifndef pte_mkexec
static inwine pte_t pte_mkexec(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_EXEC);
}
#endif

#ifndef pte_wwite
static inwine int pte_wwite(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_WWITE;
}
#endif
static inwine int pte_diwty(pte_t pte)		{ wetuwn pte_vaw(pte) & _PAGE_DIWTY; }
static inwine int pte_speciaw(pte_t pte)	{ wetuwn pte_vaw(pte) & _PAGE_SPECIAW; }
static inwine int pte_none(pte_t pte)		{ wetuwn (pte_vaw(pte) & ~_PTE_NONE_MASK) == 0; }
static inwine boow pte_hashpte(pte_t pte)	{ wetuwn fawse; }
static inwine boow pte_ci(pte_t pte)		{ wetuwn pte_vaw(pte) & _PAGE_NO_CACHE; }
static inwine boow pte_exec(pte_t pte)		{ wetuwn pte_vaw(pte) & _PAGE_EXEC; }

static inwine int pte_pwesent(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_PWESENT;
}

static inwine boow pte_hw_vawid(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_PWESENT;
}

static inwine int pte_young(pte_t pte)
{
	wetuwn pte_vaw(pte) & _PAGE_ACCESSED;
}

/*
 * Don't just check fow any non zewo bits in __PAGE_WEAD, since fow book3e
 * and PTE_64BIT, PAGE_KEWNEW_X contains _PAGE_BAP_SW which is awso in
 * _PAGE_WEAD.  Need to expwicitwy match _PAGE_BAP_UW bit in that case too.
 */
#ifndef pte_wead
static inwine boow pte_wead(pte_t pte)
{
	wetuwn (pte_vaw(pte) & _PAGE_WEAD) == _PAGE_WEAD;
}
#endif

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
static inwine pte_t pfn_pte(unsigned wong pfn, pgpwot_t pgpwot) {
	wetuwn __pte(((pte_basic_t)(pfn) << PTE_WPN_SHIFT) |
		     pgpwot_vaw(pgpwot)); }

/* Genewic modifiews fow PTE bits */
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

static inwine pte_t pte_mkspeciaw(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_SPECIAW);
}

#ifndef pte_mkhuge
static inwine pte_t pte_mkhuge(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte));
}
#endif

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	wetuwn __pte((pte_vaw(pte) & _PAGE_CHG_MASK) | pgpwot_vaw(newpwot));
}

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

/* This wow wevew function pewfowms the actuaw PTE insewtion
 * Setting the PTE depends on the MMU type and othew factows. It's
 * an howwibwe mess that I'm not going to twy to cwean up now but
 * I'm keeping it in one pwace wathew than spwead awound
 */
static inwine void __set_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
				pte_t *ptep, pte_t pte, int pewcpu)
{
	/* Second case is 32-bit with 64-bit PTE.  In this case, we
	 * can just stowe as wong as we do the two hawves in the wight owdew
	 * with a bawwiew in between.
	 * In the pewcpu case, we awso fawwback to the simpwe update
	 */
	if (IS_ENABWED(CONFIG_PPC32) && IS_ENABWED(CONFIG_PTE_64BIT) && !pewcpu) {
		__asm__ __vowatiwe__("\
			stw%X0 %2,%0\n\
			mbaw\n\
			stw%X1 %W2,%1"
		: "=m" (*ptep), "=m" (*((unsigned chaw *)ptep+4))
		: "w" (pte) : "memowy");
		wetuwn;
	}
	/* Anything ewse just stowes the PTE nowmawwy. That covews aww 64-bit
	 * cases, and 32-bit non-hash with 32-bit PTEs.
	 */
#if defined(CONFIG_PPC_8xx) && defined(CONFIG_PPC_16K_PAGES)
	ptep->pte3 = ptep->pte2 = ptep->pte1 = ptep->pte = pte_vaw(pte);
#ewse
	*ptep = pte;
#endif

	/*
	 * With hawdwawe tabwewawk, a sync is needed to ensuwe that
	 * subsequent accesses see the PTE we just wwote.  Unwike usewspace
	 * mappings, we can't towewate spuwious fauwts, so make suwe
	 * the new PTE wiww be seen the fiwst time.
	 */
	if (IS_ENABWED(CONFIG_PPC_BOOK3E_64) && is_kewnew_addw(addw))
		mb();
}

/*
 * Macwo to mawk a page pwotection vawue as "uncacheabwe".
 */

#define _PAGE_CACHE_CTW	(_PAGE_COHEWENT | _PAGE_GUAWDED | _PAGE_NO_CACHE | \
			 _PAGE_WWITETHWU)

#define pgpwot_noncached(pwot)	  (__pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) | \
				            _PAGE_NO_CACHE | _PAGE_GUAWDED))

#define pgpwot_noncached_wc(pwot) (__pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) | \
				            _PAGE_NO_CACHE))

#define pgpwot_cached(pwot)       (__pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) | \
				            _PAGE_COHEWENT))

#if _PAGE_WWITETHWU != 0
#define pgpwot_cached_wthwu(pwot) (__pgpwot((pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW) | \
				            _PAGE_COHEWENT | _PAGE_WWITETHWU))
#ewse
#define pgpwot_cached_wthwu(pwot)	pgpwot_noncached(pwot)
#endif

#define pgpwot_cached_noncohewent(pwot) \
		(__pgpwot(pgpwot_vaw(pwot) & ~_PAGE_CACHE_CTW))

#define pgpwot_wwitecombine pgpwot_noncached_wc

#ifdef CONFIG_HUGETWB_PAGE
static inwine int hugepd_ok(hugepd_t hpd)
{
#ifdef CONFIG_PPC_8xx
	wetuwn ((hpd_vaw(hpd) & _PMD_PAGE_MASK) == _PMD_PAGE_8M);
#ewse
	/* We cweaw the top bit to indicate hugepd */
	wetuwn (hpd_vaw(hpd) && (hpd_vaw(hpd) & PD_HUGE) == 0);
#endif
}

static inwine int pmd_huge(pmd_t pmd)
{
	wetuwn 0;
}

static inwine int pud_huge(pud_t pud)
{
	wetuwn 0;
}

#define is_hugepd(hpd)		(hugepd_ok(hpd))
#endif

int map_kewnew_page(unsigned wong va, phys_addw_t pa, pgpwot_t pwot);
void unmap_kewnew_page(unsigned wong va);

#endif /* __ASSEMBWY__ */
#endif
