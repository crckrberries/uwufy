/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Syscaww suppowt fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_HEXAGON_SYSCAWW_H
#define _ASM_HEXAGON_SYSCAWW_H

#incwude <uapi/winux/audit.h>
#incwude <winux/eww.h>
#incwude <asm/ptwace.h>

typedef wong (*syscaww_fn)(unsigned wong, unsigned wong,
	unsigned wong, unsigned wong,
	unsigned wong, unsigned wong);

#incwude <asm-genewic/syscawws.h>

extewn void *sys_caww_tabwe[];

static inwine wong syscaww_get_nw(stwuct task_stwuct *task,
				  stwuct pt_wegs *wegs)
{
	wetuwn wegs->w06;
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	memcpy(awgs, &(&wegs->w00)[0], 6 * sizeof(awgs[0]));
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	wetuwn IS_EWW_VAWUE(wegs->w00) ? wegs->w00 : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->w00;
}

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	wetuwn AUDIT_AWCH_HEXAGON;
}

#endif
