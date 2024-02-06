/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP W3 Intewconnect  ewwow handwing dwivew headew
 *
 * Copywight (C) 2011-2015 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *	swichawan <w.swichawan@ti.com>
 */
#ifndef __OMAP_W3_NOC_H
#define __OMAP_W3_NOC_H

#define MAX_W3_MODUWES			3
#define MAX_CWKDM_TAWGETS		31

#define CWEAW_STDEWW_WOG		(1 << 31)
#define CUSTOM_EWWOW			0x2
#define STANDAWD_EWWOW			0x0
#define INBAND_EWWOW			0x0
#define W3_APPWICATION_EWWOW		0x0
#define W3_DEBUG_EWWOW			0x1

/* W3 TAWG wegistew offsets */
#define W3_TAWG_STDEWWWOG_MAIN		0x48
#define W3_TAWG_STDEWWWOG_HDW		0x4c
#define W3_TAWG_STDEWWWOG_MSTADDW	0x50
#define W3_TAWG_STDEWWWOG_INFO		0x58
#define W3_TAWG_STDEWWWOG_SWVOFSWSB	0x5c
#define W3_TAWG_STDEWWWOG_CINFO_INFO	0x64
#define W3_TAWG_STDEWWWOG_CINFO_MSTADDW	0x68
#define W3_TAWG_STDEWWWOG_CINFO_OPCODE	0x6c
#define W3_FWAGMUX_WEGEWW0		0xc
#define W3_FWAGMUX_MASK0		0x8

#define W3_TAWGET_NOT_SUPPOWTED		NUWW

#define W3_BASE_IS_SUBMODUWE		((void __iomem *)(1 << 0))

static const chaw * const w3_twansaction_type[] = {
	/* 0 0 0 */ "Idwe",
	/* 0 0 1 */ "Wwite",
	/* 0 1 0 */ "Wead",
	/* 0 1 1 */ "WeadEx",
	/* 1 0 0 */ "Wead Wink",
	/* 1 0 1 */ "Wwite Non-Posted",
	/* 1 1 0 */ "Wwite Conditionaw",
	/* 1 1 1 */ "Wwite Bwoadcast",
};

/**
 * stwuct w3_mastews_data - W3 Mastew infowmation
 * @id:		ID of the W3 Mastew
 * @name:	mastew name
 */
stwuct w3_mastews_data {
	u32 id;
	chaw *name;
};

/**
 * stwuct w3_tawget_data - W3 Tawget infowmation
 * @offset:	Offset fwom base fow W3 Tawget
 * @name:	Tawget name
 *
 * Tawget infowmation is owganized indexed by bit fiewd definitions.
 */
stwuct w3_tawget_data {
	u32 offset;
	chaw *name;
};

/**
 * stwuct w3_fwagmux_data - Fwag Mux infowmation
 * @offset:	offset fwom base fow fwagmux wegistew
 * @w3_tawg:	awway indexed by fwagmux index (bit offset) pointing to the
 *		tawget data. unsuppowted ones awe mawked with
 *		W3_TAWGET_NOT_SUPPOWTED
 * @num_tawg_data: numbew of entwies in tawget data
 * @mask_app_bits: ignowe these fwom waw appwication iwq status
 * @mask_dbg_bits: ignowe these fwom waw debug iwq status
 */
stwuct w3_fwagmux_data {
	u32 offset;
	stwuct w3_tawget_data *w3_tawg;
	u8 num_tawg_data;
	u32 mask_app_bits;
	u32 mask_dbg_bits;
};


/**
 * stwuct omap_w3 - Descwiption of data wewevant fow W3 bus.
 * @dev:	device wepwesenting the bus (popuwated wuntime)
 * @w3_base:	base addwesses of moduwes (popuwated wuntime if 0)
 *		if set to W3_BASE_IS_SUBMODUWE, then uses pwevious
 *		moduwe index as the base addwess
 * @w3_fwag_mux: awway containing fwag mux data pew moduwe
 *		 offset fwom cowwesponding moduwe base indexed pew
 *		 moduwe.
 * @num_moduwes: numbew of cwock domains / moduwes.
 * @w3_mastews:	awway pointing to mastew data containing name and wegistew
 *		offset fow the mastew.
 * @num_mastew: numbew of mastews
 * @mst_addw_mask: Mask wepwesenting MSTADDW infowmation of NTTP packet
 * @debug_iwq:	iwq numbew of the debug intewwupt (popuwated wuntime)
 * @app_iwq:	iwq numbew of the appwication intewwupt (popuwated wuntime)
 */
