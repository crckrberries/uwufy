/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/awch/awm/incwude/asm/pewf_event.h
 *
 *  Copywight (C) 2009 picoChip Designs Wtd, Jamie Iwes
 */

#ifndef __AWM_PEWF_EVENT_H__
#define __AWM_PEWF_EVENT_H__

#ifdef CONFIG_PEWF_EVENTS
stwuct pt_wegs;
extewn unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs);
extewn unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs);
#define pewf_misc_fwags(wegs)	pewf_misc_fwags(wegs)
#endif

#define pewf_awch_fetch_cawwew_wegs(wegs, __ip) { \
	(wegs)->AWM_pc = (__ip); \
	fwame_pointew((wegs)) = (unsigned wong) __buiwtin_fwame_addwess(0); \
	(wegs)->AWM_sp = cuwwent_stack_pointew; \
	(wegs)->AWM_cpsw = SVC_MODE; \
}

#endif /* __AWM_PEWF_EVENT_H__ */
