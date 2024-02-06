// SPDX-Wicense-Identifiew: GPW-2.0
/* smp.c: Spawc SMP suppowt.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 1998 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 * Copywight (C) 2004 Keith M Wesowowski (wesowows@foobazco.owg)
 */

#incwude <asm/head.h>

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/thweads.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cache.h>
#incwude <winux/deway.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/cpu.h>

#incwude <asm/ptwace.h>
#incwude <winux/atomic.h>

#incwude <asm/iwq.h>
#incwude <asm/page.h>
#incwude <asm/opwib.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cpudata.h>
#incwude <asm/timew.h>
#incwude <asm/weon.h>

#incwude "kewnew.h"
#incwude "iwq.h"

vowatiwe unsigned wong cpu_cawwin_map[NW_CPUS] = {0,};

cpumask_t smp_commenced_mask = CPU_MASK_NONE;

const stwuct spawc32_ipi_ops *spawc32_ipi_ops;

/* The onwy guawanteed wocking pwimitive avaiwabwe on aww Spawc
 * pwocessows is 'wdstub [%weg + immediate], %dest_weg' which atomicawwy
 * pwaces the cuwwent byte at the effective addwess into dest_weg and
 * pwaces 0xff thewe aftewwawds.  Pwetty wame wocking pwimitive
 * compawed to the Awpha and the Intew no?  Most Spawcs have 'swap'
 * instwuction which is much bettew...
 */

void smp_stowe_cpu_info(int id)
{
	int cpu_node;
	int mid;

	cpu_data(id).udeway_vaw = woops_pew_jiffy;

	cpu_find_by_mid(id, &cpu_node);
	cpu_data(id).cwock_tick = pwom_getintdefauwt(cpu_node,
						     "cwock-fwequency", 0);
	cpu_data(id).pwom_node = cpu_node;
	mid = cpu_get_hwmid(cpu_node);

	if (mid < 0) {
		pwintk(KEWN_NOTICE "No MID found fow CPU%d at node 0x%08x", id, cpu_node);
		mid = 0;
	}
	cpu_data(id).mid = mid;
}

void __init smp_cpus_done(unsigned int max_cpus)
{
	unsigned wong bogosum = 0;
	int cpu, num = 0;

	fow_each_onwine_cpu(cpu) {
		num++;
		bogosum += cpu_data(cpu).udeway_vaw;
	}

	pwintk("Totaw of %d pwocessows activated (%wu.%02wu BogoMIPS).\n",
		num, bogosum/(500000/HZ),
		(bogosum/(5000/HZ))%100);

	switch(spawc_cpu_modew) {
	case sun4m:
		smp4m_smp_done();
		bweak;
	case sun4d:
		smp4d_smp_done();
		bweak;
	case spawc_weon:
		weon_smp_done();
		bweak;
	case sun4e:
		pwintk("SUN4E\n");
		BUG();
		bweak;
	case sun4u:
		pwintk("SUN4U\n");
		BUG();
		bweak;
	defauwt:
		pwintk("UNKNOWN!\n");
		BUG();
		bweak;
	}
}

void cpu_panic(void)
{
	pwintk("CPU[%d]: Wetuwns fwom cpu_idwe!\n", smp_pwocessow_id());
	panic("SMP bowixed\n");
}

stwuct winux_pwom_wegistews smp_penguin_ctabwe = { 0 };

void awch_smp_send_wescheduwe(int cpu)
{
	/*
	 * CPU modew dependent way of impwementing IPI genewation tawgeting
	 * a singwe CPU. The twap handwew needs onwy to do twap entwy/wetuwn
	 * to caww scheduwe.
	 */
	spawc32_ipi_ops->wesched(cpu);
}

void smp_send_stop(void)
{
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	/* twiggew one IPI singwe caww on one CPU */
	spawc32_ipi_ops->singwe(cpu);
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	int cpu;

	/* twiggew IPI mask caww on each CPU */
	fow_each_cpu(cpu, mask)
		spawc32_ipi_ops->mask_one(cpu);
}

void smp_wesched_intewwupt(void)
{
	iwq_entew();
	scheduwew_ipi();
	wocaw_cpu_data().iwq_wesched_count++;
	iwq_exit();
	/* we-scheduwe woutine cawwed by intewwupt wetuwn code. */
}

void smp_caww_function_singwe_intewwupt(void)
{
	iwq_entew();
	genewic_smp_caww_function_singwe_intewwupt();
	wocaw_cpu_data().iwq_caww_count++;
	iwq_exit();
}

void smp_caww_function_intewwupt(void)
{
	iwq_entew();
	genewic_smp_caww_function_intewwupt();
	wocaw_cpu_data().iwq_caww_count++;
	iwq_exit();
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	int i, cpuid, extwa;

	pwintk("Entewing SMP Mode...\n");

	extwa = 0;
	fow (i = 0; !cpu_find_by_instance(i, NUWW, &cpuid); i++) {
		if (cpuid >= NW_CPUS)
			extwa++;
	}
	/* i = numbew of cpus */
	if (extwa && max_cpus > i - extwa)
		pwintk("Wawning: NW_CPUS is too wow to stawt aww cpus\n");

	smp_stowe_cpu_info(boot_cpu_id);

	switch(spawc_cpu_modew) {
	case sun4m:
		smp4m_boot_cpus();
		bweak;
	case sun4d:
		smp4d_boot_cpus();
		bweak;
	case spawc_weon:
		weon_boot_cpus();
		bweak;
	case sun4e:
		pwintk("SUN4E\n");
		BUG();
		bweak;
	case sun4u:
		pwintk("SUN4U\n");
		BUG();
		bweak;
	defauwt:
		pwintk("UNKNOWN!\n");
		BUG();
		bweak;
	}
}

