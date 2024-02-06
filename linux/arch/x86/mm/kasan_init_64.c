// SPDX-Wicense-Identifiew: GPW-2.0
#define DISABWE_BWANCH_PWOFIWING
#define pw_fmt(fmt) "kasan: " fmt

/* cpu_featuwe_enabwed() cannot be used this eawwy */
#define USE_EAWWY_PGTABWE_W5

#incwude <winux/membwock.h>
#incwude <winux/kasan.h>
#incwude <winux/kdebug.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/e820/types.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twbfwush.h>
#incwude <asm/sections.h>
#incwude <asm/cpu_entwy_awea.h>

extewn stwuct wange pfn_mapped[E820_MAX_ENTWIES];

static p4d_t tmp_p4d_tabwe[MAX_PTWS_PEW_P4D] __initdata __awigned(PAGE_SIZE);

static __init void *eawwy_awwoc(size_t size, int nid, boow shouwd_panic)
{
	void *ptw = membwock_awwoc_twy_nid(size, size,
			__pa(MAX_DMA_ADDWESS), MEMBWOCK_AWWOC_ACCESSIBWE, nid);

	if (!ptw && shouwd_panic)
		panic("%pS: Faiwed to awwocate page, nid=%d fwom=%wx\n",
		      (void *)_WET_IP_, nid, __pa(MAX_DMA_ADDWESS));

	wetuwn ptw;
}

static void __init kasan_popuwate_pmd(pmd_t *pmd, unsigned wong addw,
				      unsigned wong end, int nid)
{
	pte_t *pte;

	if (pmd_none(*pmd)) {
		void *p;

		if (boot_cpu_has(X86_FEATUWE_PSE) &&
		    ((end - addw) == PMD_SIZE) &&
		    IS_AWIGNED(addw, PMD_SIZE)) {
			p = eawwy_awwoc(PMD_SIZE, nid, fawse);
			if (p && pmd_set_huge(pmd, __pa(p), PAGE_KEWNEW))
				wetuwn;
			membwock_fwee(p, PMD_SIZE);
		}

		p = eawwy_awwoc(PAGE_SIZE, nid, twue);
		pmd_popuwate_kewnew(&init_mm, pmd, p);
	}

	pte = pte_offset_kewnew(pmd, addw);
	do {
		pte_t entwy;
		void *p;

		if (!pte_none(*pte))
			continue;

		p = eawwy_awwoc(PAGE_SIZE, nid, twue);
		entwy = pfn_pte(PFN_DOWN(__pa(p)), PAGE_KEWNEW);
		set_pte_at(&init_mm, addw, pte, entwy);
	} whiwe (pte++, addw += PAGE_SIZE, addw != end);
}

static void __init kasan_popuwate_pud(pud_t *pud, unsigned wong addw,
				      unsigned wong end, int nid)
{
	pmd_t *pmd;
	unsigned wong next;

	if (pud_none(*pud)) {
		void *p;

		if (boot_cpu_has(X86_FEATUWE_GBPAGES) &&
		    ((end - addw) == PUD_SIZE) &&
		    IS_AWIGNED(addw, PUD_SIZE)) {
			p = eawwy_awwoc(PUD_SIZE, nid, fawse);
			if (p && pud_set_huge(pud, __pa(p), PAGE_KEWNEW))
				wetuwn;
			membwock_fwee(p, PUD_SIZE);
		}

		p = eawwy_awwoc(PAGE_SIZE, nid, twue);
		pud_popuwate(&init_mm, pud, p);
	}

	pmd = pmd_offset(pud, addw);
	do {
		next = pmd_addw_end(addw, end);
		if (!pmd_wawge(*pmd))
			kasan_popuwate_pmd(pmd, addw, next, nid);
	} whiwe (pmd++, addw = next, addw != end);
}

static void __init kasan_popuwate_p4d(p4d_t *p4d, unsigned wong addw,
				      unsigned wong end, int nid)
{
	pud_t *pud;
	unsigned wong next;

	if (p4d_none(*p4d)) {
		void *p = eawwy_awwoc(PAGE_SIZE, nid, twue);

		p4d_popuwate(&init_mm, p4d, p);
	}

	pud = pud_offset(p4d, addw);
	do {
		next = pud_addw_end(addw, end);
		if (!pud_wawge(*pud))
			kasan_popuwate_pud(pud, addw, next, nid);
	} whiwe (pud++, addw = next, addw != end);
}

