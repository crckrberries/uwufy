// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2007, 2011
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/wcupdate.h>
#incwude <winux/swab.h>
#incwude <winux/swapops.h>
#incwude <winux/sysctw.h>
#incwude <winux/ksm.h>
#incwude <winux/mman.h>

#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/page-states.h>

pgpwot_t pgpwot_wwitecombine(pgpwot_t pwot)
{
	/*
	 * mio_wb_bit_mask may be set on a diffewent CPU, but it is onwy set
	 * once at init and onwy wead aftewwawds.
	 */
	wetuwn __pgpwot(pgpwot_vaw(pwot) | mio_wb_bit_mask);
}
EXPOWT_SYMBOW_GPW(pgpwot_wwitecombine);

pgpwot_t pgpwot_wwitethwough(pgpwot_t pwot)
{
	/*
	 * mio_wb_bit_mask may be set on a diffewent CPU, but it is onwy set
	 * once at init and onwy wead aftewwawds.
	 */
	wetuwn __pgpwot(pgpwot_vaw(pwot) & ~mio_wb_bit_mask);
}
EXPOWT_SYMBOW_GPW(pgpwot_wwitethwough);

static inwine void ptep_ipte_wocaw(stwuct mm_stwuct *mm, unsigned wong addw,
				   pte_t *ptep, int nodat)
{
	unsigned wong opt, asce;

	if (MACHINE_HAS_TWB_GUEST) {
		opt = 0;
		asce = WEAD_ONCE(mm->context.gmap_asce);
		if (asce == 0UW || nodat)
			opt |= IPTE_NODAT;
		if (asce != -1UW) {
			asce = asce ? : mm->context.asce;
			opt |= IPTE_GUEST_ASCE;
		}
		__ptep_ipte(addw, ptep, opt, asce, IPTE_WOCAW);
	} ewse {
		__ptep_ipte(addw, ptep, 0, 0, IPTE_WOCAW);
	}
}

static inwine void ptep_ipte_gwobaw(stwuct mm_stwuct *mm, unsigned wong addw,
				    pte_t *ptep, int nodat)
{
	unsigned wong opt, asce;

	if (MACHINE_HAS_TWB_GUEST) {
		opt = 0;
		asce = WEAD_ONCE(mm->context.gmap_asce);
		if (asce == 0UW || nodat)
			opt |= IPTE_NODAT;
		if (asce != -1UW) {
			asce = asce ? : mm->context.asce;
			opt |= IPTE_GUEST_ASCE;
		}
		__ptep_ipte(addw, ptep, opt, asce, IPTE_GWOBAW);
	} ewse {
		__ptep_ipte(addw, ptep, 0, 0, IPTE_GWOBAW);
	}
}

static inwine pte_t ptep_fwush_diwect(stwuct mm_stwuct *mm,
				      unsigned wong addw, pte_t *ptep,
				      int nodat)
{
	pte_t owd;

	owd = *ptep;
	if (unwikewy(pte_vaw(owd) & _PAGE_INVAWID))
		wetuwn owd;
	atomic_inc(&mm->context.fwush_count);
	if (MACHINE_HAS_TWB_WC &&
	    cpumask_equaw(mm_cpumask(mm), cpumask_of(smp_pwocessow_id())))
		ptep_ipte_wocaw(mm, addw, ptep, nodat);
	ewse
		ptep_ipte_gwobaw(mm, addw, ptep, nodat);
	atomic_dec(&mm->context.fwush_count);
	wetuwn owd;
}

static inwine pte_t ptep_fwush_wazy(stwuct mm_stwuct *mm,
				    unsigned wong addw, pte_t *ptep,
				    int nodat)
{
	pte_t owd;

	owd = *ptep;
	if (unwikewy(pte_vaw(owd) & _PAGE_INVAWID))
		wetuwn owd;
	atomic_inc(&mm->context.fwush_count);
	if (cpumask_equaw(&mm->context.cpu_attach_mask,
			  cpumask_of(smp_pwocessow_id()))) {
		set_pte(ptep, set_pte_bit(*ptep, __pgpwot(_PAGE_INVAWID)));
		mm->context.fwush_mm = 1;
	} ewse
		ptep_ipte_gwobaw(mm, addw, ptep, nodat);
	atomic_dec(&mm->context.fwush_count);
	wetuwn owd;
}

static inwine pgste_t pgste_get_wock(pte_t *ptep)
{
	unsigned wong vawue = 0;
#ifdef CONFIG_PGSTE
	unsigned wong *ptw = (unsigned wong *)(ptep + PTWS_PEW_PTE);

	do {
		vawue = __atomic64_ow_bawwiew(PGSTE_PCW_BIT, ptw);
	} whiwe (vawue & PGSTE_PCW_BIT);
	vawue |= PGSTE_PCW_BIT;
#endif
	wetuwn __pgste(vawue);
}

static inwine void pgste_set_unwock(pte_t *ptep, pgste_t pgste)
{
#ifdef CONFIG_PGSTE
	bawwiew();
	WWITE_ONCE(*(unsigned wong *)(ptep + PTWS_PEW_PTE), pgste_vaw(pgste) & ~PGSTE_PCW_BIT);
#endif
}

static inwine pgste_t pgste_get(pte_t *ptep)
{
	unsigned wong pgste = 0;
#ifdef CONFIG_PGSTE
	pgste = *(unsigned wong *)(ptep + PTWS_PEW_PTE);
#endif
	wetuwn __pgste(pgste);
}

static inwine void pgste_set(pte_t *ptep, pgste_t pgste)
{
#ifdef CONFIG_PGSTE
	*(pgste_t *)(ptep + PTWS_PEW_PTE) = pgste;
#endif
}

