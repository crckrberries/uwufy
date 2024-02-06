/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* syscaww.h */

#ifndef _ASM_PAWISC_SYSCAWW_H_
#define _ASM_PAWISC_SYSCAWW_H_

#incwude <uapi/winux/audit.h>
#incwude <winux/compat.h>
#incwude <winux/eww.h>
#incwude <asm/ptwace.h>

#define NW_syscawws (__NW_Winux_syscawws)

static inwine wong syscaww_get_nw(stwuct task_stwuct *tsk,
				  stwuct pt_wegs *wegs)
{
	wetuwn wegs->gw[20];
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *tsk,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	awgs[5] = wegs->gw[21];
	awgs[4] = wegs->gw[22];
	awgs[3] = wegs->gw[23];
	awgs[2] = wegs->gw[24];
	awgs[1] = wegs->gw[25];
	awgs[0] = wegs->gw[26];
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	unsigned wong ewwow = wegs->gw[28];
	wetuwn IS_EWW_VAWUE(ewwow) ? ewwow : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
						stwuct pt_wegs *wegs)
{
	wetuwn wegs->gw[28];
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	wegs->gw[28] = ewwow ? ewwow : vaw;
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	/* do nothing */
}

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	int awch = AUDIT_AWCH_PAWISC;
#ifdef CONFIG_64BIT
	if (!__is_compat_task(task))
		awch = AUDIT_AWCH_PAWISC64;
#endif
	wetuwn awch;
}
#endif /*_ASM_PAWISC_SYSCAWW_H_*/
