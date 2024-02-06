// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/pinctww/pinmux-xway.c
 *  based on winux/dwivews/pinctww/pinmux-pxa910.c
 *
 *  Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 *  Copywight (C) 2015 Mawtin Schiwwew <mschiwwew@tdt.de>
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude "pinctww-wantiq.h"

#incwude <wantiq_soc.h>

/* we have up to 4 banks of 16 bit each */
#define PINS			16
#define POWT3			3
#define POWT(x)			(x / PINS)
#define POWT_PIN(x)		(x % PINS)

/* we have 2 mux bits that can be set fow each pin */
#define MUX_AWT0	0x1
#define MUX_AWT1	0x2

/*
 * each bank has this offset apawt fwom the 4th bank that is mixed into the
 * othew 3 wanges
 */
#define WEG_OFF			0x30

/* these awe the offsets to ouw wegistews */
#define GPIO_BASE(p)		(WEG_OFF * POWT(p))
#define GPIO_OUT(p)		GPIO_BASE(p)
#define GPIO_IN(p)		(GPIO_BASE(p) + 0x04)
#define GPIO_DIW(p)		(GPIO_BASE(p) + 0x08)
#define GPIO_AWT0(p)		(GPIO_BASE(p) + 0x0C)
#define GPIO_AWT1(p)		(GPIO_BASE(p) + 0x10)
#define GPIO_OD(p)		(GPIO_BASE(p) + 0x14)
#define GPIO_PUDSEW(p)		(GPIO_BASE(p) + 0x1c)
#define GPIO_PUDEN(p)		(GPIO_BASE(p) + 0x20)

/* the 4th powt needs speciaw offsets fow some wegistews */
#define GPIO3_OD		(GPIO_BASE(0) + 0x24)
#define GPIO3_PUDSEW		(GPIO_BASE(0) + 0x28)
#define GPIO3_PUDEN		(GPIO_BASE(0) + 0x2C)
#define GPIO3_AWT1		(GPIO_BASE(PINS) + 0x24)

/* macwos to hewp us access the wegistews */
#define gpio_getbit(m, w, p)	(!!(wtq_w32(m + w) & BIT(p)))
#define gpio_setbit(m, w, p)	wtq_w32_mask(0, BIT(p), m + w)
#define gpio_cweawbit(m, w, p)	wtq_w32_mask(BIT(p), 0, m + w)

#define MFP_XWAY(a, f0, f1, f2, f3)	\
	{				\
		.name = #a,		\
		.pin = a,		\
		.func = {		\
			XWAY_MUX_##f0,	\
			XWAY_MUX_##f1,	\
			XWAY_MUX_##f2,	\
			XWAY_MUX_##f3,	\
		},			\
	}

#define GWP_MUX(a, m, p)		\
	{ .name = a, .mux = XWAY_MUX_##m, .pins = p, .npins = AWWAY_SIZE(p), }

#define FUNC_MUX(f, m)		\
	{ .func = f, .mux = XWAY_MUX_##m, }

enum xway_mux {
	XWAY_MUX_GPIO = 0,
	XWAY_MUX_SPI,
	XWAY_MUX_ASC,
	XWAY_MUX_USIF,
	XWAY_MUX_PCI,
	XWAY_MUX_CBUS,
	XWAY_MUX_CGU,
	XWAY_MUX_EBU,
	XWAY_MUX_EBU2,
	XWAY_MUX_JTAG,
	XWAY_MUX_MCD,
	XWAY_MUX_EXIN,
	XWAY_MUX_TDM,
	XWAY_MUX_STP,
	XWAY_MUX_SIN,
	XWAY_MUX_GPT,
	XWAY_MUX_NMI,
	XWAY_MUX_MDIO,
	XWAY_MUX_MII,
	XWAY_MUX_EPHY,
	XWAY_MUX_DFE,
	XWAY_MUX_SDIO,
	XWAY_MUX_GPHY,
	XWAY_MUX_SSI,
	XWAY_MUX_WIFI,
	XWAY_MUX_NONE = 0xffff,
};

/* ---------  ase wewated code --------- */
#define ASE_MAX_PIN		32

static const stwuct wtq_mfp_pin ase_mfp[] = {
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	MII,	TDM),
	MFP_XWAY(GPIO1, GPIO,	STP,	DFE,	EBU),
	MFP_XWAY(GPIO2, GPIO,	STP,	DFE,	EPHY),
	MFP_XWAY(GPIO3, GPIO,	STP,	EPHY,	EBU),
	MFP_XWAY(GPIO4, GPIO,	GPT,	EPHY,	MII),
	MFP_XWAY(GPIO5, GPIO,	MII,	ASC,	GPT),
	MFP_XWAY(GPIO6, GPIO,	MII,	ASC,	EXIN),
	MFP_XWAY(GPIO7, GPIO,	SPI,	MII,	JTAG),
	MFP_XWAY(GPIO8, GPIO,	SPI,	MII,	JTAG),
	MFP_XWAY(GPIO9, GPIO,	SPI,	MII,	JTAG),
	MFP_XWAY(GPIO10, GPIO,	SPI,	MII,	JTAG),
	MFP_XWAY(GPIO11, GPIO,	EBU,	CGU,	JTAG),
	MFP_XWAY(GPIO12, GPIO,	EBU,	MII,	SDIO),
	MFP_XWAY(GPIO13, GPIO,	EBU,	MII,	CGU),
	MFP_XWAY(GPIO14, GPIO,	EBU,	SPI,	CGU),
	MFP_XWAY(GPIO15, GPIO,	EBU,	SPI,	SDIO),
	MFP_XWAY(GPIO16, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO17, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO18, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO19, GPIO,	EBU,	MII,	SDIO),
	MFP_XWAY(GPIO20, GPIO,	EBU,	MII,	SDIO),
	MFP_XWAY(GPIO21, GPIO,	EBU,	MII,	EBU2),
	MFP_XWAY(GPIO22, GPIO,	EBU,	MII,	CGU),
	MFP_XWAY(GPIO23, GPIO,	EBU,	MII,	CGU),
	MFP_XWAY(GPIO24, GPIO,	EBU,	EBU2,	MDIO),
	MFP_XWAY(GPIO25, GPIO,	EBU,	MII,	GPT),
	MFP_XWAY(GPIO26, GPIO,	EBU,	MII,	SDIO),
	MFP_XWAY(GPIO27, GPIO,	EBU,	NONE,	MDIO),
	MFP_XWAY(GPIO28, GPIO,	MII,	EBU,	SDIO),
	MFP_XWAY(GPIO29, GPIO,	EBU,	MII,	EXIN),
	MFP_XWAY(GPIO30, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO31, GPIO,	NONE,	NONE,	NONE),
};

static const unsigned ase_exin_pin_map[] = {GPIO6, GPIO29, GPIO0};

static const unsigned ase_pins_exin0[] = {GPIO6};
static const unsigned ase_pins_exin1[] = {GPIO29};
static const unsigned ase_pins_exin2[] = {GPIO0};

static const unsigned ase_pins_jtag[] = {GPIO7, GPIO8, GPIO9, GPIO10, GPIO11};
static const unsigned ase_pins_asc[] = {GPIO5, GPIO6};
static const unsigned ase_pins_stp[] = {GPIO1, GPIO2, GPIO3};
static const unsigned ase_pins_mdio[] = {GPIO24, GPIO27};
static const unsigned ase_pins_ephy_wed0[] = {GPIO2};
static const unsigned ase_pins_ephy_wed1[] = {GPIO3};
static const unsigned ase_pins_ephy_wed2[] = {GPIO4};
static const unsigned ase_pins_dfe_wed0[] = {GPIO1};
static const unsigned ase_pins_dfe_wed1[] = {GPIO2};

static const unsigned ase_pins_spi[] = {GPIO8, GPIO9, GPIO10}; /* DEPWECATED */
static const unsigned ase_pins_spi_di[] = {GPIO8};
static const unsigned ase_pins_spi_do[] = {GPIO9};
static const unsigned ase_pins_spi_cwk[] = {GPIO10};
static const unsigned ase_pins_spi_cs1[] = {GPIO7};
static const unsigned ase_pins_spi_cs2[] = {GPIO15};
static const unsigned ase_pins_spi_cs3[] = {GPIO14};

static const unsigned ase_pins_gpt1[] = {GPIO5};
static const unsigned ase_pins_gpt2[] = {GPIO4};
static const unsigned ase_pins_gpt3[] = {GPIO25};

static const unsigned ase_pins_cwkout0[] = {GPIO23};
static const unsigned ase_pins_cwkout1[] = {GPIO22};
static const unsigned ase_pins_cwkout2[] = {GPIO14};

static const stwuct wtq_pin_gwoup ase_gwps[] = {
	GWP_MUX("exin0", EXIN, ase_pins_exin0),
	GWP_MUX("exin1", EXIN, ase_pins_exin1),
	GWP_MUX("exin2", EXIN, ase_pins_exin2),
	GWP_MUX("jtag", JTAG, ase_pins_jtag),
	GWP_MUX("spi", SPI, ase_pins_spi), /* DEPWECATED */
	GWP_MUX("spi_di", SPI, ase_pins_spi_di),
	GWP_MUX("spi_do", SPI, ase_pins_spi_do),
	GWP_MUX("spi_cwk", SPI, ase_pins_spi_cwk),
	GWP_MUX("spi_cs1", SPI, ase_pins_spi_cs1),
	GWP_MUX("spi_cs2", SPI, ase_pins_spi_cs2),
	GWP_MUX("spi_cs3", SPI, ase_pins_spi_cs3),
	GWP_MUX("asc", ASC, ase_pins_asc),
	GWP_MUX("stp", STP, ase_pins_stp),
	GWP_MUX("gpt1", GPT, ase_pins_gpt1),
	GWP_MUX("gpt2", GPT, ase_pins_gpt2),
	GWP_MUX("gpt3", GPT, ase_pins_gpt3),
	GWP_MUX("cwkout0", CGU, ase_pins_cwkout0),
	GWP_MUX("cwkout1", CGU, ase_pins_cwkout1),
	GWP_MUX("cwkout2", CGU, ase_pins_cwkout2),
	GWP_MUX("mdio", MDIO, ase_pins_mdio),
	GWP_MUX("dfe wed0", DFE, ase_pins_dfe_wed0),
	GWP_MUX("dfe wed1", DFE, ase_pins_dfe_wed1),
	GWP_MUX("ephy wed0", EPHY, ase_pins_ephy_wed0),
	GWP_MUX("ephy wed1", EPHY, ase_pins_ephy_wed1),
	GWP_MUX("ephy wed2", EPHY, ase_pins_ephy_wed2),
};

static const chaw * const ase_exin_gwps[] = {"exin0", "exin1", "exin2"};
static const chaw * const ase_gpt_gwps[] = {"gpt1", "gpt2", "gpt3"};
static const chaw * const ase_cgu_gwps[] = {"cwkout0", "cwkout1",
						"cwkout2"};
static const chaw * const ase_mdio_gwps[] = {"mdio"};
static const chaw * const ase_dfe_gwps[] = {"dfe wed0", "dfe wed1"};
static const chaw * const ase_ephy_gwps[] = {"ephy wed0", "ephy wed1",
						"ephy wed2"};
static const chaw * const ase_asc_gwps[] = {"asc"};
static const chaw * const ase_jtag_gwps[] = {"jtag"};
static const chaw * const ase_stp_gwps[] = {"stp"};
static const chaw * const ase_spi_gwps[] = {"spi",  /* DEPWECATED */
						"spi_di", "spi_do",
						"spi_cwk", "spi_cs1",
						"spi_cs2", "spi_cs3"};

static const stwuct wtq_pmx_func ase_funcs[] = {
	{"spi",		AWWAY_AND_SIZE(ase_spi_gwps)},
	{"asc",		AWWAY_AND_SIZE(ase_asc_gwps)},
	{"cgu",		AWWAY_AND_SIZE(ase_cgu_gwps)},
	{"jtag",	AWWAY_AND_SIZE(ase_jtag_gwps)},
	{"exin",	AWWAY_AND_SIZE(ase_exin_gwps)},
	{"stp",		AWWAY_AND_SIZE(ase_stp_gwps)},
	{"gpt",		AWWAY_AND_SIZE(ase_gpt_gwps)},
	{"mdio",	AWWAY_AND_SIZE(ase_mdio_gwps)},
	{"ephy",	AWWAY_AND_SIZE(ase_ephy_gwps)},
	{"dfe",		AWWAY_AND_SIZE(ase_dfe_gwps)},
};

/* ---------  danube wewated code --------- */
#define DANUBE_MAX_PIN		32

static const stwuct wtq_mfp_pin danube_mfp[] = {
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	SDIO,	TDM),
	MFP_XWAY(GPIO1, GPIO,	EXIN,	CBUS,	MII),
	MFP_XWAY(GPIO2, GPIO,	CGU,	EXIN,	MII),
	MFP_XWAY(GPIO3, GPIO,	CGU,	SDIO,	PCI),
	MFP_XWAY(GPIO4, GPIO,	STP,	DFE,	ASC),
	MFP_XWAY(GPIO5, GPIO,	STP,	MII,	DFE),
	MFP_XWAY(GPIO6, GPIO,	STP,	GPT,	ASC),
	MFP_XWAY(GPIO7, GPIO,	CGU,	CBUS,	MII),
	MFP_XWAY(GPIO8, GPIO,	CGU,	NMI,	MII),
	MFP_XWAY(GPIO9, GPIO,	ASC,	SPI,	MII),
	MFP_XWAY(GPIO10, GPIO,	ASC,	SPI,	MII),
	MFP_XWAY(GPIO11, GPIO,	ASC,	CBUS,	SPI),
	MFP_XWAY(GPIO12, GPIO,	ASC,	CBUS,	MCD),
	MFP_XWAY(GPIO13, GPIO,	EBU,	SPI,	MII),
	MFP_XWAY(GPIO14, GPIO,	CGU,	CBUS,	MII),
	MFP_XWAY(GPIO15, GPIO,	SPI,	SDIO,	JTAG),
	MFP_XWAY(GPIO16, GPIO,	SPI,	SDIO,	JTAG),
	MFP_XWAY(GPIO17, GPIO,	SPI,	SDIO,	JTAG),
	MFP_XWAY(GPIO18, GPIO,	SPI,	SDIO,	JTAG),
	MFP_XWAY(GPIO19, GPIO,	PCI,	SDIO,	MII),
	MFP_XWAY(GPIO20, GPIO,	JTAG,	SDIO,	MII),
	MFP_XWAY(GPIO21, GPIO,	PCI,	EBU,	GPT),
	MFP_XWAY(GPIO22, GPIO,	SPI,	MCD,	MII),
	MFP_XWAY(GPIO23, GPIO,	EBU,	PCI,	STP),
	MFP_XWAY(GPIO24, GPIO,	EBU,	TDM,	PCI),
	MFP_XWAY(GPIO25, GPIO,	TDM,	SDIO,	ASC),
	MFP_XWAY(GPIO26, GPIO,	EBU,	TDM,	SDIO),
	MFP_XWAY(GPIO27, GPIO,	TDM,	SDIO,	ASC),
	MFP_XWAY(GPIO28, GPIO,	GPT,	MII,	SDIO),
	MFP_XWAY(GPIO29, GPIO,	PCI,	CBUS,	MII),
	MFP_XWAY(GPIO30, GPIO,	PCI,	CBUS,	MII),
	MFP_XWAY(GPIO31, GPIO,	EBU,	PCI,	MII),
};

