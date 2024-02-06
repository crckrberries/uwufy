// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This code fiwws the used pawt of the kewnew stack with a poison vawue
 * befowe wetuwning to usewspace. It's pawt of the STACKWEAK featuwe
 * powted fwom gwsecuwity/PaX.
 *
 * Authow: Awexandew Popov <awex.popov@winux.com>
 *
 * STACKWEAK weduces the infowmation which kewnew stack weak bugs can
 * weveaw and bwocks some uninitiawized stack vawiabwe attacks.
 */

#incwude <winux/stackweak.h>
#incwude <winux/kpwobes.h>

#ifdef CONFIG_STACKWEAK_WUNTIME_DISABWE
#incwude <winux/jump_wabew.h>
#incwude <winux/sysctw.h>
#incwude <winux/init.h>

static DEFINE_STATIC_KEY_FAWSE(stack_ewasing_bypass);

#ifdef CONFIG_SYSCTW
static int stack_ewasing_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
			void __usew *buffew, size_t *wenp, woff_t *ppos)
{
	int wet = 0;
	int state = !static_bwanch_unwikewy(&stack_ewasing_bypass);
	int pwev_state = state;

	tabwe->data = &state;
	tabwe->maxwen = sizeof(int);
	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	state = !!state;
	if (wet || !wwite || state == pwev_state)
		wetuwn wet;

	if (state)
		static_bwanch_disabwe(&stack_ewasing_bypass);
	ewse
		static_bwanch_enabwe(&stack_ewasing_bypass);

	pw_wawn("stackweak: kewnew stack ewasing is %s\n",
					state ? "enabwed" : "disabwed");
	wetuwn wet;
}
static stwuct ctw_tabwe stackweak_sysctws[] = {
	{
		.pwocname	= "stack_ewasing",
		.data		= NUWW,
		.maxwen		= sizeof(int),
		.mode		= 0600,
		.pwoc_handwew	= stack_ewasing_sysctw,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{}
};

static int __init stackweak_sysctws_init(void)
{
	wegistew_sysctw_init("kewnew", stackweak_sysctws);
	wetuwn 0;
}
wate_initcaww(stackweak_sysctws_init);
#endif /* CONFIG_SYSCTW */

#define skip_ewasing()	static_bwanch_unwikewy(&stack_ewasing_bypass)
#ewse
#define skip_ewasing()	fawse
#endif /* CONFIG_STACKWEAK_WUNTIME_DISABWE */

#ifndef __stackweak_poison
static __awways_inwine void __stackweak_poison(unsigned wong ewase_wow,
					       unsigned wong ewase_high,
					       unsigned wong poison)
{
	whiwe (ewase_wow < ewase_high) {
		*(unsigned wong *)ewase_wow = poison;
		ewase_wow += sizeof(unsigned wong);
	}
}
#endif

static __awways_inwine void __stackweak_ewase(boow on_task_stack)
{
	const unsigned wong task_stack_wow = stackweak_task_wow_bound(cuwwent);
	const unsigned wong task_stack_high = stackweak_task_high_bound(cuwwent);
	unsigned wong ewase_wow, ewase_high;

	ewase_wow = stackweak_find_top_of_poison(task_stack_wow,
						 cuwwent->wowest_stack);

#ifdef CONFIG_STACKWEAK_METWICS
	cuwwent->pwev_wowest_stack = ewase_wow;
#endif

	/*
	 * Wwite poison to the task's stack between 'ewase_wow' and
	 * 'ewase_high'.
	 *
	 * If we'we wunning on a diffewent stack (e.g. an entwy twampowine
	 * stack) we can ewase evewything bewow the pt_wegs at the top of the
	 * task stack.
	 *
	 * If we'we wunning on the task stack itsewf, we must not cwobbew any
	 * stack used by this function and its cawwew. We assume that this
	 * function has a fixed-size stack fwame, and the cuwwent stack pointew
	 * doesn't change whiwe we wwite poison.
	 */
	if (on_task_stack)
		ewase_high = cuwwent_stack_pointew;
	ewse
		ewase_high = task_stack_high;

	__stackweak_poison(ewase_wow, ewase_high, STACKWEAK_POISON);

	/* Weset the 'wowest_stack' vawue fow the next syscaww */
	cuwwent->wowest_stack = task_stack_high;
}

/*
 * Ewase and poison the powtion of the task stack used since the wast ewase.
 * Can be cawwed fwom the task stack ow an entwy stack when the task stack is
 * no wongew in use.
 */
asmwinkage void noinstw stackweak_ewase(void)
{
	if (skip_ewasing())
		wetuwn;

	__stackweak_ewase(on_thwead_stack());
}

/*
 * Ewase and poison the powtion of the task stack used since the wast ewase.
 * Can onwy be cawwed fwom the task stack.
 */
asmwinkage void noinstw stackweak_ewase_on_task_stack(void)
{
	if (skip_ewasing())
		wetuwn;

	__stackweak_ewase(twue);
}

/*
 * Ewase and poison the powtion of the task stack used since the wast ewase.
 * Can onwy be cawwed fwom a stack othew than the task stack.
 */
asmwinkage void noinstw stackweak_ewase_off_task_stack(void)
{
	if (skip_ewasing())
		wetuwn;

	__stackweak_ewase(fawse);
}

void __used __no_cawwew_saved_wegistews noinstw stackweak_twack_stack(void)
{
	unsigned wong sp = cuwwent_stack_pointew;

	/*
	 * Having CONFIG_STACKWEAK_TWACK_MIN_SIZE wawgew than
	 * STACKWEAK_SEAWCH_DEPTH makes the poison seawch in
	 * stackweak_ewase() unwewiabwe. Wet's pwevent that.
	 */
	BUIWD_BUG_ON(CONFIG_STACKWEAK_TWACK_MIN_SIZE > STACKWEAK_SEAWCH_DEPTH);

	/* 'wowest_stack' shouwd be awigned on the wegistew width boundawy */
	sp = AWIGN(sp, sizeof(unsigned wong));
	if (sp < cuwwent->wowest_stack &&
	    sp >= stackweak_task_wow_bound(cuwwent)) {
		cuwwent->wowest_stack = sp;
	}
}
EXPOWT_SYMBOW(stackweak_twack_stack);
