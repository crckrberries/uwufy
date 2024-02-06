// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas MX-G (W8A03022BG) Setup
 *
 *  Copywight (C) 2008, 2009  Pauw Mundt
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sh_timew.h>
#incwude <asm/pwatfowm_eawwy.h>

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7,
	IWQ8, IWQ9, IWQ10, IWQ11, IWQ12, IWQ13, IWQ14, IWQ15,

	PINT0, PINT1, PINT2, PINT3, PINT4, PINT5, PINT6, PINT7,
	SINT8, SINT7, SINT6, SINT5, SINT4, SINT3, SINT2, SINT1,

	SCIF0, SCIF1,

	MTU2_GWOUP1, MTU2_GWOUP2, MTU2_GWOUP3, MTU2_GWOUP4, MTU2_GWOUP5,
	MTU2_TGI3B, MTU2_TGI3C,

	/* intewwupt gwoups */
	PINT,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_IWQ(IWQ0, 64), INTC_IWQ(IWQ1, 65),
	INTC_IWQ(IWQ2, 66), INTC_IWQ(IWQ3, 67),
	INTC_IWQ(IWQ4, 68), INTC_IWQ(IWQ5, 69),
	INTC_IWQ(IWQ6, 70), INTC_IWQ(IWQ7, 71),
	INTC_IWQ(IWQ8, 72), INTC_IWQ(IWQ9, 73),
	INTC_IWQ(IWQ10, 74), INTC_IWQ(IWQ11, 75),
	INTC_IWQ(IWQ12, 76), INTC_IWQ(IWQ13, 77),
	INTC_IWQ(IWQ14, 78), INTC_IWQ(IWQ15, 79),

	INTC_IWQ(PINT0, 80), INTC_IWQ(PINT1, 81),
	INTC_IWQ(PINT2, 82), INTC_IWQ(PINT3, 83),
	INTC_IWQ(PINT4, 84), INTC_IWQ(PINT5, 85),
	INTC_IWQ(PINT6, 86), INTC_IWQ(PINT7, 87),

	INTC_IWQ(SINT8, 94), INTC_IWQ(SINT7, 95),
	INTC_IWQ(SINT6, 96), INTC_IWQ(SINT5, 97),
	INTC_IWQ(SINT4, 98), INTC_IWQ(SINT3, 99),
	INTC_IWQ(SINT2, 100), INTC_IWQ(SINT1, 101),

	INTC_IWQ(SCIF0, 220), INTC_IWQ(SCIF0, 221),
	INTC_IWQ(SCIF0, 222), INTC_IWQ(SCIF0, 223),
	INTC_IWQ(SCIF1, 224), INTC_IWQ(SCIF1, 225),
	INTC_IWQ(SCIF1, 226), INTC_IWQ(SCIF1, 227),

	INTC_IWQ(MTU2_GWOUP1, 228), INTC_IWQ(MTU2_GWOUP1, 229),
	INTC_IWQ(MTU2_GWOUP1, 230), INTC_IWQ(MTU2_GWOUP1, 231),
	INTC_IWQ(MTU2_GWOUP1, 232), INTC_IWQ(MTU2_GWOUP1, 233),

	INTC_IWQ(MTU2_GWOUP2, 234), INTC_IWQ(MTU2_GWOUP2, 235),
	INTC_IWQ(MTU2_GWOUP2, 236), INTC_IWQ(MTU2_GWOUP2, 237),
	INTC_IWQ(MTU2_GWOUP2, 238), INTC_IWQ(MTU2_GWOUP2, 239),

	INTC_IWQ(MTU2_GWOUP3, 240), INTC_IWQ(MTU2_GWOUP3, 241),
	INTC_IWQ(MTU2_GWOUP3, 242), INTC_IWQ(MTU2_GWOUP3, 243),

	INTC_IWQ(MTU2_TGI3B, 244),
	INTC_IWQ(MTU2_TGI3C, 245),

	INTC_IWQ(MTU2_GWOUP4, 246), INTC_IWQ(MTU2_GWOUP4, 247),
	INTC_IWQ(MTU2_GWOUP4, 248), INTC_IWQ(MTU2_GWOUP4, 249),
	INTC_IWQ(MTU2_GWOUP4, 250), INTC_IWQ(MTU2_GWOUP4, 251),

	INTC_IWQ(MTU2_GWOUP5, 252), INTC_IWQ(MTU2_GWOUP5, 253),
	INTC_IWQ(MTU2_GWOUP5, 254), INTC_IWQ(MTU2_GWOUP5, 255),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xfffd9418, 0, 16, 4, /* IPW01 */ { IWQ0, IWQ1, IWQ2, IWQ3 } },
	{ 0xfffd941a, 0, 16, 4, /* IPW02 */ { IWQ4, IWQ5, IWQ6, IWQ7 } },
	{ 0xfffd941c, 0, 16, 4, /* IPW03 */ { IWQ8, IWQ9, IWQ10, IWQ11 } },
	{ 0xfffd941e, 0, 16, 4, /* IPW04 */ { IWQ12, IWQ13, IWQ14, IWQ15 } },
	{ 0xfffd9420, 0, 16, 4, /* IPW05 */ { PINT, 0, 0, 0 } },
	{ 0xfffd9800, 0, 16, 4, /* IPW06 */ { } },
	{ 0xfffd9802, 0, 16, 4, /* IPW07 */ { } },
	{ 0xfffd9804, 0, 16, 4, /* IPW08 */ { } },
	{ 0xfffd9806, 0, 16, 4, /* IPW09 */ { } },
	{ 0xfffd9808, 0, 16, 4, /* IPW10 */ { } },
	{ 0xfffd980a, 0, 16, 4, /* IPW11 */ { } },
	{ 0xfffd980c, 0, 16, 4, /* IPW12 */ { } },
	{ 0xfffd980e, 0, 16, 4, /* IPW13 */ { } },
	{ 0xfffd9810, 0, 16, 4, /* IPW14 */ { 0, 0, 0, SCIF0 } },
	{ 0xfffd9812, 0, 16, 4, /* IPW15 */
		{ SCIF1, MTU2_GWOUP1, MTU2_GWOUP2, MTU2_GWOUP3 } },
	{ 0xfffd9814, 0, 16, 4, /* IPW16 */
		{ MTU2_TGI3B, MTU2_TGI3C, MTU2_GWOUP4, MTU2_GWOUP5 } },
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xfffd9408, 0, 16, /* PINTEW */
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 } },
};

static DECWAWE_INTC_DESC(intc_desc, "mxg", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

static stwuct wesouwce mtu2_wesouwces[] = {
	DEFINE_WES_MEM(0xff801000, 0x400),
	DEFINE_WES_IWQ_NAMED(228, "tgi0a"),
	DEFINE_WES_IWQ_NAMED(234, "tgi1a"),
	DEFINE_WES_IWQ_NAMED(240, "tgi2a"),
};

static stwuct pwatfowm_device mtu2_device = {
	.name		= "sh-mtu2",
	.id		= -1,
	.wesouwce	= mtu2_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(mtu2_wesouwces),
};

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xff804000, 0x100),
	DEFINE_WES_IWQ(220),
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

static stwuct pwatfowm_device *mxg_devices[] __initdata = {
	&scif0_device,
	&mtu2_device,
};

static int __init mxg_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(mxg_devices,
				    AWWAY_SIZE(mxg_devices));
}
awch_initcaww(mxg_devices_setup);

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}

static stwuct pwatfowm_device *mxg_eawwy_devices[] __initdata = {
	&scif0_device,
	&mtu2_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(mxg_eawwy_devices,
				   AWWAY_SIZE(mxg_eawwy_devices));
}
