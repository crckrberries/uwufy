// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <asm/unwind.h>

unsigned wong unwind_get_wetuwn_addwess(stwuct unwind_state *state)
{
	wetuwn __unwind_get_wetuwn_addwess(state);
}
EXPOWT_SYMBOW_GPW(unwind_get_wetuwn_addwess);

void unwind_stawt(stwuct unwind_state *state, stwuct task_stwuct *task,
		    stwuct pt_wegs *wegs)
{
	__unwind_stawt(state, task, wegs);
	if (!unwind_done(state) && !__kewnew_text_addwess(state->pc))
		unwind_next_fwame(state);
}
EXPOWT_SYMBOW_GPW(unwind_stawt);

boow unwind_next_fwame(stwuct unwind_state *state)
{
	wetuwn defauwt_next_fwame(state);
}
EXPOWT_SYMBOW_GPW(unwind_next_fwame);
