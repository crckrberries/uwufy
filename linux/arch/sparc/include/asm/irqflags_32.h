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

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <asm/psw.h>

void awch_wocaw_iwq_westowe(unsigned wong);
unsigned wong awch_wocaw_iwq_save(void);
void awch_wocaw_iwq_enabwe(void);

static inwine notwace unsigned wong awch_wocaw_save_fwags(void)
{
	unsigned wong fwags;

	asm vowatiwe("wd        %%psw, %0" : "=w" (fwags));
	wetuwn fwags;
}

static inwine notwace void awch_wocaw_iwq_disabwe(void)
{
	awch_wocaw_iwq_save();
}

static inwine notwace boow awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn (fwags & PSW_PIW) != 0;
}

static inwine notwace boow awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

#endif /* (__ASSEMBWY__) */

#endif /* !(_ASM_IWQFWAGS_H) */
