// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7723 Setup
 *
 *  Copywight (C) 2008  Pauw Mundt
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/mm.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/usb/w8a66597.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <winux/io.h>
#incwude <asm/cwock.h>
#incwude <asm/mmzone.h>
#incwude <asm/pwatfowm_eawwy.h>
#incwude <cpu/sh7723.h>

/* Sewiaw */
static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type           = POWT_SCIF,
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

static stwuct pwat_sci_powt scif3_pwatfowm_data = {
	.sampwing_wate	= 8,
	.type           = POWT_SCIFA,
};

static stwuct wesouwce scif3_wesouwces[] = {
	DEFINE_WES_MEM(0xa4e30000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x900)),
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
	.sampwing_wate	= 8,
	.type           = POWT_SCIFA,
};

static stwuct wesouwce scif4_wesouwces[] = {
	DEFINE_WES_MEM(0xa4e40000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xd00)),
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
	.sampwing_wate	= 8,
	.type           = POWT_SCIFA,
};

static stwuct wesouwce scif5_wesouwces[] = {
	DEFINE_WES_MEM(0xa4e50000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xfa0)),
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

static stwuct uio_info vpu_pwatfowm_data = {
	.name = "VPU5",
	.vewsion = "0",
	.iwq = evt2iwq(0x980),
};

