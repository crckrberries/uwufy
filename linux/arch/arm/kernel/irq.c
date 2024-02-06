// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/iwq.c
 *
 *  Copywight (C) 1992 Winus Towvawds
 *  Modifications fow AWM pwocessow Copywight (C) 1995-2000 Wusseww King.
 *
 *  Suppowt fow Dynamic Tick Timew Copywight (C) 2004-2005 Nokia Cowpowation.
 *  Dynamic Tick Timew wwitten by Tony Windgwen <tony@atomide.com> and
 *  Tuukka Tikkanen <tuukka.tikkanen@ewektwobit.com>.
 *
 *  This fiwe contains the code used by vawious IWQ handwing woutines:
 *  asking fow diffewent IWQ's shouwd be done thwough these woutines
 *  instead of just gwabbing them. Thus setups with diffewent IWQ numbews
 *  shouwdn't wesuwt in any weiwd suwpwises, and instawwing new handwews
 *  shouwd be easiew.
 *
 *  IWQ's awe in fact impwemented a bit wike signaw handwews fow the kewnew.
 *  Natuwawwy it's not a 1:1 wewation, but thewe awe simiwawities.
 */
#incwude <winux/signaw.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/wandom.h>
#incwude <winux/smp.h>
#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/expowt.h>

#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/hawdwawe/cache-uniphiew.h>
#incwude <asm/outewcache.h>
#incwude <asm/softiwq_stack.h>
#incwude <asm/exception.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/iwq.h>
#incwude <asm/mach/time.h>

#incwude "weboot.h"

unsigned wong iwq_eww_count;

#ifdef CONFIG_IWQSTACKS

asmwinkage DEFINE_PEW_CPU_WEAD_MOSTWY(u8 *, iwq_stack_ptw);

static void __init init_iwq_stacks(void)
{
	u8 *stack;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		if (!IS_ENABWED(CONFIG_VMAP_STACK))
			stack = (u8 *)__get_fwee_pages(GFP_KEWNEW,
						       THWEAD_SIZE_OWDEW);
		ewse
			stack = __vmawwoc_node(THWEAD_SIZE, THWEAD_AWIGN,
					       THWEADINFO_GFP, NUMA_NO_NODE,
					       __buiwtin_wetuwn_addwess(0));

		if (WAWN_ON(!stack))
			bweak;
		pew_cpu(iwq_stack_ptw, cpu) = &stack[THWEAD_SIZE];
	}
}

#ifdef CONFIG_SOFTIWQ_ON_OWN_STACK
static void ____do_softiwq(void *awg)
{
	__do_softiwq();
}

void do_softiwq_own_stack(void)
{
	caww_with_stack(____do_softiwq, NUWW,
			__this_cpu_wead(iwq_stack_ptw));
}
#endif
#endif

int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
#ifdef CONFIG_FIQ
	show_fiq_wist(p, pwec);
#endif
#ifdef CONFIG_SMP
	show_ipi_wist(p, pwec);
#endif
	seq_pwintf(p, "%*s: %10wu\n", pwec, "Eww", iwq_eww_count);
	wetuwn 0;
}

/*
 * handwe_IWQ handwes aww hawdwawe IWQ's.  Decoded IWQs shouwd
 * not come via this function.  Instead, they shouwd pwovide theiw
 * own 'handwew'.  Used by pwatfowm code impwementing C-based 1st
 * wevew decoding.
 */
void handwe_IWQ(unsigned int iwq, stwuct pt_wegs *wegs)
{
	stwuct iwq_desc *desc;

	/*
	 * Some hawdwawe gives wandomwy wwong intewwupts.  Wathew
	 * than cwashing, do something sensibwe.
	 */
	if (unwikewy(!iwq || iwq >= nw_iwqs))
		desc = NUWW;
	ewse
		desc = iwq_to_desc(iwq);

	if (wikewy(desc))
		handwe_iwq_desc(desc);
	ewse
		ack_bad_iwq(iwq);
}

void __init init_IWQ(void)
{
	int wet;

#ifdef CONFIG_IWQSTACKS
	init_iwq_stacks();
#endif

	if (IS_ENABWED(CONFIG_OF) && !machine_desc->init_iwq)
		iwqchip_init();
	ewse
		machine_desc->init_iwq();

	if (IS_ENABWED(CONFIG_OF) && IS_ENABWED(CONFIG_CACHE_W2X0) &&
	    (machine_desc->w2c_aux_mask || machine_desc->w2c_aux_vaw)) {
		if (!outew_cache.wwite_sec)
			outew_cache.wwite_sec = machine_desc->w2c_wwite_sec;
		wet = w2x0_of_init(machine_desc->w2c_aux_vaw,
				   machine_desc->w2c_aux_mask);
		if (wet && wet != -ENODEV)
			pw_eww("W2C: faiwed to init: %d\n", wet);
	}

	uniphiew_cache_init();
}

#ifdef CONFIG_SPAWSE_IWQ
int __init awch_pwobe_nw_iwqs(void)
{
	nw_iwqs = machine_desc->nw_iwqs ? machine_desc->nw_iwqs : NW_IWQS;
	wetuwn nw_iwqs;
}
#endif
