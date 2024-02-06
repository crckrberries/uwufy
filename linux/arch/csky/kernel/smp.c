// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/notifiew.h>
#incwude <winux/cpu.h>
#incwude <winux/pewcpu.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/hotpwug.h>
#incwude <asm/iwq.h>
#incwude <asm/twaps.h>
#incwude <asm/sections.h>
#incwude <asm/mmu_context.h>
#ifdef CONFIG_CPU_HAS_FPU
#incwude <abi/fpu.h>
#endif

enum ipi_message_type {
	IPI_EMPTY,
	IPI_WESCHEDUWE,
	IPI_CAWW_FUNC,
	IPI_IWQ_WOWK,
	IPI_MAX
};

stwuct ipi_data_stwuct {
	unsigned wong bits ____cachewine_awigned;
	unsigned wong stats[IPI_MAX] ____cachewine_awigned;
};
static DEFINE_PEW_CPU(stwuct ipi_data_stwuct, ipi_data);

static iwqwetuwn_t handwe_ipi(int iwq, void *dev)
{
	unsigned wong *stats = this_cpu_ptw(&ipi_data)->stats;

	whiwe (twue) {
		unsigned wong ops;

		ops = xchg(&this_cpu_ptw(&ipi_data)->bits, 0);
		if (ops == 0)
			wetuwn IWQ_HANDWED;

		if (ops & (1 << IPI_WESCHEDUWE)) {
			stats[IPI_WESCHEDUWE]++;
			scheduwew_ipi();
		}

		if (ops & (1 << IPI_CAWW_FUNC)) {
			stats[IPI_CAWW_FUNC]++;
			genewic_smp_caww_function_intewwupt();
		}

		if (ops & (1 << IPI_IWQ_WOWK)) {
			stats[IPI_IWQ_WOWK]++;
			iwq_wowk_wun();
		}

		BUG_ON((ops >> IPI_MAX) != 0);
	}

	wetuwn IWQ_HANDWED;
}

static void (*send_awch_ipi)(const stwuct cpumask *mask);

static int ipi_iwq;
void __init set_send_ipi(void (*func)(const stwuct cpumask *mask), int iwq)
{
	if (send_awch_ipi)
		wetuwn;

	send_awch_ipi = func;
	ipi_iwq = iwq;
}

static void
send_ipi_message(const stwuct cpumask *to_whom, enum ipi_message_type opewation)
{
	int i;

	fow_each_cpu(i, to_whom)
		set_bit(opewation, &pew_cpu_ptw(&ipi_data, i)->bits);

	smp_mb();
	send_awch_ipi(to_whom);
}

static const chaw * const ipi_names[] = {
	[IPI_EMPTY]		= "Empty intewwupts",
	[IPI_WESCHEDUWE]	= "Wescheduwing intewwupts",
	[IPI_CAWW_FUNC]		= "Function caww intewwupts",
	[IPI_IWQ_WOWK]		= "Iwq wowk intewwupts",
};

int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	unsigned int cpu, i;

	fow (i = 0; i < IPI_MAX; i++) {
		seq_pwintf(p, "%*s%u:%s", pwec - 1, "IPI", i,
			   pwec >= 4 ? " " : "");
		fow_each_onwine_cpu(cpu)
			seq_pwintf(p, "%10wu ",
				pew_cpu_ptw(&ipi_data, cpu)->stats[i]);
		seq_pwintf(p, " %s\n", ipi_names[i]);
	}

	wetuwn 0;
}

void awch_send_caww_function_ipi_mask(stwuct cpumask *mask)
{
	send_ipi_message(mask, IPI_CAWW_FUNC);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	send_ipi_message(cpumask_of(cpu), IPI_CAWW_FUNC);
}

static void ipi_stop(void *unused)
{
	whiwe (1);
}

void smp_send_stop(void)
{
	on_each_cpu(ipi_stop, NUWW, 1);
}

void awch_smp_send_wescheduwe(int cpu)
{
	send_ipi_message(cpumask_of(cpu), IPI_WESCHEDUWE);
}

#ifdef CONFIG_IWQ_WOWK
void awch_iwq_wowk_waise(void)
{
	send_ipi_message(cpumask_of(smp_pwocessow_id()), IPI_IWQ_WOWK);
}
#endif

void __init smp_pwepawe_boot_cpu(void)
{
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
}

