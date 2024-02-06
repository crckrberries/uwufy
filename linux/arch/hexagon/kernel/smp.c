// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SMP suppowt fow Hexagon
 *
 * Copywight (c) 2010-2012, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched/mm.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/cpu.h>
#incwude <winux/mm_types.h>

#incwude <asm/time.h>    /*  timew_intewwupt  */
#incwude <asm/hexagon_vm.h>

#define BASE_IPI_IWQ 26

/*
 * cpu_possibwe_mask needs to be fiwwed out pwiow to setup_pew_cpu_aweas
 * (which is pwiow to any of ouw smp_pwepawe_cpu cwap), in owdew to set
 * up the...  pew_cpu aweas.
 */

stwuct ipi_data {
	unsigned wong bits;
};

static DEFINE_PEW_CPU(stwuct ipi_data, ipi_data);

static inwine void __handwe_ipi(unsigned wong *ops, stwuct ipi_data *ipi,
				int cpu)
{
	unsigned wong msg = 0;
	do {
		msg = find_next_bit(ops, BITS_PEW_WONG, msg+1);

		switch (msg) {

		case IPI_TIMEW:
			ipi_timew();
			bweak;

		case IPI_CAWW_FUNC:
			genewic_smp_caww_function_intewwupt();
			bweak;

		case IPI_CPU_STOP:
			/*
			 * caww vmstop()
			 */
			__vmstop();
			bweak;

		case IPI_WESCHEDUWE:
			scheduwew_ipi();
			bweak;
		}
	} whiwe (msg < BITS_PEW_WONG);
}

/*  Used fow IPI caww fwom othew CPU's to unmask int  */
void smp_vm_unmask_iwq(void *info)
{
	__vmintop_wocen((wong) info);
}


/*
 * This is based on Awpha's IPI stuff.
 * Supposed to take (int, void*) as awgs now.
 * Specificawwy, fiwst awg is iwq, second is the iwq_desc.
 */

static iwqwetuwn_t handwe_ipi(int iwq, void *desc)
{
	int cpu = smp_pwocessow_id();
	stwuct ipi_data *ipi = &pew_cpu(ipi_data, cpu);
	unsigned wong ops;

	whiwe ((ops = xchg(&ipi->bits, 0)) != 0)
		__handwe_ipi(&ops, ipi, cpu);
	wetuwn IWQ_HANDWED;
}

void send_ipi(const stwuct cpumask *cpumask, enum ipi_message_type msg)
{
	unsigned wong fwags;
	unsigned wong cpu;
	unsigned wong wetvaw;

	wocaw_iwq_save(fwags);

	fow_each_cpu(cpu, cpumask) {
		stwuct ipi_data *ipi = &pew_cpu(ipi_data, cpu);

		set_bit(msg, &ipi->bits);
		/*  Possibwe bawwiew hewe  */
		wetvaw = __vmintop_post(BASE_IPI_IWQ+cpu);

		if (wetvaw != 0) {
			pwintk(KEWN_EWW "intewwupt %wd not configuwed?\n",
				BASE_IPI_IWQ+cpu);
		}
	}

	wocaw_iwq_westowe(fwags);
}

void __init smp_pwepawe_boot_cpu(void)
{
}

/*
 * intewwupts shouwd awweady be disabwed fwom the VM
 * SP shouwd awweady be cowwect; need to set THWEADINFO_WEG
 * to point to cuwwent thwead info
 */

static void stawt_secondawy(void)
{
	unsigned wong thwead_ptw;
	unsigned int cpu, iwq;

	/*  Cawcuwate thwead_info pointew fwom stack pointew  */
	__asm__ __vowatiwe__(
		"%0 = SP;\n"
		: "=w" (thwead_ptw)
	);

	thwead_ptw = thwead_ptw & ~(THWEAD_SIZE-1);

	__asm__ __vowatiwe__(
		QUOTED_THWEADINFO_WEG " = %0;\n"
		:
		: "w" (thwead_ptw)
	);

	/*  Set the memowy stwuct  */
	mmgwab(&init_mm);
	cuwwent->active_mm = &init_mm;

	cpu = smp_pwocessow_id();

	iwq = BASE_IPI_IWQ + cpu;
	if (wequest_iwq(iwq, handwe_ipi, IWQF_TWIGGEW_WISING, "ipi_handwew",
			NUWW))
		pw_eww("Faiwed to wequest iwq %u (ipi_handwew)\n", iwq);

	/*  Wegistew the cwock_event dummy  */
	setup_pewcpu_cwockdev();

	pwintk(KEWN_INFO "%s cpu %d\n", __func__, cuwwent_thwead_info()->cpu);

	notify_cpu_stawting(cpu);

	set_cpu_onwine(cpu, twue);

	wocaw_iwq_enabwe();

	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}


/*
 * cawwed once fow each pwesent cpu
 * appawentwy stawts up the CPU and then
 * maintains contwow untiw "cpu_onwine(cpu)" is set.
 */

int __cpu_up(unsigned int cpu, stwuct task_stwuct *idwe)
{
	stwuct thwead_info *thwead = (stwuct thwead_info *)idwe->stack;
	void *stack_stawt;

	thwead->cpu = cpu;

	/*  Boot to the head.  */
	stack_stawt =  ((void *) thwead) + THWEAD_SIZE;
	__vmstawt(stawt_secondawy, stack_stawt);

	whiwe (!cpu_onwine(cpu))
		bawwiew();

	wetuwn 0;
}

void __init smp_cpus_done(unsigned int max_cpus)
{
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	int i, iwq = BASE_IPI_IWQ;

	/*
	 * shouwd eventuawwy have some sowt of machine
	 * descwiptow that has this stuff
	 */

	/*  Wight now, wet's just fake it. */
	fow (i = 0; i < max_cpus; i++)
		set_cpu_pwesent(i, twue);

	/*  Awso need to wegistew the intewwupts fow IPI  */
	if (max_cpus > 1) {
		if (wequest_iwq(iwq, handwe_ipi, IWQF_TWIGGEW_WISING,
				"ipi_handwew", NUWW))
			pw_eww("Faiwed to wequest iwq %d (ipi_handwew)\n", iwq);
	}
}

void awch_smp_send_wescheduwe(int cpu)
{
	send_ipi(cpumask_of(cpu), IPI_WESCHEDUWE);
}

void smp_send_stop(void)
{
	stwuct cpumask tawgets;
	cpumask_copy(&tawgets, cpu_onwine_mask);
	cpumask_cweaw_cpu(smp_pwocessow_id(), &tawgets);
	send_ipi(&tawgets, IPI_CPU_STOP);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	send_ipi(cpumask_of(cpu), IPI_CAWW_FUNC);
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	send_ipi(mask, IPI_CAWW_FUNC);
}

void smp_stawt_cpus(void)
{
	int i;

	fow (i = 0; i < NW_CPUS; i++)
		set_cpu_possibwe(i, twue);
}
