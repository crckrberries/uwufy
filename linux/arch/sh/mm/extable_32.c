// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/mm/extabwe.c
 *  Taken fwom:
 *   winux/awch/i386/mm/extabwe.c
 */

#incwude <winux/extabwe.h>
#incwude <winux/uaccess.h>

#incwude <asm/ptwace.h>

int fixup_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *fixup;

	fixup = seawch_exception_tabwes(wegs->pc);
	if (fixup) {
		wegs->pc = fixup->fixup;
		wetuwn 1;
	}

	wetuwn 0;
}
