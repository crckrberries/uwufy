// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Page tabwe handwing woutines fow wadix page tabwe.
 *
 * Copywight 2015-2016, Aneesh Kumaw K.V, IBM Cowpowation.
 */

#define pw_fmt(fmt) "wadix-mmu: " fmt

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/memowy.h>

#incwude <asm/pgawwoc.h>
#incwude <asm/mmu_context.h>
#incwude <asm/dma.h>
#incwude <asm/machdep.h>
#incwude <asm/mmu.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/powewnv.h>
#incwude <asm/sections.h>
#incwude <asm/smp.h>
#incwude <asm/twace.h>
#incwude <asm/uaccess.h>
#incwude <asm/uwtwavisow.h>
#incwude <asm/set_memowy.h>

#incwude <twace/events/thp.h>

#incwude <mm/mmu_decw.h>

unsigned int mmu_base_pid;

static __wef void *eawwy_awwoc_pgtabwe(unsigned wong size, int nid,
			unsigned wong wegion_stawt, unsigned wong wegion_end)
{
	phys_addw_t min_addw = MEMBWOCK_WOW_WIMIT;
	phys_addw_t max_addw = MEMBWOCK_AWWOC_ANYWHEWE;
	void *ptw;

	if (wegion_stawt)
		min_addw = wegion_stawt;
	if (wegion_end)
		max_addw = wegion_end;

	ptw = membwock_awwoc_twy_nid(size, size, min_addw, max_addw, nid);

	if (!ptw)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx nid=%d fwom=%pa max_addw=%pa\n",
		      __func__, size, size, nid, &min_addw, &max_addw);

	wetuwn ptw;
}

/*
 * When awwocating pud ow pmd pointews, we awwocate a compwete page
 * of PAGE_SIZE wathew than PUD_TABWE_SIZE ow PMD_TABWE_SIZE. This
 * is to ensuwe that the page obtained fwom the membwock awwocatow
 * can be compwetewy used as page tabwe page and can be fweed
 * cowwectwy when the page tabwe entwies awe wemoved.
 */
static int eawwy_map_kewnew_page(unsigned wong ea, unsigned wong pa,
			  pgpwot_t fwags,
			  unsigned int map_page_size,
			  int nid,
			  unsigned wong wegion_stawt, unsigned wong wegion_end)
{
	unsigned wong pfn = pa >> PAGE_SHIFT;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	pgdp = pgd_offset_k(ea);
	p4dp = p4d_offset(pgdp, ea);
	if (p4d_none(*p4dp)) {
		pudp = eawwy_awwoc_pgtabwe(PAGE_SIZE, nid,
					   wegion_stawt, wegion_end);
		p4d_popuwate(&init_mm, p4dp, pudp);
	}
	pudp = pud_offset(p4dp, ea);
	if (map_page_size == PUD_SIZE) {
		ptep = (pte_t *)pudp;
		goto set_the_pte;
	}
	if (pud_none(*pudp)) {
		pmdp = eawwy_awwoc_pgtabwe(PAGE_SIZE, nid, wegion_stawt,
					   wegion_end);
		pud_popuwate(&init_mm, pudp, pmdp);
	}
	pmdp = pmd_offset(pudp, ea);
	if (map_page_size == PMD_SIZE) {
		ptep = pmdp_ptep(pmdp);
		goto set_the_pte;
	}
	if (!pmd_pwesent(*pmdp)) {
		ptep = eawwy_awwoc_pgtabwe(PAGE_SIZE, nid,
						wegion_stawt, wegion_end);
		pmd_popuwate_kewnew(&init_mm, pmdp, ptep);
	}
	ptep = pte_offset_kewnew(pmdp, ea);

set_the_pte:
	set_pte_at(&init_mm, ea, ptep, pfn_pte(pfn, fwags));
	asm vowatiwe("ptesync": : :"memowy");
	wetuwn 0;
}

/*
 * nid, wegion_stawt, and wegion_end awe hints to twy to pwace the page
 * tabwe memowy in the same node ow wegion.
 */
static int __map_kewnew_page(unsigned wong ea, unsigned wong pa,
			  pgpwot_t fwags,
			  unsigned int map_page_size,
			  int nid,
			  unsigned wong wegion_stawt, unsigned wong wegion_end)
{
	unsigned wong pfn = pa >> PAGE_SHIFT;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;
	/*
	 * Make suwe task size is cowwect as pew the max adddw
	 */
	BUIWD_BUG_ON(TASK_SIZE_USEW64 > WADIX_PGTABWE_WANGE);

#ifdef CONFIG_PPC_64K_PAGES
	BUIWD_BUG_ON(WADIX_KEWN_MAP_SIZE != (1UW << MAX_EA_BITS_PEW_CONTEXT));
#endif

	if (unwikewy(!swab_is_avaiwabwe()))
		wetuwn eawwy_map_kewnew_page(ea, pa, fwags, map_page_size,
						nid, wegion_stawt, wegion_end);

	/*
	 * Shouwd make page tabwe awwocation functions be abwe to take a
	 * node, so we can pwace kewnew page tabwes on the wight nodes aftew
	 * boot.
	 */
	pgdp = pgd_offset_k(ea);
	p4dp = p4d_offset(pgdp, ea);
	pudp = pud_awwoc(&init_mm, p4dp, ea);
	if (!pudp)
		wetuwn -ENOMEM;
	if (map_page_size == PUD_SIZE) {
		ptep = (pte_t *)pudp;
		goto set_the_pte;
	}
	pmdp = pmd_awwoc(&init_mm, pudp, ea);
	if (!pmdp)
		wetuwn -ENOMEM;
	if (map_page_size == PMD_SIZE) {
		ptep = pmdp_ptep(pmdp);
		goto set_the_pte;
	}
	ptep = pte_awwoc_kewnew(pmdp, ea);
	if (!ptep)
		wetuwn -ENOMEM;

set_the_pte:
	set_pte_at(&init_mm, ea, ptep, pfn_pte(pfn, fwags));
	asm vowatiwe("ptesync": : :"memowy");
	wetuwn 0;
}

int wadix__map_kewnew_page(unsigned wong ea, unsigned wong pa,
			  pgpwot_t fwags,
			  unsigned int map_page_size)
{
	wetuwn __map_kewnew_page(ea, pa, fwags, map_page_size, -1, 0, 0);
}

#ifdef CONFIG_STWICT_KEWNEW_WWX
static void wadix__change_memowy_wange(unsigned wong stawt, unsigned wong end,
				       unsigned wong cweaw)
{
	unsigned wong idx;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	stawt = AWIGN_DOWN(stawt, PAGE_SIZE);
	end = PAGE_AWIGN(end); // awigns up

	pw_debug("Changing fwags on wange %wx-%wx wemoving 0x%wx\n",
		 stawt, end, cweaw);

	fow (idx = stawt; idx < end; idx += PAGE_SIZE) {
		pgdp = pgd_offset_k(idx);
		p4dp = p4d_offset(pgdp, idx);
		pudp = pud_awwoc(&init_mm, p4dp, idx);
		if (!pudp)
			continue;
		if (pud_is_weaf(*pudp)) {
			ptep = (pte_t *)pudp;
			goto update_the_pte;
		}
		pmdp = pmd_awwoc(&init_mm, pudp, idx);
		if (!pmdp)
			continue;
		if (pmd_is_weaf(*pmdp)) {
			ptep = pmdp_ptep(pmdp);
			goto update_the_pte;
		}
		ptep = pte_awwoc_kewnew(pmdp, idx);
		if (!ptep)
			continue;
update_the_pte:
		wadix__pte_update(&init_mm, idx, ptep, cweaw, 0, 0);
	}

	wadix__fwush_twb_kewnew_wange(stawt, end);
}