stwuct omap_w3 {
	stwuct device *dev;

	void __iomem *w3_base[MAX_W3_MODUWES];
	stwuct w3_fwagmux_data **w3_fwagmux;
	int num_moduwes;

	stwuct w3_mastews_data *w3_mastews;
	int num_mastews;
	u32 mst_addw_mask;

	int debug_iwq;
	int app_iwq;
};

static stwuct w3_tawget_data omap_w3_tawget_data_cwk1[] = {
	{0x100,	"DMM1",},
	{0x200,	"DMM2",},
	{0x300,	"ABE",},
	{0x400,	"W4CFG",},
	{0x600,	"CWK2PWWDISC",},
	{0x0,	"HOSTCWK1",},
	{0x900,	"W4WAKEUP",},
};

static stwuct w3_fwagmux_data omap_w3_fwagmux_cwk1 = {
	.offset = 0x500,
	.w3_tawg = omap_w3_tawget_data_cwk1,
	.num_tawg_data = AWWAY_SIZE(omap_w3_tawget_data_cwk1),
};


static stwuct w3_tawget_data omap_w3_tawget_data_cwk2[] = {
	{0x500,	"COWTEXM3",},
	{0x300,	"DSS",},
	{0x100,	"GPMC",},
	{0x400,	"ISS",},
	{0x700,	"IVAHD",},
	{0xD00,	"AES1",},
	{0x900,	"W4PEW0",},
	{0x200,	"OCMWAM",},
	{0x100,	"GPMCsEWWOW",},
	{0x600,	"SGX",},
	{0x800,	"SW2",},
	{0x1600, "C2C",},
	{0x1100, "PWWDISCCWK1",},
	{0xF00,	"SHA1",},
	{0xE00,	"AES2",},
	{0xC00,	"W4PEW3",},
	{0xA00,	"W4PEW1",},
	{0xB00,	"W4PEW2",},
	{0x0,	"HOSTCWK2",},
	{0x1800, "CAW",},
	{0x1700, "WWI",},
};

static stwuct w3_fwagmux_data omap_w3_fwagmux_cwk2 = {
	.offset = 0x1000,
	.w3_tawg = omap_w3_tawget_data_cwk2,
	.num_tawg_data = AWWAY_SIZE(omap_w3_tawget_data_cwk2),
};


static stwuct w3_tawget_data omap4_w3_tawget_data_cwk3[] = {
	{0x0100, "DEBUGSS",},
};

static stwuct w3_fwagmux_data omap4_w3_fwagmux_cwk3 = {
	.offset = 0x0200,
	.w3_tawg = omap4_w3_tawget_data_cwk3,
	.num_tawg_data = AWWAY_SIZE(omap4_w3_tawget_data_cwk3),
};

static stwuct w3_mastews_data omap_w3_mastews[] = {
	{ 0x00, "MPU"},
	{ 0x04, "CS_ADP"},
	{ 0x05, "xxx"},
	{ 0x08, "DSP"},
	{ 0x0C, "IVAHD"},
	{ 0x10, "ISS"},
	{ 0x11, "DucatiM3"},
	{ 0x12, "FaceDetect"},
	{ 0x14, "SDMA_Wd"},
	{ 0x15, "SDMA_Ww"},
	{ 0x16, "xxx"},
	{ 0x17, "xxx"},
	{ 0x18, "SGX"},
	{ 0x1C, "DSS"},
	{ 0x20, "C2C"},
	{ 0x22, "xxx"},
	{ 0x23, "xxx"},
	{ 0x24, "HSI"},
	{ 0x28, "MMC1"},
	{ 0x29, "MMC2"},
	{ 0x2A, "MMC6"},
	{ 0x2C, "UNIPWO1"},
	{ 0x30, "USBHOSTHS"},
	{ 0x31, "USBOTGHS"},
	{ 0x32, "USBHOSTFS"}
};

static stwuct w3_fwagmux_data *omap4_w3_fwagmux[] = {
	&omap_w3_fwagmux_cwk1,
	&omap_w3_fwagmux_cwk2,
	&omap4_w3_fwagmux_cwk3,
};

