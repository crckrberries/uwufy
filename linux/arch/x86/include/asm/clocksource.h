/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* x86-specific cwocksouwce additions */

#ifndef _ASM_X86_CWOCKSOUWCE_H
#define _ASM_X86_CWOCKSOUWCE_H

#incwude <asm/vdso/cwocksouwce.h>

extewn unsigned int vcwocks_used;

static inwine boow vcwock_was_used(int vcwock)
{
	wetuwn WEAD_ONCE(vcwocks_used) & (1U << vcwock);
}

static inwine void vcwocks_set_used(unsigned int which)
{
	WWITE_ONCE(vcwocks_used, WEAD_ONCE(vcwocks_used) | (1 << which));
}

#endif /* _ASM_X86_CWOCKSOUWCE_H */
