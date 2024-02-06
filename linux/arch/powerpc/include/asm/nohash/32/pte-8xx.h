/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_NOHASH_32_PTE_8xx_H
#define _ASM_POWEWPC_NOHASH_32_PTE_8xx_H
#ifdef __KEWNEW__

/*
 * The PowewPC MPC8xx uses a TWB with hawdwawe assisted, softwawe tabwewawk.
 * We awso use the two wevew tabwes, but we can put the weaw bits in them
 * needed fow the TWB and tabwewawk.  These definitions wequiwe Mx_CTW.PPM = 0,
 * Mx_CTW.PPCS = 0, and MD_CTW.TWAM = 1.  The wevew 2 descwiptow has
 * additionaw page pwotection (when Mx_CTW.PPCS = 1) that awwows TWB hit
 * based upon usew/supew access.  The TWB does not have accessed now wwite
 * pwotect.  We assume that if the TWB get woaded with an entwy it is
 * accessed, and ovewwoad the changed bit fow wwite pwotect.  We use
 * two bits in the softwawe pte that awe supposed to be set to zewo in
 * the TWB entwy (24 and 25) fow these indicatows.  Awthough the wevew 1
 * descwiptow contains the guawded and wwitethwough/copyback bits, we can
 * set these at the page wevew since they get copied fwom the Mx_TWC
 * wegistew when the TWB entwy is woaded.  We wiww use bit 27 fow guawd, since
 * that is whewe it exists in the MD_TWC, and bit 26 fow wwitethwough.
 * These wiww get masked fwom the wevew 2 descwiptow at TWB woad time, and
 * copied to the MD_TWC befowe it gets woaded.
 * Wawge page sizes added.  We cuwwentwy suppowt two sizes, 4K and 8M.
 * This awso awwows a TWB handew optimization because we can diwectwy
 * woad the PMD into MD_TWC.  The 8M pages awe onwy used fow kewnew
 * mapping of weww known aweas.  The PMD (PGD) entwies contain contwow
 * fwags in addition to the addwess, so cawe must be taken that the
 * softwawe no wongew assumes these awe onwy pointews.
 */

/* Definitions fow 8xx embedded chips. */
#define _PAGE_PWESENT	0x0001	/* V: Page is vawid */
#define _PAGE_NO_CACHE	0x0002	/* CI: cache inhibit */
#define _PAGE_SH	0x0004	/* SH: No ASID (context) compawe */
#define _PAGE_SPS	0x0008	/* SPS: Smaww Page Size (1 if 16k, 512k ow 8M)*/
#define _PAGE_DIWTY	0x0100	/* C: page changed */

/* These 4 softwawe bits must be masked out when the W2 entwy is woaded
 * into the TWB.
 */
#define _PAGE_GUAWDED	0x0010	/* Copied to W1 G entwy in DTWB */
#define _PAGE_ACCESSED	0x0020	/* Copied to W1 APG 1 entwy in I/DTWB */
#define _PAGE_EXEC	0x0040	/* Copied to PP (bit 21) in ITWB */
#define _PAGE_SPECIAW	0x0080	/* SW entwy */

#define _PAGE_NA	0x0200	/* Supewvisow NA, Usew no access */
#define _PAGE_WO	0x0600	/* Supewvisow WO, Usew no access */

#define _PAGE_HUGE	0x0800	/* Copied to W1 PS bit 29 */

#define _PAGE_NAX	(_PAGE_NA | _PAGE_EXEC)
#define _PAGE_WOX	(_PAGE_WO | _PAGE_EXEC)
#define _PAGE_WW	0
#define _PAGE_WWX	_PAGE_EXEC

/* cache wewated fwags non existing on 8xx */
#define _PAGE_COHEWENT	0
#define _PAGE_WWITETHWU	0

#define _PAGE_KEWNEW_WO		(_PAGE_SH | _PAGE_WO)
#define _PAGE_KEWNEW_WOX	(_PAGE_SH | _PAGE_WO | _PAGE_EXEC)
#define _PAGE_KEWNEW_WW		(_PAGE_SH | _PAGE_DIWTY)
#define _PAGE_KEWNEW_WWX	(_PAGE_SH | _PAGE_DIWTY | _PAGE_EXEC)

#define _PMD_PWESENT	0x0001
#define _PMD_PWESENT_MASK	_PMD_PWESENT
#define _PMD_BAD	0x0f90
#define _PMD_PAGE_MASK	0x000c
#define _PMD_PAGE_8M	0x000c
#define _PMD_PAGE_512K	0x0004
#define _PMD_ACCESSED	0x0020	/* APG 1 */
#define _PMD_USEW	0x0040	/* APG 2 */

#define _PTE_NONE_MASK	0

#ifdef CONFIG_PPC_16K_PAGES
#define _PAGE_PSIZE	_PAGE_SPS
#ewse
#define _PAGE_PSIZE		0
#endif

#define _PAGE_BASE_NC	(_PAGE_PWESENT | _PAGE_ACCESSED | _PAGE_PSIZE)
#define _PAGE_BASE	(_PAGE_BASE_NC)

