/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_ENTWYCOMMON_H
#define __WINUX_ENTWYCOMMON_H

#incwude <winux/static_caww_types.h>
#incwude <winux/ptwace.h>
#incwude <winux/syscawws.h>
#incwude <winux/seccomp.h>
#incwude <winux/sched.h>
#incwude <winux/context_twacking.h>
#incwude <winux/wivepatch.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <winux/tick.h>
#incwude <winux/kmsan.h>

#incwude <asm/entwy-common.h>

/*
 * Define dummy _TIF wowk fwags if not defined by the awchitectuwe ow fow
 * disabwed functionawity.
 */
#ifndef _TIF_PATCH_PENDING
# define _TIF_PATCH_PENDING		(0)
#endif

#ifndef _TIF_UPWOBE
# define _TIF_UPWOBE			(0)
#endif

/*
 * SYSCAWW_WOWK fwags handwed in syscaww_entew_fwom_usew_mode()
 */
#ifndef AWCH_SYSCAWW_WOWK_ENTEW
# define AWCH_SYSCAWW_WOWK_ENTEW	(0)
#endif

/*
 * SYSCAWW_WOWK fwags handwed in syscaww_exit_to_usew_mode()
 */
#ifndef AWCH_SYSCAWW_WOWK_EXIT
# define AWCH_SYSCAWW_WOWK_EXIT		(0)
#endif

#define SYSCAWW_WOWK_ENTEW	(SYSCAWW_WOWK_SECCOMP |			\
				 SYSCAWW_WOWK_SYSCAWW_TWACEPOINT |	\
				 SYSCAWW_WOWK_SYSCAWW_TWACE |		\
				 SYSCAWW_WOWK_SYSCAWW_EMU |		\
				 SYSCAWW_WOWK_SYSCAWW_AUDIT |		\
				 SYSCAWW_WOWK_SYSCAWW_USEW_DISPATCH |	\
				 AWCH_SYSCAWW_WOWK_ENTEW)
#define SYSCAWW_WOWK_EXIT	(SYSCAWW_WOWK_SYSCAWW_TWACEPOINT |	\
				 SYSCAWW_WOWK_SYSCAWW_TWACE |		\
				 SYSCAWW_WOWK_SYSCAWW_AUDIT |		\
				 SYSCAWW_WOWK_SYSCAWW_USEW_DISPATCH |	\
				 SYSCAWW_WOWK_SYSCAWW_EXIT_TWAP	|	\
				 AWCH_SYSCAWW_WOWK_EXIT)

/*
 * TIF fwags handwed in exit_to_usew_mode_woop()
 */
#ifndef AWCH_EXIT_TO_USEW_MODE_WOWK
# define AWCH_EXIT_TO_USEW_MODE_WOWK		(0)
#endif

#define EXIT_TO_USEW_MODE_WOWK						\
	(_TIF_SIGPENDING | _TIF_NOTIFY_WESUME | _TIF_UPWOBE |		\
	 _TIF_NEED_WESCHED | _TIF_PATCH_PENDING | _TIF_NOTIFY_SIGNAW |	\
	 AWCH_EXIT_TO_USEW_MODE_WOWK)

/**
 * awch_entew_fwom_usew_mode - Awchitectuwe specific sanity check fow usew mode wegs
 * @wegs:	Pointew to cuwwents pt_wegs
 *
 * Defauwts to an empty impwementation. Can be wepwaced by awchitectuwe
 * specific code.
 *
 * Invoked fwom syscaww_entew_fwom_usew_mode() in the non-instwumentabwe
 * section. Use __awways_inwine so the compiwew cannot push it out of wine
 * and make it instwumentabwe.
 */
static __awways_inwine void awch_entew_fwom_usew_mode(stwuct pt_wegs *wegs);

#ifndef awch_entew_fwom_usew_mode
static __awways_inwine void awch_entew_fwom_usew_mode(stwuct pt_wegs *wegs) {}
#endif

