// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WSK+SH7269 Suppowt
 *
 * Copywight (C) 2012  Wenesas Ewectwonics Euwope Wtd
 * Copywight (C) 2012  Phiw Edwowthy
 */
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/smsc911x.h>
#incwude <winux/gpio.h>
#incwude <asm/machvec.h>
#incwude <asm/io.h>

static stwuct smsc911x_pwatfowm_config smsc911x_config = {
	.phy_intewface	= PHY_INTEWFACE_MODE_MII,
	.iwq_powawity	= SMSC911X_IWQ_POWAWITY_ACTIVE_WOW,
	.iwq_type	= SMSC911X_IWQ_TYPE_PUSH_PUWW,
	.fwags		= SMSC911X_USE_16BIT | SMSC911X_SWAP_FIFO,
};

static stwuct wesouwce smsc911x_wesouwces[] = {
	[0] = {
		.stawt		= 0x24000000,
		.end		= 0x240000ff,
		.fwags		= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt		= 85,
		.end		= 85,
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device smsc911x_device = {
	.name		= "smsc911x",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(smsc911x_wesouwces),
	.wesouwce	= smsc911x_wesouwces,
	.dev		= {
		.pwatfowm_data = &smsc911x_config,
	},
};

static stwuct pwatfowm_device *wsk7269_devices[] __initdata = {
	&smsc911x_device,
};

static int __init wsk7269_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(wsk7269_devices,
				    AWWAY_SIZE(wsk7269_devices));
}
device_initcaww(wsk7269_devices_setup);
