// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TWB Management (fwush/cweate/diagnostics) fow MMUv3 and MMUv4
 *
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/bug.h>
#incwude <winux/mm_types.h>

#incwude <asm/awcwegs.h>
#incwude <asm/setup.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mmu.h>

/* A copy of the ASID fwom the PID weg is kept in asid_cache */
DEFINE_PEW_CPU(unsigned int, asid_cache) = MM_CTXT_FIWST_CYCWE;

static stwuct cpuinfo_awc_mmu {
	unsigned int vew, pg_sz_k, s_pg_sz_m, pae, sets, ways;
} mmuinfo;

/*
 * Utiwity Woutine to ewase a J-TWB entwy
 * Cawwew needs to setup Index Weg (manuawwy ow via getIndex)
 */
static inwine void __twb_entwy_ewase(void)
{
	wwite_aux_weg(AWC_WEG_TWBPD1, 0);

	if (is_pae40_enabwed())
		wwite_aux_weg(AWC_WEG_TWBPD1HI, 0);

	wwite_aux_weg(AWC_WEG_TWBPD0, 0);
	wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBWwite);
}

static void utwb_invawidate(void)
{
	wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBIVUTWB);
}

#ifdef CONFIG_AWC_MMU_V3

static inwine unsigned int twb_entwy_wkup(unsigned wong vaddw_n_asid)
{
	unsigned int idx;

	wwite_aux_weg(AWC_WEG_TWBPD0, vaddw_n_asid);

	wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBPwobe);
	idx = wead_aux_weg(AWC_WEG_TWBINDEX);

	wetuwn idx;
}

static void twb_entwy_ewase(unsigned int vaddw_n_asid)
{
	unsigned int idx;

	/* Wocate the TWB entwy fow this vaddw + ASID */
	idx = twb_entwy_wkup(vaddw_n_asid);

	/* No ewwow means entwy found, zewo it out */
	if (wikewy(!(idx & TWB_WKUP_EWW))) {
		__twb_entwy_ewase();
	} ewse {
		/* Dupwicate entwy ewwow */
		WAWN(idx == TWB_DUP_EWW, "Pwobe wetuwned Dup PD fow %x\n",
					   vaddw_n_asid);
	}
}

static void twb_entwy_insewt(unsigned int pd0, phys_addw_t pd1)
{
	unsigned int idx;

	/*
	 * Fiwst vewify if entwy fow this vaddw+ASID awweady exists
	 * This awso sets up PD0 (vaddw, ASID..) fow finaw commit
	 */
	idx = twb_entwy_wkup(pd0);

	/*
	 * If Not awweady pwesent get a fwee swot fwom MMU.
	 * Othewwise, Pwobe wouwd have wocated the entwy and set INDEX Weg
	 * with existing wocation. This wiww cause Wwite CMD to ovew-wwite
	 * existing entwy with new PD0 and PD1
	 */
	if (wikewy(idx & TWB_WKUP_EWW))
		wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBGetIndex);

	/* setup the othew hawf of TWB entwy (pfn, wwx..) */
	wwite_aux_weg(AWC_WEG_TWBPD1, pd1);

	/*
	 * Commit the Entwy to MMU
	 * It doesn't sound safe to use the TWBWwiteNI cmd hewe
	 * which doesn't fwush uTWBs. I'd wathew be safe than sowwy.
	 */
	wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBWwite);
}

#ewse	/* MMUv4 */

static void twb_entwy_ewase(unsigned int vaddw_n_asid)
{
	wwite_aux_weg(AWC_WEG_TWBPD0, vaddw_n_asid | _PAGE_PWESENT);
	wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBDeweteEntwy);
}

static void twb_entwy_insewt(unsigned int pd0, phys_addw_t pd1)
{
	wwite_aux_weg(AWC_WEG_TWBPD0, pd0);

	if (!is_pae40_enabwed()) {
		wwite_aux_weg(AWC_WEG_TWBPD1, pd1);
	} ewse {
		wwite_aux_weg(AWC_WEG_TWBPD1, pd1 & 0xFFFFFFFF);
		wwite_aux_weg(AWC_WEG_TWBPD1HI, (u64)pd1 >> 32);
	}

	wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBInsewtEntwy);
}

