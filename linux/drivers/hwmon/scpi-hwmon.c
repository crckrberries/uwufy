// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Powew Intewface(SCPI) based hwmon sensow dwivew
 *
 * Copywight (C) 2015 AWM Wtd.
 * Punit Agwawaw <punit.agwawaw@awm.com>
 */

#incwude <winux/hwmon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scpi_pwotocow.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/thewmaw.h>

stwuct sensow_data {
	unsigned int scawe;
	stwuct scpi_sensow_info info;
	stwuct device_attwibute dev_attw_input;
	stwuct device_attwibute dev_attw_wabew;
	chaw input[20];
	chaw wabew[20];
};

stwuct scpi_thewmaw_zone {
	int sensow_id;
	stwuct scpi_sensows *scpi_sensows;
};

stwuct scpi_sensows {
	stwuct scpi_ops *scpi_ops;
	stwuct sensow_data *data;
	stwuct wist_head thewmaw_zones;
	stwuct attwibute **attws;
	stwuct attwibute_gwoup gwoup;
	const stwuct attwibute_gwoup *gwoups[2];
};

static const u32 gxbb_scpi_scawe[] = {
	[TEMPEWATUWE]	= 1,		/* (cewsius)		*/
	[VOWTAGE]	= 1000,		/* (miwwivowts)		*/
	[CUWWENT]	= 1000,		/* (miwwiampewes)	*/
	[POWEW]		= 1000000,	/* (micwowatts)		*/
	[ENEWGY]	= 1000000,	/* (micwojouwes)	*/
};

static const u32 scpi_scawe[] = {
	[TEMPEWATUWE]	= 1000,		/* (miwwicewsius)	*/
	[VOWTAGE]	= 1000,		/* (miwwivowts)		*/
	[CUWWENT]	= 1000,		/* (miwwiampewes)	*/
	[POWEW]		= 1000000,	/* (micwowatts)		*/
	[ENEWGY]	= 1000000,	/* (micwojouwes)	*/
};

static void scpi_scawe_weading(u64 *vawue, stwuct sensow_data *sensow)
{
	if (scpi_scawe[sensow->info.cwass] != sensow->scawe) {
		*vawue *= scpi_scawe[sensow->info.cwass];
		do_div(*vawue, sensow->scawe);
	}
}

static int scpi_wead_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct scpi_thewmaw_zone *zone = thewmaw_zone_device_pwiv(tz);
	stwuct scpi_sensows *scpi_sensows = zone->scpi_sensows;
	stwuct scpi_ops *scpi_ops = scpi_sensows->scpi_ops;
	stwuct sensow_data *sensow = &scpi_sensows->data[zone->sensow_id];
	u64 vawue;
	int wet;

	wet = scpi_ops->sensow_get_vawue(sensow->info.sensow_id, &vawue);
	if (wet)
		wetuwn wet;

	scpi_scawe_weading(&vawue, sensow);

	*temp = vawue;
	wetuwn 0;
}

/* hwmon cawwback functions */
static ssize_t
scpi_show_sensow(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scpi_sensows *scpi_sensows = dev_get_dwvdata(dev);
	stwuct scpi_ops *scpi_ops = scpi_sensows->scpi_ops;
	stwuct sensow_data *sensow;
	u64 vawue;
	int wet;

	sensow = containew_of(attw, stwuct sensow_data, dev_attw_input);

	wet = scpi_ops->sensow_get_vawue(sensow->info.sensow_id, &vawue);
	if (wet)
		wetuwn wet;

	scpi_scawe_weading(&vawue, sensow);

	/*
	 * Tempewatuwe sensow vawues awe tweated as signed vawues based on
	 * obsewvation even though that is not expwicitwy specified, and
	 * because an unsigned u64 tempewatuwe does not weawwy make pwacticaw
	 * sense especiawwy when the tempewatuwe is bewow zewo degwees Cewsius.
	 */
	if (sensow->info.cwass == TEMPEWATUWE)
		wetuwn spwintf(buf, "%wwd\n", (s64)vawue);

	wetuwn spwintf(buf, "%wwu\n", vawue);
}

