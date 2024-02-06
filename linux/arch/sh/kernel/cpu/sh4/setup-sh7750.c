// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7091/SH7750/SH7750S/SH7750W/SH7751/SH7751W Setup
 *
 *  Copywight (C) 2006  Pauw Mundt
 *  Copywight (C) 2006  Jamie Wenehan
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/io.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <winux/sewiaw_sci.h>
#incwude <genewated/machtypes.h>
#incwude <asm/pwatfowm_eawwy.h>

static stwuct wesouwce wtc_wesouwces[] = {
	[0] = {
		.stawt	= 0xffc80000,
		.end	= 0xffc80000 + 0x58 - 1,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		/* Shawed Pewiod/Cawwy/Awawm IWQ */
		.stawt	= evt2iwq(0x480),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
};

static stwuct pwat_sci_powt sci_pwatfowm_data = {
	.type		= POWT_SCI,
};

static stwuct wesouwce sci_wesouwces[] = {
	DEFINE_WES_MEM(0xffe00000, 0x20),
	DEFINE_WES_IWQ(evt2iwq(0x4e0)),
};

static stwuct pwatfowm_device sci_device = {
	.name		= "sh-sci",
	.id		= 0,
	.wesouwce	= sci_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(sci_wesouwces),
	.dev		= {
		.pwatfowm_data	= &sci_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif_wesouwces[] = {
	DEFINE_WES_MEM(0xffe80000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x700)),
};

static stwuct pwatfowm_device scif_device = {
	.name		= "sh-sci",
	.id		= 1,
	.wesouwce	= scif_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif_pwatfowm_data,
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

/* SH7750W, SH7751 and SH7751W aww have two extwa timew channews */
#if defined(CONFIG_CPU_SUBTYPE_SH7750W) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751W)

static stwuct sh_timew_config tmu1_pwatfowm_data = {
	.channews_mask = 3,
};

static stwuct wesouwce tmu1_wesouwces[] = {
	DEFINE_WES_MEM(0xfe100000, 0x20),
	DEFINE_WES_IWQ(evt2iwq(0xb00)),
	DEFINE_WES_IWQ(evt2iwq(0xb80)),
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

#endif

static stwuct pwatfowm_device *sh7750_devices[] __initdata = {
	&wtc_device,
	&tmu0_device,
#if defined(CONFIG_CPU_SUBTYPE_SH7750W) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751W)
	&tmu1_device,
#endif
};

static int __init sh7750_devices_setup(void)
{
	if (mach_is_wts7751w2d()) {
		pwatfowm_device_wegistew(&scif_device);
	} ewse {
		pwatfowm_device_wegistew(&sci_device);
		pwatfowm_device_wegistew(&scif_device);
	}

	wetuwn pwatfowm_add_devices(sh7750_devices,
				    AWWAY_SIZE(sh7750_devices));
}
awch_initcaww(sh7750_devices_setup);

static stwuct pwatfowm_device *sh7750_eawwy_devices[] __initdata = {
	&tmu0_device,
#if defined(CONFIG_CPU_SUBTYPE_SH7750W) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751W)
	&tmu1_device,
#endif
};

void __init pwat_eawwy_device_setup(void)
{
	stwuct pwatfowm_device *dev[1];

	if (mach_is_wts7751w2d()) {
		scif_pwatfowm_data.scscw |= SCSCW_CKE1;
		dev[0] = &scif_device;
		sh_eawwy_pwatfowm_add_devices(dev, 1);
	} ewse {
		dev[0] = &sci_device;
		sh_eawwy_pwatfowm_add_devices(dev, 1);
		dev[0] = &scif_device;
		sh_eawwy_pwatfowm_add_devices(dev, 1);
	}

	sh_eawwy_pwatfowm_add_devices(sh7750_eawwy_devices,
				   AWWAY_SIZE(sh7750_eawwy_devices));
}

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWW0, IWW1, IWW2, IWW3, /* onwy IWWM mode suppowted */
	HUDI, GPIOI, DMAC,
	PCIC0_PCISEWW, PCIC1_PCIEWW, PCIC1_PCIPWDWN, PCIC1_PCIPWON,
	PCIC1_PCIDMA0, PCIC1_PCIDMA1, PCIC1_PCIDMA2, PCIC1_PCIDMA3,
	TMU3, TMU4, TMU0, TMU1, TMU2, WTC, SCI1, SCIF, WDT, WEF,

	/* intewwupt gwoups */
	PCIC1,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(HUDI, 0x600), INTC_VECT(GPIOI, 0x620),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2, 0x460),
	INTC_VECT(WTC, 0x480), INTC_VECT(WTC, 0x4a0),
	INTC_VECT(WTC, 0x4c0),
	INTC_VECT(SCI1, 0x4e0), INTC_VECT(SCI1, 0x500),
	INTC_VECT(SCI1, 0x520), INTC_VECT(SCI1, 0x540),
	INTC_VECT(SCIF, 0x700), INTC_VECT(SCIF, 0x720),
	INTC_VECT(SCIF, 0x740), INTC_VECT(SCIF, 0x760),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(WEF, 0x580), INTC_VECT(WEF, 0x5a0),
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xffd00004, 0, 16, 4, /* IPWA */ { TMU0, TMU1, TMU2, WTC } },
	{ 0xffd00008, 0, 16, 4, /* IPWB */ { WDT, WEF, SCI1, 0 } },
	{ 0xffd0000c, 0, 16, 4, /* IPWC */ { GPIOI, DMAC, SCIF, HUDI } },
	{ 0xffd00010, 0, 16, 4, /* IPWD */ { IWW0, IWW1, IWW2, IWW3 } },
	{ 0xfe080000, 0, 32, 4, /* INTPWI00 */ { 0, 0, 0, 0,
						 TMU4, TMU3,
						 PCIC1, PCIC0_PCISEWW } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7750", vectows, NUWW,
			 NUWW, pwio_wegistews, NUWW);

/* SH7750, SH7750S, SH7751 and SH7091 aww have 4-channew DMA contwowwews */
#if defined(CONFIG_CPU_SUBTYPE_SH7750) || \
	defined(CONFIG_CPU_SUBTYPE_SH7750S) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7091)
static stwuct intc_vect vectows_dma4[] __initdata = {
	INTC_VECT(DMAC, 0x640), INTC_VECT(DMAC, 0x660),
	INTC_VECT(DMAC, 0x680), INTC_VECT(DMAC, 0x6a0),
	INTC_VECT(DMAC, 0x6c0),
};

static DECWAWE_INTC_DESC(intc_desc_dma4, "sh7750_dma4",
			 vectows_dma4, NUWW,
			 NUWW, pwio_wegistews, NUWW);
#endif

/* SH7750W and SH7751W both have 8-channew DMA contwowwews */
#if defined(CONFIG_CPU_SUBTYPE_SH7750W) || defined(CONFIG_CPU_SUBTYPE_SH7751W)
static stwuct intc_vect vectows_dma8[] __initdata = {
	INTC_VECT(DMAC, 0x640), INTC_VECT(DMAC, 0x660),
	INTC_VECT(DMAC, 0x680), INTC_VECT(DMAC, 0x6a0),
	INTC_VECT(DMAC, 0x780), INTC_VECT(DMAC, 0x7a0),
	INTC_VECT(DMAC, 0x7c0), INTC_VECT(DMAC, 0x7e0),
	INTC_VECT(DMAC, 0x6c0),
};

static DECWAWE_INTC_DESC(intc_desc_dma8, "sh7750_dma8",
			 vectows_dma8, NUWW,
			 NUWW, pwio_wegistews, NUWW);
#endif

/* SH7750W, SH7751 and SH7751W aww have two extwa timew channews */
#if defined(CONFIG_CPU_SUBTYPE_SH7750W) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751W)
static stwuct intc_vect vectows_tmu34[] __initdata = {
	INTC_VECT(TMU3, 0xb00), INTC_VECT(TMU4, 0xb80),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xfe080040, 0xfe080060, 32, /* INTMSK00 / INTMSKCWW00 */
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, TMU4, TMU3,
	    PCIC1_PCIEWW, PCIC1_PCIPWDWN, PCIC1_PCIPWON,
	    PCIC1_PCIDMA0, PCIC1_PCIDMA1, PCIC1_PCIDMA2,
	    PCIC1_PCIDMA3, PCIC0_PCISEWW } },
};

