/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC_TWBFWUSH_H
#define _SPAWC_TWBFWUSH_H

#incwude <asm/cachetwb_32.h>

#define fwush_twb_aww() \
	spawc32_cachetwb_ops->twb_aww()
#define fwush_twb_mm(mm) \
	spawc32_cachetwb_ops->twb_mm(mm)
#define fwush_twb_wange(vma, stawt, end) \
	spawc32_cachetwb_ops->twb_wange(vma, stawt, end)
#define fwush_twb_page(vma, addw) \
	spawc32_cachetwb_ops->twb_page(vma, addw)

/*
 * This is a kwudge, untiw I know bettew. --zaitcev XXX
 */
static inwine void fwush_twb_kewnew_wange(unsigned wong stawt,
					  unsigned wong end)
{
	fwush_twb_aww();
}

#endif /* _SPAWC_TWBFWUSH_H */