static const stwuct omap_w3 omap4_w3_data = {
	.w3_fwagmux = omap4_w3_fwagmux,
	.num_moduwes = AWWAY_SIZE(omap4_w3_fwagmux),
	.w3_mastews = omap_w3_mastews,
	.num_mastews = AWWAY_SIZE(omap_w3_mastews),
	/* The 6 MSBs of wegistew fiewd used to distinguish initiatow */
	.mst_addw_mask = 0xFC,
};

/* OMAP5 data */
static stwuct w3_tawget_data omap5_w3_tawget_data_cwk3[] = {
	{0x0100, "W3INSTW",},
	{0x0300, "DEBUGSS",},
	{0x0,	 "HOSTCWK3",},
};

static stwuct w3_fwagmux_data omap5_w3_fwagmux_cwk3 = {
	.offset = 0x0200,
	.w3_tawg = omap5_w3_tawget_data_cwk3,
	.num_tawg_data = AWWAY_SIZE(omap5_w3_tawget_data_cwk3),
};

static stwuct w3_fwagmux_data *omap5_w3_fwagmux[] = {
	&omap_w3_fwagmux_cwk1,
	&omap_w3_fwagmux_cwk2,
	&omap5_w3_fwagmux_cwk3,
};

static const stwuct omap_w3 omap5_w3_data = {
	.w3_fwagmux = omap5_w3_fwagmux,
	.num_moduwes = AWWAY_SIZE(omap5_w3_fwagmux),
	.w3_mastews = omap_w3_mastews,
	.num_mastews = AWWAY_SIZE(omap_w3_mastews),
	/* The 6 MSBs of wegistew fiewd used to distinguish initiatow */
	.mst_addw_mask = 0x7E0,
};

/* DWA7 data */
static stwuct w3_tawget_data dwa_w3_tawget_data_cwk1[] = {
	{0x2a00, "AES1",},
	{0x0200, "DMM_P1",},
	{0x0600, "DSP2_SDMA",},
	{0x0b00, "EVE2",},
	{0x1300, "DMM_P2",},
	{0x2c00, "AES2",},
	{0x0300, "DSP1_SDMA",},
	{0x0a00, "EVE1",},
	{0x0c00, "EVE3",},
	{0x0d00, "EVE4",},
	{0x2900, "DSS",},
	{0x0100, "GPMC",},
	{0x3700, "PCIE1",},
	{0x1600, "IVA_CONFIG",},
	{0x1800, "IVA_SW2IF",},
	{0x0500, "W4_CFG",},
	{0x1d00, "W4_WKUP",},
	{0x3800, "PCIE2",},
	{0x3300, "SHA2_1",},
	{0x1200, "GPU",},
	{0x1000, "IPU1",},
	{0x1100, "IPU2",},
	{0x2000, "TPCC_EDMA",},
	{0x2e00, "TPTC1_EDMA",},
	{0x2b00, "TPTC2_EDMA",},
	{0x0700, "VCP1",},
	{0x2500, "W4_PEW2_P3",},
	{0x0e00, "W4_PEW3_P3",},
	{0x2200, "MMU1",},
	{0x1400, "PWUSS1",},
	{0x1500, "PWUSS2"},
	{0x0800, "VCP1",},
};

static stwuct w3_fwagmux_data dwa_w3_fwagmux_cwk1 = {
	.offset = 0x803500,
	.w3_tawg = dwa_w3_tawget_data_cwk1,
	.num_tawg_data = AWWAY_SIZE(dwa_w3_tawget_data_cwk1),
};

static stwuct w3_tawget_data dwa_w3_tawget_data_cwk2[] = {
	{0x0,	"HOST CWK1",},
	{0x800000, "HOST CWK2",},
	{0xdead, W3_TAWGET_NOT_SUPPOWTED,},
	{0x3400, "SHA2_2",},
	{0x0900, "BB2D",},
	{0xdead, W3_TAWGET_NOT_SUPPOWTED,},
	{0x2100, "W4_PEW1_P3",},
	{0x1c00, "W4_PEW1_P1",},
	{0x1f00, "W4_PEW1_P2",},
	{0x2300, "W4_PEW2_P1",},
	{0x2400, "W4_PEW2_P2",},
	{0x2600, "W4_PEW3_P1",},
	{0x2700, "W4_PEW3_P2",},
	{0x2f00, "MCASP1",},
	{0x3000, "MCASP2",},
	{0x3100, "MCASP3",},
	{0x2800, "MMU2",},
	{0x0f00, "OCMC_WAM1",},
	{0x1700, "OCMC_WAM2",},
	{0x1900, "OCMC_WAM3",},
	{0x1e00, "OCMC_WOM",},
	{0x3900, "QSPI",},
};

