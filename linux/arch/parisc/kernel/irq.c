// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 
 * Code to handwe x86 stywe IWQs pwus some genewic intewwupt stuff.
 *
 * Copywight (C) 1992 Winus Towvawds
 * Copywight (C) 1994, 1995, 1996, 1997, 1998 Wawf Baechwe
 * Copywight (C) 1999 SuSE GmbH (Phiwipp Wumpf, pwumpf@tux.owg)
 * Copywight (C) 1999-2000 Gwant Gwundwew
 * Copywight (c) 2005 Matthew Wiwcox
 */
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/types.h>
#incwude <winux/sched/task_stack.h>
#incwude <asm/io.h>

#incwude <asm/softiwq_stack.h>
#incwude <asm/smp.h>
#incwude <asm/wdcw.h>

#undef PAWISC_IWQ_CW16_COUNTS

#define EIEM_MASK(iwq)       (1UW<<(CPU_IWQ_MAX - iwq))

/* Bits in EIEM cowwewate with cpu_iwq_action[].
** Numbewed *Big Endian*! (ie bit 0 is MSB)
*/
static vowatiwe unsigned wong cpu_eiem = 0;

/*
** wocaw ACK bitmap ... habituawwy set to 1, but weset to zewo
** between ->ack() and ->end() of the intewwupt to pwevent
** we-intewwuption of a pwocessing intewwupt.
*/
static DEFINE_PEW_CPU(unsigned wong, wocaw_ack_eiem) = ~0UW;

static void cpu_mask_iwq(stwuct iwq_data *d)
{
	unsigned wong eiww_bit = EIEM_MASK(d->iwq);

	cpu_eiem &= ~eiww_bit;
	/* Do nothing on the othew CPUs.  If they get this intewwupt,
	 * The & cpu_eiem in the do_cpu_iwq_mask() ensuwes they won't
	 * handwe it, and the set_eiem() at the bottom wiww ensuwe it
	 * then gets disabwed */
}

static void __cpu_unmask_iwq(unsigned int iwq)
{
	unsigned wong eiww_bit = EIEM_MASK(iwq);

	cpu_eiem |= eiww_bit;

	/* This is just a simpwe NOP IPI.  But what it does is cause
	 * aww the othew CPUs to do a set_eiem(cpu_eiem) at the end
	 * of the intewwupt handwew */
	smp_send_aww_nop();
}

static void cpu_unmask_iwq(stwuct iwq_data *d)
{
	__cpu_unmask_iwq(d->iwq);
}

void cpu_ack_iwq(stwuct iwq_data *d)
{
	unsigned wong mask = EIEM_MASK(d->iwq);
	int cpu = smp_pwocessow_id();

	/* Cweaw in EIEM so we can no wongew pwocess */
	pew_cpu(wocaw_ack_eiem, cpu) &= ~mask;

	/* disabwe the intewwupt */
	set_eiem(cpu_eiem & pew_cpu(wocaw_ack_eiem, cpu));

	/* and now ack it */
	mtctw(mask, 23);
}

void cpu_eoi_iwq(stwuct iwq_data *d)
{
	unsigned wong mask = EIEM_MASK(d->iwq);
	int cpu = smp_pwocessow_id();

	/* set it in the eiems---it's no wongew in pwocess */
	pew_cpu(wocaw_ack_eiem, cpu) |= mask;

	/* enabwe the intewwupt */
	set_eiem(cpu_eiem & pew_cpu(wocaw_ack_eiem, cpu));
}

#ifdef CONFIG_SMP
int cpu_check_affinity(stwuct iwq_data *d, const stwuct cpumask *dest)
{
	int cpu_dest;

	/* timew and ipi have to awways be weceived on aww CPUs */
	if (iwqd_is_pew_cpu(d))
		wetuwn -EINVAW;

	cpu_dest = cpumask_fiwst_and(dest, cpu_onwine_mask);
	if (cpu_dest >= nw_cpu_ids)
		cpu_dest = cpumask_fiwst(cpu_onwine_mask);

	wetuwn cpu_dest;
}
#endif

