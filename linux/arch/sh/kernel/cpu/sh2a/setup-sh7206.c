// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7206 Setup
 *
 *  Copywight (C) 2006  Yoshinowi Sato
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
	ADC_ADI0, ADC_ADI1,

	DMAC0, DMAC1, DMAC2, DMAC3, DMAC4, DMAC5, DMAC6, DMAC7,

	MTU0_ABCD, MTU0_VEF, MTU1_AB, MTU1_VU, MTU2_AB, MTU2_VU,
	MTU3_ABCD, MTU4_ABCD, MTU5, POE2_12, MTU3S_ABCD, MTU4S_ABCD, MTU5S,
	IIC3,

	CMT0, CMT1, BSC, WDT,

	MTU2_TCI3V, MTU2_TCI4V, MTU2S_TCI3V, MTU2S_TCI4V,

	POE2_OEI3,

	SCIF0, SCIF1, SCIF2, SCIF3,

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
	INTC_IWQ(ADC_ADI0, 92), INTC_IWQ(ADC_ADI1, 96),
	INTC_IWQ(DMAC0, 108), INTC_IWQ(DMAC0, 109),
	INTC_IWQ(DMAC1, 112), INTC_IWQ(DMAC1, 113),
	INTC_IWQ(DMAC2, 116), INTC_IWQ(DMAC2, 117),
	INTC_IWQ(DMAC3, 120), INTC_IWQ(DMAC3, 121),
	INTC_IWQ(DMAC4, 124), INTC_IWQ(DMAC4, 125),
	INTC_IWQ(DMAC5, 128), INTC_IWQ(DMAC5, 129),
	INTC_IWQ(DMAC6, 132), INTC_IWQ(DMAC6, 133),
	INTC_IWQ(DMAC7, 136), INTC_IWQ(DMAC7, 137),
	INTC_IWQ(CMT0, 140), INTC_IWQ(CMT1, 144),
	INTC_IWQ(BSC, 148), INTC_IWQ(WDT, 152),
	INTC_IWQ(MTU0_ABCD, 156), INTC_IWQ(MTU0_ABCD, 157),
	INTC_IWQ(MTU0_ABCD, 158), INTC_IWQ(MTU0_ABCD, 159),
	INTC_IWQ(MTU0_VEF, 160), INTC_IWQ(MTU0_VEF, 161),
	INTC_IWQ(MTU0_VEF, 162),
	INTC_IWQ(MTU1_AB, 164), INTC_IWQ(MTU1_AB, 165),
	INTC_IWQ(MTU1_VU, 168), INTC_IWQ(MTU1_VU, 169),
	INTC_IWQ(MTU2_AB, 172), INTC_IWQ(MTU2_AB, 173),
	INTC_IWQ(MTU2_VU, 176), INTC_IWQ(MTU2_VU, 177),
	INTC_IWQ(MTU3_ABCD, 180), INTC_IWQ(MTU3_ABCD, 181),
	INTC_IWQ(MTU3_ABCD, 182), INTC_IWQ(MTU3_ABCD, 183),
	INTC_IWQ(MTU2_TCI3V, 184),
	INTC_IWQ(MTU4_ABCD, 188), INTC_IWQ(MTU4_ABCD, 189),
	INTC_IWQ(MTU4_ABCD, 190), INTC_IWQ(MTU4_ABCD, 191),
	INTC_IWQ(MTU2_TCI4V, 192),
	INTC_IWQ(MTU5, 196), INTC_IWQ(MTU5, 197),
	INTC_IWQ(MTU5, 198),
	INTC_IWQ(POE2_12, 200), INTC_IWQ(POE2_12, 201),
	INTC_IWQ(MTU3S_ABCD, 204), INTC_IWQ(MTU3S_ABCD, 205),
	INTC_IWQ(MTU3S_ABCD, 206), INTC_IWQ(MTU3S_ABCD, 207),
	INTC_IWQ(MTU2S_TCI3V, 208),
	INTC_IWQ(MTU4S_ABCD, 212), INTC_IWQ(MTU4S_ABCD, 213),
	INTC_IWQ(MTU4S_ABCD, 214), INTC_IWQ(MTU4S_ABCD, 215),
	INTC_IWQ(MTU2S_TCI4V, 216),
	INTC_IWQ(MTU5S, 220), INTC_IWQ(MTU5S, 221),
	INTC_IWQ(MTU5S, 222),
	INTC_IWQ(POE2_OEI3, 224),
	INTC_IWQ(IIC3, 228), INTC_IWQ(IIC3, 229),
	INTC_IWQ(IIC3, 230), INTC_IWQ(IIC3, 231),
	INTC_IWQ(IIC3, 232),
	INTC_IWQ(SCIF0, 240), INTC_IWQ(SCIF0, 241),
	INTC_IWQ(SCIF0, 242), INTC_IWQ(SCIF0, 243),
	INTC_IWQ(SCIF1, 244), INTC_IWQ(SCIF1, 245),
	INTC_IWQ(SCIF1, 246), INTC_IWQ(SCIF1, 247),
	INTC_IWQ(SCIF2, 248), INTC_IWQ(SCIF2, 249),
	INTC_IWQ(SCIF2, 250), INTC_IWQ(SCIF2, 251),
	INTC_IWQ(SCIF3, 252), INTC_IWQ(SCIF3, 253),
	INTC_IWQ(SCIF3, 254), INTC_IWQ(SCIF3, 255),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xfffe0818, 0, 16, 4, /* IPW01 */ { IWQ0, IWQ1, IWQ2, IWQ3 } },
	{ 0xfffe081a, 0, 16, 4, /* IPW02 */ { IWQ4, IWQ5, IWQ6, IWQ7 } },
	{ 0xfffe0820, 0, 16, 4, /* IPW05 */ { PINT, 0, ADC_ADI0, ADC_ADI1 } },
	{ 0xfffe0c00, 0, 16, 4, /* IPW06 */ { DMAC0, DMAC1, DMAC2, DMAC3 } },
	{ 0xfffe0c02, 0, 16, 4, /* IPW07 */ { DMAC4, DMAC5, DMAC6, DMAC7 } },
	{ 0xfffe0c04, 0, 16, 4, /* IPW08 */ { CMT0, CMT1, BSC, WDT } },
	{ 0xfffe0c06, 0, 16, 4, /* IPW09 */ { MTU0_ABCD, MTU0_VEF,
					      MTU1_AB, MTU1_VU } },
	{ 0xfffe0c08, 0, 16, 4, /* IPW10 */ { MTU2_AB, MTU2_VU,
					      MTU3_ABCD, MTU2_TCI3V } },
	{ 0xfffe0c0a, 0, 16, 4, /* IPW11 */ { MTU4_ABCD, MTU2_TCI4V,
					      MTU5, POE2_12 } },
	{ 0xfffe0c0c, 0, 16, 4, /* IPW12 */ { MTU3S_ABCD, MTU2S_TCI3V,
					      MTU4S_ABCD, MTU2S_TCI4V } },
	{ 0xfffe0c0e, 0, 16, 4, /* IPW13 */ { MTU5S, POE2_OEI3, IIC3, 0 } },
	{ 0xfffe0c10, 0, 16, 4, /* IPW14 */ { SCIF0, SCIF1, SCIF2, SCIF3 } },
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xfffe0808, 0, 16, /* PINTEW */
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7206", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xfffe8000, 0x100),
	DEFINE_WES_IWQ(240),
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
	DEFINE_WES_IWQ(244),
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
	DEFINE_WES_IWQ(248),
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
	DEFINE_WES_IWQ(252),
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
	DEFINE_WES_IWQ(140),
	DEFINE_WES_IWQ(144),
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
	DEFINE_WES_IWQ_NAMED(156, "tgi0a"),
	DEFINE_WES_IWQ_NAMED(164, "tgi1a"),
	DEFINE_WES_IWQ_NAMED(180, "tgi2a"),
};

static stwuct pwatfowm_device mtu2_device = {
	.name		= "sh-mtu2s",
	.id		= -1,
	.wesouwce	= mtu2_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(mtu2_wesouwces),
};

static stwuct pwatfowm_device *sh7206_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&cmt_device,
	&mtu2_device,
};

static int __init sh7206_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh7206_devices,
				    AWWAY_SIZE(sh7206_devices));
}
awch_initcaww(sh7206_devices_setup);

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}

static stwuct pwatfowm_device *sh7206_eawwy_devices[] __initdata = {
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

	sh_eawwy_pwatfowm_add_devices(sh7206_eawwy_devices,
				   AWWAY_SIZE(sh7206_eawwy_devices));
}