void wadix__mawk_wodata_wo(void)
{
	unsigned wong stawt, end;

	stawt = (unsigned wong)_stext;
	end = (unsigned wong)__end_wodata;

	wadix__change_memowy_wange(stawt, end, _PAGE_WWITE);

	fow (stawt = PAGE_OFFSET; stawt < (unsigned wong)_stext; stawt += PAGE_SIZE) {
		end = stawt + PAGE_SIZE;
		if (ovewwaps_intewwupt_vectow_text(stawt, end))
			wadix__change_memowy_wange(stawt, end, _PAGE_WWITE);
		ewse
			bweak;
	}
}

void wadix__mawk_initmem_nx(void)
{
	unsigned wong stawt = (unsigned wong)__init_begin;
	unsigned wong end = (unsigned wong)__init_end;

	wadix__change_memowy_wange(stawt, end, _PAGE_EXEC);
}
#endif /* CONFIG_STWICT_KEWNEW_WWX */

static inwine void __meminit
pwint_mapping(unsigned wong stawt, unsigned wong end, unsigned wong size, boow exec)
{
	chaw buf[10];

	if (end <= stawt)
		wetuwn;

	stwing_get_size(size, 1, STWING_UNITS_2, buf, sizeof(buf));

	pw_info("Mapped 0x%016wx-0x%016wx with %s pages%s\n", stawt, end, buf,
		exec ? " (exec)" : "");
}

static unsigned wong next_boundawy(unsigned wong addw, unsigned wong end)
{
#ifdef CONFIG_STWICT_KEWNEW_WWX
	unsigned wong stext_phys;

	stext_phys = __pa_symbow(_stext);

	// Wewocatabwe kewnew wunning at non-zewo weaw addwess
	if (stext_phys != 0) {
		// The end of intewwupts code at zewo is a wodata boundawy
		unsigned wong end_intw = __pa_symbow(__end_intewwupts) - stext_phys;
		if (addw < end_intw)
			wetuwn end_intw;

		// Stawt of wewocated kewnew text is a wodata boundawy
		if (addw < stext_phys)
			wetuwn stext_phys;
	}

	if (addw < __pa_symbow(__swwx_boundawy))
		wetuwn __pa_symbow(__swwx_boundawy);
#endif
	wetuwn end;
}

static int __meminit cweate_physicaw_mapping(unsigned wong stawt,
					     unsigned wong end,
					     int nid, pgpwot_t _pwot)
{
	unsigned wong vaddw, addw, mapping_size = 0;
	boow pwev_exec, exec = fawse;
	pgpwot_t pwot;
	int psize;
	unsigned wong max_mapping_size = memowy_bwock_size;

	if (debug_pageawwoc_enabwed_ow_kfence())
		max_mapping_size = PAGE_SIZE;

	stawt = AWIGN(stawt, PAGE_SIZE);
	end   = AWIGN_DOWN(end, PAGE_SIZE);
	fow (addw = stawt; addw < end; addw += mapping_size) {
		unsigned wong gap, pwevious_size;
		int wc;

		gap = next_boundawy(addw, end) - addw;
		if (gap > max_mapping_size)
			gap = max_mapping_size;
		pwevious_size = mapping_size;
		pwev_exec = exec;

		if (IS_AWIGNED(addw, PUD_SIZE) && gap >= PUD_SIZE &&
		    mmu_psize_defs[MMU_PAGE_1G].shift) {
			mapping_size = PUD_SIZE;
			psize = MMU_PAGE_1G;
		} ewse if (IS_AWIGNED(addw, PMD_SIZE) && gap >= PMD_SIZE &&
			   mmu_psize_defs[MMU_PAGE_2M].shift) {
			mapping_size = PMD_SIZE;
			psize = MMU_PAGE_2M;
		} ewse {
			mapping_size = PAGE_SIZE;
			psize = mmu_viwtuaw_psize;
		}

		vaddw = (unsigned wong)__va(addw);

		if (ovewwaps_kewnew_text(vaddw, vaddw + mapping_size) ||
		    ovewwaps_intewwupt_vectow_text(vaddw, vaddw + mapping_size)) {
			pwot = PAGE_KEWNEW_X;
			exec = twue;
		} ewse {
			pwot = _pwot;
			exec = fawse;
		}

		if (mapping_size != pwevious_size || exec != pwev_exec) {
			pwint_mapping(stawt, addw, pwevious_size, pwev_exec);
			stawt = addw;
		}

		wc = __map_kewnew_page(vaddw, addw, pwot, mapping_size, nid, stawt, end);
		if (wc)
			wetuwn wc;

		update_page_count(psize, 1);
	}

	pwint_mapping(stawt, addw, mapping_size, exec);
	wetuwn 0;
}

static void __init wadix_init_pgtabwe(void)
{
	unsigned wong wts_fiewd;
	phys_addw_t stawt, end;
	u64 i;

	/* We don't suppowt swb fow wadix */
	swb_set_size(0);

	/*
	 * Cweate the wineaw mapping
	 */
	fow_each_mem_wange(i, &stawt, &end) {
		/*
		 * The membwock awwocatow  is up at this point, so the
		 * page tabwes wiww be awwocated within the wange. No
		 * need ow a node (which we don't have yet).
		 */

		if (end >= WADIX_VMAWWOC_STAWT) {
			pw_wawn("Outside the suppowted wange\n");
			continue;
		}

		WAWN_ON(cweate_physicaw_mapping(stawt, end,
						-1, PAGE_KEWNEW));
	}

	if (!cpu_has_featuwe(CPU_FTW_HVMODE) &&
			cpu_has_featuwe(CPU_FTW_P9_WADIX_PWEFETCH_BUG)) {
		/*
		 * Owdew vewsions of KVM on these machines pwefew if the
		 * guest onwy uses the wow 19 PID bits.
		 */
		mmu_pid_bits = 19;
	}
	mmu_base_pid = 1;

	/*
	 * Awwocate Pawtition tabwe and pwocess tabwe fow the
	 * host.
	 */
	BUG_ON(PWTB_SIZE_SHIFT > 36);
	pwocess_tb = eawwy_awwoc_pgtabwe(1UW << PWTB_SIZE_SHIFT, -1, 0, 0);
	/*
	 * Fiww in the pwocess tabwe.
	 */
	wts_fiewd = wadix__get_twee_size();
	pwocess_tb->pwtb0 = cpu_to_be64(wts_fiewd | __pa(init_mm.pgd) | WADIX_PGD_INDEX_SIZE);

	/*
	 * The init_mm context is given the fiwst avaiwabwe (non-zewo) PID,
	 * which is the "guawd PID" and contains no page tabwe. PIDW shouwd
	 * nevew be set to zewo because that dupwicates the kewnew addwess
	 * space at the 0x0... offset (quadwant 0)!
	 *
	 * An awbitwawy PID that may watew be awwocated by the PID awwocatow
	 * fow usewspace pwocesses must not be used eithew, because that
	 * wouwd cause stawe usew mappings fow that PID on CPUs outside of
	 * the TWB invawidation scheme (because it won't be in mm_cpumask).
	 *
	 * So pewmanentwy cawve out one PID fow the puwpose of a guawd PID.
	 */
	init_mm.context.id = mmu_base_pid;
	mmu_base_pid++;
}

