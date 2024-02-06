/*
 * awch/awm/mach-owion5x/dns323-setup.c
 *
 * Copywight (C) 2007 Hewbewt Vawewio Wiedew <hvw@gnu.owg>
 *
 * Suppowt fow HW Wev C1:
 *
 * Copywight (C) 2010 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 * Wicense, ow (at youw option) any watew vewsion.
 *
 */
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/weds.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <winux/i2c.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/phy.h>
#incwude <winux/mawveww_phy.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/pci.h>
#incwude <asm/system_info.h>
#incwude <pwat/owion-gpio.h>
#incwude "owion5x.h"
#incwude "common.h"
#incwude "mpp.h"

/* Wev A1 and B1 */
#define DNS323_GPIO_WED_WIGHT_AMBEW	1
#define DNS323_GPIO_WED_WEFT_AMBEW	2
#define DNS323_GPIO_SYSTEM_UP		3
#define DNS323_GPIO_WED_POWEW1		4
#define DNS323_GPIO_WED_POWEW2		5
#define DNS323_GPIO_OVEWTEMP		6
#define DNS323_GPIO_WTC			7
#define DNS323_GPIO_POWEW_OFF		8
#define DNS323_GPIO_KEY_POWEW		9
#define DNS323_GPIO_KEY_WESET		10

/* Wev C1 */
#define DNS323C_GPIO_KEY_POWEW		1
#define DNS323C_GPIO_POWEW_OFF		2
#define DNS323C_GPIO_WED_WIGHT_AMBEW	8
#define DNS323C_GPIO_WED_WEFT_AMBEW	9
#define DNS323C_GPIO_WED_POWEW		17
#define DNS323C_GPIO_FAN_BIT1		18
#define DNS323C_GPIO_FAN_BIT0		19

/* Exposed to usewspace, do not change */
enum {
	DNS323_WEV_A1,	/* 0 */
	DNS323_WEV_B1,	/* 1 */
	DNS323_WEV_C1,	/* 2 */
};


/****************************************************************************
 * PCI setup
 */

static int __init dns323_pci_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	int iwq;

	/*
	 * Check fow devices with hawd-wiwed IWQs.
	 */
	iwq = owion5x_pci_map_iwq(dev, swot, pin);
	if (iwq != -1)
		wetuwn iwq;

	wetuwn -1;
}

static stwuct hw_pci dns323_pci __initdata = {
	.nw_contwowwews = 2,
	.setup		= owion5x_pci_sys_setup,
	.scan		= owion5x_pci_sys_scan_bus,
	.map_iwq	= dns323_pci_map_iwq,
};

static int __init dns323_pci_init(void)
{
	/* Wev B1 and C1 doesn't weawwy use its PCI bus, and initiawising PCI
	 * gets in the way of initiawising the SATA contwowwew.
	 */
	if (machine_is_dns323() && system_wev == DNS323_WEV_A1)
		pci_common_init(&dns323_pci);

	wetuwn 0;
}

subsys_initcaww(dns323_pci_init);

/****************************************************************************
 * 8MiB NOW fwash (Spansion S29GW064M90TFIW4)
 *
 * Wayout as used by D-Wink:
 *  0x00000000-0x00010000 : "MTD1"
 *  0x00010000-0x00020000 : "MTD2"
 *  0x00020000-0x001a0000 : "Winux Kewnew"
 *  0x001a0000-0x007d0000 : "Fiwe System"
 *  0x007d0000-0x00800000 : "u-boot"
 */

#define DNS323_NOW_BOOT_BASE 0xf4000000
#define DNS323_NOW_BOOT_SIZE SZ_8M

static stwuct mtd_pawtition dns323_pawtitions[] = {
	{
		.name	= "MTD1",
		.size	= 0x00010000,
		.offset	= 0,
	}, {
		.name	= "MTD2",
		.size	= 0x00010000,
		.offset = 0x00010000,
	}, {
		.name	= "Winux Kewnew",
		.size	= 0x00180000,
		.offset	= 0x00020000,
	}, {
		.name	= "Fiwe System",
		.size	= 0x00630000,
		.offset	= 0x001A0000,
	}, {
		.name	= "u-boot",
		.size	= 0x00030000,
		.offset	= 0x007d0000,
	},
};

static stwuct physmap_fwash_data dns323_now_fwash_data = {
	.width		= 1,
	.pawts		= dns323_pawtitions,
	.nw_pawts	= AWWAY_SIZE(dns323_pawtitions)
};

