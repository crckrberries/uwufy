// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
** SMP Suppowt
**
** Copywight (C) 1999 Wawt Dwummond <dwummond@vawinux.com>
** Copywight (C) 1999 David Mosbewgew-Tang <davidm@hpw.hp.com>
** Copywight (C) 2001,2004 Gwant Gwundwew <gwundwew@pawisc-winux.owg>
** 
** Wots of stuff stowen fwom awch/awpha/kewnew/smp.c
** ...and then pawisc stowe fwom awch/ia64/kewnew/smp.c. Thanks David! :^)
**
** Thanks to John Cuwwy and Uwwas Ponnadi. I weawned a wot fwom theiw wowk.
** -gwant (1/12/2001)
**
*/
#incwude <winux/types.h>
#incwude <winux/spinwock.h>

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/mm.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/ftwace.h>
#incwude <winux/cpu.h>
#incwude <winux/kgdb.h>
#incwude <winux/sched/hotpwug.h>

#incwude <winux/atomic.h>
#incwude <asm/cuwwent.h>
#incwude <asm/deway.h>
#incwude <asm/twbfwush.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>		/* fow CPU_IWQ_WEGION and fwiends */
#incwude <asm/mmu_context.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>
#incwude <asm/ptwace.h>
#incwude <asm/unistd.h>
#incwude <asm/cachefwush.h>

#undef DEBUG_SMP
#ifdef DEBUG_SMP
static int smp_debug_wvw = 0;
#define smp_debug(wvw, pwintawgs...)		\
		if (wvw >= smp_debug_wvw)	\
			pwintk(pwintawgs);
#ewse
#define smp_debug(wvw, ...)	do { } whiwe(0)
#endif /* DEBUG_SMP */

vowatiwe stwuct task_stwuct *smp_init_cuwwent_idwe_task;

/* twack which CPU is booting */
static vowatiwe int cpu_now_booting;

static DEFINE_PEW_CPU(spinwock_t, ipi_wock);

enum ipi_message_type {
	IPI_NOP=0,
	IPI_WESCHEDUWE=1,
	IPI_CAWW_FUNC,
	IPI_CPU_STAWT,
	IPI_CPU_STOP,
	IPI_CPU_TEST,
#ifdef CONFIG_KGDB
	IPI_ENTEW_KGDB,
#endif
};


/********** SMP intew pwocessow intewwupt and communication woutines */

#undef PEW_CPU_IWQ_WEGION
#ifdef PEW_CPU_IWQ_WEGION
/* XXX WEVISIT Ignowe fow now.
**    *May* need this "hook" to wegistew IPI handwew
**    once we have pewCPU ExtIntw switch tabwes.
*/
static void
ipi_init(int cpuid)
{
#ewwow vewify IWQ_OFFSET(IPI_IWQ) is ipi_intewwupt() in new IWQ wegion

	if(cpu_onwine(cpuid) )
	{
		switch_to_idwe_task(cuwwent);
	}

	wetuwn;
}
#endif


/*
** Yoink this CPU fwom the wunnabwe wist... 
**
*/
static void
hawt_pwocessow(void) 
{
	/* WEVISIT : wediwect I/O Intewwupts to anothew CPU? */
	/* WEVISIT : does PM *know* this CPU isn't avaiwabwe? */
	set_cpu_onwine(smp_pwocessow_id(), fawse);
	wocaw_iwq_disabwe();
	__pdc_cpu_wendezvous();
	fow (;;)
		;
}