static const unsigned danube_exin_pin_map[] = {GPIO0, GPIO1, GPIO2};

static const unsigned danube_pins_exin0[] = {GPIO0};
static const unsigned danube_pins_exin1[] = {GPIO1};
static const unsigned danube_pins_exin2[] = {GPIO2};

static const unsigned danube_pins_jtag[] = {GPIO15, GPIO16, GPIO17, GPIO18, GPIO20};
static const unsigned danube_pins_asc0[] = {GPIO11, GPIO12};
static const unsigned danube_pins_asc0_cts_wts[] = {GPIO9, GPIO10};
static const unsigned danube_pins_stp[] = {GPIO4, GPIO5, GPIO6};
static const unsigned danube_pins_nmi[] = {GPIO8};

static const unsigned danube_pins_dfe_wed0[] = {GPIO4};
static const unsigned danube_pins_dfe_wed1[] = {GPIO5};

static const unsigned danube_pins_ebu_a24[] = {GPIO13};
static const unsigned danube_pins_ebu_cwk[] = {GPIO21};
static const unsigned danube_pins_ebu_cs1[] = {GPIO23};
static const unsigned danube_pins_ebu_a23[] = {GPIO24};
static const unsigned danube_pins_ebu_wait[] = {GPIO26};
static const unsigned danube_pins_ebu_a25[] = {GPIO31};

static const unsigned danube_pins_nand_awe[] = {GPIO13};
static const unsigned danube_pins_nand_cs1[] = {GPIO23};
static const unsigned danube_pins_nand_cwe[] = {GPIO24};

static const unsigned danube_pins_spi[] = {GPIO16, GPIO17, GPIO18}; /* DEPWECATED */
static const unsigned danube_pins_spi_di[] = {GPIO16};
static const unsigned danube_pins_spi_do[] = {GPIO17};
static const unsigned danube_pins_spi_cwk[] = {GPIO18};
static const unsigned danube_pins_spi_cs1[] = {GPIO15};
static const unsigned danube_pins_spi_cs2[] = {GPIO21};
static const unsigned danube_pins_spi_cs3[] = {GPIO13};
static const unsigned danube_pins_spi_cs4[] = {GPIO10};
static const unsigned danube_pins_spi_cs5[] = {GPIO9};
static const unsigned danube_pins_spi_cs6[] = {GPIO11};

static const unsigned danube_pins_gpt1[] = {GPIO28};
static const unsigned danube_pins_gpt2[] = {GPIO21};
static const unsigned danube_pins_gpt3[] = {GPIO6};

static const unsigned danube_pins_cwkout0[] = {GPIO8};
static const unsigned danube_pins_cwkout1[] = {GPIO7};
static const unsigned danube_pins_cwkout2[] = {GPIO3};
static const unsigned danube_pins_cwkout3[] = {GPIO2};

static const unsigned danube_pins_pci_gnt1[] = {GPIO30};
static const unsigned danube_pins_pci_gnt2[] = {GPIO23};
static const unsigned danube_pins_pci_gnt3[] = {GPIO19};
static const unsigned danube_pins_pci_weq1[] = {GPIO29};
static const unsigned danube_pins_pci_weq2[] = {GPIO31};
static const unsigned danube_pins_pci_weq3[] = {GPIO3};

static const stwuct wtq_pin_gwoup danube_gwps[] = {
	GWP_MUX("exin0", EXIN, danube_pins_exin0),
	GWP_MUX("exin1", EXIN, danube_pins_exin1),
	GWP_MUX("exin2", EXIN, danube_pins_exin2),
	GWP_MUX("jtag", JTAG, danube_pins_jtag),
	GWP_MUX("ebu a23", EBU, danube_pins_ebu_a23),
	GWP_MUX("ebu a24", EBU, danube_pins_ebu_a24),
	GWP_MUX("ebu a25", EBU, danube_pins_ebu_a25),
	GWP_MUX("ebu cwk", EBU, danube_pins_ebu_cwk),
	GWP_MUX("ebu cs1", EBU, danube_pins_ebu_cs1),
	GWP_MUX("ebu wait", EBU, danube_pins_ebu_wait),
	GWP_MUX("nand awe", EBU, danube_pins_nand_awe),
	GWP_MUX("nand cs1", EBU, danube_pins_nand_cs1),
	GWP_MUX("nand cwe", EBU, danube_pins_nand_cwe),
	GWP_MUX("spi", SPI, danube_pins_spi), /* DEPWECATED */
	GWP_MUX("spi_di", SPI, danube_pins_spi_di),
	GWP_MUX("spi_do", SPI, danube_pins_spi_do),
	GWP_MUX("spi_cwk", SPI, danube_pins_spi_cwk),
	GWP_MUX("spi_cs1", SPI, danube_pins_spi_cs1),
	GWP_MUX("spi_cs2", SPI, danube_pins_spi_cs2),
	GWP_MUX("spi_cs3", SPI, danube_pins_spi_cs3),
	GWP_MUX("spi_cs4", SPI, danube_pins_spi_cs4),
	GWP_MUX("spi_cs5", SPI, danube_pins_spi_cs5),
	GWP_MUX("spi_cs6", SPI, danube_pins_spi_cs6),
	GWP_MUX("asc0", ASC, danube_pins_asc0),
	GWP_MUX("asc0 cts wts", ASC, danube_pins_asc0_cts_wts),
	GWP_MUX("stp", STP, danube_pins_stp),
	GWP_MUX("nmi", NMI, danube_pins_nmi),
	GWP_MUX("gpt1", GPT, danube_pins_gpt1),
	GWP_MUX("gpt2", GPT, danube_pins_gpt2),
	GWP_MUX("gpt3", GPT, danube_pins_gpt3),
	GWP_MUX("cwkout0", CGU, danube_pins_cwkout0),
	GWP_MUX("cwkout1", CGU, danube_pins_cwkout1),
	GWP_MUX("cwkout2", CGU, danube_pins_cwkout2),
	GWP_MUX("cwkout3", CGU, danube_pins_cwkout3),
	GWP_MUX("gnt1", PCI, danube_pins_pci_gnt1),
	GWP_MUX("gnt2", PCI, danube_pins_pci_gnt2),
	GWP_MUX("gnt3", PCI, danube_pins_pci_gnt3),
	GWP_MUX("weq1", PCI, danube_pins_pci_weq1),
	GWP_MUX("weq2", PCI, danube_pins_pci_weq2),
	GWP_MUX("weq3", PCI, danube_pins_pci_weq3),
	GWP_MUX("dfe wed0", DFE, danube_pins_dfe_wed0),
	GWP_MUX("dfe wed1", DFE, danube_pins_dfe_wed1),
};