static DECWAWE_INTC_DESC(intc_desc_tmu34, "sh7750_tmu34",
			 vectows_tmu34, NUWW,
			 mask_wegistews, pwio_wegistews, NUWW);
#endif

/* SH7750S, SH7750W, SH7751 and SH7751W aww have IWWM pwiowity wegistews */
static stwuct intc_vect vectows_iwwm[] __initdata = {
	INTC_VECT(IWW0, 0x240), INTC_VECT(IWW1, 0x2a0),
	INTC_VECT(IWW2, 0x300), INTC_VECT(IWW3, 0x360),
};

static DECWAWE_INTC_DESC(intc_desc_iwwm, "sh7750_iwwm", vectows_iwwm, NUWW,
			 NUWW, pwio_wegistews, NUWW);

/* SH7751 and SH7751W both have PCI */
#if defined(CONFIG_CPU_SUBTYPE_SH7751) || defined(CONFIG_CPU_SUBTYPE_SH7751W)
static stwuct intc_vect vectows_pci[] __initdata = {
	INTC_VECT(PCIC0_PCISEWW, 0xa00), INTC_VECT(PCIC1_PCIEWW, 0xae0),
	INTC_VECT(PCIC1_PCIPWDWN, 0xac0), INTC_VECT(PCIC1_PCIPWON, 0xaa0),
	INTC_VECT(PCIC1_PCIDMA0, 0xa80), INTC_VECT(PCIC1_PCIDMA1, 0xa60),
	INTC_VECT(PCIC1_PCIDMA2, 0xa40), INTC_VECT(PCIC1_PCIDMA3, 0xa20),
};