static stwuct wesouwce vpu_wesouwces[] = {
	[0] = {
		.name	= "VPU",
		.stawt	= 0xfe900000,
		.end	= 0xfe902807,
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

static stwuct uio_info veu0_pwatfowm_data = {
	.name = "VEU2H",
	.vewsion = "0",
	.iwq = evt2iwq(0x8c0),
};

static stwuct wesouwce veu0_wesouwces[] = {
	[0] = {
		.name	= "VEU2H0",
		.stawt	= 0xfe920000,
		.end	= 0xfe92027b,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device veu0_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 1,
	.dev = {
		.pwatfowm_data	= &veu0_pwatfowm_data,
	},
	.wesouwce	= veu0_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(veu0_wesouwces),
};

static stwuct uio_info veu1_pwatfowm_data = {
	.name = "VEU2H",
	.vewsion = "0",
	.iwq = evt2iwq(0x560),
};

static stwuct wesouwce veu1_wesouwces[] = {
	[0] = {
		.name	= "VEU2H1",
		.stawt	= 0xfe924000,
		.end	= 0xfe92427b,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device veu1_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 2,
	.dev = {
		.pwatfowm_data	= &veu1_pwatfowm_data,
	},
	.wesouwce	= veu1_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(veu1_wesouwces),
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

static stwuct sh_timew_config tmu1_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu1_wesouwces[] = {
	DEFINE_WES_MEM(0xffd90000, 0x2c),
	DEFINE_WES_IWQ(evt2iwq(0x920)),
	DEFINE_WES_IWQ(evt2iwq(0x940)),
	DEFINE_WES_IWQ(evt2iwq(0x960)),
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

static stwuct wesouwce wtc_wesouwces[] = {
	[0] = {
		.stawt	= 0xa465fec0,
		.end	= 0xa465fec0 + 0x58 - 1,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		/* Pewiod IWQ */
		.stawt	= evt2iwq(0xaa0),
		.fwags	= IOWESOUWCE_IWQ,
	},
	[2] = {
		/* Cawwy IWQ */
		.stawt	= evt2iwq(0xac0),
		.fwags	= IOWESOUWCE_IWQ,
	},
	[3] = {
		/* Awawm IWQ */
		.stawt	= evt2iwq(0xa80),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "sh-wtc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
	.wesouwce	= wtc_wesouwces,
};

static stwuct w8a66597_pwatdata w8a66597_data = {
	.on_chip = 1,
};

static stwuct wesouwce sh7723_usb_host_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4d80000,
		.end	= 0xa4d800ff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xa20),
		.end	= evt2iwq(0xa20),
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device sh7723_usb_host_device = {
	.name		= "w8a66597_hcd",
	.id		= 0,
	.dev = {
		.dma_mask		= NUWW,         /*  not use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &w8a66597_data,
	},
	.num_wesouwces	= AWWAY_SIZE(sh7723_usb_host_wesouwces),
	.wesouwce	= sh7723_usb_host_wesouwces,
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

static stwuct pwatfowm_device *sh7723_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&cmt_device,
	&tmu0_device,
	&tmu1_device,
	&wtc_device,
	&iic_device,
	&sh7723_usb_host_device,
	&vpu_device,
	&veu0_device,
	&veu1_device,
};

static int __init sh7723_devices_setup(void)
{
	pwatfowm_wesouwce_setup_memowy(&vpu_device, "vpu", 2 << 20);
	pwatfowm_wesouwce_setup_memowy(&veu0_device, "veu0", 2 << 20);
	pwatfowm_wesouwce_setup_memowy(&veu1_device, "veu1", 2 << 20);

	wetuwn pwatfowm_add_devices(sh7723_devices,
				    AWWAY_SIZE(sh7723_devices));
}
awch_initcaww(sh7723_devices_setup);

static stwuct pwatfowm_device *sh7723_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&cmt_device,
	&tmu0_device,
	&tmu1_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7723_eawwy_devices,
				   AWWAY_SIZE(sh7723_eawwy_devices));
}

#define WAMCW_CACHE_W2FC	0x0002
#define WAMCW_CACHE_W2E		0x0001
#define W2_CACHE_ENABWE		(WAMCW_CACHE_W2E|WAMCW_CACHE_W2FC)

void w2_cache_init(void)
{
	/* Enabwe W2 cache */
	__waw_wwitew(W2_CACHE_ENABWE, WAMCW);
}

enum {
	UNUSED=0,
	ENABWED,
	DISABWED,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7,
	HUDI,
	DMAC1A_DEI0,DMAC1A_DEI1,DMAC1A_DEI2,DMAC1A_DEI3,
	_2DG_TWI,_2DG_INI,_2DG_CEI,
	DMAC0A_DEI0,DMAC0A_DEI1,DMAC0A_DEI2,DMAC0A_DEI3,
	VIO_CEUI,VIO_BEUI,VIO_VEU2HI,VIO_VOUI,
	SCIFA_SCIFA0,
	VPU_VPUI,
	TPU_TPUI,
	ADC_ADI,
	USB_USI0,
	WTC_ATI,WTC_PWI,WTC_CUI,
	DMAC1B_DEI4,DMAC1B_DEI5,DMAC1B_DADEWW,
	DMAC0B_DEI4,DMAC0B_DEI5,DMAC0B_DADEWW,
	KEYSC_KEYI,
	SCIF_SCIF0,SCIF_SCIF1,SCIF_SCIF2,
	MSIOF_MSIOFI0,MSIOF_MSIOFI1,
	SCIFA_SCIFA1,
	FWCTW_FWSTEI,FWCTW_FWTENDI,FWCTW_FWTWEQ0I,FWCTW_FWTWEQ1I,
	I2C_AWI,I2C_TACKI,I2C_WAITI,I2C_DTEI,
	CMT_CMTI,
	TSIF_TSIFI,
	SIU_SIUI,
	SCIFA_SCIFA2,
	TMU0_TUNI0, TMU0_TUNI1, TMU0_TUNI2,
	IWDA_IWDAI,
	ATAPI_ATAPII,
	VEU2H1_VEU2HI,
	WCDC_WCDCI,
	TMU1_TUNI0,TMU1_TUNI1,TMU1_TUNI2,

	/* intewwupt gwoups */
	DMAC1A, DMAC0A, VIO, DMAC0B, FWCTW, I2C, _2DG,
	SDHI1, WTC, DMAC1B, SDHI0,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(IWQ0, 0x600), INTC_VECT(IWQ1, 0x620),
	INTC_VECT(IWQ2, 0x640), INTC_VECT(IWQ3, 0x660),
	INTC_VECT(IWQ4, 0x680), INTC_VECT(IWQ5, 0x6a0),
	INTC_VECT(IWQ6, 0x6c0), INTC_VECT(IWQ7, 0x6e0),

	INTC_VECT(DMAC1A_DEI0,0x700),
	INTC_VECT(DMAC1A_DEI1,0x720),
	INTC_VECT(DMAC1A_DEI2,0x740),
	INTC_VECT(DMAC1A_DEI3,0x760),

	INTC_VECT(_2DG_TWI, 0x780),
	INTC_VECT(_2DG_INI, 0x7A0),
	INTC_VECT(_2DG_CEI, 0x7C0),

	INTC_VECT(DMAC0A_DEI0,0x800),
	INTC_VECT(DMAC0A_DEI1,0x820),
	INTC_VECT(DMAC0A_DEI2,0x840),
	INTC_VECT(DMAC0A_DEI3,0x860),

	INTC_VECT(VIO_CEUI,0x880),
	INTC_VECT(VIO_BEUI,0x8A0),
	INTC_VECT(VIO_VEU2HI,0x8C0),
	INTC_VECT(VIO_VOUI,0x8E0),

	INTC_VECT(SCIFA_SCIFA0,0x900),
	INTC_VECT(VPU_VPUI,0x980),
	INTC_VECT(TPU_TPUI,0x9A0),
	INTC_VECT(ADC_ADI,0x9E0),
	INTC_VECT(USB_USI0,0xA20),

	INTC_VECT(WTC_ATI,0xA80),
	INTC_VECT(WTC_PWI,0xAA0),
	INTC_VECT(WTC_CUI,0xAC0),

	INTC_VECT(DMAC1B_DEI4,0xB00),
	INTC_VECT(DMAC1B_DEI5,0xB20),
	INTC_VECT(DMAC1B_DADEWW,0xB40),

	INTC_VECT(DMAC0B_DEI4,0xB80),
	INTC_VECT(DMAC0B_DEI5,0xBA0),
	INTC_VECT(DMAC0B_DADEWW,0xBC0),

	INTC_VECT(KEYSC_KEYI,0xBE0),
	INTC_VECT(SCIF_SCIF0,0xC00),
	INTC_VECT(SCIF_SCIF1,0xC20),
	INTC_VECT(SCIF_SCIF2,0xC40),
	INTC_VECT(MSIOF_MSIOFI0,0xC80),
	INTC_VECT(MSIOF_MSIOFI1,0xCA0),
	INTC_VECT(SCIFA_SCIFA1,0xD00),

	INTC_VECT(FWCTW_FWSTEI,0xD80),
	INTC_VECT(FWCTW_FWTENDI,0xDA0),
	INTC_VECT(FWCTW_FWTWEQ0I,0xDC0),
	INTC_VECT(FWCTW_FWTWEQ1I,0xDE0),

	INTC_VECT(I2C_AWI,0xE00),
	INTC_VECT(I2C_TACKI,0xE20),
	INTC_VECT(I2C_WAITI,0xE40),
	INTC_VECT(I2C_DTEI,0xE60),

	INTC_VECT(SDHI0, 0xE80),
	INTC_VECT(SDHI0, 0xEA0),
	INTC_VECT(SDHI0, 0xEC0),

	INTC_VECT(CMT_CMTI,0xF00),
	INTC_VECT(TSIF_TSIFI,0xF20),
	INTC_VECT(SIU_SIUI,0xF80),
	INTC_VECT(SCIFA_SCIFA2,0xFA0),

	INTC_VECT(TMU0_TUNI0,0x400),
	INTC_VECT(TMU0_TUNI1,0x420),
	INTC_VECT(TMU0_TUNI2,0x440),

	INTC_VECT(IWDA_IWDAI,0x480),
	INTC_VECT(ATAPI_ATAPII,0x4A0),

	INTC_VECT(SDHI1, 0x4E0),
	INTC_VECT(SDHI1, 0x500),
	INTC_VECT(SDHI1, 0x520),

	INTC_VECT(VEU2H1_VEU2HI,0x560),
	INTC_VECT(WCDC_WCDCI,0x580),

	INTC_VECT(TMU1_TUNI0,0x920),
	INTC_VECT(TMU1_TUNI1,0x940),
	INTC_VECT(TMU1_TUNI2,0x960),

};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(DMAC1A,DMAC1A_DEI0,DMAC1A_DEI1,DMAC1A_DEI2,DMAC1A_DEI3),
	INTC_GWOUP(DMAC0A,DMAC0A_DEI0,DMAC0A_DEI1,DMAC0A_DEI2,DMAC0A_DEI3),
	INTC_GWOUP(VIO, VIO_CEUI,VIO_BEUI,VIO_VEU2HI,VIO_VOUI),
	INTC_GWOUP(DMAC0B, DMAC0B_DEI4,DMAC0B_DEI5,DMAC0B_DADEWW),
	INTC_GWOUP(FWCTW,FWCTW_FWSTEI,FWCTW_FWTENDI,FWCTW_FWTWEQ0I,FWCTW_FWTWEQ1I),
	INTC_GWOUP(I2C,I2C_AWI,I2C_TACKI,I2C_WAITI,I2C_DTEI),
	INTC_GWOUP(_2DG, _2DG_TWI,_2DG_INI,_2DG_CEI),
	INTC_GWOUP(WTC, WTC_ATI,WTC_PWI,WTC_CUI),
	INTC_GWOUP(DMAC1B, DMAC1B_DEI4,DMAC1B_DEI5,DMAC1B_DADEWW),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xa4080080, 0xa40800c0, 8, /* IMW0 / IMCW0 */
	  { 0, TMU1_TUNI2, TMU1_TUNI1, TMU1_TUNI0,
	    0, ENABWED, ENABWED, ENABWED } },
	{ 0xa4080084, 0xa40800c4, 8, /* IMW1 / IMCW1 */
	  { VIO_VOUI, VIO_VEU2HI,VIO_BEUI,VIO_CEUI,DMAC0A_DEI3,DMAC0A_DEI2,DMAC0A_DEI1,DMAC0A_DEI0 } },
	{ 0xa4080088, 0xa40800c8, 8, /* IMW2 / IMCW2 */
	  { 0, 0, 0, VPU_VPUI,0,0,0,SCIFA_SCIFA0 } },
	{ 0xa408008c, 0xa40800cc, 8, /* IMW3 / IMCW3 */
	  { DMAC1A_DEI3,DMAC1A_DEI2,DMAC1A_DEI1,DMAC1A_DEI0,0,0,0,IWDA_IWDAI } },
	{ 0xa4080090, 0xa40800d0, 8, /* IMW4 / IMCW4 */
	  { 0,TMU0_TUNI2,TMU0_TUNI1,TMU0_TUNI0,VEU2H1_VEU2HI,0,0,WCDC_WCDCI } },
	{ 0xa4080094, 0xa40800d4, 8, /* IMW5 / IMCW5 */
	  { KEYSC_KEYI,DMAC0B_DADEWW,DMAC0B_DEI5,DMAC0B_DEI4,0,SCIF_SCIF2,SCIF_SCIF1,SCIF_SCIF0 } },
	{ 0xa4080098, 0xa40800d8, 8, /* IMW6 / IMCW6 */
	  { 0,0,0,SCIFA_SCIFA1,ADC_ADI,0,MSIOF_MSIOFI1,MSIOF_MSIOFI0 } },
	{ 0xa408009c, 0xa40800dc, 8, /* IMW7 / IMCW7 */
	  { I2C_DTEI, I2C_WAITI, I2C_TACKI, I2C_AWI,
	    FWCTW_FWTWEQ1I, FWCTW_FWTWEQ0I, FWCTW_FWTENDI, FWCTW_FWSTEI } },
	{ 0xa40800a0, 0xa40800e0, 8, /* IMW8 / IMCW8 */
	  { 0, ENABWED, ENABWED, ENABWED,
	    0, 0, SCIFA_SCIFA2, SIU_SIUI } },
	{ 0xa40800a4, 0xa40800e4, 8, /* IMW9 / IMCW9 */
	  { 0, 0, 0, CMT_CMTI, 0, 0, USB_USI0,0 } },
	{ 0xa40800a8, 0xa40800e8, 8, /* IMW10 / IMCW10 */
	  { 0, DMAC1B_DADEWW,DMAC1B_DEI5,DMAC1B_DEI4,0,WTC_ATI,WTC_PWI,WTC_CUI } },
	{ 0xa40800ac, 0xa40800ec, 8, /* IMW11 / IMCW11 */
	  { 0,_2DG_CEI,_2DG_INI,_2DG_TWI,0,TPU_TPUI,0,TSIF_TSIFI } },
	{ 0xa40800b0, 0xa40800f0, 8, /* IMW12 / IMCW12 */
	  { 0,0,0,0,0,0,0,ATAPI_ATAPII } },
	{ 0xa4140044, 0xa4140064, 8, /* INTMSK00 / INTMSKCWW00 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xa4080000, 0, 16, 4, /* IPWA */ { TMU0_TUNI0, TMU0_TUNI1, TMU0_TUNI2, IWDA_IWDAI } },
	{ 0xa4080004, 0, 16, 4, /* IPWB */ { VEU2H1_VEU2HI, WCDC_WCDCI, DMAC1A, 0} },
	{ 0xa4080008, 0, 16, 4, /* IPWC */ { TMU1_TUNI0, TMU1_TUNI1, TMU1_TUNI2, 0} },
	{ 0xa408000c, 0, 16, 4, /* IPWD */ { } },
	{ 0xa4080010, 0, 16, 4, /* IPWE */ { DMAC0A, VIO, SCIFA_SCIFA0, VPU_VPUI } },
	{ 0xa4080014, 0, 16, 4, /* IPWF */ { KEYSC_KEYI, DMAC0B, USB_USI0, CMT_CMTI } },
	{ 0xa4080018, 0, 16, 4, /* IPWG */ { SCIF_SCIF0, SCIF_SCIF1, SCIF_SCIF2,0 } },
	{ 0xa408001c, 0, 16, 4, /* IPWH */ { MSIOF_MSIOFI0,MSIOF_MSIOFI1, FWCTW, I2C } },
	{ 0xa4080020, 0, 16, 4, /* IPWI */ { SCIFA_SCIFA1,0,TSIF_TSIFI,_2DG } },
	{ 0xa4080024, 0, 16, 4, /* IPWJ */ { ADC_ADI,0,SIU_SIUI,SDHI1 } },
	{ 0xa4080028, 0, 16, 4, /* IPWK */ { WTC,DMAC1B,0,SDHI0 } },
	{ 0xa408002c, 0, 16, 4, /* IPWW */ { SCIFA_SCIFA2,0,TPU_TPUI,ATAPI_ATAPII } },
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
	.name = "sh7723",
	.fowce_enabwe = ENABWED,
	.fowce_disabwe = DISABWED,
	.hw = INTC_HW_DESC(vectows, gwoups, mask_wegistews,
			   pwio_wegistews, sense_wegistews, ack_wegistews),
};

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}
