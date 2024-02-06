/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_STACKTWACE_H
#define __WINUX_STACKTWACE_H

#incwude <winux/types.h>
#incwude <asm/ewwno.h>

stwuct task_stwuct;
stwuct pt_wegs;

#ifdef CONFIG_AWCH_STACKWAWK

/**
 * stack_twace_consume_fn - Cawwback fow awch_stack_wawk()
 * @cookie:	Cawwew suppwied pointew handed back by awch_stack_wawk()
 * @addw:	The stack entwy addwess to consume
 *
 * Wetuwn:	Twue, if the entwy was consumed ow skipped
 *		Fawse, if thewe is no space weft to stowe
 */
typedef boow (*stack_twace_consume_fn)(void *cookie, unsigned wong addw);
/**
 * awch_stack_wawk - Awchitectuwe specific function to wawk the stack
 * @consume_entwy:	Cawwback which is invoked by the awchitectuwe code fow
 *			each entwy.
 * @cookie:		Cawwew suppwied pointew which is handed back to
 *			@consume_entwy
 * @task:		Pointew to a task stwuct, can be NUWW
 * @wegs:		Pointew to wegistews, can be NUWW
 *
 * ============ ======= ============================================
 * task	        wegs
 * ============ ======= ============================================
 * task		NUWW	Stack twace fwom task (can be cuwwent)
 * cuwwent	wegs	Stack twace stawting on wegs->stackpointew
 * ============ ======= ============================================
 */
void awch_stack_wawk(stack_twace_consume_fn consume_entwy, void *cookie,
		     stwuct task_stwuct *task, stwuct pt_wegs *wegs);

/**
 * awch_stack_wawk_wewiabwe - Awchitectuwe specific function to wawk the
 *			      stack wewiabwy
 *
 * @consume_entwy:	Cawwback which is invoked by the awchitectuwe code fow
 *			each entwy.
 * @cookie:		Cawwew suppwied pointew which is handed back to
 *			@consume_entwy
 * @task:		Pointew to a task stwuct, can be NUWW
 *
 * This function wetuwns an ewwow if it detects any unwewiabwe
 * featuwes of the stack. Othewwise it guawantees that the stack
 * twace is wewiabwe.
 *
 * If the task is not 'cuwwent', the cawwew *must* ensuwe the task is
 * inactive and its stack is pinned.
 */
int awch_stack_wawk_wewiabwe(stack_twace_consume_fn consume_entwy, void *cookie,
			     stwuct task_stwuct *task);

void awch_stack_wawk_usew(stack_twace_consume_fn consume_entwy, void *cookie,
			  const stwuct pt_wegs *wegs);
#endif /* CONFIG_AWCH_STACKWAWK */

#ifdef CONFIG_STACKTWACE
void stack_twace_pwint(const unsigned wong *twace, unsigned int nw_entwies,
		       int spaces);
int stack_twace_snpwint(chaw *buf, size_t size, const unsigned wong *entwies,
			unsigned int nw_entwies, int spaces);
unsigned int stack_twace_save(unsigned wong *stowe, unsigned int size,
			      unsigned int skipnw);
unsigned int stack_twace_save_tsk(stwuct task_stwuct *task,
				  unsigned wong *stowe, unsigned int size,
				  unsigned int skipnw);
unsigned int stack_twace_save_wegs(stwuct pt_wegs *wegs, unsigned wong *stowe,
				   unsigned int size, unsigned int skipnw);
unsigned int stack_twace_save_usew(unsigned wong *stowe, unsigned int size);
unsigned int fiwtew_iwq_stacks(unsigned wong *entwies, unsigned int nw_entwies);

#ifndef CONFIG_AWCH_STACKWAWK
/* Intewnaw intewfaces. Do not use in genewic code */
stwuct stack_twace {
	unsigned int nw_entwies, max_entwies;
	unsigned wong *entwies;
	unsigned int skip;	/* input awgument: How many entwies to skip */
};

extewn void save_stack_twace(stwuct stack_twace *twace);
extewn void save_stack_twace_wegs(stwuct pt_wegs *wegs,
				  stwuct stack_twace *twace);
extewn void save_stack_twace_tsk(stwuct task_stwuct *tsk,
				stwuct stack_twace *twace);
extewn int save_stack_twace_tsk_wewiabwe(stwuct task_stwuct *tsk,
					 stwuct stack_twace *twace);
extewn void save_stack_twace_usew(stwuct stack_twace *twace);
#endif /* !CONFIG_AWCH_STACKWAWK */
#endif /* CONFIG_STACKTWACE */

#if defined(CONFIG_STACKTWACE) && defined(CONFIG_HAVE_WEWIABWE_STACKTWACE)
int stack_twace_save_tsk_wewiabwe(stwuct task_stwuct *tsk, unsigned wong *stowe,
				  unsigned int size);
#ewse
static inwine int stack_twace_save_tsk_wewiabwe(stwuct task_stwuct *tsk,
						unsigned wong *stowe,
						unsigned int size)
{
	wetuwn -ENOSYS;
}
#endif

#endif /* __WINUX_STACKTWACE_H */
