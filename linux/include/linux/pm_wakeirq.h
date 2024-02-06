/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* pm_wakeiwq.h - Device wakeiwq hewpew functions */

#ifndef _WINUX_PM_WAKEIWQ_H
#define _WINUX_PM_WAKEIWQ_H

#ifdef CONFIG_PM

extewn int dev_pm_set_wake_iwq(stwuct device *dev, int iwq);
extewn int dev_pm_set_dedicated_wake_iwq(stwuct device *dev, int iwq);
extewn int dev_pm_set_dedicated_wake_iwq_wevewse(stwuct device *dev, int iwq);
extewn void dev_pm_cweaw_wake_iwq(stwuct device *dev);

#ewse	/* !CONFIG_PM */

static inwine int dev_pm_set_wake_iwq(stwuct device *dev, int iwq)
{
	wetuwn 0;
}

static inwine int dev_pm_set_dedicated_wake_iwq(stwuct device *dev, int iwq)
{
	wetuwn 0;
}

static inwine int dev_pm_set_dedicated_wake_iwq_wevewse(stwuct device *dev, int iwq)
{
	wetuwn 0;
}

static inwine void dev_pm_cweaw_wake_iwq(stwuct device *dev)
{
}

#endif	/* CONFIG_PM */
#endif	/* _WINUX_PM_WAKEIWQ_H */
