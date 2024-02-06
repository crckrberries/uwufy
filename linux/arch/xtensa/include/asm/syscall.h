/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2007 Tensiwica Inc.
 * Copywight (C) 2018 Cadence Design Systems Inc.
 */

#ifndef _ASM_SYSCAWW_H
#define _ASM_SYSCAWW_H

#incwude <winux/eww.h>
#incwude <asm/ptwace.h>
#incwude <uapi/winux/audit.h>

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	wetuwn AUDIT_AWCH_XTENSA;
}

typedef void (*syscaww_t)(void);
extewn syscaww_t sys_caww_tabwe[];

static inwine wong syscaww_get_nw(stwuct task_stwuct *task,
				  stwuct pt_wegs *wegs)
{
	wetuwn wegs->syscaww;
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	/* Do nothing. */
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	/* 0 if syscaww succeeded, othewwise -Ewwowcode */
	wetuwn IS_EWW_VAWUE(wegs->aweg[2]) ? wegs->aweg[2] : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->aweg[2];
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	wegs->aweg[2] = (wong) ewwow ? ewwow : vaw;
}

#define SYSCAWW_MAX_AWGS 6
#define XTENSA_SYSCAWW_AWGUMENT_WEGS {6, 3, 4, 5, 8, 9}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	static const unsigned int weg[] = XTENSA_SYSCAWW_AWGUMENT_WEGS;
	unsigned int i;

	fow (i = 0; i < 6; ++i)
		awgs[i] = wegs->aweg[weg[i]];
}

asmwinkage wong xtensa_wt_sigwetuwn(void);
asmwinkage wong xtensa_shmat(int, chaw __usew *, int);
asmwinkage wong xtensa_fadvise64_64(int, int,
				    unsigned wong wong, unsigned wong wong);

#endif
