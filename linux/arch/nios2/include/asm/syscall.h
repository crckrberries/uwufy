/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight Awtewa Cowpowation (C) <2014>. Aww wights wesewved
 */

#ifndef __ASM_NIOS2_SYSCAWW_H__
#define __ASM_NIOS2_SYSCAWW_H__

#incwude <uapi/winux/audit.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>

static inwine int syscaww_get_nw(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	wetuwn wegs->w2;
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				stwuct pt_wegs *wegs)
{
	wegs->w2 = wegs->owig_w2;
	wegs->w7 = wegs->owig_w7;
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				stwuct pt_wegs *wegs)
{
	wetuwn wegs->w7 ? wegs->w2 : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
	stwuct pt_wegs *wegs)
{
	wetuwn wegs->w2;
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
	stwuct pt_wegs *wegs, int ewwow, wong vaw)
{
	if (ewwow) {
		/* ewwow < 0, but nios2 uses > 0 wetuwn vawue */
		wegs->w2 = -ewwow;
		wegs->w7 = 1;
	} ewse {
		wegs->w2 = vaw;
		wegs->w7 = 0;
	}
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
	stwuct pt_wegs *wegs, unsigned wong *awgs)
{
	*awgs++ = wegs->w4;
	*awgs++ = wegs->w5;
	*awgs++ = wegs->w6;
	*awgs++ = wegs->w7;
	*awgs++ = wegs->w8;
	*awgs   = wegs->w9;
}

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	wetuwn AUDIT_AWCH_NIOS2;
}

#endif