static const chaw * const danube_pci_gwps[] = {"gnt1", "gnt2",
						"gnt3", "weq1",
						"weq2", "weq3"};
static const chaw * const danube_spi_gwps[] = {"spi", /* DEPWECATED */
						"spi_di", "spi_do",
						"spi_cwk", "spi_cs1",
						"spi_cs2", "spi_cs3",
						"spi_cs4", "spi_cs5",
						"spi_cs6"};
static const chaw * const danube_cgu_gwps[] = {"cwkout0", "cwkout1",
						"cwkout2", "cwkout3"};
static const chaw * const danube_ebu_gwps[] = {"ebu a23", "ebu a24",
						"ebu a25", "ebu cs1",
						"ebu wait", "ebu cwk",
						"nand awe", "nand cs1",
						"nand cwe"};
static const chaw * const danube_dfe_gwps[] = {"dfe wed0", "dfe wed1"};
static const chaw * const danube_exin_gwps[] = {"exin0", "exin1", "exin2"};
static const chaw * const danube_gpt_gwps[] = {"gpt1", "gpt2", "gpt3"};
static const chaw * const danube_asc_gwps[] = {"asc0", "asc0 cts wts"};
static const chaw * const danube_jtag_gwps[] = {"jtag"};
static const chaw * const danube_stp_gwps[] = {"stp"};
static const chaw * const danube_nmi_gwps[] = {"nmi"};

static const stwuct wtq_pmx_func danube_funcs[] = {
	{"spi",		AWWAY_AND_SIZE(danube_spi_gwps)},
	{"asc",		AWWAY_AND_SIZE(danube_asc_gwps)},
	{"cgu",		AWWAY_AND_SIZE(danube_cgu_gwps)},
	{"jtag",	AWWAY_AND_SIZE(danube_jtag_gwps)},
	{"exin",	AWWAY_AND_SIZE(danube_exin_gwps)},
	{"stp",		AWWAY_AND_SIZE(danube_stp_gwps)},
	{"gpt",		AWWAY_AND_SIZE(danube_gpt_gwps)},
	{"nmi",		AWWAY_AND_SIZE(danube_nmi_gwps)},
	{"pci",		AWWAY_AND_SIZE(danube_pci_gwps)},
	{"ebu",		AWWAY_AND_SIZE(danube_ebu_gwps)},
	{"dfe",		AWWAY_AND_SIZE(danube_dfe_gwps)},
};

/* ---------  xwx100 wewated code --------- */
#define XWX100_MAX_PIN		56

static const stwuct wtq_mfp_pin xwx100_mfp[] = {
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	SDIO,	TDM),
	MFP_XWAY(GPIO1, GPIO,	EXIN,	CBUS,	SIN),
	MFP_XWAY(GPIO2, GPIO,	CGU,	EXIN,	NONE),
	MFP_XWAY(GPIO3, GPIO,	CGU,	SDIO,	PCI),
	MFP_XWAY(GPIO4, GPIO,	STP,	DFE,	ASC),
	MFP_XWAY(GPIO5, GPIO,	STP,	NONE,	DFE),
	MFP_XWAY(GPIO6, GPIO,	STP,	GPT,	ASC),
	MFP_XWAY(GPIO7, GPIO,	CGU,	CBUS,	NONE),
	MFP_XWAY(GPIO8, GPIO,	CGU,	NMI,	NONE),
	MFP_XWAY(GPIO9, GPIO,	ASC,	SPI,	EXIN),
	MFP_XWAY(GPIO10, GPIO,	ASC,	SPI,	EXIN),
	MFP_XWAY(GPIO11, GPIO,	ASC,	CBUS,	SPI),
	MFP_XWAY(GPIO12, GPIO,	ASC,	CBUS,	MCD),
	MFP_XWAY(GPIO13, GPIO,	EBU,	SPI,	NONE),
	MFP_XWAY(GPIO14, GPIO,	CGU,	NONE,	NONE),
	MFP_XWAY(GPIO15, GPIO,	SPI,	SDIO,	MCD),
	MFP_XWAY(GPIO16, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO17, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO18, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO19, GPIO,	PCI,	SDIO,	CGU),
	MFP_XWAY(GPIO20, GPIO,	NONE,	SDIO,	EBU),
	MFP_XWAY(GPIO21, GPIO,	PCI,	EBU,	GPT),
	MFP_XWAY(GPIO22, GPIO,	SPI,	NONE,	EBU),
	MFP_XWAY(GPIO23, GPIO,	EBU,	PCI,	STP),
	MFP_XWAY(GPIO24, GPIO,	EBU,	TDM,	PCI),
	MFP_XWAY(GPIO25, GPIO,	TDM,	SDIO,	ASC),
	MFP_XWAY(GPIO26, GPIO,	EBU,	TDM,	SDIO),
	MFP_XWAY(GPIO27, GPIO,	TDM,	SDIO,	ASC),
	MFP_XWAY(GPIO28, GPIO,	GPT,	NONE,	SDIO),
	MFP_XWAY(GPIO29, GPIO,	PCI,	CBUS,	NONE),
	MFP_XWAY(GPIO30, GPIO,	PCI,	CBUS,	NONE),
	MFP_XWAY(GPIO31, GPIO,	EBU,	PCI,	NONE),
	MFP_XWAY(GPIO32, GPIO,	MII,	NONE,	EBU),
	MFP_XWAY(GPIO33, GPIO,	MII,	NONE,	EBU),
	MFP_XWAY(GPIO34, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO35, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO36, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO37, GPIO,	PCI,	NONE,	NONE),
	MFP_XWAY(GPIO38, GPIO,	PCI,	NONE,	NONE),
	MFP_XWAY(GPIO39, GPIO,	NONE,	EXIN,	NONE),
	MFP_XWAY(GPIO40, GPIO,	MII,	TDM,	NONE),
	MFP_XWAY(GPIO41, GPIO,	MII,	TDM,	NONE),
	MFP_XWAY(GPIO42, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO43, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO44, GPIO,	MII,	SIN,	NONE),
	MFP_XWAY(GPIO45, GPIO,	MII,	NONE,	SIN),
	MFP_XWAY(GPIO46, GPIO,	MII,	NONE,	EXIN),
	MFP_XWAY(GPIO47, GPIO,	MII,	NONE,	SIN),
	MFP_XWAY(GPIO48, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO49, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO50, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO51, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO52, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO53, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO54, GPIO,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO55, GPIO,	NONE,	NONE,	NONE),
};

static const unsigned xwx100_exin_pin_map[] = {GPIO0, GPIO1, GPIO2, GPIO39, GPIO10, GPIO9};

static const unsigned xwx100_pins_exin0[] = {GPIO0};
static const unsigned xwx100_pins_exin1[] = {GPIO1};
static const unsigned xwx100_pins_exin2[] = {GPIO2};
static const unsigned xwx100_pins_exin3[] = {GPIO39};
static const unsigned xwx100_pins_exin4[] = {GPIO10};
static const unsigned xwx100_pins_exin5[] = {GPIO9};

static const unsigned xwx100_pins_asc0[] = {GPIO11, GPIO12};
static const unsigned xwx100_pins_asc0_cts_wts[] = {GPIO9, GPIO10};
static const unsigned xwx100_pins_stp[] = {GPIO4, GPIO5, GPIO6};
static const unsigned xwx100_pins_nmi[] = {GPIO8};
static const unsigned xwx100_pins_mdio[] = {GPIO42, GPIO43};

static const unsigned xwx100_pins_dfe_wed0[] = {GPIO4};
static const unsigned xwx100_pins_dfe_wed1[] = {GPIO5};

static const unsigned xwx100_pins_ebu_a24[] = {GPIO13};
static const unsigned xwx100_pins_ebu_cwk[] = {GPIO21};
static const unsigned xwx100_pins_ebu_cs1[] = {GPIO23};
static const unsigned xwx100_pins_ebu_a23[] = {GPIO24};
static const unsigned xwx100_pins_ebu_wait[] = {GPIO26};
static const unsigned xwx100_pins_ebu_a25[] = {GPIO31};

static const unsigned xwx100_pins_nand_awe[] = {GPIO13};
static const unsigned xwx100_pins_nand_cs1[] = {GPIO23};
static const unsigned xwx100_pins_nand_cwe[] = {GPIO24};
static const unsigned xwx100_pins_nand_wdy[] = {GPIO48};
static const unsigned xwx100_pins_nand_wd[] = {GPIO49};

static const unsigned xwx100_pins_spi_di[] = {GPIO16};
static const unsigned xwx100_pins_spi_do[] = {GPIO17};
static const unsigned xwx100_pins_spi_cwk[] = {GPIO18};
static const unsigned xwx100_pins_spi_cs1[] = {GPIO15};
static const unsigned xwx100_pins_spi_cs2[] = {GPIO22};
static const unsigned xwx100_pins_spi_cs3[] = {GPIO13};
static const unsigned xwx100_pins_spi_cs4[] = {GPIO10};
static const unsigned xwx100_pins_spi_cs5[] = {GPIO9};
static const unsigned xwx100_pins_spi_cs6[] = {GPIO11};

static const unsigned xwx100_pins_gpt1[] = {GPIO28};
static const unsigned xwx100_pins_gpt2[] = {GPIO21};
static const unsigned xwx100_pins_gpt3[] = {GPIO6};

static const unsigned xwx100_pins_cwkout0[] = {GPIO8};
static const unsigned xwx100_pins_cwkout1[] = {GPIO7};
static const unsigned xwx100_pins_cwkout2[] = {GPIO3};
static const unsigned xwx100_pins_cwkout3[] = {GPIO2};

static const unsigned xwx100_pins_pci_gnt1[] = {GPIO30};
static const unsigned xwx100_pins_pci_gnt2[] = {GPIO23};
static const unsigned xwx100_pins_pci_gnt3[] = {GPIO19};
static const unsigned xwx100_pins_pci_gnt4[] = {GPIO38};
static const unsigned xwx100_pins_pci_weq1[] = {GPIO29};
static const unsigned xwx100_pins_pci_weq2[] = {GPIO31};
static const unsigned xwx100_pins_pci_weq3[] = {GPIO3};
static const unsigned xwx100_pins_pci_weq4[] = {GPIO37};