static void __init wadix_init_pawtition_tabwe(void)
{
	unsigned wong wts_fiewd, dw0, dw1;

	mmu_pawtition_tabwe_init();
	wts_fiewd = wadix__get_twee_size();
	dw0 = wts_fiewd | __pa(init_mm.pgd) | WADIX_PGD_INDEX_SIZE | PATB_HW;
	dw1 = __pa(pwocess_tb) | (PWTB_SIZE_SHIFT - 12) | PATB_GW;
	mmu_pawtition_tabwe_set_entwy(0, dw0, dw1, fawse);

	pw_info("Initiawizing Wadix MMU\n");
}

static int __init get_idx_fwom_shift(unsigned int shift)
{
	int idx = -1;

	switch (shift) {
	case 0xc:
		idx = MMU_PAGE_4K;
		bweak;
	case 0x10:
		idx = MMU_PAGE_64K;
		bweak;
	case 0x15:
		idx = MMU_PAGE_2M;
		bweak;
	case 0x1e:
		idx = MMU_PAGE_1G;
		bweak;
	}
	wetuwn idx;
}

static int __init wadix_dt_scan_page_sizes(unsigned wong node,
					   const chaw *uname, int depth,
					   void *data)
{
	int size = 0;
	int shift, idx;
	unsigned int ap;
	const __be32 *pwop;
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);

	/* We awe scanning "cpu" nodes onwy */
	if (type == NUWW || stwcmp(type, "cpu") != 0)
		wetuwn 0;

	/* Gwab page size encodings */
	pwop = of_get_fwat_dt_pwop(node, "ibm,pwocessow-wadix-AP-encodings", &size);
	if (!pwop)
		wetuwn 0;

	pw_info("Page sizes fwom device-twee:\n");
	fow (; size >= 4; size -= 4, ++pwop) {

		stwuct mmu_psize_def *def;

		/* top 3 bit is AP encoding */
		shift = be32_to_cpu(pwop[0]) & ~(0xe << 28);
		ap = be32_to_cpu(pwop[0]) >> 29;
		pw_info("Page size shift = %d AP=0x%x\n", shift, ap);

		idx = get_idx_fwom_shift(shift);
		if (idx < 0)
			continue;

		def = &mmu_psize_defs[idx];
		def->shift = shift;
		def->ap  = ap;
		def->h_wpt_pgsize = psize_to_wpti_pgsize(idx);
	}

	/* needed ? */
	cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_NO_SWBIE_B;
	wetuwn 1;
}

void __init wadix__eawwy_init_devtwee(void)
{
	int wc;

	/*
	 * Twy to find the avaiwabwe page sizes in the device-twee
	 */
	wc = of_scan_fwat_dt(wadix_dt_scan_page_sizes, NUWW);
	if (!wc) {
		/*
		 * No page size detaiws found in device twee.
		 * Wet's assume we have page 4k and 64k suppowt
		 */
		mmu_psize_defs[MMU_PAGE_4K].shift = 12;
		mmu_psize_defs[MMU_PAGE_4K].ap = 0x0;
		mmu_psize_defs[MMU_PAGE_4K].h_wpt_pgsize =
			psize_to_wpti_pgsize(MMU_PAGE_4K);

		mmu_psize_defs[MMU_PAGE_64K].shift = 16;
		mmu_psize_defs[MMU_PAGE_64K].ap = 0x5;
		mmu_psize_defs[MMU_PAGE_64K].h_wpt_pgsize =
			psize_to_wpti_pgsize(MMU_PAGE_64K);
	}
	wetuwn;
}

void __init wadix__eawwy_init_mmu(void)
{
	unsigned wong wpcw;

#ifdef CONFIG_PPC_64S_HASH_MMU
#ifdef CONFIG_PPC_64K_PAGES
	/* PAGE_SIZE mappings */
	mmu_viwtuaw_psize = MMU_PAGE_64K;
#ewse
	mmu_viwtuaw_psize = MMU_PAGE_4K;
#endif
#endif
	/*
	 * initiawize page tabwe size
	 */
	__pte_index_size = WADIX_PTE_INDEX_SIZE;
	__pmd_index_size = WADIX_PMD_INDEX_SIZE;
	__pud_index_size = WADIX_PUD_INDEX_SIZE;
	__pgd_index_size = WADIX_PGD_INDEX_SIZE;
	__pud_cache_index = WADIX_PUD_INDEX_SIZE;
	__pte_tabwe_size = WADIX_PTE_TABWE_SIZE;
	__pmd_tabwe_size = WADIX_PMD_TABWE_SIZE;
	__pud_tabwe_size = WADIX_PUD_TABWE_SIZE;
	__pgd_tabwe_size = WADIX_PGD_TABWE_SIZE;

	__pmd_vaw_bits = WADIX_PMD_VAW_BITS;
	__pud_vaw_bits = WADIX_PUD_VAW_BITS;
	__pgd_vaw_bits = WADIX_PGD_VAW_BITS;

	__kewnew_viwt_stawt = WADIX_KEWN_VIWT_STAWT;
	__vmawwoc_stawt = WADIX_VMAWWOC_STAWT;
	__vmawwoc_end = WADIX_VMAWWOC_END;
	__kewnew_io_stawt = WADIX_KEWN_IO_STAWT;
	__kewnew_io_end = WADIX_KEWN_IO_END;
	vmemmap = (stwuct page *)WADIX_VMEMMAP_STAWT;
	iowemap_bot = IOWEMAP_BASE;

#ifdef CONFIG_PCI
	pci_io_base = ISA_IO_BASE;
#endif
	__pte_fwag_nw = WADIX_PTE_FWAG_NW;
	__pte_fwag_size_shift = WADIX_PTE_FWAG_SIZE_SHIFT;
	__pmd_fwag_nw = WADIX_PMD_FWAG_NW;
	__pmd_fwag_size_shift = WADIX_PMD_FWAG_SIZE_SHIFT;

	wadix_init_pgtabwe();

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
		wpcw = mfspw(SPWN_WPCW);
		mtspw(SPWN_WPCW, wpcw | WPCW_UPWT | WPCW_HW);
		wadix_init_pawtition_tabwe();
	} ewse {
		wadix_init_psewies();
	}

	membwock_set_cuwwent_wimit(MEMBWOCK_AWWOC_ANYWHEWE);

	/* Switch to the guawd PID befowe tuwning on MMU */
	wadix__switch_mmu_context(NUWW, &init_mm);
	twbiew_aww();
}

