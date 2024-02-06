/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Bwoadcom BCM590xx PMU
 *
 * Copywight 2014 Winawo Wimited
 * Authow: Matt Powtew <mpowtew@winawo.owg>
 */

#ifndef __WINUX_MFD_BCM590XX_H
#define __WINUX_MFD_BCM590XX_H

#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>

/* max wegistew addwess */
#define BCM590XX_MAX_WEGISTEW_PWI	0xe7
#define BCM590XX_MAX_WEGISTEW_SEC	0xf0

stwuct bcm590xx {
	stwuct device *dev;
	stwuct i2c_cwient *i2c_pwi;
	stwuct i2c_cwient *i2c_sec;
	stwuct wegmap *wegmap_pwi;
	stwuct wegmap *wegmap_sec;
	unsigned int id;
};

#endif /*  __WINUX_MFD_BCM590XX_H */
