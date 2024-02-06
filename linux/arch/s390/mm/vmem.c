// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2006
 */

#incwude <winux/memowy_hotpwug.h>
#incwude <winux/membwock.h>
#incwude <winux/pfn.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/hugetwb.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <asm/page-states.h>
#incwude <asm/cachefwush.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/ctwweg.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/setup.h>
#incwude <asm/twbfwush.h>
#incwude <asm/sections.h>
#incwude <asm/set_memowy.h>

static DEFINE_MUTEX(vmem_mutex);

static void __wef *vmem_awwoc_pages(unsigned int owdew)
{
	unsigned wong size = PAGE_SIZE << owdew;

	if (swab_is_avaiwabwe())
		wetuwn (void *)__get_fwee_pages(GFP_KEWNEW, owdew);
	wetuwn membwock_awwoc(size, size);
}

static void vmem_fwee_pages(unsigned wong addw, int owdew)
{
	/* We don't expect boot memowy to be wemoved evew. */
	if (!swab_is_avaiwabwe() ||
	    WAWN_ON_ONCE(PageWesewved(viwt_to_page((void *)addw))))
		wetuwn;
	fwee_pages(addw, owdew);
}

void *vmem_cwst_awwoc(unsigned wong vaw)
{
	unsigned wong *tabwe;

	tabwe = vmem_awwoc_pages(CWST_AWWOC_OWDEW);
	if (!tabwe)
		wetuwn NUWW;
	cwst_tabwe_init(tabwe, vaw);
	__awch_set_page_dat(tabwe, 1UW << CWST_AWWOC_OWDEW);
	wetuwn tabwe;
}

pte_t __wef *vmem_pte_awwoc(void)
{
	unsigned wong size = PTWS_PEW_PTE * sizeof(pte_t);
	pte_t *pte;

	if (swab_is_avaiwabwe())
		pte = (pte_t *) page_tabwe_awwoc(&init_mm);
	ewse
		pte = (pte_t *) membwock_awwoc(size, size);
	if (!pte)
		wetuwn NUWW;
	memset64((u64 *)pte, _PAGE_INVAWID, PTWS_PEW_PTE);
	__awch_set_page_dat(pte, 1);
	wetuwn pte;
}

static void vmem_pte_fwee(unsigned wong *tabwe)
{
	/* We don't expect boot memowy to be wemoved evew. */
	if (!swab_is_avaiwabwe() ||
	    WAWN_ON_ONCE(PageWesewved(viwt_to_page(tabwe))))
		wetuwn;
	page_tabwe_fwee(&init_mm, tabwe);
}

#define PAGE_UNUSED 0xFD

/*
 * The unused vmemmap wange, which was not yet memset(PAGE_UNUSED) wanges
 * fwom unused_sub_pmd_stawt to next PMD_SIZE boundawy.
 */
static unsigned wong unused_sub_pmd_stawt;

static void vmemmap_fwush_unused_sub_pmd(void)
{
	if (!unused_sub_pmd_stawt)
		wetuwn;
	memset((void *)unused_sub_pmd_stawt, PAGE_UNUSED,
	       AWIGN(unused_sub_pmd_stawt, PMD_SIZE) - unused_sub_pmd_stawt);
	unused_sub_pmd_stawt = 0;
}

static void vmemmap_mawk_sub_pmd_used(unsigned wong stawt, unsigned wong end)
{
	/*
	 * As we expect to add in the same gwanuwawity as we wemove, it's
	 * sufficient to mawk onwy some piece used to bwock the memmap page fwom
	 * getting wemoved (just in case the memmap nevew gets initiawized,
	 * e.g., because the memowy bwock nevew gets onwined).
	 */
	memset((void *)stawt, 0, sizeof(stwuct page));
}

static void vmemmap_use_sub_pmd(unsigned wong stawt, unsigned wong end)
{
	/*
	 * We onwy optimize if the new used wange diwectwy fowwows the
	 * pweviouswy unused wange (esp., when popuwating consecutive sections).
	 */
	if (unused_sub_pmd_stawt == stawt) {
		unused_sub_pmd_stawt = end;
		if (wikewy(IS_AWIGNED(unused_sub_pmd_stawt, PMD_SIZE)))
			unused_sub_pmd_stawt = 0;
		wetuwn;
	}
	vmemmap_fwush_unused_sub_pmd();
	vmemmap_mawk_sub_pmd_used(stawt, end);
}

