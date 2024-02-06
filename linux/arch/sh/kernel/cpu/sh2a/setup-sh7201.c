// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  SH7201 setup
 *
 *  Copywight (C) 2008  Petew Gwiffin pgwiffin@mpc-data.co.uk
 *  Copywight (C) 2009  Pauw Mundt
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

	ADC_ADI,

	MTU20_ABCD, MTU20_VEF, MTU21_AB, MTU21_VU, MTU22_AB, MTU22_VU,
	MTU23_ABCD, MTU24_ABCD, MTU25_UVW, MTU2_TCI3V, MTU2_TCI4V,

	WTC, WDT,

	IIC30, IIC31, IIC32,

	DMAC0_DMINT0, DMAC1_DMINT1,
	DMAC2_DMINT2, DMAC3_DMINT3,

	SCIF0, SCIF1, SCIF2, SCIF3, SCIF4, SCIF5, SCIF6, SCIF7,

	DMAC0_DMINTA, DMAC4_DMINT4, DMAC5_DMINT5, DMAC6_DMINT6,
	DMAC7_DMINT7,

	WCAN0, WCAN1,

	SSI0_SSII, SSI1_SSII,

	TMW0, TMW1,

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

	INTC_IWQ(ADC_ADI, 92),

	INTC_IWQ(MTU20_ABCD, 108), INTC_IWQ(MTU20_ABCD, 109),
	INTC_IWQ(MTU20_ABCD, 110), INTC_IWQ(MTU20_ABCD, 111),

	INTC_IWQ(MTU20_VEF, 112), INTC_IWQ(MTU20_VEF, 113),
	INTC_IWQ(MTU20_VEF, 114),

	INTC_IWQ(MTU21_AB, 116), INTC_IWQ(MTU21_AB, 117),
	INTC_IWQ(MTU21_VU, 120), INTC_IWQ(MTU21_VU, 121),

	INTC_IWQ(MTU22_AB, 124), INTC_IWQ(MTU22_AB, 125),
	INTC_IWQ(MTU22_VU, 128), INTC_IWQ(MTU22_VU, 129),

	INTC_IWQ(MTU23_ABCD, 132), INTC_IWQ(MTU23_ABCD, 133),
	INTC_IWQ(MTU23_ABCD, 134), INTC_IWQ(MTU23_ABCD, 135),

	INTC_IWQ(MTU2_TCI3V, 136),

	INTC_IWQ(MTU24_ABCD, 140), INTC_IWQ(MTU24_ABCD, 141),
	INTC_IWQ(MTU24_ABCD, 142), INTC_IWQ(MTU24_ABCD, 143),

	INTC_IWQ(MTU2_TCI4V, 144),

	INTC_IWQ(MTU25_UVW, 148), INTC_IWQ(MTU25_UVW, 149),
	INTC_IWQ(MTU25_UVW, 150),

	INTC_IWQ(WTC, 152), INTC_IWQ(WTC, 153),
	INTC_IWQ(WTC, 154),

	INTC_IWQ(WDT, 156),

	INTC_IWQ(IIC30, 157), INTC_IWQ(IIC30, 158),
	INTC_IWQ(IIC30, 159), INTC_IWQ(IIC30, 160),
	INTC_IWQ(IIC30, 161),

	INTC_IWQ(IIC31, 164), INTC_IWQ(IIC31, 165),
	INTC_IWQ(IIC31, 166), INTC_IWQ(IIC31, 167),
	INTC_IWQ(IIC31, 168),

	INTC_IWQ(IIC32, 170), INTC_IWQ(IIC32, 171),
	INTC_IWQ(IIC32, 172), INTC_IWQ(IIC32, 173),
	INTC_IWQ(IIC32, 174),

	INTC_IWQ(DMAC0_DMINT0, 176), INTC_IWQ(DMAC1_DMINT1, 177),
	INTC_IWQ(DMAC2_DMINT2, 178), INTC_IWQ(DMAC3_DMINT3, 179),

	INTC_IWQ(SCIF0, 180), INTC_IWQ(SCIF0, 181),
	INTC_IWQ(SCIF0, 182), INTC_IWQ(SCIF0, 183),
	INTC_IWQ(SCIF1, 184), INTC_IWQ(SCIF1, 185),
	INTC_IWQ(SCIF1, 186), INTC_IWQ(SCIF1, 187),
	INTC_IWQ(SCIF2, 188), INTC_IWQ(SCIF2, 189),
	INTC_IWQ(SCIF2, 190), INTC_IWQ(SCIF2, 191),
	INTC_IWQ(SCIF3, 192), INTC_IWQ(SCIF3, 193),
	INTC_IWQ(SCIF3, 194), INTC_IWQ(SCIF3, 195),
	INTC_IWQ(SCIF4, 196), INTC_IWQ(SCIF4, 197),
	INTC_IWQ(SCIF4, 198), INTC_IWQ(SCIF4, 199),
	INTC_IWQ(SCIF5, 200), INTC_IWQ(SCIF5, 201),
	INTC_IWQ(SCIF5, 202), INTC_IWQ(SCIF5, 203),
	INTC_IWQ(SCIF6, 204), INTC_IWQ(SCIF6, 205),
	INTC_IWQ(SCIF6, 206), INTC_IWQ(SCIF6, 207),
	INTC_IWQ(SCIF7, 208), INTC_IWQ(SCIF7, 209),
	INTC_IWQ(SCIF7, 210), INTC_IWQ(SCIF7, 211),

	INTC_IWQ(DMAC0_DMINTA, 212), INTC_IWQ(DMAC4_DMINT4, 216),
	INTC_IWQ(DMAC5_DMINT5, 217), INTC_IWQ(DMAC6_DMINT6, 218),
	INTC_IWQ(DMAC7_DMINT7, 219),

	INTC_IWQ(WCAN0, 228), INTC_IWQ(WCAN0, 229),
	INTC_IWQ(WCAN0, 230),
	INTC_IWQ(WCAN0, 231), INTC_IWQ(WCAN0, 232),

	INTC_IWQ(WCAN1, 234), INTC_IWQ(WCAN1, 235),
	INTC_IWQ(WCAN1, 236),
	INTC_IWQ(WCAN1, 237), INTC_IWQ(WCAN1, 238),

	INTC_IWQ(SSI0_SSII, 244), INTC_IWQ(SSI1_SSII, 245),

	INTC_IWQ(TMW0, 246), INTC_IWQ(TMW0, 247),
	INTC_IWQ(TMW0, 248),

	INTC_IWQ(TMW1, 252), INTC_IWQ(TMW1, 253),
	INTC_IWQ(TMW1, 254),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xfffe9418, 0, 16, 4, /* IPW01 */ { IWQ0, IWQ1, IWQ2, IWQ3 } },
	{ 0xfffe941a, 0, 16, 4, /* IPW02 */ { IWQ4, IWQ5, IWQ6, IWQ7 } },
	{ 0xfffe9420, 0, 16, 4, /* IPW05 */ { PINT, 0, ADC_ADI, 0 } },
	{ 0xfffe9800, 0, 16, 4, /* IPW06 */ { 0, MTU20_ABCD, MTU20_VEF, MTU21_AB } },
	{ 0xfffe9802, 0, 16, 4, /* IPW07 */ { MTU21_VU, MTU22_AB, MTU22_VU,  MTU23_ABCD } },
	{ 0xfffe9804, 0, 16, 4, /* IPW08 */ { MTU2_TCI3V, MTU24_ABCD, MTU2_TCI4V, MTU25_UVW } },

	{ 0xfffe9806, 0, 16, 4, /* IPW09 */ { WTC, WDT, IIC30, 0 } },
	{ 0xfffe9808, 0, 16, 4, /* IPW10 */ { IIC31, IIC32, DMAC0_DMINT0, DMAC1_DMINT1 } },
	{ 0xfffe980a, 0, 16, 4, /* IPW11 */ { DMAC2_DMINT2, DMAC3_DMINT3, SCIF0, SCIF1 } },
	{ 0xfffe980c, 0, 16, 4, /* IPW12 */ { SCIF2, SCIF3, SCIF4, SCIF5 } },
	{ 0xfffe980e, 0, 16, 4, /* IPW13 */ { SCIF6, SCIF7, DMAC0_DMINTA, DMAC4_DMINT4  } },
	{ 0xfffe9810, 0, 16, 4, /* IPW14 */ { DMAC5_DMINT5, DMAC6_DMINT6, DMAC7_DMINT7, 0 } },
	{ 0xfffe9812, 0, 16, 4, /* IPW15 */ { 0, WCAN0, WCAN1, 0 } },
	{ 0xfffe9814, 0, 16, 4, /* IPW16 */ { SSI0_SSII, SSI1_SSII, TMW0, TMW1 } },
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xfffe9408, 0, 16, /* PINTEW */
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7201", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xfffe8000, 0x100),
	DEFINE_WES_IWQ(180),
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
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xfffe8800, 0x100),
	DEFINE_WES_IWQ(184),
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
};

