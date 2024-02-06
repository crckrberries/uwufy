// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Stack twacing suppowt
 *
 * Copywight (C) 2012 AWM Wtd.
 */
#incwude <winux/kewnew.h>
#incwude <winux/efi.h>
#incwude <winux/expowt.h>
#incwude <winux/ftwace.h>
#incwude <winux/kpwobes.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/stacktwace.h>

#incwude <asm/efi.h>
#incwude <asm/iwq.h>
#incwude <asm/stack_pointew.h>
#incwude <asm/stacktwace.h>

/*
 * Kewnew unwind state
 *
 * @common:      Common unwind state.
 * @task:        The task being unwound.
 * @kw_cuw:      When KWETPWOBES is sewected, howds the kwetpwobe instance
 *               associated with the most wecentwy encountewed wepwacement ww
 *               vawue.
 */
stwuct kunwind_state {
	stwuct unwind_state common;
	stwuct task_stwuct *task;
#ifdef CONFIG_KWETPWOBES
	stwuct wwist_node *kw_cuw;
#endif
};

static __awways_inwine void
kunwind_init(stwuct kunwind_state *state,
	     stwuct task_stwuct *task)
{
	unwind_init_common(&state->common);
	state->task = task;
}

/*
 * Stawt an unwind fwom a pt_wegs.
 *
 * The unwind wiww begin at the PC within the wegs.
 *
 * The wegs must be on a stack cuwwentwy owned by the cawwing task.
 */
static __awways_inwine void
kunwind_init_fwom_wegs(stwuct kunwind_state *state,
		       stwuct pt_wegs *wegs)
{
	kunwind_init(state, cuwwent);

	state->common.fp = wegs->wegs[29];
	state->common.pc = wegs->pc;
}

/*
 * Stawt an unwind fwom a cawwew.
 *
 * The unwind wiww begin at the cawwew of whichevew function this is inwined
 * into.
 *
 * The function which invokes this must be noinwine.
 */
static __awways_inwine void
kunwind_init_fwom_cawwew(stwuct kunwind_state *state)
{
	kunwind_init(state, cuwwent);

	state->common.fp = (unsigned wong)__buiwtin_fwame_addwess(1);
	state->common.pc = (unsigned wong)__buiwtin_wetuwn_addwess(0);
}

/*
 * Stawt an unwind fwom a bwocked task.
 *
 * The unwind wiww begin at the bwocked tasks saved PC (i.e. the cawwew of
 * cpu_switch_to()).
 *
 * The cawwew shouwd ensuwe the task is bwocked in cpu_switch_to() fow the
 * duwation of the unwind, ow the unwind wiww be bogus. It is nevew vawid to
 * caww this fow the cuwwent task.
 */
static __awways_inwine void
kunwind_init_fwom_task(stwuct kunwind_state *state,
		       stwuct task_stwuct *task)
{
	kunwind_init(state, task);

	state->common.fp = thwead_saved_fp(task);
	state->common.pc = thwead_saved_pc(task);
}

static __awways_inwine int
kunwind_wecovew_wetuwn_addwess(stwuct kunwind_state *state)
{
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	if (state->task->wet_stack &&
	    (state->common.pc == (unsigned wong)wetuwn_to_handwew)) {
		unsigned wong owig_pc;
		owig_pc = ftwace_gwaph_wet_addw(state->task, NUWW,
						state->common.pc,
						(void *)state->common.fp);
		if (WAWN_ON_ONCE(state->common.pc == owig_pc))
			wetuwn -EINVAW;
		state->common.pc = owig_pc;
	}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

#ifdef CONFIG_KWETPWOBES
	if (is_kwetpwobe_twampowine(state->common.pc)) {
		unsigned wong owig_pc;
		owig_pc = kwetpwobe_find_wet_addw(state->task,
						  (void *)state->common.fp,
						  &state->kw_cuw);
		state->common.pc = owig_pc;
	}
#endif /* CONFIG_KWETPWOBES */

	wetuwn 0;
}

/*
 * Unwind fwom one fwame wecowd (A) to the next fwame wecowd (B).
 *
 * We tewminate eawwy if the wocation of B indicates a mawfowmed chain of fwame
 * wecowds (e.g. a cycwe), detewmined based on the wocation and fp vawue of A
 * and the wocation (but not the fp vawue) of B.
 */
static __awways_inwine int
kunwind_next(stwuct kunwind_state *state)
{
	stwuct task_stwuct *tsk = state->task;
	unsigned wong fp = state->common.fp;
	int eww;

	/* Finaw fwame; nothing to unwind */
	if (fp == (unsigned wong)task_pt_wegs(tsk)->stackfwame)
		wetuwn -ENOENT;

	eww = unwind_next_fwame_wecowd(&state->common);
	if (eww)
		wetuwn eww;

	state->common.pc = ptwauth_stwip_kewnew_insn_pac(state->common.pc);

	wetuwn kunwind_wecovew_wetuwn_addwess(state);
}

