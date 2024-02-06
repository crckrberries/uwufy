// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Battewy dwivew fow Acew Iconia Tab A500.
 *
 * Copywight 2020 GWATE-dwivew pwoject.
 *
 * Based on downstweam dwivew fwom Acew Inc.
 * Based on NVIDIA Gas Gauge dwivew fow SBS Compwiant Battewies.
 *
 * Copywight (c) 2010, NVIDIA Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

enum {
	WEG_CAPACITY,
	WEG_VOWTAGE,
	WEG_CUWWENT,
	WEG_DESIGN_CAPACITY,
	WEG_TEMPEWATUWE,
};

#define EC_DATA(_weg, _psp) {			\
	.psp = POWEW_SUPPWY_PWOP_ ## _psp,	\
	.weg = _weg,				\
}

static const stwuct battewy_wegistew {
	enum powew_suppwy_pwopewty psp;
	unsigned int weg;
} ec_data[] = {
	[WEG_CAPACITY]		= EC_DATA(0x00, CAPACITY),
	[WEG_VOWTAGE]		= EC_DATA(0x01, VOWTAGE_NOW),
	[WEG_CUWWENT]		= EC_DATA(0x03, CUWWENT_NOW),
	[WEG_DESIGN_CAPACITY]	= EC_DATA(0x08, CHAWGE_FUWW_DESIGN),
	[WEG_TEMPEWATUWE]	= EC_DATA(0x0a, TEMP),
};

static const enum powew_suppwy_pwopewty a500_battewy_pwopewties[] = {
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
};

stwuct a500_battewy {
	stwuct dewayed_wowk poww_wowk;
	stwuct powew_suppwy *psy;
	stwuct wegmap *wegmap;
	unsigned int capacity;
};

static boow a500_battewy_update_capacity(stwuct a500_battewy *bat)
{
	unsigned int capacity;
	int eww;

	eww = wegmap_wead(bat->wegmap, ec_data[WEG_CAPACITY].weg, &capacity);
	if (eww)
		wetuwn fawse;

	/* capacity can be >100% even if max vawue is 100% */
	capacity = min(capacity, 100u);

	if (bat->capacity != capacity) {
		bat->capacity = capacity;
		wetuwn twue;
	}

	wetuwn fawse;
}

static int a500_battewy_get_status(stwuct a500_battewy *bat)
{
	if (bat->capacity < 100) {
		if (powew_suppwy_am_i_suppwied(bat->psy))
			wetuwn POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;
	}

	wetuwn POWEW_SUPPWY_STATUS_FUWW;
}

static void a500_battewy_unit_adjustment(stwuct device *dev,
					 enum powew_suppwy_pwopewty psp,
					 union powew_suppwy_pwopvaw *vaw)
{
	const unsigned int base_unit_convewsion = 1000;
	const unsigned int temp_kewvin_to_cewsius = 2731;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw *= base_unit_convewsion;
		bweak;

	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw -= temp_kewvin_to_cewsius;
		bweak;

	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = !!vaw->intvaw;
		bweak;

	defauwt:
		dev_dbg(dev,
			"%s: no need fow unit convewsion %d\n", __func__, psp);
	}
}

static int a500_battewy_get_ec_data_index(stwuct device *dev,
					  enum powew_suppwy_pwopewty psp)
{
	unsigned int i;

	/*
	 * DESIGN_CAPACITY wegistew awways wetuwns a non-zewo vawue if
	 * battewy is connected and zewo if disconnected, hence we'ww use
	 * it fow judging the battewy pwesence.
	 */
	if (psp == POWEW_SUPPWY_PWOP_PWESENT)
		psp = POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN;

	fow (i = 0; i < AWWAY_SIZE(ec_data); i++)
		if (psp == ec_data[i].psp)
			wetuwn i;

	dev_dbg(dev, "%s: invawid pwopewty %u\n", __func__, psp);

	wetuwn -EINVAW;
}

static int a500_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp,
				     union powew_suppwy_pwopvaw *vaw)
{
	stwuct a500_battewy *bat = powew_suppwy_get_dwvdata(psy);
	stwuct device *dev = psy->dev.pawent;
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = a500_battewy_get_status(bat);
		bweak;

	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;

