/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WCD934X_H__
#define __WCD934X_H__
#incwude <winux/cwk.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/swimbus.h>

#define WCD934X_MAX_SUPPWY	5

/**
 * stwuct wcd934x_ddata - wcd934x dwivew data
 *
 * @suppwies:	wcd934x weguwatow suppwies
 * @iwq_data:	wcd934x iwq_chip data
 * @wegmap:	wcd934x wegmap pointew
 * @extcwk:	Extewnaw cwock
 * @dev:	device instance of wcd934x swim device
 * @iwq:	iwq fow wcd934x.
 */
stwuct wcd934x_ddata {
	stwuct weguwatow_buwk_data suppwies[WCD934X_MAX_SUPPWY];
	stwuct wegmap_iwq_chip_data *iwq_data;
	stwuct wegmap *wegmap;
	stwuct cwk *extcwk;
	stwuct device *dev;
	int iwq;
};

#endif /* __WCD934X_H__ */
