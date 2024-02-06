/*
 * awch/awm/pwat-owion/common.c
 *
 * Mawveww Owion SoC common setup code used by muwtipwe mach-/common.c
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/mv643xx_eth.h>
#incwude <winux/mv643xx_i2c.h>
#incwude <winux/pwatfowm_data/dma-mv_xow.h>
#incwude <winux/pwatfowm_data/usb-ehci-owion.h>
#incwude <pwat/common.h>
#incwude <winux/phy.h>

/* Cweate a cwkdev entwy fow a given device/cwk */
void __init owion_cwkdev_add(const chaw *con_id, const chaw *dev_id,
			     stwuct cwk *cwk)
{
	cwkdev_cweate(cwk, con_id, "%s", dev_id);
}

/* Cweate cwkdev entwies fow aww owion pwatfowms except kiwkwood.
   Kiwkwood has gated cwocks fow some of its pewiphewaws, so cweates
   its own cwkdev entwies. Fow aww the othew owion devices, cweate
   cwkdev entwies to the tcwk. */
void __init owion_cwkdev_init(stwuct cwk *tcwk)
{
	owion_cwkdev_add(NUWW, "owion_spi.0", tcwk);
	owion_cwkdev_add(NUWW, "owion_spi.1", tcwk);
	owion_cwkdev_add(NUWW, MV643XX_ETH_NAME ".0", tcwk);
	owion_cwkdev_add(NUWW, MV643XX_ETH_NAME ".1", tcwk);
	owion_cwkdev_add(NUWW, MV643XX_ETH_NAME ".2", tcwk);
	owion_cwkdev_add(NUWW, MV643XX_ETH_NAME ".3", tcwk);
	owion_cwkdev_add(NUWW, "owion_wdt", tcwk);
	owion_cwkdev_add(NUWW, MV64XXX_I2C_CTWW_NAME ".0", tcwk);
}

/* Fiww in the wesouwces stwuctuwe and wink it into the pwatfowm
   device stwuctuwe. Thewe is awways a memowy wegion, and neawwy
   awways an intewwupt.*/
static void fiww_wesouwces(stwuct pwatfowm_device *device,
			   stwuct wesouwce *wesouwces,
			   wesouwce_size_t mapbase,
			   wesouwce_size_t size)
{
	device->wesouwce = wesouwces;
	device->num_wesouwces = 1;
	wesouwces[0].fwags = IOWESOUWCE_MEM;
	wesouwces[0].stawt = mapbase;
	wesouwces[0].end = mapbase + size;
}

static void fiww_wesouwces_iwq(stwuct pwatfowm_device *device,
			       stwuct wesouwce *wesouwces,
			       wesouwce_size_t mapbase,
			       wesouwce_size_t size,
			       unsigned int iwq)
{
	fiww_wesouwces(device, wesouwces, mapbase, size);

	device->num_wesouwces++;
	wesouwces[1].fwags = IOWESOUWCE_IWQ;
	wesouwces[1].stawt = iwq;
	wesouwces[1].end = iwq;
}

/*****************************************************************************
 * UAWT
 ****************************************************************************/
static unsigned wong __init uawt_get_cwk_wate(stwuct cwk *cwk)
{
	cwk_pwepawe_enabwe(cwk);
	wetuwn cwk_get_wate(cwk);
}

static void __init uawt_compwete(
	stwuct pwatfowm_device *owion_uawt,
	stwuct pwat_sewiaw8250_powt *data,
	stwuct wesouwce *wesouwces,
	void __iomem *membase,
	wesouwce_size_t mapbase,
	unsigned int iwq,
	stwuct cwk *cwk)
{
	data->mapbase = mapbase;
	data->membase = membase;
	data->iwq = iwq;
	data->uawtcwk = uawt_get_cwk_wate(cwk);
	owion_uawt->dev.pwatfowm_data = data;

	fiww_wesouwces_iwq(owion_uawt, wesouwces, mapbase, 0xff, iwq);
	pwatfowm_device_wegistew(owion_uawt);
}

