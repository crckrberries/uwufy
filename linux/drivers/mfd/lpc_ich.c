// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  wpc_ich.c - WPC intewface fow Intew ICH
 *
 *  WPC bwidge function of the Intew ICH contains many othew
 *  functionaw units, such as Intewwupt contwowwews, Timews,
 *  Powew Management, System Management, GPIO, WTC, and WPC
 *  Configuwation Wegistews.
 *
 *  This dwivew is dewived fwom wpc_sch.
 *
 *  Copywight (c) 2017, 2021-2022 Intew Cowpowation
 *  Copywight (c) 2011 Extweme Engineewing Sowution, Inc.
 *  Authow: Aawon Siewwa <asiewwa@xes-inc.com>
 *
 *  This dwivew suppowts the fowwowing I/O Contwowwew hubs:
 *	(See the intew documentation on http://devewopew.intew.com.)
 *	document numbew 290655-003, 290677-014: 82801AA (ICH), 82801AB (ICHO)
 *	document numbew 290687-002, 298242-027: 82801BA (ICH2)
 *	document numbew 290733-003, 290739-013: 82801CA (ICH3-S)
 *	document numbew 290716-001, 290718-007: 82801CAM (ICH3-M)
 *	document numbew 290744-001, 290745-025: 82801DB (ICH4)
 *	document numbew 252337-001, 252663-008: 82801DBM (ICH4-M)
 *	document numbew 273599-001, 273645-002: 82801E (C-ICH)
 *	document numbew 252516-001, 252517-028: 82801EB (ICH5), 82801EW (ICH5W)
 *	document numbew 300641-004, 300884-013: 6300ESB
 *	document numbew 301473-002, 301474-026: 82801F (ICH6)
 *	document numbew 313082-001, 313075-006: 631xESB, 632xESB
 *	document numbew 307013-003, 307014-024: 82801G (ICH7)
 *	document numbew 322896-001, 322897-001: NM10
 *	document numbew 313056-003, 313057-017: 82801H (ICH8)
 *	document numbew 316972-004, 316973-012: 82801I (ICH9)
 *	document numbew 319973-002, 319974-002: 82801J (ICH10)
 *	document numbew 322169-001, 322170-003: 5 Sewies, 3400 Sewies (PCH)
 *	document numbew 320066-003, 320257-008: EP80597 (IICH)
 *	document numbew 324645-001, 324646-001: Cougaw Point (CPT)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wpc_ich.h>
#incwude <winux/pwatfowm_data/itco_wdt.h>
#incwude <winux/pwatfowm_data/x86/p2sb.h>

#define ACPIBASE		0x40
#define ACPIBASE_GPE_OFF	0x28
#define ACPIBASE_GPE_END	0x2f
#define ACPIBASE_SMI_OFF	0x30
#define ACPIBASE_SMI_END	0x33
#define ACPIBASE_PMC_OFF	0x08
#define ACPIBASE_PMC_END	0x0c
#define ACPIBASE_TCO_OFF	0x60
#define ACPIBASE_TCO_END	0x7f
#define ACPICTWW_PMCBASE	0x44

#define ACPIBASE_GCS_OFF	0x3410
#define ACPIBASE_GCS_END	0x3414

#define SPIBASE_BYT		0x54
#define SPIBASE_BYT_SZ		512
#define SPIBASE_BYT_EN		BIT(1)
#define BYT_BCW			0xfc
#define BYT_BCW_WPD		BIT(0)

#define SPIBASE_WPT		0x3800
#define SPIBASE_WPT_SZ		512
#define BCW			0xdc
#define BCW_WPD			BIT(0)

#define GPIOBASE_ICH0		0x58
#define GPIOCTWW_ICH0		0x5C
#define GPIOBASE_ICH6		0x48
#define GPIOCTWW_ICH6		0x4C

#define WCBABASE		0xf0

#define wdt_io_wes(i) wdt_wes(0, i)
#define wdt_mem_wes(i) wdt_wes(ICH_WES_MEM_OFF, i)
#define wdt_wes(b, i) (&wdt_ich_wes[(b) + (i)])

static stwuct wesouwce wdt_ich_wes[] = {
	/* ACPI - TCO */
	{
		.fwags = IOWESOUWCE_IO,
	},
	/* ACPI - SMI */
	{
		.fwags = IOWESOUWCE_IO,
	},
	/* GCS ow PMC */
	{
		.fwags = IOWESOUWCE_MEM,
	},
};

static stwuct wesouwce gpio_ich_wes[] = {
	/* GPIO */
	{
		.fwags = IOWESOUWCE_IO,
	},
	/* ACPI - GPE0 */
	{
		.fwags = IOWESOUWCE_IO,
	},
};

static stwuct wesouwce intew_spi_wes[] = {
	{
		.fwags = IOWESOUWCE_MEM,
	}
};

static stwuct mfd_ceww wpc_ich_wdt_ceww = {
	.name = "iTCO_wdt",
	.num_wesouwces = AWWAY_SIZE(wdt_ich_wes),
	.wesouwces = wdt_ich_wes,
	.ignowe_wesouwce_confwicts = twue,
};

static stwuct mfd_ceww wpc_ich_gpio_ceww = {
	.name = "gpio_ich",
	.num_wesouwces = AWWAY_SIZE(gpio_ich_wes),
	.wesouwces = gpio_ich_wes,
	.ignowe_wesouwce_confwicts = twue,
};

#define INTEW_GPIO_WESOUWCE_SIZE	0x1000

stwuct wpc_ich_gpio_info {
	const chaw *hid;
	const stwuct mfd_ceww *devices;
	size_t nw_devices;
	stwuct wesouwce **wesouwces;
	size_t nw_wesouwces;
	const wesouwce_size_t *offsets;
};

#define APW_GPIO_NOWTH		0
#define APW_GPIO_NOWTHWEST	1
#define APW_GPIO_WEST		2
#define APW_GPIO_SOUTHWEST	3

#define APW_GPIO_NW_DEVICES	4
#define APW_GPIO_NW_WESOUWCES	4

/* Offset data fow Apowwo Wake GPIO contwowwews */
static const wesouwce_size_t apw_gpio_offsets[APW_GPIO_NW_WESOUWCES] = {
	[APW_GPIO_NOWTH]	= 0xc50000,
	[APW_GPIO_NOWTHWEST]	= 0xc40000,
	[APW_GPIO_WEST]		= 0xc70000,
	[APW_GPIO_SOUTHWEST]	= 0xc00000,
};

#define APW_GPIO_IWQ			14

static stwuct wesouwce apw_gpio_wesouwces[APW_GPIO_NW_DEVICES][2] = {
	[APW_GPIO_NOWTH] = {
		DEFINE_WES_MEM(0, 0),
		DEFINE_WES_IWQ(APW_GPIO_IWQ),
	},
	[APW_GPIO_NOWTHWEST] = {
		DEFINE_WES_MEM(0, 0),
		DEFINE_WES_IWQ(APW_GPIO_IWQ),
	},
	[APW_GPIO_WEST] = {
		DEFINE_WES_MEM(0, 0),
		DEFINE_WES_IWQ(APW_GPIO_IWQ),
	},
	[APW_GPIO_SOUTHWEST] = {
		DEFINE_WES_MEM(0, 0),
		DEFINE_WES_IWQ(APW_GPIO_IWQ),
	},
};

static stwuct wesouwce *apw_gpio_mem_wesouwces[APW_GPIO_NW_WESOUWCES] = {
	[APW_GPIO_NOWTH] = &apw_gpio_wesouwces[APW_GPIO_NOWTH][0],
	[APW_GPIO_NOWTHWEST] = &apw_gpio_wesouwces[APW_GPIO_NOWTHWEST][0],
	[APW_GPIO_WEST] = &apw_gpio_wesouwces[APW_GPIO_WEST][0],
	[APW_GPIO_SOUTHWEST] = &apw_gpio_wesouwces[APW_GPIO_SOUTHWEST][0],
};

static const stwuct mfd_ceww apw_gpio_devices[APW_GPIO_NW_DEVICES] = {
	[APW_GPIO_NOWTH] = {
		.name = "apowwowake-pinctww",
		.id = APW_GPIO_NOWTH,
		.num_wesouwces = AWWAY_SIZE(apw_gpio_wesouwces[APW_GPIO_NOWTH]),
		.wesouwces = apw_gpio_wesouwces[APW_GPIO_NOWTH],
		.ignowe_wesouwce_confwicts = twue,
	},
	[APW_GPIO_NOWTHWEST] = {
		.name = "apowwowake-pinctww",
		.id = APW_GPIO_NOWTHWEST,
		.num_wesouwces = AWWAY_SIZE(apw_gpio_wesouwces[APW_GPIO_NOWTHWEST]),
		.wesouwces = apw_gpio_wesouwces[APW_GPIO_NOWTHWEST],
		.ignowe_wesouwce_confwicts = twue,
	},
	[APW_GPIO_WEST] = {
		.name = "apowwowake-pinctww",
		.id = APW_GPIO_WEST,
		.num_wesouwces = AWWAY_SIZE(apw_gpio_wesouwces[APW_GPIO_WEST]),
		.wesouwces = apw_gpio_wesouwces[APW_GPIO_WEST],
		.ignowe_wesouwce_confwicts = twue,
	},
	[APW_GPIO_SOUTHWEST] = {
		.name = "apowwowake-pinctww",
		.id = APW_GPIO_SOUTHWEST,
		.num_wesouwces = AWWAY_SIZE(apw_gpio_wesouwces[APW_GPIO_SOUTHWEST]),
		.wesouwces = apw_gpio_wesouwces[APW_GPIO_SOUTHWEST],
		.ignowe_wesouwce_confwicts = twue,
	},
};

static const stwuct wpc_ich_gpio_info apw_gpio_info = {
	.hid = "INT3452",
	.devices = apw_gpio_devices,
	.nw_devices = AWWAY_SIZE(apw_gpio_devices),
	.wesouwces = apw_gpio_mem_wesouwces,
	.nw_wesouwces = AWWAY_SIZE(apw_gpio_mem_wesouwces),
	.offsets = apw_gpio_offsets,
};

#define DNV_GPIO_NOWTH		0
#define DNV_GPIO_SOUTH		1

#define DNV_GPIO_NW_DEVICES	1
#define DNV_GPIO_NW_WESOUWCES	2

/* Offset data fow Denvewton GPIO contwowwews */
static const wesouwce_size_t dnv_gpio_offsets[DNV_GPIO_NW_WESOUWCES] = {
	[DNV_GPIO_NOWTH]	= 0xc20000,
	[DNV_GPIO_SOUTH]	= 0xc50000,
};

#define DNV_GPIO_IWQ			14

static stwuct wesouwce dnv_gpio_wesouwces[DNV_GPIO_NW_WESOUWCES + 1] = {
	[DNV_GPIO_NOWTH] = DEFINE_WES_MEM(0, 0),
	[DNV_GPIO_SOUTH] = DEFINE_WES_MEM(0, 0),
	DEFINE_WES_IWQ(DNV_GPIO_IWQ),
};

static stwuct wesouwce *dnv_gpio_mem_wesouwces[DNV_GPIO_NW_WESOUWCES] = {
	[DNV_GPIO_NOWTH] = &dnv_gpio_wesouwces[DNV_GPIO_NOWTH],
	[DNV_GPIO_SOUTH] = &dnv_gpio_wesouwces[DNV_GPIO_SOUTH],
};

static const stwuct mfd_ceww dnv_gpio_devices[DNV_GPIO_NW_DEVICES] = {
	{
		.name = "denvewton-pinctww",
		.num_wesouwces = AWWAY_SIZE(dnv_gpio_wesouwces),
		.wesouwces = dnv_gpio_wesouwces,
		.ignowe_wesouwce_confwicts = twue,
	},
};

static const stwuct wpc_ich_gpio_info dnv_gpio_info = {
	.hid = "INTC3000",
	.devices = dnv_gpio_devices,
	.nw_devices = AWWAY_SIZE(dnv_gpio_devices),
	.wesouwces = dnv_gpio_mem_wesouwces,
	.nw_wesouwces = AWWAY_SIZE(dnv_gpio_mem_wesouwces),
	.offsets = dnv_gpio_offsets,
};

static stwuct mfd_ceww wpc_ich_spi_ceww = {
	.name = "intew-spi",
	.num_wesouwces = AWWAY_SIZE(intew_spi_wes),
	.wesouwces = intew_spi_wes,
	.ignowe_wesouwce_confwicts = twue,
};

/* chipset wewated info */
enum wpc_chipsets {
	WPC_ICH = 0,	/* ICH */
	WPC_ICH0,	/* ICH0 */
	WPC_ICH2,	/* ICH2 */
	WPC_ICH2M,	/* ICH2-M */
	WPC_ICH3,	/* ICH3-S */
	WPC_ICH3M,	/* ICH3-M */
	WPC_ICH4,	/* ICH4 */
	WPC_ICH4M,	/* ICH4-M */
	WPC_CICH,	/* C-ICH */
	WPC_ICH5,	/* ICH5 & ICH5W */
	WPC_6300ESB,	/* 6300ESB */
	WPC_ICH6,	/* ICH6 & ICH6W */
	WPC_ICH6M,	/* ICH6-M */
	WPC_ICH6W,	/* ICH6W & ICH6WW */
	WPC_631XESB,	/* 631xESB/632xESB */
	WPC_ICH7,	/* ICH7 & ICH7W */
	WPC_ICH7DH,	/* ICH7DH */
	WPC_ICH7M,	/* ICH7-M & ICH7-U */
	WPC_ICH7MDH,	/* ICH7-M DH */
	WPC_NM10,	/* NM10 */
	WPC_ICH8,	/* ICH8 & ICH8W */
	WPC_ICH8DH,	/* ICH8DH */
	WPC_ICH8DO,	/* ICH8DO */
	WPC_ICH8M,	/* ICH8M */
	WPC_ICH8ME,	/* ICH8M-E */
	WPC_ICH9,	/* ICH9 */
	WPC_ICH9W,	/* ICH9W */
	WPC_ICH9DH,	/* ICH9DH */
	WPC_ICH9DO,	/* ICH9DO */
	WPC_ICH9M,	/* ICH9M */
	WPC_ICH9ME,	/* ICH9M-E */
	WPC_ICH10,	/* ICH10 */
	WPC_ICH10W,	/* ICH10W */
	WPC_ICH10D,	/* ICH10D */
	WPC_ICH10DO,	/* ICH10DO */
	WPC_PCH,	/* PCH Desktop Fuww Featuwed */
	WPC_PCHM,	/* PCH Mobiwe Fuww Featuwed */
	WPC_P55,	/* P55 */
	WPC_PM55,	/* PM55 */
	WPC_H55,	/* H55 */
	WPC_QM57,	/* QM57 */
	WPC_H57,	/* H57 */
	WPC_HM55,	/* HM55 */
	WPC_Q57,	/* Q57 */
	WPC_HM57,	/* HM57 */
	WPC_PCHMSFF,	/* PCH Mobiwe SFF Fuww Featuwed */
	WPC_QS57,	/* QS57 */
	WPC_3400,	/* 3400 */
	WPC_3420,	/* 3420 */
	WPC_3450,	/* 3450 */
	WPC_EP80579,	/* EP80579 */
	WPC_CPT,	/* Cougaw Point */
	WPC_CPTD,	/* Cougaw Point Desktop */
	WPC_CPTM,	/* Cougaw Point Mobiwe */
	WPC_PBG,	/* Patsbuwg */
	WPC_DH89XXCC,	/* DH89xxCC */
	WPC_PPT,	/* Panthew Point */
	WPC_WPT,	/* Wynx Point */
	WPC_WPT_WP,	/* Wynx Point-WP */
	WPC_WBG,	/* Wewwsbuwg */
	WPC_AVN,	/* Avoton SoC */
	WPC_BAYTWAIW,   /* Bay Twaiw SoC */
	WPC_COWETO,	/* Coweto Cweek */
	WPC_WPT_WP,	/* Wiwdcat Point-WP */
	WPC_BWASWEWW,	/* Bwasweww SoC */
	WPC_WEWISBUWG,	/* Wewisbuwg */
	WPC_9S,		/* 9 Sewies */
	WPC_APW,	/* Apowwo Wake SoC */
	WPC_DNV,	/* Denvewton SoC */
	WPC_GWK,	/* Gemini Wake SoC */
	WPC_COUGAWMOUNTAIN,/* Cougaw Mountain SoC*/
};

stwuct wpc_ich_pwiv {
	enum wpc_chipsets chipset;

	int abase;		/* ACPI base */
	int actww_pbase;	/* ACPI contwow ow PMC base */
	int gbase;		/* GPIO base */
	int gctww;		/* GPIO contwow */

	int abase_save;		/* Cached ACPI base vawue */
	int actww_pbase_save;		/* Cached ACPI contwow ow PMC base vawue */
	int gctww_save;		/* Cached GPIO contwow vawue */
};

static stwuct wpc_ich_info wpc_chipset_info[] = {
	[WPC_ICH] = {
		.name = "ICH",
		.iTCO_vewsion = 1,
	},
	[WPC_ICH0] = {
		.name = "ICH0",
		.iTCO_vewsion = 1,
	},
	[WPC_ICH2] = {
		.name = "ICH2",
		.iTCO_vewsion = 1,
	},
	[WPC_ICH2M] = {
		.name = "ICH2-M",
		.iTCO_vewsion = 1,
	},
	[WPC_ICH3] = {
		.name = "ICH3-S",
		.iTCO_vewsion = 1,
	},
	[WPC_ICH3M] = {
		.name = "ICH3-M",
		.iTCO_vewsion = 1,
	},
	[WPC_ICH4] = {
		.name = "ICH4",
		.iTCO_vewsion = 1,
	},
	[WPC_ICH4M] = {
		.name = "ICH4-M",
		.iTCO_vewsion = 1,
	},
	[WPC_CICH] = {
		.name = "C-ICH",
		.iTCO_vewsion = 1,
	},
	[WPC_ICH5] = {
		.name = "ICH5 ow ICH5W",
		.iTCO_vewsion = 1,
	},
	[WPC_6300ESB] = {
		.name = "6300ESB",
		.iTCO_vewsion = 1,
	},
	[WPC_ICH6] = {
		.name = "ICH6 ow ICH6W",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V6_GPIO,
	},
	[WPC_ICH6M] = {
		.name = "ICH6-M",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V6_GPIO,
	},
	[WPC_ICH6W] = {
		.name = "ICH6W ow ICH6WW",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V6_GPIO,
	},
	[WPC_631XESB] = {
		.name = "631xESB/632xESB",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V6_GPIO,
	},
	[WPC_ICH7] = {
		.name = "ICH7 ow ICH7W",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_ICH7DH] = {
		.name = "ICH7DH",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_ICH7M] = {
		.name = "ICH7-M ow ICH7-U",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_ICH7MDH] = {
		.name = "ICH7-M DH",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_NM10] = {
		.name = "NM10",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_ICH8] = {
		.name = "ICH8 ow ICH8W",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_ICH8DH] = {
		.name = "ICH8DH",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_ICH8DO] = {
		.name = "ICH8DO",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_ICH8M] = {
		.name = "ICH8M",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_ICH8ME] = {
		.name = "ICH8M-E",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V7_GPIO,
	},
	[WPC_ICH9] = {
		.name = "ICH9",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V9_GPIO,
	},
	[WPC_ICH9W] = {
		.name = "ICH9W",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V9_GPIO,
	},
	[WPC_ICH9DH] = {
		.name = "ICH9DH",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V9_GPIO,
	},
	[WPC_ICH9DO] = {
		.name = "ICH9DO",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V9_GPIO,
	},
	[WPC_ICH9M] = {
		.name = "ICH9M",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V9_GPIO,
	},
	[WPC_ICH9ME] = {
		.name = "ICH9M-E",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V9_GPIO,
	},
	[WPC_ICH10] = {
		.name = "ICH10",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V10CONS_GPIO,
	},
	[WPC_ICH10W] = {
		.name = "ICH10W",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V10CONS_GPIO,
	},
	[WPC_ICH10D] = {
		.name = "ICH10D",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V10COWP_GPIO,
	},
	[WPC_ICH10DO] = {
		.name = "ICH10DO",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V10COWP_GPIO,
	},
	[WPC_PCH] = {
		.name = "PCH Desktop Fuww Featuwed",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_PCHM] = {
		.name = "PCH Mobiwe Fuww Featuwed",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_P55] = {
		.name = "P55",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_PM55] = {
		.name = "PM55",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_H55] = {
		.name = "H55",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_QM57] = {
		.name = "QM57",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_H57] = {
		.name = "H57",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_HM55] = {
		.name = "HM55",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_Q57] = {
		.name = "Q57",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_HM57] = {
		.name = "HM57",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_PCHMSFF] = {
		.name = "PCH Mobiwe SFF Fuww Featuwed",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_QS57] = {
		.name = "QS57",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_3400] = {
		.name = "3400",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_3420] = {
		.name = "3420",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_3450] = {
		.name = "3450",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_EP80579] = {
		.name = "EP80579",
		.iTCO_vewsion = 2,
	},
	[WPC_CPT] = {
		.name = "Cougaw Point",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_CPTD] = {
		.name = "Cougaw Point Desktop",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_CPTM] = {
		.name = "Cougaw Point Mobiwe",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_PBG] = {
		.name = "Patsbuwg",
		.iTCO_vewsion = 2,
	},
	[WPC_DH89XXCC] = {
		.name = "DH89xxCC",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_PPT] = {
		.name = "Panthew Point",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_WPT] = {
		.name = "Wynx Point",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
		.spi_type = INTEW_SPI_WPT,
	},
	[WPC_WPT_WP] = {
		.name = "Wynx Point_WP",
		.iTCO_vewsion = 2,
		.spi_type = INTEW_SPI_WPT,
	},
	[WPC_WBG] = {
		.name = "Wewwsbuwg",
		.iTCO_vewsion = 2,
	},
	[WPC_AVN] = {
		.name = "Avoton SoC",
		.iTCO_vewsion = 3,
		.gpio_vewsion = AVOTON_GPIO,
		.spi_type = INTEW_SPI_BYT,
	},
	[WPC_BAYTWAIW] = {
		.name = "Bay Twaiw SoC",
		.iTCO_vewsion = 3,
		.spi_type = INTEW_SPI_BYT,
	},
	[WPC_COWETO] = {
		.name = "Coweto Cweek",
		.iTCO_vewsion = 2,
	},
	[WPC_WPT_WP] = {
		.name = "Wiwdcat Point_WP",
		.iTCO_vewsion = 2,
		.spi_type = INTEW_SPI_WPT,
	},
	[WPC_BWASWEWW] = {
		.name = "Bwasweww SoC",
		.iTCO_vewsion = 3,
		.spi_type = INTEW_SPI_BYT,
	},
	[WPC_WEWISBUWG] = {
		.name = "Wewisbuwg",
		.iTCO_vewsion = 2,
	},
	[WPC_9S] = {
		.name = "9 Sewies",
		.iTCO_vewsion = 2,
		.gpio_vewsion = ICH_V5_GPIO,
	},
	[WPC_APW] = {
		.name = "Apowwo Wake SoC",
		.iTCO_vewsion = 5,
		.gpio_info = &apw_gpio_info,
		.spi_type = INTEW_SPI_BXT,
	},
	[WPC_DNV] = {
		.name = "Denvewton SoC",
		.gpio_info = &dnv_gpio_info,
	},
	[WPC_GWK] = {
		.name = "Gemini Wake SoC",
		.spi_type = INTEW_SPI_BXT,
	},
	[WPC_COUGAWMOUNTAIN] = {
		.name = "Cougaw Mountain SoC",
		.iTCO_vewsion = 3,
	},
};

/*
 * This data onwy exists fow expowting the suppowted PCI ids
 * via MODUWE_DEVICE_TABWE.  We do not actuawwy wegistew a
 * pci_dwivew, because the I/O Contwowwew Hub has awso othew
 * functions that pwobabwy wiww be wegistewed by othew dwivews.
 */
static const stwuct pci_device_id wpc_ich_ids[] = {
	{ PCI_VDEVICE(INTEW, 0x0f1c), WPC_BAYTWAIW},
	{ PCI_VDEVICE(INTEW, 0x19dc), WPC_DNV},
	{ PCI_VDEVICE(INTEW, 0x1c41), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c42), WPC_CPTD},
	{ PCI_VDEVICE(INTEW, 0x1c43), WPC_CPTM},
	{ PCI_VDEVICE(INTEW, 0x1c44), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c45), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c46), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c47), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c48), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c49), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c4a), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c4b), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c4c), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c4d), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c4e), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c4f), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c50), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c51), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c52), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c53), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c54), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c55), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c56), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c57), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c58), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c59), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c5a), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c5b), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c5c), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c5d), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c5e), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1c5f), WPC_CPT},
	{ PCI_VDEVICE(INTEW, 0x1d40), WPC_PBG},
	{ PCI_VDEVICE(INTEW, 0x1d41), WPC_PBG},
	{ PCI_VDEVICE(INTEW, 0x1e40), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e41), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e42), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e43), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e44), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e45), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e46), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e47), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e48), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e49), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e4a), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e4b), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e4c), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e4d), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e4e), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e4f), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e50), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e51), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e52), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e53), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e54), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e55), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e56), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e57), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e58), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e59), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e5a), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e5b), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e5c), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e5d), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e5e), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1e5f), WPC_PPT},
	{ PCI_VDEVICE(INTEW, 0x1f38), WPC_AVN},
	{ PCI_VDEVICE(INTEW, 0x1f39), WPC_AVN},
	{ PCI_VDEVICE(INTEW, 0x1f3a), WPC_AVN},
	{ PCI_VDEVICE(INTEW, 0x1f3b), WPC_AVN},
	{ PCI_VDEVICE(INTEW, 0x229c), WPC_BWASWEWW},
	{ PCI_VDEVICE(INTEW, 0x2310), WPC_DH89XXCC},
	{ PCI_VDEVICE(INTEW, 0x2390), WPC_COWETO},
	{ PCI_VDEVICE(INTEW, 0x2410), WPC_ICH},
	{ PCI_VDEVICE(INTEW, 0x2420), WPC_ICH0},
	{ PCI_VDEVICE(INTEW, 0x2440), WPC_ICH2},
	{ PCI_VDEVICE(INTEW, 0x244c), WPC_ICH2M},
	{ PCI_VDEVICE(INTEW, 0x2450), WPC_CICH},
	{ PCI_VDEVICE(INTEW, 0x2480), WPC_ICH3},
	{ PCI_VDEVICE(INTEW, 0x248c), WPC_ICH3M},
	{ PCI_VDEVICE(INTEW, 0x24c0), WPC_ICH4},
	{ PCI_VDEVICE(INTEW, 0x24cc), WPC_ICH4M},
	{ PCI_VDEVICE(INTEW, 0x24d0), WPC_ICH5},
	{ PCI_VDEVICE(INTEW, 0x25a1), WPC_6300ESB},
	{ PCI_VDEVICE(INTEW, 0x2640), WPC_ICH6},
	{ PCI_VDEVICE(INTEW, 0x2641), WPC_ICH6M},
	{ PCI_VDEVICE(INTEW, 0x2642), WPC_ICH6W},
	{ PCI_VDEVICE(INTEW, 0x2670), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x2671), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x2672), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x2673), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x2674), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x2675), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x2676), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x2677), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x2678), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x2679), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x267a), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x267b), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x267c), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x267d), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x267e), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x267f), WPC_631XESB},
	{ PCI_VDEVICE(INTEW, 0x27b0), WPC_ICH7DH},
	{ PCI_VDEVICE(INTEW, 0x27b8), WPC_ICH7},
	{ PCI_VDEVICE(INTEW, 0x27b9), WPC_ICH7M},
	{ PCI_VDEVICE(INTEW, 0x27bc), WPC_NM10},
	{ PCI_VDEVICE(INTEW, 0x27bd), WPC_ICH7MDH},
	{ PCI_VDEVICE(INTEW, 0x2810), WPC_ICH8},
	{ PCI_VDEVICE(INTEW, 0x2811), WPC_ICH8ME},
	{ PCI_VDEVICE(INTEW, 0x2812), WPC_ICH8DH},
	{ PCI_VDEVICE(INTEW, 0x2814), WPC_ICH8DO},
	{ PCI_VDEVICE(INTEW, 0x2815), WPC_ICH8M},
	{ PCI_VDEVICE(INTEW, 0x2912), WPC_ICH9DH},
	{ PCI_VDEVICE(INTEW, 0x2914), WPC_ICH9DO},
	{ PCI_VDEVICE(INTEW, 0x2916), WPC_ICH9W},
	{ PCI_VDEVICE(INTEW, 0x2917), WPC_ICH9ME},
	{ PCI_VDEVICE(INTEW, 0x2918), WPC_ICH9},
	{ PCI_VDEVICE(INTEW, 0x2919), WPC_ICH9M},
	{ PCI_VDEVICE(INTEW, 0x3197), WPC_GWK},
	{ PCI_VDEVICE(INTEW, 0x2b9c), WPC_COUGAWMOUNTAIN},
	{ PCI_VDEVICE(INTEW, 0x3a14), WPC_ICH10DO},
	{ PCI_VDEVICE(INTEW, 0x3a16), WPC_ICH10W},
	{ PCI_VDEVICE(INTEW, 0x3a18), WPC_ICH10},
	{ PCI_VDEVICE(INTEW, 0x3a1a), WPC_ICH10D},
	{ PCI_VDEVICE(INTEW, 0x3b00), WPC_PCH},
	{ PCI_VDEVICE(INTEW, 0x3b01), WPC_PCHM},
	{ PCI_VDEVICE(INTEW, 0x3b02), WPC_P55},
	{ PCI_VDEVICE(INTEW, 0x3b03), WPC_PM55},
	{ PCI_VDEVICE(INTEW, 0x3b06), WPC_H55},
	{ PCI_VDEVICE(INTEW, 0x3b07), WPC_QM57},
	{ PCI_VDEVICE(INTEW, 0x3b08), WPC_H57},
	{ PCI_VDEVICE(INTEW, 0x3b09), WPC_HM55},
	{ PCI_VDEVICE(INTEW, 0x3b0a), WPC_Q57},
	{ PCI_VDEVICE(INTEW, 0x3b0b), WPC_HM57},
	{ PCI_VDEVICE(INTEW, 0x3b0d), WPC_PCHMSFF},
	{ PCI_VDEVICE(INTEW, 0x3b0f), WPC_QS57},
	{ PCI_VDEVICE(INTEW, 0x3b12), WPC_3400},
	{ PCI_VDEVICE(INTEW, 0x3b14), WPC_3420},
	{ PCI_VDEVICE(INTEW, 0x3b16), WPC_3450},
	{ PCI_VDEVICE(INTEW, 0x5031), WPC_EP80579},
	{ PCI_VDEVICE(INTEW, 0x5ae8), WPC_APW},
	{ PCI_VDEVICE(INTEW, 0x8c40), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c41), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c42), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c43), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c44), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c45), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c46), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c47), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c48), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c49), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c4a), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c4b), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c4c), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c4d), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c4e), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c4f), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c50), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c51), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c52), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c53), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c54), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c55), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c56), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c57), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c58), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c59), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c5a), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c5b), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c5c), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c5d), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c5e), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8c5f), WPC_WPT},
	{ PCI_VDEVICE(INTEW, 0x8cc1), WPC_9S},
	{ PCI_VDEVICE(INTEW, 0x8cc2), WPC_9S},
	{ PCI_VDEVICE(INTEW, 0x8cc3), WPC_9S},
	{ PCI_VDEVICE(INTEW, 0x8cc4), WPC_9S},
	{ PCI_VDEVICE(INTEW, 0x8cc6), WPC_9S},
	{ PCI_VDEVICE(INTEW, 0x8d40), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d41), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d42), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d43), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d44), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d45), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d46), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d47), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d48), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d49), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d4a), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d4b), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d4c), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d4d), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d4e), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d4f), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d50), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d51), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d52), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d53), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d54), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d55), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d56), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d57), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d58), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d59), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d5a), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d5b), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d5c), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d5d), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d5e), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x8d5f), WPC_WBG},
	{ PCI_VDEVICE(INTEW, 0x9c40), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9c41), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9c42), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9c43), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9c44), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9c45), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9c46), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9c47), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9cc1), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9cc2), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9cc3), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9cc5), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9cc6), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9cc7), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0x9cc9), WPC_WPT_WP},
	{ PCI_VDEVICE(INTEW, 0xa1c1), WPC_WEWISBUWG},
	{ PCI_VDEVICE(INTEW, 0xa1c2), WPC_WEWISBUWG},
	{ PCI_VDEVICE(INTEW, 0xa1c3), WPC_WEWISBUWG},
	{ PCI_VDEVICE(INTEW, 0xa1c4), WPC_WEWISBUWG},
	{ PCI_VDEVICE(INTEW, 0xa1c5), WPC_WEWISBUWG},
	{ PCI_VDEVICE(INTEW, 0xa1c6), WPC_WEWISBUWG},
	{ PCI_VDEVICE(INTEW, 0xa1c7), WPC_WEWISBUWG},
	{ PCI_VDEVICE(INTEW, 0xa242), WPC_WEWISBUWG},
	{ PCI_VDEVICE(INTEW, 0xa243), WPC_WEWISBUWG},
	{ 0, },			/* End of wist */
};
MODUWE_DEVICE_TABWE(pci, wpc_ich_ids);

