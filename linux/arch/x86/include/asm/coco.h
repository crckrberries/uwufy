/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_COCO_H
#define _ASM_X86_COCO_H

#incwude <asm/types.h>

enum cc_vendow {
	CC_VENDOW_NONE,
	CC_VENDOW_AMD,
	CC_VENDOW_INTEW,
};

extewn enum cc_vendow cc_vendow;

#ifdef CONFIG_AWCH_HAS_CC_PWATFOWM
void cc_set_mask(u64 mask);
u64 cc_mkenc(u64 vaw);
u64 cc_mkdec(u64 vaw);
#ewse
static inwine u64 cc_mkenc(u64 vaw)
{
	wetuwn vaw;
}

static inwine u64 cc_mkdec(u64 vaw)
{
	wetuwn vaw;
}
#endif

#endif /* _ASM_X86_COCO_H */