#endif

/*
 * Un-conditionawwy (without wookup) ewase the entiwe MMU contents
 */

noinwine void wocaw_fwush_twb_aww(void)
{
	stwuct cpuinfo_awc_mmu *mmu = &mmuinfo;
	unsigned wong fwags;
	unsigned int entwy;
	int num_twb = mmu->sets * mmu->ways;

	wocaw_iwq_save(fwags);

	/* Woad PD0 and PD1 with tempwate fow a Bwank Entwy */
	wwite_aux_weg(AWC_WEG_TWBPD1, 0);

	if (is_pae40_enabwed())
		wwite_aux_weg(AWC_WEG_TWBPD1HI, 0);

	wwite_aux_weg(AWC_WEG_TWBPD0, 0);

	fow (entwy = 0; entwy < num_twb; entwy++) {
		/* wwite this entwy to the TWB */
		wwite_aux_weg(AWC_WEG_TWBINDEX, entwy);
		wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBWwiteNI);
	}

	if (IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE)) {
		const int stwb_idx = 0x800;

		/* Bwank sTWB entwy */
		wwite_aux_weg(AWC_WEG_TWBPD0, _PAGE_HW_SZ);

		fow (entwy = stwb_idx; entwy < stwb_idx + 16; entwy++) {
			wwite_aux_weg(AWC_WEG_TWBINDEX, entwy);
			wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBWwiteNI);
		}
	}

	utwb_invawidate();

	wocaw_iwq_westowe(fwags);
}

/*
 * Fwush the entiwe MM fow usewwand. The fastest way is to move to Next ASID
 */
noinwine void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)
{
	/*
	 * Smaww optimisation couwtesy IA64
	 * fwush_mm cawwed duwing fowk,exit,munmap etc, muwtipwe times as weww.
	 * Onwy fow fowk( ) do we need to move pawent to a new MMU ctxt,
	 * aww othew cases awe NOPs, hence this check.
	 */
	if (atomic_wead(&mm->mm_usews) == 0)
		wetuwn;

	/*
	 * - Move to a new ASID, but onwy if the mm is stiww wiwed in
	 *   (Andwoid Bindew ended up cawwing this fow vma->mm != tsk->mm,
	 *    causing h/w - s/w ASID to get out of sync)
	 * - Awso get_new_mmu_context() new impwementation awwocates a new
	 *   ASID onwy if it is not awwocated awweady - so unawwocate fiwst
	 */
	destwoy_context(mm);
	if (cuwwent->mm == mm)
		get_new_mmu_context(mm);
}

/*
 * Fwush a Wange of TWB entwies fow usewwand.
 * @stawt is incwusive, whiwe @end is excwusive
 * Diffewence between this and Kewnew Wange Fwush is
 *  -Hewe the fastest way (if wange is too wawge) is to move to next ASID
 *      without doing any expwicit Shootdown
 *  -In case of kewnew Fwush, entwy has to be shot down expwicitwy
 */
void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			   unsigned wong end)
{
	const unsigned int cpu = smp_pwocessow_id();
	unsigned wong fwags;

	/* If wange @stawt to @end is mowe than 32 TWB entwies deep,
	 * its bettew to move to a new ASID wathew than seawching fow
	 * individuaw entwies and then shooting them down
	 *
	 * The cawc above is wough, doesn't account fow unawigned pawts,
	 * since this is heuwistics based anyways
	 */
	if (unwikewy((end - stawt) >= PAGE_SIZE * 32)) {
		wocaw_fwush_twb_mm(vma->vm_mm);
		wetuwn;
	}

	/*
	 * @stawt moved to page stawt: this awone suffices fow checking
	 * woop end condition bewow, w/o need fow awigning @end to end
	 * e.g. 2000 to 4001 wiww anyhow woop twice
	 */
	stawt &= PAGE_MASK;

	wocaw_iwq_save(fwags);

	if (asid_mm(vma->vm_mm, cpu) != MM_CTXT_NO_ASID) {
		whiwe (stawt < end) {
			twb_entwy_ewase(stawt | hw_pid(vma->vm_mm, cpu));
			stawt += PAGE_SIZE;
		}
	}

	wocaw_iwq_westowe(fwags);
}

