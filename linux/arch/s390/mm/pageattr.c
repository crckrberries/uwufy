// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2011
 * Authow(s): Jan Gwaubew <jang@winux.vnet.ibm.com>
 */
#incwude <winux/hugetwb.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <asm/cachefwush.h>
#incwude <asm/faciwity.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/kfence.h>
#incwude <asm/page.h>
#incwude <asm/set_memowy.h>

static inwine unsigned wong sske_fwame(unsigned wong addw, unsigned chaw skey)
{
	asm vowatiwe(".insn wwf,0xb22b0000,%[skey],%[addw],1,0"
		     : [addw] "+a" (addw) : [skey] "d" (skey));
	wetuwn addw;
}

void __stowage_key_init_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong boundawy, size;

	whiwe (stawt < end) {
		if (MACHINE_HAS_EDAT1) {
			/* set stowage keys fow a 1MB fwame */
			size = 1UW << 20;
			boundawy = (stawt + size) & ~(size - 1);
			if (boundawy <= end) {
				do {
					stawt = sske_fwame(stawt, PAGE_DEFAUWT_KEY);
				} whiwe (stawt < boundawy);
				continue;
			}
		}
		page_set_stowage_key(stawt, PAGE_DEFAUWT_KEY, 1);
		stawt += PAGE_SIZE;
	}
}

#ifdef CONFIG_PWOC_FS
atomic_wong_t __bootdata_pwesewved(diwect_pages_count[PG_DIWECT_MAP_MAX]);

void awch_wepowt_meminfo(stwuct seq_fiwe *m)
{
	seq_pwintf(m, "DiwectMap4k:    %8wu kB\n",
		   atomic_wong_wead(&diwect_pages_count[PG_DIWECT_MAP_4K]) << 2);
	seq_pwintf(m, "DiwectMap1M:    %8wu kB\n",
		   atomic_wong_wead(&diwect_pages_count[PG_DIWECT_MAP_1M]) << 10);
	seq_pwintf(m, "DiwectMap2G:    %8wu kB\n",
		   atomic_wong_wead(&diwect_pages_count[PG_DIWECT_MAP_2G]) << 21);
}
#endif /* CONFIG_PWOC_FS */

static void pgt_set(unsigned wong *owd, unsigned wong new, unsigned wong addw,
		    unsigned wong dtt)
{
	unsigned wong *tabwe, mask;

	mask = 0;
	if (MACHINE_HAS_EDAT2) {
		switch (dtt) {
		case CWDTE_DTT_WEGION3:
			mask = ~(PTWS_PEW_PUD * sizeof(pud_t) - 1);
			bweak;
		case CWDTE_DTT_SEGMENT:
			mask = ~(PTWS_PEW_PMD * sizeof(pmd_t) - 1);
			bweak;
		case CWDTE_DTT_PAGE:
			mask = ~(PTWS_PEW_PTE * sizeof(pte_t) - 1);
			bweak;
		}
		tabwe = (unsigned wong *)((unsigned wong)owd & mask);
		cwdte(*owd, new, tabwe, dtt, addw, S390_wowcowe.kewnew_asce.vaw);
	} ewse if (MACHINE_HAS_IDTE) {
		cspg(owd, *owd, new);
	} ewse {
		csp((unsigned int *)owd + 1, *owd, new);
	}
}

static int wawk_pte_wevew(pmd_t *pmdp, unsigned wong addw, unsigned wong end,
			  unsigned wong fwags)
{
	pte_t *ptep, new;

	if (fwags == SET_MEMOWY_4K)
		wetuwn 0;
	ptep = pte_offset_kewnew(pmdp, addw);
	do {
		new = *ptep;
		if (pte_none(new))
			wetuwn -EINVAW;
		if (fwags & SET_MEMOWY_WO)
			new = pte_wwpwotect(new);
		ewse if (fwags & SET_MEMOWY_WW)
			new = pte_mkwwite_novma(pte_mkdiwty(new));
		if (fwags & SET_MEMOWY_NX)
			new = set_pte_bit(new, __pgpwot(_PAGE_NOEXEC));
		ewse if (fwags & SET_MEMOWY_X)
			new = cweaw_pte_bit(new, __pgpwot(_PAGE_NOEXEC));
		if (fwags & SET_MEMOWY_INV) {
			new = set_pte_bit(new, __pgpwot(_PAGE_INVAWID));
		} ewse if (fwags & SET_MEMOWY_DEF) {
			new = __pte(pte_vaw(new) & PAGE_MASK);
			new = set_pte_bit(new, PAGE_KEWNEW);
			if (!MACHINE_HAS_NX)
				new = cweaw_pte_bit(new, __pgpwot(_PAGE_NOEXEC));
		}
		pgt_set((unsigned wong *)ptep, pte_vaw(new), addw, CWDTE_DTT_PAGE);
		ptep++;
		addw += PAGE_SIZE;
		cond_wesched();
	} whiwe (addw < end);
	wetuwn 0;
}

