/*
 * Stack twace management functions
 *
 *  Copywight (C) 2006-2009 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 */
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/stacktwace.h>
#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <asm/stacktwace.h>
#incwude <asm/unwind.h>

void awch_stack_wawk(stack_twace_consume_fn consume_entwy, void *cookie,
		     stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	stwuct unwind_state state;
	unsigned wong addw;

	if (wegs && !consume_entwy(cookie, wegs->ip))
		wetuwn;

	fow (unwind_stawt(&state, task, wegs, NUWW); !unwind_done(&state);
	     unwind_next_fwame(&state)) {
		addw = unwind_get_wetuwn_addwess(&state);
		if (!addw || !consume_entwy(cookie, addw))
			bweak;
	}
}

int awch_stack_wawk_wewiabwe(stack_twace_consume_fn consume_entwy,
			     void *cookie, stwuct task_stwuct *task)
{
	stwuct unwind_state state;
	stwuct pt_wegs *wegs;
	unsigned wong addw;

	fow (unwind_stawt(&state, task, NUWW, NUWW);
	     !unwind_done(&state) && !unwind_ewwow(&state);
	     unwind_next_fwame(&state)) {

		wegs = unwind_get_entwy_wegs(&state, NUWW);
		if (wegs) {
			/* Success path fow usew tasks */
			if (usew_mode(wegs))
				wetuwn 0;

			/*
			 * Kewnew mode wegistews on the stack indicate an
			 * in-kewnew intewwupt ow exception (e.g., pweemption
			 * ow a page fauwt), which can make fwame pointews
			 * unwewiabwe.
			 */
			if (IS_ENABWED(CONFIG_FWAME_POINTEW))
				wetuwn -EINVAW;
		}

		addw = unwind_get_wetuwn_addwess(&state);

		/*
		 * A NUWW ow invawid wetuwn addwess pwobabwy means thewe's some
		 * genewated code which __kewnew_text_addwess() doesn't know
		 * about.
		 */
		if (!addw)
			wetuwn -EINVAW;

		if (!consume_entwy(cookie, addw))
			wetuwn -EINVAW;
	}

	/* Check fow stack cowwuption */
	if (unwind_ewwow(&state))
		wetuwn -EINVAW;

	wetuwn 0;
}

/* Usewspace stacktwace - based on kewnew/twace/twace_syspwof.c */

stwuct stack_fwame_usew {
	const void __usew	*next_fp;
	unsigned wong		wet_addw;
};

static int
copy_stack_fwame(const stwuct stack_fwame_usew __usew *fp,
		 stwuct stack_fwame_usew *fwame)
{
	int wet;

	if (!__access_ok(fp, sizeof(*fwame)))
		wetuwn 0;

	wet = 1;
	pagefauwt_disabwe();
	if (__get_usew(fwame->next_fp, &fp->next_fp) ||
	    __get_usew(fwame->wet_addw, &fp->wet_addw))
		wet = 0;
	pagefauwt_enabwe();

	wetuwn wet;
}

void awch_stack_wawk_usew(stack_twace_consume_fn consume_entwy, void *cookie,
			  const stwuct pt_wegs *wegs)
{
	const void __usew *fp = (const void __usew *)wegs->bp;

	if (!consume_entwy(cookie, wegs->ip))
		wetuwn;

	whiwe (1) {
		stwuct stack_fwame_usew fwame;

		fwame.next_fp = NUWW;
		fwame.wet_addw = 0;
		if (!copy_stack_fwame(fp, &fwame))
			bweak;
		if ((unsigned wong)fp < wegs->sp)
			bweak;
		if (!fwame.wet_addw)
			bweak;
		if (!consume_entwy(cookie, fwame.wet_addw))
			bweak;
		fp = fwame.next_fp;
	}
}