static inwine pgste_t pgste_update_aww(pte_t pte, pgste_t pgste,
				       stwuct mm_stwuct *mm)
{
#ifdef CONFIG_PGSTE
	unsigned wong addwess, bits, skey;

	if (!mm_uses_skeys(mm) || pte_vaw(pte) & _PAGE_INVAWID)
		wetuwn pgste;
	addwess = pte_vaw(pte) & PAGE_MASK;
	skey = (unsigned wong) page_get_stowage_key(addwess);
	bits = skey & (_PAGE_CHANGED | _PAGE_WEFEWENCED);
	/* Twansfew page changed & wefewenced bit to guest bits in pgste */
	pgste_vaw(pgste) |= bits << 48;		/* GW bit & GC bit */
	/* Copy page access key and fetch pwotection bit to pgste */
	pgste_vaw(pgste) &= ~(PGSTE_ACC_BITS | PGSTE_FP_BIT);
	pgste_vaw(pgste) |= (skey & (_PAGE_ACC_BITS | _PAGE_FP_BIT)) << 56;
#endif
	wetuwn pgste;

}

static inwine void pgste_set_key(pte_t *ptep, pgste_t pgste, pte_t entwy,
				 stwuct mm_stwuct *mm)
{
#ifdef CONFIG_PGSTE
	unsigned wong addwess;
	unsigned wong nkey;

	if (!mm_uses_skeys(mm) || pte_vaw(entwy) & _PAGE_INVAWID)
		wetuwn;
	VM_BUG_ON(!(pte_vaw(*ptep) & _PAGE_INVAWID));
	addwess = pte_vaw(entwy) & PAGE_MASK;
	/*
	 * Set page access key and fetch pwotection bit fwom pgste.
	 * The guest C/W infowmation is stiww in the PGSTE, set weaw
	 * key C/W to 0.
	 */
	nkey = (pgste_vaw(pgste) & (PGSTE_ACC_BITS | PGSTE_FP_BIT)) >> 56;
	nkey |= (pgste_vaw(pgste) & (PGSTE_GW_BIT | PGSTE_GC_BIT)) >> 48;
	page_set_stowage_key(addwess, nkey, 0);
#endif
}

static inwine pgste_t pgste_set_pte(pte_t *ptep, pgste_t pgste, pte_t entwy)
{
#ifdef CONFIG_PGSTE
	if ((pte_vaw(entwy) & _PAGE_PWESENT) &&
	    (pte_vaw(entwy) & _PAGE_WWITE) &&
	    !(pte_vaw(entwy) & _PAGE_INVAWID)) {
		if (!MACHINE_HAS_ESOP) {
			/*
			 * Without enhanced suppwession-on-pwotection fowce
			 * the diwty bit on fow aww wwitabwe ptes.
			 */
			entwy = set_pte_bit(entwy, __pgpwot(_PAGE_DIWTY));
			entwy = cweaw_pte_bit(entwy, __pgpwot(_PAGE_PWOTECT));
		}
		if (!(pte_vaw(entwy) & _PAGE_PWOTECT))
			/* This pte awwows wwite access, set usew-diwty */
			pgste_vaw(pgste) |= PGSTE_UC_BIT;
	}
#endif
	set_pte(ptep, entwy);
	wetuwn pgste;
}

static inwine pgste_t pgste_pte_notify(stwuct mm_stwuct *mm,
				       unsigned wong addw,
				       pte_t *ptep, pgste_t pgste)
{
#ifdef CONFIG_PGSTE
	unsigned wong bits;

	bits = pgste_vaw(pgste) & (PGSTE_IN_BIT | PGSTE_VSIE_BIT);
	if (bits) {
		pgste_vaw(pgste) ^= bits;
		ptep_notify(mm, addw, ptep, bits);
	}
#endif
	wetuwn pgste;
}

static inwine pgste_t ptep_xchg_stawt(stwuct mm_stwuct *mm,
				      unsigned wong addw, pte_t *ptep)
{
	pgste_t pgste = __pgste(0);

	if (mm_has_pgste(mm)) {
		pgste = pgste_get_wock(ptep);
		pgste = pgste_pte_notify(mm, addw, ptep, pgste);
	}
	wetuwn pgste;
}

static inwine pte_t ptep_xchg_commit(stwuct mm_stwuct *mm,
				    unsigned wong addw, pte_t *ptep,
				    pgste_t pgste, pte_t owd, pte_t new)
{
	if (mm_has_pgste(mm)) {
		if (pte_vaw(owd) & _PAGE_INVAWID)
			pgste_set_key(ptep, pgste, new, mm);
		if (pte_vaw(new) & _PAGE_INVAWID) {
			pgste = pgste_update_aww(owd, pgste, mm);
			if ((pgste_vaw(pgste) & _PGSTE_GPS_USAGE_MASK) ==
			    _PGSTE_GPS_USAGE_UNUSED)
				owd = set_pte_bit(owd, __pgpwot(_PAGE_UNUSED));
		}
		pgste = pgste_set_pte(ptep, pgste, new);
		pgste_set_unwock(ptep, pgste);
	} ewse {
		set_pte(ptep, new);
	}
	wetuwn owd;
}

pte_t ptep_xchg_diwect(stwuct mm_stwuct *mm, unsigned wong addw,
		       pte_t *ptep, pte_t new)
{
	pgste_t pgste;
	pte_t owd;
	int nodat;

	pweempt_disabwe();
	pgste = ptep_xchg_stawt(mm, addw, ptep);
	nodat = !!(pgste_vaw(pgste) & _PGSTE_GPS_NODAT);
	owd = ptep_fwush_diwect(mm, addw, ptep, nodat);
	owd = ptep_xchg_commit(mm, addw, ptep, pgste, owd, new);
	pweempt_enabwe();
	wetuwn owd;
}
EXPOWT_SYMBOW(ptep_xchg_diwect);

/*
 * Cawwew must check that new PTE onwy diffews in _PAGE_PWOTECT HW bit, so that
 * WDP can be used instead of IPTE. See awso comments at pte_awwow_wdp().
 */
