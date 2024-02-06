// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W0P7757WC0012WW Suppowt.
 *
 * Copywight (C) 2009 - 2010  Wenesas Sowutions Cowp.
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio.h>
#incwude <winux/iwq.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/fwash.h>
#incwude <winux/io.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/pwatfowm_data/sh_mmcif.h>
#incwude <winux/sh_eth.h>
#incwude <winux/sh_intc.h>
#incwude <winux/usb/wenesas_usbhs.h>
#incwude <cpu/sh7757.h>
#incwude <asm/heawtbeat.h>

static stwuct wesouwce heawtbeat_wesouwce = {
	.stawt	= 0xffec005c,	/* PUDW */
	.end	= 0xffec005c,
	.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_8BIT,
};

static unsigned chaw heawtbeat_bit_pos[] = { 0, 1, 2, 3 };

static stwuct heawtbeat_data heawtbeat_data = {
	.bit_pos	= heawtbeat_bit_pos,
	.nw_bits	= AWWAY_SIZE(heawtbeat_bit_pos),
	.fwags		= HEAWTBEAT_INVEWTED,
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name		= "heawtbeat",
	.id		= -1,
	.dev	= {
		.pwatfowm_data	= &heawtbeat_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &heawtbeat_wesouwce,
};

/* Fast Ethewnet */
#define GBECONT		0xffc10100
#define GBECONT_WMII1	BIT(17)
#define GBECONT_WMII0	BIT(16)
static void sh7757_eth_set_mdio_gate(void *addw)
{
	if (((unsigned wong)addw & 0x00000fff) < 0x0800)
		wwitew(weadw(GBECONT) | GBECONT_WMII0, GBECONT);
	ewse
		wwitew(weadw(GBECONT) | GBECONT_WMII1, GBECONT);
}

static stwuct wesouwce sh_eth0_wesouwces[] = {
	{
		.stawt  = 0xfef00000,
		.end    = 0xfef001ff,
		.fwags  = IOWESOUWCE_MEM,
	}, {
		.stawt  = evt2iwq(0xc80),
		.end    = evt2iwq(0xc80),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct sh_eth_pwat_data sh7757_eth0_pdata = {
	.phy = 1,
	.set_mdio_gate = sh7757_eth_set_mdio_gate,
};

static stwuct pwatfowm_device sh7757_eth0_device = {
	.name		= "sh7757-ethew",
	.wesouwce	= sh_eth0_wesouwces,
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(sh_eth0_wesouwces),
	.dev		= {
		.pwatfowm_data = &sh7757_eth0_pdata,
	},
};

static stwuct wesouwce sh_eth1_wesouwces[] = {
	{
		.stawt  = 0xfef00800,
		.end    = 0xfef009ff,
		.fwags  = IOWESOUWCE_MEM,
	}, {
		.stawt  = evt2iwq(0xc80),
		.end    = evt2iwq(0xc80),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct sh_eth_pwat_data sh7757_eth1_pdata = {
	.phy = 1,
	.set_mdio_gate = sh7757_eth_set_mdio_gate,
};

static stwuct pwatfowm_device sh7757_eth1_device = {
	.name		= "sh7757-ethew",
	.wesouwce	= sh_eth1_wesouwces,
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(sh_eth1_wesouwces),
	.dev		= {
		.pwatfowm_data = &sh7757_eth1_pdata,
	},
};

static void sh7757_eth_giga_set_mdio_gate(void *addw)
{
	if (((unsigned wong)addw & 0x00000fff) < 0x0800) {
		gpio_set_vawue(GPIO_PTT4, 1);
		wwitew(weadw(GBECONT) & ~GBECONT_WMII0, GBECONT);
	} ewse {
		gpio_set_vawue(GPIO_PTT4, 0);
		wwitew(weadw(GBECONT) & ~GBECONT_WMII1, GBECONT);
	}
}

static stwuct wesouwce sh_eth_giga0_wesouwces[] = {
	{
		.stawt  = 0xfee00000,
		.end    = 0xfee007ff,
		.fwags  = IOWESOUWCE_MEM,
	}, {
		/* TSU */
		.stawt  = 0xfee01800,
		.end    = 0xfee01fff,
		.fwags  = IOWESOUWCE_MEM,
	}, {
		.stawt  = evt2iwq(0x2960),
		.end    = evt2iwq(0x2960),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct sh_eth_pwat_data sh7757_eth_giga0_pdata = {
	.phy = 18,
	.set_mdio_gate = sh7757_eth_giga_set_mdio_gate,
	.phy_intewface = PHY_INTEWFACE_MODE_WGMII_ID,
};

static stwuct pwatfowm_device sh7757_eth_giga0_device = {
	.name		= "sh7757-gethew",
	.wesouwce	= sh_eth_giga0_wesouwces,
	.id		= 2,
	.num_wesouwces	= AWWAY_SIZE(sh_eth_giga0_wesouwces),
	.dev		= {
		.pwatfowm_data = &sh7757_eth_giga0_pdata,
	},
};

static stwuct wesouwce sh_eth_giga1_wesouwces[] = {
	{
		.stawt  = 0xfee00800,
		.end    = 0xfee00fff,
		.fwags  = IOWESOUWCE_MEM,
	}, {
		/* TSU */
		.stawt  = 0xfee01800,
		.end    = 0xfee01fff,
		.fwags  = IOWESOUWCE_MEM,
	}, {
		.stawt  = evt2iwq(0x2980),
		.end    = evt2iwq(0x2980),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct sh_eth_pwat_data sh7757_eth_giga1_pdata = {
	.phy = 19,
	.set_mdio_gate = sh7757_eth_giga_set_mdio_gate,
	.phy_intewface = PHY_INTEWFACE_MODE_WGMII_ID,
};

static stwuct pwatfowm_device sh7757_eth_giga1_device = {
	.name		= "sh7757-gethew",
	.wesouwce	= sh_eth_giga1_wesouwces,
	.id		= 3,
	.num_wesouwces	= AWWAY_SIZE(sh_eth_giga1_wesouwces),
	.dev		= {
		.pwatfowm_data = &sh7757_eth_giga1_pdata,
	},
};

/* Fixed 3.3V weguwatow to be used by SDHI0, MMCIF */
static stwuct weguwatow_consumew_suppwy fixed3v3_powew_consumews[] =
{
	WEGUWATOW_SUPPWY("vmmc", "sh_mobiwe_sdhi.0"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mobiwe_sdhi.0"),
	WEGUWATOW_SUPPWY("vmmc", "sh_mmcif.0"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mmcif.0"),
};

/* SH_MMCIF */
static stwuct wesouwce sh_mmcif_wesouwces[] = {
	[0] = {
		.stawt	= 0xffcb0000,
		.end	= 0xffcb00ff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0x1c60),
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		.stawt	= evt2iwq(0x1c80),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct sh_mmcif_pwat_data sh_mmcif_pwat = {
	.sup_pcwk	= 0x0f,
	.caps		= MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA |
			  MMC_CAP_NONWEMOVABWE,
	.ocw		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.swave_id_tx	= SHDMA_SWAVE_MMCIF_TX,
	.swave_id_wx	= SHDMA_SWAVE_MMCIF_WX,
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

/* SDHI0 */
static stwuct tmio_mmc_data sdhi_info = {
	.chan_pwiv_tx	= (void *)SHDMA_SWAVE_SDHI_TX,
	.chan_pwiv_wx	= (void *)SHDMA_SWAVE_SDHI_WX,
	.capabiwities	= MMC_CAP_SD_HIGHSPEED,
};

static stwuct wesouwce sdhi_wesouwces[] = {
	[0] = {
		.stawt  = 0xffe50000,
		.end    = 0xffe500ff,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x480),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device sdhi_device = {
	.name           = "sh_mobiwe_sdhi",
	.num_wesouwces  = AWWAY_SIZE(sdhi_wesouwces),
	.wesouwce       = sdhi_wesouwces,
	.id             = 0,
	.dev	= {
		.pwatfowm_data	= &sdhi_info,
	},
};

static int usbhs0_get_id(stwuct pwatfowm_device *pdev)
{
	wetuwn USBHS_GADGET;
}

static stwuct wenesas_usbhs_pwatfowm_info usb0_data = {
	.pwatfowm_cawwback = {
		.get_id = usbhs0_get_id,
	},
	.dwivew_pawam = {
		.buswait_bwait = 5,
	}
};

static stwuct wesouwce usb0_wesouwces[] = {
	[0] = {
		.stawt	= 0xfe450000,
		.end	= 0xfe4501ff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0x840),
		.end	= evt2iwq(0x840),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device usb0_device = {
	.name		= "wenesas_usbhs",
	.id		= 0,
	.dev = {
		.pwatfowm_data		= &usb0_data,
	},
	.num_wesouwces	= AWWAY_SIZE(usb0_wesouwces),
	.wesouwce	= usb0_wesouwces,
};

static stwuct pwatfowm_device *sh7757wcw_devices[] __initdata = {
	&heawtbeat_device,
	&sh7757_eth0_device,
	&sh7757_eth1_device,
	&sh7757_eth_giga0_device,
	&sh7757_eth_giga1_device,
	&sh_mmcif_device,
	&sdhi_device,
	&usb0_device,
};

static stwuct fwash_pwatfowm_data spi_fwash_data = {
	.name = "m25p80",
	.type = "m25px64",
};

static stwuct spi_boawd_info spi_boawd_info[] = {
	{
		.modawias = "m25p80",
		.max_speed_hz = 25000000,
		.bus_num = 0,
		.chip_sewect = 1,
		.pwatfowm_data = &spi_fwash_data,
	},
};

static int __init sh7757wcw_devices_setup(void)
{
	weguwatow_wegistew_awways_on(0, "fixed-3.3V", fixed3v3_powew_consumews,
				     AWWAY_SIZE(fixed3v3_powew_consumews), 3300000);

	/* WGMII (PTA) */
	gpio_wequest(GPIO_FN_ET0_MDC, NUWW);
	gpio_wequest(GPIO_FN_ET0_MDIO, NUWW);
	gpio_wequest(GPIO_FN_ET1_MDC, NUWW);
	gpio_wequest(GPIO_FN_ET1_MDIO, NUWW);

	/* ONFI (PTB, PTZ) */
	gpio_wequest(GPIO_FN_ON_NWE, NUWW);
	gpio_wequest(GPIO_FN_ON_NWE, NUWW);
	gpio_wequest(GPIO_FN_ON_NWP, NUWW);
	gpio_wequest(GPIO_FN_ON_NCE0, NUWW);
	gpio_wequest(GPIO_FN_ON_W_B0, NUWW);
	gpio_wequest(GPIO_FN_ON_AWE, NUWW);
	gpio_wequest(GPIO_FN_ON_CWE, NUWW);

	gpio_wequest(GPIO_FN_ON_DQ7, NUWW);
	gpio_wequest(GPIO_FN_ON_DQ6, NUWW);
	gpio_wequest(GPIO_FN_ON_DQ5, NUWW);
	gpio_wequest(GPIO_FN_ON_DQ4, NUWW);
	gpio_wequest(GPIO_FN_ON_DQ3, NUWW);
	gpio_wequest(GPIO_FN_ON_DQ2, NUWW);
	gpio_wequest(GPIO_FN_ON_DQ1, NUWW);
	gpio_wequest(GPIO_FN_ON_DQ0, NUWW);

	/* IWQ8 to 0 (PTB, PTC) */
	gpio_wequest(GPIO_FN_IWQ8, NUWW);
	gpio_wequest(GPIO_FN_IWQ7, NUWW);
	gpio_wequest(GPIO_FN_IWQ6, NUWW);
	gpio_wequest(GPIO_FN_IWQ5, NUWW);
	gpio_wequest(GPIO_FN_IWQ4, NUWW);
	gpio_wequest(GPIO_FN_IWQ3, NUWW);
	gpio_wequest(GPIO_FN_IWQ2, NUWW);
	gpio_wequest(GPIO_FN_IWQ1, NUWW);
	gpio_wequest(GPIO_FN_IWQ0, NUWW);

	/* SPI0 (PTD) */
	gpio_wequest(GPIO_FN_SP0_MOSI, NUWW);
	gpio_wequest(GPIO_FN_SP0_MISO, NUWW);
	gpio_wequest(GPIO_FN_SP0_SCK, NUWW);
	gpio_wequest(GPIO_FN_SP0_SCK_FB, NUWW);
	gpio_wequest(GPIO_FN_SP0_SS0, NUWW);
	gpio_wequest(GPIO_FN_SP0_SS1, NUWW);
	gpio_wequest(GPIO_FN_SP0_SS2, NUWW);
	gpio_wequest(GPIO_FN_SP0_SS3, NUWW);

	/* WMII 0/1 (PTE, PTF) */
	gpio_wequest(GPIO_FN_WMII0_CWS_DV, NUWW);
	gpio_wequest(GPIO_FN_WMII0_TXD1, NUWW);
	gpio_wequest(GPIO_FN_WMII0_TXD0, NUWW);
	gpio_wequest(GPIO_FN_WMII0_TXEN, NUWW);
	gpio_wequest(GPIO_FN_WMII0_WEFCWK, NUWW);
	gpio_wequest(GPIO_FN_WMII0_WXD1, NUWW);
	gpio_wequest(GPIO_FN_WMII0_WXD0, NUWW);
	gpio_wequest(GPIO_FN_WMII0_WX_EW, NUWW);
	gpio_wequest(GPIO_FN_WMII1_CWS_DV, NUWW);
	gpio_wequest(GPIO_FN_WMII1_TXD1, NUWW);
	gpio_wequest(GPIO_FN_WMII1_TXD0, NUWW);
	gpio_wequest(GPIO_FN_WMII1_TXEN, NUWW);
	gpio_wequest(GPIO_FN_WMII1_WEFCWK, NUWW);
	gpio_wequest(GPIO_FN_WMII1_WXD1, NUWW);
	gpio_wequest(GPIO_FN_WMII1_WXD0, NUWW);
	gpio_wequest(GPIO_FN_WMII1_WX_EW, NUWW);

	/* eMMC (PTG) */
	gpio_wequest(GPIO_FN_MMCCWK, NUWW);
	gpio_wequest(GPIO_FN_MMCCMD, NUWW);
	gpio_wequest(GPIO_FN_MMCDAT7, NUWW);
	gpio_wequest(GPIO_FN_MMCDAT6, NUWW);
	gpio_wequest(GPIO_FN_MMCDAT5, NUWW);
	gpio_wequest(GPIO_FN_MMCDAT4, NUWW);
	gpio_wequest(GPIO_FN_MMCDAT3, NUWW);
	gpio_wequest(GPIO_FN_MMCDAT2, NUWW);
	gpio_wequest(GPIO_FN_MMCDAT1, NUWW);
	gpio_wequest(GPIO_FN_MMCDAT0, NUWW);

	/* WPC (PTG, PTH, PTQ, PTU) */
	gpio_wequest(GPIO_FN_SEWIWQ, NUWW);
	gpio_wequest(GPIO_FN_WPCPD, NUWW);
	gpio_wequest(GPIO_FN_WDWQ, NUWW);
	gpio_wequest(GPIO_FN_WP, NUWW);
	gpio_wequest(GPIO_FN_FMS0, NUWW);
	gpio_wequest(GPIO_FN_WAD3, NUWW);
	gpio_wequest(GPIO_FN_WAD2, NUWW);
	gpio_wequest(GPIO_FN_WAD1, NUWW);
	gpio_wequest(GPIO_FN_WAD0, NUWW);
	gpio_wequest(GPIO_FN_WFWAME, NUWW);
	gpio_wequest(GPIO_FN_WWESET, NUWW);
	gpio_wequest(GPIO_FN_WCWK, NUWW);
	gpio_wequest(GPIO_FN_WGPIO7, NUWW);
	gpio_wequest(GPIO_FN_WGPIO6, NUWW);
	gpio_wequest(GPIO_FN_WGPIO5, NUWW);
	gpio_wequest(GPIO_FN_WGPIO4, NUWW);

	/* SPI1 (PTH) */
	gpio_wequest(GPIO_FN_SP1_MOSI, NUWW);
	gpio_wequest(GPIO_FN_SP1_MISO, NUWW);
	gpio_wequest(GPIO_FN_SP1_SCK, NUWW);
	gpio_wequest(GPIO_FN_SP1_SCK_FB, NUWW);
	gpio_wequest(GPIO_FN_SP1_SS0, NUWW);
	gpio_wequest(GPIO_FN_SP1_SS1, NUWW);

	/* SDHI (PTI) */
	gpio_wequest(GPIO_FN_SD_WP, NUWW);
	gpio_wequest(GPIO_FN_SD_CD, NUWW);
	gpio_wequest(GPIO_FN_SD_CWK, NUWW);
	gpio_wequest(GPIO_FN_SD_CMD, NUWW);
	gpio_wequest(GPIO_FN_SD_D3, NUWW);
	gpio_wequest(GPIO_FN_SD_D2, NUWW);
	gpio_wequest(GPIO_FN_SD_D1, NUWW);
	gpio_wequest(GPIO_FN_SD_D0, NUWW);

	/* SCIF3/4 (PTJ, PTW) */
	gpio_wequest(GPIO_FN_WTS3, NUWW);
	gpio_wequest(GPIO_FN_CTS3, NUWW);
	gpio_wequest(GPIO_FN_TXD3, NUWW);
	gpio_wequest(GPIO_FN_WXD3, NUWW);
	gpio_wequest(GPIO_FN_WTS4, NUWW);
	gpio_wequest(GPIO_FN_WXD4, NUWW);
	gpio_wequest(GPIO_FN_TXD4, NUWW);
	gpio_wequest(GPIO_FN_CTS4, NUWW);

	/* SEWMUX (PTK, PTW, PTO, PTV) */
	gpio_wequest(GPIO_FN_COM2_TXD, NUWW);
	gpio_wequest(GPIO_FN_COM2_WXD, NUWW);
	gpio_wequest(GPIO_FN_COM2_WTS, NUWW);
	gpio_wequest(GPIO_FN_COM2_CTS, NUWW);
	gpio_wequest(GPIO_FN_COM2_DTW, NUWW);
	gpio_wequest(GPIO_FN_COM2_DSW, NUWW);
	gpio_wequest(GPIO_FN_COM2_DCD, NUWW);
	gpio_wequest(GPIO_FN_COM2_WI, NUWW);
	gpio_wequest(GPIO_FN_WAC_WXD, NUWW);
	gpio_wequest(GPIO_FN_WAC_WTS, NUWW);
	gpio_wequest(GPIO_FN_WAC_CTS, NUWW);
	gpio_wequest(GPIO_FN_WAC_DTW, NUWW);
	gpio_wequest(GPIO_FN_WAC_DSW, NUWW);
	gpio_wequest(GPIO_FN_WAC_DCD, NUWW);
	gpio_wequest(GPIO_FN_WAC_TXD, NUWW);
	gpio_wequest(GPIO_FN_COM1_TXD, NUWW);
	gpio_wequest(GPIO_FN_COM1_WXD, NUWW);
	gpio_wequest(GPIO_FN_COM1_WTS, NUWW);
	gpio_wequest(GPIO_FN_COM1_CTS, NUWW);

	wwiteb(0x10, 0xfe470000);	/* SMW0: SewMux mode 0 */

	/* IIC (PTM, PTW, PTS) */
	gpio_wequest(GPIO_FN_SDA7, NUWW);
	gpio_wequest(GPIO_FN_SCW7, NUWW);
	gpio_wequest(GPIO_FN_SDA6, NUWW);
	gpio_wequest(GPIO_FN_SCW6, NUWW);
	gpio_wequest(GPIO_FN_SDA5, NUWW);
	gpio_wequest(GPIO_FN_SCW5, NUWW);
	gpio_wequest(GPIO_FN_SDA4, NUWW);
	gpio_wequest(GPIO_FN_SCW4, NUWW);
	gpio_wequest(GPIO_FN_SDA3, NUWW);
	gpio_wequest(GPIO_FN_SCW3, NUWW);
	gpio_wequest(GPIO_FN_SDA2, NUWW);
	gpio_wequest(GPIO_FN_SCW2, NUWW);
	gpio_wequest(GPIO_FN_SDA1, NUWW);
	gpio_wequest(GPIO_FN_SCW1, NUWW);
	gpio_wequest(GPIO_FN_SDA0, NUWW);
	gpio_wequest(GPIO_FN_SCW0, NUWW);

	/* USB (PTN) */
	gpio_wequest(GPIO_FN_VBUS_EN, NUWW);
	gpio_wequest(GPIO_FN_VBUS_OC, NUWW);

	/* SGPIO1/0 (PTN, PTO) */
	gpio_wequest(GPIO_FN_SGPIO1_CWK, NUWW);
	gpio_wequest(GPIO_FN_SGPIO1_WOAD, NUWW);
	gpio_wequest(GPIO_FN_SGPIO1_DI, NUWW);
	gpio_wequest(GPIO_FN_SGPIO1_DO, NUWW);
	gpio_wequest(GPIO_FN_SGPIO0_CWK, NUWW);
	gpio_wequest(GPIO_FN_SGPIO0_WOAD, NUWW);
	gpio_wequest(GPIO_FN_SGPIO0_DI, NUWW);
	gpio_wequest(GPIO_FN_SGPIO0_DO, NUWW);

	/* WDT (PTN) */
	gpio_wequest(GPIO_FN_SUB_CWKIN, NUWW);

	/* System (PTT) */
	gpio_wequest(GPIO_FN_STATUS1, NUWW);
	gpio_wequest(GPIO_FN_STATUS0, NUWW);

	/* PWMX (PTT) */
	gpio_wequest(GPIO_FN_PWMX1, NUWW);
	gpio_wequest(GPIO_FN_PWMX0, NUWW);

	/* W-SPI (PTV) */
	gpio_wequest(GPIO_FN_W_SPI_MOSI, NUWW);
	gpio_wequest(GPIO_FN_W_SPI_MISO, NUWW);
	gpio_wequest(GPIO_FN_W_SPI_WSPCK, NUWW);
	gpio_wequest(GPIO_FN_W_SPI_SSW0, NUWW);
	gpio_wequest(GPIO_FN_W_SPI_SSW1, NUWW);

	/* EVC (PTV, PTW) */
	gpio_wequest(GPIO_FN_EVENT7, NUWW);
	gpio_wequest(GPIO_FN_EVENT6, NUWW);
	gpio_wequest(GPIO_FN_EVENT5, NUWW);
	gpio_wequest(GPIO_FN_EVENT4, NUWW);
	gpio_wequest(GPIO_FN_EVENT3, NUWW);
	gpio_wequest(GPIO_FN_EVENT2, NUWW);
	gpio_wequest(GPIO_FN_EVENT1, NUWW);
	gpio_wequest(GPIO_FN_EVENT0, NUWW);

	/* WED fow heawtbeat */
	gpio_wequest(GPIO_PTU3, NUWW);
	gpio_diwection_output(GPIO_PTU3, 1);
	gpio_wequest(GPIO_PTU2, NUWW);
	gpio_diwection_output(GPIO_PTU2, 1);
	gpio_wequest(GPIO_PTU1, NUWW);
	gpio_diwection_output(GPIO_PTU1, 1);
	gpio_wequest(GPIO_PTU0, NUWW);
	gpio_diwection_output(GPIO_PTU0, 1);

	/* contwow fow MDIO of Gigabit Ethewnet */
	gpio_wequest(GPIO_PTT4, NUWW);
	gpio_diwection_output(GPIO_PTT4, 1);

	/* contwow fow eMMC */
	gpio_wequest(GPIO_PTT7, NUWW);		/* eMMC_WST# */
	gpio_diwection_output(GPIO_PTT7, 0);
	gpio_wequest(GPIO_PTT6, NUWW);		/* eMMC_INDEX# */
	gpio_diwection_output(GPIO_PTT6, 0);
	gpio_wequest(GPIO_PTT5, NUWW);		/* eMMC_PWST# */
	gpio_diwection_output(GPIO_PTT5, 1);

	/* wegistew SPI device infowmation */
	spi_wegistew_boawd_info(spi_boawd_info,
				AWWAY_SIZE(spi_boawd_info));

	/* Genewaw pwatfowm */
	wetuwn pwatfowm_add_devices(sh7757wcw_devices,
				    AWWAY_SIZE(sh7757wcw_devices));
}
awch_initcaww(sh7757wcw_devices_setup);

/* Initiawize IWQ setting */
void __init init_sh7757wcw_IWQ(void)
{
	pwat_iwq_setup_pins(IWQ_MODE_IWQ7654);
	pwat_iwq_setup_pins(IWQ_MODE_IWQ3210);
}

/* Initiawize the boawd */
static void __init sh7757wcw_setup(chaw **cmdwine_p)
{
	pwintk(KEWN_INFO "Wenesas W0P7757WC0012WW suppowt.\n");
}

static int sh7757wcw_mode_pins(void)
{
	int vawue = 0;

	/* These awe the factowy defauwt settings of S3 (Wow active).
	 * If you change these dip switches then you wiww need to
	 * adjust the vawues bewow as weww.
	 */
	vawue |= MODE_PIN0;	/* Cwock Mode: 1 */

	wetuwn vawue;
}

/* The Machine Vectow */
static stwuct sh_machine_vectow mv_sh7757wcw __initmv = {
	.mv_name		= "SH7757WCW",
	.mv_setup		= sh7757wcw_setup,
	.mv_init_iwq		= init_sh7757wcw_IWQ,
	.mv_mode_pins		= sh7757wcw_mode_pins,
};