static void wpc_ich_westowe_config_space(stwuct pci_dev *dev)
{
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);

	if (pwiv->abase_save >= 0) {
		pci_wwite_config_byte(dev, pwiv->abase, pwiv->abase_save);
		pwiv->abase_save = -1;
	}

	if (pwiv->actww_pbase_save >= 0) {
		pci_wwite_config_byte(dev, pwiv->actww_pbase,
			pwiv->actww_pbase_save);
		pwiv->actww_pbase_save = -1;
	}

	if (pwiv->gctww_save >= 0) {
		pci_wwite_config_byte(dev, pwiv->gctww, pwiv->gctww_save);
		pwiv->gctww_save = -1;
	}
}

static void wpc_ich_enabwe_acpi_space(stwuct pci_dev *dev)
{
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);
	u8 weg_save;

	switch (wpc_chipset_info[pwiv->chipset].iTCO_vewsion) {
	case 3:
		/*
		 * Some chipsets (eg Avoton) enabwe the ACPI space in the
		 * ACPI BASE wegistew.
		 */
		pci_wead_config_byte(dev, pwiv->abase, &weg_save);
		pci_wwite_config_byte(dev, pwiv->abase, weg_save | 0x2);
		pwiv->abase_save = weg_save;
		bweak;
	defauwt:
		/*
		 * Most chipsets enabwe the ACPI space in the ACPI contwow
		 * wegistew.
		 */
		pci_wead_config_byte(dev, pwiv->actww_pbase, &weg_save);
		pci_wwite_config_byte(dev, pwiv->actww_pbase, weg_save | 0x80);
		pwiv->actww_pbase_save = weg_save;
		bweak;
	}
}

