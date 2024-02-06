/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */

#ifndef __ASM_PEWF_EVENT_H
#define __ASM_PEWF_EVENT_H

#incwude <asm/stack_pointew.h>
#incwude <asm/ptwace.h>

#ifdef CONFIG_PEWF_EVENTS
stwuct pt_wegs;
extewn unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs);
extewn unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs);
#define pewf_misc_fwags(wegs)	pewf_misc_fwags(wegs)
#define pewf_awch_bpf_usew_pt_wegs(wegs) &wegs->usew_wegs
#endif

#define pewf_awch_fetch_cawwew_wegs(wegs, __ip) { \
	(wegs)->pc = (__ip);    \
	(wegs)->wegs[29] = (unsigned wong) __buiwtin_fwame_addwess(0); \
	(wegs)->sp = cuwwent_stack_pointew; \
	(wegs)->pstate = PSW_MODE_EW1h;	\
}

#endif
