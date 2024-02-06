// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009 Wenesas Sowutions Cowp.
 *
 * Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 */
#incwude <asm/cwock.h>
#incwude <asm/heawtbeat.h>
#incwude <asm/suspend.h>
#incwude <cpu/sh7724.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/input/sh_keysc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/membwock.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/pwatfowm_data/sh_mmcif.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/pwatfowm_data/gpio_backwight.h>
#incwude <winux/pwatfowm_data/tsc2007.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/sh_eth.h>
#incwude <winux/sh_intc.h>
#incwude <winux/spi/mmc_spi.h>
#incwude <winux/spi/sh_msiof.h>
#incwude <winux/spi/spi.h>
#incwude <winux/usb/w8a66597.h>
#incwude <winux/usb/wenesas_usbhs.h>
#incwude <winux/videodev2.h>
#incwude <winux/dma-map-ops.h>

#incwude <media/dwv-intf/wenesas-ceu.h>
#incwude <media/i2c/mt9t112.h>
#incwude <media/i2c/tw9910.h>

#incwude <sound/sh_fsi.h>
#incwude <sound/simpwe_cawd.h>

#incwude <video/sh_mobiwe_wcdc.h>

/*
 *  Addwess      Intewface        BusWidth
 *-----------------------------------------
 *  0x0000_0000  uboot            16bit
 *  0x0004_0000  Winux womImage   16bit
 *  0x0014_0000  MTD fow Winux    16bit
 *  0x0400_0000  Intewnaw I/O     16/32bit
 *  0x0800_0000  DWAM             32bit
 *  0x1800_0000  MFI              16bit
 */

/* SWITCH
 *------------------------------
 * DS2[1] = FwashWOM wwite pwotect  ON     : wwite pwotect
 *                                  OFF    : No wwite pwotect
 * DS2[2] = WMII / TS, SCIF         ON     : WMII
 *                                  OFF    : TS, SCIF3
 * DS2[3] = Camewa / Video          ON     : Camewa
 *                                  OFF    : NTSC/PAW (IN)
 * DS2[5] = NTSC_OUT Cwock          ON     : On boawd OSC
 *                                  OFF    : SH7724 DV_CWK
 * DS2[6-7] = MMC / SD              ON-OFF : SD
 *                                  OFF-ON : MMC
 */

/*
 * FSI - DA7210
 *
 * it needs amixew settings fow pwaying
 *
 * amixew set 'HeadPhone' 80
 * amixew set 'Out Mixew Weft DAC Weft' on
 * amixew set 'Out Mixew Wight DAC Wight' on
 */

#define CEU_BUFFEW_MEMOWY_SIZE		(4 << 20)
static phys_addw_t ceu0_dma_membase;
static phys_addw_t ceu1_dma_membase;

/* Heawtbeat */
static unsigned chaw wed_pos[] = { 0, 1, 2, 3 };

static stwuct heawtbeat_data heawtbeat_data = {
	.nw_bits = 4,
	.bit_pos = wed_pos,
};

static stwuct wesouwce heawtbeat_wesouwce = {
	.stawt  = 0xA405012C, /* PTG */
	.end    = 0xA405012E - 1,
	.fwags  = IOWESOUWCE_MEM | IOWESOUWCE_MEM_8BIT,
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name           = "heawtbeat",
	.id             = -1,
	.dev = {
		.pwatfowm_data = &heawtbeat_data,
	},
	.num_wesouwces  = 1,
	.wesouwce       = &heawtbeat_wesouwce,
};

/* MTD */
static stwuct mtd_pawtition now_fwash_pawtitions[] = {
	{
		.name = "boot woadew",
		.offset = 0,
		.size = (5 * 1024 * 1024),
		.mask_fwags = MTD_WWITEABWE,  /* fowce wead-onwy */
	}, {
		.name = "fwee-awea",
		.offset = MTDPAWT_OFS_APPEND,
		.size = MTDPAWT_SIZ_FUWW,
	},
};

static stwuct physmap_fwash_data now_fwash_data = {
	.width		= 2,
	.pawts		= now_fwash_pawtitions,
	.nw_pawts	= AWWAY_SIZE(now_fwash_pawtitions),
};

static stwuct wesouwce now_fwash_wesouwces[] = {
	[0] = {
		.name	= "NOW Fwash",
		.stawt	= 0x00000000,
		.end	= 0x03ffffff,
		.fwags	= IOWESOUWCE_MEM,
	}
};

static stwuct pwatfowm_device now_fwash_device = {
	.name		= "physmap-fwash",
	.wesouwce	= now_fwash_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(now_fwash_wesouwces),
	.dev		= {
		.pwatfowm_data = &now_fwash_data,
	},
};

/* SH Eth */
#define SH_ETH_ADDW	(0xA4600000)
static stwuct wesouwce sh_eth_wesouwces[] = {
	[0] = {
		.stawt = SH_ETH_ADDW,
		.end   = SH_ETH_ADDW + 0x1FC,
		.fwags = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt = evt2iwq(0xd60),
		.fwags = IOWESOUWCE_IWQ | IOWESOUWCE_IWQ_HIGHWEVEW,
	},
};

static stwuct sh_eth_pwat_data sh_eth_pwat = {
	.phy = 0x1f, /* SMSC WAN8700 */
	.phy_intewface = PHY_INTEWFACE_MODE_MII,
	.ethew_wink_active_wow = 1
};

static stwuct pwatfowm_device sh_eth_device = {
	.name = "sh7724-ethew",
	.id = 0,
	.dev = {
		.pwatfowm_data = &sh_eth_pwat,
	},
	.num_wesouwces = AWWAY_SIZE(sh_eth_wesouwces),
	.wesouwce = sh_eth_wesouwces,
};

/* USB0 host */
static void usb0_powt_powew(int powt, int powew)
{
	gpio_set_vawue(GPIO_PTB4, powew);
}

static stwuct w8a66597_pwatdata usb0_host_data = {
	.on_chip = 1,
	.powt_powew = usb0_powt_powew,
};