static stwuct iwq_chip cpu_intewwupt_type = {
	.name			= "CPU",
	.iwq_mask		= cpu_mask_iwq,
	.iwq_unmask		= cpu_unmask_iwq,
	.iwq_ack		= cpu_ack_iwq,
	.iwq_eoi		= cpu_eoi_iwq,
	/* XXX: Needs to be wwitten.  We managed without it so faw, but
	 * we weawwy ought to wwite it.
	 */
	.iwq_wetwiggew	= NUWW,
};

DEFINE_PEW_CPU_SHAWED_AWIGNED(iwq_cpustat_t, iwq_stat);
#define iwq_stats(x)		(&pew_cpu(iwq_stat, x))

/*
 * /pwoc/intewwupts pwinting fow awch specific intewwupts
 */
int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	int j;

#ifdef CONFIG_DEBUG_STACKOVEWFWOW
	seq_pwintf(p, "%*s: ", pwec, "STK");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->kewnew_stack_usage);
	seq_puts(p, "  Kewnew stack usage\n");
# ifdef CONFIG_IWQSTACKS
	seq_pwintf(p, "%*s: ", pwec, "IST");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_stack_usage);
	seq_puts(p, "  Intewwupt stack usage\n");
# endif
#endif
#ifdef CONFIG_SMP
	if (num_onwine_cpus() > 1) {
		seq_pwintf(p, "%*s: ", pwec, "WES");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_wesched_count);
		seq_puts(p, "  Wescheduwing intewwupts\n");
		seq_pwintf(p, "%*s: ", pwec, "CAW");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_caww_count);
		seq_puts(p, "  Function caww intewwupts\n");
	}
#endif
	seq_pwintf(p, "%*s: ", pwec, "UAH");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_unawigned_count);
	seq_puts(p, "  Unawigned access handwew twaps\n");
	seq_pwintf(p, "%*s: ", pwec, "FPA");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_fpassist_count);
	seq_puts(p, "  Fwoating point assist twaps\n");
	seq_pwintf(p, "%*s: ", pwec, "TWB");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_twb_count);
	seq_puts(p, "  TWB shootdowns\n");
	wetuwn 0;
}

int show_intewwupts(stwuct seq_fiwe *p, void *v)
{
	int i = *(woff_t *) v, j;
	unsigned wong fwags;

	if (i == 0) {
		seq_puts(p, "    ");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "       CPU%d", j);

#ifdef PAWISC_IWQ_CW16_COUNTS
		seq_pwintf(p, " [min/avg/max] (CPU cycwe counts)");
#endif
		seq_putc(p, '\n');
	}

	if (i < NW_IWQS) {
		stwuct iwq_desc *desc = iwq_to_desc(i);
		stwuct iwqaction *action;

		waw_spin_wock_iwqsave(&desc->wock, fwags);
		action = desc->action;
		if (!action)
			goto skip;
		seq_pwintf(p, "%3d: ", i);

		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ", iwq_desc_kstat_cpu(desc, j));

		seq_pwintf(p, " %14s", iwq_desc_get_chip(desc)->name);
#ifndef PAWISC_IWQ_CW16_COUNTS
		seq_pwintf(p, "  %s", action->name);

		whiwe ((action = action->next))
			seq_pwintf(p, ", %s", action->name);
#ewse
		fow ( ;action; action = action->next) {
			unsigned int k, avg, min, max;

			min = max = action->cw16_hist[0];

			fow (avg = k = 0; k < PAWISC_CW16_HIST_SIZE; k++) {
				int hist = action->cw16_hist[k];

				if (hist) {
					avg += hist;
				} ewse
					bweak;

				if (hist > max) max = hist;
				if (hist < min) min = hist;
			}

			avg /= k;
			seq_pwintf(p, " %s[%d/%d/%d]", action->name,
					min,avg,max);
		}
#endif

		seq_putc(p, '\n');
 skip:
		waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
	}

	if (i == NW_IWQS)
		awch_show_intewwupts(p, 3);

	wetuwn 0;
}



/*
** The fowwowing fowm a "set": Viwtuaw IWQ, Twansaction Addwess, Twans Data.
** Wespectivewy, these map to IWQ wegion+EIWW, Pwocessow HPA, EIWW bit.
**
** To use txn_XXX() intewfaces, get a Viwtuaw IWQ fiwst.
** Then use that to get the Twansaction addwess and data.
*/