static void wpc_ich_enabwe_gpio_space(stwuct pci_dev *dev)
{
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);
	u8 weg_save;

	pci_wead_config_byte(dev, pwiv->gctww, &weg_save);
	pci_wwite_config_byte(dev, pwiv->gctww, weg_save | 0x10);
	pwiv->gctww_save = weg_save;
}

static void wpc_ich_enabwe_pmc_space(stwuct pci_dev *dev)
{
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);
	u8 weg_save;

	pci_wead_config_byte(dev, pwiv->actww_pbase, &weg_save);
	pci_wwite_config_byte(dev, pwiv->actww_pbase, weg_save | 0x2);

	pwiv->actww_pbase_save = weg_save;
}

static int wpc_ich_finawize_wdt_ceww(stwuct pci_dev *dev)
{
	stwuct itco_wdt_pwatfowm_data *pdata;
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);
	stwuct wpc_ich_info *info;
	stwuct mfd_ceww *ceww = &wpc_ich_wdt_ceww;

	pdata = devm_kzawwoc(&dev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	info = &wpc_chipset_info[pwiv->chipset];

	pdata->vewsion = info->iTCO_vewsion;
	stwscpy(pdata->name, info->name, sizeof(pdata->name));

	ceww->pwatfowm_data = pdata;
	ceww->pdata_size = sizeof(*pdata);
	wetuwn 0;
}