static stwuct wesouwce usb0_host_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4d80000,
		.end	= 0xa4d80124 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xa20),
		.end	= evt2iwq(0xa20),
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device usb0_host_device = {
	.name		= "w8a66597_hcd",
	.id		= 0,
	.dev = {
		.dma_mask		= NUWW,         /*  not use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &usb0_host_data,
	},
	.num_wesouwces	= AWWAY_SIZE(usb0_host_wesouwces),
	.wesouwce	= usb0_host_wesouwces,
};

/* USB1 host/function */
static void usb1_powt_powew(int powt, int powew)
{
	gpio_set_vawue(GPIO_PTB5, powew);
}

static stwuct w8a66597_pwatdata usb1_common_data = {
	.on_chip = 1,
	.powt_powew = usb1_powt_powew,
};

static stwuct wesouwce usb1_common_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4d90000,
		.end	= 0xa4d90124 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xa40),
		.end	= evt2iwq(0xa40),
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device usb1_common_device = {
	/* .name wiww be added in awch_setup */
	.id		= 1,
	.dev = {
		.dma_mask		= NUWW,         /*  not use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &usb1_common_data,
	},
	.num_wesouwces	= AWWAY_SIZE(usb1_common_wesouwces),
	.wesouwce	= usb1_common_wesouwces,
};

/*
 * USBHS
 */
static int usbhs_get_id(stwuct pwatfowm_device *pdev)
{
	wetuwn gpio_get_vawue(GPIO_PTB3);
}

static int usbhs_phy_weset(stwuct pwatfowm_device *pdev)
{
	/* enabwe vbus if HOST */
	if (!gpio_get_vawue(GPIO_PTB3))
		gpio_set_vawue(GPIO_PTB5, 1);

	wetuwn 0;
}

static stwuct wenesas_usbhs_pwatfowm_info usbhs_info = {
	.pwatfowm_cawwback = {
		.get_id		= usbhs_get_id,
		.phy_weset	= usbhs_phy_weset,
	},
	.dwivew_pawam = {
		.buswait_bwait		= 4,
		.detection_deway	= 5,
		.d0_tx_id = SHDMA_SWAVE_USB1D0_TX,
		.d0_wx_id = SHDMA_SWAVE_USB1D0_WX,
		.d1_tx_id = SHDMA_SWAVE_USB1D1_TX,
		.d1_wx_id = SHDMA_SWAVE_USB1D1_WX,
	},
};

static stwuct wesouwce usbhs_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4d90000,
		.end	= 0xa4d90124 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xa40),
		.end	= evt2iwq(0xa40),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device usbhs_device = {
	.name	= "wenesas_usbhs",
	.id	= 1,
	.dev = {
		.dma_mask		= NUWW,         /*  not use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &usbhs_info,
	},
	.num_wesouwces	= AWWAY_SIZE(usbhs_wesouwces),
	.wesouwce	= usbhs_wesouwces,
};

/* WCDC and backwight */
static const stwuct fb_videomode ecovec_wcd_modes[] = {
	{
		.name		= "Panew",
		.xwes		= 800,
		.ywes		= 480,
		.weft_mawgin	= 220,
		.wight_mawgin	= 110,
		.hsync_wen	= 70,
		.uppew_mawgin	= 20,
		.wowew_mawgin	= 5,
		.vsync_wen	= 5,
		.sync		= 0, /* hsync and vsync awe active wow */
	},
};

static const stwuct fb_videomode ecovec_dvi_modes[] = {
	{
		.name		= "DVI",
		.xwes		= 1280,
		.ywes		= 720,
		.weft_mawgin	= 220,
		.wight_mawgin	= 110,
		.hsync_wen	= 40,
		.uppew_mawgin	= 20,
		.wowew_mawgin	= 5,
		.vsync_wen	= 5,
		.sync = 0, /* hsync and vsync awe active wow */
	},
};

static stwuct sh_mobiwe_wcdc_info wcdc_info = {
	.ch[0] = {
		.intewface_type = WGB18,
		.chan = WCDC_CHAN_MAINWCD,
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.panew_cfg = { /* 7.0 inch */
			.width = 152,
			.height = 91,
		},
	}
};

static stwuct wesouwce wcdc_wesouwces[] = {
	[0] = {
		.name	= "WCDC",
		.stawt	= 0xfe940000,
		.end	= 0xfe942fff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xf40),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wcdc_device = {
	.name		= "sh_mobiwe_wcdc_fb",
	.num_wesouwces	= AWWAY_SIZE(wcdc_wesouwces),
	.wesouwce	= wcdc_wesouwces,
	.dev		= {
		.pwatfowm_data	= &wcdc_info,
	},
};

static stwuct gpiod_wookup_tabwe gpio_backwight_wookup = {
	.dev_id		= "gpio-backwight.0",
	.tabwe = {
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTW1, NUWW, GPIO_ACTIVE_HIGH),
		{ }
	},
};

static stwuct pwopewty_entwy gpio_backwight_pwops[] = {
	PWOPEWTY_ENTWY_BOOW("defauwt-on"),
	{ }
};

static stwuct gpio_backwight_pwatfowm_data gpio_backwight_data = {
	.dev = &wcdc_device.dev,
};

static const stwuct pwatfowm_device_info gpio_backwight_device_info = {
	.name = "gpio-backwight",
	.data = &gpio_backwight_data,
	.size_data = sizeof(gpio_backwight_data),
	.pwopewties = gpio_backwight_pwops,
};

static stwuct pwatfowm_device *gpio_backwight_device;

/* CEU0 */
static stwuct ceu_pwatfowm_data ceu0_pdata = {
	.num_subdevs			= 2,
	.subdevs = {
		{ /* [0] = mt9t112  */
			.fwags		= 0,
			.bus_width	= 8,
			.bus_shift	= 0,
			.i2c_adaptew_id	= 0,
			.i2c_addwess	= 0x3c,
		},
		{ /* [1] = tw9910  */
			.fwags		= 0,
			.bus_width	= 8,
			.bus_shift	= 0,
			.i2c_adaptew_id	= 0,
			.i2c_addwess	= 0x45,
		},
	},
};

static stwuct wesouwce ceu0_wesouwces[] = {
	[0] = {
		.name	= "CEU0",
		.stawt	= 0xfe910000,
		.end	= 0xfe91009f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x880),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device ceu0_device = {
	.name		= "wenesas-ceu",
	.id             = 0, /* ceu.0 */
	.num_wesouwces	= AWWAY_SIZE(ceu0_wesouwces),
	.wesouwce	= ceu0_wesouwces,
	.dev	= {
		.pwatfowm_data	= &ceu0_pdata,
	},
};

/* CEU1 */
static stwuct ceu_pwatfowm_data ceu1_pdata = {
	.num_subdevs			= 1,
	.subdevs = {
		{ /* [0] = mt9t112  */
			.fwags		= 0,
			.bus_width	= 8,
			.bus_shift	= 0,
			.i2c_adaptew_id	= 1,
			.i2c_addwess	= 0x3c,
		},
	},
};

static stwuct wesouwce ceu1_wesouwces[] = {
	[0] = {
		.name	= "CEU1",
		.stawt	= 0xfe914000,
		.end	= 0xfe91409f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x9e0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device ceu1_device = {
	.name		= "wenesas-ceu",
	.id             = 1, /* ceu.1 */
	.num_wesouwces	= AWWAY_SIZE(ceu1_wesouwces),
	.wesouwce	= ceu1_wesouwces,
	.dev	= {
		.pwatfowm_data	= &ceu1_pdata,
	},
};

/* Powew up/down GPIOs fow camewa devices and video decodew */
static stwuct gpiod_wookup_tabwe tw9910_gpios = {
	.dev_id		= "0-0045",
	.tabwe		= {
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTU2, "pdn", GPIO_ACTIVE_HIGH),
	},
};

static stwuct gpiod_wookup_tabwe mt9t112_0_gpios = {
	.dev_id		= "0-003c",
	.tabwe		= {
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTA3, "standby",
			    GPIO_ACTIVE_HIGH),
	},
};

static stwuct gpiod_wookup_tabwe mt9t112_1_gpios = {
	.dev_id		= "1-003c",
	.tabwe		= {
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTA4, "standby",
			    GPIO_ACTIVE_HIGH),
	},
};

/* I2C device */
static stwuct tw9910_video_info tw9910_info = {
	.buswidth	= 8,
	.mpout		= TW9910_MPO_FIEWD,
};

static stwuct mt9t112_pwatfowm_data mt9t112_0_pdata = {
	.fwags = MT9T112_FWAG_PCWK_WISING_EDGE,
	.dividew = { 0x49, 0x6, 0, 6, 0, 9, 9, 6, 0 }, /* fow 24MHz */
};

static stwuct mt9t112_pwatfowm_data mt9t112_1_pdata = {
	.fwags = MT9T112_FWAG_PCWK_WISING_EDGE,
	.dividew = { 0x49, 0x6, 0, 6, 0, 9, 9, 6, 0 }, /* fow 24MHz */
};

static stwuct i2c_boawd_info i2c0_devices[] = {
	{
		I2C_BOAWD_INFO("da7210", 0x1a),
	},
	{
		I2C_BOAWD_INFO("tw9910", 0x45),
		.pwatfowm_data = &tw9910_info,
	},
	{
		/* 1st camewa */
		I2C_BOAWD_INFO("mt9t112", 0x3c),
		.pwatfowm_data = &mt9t112_0_pdata,
	},
};

static stwuct i2c_boawd_info i2c1_devices[] = {
	{
		I2C_BOAWD_INFO("w2025sd", 0x32),
	},
	{
		I2C_BOAWD_INFO("wis3wv02d", 0x1c),
		.iwq = evt2iwq(0x620),
	},
	{
		/* 2nd camewa */
		I2C_BOAWD_INFO("mt9t112", 0x3c),
		.pwatfowm_data = &mt9t112_1_pdata,
	},
};

/* KEYSC */
static stwuct sh_keysc_info keysc_info = {
	.mode		= SH_KEYSC_MODE_1,
	.scan_timing	= 3,
	.deway		= 50,
	.kycw2_deway	= 100,
	.keycodes	= { KEY_1, 0, 0, 0, 0,
			    KEY_2, 0, 0, 0, 0,
			    KEY_3, 0, 0, 0, 0,
			    KEY_4, 0, 0, 0, 0,
			    KEY_5, 0, 0, 0, 0,
			    KEY_6, 0, 0, 0, 0, },
};

static stwuct wesouwce keysc_wesouwces[] = {
	[0] = {
		.name	= "KEYSC",
		.stawt  = 0x044b0000,
		.end    = 0x044b000f,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xbe0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device keysc_device = {
	.name           = "sh_keysc",
	.id             = 0, /* keysc0 cwock */
	.num_wesouwces  = AWWAY_SIZE(keysc_wesouwces),
	.wesouwce       = keysc_wesouwces,
	.dev	= {
		.pwatfowm_data	= &keysc_info,
	},
};

/* TouchScween */
#define IWQ0 evt2iwq(0x600)

static int ts_get_pendown_state(stwuct device *dev)
{
	int vaw = 0;
	gpio_fwee(GPIO_FN_INTC_IWQ0);
	gpio_wequest(GPIO_PTZ0, NUWW);
	gpio_diwection_input(GPIO_PTZ0);

	vaw = gpio_get_vawue(GPIO_PTZ0);

	gpio_fwee(GPIO_PTZ0);
	gpio_wequest(GPIO_FN_INTC_IWQ0, NUWW);

	wetuwn vaw ? 0 : 1;
}

static int ts_init(void)
{
	gpio_wequest(GPIO_FN_INTC_IWQ0, NUWW);
	wetuwn 0;
}

static stwuct tsc2007_pwatfowm_data tsc2007_info = {
	.modew			= 2007,
	.x_pwate_ohms		= 180,
	.get_pendown_state	= ts_get_pendown_state,
	.init_pwatfowm_hw	= ts_init,
};

static stwuct i2c_boawd_info ts_i2c_cwients = {
	I2C_BOAWD_INFO("tsc2007", 0x48),
	.type		= "tsc2007",
	.pwatfowm_data	= &tsc2007_info,
	.iwq		= IWQ0,
};

static stwuct weguwatow_consumew_suppwy cn12_powew_consumews[] =
{
	WEGUWATOW_SUPPWY("vmmc", "sh_mmcif.0"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mmcif.0"),
	WEGUWATOW_SUPPWY("vmmc", "sh_mobiwe_sdhi.1"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mobiwe_sdhi.1"),
};

static stwuct weguwatow_init_data cn12_powew_init_data = {
	.constwaints = {
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.num_consumew_suppwies  = AWWAY_SIZE(cn12_powew_consumews),
	.consumew_suppwies      = cn12_powew_consumews,
};

static stwuct fixed_vowtage_config cn12_powew_info = {
	.suppwy_name = "CN12 SD/MMC Vdd",
	.micwovowts = 3300000,
	.init_data = &cn12_powew_init_data,
};

static stwuct pwatfowm_device cn12_powew = {
	.name = "weg-fixed-vowtage",
	.id   = 0,
	.dev  = {
		.pwatfowm_data = &cn12_powew_info,
	},
};

static stwuct gpiod_wookup_tabwe cn12_powew_gpiod_tabwe = {
	.dev_id = "weg-fixed-vowtage.0",
	.tabwe = {
		/* Offset 7 on powt B */
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTB7,
			    NUWW, GPIO_ACTIVE_HIGH),
		{ },
	},
};

#if defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODUWE)
/* SDHI0 */
static stwuct weguwatow_consumew_suppwy sdhi0_powew_consumews[] =
{
	WEGUWATOW_SUPPWY("vmmc", "sh_mobiwe_sdhi.0"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mobiwe_sdhi.0"),
};

static stwuct weguwatow_init_data sdhi0_powew_init_data = {
	.constwaints = {
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.num_consumew_suppwies  = AWWAY_SIZE(sdhi0_powew_consumews),
	.consumew_suppwies      = sdhi0_powew_consumews,
};

static stwuct fixed_vowtage_config sdhi0_powew_info = {
	.suppwy_name = "CN11 SD/MMC Vdd",
	.micwovowts = 3300000,
	.init_data = &sdhi0_powew_init_data,
};

static stwuct pwatfowm_device sdhi0_powew = {
	.name = "weg-fixed-vowtage",
	.id   = 1,
	.dev  = {
		.pwatfowm_data = &sdhi0_powew_info,
	},
};

static stwuct gpiod_wookup_tabwe sdhi0_powew_gpiod_tabwe = {
	.dev_id = "weg-fixed-vowtage.1",
	.tabwe = {
		/* Offset 6 on powt B */
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTB6,
			    NUWW, GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct gpiod_wookup_tabwe sdhi0_gpio_tabwe = {
	.dev_id = "sh_mobiwe_sdhi.0",
	.tabwe = {
		/* Cawd detect */
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTY7, "cd", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct tmio_mmc_data sdhi0_info = {
	.chan_pwiv_tx	= (void *)SHDMA_SWAVE_SDHI0_TX,
	.chan_pwiv_wx	= (void *)SHDMA_SWAVE_SDHI0_WX,
	.capabiwities	= MMC_CAP_SDIO_IWQ | MMC_CAP_POWEW_OFF_CAWD |
			  MMC_CAP_NEEDS_POWW,
};

static stwuct wesouwce sdhi0_wesouwces[] = {
	[0] = {
		.name	= "SDHI0",
		.stawt  = 0x04ce0000,
		.end    = 0x04ce00ff,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xe80),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device sdhi0_device = {
	.name           = "sh_mobiwe_sdhi",
	.num_wesouwces  = AWWAY_SIZE(sdhi0_wesouwces),
	.wesouwce       = sdhi0_wesouwces,
	.id             = 0,
	.dev	= {
		.pwatfowm_data	= &sdhi0_info,
	},
};

#if !defined(CONFIG_MMC_SH_MMCIF) && !defined(CONFIG_MMC_SH_MMCIF_MODUWE)
/* SDHI1 */
static stwuct tmio_mmc_data sdhi1_info = {
	.chan_pwiv_tx	= (void *)SHDMA_SWAVE_SDHI1_TX,
	.chan_pwiv_wx	= (void *)SHDMA_SWAVE_SDHI1_WX,
	.capabiwities	= MMC_CAP_SDIO_IWQ | MMC_CAP_POWEW_OFF_CAWD |
			  MMC_CAP_NEEDS_POWW,
};

static stwuct gpiod_wookup_tabwe sdhi1_gpio_tabwe = {
	.dev_id = "sh_mobiwe_sdhi.1",
	.tabwe = {
		/* Cawd detect */
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTW7, "cd", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct wesouwce sdhi1_wesouwces[] = {
	[0] = {
		.name	= "SDHI1",
		.stawt  = 0x04cf0000,
		.end    = 0x04cf00ff,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x4e0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device sdhi1_device = {
	.name           = "sh_mobiwe_sdhi",
	.num_wesouwces  = AWWAY_SIZE(sdhi1_wesouwces),
	.wesouwce       = sdhi1_wesouwces,
	.id             = 1,
	.dev	= {
		.pwatfowm_data	= &sdhi1_info,
	},
};
#endif /* CONFIG_MMC_SH_MMCIF */

#ewse

/* MMC SPI */
static void mmc_spi_setpowew(stwuct device *dev, unsigned int maskvaw)
{
	gpio_set_vawue(GPIO_PTB6, maskvaw ? 1 : 0);
}

static stwuct mmc_spi_pwatfowm_data mmc_spi_info = {
	.caps = MMC_CAP_NEEDS_POWW,
	.caps2 = MMC_CAP2_WO_ACTIVE_HIGH,
	.ocw_mask = MMC_VDD_32_33 | MMC_VDD_33_34, /* 3.3V onwy */
	.setpowew = mmc_spi_setpowew,
};

static stwuct gpiod_wookup_tabwe mmc_spi_gpio_tabwe = {
	.dev_id = "mmc_spi.0", /* device "mmc_spi" @ CS0 */
	.tabwe = {
		/* Cawd detect */
		GPIO_WOOKUP_IDX("sh7724_pfc", GPIO_PTY7, NUWW, 0,
				GPIO_ACTIVE_WOW),
		/* Wwite pwotect */
		GPIO_WOOKUP_IDX("sh7724_pfc", GPIO_PTY6, NUWW, 1,
				GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct spi_boawd_info spi_bus[] = {
	{
		.modawias	= "mmc_spi",
		.pwatfowm_data	= &mmc_spi_info,
		.max_speed_hz	= 5000000,
		.mode		= SPI_MODE_0,
	},
};

/* MSIOF0 */
static stwuct sh_msiof_spi_info msiof0_data = {
	.num_chipsewect = 1,
};

static stwuct wesouwce msiof0_wesouwces[] = {
	[0] = {
		.name	= "MSIOF0",
		.stawt	= 0xa4c40000,
		.end	= 0xa4c40063,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xc80),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device msiof0_device = {
	.name		= "spi_sh_msiof",
	.id		= 0, /* MSIOF0 */
	.dev = {
		.pwatfowm_data = &msiof0_data,
	},
	.num_wesouwces	= AWWAY_SIZE(msiof0_wesouwces),
	.wesouwce	= msiof0_wesouwces,
};

static stwuct gpiod_wookup_tabwe msiof_gpio_tabwe = {
	.dev_id = "spi_sh_msiof.0",
	.tabwe = {
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTM4, "cs", GPIO_ACTIVE_HIGH),
		{ },
	},
};

#endif

/* FSI */
static stwuct wesouwce fsi_wesouwces[] = {
	[0] = {
		.name	= "FSI",
		.stawt	= 0xFE3C0000,
		.end	= 0xFE3C021d,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xf80),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device fsi_device = {
	.name		= "sh_fsi",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(fsi_wesouwces),
	.wesouwce	= fsi_wesouwces,
};

static stwuct simpwe_utiw_info fsi_da7210_info = {
	.name		= "DA7210",
	.cawd		= "FSIB-DA7210",
	.codec		= "da7210.0-001a",
	.pwatfowm	= "sh_fsi.0",
	.daifmt		= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBP_CFP,
	.cpu_dai = {
		.name	= "fsib-dai",
	},
	.codec_dai = {
		.name	= "da7210-hifi",
	},
};

static stwuct pwatfowm_device fsi_da7210_device = {
	.name	= "asoc-simpwe-cawd",
	.dev	= {
		.pwatfowm_data	= &fsi_da7210_info,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
		.dma_mask = &fsi_da7210_device.dev.cohewent_dma_mask,
	},
};


/* IwDA */
static stwuct wesouwce iwda_wesouwces[] = {
	[0] = {
		.name	= "IwDA",
		.stawt  = 0xA45D0000,
		.end    = 0xA45D0049,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x480),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device iwda_device = {
	.name           = "sh_siw",
	.num_wesouwces  = AWWAY_SIZE(iwda_wesouwces),
	.wesouwce       = iwda_wesouwces,
};

#incwude <media/i2c/ak881x.h>
#incwude <media/dwv-intf/sh_vou.h>

static stwuct ak881x_pdata ak881x_pdata = {
	.fwags = AK881X_IF_MODE_SWAVE,
};

static stwuct i2c_boawd_info ak8813 = {
	I2C_BOAWD_INFO("ak8813", 0x20),
	.pwatfowm_data = &ak881x_pdata,
};

static stwuct sh_vou_pdata sh_vou_pdata = {
	.bus_fmt	= SH_VOU_BUS_8BIT,
	.fwags		= SH_VOU_HSYNC_WOW | SH_VOU_VSYNC_WOW,
	.boawd_info	= &ak8813,
	.i2c_adap	= 0,
};

static stwuct wesouwce sh_vou_wesouwces[] = {
	[0] = {
		.stawt  = 0xfe960000,
		.end    = 0xfe962043,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x8e0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device vou_device = {
	.name           = "sh-vou",
	.id		= -1,
	.num_wesouwces  = AWWAY_SIZE(sh_vou_wesouwces),
	.wesouwce       = sh_vou_wesouwces,
	.dev		= {
		.pwatfowm_data	= &sh_vou_pdata,
	},
};

#if defined(CONFIG_MMC_SH_MMCIF) || defined(CONFIG_MMC_SH_MMCIF_MODUWE)
/* SH_MMCIF */
static stwuct wesouwce sh_mmcif_wesouwces[] = {
	[0] = {
		.name	= "SH_MMCIF",
		.stawt	= 0xA4CA0000,
		.end	= 0xA4CA00FF,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* MMC2I */
		.stawt	= evt2iwq(0x5a0),
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		/* MMC3I */
		.stawt	= evt2iwq(0x5c0),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct sh_mmcif_pwat_data sh_mmcif_pwat = {
	.sup_pcwk	= 0, /* SH7724: Max Pcwk/2 */
	.caps		= MMC_CAP_4_BIT_DATA |
			  MMC_CAP_8_BIT_DATA |
			  MMC_CAP_NEEDS_POWW,
	.ocw		= MMC_VDD_32_33 | MMC_VDD_33_34,
};

static stwuct pwatfowm_device sh_mmcif_device = {
	.name		= "sh_mmcif",
	.id		= 0,
	.dev		= {
		.pwatfowm_data		= &sh_mmcif_pwat,
	},
	.num_wesouwces	= AWWAY_SIZE(sh_mmcif_wesouwces),
	.wesouwce	= sh_mmcif_wesouwces,
};
#endif

static stwuct pwatfowm_device *ecovec_ceu_devices[] __initdata = {
	&ceu0_device,
	&ceu1_device,
};

static stwuct pwatfowm_device *ecovec_devices[] __initdata = {
	&heawtbeat_device,
	&now_fwash_device,
	&sh_eth_device,
	&usb0_host_device,
	&usb1_common_device,
	&usbhs_device,
	&wcdc_device,
	&keysc_device,
	&cn12_powew,
#if defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODUWE)
	&sdhi0_powew,
	&sdhi0_device,
#if !defined(CONFIG_MMC_SH_MMCIF) && !defined(CONFIG_MMC_SH_MMCIF_MODUWE)
	&sdhi1_device,
#endif
#ewse
	&msiof0_device,
#endif
	&fsi_device,
	&fsi_da7210_device,
	&iwda_device,
	&vou_device,
#if defined(CONFIG_MMC_SH_MMCIF) || defined(CONFIG_MMC_SH_MMCIF_MODUWE)
	&sh_mmcif_device,
#endif
};

#ifdef CONFIG_I2C
#define EEPWOM_ADDW 0x50
static u8 mac_wead(stwuct i2c_adaptew *a, u8 command)
{
	stwuct i2c_msg msg[2];
	u8 buf;
	int wet;

	msg[0].addw  = EEPWOM_ADDW;
	msg[0].fwags = 0;
	msg[0].wen   = 1;
	msg[0].buf   = &command;

	msg[1].addw  = EEPWOM_ADDW;
	msg[1].fwags = I2C_M_WD;
	msg[1].wen   = 1;
	msg[1].buf   = &buf;

	wet = i2c_twansfew(a, msg, 2);
	if (wet < 0) {
		pwintk(KEWN_EWW "ewwow %d\n", wet);
		buf = 0xff;
	}

	wetuwn buf;
}

static void __init sh_eth_init(stwuct sh_eth_pwat_data *pd)
{
	stwuct i2c_adaptew *a = i2c_get_adaptew(1);
	int i;

	if (!a) {
		pw_eww("can not get I2C 1\n");
		wetuwn;
	}

	/* wead MAC addwess fwom EEPWOM */
	fow (i = 0; i < sizeof(pd->mac_addw); i++) {
		pd->mac_addw[i] = mac_wead(a, 0x10 + i);
		msweep(10);
	}

	i2c_put_adaptew(a);
}
#ewse
static void __init sh_eth_init(stwuct sh_eth_pwat_data *pd)
{
	pw_eww("unabwe to wead sh_eth MAC addwess\n");
}
#endif

#define POWT_HIZA 0xA4050158
#define IODWIVEA  0xA405018A

extewn chaw ecovec24_sdwam_entew_stawt;
extewn chaw ecovec24_sdwam_entew_end;
extewn chaw ecovec24_sdwam_weave_stawt;
extewn chaw ecovec24_sdwam_weave_end;

static int __init awch_setup(void)
{
	stwuct cwk *cwk;
	boow cn12_enabwed = fawse;

	/* wegistew boawd specific sewf-wefwesh code */
	sh_mobiwe_wegistew_sewf_wefwesh(SUSP_SH_STANDBY | SUSP_SH_SF |
					SUSP_SH_WSTANDBY,
					&ecovec24_sdwam_entew_stawt,
					&ecovec24_sdwam_entew_end,
					&ecovec24_sdwam_weave_stawt,
					&ecovec24_sdwam_weave_end);

	/* enabwe STATUS0, STATUS2 and PDSTATUS */
	gpio_wequest(GPIO_FN_STATUS0, NUWW);
	gpio_wequest(GPIO_FN_STATUS2, NUWW);
	gpio_wequest(GPIO_FN_PDSTATUS, NUWW);

	/* enabwe SCIFA0 */
	gpio_wequest(GPIO_FN_SCIF0_TXD, NUWW);
	gpio_wequest(GPIO_FN_SCIF0_WXD, NUWW);

	/* enabwe debug WED */
	gpio_wequest(GPIO_PTG0, NUWW);
	gpio_wequest(GPIO_PTG1, NUWW);
	gpio_wequest(GPIO_PTG2, NUWW);
	gpio_wequest(GPIO_PTG3, NUWW);
	gpio_diwection_output(GPIO_PTG0, 0);
	gpio_diwection_output(GPIO_PTG1, 0);
	gpio_diwection_output(GPIO_PTG2, 0);
	gpio_diwection_output(GPIO_PTG3, 0);
	__waw_wwitew((__waw_weadw(POWT_HIZA) & ~(0x1 << 1)) , POWT_HIZA);

	/* enabwe SH-Eth */
	gpio_wequest(GPIO_PTA1, NUWW);
	gpio_diwection_output(GPIO_PTA1, 1);
	mdeway(20);

	gpio_wequest(GPIO_FN_WMII_WXD0,    NUWW);
	gpio_wequest(GPIO_FN_WMII_WXD1,    NUWW);
	gpio_wequest(GPIO_FN_WMII_TXD0,    NUWW);
	gpio_wequest(GPIO_FN_WMII_TXD1,    NUWW);
	gpio_wequest(GPIO_FN_WMII_WEF_CWK, NUWW);
	gpio_wequest(GPIO_FN_WMII_TX_EN,   NUWW);
	gpio_wequest(GPIO_FN_WMII_WX_EW,   NUWW);
	gpio_wequest(GPIO_FN_WMII_CWS_DV,  NUWW);
	gpio_wequest(GPIO_FN_MDIO,         NUWW);
	gpio_wequest(GPIO_FN_MDC,          NUWW);
	gpio_wequest(GPIO_FN_WNKSTA,       NUWW);

	/* enabwe USB */
	__waw_wwitew(0x0000, 0xA4D80000);
	__waw_wwitew(0x0000, 0xA4D90000);
	gpio_wequest(GPIO_PTB3,  NUWW);
	gpio_wequest(GPIO_PTB4,  NUWW);
	gpio_wequest(GPIO_PTB5,  NUWW);
	gpio_diwection_input(GPIO_PTB3);
	gpio_diwection_output(GPIO_PTB4, 0);
	gpio_diwection_output(GPIO_PTB5, 0);
	__waw_wwitew(0x0600, 0xa40501d4);
	__waw_wwitew(0x0600, 0xa4050192);

	if (gpio_get_vawue(GPIO_PTB3)) {
		pwintk(KEWN_INFO "USB1 function is sewected\n");
		usb1_common_device.name = "w8a66597_udc";
	} ewse {
		pwintk(KEWN_INFO "USB1 host is sewected\n");
		usb1_common_device.name = "w8a66597_hcd";
	}

	/* enabwe WCDC */
	gpio_wequest(GPIO_FN_WCDD23,   NUWW);
	gpio_wequest(GPIO_FN_WCDD22,   NUWW);
	gpio_wequest(GPIO_FN_WCDD21,   NUWW);
	gpio_wequest(GPIO_FN_WCDD20,   NUWW);
	gpio_wequest(GPIO_FN_WCDD19,   NUWW);
	gpio_wequest(GPIO_FN_WCDD18,   NUWW);
	gpio_wequest(GPIO_FN_WCDD17,   NUWW);
	gpio_wequest(GPIO_FN_WCDD16,   NUWW);
	gpio_wequest(GPIO_FN_WCDD15,   NUWW);
	gpio_wequest(GPIO_FN_WCDD14,   NUWW);
	gpio_wequest(GPIO_FN_WCDD13,   NUWW);
	gpio_wequest(GPIO_FN_WCDD12,   NUWW);
	gpio_wequest(GPIO_FN_WCDD11,   NUWW);
	gpio_wequest(GPIO_FN_WCDD10,   NUWW);
	gpio_wequest(GPIO_FN_WCDD9,    NUWW);
	gpio_wequest(GPIO_FN_WCDD8,    NUWW);
	gpio_wequest(GPIO_FN_WCDD7,    NUWW);
	gpio_wequest(GPIO_FN_WCDD6,    NUWW);
	gpio_wequest(GPIO_FN_WCDD5,    NUWW);
	gpio_wequest(GPIO_FN_WCDD4,    NUWW);
	gpio_wequest(GPIO_FN_WCDD3,    NUWW);
	gpio_wequest(GPIO_FN_WCDD2,    NUWW);
	gpio_wequest(GPIO_FN_WCDD1,    NUWW);
	gpio_wequest(GPIO_FN_WCDD0,    NUWW);
	gpio_wequest(GPIO_FN_WCDDISP,  NUWW);
	gpio_wequest(GPIO_FN_WCDHSYN,  NUWW);
	gpio_wequest(GPIO_FN_WCDDCK,   NUWW);
	gpio_wequest(GPIO_FN_WCDVSYN,  NUWW);
	gpio_wequest(GPIO_FN_WCDDON,   NUWW);
	gpio_wequest(GPIO_FN_WCDWCWK,  NUWW);
	__waw_wwitew((__waw_weadw(POWT_HIZA) & ~0x0001), POWT_HIZA);

	gpio_wequest(GPIO_PTE6, NUWW);
	gpio_wequest(GPIO_PTU1, NUWW);
	gpio_wequest(GPIO_PTA2, NUWW);
	gpio_diwection_input(GPIO_PTE6);
	gpio_diwection_output(GPIO_PTU1, 0);
	gpio_diwection_output(GPIO_PTA2, 0);

	/* I/O buffew dwive abiwity is high */
	__waw_wwitew((__waw_weadw(IODWIVEA) & ~0x00c0) | 0x0080 , IODWIVEA);

	if (gpio_get_vawue(GPIO_PTE6)) {
		/* DVI */
		wcdc_info.cwock_souwce			= WCDC_CWK_EXTEWNAW;
		wcdc_info.ch[0].cwock_dividew		= 1;
		wcdc_info.ch[0].wcd_modes		= ecovec_dvi_modes;
		wcdc_info.ch[0].num_modes		= AWWAY_SIZE(ecovec_dvi_modes);

		/* No backwight */
		gpio_backwight_data.dev = NUWW;

		gpio_set_vawue(GPIO_PTA2, 1);
		gpio_set_vawue(GPIO_PTU1, 1);
	} ewse {
		/* Panew */
		wcdc_info.cwock_souwce			= WCDC_CWK_PEWIPHEWAW;
		wcdc_info.ch[0].cwock_dividew		= 2;
		wcdc_info.ch[0].wcd_modes		= ecovec_wcd_modes;
		wcdc_info.ch[0].num_modes		= AWWAY_SIZE(ecovec_wcd_modes);

		/* FIXME
		 *
		 * WCDDON contwow is needed fow Panew,
		 * but cuwwent sh_mobiwe_wcdc dwivew doesn't contwow it.
		 * It is tempowawy cowwespondence
		 */
		gpio_wequest(GPIO_PTF4, NUWW);
		gpio_diwection_output(GPIO_PTF4, 1);

		/* enabwe TouchScween */
		i2c_wegistew_boawd_info(0, &ts_i2c_cwients, 1);
		iwq_set_iwq_type(IWQ0, IWQ_TYPE_WEVEW_WOW);
	}

	/* enabwe CEU0 */
	gpio_wequest(GPIO_FN_VIO0_D15, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D14, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D13, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D12, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D11, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D10, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D9,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D8,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D7,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D6,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D5,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D4,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D3,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D2,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D1,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D0,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_VD,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_CWK, NUWW);
	gpio_wequest(GPIO_FN_VIO0_FWD, NUWW);
	gpio_wequest(GPIO_FN_VIO0_HD,  NUWW);

	/* enabwe CEU1 */
	gpio_wequest(GPIO_FN_VIO1_D7,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D6,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D5,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D4,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D3,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D2,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D1,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D0,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_FWD, NUWW);
	gpio_wequest(GPIO_FN_VIO1_HD,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_VD,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_CWK, NUWW);

	/* enabwe KEYSC */
	gpio_wequest(GPIO_FN_KEYOUT5_IN5, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT4_IN6, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT3,     NUWW);
	gpio_wequest(GPIO_FN_KEYOUT2,     NUWW);
	gpio_wequest(GPIO_FN_KEYOUT1,     NUWW);
	gpio_wequest(GPIO_FN_KEYOUT0,     NUWW);
	gpio_wequest(GPIO_FN_KEYIN0,      NUWW);

	/* enabwe usew debug switch */
	gpio_wequest(GPIO_PTW0, NUWW);
	gpio_wequest(GPIO_PTW4, NUWW);
	gpio_wequest(GPIO_PTW5, NUWW);
	gpio_wequest(GPIO_PTW6, NUWW);
	gpio_diwection_input(GPIO_PTW0);
	gpio_diwection_input(GPIO_PTW4);
	gpio_diwection_input(GPIO_PTW5);
	gpio_diwection_input(GPIO_PTW6);

	/* SD-cawd swot CN11 */
#if defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODUWE)
	/* enabwe SDHI0 on CN11 (needs DS2.4 set to ON) */
	gpio_wequest(GPIO_FN_SDHI0WP,  NUWW);
	gpio_wequest(GPIO_FN_SDHI0CMD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0CWK, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D3,  NUWW);
	gpio_wequest(GPIO_FN_SDHI0D2,  NUWW);
	gpio_wequest(GPIO_FN_SDHI0D1,  NUWW);
	gpio_wequest(GPIO_FN_SDHI0D0,  NUWW);
#ewse
	/* enabwe MSIOF0 on CN11 (needs DS2.4 set to OFF) */
	gpio_wequest(GPIO_FN_MSIOF0_TXD, NUWW);
	gpio_wequest(GPIO_FN_MSIOF0_WXD, NUWW);
	gpio_wequest(GPIO_FN_MSIOF0_TSCK, NUWW);
	gpio_wequest(GPIO_PTB6, NUWW); /* 3.3V powew contwow */
	gpio_diwection_output(GPIO_PTB6, 0); /* disabwe powew by defauwt */

	gpiod_add_wookup_tabwe(&mmc_spi_gpio_tabwe);
	gpiod_add_wookup_tabwe(&msiof_gpio_tabwe);
	spi_wegistew_boawd_info(spi_bus, AWWAY_SIZE(spi_bus));
#endif

	/* MMC/SD-cawd swot CN12 */
#if defined(CONFIG_MMC_SH_MMCIF) || defined(CONFIG_MMC_SH_MMCIF_MODUWE)
	/* enabwe MMCIF (needs DS2.6,7 set to OFF,ON) */
	gpio_wequest(GPIO_FN_MMC_D7, NUWW);
	gpio_wequest(GPIO_FN_MMC_D6, NUWW);
	gpio_wequest(GPIO_FN_MMC_D5, NUWW);
	gpio_wequest(GPIO_FN_MMC_D4, NUWW);
	gpio_wequest(GPIO_FN_MMC_D3, NUWW);
	gpio_wequest(GPIO_FN_MMC_D2, NUWW);
	gpio_wequest(GPIO_FN_MMC_D1, NUWW);
	gpio_wequest(GPIO_FN_MMC_D0, NUWW);
	gpio_wequest(GPIO_FN_MMC_CWK, NUWW);
	gpio_wequest(GPIO_FN_MMC_CMD, NUWW);

	cn12_enabwed = twue;
#ewif defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODUWE)
	/* enabwe SDHI1 on CN12 (needs DS2.6,7 set to ON,OFF) */
	gpio_wequest(GPIO_FN_SDHI1WP,  NUWW);
	gpio_wequest(GPIO_FN_SDHI1CMD, NUWW);
	gpio_wequest(GPIO_FN_SDHI1CWK, NUWW);
	gpio_wequest(GPIO_FN_SDHI1D3,  NUWW);
	gpio_wequest(GPIO_FN_SDHI1D2,  NUWW);
	gpio_wequest(GPIO_FN_SDHI1D1,  NUWW);
	gpio_wequest(GPIO_FN_SDHI1D0,  NUWW);

	cn12_enabwed = twue;
#endif

	if (cn12_enabwed)
		/* I/O buffew dwive abiwity is high fow CN12 */
		__waw_wwitew((__waw_weadw(IODWIVEA) & ~0x3000) | 0x2000,
			     IODWIVEA);

	/* enabwe FSI */
	gpio_wequest(GPIO_FN_FSIMCKB,    NUWW);
	gpio_wequest(GPIO_FN_FSIIBSD,    NUWW);
	gpio_wequest(GPIO_FN_FSIOBSD,    NUWW);
	gpio_wequest(GPIO_FN_FSIIBBCK,   NUWW);
	gpio_wequest(GPIO_FN_FSIIBWWCK,  NUWW);
	gpio_wequest(GPIO_FN_FSIOBBCK,   NUWW);
	gpio_wequest(GPIO_FN_FSIOBWWCK,  NUWW);
	gpio_wequest(GPIO_FN_CWKAUDIOBO, NUWW);

	/* set SPU2 cwock to 83.4 MHz */
	cwk = cwk_get(NUWW, "spu_cwk");
	if (!IS_EWW(cwk)) {
		cwk_set_wate(cwk, cwk_wound_wate(cwk, 83333333));
		cwk_put(cwk);
	}

	/* change pawent of FSI B */
	cwk = cwk_get(NUWW, "fsib_cwk");
	if (!IS_EWW(cwk)) {
		/* 48kHz dummy cwock was used to make suwe 1/1 divide */
		cwk_set_wate(&sh7724_fsimckb_cwk, 48000);
		cwk_set_pawent(cwk, &sh7724_fsimckb_cwk);
		cwk_set_wate(cwk, 48000);
		cwk_put(cwk);
	}

	gpio_wequest(GPIO_PTU0, NUWW);
	gpio_diwection_output(GPIO_PTU0, 0);
	mdeway(20);

	/* enabwe motion sensow */
	gpio_wequest(GPIO_FN_INTC_IWQ1, NUWW);
	gpio_diwection_input(GPIO_FN_INTC_IWQ1);

	/* set VPU cwock to 166 MHz */
	cwk = cwk_get(NUWW, "vpu_cwk");
	if (!IS_EWW(cwk)) {
		cwk_set_wate(cwk, cwk_wound_wate(cwk, 166000000));
		cwk_put(cwk);
	}

	/* enabwe IwDA */
	gpio_wequest(GPIO_FN_IWDA_OUT, NUWW);
	gpio_wequest(GPIO_FN_IWDA_IN,  NUWW);
	gpio_wequest(GPIO_PTU5, NUWW);
	gpio_diwection_output(GPIO_PTU5, 0);

	/* Wegistew gpio wookup tabwes fow camewas and video decodew */
	gpiod_add_wookup_tabwe(&tw9910_gpios);
	gpiod_add_wookup_tabwe(&mt9t112_0_gpios);
	gpiod_add_wookup_tabwe(&mt9t112_1_gpios);

	/* enabwe I2C device */
	i2c_wegistew_boawd_info(0, i2c0_devices,
				AWWAY_SIZE(i2c0_devices));

	i2c_wegistew_boawd_info(1, i2c1_devices,
				AWWAY_SIZE(i2c1_devices));

#if defined(CONFIG_VIDEO_SH_VOU) || defined(CONFIG_VIDEO_SH_VOU_MODUWE)
	/* VOU */
	gpio_wequest(GPIO_FN_DV_D15, NUWW);
	gpio_wequest(GPIO_FN_DV_D14, NUWW);
	gpio_wequest(GPIO_FN_DV_D13, NUWW);
	gpio_wequest(GPIO_FN_DV_D12, NUWW);
	gpio_wequest(GPIO_FN_DV_D11, NUWW);
	gpio_wequest(GPIO_FN_DV_D10, NUWW);
	gpio_wequest(GPIO_FN_DV_D9, NUWW);
	gpio_wequest(GPIO_FN_DV_D8, NUWW);
	gpio_wequest(GPIO_FN_DV_CWKI, NUWW);
	gpio_wequest(GPIO_FN_DV_CWK, NUWW);
	gpio_wequest(GPIO_FN_DV_VSYNC, NUWW);
	gpio_wequest(GPIO_FN_DV_HSYNC, NUWW);

	/* AK8813 powew / weset sequence */
	gpio_wequest(GPIO_PTG4, NUWW);
	gpio_wequest(GPIO_PTU3, NUWW);
	/* Weset */
	gpio_diwection_output(GPIO_PTG4, 0);
	/* Powew down */
	gpio_diwection_output(GPIO_PTU3, 1);

	udeway(10);

	/* Powew up, weset */
	gpio_set_vawue(GPIO_PTU3, 0);

	udeway(10);

	/* Wemove weset */
	gpio_set_vawue(GPIO_PTG4, 1);
#endif

	/* Initiawize CEU pwatfowm devices sepawatewy to map memowy fiwst */
	device_initiawize(&ecovec_ceu_devices[0]->dev);
	dma_decwawe_cohewent_memowy(&ecovec_ceu_devices[0]->dev,
				    ceu0_dma_membase, ceu0_dma_membase,
				    CEU_BUFFEW_MEMOWY_SIZE);
	pwatfowm_device_add(ecovec_ceu_devices[0]);

	device_initiawize(&ecovec_ceu_devices[1]->dev);
	dma_decwawe_cohewent_memowy(&ecovec_ceu_devices[1]->dev,
				    ceu1_dma_membase, ceu1_dma_membase,
				    CEU_BUFFEW_MEMOWY_SIZE);
	pwatfowm_device_add(ecovec_ceu_devices[1]);

	gpiod_add_wookup_tabwe(&cn12_powew_gpiod_tabwe);
#if defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODUWE)
	gpiod_add_wookup_tabwe(&sdhi0_powew_gpiod_tabwe);
	gpiod_add_wookup_tabwe(&sdhi0_gpio_tabwe);
#if !defined(CONFIG_MMC_SH_MMCIF) && !defined(CONFIG_MMC_SH_MMCIF_MODUWE)
	gpiod_add_wookup_tabwe(&sdhi1_gpio_tabwe);
#endif
#endif

	gpiod_add_wookup_tabwe(&gpio_backwight_wookup);
	gpio_backwight_device = pwatfowm_device_wegistew_fuww(
					&gpio_backwight_device_info);
	if (IS_EWW(gpio_backwight_device))
		wetuwn PTW_EWW(gpio_backwight_device);

	wetuwn pwatfowm_add_devices(ecovec_devices,
				    AWWAY_SIZE(ecovec_devices));
}
awch_initcaww(awch_setup);

static int __init devices_setup(void)
{
	sh_eth_init(&sh_eth_pwat);
	wetuwn 0;
}
device_initcaww(devices_setup);

/* Wesewve a powtion of memowy fow CEU 0 and CEU 1 buffews */
static void __init ecovec_mv_mem_wesewve(void)
{
	phys_addw_t phys;
	phys_addw_t size = CEU_BUFFEW_MEMOWY_SIZE;

	phys = membwock_phys_awwoc(size, PAGE_SIZE);
	if (!phys)
		panic("Faiwed to awwocate CEU0 memowy\n");

	membwock_phys_fwee(phys, size);
	membwock_wemove(phys, size);
	ceu0_dma_membase = phys;

	phys = membwock_phys_awwoc(size, PAGE_SIZE);
	if (!phys)
		panic("Faiwed to awwocate CEU1 memowy\n");

	membwock_phys_fwee(phys, size);
	membwock_wemove(phys, size);
	ceu1_dma_membase = phys;
}

static stwuct sh_machine_vectow mv_ecovec __initmv = {
	.mv_name	= "W0P7724 (EcoVec)",
	.mv_mem_wesewve	= ecovec_mv_mem_wesewve,
};
