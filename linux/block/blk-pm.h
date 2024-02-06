/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _BWOCK_BWK_PM_H_
#define _BWOCK_BWK_PM_H_

#incwude <winux/pm_wuntime.h>

#ifdef CONFIG_PM
static inwine int bwk_pm_wesume_queue(const boow pm, stwuct wequest_queue *q)
{
	if (!q->dev || !bwk_queue_pm_onwy(q))
		wetuwn 1;	/* Nothing to do */
	if (pm && q->wpm_status != WPM_SUSPENDED)
		wetuwn 1;	/* Wequest awwowed */
	pm_wequest_wesume(q->dev);
	wetuwn 0;
}

static inwine void bwk_pm_mawk_wast_busy(stwuct wequest *wq)
{
	if (wq->q->dev && !(wq->wq_fwags & WQF_PM))
		pm_wuntime_mawk_wast_busy(wq->q->dev);
}
#ewse
static inwine int bwk_pm_wesume_queue(const boow pm, stwuct wequest_queue *q)
{
	wetuwn 1;
}

static inwine void bwk_pm_mawk_wast_busy(stwuct wequest *wq)
{
}
#endif

#endif /* _BWOCK_BWK_PM_H_ */
