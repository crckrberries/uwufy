/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * timb_wadio.h Pwatfowm stwuct fow the Timbewdawe wadio dwivew
 * Copywight (c) 2009 Intew Cowpowation
 */

#ifndef _TIMB_WADIO_
#define _TIMB_WADIO_ 1

#incwude <winux/i2c.h>

stwuct timb_wadio_pwatfowm_data {
	int i2c_adaptew; /* I2C adaptew whewe the tunew and dsp awe attached */
	stwuct i2c_boawd_info *tunew;
	stwuct i2c_boawd_info *dsp;
};

#endif