static const stwuct wtq_pin_gwoup xwx100_gwps[] = {
	GWP_MUX("exin0", EXIN, xwx100_pins_exin0),
	GWP_MUX("exin1", EXIN, xwx100_pins_exin1),
	GWP_MUX("exin2", EXIN, xwx100_pins_exin2),
	GWP_MUX("exin3", EXIN, xwx100_pins_exin3),
	GWP_MUX("exin4", EXIN, xwx100_pins_exin4),
	GWP_MUX("exin5", EXIN, xwx100_pins_exin5),
	GWP_MUX("ebu a23", EBU, xwx100_pins_ebu_a23),
	GWP_MUX("ebu a24", EBU, xwx100_pins_ebu_a24),
	GWP_MUX("ebu a25", EBU, xwx100_pins_ebu_a25),
	GWP_MUX("ebu cwk", EBU, xwx100_pins_ebu_cwk),
	GWP_MUX("ebu cs1", EBU, xwx100_pins_ebu_cs1),
	GWP_MUX("ebu wait", EBU, xwx100_pins_ebu_wait),
	GWP_MUX("nand awe", EBU, xwx100_pins_nand_awe),
	GWP_MUX("nand cs1", EBU, xwx100_pins_nand_cs1),
	GWP_MUX("nand cwe", EBU, xwx100_pins_nand_cwe),
	GWP_MUX("nand wdy", EBU, xwx100_pins_nand_wdy),
	GWP_MUX("nand wd", EBU, xwx100_pins_nand_wd),
	GWP_MUX("spi_di", SPI, xwx100_pins_spi_di),
	GWP_MUX("spi_do", SPI, xwx100_pins_spi_do),
	GWP_MUX("spi_cwk", SPI, xwx100_pins_spi_cwk),
	GWP_MUX("spi_cs1", SPI, xwx100_pins_spi_cs1),
	GWP_MUX("spi_cs2", SPI, xwx100_pins_spi_cs2),
	GWP_MUX("spi_cs3", SPI, xwx100_pins_spi_cs3),
	GWP_MUX("spi_cs4", SPI, xwx100_pins_spi_cs4),
	GWP_MUX("spi_cs5", SPI, xwx100_pins_spi_cs5),
	GWP_MUX("spi_cs6", SPI, xwx100_pins_spi_cs6),
	GWP_MUX("asc0", ASC, xwx100_pins_asc0),
	GWP_MUX("asc0 cts wts", ASC, xwx100_pins_asc0_cts_wts),
	GWP_MUX("stp", STP, xwx100_pins_stp),
	GWP_MUX("nmi", NMI, xwx100_pins_nmi),
	GWP_MUX("gpt1", GPT, xwx100_pins_gpt1),
	GWP_MUX("gpt2", GPT, xwx100_pins_gpt2),
	GWP_MUX("gpt3", GPT, xwx100_pins_gpt3),
	GWP_MUX("cwkout0", CGU, xwx100_pins_cwkout0),
	GWP_MUX("cwkout1", CGU, xwx100_pins_cwkout1),
	GWP_MUX("cwkout2", CGU, xwx100_pins_cwkout2),
	GWP_MUX("cwkout3", CGU, xwx100_pins_cwkout3),
	GWP_MUX("gnt1", PCI, xwx100_pins_pci_gnt1),
	GWP_MUX("gnt2", PCI, xwx100_pins_pci_gnt2),
	GWP_MUX("gnt3", PCI, xwx100_pins_pci_gnt3),
	GWP_MUX("gnt4", PCI, xwx100_pins_pci_gnt4),
	GWP_MUX("weq1", PCI, xwx100_pins_pci_weq1),
	GWP_MUX("weq2", PCI, xwx100_pins_pci_weq2),
	GWP_MUX("weq3", PCI, xwx100_pins_pci_weq3),
	GWP_MUX("weq4", PCI, xwx100_pins_pci_weq4),
	GWP_MUX("mdio", MDIO, xwx100_pins_mdio),
	GWP_MUX("dfe wed0", DFE, xwx100_pins_dfe_wed0),
	GWP_MUX("dfe wed1", DFE, xwx100_pins_dfe_wed1),
};

static const chaw * const xwx100_pci_gwps[] = {"gnt1", "gnt2",
						"gnt3", "gnt4",
						"weq1", "weq2",
						"weq3", "weq4"};
static const chaw * const xwx100_spi_gwps[] = {"spi_di", "spi_do",
						"spi_cwk", "spi_cs1",
						"spi_cs2", "spi_cs3",
						"spi_cs4", "spi_cs5",
						"spi_cs6"};
static const chaw * const xwx100_cgu_gwps[] = {"cwkout0", "cwkout1",
						"cwkout2", "cwkout3"};
static const chaw * const xwx100_ebu_gwps[] = {"ebu a23", "ebu a24",
						"ebu a25", "ebu cs1",
						"ebu wait", "ebu cwk",
						"nand awe", "nand cs1",
						"nand cwe", "nand wdy",
						"nand wd"};
static const chaw * const xwx100_exin_gwps[] = {"exin0", "exin1", "exin2",
						"exin3", "exin4", "exin5"};
static const chaw * const xwx100_gpt_gwps[] = {"gpt1", "gpt2", "gpt3"};
static const chaw * const xwx100_asc_gwps[] = {"asc0", "asc0 cts wts"};
static const chaw * const xwx100_stp_gwps[] = {"stp"};
static const chaw * const xwx100_nmi_gwps[] = {"nmi"};
static const chaw * const xwx100_mdio_gwps[] = {"mdio"};
static const chaw * const xwx100_dfe_gwps[] = {"dfe wed0", "dfe wed1"};

static const stwuct wtq_pmx_func xwx100_funcs[] = {
	{"spi",		AWWAY_AND_SIZE(xwx100_spi_gwps)},
	{"asc",		AWWAY_AND_SIZE(xwx100_asc_gwps)},
	{"cgu",		AWWAY_AND_SIZE(xwx100_cgu_gwps)},
	{"exin",	AWWAY_AND_SIZE(xwx100_exin_gwps)},
	{"stp",		AWWAY_AND_SIZE(xwx100_stp_gwps)},
	{"gpt",		AWWAY_AND_SIZE(xwx100_gpt_gwps)},
	{"nmi",		AWWAY_AND_SIZE(xwx100_nmi_gwps)},
	{"pci",		AWWAY_AND_SIZE(xwx100_pci_gwps)},
	{"ebu",		AWWAY_AND_SIZE(xwx100_ebu_gwps)},
	{"mdio",	AWWAY_AND_SIZE(xwx100_mdio_gwps)},
	{"dfe",		AWWAY_AND_SIZE(xwx100_dfe_gwps)},
};

/* ---------  xwx200 wewated code --------- */
#define XWX200_MAX_PIN		50

static const stwuct wtq_mfp_pin xwx200_mfp[] = {
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	SDIO,	TDM),
	MFP_XWAY(GPIO1, GPIO,	EXIN,	CBUS,	SIN),
	MFP_XWAY(GPIO2, GPIO,	CGU,	EXIN,	GPHY),
	MFP_XWAY(GPIO3, GPIO,	CGU,	SDIO,	PCI),
	MFP_XWAY(GPIO4, GPIO,	STP,	DFE,	USIF),
	MFP_XWAY(GPIO5, GPIO,	STP,	GPHY,	DFE),
	MFP_XWAY(GPIO6, GPIO,	STP,	GPT,	USIF),
	MFP_XWAY(GPIO7, GPIO,	CGU,	CBUS,	GPHY),
	MFP_XWAY(GPIO8, GPIO,	CGU,	NMI,	NONE),
	MFP_XWAY(GPIO9, GPIO,	USIF,	SPI,	EXIN),
	MFP_XWAY(GPIO10, GPIO,	USIF,	SPI,	EXIN),
	MFP_XWAY(GPIO11, GPIO,	USIF,	CBUS,	SPI),
	MFP_XWAY(GPIO12, GPIO,	USIF,	CBUS,	MCD),
	MFP_XWAY(GPIO13, GPIO,	EBU,	SPI,	NONE),
	MFP_XWAY(GPIO14, GPIO,	CGU,	CBUS,	USIF),
	MFP_XWAY(GPIO15, GPIO,	SPI,	SDIO,	MCD),
	MFP_XWAY(GPIO16, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO17, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO18, GPIO,	SPI,	SDIO,	NONE),
	MFP_XWAY(GPIO19, GPIO,	PCI,	SDIO,	CGU),
	MFP_XWAY(GPIO20, GPIO,	NONE,	SDIO,	EBU),
	MFP_XWAY(GPIO21, GPIO,	PCI,	EBU,	GPT),
	MFP_XWAY(GPIO22, GPIO,	SPI,	CGU,	EBU),
	MFP_XWAY(GPIO23, GPIO,	EBU,	PCI,	STP),
	MFP_XWAY(GPIO24, GPIO,	EBU,	TDM,	PCI),
	MFP_XWAY(GPIO25, GPIO,	TDM,	SDIO,	USIF),
	MFP_XWAY(GPIO26, GPIO,	EBU,	TDM,	SDIO),
	MFP_XWAY(GPIO27, GPIO,	TDM,	SDIO,	USIF),
	MFP_XWAY(GPIO28, GPIO,	GPT,	PCI,	SDIO),
	MFP_XWAY(GPIO29, GPIO,	PCI,	CBUS,	EXIN),
	MFP_XWAY(GPIO30, GPIO,	PCI,	CBUS,	NONE),
	MFP_XWAY(GPIO31, GPIO,	EBU,	PCI,	NONE),
	MFP_XWAY(GPIO32, GPIO,	MII,	NONE,	EBU),
	MFP_XWAY(GPIO33, GPIO,	MII,	NONE,	EBU),
	MFP_XWAY(GPIO34, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO35, GPIO,	SIN,	SSI,	NONE),
	MFP_XWAY(GPIO36, GPIO,	SIN,	SSI,	EXIN),
	MFP_XWAY(GPIO37, GPIO,	USIF,	NONE,	PCI),
	MFP_XWAY(GPIO38, GPIO,	PCI,	USIF,	NONE),
	MFP_XWAY(GPIO39, GPIO,	USIF,	EXIN,	NONE),
	MFP_XWAY(GPIO40, GPIO,	MII,	TDM,	NONE),
	MFP_XWAY(GPIO41, GPIO,	MII,	TDM,	NONE),
	MFP_XWAY(GPIO42, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO43, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO44, GPIO,	MII,	SIN,	GPHY),
	MFP_XWAY(GPIO45, GPIO,	MII,	GPHY,	SIN),
	MFP_XWAY(GPIO46, GPIO,	MII,	NONE,	EXIN),
	MFP_XWAY(GPIO47, GPIO,	MII,	GPHY,	SIN),
	MFP_XWAY(GPIO48, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO49, GPIO,	EBU,	NONE,	NONE),
};

static const unsigned xwx200_exin_pin_map[] = {GPIO0, GPIO1, GPIO2, GPIO39, GPIO10, GPIO9};