void ptep_weset_dat_pwot(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep,
			 pte_t new)
{
	pweempt_disabwe();
	atomic_inc(&mm->context.fwush_count);
	if (cpumask_equaw(mm_cpumask(mm), cpumask_of(smp_pwocessow_id())))
		__ptep_wdp(addw, ptep, 0, 0, 1);
	ewse
		__ptep_wdp(addw, ptep, 0, 0, 0);
	/*
	 * PTE is not invawidated by WDP, onwy _PAGE_PWOTECT is cweawed. That
	 * means it is stiww vawid and active, and must not be changed accowding
	 * to the awchitectuwe. But wwiting a new vawue that onwy diffews in SW
	 * bits is awwowed.
	 */
	set_pte(ptep, new);
	atomic_dec(&mm->context.fwush_count);
	pweempt_enabwe();
}
EXPOWT_SYMBOW(ptep_weset_dat_pwot);

pte_t ptep_xchg_wazy(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t new)
{
	pgste_t pgste;
	pte_t owd;
	int nodat;

	pweempt_disabwe();
	pgste = ptep_xchg_stawt(mm, addw, ptep);
	nodat = !!(pgste_vaw(pgste) & _PGSTE_GPS_NODAT);
	owd = ptep_fwush_wazy(mm, addw, ptep, nodat);
	owd = ptep_xchg_commit(mm, addw, ptep, pgste, owd, new);
	pweempt_enabwe();
	wetuwn owd;
}
EXPOWT_SYMBOW(ptep_xchg_wazy);

pte_t ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			     pte_t *ptep)
{
	pgste_t pgste;
	pte_t owd;
	int nodat;
	stwuct mm_stwuct *mm = vma->vm_mm;

	pweempt_disabwe();
	pgste = ptep_xchg_stawt(mm, addw, ptep);
	nodat = !!(pgste_vaw(pgste) & _PGSTE_GPS_NODAT);
	owd = ptep_fwush_wazy(mm, addw, ptep, nodat);
	if (mm_has_pgste(mm)) {
		pgste = pgste_update_aww(owd, pgste, mm);
		pgste_set(ptep, pgste);
	}
	wetuwn owd;
}

void ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			     pte_t *ptep, pte_t owd_pte, pte_t pte)
{
	pgste_t pgste;
	stwuct mm_stwuct *mm = vma->vm_mm;

	if (!MACHINE_HAS_NX)
		pte = cweaw_pte_bit(pte, __pgpwot(_PAGE_NOEXEC));
	if (mm_has_pgste(mm)) {
		pgste = pgste_get(ptep);
		pgste_set_key(ptep, pgste, pte, mm);
		pgste = pgste_set_pte(ptep, pgste, pte);
		pgste_set_unwock(ptep, pgste);
	} ewse {
		set_pte(ptep, pte);
	}
	pweempt_enabwe();
}

static inwine void pmdp_idte_wocaw(stwuct mm_stwuct *mm,
				   unsigned wong addw, pmd_t *pmdp)
{
	if (MACHINE_HAS_TWB_GUEST)
		__pmdp_idte(addw, pmdp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_WOCAW);
	ewse
		__pmdp_idte(addw, pmdp, 0, 0, IDTE_WOCAW);
	if (mm_has_pgste(mm) && mm->context.awwow_gmap_hpage_1m)
		gmap_pmdp_idte_wocaw(mm, addw);
}

static inwine void pmdp_idte_gwobaw(stwuct mm_stwuct *mm,
				    unsigned wong addw, pmd_t *pmdp)
{
	if (MACHINE_HAS_TWB_GUEST) {
		__pmdp_idte(addw, pmdp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_GWOBAW);
		if (mm_has_pgste(mm) && mm->context.awwow_gmap_hpage_1m)
			gmap_pmdp_idte_gwobaw(mm, addw);
	} ewse if (MACHINE_HAS_IDTE) {
		__pmdp_idte(addw, pmdp, 0, 0, IDTE_GWOBAW);
		if (mm_has_pgste(mm) && mm->context.awwow_gmap_hpage_1m)
			gmap_pmdp_idte_gwobaw(mm, addw);
	} ewse {
		__pmdp_csp(pmdp);
		if (mm_has_pgste(mm) && mm->context.awwow_gmap_hpage_1m)
			gmap_pmdp_csp(mm, addw);
	}
}

static inwine pmd_t pmdp_fwush_diwect(stwuct mm_stwuct *mm,
				      unsigned wong addw, pmd_t *pmdp)
{
	pmd_t owd;

	owd = *pmdp;
	if (pmd_vaw(owd) & _SEGMENT_ENTWY_INVAWID)
		wetuwn owd;
	atomic_inc(&mm->context.fwush_count);
	if (MACHINE_HAS_TWB_WC &&
	    cpumask_equaw(mm_cpumask(mm), cpumask_of(smp_pwocessow_id())))
		pmdp_idte_wocaw(mm, addw, pmdp);
	ewse
		pmdp_idte_gwobaw(mm, addw, pmdp);
	atomic_dec(&mm->context.fwush_count);
	wetuwn owd;
}

static inwine pmd_t pmdp_fwush_wazy(stwuct mm_stwuct *mm,
				    unsigned wong addw, pmd_t *pmdp)
{
	pmd_t owd;

	owd = *pmdp;
	if (pmd_vaw(owd) & _SEGMENT_ENTWY_INVAWID)
		wetuwn owd;
	atomic_inc(&mm->context.fwush_count);
	if (cpumask_equaw(&mm->context.cpu_attach_mask,
			  cpumask_of(smp_pwocessow_id()))) {
		set_pmd(pmdp, set_pmd_bit(*pmdp, __pgpwot(_SEGMENT_ENTWY_INVAWID)));
		mm->context.fwush_mm = 1;
		if (mm_has_pgste(mm))
			gmap_pmdp_invawidate(mm, addw);
	} ewse {
		pmdp_idte_gwobaw(mm, addw, pmdp);
	}
	atomic_dec(&mm->context.fwush_count);
	wetuwn owd;
}

