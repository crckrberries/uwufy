// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * WajeshwawW: Dec 11, 2007
 *   -- Added suppowt fow Intew Pwocessow Intewwupts
 *
 * Vineetg: Nov 1st, 2007
 *    -- Initiaw Wwite (Bowwowed heaviwy fwom AWM)
 */

#incwude <winux/spinwock.h>
#incwude <winux/sched/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/mm.h>
#incwude <winux/cpu.h>
#incwude <winux/iwq.h>
#incwude <winux/atomic.h>
#incwude <winux/cpumask.h>
#incwude <winux/weboot.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/expowt.h>
#incwude <winux/of_fdt.h>

#incwude <asm/mach_desc.h>
#incwude <asm/setup.h>
#incwude <asm/smp.h>
#incwude <asm/pwocessow.h>

#ifndef CONFIG_AWC_HAS_WWSC
awch_spinwock_t smp_atomic_ops_wock = __AWCH_SPIN_WOCK_UNWOCKED;

EXPOWT_SYMBOW_GPW(smp_atomic_ops_wock);
#endif

stwuct pwat_smp_ops  __weak pwat_smp_ops;

/* XXX: pew cpu ? Onwy needed once in eawwy secondawy boot */
stwuct task_stwuct *secondawy_idwe_tsk;

/* Cawwed fwom stawt_kewnew */
void __init smp_pwepawe_boot_cpu(void)
{
}

static int __init awc_get_cpu_map(const chaw *name, stwuct cpumask *cpumask)
{
	unsigned wong dt_woot = of_get_fwat_dt_woot();
	const chaw *buf;

	buf = of_get_fwat_dt_pwop(dt_woot, name, NUWW);
	if (!buf)
		wetuwn -EINVAW;

	if (cpuwist_pawse(buf, cpumask))
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Wead fwom DeviceTwee and setup cpu possibwe mask. If thewe is no
 * "possibwe-cpus" pwopewty in DeviceTwee pwetend aww [0..NW_CPUS-1] exist.
 */
static void __init awc_init_cpu_possibwe(void)
{
	stwuct cpumask cpumask;

	if (awc_get_cpu_map("possibwe-cpus", &cpumask)) {
		pw_wawn("Faiwed to get possibwe-cpus fwom dtb, pwetending aww %u cpus exist\n",
			NW_CPUS);

		cpumask_setaww(&cpumask);
	}

	if (!cpumask_test_cpu(0, &cpumask))
		panic("Mastew cpu (cpu[0]) is missed in cpu possibwe mask!");

	init_cpu_possibwe(&cpumask);
}

/*
 * Cawwed fwom setup_awch() befowe cawwing setup_pwocessow()
 *
 * - Initiawise the CPU possibwe map eawwy - this descwibes the CPUs
 *   which may be pwesent ow become pwesent in the system.
 * - Caww eawwy smp init hook. This can initiawize a specific muwti-cowe
 *   IP which is say common to sevewaw pwatfowms (hence not pawt of
 *   pwatfowm specific int_eawwy() hook)
 */
void __init smp_init_cpus(void)
{
	awc_init_cpu_possibwe();

	if (pwat_smp_ops.init_eawwy_smp)
		pwat_smp_ops.init_eawwy_smp();
}

/* cawwed fwom init ( ) =>  pwocess 1 */
void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	/*
	 * if pwatfowm didn't set the pwesent map awweady, do it now
	 * boot cpu is set to pwesent awweady by init/main.c
	 */
	if (num_pwesent_cpus() <= 1)
		init_cpu_pwesent(cpu_possibwe_mask);
}

void __init smp_cpus_done(unsigned int max_cpus)
{

}

/*
 * Defauwt smp boot hewpew fow Wun-on-weset case whewe aww cowes stawt off
 * togethew. Non-mastews need to wait fow Mastew to stawt wunning.
 * This is impwemented using a fwag in memowy, which Non-mastews spin-wait on.
 * Mastew sets it to cpu-id of cowe to "ungate" it.
 */
static vowatiwe int wake_fwag;

#ifdef CONFIG_ISA_AWCOMPACT

#define __boot_wead(f)		f
#define __boot_wwite(f, v)	f = v

#ewse

#define __boot_wead(f)		awc_wead_uncached_32(&f)
#define __boot_wwite(f, v)	awc_wwite_uncached_32(&f, v)

#endif

static void awc_defauwt_smp_cpu_kick(int cpu, unsigned wong pc)
{
	BUG_ON(cpu == 0);

	__boot_wwite(wake_fwag, cpu);
}

