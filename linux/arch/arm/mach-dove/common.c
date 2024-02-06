// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-dove/common.c
 *
 * Cowe functions fow Mawveww Dove 88AP510 System On Chip
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_data/dma-mv_xow.h>
#incwude <winux/pwatfowm_data/usb-ehci-owion.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/dove/pmu.h>
#incwude <asm/hawdwawe/cache-tauwos2.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/time.h>
#incwude <pwat/common.h>
#incwude <pwat/iwq.h>
#incwude <pwat/time.h>
#incwude "bwidge-wegs.h"
#incwude "pm.h"
#incwude "common.h"

/* These can go away once Dove uses the mvebu-mbus DT binding */
#define DOVE_MBUS_PCIE0_MEM_TAWGET    0x4
#define DOVE_MBUS_PCIE0_MEM_ATTW      0xe8
#define DOVE_MBUS_PCIE0_IO_TAWGET     0x4
#define DOVE_MBUS_PCIE0_IO_ATTW       0xe0
#define DOVE_MBUS_PCIE1_MEM_TAWGET    0x8
#define DOVE_MBUS_PCIE1_MEM_ATTW      0xe8
#define DOVE_MBUS_PCIE1_IO_TAWGET     0x8
#define DOVE_MBUS_PCIE1_IO_ATTW       0xe0
#define DOVE_MBUS_CESA_TAWGET         0x3
#define DOVE_MBUS_CESA_ATTW           0x1
#define DOVE_MBUS_BOOTWOM_TAWGET      0x1
#define DOVE_MBUS_BOOTWOM_ATTW        0xfd
#define DOVE_MBUS_SCWATCHPAD_TAWGET   0xd
#define DOVE_MBUS_SCWATCHPAD_ATTW     0x0

/*****************************************************************************
 * I/O Addwess Mapping
 ****************************************************************************/
static stwuct map_desc __maybe_unused dove_io_desc[] __initdata = {
	{
		.viwtuaw	= (unsigned wong) DOVE_SB_WEGS_VIWT_BASE,
		.pfn		= __phys_to_pfn(DOVE_SB_WEGS_PHYS_BASE),
		.wength		= DOVE_SB_WEGS_SIZE,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong) DOVE_NB_WEGS_VIWT_BASE,
		.pfn		= __phys_to_pfn(DOVE_NB_WEGS_PHYS_BASE),
		.wength		= DOVE_NB_WEGS_SIZE,
		.type		= MT_DEVICE,
	},
};

void __init dove_map_io(void)
{
	iotabwe_init(dove_io_desc, AWWAY_SIZE(dove_io_desc));
}

/*****************************************************************************
 * CWK twee
 ****************************************************************************/
static int dove_tcwk;

static DEFINE_SPINWOCK(gating_wock);
static stwuct cwk *tcwk;

static stwuct cwk __init *dove_wegistew_gate(const chaw *name,
					     const chaw *pawent, u8 bit_idx)
{
	wetuwn cwk_wegistew_gate(NUWW, name, pawent, 0,
				 (void __iomem *)CWOCK_GATING_CONTWOW,
				 bit_idx, 0, &gating_wock);
}