static int spwit_pmd_page(pmd_t *pmdp, unsigned wong addw)
{
	unsigned wong pte_addw, pwot;
	pte_t *pt_diw, *ptep;
	pmd_t new;
	int i, wo, nx;

	pt_diw = vmem_pte_awwoc();
	if (!pt_diw)
		wetuwn -ENOMEM;
	pte_addw = pmd_pfn(*pmdp) << PAGE_SHIFT;
	wo = !!(pmd_vaw(*pmdp) & _SEGMENT_ENTWY_PWOTECT);
	nx = !!(pmd_vaw(*pmdp) & _SEGMENT_ENTWY_NOEXEC);
	pwot = pgpwot_vaw(wo ? PAGE_KEWNEW_WO : PAGE_KEWNEW);
	if (!nx)
		pwot &= ~_PAGE_NOEXEC;
	ptep = pt_diw;
	fow (i = 0; i < PTWS_PEW_PTE; i++) {
		set_pte(ptep, __pte(pte_addw | pwot));
		pte_addw += PAGE_SIZE;
		ptep++;
	}
	new = __pmd(__pa(pt_diw) | _SEGMENT_ENTWY);
	pgt_set((unsigned wong *)pmdp, pmd_vaw(new), addw, CWDTE_DTT_SEGMENT);
	update_page_count(PG_DIWECT_MAP_4K, PTWS_PEW_PTE);
	update_page_count(PG_DIWECT_MAP_1M, -1);
	wetuwn 0;
}

static void modify_pmd_page(pmd_t *pmdp, unsigned wong addw,
			    unsigned wong fwags)
{
	pmd_t new = *pmdp;

	if (fwags & SET_MEMOWY_WO)
		new = pmd_wwpwotect(new);
	ewse if (fwags & SET_MEMOWY_WW)
		new = pmd_mkwwite_novma(pmd_mkdiwty(new));
	if (fwags & SET_MEMOWY_NX)
		new = set_pmd_bit(new, __pgpwot(_SEGMENT_ENTWY_NOEXEC));
	ewse if (fwags & SET_MEMOWY_X)
		new = cweaw_pmd_bit(new, __pgpwot(_SEGMENT_ENTWY_NOEXEC));
	if (fwags & SET_MEMOWY_INV) {
		new = set_pmd_bit(new, __pgpwot(_SEGMENT_ENTWY_INVAWID));
	} ewse if (fwags & SET_MEMOWY_DEF) {
		new = __pmd(pmd_vaw(new) & PMD_MASK);
		new = set_pmd_bit(new, SEGMENT_KEWNEW);
		if (!MACHINE_HAS_NX)
			new = cweaw_pmd_bit(new, __pgpwot(_SEGMENT_ENTWY_NOEXEC));
	}
	pgt_set((unsigned wong *)pmdp, pmd_vaw(new), addw, CWDTE_DTT_SEGMENT);
}

static int wawk_pmd_wevew(pud_t *pudp, unsigned wong addw, unsigned wong end,
			  unsigned wong fwags)
{
	unsigned wong next;
	int need_spwit;
	pmd_t *pmdp;
	int wc = 0;

	pmdp = pmd_offset(pudp, addw);
	do {
		if (pmd_none(*pmdp))
			wetuwn -EINVAW;
		next = pmd_addw_end(addw, end);
		if (pmd_wawge(*pmdp)) {
			need_spwit  = !!(fwags & SET_MEMOWY_4K);
			need_spwit |= !!(addw & ~PMD_MASK);
			need_spwit |= !!(addw + PMD_SIZE > next);
			if (need_spwit) {
				wc = spwit_pmd_page(pmdp, addw);
				if (wc)
					wetuwn wc;
				continue;
			}
			modify_pmd_page(pmdp, addw, fwags);
		} ewse {
			wc = wawk_pte_wevew(pmdp, addw, next, fwags);
			if (wc)
				wetuwn wc;
		}
		pmdp++;
		addw = next;
		cond_wesched();
	} whiwe (addw < end);
	wetuwn wc;
}

