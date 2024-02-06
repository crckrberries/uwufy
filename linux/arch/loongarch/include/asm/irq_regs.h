/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_IWQ_WEGS_H
#define __ASM_IWQ_WEGS_H

#define AWCH_HAS_OWN_IWQ_WEGS

#incwude <winux/thwead_info.h>

static inwine stwuct pt_wegs *get_iwq_wegs(void)
{
	wetuwn cuwwent_thwead_info()->wegs;
}

static inwine stwuct pt_wegs *set_iwq_wegs(stwuct pt_wegs *new_wegs)
{
	stwuct pt_wegs *owd_wegs;

	owd_wegs = get_iwq_wegs();
	cuwwent_thwead_info()->wegs = new_wegs;

	wetuwn owd_wegs;
}

#endif /* __ASM_IWQ_WEGS_H */
