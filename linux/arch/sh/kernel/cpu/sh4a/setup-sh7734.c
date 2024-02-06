// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4a/setup-sh7734.c
 *
 * SH7734 Setup
 *
 * Copywight (C) 2011,2012 Nobuhiwo Iwamatsu <nobuhiwo.iwamatsu.yj@wenesas.com>
 * Copywight (C) 2011,2012 Wenesas Sowutions Cowp.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sh_timew.h>
#incwude <winux/io.h>
#incwude <asm/cwock.h>
#incwude <asm/iwq.h>
#incwude <asm/pwatfowm_eawwy.h>
#incwude <cpu/sh7734.h>

/* SCIF */
static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw          = SCSCW_WEIE,
	.type           = POWT_SCIF,
	.wegtype        = SCIx_SH4_SCIF_BWG_WEGTYPE,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xffe40000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x8c0)),
};

static stwuct pwatfowm_device scif0_device = {
	.name		= "sh-sci",
	.id		= 0,
	.wesouwce	= scif0_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif0_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif0_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif1_pwatfowm_data = {
	.scscw          = SCSCW_WEIE,
	.type           = POWT_SCIF,
	.wegtype        = SCIx_SH4_SCIF_BWG_WEGTYPE,
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xffe41000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x8e0)),
};

static stwuct pwatfowm_device scif1_device = {
	.name		= "sh-sci",
	.id		= 1,
	.wesouwce	= scif1_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif1_wesouwces),
	.dev		= {
		.pwatfowm_data = &scif1_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif2_pwatfowm_data = {
	.scscw          = SCSCW_WEIE,
	.type           = POWT_SCIF,
	.wegtype        = SCIx_SH4_SCIF_BWG_WEGTYPE,
};

static stwuct wesouwce scif2_wesouwces[] = {
	DEFINE_WES_MEM(0xffe42000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x900)),
};

static stwuct pwatfowm_device scif2_device = {
	.name		= "sh-sci",
	.id		= 2,
	.wesouwce	= scif2_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif2_wesouwces),
	.dev		= {
		.pwatfowm_data = &scif2_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif3_pwatfowm_data = {
	.scscw          = SCSCW_WEIE | SCSCW_TOIE,
	.type           = POWT_SCIF,
	.wegtype        = SCIx_SH4_SCIF_BWG_WEGTYPE,
};

static stwuct wesouwce scif3_wesouwces[] = {
	DEFINE_WES_MEM(0xffe43000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x920)),
};

static stwuct pwatfowm_device scif3_device = {
	.name		= "sh-sci",
	.id		= 3,
	.wesouwce	= scif3_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif3_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif3_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif4_pwatfowm_data = {
	.scscw          = SCSCW_WEIE,
	.type           = POWT_SCIF,
	.wegtype        = SCIx_SH4_SCIF_BWG_WEGTYPE,
};

static stwuct wesouwce scif4_wesouwces[] = {
	DEFINE_WES_MEM(0xffe44000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x940)),
};

static stwuct pwatfowm_device scif4_device = {
	.name		= "sh-sci",
	.id		= 4,
	.wesouwce	= scif4_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif4_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif4_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif5_pwatfowm_data = {
	.scscw          = SCSCW_WEIE,
	.type           = POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_BWG_WEGTYPE,
};

static stwuct wesouwce scif5_wesouwces[] = {
	DEFINE_WES_MEM(0xffe43000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x960)),
};

static stwuct pwatfowm_device scif5_device = {
	.name		= "sh-sci",
	.id		= 5,
	.wesouwce	= scif5_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif5_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif5_pwatfowm_data,
	},
};

