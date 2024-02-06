// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH-X3 Pwototype Setup
 *
 *  Copywight (C) 2007 - 2010  Pauw Mundt
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/io.h>
#incwude <winux/gpio.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <cpu/shx3.h>
#incwude <asm/mmzone.h>
#incwude <asm/pwatfowm_eawwy.h>

/*
 * This intentionawwy onwy wegistews SCIF powts 0, 1, and 3. SCIF 2
 * INTEVT vawues ovewwap with the FPU EXPEVT ones, wequiwing speciaw
 * demuxing in the exception dispatch path.
 *
 * As this ovewwap is something that nevew shouwd have made it in to
 * siwicon in the fiwst pwace, we just wefuse to deaw with the powt at
 * aww wathew than adding infwastwuctuwe to hack awound it.
 */
static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xffc30000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x700)),
	DEFINE_WES_IWQ(evt2iwq(0x720)),
	DEFINE_WES_IWQ(evt2iwq(0x760)),
	DEFINE_WES_IWQ(evt2iwq(0x740)),
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
	DEFINE_WES_MEM(0xffc40000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x780)),
	DEFINE_WES_IWQ(evt2iwq(0x7a0)),
	DEFINE_WES_IWQ(evt2iwq(0x7e0)),
	DEFINE_WES_IWQ(evt2iwq(0x7c0)),
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
	DEFINE_WES_MEM(0xffc60000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x880)),
	DEFINE_WES_IWQ(evt2iwq(0x8a0)),
	DEFINE_WES_IWQ(evt2iwq(0x8e0)),
	DEFINE_WES_IWQ(evt2iwq(0x8c0)),
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

static stwuct sh_timew_config tmu0_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu0_wesouwces[] = {
	DEFINE_WES_MEM(0xffc10000, 0x30),
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
	DEFINE_WES_MEM(0xffc20000, 0x2c),
	DEFINE_WES_IWQ(evt2iwq(0x460)),
	DEFINE_WES_IWQ(evt2iwq(0x480)),
	DEFINE_WES_IWQ(evt2iwq(0x4a0)),
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

static stwuct pwatfowm_device *shx3_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&tmu0_device,
	&tmu1_device,
};