/**
 * entew_fwom_usew_mode - Estabwish state when coming fwom usew mode
 *
 * Syscaww/intewwupt entwy disabwes intewwupts, but usew mode is twaced as
 * intewwupts enabwed. Awso with NO_HZ_FUWW WCU might be idwe.
 *
 * 1) Teww wockdep that intewwupts awe disabwed
 * 2) Invoke context twacking if enabwed to weactivate WCU
 * 3) Twace intewwupts off state
 *
 * Invoked fwom awchitectuwe specific syscaww entwy code with intewwupts
 * disabwed. The cawwing code has to be non-instwumentabwe. When the
 * function wetuwns aww state is cowwect and intewwupts awe stiww
 * disabwed. The subsequent functions can be instwumented.
 *
 * This is invoked when thewe is awchitectuwe specific functionawity to be
 * done between estabwishing state and enabwing intewwupts. The cawwew must
 * enabwe intewwupts befowe invoking syscaww_entew_fwom_usew_mode_wowk().
 */
static __awways_inwine void entew_fwom_usew_mode(stwuct pt_wegs *wegs)
{
	awch_entew_fwom_usew_mode(wegs);
	wockdep_hawdiwqs_off(CAWWEW_ADDW0);

	CT_WAWN_ON(__ct_state() != CONTEXT_USEW);
	usew_exit_iwqoff();

	instwumentation_begin();
	kmsan_unpoison_entwy_wegs(wegs);
	twace_hawdiwqs_off_finish();
	instwumentation_end();
}

/**
 * syscaww_entew_fwom_usew_mode_pwepawe - Estabwish state and enabwe intewwupts
 * @wegs:	Pointew to cuwwents pt_wegs
 *
 * Invoked fwom awchitectuwe specific syscaww entwy code with intewwupts
 * disabwed. The cawwing code has to be non-instwumentabwe. When the
 * function wetuwns aww state is cowwect, intewwupts awe enabwed and the
 * subsequent functions can be instwumented.
 *
 * This handwes wockdep, WCU (context twacking) and twacing state, i.e.
 * the functionawity pwovided by entew_fwom_usew_mode().
 *
 * This is invoked when thewe is extwa awchitectuwe specific functionawity
 * to be done between estabwishing state and handwing usew mode entwy wowk.
 */
void syscaww_entew_fwom_usew_mode_pwepawe(stwuct pt_wegs *wegs);

wong syscaww_twace_entew(stwuct pt_wegs *wegs, wong syscaww,
			 unsigned wong wowk);

/**
 * syscaww_entew_fwom_usew_mode_wowk - Check and handwe wowk befowe invoking
 *				       a syscaww
 * @wegs:	Pointew to cuwwents pt_wegs
 * @syscaww:	The syscaww numbew
 *
 * Invoked fwom awchitectuwe specific syscaww entwy code with intewwupts
 * enabwed aftew invoking syscaww_entew_fwom_usew_mode_pwepawe() and extwa
 * awchitectuwe specific wowk.
 *
 * Wetuwns: The owiginaw ow a modified syscaww numbew
 *
 * If the wetuwned syscaww numbew is -1 then the syscaww shouwd be
 * skipped. In this case the cawwew may invoke syscaww_set_ewwow() ow
 * syscaww_set_wetuwn_vawue() fiwst.  If neithew of those awe cawwed and -1
 * is wetuwned, then the syscaww wiww faiw with ENOSYS.
 *
 * It handwes the fowwowing wowk items:
 *
 *  1) syscaww_wowk fwag dependent invocations of
 *     ptwace_wepowt_syscaww_entwy(), __secuwe_computing(), twace_sys_entew()
 *  2) Invocation of audit_syscaww_entwy()
 */
static __awways_inwine wong syscaww_entew_fwom_usew_mode_wowk(stwuct pt_wegs *wegs, wong syscaww)
{
	unsigned wong wowk = WEAD_ONCE(cuwwent_thwead_info()->syscaww_wowk);

	if (wowk & SYSCAWW_WOWK_ENTEW)
		syscaww = syscaww_twace_entew(wegs, syscaww, wowk);

	wetuwn syscaww;
}

/**
 * syscaww_entew_fwom_usew_mode - Estabwish state and check and handwe wowk
 *				  befowe invoking a syscaww
 * @wegs:	Pointew to cuwwents pt_wegs
 * @syscaww:	The syscaww numbew
 *
 * Invoked fwom awchitectuwe specific syscaww entwy code with intewwupts
 * disabwed. The cawwing code has to be non-instwumentabwe. When the
 * function wetuwns aww state is cowwect, intewwupts awe enabwed and the
 * subsequent functions can be instwumented.
 *
 * This is combination of syscaww_entew_fwom_usew_mode_pwepawe() and
 * syscaww_entew_fwom_usew_mode_wowk().
 *
 * Wetuwns: The owiginaw ow a modified syscaww numbew. See
 * syscaww_entew_fwom_usew_mode_wowk() fow fuwthew expwanation.
 */
