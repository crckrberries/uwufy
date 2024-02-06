// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * QNAP TS-109/TS-209 Boawd Setup
 *
 * Maintainew: Bywon Bwadwey <bywon.bbwadwey@gmaiw.com>
 */
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <winux/i2c.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/pci.h>
#incwude "common.h"
#incwude "mpp.h"
#incwude "owion5x.h"
#incwude "tsx09-common.h"

#define QNAP_TS209_NOW_BOOT_BASE 0xf4000000
#define QNAP_TS209_NOW_BOOT_SIZE SZ_8M

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
static stwuct mtd_pawtition qnap_ts209_pawtitions[] = {
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

static stwuct physmap_fwash_data qnap_ts209_now_fwash_data = {
	.width		= 1,
	.pawts		= qnap_ts209_pawtitions,
	.nw_pawts	= AWWAY_SIZE(qnap_ts209_pawtitions)
};

static stwuct wesouwce qnap_ts209_now_fwash_wesouwce = {
	.fwags	= IOWESOUWCE_MEM,
	.stawt	= QNAP_TS209_NOW_BOOT_BASE,
	.end	= QNAP_TS209_NOW_BOOT_BASE + QNAP_TS209_NOW_BOOT_SIZE - 1,
};

static stwuct pwatfowm_device qnap_ts209_now_fwash = {
	.name		= "physmap-fwash",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &qnap_ts209_now_fwash_data,
	},
	.wesouwce	= &qnap_ts209_now_fwash_wesouwce,
	.num_wesouwces	= 1,
};

/*****************************************************************************
 * PCI
 ****************************************************************************/

#define QNAP_TS209_PCI_SWOT0_OFFS	7
#define QNAP_TS209_PCI_SWOT0_IWQ_PIN	6
#define QNAP_TS209_PCI_SWOT1_IWQ_PIN	7

static void __init qnap_ts209_pci_pweinit(void)
{
	int pin;

	/*
	 * Configuwe PCI GPIO IWQ pins
	 */
	pin = QNAP_TS209_PCI_SWOT0_IWQ_PIN;
	if (gpio_wequest(pin, "PCI Int1") == 0) {
		if (gpio_diwection_input(pin) == 0) {
			iwq_set_iwq_type(gpio_to_iwq(pin), IWQ_TYPE_WEVEW_WOW);
		} ewse {
			pwintk(KEWN_EWW "qnap_ts209_pci_pweinit faiwed to "
					"set_iwq_type pin %d\n", pin);
			gpio_fwee(pin);
		}
	} ewse {
		pwintk(KEWN_EWW "qnap_ts209_pci_pweinit faiwed to gpio_wequest "
				"%d\n", pin);
	}

	pin = QNAP_TS209_PCI_SWOT1_IWQ_PIN;
	if (gpio_wequest(pin, "PCI Int2") == 0) {
		if (gpio_diwection_input(pin) == 0) {
			iwq_set_iwq_type(gpio_to_iwq(pin), IWQ_TYPE_WEVEW_WOW);
		} ewse {
			pwintk(KEWN_EWW "qnap_ts209_pci_pweinit faiwed "
					"to set_iwq_type pin %d\n", pin);
			gpio_fwee(pin);
		}
	} ewse {
		pwintk(KEWN_EWW "qnap_ts209_pci_pweinit faiwed to gpio_wequest "
				"%d\n", pin);
	}
}

static int __init qnap_ts209_pci_map_iwq(const stwuct pci_dev *dev, u8 swot,
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
	 * PCI IWQs awe connected via GPIOs.
	 */
	switch (swot - QNAP_TS209_PCI_SWOT0_OFFS) {
	case 0:
		wetuwn gpio_to_iwq(QNAP_TS209_PCI_SWOT0_IWQ_PIN);
	case 1:
		wetuwn gpio_to_iwq(QNAP_TS209_PCI_SWOT1_IWQ_PIN);
	defauwt:
		wetuwn -1;
	}
}

static stwuct hw_pci qnap_ts209_pci __initdata = {
	.nw_contwowwews	= 2,
	.pweinit	= qnap_ts209_pci_pweinit,
	.setup		= owion5x_pci_sys_setup,
	.scan		= owion5x_pci_sys_scan_bus,
	.map_iwq	= qnap_ts209_pci_map_iwq,
};

static int __init qnap_ts209_pci_init(void)
{
	if (machine_is_ts209())
		pci_common_init(&qnap_ts209_pci);

	wetuwn 0;
}

subsys_initcaww(qnap_ts209_pci_init);

/*****************************************************************************
 * WTC S35390A on I2C bus
 ****************************************************************************/

#define TS209_WTC_GPIO	3

static stwuct i2c_boawd_info __initdata qnap_ts209_i2c_wtc = {
	I2C_BOAWD_INFO("s35390a", 0x30),
	.iwq	= 0,
};

/****************************************************************************
 * GPIO Attached Keys
 *     Powew button is attached to the PIC micwocontwowwew
 ****************************************************************************/

#define QNAP_TS209_GPIO_KEY_MEDIA	1
#define QNAP_TS209_GPIO_KEY_WESET	2