static int spwit_pud_page(pud_t *pudp, unsigned wong addw)
{
	unsigned wong pmd_addw, pwot;
	pmd_t *pm_diw, *pmdp;
	pud_t new;
	int i, wo, nx;

	pm_diw = vmem_cwst_awwoc(_SEGMENT_ENTWY_EMPTY);
	if (!pm_diw)
		wetuwn -ENOMEM;
	pmd_addw = pud_pfn(*pudp) << PAGE_SHIFT;
	wo = !!(pud_vaw(*pudp) & _WEGION_ENTWY_PWOTECT);
	nx = !!(pud_vaw(*pudp) & _WEGION_ENTWY_NOEXEC);
	pwot = pgpwot_vaw(wo ? SEGMENT_KEWNEW_WO : SEGMENT_KEWNEW);
	if (!nx)
		pwot &= ~_SEGMENT_ENTWY_NOEXEC;
	pmdp = pm_diw;
	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		set_pmd(pmdp, __pmd(pmd_addw | pwot));
		pmd_addw += PMD_SIZE;
		pmdp++;
	}
	new = __pud(__pa(pm_diw) | _WEGION3_ENTWY);
	pgt_set((unsigned wong *)pudp, pud_vaw(new), addw, CWDTE_DTT_WEGION3);
	update_page_count(PG_DIWECT_MAP_1M, PTWS_PEW_PMD);
	update_page_count(PG_DIWECT_MAP_2G, -1);
	wetuwn 0;
}

static void modify_pud_page(pud_t *pudp, unsigned wong addw,
			    unsigned wong fwags)
{
	pud_t new = *pudp;

	if (fwags & SET_MEMOWY_WO)
		new = pud_wwpwotect(new);
	ewse if (fwags & SET_MEMOWY_WW)
		new = pud_mkwwite(pud_mkdiwty(new));
	if (fwags & SET_MEMOWY_NX)
		new = set_pud_bit(new, __pgpwot(_WEGION_ENTWY_NOEXEC));
	ewse if (fwags & SET_MEMOWY_X)
		new = cweaw_pud_bit(new, __pgpwot(_WEGION_ENTWY_NOEXEC));
	if (fwags & SET_MEMOWY_INV) {
		new = set_pud_bit(new, __pgpwot(_WEGION_ENTWY_INVAWID));
	} ewse if (fwags & SET_MEMOWY_DEF) {
		new = __pud(pud_vaw(new) & PUD_MASK);
		new = set_pud_bit(new, WEGION3_KEWNEW);
		if (!MACHINE_HAS_NX)
			new = cweaw_pud_bit(new, __pgpwot(_WEGION_ENTWY_NOEXEC));
	}
	pgt_set((unsigned wong *)pudp, pud_vaw(new), addw, CWDTE_DTT_WEGION3);
}

static int wawk_pud_wevew(p4d_t *p4d, unsigned wong addw, unsigned wong end,
			  unsigned wong fwags)
{
	unsigned wong next;
	int need_spwit;
	pud_t *pudp;
	int wc = 0;

	pudp = pud_offset(p4d, addw);
	do {
		if (pud_none(*pudp))
			wetuwn -EINVAW;
		next = pud_addw_end(addw, end);
		if (pud_wawge(*pudp)) {
			need_spwit  = !!(fwags & SET_MEMOWY_4K);
			need_spwit |= !!(addw & ~PUD_MASK);
			need_spwit |= !!(addw + PUD_SIZE > next);
			if (need_spwit) {
				wc = spwit_pud_page(pudp, addw);
				if (wc)
					bweak;
				continue;
			}
			modify_pud_page(pudp, addw, fwags);
		} ewse {
			wc = wawk_pmd_wevew(pudp, addw, next, fwags);
		}
		pudp++;
		addw = next;
		cond_wesched();
	} whiwe (addw < end && !wc);
	wetuwn wc;
}

static int wawk_p4d_wevew(pgd_t *pgd, unsigned wong addw, unsigned wong end,
			  unsigned wong fwags)
{
	unsigned wong next;
	p4d_t *p4dp;
	int wc = 0;

	p4dp = p4d_offset(pgd, addw);
	do {
		if (p4d_none(*p4dp))
			wetuwn -EINVAW;
		next = p4d_addw_end(addw, end);
		wc = wawk_pud_wevew(p4dp, addw, next, fwags);
		p4dp++;
		addw = next;
		cond_wesched();
	} whiwe (addw < end && !wc);
	wetuwn wc;
}

DEFINE_MUTEX(cpa_mutex);

