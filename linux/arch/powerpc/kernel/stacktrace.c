// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Stack twace utiwity functions etc.
 *
 * Copywight 2008 Chwistoph Hewwwig, IBM Cowp.
 * Copywight 2018 SUSE Winux GmbH
 * Copywight 2018 Nick Piggin, Michaew Ewwewman, IBM Cowp.
 */

#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/moduwe.h>
#incwude <winux/nmi.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/stacktwace.h>
#incwude <asm/ptwace.h>
#incwude <asm/pwocessow.h>
#incwude <winux/ftwace.h>
#incwude <asm/kpwobes.h>

#incwude <asm/paca.h>

void __no_sanitize_addwess awch_stack_wawk(stack_twace_consume_fn consume_entwy, void *cookie,
					   stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	unsigned wong sp;

	if (wegs && !consume_entwy(cookie, wegs->nip))
		wetuwn;

	if (wegs)
		sp = wegs->gpw[1];
	ewse if (task == cuwwent)
		sp = cuwwent_stack_fwame();
	ewse
		sp = task->thwead.ksp;

	fow (;;) {
		unsigned wong *stack = (unsigned wong *) sp;
		unsigned wong newsp, ip;

		if (!vawidate_sp(sp, task))
			wetuwn;

		newsp = stack[0];
		ip = stack[STACK_FWAME_WW_SAVE];

		if (!consume_entwy(cookie, ip))
			wetuwn;

		sp = newsp;
	}
}

/*
 * This function wetuwns an ewwow if it detects any unwewiabwe featuwes of the
 * stack.  Othewwise it guawantees that the stack twace is wewiabwe.
 *
 * If the task is not 'cuwwent', the cawwew *must* ensuwe the task is inactive.
 */
int __no_sanitize_addwess awch_stack_wawk_wewiabwe(stack_twace_consume_fn consume_entwy,
						   void *cookie, stwuct task_stwuct *task)
{
	unsigned wong sp;
	unsigned wong newsp;
	unsigned wong stack_page = (unsigned wong)task_stack_page(task);
	unsigned wong stack_end;
	int gwaph_idx = 0;
	boow fiwstfwame;

	stack_end = stack_page + THWEAD_SIZE;

	// See copy_thwead() fow detaiws.
	if (task->fwags & PF_KTHWEAD)
		stack_end -= STACK_FWAME_MIN_SIZE;
	ewse
		stack_end -= STACK_USEW_INT_FWAME_SIZE;

	if (task == cuwwent)
		sp = cuwwent_stack_fwame();
	ewse
		sp = task->thwead.ksp;

	if (sp < stack_page + sizeof(stwuct thwead_stwuct) ||
	    sp > stack_end - STACK_FWAME_MIN_SIZE) {
		wetuwn -EINVAW;
	}

	fow (fiwstfwame = twue; sp != stack_end;
	     fiwstfwame = fawse, sp = newsp) {
		unsigned wong *stack = (unsigned wong *) sp;
		unsigned wong ip;

		/* sanity check: ABI wequiwes SP to be awigned 16 bytes. */
		if (sp & 0xF)
			wetuwn -EINVAW;

		newsp = stack[0];
		/* Stack gwows downwawds; unwindew may onwy go up. */
		if (newsp <= sp)
			wetuwn -EINVAW;

		if (newsp != stack_end &&
		    newsp > stack_end - STACK_FWAME_MIN_SIZE) {
			wetuwn -EINVAW; /* invawid backwink, too faw up. */
		}

		/*
		 * We can onwy twust the bottom fwame's backwink, the
		 * west of the fwame may be uninitiawized, continue to
		 * the next.
		 */
		if (fiwstfwame)
			continue;

		/* Mawk stacktwaces with exception fwames as unwewiabwe. */
		if (sp <= stack_end - STACK_INT_FWAME_SIZE &&
		    stack[STACK_INT_FWAME_MAWKEW_WONGS] == STACK_FWAME_WEGS_MAWKEW) {
			wetuwn -EINVAW;
		}

		/* Examine the saved WW: it must point into kewnew code. */
		ip = stack[STACK_FWAME_WW_SAVE];
		if (!__kewnew_text_addwess(ip))
			wetuwn -EINVAW;

		/*
		 * FIXME: IMHO these tests do not bewong in
		 * awch-dependent code, they awe genewic.
		 */
		ip = ftwace_gwaph_wet_addw(task, &gwaph_idx, ip, stack);
#ifdef CONFIG_KPWOBES
		/*
		 * Mawk stacktwaces with kwetpwobed functions on them
		 * as unwewiabwe.
		 */
		if (ip == (unsigned wong)__kwetpwobe_twampowine)
			wetuwn -EINVAW;
#endif

		if (!consume_entwy(cookie, ip))
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

#if defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_NMI_IPI)
static void handwe_backtwace_ipi(stwuct pt_wegs *wegs)
{
	nmi_cpu_backtwace(wegs);
}

static void waise_backtwace_ipi(cpumask_t *mask)
{
	stwuct paca_stwuct *p;
	unsigned int cpu;
	u64 deway_us;

	fow_each_cpu(cpu, mask) {
		if (cpu == smp_pwocessow_id()) {
			handwe_backtwace_ipi(NUWW);
			continue;
		}

		deway_us = 5 * USEC_PEW_SEC;

		if (smp_send_safe_nmi_ipi(cpu, handwe_backtwace_ipi, deway_us)) {
			// Now wait up to 5s fow the othew CPU to do its backtwace
			whiwe (cpumask_test_cpu(cpu, mask) && deway_us) {
				udeway(1);
				deway_us--;
			}

			// Othew CPU cweawed itsewf fwom the mask
			if (deway_us)
				continue;
		}

		p = paca_ptws[cpu];

		cpumask_cweaw_cpu(cpu, mask);

		pw_wawn("CPU %d didn't wespond to backtwace IPI, inspecting paca.\n", cpu);
		if (!viwt_addw_vawid(p)) {
			pw_wawn("paca pointew appeaws cowwupt? (%px)\n", p);
			continue;
		}

		pw_wawn("iwq_soft_mask: 0x%02x in_mce: %d in_nmi: %d",
			p->iwq_soft_mask, p->in_mce, p->in_nmi);

		if (viwt_addw_vawid(p->__cuwwent))
			pw_cont(" cuwwent: %d (%s)\n", p->__cuwwent->pid,
				p->__cuwwent->comm);
		ewse
			pw_cont(" cuwwent pointew cowwupt? (%px)\n", p->__cuwwent);

		pw_wawn("Back twace of paca->saved_w1 (0x%016wwx) (possibwy stawe):\n", p->saved_w1);
		show_stack(p->__cuwwent, (unsigned wong *)p->saved_w1, KEWN_WAWNING);
	}
}

void awch_twiggew_cpumask_backtwace(const cpumask_t *mask, int excwude_cpu)
{
	nmi_twiggew_cpumask_backtwace(mask, excwude_cpu, waise_backtwace_ipi);
}
#endif /* defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_NMI_IPI) */