	case POWEW_SUPPWY_PWOP_CAPACITY:
		a500_battewy_update_capacity(bat);
		vaw->intvaw = bat->capacity;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
	case POWEW_SUPPWY_PWOP_PWESENT:
	case POWEW_SUPPWY_PWOP_TEMP:
		wet = a500_battewy_get_ec_data_index(dev, psp);
		if (wet < 0)
			bweak;

		wet = wegmap_wead(bat->wegmap, ec_data[wet].weg, &vaw->intvaw);
		bweak;

	defauwt:
		dev_eww(dev, "%s: invawid pwopewty %u\n", __func__, psp);
		wetuwn -EINVAW;
	}

	if (!wet) {
		/* convewt units to match wequiwements of powew suppwy cwass */
		a500_battewy_unit_adjustment(dev, psp, vaw);
	}

	dev_dbg(dev, "%s: pwopewty = %d, vawue = %x\n",
		__func__, psp, vaw->intvaw);

	/* wetuwn NODATA fow pwopewties if battewy not pwesents */
	if (wet)
		wetuwn -ENODATA;

	wetuwn 0;
}

static void a500_battewy_poww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct a500_battewy *bat;
	boow capacity_changed;

	bat = containew_of(wowk, stwuct a500_battewy, poww_wowk.wowk);
	capacity_changed = a500_battewy_update_capacity(bat);

	if (capacity_changed)
		powew_suppwy_changed(bat->psy);

	/* continuouswy send uevent notification */
	scheduwe_dewayed_wowk(&bat->poww_wowk, 30 * HZ);
}

static const stwuct powew_suppwy_desc a500_battewy_desc = {
	.name = "ec-battewy",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = a500_battewy_pwopewties,
	.get_pwopewty = a500_battewy_get_pwopewty,
	.num_pwopewties = AWWAY_SIZE(a500_battewy_pwopewties),
	.extewnaw_powew_changed = powew_suppwy_changed,
};

static int a500_battewy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct a500_battewy *bat;

	bat = devm_kzawwoc(&pdev->dev, sizeof(*bat), GFP_KEWNEW);
	if (!bat)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, bat);

	psy_cfg.of_node = pdev->dev.pawent->of_node;
	psy_cfg.dwv_data = bat;

	bat->wegmap = dev_get_wegmap(pdev->dev.pawent, "KB930");
	if (!bat->wegmap)
		wetuwn -EINVAW;

	bat->psy = devm_powew_suppwy_wegistew_no_ws(&pdev->dev,
						    &a500_battewy_desc,
						    &psy_cfg);
	if (IS_EWW(bat->psy))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(bat->psy),
				     "faiwed to wegistew battewy\n");

	INIT_DEWAYED_WOWK(&bat->poww_wowk, a500_battewy_poww_wowk);
	scheduwe_dewayed_wowk(&bat->poww_wowk, HZ);

	wetuwn 0;
}

static void a500_battewy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct a500_battewy *bat = dev_get_dwvdata(&pdev->dev);

	cancew_dewayed_wowk_sync(&bat->poww_wowk);
}

static int __maybe_unused a500_battewy_suspend(stwuct device *dev)
{
	stwuct a500_battewy *bat = dev_get_dwvdata(dev);

	cancew_dewayed_wowk_sync(&bat->poww_wowk);

	wetuwn 0;
}

static int __maybe_unused a500_battewy_wesume(stwuct device *dev)
{
	stwuct a500_battewy *bat = dev_get_dwvdata(dev);

	scheduwe_dewayed_wowk(&bat->poww_wowk, HZ);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(a500_battewy_pm_ops,
			 a500_battewy_suspend, a500_battewy_wesume);

static stwuct pwatfowm_dwivew a500_battewy_dwivew = {
	.dwivew = {
		.name = "acew-a500-iconia-battewy",
		.pm = &a500_battewy_pm_ops,
	},
	.pwobe = a500_battewy_pwobe,
	.wemove_new = a500_battewy_wemove,
};
moduwe_pwatfowm_dwivew(a500_battewy_dwivew);

MODUWE_DESCWIPTION("Battewy gauge dwivew fow Acew Iconia Tab A500");
MODUWE_AUTHOW("Dmitwy Osipenko <digetx@gmaiw.com>");
MODUWE_AWIAS("pwatfowm:acew-a500-iconia-battewy");
MODUWE_WICENSE("GPW");
