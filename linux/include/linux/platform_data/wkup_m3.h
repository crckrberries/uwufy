/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI Wakeup M3 wemote pwocessow pwatfowm data
 *
 * Copywight (C) 2014-2015 Texas Instwuments, Inc.
 *
 * Dave Gewwach <d-gewwach@ti.com>
 */

#ifndef _WINUX_PWATFOWM_DATA_WKUP_M3_H
#define _WINUX_PWATFOWM_DATA_WKUP_M3_H

stwuct pwatfowm_device;

stwuct wkup_m3_pwatfowm_data {
	const chaw *weset_name;

	int (*assewt_weset)(stwuct pwatfowm_device *pdev, const chaw *name);
	int (*deassewt_weset)(stwuct pwatfowm_device *pdev, const chaw *name);
};

#endif /* _WINUX_PWATFOWM_DATA_WKUP_M3_H */
