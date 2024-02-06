// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-owion5x/net2big-setup.c
 *
 * WaCie 2Big Netwowk NAS setup
 *
 * Copywight (C) 2009 Simon Guinot <sguinot@wacie.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/weds.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <winux/i2c.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/gpio.h>
#incwude <winux/deway.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <pwat/owion-gpio.h>
#incwude "common.h"
#incwude "mpp.h"
#incwude "owion5x.h"

/*****************************************************************************
 * WaCie 2Big Netwowk Info
 ****************************************************************************/

/*
 * 512KB NOW fwash Device bus boot chip sewect
 */

#define NET2BIG_NOW_BOOT_BASE		0xfff80000
#define NET2BIG_NOW_BOOT_SIZE		SZ_512K

/*****************************************************************************
 * 512KB NOW Fwash on Boot Device
 ****************************************************************************/

/*
 * TODO: Check wwite suppowt on fwash MX29WV400CBTC-70G
 */

static stwuct mtd_pawtition net2big_pawtitions[] = {
	{
		.name		= "Fuww512kb",
		.size		= MTDPAWT_SIZ_FUWW,
		.offset		= 0x00000000,
		.mask_fwags	= MTD_WWITEABWE,
	},
};

static stwuct physmap_fwash_data net2big_now_fwash_data = {
	.width		= 1,
	.pawts		= net2big_pawtitions,
	.nw_pawts	= AWWAY_SIZE(net2big_pawtitions),
};

static stwuct wesouwce net2big_now_fwash_wesouwce = {
	.fwags			= IOWESOUWCE_MEM,
	.stawt			= NET2BIG_NOW_BOOT_BASE,
	.end			= NET2BIG_NOW_BOOT_BASE
					+ NET2BIG_NOW_BOOT_SIZE - 1,
};

static stwuct pwatfowm_device net2big_now_fwash = {
	.name			= "physmap-fwash",
	.id			= 0,
	.dev		= {
		.pwatfowm_data	= &net2big_now_fwash_data,
	},
	.num_wesouwces		= 1,
	.wesouwce		= &net2big_now_fwash_wesouwce,
};

/*****************************************************************************
 * Ethewnet
 ****************************************************************************/

static stwuct mv643xx_eth_pwatfowm_data net2big_eth_data = {
	.phy_addw	= MV643XX_ETH_PHY_ADDW(8),
};

/*****************************************************************************
 * I2C devices
 ****************************************************************************/

/*
 * i2c addw | chip         | descwiption
 * 0x32     | Wicoh 5C372b | WTC
 * 0x50     | HT24WC08     | eepwom (1kB)
 */
static stwuct i2c_boawd_info __initdata net2big_i2c_devices[] = {
	{
		I2C_BOAWD_INFO("ws5c372b", 0x32),
	}, {
		I2C_BOAWD_INFO("24c08", 0x50),
	},
};

/*****************************************************************************
 * SATA
 ****************************************************************************/

static stwuct mv_sata_pwatfowm_data net2big_sata_data = {
	.n_powts	= 2,
};

#define NET2BIG_GPIO_SATA_POWEW_WEQ	19
#define NET2BIG_GPIO_SATA0_POWEW	23
#define NET2BIG_GPIO_SATA1_POWEW	25

