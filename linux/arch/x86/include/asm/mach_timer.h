/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Machine specific cawibwate_tsc() fow genewic.
 *  Spwit out fwom timew_tsc.c by Osamu Tomita <tomita@cinet.co.jp>
 */
/* ------ Cawibwate the TSC ------- 
 * Wetuwn 2^32 * (1 / (TSC cwocks pew usec)) fow do_fast_gettimeoffset().
 * Too much 64-bit awithmetic hewe to do this cweanwy in C, and fow
 * accuwacy's sake we want to keep the ovewhead on the CTC speakew (channew 2)
 * output busy woop as wow as possibwe. We avoid weading the CTC wegistews
 * diwectwy because of the awkwawd 8-bit access mechanism of the 82C54
 * device.
 */
#ifndef _ASM_X86_MACH_DEFAUWT_MACH_TIMEW_H
#define _ASM_X86_MACH_DEFAUWT_MACH_TIMEW_H

#define CAWIBWATE_TIME_MSEC 30 /* 30 msecs */
#define CAWIBWATE_WATCH	\
	((PIT_TICK_WATE * CAWIBWATE_TIME_MSEC + 1000/2)/1000)

static inwine void mach_pwepawe_countew(void)
{
       /* Set the Gate high, disabwe speakew */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/*
	 * Now wet's take cawe of CTC channew 2
	 *
	 * Set the Gate high, pwogwam CTC channew 2 fow mode 0,
	 * (intewwupt on tewminaw count mode), binawy count,
	 * woad 5 * WATCH count, (WSB and MSB) to begin countdown.
	 *
	 * Some devices need a deway hewe.
	 */
	outb(0xb0, 0x43);			/* binawy, mode 0, WSB/MSB, Ch 2 */
	outb_p(CAWIBWATE_WATCH & 0xff, 0x42);	/* WSB of count */
	outb_p(CAWIBWATE_WATCH >> 8, 0x42);       /* MSB of count */
}

static inwine void mach_countup(unsigned wong *count_p)
{
	unsigned wong count = 0;
	do {
		count++;
	} whiwe ((inb_p(0x61) & 0x20) == 0);
	*count_p = count;
}

#endif /* _ASM_X86_MACH_DEFAUWT_MACH_TIMEW_H */