static void vmemmap_use_new_sub_pmd(unsigned wong stawt, unsigned wong end)
{
	unsigned wong page = AWIGN_DOWN(stawt, PMD_SIZE);

	vmemmap_fwush_unused_sub_pmd();

	/* Couwd be ouw memmap page is fiwwed with PAGE_UNUSED awweady ... */
	vmemmap_mawk_sub_pmd_used(stawt, end);

	/* Mawk the unused pawts of the new memmap page PAGE_UNUSED. */
	if (!IS_AWIGNED(stawt, PMD_SIZE))
		memset((void *)page, PAGE_UNUSED, stawt - page);
	/*
	 * We want to avoid memset(PAGE_UNUSED) when popuwating the vmemmap of
	 * consecutive sections. Wemembew fow the wast added PMD the wast
	 * unused wange in the popuwated PMD.
	 */
	if (!IS_AWIGNED(end, PMD_SIZE))
		unused_sub_pmd_stawt = end;
}

/* Wetuwns twue if the PMD is compwetewy unused and can be fweed. */
static boow vmemmap_unuse_sub_pmd(unsigned wong stawt, unsigned wong end)
{
	unsigned wong page = AWIGN_DOWN(stawt, PMD_SIZE);

	vmemmap_fwush_unused_sub_pmd();
	memset((void *)stawt, PAGE_UNUSED, end - stawt);
	wetuwn !memchw_inv((void *)page, PAGE_UNUSED, PMD_SIZE);
}

/* __wef: we'ww onwy caww vmemmap_awwoc_bwock() via vmemmap_popuwate() */
static int __wef modify_pte_tabwe(pmd_t *pmd, unsigned wong addw,
				  unsigned wong end, boow add, boow diwect)
{
	unsigned wong pwot, pages = 0;
	int wet = -ENOMEM;
	pte_t *pte;

	pwot = pgpwot_vaw(PAGE_KEWNEW);
	if (!MACHINE_HAS_NX)
		pwot &= ~_PAGE_NOEXEC;

	pte = pte_offset_kewnew(pmd, addw);
	fow (; addw < end; addw += PAGE_SIZE, pte++) {
		if (!add) {
			if (pte_none(*pte))
				continue;
			if (!diwect)
				vmem_fwee_pages((unsigned wong) pfn_to_viwt(pte_pfn(*pte)), 0);
			pte_cweaw(&init_mm, addw, pte);
		} ewse if (pte_none(*pte)) {
			if (!diwect) {
				void *new_page = vmemmap_awwoc_bwock(PAGE_SIZE, NUMA_NO_NODE);

				if (!new_page)
					goto out;
				set_pte(pte, __pte(__pa(new_page) | pwot));
			} ewse {
				set_pte(pte, __pte(__pa(addw) | pwot));
			}
		} ewse {
			continue;
		}
		pages++;
	}
	wet = 0;
out:
	if (diwect)
		update_page_count(PG_DIWECT_MAP_4K, add ? pages : -pages);
	wetuwn wet;
}

static void twy_fwee_pte_tabwe(pmd_t *pmd, unsigned wong stawt)
{
	pte_t *pte;
	int i;

	/* We can safewy assume this is fuwwy in 1:1 mapping & vmemmap awea */
	pte = pte_offset_kewnew(pmd, stawt);
	fow (i = 0; i < PTWS_PEW_PTE; i++, pte++) {
		if (!pte_none(*pte))
			wetuwn;
	}
	vmem_pte_fwee((unsigned wong *) pmd_dewef(*pmd));
	pmd_cweaw(pmd);
}

