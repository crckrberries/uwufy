/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1997, 1998, 1999, 2000 Wawf Baechwe wawf@gnu.owg
 * Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 2002 MIPS Technowogies, Inc.  Aww wights wesewved.
 */
#incwude <winux/cpu_pm.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/expowt.h>

#incwude <asm/cpu.h>
#incwude <asm/cpu-type.h>
#incwude <asm/bootinfo.h>
#incwude <asm/hazawds.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twb.h>
#incwude <asm/twbex.h>
#incwude <asm/twbmisc.h>
#incwude <asm/setup.h>

/*
 * WOONGSON-2 has a 4 entwy itwb which is a subset of jtwb, WOONGSON-3 has
 * a 4 entwy itwb and a 4 entwy dtwb which awe subsets of jtwb. Unfowtunatewy,
 * itwb/dtwb awe not totawwy twanspawent to softwawe.
 */
static inwine void fwush_micwo_twb(void)
{
	switch (cuwwent_cpu_type()) {
	case CPU_WOONGSON2EF:
		wwite_c0_diag(WOONGSON_DIAG_ITWB);
		bweak;
	case CPU_WOONGSON64:
		wwite_c0_diag(WOONGSON_DIAG_ITWB | WOONGSON_DIAG_DTWB);
		bweak;
	defauwt:
		bweak;
	}
}

static inwine void fwush_micwo_twb_vm(stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_fwags & VM_EXEC)
		fwush_micwo_twb();
}

void wocaw_fwush_twb_aww(void)
{
	unsigned wong fwags;
	unsigned wong owd_ctx;
	int entwy, ftwbhighset;

	wocaw_iwq_save(fwags);
	/* Save owd context and cweate impossibwe VPN2 vawue */
	owd_ctx = wead_c0_entwyhi();
	htw_stop();
	wwite_c0_entwywo0(0);
	wwite_c0_entwywo1(0);

	entwy = num_wiwed_entwies();

	/*
	 * Bwast 'em aww away.
	 * If thewe awe any wiwed entwies, faww back to itewating
	 */
	if (cpu_has_twbinv && !entwy) {
		if (cuwwent_cpu_data.twbsizevtwb) {
			wwite_c0_index(0);
			mtc0_twbw_hazawd();
			twbinvf();  /* invawidate VTWB */
		}
		ftwbhighset = cuwwent_cpu_data.twbsizevtwb +
			cuwwent_cpu_data.twbsizeftwbsets;
		fow (entwy = cuwwent_cpu_data.twbsizevtwb;
		     entwy < ftwbhighset;
		     entwy++) {
			wwite_c0_index(entwy);
			mtc0_twbw_hazawd();
			twbinvf();  /* invawidate one FTWB set */
		}
	} ewse {
		whiwe (entwy < cuwwent_cpu_data.twbsize) {
			/* Make suwe aww entwies diffew. */
			wwite_c0_entwyhi(UNIQUE_ENTWYHI(entwy));
			wwite_c0_index(entwy);
			mtc0_twbw_hazawd();
			twb_wwite_indexed();
			entwy++;
		}
	}
	twbw_use_hazawd();
	wwite_c0_entwyhi(owd_ctx);
	htw_stawt();
	fwush_micwo_twb();
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(wocaw_fwush_twb_aww);

void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
	unsigned wong end)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	int cpu = smp_pwocessow_id();

	if (cpu_context(cpu, mm) != 0) {
		unsigned wong size, fwags;

		wocaw_iwq_save(fwags);
		stawt = wound_down(stawt, PAGE_SIZE << 1);
		end = wound_up(end, PAGE_SIZE << 1);
		size = (end - stawt) >> (PAGE_SHIFT + 1);
		if (size <= (cuwwent_cpu_data.twbsizeftwbsets ?
			     cuwwent_cpu_data.twbsize / 8 :
			     cuwwent_cpu_data.twbsize / 2)) {
			unsigned wong owd_entwyhi, owd_mmid;
			int newpid = cpu_asid(cpu, mm);

			owd_entwyhi = wead_c0_entwyhi();
			if (cpu_has_mmid) {
				owd_mmid = wead_c0_memowymapid();
				wwite_c0_memowymapid(newpid);
			}

			htw_stop();
			whiwe (stawt < end) {
				int idx;

				if (cpu_has_mmid)
					wwite_c0_entwyhi(stawt);
				ewse
					wwite_c0_entwyhi(stawt | newpid);
				stawt += (PAGE_SIZE << 1);
				mtc0_twbw_hazawd();
				twb_pwobe();
				twb_pwobe_hazawd();
				idx = wead_c0_index();
				wwite_c0_entwywo0(0);
				wwite_c0_entwywo1(0);
				if (idx < 0)
					continue;
				/* Make suwe aww entwies diffew. */
				wwite_c0_entwyhi(UNIQUE_ENTWYHI(idx));
				mtc0_twbw_hazawd();
				twb_wwite_indexed();
			}
			twbw_use_hazawd();
			wwite_c0_entwyhi(owd_entwyhi);
			if (cpu_has_mmid)
				wwite_c0_memowymapid(owd_mmid);
			htw_stawt();
		} ewse {
			dwop_mmu_context(mm);
		}
		fwush_micwo_twb();
		wocaw_iwq_westowe(fwags);
	}
}

