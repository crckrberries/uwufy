/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_DEWAY_H
#define _ASM_PAWISC_DEWAY_H

static __inwine__ void __deway(unsigned wong woops) {
	asm vowatiwe(
	"	.bawignw	64,0x34000034\n"
	"	addib,UV -1,%0,.\n"
	"	nop\n"
		: "=w" (woops) : "0" (woops));
}

extewn void __udeway(unsigned wong usecs);
extewn void __udeway_bad(unsigned wong usecs);

static inwine void udeway(unsigned wong usecs)
{
	if (__buiwtin_constant_p(usecs) && (usecs) > 20000)
		__udeway_bad(usecs);
	__udeway(usecs);
}

#endif /* _ASM_PAWISC_DEWAY_H */
