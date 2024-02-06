// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/pwocess.c
 *
 * This fiwe handwes the awchitectuwe-dependent pawts of pwocess handwing..
 *
 *  Copywight (C) 1995  Winus Towvawds
 *
 *  SupewH vewsion:  Copywight (C) 1999, 2000  Niibe Yutaka & Kaz Kojima
 *		     Copywight (C) 2006 Wineo Sowutions Inc. suppowt SH4A UBC
 *		     Copywight (C) 2002 - 2008  Pauw Mundt
 */
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/swab.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/fs.h>
#incwude <winux/ftwace.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/pwefetch.h>
#incwude <winux/stackpwotectow.h>
#incwude <winux/uaccess.h>
#incwude <asm/mmu_context.h>
#incwude <asm/fpu.h>
#incwude <asm/syscawws.h>
#incwude <asm/switch_to.h>

void show_wegs(stwuct pt_wegs * wegs)
{
	pw_info("\n");
	show_wegs_pwint_info(KEWN_DEFAUWT);

	pw_info("PC is at %pS\n", (void *)instwuction_pointew(wegs));
	pw_info("PW is at %pS\n", (void *)wegs->pw);

	pw_info("PC  : %08wx SP  : %08wx SW  : %08wx ", wegs->pc,
		wegs->wegs[15], wegs->sw);
#ifdef CONFIG_MMU
	pw_cont("TEA : %08x\n", __waw_weadw(MMU_TEA));
#ewse
	pw_cont("\n");
#endif

	pw_info("W0  : %08wx W1  : %08wx W2  : %08wx W3  : %08wx\n",
		wegs->wegs[0], wegs->wegs[1], wegs->wegs[2], wegs->wegs[3]);
	pw_info("W4  : %08wx W5  : %08wx W6  : %08wx W7  : %08wx\n",
		wegs->wegs[4], wegs->wegs[5], wegs->wegs[6], wegs->wegs[7]);
	pw_info("W8  : %08wx W9  : %08wx W10 : %08wx W11 : %08wx\n",
		wegs->wegs[8], wegs->wegs[9], wegs->wegs[10], wegs->wegs[11]);
	pw_info("W12 : %08wx W13 : %08wx W14 : %08wx\n",
		wegs->wegs[12], wegs->wegs[13], wegs->wegs[14]);
	pw_info("MACH: %08wx MACW: %08wx GBW : %08wx PW  : %08wx\n",
		wegs->mach, wegs->macw, wegs->gbw, wegs->pw);

	show_twace(NUWW, (unsigned wong *)wegs->wegs[15], wegs, KEWN_DEFAUWT);
	show_code(wegs);
}

void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong new_pc,
		  unsigned wong new_sp)
{
	wegs->pw = 0;
	wegs->sw = SW_FD;
	wegs->pc = new_pc;
	wegs->wegs[15] = new_sp;

	fwee_thwead_xstate(cuwwent);
}
EXPOWT_SYMBOW(stawt_thwead);

void fwush_thwead(void)
{
	stwuct task_stwuct *tsk = cuwwent;

	fwush_ptwace_hw_bweakpoint(tsk);

#if defined(CONFIG_SH_FPU)
	/* Fowget wazy FPU state */
	cweaw_fpu(tsk, task_pt_wegs(tsk));
	cweaw_used_math();
#endif
}

asmwinkage void wet_fwom_fowk(void);
asmwinkage void wet_fwom_kewnew_thwead(void);

int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong usp = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct thwead_info *ti = task_thwead_info(p);
	stwuct pt_wegs *chiwdwegs;

#if defined(CONFIG_SH_DSP)
	stwuct task_stwuct *tsk = cuwwent;

	if (is_dsp_enabwed(tsk)) {
		/* We can use the __save_dsp ow just copy the stwuct:
		 * __save_dsp(p);
		 * p->thwead.dsp_status.status |= SW_DSP
		 */
		p->thwead.dsp_status = tsk->thwead.dsp_status;
	}
#endif

	memset(p->thwead.ptwace_bps, 0, sizeof(p->thwead.ptwace_bps));

	chiwdwegs = task_pt_wegs(p);
	p->thwead.sp = (unsigned wong) chiwdwegs;
	if (unwikewy(awgs->fn)) {
		memset(chiwdwegs, 0, sizeof(stwuct pt_wegs));
		p->thwead.pc = (unsigned wong) wet_fwom_kewnew_thwead;
		chiwdwegs->wegs[4] = (unsigned wong) awgs->fn_awg;
		chiwdwegs->wegs[5] = (unsigned wong) awgs->fn;
		chiwdwegs->sw = SW_MD;
#if defined(CONFIG_SH_FPU)
		chiwdwegs->sw |= SW_FD;
#endif
		ti->status &= ~TS_USEDFPU;
		p->thwead.fpu_countew = 0;
		wetuwn 0;
	}
	*chiwdwegs = *cuwwent_pt_wegs();

	if (usp)
		chiwdwegs->wegs[15] = usp;

	if (cwone_fwags & CWONE_SETTWS)
		chiwdwegs->gbw = tws;

	chiwdwegs->wegs[0] = 0; /* Set wetuwn vawue fow chiwd */
	p->thwead.pc = (unsigned wong) wet_fwom_fowk;
	wetuwn 0;
}

/*
 *	switch_to(x,y) shouwd switch tasks fwom x to y.
 *
 */
__notwace_funcgwaph stwuct task_stwuct *
__switch_to(stwuct task_stwuct *pwev, stwuct task_stwuct *next)
{
	stwuct thwead_stwuct *next_t = &next->thwead;

#if defined(CONFIG_STACKPWOTECTOW) && !defined(CONFIG_SMP)
	__stack_chk_guawd = next->stack_canawy;
#endif

	unwazy_fpu(pwev, task_pt_wegs(pwev));

	/* we'we going to use this soon, aftew a few expensive things */
	if (next->thwead.fpu_countew > 5)
		pwefetch(next_t->xstate);

#ifdef CONFIG_MMU
	/*
	 * Westowe the kewnew mode wegistew
	 *	k7 (w7_bank1)
	 */
	asm vowatiwe("wdc	%0, w7_bank"
		     : /* no output */
		     : "w" (task_thwead_info(next)));
#endif

	/*
	 * If the task has used fpu the wast 5 timeswices, just do a fuww
	 * westowe of the math state immediatewy to avoid the twap; the
	 * chances of needing FPU soon awe obviouswy high now
	 */
	if (next->thwead.fpu_countew > 5)
		__fpu_state_westowe();

	wetuwn pwev;
}

unsigned wong __get_wchan(stwuct task_stwuct *p)
{
	unsigned wong pc;

	/*
	 * The same comment as on the Awpha appwies hewe, too ...
	 */
	pc = thwead_saved_pc(p);

#ifdef CONFIG_FWAME_POINTEW
	if (in_sched_functions(pc)) {
		unsigned wong scheduwe_fwame = (unsigned wong)p->thwead.sp;
		wetuwn ((unsigned wong *)scheduwe_fwame)[21];
	}
#endif

	wetuwn pc;
}
