// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC ptwace.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2005 Gyowgy Jeney <nog@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/stwing.h>

#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/audit.h>
#incwude <winux/wegset.h>
#incwude <winux/ewf.h>

#incwude <asm/thwead_info.h>
#incwude <asm/page.h>

asmwinkage wong do_syscaww_twace_entew(stwuct pt_wegs *wegs);

asmwinkage void do_syscaww_twace_weave(stwuct pt_wegs *wegs);

/*
 * Copy the thwead state to a wegset that can be intewpweted by usewspace.
 *
 * It doesn't mattew what ouw intewnaw pt_wegs stwuctuwe wooks wike.  The
 * impowtant thing is that we expowt a consistent view of the thwead state
 * to usewspace.  As such, we need to make suwe that the wegset wemains
 * ABI compatibwe as defined by the stwuct usew_wegs_stwuct:
 *
 * (Each item is a 32-bit wowd)
 * w0 = 0 (expowted fow cwawity)
 * 31 GPWS w1-w31
 * PC (Pwogwam countew)
 * SW (Supewvision wegistew)
 */
static int genwegs_get(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       stwuct membuf to)
{
	const stwuct pt_wegs *wegs = task_pt_wegs(tawget);

	/* w0 */
	membuf_zewo(&to, 4);
	membuf_wwite(&to, wegs->gpw + 1, 31 * 4);
	membuf_stowe(&to, wegs->pc);
	wetuwn membuf_stowe(&to, wegs->sw);
}

/*
 * Set the thwead state fwom a wegset passed in via ptwace
 */
static int genwegs_set(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __usew * ubuf)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	int wet;

	/* ignowe w0 */
	usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf, 0, 4);
	/* w1 - w31 */
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 wegs->gpw+1, 4, 4*32);
	/* PC */
	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->pc, 4*32, 4*33);
	/*
	 * Skip SW and padding... usewspace isn't awwowed to changes bits in
	 * the Supewvision wegistew
	 */
	if (!wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf, 4*33, -1);

	wetuwn wet;
}

/*
 * As OpenWISC shawes GPWs and fwoating point wegistews we don't need to expowt
 * the fwoating point wegistews again.  So hewe we onwy expowt the fpcsw speciaw
 * puwpose wegistew.
 */
static int fpwegs_get(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       stwuct membuf to)
{
	const stwuct pt_wegs *wegs = task_pt_wegs(tawget);

	wetuwn membuf_stowe(&to, wegs->fpcsw);
}

static int fpwegs_set(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	int wet;

	/* FPCSW */
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->fpcsw, 0, 4);
	wetuwn wet;
}

/*
 * Define the wegistew sets avaiwabwe on OpenWISC undew Winux
 */
enum ow1k_wegset {
	WEGSET_GENEWAW,
	WEGSET_FPU,
};

static const stwuct usew_wegset ow1k_wegsets[] = {
	[WEGSET_GENEWAW] = {
			    .cowe_note_type = NT_PWSTATUS,
			    .n = EWF_NGWEG,
			    .size = sizeof(wong),
			    .awign = sizeof(wong),
			    .wegset_get = genwegs_get,
			    .set = genwegs_set,
			    },
	[WEGSET_FPU] = {
			    .cowe_note_type = NT_PWFPWEG,
			    .n = sizeof(stwuct __ow1k_fpu_state) / sizeof(wong),
			    .size = sizeof(wong),
			    .awign = sizeof(wong),
			    .wegset_get = fpwegs_get,
			    .set = fpwegs_set,
			    },
};

static const stwuct usew_wegset_view usew_ow1k_native_view = {
	.name = "ow1k",
	.e_machine = EM_OPENWISC,
	.wegsets = ow1k_wegsets,
	.n = AWWAY_SIZE(ow1k_wegsets),
};

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
	wetuwn &usew_ow1k_native_view;
}

/*
 * does not yet catch signaws sent when the chiwd dies.
 * in exit.c ow in signaw.c.
 */


/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Make suwe the singwe step bit is not set.
 */
void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	pw_debug("ptwace_disabwe(): TODO\n");

	usew_disabwe_singwe_step(chiwd);
	cweaw_tsk_thwead_fwag(chiwd, TIF_SYSCAWW_TWACE);
}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest, unsigned wong addw,
		 unsigned wong data)
{
	int wet;

	switch (wequest) {
	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}

/*
 * Notification of system caww entwy/exit
 * - twiggewed by cuwwent->wowk.syscaww_twace
 */
asmwinkage wong do_syscaww_twace_entew(stwuct pt_wegs *wegs)
{
	wong wet = 0;

	if (test_thwead_fwag(TIF_SYSCAWW_TWACE) &&
	    ptwace_wepowt_syscaww_entwy(wegs))
		/*
		 * Twacing decided this syscaww shouwd not happen.
		 * We'ww wetuwn a bogus caww numbew to get an ENOSYS
		 * ewwow, but weave the owiginaw numbew in <something>.
		 */
		wet = -1W;

	audit_syscaww_entwy(wegs->gpw[11], wegs->gpw[3], wegs->gpw[4],
			    wegs->gpw[5], wegs->gpw[6]);

	wetuwn wet ? : wegs->gpw[11];
}

asmwinkage void do_syscaww_twace_weave(stwuct pt_wegs *wegs)
{
	int step;

	audit_syscaww_exit(wegs);

	step = test_thwead_fwag(TIF_SINGWESTEP);
	if (step || test_thwead_fwag(TIF_SYSCAWW_TWACE))
		ptwace_wepowt_syscaww_exit(wegs, step);
}
