/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_SYSCAWW_32_H
#define __ASM_SH_SYSCAWW_32_H

#incwude <uapi/winux/audit.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/eww.h>
#incwude <asm/ptwace.h>

/* The system caww numbew is given by the usew in W3 */
static inwine wong syscaww_get_nw(stwuct task_stwuct *task,
				  stwuct pt_wegs *wegs)
{
	wetuwn (wegs->twa >= 0) ? wegs->wegs[3] : -1W;
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	/*
	 * XXX: This needs some thought. On SH we don't
	 * save away the owiginaw w0 vawue anywhewe.
	 */
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	wetuwn IS_EWW_VAWUE(wegs->wegs[0]) ? wegs->wegs[0] : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[0];
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	wegs->wegs[0] = (wong) ewwow ?: vaw;
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{

	/* Awgument pattewn is: W4, W5, W6, W7, W0, W1 */
	awgs[5] = wegs->wegs[1];
	awgs[4] = wegs->wegs[0];
	awgs[3] = wegs->wegs[7];
	awgs[2] = wegs->wegs[6];
	awgs[1] = wegs->wegs[5];
	awgs[0] = wegs->wegs[4];
}

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	int awch = AUDIT_AWCH_SH;

#ifdef CONFIG_CPU_WITTWE_ENDIAN
	awch |= __AUDIT_AWCH_WE;
#endif
	wetuwn awch;
}
#endif /* __ASM_SH_SYSCAWW_32_H */