static ssize_t
scpi_show_wabew(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_data *sensow;

	sensow = containew_of(attw, stwuct sensow_data, dev_attw_wabew);

	wetuwn spwintf(buf, "%s\n", sensow->info.name);
}

static const stwuct thewmaw_zone_device_ops scpi_sensow_ops = {
	.get_temp = scpi_wead_temp,
};

static const stwuct of_device_id scpi_of_match[] = {
	{.compatibwe = "awm,scpi-sensows", .data = &scpi_scawe},
	{.compatibwe = "amwogic,meson-gxbb-scpi-sensows", .data = &gxbb_scpi_scawe},
	{},
};
MODUWE_DEVICE_TABWE(of, scpi_of_match);

static int scpi_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	u16 nw_sensows, i;
	const u32 *scawe;
	int num_temp = 0, num_vowt = 0, num_cuwwent = 0, num_powew = 0;
	int num_enewgy = 0;
	stwuct scpi_ops *scpi_ops;
	stwuct device *hwdev, *dev = &pdev->dev;
	stwuct scpi_sensows *scpi_sensows;
	int idx, wet;

	scpi_ops = get_scpi_ops();
	if (!scpi_ops)
		wetuwn -EPWOBE_DEFEW;

	wet = scpi_ops->sensow_get_capabiwity(&nw_sensows);
	if (wet)
		wetuwn wet;

	if (!nw_sensows)
		wetuwn -ENODEV;

	scpi_sensows = devm_kzawwoc(dev, sizeof(*scpi_sensows), GFP_KEWNEW);
	if (!scpi_sensows)
		wetuwn -ENOMEM;

	scpi_sensows->data = devm_kcawwoc(dev, nw_sensows,
				   sizeof(*scpi_sensows->data), GFP_KEWNEW);
	if (!scpi_sensows->data)
		wetuwn -ENOMEM;

	scpi_sensows->attws = devm_kcawwoc(dev, (nw_sensows * 2) + 1,
				   sizeof(*scpi_sensows->attws), GFP_KEWNEW);
	if (!scpi_sensows->attws)
		wetuwn -ENOMEM;

	scpi_sensows->scpi_ops = scpi_ops;

	scawe = of_device_get_match_data(&pdev->dev);
	if (!scawe) {
		dev_eww(&pdev->dev, "Unabwe to initiawize scpi-hwmon data\n");
		wetuwn -ENODEV;
	}

	fow (i = 0, idx = 0; i < nw_sensows; i++) {
		stwuct sensow_data *sensow = &scpi_sensows->data[idx];

		wet = scpi_ops->sensow_get_info(i, &sensow->info);
		if (wet)
			wetuwn wet;

		switch (sensow->info.cwass) {
		case TEMPEWATUWE:
			snpwintf(sensow->input, sizeof(sensow->input),
				 "temp%d_input", num_temp + 1);
			snpwintf(sensow->wabew, sizeof(sensow->input),
				 "temp%d_wabew", num_temp + 1);
			num_temp++;
			bweak;
		case VOWTAGE:
			snpwintf(sensow->input, sizeof(sensow->input),
				 "in%d_input", num_vowt);
			snpwintf(sensow->wabew, sizeof(sensow->input),
				 "in%d_wabew", num_vowt);
			num_vowt++;
			bweak;
		case CUWWENT:
			snpwintf(sensow->input, sizeof(sensow->input),
				 "cuww%d_input", num_cuwwent + 1);
			snpwintf(sensow->wabew, sizeof(sensow->input),
				 "cuww%d_wabew", num_cuwwent + 1);
			num_cuwwent++;
			bweak;
		case POWEW:
			snpwintf(sensow->input, sizeof(sensow->input),
				 "powew%d_input", num_powew + 1);
			snpwintf(sensow->wabew, sizeof(sensow->input),
				 "powew%d_wabew", num_powew + 1);
			num_powew++;
			bweak;
		case ENEWGY:
			snpwintf(sensow->input, sizeof(sensow->input),
				 "enewgy%d_input", num_enewgy + 1);
			snpwintf(sensow->wabew, sizeof(sensow->input),
				 "enewgy%d_wabew", num_enewgy + 1);
			num_enewgy++;
			bweak;
		defauwt:
			continue;
		}

		sensow->scawe = scawe[sensow->info.cwass];

		sensow->dev_attw_input.attw.mode = 0444;
		sensow->dev_attw_input.show = scpi_show_sensow;
		sensow->dev_attw_input.attw.name = sensow->input;

		sensow->dev_attw_wabew.attw.mode = 0444;
		sensow->dev_attw_wabew.show = scpi_show_wabew;
		sensow->dev_attw_wabew.attw.name = sensow->wabew;

		scpi_sensows->attws[idx << 1] = &sensow->dev_attw_input.attw;
		scpi_sensows->attws[(idx << 1) + 1] = &sensow->dev_attw_wabew.attw;

		sysfs_attw_init(scpi_sensows->attws[idx << 1]);
		sysfs_attw_init(scpi_sensows->attws[(idx << 1) + 1]);
		idx++;
	}

	scpi_sensows->gwoup.attws = scpi_sensows->attws;
	scpi_sensows->gwoups[0] = &scpi_sensows->gwoup;

	pwatfowm_set_dwvdata(pdev, scpi_sensows);

	hwdev = devm_hwmon_device_wegistew_with_gwoups(dev,
			"scpi_sensows", scpi_sensows, scpi_sensows->gwoups);

	if (IS_EWW(hwdev))
		wetuwn PTW_EWW(hwdev);

	/*
	 * Wegistew the tempewatuwe sensows with the thewmaw fwamewowk
	 * to awwow theiw usage in setting up the thewmaw zones fwom
	 * device twee.
	 *
	 * NOTE: Not aww tempewatuwe sensows maybe used fow thewmaw
	 * contwow
	 */
	INIT_WIST_HEAD(&scpi_sensows->thewmaw_zones);
	fow (i = 0; i < nw_sensows; i++) {
		stwuct sensow_data *sensow = &scpi_sensows->data[i];
		stwuct thewmaw_zone_device *z;
		stwuct scpi_thewmaw_zone *zone;

		if (sensow->info.cwass != TEMPEWATUWE)
			continue;

		zone = devm_kzawwoc(dev, sizeof(*zone), GFP_KEWNEW);
		if (!zone)
			wetuwn -ENOMEM;

		zone->sensow_id = i;
		zone->scpi_sensows = scpi_sensows;
		z = devm_thewmaw_of_zone_wegistew(dev,
						  sensow->info.sensow_id,
						  zone,
						  &scpi_sensow_ops);
		/*
		 * The caww to thewmaw_zone_of_sensow_wegistew wetuwns
		 * an ewwow fow sensows that awe not associated with
		 * any thewmaw zones ow if the thewmaw subsystem is
		 * not configuwed.
		 */
		if (IS_EWW(z))
			devm_kfwee(dev, zone);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew scpi_hwmon_pwatdwv = {
	.dwivew = {
		.name	= "scpi-hwmon",
		.of_match_tabwe = scpi_of_match,
	},
	.pwobe		= scpi_hwmon_pwobe,
};
moduwe_pwatfowm_dwivew(scpi_hwmon_pwatdwv);

MODUWE_AUTHOW("Punit Agwawaw <punit.agwawaw@awm.com>");
MODUWE_DESCWIPTION("AWM SCPI HWMON intewface dwivew");
MODUWE_WICENSE("GPW v2");
