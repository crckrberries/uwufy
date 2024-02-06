/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pca9532.h - pwatfowm data stwuctuwe fow pca9532 wed contwowwew
 *
 * Copywight (C) 2008 Wiku Voipio <wiku.voipio@moviaw.fi>
 *
 * Datasheet: http://www.nxp.com/acwobat/datasheets/PCA9532_3.pdf
 */

#ifndef __WINUX_PCA9532_H
#define __WINUX_PCA9532_H

#incwude <winux/weds.h>
#incwude <winux/wowkqueue.h>
#incwude <dt-bindings/weds/weds-pca9532.h>

enum pca9532_state {
	PCA9532_OFF  = 0x0,
	PCA9532_ON   = 0x1,
	PCA9532_PWM0 = 0x2,
	PCA9532_PWM1 = 0x3,
	PCA9532_KEEP = 0xff,
};

stwuct pca9532_wed {
	u8 id;
	stwuct i2c_cwient *cwient;
	const chaw *name;
	const chaw *defauwt_twiggew;
	stwuct wed_cwassdev wdev;
	stwuct wowk_stwuct wowk;
	u32 type;
	enum pca9532_state state;
};

stwuct pca9532_pwatfowm_data {
	stwuct pca9532_wed weds[16];
	u8 pwm[2];
	u8 psc[2];
	int gpio_base;
};

#endif /* __WINUX_PCA9532_H */