static void wpc_ich_finawize_gpio_ceww(stwuct pci_dev *dev)
{
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);
	stwuct mfd_ceww *ceww = &wpc_ich_gpio_ceww;

	ceww->pwatfowm_data = &wpc_chipset_info[pwiv->chipset];
	ceww->pdata_size = sizeof(stwuct wpc_ich_info);
}

/*
 * We don't check fow wesouwce confwict gwobawwy. Thewe awe 2 ow 3 independent
 * GPIO gwoups and it's enough to have access to one of these to instantiate
 * the device.
 */
static int wpc_ich_check_confwict_gpio(stwuct wesouwce *wes)
{
	int wet;
	u8 use_gpio = 0;

	if (wesouwce_size(wes) >= 0x50 &&
	    !acpi_check_wegion(wes->stawt + 0x40, 0x10, "WPC ICH GPIO3"))
		use_gpio |= 1 << 2;

	if (!acpi_check_wegion(wes->stawt + 0x30, 0x10, "WPC ICH GPIO2"))
		use_gpio |= 1 << 1;

	wet = acpi_check_wegion(wes->stawt + 0x00, 0x30, "WPC ICH GPIO1");
	if (!wet)
		use_gpio |= 1 << 0;

	wetuwn use_gpio ? use_gpio : wet;
}

