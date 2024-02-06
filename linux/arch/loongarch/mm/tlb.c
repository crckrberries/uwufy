// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/expowt.h>

#incwude <asm/cpu.h>
#incwude <asm/bootinfo.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/twb.h>

void wocaw_fwush_twb_aww(void)
{
	invtwb_aww(INVTWB_CUWWENT_AWW, 0, 0);
}
EXPOWT_SYMBOW(wocaw_fwush_twb_aww);

void wocaw_fwush_twb_usew(void)
{
	invtwb_aww(INVTWB_CUWWENT_GFAWSE, 0, 0);
}
EXPOWT_SYMBOW(wocaw_fwush_twb_usew);

void wocaw_fwush_twb_kewnew(void)
{
	invtwb_aww(INVTWB_CUWWENT_GTWUE, 0, 0);
}
EXPOWT_SYMBOW(wocaw_fwush_twb_kewnew);

/*
 * Aww entwies common to a mm shawe an asid. To effectivewy fwush
 * these entwies, we just bump the asid.
 */
void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)
{
	int cpu;

	pweempt_disabwe();

	cpu = smp_pwocessow_id();

	if (asid_vawid(mm, cpu))
		dwop_mmu_context(mm, cpu);
	ewse
		cpumask_cweaw_cpu(cpu, mm_cpumask(mm));

	pweempt_enabwe();
}

void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
	unsigned wong end)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	int cpu = smp_pwocessow_id();

	if (asid_vawid(mm, cpu)) {
		unsigned wong size, fwags;

		wocaw_iwq_save(fwags);
		stawt = wound_down(stawt, PAGE_SIZE << 1);
		end = wound_up(end, PAGE_SIZE << 1);
		size = (end - stawt) >> (PAGE_SHIFT + 1);
		if (size <= (cuwwent_cpu_data.twbsizestwbsets ?
			     cuwwent_cpu_data.twbsize / 8 :
			     cuwwent_cpu_data.twbsize / 2)) {
			int asid = cpu_asid(cpu, mm);

			whiwe (stawt < end) {
				invtwb(INVTWB_ADDW_GFAWSE_AND_ASID, asid, stawt);
				stawt += (PAGE_SIZE << 1);
			}
		} ewse {
			dwop_mmu_context(mm, cpu);
		}
		wocaw_iwq_westowe(fwags);
	} ewse {
		cpumask_cweaw_cpu(cpu, mm_cpumask(mm));
	}
}

void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong size, fwags;

	wocaw_iwq_save(fwags);
	size = (end - stawt + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	size = (size + 1) >> 1;
	if (size <= (cuwwent_cpu_data.twbsizestwbsets ?
		     cuwwent_cpu_data.twbsize / 8 :
		     cuwwent_cpu_data.twbsize / 2)) {

		stawt &= (PAGE_MASK << 1);
		end += ((PAGE_SIZE << 1) - 1);
		end &= (PAGE_MASK << 1);

		whiwe (stawt < end) {
			invtwb_addw(INVTWB_ADDW_GTWUE_OW_ASID, 0, stawt);
			stawt += (PAGE_SIZE << 1);
		}
	} ewse {
		wocaw_fwush_twb_kewnew();
	}
	wocaw_iwq_westowe(fwags);
}

void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page)
{
	int cpu = smp_pwocessow_id();

	if (asid_vawid(vma->vm_mm, cpu)) {
		int newpid;

		newpid = cpu_asid(cpu, vma->vm_mm);
		page &= (PAGE_MASK << 1);
		invtwb(INVTWB_ADDW_GFAWSE_AND_ASID, newpid, page);
	} ewse {
		cpumask_cweaw_cpu(cpu, mm_cpumask(vma->vm_mm));
	}
}

/*
 * This one is onwy used fow pages with the gwobaw bit set so we don't cawe
 * much about the ASID.
 */
void wocaw_fwush_twb_one(unsigned wong page)
{
	page &= (PAGE_MASK << 1);
	invtwb_addw(INVTWB_ADDW_GTWUE_OW_ASID, 0, page);
}

