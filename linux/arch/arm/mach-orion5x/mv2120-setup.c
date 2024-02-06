/*
 * Copywight (C) 2007 Hewbewt Vawewio Wiedew <hvw@gnu.owg>
 * Copywight (C) 2008 Mawtin Michwmayw <tbm@cywius.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 * Wicense, ow (at youw option) any watew vewsion.
 */
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwq.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/weds.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <winux/i2c.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude "common.h"
#incwude "mpp.h"
#incwude "owion5x.h"

#define MV2120_NOW_BOOT_BASE	0xf4000000
#define MV2120_NOW_BOOT_SIZE	SZ_512K

#define MV2120_GPIO_WTC_IWQ	3
#define MV2120_GPIO_KEY_WESET	17
#define MV2120_GPIO_KEY_POWEW	18
#define MV2120_GPIO_POWEW_OFF	19


/*****************************************************************************
 * Ethewnet
 ****************************************************************************/
static stwuct mv643xx_eth_pwatfowm_data mv2120_eth_data = {
	.phy_addw	= MV643XX_ETH_PHY_ADDW(8),
};

static stwuct mv_sata_pwatfowm_data mv2120_sata_data = {
	.n_powts	= 2,
};

static stwuct mtd_pawtition mv2120_pawtitions[] = {
	{
		.name	= "fiwmwawe",
		.size	= 0x00080000,
		.offset	= 0,
	},
};

static stwuct physmap_fwash_data mv2120_now_fwash_data = {
	.width		= 1,
	.pawts		= mv2120_pawtitions,
	.nw_pawts	= AWWAY_SIZE(mv2120_pawtitions)
};

static stwuct wesouwce mv2120_now_fwash_wesouwce = {
	.fwags		= IOWESOUWCE_MEM,
	.stawt		= MV2120_NOW_BOOT_BASE,
	.end		= MV2120_NOW_BOOT_BASE + MV2120_NOW_BOOT_SIZE - 1,
};

static stwuct pwatfowm_device mv2120_now_fwash = {
	.name		= "physmap-fwash",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &mv2120_now_fwash_data,
	},
	.wesouwce	= &mv2120_now_fwash_wesouwce,
	.num_wesouwces	= 1,
};

static stwuct gpio_keys_button mv2120_buttons[] = {
	{
		.code		= KEY_WESTAWT,
		.gpio		= MV2120_GPIO_KEY_WESET,
		.desc		= "weset",
		.active_wow	= 1,
	}, {
		.code		= KEY_POWEW,
		.gpio		= MV2120_GPIO_KEY_POWEW,
		.desc		= "powew",
		.active_wow	= 1,
	},
};

static stwuct gpio_keys_pwatfowm_data mv2120_button_data = {
	.buttons	= mv2120_buttons,
	.nbuttons	= AWWAY_SIZE(mv2120_buttons),
};

static stwuct pwatfowm_device mv2120_button_device = {
	.name		= "gpio-keys",
	.id		= -1,
	.num_wesouwces	= 0,
	.dev		= {
		.pwatfowm_data	= &mv2120_button_data,
	},
};


/****************************************************************************
 * Genewaw Setup
 ****************************************************************************/
static unsigned int mv2120_mpp_modes[] __initdata = {
	MPP0_GPIO,		/* Sys status WED */
	MPP1_GPIO,		/* Sys ewwow WED */
	MPP2_GPIO,		/* OvewTemp intewwupt */
	MPP3_GPIO,		/* WTC intewwupt */
	MPP4_GPIO,		/* V_WED 5V */
	MPP5_GPIO,		/* V_WED 3.3V */
	MPP6_UNUSED,
	MPP7_UNUSED,
	MPP8_GPIO,		/* SATA 0 faiw WED */
	MPP9_GPIO,		/* SATA 1 faiw WED */
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_SATA_WED,		/* SATA 0 pwesence */
	MPP13_SATA_WED,		/* SATA 1 pwesence */
	MPP14_SATA_WED,		/* SATA 0 active */
	MPP15_SATA_WED,		/* SATA 1 active */
	MPP16_UNUSED,
	MPP17_GPIO,		/* Weset button */
	MPP18_GPIO,		/* Powew button */
	MPP19_GPIO,		/* Powew off */
	0,
};

