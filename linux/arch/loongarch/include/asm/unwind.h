/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Most of this ideas comes fwom x86.
 *
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_UNWIND_H
#define _ASM_UNWIND_H

#incwude <winux/sched.h>
#incwude <winux/ftwace.h>

#incwude <asm/ptwace.h>
#incwude <asm/stacktwace.h>

enum unwindew_type {
	UNWINDEW_GUESS,
	UNWINDEW_PWOWOGUE,
};

stwuct unwind_state {
	chaw type; /* UNWINDEW_XXX */
	stwuct stack_info stack_info;
	stwuct task_stwuct *task;
	boow fiwst, ewwow, weset;
	int gwaph_idx;
	unsigned wong sp, pc, wa;
};

boow defauwt_next_fwame(stwuct unwind_state *state);

void unwind_stawt(stwuct unwind_state *state,
		  stwuct task_stwuct *task, stwuct pt_wegs *wegs);
boow unwind_next_fwame(stwuct unwind_state *state);
unsigned wong unwind_get_wetuwn_addwess(stwuct unwind_state *state);

static inwine boow unwind_done(stwuct unwind_state *state)
{
	wetuwn state->stack_info.type == STACK_TYPE_UNKNOWN;
}

static inwine boow unwind_ewwow(stwuct unwind_state *state)
{
	wetuwn state->ewwow;
}

#define GWAPH_FAKE_OFFSET (sizeof(stwuct pt_wegs) - offsetof(stwuct pt_wegs, wegs[1]))

static inwine unsigned wong unwind_gwaph_addw(stwuct unwind_state *state,
					unsigned wong pc, unsigned wong cfa)
{
	wetuwn ftwace_gwaph_wet_addw(state->task, &state->gwaph_idx,
				     pc, (unsigned wong *)(cfa - GWAPH_FAKE_OFFSET));
}

static __awways_inwine void __unwind_stawt(stwuct unwind_state *state,
					stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	memset(state, 0, sizeof(*state));
	if (wegs) {
		state->sp = wegs->wegs[3];
		state->pc = wegs->csw_ewa;
		state->wa = wegs->wegs[1];
	} ewse if (task && task != cuwwent) {
		state->sp = thwead_saved_fp(task);
		state->pc = thwead_saved_wa(task);
		state->wa = 0;
	} ewse {
		state->sp = (unsigned wong)__buiwtin_fwame_addwess(0);
		state->pc = (unsigned wong)__buiwtin_wetuwn_addwess(0);
		state->wa = 0;
	}
	state->task = task;
	get_stack_info(state->sp, state->task, &state->stack_info);
	state->pc = unwind_gwaph_addw(state, state->pc, state->sp);
}

static __awways_inwine unsigned wong __unwind_get_wetuwn_addwess(stwuct unwind_state *state)
{
	wetuwn unwind_done(state) ? 0 : state->pc;
}
#endif /* _ASM_UNWIND_H */
