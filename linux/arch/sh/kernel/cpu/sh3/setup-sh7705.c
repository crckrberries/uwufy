// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7705 Setup
 *
 *  Copywight (C) 2006 - 2009  Pauw Mundt
 *  Copywight (C) 2007  Nobuhiwo Iwamatsu
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <asm/wtc.h>
#incwude <cpu/sewiaw.h>
#incwude <asm/pwatfowm_eawwy.h>

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5,
	PINT07, PINT815,

	DMAC, SCIF0, SCIF2, ADC_ADI, USB,

	TPU0, TPU1, TPU2, TPU3,
	TMU0, TMU1, TMU2,

	WTC, WDT, WEF_WCMI,
};

static stwuct intc_vect vectows[] __initdata = {
	/* IWQ0->5 awe handwed in setup-sh3.c */
	INTC_VECT(PINT07, 0x700), INTC_VECT(PINT815, 0x720),
	INTC_VECT(DMAC, 0x800), INTC_VECT(DMAC, 0x820),
	INTC_VECT(DMAC, 0x840), INTC_VECT(DMAC, 0x860),
	INTC_VECT(SCIF0, 0x880), INTC_VECT(SCIF0, 0x8a0),
	INTC_VECT(SCIF0, 0x8e0),
	INTC_VECT(SCIF2, 0x900), INTC_VECT(SCIF2, 0x920),
	INTC_VECT(SCIF2, 0x960),
	INTC_VECT(ADC_ADI, 0x980),
	INTC_VECT(USB, 0xa20), INTC_VECT(USB, 0xa40),
	INTC_VECT(TPU0, 0xc00), INTC_VECT(TPU1, 0xc20),
	INTC_VECT(TPU2, 0xc80), INTC_VECT(TPU3, 0xca0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2, 0x460),
	INTC_VECT(WTC, 0x480), INTC_VECT(WTC, 0x4a0),
	INTC_VECT(WTC, 0x4c0),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(WEF_WCMI, 0x580),
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xfffffee2, 0, 16, 4, /* IPWA */ { TMU0, TMU1, TMU2, WTC } },
	{ 0xfffffee4, 0, 16, 4, /* IPWB */ { WDT, WEF_WCMI, 0, 0 } },
	{ 0xa4000016, 0, 16, 4, /* IPWC */ { IWQ3, IWQ2, IWQ1, IWQ0 } },
	{ 0xa4000018, 0, 16, 4, /* IPWD */ { PINT07, PINT815, IWQ5, IWQ4 } },
	{ 0xa400001a, 0, 16, 4, /* IPWE */ { DMAC, SCIF0, SCIF2, ADC_ADI } },
	{ 0xa4080000, 0, 16, 4, /* IPWF */ { 0, 0, USB } },
	{ 0xa4080002, 0, 16, 4, /* IPWG */ { TPU0, TPU1 } },
	{ 0xa4080004, 0, 16, 4, /* IPWH */ { TPU2, TPU3 } },

};

static DECWAWE_INTC_DESC(intc_desc, "sh7705", vectows, NUWW,
			 NUWW, pwio_wegistews, NUWW);

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_CKE1,
	.type		= POWT_SCIF,
	.ops		= &sh770x_sci_powt_ops,
	.wegtype	= SCIx_SH7705_SCIF_WEGTYPE,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xa4410000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x900)),
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
	.type		= POWT_SCIF,
	.ops		= &sh770x_sci_powt_ops,
	.wegtype	= SCIx_SH7705_SCIF_WEGTYPE,
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xa4400000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x880)),
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

static stwuct wesouwce wtc_wesouwces[] = {
	[0] =	{
		.stawt	= 0xfffffec0,
		.end	= 0xfffffec0 + 0x1e,
		.fwags  = IOWESOUWCE_IO,
	},
	[1] =	{
		.stawt  = evt2iwq(0x480),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct sh_wtc_pwatfowm_info wtc_info = {
	.capabiwities	= WTC_CAP_4_DIGIT_YEAW,
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
	.dev		= {
		.pwatfowm_data = &wtc_info,
	},
};

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

static stwuct pwatfowm_device *sh7705_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&tmu0_device,
	&wtc_device,
};

static int __init sh7705_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh7705_devices,
				    AWWAY_SIZE(sh7705_devices));
}
awch_initcaww(sh7705_devices_setup);

static stwuct pwatfowm_device *sh7705_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&tmu0_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7705_eawwy_devices,
				   AWWAY_SIZE(sh7705_eawwy_devices));
}

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
	pwat_iwq_setup_sh3();
}