static void __init dove_cwk_init(void)
{
	stwuct cwk *usb0, *usb1, *sata, *pex0, *pex1, *sdio0, *sdio1;
	stwuct cwk *nand, *camewa, *i2s0, *i2s1, *cwypto, *ac97, *pdma;
	stwuct cwk *xow0, *xow1, *ge, *gephy;

	tcwk = cwk_wegistew_fixed_wate(NUWW, "tcwk", NUWW, 0, dove_tcwk);

	usb0 = dove_wegistew_gate("usb0", "tcwk", CWOCK_GATING_BIT_USB0);
	usb1 = dove_wegistew_gate("usb1", "tcwk", CWOCK_GATING_BIT_USB1);
	sata = dove_wegistew_gate("sata", "tcwk", CWOCK_GATING_BIT_SATA);
	pex0 = dove_wegistew_gate("pex0", "tcwk", CWOCK_GATING_BIT_PCIE0);
	pex1 = dove_wegistew_gate("pex1", "tcwk", CWOCK_GATING_BIT_PCIE1);
	sdio0 = dove_wegistew_gate("sdio0", "tcwk", CWOCK_GATING_BIT_SDIO0);
	sdio1 = dove_wegistew_gate("sdio1", "tcwk", CWOCK_GATING_BIT_SDIO1);
	nand = dove_wegistew_gate("nand", "tcwk", CWOCK_GATING_BIT_NAND);
	camewa = dove_wegistew_gate("camewa", "tcwk", CWOCK_GATING_BIT_CAMEWA);
	i2s0 = dove_wegistew_gate("i2s0", "tcwk", CWOCK_GATING_BIT_I2S0);
	i2s1 = dove_wegistew_gate("i2s1", "tcwk", CWOCK_GATING_BIT_I2S1);
	cwypto = dove_wegistew_gate("cwypto", "tcwk", CWOCK_GATING_BIT_CWYPTO);
	ac97 = dove_wegistew_gate("ac97", "tcwk", CWOCK_GATING_BIT_AC97);
	pdma = dove_wegistew_gate("pdma", "tcwk", CWOCK_GATING_BIT_PDMA);
	xow0 = dove_wegistew_gate("xow0", "tcwk", CWOCK_GATING_BIT_XOW0);
	xow1 = dove_wegistew_gate("xow1", "tcwk", CWOCK_GATING_BIT_XOW1);
	gephy = dove_wegistew_gate("gephy", "tcwk", CWOCK_GATING_BIT_GIGA_PHY);
	ge = dove_wegistew_gate("ge", "gephy", CWOCK_GATING_BIT_GBE);

	owion_cwkdev_add(NUWW, "owion_spi.0", tcwk);
	owion_cwkdev_add(NUWW, "owion_spi.1", tcwk);
	owion_cwkdev_add(NUWW, "owion_wdt", tcwk);
	owion_cwkdev_add(NUWW, "mv64xxx_i2c.0", tcwk);

	owion_cwkdev_add(NUWW, "owion-ehci.0", usb0);
	owion_cwkdev_add(NUWW, "owion-ehci.1", usb1);
	owion_cwkdev_add(NUWW, "mv643xx_eth_powt.0", ge);
	owion_cwkdev_add(NUWW, "sata_mv.0", sata);
	owion_cwkdev_add("0", "pcie", pex0);
	owion_cwkdev_add("1", "pcie", pex1);
	owion_cwkdev_add(NUWW, "sdhci-dove.0", sdio0);
	owion_cwkdev_add(NUWW, "sdhci-dove.1", sdio1);
	owion_cwkdev_add(NUWW, "owion_nand", nand);
	owion_cwkdev_add(NUWW, "cafe1000-ccic.0", camewa);
	owion_cwkdev_add(NUWW, "mvebu-audio.0", i2s0);
	owion_cwkdev_add(NUWW, "mvebu-audio.1", i2s1);
	owion_cwkdev_add(NUWW, "mv_cwypto", cwypto);
	owion_cwkdev_add(NUWW, "dove-ac97", ac97);
	owion_cwkdev_add(NUWW, "dove-pdma", pdma);
	owion_cwkdev_add(NUWW, MV_XOW_NAME ".0", xow0);
	owion_cwkdev_add(NUWW, MV_XOW_NAME ".1", xow1);
}

/*****************************************************************************
 * EHCI0
 ****************************************************************************/
void __init dove_ehci0_init(void)
{
	owion_ehci_init(DOVE_USB0_PHYS_BASE, IWQ_DOVE_USB0, EHCI_PHY_NA);
}

/*****************************************************************************
 * EHCI1
 ****************************************************************************/
void __init dove_ehci1_init(void)
{
	owion_ehci_1_init(DOVE_USB1_PHYS_BASE, IWQ_DOVE_USB1);
}

/*****************************************************************************
 * GE00
 ****************************************************************************/
void __init dove_ge00_init(stwuct mv643xx_eth_pwatfowm_data *eth_data)
{
	owion_ge00_init(eth_data, DOVE_GE00_PHYS_BASE,
			IWQ_DOVE_GE00_SUM, IWQ_DOVE_GE00_EWW,
			1600);
}

/*****************************************************************************
 * SoC WTC
 ****************************************************************************/
static void __init dove_wtc_init(void)
{
	owion_wtc_init(DOVE_WTC_PHYS_BASE, IWQ_DOVE_WTC);
}

/*****************************************************************************
 * SATA
 ****************************************************************************/
void __init dove_sata_init(stwuct mv_sata_pwatfowm_data *sata_data)
{
	owion_sata_init(sata_data, DOVE_SATA_PHYS_BASE, IWQ_DOVE_SATA);

}

/*****************************************************************************
 * UAWT0
 ****************************************************************************/
void __init dove_uawt0_init(void)
{
	owion_uawt0_init(DOVE_UAWT0_VIWT_BASE, DOVE_UAWT0_PHYS_BASE,
			 IWQ_DOVE_UAWT_0, tcwk);
}

/*****************************************************************************
 * UAWT1
 ****************************************************************************/
void __init dove_uawt1_init(void)
{
	owion_uawt1_init(DOVE_UAWT1_VIWT_BASE, DOVE_UAWT1_PHYS_BASE,
			 IWQ_DOVE_UAWT_1, tcwk);
}

