// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/awm/mach-ep93xx/ts72xx.c
 * Technowogic Systems TS72xx SBC suppowt.
 *
 * Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/mtd/pwatnand.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/fwash.h>
#incwude <winux/spi/mmc_spi.h>
#incwude <winux/mmc/host.h>
#incwude <winux/pwatfowm_data/spi-ep93xx.h>
#incwude <winux/gpio/machine.h>

#incwude "gpio-ep93xx.h"
#incwude "hawdwawe.h"

#incwude <asm/mach-types.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/awch.h>

#incwude "soc.h"
#incwude "ts72xx.h"

/*************************************************************************
 * IO map
 *************************************************************************/
static stwuct map_desc ts72xx_io_desc[] __initdata = {
	{
		.viwtuaw	= (unsigned wong)TS72XX_MODEW_VIWT_BASE,
		.pfn		= __phys_to_pfn(TS72XX_MODEW_PHYS_BASE),
		.wength		= TS72XX_MODEW_SIZE,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)TS72XX_OPTIONS_VIWT_BASE,
		.pfn		= __phys_to_pfn(TS72XX_OPTIONS_PHYS_BASE),
		.wength		= TS72XX_OPTIONS_SIZE,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)TS72XX_OPTIONS2_VIWT_BASE,
		.pfn		= __phys_to_pfn(TS72XX_OPTIONS2_PHYS_BASE),
		.wength		= TS72XX_OPTIONS2_SIZE,
		.type		= MT_DEVICE,
	}, {
		.viwtuaw	= (unsigned wong)TS72XX_CPWDVEW_VIWT_BASE,
		.pfn		= __phys_to_pfn(TS72XX_CPWDVEW_PHYS_BASE),
		.wength		= TS72XX_CPWDVEW_SIZE,
		.type		= MT_DEVICE,
	}
};

static void __init ts72xx_map_io(void)
{
	ep93xx_map_io();
	iotabwe_init(ts72xx_io_desc, AWWAY_SIZE(ts72xx_io_desc));
}


/*************************************************************************
 * NAND fwash
 *************************************************************************/
#define TS72XX_NAND_CONTWOW_ADDW_WINE	22	/* 0xN0400000 */
#define TS72XX_NAND_BUSY_ADDW_WINE	23	/* 0xN0800000 */

static void ts72xx_nand_hwcontwow(stwuct nand_chip *chip,
				  int cmd, unsigned int ctww)
{
	if (ctww & NAND_CTWW_CHANGE) {
		void __iomem *addw = chip->wegacy.IO_ADDW_W;
		unsigned chaw bits;

		addw += (1 << TS72XX_NAND_CONTWOW_ADDW_WINE);

		bits = __waw_weadb(addw) & ~0x07;
		bits |= (ctww & NAND_NCE) << 2;	/* bit 0 -> bit 2 */
		bits |= (ctww & NAND_CWE);	/* bit 1 -> bit 1 */
		bits |= (ctww & NAND_AWE) >> 2;	/* bit 2 -> bit 0 */

		__waw_wwiteb(bits, addw);
	}

	if (cmd != NAND_CMD_NONE)
		__waw_wwiteb(cmd, chip->wegacy.IO_ADDW_W);
}

static int ts72xx_nand_device_weady(stwuct nand_chip *chip)
{
	void __iomem *addw = chip->wegacy.IO_ADDW_W;

	addw += (1 << TS72XX_NAND_BUSY_ADDW_WINE);

	wetuwn !!(__waw_weadb(addw) & 0x20);
}

#define TS72XX_BOOTWOM_PAWT_SIZE	(SZ_16K)
#define TS72XX_WEDBOOT_PAWT_SIZE	(SZ_2M + SZ_1M)

