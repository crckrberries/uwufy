// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7763 Setup
 *
 *  Copywight (C) 2006  Pauw Mundt
 *  Copywight (C) 2007  Yoshihiwo Shimoda
 *  Copywight (C) 2008, 2009  Nobuhiwo Iwamatsu
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <winux/io.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/usb/ohci_pdwivew.h>
#incwude <asm/pwatfowm_eawwy.h>

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xffe00000, 0x100),
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
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
	.wegtype	= SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xffe08000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xb80)),
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
	DEFINE_WES_MEM(0xffe10000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xf00)),
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

static stwuct wesouwce wtc_wesouwces[] = {
	[0] = {
		.stawt	= 0xffe80000,
		.end	= 0xffe80000 + 0x58 - 1,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		/* Shawed Pewiod/Cawwy/Awawm IWQ */
		.stawt  = evt2iwq(0x480),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
};

static stwuct wesouwce usb_ohci_wesouwces[] = {
	[0] = {
		.stawt	= 0xffec8000,
		.end	= 0xffec80ff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xc60),
		.end	= evt2iwq(0xc60),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static u64 usb_ohci_dma_mask = 0xffffffffUW;

static stwuct usb_ohci_pdata usb_ohci_pdata;

static stwuct pwatfowm_device usb_ohci_device = {
	.name		= "ohci-pwatfowm",
	.id		= -1,
	.dev = {
		.dma_mask		= &usb_ohci_dma_mask,
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &usb_ohci_pdata,
	},
	.num_wesouwces	= AWWAY_SIZE(usb_ohci_wesouwces),
	.wesouwce	= usb_ohci_wesouwces,
};

static stwuct wesouwce usbf_wesouwces[] = {
	[0] = {
		.stawt	= 0xffec0000,
		.end	= 0xffec00ff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xc80),
		.end	= evt2iwq(0xc80),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device usbf_device = {
	.name		= "sh_udc",
	.id		= -1,
	.dev = {
		.dma_mask		= NUWW,
		.cohewent_dma_mask	= 0xffffffff,
	},
	.num_wesouwces	= AWWAY_SIZE(usbf_wesouwces),
	.wesouwce	= usbf_wesouwces,
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
	DEFINE_WES_MEM(0xffd88000, 0x2c),
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

static stwuct pwatfowm_device *sh7763_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&tmu0_device,
	&tmu1_device,
	&wtc_device,
	&usb_ohci_device,
	&usbf_device,
};

static int __init sh7763_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh7763_devices,
				    AWWAY_SIZE(sh7763_devices));
}
awch_initcaww(sh7763_devices_setup);

static stwuct pwatfowm_device *sh7763_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&tmu0_device,
	&tmu1_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7763_eawwy_devices,
				   AWWAY_SIZE(sh7763_eawwy_devices));
}

enum {
	UNUSED = 0,

	/* intewwupt souwces */

	IWW_WWWW, IWW_WWWH, IWW_WWHW, IWW_WWHH,
	IWW_WHWW, IWW_WHWH, IWW_WHHW, IWW_WHHH,
	IWW_HWWW, IWW_HWWH, IWW_HWHW, IWW_HWHH,
	IWW_HHWW, IWW_HHWH, IWW_HHHW,

	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7,
	WTC, WDT, TMU0, TMU1, TMU2, TMU2_TICPI,
	HUDI, WCDC, DMAC, SCIF0, IIC0, IIC1, CMT, GETHEW, HAC,
	PCISEWW, PCIINTA, PCIINTB, PCIINTC, PCIINTD, PCIC5,
	STIF0, STIF1, SCIF1, SIOF0, SIOF1, SIOF2,
	USBH, USBF, TPU, PCC, MMCIF, SIM,
	TMU3, TMU4, TMU5, ADC, SSI0, SSI1, SSI2, SSI3,
	SCIF2, GPIO,

	/* intewwupt gwoups */

