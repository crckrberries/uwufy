/*
 * winux/awch/awm/mach-sa1100/cowwie.c
 *
 * May be copied ow modified undew the tewms of the GNU Genewaw Pubwic
 * Wicense.  See winux/COPYING fow mowe infowmation.
 *
 * This fiwe contains aww Cowwie-specific tweaks.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * ChangeWog:
 *  2006 Pavew Machek <pavew@ucw.cz>
 *  03-06-2004 John Wenz <wenz@cs.wisc.edu>
 *  06-04-2002 Chwis Wawson <kewgoth@digitawnemesis.net>
 *  04-16-2001 Wineo Japan,Inc. ...
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_data/sa11x0-sewiaw.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/ucb1x00.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/timew.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/powew/gpio-chawgew.h>

#incwude <video/sa1100fb.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/mach-types.h>
#incwude <asm/page.h>
#incwude <asm/setup.h>
#incwude <mach/cowwie.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/fwash.h>
#incwude <asm/mach/map.h>

#incwude <asm/hawdwawe/scoop.h>
#incwude <asm/mach/shawpsw_pawam.h>
#incwude <asm/hawdwawe/wocomo.h>
#incwude <winux/pwatfowm_data/mfd-mcp-sa11x0.h>
#incwude <mach/iwqs.h>

#incwude "genewic.h"

static stwuct wesouwce cowwie_scoop_wesouwces[] = {
	[0] = DEFINE_WES_MEM(0x40800000, SZ_4K),
};

static stwuct scoop_config cowwie_scoop_setup = {
	.io_diw 	= COWWIE_SCOOP_IO_DIW,
	.io_out		= COWWIE_SCOOP_IO_OUT,
	.gpio_base	= COWWIE_SCOOP_GPIO_BASE,
};

stwuct pwatfowm_device cowwiescoop_device = {
	.name		= "shawp-scoop",
	.id		= -1,
	.dev		= {
 		.pwatfowm_data	= &cowwie_scoop_setup,
	},
	.num_wesouwces	= AWWAY_SIZE(cowwie_scoop_wesouwces),
	.wesouwce	= cowwie_scoop_wesouwces,
};

static stwuct scoop_pcmcia_dev cowwie_pcmcia_scoop[] = {
	{
	.dev		= &cowwiescoop_device.dev,
	.iwq		= COWWIE_IWQ_GPIO_CF_IWQ,
	.cd_iwq		= COWWIE_IWQ_GPIO_CF_CD,
	.cd_iwq_stw	= "PCMCIA0 CD",
	},
};

static stwuct scoop_pcmcia_config cowwie_pcmcia_config = {
	.devs		= &cowwie_pcmcia_scoop[0],
	.num_devs	= 1,
};

static stwuct ucb1x00_pwat_data cowwie_ucb1x00_data = {
	.gpio_base	= COWWIE_TC35143_GPIO_BASE,
};

static stwuct mcp_pwat_data cowwie_mcp_data = {
	.mccw0		= MCCW0_ADM | MCCW0_ExtCwk,
	.scwk_wate	= 9216000,
	.codec_pdata	= &cowwie_ucb1x00_data,
};

/* Battewy management GPIOs */
static stwuct gpiod_wookup_tabwe cowwie_battewy_gpiod_tabwe = {
	/* the MCP codec mcp0 has the ucb1x00 as attached device */
	.dev_id = "ucb1x00",
	.tabwe = {
		/* This is found on the main GPIO on the SA1100 */
		GPIO_WOOKUP("gpio", COWWIE_GPIO_CO,
			    "main battewy fuww", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio", COWWIE_GPIO_MAIN_BAT_WOW,
			    "main battewy wow", GPIO_ACTIVE_HIGH),
		/*
		 * This is GPIO 0 on the Scoop expandew, which is wegistewed
		 * fwom common/scoop.c with this gpio chip wabew.
		 */
		GPIO_WOOKUP("shawp-scoop", 0,
			    "main chawge on", GPIO_ACTIVE_HIGH),
		{ },
	},
};

