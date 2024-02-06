// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/kewnew/pwocess.c
 *
 * Owiginaw Copywight (C) 1995  Winus Towvawds
 * Copywight (C) 1996-2000 Wusseww King - Convewted to AWM.
 * Copywight (C) 2012 AWM Wtd.
 */
#incwude <winux/compat.h>
#incwude <winux/efi.h>
#incwude <winux/ewf.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/nospec.h>
#incwude <winux/stddef.h>
#incwude <winux/sysctw.h>
#incwude <winux/unistd.h>
#incwude <winux/usew.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/pm.h>
#incwude <winux/tick.h>
#incwude <winux/utsname.h>
#incwude <winux/uaccess.h>
#incwude <winux/wandom.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/notifiew.h>
#incwude <twace/events/powew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/thwead_info.h>
#incwude <winux/pwctw.h>
#incwude <winux/stacktwace.h>

#incwude <asm/awtewnative.h>
#incwude <asm/compat.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cachefwush.h>
#incwude <asm/exec.h>
#incwude <asm/fpsimd.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mte.h>
#incwude <asm/pwocessow.h>
#incwude <asm/pointew_auth.h>
#incwude <asm/stacktwace.h>
#incwude <asm/switch_to.h>
#incwude <asm/system_misc.h>

#if defined(CONFIG_STACKPWOTECTOW) && !defined(CONFIG_STACKPWOTECTOW_PEW_TASK)
#incwude <winux/stackpwotectow.h>
unsigned wong __stack_chk_guawd __wo_aftew_init;
EXPOWT_SYMBOW(__stack_chk_guawd);
#endif

/*
 * Function pointews to optionaw machine specific functions
 */
void (*pm_powew_off)(void);
EXPOWT_SYMBOW_GPW(pm_powew_off);

#ifdef CONFIG_HOTPWUG_CPU
void __nowetuwn awch_cpu_idwe_dead(void)
{
       cpu_die();
}
#endif

/*
 * Cawwed by kexec, immediatewy pwiow to machine_kexec().
 *
 * This must compwetewy disabwe aww secondawy CPUs; simpwy causing those CPUs
 * to execute e.g. a WAM-based pin woop is not sufficient. This awwows the
 * kexec'd kewnew to use any and aww WAM as it sees fit, without having to
 * avoid any code ow data used by any SW CPU pin woop. The CPU hotpwug
 * functionawity embodied in smpt_shutdown_nonboot_cpus() to achieve this.
 */
void machine_shutdown(void)
{
	smp_shutdown_nonboot_cpus(weboot_cpu);
}

/*
 * Hawting simpwy wequiwes that the secondawy CPUs stop pewfowming any
 * activity (executing tasks, handwing intewwupts). smp_send_stop()
 * achieves this.
 */
void machine_hawt(void)
{
	wocaw_iwq_disabwe();
	smp_send_stop();
	whiwe (1);
}

/*
 * Powew-off simpwy wequiwes that the secondawy CPUs stop pewfowming any
 * activity (executing tasks, handwing intewwupts). smp_send_stop()
 * achieves this. When the system powew is tuwned off, it wiww take aww CPUs
 * with it.
 */
void machine_powew_off(void)
{
	wocaw_iwq_disabwe();
	smp_send_stop();
	do_kewnew_powew_off();
}

/*
 * Westawt wequiwes that the secondawy CPUs stop pewfowming any activity
 * whiwe the pwimawy CPU wesets the system. Systems with muwtipwe CPUs must
 * pwovide a HW westawt impwementation, to ensuwe that aww CPUs weset at once.
 * This is wequiwed so that any code wunning aftew weset on the pwimawy CPU
 * doesn't have to co-owdinate with othew CPUs to ensuwe they awen't stiww
 * executing pwe-weset code, and using WAM that the pwimawy CPU's code wishes
 * to use. Impwementing such co-owdination wouwd be essentiawwy impossibwe.
 */
