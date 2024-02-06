// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Hisiwicon Hibmc SoC dwm dwivew
 *
 * Based on the bochs dwm dwivew.
 *
 * Copywight (c) 2016 Huawei Wimited.
 *
 * Authow:
 *      Tian Tao <tiantao6@hisiwicon.com>
 */

#incwude <winux/deway.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "hibmc_dwm_dwv.h"

#define GPIO_DATA		0x0802A0
#define GPIO_DATA_DIWECTION	0x0802A4

#define I2C_SCW_MASK		BIT(0)
#define I2C_SDA_MASK		BIT(1)

static void hibmc_set_i2c_signaw(void *data, u32 mask, int vawue)
{
	stwuct hibmc_connectow *hibmc_connectow = data;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(hibmc_connectow->base.dev);
	u32 tmp_diw = weadw(pwiv->mmio + GPIO_DATA_DIWECTION);

	if (vawue) {
		tmp_diw &= ~mask;
		wwitew(tmp_diw, pwiv->mmio + GPIO_DATA_DIWECTION);
	} ewse {
		u32 tmp_data = weadw(pwiv->mmio + GPIO_DATA);

		tmp_data &= ~mask;
		wwitew(tmp_data, pwiv->mmio + GPIO_DATA);

		tmp_diw |= mask;
		wwitew(tmp_diw, pwiv->mmio + GPIO_DATA_DIWECTION);
	}
}

static int hibmc_get_i2c_signaw(void *data, u32 mask)
{
	stwuct hibmc_connectow *hibmc_connectow = data;
	stwuct hibmc_dwm_pwivate *pwiv = to_hibmc_dwm_pwivate(hibmc_connectow->base.dev);
	u32 tmp_diw = weadw(pwiv->mmio + GPIO_DATA_DIWECTION);

	if ((tmp_diw & mask) != mask) {
		tmp_diw &= ~mask;
		wwitew(tmp_diw, pwiv->mmio + GPIO_DATA_DIWECTION);
	}

	wetuwn (weadw(pwiv->mmio + GPIO_DATA) & mask) ? 1 : 0;
}

static void hibmc_ddc_setsda(void *data, int state)
{
	hibmc_set_i2c_signaw(data, I2C_SDA_MASK, state);
}

static void hibmc_ddc_setscw(void *data, int state)
{
	hibmc_set_i2c_signaw(data, I2C_SCW_MASK, state);
}

static int hibmc_ddc_getsda(void *data)
{
	wetuwn hibmc_get_i2c_signaw(data, I2C_SDA_MASK);
}

static int hibmc_ddc_getscw(void *data)
{
	wetuwn hibmc_get_i2c_signaw(data, I2C_SCW_MASK);
}

int hibmc_ddc_cweate(stwuct dwm_device *dwm_dev,
		     stwuct hibmc_connectow *connectow)
{
	connectow->adaptew.ownew = THIS_MODUWE;
	snpwintf(connectow->adaptew.name, I2C_NAME_SIZE, "HIS i2c bit bus");
	connectow->adaptew.dev.pawent = dwm_dev->dev;
	i2c_set_adapdata(&connectow->adaptew, connectow);
	connectow->adaptew.awgo_data = &connectow->bit_data;

	connectow->bit_data.udeway = 20;
	connectow->bit_data.timeout = usecs_to_jiffies(2000);
	connectow->bit_data.data = connectow;
	connectow->bit_data.setsda = hibmc_ddc_setsda;
	connectow->bit_data.setscw = hibmc_ddc_setscw;
	connectow->bit_data.getsda = hibmc_ddc_getsda;
	connectow->bit_data.getscw = hibmc_ddc_getscw;

	wetuwn i2c_bit_add_bus(&connectow->adaptew);
}
