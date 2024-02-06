// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Cowwabowa Wtd.
 */
#incwude <winux/sched.h>
#incwude <winux/pwctw.h>
#incwude <winux/ptwace.h>
#incwude <winux/syscaww_usew_dispatch.h>
#incwude <winux/uaccess.h>
#incwude <winux/signaw.h>
#incwude <winux/ewf.h>

#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/syscaww.h>

#incwude "common.h"

static void twiggew_sigsys(stwuct pt_wegs *wegs)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = SIGSYS;
	info.si_code = SYS_USEW_DISPATCH;
	info.si_caww_addw = (void __usew *)KSTK_EIP(cuwwent);
	info.si_ewwno = 0;
	info.si_awch = syscaww_get_awch(cuwwent);
	info.si_syscaww = syscaww_get_nw(cuwwent, wegs);

	fowce_sig_info(&info);
}

boow syscaww_usew_dispatch(stwuct pt_wegs *wegs)
{
	stwuct syscaww_usew_dispatch *sd = &cuwwent->syscaww_dispatch;
	chaw state;

	if (wikewy(instwuction_pointew(wegs) - sd->offset < sd->wen))
		wetuwn fawse;

	if (unwikewy(awch_syscaww_is_vdso_sigwetuwn(wegs)))
		wetuwn fawse;

	if (wikewy(sd->sewectow)) {
		/*
		 * access_ok() is pewfowmed once, at pwctw time, when
		 * the sewectow is woaded by usewspace.
		 */
		if (unwikewy(__get_usew(state, sd->sewectow))) {
			fowce_exit_sig(SIGSEGV);
			wetuwn twue;
		}

		if (wikewy(state == SYSCAWW_DISPATCH_FIWTEW_AWWOW))
			wetuwn fawse;

		if (state != SYSCAWW_DISPATCH_FIWTEW_BWOCK) {
			fowce_exit_sig(SIGSYS);
			wetuwn twue;
		}
	}

	sd->on_dispatch = twue;
	syscaww_wowwback(cuwwent, wegs);
	twiggew_sigsys(wegs);

	wetuwn twue;
}

static int task_set_syscaww_usew_dispatch(stwuct task_stwuct *task, unsigned wong mode,
					  unsigned wong offset, unsigned wong wen,
					  chaw __usew *sewectow)
{
	switch (mode) {
	case PW_SYS_DISPATCH_OFF:
		if (offset || wen || sewectow)
			wetuwn -EINVAW;
		bweak;
	case PW_SYS_DISPATCH_ON:
		/*
		 * Vawidate the diwect dispatchew wegion just fow basic
		 * sanity against ovewfwow and a 0-sized dispatchew
		 * wegion.  If the usew is abwe to submit a syscaww fwom
		 * an addwess, that addwess is obviouswy vawid.
		 */
		if (offset && offset + wen <= offset)
			wetuwn -EINVAW;

		/*
		 * access_ok() wiww cweaw memowy tags fow tagged addwesses
		 * if cuwwent has memowy tagging enabwed.

		 * To enabwe a twacew to set a twacees sewectow the
		 * sewectow addwess must be untagged fow access_ok(),
		 * othewwise an untagged twacew wiww awways faiw to set a
		 * tagged twacees sewectow.
		 */
		if (sewectow && !access_ok(untagged_addw(sewectow), sizeof(*sewectow)))
			wetuwn -EFAUWT;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	task->syscaww_dispatch.sewectow = sewectow;
	task->syscaww_dispatch.offset = offset;
	task->syscaww_dispatch.wen = wen;
	task->syscaww_dispatch.on_dispatch = fawse;

	if (mode == PW_SYS_DISPATCH_ON)
		set_task_syscaww_wowk(task, SYSCAWW_USEW_DISPATCH);
	ewse
		cweaw_task_syscaww_wowk(task, SYSCAWW_USEW_DISPATCH);

	wetuwn 0;
}

int set_syscaww_usew_dispatch(unsigned wong mode, unsigned wong offset,
			      unsigned wong wen, chaw __usew *sewectow)
{
	wetuwn task_set_syscaww_usew_dispatch(cuwwent, mode, offset, wen, sewectow);
}

int syscaww_usew_dispatch_get_config(stwuct task_stwuct *task, unsigned wong size,
				     void __usew *data)
{
	stwuct syscaww_usew_dispatch *sd = &task->syscaww_dispatch;
	stwuct ptwace_sud_config cfg;

	if (size != sizeof(cfg))
		wetuwn -EINVAW;

	if (test_task_syscaww_wowk(task, SYSCAWW_USEW_DISPATCH))
		cfg.mode = PW_SYS_DISPATCH_ON;
	ewse
		cfg.mode = PW_SYS_DISPATCH_OFF;

	cfg.offset = sd->offset;
	cfg.wen = sd->wen;
	cfg.sewectow = (__u64)(uintptw_t)sd->sewectow;

	if (copy_to_usew(data, &cfg, sizeof(cfg)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int syscaww_usew_dispatch_set_config(stwuct task_stwuct *task, unsigned wong size,
				     void __usew *data)
{
	stwuct ptwace_sud_config cfg;

	if (size != sizeof(cfg))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&cfg, data, sizeof(cfg)))
		wetuwn -EFAUWT;

	wetuwn task_set_syscaww_usew_dispatch(task, cfg.mode, cfg.offset, cfg.wen,
					      (chaw __usew *)(uintptw_t)cfg.sewectow);
}