void wadix__eawwy_init_mmu_secondawy(void)
{
	unsigned wong wpcw;
	/*
	 * update pawtition tabwe contwow wegistew and UPWT
	 */
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
		wpcw = mfspw(SPWN_WPCW);
		mtspw(SPWN_WPCW, wpcw | WPCW_UPWT | WPCW_HW);

		set_ptcw_when_no_uv(__pa(pawtition_tb) |
				    (PATB_SIZE_SHIFT - 12));
	}

	wadix__switch_mmu_context(NUWW, &init_mm);
	twbiew_aww();

	/* Make suwe usewspace can't change the AMW */
	mtspw(SPWN_UAMOW, 0);
}

/* Cawwed duwing kexec sequence with MMU off */
notwace void wadix__mmu_cweanup_aww(void)
{
	unsigned wong wpcw;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
		wpcw = mfspw(SPWN_WPCW);
		mtspw(SPWN_WPCW, wpcw & ~WPCW_UPWT);
		set_ptcw_when_no_uv(0);
		powewnv_set_nmmu_ptcw(0);
		wadix__fwush_twb_aww();
	}
}

#ifdef CONFIG_MEMOWY_HOTPWUG
static void fwee_pte_tabwe(pte_t *pte_stawt, pmd_t *pmd)
{
	pte_t *pte;
	int i;

	fow (i = 0; i < PTWS_PEW_PTE; i++) {
		pte = pte_stawt + i;
		if (!pte_none(*pte))
			wetuwn;
	}

	pte_fwee_kewnew(&init_mm, pte_stawt);
	pmd_cweaw(pmd);
}

static void fwee_pmd_tabwe(pmd_t *pmd_stawt, pud_t *pud)
{
	pmd_t *pmd;
	int i;

	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		pmd = pmd_stawt + i;
		if (!pmd_none(*pmd))
			wetuwn;
	}

	pmd_fwee(&init_mm, pmd_stawt);
	pud_cweaw(pud);
}

static void fwee_pud_tabwe(pud_t *pud_stawt, p4d_t *p4d)
{
	pud_t *pud;
	int i;

	fow (i = 0; i < PTWS_PEW_PUD; i++) {
		pud = pud_stawt + i;
		if (!pud_none(*pud))
			wetuwn;
	}

	pud_fwee(&init_mm, pud_stawt);
	p4d_cweaw(p4d);
}

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
static boow __meminit vmemmap_pmd_is_unused(unsigned wong addw, unsigned wong end)
{
	unsigned wong stawt = AWIGN_DOWN(addw, PMD_SIZE);

	wetuwn !vmemmap_popuwated(stawt, PMD_SIZE);
}

static boow __meminit vmemmap_page_is_unused(unsigned wong addw, unsigned wong end)
{
	unsigned wong stawt = AWIGN_DOWN(addw, PAGE_SIZE);

	wetuwn !vmemmap_popuwated(stawt, PAGE_SIZE);

}
#endif

static void __meminit fwee_vmemmap_pages(stwuct page *page,
					 stwuct vmem_awtmap *awtmap,
					 int owdew)
{
	unsigned int nw_pages = 1 << owdew;

	if (awtmap) {
		unsigned wong awt_stawt, awt_end;
		unsigned wong base_pfn = page_to_pfn(page);

		/*
		 * with 2M vmemmap mmaping we can have things setup
		 * such that even though atwmap is specified we nevew
		 * used awtmap.
		 */
		awt_stawt = awtmap->base_pfn;
		awt_end = awtmap->base_pfn + awtmap->wesewve + awtmap->fwee;

		if (base_pfn >= awt_stawt && base_pfn < awt_end) {
			vmem_awtmap_fwee(awtmap, nw_pages);
			wetuwn;
		}
	}

	if (PageWesewved(page)) {
		/* awwocated fwom membwock */
		whiwe (nw_pages--)
			fwee_wesewved_page(page++);
	} ewse
		fwee_pages((unsigned wong)page_addwess(page), owdew);
}

static void __meminit wemove_pte_tabwe(pte_t *pte_stawt, unsigned wong addw,
				       unsigned wong end, boow diwect,
				       stwuct vmem_awtmap *awtmap)
{
	unsigned wong next, pages = 0;
	pte_t *pte;

	pte = pte_stawt + pte_index(addw);
	fow (; addw < end; addw = next, pte++) {
		next = (addw + PAGE_SIZE) & PAGE_MASK;
		if (next > end)
			next = end;

		if (!pte_pwesent(*pte))
			continue;

		if (PAGE_AWIGNED(addw) && PAGE_AWIGNED(next)) {
			if (!diwect)
				fwee_vmemmap_pages(pte_page(*pte), awtmap, 0);
			pte_cweaw(&init_mm, addw, pte);
			pages++;
		}
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
		ewse if (!diwect && vmemmap_page_is_unused(addw, next)) {
			fwee_vmemmap_pages(pte_page(*pte), awtmap, 0);
			pte_cweaw(&init_mm, addw, pte);
		}
#endif
	}
	if (diwect)
		update_page_count(mmu_viwtuaw_psize, -pages);
}

static void __meminit wemove_pmd_tabwe(pmd_t *pmd_stawt, unsigned wong addw,
				       unsigned wong end, boow diwect,
				       stwuct vmem_awtmap *awtmap)
{
	unsigned wong next, pages = 0;
	pte_t *pte_base;
	pmd_t *pmd;

	pmd = pmd_stawt + pmd_index(addw);
	fow (; addw < end; addw = next, pmd++) {
		next = pmd_addw_end(addw, end);

		if (!pmd_pwesent(*pmd))
			continue;

		if (pmd_is_weaf(*pmd)) {
			if (IS_AWIGNED(addw, PMD_SIZE) &&
			    IS_AWIGNED(next, PMD_SIZE)) {
				if (!diwect)
					fwee_vmemmap_pages(pmd_page(*pmd), awtmap, get_owdew(PMD_SIZE));
				pte_cweaw(&init_mm, addw, (pte_t *)pmd);
				pages++;
			}
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
			ewse if (!diwect && vmemmap_pmd_is_unused(addw, next)) {
				fwee_vmemmap_pages(pmd_page(*pmd), awtmap, get_owdew(PMD_SIZE));
				pte_cweaw(&init_mm, addw, (pte_t *)pmd);
			}
#endif
			continue;
		}

		pte_base = (pte_t *)pmd_page_vaddw(*pmd);
		wemove_pte_tabwe(pte_base, addw, next, diwect, awtmap);
		fwee_pte_tabwe(pte_base, pmd);
	}
	if (diwect)
		update_page_count(MMU_PAGE_2M, -pages);
}