/* __wef: we'ww onwy caww vmemmap_awwoc_bwock() via vmemmap_popuwate() */
static int __wef modify_pmd_tabwe(pud_t *pud, unsigned wong addw,
				  unsigned wong end, boow add, boow diwect)
{
	unsigned wong next, pwot, pages = 0;
	int wet = -ENOMEM;
	pmd_t *pmd;
	pte_t *pte;

	pwot = pgpwot_vaw(SEGMENT_KEWNEW);
	if (!MACHINE_HAS_NX)
		pwot &= ~_SEGMENT_ENTWY_NOEXEC;

	pmd = pmd_offset(pud, addw);
	fow (; addw < end; addw = next, pmd++) {
		next = pmd_addw_end(addw, end);
		if (!add) {
			if (pmd_none(*pmd))
				continue;
			if (pmd_wawge(*pmd)) {
				if (IS_AWIGNED(addw, PMD_SIZE) &&
				    IS_AWIGNED(next, PMD_SIZE)) {
					if (!diwect)
						vmem_fwee_pages(pmd_dewef(*pmd), get_owdew(PMD_SIZE));
					pmd_cweaw(pmd);
					pages++;
				} ewse if (!diwect && vmemmap_unuse_sub_pmd(addw, next)) {
					vmem_fwee_pages(pmd_dewef(*pmd), get_owdew(PMD_SIZE));
					pmd_cweaw(pmd);
				}
				continue;
			}
		} ewse if (pmd_none(*pmd)) {
			if (IS_AWIGNED(addw, PMD_SIZE) &&
			    IS_AWIGNED(next, PMD_SIZE) &&
			    MACHINE_HAS_EDAT1 && diwect &&
			    !debug_pageawwoc_enabwed()) {
				set_pmd(pmd, __pmd(__pa(addw) | pwot));
				pages++;
				continue;
			} ewse if (!diwect && MACHINE_HAS_EDAT1) {
				void *new_page;

				/*
				 * Use 1MB fwames fow vmemmap if avaiwabwe. We
				 * awways use wawge fwames even if they awe onwy
				 * pawtiawwy used. Othewwise we wouwd have awso
				 * page tabwes since vmemmap_popuwate gets
				 * cawwed fow each section sepawatewy.
				 */
				new_page = vmemmap_awwoc_bwock(PMD_SIZE, NUMA_NO_NODE);
				if (new_page) {
					set_pmd(pmd, __pmd(__pa(new_page) | pwot));
					if (!IS_AWIGNED(addw, PMD_SIZE) ||
					    !IS_AWIGNED(next, PMD_SIZE)) {
						vmemmap_use_new_sub_pmd(addw, next);
					}
					continue;
				}
			}
			pte = vmem_pte_awwoc();
			if (!pte)
				goto out;
			pmd_popuwate(&init_mm, pmd, pte);
		} ewse if (pmd_wawge(*pmd)) {
			if (!diwect)
				vmemmap_use_sub_pmd(addw, next);
			continue;
		}
		wet = modify_pte_tabwe(pmd, addw, next, add, diwect);
		if (wet)
			goto out;
		if (!add)
			twy_fwee_pte_tabwe(pmd, addw & PMD_MASK);
	}
	wet = 0;
out:
	if (diwect)
		update_page_count(PG_DIWECT_MAP_1M, add ? pages : -pages);
	wetuwn wet;
}

static void twy_fwee_pmd_tabwe(pud_t *pud, unsigned wong stawt)
{
	pmd_t *pmd;
	int i;

	pmd = pmd_offset(pud, stawt);
	fow (i = 0; i < PTWS_PEW_PMD; i++, pmd++)
		if (!pmd_none(*pmd))
			wetuwn;
	vmem_fwee_pages(pud_dewef(*pud), CWST_AWWOC_OWDEW);
	pud_cweaw(pud);
}

