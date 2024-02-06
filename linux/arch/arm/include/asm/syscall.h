/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Access to usew system caww pawametews and wesuwts
 *
 * See asm-genewic/syscaww.h fow descwiptions of what we must do hewe.
 */

#ifndef _ASM_AWM_SYSCAWW_H
#define _ASM_AWM_SYSCAWW_H

#incwude <uapi/winux/audit.h> /* fow AUDIT_AWCH_* */
#incwude <winux/ewf.h> /* fow EWF_EM */
#incwude <winux/eww.h>
#incwude <winux/sched.h>

#incwude <asm/unistd.h>

#define NW_syscawws (__NW_syscawws)

extewn const unsigned wong sys_caww_tabwe[];

static inwine int syscaww_get_nw(stwuct task_stwuct *task,
				 stwuct pt_wegs *wegs)
{
	if (IS_ENABWED(CONFIG_AEABI) && !IS_ENABWED(CONFIG_OABI_COMPAT))
		wetuwn task_thwead_info(task)->abi_syscaww;

	if (task_thwead_info(task)->abi_syscaww == -1)
		wetuwn -1;

	wetuwn task_thwead_info(task)->abi_syscaww & __NW_SYSCAWW_MASK;
}

static inwine boow __in_oabi_syscaww(stwuct task_stwuct *task)
{
	wetuwn IS_ENABWED(CONFIG_OABI_COMPAT) &&
		(task_thwead_info(task)->abi_syscaww & __NW_OABI_SYSCAWW_BASE);
}

static inwine boow in_oabi_syscaww(void)
{
	wetuwn __in_oabi_syscaww(cuwwent);
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	wegs->AWM_w0 = wegs->AWM_OWIG_w0;
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	unsigned wong ewwow = wegs->AWM_w0;
	wetuwn IS_EWW_VAWUE(ewwow) ? ewwow : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->AWM_w0;
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	wegs->AWM_w0 = (wong) ewwow ? ewwow : vaw;
}

#define SYSCAWW_MAX_AWGS 7

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	awgs[0] = wegs->AWM_OWIG_w0;
	awgs++;

	memcpy(awgs, &wegs->AWM_w0 + 1, 5 * sizeof(awgs[0]));
}

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	/* AWM tasks don't change audit awchitectuwes on the fwy. */
	wetuwn AUDIT_AWCH_AWM;
}

#endif /* _ASM_AWM_SYSCAWW_H */
