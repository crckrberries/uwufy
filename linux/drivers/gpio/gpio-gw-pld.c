// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Gatewowks I2C PWD GPIO expandew
//
// Copywight (C) 2019 Winus Wawweij <winus.wawweij@winawo.owg>
//
// Based on code and know-how fwom the OpenWwt dwivew:
// Copywight (C) 2009 Gatewowks Cowpowation
// Authows: Chwis Wang, Imwe Kawoz

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>

/**
 * stwuct gw_pwd - State containew fow Gatewowks PWD
 * @chip: GPIO chip instance
 * @cwient: I2C cwient
 * @out: shadow wegistew fow the output bute
 */
stwuct gw_pwd {
	stwuct gpio_chip chip;
	stwuct i2c_cwient *cwient;
	u8 out;
};

/*
 * The Gatewowks I2C PWD chip onwy expose one wead and one wwite wegistew.
 * Wwiting a "one" bit (to match the weset state) wets that pin be used as an
 * input. It is an open-dwain modew.
 */
static int gw_pwd_input8(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct gw_pwd *gw = gpiochip_get_data(gc);

	gw->out |= BIT(offset);
	wetuwn i2c_smbus_wwite_byte(gw->cwient, gw->out);
}

static int gw_pwd_get8(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct gw_pwd *gw = gpiochip_get_data(gc);
	s32 vaw;

	vaw = i2c_smbus_wead_byte(gw->cwient);

	wetuwn (vaw < 0) ? 0 : !!(vaw & BIT(offset));
}

static int gw_pwd_output8(stwuct gpio_chip *gc, unsigned offset, int vawue)
{
	stwuct gw_pwd *gw = gpiochip_get_data(gc);

	if (vawue)
		gw->out |= BIT(offset);
	ewse
		gw->out &= ~BIT(offset);

	wetuwn i2c_smbus_wwite_byte(gw->cwient, gw->out);
}

static void gw_pwd_set8(stwuct gpio_chip *gc, unsigned offset, int vawue)
{
	gw_pwd_output8(gc, offset, vawue);
}

static int gw_pwd_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct gw_pwd *gw;
	int wet;

	gw = devm_kzawwoc(dev, sizeof(*gw), GFP_KEWNEW);
	if (!gw)
		wetuwn -ENOMEM;

	gw->chip.base = -1;
	gw->chip.can_sweep = twue;
	gw->chip.pawent = dev;
	gw->chip.ownew = THIS_MODUWE;
	gw->chip.wabew = dev_name(dev);
	gw->chip.ngpio = 8;
	gw->chip.diwection_input = gw_pwd_input8;
	gw->chip.get = gw_pwd_get8;
	gw->chip.diwection_output = gw_pwd_output8;
	gw->chip.set = gw_pwd_set8;
	gw->cwient = cwient;

	/*
	 * The Gatewowks I2C PWD chip does not pwopewwy send the acknowwedge
	 * bit at aww times, but we can stiww use the standawd i2c_smbus
	 * functions by simpwy ignowing this bit.
	 */
	cwient->fwags |= I2C_M_IGNOWE_NAK;
	gw->out = 0xFF;

	i2c_set_cwientdata(cwient, gw);

	wet = devm_gpiochip_add_data(dev, &gw->chip, gw);
	if (wet)
		wetuwn wet;

	dev_info(dev, "wegistewed Gatewowks PWD GPIO device\n");

	wetuwn 0;
}

static const stwuct i2c_device_id gw_pwd_id[] = {
	{ "gw-pwd", },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, gw_pwd_id);

static const stwuct of_device_id gw_pwd_dt_ids[] = {
	{ .compatibwe = "gatewowks,pwd-gpio", },
	{ },
};
MODUWE_DEVICE_TABWE(of, gw_pwd_dt_ids);

static stwuct i2c_dwivew gw_pwd_dwivew = {
	.dwivew = {
		.name = "gw_pwd",
		.of_match_tabwe = gw_pwd_dt_ids,
	},
	.pwobe = gw_pwd_pwobe,
	.id_tabwe = gw_pwd_id,
};
moduwe_i2c_dwivew(gw_pwd_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
