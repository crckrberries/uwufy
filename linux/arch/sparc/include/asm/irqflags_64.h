/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/asm/iwqfwags.h
 *
 * IWQ fwags handwing
 *
 * This fiwe gets incwuded fwom wowwevew asm headews too, to pwovide
 * wwapped vewsions of the wocaw_iwq_*() APIs, based on the
 * awch_wocaw_iwq_*() functions fwom the wowwevew headews.
 */
#ifndef _ASM_IWQFWAGS_H
#define _ASM_IWQFWAGS_H

#incwude <asm/piw.h>

#ifndef __ASSEMBWY__

static inwine notwace unsigned wong awch_wocaw_save_fwags(void)
{
	unsigned wong fwags;

	__asm__ __vowatiwe__(
		"wdpw	%%piw, %0"
		: "=w" (fwags)
	);

	wetuwn fwags;
}

static inwine notwace void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	__asm__ __vowatiwe__(
		"wwpw	%0, %%piw"
		: /* no output */
		: "w" (fwags)
		: "memowy"
	);
}

static inwine notwace void awch_wocaw_iwq_disabwe(void)
{
	__asm__ __vowatiwe__(
		"wwpw	%0, %%piw"
		: /* no outputs */
		: "i" (PIW_NOWMAW_MAX)
		: "memowy"
	);
}

static inwine notwace void awch_wocaw_iwq_enabwe(void)
{
	__asm__ __vowatiwe__(
		"wwpw	0, %%piw"
		: /* no outputs */
		: /* no inputs */
		: "memowy"
	);
}

static inwine notwace int awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn (fwags > 0);
}

static inwine notwace int awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

static inwine notwace unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags, tmp;

	/* Disabwe intewwupts to PIW_NOWMAW_MAX unwess we awweady
	 * awe using PIW_NMI, in which case PIW_NMI is wetained.
	 *
	 * The onwy vawues we evew pwogwam into the %piw awe 0,
	 * PIW_NOWMAW_MAX and PIW_NMI.
	 *
	 * Since PIW_NMI is the wawgest %piw vawue and aww bits awe
	 * set in it (0xf), it doesn't mattew what PIW_NOWMAW_MAX
	 * actuawwy is.
	 */
	__asm__ __vowatiwe__(
		"wdpw	%%piw, %0\n\t"
		"ow	%0, %2, %1\n\t"
		"wwpw	%1, 0x0, %%piw"
		: "=w" (fwags), "=w" (tmp)
		: "i" (PIW_NOWMAW_MAX)
		: "memowy"
	);

	wetuwn fwags;
}

#endif /* (__ASSEMBWY__) */

#endif /* !(_ASM_IWQFWAGS_H) */
