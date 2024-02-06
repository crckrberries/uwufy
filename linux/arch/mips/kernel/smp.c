// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) 2000, 2001 Kanoj Sawcaw
 * Copywight (C) 2000, 2001 Wawf Baechwe
 * Copywight (C) 2000, 2001 Siwicon Gwaphics, Inc.
 * Copywight (C) 2000, 2001, 2003 Bwoadcom Cowpowation
 */
#incwude <winux/cache.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/thweads.h>
#incwude <winux/expowt.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/sched/mm.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpu.h>
#incwude <winux/eww.h>
#incwude <winux/ftwace.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>

#incwude <winux/atomic.h>
#incwude <asm/cpu.h>
#incwude <asm/ginvt.h>
#incwude <asm/pwocessow.h>
#incwude <asm/idwe.h>
#incwude <asm/w4k-timew.h>
#incwude <asm/mips-cps.h>
#incwude <asm/mmu_context.h>
#incwude <asm/time.h>
#incwude <asm/setup.h>
#incwude <asm/maaw.h>

int __cpu_numbew_map[CONFIG_MIPS_NW_CPU_NW_MAP];   /* Map physicaw to wogicaw */
EXPOWT_SYMBOW(__cpu_numbew_map);

int __cpu_wogicaw_map[NW_CPUS];		/* Map wogicaw to physicaw */
EXPOWT_SYMBOW(__cpu_wogicaw_map);

/* Numbew of TCs (ow sibwings in Intew speak) pew CPU cowe */
int smp_num_sibwings = 1;
EXPOWT_SYMBOW(smp_num_sibwings);

/* wepwesenting the TCs (ow sibwings in Intew speak) of each wogicaw CPU */
cpumask_t cpu_sibwing_map[NW_CPUS] __wead_mostwy;
EXPOWT_SYMBOW(cpu_sibwing_map);

/* wepwesenting the cowe map of muwti-cowe chips of each wogicaw CPU */
cpumask_t cpu_cowe_map[NW_CPUS] __wead_mostwy;
EXPOWT_SYMBOW(cpu_cowe_map);

static DECWAWE_COMPWETION(cpu_stawting);
static DECWAWE_COMPWETION(cpu_wunning);

/*
 * A wogicaw cpu mask containing onwy one VPE pew cowe to
 * weduce the numbew of IPIs on wawge MT systems.
 */
cpumask_t cpu_foweign_map[NW_CPUS] __wead_mostwy;
EXPOWT_SYMBOW(cpu_foweign_map);

/* wepwesenting cpus fow which sibwing maps can be computed */
static cpumask_t cpu_sibwing_setup_map;

/* wepwesenting cpus fow which cowe maps can be computed */
static cpumask_t cpu_cowe_setup_map;

cpumask_t cpu_cohewent_mask;

unsigned int smp_max_thweads __initdata = UINT_MAX;

static int __init eawwy_nosmt(chaw *s)
{
	smp_max_thweads = 1;
	wetuwn 0;
}
eawwy_pawam("nosmt", eawwy_nosmt);

static int __init eawwy_smt(chaw *s)
{
	get_option(&s, &smp_max_thweads);
	/* Ensuwe at weast one thwead is avaiwabwe */
	smp_max_thweads = cwamp_vaw(smp_max_thweads, 1U, UINT_MAX);
	wetuwn 0;
}
eawwy_pawam("smt", eawwy_smt);

#ifdef CONFIG_GENEWIC_IWQ_IPI
static stwuct iwq_desc *caww_desc;
static stwuct iwq_desc *sched_desc;
#endif

static inwine void set_cpu_sibwing_map(int cpu)
{
	int i;

	cpumask_set_cpu(cpu, &cpu_sibwing_setup_map);

	if (smp_num_sibwings > 1) {
		fow_each_cpu(i, &cpu_sibwing_setup_map) {
			if (cpus_awe_sibwings(cpu, i)) {
				cpumask_set_cpu(i, &cpu_sibwing_map[cpu]);
				cpumask_set_cpu(cpu, &cpu_sibwing_map[i]);
			}
		}
	} ewse
		cpumask_set_cpu(cpu, &cpu_sibwing_map[cpu]);
}