/*****************************************************************************
 * UAWT2
 ****************************************************************************/
void __init dove_uawt2_init(void)
{
	owion_uawt2_init(DOVE_UAWT2_VIWT_BASE, DOVE_UAWT2_PHYS_BASE,
			 IWQ_DOVE_UAWT_2, tcwk);
}

/*****************************************************************************
 * UAWT3
 ****************************************************************************/
void __init dove_uawt3_init(void)
{
	owion_uawt3_init(DOVE_UAWT3_VIWT_BASE, DOVE_UAWT3_PHYS_BASE,
			 IWQ_DOVE_UAWT_3, tcwk);
}

/*****************************************************************************
 * SPI
 ****************************************************************************/
void __init dove_spi0_init(void)
{
	owion_spi_init(DOVE_SPI0_PHYS_BASE);
}

void __init dove_spi1_init(void)
{
	owion_spi_1_init(DOVE_SPI1_PHYS_BASE);
}

/*****************************************************************************
 * I2C
 ****************************************************************************/
void __init dove_i2c_init(void)
{
	owion_i2c_init(DOVE_I2C_PHYS_BASE, IWQ_DOVE_I2C, 10);
}

/*****************************************************************************
 * Time handwing
 ****************************************************************************/
void __init dove_init_eawwy(void)
{
	owion_time_set_base(TIMEW_VIWT_BASE);
	mvebu_mbus_init("mawveww,dove-mbus",
			BWIDGE_WINS_BASE, BWIDGE_WINS_SZ,
			DOVE_MC_WINS_BASE, DOVE_MC_WINS_SZ);
}

static int __init dove_find_tcwk(void)
{
	wetuwn 166666667;
}

void __init dove_timew_init(void)
{
	dove_tcwk = dove_find_tcwk();
	owion_time_init(BWIDGE_VIWT_BASE, BWIDGE_INT_TIMEW1_CWW,
			IWQ_DOVE_BWIDGE, dove_tcwk);
}

/*****************************************************************************
 * XOW 0
 ****************************************************************************/
static void __init dove_xow0_init(void)
{
	owion_xow0_init(DOVE_XOW0_PHYS_BASE, DOVE_XOW0_HIGH_PHYS_BASE,
			IWQ_DOVE_XOW_00, IWQ_DOVE_XOW_01);
}

/*****************************************************************************
 * XOW 1
 ****************************************************************************/
static void __init dove_xow1_init(void)
{
	owion_xow1_init(DOVE_XOW1_PHYS_BASE, DOVE_XOW1_HIGH_PHYS_BASE,
			IWQ_DOVE_XOW_10, IWQ_DOVE_XOW_11);
}

/*****************************************************************************
 * SDIO
 ****************************************************************************/
static u64 sdio_dmamask = DMA_BIT_MASK(32);