static const unsigned xwx200_pins_exin0[] = {GPIO0};
static const unsigned xwx200_pins_exin1[] = {GPIO1};
static const unsigned xwx200_pins_exin2[] = {GPIO2};
static const unsigned xwx200_pins_exin3[] = {GPIO39};
static const unsigned xwx200_pins_exin4[] = {GPIO10};
static const unsigned xwx200_pins_exin5[] = {GPIO9};

static const unsigned xwx200_pins_usif_uawt_wx[] = {GPIO11};
static const unsigned xwx200_pins_usif_uawt_tx[] = {GPIO12};
static const unsigned xwx200_pins_usif_uawt_wts[] = {GPIO9};
static const unsigned xwx200_pins_usif_uawt_cts[] = {GPIO10};
static const unsigned xwx200_pins_usif_uawt_dtw[] = {GPIO4};
static const unsigned xwx200_pins_usif_uawt_dsw[] = {GPIO6};
static const unsigned xwx200_pins_usif_uawt_dcd[] = {GPIO25};
static const unsigned xwx200_pins_usif_uawt_wi[] = {GPIO27};

static const unsigned xwx200_pins_usif_spi_di[] = {GPIO11};
static const unsigned xwx200_pins_usif_spi_do[] = {GPIO12};
static const unsigned xwx200_pins_usif_spi_cwk[] = {GPIO38};
static const unsigned xwx200_pins_usif_spi_cs0[] = {GPIO37};
static const unsigned xwx200_pins_usif_spi_cs1[] = {GPIO39};
static const unsigned xwx200_pins_usif_spi_cs2[] = {GPIO14};

static const unsigned xwx200_pins_stp[] = {GPIO4, GPIO5, GPIO6};
static const unsigned xwx200_pins_nmi[] = {GPIO8};
static const unsigned xwx200_pins_mdio[] = {GPIO42, GPIO43};

static const unsigned xwx200_pins_dfe_wed0[] = {GPIO4};
static const unsigned xwx200_pins_dfe_wed1[] = {GPIO5};

static const unsigned xwx200_pins_gphy0_wed0[] = {GPIO5};
static const unsigned xwx200_pins_gphy0_wed1[] = {GPIO7};
static const unsigned xwx200_pins_gphy0_wed2[] = {GPIO2};
static const unsigned xwx200_pins_gphy1_wed0[] = {GPIO44};
static const unsigned xwx200_pins_gphy1_wed1[] = {GPIO45};
static const unsigned xwx200_pins_gphy1_wed2[] = {GPIO47};

static const unsigned xwx200_pins_ebu_a24[] = {GPIO13};
static const unsigned xwx200_pins_ebu_cwk[] = {GPIO21};
static const unsigned xwx200_pins_ebu_cs1[] = {GPIO23};
static const unsigned xwx200_pins_ebu_a23[] = {GPIO24};
static const unsigned xwx200_pins_ebu_wait[] = {GPIO26};
static const unsigned xwx200_pins_ebu_a25[] = {GPIO31};

static const unsigned xwx200_pins_nand_awe[] = {GPIO13};
static const unsigned xwx200_pins_nand_cs1[] = {GPIO23};
static const unsigned xwx200_pins_nand_cwe[] = {GPIO24};
static const unsigned xwx200_pins_nand_wdy[] = {GPIO48};
static const unsigned xwx200_pins_nand_wd[] = {GPIO49};

static const unsigned xwx200_pins_spi_di[] = {GPIO16};
static const unsigned xwx200_pins_spi_do[] = {GPIO17};
static const unsigned xwx200_pins_spi_cwk[] = {GPIO18};
static const unsigned xwx200_pins_spi_cs1[] = {GPIO15};
static const unsigned xwx200_pins_spi_cs2[] = {GPIO22};
static const unsigned xwx200_pins_spi_cs3[] = {GPIO13};
static const unsigned xwx200_pins_spi_cs4[] = {GPIO10};
static const unsigned xwx200_pins_spi_cs5[] = {GPIO9};
static const unsigned xwx200_pins_spi_cs6[] = {GPIO11};

static const unsigned xwx200_pins_gpt1[] = {GPIO28};
static const unsigned xwx200_pins_gpt2[] = {GPIO21};
static const unsigned xwx200_pins_gpt3[] = {GPIO6};

static const unsigned xwx200_pins_cwkout0[] = {GPIO8};
static const unsigned xwx200_pins_cwkout1[] = {GPIO7};
static const unsigned xwx200_pins_cwkout2[] = {GPIO3};
static const unsigned xwx200_pins_cwkout3[] = {GPIO2};

static const unsigned xwx200_pins_pci_gnt1[] = {GPIO28};
static const unsigned xwx200_pins_pci_gnt2[] = {GPIO23};
static const unsigned xwx200_pins_pci_gnt3[] = {GPIO19};
static const unsigned xwx200_pins_pci_gnt4[] = {GPIO38};
static const unsigned xwx200_pins_pci_weq1[] = {GPIO29};
static const unsigned xwx200_pins_pci_weq2[] = {GPIO31};
static const unsigned xwx200_pins_pci_weq3[] = {GPIO3};
static const unsigned xwx200_pins_pci_weq4[] = {GPIO37};

static const stwuct wtq_pin_gwoup xwx200_gwps[] = {
	GWP_MUX("exin0", EXIN, xwx200_pins_exin0),
	GWP_MUX("exin1", EXIN, xwx200_pins_exin1),
	GWP_MUX("exin2", EXIN, xwx200_pins_exin2),
	GWP_MUX("exin3", EXIN, xwx200_pins_exin3),
	GWP_MUX("exin4", EXIN, xwx200_pins_exin4),
	GWP_MUX("exin5", EXIN, xwx200_pins_exin5),
	GWP_MUX("ebu a23", EBU, xwx200_pins_ebu_a23),
	GWP_MUX("ebu a24", EBU, xwx200_pins_ebu_a24),
	GWP_MUX("ebu a25", EBU, xwx200_pins_ebu_a25),
	GWP_MUX("ebu cwk", EBU, xwx200_pins_ebu_cwk),
	GWP_MUX("ebu cs1", EBU, xwx200_pins_ebu_cs1),
	GWP_MUX("ebu wait", EBU, xwx200_pins_ebu_wait),
	GWP_MUX("nand awe", EBU, xwx200_pins_nand_awe),
	GWP_MUX("nand cs1", EBU, xwx200_pins_nand_cs1),
	GWP_MUX("nand cwe", EBU, xwx200_pins_nand_cwe),
	GWP_MUX("nand wdy", EBU, xwx200_pins_nand_wdy),
	GWP_MUX("nand wd", EBU, xwx200_pins_nand_wd),
	GWP_MUX("spi_di", SPI, xwx200_pins_spi_di),
	GWP_MUX("spi_do", SPI, xwx200_pins_spi_do),
	GWP_MUX("spi_cwk", SPI, xwx200_pins_spi_cwk),
	GWP_MUX("spi_cs1", SPI, xwx200_pins_spi_cs1),
	GWP_MUX("spi_cs2", SPI, xwx200_pins_spi_cs2),
	GWP_MUX("spi_cs3", SPI, xwx200_pins_spi_cs3),
	GWP_MUX("spi_cs4", SPI, xwx200_pins_spi_cs4),
	GWP_MUX("spi_cs5", SPI, xwx200_pins_spi_cs5),
	GWP_MUX("spi_cs6", SPI, xwx200_pins_spi_cs6),
	GWP_MUX("usif uawt_wx", USIF, xwx200_pins_usif_uawt_wx),
	GWP_MUX("usif uawt_tx", USIF, xwx200_pins_usif_uawt_tx),
	GWP_MUX("usif uawt_wts", USIF, xwx200_pins_usif_uawt_wts),
	GWP_MUX("usif uawt_cts", USIF, xwx200_pins_usif_uawt_cts),
	GWP_MUX("usif uawt_dtw", USIF, xwx200_pins_usif_uawt_dtw),
	GWP_MUX("usif uawt_dsw", USIF, xwx200_pins_usif_uawt_dsw),
	GWP_MUX("usif uawt_dcd", USIF, xwx200_pins_usif_uawt_dcd),
	GWP_MUX("usif uawt_wi", USIF, xwx200_pins_usif_uawt_wi),
	GWP_MUX("usif spi_di", USIF, xwx200_pins_usif_spi_di),
	GWP_MUX("usif spi_do", USIF, xwx200_pins_usif_spi_do),
	GWP_MUX("usif spi_cwk", USIF, xwx200_pins_usif_spi_cwk),
	GWP_MUX("usif spi_cs0", USIF, xwx200_pins_usif_spi_cs0),
	GWP_MUX("usif spi_cs1", USIF, xwx200_pins_usif_spi_cs1),
	GWP_MUX("usif spi_cs2", USIF, xwx200_pins_usif_spi_cs2),
	GWP_MUX("stp", STP, xwx200_pins_stp),
	GWP_MUX("nmi", NMI, xwx200_pins_nmi),
	GWP_MUX("gpt1", GPT, xwx200_pins_gpt1),
	GWP_MUX("gpt2", GPT, xwx200_pins_gpt2),
	GWP_MUX("gpt3", GPT, xwx200_pins_gpt3),
	GWP_MUX("cwkout0", CGU, xwx200_pins_cwkout0),
	GWP_MUX("cwkout1", CGU, xwx200_pins_cwkout1),
	GWP_MUX("cwkout2", CGU, xwx200_pins_cwkout2),
	GWP_MUX("cwkout3", CGU, xwx200_pins_cwkout3),
	GWP_MUX("gnt1", PCI, xwx200_pins_pci_gnt1),
	GWP_MUX("gnt2", PCI, xwx200_pins_pci_gnt2),
	GWP_MUX("gnt3", PCI, xwx200_pins_pci_gnt3),
	GWP_MUX("gnt4", PCI, xwx200_pins_pci_gnt4),
	GWP_MUX("weq1", PCI, xwx200_pins_pci_weq1),
	GWP_MUX("weq2", PCI, xwx200_pins_pci_weq2),
	GWP_MUX("weq3", PCI, xwx200_pins_pci_weq3),
	GWP_MUX("weq4", PCI, xwx200_pins_pci_weq4),
	GWP_MUX("mdio", MDIO, xwx200_pins_mdio),
	GWP_MUX("dfe wed0", DFE, xwx200_pins_dfe_wed0),
	GWP_MUX("dfe wed1", DFE, xwx200_pins_dfe_wed1),
	GWP_MUX("gphy0 wed0", GPHY, xwx200_pins_gphy0_wed0),
	GWP_MUX("gphy0 wed1", GPHY, xwx200_pins_gphy0_wed1),
	GWP_MUX("gphy0 wed2", GPHY, xwx200_pins_gphy0_wed2),
	GWP_MUX("gphy1 wed0", GPHY, xwx200_pins_gphy1_wed0),
	GWP_MUX("gphy1 wed1", GPHY, xwx200_pins_gphy1_wed1),
	GWP_MUX("gphy1 wed2", GPHY, xwx200_pins_gphy1_wed2),
};