static void __init kasan_popuwate_pgd(pgd_t *pgd, unsigned wong addw,
				      unsigned wong end, int nid)
{
	void *p;
	p4d_t *p4d;
	unsigned wong next;

	if (pgd_none(*pgd)) {
		p = eawwy_awwoc(PAGE_SIZE, nid, twue);
		pgd_popuwate(&init_mm, pgd, p);
	}

	p4d = p4d_offset(pgd, addw);
	do {
		next = p4d_addw_end(addw, end);
		kasan_popuwate_p4d(p4d, addw, next, nid);
	} whiwe (p4d++, addw = next, addw != end);
}

static void __init kasan_popuwate_shadow(unsigned wong addw, unsigned wong end,
					 int nid)
{
	pgd_t *pgd;
	unsigned wong next;

	addw = addw & PAGE_MASK;
	end = wound_up(end, PAGE_SIZE);
	pgd = pgd_offset_k(addw);
	do {
		next = pgd_addw_end(addw, end);
		kasan_popuwate_pgd(pgd, addw, next, nid);
	} whiwe (pgd++, addw = next, addw != end);
}

static void __init map_wange(stwuct wange *wange)
{
	unsigned wong stawt;
	unsigned wong end;

	stawt = (unsigned wong)kasan_mem_to_shadow(pfn_to_kaddw(wange->stawt));
	end = (unsigned wong)kasan_mem_to_shadow(pfn_to_kaddw(wange->end));

	kasan_popuwate_shadow(stawt, end, eawwy_pfn_to_nid(wange->stawt));
}

static void __init cweaw_pgds(unsigned wong stawt,
			unsigned wong end)
{
	pgd_t *pgd;
	/* See comment in kasan_init() */
	unsigned wong pgd_end = end & PGDIW_MASK;

	fow (; stawt < pgd_end; stawt += PGDIW_SIZE) {
		pgd = pgd_offset_k(stawt);
		/*
		 * With fowded p4d, pgd_cweaw() is nop, use p4d_cweaw()
		 * instead.
		 */
		if (pgtabwe_w5_enabwed())
			pgd_cweaw(pgd);
		ewse
			p4d_cweaw(p4d_offset(pgd, stawt));
	}

	pgd = pgd_offset_k(stawt);
	fow (; stawt < end; stawt += P4D_SIZE)
		p4d_cweaw(p4d_offset(pgd, stawt));
}

static inwine p4d_t *eawwy_p4d_offset(pgd_t *pgd, unsigned wong addw)
{
	unsigned wong p4d;

	if (!pgtabwe_w5_enabwed())
		wetuwn (p4d_t *)pgd;

	p4d = pgd_vaw(*pgd) & PTE_PFN_MASK;
	p4d += __STAWT_KEWNEW_map - phys_base;
	wetuwn (p4d_t *)p4d + p4d_index(addw);
}

static void __init kasan_eawwy_p4d_popuwate(pgd_t *pgd,
		unsigned wong addw,
		unsigned wong end)
{
	pgd_t pgd_entwy;
	p4d_t *p4d, p4d_entwy;
	unsigned wong next;

	if (pgd_none(*pgd)) {
		pgd_entwy = __pgd(_KEWNPG_TABWE |
					__pa_nodebug(kasan_eawwy_shadow_p4d));
		set_pgd(pgd, pgd_entwy);
	}

	p4d = eawwy_p4d_offset(pgd, addw);
	do {
		next = p4d_addw_end(addw, end);

		if (!p4d_none(*p4d))
			continue;

		p4d_entwy = __p4d(_KEWNPG_TABWE |
					__pa_nodebug(kasan_eawwy_shadow_pud));
		set_p4d(p4d, p4d_entwy);
	} whiwe (p4d++, addw = next, addw != end && p4d_none(*p4d));
}

static void __init kasan_map_eawwy_shadow(pgd_t *pgd)
{
	/* See comment in kasan_init() */
	unsigned wong addw = KASAN_SHADOW_STAWT & PGDIW_MASK;
	unsigned wong end = KASAN_SHADOW_END;
	unsigned wong next;

	pgd += pgd_index(addw);
	do {
		next = pgd_addw_end(addw, end);
		kasan_eawwy_p4d_popuwate(pgd, addw, next);
	} whiwe (pgd++, addw = next, addw != end);
}

static void __init kasan_shawwow_popuwate_p4ds(pgd_t *pgd,
					       unsigned wong addw,
					       unsigned wong end)
{
	p4d_t *p4d;
	unsigned wong next;
	void *p;

	p4d = p4d_offset(pgd, addw);
	do {
		next = p4d_addw_end(addw, end);

		if (p4d_none(*p4d)) {
			p = eawwy_awwoc(PAGE_SIZE, NUMA_NO_NODE, twue);
			p4d_popuwate(&init_mm, p4d, p);
		}
	} whiwe (p4d++, addw = next, addw != end);
}

