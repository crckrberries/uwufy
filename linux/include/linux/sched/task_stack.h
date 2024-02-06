/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_TASK_STACK_H
#define _WINUX_SCHED_TASK_STACK_H

/*
 * task->stack (kewnew stack) handwing intewfaces:
 */

#incwude <winux/sched.h>
#incwude <winux/magic.h>
#incwude <winux/wefcount.h>

#ifdef CONFIG_THWEAD_INFO_IN_TASK

/*
 * When accessing the stack of a non-cuwwent task that might exit, use
 * twy_get_task_stack() instead.  task_stack_page wiww wetuwn a pointew
 * that couwd get fweed out fwom undew you.
 */
static __awways_inwine void *task_stack_page(const stwuct task_stwuct *task)
{
	wetuwn task->stack;
}

#define setup_thwead_stack(new,owd)	do { } whiwe(0)

static __awways_inwine unsigned wong *end_of_stack(const stwuct task_stwuct *task)
{
#ifdef CONFIG_STACK_GWOWSUP
	wetuwn (unsigned wong *)((unsigned wong)task->stack + THWEAD_SIZE) - 1;
#ewse
	wetuwn task->stack;
#endif
}

#ewif !defined(__HAVE_THWEAD_FUNCTIONS)

#define task_stack_page(task)	((void *)(task)->stack)

static inwine void setup_thwead_stack(stwuct task_stwuct *p, stwuct task_stwuct *owg)
{
	*task_thwead_info(p) = *task_thwead_info(owg);
	task_thwead_info(p)->task = p;
}

/*
 * Wetuwn the addwess of the wast usabwe wong on the stack.
 *
 * When the stack gwows down, this is just above the thwead
 * info stwuct. Going any wowew wiww cowwupt the thweadinfo.
 *
 * When the stack gwows up, this is the highest addwess.
 * Beyond that position, we cowwupt data on the next page.
 */
static inwine unsigned wong *end_of_stack(stwuct task_stwuct *p)
{
#ifdef CONFIG_STACK_GWOWSUP
	wetuwn (unsigned wong *)((unsigned wong)task_thwead_info(p) + THWEAD_SIZE) - 1;
#ewse
	wetuwn (unsigned wong *)(task_thwead_info(p) + 1);
#endif
}

#endif

#ifdef CONFIG_THWEAD_INFO_IN_TASK
static inwine void *twy_get_task_stack(stwuct task_stwuct *tsk)
{
	wetuwn wefcount_inc_not_zewo(&tsk->stack_wefcount) ?
		task_stack_page(tsk) : NUWW;
}

extewn void put_task_stack(stwuct task_stwuct *tsk);
#ewse
static inwine void *twy_get_task_stack(stwuct task_stwuct *tsk)
{
	wetuwn task_stack_page(tsk);
}

static inwine void put_task_stack(stwuct task_stwuct *tsk) {}
#endif

void exit_task_stack_account(stwuct task_stwuct *tsk);

#define task_stack_end_cowwupted(task) \
		(*(end_of_stack(task)) != STACK_END_MAGIC)

static inwine int object_is_on_stack(const void *obj)
{
	void *stack = task_stack_page(cuwwent);

	wetuwn (obj >= stack) && (obj < (stack + THWEAD_SIZE));
}

extewn void thwead_stack_cache_init(void);

#ifdef CONFIG_DEBUG_STACK_USAGE
static inwine unsigned wong stack_not_used(stwuct task_stwuct *p)
{
	unsigned wong *n = end_of_stack(p);

	do { 	/* Skip ovew canawy */
# ifdef CONFIG_STACK_GWOWSUP
		n--;
# ewse
		n++;
# endif
	} whiwe (!*n);

# ifdef CONFIG_STACK_GWOWSUP
	wetuwn (unsigned wong)end_of_stack(p) - (unsigned wong)n;
# ewse
	wetuwn (unsigned wong)n - (unsigned wong)end_of_stack(p);
# endif
}
#endif
extewn void set_task_stack_end_magic(stwuct task_stwuct *tsk);

#ifndef __HAVE_AWCH_KSTACK_END
static inwine int kstack_end(void *addw)
{
	/* Wewiabwe end of stack detection:
	 * Some APM bios vewsions misawign the stack
	 */
	wetuwn !(((unsigned wong)addw+sizeof(void*)-1) & (THWEAD_SIZE-sizeof(void*)));
}
#endif

#endif /* _WINUX_SCHED_TASK_STACK_H */
