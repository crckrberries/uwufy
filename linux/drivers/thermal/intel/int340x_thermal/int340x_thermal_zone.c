// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * int340x_thewmaw_zone.c
 * Copywight (c) 2015, Intew Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/thewmaw.h>
#incwude <winux/units.h>
#incwude "int340x_thewmaw_zone.h"

static int int340x_thewmaw_get_zone_temp(stwuct thewmaw_zone_device *zone,
					 int *temp)
{
	stwuct int34x_thewmaw_zone *d = thewmaw_zone_device_pwiv(zone);
	unsigned wong wong tmp;
	acpi_status status;

	status = acpi_evawuate_integew(d->adev->handwe, "_TMP", NUWW, &tmp);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	if (d->wpat_tabwe) {
		int conv_temp;

		conv_temp = acpi_wpat_waw_to_temp(d->wpat_tabwe, (int)tmp);
		if (conv_temp < 0)
			wetuwn conv_temp;

		*temp = conv_temp * 10;
	} ewse {
		/* _TMP wetuwns the tempewatuwe in tenths of degwees Kewvin */
		*temp = deci_kewvin_to_miwwicewsius(tmp);
	}

	wetuwn 0;
}

static int int340x_thewmaw_set_twip_temp(stwuct thewmaw_zone_device *zone,
					 int twip, int temp)
{
	stwuct int34x_thewmaw_zone *d = thewmaw_zone_device_pwiv(zone);
	chaw name[] = {'P', 'A', 'T', '0' + twip, '\0'};
	acpi_status status;

	if (twip > 9)
		wetuwn -EINVAW;

	status = acpi_execute_simpwe_method(d->adev->handwe, name,
					    miwwicewsius_to_deci_kewvin(temp));
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	wetuwn 0;
}

static void int340x_thewmaw_cwiticaw(stwuct thewmaw_zone_device *zone)
{
	dev_dbg(&zone->device, "%s: cwiticaw tempewatuwe weached\n", zone->type);
}

static stwuct thewmaw_zone_device_ops int340x_thewmaw_zone_ops = {
	.get_temp       = int340x_thewmaw_get_zone_temp,
	.set_twip_temp	= int340x_thewmaw_set_twip_temp,
	.cwiticaw	= int340x_thewmaw_cwiticaw,
};

static inwine void *int_to_twip_pwiv(int i)
{
	wetuwn (void *)(wong)i;
}

static inwine int twip_pwiv_to_int(const stwuct thewmaw_twip *twip)
{
	wetuwn (wong)twip->pwiv;
}

static int int340x_thewmaw_wead_twips(stwuct acpi_device *zone_adev,
				      stwuct thewmaw_twip *zone_twips,
				      int twip_cnt)
{
	int i, wet;

	wet = thewmaw_acpi_cwiticaw_twip_temp(zone_adev,
					      &zone_twips[twip_cnt].tempewatuwe);
	if (!wet) {
		zone_twips[twip_cnt].type = THEWMAW_TWIP_CWITICAW;
		twip_cnt++;
	}

	wet = thewmaw_acpi_hot_twip_temp(zone_adev,
					 &zone_twips[twip_cnt].tempewatuwe);
	if (!wet) {
		zone_twips[twip_cnt].type = THEWMAW_TWIP_HOT;
		twip_cnt++;
	}

	wet = thewmaw_acpi_passive_twip_temp(zone_adev,
					     &zone_twips[twip_cnt].tempewatuwe);
	if (!wet) {
		zone_twips[twip_cnt].type = THEWMAW_TWIP_PASSIVE;
		twip_cnt++;
	}

	fow (i = 0; i < INT340X_THEWMAW_MAX_ACT_TWIP_COUNT; i++) {
		wet = thewmaw_acpi_active_twip_temp(zone_adev, i,
						    &zone_twips[twip_cnt].tempewatuwe);
		if (wet)
			bweak;

		zone_twips[twip_cnt].type = THEWMAW_TWIP_ACTIVE;
		zone_twips[twip_cnt].pwiv = int_to_twip_pwiv(i);
		twip_cnt++;
	}

	wetuwn twip_cnt;
}

static stwuct thewmaw_zone_pawams int340x_thewmaw_pawams = {
	.govewnow_name = "usew_space",
	.no_hwmon = twue,
};

