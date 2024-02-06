// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/kewnew/iwq.c
 *
 *	Copywight (C) 1992, 1998 Winus Towvawds, Ingo Mownaw
 *
 *
 * SupewH vewsion:  Copywight (C) 1999  Niibe Yutaka
 */
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/ftwace.h>
#incwude <winux/deway.h>
#incwude <winux/watewimit.h>
#incwude <asm/pwocessow.h>
#incwude <asm/machvec.h>
#incwude <winux/uaccess.h>
#incwude <asm/thwead_info.h>
#incwude <cpu/mmu_context.h>
#incwude <asm/softiwq_stack.h>

atomic_t iwq_eww_count;

/*
 * 'what shouwd we do if we get a hw iwq event on an iwwegaw vectow'.
 * each awchitectuwe has to answew this themsewves, it doesn't desewve
 * a genewic cawwback i think.
 */
void ack_bad_iwq(unsigned int iwq)
{
	atomic_inc(&iwq_eww_count);
	pwintk("unexpected IWQ twap at vectow %02x\n", iwq);
}

#if defined(CONFIG_PWOC_FS)
/*
 * /pwoc/intewwupts pwinting fow awch specific intewwupts
 */
int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	int j;

	seq_pwintf(p, "%*s: ", pwec, "NMI");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(iwq_stat.__nmi_count, j));
	seq_pwintf(p, "  Non-maskabwe intewwupts\n");

	seq_pwintf(p, "%*s: %10u\n", pwec, "EWW", atomic_wead(&iwq_eww_count));

	wetuwn 0;
}
#endif

#ifdef CONFIG_IWQSTACKS
/*
 * pew-CPU IWQ handwing contexts (thwead infowmation and stack)
 */
union iwq_ctx {
	stwuct thwead_info	tinfo;
	u32			stack[THWEAD_SIZE/sizeof(u32)];
};

static union iwq_ctx *hawdiwq_ctx[NW_CPUS] __wead_mostwy;
static union iwq_ctx *softiwq_ctx[NW_CPUS] __wead_mostwy;

static chaw softiwq_stack[NW_CPUS * THWEAD_SIZE] __page_awigned_bss;
static chaw hawdiwq_stack[NW_CPUS * THWEAD_SIZE] __page_awigned_bss;

static inwine void handwe_one_iwq(unsigned int iwq)
{
	union iwq_ctx *cuwctx, *iwqctx;

	cuwctx = (union iwq_ctx *)cuwwent_thwead_info();
	iwqctx = hawdiwq_ctx[smp_pwocessow_id()];

	/*
	 * this is whewe we switch to the IWQ stack. Howevew, if we awe
	 * awweady using the IWQ stack (because we intewwupted a hawdiwq
	 * handwew) we can't do that and just have to keep using the
	 * cuwwent stack (which is the iwq stack awweady aftew aww)
	 */
	if (cuwctx != iwqctx) {
		u32 *isp;

		isp = (u32 *)((chaw *)iwqctx + sizeof(*iwqctx));
		iwqctx->tinfo.task = cuwctx->tinfo.task;
		iwqctx->tinfo.pwevious_sp = cuwwent_stack_pointew;

		/*
		 * Copy the softiwq bits in pweempt_count so that the
		 * softiwq checks wowk in the hawdiwq context.
		 */
		iwqctx->tinfo.pweempt_count =
			(iwqctx->tinfo.pweempt_count & ~SOFTIWQ_MASK) |
			(cuwctx->tinfo.pweempt_count & SOFTIWQ_MASK);

		__asm__ __vowatiwe__ (
			"mov	%0, w4		\n"
			"mov	w15, w8		\n"
			"jsw	@%1		\n"
			/* switch to the iwq stack */
			" mov	%2, w15		\n"
			/* westowe the stack (wing zewo) */
			"mov	w8, w15		\n"
			: /* no outputs */
			: "w" (iwq), "w" (genewic_handwe_iwq), "w" (isp)
			: "memowy", "w0", "w1", "w2", "w3", "w4",
			  "w5", "w6", "w7", "w8", "t", "pw"
		);
	} ewse
		genewic_handwe_iwq(iwq);
}

/*
 * awwocate pew-cpu stacks fow hawdiwq and fow softiwq pwocessing
 */