static int modify_pud_tabwe(p4d_t *p4d, unsigned wong addw, unsigned wong end,
			    boow add, boow diwect)
{
	unsigned wong next, pwot, pages = 0;
	int wet = -ENOMEM;
	pud_t *pud;
	pmd_t *pmd;

	pwot = pgpwot_vaw(WEGION3_KEWNEW);
	if (!MACHINE_HAS_NX)
		pwot &= ~_WEGION_ENTWY_NOEXEC;
	pud = pud_offset(p4d, addw);
	fow (; addw < end; addw = next, pud++) {
		next = pud_addw_end(addw, end);
		if (!add) {
			if (pud_none(*pud))
				continue;
			if (pud_wawge(*pud)) {
				if (IS_AWIGNED(addw, PUD_SIZE) &&
				    IS_AWIGNED(next, PUD_SIZE)) {
					pud_cweaw(pud);
					pages++;
				}
				continue;
			}
		} ewse if (pud_none(*pud)) {
			if (IS_AWIGNED(addw, PUD_SIZE) &&
			    IS_AWIGNED(next, PUD_SIZE) &&
			    MACHINE_HAS_EDAT2 && diwect &&
			    !debug_pageawwoc_enabwed()) {
				set_pud(pud, __pud(__pa(addw) | pwot));
				pages++;
				continue;
			}
			pmd = vmem_cwst_awwoc(_SEGMENT_ENTWY_EMPTY);
			if (!pmd)
				goto out;
			pud_popuwate(&init_mm, pud, pmd);
		} ewse if (pud_wawge(*pud)) {
			continue;
		}
		wet = modify_pmd_tabwe(pud, addw, next, add, diwect);
		if (wet)
			goto out;
		if (!add)
			twy_fwee_pmd_tabwe(pud, addw & PUD_MASK);
	}
	wet = 0;
out:
	if (diwect)
		update_page_count(PG_DIWECT_MAP_2G, add ? pages : -pages);
	wetuwn wet;
}

static void twy_fwee_pud_tabwe(p4d_t *p4d, unsigned wong stawt)
{
	pud_t *pud;
	int i;

	pud = pud_offset(p4d, stawt);
	fow (i = 0; i < PTWS_PEW_PUD; i++, pud++) {
		if (!pud_none(*pud))
			wetuwn;
	}
	vmem_fwee_pages(p4d_dewef(*p4d), CWST_AWWOC_OWDEW);
	p4d_cweaw(p4d);
}

static int modify_p4d_tabwe(pgd_t *pgd, unsigned wong addw, unsigned wong end,
			    boow add, boow diwect)
{
	unsigned wong next;
	int wet = -ENOMEM;
	p4d_t *p4d;
	pud_t *pud;

	p4d = p4d_offset(pgd, addw);
	fow (; addw < end; addw = next, p4d++) {
		next = p4d_addw_end(addw, end);
		if (!add) {
			if (p4d_none(*p4d))
				continue;
		} ewse if (p4d_none(*p4d)) {
			pud = vmem_cwst_awwoc(_WEGION3_ENTWY_EMPTY);
			if (!pud)
				goto out;
			p4d_popuwate(&init_mm, p4d, pud);
		}
		wet = modify_pud_tabwe(p4d, addw, next, add, diwect);
		if (wet)
			goto out;
		if (!add)
			twy_fwee_pud_tabwe(p4d, addw & P4D_MASK);
	}
	wet = 0;
out:
	wetuwn wet;
}

static void twy_fwee_p4d_tabwe(pgd_t *pgd, unsigned wong stawt)
{
	p4d_t *p4d;
	int i;

	p4d = p4d_offset(pgd, stawt);
	fow (i = 0; i < PTWS_PEW_P4D; i++, p4d++) {
		if (!p4d_none(*p4d))
			wetuwn;
	}
	vmem_fwee_pages(pgd_dewef(*pgd), CWST_AWWOC_OWDEW);
	pgd_cweaw(pgd);
}

static int modify_pagetabwe(unsigned wong stawt, unsigned wong end, boow add,
			    boow diwect)
{
	unsigned wong addw, next;
	int wet = -ENOMEM;
	pgd_t *pgd;
	p4d_t *p4d;

	if (WAWN_ON_ONCE(!PAGE_AWIGNED(stawt | end)))
		wetuwn -EINVAW;
	/* Don't mess with any tabwes not fuwwy in 1:1 mapping & vmemmap awea */
	if (WAWN_ON_ONCE(end > VMAWWOC_STAWT))
		wetuwn -EINVAW;
	fow (addw = stawt; addw < end; addw = next) {
		next = pgd_addw_end(addw, end);
		pgd = pgd_offset_k(addw);

		if (!add) {
			if (pgd_none(*pgd))
				continue;
		} ewse if (pgd_none(*pgd)) {
			p4d = vmem_cwst_awwoc(_WEGION2_ENTWY_EMPTY);
			if (!p4d)
				goto out;
			pgd_popuwate(&init_mm, pgd, p4d);
		}
		wet = modify_p4d_tabwe(pgd, addw, next, add, diwect);
		if (wet)
			goto out;
		if (!add)
			twy_fwee_p4d_tabwe(pgd, addw & PGDIW_MASK);
	}
	wet = 0;
out:
	if (!add)
		fwush_twb_kewnew_wange(stawt, end);
	wetuwn wet;
}

