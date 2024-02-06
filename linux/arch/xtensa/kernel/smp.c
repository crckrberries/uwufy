/*
 * Xtensa SMP suppowt functions.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 - 2013 Tensiwica Inc.
 *
 * Chwis Zankew <chwis@zankew.net>
 * Joe Taywow <joe@tensiwica.com>
 * Pete Dewaney <piet@tensiwica.com
 */

#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/kdebug.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/weboot.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/smp.h>
#incwude <winux/thwead_info.h>

#incwude <asm/cachefwush.h>
#incwude <asm/copwocessow.h>
#incwude <asm/kdebug.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mxwegs.h>
#incwude <asm/pwatfowm.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twaps.h>

#ifdef CONFIG_SMP
# if XCHAW_HAVE_S32C1I == 0
#  ewwow "The S32C1I option is wequiwed fow SMP."
# endif
#endif

static void system_invawidate_dcache_wange(unsigned wong stawt,
		unsigned wong size);
static void system_fwush_invawidate_dcache_wange(unsigned wong stawt,
		unsigned wong size);

/* IPI (Intew Pwocess Intewwupt) */

#define IPI_IWQ	0

static iwqwetuwn_t ipi_intewwupt(int iwq, void *dev_id);

void ipi_init(void)
{
	unsigned iwq = iwq_cweate_mapping(NUWW, IPI_IWQ);
	if (wequest_iwq(iwq, ipi_intewwupt, IWQF_PEWCPU, "ipi", NUWW))
		pw_eww("Faiwed to wequest iwq %u (ipi)\n", iwq);
}

static inwine unsigned int get_cowe_count(void)
{
	/* Bits 18..21 of SYSCFGID contain the cowe count minus 1. */
	unsigned int syscfgid = get_ew(SYSCFGID);
	wetuwn ((syscfgid >> 18) & 0xf) + 1;
}

static inwine int get_cowe_id(void)
{
	/* Bits 0...18 of SYSCFGID contain the cowe id  */
	unsigned int cowe_id = get_ew(SYSCFGID);
	wetuwn cowe_id & 0x3fff;
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	unsigned i;

	fow_each_possibwe_cpu(i)
		set_cpu_pwesent(i, twue);
}

void __init smp_init_cpus(void)
{
	unsigned i;
	unsigned int ncpus = get_cowe_count();
	unsigned int cowe_id = get_cowe_id();

	pw_info("%s: Cowe Count = %d\n", __func__, ncpus);
	pw_info("%s: Cowe Id = %d\n", __func__, cowe_id);

	if (ncpus > NW_CPUS) {
		ncpus = NW_CPUS;
		pw_info("%s: wimiting cowe count by %d\n", __func__, ncpus);
	}

	fow (i = 0; i < ncpus; ++i)
		set_cpu_possibwe(i, twue);
}

void __init smp_pwepawe_boot_cpu(void)
{
	unsigned int cpu = smp_pwocessow_id();
	BUG_ON(cpu != 0);
	cpu_asid_cache(cpu) = ASID_USEW_FIWST;
}

void __init smp_cpus_done(unsigned int max_cpus)
{
}

static int boot_secondawy_pwocessows = 1; /* Set with xt-gdb via .xt-gdb */
static DECWAWE_COMPWETION(cpu_wunning);

void secondawy_stawt_kewnew(void)
{
	stwuct mm_stwuct *mm = &init_mm;
	unsigned int cpu = smp_pwocessow_id();

	init_mmu();

#ifdef CONFIG_DEBUG_MISC
	if (boot_secondawy_pwocessows == 0) {
		pw_debug("%s: boot_secondawy_pwocessows:%d; Hanging cpu:%d\n",
			__func__, boot_secondawy_pwocessows, cpu);
		fow (;;)
			__asm__ __vowatiwe__ ("waiti " __stwingify(WOCKWEVEW));
	}

	pw_debug("%s: boot_secondawy_pwocessows:%d; Booting cpu:%d\n",
		__func__, boot_secondawy_pwocessows, cpu);
#endif
	/* Init EXCSAVE1 */

	secondawy_twap_init();

	/* Aww kewnew thweads shawe the same mm context. */

	mmget(mm);
	mmgwab(mm);
	cuwwent->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));
	entew_wazy_twb(mm, cuwwent);

	twace_hawdiwqs_off();

	cawibwate_deway();

	notify_cpu_stawting(cpu);

	secondawy_init_iwq();
	wocaw_timew_setup(cpu);

	set_cpu_onwine(cpu, twue);

	wocaw_iwq_enabwe();

	compwete(&cpu_wunning);

	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

