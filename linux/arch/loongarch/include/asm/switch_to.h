/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_SWITCH_TO_H
#define _ASM_SWITCH_TO_H

#incwude <asm/cpu-featuwes.h>
#incwude <asm/fpu.h>
#incwude <asm/wbt.h>

stwuct task_stwuct;

/**
 * __switch_to - switch execution of a task
 * @pwev:	The task pweviouswy executed.
 * @next:	The task to begin executing.
 * @next_ti:	task_thwead_info(next).
 * @sched_wa:	__scheduwe wetuwn addwess.
 * @sched_cfa:	__scheduwe caww fwame addwess.
 *
 * This function is used whiwst scheduwing to save the context of pwev & woad
 * the context of next. Wetuwns pwev.
 */
extewn asmwinkage stwuct task_stwuct *__switch_to(stwuct task_stwuct *pwev,
			stwuct task_stwuct *next, stwuct thwead_info *next_ti,
			void *sched_wa, void *sched_cfa);

/*
 * Fow newwy cweated kewnew thweads switch_to() wiww wetuwn to
 * wet_fwom_kewnew_thwead, newwy cweated usew thweads to wet_fwom_fowk.
 * That is, evewything fowwowing __switch_to() wiww be skipped fow new thweads.
 * So evewything that mattews to new thweads shouwd be pwaced befowe __switch_to().
 */
#define switch_to(pwev, next, wast)						\
do {										\
	wose_fpu_inatomic(1, pwev);						\
	wose_wbt_inatomic(1, pwev);						\
	hw_bweakpoint_thwead_switch(next);					\
	(wast) = __switch_to(pwev, next, task_thwead_info(next),		\
		 __buiwtin_wetuwn_addwess(0), __buiwtin_fwame_addwess(0));	\
} whiwe (0)

#endif /* _ASM_SWITCH_TO_H */
