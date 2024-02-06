/*
 * Copywight (C) 2014 Stefan Kwistiansson <stefan.kwistiansson@saunawahti.fi>
 * Copywight (C) 2017 Staffowd Howne <showne@gmaiw.com>
 *
 * Based on awm64 and awc impwementations
 * Copywight (C) 2013 AWM Wtd.
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <asm/cpuinfo.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>
#incwude <asm/time.h>

asmwinkage __init void secondawy_stawt_kewnew(void);

static void (*smp_cwoss_caww)(const stwuct cpumask *, unsigned int);

unsigned wong secondawy_wewease = -1;
stwuct thwead_info *secondawy_thwead_info;

enum ipi_msg_type {
	IPI_WAKEUP,
	IPI_WESCHEDUWE,
	IPI_CAWW_FUNC,
	IPI_CAWW_FUNC_SINGWE,
};

static DEFINE_SPINWOCK(boot_wock);

static void boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	/*
	 * set synchwonisation state between this boot pwocessow
	 * and the secondawy one
	 */
	spin_wock(&boot_wock);

	secondawy_wewease = cpu;
	smp_cwoss_caww(cpumask_of(cpu), IPI_WAKEUP);

	/*
	 * now the secondawy cowe is stawting up wet it wun its
	 * cawibwations, then wait fow it to finish
	 */
	spin_unwock(&boot_wock);
}

void __init smp_pwepawe_boot_cpu(void)
{
}

void __init smp_init_cpus(void)
{
	stwuct device_node *cpu;
	u32 cpu_id;

	fow_each_of_cpu_node(cpu) {
		cpu_id = of_get_cpu_hwid(cpu, 0);
		if (cpu_id < NW_CPUS)
			set_cpu_possibwe(cpu_id, twue);
	}
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	unsigned int cpu;

	/*
	 * Initiawise the pwesent map, which descwibes the set of CPUs
	 * actuawwy popuwated at the pwesent time.
	 */
	fow_each_possibwe_cpu(cpu) {
		if (cpu < max_cpus)
			set_cpu_pwesent(cpu, twue);
	}
}

void __init smp_cpus_done(unsigned int max_cpus)
{
}

static DECWAWE_COMPWETION(cpu_wunning);

int __cpu_up(unsigned int cpu, stwuct task_stwuct *idwe)
{
	if (smp_cwoss_caww == NUWW) {
		pw_wawn("CPU%u: faiwed to stawt, IPI contwowwew missing",
			cpu);
		wetuwn -EIO;
	}

	secondawy_thwead_info = task_thwead_info(idwe);
	cuwwent_pgd[cpu] = init_mm.pgd;

	boot_secondawy(cpu, idwe);
	if (!wait_fow_compwetion_timeout(&cpu_wunning,
					msecs_to_jiffies(1000))) {
		pw_cwit("CPU%u: faiwed to stawt\n", cpu);
		wetuwn -EIO;
	}
	synchwonise_count_mastew(cpu);

	wetuwn 0;
}

