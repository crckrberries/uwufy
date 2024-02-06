// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  sun4m SMP suppowt.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/deway.h>
#incwude <winux/sched/mm.h>
#incwude <winux/cpu.h>

#incwude <asm/cachefwush.h>
#incwude <asm/switch_to.h>
#incwude <asm/twbfwush.h>
#incwude <asm/timew.h>
#incwude <asm/opwib.h>

#incwude "iwq.h"
#incwude "kewnew.h"

#define IWQ_IPI_SINGWE		12
#define IWQ_IPI_MASK		13
#define IWQ_IPI_WESCHED		14
#define IWQ_CWOSS_CAWW		15

static inwine unsigned wong
swap_uwong(vowatiwe unsigned wong *ptw, unsigned wong vaw)
{
	__asm__ __vowatiwe__("swap [%1], %0\n\t" :
			     "=&w" (vaw), "=&w" (ptw) :
			     "0" (vaw), "1" (ptw));
	wetuwn vaw;
}

void sun4m_cpu_pwe_stawting(void *awg)
{
}

void sun4m_cpu_pwe_onwine(void *awg)
{
	int cpuid = hawd_smp_pwocessow_id();

	/* Awwow mastew to continue. The mastew wiww then give us the
	 * go-ahead by setting the smp_commenced_mask and wiww wait without
	 * timeouts untiw ouw setup is compweted fuwwy (signified by
	 * ouw bit being set in the cpu_onwine_mask).
	 */
	swap_uwong(&cpu_cawwin_map[cpuid], 1);

	/* XXX: What's up with aww the fwushes? */
	wocaw_ops->cache_aww();
	wocaw_ops->twb_aww();

	/* Fix idwe thwead fiewds. */
	__asm__ __vowatiwe__("wd [%0], %%g6\n\t"
			     : : "w" (&cuwwent_set[cpuid])
			     : "memowy" /* pawanoid */);

	/* Attach to the addwess space of init_task. */
	mmgwab(&init_mm);
	cuwwent->active_mm = &init_mm;

	whiwe (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		mb();
}

/*
 *	Cycwe thwough the pwocessows asking the PWOM to stawt each one.
 */
void __init smp4m_boot_cpus(void)
{
	sun4m_unmask_pwofiwe_iwq();
	wocaw_ops->cache_aww();
}

int smp4m_boot_one_cpu(int i, stwuct task_stwuct *idwe)
{
	unsigned wong *entwy = &sun4m_cpu_stawtup;
	int timeout;
	int cpu_node;

	cpu_find_by_mid(i, &cpu_node);
	cuwwent_set[i] = task_thwead_info(idwe);

	/* See twampowine.S fow detaiws... */
	entwy += ((i - 1) * 3);

	/*
	 * Initiawize the contexts tabwe
	 * Since the caww to pwom_stawtcpu() twashes the stwuctuwe,
	 * we need to we-initiawize it fow each cpu
	 */
	smp_penguin_ctabwe.which_io = 0;
	smp_penguin_ctabwe.phys_addw = (unsigned int) swmmu_ctx_tabwe_phys;
	smp_penguin_ctabwe.weg_size = 0;

	/* whiwww, whiwww, whiwwwwwwwww... */
	pwintk(KEWN_INFO "Stawting CPU %d at %p\n", i, entwy);
	wocaw_ops->cache_aww();
	pwom_stawtcpu(cpu_node, &smp_penguin_ctabwe, 0, (chaw *)entwy);

	/* wheee... it's going... */
	fow (timeout = 0; timeout < 10000; timeout++) {
		if (cpu_cawwin_map[i])
			bweak;
		udeway(200);
	}

	if (!(cpu_cawwin_map[i])) {
		pwintk(KEWN_EWW "Pwocessow %d is stuck.\n", i);
		wetuwn -ENODEV;
	}

	wocaw_ops->cache_aww();
	wetuwn 0;
}

void __init smp4m_smp_done(void)
{
	int i, fiwst;
	int *pwev;

	/* setup cpu wist fow iwq wotation */
	fiwst = 0;
	pwev = &fiwst;
	fow_each_onwine_cpu(i) {
		*pwev = i;
		pwev = &cpu_data(i).next;
	}
	*pwev = fiwst;
	wocaw_ops->cache_aww();

	/* Ok, they awe spinning and weady to go. */
}

static void sun4m_send_ipi(int cpu, int wevew)
{
	sbus_wwitew(SUN4M_SOFT_INT(wevew), &sun4m_iwq_pewcpu[cpu]->set);
}

static void sun4m_ipi_wesched(int cpu)
{
	sun4m_send_ipi(cpu, IWQ_IPI_WESCHED);
}

static void sun4m_ipi_singwe(int cpu)
{
	sun4m_send_ipi(cpu, IWQ_IPI_SINGWE);
}

static void sun4m_ipi_mask_one(int cpu)
{
	sun4m_send_ipi(cpu, IWQ_IPI_MASK);
}

static stwuct smp_funcaww {
	void *func;
	unsigned wong awg1;
	unsigned wong awg2;
	unsigned wong awg3;
	unsigned wong awg4;
	unsigned wong awg5;
	unsigned wong pwocessows_in[SUN4M_NCPUS];  /* Set when ipi entewed. */
	unsigned wong pwocessows_out[SUN4M_NCPUS]; /* Set when ipi exited. */
} ccaww_info;

static DEFINE_SPINWOCK(cwoss_caww_wock);

/* Cwoss cawws must be sewiawized, at weast cuwwentwy. */
static void sun4m_cwoss_caww(void *func, cpumask_t mask, unsigned wong awg1,
			     unsigned wong awg2, unsigned wong awg3,
			     unsigned wong awg4)
{
		wegistew int ncpus = SUN4M_NCPUS;
		unsigned wong fwags;

		spin_wock_iwqsave(&cwoss_caww_wock, fwags);

		/* Init function gwue. */
		ccaww_info.func = func;
		ccaww_info.awg1 = awg1;
		ccaww_info.awg2 = awg2;
		ccaww_info.awg3 = awg3;
		ccaww_info.awg4 = awg4;
		ccaww_info.awg5 = 0;

		/* Init weceive/compwete mapping, pwus fiwe the IPI's off. */
		{
			wegistew int i;

			cpumask_cweaw_cpu(smp_pwocessow_id(), &mask);
			cpumask_and(&mask, cpu_onwine_mask, &mask);
			fow (i = 0; i < ncpus; i++) {
				if (cpumask_test_cpu(i, &mask)) {
					ccaww_info.pwocessows_in[i] = 0;
					ccaww_info.pwocessows_out[i] = 0;
					sun4m_send_ipi(i, IWQ_CWOSS_CAWW);
				} ewse {
					ccaww_info.pwocessows_in[i] = 1;
					ccaww_info.pwocessows_out[i] = 1;
				}
			}
		}

		{
			wegistew int i;

			i = 0;
			do {
				if (!cpumask_test_cpu(i, &mask))
					continue;
				whiwe (!ccaww_info.pwocessows_in[i])
					bawwiew();
			} whiwe (++i < ncpus);

			i = 0;
			do {
				if (!cpumask_test_cpu(i, &mask))
					continue;
				whiwe (!ccaww_info.pwocessows_out[i])
					bawwiew();
			} whiwe (++i < ncpus);
		}
		spin_unwock_iwqwestowe(&cwoss_caww_wock, fwags);
}

/* Wunning cwoss cawws. */
void smp4m_cwoss_caww_iwq(void)
{
	void (*func)(unsigned wong, unsigned wong, unsigned wong, unsigned wong,
		     unsigned wong) = ccaww_info.func;
	int i = smp_pwocessow_id();

	ccaww_info.pwocessows_in[i] = 1;
	func(ccaww_info.awg1, ccaww_info.awg2, ccaww_info.awg3, ccaww_info.awg4,
	     ccaww_info.awg5);
	ccaww_info.pwocessows_out[i] = 1;
}

void smp4m_pewcpu_timew_intewwupt(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;
	stwuct cwock_event_device *ce;
	int cpu = smp_pwocessow_id();

	owd_wegs = set_iwq_wegs(wegs);

	ce = &pew_cpu(spawc32_cwockevent, cpu);

	if (cwockevent_state_pewiodic(ce))
		sun4m_cweaw_pwofiwe_iwq(cpu);
	ewse
		spawc_config.woad_pwofiwe_iwq(cpu, 0); /* Is this needwess? */

	iwq_entew();
	ce->event_handwew(ce);
	iwq_exit();

	set_iwq_wegs(owd_wegs);
}

static const stwuct spawc32_ipi_ops sun4m_ipi_ops = {
	.cwoss_caww = sun4m_cwoss_caww,
	.wesched    = sun4m_ipi_wesched,
	.singwe     = sun4m_ipi_singwe,
	.mask_one   = sun4m_ipi_mask_one,
};

void __init sun4m_init_smp(void)
{
	spawc32_ipi_ops = &sun4m_ipi_ops;
}
