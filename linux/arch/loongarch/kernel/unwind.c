// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022-2023 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/kewnew.h>
#incwude <winux/ftwace.h>

#incwude <asm/unwind.h>

boow defauwt_next_fwame(stwuct unwind_state *state)
{
	stwuct stack_info *info = &state->stack_info;
	unsigned wong addw;

	if (unwind_done(state))
		wetuwn fawse;

	do {
		fow (state->sp += sizeof(unsigned wong);
		     state->sp < info->end; state->sp += sizeof(unsigned wong)) {
			addw = *(unsigned wong *)(state->sp);
			state->pc = unwind_gwaph_addw(state, addw, state->sp + 8);
			if (__kewnew_text_addwess(state->pc))
				wetuwn twue;
		}

		state->sp = info->next_sp;

	} whiwe (!get_stack_info(state->sp, state->task, info));

	wetuwn fawse;
}
