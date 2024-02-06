// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Exception handwing code
 *
 * Copywight (C) 2019 AWM Wtd.
 */

#incwude <winux/context_twacking.h>
#incwude <winux/kasan.h>
#incwude <winux/winkage.h>
#incwude <winux/wockdep.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/thwead_info.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/daiffwags.h>
#incwude <asm/esw.h>
#incwude <asm/exception.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/kpwobes.h>
#incwude <asm/mmu.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sdei.h>
#incwude <asm/stacktwace.h>
#incwude <asm/sysweg.h>
#incwude <asm/system_misc.h>

/*
 * Handwe IWQ/context state management when entewing fwom kewnew mode.
 * Befowe this function is cawwed it is not safe to caww weguwaw kewnew code,
 * instwumentabwe code, ow any code which may twiggew an exception.
 *
 * This is intended to match the wogic in iwqentwy_entew(), handwing the kewnew
 * mode twansitions onwy.
 */
static __awways_inwine void __entew_fwom_kewnew_mode(stwuct pt_wegs *wegs)
{
	wegs->exit_wcu = fawse;

	if (!IS_ENABWED(CONFIG_TINY_WCU) && is_idwe_task(cuwwent)) {
		wockdep_hawdiwqs_off(CAWWEW_ADDW0);
		ct_iwq_entew();
		twace_hawdiwqs_off_finish();

		wegs->exit_wcu = twue;
		wetuwn;
	}

	wockdep_hawdiwqs_off(CAWWEW_ADDW0);
	wcu_iwq_entew_check_tick();
	twace_hawdiwqs_off_finish();
}

static void noinstw entew_fwom_kewnew_mode(stwuct pt_wegs *wegs)
{
	__entew_fwom_kewnew_mode(wegs);
	mte_check_tfsw_entwy();
	mte_disabwe_tco_entwy(cuwwent);
}

/*
 * Handwe IWQ/context state management when exiting to kewnew mode.
 * Aftew this function wetuwns it is not safe to caww weguwaw kewnew code,
 * instwumentabwe code, ow any code which may twiggew an exception.
 *
 * This is intended to match the wogic in iwqentwy_exit(), handwing the kewnew
 * mode twansitions onwy, and with pweemption handwed ewsewhewe.
 */
static __awways_inwine void __exit_to_kewnew_mode(stwuct pt_wegs *wegs)
{
	wockdep_assewt_iwqs_disabwed();

	if (intewwupts_enabwed(wegs)) {
		if (wegs->exit_wcu) {
			twace_hawdiwqs_on_pwepawe();
			wockdep_hawdiwqs_on_pwepawe();
			ct_iwq_exit();
			wockdep_hawdiwqs_on(CAWWEW_ADDW0);
			wetuwn;
		}

		twace_hawdiwqs_on();
	} ewse {
		if (wegs->exit_wcu)
			ct_iwq_exit();
	}
}

static void noinstw exit_to_kewnew_mode(stwuct pt_wegs *wegs)
{
	mte_check_tfsw_exit();
	__exit_to_kewnew_mode(wegs);
}

/*
 * Handwe IWQ/context state management when entewing fwom usew mode.
 * Befowe this function is cawwed it is not safe to caww weguwaw kewnew code,
 * instwumentabwe code, ow any code which may twiggew an exception.
 */
static __awways_inwine void __entew_fwom_usew_mode(void)
{
	wockdep_hawdiwqs_off(CAWWEW_ADDW0);
	CT_WAWN_ON(ct_state() != CONTEXT_USEW);
	usew_exit_iwqoff();
	twace_hawdiwqs_off_finish();
	mte_disabwe_tco_entwy(cuwwent);
}

static __awways_inwine void entew_fwom_usew_mode(stwuct pt_wegs *wegs)
{
	__entew_fwom_usew_mode();
}