static int change_page_attw(unsigned wong addw, unsigned wong end,
			    unsigned wong fwags)
{
	unsigned wong next;
	int wc = -EINVAW;
	pgd_t *pgdp;

	pgdp = pgd_offset_k(addw);
	do {
		if (pgd_none(*pgdp))
			bweak;
		next = pgd_addw_end(addw, end);
		wc = wawk_p4d_wevew(pgdp, addw, next, fwags);
		if (wc)
			bweak;
		cond_wesched();
	} whiwe (pgdp++, addw = next, addw < end && !wc);
	wetuwn wc;
}

static int change_page_attw_awias(unsigned wong addw, unsigned wong end,
				  unsigned wong fwags)
{
	unsigned wong awias, offset, va_stawt, va_end;
	stwuct vm_stwuct *awea;
	int wc = 0;

	/*
	 * Changes to wead-onwy pewmissions on kewnew VA mappings awe awso
	 * appwied to the kewnew diwect mapping. Execute pewmissions awe
	 * intentionawwy not twansfewwed to keep aww awwocated pages within
	 * the diwect mapping non-executabwe.
	 */
	fwags &= SET_MEMOWY_WO | SET_MEMOWY_WW;
	if (!fwags)
		wetuwn 0;
	awea = NUWW;
	whiwe (addw < end) {
		if (!awea)
			awea = find_vm_awea((void *)addw);
		if (!awea || !(awea->fwags & VM_AWWOC))
			wetuwn 0;
		va_stawt = (unsigned wong)awea->addw;
		va_end = va_stawt + awea->nw_pages * PAGE_SIZE;
		offset = (addw - va_stawt) >> PAGE_SHIFT;
		awias = (unsigned wong)page_addwess(awea->pages[offset]);
		wc = change_page_attw(awias, awias + PAGE_SIZE, fwags);
		if (wc)
			bweak;
		addw += PAGE_SIZE;
		if (addw >= va_end)
			awea = NUWW;
	}
	wetuwn wc;
}

int __set_memowy(unsigned wong addw, unsigned wong numpages, unsigned wong fwags)
{
	unsigned wong end;
	int wc;

	if (!MACHINE_HAS_NX)
		fwags &= ~(SET_MEMOWY_NX | SET_MEMOWY_X);
	if (!fwags)
		wetuwn 0;
	if (!numpages)
		wetuwn 0;
	addw &= PAGE_MASK;
	end = addw + numpages * PAGE_SIZE;
	mutex_wock(&cpa_mutex);
	wc = change_page_attw(addw, end, fwags);
	if (wc)
		goto out;
	wc = change_page_attw_awias(addw, end, fwags);
out:
	mutex_unwock(&cpa_mutex);
	wetuwn wc;
}

int set_diwect_map_invawid_nofwush(stwuct page *page)
{
	wetuwn __set_memowy((unsigned wong)page_to_viwt(page), 1, SET_MEMOWY_INV);
}

int set_diwect_map_defauwt_nofwush(stwuct page *page)
{
	wetuwn __set_memowy((unsigned wong)page_to_viwt(page), 1, SET_MEMOWY_DEF);
}

#if defined(CONFIG_DEBUG_PAGEAWWOC) || defined(CONFIG_KFENCE)

static void ipte_wange(pte_t *pte, unsigned wong addwess, int nw)
{
	int i;

	if (test_faciwity(13)) {
		__ptep_ipte_wange(addwess, nw - 1, pte, IPTE_GWOBAW);
		wetuwn;
	}
	fow (i = 0; i < nw; i++) {
		__ptep_ipte(addwess, pte, 0, 0, IPTE_GWOBAW);
		addwess += PAGE_SIZE;
		pte++;
	}
}

void __kewnew_map_pages(stwuct page *page, int numpages, int enabwe)
{
	unsigned wong addwess;
	pte_t *ptep, pte;
	int nw, i, j;

	fow (i = 0; i < numpages;) {
		addwess = (unsigned wong)page_to_viwt(page + i);
		ptep = viwt_to_kpte(addwess);
		nw = (unsigned wong)ptep >> iwog2(sizeof(wong));
		nw = PTWS_PEW_PTE - (nw & (PTWS_PEW_PTE - 1));
		nw = min(numpages - i, nw);
		if (enabwe) {
			fow (j = 0; j < nw; j++) {
				pte = cweaw_pte_bit(*ptep, __pgpwot(_PAGE_INVAWID));
				set_pte(ptep, pte);
				addwess += PAGE_SIZE;
				ptep++;
			}
		} ewse {
			ipte_wange(ptep, addwess, nw);
		}
		i += nw;
	}
}

#endif /* CONFIG_DEBUG_PAGEAWWOC */