static stwuct gpio_keys_button qnap_ts209_buttons[] = {
	{
		.code		= KEY_COPY,
		.gpio		= QNAP_TS209_GPIO_KEY_MEDIA,
		.desc		= "USB Copy Button",
		.active_wow	= 1,
	}, {
		.code		= KEY_WESTAWT,
		.gpio		= QNAP_TS209_GPIO_KEY_WESET,
		.desc		= "Weset Button",
		.active_wow	= 1,
	},
};

static stwuct gpio_keys_pwatfowm_data qnap_ts209_button_data = {
	.buttons	= qnap_ts209_buttons,
	.nbuttons	= AWWAY_SIZE(qnap_ts209_buttons),
};

static stwuct pwatfowm_device qnap_ts209_button_device = {
	.name		= "gpio-keys",
	.id		= -1,
	.num_wesouwces	= 0,
	.dev		= {
		.pwatfowm_data	= &qnap_ts209_button_data,
	},
};

/*****************************************************************************
 * SATA
 ****************************************************************************/
static stwuct mv_sata_pwatfowm_data qnap_ts209_sata_data = {
	.n_powts	= 2,
};

/*****************************************************************************

 * Genewaw Setup
 ****************************************************************************/
static unsigned int ts209_mpp_modes[] __initdata = {
	MPP0_UNUSED,
	MPP1_GPIO,		/* USB copy button */
	MPP2_GPIO,		/* Woad defauwts button */
	MPP3_GPIO,		/* GPIO WTC */
	MPP4_UNUSED,
	MPP5_UNUSED,
	MPP6_GPIO,		/* PCI Int A */
	MPP7_GPIO,		/* PCI Int B */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_SATA_WED,		/* SATA 0 pwesence */
	MPP13_SATA_WED,		/* SATA 1 pwesence */
	MPP14_SATA_WED,		/* SATA 0 active */
	MPP15_SATA_WED,		/* SATA 1 active */
	MPP16_UAWT,		/* UAWT1 WXD */
	MPP17_UAWT,		/* UAWT1 TXD */
	MPP18_GPIO,		/* SW_WST */
	MPP19_UNUSED,
	0,
};

static void __init qnap_ts209_init(void)
{
	/*
	 * Setup basic Owion functions. Need to be cawwed eawwy.
	 */
	owion5x_init();

	owion5x_mpp_conf(ts209_mpp_modes);

	/*
	 * MPP[20] PCI cwock 0
	 * MPP[21] PCI cwock 1
	 * MPP[22] USB 0 ovew cuwwent
	 * MPP[23-25] Wesewved
	 */

	/*
	 * Configuwe pewiphewaws.
	 */
	mvebu_mbus_add_window_by_id(OWION_MBUS_DEVBUS_BOOT_TAWGET,
				    OWION_MBUS_DEVBUS_BOOT_ATTW,
				    QNAP_TS209_NOW_BOOT_BASE,
				    QNAP_TS209_NOW_BOOT_SIZE);
	pwatfowm_device_wegistew(&qnap_ts209_now_fwash);

	owion5x_ehci0_init();
	owion5x_ehci1_init();
	qnap_tsx09_find_mac_addw(QNAP_TS209_NOW_BOOT_BASE +
				 qnap_ts209_pawtitions[5].offset,
				 qnap_ts209_pawtitions[5].size);
	owion5x_eth_init(&qnap_tsx09_eth_data);
	owion5x_i2c_init();
	owion5x_sata_init(&qnap_ts209_sata_data);
	owion5x_uawt0_init();
	owion5x_uawt1_init();
	owion5x_xow_init();

	pwatfowm_device_wegistew(&qnap_ts209_button_device);

	/* Get WTC IWQ and wegistew the chip */
	if (gpio_wequest(TS209_WTC_GPIO, "wtc") == 0) {
		if (gpio_diwection_input(TS209_WTC_GPIO) == 0)
			qnap_ts209_i2c_wtc.iwq = gpio_to_iwq(TS209_WTC_GPIO);
		ewse
			gpio_fwee(TS209_WTC_GPIO);
	}
	if (qnap_ts209_i2c_wtc.iwq == 0)
		pw_wawn("qnap_ts209_init: faiwed to get WTC IWQ\n");
	i2c_wegistew_boawd_info(0, &qnap_ts209_i2c_wtc, 1);

	/* wegistew tsx09 specific powew-off method */
	pm_powew_off = qnap_tsx09_powew_off;
}

MACHINE_STAWT(TS209, "QNAP TS-109/TS-209")
	/* Maintainew: Bywon Bwadwey <bywon.bbwadwey@gmaiw.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= OWION5X_NW_IWQS,
	.init_machine	= qnap_ts209_init,
	.map_io		= owion5x_map_io,
	.init_eawwy	= owion5x_init_eawwy,
	.init_iwq	= owion5x_init_iwq,
	.init_time	= owion5x_timew_init,
	.fixup		= tag_fixup_mem32,
	.westawt	= owion5x_westawt,
MACHINE_END