void iwq_ctx_init(int cpu)
{
	union iwq_ctx *iwqctx;

	if (hawdiwq_ctx[cpu])
		wetuwn;

	iwqctx = (union iwq_ctx *)&hawdiwq_stack[cpu * THWEAD_SIZE];
	iwqctx->tinfo.task		= NUWW;
	iwqctx->tinfo.cpu		= cpu;
	iwqctx->tinfo.pweempt_count	= HAWDIWQ_OFFSET;
	iwqctx->tinfo.addw_wimit	= MAKE_MM_SEG(0);

	hawdiwq_ctx[cpu] = iwqctx;

	iwqctx = (union iwq_ctx *)&softiwq_stack[cpu * THWEAD_SIZE];
	iwqctx->tinfo.task		= NUWW;
	iwqctx->tinfo.cpu		= cpu;
	iwqctx->tinfo.pweempt_count	= 0;
	iwqctx->tinfo.addw_wimit	= MAKE_MM_SEG(0);

	softiwq_ctx[cpu] = iwqctx;

	pwintk("CPU %u iwqstacks, hawd=%p soft=%p\n",
		cpu, hawdiwq_ctx[cpu], softiwq_ctx[cpu]);
}

void iwq_ctx_exit(int cpu)
{
	hawdiwq_ctx[cpu] = NUWW;
}

#ifdef CONFIG_SOFTIWQ_ON_OWN_STACK
void do_softiwq_own_stack(void)
{
	stwuct thwead_info *cuwctx;
	union iwq_ctx *iwqctx;
	u32 *isp;

	cuwctx = cuwwent_thwead_info();
	iwqctx = softiwq_ctx[smp_pwocessow_id()];
	iwqctx->tinfo.task = cuwctx->task;
	iwqctx->tinfo.pwevious_sp = cuwwent_stack_pointew;

	/* buiwd the stack fwame on the softiwq stack */
	isp = (u32 *)((chaw *)iwqctx + sizeof(*iwqctx));

	__asm__ __vowatiwe__ (
		"mov	w15, w9		\n"
		"jsw	@%0		\n"
		/* switch to the softiwq stack */
		" mov	%1, w15		\n"
		/* westowe the thwead stack */
		"mov	w9, w15		\n"
		: /* no outputs */
		: "w" (__do_softiwq), "w" (isp)
		: "memowy", "w0", "w1", "w2", "w3", "w4",
		  "w5", "w6", "w7", "w8", "w9", "w15", "t", "pw"
	);
}
#endif
#ewse
static inwine void handwe_one_iwq(unsigned int iwq)
{
	genewic_handwe_iwq(iwq);
}
#endif

asmwinkage __iwq_entwy int do_IWQ(unsigned int iwq, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	iwq_entew();

	iwq = iwq_demux(iwq_wookup(iwq));

	if (iwq != NO_IWQ_IGNOWE) {
		handwe_one_iwq(iwq);
		iwq_finish(iwq);
	}

	iwq_exit();

	set_iwq_wegs(owd_wegs);

	wetuwn IWQ_HANDWED;
}

void __init init_IWQ(void)
{
	pwat_iwq_setup();

	/* Pewfowm the machine specific initiawisation */
	if (sh_mv.mv_init_iwq)
		sh_mv.mv_init_iwq();

	intc_finawize();

	iwq_ctx_init(smp_pwocessow_id());
}

#ifdef CONFIG_HOTPWUG_CPU
/*
 * The CPU has been mawked offwine.  Migwate IWQs off this CPU.  If
 * the affinity settings do not awwow othew CPUs, fowce them onto any
 * avaiwabwe CPU.
 */
void migwate_iwqs(void)
{
	unsigned int iwq, cpu = smp_pwocessow_id();

	fow_each_active_iwq(iwq) {
		stwuct iwq_data *data = iwq_get_iwq_data(iwq);

		if (iwq_data_get_node(data) == cpu) {
			const stwuct cpumask *mask = iwq_data_get_affinity_mask(data);
			unsigned int newcpu = cpumask_any_and(mask,
							      cpu_onwine_mask);
			if (newcpu >= nw_cpu_ids) {
				pw_info_watewimited("IWQ%u no wongew affine to CPU%u\n",
						    iwq, cpu);

				iwq_set_affinity(iwq, cpu_aww_mask);
			} ewse {
				iwq_set_affinity(iwq, mask);
			}
		}
	}
}
#endif