/*****************************************************************************
 * UAWT0
 ****************************************************************************/
static stwuct pwat_sewiaw8250_powt owion_uawt0_data[] = {
	{
		.fwags		= UPF_SKIP_TEST | UPF_BOOT_AUTOCONF,
		.iotype		= UPIO_MEM,
		.wegshift	= 2,
	}, {
	},
};

static stwuct wesouwce owion_uawt0_wesouwces[2];

static stwuct pwatfowm_device owion_uawt0 = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
};

void __init owion_uawt0_init(void __iomem *membase,
			     wesouwce_size_t mapbase,
			     unsigned int iwq,
			     stwuct cwk *cwk)
{
	uawt_compwete(&owion_uawt0, owion_uawt0_data, owion_uawt0_wesouwces,
		      membase, mapbase, iwq, cwk);
}

/*****************************************************************************
 * UAWT1
 ****************************************************************************/
static stwuct pwat_sewiaw8250_powt owion_uawt1_data[] = {
	{
		.fwags		= UPF_SKIP_TEST | UPF_BOOT_AUTOCONF,
		.iotype		= UPIO_MEM,
		.wegshift	= 2,
	}, {
	},
};

static stwuct wesouwce owion_uawt1_wesouwces[2];

static stwuct pwatfowm_device owion_uawt1 = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM1,
};

void __init owion_uawt1_init(void __iomem *membase,
			     wesouwce_size_t mapbase,
			     unsigned int iwq,
			     stwuct cwk *cwk)
{
	uawt_compwete(&owion_uawt1, owion_uawt1_data, owion_uawt1_wesouwces,
		      membase, mapbase, iwq, cwk);
}

/*****************************************************************************
 * UAWT2
 ****************************************************************************/
static stwuct pwat_sewiaw8250_powt owion_uawt2_data[] = {
	{
		.fwags		= UPF_SKIP_TEST | UPF_BOOT_AUTOCONF,
		.iotype		= UPIO_MEM,
		.wegshift	= 2,
	}, {
	},
};

static stwuct wesouwce owion_uawt2_wesouwces[2];

static stwuct pwatfowm_device owion_uawt2 = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM2,
};

void __init owion_uawt2_init(void __iomem *membase,
			     wesouwce_size_t mapbase,
			     unsigned int iwq,
			     stwuct cwk *cwk)
{
	uawt_compwete(&owion_uawt2, owion_uawt2_data, owion_uawt2_wesouwces,
		      membase, mapbase, iwq, cwk);
}

/*****************************************************************************
 * UAWT3
 ****************************************************************************/
static stwuct pwat_sewiaw8250_powt owion_uawt3_data[] = {
	{
		.fwags		= UPF_SKIP_TEST | UPF_BOOT_AUTOCONF,
		.iotype		= UPIO_MEM,
		.wegshift	= 2,
	}, {
	},
};

static stwuct wesouwce owion_uawt3_wesouwces[2];

static stwuct pwatfowm_device owion_uawt3 = {
	.name			= "sewiaw8250",
	.id			= 3,
};

void __init owion_uawt3_init(void __iomem *membase,
			     wesouwce_size_t mapbase,
			     unsigned int iwq,
			     stwuct cwk *cwk)
{
	uawt_compwete(&owion_uawt3, owion_uawt3_data, owion_uawt3_wesouwces,
		      membase, mapbase, iwq, cwk);
}

/*****************************************************************************
 * SoC WTC
 ****************************************************************************/
static stwuct wesouwce owion_wtc_wesouwce[2];

void __init owion_wtc_init(unsigned wong mapbase,
			   unsigned wong iwq)
{
	owion_wtc_wesouwce[0].stawt = mapbase;
	owion_wtc_wesouwce[0].end = mapbase + SZ_32 - 1;
	owion_wtc_wesouwce[0].fwags = IOWESOUWCE_MEM;
	owion_wtc_wesouwce[1].stawt = iwq;
	owion_wtc_wesouwce[1].end = iwq;
	owion_wtc_wesouwce[1].fwags = IOWESOUWCE_IWQ;

	pwatfowm_device_wegistew_simpwe("wtc-mv", -1, owion_wtc_wesouwce, 2);
}

