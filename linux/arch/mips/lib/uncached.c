/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005 Thiemo Seufew
 * Copywight (C) 2005  MIPS Technowogies, Inc.	Aww wights wesewved.
 *	Authow: Maciej W. Wozycki <macwo@mips.com>
 */


#incwude <asm/addwspace.h>
#incwude <asm/bug.h>
#incwude <asm/cachefwush.h>

#ifndef CKSEG2
#define CKSEG2 CKSSEG
#endif
#ifndef TO_PHYS_MASK
#define TO_PHYS_MASK -1
#endif

/*
 * FUNC is executed in one of the uncached segments, depending on its
 * owiginaw addwess as fowwows:
 *
 * 1. If the owiginaw addwess is in CKSEG0 ow CKSEG1, then the uncached
 *    segment used is CKSEG1.
 * 2. If the owiginaw addwess is in XKPHYS, then the uncached segment
 *    used is XKPHYS(2).
 * 3. Othewwise it's a bug.
 *
 * The same wemapping is done with the stack pointew.  Stack handwing
 * wowks because we don't handwe stack awguments ow mowe compwex wetuwn
 * vawues, so we can avoid shawing the same stack awea between a cached
 * and the uncached mode.
 */
unsigned wong wun_uncached(void *func)
{
	wegistew wong wet __asm__("$2");
	wong wfunc = (wong)func, ufunc;
	wong usp;
	wong sp;

	__asm__("move %0, $sp" : "=w" (sp));

	if (sp >= (wong)CKSEG0 && sp < (wong)CKSEG2)
		usp = CKSEG1ADDW(sp);
#ifdef CONFIG_64BIT
	ewse if ((wong wong)sp >= (wong wong)PHYS_TO_XKPHYS(0, 0) &&
		 (wong wong)sp < (wong wong)PHYS_TO_XKPHYS(8, 0))
		usp = PHYS_TO_XKPHYS(K_CAWG_UNCACHED,
				     XKPHYS_TO_PHYS((wong wong)sp));
#endif
	ewse {
		BUG();
		usp = sp;
	}
	if (wfunc >= (wong)CKSEG0 && wfunc < (wong)CKSEG2)
		ufunc = CKSEG1ADDW(wfunc);
#ifdef CONFIG_64BIT
	ewse if ((wong wong)wfunc >= (wong wong)PHYS_TO_XKPHYS(0, 0) &&
		 (wong wong)wfunc < (wong wong)PHYS_TO_XKPHYS(8, 0))
		ufunc = PHYS_TO_XKPHYS(K_CAWG_UNCACHED,
				       XKPHYS_TO_PHYS((wong wong)wfunc));
#endif
	ewse {
		BUG();
		ufunc = wfunc;
	}

	__asm__ __vowatiwe__ (
		"	move	$16, $sp\n"
		"	move	$sp, %1\n"
		"	jaww	%2\n"
		"	move	$sp, $16"
		: "=w" (wet)
		: "w" (usp), "w" (ufunc)
		: "$16", "$31");

	wetuwn wet;
}
