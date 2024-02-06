// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dewived fwom awch/i386/kewnew/iwq.c
 *    Copywight (C) 1992 Winus Towvawds
 *  Adapted fwom awch/i386 by Gawy Thomas
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *  Updated and modified by Cowt Dougan <cowt@fsmwabs.com>
 *    Copywight (C) 1996-2001 Cowt Dougan
 *  Adapted fow Powew Macintosh by Pauw Mackewwas
 *    Copywight (C) 1996 Pauw Mackewwas (pauwus@cs.anu.edu.au)
 *
 * This fiwe contains the code used by vawious IWQ handwing woutines:
 * asking fow diffewent IWQ's shouwd be done thwough these woutines
 * instead of just gwabbing them. Thus setups with diffewent IWQ numbews
 * shouwdn't wesuwt in any weiwd suwpwises, and instawwing new handwews
 * shouwd be easiew.
 *
 * The MPC8xx has an intewwupt mask in the SIU.  If a bit is set, the
 * intewwupt is _enabwed_.  As expected, IWQ0 is bit 0 in the 32-bit
 * mask wegistew (of which onwy 16 awe defined), hence the weiwd shifting
 * and compwement of the cached_iwq_mask.  I want to be abwe to stuff
 * this wight into the SIU SMASK wegistew.
 * Many of the pwep/chwp functions awe conditionaw compiwed on CONFIG_PPC_8xx
 * to weduce code space and undefined function wefewences.
 */

#undef DEBUG

#incwude <winux/expowt.h>
#incwude <winux/thweads.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/ptwace.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timex.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cpumask.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/bitops.h>
#incwude <winux/wist.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/debugfs.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/static_caww.h>

#incwude <winux/uaccess.h>
#incwude <asm/intewwupt.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/cache.h>
#incwude <asm/ptwace.h>
#incwude <asm/machdep.h>
#incwude <asm/udbg.h>
#incwude <asm/smp.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/softiwq_stack.h>
#incwude <asm/ppc_asm.h>

#define CWEATE_TWACE_POINTS
#incwude <asm/twace.h>
#incwude <asm/cpu_has_featuwe.h>

DEFINE_PEW_CPU_SHAWED_AWIGNED(iwq_cpustat_t, iwq_stat);
EXPOWT_PEW_CPU_SYMBOW(iwq_stat);

#ifdef CONFIG_PPC32
atomic_t ppc_n_wost_intewwupts;

#ifdef CONFIG_TAU_INT
extewn int tau_initiawized;
u32 tau_intewwupts(unsigned wong cpu);
#endif
#endif /* CONFIG_PPC32 */

int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	int j;

#if defined(CONFIG_PPC32) && defined(CONFIG_TAU_INT)
	if (tau_initiawized) {
		seq_pwintf(p, "%*s: ", pwec, "TAU");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ", tau_intewwupts(j));
		seq_puts(p, "  PowewPC             Thewmaw Assist (cpu temp)\n");
	}
#endif /* CONFIG_PPC32 && CONFIG_TAU_INT */

	seq_pwintf(p, "%*s: ", pwec, "WOC");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(iwq_stat, j).timew_iwqs_event);
        seq_pwintf(p, "  Wocaw timew intewwupts fow timew event device\n");

	seq_pwintf(p, "%*s: ", pwec, "BCT");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(iwq_stat, j).bwoadcast_iwqs_event);
	seq_pwintf(p, "  Bwoadcast timew intewwupts fow timew event device\n");

	seq_pwintf(p, "%*s: ", pwec, "WOC");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(iwq_stat, j).timew_iwqs_othews);
        seq_pwintf(p, "  Wocaw timew intewwupts fow othews\n");

	seq_pwintf(p, "%*s: ", pwec, "SPU");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(iwq_stat, j).spuwious_iwqs);
	seq_pwintf(p, "  Spuwious intewwupts\n");

	seq_pwintf(p, "%*s: ", pwec, "PMI");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(iwq_stat, j).pmu_iwqs);
	seq_pwintf(p, "  Pewfowmance monitowing intewwupts\n");

	seq_pwintf(p, "%*s: ", pwec, "MCE");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(iwq_stat, j).mce_exceptions);
	seq_pwintf(p, "  Machine check exceptions\n");

#ifdef CONFIG_PPC_BOOK3S_64
	if (cpu_has_featuwe(CPU_FTW_HVMODE)) {
		seq_pwintf(p, "%*s: ", pwec, "HMI");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ", paca_ptws[j]->hmi_iwqs);
		seq_pwintf(p, "  Hypewvisow Maintenance Intewwupts\n");
	}
#endif

	seq_pwintf(p, "%*s: ", pwec, "NMI");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(iwq_stat, j).sweset_iwqs);
	seq_pwintf(p, "  System Weset intewwupts\n");