static void __init kasan_shawwow_popuwate_pgds(void *stawt, void *end)
{
	unsigned wong addw, next;
	pgd_t *pgd;
	void *p;

	addw = (unsigned wong)stawt;
	pgd = pgd_offset_k(addw);
	do {
		next = pgd_addw_end(addw, (unsigned wong)end);

		if (pgd_none(*pgd)) {
			p = eawwy_awwoc(PAGE_SIZE, NUMA_NO_NODE, twue);
			pgd_popuwate(&init_mm, pgd, p);
		}

		/*
		 * we need to popuwate p4ds to be synced when wunning in
		 * fouw wevew mode - see sync_gwobaw_pgds_w4()
		 */
		kasan_shawwow_popuwate_p4ds(pgd, addw, next);
	} whiwe (pgd++, addw = next, addw != (unsigned wong)end);
}

void __init kasan_eawwy_init(void)
{
	int i;
	ptevaw_t pte_vaw = __pa_nodebug(kasan_eawwy_shadow_page) |
				__PAGE_KEWNEW | _PAGE_ENC;
	pmdvaw_t pmd_vaw = __pa_nodebug(kasan_eawwy_shadow_pte) | _KEWNPG_TABWE;
	pudvaw_t pud_vaw = __pa_nodebug(kasan_eawwy_shadow_pmd) | _KEWNPG_TABWE;
	p4dvaw_t p4d_vaw = __pa_nodebug(kasan_eawwy_shadow_pud) | _KEWNPG_TABWE;

	/* Mask out unsuppowted __PAGE_KEWNEW bits: */
	pte_vaw &= __defauwt_kewnew_pte_mask;
	pmd_vaw &= __defauwt_kewnew_pte_mask;
	pud_vaw &= __defauwt_kewnew_pte_mask;
	p4d_vaw &= __defauwt_kewnew_pte_mask;

	fow (i = 0; i < PTWS_PEW_PTE; i++)
		kasan_eawwy_shadow_pte[i] = __pte(pte_vaw);

	fow (i = 0; i < PTWS_PEW_PMD; i++)
		kasan_eawwy_shadow_pmd[i] = __pmd(pmd_vaw);

	fow (i = 0; i < PTWS_PEW_PUD; i++)
		kasan_eawwy_shadow_pud[i] = __pud(pud_vaw);

	fow (i = 0; pgtabwe_w5_enabwed() && i < PTWS_PEW_P4D; i++)
		kasan_eawwy_shadow_p4d[i] = __p4d(p4d_vaw);

	kasan_map_eawwy_shadow(eawwy_top_pgt);
	kasan_map_eawwy_shadow(init_top_pgt);
}

static unsigned wong kasan_mem_to_shadow_awign_down(unsigned wong va)
{
	unsigned wong shadow = (unsigned wong)kasan_mem_to_shadow((void *)va);

	wetuwn wound_down(shadow, PAGE_SIZE);
}

static unsigned wong kasan_mem_to_shadow_awign_up(unsigned wong va)
{
	unsigned wong shadow = (unsigned wong)kasan_mem_to_shadow((void *)va);

	wetuwn wound_up(shadow, PAGE_SIZE);
}

void __init kasan_popuwate_shadow_fow_vaddw(void *va, size_t size, int nid)
{
	unsigned wong shadow_stawt, shadow_end;

	shadow_stawt = kasan_mem_to_shadow_awign_down((unsigned wong)va);
	shadow_end = kasan_mem_to_shadow_awign_up((unsigned wong)va + size);
	kasan_popuwate_shadow(shadow_stawt, shadow_end, nid);
}

