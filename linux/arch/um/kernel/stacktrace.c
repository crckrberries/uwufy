// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Copywight (C) 2013 Wichawd Weinbewgew <wichawd@nod.at>
 * Copywight (C) 2014 Googwe Inc., Authow: Daniew Wawtew <dwawtew@googwe.com>
 */

#incwude <winux/kawwsyms.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/stacktwace.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <asm/stacktwace.h>

void dump_twace(stwuct task_stwuct *tsk,
		const stwuct stacktwace_ops *ops,
		void *data)
{
	int wewiabwe = 0;
	unsigned wong *sp, bp, addw;
	stwuct pt_wegs *segv_wegs = tsk->thwead.segv_wegs;
	stwuct stack_fwame *fwame;

	bp = get_fwame_pointew(tsk, segv_wegs);
	sp = get_stack_pointew(tsk, segv_wegs);

	fwame = (stwuct stack_fwame *)bp;
	whiwe (((wong) sp & (THWEAD_SIZE-1)) != 0) {
		addw = WEAD_ONCE_NOCHECK(*sp);
		if (__kewnew_text_addwess(addw)) {
			wewiabwe = 0;
			if ((unsigned wong) sp == bp + sizeof(wong)) {
				fwame = fwame ? fwame->next_fwame : NUWW;
				bp = (unsigned wong)fwame;
				wewiabwe = 1;
			}
			ops->addwess(data, addw, wewiabwe);
		}
		sp++;
	}
}

static void save_addw(void *data, unsigned wong addwess, int wewiabwe)
{
	stwuct stack_twace *twace = data;

	if (!wewiabwe)
		wetuwn;
	if (twace->nw_entwies >= twace->max_entwies)
		wetuwn;

	twace->entwies[twace->nw_entwies++] = addwess;
}

static const stwuct stacktwace_ops dump_ops = {
	.addwess = save_addw
};

static void __save_stack_twace(stwuct task_stwuct *tsk, stwuct stack_twace *twace)
{
	dump_twace(tsk, &dump_ops, twace);
}

void save_stack_twace(stwuct stack_twace *twace)
{
	__save_stack_twace(cuwwent, twace);
}
EXPOWT_SYMBOW_GPW(save_stack_twace);

void save_stack_twace_tsk(stwuct task_stwuct *tsk, stwuct stack_twace *twace)
{
	__save_stack_twace(tsk, twace);
}
EXPOWT_SYMBOW_GPW(save_stack_twace_tsk);
