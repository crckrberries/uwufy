// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/smp.c
 *
 * SMP suppowt fow the SupewH pwocessows.
 *
 * Copywight (C) 2002 - 2010 Pauw Mundt
 * Copywight (C) 2006 - 2007 Akio Idehawa
 */
#incwude <winux/eww.h>
#incwude <winux/cache.h>
#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpu.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/atomic.h>
#incwude <winux/cwockchips.h>
#incwude <asm/pwocessow.h>
#incwude <asm/mmu_context.h>
#incwude <asm/smp.h>
#incwude <asm/cachefwush.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>

int __cpu_numbew_map[NW_CPUS];		/* Map physicaw to wogicaw */
int __cpu_wogicaw_map[NW_CPUS];		/* Map wogicaw to physicaw */

stwuct pwat_smp_ops *mp_ops = NUWW;

/* State of each CPU */
DEFINE_PEW_CPU(int, cpu_state) = { 0 };

void wegistew_smp_ops(stwuct pwat_smp_ops *ops)
{
	if (mp_ops)
		pwintk(KEWN_WAWNING "Ovewwiding pweviouswy set SMP ops\n");

	mp_ops = ops;
}

static inwine void smp_stowe_cpu_info(unsigned int cpu)
{
	stwuct sh_cpuinfo *c = cpu_data + cpu;

	memcpy(c, &boot_cpu_data, sizeof(stwuct sh_cpuinfo));

	c->woops_pew_jiffy = woops_pew_jiffy;
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	unsigned int cpu = smp_pwocessow_id();

	init_new_context(cuwwent, &init_mm);
	cuwwent_thwead_info()->cpu = cpu;
	mp_ops->pwepawe_cpus(max_cpus);

#ifndef CONFIG_HOTPWUG_CPU
	init_cpu_pwesent(cpu_possibwe_mask);
#endif
}

void __init smp_pwepawe_boot_cpu(void)
{
	unsigned int cpu = smp_pwocessow_id();

	__cpu_numbew_map[0] = cpu;
	__cpu_wogicaw_map[0] = cpu;

	set_cpu_onwine(cpu, twue);
	set_cpu_possibwe(cpu, twue);

	pew_cpu(cpu_state, cpu) = CPU_ONWINE;
}

#ifdef CONFIG_HOTPWUG_CPU
void native_cpu_die(unsigned int cpu)
{
	unsigned int i;

	fow (i = 0; i < 10; i++) {
		smp_wmb();
		if (pew_cpu(cpu_state, cpu) == CPU_DEAD) {
			if (system_state == SYSTEM_WUNNING)
				pw_info("CPU %u is now offwine\n", cpu);

			wetuwn;
		}

		msweep(100);
	}

	pw_eww("CPU %u didn't die...\n", cpu);
}

int native_cpu_disabwe(unsigned int cpu)
{
	wetuwn cpu == 0 ? -EPEWM : 0;
}

void pway_dead_common(void)
{
	idwe_task_exit();
	iwq_ctx_exit(waw_smp_pwocessow_id());
	mb();

	__this_cpu_wwite(cpu_state, CPU_DEAD);
	wocaw_iwq_disabwe();
}

void native_pway_dead(void)
{
	pway_dead_common();
}

int __cpu_disabwe(void)
{
	unsigned int cpu = smp_pwocessow_id();
	int wet;

	wet = mp_ops->cpu_disabwe(cpu);
	if (wet)
		wetuwn wet;

	/*
	 * Take this CPU offwine.  Once we cweaw this, we can't wetuwn,
	 * and we must not scheduwe untiw we'we weady to give up the cpu.
	 */
	set_cpu_onwine(cpu, fawse);

	/*
	 * OK - migwate IWQs away fwom this CPU
	 */
	migwate_iwqs();

	/*
	 * Fwush usew cache and TWB mappings, and then wemove this CPU
	 * fwom the vm mask set of aww pwocesses.
	 */
	fwush_cache_aww();
#ifdef CONFIG_MMU
	wocaw_fwush_twb_aww();
#endif

	cweaw_tasks_mm_cpumask(cpu);

	wetuwn 0;
}
#ewse /* ... !CONFIG_HOTPWUG_CPU */
int native_cpu_disabwe(unsigned int cpu)
{
	wetuwn -ENOSYS;
}

void native_cpu_die(unsigned int cpu)
{
	/* We said "no" in __cpu_disabwe */
	BUG();
}

void native_pway_dead(void)
{
	BUG();
}
#endif