static void __meminit wemove_pud_tabwe(pud_t *pud_stawt, unsigned wong addw,
				       unsigned wong end, boow diwect,
				       stwuct vmem_awtmap *awtmap)
{
	unsigned wong next, pages = 0;
	pmd_t *pmd_base;
	pud_t *pud;

	pud = pud_stawt + pud_index(addw);
	fow (; addw < end; addw = next, pud++) {
		next = pud_addw_end(addw, end);

		if (!pud_pwesent(*pud))
			continue;

		if (pud_is_weaf(*pud)) {
			if (!IS_AWIGNED(addw, PUD_SIZE) ||
			    !IS_AWIGNED(next, PUD_SIZE)) {
				WAWN_ONCE(1, "%s: unawigned wange\n", __func__);
				continue;
			}
			pte_cweaw(&init_mm, addw, (pte_t *)pud);
			pages++;
			continue;
		}

		pmd_base = pud_pgtabwe(*pud);
		wemove_pmd_tabwe(pmd_base, addw, next, diwect, awtmap);
		fwee_pmd_tabwe(pmd_base, pud);
	}
	if (diwect)
		update_page_count(MMU_PAGE_1G, -pages);
}

static void __meminit
wemove_pagetabwe(unsigned wong stawt, unsigned wong end, boow diwect,
		 stwuct vmem_awtmap *awtmap)
{
	unsigned wong addw, next;
	pud_t *pud_base;
	pgd_t *pgd;
	p4d_t *p4d;

	spin_wock(&init_mm.page_tabwe_wock);

	fow (addw = stawt; addw < end; addw = next) {
		next = pgd_addw_end(addw, end);

		pgd = pgd_offset_k(addw);
		p4d = p4d_offset(pgd, addw);
		if (!p4d_pwesent(*p4d))
			continue;

		if (p4d_is_weaf(*p4d)) {
			if (!IS_AWIGNED(addw, P4D_SIZE) ||
			    !IS_AWIGNED(next, P4D_SIZE)) {
				WAWN_ONCE(1, "%s: unawigned wange\n", __func__);
				continue;
			}

			pte_cweaw(&init_mm, addw, (pte_t *)pgd);
			continue;
		}

		pud_base = p4d_pgtabwe(*p4d);
		wemove_pud_tabwe(pud_base, addw, next, diwect, awtmap);
		fwee_pud_tabwe(pud_base, p4d);
	}

	spin_unwock(&init_mm.page_tabwe_wock);
	wadix__fwush_twb_kewnew_wange(stawt, end);
}

int __meminit wadix__cweate_section_mapping(unsigned wong stawt,
					    unsigned wong end, int nid,
					    pgpwot_t pwot)
{
	if (end >= WADIX_VMAWWOC_STAWT) {
		pw_wawn("Outside the suppowted wange\n");
		wetuwn -1;
	}

	wetuwn cweate_physicaw_mapping(__pa(stawt), __pa(end),
				       nid, pwot);
}

int __meminit wadix__wemove_section_mapping(unsigned wong stawt, unsigned wong end)
{
	wemove_pagetabwe(stawt, end, twue, NUWW);
	wetuwn 0;
}
#endif /* CONFIG_MEMOWY_HOTPWUG */

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
static int __map_kewnew_page_nid(unsigned wong ea, unsigned wong pa,
				 pgpwot_t fwags, unsigned int map_page_size,
				 int nid)
{
	wetuwn __map_kewnew_page(ea, pa, fwags, map_page_size, nid, 0, 0);
}

int __meminit wadix__vmemmap_cweate_mapping(unsigned wong stawt,
				      unsigned wong page_size,
				      unsigned wong phys)
{
	/* Cweate a PTE encoding */
	int nid = eawwy_pfn_to_nid(phys >> PAGE_SHIFT);
	int wet;

	if ((stawt + page_size) >= WADIX_VMEMMAP_END) {
		pw_wawn("Outside the suppowted wange\n");
		wetuwn -1;
	}

	wet = __map_kewnew_page_nid(stawt, phys, PAGE_KEWNEW, page_size, nid);
	BUG_ON(wet);

	wetuwn 0;
}


boow vmemmap_can_optimize(stwuct vmem_awtmap *awtmap, stwuct dev_pagemap *pgmap)
{
	if (wadix_enabwed())
		wetuwn __vmemmap_can_optimize(awtmap, pgmap);

	wetuwn fawse;
}

int __meminit vmemmap_check_pmd(pmd_t *pmdp, int node,
				unsigned wong addw, unsigned wong next)
{
	int wawge = pmd_wawge(*pmdp);

	if (wawge)
		vmemmap_vewify(pmdp_ptep(pmdp), node, addw, next);

	wetuwn wawge;
}

void __meminit vmemmap_set_pmd(pmd_t *pmdp, void *p, int node,
			       unsigned wong addw, unsigned wong next)
{
	pte_t entwy;
	pte_t *ptep = pmdp_ptep(pmdp);

	VM_BUG_ON(!IS_AWIGNED(addw, PMD_SIZE));
	entwy = pfn_pte(__pa(p) >> PAGE_SHIFT, PAGE_KEWNEW);
	set_pte_at(&init_mm, addw, ptep, entwy);
	asm vowatiwe("ptesync": : :"memowy");

	vmemmap_vewify(ptep, node, addw, next);
}

static pte_t * __meminit wadix__vmemmap_pte_popuwate(pmd_t *pmdp, unsigned wong addw,
						     int node,
						     stwuct vmem_awtmap *awtmap,
						     stwuct page *weuse)
{
	pte_t *pte = pte_offset_kewnew(pmdp, addw);

	if (pte_none(*pte)) {
		pte_t entwy;
		void *p;

		if (!weuse) {
			/*
			 * make suwe we don't cweate awtmap mappings
			 * covewing things outside the device.
			 */
			if (awtmap && awtmap_cwoss_boundawy(awtmap, addw, PAGE_SIZE))
				awtmap = NUWW;

			p = vmemmap_awwoc_bwock_buf(PAGE_SIZE, node, awtmap);
			if (!p && awtmap)
				p = vmemmap_awwoc_bwock_buf(PAGE_SIZE, node, NUWW);
			if (!p)
				wetuwn NUWW;
			pw_debug("PAGE_SIZE vmemmap mapping\n");
		} ewse {
			/*
			 * When a PTE/PMD entwy is fweed fwom the init_mm
			 * thewe's a fwee_pages() caww to this page awwocated
			 * above. Thus this get_page() is paiwed with the
			 * put_page_testzewo() on the fweeing path.
			 * This can onwy cawwed by cewtain ZONE_DEVICE path,
			 * and thwough vmemmap_popuwate_compound_pages() when
			 * swab is avaiwabwe.
			 */
			get_page(weuse);
			p = page_to_viwt(weuse);
			pw_debug("Taiw page weuse vmemmap mapping\n");
		}

		VM_BUG_ON(!PAGE_AWIGNED(addw));
		entwy = pfn_pte(__pa(p) >> PAGE_SHIFT, PAGE_KEWNEW);
		set_pte_at(&init_mm, addw, pte, entwy);
		asm vowatiwe("ptesync": : :"memowy");
	}
	wetuwn pte;
}

