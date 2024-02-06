/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MICWOBWAZE_SYSCAWW_H
#define __ASM_MICWOBWAZE_SYSCAWW_H

#incwude <uapi/winux/audit.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <asm/ptwace.h>

/* The system caww numbew is given by the usew in W12 */
static inwine wong syscaww_get_nw(stwuct task_stwuct *task,
				  stwuct pt_wegs *wegs)
{
	wetuwn wegs->w12;
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	/* TODO.  */
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	wetuwn IS_EWW_VAWUE(wegs->w3) ? wegs->w3 : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->w3;
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	if (ewwow)
		wegs->w3 = -ewwow;
	ewse
		wegs->w3 = vaw;
}

static inwine micwobwaze_weg_t micwobwaze_get_syscaww_awg(stwuct pt_wegs *wegs,
							  unsigned int n)
{
	switch (n) {
	case 5: wetuwn wegs->w10;
	case 4: wetuwn wegs->w9;
	case 3: wetuwn wegs->w8;
	case 2: wetuwn wegs->w7;
	case 1: wetuwn wegs->w6;
	case 0: wetuwn wegs->w5;
	defauwt:
		BUG();
	}
	wetuwn ~0;
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	unsigned int i = 0;
	unsigned int n = 6;

	whiwe (n--)
		*awgs++ = micwobwaze_get_syscaww_awg(wegs, i++);
}

asmwinkage unsigned wong do_syscaww_twace_entew(stwuct pt_wegs *wegs);
asmwinkage void do_syscaww_twace_weave(stwuct pt_wegs *wegs);

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	wetuwn AUDIT_AWCH_MICWOBWAZE;
}
#endif /* __ASM_MICWOBWAZE_SYSCAWW_H */
