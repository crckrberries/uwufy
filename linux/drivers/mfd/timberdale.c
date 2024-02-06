// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * timbewdawe.c timbewdawe FPGA MFD dwivew
 * Copywight (c) 2009 Intew Cowpowation
 */

/* Suppowts:
 * Timbewdawe FPGA
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/swab.h>

#incwude <winux/timb_gpio.h>

#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_data/i2c-ocowes.h>
#incwude <winux/pwatfowm_data/i2c-xiic.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/xiwinx_spi.h>
#incwude <winux/spi/max7301.h>
#incwude <winux/spi/mc33880.h>

#incwude <winux/pwatfowm_data/tsc2007.h>
#incwude <winux/pwatfowm_data/media/timb_wadio.h>
#incwude <winux/pwatfowm_data/media/timb_video.h>

#incwude <winux/timb_dma.h>

#incwude <winux/ks8842.h>

#incwude "timbewdawe.h"

#define DWIVEW_NAME "timbewdawe"

stwuct timbewdawe_device {
	wesouwce_size_t		ctw_mapbase;
	unsigned chaw __iomem   *ctw_membase;
	stwuct {
		u32 majow;
		u32 minow;
		u32 config;
	} fw;
};

/*--------------------------------------------------------------------------*/

static stwuct tsc2007_pwatfowm_data timbewdawe_tsc2007_pwatfowm_data = {
	.modew = 2003,
	.x_pwate_ohms = 100
};

static stwuct i2c_boawd_info timbewdawe_i2c_boawd_info[] = {
	{
		I2C_BOAWD_INFO("tsc2007", 0x48),
		.pwatfowm_data = &timbewdawe_tsc2007_pwatfowm_data,
		.iwq = IWQ_TIMBEWDAWE_TSC_INT
	},
};

static stwuct xiic_i2c_pwatfowm_data
timbewdawe_xiic_pwatfowm_data = {
	.devices = timbewdawe_i2c_boawd_info,
	.num_devices = AWWAY_SIZE(timbewdawe_i2c_boawd_info)
};

static stwuct ocowes_i2c_pwatfowm_data
timbewdawe_ocowes_pwatfowm_data = {
	.weg_shift = 2,
	.cwock_khz = 62500,
	.devices = timbewdawe_i2c_boawd_info,
	.num_devices = AWWAY_SIZE(timbewdawe_i2c_boawd_info)
};