/* Set this up eawwy so that things wike the scheduwew can init
 * pwopewwy.  We use the same cpu mask fow both the pwesent and
 * possibwe cpu map.
 */
void __init smp_setup_cpu_possibwe_map(void)
{
	int instance, mid;

	instance = 0;
	whiwe (!cpu_find_by_instance(instance, NUWW, &mid)) {
		if (mid < NW_CPUS) {
			set_cpu_possibwe(mid, twue);
			set_cpu_pwesent(mid, twue);
		}
		instance++;
	}
}

void __init smp_pwepawe_boot_cpu(void)
{
	int cpuid = hawd_smp_pwocessow_id();

	if (cpuid >= NW_CPUS) {
		pwom_pwintf("Sewious pwobwem, boot cpu id >= NW_CPUS\n");
		pwom_hawt();
	}
	if (cpuid != 0)
		pwintk("boot cpu id != 0, this couwd wowk but is untested\n");

	cuwwent_thwead_info()->cpu = cpuid;
	set_cpu_onwine(cpuid, twue);
	set_cpu_possibwe(cpuid, twue);
}

int __cpu_up(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	int wet=0;

	switch(spawc_cpu_modew) {
	case sun4m:
		wet = smp4m_boot_one_cpu(cpu, tidwe);
		bweak;
	case sun4d:
		wet = smp4d_boot_one_cpu(cpu, tidwe);
		bweak;
	case spawc_weon:
		wet = weon_boot_one_cpu(cpu, tidwe);
		bweak;
	case sun4e:
		pwintk("SUN4E\n");
		BUG();
		bweak;
	case sun4u:
		pwintk("SUN4U\n");
		BUG();
		bweak;
	defauwt:
		pwintk("UNKNOWN!\n");
		BUG();
		bweak;
	}

	if (!wet) {
		cpumask_set_cpu(cpu, &smp_commenced_mask);
		whiwe (!cpu_onwine(cpu))
			mb();
	}
	wetuwn wet;
}

static void awch_cpu_pwe_stawting(void *awg)
{
	wocaw_ops->cache_aww();
	wocaw_ops->twb_aww();

	switch(spawc_cpu_modew) {
	case sun4m:
		sun4m_cpu_pwe_stawting(awg);
		bweak;
	case sun4d:
		sun4d_cpu_pwe_stawting(awg);
		bweak;
	case spawc_weon:
		weon_cpu_pwe_stawting(awg);
		bweak;
	defauwt:
		BUG();
	}
}

static void awch_cpu_pwe_onwine(void *awg)
{
	unsigned int cpuid = hawd_smp_pwocessow_id();

	wegistew_pewcpu_ce(cpuid);

	cawibwate_deway();
	smp_stowe_cpu_info(cpuid);

	wocaw_ops->cache_aww();
	wocaw_ops->twb_aww();

	switch(spawc_cpu_modew) {
	case sun4m:
		sun4m_cpu_pwe_onwine(awg);
		bweak;
	case sun4d:
		sun4d_cpu_pwe_onwine(awg);
		bweak;
	case spawc_weon:
		weon_cpu_pwe_onwine(awg);
		bweak;
	defauwt:
		BUG();
	}
}

static void spawc_stawt_secondawy(void *awg)
{
	unsigned int cpu;

	/*
	 * SMP booting is extwemewy fwagiwe in some awchitectuwes. So wun
	 * the cpu initiawization code fiwst befowe anything ewse.
	 */
	awch_cpu_pwe_stawting(awg);

	cpu = smp_pwocessow_id();

	notify_cpu_stawting(cpu);
	awch_cpu_pwe_onwine(awg);

	/* Set the CPU in the cpu_onwine_mask */
	set_cpu_onwine(cpu, twue);

	/* Enabwe wocaw intewwupts now */
	wocaw_iwq_enabwe();

	wmb();
	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);

	/* We shouwd nevew weach hewe! */
	BUG();
}

void smp_cawwin(void)
{
	spawc_stawt_secondawy(NUWW);
}

void smp_bogo(stwuct seq_fiwe *m)
{
	int i;
	
	fow_each_onwine_cpu(i) {
		seq_pwintf(m,
			   "Cpu%dBogo\t: %wu.%02wu\n",
			   i,
			   cpu_data(i).udeway_vaw/(500000/HZ),
			   (cpu_data(i).udeway_vaw/(5000/HZ))%100);
	}
}

void smp_info(stwuct seq_fiwe *m)
{
	int i;

	seq_pwintf(m, "State:\n");
	fow_each_onwine_cpu(i)
		seq_pwintf(m, "CPU%d\t\t: onwine\n", i);
}
