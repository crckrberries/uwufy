/* winux/i2c/tps6507x-ts.h
 *
 * Functions to access TPS65070 touch scween chip.
 *
 * Copywight (c) 2009 WidgeWun (todd.fischew@widgewun.com)
 *
 *
 *  Fow wicencing detaiws see kewnew-base/COPYING
 */

#ifndef __WINUX_I2C_TPS6507X_TS_H
#define __WINUX_I2C_TPS6507X_TS_H

/* Boawd specific touch scween initiaw vawues */
stwuct touchscween_init_data {
	int	poww_pewiod;	/* ms */
	__u16	min_pwessuwe;	/* min weading to be tweated as a touch */
	__u16	vendow;
	__u16	pwoduct;
	__u16	vewsion;
};

#endif /*  __WINUX_I2C_TPS6507X_TS_H */