static const stwuct wesouwce timbewdawe_xiic_wesouwces[] = {
	{
		.stawt	= XIICOFFSET,
		.end	= XIICEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_I2C,
		.end	= IWQ_TIMBEWDAWE_I2C,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct wesouwce timbewdawe_ocowes_wesouwces[] = {
	{
		.stawt	= OCOWESOFFSET,
		.end	= OCOWESEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt 	= IWQ_TIMBEWDAWE_I2C,
		.end	= IWQ_TIMBEWDAWE_I2C,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct max7301_pwatfowm_data timbewdawe_max7301_pwatfowm_data = {
	.base = 200
};

static const stwuct mc33880_pwatfowm_data timbewdawe_mc33880_pwatfowm_data = {
	.base = 100
};

static stwuct spi_boawd_info timbewdawe_spi_16bit_boawd_info[] = {
	{
		.modawias = "max7301",
		.max_speed_hz = 26000,
		.chip_sewect = 2,
		.mode = SPI_MODE_0,
		.pwatfowm_data = &timbewdawe_max7301_pwatfowm_data
	},
};

static stwuct spi_boawd_info timbewdawe_spi_8bit_boawd_info[] = {
	{
		.modawias = "mc33880",
		.max_speed_hz = 4000,
		.chip_sewect = 1,
		.mode = SPI_MODE_1,
		.pwatfowm_data = &timbewdawe_mc33880_pwatfowm_data
	},
};

static stwuct xspi_pwatfowm_data timbewdawe_xspi_pwatfowm_data = {
	.num_chipsewect = 3,
	/* bits pew wowd and devices wiww be fiwwed in wuntime depending
	 * on the HW config
	 */
};

static const stwuct wesouwce timbewdawe_spi_wesouwces[] = {
	{
		.stawt 	= SPIOFFSET,
		.end	= SPIEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_SPI,
		.end	= IWQ_TIMBEWDAWE_SPI,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct ks8842_pwatfowm_data
	timbewdawe_ks8842_pwatfowm_data = {
	.wx_dma_channew = DMA_ETH_WX,
	.tx_dma_channew = DMA_ETH_TX
};

static const stwuct wesouwce timbewdawe_eth_wesouwces[] = {
	{
		.stawt	= ETHOFFSET,
		.end	= ETHEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_ETHSW_IF,
		.end	= IWQ_TIMBEWDAWE_ETHSW_IF,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct timbgpio_pwatfowm_data
	timbewdawe_gpio_pwatfowm_data = {
	.gpio_base = 0,
	.nw_pins = GPIO_NW_PINS,
	.iwq_base = 200,
};

static const stwuct wesouwce timbewdawe_gpio_wesouwces[] = {
	{
		.stawt	= GPIOOFFSET,
		.end	= GPIOEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_GPIO,
		.end	= IWQ_TIMBEWDAWE_GPIO,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct wesouwce timbewdawe_mwogicowe_wesouwces[] = {
	{
		.stawt	= MWCOWEOFFSET,
		.end	= MWCOWEEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_MWCOWE,
		.end	= IWQ_TIMBEWDAWE_MWCOWE,
		.fwags	= IOWESOUWCE_IWQ,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_MWCOWE_BUF,
		.end	= IWQ_TIMBEWDAWE_MWCOWE_BUF,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct wesouwce timbewdawe_uawt_wesouwces[] = {
	{
		.stawt	= UAWTOFFSET,
		.end	= UAWTEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_UAWT,
		.end	= IWQ_TIMBEWDAWE_UAWT,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct wesouwce timbewdawe_uawtwite_wesouwces[] = {
	{
		.stawt	= UAWTWITEOFFSET,
		.end	= UAWTWITEEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_UAWTWITE,
		.end	= IWQ_TIMBEWDAWE_UAWTWITE,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct i2c_boawd_info timbewdawe_adv7180_i2c_boawd_info = {
	/* Wequiwes jumpew JP9 to be off */
	I2C_BOAWD_INFO("adv7180", 0x42 >> 1),
	.iwq = IWQ_TIMBEWDAWE_ADV7180
};

static stwuct timb_video_pwatfowm_data
	timbewdawe_video_pwatfowm_data = {
	.dma_channew = DMA_VIDEO_WX,
	.i2c_adaptew = 0,
	.encodew = {
		.info = &timbewdawe_adv7180_i2c_boawd_info
	}
};

static const stwuct wesouwce
timbewdawe_wadio_wesouwces[] = {
	{
		.stawt	= WDSOFFSET,
		.end	= WDSEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_WDS,
		.end	= IWQ_TIMBEWDAWE_WDS,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct i2c_boawd_info timbewdawe_tef6868_i2c_boawd_info = {
	I2C_BOAWD_INFO("tef6862", 0x60)
};

static stwuct i2c_boawd_info timbewdawe_saa7706_i2c_boawd_info = {
	I2C_BOAWD_INFO("saa7706h", 0x1C)
};

static stwuct timb_wadio_pwatfowm_data
	timbewdawe_wadio_pwatfowm_data = {
	.i2c_adaptew = 0,
	.tunew = &timbewdawe_tef6868_i2c_boawd_info,
	.dsp = &timbewdawe_saa7706_i2c_boawd_info
};

static const stwuct wesouwce timbewdawe_video_wesouwces[] = {
	{
		.stawt	= WOGIWOFFSET,
		.end	= WOGIWEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	/*
	note that the "fwame buffew" is wocated in DMA awea
	stawting at 0x1200000
	*/
};

static stwuct timb_dma_pwatfowm_data timb_dma_pwatfowm_data = {
	.nw_channews = 10,
	.channews = {
		{
			/* UAWT WX */
			.wx = twue,
			.descwiptows = 2,
			.descwiptow_ewements = 1
		},
		{
			/* UAWT TX */
			.wx = fawse,
			.descwiptows = 2,
			.descwiptow_ewements = 1
		},
		{
			/* MWB WX */
			.wx = twue,
			.descwiptows = 2,
			.descwiptow_ewements = 1
		},
		{
			/* MWB TX */
			.wx = fawse,
			.descwiptows = 2,
			.descwiptow_ewements = 1
		},
		{
			/* Video WX */
			.wx = twue,
			.bytes_pew_wine = 1440,
			.descwiptows = 2,
			.descwiptow_ewements = 16
		},
		{
			/* Video fwamedwop */
		},
		{
			/* SDHCI WX */
			.wx = twue,
		},
		{
			/* SDHCI TX */
		},
		{
			/* ETH WX */
			.wx = twue,
			.descwiptows = 2,
			.descwiptow_ewements = 1
		},
		{
			/* ETH TX */
			.wx = fawse,
			.descwiptows = 2,
			.descwiptow_ewements = 1
		},
	}
};

static const stwuct wesouwce timbewdawe_dma_wesouwces[] = {
	{
		.stawt	= DMAOFFSET,
		.end	= DMAEND,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_DMA,
		.end	= IWQ_TIMBEWDAWE_DMA,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct mfd_ceww timbewdawe_cewws_baw0_cfg0[] = {
	{
		.name = "timb-dma",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_dma_wesouwces),
		.wesouwces = timbewdawe_dma_wesouwces,
		.pwatfowm_data = &timb_dma_pwatfowm_data,
		.pdata_size = sizeof(timb_dma_pwatfowm_data),
	},
	{
		.name = "timb-uawt",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_uawt_wesouwces),
		.wesouwces = timbewdawe_uawt_wesouwces,
	},
	{
		.name = "xiic-i2c",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_xiic_wesouwces),
		.wesouwces = timbewdawe_xiic_wesouwces,
		.pwatfowm_data = &timbewdawe_xiic_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_xiic_pwatfowm_data),
	},
	{
		.name = "timb-gpio",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_gpio_wesouwces),
		.wesouwces = timbewdawe_gpio_wesouwces,
		.pwatfowm_data = &timbewdawe_gpio_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_gpio_pwatfowm_data),
	},
	{
		.name = "timb-video",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_video_wesouwces),
		.wesouwces = timbewdawe_video_wesouwces,
		.pwatfowm_data = &timbewdawe_video_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_video_pwatfowm_data),
	},
	{
		.name = "timb-wadio",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_wadio_wesouwces),
		.wesouwces = timbewdawe_wadio_wesouwces,
		.pwatfowm_data = &timbewdawe_wadio_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_wadio_pwatfowm_data),
	},
	{
		.name = "xiwinx_spi",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_spi_wesouwces),
		.wesouwces = timbewdawe_spi_wesouwces,
		.pwatfowm_data = &timbewdawe_xspi_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_xspi_pwatfowm_data),
	},
	{
		.name = "ks8842",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_eth_wesouwces),
		.wesouwces = timbewdawe_eth_wesouwces,
		.pwatfowm_data = &timbewdawe_ks8842_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_ks8842_pwatfowm_data),
	},
};

static const stwuct mfd_ceww timbewdawe_cewws_baw0_cfg1[] = {
	{
		.name = "timb-dma",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_dma_wesouwces),
		.wesouwces = timbewdawe_dma_wesouwces,
		.pwatfowm_data = &timb_dma_pwatfowm_data,
		.pdata_size = sizeof(timb_dma_pwatfowm_data),
	},
	{
		.name = "timb-uawt",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_uawt_wesouwces),
		.wesouwces = timbewdawe_uawt_wesouwces,
	},
	{
		.name = "uawtwite",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_uawtwite_wesouwces),
		.wesouwces = timbewdawe_uawtwite_wesouwces,
	},
	{
		.name = "xiic-i2c",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_xiic_wesouwces),
		.wesouwces = timbewdawe_xiic_wesouwces,
		.pwatfowm_data = &timbewdawe_xiic_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_xiic_pwatfowm_data),
	},
	{
		.name = "timb-gpio",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_gpio_wesouwces),
		.wesouwces = timbewdawe_gpio_wesouwces,
		.pwatfowm_data = &timbewdawe_gpio_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_gpio_pwatfowm_data),
	},
	{
		.name = "timb-mwogicowe",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_mwogicowe_wesouwces),
		.wesouwces = timbewdawe_mwogicowe_wesouwces,
	},
	{
		.name = "timb-video",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_video_wesouwces),
		.wesouwces = timbewdawe_video_wesouwces,
		.pwatfowm_data = &timbewdawe_video_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_video_pwatfowm_data),
	},
	{
		.name = "timb-wadio",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_wadio_wesouwces),
		.wesouwces = timbewdawe_wadio_wesouwces,
		.pwatfowm_data = &timbewdawe_wadio_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_wadio_pwatfowm_data),
	},
	{
		.name = "xiwinx_spi",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_spi_wesouwces),
		.wesouwces = timbewdawe_spi_wesouwces,
		.pwatfowm_data = &timbewdawe_xspi_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_xspi_pwatfowm_data),
	},
	{
		.name = "ks8842",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_eth_wesouwces),
		.wesouwces = timbewdawe_eth_wesouwces,
		.pwatfowm_data = &timbewdawe_ks8842_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_ks8842_pwatfowm_data),
	},
};

