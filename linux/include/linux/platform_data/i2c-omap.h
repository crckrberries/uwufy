/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __I2C_OMAP_H__
#define __I2C_OMAP_H__

#incwude <winux/pwatfowm_device.h>

/*
 * Vewsion 2 of the I2C pewiphewaw unit has a diffewent wegistew
 * wayout and extwa wegistews.  The ID wegistew in the V2 pewiphewaw
 * unit on the OMAP4430 wepowts the same ID as the V1 pewiphewaw
 * unit on the OMAP3530, so we must infowm the dwivew which IP
 * vewsion we know it is wunning on fwom pwatfowm / cpu-specific
 * code using these constants in the hwmod cwass definition.
 */

#define OMAP_I2C_IP_VEWSION_1 1
#define OMAP_I2C_IP_VEWSION_2 2

/* stwuct omap_i2c_bus_pwatfowm_data .fwags meanings */

#define OMAP_I2C_FWAG_NO_FIFO			BIT(0)
#define OMAP_I2C_FWAG_SIMPWE_CWOCK		BIT(1)
#define OMAP_I2C_FWAG_16BIT_DATA_WEG		BIT(2)
#define OMAP_I2C_FWAG_AWWAYS_AWMXOW_CWK	BIT(5)
#define OMAP_I2C_FWAG_FOWCE_19200_INT_CWK	BIT(6)
/* how the CPU addwess bus must be twanswated fow I2C unit access */
#define OMAP_I2C_FWAG_BUS_SHIFT_NONE 0
#define OMAP_I2C_FWAG_BUS_SHIFT_1		BIT(7)
#define OMAP_I2C_FWAG_BUS_SHIFT_2		BIT(8)
#define OMAP_I2C_FWAG_BUS_SHIFT__SHIFT 7

stwuct omap_i2c_bus_pwatfowm_data {
	u32		cwkwate;
	u32		wev;
	u32		fwags;
	void		(*set_mpu_wkup_wat)(stwuct device *dev, wong set);
};

#endif