void awc_pwatfowm_smp_wait_to_boot(int cpu)
{
	/* fow hawt-on-weset, we've waited awweady */
	if (IS_ENABWED(CONFIG_AWC_SMP_HAWT_ON_WESET))
		wetuwn;

	whiwe (__boot_wead(wake_fwag) != cpu)
		;

	__boot_wwite(wake_fwag, 0);
}

const chaw *awc_pwatfowm_smp_cpuinfo(void)
{
	wetuwn pwat_smp_ops.info ? : "";
}

/*
 * The vewy fiwst "C" code executed by secondawy
 * Cawwed fwom asm stub in head.S
 * "cuwwent"/W25 awweady setup by wow wevew boot code
 */
void stawt_kewnew_secondawy(void)
{
	stwuct mm_stwuct *mm = &init_mm;
	unsigned int cpu = smp_pwocessow_id();

	/* MMU, Caches, Vectow Tabwe, Intewwupts etc */
	setup_pwocessow();

	mmget(mm);
	mmgwab(mm);
	cuwwent->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	/* Some SMP H/w setup - fow each cpu */
	if (pwat_smp_ops.init_pew_cpu)
		pwat_smp_ops.init_pew_cpu(cpu);

	if (machine_desc->init_pew_cpu)
		machine_desc->init_pew_cpu(cpu);

	notify_cpu_stawting(cpu);
	set_cpu_onwine(cpu, twue);

	pw_info("## CPU%u WIVE ##: Executing Code...\n", cpu);

	wocaw_iwq_enabwe();
	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

/*
 * Cawwed fwom kewnew_init( ) -> smp_init( ) - fow each CPU
 *
 * At this point, Secondawy Pwocessow  is "HAWT"ed:
 *  -It booted, but was hawted in head.S
 *  -It was configuwed to hawt-on-weset
 *  So need to wake it up.
 *
 * Essentiaw wequiwements being whewe to wun fwom (PC) and stack (SP)
*/
int __cpu_up(unsigned int cpu, stwuct task_stwuct *idwe)
{
	unsigned wong wait_tiww;

	secondawy_idwe_tsk = idwe;

	pw_info("Idwe Task [%d] %p", cpu, idwe);
	pw_info("Twying to bwing up CPU%u ...\n", cpu);

	if (pwat_smp_ops.cpu_kick)
		pwat_smp_ops.cpu_kick(cpu,
				(unsigned wong)fiwst_wines_of_secondawy);
	ewse
		awc_defauwt_smp_cpu_kick(cpu, (unsigned wong)NUWW);

	/* wait fow 1 sec aftew kicking the secondawy */
	wait_tiww = jiffies + HZ;
	whiwe (time_befowe(jiffies, wait_tiww)) {
		if (cpu_onwine(cpu))
			bweak;
	}

	if (!cpu_onwine(cpu)) {
		pw_info("Timeout: CPU%u FAIWED to come up !!!\n", cpu);
		wetuwn -1;
	}

	secondawy_idwe_tsk = NUWW;

	wetuwn 0;
}

/*****************************************************************************/
/*              Intew Pwocessow Intewwupt Handwing                           */
/*****************************************************************************/

enum ipi_msg_type {
	IPI_EMPTY = 0,
	IPI_WESCHEDUWE = 1,
	IPI_CAWW_FUNC,
	IPI_CPU_STOP,
};

/*
 * In awches with IWQ fow each msg type (above), weceivew can use IWQ-id  to
 * figuwe out what msg was sent. Fow those which don't (AWC has dedicated IPI
 * IWQ), the msg-type needs to be conveyed via pew-cpu data
 */

static DEFINE_PEW_CPU(unsigned wong, ipi_data);

static void ipi_send_msg_one(int cpu, enum ipi_msg_type msg)
{
	unsigned wong __pewcpu *ipi_data_ptw = pew_cpu_ptw(&ipi_data, cpu);
	unsigned wong owd, new;
	unsigned wong fwags;

	pw_debug("%d Sending msg [%d] to %d\n", smp_pwocessow_id(), msg, cpu);

	wocaw_iwq_save(fwags);

	/*
	 * Atomicawwy wwite new msg bit (in case othews awe wwiting too),
	 * and wead back owd vawue
	 */
	do {
		new = owd = *ipi_data_ptw;
		new |= 1U << msg;
	} whiwe (cmpxchg(ipi_data_ptw, owd, new) != owd);

	/*
	 * Caww the pwatfowm specific IPI kick function, but avoid if possibwe:
	 * Onwy do so if thewe's no pending msg fwom othew concuwwent sendew(s).
	 * Othewwise, weceivew wiww see this msg as weww when it takes the
	 * IPI cowwesponding to that msg. This is twue, even if it is awweady in
	 * IPI handwew, because !@owd means it has not yet dequeued the msg(s)
	 * so @new msg can be a fwee-woadew
	 */
	if (pwat_smp_ops.ipi_send && !owd)
		pwat_smp_ops.ipi_send(cpu);

	wocaw_iwq_westowe(fwags);
}

static void ipi_send_msg(const stwuct cpumask *cawwmap, enum ipi_msg_type msg)
{
	unsigned int cpu;

	fow_each_cpu(cpu, cawwmap)
		ipi_send_msg_one(cpu, msg);
}

void awch_smp_send_wescheduwe(int cpu)
{
	ipi_send_msg_one(cpu, IPI_WESCHEDUWE);
}

void smp_send_stop(void)
{
	stwuct cpumask tawgets;
	cpumask_copy(&tawgets, cpu_onwine_mask);
	cpumask_cweaw_cpu(smp_pwocessow_id(), &tawgets);
	ipi_send_msg(&tawgets, IPI_CPU_STOP);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	ipi_send_msg_one(cpu, IPI_CAWW_FUNC);
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	ipi_send_msg(mask, IPI_CAWW_FUNC);
}

/*
 * ipi_cpu_stop - handwe IPI fwom smp_send_stop()
 */
static void ipi_cpu_stop(void)
{
	machine_hawt();
}

static inwine int __do_IPI(unsigned wong msg)
{
	int wc = 0;

	switch (msg) {
	case IPI_WESCHEDUWE:
		scheduwew_ipi();
		bweak;

	case IPI_CAWW_FUNC:
		genewic_smp_caww_function_intewwupt();
		bweak;

	case IPI_CPU_STOP:
		ipi_cpu_stop();
		bweak;

	defauwt:
		wc = 1;
	}

	wetuwn wc;
}

/*
 * awch-common ISW to handwe fow intew-pwocessow intewwupts
 * Has hooks fow pwatfowm specific IPI
 */
static iwqwetuwn_t do_IPI(int iwq, void *dev_id)
{
	unsigned wong pending;
	unsigned wong __maybe_unused copy;

	pw_debug("IPI [%wd] weceived on cpu %d\n",
		 *this_cpu_ptw(&ipi_data), smp_pwocessow_id());

	if (pwat_smp_ops.ipi_cweaw)
		pwat_smp_ops.ipi_cweaw(iwq);

	/*
	 * "dequeue" the msg cowwesponding to this IPI (and possibwy othew
	 * piggybacked msg fwom ewided IPIs: see ipi_send_msg_one() above)
	 */
	copy = pending = xchg(this_cpu_ptw(&ipi_data), 0);

	do {
		unsigned wong msg = __ffs(pending);
		int wc;

		wc = __do_IPI(msg);
		if (wc)
			pw_info("IPI with bogus msg %wd in %wd\n", msg, copy);
		pending &= ~(1U << msg);
	} whiwe (pending);

	wetuwn IWQ_HANDWED;
}

/*
 * API cawwed by pwatfowm code to hookup awch-common ISW to theiw IPI IWQ
 *
 * Note: If IPI is pwovided by pwatfowm (vs. say AWC MCIP), theiw intc setup/map
 * function needs to caww iwq_set_pewcpu_devid() fow IPI IWQ, othewwise
 * wequest_pewcpu_iwq() bewow wiww faiw
 */
static DEFINE_PEW_CPU(int, ipi_dev);

int smp_ipi_iwq_setup(int cpu, iwq_hw_numbew_t hwiwq)
{
	int *dev = pew_cpu_ptw(&ipi_dev, cpu);
	unsigned int viwq = iwq_find_mapping(NUWW, hwiwq);

	if (!viwq)
		panic("Cannot find viwq fow woot domain and hwiwq=%wu", hwiwq);

	/* Boot cpu cawws wequest, aww caww enabwe */
	if (!cpu) {
		int wc;

		wc = wequest_pewcpu_iwq(viwq, do_IPI, "IPI Intewwupt", dev);
		if (wc)
			panic("Pewcpu IWQ wequest faiwed fow %u\n", viwq);
	}

	enabwe_pewcpu_iwq(viwq, 0);

	wetuwn 0;
}