	TMU012, TMU345,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(WTC, 0x480), INTC_VECT(WTC, 0x4a0),
	INTC_VECT(WTC, 0x4c0),
	INTC_VECT(WDT, 0x560), INTC_VECT(TMU0, 0x580),
	INTC_VECT(TMU1, 0x5a0), INTC_VECT(TMU2, 0x5c0),
	INTC_VECT(TMU2_TICPI, 0x5e0), INTC_VECT(HUDI, 0x600),
	INTC_VECT(WCDC, 0x620),
	INTC_VECT(DMAC, 0x640), INTC_VECT(DMAC, 0x660),
	INTC_VECT(DMAC, 0x680), INTC_VECT(DMAC, 0x6a0),
	INTC_VECT(DMAC, 0x6c0),
	INTC_VECT(SCIF0, 0x700), INTC_VECT(SCIF0, 0x720),
	INTC_VECT(SCIF0, 0x740), INTC_VECT(SCIF0, 0x760),
	INTC_VECT(DMAC, 0x780), INTC_VECT(DMAC, 0x7a0),
	INTC_VECT(IIC0, 0x8A0), INTC_VECT(IIC1, 0x8C0),
	INTC_VECT(CMT, 0x900), INTC_VECT(GETHEW, 0x920),
	INTC_VECT(GETHEW, 0x940), INTC_VECT(GETHEW, 0x960),
	INTC_VECT(HAC, 0x980),
	INTC_VECT(PCISEWW, 0xa00), INTC_VECT(PCIINTA, 0xa20),
	INTC_VECT(PCIINTB, 0xa40), INTC_VECT(PCIINTC, 0xa60),
	INTC_VECT(PCIINTD, 0xa80), INTC_VECT(PCIC5, 0xaa0),
	INTC_VECT(PCIC5, 0xac0), INTC_VECT(PCIC5, 0xae0),
	INTC_VECT(PCIC5, 0xb00), INTC_VECT(PCIC5, 0xb20),
	INTC_VECT(STIF0, 0xb40), INTC_VECT(STIF1, 0xb60),
	INTC_VECT(SCIF1, 0xb80), INTC_VECT(SCIF1, 0xba0),
	INTC_VECT(SCIF1, 0xbc0), INTC_VECT(SCIF1, 0xbe0),
	INTC_VECT(SIOF0, 0xc00), INTC_VECT(SIOF1, 0xc20),
	INTC_VECT(USBH, 0xc60), INTC_VECT(USBF, 0xc80),
	INTC_VECT(USBF, 0xca0),
	INTC_VECT(TPU, 0xcc0), INTC_VECT(PCC, 0xce0),
	INTC_VECT(MMCIF, 0xd00), INTC_VECT(MMCIF, 0xd20),
	INTC_VECT(MMCIF, 0xd40), INTC_VECT(MMCIF, 0xd60),
	INTC_VECT(SIM, 0xd80), INTC_VECT(SIM, 0xda0),
	INTC_VECT(SIM, 0xdc0), INTC_VECT(SIM, 0xde0),
	INTC_VECT(TMU3, 0xe00), INTC_VECT(TMU4, 0xe20),
	INTC_VECT(TMU5, 0xe40), INTC_VECT(ADC, 0xe60),
	INTC_VECT(SSI0, 0xe80), INTC_VECT(SSI1, 0xea0),
	INTC_VECT(SSI2, 0xec0), INTC_VECT(SSI3, 0xee0),
	INTC_VECT(SCIF2, 0xf00), INTC_VECT(SCIF2, 0xf20),
	INTC_VECT(SCIF2, 0xf40), INTC_VECT(SCIF2, 0xf60),
	INTC_VECT(GPIO, 0xf80), INTC_VECT(GPIO, 0xfa0),
	INTC_VECT(GPIO, 0xfc0), INTC_VECT(GPIO, 0xfe0),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(TMU012, TMU0, TMU1, TMU2, TMU2_TICPI),
	INTC_GWOUP(TMU345, TMU3, TMU4, TMU5),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xffd40038, 0xffd4003c, 32, /* INT2MSKW / INT2MSKCW */
	  { 0, 0, 0, 0, 0, 0, GPIO, 0,
	    SSI0, MMCIF, 0, SIOF0, PCIC5, PCIINTD, PCIINTC, PCIINTB,
	    PCIINTA, PCISEWW, HAC, CMT, 0, 0, 0, DMAC,
	    HUDI, 0, WDT, SCIF1, SCIF0, WTC, TMU345, TMU012 } },
	{ 0xffd400d0, 0xffd400d4, 32, /* INT2MSKW1 / INT2MSKCW1 */
	  { 0, 0, 0, 0, 0, 0, SCIF2, USBF,
	    0, 0, STIF1, STIF0, 0, 0, USBH, GETHEW,
	    PCC, 0, 0, ADC, TPU, SIM, SIOF2, SIOF1,
	    WCDC, 0, IIC1, IIC0, SSI3, SSI2, SSI1, 0 } },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xffd40000, 0, 32, 8, /* INT2PWI0 */ { TMU0, TMU1,
						 TMU2, TMU2_TICPI } },
	{ 0xffd40004, 0, 32, 8, /* INT2PWI1 */ { TMU3, TMU4, TMU5, WTC } },
	{ 0xffd40008, 0, 32, 8, /* INT2PWI2 */ { SCIF0, SCIF1, WDT } },
	{ 0xffd4000c, 0, 32, 8, /* INT2PWI3 */ { HUDI, DMAC, ADC } },
	{ 0xffd40010, 0, 32, 8, /* INT2PWI4 */ { CMT, HAC,
						 PCISEWW, PCIINTA } },
	{ 0xffd40014, 0, 32, 8, /* INT2PWI5 */ { PCIINTB, PCIINTC,
						 PCIINTD, PCIC5 } },
	{ 0xffd40018, 0, 32, 8, /* INT2PWI6 */ { SIOF0, USBF, MMCIF, SSI0 } },
	{ 0xffd4001c, 0, 32, 8, /* INT2PWI7 */ { SCIF2, GPIO } },
	{ 0xffd400a0, 0, 32, 8, /* INT2PWI8 */ { SSI3, SSI2, SSI1, 0 } },
	{ 0xffd400a4, 0, 32, 8, /* INT2PWI9 */ { WCDC, 0, IIC1, IIC0 } },
	{ 0xffd400a8, 0, 32, 8, /* INT2PWI10 */ { TPU, SIM, SIOF2, SIOF1 } },
	{ 0xffd400ac, 0, 32, 8, /* INT2PWI11 */ { PCC } },
	{ 0xffd400b0, 0, 32, 8, /* INT2PWI12 */ { 0, 0, USBH, GETHEW } },
	{ 0xffd400b4, 0, 32, 8, /* INT2PWI13 */ { 0, 0, STIF1, STIF0 } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7763", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

/* Suppowt fow extewnaw intewwupt pins in IWQ mode */
static stwuct intc_vect iwq_vectows[] __initdata = {
	INTC_VECT(IWQ0, 0x240), INTC_VECT(IWQ1, 0x280),
	INTC_VECT(IWQ2, 0x2c0), INTC_VECT(IWQ3, 0x300),
	INTC_VECT(IWQ4, 0x340), INTC_VECT(IWQ5, 0x380),
	INTC_VECT(IWQ6, 0x3c0), INTC_VECT(IWQ7, 0x200),
};

static stwuct intc_mask_weg iwq_mask_wegistews[] __initdata = {
	{ 0xffd00044, 0xffd00064, 32, /* INTMSK0 / INTMSKCWW0 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_pwio_weg iwq_pwio_wegistews[] __initdata = {
	{ 0xffd00010, 0, 32, 4, /* INTPWI */ { IWQ0, IWQ1, IWQ2, IWQ3,
					       IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_sense_weg iwq_sense_wegistews[] __initdata = {
	{ 0xffd0001c, 32, 2, /* ICW1 */   { IWQ0, IWQ1, IWQ2, IWQ3,
					    IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_mask_weg iwq_ack_wegistews[] __initdata = {
	{ 0xffd00024, 0, 32, /* INTWEQ */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static DECWAWE_INTC_DESC_ACK(intc_iwq_desc, "sh7763-iwq", iwq_vectows,
			     NUWW, iwq_mask_wegistews, iwq_pwio_wegistews,
			     iwq_sense_wegistews, iwq_ack_wegistews);


/* Extewnaw intewwupt pins in IWW mode */
static stwuct intc_vect iww_vectows[] __initdata = {
	INTC_VECT(IWW_WWWW, 0x200), INTC_VECT(IWW_WWWH, 0x220),
	INTC_VECT(IWW_WWHW, 0x240), INTC_VECT(IWW_WWHH, 0x260),
	INTC_VECT(IWW_WHWW, 0x280), INTC_VECT(IWW_WHWH, 0x2a0),
	INTC_VECT(IWW_WHHW, 0x2c0), INTC_VECT(IWW_WHHH, 0x2e0),
	INTC_VECT(IWW_HWWW, 0x300), INTC_VECT(IWW_HWWH, 0x320),
	INTC_VECT(IWW_HWHW, 0x340), INTC_VECT(IWW_HWHH, 0x360),
	INTC_VECT(IWW_HHWW, 0x380), INTC_VECT(IWW_HHWH, 0x3a0),
	INTC_VECT(IWW_HHHW, 0x3c0),
};

static stwuct intc_mask_weg iww3210_mask_wegistews[] __initdata = {
	{ 0xffd40080, 0xffd40084, 32, /* INTMSK2 / INTMSKCWW2 */
	  { IWW_WWWW, IWW_WWWH, IWW_WWHW, IWW_WWHH,
	    IWW_WHWW, IWW_WHWH, IWW_WHHW, IWW_WHHH,
	    IWW_HWWW, IWW_HWWH, IWW_HWHW, IWW_HWHH,
	    IWW_HHWW, IWW_HHWH, IWW_HHHW, } },
};

static stwuct intc_mask_weg iww7654_mask_wegistews[] __initdata = {
	{ 0xffd40080, 0xffd40084, 32, /* INTMSK2 / INTMSKCWW2 */
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    IWW_WWWW, IWW_WWWH, IWW_WWHW, IWW_WWHH,
	    IWW_WHWW, IWW_WHWH, IWW_WHHW, IWW_WHHH,
	    IWW_HWWW, IWW_HWWH, IWW_HWHW, IWW_HWHH,
	    IWW_HHWW, IWW_HHWH, IWW_HHHW, } },
};

static DECWAWE_INTC_DESC(intc_iww7654_desc, "sh7763-iww7654", iww_vectows,
			NUWW, iww7654_mask_wegistews, NUWW, NUWW);

static DECWAWE_INTC_DESC(intc_iww3210_desc, "sh7763-iww3210", iww_vectows,
			NUWW, iww3210_mask_wegistews, NUWW, NUWW);

#define INTC_ICW0	0xffd00000
#define INTC_INTMSK0	0xffd00044
#define INTC_INTMSK1	0xffd00048
#define INTC_INTMSK2	0xffd40080
#define INTC_INTMSKCWW1	0xffd00068
#define INTC_INTMSKCWW2	0xffd40084

void __init pwat_iwq_setup(void)
{
	/* disabwe IWQ7-0 */
	__waw_wwitew(0xff000000, INTC_INTMSK0);

	/* disabwe IWW3-0 + IWW7-4 */
	__waw_wwitew(0xc0000000, INTC_INTMSK1);
	__waw_wwitew(0xfffefffe, INTC_INTMSK2);

	wegistew_intc_contwowwew(&intc_desc);
}

void __init pwat_iwq_setup_pins(int mode)
{
	switch (mode) {
	case IWQ_MODE_IWQ:
		/* sewect IWQ mode fow IWW3-0 + IWW7-4 */
		__waw_wwitew(__waw_weadw(INTC_ICW0) | 0x00c00000, INTC_ICW0);
		wegistew_intc_contwowwew(&intc_iwq_desc);
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
		wegistew_intc_contwowwew(&intc_iww7654_desc);
		bweak;
	case IWQ_MODE_IWW3210_MASK:
		/* enabwe IWW0-3 and mask using cpu intc contwowwew */
		__waw_wwitew(0x80000000, INTC_INTMSKCWW1);
		wegistew_intc_contwowwew(&intc_iww3210_desc);
		bweak;
	defauwt:
		BUG();
	}
}
