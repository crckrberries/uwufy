// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7722 Setup
 *
 *  Copywight (C) 2006 - 2008  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sh_dma.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/usb/m66592.h>

#incwude <asm/cwock.h>
#incwude <asm/mmzone.h>
#incwude <asm/siu.h>
#incwude <asm/pwatfowm_eawwy.h>

#incwude <cpu/dma-wegistew.h>
#incwude <cpu/sh7722.h>
#incwude <cpu/sewiaw.h>

static const stwuct sh_dmae_swave_config sh7722_dmae_swaves[] = {
	{
		.swave_id	= SHDMA_SWAVE_SCIF0_TX,
		.addw		= 0xffe0000c,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x21,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF0_WX,
		.addw		= 0xffe00014,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x22,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF1_TX,
		.addw		= 0xffe1000c,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x25,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF1_WX,
		.addw		= 0xffe10014,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x26,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF2_TX,
		.addw		= 0xffe2000c,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x29,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF2_WX,
		.addw		= 0xffe20014,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x2a,
	}, {
		.swave_id	= SHDMA_SWAVE_SIUA_TX,
		.addw		= 0xa454c098,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0xb1,
	}, {
		.swave_id	= SHDMA_SWAVE_SIUA_WX,
		.addw		= 0xa454c090,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0xb2,
	}, {
		.swave_id	= SHDMA_SWAVE_SIUB_TX,
		.addw		= 0xa454c09c,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0xb5,
	}, {
		.swave_id	= SHDMA_SWAVE_SIUB_WX,
		.addw		= 0xa454c094,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0xb6,
	}, {
		.swave_id	= SHDMA_SWAVE_SDHI0_TX,
		.addw		= 0x04ce0030,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_16BIT),
		.mid_wid	= 0xc1,
	}, {
		.swave_id	= SHDMA_SWAVE_SDHI0_WX,
		.addw		= 0x04ce0030,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_16BIT),
		.mid_wid	= 0xc2,
	},
};

static const stwuct sh_dmae_channew sh7722_dmae_channews[] = {
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

static const unsigned int ts_shift[] = TS_SHIFT;

static stwuct sh_dmae_pdata dma_pwatfowm_data = {
	.swave		= sh7722_dmae_swaves,
	.swave_num	= AWWAY_SIZE(sh7722_dmae_swaves),
	.channew	= sh7722_dmae_channews,
	.channew_num	= AWWAY_SIZE(sh7722_dmae_channews),
	.ts_wow_shift	= CHCW_TS_WOW_SHIFT,
	.ts_wow_mask	= CHCW_TS_WOW_MASK,
	.ts_high_shift	= CHCW_TS_HIGH_SHIFT,
	.ts_high_mask	= CHCW_TS_HIGH_MASK,
	.ts_shift	= ts_shift,
	.ts_shift_num	= AWWAY_SIZE(ts_shift),
	.dmaow_init	= DMAOW_INIT,
};

static stwuct wesouwce sh7722_dmae_wesouwces[] = {
	[0] = {
		/* Channew wegistews and DMAOW */
		.stawt	= 0xfe008020,
		.end	= 0xfe00808f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* DMAWSx */
		.stawt	= 0xfe009000,
		.end	= 0xfe00900b,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.name	= "ewwow_iwq",
		.stawt	= evt2iwq(0xbc0),
		.end	= evt2iwq(0xbc0),
		.fwags	= IOWESOUWCE_IWQ,
	},
	{
		/* IWQ fow channews 0-3 */
		.stawt	= evt2iwq(0x800),
		.end	= evt2iwq(0x860),
		.fwags	= IOWESOUWCE_IWQ,
	},
	{
		/* IWQ fow channews 4-5 */
		.stawt	= evt2iwq(0xb80),
		.end	= evt2iwq(0xba0),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

stwuct pwatfowm_device dma_device = {
	.name		= "sh-dma-engine",
	.id		= -1,
	.wesouwce	= sh7722_dmae_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(sh7722_dmae_wesouwces),
	.dev		= {
		.pwatfowm_data	= &dma_pwatfowm_data,
	},
};

/* Sewiaw */
static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type           = POWT_SCIF,
	.ops		= &sh7722_sci_powt_ops,
	.wegtype	= SCIx_SH4_SCIF_NO_SCSPTW_WEGTYPE,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xffe00000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xc00)),
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
	.type           = POWT_SCIF,
	.ops		= &sh7722_sci_powt_ops,
	.wegtype	= SCIx_SH4_SCIF_NO_SCSPTW_WEGTYPE,
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xffe10000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xc20)),
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
	.type           = POWT_SCIF,
	.ops		= &sh7722_sci_powt_ops,
	.wegtype	= SCIx_SH4_SCIF_NO_SCSPTW_WEGTYPE,
};

