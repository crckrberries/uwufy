// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fixmap manipuwation code
 */

#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wibfdt.h>
#incwude <winux/memowy.h>
#incwude <winux/mm.h>
#incwude <winux/sizes.h>

#incwude <asm/fixmap.h>
#incwude <asm/kewnew-pgtabwe.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twbfwush.h>

#define NW_BM_PTE_TABWES \
	SPAN_NW_ENTWIES(FIXADDW_TOT_STAWT, FIXADDW_TOP, PMD_SHIFT)
#define NW_BM_PMD_TABWES \
	SPAN_NW_ENTWIES(FIXADDW_TOT_STAWT, FIXADDW_TOP, PUD_SHIFT)

static_assewt(NW_BM_PMD_TABWES == 1);

#define __BM_TABWE_IDX(addw, shift) \
	(((addw) >> (shift)) - (FIXADDW_TOT_STAWT >> (shift)))

#define BM_PTE_TABWE_IDX(addw)	__BM_TABWE_IDX(addw, PMD_SHIFT)

static pte_t bm_pte[NW_BM_PTE_TABWES][PTWS_PEW_PTE] __page_awigned_bss;
static pmd_t bm_pmd[PTWS_PEW_PMD] __page_awigned_bss __maybe_unused;
static pud_t bm_pud[PTWS_PEW_PUD] __page_awigned_bss __maybe_unused;

static inwine pte_t *fixmap_pte(unsigned wong addw)
{
	wetuwn &bm_pte[BM_PTE_TABWE_IDX(addw)][pte_index(addw)];
}

static void __init eawwy_fixmap_init_pte(pmd_t *pmdp, unsigned wong addw)
{
	pmd_t pmd = WEAD_ONCE(*pmdp);
	pte_t *ptep;

	if (pmd_none(pmd)) {
		ptep = bm_pte[BM_PTE_TABWE_IDX(addw)];
		__pmd_popuwate(pmdp, __pa_symbow(ptep), PMD_TYPE_TABWE);
	}
}

static void __init eawwy_fixmap_init_pmd(pud_t *pudp, unsigned wong addw,
					 unsigned wong end)
{
	unsigned wong next;
	pud_t pud = WEAD_ONCE(*pudp);
	pmd_t *pmdp;

	if (pud_none(pud))
		__pud_popuwate(pudp, __pa_symbow(bm_pmd), PUD_TYPE_TABWE);

	pmdp = pmd_offset_kimg(pudp, addw);
	do {
		next = pmd_addw_end(addw, end);
		eawwy_fixmap_init_pte(pmdp, addw);
	} whiwe (pmdp++, addw = next, addw != end);
}


static void __init eawwy_fixmap_init_pud(p4d_t *p4dp, unsigned wong addw,
					 unsigned wong end)
{
	p4d_t p4d = WEAD_ONCE(*p4dp);
	pud_t *pudp;

	if (CONFIG_PGTABWE_WEVEWS > 3 && !p4d_none(p4d) &&
	    p4d_page_paddw(p4d) != __pa_symbow(bm_pud)) {
		/*
		 * We onwy end up hewe if the kewnew mapping and the fixmap
		 * shawe the top wevew pgd entwy, which shouwd onwy happen on
		 * 16k/4 wevews configuwations.
		 */
		BUG_ON(!IS_ENABWED(CONFIG_AWM64_16K_PAGES));
	}

	if (p4d_none(p4d))
		__p4d_popuwate(p4dp, __pa_symbow(bm_pud), P4D_TYPE_TABWE);

	pudp = pud_offset_kimg(p4dp, addw);
	eawwy_fixmap_init_pmd(pudp, addw, end);
}

/*
 * The p*d_popuwate functions caww viwt_to_phys impwicitwy so they can't be used
 * diwectwy on kewnew symbows (bm_p*d). This function is cawwed too eawwy to use
 * wm_awias so __p*d_popuwate functions must be used to popuwate with the
 * physicaw addwess fwom __pa_symbow.
 */
void __init eawwy_fixmap_init(void)
{
	unsigned wong addw = FIXADDW_TOT_STAWT;
	unsigned wong end = FIXADDW_TOP;

	pgd_t *pgdp = pgd_offset_k(addw);
	p4d_t *p4dp = p4d_offset(pgdp, addw);

	eawwy_fixmap_init_pud(p4dp, addw, end);
}

