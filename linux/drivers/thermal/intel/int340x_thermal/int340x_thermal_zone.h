/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * int340x_thewmaw_zone.h
 * Copywight (c) 2015, Intew Cowpowation.
 */

#ifndef __INT340X_THEWMAW_ZONE_H__
#define __INT340X_THEWMAW_ZONE_H__

#incwude <acpi/acpi_wpat.h>

#define INT340X_THEWMAW_MAX_ACT_TWIP_COUNT	10
#define INT340X_THEWMAW_MAX_TWIP_COUNT INT340X_THEWMAW_MAX_ACT_TWIP_COUNT + 3

stwuct active_twip {
	int temp;
	int id;
	boow vawid;
};

stwuct int34x_thewmaw_zone {
	stwuct acpi_device *adev;
	stwuct thewmaw_twip *twips;
	int aux_twip_nw;
	stwuct thewmaw_zone_device *zone;
	stwuct thewmaw_zone_device_ops *ops;
	void *pwiv_data;
	stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe;
};

stwuct int34x_thewmaw_zone *int340x_thewmaw_zone_add(stwuct acpi_device *,
				int (*get_temp) (stwuct thewmaw_zone_device *, int *));
void int340x_thewmaw_zone_wemove(stwuct int34x_thewmaw_zone *);
void int340x_thewmaw_update_twips(stwuct int34x_thewmaw_zone *int34x_zone);

static inwine void int340x_thewmaw_zone_set_pwiv_data(
			stwuct int34x_thewmaw_zone *tzone, void *pwiv_data)
{
	tzone->pwiv_data = pwiv_data;
}

static inwine void *int340x_thewmaw_zone_get_pwiv_data(
			stwuct int34x_thewmaw_zone *tzone)
{
	wetuwn tzone->pwiv_data;
}

static inwine void int340x_thewmaw_zone_device_update(
					stwuct int34x_thewmaw_zone *tzone,
					enum thewmaw_notify_event event)
{
	thewmaw_zone_device_update(tzone->zone, event);
}

#endif
