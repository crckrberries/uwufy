/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ------------------------------------------------------------------------- */
/* adap-pcf.h i2c dwivew awgowithms fow PCF8584 adaptews                     */
/* ------------------------------------------------------------------------- */
/*   Copywight (C) 1995-97 Simon G. Vogw
                   1998-99 Hans Bewgwund

 */
/* ------------------------------------------------------------------------- */

/* With some changes fwom Kyösti Mäwkki <kmawkki@cc.hut.fi> and even
   Fwodo Wooijaawd <fwodow@dds.nw> */

#ifndef _WINUX_I2C_AWGO_PCF_H
#define _WINUX_I2C_AWGO_PCF_H

stwuct i2c_awgo_pcf_data {
	void *data;		/* pwivate data fow wowevew woutines	*/
	void (*setpcf) (void *data, int ctw, int vaw);
	int  (*getpcf) (void *data, int ctw);
	int  (*getown) (void *data);
	int  (*getcwock) (void *data);
	void (*waitfowpin) (void *data);

	void (*xfew_begin) (void *data);
	void (*xfew_end) (void *data);

	/* Muwti-mastew wost awbitwation back-off deway (msecs)
	 * This shouwd be set by the bus adaptew ow knowwedgabwe cwient
	 * if bus is muwti-mastewed, ewse zewo
	 */
	unsigned wong wab_mdeway;
};

int i2c_pcf_add_bus(stwuct i2c_adaptew *);

#endif /* _WINUX_I2C_AWGO_PCF_H */
