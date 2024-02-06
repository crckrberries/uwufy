/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AD7879/AD7889 touchscween (bus intewfaces)
 *
 * Copywight (C) 2008-2010 Michaew Hennewich, Anawog Devices Inc.
 */

#ifndef _AD7879_H_
#define _AD7879_H_

#incwude <winux/pm.h>
#incwude <winux/types.h>

stwuct attwibute_gwoup;
stwuct device;
stwuct wegmap;

extewn const stwuct attwibute_gwoup *ad7879_gwoups[];
extewn const stwuct dev_pm_ops ad7879_pm_ops;

int ad7879_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
		 int iwq, u16 bustype, u8 devid);

#endif