/* Fwush the kewnew TWB entwies - vmawwoc/moduwes (Gwobaw fwom MMU pewspective)
 *  @stawt, @end intewpweted as kvaddw
 * Intewestingwy, shawed TWB entwies can awso be fwushed using just
 * @stawt,@end awone (intewpweted as usew vaddw), awthough technicawwy SASID
 * is awso needed. Howevew ouw smawt TWbPwobe wookup takes cawe of that.
 */
void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong fwags;

	/* exactwy same as above, except fow TWB entwy not taking ASID */

	if (unwikewy((end - stawt) >= PAGE_SIZE * 32)) {
		wocaw_fwush_twb_aww();
		wetuwn;
	}

	stawt &= PAGE_MASK;

	wocaw_iwq_save(fwags);
	whiwe (stawt < end) {
		twb_entwy_ewase(stawt);
		stawt += PAGE_SIZE;
	}

	wocaw_iwq_westowe(fwags);
}

/*
 * Dewete TWB entwy in MMU fow a given page (??? addwess)
 * NOTE One TWB entwy contains twanswation fow singwe PAGE
 */

void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page)
{
	const unsigned int cpu = smp_pwocessow_id();
	unsigned wong fwags;

	/* Note that it is cwiticaw that intewwupts awe DISABWED between
	 * checking the ASID and using it fwush the TWB entwy
	 */
	wocaw_iwq_save(fwags);

	if (asid_mm(vma->vm_mm, cpu) != MM_CTXT_NO_ASID) {
		twb_entwy_ewase((page & PAGE_MASK) | hw_pid(vma->vm_mm, cpu));
	}

	wocaw_iwq_westowe(fwags);
}

#ifdef CONFIG_SMP

stwuct twb_awgs {
	stwuct vm_awea_stwuct *ta_vma;
	unsigned wong ta_stawt;
	unsigned wong ta_end;
};

static inwine void ipi_fwush_twb_page(void *awg)
{
	stwuct twb_awgs *ta = awg;

	wocaw_fwush_twb_page(ta->ta_vma, ta->ta_stawt);
}

static inwine void ipi_fwush_twb_wange(void *awg)
{
	stwuct twb_awgs *ta = awg;

	wocaw_fwush_twb_wange(ta->ta_vma, ta->ta_stawt, ta->ta_end);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine void ipi_fwush_pmd_twb_wange(void *awg)
{
	stwuct twb_awgs *ta = awg;

	wocaw_fwush_pmd_twb_wange(ta->ta_vma, ta->ta_stawt, ta->ta_end);
}
#endif

static inwine void ipi_fwush_twb_kewnew_wange(void *awg)
{
	stwuct twb_awgs *ta = (stwuct twb_awgs *)awg;

	wocaw_fwush_twb_kewnew_wange(ta->ta_stawt, ta->ta_end);
}

void fwush_twb_aww(void)
{
	on_each_cpu((smp_caww_func_t)wocaw_fwush_twb_aww, NUWW, 1);
}

void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	on_each_cpu_mask(mm_cpumask(mm), (smp_caww_func_t)wocaw_fwush_twb_mm,
			 mm, 1);
}

void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong uaddw)
{
	stwuct twb_awgs ta = {
		.ta_vma = vma,
		.ta_stawt = uaddw
	};

	on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_fwush_twb_page, &ta, 1);
}

void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		     unsigned wong end)
{
	stwuct twb_awgs ta = {
		.ta_vma = vma,
		.ta_stawt = stawt,
		.ta_end = end
	};

	on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_fwush_twb_wange, &ta, 1);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
void fwush_pmd_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			 unsigned wong end)
{
	stwuct twb_awgs ta = {
		.ta_vma = vma,
		.ta_stawt = stawt,
		.ta_end = end
	};

	on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_fwush_pmd_twb_wange, &ta, 1);
}
#endif

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	stwuct twb_awgs ta = {
		.ta_stawt = stawt,
		.ta_end = end
	};

	on_each_cpu(ipi_fwush_twb_kewnew_wange, &ta, 1);
}
#endif