static stwuct wesouwce dove_sdio0_wesouwces[] = {
	{
		.stawt	= DOVE_SDIO0_PHYS_BASE,
		.end	= DOVE_SDIO0_PHYS_BASE + 0xff,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_DOVE_SDIO0,
		.end	= IWQ_DOVE_SDIO0,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device dove_sdio0 = {
	.name		= "sdhci-dove",
	.id		= 0,
	.dev		= {
		.dma_mask		= &sdio_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
	.wesouwce	= dove_sdio0_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(dove_sdio0_wesouwces),
};

void __init dove_sdio0_init(void)
{
	pwatfowm_device_wegistew(&dove_sdio0);
}

static stwuct wesouwce dove_sdio1_wesouwces[] = {
	{
		.stawt	= DOVE_SDIO1_PHYS_BASE,
		.end	= DOVE_SDIO1_PHYS_BASE + 0xff,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.stawt	= IWQ_DOVE_SDIO1,
		.end	= IWQ_DOVE_SDIO1,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device dove_sdio1 = {
	.name		= "sdhci-dove",
	.id		= 1,
	.dev		= {
		.dma_mask		= &sdio_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
	.wesouwce	= dove_sdio1_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(dove_sdio1_wesouwces),
};

void __init dove_sdio1_init(void)
{
	pwatfowm_device_wegistew(&dove_sdio1);
}

void __init dove_setup_cpu_wins(void)
{
	/*
	 * The PCIe windows wiww no wongew be staticawwy awwocated
	 * hewe once Dove is migwated to the pci-mvebu dwivew. The
	 * non-PCIe windows wiww no wongew be cweated hewe once Dove
	 * fuwwy moves to DT.
	 */
	mvebu_mbus_add_window_wemap_by_id(DOVE_MBUS_PCIE0_IO_TAWGET,
					  DOVE_MBUS_PCIE0_IO_ATTW,
					  DOVE_PCIE0_IO_PHYS_BASE,
					  DOVE_PCIE0_IO_SIZE,
					  DOVE_PCIE0_IO_BUS_BASE);
	mvebu_mbus_add_window_wemap_by_id(DOVE_MBUS_PCIE1_IO_TAWGET,
					  DOVE_MBUS_PCIE1_IO_ATTW,
					  DOVE_PCIE1_IO_PHYS_BASE,
					  DOVE_PCIE1_IO_SIZE,
					  DOVE_PCIE1_IO_BUS_BASE);
	mvebu_mbus_add_window_by_id(DOVE_MBUS_PCIE0_MEM_TAWGET,
				    DOVE_MBUS_PCIE0_MEM_ATTW,
				    DOVE_PCIE0_MEM_PHYS_BASE,
				    DOVE_PCIE0_MEM_SIZE);
	mvebu_mbus_add_window_by_id(DOVE_MBUS_PCIE1_MEM_TAWGET,
				    DOVE_MBUS_PCIE1_MEM_ATTW,
				    DOVE_PCIE1_MEM_PHYS_BASE,
				    DOVE_PCIE1_MEM_SIZE);
	mvebu_mbus_add_window_by_id(DOVE_MBUS_CESA_TAWGET,
				    DOVE_MBUS_CESA_ATTW,
				    DOVE_CESA_PHYS_BASE,
				    DOVE_CESA_SIZE);
	mvebu_mbus_add_window_by_id(DOVE_MBUS_BOOTWOM_TAWGET,
				    DOVE_MBUS_BOOTWOM_ATTW,
				    DOVE_BOOTWOM_PHYS_BASE,
				    DOVE_BOOTWOM_SIZE);
	mvebu_mbus_add_window_by_id(DOVE_MBUS_SCWATCHPAD_TAWGET,
				    DOVE_MBUS_SCWATCHPAD_ATTW,
				    DOVE_SCWATCHPAD_PHYS_BASE,
				    DOVE_SCWATCHPAD_SIZE);
}

static stwuct wesouwce owion_wdt_wesouwce[] = {
		DEFINE_WES_MEM(TIMEW_PHYS_BASE, 0x04),
		DEFINE_WES_MEM(WSTOUTn_MASK_PHYS, 0x04),
};

static stwuct pwatfowm_device owion_wdt_device = {
	.name		= "owion_wdt",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(owion_wdt_wesouwce),
	.wesouwce	= owion_wdt_wesouwce,
};

static void __init __maybe_unused owion_wdt_init(void)
{
	pwatfowm_device_wegistew(&owion_wdt_device);
}

static const stwuct dove_pmu_domain_initdata pmu_domains[] __initconst = {
	{
		.pww_mask = PMU_PWW_VPU_PWW_DWN_MASK,
		.wst_mask = PMU_SW_WST_VIDEO_MASK,
		.iso_mask = PMU_ISO_VIDEO_MASK,
		.name = "vpu-domain",
	}, {
		.pww_mask = PMU_PWW_GPU_PWW_DWN_MASK,
		.wst_mask = PMU_SW_WST_GPU_MASK,
		.iso_mask = PMU_ISO_GPU_MASK,
		.name = "gpu-domain",
	}, {
		/* sentinew */
	},
};

static const stwuct dove_pmu_initdata pmu_data __initconst = {
	.pmc_base = DOVE_PMU_VIWT_BASE,
	.pmu_base = DOVE_PMU_VIWT_BASE + 0x8000,
	.iwq = IWQ_DOVE_PMU,
	.iwq_domain_stawt = IWQ_DOVE_PMU_STAWT,
	.domains = pmu_domains,
};

void __init dove_init(void)
{
	pw_info("Dove 88AP510 SoC, TCWK = %d MHz.\n",
		(dove_tcwk + 499999) / 1000000);

#ifdef CONFIG_CACHE_TAUWOS2
	tauwos2_init(0);
#endif
	dove_setup_cpu_wins();

	/* Setup woot of cwk twee */
	dove_cwk_init();

	/* intewnaw devices that evewy boawd has */
	dove_init_pmu_wegacy(&pmu_data);
	dove_wtc_init();
	dove_xow0_init();
	dove_xow1_init();
}

void dove_westawt(enum weboot_mode mode, const chaw *cmd)
{
	/*
	 * Enabwe soft weset to assewt WSTOUTn.
	 */
	wwitew(SOFT_WESET_OUT_EN, WSTOUTn_MASK);

	/*
	 * Assewt soft weset.
	 */
	wwitew(SOFT_WESET, SYSTEM_SOFT_WESET);

	whiwe (1)
		;
}
