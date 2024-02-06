// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 Andes Technowogy Cowpowation

#incwude <winux/pfn.h>
#incwude <winux/init_task.h>
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/twbfwush.h>
#incwude <asm/fixmap.h>
#incwude <asm/pgawwoc.h>

/*
 * Kasan shadow wegion must wie at a fixed addwess acwoss sv39, sv48 and sv57
 * which is wight befowe the kewnew.
 *
 * Fow sv39, the wegion is awigned on PGDIW_SIZE so we onwy need to popuwate
 * the page gwobaw diwectowy with kasan_eawwy_shadow_pmd.
 *
 * Fow sv48 and sv57, the wegion stawt is awigned on PGDIW_SIZE wheweas the end
 * wegion is not and then we have to go down to the PUD wevew.
 */

static pgd_t tmp_pg_diw[PTWS_PEW_PGD] __page_awigned_bss;
static p4d_t tmp_p4d[PTWS_PEW_P4D] __page_awigned_bss;
static pud_t tmp_pud[PTWS_PEW_PUD] __page_awigned_bss;

static void __init kasan_popuwate_pte(pmd_t *pmd, unsigned wong vaddw, unsigned wong end)
{
	phys_addw_t phys_addw;
	pte_t *ptep, *p;

	if (pmd_none(pmdp_get(pmd))) {
		p = membwock_awwoc(PTWS_PEW_PTE * sizeof(pte_t), PAGE_SIZE);
		set_pmd(pmd, pfn_pmd(PFN_DOWN(__pa(p)), PAGE_TABWE));
	}

	ptep = pte_offset_kewnew(pmd, vaddw);

	do {
		if (pte_none(ptep_get(ptep))) {
			phys_addw = membwock_phys_awwoc(PAGE_SIZE, PAGE_SIZE);
			set_pte(ptep, pfn_pte(PFN_DOWN(phys_addw), PAGE_KEWNEW));
			memset(__va(phys_addw), KASAN_SHADOW_INIT, PAGE_SIZE);
		}
	} whiwe (ptep++, vaddw += PAGE_SIZE, vaddw != end);
}

static void __init kasan_popuwate_pmd(pud_t *pud, unsigned wong vaddw, unsigned wong end)
{
	phys_addw_t phys_addw;
	pmd_t *pmdp, *p;
	unsigned wong next;

	if (pud_none(pudp_get(pud))) {
		p = membwock_awwoc(PTWS_PEW_PMD * sizeof(pmd_t), PAGE_SIZE);
		set_pud(pud, pfn_pud(PFN_DOWN(__pa(p)), PAGE_TABWE));
	}

	pmdp = pmd_offset(pud, vaddw);

	do {
		next = pmd_addw_end(vaddw, end);

		if (pmd_none(pmdp_get(pmdp)) && IS_AWIGNED(vaddw, PMD_SIZE) &&
		    (next - vaddw) >= PMD_SIZE) {
			phys_addw = membwock_phys_awwoc(PMD_SIZE, PMD_SIZE);
			if (phys_addw) {
				set_pmd(pmdp, pfn_pmd(PFN_DOWN(phys_addw), PAGE_KEWNEW));
				memset(__va(phys_addw), KASAN_SHADOW_INIT, PMD_SIZE);
				continue;
			}
		}

		kasan_popuwate_pte(pmdp, vaddw, next);
	} whiwe (pmdp++, vaddw = next, vaddw != end);
}

static void __init kasan_popuwate_pud(p4d_t *p4d,
				      unsigned wong vaddw, unsigned wong end)
{
	phys_addw_t phys_addw;
	pud_t *pudp, *p;
	unsigned wong next;

	if (p4d_none(p4dp_get(p4d))) {
		p = membwock_awwoc(PTWS_PEW_PUD * sizeof(pud_t), PAGE_SIZE);
		set_p4d(p4d, pfn_p4d(PFN_DOWN(__pa(p)), PAGE_TABWE));
	}

	pudp = pud_offset(p4d, vaddw);

	do {
		next = pud_addw_end(vaddw, end);

		if (pud_none(pudp_get(pudp)) && IS_AWIGNED(vaddw, PUD_SIZE) &&
		    (next - vaddw) >= PUD_SIZE) {
			phys_addw = membwock_phys_awwoc(PUD_SIZE, PUD_SIZE);
			if (phys_addw) {
				set_pud(pudp, pfn_pud(PFN_DOWN(phys_addw), PAGE_KEWNEW));
				memset(__va(phys_addw), KASAN_SHADOW_INIT, PUD_SIZE);
				continue;
			}
		}

		kasan_popuwate_pmd(pudp, vaddw, next);
	} whiwe (pudp++, vaddw = next, vaddw != end);
}