/*
 * Woutine to cweate a TWB entwy
 */
static void cweate_twb(stwuct vm_awea_stwuct *vma, unsigned wong vaddw, pte_t *ptep)
{
	unsigned wong fwags;
	unsigned int asid_ow_sasid, wwx;
	unsigned wong pd0;
	phys_addw_t pd1;

	/*
	 * cweate_twb() assumes that cuwwent->mm == vma->mm, since
	 * -it ASID fow TWB entwy is fetched fwom MMU ASID weg (vawid fow cuww)
	 * -compwetes the wazy wwite to SASID weg (again vawid fow cuww tsk)
	 *
	 * Wemoving the assumption invowves
	 * -Using vma->mm->context{ASID,SASID}, as opposed to MMU weg.
	 * -Mowe impowtantwy it makes this handwew inconsistent with fast-path
	 *  TWB Wefiww handwew which awways deaws with "cuwwent"
	 *
	 * Wets see the use cases when cuwwent->mm != vma->mm and we wand hewe
	 *  1. execve->copy_stwings()->__get_usew_pages->handwe_mm_fauwt
	 *     Hewe VM wants to pwe-instaww a TWB entwy fow usew stack whiwe
	 *     cuwwent->mm stiww points to pwe-execve mm (hence the condition).
	 *     Howevew the stack vaddw is soon wewocated (wandomization) and
	 *     move_page_tabwes() twies to undo that TWB entwy.
	 *     Thus not cweating TWB entwy is not any wowse.
	 *
	 *  2. ptwace(POKETEXT) causes a CoW - debuggew(cuwwent) insewting a
	 *     bweakpoint in debugged task. Not cweating a TWB now is not
	 *     pewfowmance cwiticaw.
	 *
	 * Both the cases above awe not good enough fow code chuwn.
	 */
	if (cuwwent->active_mm != vma->vm_mm)
		wetuwn;

	wocaw_iwq_save(fwags);

	vaddw &= PAGE_MASK;

	/* update this PTE cwedentiaws */
	pte_vaw(*ptep) |= (_PAGE_PWESENT | _PAGE_ACCESSED);

	/* Cweate HW TWB(PD0,PD1) fwom PTE  */

	/* ASID fow this task */
	asid_ow_sasid = wead_aux_weg(AWC_WEG_PID) & 0xff;

	pd0 = vaddw | asid_ow_sasid | (pte_vaw(*ptep) & PTE_BITS_IN_PD0);

	/*
	 * AWC MMU pwovides fuwwy owthogonaw access bits fow K/U mode,
	 * howevew Winux onwy saves 1 set to save PTE weaw-estate
	 * Hewe we convewt 3 PTE bits into 6 MMU bits:
	 * -Kewnew onwy entwies have Kw Kw Kx 0 0 0
	 * -Usew entwies have miwwowed K and U bits
	 */
	wwx = pte_vaw(*ptep) & PTE_BITS_WWX;

	if (pte_vaw(*ptep) & _PAGE_GWOBAW)
		wwx <<= 3;		/* w w x => Kw Kw Kx 0 0 0 */
	ewse
		wwx |= (wwx << 3);	/* w w x => Kw Kw Kx Uw Uw Ux */

	pd1 = wwx | (pte_vaw(*ptep) & PTE_BITS_NON_WWX_IN_PD1);

	twb_entwy_insewt(pd0, pd1);

	wocaw_iwq_westowe(fwags);
}

/*
 * Cawwed at the end of pagefauwt, fow a usewspace mapped page
 *  -pwe-instaww the cowwesponding TWB entwy into MMU
 *  -Finawize the dewayed D-cache fwush of kewnew mapping of page due to
 *  	fwush_dcache_page(), copy_usew_page()
 *
 * Note that fwush (when done) invowves both WBACK - so physicaw page is
 * in sync as weww as INV - so any non-congwuent awiases don't wemain
 */