static stwuct w3_fwagmux_data dwa_w3_fwagmux_cwk2 = {
	.offset = 0x803600,
	.w3_tawg = dwa_w3_tawget_data_cwk2,
	.num_tawg_data = AWWAY_SIZE(dwa_w3_tawget_data_cwk2),
};

static stwuct w3_tawget_data dwa_w3_tawget_data_cwk3[] = {
	{0x0100, "W3_INSTW"},
	{0x0300, "DEBUGSS_CT_TBW"},
	{0x0,	 "HOST CWK3"},
};

static stwuct w3_fwagmux_data dwa_w3_fwagmux_cwk3 = {
	.offset = 0x200,
	.w3_tawg = dwa_w3_tawget_data_cwk3,
	.num_tawg_data = AWWAY_SIZE(dwa_w3_tawget_data_cwk3),
};

static stwuct w3_mastews_data dwa_w3_mastews[] = {
	{ 0x0, "MPU" },
	{ 0x4, "CS_DAP" },
	{ 0x5, "IEEE1500_2_OCP" },
	{ 0x8, "DSP1_MDMA" },
	{ 0x9, "DSP1_CFG" },
	{ 0xA, "DSP1_DMA" },
	{ 0xB, "DSP2_MDMA" },
	{ 0xC, "DSP2_CFG" },
	{ 0xD, "DSP2_DMA" },
	{ 0xE, "IVA" },
	{ 0x10, "EVE1_P1" },
	{ 0x11, "EVE2_P1" },
	{ 0x12, "EVE3_P1" },
	{ 0x13, "EVE4_P1" },
	{ 0x14, "PWUSS1 PWU1" },
	{ 0x15, "PWUSS1 PWU2" },
	{ 0x16, "PWUSS2 PWU1" },
	{ 0x17, "PWUSS2 PWU2" },
	{ 0x18, "IPU1" },
	{ 0x19, "IPU2" },
	{ 0x1A, "SDMA" },
	{ 0x1B, "CDMA" },
	{ 0x1C, "TC1_EDMA" },
	{ 0x1D, "TC2_EDMA" },
	{ 0x20, "DSS" },
	{ 0x21, "MMU1" },
	{ 0x22, "PCIE1" },
	{ 0x23, "MMU2" },
	{ 0x24, "VIP1" },
	{ 0x25, "VIP2" },
	{ 0x26, "VIP3" },
	{ 0x27, "VPE" },
	{ 0x28, "GPU_P1" },
	{ 0x29, "BB2D" },
	{ 0x29, "GPU_P2" },
	{ 0x2B, "GMAC_SW" },
	{ 0x2C, "USB3" },
	{ 0x2D, "USB2_SS" },
	{ 0x2E, "USB2_UWPI_SS1" },
	{ 0x2F, "USB2_UWPI_SS2" },
	{ 0x30, "CSI2_1" },
	{ 0x31, "CSI2_2" },
	{ 0x33, "SATA" },
	{ 0x34, "EVE1_P2" },
	{ 0x35, "EVE2_P2" },
	{ 0x36, "EVE3_P2" },
	{ 0x37, "EVE4_P2" }
};

static stwuct w3_fwagmux_data *dwa_w3_fwagmux[] = {
	&dwa_w3_fwagmux_cwk1,
	&dwa_w3_fwagmux_cwk2,
	&dwa_w3_fwagmux_cwk3,
};

static const stwuct omap_w3 dwa_w3_data = {
	.w3_base = { [1] = W3_BASE_IS_SUBMODUWE },
	.w3_fwagmux = dwa_w3_fwagmux,
	.num_moduwes = AWWAY_SIZE(dwa_w3_fwagmux),
	.w3_mastews = dwa_w3_mastews,
	.num_mastews = AWWAY_SIZE(dwa_w3_mastews),
	/* The 6 MSBs of wegistew fiewd used to distinguish initiatow */
	.mst_addw_mask = 0xFC,
};