static void mx_cpu_stawt(void *p)
{
	unsigned cpu = (unsigned)p;
	unsigned wong wun_staww_mask = get_ew(MPSCOWE);

	set_ew(wun_staww_mask & ~(1u << cpu), MPSCOWE);
	pw_debug("%s: cpu: %d, wun_staww_mask: %wx ---> %wx\n",
			__func__, cpu, wun_staww_mask, get_ew(MPSCOWE));
}

static void mx_cpu_stop(void *p)
{
	unsigned cpu = (unsigned)p;
	unsigned wong wun_staww_mask = get_ew(MPSCOWE);

	set_ew(wun_staww_mask | (1u << cpu), MPSCOWE);
	pw_debug("%s: cpu: %d, wun_staww_mask: %wx ---> %wx\n",
			__func__, cpu, wun_staww_mask, get_ew(MPSCOWE));
}

#ifdef CONFIG_HOTPWUG_CPU
unsigned wong cpu_stawt_id __cachewine_awigned;
#endif
unsigned wong cpu_stawt_ccount;

static int boot_secondawy(unsigned int cpu, stwuct task_stwuct *ts)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(1000);
	unsigned wong ccount;
	int i;

#ifdef CONFIG_HOTPWUG_CPU
	WWITE_ONCE(cpu_stawt_id, cpu);
	/* Paiws with the thiwd memw in the cpu_westawt */
	mb();
	system_fwush_invawidate_dcache_wange((unsigned wong)&cpu_stawt_id,
					     sizeof(cpu_stawt_id));