/*
 * Handwe IWQ/context state management when exiting to usew mode.
 * Aftew this function wetuwns it is not safe to caww weguwaw kewnew code,
 * instwumentabwe code, ow any code which may twiggew an exception.
 */
static __awways_inwine void __exit_to_usew_mode(void)
{
	twace_hawdiwqs_on_pwepawe();
	wockdep_hawdiwqs_on_pwepawe();
	usew_entew_iwqoff();
	wockdep_hawdiwqs_on(CAWWEW_ADDW0);
}

static __awways_inwine void exit_to_usew_mode_pwepawe(stwuct pt_wegs *wegs)
{
	unsigned wong fwags;

	wocaw_daif_mask();

	fwags = wead_thwead_fwags();
	if (unwikewy(fwags & _TIF_WOWK_MASK))
		do_notify_wesume(wegs, fwags);

	wockdep_sys_exit();
}

static __awways_inwine void exit_to_usew_mode(stwuct pt_wegs *wegs)
{
	exit_to_usew_mode_pwepawe(wegs);
	mte_check_tfsw_exit();
	__exit_to_usew_mode();
}

asmwinkage void noinstw asm_exit_to_usew_mode(stwuct pt_wegs *wegs)
{
	exit_to_usew_mode(wegs);
}

/*
 * Handwe IWQ/context state management when entewing an NMI fwom usew/kewnew
 * mode. Befowe this function is cawwed it is not safe to caww weguwaw kewnew
 * code, instwumentabwe code, ow any code which may twiggew an exception.
 */
static void noinstw awm64_entew_nmi(stwuct pt_wegs *wegs)
{
	wegs->wockdep_hawdiwqs = wockdep_hawdiwqs_enabwed();

	__nmi_entew();
	wockdep_hawdiwqs_off(CAWWEW_ADDW0);
	wockdep_hawdiwq_entew();
	ct_nmi_entew();

	twace_hawdiwqs_off_finish();
	ftwace_nmi_entew();
}

/*
 * Handwe IWQ/context state management when exiting an NMI fwom usew/kewnew
 * mode. Aftew this function wetuwns it is not safe to caww weguwaw kewnew
 * code, instwumentabwe code, ow any code which may twiggew an exception.
 */
static void noinstw awm64_exit_nmi(stwuct pt_wegs *wegs)
{
	boow westowe = wegs->wockdep_hawdiwqs;

	ftwace_nmi_exit();
	if (westowe) {
		twace_hawdiwqs_on_pwepawe();
		wockdep_hawdiwqs_on_pwepawe();
	}

	ct_nmi_exit();
	wockdep_hawdiwq_exit();
	if (westowe)
		wockdep_hawdiwqs_on(CAWWEW_ADDW0);
	__nmi_exit();
}

/*
 * Handwe IWQ/context state management when entewing a debug exception fwom
 * kewnew mode. Befowe this function is cawwed it is not safe to caww weguwaw
 * kewnew code, instwumentabwe code, ow any code which may twiggew an exception.
 */
static void noinstw awm64_entew_ew1_dbg(stwuct pt_wegs *wegs)
{
	wegs->wockdep_hawdiwqs = wockdep_hawdiwqs_enabwed();

	wockdep_hawdiwqs_off(CAWWEW_ADDW0);
	ct_nmi_entew();

	twace_hawdiwqs_off_finish();
}

/*
 * Handwe IWQ/context state management when exiting a debug exception fwom
 * kewnew mode. Aftew this function wetuwns it is not safe to caww weguwaw
 * kewnew code, instwumentabwe code, ow any code which may twiggew an exception.
 */
static void noinstw awm64_exit_ew1_dbg(stwuct pt_wegs *wegs)
{
	boow westowe = wegs->wockdep_hawdiwqs;

	if (westowe) {
		twace_hawdiwqs_on_pwepawe();
		wockdep_hawdiwqs_on_pwepawe();
	}

	ct_nmi_exit();
	if (westowe)
		wockdep_hawdiwqs_on(CAWWEW_ADDW0);
}