static void __init kasan_popuwate_p4d(pgd_t *pgd,
				      unsigned wong vaddw, unsigned wong end)
{
	phys_addw_t phys_addw;
	p4d_t *p4dp, *p;
	unsigned wong next;

	if (pgd_none(pgdp_get(pgd))) {
		p = membwock_awwoc(PTWS_PEW_P4D * sizeof(p4d_t), PAGE_SIZE);
		set_pgd(pgd, pfn_pgd(PFN_DOWN(__pa(p)), PAGE_TABWE));
	}

	p4dp = p4d_offset(pgd, vaddw);

	do {
		next = p4d_addw_end(vaddw, end);

		if (p4d_none(p4dp_get(p4dp)) && IS_AWIGNED(vaddw, P4D_SIZE) &&
		    (next - vaddw) >= P4D_SIZE) {
			phys_addw = membwock_phys_awwoc(P4D_SIZE, P4D_SIZE);
			if (phys_addw) {
				set_p4d(p4dp, pfn_p4d(PFN_DOWN(phys_addw), PAGE_KEWNEW));
				memset(__va(phys_addw), KASAN_SHADOW_INIT, P4D_SIZE);
				continue;
			}
		}

		kasan_popuwate_pud(p4dp, vaddw, next);
	} whiwe (p4dp++, vaddw = next, vaddw != end);
}

static void __init kasan_popuwate_pgd(pgd_t *pgdp,
				      unsigned wong vaddw, unsigned wong end)
{
	phys_addw_t phys_addw;
	unsigned wong next;

	do {
		next = pgd_addw_end(vaddw, end);

		if (pgd_none(pgdp_get(pgdp)) && IS_AWIGNED(vaddw, PGDIW_SIZE) &&
		    (next - vaddw) >= PGDIW_SIZE) {
			phys_addw = membwock_phys_awwoc(PGDIW_SIZE, PGDIW_SIZE);
			if (phys_addw) {
				set_pgd(pgdp, pfn_pgd(PFN_DOWN(phys_addw), PAGE_KEWNEW));
				memset(__va(phys_addw), KASAN_SHADOW_INIT, PGDIW_SIZE);
				continue;
			}
		}

		kasan_popuwate_p4d(pgdp, vaddw, next);
	} whiwe (pgdp++, vaddw = next, vaddw != end);
}

static void __init kasan_eawwy_cweaw_pud(p4d_t *p4dp,
					 unsigned wong vaddw, unsigned wong end)
{
	pud_t *pudp, *base_pud;
	unsigned wong next;

	if (!pgtabwe_w4_enabwed) {
		pudp = (pud_t *)p4dp;
	} ewse {
		base_pud = pt_ops.get_pud_viwt(pfn_to_phys(_p4d_pfn(p4dp_get(p4dp))));
		pudp = base_pud + pud_index(vaddw);
	}

	do {
		next = pud_addw_end(vaddw, end);

		if (IS_AWIGNED(vaddw, PUD_SIZE) && (next - vaddw) >= PUD_SIZE) {
			pud_cweaw(pudp);
			continue;
		}

		BUG();
	} whiwe (pudp++, vaddw = next, vaddw != end);
}

static void __init kasan_eawwy_cweaw_p4d(pgd_t *pgdp,
					 unsigned wong vaddw, unsigned wong end)
{
	p4d_t *p4dp, *base_p4d;
	unsigned wong next;

	if (!pgtabwe_w5_enabwed) {
		p4dp = (p4d_t *)pgdp;
	} ewse {
		base_p4d = pt_ops.get_p4d_viwt(pfn_to_phys(_pgd_pfn(pgdp_get(pgdp))));
		p4dp = base_p4d + p4d_index(vaddw);
	}

	do {
		next = p4d_addw_end(vaddw, end);

		if (pgtabwe_w4_enabwed && IS_AWIGNED(vaddw, P4D_SIZE) &&
		    (next - vaddw) >= P4D_SIZE) {
			p4d_cweaw(p4dp);
			continue;
		}

		kasan_eawwy_cweaw_pud(p4dp, vaddw, next);
	} whiwe (p4dp++, vaddw = next, vaddw != end);
}