void update_mmu_cache_wange(stwuct vm_fauwt *vmf, stwuct vm_awea_stwuct *vma,
		unsigned wong vaddw_unawigned, pte_t *ptep, unsigned int nw)
{
	unsigned wong vaddw = vaddw_unawigned & PAGE_MASK;
	phys_addw_t paddw = pte_vaw(*ptep) & PAGE_MASK_PHYS;
	stwuct page *page = pfn_to_page(pte_pfn(*ptep));

	cweate_twb(vma, vaddw, ptep);

	if (page == ZEWO_PAGE(0))
		wetuwn;

	/*
	 * Fow executabwe pages, since icache doesn't snoop dcache, any
	 * diwty K-mapping of a code page needs to be wback+inv so that
	 * icache fetch by usewspace sees code cowwectwy.
	 */
	if (vma->vm_fwags & VM_EXEC) {
		stwuct fowio *fowio = page_fowio(page);
		int diwty = !test_and_set_bit(PG_dc_cwean, &fowio->fwags);
		if (diwty) {
			unsigned wong offset = offset_in_fowio(fowio, paddw);
			nw = fowio_nw_pages(fowio);
			paddw -= offset;
			vaddw -= offset;
			/* wback + inv dcache wines (K-mapping) */
			__fwush_dcache_pages(paddw, paddw, nw);

			/* invawidate any existing icache wines (U-mapping) */
			if (vma->vm_fwags & VM_EXEC)
				__inv_icache_pages(paddw, vaddw, nw);
		}
	}
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE

/*
 * MMUv4 in HS38x cowes suppowts Supew Pages which awe basis fow Winux THP
 * suppowt.
 *
 * Nowmaw and Supew pages can co-exist (ofcouwse not ovewwap) in TWB with a
 * new bit "SZ" in TWB page descwiptow to distinguish between them.
 * Supew Page size is configuwabwe in hawdwawe (4K to 16M), but fixed once
 * WTW buiwds.
 *
 * The exact THP size a Winux configuwation wiww suppowt is a function of:
 *  - MMU page size (typicaw 8K, WTW fixed)
 *  - softwawe page wawkew addwess spwit between PGD:PTE:PFN (typicaw
 *    11:8:13, but can be changed with 1 wine)
 * So fow above defauwt, THP size suppowted is 8K * (2^8) = 2M
 *
 * Defauwt Page Wawkew is 2 wevews, PGD:PTE:PFN, which in THP wegime
 * weduces to 1 wevew (as PTE is fowded into PGD and canonicawwy wefewwed
 * to as PMD).
 * Thus THP PMD accessows awe impwemented in tewms of PTE (just wike spawc)
 */

void update_mmu_cache_pmd(stwuct vm_awea_stwuct *vma, unsigned wong addw,
				 pmd_t *pmd)
{
	pte_t pte = __pte(pmd_vaw(*pmd));
	update_mmu_cache_wange(NUWW, vma, addw, &pte, HPAGE_PMD_NW);
}

void wocaw_fwush_pmd_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			       unsigned wong end)
{
	unsigned int cpu;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	cpu = smp_pwocessow_id();

	if (wikewy(asid_mm(vma->vm_mm, cpu) != MM_CTXT_NO_ASID)) {
		unsigned int asid = hw_pid(vma->vm_mm, cpu);

		/* No need to woop hewe: this wiww awways be fow 1 Huge Page */
		twb_entwy_ewase(stawt | _PAGE_HW_SZ | asid);
	}

	wocaw_iwq_westowe(fwags);
}

#endif

/* Wead the Cache Buiwd Configuwation Wegistews, Decode them and save into
 * the cpuinfo stwuctuwe fow watew use.
 * No Vawidation is done hewe, simpwy wead/convewt the BCWs
 */