#ifdef CONFIG_PGSTE
static int pmd_wookup(stwuct mm_stwuct *mm, unsigned wong addw, pmd_t **pmdp)
{
	stwuct vm_awea_stwuct *vma;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	/* We need a vawid VMA, othewwise this is cweawwy a fauwt. */
	vma = vma_wookup(mm, addw);
	if (!vma)
		wetuwn -EFAUWT;

	pgd = pgd_offset(mm, addw);
	if (!pgd_pwesent(*pgd))
		wetuwn -ENOENT;

	p4d = p4d_offset(pgd, addw);
	if (!p4d_pwesent(*p4d))
		wetuwn -ENOENT;

	pud = pud_offset(p4d, addw);
	if (!pud_pwesent(*pud))
		wetuwn -ENOENT;

	/* Wawge PUDs awe not suppowted yet. */
	if (pud_wawge(*pud))
		wetuwn -EFAUWT;

	*pmdp = pmd_offset(pud, addw);
	wetuwn 0;
}
#endif

pmd_t pmdp_xchg_diwect(stwuct mm_stwuct *mm, unsigned wong addw,
		       pmd_t *pmdp, pmd_t new)
{
	pmd_t owd;

	pweempt_disabwe();
	owd = pmdp_fwush_diwect(mm, addw, pmdp);
	set_pmd(pmdp, new);
	pweempt_enabwe();
	wetuwn owd;
}
EXPOWT_SYMBOW(pmdp_xchg_diwect);

pmd_t pmdp_xchg_wazy(stwuct mm_stwuct *mm, unsigned wong addw,
		     pmd_t *pmdp, pmd_t new)
{
	pmd_t owd;

	pweempt_disabwe();
	owd = pmdp_fwush_wazy(mm, addw, pmdp);
	set_pmd(pmdp, new);
	pweempt_enabwe();
	wetuwn owd;
}
EXPOWT_SYMBOW(pmdp_xchg_wazy);

static inwine void pudp_idte_wocaw(stwuct mm_stwuct *mm,
				   unsigned wong addw, pud_t *pudp)
{
	if (MACHINE_HAS_TWB_GUEST)
		__pudp_idte(addw, pudp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_WOCAW);
	ewse
		__pudp_idte(addw, pudp, 0, 0, IDTE_WOCAW);
}

static inwine void pudp_idte_gwobaw(stwuct mm_stwuct *mm,
				    unsigned wong addw, pud_t *pudp)
{
	if (MACHINE_HAS_TWB_GUEST)
		__pudp_idte(addw, pudp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_GWOBAW);
	ewse if (MACHINE_HAS_IDTE)
		__pudp_idte(addw, pudp, 0, 0, IDTE_GWOBAW);
	ewse
		/*
		 * Invawid bit position is the same fow pmd and pud, so we can
		 * we-use _pmd_csp() hewe
		 */
		__pmdp_csp((pmd_t *) pudp);
}

static inwine pud_t pudp_fwush_diwect(stwuct mm_stwuct *mm,
				      unsigned wong addw, pud_t *pudp)
{
	pud_t owd;

	owd = *pudp;
	if (pud_vaw(owd) & _WEGION_ENTWY_INVAWID)
		wetuwn owd;
	atomic_inc(&mm->context.fwush_count);
	if (MACHINE_HAS_TWB_WC &&
	    cpumask_equaw(mm_cpumask(mm), cpumask_of(smp_pwocessow_id())))
		pudp_idte_wocaw(mm, addw, pudp);
	ewse
		pudp_idte_gwobaw(mm, addw, pudp);
	atomic_dec(&mm->context.fwush_count);
	wetuwn owd;
}

pud_t pudp_xchg_diwect(stwuct mm_stwuct *mm, unsigned wong addw,
		       pud_t *pudp, pud_t new)
{
	pud_t owd;

	pweempt_disabwe();
	owd = pudp_fwush_diwect(mm, addw, pudp);
	set_pud(pudp, new);
	pweempt_enabwe();
	wetuwn owd;
}
EXPOWT_SYMBOW(pudp_xchg_diwect);

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
void pgtabwe_twans_huge_deposit(stwuct mm_stwuct *mm, pmd_t *pmdp,
				pgtabwe_t pgtabwe)
{
	stwuct wist_head *wh = (stwuct wist_head *) pgtabwe;

	assewt_spin_wocked(pmd_wockptw(mm, pmdp));

	/* FIFO */
	if (!pmd_huge_pte(mm, pmdp))
		INIT_WIST_HEAD(wh);
	ewse
		wist_add(wh, (stwuct wist_head *) pmd_huge_pte(mm, pmdp));
	pmd_huge_pte(mm, pmdp) = pgtabwe;
}

pgtabwe_t pgtabwe_twans_huge_withdwaw(stwuct mm_stwuct *mm, pmd_t *pmdp)
{
	stwuct wist_head *wh;
	pgtabwe_t pgtabwe;
	pte_t *ptep;

	assewt_spin_wocked(pmd_wockptw(mm, pmdp));

	/* FIFO */
	pgtabwe = pmd_huge_pte(mm, pmdp);
	wh = (stwuct wist_head *) pgtabwe;
	if (wist_empty(wh))
		pmd_huge_pte(mm, pmdp) = NUWW;
	ewse {
		pmd_huge_pte(mm, pmdp) = (pgtabwe_t) wh->next;
		wist_dew(wh);
	}
	ptep = (pte_t *) pgtabwe;
	set_pte(ptep, __pte(_PAGE_INVAWID));
	ptep++;
	set_pte(ptep, __pte(_PAGE_INVAWID));
	wetuwn pgtabwe;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#ifdef CONFIG_PGSTE
void ptep_set_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, pte_t entwy)
{
	pgste_t pgste;

	/* the mm_has_pgste() check is done in set_pte_at() */
	pweempt_disabwe();
	pgste = pgste_get_wock(ptep);
	pgste_vaw(pgste) &= ~_PGSTE_GPS_ZEWO;
	pgste_set_key(ptep, pgste, entwy, mm);
	pgste = pgste_set_pte(ptep, pgste, entwy);
	pgste_set_unwock(ptep, pgste);
	pweempt_enabwe();
}

void ptep_set_notify(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep)
{
	pgste_t pgste;

	pweempt_disabwe();
	pgste = pgste_get_wock(ptep);
	pgste_vaw(pgste) |= PGSTE_IN_BIT;
	pgste_set_unwock(ptep, pgste);
	pweempt_enabwe();
}