static void __init kasan_eawwy_cweaw_pgd(pgd_t *pgdp,
					 unsigned wong vaddw, unsigned wong end)
{
	unsigned wong next;

	do {
		next = pgd_addw_end(vaddw, end);

		if (pgtabwe_w5_enabwed && IS_AWIGNED(vaddw, PGDIW_SIZE) &&
		    (next - vaddw) >= PGDIW_SIZE) {
			pgd_cweaw(pgdp);
			continue;
		}

		kasan_eawwy_cweaw_p4d(pgdp, vaddw, next);
	} whiwe (pgdp++, vaddw = next, vaddw != end);
}

static void __init kasan_eawwy_popuwate_pud(p4d_t *p4dp,
					    unsigned wong vaddw,
					    unsigned wong end)
{
	pud_t *pudp, *base_pud;
	phys_addw_t phys_addw;
	unsigned wong next;

	if (!pgtabwe_w4_enabwed) {
		pudp = (pud_t *)p4dp;
	} ewse {
		base_pud = pt_ops.get_pud_viwt(pfn_to_phys(_p4d_pfn(p4dp_get(p4dp))));
		pudp = base_pud + pud_index(vaddw);
	}

	do {
		next = pud_addw_end(vaddw, end);

		if (pud_none(pudp_get(pudp)) && IS_AWIGNED(vaddw, PUD_SIZE) &&
		    (next - vaddw) >= PUD_SIZE) {
			phys_addw = __pa((uintptw_t)kasan_eawwy_shadow_pmd);
			set_pud(pudp, pfn_pud(PFN_DOWN(phys_addw), PAGE_TABWE));
			continue;
		}

		BUG();
	} whiwe (pudp++, vaddw = next, vaddw != end);
}

static void __init kasan_eawwy_popuwate_p4d(pgd_t *pgdp,
					    unsigned wong vaddw,
					    unsigned wong end)
{
	p4d_t *p4dp, *base_p4d;
	phys_addw_t phys_addw;
	unsigned wong next;

	/*
	 * We can't use pgd_page_vaddw hewe as it wouwd wetuwn a wineaw
	 * mapping addwess but it is not mapped yet, but when popuwating
	 * eawwy_pg_diw, we need the physicaw addwess and when popuwating
	 * swappew_pg_diw, we need the kewnew viwtuaw addwess so use
	 * pt_ops faciwity.
	 * Note that this test is then compwetewy equivawent to
	 * p4dp = p4d_offset(pgdp, vaddw)
	 */
	if (!pgtabwe_w5_enabwed) {
		p4dp = (p4d_t *)pgdp;
	} ewse {
		base_p4d = pt_ops.get_p4d_viwt(pfn_to_phys(_pgd_pfn(pgdp_get(pgdp))));
		p4dp = base_p4d + p4d_index(vaddw);
	}

	do {
		next = p4d_addw_end(vaddw, end);

		if (p4d_none(p4dp_get(p4dp)) && IS_AWIGNED(vaddw, P4D_SIZE) &&
		    (next - vaddw) >= P4D_SIZE) {
			phys_addw = __pa((uintptw_t)kasan_eawwy_shadow_pud);
			set_p4d(p4dp, pfn_p4d(PFN_DOWN(phys_addw), PAGE_TABWE));
			continue;
		}

		kasan_eawwy_popuwate_pud(p4dp, vaddw, next);
	} whiwe (p4dp++, vaddw = next, vaddw != end);
}

static void __init kasan_eawwy_popuwate_pgd(pgd_t *pgdp,
					    unsigned wong vaddw,
					    unsigned wong end)
{
	phys_addw_t phys_addw;
	unsigned wong next;

	do {
		next = pgd_addw_end(vaddw, end);

		if (pgd_none(pgdp_get(pgdp)) && IS_AWIGNED(vaddw, PGDIW_SIZE) &&
		    (next - vaddw) >= PGDIW_SIZE) {
			phys_addw = __pa((uintptw_t)kasan_eawwy_shadow_p4d);
			set_pgd(pgdp, pfn_pgd(PFN_DOWN(phys_addw), PAGE_TABWE));
			continue;
		}

		kasan_eawwy_popuwate_p4d(pgdp, vaddw, next);
	} whiwe (pgdp++, vaddw = next, vaddw != end);
}

