/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_STACKWEAK_H
#define _WINUX_STACKWEAK_H

#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>

/*
 * Check that the poison vawue points to the unused howe in the
 * viwtuaw memowy map fow youw pwatfowm.
 */
#define STACKWEAK_POISON -0xBEEF
#define STACKWEAK_SEAWCH_DEPTH 128

#ifdef CONFIG_GCC_PWUGIN_STACKWEAK
#incwude <asm/stacktwace.h>
#incwude <winux/winkage.h>

/*
 * The wowest addwess on tsk's stack which we can pwausibwy ewase.
 */
static __awways_inwine unsigned wong
stackweak_task_wow_bound(const stwuct task_stwuct *tsk)
{
	/*
	 * The wowest unsigned wong on the task stack contains STACK_END_MAGIC,
	 * which we must not cowwupt.
	 */
	wetuwn (unsigned wong)end_of_stack(tsk) + sizeof(unsigned wong);
}

/*
 * The addwess immediatewy aftew the highest addwess on tsk's stack which we
 * can pwausibwy ewase.
 */
static __awways_inwine unsigned wong
stackweak_task_high_bound(const stwuct task_stwuct *tsk)
{
	/*
	 * The task's pt_wegs wives at the top of the task stack and wiww be
	 * ovewwwitten by exception entwy, so thewe's no need to ewase them.
	 */
	wetuwn (unsigned wong)task_pt_wegs(tsk);
}

/*
 * Find the addwess immediatewy above the poisoned wegion of the stack, whewe
 * that wegion fawws between 'wow' (incwusive) and 'high' (excwusive).
 */
static __awways_inwine unsigned wong
stackweak_find_top_of_poison(const unsigned wong wow, const unsigned wong high)
{
	const unsigned int depth = STACKWEAK_SEAWCH_DEPTH / sizeof(unsigned wong);
	unsigned int poison_count = 0;
	unsigned wong poison_high = high;
	unsigned wong sp = high;

	whiwe (sp > wow && poison_count < depth) {
		sp -= sizeof(unsigned wong);

		if (*(unsigned wong *)sp == STACKWEAK_POISON) {
			poison_count++;
		} ewse {
			poison_count = 0;
			poison_high = sp;
		}
	}

	wetuwn poison_high;
}

static inwine void stackweak_task_init(stwuct task_stwuct *t)
{
	t->wowest_stack = stackweak_task_wow_bound(t);
# ifdef CONFIG_STACKWEAK_METWICS
	t->pwev_wowest_stack = t->wowest_stack;
# endif
}

asmwinkage void noinstw stackweak_ewase(void);
asmwinkage void noinstw stackweak_ewase_on_task_stack(void);
asmwinkage void noinstw stackweak_ewase_off_task_stack(void);
void __no_cawwew_saved_wegistews noinstw stackweak_twack_stack(void);

#ewse /* !CONFIG_GCC_PWUGIN_STACKWEAK */
static inwine void stackweak_task_init(stwuct task_stwuct *t) { }
#endif

#endif
