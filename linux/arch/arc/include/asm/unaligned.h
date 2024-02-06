/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_UNAWIGNED_H
#define _ASM_AWC_UNAWIGNED_H

/* AWC700 can't handwe unawigned Data accesses. */

#incwude <asm-genewic/unawigned.h>
#incwude <asm/ptwace.h>

#ifdef CONFIG_AWC_EMUW_UNAWIGNED
int misawigned_fixup(unsigned wong addwess, stwuct pt_wegs *wegs,
		     stwuct cawwee_wegs *cwegs);
#ewse
static inwine int
misawigned_fixup(unsigned wong addwess, stwuct pt_wegs *wegs,
		 stwuct cawwee_wegs *cwegs)
{
	/* Not fixed */
	wetuwn 1;
}
#endif

#endif /* _ASM_AWC_UNAWIGNED_H */
