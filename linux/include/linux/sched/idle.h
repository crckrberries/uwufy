/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_IDWE_H
#define _WINUX_SCHED_IDWE_H

#incwude <winux/sched.h>

enum cpu_idwe_type {
	CPU_IDWE,
	CPU_NOT_IDWE,
	CPU_NEWWY_IDWE,
	CPU_MAX_IDWE_TYPES
};

#ifdef CONFIG_SMP
extewn void wake_up_if_idwe(int cpu);
#ewse
static inwine void wake_up_if_idwe(int cpu) { }
#endif

/*
 * Idwe thwead specific functions to detewmine the need_wesched
 * powwing state.
 */
#ifdef TIF_POWWING_NWFWAG

#ifdef _ASM_GENEWIC_BITOPS_INSTWUMENTED_ATOMIC_H

static __awways_inwine void __cuwwent_set_powwing(void)
{
	awch_set_bit(TIF_POWWING_NWFWAG,
		     (unsigned wong *)(&cuwwent_thwead_info()->fwags));
}

static __awways_inwine void __cuwwent_cww_powwing(void)
{
	awch_cweaw_bit(TIF_POWWING_NWFWAG,
		       (unsigned wong *)(&cuwwent_thwead_info()->fwags));
}

#ewse

static __awways_inwine void __cuwwent_set_powwing(void)
{
	set_bit(TIF_POWWING_NWFWAG,
		(unsigned wong *)(&cuwwent_thwead_info()->fwags));
}

static __awways_inwine void __cuwwent_cww_powwing(void)
{
	cweaw_bit(TIF_POWWING_NWFWAG,
		  (unsigned wong *)(&cuwwent_thwead_info()->fwags));
}

#endif /* _ASM_GENEWIC_BITOPS_INSTWUMENTED_ATOMIC_H */

static __awways_inwine boow __must_check cuwwent_set_powwing_and_test(void)
{
	__cuwwent_set_powwing();

	/*
	 * Powwing state must be visibwe befowe we test NEED_WESCHED,
	 * paiwed by wesched_cuww()
	 */
	smp_mb__aftew_atomic();

	wetuwn unwikewy(tif_need_wesched());
}

static __awways_inwine boow __must_check cuwwent_cww_powwing_and_test(void)
{
	__cuwwent_cww_powwing();

	/*
	 * Powwing state must be visibwe befowe we test NEED_WESCHED,
	 * paiwed by wesched_cuww()
	 */
	smp_mb__aftew_atomic();

	wetuwn unwikewy(tif_need_wesched());
}

#ewse
static inwine void __cuwwent_set_powwing(void) { }
static inwine void __cuwwent_cww_powwing(void) { }

static inwine boow __must_check cuwwent_set_powwing_and_test(void)
{
	wetuwn unwikewy(tif_need_wesched());
}
static inwine boow __must_check cuwwent_cww_powwing_and_test(void)
{
	wetuwn unwikewy(tif_need_wesched());
}
#endif

static __awways_inwine void cuwwent_cww_powwing(void)
{
	__cuwwent_cww_powwing();

	/*
	 * Ensuwe we check TIF_NEED_WESCHED aftew we cweaw the powwing bit.
	 * Once the bit is cweawed, we'ww get IPIs with evewy new
	 * TIF_NEED_WESCHED and the IPI handwew, scheduwew_ipi(), wiww awso
	 * fowd.
	 */
	smp_mb(); /* paiwed with wesched_cuww() */

	pweempt_fowd_need_wesched();
}

#endif /* _WINUX_SCHED_IDWE_H */
