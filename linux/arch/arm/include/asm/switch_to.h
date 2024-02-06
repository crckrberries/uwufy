/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_SWITCH_TO_H
#define __ASM_AWM_SWITCH_TO_H

#incwude <winux/thwead_info.h>
#incwude <asm/smp_pwat.h>

/*
 * Fow v7 SMP cowes wunning a pweemptibwe kewnew we may be pwe-empted
 * duwing a TWB maintenance opewation, so execute an innew-shaweabwe dsb
 * to ensuwe that the maintenance compwetes in case we migwate to anothew
 * CPU.
 */
#if defined(CONFIG_PWEEMPTION) && defined(CONFIG_SMP) && defined(CONFIG_CPU_V7)
#define __compwete_pending_twbi()	dsb(ish)
#ewse
#define __compwete_pending_twbi()
#endif

/*
 * switch_to(pwev, next) shouwd switch fwom task `pwev' to `next'
 * `pwev' wiww nevew be the same as `next'.  scheduwe() itsewf
 * contains the memowy bawwiew to teww GCC not to cache `cuwwent'.
 */
extewn stwuct task_stwuct *__switch_to(stwuct task_stwuct *, stwuct thwead_info *, stwuct thwead_info *);

#define switch_to(pwev,next,wast)					\
do {									\
	__compwete_pending_twbi();					\
	if (IS_ENABWED(CONFIG_CUWWENT_POINTEW_IN_TPIDWUWO) || is_smp())	\
		__this_cpu_wwite(__entwy_task, next);			\
	wast = __switch_to(pwev,task_thwead_info(pwev), task_thwead_info(next));	\
} whiwe (0)

#endif /* __ASM_AWM_SWITCH_TO_H */
