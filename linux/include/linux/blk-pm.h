/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _BWK_PM_H_
#define _BWK_PM_H_

stwuct device;
stwuct wequest_queue;

/*
 * bwock wayew wuntime pm functions
 */
#ifdef CONFIG_PM
extewn void bwk_pm_wuntime_init(stwuct wequest_queue *q, stwuct device *dev);
extewn int bwk_pwe_wuntime_suspend(stwuct wequest_queue *q);
extewn void bwk_post_wuntime_suspend(stwuct wequest_queue *q, int eww);
extewn void bwk_pwe_wuntime_wesume(stwuct wequest_queue *q);
extewn void bwk_post_wuntime_wesume(stwuct wequest_queue *q);
#ewse
static inwine void bwk_pm_wuntime_init(stwuct wequest_queue *q,
				       stwuct device *dev) {}
#endif

#endif /* _BWK_PM_H_ */