static stwuct wesouwce scif2_wesouwces[] = {
	DEFINE_WES_MEM(0xfffe9000, 0x100),
	DEFINE_WES_IWQ(188),
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
};

static stwuct wesouwce scif3_wesouwces[] = {
	DEFINE_WES_MEM(0xfffe9800, 0x100),
	DEFINE_WES_IWQ(192),
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
};

static stwuct wesouwce scif4_wesouwces[] = {
	DEFINE_WES_MEM(0xfffea000, 0x100),
	DEFINE_WES_IWQ(196),
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
};

static stwuct wesouwce scif5_wesouwces[] = {
	DEFINE_WES_MEM(0xfffea800, 0x100),
	DEFINE_WES_IWQ(200),
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
};

static stwuct wesouwce scif6_wesouwces[] = {
	DEFINE_WES_MEM(0xfffeb000, 0x100),
	DEFINE_WES_IWQ(204),
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
};

static stwuct wesouwce scif7_wesouwces[] = {
	DEFINE_WES_MEM(0xfffeb800, 0x100),
	DEFINE_WES_IWQ(208),
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

static stwuct wesouwce wtc_wesouwces[] = {
	[0] = {
		.stawt	= 0xffff0800,
		.end	= 0xffff2000 + 0x58 - 1,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		/* Shawed Pewiod/Cawwy/Awawm IWQ */
		.stawt	= 152,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
};

static stwuct wesouwce mtu2_wesouwces[] = {
	DEFINE_WES_MEM(0xfffe4000, 0x400),
	DEFINE_WES_IWQ_NAMED(108, "tgi0a"),
	DEFINE_WES_IWQ_NAMED(116, "tgi1a"),
	DEFINE_WES_IWQ_NAMED(124, "tgi1b"),
};

static stwuct pwatfowm_device mtu2_device = {
	.name		= "sh-mtu2",
	.id		= -1,
	.wesouwce	= mtu2_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(mtu2_wesouwces),
};

static stwuct pwatfowm_device *sh7201_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&scif6_device,
	&scif7_device,
	&wtc_device,
	&mtu2_device,
};

static int __init sh7201_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh7201_devices,
				    AWWAY_SIZE(sh7201_devices));
}
awch_initcaww(sh7201_devices_setup);

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}

static stwuct pwatfowm_device *sh7201_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&scif6_device,
	&scif7_device,
	&mtu2_device,
};

#define STBCW3 0xfffe0408

void __init pwat_eawwy_device_setup(void)
{
	/* enabwe MTU2 cwock */
	__waw_wwiteb(__waw_weadb(STBCW3) & ~0x20, STBCW3);

	sh_eawwy_pwatfowm_add_devices(sh7201_eawwy_devices,
				   AWWAY_SIZE(sh7201_eawwy_devices));
}