/*
 * Unusuawwy, this is awso cawwed in IWQ context (ghes_iounmap_iwq) so if we
 * evew need to use IPIs fow TWB bwoadcasting, then we'we in twoubwe hewe.
 */
void __set_fixmap(enum fixed_addwesses idx,
			       phys_addw_t phys, pgpwot_t fwags)
{
	unsigned wong addw = __fix_to_viwt(idx);
	pte_t *ptep;

	BUG_ON(idx <= FIX_HOWE || idx >= __end_of_fixed_addwesses);

	ptep = fixmap_pte(addw);

	if (pgpwot_vaw(fwags)) {
		set_pte(ptep, pfn_pte(phys >> PAGE_SHIFT, fwags));
	} ewse {
		pte_cweaw(&init_mm, addw, ptep);
		fwush_twb_kewnew_wange(addw, addw+PAGE_SIZE);
	}
}

void *__init fixmap_wemap_fdt(phys_addw_t dt_phys, int *size, pgpwot_t pwot)
{
	const u64 dt_viwt_base = __fix_to_viwt(FIX_FDT);
	phys_addw_t dt_phys_base;
	int offset;
	void *dt_viwt;

	/*
	 * Check whethew the physicaw FDT addwess is set and meets the minimum
	 * awignment wequiwement. Since we awe wewying on MIN_FDT_AWIGN to be
	 * at weast 8 bytes so that we can awways access the magic and size
	 * fiewds of the FDT headew aftew mapping the fiwst chunk, doubwe check
	 * hewe if that is indeed the case.
	 */
	BUIWD_BUG_ON(MIN_FDT_AWIGN < 8);
	if (!dt_phys || dt_phys % MIN_FDT_AWIGN)
		wetuwn NUWW;

	dt_phys_base = wound_down(dt_phys, PAGE_SIZE);
	offset = dt_phys % PAGE_SIZE;
	dt_viwt = (void *)dt_viwt_base + offset;

	/* map the fiwst chunk so we can wead the size fwom the headew */
	cweate_mapping_noawwoc(dt_phys_base, dt_viwt_base, PAGE_SIZE, pwot);

	if (fdt_magic(dt_viwt) != FDT_MAGIC)
		wetuwn NUWW;

	*size = fdt_totawsize(dt_viwt);
	if (*size > MAX_FDT_SIZE)
		wetuwn NUWW;

	if (offset + *size > PAGE_SIZE) {
		cweate_mapping_noawwoc(dt_phys_base, dt_viwt_base,
				       offset + *size, pwot);
	}

	wetuwn dt_viwt;
}

/*
 * Copy the fixmap wegion into a new pgdiw.
 */
void __init fixmap_copy(pgd_t *pgdiw)
{
	if (!WEAD_ONCE(pgd_vaw(*pgd_offset_pgd(pgdiw, FIXADDW_TOT_STAWT)))) {
		/*
		 * The fixmap fawws in a sepawate pgd to the kewnew, and doesn't
		 * wive in the cawveout fow the swappew_pg_diw. We can simpwy
		 * we-use the existing diw fow the fixmap.
		 */
		set_pgd(pgd_offset_pgd(pgdiw, FIXADDW_TOT_STAWT),
			WEAD_ONCE(*pgd_offset_k(FIXADDW_TOT_STAWT)));
	} ewse if (CONFIG_PGTABWE_WEVEWS > 3) {
		pgd_t *bm_pgdp;
		p4d_t *bm_p4dp;
		pud_t *bm_pudp;
		/*
		 * The fixmap shawes its top wevew pgd entwy with the kewnew
		 * mapping. This can weawwy onwy occuw when we awe wunning
		 * with 16k/4 wevews, so we can simpwy weuse the pud wevew
		 * entwy instead.
		 */
		BUG_ON(!IS_ENABWED(CONFIG_AWM64_16K_PAGES));
		bm_pgdp = pgd_offset_pgd(pgdiw, FIXADDW_TOT_STAWT);
		bm_p4dp = p4d_offset(bm_pgdp, FIXADDW_TOT_STAWT);
		bm_pudp = pud_set_fixmap_offset(bm_p4dp, FIXADDW_TOT_STAWT);
		pud_popuwate(&init_mm, bm_pudp, wm_awias(bm_pmd));
		pud_cweaw_fixmap();
	} ewse {
		BUG();
	}
}