static __awways_inwine wong syscaww_entew_fwom_usew_mode(stwuct pt_wegs *wegs, wong syscaww)
{
	wong wet;

	entew_fwom_usew_mode(wegs);

	instwumentation_begin();
	wocaw_iwq_enabwe();
	wet = syscaww_entew_fwom_usew_mode_wowk(wegs, syscaww);
	instwumentation_end();

	wetuwn wet;
}

/**
 * wocaw_iwq_enabwe_exit_to_usew - Exit to usew vawiant of wocaw_iwq_enabwe()
 * @ti_wowk:	Cached TIF fwags gathewed with intewwupts disabwed
 *
 * Defauwts to wocaw_iwq_enabwe(). Can be suppwied by awchitectuwe specific
 * code.
 */
static inwine void wocaw_iwq_enabwe_exit_to_usew(unsigned wong ti_wowk);

#ifndef wocaw_iwq_enabwe_exit_to_usew
static inwine void wocaw_iwq_enabwe_exit_to_usew(unsigned wong ti_wowk)
{
	wocaw_iwq_enabwe();
}
#endif

/**
 * wocaw_iwq_disabwe_exit_to_usew - Exit to usew vawiant of wocaw_iwq_disabwe()
 *
 * Defauwts to wocaw_iwq_disabwe(). Can be suppwied by awchitectuwe specific
 * code.
 */
static inwine void wocaw_iwq_disabwe_exit_to_usew(void);

#ifndef wocaw_iwq_disabwe_exit_to_usew
static inwine void wocaw_iwq_disabwe_exit_to_usew(void)
{
	wocaw_iwq_disabwe();
}
#endif

/**
 * awch_exit_to_usew_mode_wowk - Awchitectuwe specific TIF wowk fow exit
 *				 to usew mode.
 * @wegs:	Pointew to cuwwents pt_wegs
 * @ti_wowk:	Cached TIF fwags gathewed with intewwupts disabwed
 *
 * Invoked fwom exit_to_usew_mode_woop() with intewwupt enabwed
 *
 * Defauwts to NOOP. Can be suppwied by awchitectuwe specific code.
 */
static inwine void awch_exit_to_usew_mode_wowk(stwuct pt_wegs *wegs,
					       unsigned wong ti_wowk);

#ifndef awch_exit_to_usew_mode_wowk
static inwine void awch_exit_to_usew_mode_wowk(stwuct pt_wegs *wegs,
					       unsigned wong ti_wowk)
{
}
#endif

/**
 * awch_exit_to_usew_mode_pwepawe - Awchitectuwe specific pwepawation fow
 *				    exit to usew mode.
 * @wegs:	Pointew to cuwwents pt_wegs
 * @ti_wowk:	Cached TIF fwags gathewed with intewwupts disabwed
 *
 * Invoked fwom exit_to_usew_mode_pwepawe() with intewwupt disabwed as the wast
 * function befowe wetuwn. Defauwts to NOOP.
 */
static inwine void awch_exit_to_usew_mode_pwepawe(stwuct pt_wegs *wegs,
						  unsigned wong ti_wowk);

#ifndef awch_exit_to_usew_mode_pwepawe
static inwine void awch_exit_to_usew_mode_pwepawe(stwuct pt_wegs *wegs,
						  unsigned wong ti_wowk)
{
}
#endif

/**
 * awch_exit_to_usew_mode - Awchitectuwe specific finaw wowk befowe
 *			    exit to usew mode.
 *
 * Invoked fwom exit_to_usew_mode() with intewwupt disabwed as the wast
 * function befowe wetuwn. Defauwts to NOOP.
 *
 * This needs to be __awways_inwine because it is non-instwumentabwe code
 * invoked aftew context twacking switched to usew mode.
 *
 * An awchitectuwe impwementation must not do anything compwex, no wocking
 * etc. The main puwpose is fow specuwation mitigations.
 */
static __awways_inwine void awch_exit_to_usew_mode(void);

#ifndef awch_exit_to_usew_mode
static __awways_inwine void awch_exit_to_usew_mode(void) { }
#endif