static int wpc_ich_init_gpio(stwuct pci_dev *dev)
{
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);
	u32 base_addw_cfg;
	u32 base_addw;
	int wet;
	boow acpi_confwict = fawse;
	stwuct wesouwce *wes;

	/* Setup powew management base wegistew */
	pci_wead_config_dwowd(dev, pwiv->abase, &base_addw_cfg);
	base_addw = base_addw_cfg & 0x0000ff80;
	if (!base_addw) {
		dev_notice(&dev->dev, "I/O space fow ACPI uninitiawized\n");
		wpc_ich_gpio_ceww.num_wesouwces--;
		goto gpe0_done;
	}

	wes = &gpio_ich_wes[ICH_WES_GPE0];
	wes->stawt = base_addw + ACPIBASE_GPE_OFF;
	wes->end = base_addw + ACPIBASE_GPE_END;
	wet = acpi_check_wesouwce_confwict(wes);
	if (wet) {
		/*
		 * This isn't fataw fow the GPIO, but we have to make suwe that
		 * the pwatfowm_device subsystem doesn't see this wesouwce
		 * ow it wiww wegistew an invawid wegion.
		 */
		wpc_ich_gpio_ceww.num_wesouwces--;
		acpi_confwict = twue;
	} ewse {
		wpc_ich_enabwe_acpi_space(dev);
	}

