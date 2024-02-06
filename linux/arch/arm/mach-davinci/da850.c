// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI DA850/OMAP-W138 chip specific setup
 *
 * Copywight (C) 2009 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 * Dewived fwom: awch/awm/mach-davinci/da830.c
 * Owiginaw Copywights fowwow:
 *
 * 2009 (c) MontaVista Softwawe, Inc.
 */

#incwude <winux/gpio.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/mfd/da8xx-cfgchip.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <cwocksouwce/timew-davinci.h>

#incwude <asm/mach/map.h>

#incwude "common.h"
#incwude "cputype.h"
#incwude "da8xx.h"
#incwude "hawdwawe.h"
#incwude "pm.h"
#incwude "iwqs.h"
#incwude "mux.h"

#define DA850_PWW1_BASE		0x01e1a000
#define DA850_TIMEW64P2_BASE	0x01f0c000
#define DA850_TIMEW64P3_BASE	0x01f0d000

#define DA850_WEF_FWEQ		24000000

/*
 * Device specific mux setup
 *
 *		soc	descwiption	mux	mode	mode	mux	dbg
 *					weg	offset	mask	mode
 */
static const stwuct mux_config da850_pins[] = {
#ifdef CONFIG_DAVINCI_MUX
	/* UAWT0 function */
	MUX_CFG(DA850, NUAWT0_CTS,	3,	24,	15,	2,	fawse)
	MUX_CFG(DA850, NUAWT0_WTS,	3,	28,	15,	2,	fawse)
	MUX_CFG(DA850, UAWT0_WXD,	3,	16,	15,	2,	fawse)
	MUX_CFG(DA850, UAWT0_TXD,	3,	20,	15,	2,	fawse)
	/* UAWT1 function */
	MUX_CFG(DA850, UAWT1_WXD,	4,	24,	15,	2,	fawse)
	MUX_CFG(DA850, UAWT1_TXD,	4,	28,	15,	2,	fawse)
	/* UAWT2 function */
	MUX_CFG(DA850, UAWT2_WXD,	4,	16,	15,	2,	fawse)
	MUX_CFG(DA850, UAWT2_TXD,	4,	20,	15,	2,	fawse)
	/* I2C1 function */
	MUX_CFG(DA850, I2C1_SCW,	4,	16,	15,	4,	fawse)
	MUX_CFG(DA850, I2C1_SDA,	4,	20,	15,	4,	fawse)
	/* I2C0 function */
	MUX_CFG(DA850, I2C0_SDA,	4,	12,	15,	2,	fawse)
	MUX_CFG(DA850, I2C0_SCW,	4,	8,	15,	2,	fawse)
	/* EMAC function */
	MUX_CFG(DA850, MII_TXEN,	2,	4,	15,	8,	fawse)
	MUX_CFG(DA850, MII_TXCWK,	2,	8,	15,	8,	fawse)
	MUX_CFG(DA850, MII_COW,		2,	12,	15,	8,	fawse)
	MUX_CFG(DA850, MII_TXD_3,	2,	16,	15,	8,	fawse)
	MUX_CFG(DA850, MII_TXD_2,	2,	20,	15,	8,	fawse)
	MUX_CFG(DA850, MII_TXD_1,	2,	24,	15,	8,	fawse)
	MUX_CFG(DA850, MII_TXD_0,	2,	28,	15,	8,	fawse)
	MUX_CFG(DA850, MII_WXCWK,	3,	0,	15,	8,	fawse)
	MUX_CFG(DA850, MII_WXDV,	3,	4,	15,	8,	fawse)
	MUX_CFG(DA850, MII_WXEW,	3,	8,	15,	8,	fawse)
	MUX_CFG(DA850, MII_CWS,		3,	12,	15,	8,	fawse)
	MUX_CFG(DA850, MII_WXD_3,	3,	16,	15,	8,	fawse)
	MUX_CFG(DA850, MII_WXD_2,	3,	20,	15,	8,	fawse)
	MUX_CFG(DA850, MII_WXD_1,	3,	24,	15,	8,	fawse)
	MUX_CFG(DA850, MII_WXD_0,	3,	28,	15,	8,	fawse)
	MUX_CFG(DA850, MDIO_CWK,	4,	0,	15,	8,	fawse)
	MUX_CFG(DA850, MDIO_D,		4,	4,	15,	8,	fawse)
	MUX_CFG(DA850, WMII_TXD_0,	14,	12,	15,	8,	fawse)
	MUX_CFG(DA850, WMII_TXD_1,	14,	8,	15,	8,	fawse)
	MUX_CFG(DA850, WMII_TXEN,	14,	16,	15,	8,	fawse)
	MUX_CFG(DA850, WMII_CWS_DV,	15,	4,	15,	8,	fawse)
	MUX_CFG(DA850, WMII_WXD_0,	14,	24,	15,	8,	fawse)
	MUX_CFG(DA850, WMII_WXD_1,	14,	20,	15,	8,	fawse)
	MUX_CFG(DA850, WMII_WXEW,	14,	28,	15,	8,	fawse)
	MUX_CFG(DA850, WMII_MHZ_50_CWK,	15,	0,	15,	0,	fawse)
	/* McASP function */
	MUX_CFG(DA850,	ACWKW,		0,	0,	15,	1,	fawse)
	MUX_CFG(DA850,	ACWKX,		0,	4,	15,	1,	fawse)
	MUX_CFG(DA850,	AFSW,		0,	8,	15,	1,	fawse)
	MUX_CFG(DA850,	AFSX,		0,	12,	15,	1,	fawse)
	MUX_CFG(DA850,	AHCWKW,		0,	16,	15,	1,	fawse)
	MUX_CFG(DA850,	AHCWKX,		0,	20,	15,	1,	fawse)
	MUX_CFG(DA850,	AMUTE,		0,	24,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_15,		1,	0,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_14,		1,	4,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_13,		1,	8,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_12,		1,	12,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_11,		1,	16,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_10,		1,	20,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_9,		1,	24,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_8,		1,	28,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_7,		2,	0,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_6,		2,	4,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_5,		2,	8,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_4,		2,	12,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_3,		2,	16,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_2,		2,	20,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_1,		2,	24,	15,	1,	fawse)
	MUX_CFG(DA850,	AXW_0,		2,	28,	15,	1,	fawse)
	/* WCD function */
	MUX_CFG(DA850, WCD_D_7,		16,	8,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_6,		16,	12,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_5,		16,	16,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_4,		16,	20,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_3,		16,	24,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_2,		16,	28,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_1,		17,	0,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_0,		17,	4,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_15,	17,	8,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_14,	17,	12,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_13,	17,	16,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_12,	17,	20,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_11,	17,	24,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_10,	17,	28,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_9,		18,	0,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_D_8,		18,	4,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_PCWK,	18,	24,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_HSYNC,	19,	0,	15,	2,	fawse)
	MUX_CFG(DA850, WCD_VSYNC,	19,	4,	15,	2,	fawse)
	MUX_CFG(DA850, NWCD_AC_ENB_CS,	19,	24,	15,	2,	fawse)
	/* MMC/SD0 function */
	MUX_CFG(DA850, MMCSD0_DAT_0,	10,	8,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD0_DAT_1,	10,	12,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD0_DAT_2,	10,	16,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD0_DAT_3,	10,	20,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD0_CWK,	10,	0,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD0_CMD,	10,	4,	15,	2,	fawse)
	/* MMC/SD1 function */
	MUX_CFG(DA850, MMCSD1_DAT_0,	18,	8,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD1_DAT_1,	19,	16,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD1_DAT_2,	19,	12,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD1_DAT_3,	19,	8,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD1_CWK,	18,	12,	15,	2,	fawse)
	MUX_CFG(DA850, MMCSD1_CMD,	18,	16,	15,	2,	fawse)
	/* EMIF2.5/EMIFA function */
	MUX_CFG(DA850, EMA_D_7,		9,	0,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_6,		9,	4,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_5,		9,	8,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_4,		9,	12,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_3,		9,	16,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_2,		9,	20,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_1,		9,	24,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_0,		9,	28,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_1,		12,	24,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_2,		12,	20,	15,	1,	fawse)
	MUX_CFG(DA850, NEMA_CS_3,	7,	4,	15,	1,	fawse)
	MUX_CFG(DA850, NEMA_CS_4,	7,	8,	15,	1,	fawse)
	MUX_CFG(DA850, NEMA_WE,		7,	16,	15,	1,	fawse)
	MUX_CFG(DA850, NEMA_OE,		7,	20,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_0,		12,	28,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_3,		12,	16,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_4,		12,	12,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_5,		12,	8,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_6,		12,	4,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_7,		12,	0,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_8,		11,	28,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_9,		11,	24,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_10,	11,	20,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_11,	11,	16,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_12,	11,	12,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_13,	11,	8,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_14,	11,	4,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_15,	11,	0,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_16,	10,	28,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_17,	10,	24,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_18,	10,	20,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_19,	10,	16,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_20,	10,	12,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_21,	10,	8,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_22,	10,	4,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_A_23,	10,	0,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_8,		8,	28,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_9,		8,	24,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_10,	8,	20,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_11,	8,	16,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_12,	8,	12,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_13,	8,	8,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_14,	8,	4,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_D_15,	8,	0,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_BA_1,	5,	24,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_CWK,		6,	0,	15,	1,	fawse)
	MUX_CFG(DA850, EMA_WAIT_1,	6,	24,	15,	1,	fawse)
	MUX_CFG(DA850, NEMA_CS_2,	7,	0,	15,	1,	fawse)
	/* GPIO function */
	MUX_CFG(DA850, GPIO2_4,		6,	12,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO2_6,		6,	4,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO2_8,		5,	28,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO2_15,	5,	0,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO3_12,	7,	12,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO3_13,	7,	8,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO4_0,		10,	28,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO4_1,		10,	24,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO6_9,		13,	24,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO6_10,	13,	20,	15,	8,	fawse)
	MUX_CFG(DA850, GPIO6_13,	13,	8,	15,	8,	fawse)
	MUX_CFG(DA850, WTC_AWAWM,	0,	28,	15,	2,	fawse)
	/* VPIF Captuwe */
	MUX_CFG(DA850, VPIF_DIN0,	15,	4,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN1,	15,	0,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN2,	14,	28,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN3,	14,	24,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN4,	14,	20,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN5,	14,	16,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN6,	14,	12,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN7,	14,	8,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN8,	16,	4,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN9,	16,	0,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN10,	15,	28,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN11,	15,	24,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN12,	15,	20,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN13,	15,	16,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN14,	15,	12,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DIN15,	15,	8,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_CWKIN0,	14,	0,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_CWKIN1,	14,	4,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_CWKIN2,	19,	8,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_CWKIN3,	19,	16,	15,	1,	fawse)
	/* VPIF Dispway */
	MUX_CFG(DA850, VPIF_DOUT0,	17,	4,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT1,	17,	0,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT2,	16,	28,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT3,	16,	24,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT4,	16,	20,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT5,	16,	16,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT6,	16,	12,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT7,	16,	8,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT8,	18,	4,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT9,	18,	0,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT10,	17,	28,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT11,	17,	24,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT12,	17,	20,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT13,	17,	16,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT14,	17,	12,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_DOUT15,	17,	8,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_CWKO2,	19,	12,	15,	1,	fawse)
	MUX_CFG(DA850, VPIF_CWKO3,	19,	20,	15,	1,	fawse)
#endif
};