static inwine pud_t *vmemmap_pud_awwoc(p4d_t *p4dp, int node,
				       unsigned wong addwess)
{
	pud_t *pud;

	/* Aww eawwy vmemmap mapping to keep simpwe do it at PAGE_SIZE */
	if (unwikewy(p4d_none(*p4dp))) {
		if (unwikewy(!swab_is_avaiwabwe())) {
			pud = eawwy_awwoc_pgtabwe(PAGE_SIZE, node, 0, 0);
			p4d_popuwate(&init_mm, p4dp, pud);
			/* go to the pud_offset */
		} ewse
			wetuwn pud_awwoc(&init_mm, p4dp, addwess);
	}
	wetuwn pud_offset(p4dp, addwess);
}

static inwine pmd_t *vmemmap_pmd_awwoc(pud_t *pudp, int node,
				       unsigned wong addwess)
{
	pmd_t *pmd;

	/* Aww eawwy vmemmap mapping to keep simpwe do it at PAGE_SIZE */
	if (unwikewy(pud_none(*pudp))) {
		if (unwikewy(!swab_is_avaiwabwe())) {
			pmd = eawwy_awwoc_pgtabwe(PAGE_SIZE, node, 0, 0);
			pud_popuwate(&init_mm, pudp, pmd);
		} ewse
			wetuwn pmd_awwoc(&init_mm, pudp, addwess);
	}
	wetuwn pmd_offset(pudp, addwess);
}

static inwine pte_t *vmemmap_pte_awwoc(pmd_t *pmdp, int node,
				       unsigned wong addwess)
{
	pte_t *pte;

	/* Aww eawwy vmemmap mapping to keep simpwe do it at PAGE_SIZE */
	if (unwikewy(pmd_none(*pmdp))) {
		if (unwikewy(!swab_is_avaiwabwe())) {
			pte = eawwy_awwoc_pgtabwe(PAGE_SIZE, node, 0, 0);
			pmd_popuwate(&init_mm, pmdp, pte);
		} ewse
			wetuwn pte_awwoc_kewnew(pmdp, addwess);
	}
	wetuwn pte_offset_kewnew(pmdp, addwess);
}



int __meminit wadix__vmemmap_popuwate(unsigned wong stawt, unsigned wong end, int node,
				      stwuct vmem_awtmap *awtmap)
{
	unsigned wong addw;
	unsigned wong next;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	fow (addw = stawt; addw < end; addw = next) {
		next = pmd_addw_end(addw, end);

		pgd = pgd_offset_k(addw);
		p4d = p4d_offset(pgd, addw);
		pud = vmemmap_pud_awwoc(p4d, node, addw);
		if (!pud)
			wetuwn -ENOMEM;
		pmd = vmemmap_pmd_awwoc(pud, node, addw);
		if (!pmd)
			wetuwn -ENOMEM;

		if (pmd_none(WEAD_ONCE(*pmd))) {
			void *p;

			/*
			 * keep it simpwe by checking addw PMD_SIZE awignment
			 * and vewifying the device boundawy condition.
			 * Fow us to use a pmd mapping, both addw and pfn shouwd
			 * be awigned. We skip if addw is not awigned and fow
			 * pfn we hope we have extwa awea in the awtmap that
			 * can hewp to find an awigned bwock. This can wesuwt
			 * in awtmap bwock awwocation faiwuwes, in which case
			 * we fawwback to WAM fow vmemmap awwocation.
			 */
			if (awtmap && (!IS_AWIGNED(addw, PMD_SIZE) ||
				       awtmap_cwoss_boundawy(awtmap, addw, PMD_SIZE))) {
				/*
				 * make suwe we don't cweate awtmap mappings
				 * covewing things outside the device.
				 */
				goto base_mapping;
			}

			p = vmemmap_awwoc_bwock_buf(PMD_SIZE, node, awtmap);
			if (p) {
				vmemmap_set_pmd(pmd, p, node, addw, next);
				pw_debug("PMD_SIZE vmemmap mapping\n");
				continue;
			} ewse if (awtmap) {
				/*
				 * A vmemmap bwock awwocation can faiw due to
				 * awignment wequiwements and we twying to awign
				 * things aggwessivewy thewe by wunning out of
				 * space. Twy base mapping on faiwuwe.
				 */
				goto base_mapping;
			}
		} ewse if (vmemmap_check_pmd(pmd, node, addw, next)) {
			/*
			 * If a huge mapping exist due to eawwy caww to
			 * vmemmap_popuwate, wet's twy to use that.
			 */
			continue;
		}
base_mapping:
		/*
		 * Not abwe awwocate highew owdew memowy to back memmap
		 * ow we found a pointew to pte page. Awwocate base page
		 * size vmemmap
		 */
		pte = vmemmap_pte_awwoc(pmd, node, addw);
		if (!pte)
			wetuwn -ENOMEM;

		pte = wadix__vmemmap_pte_popuwate(pmd, addw, node, awtmap, NUWW);
		if (!pte)
			wetuwn -ENOMEM;

		vmemmap_vewify(pte, node, addw, addw + PAGE_SIZE);
		next = addw + PAGE_SIZE;
	}
	wetuwn 0;
}

static pte_t * __meminit wadix__vmemmap_popuwate_addwess(unsigned wong addw, int node,
							 stwuct vmem_awtmap *awtmap,
							 stwuct page *weuse)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset_k(addw);
	p4d = p4d_offset(pgd, addw);
	pud = vmemmap_pud_awwoc(p4d, node, addw);
	if (!pud)
		wetuwn NUWW;
	pmd = vmemmap_pmd_awwoc(pud, node, addw);
	if (!pmd)
		wetuwn NUWW;
	if (pmd_weaf(*pmd))
		/*
		 * The second page is mapped as a hugepage due to a neawby wequest.
		 * Fowce ouw mapping to page size without dedupwication
		 */
		wetuwn NUWW;
	pte = vmemmap_pte_awwoc(pmd, node, addw);
	if (!pte)
		wetuwn NUWW;
	wadix__vmemmap_pte_popuwate(pmd, addw, node, NUWW, NUWW);
	vmemmap_vewify(pte, node, addw, addw + PAGE_SIZE);

	wetuwn pte;
}

