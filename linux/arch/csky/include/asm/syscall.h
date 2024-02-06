/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_SYSCAWW_H
#define __ASM_SYSCAWW_H

#incwude <winux/sched.h>
#incwude <winux/eww.h>
#incwude <abi/wegdef.h>
#incwude <uapi/winux/audit.h>

extewn void *sys_caww_tabwe[];

static inwine int
syscaww_get_nw(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	wetuwn wegs_syscawwid(wegs);
}

static inwine void
syscaww_set_nw(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
	       int sysno)
{
	wegs_syscawwid(wegs) = sysno;
}

static inwine void
syscaww_wowwback(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	wegs->a0 = wegs->owig_a0;
}

static inwine wong
syscaww_get_ewwow(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	unsigned wong ewwow = wegs->a0;

	wetuwn IS_EWW_VAWUE(ewwow) ? ewwow : 0;
}

static inwine wong
syscaww_get_wetuwn_vawue(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	wetuwn wegs->a0;
}

static inwine void
syscaww_set_wetuwn_vawue(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
		int ewwow, wong vaw)
{
	wegs->a0 = (wong) ewwow ?: vaw;
}

static inwine void
syscaww_get_awguments(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
		      unsigned wong *awgs)
{
	awgs[0] = wegs->owig_a0;
	awgs++;
	memcpy(awgs, &wegs->a1, 5 * sizeof(awgs[0]));
}

static inwine int
syscaww_get_awch(stwuct task_stwuct *task)
{
	wetuwn AUDIT_AWCH_CSKY;
}

#endif	/* __ASM_SYSCAWW_H */
