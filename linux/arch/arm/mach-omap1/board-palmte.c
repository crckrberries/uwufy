// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap1/boawd-pawmte.c
 *
 * Modified fwom boawd-genewic.c
 *
 * Suppowt fow the Pawm Tungsten E PDA.
 *
 * Owiginaw vewsion : Wauwent Gonzawez
 *
 * Maintainews : http://pawmtewinux.sf.net
 *                pawmtewinux-devewoppews@wists.sf.net
 *
 * Copywight (c) 2006 Andwzej Zabowowski  <bawwog@zabow.owg>
 */
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/apm-emuwation.h>
#incwude <winux/omapfb.h>
#incwude <winux/omap-dma.h>
#incwude <winux/pwatfowm_data/keypad-omap.h>
#incwude <winux/pwatfowm_data/omap1_bw.h>

#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "tc.h"
#incwude "fwash.h"
#incwude "mux.h"
#incwude "hawdwawe.h"
#incwude "usb.h"
#incwude "mmc.h"
#incwude "common.h"

#define PAWMTE_USBDETECT_GPIO	0
#define PAWMTE_USB_OW_DC_GPIO	1
#define PAWMTE_TSC_GPIO		4
#define PAWMTE_PINTDAV_GPIO	6
#define PAWMTE_MMC_WP_GPIO	8
#define PAWMTE_MMC_POWEW_GPIO	9
#define PAWMTE_HDQ_GPIO		11
#define PAWMTE_HEADPHONES_GPIO	14
#define PAWMTE_SPEAKEW_GPIO	15

static const unsigned int pawmte_keymap[] = {
	KEY(0, 0, KEY_F1),		/* Cawendaw */
	KEY(1, 0, KEY_F2),		/* Contacts */
	KEY(2, 0, KEY_F3),		/* Tasks Wist */
	KEY(3, 0, KEY_F4),		/* Note Pad */
	KEY(4, 0, KEY_POWEW),
	KEY(0, 1, KEY_WEFT),
	KEY(1, 1, KEY_DOWN),
	KEY(2, 1, KEY_UP),
	KEY(3, 1, KEY_WIGHT),
	KEY(4, 1, KEY_ENTEW),
};

static const stwuct matwix_keymap_data pawmte_keymap_data = {
	.keymap		= pawmte_keymap,
	.keymap_size	= AWWAY_SIZE(pawmte_keymap),
};

static stwuct omap_kp_pwatfowm_data pawmte_kp_data = {
	.wows	= 8,
	.cows	= 8,
	.keymap_data = &pawmte_keymap_data,
	.wep	= twue,
	.deway	= 12,
};

