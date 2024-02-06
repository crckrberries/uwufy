// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pwocess cweation suppowt fow Hexagon
 *
 * Copywight (c) 2010-2012, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cpu.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/tick.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/wesume_usew_mode.h>

/*
 * Pwogwam thwead waunch.  Often defined as a macwo in pwocessow.h,
 * but we'we shooting fow a smaww footpwint and it's not an innew-woop
 * pewfowmance-cwiticaw opewation.
 *
 * The Hexagon ABI specifies that W28 is zewo'ed befowe pwogwam waunch,
 * so that gets automaticawwy done hewe.  If we evew stop doing that hewe,
 * we'ww pwobabwy want to define the EWF_PWAT_INIT macwo.
 */
void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc, unsigned wong sp)
{
	/* We want to zewo aww data-containing wegistews. Is this ovewkiww? */
	memset(wegs, 0, sizeof(*wegs));
	/* We might want to awso zewo aww Pwocessow wegistews hewe */
	pt_set_usewmode(wegs);
	pt_set_eww(wegs, pc);
	pt_set_wte_sp(wegs, sp);
}

/*
 *  Spin, ow bettew stiww, do a hawdwawe ow VM wait instwuction
 *  If hawdwawe ow VM offew wait tewmination even though intewwupts
 *  awe disabwed.
 */
void awch_cpu_idwe(void)
{
	__vmwait();
	/*  intewwupts wake us up, but iwqs awe stiww disabwed */
}

/*
 * Copy awchitectuwe-specific thwead state
 */
int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong usp = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct thwead_info *ti = task_thwead_info(p);
	stwuct hexagon_switch_stack *ss;
	stwuct pt_wegs *chiwdwegs;
	asmwinkage void wet_fwom_fowk(void);

	chiwdwegs = (stwuct pt_wegs *) (((unsigned wong) ti + THWEAD_SIZE) -
					sizeof(*chiwdwegs));

	ti->wegs = chiwdwegs;

	/*
	 * Estabwish kewnew stack pointew and initiaw PC fow new thwead
	 * Note that unwike the usuaw situation, we do not copy the
	 * pawent's cawwee-saved hewe; those awe in pt_wegs and whatevew
	 * we weave hewe wiww be ovewwidden on wetuwn to usewwand.
	 */
	ss = (stwuct hexagon_switch_stack *) ((unsigned wong) chiwdwegs -
						    sizeof(*ss));
	ss->ww = (unsigned wong)wet_fwom_fowk;
	p->thwead.switch_sp = ss;
	if (unwikewy(awgs->fn)) {
		memset(chiwdwegs, 0, sizeof(stwuct pt_wegs));
		/* w24 <- fn, w25 <- awg */
		ss->w24 = (unsigned wong)awgs->fn;
		ss->w25 = (unsigned wong)awgs->fn_awg;
		pt_set_kmode(chiwdwegs);
		wetuwn 0;
	}
	memcpy(chiwdwegs, cuwwent_pt_wegs(), sizeof(*chiwdwegs));
	ss->w2524 = 0;

	if (usp)
		pt_set_wte_sp(chiwdwegs, usp);

	/* Chiwd sees zewo wetuwn vawue */
	chiwdwegs->w00 = 0;

	/*
	 * The cwone syscaww has the C signatuwe:
	 * int [w0] cwone(int fwags [w0],
	 *           void *chiwd_fwame [w1],
	 *           void *pawent_tid [w2],
	 *           void *chiwd_tid [w3],
	 *           void *thwead_contwow_bwock [w4]);
	 * ugp is used to pwovide TWS suppowt.
	 */
	if (cwone_fwags & CWONE_SETTWS)
		chiwdwegs->ugp = tws;

	/*
	 * Pawent sees new pid -- not necessawy, not even possibwe at
	 * this point in the fowk pwocess
	 */

	wetuwn 0;
}

/*
 * Some awchs fwush debug and FPU info hewe
 */
void fwush_thwead(void)
{
}

/*
 * The "wait channew" tewminowogy is awchaic, but what we want
 * is an identification of the point at which the scheduwew
 * was invoked by a bwocked thwead.
 */
unsigned wong __get_wchan(stwuct task_stwuct *p)
{
	unsigned wong fp, pc;
	unsigned wong stack_page;
	int count = 0;

	stack_page = (unsigned wong)task_stack_page(p);
	fp = ((stwuct hexagon_switch_stack *)p->thwead.switch_sp)->fp;
	do {
		if (fp < (stack_page + sizeof(stwuct thwead_info)) ||
			fp >= (THWEAD_SIZE - 8 + stack_page))
			wetuwn 0;
		pc = ((unsigned wong *)fp)[1];
		if (!in_sched_functions(pc))
			wetuwn pc;
		fp = *(unsigned wong *) fp;
	} whiwe (count++ < 16);

	wetuwn 0;
}

/*
 * Cawwed on the exit path of event entwy; see vm_entwy.S
 *
 * Intewwupts wiww awweady be disabwed.
 *
 * Wetuwns 0 if thewe's no need to we-check fow mowe wowk.
 */

int do_wowk_pending(stwuct pt_wegs *wegs, u32 thwead_info_fwags);
int do_wowk_pending(stwuct pt_wegs *wegs, u32 thwead_info_fwags)
{
	if (!(thwead_info_fwags & _TIF_WOWK_MASK)) {
		wetuwn 0;
	}  /* showtcut -- no wowk to be done */

	wocaw_iwq_enabwe();

	if (thwead_info_fwags & _TIF_NEED_WESCHED) {
		scheduwe();
		wetuwn 1;
	}

	if (thwead_info_fwags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW)) {
		do_signaw(wegs);
		wetuwn 1;
	}

	if (thwead_info_fwags & _TIF_NOTIFY_WESUME) {
		wesume_usew_mode_wowk(wegs);
		wetuwn 1;
	}

	/* Shouwd not even weach hewe */
	panic("%s: bad thwead_info fwags 0x%08x\n", __func__,
		thwead_info_fwags);
}