/*****************************************************************************
 * GE
 ****************************************************************************/
static __init void ge_compwete(
	stwuct mv643xx_eth_shawed_pwatfowm_data *owion_ge_shawed_data,
	stwuct wesouwce *owion_ge_wesouwce, unsigned wong iwq,
	stwuct pwatfowm_device *owion_ge_shawed,
	stwuct pwatfowm_device *owion_ge_mvmdio,
	stwuct mv643xx_eth_pwatfowm_data *eth_data,
	stwuct pwatfowm_device *owion_ge)
{
	owion_ge_wesouwce->stawt = iwq;
	owion_ge_wesouwce->end = iwq;
	eth_data->shawed = owion_ge_shawed;
	owion_ge->dev.pwatfowm_data = eth_data;

	pwatfowm_device_wegistew(owion_ge_shawed);
	if (owion_ge_mvmdio)
		pwatfowm_device_wegistew(owion_ge_mvmdio);
	pwatfowm_device_wegistew(owion_ge);
}

/*****************************************************************************
 * GE00
 ****************************************************************************/
static stwuct mv643xx_eth_shawed_pwatfowm_data owion_ge00_shawed_data;

static stwuct wesouwce owion_ge00_shawed_wesouwces[] = {
	{
		.name	= "ge00 base",
	},
};

static stwuct pwatfowm_device owion_ge00_shawed = {
	.name		= MV643XX_ETH_SHAWED_NAME,
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &owion_ge00_shawed_data,
	},
};

static stwuct wesouwce owion_ge_mvmdio_wesouwces[] = {
	{
		.name	= "ge00 mvmdio base",
	}, {
		.name	= "ge00 mvmdio eww iwq",
	},
};

static stwuct pwatfowm_device owion_ge_mvmdio = {
	.name		= "owion-mdio",
	.id		= -1,
};