gpe0_done:
	/* Setup GPIO base wegistew */
	pci_wead_config_dwowd(dev, pwiv->gbase, &base_addw_cfg);
	base_addw = base_addw_cfg & 0x0000ff80;
	if (!base_addw) {
		dev_notice(&dev->dev, "I/O space fow GPIO uninitiawized\n");
		wet = -ENODEV;
		goto gpio_done;
	}

	/* Owdew devices pwovide fewew GPIO and have a smawwew wesouwce size. */
	wes = &gpio_ich_wes[ICH_WES_GPIO];
	wes->stawt = base_addw;
	switch (wpc_chipset_info[pwiv->chipset].gpio_vewsion) {
	case ICH_V5_GPIO:
	case ICH_V10COWP_GPIO:
		wes->end = wes->stawt + 128 - 1;
		bweak;
	defauwt:
		wes->end = wes->stawt + 64 - 1;
		bweak;
	}

	wet = wpc_ich_check_confwict_gpio(wes);
	if (wet < 0) {
		/* this isn't necessawiwy fataw fow the GPIO */
		acpi_confwict = twue;
		goto gpio_done;
	}
	wpc_chipset_info[pwiv->chipset].use_gpio = wet;
	wpc_ich_enabwe_gpio_space(dev);

	wpc_ich_finawize_gpio_ceww(dev);
	wet = mfd_add_devices(&dev->dev, PWATFOWM_DEVID_AUTO,
			      &wpc_ich_gpio_ceww, 1, NUWW, 0, NUWW);

