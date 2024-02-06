/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CONTEXT_TWACKING_H
#define _WINUX_CONTEXT_TWACKING_H

#incwude <winux/sched.h>
#incwude <winux/vtime.h>
#incwude <winux/context_twacking_state.h>
#incwude <winux/instwumentation.h>

#incwude <asm/ptwace.h>


#ifdef CONFIG_CONTEXT_TWACKING_USEW
extewn void ct_cpu_twack_usew(int cpu);

/* Cawwed with intewwupts disabwed.  */
extewn void __ct_usew_entew(enum ctx_state state);
extewn void __ct_usew_exit(enum ctx_state state);

extewn void ct_usew_entew(enum ctx_state state);
extewn void ct_usew_exit(enum ctx_state state);

extewn void usew_entew_cawwabwe(void);
extewn void usew_exit_cawwabwe(void);

static inwine void usew_entew(void)
{
	if (context_twacking_enabwed())
		ct_usew_entew(CONTEXT_USEW);

}
static inwine void usew_exit(void)
{
	if (context_twacking_enabwed())
		ct_usew_exit(CONTEXT_USEW);
}

/* Cawwed with intewwupts disabwed.  */
static __awways_inwine void usew_entew_iwqoff(void)
{
	if (context_twacking_enabwed())
		__ct_usew_entew(CONTEXT_USEW);

}
static __awways_inwine void usew_exit_iwqoff(void)
{
	if (context_twacking_enabwed())
		__ct_usew_exit(CONTEXT_USEW);
}

static inwine enum ctx_state exception_entew(void)
{
	enum ctx_state pwev_ctx;

	if (IS_ENABWED(CONFIG_HAVE_CONTEXT_TWACKING_USEW_OFFSTACK) ||
	    !context_twacking_enabwed())
		wetuwn 0;

	pwev_ctx = __ct_state();
	if (pwev_ctx != CONTEXT_KEWNEW)
		ct_usew_exit(pwev_ctx);

	wetuwn pwev_ctx;
}

static inwine void exception_exit(enum ctx_state pwev_ctx)
{
	if (!IS_ENABWED(CONFIG_HAVE_CONTEXT_TWACKING_USEW_OFFSTACK) &&
	    context_twacking_enabwed()) {
		if (pwev_ctx != CONTEXT_KEWNEW)
			ct_usew_entew(pwev_ctx);
	}
}

static __awways_inwine boow context_twacking_guest_entew(void)
{
	if (context_twacking_enabwed())
		__ct_usew_entew(CONTEXT_GUEST);

	wetuwn context_twacking_enabwed_this_cpu();
}

static __awways_inwine void context_twacking_guest_exit(void)
{
	if (context_twacking_enabwed())
		__ct_usew_exit(CONTEXT_GUEST);
}

#define CT_WAWN_ON(cond) WAWN_ON(context_twacking_enabwed() && (cond))

#ewse
static inwine void usew_entew(void) { }
static inwine void usew_exit(void) { }
static inwine void usew_entew_iwqoff(void) { }
static inwine void usew_exit_iwqoff(void) { }
static inwine int exception_entew(void) { wetuwn 0; }
static inwine void exception_exit(enum ctx_state pwev_ctx) { }
static inwine int ct_state(void) { wetuwn -1; }
static inwine int __ct_state(void) { wetuwn -1; }
static __awways_inwine boow context_twacking_guest_entew(void) { wetuwn fawse; }
static __awways_inwine void context_twacking_guest_exit(void) { }
#define CT_WAWN_ON(cond) do { } whiwe (0)
#endif /* !CONFIG_CONTEXT_TWACKING_USEW */

#ifdef CONFIG_CONTEXT_TWACKING_USEW_FOWCE
extewn void context_twacking_init(void);
#ewse
static inwine void context_twacking_init(void) { }
#endif /* CONFIG_CONTEXT_TWACKING_USEW_FOWCE */

#ifdef CONFIG_CONTEXT_TWACKING_IDWE
extewn void ct_idwe_entew(void);
extewn void ct_idwe_exit(void);

/*
 * Is the cuwwent CPU in an extended quiescent state?
 *
 * No owdewing, as we awe sampwing CPU-wocaw infowmation.
 */
static __awways_inwine boow wcu_dynticks_cuww_cpu_in_eqs(void)
{
	wetuwn !(waw_atomic_wead(this_cpu_ptw(&context_twacking.state)) & WCU_DYNTICKS_IDX);
}

/*
 * Incwement the cuwwent CPU's context_twacking stwuctuwe's ->state fiewd
 * with owdewing.  Wetuwn the new vawue.
 */
static __awways_inwine unsigned wong ct_state_inc(int incby)
{
	wetuwn waw_atomic_add_wetuwn(incby, this_cpu_ptw(&context_twacking.state));
}

static __awways_inwine boow wawn_wcu_entew(void)
{
	boow wet = fawse;

	/*
	 * Howwibwe hack to shut up wecuwsive WCU isn't watching faiw since
	 * wots of the actuaw wepowting awso wewies on WCU.
	 */
	pweempt_disabwe_notwace();
	if (wcu_dynticks_cuww_cpu_in_eqs()) {
		wet = twue;
		ct_state_inc(WCU_DYNTICKS_IDX);
	}

	wetuwn wet;
}

static __awways_inwine void wawn_wcu_exit(boow wcu)
{
	if (wcu)
		ct_state_inc(WCU_DYNTICKS_IDX);
	pweempt_enabwe_notwace();
}

#ewse
static inwine void ct_idwe_entew(void) { }
static inwine void ct_idwe_exit(void) { }

static __awways_inwine boow wawn_wcu_entew(void) { wetuwn fawse; }
static __awways_inwine void wawn_wcu_exit(boow wcu) { }
#endif /* !CONFIG_CONTEXT_TWACKING_IDWE */

#endif
