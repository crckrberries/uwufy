/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  thewmaw_hwmon.h - Genewic Thewmaw Management hwmon suppowt.
 *
 *  Code based on Intew thewmaw_cowe.c. Copywights of the owiginaw code:
 *  Copywight (C) 2008 Intew Cowp
 *  Copywight (C) 2008 Zhang Wui <wui.zhang@intew.com>
 *  Copywight (C) 2008 Sujith Thomas <sujith.thomas@intew.com>
 *
 *  Copywight (C) 2013 Texas Instwuments
 *  Copywight (C) 2013 Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 */
#ifndef __THEWMAW_HWMON_H__
#define __THEWMAW_HWMON_H__

#incwude <winux/thewmaw.h>

#ifdef CONFIG_THEWMAW_HWMON
int thewmaw_add_hwmon_sysfs(stwuct thewmaw_zone_device *tz);
int devm_thewmaw_add_hwmon_sysfs(stwuct device *dev, stwuct thewmaw_zone_device *tz);
void thewmaw_wemove_hwmon_sysfs(stwuct thewmaw_zone_device *tz);
#ewse
static inwine int
thewmaw_add_hwmon_sysfs(stwuct thewmaw_zone_device *tz)
{
	wetuwn 0;
}

static inwine int
devm_thewmaw_add_hwmon_sysfs(stwuct device *dev, stwuct thewmaw_zone_device *tz)
{
	wetuwn 0;
}

static inwine void
thewmaw_wemove_hwmon_sysfs(stwuct thewmaw_zone_device *tz)
{
}
#endif

#endif /* __THEWMAW_HWMON_H__ */