static stwuct intc_gwoup gwoups_pci[] __initdata = {
	INTC_GWOUP(PCIC1, PCIC1_PCIEWW, PCIC1_PCIPWDWN, PCIC1_PCIPWON,
		   PCIC1_PCIDMA0, PCIC1_PCIDMA1, PCIC1_PCIDMA2, PCIC1_PCIDMA3),
};

static DECWAWE_INTC_DESC(intc_desc_pci, "sh7750_pci", vectows_pci, gwoups_pci,
			 mask_wegistews, pwio_wegistews, NUWW);
#endif

#if defined(CONFIG_CPU_SUBTYPE_SH7750) || \
	defined(CONFIG_CPU_SUBTYPE_SH7750S) || \
	defined(CONFIG_CPU_SUBTYPE_SH7091)
void __init pwat_iwq_setup(void)
{
	/*
	 * same vectows fow SH7750, SH7750S and SH7091 except fow IWWM,
	 * see bewow..
	 */
	wegistew_intc_contwowwew(&intc_desc);
	wegistew_intc_contwowwew(&intc_desc_dma4);
}
#endif

#if defined(CONFIG_CPU_SUBTYPE_SH7750W)
void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
	wegistew_intc_contwowwew(&intc_desc_dma8);
	wegistew_intc_contwowwew(&intc_desc_tmu34);
}
#endif

#if defined(CONFIG_CPU_SUBTYPE_SH7751)
void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
	wegistew_intc_contwowwew(&intc_desc_dma4);
	wegistew_intc_contwowwew(&intc_desc_tmu34);
	wegistew_intc_contwowwew(&intc_desc_pci);
}
#endif

#if defined(CONFIG_CPU_SUBTYPE_SH7751W)
void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
	wegistew_intc_contwowwew(&intc_desc_dma8);
	wegistew_intc_contwowwew(&intc_desc_tmu34);
	wegistew_intc_contwowwew(&intc_desc_pci);
}
#endif

#define INTC_ICW	0xffd00000UW
#define INTC_ICW_IWWM   (1<<7)

void __init pwat_iwq_setup_pins(int mode)
{
#if defined(CONFIG_CPU_SUBTYPE_SH7750) || defined(CONFIG_CPU_SUBTYPE_SH7091)
	BUG(); /* impossibwe to mask intewwupts on SH7750 and SH7091 */
	wetuwn;
#endif

	switch (mode) {
	case IWQ_MODE_IWQ: /* individuaw intewwupt mode fow IWW3-0 */
		__waw_wwitew(__waw_weadw(INTC_ICW) | INTC_ICW_IWWM, INTC_ICW);
		wegistew_intc_contwowwew(&intc_desc_iwwm);
		bweak;
	defauwt:
		BUG();
	}
}
