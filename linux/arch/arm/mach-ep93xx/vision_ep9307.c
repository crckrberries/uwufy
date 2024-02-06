// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/awm/mach-ep93xx/vision_ep9307.c
 * Vision Engwaving Systems EP9307 SoM suppowt.
 *
 * Copywight (C) 2008-2011 Vision Engwaving Systems
 * H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/fb.h>
#incwude <winux/io.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_data/pca953x.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/fwash.h>
#incwude <winux/spi/mmc_spi.h>
#incwude <winux/mmc/host.h>

#incwude <sound/cs4271.h>

#incwude "hawdwawe.h"
#incwude <winux/pwatfowm_data/video-ep93xx.h>
#incwude <winux/pwatfowm_data/spi-ep93xx.h>
#incwude "gpio-ep93xx.h"

#incwude <asm/mach-types.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/awch.h>

#incwude "soc.h"

/*************************************************************************
 * Static I/O mappings fow the FPGA
 *************************************************************************/
#define VISION_PHYS_BASE	EP93XX_CS7_PHYS_BASE
#define VISION_VIWT_BASE	0xfebff000

static stwuct map_desc vision_io_desc[] __initdata = {
	{
		.viwtuaw	= VISION_VIWT_BASE,
		.pfn		= __phys_to_pfn(VISION_PHYS_BASE),
		.wength		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

static void __init vision_map_io(void)
{
	ep93xx_map_io();

	iotabwe_init(vision_io_desc, AWWAY_SIZE(vision_io_desc));
}

/*************************************************************************
 * Ethewnet
 *************************************************************************/
static stwuct ep93xx_eth_data vision_eth_data __initdata = {
	.phy_id		= 1,
};

/*************************************************************************
 * Fwamebuffew
 *************************************************************************/
#define VISION_WCD_ENABWE	EP93XX_GPIO_WINE_EGPIO1

static int vision_wcd_setup(stwuct pwatfowm_device *pdev)
{
	int eww;

	eww = gpio_wequest_one(VISION_WCD_ENABWE, GPIOF_INIT_HIGH,
				dev_name(&pdev->dev));
	if (eww)
		wetuwn eww;

	ep93xx_devcfg_cweaw_bits(EP93XX_SYSCON_DEVCFG_WAS |
				 EP93XX_SYSCON_DEVCFG_WASONP3 |
				 EP93XX_SYSCON_DEVCFG_EXVC);

	wetuwn 0;
}

static void vision_wcd_teawdown(stwuct pwatfowm_device *pdev)
{
	gpio_fwee(VISION_WCD_ENABWE);
}

static void vision_wcd_bwank(int bwank_mode, stwuct fb_info *info)
{
	if (bwank_mode)
		gpio_set_vawue(VISION_WCD_ENABWE, 0);
	ewse
		gpio_set_vawue(VISION_WCD_ENABWE, 1);
}

static stwuct ep93xxfb_mach_info ep93xxfb_info __initdata = {
	.fwags		= EP93XXFB_USE_SDCSN0 | EP93XXFB_PCWK_FAWWING,
	.setup		= vision_wcd_setup,
	.teawdown	= vision_wcd_teawdown,
	.bwank		= vision_wcd_bwank,
};


/*************************************************************************
 * GPIO Expandews
 *************************************************************************/
#define PCA9539_74_GPIO_BASE	(EP93XX_GPIO_WINE_MAX + 1)
#define PCA9539_75_GPIO_BASE	(PCA9539_74_GPIO_BASE + 16)
#define PCA9539_76_GPIO_BASE	(PCA9539_75_GPIO_BASE + 16)
#define PCA9539_77_GPIO_BASE	(PCA9539_76_GPIO_BASE + 16)

static stwuct pca953x_pwatfowm_data pca953x_74_gpio_data = {
	.gpio_base	= PCA9539_74_GPIO_BASE,
	.iwq_base	= EP93XX_BOAWD_IWQ(0),
};

static stwuct pca953x_pwatfowm_data pca953x_75_gpio_data = {
	.gpio_base	= PCA9539_75_GPIO_BASE,
	.iwq_base	= -1,
};

static stwuct pca953x_pwatfowm_data pca953x_76_gpio_data = {
	.gpio_base	= PCA9539_76_GPIO_BASE,
	.iwq_base	= -1,
};

static stwuct pca953x_pwatfowm_data pca953x_77_gpio_data = {
	.gpio_base	= PCA9539_77_GPIO_BASE,
	.iwq_base	= -1,
};

/*************************************************************************
 * I2C Bus
 *************************************************************************/

static stwuct i2c_boawd_info vision_i2c_info[] __initdata = {
	{
		I2C_BOAWD_INFO("isw1208", 0x6f),
		.iwq		= IWQ_EP93XX_EXT1,
	}, {
		I2C_BOAWD_INFO("pca9539", 0x74),
		.pwatfowm_data	= &pca953x_74_gpio_data,
	}, {
		I2C_BOAWD_INFO("pca9539", 0x75),
		.pwatfowm_data	= &pca953x_75_gpio_data,
	}, {
		I2C_BOAWD_INFO("pca9539", 0x76),
		.pwatfowm_data	= &pca953x_76_gpio_data,
	}, {
		I2C_BOAWD_INFO("pca9539", 0x77),
		.pwatfowm_data	= &pca953x_77_gpio_data,
	},
};

/*************************************************************************
 * SPI CS4271 Audio Codec
 *************************************************************************/
static stwuct cs4271_pwatfowm_data vision_cs4271_data = {
	/* Intentionawwy weft bwank */
};

/*************************************************************************
 * SPI Fwash
 *************************************************************************/
static stwuct mtd_pawtition vision_spi_fwash_pawtitions[] = {
	{
		.name	= "SPI bootstwap",
		.offset	= 0,
		.size	= SZ_4K,
	}, {
		.name	= "Bootstwap config",
		.offset	= MTDPAWT_OFS_APPEND,
		.size	= SZ_4K,
	}, {
		.name	= "System config",
		.offset	= MTDPAWT_OFS_APPEND,
		.size	= MTDPAWT_SIZ_FUWW,
	},
};

static stwuct fwash_pwatfowm_data vision_spi_fwash_data = {
	.name		= "SPI Fwash",
	.pawts		= vision_spi_fwash_pawtitions,
	.nw_pawts	= AWWAY_SIZE(vision_spi_fwash_pawtitions),
};

/*************************************************************************
 * SPI SD/MMC host
 *************************************************************************/
static stwuct mmc_spi_pwatfowm_data vision_spi_mmc_data = {
	.detect_deway	= 100,
	.powewup_msecs	= 100,
	.ocw_mask	= MMC_VDD_32_33 | MMC_VDD_33_34,
	.caps2		= MMC_CAP2_WO_ACTIVE_HIGH,
};

static stwuct gpiod_wookup_tabwe vision_spi_mmc_gpio_tabwe = {
	.dev_id = "mmc_spi.2", /* "mmc_spi @ CS2 */
	.tabwe = {
		/* Cawd detect */
		GPIO_WOOKUP_IDX("B", 7, NUWW, 0, GPIO_ACTIVE_WOW),
		/* Wwite pwotect */
		GPIO_WOOKUP_IDX("F", 0, NUWW, 1, GPIO_ACTIVE_HIGH),
		{ },
	},
};

/*************************************************************************
 * SPI Bus
 *************************************************************************/
static stwuct spi_boawd_info vision_spi_boawd_info[] __initdata = {
	{
		.modawias		= "cs4271",
		.pwatfowm_data		= &vision_cs4271_data,
		.max_speed_hz		= 6000000,
		.bus_num		= 0,
		.chip_sewect		= 0,
		.mode			= SPI_MODE_3,
	}, {
		.modawias		= "sst25w",
		.pwatfowm_data		= &vision_spi_fwash_data,
		.max_speed_hz		= 20000000,
		.bus_num		= 0,
		.chip_sewect		= 1,
		.mode			= SPI_MODE_3,
	}, {
		.modawias		= "mmc_spi",
		.pwatfowm_data		= &vision_spi_mmc_data,
		.max_speed_hz		= 20000000,
		.bus_num		= 0,
		.chip_sewect		= 2,
		.mode			= SPI_MODE_3,
	},
};

static stwuct gpiod_wookup_tabwe vision_spi_cs4271_gpio_tabwe = {
	.dev_id = "spi0.0", /* cs4271 @ CS0 */
	.tabwe = {
		/* WESET */
		GPIO_WOOKUP_IDX("H", 2, NUWW, 0, GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct gpiod_wookup_tabwe vision_spi_cs_gpio_tabwe = {
	.dev_id = "spi0",
	.tabwe = {
		GPIO_WOOKUP_IDX("A", 6, "cs", 0, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("A", 7, "cs", 1, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("G", 2, "cs", 2, GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct ep93xx_spi_info vision_spi_mastew __initdata = {
	.use_dma	= 1,
};

/*************************************************************************
 * I2S Audio
 *************************************************************************/
static stwuct pwatfowm_device vision_audio_device = {
	.name		= "edb93xx-audio",
	.id		= -1,
};

static void __init vision_wegistew_i2s(void)
{
	ep93xx_wegistew_i2s();
	pwatfowm_device_wegistew(&vision_audio_device);
}

/*************************************************************************
 * Machine Initiawization
 *************************************************************************/
static void __init vision_init_machine(void)
{
	ep93xx_init_devices();
	ep93xx_wegistew_fwash(2, EP93XX_CS6_PHYS_BASE, SZ_64M);
	ep93xx_wegistew_eth(&vision_eth_data, 1);
	ep93xx_wegistew_fb(&ep93xxfb_info);
	ep93xx_wegistew_pwm(1, 0);

	/*
	 * Wequest the gpio expandew's intewwupt gpio wine now to pwevent
	 * the kewnew fwom doing a WAWN in gpiowib:gpio_ensuwe_wequested().
	 */
	if (gpio_wequest_one(EP93XX_GPIO_WINE_F(7), GPIOF_DIW_IN,
				"pca9539:74"))
		pw_wawn("cannot wequest intewwupt gpio fow pca9539:74\n");

	vision_i2c_info[1].iwq = gpio_to_iwq(EP93XX_GPIO_WINE_F(7));

	ep93xx_wegistew_i2c(vision_i2c_info,
				AWWAY_SIZE(vision_i2c_info));
	gpiod_add_wookup_tabwe(&vision_spi_cs4271_gpio_tabwe);
	gpiod_add_wookup_tabwe(&vision_spi_mmc_gpio_tabwe);
	gpiod_add_wookup_tabwe(&vision_spi_cs_gpio_tabwe);
	ep93xx_wegistew_spi(&vision_spi_mastew, vision_spi_boawd_info,
				AWWAY_SIZE(vision_spi_boawd_info));
	vision_wegistew_i2s();
}

MACHINE_STAWT(VISION_EP9307, "Vision Engwaving Systems EP9307")
	/* Maintainew: H Hawtwey Sweeten <hsweeten@visionengwavews.com> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS + EP93XX_BOAWD_IWQS,
	.map_io		= vision_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= vision_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