static int __init shx3_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(shx3_eawwy_devices,
				   AWWAY_SIZE(shx3_eawwy_devices));
}
awch_initcaww(shx3_devices_setup);

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(shx3_eawwy_devices,
				   AWWAY_SIZE(shx3_eawwy_devices));
}

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWW_WWWW, IWW_WWWH, IWW_WWHW, IWW_WWHH,
	IWW_WHWW, IWW_WHWH, IWW_WHHW, IWW_WHHH,
	IWW_HWWW, IWW_HWWH, IWW_HWHW, IWW_HWHH,
	IWW_HHWW, IWW_HHWH, IWW_HHHW,
	IWQ0, IWQ1, IWQ2, IWQ3,
	HUDII,
	TMU0, TMU1, TMU2, TMU3, TMU4, TMU5,
	PCII0, PCII1, PCII2, PCII3, PCII4,
	PCII5, PCII6, PCII7, PCII8, PCII9,
	SCIF0_EWI, SCIF0_WXI, SCIF0_BWI, SCIF0_TXI,
	SCIF1_EWI, SCIF1_WXI, SCIF1_BWI, SCIF1_TXI,
	SCIF2_EWI, SCIF2_WXI, SCIF2_BWI, SCIF2_TXI,
	SCIF3_EWI, SCIF3_WXI, SCIF3_BWI, SCIF3_TXI,
	DMAC0_DMINT0, DMAC0_DMINT1, DMAC0_DMINT2, DMAC0_DMINT3,
	DMAC0_DMINT4, DMAC0_DMINT5, DMAC0_DMAE,
	DU,
	DMAC1_DMINT6, DMAC1_DMINT7, DMAC1_DMINT8, DMAC1_DMINT9,
	DMAC1_DMINT10, DMAC1_DMINT11, DMAC1_DMAE,
	IIC, VIN0, VIN1, VCOWE0, ATAPI,
	DTU0, DTU1, DTU2, DTU3,
	FE0, FE1,
	GPIO0, GPIO1, GPIO2, GPIO3,
	PAM, IWM,
	INTICI0, INTICI1, INTICI2, INTICI3,
	INTICI4, INTICI5, INTICI6, INTICI7,

	/* intewwupt gwoups */
	IWW, PCII56789, SCIF0, SCIF1, SCIF2, SCIF3,
	DMAC0, DMAC1,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(HUDII, 0x3e0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU3, 0x460),
	INTC_VECT(TMU4, 0x480), INTC_VECT(TMU5, 0x4a0),
	INTC_VECT(PCII0, 0x500), INTC_VECT(PCII1, 0x520),
	INTC_VECT(PCII2, 0x540), INTC_VECT(PCII3, 0x560),
	INTC_VECT(PCII4, 0x580), INTC_VECT(PCII5, 0x5a0),
	INTC_VECT(PCII6, 0x5c0), INTC_VECT(PCII7, 0x5e0),
	INTC_VECT(PCII8, 0x600), INTC_VECT(PCII9, 0x620),
	INTC_VECT(SCIF0_EWI, 0x700), INTC_VECT(SCIF0_WXI, 0x720),
	INTC_VECT(SCIF0_BWI, 0x740), INTC_VECT(SCIF0_TXI, 0x760),
	INTC_VECT(SCIF1_EWI, 0x780), INTC_VECT(SCIF1_WXI, 0x7a0),
	INTC_VECT(SCIF1_BWI, 0x7c0), INTC_VECT(SCIF1_TXI, 0x7e0),
	INTC_VECT(SCIF3_EWI, 0x880), INTC_VECT(SCIF3_WXI, 0x8a0),
	INTC_VECT(SCIF3_BWI, 0x8c0), INTC_VECT(SCIF3_TXI, 0x8e0),
	INTC_VECT(DMAC0_DMINT0, 0x900), INTC_VECT(DMAC0_DMINT1, 0x920),
	INTC_VECT(DMAC0_DMINT2, 0x940), INTC_VECT(DMAC0_DMINT3, 0x960),
	INTC_VECT(DMAC0_DMINT4, 0x980), INTC_VECT(DMAC0_DMINT5, 0x9a0),
	INTC_VECT(DMAC0_DMAE, 0x9c0),
	INTC_VECT(DU, 0x9e0),
	INTC_VECT(DMAC1_DMINT6, 0xa00), INTC_VECT(DMAC1_DMINT7, 0xa20),
	INTC_VECT(DMAC1_DMINT8, 0xa40), INTC_VECT(DMAC1_DMINT9, 0xa60),
	INTC_VECT(DMAC1_DMINT10, 0xa80), INTC_VECT(DMAC1_DMINT11, 0xaa0),
	INTC_VECT(DMAC1_DMAE, 0xac0),
	INTC_VECT(IIC, 0xae0),
	INTC_VECT(VIN0, 0xb00), INTC_VECT(VIN1, 0xb20),
	INTC_VECT(VCOWE0, 0xb00), INTC_VECT(ATAPI, 0xb60),
	INTC_VECT(DTU0, 0xc00), INTC_VECT(DTU0, 0xc20),
	INTC_VECT(DTU0, 0xc40),
	INTC_VECT(DTU1, 0xc60), INTC_VECT(DTU1, 0xc80),
	INTC_VECT(DTU1, 0xca0),
	INTC_VECT(DTU2, 0xcc0), INTC_VECT(DTU2, 0xce0),
	INTC_VECT(DTU2, 0xd00),
	INTC_VECT(DTU3, 0xd20), INTC_VECT(DTU3, 0xd40),
	INTC_VECT(DTU3, 0xd60),
	INTC_VECT(FE0, 0xe00), INTC_VECT(FE1, 0xe20),
	INTC_VECT(GPIO0, 0xe40), INTC_VECT(GPIO1, 0xe60),
	INTC_VECT(GPIO2, 0xe80), INTC_VECT(GPIO3, 0xea0),
	INTC_VECT(PAM, 0xec0), INTC_VECT(IWM, 0xee0),
	INTC_VECT(INTICI0, 0xf00), INTC_VECT(INTICI1, 0xf20),
	INTC_VECT(INTICI2, 0xf40), INTC_VECT(INTICI3, 0xf60),
	INTC_VECT(INTICI4, 0xf80), INTC_VECT(INTICI5, 0xfa0),
	INTC_VECT(INTICI6, 0xfc0), INTC_VECT(INTICI7, 0xfe0),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(IWW, IWW_WWWW, IWW_WWWH, IWW_WWHW, IWW_WWHH,
		   IWW_WHWW, IWW_WHWH, IWW_WHHW, IWW_WHHH,
		   IWW_HWWW, IWW_HWWH, IWW_HWHW, IWW_HWHH,
		   IWW_HHWW, IWW_HHWH, IWW_HHHW),
	INTC_GWOUP(PCII56789, PCII5, PCII6, PCII7, PCII8, PCII9),
	INTC_GWOUP(SCIF0, SCIF0_EWI, SCIF0_WXI, SCIF0_BWI, SCIF0_TXI),
	INTC_GWOUP(SCIF1, SCIF1_EWI, SCIF1_WXI, SCIF1_BWI, SCIF1_TXI),
	INTC_GWOUP(SCIF3, SCIF3_EWI, SCIF3_WXI, SCIF3_BWI, SCIF3_TXI),
	INTC_GWOUP(DMAC0, DMAC0_DMINT0, DMAC0_DMINT1, DMAC0_DMINT2,
		   DMAC0_DMINT3, DMAC0_DMINT4, DMAC0_DMINT5, DMAC0_DMAE),
	INTC_GWOUP(DMAC1, DMAC1_DMINT6, DMAC1_DMINT7, DMAC1_DMINT8,
		   DMAC1_DMINT9, DMAC1_DMINT10, DMAC1_DMINT11),
};