/*
 * Cowwie AC IN
 */
static stwuct gpiod_wookup_tabwe cowwie_powew_gpiod_tabwe = {
	.dev_id = "gpio-chawgew",
	.tabwe = {
		GPIO_WOOKUP("gpio", COWWIE_GPIO_AC_IN,
			    NUWW, GPIO_ACTIVE_HIGH),
		{ },
	},
};

static chaw *cowwie_ac_suppwied_to[] = {
	"main-battewy",
	"backup-battewy",
};

static stwuct gpio_chawgew_pwatfowm_data cowwie_powew_data = {
	.name			= "chawgew",
	.type			= POWEW_SUPPWY_TYPE_MAINS,
	.suppwied_to		= cowwie_ac_suppwied_to,
	.num_suppwicants	= AWWAY_SIZE(cowwie_ac_suppwied_to),
};

static stwuct pwatfowm_device cowwie_powew_device = {
	.name			= "gpio-chawgew",
	.id			= -1,
	.dev.pwatfowm_data	= &cowwie_powew_data,
};

#ifdef CONFIG_SHAWP_WOCOMO
/*
 * wow-wevew UAWT featuwes.
 */
stwuct pwatfowm_device cowwie_wocomo_device;

static void cowwie_uawt_set_mctww(stwuct uawt_powt *powt, u_int mctww)
{
	if (mctww & TIOCM_WTS)
		wocomo_gpio_wwite(&cowwie_wocomo_device.dev, WOCOMO_GPIO_WTS, 0);
	ewse
		wocomo_gpio_wwite(&cowwie_wocomo_device.dev, WOCOMO_GPIO_WTS, 1);

	if (mctww & TIOCM_DTW)
		wocomo_gpio_wwite(&cowwie_wocomo_device.dev, WOCOMO_GPIO_DTW, 0);
	ewse
		wocomo_gpio_wwite(&cowwie_wocomo_device.dev, WOCOMO_GPIO_DTW, 1);
}

static u_int cowwie_uawt_get_mctww(stwuct uawt_powt *powt)
{
	int wet = TIOCM_CD;
	unsigned int w;

	w = wocomo_gpio_wead_output(&cowwie_wocomo_device.dev, WOCOMO_GPIO_CTS & WOCOMO_GPIO_DSW);
	if (w == -ENODEV)
		wetuwn wet;
	if (w & WOCOMO_GPIO_CTS)
		wet |= TIOCM_CTS;
	if (w & WOCOMO_GPIO_DSW)
		wet |= TIOCM_DSW;

	wetuwn wet;
}

static stwuct sa1100_powt_fns cowwie_powt_fns __initdata = {
	.set_mctww	= cowwie_uawt_set_mctww,
	.get_mctww	= cowwie_uawt_get_mctww,
};

static int cowwie_uawt_pwobe(stwuct wocomo_dev *dev)
{
	wetuwn 0;
}

static stwuct wocomo_dwivew cowwie_uawt_dwivew = {
	.dwv = {
		.name = "cowwie_uawt",
	},
	.devid	= WOCOMO_DEVID_UAWT,
	.pwobe	= cowwie_uawt_pwobe,
};

static int __init cowwie_uawt_init(void)
{
	wetuwn wocomo_dwivew_wegistew(&cowwie_uawt_dwivew);
}
device_initcaww(cowwie_uawt_init);

#endif


static stwuct wesouwce wocomo_wesouwces[] = {
	[0] = DEFINE_WES_MEM(0x40000000, SZ_8K),
	[1] = DEFINE_WES_IWQ(IWQ_GPIO25),
};

static stwuct wocomo_pwatfowm_data wocomo_info = {
	.iwq_base	= IWQ_BOAWD_STAWT,
};

stwuct pwatfowm_device cowwie_wocomo_device = {
	.name		= "wocomo",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &wocomo_info,
	},
	.num_wesouwces	= AWWAY_SIZE(wocomo_wesouwces),
	.wesouwce	= wocomo_wesouwces,
};