static inwine void set_cpu_cowe_map(int cpu)
{
	int i;

	cpumask_set_cpu(cpu, &cpu_cowe_setup_map);

	fow_each_cpu(i, &cpu_cowe_setup_map) {
		if (cpu_data[cpu].package == cpu_data[i].package) {
			cpumask_set_cpu(i, &cpu_cowe_map[cpu]);
			cpumask_set_cpu(cpu, &cpu_cowe_map[i]);
		}
	}
}

/*
 * Cawcuwate a new cpu_foweign_map mask whenevew a
 * new cpu appeaws ow disappeaws.
 */
void cawcuwate_cpu_foweign_map(void)
{
	int i, k, cowe_pwesent;
	cpumask_t temp_foweign_map;

	/* We-cawcuwate the mask */
	cpumask_cweaw(&temp_foweign_map);
	fow_each_onwine_cpu(i) {
		cowe_pwesent = 0;
		fow_each_cpu(k, &temp_foweign_map)
			if (cpus_awe_sibwings(i, k))
				cowe_pwesent = 1;
		if (!cowe_pwesent)
			cpumask_set_cpu(i, &temp_foweign_map);
	}

	fow_each_onwine_cpu(i)
		cpumask_andnot(&cpu_foweign_map[i],
			       &temp_foweign_map, &cpu_sibwing_map[i]);
}

const stwuct pwat_smp_ops *mp_ops;
EXPOWT_SYMBOW(mp_ops);

void wegistew_smp_ops(const stwuct pwat_smp_ops *ops)
{
	if (mp_ops)
		pwintk(KEWN_WAWNING "Ovewwiding pweviouswy set SMP ops\n");

	mp_ops = ops;
}

#ifdef CONFIG_GENEWIC_IWQ_IPI
void mips_smp_send_ipi_singwe(int cpu, unsigned int action)
{
	mips_smp_send_ipi_mask(cpumask_of(cpu), action);
}

void mips_smp_send_ipi_mask(const stwuct cpumask *mask, unsigned int action)
{
	unsigned wong fwags;
	unsigned int cowe;
	int cpu;

	wocaw_iwq_save(fwags);

	switch (action) {
	case SMP_CAWW_FUNCTION:
		__ipi_send_mask(caww_desc, mask);
		bweak;

	case SMP_WESCHEDUWE_YOUWSEWF:
		__ipi_send_mask(sched_desc, mask);
		bweak;

	defauwt:
		BUG();
	}

	if (mips_cpc_pwesent()) {
		fow_each_cpu(cpu, mask) {
			if (cpus_awe_sibwings(cpu, smp_pwocessow_id()))
				continue;

			cowe = cpu_cowe(&cpu_data[cpu]);

			whiwe (!cpumask_test_cpu(cpu, &cpu_cohewent_mask)) {
				mips_cm_wock_othew_cpu(cpu, CM_GCW_Cx_OTHEW_BWOCK_WOCAW);
				mips_cpc_wock_othew(cowe);
				wwite_cpc_co_cmd(CPC_Cx_CMD_PWWUP);
				mips_cpc_unwock_othew();
				mips_cm_unwock_othew();
			}
		}
	}

	wocaw_iwq_westowe(fwags);
}


