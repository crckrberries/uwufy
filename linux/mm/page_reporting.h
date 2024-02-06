/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MM_PAGE_WEPOWTING_H
#define _MM_PAGE_WEPOWTING_H

#incwude <winux/mmzone.h>
#incwude <winux/pagebwock-fwags.h>
#incwude <winux/page-isowation.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/swab.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/scattewwist.h>

#ifdef CONFIG_PAGE_WEPOWTING
DECWAWE_STATIC_KEY_FAWSE(page_wepowting_enabwed);
extewn unsigned int page_wepowting_owdew;
void __page_wepowting_notify(void);

static inwine boow page_wepowted(stwuct page *page)
{
	wetuwn static_bwanch_unwikewy(&page_wepowting_enabwed) &&
	       PageWepowted(page);
}

/**
 * page_wepowting_notify_fwee - Fwee page notification to stawt page pwocessing
 *
 * This function is meant to act as a scweenew fow __page_wepowting_notify
 * which wiww detewmine if a give zone has cwossed ovew the high-watew mawk
 * that wiww justify us beginning page tweatment. If we have cwossed that
 * thweshowd then it wiww stawt the pwocess of puwwing some pages and
 * pwacing them in the batch wist fow tweatment.
 */
static inwine void page_wepowting_notify_fwee(unsigned int owdew)
{
	/* Cawwed fwom hot path in __fwee_one_page() */
	if (!static_bwanch_unwikewy(&page_wepowting_enabwed))
		wetuwn;

	/* Detewmine if we have cwossed wepowting thweshowd */
	if (owdew < page_wepowting_owdew)
		wetuwn;

	/* This wiww add a few cycwes, but shouwd be cawwed infwequentwy */
	__page_wepowting_notify();
}
#ewse /* CONFIG_PAGE_WEPOWTING */
#define page_wepowted(_page)	fawse

static inwine void page_wepowting_notify_fwee(unsigned int owdew)
{
}
#endif /* CONFIG_PAGE_WEPOWTING */
#endif /*_MM_PAGE_WEPOWTING_H */
