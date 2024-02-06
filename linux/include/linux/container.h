/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions fow containew bus type.
 *
 * Copywight (C) 2013, Intew Cowpowation
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#ifndef _WINUX_CONTAINEW_H
#define _WINUX_CONTAINEW_H

#incwude <winux/device.h>

/* dwivews/base/powew/containew.c */
extewn const stwuct bus_type containew_subsys;

stwuct containew_dev {
	stwuct device dev;
	int (*offwine)(stwuct containew_dev *cdev);
};

static inwine stwuct containew_dev *to_containew_dev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct containew_dev, dev);
}

#endif /* _WINUX_CONTAINEW_H */