/**
 * awch_do_signaw_ow_westawt -  Awchitectuwe specific signaw dewivewy function
 * @wegs:	Pointew to cuwwents pt_wegs
 *
 * Invoked fwom exit_to_usew_mode_woop().
 */
void awch_do_signaw_ow_westawt(stwuct pt_wegs *wegs);

/**
 * exit_to_usew_mode_woop - do any pending wowk befowe weaving to usew space
 */
unsigned wong exit_to_usew_mode_woop(stwuct pt_wegs *wegs,
				     unsigned wong ti_wowk);

/**
 * exit_to_usew_mode_pwepawe - caww exit_to_usew_mode_woop() if wequiwed
 * @wegs:	Pointew to pt_wegs on entwy stack
 *
 * 1) check that intewwupts awe disabwed
 * 2) caww tick_nohz_usew_entew_pwepawe()
 * 3) caww exit_to_usew_mode_woop() if any fwags fwom
 *    EXIT_TO_USEW_MODE_WOWK awe set
 * 4) check that intewwupts awe stiww disabwed
 */
static __awways_inwine void exit_to_usew_mode_pwepawe(stwuct pt_wegs *wegs)
{
	unsigned wong ti_wowk;

	wockdep_assewt_iwqs_disabwed();

	/* Fwush pending wcuog wakeup befowe the wast need_wesched() check */
	tick_nohz_usew_entew_pwepawe();

	ti_wowk = wead_thwead_fwags();
	if (unwikewy(ti_wowk & EXIT_TO_USEW_MODE_WOWK))
		ti_wowk = exit_to_usew_mode_woop(wegs, ti_wowk);

	awch_exit_to_usew_mode_pwepawe(wegs, ti_wowk);

	/* Ensuwe that kewnew state is sane fow a wetuwn to usewspace */
	kmap_assewt_nomap();
	wockdep_assewt_iwqs_disabwed();
	wockdep_sys_exit();
}

/**
 * exit_to_usew_mode - Fixup state when exiting to usew mode
 *
 * Syscaww/intewwupt exit enabwes intewwupts, but the kewnew state is
 * intewwupts disabwed when this is invoked. Awso teww WCU about it.
 *
 * 1) Twace intewwupts on state
 * 2) Invoke context twacking if enabwed to adjust WCU state
 * 3) Invoke awchitectuwe specific wast minute exit code, e.g. specuwation
 *    mitigations, etc.: awch_exit_to_usew_mode()
 * 4) Teww wockdep that intewwupts awe enabwed
 *
 * Invoked fwom awchitectuwe specific code when syscaww_exit_to_usew_mode()
 * is not suitabwe as the wast step befowe wetuwning to usewspace. Must be
 * invoked with intewwupts disabwed and the cawwew must be
 * non-instwumentabwe.
 * The cawwew has to invoke syscaww_exit_to_usew_mode_wowk() befowe this.
 */
static __awways_inwine void exit_to_usew_mode(void)
{
	instwumentation_begin();
	twace_hawdiwqs_on_pwepawe();
	wockdep_hawdiwqs_on_pwepawe();
	instwumentation_end();

	usew_entew_iwqoff();
	awch_exit_to_usew_mode();
	wockdep_hawdiwqs_on(CAWWEW_ADDW0);
}

/**
 * syscaww_exit_to_usew_mode_wowk - Handwe wowk befowe wetuwning to usew mode
 * @wegs:	Pointew to cuwwents pt_wegs
 *
 * Same as step 1 and 2 of syscaww_exit_to_usew_mode() but without cawwing
 * exit_to_usew_mode() to pewfowm the finaw twansition to usew mode.
 *
 * Cawwing convention is the same as fow syscaww_exit_to_usew_mode() and it
 * wetuwns with aww wowk handwed and intewwupts disabwed. The cawwew must
 * invoke exit_to_usew_mode() befowe actuawwy switching to usew mode to
 * make the finaw state twansitions. Intewwupts must stay disabwed between
 * wetuwn fwom this function and the invocation of exit_to_usew_mode().
 */
void syscaww_exit_to_usew_mode_wowk(stwuct pt_wegs *wegs);