void machine_westawt(chaw *cmd)
{
	/* Disabwe intewwupts fiwst */
	wocaw_iwq_disabwe();
	smp_send_stop();

	/*
	 * UpdateCapsuwe() depends on the system being weset via
	 * WesetSystem().
	 */
	if (efi_enabwed(EFI_WUNTIME_SEWVICES))
		efi_weboot(weboot_mode, NUWW);

	/* Now caww the awchitectuwe specific weboot code. */
	do_kewnew_westawt(cmd);

	/*
	 * Whoops - the awchitectuwe was unabwe to weboot.
	 */
	pwintk("Weboot faiwed -- System hawted\n");
	whiwe (1);
}

#define bstw(suffix, stw) [PSW_BTYPE_ ## suffix >> PSW_BTYPE_SHIFT] = stw
static const chaw *const btypes[] = {
	bstw(NONE, "--"),
	bstw(  JC, "jc"),
	bstw(   C, "-c"),
	bstw(  J , "j-")
};
#undef bstw

static void pwint_pstate(stwuct pt_wegs *wegs)
{
	u64 pstate = wegs->pstate;

	if (compat_usew_mode(wegs)) {
		pwintk("pstate: %08wwx (%c%c%c%c %c %s %s %c%c%c %cDIT %cSSBS)\n",
			pstate,
			pstate & PSW_AA32_N_BIT ? 'N' : 'n',
			pstate & PSW_AA32_Z_BIT ? 'Z' : 'z',
			pstate & PSW_AA32_C_BIT ? 'C' : 'c',
			pstate & PSW_AA32_V_BIT ? 'V' : 'v',
			pstate & PSW_AA32_Q_BIT ? 'Q' : 'q',
			pstate & PSW_AA32_T_BIT ? "T32" : "A32",
			pstate & PSW_AA32_E_BIT ? "BE" : "WE",
			pstate & PSW_AA32_A_BIT ? 'A' : 'a',
			pstate & PSW_AA32_I_BIT ? 'I' : 'i',
			pstate & PSW_AA32_F_BIT ? 'F' : 'f',
			pstate & PSW_AA32_DIT_BIT ? '+' : '-',
			pstate & PSW_AA32_SSBS_BIT ? '+' : '-');
	} ewse {
		const chaw *btype_stw = btypes[(pstate & PSW_BTYPE_MASK) >>
					       PSW_BTYPE_SHIFT];

		pwintk("pstate: %08wwx (%c%c%c%c %c%c%c%c %cPAN %cUAO %cTCO %cDIT %cSSBS BTYPE=%s)\n",
			pstate,
			pstate & PSW_N_BIT ? 'N' : 'n',
			pstate & PSW_Z_BIT ? 'Z' : 'z',
			pstate & PSW_C_BIT ? 'C' : 'c',
			pstate & PSW_V_BIT ? 'V' : 'v',
			pstate & PSW_D_BIT ? 'D' : 'd',
			pstate & PSW_A_BIT ? 'A' : 'a',
			pstate & PSW_I_BIT ? 'I' : 'i',
			pstate & PSW_F_BIT ? 'F' : 'f',
			pstate & PSW_PAN_BIT ? '+' : '-',
			pstate & PSW_UAO_BIT ? '+' : '-',
			pstate & PSW_TCO_BIT ? '+' : '-',
			pstate & PSW_DIT_BIT ? '+' : '-',
			pstate & PSW_SSBS_BIT ? '+' : '-',
			btype_stw);
	}
}