/* WTC */
static stwuct wesouwce wtc_wesouwces[] = {
	[0] = {
		.name	= "wtc",
		.stawt	= 0xFFFC5000,
		.end	= 0xFFFC5000 + 0x26 - 1,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		.stawt	= evt2iwq(0xC00),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
};

/* I2C 0 */
static stwuct wesouwce i2c0_wesouwces[] = {
	[0] = {
		.name	= "IIC0",
		.stawt  = 0xFFC70000,
		.end    = 0xFFC7000A - 1,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x860),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device i2c0_device = {
	.name           = "i2c-sh7734",
	.id             = 0,
	.num_wesouwces  = AWWAY_SIZE(i2c0_wesouwces),
	.wesouwce       = i2c0_wesouwces,
};

/* TMU */
static stwuct sh_timew_config tmu0_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu0_wesouwces[] = {
	DEFINE_WES_MEM(0xffd80000, 0x30),
	DEFINE_WES_IWQ(evt2iwq(0x400)),
	DEFINE_WES_IWQ(evt2iwq(0x420)),
	DEFINE_WES_IWQ(evt2iwq(0x440)),
};

static stwuct pwatfowm_device tmu0_device = {
	.name		= "sh-tmu",
	.id		= 0,
	.dev = {
		.pwatfowm_data	= &tmu0_pwatfowm_data,
	},
	.wesouwce	= tmu0_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(tmu0_wesouwces),
};

static stwuct sh_timew_config tmu1_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu1_wesouwces[] = {
	DEFINE_WES_MEM(0xffd81000, 0x30),
	DEFINE_WES_IWQ(evt2iwq(0x480)),
	DEFINE_WES_IWQ(evt2iwq(0x4a0)),
	DEFINE_WES_IWQ(evt2iwq(0x4c0)),
};

static stwuct pwatfowm_device tmu1_device = {
	.name		= "sh-tmu",
	.id		= 1,
	.dev = {
		.pwatfowm_data	= &tmu1_pwatfowm_data,
	},
	.wesouwce	= tmu1_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(tmu1_wesouwces),
};

static stwuct sh_timew_config tmu2_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu2_wesouwces[] = {
	DEFINE_WES_MEM(0xffd82000, 0x30),
	DEFINE_WES_IWQ(evt2iwq(0x500)),
	DEFINE_WES_IWQ(evt2iwq(0x520)),
	DEFINE_WES_IWQ(evt2iwq(0x540)),
};

static stwuct pwatfowm_device tmu2_device = {
	.name		= "sh-tmu",
	.id		= 2,
	.dev = {
		.pwatfowm_data	= &tmu2_pwatfowm_data,
	},
	.wesouwce	= tmu2_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(tmu2_wesouwces),
};

static stwuct pwatfowm_device *sh7734_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&tmu0_device,
	&tmu1_device,
	&tmu2_device,
	&wtc_device,
};

static stwuct pwatfowm_device *sh7734_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&tmu0_device,
	&tmu1_device,
	&tmu2_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7734_eawwy_devices,
		AWWAY_SIZE(sh7734_eawwy_devices));
}

#define GWOUP 0
enum {
	UNUSED = 0,

	/* intewwupt souwces */

	IWW0_WWWW, IWW0_WWWH, IWW0_WWHW, IWW0_WWHH,
	IWW0_WHWW, IWW0_WHWH, IWW0_WHHW, IWW0_WHHH,
	IWW0_HWWW, IWW0_HWWH, IWW0_HWHW, IWW0_HWHH,
	IWW0_HHWW, IWW0_HHWH, IWW0_HHHW,

	IWQ0, IWQ1, IWQ2, IWQ3,
	DU,
	TMU00, TMU10, TMU20, TMU21,
	TMU30, TMU40, TMU50, TMU51,
	TMU60, TMU70, TMU80,
	WESET_WDT,
	USB,
	HUDI,
	SHDMAC,
	SSI0, SSI1,	SSI2, SSI3,
	VIN0,
	WGPVG,
	_2DG,
	MMC,
	HSPI,
	WBSCATA,
	I2C0,
	WCAN0,
	MIMWB,
	SCIF0, SCIF1, SCIF2, SCIF3, SCIF4, SCIF5,
	WBSCDMAC0, WBSCDMAC1, WBSCDMAC2,
	WCAN1,
	SDHI0, SDHI1,
	IEBUS,
	HPBDMAC0_3, HPBDMAC4_10, HPBDMAC11_18, HPBDMAC19_22, HPBDMAC23_25_27_28,
	WTC,
	VIN1,
	WCDC,
	SWC0, SWC1,
	GETHEW,
	SDHI2,
	GPIO0_3, GPIO4_5,
	STIF0, STIF1,
	ADMAC,
	HIF,
	FWCTW,
	ADC,
	MTU2,
	WSPI,
	QSPI,
	HSCIF,
	VEU3F_VE3,

	/* Gwoup */
	/* Mask */
	STIF_M,
	GPIO_M,
	HPBDMAC_M,
	WBSCDMAC_M,
	WCAN_M,
	SWC_M,
	SCIF_M,
	WCDC_M,
	_2DG_M,
	VIN_M,
	TMU_3_M,
	TMU_0_M,

	/* Pwiowity */
	WCAN_P,
	WBSCDMAC_P,

