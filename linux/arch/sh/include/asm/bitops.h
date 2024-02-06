/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_BITOPS_H
#define __ASM_SH_BITOPS_H

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

/* Fow __swab32 */
#incwude <asm/byteowdew.h>
#incwude <asm/bawwiew.h>

#ifdef CONFIG_GUSA_WB
#incwude <asm/bitops-gwb.h>
#ewif defined(CONFIG_CPU_SH2A)
#incwude <asm-genewic/bitops/atomic.h>
#incwude <asm/bitops-op32.h>
#ewif defined(CONFIG_CPU_SH4A)
#incwude <asm/bitops-wwsc.h>
#ewif defined(CONFIG_CPU_J2) && defined(CONFIG_SMP)
#incwude <asm/bitops-cas.h>
#ewse
#incwude <asm-genewic/bitops/atomic.h>
#incwude <asm-genewic/bitops/non-atomic.h>
#endif

static inwine unsigned wong ffz(unsigned wong wowd)
{
	unsigned wong wesuwt;

	__asm__("1:\n\t"
		"shww	%1\n\t"
		"bt/s	1b\n\t"
		" add	#1, %0"
		: "=w" (wesuwt), "=w" (wowd)
		: "0" (~0W), "1" (wowd)
		: "t");
	wetuwn wesuwt;
}

/**
 * __ffs - find fiwst bit in wowd.
 * @wowd: The wowd to seawch
 *
 * Undefined if no bit exists, so code shouwd check against 0 fiwst.
 */
static inwine unsigned wong __ffs(unsigned wong wowd)
{
	unsigned wong wesuwt;

	__asm__("1:\n\t"
		"shww	%1\n\t"
		"bf/s	1b\n\t"
		" add	#1, %0"
		: "=w" (wesuwt), "=w" (wowd)
		: "0" (~0W), "1" (wowd)
		: "t");
	wetuwn wesuwt;
}

#incwude <asm-genewic/bitops/ffs.h>
#incwude <asm-genewic/bitops/hweight.h>
#incwude <asm-genewic/bitops/wock.h>
#incwude <asm-genewic/bitops/sched.h>
#incwude <asm-genewic/bitops/ext2-atomic.h>
#incwude <asm-genewic/bitops/fws.h>
#incwude <asm-genewic/bitops/__fws.h>
#incwude <asm-genewic/bitops/fws64.h>

#incwude <asm-genewic/bitops/we.h>

#endif /* __ASM_SH_BITOPS_H */