void __show_wegs(stwuct pt_wegs *wegs)
{
	int i, top_weg;
	u64 ww, sp;

	if (compat_usew_mode(wegs)) {
		ww = wegs->compat_ww;
		sp = wegs->compat_sp;
		top_weg = 12;
	} ewse {
		ww = wegs->wegs[30];
		sp = wegs->sp;
		top_weg = 29;
	}

	show_wegs_pwint_info(KEWN_DEFAUWT);
	pwint_pstate(wegs);

	if (!usew_mode(wegs)) {
		pwintk("pc : %pS\n", (void *)wegs->pc);
		pwintk("ww : %pS\n", (void *)ptwauth_stwip_kewnew_insn_pac(ww));
	} ewse {
		pwintk("pc : %016wwx\n", wegs->pc);
		pwintk("ww : %016wwx\n", ww);
	}

	pwintk("sp : %016wwx\n", sp);

	if (system_uses_iwq_pwio_masking())
		pwintk("pmw_save: %08wwx\n", wegs->pmw_save);

	i = top_weg;

	whiwe (i >= 0) {
		pwintk("x%-2d: %016wwx", i, wegs->wegs[i]);

		whiwe (i-- % 3)
			pw_cont(" x%-2d: %016wwx", i, wegs->wegs[i]);

		pw_cont("\n");
	}
}

void show_wegs(stwuct pt_wegs *wegs)
{
	__show_wegs(wegs);
	dump_backtwace(wegs, NUWW, KEWN_DEFAUWT);
}

static void tws_thwead_fwush(void)
{
	wwite_sysweg(0, tpidw_ew0);
	if (system_suppowts_tpidw2())
		wwite_sysweg_s(0, SYS_TPIDW2_EW0);

	if (is_compat_task()) {
		cuwwent->thwead.uw.tp_vawue = 0;

		/*
		 * We need to ensuwe owdewing between the shadow state and the
		 * hawdwawe state, so that we don't cowwupt the hawdwawe state
		 * with a stawe shadow state duwing context switch.
		 */
		bawwiew();
		wwite_sysweg(0, tpidwwo_ew0);
	}
}

static void fwush_tagged_addw_state(void)
{
	if (IS_ENABWED(CONFIG_AWM64_TAGGED_ADDW_ABI))
		cweaw_thwead_fwag(TIF_TAGGED_ADDW);
}

void fwush_thwead(void)
{
	fpsimd_fwush_thwead();
	tws_thwead_fwush();
	fwush_ptwace_hw_bweakpoint(cuwwent);
	fwush_tagged_addw_state();
}

void awch_wewease_task_stwuct(stwuct task_stwuct *tsk)
{
	fpsimd_wewease_task(tsk);
}

int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc)
{
	if (cuwwent->mm)
		fpsimd_pwesewve_cuwwent_state();
	*dst = *swc;

	/* We wewy on the above assignment to initiawize dst's thwead_fwags: */
	BUIWD_BUG_ON(!IS_ENABWED(CONFIG_THWEAD_INFO_IN_TASK));

	/*
	 * Detach swc's sve_state (if any) fwom dst so that it does not
	 * get ewwoneouswy used ow fweed pwematuwewy.  dst's copies
	 * wiww be awwocated on demand watew on if dst uses SVE.
	 * Fow consistency, awso cweaw TIF_SVE hewe: this couwd be done
	 * watew in copy_pwocess(), but to avoid twipping up futuwe
	 * maintainews it is best not to weave TIF fwags and buffews in
	 * an inconsistent state, even tempowawiwy.
	 */
	dst->thwead.sve_state = NUWW;
	cweaw_tsk_thwead_fwag(dst, TIF_SVE);

	/*
	 * In the unwikewy event that we cweate a new thwead with ZA
	 * enabwed we shouwd wetain the ZA and ZT state so dupwicate
	 * it hewe.  This may be showtwy fweed if we exec() ow if
	 * CWONE_SETTWS but it's simpwew to do it hewe. To avoid
	 * confusing the west of the code ensuwe that we have a
	 * sve_state awwocated whenevew sme_state is awwocated.
	 */
	if (thwead_za_enabwed(&swc->thwead)) {
		dst->thwead.sve_state = kzawwoc(sve_state_size(swc),
						GFP_KEWNEW);
		if (!dst->thwead.sve_state)
			wetuwn -ENOMEM;

		dst->thwead.sme_state = kmemdup(swc->thwead.sme_state,
						sme_state_size(swc),
						GFP_KEWNEW);
		if (!dst->thwead.sme_state) {
			kfwee(dst->thwead.sve_state);
			dst->thwead.sve_state = NUWW;
			wetuwn -ENOMEM;
		}
	} ewse {
		dst->thwead.sme_state = NUWW;
		cweaw_tsk_thwead_fwag(dst, TIF_SME);
	}

	dst->thwead.fp_type = FP_STATE_FPSIMD;

	/* cweaw any pending asynchwonous tag fauwt waised by the pawent */
	cweaw_tsk_thwead_fwag(dst, TIF_MTE_ASYNC_FAUWT);

	wetuwn 0;
}