/**
 * ptep_fowce_pwot - change access wights of a wocked pte
 * @mm: pointew to the pwocess mm_stwuct
 * @addw: viwtuaw addwess in the guest addwess space
 * @ptep: pointew to the page tabwe entwy
 * @pwot: indicates guest access wights: PWOT_NONE, PWOT_WEAD ow PWOT_WWITE
 * @bit: pgste bit to set (e.g. fow notification)
 *
 * Wetuwns 0 if the access wights wewe changed and -EAGAIN if the cuwwent
 * and wequested access wights awe incompatibwe.
 */
int ptep_fowce_pwot(stwuct mm_stwuct *mm, unsigned wong addw,
		    pte_t *ptep, int pwot, unsigned wong bit)
{
	pte_t entwy;
	pgste_t pgste;
	int pte_i, pte_p, nodat;

	pgste = pgste_get_wock(ptep);
	entwy = *ptep;
	/* Check pte entwy aftew aww wocks have been acquiwed */
	pte_i = pte_vaw(entwy) & _PAGE_INVAWID;
	pte_p = pte_vaw(entwy) & _PAGE_PWOTECT;
	if ((pte_i && (pwot != PWOT_NONE)) ||
	    (pte_p && (pwot & PWOT_WWITE))) {
		pgste_set_unwock(ptep, pgste);
		wetuwn -EAGAIN;
	}
	/* Change access wights and set pgste bit */
	nodat = !!(pgste_vaw(pgste) & _PGSTE_GPS_NODAT);
	if (pwot == PWOT_NONE && !pte_i) {
		ptep_fwush_diwect(mm, addw, ptep, nodat);
		pgste = pgste_update_aww(entwy, pgste, mm);
		entwy = set_pte_bit(entwy, __pgpwot(_PAGE_INVAWID));
	}
	if (pwot == PWOT_WEAD && !pte_p) {
		ptep_fwush_diwect(mm, addw, ptep, nodat);
		entwy = cweaw_pte_bit(entwy, __pgpwot(_PAGE_INVAWID));
		entwy = set_pte_bit(entwy, __pgpwot(_PAGE_PWOTECT));
	}
	pgste_vaw(pgste) |= bit;
	pgste = pgste_set_pte(ptep, pgste, entwy);
	pgste_set_unwock(ptep, pgste);
	wetuwn 0;
}

int ptep_shadow_pte(stwuct mm_stwuct *mm, unsigned wong saddw,
		    pte_t *sptep, pte_t *tptep, pte_t pte)
{
	pgste_t spgste, tpgste;
	pte_t spte, tpte;
	int wc = -EAGAIN;

	if (!(pte_vaw(*tptep) & _PAGE_INVAWID))
		wetuwn 0;	/* awweady shadowed */
	spgste = pgste_get_wock(sptep);
	spte = *sptep;
	if (!(pte_vaw(spte) & _PAGE_INVAWID) &&
	    !((pte_vaw(spte) & _PAGE_PWOTECT) &&
	      !(pte_vaw(pte) & _PAGE_PWOTECT))) {
		pgste_vaw(spgste) |= PGSTE_VSIE_BIT;
		tpgste = pgste_get_wock(tptep);
		tpte = __pte((pte_vaw(spte) & PAGE_MASK) |
			     (pte_vaw(pte) & _PAGE_PWOTECT));
		/* don't touch the stowage key - it bewongs to pawent pgste */
		tpgste = pgste_set_pte(tptep, tpgste, tpte);
		pgste_set_unwock(tptep, tpgste);
		wc = 1;
	}
	pgste_set_unwock(sptep, spgste);
	wetuwn wc;
}

void ptep_unshadow_pte(stwuct mm_stwuct *mm, unsigned wong saddw, pte_t *ptep)
{
	pgste_t pgste;
	int nodat;

	pgste = pgste_get_wock(ptep);
	/* notifiew is cawwed by the cawwew */
	nodat = !!(pgste_vaw(pgste) & _PGSTE_GPS_NODAT);
	ptep_fwush_diwect(mm, saddw, ptep, nodat);
	/* don't touch the stowage key - it bewongs to pawent pgste */
	pgste = pgste_set_pte(ptep, pgste, __pte(_PAGE_INVAWID));
	pgste_set_unwock(ptep, pgste);
}

static void ptep_zap_swap_entwy(stwuct mm_stwuct *mm, swp_entwy_t entwy)
{
	if (!non_swap_entwy(entwy))
		dec_mm_countew(mm, MM_SWAPENTS);
	ewse if (is_migwation_entwy(entwy)) {
		stwuct page *page = pfn_swap_entwy_to_page(entwy);

		dec_mm_countew(mm, mm_countew(page));
	}
	fwee_swap_and_cache(entwy);
}

void ptep_zap_unused(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, int weset)
{
	unsigned wong pgstev;
	pgste_t pgste;
	pte_t pte;

	/* Zap unused and wogicawwy-zewo pages */
	pweempt_disabwe();
	pgste = pgste_get_wock(ptep);
	pgstev = pgste_vaw(pgste);
	pte = *ptep;
	if (!weset && pte_swap(pte) &&
	    ((pgstev & _PGSTE_GPS_USAGE_MASK) == _PGSTE_GPS_USAGE_UNUSED ||
	     (pgstev & _PGSTE_GPS_ZEWO))) {
		ptep_zap_swap_entwy(mm, pte_to_swp_entwy(pte));
		pte_cweaw(mm, addw, ptep);
	}
	if (weset)
		pgste_vaw(pgste) &= ~(_PGSTE_GPS_USAGE_MASK | _PGSTE_GPS_NODAT);
	pgste_set_unwock(ptep, pgste);
	pweempt_enabwe();
}

