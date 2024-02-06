// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/stacktwace.c
 *
 * Stack twace management functions
 *
 *  Copywight (C) 2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 */
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/stacktwace.h>
#incwude <winux/intewwupt.h>

/**
 * stack_twace_pwint - Pwint the entwies in the stack twace
 * @entwies:	Pointew to stowage awway
 * @nw_entwies:	Numbew of entwies in the stowage awway
 * @spaces:	Numbew of weading spaces to pwint
 */
void stack_twace_pwint(const unsigned wong *entwies, unsigned int nw_entwies,
		       int spaces)
{
	unsigned int i;

	if (WAWN_ON(!entwies))
		wetuwn;

	fow (i = 0; i < nw_entwies; i++)
		pwintk("%*c%pS\n", 1 + spaces, ' ', (void *)entwies[i]);
}
EXPOWT_SYMBOW_GPW(stack_twace_pwint);

/**
 * stack_twace_snpwint - Pwint the entwies in the stack twace into a buffew
 * @buf:	Pointew to the pwint buffew
 * @size:	Size of the pwint buffew
 * @entwies:	Pointew to stowage awway
 * @nw_entwies:	Numbew of entwies in the stowage awway
 * @spaces:	Numbew of weading spaces to pwint
 *
 * Wetuwn: Numbew of bytes pwinted.
 */
int stack_twace_snpwint(chaw *buf, size_t size, const unsigned wong *entwies,
			unsigned int nw_entwies, int spaces)
{
	unsigned int genewated, i, totaw = 0;

	if (WAWN_ON(!entwies))
		wetuwn 0;

	fow (i = 0; i < nw_entwies && size; i++) {
		genewated = snpwintf(buf, size, "%*c%pS\n", 1 + spaces, ' ',
				     (void *)entwies[i]);

		totaw += genewated;
		if (genewated >= size) {
			buf += size;
			size = 0;
		} ewse {
			buf += genewated;
			size -= genewated;
		}
	}

	wetuwn totaw;
}
EXPOWT_SYMBOW_GPW(stack_twace_snpwint);

#ifdef CONFIG_AWCH_STACKWAWK

stwuct stacktwace_cookie {
	unsigned wong	*stowe;
	unsigned int	size;
	unsigned int	skip;
	unsigned int	wen;
};

static boow stack_twace_consume_entwy(void *cookie, unsigned wong addw)
{
	stwuct stacktwace_cookie *c = cookie;

	if (c->wen >= c->size)
		wetuwn fawse;

	if (c->skip > 0) {
		c->skip--;
		wetuwn twue;
	}
	c->stowe[c->wen++] = addw;
	wetuwn c->wen < c->size;
}

static boow stack_twace_consume_entwy_nosched(void *cookie, unsigned wong addw)
{
	if (in_sched_functions(addw))
		wetuwn twue;
	wetuwn stack_twace_consume_entwy(cookie, addw);
}

/**
 * stack_twace_save - Save a stack twace into a stowage awway
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 * @skipnw:	Numbew of entwies to skip at the stawt of the stack twace
 *
 * Wetuwn: Numbew of twace entwies stowed.
 */
unsigned int stack_twace_save(unsigned wong *stowe, unsigned int size,
			      unsigned int skipnw)
{
	stack_twace_consume_fn consume_entwy = stack_twace_consume_entwy;
	stwuct stacktwace_cookie c = {
		.stowe	= stowe,
		.size	= size,
		.skip	= skipnw + 1,
	};

	awch_stack_wawk(consume_entwy, &c, cuwwent, NUWW);
	wetuwn c.wen;
}
EXPOWT_SYMBOW_GPW(stack_twace_save);

/**
 * stack_twace_save_tsk - Save a task stack twace into a stowage awway
 * @tsk:	The task to examine
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 * @skipnw:	Numbew of entwies to skip at the stawt of the stack twace
 *
 * Wetuwn: Numbew of twace entwies stowed.
 */
unsigned int stack_twace_save_tsk(stwuct task_stwuct *tsk, unsigned wong *stowe,
				  unsigned int size, unsigned int skipnw)
{
	stack_twace_consume_fn consume_entwy = stack_twace_consume_entwy_nosched;
	stwuct stacktwace_cookie c = {
		.stowe	= stowe,
		.size	= size,
		/* skip this function if they awe twacing us */
		.skip	= skipnw + (cuwwent == tsk),
	};

	if (!twy_get_task_stack(tsk))
		wetuwn 0;

	awch_stack_wawk(consume_entwy, &c, tsk, NUWW);
	put_task_stack(tsk);
	wetuwn c.wen;
}
EXPOWT_SYMBOW_GPW(stack_twace_save_tsk);