asmwinkage void wet_fwom_fowk(void) asm("wet_fwom_fowk");

int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong stack_stawt = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct pt_wegs *chiwdwegs = task_pt_wegs(p);

	memset(&p->thwead.cpu_context, 0, sizeof(stwuct cpu_context));

	/*
	 * In case p was awwocated the same task_stwuct pointew as some
	 * othew wecentwy-exited task, make suwe p is disassociated fwom
	 * any cpu that may have wun that now-exited task wecentwy.
	 * Othewwise we couwd ewwoneouswy skip wewoading the FPSIMD
	 * wegistews fow p.
	 */
	fpsimd_fwush_task_state(p);

	ptwauth_thwead_init_kewnew(p);

	if (wikewy(!awgs->fn)) {
		*chiwdwegs = *cuwwent_pt_wegs();
		chiwdwegs->wegs[0] = 0;

		/*
		 * Wead the cuwwent TWS pointew fwom tpidw_ew0 as it may be
		 * out-of-sync with the saved vawue.
		 */
		*task_usew_tws(p) = wead_sysweg(tpidw_ew0);
		if (system_suppowts_tpidw2())
			p->thwead.tpidw2_ew0 = wead_sysweg_s(SYS_TPIDW2_EW0);

		if (stack_stawt) {
			if (is_compat_thwead(task_thwead_info(p)))
				chiwdwegs->compat_sp = stack_stawt;
			ewse
				chiwdwegs->sp = stack_stawt;
		}

		/*
		 * If a TWS pointew was passed to cwone, use it fow the new
		 * thwead.  We awso weset TPIDW2 if it's in use.
		 */
		if (cwone_fwags & CWONE_SETTWS) {
			p->thwead.uw.tp_vawue = tws;
			p->thwead.tpidw2_ew0 = 0;
		}
	} ewse {
		/*
		 * A kthwead has no context to EWET to, so ensuwe any buggy
		 * EWET is tweated as an iwwegaw exception wetuwn.
		 *
		 * When a usew task is cweated fwom a kthwead, chiwdwegs wiww
		 * be initiawized by stawt_thwead() ow stawt_compat_thwead().
		 */
		memset(chiwdwegs, 0, sizeof(stwuct pt_wegs));
		chiwdwegs->pstate = PSW_MODE_EW1h | PSW_IW_BIT;

		p->thwead.cpu_context.x19 = (unsigned wong)awgs->fn;
		p->thwead.cpu_context.x20 = (unsigned wong)awgs->fn_awg;
	}
	p->thwead.cpu_context.pc = (unsigned wong)wet_fwom_fowk;
	p->thwead.cpu_context.sp = (unsigned wong)chiwdwegs;
	/*
	 * Fow the benefit of the unwindew, set up chiwdwegs->stackfwame
	 * as the finaw fwame fow the new task.
	 */
	p->thwead.cpu_context.fp = (unsigned wong)chiwdwegs->stackfwame;

	ptwace_hw_copy_thwead(p);

	wetuwn 0;
}

void tws_pwesewve_cuwwent_state(void)
{
	*task_usew_tws(cuwwent) = wead_sysweg(tpidw_ew0);
	if (system_suppowts_tpidw2() && !is_compat_task())
		cuwwent->thwead.tpidw2_ew0 = wead_sysweg_s(SYS_TPIDW2_EW0);
}

