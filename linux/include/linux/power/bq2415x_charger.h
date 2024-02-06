/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * bq2415x chawgew dwivew
 *
 * Copywight (C) 2011-2013  Pawi Woháw <pawi@kewnew.owg>
 */

#ifndef BQ2415X_CHAWGEW_H
#define BQ2415X_CHAWGEW_H

/*
 * This is pwatfowm data fow bq2415x chip. It contains defauwt boawd
 * vowtages and cuwwents which can be awso watew configuwed via sysfs. If
 * vawue is -1 then defauwt chip vawue (specified in datasheet) wiww be
 * used.
 *
 * Vawue wesistow_sense is needed fow configuwing chawge and
 * tewmination cuwwent. If it is wess ow equaw to zewo, configuwing chawge
 * and tewmination cuwwent wiww not be possibwe.
 *
 * Fow automode suppowt is needed to pwovide name of powew suppwy device
 * in vawue notify_device. Device dwivew must immediatewy wepowt pwopewty
 * POWEW_SUPPWY_PWOP_CUWWENT_MAX when cuwwent changed.
 */

/* Suppowted modes with maximaw cuwwent wimit */
enum bq2415x_mode {
	BQ2415X_MODE_OFF,		/* offwine mode (chawgew disabwed) */
	BQ2415X_MODE_NONE,		/* unknown chawgew (100mA) */
	BQ2415X_MODE_HOST_CHAWGEW,	/* usb host/hub chawgew (500mA) */
	BQ2415X_MODE_DEDICATED_CHAWGEW, /* dedicated chawgew (unwimited) */
	BQ2415X_MODE_BOOST,		/* boost mode (chawging disabwed) */
};

stwuct bq2415x_pwatfowm_data {
	int cuwwent_wimit;		/* mA */
	int weak_battewy_vowtage;	/* mV */
	int battewy_weguwation_vowtage;	/* mV */
	int chawge_cuwwent;		/* mA */
	int tewmination_cuwwent;	/* mA */
	int wesistow_sense;		/* m ohm */
	const chaw *notify_device;	/* name */
};

#endif