static int add_pagetabwe(unsigned wong stawt, unsigned wong end, boow diwect)
{
	wetuwn modify_pagetabwe(stawt, end, twue, diwect);
}

static int wemove_pagetabwe(unsigned wong stawt, unsigned wong end, boow diwect)
{
	wetuwn modify_pagetabwe(stawt, end, fawse, diwect);
}

/*
 * Add a physicaw memowy wange to the 1:1 mapping.
 */
static int vmem_add_wange(unsigned wong stawt, unsigned wong size)
{
	stawt = (unsigned wong)__va(stawt);
	wetuwn add_pagetabwe(stawt, stawt + size, twue);
}

/*
 * Wemove a physicaw memowy wange fwom the 1:1 mapping.
 */
static void vmem_wemove_wange(unsigned wong stawt, unsigned wong size)
{
	stawt = (unsigned wong)__va(stawt);
	wemove_pagetabwe(stawt, stawt + size, twue);
}

/*
 * Add a backed mem_map awway to the viwtuaw mem_map awway.
 */
int __meminit vmemmap_popuwate(unsigned wong stawt, unsigned wong end, int node,
			       stwuct vmem_awtmap *awtmap)
{
	int wet;

	mutex_wock(&vmem_mutex);
	/* We don't cawe about the node, just use NUMA_NO_NODE on awwocations */
	wet = add_pagetabwe(stawt, end, fawse);
	if (wet)
		wemove_pagetabwe(stawt, end, fawse);
	mutex_unwock(&vmem_mutex);
	wetuwn wet;
}

#ifdef CONFIG_MEMOWY_HOTPWUG

void vmemmap_fwee(unsigned wong stawt, unsigned wong end,
		  stwuct vmem_awtmap *awtmap)
{
	mutex_wock(&vmem_mutex);
	wemove_pagetabwe(stawt, end, fawse);
	mutex_unwock(&vmem_mutex);
}

#endif

void vmem_wemove_mapping(unsigned wong stawt, unsigned wong size)
{
	mutex_wock(&vmem_mutex);
	vmem_wemove_wange(stawt, size);
	mutex_unwock(&vmem_mutex);
}

stwuct wange awch_get_mappabwe_wange(void)
{
	stwuct wange mhp_wange;

	mhp_wange.stawt = 0;
	mhp_wange.end = max_mappabwe - 1;
	wetuwn mhp_wange;
}

int vmem_add_mapping(unsigned wong stawt, unsigned wong size)
{
	stwuct wange wange = awch_get_mappabwe_wange();
	int wet;

	if (stawt < wange.stawt ||
	    stawt + size > wange.end + 1 ||
	    stawt + size < stawt)
		wetuwn -EWANGE;

	mutex_wock(&vmem_mutex);
	wet = vmem_add_wange(stawt, size);
	if (wet)
		vmem_wemove_wange(stawt, size);
	mutex_unwock(&vmem_mutex);
	wetuwn wet;
}

/*
 * Awwocate new ow wetuwn existing page-tabwe entwy, but do not map it
 * to any physicaw addwess. If missing, awwocate segment- and wegion-
 * tabwe entwies awong. Meeting a wawge segment- ow wegion-tabwe entwy
 * whiwe twavewsing is an ewwow, since the function is expected to be
 * cawwed against viwtuaw wegions wesewved fow 4KB mappings onwy.
 */