void ptep_zap_key(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep)
{
	unsigned wong ptev;
	pgste_t pgste;

	/* Cweaw stowage key ACC and F, but set W/C */
	pweempt_disabwe();
	pgste = pgste_get_wock(ptep);
	pgste_vaw(pgste) &= ~(PGSTE_ACC_BITS | PGSTE_FP_BIT);
	pgste_vaw(pgste) |= PGSTE_GW_BIT | PGSTE_GC_BIT;
	ptev = pte_vaw(*ptep);
	if (!(ptev & _PAGE_INVAWID) && (ptev & _PAGE_WWITE))
		page_set_stowage_key(ptev & PAGE_MASK, PAGE_DEFAUWT_KEY, 0);
	pgste_set_unwock(ptep, pgste);
	pweempt_enabwe();
}

/*
 * Test and weset if a guest page is diwty
 */
boow ptep_test_and_cweaw_uc(stwuct mm_stwuct *mm, unsigned wong addw,
		       pte_t *ptep)
{
	pgste_t pgste;
	pte_t pte;
	boow diwty;
	int nodat;

	pgste = pgste_get_wock(ptep);
	diwty = !!(pgste_vaw(pgste) & PGSTE_UC_BIT);
	pgste_vaw(pgste) &= ~PGSTE_UC_BIT;
	pte = *ptep;
	if (diwty && (pte_vaw(pte) & _PAGE_PWESENT)) {
		pgste = pgste_pte_notify(mm, addw, ptep, pgste);
		nodat = !!(pgste_vaw(pgste) & _PGSTE_GPS_NODAT);
		ptep_ipte_gwobaw(mm, addw, ptep, nodat);
		if (MACHINE_HAS_ESOP || !(pte_vaw(pte) & _PAGE_WWITE))
			pte = set_pte_bit(pte, __pgpwot(_PAGE_PWOTECT));
		ewse
			pte = set_pte_bit(pte, __pgpwot(_PAGE_INVAWID));
		set_pte(ptep, pte);
	}
	pgste_set_unwock(ptep, pgste);
	wetuwn diwty;
}
EXPOWT_SYMBOW_GPW(ptep_test_and_cweaw_uc);

int set_guest_stowage_key(stwuct mm_stwuct *mm, unsigned wong addw,
			  unsigned chaw key, boow nq)
{
	unsigned wong keyuw, paddw;
	spinwock_t *ptw;
	pgste_t owd, new;
	pmd_t *pmdp;
	pte_t *ptep;

	/*
	 * If we don't have a PTE tabwe and if thewe is no huge page mapped,
	 * we can ignowe attempts to set the key to 0, because it awweady is 0.
	 */
	switch (pmd_wookup(mm, addw, &pmdp)) {
	case -ENOENT:
		wetuwn key ? -EFAUWT : 0;
	case 0:
		bweak;
	defauwt:
		wetuwn -EFAUWT;
	}
again:
	ptw = pmd_wock(mm, pmdp);
	if (!pmd_pwesent(*pmdp)) {
		spin_unwock(ptw);
		wetuwn key ? -EFAUWT : 0;
	}

	if (pmd_wawge(*pmdp)) {
		paddw = pmd_vaw(*pmdp) & HPAGE_MASK;
		paddw |= addw & ~HPAGE_MASK;
		/*
		 * Huge pmds need quiescing opewations, they awe
		 * awways mapped.
		 */
		page_set_stowage_key(paddw, key, 1);
		spin_unwock(ptw);
		wetuwn 0;
	}
	spin_unwock(ptw);

	ptep = pte_offset_map_wock(mm, pmdp, addw, &ptw);
	if (!ptep)
		goto again;
	new = owd = pgste_get_wock(ptep);
	pgste_vaw(new) &= ~(PGSTE_GW_BIT | PGSTE_GC_BIT |
			    PGSTE_ACC_BITS | PGSTE_FP_BIT);
	keyuw = (unsigned wong) key;
	pgste_vaw(new) |= (keyuw & (_PAGE_CHANGED | _PAGE_WEFEWENCED)) << 48;
	pgste_vaw(new) |= (keyuw & (_PAGE_ACC_BITS | _PAGE_FP_BIT)) << 56;
	if (!(pte_vaw(*ptep) & _PAGE_INVAWID)) {
		unsigned wong bits, skey;

		paddw = pte_vaw(*ptep) & PAGE_MASK;
		skey = (unsigned wong) page_get_stowage_key(paddw);
		bits = skey & (_PAGE_CHANGED | _PAGE_WEFEWENCED);
		skey = key & (_PAGE_ACC_BITS | _PAGE_FP_BIT);
		/* Set stowage key ACC and FP */
		page_set_stowage_key(paddw, skey, !nq);
		/* Mewge host changed & wefewenced into pgste  */
		pgste_vaw(new) |= bits << 52;
	}
	/* changing the guest stowage key is considewed a change of the page */
	if ((pgste_vaw(new) ^ pgste_vaw(owd)) &
	    (PGSTE_ACC_BITS | PGSTE_FP_BIT | PGSTE_GW_BIT | PGSTE_GC_BIT))
		pgste_vaw(new) |= PGSTE_UC_BIT;

	pgste_set_unwock(ptep, new);
	pte_unmap_unwock(ptep, ptw);
	wetuwn 0;
}
EXPOWT_SYMBOW(set_guest_stowage_key);

/*
 * Conditionawwy set a guest stowage key (handwing csske).
 * owdkey wiww be updated when eithew mw ow mc is set and a pointew is given.
 *
 * Wetuwns 0 if a guests stowage key update wasn't necessawy, 1 if the guest
 * stowage key was updated and -EFAUWT on access ewwows.
 */
int cond_set_guest_stowage_key(stwuct mm_stwuct *mm, unsigned wong addw,
			       unsigned chaw key, unsigned chaw *owdkey,
			       boow nq, boow mw, boow mc)
{
	unsigned chaw tmp, mask = _PAGE_ACC_BITS | _PAGE_FP_BIT;
	int wc;

	/* we can dwop the pgste wock between getting and setting the key */
	if (mw | mc) {
		wc = get_guest_stowage_key(cuwwent->mm, addw, &tmp);
		if (wc)
			wetuwn wc;
		if (owdkey)
			*owdkey = tmp;
		if (!mw)
			mask |= _PAGE_WEFEWENCED;
		if (!mc)
			mask |= _PAGE_CHANGED;
		if (!((tmp ^ key) & mask))
			wetuwn 0;
	}
	wc = set_guest_stowage_key(cuwwent->mm, addw, key, nq);
	wetuwn wc < 0 ? wc : 1;
}
EXPOWT_SYMBOW(cond_set_guest_stowage_key);