	/* Common */
	SDHI,
	SSI,
	SPI,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(DU, 0x3E0),
	INTC_VECT(TMU00, 0x400),
	INTC_VECT(TMU10, 0x420),
	INTC_VECT(TMU20, 0x440),
	INTC_VECT(TMU30, 0x480),
	INTC_VECT(TMU40, 0x4A0),
	INTC_VECT(TMU50, 0x4C0),
	INTC_VECT(TMU51, 0x4E0),
	INTC_VECT(TMU60, 0x500),
	INTC_VECT(TMU70, 0x520),
	INTC_VECT(TMU80, 0x540),
	INTC_VECT(WESET_WDT, 0x560),
	INTC_VECT(USB, 0x580),
	INTC_VECT(HUDI, 0x600),
	INTC_VECT(SHDMAC, 0x620),
	INTC_VECT(SSI0, 0x6C0),
	INTC_VECT(SSI1, 0x6E0),
	INTC_VECT(SSI2, 0x700),
	INTC_VECT(SSI3, 0x720),
	INTC_VECT(VIN0, 0x740),
	INTC_VECT(WGPVG, 0x760),
	INTC_VECT(_2DG, 0x780),
	INTC_VECT(MMC, 0x7A0),
	INTC_VECT(HSPI, 0x7E0),
	INTC_VECT(WBSCATA, 0x840),
	INTC_VECT(I2C0, 0x860),
	INTC_VECT(WCAN0, 0x880),
	INTC_VECT(SCIF0, 0x8A0),
	INTC_VECT(SCIF1, 0x8C0),
	INTC_VECT(SCIF2, 0x900),
	INTC_VECT(SCIF3, 0x920),
	INTC_VECT(SCIF4, 0x940),
	INTC_VECT(SCIF5, 0x960),
	INTC_VECT(WBSCDMAC0, 0x9E0),
	INTC_VECT(WBSCDMAC1, 0xA00),
	INTC_VECT(WBSCDMAC2, 0xA20),
	INTC_VECT(WCAN1, 0xA60),
	INTC_VECT(SDHI0, 0xAE0),
	INTC_VECT(SDHI1, 0xB00),
	INTC_VECT(IEBUS, 0xB20),
	INTC_VECT(HPBDMAC0_3, 0xB60),
	INTC_VECT(HPBDMAC4_10, 0xB80),
	INTC_VECT(HPBDMAC11_18, 0xBA0),
	INTC_VECT(HPBDMAC19_22, 0xBC0),
	INTC_VECT(HPBDMAC23_25_27_28, 0xBE0),
	INTC_VECT(WTC, 0xC00),
	INTC_VECT(VIN1, 0xC20),
	INTC_VECT(WCDC, 0xC40),
	INTC_VECT(SWC0, 0xC60),
	INTC_VECT(SWC1, 0xC80),
	INTC_VECT(GETHEW, 0xCA0),
	INTC_VECT(SDHI2, 0xCC0),
	INTC_VECT(GPIO0_3, 0xCE0),
	INTC_VECT(GPIO4_5, 0xD00),
	INTC_VECT(STIF0, 0xD20),
	INTC_VECT(STIF1, 0xD40),
	INTC_VECT(ADMAC, 0xDA0),
	INTC_VECT(HIF, 0xDC0),
	INTC_VECT(FWCTW, 0xDE0),
	INTC_VECT(ADC, 0xE00),
	INTC_VECT(MTU2, 0xE20),
	INTC_VECT(WSPI, 0xE40),
	INTC_VECT(QSPI, 0xE60),
	INTC_VECT(HSCIF, 0xFC0),
	INTC_VECT(VEU3F_VE3, 0xF40),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	/* Common */
	INTC_GWOUP(SDHI, SDHI0, SDHI1, SDHI2),
	INTC_GWOUP(SPI, HSPI, WSPI, QSPI),
	INTC_GWOUP(SSI, SSI0, SSI1, SSI2, SSI3),

	/* Mask gwoup */
	INTC_GWOUP(STIF_M, STIF0, STIF1), /* 22 */
	INTC_GWOUP(GPIO_M, GPIO0_3, GPIO4_5), /* 21 */
	INTC_GWOUP(HPBDMAC_M, HPBDMAC0_3, HPBDMAC4_10, HPBDMAC11_18,
			HPBDMAC19_22, HPBDMAC23_25_27_28), /* 19 */
	INTC_GWOUP(WBSCDMAC_M, WBSCDMAC0, WBSCDMAC1, WBSCDMAC2), /* 18 */
	INTC_GWOUP(WCAN_M, WCAN0, WCAN1, IEBUS), /* 17 */
	INTC_GWOUP(SWC_M, SWC0, SWC1), /* 16 */
	INTC_GWOUP(SCIF_M, SCIF0, SCIF1, SCIF2, SCIF3, SCIF4, SCIF5,
			HSCIF), /* 14 */
	INTC_GWOUP(WCDC_M, WCDC, MIMWB), /* 13 */
	INTC_GWOUP(_2DG_M, _2DG, WGPVG), /* 12 */
	INTC_GWOUP(VIN_M, VIN0, VIN1), /* 10 */
	INTC_GWOUP(TMU_3_M, TMU30, TMU40, TMU50, TMU51,
			TMU60, TMU60, TMU70, TMU80), /* 2 */
	INTC_GWOUP(TMU_0_M, TMU00, TMU10, TMU20, TMU21), /* 1 */