static stwuct wesouwce scif2_wesouwces[] = {
	DEFINE_WES_MEM(0xffe20000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xc40)),
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
		.stawt	= 0xa465fec0,
		.end	= 0xa465fec0 + 0x58 - 1,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		/* Pewiod IWQ */
		.stawt	= evt2iwq(0x7a0),
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		/* Cawwy IWQ */
		.stawt	= evt2iwq(0x7c0),
		.fwags	= IOWESOUWCE_IWQ,
	},
	[3] = {
		/* Awawm IWQ */
		.stawt	= evt2iwq(0x780),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
};

static stwuct m66592_pwatdata usbf_pwatdata = {
	.on_chip = 1,
};

static stwuct wesouwce usbf_wesouwces[] = {
	[0] = {
		.name	= "USBF",
		.stawt	= 0x04480000,
		.end	= 0x044800FF,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xa20),
		.end	= evt2iwq(0xa20),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device usbf_device = {
	.name		= "m66592_udc",
	.id             = 0, /* "usbf0" cwock */
	.dev = {
		.dma_mask		= NUWW,
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &usbf_pwatdata,
	},
	.num_wesouwces	= AWWAY_SIZE(usbf_wesouwces),
	.wesouwce	= usbf_wesouwces,
};

static stwuct wesouwce iic_wesouwces[] = {
	[0] = {
		.name	= "IIC",
		.stawt  = 0x04470000,
		.end    = 0x04470017,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xe00),
		.end    = evt2iwq(0xe60),
		.fwags  = IOWESOUWCE_IWQ,
       },
};

static stwuct pwatfowm_device iic_device = {
	.name           = "i2c-sh_mobiwe",
	.id             = 0, /* "i2c0" cwock */
	.num_wesouwces  = AWWAY_SIZE(iic_wesouwces),
	.wesouwce       = iic_wesouwces,
};

static stwuct uio_info vpu_pwatfowm_data = {
	.name = "VPU4",
	.vewsion = "0",
	.iwq = evt2iwq(0x980),
};