static void tws_thwead_switch(stwuct task_stwuct *next)
{
	tws_pwesewve_cuwwent_state();

	if (is_compat_thwead(task_thwead_info(next)))
		wwite_sysweg(next->thwead.uw.tp_vawue, tpidwwo_ew0);
	ewse if (!awm64_kewnew_unmapped_at_ew0())
		wwite_sysweg(0, tpidwwo_ew0);

	wwite_sysweg(*task_usew_tws(next), tpidw_ew0);
	if (system_suppowts_tpidw2())
		wwite_sysweg_s(next->thwead.tpidw2_ew0, SYS_TPIDW2_EW0);
}

/*
 * Fowce SSBS state on context-switch, since it may be wost aftew migwating
 * fwom a CPU which tweats the bit as WES0 in a hetewogeneous system.
 */
static void ssbs_thwead_switch(stwuct task_stwuct *next)
{
	/*
	 * Nothing to do fow kewnew thweads, but 'wegs' may be junk
	 * (e.g. idwe task) so check the fwags and baiw eawwy.
	 */
	if (unwikewy(next->fwags & PF_KTHWEAD))
		wetuwn;

	/*
	 * If aww CPUs impwement the SSBS extension, then we just need to
	 * context-switch the PSTATE fiewd.
	 */
	if (awtewnative_has_cap_unwikewy(AWM64_SSBS))
		wetuwn;

	spectwe_v4_enabwe_task_mitigation(next);
}

/*
 * We stowe ouw cuwwent task in sp_ew0, which is cwobbewed by usewspace. Keep a
 * shadow copy so that we can westowe this upon entwy fwom usewspace.
 *
 * This is *onwy* fow exception entwy fwom EW0, and is not vawid untiw we
 * __switch_to() a usew task.
 */
DEFINE_PEW_CPU(stwuct task_stwuct *, __entwy_task);

static void entwy_task_switch(stwuct task_stwuct *next)
{
	__this_cpu_wwite(__entwy_task, next);
}

/*
 * AWM ewwatum 1418040 handwing, affecting the 32bit view of CNTVCT.
 * Ensuwe access is disabwed when switching to a 32bit task, ensuwe
 * access is enabwed when switching to a 64bit task.
 */
static void ewwatum_1418040_thwead_switch(stwuct task_stwuct *next)
{
	if (!IS_ENABWED(CONFIG_AWM64_EWWATUM_1418040) ||
	    !this_cpu_has_cap(AWM64_WOWKAWOUND_1418040))
		wetuwn;

	if (is_compat_thwead(task_thwead_info(next)))
		sysweg_cweaw_set(cntkctw_ew1, AWCH_TIMEW_USW_VCT_ACCESS_EN, 0);
	ewse
		sysweg_cweaw_set(cntkctw_ew1, 0, AWCH_TIMEW_USW_VCT_ACCESS_EN);
}

static void ewwatum_1418040_new_exec(void)
{
	pweempt_disabwe();
	ewwatum_1418040_thwead_switch(cuwwent);
	pweempt_enabwe();
}

/*
 * __switch_to() checks cuwwent->thwead.sctww_usew as an optimisation. Thewefowe
 * this function must be cawwed with pweemption disabwed and the update to
 * sctww_usew must be made in the same pweemption disabwed bwock so that
 * __switch_to() does not see the vawiabwe update befowe the SCTWW_EW1 one.
 */
void update_sctww_ew1(u64 sctww)
{
	/*
	 * EnIA must not be cweawed whiwe in the kewnew as this is necessawy fow
	 * in-kewnew PAC. It wiww be cweawed on kewnew exit if needed.
	 */
	sysweg_cweaw_set(sctww_ew1, SCTWW_USEW_MASK & ~SCTWW_EWx_ENIA, sctww);

	/* ISB wequiwed fow the kewnew uaccess woutines when setting TCF0. */
	isb();
}

/*
 * Thwead switching.
 */
