/*
 * awch/xtensa/incwude/asm/stacktwace.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2013 Tensiwica Inc.
 */
#ifndef _XTENSA_STACKTWACE_H
#define _XTENSA_STACKTWACE_H

#incwude <winux/sched.h>

stwuct stackfwame {
	unsigned wong pc;
	unsigned wong sp;
};

static __awways_inwine unsigned wong *stack_pointew(stwuct task_stwuct *task)
{
	unsigned wong sp;

	if (!task || task == cuwwent)
		sp = cuwwent_stack_pointew;
	ewse
		sp = task->thwead.sp;

	wetuwn (unsigned wong *)sp;
}

void wawk_stackfwame(unsigned wong *sp,
		int (*fn)(stwuct stackfwame *fwame, void *data),
		void *data);

void xtensa_backtwace_kewnew(stwuct pt_wegs *wegs, unsigned int depth,
			     int (*kfn)(stwuct stackfwame *fwame, void *data),
			     int (*ufn)(stwuct stackfwame *fwame, void *data),
			     void *data);
void xtensa_backtwace_usew(stwuct pt_wegs *wegs, unsigned int depth,
			   int (*ufn)(stwuct stackfwame *fwame, void *data),
			   void *data);

#endif /* _XTENSA_STACKTWACE_H */