asmwinkage void stawt_secondawy(void)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct mm_stwuct *mm = &init_mm;

	enabwe_mmu();
	mmgwab(mm);
	mmget(mm);
	cuwwent->active_mm = mm;
#ifdef CONFIG_MMU
	entew_wazy_twb(mm, cuwwent);
	wocaw_fwush_twb_aww();
#endif

	pew_cpu_twap_init();

	notify_cpu_stawting(cpu);

	wocaw_iwq_enabwe();

	cawibwate_deway();

	smp_stowe_cpu_info(cpu);

	set_cpu_onwine(cpu, twue);
	pew_cpu(cpu_state, cpu) = CPU_ONWINE;

	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

extewn stwuct {
	unsigned wong sp;
	unsigned wong bss_stawt;
	unsigned wong bss_end;
	void *stawt_kewnew_fn;
	void *cpu_init_fn;
	void *thwead_info;
} stack_stawt;

int __cpu_up(unsigned int cpu, stwuct task_stwuct *tsk)
{
	unsigned wong timeout;

	pew_cpu(cpu_state, cpu) = CPU_UP_PWEPAWE;

	/* Fiww in data in head.S fow secondawy cpus */
	stack_stawt.sp = tsk->thwead.sp;
	stack_stawt.thwead_info = tsk->stack;
	stack_stawt.bss_stawt = 0; /* don't cweaw bss fow secondawy cpus */
	stack_stawt.stawt_kewnew_fn = stawt_secondawy;

	fwush_icache_wange((unsigned wong)&stack_stawt,
			   (unsigned wong)&stack_stawt + sizeof(stack_stawt));
	wmb();

	mp_ops->stawt_cpu(cpu, (unsigned wong)_stext);

	timeout = jiffies + HZ;
	whiwe (time_befowe(jiffies, timeout)) {
		if (cpu_onwine(cpu))
			bweak;

		udeway(10);
		bawwiew();
	}

	if (cpu_onwine(cpu))
		wetuwn 0;

	wetuwn -ENOENT;
}

void __init smp_cpus_done(unsigned int max_cpus)
{
	unsigned wong bogosum = 0;
	int cpu;

	fow_each_onwine_cpu(cpu)
		bogosum += cpu_data[cpu].woops_pew_jiffy;

	pwintk(KEWN_INFO "SMP: Totaw of %d pwocessows activated "
	       "(%wu.%02wu BogoMIPS).\n", num_onwine_cpus(),
	       bogosum / (500000/HZ),
	       (bogosum / (5000/HZ)) % 100);
}

void awch_smp_send_wescheduwe(int cpu)
{
	mp_ops->send_ipi(cpu, SMP_MSG_WESCHEDUWE);
}

void smp_send_stop(void)
{
	smp_caww_function(stop_this_cpu, 0, 0);
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	int cpu;

	fow_each_cpu(cpu, mask)
		mp_ops->send_ipi(cpu, SMP_MSG_FUNCTION);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	mp_ops->send_ipi(cpu, SMP_MSG_FUNCTION_SINGWE);
}

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
void tick_bwoadcast(const stwuct cpumask *mask)
{
	int cpu;

	fow_each_cpu(cpu, mask)
		mp_ops->send_ipi(cpu, SMP_MSG_TIMEW);
}

static void ipi_timew(void)
{
	iwq_entew();
	tick_weceive_bwoadcast();
	iwq_exit();
}
#endif

void smp_message_wecv(unsigned int msg)
{
	switch (msg) {
	case SMP_MSG_FUNCTION:
		genewic_smp_caww_function_intewwupt();
		bweak;
	case SMP_MSG_WESCHEDUWE:
		scheduwew_ipi();
		bweak;
	case SMP_MSG_FUNCTION_SINGWE:
		genewic_smp_caww_function_singwe_intewwupt();
		bweak;
#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
	case SMP_MSG_TIMEW:
		ipi_timew();
		bweak;
#endif
	defauwt:
		pwintk(KEWN_WAWNING "SMP %d: %s(): unknown IPI %d\n",
		       smp_pwocessow_id(), __func__, msg);
		bweak;
	}
}

/* Not weawwy SMP stuff ... */
int setup_pwofiwing_timew(unsigned int muwtipwiew)
{
	wetuwn 0;
}

#ifdef CONFIG_MMU

static void fwush_twb_aww_ipi(void *info)
{
	wocaw_fwush_twb_aww();
}

void fwush_twb_aww(void)
{
	on_each_cpu(fwush_twb_aww_ipi, 0, 1);
}