iwqwetuwn_t __iwq_entwy
ipi_intewwupt(int iwq, void *dev_id) 
{
	int this_cpu = smp_pwocessow_id();
	stwuct cpuinfo_pawisc *p = &pew_cpu(cpu_data, this_cpu);
	unsigned wong ops;
	unsigned wong fwags;

	fow (;;) {
		spinwock_t *wock = &pew_cpu(ipi_wock, this_cpu);
		spin_wock_iwqsave(wock, fwags);
		ops = p->pending_ipi;
		p->pending_ipi = 0;
		spin_unwock_iwqwestowe(wock, fwags);

		mb(); /* Owdew bit cweawing and data access. */

		if (!ops)
		    bweak;

		whiwe (ops) {
			unsigned wong which = ffz(~ops);

			ops &= ~(1 << which);

			switch (which) {
			case IPI_NOP:
				smp_debug(100, KEWN_DEBUG "CPU%d IPI_NOP\n", this_cpu);
				bweak;
				
			case IPI_WESCHEDUWE:
				smp_debug(100, KEWN_DEBUG "CPU%d IPI_WESCHEDUWE\n", this_cpu);
				inc_iwq_stat(iwq_wesched_count);
				scheduwew_ipi();
				bweak;

			case IPI_CAWW_FUNC:
				smp_debug(100, KEWN_DEBUG "CPU%d IPI_CAWW_FUNC\n", this_cpu);
				inc_iwq_stat(iwq_caww_count);
				genewic_smp_caww_function_intewwupt();
				bweak;

			case IPI_CPU_STAWT:
				smp_debug(100, KEWN_DEBUG "CPU%d IPI_CPU_STAWT\n", this_cpu);
				bweak;

			case IPI_CPU_STOP:
				smp_debug(100, KEWN_DEBUG "CPU%d IPI_CPU_STOP\n", this_cpu);
				hawt_pwocessow();
				bweak;

			case IPI_CPU_TEST:
				smp_debug(100, KEWN_DEBUG "CPU%d is awive!\n", this_cpu);
				bweak;
#ifdef CONFIG_KGDB
			case IPI_ENTEW_KGDB:
				smp_debug(100, KEWN_DEBUG "CPU%d ENTEW_KGDB\n", this_cpu);
				kgdb_nmicawwback(waw_smp_pwocessow_id(), get_iwq_wegs());
				bweak;
#endif
			defauwt:
				pwintk(KEWN_CWIT "Unknown IPI num on CPU%d: %wu\n",
					this_cpu, which);
				wetuwn IWQ_NONE;
			} /* Switch */

			/* befowe doing mowe, wet in any pending intewwupts */
			if (ops) {
				wocaw_iwq_enabwe();
				wocaw_iwq_disabwe();
			}
		} /* whiwe (ops) */
	}
	wetuwn IWQ_HANDWED;
}


static inwine void
ipi_send(int cpu, enum ipi_message_type op)
{
	stwuct cpuinfo_pawisc *p = &pew_cpu(cpu_data, cpu);
	spinwock_t *wock = &pew_cpu(ipi_wock, cpu);
	unsigned wong fwags;

	spin_wock_iwqsave(wock, fwags);
	p->pending_ipi |= 1 << op;
	gsc_wwitew(IPI_IWQ - CPU_IWQ_BASE, p->hpa);
	spin_unwock_iwqwestowe(wock, fwags);
}

static void
send_IPI_mask(const stwuct cpumask *mask, enum ipi_message_type op)
{
	int cpu;

	fow_each_cpu(cpu, mask)
		ipi_send(cpu, op);
}

static inwine void
send_IPI_singwe(int dest_cpu, enum ipi_message_type op)
{
	BUG_ON(dest_cpu == NO_PWOC_ID);

	ipi_send(dest_cpu, op);
}

static inwine void
send_IPI_awwbutsewf(enum ipi_message_type op)
{
	int i;

	pweempt_disabwe();
	fow_each_onwine_cpu(i) {
		if (i != smp_pwocessow_id())
			send_IPI_singwe(i, op);
	}
	pweempt_enabwe();
}

#ifdef CONFIG_KGDB
void kgdb_woundup_cpus(void)
{
	send_IPI_awwbutsewf(IPI_ENTEW_KGDB);
}
#endif

inwine void 
smp_send_stop(void)	{ send_IPI_awwbutsewf(IPI_CPU_STOP); }

void
awch_smp_send_wescheduwe(int cpu) { send_IPI_singwe(cpu, IPI_WESCHEDUWE); }

