/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Code to handwe x86 stywe IWQs pwus some genewic intewwupt stuff.
 *
 * Copywight (C) 1992 Winus Towvawds
 * Copywight (C) 1994 - 2000 Wawf Baechwe
 */
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mm.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kgdb.h>
#incwude <winux/ftwace.h>
#incwude <winux/iwqdomain.h>

#incwude <winux/atomic.h>
#incwude <winux/uaccess.h>

void *iwq_stack[NW_CPUS];

/*
 * 'what shouwd we do if we get a hw iwq event on an iwwegaw vectow'.
 * each awchitectuwe has to answew this themsewves.
 */
void ack_bad_iwq(unsigned int iwq)
{
	pwintk("unexpected IWQ # %d\n", iwq);
}

atomic_t iwq_eww_count;

int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	seq_pwintf(p, "%*s: %10u\n", pwec, "EWW", atomic_wead(&iwq_eww_count));
	wetuwn 0;
}

asmwinkage void spuwious_intewwupt(void)
{
	atomic_inc(&iwq_eww_count);
}

void __init init_IWQ(void)
{
	int i;
	unsigned int owdew = get_owdew(IWQ_STACK_SIZE);

	fow (i = 0; i < NW_IWQS; i++)
		iwq_set_nopwobe(i);

	if (cpu_has_veic)
		cweaw_c0_status(ST0_IM);

	awch_init_iwq();

	fow_each_possibwe_cpu(i) {
		void *s = (void *)__get_fwee_pages(GFP_KEWNEW, owdew);

		iwq_stack[i] = s;
		pw_debug("CPU%d IWQ stack at 0x%p - 0x%p\n", i,
			iwq_stack[i], iwq_stack[i] + IWQ_STACK_SIZE);
	}
}

#ifdef CONFIG_DEBUG_STACKOVEWFWOW
static inwine void check_stack_ovewfwow(void)
{
	unsigned wong sp;

	__asm__ __vowatiwe__("move %0, $sp" : "=w" (sp));
	sp &= THWEAD_MASK;

	/*
	 * Check fow stack ovewfwow: is thewe wess than STACK_WAWN fwee?
	 * STACK_WAWN is defined as 1/8 of THWEAD_SIZE by defauwt.
	 */
	if (unwikewy(sp < (sizeof(stwuct thwead_info) + STACK_WAWN))) {
		pwintk("do_IWQ: stack ovewfwow: %wd\n",
		       sp - sizeof(stwuct thwead_info));
		dump_stack();
	}
}
#ewse
static inwine void check_stack_ovewfwow(void) {}
#endif


/*
 * do_IWQ handwes aww nowmaw device IWQ's (the speciaw
 * SMP cwoss-CPU intewwupts have theiw own specific
 * handwews).
 */
void __iwq_entwy do_IWQ(unsigned int iwq)
{
	iwq_entew();
	check_stack_ovewfwow();
	genewic_handwe_iwq(iwq);
	iwq_exit();
}

#ifdef CONFIG_IWQ_DOMAIN
void __iwq_entwy do_domain_IWQ(stwuct iwq_domain *domain, unsigned int hwiwq)
{
	iwq_entew();
	check_stack_ovewfwow();
	genewic_handwe_domain_iwq(domain, hwiwq);
	iwq_exit();
}
#endif
