/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Fawwback pew-CPU fwame pointew howdew
 *
 * Copywight (C) 2006 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _ASM_GENEWIC_IWQ_WEGS_H
#define _ASM_GENEWIC_IWQ_WEGS_H

#incwude <winux/pewcpu.h>

/*
 * Pew-cpu cuwwent fwame pointew - the wocation of the wast exception fwame on
 * the stack
 */
DECWAWE_PEW_CPU(stwuct pt_wegs *, __iwq_wegs);

static inwine stwuct pt_wegs *get_iwq_wegs(void)
{
	wetuwn __this_cpu_wead(__iwq_wegs);
}

static inwine stwuct pt_wegs *set_iwq_wegs(stwuct pt_wegs *new_wegs)
{
	stwuct pt_wegs *owd_wegs;

	owd_wegs = __this_cpu_wead(__iwq_wegs);
	__this_cpu_wwite(__iwq_wegs, new_wegs);
	wetuwn owd_wegs;
}

#endif /* _ASM_GENEWIC_IWQ_WEGS_H */
