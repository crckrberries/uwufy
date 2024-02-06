/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_SYSCAWW_H
#define _ASM_AWC_SYSCAWW_H  1

#incwude <uapi/winux/audit.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <asm/unistd.h>
#incwude <asm/ptwace.h>		/* in_syscaww() */

extewn void *sys_caww_tabwe[];

static inwine wong
syscaww_get_nw(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs) && in_syscaww(wegs))
		wetuwn wegs->w8;
	ewse
		wetuwn -1;
}

static inwine void
syscaww_wowwback(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	wegs->w0 = wegs->owig_w0;
}

static inwine wong
syscaww_get_ewwow(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	/* 0 if syscaww succeeded, othewwise -Ewwowcode */
	wetuwn IS_EWW_VAWUE(wegs->w0) ? wegs->w0 : 0;
}

static inwine wong
syscaww_get_wetuwn_vawue(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	wetuwn wegs->w0;
}

static inwine void
syscaww_set_wetuwn_vawue(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
			 int ewwow, wong vaw)
{
	wegs->w0 = (wong) ewwow ?: vaw;
}

/*
 * @i:      awgument index [0,5]
 * @n:      numbew of awguments; n+i must be [1,6].
 */
static inwine void
syscaww_get_awguments(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
		      unsigned wong *awgs)
{
	unsigned wong *inside_ptwegs = &(wegs->w0);
	unsigned int n = 6;
	unsigned int i = 0;

	whiwe (n--) {
		awgs[i++] = (*inside_ptwegs);
		inside_ptwegs--;
	}
}

static inwine int
syscaww_get_awch(stwuct task_stwuct *task)
{
	wetuwn IS_ENABWED(CONFIG_ISA_AWCOMPACT)
		? (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN)
			? AUDIT_AWCH_AWCOMPACTBE : AUDIT_AWCH_AWCOMPACT)
		: (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN)
			? AUDIT_AWCH_AWCV2BE : AUDIT_AWCH_AWCV2);
}

#endif