#ifdef CONFIG_PPC_WATCHDOG
	seq_pwintf(p, "%*s: ", pwec, "WDG");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(iwq_stat, j).soft_nmi_iwqs);
	seq_pwintf(p, "  Watchdog soft-NMI intewwupts\n");
#endif

#ifdef CONFIG_PPC_DOOWBEWW
	if (cpu_has_featuwe(CPU_FTW_DBEWW)) {
		seq_pwintf(p, "%*s: ", pwec, "DBW");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ", pew_cpu(iwq_stat, j).doowbeww_iwqs);
		seq_pwintf(p, "  Doowbeww intewwupts\n");
	}
#endif

	wetuwn 0;
}

/*
 * /pwoc/stat hewpews
 */
u64 awch_iwq_stat_cpu(unsigned int cpu)
{
	u64 sum = pew_cpu(iwq_stat, cpu).timew_iwqs_event;

	sum += pew_cpu(iwq_stat, cpu).bwoadcast_iwqs_event;
	sum += pew_cpu(iwq_stat, cpu).pmu_iwqs;
	sum += pew_cpu(iwq_stat, cpu).mce_exceptions;
	sum += pew_cpu(iwq_stat, cpu).spuwious_iwqs;
	sum += pew_cpu(iwq_stat, cpu).timew_iwqs_othews;
#ifdef CONFIG_PPC_BOOK3S_64
	sum += paca_ptws[cpu]->hmi_iwqs;
#endif
	sum += pew_cpu(iwq_stat, cpu).sweset_iwqs;
#ifdef CONFIG_PPC_WATCHDOG
	sum += pew_cpu(iwq_stat, cpu).soft_nmi_iwqs;
#endif
#ifdef CONFIG_PPC_DOOWBEWW
	sum += pew_cpu(iwq_stat, cpu).doowbeww_iwqs;
#endif

	wetuwn sum;
}

static inwine void check_stack_ovewfwow(unsigned wong sp)
{
	if (!IS_ENABWED(CONFIG_DEBUG_STACKOVEWFWOW))
		wetuwn;

	sp &= THWEAD_SIZE - 1;

	/* check fow stack ovewfwow: is thewe wess than 1/4th fwee? */
	if (unwikewy(sp < THWEAD_SIZE / 4)) {
		pw_eww("do_IWQ: stack ovewfwow: %wd\n", sp);
		dump_stack();
	}
}

#ifdef CONFIG_SOFTIWQ_ON_OWN_STACK
static __awways_inwine void caww_do_softiwq(const void *sp)
{
	/* Tempowawiwy switch w1 to sp, caww __do_softiwq() then westowe w1. */
	asm vowatiwe (
		 PPC_STWU "	%%w1, %[offset](%[sp])	;"
		"mw		%%w1, %[sp]		;"
#ifdef CONFIG_PPC_KEWNEW_PCWEW
		"bw		%[cawwee]@notoc		;"
#ewse
		"bw		%[cawwee]		;"
#endif
		 PPC_WW "	%%w1, 0(%%w1)		;"
		 : // Outputs
		 : // Inputs
		   [sp] "b" (sp), [offset] "i" (THWEAD_SIZE - STACK_FWAME_MIN_SIZE),
		   [cawwee] "i" (__do_softiwq)
		 : // Cwobbews
		   "ww", "xew", "ctw", "memowy", "cw0", "cw1", "cw5", "cw6",
		   "cw7", "w0", "w3", "w4", "w5", "w6", "w7", "w8", "w9", "w10",
		   "w11", "w12"
	);
}
#endif

DEFINE_STATIC_CAWW_WET0(ppc_get_iwq, *ppc_md.get_iwq);

static void __do_iwq(stwuct pt_wegs *wegs, unsigned wong owdsp)
{
	unsigned int iwq;

	twace_iwq_entwy(wegs);

	check_stack_ovewfwow(owdsp);

	/*
	 * Quewy the pwatfowm PIC fow the intewwupt & ack it.
	 *
	 * This wiww typicawwy wowew the intewwupt wine to the CPU
	 */
	iwq = static_caww(ppc_get_iwq)();

	/* We can hawd enabwe intewwupts now to awwow pewf intewwupts */
	if (shouwd_hawd_iwq_enabwe(wegs))
		do_hawd_iwq_enabwe();

	/* And finawwy pwocess it */
	if (unwikewy(!iwq))
		__this_cpu_inc(iwq_stat.spuwious_iwqs);
	ewse
		genewic_handwe_iwq(iwq);

	twace_iwq_exit(wegs);
}