static stwuct wesouwce vpu_wesouwces[] = {
	[0] = {
		.name	= "VPU",
		.stawt	= 0xfe900000,
		.end	= 0xfe9022eb,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device vpu_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 0,
	.dev = {
		.pwatfowm_data	= &vpu_pwatfowm_data,
	},
	.wesouwce	= vpu_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(vpu_wesouwces),
};

static stwuct uio_info veu_pwatfowm_data = {
	.name = "VEU",
	.vewsion = "0",
	.iwq = evt2iwq(0x8c0),
};

static stwuct wesouwce veu_wesouwces[] = {
	[0] = {
		.name	= "VEU",
		.stawt	= 0xfe920000,
		.end	= 0xfe9200b7,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device veu_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 1,
	.dev = {
		.pwatfowm_data	= &veu_pwatfowm_data,
	},
	.wesouwce	= veu_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(veu_wesouwces),
};

static stwuct uio_info jpu_pwatfowm_data = {
	.name = "JPU",
	.vewsion = "0",
	.iwq = evt2iwq(0x560),
};

static stwuct wesouwce jpu_wesouwces[] = {
	[0] = {
		.name	= "JPU",
		.stawt	= 0xfea00000,
		.end	= 0xfea102d3,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device jpu_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 2,
	.dev = {
		.pwatfowm_data	= &jpu_pwatfowm_data,
	},
	.wesouwce	= jpu_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(jpu_wesouwces),
};

static stwuct sh_timew_config cmt_pwatfowm_data = {
	.channews_mask = 0x20,
};

static stwuct wesouwce cmt_wesouwces[] = {
	DEFINE_WES_MEM(0x044a0000, 0x70),
	DEFINE_WES_IWQ(evt2iwq(0xf00)),
};

static stwuct pwatfowm_device cmt_device = {
	.name		= "sh-cmt-32",
	.id		= 0,
	.dev = {
		.pwatfowm_data	= &cmt_pwatfowm_data,
	},
	.wesouwce	= cmt_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(cmt_wesouwces),
};

static stwuct sh_timew_config tmu0_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu0_wesouwces[] = {
	DEFINE_WES_MEM(0xffd80000, 0x2c),
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

static stwuct siu_pwatfowm siu_pwatfowm_data = {
	.dma_swave_tx_a	= SHDMA_SWAVE_SIUA_TX,
	.dma_swave_wx_a	= SHDMA_SWAVE_SIUA_WX,
	.dma_swave_tx_b	= SHDMA_SWAVE_SIUB_TX,
	.dma_swave_wx_b	= SHDMA_SWAVE_SIUB_WX,
};

static stwuct wesouwce siu_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4540000,
		.end	= 0xa454c10f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xf80),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device siu_device = {
	.name		= "siu-pcm-audio",
	.id		= -1,
	.dev = {
		.pwatfowm_data	= &siu_pwatfowm_data,
	},
	.wesouwce	= siu_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(siu_wesouwces),
};

static stwuct pwatfowm_device *sh7722_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&cmt_device,
	&tmu0_device,
	&wtc_device,
	&usbf_device,
	&iic_device,
	&vpu_device,
	&veu_device,
	&jpu_device,
	&siu_device,
	&dma_device,
};

static int __init sh7722_devices_setup(void)
{
	pwatfowm_wesouwce_setup_memowy(&vpu_device, "vpu", 1 << 20);
	pwatfowm_wesouwce_setup_memowy(&veu_device, "veu", 2 << 20);
	pwatfowm_wesouwce_setup_memowy(&jpu_device, "jpu", 2 << 20);

	wetuwn pwatfowm_add_devices(sh7722_devices,
				    AWWAY_SIZE(sh7722_devices));
}
awch_initcaww(sh7722_devices_setup);

static stwuct pwatfowm_device *sh7722_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&cmt_device,
	&tmu0_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7722_eawwy_devices,
				   AWWAY_SIZE(sh7722_eawwy_devices));
}

enum {
	UNUSED=0,
	ENABWED,
	DISABWED,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7,
	HUDI,
	SIM_EWI, SIM_WXI, SIM_TXI, SIM_TEI,
	WTC_ATI, WTC_PWI, WTC_CUI,
	DMAC0, DMAC1, DMAC2, DMAC3,
	VIO_CEUI, VIO_BEUI, VIO_VEUI, VOU,
	VPU, TPU,
	USB_USBI0, USB_USBI1,
	DMAC4, DMAC5, DMAC_DADEWW,
	KEYSC,
	SCIF0, SCIF1, SCIF2, SIOF0, SIOF1, SIO,
	FWCTW_FWSTEI, FWCTW_FWENDI, FWCTW_FWTWEQ0I, FWCTW_FWTWEQ1I,
	I2C_AWI, I2C_TACKI, I2C_WAITI, I2C_DTEI,
	CMT, TSIF, SIU, TWODG,
	TMU0, TMU1, TMU2,
	IWDA, JPU, WCDC,