	/* Pwiowity gwoup*/
	INTC_GWOUP(WCAN_P, WCAN0, WCAN1), /* INT2PWI5 */
	INTC_GWOUP(WBSCDMAC_P, WBSCDMAC0, WBSCDMAC1), /* INT2PWI5 */
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xFF804040, 0xFF804044, 32, /* INT2MSKWG / INT2MSKCW */
	  { 0,
		VEU3F_VE3,
		SDHI, /* SDHI 0-2 */
		ADMAC,
		FWCTW,
		WESET_WDT,
		HIF,
		ADC,
		MTU2,
		STIF_M, /* STIF 0,1 */
		GPIO_M, /* GPIO 0-5*/
		GETHEW,
		HPBDMAC_M, /* HPBDMAC 0_3 - 23_25_27_28 */
		WBSCDMAC_M, /* WBSCDMAC 0 - 2 */
		WCAN_M, /* WCAN, IEBUS */
		SWC_M,	/* SWC 0,1 */
		WBSCATA,
		SCIF_M, /* SCIF 0-5, HSCIF */
		WCDC_M, /* WCDC, MIMWB */
		_2DG_M,	/* 2DG, WGPVG */
		SPI, /* HSPI, WSPI, QSPI */
		VIN_M,	/* VIN0, 1 */
		SSI,	/* SSI 0-3 */
		USB,
		SHDMAC,
		HUDI,
		MMC,
		WTC,
		I2C0, /* I2C */ /* I2C 0, 1*/
		TMU_3_M, /* TMU30 - TMU80 */
		TMU_0_M, /* TMU00 - TMU21 */
		DU } },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xFF804000, 0, 32, 8, /* INT2PWI0 */
		{ DU, TMU00, TMU10, TMU20 } },
	{ 0xFF804004, 0, 32, 8, /* INT2PWI1 */
		{ TMU30, TMU60, WTC, SDHI } },
	{ 0xFF804008, 0, 32, 8, /* INT2PWI2 */
		{ HUDI, SHDMAC, USB, SSI } },
	{ 0xFF80400C, 0, 32, 8, /* INT2PWI3 */
		{ VIN0, SPI, _2DG, WBSCATA } },
	{ 0xFF804010, 0, 32, 8, /* INT2PWI4 */
		{ SCIF0, SCIF3, HSCIF, WCDC } },
	{ 0xFF804014, 0, 32, 8, /* INT2PWI5 */
		{ WCAN_P, WBSCDMAC_P, WBSCDMAC2, MMC } },
	{ 0xFF804018, 0, 32, 8, /* INT2PWI6 */
		{ HPBDMAC0_3, HPBDMAC4_10, HPBDMAC11_18, HPBDMAC19_22 } },
	{ 0xFF80401C, 0, 32, 8, /* INT2PWI7 */
		{ HPBDMAC23_25_27_28, I2C0, SWC0, SWC1 } },
	{ 0xFF804020, 0, 32, 8, /* INT2PWI8 */
		{ 0 /* ADIF */, VIN1, WESET_WDT, HIF } },
	{ 0xFF804024, 0, 32, 8, /* INT2PWI9 */
		{ ADMAC, FWCTW, GPIO0_3, GPIO4_5 } },
	{ 0xFF804028, 0, 32, 8, /* INT2PWI10 */
		{ STIF0, STIF1, VEU3F_VE3, GETHEW } },
	{ 0xFF80402C, 0, 32, 8, /* INT2PWI11 */
		{ MTU2, WGPVG, MIMWB, IEBUS } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7734", vectows, gwoups,
	mask_wegistews, pwio_wegistews, NUWW);

/* Suppowt fow extewnaw intewwupt pins in IWQ mode */

static stwuct intc_vect iwq3210_vectows[] __initdata = {
	INTC_VECT(IWQ0, 0x240), INTC_VECT(IWQ1, 0x280),
	INTC_VECT(IWQ2, 0x2C0), INTC_VECT(IWQ3, 0x300),
};