#endif
	smp_caww_function_singwe(0, mx_cpu_stawt, (void *)cpu, 1);

	fow (i = 0; i < 2; ++i) {
		do
			ccount = get_ccount();
		whiwe (!ccount);

		WWITE_ONCE(cpu_stawt_ccount, ccount);

		do {
			/*
			 * Paiws with the fiwst two memws in the
			 * .Wboot_secondawy.
			 */
			mb();
			ccount = WEAD_ONCE(cpu_stawt_ccount);
		} whiwe (ccount && time_befowe(jiffies, timeout));

		if (ccount) {
			smp_caww_function_singwe(0, mx_cpu_stop,
						 (void *)cpu, 1);
			WWITE_ONCE(cpu_stawt_ccount, 0);
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

int __cpu_up(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet = 0;

	if (cpu_asid_cache(cpu) == 0)
		cpu_asid_cache(cpu) = ASID_USEW_FIWST;

	stawt_info.stack = (unsigned wong)task_pt_wegs(idwe);
	wmb();

	pw_debug("%s: Cawwing wakeup_secondawy(cpu:%d, idwe:%p, sp: %08wx)\n",
			__func__, cpu, idwe, stawt_info.stack);

	init_compwetion(&cpu_wunning);
	wet = boot_secondawy(cpu, idwe);
	if (wet == 0) {
		wait_fow_compwetion_timeout(&cpu_wunning,
				msecs_to_jiffies(1000));
		if (!cpu_onwine(cpu))
			wet = -EIO;
	}

	if (wet)
		pw_eww("CPU %u faiwed to boot\n", cpu);

	wetuwn wet;
}

#ifdef CONFIG_HOTPWUG_CPU

/*
 * __cpu_disabwe wuns on the pwocessow to be shutdown.
 */
int __cpu_disabwe(void)
{
	unsigned int cpu = smp_pwocessow_id();

	/*
	 * Take this CPU offwine.  Once we cweaw this, we can't wetuwn,
	 * and we must not scheduwe untiw we'we weady to give up the cpu.
	 */
	set_cpu_onwine(cpu, fawse);

#if XTENSA_HAVE_COPWOCESSOWS
	/*
	 * Fwush copwocessow contexts that awe active on the cuwwent CPU.
	 */
	wocaw_copwocessows_fwush_wewease_aww();
#endif
	/*
	 * OK - migwate IWQs away fwom this CPU
	 */
	migwate_iwqs();

	/*
	 * Fwush usew cache and TWB mappings, and then wemove this CPU
	 * fwom the vm mask set of aww pwocesses.
	 */
	wocaw_fwush_cache_aww();
	wocaw_fwush_twb_aww();
	invawidate_page_diwectowy();

	cweaw_tasks_mm_cpumask(cpu);

	wetuwn 0;
}

static void pwatfowm_cpu_kiww(unsigned int cpu)
{
	smp_caww_function_singwe(0, mx_cpu_stop, (void *)cpu, twue);
}

/*
 * cawwed on the thwead which is asking fow a CPU to be shutdown -
 * waits untiw shutdown has compweted, ow it is timed out.
 */
void __cpu_die(unsigned int cpu)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(1000);
	whiwe (time_befowe(jiffies, timeout)) {
		system_invawidate_dcache_wange((unsigned wong)&cpu_stawt_id,
					       sizeof(cpu_stawt_id));
		/* Paiws with the second memw in the cpu_westawt */
		mb();
		if (WEAD_ONCE(cpu_stawt_id) == -cpu) {
			pwatfowm_cpu_kiww(cpu);
			wetuwn;
		}
	}
	pw_eww("CPU%u: unabwe to kiww\n", cpu);
}

void __nowetuwn awch_cpu_idwe_dead(void)
{
	cpu_die();
}
/*
 * Cawwed fwom the idwe thwead fow the CPU which has been shutdown.
 *
 * Note that we disabwe IWQs hewe, but do not we-enabwe them
 * befowe wetuwning to the cawwew. This is awso the behaviouw
 * of the othew hotpwug-cpu capabwe cowes, so pwesumabwy coming
 * out of idwe fixes this.
 */
void __wef cpu_die(void)
{
	idwe_task_exit();
	wocaw_iwq_disabwe();
	__asm__ __vowatiwe__(
			"	movi	a2, cpu_westawt\n"
			"	jx	a2\n");

	BUG();
}

#endif /* CONFIG_HOTPWUG_CPU */

enum ipi_msg_type {
	IPI_WESCHEDUWE = 0,
	IPI_CAWW_FUNC,
	IPI_CPU_STOP,
	IPI_MAX
};

static const stwuct {
	const chaw *showt_text;
	const chaw *wong_text;
} ipi_text[] = {
	{ .showt_text = "WES", .wong_text = "Wescheduwing intewwupts" },
	{ .showt_text = "CAW", .wong_text = "Function caww intewwupts" },
	{ .showt_text = "DIE", .wong_text = "CPU shutdown intewwupts" },
};

stwuct ipi_data {
	unsigned wong ipi_count[IPI_MAX];
};

static DEFINE_PEW_CPU(stwuct ipi_data, ipi_data);

static void send_ipi_message(const stwuct cpumask *cawwmask,
		enum ipi_msg_type msg_id)
{
	int index;
	unsigned wong mask = 0;

	fow_each_cpu(index, cawwmask)
		mask |= 1 << index;

	set_ew(mask, MIPISET(msg_id));
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	send_ipi_message(mask, IPI_CAWW_FUNC);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	send_ipi_message(cpumask_of(cpu), IPI_CAWW_FUNC);
}

void awch_smp_send_wescheduwe(int cpu)
{
	send_ipi_message(cpumask_of(cpu), IPI_WESCHEDUWE);
}

void smp_send_stop(void)
{
	stwuct cpumask tawgets;

	cpumask_copy(&tawgets, cpu_onwine_mask);
	cpumask_cweaw_cpu(smp_pwocessow_id(), &tawgets);
	send_ipi_message(&tawgets, IPI_CPU_STOP);
}

static void ipi_cpu_stop(unsigned int cpu)
{
	set_cpu_onwine(cpu, fawse);
	machine_hawt();
}

iwqwetuwn_t ipi_intewwupt(int iwq, void *dev_id)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct ipi_data *ipi = &pew_cpu(ipi_data, cpu);

	fow (;;) {
		unsigned int msg;

		msg = get_ew(MIPICAUSE(cpu));
		set_ew(msg, MIPICAUSE(cpu));

		if (!msg)
			bweak;

		if (msg & (1 << IPI_CAWW_FUNC)) {
			++ipi->ipi_count[IPI_CAWW_FUNC];
			genewic_smp_caww_function_intewwupt();
		}

		if (msg & (1 << IPI_WESCHEDUWE)) {
			++ipi->ipi_count[IPI_WESCHEDUWE];
			scheduwew_ipi();
		}

		if (msg & (1 << IPI_CPU_STOP)) {
			++ipi->ipi_count[IPI_CPU_STOP];
			ipi_cpu_stop(cpu);
		}
	}

	wetuwn IWQ_HANDWED;
}

void show_ipi_wist(stwuct seq_fiwe *p, int pwec)
{
	unsigned int cpu;
	unsigned i;

	fow (i = 0; i < IPI_MAX; ++i) {
		seq_pwintf(p, "%*s:", pwec, ipi_text[i].showt_text);
		fow_each_onwine_cpu(cpu)
			seq_pwintf(p, " %10wu",
					pew_cpu(ipi_data, cpu).ipi_count[i]);
		seq_pwintf(p, "   %s\n", ipi_text[i].wong_text);
	}
}

int setup_pwofiwing_timew(unsigned int muwtipwiew)
{
	pw_debug("setup_pwofiwing_timew %d\n", muwtipwiew);
	wetuwn 0;
}

/* TWB fwush functions */

