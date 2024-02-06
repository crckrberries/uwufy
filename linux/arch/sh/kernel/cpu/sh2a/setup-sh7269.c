// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7269 Setup
 *
 * Copywight (C) 2012  Wenesas Ewectwonics Euwope Wtd
 * Copywight (C) 2012  Phiw Edwowthy
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/usb/w8a66597.h>
#incwude <winux/sh_timew.h>
#incwude <winux/io.h>
#incwude <asm/pwatfowm_eawwy.h>

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7,
	PINT0, PINT1, PINT2, PINT3, PINT4, PINT5, PINT6, PINT7,

	DMAC0, DMAC1, DMAC2, DMAC3, DMAC4, DMAC5, DMAC6, DMAC7,
	DMAC8, DMAC9, DMAC10, DMAC11, DMAC12, DMAC13, DMAC14, DMAC15,
	USB, VDC4, CMT0, CMT1, BSC, WDT,
	MTU0_ABCD, MTU0_VEF, MTU1_AB, MTU1_VU, MTU2_AB, MTU2_VU,
	MTU3_ABCD, MTU3_TCI3V, MTU4_ABCD, MTU4_TCI4V,
	PWMT1, PWMT2, ADC_ADI,
	SSIF0, SSII1, SSII2, SSII3, SSII4, SSII5,
	WSPDIF,
	IIC30, IIC31, IIC32, IIC33,
	SCIF0_BWI, SCIF0_EWI, SCIF0_WXI, SCIF0_TXI,
	SCIF1_BWI, SCIF1_EWI, SCIF1_WXI, SCIF1_TXI,
	SCIF2_BWI, SCIF2_EWI, SCIF2_WXI, SCIF2_TXI,
	SCIF3_BWI, SCIF3_EWI, SCIF3_WXI, SCIF3_TXI,
	SCIF4_BWI, SCIF4_EWI, SCIF4_WXI, SCIF4_TXI,
	SCIF5_BWI, SCIF5_EWI, SCIF5_WXI, SCIF5_TXI,
	SCIF6_BWI, SCIF6_EWI, SCIF6_WXI, SCIF6_TXI,
	SCIF7_BWI, SCIF7_EWI, SCIF7_WXI, SCIF7_TXI,
	WCAN0, WCAN1, WCAN2,
	WSPIC0, WSPIC1,
	IEBC, CD_WOMD,
	NFMC,
	SDHI0, SDHI1,
	WTC,
	SWCC0, SWCC1, SWCC2,

	/* intewwupt gwoups */
	PINT, SCIF0, SCIF1, SCIF2, SCIF3, SCIF4, SCIF5, SCIF6, SCIF7,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_IWQ(IWQ0, 64), INTC_IWQ(IWQ1, 65),
	INTC_IWQ(IWQ2, 66), INTC_IWQ(IWQ3, 67),
	INTC_IWQ(IWQ4, 68), INTC_IWQ(IWQ5, 69),
	INTC_IWQ(IWQ6, 70), INTC_IWQ(IWQ7, 71),

	INTC_IWQ(PINT0, 80), INTC_IWQ(PINT1, 81),
	INTC_IWQ(PINT2, 82), INTC_IWQ(PINT3, 83),
	INTC_IWQ(PINT4, 84), INTC_IWQ(PINT5, 85),
	INTC_IWQ(PINT6, 86), INTC_IWQ(PINT7, 87),

	INTC_IWQ(DMAC0, 108), INTC_IWQ(DMAC0, 109),
	INTC_IWQ(DMAC1, 112), INTC_IWQ(DMAC1, 113),
	INTC_IWQ(DMAC2, 116), INTC_IWQ(DMAC2, 117),
	INTC_IWQ(DMAC3, 120), INTC_IWQ(DMAC3, 121),
	INTC_IWQ(DMAC4, 124), INTC_IWQ(DMAC4, 125),
	INTC_IWQ(DMAC5, 128), INTC_IWQ(DMAC5, 129),
	INTC_IWQ(DMAC6, 132), INTC_IWQ(DMAC6, 133),
	INTC_IWQ(DMAC7, 136), INTC_IWQ(DMAC7, 137),
	INTC_IWQ(DMAC8, 140), INTC_IWQ(DMAC8, 141),
	INTC_IWQ(DMAC9, 144), INTC_IWQ(DMAC9, 145),
	INTC_IWQ(DMAC10, 148), INTC_IWQ(DMAC10, 149),
	INTC_IWQ(DMAC11, 152), INTC_IWQ(DMAC11, 153),
	INTC_IWQ(DMAC12, 156), INTC_IWQ(DMAC12, 157),
	INTC_IWQ(DMAC13, 160), INTC_IWQ(DMAC13, 161),
	INTC_IWQ(DMAC14, 164), INTC_IWQ(DMAC14, 165),
	INTC_IWQ(DMAC15, 168), INTC_IWQ(DMAC15, 169),

	INTC_IWQ(USB, 170),

	INTC_IWQ(VDC4, 171), INTC_IWQ(VDC4, 172),
	INTC_IWQ(VDC4, 173), INTC_IWQ(VDC4, 174),
	INTC_IWQ(VDC4, 175), INTC_IWQ(VDC4, 176),
	INTC_IWQ(VDC4, 177), INTC_IWQ(VDC4, 177),

	INTC_IWQ(CMT0, 188), INTC_IWQ(CMT1, 189),

	INTC_IWQ(BSC, 190), INTC_IWQ(WDT, 191),

	INTC_IWQ(MTU0_ABCD, 192), INTC_IWQ(MTU0_ABCD, 193),
	INTC_IWQ(MTU0_ABCD, 194), INTC_IWQ(MTU0_ABCD, 195),
	INTC_IWQ(MTU0_VEF, 196), INTC_IWQ(MTU0_VEF, 197),
	INTC_IWQ(MTU0_VEF, 198),
	INTC_IWQ(MTU1_AB, 199), INTC_IWQ(MTU1_AB, 200),
	INTC_IWQ(MTU1_VU, 201), INTC_IWQ(MTU1_VU, 202),
	INTC_IWQ(MTU2_AB, 203), INTC_IWQ(MTU2_AB, 204),
	INTC_IWQ(MTU2_VU, 205), INTC_IWQ(MTU2_VU, 206),
	INTC_IWQ(MTU3_ABCD, 207), INTC_IWQ(MTU3_ABCD, 208),
	INTC_IWQ(MTU3_ABCD, 209), INTC_IWQ(MTU3_ABCD, 210),
	INTC_IWQ(MTU3_TCI3V, 211),
	INTC_IWQ(MTU4_ABCD, 212), INTC_IWQ(MTU4_ABCD, 213),
	INTC_IWQ(MTU4_ABCD, 214), INTC_IWQ(MTU4_ABCD, 215),
	INTC_IWQ(MTU4_TCI4V, 216),

	INTC_IWQ(PWMT1, 217), INTC_IWQ(PWMT2, 218),

	INTC_IWQ(ADC_ADI, 223),

	INTC_IWQ(SSIF0, 224), INTC_IWQ(SSIF0, 225),
	INTC_IWQ(SSIF0, 226),
	INTC_IWQ(SSII1, 227), INTC_IWQ(SSII1, 228),
	INTC_IWQ(SSII2, 229), INTC_IWQ(SSII2, 230),
	INTC_IWQ(SSII3, 231), INTC_IWQ(SSII3, 232),
	INTC_IWQ(SSII4, 233), INTC_IWQ(SSII4, 234),
	INTC_IWQ(SSII5, 235), INTC_IWQ(SSII5, 236),

	INTC_IWQ(WSPDIF, 237),

	INTC_IWQ(IIC30, 238), INTC_IWQ(IIC30, 239),
	INTC_IWQ(IIC30, 240), INTC_IWQ(IIC30, 241),
	INTC_IWQ(IIC30, 242),
	INTC_IWQ(IIC31, 243), INTC_IWQ(IIC31, 244),
	INTC_IWQ(IIC31, 245), INTC_IWQ(IIC31, 246),
	INTC_IWQ(IIC31, 247),
	INTC_IWQ(IIC32, 248), INTC_IWQ(IIC32, 249),
	INTC_IWQ(IIC32, 250), INTC_IWQ(IIC32, 251),
	INTC_IWQ(IIC32, 252),
	INTC_IWQ(IIC33, 253), INTC_IWQ(IIC33, 254),
	INTC_IWQ(IIC33, 255), INTC_IWQ(IIC33, 256),
	INTC_IWQ(IIC33, 257),

	INTC_IWQ(SCIF0_BWI, 258), INTC_IWQ(SCIF0_EWI, 259),
	INTC_IWQ(SCIF0_WXI, 260), INTC_IWQ(SCIF0_TXI, 261),
	INTC_IWQ(SCIF1_BWI, 262), INTC_IWQ(SCIF1_EWI, 263),
	INTC_IWQ(SCIF1_WXI, 264), INTC_IWQ(SCIF1_TXI, 265),
	INTC_IWQ(SCIF2_BWI, 266), INTC_IWQ(SCIF2_EWI, 267),
	INTC_IWQ(SCIF2_WXI, 268), INTC_IWQ(SCIF2_TXI, 269),
	INTC_IWQ(SCIF3_BWI, 270), INTC_IWQ(SCIF3_EWI, 271),
	INTC_IWQ(SCIF3_WXI, 272), INTC_IWQ(SCIF3_TXI, 273),
	INTC_IWQ(SCIF4_BWI, 274), INTC_IWQ(SCIF4_EWI, 275),
	INTC_IWQ(SCIF4_WXI, 276), INTC_IWQ(SCIF4_TXI, 277),
	INTC_IWQ(SCIF5_BWI, 278), INTC_IWQ(SCIF5_EWI, 279),
	INTC_IWQ(SCIF5_WXI, 280), INTC_IWQ(SCIF5_TXI, 281),
	INTC_IWQ(SCIF6_BWI, 282), INTC_IWQ(SCIF6_EWI, 283),
	INTC_IWQ(SCIF6_WXI, 284), INTC_IWQ(SCIF6_TXI, 285),
	INTC_IWQ(SCIF7_BWI, 286), INTC_IWQ(SCIF7_EWI, 287),
	INTC_IWQ(SCIF7_WXI, 288), INTC_IWQ(SCIF7_TXI, 289),

	INTC_IWQ(WCAN0, 291), INTC_IWQ(WCAN0, 292),
	INTC_IWQ(WCAN0, 293), INTC_IWQ(WCAN0, 294),
	INTC_IWQ(WCAN0, 295),
	INTC_IWQ(WCAN1, 296), INTC_IWQ(WCAN1, 297),
	INTC_IWQ(WCAN1, 298), INTC_IWQ(WCAN1, 299),
	INTC_IWQ(WCAN1, 300),
	INTC_IWQ(WCAN2, 301), INTC_IWQ(WCAN2, 302),
	INTC_IWQ(WCAN2, 303), INTC_IWQ(WCAN2, 304),
	INTC_IWQ(WCAN2, 305),

	INTC_IWQ(WSPIC0, 306), INTC_IWQ(WSPIC0, 307),
	INTC_IWQ(WSPIC0, 308),
	INTC_IWQ(WSPIC1, 309), INTC_IWQ(WSPIC1, 310),
	INTC_IWQ(WSPIC1, 311),

	INTC_IWQ(IEBC, 318),

	INTC_IWQ(CD_WOMD, 319), INTC_IWQ(CD_WOMD, 320),
	INTC_IWQ(CD_WOMD, 321), INTC_IWQ(CD_WOMD, 322),
	INTC_IWQ(CD_WOMD, 323), INTC_IWQ(CD_WOMD, 324),

	INTC_IWQ(NFMC, 325), INTC_IWQ(NFMC, 326),
	INTC_IWQ(NFMC, 327), INTC_IWQ(NFMC, 328),

	INTC_IWQ(SDHI0, 332), INTC_IWQ(SDHI0, 333),
	INTC_IWQ(SDHI0, 334),
	INTC_IWQ(SDHI1, 335), INTC_IWQ(SDHI1, 336),
	INTC_IWQ(SDHI1, 337),

	INTC_IWQ(WTC, 338), INTC_IWQ(WTC, 339),
	INTC_IWQ(WTC, 340),

	INTC_IWQ(SWCC0, 341), INTC_IWQ(SWCC0, 342),
	INTC_IWQ(SWCC0, 343), INTC_IWQ(SWCC0, 344),
	INTC_IWQ(SWCC0, 345),
	INTC_IWQ(SWCC1, 346), INTC_IWQ(SWCC1, 347),
	INTC_IWQ(SWCC1, 348), INTC_IWQ(SWCC1, 349),
	INTC_IWQ(SWCC1, 350),
	INTC_IWQ(SWCC2, 351), INTC_IWQ(SWCC2, 352),
	INTC_IWQ(SWCC2, 353), INTC_IWQ(SWCC2, 354),
	INTC_IWQ(SWCC2, 355),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
	INTC_GWOUP(SCIF0, SCIF0_BWI, SCIF0_EWI, SCIF0_WXI, SCIF0_TXI),
	INTC_GWOUP(SCIF1, SCIF1_BWI, SCIF1_EWI, SCIF1_WXI, SCIF1_TXI),
	INTC_GWOUP(SCIF2, SCIF2_BWI, SCIF2_EWI, SCIF2_WXI, SCIF2_TXI),
	INTC_GWOUP(SCIF3, SCIF3_BWI, SCIF3_EWI, SCIF3_WXI, SCIF3_TXI),
	INTC_GWOUP(SCIF4, SCIF4_BWI, SCIF4_EWI, SCIF4_WXI, SCIF4_TXI),
	INTC_GWOUP(SCIF5, SCIF5_BWI, SCIF5_EWI, SCIF5_WXI, SCIF5_TXI),
	INTC_GWOUP(SCIF6, SCIF6_BWI, SCIF6_EWI, SCIF6_WXI, SCIF6_TXI),
	INTC_GWOUP(SCIF7, SCIF7_BWI, SCIF7_EWI, SCIF7_WXI, SCIF7_TXI),
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xfffe0818, 0, 16, 4, /* IPW01 */ { IWQ0, IWQ1, IWQ2, IWQ3 } },
	{ 0xfffe081a, 0, 16, 4, /* IPW02 */ { IWQ4, IWQ5, IWQ6, IWQ7 } },
	{ 0xfffe0820, 0, 16, 4, /* IPW05 */ { PINT, 0, 0, 0 } },
	{ 0xfffe0c00, 0, 16, 4, /* IPW06 */ { DMAC0,  DMAC1, DMAC2,  DMAC3 } },
	{ 0xfffe0c02, 0, 16, 4, /* IPW07 */ { DMAC4,  DMAC5, DMAC6,  DMAC7 } },
	{ 0xfffe0c04, 0, 16, 4, /* IPW08 */ { DMAC8,  DMAC9,
					      DMAC10, DMAC11 } },
	{ 0xfffe0c06, 0, 16, 4, /* IPW09 */ { DMAC12, DMAC13,
					      DMAC14, DMAC15 } },
	{ 0xfffe0c08, 0, 16, 4, /* IPW10 */ { USB, VDC4, VDC4, VDC4 } },
	{ 0xfffe0c0a, 0, 16, 4, /* IPW11 */ { 0, 0, 0, 0 } },
	{ 0xfffe0c0c, 0, 16, 4, /* IPW12 */ { CMT0, CMT1, BSC, WDT } },
	{ 0xfffe0c0e, 0, 16, 4, /* IPW13 */ { MTU0_ABCD, MTU0_VEF,
					      MTU1_AB, MTU1_VU } },
	{ 0xfffe0c10, 0, 16, 4, /* IPW14 */ { MTU2_AB, MTU2_VU,
					      MTU3_ABCD, MTU3_TCI3V } },
	{ 0xfffe0c12, 0, 16, 4, /* IPW15 */ { MTU4_ABCD, MTU4_TCI4V,
					      PWMT1, PWMT2 } },
	{ 0xfffe0c14, 0, 16, 4, /* IPW16 */ { 0, 0, 0, 0 } },
	{ 0xfffe0c16, 0, 16, 4, /* IPW17 */ { ADC_ADI, SSIF0, SSII1, SSII2 } },
	{ 0xfffe0c18, 0, 16, 4, /* IPW18 */ { SSII3, SSII4, SSII5,  WSPDIF} },
	{ 0xfffe0c1a, 0, 16, 4, /* IPW19 */ { IIC30, IIC31, IIC32, IIC33 } },
	{ 0xfffe0c1c, 0, 16, 4, /* IPW20 */ { SCIF0, SCIF1, SCIF2, SCIF3 } },
	{ 0xfffe0c1e, 0, 16, 4, /* IPW21 */ { SCIF4, SCIF5, SCIF6, SCIF7 } },
	{ 0xfffe0c20, 0, 16, 4, /* IPW22 */ { 0, WCAN0, WCAN1, WCAN2 } },
	{ 0xfffe0c22, 0, 16, 4, /* IPW23 */ { WSPIC0, WSPIC1, 0, 0 } },
	{ 0xfffe0c24, 0, 16, 4, /* IPW24 */ { IEBC, CD_WOMD, NFMC, 0 } },
	{ 0xfffe0c26, 0, 16, 4, /* IPW25 */ { SDHI0, SDHI1, WTC, 0 } },
	{ 0xfffe0c28, 0, 16, 4, /* IPW26 */ { SWCC0, SWCC1, SWCC2, 0 } },
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xfffe0808, 0, 16, /* PINTEW */
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7269", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xe8007000, 0x100),
	DEFINE_WES_IWQ(259),
	DEFINE_WES_IWQ(260),
	DEFINE_WES_IWQ(261),
	DEFINE_WES_IWQ(258),
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
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xe8007800, 0x100),
	DEFINE_WES_IWQ(263),
	DEFINE_WES_IWQ(264),
	DEFINE_WES_IWQ(265),
	DEFINE_WES_IWQ(262),
};

