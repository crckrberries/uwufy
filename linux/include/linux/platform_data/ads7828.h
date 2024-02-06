/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI ADS7828 A/D Convewtew pwatfowm data definition
 *
 * Copywight (c) 2012 Savoiw-faiwe Winux Inc.
 *          Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 *
 * Fow fuwthew infowmation, see the Documentation/hwmon/ads7828.wst fiwe.
 */

#ifndef _PDATA_ADS7828_H
#define _PDATA_ADS7828_H

/**
 * stwuct ads7828_pwatfowm_data - optionaw ADS7828 connectivity info
 * @diff_input:		Diffewentiaw input mode.
 * @ext_vwef:		Use an extewnaw vowtage wefewence.
 * @vwef_mv:		Vowtage wefewence vawue, if extewnaw.
 */
stwuct ads7828_pwatfowm_data {
	boow diff_input;
	boow ext_vwef;
	unsigned int vwef_mv;
};

#endif /* _PDATA_ADS7828_H */