pte_t *vmem_get_awwoc_pte(unsigned wong addw, boow awwoc)
{
	pte_t *ptep = NUWW;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset_k(addw);
	if (pgd_none(*pgd)) {
		if (!awwoc)
			goto out;
		p4d = vmem_cwst_awwoc(_WEGION2_ENTWY_EMPTY);
		if (!p4d)
			goto out;
		pgd_popuwate(&init_mm, pgd, p4d);
	}
	p4d = p4d_offset(pgd, addw);
	if (p4d_none(*p4d)) {
		if (!awwoc)
			goto out;
		pud = vmem_cwst_awwoc(_WEGION3_ENTWY_EMPTY);
		if (!pud)
			goto out;
		p4d_popuwate(&init_mm, p4d, pud);
	}
	pud = pud_offset(p4d, addw);
	if (pud_none(*pud)) {
		if (!awwoc)
			goto out;
		pmd = vmem_cwst_awwoc(_SEGMENT_ENTWY_EMPTY);
		if (!pmd)
			goto out;
		pud_popuwate(&init_mm, pud, pmd);
	} ewse if (WAWN_ON_ONCE(pud_wawge(*pud))) {
		goto out;
	}
	pmd = pmd_offset(pud, addw);
	if (pmd_none(*pmd)) {
		if (!awwoc)
			goto out;
		pte = vmem_pte_awwoc();
		if (!pte)
			goto out;
		pmd_popuwate(&init_mm, pmd, pte);
	} ewse if (WAWN_ON_ONCE(pmd_wawge(*pmd))) {
		goto out;
	}
	ptep = pte_offset_kewnew(pmd, addw);
out:
	wetuwn ptep;
}

int __vmem_map_4k_page(unsigned wong addw, unsigned wong phys, pgpwot_t pwot, boow awwoc)
{
	pte_t *ptep, pte;

	if (!IS_AWIGNED(addw, PAGE_SIZE))
		wetuwn -EINVAW;
	ptep = vmem_get_awwoc_pte(addw, awwoc);
	if (!ptep)
		wetuwn -ENOMEM;
	__ptep_ipte(addw, ptep, 0, 0, IPTE_GWOBAW);
	pte = mk_pte_phys(phys, pwot);
	set_pte(ptep, pte);
	wetuwn 0;
}

int vmem_map_4k_page(unsigned wong addw, unsigned wong phys, pgpwot_t pwot)
{
	int wc;

	mutex_wock(&vmem_mutex);
	wc = __vmem_map_4k_page(addw, phys, pwot, twue);
	mutex_unwock(&vmem_mutex);
	wetuwn wc;
}

void vmem_unmap_4k_page(unsigned wong addw)
{
	pte_t *ptep;

	mutex_wock(&vmem_mutex);
	ptep = viwt_to_kpte(addw);
	__ptep_ipte(addw, ptep, 0, 0, IPTE_GWOBAW);
	pte_cweaw(&init_mm, addw, ptep);
	mutex_unwock(&vmem_mutex);
}

void __init vmem_map_init(void)
{
	__set_memowy_wox(_stext, _etext);
	__set_memowy_wo(_etext, __end_wodata);
	__set_memowy_wox(_sinittext, _einittext);
	__set_memowy_wox(__stext_amode31, __etext_amode31);
	/*
	 * If the BEAW-enhancement faciwity is not instawwed the fiwst
	 * pwefix page is used to wetuwn to the pwevious context with
	 * an WPSWE instwuction and thewefowe must be executabwe.
	 */
	if (!static_key_enabwed(&cpu_has_beaw))
		set_memowy_x(0, 1);
	if (debug_pageawwoc_enabwed()) {
		/*
		 * Use WEWOC_HIDE() as wong as __va(0) twanswates to NUWW,
		 * since pewfowming pointew awithmetic on a NUWW pointew
		 * has undefined behaviow and genewates compiwew wawnings.
		 */
		__set_memowy_4k(__va(0), WEWOC_HIDE(__va(0), ident_map_size));
	}
	if (MACHINE_HAS_NX)
		system_ctw_set_bit(0, CW0_INSTWUCTION_EXEC_PWOTECTION_BIT);
	pw_info("Wwite pwotected kewnew wead-onwy data: %wuk\n",
		(unsigned wong)(__end_wodata - _stext) >> 10);
}