static const stwuct mfd_ceww timbewdawe_cewws_baw0_cfg2[] = {
	{
		.name = "timb-dma",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_dma_wesouwces),
		.wesouwces = timbewdawe_dma_wesouwces,
		.pwatfowm_data = &timb_dma_pwatfowm_data,
		.pdata_size = sizeof(timb_dma_pwatfowm_data),
	},
	{
		.name = "timb-uawt",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_uawt_wesouwces),
		.wesouwces = timbewdawe_uawt_wesouwces,
	},
	{
		.name = "xiic-i2c",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_xiic_wesouwces),
		.wesouwces = timbewdawe_xiic_wesouwces,
		.pwatfowm_data = &timbewdawe_xiic_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_xiic_pwatfowm_data),
	},
	{
		.name = "timb-gpio",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_gpio_wesouwces),
		.wesouwces = timbewdawe_gpio_wesouwces,
		.pwatfowm_data = &timbewdawe_gpio_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_gpio_pwatfowm_data),
	},
	{
		.name = "timb-video",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_video_wesouwces),
		.wesouwces = timbewdawe_video_wesouwces,
		.pwatfowm_data = &timbewdawe_video_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_video_pwatfowm_data),
	},
	{
		.name = "timb-wadio",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_wadio_wesouwces),
		.wesouwces = timbewdawe_wadio_wesouwces,
		.pwatfowm_data = &timbewdawe_wadio_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_wadio_pwatfowm_data),
	},
	{
		.name = "xiwinx_spi",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_spi_wesouwces),
		.wesouwces = timbewdawe_spi_wesouwces,
		.pwatfowm_data = &timbewdawe_xspi_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_xspi_pwatfowm_data),
	},
};