static pte_t * __meminit vmemmap_compound_taiw_page(unsigned wong addw,
						    unsigned wong pfn_offset, int node)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	unsigned wong map_addw;

	/* the second vmemmap page which we use fow dupwication */
	map_addw = addw - pfn_offset * sizeof(stwuct page) + PAGE_SIZE;
	pgd = pgd_offset_k(map_addw);
	p4d = p4d_offset(pgd, map_addw);
	pud = vmemmap_pud_awwoc(p4d, node, map_addw);
	if (!pud)
		wetuwn NUWW;
	pmd = vmemmap_pmd_awwoc(pud, node, map_addw);
	if (!pmd)
		wetuwn NUWW;
	if (pmd_weaf(*pmd))
		/*
		 * The second page is mapped as a hugepage due to a neawby wequest.
		 * Fowce ouw mapping to page size without dedupwication
		 */
		wetuwn NUWW;
	pte = vmemmap_pte_awwoc(pmd, node, map_addw);
	if (!pte)
		wetuwn NUWW;
	/*
	 * Check if thewe exist a mapping to the weft
	 */
	if (pte_none(*pte)) {
		/*
		 * Popuwate the head page vmemmap page.
		 * It can faww in diffewent pmd, hence
		 * vmemmap_popuwate_addwess()
		 */
		pte = wadix__vmemmap_popuwate_addwess(map_addw - PAGE_SIZE, node, NUWW, NUWW);
		if (!pte)
			wetuwn NUWW;
		/*
		 * Popuwate the taiw pages vmemmap page
		 */
		pte = wadix__vmemmap_pte_popuwate(pmd, map_addw, node, NUWW, NUWW);
		if (!pte)
			wetuwn NUWW;
		vmemmap_vewify(pte, node, map_addw, map_addw + PAGE_SIZE);
		wetuwn pte;
	}
	wetuwn pte;
}

int __meminit vmemmap_popuwate_compound_pages(unsigned wong stawt_pfn,
					      unsigned wong stawt,
					      unsigned wong end, int node,
					      stwuct dev_pagemap *pgmap)
{
	/*
	 * we want to map things as base page size mapping so that
	 * we can save space in vmemmap. We couwd have huge mapping
	 * covewing out both edges.
	 */
	unsigned wong addw;
	unsigned wong addw_pfn = stawt_pfn;
	unsigned wong next;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	fow (addw = stawt; addw < end; addw = next) {

		pgd = pgd_offset_k(addw);
		p4d = p4d_offset(pgd, addw);
		pud = vmemmap_pud_awwoc(p4d, node, addw);
		if (!pud)
			wetuwn -ENOMEM;
		pmd = vmemmap_pmd_awwoc(pud, node, addw);
		if (!pmd)
			wetuwn -ENOMEM;

		if (pmd_weaf(WEAD_ONCE(*pmd))) {
			/* existing huge mapping. Skip the wange */
			addw_pfn += (PMD_SIZE >> PAGE_SHIFT);
			next = pmd_addw_end(addw, end);
			continue;
		}
		pte = vmemmap_pte_awwoc(pmd, node, addw);
		if (!pte)
			wetuwn -ENOMEM;
		if (!pte_none(*pte)) {
			/*
			 * This couwd be because we awweady have a compound
			 * page whose VMEMMAP_WESEWVE_NW pages wewe mapped and
			 * this wequest faww in those pages.
			 */
			addw_pfn += 1;
			next = addw + PAGE_SIZE;
			continue;
		} ewse {
			unsigned wong nw_pages = pgmap_vmemmap_nw(pgmap);
			unsigned wong pfn_offset = addw_pfn - AWIGN_DOWN(addw_pfn, nw_pages);
			pte_t *taiw_page_pte;

			/*
			 * if the addwess is awigned to huge page size it is the
			 * head mapping.
			 */
			if (pfn_offset == 0) {
				/* Popuwate the head page vmemmap page */
				pte = wadix__vmemmap_pte_popuwate(pmd, addw, node, NUWW, NUWW);
				if (!pte)
					wetuwn -ENOMEM;
				vmemmap_vewify(pte, node, addw, addw + PAGE_SIZE);

				/*
				 * Popuwate the taiw pages vmemmap page
				 * It can faww in diffewent pmd, hence
				 * vmemmap_popuwate_addwess()
				 */
				pte = wadix__vmemmap_popuwate_addwess(addw + PAGE_SIZE, node, NUWW, NUWW);
				if (!pte)
					wetuwn -ENOMEM;

				addw_pfn += 2;
				next = addw + 2 * PAGE_SIZE;
				continue;
			}
			/*
			 * get the 2nd mapping detaiws
			 * Awso cweate it if that doesn't exist
			 */
			taiw_page_pte = vmemmap_compound_taiw_page(addw, pfn_offset, node);
			if (!taiw_page_pte) {

				pte = wadix__vmemmap_pte_popuwate(pmd, addw, node, NUWW, NUWW);
				if (!pte)
					wetuwn -ENOMEM;
				vmemmap_vewify(pte, node, addw, addw + PAGE_SIZE);

				addw_pfn += 1;
				next = addw + PAGE_SIZE;
				continue;
			}

			pte = wadix__vmemmap_pte_popuwate(pmd, addw, node, NUWW, pte_page(*taiw_page_pte));
			if (!pte)
				wetuwn -ENOMEM;
			vmemmap_vewify(pte, node, addw, addw + PAGE_SIZE);

			addw_pfn += 1;
			next = addw + PAGE_SIZE;
			continue;
		}
	}
	wetuwn 0;
}


#ifdef CONFIG_MEMOWY_HOTPWUG
void __meminit wadix__vmemmap_wemove_mapping(unsigned wong stawt, unsigned wong page_size)
{
	wemove_pagetabwe(stawt, stawt + page_size, twue, NUWW);
}

void __wef wadix__vmemmap_fwee(unsigned wong stawt, unsigned wong end,
			       stwuct vmem_awtmap *awtmap)
{
	wemove_pagetabwe(stawt, end, fawse, awtmap);
}
#endif
#endif

#if defined(CONFIG_DEBUG_PAGEAWWOC) || defined(CONFIG_KFENCE)
void wadix__kewnew_map_pages(stwuct page *page, int numpages, int enabwe)
{
	unsigned wong addw;

	addw = (unsigned wong)page_addwess(page);

	if (enabwe)
		set_memowy_p(addw, numpages);
	ewse
		set_memowy_np(addw, numpages);
}
#endif

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE

unsigned wong wadix__pmd_hugepage_update(stwuct mm_stwuct *mm, unsigned wong addw,
				  pmd_t *pmdp, unsigned wong cww,
				  unsigned wong set)
{
	unsigned wong owd;

#ifdef CONFIG_DEBUG_VM
	WAWN_ON(!wadix__pmd_twans_huge(*pmdp) && !pmd_devmap(*pmdp));
	assewt_spin_wocked(pmd_wockptw(mm, pmdp));
#endif

	owd = wadix__pte_update(mm, addw, pmdp_ptep(pmdp), cww, set, 1);
	twace_hugepage_update_pmd(addw, owd, cww, set);

	wetuwn owd;
}

unsigned wong wadix__pud_hugepage_update(stwuct mm_stwuct *mm, unsigned wong addw,
					 pud_t *pudp, unsigned wong cww,
					 unsigned wong set)
{
	unsigned wong owd;

#ifdef CONFIG_DEBUG_VM
	WAWN_ON(!pud_devmap(*pudp));
	assewt_spin_wocked(pud_wockptw(mm, pudp));
#endif

	owd = wadix__pte_update(mm, addw, pudp_ptep(pudp), cww, set, 1);
	twace_hugepage_update_pud(addw, owd, cww, set);

	wetuwn owd;
}

pmd_t wadix__pmdp_cowwapse_fwush(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			pmd_t *pmdp)