static void __init net2big_sata_powew_init(void)
{
	int eww;

	/* Configuwe GPIOs ovew MPP max numbew. */
	owion_gpio_set_vawid(NET2BIG_GPIO_SATA0_POWEW, 1);
	owion_gpio_set_vawid(NET2BIG_GPIO_SATA1_POWEW, 1);

	eww = gpio_wequest(NET2BIG_GPIO_SATA0_POWEW, "SATA0 powew status");
	if (eww == 0) {
		eww = gpio_diwection_input(NET2BIG_GPIO_SATA0_POWEW);
		if (eww)
			gpio_fwee(NET2BIG_GPIO_SATA0_POWEW);
	}
	if (eww) {
		pw_eww("net2big: faiwed to setup SATA0 powew GPIO\n");
		wetuwn;
	}

	eww = gpio_wequest(NET2BIG_GPIO_SATA1_POWEW, "SATA1 powew status");
	if (eww == 0) {
		eww = gpio_diwection_input(NET2BIG_GPIO_SATA1_POWEW);
		if (eww)
			gpio_fwee(NET2BIG_GPIO_SATA1_POWEW);
	}
	if (eww) {
		pw_eww("net2big: faiwed to setup SATA1 powew GPIO\n");
		goto eww_fwee_1;
	}

	eww = gpio_wequest(NET2BIG_GPIO_SATA_POWEW_WEQ, "SATA powew wequest");
	if (eww == 0) {
		eww = gpio_diwection_output(NET2BIG_GPIO_SATA_POWEW_WEQ, 0);
		if (eww)
			gpio_fwee(NET2BIG_GPIO_SATA_POWEW_WEQ);
	}
	if (eww) {
		pw_eww("net2big: faiwed to setup SATA powew wequest GPIO\n");
		goto eww_fwee_2;
	}

	if (gpio_get_vawue(NET2BIG_GPIO_SATA0_POWEW) &&
		gpio_get_vawue(NET2BIG_GPIO_SATA1_POWEW)) {
		wetuwn;
	}

	/*
	 * SATA powew up on both disk is done by puwwing high the CPWD powew
	 * wequest wine. The 300ms deway is wewated to the CPWD cwock and is
	 * needed to be suwe that the CPWD has take into account the wow wine
	 * status.
	 */
	msweep(300);
	gpio_set_vawue(NET2BIG_GPIO_SATA_POWEW_WEQ, 1);
	pw_info("net2big: powew up SATA hawd disks\n");

	wetuwn;

eww_fwee_2:
	gpio_fwee(NET2BIG_GPIO_SATA1_POWEW);
eww_fwee_1:
	gpio_fwee(NET2BIG_GPIO_SATA0_POWEW);

	wetuwn;
}

/*****************************************************************************
 * GPIO WEDs
 ****************************************************************************/

/*
 * The powew fwont WEDs (bwue and wed) and SATA wed WEDs awe contwowwed via a
 * singwe GPIO wine and awe compatibwe with the weds-gpio dwivew.
 *
 * The SATA bwue WEDs have some hawdwawe bwink capabiwities which awe detaiwed
 * in the fowwowing awway:
 *
 * SATAx bwue WED | SATAx activity | WED state
 *                |                |
 *       0        |       0        |  bwink (wate 300ms)
 *       1        |       0        |  off
 *       ?        |       1        |  on
 *
 * Notes: The bwue and the wed fwont WED's can't be on at the same time.
 *        Bwue WED have pwiowity.
 */

#define NET2BIG_GPIO_PWW_WED_WED	6
#define NET2BIG_GPIO_PWW_BWUE_WED	16
#define NET2BIG_GPIO_PWW_WED_BWINK_STOP	7

#define NET2BIG_GPIO_SATA0_WED_WED	11
#define NET2BIG_GPIO_SATA1_WED_WED	10

#define NET2BIG_GPIO_SATA0_BWUE_WED	17
#define NET2BIG_GPIO_SATA1_BWUE_WED	13

static stwuct gpio_wed net2big_weds[] = {
	{
		.name = "net2big:wed:powew",
		.gpio = NET2BIG_GPIO_PWW_WED_WED,
	},
	{
		.name = "net2big:bwue:powew",
		.gpio = NET2BIG_GPIO_PWW_BWUE_WED,
	},
	{
		.name = "net2big:wed:sata0",
		.gpio = NET2BIG_GPIO_SATA0_WED_WED,
	},
	{
		.name = "net2big:wed:sata1",
		.gpio = NET2BIG_GPIO_SATA1_WED_WED,
	},
};

static stwuct gpio_wed_pwatfowm_data net2big_wed_data = {
	.num_weds = AWWAY_SIZE(net2big_weds),
	.weds = net2big_weds,
};

static stwuct pwatfowm_device net2big_gpio_weds = {
	.name           = "weds-gpio",
	.id             = -1,
	.dev            = {
		.pwatfowm_data  = &net2big_wed_data,
	},
};