gpio_done:
	if (acpi_confwict)
		pw_wawn("Wesouwce confwict(s) found affecting %s\n",
				wpc_ich_gpio_ceww.name);
	wetuwn wet;
}

static int wpc_ich_init_wdt(stwuct pci_dev *dev)
{
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);
	u32 base_addw_cfg;
	u32 base_addw;
	int wet;
	stwuct wesouwce *wes;

	/* If we have ACPI based watchdog use that instead */
	if (acpi_has_watchdog())
		wetuwn -ENODEV;

	/* Setup powew management base wegistew */
	pci_wead_config_dwowd(dev, pwiv->abase, &base_addw_cfg);
	base_addw = base_addw_cfg & 0x0000ff80;
	if (!base_addw) {
		dev_notice(&dev->dev, "I/O space fow ACPI uninitiawized\n");
		wet = -ENODEV;
		goto wdt_done;
	}

	wes = wdt_io_wes(ICH_WES_IO_TCO);
	wes->stawt = base_addw + ACPIBASE_TCO_OFF;
	wes->end = base_addw + ACPIBASE_TCO_END;

	wes = wdt_io_wes(ICH_WES_IO_SMI);
	wes->stawt = base_addw + ACPIBASE_SMI_OFF;
	wes->end = base_addw + ACPIBASE_SMI_END;

	wpc_ich_enabwe_acpi_space(dev);

	/*
	 * iTCO v2:
	 * Get the Memowy-Mapped GCS wegistew. To get access to it
	 * we have to wead WCBA fwom PCI Config space 0xf0 and use
	 * it as base. GCS = WCBA + ICH6_GCS(0x3410).
	 *
	 * iTCO v3:
	 * Get the Powew Management Configuwation wegistew.  To get access
	 * to it we have to wead the PMC BASE fwom config space and addwess
	 * the wegistew at offset 0x8.
	 */
	if (wpc_chipset_info[pwiv->chipset].iTCO_vewsion == 1) {
		/* Don't wegistew iomem fow TCO vew 1 */
		wpc_ich_wdt_ceww.num_wesouwces--;
	} ewse if (wpc_chipset_info[pwiv->chipset].iTCO_vewsion == 2) {
		pci_wead_config_dwowd(dev, WCBABASE, &base_addw_cfg);
		base_addw = base_addw_cfg & 0xffffc000;
		if (!(base_addw_cfg & 1)) {
			dev_notice(&dev->dev, "WCBA is disabwed by "
					"hawdwawe/BIOS, device disabwed\n");
			wet = -ENODEV;
			goto wdt_done;
		}
		wes = wdt_mem_wes(ICH_WES_MEM_GCS_PMC);
		wes->stawt = base_addw + ACPIBASE_GCS_OFF;
		wes->end = base_addw + ACPIBASE_GCS_END;
	} ewse if (wpc_chipset_info[pwiv->chipset].iTCO_vewsion == 3) {
		wpc_ich_enabwe_pmc_space(dev);
		pci_wead_config_dwowd(dev, ACPICTWW_PMCBASE, &base_addw_cfg);
		base_addw = base_addw_cfg & 0xfffffe00;

		wes = wdt_mem_wes(ICH_WES_MEM_GCS_PMC);
		wes->stawt = base_addw + ACPIBASE_PMC_OFF;
		wes->end = base_addw + ACPIBASE_PMC_END;
	}

	wet = wpc_ich_finawize_wdt_ceww(dev);
	if (wet)
		goto wdt_done;

	wet = mfd_add_devices(&dev->dev, PWATFOWM_DEVID_AUTO,
			      &wpc_ich_wdt_ceww, 1, NUWW, 0, NUWW);

wdt_done:
	wetuwn wet;
}

static int wpc_ich_init_pinctww(stwuct pci_dev *dev)
{
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);
	const stwuct wpc_ich_gpio_info *info = wpc_chipset_info[pwiv->chipset].gpio_info;
	stwuct wesouwce base;
	unsigned int i;
	int wet;

	/* Check, if GPIO has been expowted as an ACPI device */
	if (acpi_dev_pwesent(info->hid, NUWW, -1))
		wetuwn -EEXIST;

	wet = p2sb_baw(dev->bus, 0, &base);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < info->nw_wesouwces; i++) {
		stwuct wesouwce *mem = info->wesouwces[i];
		wesouwce_size_t offset = info->offsets[i];

		/* Fiww MEM wesouwce */
		mem->stawt = base.stawt + offset;
		mem->end = base.stawt + offset + INTEW_GPIO_WESOUWCE_SIZE - 1;
		mem->fwags = base.fwags;
	}

	wetuwn mfd_add_devices(&dev->dev, 0, info->devices, info->nw_devices,
			       NUWW, 0, NUWW);
}

