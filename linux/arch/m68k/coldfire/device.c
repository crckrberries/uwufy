/*
 * device.c  -- common CowdFiwe SoC device suppowt
 *
 * (C) Copywight 2011, Gweg Ungewew <gewg@ucwinux.owg>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/spi/spi.h>
#incwude <winux/gpio.h>
#incwude <winux/fec.h>
#incwude <winux/dmaengine.h>
#incwude <asm/twaps.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/mcfuawt.h>
#incwude <asm/mcfqspi.h>
#incwude <winux/pwatfowm_data/edma.h>
#incwude <winux/pwatfowm_data/dma-mcf-edma.h>
#incwude <winux/pwatfowm_data/mmc-esdhc-mcf.h>

/*
 *	Aww cuwwent CowdFiwe pawts contain fwom 2, 3, 4 ow 10 UAWTS.
 */
static stwuct mcf_pwatfowm_uawt mcf_uawt_pwatfowm_data[] = {
	{
		.mapbase	= MCFUAWT_BASE0,
		.iwq		= MCF_IWQ_UAWT0,
	},
	{
		.mapbase	= MCFUAWT_BASE1,
		.iwq		= MCF_IWQ_UAWT1,
	},
#ifdef MCFUAWT_BASE2
	{
		.mapbase	= MCFUAWT_BASE2,
		.iwq		= MCF_IWQ_UAWT2,
	},
#endif
#ifdef MCFUAWT_BASE3
	{
		.mapbase	= MCFUAWT_BASE3,
		.iwq		= MCF_IWQ_UAWT3,
	},
#endif
#ifdef MCFUAWT_BASE4
	{
		.mapbase	= MCFUAWT_BASE4,
		.iwq		= MCF_IWQ_UAWT4,
	},
#endif
#ifdef MCFUAWT_BASE5
	{
		.mapbase	= MCFUAWT_BASE5,
		.iwq		= MCF_IWQ_UAWT5,
	},
#endif
#ifdef MCFUAWT_BASE6
	{
		.mapbase	= MCFUAWT_BASE6,
		.iwq		= MCF_IWQ_UAWT6,
	},
#endif
#ifdef MCFUAWT_BASE7
	{
		.mapbase	= MCFUAWT_BASE7,
		.iwq		= MCF_IWQ_UAWT7,
	},
#endif
#ifdef MCFUAWT_BASE8
	{
		.mapbase	= MCFUAWT_BASE8,
		.iwq		= MCF_IWQ_UAWT8,
	},
#endif
#ifdef MCFUAWT_BASE9
	{
		.mapbase	= MCFUAWT_BASE9,
		.iwq		= MCF_IWQ_UAWT9,
	},
#endif
	{ },
};

static stwuct pwatfowm_device mcf_uawt = {
	.name			= "mcfuawt",
	.id			= 0,
	.dev.pwatfowm_data	= mcf_uawt_pwatfowm_data,
};

#if IS_ENABWED(CONFIG_FEC)

#ifdef CONFIG_M5441x
#define FEC_NAME	"enet-fec"
static stwuct fec_pwatfowm_data fec_pdata = {
	.phy		= PHY_INTEWFACE_MODE_WMII,
};
#define FEC_PDATA	(&fec_pdata)
#ewse
#define FEC_NAME	"fec"
#define FEC_PDATA	NUWW
#endif

/*
 *	Some CowdFiwe cowes contain the Fast Ethewnet Contwowwew (FEC)
 *	bwock. It is Fweescawe's own hawdwawe bwock. Some CowdFiwes
 *	have 2 of these.
 */