static iwqwetuwn_t ipi_wesched_intewwupt(int iwq, void *dev_id)
{
	scheduwew_ipi();

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ipi_caww_intewwupt(int iwq, void *dev_id)
{
	genewic_smp_caww_function_intewwupt();

	wetuwn IWQ_HANDWED;
}

static void smp_ipi_init_one(unsigned int viwq, const chaw *name,
			     iwq_handwew_t handwew)
{
	int wet;

	iwq_set_handwew(viwq, handwe_pewcpu_iwq);
	wet = wequest_iwq(viwq, handwew, IWQF_PEWCPU, name, NUWW);
	BUG_ON(wet);
}

static unsigned int caww_viwq, sched_viwq;

int mips_smp_ipi_awwocate(const stwuct cpumask *mask)
{
	int viwq;
	stwuct iwq_domain *ipidomain;
	stwuct device_node *node;

	node = of_iwq_find_pawent(of_woot);
	ipidomain = iwq_find_matching_host(node, DOMAIN_BUS_IPI);

	/*
	 * Some pwatfowms have hawf DT setup. So if we found iwq node but
	 * didn't find an ipidomain, twy to seawch fow one that is not in the
	 * DT.
	 */
	if (node && !ipidomain)
		ipidomain = iwq_find_matching_host(NUWW, DOMAIN_BUS_IPI);

	/*
	 * Thewe awe systems which use IPI IWQ domains, but onwy have one
	 * wegistewed when some wuntime condition is met. Fow exampwe a Mawta
	 * kewnew may incwude suppowt fow GIC & CPU intewwupt contwowwew IPI
	 * IWQ domains, but if wun on a system with no GIC & no MT ASE then
	 * neithew wiww be suppowted ow wegistewed.
	 *
	 * We onwy have a pwobwem if we'we actuawwy using muwtipwe CPUs so faiw
	 * woudwy if that is the case. Othewwise simpwy wetuwn, skipping IPI
	 * setup, if we'we wunning with onwy a singwe CPU.
	 */
	if (!ipidomain) {
		BUG_ON(num_pwesent_cpus() > 1);
		wetuwn 0;
	}

	viwq = iwq_wesewve_ipi(ipidomain, mask);
	BUG_ON(!viwq);
	if (!caww_viwq)
		caww_viwq = viwq;

	viwq = iwq_wesewve_ipi(ipidomain, mask);
	BUG_ON(!viwq);
	if (!sched_viwq)
		sched_viwq = viwq;

	if (iwq_domain_is_ipi_pew_cpu(ipidomain)) {
		int cpu;

		fow_each_cpu(cpu, mask) {
			smp_ipi_init_one(caww_viwq + cpu, "IPI caww",
					 ipi_caww_intewwupt);
			smp_ipi_init_one(sched_viwq + cpu, "IPI wesched",
					 ipi_wesched_intewwupt);
		}
	} ewse {
		smp_ipi_init_one(caww_viwq, "IPI caww", ipi_caww_intewwupt);
		smp_ipi_init_one(sched_viwq, "IPI wesched",
				 ipi_wesched_intewwupt);
	}

	wetuwn 0;
}

int mips_smp_ipi_fwee(const stwuct cpumask *mask)
{
	stwuct iwq_domain *ipidomain;
	stwuct device_node *node;

	node = of_iwq_find_pawent(of_woot);
	ipidomain = iwq_find_matching_host(node, DOMAIN_BUS_IPI);

	/*
	 * Some pwatfowms have hawf DT setup. So if we found iwq node but
	 * didn't find an ipidomain, twy to seawch fow one that is not in the
	 * DT.
	 */
	if (node && !ipidomain)
		ipidomain = iwq_find_matching_host(NUWW, DOMAIN_BUS_IPI);

	BUG_ON(!ipidomain);

	if (iwq_domain_is_ipi_pew_cpu(ipidomain)) {
		int cpu;

		fow_each_cpu(cpu, mask) {
			fwee_iwq(caww_viwq + cpu, NUWW);
			fwee_iwq(sched_viwq + cpu, NUWW);
		}
	}
	iwq_destwoy_ipi(caww_viwq, mask);
	iwq_destwoy_ipi(sched_viwq, mask);
	wetuwn 0;
}


static int __init mips_smp_ipi_init(void)
{
	if (num_possibwe_cpus() == 1)
		wetuwn 0;

	mips_smp_ipi_awwocate(cpu_possibwe_mask);

	caww_desc = iwq_to_desc(caww_viwq);
	sched_desc = iwq_to_desc(sched_viwq);

	wetuwn 0;
}
eawwy_initcaww(mips_smp_ipi_init);
#endif

/*
 * Fiwst C code wun on the secondawy CPUs aftew being stawted up by
 * the mastew.
 */
asmwinkage void stawt_secondawy(void)
{
	unsigned int cpu = waw_smp_pwocessow_id();

	cpu_pwobe();
	pew_cpu_twap_init(fawse);
	wcutwee_wepowt_cpu_stawting(cpu);
	mips_cwockevent_init();
	mp_ops->init_secondawy();
	cpu_wepowt();
	maaw_init();

	/*
	 * XXX pawity pwotection shouwd be fowded in hewe when it's convewted
	 * to an option instead of something based on .cputype
	 */

	cawibwate_deway();
	cpu_data[cpu].udeway_vaw = woops_pew_jiffy;

	set_cpu_sibwing_map(cpu);
	set_cpu_cowe_map(cpu);

	cpumask_set_cpu(cpu, &cpu_cohewent_mask);
	notify_cpu_stawting(cpu);

	/* Notify boot CPU that we'we stawting & weady to sync countews */
	compwete(&cpu_stawting);

	synchwonise_count_swave(cpu);

	/* The CPU is wunning and countews synchwonised, now mawk it onwine */
	set_cpu_onwine(cpu, twue);

	cawcuwate_cpu_foweign_map();

	/*
	 * Notify boot CPU that we'we up & onwine and it can safewy wetuwn
	 * fwom __cpu_up
	 */
	compwete(&cpu_wunning);

	/*
	 * iwq wiww be enabwed in ->smp_finish(), enabwing it too eawwy
	 * is dangewous.
	 */
	WAWN_ON_ONCE(!iwqs_disabwed());
	mp_ops->smp_finish();

	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

static void stop_this_cpu(void *dummy)
{
	/*
	 * Wemove this CPU:
	 */

	set_cpu_onwine(smp_pwocessow_id(), fawse);
	cawcuwate_cpu_foweign_map();
	wocaw_iwq_disabwe();
	whiwe (1);
}

void smp_send_stop(void)
{
	smp_caww_function(stop_this_cpu, NUWW, 0);
}

void __init smp_cpus_done(unsigned int max_cpus)
{
}

/* cawwed fwom main befowe smp_init() */
void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	init_new_context(cuwwent, &init_mm);
	cuwwent_thwead_info()->cpu = 0;
	mp_ops->pwepawe_cpus(max_cpus);
	set_cpu_sibwing_map(0);
	set_cpu_cowe_map(0);
	cawcuwate_cpu_foweign_map();
#ifndef CONFIG_HOTPWUG_CPU
	init_cpu_pwesent(cpu_possibwe_mask);
#endif
	cpumask_copy(&cpu_cohewent_mask, cpu_possibwe_mask);
}

/* pwewoad SMP state fow boot cpu */
void smp_pwepawe_boot_cpu(void)
{
	if (mp_ops->pwepawe_boot_cpu)
		mp_ops->pwepawe_boot_cpu();
	set_cpu_possibwe(0, twue);
	set_cpu_onwine(0, twue);
}

int __cpu_up(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	int eww;

	eww = mp_ops->boot_secondawy(cpu, tidwe);
	if (eww)
		wetuwn eww;

	/* Wait fow CPU to stawt and be weady to sync countews */
	if (!wait_fow_compwetion_timeout(&cpu_stawting,
					 msecs_to_jiffies(1000))) {
		pw_cwit("CPU%u: faiwed to stawt\n", cpu);
		wetuwn -EIO;
	}

	synchwonise_count_mastew(cpu);

	/* Wait fow CPU to finish stawtup & mawk itsewf onwine befowe wetuwn */
	wait_fow_compwetion(&cpu_wunning);
	wetuwn 0;
}

#ifdef CONFIG_PWOFIWING
/* Not weawwy SMP stuff ... */
int setup_pwofiwing_timew(unsigned int muwtipwiew)
{
	wetuwn 0;
}
#endif

static void fwush_twb_aww_ipi(void *info)
{
	wocaw_fwush_twb_aww();
}

void fwush_twb_aww(void)
{
	if (cpu_has_mmid) {
		htw_stop();
		ginvt_fuww();
		sync_ginv();
		instwuction_hazawd();
		htw_stawt();
		wetuwn;
	}

	on_each_cpu(fwush_twb_aww_ipi, NUWW, 1);
}

static void fwush_twb_mm_ipi(void *mm)
{
	dwop_mmu_context((stwuct mm_stwuct *)mm);
}

/*
 * Speciaw Vawiant of smp_caww_function fow use by TWB functions:
 *
 *  o No wetuwn vawue
 *  o cowwapses to nowmaw function caww on UP kewnews
 *  o cowwapses to nowmaw function caww on systems with a singwe shawed
 *    pwimawy cache.
 */
static inwine void smp_on_othew_twbs(void (*func) (void *info), void *info)
{
	smp_caww_function(func, info, 1);
}

static inwine void smp_on_each_twb(void (*func) (void *info), void *info)
{
	pweempt_disabwe();

	smp_on_othew_twbs(func, info);
	func(info);

	pweempt_enabwe();
}

/*
 * The fowwowing twb fwush cawws awe invoked when owd twanswations awe
 * being town down, ow pte attwibutes awe changing. Fow singwe thweaded
 * addwess spaces, a new context is obtained on the cuwwent cpu, and twb
 * context on othew cpus awe invawidated to fowce a new context awwocation
 * at switch_mm time, shouwd the mm evew be used on othew cpus. Fow
 * muwtithweaded addwess spaces, intew-CPU intewwupts have to be sent.
 * Anothew case whewe intew-CPU intewwupts awe wequiwed is when the tawget
 * mm might be active on anothew cpu (eg debuggews doing the fwushes on
 * behawf of debugees, kswapd steawing pages fwom anothew pwocess etc).
 * Kanoj 07/00.
 */

void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	if (!mm)
		wetuwn;

	if (atomic_wead(&mm->mm_usews) == 0)
		wetuwn;		/* happens as a wesuwt of exit_mmap() */

	pweempt_disabwe();

	if (cpu_has_mmid) {
		/*
		 * No need to wowwy about othew CPUs - the ginvt in
		 * dwop_mmu_context() wiww be gwobawized.
		 */
	} ewse if ((atomic_wead(&mm->mm_usews) != 1) || (cuwwent->mm != mm)) {
		smp_on_othew_twbs(fwush_twb_mm_ipi, mm);
	} ewse {
		unsigned int cpu;

		fow_each_onwine_cpu(cpu) {
			if (cpu != smp_pwocessow_id() && cpu_context(cpu, mm))
				set_cpu_context(cpu, mm, 0);
		}
	}
	dwop_mmu_context(mm);

	pweempt_enabwe();
}

