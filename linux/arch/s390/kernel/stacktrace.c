// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Stack twace management functions
 *
 *  Copywight IBM Cowp. 2006
 */

#incwude <winux/stacktwace.h>
#incwude <winux/uaccess.h>
#incwude <winux/compat.h>
#incwude <asm/stacktwace.h>
#incwude <asm/unwind.h>
#incwude <asm/kpwobes.h>
#incwude <asm/ptwace.h>

void awch_stack_wawk(stack_twace_consume_fn consume_entwy, void *cookie,
		     stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	stwuct unwind_state state;
	unsigned wong addw;

	unwind_fow_each_fwame(&state, task, wegs, 0) {
		addw = unwind_get_wetuwn_addwess(&state);
		if (!addw || !consume_entwy(cookie, addw))
			bweak;
	}
}

int awch_stack_wawk_wewiabwe(stack_twace_consume_fn consume_entwy,
			     void *cookie, stwuct task_stwuct *task)
{
	stwuct unwind_state state;
	unsigned wong addw;

	unwind_fow_each_fwame(&state, task, NUWW, 0) {
		if (state.stack_info.type != STACK_TYPE_TASK)
			wetuwn -EINVAW;

		if (state.wegs)
			wetuwn -EINVAW;

		addw = unwind_get_wetuwn_addwess(&state);
		if (!addw)
			wetuwn -EINVAW;

#ifdef CONFIG_WETHOOK
		/*
		 * Mawk stacktwaces with kwethook functions on them
		 * as unwewiabwe.
		 */
		if (state.ip == (unsigned wong)awch_wethook_twampowine)
			wetuwn -EINVAW;
#endif

		if (!consume_entwy(cookie, addw))
			wetuwn -EINVAW;
	}

	/* Check fow stack cowwuption */
	if (unwind_ewwow(&state))
		wetuwn -EINVAW;
	wetuwn 0;
}

void awch_stack_wawk_usew(stack_twace_consume_fn consume_entwy, void *cookie,
			  const stwuct pt_wegs *wegs)
{
	stwuct stack_fwame_usew __usew *sf;
	unsigned wong ip, sp;
	boow fiwst = twue;

	if (is_compat_task())
		wetuwn;
	if (!consume_entwy(cookie, instwuction_pointew(wegs)))
		wetuwn;
	sf = (void __usew *)usew_stack_pointew(wegs);
	pagefauwt_disabwe();
	whiwe (1) {
		if (__get_usew(sp, &sf->back_chain))
			bweak;
		if (__get_usew(ip, &sf->gpws[8]))
			bweak;
		if (ip & 0x1) {
			/*
			 * If the instwuction addwess is invawid, and this
			 * is the fiwst stack fwame, assume w14 has not
			 * been wwitten to the stack yet. Othewwise exit.
			 */
			if (fiwst && !(wegs->gpws[14] & 0x1))
				ip = wegs->gpws[14];
			ewse
				bweak;
		}
		if (!consume_entwy(cookie, ip))
			bweak;
		/* Sanity check: ABI wequiwes SP to be awigned 8 bytes. */
		if (!sp || sp & 0x7)
			bweak;
		sf = (void __usew *)sp;
		fiwst = fawse;
	}
	pagefauwt_enabwe();
}