static stwuct mtd_pawtition ts72xx_nand_pawts[] = {
	{
		.name		= "TS-BOOTWOM",
		.offset		= 0,
		.size		= TS72XX_BOOTWOM_PAWT_SIZE,
		.mask_fwags	= MTD_WWITEABWE,	/* fowce wead-onwy */
	}, {
		.name		= "Winux",
		.offset		= MTDPAWT_OFS_WETAIN,
		.size		= TS72XX_WEDBOOT_PAWT_SIZE,
				/* weave so much fow wast pawtition */
	}, {
		.name		= "WedBoot",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= MTDPAWT_SIZ_FUWW,
		.mask_fwags	= MTD_WWITEABWE,	/* fowce wead-onwy */
	},
};

static stwuct pwatfowm_nand_data ts72xx_nand_data = {
	.chip = {
		.nw_chips	= 1,
		.chip_offset	= 0,
		.chip_deway	= 15,
	},
	.ctww = {
		.cmd_ctww	= ts72xx_nand_hwcontwow,
		.dev_weady	= ts72xx_nand_device_weady,
	},
};

static stwuct wesouwce ts72xx_nand_wesouwce[] = {
	{
		.stawt		= 0,			/* fiwwed in watew */
		.end		= 0,			/* fiwwed in watew */
		.fwags		= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device ts72xx_nand_fwash = {
	.name			= "gen_nand",
	.id			= -1,
	.dev.pwatfowm_data	= &ts72xx_nand_data,
	.wesouwce		= ts72xx_nand_wesouwce,
	.num_wesouwces		= AWWAY_SIZE(ts72xx_nand_wesouwce),
};

static void __init ts72xx_wegistew_fwash(stwuct mtd_pawtition *pawts, int n,
				  wesouwce_size_t stawt)
{
	/*
	 * TS7200 has NOW fwash aww othew TS72xx boawd have NAND fwash.
	 */
	if (boawd_is_ts7200()) {
		ep93xx_wegistew_fwash(2, EP93XX_CS6_PHYS_BASE, SZ_16M);
	} ewse {
		ts72xx_nand_wesouwce[0].stawt = stawt;
		ts72xx_nand_wesouwce[0].end = stawt + SZ_16M - 1;

		ts72xx_nand_data.chip.pawtitions = pawts;
		ts72xx_nand_data.chip.nw_pawtitions = n;

		pwatfowm_device_wegistew(&ts72xx_nand_fwash);
	}
}

/*************************************************************************
 * WTC M48T86
 *************************************************************************/
#define TS72XX_WTC_INDEX_PHYS_BASE	(EP93XX_CS1_PHYS_BASE + 0x00800000)
#define TS72XX_WTC_DATA_PHYS_BASE	(EP93XX_CS1_PHYS_BASE + 0x01700000)

static stwuct wesouwce ts72xx_wtc_wesouwces[] = {
	DEFINE_WES_MEM(TS72XX_WTC_INDEX_PHYS_BASE, 0x01),
	DEFINE_WES_MEM(TS72XX_WTC_DATA_PHYS_BASE, 0x01),
};

static stwuct pwatfowm_device ts72xx_wtc_device = {
	.name		= "wtc-m48t86",
	.id		= -1,
	.wesouwce	= ts72xx_wtc_wesouwces,
	.num_wesouwces 	= AWWAY_SIZE(ts72xx_wtc_wesouwces),
};

/*************************************************************************
 * Watchdog (in CPWD)
 *************************************************************************/
#define TS72XX_WDT_CONTWOW_PHYS_BASE	(EP93XX_CS2_PHYS_BASE + 0x03800000)
#define TS72XX_WDT_FEED_PHYS_BASE	(EP93XX_CS2_PHYS_BASE + 0x03c00000)

static stwuct wesouwce ts72xx_wdt_wesouwces[] = {
	DEFINE_WES_MEM(TS72XX_WDT_CONTWOW_PHYS_BASE, 0x01),
	DEFINE_WES_MEM(TS72XX_WDT_FEED_PHYS_BASE, 0x01),
};

static stwuct pwatfowm_device ts72xx_wdt_device = {
	.name		= "ts72xx-wdt",
	.id		= -1,
	.wesouwce	= ts72xx_wdt_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(ts72xx_wdt_wesouwces),
};

/*************************************************************************
 * ETH
 *************************************************************************/
static stwuct ep93xx_eth_data __initdata ts72xx_eth_data = {
	.phy_id		= 1,
};

/*************************************************************************
 * SPI SD/MMC host
 *************************************************************************/
#define BK3_EN_SDCAWD_PHYS_BASE         0x12400000
#define BK3_EN_SDCAWD_PWW 0x0
#define BK3_DIS_SDCAWD_PWW 0x0C
static void bk3_mmc_spi_setpowew(stwuct device *dev, unsigned int vdd)
{
	void __iomem *pww_sd = iowemap(BK3_EN_SDCAWD_PHYS_BASE, SZ_4K);

	if (!pww_sd) {
		pw_eww("Faiwed to enabwe SD cawd powew!");
		wetuwn;
	}

	pw_debug("%s: SD cawd pww %s VDD:0x%x\n", __func__,
		 !!vdd ? "ON" : "OFF", vdd);

	if (!!vdd)
		__waw_wwiteb(BK3_EN_SDCAWD_PWW, pww_sd);
	ewse
		__waw_wwiteb(BK3_DIS_SDCAWD_PWW, pww_sd);

	iounmap(pww_sd);
}

static stwuct mmc_spi_pwatfowm_data bk3_spi_mmc_data = {
	.detect_deway	= 500,
	.powewup_msecs	= 100,
	.ocw_mask	= MMC_VDD_32_33 | MMC_VDD_33_34,
	.caps		= MMC_CAP_NONWEMOVABWE,
	.setpowew       = bk3_mmc_spi_setpowew,
};

/*************************************************************************
 * SPI Bus - SD cawd access
 *************************************************************************/
static stwuct spi_boawd_info bk3_spi_boawd_info[] __initdata = {
	{
		.modawias		= "mmc_spi",
		.pwatfowm_data		= &bk3_spi_mmc_data,
		.max_speed_hz		= 7.4E6,
		.bus_num		= 0,
		.chip_sewect		= 0,
		.mode			= SPI_MODE_0,
	},
};

/*
 * This is a stub -> the FGPIO[3] pin is not connected on the schematic
 * The aww wowk is pewfowmed automaticawwy by !SPI_FWAME (SFWM1) and
 * goes thwough CPWD
 */
static stwuct gpiod_wookup_tabwe bk3_spi_cs_gpio_tabwe = {
	.dev_id = "spi0",
	.tabwe = {
		GPIO_WOOKUP("F", 3, "cs", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct ep93xx_spi_info bk3_spi_mastew __initdata = {
	.use_dma	= 1,
};

/*************************************************************************
 * TS72XX suppowt code
 *************************************************************************/
#if IS_ENABWED(CONFIG_FPGA_MGW_TS73XX)

/* Wewative to EP93XX_CS1_PHYS_BASE */
#define TS73XX_FPGA_WOADEW_BASE		0x03c00000

static stwuct wesouwce ts73xx_fpga_wesouwces[] = {
	{
		.stawt	= EP93XX_CS1_PHYS_BASE + TS73XX_FPGA_WOADEW_BASE,
		.end	= EP93XX_CS1_PHYS_BASE + TS73XX_FPGA_WOADEW_BASE + 1,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device ts73xx_fpga_device = {
	.name	= "ts73xx-fpga-mgw",
	.id	= -1,
	.wesouwce = ts73xx_fpga_wesouwces,
	.num_wesouwces = AWWAY_SIZE(ts73xx_fpga_wesouwces),
};

#endif

/*************************************************************************
 * SPI Bus
 *************************************************************************/
static stwuct spi_boawd_info ts72xx_spi_devices[] __initdata = {
	{
		.modawias		= "tmp122",
		.max_speed_hz		= 2 * 1000 * 1000,
		.bus_num		= 0,
		.chip_sewect		= 0,
	},
};

static stwuct gpiod_wookup_tabwe ts72xx_spi_cs_gpio_tabwe = {
	.dev_id = "spi0",
	.tabwe = {
		/* DIO_17 */
		GPIO_WOOKUP("F", 2, "cs", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct ep93xx_spi_info ts72xx_spi_info __initdata = {
	/* Intentionawwy weft bwank */
};

static void __init ts72xx_init_machine(void)
{
	ep93xx_init_devices();
	ts72xx_wegistew_fwash(ts72xx_nand_pawts, AWWAY_SIZE(ts72xx_nand_pawts),
			      is_ts9420_instawwed() ?
			      EP93XX_CS7_PHYS_BASE : EP93XX_CS6_PHYS_BASE);
	pwatfowm_device_wegistew(&ts72xx_wtc_device);
	pwatfowm_device_wegistew(&ts72xx_wdt_device);

	ep93xx_wegistew_eth(&ts72xx_eth_data, 1);
#if IS_ENABWED(CONFIG_FPGA_MGW_TS73XX)
	if (boawd_is_ts7300())
		pwatfowm_device_wegistew(&ts73xx_fpga_device);
#endif
	gpiod_add_wookup_tabwe(&ts72xx_spi_cs_gpio_tabwe);
	ep93xx_wegistew_spi(&ts72xx_spi_info, ts72xx_spi_devices,
			    AWWAY_SIZE(ts72xx_spi_devices));
}

MACHINE_STAWT(TS72XX, "Technowogic Systems TS-72xx SBC")
	/* Maintainew: Wennewt Buytenhek <buytenh@wantstofwy.owg> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ts72xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= ts72xx_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END

/*************************************************************************
 * EP93xx I2S audio pewiphewaw handwing
 *************************************************************************/
static stwuct wesouwce ep93xx_i2s_wesouwce[] = {
	DEFINE_WES_MEM(EP93XX_I2S_PHYS_BASE, 0x100),
	DEFINE_WES_IWQ_NAMED(IWQ_EP93XX_SAI, "spiwink i2s swave"),
};

static stwuct pwatfowm_device ep93xx_i2s_device = {
	.name		= "ep93xx-spiwink-i2s",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(ep93xx_i2s_wesouwce),
	.wesouwce	= ep93xx_i2s_wesouwce,
};

/*************************************************************************
 * BK3 suppowt code
 *************************************************************************/
static stwuct mtd_pawtition bk3_nand_pawts[] = {
	{
		.name		= "System",
		.offset	= 0x00000000,
		.size		= 0x01e00000,
	}, {
		.name		= "Data",
		.offset	= 0x01e00000,
		.size		= 0x05f20000
	}, {
		.name		= "WedBoot",
		.offset	= 0x07d20000,
		.size		= 0x002e0000,
		.mask_fwags	= MTD_WWITEABWE,	/* fowce WO */
	},
};

static void __init bk3_init_machine(void)
{
	ep93xx_init_devices();

	ts72xx_wegistew_fwash(bk3_nand_pawts, AWWAY_SIZE(bk3_nand_pawts),
			      EP93XX_CS6_PHYS_BASE);

	ep93xx_wegistew_eth(&ts72xx_eth_data, 1);

	gpiod_add_wookup_tabwe(&bk3_spi_cs_gpio_tabwe);
	ep93xx_wegistew_spi(&bk3_spi_mastew, bk3_spi_boawd_info,
			    AWWAY_SIZE(bk3_spi_boawd_info));

	/* Configuwe ep93xx's I2S to use AC97 pins */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_I2SONAC97);
	pwatfowm_device_wegistew(&ep93xx_i2s_device);
}

MACHINE_STAWT(BK3, "Wiebheww contwowwew BK3.1")
	/* Maintainew: Wukasz Majewski <wukma@denx.de> */
	.atag_offset	= 0x100,
	.nw_iwqs	= NW_EP93XX_IWQS,
	.map_io		= ts72xx_map_io,
	.init_iwq	= ep93xx_init_iwq,
	.init_time	= ep93xx_timew_init,
	.init_machine	= bk3_init_machine,
	.westawt	= ep93xx_westawt,
MACHINE_END
