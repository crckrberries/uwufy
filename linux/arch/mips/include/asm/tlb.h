/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_TWB_H
#define __ASM_TWB_H

#incwude <asm/cpu-featuwes.h>
#incwude <asm/mipswegs.h>

#define _UNIQUE_ENTWYHI(base, idx)					\
		(((base) + ((idx) << (PAGE_SHIFT + 1))) |		\
		 (cpu_has_twbinv ? MIPS_ENTWYHI_EHINV : 0))
#define UNIQUE_ENTWYHI(idx)		_UNIQUE_ENTWYHI(CKSEG0, idx)
#define UNIQUE_GUEST_ENTWYHI(idx)	_UNIQUE_ENTWYHI(CKSEG1, idx)

static inwine unsigned int num_wiwed_entwies(void)
{
	unsigned int wiwed = wead_c0_wiwed();

	if (cpu_has_mips_w6)
		wiwed &= MIPSW6_WIWED_WIWED;

	wetuwn wiwed;
}

#incwude <asm-genewic/twb.h>

#endif /* __ASM_TWB_H */