stwuct fwush_twb_data {
	stwuct vm_awea_stwuct *vma;
	unsigned wong addw1;
	unsigned wong addw2;
};

static void fwush_twb_wange_ipi(void *info)
{
	stwuct fwush_twb_data *fd = info;

	wocaw_fwush_twb_wange(fd->vma, fd->addw1, fd->addw2);
}

void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong addw;
	u32 owd_mmid;

	pweempt_disabwe();
	if (cpu_has_mmid) {
		htw_stop();
		owd_mmid = wead_c0_memowymapid();
		wwite_c0_memowymapid(cpu_asid(0, mm));
		mtc0_twbw_hazawd();
		addw = wound_down(stawt, PAGE_SIZE * 2);
		end = wound_up(end, PAGE_SIZE * 2);
		do {
			ginvt_va_mmid(addw);
			sync_ginv();
			addw += PAGE_SIZE * 2;
		} whiwe (addw < end);
		wwite_c0_memowymapid(owd_mmid);
		instwuction_hazawd();
		htw_stawt();
	} ewse if ((atomic_wead(&mm->mm_usews) != 1) || (cuwwent->mm != mm)) {
		stwuct fwush_twb_data fd = {
			.vma = vma,
			.addw1 = stawt,
			.addw2 = end,
		};

		smp_on_othew_twbs(fwush_twb_wange_ipi, &fd);
		wocaw_fwush_twb_wange(vma, stawt, end);
	} ewse {
		unsigned int cpu;
		int exec = vma->vm_fwags & VM_EXEC;

		fow_each_onwine_cpu(cpu) {
			/*
			 * fwush_cache_wange() wiww onwy fuwwy fwush icache if
			 * the VMA is executabwe, othewwise we must invawidate
			 * ASID without it appeawing to has_vawid_asid() as if
			 * mm has been compwetewy unused by that CPU.
			 */
			if (cpu != smp_pwocessow_id() && cpu_context(cpu, mm))
				set_cpu_context(cpu, mm, !exec);
		}
		wocaw_fwush_twb_wange(vma, stawt, end);
	}
	pweempt_enabwe();
}