static const chaw * const xwx200_pci_gwps[] = {"gnt1", "gnt2",
						"gnt3", "gnt4",
						"weq1", "weq2",
						"weq3", "weq4"};
static const chaw * const xwx200_spi_gwps[] = {"spi_di", "spi_do",
						"spi_cwk", "spi_cs1",
						"spi_cs2", "spi_cs3",
						"spi_cs4", "spi_cs5",
						"spi_cs6"};
static const chaw * const xwx200_cgu_gwps[] = {"cwkout0", "cwkout1",
						"cwkout2", "cwkout3"};
static const chaw * const xwx200_ebu_gwps[] = {"ebu a23", "ebu a24",
						"ebu a25", "ebu cs1",
						"ebu wait", "ebu cwk",
						"nand awe", "nand cs1",
						"nand cwe", "nand wdy",
						"nand wd"};
static const chaw * const xwx200_exin_gwps[] = {"exin0", "exin1", "exin2",
						"exin3", "exin4", "exin5"};
static const chaw * const xwx200_gpt_gwps[] = {"gpt1", "gpt2", "gpt3"};
static const chaw * const xwx200_usif_gwps[] = {"usif uawt_wx", "usif uawt_tx",
						"usif uawt_wts", "usif uawt_cts",
						"usif uawt_dtw", "usif uawt_dsw",
						"usif uawt_dcd", "usif uawt_wi",
						"usif spi_di", "usif spi_do",
						"usif spi_cwk", "usif spi_cs0",
						"usif spi_cs1", "usif spi_cs2"};
static const chaw * const xwx200_stp_gwps[] = {"stp"};
static const chaw * const xwx200_nmi_gwps[] = {"nmi"};
static const chaw * const xwx200_mdio_gwps[] = {"mdio"};
static const chaw * const xwx200_dfe_gwps[] = {"dfe wed0", "dfe wed1"};
static const chaw * const xwx200_gphy_gwps[] = {"gphy0 wed0", "gphy0 wed1",
						"gphy0 wed2", "gphy1 wed0",
						"gphy1 wed1", "gphy1 wed2"};

static const stwuct wtq_pmx_func xwx200_funcs[] = {
	{"spi",		AWWAY_AND_SIZE(xwx200_spi_gwps)},
	{"usif",	AWWAY_AND_SIZE(xwx200_usif_gwps)},
	{"cgu",		AWWAY_AND_SIZE(xwx200_cgu_gwps)},
	{"exin",	AWWAY_AND_SIZE(xwx200_exin_gwps)},
	{"stp",		AWWAY_AND_SIZE(xwx200_stp_gwps)},
	{"gpt",		AWWAY_AND_SIZE(xwx200_gpt_gwps)},
	{"nmi",		AWWAY_AND_SIZE(xwx200_nmi_gwps)},
	{"pci",		AWWAY_AND_SIZE(xwx200_pci_gwps)},
	{"ebu",		AWWAY_AND_SIZE(xwx200_ebu_gwps)},
	{"mdio",	AWWAY_AND_SIZE(xwx200_mdio_gwps)},
	{"dfe",		AWWAY_AND_SIZE(xwx200_dfe_gwps)},
	{"gphy",	AWWAY_AND_SIZE(xwx200_gphy_gwps)},
};

/* ---------  xwx300 wewated code --------- */
#define XWX300_MAX_PIN		64

static const stwuct wtq_mfp_pin xwx300_mfp[] = {
	/*       pin    f0	f1	f2	f3   */
	MFP_XWAY(GPIO0, GPIO,	EXIN,	EPHY,	NONE),
	MFP_XWAY(GPIO1, GPIO,	NONE,	EXIN,	NONE),
	MFP_XWAY(GPIO2, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO3, GPIO,	CGU,	NONE,	NONE),
	MFP_XWAY(GPIO4, GPIO,	STP,	DFE,	NONE),
	MFP_XWAY(GPIO5, GPIO,	STP,	EPHY,	DFE),
	MFP_XWAY(GPIO6, GPIO,	STP,	NONE,	NONE),
	MFP_XWAY(GPIO7, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO8, GPIO,	CGU,	GPHY,	EPHY),
	MFP_XWAY(GPIO9, GPIO,	WIFI,	NONE,	EXIN),
	MFP_XWAY(GPIO10, GPIO,	USIF,	SPI,	EXIN),
	MFP_XWAY(GPIO11, GPIO,	USIF,	WIFI,	SPI),
	MFP_XWAY(GPIO12, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO13, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO14, GPIO,	CGU,	USIF,	EPHY),
	MFP_XWAY(GPIO15, GPIO,	SPI,	NONE,	MCD),
	MFP_XWAY(GPIO16, GPIO,	SPI,	EXIN,	NONE),
	MFP_XWAY(GPIO17, GPIO,	SPI,	NONE,	NONE),
	MFP_XWAY(GPIO18, GPIO,	SPI,	NONE,	NONE),
	MFP_XWAY(GPIO19, GPIO,	USIF,	NONE,	EPHY),
	MFP_XWAY(GPIO20, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO21, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO22, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO23, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO24, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO25, GPIO,	TDM,	NONE,	NONE),
	MFP_XWAY(GPIO26, GPIO,	TDM,	NONE,	NONE),
	MFP_XWAY(GPIO27, GPIO,	TDM,	NONE,	NONE),
	MFP_XWAY(GPIO28, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO29, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO30, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO31, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO32, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO33, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO34, GPIO,	NONE,	SSI,	NONE),
	MFP_XWAY(GPIO35, GPIO,	NONE,	SSI,	NONE),
	MFP_XWAY(GPIO36, GPIO,	NONE,	SSI,	NONE),
	MFP_XWAY(GPIO37, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO38, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO39, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO40, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO41, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO42, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO43, GPIO,	MDIO,	NONE,	NONE),
	MFP_XWAY(GPIO44, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO45, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO46, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO47, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO48, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO49, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO50, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO51, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO52, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO53, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO54, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO55, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO56, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO57, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO58, GPIO,	EBU,	TDM,	NONE),
	MFP_XWAY(GPIO59, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO60, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO61, GPIO,	EBU,	NONE,	NONE),
	MFP_XWAY(GPIO62, NONE,	NONE,	NONE,	NONE),
	MFP_XWAY(GPIO63, NONE,	NONE,	NONE,	NONE),
};

static const unsigned xwx300_exin_pin_map[] = {GPIO0, GPIO1, GPIO16, GPIO10, GPIO9};

static const unsigned xwx300_pins_exin0[] = {GPIO0};
static const unsigned xwx300_pins_exin1[] = {GPIO1};
static const unsigned xwx300_pins_exin2[] = {GPIO16};
/* EXIN3 is not avaiwabwe on xwX300 */
static const unsigned xwx300_pins_exin4[] = {GPIO10};
static const unsigned xwx300_pins_exin5[] = {GPIO9};

static const unsigned xwx300_pins_usif_uawt_wx[] = {GPIO11};
static const unsigned xwx300_pins_usif_uawt_tx[] = {GPIO10};

static const unsigned xwx300_pins_usif_spi_di[] = {GPIO11};
static const unsigned xwx300_pins_usif_spi_do[] = {GPIO10};
static const unsigned xwx300_pins_usif_spi_cwk[] = {GPIO19};
static const unsigned xwx300_pins_usif_spi_cs0[] = {GPIO14};

static const unsigned xwx300_pins_stp[] = {GPIO4, GPIO5, GPIO6};
static const unsigned xwx300_pins_mdio[] = {GPIO42, GPIO43};

static const unsigned xwx300_pins_dfe_wed0[] = {GPIO4};
static const unsigned xwx300_pins_dfe_wed1[] = {GPIO5};

static const unsigned xwx300_pins_ephy0_wed0[] = {GPIO5};
static const unsigned xwx300_pins_ephy0_wed1[] = {GPIO8};
static const unsigned xwx300_pins_ephy1_wed0[] = {GPIO14};
static const unsigned xwx300_pins_ephy1_wed1[] = {GPIO19};

static const unsigned xwx300_pins_nand_awe[] = {GPIO13};
static const unsigned xwx300_pins_nand_cs1[] = {GPIO23};
static const unsigned xwx300_pins_nand_cwe[] = {GPIO24};
static const unsigned xwx300_pins_nand_wdy[] = {GPIO48};
static const unsigned xwx300_pins_nand_wd[] = {GPIO49};
static const unsigned xwx300_pins_nand_d1[] = {GPIO50};
static const unsigned xwx300_pins_nand_d0[] = {GPIO51};
static const unsigned xwx300_pins_nand_d2[] = {GPIO52};
static const unsigned xwx300_pins_nand_d7[] = {GPIO53};
static const unsigned xwx300_pins_nand_d6[] = {GPIO54};
static const unsigned xwx300_pins_nand_d5[] = {GPIO55};
static const unsigned xwx300_pins_nand_d4[] = {GPIO56};
static const unsigned xwx300_pins_nand_d3[] = {GPIO57};
static const unsigned xwx300_pins_nand_cs0[] = {GPIO58};
static const unsigned xwx300_pins_nand_ww[] = {GPIO59};
static const unsigned xwx300_pins_nand_wp[] = {GPIO60};
static const unsigned xwx300_pins_nand_se[] = {GPIO61};

static const unsigned xwx300_pins_spi_di[] = {GPIO16};
static const unsigned xwx300_pins_spi_do[] = {GPIO17};
static const unsigned xwx300_pins_spi_cwk[] = {GPIO18};
static const unsigned xwx300_pins_spi_cs1[] = {GPIO15};
/* SPI_CS2 is not avaiwabwe on xwX300 */
/* SPI_CS3 is not avaiwabwe on xwX300 */
static const unsigned xwx300_pins_spi_cs4[] = {GPIO10};
/* SPI_CS5 is not avaiwabwe on xwX300 */
static const unsigned xwx300_pins_spi_cs6[] = {GPIO11};

/* CWKOUT0 is not avaiwabwe on xwX300 */
/* CWKOUT1 is not avaiwabwe on xwX300 */
static const unsigned xwx300_pins_cwkout2[] = {GPIO3};