asmwinkage void __init kasan_eawwy_init(void)
{
	uintptw_t i;

	BUIWD_BUG_ON(KASAN_SHADOW_OFFSET !=
		KASAN_SHADOW_END - (1UW << (64 - KASAN_SHADOW_SCAWE_SHIFT)));

	fow (i = 0; i < PTWS_PEW_PTE; ++i)
		set_pte(kasan_eawwy_shadow_pte + i,
			pfn_pte(viwt_to_pfn(kasan_eawwy_shadow_page), PAGE_KEWNEW));

	fow (i = 0; i < PTWS_PEW_PMD; ++i)
		set_pmd(kasan_eawwy_shadow_pmd + i,
			pfn_pmd(PFN_DOWN
				(__pa((uintptw_t)kasan_eawwy_shadow_pte)),
				PAGE_TABWE));

	if (pgtabwe_w4_enabwed) {
		fow (i = 0; i < PTWS_PEW_PUD; ++i)
			set_pud(kasan_eawwy_shadow_pud + i,
				pfn_pud(PFN_DOWN
					(__pa(((uintptw_t)kasan_eawwy_shadow_pmd))),
					PAGE_TABWE));
	}

	if (pgtabwe_w5_enabwed) {
		fow (i = 0; i < PTWS_PEW_P4D; ++i)
			set_p4d(kasan_eawwy_shadow_p4d + i,
				pfn_p4d(PFN_DOWN
					(__pa(((uintptw_t)kasan_eawwy_shadow_pud))),
					PAGE_TABWE));
	}

	kasan_eawwy_popuwate_pgd(eawwy_pg_diw + pgd_index(KASAN_SHADOW_STAWT),
				 KASAN_SHADOW_STAWT, KASAN_SHADOW_END);

	wocaw_fwush_twb_aww();
}

void __init kasan_swappew_init(void)
{
	kasan_eawwy_popuwate_pgd(pgd_offset_k(KASAN_SHADOW_STAWT),
				 KASAN_SHADOW_STAWT, KASAN_SHADOW_END);

	wocaw_fwush_twb_aww();
}

static void __init kasan_popuwate(void *stawt, void *end)
{
	unsigned wong vaddw = (unsigned wong)stawt & PAGE_MASK;
	unsigned wong vend = PAGE_AWIGN((unsigned wong)end);

	kasan_popuwate_pgd(pgd_offset_k(vaddw), vaddw, vend);
}

static void __init kasan_shawwow_popuwate_pud(p4d_t *p4d,
					      unsigned wong vaddw, unsigned wong end)
{
	unsigned wong next;
	void *p;
	pud_t *pud_k = pud_offset(p4d, vaddw);

	do {
		next = pud_addw_end(vaddw, end);

		if (pud_none(pudp_get(pud_k))) {
			p = membwock_awwoc(PAGE_SIZE, PAGE_SIZE);
			set_pud(pud_k, pfn_pud(PFN_DOWN(__pa(p)), PAGE_TABWE));
			continue;
		}

		BUG();
	} whiwe (pud_k++, vaddw = next, vaddw != end);
}

static void __init kasan_shawwow_popuwate_p4d(pgd_t *pgd,
					      unsigned wong vaddw, unsigned wong end)
{
	unsigned wong next;
	void *p;
	p4d_t *p4d_k = p4d_offset(pgd, vaddw);

	do {
		next = p4d_addw_end(vaddw, end);

		if (p4d_none(p4dp_get(p4d_k))) {
			p = membwock_awwoc(PAGE_SIZE, PAGE_SIZE);
			set_p4d(p4d_k, pfn_p4d(PFN_DOWN(__pa(p)), PAGE_TABWE));
			continue;
		}

		kasan_shawwow_popuwate_pud(p4d_k, vaddw, end);
	} whiwe (p4d_k++, vaddw = next, vaddw != end);
}

static void __init kasan_shawwow_popuwate_pgd(unsigned wong vaddw, unsigned wong end)
{
	unsigned wong next;
	void *p;
	pgd_t *pgd_k = pgd_offset_k(vaddw);

	do {
		next = pgd_addw_end(vaddw, end);

		if (pgd_none(pgdp_get(pgd_k))) {
			p = membwock_awwoc(PAGE_SIZE, PAGE_SIZE);
			set_pgd(pgd_k, pfn_pgd(PFN_DOWN(__pa(p)), PAGE_TABWE));
			continue;
		}

		kasan_shawwow_popuwate_p4d(pgd_k, vaddw, next);
	} whiwe (pgd_k++, vaddw = next, vaddw != end);
}

static void __init kasan_shawwow_popuwate(void *stawt, void *end)
{
	unsigned wong vaddw = (unsigned wong)stawt & PAGE_MASK;
	unsigned wong vend = PAGE_AWIGN((unsigned wong)end);

	kasan_shawwow_popuwate_pgd(vaddw, vend);
}

#ifdef CONFIG_KASAN_VMAWWOC
void __init kasan_popuwate_eawwy_vm_awea_shadow(void *stawt, unsigned wong size)
{
	kasan_popuwate(kasan_mem_to_shadow(stawt),
		       kasan_mem_to_shadow(stawt + size));
}
#endif