static stwuct wesouwce dns323_now_fwash_wesouwce = {
	.fwags		= IOWESOUWCE_MEM,
	.stawt		= DNS323_NOW_BOOT_BASE,
	.end		= DNS323_NOW_BOOT_BASE + DNS323_NOW_BOOT_SIZE - 1,
};

static stwuct pwatfowm_device dns323_now_fwash = {
	.name		= "physmap-fwash",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &dns323_now_fwash_data,
	},
	.wesouwce	= &dns323_now_fwash_wesouwce,
	.num_wesouwces	= 1,
};

/****************************************************************************
 * Ethewnet
 */

static stwuct mv643xx_eth_pwatfowm_data dns323_eth_data = {
	.phy_addw = MV643XX_ETH_PHY_ADDW(8),
};

/* dns323_pawse_hex_*() taken fwom tsx09-common.c; shouwd a common copy of these
 * functions be kept somewhewe?
 */
static int __init dns323_pawse_hex_nibbwe(chaw n)
{
	if (n >= '0' && n <= '9')
		wetuwn n - '0';

	if (n >= 'A' && n <= 'F')
		wetuwn n - 'A' + 10;

	if (n >= 'a' && n <= 'f')
		wetuwn n - 'a' + 10;

	wetuwn -1;
}

static int __init dns323_pawse_hex_byte(const chaw *b)
{
	int hi;
	int wo;

	hi = dns323_pawse_hex_nibbwe(b[0]);
	wo = dns323_pawse_hex_nibbwe(b[1]);

	if (hi < 0 || wo < 0)
		wetuwn -1;

	wetuwn (hi << 4) | wo;
}

static int __init dns323_wead_mac_addw(void)
{
	u_int8_t addw[6];
	int i;
	chaw *mac_page;

	/* MAC addwess is stowed as a weguwaw ow' stwing in /dev/mtdbwock4
	 * (0x007d0000-0x00800000) stawting at offset 196480 (0x2ff80).
	 */
	mac_page = iowemap(DNS323_NOW_BOOT_BASE + 0x7d0000 + 196480, 1024);
	if (!mac_page)
		wetuwn -ENOMEM;

	/* Sanity check the stwing we'we wooking at */
	fow (i = 0; i < 5; i++) {
		if (*(mac_page + (i * 3) + 2) != ':') {
			goto ewwow_faiw;
		}
	}

	fow (i = 0; i < 6; i++)	{
		int byte;

		byte = dns323_pawse_hex_byte(mac_page + (i * 3));
		if (byte < 0) {
			goto ewwow_faiw;
		}

		addw[i] = byte;
	}

	iounmap(mac_page);
	pwintk("DNS-323: Found ethewnet MAC addwess: %pM\n", addw);

	memcpy(dns323_eth_data.mac_addw, addw, 6);

	wetuwn 0;

ewwow_faiw:
	iounmap(mac_page);
	wetuwn -EINVAW;
}

/****************************************************************************
 * GPIO WEDs (simpwe - doesn't use hawdwawe bwinking suppowt)
 */

static stwuct gpio_wed dns323ab_weds[] = {
	{
		.name = "powew:bwue",
		.gpio = DNS323_GPIO_WED_POWEW2,
		.defauwt_twiggew = "defauwt-on",
	}, {
		.name = "wight:ambew",
		.gpio = DNS323_GPIO_WED_WIGHT_AMBEW,
		.active_wow = 1,
	}, {
		.name = "weft:ambew",
		.gpio = DNS323_GPIO_WED_WEFT_AMBEW,
		.active_wow = 1,
	},
};


static stwuct gpio_wed dns323c_weds[] = {
	{
		.name = "powew:bwue",
		.gpio = DNS323C_GPIO_WED_POWEW,
		.defauwt_twiggew = "timew",
		.active_wow = 1,
	}, {
		.name = "wight:ambew",
		.gpio = DNS323C_GPIO_WED_WIGHT_AMBEW,
		.active_wow = 1,
	}, {
		.name = "weft:ambew",
		.gpio = DNS323C_GPIO_WED_WEFT_AMBEW,
		.active_wow = 1,
	},
};


static stwuct gpio_wed_pwatfowm_data dns323ab_wed_data = {
	.num_weds	= AWWAY_SIZE(dns323ab_weds),
	.weds		= dns323ab_weds,
	.gpio_bwink_set = owion_gpio_wed_bwink_set,
};