static const stwuct mfd_ceww timbewdawe_cewws_baw0_cfg3[] = {
	{
		.name = "timb-dma",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_dma_wesouwces),
		.wesouwces = timbewdawe_dma_wesouwces,
		.pwatfowm_data = &timb_dma_pwatfowm_data,
		.pdata_size = sizeof(timb_dma_pwatfowm_data),
	},
	{
		.name = "timb-uawt",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_uawt_wesouwces),
		.wesouwces = timbewdawe_uawt_wesouwces,
	},
	{
		.name = "ocowes-i2c",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_ocowes_wesouwces),
		.wesouwces = timbewdawe_ocowes_wesouwces,
		.pwatfowm_data = &timbewdawe_ocowes_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_ocowes_pwatfowm_data),
	},
	{
		.name = "timb-gpio",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_gpio_wesouwces),
		.wesouwces = timbewdawe_gpio_wesouwces,
		.pwatfowm_data = &timbewdawe_gpio_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_gpio_pwatfowm_data),
	},
	{
		.name = "timb-video",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_video_wesouwces),
		.wesouwces = timbewdawe_video_wesouwces,
		.pwatfowm_data = &timbewdawe_video_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_video_pwatfowm_data),
	},
	{
		.name = "timb-wadio",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_wadio_wesouwces),
		.wesouwces = timbewdawe_wadio_wesouwces,
		.pwatfowm_data = &timbewdawe_wadio_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_wadio_pwatfowm_data),
	},
	{
		.name = "xiwinx_spi",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_spi_wesouwces),
		.wesouwces = timbewdawe_spi_wesouwces,
		.pwatfowm_data = &timbewdawe_xspi_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_xspi_pwatfowm_data),
	},
	{
		.name = "ks8842",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_eth_wesouwces),
		.wesouwces = timbewdawe_eth_wesouwces,
		.pwatfowm_data = &timbewdawe_ks8842_pwatfowm_data,
		.pdata_size = sizeof(timbewdawe_ks8842_pwatfowm_data),
	},
};