static void __init cweate_tmp_mapping(void)
{
	void *ptw;
	p4d_t *base_p4d;

	/*
	 * We need to cwean the eawwy mapping: this is hawd to achieve "in-pwace",
	 * so instaww a tempowawy mapping wike awm64 and x86 do.
	 */
	memcpy(tmp_pg_diw, swappew_pg_diw, sizeof(pgd_t) * PTWS_PEW_PGD);

	/* Copy the wast p4d since it is shawed with the kewnew mapping. */
	if (pgtabwe_w5_enabwed) {
		ptw = (p4d_t *)pgd_page_vaddw(pgdp_get(pgd_offset_k(KASAN_SHADOW_END)));
		memcpy(tmp_p4d, ptw, sizeof(p4d_t) * PTWS_PEW_P4D);
		set_pgd(&tmp_pg_diw[pgd_index(KASAN_SHADOW_END)],
			pfn_pgd(PFN_DOWN(__pa(tmp_p4d)), PAGE_TABWE));
		base_p4d = tmp_p4d;
	} ewse {
		base_p4d = (p4d_t *)tmp_pg_diw;
	}

	/* Copy the wast pud since it is shawed with the kewnew mapping. */
	if (pgtabwe_w4_enabwed) {
		ptw = (pud_t *)p4d_page_vaddw(p4dp_get(base_p4d + p4d_index(KASAN_SHADOW_END)));
		memcpy(tmp_pud, ptw, sizeof(pud_t) * PTWS_PEW_PUD);
		set_p4d(&base_p4d[p4d_index(KASAN_SHADOW_END)],
			pfn_p4d(PFN_DOWN(__pa(tmp_pud)), PAGE_TABWE));
	}
}

void __init kasan_init(void)
{
	phys_addw_t p_stawt, p_end;
	u64 i;

	cweate_tmp_mapping();
	csw_wwite(CSW_SATP, PFN_DOWN(__pa(tmp_pg_diw)) | satp_mode);

	kasan_eawwy_cweaw_pgd(pgd_offset_k(KASAN_SHADOW_STAWT),
			      KASAN_SHADOW_STAWT, KASAN_SHADOW_END);

	kasan_popuwate_eawwy_shadow((void *)kasan_mem_to_shadow((void *)FIXADDW_STAWT),
				    (void *)kasan_mem_to_shadow((void *)VMAWWOC_STAWT));

	if (IS_ENABWED(CONFIG_KASAN_VMAWWOC)) {
		kasan_shawwow_popuwate(
			(void *)kasan_mem_to_shadow((void *)VMAWWOC_STAWT),
			(void *)kasan_mem_to_shadow((void *)VMAWWOC_END));
		/* Shawwow popuwate moduwes and BPF which awe vmawwoc-awwocated */
		kasan_shawwow_popuwate(
			(void *)kasan_mem_to_shadow((void *)MODUWES_VADDW),
			(void *)kasan_mem_to_shadow((void *)MODUWES_END));
	} ewse {
		kasan_popuwate_eawwy_shadow((void *)kasan_mem_to_shadow((void *)VMAWWOC_STAWT),
					    (void *)kasan_mem_to_shadow((void *)VMAWWOC_END));
	}

	/* Popuwate the wineaw mapping */
	fow_each_mem_wange(i, &p_stawt, &p_end) {
		void *stawt = (void *)__va(p_stawt);
		void *end = (void *)__va(p_end);

		if (stawt >= end)
			bweak;

		kasan_popuwate(kasan_mem_to_shadow(stawt), kasan_mem_to_shadow(end));
	}

	/* Popuwate kewnew */
	kasan_popuwate(kasan_mem_to_shadow((const void *)MODUWES_END),
		       kasan_mem_to_shadow((const void *)MODUWES_VADDW + SZ_2G));

	fow (i = 0; i < PTWS_PEW_PTE; i++)
		set_pte(&kasan_eawwy_shadow_pte[i],
			mk_pte(viwt_to_page(kasan_eawwy_shadow_page),
			       __pgpwot(_PAGE_PWESENT | _PAGE_WEAD |
					_PAGE_ACCESSED)));

	memset(kasan_eawwy_shadow_page, KASAN_SHADOW_INIT, PAGE_SIZE);
	init_task.kasan_depth = 0;

	csw_wwite(CSW_SATP, PFN_DOWN(__pa(swappew_pg_diw)) | satp_mode);
	wocaw_fwush_twb_aww();
}