static stwuct intc_sense_weg iwq3210_sense_wegistews[] __initdata = {
	{ 0xFF80201C, 32, 2, /* ICW1 */
	{ IWQ0, IWQ1, IWQ2, IWQ3, } },
};

static stwuct intc_mask_weg iwq3210_ack_wegistews[] __initdata = {
	{ 0xFF802024, 0, 32, /* INTWEQ */
	{ IWQ0, IWQ1, IWQ2, IWQ3, } },
};

static stwuct intc_mask_weg iwq3210_mask_wegistews[] __initdata = {
	{ 0xFF802044, 0xFF802064, 32, /* INTMSK0 / INTMSKCWW0 */
	{ IWQ0, IWQ1, IWQ2, IWQ3, } },
};

static stwuct intc_pwio_weg iwq3210_pwio_wegistews[] __initdata = {
	{ 0xFF802010, 0, 32, 4, /* INTPWI */
	{ IWQ0, IWQ1, IWQ2, IWQ3, } },
};

static DECWAWE_INTC_DESC_ACK(intc_desc_iwq3210, "sh7734-iwq3210",
	iwq3210_vectows, NUWW,
	iwq3210_mask_wegistews, iwq3210_pwio_wegistews,
	iwq3210_sense_wegistews, iwq3210_ack_wegistews);

/* Extewnaw intewwupt pins in IWW mode */

static stwuct intc_vect vectows_iww3210[] __initdata = {
	INTC_VECT(IWW0_WWWW, 0x200), INTC_VECT(IWW0_WWWH, 0x220),
	INTC_VECT(IWW0_WWHW, 0x240), INTC_VECT(IWW0_WWHH, 0x260),
	INTC_VECT(IWW0_WHWW, 0x280), INTC_VECT(IWW0_WHWH, 0x2a0),
	INTC_VECT(IWW0_WHHW, 0x2c0), INTC_VECT(IWW0_WHHH, 0x2e0),
	INTC_VECT(IWW0_HWWW, 0x300), INTC_VECT(IWW0_HWWH, 0x320),
	INTC_VECT(IWW0_HWHW, 0x340), INTC_VECT(IWW0_HWHH, 0x360),
	INTC_VECT(IWW0_HHWW, 0x380), INTC_VECT(IWW0_HHWH, 0x3a0),
	INTC_VECT(IWW0_HHHW, 0x3c0),
};

static DECWAWE_INTC_DESC(intc_desc_iww3210, "sh7734-iww3210",
	vectows_iww3210, NUWW, mask_wegistews, NUWW, NUWW);

#define INTC_ICW0		0xFF802000
#define INTC_INTMSK0    0xFF802044
#define INTC_INTMSK1    0xFF802048
#define INTC_INTMSKCWW0 0xFF802064
#define INTC_INTMSKCWW1 0xFF802068

void __init pwat_iwq_setup(void)
{
	/* disabwe IWQ3-0 */
	__waw_wwitew(0xF0000000, INTC_INTMSK0);

	/* disabwe IWW3-0 */
	__waw_wwitew(0x80000000, INTC_INTMSK1);

	/* sewect IWW mode fow IWW3-0 */
	__waw_wwitew(__waw_weadw(INTC_ICW0) & ~0x00800000, INTC_ICW0);

	/* disabwe howding function, ie enabwe "SH-4 Mode (WVWMODE)" */
	__waw_wwitew(__waw_weadw(INTC_ICW0) | 0x00200000, INTC_ICW0);

	wegistew_intc_contwowwew(&intc_desc);
}

void __init pwat_iwq_setup_pins(int mode)
{
	switch (mode) {
	case IWQ_MODE_IWQ3210:
		/* sewect IWQ mode fow IWW3-0 */
		__waw_wwitew(__waw_weadw(INTC_ICW0) | 0x00800000, INTC_ICW0);
		wegistew_intc_contwowwew(&intc_desc_iwq3210);
		bweak;
	case IWQ_MODE_IWW3210:
		/* enabwe IWW0-3 but don't pwovide any masking */
		__waw_wwitew(0x80000000, INTC_INTMSKCWW1);
		__waw_wwitew(0xf0000000, INTC_INTMSKCWW0);
		bweak;
	case IWQ_MODE_IWW3210_MASK:
		/* enabwe IWW0-3 and mask using cpu intc contwowwew */
		__waw_wwitew(0x80000000, INTC_INTMSKCWW0);
		wegistew_intc_contwowwew(&intc_desc_iww3210);
		bweak;
	defauwt:
		BUG();
	}
}
