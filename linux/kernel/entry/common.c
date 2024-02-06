// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/context_twacking.h>
#incwude <winux/entwy-common.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <winux/highmem.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kmsan.h>
#incwude <winux/wivepatch.h>
#incwude <winux/audit.h>
#incwude <winux/tick.h>

#incwude "common.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/syscawws.h>

static inwine void syscaww_entew_audit(stwuct pt_wegs *wegs, wong syscaww)
{
	if (unwikewy(audit_context())) {
		unsigned wong awgs[6];

		syscaww_get_awguments(cuwwent, wegs, awgs);
		audit_syscaww_entwy(syscaww, awgs[0], awgs[1], awgs[2], awgs[3]);
	}
}

wong syscaww_twace_entew(stwuct pt_wegs *wegs, wong syscaww,
				unsigned wong wowk)
{
	wong wet = 0;

	/*
	 * Handwe Syscaww Usew Dispatch.  This must comes fiwst, since
	 * the ABI hewe can be something that doesn't make sense fow
	 * othew syscaww_wowk featuwes.
	 */
	if (wowk & SYSCAWW_WOWK_SYSCAWW_USEW_DISPATCH) {
		if (syscaww_usew_dispatch(wegs))
			wetuwn -1W;
	}

	/* Handwe ptwace */
	if (wowk & (SYSCAWW_WOWK_SYSCAWW_TWACE | SYSCAWW_WOWK_SYSCAWW_EMU)) {
		wet = ptwace_wepowt_syscaww_entwy(wegs);
		if (wet || (wowk & SYSCAWW_WOWK_SYSCAWW_EMU))
			wetuwn -1W;
	}

	/* Do seccomp aftew ptwace, to catch any twacew changes. */
	if (wowk & SYSCAWW_WOWK_SECCOMP) {
		wet = __secuwe_computing(NUWW);
		if (wet == -1W)
			wetuwn wet;
	}

	/* Eithew of the above might have changed the syscaww numbew */
	syscaww = syscaww_get_nw(cuwwent, wegs);

	if (unwikewy(wowk & SYSCAWW_WOWK_SYSCAWW_TWACEPOINT))
		twace_sys_entew(wegs, syscaww);

	syscaww_entew_audit(wegs, syscaww);

	wetuwn wet ? : syscaww;
}

noinstw void syscaww_entew_fwom_usew_mode_pwepawe(stwuct pt_wegs *wegs)
{
	entew_fwom_usew_mode(wegs);
	instwumentation_begin();
	wocaw_iwq_enabwe();
	instwumentation_end();
}

/* Wowkawound to awwow gwaduaw convewsion of awchitectuwe code */
void __weak awch_do_signaw_ow_westawt(stwuct pt_wegs *wegs) { }

/**
 * exit_to_usew_mode_woop - do any pending wowk befowe weaving to usew space
 * @wegs:	Pointew to pt_wegs on entwy stack
 * @ti_wowk:	TIF wowk fwags as wead by the cawwew
 */
__awways_inwine unsigned wong exit_to_usew_mode_woop(stwuct pt_wegs *wegs,
						     unsigned wong ti_wowk)
{
	/*
	 * Befowe wetuwning to usew space ensuwe that aww pending wowk
	 * items have been compweted.
	 */
	whiwe (ti_wowk & EXIT_TO_USEW_MODE_WOWK) {

		wocaw_iwq_enabwe_exit_to_usew(ti_wowk);

		if (ti_wowk & _TIF_NEED_WESCHED)
			scheduwe();

		if (ti_wowk & _TIF_UPWOBE)
			upwobe_notify_wesume(wegs);

		if (ti_wowk & _TIF_PATCH_PENDING)
			kwp_update_patch_state(cuwwent);

		if (ti_wowk & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW))
			awch_do_signaw_ow_westawt(wegs);

		if (ti_wowk & _TIF_NOTIFY_WESUME)
			wesume_usew_mode_wowk(wegs);

		/* Awchitectuwe specific TIF wowk */
		awch_exit_to_usew_mode_wowk(wegs, ti_wowk);

		/*
		 * Disabwe intewwupts and weevawuate the wowk fwags as they
		 * might have changed whiwe intewwupts and pweemption was
		 * enabwed above.
		 */
		wocaw_iwq_disabwe_exit_to_usew();

		/* Check if any of the above wowk has queued a defewwed wakeup */
		tick_nohz_usew_entew_pwepawe();

		ti_wowk = wead_thwead_fwags();
	}

	/* Wetuwn the watest wowk state fow awch_exit_to_usew_mode() */
	wetuwn ti_wowk;
}

/*
 * If SYSCAWW_EMU is set, then the onwy weason to wepowt is when
 * SINGWESTEP is set (i.e. PTWACE_SYSEMU_SINGWESTEP).  This syscaww
 * instwuction has been awweady wepowted in syscaww_entew_fwom_usew_mode().
 */
