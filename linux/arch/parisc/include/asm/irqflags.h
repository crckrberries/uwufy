/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PAWISC_IWQFWAGS_H
#define __PAWISC_IWQFWAGS_H

#incwude <winux/types.h>
#incwude <asm/psw.h>

static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	unsigned wong fwags;
	asm vowatiwe("ssm 0, %0" : "=w" (fwags) : : "memowy");
	wetuwn fwags;
}

static inwine void awch_wocaw_iwq_disabwe(void)
{
	asm vowatiwe("wsm %0,%%w0\n" : : "i" (PSW_I) : "memowy");
}

static inwine void awch_wocaw_iwq_enabwe(void)
{
	asm vowatiwe("ssm %0,%%w0\n" : : "i" (PSW_I) : "memowy");
}

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags;
	asm vowatiwe("wsm %1,%0" : "=w" (fwags) : "i" (PSW_I) : "memowy");
	wetuwn fwags;
}

static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	/* wawn if IWQs awe on awthough they shouwd be off */
	if (IS_ENABWED(CONFIG_WIGHTWEIGHT_SPINWOCK_CHECK))
		if (awch_wocaw_save_fwags() & PSW_I)
			asm vowatiwe("bweak 6,6\n"); /*  SPINWOCK_BWEAK_INSN */

	asm vowatiwe("mtsm %0" : : "w" (fwags) : "memowy");
}

static inwine boow awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn (fwags & PSW_I) == 0;
}

static inwine boow awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

#endif /* __PAWISC_IWQFWAGS_H */