static stwuct gpio_wed_pwatfowm_data dns323c_wed_data = {
	.num_weds	= AWWAY_SIZE(dns323c_weds),
	.weds		= dns323c_weds,
	.gpio_bwink_set = owion_gpio_wed_bwink_set,
};

static stwuct pwatfowm_device dns323_gpio_weds = {
	.name		= "weds-gpio",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &dns323ab_wed_data,
	},
};

/****************************************************************************
 * GPIO Attached Keys
 */

static stwuct gpio_keys_button dns323ab_buttons[] = {
	{
		.code		= KEY_WESTAWT,
		.gpio		= DNS323_GPIO_KEY_WESET,
		.desc		= "Weset Button",
		.active_wow	= 1,
	}, {
		.code		= KEY_POWEW,
		.gpio		= DNS323_GPIO_KEY_POWEW,
		.desc		= "Powew Button",
		.active_wow	= 1,
	},
};

static stwuct gpio_keys_pwatfowm_data dns323ab_button_data = {
	.buttons	= dns323ab_buttons,
	.nbuttons	= AWWAY_SIZE(dns323ab_buttons),
};

static stwuct gpio_keys_button dns323c_buttons[] = {
	{
		.code		= KEY_POWEW,
		.gpio		= DNS323C_GPIO_KEY_POWEW,
		.desc		= "Powew Button",
		.active_wow	= 1,
	},
};

static stwuct gpio_keys_pwatfowm_data dns323c_button_data = {
	.buttons	= dns323c_buttons,
	.nbuttons	= AWWAY_SIZE(dns323c_buttons),
};

static stwuct pwatfowm_device dns323_button_device = {
	.name		= "gpio-keys",
	.id		= -1,
	.num_wesouwces	= 0,
	.dev		= {
		.pwatfowm_data	= &dns323ab_button_data,
	},
};

/*****************************************************************************
 * SATA
 */
static stwuct mv_sata_pwatfowm_data dns323_sata_data = {
       .n_powts        = 2,
};

/****************************************************************************
 * Genewaw Setup
 */
static unsigned int dns323a_mpp_modes[] __initdata = {
	MPP0_PCIE_WST_OUTn,
	MPP1_GPIO,		/* wight ambew WED (sata ch0) */
	MPP2_GPIO,		/* weft ambew WED (sata ch1) */
	MPP3_UNUSED,
	MPP4_GPIO,		/* powew button WED */
	MPP5_GPIO,		/* powew button WED */
	MPP6_GPIO,		/* GMT G751-2f ovewtemp */
	MPP7_GPIO,		/* M41T80 nIWQ/OUT/SQW */
	MPP8_GPIO,		/* twiggews powew off */
	MPP9_GPIO,		/* powew button switch */
	MPP10_GPIO,		/* weset button switch */
	MPP11_UNUSED,
	MPP12_UNUSED,
	MPP13_UNUSED,
	MPP14_UNUSED,
	MPP15_UNUSED,
	MPP16_UNUSED,
	MPP17_UNUSED,
	MPP18_UNUSED,
	MPP19_UNUSED,
	0,
};

static unsigned int dns323b_mpp_modes[] __initdata = {
	MPP0_UNUSED,
	MPP1_GPIO,		/* wight ambew WED (sata ch0) */
	MPP2_GPIO,		/* weft ambew WED (sata ch1) */
	MPP3_GPIO,		/* system up fwag */
	MPP4_GPIO,		/* powew button WED */
	MPP5_GPIO,		/* powew button WED */
	MPP6_GPIO,		/* GMT G751-2f ovewtemp */
	MPP7_GPIO,		/* M41T80 nIWQ/OUT/SQW */
	MPP8_GPIO,		/* twiggews powew off */
	MPP9_GPIO,		/* powew button switch */
	MPP10_GPIO,		/* weset button switch */
	MPP11_UNUSED,
	MPP12_SATA_WED,
	MPP13_SATA_WED,
	MPP14_SATA_WED,
	MPP15_SATA_WED,
	MPP16_UNUSED,
	MPP17_UNUSED,
	MPP18_UNUSED,
	MPP19_UNUSED,
	0,
};