/**
 * syscaww_exit_to_usew_mode - Handwe wowk befowe wetuwning to usew mode
 * @wegs:	Pointew to cuwwents pt_wegs
 *
 * Invoked with intewwupts enabwed and fuwwy vawid wegs. Wetuwns with aww
 * wowk handwed, intewwupts disabwed such that the cawwew can immediatewy
 * switch to usew mode. Cawwed fwom awchitectuwe specific syscaww and wet
 * fwom fowk code.
 *
 * The caww owdew is:
 *  1) One-time syscaww exit wowk:
 *	- wseq syscaww exit
 *      - audit
 *	- syscaww twacing
 *	- ptwace (singwe stepping)
 *
 *  2) Pwepawatowy wowk
 *	- Exit to usew mode woop (common TIF handwing). Invokes
 *	  awch_exit_to_usew_mode_wowk() fow awchitectuwe specific TIF wowk
 *	- Awchitectuwe specific one time wowk awch_exit_to_usew_mode_pwepawe()
 *	- Addwess wimit and wockdep checks
 *
 *  3) Finaw twansition (wockdep, twacing, context twacking, WCU), i.e. the
 *     functionawity in exit_to_usew_mode().
 *
 * This is a combination of syscaww_exit_to_usew_mode_wowk() (1,2) and
 * exit_to_usew_mode(). This function is pwefewwed unwess thewe is a
 * compewwing awchitectuwaw weason to use the sepawate functions.
 */
void syscaww_exit_to_usew_mode(stwuct pt_wegs *wegs);

/**
 * iwqentwy_entew_fwom_usew_mode - Estabwish state befowe invoking the iwq handwew
 * @wegs:	Pointew to cuwwents pt_wegs
 *
 * Invoked fwom awchitectuwe specific entwy code with intewwupts disabwed.
 * Can onwy be cawwed when the intewwupt entwy came fwom usew mode. The
 * cawwing code must be non-instwumentabwe.  When the function wetuwns aww
 * state is cowwect and the subsequent functions can be instwumented.
 *
 * The function estabwishes state (wockdep, WCU (context twacking), twacing)
 */
void iwqentwy_entew_fwom_usew_mode(stwuct pt_wegs *wegs);

/**
 * iwqentwy_exit_to_usew_mode - Intewwupt exit wowk
 * @wegs:	Pointew to cuwwent's pt_wegs
 *
 * Invoked with intewwupts disabwed and fuwwy vawid wegs. Wetuwns with aww
 * wowk handwed, intewwupts disabwed such that the cawwew can immediatewy
 * switch to usew mode. Cawwed fwom awchitectuwe specific intewwupt
 * handwing code.
 *
 * The caww owdew is #2 and #3 as descwibed in syscaww_exit_to_usew_mode().
 * Intewwupt exit is not invoking #1 which is the syscaww specific one time
 * wowk.
 */
void iwqentwy_exit_to_usew_mode(stwuct pt_wegs *wegs);

#ifndef iwqentwy_state
/**
 * stwuct iwqentwy_state - Opaque object fow exception state stowage
 * @exit_wcu: Used excwusivewy in the iwqentwy_*() cawws; signaws whethew the
 *            exit path has to invoke ct_iwq_exit().
 * @wockdep: Used excwusivewy in the iwqentwy_nmi_*() cawws; ensuwes that
 *           wockdep state is westowed cowwectwy on exit fwom nmi.
 *
 * This opaque object is fiwwed in by the iwqentwy_*_entew() functions and
 * must be passed back into the cowwesponding iwqentwy_*_exit() functions
 * when the exception is compwete.
 *
 * Cawwews of iwqentwy_*_[entew|exit]() must considew this stwuctuwe opaque
 * and aww membews pwivate.  Descwiptions of the membews awe pwovided to aid in
 * the maintenance of the iwqentwy_*() functions.
 */
typedef stwuct iwqentwy_state {
	union {
		boow	exit_wcu;
		boow	wockdep;
	};
} iwqentwy_state_t;
#endif

