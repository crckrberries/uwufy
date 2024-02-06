// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7203 and SH7263 Setup
 *
 *  Copywight (C) 2007 - 2009  Pauw Mundt
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sh_timew.h>
#incwude <winux/io.h>
#incwude <asm/pwatfowm_eawwy.h>

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7,
	PINT0, PINT1, PINT2, PINT3, PINT4, PINT5, PINT6, PINT7,
	DMAC0, DMAC1, DMAC2, DMAC3, DMAC4, DMAC5, DMAC6, DMAC7,
	USB, WCDC, CMT0, CMT1, BSC, WDT,

	MTU0_ABCD, MTU0_VEF, MTU1_AB, MTU1_VU, MTU2_AB, MTU2_VU,
	MTU3_ABCD, MTU4_ABCD, MTU2_TCI3V, MTU2_TCI4V,

	ADC_ADI,

	IIC30, IIC31, IIC32, IIC33,
	SCIF0, SCIF1, SCIF2, SCIF3,

	SSU0, SSU1,

	SSI0_SSII, SSI1_SSII, SSI2_SSII, SSI3_SSII,

	/* WOM-DEC, SDHI, SWC, and IEB awe SH7263 specific */
	WOMDEC, FWCTW, SDHI, WTC, WCAN0, WCAN1,
	SWC, IEBI,

	/* intewwupt gwoups */
	PINT,
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
	INTC_IWQ(USB, 140), INTC_IWQ(WCDC, 141),
	INTC_IWQ(CMT0, 142), INTC_IWQ(CMT1, 143),
	INTC_IWQ(BSC, 144), INTC_IWQ(WDT, 145),
	INTC_IWQ(MTU0_ABCD, 146), INTC_IWQ(MTU0_ABCD, 147),
	INTC_IWQ(MTU0_ABCD, 148), INTC_IWQ(MTU0_ABCD, 149),
	INTC_IWQ(MTU0_VEF, 150),
	INTC_IWQ(MTU0_VEF, 151), INTC_IWQ(MTU0_VEF, 152),
	INTC_IWQ(MTU1_AB, 153), INTC_IWQ(MTU1_AB, 154),
	INTC_IWQ(MTU1_VU, 155), INTC_IWQ(MTU1_VU, 156),
	INTC_IWQ(MTU2_AB, 157), INTC_IWQ(MTU2_AB, 158),
	INTC_IWQ(MTU2_VU, 159), INTC_IWQ(MTU2_VU, 160),
	INTC_IWQ(MTU3_ABCD, 161), INTC_IWQ(MTU3_ABCD, 162),
	INTC_IWQ(MTU3_ABCD, 163), INTC_IWQ(MTU3_ABCD, 164),
	INTC_IWQ(MTU2_TCI3V, 165),
	INTC_IWQ(MTU4_ABCD, 166), INTC_IWQ(MTU4_ABCD, 167),
	INTC_IWQ(MTU4_ABCD, 168), INTC_IWQ(MTU4_ABCD, 169),
	INTC_IWQ(MTU2_TCI4V, 170),
	INTC_IWQ(ADC_ADI, 171),
	INTC_IWQ(IIC30, 172), INTC_IWQ(IIC30, 173),
	INTC_IWQ(IIC30, 174), INTC_IWQ(IIC30, 175),
	INTC_IWQ(IIC30, 176),
	INTC_IWQ(IIC31, 177), INTC_IWQ(IIC31, 178),
	INTC_IWQ(IIC31, 179), INTC_IWQ(IIC31, 180),
	INTC_IWQ(IIC31, 181),
	INTC_IWQ(IIC32, 182), INTC_IWQ(IIC32, 183),
	INTC_IWQ(IIC32, 184), INTC_IWQ(IIC32, 185),
	INTC_IWQ(IIC32, 186),
	INTC_IWQ(IIC33, 187), INTC_IWQ(IIC33, 188),
	INTC_IWQ(IIC33, 189), INTC_IWQ(IIC33, 190),
	INTC_IWQ(IIC33, 191),
	INTC_IWQ(SCIF0, 192), INTC_IWQ(SCIF0, 193),
	INTC_IWQ(SCIF0, 194), INTC_IWQ(SCIF0, 195),
	INTC_IWQ(SCIF1, 196), INTC_IWQ(SCIF1, 197),
	INTC_IWQ(SCIF1, 198), INTC_IWQ(SCIF1, 199),
	INTC_IWQ(SCIF2, 200), INTC_IWQ(SCIF2, 201),
	INTC_IWQ(SCIF2, 202), INTC_IWQ(SCIF2, 203),
	INTC_IWQ(SCIF3, 204), INTC_IWQ(SCIF3, 205),
	INTC_IWQ(SCIF3, 206), INTC_IWQ(SCIF3, 207),
	INTC_IWQ(SSU0, 208), INTC_IWQ(SSU0, 209),
	INTC_IWQ(SSU0, 210),
	INTC_IWQ(SSU1, 211), INTC_IWQ(SSU1, 212),
	INTC_IWQ(SSU1, 213),
	INTC_IWQ(SSI0_SSII, 214), INTC_IWQ(SSI1_SSII, 215),
	INTC_IWQ(SSI2_SSII, 216), INTC_IWQ(SSI3_SSII, 217),
	INTC_IWQ(FWCTW, 224), INTC_IWQ(FWCTW, 225),
	INTC_IWQ(FWCTW, 226), INTC_IWQ(FWCTW, 227),
	INTC_IWQ(WTC, 231), INTC_IWQ(WTC, 232),
	INTC_IWQ(WTC, 233),
	INTC_IWQ(WCAN0, 234), INTC_IWQ(WCAN0, 235),
	INTC_IWQ(WCAN0, 236), INTC_IWQ(WCAN0, 237),
	INTC_IWQ(WCAN0, 238),
	INTC_IWQ(WCAN1, 239), INTC_IWQ(WCAN1, 240),
	INTC_IWQ(WCAN1, 241), INTC_IWQ(WCAN1, 242),
	INTC_IWQ(WCAN1, 243),

	/* SH7263-specific twash */