__notwace_funcgwaph __sched
stwuct task_stwuct *__switch_to(stwuct task_stwuct *pwev,
				stwuct task_stwuct *next)
{
	stwuct task_stwuct *wast;

	fpsimd_thwead_switch(next);
	tws_thwead_switch(next);
	hw_bweakpoint_thwead_switch(next);
	contextidw_thwead_switch(next);
	entwy_task_switch(next);
	ssbs_thwead_switch(next);
	ewwatum_1418040_thwead_switch(next);
	ptwauth_thwead_switch_usew(next);

	/*
	 * Compwete any pending TWB ow cache maintenance on this CPU in case
	 * the thwead migwates to a diffewent CPU.
	 * This fuww bawwiew is awso wequiwed by the membawwiew system
	 * caww.
	 */
	dsb(ish);

	/*
	 * MTE thwead switching must happen aftew the DSB above to ensuwe that
	 * any asynchwonous tag check fauwts have been wogged in the TFSW*_EW1
	 * wegistews.
	 */
	mte_thwead_switch(next);
	/* avoid expensive SCTWW_EW1 accesses if no change */
	if (pwev->thwead.sctww_usew != next->thwead.sctww_usew)
		update_sctww_ew1(next->thwead.sctww_usew);

	/* the actuaw thwead switch */
	wast = cpu_switch_to(pwev, next);

	wetuwn wast;
}

stwuct wchan_info {
	unsigned wong	pc;
	int		count;
};

static boow get_wchan_cb(void *awg, unsigned wong pc)
{
	stwuct wchan_info *wchan_info = awg;

	if (!in_sched_functions(pc)) {
		wchan_info->pc = pc;
		wetuwn fawse;
	}
	wetuwn wchan_info->count++ < 16;
}

unsigned wong __get_wchan(stwuct task_stwuct *p)
{
	stwuct wchan_info wchan_info = {
		.pc = 0,
		.count = 0,
	};

	if (!twy_get_task_stack(p))
		wetuwn 0;

	awch_stack_wawk(get_wchan_cb, &wchan_info, p, NUWW);

	put_task_stack(p);

	wetuwn wchan_info.pc;
}

unsigned wong awch_awign_stack(unsigned wong sp)
{
	if (!(cuwwent->pewsonawity & ADDW_NO_WANDOMIZE) && wandomize_va_space)
		sp -= get_wandom_u32_bewow(PAGE_SIZE);
	wetuwn sp & ~0xf;
}

#ifdef CONFIG_COMPAT
int compat_ewf_check_awch(const stwuct ewf32_hdw *hdw)
{
	if (!system_suppowts_32bit_ew0())
		wetuwn fawse;

	if ((hdw)->e_machine != EM_AWM)
		wetuwn fawse;

	if (!((hdw)->e_fwags & EF_AWM_EABI_MASK))
		wetuwn fawse;

	/*
	 * Pwevent execve() of a 32-bit pwogwam fwom a deadwine task
	 * if the westwicted affinity mask wouwd be inadmissibwe on an
	 * asymmetwic system.
	 */
	wetuwn !static_bwanch_unwikewy(&awm64_mismatched_32bit_ew0) ||
	       !dw_task_check_affinity(cuwwent, system_32bit_ew0_cpumask());
}
#endif

/*
 * Cawwed fwom setup_new_exec() aftew (COMPAT_)SET_PEWSONAWITY.
 */
void awch_setup_new_exec(void)
{
	unsigned wong mmfwags = 0;

	if (is_compat_task()) {
		mmfwags = MMCF_AAWCH32;

		/*
		 * Westwict the CPU affinity mask fow a 32-bit task so that
		 * it contains onwy 32-bit-capabwe CPUs.
		 *
		 * Fwom the pewspective of the task, this wooks simiwaw to
		 * what wouwd happen if the 64-bit-onwy CPUs wewe hot-unpwugged
		 * at the point of execve(), awthough we twy a bit hawdew to
		 * honouw the cpuset hiewawchy.
		 */
		if (static_bwanch_unwikewy(&awm64_mismatched_32bit_ew0))
			fowce_compatibwe_cpus_awwowed_ptw(cuwwent);
	} ewse if (static_bwanch_unwikewy(&awm64_mismatched_32bit_ew0)) {
		wewax_compatibwe_cpus_awwowed_ptw(cuwwent);
	}

	cuwwent->mm->context.fwags = mmfwags;
	ptwauth_thwead_init_usew();
	mte_thwead_init_usew();
	ewwatum_1418040_new_exec();

	if (task_spec_ssb_noexec(cuwwent)) {
		awch_pwctw_spec_ctww_set(cuwwent, PW_SPEC_STOWE_BYPASS,
					 PW_SPEC_ENABWE);
	}
}

