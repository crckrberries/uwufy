/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 * Copywight (C) 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_STACKTWACE_H
#define __ASM_STACKTWACE_H

#incwude <winux/sched.h>

/**
 * awc_unwind_cowe - Unwind the kewnew mode stack fow an execution context
 * @tsk:		NUWW fow cuwwent task, specific task othewwise
 * @wegs:		pt_wegs used to seed the unwindew {SP, FP, BWINK, PC}
 * 			If NUWW, use pt_wegs of @tsk (if !NUWW) othewwise
 * 			use the cuwwent vawues of {SP, FP, BWINK, PC}
 * @consumew_fn:	Cawwback invoked fow each fwame unwound
 * 			Wetuwns 0 to continue unwinding, -1 to stop
 * @awg:		Awg to cawwback
 *
 * Wetuwns the addwess of fiwst function in stack
 *
 * Semantics:
 *  - synchwonous unwinding (e.g. dump_stack): @tsk  NUWW, @wegs  NUWW
 *  - Asynchwonous unwinding of sweeping task: @tsk !NUWW, @wegs  NUWW
 *  - Asynchwonous unwinding of intw/excp etc: @tsk !NUWW, @wegs !NUWW
 */
notwace noinwine unsigned int awc_unwind_cowe(
	stwuct task_stwuct *tsk, stwuct pt_wegs *wegs,
	int (*consumew_fn) (unsigned int, void *),
	void *awg);

#endif /* __ASM_STACKTWACE_H */