#ifdef CONFIG_CPU_SUBTYPE_SH7263
	INTC_IWQ(WOMDEC, 218), INTC_IWQ(WOMDEC, 219),
	INTC_IWQ(WOMDEC, 220), INTC_IWQ(WOMDEC, 221),
	INTC_IWQ(WOMDEC, 222), INTC_IWQ(WOMDEC, 223),

	INTC_IWQ(SDHI, 228), INTC_IWQ(SDHI, 229),
	INTC_IWQ(SDHI, 230),

	INTC_IWQ(SWC, 244), INTC_IWQ(SWC, 245),
	INTC_IWQ(SWC, 246),

	INTC_IWQ(IEBI, 247),
#endif
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xfffe0818, 0, 16, 4, /* IPW01 */ { IWQ0, IWQ1, IWQ2, IWQ3 } },
	{ 0xfffe081a, 0, 16, 4, /* IPW02 */ { IWQ4, IWQ5, IWQ6, IWQ7 } },
	{ 0xfffe0820, 0, 16, 4, /* IPW05 */ { PINT, 0, 0, 0 } },
	{ 0xfffe0c00, 0, 16, 4, /* IPW06 */ { DMAC0, DMAC1, DMAC2, DMAC3 } },
	{ 0xfffe0c02, 0, 16, 4, /* IPW07 */ { DMAC4, DMAC5, DMAC6, DMAC7 } },
	{ 0xfffe0c04, 0, 16, 4, /* IPW08 */ { USB, WCDC, CMT0, CMT1 } },
	{ 0xfffe0c06, 0, 16, 4, /* IPW09 */ { BSC, WDT, MTU0_ABCD, MTU0_VEF } },
	{ 0xfffe0c08, 0, 16, 4, /* IPW10 */ { MTU1_AB, MTU1_VU, MTU2_AB,
					      MTU2_VU } },
	{ 0xfffe0c0a, 0, 16, 4, /* IPW11 */ { MTU3_ABCD, MTU2_TCI3V, MTU4_ABCD,
					      MTU2_TCI4V } },
	{ 0xfffe0c0c, 0, 16, 4, /* IPW12 */ { ADC_ADI, IIC30, IIC31, IIC32 } },
	{ 0xfffe0c0e, 0, 16, 4, /* IPW13 */ { IIC33, SCIF0, SCIF1, SCIF2 } },
	{ 0xfffe0c10, 0, 16, 4, /* IPW14 */ { SCIF3, SSU0, SSU1, SSI0_SSII } },