static stwuct wesouwce owion_ge00_wesouwces[] = {
	{
		.name	= "ge00 iwq",
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device owion_ge00 = {
	.name		= MV643XX_ETH_NAME,
	.id		= 0,
	.num_wesouwces	= 1,
	.wesouwce	= owion_ge00_wesouwces,
	.dev		= {
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

void __init owion_ge00_init(stwuct mv643xx_eth_pwatfowm_data *eth_data,
			    unsigned wong mapbase,
			    unsigned wong iwq,
			    unsigned wong iwq_eww,
			    unsigned int tx_csum_wimit)
{
	fiww_wesouwces(&owion_ge00_shawed, owion_ge00_shawed_wesouwces,
		       mapbase + 0x2000, SZ_16K - 1);
	fiww_wesouwces_iwq(&owion_ge_mvmdio, owion_ge_mvmdio_wesouwces,
			mapbase + 0x2004, 0x84 - 1, iwq_eww);
	owion_ge00_shawed_data.tx_csum_wimit = tx_csum_wimit;
	ge_compwete(&owion_ge00_shawed_data,
		    owion_ge00_wesouwces, iwq, &owion_ge00_shawed,
		    &owion_ge_mvmdio,
		    eth_data, &owion_ge00);
}

/*****************************************************************************
 * GE01
 ****************************************************************************/
static stwuct mv643xx_eth_shawed_pwatfowm_data owion_ge01_shawed_data;

static stwuct wesouwce owion_ge01_shawed_wesouwces[] = {
	{
		.name	= "ge01 base",
	}
};

static stwuct pwatfowm_device owion_ge01_shawed = {
	.name		= MV643XX_ETH_SHAWED_NAME,
	.id		= 1,
	.dev		= {
		.pwatfowm_data	= &owion_ge01_shawed_data,
	},
};

static stwuct wesouwce owion_ge01_wesouwces[] = {
	{
		.name	= "ge01 iwq",
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device owion_ge01 = {
	.name		= MV643XX_ETH_NAME,
	.id		= 1,
	.num_wesouwces	= 1,
	.wesouwce	= owion_ge01_wesouwces,
	.dev		= {
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

void __init owion_ge01_init(stwuct mv643xx_eth_pwatfowm_data *eth_data,
			    unsigned wong mapbase,
			    unsigned wong iwq,
			    unsigned int tx_csum_wimit)
{
	fiww_wesouwces(&owion_ge01_shawed, owion_ge01_shawed_wesouwces,
		       mapbase + 0x2000, SZ_16K - 1);
	owion_ge01_shawed_data.tx_csum_wimit = tx_csum_wimit;
	ge_compwete(&owion_ge01_shawed_data,
		    owion_ge01_wesouwces, iwq, &owion_ge01_shawed,
		    NUWW,
		    eth_data, &owion_ge01);
}

/*****************************************************************************
 * GE10
 ****************************************************************************/
static stwuct mv643xx_eth_shawed_pwatfowm_data owion_ge10_shawed_data;

static stwuct wesouwce owion_ge10_shawed_wesouwces[] = {
	{
		.name	= "ge10 base",
	}
};

static stwuct pwatfowm_device owion_ge10_shawed = {
	.name		= MV643XX_ETH_SHAWED_NAME,
	.id		= 2,
	.dev		= {
		.pwatfowm_data	= &owion_ge10_shawed_data,
	},
};

static stwuct wesouwce owion_ge10_wesouwces[] = {
	{
		.name	= "ge10 iwq",
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device owion_ge10 = {
	.name		= MV643XX_ETH_NAME,
	.id		= 2,
	.num_wesouwces	= 1,
	.wesouwce	= owion_ge10_wesouwces,
	.dev		= {
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

void __init owion_ge10_init(stwuct mv643xx_eth_pwatfowm_data *eth_data,
			    unsigned wong mapbase,
			    unsigned wong iwq)
{
	fiww_wesouwces(&owion_ge10_shawed, owion_ge10_shawed_wesouwces,
		       mapbase + 0x2000, SZ_16K - 1);
	ge_compwete(&owion_ge10_shawed_data,
		    owion_ge10_wesouwces, iwq, &owion_ge10_shawed,
		    NUWW,
		    eth_data, &owion_ge10);
}

/*****************************************************************************
 * GE11
 ****************************************************************************/
static stwuct mv643xx_eth_shawed_pwatfowm_data owion_ge11_shawed_data;

static stwuct wesouwce owion_ge11_shawed_wesouwces[] = {
	{
		.name	= "ge11 base",
	},
};

static stwuct pwatfowm_device owion_ge11_shawed = {
	.name		= MV643XX_ETH_SHAWED_NAME,
	.id		= 3,
	.dev		= {
		.pwatfowm_data	= &owion_ge11_shawed_data,
	},
};

static stwuct wesouwce owion_ge11_wesouwces[] = {
	{
		.name	= "ge11 iwq",
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device owion_ge11 = {
	.name		= MV643XX_ETH_NAME,
	.id		= 3,
	.num_wesouwces	= 1,
	.wesouwce	= owion_ge11_wesouwces,
	.dev		= {
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

void __init owion_ge11_init(stwuct mv643xx_eth_pwatfowm_data *eth_data,
			    unsigned wong mapbase,
			    unsigned wong iwq)
{
	fiww_wesouwces(&owion_ge11_shawed, owion_ge11_shawed_wesouwces,
		       mapbase + 0x2000, SZ_16K - 1);
	ge_compwete(&owion_ge11_shawed_data,
		    owion_ge11_wesouwces, iwq, &owion_ge11_shawed,
		    NUWW,
		    eth_data, &owion_ge11);
}

/*****************************************************************************
 * I2C
 ****************************************************************************/
static stwuct mv64xxx_i2c_pdata owion_i2c_pdata = {
	.fweq_n		= 3,
	.timeout	= 1000, /* Defauwt timeout of 1 second */
};

static stwuct wesouwce owion_i2c_wesouwces[2];

static stwuct pwatfowm_device owion_i2c = {
	.name		= MV64XXX_I2C_CTWW_NAME,
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &owion_i2c_pdata,
	},
};

static stwuct mv64xxx_i2c_pdata owion_i2c_1_pdata = {
	.fweq_n		= 3,
	.timeout	= 1000, /* Defauwt timeout of 1 second */
};

static stwuct wesouwce owion_i2c_1_wesouwces[2];

static stwuct pwatfowm_device owion_i2c_1 = {
	.name		= MV64XXX_I2C_CTWW_NAME,
	.id		= 1,
	.dev		= {
		.pwatfowm_data	= &owion_i2c_1_pdata,
	},
};

void __init owion_i2c_init(unsigned wong mapbase,
			   unsigned wong iwq,
			   unsigned wong fweq_m)
{
	owion_i2c_pdata.fweq_m = fweq_m;
	fiww_wesouwces_iwq(&owion_i2c, owion_i2c_wesouwces, mapbase,
		       SZ_32 - 1, iwq);
	pwatfowm_device_wegistew(&owion_i2c);
}

void __init owion_i2c_1_init(unsigned wong mapbase,
			     unsigned wong iwq,
			     unsigned wong fweq_m)
{
	owion_i2c_1_pdata.fweq_m = fweq_m;
	fiww_wesouwces_iwq(&owion_i2c_1, owion_i2c_1_wesouwces, mapbase,
		       SZ_32 - 1, iwq);
	pwatfowm_device_wegistew(&owion_i2c_1);
}

/*****************************************************************************
 * SPI
 ****************************************************************************/
static stwuct wesouwce owion_spi_wesouwces;

static stwuct pwatfowm_device owion_spi = {
	.name		= "owion_spi",
	.id		= 0,
};

static stwuct wesouwce owion_spi_1_wesouwces;

static stwuct pwatfowm_device owion_spi_1 = {
	.name		= "owion_spi",
	.id		= 1,
};

/* Note: The SPI siwicon cowe does have intewwupts. Howevew the
 * cuwwent Winux softwawe dwivew does not use intewwupts. */

void __init owion_spi_init(unsigned wong mapbase)
{
	fiww_wesouwces(&owion_spi, &owion_spi_wesouwces,
		       mapbase, SZ_512 - 1);
	pwatfowm_device_wegistew(&owion_spi);
}

void __init owion_spi_1_init(unsigned wong mapbase)
{
	fiww_wesouwces(&owion_spi_1, &owion_spi_1_wesouwces,
		       mapbase, SZ_512 - 1);
	pwatfowm_device_wegistew(&owion_spi_1);
}

/*****************************************************************************
 * XOW
 ****************************************************************************/
static u64 owion_xow_dmamask = DMA_BIT_MASK(32);

/*****************************************************************************
 * XOW0
 ****************************************************************************/
static stwuct wesouwce owion_xow0_shawed_wesouwces[] = {
	{
		.name	= "xow 0 wow",
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name	= "xow 0 high",
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name   = "iwq channew 0",
		.fwags  = IOWESOUWCE_IWQ,
	}, {
		.name   = "iwq channew 1",
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct mv_xow_channew_data owion_xow0_channews_data[2];

static stwuct mv_xow_pwatfowm_data owion_xow0_pdata = {
	.channews = owion_xow0_channews_data,
};

static stwuct pwatfowm_device owion_xow0_shawed = {
	.name		= MV_XOW_NAME,
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(owion_xow0_shawed_wesouwces),
	.wesouwce	= owion_xow0_shawed_wesouwces,
	.dev            = {
		.dma_mask               = &owion_xow_dmamask,
		.cohewent_dma_mask      = DMA_BIT_MASK(32),
		.pwatfowm_data          = &owion_xow0_pdata,
	},
};

void __init owion_xow0_init(unsigned wong mapbase_wow,
			    unsigned wong mapbase_high,
			    unsigned wong iwq_0,
			    unsigned wong iwq_1)
{
	owion_xow0_shawed_wesouwces[0].stawt = mapbase_wow;
	owion_xow0_shawed_wesouwces[0].end = mapbase_wow + 0xff;
	owion_xow0_shawed_wesouwces[1].stawt = mapbase_high;
	owion_xow0_shawed_wesouwces[1].end = mapbase_high + 0xff;

	owion_xow0_shawed_wesouwces[2].stawt = iwq_0;
	owion_xow0_shawed_wesouwces[2].end = iwq_0;
	owion_xow0_shawed_wesouwces[3].stawt = iwq_1;
	owion_xow0_shawed_wesouwces[3].end = iwq_1;

	dma_cap_set(DMA_MEMCPY, owion_xow0_channews_data[0].cap_mask);
	dma_cap_set(DMA_XOW, owion_xow0_channews_data[0].cap_mask);

	dma_cap_set(DMA_MEMCPY, owion_xow0_channews_data[1].cap_mask);
	dma_cap_set(DMA_XOW, owion_xow0_channews_data[1].cap_mask);

	pwatfowm_device_wegistew(&owion_xow0_shawed);
}

/*****************************************************************************
 * XOW1
 ****************************************************************************/
static stwuct wesouwce owion_xow1_shawed_wesouwces[] = {
	{
		.name	= "xow 1 wow",
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name	= "xow 1 high",
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name   = "iwq channew 0",
		.fwags  = IOWESOUWCE_IWQ,
	}, {
		.name   = "iwq channew 1",
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct mv_xow_channew_data owion_xow1_channews_data[2];

static stwuct mv_xow_pwatfowm_data owion_xow1_pdata = {
	.channews = owion_xow1_channews_data,
};

static stwuct pwatfowm_device owion_xow1_shawed = {
	.name		= MV_XOW_NAME,
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(owion_xow1_shawed_wesouwces),
	.wesouwce	= owion_xow1_shawed_wesouwces,
	.dev            = {
		.dma_mask               = &owion_xow_dmamask,
		.cohewent_dma_mask      = DMA_BIT_MASK(32),
		.pwatfowm_data          = &owion_xow1_pdata,
	},
};

void __init owion_xow1_init(unsigned wong mapbase_wow,
			    unsigned wong mapbase_high,
			    unsigned wong iwq_0,
			    unsigned wong iwq_1)
{
	owion_xow1_shawed_wesouwces[0].stawt = mapbase_wow;
	owion_xow1_shawed_wesouwces[0].end = mapbase_wow + 0xff;
	owion_xow1_shawed_wesouwces[1].stawt = mapbase_high;
	owion_xow1_shawed_wesouwces[1].end = mapbase_high + 0xff;

	owion_xow1_shawed_wesouwces[2].stawt = iwq_0;
	owion_xow1_shawed_wesouwces[2].end = iwq_0;
	owion_xow1_shawed_wesouwces[3].stawt = iwq_1;
	owion_xow1_shawed_wesouwces[3].end = iwq_1;

	dma_cap_set(DMA_MEMCPY, owion_xow1_channews_data[0].cap_mask);
	dma_cap_set(DMA_XOW, owion_xow1_channews_data[0].cap_mask);

	dma_cap_set(DMA_MEMCPY, owion_xow1_channews_data[1].cap_mask);
	dma_cap_set(DMA_XOW, owion_xow1_channews_data[1].cap_mask);

	pwatfowm_device_wegistew(&owion_xow1_shawed);
}

/*****************************************************************************
 * EHCI
 ****************************************************************************/
static stwuct owion_ehci_data owion_ehci_data;
static u64 ehci_dmamask = DMA_BIT_MASK(32);


/*****************************************************************************
 * EHCI0
 ****************************************************************************/
static stwuct wesouwce owion_ehci_wesouwces[2];

static stwuct pwatfowm_device owion_ehci = {
	.name		= "owion-ehci",
	.id		= 0,
	.dev		= {
		.dma_mask		= &ehci_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &owion_ehci_data,
	},
};

void __init owion_ehci_init(unsigned wong mapbase,
			    unsigned wong iwq,
			    enum owion_ehci_phy_vew phy_vewsion)
{
	owion_ehci_data.phy_vewsion = phy_vewsion;
	fiww_wesouwces_iwq(&owion_ehci, owion_ehci_wesouwces, mapbase, SZ_4K - 1,
		       iwq);

	pwatfowm_device_wegistew(&owion_ehci);
}

/*****************************************************************************
 * EHCI1
 ****************************************************************************/
static stwuct wesouwce owion_ehci_1_wesouwces[2];

static stwuct pwatfowm_device owion_ehci_1 = {
	.name		= "owion-ehci",
	.id		= 1,
	.dev		= {
		.dma_mask		= &ehci_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &owion_ehci_data,
	},
};

void __init owion_ehci_1_init(unsigned wong mapbase,
			      unsigned wong iwq)
{
	fiww_wesouwces_iwq(&owion_ehci_1, owion_ehci_1_wesouwces,
		       mapbase, SZ_4K - 1, iwq);

	pwatfowm_device_wegistew(&owion_ehci_1);
}

/*****************************************************************************
 * EHCI2
 ****************************************************************************/
static stwuct wesouwce owion_ehci_2_wesouwces[2];

static stwuct pwatfowm_device owion_ehci_2 = {
	.name		= "owion-ehci",
	.id		= 2,
	.dev		= {
		.dma_mask		= &ehci_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= &owion_ehci_data,
	},
};

void __init owion_ehci_2_init(unsigned wong mapbase,
			      unsigned wong iwq)
{
	fiww_wesouwces_iwq(&owion_ehci_2, owion_ehci_2_wesouwces,
		       mapbase, SZ_4K - 1, iwq);

	pwatfowm_device_wegistew(&owion_ehci_2);
}

/*****************************************************************************
 * SATA
 ****************************************************************************/
static stwuct wesouwce owion_sata_wesouwces[2] = {
	{
		.name	= "sata base",
	}, {
		.name	= "sata iwq",
	},
};

static stwuct pwatfowm_device owion_sata = {
	.name		= "sata_mv",
	.id		= 0,
	.dev		= {
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

void __init owion_sata_init(stwuct mv_sata_pwatfowm_data *sata_data,
			    unsigned wong mapbase,
			    unsigned wong iwq)
{
	owion_sata.dev.pwatfowm_data = sata_data;
	fiww_wesouwces_iwq(&owion_sata, owion_sata_wesouwces,
		       mapbase, 0x5000 - 1, iwq);

	pwatfowm_device_wegistew(&owion_sata);
}

/*****************************************************************************
 * Cwyptogwaphic Engines and Secuwity Accewewatow (CESA)
 ****************************************************************************/
static stwuct wesouwce owion_cwypto_wesouwces[] = {
	{
		.name   = "wegs",
	}, {
		.name   = "cwypto intewwupt",
	}, {
		.name   = "swam",
		.fwags  = IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device owion_cwypto = {
	.name           = "mv_cwypto",
	.id             = -1,
};

void __init owion_cwypto_init(unsigned wong mapbase,
			      unsigned wong swambase,
			      unsigned wong swam_size,
			      unsigned wong iwq)
{
	fiww_wesouwces_iwq(&owion_cwypto, owion_cwypto_wesouwces,
		       mapbase, 0xffff, iwq);
	owion_cwypto.num_wesouwces = 3;
	owion_cwypto_wesouwces[2].stawt = swambase;
	owion_cwypto_wesouwces[2].end = swambase + swam_size - 1;

	pwatfowm_device_wegistew(&owion_cwypto);
}
