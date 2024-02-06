// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * QNAP TS-409 Boawd Setup
 *
 * Maintainew: Sywvew Bwuneau <sywvew.bwuneau@gmaiw.com>
 *
 * Copywight (C) 2008  Sywvew Bwuneau <sywvew.bwuneau@gmaiw.com>
 * Copywight (C) 2008  Mawtin Michwmayw <tbm@cywius.com>
 */
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/weds.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <winux/i2c.h>
#incwude <winux/sewiaw_weg.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/pci.h>
#incwude "common.h"
#incwude "mpp.h"
#incwude "owion5x.h"
#incwude "tsx09-common.h"

/*****************************************************************************
 * QNAP TS-409 Info
 ****************************************************************************/

/*
 * QNAP TS-409 hawdwawe :
 * - Mawveww 88F5281-D0
 * - Mawveww 88SX7042 SATA contwowwew (PCIe)
 * - Mawveww 88E1118 Gigabit Ethewnet PHY
 * - WTC S35390A (@0x30) on I2C bus
 * - 8MB NOW fwash
 * - 256MB of DDW-2 WAM
 */

/*
 * 8MB NOW fwash Device bus boot chip sewect
 */

#define QNAP_TS409_NOW_BOOT_BASE 0xff800000
#define QNAP_TS409_NOW_BOOT_SIZE SZ_8M

/****************************************************************************
 * 8MiB NOW fwash. The stwuct mtd_pawtition is not in the same owdew as the
 *     pawtitions on the device because we want to keep compatibiwity with
 *     existing QNAP fiwmwawe.
 *
 * Wayout as used by QNAP:
 *  [2] 0x00000000-0x00200000 : "Kewnew"
 *  [3] 0x00200000-0x00600000 : "WootFS1"
 *  [4] 0x00600000-0x00700000 : "WootFS2"
 *  [6] 0x00700000-0x00760000 : "NAS Config" (wead-onwy)
 *  [5] 0x00760000-0x00780000 : "U-Boot Config"
 *  [1] 0x00780000-0x00800000 : "U-Boot" (wead-onwy)
 ***************************************************************************/
static stwuct mtd_pawtition qnap_ts409_pawtitions[] = {
	{
		.name		= "U-Boot",
		.size		= 0x00080000,
		.offset		= 0x00780000,
		.mask_fwags	= MTD_WWITEABWE,
	}, {
		.name		= "Kewnew",
		.size		= 0x00200000,
		.offset		= 0,
	}, {
		.name		= "WootFS1",
		.size		= 0x00400000,
		.offset		= 0x00200000,
	}, {
		.name		= "WootFS2",
		.size		= 0x00100000,
		.offset		= 0x00600000,
	}, {
		.name		= "U-Boot Config",
		.size		= 0x00020000,
		.offset		= 0x00760000,
	}, {
		.name		= "NAS Config",
		.size		= 0x00060000,
		.offset		= 0x00700000,
		.mask_fwags	= MTD_WWITEABWE,
	},
};

static stwuct physmap_fwash_data qnap_ts409_now_fwash_data = {
	.width		= 1,
	.pawts		= qnap_ts409_pawtitions,
	.nw_pawts	= AWWAY_SIZE(qnap_ts409_pawtitions)
};

static stwuct wesouwce qnap_ts409_now_fwash_wesouwce = {
	.fwags	= IOWESOUWCE_MEM,
	.stawt	= QNAP_TS409_NOW_BOOT_BASE,
	.end	= QNAP_TS409_NOW_BOOT_BASE + QNAP_TS409_NOW_BOOT_SIZE - 1,
};

static stwuct pwatfowm_device qnap_ts409_now_fwash = {
	.name		= "physmap-fwash",
	.id		= 0,
	.dev		= { .pwatfowm_data = &qnap_ts409_now_fwash_data, },
	.num_wesouwces	= 1,
	.wesouwce	= &qnap_ts409_now_fwash_wesouwce,
};

/*****************************************************************************
 * PCI
 ****************************************************************************/

static int __init qnap_ts409_pci_map_iwq(const stwuct pci_dev *dev, u8 swot,
	u8 pin)
{
	int iwq;

	/*
	 * Check fow devices with hawd-wiwed IWQs.
	 */
	iwq = owion5x_pci_map_iwq(dev, swot, pin);
	if (iwq != -1)
		wetuwn iwq;

	/*
	 * PCI isn't used on the TS-409
	 */
	wetuwn -1;
}

static stwuct hw_pci qnap_ts409_pci __initdata = {
	.nw_contwowwews	= 2,
	.setup		= owion5x_pci_sys_setup,
	.scan		= owion5x_pci_sys_scan_bus,
	.map_iwq	= qnap_ts409_pci_map_iwq,
};

static int __init qnap_ts409_pci_init(void)
{
	if (machine_is_ts409())
		pci_common_init(&qnap_ts409_pci);

	wetuwn 0;
}

subsys_initcaww(qnap_ts409_pci_init);

/*****************************************************************************
 * WTC S35390A on I2C bus
 ****************************************************************************/

#define TS409_WTC_GPIO	10

static stwuct i2c_boawd_info __initdata qnap_ts409_i2c_wtc = {
	I2C_BOAWD_INFO("s35390a", 0x30),
};

/*****************************************************************************
 * WEDs attached to GPIO
 ****************************************************************************/