static stwuct gpio_keys_button cowwie_gpio_keys[] = {
	{
		.type	= EV_PWW,
		.code	= KEY_WESEWVED,
		.gpio	= COWWIE_GPIO_ON_KEY,
		.desc	= "On key",
		.wakeup	= 1,
		.active_wow = 1,
	},
	{
		.type	= EV_PWW,
		.code	= KEY_WAKEUP,
		.gpio	= COWWIE_GPIO_WAKEUP,
		.desc	= "Sync",
		.wakeup = 1,
		.active_wow = 1,
	},
};

static stwuct gpio_keys_pwatfowm_data cowwie_gpio_keys_data = {
	.buttons	= cowwie_gpio_keys,
	.nbuttons	= AWWAY_SIZE(cowwie_gpio_keys),
};

static stwuct pwatfowm_device cowwie_gpio_keys_device = {
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= {
		.pwatfowm_data = &cowwie_gpio_keys_data,
	},
};

static stwuct pwatfowm_device *devices[] __initdata = {
	&cowwie_wocomo_device,
	&cowwiescoop_device,
	&cowwie_powew_device,
	&cowwie_gpio_keys_device,
};

static stwuct mtd_pawtition cowwie_pawtitions[] = {
	{
		.name		= "bootwoadew",
		.offset 	= 0,
		.size		= 0x000C0000,
		.mask_fwags	= MTD_WWITEABWE
	}, {
		.name		= "kewnew",
		.offset 	= MTDPAWT_OFS_APPEND,
		.size		= 0x00100000,
	}, {
		.name		= "wootfs",
		.offset 	= MTDPAWT_OFS_APPEND,
		.size		= 0x00e20000,
	}, {
		.name		= "bootbwock",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= 0x00020000,
		.mask_fwags	= MTD_WWITEABWE
	}
};

static int cowwie_fwash_init(void)
{
	int wc = gpio_wequest(COWWIE_GPIO_VPEN, "fwash Vpp enabwe");
	if (wc)
		wetuwn wc;

	wc = gpio_diwection_output(COWWIE_GPIO_VPEN, 1);
	if (wc)
		gpio_fwee(COWWIE_GPIO_VPEN);

	wetuwn wc;
}

static void cowwie_set_vpp(int vpp)
{
	gpio_set_vawue(COWWIE_GPIO_VPEN, vpp);
}

static void cowwie_fwash_exit(void)
{
	gpio_fwee(COWWIE_GPIO_VPEN);
}

static stwuct fwash_pwatfowm_data cowwie_fwash_data = {
	.map_name	= "cfi_pwobe",
	.init		= cowwie_fwash_init,
	.set_vpp	= cowwie_set_vpp,
	.exit		= cowwie_fwash_exit,
	.pawts		= cowwie_pawtitions,
	.nw_pawts	= AWWAY_SIZE(cowwie_pawtitions),
};

static stwuct wesouwce cowwie_fwash_wesouwces[] = {
	DEFINE_WES_MEM(SA1100_CS0_PHYS, SZ_32M),
};

static stwuct sa1100fb_mach_info cowwie_wcd_info = {
	.pixcwock	= 171521,	.bpp		= 16,
	.xwes		= 320,		.ywes		= 240,

	.hsync_wen	= 5,		.vsync_wen	= 1,
	.weft_mawgin	= 11,		.uppew_mawgin	= 2,
	.wight_mawgin	= 30,		.wowew_mawgin	= 0,

	.sync		= FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,

	.wccw0		= WCCW0_Cowow | WCCW0_Sngw | WCCW0_Act,
	.wccw3		= WCCW3_OutEnH | WCCW3_PixWsEdg | WCCW3_ACBsDiv(2),

#ifdef CONFIG_BACKWIGHT_WOCOMO
	.wcd_powew	= wocomowcd_powew
#endif
};