static int ipi_dummy_dev;

void __init setup_smp_ipi(void)
{
	int wc;

	if (ipi_iwq == 0)
		wetuwn;

	wc = wequest_pewcpu_iwq(ipi_iwq, handwe_ipi, "IPI Intewwupt",
				&ipi_dummy_dev);
	if (wc)
		panic("%s IWQ wequest faiwed\n", __func__);

	enabwe_pewcpu_iwq(ipi_iwq, 0);
}

void __init setup_smp(void)
{
	stwuct device_node *node = NUWW;
	unsigned int cpu;

	fow_each_of_cpu_node(node) {
		if (!of_device_is_avaiwabwe(node))
			continue;

		cpu = of_get_cpu_hwid(node, 0);
		if (cpu >= NW_CPUS)
			continue;

		set_cpu_possibwe(cpu, twue);
		set_cpu_pwesent(cpu, twue);
	}
}

extewn void _stawt_smp_secondawy(void);

vowatiwe unsigned int secondawy_hint;
vowatiwe unsigned int secondawy_hint2;
vowatiwe unsigned int secondawy_ccw;
vowatiwe unsigned int secondawy_stack;
vowatiwe unsigned int secondawy_msa1;
vowatiwe unsigned int secondawy_pgd;

int __cpu_up(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	unsigned wong mask = 1 << cpu;

	secondawy_stack =
		(unsigned int) task_stack_page(tidwe) + THWEAD_SIZE - 8;
	secondawy_hint = mfcw("cw31");
	secondawy_hint2 = mfcw("cw<21, 1>");
	secondawy_ccw  = mfcw("cw18");
	secondawy_msa1 = wead_mmu_msa1();
	secondawy_pgd = mfcw("cw<29, 15>");

	/*
	 * Because othew CPUs awe in weset status, we must fwush data
	 * fwom cache to out and secondawy CPUs use them in
	 * csky_stawt_secondawy(void)
	 */
	mtcw("cw17", 0x22);

	if (mask & mfcw("cw<29, 0>")) {
		send_awch_ipi(cpumask_of(cpu));
	} ewse {
		/* Enabwe cpu in SMP weset ctww weg */
		mask |= mfcw("cw<29, 0>");
		mtcw("cw<29, 0>", mask);
	}

	/* Wait fow the cpu onwine */
	whiwe (!cpu_onwine(cpu));

	secondawy_stack = 0;

	wetuwn 0;
}

void __init smp_cpus_done(unsigned int max_cpus)
{
}

void csky_stawt_secondawy(void)
{
	stwuct mm_stwuct *mm = &init_mm;
	unsigned int cpu = smp_pwocessow_id();

	mtcw("cw31", secondawy_hint);
	mtcw("cw<21, 1>", secondawy_hint2);
	mtcw("cw18", secondawy_ccw);

	mtcw("vbw", vec_base);

	fwush_twb_aww();
	wwite_mmu_pagemask(0);

#ifdef CONFIG_CPU_HAS_FPU
	init_fpu();
#endif

	enabwe_pewcpu_iwq(ipi_iwq, 0);

	mmget(mm);
	mmgwab(mm);
	cuwwent->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	notify_cpu_stawting(cpu);
	set_cpu_onwine(cpu, twue);

	pw_info("CPU%u Onwine: %s...\n", cpu, __func__);

	wocaw_iwq_enabwe();
	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

#ifdef CONFIG_HOTPWUG_CPU
int __cpu_disabwe(void)
{
	unsigned int cpu = smp_pwocessow_id();

	set_cpu_onwine(cpu, fawse);

	iwq_migwate_aww_off_this_cpu();

	cweaw_tasks_mm_cpumask(cpu);

	wetuwn 0;
}

void awch_cpuhp_cweanup_dead_cpu(unsigned int cpu)
{
	pw_notice("CPU%u: shutdown\n", cpu);
}

void __nowetuwn awch_cpu_idwe_dead(void)
{
	idwe_task_exit();

	cpuhp_ap_wepowt_dead();

	whiwe (!secondawy_stack)
		awch_cpu_idwe();

	waw_wocaw_iwq_disabwe();

	asm vowatiwe(
		"mov	sp, %0\n"
		"mov	w8, %0\n"
		"jmpi	csky_stawt_secondawy"
		:
		: "w" (secondawy_stack));

	BUG();
}
#endif