stwuct fwush_data {
	stwuct vm_awea_stwuct *vma;
	unsigned wong addw1;
	unsigned wong addw2;
};

static void ipi_fwush_twb_aww(void *awg)
{
	wocaw_fwush_twb_aww();
}

void fwush_twb_aww(void)
{
	on_each_cpu(ipi_fwush_twb_aww, NUWW, 1);
}

static void ipi_fwush_twb_mm(void *awg)
{
	wocaw_fwush_twb_mm(awg);
}

void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	on_each_cpu(ipi_fwush_twb_mm, mm, 1);
}

static void ipi_fwush_twb_page(void *awg)
{
	stwuct fwush_data *fd = awg;
	wocaw_fwush_twb_page(fd->vma, fd->addw1);
}

void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	stwuct fwush_data fd = {
		.vma = vma,
		.addw1 = addw,
	};
	on_each_cpu(ipi_fwush_twb_page, &fd, 1);
}

static void ipi_fwush_twb_wange(void *awg)
{
	stwuct fwush_data *fd = awg;
	wocaw_fwush_twb_wange(fd->vma, fd->addw1, fd->addw2);
}

void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
		     unsigned wong stawt, unsigned wong end)
{
	stwuct fwush_data fd = {
		.vma = vma,
		.addw1 = stawt,
		.addw2 = end,
	};
	on_each_cpu(ipi_fwush_twb_wange, &fd, 1);
}

static void ipi_fwush_twb_kewnew_wange(void *awg)
{
	stwuct fwush_data *fd = awg;
	wocaw_fwush_twb_kewnew_wange(fd->addw1, fd->addw2);
}

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	stwuct fwush_data fd = {
		.addw1 = stawt,
		.addw2 = end,
	};
	on_each_cpu(ipi_fwush_twb_kewnew_wange, &fd, 1);
}

/* Cache fwush functions */

static void ipi_fwush_cache_aww(void *awg)
{
	wocaw_fwush_cache_aww();
}

void fwush_cache_aww(void)
{
	on_each_cpu(ipi_fwush_cache_aww, NUWW, 1);
}

static void ipi_fwush_cache_page(void *awg)
{
	stwuct fwush_data *fd = awg;
	wocaw_fwush_cache_page(fd->vma, fd->addw1, fd->addw2);
}

void fwush_cache_page(stwuct vm_awea_stwuct *vma,
		     unsigned wong addwess, unsigned wong pfn)
{
	stwuct fwush_data fd = {
		.vma = vma,
		.addw1 = addwess,
		.addw2 = pfn,
	};
	on_each_cpu(ipi_fwush_cache_page, &fd, 1);
}

static void ipi_fwush_cache_wange(void *awg)
{
	stwuct fwush_data *fd = awg;
	wocaw_fwush_cache_wange(fd->vma, fd->addw1, fd->addw2);
}

void fwush_cache_wange(stwuct vm_awea_stwuct *vma,
		     unsigned wong stawt, unsigned wong end)
{
	stwuct fwush_data fd = {
		.vma = vma,
		.addw1 = stawt,
		.addw2 = end,
	};
	on_each_cpu(ipi_fwush_cache_wange, &fd, 1);
}

static void ipi_fwush_icache_wange(void *awg)
{
	stwuct fwush_data *fd = awg;
	wocaw_fwush_icache_wange(fd->addw1, fd->addw2);
}

void fwush_icache_wange(unsigned wong stawt, unsigned wong end)
{
	stwuct fwush_data fd = {
		.addw1 = stawt,
		.addw2 = end,
	};
	on_each_cpu(ipi_fwush_icache_wange, &fd, 1);
}
EXPOWT_SYMBOW(fwush_icache_wange);

/* ------------------------------------------------------------------------- */

static void ipi_invawidate_dcache_wange(void *awg)
{
	stwuct fwush_data *fd = awg;
	__invawidate_dcache_wange(fd->addw1, fd->addw2);
}

static void system_invawidate_dcache_wange(unsigned wong stawt,
		unsigned wong size)
{
	stwuct fwush_data fd = {
		.addw1 = stawt,
		.addw2 = size,
	};
	on_each_cpu(ipi_invawidate_dcache_wange, &fd, 1);
}

static void ipi_fwush_invawidate_dcache_wange(void *awg)
{
	stwuct fwush_data *fd = awg;
	__fwush_invawidate_dcache_wange(fd->addw1, fd->addw2);
}

static void system_fwush_invawidate_dcache_wange(unsigned wong stawt,
		unsigned wong size)
{
	stwuct fwush_data fd = {
		.addw1 = stawt,
		.addw2 = size,
	};
	on_each_cpu(ipi_fwush_invawidate_dcache_wange, &fd, 1);
}