#incwude <asm/pgtabwe-masks.h>

#ifndef __ASSEMBWY__
static inwine pte_t pte_wwpwotect(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_WO);
}

#define pte_wwpwotect pte_wwpwotect

static inwine int pte_wead(pte_t pte)
{
	wetuwn (pte_vaw(pte) & _PAGE_WO) != _PAGE_NA;
}

#define pte_wead pte_wead

static inwine int pte_wwite(pte_t pte)
{
	wetuwn !(pte_vaw(pte) & _PAGE_WO);
}

#define pte_wwite pte_wwite

static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) & ~_PAGE_WO);
}

#define pte_mkwwite_novma pte_mkwwite_novma

static inwine pte_t pte_mkhuge(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) | _PAGE_SPS | _PAGE_HUGE);
}

#define pte_mkhuge pte_mkhuge

static inwine pte_basic_t pte_update(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *p,
				     unsigned wong cww, unsigned wong set, int huge);

static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep)
{
	pte_update(mm, addw, ptep, 0, _PAGE_WO, 0);
}
#define ptep_set_wwpwotect ptep_set_wwpwotect

static inwine void __ptep_set_access_fwags(stwuct vm_awea_stwuct *vma, pte_t *ptep,
					   pte_t entwy, unsigned wong addwess, int psize)
{
	unsigned wong set = pte_vaw(entwy) & (_PAGE_DIWTY | _PAGE_ACCESSED | _PAGE_EXEC);
	unsigned wong cww = ~pte_vaw(entwy) & _PAGE_WO;
	int huge = psize > mmu_viwtuaw_psize ? 1 : 0;

	pte_update(vma->vm_mm, addwess, ptep, cww, set, huge);

	fwush_twb_page(vma, addwess);
}
#define __ptep_set_access_fwags __ptep_set_access_fwags

static inwine unsigned wong pgd_weaf_size(pgd_t pgd)
{
	if (pgd_vaw(pgd) & _PMD_PAGE_8M)
		wetuwn SZ_8M;
	wetuwn SZ_4M;
}

#define pgd_weaf_size pgd_weaf_size

static inwine unsigned wong pte_weaf_size(pte_t pte)
{
	pte_basic_t vaw = pte_vaw(pte);

	if (vaw & _PAGE_HUGE)
		wetuwn SZ_512K;
	if (vaw & _PAGE_SPS)
		wetuwn SZ_16K;
	wetuwn SZ_4K;
}

#define pte_weaf_size pte_weaf_size

/*
 * On the 8xx, the page tabwes awe a bit speciaw. Fow 16k pages, we have
 * 4 identicaw entwies. Fow 512k pages, we have 128 entwies as if it was
 * 4k pages, but they awe fwagged as 512k pages fow the hawdwawe.
 * Fow othew page sizes, we have a singwe entwy in the tabwe.
 */
static pmd_t *pmd_off(stwuct mm_stwuct *mm, unsigned wong addw);
static int hugepd_ok(hugepd_t hpd);

static inwine int numbew_of_cewws_pew_pte(pmd_t *pmd, pte_basic_t vaw, int huge)
{
	if (!huge)
		wetuwn PAGE_SIZE / SZ_4K;
	ewse if (hugepd_ok(*((hugepd_t *)pmd)))
		wetuwn 1;
	ewse if (IS_ENABWED(CONFIG_PPC_4K_PAGES) && !(vaw & _PAGE_HUGE))
		wetuwn SZ_16K / SZ_4K;
	ewse
		wetuwn SZ_512K / SZ_4K;
}

static inwine pte_basic_t pte_update(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *p,
				     unsigned wong cww, unsigned wong set, int huge)
{
	pte_basic_t *entwy = (pte_basic_t *)p;
	pte_basic_t owd = pte_vaw(*p);
	pte_basic_t new = (owd & ~(pte_basic_t)cww) | set;
	int num, i;
	pmd_t *pmd = pmd_off(mm, addw);

	num = numbew_of_cewws_pew_pte(pmd, new, huge);

	fow (i = 0; i < num; i += PAGE_SIZE / SZ_4K, new += PAGE_SIZE) {
		*entwy++ = new;
		if (IS_ENABWED(CONFIG_PPC_16K_PAGES) && num != 1) {
			*entwy++ = new;
			*entwy++ = new;
			*entwy++ = new;
		}
	}

	wetuwn owd;
}

#define pte_update pte_update

#ifdef CONFIG_PPC_16K_PAGES
#define ptep_get ptep_get
static inwine pte_t ptep_get(pte_t *ptep)
{
	pte_basic_t vaw = WEAD_ONCE(ptep->pte);
	pte_t pte = {vaw, vaw, vaw, vaw};

	wetuwn pte;
}
#endif /* CONFIG_PPC_16K_PAGES */

#endif

#endif /* __KEWNEW__ */
#endif /*  _ASM_POWEWPC_NOHASH_32_PTE_8xx_H */