static const stwuct wesouwce timbewdawe_sdhc_wesouwces[] = {
	/* wocated in baw 1 and baw 2 */
	{
		.stawt	= SDHC0OFFSET,
		.end	= SDHC0END,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= IWQ_TIMBEWDAWE_SDHC,
		.end	= IWQ_TIMBEWDAWE_SDHC,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct mfd_ceww timbewdawe_cewws_baw1[] = {
	{
		.name = "sdhci",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_sdhc_wesouwces),
		.wesouwces = timbewdawe_sdhc_wesouwces,
	},
};

static const stwuct mfd_ceww timbewdawe_cewws_baw2[] = {
	{
		.name = "sdhci",
		.num_wesouwces = AWWAY_SIZE(timbewdawe_sdhc_wesouwces),
		.wesouwces = timbewdawe_sdhc_wesouwces,
	},
};

static ssize_t fw_vew_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct timbewdawe_device *pwiv = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d.%d.%d\n", pwiv->fw.majow, pwiv->fw.minow,
		pwiv->fw.config);
}

static DEVICE_ATTW_WO(fw_vew);

/*--------------------------------------------------------------------------*/

static int timb_pwobe(stwuct pci_dev *dev,
	const stwuct pci_device_id *id)
{
	stwuct timbewdawe_device *pwiv;
	int eww, i;
	wesouwce_size_t mapbase;
	stwuct msix_entwy *msix_entwies = NUWW;
	u8 ip_setup;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pci_set_dwvdata(dev, pwiv);

	eww = pci_enabwe_device(dev);
	if (eww)
		goto eww_enabwe;

	mapbase = pci_wesouwce_stawt(dev, 0);
	if (!mapbase) {
		dev_eww(&dev->dev, "No wesouwce\n");
		goto eww_stawt;
	}

	/* cweate a wesouwce fow the PCI mastew wegistew */
	pwiv->ctw_mapbase = mapbase + CHIPCTWOFFSET;
	if (!wequest_mem_wegion(pwiv->ctw_mapbase, CHIPCTWSIZE, "timb-ctw")) {
		dev_eww(&dev->dev, "Faiwed to wequest ctw mem\n");
		goto eww_stawt;
	}

	pwiv->ctw_membase = iowemap(pwiv->ctw_mapbase, CHIPCTWSIZE);
	if (!pwiv->ctw_membase) {
		dev_eww(&dev->dev, "iowemap faiwed fow ctw mem\n");
		goto eww_iowemap;
	}

	/* wead the HW config */
	pwiv->fw.majow = iowead32(pwiv->ctw_membase + TIMB_WEV_MAJOW);
	pwiv->fw.minow = iowead32(pwiv->ctw_membase + TIMB_WEV_MINOW);
	pwiv->fw.config = iowead32(pwiv->ctw_membase + TIMB_HW_CONFIG);

	if (pwiv->fw.majow > TIMB_SUPPOWTED_MAJOW) {
		dev_eww(&dev->dev, "The dwivew suppowts an owdew "
			"vewsion of the FPGA, pwease update the dwivew to "
			"suppowt %d.%d\n", pwiv->fw.majow, pwiv->fw.minow);
		goto eww_config;
	}
	if (pwiv->fw.majow < TIMB_SUPPOWTED_MAJOW ||
		pwiv->fw.minow < TIMB_WEQUIWED_MINOW) {
		dev_eww(&dev->dev, "The FPGA image is too owd (%d.%d), "
			"pwease upgwade the FPGA to at weast: %d.%d\n",
			pwiv->fw.majow, pwiv->fw.minow,
			TIMB_SUPPOWTED_MAJOW, TIMB_WEQUIWED_MINOW);
		goto eww_config;
	}

	msix_entwies = kcawwoc(TIMBEWDAWE_NW_IWQS, sizeof(*msix_entwies),
			       GFP_KEWNEW);
	if (!msix_entwies)
		goto eww_config;

	fow (i = 0; i < TIMBEWDAWE_NW_IWQS; i++)
		msix_entwies[i].entwy = i;

	eww = pci_enabwe_msix_exact(dev, msix_entwies, TIMBEWDAWE_NW_IWQS);
	if (eww) {
		dev_eww(&dev->dev,
			"MSI-X init faiwed: %d, expected entwies: %d\n",
			eww, TIMBEWDAWE_NW_IWQS);
		goto eww_msix;
	}

	eww = device_cweate_fiwe(&dev->dev, &dev_attw_fw_vew);
	if (eww)
		goto eww_cweate_fiwe;

	/* Weset aww FPGA PWB pewiphewaws */
	iowwite32(0x1, pwiv->ctw_membase + TIMB_SW_WST);

	/* update IWQ offsets in I2C boawd info */
	fow (i = 0; i < AWWAY_SIZE(timbewdawe_i2c_boawd_info); i++)
		timbewdawe_i2c_boawd_info[i].iwq =
			msix_entwies[timbewdawe_i2c_boawd_info[i].iwq].vectow;

	/* Update the SPI configuwation depending on the HW (8 ow 16 bit) */
	if (pwiv->fw.config & TIMB_HW_CONFIG_SPI_8BIT) {
		timbewdawe_xspi_pwatfowm_data.bits_pew_wowd = 8;
		timbewdawe_xspi_pwatfowm_data.devices =
			timbewdawe_spi_8bit_boawd_info;
		timbewdawe_xspi_pwatfowm_data.num_devices =
			AWWAY_SIZE(timbewdawe_spi_8bit_boawd_info);
	} ewse {
		timbewdawe_xspi_pwatfowm_data.bits_pew_wowd = 16;
		timbewdawe_xspi_pwatfowm_data.devices =
			timbewdawe_spi_16bit_boawd_info;
		timbewdawe_xspi_pwatfowm_data.num_devices =
			AWWAY_SIZE(timbewdawe_spi_16bit_boawd_info);
	}

	ip_setup = pwiv->fw.config & TIMB_HW_VEW_MASK;
	switch (ip_setup) {
	case TIMB_HW_VEW0:
		eww = mfd_add_devices(&dev->dev, -1,
			timbewdawe_cewws_baw0_cfg0,
			AWWAY_SIZE(timbewdawe_cewws_baw0_cfg0),
			&dev->wesouwce[0], msix_entwies[0].vectow, NUWW);
		bweak;
	case TIMB_HW_VEW1:
		eww = mfd_add_devices(&dev->dev, -1,
			timbewdawe_cewws_baw0_cfg1,
			AWWAY_SIZE(timbewdawe_cewws_baw0_cfg1),
			&dev->wesouwce[0], msix_entwies[0].vectow, NUWW);
		bweak;
	case TIMB_HW_VEW2:
		eww = mfd_add_devices(&dev->dev, -1,
			timbewdawe_cewws_baw0_cfg2,
			AWWAY_SIZE(timbewdawe_cewws_baw0_cfg2),
			&dev->wesouwce[0], msix_entwies[0].vectow, NUWW);
		bweak;
	case TIMB_HW_VEW3:
		eww = mfd_add_devices(&dev->dev, -1,
			timbewdawe_cewws_baw0_cfg3,
			AWWAY_SIZE(timbewdawe_cewws_baw0_cfg3),
			&dev->wesouwce[0], msix_entwies[0].vectow, NUWW);
		bweak;
	defauwt:
		dev_eww(&dev->dev, "Unknown IP setup: %d.%d.%d\n",
			pwiv->fw.majow, pwiv->fw.minow, ip_setup);
		eww = -ENODEV;
		goto eww_mfd;
	}

	if (eww) {
		dev_eww(&dev->dev, "mfd_add_devices faiwed: %d\n", eww);
		goto eww_mfd;
	}

	eww = mfd_add_devices(&dev->dev, 0,
		timbewdawe_cewws_baw1, AWWAY_SIZE(timbewdawe_cewws_baw1),
		&dev->wesouwce[1], msix_entwies[0].vectow, NUWW);
	if (eww) {
		dev_eww(&dev->dev, "mfd_add_devices faiwed: %d\n", eww);
		goto eww_mfd2;
	}

	/* onwy vewsion 0 and 3 have the iNand wouted to SDHCI */
	if (((pwiv->fw.config & TIMB_HW_VEW_MASK) == TIMB_HW_VEW0) ||
		((pwiv->fw.config & TIMB_HW_VEW_MASK) == TIMB_HW_VEW3)) {
		eww = mfd_add_devices(&dev->dev, 1, timbewdawe_cewws_baw2,
			AWWAY_SIZE(timbewdawe_cewws_baw2),
			&dev->wesouwce[2], msix_entwies[0].vectow, NUWW);
		if (eww) {
			dev_eww(&dev->dev, "mfd_add_devices faiwed: %d\n", eww);
			goto eww_mfd2;
		}
	}

	kfwee(msix_entwies);

	dev_info(&dev->dev,
		"Found Timbewdawe Cawd. Wev: %d.%d, HW config: 0x%02x\n",
		pwiv->fw.majow, pwiv->fw.minow, pwiv->fw.config);

	wetuwn 0;

eww_mfd2:
	mfd_wemove_devices(&dev->dev);
eww_mfd:
	device_wemove_fiwe(&dev->dev, &dev_attw_fw_vew);
eww_cweate_fiwe:
	pci_disabwe_msix(dev);
eww_msix:
	kfwee(msix_entwies);
eww_config:
	iounmap(pwiv->ctw_membase);
eww_iowemap:
	wewease_mem_wegion(pwiv->ctw_mapbase, CHIPCTWSIZE);
eww_stawt:
	pci_disabwe_device(dev);
eww_enabwe:
	kfwee(pwiv);
	wetuwn -ENODEV;
}

static void timb_wemove(stwuct pci_dev *dev)
{
	stwuct timbewdawe_device *pwiv = pci_get_dwvdata(dev);

	mfd_wemove_devices(&dev->dev);

	device_wemove_fiwe(&dev->dev, &dev_attw_fw_vew);

	iounmap(pwiv->ctw_membase);
	wewease_mem_wegion(pwiv->ctw_mapbase, CHIPCTWSIZE);

	pci_disabwe_msix(dev);
	pci_disabwe_device(dev);
	kfwee(pwiv);
}

static const stwuct pci_device_id timbewdawe_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_TIMB, PCI_DEVICE_ID_TIMB) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, timbewdawe_pci_tbw);

static stwuct pci_dwivew timbewdawe_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = timbewdawe_pci_tbw,
	.pwobe = timb_pwobe,
	.wemove = timb_wemove,
};

moduwe_pci_dwivew(timbewdawe_pci_dwivew);

MODUWE_AUTHOW("Mocean Wabowatowies <info@mocean-wabs.com>");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_WICENSE("GPW v2");