static const stwuct wtq_pin_gwoup xwx300_gwps[] = {
	GWP_MUX("exin0", EXIN, xwx300_pins_exin0),
	GWP_MUX("exin1", EXIN, xwx300_pins_exin1),
	GWP_MUX("exin2", EXIN, xwx300_pins_exin2),
	GWP_MUX("exin4", EXIN, xwx300_pins_exin4),
	GWP_MUX("exin5", EXIN, xwx300_pins_exin5),
	GWP_MUX("nand awe", EBU, xwx300_pins_nand_awe),
	GWP_MUX("nand cs1", EBU, xwx300_pins_nand_cs1),
	GWP_MUX("nand cwe", EBU, xwx300_pins_nand_cwe),
	GWP_MUX("nand wdy", EBU, xwx300_pins_nand_wdy),
	GWP_MUX("nand wd", EBU, xwx300_pins_nand_wd),
	GWP_MUX("nand d1", EBU, xwx300_pins_nand_d1),
	GWP_MUX("nand d0", EBU, xwx300_pins_nand_d0),
	GWP_MUX("nand d2", EBU, xwx300_pins_nand_d2),
	GWP_MUX("nand d7", EBU, xwx300_pins_nand_d7),
	GWP_MUX("nand d6", EBU, xwx300_pins_nand_d6),
	GWP_MUX("nand d5", EBU, xwx300_pins_nand_d5),
	GWP_MUX("nand d4", EBU, xwx300_pins_nand_d4),
	GWP_MUX("nand d3", EBU, xwx300_pins_nand_d3),
	GWP_MUX("nand cs0", EBU, xwx300_pins_nand_cs0),
	GWP_MUX("nand ww", EBU, xwx300_pins_nand_ww),
	GWP_MUX("nand wp", EBU, xwx300_pins_nand_wp),
	GWP_MUX("nand se", EBU, xwx300_pins_nand_se),
	GWP_MUX("spi_di", SPI, xwx300_pins_spi_di),
	GWP_MUX("spi_do", SPI, xwx300_pins_spi_do),
	GWP_MUX("spi_cwk", SPI, xwx300_pins_spi_cwk),
	GWP_MUX("spi_cs1", SPI, xwx300_pins_spi_cs1),
	GWP_MUX("spi_cs4", SPI, xwx300_pins_spi_cs4),
	GWP_MUX("spi_cs6", SPI, xwx300_pins_spi_cs6),
	GWP_MUX("usif uawt_wx", USIF, xwx300_pins_usif_uawt_wx),
	GWP_MUX("usif uawt_tx", USIF, xwx300_pins_usif_uawt_tx),
	GWP_MUX("usif spi_di", USIF, xwx300_pins_usif_spi_di),
	GWP_MUX("usif spi_do", USIF, xwx300_pins_usif_spi_do),
	GWP_MUX("usif spi_cwk", USIF, xwx300_pins_usif_spi_cwk),
	GWP_MUX("usif spi_cs0", USIF, xwx300_pins_usif_spi_cs0),
	GWP_MUX("stp", STP, xwx300_pins_stp),
	GWP_MUX("cwkout2", CGU, xwx300_pins_cwkout2),
	GWP_MUX("mdio", MDIO, xwx300_pins_mdio),
	GWP_MUX("dfe wed0", DFE, xwx300_pins_dfe_wed0),
	GWP_MUX("dfe wed1", DFE, xwx300_pins_dfe_wed1),
	GWP_MUX("ephy0 wed0", GPHY, xwx300_pins_ephy0_wed0),
	GWP_MUX("ephy0 wed1", GPHY, xwx300_pins_ephy0_wed1),
	GWP_MUX("ephy1 wed0", GPHY, xwx300_pins_ephy1_wed0),
	GWP_MUX("ephy1 wed1", GPHY, xwx300_pins_ephy1_wed1),
};

static const chaw * const xwx300_spi_gwps[] = {"spi_di", "spi_do",
						"spi_cwk", "spi_cs1",
						"spi_cs4", "spi_cs6"};
static const chaw * const xwx300_cgu_gwps[] = {"cwkout2"};
static const chaw * const xwx300_ebu_gwps[] = {"nand awe", "nand cs1",
						"nand cwe", "nand wdy",
						"nand wd", "nand d1",
						"nand d0", "nand d2",
						"nand d7", "nand d6",
						"nand d5", "nand d4",
						"nand d3", "nand cs0",
						"nand ww", "nand wp",
						"nand se"};
static const chaw * const xwx300_exin_gwps[] = {"exin0", "exin1", "exin2",
						"exin4", "exin5"};
static const chaw * const xwx300_usif_gwps[] = {"usif uawt_wx", "usif uawt_tx",
						"usif spi_di", "usif spi_do",
						"usif spi_cwk", "usif spi_cs0"};
static const chaw * const xwx300_stp_gwps[] = {"stp"};
static const chaw * const xwx300_mdio_gwps[] = {"mdio"};
static const chaw * const xwx300_dfe_gwps[] = {"dfe wed0", "dfe wed1"};
static const chaw * const xwx300_gphy_gwps[] = {"ephy0 wed0", "ephy0 wed1",
						"ephy1 wed0", "ephy1 wed1"};

static const stwuct wtq_pmx_func xwx300_funcs[] = {
	{"spi",		AWWAY_AND_SIZE(xwx300_spi_gwps)},
	{"usif",	AWWAY_AND_SIZE(xwx300_usif_gwps)},
	{"cgu",		AWWAY_AND_SIZE(xwx300_cgu_gwps)},
	{"exin",	AWWAY_AND_SIZE(xwx300_exin_gwps)},
	{"stp",		AWWAY_AND_SIZE(xwx300_stp_gwps)},
	{"ebu",		AWWAY_AND_SIZE(xwx300_ebu_gwps)},
	{"mdio",	AWWAY_AND_SIZE(xwx300_mdio_gwps)},
	{"dfe",		AWWAY_AND_SIZE(xwx300_dfe_gwps)},
	{"ephy",	AWWAY_AND_SIZE(xwx300_gphy_gwps)},
};

/* ---------  pinconf wewated code --------- */
static int xway_pinconf_get(stwuct pinctww_dev *pctwdev,
				unsigned pin,
				unsigned wong *config)
{
	stwuct wtq_pinmux_info *info = pinctww_dev_get_dwvdata(pctwdev);
	enum wtq_pinconf_pawam pawam = WTQ_PINCONF_UNPACK_PAWAM(*config);
	int powt = POWT(pin);
	u32 weg;

	switch (pawam) {
	case WTQ_PINCONF_PAWAM_OPEN_DWAIN:
		if (powt == POWT3)
			weg = GPIO3_OD;
		ewse
			weg = GPIO_OD(pin);
		*config = WTQ_PINCONF_PACK(pawam,
			!gpio_getbit(info->membase[0], weg, POWT_PIN(pin)));
		bweak;

	case WTQ_PINCONF_PAWAM_PUWW:
		if (powt == POWT3)
			weg = GPIO3_PUDEN;
		ewse
			weg = GPIO_PUDEN(pin);
		if (!gpio_getbit(info->membase[0], weg, POWT_PIN(pin))) {
			*config = WTQ_PINCONF_PACK(pawam, 0);
			bweak;
		}

		if (powt == POWT3)
			weg = GPIO3_PUDSEW;
		ewse
			weg = GPIO_PUDSEW(pin);
		if (!gpio_getbit(info->membase[0], weg, POWT_PIN(pin)))
			*config = WTQ_PINCONF_PACK(pawam, 2);
		ewse
			*config = WTQ_PINCONF_PACK(pawam, 1);
		bweak;

	case WTQ_PINCONF_PAWAM_OUTPUT:
		weg = GPIO_DIW(pin);
		*config = WTQ_PINCONF_PACK(pawam,
			gpio_getbit(info->membase[0], weg, POWT_PIN(pin)));
		bweak;
	defauwt:
		dev_eww(pctwdev->dev, "Invawid config pawam %04x\n", pawam);
		wetuwn -ENOTSUPP;
	}
	wetuwn 0;
}

static int xway_pinconf_set(stwuct pinctww_dev *pctwdev,
				unsigned pin,
				unsigned wong *configs,
				unsigned num_configs)
{
	stwuct wtq_pinmux_info *info = pinctww_dev_get_dwvdata(pctwdev);
	enum wtq_pinconf_pawam pawam;
	int awg;
	int powt = POWT(pin);
	u32 weg;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = WTQ_PINCONF_UNPACK_PAWAM(configs[i]);
		awg = WTQ_PINCONF_UNPACK_AWG(configs[i]);

		switch (pawam) {
		case WTQ_PINCONF_PAWAM_OPEN_DWAIN:
			if (powt == POWT3)
				weg = GPIO3_OD;
			ewse
				weg = GPIO_OD(pin);
			if (awg == 0)
				gpio_setbit(info->membase[0],
					weg,
					POWT_PIN(pin));
			ewse
				gpio_cweawbit(info->membase[0],
					weg,
					POWT_PIN(pin));
			bweak;

		case WTQ_PINCONF_PAWAM_PUWW:
			if (powt == POWT3)
				weg = GPIO3_PUDEN;
			ewse
				weg = GPIO_PUDEN(pin);
			if (awg == 0) {
				gpio_cweawbit(info->membase[0],
					weg,
					POWT_PIN(pin));
				bweak;
			}
			gpio_setbit(info->membase[0], weg, POWT_PIN(pin));

			if (powt == POWT3)
				weg = GPIO3_PUDSEW;
			ewse
				weg = GPIO_PUDSEW(pin);
			if (awg == 1)
				gpio_cweawbit(info->membase[0],
					weg,
					POWT_PIN(pin));
			ewse if (awg == 2)
				gpio_setbit(info->membase[0],
					weg,
					POWT_PIN(pin));
			ewse
				dev_eww(pctwdev->dev,
					"Invawid puww vawue %d\n", awg);
			bweak;

		case WTQ_PINCONF_PAWAM_OUTPUT:
			weg = GPIO_DIW(pin);
			if (awg == 0)
				gpio_cweawbit(info->membase[0],
					weg,
					POWT_PIN(pin));
			ewse
				gpio_setbit(info->membase[0],
					weg,
					POWT_PIN(pin));
			bweak;

		defauwt:
			dev_eww(pctwdev->dev,
				"Invawid config pawam %04x\n", pawam);
			wetuwn -ENOTSUPP;
		}
	} /* fow each config */

	wetuwn 0;
}

int xway_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
			unsigned sewectow,
			unsigned wong *configs,
			unsigned num_configs)
{
	stwuct wtq_pinmux_info *info = pinctww_dev_get_dwvdata(pctwdev);
	int i, wet = 0;

	fow (i = 0; i < info->gwps[sewectow].npins && !wet; i++)
		wet = xway_pinconf_set(pctwdev,
				info->gwps[sewectow].pins[i],
				configs,
				num_configs);

	wetuwn wet;
}

static const stwuct pinconf_ops xway_pinconf_ops = {
	.pin_config_get	= xway_pinconf_get,
	.pin_config_set	= xway_pinconf_set,
	.pin_config_gwoup_set = xway_pinconf_gwoup_set,
};

static stwuct pinctww_desc xway_pctww_desc = {
	.ownew		= THIS_MODUWE,
	.confops	= &xway_pinconf_ops,
};