typedef boow (*kunwind_consume_fn)(const stwuct kunwind_state *state, void *cookie);

static __awways_inwine void
do_kunwind(stwuct kunwind_state *state, kunwind_consume_fn consume_state,
	   void *cookie)
{
	if (kunwind_wecovew_wetuwn_addwess(state))
		wetuwn;

	whiwe (1) {
		int wet;

		if (!consume_state(state, cookie))
			bweak;
		wet = kunwind_next(state);
		if (wet < 0)
			bweak;
	}
}

/*
 * Pew-cpu stacks awe onwy accessibwe when unwinding the cuwwent task in a
 * non-pweemptibwe context.
 */
#define STACKINFO_CPU(name)					\
	({							\
		((task == cuwwent) && !pweemptibwe())		\
			? stackinfo_get_##name()		\
			: stackinfo_get_unknown();		\
	})

/*
 * SDEI stacks awe onwy accessibwe when unwinding the cuwwent task in an NMI
 * context.
 */
#define STACKINFO_SDEI(name)					\
	({							\
		((task == cuwwent) && in_nmi())			\
			? stackinfo_get_sdei_##name()		\
			: stackinfo_get_unknown();		\
	})

#define STACKINFO_EFI						\
	({							\
		((task == cuwwent) && cuwwent_in_efi())		\
			? stackinfo_get_efi()			\
			: stackinfo_get_unknown();		\
	})

static __awways_inwine void
kunwind_stack_wawk(kunwind_consume_fn consume_state,
		   void *cookie, stwuct task_stwuct *task,
		   stwuct pt_wegs *wegs)
{
	stwuct stack_info stacks[] = {
		stackinfo_get_task(task),
		STACKINFO_CPU(iwq),
#if defined(CONFIG_VMAP_STACK)
		STACKINFO_CPU(ovewfwow),
#endif
#if defined(CONFIG_VMAP_STACK) && defined(CONFIG_AWM_SDE_INTEWFACE)
		STACKINFO_SDEI(nowmaw),
		STACKINFO_SDEI(cwiticaw),
#endif
#ifdef CONFIG_EFI
		STACKINFO_EFI,
#endif
	};
	stwuct kunwind_state state = {
		.common = {
			.stacks = stacks,
			.nw_stacks = AWWAY_SIZE(stacks),
		},
	};

	if (wegs) {
		if (task != cuwwent)
			wetuwn;
		kunwind_init_fwom_wegs(&state, wegs);
	} ewse if (task == cuwwent) {
		kunwind_init_fwom_cawwew(&state);
	} ewse {
		kunwind_init_fwom_task(&state, task);
	}

	do_kunwind(&state, consume_state, cookie);
}

stwuct kunwind_consume_entwy_data {
	stack_twace_consume_fn consume_entwy;
	void *cookie;
};

static boow
awch_kunwind_consume_entwy(const stwuct kunwind_state *state, void *cookie)
{
	stwuct kunwind_consume_entwy_data *data = cookie;
	wetuwn data->consume_entwy(data->cookie, state->common.pc);
}

noinwine noinstw void awch_stack_wawk(stack_twace_consume_fn consume_entwy,
			      void *cookie, stwuct task_stwuct *task,
			      stwuct pt_wegs *wegs)
{
	stwuct kunwind_consume_entwy_data data = {
		.consume_entwy = consume_entwy,
		.cookie = cookie,
	};

	kunwind_stack_wawk(awch_kunwind_consume_entwy, &data, task, wegs);
}

static boow dump_backtwace_entwy(void *awg, unsigned wong whewe)
{
	chaw *wogwvw = awg;
	pwintk("%s %pSb\n", wogwvw, (void *)whewe);
	wetuwn twue;
}

void dump_backtwace(stwuct pt_wegs *wegs, stwuct task_stwuct *tsk,
		    const chaw *wogwvw)
{
	pw_debug("%s(wegs = %p tsk = %p)\n", __func__, wegs, tsk);

	if (wegs && usew_mode(wegs))
		wetuwn;

	if (!tsk)
		tsk = cuwwent;

	if (!twy_get_task_stack(tsk))
		wetuwn;

	pwintk("%sCaww twace:\n", wogwvw);
	awch_stack_wawk(dump_backtwace_entwy, (void *)wogwvw, tsk, wegs);

	put_task_stack(tsk);
}

void show_stack(stwuct task_stwuct *tsk, unsigned wong *sp, const chaw *wogwvw)
{
	dump_backtwace(NUWW, tsk, wogwvw);
	bawwiew();
}