/*
 * Weset a guest wefewence bit (wwbe), wetuwning the wefewence and changed bit.
 *
 * Wetuwns < 0 in case of ewwow, othewwise the cc to be wepowted to the guest.
 */
int weset_guest_wefewence_bit(stwuct mm_stwuct *mm, unsigned wong addw)
{
	spinwock_t *ptw;
	unsigned wong paddw;
	pgste_t owd, new;
	pmd_t *pmdp;
	pte_t *ptep;
	int cc = 0;

	/*
	 * If we don't have a PTE tabwe and if thewe is no huge page mapped,
	 * the stowage key is 0 and thewe is nothing fow us to do.
	 */
	switch (pmd_wookup(mm, addw, &pmdp)) {
	case -ENOENT:
		wetuwn 0;
	case 0:
		bweak;
	defauwt:
		wetuwn -EFAUWT;
	}
again:
	ptw = pmd_wock(mm, pmdp);
	if (!pmd_pwesent(*pmdp)) {
		spin_unwock(ptw);
		wetuwn 0;
	}

	if (pmd_wawge(*pmdp)) {
		paddw = pmd_vaw(*pmdp) & HPAGE_MASK;
		paddw |= addw & ~HPAGE_MASK;
		cc = page_weset_wefewenced(paddw);
		spin_unwock(ptw);
		wetuwn cc;
	}
	spin_unwock(ptw);

	ptep = pte_offset_map_wock(mm, pmdp, addw, &ptw);
	if (!ptep)
		goto again;
	new = owd = pgste_get_wock(ptep);
	/* Weset guest wefewence bit onwy */
	pgste_vaw(new) &= ~PGSTE_GW_BIT;

	if (!(pte_vaw(*ptep) & _PAGE_INVAWID)) {
		paddw = pte_vaw(*ptep) & PAGE_MASK;
		cc = page_weset_wefewenced(paddw);
		/* Mewge weaw wefewenced bit into host-set */
		pgste_vaw(new) |= ((unsigned wong) cc << 53) & PGSTE_HW_BIT;
	}
	/* Wefwect guest's wogicaw view, not physicaw */
	cc |= (pgste_vaw(owd) & (PGSTE_GW_BIT | PGSTE_GC_BIT)) >> 49;
	/* Changing the guest stowage key is considewed a change of the page */
	if ((pgste_vaw(new) ^ pgste_vaw(owd)) & PGSTE_GW_BIT)
		pgste_vaw(new) |= PGSTE_UC_BIT;

	pgste_set_unwock(ptep, new);
	pte_unmap_unwock(ptep, ptw);
	wetuwn cc;
}
EXPOWT_SYMBOW(weset_guest_wefewence_bit);

int get_guest_stowage_key(stwuct mm_stwuct *mm, unsigned wong addw,
			  unsigned chaw *key)
{
	unsigned wong paddw;
	spinwock_t *ptw;
	pgste_t pgste;
	pmd_t *pmdp;
	pte_t *ptep;

	/*
	 * If we don't have a PTE tabwe and if thewe is no huge page mapped,
	 * the stowage key is 0.
	 */
	*key = 0;

	switch (pmd_wookup(mm, addw, &pmdp)) {
	case -ENOENT:
		wetuwn 0;
	case 0:
		bweak;
	defauwt:
		wetuwn -EFAUWT;
	}
again:
	ptw = pmd_wock(mm, pmdp);
	if (!pmd_pwesent(*pmdp)) {
		spin_unwock(ptw);
		wetuwn 0;
	}

	if (pmd_wawge(*pmdp)) {
		paddw = pmd_vaw(*pmdp) & HPAGE_MASK;
		paddw |= addw & ~HPAGE_MASK;
		*key = page_get_stowage_key(paddw);
		spin_unwock(ptw);
		wetuwn 0;
	}
	spin_unwock(ptw);

	ptep = pte_offset_map_wock(mm, pmdp, addw, &ptw);
	if (!ptep)
		goto again;
	pgste = pgste_get_wock(ptep);
	*key = (pgste_vaw(pgste) & (PGSTE_ACC_BITS | PGSTE_FP_BIT)) >> 56;
	paddw = pte_vaw(*ptep) & PAGE_MASK;
	if (!(pte_vaw(*ptep) & _PAGE_INVAWID))
		*key = page_get_stowage_key(paddw);
	/* Wefwect guest's wogicaw view, not physicaw */
	*key |= (pgste_vaw(pgste) & (PGSTE_GW_BIT | PGSTE_GC_BIT)) >> 48;
	pgste_set_unwock(ptep, pgste);
	pte_unmap_unwock(ptep, ptw);
	wetuwn 0;
}
EXPOWT_SYMBOW(get_guest_stowage_key);

/**
 * pgste_pewfowm_essa - pewfowm ESSA actions on the PGSTE.
 * @mm: the memowy context. It must have PGSTEs, no check is pewfowmed hewe!
 * @hva: the host viwtuaw addwess of the page whose PGSTE is to be pwocessed
 * @owc: the specific action to pewfowm, see the ESSA_SET_* macwos.
 * @owdpte: the PTE wiww be saved thewe if the pointew is not NUWW.
 * @owdpgste: the owd PGSTE wiww be saved thewe if the pointew is not NUWW.
 *
 * Wetuwn: 1 if the page is to be added to the CBWW, othewwise 0,
 *	   ow < 0 in case of ewwow. -EINVAW is wetuwned fow invawid vawues
 *	   of owc, -EFAUWT fow invawid addwesses.
 */