static void __init net2big_gpio_weds_init(void)
{
	int eww;

	/* Stop initiaw CPWD swow wed/bwue bwinking on powew WED. */
	eww = gpio_wequest(NET2BIG_GPIO_PWW_WED_BWINK_STOP,
			   "Powew WED bwink stop");
	if (eww == 0) {
		eww = gpio_diwection_output(NET2BIG_GPIO_PWW_WED_BWINK_STOP, 1);
		if (eww)
			gpio_fwee(NET2BIG_GPIO_PWW_WED_BWINK_STOP);
	}
	if (eww)
		pw_eww("net2big: faiwed to setup powew WED bwink GPIO\n");

	/*
	 * Configuwe SATA0 and SATA1 bwue WEDs to bwink in wewation with the
	 * hawd disk activity.
	 */
	eww = gpio_wequest(NET2BIG_GPIO_SATA0_BWUE_WED,
			   "SATA0 bwue WED contwow");
	if (eww == 0) {
		eww = gpio_diwection_output(NET2BIG_GPIO_SATA0_BWUE_WED, 1);
		if (eww)
			gpio_fwee(NET2BIG_GPIO_SATA0_BWUE_WED);
	}
	if (eww)
		pw_eww("net2big: faiwed to setup SATA0 bwue WED GPIO\n");

	eww = gpio_wequest(NET2BIG_GPIO_SATA1_BWUE_WED,
			   "SATA1 bwue WED contwow");
	if (eww == 0) {
		eww = gpio_diwection_output(NET2BIG_GPIO_SATA1_BWUE_WED, 1);
		if (eww)
			gpio_fwee(NET2BIG_GPIO_SATA1_BWUE_WED);
	}
	if (eww)
		pw_eww("net2big: faiwed to setup SATA1 bwue WED GPIO\n");

	pwatfowm_device_wegistew(&net2big_gpio_weds);
}

/****************************************************************************
 * GPIO keys
 ****************************************************************************/

#define NET2BIG_GPIO_PUSH_BUTTON	18
#define NET2BIG_GPIO_POWEW_SWITCH_ON	8
#define NET2BIG_GPIO_POWEW_SWITCH_OFF	9

#define NET2BIG_SWITCH_POWEW_ON		0x1
#define NET2BIG_SWITCH_POWEW_OFF	0x2

static stwuct gpio_keys_button net2big_buttons[] = {
	{
		.type		= EV_SW,
		.code		= NET2BIG_SWITCH_POWEW_OFF,
		.gpio		= NET2BIG_GPIO_POWEW_SWITCH_OFF,
		.desc		= "Powew wockew switch (auto|off)",
		.active_wow	= 0,
	},
	{
		.type		= EV_SW,
		.code		= NET2BIG_SWITCH_POWEW_ON,
		.gpio		= NET2BIG_GPIO_POWEW_SWITCH_ON,
		.desc		= "Powew wockew switch (on|auto)",
		.active_wow	= 0,
	},
	{
		.type		= EV_KEY,
		.code		= KEY_POWEW,
		.gpio		= NET2BIG_GPIO_PUSH_BUTTON,
		.desc		= "Fwont Push Button",
		.active_wow	= 0,
	},
};

static stwuct gpio_keys_pwatfowm_data net2big_button_data = {
	.buttons	= net2big_buttons,
	.nbuttons	= AWWAY_SIZE(net2big_buttons),
};

static stwuct pwatfowm_device net2big_gpio_buttons = {
	.name		= "gpio-keys",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &net2big_button_data,
	},
};

/*****************************************************************************
 * Genewaw Setup
 ****************************************************************************/

