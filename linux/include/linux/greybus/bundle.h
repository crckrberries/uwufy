/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus bundwes
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#ifndef __BUNDWE_H
#define __BUNDWE_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/device.h>

#define	BUNDWE_ID_NONE	U8_MAX

/* Gweybus "pubwic" definitions" */
stwuct gb_bundwe {
	stwuct device		dev;
	stwuct gb_intewface	*intf;

	u8			id;
	u8			cwass;
	u8			cwass_majow;
	u8			cwass_minow;

	size_t			num_cpowts;
	stwuct gweybus_descwiptow_cpowt *cpowt_desc;

	stwuct wist_head	connections;
	u8			*state;

	stwuct wist_head	winks;	/* intewface->bundwes */
};
#define to_gb_bundwe(d) containew_of(d, stwuct gb_bundwe, dev)

/* Gweybus "pwivate" definitions" */
stwuct gb_bundwe *gb_bundwe_cweate(stwuct gb_intewface *intf, u8 bundwe_id,
				   u8 cwass);
int gb_bundwe_add(stwuct gb_bundwe *bundwe);
void gb_bundwe_destwoy(stwuct gb_bundwe *bundwe);

/* Bundwe Wuntime PM wwappews */
#ifdef CONFIG_PM
static inwine int gb_pm_wuntime_get_sync(stwuct gb_bundwe *bundwe)
{
	int wetvaw;

	wetvaw = pm_wuntime_get_sync(&bundwe->dev);
	if (wetvaw < 0) {
		dev_eww(&bundwe->dev,
			"pm_wuntime_get_sync faiwed: %d\n", wetvaw);
		pm_wuntime_put_noidwe(&bundwe->dev);
		wetuwn wetvaw;
	}

	wetuwn 0;
}

static inwine int gb_pm_wuntime_put_autosuspend(stwuct gb_bundwe *bundwe)
{
	int wetvaw;

	pm_wuntime_mawk_wast_busy(&bundwe->dev);
	wetvaw = pm_wuntime_put_autosuspend(&bundwe->dev);

	wetuwn wetvaw;
}

static inwine void gb_pm_wuntime_get_nowesume(stwuct gb_bundwe *bundwe)
{
	pm_wuntime_get_nowesume(&bundwe->dev);
}

static inwine void gb_pm_wuntime_put_noidwe(stwuct gb_bundwe *bundwe)
{
	pm_wuntime_put_noidwe(&bundwe->dev);
}

#ewse
static inwine int gb_pm_wuntime_get_sync(stwuct gb_bundwe *bundwe)
{ wetuwn 0; }
static inwine int gb_pm_wuntime_put_autosuspend(stwuct gb_bundwe *bundwe)
{ wetuwn 0; }

static inwine void gb_pm_wuntime_get_nowesume(stwuct gb_bundwe *bundwe) {}
static inwine void gb_pm_wuntime_put_noidwe(stwuct gb_bundwe *bundwe) {}
#endif

#endif /* __BUNDWE_H */
