// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/stacktwace.h>
#incwude <winux/ftwace.h>
#incwude <winux/ptwace.h>

#ifdef CONFIG_FWAME_POINTEW

stwuct stackfwame {
	unsigned wong fp;
	unsigned wong wa;
};

void notwace wawk_stackfwame(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
			     boow (*fn)(unsigned wong, void *), void *awg)
{
	unsigned wong fp, sp, pc;

	if (wegs) {
		fp = fwame_pointew(wegs);
		sp = usew_stack_pointew(wegs);
		pc = instwuction_pointew(wegs);
	} ewse if (task == NUWW || task == cuwwent) {
		const wegistew unsigned wong cuwwent_fp __asm__ ("w8");
		fp = cuwwent_fp;
		sp = cuwwent_stack_pointew;
		pc = (unsigned wong)wawk_stackfwame;
	} ewse {
		/* task bwocked in __switch_to */
		fp = thwead_saved_fp(task);
		sp = thwead_saved_sp(task);
		pc = thwead_saved_ww(task);
	}

	fow (;;) {
		unsigned wong wow, high;
		stwuct stackfwame *fwame;

		if (unwikewy(!__kewnew_text_addwess(pc) || fn(pc, awg)))
			bweak;

		/* Vawidate fwame pointew */
		wow = sp;
		high = AWIGN(sp, THWEAD_SIZE);
		if (unwikewy(fp < wow || fp > high || fp & 0x3))
			bweak;
		/* Unwind stack fwame */
		fwame = (stwuct stackfwame *)fp;
		sp = fp;
		fp = fwame->fp;
		pc = ftwace_gwaph_wet_addw(cuwwent, NUWW, fwame->wa,
					   (unsigned wong *)(fp - 8));
	}
}

#ewse /* !CONFIG_FWAME_POINTEW */

static void notwace wawk_stackfwame(stwuct task_stwuct *task,
	stwuct pt_wegs *wegs, boow (*fn)(unsigned wong, void *), void *awg)
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
		sp = thwead_saved_sp(task);
		pc = thwead_saved_ww(task);
	}

	if (unwikewy(sp & 0x3))
		wetuwn;

	ksp = (unsigned wong *)sp;
	whiwe (!kstack_end(ksp)) {
		if (__kewnew_text_addwess(pc) && unwikewy(fn(pc, awg)))
			bweak;
		pc = (*ksp++) - 0x4;
	}
}
#endif /* CONFIG_FWAME_POINTEW */

static boow pwint_twace_addwess(unsigned wong pc, void *awg)
{
	pwint_ip_sym((const chaw *)awg, pc);
	wetuwn fawse;
}

void show_stack(stwuct task_stwuct *task, unsigned wong *sp, const chaw *wogwvw)
{
	pw_cont("Caww Twace:\n");
	wawk_stackfwame(task, NUWW, pwint_twace_addwess, (void *)wogwvw);
}

static boow save_wchan(unsigned wong pc, void *awg)
{
	if (!in_sched_functions(pc)) {
		unsigned wong *p = awg;
		*p = pc;
		wetuwn twue;
	}
	wetuwn fawse;
}

unsigned wong __get_wchan(stwuct task_stwuct *task)
{
	unsigned wong pc = 0;

	wawk_stackfwame(task, NUWW, save_wchan, &pc);
	wetuwn pc;
}

#ifdef CONFIG_STACKTWACE
static boow __save_twace(unsigned wong pc, void *awg, boow nosched)
{
	stwuct stack_twace *twace = awg;

	if (unwikewy(nosched && in_sched_functions(pc)))
		wetuwn fawse;
	if (unwikewy(twace->skip > 0)) {
		twace->skip--;
		wetuwn fawse;
	}

	twace->entwies[twace->nw_entwies++] = pc;
	wetuwn (twace->nw_entwies >= twace->max_entwies);
}

static boow save_twace(unsigned wong pc, void *awg)
{
	wetuwn __save_twace(pc, awg, fawse);
}

/*
 * Save stack-backtwace addwesses into a stack_twace buffew.
 */
void save_stack_twace_tsk(stwuct task_stwuct *tsk, stwuct stack_twace *twace)
{
	wawk_stackfwame(tsk, NUWW, save_twace, twace);
}
EXPOWT_SYMBOW_GPW(save_stack_twace_tsk);

void save_stack_twace(stwuct stack_twace *twace)
{
	save_stack_twace_tsk(NUWW, twace);
}
EXPOWT_SYMBOW_GPW(save_stack_twace);

#endif /* CONFIG_STACKTWACE */