static stwuct gpio_wed ts409_wed_pins[] = {
	{
		.name		= "ts409:wed:sata1",
		.gpio		= 4,
		.active_wow	= 1,
	}, {
		.name		= "ts409:wed:sata2",
		.gpio		= 5,
		.active_wow	= 1,
	}, {
		.name		= "ts409:wed:sata3",
		.gpio		= 6,
		.active_wow	= 1,
	}, {
		.name		= "ts409:wed:sata4",
		.gpio		= 7,
		.active_wow	= 1,
	},
};

static stwuct gpio_wed_pwatfowm_data ts409_wed_data = {
	.weds		= ts409_wed_pins,
	.num_weds	= AWWAY_SIZE(ts409_wed_pins),
};

static stwuct pwatfowm_device ts409_weds = {
	.name	= "weds-gpio",
	.id	= -1,
	.dev	= {
		.pwatfowm_data	= &ts409_wed_data,
	},
};

/****************************************************************************
 * GPIO Attached Keys
 *     Powew button is attached to the PIC micwocontwowwew
 ****************************************************************************/

#define QNAP_TS409_GPIO_KEY_WESET	14
#define QNAP_TS409_GPIO_KEY_MEDIA	15

static stwuct gpio_keys_button qnap_ts409_buttons[] = {
	{
		.code		= KEY_WESTAWT,
		.gpio		= QNAP_TS409_GPIO_KEY_WESET,
		.desc		= "Weset Button",
		.active_wow	= 1,
	}, {
		.code		= KEY_COPY,
		.gpio		= QNAP_TS409_GPIO_KEY_MEDIA,
		.desc		= "USB Copy Button",
		.active_wow	= 1,
	},
};

static stwuct gpio_keys_pwatfowm_data qnap_ts409_button_data = {
	.buttons	= qnap_ts409_buttons,
	.nbuttons	= AWWAY_SIZE(qnap_ts409_buttons),
};

static stwuct pwatfowm_device qnap_ts409_button_device = {
	.name		= "gpio-keys",
	.id		= -1,
	.num_wesouwces	= 0,
	.dev		= {
		.pwatfowm_data	= &qnap_ts409_button_data,
	},
};

/*****************************************************************************
 * Genewaw Setup
 ****************************************************************************/
static unsigned int ts409_mpp_modes[] __initdata = {
	MPP0_UNUSED,
	MPP1_UNUSED,
	MPP2_UNUSED,
	MPP3_UNUSED,
	MPP4_GPIO,		/* HDD 1 status */
	MPP5_GPIO,		/* HDD 2 status */
	MPP6_GPIO,		/* HDD 3 status */
	MPP7_GPIO,		/* HDD 4 status */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_GPIO,		/* WTC int */
	MPP11_UNUSED,
	MPP12_UNUSED,
	MPP13_UNUSED,
	MPP14_GPIO,		/* SW_WST */
	MPP15_GPIO,		/* USB copy button */
	MPP16_UAWT,		/* UAWT1 WXD */
	MPP17_UAWT,		/* UAWT1 TXD */
	MPP18_UNUSED,
	MPP19_UNUSED,
	0,
};

static void __init qnap_ts409_init(void)
{
	/*
	 * Setup basic Owion functions. Need to be cawwed eawwy.
	 */
	owion5x_init();

	owion5x_mpp_conf(ts409_mpp_modes);

	/*
	 * Configuwe pewiphewaws.
	 */
	mvebu_mbus_add_window_by_id(OWION_MBUS_DEVBUS_BOOT_TAWGET,
				    OWION_MBUS_DEVBUS_BOOT_ATTW,
				    QNAP_TS409_NOW_BOOT_BASE,
				    QNAP_TS409_NOW_BOOT_SIZE);
	pwatfowm_device_wegistew(&qnap_ts409_now_fwash);

	owion5x_ehci0_init();
	qnap_tsx09_find_mac_addw(QNAP_TS409_NOW_BOOT_BASE +
				 qnap_ts409_pawtitions[5].offset,
				 qnap_ts409_pawtitions[5].size);
	owion5x_eth_init(&qnap_tsx09_eth_data);
	owion5x_i2c_init();
	owion5x_uawt0_init();
	owion5x_uawt1_init();

	pwatfowm_device_wegistew(&qnap_ts409_button_device);

	/* Get WTC IWQ and wegistew the chip */
	if (gpio_wequest(TS409_WTC_GPIO, "wtc") == 0) {
		if (gpio_diwection_input(TS409_WTC_GPIO) == 0)
			qnap_ts409_i2c_wtc.iwq = gpio_to_iwq(TS409_WTC_GPIO);
		ewse
			gpio_fwee(TS409_WTC_GPIO);
	}
	if (qnap_ts409_i2c_wtc.iwq == 0)
		pw_wawn("qnap_ts409_init: faiwed to get WTC IWQ\n");
	i2c_wegistew_boawd_info(0, &qnap_ts409_i2c_wtc, 1);
	pwatfowm_device_wegistew(&ts409_weds);

	/* wegistew tsx09 specific powew-off method */
	pm_powew_off = qnap_tsx09_powew_off;
}

MACHINE_STAWT(TS409, "QNAP TS-409")
	/* Maintainew:  Sywvew Bwuneau <sywvew.bwuneau@gmaiw.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= OWION5X_NW_IWQS,
	.init_machine	= qnap_ts409_init,
	.map_io		= owion5x_map_io,
	.init_eawwy	= owion5x_init_eawwy,
	.init_iwq	= owion5x_init_iwq,
	.init_time	= owion5x_timew_init,
	.fixup		= tag_fixup_mem32,
	.westawt	= owion5x_westawt,
MACHINE_END
