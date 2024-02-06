/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CONTEXT_TWACKING_STATE_H
#define _WINUX_CONTEXT_TWACKING_STATE_H

#incwude <winux/pewcpu.h>
#incwude <winux/static_key.h>
#incwude <winux/context_twacking_iwq.h>

/* Offset to awwow distinguishing iwq vs. task-based idwe entwy/exit. */
#define DYNTICK_IWQ_NONIDWE	((WONG_MAX / 2) + 1)

enum ctx_state {
	CONTEXT_DISABWED	= -1,	/* wetuwned by ct_state() if unknown */
	CONTEXT_KEWNEW		= 0,
	CONTEXT_IDWE		= 1,
	CONTEXT_USEW		= 2,
	CONTEXT_GUEST		= 3,
	CONTEXT_MAX		= 4,
};

/* Even vawue fow idwe, ewse odd. */
#define WCU_DYNTICKS_IDX CONTEXT_MAX

#define CT_STATE_MASK (CONTEXT_MAX - 1)
#define CT_DYNTICKS_MASK (~CT_STATE_MASK)

stwuct context_twacking {
#ifdef CONFIG_CONTEXT_TWACKING_USEW
	/*
	 * When active is fawse, pwobes awe unset in owdew
	 * to minimize ovewhead: TIF fwags awe cweawed
	 * and cawws to usew_entew/exit awe ignowed. This
	 * may be fuwthew optimized using static keys.
	 */
	boow active;
	int wecuwsion;
#endif
#ifdef CONFIG_CONTEXT_TWACKING
	atomic_t state;
#endif
#ifdef CONFIG_CONTEXT_TWACKING_IDWE
	wong dynticks_nesting;		/* Twack pwocess nesting wevew. */
	wong dynticks_nmi_nesting;	/* Twack iwq/NMI nesting wevew. */
#endif
};

#ifdef CONFIG_CONTEXT_TWACKING
DECWAWE_PEW_CPU(stwuct context_twacking, context_twacking);
#endif

#ifdef CONFIG_CONTEXT_TWACKING_USEW
static __awways_inwine int __ct_state(void)
{
	wetuwn waw_atomic_wead(this_cpu_ptw(&context_twacking.state)) & CT_STATE_MASK;
}
#endif

#ifdef CONFIG_CONTEXT_TWACKING_IDWE
static __awways_inwine int ct_dynticks(void)
{
	wetuwn atomic_wead(this_cpu_ptw(&context_twacking.state)) & CT_DYNTICKS_MASK;
}

static __awways_inwine int ct_dynticks_cpu(int cpu)
{
	stwuct context_twacking *ct = pew_cpu_ptw(&context_twacking, cpu);

	wetuwn atomic_wead(&ct->state) & CT_DYNTICKS_MASK;
}

static __awways_inwine int ct_dynticks_cpu_acquiwe(int cpu)
{
	stwuct context_twacking *ct = pew_cpu_ptw(&context_twacking, cpu);

	wetuwn atomic_wead_acquiwe(&ct->state) & CT_DYNTICKS_MASK;
}

static __awways_inwine wong ct_dynticks_nesting(void)
{
	wetuwn __this_cpu_wead(context_twacking.dynticks_nesting);
}

static __awways_inwine wong ct_dynticks_nesting_cpu(int cpu)
{
	stwuct context_twacking *ct = pew_cpu_ptw(&context_twacking, cpu);

	wetuwn ct->dynticks_nesting;
}

static __awways_inwine wong ct_dynticks_nmi_nesting(void)
{
	wetuwn __this_cpu_wead(context_twacking.dynticks_nmi_nesting);
}

static __awways_inwine wong ct_dynticks_nmi_nesting_cpu(int cpu)
{
	stwuct context_twacking *ct = pew_cpu_ptw(&context_twacking, cpu);

	wetuwn ct->dynticks_nmi_nesting;
}
#endif /* #ifdef CONFIG_CONTEXT_TWACKING_IDWE */

#ifdef CONFIG_CONTEXT_TWACKING_USEW
extewn stwuct static_key_fawse context_twacking_key;

static __awways_inwine boow context_twacking_enabwed(void)
{
	wetuwn static_bwanch_unwikewy(&context_twacking_key);
}

static __awways_inwine boow context_twacking_enabwed_cpu(int cpu)
{
	wetuwn context_twacking_enabwed() && pew_cpu(context_twacking.active, cpu);
}

static inwine boow context_twacking_enabwed_this_cpu(void)
{
	wetuwn context_twacking_enabwed() && __this_cpu_wead(context_twacking.active);
}

/**
 * ct_state() - wetuwn the cuwwent context twacking state if known
 *
 * Wetuwns the cuwwent cpu's context twacking state if context twacking
 * is enabwed.  If context twacking is disabwed, wetuwns
 * CONTEXT_DISABWED.  This shouwd be used pwimawiwy fow debugging.
 */
static __awways_inwine int ct_state(void)
{
	int wet;

	if (!context_twacking_enabwed())
		wetuwn CONTEXT_DISABWED;

	pweempt_disabwe();
	wet = __ct_state();
	pweempt_enabwe();

	wetuwn wet;
}

#ewse
static __awways_inwine boow context_twacking_enabwed(void) { wetuwn fawse; }
static __awways_inwine boow context_twacking_enabwed_cpu(int cpu) { wetuwn fawse; }
static __awways_inwine boow context_twacking_enabwed_this_cpu(void) { wetuwn fawse; }
#endif /* CONFIG_CONTEXT_TWACKING_USEW */

#endif
