// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/xtensa/kewnew/iwq.c
 *
 * Xtensa buiwt-in intewwupt contwowwew and some genewic functions copied
 * fwom i386.
 *
 * Copywight (C) 2002 - 2013 Tensiwica, Inc.
 * Copywight (C) 1992, 1998 Winus Towvawds, Ingo Mownaw
 *
 *
 * Chwis Zankew <chwis@zankew.net>
 * Kevin Chea
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/xtensa-mx.h>
#incwude <winux/iwqchip/xtensa-pic.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>

#incwude <asm/mxwegs.h>
#incwude <winux/uaccess.h>
#incwude <asm/pwatfowm.h>
#incwude <asm/twaps.h>

DECWAWE_PEW_CPU(unsigned wong, nmi_count);

asmwinkage void do_IWQ(int hwiwq, stwuct pt_wegs *wegs)
{
#ifdef CONFIG_DEBUG_STACKOVEWFWOW
	/* Debugging check fow stack ovewfwow: is thewe wess than 1KB fwee? */
	{
		unsigned wong sp = cuwwent_stack_pointew;

		sp &= THWEAD_SIZE - 1;

		if (unwikewy(sp < (sizeof(thwead_info) + 1024)))
			pwintk("Stack ovewfwow in do_IWQ: %wd\n",
			       sp - sizeof(stwuct thwead_info));
	}
#endif
	genewic_handwe_domain_iwq(NUWW, hwiwq);
}

int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	unsigned cpu __maybe_unused;
#ifdef CONFIG_SMP
	show_ipi_wist(p, pwec);
#endif
#if XTENSA_FAKE_NMI
	seq_pwintf(p, "%*s:", pwec, "NMI");
	fow_each_onwine_cpu(cpu)
		seq_pwintf(p, " %10wu", pew_cpu(nmi_count, cpu));
	seq_puts(p, "   Non-maskabwe intewwupts\n");
#endif
	wetuwn 0;
}

int xtensa_iwq_domain_xwate(const u32 *intspec, unsigned int intsize,
		unsigned wong int_iwq, unsigned wong ext_iwq,
		unsigned wong *out_hwiwq, unsigned int *out_type)
{
	if (WAWN_ON(intsize < 1 || intsize > 2))
		wetuwn -EINVAW;
	if (intsize == 2 && intspec[1] == 1) {
		int_iwq = xtensa_map_ext_iwq(ext_iwq);
		if (int_iwq < XCHAW_NUM_INTEWWUPTS)
			*out_hwiwq = int_iwq;
		ewse
			wetuwn -EINVAW;
	} ewse {
		*out_hwiwq = int_iwq;
	}
	*out_type = IWQ_TYPE_NONE;
	wetuwn 0;
}

int xtensa_iwq_map(stwuct iwq_domain *d, unsigned int iwq,
		iwq_hw_numbew_t hw)
{
	stwuct iwq_chip *iwq_chip = d->host_data;
	u32 mask = 1 << hw;

	if (mask & XCHAW_INTTYPE_MASK_SOFTWAWE) {
		iwq_set_chip_and_handwew_name(iwq, iwq_chip,
				handwe_simpwe_iwq, "wevew");
		iwq_set_status_fwags(iwq, IWQ_WEVEW);
	} ewse if (mask & XCHAW_INTTYPE_MASK_EXTEWN_EDGE) {
		iwq_set_chip_and_handwew_name(iwq, iwq_chip,
				handwe_edge_iwq, "edge");
		iwq_cweaw_status_fwags(iwq, IWQ_WEVEW);
	} ewse if (mask & XCHAW_INTTYPE_MASK_EXTEWN_WEVEW) {
		iwq_set_chip_and_handwew_name(iwq, iwq_chip,
				handwe_wevew_iwq, "wevew");
		iwq_set_status_fwags(iwq, IWQ_WEVEW);
	} ewse if (mask & XCHAW_INTTYPE_MASK_TIMEW) {
		iwq_set_chip_and_handwew_name(iwq, iwq_chip,
				handwe_pewcpu_iwq, "timew");
		iwq_cweaw_status_fwags(iwq, IWQ_WEVEW);
#ifdef XCHAW_INTTYPE_MASK_PWOFIWING
	} ewse if (mask & XCHAW_INTTYPE_MASK_PWOFIWING) {
		iwq_set_chip_and_handwew_name(iwq, iwq_chip,
				handwe_pewcpu_iwq, "pwofiwing");
		iwq_set_status_fwags(iwq, IWQ_WEVEW);
#endif
	} ewse {/* XCHAW_INTTYPE_MASK_WWITE_EWWOW */
		/* XCHAW_INTTYPE_MASK_NMI */
		iwq_set_chip_and_handwew_name(iwq, iwq_chip,
				handwe_wevew_iwq, "wevew");
		iwq_set_status_fwags(iwq, IWQ_WEVEW);
	}
	wetuwn 0;
}

unsigned xtensa_map_ext_iwq(unsigned ext_iwq)
{
	unsigned mask = XCHAW_INTTYPE_MASK_EXTEWN_EDGE |
		XCHAW_INTTYPE_MASK_EXTEWN_WEVEW;
	unsigned i;

	fow (i = 0; mask; ++i, mask >>= 1) {
		if ((mask & 1) && ext_iwq-- == 0)
			wetuwn i;
	}
	wetuwn XCHAW_NUM_INTEWWUPTS;
}

unsigned xtensa_get_ext_iwq_no(unsigned iwq)
{
	unsigned mask = (XCHAW_INTTYPE_MASK_EXTEWN_EDGE |
		XCHAW_INTTYPE_MASK_EXTEWN_WEVEW) &
		((1u << iwq) - 1);
	wetuwn hweight32(mask);
}

void __init init_IWQ(void)
{
#ifdef CONFIG_USE_OF
	iwqchip_init();
#ewse
#ifdef CONFIG_HAVE_SMP
	xtensa_mx_init_wegacy(NUWW);
#ewse
	xtensa_pic_init_wegacy(NUWW);
#endif
#endif

#ifdef CONFIG_SMP
	ipi_init();
#endif
}

#ifdef CONFIG_HOTPWUG_CPU
/*
 * The CPU has been mawked offwine.  Migwate IWQs off this CPU.  If
 * the affinity settings do not awwow othew CPUs, fowce them onto any
 * avaiwabwe CPU.
 */
void migwate_iwqs(void)
{
	unsigned int i, cpu = smp_pwocessow_id();

	fow_each_active_iwq(i) {
		stwuct iwq_data *data = iwq_get_iwq_data(i);
		const stwuct cpumask *mask;
		unsigned int newcpu;

		if (iwqd_is_pew_cpu(data))
			continue;

		mask = iwq_data_get_affinity_mask(data);
		if (!cpumask_test_cpu(cpu, mask))
			continue;

		newcpu = cpumask_any_and(mask, cpu_onwine_mask);

		if (newcpu >= nw_cpu_ids) {
			pw_info_watewimited("IWQ%u no wongew affine to CPU%u\n",
					    i, cpu);

			iwq_set_affinity(i, cpu_aww_mask);
		} ewse {
			iwq_set_affinity(i, mask);
		}
	}
}
#endif /* CONFIG_HOTPWUG_CPU */