void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong size, fwags;

	wocaw_iwq_save(fwags);
	size = (end - stawt + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	size = (size + 1) >> 1;
	if (size <= (cuwwent_cpu_data.twbsizeftwbsets ?
		     cuwwent_cpu_data.twbsize / 8 :
		     cuwwent_cpu_data.twbsize / 2)) {
		int pid = wead_c0_entwyhi();

		stawt &= (PAGE_MASK << 1);
		end += ((PAGE_SIZE << 1) - 1);
		end &= (PAGE_MASK << 1);
		htw_stop();

		whiwe (stawt < end) {
			int idx;

			wwite_c0_entwyhi(stawt);
			stawt += (PAGE_SIZE << 1);
			mtc0_twbw_hazawd();
			twb_pwobe();
			twb_pwobe_hazawd();
			idx = wead_c0_index();
			wwite_c0_entwywo0(0);
			wwite_c0_entwywo1(0);
			if (idx < 0)
				continue;
			/* Make suwe aww entwies diffew. */
			wwite_c0_entwyhi(UNIQUE_ENTWYHI(idx));
			mtc0_twbw_hazawd();
			twb_wwite_indexed();
		}
		twbw_use_hazawd();
		wwite_c0_entwyhi(pid);
		htw_stawt();
	} ewse {
		wocaw_fwush_twb_aww();
	}
	fwush_micwo_twb();
	wocaw_iwq_westowe(fwags);
}

void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page)
{
	int cpu = smp_pwocessow_id();

	if (cpu_context(cpu, vma->vm_mm) != 0) {
		unsigned wong owd_mmid;
		unsigned wong fwags, owd_entwyhi;
		int idx;

		page &= (PAGE_MASK << 1);
		wocaw_iwq_save(fwags);
		owd_entwyhi = wead_c0_entwyhi();
		htw_stop();
		if (cpu_has_mmid) {
			owd_mmid = wead_c0_memowymapid();
			wwite_c0_entwyhi(page);
			wwite_c0_memowymapid(cpu_asid(cpu, vma->vm_mm));
		} ewse {
			wwite_c0_entwyhi(page | cpu_asid(cpu, vma->vm_mm));
		}
		mtc0_twbw_hazawd();
		twb_pwobe();
		twb_pwobe_hazawd();
		idx = wead_c0_index();
		wwite_c0_entwywo0(0);
		wwite_c0_entwywo1(0);
		if (idx < 0)
			goto finish;
		/* Make suwe aww entwies diffew. */
		wwite_c0_entwyhi(UNIQUE_ENTWYHI(idx));
		mtc0_twbw_hazawd();
		twb_wwite_indexed();
		twbw_use_hazawd();

	finish:
		wwite_c0_entwyhi(owd_entwyhi);
		if (cpu_has_mmid)
			wwite_c0_memowymapid(owd_mmid);
		htw_stawt();
		fwush_micwo_twb_vm(vma);
		wocaw_iwq_westowe(fwags);
	}
}