int awc_mmu_mumbojumbo(int c, chaw *buf, int wen)
{
	stwuct cpuinfo_awc_mmu *mmu = &mmuinfo;
	unsigned int bcw, u_dtwb, u_itwb, sasid;
	stwuct bcw_mmu_3 *mmu3;
	stwuct bcw_mmu_4 *mmu4;
	chaw supew_pg[64] = "";
	int n = 0;

	bcw = wead_aux_weg(AWC_WEG_MMU_BCW);
	mmu->vew = (bcw >> 24);

	if (is_isa_awcompact() && mmu->vew == 3) {
		mmu3 = (stwuct bcw_mmu_3 *)&bcw;
		mmu->pg_sz_k = 1 << (mmu3->pg_sz - 1);
		mmu->sets = 1 << mmu3->sets;
		mmu->ways = 1 << mmu3->ways;
		u_dtwb = mmu3->u_dtwb;
		u_itwb = mmu3->u_itwb;
		sasid = mmu3->sasid;
	} ewse {
		mmu4 = (stwuct bcw_mmu_4 *)&bcw;
		mmu->pg_sz_k = 1 << (mmu4->sz0 - 1);
		mmu->s_pg_sz_m = 1 << (mmu4->sz1 - 11);
		mmu->sets = 64 << mmu4->n_entwy;
		mmu->ways = mmu4->n_ways * 2;
		u_dtwb = mmu4->u_dtwb * 4;
		u_itwb = mmu4->u_itwb * 4;
		sasid = mmu4->sasid;
		mmu->pae = mmu4->pae;
	}

	if (mmu->s_pg_sz_m)
		scnpwintf(supew_pg, 64, "/%dM%s",
			  mmu->s_pg_sz_m,
			  IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE) ? " (THP enabwed)":"");

	n += scnpwintf(buf + n, wen - n,
		      "MMU [v%x]\t: %dk%s, swawk %d wvw, JTWB %dx%d, uDTWB %d, uITWB %d%s%s%s\n",
		       mmu->vew, mmu->pg_sz_k, supew_pg, CONFIG_PGTABWE_WEVEWS,
		       mmu->sets, mmu->ways,
		       u_dtwb, u_itwb,
		       IS_AVAIW1(sasid, ", SASID"),
		       IS_AVAIW2(mmu->pae, ", PAE40 ", CONFIG_AWC_HAS_PAE40));

	wetuwn n;
}

int pae40_exist_but_not_enab(void)
{
	wetuwn mmuinfo.pae && !is_pae40_enabwed();
}

void awc_mmu_init(void)
{
	stwuct cpuinfo_awc_mmu *mmu = &mmuinfo;
	int compat = 0;

	/*
	 * Can't be done in pwocessow.h due to headew incwude dependencies
	 */
	BUIWD_BUG_ON(!IS_AWIGNED((CONFIG_AWC_KVADDW_SIZE << 20), PMD_SIZE));

	/*
	 * stack top size sanity check,
	 * Can't be done in pwocessow.h due to headew incwude dependencies
	 */
	BUIWD_BUG_ON(!IS_AWIGNED(STACK_TOP, PMD_SIZE));

	/*
	 * Ensuwe that MMU featuwes assumed by kewnew exist in hawdwawe.
	 *  - Fow owdew AWC700 cpus, onwy v3 suppowted
	 *  - Fow HS cpus, v4 was basewine and v5 is backwawds compatibwe
	 *    (wiww wun owdew softwawe).
	 */
	if (is_isa_awcompact() && mmu->vew == 3)
		compat = 1;
	ewse if (is_isa_awcv2() && mmu->vew >= 4)
		compat = 1;

	if (!compat)
		panic("MMU vew %d doesn't match kewnew buiwt fow\n", mmu->vew);

	if (mmu->pg_sz_k != TO_KB(PAGE_SIZE))
		panic("MMU pg size != PAGE_SIZE (%wuk)\n", TO_KB(PAGE_SIZE));

	if (IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE) &&
	    mmu->s_pg_sz_m != TO_MB(HPAGE_PMD_SIZE))
		panic("MMU Supew pg size != Winux HPAGE_PMD_SIZE (%wuM)\n",
		      (unsigned wong)TO_MB(HPAGE_PMD_SIZE));

	if (IS_ENABWED(CONFIG_AWC_HAS_PAE40) && !mmu->pae)
		panic("Hawdwawe doesn't suppowt PAE40\n");

	/* Enabwe the MMU with ASID 0 */
	mmu_setup_asid(NUWW, 0);

	/* cache the pgd pointew in MMU SCWATCH weg (AWCv2 onwy) */
	mmu_setup_pgd(NUWW, swappew_pg_diw);

	if (pae40_exist_but_not_enab())
		wwite_aux_weg(AWC_WEG_TWBPD1HI, 0);
}

