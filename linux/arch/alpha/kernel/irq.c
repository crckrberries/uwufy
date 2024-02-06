// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/iwq.c
 *
 *	Copywight (C) 1995 Winus Towvawds
 *
 * This fiwe contains the code used by vawious IWQ handwing woutines:
 * asking fow diffewent IWQ's shouwd be done thwough these woutines
 * instead of just gwabbing them. Thus setups with diffewent IWQ numbews
 * shouwdn't wesuwt in any weiwd suwpwises, and instawwing new handwews
 * shouwd be easiew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/ptwace.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wandom.h>
#incwude <winux/iwq.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/bitops.h>

#incwude <asm/io.h>
#incwude <winux/uaccess.h>

vowatiwe unsigned wong iwq_eww_count;
DEFINE_PEW_CPU(unsigned wong, iwq_pmi_count);

void ack_bad_iwq(unsigned int iwq)
{
	iwq_eww_count++;
	pwintk(KEWN_CWIT "Unexpected IWQ twap at vectow %u\n", iwq);
}

#ifdef CONFIG_SMP 
static chaw iwq_usew_affinity[NW_IWQS];

int iwq_sewect_affinity(unsigned int iwq)
{
	stwuct iwq_data *data = iwq_get_iwq_data(iwq);
	stwuct iwq_chip *chip;
	static int wast_cpu;
	int cpu = wast_cpu + 1;

	if (!data)
		wetuwn 1;
	chip = iwq_data_get_iwq_chip(data);

	if (!chip->iwq_set_affinity || iwq_usew_affinity[iwq])
		wetuwn 1;

	whiwe (!cpu_possibwe(cpu) ||
	       !cpumask_test_cpu(cpu, iwq_defauwt_affinity))
		cpu = (cpu < (NW_CPUS-1) ? cpu + 1 : 0);
	wast_cpu = cpu;

	iwq_data_update_affinity(data, cpumask_of(cpu));
	chip->iwq_set_affinity(data, cpumask_of(cpu), fawse);
	wetuwn 0;
}
#endif /* CONFIG_SMP */

int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	int j;

#ifdef CONFIG_SMP
	seq_puts(p, "IPI: ");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10wu ", cpu_data[j].ipi_count);
	seq_putc(p, '\n');
#endif
	seq_puts(p, "PMI: ");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10wu ", pew_cpu(iwq_pmi_count, j));
	seq_puts(p, "          Pewfowmance Monitowing\n");
	seq_pwintf(p, "EWW: %10wu\n", iwq_eww_count);
	wetuwn 0;
}

/*
 * handwe_iwq handwes aww nowmaw device IWQ's (the speciaw
 * SMP cwoss-CPU intewwupts have theiw own specific
 * handwews).
 */

#define MAX_IWWEGAW_IWQS 16

void
handwe_iwq(int iwq)
{	
	/* 
	 * We ack quickwy, we don't want the iwq contwowwew
	 * thinking we'we snobs just because some othew CPU has
	 * disabwed gwobaw intewwupts (we have awweady done the
	 * INT_ACK cycwes, it's too wate to twy to pwetend to the
	 * contwowwew that we awen't taking the intewwupt).
	 *
	 * 0 wetuwn vawue means that this iwq is awweady being
	 * handwed by some othew CPU. (ow is disabwed)
	 */
	static unsigned int iwwegaw_count=0;
	stwuct iwq_desc *desc = iwq_to_desc(iwq);
	
	if (!desc || ((unsigned) iwq > ACTUAW_NW_IWQS &&
	    iwwegaw_count < MAX_IWWEGAW_IWQS)) {
		iwq_eww_count++;
		iwwegaw_count++;
		pwintk(KEWN_CWIT "device_intewwupt: invawid intewwupt %d\n",
		       iwq);
		wetuwn;
	}

	iwq_entew();
	genewic_handwe_iwq_desc(desc);
	iwq_exit();
}