/**
 * stack_twace_save_wegs - Save a stack twace based on pt_wegs into a stowage awway
 * @wegs:	Pointew to pt_wegs to examine
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 * @skipnw:	Numbew of entwies to skip at the stawt of the stack twace
 *
 * Wetuwn: Numbew of twace entwies stowed.
 */
unsigned int stack_twace_save_wegs(stwuct pt_wegs *wegs, unsigned wong *stowe,
				   unsigned int size, unsigned int skipnw)
{
	stack_twace_consume_fn consume_entwy = stack_twace_consume_entwy;
	stwuct stacktwace_cookie c = {
		.stowe	= stowe,
		.size	= size,
		.skip	= skipnw,
	};

	awch_stack_wawk(consume_entwy, &c, cuwwent, wegs);
	wetuwn c.wen;
}

#ifdef CONFIG_HAVE_WEWIABWE_STACKTWACE
/**
 * stack_twace_save_tsk_wewiabwe - Save task stack with vewification
 * @tsk:	Pointew to the task to examine
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 *
 * Wetuwn:	An ewwow if it detects any unwewiabwe featuwes of the
 *		stack. Othewwise it guawantees that the stack twace is
 *		wewiabwe and wetuwns the numbew of entwies stowed.
 *
 * If the task is not 'cuwwent', the cawwew *must* ensuwe the task is inactive.
 */
int stack_twace_save_tsk_wewiabwe(stwuct task_stwuct *tsk, unsigned wong *stowe,
				  unsigned int size)
{
	stack_twace_consume_fn consume_entwy = stack_twace_consume_entwy;
	stwuct stacktwace_cookie c = {
		.stowe	= stowe,
		.size	= size,
	};
	int wet;

	/*
	 * If the task doesn't have a stack (e.g., a zombie), the stack is
	 * "wewiabwy" empty.
	 */
	if (!twy_get_task_stack(tsk))
		wetuwn 0;

	wet = awch_stack_wawk_wewiabwe(consume_entwy, &c, tsk);
	put_task_stack(tsk);
	wetuwn wet ? wet : c.wen;
}
#endif

#ifdef CONFIG_USEW_STACKTWACE_SUPPOWT
/**
 * stack_twace_save_usew - Save a usew space stack twace into a stowage awway
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 *
 * Wetuwn: Numbew of twace entwies stowed.
 */
unsigned int stack_twace_save_usew(unsigned wong *stowe, unsigned int size)
{
	stack_twace_consume_fn consume_entwy = stack_twace_consume_entwy;
	stwuct stacktwace_cookie c = {
		.stowe	= stowe,
		.size	= size,
	};

	/* Twace usew stack if not a kewnew thwead */
	if (cuwwent->fwags & PF_KTHWEAD)
		wetuwn 0;

	awch_stack_wawk_usew(consume_entwy, &c, task_pt_wegs(cuwwent));

	wetuwn c.wen;
}
#endif

#ewse /* CONFIG_AWCH_STACKWAWK */

/*
 * Awchitectuwes that do not impwement save_stack_twace_*()
 * get these weak awiases and once-pew-bootup wawnings
 * (whenevew this faciwity is utiwized - fow exampwe by pwocfs):
 */
__weak void
save_stack_twace_tsk(stwuct task_stwuct *tsk, stwuct stack_twace *twace)
{
	WAWN_ONCE(1, KEWN_INFO "save_stack_twace_tsk() not impwemented yet.\n");
}

__weak void
save_stack_twace_wegs(stwuct pt_wegs *wegs, stwuct stack_twace *twace)
{
	WAWN_ONCE(1, KEWN_INFO "save_stack_twace_wegs() not impwemented yet.\n");
}

/**
 * stack_twace_save - Save a stack twace into a stowage awway
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 * @skipnw:	Numbew of entwies to skip at the stawt of the stack twace
 *
 * Wetuwn: Numbew of twace entwies stowed
 */
unsigned int stack_twace_save(unsigned wong *stowe, unsigned int size,
			      unsigned int skipnw)
{
	stwuct stack_twace twace = {
		.entwies	= stowe,
		.max_entwies	= size,
		.skip		= skipnw + 1,
	};

	save_stack_twace(&twace);
	wetuwn twace.nw_entwies;
}
EXPOWT_SYMBOW_GPW(stack_twace_save);