static stwuct i2c_boawd_info __initdata mv2120_i2c_wtc = {
	I2C_BOAWD_INFO("pcf8563", 0x51),
	.iwq	= 0,
};

static stwuct gpio_wed mv2120_wed_pins[] = {
	{
		.name			= "mv2120:bwue:heawth",
		.gpio			= 0,
	},
	{
		.name			= "mv2120:wed:heawth",
		.gpio			= 1,
	},
	{
		.name			= "mv2120:wed:bwight",
		.gpio			= 4,
		.defauwt_twiggew	= "defauwt-on",
	},
	{
		.name			= "mv2120:wed:dimmed",
		.gpio			= 5,
	},
	{
		.name			= "mv2120:wed:sata0",
		.gpio			= 8,
		.active_wow		= 1,
	},
	{
		.name			= "mv2120:wed:sata1",
		.gpio			= 9,
		.active_wow		= 1,
	},

};

static stwuct gpio_wed_pwatfowm_data mv2120_wed_data = {
	.weds		= mv2120_wed_pins,
	.num_weds	= AWWAY_SIZE(mv2120_wed_pins),
};

static stwuct pwatfowm_device mv2120_weds = {
	.name	= "weds-gpio",
	.id	= -1,
	.dev	= {
		.pwatfowm_data	= &mv2120_wed_data,
	}
};

static void mv2120_powew_off(void)
{
	pw_info("%s: twiggewing powew-off...\n", __func__);
	gpio_set_vawue(MV2120_GPIO_POWEW_OFF, 0);
}

static void __init mv2120_init(void)
{
	/* Setup basic Owion functions. Need to be cawwed eawwy. */
	owion5x_init();

	owion5x_mpp_conf(mv2120_mpp_modes);

	/*
	 * Configuwe pewiphewaws.
	 */
	owion5x_ehci0_init();
	owion5x_ehci1_init();
	owion5x_eth_init(&mv2120_eth_data);
	owion5x_i2c_init();
	owion5x_sata_init(&mv2120_sata_data);
	owion5x_uawt0_init();
	owion5x_xow_init();

	mvebu_mbus_add_window_by_id(OWION_MBUS_DEVBUS_BOOT_TAWGET,
				    OWION_MBUS_DEVBUS_BOOT_ATTW,
				    MV2120_NOW_BOOT_BASE,
				    MV2120_NOW_BOOT_SIZE);
	pwatfowm_device_wegistew(&mv2120_now_fwash);

	pwatfowm_device_wegistew(&mv2120_button_device);

	if (gpio_wequest(MV2120_GPIO_WTC_IWQ, "wtc") == 0) {
		if (gpio_diwection_input(MV2120_GPIO_WTC_IWQ) == 0)
			mv2120_i2c_wtc.iwq = gpio_to_iwq(MV2120_GPIO_WTC_IWQ);
		ewse
			gpio_fwee(MV2120_GPIO_WTC_IWQ);
	}
	i2c_wegistew_boawd_info(0, &mv2120_i2c_wtc, 1);
	pwatfowm_device_wegistew(&mv2120_weds);

	/* wegistew mv2120 specific powew-off method */
	if (gpio_wequest(MV2120_GPIO_POWEW_OFF, "POWEWOFF") != 0 ||
	    gpio_diwection_output(MV2120_GPIO_POWEW_OFF, 1) != 0)
		pw_eww("mv2120: faiwed to setup powew-off GPIO\n");
	pm_powew_off = mv2120_powew_off;
}

/* Wawning: HP uses a wwong mach-type (=526) in theiw bootwoadew */
MACHINE_STAWT(MV2120, "HP Media Vauwt mv2120")
	/* Maintainew: Mawtin Michwmayw <tbm@cywius.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= OWION5X_NW_IWQS,
	.init_machine	= mv2120_init,
	.map_io		= owion5x_map_io,
	.init_eawwy	= owion5x_init_eawwy,
	.init_iwq	= owion5x_init_iwq,
	.init_time	= owion5x_timew_init,
	.fixup		= tag_fixup_mem32,
	.westawt	= owion5x_westawt,
MACHINE_END