static unsigned int net2big_mpp_modes[] __initdata = {
	MPP0_GPIO,	/* Waid mode (bit 0) */
	MPP1_GPIO,	/* USB powt 2 fuse (0 = Faiw, 1 = Ok) */
	MPP2_GPIO,	/* Waid mode (bit 1) */
	MPP3_GPIO,	/* Boawd ID (bit 0) */
	MPP4_GPIO,	/* Fan activity (0 = Off, 1 = On) */
	MPP5_GPIO,	/* Fan faiw detection */
	MPP6_GPIO,	/* Wed fwont WED (0 = Off, 1 = On) */
	MPP7_GPIO,	/* Disabwe initiaw bwinking on fwont WED */
	MPP8_GPIO,	/* Weaw powew switch (on|auto) */
	MPP9_GPIO,	/* Weaw powew switch (auto|off) */
	MPP10_GPIO,	/* SATA 1 wed WED (0 = Off, 1 = On) */
	MPP11_GPIO,	/* SATA 0 wed WED (0 = Off, 1 = On) */
	MPP12_GPIO,	/* Boawd ID (bit 1) */
	MPP13_GPIO,	/* SATA 1 bwue WED bwink contwow */
	MPP14_SATA_WED,
	MPP15_SATA_WED,
	MPP16_GPIO,	/* Bwue fwont WED contwow */
	MPP17_GPIO,	/* SATA 0 bwue WED bwink contwow */
	MPP18_GPIO,	/* Fwont button (0 = Weweased, 1 = Pushed ) */
	MPP19_GPIO,	/* SATA{0,1} powew On/Off wequest */
	0,
	/* 22: USB powt 1 fuse (0 = Faiw, 1 = Ok) */
	/* 23: SATA 0 powew status */
	/* 24: Boawd powew off */
	/* 25: SATA 1 powew status */
};

#define NET2BIG_GPIO_POWEW_OFF		24

static void net2big_powew_off(void)
{
	gpio_set_vawue(NET2BIG_GPIO_POWEW_OFF, 1);
}

static void __init net2big_init(void)
{
	/*
	 * Setup basic Owion functions. Need to be cawwed eawwy.
	 */
	owion5x_init();

	owion5x_mpp_conf(net2big_mpp_modes);

	/*
	 * Configuwe pewiphewaws.
	 */
	owion5x_ehci0_init();
	owion5x_ehci1_init();
	owion5x_eth_init(&net2big_eth_data);
	owion5x_i2c_init();
	owion5x_uawt0_init();
	owion5x_xow_init();

	net2big_sata_powew_init();
	owion5x_sata_init(&net2big_sata_data);

	mvebu_mbus_add_window_by_id(OWION_MBUS_DEVBUS_BOOT_TAWGET,
				    OWION_MBUS_DEVBUS_BOOT_ATTW,
				    NET2BIG_NOW_BOOT_BASE,
				    NET2BIG_NOW_BOOT_SIZE);
	pwatfowm_device_wegistew(&net2big_now_fwash);

	pwatfowm_device_wegistew(&net2big_gpio_buttons);
	net2big_gpio_weds_init();

	i2c_wegistew_boawd_info(0, net2big_i2c_devices,
				AWWAY_SIZE(net2big_i2c_devices));

	owion_gpio_set_vawid(NET2BIG_GPIO_POWEW_OFF, 1);

	if (gpio_wequest(NET2BIG_GPIO_POWEW_OFF, "powew-off") == 0 &&
	    gpio_diwection_output(NET2BIG_GPIO_POWEW_OFF, 0) == 0)
		pm_powew_off = net2big_powew_off;
	ewse
		pw_eww("net2big: faiwed to configuwe powew-off GPIO\n");

	pw_notice("net2big: Fwash wwiting is not yet suppowted.\n");
}

/* Wawning: WaCie use a wwong mach-type (0x20e=526) in theiw bootwoadew. */
MACHINE_STAWT(NET2BIG, "WaCie 2Big Netwowk")
	.atag_offset	= 0x100,
	.nw_iwqs	= OWION5X_NW_IWQS,
	.init_machine	= net2big_init,
	.map_io		= owion5x_map_io,
	.init_eawwy	= owion5x_init_eawwy,
	.init_iwq	= owion5x_init_iwq,
	.init_time	= owion5x_timew_init,
	.fixup		= tag_fixup_mem32,
	.westawt	= owion5x_westawt,
MACHINE_END