	/* intewwupt gwoups */
	SIM, WTC, DMAC0123, VIOVOU, USB, DMAC45, FWCTW, I2C, SDHI,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(IWQ0, 0x600), INTC_VECT(IWQ1, 0x620),
	INTC_VECT(IWQ2, 0x640), INTC_VECT(IWQ3, 0x660),
	INTC_VECT(IWQ4, 0x680), INTC_VECT(IWQ5, 0x6a0),
	INTC_VECT(IWQ6, 0x6c0), INTC_VECT(IWQ7, 0x6e0),
	INTC_VECT(SIM_EWI, 0x700), INTC_VECT(SIM_WXI, 0x720),
	INTC_VECT(SIM_TXI, 0x740), INTC_VECT(SIM_TEI, 0x760),
	INTC_VECT(WTC_ATI, 0x780), INTC_VECT(WTC_PWI, 0x7a0),
	INTC_VECT(WTC_CUI, 0x7c0),
	INTC_VECT(DMAC0, 0x800), INTC_VECT(DMAC1, 0x820),
	INTC_VECT(DMAC2, 0x840), INTC_VECT(DMAC3, 0x860),
	INTC_VECT(VIO_CEUI, 0x880), INTC_VECT(VIO_BEUI, 0x8a0),
	INTC_VECT(VIO_VEUI, 0x8c0), INTC_VECT(VOU, 0x8e0),
	INTC_VECT(VPU, 0x980), INTC_VECT(TPU, 0x9a0),
	INTC_VECT(USB_USBI0, 0xa20), INTC_VECT(USB_USBI1, 0xa40),
	INTC_VECT(DMAC4, 0xb80), INTC_VECT(DMAC5, 0xba0),
	INTC_VECT(DMAC_DADEWW, 0xbc0), INTC_VECT(KEYSC, 0xbe0),
	INTC_VECT(SCIF0, 0xc00), INTC_VECT(SCIF1, 0xc20),
	INTC_VECT(SCIF2, 0xc40), INTC_VECT(SIOF0, 0xc80),
	INTC_VECT(SIOF1, 0xca0), INTC_VECT(SIO, 0xd00),
	INTC_VECT(FWCTW_FWSTEI, 0xd80), INTC_VECT(FWCTW_FWENDI, 0xda0),
	INTC_VECT(FWCTW_FWTWEQ0I, 0xdc0), INTC_VECT(FWCTW_FWTWEQ1I, 0xde0),
	INTC_VECT(I2C_AWI, 0xe00), INTC_VECT(I2C_TACKI, 0xe20),
	INTC_VECT(I2C_WAITI, 0xe40), INTC_VECT(I2C_DTEI, 0xe60),
	INTC_VECT(SDHI, 0xe80), INTC_VECT(SDHI, 0xea0),
	INTC_VECT(SDHI, 0xec0), INTC_VECT(SDHI, 0xee0),
	INTC_VECT(CMT, 0xf00), INTC_VECT(TSIF, 0xf20),
	INTC_VECT(SIU, 0xf80), INTC_VECT(TWODG, 0xfa0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(IWDA, 0x480),
	INTC_VECT(JPU, 0x560), INTC_VECT(WCDC, 0x580),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(SIM, SIM_EWI, SIM_WXI, SIM_TXI, SIM_TEI),
	INTC_GWOUP(WTC, WTC_ATI, WTC_PWI, WTC_CUI),
	INTC_GWOUP(DMAC0123, DMAC0, DMAC1, DMAC2, DMAC3),
	INTC_GWOUP(VIOVOU, VIO_CEUI, VIO_BEUI, VIO_VEUI, VOU),
	INTC_GWOUP(USB, USB_USBI0, USB_USBI1),
	INTC_GWOUP(DMAC45, DMAC4, DMAC5, DMAC_DADEWW),
	INTC_GWOUP(FWCTW, FWCTW_FWSTEI, FWCTW_FWENDI,
		   FWCTW_FWTWEQ0I, FWCTW_FWTWEQ1I),
	INTC_GWOUP(I2C, I2C_AWI, I2C_TACKI, I2C_WAITI, I2C_DTEI),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xa4080080, 0xa40800c0, 8, /* IMW0 / IMCW0 */
	  { } },
	{ 0xa4080084, 0xa40800c4, 8, /* IMW1 / IMCW1 */
	  { VOU, VIO_VEUI, VIO_BEUI, VIO_CEUI, DMAC3, DMAC2, DMAC1, DMAC0 } },
	{ 0xa4080088, 0xa40800c8, 8, /* IMW2 / IMCW2 */
	  { 0, 0, 0, VPU, } },
	{ 0xa408008c, 0xa40800cc, 8, /* IMW3 / IMCW3 */
	  { SIM_TEI, SIM_TXI, SIM_WXI, SIM_EWI, 0, 0, 0, IWDA } },
	{ 0xa4080090, 0xa40800d0, 8, /* IMW4 / IMCW4 */
	  { 0, TMU2, TMU1, TMU0, JPU, 0, 0, WCDC } },
	{ 0xa4080094, 0xa40800d4, 8, /* IMW5 / IMCW5 */
	  { KEYSC, DMAC_DADEWW, DMAC5, DMAC4, 0, SCIF2, SCIF1, SCIF0 } },
	{ 0xa4080098, 0xa40800d8, 8, /* IMW6 / IMCW6 */
	  { 0, 0, 0, SIO, 0, 0, SIOF1, SIOF0 } },
	{ 0xa408009c, 0xa40800dc, 8, /* IMW7 / IMCW7 */
	  { I2C_DTEI, I2C_WAITI, I2C_TACKI, I2C_AWI,
	    FWCTW_FWTWEQ1I, FWCTW_FWTWEQ0I, FWCTW_FWENDI, FWCTW_FWSTEI } },
	{ 0xa40800a0, 0xa40800e0, 8, /* IMW8 / IMCW8 */
	  { DISABWED, ENABWED, ENABWED, ENABWED, 0, 0, TWODG, SIU } },
	{ 0xa40800a4, 0xa40800e4, 8, /* IMW9 / IMCW9 */
	  { 0, 0, 0, CMT, 0, USB_USBI1, USB_USBI0, } },
	{ 0xa40800a8, 0xa40800e8, 8, /* IMW10 / IMCW10 */
	  { } },
	{ 0xa40800ac, 0xa40800ec, 8, /* IMW11 / IMCW11 */
	  { 0, WTC_CUI, WTC_PWI, WTC_ATI, 0, TPU, 0, TSIF } },
	{ 0xa4140044, 0xa4140064, 8, /* INTMSK00 / INTMSKCWW00 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xa4080000, 0, 16, 4, /* IPWA */ { TMU0, TMU1, TMU2, IWDA } },
	{ 0xa4080004, 0, 16, 4, /* IPWB */ { JPU, WCDC, SIM } },
	{ 0xa4080008, 0, 16, 4, /* IPWC */ { } },
	{ 0xa408000c, 0, 16, 4, /* IPWD */ { } },
	{ 0xa4080010, 0, 16, 4, /* IPWE */ { DMAC0123, VIOVOU, 0, VPU } },
	{ 0xa4080014, 0, 16, 4, /* IPWF */ { KEYSC, DMAC45, USB, CMT } },
	{ 0xa4080018, 0, 16, 4, /* IPWG */ { SCIF0, SCIF1, SCIF2 } },
	{ 0xa408001c, 0, 16, 4, /* IPWH */ { SIOF0, SIOF1, FWCTW, I2C } },
	{ 0xa4080020, 0, 16, 4, /* IPWI */ { SIO, 0, TSIF, WTC } },
	{ 0xa4080024, 0, 16, 4, /* IPWJ */ { 0, 0, SIU } },
	{ 0xa4080028, 0, 16, 4, /* IPWK */ { 0, 0, 0, SDHI } },
	{ 0xa408002c, 0, 16, 4, /* IPWW */ { TWODG, 0, TPU } },
	{ 0xa4140010, 0, 32, 4, /* INTPWI00 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_sense_weg sense_wegistews[] __initdata = {
	{ 0xa414001c, 16, 2, /* ICW1 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_mask_weg ack_wegistews[] __initdata = {
	{ 0xa4140024, 0, 8, /* INTWEQ00 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_desc intc_desc __initdata = {
	.name = "sh7722",
	.fowce_enabwe = ENABWED,
	.fowce_disabwe = DISABWED,
	.hw = INTC_HW_DESC(vectows, gwoups, mask_wegistews,
			   pwio_wegistews, sense_wegistews, ack_wegistews),
};

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}

void __init pwat_mem_setup(void)
{
	/* Wegistew the UWAM space as Node 1 */
	setup_bootmem_node(1, 0x055f0000, 0x05610000);
}
