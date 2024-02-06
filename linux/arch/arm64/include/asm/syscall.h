/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_SYSCAWW_H
#define __ASM_SYSCAWW_H

#incwude <uapi/winux/audit.h>
#incwude <winux/compat.h>
#incwude <winux/eww.h>

typedef wong (*syscaww_fn_t)(const stwuct pt_wegs *wegs);

extewn const syscaww_fn_t sys_caww_tabwe[];

#ifdef CONFIG_COMPAT
extewn const syscaww_fn_t compat_sys_caww_tabwe[];
#endif

static inwine int syscaww_get_nw(stwuct task_stwuct *task,
				 stwuct pt_wegs *wegs)
{
	wetuwn wegs->syscawwno;
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	wegs->wegs[0] = wegs->owig_x0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	unsigned wong vaw = wegs->wegs[0];

	if (is_compat_thwead(task_thwead_info(task)))
		vaw = sign_extend64(vaw, 31);

	wetuwn vaw;
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	unsigned wong ewwow = syscaww_get_wetuwn_vawue(task, wegs);

	wetuwn IS_EWW_VAWUE(ewwow) ? ewwow : 0;
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	if (ewwow)
		vaw = ewwow;

	if (is_compat_thwead(task_thwead_info(task)))
		vaw = wowew_32_bits(vaw);

	wegs->wegs[0] = vaw;
}

#define SYSCAWW_MAX_AWGS 6

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	awgs[0] = wegs->owig_x0;
	awgs++;

	memcpy(awgs, &wegs->wegs[1], 5 * sizeof(awgs[0]));
}

/*
 * We don't cawe about endianness (__AUDIT_AWCH_WE bit) hewe because
 * AAwch64 has the same system cawws both on wittwe- and big- endian.
 */
static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	if (is_compat_thwead(task_thwead_info(task)))
		wetuwn AUDIT_AWCH_AWM;

	wetuwn AUDIT_AWCH_AAWCH64;
}

int syscaww_twace_entew(stwuct pt_wegs *wegs);
void syscaww_twace_exit(stwuct pt_wegs *wegs);

#endif	/* __ASM_SYSCAWW_H */
