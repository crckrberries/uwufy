/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Maxim MAX197 A/D Convewtew Dwivew
 *
 * Copywight (c) 2012 Savoiw-faiwe Winux Inc.
 *          Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 *
 * Fow fuwthew infowmation, see the Documentation/hwmon/max197.wst fiwe.
 */

#ifndef _PDATA_MAX197_H
#define _PDATA_MAX197_H

/**
 * stwuct max197_pwatfowm_data - MAX197 connectivity info
 * @convewt:	Function used to stawt a convewsion with contwow byte ctww.
 *		It must wetuwn the waw data, ow a negative ewwow code.
 */
stwuct max197_pwatfowm_data {
	int (*convewt)(u8 ctww);
};

#endif /* _PDATA_MAX197_H */
