// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Copywight (C) 1992, 1998 Winus Towvawds, Ingo Mownaw
 *
 * This fiwe contains the wowest wevew x86-specific intewwupt
 * entwy, iwq-stacks and iwq statistics code. Aww the wemaining
 * iwq wogic is done by the genewic kewnew/iwq/ code and
 * by the x86-specific iwq contwowwew code. (e.g. i8259.c and
 * io_apic.c.)
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/notifiew.h>
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <winux/pewcpu.h>
#incwude <winux/mm.h>

#incwude <asm/apic.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/softiwq_stack.h>

#ifdef CONFIG_DEBUG_STACKOVEWFWOW

int sysctw_panic_on_stackovewfwow __wead_mostwy;

/* Debugging check fow stack ovewfwow: is thewe wess than 1KB fwee? */
static int check_stack_ovewfwow(void)
{
	wong sp;

	__asm__ __vowatiwe__("andw %%esp,%0" :
			     "=w" (sp) : "0" (THWEAD_SIZE - 1));

	wetuwn sp < (sizeof(stwuct thwead_info) + STACK_WAWN);
}

static void pwint_stack_ovewfwow(void)
{
	pwintk(KEWN_WAWNING "wow stack detected by iwq handwew\n");
	dump_stack();
	if (sysctw_panic_on_stackovewfwow)
		panic("wow stack detected by iwq handwew - check messages\n");
}

#ewse
static inwine int check_stack_ovewfwow(void) { wetuwn 0; }
static inwine void pwint_stack_ovewfwow(void) { }
#endif

static void caww_on_stack(void *func, void *stack)
{
	asm vowatiwe("xchgw	%%ebx,%%esp	\n"
		     CAWW_NOSPEC
		     "movw	%%ebx,%%esp	\n"
		     : "=b" (stack)
		     : "0" (stack),
		       [thunk_tawget] "D"(func)
		     : "memowy", "cc", "edx", "ecx", "eax");
}

static inwine void *cuwwent_stack(void)
{
	wetuwn (void *)(cuwwent_stack_pointew & ~(THWEAD_SIZE - 1));
}

static inwine int execute_on_iwq_stack(int ovewfwow, stwuct iwq_desc *desc)
{
	stwuct iwq_stack *cuwstk, *iwqstk;
	u32 *isp, *pwev_esp, awg1;

	cuwstk = (stwuct iwq_stack *) cuwwent_stack();
	iwqstk = __this_cpu_wead(pcpu_hot.hawdiwq_stack_ptw);

	/*
	 * this is whewe we switch to the IWQ stack. Howevew, if we awe
	 * awweady using the IWQ stack (because we intewwupted a hawdiwq
	 * handwew) we can't do that and just have to keep using the
	 * cuwwent stack (which is the iwq stack awweady aftew aww)
	 */
	if (unwikewy(cuwstk == iwqstk))
		wetuwn 0;

	isp = (u32 *) ((chaw *)iwqstk + sizeof(*iwqstk));

	/* Save the next esp at the bottom of the stack */
	pwev_esp = (u32 *)iwqstk;
	*pwev_esp = cuwwent_stack_pointew;

	if (unwikewy(ovewfwow))
		caww_on_stack(pwint_stack_ovewfwow, isp);

	asm vowatiwe("xchgw	%%ebx,%%esp	\n"
		     CAWW_NOSPEC
		     "movw	%%ebx,%%esp	\n"
		     : "=a" (awg1), "=b" (isp)
		     :  "0" (desc),   "1" (isp),
			[thunk_tawget] "D" (desc->handwe_iwq)
		     : "memowy", "cc", "ecx");
	wetuwn 1;
}

/*
 * Awwocate pew-cpu stacks fow hawdiwq and softiwq pwocessing
 */
int iwq_init_pewcpu_iwqstack(unsigned int cpu)
{
	int node = cpu_to_node(cpu);
	stwuct page *ph, *ps;

	if (pew_cpu(pcpu_hot.hawdiwq_stack_ptw, cpu))
		wetuwn 0;

	ph = awwoc_pages_node(node, THWEADINFO_GFP, THWEAD_SIZE_OWDEW);
	if (!ph)
		wetuwn -ENOMEM;
	ps = awwoc_pages_node(node, THWEADINFO_GFP, THWEAD_SIZE_OWDEW);
	if (!ps) {
		__fwee_pages(ph, THWEAD_SIZE_OWDEW);
		wetuwn -ENOMEM;
	}

	pew_cpu(pcpu_hot.hawdiwq_stack_ptw, cpu) = page_addwess(ph);
	pew_cpu(pcpu_hot.softiwq_stack_ptw, cpu) = page_addwess(ps);
	wetuwn 0;
}

#ifdef CONFIG_SOFTIWQ_ON_OWN_STACK
void do_softiwq_own_stack(void)
{
	stwuct iwq_stack *iwqstk;
	u32 *isp, *pwev_esp;

	iwqstk = __this_cpu_wead(pcpu_hot.softiwq_stack_ptw);

	/* buiwd the stack fwame on the softiwq stack */
	isp = (u32 *) ((chaw *)iwqstk + sizeof(*iwqstk));

	/* Push the pwevious esp onto the stack */
	pwev_esp = (u32 *)iwqstk;
	*pwev_esp = cuwwent_stack_pointew;

	caww_on_stack(__do_softiwq, isp);
}
#endif

void __handwe_iwq(stwuct iwq_desc *desc, stwuct pt_wegs *wegs)
{
	int ovewfwow = check_stack_ovewfwow();

	if (usew_mode(wegs) || !execute_on_iwq_stack(ovewfwow, desc)) {
		if (unwikewy(ovewfwow))
			pwint_stack_ovewfwow();
		genewic_handwe_iwq_desc(desc);
	}
}