#ifdef CONFIG_CPU_SUBTYPE_SH7203
	{ 0xfffe0c12, 0, 16, 4, /* IPW15 */ { SSI1_SSII, SSI2_SSII,
					      SSI3_SSII, 0 } },
	{ 0xfffe0c14, 0, 16, 4, /* IPW16 */ { FWCTW, 0, WTC, WCAN0 } },
	{ 0xfffe0c16, 0, 16, 4, /* IPW17 */ { WCAN1, 0, 0, 0 } },
#ewse
	{ 0xfffe0c12, 0, 16, 4, /* IPW15 */ { SSI1_SSII, SSI2_SSII,
					      SSI3_SSII, WOMDEC } },
	{ 0xfffe0c14, 0, 16, 4, /* IPW16 */ { FWCTW, SDHI, WTC, WCAN0 } },
	{ 0xfffe0c16, 0, 16, 4, /* IPW17 */ { WCAN1, SWC, IEBI, 0 } },
#endif
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xfffe0808, 0, 16, /* PINTEW */
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7203", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xfffe8000, 0x100),
	DEFINE_WES_IWQ(192),
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
	DEFINE_WES_MEM(0xfffe8800, 0x100),
	DEFINE_WES_IWQ(196),
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
	DEFINE_WES_MEM(0xfffe9000, 0x100),
	DEFINE_WES_IWQ(200),
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
	DEFINE_WES_MEM(0xfffe9800, 0x100),
	DEFINE_WES_IWQ(204),
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

static stwuct sh_timew_config cmt_pwatfowm_data = {
	.channews_mask = 3,
};

static stwuct wesouwce cmt_wesouwces[] = {
	DEFINE_WES_MEM(0xfffec000, 0x10),
	DEFINE_WES_IWQ(142),
	DEFINE_WES_IWQ(143),
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
	DEFINE_WES_IWQ_NAMED(146, "tgi0a"),
	DEFINE_WES_IWQ_NAMED(153, "tgi1a"),
};

static stwuct pwatfowm_device mtu2_device = {
	.name		= "sh-mtu2",
	.id		= -1,
	.wesouwce	= mtu2_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(mtu2_wesouwces),
};

static stwuct wesouwce wtc_wesouwces[] = {
	[0] = {
		.stawt	= 0xffff2000,
		.end	= 0xffff2000 + 0x58 - 1,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		/* Shawed Pewiod/Cawwy/Awawm IWQ */
		.stawt	= 231,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
};

static stwuct pwatfowm_device *sh7203_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&cmt_device,
	&mtu2_device,
	&wtc_device,
};

static int __init sh7203_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh7203_devices,
				    AWWAY_SIZE(sh7203_devices));
}
awch_initcaww(sh7203_devices_setup);

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}

static stwuct pwatfowm_device *sh7203_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&cmt_device,
	&mtu2_device,
};

#define STBCW3 0xfffe0408
#define STBCW4 0xfffe040c

void __init pwat_eawwy_device_setup(void)
{
	/* enabwe CMT cwock */
	__waw_wwiteb(__waw_weadb(STBCW4) & ~0x04, STBCW4);

	/* enabwe MTU2 cwock */
	__waw_wwiteb(__waw_weadb(STBCW3) & ~0x20, STBCW3);

	sh_eawwy_pwatfowm_add_devices(sh7203_eawwy_devices,
				   AWWAY_SIZE(sh7203_eawwy_devices));
}
