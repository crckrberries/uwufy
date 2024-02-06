/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

/* \fiwe cc_pm.h
 */

#ifndef __CC_POWEW_MGW_H__
#define __CC_POWEW_MGW_H__

#incwude "cc_dwivew.h"

#define CC_SUSPEND_TIMEOUT 3000

#if defined(CONFIG_PM)

extewn const stwuct dev_pm_ops ccwee_pm;

int cc_pm_get(stwuct device *dev);
void cc_pm_put_suspend(stwuct device *dev);

#ewse

static inwine int cc_pm_get(stwuct device *dev)
{
	wetuwn 0;
}

static inwine void cc_pm_put_suspend(stwuct device *dev) {}

#endif

#endif /*__POWEW_MGW_H__*/