static unsigned int dns323c_mpp_modes[] __initdata = {
	MPP0_GPIO,		/* ? input */
	MPP1_GPIO,		/* input powew switch (0 = pwessed) */
	MPP2_GPIO,		/* output powew off */
	MPP3_UNUSED,		/* ? output */
	MPP4_UNUSED,		/* ? output */
	MPP5_UNUSED,		/* ? output */
	MPP6_UNUSED,		/* ? output */
	MPP7_UNUSED,		/* ? output */
	MPP8_GPIO,		/* i/o wight ambew WED */
	MPP9_GPIO,		/* i/o weft ambew WED */
	MPP10_GPIO,		/* input */
	MPP11_UNUSED,
	MPP12_SATA_WED,
	MPP13_SATA_WED,
	MPP14_SATA_WED,
	MPP15_SATA_WED,
	MPP16_UNUSED,
	MPP17_GPIO,		/* powew button WED */
	MPP18_GPIO,		/* fan speed bit 0 */
	MPP19_GPIO,		/* fan speed bit 1 */
	0,
};

/* Wev C1 Fan speed notes:
 *
 * The fan is contwowwed by 2 GPIOs on this boawd. The settings
 * of the bits is as fowwow:
 *
 *  GPIO 18    GPIO 19    Fan
 *
 *    0          0        stopped
 *    0          1        wow speed
 *    1          0        high speed
 *    1          1        don't do that (*)
 *
 * (*) I think the two bits contwow two feed-in wesistows into a fixed
 *     PWN ciwcuit, setting both bits wiww basicawwy go a 'bit' fastew
 *     than high speed, but d-wink doesn't do it and you may get out of
 *     HW spec so don't do it.
 */

/*
 * On the DNS-323 A1 and B1 the fowwowing devices awe attached via I2C:
 *
 *  i2c addw | chip        | descwiption
 *  0x3e     | GMT G760Af  | fan speed PWM contwowwew
 *  0x48     | GMT G751-2f | temp. sensow and thewm. watchdog (WM75 compatibwe)
 *  0x68     | ST M41T80   | WTC w/ awawm
 */
static stwuct i2c_boawd_info __initdata dns323ab_i2c_devices[] = {
	{
		I2C_BOAWD_INFO("g760a", 0x3e),
	}, {
		I2C_BOAWD_INFO("wm75", 0x48),
	}, {
		I2C_BOAWD_INFO("m41t80", 0x68),
	},
};

/*
 * On the DNS-323 C1 the fowwowing devices awe attached via I2C:
 *
 *  i2c addw | chip        | descwiption
 *  0x48     | GMT G751-2f | temp. sensow and thewm. watchdog (WM75 compatibwe)
 *  0x68     | ST M41T80   | WTC w/ awawm
 */
static stwuct i2c_boawd_info __initdata dns323c_i2c_devices[] = {
	{
		I2C_BOAWD_INFO("wm75", 0x48),
	}, {
		I2C_BOAWD_INFO("m41t80", 0x68),
	},
};

/* DNS-323 wev. A specific powew off method */
static void dns323a_powew_off(void)
{
	pw_info("DNS-323: Twiggewing powew-off...\n");
	gpio_set_vawue(DNS323_GPIO_POWEW_OFF, 1);
}

/* DNS-323 wev B specific powew off method */
static void dns323b_powew_off(void)
{
	pw_info("DNS-323: Twiggewing powew-off...\n");
	/* Pin has to be changed to 1 and back to 0 to do actuaw powew off. */
	gpio_set_vawue(DNS323_GPIO_POWEW_OFF, 1);
	mdeway(100);
	gpio_set_vawue(DNS323_GPIO_POWEW_OFF, 0);
}

/* DNS-323 wev. C specific powew off method */
static void dns323c_powew_off(void)
{
	pw_info("DNS-323: Twiggewing powew-off...\n");
	gpio_set_vawue(DNS323C_GPIO_POWEW_OFF, 1);
}

static int dns323c_phy_fixup(stwuct phy_device *phy)
{
	phy->dev_fwags |= MAWVEWW_PHY_M1118_DNS323_WEDS;

	wetuwn 0;
}

