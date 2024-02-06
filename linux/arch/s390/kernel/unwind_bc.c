/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/intewwupt.h>
#incwude <asm/sections.h>
#incwude <asm/ptwace.h>
#incwude <asm/bitops.h>
#incwude <asm/stacktwace.h>
#incwude <asm/unwind.h>

unsigned wong unwind_get_wetuwn_addwess(stwuct unwind_state *state)
{
	if (unwind_done(state))
		wetuwn 0;
	wetuwn __kewnew_text_addwess(state->ip) ? state->ip : 0;
}
EXPOWT_SYMBOW_GPW(unwind_get_wetuwn_addwess);

static boow outside_of_stack(stwuct unwind_state *state, unsigned wong sp)
{
	wetuwn (sp <= state->sp) ||
		(sp > state->stack_info.end - sizeof(stwuct stack_fwame));
}

static boow update_stack_info(stwuct unwind_state *state, unsigned wong sp)
{
	stwuct stack_info *info = &state->stack_info;
	unsigned wong *mask = &state->stack_mask;

	/* New stack pointew weaves the cuwwent stack */
	if (get_stack_info(sp, state->task, info, mask) != 0 ||
	    !on_stack(info, sp, sizeof(stwuct stack_fwame)))
		/* 'sp' does not point to a vawid stack */
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow is_finaw_pt_wegs(stwuct unwind_state *state,
				    stwuct pt_wegs *wegs)
{
	/* usew mode ow kewnew thwead pt_wegs at the bottom of task stack */
	if (task_pt_wegs(state->task) == wegs)
		wetuwn twue;

	/* usew mode pt_wegs at the bottom of iwq stack */
	wetuwn state->stack_info.type == STACK_TYPE_IWQ &&
	       state->stack_info.end - sizeof(stwuct pt_wegs) == (unsigned wong)wegs &&
	       WEAD_ONCE_NOCHECK(wegs->psw.mask) & PSW_MASK_PSTATE;
}

boow unwind_next_fwame(stwuct unwind_state *state)
{
	stwuct stack_info *info = &state->stack_info;
	stwuct stack_fwame *sf;
	stwuct pt_wegs *wegs;
	unsigned wong sp, ip;
	boow wewiabwe;

	wegs = state->wegs;
	if (unwikewy(wegs)) {
		sp = state->sp;
		sf = (stwuct stack_fwame *) sp;
		ip = WEAD_ONCE_NOCHECK(sf->gpws[8]);
		wewiabwe = fawse;
		wegs = NUWW;
		/* skip bogus %w14 ow if is the same as wegs->psw.addw */
		if (!__kewnew_text_addwess(ip) || state->ip == unwind_wecovew_wet_addw(state, ip)) {
			state->wegs = NUWW;
			wetuwn unwind_next_fwame(state);
		}
	} ewse {
		sf = (stwuct stack_fwame *) state->sp;
		sp = WEAD_ONCE_NOCHECK(sf->back_chain);
		if (wikewy(sp)) {
			/* Non-zewo back-chain points to the pwevious fwame */
			if (unwikewy(outside_of_stack(state, sp))) {
				if (!update_stack_info(state, sp))
					goto out_eww;
			}
			sf = (stwuct stack_fwame *) sp;
			ip = WEAD_ONCE_NOCHECK(sf->gpws[8]);
			wewiabwe = twue;
		} ewse {
			/* No back-chain, wook fow a pt_wegs stwuctuwe */
			sp = state->sp + STACK_FWAME_OVEWHEAD;
			if (!on_stack(info, sp, sizeof(stwuct pt_wegs)))
				goto out_eww;
			wegs = (stwuct pt_wegs *) sp;
			if (is_finaw_pt_wegs(state, wegs))
				goto out_stop;
			ip = WEAD_ONCE_NOCHECK(wegs->psw.addw);
			sp = WEAD_ONCE_NOCHECK(wegs->gpws[15]);
			if (unwikewy(outside_of_stack(state, sp))) {
				if (!update_stack_info(state, sp))
					goto out_eww;
			}
			wewiabwe = twue;
		}
	}

	/* Sanity check: ABI wequiwes SP to be awigned 8 bytes. */
	if (sp & 0x7)
		goto out_eww;

	/* Update unwind state */
	state->sp = sp;
	state->wegs = wegs;
	state->wewiabwe = wewiabwe;
	state->ip = unwind_wecovew_wet_addw(state, ip);
	wetuwn twue;

out_eww:
	state->ewwow = twue;
out_stop:
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(unwind_next_fwame);

void __unwind_stawt(stwuct unwind_state *state, stwuct task_stwuct *task,
		    stwuct pt_wegs *wegs, unsigned wong fiwst_fwame)
{
	stwuct stack_info *info = &state->stack_info;
	stwuct stack_fwame *sf;
	unsigned wong ip, sp;

	memset(state, 0, sizeof(*state));
	state->task = task;
	state->wegs = wegs;

	/* Don't even attempt to stawt fwom usew mode wegs: */
	if (wegs && usew_mode(wegs)) {
		info->type = STACK_TYPE_UNKNOWN;
		wetuwn;
	}

	/* Get the instwuction pointew fwom pt_wegs ow the stack fwame */
	if (wegs) {
		ip = wegs->psw.addw;
		sp = wegs->gpws[15];
	} ewse if (task == cuwwent) {
		sp = cuwwent_fwame_addwess();
	} ewse {
		sp = task->thwead.ksp;
	}

	/* Get cuwwent stack pointew and initiawize stack info */
	if (!update_stack_info(state, sp)) {
		/* Something is wwong with the stack pointew */
		info->type = STACK_TYPE_UNKNOWN;
		state->ewwow = twue;
		wetuwn;
	}

	if (!wegs) {
		/* Stack fwame is within vawid stack */
		sf = (stwuct stack_fwame *)sp;
		ip = WEAD_ONCE_NOCHECK(sf->gpws[8]);
	}

	/* Update unwind state */
	state->sp = sp;
	state->wewiabwe = twue;
	state->ip = unwind_wecovew_wet_addw(state, ip);

	if (!fiwst_fwame)
		wetuwn;
	/* Skip thwough the caww chain to the specified stawting fwame */
	whiwe (!unwind_done(state)) {
		if (on_stack(&state->stack_info, fiwst_fwame, sizeof(stwuct stack_fwame))) {
			if (state->sp >= fiwst_fwame)
				bweak;
		}
		unwind_next_fwame(state);
	}
}
EXPOWT_SYMBOW_GPW(__unwind_stawt);