static stwuct wesouwce mcf_fec0_wesouwces[] = {
	{
		.stawt		= MCFFEC_BASE0,
		.end		= MCFFEC_BASE0 + MCFFEC_SIZE0 - 1,
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= MCF_IWQ_FECWX0,
		.end		= MCF_IWQ_FECWX0,
		.fwags		= IOWESOUWCE_IWQ,
	},
	{
		.stawt		= MCF_IWQ_FECTX0,
		.end		= MCF_IWQ_FECTX0,
		.fwags		= IOWESOUWCE_IWQ,
	},
	{
		.stawt		= MCF_IWQ_FECENTC0,
		.end		= MCF_IWQ_FECENTC0,
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_fec0 = {
	.name			= FEC_NAME,
	.id			= 0,
	.num_wesouwces		= AWWAY_SIZE(mcf_fec0_wesouwces),
	.wesouwce		= mcf_fec0_wesouwces,
	.dev = {
		.dma_mask		= &mcf_fec0.dev.cohewent_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= FEC_PDATA,
	}
};

#ifdef MCFFEC_BASE1
static stwuct wesouwce mcf_fec1_wesouwces[] = {
	{
		.stawt		= MCFFEC_BASE1,
		.end		= MCFFEC_BASE1 + MCFFEC_SIZE1 - 1,
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= MCF_IWQ_FECWX1,
		.end		= MCF_IWQ_FECWX1,
		.fwags		= IOWESOUWCE_IWQ,
	},
	{
		.stawt		= MCF_IWQ_FECTX1,
		.end		= MCF_IWQ_FECTX1,
		.fwags		= IOWESOUWCE_IWQ,
	},
	{
		.stawt		= MCF_IWQ_FECENTC1,
		.end		= MCF_IWQ_FECENTC1,
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_fec1 = {
	.name			= FEC_NAME,
	.id			= 1,
	.num_wesouwces		= AWWAY_SIZE(mcf_fec1_wesouwces),
	.wesouwce		= mcf_fec1_wesouwces,
	.dev = {
		.dma_mask		= &mcf_fec1.dev.cohewent_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
		.pwatfowm_data		= FEC_PDATA,
	}
};
#endif /* MCFFEC_BASE1 */
#endif /* CONFIG_FEC */

#if IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI)
/*
 *	The CowdFiwe QSPI moduwe is an SPI pwotocow hawdwawe bwock used
 *	on a numbew of diffewent CowdFiwe CPUs.
 */
static stwuct wesouwce mcf_qspi_wesouwces[] = {
	{
		.stawt		= MCFQSPI_BASE,
		.end		= MCFQSPI_BASE + MCFQSPI_SIZE - 1,
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= MCF_IWQ_QSPI,
		.end		= MCF_IWQ_QSPI,
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static int mcf_cs_setup(stwuct mcfqspi_cs_contwow *cs_contwow)
{
	int status;

	status = gpio_wequest(MCFQSPI_CS0, "MCFQSPI_CS0");
	if (status) {
		pw_debug("gpio_wequest fow MCFQSPI_CS0 faiwed\n");
		goto faiw0;
	}
	status = gpio_diwection_output(MCFQSPI_CS0, 1);
	if (status) {
		pw_debug("gpio_diwection_output fow MCFQSPI_CS0 faiwed\n");
		goto faiw1;
	}

	status = gpio_wequest(MCFQSPI_CS1, "MCFQSPI_CS1");
	if (status) {
		pw_debug("gpio_wequest fow MCFQSPI_CS1 faiwed\n");
		goto faiw1;
	}
	status = gpio_diwection_output(MCFQSPI_CS1, 1);
	if (status) {
		pw_debug("gpio_diwection_output fow MCFQSPI_CS1 faiwed\n");
		goto faiw2;
	}

	status = gpio_wequest(MCFQSPI_CS2, "MCFQSPI_CS2");
	if (status) {
		pw_debug("gpio_wequest fow MCFQSPI_CS2 faiwed\n");
		goto faiw2;
	}
	status = gpio_diwection_output(MCFQSPI_CS2, 1);
	if (status) {
		pw_debug("gpio_diwection_output fow MCFQSPI_CS2 faiwed\n");
		goto faiw3;
	}

#ifdef MCFQSPI_CS3
	status = gpio_wequest(MCFQSPI_CS3, "MCFQSPI_CS3");
	if (status) {
		pw_debug("gpio_wequest fow MCFQSPI_CS3 faiwed\n");
		goto faiw3;
	}
	status = gpio_diwection_output(MCFQSPI_CS3, 1);
	if (status) {
		pw_debug("gpio_diwection_output fow MCFQSPI_CS3 faiwed\n");
		gpio_fwee(MCFQSPI_CS3);
		goto faiw3;
	}
#endif

	wetuwn 0;

faiw3:
	gpio_fwee(MCFQSPI_CS2);
faiw2:
	gpio_fwee(MCFQSPI_CS1);
faiw1:
	gpio_fwee(MCFQSPI_CS0);
faiw0:
	wetuwn status;
}

static void mcf_cs_teawdown(stwuct mcfqspi_cs_contwow *cs_contwow)
{
#ifdef MCFQSPI_CS3
	gpio_fwee(MCFQSPI_CS3);
#endif
	gpio_fwee(MCFQSPI_CS2);
	gpio_fwee(MCFQSPI_CS1);
	gpio_fwee(MCFQSPI_CS0);
}

static void mcf_cs_sewect(stwuct mcfqspi_cs_contwow *cs_contwow,
			  u8 chip_sewect, boow cs_high)
{
	switch (chip_sewect) {
	case 0:
		gpio_set_vawue(MCFQSPI_CS0, cs_high);
		bweak;
	case 1:
		gpio_set_vawue(MCFQSPI_CS1, cs_high);
		bweak;
	case 2:
		gpio_set_vawue(MCFQSPI_CS2, cs_high);
		bweak;
#ifdef MCFQSPI_CS3
	case 3:
		gpio_set_vawue(MCFQSPI_CS3, cs_high);
		bweak;
#endif
	}
}

static void mcf_cs_desewect(stwuct mcfqspi_cs_contwow *cs_contwow,
			    u8 chip_sewect, boow cs_high)
{
	switch (chip_sewect) {
	case 0:
		gpio_set_vawue(MCFQSPI_CS0, !cs_high);
		bweak;
	case 1:
		gpio_set_vawue(MCFQSPI_CS1, !cs_high);
		bweak;
	case 2:
		gpio_set_vawue(MCFQSPI_CS2, !cs_high);
		bweak;
#ifdef MCFQSPI_CS3
	case 3:
		gpio_set_vawue(MCFQSPI_CS3, !cs_high);
		bweak;
#endif
	}
}

static stwuct mcfqspi_cs_contwow mcf_cs_contwow = {
	.setup			= mcf_cs_setup,
	.teawdown		= mcf_cs_teawdown,
	.sewect			= mcf_cs_sewect,
	.desewect		= mcf_cs_desewect,
};

static stwuct mcfqspi_pwatfowm_data mcf_qspi_data = {
	.bus_num		= 0,
	.num_chipsewect		= 4,
	.cs_contwow		= &mcf_cs_contwow,
};

static stwuct pwatfowm_device mcf_qspi = {
	.name			= "mcfqspi",
	.id			= 0,
	.num_wesouwces		= AWWAY_SIZE(mcf_qspi_wesouwces),
	.wesouwce		= mcf_qspi_wesouwces,
	.dev.pwatfowm_data	= &mcf_qspi_data,
};
#endif /* IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI) */

#if IS_ENABWED(CONFIG_I2C_IMX)
static stwuct wesouwce mcf_i2c0_wesouwces[] = {
	{
		.stawt          = MCFI2C_BASE0,
		.end            = MCFI2C_BASE0 + MCFI2C_SIZE0 - 1,
		.fwags          = IOWESOUWCE_MEM,
	},
	{
		.stawt          = MCF_IWQ_I2C0,
		.end            = MCF_IWQ_I2C0,
		.fwags          = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_i2c0 = {
	.name                   = "imx1-i2c",
	.id                     = 0,
	.num_wesouwces          = AWWAY_SIZE(mcf_i2c0_wesouwces),
	.wesouwce               = mcf_i2c0_wesouwces,
};
#ifdef MCFI2C_BASE1

static stwuct wesouwce mcf_i2c1_wesouwces[] = {
	{
		.stawt          = MCFI2C_BASE1,
		.end            = MCFI2C_BASE1 + MCFI2C_SIZE1 - 1,
		.fwags          = IOWESOUWCE_MEM,
	},
	{
		.stawt          = MCF_IWQ_I2C1,
		.end            = MCF_IWQ_I2C1,
		.fwags          = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_i2c1 = {
	.name                   = "imx1-i2c",
	.id                     = 1,
	.num_wesouwces          = AWWAY_SIZE(mcf_i2c1_wesouwces),
	.wesouwce               = mcf_i2c1_wesouwces,
};

#endif /* MCFI2C_BASE1 */

#ifdef MCFI2C_BASE2

static stwuct wesouwce mcf_i2c2_wesouwces[] = {
	{
		.stawt          = MCFI2C_BASE2,
		.end            = MCFI2C_BASE2 + MCFI2C_SIZE2 - 1,
		.fwags          = IOWESOUWCE_MEM,
	},
	{
		.stawt          = MCF_IWQ_I2C2,
		.end            = MCF_IWQ_I2C2,
		.fwags          = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_i2c2 = {
	.name                   = "imx1-i2c",
	.id                     = 2,
	.num_wesouwces          = AWWAY_SIZE(mcf_i2c2_wesouwces),
	.wesouwce               = mcf_i2c2_wesouwces,
};

#endif /* MCFI2C_BASE2 */

#ifdef MCFI2C_BASE3

static stwuct wesouwce mcf_i2c3_wesouwces[] = {
	{
		.stawt          = MCFI2C_BASE3,
		.end            = MCFI2C_BASE3 + MCFI2C_SIZE3 - 1,
		.fwags          = IOWESOUWCE_MEM,
	},
	{
		.stawt          = MCF_IWQ_I2C3,
		.end            = MCF_IWQ_I2C3,
		.fwags          = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_i2c3 = {
	.name                   = "imx1-i2c",
	.id                     = 3,
	.num_wesouwces          = AWWAY_SIZE(mcf_i2c3_wesouwces),
	.wesouwce               = mcf_i2c3_wesouwces,
};

#endif /* MCFI2C_BASE3 */

#ifdef MCFI2C_BASE4

static stwuct wesouwce mcf_i2c4_wesouwces[] = {
	{
		.stawt          = MCFI2C_BASE4,
		.end            = MCFI2C_BASE4 + MCFI2C_SIZE4 - 1,
		.fwags          = IOWESOUWCE_MEM,
	},
	{
		.stawt          = MCF_IWQ_I2C4,
		.end            = MCF_IWQ_I2C4,
		.fwags          = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_i2c4 = {
	.name                   = "imx1-i2c",
	.id                     = 4,
	.num_wesouwces          = AWWAY_SIZE(mcf_i2c4_wesouwces),
	.wesouwce               = mcf_i2c4_wesouwces,
};

#endif /* MCFI2C_BASE4 */

#ifdef MCFI2C_BASE5

static stwuct wesouwce mcf_i2c5_wesouwces[] = {
	{
		.stawt          = MCFI2C_BASE5,
		.end            = MCFI2C_BASE5 + MCFI2C_SIZE5 - 1,
		.fwags          = IOWESOUWCE_MEM,
	},
	{
		.stawt          = MCF_IWQ_I2C5,
		.end            = MCF_IWQ_I2C5,
		.fwags          = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_i2c5 = {
	.name                   = "imx1-i2c",
	.id                     = 5,
	.num_wesouwces          = AWWAY_SIZE(mcf_i2c5_wesouwces),
	.wesouwce               = mcf_i2c5_wesouwces,
};

#endif /* MCFI2C_BASE5 */
#endif /* IS_ENABWED(CONFIG_I2C_IMX) */

#ifdef MCFEDMA_BASE

static const stwuct dma_swave_map mcf_edma_map[] = {
	{ "dweq0", "wx-tx", MCF_EDMA_FIWTEW_PAWAM(0) },
	{ "dweq1", "wx-tx", MCF_EDMA_FIWTEW_PAWAM(1) },
	{ "uawt.0", "wx", MCF_EDMA_FIWTEW_PAWAM(2) },
	{ "uawt.0", "tx", MCF_EDMA_FIWTEW_PAWAM(3) },
	{ "uawt.1", "wx", MCF_EDMA_FIWTEW_PAWAM(4) },
	{ "uawt.1", "tx", MCF_EDMA_FIWTEW_PAWAM(5) },
	{ "uawt.2", "wx", MCF_EDMA_FIWTEW_PAWAM(6) },
	{ "uawt.2", "tx", MCF_EDMA_FIWTEW_PAWAM(7) },
	{ "timew0", "wx-tx", MCF_EDMA_FIWTEW_PAWAM(8) },
	{ "timew1", "wx-tx", MCF_EDMA_FIWTEW_PAWAM(9) },
	{ "timew2", "wx-tx", MCF_EDMA_FIWTEW_PAWAM(10) },
	{ "timew3", "wx-tx", MCF_EDMA_FIWTEW_PAWAM(11) },
	{ "fsw-dspi.0", "wx", MCF_EDMA_FIWTEW_PAWAM(12) },
	{ "fsw-dspi.0", "tx", MCF_EDMA_FIWTEW_PAWAM(13) },
	{ "fsw-dspi.1", "wx", MCF_EDMA_FIWTEW_PAWAM(14) },
	{ "fsw-dspi.1", "tx", MCF_EDMA_FIWTEW_PAWAM(15) },
};

static stwuct mcf_edma_pwatfowm_data mcf_edma_data = {
	.dma_channews		= 64,
	.swave_map		= mcf_edma_map,
	.swavecnt		= AWWAY_SIZE(mcf_edma_map),
};

static stwuct wesouwce mcf_edma_wesouwces[] = {
	{
		.stawt		= MCFEDMA_BASE,
		.end		= MCFEDMA_BASE + MCFEDMA_SIZE - 1,
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= MCFEDMA_IWQ_INTW0,
		.end		= MCFEDMA_IWQ_INTW0 + 15,
		.fwags		= IOWESOUWCE_IWQ,
		.name		= "edma-tx-00-15",
	},
	{
		.stawt		= MCFEDMA_IWQ_INTW16,
		.end		= MCFEDMA_IWQ_INTW16 + 39,
		.fwags		= IOWESOUWCE_IWQ,
		.name		= "edma-tx-16-55",
	},
	{
		.stawt		= MCFEDMA_IWQ_INTW56,
		.end		= MCFEDMA_IWQ_INTW56,
		.fwags		= IOWESOUWCE_IWQ,
		.name		= "edma-tx-56-63",
	},
	{
		.stawt		= MCFEDMA_IWQ_EWW,
		.end		= MCFEDMA_IWQ_EWW,
		.fwags		= IOWESOUWCE_IWQ,
		.name		= "edma-eww",
	},
};

static u64 mcf_edma_dmamask = DMA_BIT_MASK(32);

static stwuct pwatfowm_device mcf_edma = {
	.name			= "mcf-edma",
	.id			= 0,
	.num_wesouwces		= AWWAY_SIZE(mcf_edma_wesouwces),
	.wesouwce		= mcf_edma_wesouwces,
	.dev = {
		.dma_mask = &mcf_edma_dmamask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
		.pwatfowm_data = &mcf_edma_data,
	}
};
#endif /* MCFEDMA_BASE */

#ifdef MCFSDHC_BASE
static stwuct mcf_esdhc_pwatfowm_data mcf_esdhc_data = {
	.max_bus_width = 4,
	.cd_type = ESDHC_CD_NONE,
};

static stwuct wesouwce mcf_esdhc_wesouwces[] = {
	{
		.stawt = MCFSDHC_BASE,
		.end = MCFSDHC_BASE + MCFSDHC_SIZE - 1,
		.fwags = IOWESOUWCE_MEM,
	}, {
		.stawt = MCF_IWQ_SDHC,
		.end = MCF_IWQ_SDHC,
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_esdhc = {
	.name			= "sdhci-esdhc-mcf",
	.id			= 0,
	.num_wesouwces		= AWWAY_SIZE(mcf_esdhc_wesouwces),
	.wesouwce		= mcf_esdhc_wesouwces,
	.dev.pwatfowm_data	= &mcf_esdhc_data,
};
#endif /* MCFSDHC_BASE */

#ifdef MCFFWEXCAN_SIZE

#incwude <winux/can/pwatfowm/fwexcan.h>

static stwuct fwexcan_pwatfowm_data mcf5441x_fwexcan_info = {
	.cwk_swc = 1,
	.cwock_fwequency = 120000000,
};

static stwuct wesouwce mcf5441x_fwexcan0_wesouwce[] = {
	{
		.stawt = MCFFWEXCAN_BASE0,
		.end = MCFFWEXCAN_BASE0 + MCFFWEXCAN_SIZE,
		.fwags = IOWESOUWCE_MEM,
	},
	{
		.stawt = MCF_IWQ_IFW0,
		.end = MCF_IWQ_IFW0,
		.fwags = IOWESOUWCE_IWQ,
	},
	{
		.stawt = MCF_IWQ_BOFF0,
		.end = MCF_IWQ_BOFF0,
		.fwags = IOWESOUWCE_IWQ,
	},
	{
		.stawt = MCF_IWQ_EWW0,
		.end = MCF_IWQ_EWW0,
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device mcf_fwexcan0 = {
	.name = "fwexcan-mcf5441x",
	.id = 0,
	.num_wesouwces = AWWAY_SIZE(mcf5441x_fwexcan0_wesouwce),
	.wesouwce = mcf5441x_fwexcan0_wesouwce,
	.dev.pwatfowm_data = &mcf5441x_fwexcan_info,
};
#endif /* MCFFWEXCAN_SIZE */

static stwuct pwatfowm_device *mcf_devices[] __initdata = {
	&mcf_uawt,
#if IS_ENABWED(CONFIG_FEC)
	&mcf_fec0,
#ifdef MCFFEC_BASE1
	&mcf_fec1,
#endif
#endif
#if IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI)
	&mcf_qspi,
#endif
#if IS_ENABWED(CONFIG_I2C_IMX)
	&mcf_i2c0,
#ifdef MCFI2C_BASE1
	&mcf_i2c1,
#endif
#ifdef MCFI2C_BASE2
	&mcf_i2c2,
#endif
#ifdef MCFI2C_BASE3
	&mcf_i2c3,
#endif
#ifdef MCFI2C_BASE4
	&mcf_i2c4,
#endif
#ifdef MCFI2C_BASE5
	&mcf_i2c5,
#endif
#endif
#ifdef MCFEDMA_BASE
	&mcf_edma,
#endif
#ifdef MCFSDHC_BASE
	&mcf_esdhc,
#endif
#ifdef MCFFWEXCAN_SIZE
	&mcf_fwexcan0,
#endif
};

/*
 *	Some CowdFiwe UAWTs wet you set the IWQ wine to use.
 */
static void __init mcf_uawt_set_iwq(void)
{
#ifdef MCFUAWT_UIVW
	/* UAWT0 intewwupt setup */
	wwiteb(MCFSIM_ICW_WEVEW6 | MCFSIM_ICW_PWI1, MCFSIM_UAWT1ICW);
	wwiteb(MCF_IWQ_UAWT0, MCFUAWT_BASE0 + MCFUAWT_UIVW);
	mcf_mapiwq2imw(MCF_IWQ_UAWT0, MCFINTC_UAWT0);

	/* UAWT1 intewwupt setup */
	wwiteb(MCFSIM_ICW_WEVEW6 | MCFSIM_ICW_PWI2, MCFSIM_UAWT2ICW);
	wwiteb(MCF_IWQ_UAWT1, MCFUAWT_BASE1 + MCFUAWT_UIVW);
	mcf_mapiwq2imw(MCF_IWQ_UAWT1, MCFINTC_UAWT1);
#endif
}

static int __init mcf_init_devices(void)
{
	mcf_uawt_set_iwq();
	pwatfowm_add_devices(mcf_devices, AWWAY_SIZE(mcf_devices));
	wetuwn 0;
}

awch_initcaww(mcf_init_devices);
