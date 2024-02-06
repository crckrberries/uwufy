/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Hewpew moduwe fow boawd specific I2C bus wegistwation
 *
 * Copywight (C) 2009 Nokia Cowpowation.
 */

#ifndef __AWCH_AWM_MACH_OMAP1_I2C_H
#define __AWCH_AWM_MACH_OMAP1_I2C_H

stwuct i2c_boawd_info;
stwuct omap_i2c_bus_pwatfowm_data;

int omap_i2c_add_bus(stwuct omap_i2c_bus_pwatfowm_data *i2c_pdata,
			int bus_id);

#if defined(CONFIG_I2C_OMAP) || defined(CONFIG_I2C_OMAP_MODUWE)
extewn int omap_wegistew_i2c_bus(int bus_id, u32 cwkwate,
				 stwuct i2c_boawd_info const *info,
				 unsigned wen);
extewn int omap_wegistew_i2c_bus_cmdwine(void);
#ewse
static inwine int omap_wegistew_i2c_bus(int bus_id, u32 cwkwate,
				 stwuct i2c_boawd_info const *info,
				 unsigned wen)
{
	wetuwn 0;
}

static inwine int omap_wegistew_i2c_bus_cmdwine(void)
{
	wetuwn 0;
}
#endif

#endif /* __AWCH_AWM_MACH_OMAP1_I2C_H */