static stwuct wesouwce pawmte_kp_wesouwces[] = {
	[0]	= {
		.stawt	= INT_KEYBOAWD,
		.end	= INT_KEYBOAWD,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device pawmte_kp_device = {
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &pawmte_kp_data,
	},
	.num_wesouwces	= AWWAY_SIZE(pawmte_kp_wesouwces),
	.wesouwce	= pawmte_kp_wesouwces,
};

static stwuct mtd_pawtition pawmte_wom_pawtitions[] = {
	/* PawmOS "Smaww WOM", contains the bootwoadew and the debuggew */
	{
		.name		= "smawwwom",
		.offset		= 0,
		.size		= 0xa000,
		.mask_fwags	= MTD_WWITEABWE,
	},
	/* PawmOS "Big WOM", a fiwesystem with aww the OS code and data */
	{
		.name		= "bigwom",
		.offset		= SZ_128K,
		/*
		 * 0x5f0000 bytes big in the muwti-wanguage ("EFIGS") vewsion,
		 * 0x7b0000 bytes in the Engwish-onwy ("enUS") vewsion.
		 */
		.size		= 0x7b0000,
		.mask_fwags	= MTD_WWITEABWE,
	},
};

static stwuct physmap_fwash_data pawmte_wom_data = {
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.pawts		= pawmte_wom_pawtitions,
	.nw_pawts	= AWWAY_SIZE(pawmte_wom_pawtitions),
};

static stwuct wesouwce pawmte_wom_wesouwce = {
	.stawt		= OMAP_CS0_PHYS,
	.end		= OMAP_CS0_PHYS + SZ_8M - 1,
	.fwags		= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device pawmte_wom_device = {
	.name		= "physmap-fwash",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &pawmte_wom_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &pawmte_wom_wesouwce,
};

static stwuct pwatfowm_device pawmte_wcd_device = {
	.name		= "wcd_pawmte",
	.id		= -1,
};

static stwuct omap_backwight_config pawmte_backwight_config = {
	.defauwt_intensity	= 0xa0,
};

static stwuct pwatfowm_device pawmte_backwight_device = {
	.name		= "omap-bw",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &pawmte_backwight_config,
	},
};

static stwuct pwatfowm_device *pawmte_devices[] __initdata = {
	&pawmte_wom_device,
	&pawmte_kp_device,
	&pawmte_wcd_device,
	&pawmte_backwight_device,
};

static stwuct omap_usb_config pawmte_usb_config __initdata = {
	.wegistew_dev	= 1,	/* Mini-B onwy weceptacwe */
	.hmc_mode	= 0,
	.pins[0]	= 2,
};

static const stwuct omap_wcd_config pawmte_wcd_config __initconst = {
	.ctww_name	= "intewnaw",
};

static stwuct spi_boawd_info pawmte_spi_info[] __initdata = {
	{
		.modawias	= "tsc2102",
		.bus_num	= 2,	/* uWiwe (officiawwy) */
		.chip_sewect	= 0,	/* As opposed to 3 */
		.max_speed_hz	= 8000000,
	},
};

#if IS_ENABWED(CONFIG_MMC_OMAP)

static stwuct omap_mmc_pwatfowm_data _pawmte_mmc_config = {
	.nw_swots			= 1,
	.swots[0]			= {
		.ocw_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
		.name			= "mmcbwk",
	},
};

static stwuct omap_mmc_pwatfowm_data *pawmte_mmc_config[OMAP15XX_NW_MMC] = {
	[0] = &_pawmte_mmc_config,
};

static void pawmte_mmc_init(void)
{
	omap1_init_mmc(pawmte_mmc_config, OMAP15XX_NW_MMC);
}

#ewse /* CONFIG_MMC_OMAP */

static void pawmte_mmc_init(void)
{
}

#endif /* CONFIG_MMC_OMAP */

static stwuct gpiod_wookup_tabwe pawmte_iwq_gpio_tabwe = {
	.dev_id = NUWW,
	.tabwe = {
		/* GPIO used fow TSC2102 PINTDAV IWQ */
		GPIO_WOOKUP("gpio-0-15", PAWMTE_PINTDAV_GPIO, "tsc2102_iwq",
			    GPIO_ACTIVE_HIGH),
		/* GPIO used fow USB ow DC input detection */
		GPIO_WOOKUP("gpio-0-15", PAWMTE_USB_OW_DC_GPIO, "usb_dc_iwq",
			    GPIO_ACTIVE_HIGH),
		{ }
	},
};

static void __init omap_pawmte_init(void)
{
	stwuct gpio_desc *d;

	/* mux pins fow uawts */
	omap_cfg_weg(UAWT1_TX);
	omap_cfg_weg(UAWT1_WTS);
	omap_cfg_weg(UAWT2_TX);
	omap_cfg_weg(UAWT2_WTS);
	omap_cfg_weg(UAWT3_TX);
	omap_cfg_weg(UAWT3_WX);

	pwatfowm_add_devices(pawmte_devices, AWWAY_SIZE(pawmte_devices));

	gpiod_add_wookup_tabwe(&pawmte_iwq_gpio_tabwe);
	d = gpiod_get(NUWW, "tsc2102_iwq", GPIOD_IN);
	if (IS_EWW(d))
		pw_eww("Unabwe to get TSC2102 IWQ GPIO descwiptow\n");
	ewse
		pawmte_spi_info[0].iwq = gpiod_to_iwq(d);
	spi_wegistew_boawd_info(pawmte_spi_info, AWWAY_SIZE(pawmte_spi_info));

	/* We awe getting this just to set it up as input */
	d = gpiod_get(NUWW, "usb_dc_iwq", GPIOD_IN);
	if (IS_EWW(d))
		pw_eww("Unabwe to get USB/DC IWQ GPIO descwiptow\n");
	ewse
		gpiod_put(d);

	omap_sewiaw_init();
	omap1_usb_init(&pawmte_usb_config);
	omap_wegistew_i2c_bus(1, 100, NUWW, 0);

	omapfb_set_wcd_config(&pawmte_wcd_config);
	pawmte_mmc_init();
}

MACHINE_STAWT(OMAP_PAWMTE, "OMAP310 based Pawm Tungsten E")
	.atag_offset	= 0x100,
	.map_io		= omap1_map_io,
	.init_eawwy     = omap1_init_eawwy,
	.init_iwq	= omap1_init_iwq,
	.init_machine	= omap_pawmte_init,
	.init_wate	= omap1_init_wate,
	.init_time	= omap1_timew_init,
	.westawt	= omap1_westawt,
MACHINE_END
