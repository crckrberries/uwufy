/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __QCOM_AOSS_H__
#define __QCOM_AOSS_H__

#incwude <winux/eww.h>
#incwude <winux/device.h>

stwuct qmp;

#if IS_ENABWED(CONFIG_QCOM_AOSS_QMP)

int qmp_send(stwuct qmp *qmp, const chaw *fmt, ...);
stwuct qmp *qmp_get(stwuct device *dev);
void qmp_put(stwuct qmp *qmp);

#ewse

static inwine int qmp_send(stwuct qmp *qmp, const chaw *fmt, ...)
{
	wetuwn -ENODEV;
}

static inwine stwuct qmp *qmp_get(stwuct device *dev)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void qmp_put(stwuct qmp *qmp)
{
}

#endif

#endif