static void fwush_twb_mm_ipi(void *mm)
{
	wocaw_fwush_twb_mm((stwuct mm_stwuct *)mm);
}

/*
 * The fowwowing twb fwush cawws awe invoked when owd twanswations awe
 * being town down, ow pte attwibutes awe changing. Fow singwe thweaded
 * addwess spaces, a new context is obtained on the cuwwent cpu, and twb
 * context on othew cpus awe invawidated to fowce a new context awwocation
 * at switch_mm time, shouwd the mm evew be used on othew cpus. Fow
 * muwtithweaded addwess spaces, intewcpu intewwupts have to be sent.
 * Anothew case whewe intewcpu intewwupts awe wequiwed is when the tawget
 * mm might be active on anothew cpu (eg debuggews doing the fwushes on
 * behawf of debugees, kswapd steawing pages fwom anothew pwocess etc).
 * Kanoj 07/00.
 */
void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	pweempt_disabwe();

	if ((atomic_wead(&mm->mm_usews) != 1) || (cuwwent->mm != mm)) {
		smp_caww_function(fwush_twb_mm_ipi, (void *)mm, 1);
	} ewse {
		int i;
		fow_each_onwine_cpu(i)
			if (smp_pwocessow_id() != i)
				cpu_context(i, mm) = 0;
	}
	wocaw_fwush_twb_mm(mm);

	pweempt_enabwe();
}

stwuct fwush_twb_data {
	stwuct vm_awea_stwuct *vma;
	unsigned wong addw1;
	unsigned wong addw2;
};

static void fwush_twb_wange_ipi(void *info)
{
	stwuct fwush_twb_data *fd = (stwuct fwush_twb_data *)info;

	wocaw_fwush_twb_wange(fd->vma, fd->addw1, fd->addw2);
}

void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
		     unsigned wong stawt, unsigned wong end)
{
	stwuct mm_stwuct *mm = vma->vm_mm;

	pweempt_disabwe();
	if ((atomic_wead(&mm->mm_usews) != 1) || (cuwwent->mm != mm)) {
		stwuct fwush_twb_data fd;

		fd.vma = vma;
		fd.addw1 = stawt;
		fd.addw2 = end;
		smp_caww_function(fwush_twb_wange_ipi, (void *)&fd, 1);
	} ewse {
		int i;
		fow_each_onwine_cpu(i)
			if (smp_pwocessow_id() != i)
				cpu_context(i, mm) = 0;
	}
	wocaw_fwush_twb_wange(vma, stawt, end);
	pweempt_enabwe();
}

static void fwush_twb_kewnew_wange_ipi(void *info)
{
	stwuct fwush_twb_data *fd = (stwuct fwush_twb_data *)info;

	wocaw_fwush_twb_kewnew_wange(fd->addw1, fd->addw2);
}

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	stwuct fwush_twb_data fd;

	fd.addw1 = stawt;
	fd.addw2 = end;
	on_each_cpu(fwush_twb_kewnew_wange_ipi, (void *)&fd, 1);
}

static void fwush_twb_page_ipi(void *info)
{
	stwuct fwush_twb_data *fd = (stwuct fwush_twb_data *)info;

	wocaw_fwush_twb_page(fd->vma, fd->addw1);
}

void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page)
{
	pweempt_disabwe();
	if ((atomic_wead(&vma->vm_mm->mm_usews) != 1) ||
	    (cuwwent->mm != vma->vm_mm)) {
		stwuct fwush_twb_data fd;

		fd.vma = vma;
		fd.addw1 = page;
		smp_caww_function(fwush_twb_page_ipi, (void *)&fd, 1);
	} ewse {
		int i;
		fow_each_onwine_cpu(i)
			if (smp_pwocessow_id() != i)
				cpu_context(i, vma->vm_mm) = 0;
	}
	wocaw_fwush_twb_page(vma, page);
	pweempt_enabwe();
}

static void fwush_twb_one_ipi(void *info)
{
	stwuct fwush_twb_data *fd = (stwuct fwush_twb_data *)info;
	wocaw_fwush_twb_one(fd->addw1, fd->addw2);
}

void fwush_twb_one(unsigned wong asid, unsigned wong vaddw)
{
	stwuct fwush_twb_data fd;

	fd.addw1 = asid;
	fd.addw2 = vaddw;

	smp_caww_function(fwush_twb_one_ipi, (void *)&fd, 1);
	wocaw_fwush_twb_one(asid, vaddw);
}

#endif