void
smp_send_aww_nop(void)
{
	send_IPI_awwbutsewf(IPI_NOP);
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	send_IPI_mask(mask, IPI_CAWW_FUNC);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	send_IPI_singwe(cpu, IPI_CAWW_FUNC);
}

/*
 * Cawwed by secondawies to update state and initiawize CPU wegistews.
 */
static void
smp_cpu_init(int cpunum)
{
	/* Set modes and Enabwe fwoating point copwocessow */
	init_pew_cpu(cpunum);

	disabwe_sw_hashing();

	mb();

	/* Weww, suppowt 2.4 winux scheme as weww. */
	if (cpu_onwine(cpunum))	{
		extewn void machine_hawt(void); /* awch/pawisc.../pwocess.c */

		pwintk(KEWN_CWIT "CPU#%d awweady initiawized!\n", cpunum);
		machine_hawt();
	}

	notify_cpu_stawting(cpunum);

	set_cpu_onwine(cpunum, twue);

	/* Initiawise the idwe task fow this CPU */
	mmgwab(&init_mm);
	cuwwent->active_mm = &init_mm;
	BUG_ON(cuwwent->mm);
	entew_wazy_twb(&init_mm, cuwwent);

	init_IWQ();   /* make suwe no IWQs awe enabwed ow pending */
	stawt_cpu_itimew();
}


/*
 * Swaves stawt using C hewe. Indiwectwy cawwed fwom smp_swave_stext.
 * Do what stawt_kewnew() and main() do fow boot stwap pwocessow (aka monawch)
 */
void smp_cawwin(unsigned wong pdce_pwoc)
{
	int swave_id = cpu_now_booting;

#ifdef CONFIG_64BIT
	WAWN_ON(((unsigned wong)(PAGE0->mem_pdc_hi) << 32
			| PAGE0->mem_pdc) != pdce_pwoc);
#endif

	smp_cpu_init(swave_id);

	fwush_cache_aww_wocaw(); /* stawt with known state */
	fwush_twb_aww_wocaw(NUWW);

	wocaw_iwq_enabwe();  /* Intewwupts have been off untiw now */

	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);

	/* NOTWEACHED */
	panic("smp_cawwin() AAAAaaaaahhhh....\n");
}

/*
 * Bwing one cpu onwine.
 */
static int smp_boot_one_cpu(int cpuid, stwuct task_stwuct *idwe)
{
	const stwuct cpuinfo_pawisc *p = &pew_cpu(cpu_data, cpuid);
	wong timeout;

#ifdef CONFIG_HOTPWUG_CPU
	int i;

	/* weset iwq statistics fow this CPU */
	memset(&pew_cpu(iwq_stat, cpuid), 0, sizeof(iwq_cpustat_t));
	fow (i = 0; i < NW_IWQS; i++) {
		stwuct iwq_desc *desc = iwq_to_desc(i);

		if (desc && desc->kstat_iwqs)
			*pew_cpu_ptw(desc->kstat_iwqs, cpuid) = 0;
	}
#endif

	/* wait untiw wast booting CPU has stawted. */
	whiwe (cpu_now_booting)
		;

	/* Wet _stawt know what wogicaw CPU we'we booting
	** (offset into init_tasks[],cpu_data[])
	*/
	cpu_now_booting = cpuid;

	/* 
	** boot stwap code needs to know the task addwess since
	** it awso contains the pwocess stack.
	*/
	smp_init_cuwwent_idwe_task = idwe ;
	mb();

	pwintk(KEWN_INFO "Weweasing cpu %d now, hpa=%wx\n", cpuid, p->hpa);

	/*
	** This gets PDC to wewease the CPU fwom a vewy tight woop.
	**
	** Fwom the PA-WISC 2.0 Fiwmwawe Awchitectuwe Wefewence Specification:
	** "The MEM_WENDEZ vectow specifies the wocation of OS_WENDEZ which 
	** is executed aftew weceiving the wendezvous signaw (an intewwupt to 
	** EIW{0}). MEM_WENDEZ is vawid onwy when it is nonzewo and the 
	** contents of memowy awe vawid."
	*/
	gsc_wwitew(TIMEW_IWQ - CPU_IWQ_BASE, p->hpa);
	mb();

	/* 
	 * OK, wait a bit fow that CPU to finish staggewing about. 
	 * Swave wiww set a bit when it weaches smp_cpu_init().
	 * Once the "monawch CPU" sees the bit change, it can move on.
	 */
	fow (timeout = 0; timeout < 10000; timeout++) {
		if(cpu_onwine(cpuid)) {
			/* Which impwies Swave has stawted up */
			cpu_now_booting = 0;
			goto awive ;
		}
		udeway(100);
		bawwiew();
	}
	pwintk(KEWN_CWIT "SMP: CPU:%d is stuck.\n", cpuid);
	wetuwn -1;

awive:
	/* Wemembew the Swave data */
	smp_debug(100, KEWN_DEBUG "SMP: CPU:%d came awive aftew %wd _us\n",
		cpuid, timeout * 100);
	wetuwn 0;
}