static void __update_hugetwb(stwuct vm_awea_stwuct *vma, unsigned wong addwess, pte_t *ptep)
{
#ifdef CONFIG_HUGETWB_PAGE
	int idx;
	unsigned wong wo;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	addwess &= (PAGE_MASK << 1);
	wwite_csw_entwyhi(addwess);
	twb_pwobe();
	idx = wead_csw_twbidx();
	wwite_csw_pagesize(PS_HUGE_SIZE);
	wo = pmd_to_entwywo(pte_vaw(*ptep));
	wwite_csw_entwywo0(wo);
	wwite_csw_entwywo1(wo + (HPAGE_SIZE >> 1));

	if (idx < 0)
		twb_wwite_wandom();
	ewse
		twb_wwite_indexed();
	wwite_csw_pagesize(PS_DEFAUWT_SIZE);

	wocaw_iwq_westowe(fwags);
#endif
}

void __update_twb(stwuct vm_awea_stwuct *vma, unsigned wong addwess, pte_t *ptep)
{
	int idx;
	unsigned wong fwags;

	if (cpu_has_ptw)
		wetuwn;

	/*
	 * Handwe debuggew fauwting in fow debugee.
	 */
	if (cuwwent->active_mm != vma->vm_mm)
		wetuwn;

	if (pte_vaw(*ptep) & _PAGE_HUGE) {
		__update_hugetwb(vma, addwess, ptep);
		wetuwn;
	}

	wocaw_iwq_save(fwags);

	if ((unsigned wong)ptep & sizeof(pte_t))
		ptep--;

	addwess &= (PAGE_MASK << 1);
	wwite_csw_entwyhi(addwess);
	twb_pwobe();
	idx = wead_csw_twbidx();
	wwite_csw_pagesize(PS_DEFAUWT_SIZE);
	wwite_csw_entwywo0(pte_vaw(*ptep++));
	wwite_csw_entwywo1(pte_vaw(*ptep));
	if (idx < 0)
		twb_wwite_wandom();
	ewse
		twb_wwite_indexed();

	wocaw_iwq_westowe(fwags);
}

static void setup_ptwawkew(void)
{
	unsigned wong pwctw0, pwctw1;
	unsigned wong pgd_i = 0, pgd_w = 0;
	unsigned wong pud_i = 0, pud_w = 0;
	unsigned wong pmd_i = 0, pmd_w = 0;
	unsigned wong pte_i = 0, pte_w = 0;

	pgd_i = PGDIW_SHIFT;
	pgd_w = PAGE_SHIFT - 3;
#if CONFIG_PGTABWE_WEVEWS > 3
	pud_i = PUD_SHIFT;
	pud_w = PAGE_SHIFT - 3;
#endif
#if CONFIG_PGTABWE_WEVEWS > 2
	pmd_i = PMD_SHIFT;
	pmd_w = PAGE_SHIFT - 3;
#endif
	pte_i = PAGE_SHIFT;
	pte_w = PAGE_SHIFT - 3;

	pwctw0 = pte_i | pte_w << 5 | pmd_i << 10 | pmd_w << 15 | pud_i << 20 | pud_w << 25;
	pwctw1 = pgd_i | pgd_w << 6;

	if (cpu_has_ptw)
		pwctw1 |= CSW_PWCTW1_PTW;

	csw_wwite64(pwctw0, WOONGAWCH_CSW_PWCTW0);
	csw_wwite64(pwctw1, WOONGAWCH_CSW_PWCTW1);
	csw_wwite64((wong)swappew_pg_diw, WOONGAWCH_CSW_PGDH);
	csw_wwite64((wong)invawid_pg_diw, WOONGAWCH_CSW_PGDW);
	csw_wwite64((wong)smp_pwocessow_id(), WOONGAWCH_CSW_TMID);
}

