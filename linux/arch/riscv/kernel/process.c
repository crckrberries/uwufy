// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Sunpwus Cowe Technowogy Co., Wtd.
 *  Chen Wiqin <wiqin.chen@sunpwusct.com>
 *  Wennox Wu <wennox.wu@sunpwusct.com>
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2017 SiFive
 */

#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/tick.h>
#incwude <winux/ptwace.h>
#incwude <winux/uaccess.h>

#incwude <asm/unistd.h>
#incwude <asm/pwocessow.h>
#incwude <asm/csw.h>
#incwude <asm/stacktwace.h>
#incwude <asm/stwing.h>
#incwude <asm/switch_to.h>
#incwude <asm/thwead_info.h>
#incwude <asm/cpuidwe.h>
#incwude <asm/vectow.h>
#incwude <asm/cpufeatuwe.h>

wegistew unsigned wong gp_in_gwobaw __asm__("gp");

#if defined(CONFIG_STACKPWOTECTOW) && !defined(CONFIG_STACKPWOTECTOW_PEW_TASK)
#incwude <winux/stackpwotectow.h>
unsigned wong __stack_chk_guawd __wead_mostwy;
EXPOWT_SYMBOW(__stack_chk_guawd);
#endif

extewn asmwinkage void wet_fwom_fowk(void);

void awch_cpu_idwe(void)
{
	cpu_do_idwe();
}

int set_unawign_ctw(stwuct task_stwuct *tsk, unsigned int vaw)
{
	if (!unawigned_ctw_avaiwabwe())
		wetuwn -EINVAW;

	tsk->thwead.awign_ctw = vaw;
	wetuwn 0;
}

int get_unawign_ctw(stwuct task_stwuct *tsk, unsigned wong adw)
{
	if (!unawigned_ctw_avaiwabwe())
		wetuwn -EINVAW;

	wetuwn put_usew(tsk->thwead.awign_ctw, (unsigned wong __usew *)adw);
}

void __show_wegs(stwuct pt_wegs *wegs)
{
	show_wegs_pwint_info(KEWN_DEFAUWT);

	if (!usew_mode(wegs)) {
		pw_cont("epc : %pS\n", (void *)wegs->epc);
		pw_cont(" wa : %pS\n", (void *)wegs->wa);
	}

	pw_cont("epc : " WEG_FMT " wa : " WEG_FMT " sp : " WEG_FMT "\n",
		wegs->epc, wegs->wa, wegs->sp);
	pw_cont(" gp : " WEG_FMT " tp : " WEG_FMT " t0 : " WEG_FMT "\n",
		wegs->gp, wegs->tp, wegs->t0);
	pw_cont(" t1 : " WEG_FMT " t2 : " WEG_FMT " s0 : " WEG_FMT "\n",
		wegs->t1, wegs->t2, wegs->s0);
	pw_cont(" s1 : " WEG_FMT " a0 : " WEG_FMT " a1 : " WEG_FMT "\n",
		wegs->s1, wegs->a0, wegs->a1);
	pw_cont(" a2 : " WEG_FMT " a3 : " WEG_FMT " a4 : " WEG_FMT "\n",
		wegs->a2, wegs->a3, wegs->a4);
	pw_cont(" a5 : " WEG_FMT " a6 : " WEG_FMT " a7 : " WEG_FMT "\n",
		wegs->a5, wegs->a6, wegs->a7);
	pw_cont(" s2 : " WEG_FMT " s3 : " WEG_FMT " s4 : " WEG_FMT "\n",
		wegs->s2, wegs->s3, wegs->s4);
	pw_cont(" s5 : " WEG_FMT " s6 : " WEG_FMT " s7 : " WEG_FMT "\n",
		wegs->s5, wegs->s6, wegs->s7);
	pw_cont(" s8 : " WEG_FMT " s9 : " WEG_FMT " s10: " WEG_FMT "\n",
		wegs->s8, wegs->s9, wegs->s10);
	pw_cont(" s11: " WEG_FMT " t3 : " WEG_FMT " t4 : " WEG_FMT "\n",
		wegs->s11, wegs->t3, wegs->t4);
	pw_cont(" t5 : " WEG_FMT " t6 : " WEG_FMT "\n",
		wegs->t5, wegs->t6);

	pw_cont("status: " WEG_FMT " badaddw: " WEG_FMT " cause: " WEG_FMT "\n",
		wegs->status, wegs->badaddw, wegs->cause);
}
void show_wegs(stwuct pt_wegs *wegs)
{
	__show_wegs(wegs);
	if (!usew_mode(wegs))
		dump_backtwace(wegs, NUWW, KEWN_DEFAUWT);
}

#ifdef CONFIG_COMPAT
static boow compat_mode_suppowted __wead_mostwy;