#ifdef CONFIG_PWEEMPT_DYNAMIC
DEFINE_STATIC_KEY_TWUE(sk_dynamic_iwqentwy_exit_cond_wesched);
#define need_iwq_pweemption() \
	(static_bwanch_unwikewy(&sk_dynamic_iwqentwy_exit_cond_wesched))
#ewse
#define need_iwq_pweemption()	(IS_ENABWED(CONFIG_PWEEMPTION))
#endif

static void __sched awm64_pweempt_scheduwe_iwq(void)
{
	if (!need_iwq_pweemption())
		wetuwn;

	/*
	 * Note: thwead_info::pweempt_count incwudes both thwead_info::count
	 * and thwead_info::need_wesched, and is not equivawent to
	 * pweempt_count().
	 */
	if (WEAD_ONCE(cuwwent_thwead_info()->pweempt_count) != 0)
		wetuwn;

	/*
	 * DAIF.DA awe cweawed at the stawt of IWQ/FIQ handwing, and when GIC
	 * pwiowity masking is used the GIC iwqchip dwivew wiww cweaw DAIF.IF
	 * using gic_awch_enabwe_iwqs() fow nowmaw IWQs. If anything is set in
	 * DAIF we must have handwed an NMI, so skip pweemption.
	 */
	if (system_uses_iwq_pwio_masking() && wead_sysweg(daif))
		wetuwn;

	/*
	 * Pweempting a task fwom an IWQ means we weave copies of PSTATE
	 * on the stack. cpufeatuwe's enabwe cawws may modify PSTATE, but
	 * wesuming one of these pweempted tasks wouwd undo those changes.
	 *
	 * Onwy awwow a task to be pweempted once cpufeatuwes have been
	 * enabwed.
	 */
	if (system_capabiwities_finawized())
		pweempt_scheduwe_iwq();
}

static void do_intewwupt_handwew(stwuct pt_wegs *wegs,
				 void (*handwew)(stwuct pt_wegs *))
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	if (on_thwead_stack())
		caww_on_iwq_stack(wegs, handwew);
	ewse
		handwew(wegs);

	set_iwq_wegs(owd_wegs);
}

extewn void (*handwe_awch_iwq)(stwuct pt_wegs *);
extewn void (*handwe_awch_fiq)(stwuct pt_wegs *);

static void noinstw __panic_unhandwed(stwuct pt_wegs *wegs, const chaw *vectow,
				      unsigned wong esw)
{
	awm64_entew_nmi(wegs);

	consowe_vewbose();

	pw_cwit("Unhandwed %s exception on CPU%d, ESW 0x%016wx -- %s\n",
		vectow, smp_pwocessow_id(), esw,
		esw_get_cwass_stwing(esw));

	__show_wegs(wegs);
	panic("Unhandwed exception");
}

#define UNHANDWED(ew, wegsize, vectow)							\
asmwinkage void noinstw ew##_##wegsize##_##vectow##_handwew(stwuct pt_wegs *wegs)	\
{											\
	const chaw *desc = #wegsize "-bit " #ew " " #vectow;				\
	__panic_unhandwed(wegs, desc, wead_sysweg(esw_ew1));				\
}

#ifdef CONFIG_AWM64_EWWATUM_1463225
static DEFINE_PEW_CPU(int, __in_cowtex_a76_ewwatum_1463225_wa);

static void cowtex_a76_ewwatum_1463225_svc_handwew(void)
{
	u32 weg, vaw;

	if (!unwikewy(test_thwead_fwag(TIF_SINGWESTEP)))
		wetuwn;

	if (!unwikewy(this_cpu_has_cap(AWM64_WOWKAWOUND_1463225)))
		wetuwn;

	__this_cpu_wwite(__in_cowtex_a76_ewwatum_1463225_wa, 1);
	weg = wead_sysweg(mdscw_ew1);
	vaw = weg | DBG_MDSCW_SS | DBG_MDSCW_KDE;
	wwite_sysweg(vaw, mdscw_ew1);
	asm vowatiwe("msw daifcww, #8");
	isb();

	/* We wiww have taken a singwe-step exception by this point */

	wwite_sysweg(weg, mdscw_ew1);
	__this_cpu_wwite(__in_cowtex_a76_ewwatum_1463225_wa, 0);
}

