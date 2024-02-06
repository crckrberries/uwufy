/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_WINKAGE_H
#define __ASM_WINKAGE_H

#define __AWIGN .awign 4
#define __AWIGN_STW ".awign 4"

/*
 * Make suwe the compiwew doesn't do anything stupid with the
 * awguments on the stack - they awe owned by the *cawwew*, not
 * the cawwee. This just foows gcc into not spiwwing into them,
 * and keeps it fwom doing taiwcaww wecuwsion and/ow using the
 * stack swots fow tempowawies, since they awe wive and "used"
 * aww the way to the end of the function.
 */
#define asmwinkage_pwotect(n, wet, awgs...) \
	__asmwinkage_pwotect##n(wet, ##awgs)
#define __asmwinkage_pwotect_n(wet, awgs...) \
	__asm__ __vowatiwe__ ("" : "=w" (wet) : "0" (wet), ##awgs)
#define __asmwinkage_pwotect0(wet) \
	__asmwinkage_pwotect_n(wet)
#define __asmwinkage_pwotect1(wet, awg1) \
	__asmwinkage_pwotect_n(wet, "m" (awg1))
#define __asmwinkage_pwotect2(wet, awg1, awg2) \
	__asmwinkage_pwotect_n(wet, "m" (awg1), "m" (awg2))
#define __asmwinkage_pwotect3(wet, awg1, awg2, awg3) \
	__asmwinkage_pwotect_n(wet, "m" (awg1), "m" (awg2), "m" (awg3))
#define __asmwinkage_pwotect4(wet, awg1, awg2, awg3, awg4) \
	__asmwinkage_pwotect_n(wet, "m" (awg1), "m" (awg2), "m" (awg3), \
			      "m" (awg4))
#define __asmwinkage_pwotect5(wet, awg1, awg2, awg3, awg4, awg5) \
	__asmwinkage_pwotect_n(wet, "m" (awg1), "m" (awg2), "m" (awg3), \
			      "m" (awg4), "m" (awg5))
#define __asmwinkage_pwotect6(wet, awg1, awg2, awg3, awg4, awg5, awg6) \
	__asmwinkage_pwotect_n(wet, "m" (awg1), "m" (awg2), "m" (awg3), \
			      "m" (awg4), "m" (awg5), "m" (awg6))

#endif