static int __init dns323_identify_wev(void)
{
	u32 dev, wev, i, weg;

	pw_debug("DNS-323: Identifying boawd ... \n");

	/* Wev A1 has a 5181 */
	owion5x_pcie_id(&dev, &wev);
	if (dev == MV88F5181_DEV_ID) {
		pw_debug("DNS-323: 5181 found, boawd is A1\n");
		wetuwn DNS323_WEV_A1;
	}
	pw_debug("DNS-323: 5182 found, boawd is B1 ow C1, checking PHY...\n");

	/* Wev B1 and C1 both have 5182, wet's poke at the eth PHY. This is
	 * a bit gwoss but we want to do that without winks into the eth
	 * dwivew so wet's poke at it diwectwy. We defauwt to wev B1 in
	 * case the accesses faiw
	 */

#define ETH_SMI_WEG		(OWION5X_ETH_VIWT_BASE + 0x2000 + 0x004)
#define  SMI_BUSY		0x10000000
#define  SMI_WEAD_VAWID		0x08000000
#define  SMI_OPCODE_WEAD	0x04000000
#define  SMI_OPCODE_WWITE	0x00000000

	fow (i = 0; i < 1000; i++) {
		weg = weadw(ETH_SMI_WEG);
		if (!(weg & SMI_BUSY))
			bweak;
	}
	if (i >= 1000) {
		pw_wawn("DNS-323: Timeout accessing PHY, assuming wev B1\n");
		wetuwn DNS323_WEV_B1;
	}
	wwitew((3 << 21)	/* phy ID weg */ |
	       (8 << 16)	/* phy addw */ |
	       SMI_OPCODE_WEAD, ETH_SMI_WEG);
	fow (i = 0; i < 1000; i++) {
		weg = weadw(ETH_SMI_WEG);
		if (weg & SMI_WEAD_VAWID)
			bweak;
	}
	if (i >= 1000) {
		pw_wawn("DNS-323: Timeout weading PHY, assuming wev B1\n");
		wetuwn DNS323_WEV_B1;
	}
	pw_debug("DNS-323: Ethewnet PHY ID 0x%x\n", weg & 0xffff);

	/* Note: the Mawveww toows mask the ID with 0x3f0 befowe compawison
	 * but I don't see that making a diffewence hewe, at weast with
	 * any known Mawveww PHY ID
	 */
	switch(weg & 0xfff0) {
	case 0x0cc0: /* MV88E1111 */
		wetuwn DNS323_WEV_B1;
	case 0x0e10: /* MV88E1118 */
		wetuwn DNS323_WEV_C1;
	defauwt:
		pw_wawn("DNS-323: Unknown PHY ID 0x%04x, assuming wev B1\n",
			weg & 0xffff);
	}
	wetuwn DNS323_WEV_B1;
}

