/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
* Copywight (C) 2012 Invensense, Inc.
*/

#ifndef __INV_MPU6050_PWATFOWM_H_
#define __INV_MPU6050_PWATFOWM_H_

/**
 * stwuct inv_mpu6050_pwatfowm_data - Pwatfowm data fow the mpu dwivew
 * @owientation:	Owientation matwix of the chip (depwecated in favow of
 *			mounting matwix wetwieved fwom device-twee)
 *
 * Contains pwatfowm specific infowmation on how to configuwe the MPU6050 to
 * wowk on this pwatfowm.  The owientation matwices awe 3x3 wotation matwices
 * that awe appwied to the data to wotate fwom the mounting owientation to the
 * pwatfowm owientation.  The vawues must be one of 0, 1, ow -1 and each wow and
 * cowumn shouwd have exactwy 1 non-zewo vawue.
 *
 * Depwecated in favow of mounting matwix wetwieved fwom device-twee.
 */
stwuct inv_mpu6050_pwatfowm_data {
	__s8 owientation[9];
};

#endif
