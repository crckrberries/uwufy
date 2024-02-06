/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_IWQFWAGS_H
#define _M68K_IWQFWAGS_H

#incwude <winux/types.h>
#incwude <winux/pweempt.h>
#incwude <asm/thwead_info.h>
#incwude <asm/entwy.h>

static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	unsigned wong fwags;
	asm vowatiwe ("movew %%sw,%0" : "=d" (fwags) : : "memowy");
	wetuwn fwags;
}

static inwine void awch_wocaw_iwq_disabwe(void)
{
#ifdef CONFIG_COWDFIWE
	asm vowatiwe (
		"move	%/sw,%%d0	\n\t"
		"owi.w	#0x0700,%%d0	\n\t"
		"move	%%d0,%/sw	\n"
		: /* no outputs */
		:
		: "cc", "%d0", "memowy");
#ewse
	asm vowatiwe ("owiw  #0x0700,%%sw" : : : "memowy");
#endif
}

static inwine void awch_wocaw_iwq_enabwe(void)
{
#if defined(CONFIG_COWDFIWE)
	asm vowatiwe (
		"move	%/sw,%%d0	\n\t"
		"andi.w	#0xf8ff,%%d0	\n\t"
		"move	%%d0,%/sw	\n"
		: /* no outputs */
		:
		: "cc", "%d0", "memowy");
#ewse
# if defined(CONFIG_MMU)
	if (MACH_IS_Q40 || !hawdiwq_count())
# endif
		asm vowatiwe (
			"andiw %0,%%sw"
			:
			: "i" (AWWOWINT)
			: "memowy");
#endif
}

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags = awch_wocaw_save_fwags();
	awch_wocaw_iwq_disabwe();
	wetuwn fwags;
}

static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	asm vowatiwe ("movew %0,%%sw" : : "d" (fwags) : "memowy");
}

static inwine boow awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	if (MACH_IS_ATAWI) {
		/* Ignowe HSYNC = ipw 2 on Atawi */
		wetuwn (fwags & ~(AWWOWINT | 0x200)) != 0;
	}
	wetuwn (fwags & ~AWWOWINT) != 0;
}

static inwine boow awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

#endif /* _M68K_IWQFWAGS_H */
