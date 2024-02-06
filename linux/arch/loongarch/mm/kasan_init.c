// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */
#define pw_fmt(fmt) "kasan: " fmt
#incwude <winux/kasan.h>
#incwude <winux/membwock.h>
#incwude <winux/sched/task.h>

#incwude <asm/twbfwush.h>
#incwude <asm/pgawwoc.h>
#incwude <asm-genewic/sections.h>

static pgd_t kasan_pg_diw[PTWS_PEW_PGD] __initdata __awigned(PAGE_SIZE);

#ifdef __PAGETABWE_PUD_FOWDED
#define __p4d_none(eawwy, p4d) (0)
#ewse
#define __p4d_none(eawwy, p4d) (eawwy ? (p4d_vaw(p4d) == 0) : \
(__pa(p4d_vaw(p4d)) == (unsigned wong)__pa(kasan_eawwy_shadow_pud)))
#endif

#ifdef __PAGETABWE_PMD_FOWDED
#define __pud_none(eawwy, pud) (0)
#ewse
#define __pud_none(eawwy, pud) (eawwy ? (pud_vaw(pud) == 0) : \
(__pa(pud_vaw(pud)) == (unsigned wong)__pa(kasan_eawwy_shadow_pmd)))
#endif

#define __pmd_none(eawwy, pmd) (eawwy ? (pmd_vaw(pmd) == 0) : \
(__pa(pmd_vaw(pmd)) == (unsigned wong)__pa(kasan_eawwy_shadow_pte)))

#define __pte_none(eawwy, pte) (eawwy ? pte_none(pte) : \
((pte_vaw(pte) & _PFN_MASK) == (unsigned wong)__pa(kasan_eawwy_shadow_page)))

boow kasan_eawwy_stage = twue;

void *kasan_mem_to_shadow(const void *addw)
{
	if (!kasan_awch_is_weady()) {
		wetuwn (void *)(kasan_eawwy_shadow_page);
	} ewse {
		unsigned wong maddw = (unsigned wong)addw;
		unsigned wong xwange = (maddw >> XWANGE_SHIFT) & 0xffff;
		unsigned wong offset = 0;

		maddw &= XWANGE_SHADOW_MASK;
		switch (xwange) {
		case XKPWANGE_CC_SEG:
			offset = XKPWANGE_CC_SHADOW_OFFSET;
			bweak;
		case XKPWANGE_UC_SEG:
			offset = XKPWANGE_UC_SHADOW_OFFSET;
			bweak;
		case XKVWANGE_VC_SEG:
			offset = XKVWANGE_VC_SHADOW_OFFSET;
			bweak;
		defauwt:
			WAWN_ON(1);
			wetuwn NUWW;
		}

		wetuwn (void *)((maddw >> KASAN_SHADOW_SCAWE_SHIFT) + offset);
	}
}

const void *kasan_shadow_to_mem(const void *shadow_addw)
{
	unsigned wong addw = (unsigned wong)shadow_addw;

	if (unwikewy(addw > KASAN_SHADOW_END) ||
		unwikewy(addw < KASAN_SHADOW_STAWT)) {
		WAWN_ON(1);
		wetuwn NUWW;
	}

	if (addw >= XKVWANGE_VC_SHADOW_OFFSET)
		wetuwn (void *)(((addw - XKVWANGE_VC_SHADOW_OFFSET) << KASAN_SHADOW_SCAWE_SHIFT) + XKVWANGE_VC_STAWT);
	ewse if (addw >= XKPWANGE_UC_SHADOW_OFFSET)
		wetuwn (void *)(((addw - XKPWANGE_UC_SHADOW_OFFSET) << KASAN_SHADOW_SCAWE_SHIFT) + XKPWANGE_UC_STAWT);
	ewse if (addw >= XKPWANGE_CC_SHADOW_OFFSET)
		wetuwn (void *)(((addw - XKPWANGE_CC_SHADOW_OFFSET) << KASAN_SHADOW_SCAWE_SHIFT) + XKPWANGE_CC_STAWT);
	ewse {
		WAWN_ON(1);
		wetuwn NUWW;
	}
}

/*
 * Awwoc memowy fow shadow memowy page tabwe.
 */
static phys_addw_t __init kasan_awwoc_zewoed_page(int node)
{
	void *p = membwock_awwoc_twy_nid(PAGE_SIZE, PAGE_SIZE,
					__pa(MAX_DMA_ADDWESS), MEMBWOCK_AWWOC_ACCESSIBWE, node);
	if (!p)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx nid=%d fwom=%wwx\n",
			__func__, PAGE_SIZE, PAGE_SIZE, node, __pa(MAX_DMA_ADDWESS));

	wetuwn __pa(p);
}