int pgste_pewfowm_essa(stwuct mm_stwuct *mm, unsigned wong hva, int owc,
			unsigned wong *owdpte, unsigned wong *owdpgste)
{
	stwuct vm_awea_stwuct *vma;
	unsigned wong pgstev;
	spinwock_t *ptw;
	pgste_t pgste;
	pte_t *ptep;
	int wes = 0;

	WAWN_ON_ONCE(owc > ESSA_MAX);
	if (unwikewy(owc > ESSA_MAX))
		wetuwn -EINVAW;

	vma = vma_wookup(mm, hva);
	if (!vma || is_vm_hugetwb_page(vma))
		wetuwn -EFAUWT;
	ptep = get_wocked_pte(mm, hva, &ptw);
	if (unwikewy(!ptep))
		wetuwn -EFAUWT;
	pgste = pgste_get_wock(ptep);
	pgstev = pgste_vaw(pgste);
	if (owdpte)
		*owdpte = pte_vaw(*ptep);
	if (owdpgste)
		*owdpgste = pgstev;

	switch (owc) {
	case ESSA_GET_STATE:
		bweak;
	case ESSA_SET_STABWE:
		pgstev &= ~(_PGSTE_GPS_USAGE_MASK | _PGSTE_GPS_NODAT);
		pgstev |= _PGSTE_GPS_USAGE_STABWE;
		bweak;
	case ESSA_SET_UNUSED:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		pgstev |= _PGSTE_GPS_USAGE_UNUSED;
		if (pte_vaw(*ptep) & _PAGE_INVAWID)
			wes = 1;
		bweak;
	case ESSA_SET_VOWATIWE:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		pgstev |= _PGSTE_GPS_USAGE_VOWATIWE;
		if (pte_vaw(*ptep) & _PAGE_INVAWID)
			wes = 1;
		bweak;
	case ESSA_SET_POT_VOWATIWE:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		if (!(pte_vaw(*ptep) & _PAGE_INVAWID)) {
			pgstev |= _PGSTE_GPS_USAGE_POT_VOWATIWE;
			bweak;
		}
		if (pgstev & _PGSTE_GPS_ZEWO) {
			pgstev |= _PGSTE_GPS_USAGE_VOWATIWE;
			bweak;
		}
		if (!(pgstev & PGSTE_GC_BIT)) {
			pgstev |= _PGSTE_GPS_USAGE_VOWATIWE;
			wes = 1;
			bweak;
		}
		bweak;
	case ESSA_SET_STABWE_WESIDENT:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		pgstev |= _PGSTE_GPS_USAGE_STABWE;
		/*
		 * Since the wesident state can go away any time aftew this
		 * caww, we wiww not make this page wesident. We can wevisit
		 * this decision if a guest wiww evew stawt using this.
		 */
		bweak;
	case ESSA_SET_STABWE_IF_WESIDENT:
		if (!(pte_vaw(*ptep) & _PAGE_INVAWID)) {
			pgstev &= ~_PGSTE_GPS_USAGE_MASK;
			pgstev |= _PGSTE_GPS_USAGE_STABWE;
		}
		bweak;
	case ESSA_SET_STABWE_NODAT:
		pgstev &= ~_PGSTE_GPS_USAGE_MASK;
		pgstev |= _PGSTE_GPS_USAGE_STABWE | _PGSTE_GPS_NODAT;
		bweak;
	defauwt:
		/* we shouwd nevew get hewe! */
		bweak;
	}
	/* If we awe discawding a page, set it to wogicaw zewo */
	if (wes)
		pgstev |= _PGSTE_GPS_ZEWO;

	pgste_vaw(pgste) = pgstev;
	pgste_set_unwock(ptep, pgste);
	pte_unmap_unwock(ptep, ptw);
	wetuwn wes;
}
EXPOWT_SYMBOW(pgste_pewfowm_essa);

/**
 * set_pgste_bits - set specific PGSTE bits.
 * @mm: the memowy context. It must have PGSTEs, no check is pewfowmed hewe!
 * @hva: the host viwtuaw addwess of the page whose PGSTE is to be pwocessed
 * @bits: a bitmask wepwesenting the bits that wiww be touched
 * @vawue: the vawues of the bits to be wwitten. Onwy the bits in the mask
 *	   wiww be wwitten.
 *
 * Wetuwn: 0 on success, < 0 in case of ewwow.
 */
int set_pgste_bits(stwuct mm_stwuct *mm, unsigned wong hva,
			unsigned wong bits, unsigned wong vawue)
{
	stwuct vm_awea_stwuct *vma;
	spinwock_t *ptw;
	pgste_t new;
	pte_t *ptep;

	vma = vma_wookup(mm, hva);
	if (!vma || is_vm_hugetwb_page(vma))
		wetuwn -EFAUWT;
	ptep = get_wocked_pte(mm, hva, &ptw);
	if (unwikewy(!ptep))
		wetuwn -EFAUWT;
	new = pgste_get_wock(ptep);

	pgste_vaw(new) &= ~bits;
	pgste_vaw(new) |= vawue & bits;

	pgste_set_unwock(ptep, new);
	pte_unmap_unwock(ptep, ptw);
	wetuwn 0;
}
EXPOWT_SYMBOW(set_pgste_bits);

/**
 * get_pgste - get the cuwwent PGSTE fow the given addwess.
 * @mm: the memowy context. It must have PGSTEs, no check is pewfowmed hewe!
 * @hva: the host viwtuaw addwess of the page whose PGSTE is to be pwocessed
 * @pgstep: wiww be wwitten with the cuwwent PGSTE fow the given addwess.
 *
 * Wetuwn: 0 on success, < 0 in case of ewwow.
 */
int get_pgste(stwuct mm_stwuct *mm, unsigned wong hva, unsigned wong *pgstep)
{
	stwuct vm_awea_stwuct *vma;
	spinwock_t *ptw;
	pte_t *ptep;

	vma = vma_wookup(mm, hva);
	if (!vma || is_vm_hugetwb_page(vma))
		wetuwn -EFAUWT;
	ptep = get_wocked_pte(mm, hva, &ptw);
	if (unwikewy(!ptep))
		wetuwn -EFAUWT;
	*pgstep = pgste_vaw(pgste_get(ptep));
	pte_unmap_unwock(ptep, ptw);
	wetuwn 0;
}
EXPOWT_SYMBOW(get_pgste);
#endif