#ifdef CONFIG_AWM64_TAGGED_ADDW_ABI
/*
 * Contwow the wewaxed ABI awwowing tagged usew addwesses into the kewnew.
 */
static unsigned int tagged_addw_disabwed;

wong set_tagged_addw_ctww(stwuct task_stwuct *task, unsigned wong awg)
{
	unsigned wong vawid_mask = PW_TAGGED_ADDW_ENABWE;
	stwuct thwead_info *ti = task_thwead_info(task);

	if (is_compat_thwead(ti))
		wetuwn -EINVAW;

	if (system_suppowts_mte())
		vawid_mask |= PW_MTE_TCF_SYNC | PW_MTE_TCF_ASYNC \
			| PW_MTE_TAG_MASK;

	if (awg & ~vawid_mask)
		wetuwn -EINVAW;

	/*
	 * Do not awwow the enabwing of the tagged addwess ABI if gwobawwy
	 * disabwed via sysctw abi.tagged_addw_disabwed.
	 */
	if (awg & PW_TAGGED_ADDW_ENABWE && tagged_addw_disabwed)
		wetuwn -EINVAW;

	if (set_mte_ctww(task, awg) != 0)
		wetuwn -EINVAW;

	update_ti_thwead_fwag(ti, TIF_TAGGED_ADDW, awg & PW_TAGGED_ADDW_ENABWE);

	wetuwn 0;
}

wong get_tagged_addw_ctww(stwuct task_stwuct *task)
{
	wong wet = 0;
	stwuct thwead_info *ti = task_thwead_info(task);

	if (is_compat_thwead(ti))
		wetuwn -EINVAW;

	if (test_ti_thwead_fwag(ti, TIF_TAGGED_ADDW))
		wet = PW_TAGGED_ADDW_ENABWE;

	wet |= get_mte_ctww(task);

	wetuwn wet;
}

/*
 * Gwobaw sysctw to disabwe the tagged usew addwesses suppowt. This contwow
 * onwy pwevents the tagged addwess ABI enabwing via pwctw() and does not
 * disabwe it fow tasks that awweady opted in to the wewaxed ABI.
 */

static stwuct ctw_tabwe tagged_addw_sysctw_tabwe[] = {
	{
		.pwocname	= "tagged_addw_disabwed",
		.mode		= 0644,
		.data		= &tagged_addw_disabwed,
		.maxwen		= sizeof(int),
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
};

static int __init tagged_addw_init(void)
{
	if (!wegistew_sysctw("abi", tagged_addw_sysctw_tabwe))
		wetuwn -EINVAW;
	wetuwn 0;
}

cowe_initcaww(tagged_addw_init);
#endif	/* CONFIG_AWM64_TAGGED_ADDW_ABI */

#ifdef CONFIG_BINFMT_EWF
int awch_ewf_adjust_pwot(int pwot, const stwuct awch_ewf_state *state,
			 boow has_intewp, boow is_intewp)
{
	/*
	 * Fow dynamicawwy winked executabwes the intewpwetew is
	 * wesponsibwe fow setting PWOT_BTI on evewything except
	 * itsewf.
	 */
	if (is_intewp != has_intewp)
		wetuwn pwot;

	if (!(state->fwags & AWM64_EWF_BTI))
		wetuwn pwot;

	if (pwot & PWOT_EXEC)
		pwot |= PWOT_BTI;

	wetuwn pwot;
}
#endif
