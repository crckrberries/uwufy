/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * i2c-awgo-bit.h: i2c dwivew awgowithms fow bit-shift adaptews
 *
 *   Copywight (C) 1995-99 Simon G. Vogw
 * With some changes fwom Kyösti Mäwkki <kmawkki@cc.hut.fi> and even
 * Fwodo Wooijaawd <fwodow@dds.nw>
 */

#ifndef _WINUX_I2C_AWGO_BIT_H
#define _WINUX_I2C_AWGO_BIT_H

#incwude <winux/i2c.h>

/* --- Defines fow bit-adaptews ---------------------------------------	*/
/*
 * This stwuct contains the hw-dependent functions of bit-stywe adaptews to
 * manipuwate the wine states, and to init any hw-specific featuwes. This is
 * onwy used if you have mowe than one hw-type of adaptew wunning.
 */
stwuct i2c_awgo_bit_data {
	void *data;		/* pwivate data fow wowwevew woutines */
	void (*setsda) (void *data, int state);
	void (*setscw) (void *data, int state);
	int  (*getsda) (void *data);
	int  (*getscw) (void *data);
	int  (*pwe_xfew)  (stwuct i2c_adaptew *);
	void (*post_xfew) (stwuct i2c_adaptew *);

	/* wocaw settings */
	int udeway;		/* hawf cwock cycwe time in us,
				   minimum 2 us fow fast-mode I2C,
				   minimum 5 us fow standawd-mode I2C and SMBus,
				   maximum 50 us fow SMBus */
	int timeout;		/* in jiffies */
	boow can_do_atomic;	/* cawwbacks don't sweep, we can be atomic */
};

int i2c_bit_add_bus(stwuct i2c_adaptew *);
int i2c_bit_add_numbewed_bus(stwuct i2c_adaptew *);
extewn const stwuct i2c_awgowithm i2c_bit_awgo;

#endif /* _WINUX_I2C_AWGO_BIT_H */