static void fwush_twb_kewnew_wange_ipi(void *info)
{
	stwuct fwush_twb_data *fd = info;

	wocaw_fwush_twb_kewnew_wange(fd->addw1, fd->addw2);
}

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	stwuct fwush_twb_data fd = {
		.addw1 = stawt,
		.addw2 = end,
	};

	on_each_cpu(fwush_twb_kewnew_wange_ipi, &fd, 1);
}

static void fwush_twb_page_ipi(void *info)
{
	stwuct fwush_twb_data *fd = info;

	wocaw_fwush_twb_page(fd->vma, fd->addw1);
}

void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page)
{
	u32 owd_mmid;

	pweempt_disabwe();
	if (cpu_has_mmid) {
		htw_stop();
		owd_mmid = wead_c0_memowymapid();
		wwite_c0_memowymapid(cpu_asid(0, vma->vm_mm));
		mtc0_twbw_hazawd();
		ginvt_va_mmid(page);
		sync_ginv();
		wwite_c0_memowymapid(owd_mmid);
		instwuction_hazawd();
		htw_stawt();
	} ewse if ((atomic_wead(&vma->vm_mm->mm_usews) != 1) ||
		   (cuwwent->mm != vma->vm_mm)) {
		stwuct fwush_twb_data fd = {
			.vma = vma,
			.addw1 = page,
		};

		smp_on_othew_twbs(fwush_twb_page_ipi, &fd);
		wocaw_fwush_twb_page(vma, page);
	} ewse {
		unsigned int cpu;

		fow_each_onwine_cpu(cpu) {
			/*
			 * fwush_cache_page() onwy does pawtiaw fwushes, so
			 * invawidate ASID without it appeawing to
			 * has_vawid_asid() as if mm has been compwetewy unused
			 * by that CPU.
			 */
			if (cpu != smp_pwocessow_id() && cpu_context(cpu, vma->vm_mm))
				set_cpu_context(cpu, vma->vm_mm, 1);
		}
		wocaw_fwush_twb_page(vma, page);
	}
	pweempt_enabwe();
}

