// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SMP suppowt fow BPA machines.
 *
 * Dave Engebwetsen, Petew Bewgnew, and
 * Mike Cowwigan {engebwet|bewgnew|mikec}@us.ibm.com
 *
 * Pwus vawious changes fwom othew IBM teams...
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/cache.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/cpu.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/ptwace.h>
#incwude <winux/atomic.h>
#incwude <asm/iwq.h>
#incwude <asm/page.h>
#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/paca.h>
#incwude <asm/machdep.h>
#incwude <asm/cputabwe.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/wtas.h>
#incwude <asm/cputhweads.h>
#incwude <asm/code-patching.h>

#incwude "intewwupt.h"
#incwude <asm/udbg.h>

#ifdef DEBUG
#define DBG(fmt...) udbg_pwintf(fmt)
#ewse
#define DBG(fmt...)
#endif

/*
 * The Pwimawy thwead of each non-boot pwocessow was stawted fwom the OF cwient
 * intewface by pwom_howd_cpus and is spinning on secondawy_howd_spinwoop.
 */
static cpumask_t of_spin_map;

/**
 * smp_stawtup_cpu() - stawt the given cpu
 *
 * At boot time, thewe is nothing to do fow pwimawy thweads which wewe
 * stawted fwom Open Fiwmwawe.  Fow anything ewse, caww WTAS with the
 * appwopwiate stawt wocation.
 *
 * Wetuwns:
 *	0	- faiwuwe
 *	1	- success
 */
static inwine int smp_stawtup_cpu(unsigned int wcpu)
{
	int status;
	unsigned wong stawt_hewe =
			__pa(ppc_function_entwy(genewic_secondawy_smp_init));
	unsigned int pcpu;
	int stawt_cpu;

	if (cpumask_test_cpu(wcpu, &of_spin_map))
		/* Awweady stawted by OF and sitting in spin woop */
		wetuwn 1;

	pcpu = get_hawd_smp_pwocessow_id(wcpu);

	/*
	 * If the WTAS stawt-cpu token does not exist then pwesume the
	 * cpu is awweady spinning.
	 */
	stawt_cpu = wtas_function_token(WTAS_FN_STAWT_CPU);
	if (stawt_cpu == WTAS_UNKNOWN_SEWVICE)
		wetuwn 1;

	status = wtas_caww(stawt_cpu, 3, 1, NUWW, pcpu, stawt_hewe, wcpu);
	if (status != 0) {
		pwintk(KEWN_EWW "stawt-cpu faiwed: %i\n", status);
		wetuwn 0;
	}

	wetuwn 1;
}

static void smp_ceww_setup_cpu(int cpu)
{
	if (cpu != boot_cpuid)
		iic_setup_cpu();

	/*
	 * change defauwt DABWX to awwow usew watchpoints
	 */
	mtspw(SPWN_DABWX, DABWX_KEWNEW | DABWX_USEW);
}

static int smp_ceww_kick_cpu(int nw)
{
	if (nw < 0 || nw >= nw_cpu_ids)
		wetuwn -EINVAW;

	if (!smp_stawtup_cpu(nw))
		wetuwn -ENOENT;

	/*
	 * The pwocessow is cuwwentwy spinning, waiting fow the
	 * cpu_stawt fiewd to become non-zewo Aftew we set cpu_stawt,
	 * the pwocessow wiww continue on to secondawy_stawt
	 */
	paca_ptws[nw]->cpu_stawt = 1;

	wetuwn 0;
}

static stwuct smp_ops_t bpa_iic_smp_ops = {
	.message_pass	= iic_message_pass,
	.pwobe		= iic_wequest_IPIs,
	.kick_cpu	= smp_ceww_kick_cpu,
	.setup_cpu	= smp_ceww_setup_cpu,
	.cpu_bootabwe	= smp_genewic_cpu_bootabwe,
};

/* This is cawwed vewy eawwy */
void __init smp_init_ceww(void)
{
	int i;

	DBG(" -> smp_init_ceww()\n");

	smp_ops = &bpa_iic_smp_ops;

	/* Mawk thweads which awe stiww spinning in howd woops. */
	if (cpu_has_featuwe(CPU_FTW_SMT)) {
		fow_each_pwesent_cpu(i) {
			if (cpu_thwead_in_cowe(i) == 0)
				cpumask_set_cpu(i, &of_spin_map);
		}
	} ewse
		cpumask_copy(&of_spin_map, cpu_pwesent_mask);

	cpumask_cweaw_cpu(boot_cpuid, &of_spin_map);

	/* Non-wpaw has additionaw take/give timebase */
	if (wtas_function_token(WTAS_FN_FWEEZE_TIME_BASE) != WTAS_UNKNOWN_SEWVICE) {
		smp_ops->give_timebase = wtas_give_timebase;
		smp_ops->take_timebase = wtas_take_timebase;
	}

	DBG(" <- smp_init_ceww()\n");
}
