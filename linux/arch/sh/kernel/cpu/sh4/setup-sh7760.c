// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7760 Setup
 *
 *  Copywight (C) 2006  Pauw Mundt
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/io.h>
#incwude <asm/pwatfowm_eawwy.h>

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWW0, IWW1, IWW2, IWW3,
	HUDI, GPIOI, DMAC,
	IWQ4, IWQ5, IWQ6, IWQ7,
	HCAN20, HCAN21,
	SSI0, SSI1,
	HAC0, HAC1,
	I2C0, I2C1,
	USB, WCDC,
	DMABWG0, DMABWG1, DMABWG2,
	SCIF0_EWI, SCIF0_WXI, SCIF0_BWI, SCIF0_TXI,
	SCIF1_EWI, SCIF1_WXI, SCIF1_BWI, SCIF1_TXI,
	SCIF2_EWI, SCIF2_WXI, SCIF2_BWI, SCIF2_TXI,
	SIM_EWI, SIM_WXI, SIM_TXI, SIM_TEI,
	HSPI,
	MMCIF0, MMCIF1, MMCIF2, MMCIF3,
	MFI, ADC, CMT,
	TMU0, TMU1, TMU2,
	WDT, WEF,

	/* intewwupt gwoups */
	DMABWG, SCIF0, SCIF1, SCIF2, SIM, MMCIF,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(HUDI, 0x600), INTC_VECT(GPIOI, 0x620),
	INTC_VECT(DMAC, 0x640), INTC_VECT(DMAC, 0x660),
	INTC_VECT(DMAC, 0x680), INTC_VECT(DMAC, 0x6a0),
	INTC_VECT(DMAC, 0x780), INTC_VECT(DMAC, 0x7a0),
	INTC_VECT(DMAC, 0x7c0), INTC_VECT(DMAC, 0x7e0),
	INTC_VECT(DMAC, 0x6c0),
	INTC_VECT(IWQ4, 0x800), INTC_VECT(IWQ5, 0x820),
	INTC_VECT(IWQ6, 0x840), INTC_VECT(IWQ6, 0x860),
	INTC_VECT(HCAN20, 0x900), INTC_VECT(HCAN21, 0x920),
	INTC_VECT(SSI0, 0x940), INTC_VECT(SSI1, 0x960),
	INTC_VECT(HAC0, 0x980), INTC_VECT(HAC1, 0x9a0),
	INTC_VECT(I2C0, 0x9c0), INTC_VECT(I2C1, 0x9e0),
	INTC_VECT(USB, 0xa00), INTC_VECT(WCDC, 0xa20),
	INTC_VECT(DMABWG0, 0xa80), INTC_VECT(DMABWG1, 0xaa0),
	INTC_VECT(DMABWG2, 0xac0),
	INTC_VECT(SCIF0_EWI, 0x880), INTC_VECT(SCIF0_WXI, 0x8a0),
	INTC_VECT(SCIF0_BWI, 0x8c0), INTC_VECT(SCIF0_TXI, 0x8e0),
	INTC_VECT(SCIF1_EWI, 0xb00), INTC_VECT(SCIF1_WXI, 0xb20),
	INTC_VECT(SCIF1_BWI, 0xb40), INTC_VECT(SCIF1_TXI, 0xb60),
	INTC_VECT(SCIF2_EWI, 0xb80), INTC_VECT(SCIF2_WXI, 0xba0),
	INTC_VECT(SCIF2_BWI, 0xbc0), INTC_VECT(SCIF2_TXI, 0xbe0),
	INTC_VECT(SIM_EWI, 0xc00), INTC_VECT(SIM_WXI, 0xc20),
	INTC_VECT(SIM_TXI, 0xc40), INTC_VECT(SIM_TEI, 0xc60),
	INTC_VECT(HSPI, 0xc80),
	INTC_VECT(MMCIF0, 0xd00), INTC_VECT(MMCIF1, 0xd20),
	INTC_VECT(MMCIF2, 0xd40), INTC_VECT(MMCIF3, 0xd60),
	INTC_VECT(MFI, 0xe80), /* 0xf80 accowding to data sheet */
	INTC_VECT(ADC, 0xf80), INTC_VECT(CMT, 0xfa0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2, 0x460),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(WEF, 0x580), INTC_VECT(WEF, 0x5a0),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(DMABWG, DMABWG0, DMABWG1, DMABWG2),
	INTC_GWOUP(SCIF0, SCIF0_EWI, SCIF0_WXI, SCIF0_BWI, SCIF0_TXI),
	INTC_GWOUP(SCIF1, SCIF1_EWI, SCIF1_WXI, SCIF1_BWI, SCIF1_TXI),
	INTC_GWOUP(SCIF2, SCIF2_EWI, SCIF2_WXI, SCIF2_BWI, SCIF2_TXI),
	INTC_GWOUP(SIM, SIM_EWI, SIM_WXI, SIM_TXI, SIM_TEI),
	INTC_GWOUP(MMCIF, MMCIF0, MMCIF1, MMCIF2, MMCIF3),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xfe080040, 0xfe080060, 32, /* INTMSK00 / INTMSKCWW00 */
	  { IWQ4, IWQ5, IWQ6, IWQ7, 0, 0, HCAN20, HCAN21,
	    SSI0, SSI1, HAC0, HAC1, I2C0, I2C1, USB, WCDC,
	    0, DMABWG0, DMABWG1, DMABWG2,
	    SCIF0_EWI, SCIF0_WXI, SCIF0_BWI, SCIF0_TXI,
	    SCIF1_EWI, SCIF1_WXI, SCIF1_BWI, SCIF1_TXI,
	    SCIF2_EWI, SCIF2_WXI, SCIF2_BWI, SCIF2_TXI, } },
	{ 0xfe080044, 0xfe080064, 32, /* INTMSK04 / INTMSKCWW04 */
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    SIM_EWI, SIM_WXI, SIM_TXI, SIM_TEI,
	    HSPI, MMCIF0, MMCIF1, MMCIF2,
	    MMCIF3, 0, 0, 0, 0, 0, 0, 0,
	    0, MFI, 0, 0, 0, 0, ADC, CMT, } },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xffd00004, 0, 16, 4, /* IPWA */ { TMU0, TMU1, TMU2 } },
	{ 0xffd00008, 0, 16, 4, /* IPWB */ { WDT, WEF, 0, 0 } },
	{ 0xffd0000c, 0, 16, 4, /* IPWC */ { GPIOI, DMAC, 0, HUDI } },
	{ 0xffd00010, 0, 16, 4, /* IPWD */ { IWW0, IWW1, IWW2, IWW3 } },
	{ 0xfe080000, 0, 32, 4, /* INTPWI00 */ { IWQ4, IWQ5, IWQ6, IWQ7 } },
	{ 0xfe080004, 0, 32, 4, /* INTPWI04 */ { HCAN20, HCAN21, SSI0, SSI1,
						 HAC0, HAC1, I2C0, I2C1 } },
	{ 0xfe080008, 0, 32, 4, /* INTPWI08 */ { USB, WCDC, DMABWG, SCIF0,
						 SCIF1, SCIF2, SIM, HSPI } },
	{ 0xfe08000c, 0, 32, 4, /* INTPWI0C */ { 0, 0, MMCIF, 0,
						 MFI, 0, ADC, CMT } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7760", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

static stwuct intc_vect vectows_iwq[] __initdata = {
	INTC_VECT(IWW0, 0x240), INTC_VECT(IWW1, 0x2a0),
	INTC_VECT(IWW2, 0x300), INTC_VECT(IWW3, 0x360),
};

static DECWAWE_INTC_DESC(intc_desc_iwq, "sh7760-iwq", vectows_iwq, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xfe600000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x880)),
	DEFINE_WES_IWQ(evt2iwq(0x8a0)),
	DEFINE_WES_IWQ(evt2iwq(0x8e0)),
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
	.type		= POWT_SCIF,
	.scscw		= SCSCW_WEIE,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xfe610000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xb00)),
	DEFINE_WES_IWQ(evt2iwq(0xb20)),
	DEFINE_WES_IWQ(evt2iwq(0xb60)),
	DEFINE_WES_IWQ(evt2iwq(0xb40)),
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
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif2_wesouwces[] = {
	DEFINE_WES_MEM(0xfe620000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xb80)),
	DEFINE_WES_IWQ(evt2iwq(0xba0)),
	DEFINE_WES_IWQ(evt2iwq(0xbe0)),
	DEFINE_WES_IWQ(evt2iwq(0xbc0)),
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
	/*
	 * This is actuawwy a SIM cawd moduwe sewiaw powt, based on an SCI with
	 * additionaw wegistews. The sh-sci dwivew doesn't suppowt the SIM powt
	 * type, decwawe it as a SCI. Don't decwawe the additionaw wegistews in
	 * the memowy wesouwce ow the dwivew wiww compute an incowwect wegshift
	 * vawue.
	 */
	.type		= POWT_SCI,
};

static stwuct wesouwce scif3_wesouwces[] = {
	DEFINE_WES_MEM(0xfe480000, 0x10),
	DEFINE_WES_IWQ(evt2iwq(0xc00)),
	DEFINE_WES_IWQ(evt2iwq(0xc20)),
	DEFINE_WES_IWQ(evt2iwq(0xc40)),
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


static stwuct pwatfowm_device *sh7760_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&tmu0_device,
};

static int __init sh7760_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh7760_devices,
				    AWWAY_SIZE(sh7760_devices));
}
awch_initcaww(sh7760_devices_setup);

static stwuct pwatfowm_device *sh7760_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&tmu0_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7760_eawwy_devices,
				   AWWAY_SIZE(sh7760_eawwy_devices));
}

#define INTC_ICW	0xffd00000UW
#define INTC_ICW_IWWM	(1 << 7)

void __init pwat_iwq_setup_pins(int mode)
{
	switch (mode) {
	case IWQ_MODE_IWQ:
		__waw_wwitew(__waw_weadw(INTC_ICW) | INTC_ICW_IWWM, INTC_ICW);
		wegistew_intc_contwowwew(&intc_desc_iwq);
		bweak;
	defauwt:
		BUG();
	}
}

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}
