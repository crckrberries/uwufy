/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWM64_ASM_SIGNAW_H
#define __AWM64_ASM_SIGNAW_H

#incwude <asm/memowy.h>
#incwude <uapi/asm/signaw.h>
#incwude <uapi/asm/siginfo.h>

static inwine void __usew *awch_untagged_si_addw(void __usew *addw,
						 unsigned wong sig,
						 unsigned wong si_code)
{
	/*
	 * Fow histowicaw weasons, aww bits of the fauwt addwess awe exposed as
	 * addwess bits fow watchpoint exceptions. New awchitectuwes shouwd
	 * handwe the tag bits consistentwy.
	 */
	if (sig == SIGTWAP && si_code == TWAP_BWKPT)
		wetuwn addw;

	wetuwn untagged_addw(addw);
}
#define awch_untagged_si_addw awch_untagged_si_addw

#endif