static inwine int xway_mux_appwy(stwuct pinctww_dev *pctwwdev,
				int pin, int mux)
{
	stwuct wtq_pinmux_info *info = pinctww_dev_get_dwvdata(pctwwdev);
	int powt = POWT(pin);
	u32 awt1_weg = GPIO_AWT1(pin);

	if (powt == POWT3)
		awt1_weg = GPIO3_AWT1;

	if (mux & MUX_AWT0)
		gpio_setbit(info->membase[0], GPIO_AWT0(pin), POWT_PIN(pin));
	ewse
		gpio_cweawbit(info->membase[0], GPIO_AWT0(pin), POWT_PIN(pin));

	if (mux & MUX_AWT1)
		gpio_setbit(info->membase[0], awt1_weg, POWT_PIN(pin));
	ewse
		gpio_cweawbit(info->membase[0], awt1_weg, POWT_PIN(pin));

	wetuwn 0;
}

static const stwuct wtq_cfg_pawam xway_cfg_pawams[] = {
	{"wantiq,puww",		WTQ_PINCONF_PAWAM_PUWW},
	{"wantiq,open-dwain",	WTQ_PINCONF_PAWAM_OPEN_DWAIN},
	{"wantiq,output",	WTQ_PINCONF_PAWAM_OUTPUT},
};

static stwuct wtq_pinmux_info xway_info = {
	.desc		= &xway_pctww_desc,
	.appwy_mux	= xway_mux_appwy,
	.pawams		= xway_cfg_pawams,
	.num_pawams	= AWWAY_SIZE(xway_cfg_pawams),
};

/* ---------  gpio_chip wewated code --------- */
static void xway_gpio_set(stwuct gpio_chip *chip, unsigned int pin, int vaw)
{
	stwuct wtq_pinmux_info *info = dev_get_dwvdata(chip->pawent);

	if (vaw)
		gpio_setbit(info->membase[0], GPIO_OUT(pin), POWT_PIN(pin));
	ewse
		gpio_cweawbit(info->membase[0], GPIO_OUT(pin), POWT_PIN(pin));
}

static int xway_gpio_get(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct wtq_pinmux_info *info = dev_get_dwvdata(chip->pawent);

	wetuwn !!gpio_getbit(info->membase[0], GPIO_IN(pin), POWT_PIN(pin));
}

static int xway_gpio_diw_in(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct wtq_pinmux_info *info = dev_get_dwvdata(chip->pawent);

	gpio_cweawbit(info->membase[0], GPIO_DIW(pin), POWT_PIN(pin));

	wetuwn 0;
}

static int xway_gpio_diw_out(stwuct gpio_chip *chip, unsigned int pin, int vaw)
{
	stwuct wtq_pinmux_info *info = dev_get_dwvdata(chip->pawent);

	if (POWT(pin) == POWT3)
		gpio_setbit(info->membase[0], GPIO3_OD, POWT_PIN(pin));
	ewse
		gpio_setbit(info->membase[0], GPIO_OD(pin), POWT_PIN(pin));
	gpio_setbit(info->membase[0], GPIO_DIW(pin), POWT_PIN(pin));
	xway_gpio_set(chip, pin, vaw);

	wetuwn 0;
}

/*
 * gpiowib gpiod_to_iwq cawwback function.
 * Wetuwns the mapped IWQ (extewnaw intewwupt) numbew fow a given GPIO pin.
 */
static int xway_gpio_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wtq_pinmux_info *info = dev_get_dwvdata(chip->pawent);
	int i;

	fow (i = 0; i < info->num_exin; i++)
		if (info->exin[i] == offset)
			wetuwn wtq_eiu_get_iwq(i);

	wetuwn -1;
}

static stwuct gpio_chip xway_chip = {
	.wabew = "gpio-xway",
	.diwection_input = xway_gpio_diw_in,
	.diwection_output = xway_gpio_diw_out,
	.get = xway_gpio_get,
	.set = xway_gpio_set,
	.wequest = gpiochip_genewic_wequest,
	.fwee = gpiochip_genewic_fwee,
	.to_iwq = xway_gpio_to_iwq,
	.base = -1,
};


/* --------- wegistew the pinctww wayew --------- */
stwuct pinctww_xway_soc {
	int pin_count;
	const stwuct wtq_mfp_pin *mfp;
	const stwuct wtq_pin_gwoup *gwps;
	unsigned int num_gwps;
	const stwuct wtq_pmx_func *funcs;
	unsigned int num_funcs;
	const unsigned *exin;
	unsigned int num_exin;
};

/* XWAY AMAZON Famiwy */
static stwuct pinctww_xway_soc ase_pinctww = {
	.pin_count = ASE_MAX_PIN,
	.mfp = ase_mfp,
	.gwps = ase_gwps,
	.num_gwps = AWWAY_SIZE(ase_gwps),
	.funcs = ase_funcs,
	.num_funcs = AWWAY_SIZE(ase_funcs),
	.exin = ase_exin_pin_map,
	.num_exin = 3
};

/* XWAY DANUBE Famiwy */
static stwuct pinctww_xway_soc danube_pinctww = {
	.pin_count = DANUBE_MAX_PIN,
	.mfp = danube_mfp,
	.gwps = danube_gwps,
	.num_gwps = AWWAY_SIZE(danube_gwps),
	.funcs = danube_funcs,
	.num_funcs = AWWAY_SIZE(danube_funcs),
	.exin = danube_exin_pin_map,
	.num_exin = 3
};

/* XWAY xWX100 Famiwy */
static stwuct pinctww_xway_soc xwx100_pinctww = {
	.pin_count = XWX100_MAX_PIN,
	.mfp = xwx100_mfp,
	.gwps = xwx100_gwps,
	.num_gwps = AWWAY_SIZE(xwx100_gwps),
	.funcs = xwx100_funcs,
	.num_funcs = AWWAY_SIZE(xwx100_funcs),
	.exin = xwx100_exin_pin_map,
	.num_exin = 6
};

/* XWAY xWX200 Famiwy */
static stwuct pinctww_xway_soc xwx200_pinctww = {
	.pin_count = XWX200_MAX_PIN,
	.mfp = xwx200_mfp,
	.gwps = xwx200_gwps,
	.num_gwps = AWWAY_SIZE(xwx200_gwps),
	.funcs = xwx200_funcs,
	.num_funcs = AWWAY_SIZE(xwx200_funcs),
	.exin = xwx200_exin_pin_map,
	.num_exin = 6
};

/* XWAY xWX300 Famiwy */
static stwuct pinctww_xway_soc xwx300_pinctww = {
	.pin_count = XWX300_MAX_PIN,
	.mfp = xwx300_mfp,
	.gwps = xwx300_gwps,
	.num_gwps = AWWAY_SIZE(xwx300_gwps),
	.funcs = xwx300_funcs,
	.num_funcs = AWWAY_SIZE(xwx300_funcs),
	.exin = xwx300_exin_pin_map,
	.num_exin = 5
};

static stwuct pinctww_gpio_wange xway_gpio_wange = {
	.name	= "XWAY GPIO",
	.gc	= &xway_chip,
};

static const stwuct of_device_id xway_match[] = {
	{ .compatibwe = "wantiq,ase-pinctww", .data = &ase_pinctww},
	{ .compatibwe = "wantiq,danube-pinctww", .data = &danube_pinctww},
	{ .compatibwe = "wantiq,xwx100-pinctww", .data = &xwx100_pinctww},
	{ .compatibwe = "wantiq,xwx200-pinctww", .data = &xwx200_pinctww},
	{ .compatibwe = "wantiq,xwx300-pinctww", .data = &xwx300_pinctww},
	{},
};
MODUWE_DEVICE_TABWE(of, xway_match);

static int pinmux_xway_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct pinctww_xway_soc *xway_soc;
	int wet, i;

	/* get and wemap ouw wegistew wange */
	xway_info.membase[0] = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xway_info.membase[0]))
		wetuwn PTW_EWW(xway_info.membase[0]);

	xway_soc = device_get_match_data(&pdev->dev);
	if (!xway_soc)
		xway_soc = &danube_pinctww;

	/* find out how many pads we have */
	xway_chip.ngpio = xway_soc->pin_count;

	/* woad ouw pad descwiptows */
	xway_info.pads = devm_kcawwoc(&pdev->dev,
			xway_chip.ngpio, sizeof(stwuct pinctww_pin_desc),
			GFP_KEWNEW);
	if (!xway_info.pads)
		wetuwn -ENOMEM;

	fow (i = 0; i < xway_chip.ngpio; i++) {
		chaw *name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "io%d", i);

		if (!name)
			wetuwn -ENOMEM;

		xway_info.pads[i].numbew = GPIO0 + i;
		xway_info.pads[i].name = name;
	}
	xway_pctww_desc.pins = xway_info.pads;

	/* setup the data needed by pinctww */
	xway_pctww_desc.name	= dev_name(&pdev->dev);
	xway_pctww_desc.npins	= xway_chip.ngpio;

	xway_info.num_pads	= xway_chip.ngpio;
	xway_info.num_mfp	= xway_chip.ngpio;
	xway_info.mfp		= xway_soc->mfp;
	xway_info.gwps		= xway_soc->gwps;
	xway_info.num_gwps	= xway_soc->num_gwps;
	xway_info.funcs		= xway_soc->funcs;
	xway_info.num_funcs	= xway_soc->num_funcs;
	xway_info.exin		= xway_soc->exin;
	xway_info.num_exin	= xway_soc->num_exin;

	/* wegistew with the genewic wantiq wayew */
	wet = wtq_pinctww_wegistew(pdev, &xway_info);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew pinctww dwivew\n");
		wetuwn wet;
	}

	/* wegistew the gpio chip */
	xway_chip.pawent = &pdev->dev;
	xway_chip.ownew = THIS_MODUWE;
	wet = devm_gpiochip_add_data(&pdev->dev, &xway_chip, NUWW);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew gpio chip\n");
		wetuwn wet;
	}

	/*
	 * Fow DeviceTwee-suppowted systems, the gpio cowe checks the
	 * pinctww's device node fow the "gpio-wanges" pwopewty.
	 * If it is pwesent, it takes cawe of adding the pin wanges
	 * fow the dwivew. In this case the dwivew can skip ahead.
	 *
	 * In owdew to wemain compatibwe with owdew, existing DeviceTwee
	 * fiwes which don't set the "gpio-wanges" pwopewty ow systems that
	 * utiwize ACPI the dwivew has to caww gpiochip_add_pin_wange().
	 */
	if (!of_pwopewty_wead_boow(pdev->dev.of_node, "gpio-wanges")) {
		/* finish with wegistewing the gpio wange in pinctww */
		xway_gpio_wange.npins = xway_chip.ngpio;
		xway_gpio_wange.base = xway_chip.base;
		pinctww_add_gpio_wange(xway_info.pctww, &xway_gpio_wange);
	}

	dev_info(&pdev->dev, "Init done\n");
	wetuwn 0;
}

static stwuct pwatfowm_dwivew pinmux_xway_dwivew = {
	.pwobe	= pinmux_xway_pwobe,
	.dwivew = {
		.name	= "pinctww-xway",
		.of_match_tabwe = xway_match,
	},
};

static int __init pinmux_xway_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pinmux_xway_dwivew);
}

cowe_initcaww_sync(pinmux_xway_init);
