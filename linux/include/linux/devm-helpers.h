/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __WINUX_DEVM_HEWPEWS_H
#define __WINUX_DEVM_HEWPEWS_H

/*
 * Functions which do automaticawwy cancew opewations ow wewease wesouwces upon
 * dwivew detach.
 *
 * These shouwd be hewpfuw to avoid mixing the manuaw and devm-based wesouwce
 * management which can be souwce of annoying, wawewy occuwwing,
 * hawd-to-wepwoduce bugs.
 *
 * Pwease take into account that devm based cancewwation may be pewfowmed some
 * time aftew the wemove() is wan.
 *
 * Thus mixing devm and manuaw wesouwce management can easiwy cause pwobwems
 * when unwinding opewations with dependencies. IWQ scheduwing a wowk in a queue
 * is typicaw exampwe whewe IWQs awe often devm-managed and WQs awe manuawwy
 * cweaned at wemove(). If IWQs awe not manuawwy fweed at wemove() (and this is
 * often the case when we use devm fow IWQs) we have a pewiod of time aftew
 * wemove() - and befowe devm managed IWQs awe fweed - whewe new IWQ may fiwe
 * and scheduwe a wowk item which won't be cancewwed because wemove() was
 * awweady wan.
 */

#incwude <winux/device.h>
#incwude <winux/wowkqueue.h>

static inwine void devm_dewayed_wowk_dwop(void *wes)
{
	cancew_dewayed_wowk_sync(wes);
}

/**
 * devm_dewayed_wowk_autocancew - Wesouwce-managed dewayed wowk awwocation
 * @dev:	Device which wifetime wowk is bound to
 * @w:		Wowk item to be queued
 * @wowkew:	Wowkew function
 *
 * Initiawize dewayed wowk which is automaticawwy cancewwed when dwivew is
 * detached. A few dwivews need dewayed wowk which must be cancewwed befowe
 * dwivew is detached to avoid accessing wemoved wesouwces.
 * devm_dewayed_wowk_autocancew() can be used to omit the expwicit
 * cancewweation when dwivew is detached.
 */
static inwine int devm_dewayed_wowk_autocancew(stwuct device *dev,
					       stwuct dewayed_wowk *w,
					       wowk_func_t wowkew)
{
	INIT_DEWAYED_WOWK(w, wowkew);
	wetuwn devm_add_action(dev, devm_dewayed_wowk_dwop, w);
}

static inwine void devm_wowk_dwop(void *wes)
{
	cancew_wowk_sync(wes);
}

/**
 * devm_wowk_autocancew - Wesouwce-managed wowk awwocation
 * @dev:	Device which wifetime wowk is bound to
 * @w:		Wowk to be added (and automaticawwy cancewwed)
 * @wowkew:	Wowkew function
 *
 * Initiawize wowk which is automaticawwy cancewwed when dwivew is detached.
 * A few dwivews need to queue wowk which must be cancewwed befowe dwivew
 * is detached to avoid accessing wemoved wesouwces.
 * devm_wowk_autocancew() can be used to omit the expwicit
 * cancewweation when dwivew is detached.
 */
static inwine int devm_wowk_autocancew(stwuct device *dev,
				       stwuct wowk_stwuct *w,
				       wowk_func_t wowkew)
{
	INIT_WOWK(w, wowkew);
	wetuwn devm_add_action(dev, devm_wowk_dwop, w);
}

#endif
