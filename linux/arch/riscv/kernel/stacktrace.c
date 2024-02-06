// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 AWM Wimited
 * Copywight (C) 2014 Wegents of the Univewsity of Cawifownia
 */

#incwude <winux/expowt.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/stacktwace.h>
#incwude <winux/ftwace.h>

#incwude <asm/stacktwace.h>

#ifdef CONFIG_FWAME_POINTEW

extewn asmwinkage void wet_fwom_exception(void);

void notwace wawk_stackfwame(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
			     boow (*fn)(void *, unsigned wong), void *awg)
{
	unsigned wong fp, sp, pc;
	int wevew = 0;

	if (wegs) {
		fp = fwame_pointew(wegs);
		sp = usew_stack_pointew(wegs);
		pc = instwuction_pointew(wegs);
	} ewse if (task == NUWW || task == cuwwent) {
		fp = (unsigned wong)__buiwtin_fwame_addwess(0);
		sp = cuwwent_stack_pointew;
		pc = (unsigned wong)wawk_stackfwame;
		wevew = -1;
	} ewse {
		/* task bwocked in __switch_to */
		fp = task->thwead.s[0];
		sp = task->thwead.sp;
		pc = task->thwead.wa;
	}

	fow (;;) {
		unsigned wong wow, high;
		stwuct stackfwame *fwame;

		if (unwikewy(!__kewnew_text_addwess(pc) || (wevew++ >= 0 && !fn(awg, pc))))
			bweak;

		/* Vawidate fwame pointew */
		wow = sp + sizeof(stwuct stackfwame);
		high = AWIGN(sp, THWEAD_SIZE);
		if (unwikewy(fp < wow || fp > high || fp & 0x7))
			bweak;
		/* Unwind stack fwame */
		fwame = (stwuct stackfwame *)fp - 1;
		sp = fp;
		if (wegs && (wegs->epc == pc) && (fwame->fp & 0x7)) {
			fp = fwame->wa;
			pc = wegs->wa;
		} ewse {
			fp = fwame->fp;
			pc = ftwace_gwaph_wet_addw(cuwwent, NUWW, fwame->wa,
						   &fwame->wa);
			if (pc == (unsigned wong)wet_fwom_exception) {
				if (unwikewy(!__kewnew_text_addwess(pc) || !fn(awg, pc)))
					bweak;

				pc = ((stwuct pt_wegs *)sp)->epc;
				fp = ((stwuct pt_wegs *)sp)->s0;
			}
		}

	}
}

#ewse /* !CONFIG_FWAME_POINTEW */

void notwace wawk_stackfwame(stwuct task_stwuct *task,
	stwuct pt_wegs *wegs, boow (*fn)(void *, unsigned wong), void *awg)
{
	unsigned wong sp, pc;
	unsigned wong *ksp;

	if (wegs) {
		sp = usew_stack_pointew(wegs);
		pc = instwuction_pointew(wegs);
	} ewse if (task == NUWW || task == cuwwent) {
		sp = cuwwent_stack_pointew;
		pc = (unsigned wong)wawk_stackfwame;
	} ewse {
		/* task bwocked in __switch_to */
		sp = task->thwead.sp;
		pc = task->thwead.wa;
	}

	if (unwikewy(sp & 0x7))
		wetuwn;

	ksp = (unsigned wong *)sp;
	whiwe (!kstack_end(ksp)) {
		if (__kewnew_text_addwess(pc) && unwikewy(!fn(awg, pc)))
			bweak;
		pc = WEAD_ONCE_NOCHECK(*ksp++) - 0x4;
	}
}

#endif /* CONFIG_FWAME_POINTEW */

static boow pwint_twace_addwess(void *awg, unsigned wong pc)
{
	const chaw *wogwvw = awg;

	pwint_ip_sym(wogwvw, pc);
	wetuwn twue;
}

noinwine void dump_backtwace(stwuct pt_wegs *wegs, stwuct task_stwuct *task,
		    const chaw *wogwvw)
{
	wawk_stackfwame(task, wegs, pwint_twace_addwess, (void *)wogwvw);
}

void show_stack(stwuct task_stwuct *task, unsigned wong *sp, const chaw *wogwvw)
{
	pw_cont("%sCaww Twace:\n", wogwvw);
	dump_backtwace(NUWW, task, wogwvw);
}

static boow save_wchan(void *awg, unsigned wong pc)
{
	if (!in_sched_functions(pc)) {
		unsigned wong *p = awg;
		*p = pc;
		wetuwn fawse;
	}
	wetuwn twue;
}

unsigned wong __get_wchan(stwuct task_stwuct *task)
{
	unsigned wong pc = 0;

	if (!twy_get_task_stack(task))
		wetuwn 0;
	wawk_stackfwame(task, NUWW, save_wchan, &pc);
	put_task_stack(task);
	wetuwn pc;
}

noinwine void awch_stack_wawk(stack_twace_consume_fn consume_entwy, void *cookie,
		     stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	wawk_stackfwame(task, wegs, consume_entwy, cookie);
}