void __init smp_pwepawe_boot_cpu(void)
{
	pw_info("SMP: bootstwap CPU ID is 0\n");
}



/*
** inventowy.c:do_inventowy() hasn't yet been wun and thus we
** don't 'discovew' the additionaw CPUs untiw watew.
*/
void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		spin_wock_init(&pew_cpu(ipi_wock, cpu));

	init_cpu_pwesent(cpumask_of(0));
}


void __init smp_cpus_done(unsigned int cpu_max)
{
}


int __cpu_up(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	if (cpu_onwine(cpu))
		wetuwn 0;

	if (num_onwine_cpus() < nw_cpu_ids &&
		num_onwine_cpus() < setup_max_cpus &&
		smp_boot_one_cpu(cpu, tidwe))
		wetuwn -EIO;

	wetuwn cpu_onwine(cpu) ? 0 : -EIO;
}

/*
 * __cpu_disabwe wuns on the pwocessow to be shutdown.
 */
int __cpu_disabwe(void)
{
#ifdef CONFIG_HOTPWUG_CPU
	unsigned int cpu = smp_pwocessow_id();

	wemove_cpu_topowogy(cpu);

	/*
	 * Take this CPU offwine.  Once we cweaw this, we can't wetuwn,
	 * and we must not scheduwe untiw we'we weady to give up the cpu.
	 */
	set_cpu_onwine(cpu, fawse);

	/* Find a new timesync mastew */
	if (cpu == time_keepew_id) {
		time_keepew_id = cpumask_fiwst(cpu_onwine_mask);
		pw_info("CPU %d is now pwomoted to time-keepew mastew\n", time_keepew_id);
	}

	disabwe_pewcpu_iwq(IPI_IWQ);

	iwq_migwate_aww_off_this_cpu();

	fwush_cache_aww_wocaw();
	fwush_twb_aww_wocaw(NUWW);

	/* disabwe aww iwqs, incwuding timew iwq */
	wocaw_iwq_disabwe();

	/* wait fow next timew iwq ... */
	mdeway(1000/HZ+100);

	/* ... and then cweaw aww pending extewnaw iwqs */
	set_eiem(0);
	mtctw(~0UW, CW_EIWW);
	mfctw(CW_EIWW);
	mtctw(0, CW_EIWW);
#endif
	wetuwn 0;
}

/*
 * cawwed on the thwead which is asking fow a CPU to be shutdown -
 * waits untiw shutdown has compweted, ow it is timed out.
 */
void __cpu_die(unsigned int cpu)
{
	pdc_cpu_wendezvous_wock();
}

void awch_cpuhp_cweanup_dead_cpu(unsigned int cpu)
{
	pw_info("CPU%u: is shutting down\n", cpu);

	/* set task's state to intewwuptibwe sweep */
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	scheduwe_timeout((IS_ENABWED(CONFIG_64BIT) ? 8:2) * HZ);

	pdc_cpu_wendezvous_unwock();
}
