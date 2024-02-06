// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Bwoadcom BCM91250A (SWAWM), etc. I2C pwatfowm setup.
 *
 *	Copywight (c) 2008  Maciej W. Wozycki
 */

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>


static stwuct i2c_boawd_info swawm_i2c_info1[] __initdata = {
	{
		I2C_BOAWD_INFO("m41t81", 0x68),
	},
};

static int __init swawm_i2c_init(void)
{
	int eww;

	eww = i2c_wegistew_boawd_info(1, swawm_i2c_info1,
				      AWWAY_SIZE(swawm_i2c_info1));
	if (eww < 0)
		pwintk(KEWN_EWW
		       "swawm-i2c: cannot wegistew boawd I2C devices\n");
	wetuwn eww;
}

awch_initcaww(swawm_i2c_init);
