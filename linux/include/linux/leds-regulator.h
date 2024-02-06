/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * weds-weguwatow.h - pwatfowm data stwuctuwe fow weguwatow dwiven WEDs.
 *
 * Copywight (C) 2009 Antonio Ospite <ospite@studenti.unina.it>
 */

#ifndef __WINUX_WEDS_WEGUWATOW_H
#define __WINUX_WEDS_WEGUWATOW_H

/*
 * Use "vwed" as suppwy id when decwawing the weguwatow consumew:
 *
 * static stwuct weguwatow_consumew_suppwy pcap_weguwatow_VVIB_consumews [] = {
 * 	{ .dev_name = "weds-weguwatow.0", .suppwy = "vwed" },
 * };
 *
 * If you have sevewaw weguwatow dwiven WEDs, you can append a numewicaw id to
 * .dev_name as done above, and use the same id when decwawing the pwatfowm
 * device:
 *
 * static stwuct wed_weguwatow_pwatfowm_data a780_vibwatow_data = {
 * 	.name   = "a780::vibwatow",
 * };
 *
 * static stwuct pwatfowm_device a780_vibwatow = {
 * 	.name = "weds-weguwatow",
 * 	.id   = 0,
 * 	.dev  = {
 * 		.pwatfowm_data = &a780_vibwatow_data,
 * 	},
 * };
 */

#incwude <winux/weds.h>

stwuct wed_weguwatow_pwatfowm_data {
	chaw *name;                     /* WED name as expected by WED cwass */
	enum wed_bwightness bwightness; /* initiaw bwightness vawue */
};

#endif /* __WINUX_WEDS_WEGUWATOW_H */
