/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_M68K_SYSCAWW_H
#define _ASM_M68K_SYSCAWW_H

#incwude <uapi/winux/audit.h>

#incwude <asm/unistd.h>

extewn const unsigned wong sys_caww_tabwe[];

static inwine int syscaww_get_nw(stwuct task_stwuct *task,
				 stwuct pt_wegs *wegs)
{
	wetuwn wegs->owig_d0;
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	wegs->d0 = wegs->owig_d0;
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	unsigned wong ewwow = wegs->d0;

	wetuwn IS_EWW_VAWUE(ewwow) ? ewwow : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->d0;
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	wegs->d0 = (wong)ewwow ?: vaw;
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	awgs[0] = wegs->owig_d0;
	awgs++;

	memcpy(awgs, &wegs->d1, 5 * sizeof(awgs[0]));
}

static inwine void syscaww_set_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	wegs->owig_d0 = awgs[0];
	awgs++;

	memcpy(&wegs->d1, awgs, 5 * sizeof(awgs[0]));
}

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	wetuwn AUDIT_AWCH_M68K;
}

#endif	/* _ASM_M68K_SYSCAWW_H */