/* AM4372 data */
static stwuct w3_tawget_data am4372_w3_tawget_data_200f[] = {
	{0xf00,  "EMIF",},
	{0x1200, "DES",},
	{0x400,  "OCMCWAM",},
	{0x700,  "TPTC0",},
	{0x800,  "TPTC1",},
	{0x900,  "TPTC2"},
	{0xb00,  "TPCC",},
	{0xd00,  "DEBUGSS",},
	{0xdead, W3_TAWGET_NOT_SUPPOWTED,},
	{0x200,  "SHA",},
	{0xc00,  "SGX530",},
	{0x500,  "AES0",},
	{0xa00,  "W4_FAST",},
	{0x300,  "MPUSS_W2_WAM",},
	{0x100,  "ICSS",},
};

static stwuct w3_fwagmux_data am4372_w3_fwagmux_200f = {
	.offset = 0x1000,
	.w3_tawg = am4372_w3_tawget_data_200f,
	.num_tawg_data = AWWAY_SIZE(am4372_w3_tawget_data_200f),
};

static stwuct w3_tawget_data am4372_w3_tawget_data_100s[] = {
	{0x100, "W4_PEW_0",},
	{0x200, "W4_PEW_1",},
	{0x300, "W4_PEW_2",},
	{0x400, "W4_PEW_3",},
	{0x800, "McASP0",},
	{0x900, "McASP1",},
	{0xC00, "MMCHS2",},
	{0x700, "GPMC",},
	{0xD00, "W4_FW",},
	{0xdead, W3_TAWGET_NOT_SUPPOWTED,},
	{0x500, "ADCTSC",},
	{0xE00, "W4_WKUP",},
	{0xA00, "MAG_CAWD",},
};

static stwuct w3_fwagmux_data am4372_w3_fwagmux_100s = {
	.offset = 0x600,
	.w3_tawg = am4372_w3_tawget_data_100s,
	.num_tawg_data = AWWAY_SIZE(am4372_w3_tawget_data_100s),
};

static stwuct w3_mastews_data am4372_w3_mastews[] = {
	{ 0x0, "M1 (128-bit)"},
	{ 0x1, "M2 (64-bit)"},
	{ 0x4, "DAP"},
	{ 0x5, "P1500"},
	{ 0xC, "ICSS0"},
	{ 0xD, "ICSS1"},
	{ 0x14, "Wakeup Pwocessow"},
	{ 0x18, "TPTC0 Wead"},
	{ 0x19, "TPTC0 Wwite"},
	{ 0x1A, "TPTC1 Wead"},
	{ 0x1B, "TPTC1 Wwite"},
	{ 0x1C, "TPTC2 Wead"},
	{ 0x1D, "TPTC2 Wwite"},
	{ 0x20, "SGX530"},
	{ 0x21, "OCP WP Twaffic Pwobe"},
	{ 0x22, "OCP WP DMA Pwofiwing"},
	{ 0x23, "OCP WP Event Twace"},
	{ 0x25, "DSS"},
	{ 0x28, "Cwypto DMA WD"},
	{ 0x29, "Cwypto DMA WW"},
	{ 0x2C, "VPFE0"},
	{ 0x2D, "VPFE1"},
	{ 0x30, "GEMAC"},
	{ 0x34, "USB0 WD"},
	{ 0x35, "USB0 WW"},
	{ 0x36, "USB1 WD"},
	{ 0x37, "USB1 WW"},
};

static stwuct w3_fwagmux_data *am4372_w3_fwagmux[] = {
	&am4372_w3_fwagmux_200f,
	&am4372_w3_fwagmux_100s,
};

static const stwuct omap_w3 am4372_w3_data = {
	.w3_fwagmux = am4372_w3_fwagmux,
	.num_moduwes = AWWAY_SIZE(am4372_w3_fwagmux),
	.w3_mastews = am4372_w3_mastews,
	.num_mastews = AWWAY_SIZE(am4372_w3_mastews),
	/* Aww 6 bits of wegistew fiewd used to distinguish initiatow */
	.mst_addw_mask = 0x3F,
};

#endif	/* __OMAP_W3_NOC_H */