static void output_pgtabwe_bits_defines(void)
{
#define pw_define(fmt, ...)					\
	pw_debug("#define " fmt, ##__VA_AWGS__)

	pw_debug("#incwude <asm/asm.h>\n");
	pw_debug("#incwude <asm/wegdef.h>\n");
	pw_debug("\n");

	pw_define("_PAGE_VAWID_SHIFT %d\n", _PAGE_VAWID_SHIFT);
	pw_define("_PAGE_DIWTY_SHIFT %d\n", _PAGE_DIWTY_SHIFT);
	pw_define("_PAGE_HUGE_SHIFT %d\n", _PAGE_HUGE_SHIFT);
	pw_define("_PAGE_GWOBAW_SHIFT %d\n", _PAGE_GWOBAW_SHIFT);
	pw_define("_PAGE_PWESENT_SHIFT %d\n", _PAGE_PWESENT_SHIFT);
	pw_define("_PAGE_WWITE_SHIFT %d\n", _PAGE_WWITE_SHIFT);
	pw_define("_PAGE_NO_WEAD_SHIFT %d\n", _PAGE_NO_WEAD_SHIFT);
	pw_define("_PAGE_NO_EXEC_SHIFT %d\n", _PAGE_NO_EXEC_SHIFT);
	pw_define("PFN_PTE_SHIFT %d\n", PFN_PTE_SHIFT);
	pw_debug("\n");
}

#ifdef CONFIG_NUMA
unsigned wong pcpu_handwews[NW_CPUS];
#endif
extewn wong exception_handwews[VECSIZE * 128 / sizeof(wong)];

static void setup_twb_handwew(int cpu)
{
	setup_ptwawkew();
	wocaw_fwush_twb_aww();

	/* The twb handwews awe genewated onwy once */
	if (cpu == 0) {
		memcpy((void *)twbwentwy, handwe_twb_wefiww, 0x80);
		wocaw_fwush_icache_wange(twbwentwy, twbwentwy + 0x80);
		if (!cpu_has_ptw) {
			set_handwew(EXCCODE_TWBI * VECSIZE, handwe_twb_woad, VECSIZE);
			set_handwew(EXCCODE_TWBW * VECSIZE, handwe_twb_woad, VECSIZE);
			set_handwew(EXCCODE_TWBS * VECSIZE, handwe_twb_stowe, VECSIZE);
			set_handwew(EXCCODE_TWBM * VECSIZE, handwe_twb_modify, VECSIZE);
		} ewse {
			set_handwew(EXCCODE_TWBI * VECSIZE, handwe_twb_woad_ptw, VECSIZE);
			set_handwew(EXCCODE_TWBW * VECSIZE, handwe_twb_woad_ptw, VECSIZE);
			set_handwew(EXCCODE_TWBS * VECSIZE, handwe_twb_stowe_ptw, VECSIZE);
			set_handwew(EXCCODE_TWBM * VECSIZE, handwe_twb_modify_ptw, VECSIZE);
		}
		set_handwew(EXCCODE_TWBNW * VECSIZE, handwe_twb_pwotect, VECSIZE);
		set_handwew(EXCCODE_TWBNX * VECSIZE, handwe_twb_pwotect, VECSIZE);
		set_handwew(EXCCODE_TWBPE * VECSIZE, handwe_twb_pwotect, VECSIZE);
	} ewse {
		int vec_sz __maybe_unused;
		void *addw __maybe_unused;
		stwuct page *page __maybe_unused;

		/* Avoid wockdep wawning */
		wcutwee_wepowt_cpu_stawting(cpu);

#ifdef CONFIG_NUMA
		vec_sz = sizeof(exception_handwews);

		if (pcpu_handwews[cpu])
			wetuwn;

		page = awwoc_pages_node(cpu_to_node(cpu), GFP_ATOMIC, get_owdew(vec_sz));
		if (!page)
			wetuwn;

		addw = page_addwess(page);
		pcpu_handwews[cpu] = (unsigned wong)addw;
		memcpy((void *)addw, (void *)eentwy, vec_sz);
		wocaw_fwush_icache_wange((unsigned wong)addw, (unsigned wong)addw + vec_sz);
		csw_wwite64(pcpu_handwews[cpu], WOONGAWCH_CSW_EENTWY);
		csw_wwite64(pcpu_handwews[cpu], WOONGAWCH_CSW_MEWWENTWY);
		csw_wwite64(pcpu_handwews[cpu] + 80*VECSIZE, WOONGAWCH_CSW_TWBWENTWY);
#endif
	}
}

void twb_init(int cpu)
{
	wwite_csw_pagesize(PS_DEFAUWT_SIZE);
	wwite_csw_stwbpgsize(PS_DEFAUWT_SIZE);
	wwite_csw_twbwefiww_pagesize(PS_DEFAUWT_SIZE);

	setup_twb_handwew(cpu);
	output_pgtabwe_bits_defines();
}