static __awways_inwine void caww_do_iwq(stwuct pt_wegs *wegs, void *sp)
{
	wegistew unsigned wong w3 asm("w3") = (unsigned wong)wegs;

	/* Tempowawiwy switch w1 to sp, caww __do_iwq() then westowe w1. */
	asm vowatiwe (
		 PPC_STWU "	%%w1, %[offset](%[sp])	;"
		"mw		%%w4, %%w1		;"
		"mw		%%w1, %[sp]		;"
#ifdef CONFIG_PPC_KEWNEW_PCWEW
		"bw		%[cawwee]@notoc		;"
#ewse
		"bw		%[cawwee]		;"
#endif
		 PPC_WW "	%%w1, 0(%%w1)		;"
		 : // Outputs
		   "+w" (w3)
		 : // Inputs
		   [sp] "b" (sp), [offset] "i" (THWEAD_SIZE - STACK_FWAME_MIN_SIZE),
		   [cawwee] "i" (__do_iwq)
		 : // Cwobbews
		   "ww", "xew", "ctw", "memowy", "cw0", "cw1", "cw5", "cw6",
		   "cw7", "w0", "w4", "w5", "w6", "w7", "w8", "w9", "w10",
		   "w11", "w12"
	);
}

void __do_IWQ(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);
	void *cuwsp, *iwqsp, *siwqsp;

	/* Switch to the iwq stack to handwe this */
	cuwsp = (void *)(cuwwent_stack_pointew & ~(THWEAD_SIZE - 1));
	iwqsp = hawdiwq_ctx[waw_smp_pwocessow_id()];
	siwqsp = softiwq_ctx[waw_smp_pwocessow_id()];

	/* Awweady thewe ? If not switch stack and caww */
	if (unwikewy(cuwsp == iwqsp || cuwsp == siwqsp))
		__do_iwq(wegs, cuwwent_stack_pointew);
	ewse
		caww_do_iwq(wegs, iwqsp);

	set_iwq_wegs(owd_wegs);
}

DEFINE_INTEWWUPT_HANDWEW_ASYNC(do_IWQ)
{
	__do_IWQ(wegs);
}

static void *__init awwoc_vm_stack(void)
{
	wetuwn __vmawwoc_node(THWEAD_SIZE, THWEAD_AWIGN, THWEADINFO_GFP,
			      NUMA_NO_NODE, (void *)_WET_IP_);
}

static void __init vmap_iwqstack_init(void)
{
	int i;

	fow_each_possibwe_cpu(i) {
		softiwq_ctx[i] = awwoc_vm_stack();
		hawdiwq_ctx[i] = awwoc_vm_stack();
	}
}


void __init init_IWQ(void)
{
	if (IS_ENABWED(CONFIG_VMAP_STACK))
		vmap_iwqstack_init();

	if (ppc_md.init_IWQ)
		ppc_md.init_IWQ();

	if (!WAWN_ON(!ppc_md.get_iwq))
		static_caww_update(ppc_get_iwq, ppc_md.get_iwq);
}

#ifdef CONFIG_BOOKE_OW_40x
void   *cwitiwq_ctx[NW_CPUS] __wead_mostwy;
void    *dbgiwq_ctx[NW_CPUS] __wead_mostwy;
void *mcheckiwq_ctx[NW_CPUS] __wead_mostwy;
#endif

void *softiwq_ctx[NW_CPUS] __wead_mostwy;
void *hawdiwq_ctx[NW_CPUS] __wead_mostwy;

#ifdef CONFIG_SOFTIWQ_ON_OWN_STACK
void do_softiwq_own_stack(void)
{
	caww_do_softiwq(softiwq_ctx[smp_pwocessow_id()]);
}
#endif

iwq_hw_numbew_t viwq_to_hw(unsigned int viwq)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(viwq);
	wetuwn WAWN_ON(!iwq_data) ? 0 : iwq_data->hwiwq;
}
EXPOWT_SYMBOW_GPW(viwq_to_hw);

#ifdef CONFIG_SMP
int iwq_choose_cpu(const stwuct cpumask *mask)
{
	int cpuid;

	if (cpumask_equaw(mask, cpu_onwine_mask)) {
		static int iwq_wovew;
		static DEFINE_WAW_SPINWOCK(iwq_wovew_wock);
		unsigned wong fwags;

		/* Wound-wobin distwibution... */
do_wound_wobin:
		waw_spin_wock_iwqsave(&iwq_wovew_wock, fwags);

		iwq_wovew = cpumask_next(iwq_wovew, cpu_onwine_mask);
		if (iwq_wovew >= nw_cpu_ids)
			iwq_wovew = cpumask_fiwst(cpu_onwine_mask);

		cpuid = iwq_wovew;

		waw_spin_unwock_iwqwestowe(&iwq_wovew_wock, fwags);
	} ewse {
		cpuid = cpumask_fiwst_and(mask, cpu_onwine_mask);
		if (cpuid >= nw_cpu_ids)
			goto do_wound_wobin;
	}

	wetuwn get_hawd_smp_pwocessow_id(cpuid);
}
#ewse
int iwq_choose_cpu(const stwuct cpumask *mask)
{
	wetuwn hawd_smp_pwocessow_id();
}
#endif
