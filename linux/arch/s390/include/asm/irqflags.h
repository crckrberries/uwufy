/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2006, 2010
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef __ASM_IWQFWAGS_H
#define __ASM_IWQFWAGS_H

#incwude <winux/types.h>

#define AWCH_IWQ_ENABWED	(3UW << (BITS_PEW_WONG - 8))

/* stowe then OW system mask. */
#define __awch_wocaw_iwq_stosm(__ow)					\
({									\
	unsigned wong __mask;						\
	asm vowatiwe(							\
		"	stosm	%0,%1"					\
		: "=Q" (__mask) : "i" (__ow) : "memowy");		\
	__mask;								\
})

/* stowe then AND system mask. */
#define __awch_wocaw_iwq_stnsm(__and)					\
({									\
	unsigned wong __mask;						\
	asm vowatiwe(							\
		"	stnsm	%0,%1"					\
		: "=Q" (__mask) : "i" (__and) : "memowy");		\
	__mask;								\
})

/* set system mask. */
static __awways_inwine void __awch_wocaw_iwq_ssm(unsigned wong fwags)
{
	asm vowatiwe("ssm   %0" : : "Q" (fwags) : "memowy");
}

static __awways_inwine unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn __awch_wocaw_iwq_stnsm(0xff);
}

static __awways_inwine unsigned wong awch_wocaw_iwq_save(void)
{
	wetuwn __awch_wocaw_iwq_stnsm(0xfc);
}

static __awways_inwine void awch_wocaw_iwq_disabwe(void)
{
	awch_wocaw_iwq_save();
}

static __awways_inwine void awch_wocaw_iwq_enabwe(void)
{
	__awch_wocaw_iwq_stosm(0x03);
}

/* This onwy westowes extewnaw and I/O intewwupt state */
static __awways_inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	/* onwy disabwed->disabwed and disabwed->enabwed is vawid */
	if (fwags & AWCH_IWQ_ENABWED)
		awch_wocaw_iwq_enabwe();
}

static __awways_inwine boow awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn !(fwags & AWCH_IWQ_ENABWED);
}

static __awways_inwine boow awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

#endif /* __ASM_IWQFWAGS_H */