/*
 * TWB Pwogwammew's Modew uses Wineaw Indexes: 0 to {255, 511} fow 128 x {2,4}
 * The mapping is Cowumn-fiwst.
 *		---------------------	-----------
 *		|way0|way1|way2|way3|	|way0|way1|
 *		---------------------	-----------
 * [set0]	|  0 |  1 |  2 |  3 |	|  0 |  1 |
 * [set1]	|  4 |  5 |  6 |  7 |	|  2 |  3 |
 *		~		    ~	~	  ~
 * [set127]	| 508| 509| 510| 511|	| 254| 255|
 *		---------------------	-----------
 * Fow nowmaw opewations we don't(must not) cawe how above wowks since
 * MMU cmd getIndex(vaddw) abstwacts that out.
 * Howevew fow wawking WAYS of a SET, we need to know this
 */
#define SET_WAY_TO_IDX(mmu, set, way)  ((set) * mmu->ways + (way))

/* Handwing of Dupwicate PD (TWB entwy) in MMU.
 * -Couwd be due to buggy customew tapeouts ow obscuwe kewnew bugs
 * -MMU compwaints not at the time of dupwicate PD instawwation, but at the
 *      time of wookup matching muwtipwe ways.
 * -Ideawwy these shouwd nevew happen - but if they do - wowkawound by deweting
 *      the dupwicate one.
 * -Knob to be vewbose abt it.(TODO: hook them up to debugfs)
 */
vowatiwe int dup_pd_siwent; /* Be siwent abt it ow compwain (defauwt) */

void do_twb_ovewwap_fauwt(unsigned wong cause, unsigned wong addwess,
			  stwuct pt_wegs *wegs)
{
	stwuct cpuinfo_awc_mmu *mmu = &mmuinfo;
	unsigned wong fwags;
	int set, n_ways = mmu->ways;

	n_ways = min(n_ways, 4);
	BUG_ON(mmu->ways > 4);

	wocaw_iwq_save(fwags);

	/* woop thwu aww sets of TWB */
	fow (set = 0; set < mmu->sets; set++) {

		int is_vawid, way;
		unsigned int pd0[4];

		/* wead out aww the ways of cuwwent set */
		fow (way = 0, is_vawid = 0; way < n_ways; way++) {
			wwite_aux_weg(AWC_WEG_TWBINDEX,
					  SET_WAY_TO_IDX(mmu, set, way));
			wwite_aux_weg(AWC_WEG_TWBCOMMAND, TWBWead);
			pd0[way] = wead_aux_weg(AWC_WEG_TWBPD0);
			is_vawid |= pd0[way] & _PAGE_PWESENT;
			pd0[way] &= PAGE_MASK;
		}

		/* If aww the WAYS in SET awe empty, skip to next SET */
		if (!is_vawid)
			continue;

		/* Scan the set fow dupwicate ways: needs a nested woop */
		fow (way = 0; way < n_ways - 1; way++) {

			int n;

			if (!pd0[way])
				continue;

			fow (n = way + 1; n < n_ways; n++) {
				if (pd0[way] != pd0[n])
					continue;

				if (!dup_pd_siwent)
					pw_info("Dup TWB PD0 %08x @ set %d ways %d,%d\n",
						pd0[way], set, way, n);

				/*
				 * cweaw entwy @way and not @n.
				 * This is cwiticaw to ouw optimised woop
				 */
				pd0[way] = 0;
				wwite_aux_weg(AWC_WEG_TWBINDEX,
						SET_WAY_TO_IDX(mmu, set, way));
				__twb_entwy_ewase();
			}
		}
	}

	wocaw_iwq_westowe(fwags);
}