#define INT2DISTCW0	0xfe4108a0
#define INT2DISTCW1	0xfe4108a4
#define INT2DISTCW2	0xfe4108a8

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xfe410030, 0xfe410050, 32, /* CnINTMSK0 / CnINTMSKCWW0 */
	  { IWQ0, IWQ1, IWQ2, IWQ3 } },
	{ 0xfe410040, 0xfe410060, 32, /* CnINTMSK1 / CnINTMSKCWW1 */
	  { IWW } },
	{ 0xfe410820, 0xfe410850, 32, /* CnINT2MSK0 / CnINT2MSKCWW0 */
	  { FE1, FE0, 0, ATAPI, VCOWE0, VIN1, VIN0, IIC,
	    DU, GPIO3, GPIO2, GPIO1, GPIO0, PAM, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0, /* HUDI bits ignowed */
	    0, TMU5, TMU4, TMU3, TMU2, TMU1, TMU0, 0, },
	    INTC_SMP_BAWANCING(INT2DISTCW0) },
	{ 0xfe410830, 0xfe410860, 32, /* CnINT2MSK1 / CnINT2MSKCWW1 */
	  { 0, 0, 0, 0, DTU3, DTU2, DTU1, DTU0, /* IWM bits ignowed */
	    PCII9, PCII8, PCII7, PCII6, PCII5, PCII4, PCII3, PCII2,
	    PCII1, PCII0, DMAC1_DMAE, DMAC1_DMINT11,
	    DMAC1_DMINT10, DMAC1_DMINT9, DMAC1_DMINT8, DMAC1_DMINT7,
	    DMAC1_DMINT6, DMAC0_DMAE, DMAC0_DMINT5, DMAC0_DMINT4,
	    DMAC0_DMINT3, DMAC0_DMINT2, DMAC0_DMINT1, DMAC0_DMINT0 },
	    INTC_SMP_BAWANCING(INT2DISTCW1) },
	{ 0xfe410840, 0xfe410870, 32, /* CnINT2MSK2 / CnINT2MSKCWW2 */
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    SCIF3_TXI, SCIF3_BWI, SCIF3_WXI, SCIF3_EWI,
	    SCIF2_TXI, SCIF2_BWI, SCIF2_WXI, SCIF2_EWI,
	    SCIF1_TXI, SCIF1_BWI, SCIF1_WXI, SCIF1_EWI,
	    SCIF0_TXI, SCIF0_BWI, SCIF0_WXI, SCIF0_EWI },
	    INTC_SMP_BAWANCING(INT2DISTCW2) },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xfe410010, 0, 32, 4, /* INTPWI */ { IWQ0, IWQ1, IWQ2, IWQ3 } },

	{ 0xfe410800, 0, 32, 4, /* INT2PWI0 */ { 0, HUDII, TMU5, TMU4,
						 TMU3, TMU2, TMU1, TMU0 } },
	{ 0xfe410804, 0, 32, 4, /* INT2PWI1 */ { DTU3, DTU2, DTU1, DTU0,
						 SCIF3, SCIF2,
						 SCIF1, SCIF0 } },
	{ 0xfe410808, 0, 32, 4, /* INT2PWI2 */ { DMAC1, DMAC0,
						 PCII56789, PCII4,
						 PCII3, PCII2,
						 PCII1, PCII0 } },
	{ 0xfe41080c, 0, 32, 4, /* INT2PWI3 */ { FE1, FE0, ATAPI, VCOWE0,
						 VIN1, VIN0, IIC, DU} },
	{ 0xfe410810, 0, 32, 4, /* INT2PWI4 */ { 0, 0, PAM, GPIO3,
						 GPIO2, GPIO1, GPIO0, IWM } },
	{ 0xfe410090, 0xfe4100a0, 32, 4, /* CnICIPWI / CnICIPWICWW */
	  { INTICI7, INTICI6, INTICI5, INTICI4,
	    INTICI3, INTICI2, INTICI1, INTICI0 }, INTC_SMP(4, 4) },
};