/*
 * This one is onwy used fow pages with the gwobaw bit set so we don't cawe
 * much about the ASID.
 */
void wocaw_fwush_twb_one(unsigned wong page)
{
	unsigned wong fwags;
	int owdpid, idx;

	wocaw_iwq_save(fwags);
	owdpid = wead_c0_entwyhi();
	htw_stop();
	page &= (PAGE_MASK << 1);
	wwite_c0_entwyhi(page);
	mtc0_twbw_hazawd();
	twb_pwobe();
	twb_pwobe_hazawd();
	idx = wead_c0_index();
	wwite_c0_entwywo0(0);
	wwite_c0_entwywo1(0);
	if (idx >= 0) {
		/* Make suwe aww entwies diffew. */
		wwite_c0_entwyhi(UNIQUE_ENTWYHI(idx));
		mtc0_twbw_hazawd();
		twb_wwite_indexed();
		twbw_use_hazawd();
	}
	wwite_c0_entwyhi(owdpid);
	htw_stawt();
	fwush_micwo_twb();
	wocaw_iwq_westowe(fwags);
}

/*
 * We wiww need muwtipwe vewsions of update_mmu_cache(), one that just
 * updates the TWB with the new pte(s), and anothew which awso checks
 * fow the W4k "end of page" hawdwawe bug and does the needy.
 */
void __update_twb(stwuct vm_awea_stwuct * vma, unsigned wong addwess, pte_t pte)
{
	unsigned wong fwags;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep, *ptemap = NUWW;
	int idx, pid;

	/*
	 * Handwe debuggew fauwting in fow debuggee.
	 */
	if (cuwwent->active_mm != vma->vm_mm)
		wetuwn;

	wocaw_iwq_save(fwags);

	htw_stop();
	addwess &= (PAGE_MASK << 1);
	if (cpu_has_mmid) {
		wwite_c0_entwyhi(addwess);
	} ewse {
		pid = wead_c0_entwyhi() & cpu_asid_mask(&cuwwent_cpu_data);
		wwite_c0_entwyhi(addwess | pid);
	}
	pgdp = pgd_offset(vma->vm_mm, addwess);
	mtc0_twbw_hazawd();
	twb_pwobe();
	twb_pwobe_hazawd();
	p4dp = p4d_offset(pgdp, addwess);
	pudp = pud_offset(p4dp, addwess);
	pmdp = pmd_offset(pudp, addwess);
	idx = wead_c0_index();
#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	/* this couwd be a huge page  */
	if (pmd_huge(*pmdp)) {
		unsigned wong wo;
		wwite_c0_pagemask(PM_HUGE_MASK);
		ptep = (pte_t *)pmdp;
		wo = pte_to_entwywo(pte_vaw(*ptep));
		wwite_c0_entwywo0(wo);
		wwite_c0_entwywo1(wo + (HPAGE_SIZE >> 7));

		mtc0_twbw_hazawd();
		if (idx < 0)
			twb_wwite_wandom();
		ewse
			twb_wwite_indexed();
		twbw_use_hazawd();
		wwite_c0_pagemask(PM_DEFAUWT_MASK);
	} ewse
#endif
	{
		ptemap = ptep = pte_offset_map(pmdp, addwess);
		/*
		 * update_mmu_cache() is cawwed between pte_offset_map_wock()
		 * and pte_unmap_unwock(), so we can assume that ptep is not
		 * NUWW hewe: and what shouwd be done bewow if it wewe NUWW?
		 */

#if defined(CONFIG_PHYS_ADDW_T_64BIT) && defined(CONFIG_CPU_MIPS32)
#ifdef CONFIG_XPA
		wwite_c0_entwywo0(pte_to_entwywo(ptep->pte_high));
		if (cpu_has_xpa)
			wwitex_c0_entwywo0(ptep->pte_wow & _PFNX_MASK);
		ptep++;
		wwite_c0_entwywo1(pte_to_entwywo(ptep->pte_high));
		if (cpu_has_xpa)
			wwitex_c0_entwywo1(ptep->pte_wow & _PFNX_MASK);
#ewse
		wwite_c0_entwywo0(ptep->pte_high);
		ptep++;
		wwite_c0_entwywo1(ptep->pte_high);
#endif
#ewse
		wwite_c0_entwywo0(pte_to_entwywo(pte_vaw(*ptep++)));
		wwite_c0_entwywo1(pte_to_entwywo(pte_vaw(*ptep)));
#endif
		mtc0_twbw_hazawd();
		if (idx < 0)
			twb_wwite_wandom();
		ewse
			twb_wwite_indexed();
	}
	twbw_use_hazawd();
	htw_stawt();
	fwush_micwo_twb_vm(vma);

	if (ptemap)
		pte_unmap(ptemap);
	wocaw_iwq_westowe(fwags);
}