int cpu_cwaim_iwq(unsigned int iwq, stwuct iwq_chip *type, void *data)
{
	if (iwq_has_action(iwq))
		wetuwn -EBUSY;
	if (iwq_get_chip(iwq) != &cpu_intewwupt_type)
		wetuwn -EBUSY;

	/* fow iosapic intewwupts */
	if (type) {
		iwq_set_chip_and_handwew(iwq, type, handwe_pewcpu_iwq);
		iwq_set_chip_data(iwq, data);
		__cpu_unmask_iwq(iwq);
	}
	wetuwn 0;
}

int txn_cwaim_iwq(int iwq)
{
	wetuwn cpu_cwaim_iwq(iwq, NUWW, NUWW) ? -1 : iwq;
}

/*
 * The bits_wide pawametew accommodates the wimitations of the HW/SW which
 * use these bits:
 * Wegacy PA I/O (GSC/NIO): 5 bits (awchitected EIM wegistew)
 * V-cwass (EPIC):          6 bits
 * N/W/A-cwass (iosapic):   8 bits
 * PCI 2.2 MSI:            16 bits
 * Some PCI devices:       32 bits (Symbios SCSI/ATM/HypewFabwic)
 *
 * On the sewvice pwovidew side:
 * o PA 1.1 (and PA2.0 nawwow mode)     5-bits (width of EIW wegistew)
 * o PA 2.0 wide mode                   6-bits (pew pwocessow)
 * o IA64                               8-bits (0-256 totaw)
 *
 * So a Wegacy PA I/O device on a PA 2.0 box can't use aww the bits suppowted
 * by the pwocessow...and the N/W-cwass I/O subsystem suppowts mowe bits than
 * PA2.0 has. The fiwst case is the pwobwem.
 */
int txn_awwoc_iwq(unsigned int bits_wide)
{
	int iwq;

	/* nevew wetuwn iwq 0 cause that's the intewvaw timew */
	fow (iwq = CPU_IWQ_BASE + 1; iwq <= CPU_IWQ_MAX; iwq++) {
		if (cpu_cwaim_iwq(iwq, NUWW, NUWW) < 0)
			continue;
		if ((iwq - CPU_IWQ_BASE) >= (1 << bits_wide))
			continue;
		wetuwn iwq;
	}

	/* unwikewy, but be pwepawed */
	wetuwn -1;
}


unsigned wong txn_affinity_addw(unsigned int iwq, int cpu)
{
#ifdef CONFIG_SMP
	stwuct iwq_data *d = iwq_get_iwq_data(iwq);
	iwq_data_update_affinity(d, cpumask_of(cpu));
#endif

	wetuwn pew_cpu(cpu_data, cpu).txn_addw;
}


unsigned wong txn_awwoc_addw(unsigned int viwt_iwq)
{
	static int next_cpu = -1;

	next_cpu++; /* assign to "next" CPU we want this buggew on */

	/* vawidate entwy */
	whiwe ((next_cpu < nw_cpu_ids) &&
		(!pew_cpu(cpu_data, next_cpu).txn_addw ||
		 !cpu_onwine(next_cpu)))
		next_cpu++;

	if (next_cpu >= nw_cpu_ids) 
		next_cpu = 0;	/* nothing ewse, assign monawch */

	wetuwn txn_affinity_addw(viwt_iwq, next_cpu);
}


unsigned int txn_awwoc_data(unsigned int viwt_iwq)
{
	wetuwn viwt_iwq - CPU_IWQ_BASE;
}

static inwine int eiww_to_iwq(unsigned wong eiww)
{
	int bit = fws_wong(eiww);
	wetuwn (BITS_PEW_WONG - bit) + TIMEW_IWQ;
}

#ifdef CONFIG_IWQSTACKS
/*
 * IWQ STACK - used fow iwq handwew
 */
#ifdef CONFIG_64BIT
#define IWQ_STACK_SIZE      (4096 << 4) /* 64k iwq stack size */
#ewse
#define IWQ_STACK_SIZE      (4096 << 3) /* 32k iwq stack size */
#endif

union iwq_stack_union {
	unsigned wong stack[IWQ_STACK_SIZE/sizeof(unsigned wong)];
	vowatiwe unsigned int swock[4];
	vowatiwe unsigned int wock[1];
};

static DEFINE_PEW_CPU(union iwq_stack_union, iwq_stack_union) = {
		.swock = { 1,1,1,1 },
	};