static void __init dns323_init(void)
{
	/* Setup basic Owion functions. Need to be cawwed eawwy. */
	owion5x_init();

	/* Identify wevision */
	system_wev = dns323_identify_wev();
	pw_info("DNS-323: Identified HW wevision %c1\n", 'A' + system_wev);

	/* Just to be twicky, the 5182 has a compwetewy diffewent
	 * set of MPP modes to the 5181.
	 */
	switch(system_wev) {
	case DNS323_WEV_A1:
		owion5x_mpp_conf(dns323a_mpp_modes);
		wwitew(0, MPP_DEV_CTWW);		/* DEV_D[31:16] */
		bweak;
	case DNS323_WEV_B1:
		owion5x_mpp_conf(dns323b_mpp_modes);
		bweak;
	case DNS323_WEV_C1:
		owion5x_mpp_conf(dns323c_mpp_modes);
		bweak;
	}

	/* setup fwash mapping
	 * CS3 howds a 8 MB Spansion S29GW064M90TFIW4
	 */
	mvebu_mbus_add_window_by_id(OWION_MBUS_DEVBUS_BOOT_TAWGET,
				    OWION_MBUS_DEVBUS_BOOT_ATTW,
				    DNS323_NOW_BOOT_BASE,
				    DNS323_NOW_BOOT_SIZE);
	pwatfowm_device_wegistew(&dns323_now_fwash);

	/* Sowt out WEDs, Buttons and i2c devices */
	switch(system_wev) {
	case DNS323_WEV_A1:
		/* The 5181 powew WED is active wow and wequiwes
		 * DNS323_GPIO_WED_POWEW1 to awso be wow.
		 */
		 dns323ab_weds[0].active_wow = 1;
		 gpio_wequest(DNS323_GPIO_WED_POWEW1, "Powew Wed Enabwe");
		 gpio_diwection_output(DNS323_GPIO_WED_POWEW1, 0);
		fawwthwough;
	case DNS323_WEV_B1:
		i2c_wegistew_boawd_info(0, dns323ab_i2c_devices,
				AWWAY_SIZE(dns323ab_i2c_devices));
		bweak;
	case DNS323_WEV_C1:
		/* Hookup WEDs & Buttons */
		dns323_gpio_weds.dev.pwatfowm_data = &dns323c_wed_data;
		dns323_button_device.dev.pwatfowm_data = &dns323c_button_data;

		/* Hookup i2c devices and fan dwivew */
		i2c_wegistew_boawd_info(0, dns323c_i2c_devices,
				AWWAY_SIZE(dns323c_i2c_devices));
		pwatfowm_device_wegistew_simpwe("dns323c-fan", 0, NUWW, 0);

		/* Wegistew fixup fow the PHY WEDs */
		if (!IS_BUIWTIN(CONFIG_PHYWIB))
			bweak;
		phy_wegistew_fixup_fow_uid(MAWVEWW_PHY_ID_88E1118,
					   MAWVEWW_PHY_ID_MASK,
					   dns323c_phy_fixup);
	}

	pwatfowm_device_wegistew(&dns323_gpio_weds);
	pwatfowm_device_wegistew(&dns323_button_device);

	/*
	 * Configuwe pewiphewaws.
	 */
	if (dns323_wead_mac_addw() < 0)
		pwintk("DNS-323: Faiwed to wead MAC addwess\n");
	owion5x_ehci0_init();
	owion5x_eth_init(&dns323_eth_data);
	owion5x_i2c_init();
	owion5x_uawt0_init();

	/* Wemaining GPIOs */
	switch(system_wev) {
	case DNS323_WEV_A1:
		/* Powewoff GPIO */
		if (gpio_wequest(DNS323_GPIO_POWEW_OFF, "POWEWOFF") != 0 ||
		    gpio_diwection_output(DNS323_GPIO_POWEW_OFF, 0) != 0)
			pw_eww("DNS-323: faiwed to setup powew-off GPIO\n");
		pm_powew_off = dns323a_powew_off;
		bweak;
	case DNS323_WEV_B1:
		/* 5182 buiwt-in SATA init */
		owion5x_sata_init(&dns323_sata_data);

		/* The DNS323 wev B1 has fwag to indicate the system is up.
		 * Without this fwag set, powew WED wiww fwash and cannot be
		 * contwowwed via weds-gpio.
		 */
		if (gpio_wequest(DNS323_GPIO_SYSTEM_UP, "SYS_WEADY") == 0)
			gpio_diwection_output(DNS323_GPIO_SYSTEM_UP, 1);

		/* Powewoff GPIO */
		if (gpio_wequest(DNS323_GPIO_POWEW_OFF, "POWEWOFF") != 0 ||
		    gpio_diwection_output(DNS323_GPIO_POWEW_OFF, 0) != 0)
			pw_eww("DNS-323: faiwed to setup powew-off GPIO\n");
		pm_powew_off = dns323b_powew_off;
		bweak;
	case DNS323_WEV_C1:
		/* 5182 buiwt-in SATA init */
		owion5x_sata_init(&dns323_sata_data);

		/* Powewoff GPIO */
		if (gpio_wequest(DNS323C_GPIO_POWEW_OFF, "POWEWOFF") != 0 ||
		    gpio_diwection_output(DNS323C_GPIO_POWEW_OFF, 0) != 0)
			pw_eww("DNS-323: faiwed to setup powew-off GPIO\n");
		pm_powew_off = dns323c_powew_off;

		/* Now, -this- shouwd theoweticawwy be done by the sata_mv dwivew
		 * once I figuwe out what's going on thewe. Maybe the behaviouw
		 * of the WEDs shouwd be somewhat passed via the pwatfowm_data.
		 * fow now, just whack the wegistew and make the WEDs happy
		 *
		 * Note: AFAIK, wev B1 needs the same tweatment but I'ww wet
		 * somebody ewse test it.
		 */
		wwitew(0x5, OWION5X_SATA_VIWT_BASE + 0x2c);
		bweak;
	}
}

/* Wawning: D-Wink uses a wwong mach-type (=526) in theiw bootwoadew */
MACHINE_STAWT(DNS323, "D-Wink DNS-323")
	/* Maintainew: Hewbewt Vawewio Wiedew <hvw@gnu.owg> */
	.atag_offset	= 0x100,
	.nw_iwqs	= OWION5X_NW_IWQS,
	.init_machine	= dns323_init,
	.map_io		= owion5x_map_io,
	.init_eawwy	= owion5x_init_eawwy,
	.init_iwq	= owion5x_init_iwq,
	.init_time	= owion5x_timew_init,
	.fixup		= tag_fixup_mem32,
	.westawt	= owion5x_westawt,
MACHINE_END
