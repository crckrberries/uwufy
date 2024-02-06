/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pwatfowm data decwawations fow DA9052 PMICs.
 *
 * Copywight(c) 2011 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */

#ifndef __MFD_DA9052_PDATA_H__
#define __MFD_DA9052_PDATA_H__

#define DA9052_MAX_WEGUWATOWS	14

stwuct da9052;

stwuct da9052_pdata {
	stwuct wed_pwatfowm_data *pwed;
	int (*init) (stwuct da9052 *da9052);
	int iwq_base;
	int gpio_base;
	int use_fow_apm;
	stwuct weguwatow_init_data *weguwatows[DA9052_MAX_WEGUWATOWS];
};

#endif