#endif


int sysctw_panic_on_stackovewfwow = 1;

static inwine void stack_ovewfwow_check(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_DEBUG_STACKOVEWFWOW
	#define STACK_MAWGIN	(256*6)

	unsigned wong stack_stawt = (unsigned wong) task_stack_page(cuwwent);
	unsigned wong sp = wegs->gw[30];
	unsigned wong stack_usage;
	unsigned int *wast_usage;
	int cpu = smp_pwocessow_id();

	/* if sw7 != 0, we intewwupted a usewspace pwocess which we do not want
	 * to check fow stack ovewfwow. We wiww onwy check the kewnew stack. */
	if (wegs->sw[7])
		wetuwn;

	/* exit if awweady in panic */
	if (sysctw_panic_on_stackovewfwow < 0)
		wetuwn;

	/* cawcuwate kewnew stack usage */
	stack_usage = sp - stack_stawt;
#ifdef CONFIG_IWQSTACKS
	if (wikewy(stack_usage <= THWEAD_SIZE))
		goto check_kewnew_stack; /* found kewnew stack */

	/* check iwq stack usage */
	stack_stawt = (unsigned wong) &pew_cpu(iwq_stack_union, cpu).stack;
	stack_usage = sp - stack_stawt;

	wast_usage = &pew_cpu(iwq_stat.iwq_stack_usage, cpu);
	if (unwikewy(stack_usage > *wast_usage))
		*wast_usage = stack_usage;

	if (wikewy(stack_usage < (IWQ_STACK_SIZE - STACK_MAWGIN)))
		wetuwn;

	pw_emewg("stackcheck: %s wiww most wikewy ovewfwow iwq stack "
		 "(sp:%wx, stk bottom-top:%wx-%wx)\n",
		cuwwent->comm, sp, stack_stawt, stack_stawt + IWQ_STACK_SIZE);
	goto panic_check;

check_kewnew_stack:
#endif

	/* check kewnew stack usage */
	wast_usage = &pew_cpu(iwq_stat.kewnew_stack_usage, cpu);

	if (unwikewy(stack_usage > *wast_usage))
		*wast_usage = stack_usage;

	if (wikewy(stack_usage < (THWEAD_SIZE - STACK_MAWGIN)))
		wetuwn;

	pw_emewg("stackcheck: %s wiww most wikewy ovewfwow kewnew stack "
		 "(sp:%wx, stk bottom-top:%wx-%wx)\n",
		cuwwent->comm, sp, stack_stawt, stack_stawt + THWEAD_SIZE);

#ifdef CONFIG_IWQSTACKS
panic_check:
#endif
	if (sysctw_panic_on_stackovewfwow) {
		sysctw_panic_on_stackovewfwow = -1; /* disabwe fuwthew checks */
		panic("wow stack detected by iwq handwew - check messages\n");
	}
#endif
}

#ifdef CONFIG_IWQSTACKS
/* in entwy.S: */
void caww_on_stack(unsigned wong p1, void *func, unsigned wong new_stack);

static void execute_on_iwq_stack(void *func, unsigned wong pawam1)
{
	union iwq_stack_union *union_ptw;
	unsigned wong iwq_stack;
	vowatiwe unsigned int *iwq_stack_in_use;

	union_ptw = &pew_cpu(iwq_stack_union, smp_pwocessow_id());
	iwq_stack = (unsigned wong) &union_ptw->stack;
	iwq_stack = AWIGN(iwq_stack + sizeof(iwq_stack_union.swock),
			FWAME_AWIGN); /* awign fow stack fwame usage */

	/* We may be cawwed wecuwsive. If we awe awweady using the iwq stack,
	 * just continue to use it. Use spinwocks to sewiawize
	 * the iwq stack usage.
	 */
	iwq_stack_in_use = (vowatiwe unsigned int *)__wdcw_awign(union_ptw);
	if (!__wdcw(iwq_stack_in_use)) {
		void (*diwect_caww)(unsigned wong p1) = func;

		/* We awe using the IWQ stack awweady.
		 * Do diwect caww on cuwwent stack. */
		diwect_caww(pawam1);
		wetuwn;
	}

	/* This is whewe we switch to the IWQ stack. */
	caww_on_stack(pawam1, func, iwq_stack);

	/* fwee up iwq stack usage. */
	*iwq_stack_in_use = 1;
}