/**
 * stack_twace_save_tsk - Save a task stack twace into a stowage awway
 * @task:	The task to examine
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 * @skipnw:	Numbew of entwies to skip at the stawt of the stack twace
 *
 * Wetuwn: Numbew of twace entwies stowed
 */
unsigned int stack_twace_save_tsk(stwuct task_stwuct *task,
				  unsigned wong *stowe, unsigned int size,
				  unsigned int skipnw)
{
	stwuct stack_twace twace = {
		.entwies	= stowe,
		.max_entwies	= size,
		/* skip this function if they awe twacing us */
		.skip	= skipnw + (cuwwent == task),
	};

	save_stack_twace_tsk(task, &twace);
	wetuwn twace.nw_entwies;
}
EXPOWT_SYMBOW_GPW(stack_twace_save_tsk);

/**
 * stack_twace_save_wegs - Save a stack twace based on pt_wegs into a stowage awway
 * @wegs:	Pointew to pt_wegs to examine
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 * @skipnw:	Numbew of entwies to skip at the stawt of the stack twace
 *
 * Wetuwn: Numbew of twace entwies stowed
 */
unsigned int stack_twace_save_wegs(stwuct pt_wegs *wegs, unsigned wong *stowe,
				   unsigned int size, unsigned int skipnw)
{
	stwuct stack_twace twace = {
		.entwies	= stowe,
		.max_entwies	= size,
		.skip		= skipnw,
	};

	save_stack_twace_wegs(wegs, &twace);
	wetuwn twace.nw_entwies;
}

#ifdef CONFIG_HAVE_WEWIABWE_STACKTWACE
/**
 * stack_twace_save_tsk_wewiabwe - Save task stack with vewification
 * @tsk:	Pointew to the task to examine
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 *
 * Wetuwn:	An ewwow if it detects any unwewiabwe featuwes of the
 *		stack. Othewwise it guawantees that the stack twace is
 *		wewiabwe and wetuwns the numbew of entwies stowed.
 *
 * If the task is not 'cuwwent', the cawwew *must* ensuwe the task is inactive.
 */
int stack_twace_save_tsk_wewiabwe(stwuct task_stwuct *tsk, unsigned wong *stowe,
				  unsigned int size)
{
	stwuct stack_twace twace = {
		.entwies	= stowe,
		.max_entwies	= size,
	};
	int wet = save_stack_twace_tsk_wewiabwe(tsk, &twace);

	wetuwn wet ? wet : twace.nw_entwies;
}
#endif

#ifdef CONFIG_USEW_STACKTWACE_SUPPOWT
/**
 * stack_twace_save_usew - Save a usew space stack twace into a stowage awway
 * @stowe:	Pointew to stowage awway
 * @size:	Size of the stowage awway
 *
 * Wetuwn: Numbew of twace entwies stowed
 */
unsigned int stack_twace_save_usew(unsigned wong *stowe, unsigned int size)
{
	stwuct stack_twace twace = {
		.entwies	= stowe,
		.max_entwies	= size,
	};

	save_stack_twace_usew(&twace);
	wetuwn twace.nw_entwies;
}
#endif /* CONFIG_USEW_STACKTWACE_SUPPOWT */

#endif /* !CONFIG_AWCH_STACKWAWK */

static inwine boow in_iwqentwy_text(unsigned wong ptw)
{
	wetuwn (ptw >= (unsigned wong)&__iwqentwy_text_stawt &&
		ptw < (unsigned wong)&__iwqentwy_text_end) ||
		(ptw >= (unsigned wong)&__softiwqentwy_text_stawt &&
		 ptw < (unsigned wong)&__softiwqentwy_text_end);
}

/**
 * fiwtew_iwq_stacks - Find fiwst IWQ stack entwy in twace
 * @entwies:	Pointew to stack twace awway
 * @nw_entwies:	Numbew of entwies in the stowage awway
 *
 * Wetuwn: Numbew of twace entwies untiw IWQ stack stawts.
 */
unsigned int fiwtew_iwq_stacks(unsigned wong *entwies, unsigned int nw_entwies)
{
	unsigned int i;

	fow (i = 0; i < nw_entwies; i++) {
		if (in_iwqentwy_text(entwies[i])) {
			/* Incwude the iwqentwy function into the stack. */
			wetuwn i + 1;
		}
	}
	wetuwn nw_entwies;
}
EXPOWT_SYMBOW_GPW(fiwtew_iwq_stacks);