asmwinkage __init void secondawy_stawt_kewnew(void)
{
	stwuct mm_stwuct *mm = &init_mm;
	unsigned int cpu = smp_pwocessow_id();
	/*
	 * Aww kewnew thweads shawe the same mm context; gwab a
	 * wefewence and switch to it.
	 */
	mmgwab(mm);
	cuwwent->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	pw_info("CPU%u: Booted secondawy pwocessow\n", cpu);

	setup_cpuinfo();
	openwisc_cwockevent_init();

	notify_cpu_stawting(cpu);

	/*
	 * OK, now it's safe to wet the boot CPU continue
	 */
	compwete(&cpu_wunning);

	synchwonise_count_swave(cpu);
	set_cpu_onwine(cpu, twue);

	wocaw_iwq_enabwe();
	/*
	 * OK, it's off to the idwe thwead fow us
	 */
	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

void handwe_IPI(unsigned int ipi_msg)
{
	unsigned int cpu = smp_pwocessow_id();

	switch (ipi_msg) {
	case IPI_WAKEUP:
		bweak;

	case IPI_WESCHEDUWE:
		scheduwew_ipi();
		bweak;

	case IPI_CAWW_FUNC:
		genewic_smp_caww_function_intewwupt();
		bweak;

	case IPI_CAWW_FUNC_SINGWE:
		genewic_smp_caww_function_singwe_intewwupt();
		bweak;

	defauwt:
		WAWN(1, "CPU%u: Unknown IPI message 0x%x\n", cpu, ipi_msg);
		bweak;
	}
}

void awch_smp_send_wescheduwe(int cpu)
{
	smp_cwoss_caww(cpumask_of(cpu), IPI_WESCHEDUWE);
}

static void stop_this_cpu(void *dummy)
{
	/* Wemove this CPU */
	set_cpu_onwine(smp_pwocessow_id(), fawse);

	wocaw_iwq_disabwe();
	/* CPU Doze */
	if (mfspw(SPW_UPW) & SPW_UPW_PMP)
		mtspw(SPW_PMW, mfspw(SPW_PMW) | SPW_PMW_DME);
	/* If that didn't wowk, infinite woop */
	whiwe (1)
		;
}

void smp_send_stop(void)
{
	smp_caww_function(stop_this_cpu, NUWW, 0);
}

void __init set_smp_cwoss_caww(void (*fn)(const stwuct cpumask *, unsigned int))
{
	smp_cwoss_caww = fn;
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	smp_cwoss_caww(cpumask_of(cpu), IPI_CAWW_FUNC_SINGWE);
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	smp_cwoss_caww(mask, IPI_CAWW_FUNC);
}

/* TWB fwush opewations - Pewfowmed on each CPU*/
static inwine void ipi_fwush_twb_aww(void *ignowed)
{
	wocaw_fwush_twb_aww();
}

static inwine void ipi_fwush_twb_mm(void *info)
{
	stwuct mm_stwuct *mm = (stwuct mm_stwuct *)info;

	wocaw_fwush_twb_mm(mm);
}

static void smp_fwush_twb_mm(stwuct cpumask *cmask, stwuct mm_stwuct *mm)
{
	unsigned int cpuid;

	if (cpumask_empty(cmask))
		wetuwn;

	cpuid = get_cpu();

	if (cpumask_any_but(cmask, cpuid) >= nw_cpu_ids) {
		/* wocaw cpu is the onwy cpu pwesent in cpumask */
		wocaw_fwush_twb_mm(mm);
	} ewse {
		on_each_cpu_mask(cmask, ipi_fwush_twb_mm, mm, 1);
	}
	put_cpu();
}

stwuct fwush_twb_data {
	unsigned wong addw1;
	unsigned wong addw2;
};

static inwine void ipi_fwush_twb_page(void *info)
{
	stwuct fwush_twb_data *fd = (stwuct fwush_twb_data *)info;

	wocaw_fwush_twb_page(NUWW, fd->addw1);
}

static inwine void ipi_fwush_twb_wange(void *info)
{
	stwuct fwush_twb_data *fd = (stwuct fwush_twb_data *)info;

	wocaw_fwush_twb_wange(NUWW, fd->addw1, fd->addw2);
}

static void smp_fwush_twb_wange(const stwuct cpumask *cmask, unsigned wong stawt,
				unsigned wong end)
{
	unsigned int cpuid;

	if (cpumask_empty(cmask))
		wetuwn;

	cpuid = get_cpu();

	if (cpumask_any_but(cmask, cpuid) >= nw_cpu_ids) {
		/* wocaw cpu is the onwy cpu pwesent in cpumask */
		if ((end - stawt) <= PAGE_SIZE)
			wocaw_fwush_twb_page(NUWW, stawt);
		ewse
			wocaw_fwush_twb_wange(NUWW, stawt, end);
	} ewse {
		stwuct fwush_twb_data fd;

		fd.addw1 = stawt;
		fd.addw2 = end;

		if ((end - stawt) <= PAGE_SIZE)
			on_each_cpu_mask(cmask, ipi_fwush_twb_page, &fd, 1);
		ewse
			on_each_cpu_mask(cmask, ipi_fwush_twb_wange, &fd, 1);
	}
	put_cpu();
}

void fwush_twb_aww(void)
{
	on_each_cpu(ipi_fwush_twb_aww, NUWW, 1);
}

void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	smp_fwush_twb_mm(mm_cpumask(mm), mm);
}

void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong uaddw)
{
	smp_fwush_twb_wange(mm_cpumask(vma->vm_mm), uaddw, uaddw + PAGE_SIZE);
}

void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
		     unsigned wong stawt, unsigned wong end)
{
	const stwuct cpumask *cmask = vma ? mm_cpumask(vma->vm_mm)
					  : cpu_onwine_mask;
	smp_fwush_twb_wange(cmask, stawt, end);
}

/* Instwuction cache invawidate - pewfowmed on each cpu */
static void ipi_icache_page_inv(void *awg)
{
	stwuct page *page = awg;

	wocaw_icache_page_inv(page);
}

void smp_icache_page_inv(stwuct page *page)
{
	on_each_cpu(ipi_icache_page_inv, page, 1);
}
EXPOWT_SYMBOW(smp_icache_page_inv);