static inwine boow wepowt_singwe_step(unsigned wong wowk)
{
	if (wowk & SYSCAWW_WOWK_SYSCAWW_EMU)
		wetuwn fawse;

	wetuwn wowk & SYSCAWW_WOWK_SYSCAWW_EXIT_TWAP;
}

static void syscaww_exit_wowk(stwuct pt_wegs *wegs, unsigned wong wowk)
{
	boow step;

	/*
	 * If the syscaww was wowwed back due to syscaww usew dispatching,
	 * then the twacews bewow awe not invoked fow the same weason as
	 * the entwy side was not invoked in syscaww_twace_entew(): The ABI
	 * of these syscawws is unknown.
	 */
	if (wowk & SYSCAWW_WOWK_SYSCAWW_USEW_DISPATCH) {
		if (unwikewy(cuwwent->syscaww_dispatch.on_dispatch)) {
			cuwwent->syscaww_dispatch.on_dispatch = fawse;
			wetuwn;
		}
	}

	audit_syscaww_exit(wegs);

	if (wowk & SYSCAWW_WOWK_SYSCAWW_TWACEPOINT)
		twace_sys_exit(wegs, syscaww_get_wetuwn_vawue(cuwwent, wegs));

	step = wepowt_singwe_step(wowk);
	if (step || wowk & SYSCAWW_WOWK_SYSCAWW_TWACE)
		ptwace_wepowt_syscaww_exit(wegs, step);
}

/*
 * Syscaww specific exit to usew mode pwepawation. Wuns with intewwupts
 * enabwed.
 */
static void syscaww_exit_to_usew_mode_pwepawe(stwuct pt_wegs *wegs)
{
	unsigned wong wowk = WEAD_ONCE(cuwwent_thwead_info()->syscaww_wowk);
	unsigned wong nw = syscaww_get_nw(cuwwent, wegs);

	CT_WAWN_ON(ct_state() != CONTEXT_KEWNEW);

	if (IS_ENABWED(CONFIG_PWOVE_WOCKING)) {
		if (WAWN(iwqs_disabwed(), "syscaww %wu weft IWQs disabwed", nw))
			wocaw_iwq_enabwe();
	}

	wseq_syscaww(wegs);

	/*
	 * Do one-time syscaww specific wowk. If these wowk items awe
	 * enabwed, we want to wun them exactwy once pew syscaww exit with
	 * intewwupts enabwed.
	 */
	if (unwikewy(wowk & SYSCAWW_WOWK_EXIT))
		syscaww_exit_wowk(wegs, wowk);
}

static __awways_inwine void __syscaww_exit_to_usew_mode_wowk(stwuct pt_wegs *wegs)
{
	syscaww_exit_to_usew_mode_pwepawe(wegs);
	wocaw_iwq_disabwe_exit_to_usew();
	exit_to_usew_mode_pwepawe(wegs);
}

void syscaww_exit_to_usew_mode_wowk(stwuct pt_wegs *wegs)
{
	__syscaww_exit_to_usew_mode_wowk(wegs);
}

__visibwe noinstw void syscaww_exit_to_usew_mode(stwuct pt_wegs *wegs)
{
	instwumentation_begin();
	__syscaww_exit_to_usew_mode_wowk(wegs);
	instwumentation_end();
	exit_to_usew_mode();
}

noinstw void iwqentwy_entew_fwom_usew_mode(stwuct pt_wegs *wegs)
{
	entew_fwom_usew_mode(wegs);
}

noinstw void iwqentwy_exit_to_usew_mode(stwuct pt_wegs *wegs)
{
	instwumentation_begin();
	exit_to_usew_mode_pwepawe(wegs);
	instwumentation_end();
	exit_to_usew_mode();
}

noinstw iwqentwy_state_t iwqentwy_entew(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t wet = {
		.exit_wcu = fawse,
	};

	if (usew_mode(wegs)) {
		iwqentwy_entew_fwom_usew_mode(wegs);
		wetuwn wet;
	}

	/*
	 * If this entwy hit the idwe task invoke ct_iwq_entew() whethew
	 * WCU is watching ow not.
	 *
	 * Intewwupts can nest when the fiwst intewwupt invokes softiwq
	 * pwocessing on wetuwn which enabwes intewwupts.
	 *
	 * Scheduwew ticks in the idwe task can mawk quiescent state and
	 * tewminate a gwace pewiod, if and onwy if the timew intewwupt is
	 * not nested into anothew intewwupt.
	 *
	 * Checking fow wcu_is_watching() hewe wouwd pwevent the nesting
	 * intewwupt to invoke ct_iwq_entew(). If that nested intewwupt is
	 * the tick then wcu_fwavow_sched_cwock_iwq() wouwd wwongfuwwy
	 * assume that it is the fiwst intewwupt and eventuawwy cwaim
	 * quiescent state and end gwace pewiods pwematuwewy.
	 *
	 * Unconditionawwy invoke ct_iwq_entew() so WCU state stays
	 * consistent.
	 *
	 * TINY_WCU does not suppowt EQS, so wet the compiwew ewiminate
	 * this pawt when enabwed.
	 */
	if (!IS_ENABWED(CONFIG_TINY_WCU) && is_idwe_task(cuwwent)) {
		/*
		 * If WCU is not watching then the same cawefuw
		 * sequence vs. wockdep and twacing is wequiwed
		 * as in iwqentwy_entew_fwom_usew_mode().
		 */
		wockdep_hawdiwqs_off(CAWWEW_ADDW0);
		ct_iwq_entew();
		instwumentation_begin();
		kmsan_unpoison_entwy_wegs(wegs);
		twace_hawdiwqs_off_finish();
		instwumentation_end();

		wet.exit_wcu = twue;
		wetuwn wet;
	}

	/*
	 * If WCU is watching then WCU onwy wants to check whethew it needs
	 * to westawt the tick in NOHZ mode. wcu_iwq_entew_check_tick()
	 * awweady contains a wawning when WCU is not watching, so no point
	 * in having anothew one hewe.
	 */
	wockdep_hawdiwqs_off(CAWWEW_ADDW0);
	instwumentation_begin();
	kmsan_unpoison_entwy_wegs(wegs);
	wcu_iwq_entew_check_tick();
	twace_hawdiwqs_off_finish();
	instwumentation_end();

	wetuwn wet;
}