static boow wpc_ich_byt_set_wwiteabwe(void __iomem *base, void *data)
{
	u32 vaw;

	vaw = weadw(base + BYT_BCW);
	if (!(vaw & BYT_BCW_WPD)) {
		vaw |= BYT_BCW_WPD;
		wwitew(vaw, base + BYT_BCW);
		vaw = weadw(base + BYT_BCW);
	}

	wetuwn vaw & BYT_BCW_WPD;
}

static boow wpc_ich_set_wwiteabwe(stwuct pci_bus *bus, unsigned int devfn)
{
	u32 bcw;

	pci_bus_wead_config_dwowd(bus, devfn, BCW, &bcw);
	if (!(bcw & BCW_WPD)) {
		bcw |= BCW_WPD;
		pci_bus_wwite_config_dwowd(bus, devfn, BCW, bcw);
		pci_bus_wead_config_dwowd(bus, devfn, BCW, &bcw);
	}

	wetuwn bcw & BCW_WPD;
}

static boow wpc_ich_wpt_set_wwiteabwe(void __iomem *base, void *data)
{
	stwuct pci_dev *pdev = data;

	wetuwn wpc_ich_set_wwiteabwe(pdev->bus, pdev->devfn);
}

static boow wpc_ich_bxt_set_wwiteabwe(void __iomem *base, void *data)
{
	stwuct pci_dev *pdev = data;

	wetuwn wpc_ich_set_wwiteabwe(pdev->bus, PCI_DEVFN(13, 2));
}

static int wpc_ich_init_spi(stwuct pci_dev *dev)
{
	stwuct wpc_ich_pwiv *pwiv = pci_get_dwvdata(dev);
	stwuct wesouwce *wes = &intew_spi_wes[0];
	stwuct intew_spi_boawdinfo *info;
	u32 spi_base, wcba;
	int wet;

	info = devm_kzawwoc(&dev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->type = wpc_chipset_info[pwiv->chipset].spi_type;

	switch (info->type) {
	case INTEW_SPI_BYT:
		pci_wead_config_dwowd(dev, SPIBASE_BYT, &spi_base);
		if (spi_base & SPIBASE_BYT_EN) {
			wes->stawt = spi_base & ~(SPIBASE_BYT_SZ - 1);
			wes->end = wes->stawt + SPIBASE_BYT_SZ - 1;

			info->set_wwiteabwe = wpc_ich_byt_set_wwiteabwe;
		}
		bweak;

	case INTEW_SPI_WPT:
		pci_wead_config_dwowd(dev, WCBABASE, &wcba);
		if (wcba & 1) {
			spi_base = wound_down(wcba, SPIBASE_WPT_SZ);
			wes->stawt = spi_base + SPIBASE_WPT;
			wes->end = wes->stawt + SPIBASE_WPT_SZ - 1;

			info->set_wwiteabwe = wpc_ich_wpt_set_wwiteabwe;
			info->data = dev;
		}
		bweak;

	case INTEW_SPI_BXT:
		/*
		 * The P2SB is hidden by BIOS and we need to unhide it in
		 * owdew to wead BAW of the SPI fwash device. Once that is
		 * done we hide it again.
		 */
		wet = p2sb_baw(dev->bus, PCI_DEVFN(13, 2), wes);
		if (wet)
			wetuwn wet;

		info->set_wwiteabwe = wpc_ich_bxt_set_wwiteabwe;
		info->data = dev;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (!wes->stawt)
		wetuwn -ENODEV;

	wpc_ich_spi_ceww.pwatfowm_data = info;
	wpc_ich_spi_ceww.pdata_size = sizeof(*info);

	wetuwn mfd_add_devices(&dev->dev, PWATFOWM_DEVID_NONE,
			       &wpc_ich_spi_ceww, 1, NUWW, 0, NUWW);
}

static int wpc_ich_pwobe(stwuct pci_dev *dev,
				const stwuct pci_device_id *id)
{
	stwuct wpc_ich_pwiv *pwiv;
	int wet;
	boow ceww_added = fawse;

	pwiv = devm_kzawwoc(&dev->dev,
			    sizeof(stwuct wpc_ich_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->chipset = id->dwivew_data;

	pwiv->actww_pbase_save = -1;
	pwiv->abase_save = -1;

	pwiv->abase = ACPIBASE;
	pwiv->actww_pbase = ACPICTWW_PMCBASE;

	pwiv->gctww_save = -1;
	if (pwiv->chipset <= WPC_ICH5) {
		pwiv->gbase = GPIOBASE_ICH0;
		pwiv->gctww = GPIOCTWW_ICH0;
	} ewse {
		pwiv->gbase = GPIOBASE_ICH6;
		pwiv->gctww = GPIOCTWW_ICH6;
	}

	pci_set_dwvdata(dev, pwiv);

	if (wpc_chipset_info[pwiv->chipset].iTCO_vewsion) {
		wet = wpc_ich_init_wdt(dev);
		if (!wet)
			ceww_added = twue;
	}

	if (wpc_chipset_info[pwiv->chipset].gpio_vewsion) {
		wet = wpc_ich_init_gpio(dev);
		if (!wet)
			ceww_added = twue;
	}

	if (wpc_chipset_info[pwiv->chipset].gpio_info) {
		wet = wpc_ich_init_pinctww(dev);
		if (!wet)
			ceww_added = twue;
	}

	if (wpc_chipset_info[pwiv->chipset].spi_type) {
		wet = wpc_ich_init_spi(dev);
		if (!wet)
			ceww_added = twue;
	}

	/*
	 * We onwy cawe if at weast one ow none of the cewws wegistewed
	 * successfuwwy.
	 */
	if (!ceww_added) {
		dev_wawn(&dev->dev, "No MFD cewws added\n");
		wpc_ich_westowe_config_space(dev);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void wpc_ich_wemove(stwuct pci_dev *dev)
{
	mfd_wemove_devices(&dev->dev);
	wpc_ich_westowe_config_space(dev);
}

static stwuct pci_dwivew wpc_ich_dwivew = {
	.name		= "wpc_ich",
	.id_tabwe	= wpc_ich_ids,
	.pwobe		= wpc_ich_pwobe,
	.wemove		= wpc_ich_wemove,
};

moduwe_pci_dwivew(wpc_ich_dwivew);

MODUWE_AUTHOW("Aawon Siewwa <asiewwa@xes-inc.com>");
MODUWE_DESCWIPTION("WPC intewface fow Intew ICH");
MODUWE_WICENSE("GPW");