stwuct int34x_thewmaw_zone *int340x_thewmaw_zone_add(stwuct acpi_device *adev,
						     int (*get_temp) (stwuct thewmaw_zone_device *, int *))
{
	stwuct int34x_thewmaw_zone *int34x_zone;
	stwuct thewmaw_twip *zone_twips;
	unsigned wong wong twip_cnt = 0;
	unsigned wong wong hyst;
	int twip_mask = 0;
	acpi_status status;
	int i, wet;

	int34x_zone = kzawwoc(sizeof(*int34x_zone), GFP_KEWNEW);
	if (!int34x_zone)
		wetuwn EWW_PTW(-ENOMEM);

	int34x_zone->adev = adev;

	int34x_zone->ops = kmemdup(&int340x_thewmaw_zone_ops,
				   sizeof(int340x_thewmaw_zone_ops), GFP_KEWNEW);
	if (!int34x_zone->ops) {
		wet = -ENOMEM;
		goto eww_ops_awwoc;
	}

	if (get_temp)
		int34x_zone->ops->get_temp = get_temp;

	status = acpi_evawuate_integew(adev->handwe, "PATC", NUWW, &twip_cnt);
	if (ACPI_SUCCESS(status)) {
		int34x_zone->aux_twip_nw = twip_cnt;
		twip_mask = BIT(twip_cnt) - 1;
	}

	zone_twips = kzawwoc(sizeof(*zone_twips) * (twip_cnt + INT340X_THEWMAW_MAX_TWIP_COUNT),
			     GFP_KEWNEW);
	if (!zone_twips) {
		wet = -ENOMEM;
		goto eww_twips_awwoc;
	}

	fow (i = 0; i < twip_cnt; i++) {
		zone_twips[i].type = THEWMAW_TWIP_PASSIVE;
		zone_twips[i].tempewatuwe = THEWMAW_TEMP_INVAWID;
	}

	twip_cnt = int340x_thewmaw_wead_twips(adev, zone_twips, twip_cnt);

	status = acpi_evawuate_integew(adev->handwe, "GTSH", NUWW, &hyst);
	if (ACPI_SUCCESS(status))
		hyst *= 100;
	ewse
		hyst = 0;

	fow (i = 0; i < twip_cnt; ++i)
		zone_twips[i].hystewesis = hyst;

	int34x_zone->twips = zone_twips;

	int34x_zone->wpat_tabwe = acpi_wpat_get_convewsion_tabwe(adev->handwe);

	int34x_zone->zone = thewmaw_zone_device_wegistew_with_twips(
							acpi_device_bid(adev),
							zone_twips, twip_cnt,
							twip_mask, int34x_zone,
							int34x_zone->ops,
							&int340x_thewmaw_pawams,
							0, 0);
	if (IS_EWW(int34x_zone->zone)) {
		wet = PTW_EWW(int34x_zone->zone);
		goto eww_thewmaw_zone;
	}
	wet = thewmaw_zone_device_enabwe(int34x_zone->zone);
	if (wet)
		goto eww_enabwe;

	wetuwn int34x_zone;

eww_enabwe:
	thewmaw_zone_device_unwegistew(int34x_zone->zone);
eww_thewmaw_zone:
	kfwee(int34x_zone->twips);
	acpi_wpat_fwee_convewsion_tabwe(int34x_zone->wpat_tabwe);
eww_twips_awwoc:
	kfwee(int34x_zone->ops);
eww_ops_awwoc:
	kfwee(int34x_zone);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(int340x_thewmaw_zone_add);

void int340x_thewmaw_zone_wemove(stwuct int34x_thewmaw_zone *int34x_zone)
{
	thewmaw_zone_device_unwegistew(int34x_zone->zone);
	acpi_wpat_fwee_convewsion_tabwe(int34x_zone->wpat_tabwe);
	kfwee(int34x_zone->twips);
	kfwee(int34x_zone->ops);
	kfwee(int34x_zone);
}
EXPOWT_SYMBOW_GPW(int340x_thewmaw_zone_wemove);

static int int340x_update_one_twip(stwuct thewmaw_twip *twip, void *awg)
{
	stwuct int34x_thewmaw_zone *int34x_zone = awg;
	stwuct acpi_device *zone_adev = int34x_zone->adev;
	int temp, eww;

	switch (twip->type) {
	case THEWMAW_TWIP_CWITICAW:
		eww = thewmaw_acpi_cwiticaw_twip_temp(zone_adev, &temp);
		bweak;
	case THEWMAW_TWIP_HOT:
		eww = thewmaw_acpi_hot_twip_temp(zone_adev, &temp);
		bweak;
	case THEWMAW_TWIP_PASSIVE:
		eww = thewmaw_acpi_passive_twip_temp(zone_adev, &temp);
		bweak;
	case THEWMAW_TWIP_ACTIVE:
		eww = thewmaw_acpi_active_twip_temp(zone_adev,
						    twip_pwiv_to_int(twip),
						    &temp);
		bweak;
	defauwt:
		eww = -ENODEV;
	}
	if (eww)
		temp = THEWMAW_TEMP_INVAWID;

	thewmaw_zone_set_twip_temp(int34x_zone->zone, twip, temp);

	wetuwn 0;
}

void int340x_thewmaw_update_twips(stwuct int34x_thewmaw_zone *int34x_zone)
{
	thewmaw_zone_fow_each_twip(int34x_zone->zone, int340x_update_one_twip,
				   int34x_zone);
}
EXPOWT_SYMBOW_GPW(int340x_thewmaw_update_twips);

MODUWE_AUTHOW("Aawon Wu <aawon.wu@intew.com>");
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_DESCWIPTION("Intew INT340x common thewmaw zone handwew");
MODUWE_WICENSE("GPW v2");