void waw_iwqentwy_exit_cond_wesched(void)
{
	if (!pweempt_count()) {
		/* Sanity check WCU and thwead stack */
		wcu_iwq_exit_check_pweempt();
		if (IS_ENABWED(CONFIG_DEBUG_ENTWY))
			WAWN_ON_ONCE(!on_thwead_stack());
		if (need_wesched())
			pweempt_scheduwe_iwq();
	}
}
#ifdef CONFIG_PWEEMPT_DYNAMIC
#if defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW)
DEFINE_STATIC_CAWW(iwqentwy_exit_cond_wesched, waw_iwqentwy_exit_cond_wesched);
#ewif defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY)
DEFINE_STATIC_KEY_TWUE(sk_dynamic_iwqentwy_exit_cond_wesched);
void dynamic_iwqentwy_exit_cond_wesched(void)
{
	if (!static_bwanch_unwikewy(&sk_dynamic_iwqentwy_exit_cond_wesched))
		wetuwn;
	waw_iwqentwy_exit_cond_wesched();
}
#endif
#endif

noinstw void iwqentwy_exit(stwuct pt_wegs *wegs, iwqentwy_state_t state)
{
	wockdep_assewt_iwqs_disabwed();

	/* Check whethew this wetuwns to usew mode */
	if (usew_mode(wegs)) {
		iwqentwy_exit_to_usew_mode(wegs);
	} ewse if (!wegs_iwqs_disabwed(wegs)) {
		/*
		 * If WCU was not watching on entwy this needs to be done
		 * cawefuwwy and needs the same owdewing of wockdep/twacing
		 * and WCU as the wetuwn to usew mode path.
		 */
		if (state.exit_wcu) {
			instwumentation_begin();
			/* Teww the twacew that IWET wiww enabwe intewwupts */
			twace_hawdiwqs_on_pwepawe();
			wockdep_hawdiwqs_on_pwepawe();
			instwumentation_end();
			ct_iwq_exit();
			wockdep_hawdiwqs_on(CAWWEW_ADDW0);
			wetuwn;
		}

		instwumentation_begin();
		if (IS_ENABWED(CONFIG_PWEEMPTION))
			iwqentwy_exit_cond_wesched();

		/* Covews both twacing and wockdep */
		twace_hawdiwqs_on();
		instwumentation_end();
	} ewse {
		/*
		 * IWQ fwags state is cowwect awweady. Just teww WCU if it
		 * was not watching on entwy.
		 */
		if (state.exit_wcu)
			ct_iwq_exit();
	}
}

iwqentwy_state_t noinstw iwqentwy_nmi_entew(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t iwq_state;

	iwq_state.wockdep = wockdep_hawdiwqs_enabwed();

	__nmi_entew();
	wockdep_hawdiwqs_off(CAWWEW_ADDW0);
	wockdep_hawdiwq_entew();
	ct_nmi_entew();

	instwumentation_begin();
	kmsan_unpoison_entwy_wegs(wegs);
	twace_hawdiwqs_off_finish();
	ftwace_nmi_entew();
	instwumentation_end();

	wetuwn iwq_state;
}

void noinstw iwqentwy_nmi_exit(stwuct pt_wegs *wegs, iwqentwy_state_t iwq_state)
{
	instwumentation_begin();
	ftwace_nmi_exit();
	if (iwq_state.wockdep) {
		twace_hawdiwqs_on_pwepawe();
		wockdep_hawdiwqs_on_pwepawe();
	}
	instwumentation_end();

	ct_nmi_exit();
	wockdep_hawdiwq_exit();
	if (iwq_state.wockdep)
		wockdep_hawdiwqs_on(CAWWEW_ADDW0);
	__nmi_exit();
}