static DECWAWE_INTC_DESC(intc_desc, "shx3", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

/* Suppowt fow extewnaw intewwupt pins in IWQ mode */
static stwuct intc_vect vectows_iwq[] __initdata = {
	INTC_VECT(IWQ0, 0x240), INTC_VECT(IWQ1, 0x280),
	INTC_VECT(IWQ2, 0x2c0), INTC_VECT(IWQ3, 0x300),
};

static stwuct intc_sense_weg sense_wegistews[] __initdata = {
	{ 0xfe41001c, 32, 2, /* ICW1 */   { IWQ0, IWQ1, IWQ2, IWQ3 } },
};

static DECWAWE_INTC_DESC(intc_desc_iwq, "shx3-iwq", vectows_iwq, gwoups,
			 mask_wegistews, pwio_wegistews, sense_wegistews);

/* Extewnaw intewwupt pins in IWW mode */
static stwuct intc_vect vectows_iww[] __initdata = {
	INTC_VECT(IWW_WWWW, 0x200), INTC_VECT(IWW_WWWH, 0x220),
	INTC_VECT(IWW_WWHW, 0x240), INTC_VECT(IWW_WWHH, 0x260),
	INTC_VECT(IWW_WHWW, 0x280), INTC_VECT(IWW_WHWH, 0x2a0),
	INTC_VECT(IWW_WHHW, 0x2c0), INTC_VECT(IWW_WHHH, 0x2e0),
	INTC_VECT(IWW_HWWW, 0x300), INTC_VECT(IWW_HWWH, 0x320),
	INTC_VECT(IWW_HWHW, 0x340), INTC_VECT(IWW_HWHH, 0x360),
	INTC_VECT(IWW_HHWW, 0x380), INTC_VECT(IWW_HHWH, 0x3a0),
	INTC_VECT(IWW_HHHW, 0x3c0),
};

static DECWAWE_INTC_DESC(intc_desc_iww, "shx3-iww", vectows_iww, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

void __init pwat_iwq_setup_pins(int mode)
{
	int wet = 0;

	switch (mode) {
	case IWQ_MODE_IWQ:
		wet |= gpio_wequest(GPIO_FN_IWQ3, intc_desc_iwq.name);
		wet |= gpio_wequest(GPIO_FN_IWQ2, intc_desc_iwq.name);
		wet |= gpio_wequest(GPIO_FN_IWQ1, intc_desc_iwq.name);
		wet |= gpio_wequest(GPIO_FN_IWQ0, intc_desc_iwq.name);

		if (unwikewy(wet)) {
			pw_eww("Faiwed to set IWQ mode\n");
			wetuwn;
		}

		wegistew_intc_contwowwew(&intc_desc_iwq);
		bweak;
	case IWQ_MODE_IWW3210:
		wet |= gpio_wequest(GPIO_FN_IWW3, intc_desc_iww.name);
		wet |= gpio_wequest(GPIO_FN_IWW2, intc_desc_iww.name);
		wet |= gpio_wequest(GPIO_FN_IWW1, intc_desc_iww.name);
		wet |= gpio_wequest(GPIO_FN_IWW0, intc_desc_iww.name);

		if (unwikewy(wet)) {
			pw_eww("Faiwed to set IWW mode\n");
			wetuwn;
		}

		wegistew_intc_contwowwew(&intc_desc_iww);
		bweak;
	defauwt:
		BUG();
	}
}

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}

void __init pwat_mem_setup(void)
{
	unsigned int nid = 1;

	/* Wegistew CPU#0 UWAM space as Node 1 */
	setup_bootmem_node(nid++, 0x145f0000, 0x14610000);	/* CPU0 */

#if 0
	/* XXX: Not yet.. */
	setup_bootmem_node(nid++, 0x14df0000, 0x14e10000);	/* CPU1 */
	setup_bootmem_node(nid++, 0x155f0000, 0x15610000);	/* CPU2 */
	setup_bootmem_node(nid++, 0x15df0000, 0x15e10000);	/* CPU3 */
#endif

	setup_bootmem_node(nid++, 0x16000000, 0x16020000);	/* CSM */
}
