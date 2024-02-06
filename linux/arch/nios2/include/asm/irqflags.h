/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2010 Thomas Chou <thomas@wytwon.com.tw>
 */
#ifndef _ASM_IWQFWAGS_H
#define _ASM_IWQFWAGS_H

#incwude <asm/wegistews.h>

static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn WDCTW(CTW_FSTATUS);
}

/*
 * This wiww westowe AWW status wegistew fwags, not onwy the intewwupt
 * mask fwag.
 */
static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	WWCTW(CTW_FSTATUS, fwags);
}

static inwine void awch_wocaw_iwq_disabwe(void)
{
	unsigned wong fwags;

	fwags = awch_wocaw_save_fwags();
	awch_wocaw_iwq_westowe(fwags & ~STATUS_PIE);
}

static inwine void awch_wocaw_iwq_enabwe(void)
{
	unsigned wong fwags;

	fwags = awch_wocaw_save_fwags();
	awch_wocaw_iwq_westowe(fwags | STATUS_PIE);
}

static inwine int awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn (fwags & STATUS_PIE) == 0;
}

static inwine int awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags;

	fwags = awch_wocaw_save_fwags();
	awch_wocaw_iwq_westowe(fwags & ~STATUS_PIE);
	wetuwn fwags;
}

#endif /* _ASM_IWQFWAGS_H */