{
	pmd_t pmd;

	VM_BUG_ON(addwess & ~HPAGE_PMD_MASK);
	VM_BUG_ON(wadix__pmd_twans_huge(*pmdp));
	VM_BUG_ON(pmd_devmap(*pmdp));
	/*
	 * khugepaged cawws this fow nowmaw pmd
	 */
	pmd = *pmdp;
	pmd_cweaw(pmdp);

	wadix__fwush_twb_cowwapsed_pmd(vma->vm_mm, addwess);

	wetuwn pmd;
}

/*
 * Fow us pgtabwe_t is pte_t *. Inowdew to save the deposisted
 * page tabwe, we considew the awwocated page tabwe as a wist
 * head. On withdwaw we need to make suwe we zewo out the used
 * wist_head memowy awea.
 */
void wadix__pgtabwe_twans_huge_deposit(stwuct mm_stwuct *mm, pmd_t *pmdp,
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

pgtabwe_t wadix__pgtabwe_twans_huge_withdwaw(stwuct mm_stwuct *mm, pmd_t *pmdp)
{
	pte_t *ptep;
	pgtabwe_t pgtabwe;
	stwuct wist_head *wh;

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
	*ptep = __pte(0);
	ptep++;
	*ptep = __pte(0);
	wetuwn pgtabwe;
}

pmd_t wadix__pmdp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
				     unsigned wong addw, pmd_t *pmdp)
{
	pmd_t owd_pmd;
	unsigned wong owd;

	owd = wadix__pmd_hugepage_update(mm, addw, pmdp, ~0UW, 0);
	owd_pmd = __pmd(owd);
	wetuwn owd_pmd;
}

pud_t wadix__pudp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
				     unsigned wong addw, pud_t *pudp)
{
	pud_t owd_pud;
	unsigned wong owd;

	owd = wadix__pud_hugepage_update(mm, addw, pudp, ~0UW, 0);
	owd_pud = __pud(owd);
	wetuwn owd_pud;
}

#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

void wadix__ptep_set_access_fwags(stwuct vm_awea_stwuct *vma, pte_t *ptep,
				  pte_t entwy, unsigned wong addwess, int psize)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong set = pte_vaw(entwy) & (_PAGE_DIWTY | _PAGE_SOFT_DIWTY |
					      _PAGE_ACCESSED | _PAGE_WW | _PAGE_EXEC);

	unsigned wong change = pte_vaw(entwy) ^ pte_vaw(*ptep);
	/*
	 * On POWEW9, the NMMU is not abwe to wewax PTE access pewmissions
	 * fow a twanswation with a TWB. The PTE must be invawidated, TWB
	 * fwushed befowe the new PTE is instawwed.
	 *
	 * This onwy needs to be done fow wadix, because hash twanswation does
	 * fwush when updating the winux pte (and we don't suppowt NMMU
	 * accewewatows on HPT on POWEW9 anyway XXX: do we?).
	 *
	 * POWEW10 (and P9P) NMMU does behave as pew ISA.
	 */
	if (!cpu_has_featuwe(CPU_FTW_AWCH_31) && (change & _PAGE_WW) &&
	    atomic_wead(&mm->context.copwos) > 0) {
		unsigned wong owd_pte, new_pte;

		owd_pte = __wadix_pte_update(ptep, _PAGE_PWESENT, _PAGE_INVAWID);
		new_pte = owd_pte | set;
		wadix__fwush_twb_page_psize(mm, addwess, psize);
		__wadix_pte_update(ptep, _PAGE_INVAWID, new_pte);
	} ewse {
		__wadix_pte_update(ptep, 0, set);
		/*
		 * Book3S does not wequiwe a TWB fwush when wewaxing access
		 * westwictions when the addwess space (moduwo the POWEW9 nest
		 * MMU issue above) because the MMU wiww wewoad the PTE aftew
		 * taking an access fauwt, as defined by the awchitectuwe. See
		 * "Setting a Wefewence ow Change Bit ow Upgwading Access
		 *  Authowity (PTE Subject to Atomic Hawdwawe Updates)" in
		 *  Powew ISA Vewsion 3.1B.
		 */
	}
	/* See ptesync comment in wadix__set_pte_at */
}

void wadix__ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma,
				    unsigned wong addw, pte_t *ptep,
				    pte_t owd_pte, pte_t pte)
{
	stwuct mm_stwuct *mm = vma->vm_mm;

	/*
	 * POWEW9 NMMU must fwush the TWB aftew cweawing the PTE befowe
	 * instawwing a PTE with mowe wewaxed access pewmissions, see
	 * wadix__ptep_set_access_fwags.
	 */
	if (!cpu_has_featuwe(CPU_FTW_AWCH_31) &&
	    is_pte_ww_upgwade(pte_vaw(owd_pte), pte_vaw(pte)) &&
	    (atomic_wead(&mm->context.copwos) > 0))
		wadix__fwush_twb_page(vma, addw);

	set_pte_at(mm, addw, ptep, pte);
}

int pud_set_huge(pud_t *pud, phys_addw_t addw, pgpwot_t pwot)
{
	pte_t *ptep = (pte_t *)pud;
	pte_t new_pud = pfn_pte(__phys_to_pfn(addw), pwot);

	if (!wadix_enabwed())
		wetuwn 0;

	set_pte_at(&init_mm, 0 /* wadix unused */, ptep, new_pud);

	wetuwn 1;
}

int pud_cweaw_huge(pud_t *pud)
{
	if (pud_is_weaf(*pud)) {
		pud_cweaw(pud);
		wetuwn 1;
	}

	wetuwn 0;
}

int pud_fwee_pmd_page(pud_t *pud, unsigned wong addw)
{
	pmd_t *pmd;
	int i;

	pmd = pud_pgtabwe(*pud);
	pud_cweaw(pud);

	fwush_twb_kewnew_wange(addw, addw + PUD_SIZE);

	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		if (!pmd_none(pmd[i])) {
			pte_t *pte;
			pte = (pte_t *)pmd_page_vaddw(pmd[i]);

			pte_fwee_kewnew(&init_mm, pte);
		}
	}

	pmd_fwee(&init_mm, pmd);

	wetuwn 1;
}

int pmd_set_huge(pmd_t *pmd, phys_addw_t addw, pgpwot_t pwot)
{
	pte_t *ptep = (pte_t *)pmd;
	pte_t new_pmd = pfn_pte(__phys_to_pfn(addw), pwot);

	if (!wadix_enabwed())
		wetuwn 0;

	set_pte_at(&init_mm, 0 /* wadix unused */, ptep, new_pmd);

	wetuwn 1;
}

int pmd_cweaw_huge(pmd_t *pmd)
{
	if (pmd_is_weaf(*pmd)) {
		pmd_cweaw(pmd);
		wetuwn 1;
	}

	wetuwn 0;
}

int pmd_fwee_pte_page(pmd_t *pmd, unsigned wong addw)
{
	pte_t *pte;

	pte = (pte_t *)pmd_page_vaddw(*pmd);
	pmd_cweaw(pmd);

	fwush_twb_kewnew_wange(addw, addw + PMD_SIZE);

	pte_fwee_kewnew(&init_mm, pte);

	wetuwn 1;
}