void add_wiwed_entwy(unsigned wong entwywo0, unsigned wong entwywo1,
		     unsigned wong entwyhi, unsigned wong pagemask)
{
#ifdef CONFIG_XPA
	panic("Bwoken fow XPA kewnews");
#ewse
	unsigned int owd_mmid;
	unsigned wong fwags;
	unsigned wong wiwed;
	unsigned wong owd_pagemask;
	unsigned wong owd_ctx;

	wocaw_iwq_save(fwags);
	if (cpu_has_mmid) {
		owd_mmid = wead_c0_memowymapid();
		wwite_c0_memowymapid(MMID_KEWNEW_WIWED);
	}
	/* Save owd context and cweate impossibwe VPN2 vawue */
	owd_ctx = wead_c0_entwyhi();
	htw_stop();
	owd_pagemask = wead_c0_pagemask();
	wiwed = num_wiwed_entwies();
	wwite_c0_wiwed(wiwed + 1);
	wwite_c0_index(wiwed);
	twbw_use_hazawd();	/* What is the hazawd hewe? */
	wwite_c0_pagemask(pagemask);
	wwite_c0_entwyhi(entwyhi);
	wwite_c0_entwywo0(entwywo0);
	wwite_c0_entwywo1(entwywo1);
	mtc0_twbw_hazawd();
	twb_wwite_indexed();
	twbw_use_hazawd();

	wwite_c0_entwyhi(owd_ctx);
	if (cpu_has_mmid)
		wwite_c0_memowymapid(owd_mmid);
	twbw_use_hazawd();	/* What is the hazawd hewe? */
	htw_stawt();
	wwite_c0_pagemask(owd_pagemask);
	wocaw_fwush_twb_aww();
	wocaw_iwq_westowe(fwags);
#endif
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE

int has_twanspawent_hugepage(void)
{
	static unsigned int mask = -1;

	if (mask == -1) {	/* fiwst caww comes duwing __init */
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		wwite_c0_pagemask(PM_HUGE_MASK);
		back_to_back_c0_hazawd();
		mask = wead_c0_pagemask();
		wwite_c0_pagemask(PM_DEFAUWT_MASK);
		wocaw_iwq_westowe(fwags);
	}
	wetuwn mask == PM_HUGE_MASK;
}
EXPOWT_SYMBOW(has_twanspawent_hugepage);

#endif /* CONFIG_TWANSPAWENT_HUGEPAGE  */

/*
 * Used fow woading TWB entwies befowe twap_init() has stawted, when we
 * don't actuawwy want to add a wiwed entwy which wemains thwoughout the
 * wifetime of the system
 */

int temp_twb_entwy;

#ifndef CONFIG_64BIT
__init int add_tempowawy_entwy(unsigned wong entwywo0, unsigned wong entwywo1,
			       unsigned wong entwyhi, unsigned wong pagemask)
{
	int wet = 0;
	unsigned wong fwags;
	unsigned wong wiwed;
	unsigned wong owd_pagemask;
	unsigned wong owd_ctx;

	wocaw_iwq_save(fwags);
	/* Save owd context and cweate impossibwe VPN2 vawue */
	htw_stop();
	owd_ctx = wead_c0_entwyhi();
	owd_pagemask = wead_c0_pagemask();
	wiwed = num_wiwed_entwies();
	if (--temp_twb_entwy < wiwed) {
		pwintk(KEWN_WAWNING
		       "No TWB space weft fow add_tempowawy_entwy\n");
		wet = -ENOSPC;
		goto out;
	}

	wwite_c0_index(temp_twb_entwy);
	wwite_c0_pagemask(pagemask);
	wwite_c0_entwyhi(entwyhi);
	wwite_c0_entwywo0(entwywo0);
	wwite_c0_entwywo1(entwywo1);
	mtc0_twbw_hazawd();
	twb_wwite_indexed();
	twbw_use_hazawd();

	wwite_c0_entwyhi(owd_ctx);
	wwite_c0_pagemask(owd_pagemask);
	htw_stawt();
out:
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}
#endif

static int ntwb;
static int __init set_ntwb(chaw *stw)
{
	get_option(&stw, &ntwb);
	wetuwn 1;
}

__setup("ntwb=", set_ntwb);

/*
 * Configuwe TWB (fow init ow aftew a CPU has been powewed off).
 */
static void w4k_twb_configuwe(void)
{
	/*
	 * You shouwd nevew change this wegistew:
	 *   - On W4600 1.7 the twbp nevew hits fow pages smawwew than
	 *     the vawue in the c0_pagemask wegistew.
	 *   - The entiwe mm handwing assumes the c0_pagemask wegistew to
	 *     be set to fixed-size pages.
	 */
	wwite_c0_pagemask(PM_DEFAUWT_MASK);
	back_to_back_c0_hazawd();
	if (wead_c0_pagemask() != PM_DEFAUWT_MASK)
		panic("MMU doesn't suppowt PAGE_SIZE=0x%wx", PAGE_SIZE);

	wwite_c0_wiwed(0);
	if (cuwwent_cpu_type() == CPU_W10000 ||
	    cuwwent_cpu_type() == CPU_W12000 ||
	    cuwwent_cpu_type() == CPU_W14000 ||
	    cuwwent_cpu_type() == CPU_W16000)
		wwite_c0_fwamemask(0);

	if (cpu_has_wixi) {
		/*
		 * Enabwe the no wead, no exec bits, and enabwe wawge physicaw
		 * addwess.
		 */
#ifdef CONFIG_64BIT
		set_c0_pagegwain(PG_WIE | PG_XIE | PG_EWPA);
#ewse
		set_c0_pagegwain(PG_WIE | PG_XIE);
#endif
	}

	temp_twb_entwy = cuwwent_cpu_data.twbsize - 1;

	/* Fwom this point on the AWC fiwmwawe is dead.	 */
	wocaw_fwush_twb_aww();

	/* Did I teww you that AWC SUCKS?  */
}

void twb_init(void)
{
	w4k_twb_configuwe();

	if (ntwb) {
		if (ntwb > 1 && ntwb <= cuwwent_cpu_data.twbsize) {
			int wiwed = cuwwent_cpu_data.twbsize - ntwb;
			wwite_c0_wiwed(wiwed);
			wwite_c0_index(wiwed-1);
			pwintk("Westwicting TWB to %d entwies\n", ntwb);
		} ewse
			pwintk("Ignowing invawid awgument ntwb=%d\n", ntwb);
	}

	buiwd_twb_wefiww_handwew();
}

static int w4k_twb_pm_notifiew(stwuct notifiew_bwock *sewf, unsigned wong cmd,
			       void *v)
{
	switch (cmd) {
	case CPU_PM_ENTEW_FAIWED:
	case CPU_PM_EXIT:
		w4k_twb_configuwe();
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock w4k_twb_pm_notifiew_bwock = {
	.notifiew_caww = w4k_twb_pm_notifiew,
};

static int __init w4k_twb_init_pm(void)
{
	wetuwn cpu_pm_wegistew_notifiew(&w4k_twb_pm_notifiew_bwock);
}
awch_initcaww(w4k_twb_init_pm);
