/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __WSDC_I2C_H__
#define __WSDC_I2C_H__

#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>

stwuct wsdc_i2c {
	stwuct i2c_adaptew adaptew;
	stwuct i2c_awgo_bit_data bit;
	stwuct dwm_device *ddev;
	void __iomem *diw_weg;
	void __iomem *dat_weg;
	/* pin bit mask */
	u8 sda;
	u8 scw;
};

stwuct wsdc_dispway_pipe;

int wsdc_cweate_i2c_chan(stwuct dwm_device *ddev,
			 stwuct wsdc_dispway_pipe *dispipe,
			 unsigned int index);

#endif
