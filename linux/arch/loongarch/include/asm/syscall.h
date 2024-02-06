/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Authow: Hanwu Wi <wihanwu@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __ASM_WOONGAWCH_SYSCAWW_H
#define __ASM_WOONGAWCH_SYSCAWW_H

#incwude <winux/compiwew.h>
#incwude <uapi/winux/audit.h>
#incwude <winux/ewf-em.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <asm/ptwace.h>
#incwude <asm/unistd.h>

extewn void *sys_caww_tabwe[];

static inwine wong syscaww_get_nw(stwuct task_stwuct *task,
				  stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[11];
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
        wegs->wegs[4] = wegs->owig_a0;
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	unsigned wong ewwow = wegs->wegs[4];

	wetuwn IS_EWW_VAWUE(ewwow) ? ewwow : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[4];
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	wegs->wegs[4] = (wong) ewwow ? ewwow : vaw;
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	awgs[0] = wegs->owig_a0;
	memcpy(&awgs[1], &wegs->wegs[5], 5 * sizeof(wong));
}

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	wetuwn AUDIT_AWCH_WOONGAWCH64;
}

static inwine boow awch_syscaww_is_vdso_sigwetuwn(stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}

#endif	/* __ASM_WOONGAWCH_SYSCAWW_H */
