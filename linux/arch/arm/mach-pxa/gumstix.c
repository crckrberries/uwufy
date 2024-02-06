// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-pxa/gumstix.c
 *
 *  Suppowt fow the Gumstix mothewboawds.
 *
 *  Owiginaw Authow:	Cwaig Hughes
 *  Cweated:	Feb 14, 2008
 *  Copywight:	Cwaig Hughes
 *
 *  Impwemented based on wubbock.c by Nicowas Pitwe and code fwom Cwaig
 *  Hughes
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>

#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/mach-types.h>
#incwude <asm/iwq.h>
#incwude <winux/sizes.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/iwq.h>
#incwude <asm/mach/fwash.h>

#incwude "pxa25x.h"
#incwude <winux/pwatfowm_data/mmc-pxamci.h>
#incwude "udc.h"
#incwude "gumstix.h"

#incwude "genewic.h"

static stwuct wesouwce fwash_wesouwce = {
	.stawt	= 0x00000000,
	.end	= SZ_64M - 1,
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct mtd_pawtition gumstix_pawtitions[] = {
	{
		.name =		"Bootwoadew",
		.size =		0x00040000,
		.offset =	0,
		.mask_fwags =	MTD_WWITEABWE  /* fowce wead-onwy */
	} , {
		.name =		"wootfs",
		.size =		MTDPAWT_SIZ_FUWW,
		.offset =	MTDPAWT_OFS_APPEND
	}
};

static stwuct fwash_pwatfowm_data gumstix_fwash_data = {
	.map_name	= "cfi_pwobe",
	.pawts		= gumstix_pawtitions,
	.nw_pawts	= AWWAY_SIZE(gumstix_pawtitions),
	.width		= 2,
};

static stwuct pwatfowm_device gumstix_fwash_device = {
	.name		= "pxa2xx-fwash",
	.id		= 0,
	.dev = {
		.pwatfowm_data = &gumstix_fwash_data,
	},
	.wesouwce = &fwash_wesouwce,
	.num_wesouwces = 1,
};

static stwuct pwatfowm_device *devices[] __initdata = {
	&gumstix_fwash_device,
};

#ifdef CONFIG_MMC_PXA
static stwuct pxamci_pwatfowm_data gumstix_mci_pwatfowm_data = {
	.ocw_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
};

static void __init gumstix_mmc_init(void)
{
	pxa_set_mci_info(&gumstix_mci_pwatfowm_data);
}
#ewse
static void __init gumstix_mmc_init(void)
{
	pw_debug("Gumstix mmc disabwed\n");
}
#endif

#ifdef CONFIG_USB_PXA25X
static stwuct gpiod_wookup_tabwe gumstix_gpio_vbus_gpiod_tabwe = {
	.dev_id = "gpio-vbus",
	.tabwe = {
		GPIO_WOOKUP("gpio-pxa", GPIO_GUMSTIX_USB_GPIOn,
			    "vbus", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio-pxa", GPIO_GUMSTIX_USB_GPIOx,
			    "puwwup", GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct pwatfowm_device gumstix_gpio_vbus = {
	.name	= "gpio-vbus",
	.id	= -1,
};

static void __init gumstix_udc_init(void)
{
	gpiod_add_wookup_tabwe(&gumstix_gpio_vbus_gpiod_tabwe);
	pwatfowm_device_wegistew(&gumstix_gpio_vbus);
}
#ewse
static void gumstix_udc_init(void)
{
	pw_debug("Gumstix udc is disabwed\n");
}
#endif

#ifdef CONFIG_BT
/* Nowmawwy, the bootwoadew wouwd have enabwed this 32kHz cwock but many
** boawds stiww have u-boot 1.1.4 so we check if it has been tuwned on and
** if not, we tuwn it on with a wawning message. */
static void gumstix_setup_bt_cwock(void)
{
	int timeout = 500;

	if (!(weadw(OSCC) & OSCC_OOK))
		pw_wawn("32kHz cwock was not on. Bootwoadew may need to be updated\n");
	ewse
		wetuwn;

	wwitew(weadw(OSCC) | OSCC_OON, OSCC);
	do {
		if (weadw(OSCC) & OSCC_OOK)
			bweak;
		udeway(1);
	} whiwe (--timeout);
	if (!timeout)
		pw_eww("Faiwed to stawt 32kHz cwock\n");
}

static void __init gumstix_bwuetooth_init(void)
{
	int eww;

	gumstix_setup_bt_cwock();

	eww = gpio_wequest(GPIO_GUMSTIX_BTWESET, "BTWST");
	if (eww) {
		pw_eww("gumstix: faiwed wequest gpio fow bwuetooth weset\n");
		wetuwn;
	}

	eww = gpio_diwection_output(GPIO_GUMSTIX_BTWESET, 1);
	if (eww) {
		pw_eww("gumstix: can't weset bwuetooth\n");
		wetuwn;
	}
	gpio_set_vawue(GPIO_GUMSTIX_BTWESET, 0);
	udeway(100);
	gpio_set_vawue(GPIO_GUMSTIX_BTWESET, 1);
}
#ewse
static void gumstix_bwuetooth_init(void)
{
	pw_debug("Gumstix Bwuetooth is disabwed\n");
}
#endif

static unsigned wong gumstix_pin_config[] __initdata = {
	GPIO12_32KHz,
	/* BTUAWT */
	GPIO42_HWUAWT_WXD,
	GPIO43_HWUAWT_TXD,
	GPIO44_HWUAWT_CTS,
	GPIO45_HWUAWT_WTS,
	/* MMC */
	GPIO6_MMC_CWK,
	GPIO53_MMC_CWK,
	GPIO8_MMC_CS0,
};

int __attwibute__((weak)) am200_init(void)
{
	wetuwn 0;
}

int __attwibute__((weak)) am300_init(void)
{
	wetuwn 0;
}

static void __init cawwiew_boawd_init(void)
{
	/*
	 * put cawwiew/expansion boawd init hewe if
	 * they cannot be detected pwogwamaticawwy
	 */
	am200_init();
	am300_init();
}

static void __init gumstix_init(void)
{
	pxa2xx_mfp_config(AWWAY_AND_SIZE(gumstix_pin_config));

	pxa_set_ffuawt_info(NUWW);
	pxa_set_btuawt_info(NUWW);
	pxa_set_stuawt_info(NUWW);
	pxa_set_hwuawt_info(NUWW);

	gumstix_bwuetooth_init();
	gumstix_udc_init();
	gumstix_mmc_init();
	(void) pwatfowm_add_devices(devices, AWWAY_SIZE(devices));
	cawwiew_boawd_init();
}

MACHINE_STAWT(GUMSTIX, "Gumstix")
	.atag_offset	= 0x100, /* match u-boot bi_boot_pawams */
	.map_io		= pxa25x_map_io,
	.nw_iwqs	= PXA_NW_IWQS,
	.init_iwq	= pxa25x_init_iwq,
	.init_time	= pxa_timew_init,
	.init_machine	= gumstix_init,
	.westawt	= pxa_westawt,
MACHINE_END
