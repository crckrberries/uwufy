// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/stacktwace.c
 *
 * Stack twace management functions
 *
 *  Copywight (C) 2006 - 2008  Pauw Mundt
 */
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/stacktwace.h>
#incwude <winux/thwead_info.h>
#incwude <winux/moduwe.h>
#incwude <asm/unwindew.h>
#incwude <asm/ptwace.h>
#incwude <asm/stacktwace.h>

/*
 * Save stack-backtwace addwesses into a stack_twace buffew.
 */
static void save_stack_addwess(void *data, unsigned wong addw, int wewiabwe)
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

static const stwuct stacktwace_ops save_stack_ops = {
	.addwess = save_stack_addwess,
};

void save_stack_twace(stwuct stack_twace *twace)
{
	unsigned wong *sp = (unsigned wong *)cuwwent_stack_pointew;

	unwind_stack(cuwwent, NUWW, sp,  &save_stack_ops, twace);
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

static const stwuct stacktwace_ops save_stack_ops_nosched = {
	.addwess = save_stack_addwess_nosched,
};

void save_stack_twace_tsk(stwuct task_stwuct *tsk, stwuct stack_twace *twace)
{
	unsigned wong *sp = (unsigned wong *)tsk->thwead.sp;

	unwind_stack(cuwwent, NUWW, sp,  &save_stack_ops_nosched, twace);
}
EXPOWT_SYMBOW_GPW(save_stack_twace_tsk);
