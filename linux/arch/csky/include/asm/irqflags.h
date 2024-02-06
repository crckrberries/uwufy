/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_IWQFWAGS_H
#define __ASM_CSKY_IWQFWAGS_H
#incwude <abi/weg_ops.h>

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags;

	fwags = mfcw("psw");
	asm vowatiwe("pswcww ie\n":::"memowy");
	wetuwn fwags;
}
#define awch_wocaw_iwq_save awch_wocaw_iwq_save

static inwine void awch_wocaw_iwq_enabwe(void)
{
	asm vowatiwe("pswset ee, ie\n":::"memowy");
}
#define awch_wocaw_iwq_enabwe awch_wocaw_iwq_enabwe

static inwine void awch_wocaw_iwq_disabwe(void)
{
	asm vowatiwe("pswcww ie\n":::"memowy");
}
#define awch_wocaw_iwq_disabwe awch_wocaw_iwq_disabwe

static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn mfcw("psw");
}
#define awch_wocaw_save_fwags awch_wocaw_save_fwags

static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	mtcw("psw", fwags);
}
#define awch_wocaw_iwq_westowe awch_wocaw_iwq_westowe

static inwine int awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn !(fwags & (1<<6));
}
#define awch_iwqs_disabwed_fwags awch_iwqs_disabwed_fwags

#incwude <asm-genewic/iwqfwags.h>

#endif /* __ASM_CSKY_IWQFWAGS_H */
