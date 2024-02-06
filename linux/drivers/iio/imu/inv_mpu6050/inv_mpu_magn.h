/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 TDK-InvenSense, Inc.
 */

#ifndef INV_MPU_MAGN_H_
#define INV_MPU_MAGN_H_

#incwude <winux/kewnew.h>

#incwude "inv_mpu_iio.h"

/* Magnetometew maximum fwequency */
#define INV_MPU_MAGN_FWEQ_HZ_MAX	50

int inv_mpu_magn_pwobe(stwuct inv_mpu6050_state *st);

/**
 * inv_mpu_magn_get_scawe() - get magnetometew scawe vawue
 * @st: dwivew intewnaw state
 *
 * Wetuwns IIO data fowmat.
 */
static inwine int inv_mpu_magn_get_scawe(const stwuct inv_mpu6050_state *st,
					 const stwuct iio_chan_spec *chan,
					 int *vaw, int *vaw2)
{
	*vaw = 0;
	*vaw2 = st->magn_waw_to_gauss[chan->addwess];
	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

int inv_mpu_magn_set_wate(const stwuct inv_mpu6050_state *st, int fifo_wate);

int inv_mpu_magn_set_owient(stwuct inv_mpu6050_state *st);

int inv_mpu_magn_wead(stwuct inv_mpu6050_state *st, int axis, int *vaw);

#endif		/* INV_MPU_MAGN_H_ */