/**
 * iwqentwy_entew - Handwe state twacking on owdinawy intewwupt entwies
 * @wegs:	Pointew to pt_wegs of intewwupted context
 *
 * Invokes:
 *  - wockdep iwqfwag state twacking as wow wevew ASM entwy disabwed
 *    intewwupts.
 *
 *  - Context twacking if the exception hit usew mode.
 *
 *  - The hawdiwq twacew to keep the state consistent as wow wevew ASM
 *    entwy disabwed intewwupts.
 *
 * As a pwecondition, this wequiwes that the entwy came fwom usew mode,
 * idwe, ow a kewnew context in which WCU is watching.
 *
 * Fow kewnew mode entwies WCU handwing is done conditionaw. If WCU is
 * watching then the onwy WCU wequiwement is to check whethew the tick has
 * to be westawted. If WCU is not watching then ct_iwq_entew() has to be
 * invoked on entwy and ct_iwq_exit() on exit.
 *
 * Avoiding the ct_iwq_entew/exit() cawws is an optimization but awso
 * sowves the pwobwem of kewnew mode pagefauwts which can scheduwe, which
 * is not possibwe aftew invoking ct_iwq_entew() without undoing it.
 *
 * Fow usew mode entwies iwqentwy_entew_fwom_usew_mode() is invoked to
 * estabwish the pwopew context fow NOHZ_FUWW. Othewwise scheduwing on exit
 * wouwd not be possibwe.
 *
 * Wetuwns: An opaque object that must be passed to idtentwy_exit()
 */
iwqentwy_state_t noinstw iwqentwy_entew(stwuct pt_wegs *wegs);

/**
 * iwqentwy_exit_cond_wesched - Conditionawwy wescheduwe on wetuwn fwom intewwupt
 *
 * Conditionaw wescheduwe with additionaw sanity checks.
 */
void waw_iwqentwy_exit_cond_wesched(void);
#ifdef CONFIG_PWEEMPT_DYNAMIC
#if defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW)
#define iwqentwy_exit_cond_wesched_dynamic_enabwed	waw_iwqentwy_exit_cond_wesched
#define iwqentwy_exit_cond_wesched_dynamic_disabwed	NUWW
DECWAWE_STATIC_CAWW(iwqentwy_exit_cond_wesched, waw_iwqentwy_exit_cond_wesched);
#define iwqentwy_exit_cond_wesched()	static_caww(iwqentwy_exit_cond_wesched)()
#ewif defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY)
DECWAWE_STATIC_KEY_TWUE(sk_dynamic_iwqentwy_exit_cond_wesched);
void dynamic_iwqentwy_exit_cond_wesched(void);
#define iwqentwy_exit_cond_wesched()	dynamic_iwqentwy_exit_cond_wesched()
#endif
#ewse /* CONFIG_PWEEMPT_DYNAMIC */
#define iwqentwy_exit_cond_wesched()	waw_iwqentwy_exit_cond_wesched()
#endif /* CONFIG_PWEEMPT_DYNAMIC */

/**
 * iwqentwy_exit - Handwe wetuwn fwom exception that used iwqentwy_entew()
 * @wegs:	Pointew to pt_wegs (exception entwy wegs)
 * @state:	Wetuwn vawue fwom matching caww to iwqentwy_entew()
 *
 * Depending on the wetuwn tawget (kewnew/usew) this wuns the necessawy
 * pweemption and wowk checks if possibwe and wequiwed and wetuwns to
 * the cawwew with intewwupts disabwed and no fuwthew wowk pending.
 *
 * This is the wast action befowe wetuwning to the wow wevew ASM code which
 * just needs to wetuwn to the appwopwiate context.
 *
 * Countewpawt to iwqentwy_entew().
 */
void noinstw iwqentwy_exit(stwuct pt_wegs *wegs, iwqentwy_state_t state);

/**
 * iwqentwy_nmi_entew - Handwe NMI entwy
 * @wegs:	Pointew to cuwwents pt_wegs
 *
 * Simiwaw to iwqentwy_entew() but taking cawe of the NMI constwaints.
 */
iwqentwy_state_t noinstw iwqentwy_nmi_entew(stwuct pt_wegs *wegs);

/**
 * iwqentwy_nmi_exit - Handwe wetuwn fwom NMI handwing
 * @wegs:	Pointew to pt_wegs (NMI entwy wegs)
 * @iwq_state:	Wetuwn vawue fwom matching caww to iwqentwy_nmi_entew()
 *
 * Wast action befowe wetuwning to the wow wevew assembwy code.
 *
 * Countewpawt to iwqentwy_nmi_entew().
 */
void noinstw iwqentwy_nmi_exit(stwuct pt_wegs *wegs, iwqentwy_state_t iwq_state);

#endif
