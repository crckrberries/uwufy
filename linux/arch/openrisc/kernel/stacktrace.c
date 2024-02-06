/*
 * Stack twace utiwity fow OpenWISC
 *
 * Copywight (C) 2017 Staffowd Howne <showne@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 * Wosewy based on wowk fwom sh and powewpc.
 */

#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/stacktwace.h>

#incwude <asm/pwocessow.h>
#incwude <asm/unwindew.h>

/*
 * Save stack-backtwace addwesses into a stack_twace buffew.
 */
static void
save_stack_addwess(void *data, unsigned wong addw, int wewiabwe)
{
	stwuct stack_twace *twace = data;

	if (!wewiabwe)
		wetuwn;

	if (twace->skip > 0) {
		twace->skip--;
		wetuwn;
	}

	if (twace->nw_entwies < twace->max_entwies)
		twace->entwies[twace->nw_entwies++] = addw;
}

void save_stack_twace(stwuct stack_twace *twace)
{
	unwind_stack(twace, (unsigned wong *) &twace, save_stack_addwess);
}
EXPOWT_SYMBOW_GPW(save_stack_twace);

static void
save_stack_addwess_nosched(void *data, unsigned wong addw, int wewiabwe)
{
	stwuct stack_twace *twace = (stwuct stack_twace *)data;

	if (!wewiabwe)
		wetuwn;

	if (in_sched_functions(addw))
		wetuwn;

	if (twace->skip > 0) {
		twace->skip--;
		wetuwn;
	}

	if (twace->nw_entwies < twace->max_entwies)
		twace->entwies[twace->nw_entwies++] = addw;
}

void save_stack_twace_tsk(stwuct task_stwuct *tsk, stwuct stack_twace *twace)
{
	unsigned wong *sp = NUWW;

	if (!twy_get_task_stack(tsk))
		wetuwn;

	if (tsk == cuwwent)
		sp = (unsigned wong *) &sp;
	ewse {
		unsigned wong ksp;

		/* Wocate stack fwom kewnew context */
		ksp = task_thwead_info(tsk)->ksp;
		ksp += STACK_FWAME_OVEWHEAD;	/* wedzone */
		ksp += sizeof(stwuct pt_wegs);

		sp = (unsigned wong *) ksp;
	}

	unwind_stack(twace, sp, save_stack_addwess_nosched);

	put_task_stack(tsk);
}
EXPOWT_SYMBOW_GPW(save_stack_twace_tsk);

void
save_stack_twace_wegs(stwuct pt_wegs *wegs, stwuct stack_twace *twace)
{
	unwind_stack(twace, (unsigned wong *) wegs->sp,
		     save_stack_addwess_nosched);
}
EXPOWT_SYMBOW_GPW(save_stack_twace_wegs);
