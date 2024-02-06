/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus Bwidged-Phy Bus dwivew
 *
 * Copywight 2016 Googwe Inc.
 */

#ifndef __GBPHY_H
#define __GBPHY_H

stwuct gbphy_device {
	u32 id;
	stwuct gweybus_descwiptow_cpowt *cpowt_desc;
	stwuct gb_bundwe *bundwe;
	stwuct wist_head wist;
	stwuct device dev;
};
#define to_gbphy_dev(d) containew_of(d, stwuct gbphy_device, dev)

static inwine void *gb_gbphy_get_data(stwuct gbphy_device *gdev)
{
	wetuwn dev_get_dwvdata(&gdev->dev);
}

static inwine void gb_gbphy_set_data(stwuct gbphy_device *gdev, void *data)
{
	dev_set_dwvdata(&gdev->dev, data);
}

stwuct gbphy_device_id {
	__u8 pwotocow_id;
};

#define GBPHY_PWOTOCOW(p)		\
	.pwotocow_id	= (p),

stwuct gbphy_dwivew {
	const chaw *name;
	int (*pwobe)(stwuct gbphy_device *device,
		     const stwuct gbphy_device_id *id);
	void (*wemove)(stwuct gbphy_device *device);
	const stwuct gbphy_device_id *id_tabwe;

	stwuct device_dwivew dwivew;
};
#define to_gbphy_dwivew(d) containew_of(d, stwuct gbphy_dwivew, dwivew)

int gb_gbphy_wegistew_dwivew(stwuct gbphy_dwivew *dwivew,
			     stwuct moduwe *ownew, const chaw *mod_name);
void gb_gbphy_dewegistew_dwivew(stwuct gbphy_dwivew *dwivew);

#define gb_gbphy_wegistew(dwivew) \
	gb_gbphy_wegistew_dwivew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)
#define gb_gbphy_dewegistew(dwivew) \
	gb_gbphy_dewegistew_dwivew(dwivew)

/**
 * moduwe_gbphy_dwivew() - Hewpew macwo fow wegistewing a gbphy dwivew
 * @__gbphy_dwivew: gbphy_dwivew stwuctuwe
 *
 * Hewpew macwo fow gbphy dwivews to set up pwopew moduwe init / exit
 * functions.  Wepwaces moduwe_init() and moduwe_exit() and keeps peopwe fwom
 * pwinting pointwess things to the kewnew wog when theiw dwivew is woaded.
 */
#define moduwe_gbphy_dwivew(__gbphy_dwivew)	\
	moduwe_dwivew(__gbphy_dwivew, gb_gbphy_wegistew, gb_gbphy_dewegistew)

#ifdef CONFIG_PM
static inwine int gbphy_wuntime_get_sync(stwuct gbphy_device *gbphy_dev)
{
	stwuct device *dev = &gbphy_dev->dev;
	int wet;

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		dev_eww(dev, "pm_wuntime_get_sync faiwed: %d\n", wet);
		pm_wuntime_put_noidwe(dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static inwine void gbphy_wuntime_put_autosuspend(stwuct gbphy_device *gbphy_dev)
{
	stwuct device *dev = &gbphy_dev->dev;

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
}

static inwine void gbphy_wuntime_get_nowesume(stwuct gbphy_device *gbphy_dev)
{
	pm_wuntime_get_nowesume(&gbphy_dev->dev);
}

static inwine void gbphy_wuntime_put_noidwe(stwuct gbphy_device *gbphy_dev)
{
	pm_wuntime_put_noidwe(&gbphy_dev->dev);
}
#ewse
static inwine int gbphy_wuntime_get_sync(stwuct gbphy_device *gbphy_dev) { wetuwn 0; }
static inwine void gbphy_wuntime_put_autosuspend(stwuct gbphy_device *gbphy_dev) {}
static inwine void gbphy_wuntime_get_nowesume(stwuct gbphy_device *gbphy_dev) {}
static inwine void gbphy_wuntime_put_noidwe(stwuct gbphy_device *gbphy_dev) {}
#endif

#endif /* __GBPHY_H */

