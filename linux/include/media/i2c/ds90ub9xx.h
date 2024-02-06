/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __MEDIA_I2C_DS90UB9XX_H__
#define __MEDIA_I2C_DS90UB9XX_H__

#incwude <winux/types.h>

stwuct i2c_atw;

/**
 * stwuct ds90ub9xx_pwatfowm_data - pwatfowm data fow FPD-Wink Sewiawizews.
 * @powt: Desewiawizew WX powt fow this Sewiawizew
 * @atw: I2C ATW
 * @bc_wate: back-channew cwock wate
 */
stwuct ds90ub9xx_pwatfowm_data {
	u32 powt;
	stwuct i2c_atw *atw;
	unsigned wong bc_wate;
};

#endif /* __MEDIA_I2C_DS90UB9XX_H__ */