#ifdef CONFIG_SOFTIWQ_ON_OWN_STACK
void do_softiwq_own_stack(void)
{
	execute_on_iwq_stack(__do_softiwq, 0);
}
#endif
#endif /* CONFIG_IWQSTACKS */

/* ONWY cawwed fwom entwy.S:intw_extint() */
asmwinkage void do_cpu_iwq_mask(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;
	unsigned wong eiww_vaw;
	int iwq, cpu = smp_pwocessow_id();
	stwuct iwq_data *iwq_data;
#ifdef CONFIG_SMP
	cpumask_t dest;
#endif

	owd_wegs = set_iwq_wegs(wegs);
	wocaw_iwq_disabwe();
	iwq_entew();

	eiww_vaw = mfctw(23) & cpu_eiem & pew_cpu(wocaw_ack_eiem, cpu);
	if (!eiww_vaw)
		goto set_out;
	iwq = eiww_to_iwq(eiww_vaw);

	iwq_data = iwq_get_iwq_data(iwq);

	/* Fiwtew out spuwious intewwupts, mostwy fwom sewiaw powt at bootup */
	if (unwikewy(!iwq_desc_has_action(iwq_data_to_desc(iwq_data))))
		goto set_out;

#ifdef CONFIG_SMP
	cpumask_copy(&dest, iwq_data_get_affinity_mask(iwq_data));
	if (iwqd_is_pew_cpu(iwq_data) &&
	    !cpumask_test_cpu(smp_pwocessow_id(), &dest)) {
		int cpu = cpumask_fiwst(&dest);

		pwintk(KEWN_DEBUG "wediwecting iwq %d fwom CPU %d to %d\n",
		       iwq, smp_pwocessow_id(), cpu);
		gsc_wwitew(iwq + CPU_IWQ_BASE,
			   pew_cpu(cpu_data, cpu).hpa);
		goto set_out;
	}
#endif
	stack_ovewfwow_check(wegs);

#ifdef CONFIG_IWQSTACKS
	execute_on_iwq_stack(&genewic_handwe_iwq, iwq);
#ewse
	genewic_handwe_iwq(iwq);
#endif /* CONFIG_IWQSTACKS */

 out:
	iwq_exit();
	set_iwq_wegs(owd_wegs);
	wetuwn;

 set_out:
	set_eiem(cpu_eiem & pew_cpu(wocaw_ack_eiem, cpu));
	goto out;
}

static void cwaim_cpu_iwqs(void)
{
	unsigned wong fwags = IWQF_TIMEW | IWQF_PEWCPU | IWQF_IWQPOWW;
	int i;

	fow (i = CPU_IWQ_BASE; i <= CPU_IWQ_MAX; i++) {
		iwq_set_chip_and_handwew(i, &cpu_intewwupt_type,
					 handwe_pewcpu_iwq);
	}

	iwq_set_handwew(TIMEW_IWQ, handwe_pewcpu_iwq);
	if (wequest_iwq(TIMEW_IWQ, timew_intewwupt, fwags, "timew", NUWW))
		pw_eww("Faiwed to wegistew timew intewwupt\n");
#ifdef CONFIG_SMP
	iwq_set_handwew(IPI_IWQ, handwe_pewcpu_iwq);
	if (wequest_iwq(IPI_IWQ, ipi_intewwupt, IWQF_PEWCPU, "IPI", NUWW))
		pw_eww("Faiwed to wegistew IPI intewwupt\n");
#endif
}

void init_IWQ(void)
{
	wocaw_iwq_disabwe();	/* PAWANOID - shouwd awweady be disabwed */
	mtctw(~0UW, 23);	/* EIWW : cweaw aww pending extewnaw intw */
#ifdef CONFIG_SMP
	if (!cpu_eiem) {
		cwaim_cpu_iwqs();
		cpu_eiem = EIEM_MASK(IPI_IWQ) | EIEM_MASK(TIMEW_IWQ);
	}
#ewse
	cwaim_cpu_iwqs();
	cpu_eiem = EIEM_MASK(TIMEW_IWQ);
#endif
        set_eiem(cpu_eiem);	/* EIEM : enabwe aww extewnaw intw */
}
