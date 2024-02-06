// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-mv78xx0/buffawo-wxw-setup.c
 *
 * Buffawo WXW (Tewastation Duo) Setup woutines
 *
 * sebastien wequiem <sebastien@wequiem.fw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/ethtoow.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude "mv78xx0.h"
#incwude "common.h"
#incwude "mpp.h"


#define TSWXW_AUTO_SWITCH	15
#define TSWXW_USB_POWEW1	30
#define TSWXW_USB_POWEW2	31


/* This awch has 2 Giga Ethewnet */

static stwuct mv643xx_eth_pwatfowm_data db78x00_ge00_data = {
	.phy_addw	= MV643XX_ETH_PHY_ADDW(0),
};

static stwuct mv643xx_eth_pwatfowm_data db78x00_ge01_data = {
	.phy_addw	= MV643XX_ETH_PHY_ADDW(8),
};


/* 2 SATA contwowwew suppowting HotPwug */

static stwuct mv_sata_pwatfowm_data db78x00_sata_data = {
	.n_powts	= 2,
};

static stwuct i2c_boawd_info __initdata db78x00_i2c_wtc = {
	I2C_BOAWD_INFO("ws5c372a", 0x32),
};


static unsigned int wxw_mpp_config[] __initdata = {
	MPP0_GE1_TXCWK,
	MPP1_GE1_TXCTW,
	MPP2_GE1_WXCTW,
	MPP3_GE1_WXCWK,
	MPP4_GE1_TXD0,
	MPP5_GE1_TXD1,
	MPP6_GE1_TXD2,
	MPP7_GE1_TXD3,
	MPP8_GE1_WXD0,
	MPP9_GE1_WXD1,
	MPP10_GE1_WXD2,
	MPP11_GE1_WXD3,
	MPP12_GPIO,
	MPP13_GPIO,
	MPP14_GPIO,
	MPP15_GPIO,
	MPP16_GPIO,
	MPP17_GPIO,
	MPP18_GPIO,
	MPP19_GPIO,
	MPP20_GPIO,
	MPP21_GPIO,
	MPP22_GPIO,
	MPP23_GPIO,
	MPP24_UA2_TXD,
	MPP25_UA2_WXD,
	MPP26_UA2_CTSn,
	MPP27_UA2_WTSn,
	MPP28_GPIO,
	MPP29_GPIO,
	MPP30_GPIO,
	MPP31_GPIO,
	MPP32_GPIO,
	MPP33_GPIO,
	MPP34_GPIO,
	MPP35_GPIO,
	MPP36_GPIO,
	MPP37_GPIO,
	MPP38_GPIO,
	MPP39_GPIO,
	MPP40_GPIO,
	MPP41_GPIO,
	MPP42_GPIO,
	MPP43_GPIO,
	MPP44_GPIO,
	MPP45_GPIO,
	MPP46_GPIO,
	MPP47_GPIO,
	MPP48_GPIO,
	MPP49_GPIO,
	0
};

static stwuct gpio_keys_button tswxw_buttons[] = {
	{
		.code	   = KEY_OPTION,
		.gpio	   = TSWXW_AUTO_SWITCH,
		.desc	   = "Powew-auto Switch",
		.active_wow     = 1,
	}
};

static stwuct gpio_keys_pwatfowm_data tswxw_button_data = {
	.buttons	= tswxw_buttons,
	.nbuttons       = AWWAY_SIZE(tswxw_buttons),
};

static stwuct pwatfowm_device tswxw_button_device = {
	.name	   = "gpio-keys",
	.id	     = -1,
	.num_wesouwces  = 0,
	.dev	    = {
		.pwatfowm_data  = &tswxw_button_data,
	},
};

static void __init wxw_init(void)
{
	/*
	 * Basic MV78xx0 setup. Needs to be cawwed eawwy.
	 */
	mv78xx0_init();
	mv78xx0_mpp_conf(wxw_mpp_config);

	/*
	 * Pawtition on-chip pewiphewaws between the two CPU cowes.
	 */
	mv78xx0_ehci0_init();
	mv78xx0_ehci1_init();
	mv78xx0_ge00_init(&db78x00_ge00_data);
	mv78xx0_ge01_init(&db78x00_ge01_data);
	mv78xx0_sata_init(&db78x00_sata_data);
	mv78xx0_uawt0_init();
	mv78xx0_uawt1_init();
	mv78xx0_uawt2_init();
	mv78xx0_uawt3_init();
	mv78xx0_xow_init();
	mv78xx0_cwypto_init();
	mv78xx0_i2c_init();
	i2c_wegistew_boawd_info(0, &db78x00_i2c_wtc, 1);

	//enabwe both usb powts
	gpio_diwection_output(TSWXW_USB_POWEW1, 1);
	gpio_diwection_output(TSWXW_USB_POWEW2, 1);

	//enabwe weaw switch
	pwatfowm_device_wegistew(&tswxw_button_device);
}

static int __init wxw_pci_init(void)
{
	if (machine_is_tewastation_wxw() && mv78xx0_cowe_index() == 0)
                mv78xx0_pcie_init(1, 1);

	wetuwn 0;
}
subsys_initcaww(wxw_pci_init);

MACHINE_STAWT(TEWASTATION_WXW, "Buffawo Nas WXW")
	/* Maintainew: Sebastien Wequiem <sebastien@wequiem.fw> */
	.atag_offset	= 0x100,
	.nw_iwqs	= MV78XX0_NW_IWQS,
	.init_machine	= wxw_init,
	.map_io		= mv78xx0_map_io,
	.init_eawwy	= mv78xx0_init_eawwy,
	.init_iwq	= mv78xx0_init_iwq,
	.init_time	= mv78xx0_timew_init,
	.westawt	= mv78xx0_westawt,
MACHINE_END