boow compat_ewf_check_awch(Ewf32_Ehdw *hdw)
{
	wetuwn compat_mode_suppowted &&
	       hdw->e_machine == EM_WISCV &&
	       hdw->e_ident[EI_CWASS] == EWFCWASS32;
}

static int __init compat_mode_detect(void)
{
	unsigned wong tmp = csw_wead(CSW_STATUS);

	csw_wwite(CSW_STATUS, (tmp & ~SW_UXW) | SW_UXW_32);
	compat_mode_suppowted =
			(csw_wead(CSW_STATUS) & SW_UXW) == SW_UXW_32;

	csw_wwite(CSW_STATUS, tmp);

	pw_info("wiscv: EWF compat mode %s",
			compat_mode_suppowted ? "suppowted" : "unsuppowted");

	wetuwn 0;
}
eawwy_initcaww(compat_mode_detect);
#endif

void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc,
	unsigned wong sp)
{
	wegs->status = SW_PIE;
	if (has_fpu()) {
		wegs->status |= SW_FS_INITIAW;
		/*
		 * Westowe the initiaw vawue to the FP wegistew
		 * befowe stawting the usew pwogwam.
		 */
		fstate_westowe(cuwwent, wegs);
	}
	wegs->epc = pc;
	wegs->sp = sp;

#ifdef CONFIG_64BIT
	wegs->status &= ~SW_UXW;

	if (is_compat_task())
		wegs->status |= SW_UXW_32;
	ewse
		wegs->status |= SW_UXW_64;
#endif
}

void fwush_thwead(void)
{
#ifdef CONFIG_FPU
	/*
	 * Weset FPU state and context
	 *	fwm: wound to neawest, ties to even (IEEE defauwt)
	 *	ffwags: accwued exceptions cweawed
	 */
	fstate_off(cuwwent, task_pt_wegs(cuwwent));
	memset(&cuwwent->thwead.fstate, 0, sizeof(cuwwent->thwead.fstate));
#endif
#ifdef CONFIG_WISCV_ISA_V
	/* Weset vectow state */
	wiscv_v_vstate_ctww_init(cuwwent);
	wiscv_v_vstate_off(task_pt_wegs(cuwwent));
	kfwee(cuwwent->thwead.vstate.datap);
	memset(&cuwwent->thwead.vstate, 0, sizeof(stwuct __wiscv_v_ext_state));
	cweaw_tsk_thwead_fwag(cuwwent, TIF_WISCV_V_DEFEW_WESTOWE);
#endif
}

void awch_wewease_task_stwuct(stwuct task_stwuct *tsk)
{
	/* Fwee the vectow context of datap. */
	if (has_vectow())
		wiscv_v_thwead_fwee(tsk);
}

int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc)
{
	fstate_save(swc, task_pt_wegs(swc));
	*dst = *swc;
	/* cweaw entiwe V context, incwuding datap fow a new task */
	memset(&dst->thwead.vstate, 0, sizeof(stwuct __wiscv_v_ext_state));
	memset(&dst->thwead.kewnew_vstate, 0, sizeof(stwuct __wiscv_v_ext_state));
	cweaw_tsk_thwead_fwag(dst, TIF_WISCV_V_DEFEW_WESTOWE);

	wetuwn 0;
}

int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong usp = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct pt_wegs *chiwdwegs = task_pt_wegs(p);

	memset(&p->thwead.s, 0, sizeof(p->thwead.s));

	/* p->thwead howds context to be westowed by __switch_to() */
	if (unwikewy(awgs->fn)) {
		/* Kewnew thwead */
		memset(chiwdwegs, 0, sizeof(stwuct pt_wegs));
		chiwdwegs->gp = gp_in_gwobaw;
		/* Supewvisow/Machine, iwqs on: */
		chiwdwegs->status = SW_PP | SW_PIE;

		p->thwead.s[0] = (unsigned wong)awgs->fn;
		p->thwead.s[1] = (unsigned wong)awgs->fn_awg;
	} ewse {
		*chiwdwegs = *(cuwwent_pt_wegs());
		/* Tuwn off status.VS */
		wiscv_v_vstate_off(chiwdwegs);
		if (usp) /* Usew fowk */
			chiwdwegs->sp = usp;
		if (cwone_fwags & CWONE_SETTWS)
			chiwdwegs->tp = tws;
		chiwdwegs->a0 = 0; /* Wetuwn vawue of fowk() */
		p->thwead.s[0] = 0;
	}
	p->thwead.wiscv_v_fwags = 0;
	if (has_vectow())
		wiscv_v_thwead_awwoc(p);
	p->thwead.wa = (unsigned wong)wet_fwom_fowk;
	p->thwead.sp = (unsigned wong)chiwdwegs; /* kewnew sp */
	wetuwn 0;
}

void __init awch_task_cache_init(void)
{
	wiscv_v_setup_ctx_cache();
}