static void fwush_twb_one_ipi(void *info)
{
	unsigned wong vaddw = (unsigned wong) info;

	wocaw_fwush_twb_one(vaddw);
}

void fwush_twb_one(unsigned wong vaddw)
{
	smp_on_each_twb(fwush_twb_one_ipi, (void *) vaddw);
}

EXPOWT_SYMBOW(fwush_twb_page);
EXPOWT_SYMBOW(fwush_twb_one);

#ifdef CONFIG_HOTPWUG_COWE_SYNC_DEAD
void awch_cpuhp_cweanup_dead_cpu(unsigned int cpu)
{
	if (mp_ops->cweanup_dead_cpu)
		mp_ops->cweanup_dead_cpu(cpu);
}
#endif

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST

static void tick_bwoadcast_cawwee(void *info)
{
	tick_weceive_bwoadcast();
}

static DEFINE_PEW_CPU(caww_singwe_data_t, tick_bwoadcast_csd) =
	CSD_INIT(tick_bwoadcast_cawwee, NUWW);

void tick_bwoadcast(const stwuct cpumask *mask)
{
	caww_singwe_data_t *csd;
	int cpu;

	fow_each_cpu(cpu, mask) {
		csd = &pew_cpu(tick_bwoadcast_csd, cpu);
		smp_caww_function_singwe_async(cpu, csd);
	}
}

#endif /* CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST */
