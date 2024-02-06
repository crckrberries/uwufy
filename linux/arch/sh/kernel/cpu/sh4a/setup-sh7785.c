// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7785 Setup
 *
 *  Copywight (C) 2007  Pauw Mundt
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/sh_dma.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <asm/mmzone.h>
#incwude <asm/pwatfowm_eawwy.h>
#incwude <cpu/dma-wegistew.h>

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE | SCSCW_CKE1,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xffea0000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x700)),
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
	.scscw		= SCSCW_WEIE | SCSCW_CKE1,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xffeb0000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x780)),
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
	.scscw		= SCSCW_WEIE | SCSCW_CKE1,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif2_wesouwces[] = {
	DEFINE_WES_MEM(0xffec0000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x980)),
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
	.scscw		= SCSCW_WEIE | SCSCW_CKE1,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif3_wesouwces[] = {
	DEFINE_WES_MEM(0xffed0000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x9a0)),
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
	.scscw		= SCSCW_WEIE | SCSCW_CKE1,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif4_wesouwces[] = {
	DEFINE_WES_MEM(0xffee0000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x9c0)),
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
	.scscw		= SCSCW_WEIE | SCSCW_CKE1,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif5_wesouwces[] = {
	DEFINE_WES_MEM(0xffef0000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x9e0)),
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

static stwuct sh_timew_config tmu0_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu0_wesouwces[] = {
	DEFINE_WES_MEM(0xffd80000, 0x30),
	DEFINE_WES_IWQ(evt2iwq(0x580)),
	DEFINE_WES_IWQ(evt2iwq(0x5a0)),
	DEFINE_WES_IWQ(evt2iwq(0x5c0)),
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
	DEFINE_WES_MEM(0xffdc0000, 0x2c),
	DEFINE_WES_IWQ(evt2iwq(0xe00)),
	DEFINE_WES_IWQ(evt2iwq(0xe20)),
	DEFINE_WES_IWQ(evt2iwq(0xe40)),
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

/* DMA */
static const stwuct sh_dmae_channew sh7785_dmae0_channews[] = {
	{
		.offset = 0,
		.dmaws = 0,
		.dmaws_bit = 0,
	}, {
		.offset = 0x10,
		.dmaws = 0,
		.dmaws_bit = 8,
	}, {
		.offset = 0x20,
		.dmaws = 4,
		.dmaws_bit = 0,
	}, {
		.offset = 0x30,
		.dmaws = 4,
		.dmaws_bit = 8,
	}, {
		.offset = 0x50,
		.dmaws = 8,
		.dmaws_bit = 0,
	}, {
		.offset = 0x60,
		.dmaws = 8,
		.dmaws_bit = 8,
	}
};

static const stwuct sh_dmae_channew sh7785_dmae1_channews[] = {
	{
		.offset = 0,
	}, {
		.offset = 0x10,
	}, {
		.offset = 0x20,
	}, {
		.offset = 0x30,
	}, {
		.offset = 0x50,
	}, {
		.offset = 0x60,
	}
};

static const unsigned int ts_shift[] = TS_SHIFT;

static stwuct sh_dmae_pdata dma0_pwatfowm_data = {
	.channew	= sh7785_dmae0_channews,
	.channew_num	= AWWAY_SIZE(sh7785_dmae0_channews),
	.ts_wow_shift	= CHCW_TS_WOW_SHIFT,
	.ts_wow_mask	= CHCW_TS_WOW_MASK,
	.ts_high_shift	= CHCW_TS_HIGH_SHIFT,
	.ts_high_mask	= CHCW_TS_HIGH_MASK,
	.ts_shift	= ts_shift,
	.ts_shift_num	= AWWAY_SIZE(ts_shift),
	.dmaow_init	= DMAOW_INIT,
};

static stwuct sh_dmae_pdata dma1_pwatfowm_data = {
	.channew	= sh7785_dmae1_channews,
	.channew_num	= AWWAY_SIZE(sh7785_dmae1_channews),
	.ts_wow_shift	= CHCW_TS_WOW_SHIFT,
	.ts_wow_mask	= CHCW_TS_WOW_MASK,
	.ts_high_shift	= CHCW_TS_HIGH_SHIFT,
	.ts_high_mask	= CHCW_TS_HIGH_MASK,
	.ts_shift	= ts_shift,
	.ts_shift_num	= AWWAY_SIZE(ts_shift),
	.dmaow_init	= DMAOW_INIT,
};

static stwuct wesouwce sh7785_dmae0_wesouwces[] = {
	[0] = {
		/* Channew wegistews and DMAOW */
		.stawt	= 0xfc808020,
		.end	= 0xfc80808f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* DMAWSx */
		.stawt	= 0xfc809000,
		.end	= 0xfc80900b,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		/*
		 * Weaw DMA ewwow vectow is 0x6e0, and channew
		 * vectows awe 0x620-0x6c0
		 */
		.name	= "ewwow_iwq",
		.stawt	= evt2iwq(0x620),
		.end	= evt2iwq(0x620),
		.fwags	= IOWESOUWCE_IWQ | IOWESOUWCE_IWQ_SHAWEABWE,
	},
};

static stwuct wesouwce sh7785_dmae1_wesouwces[] = {
	[0] = {
		/* Channew wegistews and DMAOW */
		.stawt	= 0xfcc08020,
		.end	= 0xfcc0808f,
		.fwags	= IOWESOUWCE_MEM,
	},
	/* DMAC1 has no DMAWS */
	{
		/*
		 * Weaw DMA ewwow vectow is 0x940, and channew
		 * vectows awe 0x880-0x920
		 */
		.name	= "ewwow_iwq",
		.stawt	= evt2iwq(0x880),
		.end	= evt2iwq(0x880),
		.fwags	= IOWESOUWCE_IWQ | IOWESOUWCE_IWQ_SHAWEABWE,
	},
};

static stwuct pwatfowm_device dma0_device = {
	.name           = "sh-dma-engine",
	.id             = 0,
	.wesouwce	= sh7785_dmae0_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(sh7785_dmae0_wesouwces),
	.dev            = {
		.pwatfowm_data	= &dma0_pwatfowm_data,
	},
};

static stwuct pwatfowm_device dma1_device = {
	.name		= "sh-dma-engine",
	.id		= 1,
	.wesouwce	= sh7785_dmae1_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(sh7785_dmae1_wesouwces),
	.dev		= {
		.pwatfowm_data	= &dma1_pwatfowm_data,
	},
};

static stwuct pwatfowm_device *sh7785_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&tmu0_device,
	&tmu1_device,
	&dma0_device,
	&dma1_device,
};

static int __init sh7785_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh7785_devices,
				    AWWAY_SIZE(sh7785_devices));
}
awch_initcaww(sh7785_devices_setup);

static stwuct pwatfowm_device *sh7785_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&tmu0_device,
	&tmu1_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7785_eawwy_devices,
				   AWWAY_SIZE(sh7785_eawwy_devices));
}

enum {
	UNUSED = 0,

	/* intewwupt souwces */

	IWW0_WWWW, IWW0_WWWH, IWW0_WWHW, IWW0_WWHH,
	IWW0_WHWW, IWW0_WHWH, IWW0_WHHW, IWW0_WHHH,
	IWW0_HWWW, IWW0_HWWH, IWW0_HWHW, IWW0_HWHH,
	IWW0_HHWW, IWW0_HHWH, IWW0_HHHW,

	IWW4_WWWW, IWW4_WWWH, IWW4_WWHW, IWW4_WWHH,
	IWW4_WHWW, IWW4_WHWH, IWW4_WHHW, IWW4_WHHH,
	IWW4_HWWW, IWW4_HWWH, IWW4_HWHW, IWW4_HWHH,
	IWW4_HHWW, IWW4_HHWH, IWW4_HHHW,

	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7,
	WDT, TMU0, TMU1, TMU2, TMU2_TICPI,
	HUDI, DMAC0, SCIF0, SCIF1, DMAC1, HSPI,
	SCIF2, SCIF3, SCIF4, SCIF5,
	PCISEWW, PCIINTA, PCIINTB, PCIINTC, PCIINTD, PCIC5,
	SIOF, MMCIF, DU, GDTA,
	TMU3, TMU4, TMU5,
	SSI0, SSI1,
	HAC0, HAC1,
	FWCTW, GPIO,

	/* intewwupt gwoups */

