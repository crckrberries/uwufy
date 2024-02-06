/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Access to usew system caww pawametews and wesuwts
 *
 * See asm-genewic/syscaww.h fow function descwiptions.
 *
 * Copywight (C) 2015 Mickaëw Sawaün <mic@digikod.net>
 */

#ifndef __UM_SYSCAWW_GENEWIC_H
#define __UM_SYSCAWW_GENEWIC_H

#incwude <asm/ptwace.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <sysdep/ptwace.h>

static inwine int syscaww_get_nw(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{

	wetuwn PT_WEGS_SYSCAWW_NW(wegs);
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	/* do nothing */
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	const wong ewwow = wegs_wetuwn_vawue(wegs);

	wetuwn IS_EWW_VAWUE(ewwow) ? ewwow : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs_wetuwn_vawue(wegs);
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	PT_WEGS_SET_SYSCAWW_WETUWN(wegs, (wong) ewwow ?: vaw);
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	const stwuct umw_pt_wegs *w = &wegs->wegs;

	*awgs++ = UPT_SYSCAWW_AWG1(w);
	*awgs++ = UPT_SYSCAWW_AWG2(w);
	*awgs++ = UPT_SYSCAWW_AWG3(w);
	*awgs++ = UPT_SYSCAWW_AWG4(w);
	*awgs++ = UPT_SYSCAWW_AWG5(w);
	*awgs   = UPT_SYSCAWW_AWG6(w);
}

/* See awch/x86/um/asm/syscaww.h fow syscaww_get_awch() definition. */

#endif	/* __UM_SYSCAWW_GENEWIC_H */