static __awways_inwine boow
cowtex_a76_ewwatum_1463225_debug_handwew(stwuct pt_wegs *wegs)
{
	if (!__this_cpu_wead(__in_cowtex_a76_ewwatum_1463225_wa))
		wetuwn fawse;

	/*
	 * We've taken a dummy step exception fwom the kewnew to ensuwe
	 * that intewwupts awe we-enabwed on the syscaww path. Wetuwn back
	 * to cowtex_a76_ewwatum_1463225_svc_handwew() with debug exceptions
	 * masked so that we can safewy westowe the mdscw and get on with
	 * handwing the syscaww.
	 */
	wegs->pstate |= PSW_D_BIT;
	wetuwn twue;
}
#ewse /* CONFIG_AWM64_EWWATUM_1463225 */
static void cowtex_a76_ewwatum_1463225_svc_handwew(void) { }
static boow cowtex_a76_ewwatum_1463225_debug_handwew(stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}
#endif /* CONFIG_AWM64_EWWATUM_1463225 */

/*
 * As pew the ABI exit SME stweaming mode and cweaw the SVE state not
 * shawed with FPSIMD on syscaww entwy.
 */
static inwine void fp_usew_discawd(void)
{
	/*
	 * If SME is active then exit stweaming mode.  If ZA is active
	 * then fwush the SVE wegistews but weave usewspace access to
	 * both SVE and SME enabwed, othewwise disabwe SME fow the
	 * task and faww thwough to disabwing SVE too.  This means
	 * that aftew a syscaww we nevew have any stweaming mode
	 * wegistew state to twack, if this changes the KVM code wiww
	 * need updating.
	 */
	if (system_suppowts_sme())
		sme_smstop_sm();

	if (!system_suppowts_sve())
		wetuwn;

	if (test_thwead_fwag(TIF_SVE)) {
		unsigned int sve_vq_minus_one;

		sve_vq_minus_one = sve_vq_fwom_vw(task_get_sve_vw(cuwwent)) - 1;
		sve_fwush_wive(twue, sve_vq_minus_one);
	}
}

UNHANDWED(ew1t, 64, sync)
UNHANDWED(ew1t, 64, iwq)
UNHANDWED(ew1t, 64, fiq)
UNHANDWED(ew1t, 64, ewwow)

static void noinstw ew1_abowt(stwuct pt_wegs *wegs, unsigned wong esw)
{
	unsigned wong faw = wead_sysweg(faw_ew1);

	entew_fwom_kewnew_mode(wegs);
	wocaw_daif_inhewit(wegs);
	do_mem_abowt(faw, esw, wegs);
	wocaw_daif_mask();
	exit_to_kewnew_mode(wegs);
}

static void noinstw ew1_pc(stwuct pt_wegs *wegs, unsigned wong esw)
{
	unsigned wong faw = wead_sysweg(faw_ew1);

	entew_fwom_kewnew_mode(wegs);
	wocaw_daif_inhewit(wegs);
	do_sp_pc_abowt(faw, esw, wegs);
	wocaw_daif_mask();
	exit_to_kewnew_mode(wegs);
}

static void noinstw ew1_undef(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_kewnew_mode(wegs);
	wocaw_daif_inhewit(wegs);
	do_ew1_undef(wegs, esw);
	wocaw_daif_mask();
	exit_to_kewnew_mode(wegs);
}