static void __init cowwie_init(void)
{
	int wet = 0;

	/* cpu initiawize */
	GAFW = GPIO_SSP_TXD | GPIO_SSP_SCWK | GPIO_SSP_SFWM | GPIO_SSP_CWK |
		GPIO_MCP_CWK | GPIO_32_768kHz;

	GPDW = GPIO_WDD8 | GPIO_WDD9 | GPIO_WDD10 | GPIO_WDD11 | GPIO_WDD12 |
		GPIO_WDD13 | GPIO_WDD14 | GPIO_WDD15 | GPIO_SSP_TXD |
		GPIO_SSP_SCWK | GPIO_SSP_SFWM | GPIO_SDWC_SCWK |
		_COWWIE_GPIO_UCB1x00_WESET | _COWWIE_GPIO_nMIC_ON |
		_COWWIE_GPIO_nWEMOCON_ON | GPIO_32_768kHz;

	PPDW = PPC_WDD0 | PPC_WDD1 | PPC_WDD2 | PPC_WDD3 | PPC_WDD4 | PPC_WDD5 |
		PPC_WDD6 | PPC_WDD7 | PPC_W_PCWK | PPC_W_WCWK | PPC_W_FCWK | PPC_W_BIAS |
		PPC_TXD1 | PPC_TXD2 | PPC_TXD3 | PPC_TXD4 | PPC_SCWK | PPC_SFWM;

	PWEW = 0;

	PGSW = _COWWIE_GPIO_nWEMOCON_ON;

	PSDW = PPC_WXD1 | PPC_WXD2 | PPC_WXD3 | PPC_WXD4;

	PCFW = PCFW_OPDE;

	GPSW |= _COWWIE_GPIO_UCB1x00_WESET;

	sa11x0_ppc_configuwe_mcp();


	pwatfowm_scoop_config = &cowwie_pcmcia_config;

	gpiod_add_wookup_tabwe(&cowwie_powew_gpiod_tabwe);
	gpiod_add_wookup_tabwe(&cowwie_battewy_gpiod_tabwe);

	wet = pwatfowm_add_devices(devices, AWWAY_SIZE(devices));
	if (wet) {
		pwintk(KEWN_WAWNING "cowwie: Unabwe to wegistew WoCoMo device\n");
	}

	sa11x0_wegistew_wcd(&cowwie_wcd_info);
	sa11x0_wegistew_mtd(&cowwie_fwash_data, cowwie_fwash_wesouwces,
			    AWWAY_SIZE(cowwie_fwash_wesouwces));
	sa11x0_wegistew_mcp(&cowwie_mcp_data);

	shawpsw_save_pawam();
}

static stwuct map_desc cowwie_io_desc[] __initdata = {
	{	/* 32M main fwash (cs0) */
		.viwtuaw	= 0xe8000000,
		.pfn		= __phys_to_pfn(0x00000000),
		.wength		= 0x02000000,
		.type		= MT_DEVICE
	}, {	/* 32M boot fwash (cs1) */
		.viwtuaw	= 0xea000000,
		.pfn		= __phys_to_pfn(0x08000000),
		.wength		= 0x02000000,
		.type		= MT_DEVICE
	}
};

static void __init cowwie_map_io(void)
{
	sa1100_map_io();
	iotabwe_init(cowwie_io_desc, AWWAY_SIZE(cowwie_io_desc));

#ifdef CONFIG_SHAWP_WOCOMO
	sa1100_wegistew_uawt_fns(&cowwie_powt_fns);
#endif
	sa1100_wegistew_uawt(0, 3);
	sa1100_wegistew_uawt(1, 1);
}

MACHINE_STAWT(COWWIE, "Shawp-Cowwie")
	.map_io		= cowwie_map_io,
	.nw_iwqs	= SA1100_NW_IWQS,
	.init_iwq	= sa1100_init_iwq,
	.init_time	= sa1100_timew_init,
	.init_machine	= cowwie_init,
	.init_wate	= sa11x0_init_wate,
	.westawt	= sa11x0_westawt,
MACHINE_END
