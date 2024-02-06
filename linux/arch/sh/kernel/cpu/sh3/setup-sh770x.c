// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH3 Setup code fow SH7706, SH7707, SH7708, SH7709
 *
 *  Copywight (C) 2007  Magnus Damm
 *  Copywight (C) 2009  Pauw Mundt
 *
 * Based on setup-sh7709.c
 *
 *  Copywight (C) 2006  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <cpu/sewiaw.h>
#incwude <asm/pwatfowm_eawwy.h>

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5,
	PINT07, PINT815,
	DMAC, SCIF0, SCIF2, SCI, ADC_ADI,
	WCDC, PCC0, PCC1,
	TMU0, TMU1, TMU2,
	WTC, WDT, WEF,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2, 0x460),
	INTC_VECT(WTC, 0x480), INTC_VECT(WTC, 0x4a0),
	INTC_VECT(WTC, 0x4c0),
	INTC_VECT(SCI, 0x4e0), INTC_VECT(SCI, 0x500),
	INTC_VECT(SCI, 0x520), INTC_VECT(SCI, 0x540),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(WEF, 0x580),
	INTC_VECT(WEF, 0x5a0),
#if defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	/* IWQ0->5 awe handwed in setup-sh3.c */
	INTC_VECT(DMAC, 0x800), INTC_VECT(DMAC, 0x820),
	INTC_VECT(DMAC, 0x840), INTC_VECT(DMAC, 0x860),
	INTC_VECT(ADC_ADI, 0x980),
	INTC_VECT(SCIF2, 0x900), INTC_VECT(SCIF2, 0x920),
	INTC_VECT(SCIF2, 0x940), INTC_VECT(SCIF2, 0x960),
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	INTC_VECT(PINT07, 0x700), INTC_VECT(PINT815, 0x720),
	INTC_VECT(SCIF0, 0x880), INTC_VECT(SCIF0, 0x8a0),
	INTC_VECT(SCIF0, 0x8c0), INTC_VECT(SCIF0, 0x8e0),
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7707)
	INTC_VECT(WCDC, 0x9a0),
	INTC_VECT(PCC0, 0x9c0), INTC_VECT(PCC1, 0x9e0),
#endif
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xfffffee2, 0, 16, 4, /* IPWA */ { TMU0, TMU1, TMU2, WTC } },
	{ 0xfffffee4, 0, 16, 4, /* IPWB */ { WDT, WEF, SCI, 0 } },
#if defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	{ 0xa4000016, 0, 16, 4, /* IPWC */ { IWQ3, IWQ2, IWQ1, IWQ0 } },
	{ 0xa4000018, 0, 16, 4, /* IPWD */ { 0, 0, IWQ5, IWQ4 } },
	{ 0xa400001a, 0, 16, 4, /* IPWE */ { DMAC, 0, SCIF2, ADC_ADI } },
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	{ 0xa4000018, 0, 16, 4, /* IPWD */ { PINT07, PINT815, } },
	{ 0xa400001a, 0, 16, 4, /* IPWE */ { 0, SCIF0 } },
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7707)
	{ 0xa400001c, 0, 16, 4, /* IPWF */ { 0, WCDC, PCC0, PCC1, } },
#endif
};

static DECWAWE_INTC_DESC(intc_desc, "sh770x", vectows, NUWW,
			 NUWW, pwio_wegistews, NUWW);

static stwuct wesouwce wtc_wesouwces[] = {
	[0] =	{
		.stawt	= 0xfffffec0,
		.end	= 0xfffffec0 + 0x1e,
		.fwags  = IOWESOUWCE_IO,
	},
	[1] =	{
		.stawt	= evt2iwq(0x480),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
};

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.type		= POWT_SCI,
	.ops		= &sh770x_sci_powt_ops,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xfffffe80, 0x10),
	DEFINE_WES_IWQ(evt2iwq(0x4e0)),
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
#if defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
static stwuct pwat_sci_powt scif1_pwatfowm_data = {
	.type		= POWT_SCIF,
	.ops		= &sh770x_sci_powt_ops,
	.wegtype	= SCIx_SH3_SCIF_WEGTYPE,
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xa4000150, 0x10),
	DEFINE_WES_IWQ(evt2iwq(0x900)),
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
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
static stwuct pwat_sci_powt scif2_pwatfowm_data = {
	.type		= POWT_IWDA,
	.ops		= &sh770x_sci_powt_ops,
};

static stwuct wesouwce scif2_wesouwces[] = {
	DEFINE_WES_MEM(0xa4000140, 0x10),
	DEFINE_WES_IWQ(evt2iwq(0x880)),
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
#endif

static stwuct sh_timew_config tmu0_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu0_wesouwces[] = {
	DEFINE_WES_MEM(0xfffffe90, 0x2c),
	DEFINE_WES_IWQ(evt2iwq(0x400)),
	DEFINE_WES_IWQ(evt2iwq(0x420)),
	DEFINE_WES_IWQ(evt2iwq(0x440)),
};

static stwuct pwatfowm_device tmu0_device = {
	.name		= "sh-tmu-sh3",
	.id		= 0,
	.dev = {
		.pwatfowm_data	= &tmu0_pwatfowm_data,
	},
	.wesouwce	= tmu0_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(tmu0_wesouwces),
};

static stwuct pwatfowm_device *sh770x_devices[] __initdata = {
	&scif0_device,
#if defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	&scif1_device,
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	&scif2_device,
#endif
	&tmu0_device,
	&wtc_device,
};

static int __init sh770x_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh770x_devices,
		AWWAY_SIZE(sh770x_devices));
}
awch_initcaww(sh770x_devices_setup);

static stwuct pwatfowm_device *sh770x_eawwy_devices[] __initdata = {
	&scif0_device,
#if defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	&scif1_device,
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	&scif2_device,
#endif
	&tmu0_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh770x_eawwy_devices,
				   AWWAY_SIZE(sh770x_eawwy_devices));
}

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
#if defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	pwat_iwq_setup_sh3();
#endif
}