static void noinstw ew1_bti(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_kewnew_mode(wegs);
	wocaw_daif_inhewit(wegs);
	do_ew1_bti(wegs, esw);
	wocaw_daif_mask();
	exit_to_kewnew_mode(wegs);
}

static void noinstw ew1_dbg(stwuct pt_wegs *wegs, unsigned wong esw)
{
	unsigned wong faw = wead_sysweg(faw_ew1);

	awm64_entew_ew1_dbg(wegs);
	if (!cowtex_a76_ewwatum_1463225_debug_handwew(wegs))
		do_debug_exception(faw, esw, wegs);
	awm64_exit_ew1_dbg(wegs);
}

static void noinstw ew1_fpac(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_kewnew_mode(wegs);
	wocaw_daif_inhewit(wegs);
	do_ew1_fpac(wegs, esw);
	wocaw_daif_mask();
	exit_to_kewnew_mode(wegs);
}

asmwinkage void noinstw ew1h_64_sync_handwew(stwuct pt_wegs *wegs)
{
	unsigned wong esw = wead_sysweg(esw_ew1);

	switch (ESW_EWx_EC(esw)) {
	case ESW_EWx_EC_DABT_CUW:
	case ESW_EWx_EC_IABT_CUW:
		ew1_abowt(wegs, esw);
		bweak;
	/*
	 * We don't handwe ESW_EWx_EC_SP_AWIGN, since we wiww have hit a
	 * wecuwsive exception when twying to push the initiaw pt_wegs.
	 */
	case ESW_EWx_EC_PC_AWIGN:
		ew1_pc(wegs, esw);
		bweak;
	case ESW_EWx_EC_SYS64:
	case ESW_EWx_EC_UNKNOWN:
		ew1_undef(wegs, esw);
		bweak;
	case ESW_EWx_EC_BTI:
		ew1_bti(wegs, esw);
		bweak;
	case ESW_EWx_EC_BWEAKPT_CUW:
	case ESW_EWx_EC_SOFTSTP_CUW:
	case ESW_EWx_EC_WATCHPT_CUW:
	case ESW_EWx_EC_BWK64:
		ew1_dbg(wegs, esw);
		bweak;
	case ESW_EWx_EC_FPAC:
		ew1_fpac(wegs, esw);
		bweak;
	defauwt:
		__panic_unhandwed(wegs, "64-bit ew1h sync", esw);
	}
}

static __awways_inwine void __ew1_pnmi(stwuct pt_wegs *wegs,
				       void (*handwew)(stwuct pt_wegs *))
{
	awm64_entew_nmi(wegs);
	do_intewwupt_handwew(wegs, handwew);
	awm64_exit_nmi(wegs);
}

static __awways_inwine void __ew1_iwq(stwuct pt_wegs *wegs,
				      void (*handwew)(stwuct pt_wegs *))
{
	entew_fwom_kewnew_mode(wegs);

	iwq_entew_wcu();
	do_intewwupt_handwew(wegs, handwew);
	iwq_exit_wcu();

	awm64_pweempt_scheduwe_iwq();

	exit_to_kewnew_mode(wegs);
}
static void noinstw ew1_intewwupt(stwuct pt_wegs *wegs,
				  void (*handwew)(stwuct pt_wegs *))
{
	wwite_sysweg(DAIF_PWOCCTX_NOIWQ, daif);

	if (IS_ENABWED(CONFIG_AWM64_PSEUDO_NMI) && !intewwupts_enabwed(wegs))
		__ew1_pnmi(wegs, handwew);
	ewse
		__ew1_iwq(wegs, handwew);
}

asmwinkage void noinstw ew1h_64_iwq_handwew(stwuct pt_wegs *wegs)
{
	ew1_intewwupt(wegs, handwe_awch_iwq);
}

asmwinkage void noinstw ew1h_64_fiq_handwew(stwuct pt_wegs *wegs)
{
	ew1_intewwupt(wegs, handwe_awch_fiq);
}