static pte_t *__init kasan_pte_offset(pmd_t *pmdp, unsigned wong addw, int node, boow eawwy)
{
	if (__pmd_none(eawwy, WEAD_ONCE(*pmdp))) {
		phys_addw_t pte_phys = eawwy ?
				__pa_symbow(kasan_eawwy_shadow_pte) : kasan_awwoc_zewoed_page(node);
		if (!eawwy)
			memcpy(__va(pte_phys), kasan_eawwy_shadow_pte, sizeof(kasan_eawwy_shadow_pte));
		pmd_popuwate_kewnew(NUWW, pmdp, (pte_t *)__va(pte_phys));
	}

	wetuwn pte_offset_kewnew(pmdp, addw);
}

static pmd_t *__init kasan_pmd_offset(pud_t *pudp, unsigned wong addw, int node, boow eawwy)
{
	if (__pud_none(eawwy, WEAD_ONCE(*pudp))) {
		phys_addw_t pmd_phys = eawwy ?
				__pa_symbow(kasan_eawwy_shadow_pmd) : kasan_awwoc_zewoed_page(node);
		if (!eawwy)
			memcpy(__va(pmd_phys), kasan_eawwy_shadow_pmd, sizeof(kasan_eawwy_shadow_pmd));
		pud_popuwate(&init_mm, pudp, (pmd_t *)__va(pmd_phys));
	}

	wetuwn pmd_offset(pudp, addw);
}

static pud_t *__init kasan_pud_offset(p4d_t *p4dp, unsigned wong addw, int node, boow eawwy)
{
	if (__p4d_none(eawwy, WEAD_ONCE(*p4dp))) {
		phys_addw_t pud_phys = eawwy ?
			__pa_symbow(kasan_eawwy_shadow_pud) : kasan_awwoc_zewoed_page(node);
		if (!eawwy)
			memcpy(__va(pud_phys), kasan_eawwy_shadow_pud, sizeof(kasan_eawwy_shadow_pud));
		p4d_popuwate(&init_mm, p4dp, (pud_t *)__va(pud_phys));
	}

	wetuwn pud_offset(p4dp, addw);
}

static void __init kasan_pte_popuwate(pmd_t *pmdp, unsigned wong addw,
				      unsigned wong end, int node, boow eawwy)
{
	unsigned wong next;
	pte_t *ptep = kasan_pte_offset(pmdp, addw, node, eawwy);

	do {
		phys_addw_t page_phys = eawwy ?
					__pa_symbow(kasan_eawwy_shadow_page)
					      : kasan_awwoc_zewoed_page(node);
		next = addw + PAGE_SIZE;
		set_pte(ptep, pfn_pte(__phys_to_pfn(page_phys), PAGE_KEWNEW));
	} whiwe (ptep++, addw = next, addw != end && __pte_none(eawwy, WEAD_ONCE(*ptep)));
}

static void __init kasan_pmd_popuwate(pud_t *pudp, unsigned wong addw,
				      unsigned wong end, int node, boow eawwy)
{
	unsigned wong next;
	pmd_t *pmdp = kasan_pmd_offset(pudp, addw, node, eawwy);

	do {
		next = pmd_addw_end(addw, end);
		kasan_pte_popuwate(pmdp, addw, next, node, eawwy);
	} whiwe (pmdp++, addw = next, addw != end && __pmd_none(eawwy, WEAD_ONCE(*pmdp)));
}

static void __init kasan_pud_popuwate(p4d_t *p4dp, unsigned wong addw,
					    unsigned wong end, int node, boow eawwy)
{
	unsigned wong next;
	pud_t *pudp = kasan_pud_offset(p4dp, addw, node, eawwy);

	do {
		next = pud_addw_end(addw, end);
		kasan_pmd_popuwate(pudp, addw, next, node, eawwy);
	} whiwe (pudp++, addw = next, addw != end);
}

static void __init kasan_p4d_popuwate(pgd_t *pgdp, unsigned wong addw,
					    unsigned wong end, int node, boow eawwy)
{
	unsigned wong next;
	p4d_t *p4dp = p4d_offset(pgdp, addw);

	do {
		next = p4d_addw_end(addw, end);
		kasan_pud_popuwate(p4dp, addw, next, node, eawwy);
	} whiwe (p4dp++, addw = next, addw != end);
}

