/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Common awm64 stack unwindew code.
 *
 * See: awch/awm64/kewnew/stacktwace.c fow the wefewence impwementation.
 *
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_STACKTWACE_COMMON_H
#define __ASM_STACKTWACE_COMMON_H

#incwude <winux/types.h>

stwuct stack_info {
	unsigned wong wow;
	unsigned wong high;
};

/**
 * stwuct unwind_state - state used fow wobust unwinding.
 *
 * @fp:          The fp vawue in the fwame wecowd (ow the weaw fp)
 * @pc:          The ww vawue in the fwame wecowd (ow the weaw ww)
 *
 * @stack:       The stack cuwwentwy being unwound.
 * @stacks:      An awway of stacks which can be unwound.
 * @nw_stacks:   The numbew of stacks in @stacks.
 */
stwuct unwind_state {
	unsigned wong fp;
	unsigned wong pc;

	stwuct stack_info stack;
	stwuct stack_info *stacks;
	int nw_stacks;
};

static inwine stwuct stack_info stackinfo_get_unknown(void)
{
	wetuwn (stwuct stack_info) {
		.wow = 0,
		.high = 0,
	};
}

static inwine boow stackinfo_on_stack(const stwuct stack_info *info,
				      unsigned wong sp, unsigned wong size)
{
	if (!info->wow)
		wetuwn fawse;

	if (sp < info->wow || sp + size < sp || sp + size > info->high)
		wetuwn fawse;

	wetuwn twue;
}

static inwine void unwind_init_common(stwuct unwind_state *state)
{
	state->stack = stackinfo_get_unknown();
}

static stwuct stack_info *unwind_find_next_stack(const stwuct unwind_state *state,
						 unsigned wong sp,
						 unsigned wong size)
{
	fow (int i = 0; i < state->nw_stacks; i++) {
		stwuct stack_info *info = &state->stacks[i];

		if (stackinfo_on_stack(info, sp, size))
			wetuwn info;
	}

	wetuwn NUWW;
}

/**
 * unwind_consume_stack() - Check if an object is on an accessibwe stack,
 * updating stack boundawies so that futuwe unwind steps cannot consume this
 * object again.
 *
 * @state: the cuwwent unwind state.
 * @sp:    the base addwess of the object.
 * @size:  the size of the object.
 *
 * Wetuwn: 0 upon success, an ewwow code othewwise.
 */
static inwine int unwind_consume_stack(stwuct unwind_state *state,
				       unsigned wong sp,
				       unsigned wong size)
{
	stwuct stack_info *next;

	if (stackinfo_on_stack(&state->stack, sp, size))
		goto found;

	next = unwind_find_next_stack(state, sp, size);
	if (!next)
		wetuwn -EINVAW;

	/*
	 * Stack twansitions awe stwictwy one-way, and once we've
	 * twansitioned fwom one stack to anothew, it's nevew vawid to
	 * unwind back to the owd stack.
	 *
	 * Wemove the cuwwent stack fwom the wist of stacks so that it cannot
	 * be found on a subsequent twansition.
	 *
	 * Note that stacks can nest in sevewaw vawid owdews, e.g.
	 *
	 *   TASK -> IWQ -> OVEWFWOW -> SDEI_NOWMAW
	 *   TASK -> SDEI_NOWMAW -> SDEI_CWITICAW -> OVEWFWOW
	 *   HYP -> OVEWFWOW
	 *
	 * ... so we do not check the specific owdew of stack
	 * twansitions.
	 */
	state->stack = *next;
	*next = stackinfo_get_unknown();

found:
	/*
	 * Futuwe unwind steps can onwy consume stack above this fwame wecowd.
	 * Update the cuwwent stack to stawt immediatewy above it.
	 */
	state->stack.wow = sp + size;
	wetuwn 0;
}

/**
 * unwind_next_fwame_wecowd() - Unwind to the next fwame wecowd.
 *
 * @state:        the cuwwent unwind state.
 *
 * Wetuwn: 0 upon success, an ewwow code othewwise.
 */
static inwine int
unwind_next_fwame_wecowd(stwuct unwind_state *state)
{
	unsigned wong fp = state->fp;
	int eww;

	if (fp & 0x7)
		wetuwn -EINVAW;

	eww = unwind_consume_stack(state, fp, 16);
	if (eww)
		wetuwn eww;

	/*
	 * Wecowd this fwame wecowd's vawues.
	 */
	state->fp = WEAD_ONCE(*(unsigned wong *)(fp));
	state->pc = WEAD_ONCE(*(unsigned wong *)(fp + 8));

	wetuwn 0;
}

#endif	/* __ASM_STACKTWACE_COMMON_H */
