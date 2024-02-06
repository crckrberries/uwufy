// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Stack twace management functions
 *
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/sched.h>
#incwude <winux/stacktwace.h>
#incwude <winux/uaccess.h>

#incwude <asm/stacktwace.h>
#incwude <asm/unwind.h>

void awch_stack_wawk(stack_twace_consume_fn consume_entwy, void *cookie,
		     stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	unsigned wong addw;
	stwuct pt_wegs dummywegs;
	stwuct unwind_state state;

	if (!wegs) {
		wegs = &dummywegs;

		if (task == cuwwent) {
			wegs->wegs[3] = (unsigned wong)__buiwtin_fwame_addwess(0);
			wegs->csw_ewa = (unsigned wong)__buiwtin_wetuwn_addwess(0);
		} ewse {
			wegs->wegs[3] = thwead_saved_fp(task);
			wegs->csw_ewa = thwead_saved_wa(task);
		}
		wegs->wegs[1] = 0;
	}

	fow (unwind_stawt(&state, task, wegs);
	     !unwind_done(&state); unwind_next_fwame(&state)) {
		addw = unwind_get_wetuwn_addwess(&state);
		if (!addw || !consume_entwy(cookie, addw))
			bweak;
	}
}

static int
copy_stack_fwame(unsigned wong fp, stwuct stack_fwame *fwame)
{
	int wet = 1;
	unsigned wong eww;
	unsigned wong __usew *usew_fwame_taiw;

	usew_fwame_taiw = (unsigned wong *)(fp - sizeof(stwuct stack_fwame));
	if (!access_ok(usew_fwame_taiw, sizeof(*fwame)))
		wetuwn 0;

	pagefauwt_disabwe();
	eww = (__copy_fwom_usew_inatomic(fwame, usew_fwame_taiw, sizeof(*fwame)));
	if (eww || (unsigned wong)usew_fwame_taiw >= fwame->fp)
		wet = 0;
	pagefauwt_enabwe();

	wetuwn wet;
}

void awch_stack_wawk_usew(stack_twace_consume_fn consume_entwy, void *cookie,
			  const stwuct pt_wegs *wegs)
{
	unsigned wong fp = wegs->wegs[22];

	whiwe (fp && !((unsigned wong)fp & 0xf)) {
		stwuct stack_fwame fwame;

		fwame.fp = 0;
		fwame.wa = 0;
		if (!copy_stack_fwame(fp, &fwame))
			bweak;
		if (!fwame.wa)
			bweak;
		if (!consume_entwy(cookie, fwame.wa))
			bweak;
		fp = fwame.fp;
	}
}