static stwuct pwatfowm_device scif1_device = {
	.name		= "sh-sci",
	.id		= 1,
	.wesouwce	= scif1_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif1_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif1_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif2_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif2_wesouwces[] = {
	DEFINE_WES_MEM(0xe8008000, 0x100),
	DEFINE_WES_IWQ(267),
	DEFINE_WES_IWQ(268),
	DEFINE_WES_IWQ(269),
	DEFINE_WES_IWQ(266),
};

static stwuct pwatfowm_device scif2_device = {
	.name		= "sh-sci",
	.id		= 2,
	.wesouwce	= scif2_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif2_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif2_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif3_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif3_wesouwces[] = {
	DEFINE_WES_MEM(0xe8008800, 0x100),
	DEFINE_WES_IWQ(271),
	DEFINE_WES_IWQ(272),
	DEFINE_WES_IWQ(273),
	DEFINE_WES_IWQ(270),
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
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif4_wesouwces[] = {
	DEFINE_WES_MEM(0xe8009000, 0x100),
	DEFINE_WES_IWQ(275),
	DEFINE_WES_IWQ(276),
	DEFINE_WES_IWQ(277),
	DEFINE_WES_IWQ(274),
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
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif5_wesouwces[] = {
	DEFINE_WES_MEM(0xe8009800, 0x100),
	DEFINE_WES_IWQ(279),
	DEFINE_WES_IWQ(280),
	DEFINE_WES_IWQ(281),
	DEFINE_WES_IWQ(278),
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

static stwuct pwat_sci_powt scif6_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif6_wesouwces[] = {
	DEFINE_WES_MEM(0xe800a000, 0x100),
	DEFINE_WES_IWQ(283),
	DEFINE_WES_IWQ(284),
	DEFINE_WES_IWQ(285),
	DEFINE_WES_IWQ(282),
};

static stwuct pwatfowm_device scif6_device = {
	.name		= "sh-sci",
	.id		= 6,
	.wesouwce	= scif6_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif6_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif6_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif7_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif7_wesouwces[] = {
	DEFINE_WES_MEM(0xe800a800, 0x100),
	DEFINE_WES_IWQ(287),
	DEFINE_WES_IWQ(288),
	DEFINE_WES_IWQ(289),
	DEFINE_WES_IWQ(286),
};

static stwuct pwatfowm_device scif7_device = {
	.name		= "sh-sci",
	.id		= 7,
	.wesouwce	= scif7_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif7_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif7_pwatfowm_data,
	},
};

static stwuct sh_timew_config cmt_pwatfowm_data = {
	.channews_mask = 3,
};

static stwuct wesouwce cmt_wesouwces[] = {
	DEFINE_WES_MEM(0xfffec000, 0x10),
	DEFINE_WES_IWQ(188),
	DEFINE_WES_IWQ(189),
};

static stwuct pwatfowm_device cmt_device = {
	.name		= "sh-cmt-16",
	.id		= 0,
	.dev = {
		.pwatfowm_data	= &cmt_pwatfowm_data,
	},
	.wesouwce	= cmt_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(cmt_wesouwces),
};

static stwuct wesouwce mtu2_wesouwces[] = {
	DEFINE_WES_MEM(0xfffe4000, 0x400),
	DEFINE_WES_IWQ_NAMED(192, "tgi0a"),
	DEFINE_WES_IWQ_NAMED(203, "tgi1a"),
};

static stwuct pwatfowm_device mtu2_device = {
	.name		= "sh-mtu2",
	.id		= -1,
	.wesouwce	= mtu2_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(mtu2_wesouwces),
};

static stwuct wesouwce wtc_wesouwces[] = {
	[0] = {
		.stawt	= 0xfffe6000,
		.end	= 0xfffe6000 + 0x30 - 1,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		/* Shawed Pewiod/Cawwy/Awawm IWQ */
		.stawt	= 338,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
};

/* USB Host */
static stwuct w8a66597_pwatdata w8a66597_data = {
	.on_chip = 1,
	.endian = 1,
};

static stwuct wesouwce w8a66597_usb_host_wesouwces[] = {
	[0] = {
		.stawt	= 0xe8010000,
		.end	= 0xe80100e4,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= 170,
		.end	= 170,
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device w8a66597_usb_host_device = {
	.name		= "w8a66597_hcd",
	.id		= 0,
	.dev = {
		.dma_mask		= NUWW,         /*  not use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &w8a66597_data,
	},
	.num_wesouwces	= AWWAY_SIZE(w8a66597_usb_host_wesouwces),
	.wesouwce	= w8a66597_usb_host_wesouwces,
};

static stwuct pwatfowm_device *sh7269_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&scif6_device,
	&scif7_device,
	&cmt_device,
	&mtu2_device,
	&wtc_device,
	&w8a66597_usb_host_device,
};

static int __init sh7269_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh7269_devices,
				    AWWAY_SIZE(sh7269_devices));
}
awch_initcaww(sh7269_devices_setup);

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}

static stwuct pwatfowm_device *sh7269_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&scif6_device,
	&scif7_device,
	&cmt_device,
	&mtu2_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7269_eawwy_devices,
				   AWWAY_SIZE(sh7269_eawwy_devices));
}
