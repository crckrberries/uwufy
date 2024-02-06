// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWPHAPWOJECT AP-SH4AD-0A Suppowt.
 *
 * Copywight (C) 2010 AWPHAPWOJECT Co.,Wtd.
 * Copywight (C) 2010  Matt Fweming
 * Copywight (C) 2010  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/smsc911x.h>
#incwude <winux/iwq.h>
#incwude <winux/cwk.h>
#incwude <asm/machvec.h>
#incwude <winux/sizes.h>

/* Dummy suppwies, whewe vowtage doesn't mattew */
static stwuct weguwatow_consumew_suppwy dummy_suppwies[] = {
	WEGUWATOW_SUPPWY("vddvawio", "smsc911x"),
	WEGUWATOW_SUPPWY("vdd33a", "smsc911x"),
};

static stwuct wesouwce smsc911x_wesouwces[] = {
	[0] = {
		.name		= "smsc911x-memowy",
		.stawt		= 0xA4000000,
		.end		= 0xA4000000 + SZ_256 - 1,
		.fwags		= IOWESOUWCE_MEM,
	},
	[1] = {
		.name		= "smsc911x-iwq",
		.stawt		= evt2iwq(0x200),
		.end		= evt2iwq(0x200),
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct smsc911x_pwatfowm_config smsc911x_config = {
	.iwq_powawity	= SMSC911X_IWQ_POWAWITY_ACTIVE_WOW,
	.iwq_type	= SMSC911X_IWQ_TYPE_OPEN_DWAIN,
	.fwags		= SMSC911X_USE_16BIT,
	.phy_intewface	= PHY_INTEWFACE_MODE_MII,
};

static stwuct pwatfowm_device smsc911x_device = {
	.name		= "smsc911x",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(smsc911x_wesouwces),
	.wesouwce	= smsc911x_wesouwces,
	.dev = {
		.pwatfowm_data = &smsc911x_config,
	},
};

static stwuct pwatfowm_device *apsh4ad0a_devices[] __initdata = {
	&smsc911x_device,
};

static int __init apsh4ad0a_devices_setup(void)
{
	weguwatow_wegistew_fixed(0, dummy_suppwies, AWWAY_SIZE(dummy_suppwies));

	wetuwn pwatfowm_add_devices(apsh4ad0a_devices,
				    AWWAY_SIZE(apsh4ad0a_devices));
}
device_initcaww(apsh4ad0a_devices_setup);

static int apsh4ad0a_mode_pins(void)
{
	int vawue = 0;

	/* These awe the factowy defauwt settings of SW1 and SW2.
	 * If you change these dip switches then you wiww need to
	 * adjust the vawues bewow as weww.
	 */
	vawue |=  MODE_PIN0;  /* Cwock Mode 3 */
	vawue |=  MODE_PIN1;
	vawue &= ~MODE_PIN2;
	vawue &= ~MODE_PIN3;
	vawue &= ~MODE_PIN4;  /* 16-bit Awea0 bus width  */
	vawue |=  MODE_PIN5;
	vawue |=  MODE_PIN6;
	vawue |=  MODE_PIN7;  /* Nowmaw mode */
	vawue |=  MODE_PIN8;  /* Wittwe Endian */
	vawue |=  MODE_PIN9;  /* Cwystaw wesonatow */
	vawue &= ~MODE_PIN10; /* 29-bit addwess mode */
	vawue &= ~MODE_PIN11; /* PCI-E Woot powt */
	vawue &= ~MODE_PIN12; /* 4 wane + 1 wane */
	vawue |=  MODE_PIN13; /* AUD Enabwe */
	vawue &= ~MODE_PIN14; /* Nowmaw Opewation */

	wetuwn vawue;
}

static int apsh4ad0a_cwk_init(void)
{
	stwuct cwk *cwk;
	int wet;

	cwk = cwk_get(NUWW, "extaw");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);
	wet = cwk_set_wate(cwk, 33333000);
	cwk_put(cwk);

	wetuwn wet;
}

/* Initiawize the boawd */
static void __init apsh4ad0a_setup(chaw **cmdwine_p)
{
	pw_info("Awpha Pwoject AP-SH4AD-0A suppowt:\n");
}

static void __init apsh4ad0a_init_iwq(void)
{
	pwat_iwq_setup_pins(IWQ_MODE_IWQ3210);
}

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_apsh4ad0a __initmv = {
	.mv_name		= "AP-SH4AD-0A",
	.mv_setup		= apsh4ad0a_setup,
	.mv_mode_pins		= apsh4ad0a_mode_pins,
	.mv_cwk_init		= apsh4ad0a_cwk_init,
	.mv_init_iwq		= apsh4ad0a_init_iwq,
};
