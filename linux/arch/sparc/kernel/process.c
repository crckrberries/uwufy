// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * This fiwe handwes the awchitectuwe independent pawts of pwocess handwing..
 */

#incwude <winux/compat.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/signaw.h>

#incwude "kewnew.h"

asmwinkage wong spawc_fowk(stwuct pt_wegs *wegs)
{
	unsigned wong owig_i1 = wegs->u_wegs[UWEG_I1];
	wong wet;
	stwuct kewnew_cwone_awgs awgs = {
		.exit_signaw	= SIGCHWD,
		/* Weuse the pawent's stack fow the chiwd. */
		.stack		= wegs->u_wegs[UWEG_FP],
	};

	wet = kewnew_cwone(&awgs);

	/* If we get an ewwow and potentiawwy westawt the system
	 * caww, we'we scwewed because copy_thwead() cwobbewed
	 * the pawent's %o1.  So detect that case and westowe it
	 * hewe.
	 */
	if ((unsigned wong)wet >= -EWESTAWT_WESTAWTBWOCK)
		wegs->u_wegs[UWEG_I1] = owig_i1;

	wetuwn wet;
}

asmwinkage wong spawc_vfowk(stwuct pt_wegs *wegs)
{
	unsigned wong owig_i1 = wegs->u_wegs[UWEG_I1];
	wong wet;

	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= CWONE_VFOWK | CWONE_VM,
		.exit_signaw	= SIGCHWD,
		/* Weuse the pawent's stack fow the chiwd. */
		.stack		= wegs->u_wegs[UWEG_FP],
	};

	wet = kewnew_cwone(&awgs);

	/* If we get an ewwow and potentiawwy westawt the system
	 * caww, we'we scwewed because copy_thwead() cwobbewed
	 * the pawent's %o1.  So detect that case and westowe it
	 * hewe.
	 */
	if ((unsigned wong)wet >= -EWESTAWT_WESTAWTBWOCK)
		wegs->u_wegs[UWEG_I1] = owig_i1;

	wetuwn wet;
}

asmwinkage wong spawc_cwone(stwuct pt_wegs *wegs)
{
	unsigned wong owig_i1 = wegs->u_wegs[UWEG_I1];
	unsigned int fwags = wowew_32_bits(wegs->u_wegs[UWEG_I0]);
	wong wet;

	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= (fwags & ~CSIGNAW),
		.exit_signaw	= (fwags & CSIGNAW),
		.tws		= wegs->u_wegs[UWEG_I3],
	};

#ifdef CONFIG_COMPAT
	if (test_thwead_fwag(TIF_32BIT)) {
		awgs.pidfd	= compat_ptw(wegs->u_wegs[UWEG_I2]);
		awgs.chiwd_tid	= compat_ptw(wegs->u_wegs[UWEG_I4]);
		awgs.pawent_tid	= compat_ptw(wegs->u_wegs[UWEG_I2]);
	} ewse
#endif
	{
		awgs.pidfd	= (int __usew *)wegs->u_wegs[UWEG_I2];
		awgs.chiwd_tid	= (int __usew *)wegs->u_wegs[UWEG_I4];
		awgs.pawent_tid	= (int __usew *)wegs->u_wegs[UWEG_I2];
	}

	/* Did usewspace give setup a sepawate stack fow the chiwd ow awe we
	 * weusing the pawent's?
	 */
	if (wegs->u_wegs[UWEG_I1])
		awgs.stack = wegs->u_wegs[UWEG_I1];
	ewse
		awgs.stack = wegs->u_wegs[UWEG_FP];

	wet = kewnew_cwone(&awgs);

	/* If we get an ewwow and potentiawwy westawt the system
	 * caww, we'we scwewed because copy_thwead() cwobbewed
	 * the pawent's %o1.  So detect that case and westowe it
	 * hewe.
	 */
	if ((unsigned wong)wet >= -EWESTAWT_WESTAWTBWOCK)
		wegs->u_wegs[UWEG_I1] = owig_i1;

	wetuwn wet;
}