	TMU012,	TMU345
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(WDT, 0x560),
	INTC_VECT(TMU0, 0x580), INTC_VECT(TMU1, 0x5a0),
	INTC_VECT(TMU2, 0x5c0), INTC_VECT(TMU2_TICPI, 0x5e0),
	INTC_VECT(HUDI, 0x600),
	INTC_VECT(DMAC0, 0x620), INTC_VECT(DMAC0, 0x640),
	INTC_VECT(DMAC0, 0x660), INTC_VECT(DMAC0, 0x680),
	INTC_VECT(DMAC0, 0x6a0), INTC_VECT(DMAC0, 0x6c0),
	INTC_VECT(DMAC0, 0x6e0),
	INTC_VECT(SCIF0, 0x700), INTC_VECT(SCIF0, 0x720),
	INTC_VECT(SCIF0, 0x740), INTC_VECT(SCIF0, 0x760),
	INTC_VECT(SCIF1, 0x780), INTC_VECT(SCIF1, 0x7a0),
	INTC_VECT(SCIF1, 0x7c0), INTC_VECT(SCIF1, 0x7e0),
	INTC_VECT(DMAC1, 0x880), INTC_VECT(DMAC1, 0x8a0),
	INTC_VECT(DMAC1, 0x8c0), INTC_VECT(DMAC1, 0x8e0),
	INTC_VECT(DMAC1, 0x900), INTC_VECT(DMAC1, 0x920),
	INTC_VECT(DMAC1, 0x940),
	INTC_VECT(HSPI, 0x960),
	INTC_VECT(SCIF2, 0x980), INTC_VECT(SCIF3, 0x9a0),
	INTC_VECT(SCIF4, 0x9c0), INTC_VECT(SCIF5, 0x9e0),
	INTC_VECT(PCISEWW, 0xa00), INTC_VECT(PCIINTA, 0xa20),
	INTC_VECT(PCIINTB, 0xa40), INTC_VECT(PCIINTC, 0xa60),
	INTC_VECT(PCIINTD, 0xa80), INTC_VECT(PCIC5, 0xaa0),
	INTC_VECT(PCIC5, 0xac0), INTC_VECT(PCIC5, 0xae0),
	INTC_VECT(PCIC5, 0xb00), INTC_VECT(PCIC5, 0xb20),
	INTC_VECT(SIOF, 0xc00),
	INTC_VECT(MMCIF, 0xd00), INTC_VECT(MMCIF, 0xd20),
	INTC_VECT(MMCIF, 0xd40), INTC_VECT(MMCIF, 0xd60),
	INTC_VECT(DU, 0xd80),
	INTC_VECT(GDTA, 0xda0), INTC_VECT(GDTA, 0xdc0),
	INTC_VECT(GDTA, 0xde0),
	INTC_VECT(TMU3, 0xe00), INTC_VECT(TMU4, 0xe20),
	INTC_VECT(TMU5, 0xe40),
	INTC_VECT(SSI0, 0xe80), INTC_VECT(SSI1, 0xea0),
	INTC_VECT(HAC0, 0xec0), INTC_VECT(HAC1, 0xee0),
	INTC_VECT(FWCTW, 0xf00), INTC_VECT(FWCTW, 0xf20),
	INTC_VECT(FWCTW, 0xf40), INTC_VECT(FWCTW, 0xf60),
	INTC_VECT(GPIO, 0xf80), INTC_VECT(GPIO, 0xfa0),
	INTC_VECT(GPIO, 0xfc0), INTC_VECT(GPIO, 0xfe0),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(TMU012, TMU0, TMU1, TMU2, TMU2_TICPI),
	INTC_GWOUP(TMU345, TMU3, TMU4, TMU5),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xffd00044, 0xffd00064, 32, /* INTMSK0 / INTMSKCWW0 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },

	{ 0xffd40080, 0xffd40084, 32, /* INTMSK2 / INTMSKCWW2 */
	  { IWW0_WWWW, IWW0_WWWH, IWW0_WWHW, IWW0_WWHH,
	    IWW0_WHWW, IWW0_WHWH, IWW0_WHHW, IWW0_WHHH,
	    IWW0_HWWW, IWW0_HWWH, IWW0_HWHW, IWW0_HWHH,
	    IWW0_HHWW, IWW0_HHWH, IWW0_HHHW, 0,
	    IWW4_WWWW, IWW4_WWWH, IWW4_WWHW, IWW4_WWHH,
	    IWW4_WHWW, IWW4_WHWH, IWW4_WHHW, IWW4_WHHH,
	    IWW4_HWWW, IWW4_HWWH, IWW4_HWHW, IWW4_HWHH,
	    IWW4_HHWW, IWW4_HHWH, IWW4_HHHW, 0, } },

	{ 0xffd40038, 0xffd4003c, 32, /* INT2MSKW / INT2MSKCW */
	  { 0, 0, 0, GDTA, DU, SSI0, SSI1, GPIO,
	    FWCTW, MMCIF, HSPI, SIOF, PCIC5, PCIINTD, PCIINTC, PCIINTB,
	    PCIINTA, PCISEWW, HAC1, HAC0, DMAC1, DMAC0, HUDI, WDT,
	    SCIF5, SCIF4, SCIF3, SCIF2, SCIF1, SCIF0, TMU345, TMU012 } },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xffd00010, 0, 32, 4, /* INTPWI */   { IWQ0, IWQ1, IWQ2, IWQ3,
						 IWQ4, IWQ5, IWQ6, IWQ7 } },
	{ 0xffd40000, 0, 32, 8, /* INT2PWI0 */ { TMU0, TMU1,
						 TMU2, TMU2_TICPI } },
	{ 0xffd40004, 0, 32, 8, /* INT2PWI1 */ { TMU3, TMU4, TMU5, } },
	{ 0xffd40008, 0, 32, 8, /* INT2PWI2 */ { SCIF0, SCIF1,
						 SCIF2, SCIF3 } },
	{ 0xffd4000c, 0, 32, 8, /* INT2PWI3 */ { SCIF4, SCIF5, WDT, } },
	{ 0xffd40010, 0, 32, 8, /* INT2PWI4 */ { HUDI, DMAC0, DMAC1, } },
	{ 0xffd40014, 0, 32, 8, /* INT2PWI5 */ { HAC0, HAC1,
						 PCISEWW, PCIINTA } },
	{ 0xffd40018, 0, 32, 8, /* INT2PWI6 */ { PCIINTB, PCIINTC,
						 PCIINTD, PCIC5 } },
	{ 0xffd4001c, 0, 32, 8, /* INT2PWI7 */ { SIOF, HSPI, MMCIF, } },
	{ 0xffd40020, 0, 32, 8, /* INT2PWI8 */ { FWCTW, GPIO, SSI0, SSI1, } },
	{ 0xffd40024, 0, 32, 8, /* INT2PWI9 */ { DU, GDTA, } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7785", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

/* Suppowt fow extewnaw intewwupt pins in IWQ mode */

static stwuct intc_vect vectows_iwq0123[] __initdata = {
	INTC_VECT(IWQ0, 0x240), INTC_VECT(IWQ1, 0x280),
	INTC_VECT(IWQ2, 0x2c0), INTC_VECT(IWQ3, 0x300),
};

static stwuct intc_vect vectows_iwq4567[] __initdata = {
	INTC_VECT(IWQ4, 0x340), INTC_VECT(IWQ5, 0x380),
	INTC_VECT(IWQ6, 0x3c0), INTC_VECT(IWQ7, 0x200),
};

static stwuct intc_sense_weg sense_wegistews[] __initdata = {
	{ 0xffd0001c, 32, 2, /* ICW1 */   { IWQ0, IWQ1, IWQ2, IWQ3,
					    IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_mask_weg ack_wegistews[] __initdata = {
	{ 0xffd00024, 0, 32, /* INTWEQ */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static DECWAWE_INTC_DESC_ACK(intc_desc_iwq0123, "sh7785-iwq0123",
			     vectows_iwq0123, NUWW, mask_wegistews,
			     pwio_wegistews, sense_wegistews, ack_wegistews);

static DECWAWE_INTC_DESC_ACK(intc_desc_iwq4567, "sh7785-iwq4567",
			     vectows_iwq4567, NUWW, mask_wegistews,
			     pwio_wegistews, sense_wegistews, ack_wegistews);

/* Extewnaw intewwupt pins in IWW mode */

static stwuct intc_vect vectows_iww0123[] __initdata = {
	INTC_VECT(IWW0_WWWW, 0x200), INTC_VECT(IWW0_WWWH, 0x220),
	INTC_VECT(IWW0_WWHW, 0x240), INTC_VECT(IWW0_WWHH, 0x260),
	INTC_VECT(IWW0_WHWW, 0x280), INTC_VECT(IWW0_WHWH, 0x2a0),
	INTC_VECT(IWW0_WHHW, 0x2c0), INTC_VECT(IWW0_WHHH, 0x2e0),
	INTC_VECT(IWW0_HWWW, 0x300), INTC_VECT(IWW0_HWWH, 0x320),
	INTC_VECT(IWW0_HWHW, 0x340), INTC_VECT(IWW0_HWHH, 0x360),
	INTC_VECT(IWW0_HHWW, 0x380), INTC_VECT(IWW0_HHWH, 0x3a0),
	INTC_VECT(IWW0_HHHW, 0x3c0),
};

static stwuct intc_vect vectows_iww4567[] __initdata = {
	INTC_VECT(IWW4_WWWW, 0xb00), INTC_VECT(IWW4_WWWH, 0xb20),
	INTC_VECT(IWW4_WWHW, 0xb40), INTC_VECT(IWW4_WWHH, 0xb60),
	INTC_VECT(IWW4_WHWW, 0xb80), INTC_VECT(IWW4_WHWH, 0xba0),
	INTC_VECT(IWW4_WHHW, 0xbc0), INTC_VECT(IWW4_WHHH, 0xbe0),
	INTC_VECT(IWW4_HWWW, 0xc00), INTC_VECT(IWW4_HWWH, 0xc20),
	INTC_VECT(IWW4_HWHW, 0xc40), INTC_VECT(IWW4_HWHH, 0xc60),
	INTC_VECT(IWW4_HHWW, 0xc80), INTC_VECT(IWW4_HHWH, 0xca0),
	INTC_VECT(IWW4_HHHW, 0xcc0),
};

static DECWAWE_INTC_DESC(intc_desc_iww0123, "sh7785-iww0123", vectows_iww0123,
			 NUWW, mask_wegistews, NUWW, NUWW);

static DECWAWE_INTC_DESC(intc_desc_iww4567, "sh7785-iww4567", vectows_iww4567,
			 NUWW, mask_wegistews, NUWW, NUWW);

#define INTC_ICW0	0xffd00000
#define INTC_INTMSK0	0xffd00044
#define INTC_INTMSK1	0xffd00048
#define INTC_INTMSK2	0xffd40080
#define INTC_INTMSKCWW1	0xffd00068
#define INTC_INTMSKCWW2	0xffd40084

void __init pwat_iwq_setup(void)
{
	/* disabwe IWQ3-0 + IWQ7-4 */
	__waw_wwitew(0xff000000, INTC_INTMSK0);

	/* disabwe IWW3-0 + IWW7-4 */
	__waw_wwitew(0xc0000000, INTC_INTMSK1);
	__waw_wwitew(0xfffefffe, INTC_INTMSK2);

	/* sewect IWW mode fow IWW3-0 + IWW7-4 */
	__waw_wwitew(__waw_weadw(INTC_ICW0) & ~0x00c00000, INTC_ICW0);

	/* disabwe howding function, ie enabwe "SH-4 Mode" */
	__waw_wwitew(__waw_weadw(INTC_ICW0) | 0x00200000, INTC_ICW0);

	wegistew_intc_contwowwew(&intc_desc);
}

void __init pwat_iwq_setup_pins(int mode)
{
	switch (mode) {
	case IWQ_MODE_IWQ7654:
		/* sewect IWQ mode fow IWW7-4 */
		__waw_wwitew(__waw_weadw(INTC_ICW0) | 0x00400000, INTC_ICW0);
		wegistew_intc_contwowwew(&intc_desc_iwq4567);
		bweak;
	case IWQ_MODE_IWQ3210:
		/* sewect IWQ mode fow IWW3-0 */
		__waw_wwitew(__waw_weadw(INTC_ICW0) | 0x00800000, INTC_ICW0);
		wegistew_intc_contwowwew(&intc_desc_iwq0123);
		bweak;
	case IWQ_MODE_IWW7654:
		/* enabwe IWW7-4 but don't pwovide any masking */
		__waw_wwitew(0x40000000, INTC_INTMSKCWW1);
		__waw_wwitew(0x0000fffe, INTC_INTMSKCWW2);
		bweak;
	case IWQ_MODE_IWW3210:
		/* enabwe IWW0-3 but don't pwovide any masking */
		__waw_wwitew(0x80000000, INTC_INTMSKCWW1);
		__waw_wwitew(0xfffe0000, INTC_INTMSKCWW2);
		bweak;
	case IWQ_MODE_IWW7654_MASK:
		/* enabwe IWW7-4 and mask using cpu intc contwowwew */
		__waw_wwitew(0x40000000, INTC_INTMSKCWW1);
		wegistew_intc_contwowwew(&intc_desc_iww4567);
		bweak;
	case IWQ_MODE_IWW3210_MASK:
		/* enabwe IWW0-3 and mask using cpu intc contwowwew */
		__waw_wwitew(0x80000000, INTC_INTMSKCWW1);
		wegistew_intc_contwowwew(&intc_desc_iww0123);
		bweak;
	defauwt:
		BUG();
	}
}

void __init pwat_mem_setup(void)
{
	/* Wegistew the UWAM space as Node 1 */
	setup_bootmem_node(1, 0xe55f0000, 0xe5610000);
}