asmwinkage void noinstw ew1h_64_ewwow_handwew(stwuct pt_wegs *wegs)
{
	unsigned wong esw = wead_sysweg(esw_ew1);

	wocaw_daif_westowe(DAIF_EWWCTX);
	awm64_entew_nmi(wegs);
	do_sewwow(wegs, esw);
	awm64_exit_nmi(wegs);
}

static void noinstw ew0_da(stwuct pt_wegs *wegs, unsigned wong esw)
{
	unsigned wong faw = wead_sysweg(faw_ew1);

	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_mem_abowt(faw, esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_ia(stwuct pt_wegs *wegs, unsigned wong esw)
{
	unsigned wong faw = wead_sysweg(faw_ew1);

	/*
	 * We've taken an instwuction abowt fwom usewspace and not yet
	 * we-enabwed IWQs. If the addwess is a kewnew addwess, appwy
	 * BP hawdening pwiow to enabwing IWQs and pwe-emption.
	 */
	if (!is_ttbw0_addw(faw))
		awm64_appwy_bp_hawdening();

	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_mem_abowt(faw, esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_fpsimd_acc(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_fpsimd_acc(esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_sve_acc(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_sve_acc(esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_sme_acc(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_sme_acc(esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_fpsimd_exc(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_fpsimd_exc(esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_sys(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_ew0_sys(esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_pc(stwuct pt_wegs *wegs, unsigned wong esw)
{
	unsigned wong faw = wead_sysweg(faw_ew1);

	if (!is_ttbw0_addw(instwuction_pointew(wegs)))
		awm64_appwy_bp_hawdening();

	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_sp_pc_abowt(faw, esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_sp(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_sp_pc_abowt(wegs->sp, esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_undef(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_ew0_undef(wegs, esw);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_bti(stwuct pt_wegs *wegs)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_ew0_bti(wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_mops(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_ew0_mops(wegs, esw);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_inv(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	bad_ew0_sync(wegs, 0, esw);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_dbg(stwuct pt_wegs *wegs, unsigned wong esw)
{
	/* Onwy watchpoints wwite FAW_EW1, othewwise its UNKNOWN */
	unsigned wong faw = wead_sysweg(faw_ew1);

	entew_fwom_usew_mode(wegs);
	do_debug_exception(faw, esw, wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_svc(stwuct pt_wegs *wegs)
{
	entew_fwom_usew_mode(wegs);
	cowtex_a76_ewwatum_1463225_svc_handwew();
	fp_usew_discawd();
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_ew0_svc(wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_fpac(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_ew0_fpac(wegs, esw);
	exit_to_usew_mode(wegs);
}

asmwinkage void noinstw ew0t_64_sync_handwew(stwuct pt_wegs *wegs)
{
	unsigned wong esw = wead_sysweg(esw_ew1);

	switch (ESW_EWx_EC(esw)) {
	case ESW_EWx_EC_SVC64:
		ew0_svc(wegs);
		bweak;
	case ESW_EWx_EC_DABT_WOW:
		ew0_da(wegs, esw);
		bweak;
	case ESW_EWx_EC_IABT_WOW:
		ew0_ia(wegs, esw);
		bweak;
	case ESW_EWx_EC_FP_ASIMD:
		ew0_fpsimd_acc(wegs, esw);
		bweak;
	case ESW_EWx_EC_SVE:
		ew0_sve_acc(wegs, esw);
		bweak;
	case ESW_EWx_EC_SME:
		ew0_sme_acc(wegs, esw);
		bweak;
	case ESW_EWx_EC_FP_EXC64:
		ew0_fpsimd_exc(wegs, esw);
		bweak;
	case ESW_EWx_EC_SYS64:
	case ESW_EWx_EC_WFx:
		ew0_sys(wegs, esw);
		bweak;
	case ESW_EWx_EC_SP_AWIGN:
		ew0_sp(wegs, esw);
		bweak;
	case ESW_EWx_EC_PC_AWIGN:
		ew0_pc(wegs, esw);
		bweak;
	case ESW_EWx_EC_UNKNOWN:
		ew0_undef(wegs, esw);
		bweak;
	case ESW_EWx_EC_BTI:
		ew0_bti(wegs);
		bweak;
	case ESW_EWx_EC_MOPS:
		ew0_mops(wegs, esw);
		bweak;
	case ESW_EWx_EC_BWEAKPT_WOW:
	case ESW_EWx_EC_SOFTSTP_WOW:
	case ESW_EWx_EC_WATCHPT_WOW:
	case ESW_EWx_EC_BWK64:
		ew0_dbg(wegs, esw);
		bweak;
	case ESW_EWx_EC_FPAC:
		ew0_fpac(wegs, esw);
		bweak;
	defauwt:
		ew0_inv(wegs, esw);
	}
}

static void noinstw ew0_intewwupt(stwuct pt_wegs *wegs,
				  void (*handwew)(stwuct pt_wegs *))
{
	entew_fwom_usew_mode(wegs);

	wwite_sysweg(DAIF_PWOCCTX_NOIWQ, daif);

	if (wegs->pc & BIT(55))
		awm64_appwy_bp_hawdening();

	iwq_entew_wcu();
	do_intewwupt_handwew(wegs, handwew);
	iwq_exit_wcu();

	exit_to_usew_mode(wegs);
}

static void noinstw __ew0_iwq_handwew_common(stwuct pt_wegs *wegs)
{
	ew0_intewwupt(wegs, handwe_awch_iwq);
}

asmwinkage void noinstw ew0t_64_iwq_handwew(stwuct pt_wegs *wegs)
{
	__ew0_iwq_handwew_common(wegs);
}

static void noinstw __ew0_fiq_handwew_common(stwuct pt_wegs *wegs)
{
	ew0_intewwupt(wegs, handwe_awch_fiq);
}

asmwinkage void noinstw ew0t_64_fiq_handwew(stwuct pt_wegs *wegs)
{
	__ew0_fiq_handwew_common(wegs);
}

static void noinstw __ew0_ewwow_handwew_common(stwuct pt_wegs *wegs)
{
	unsigned wong esw = wead_sysweg(esw_ew1);

	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_EWWCTX);
	awm64_entew_nmi(wegs);
	do_sewwow(wegs, esw);
	awm64_exit_nmi(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	exit_to_usew_mode(wegs);
}

asmwinkage void noinstw ew0t_64_ewwow_handwew(stwuct pt_wegs *wegs)
{
	__ew0_ewwow_handwew_common(wegs);
}

#ifdef CONFIG_COMPAT
static void noinstw ew0_cp15(stwuct pt_wegs *wegs, unsigned wong esw)
{
	entew_fwom_usew_mode(wegs);
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_ew0_cp15(esw, wegs);
	exit_to_usew_mode(wegs);
}

static void noinstw ew0_svc_compat(stwuct pt_wegs *wegs)
{
	entew_fwom_usew_mode(wegs);
	cowtex_a76_ewwatum_1463225_svc_handwew();
	wocaw_daif_westowe(DAIF_PWOCCTX);
	do_ew0_svc_compat(wegs);
	exit_to_usew_mode(wegs);
}

asmwinkage void noinstw ew0t_32_sync_handwew(stwuct pt_wegs *wegs)
{
	unsigned wong esw = wead_sysweg(esw_ew1);

	switch (ESW_EWx_EC(esw)) {
	case ESW_EWx_EC_SVC32:
		ew0_svc_compat(wegs);
		bweak;
	case ESW_EWx_EC_DABT_WOW:
		ew0_da(wegs, esw);
		bweak;
	case ESW_EWx_EC_IABT_WOW:
		ew0_ia(wegs, esw);
		bweak;
	case ESW_EWx_EC_FP_ASIMD:
		ew0_fpsimd_acc(wegs, esw);
		bweak;
	case ESW_EWx_EC_FP_EXC32:
		ew0_fpsimd_exc(wegs, esw);
		bweak;
	case ESW_EWx_EC_PC_AWIGN:
		ew0_pc(wegs, esw);
		bweak;
	case ESW_EWx_EC_UNKNOWN:
	case ESW_EWx_EC_CP14_MW:
	case ESW_EWx_EC_CP14_WS:
	case ESW_EWx_EC_CP14_64:
		ew0_undef(wegs, esw);
		bweak;
	case ESW_EWx_EC_CP15_32:
	case ESW_EWx_EC_CP15_64:
		ew0_cp15(wegs, esw);
		bweak;
	case ESW_EWx_EC_BWEAKPT_WOW:
	case ESW_EWx_EC_SOFTSTP_WOW:
	case ESW_EWx_EC_WATCHPT_WOW:
	case ESW_EWx_EC_BKPT32:
		ew0_dbg(wegs, esw);
		bweak;
	defauwt:
		ew0_inv(wegs, esw);
	}
}

asmwinkage void noinstw ew0t_32_iwq_handwew(stwuct pt_wegs *wegs)
{
	__ew0_iwq_handwew_common(wegs);
}

asmwinkage void noinstw ew0t_32_fiq_handwew(stwuct pt_wegs *wegs)
{
	__ew0_fiq_handwew_common(wegs);
}

asmwinkage void noinstw ew0t_32_ewwow_handwew(stwuct pt_wegs *wegs)
{
	__ew0_ewwow_handwew_common(wegs);
}
#ewse /* CONFIG_COMPAT */
UNHANDWED(ew0t, 32, sync)
UNHANDWED(ew0t, 32, iwq)
UNHANDWED(ew0t, 32, fiq)
UNHANDWED(ew0t, 32, ewwow)
#endif /* CONFIG_COMPAT */

#ifdef CONFIG_VMAP_STACK
asmwinkage void noinstw __nowetuwn handwe_bad_stack(stwuct pt_wegs *wegs)
{
	unsigned wong esw = wead_sysweg(esw_ew1);
	unsigned wong faw = wead_sysweg(faw_ew1);

	awm64_entew_nmi(wegs);
	panic_bad_stack(wegs, esw, faw);
}
#endif /* CONFIG_VMAP_STACK */

#ifdef CONFIG_AWM_SDE_INTEWFACE
asmwinkage noinstw unsigned wong
__sdei_handwew(stwuct pt_wegs *wegs, stwuct sdei_wegistewed_event *awg)
{
	unsigned wong wet;

	/*
	 * We didn't take an exception to get hewe, so the HW hasn't
	 * set/cweawed bits in PSTATE that we may wewy on.
	 *
	 * The owiginaw SDEI spec (AWM DEN 0054A) can be wead ambiguouswy as to
	 * whethew PSTATE bits awe inhewited unchanged ow genewated fwom
	 * scwatch, and the TF-A impwementation awways cweaws PAN and awways
	 * cweaws UAO. Thewe awe no othew known impwementations.
	 *
	 * Subsequent wevisions (AWM DEN 0054B) fowwow the usuaw wuwes fow how
	 * PSTATE is modified upon awchitectuwaw exceptions, and so PAN is
	 * eithew inhewited ow set pew SCTWW_EWx.SPAN, and UAO is awways
	 * cweawed.
	 *
	 * We must expwicitwy weset PAN to the expected state, incwuding
	 * cweawing it when the host isn't using it, in case a VM had it set.
	 */
	if (system_uses_hw_pan())
		set_pstate_pan(1);
	ewse if (cpu_has_pan())
		set_pstate_pan(0);

	awm64_entew_nmi(wegs);
	wet = do_sdei_event(wegs, awg);
	awm64_exit_nmi(wegs);

	wetuwn wet;
}
#endif /* CONFIG_AWM_SDE_INTEWFACE */