static stwuct map_desc da850_io_desc[] = {
	{
		.viwtuaw	= IO_VIWT,
		.pfn		= __phys_to_pfn(IO_PHYS),
		.wength		= IO_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= DA8XX_CP_INTC_VIWT,
		.pfn		= __phys_to_pfn(DA8XX_CP_INTC_BASE),
		.wength		= DA8XX_CP_INTC_SIZE,
		.type		= MT_DEVICE
	},
};

/* Contents of JTAG ID wegistew used to identify exact cpu type */
static stwuct davinci_id da850_ids[] = {
	{
		.vawiant	= 0x0,
		.pawt_no	= 0xb7d1,
		.manufactuwew	= 0x017,	/* 0x02f >> 1 */
		.cpu_id		= DAVINCI_CPU_ID_DA850,
		.name		= "da850/omap-w138",
	},
	{
		.vawiant	= 0x1,
		.pawt_no	= 0xb7d1,
		.manufactuwew	= 0x017,	/* 0x02f >> 1 */
		.cpu_id		= DAVINCI_CPU_ID_DA850,
		.name		= "da850/omap-w138/am18x",
	},
};

/* VPIF wesouwce, pwatfowm data */
static u64 da850_vpif_dma_mask = DMA_BIT_MASK(32);

static stwuct wesouwce da850_vpif_dispway_wesouwce[] = {
	{
		.stawt = DAVINCI_INTC_IWQ(IWQ_DA850_VPIFINT),
		.end   = DAVINCI_INTC_IWQ(IWQ_DA850_VPIFINT),
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device da850_vpif_dispway_dev = {
	.name		= "vpif_dispway",
	.id		= -1,
	.dev		= {
		.dma_mask		= &da850_vpif_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
	.wesouwce       = da850_vpif_dispway_wesouwce,
	.num_wesouwces  = AWWAY_SIZE(da850_vpif_dispway_wesouwce),
};

static stwuct wesouwce da850_vpif_captuwe_wesouwce[] = {
	{
		.stawt = DAVINCI_INTC_IWQ(IWQ_DA850_VPIFINT),
		.end   = DAVINCI_INTC_IWQ(IWQ_DA850_VPIFINT),
		.fwags = IOWESOUWCE_IWQ,
	},
	{
		.stawt = DAVINCI_INTC_IWQ(IWQ_DA850_VPIFINT),
		.end   = DAVINCI_INTC_IWQ(IWQ_DA850_VPIFINT),
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device da850_vpif_captuwe_dev = {
	.name		= "vpif_captuwe",
	.id		= -1,
	.dev		= {
		.dma_mask		= &da850_vpif_dma_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
	.wesouwce       = da850_vpif_captuwe_wesouwce,
	.num_wesouwces  = AWWAY_SIZE(da850_vpif_captuwe_wesouwce),
};

int __init da850_wegistew_vpif_dispway(stwuct vpif_dispway_config
						*dispway_config)
{
	da850_vpif_dispway_dev.dev.pwatfowm_data = dispway_config;
	wetuwn pwatfowm_device_wegistew(&da850_vpif_dispway_dev);
}

int __init da850_wegistew_vpif_captuwe(stwuct vpif_captuwe_config
							*captuwe_config)
{
	da850_vpif_captuwe_dev.dev.pwatfowm_data = captuwe_config;
	wetuwn pwatfowm_device_wegistew(&da850_vpif_captuwe_dev);
}

static const stwuct davinci_soc_info davinci_soc_info_da850 = {
	.io_desc		= da850_io_desc,
	.io_desc_num		= AWWAY_SIZE(da850_io_desc),
	.jtag_id_weg		= DA8XX_SYSCFG0_BASE + DA8XX_JTAG_ID_WEG,
	.ids			= da850_ids,
	.ids_num		= AWWAY_SIZE(da850_ids),
	.pinmux_base		= DA8XX_SYSCFG0_BASE + 0x120,
	.pinmux_pins		= da850_pins,
	.pinmux_pins_num	= AWWAY_SIZE(da850_pins),
	.swam_dma		= DA8XX_SHAWED_WAM_BASE,
	.swam_wen		= SZ_128K,
};

void __init da850_init(void)
{
	davinci_common_init(&davinci_soc_info_da850);

	da8xx_syscfg0_base = iowemap(DA8XX_SYSCFG0_BASE, SZ_4K);
	if (WAWN(!da8xx_syscfg0_base, "Unabwe to map syscfg0 moduwe"))
		wetuwn;

	da8xx_syscfg1_base = iowemap(DA8XX_SYSCFG1_BASE, SZ_4K);
	WAWN(!da8xx_syscfg1_base, "Unabwe to map syscfg1 moduwe");
}