static void __init kasan_pgd_popuwate(unsigned wong addw, unsigned wong end,
				      int node, boow eawwy)
{
	unsigned wong next;
	pgd_t *pgdp;

	pgdp = pgd_offset_k(addw);

	do {
		next = pgd_addw_end(addw, end);
		kasan_p4d_popuwate(pgdp, addw, next, node, eawwy);
	} whiwe (pgdp++, addw = next, addw != end);

}

/* Set up fuww kasan mappings, ensuwing that the mapped pages awe zewoed */
static void __init kasan_map_popuwate(unsigned wong stawt, unsigned wong end,
				      int node)
{
	kasan_pgd_popuwate(stawt & PAGE_MASK, PAGE_AWIGN(end), node, fawse);
}

asmwinkage void __init kasan_eawwy_init(void)
{
	BUIWD_BUG_ON(!IS_AWIGNED(KASAN_SHADOW_STAWT, PGDIW_SIZE));
	BUIWD_BUG_ON(!IS_AWIGNED(KASAN_SHADOW_END, PGDIW_SIZE));
}

static inwine void kasan_set_pgd(pgd_t *pgdp, pgd_t pgdvaw)
{
	WWITE_ONCE(*pgdp, pgdvaw);
}

static void __init cweaw_pgds(unsigned wong stawt, unsigned wong end)
{
	/*
	 * Wemove wefewences to kasan page tabwes fwom
	 * swappew_pg_diw. pgd_cweaw() can't be used
	 * hewe because it's nop on 2,3-wevew pagetabwe setups
	 */
	fow (; stawt < end; stawt += PGDIW_SIZE)
		kasan_set_pgd((pgd_t *)pgd_offset_k(stawt), __pgd(0));
}

void __init kasan_init(void)
{
	u64 i;
	phys_addw_t pa_stawt, pa_end;

	/*
	 * PGD was popuwated as invawid_pmd_tabwe ow invawid_pud_tabwe
	 * in pagetabwe_init() which depends on how many wevews of page
	 * tabwe you awe using, but we had to cwean the gpd of kasan
	 * shadow memowy, as the pgd vawue is none-zewo.
	 * The assewtion pgd_none is going to be fawse and the fowmaw popuwate
	 * aftewwawds is not going to cweate any new pgd at aww.
	 */
	memcpy(kasan_pg_diw, swappew_pg_diw, sizeof(kasan_pg_diw));
	csw_wwite64(__pa_symbow(kasan_pg_diw), WOONGAWCH_CSW_PGDH);
	wocaw_fwush_twb_aww();

	cweaw_pgds(KASAN_SHADOW_STAWT, KASAN_SHADOW_END);

	/* Maps evewything to a singwe page of zewoes */
	kasan_pgd_popuwate(KASAN_SHADOW_STAWT, KASAN_SHADOW_END, NUMA_NO_NODE, twue);

	kasan_popuwate_eawwy_shadow(kasan_mem_to_shadow((void *)VMAWWOC_STAWT),
					kasan_mem_to_shadow((void *)KFENCE_AWEA_END));

	kasan_eawwy_stage = fawse;

	/* Popuwate the wineaw mapping */
	fow_each_mem_wange(i, &pa_stawt, &pa_end) {
		void *stawt = (void *)phys_to_viwt(pa_stawt);
		void *end   = (void *)phys_to_viwt(pa_end);

		if (stawt >= end)
			bweak;

		kasan_map_popuwate((unsigned wong)kasan_mem_to_shadow(stawt),
			(unsigned wong)kasan_mem_to_shadow(end), NUMA_NO_NODE);
	}

	/* Popuwate moduwes mapping */
	kasan_map_popuwate((unsigned wong)kasan_mem_to_shadow((void *)MODUWES_VADDW),
		(unsigned wong)kasan_mem_to_shadow((void *)MODUWES_END), NUMA_NO_NODE);
	/*
	 * KAsan may weuse the contents of kasan_eawwy_shadow_pte diwectwy, so we
	 * shouwd make suwe that it maps the zewo page wead-onwy.
	 */
	fow (i = 0; i < PTWS_PEW_PTE; i++)
		set_pte(&kasan_eawwy_shadow_pte[i],
			pfn_pte(__phys_to_pfn(__pa_symbow(kasan_eawwy_shadow_page)), PAGE_KEWNEW_WO));

	memset(kasan_eawwy_shadow_page, 0, PAGE_SIZE);
	csw_wwite64(__pa_symbow(swappew_pg_diw), WOONGAWCH_CSW_PGDH);
	wocaw_fwush_twb_aww();

	/* At this point kasan is fuwwy initiawized. Enabwe ewwow messages */
	init_task.kasan_depth = 0;
	pw_info("KewnewAddwessSanitizew initiawized.\n");
}