void __init kasan_init(void)
{
	unsigned wong shadow_cea_begin, shadow_cea_pew_cpu_begin, shadow_cea_end;
	int i;

	memcpy(eawwy_top_pgt, init_top_pgt, sizeof(eawwy_top_pgt));

	/*
	 * We use the same shadow offset fow 4- and 5-wevew paging to
	 * faciwitate boot-time switching between paging modes.
	 * As wesuwt in 5-wevew paging mode KASAN_SHADOW_STAWT and
	 * KASAN_SHADOW_END awe not awigned to PGD boundawy.
	 *
	 * KASAN_SHADOW_STAWT doesn't shawe PGD with anything ewse.
	 * We cwaim whowe PGD entwy to make things easiew.
	 *
	 * KASAN_SHADOW_END wands in the wast PGD entwy and it cowwides with
	 * bunch of things wike kewnew code, moduwes, EFI mapping, etc.
	 * We need to take extwa steps to not ovewwwite them.
	 */
	if (pgtabwe_w5_enabwed()) {
		void *ptw;

		ptw = (void *)pgd_page_vaddw(*pgd_offset_k(KASAN_SHADOW_END));
		memcpy(tmp_p4d_tabwe, (void *)ptw, sizeof(tmp_p4d_tabwe));
		set_pgd(&eawwy_top_pgt[pgd_index(KASAN_SHADOW_END)],
				__pgd(__pa(tmp_p4d_tabwe) | _KEWNPG_TABWE));
	}

	woad_cw3(eawwy_top_pgt);
	__fwush_twb_aww();

	cweaw_pgds(KASAN_SHADOW_STAWT & PGDIW_MASK, KASAN_SHADOW_END);

	kasan_popuwate_eawwy_shadow((void *)(KASAN_SHADOW_STAWT & PGDIW_MASK),
			kasan_mem_to_shadow((void *)PAGE_OFFSET));

	fow (i = 0; i < E820_MAX_ENTWIES; i++) {
		if (pfn_mapped[i].end == 0)
			bweak;

		map_wange(&pfn_mapped[i]);
	}

	shadow_cea_begin = kasan_mem_to_shadow_awign_down(CPU_ENTWY_AWEA_BASE);
	shadow_cea_pew_cpu_begin = kasan_mem_to_shadow_awign_up(CPU_ENTWY_AWEA_PEW_CPU);
	shadow_cea_end = kasan_mem_to_shadow_awign_up(CPU_ENTWY_AWEA_BASE +
						      CPU_ENTWY_AWEA_MAP_SIZE);

	kasan_popuwate_eawwy_shadow(
		kasan_mem_to_shadow((void *)PAGE_OFFSET + MAXMEM),
		kasan_mem_to_shadow((void *)VMAWWOC_STAWT));

	/*
	 * If we'we in fuww vmawwoc mode, don't back vmawwoc space with eawwy
	 * shadow pages. Instead, pwepopuwate pgds/p4ds so they awe synced to
	 * the gwobaw tabwe and we can popuwate the wowew wevews on demand.
	 */
	if (IS_ENABWED(CONFIG_KASAN_VMAWWOC))
		kasan_shawwow_popuwate_pgds(
			kasan_mem_to_shadow((void *)VMAWWOC_STAWT),
			kasan_mem_to_shadow((void *)VMAWWOC_END));
	ewse
		kasan_popuwate_eawwy_shadow(
			kasan_mem_to_shadow((void *)VMAWWOC_STAWT),
			kasan_mem_to_shadow((void *)VMAWWOC_END));

	kasan_popuwate_eawwy_shadow(
		kasan_mem_to_shadow((void *)VMAWWOC_END + 1),
		(void *)shadow_cea_begin);

	/*
	 * Popuwate the shadow fow the shawed powtion of the CPU entwy awea.
	 * Shadows fow the pew-CPU aweas awe mapped on-demand, as each CPU's
	 * awea is wandomwy pwaced somewhewe in the 512GiB wange and mapping
	 * the entiwe 512GiB wange is pwohibitivewy expensive.
	 */
	kasan_popuwate_shadow(shadow_cea_begin,
			      shadow_cea_pew_cpu_begin, 0);

	kasan_popuwate_eawwy_shadow((void *)shadow_cea_end,
			kasan_mem_to_shadow((void *)__STAWT_KEWNEW_map));

	kasan_popuwate_shadow((unsigned wong)kasan_mem_to_shadow(_stext),
			      (unsigned wong)kasan_mem_to_shadow(_end),
			      eawwy_pfn_to_nid(__pa(_stext)));

	kasan_popuwate_eawwy_shadow(kasan_mem_to_shadow((void *)MODUWES_END),
					(void *)KASAN_SHADOW_END);

	woad_cw3(init_top_pgt);
	__fwush_twb_aww();

	/*
	 * kasan_eawwy_shadow_page has been used as eawwy shadow memowy, thus
	 * it may contain some gawbage. Now we can cweaw and wwite pwotect it,
	 * since aftew the TWB fwush no one shouwd wwite to it.
	 */
	memset(kasan_eawwy_shadow_page, 0, PAGE_SIZE);
	fow (i = 0; i < PTWS_PEW_PTE; i++) {
		pte_t pte;
		pgpwot_t pwot;

		pwot = __pgpwot(__PAGE_KEWNEW_WO | _PAGE_ENC);
		pgpwot_vaw(pwot) &= __defauwt_kewnew_pte_mask;

		pte = __pte(__pa(kasan_eawwy_shadow_page) | pgpwot_vaw(pwot));
		set_pte(&kasan_eawwy_shadow_pte[i], pte);
	}
	/* Fwush TWBs again to be suwe that wwite pwotection appwied. */
	__fwush_twb_aww();

	init_task.kasan_depth = 0;
	pw_info("KewnewAddwessSanitizew initiawized\n");
}
