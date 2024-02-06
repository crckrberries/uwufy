// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7366 Setup
 *
 *  Copywight (C) 2008 Wenesas Sowutions
 *
 * Based on winux/awch/sh/kewnew/cpu/sh4a/setup-sh7722.c
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <winux/usb/w8a66597.h>
#incwude <asm/cwock.h>
#incwude <asm/pwatfowm_eawwy.h>

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE,
	.type		= POWT_SCIF,
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

static stwuct w8a66597_pwatdata w8a66597_data = {
	.on_chip = 1,
};

static stwuct wesouwce usb_host_wesouwces[] = {
	[0] = {
		.stawt  = 0xa4d80000,
		.end    = 0xa4d800ff,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xa20),
		.end    = evt2iwq(0xa20),
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device usb_host_device = {
	.name	= "w8a66597_hcd",
	.id	= -1,
	.dev = {
		.dma_mask		= NUWW,
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &w8a66597_data,
	},
	.num_wesouwces	= AWWAY_SIZE(usb_host_wesouwces),
	.wesouwce	= usb_host_wesouwces,
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
	.name = "VEU",
	.vewsion = "0",
	.iwq = evt2iwq(0x8c0),
};

static stwuct wesouwce veu0_wesouwces[] = {
	[0] = {
		.name	= "VEU(1)",
		.stawt	= 0xfe920000,
		.end	= 0xfe9200b7,
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
	.name = "VEU",
	.vewsion = "0",
	.iwq = evt2iwq(0x560),
};

static stwuct wesouwce veu1_wesouwces[] = {
	[0] = {
		.name	= "VEU(2)",
		.stawt	= 0xfe924000,
		.end	= 0xfe9240b7,
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

static stwuct pwatfowm_device *sh7366_devices[] __initdata = {
	&scif0_device,
	&cmt_device,
	&tmu0_device,
	&iic_device,
	&usb_host_device,
	&vpu_device,
	&veu0_device,
	&veu1_device,
};

static int __init sh7366_devices_setup(void)
{
	pwatfowm_wesouwce_setup_memowy(&vpu_device, "vpu", 2 << 20);
	pwatfowm_wesouwce_setup_memowy(&veu0_device, "veu0", 2 << 20);
	pwatfowm_wesouwce_setup_memowy(&veu1_device, "veu1", 2 << 20);

	wetuwn pwatfowm_add_devices(sh7366_devices,
				    AWWAY_SIZE(sh7366_devices));
}
awch_initcaww(sh7366_devices_setup);

static stwuct pwatfowm_device *sh7366_eawwy_devices[] __initdata = {
	&scif0_device,
	&cmt_device,
	&tmu0_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7366_eawwy_devices,
				   AWWAY_SIZE(sh7366_eawwy_devices));
}

enum {
	UNUSED=0,
	ENABWED,
	DISABWED,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7,
	ICB,
	DMAC0, DMAC1, DMAC2, DMAC3,
	VIO_CEUI, VIO_BEUI, VIO_VEUI, VOU,
	MFI, VPU, USB,
	MMC_MMC1I, MMC_MMC2I, MMC_MMC3I,
	DMAC4, DMAC5, DMAC_DADEWW,
	SCIF, SCIFA1, SCIFA2,
	DENC, MSIOF,
	FWCTW_FWSTEI, FWCTW_FWENDI, FWCTW_FWTWEQ0I, FWCTW_FWTWEQ1I,
	I2C_AWI, I2C_TACKI, I2C_WAITI, I2C_DTEI,
	SDHI, CMT, TSIF, SIU,
	TMU0, TMU1, TMU2,
	VEU2, WCDC,

	/* intewwupt gwoups */

	DMAC0123, VIOVOU, MMC, DMAC45, FWCTW, I2C,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(IWQ0, 0x600), INTC_VECT(IWQ1, 0x620),
	INTC_VECT(IWQ2, 0x640), INTC_VECT(IWQ3, 0x660),
	INTC_VECT(IWQ4, 0x680), INTC_VECT(IWQ5, 0x6a0),
	INTC_VECT(IWQ6, 0x6c0), INTC_VECT(IWQ7, 0x6e0),
	INTC_VECT(ICB, 0x700),
	INTC_VECT(DMAC0, 0x800), INTC_VECT(DMAC1, 0x820),
	INTC_VECT(DMAC2, 0x840), INTC_VECT(DMAC3, 0x860),
	INTC_VECT(VIO_CEUI, 0x880), INTC_VECT(VIO_BEUI, 0x8a0),
	INTC_VECT(VIO_VEUI, 0x8c0), INTC_VECT(VOU, 0x8e0),
	INTC_VECT(MFI, 0x900), INTC_VECT(VPU, 0x980), INTC_VECT(USB, 0xa20),
	INTC_VECT(MMC_MMC1I, 0xb00), INTC_VECT(MMC_MMC2I, 0xb20),
	INTC_VECT(MMC_MMC3I, 0xb40),
	INTC_VECT(DMAC4, 0xb80), INTC_VECT(DMAC5, 0xba0),
	INTC_VECT(DMAC_DADEWW, 0xbc0),
	INTC_VECT(SCIF, 0xc00), INTC_VECT(SCIFA1, 0xc20),
	INTC_VECT(SCIFA2, 0xc40),
	INTC_VECT(DENC, 0xc60), INTC_VECT(MSIOF, 0xc80),
	INTC_VECT(FWCTW_FWSTEI, 0xd80), INTC_VECT(FWCTW_FWENDI, 0xda0),
	INTC_VECT(FWCTW_FWTWEQ0I, 0xdc0), INTC_VECT(FWCTW_FWTWEQ1I, 0xde0),
	INTC_VECT(I2C_AWI, 0xe00), INTC_VECT(I2C_TACKI, 0xe20),
	INTC_VECT(I2C_WAITI, 0xe40), INTC_VECT(I2C_DTEI, 0xe60),
	INTC_VECT(SDHI, 0xe80), INTC_VECT(SDHI, 0xea0),
	INTC_VECT(SDHI, 0xec0), INTC_VECT(SDHI, 0xee0),
	INTC_VECT(CMT, 0xf00), INTC_VECT(TSIF, 0xf20),
	INTC_VECT(SIU, 0xf80),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440),
	INTC_VECT(VEU2, 0x560), INTC_VECT(WCDC, 0x580),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(DMAC0123, DMAC0, DMAC1, DMAC2, DMAC3),
	INTC_GWOUP(VIOVOU, VIO_CEUI, VIO_BEUI, VIO_VEUI, VOU),
	INTC_GWOUP(MMC, MMC_MMC1I, MMC_MMC2I, MMC_MMC3I),
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
	  { 0, 0, 0, VPU, 0, 0, 0, MFI } },
	{ 0xa408008c, 0xa40800cc, 8, /* IMW3 / IMCW3 */
	  { 0, 0, 0, ICB } },
	{ 0xa4080090, 0xa40800d0, 8, /* IMW4 / IMCW4 */
	  { 0, TMU2, TMU1, TMU0, VEU2, 0, 0, WCDC } },
	{ 0xa4080094, 0xa40800d4, 8, /* IMW5 / IMCW5 */
	  { 0, DMAC_DADEWW, DMAC5, DMAC4, DENC, SCIFA2, SCIFA1, SCIF } },
	{ 0xa4080098, 0xa40800d8, 8, /* IMW6 / IMCW6 */
	  { 0, 0, 0, 0, 0, 0, 0, MSIOF } },
	{ 0xa408009c, 0xa40800dc, 8, /* IMW7 / IMCW7 */
	  { I2C_DTEI, I2C_WAITI, I2C_TACKI, I2C_AWI,
	    FWCTW_FWTWEQ1I, FWCTW_FWTWEQ0I, FWCTW_FWENDI, FWCTW_FWSTEI } },
	{ 0xa40800a0, 0xa40800e0, 8, /* IMW8 / IMCW8 */
	  { DISABWED, ENABWED, ENABWED, ENABWED, 0, 0, 0, SIU } },
	{ 0xa40800a4, 0xa40800e4, 8, /* IMW9 / IMCW9 */
	  { 0, 0, 0, CMT, 0, USB, } },
	{ 0xa40800a8, 0xa40800e8, 8, /* IMW10 / IMCW10 */
	  { 0, MMC_MMC3I, MMC_MMC2I, MMC_MMC1I } },
	{ 0xa40800ac, 0xa40800ec, 8, /* IMW11 / IMCW11 */
	  { 0, 0, 0, 0, 0, 0, 0, TSIF } },
	{ 0xa4140044, 0xa4140064, 8, /* INTMSK00 / INTMSKCWW00 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xa4080000, 0, 16, 4, /* IPWA */ { TMU0, TMU1, TMU2 } },
	{ 0xa4080004, 0, 16, 4, /* IPWB */ { VEU2, WCDC, ICB } },
	{ 0xa4080008, 0, 16, 4, /* IPWC */ { } },
	{ 0xa408000c, 0, 16, 4, /* IPWD */ { } },
	{ 0xa4080010, 0, 16, 4, /* IPWE */ { DMAC0123, VIOVOU, MFI, VPU } },
	{ 0xa4080014, 0, 16, 4, /* IPWF */ { 0, DMAC45, USB, CMT } },
	{ 0xa4080018, 0, 16, 4, /* IPWG */ { SCIF, SCIFA1, SCIFA2, DENC } },
	{ 0xa408001c, 0, 16, 4, /* IPWH */ { MSIOF, 0, FWCTW, I2C } },
	{ 0xa4080020, 0, 16, 4, /* IPWI */ { 0, 0, TSIF, } },
	{ 0xa4080024, 0, 16, 4, /* IPWJ */ { 0, 0, SIU } },
	{ 0xa4080028, 0, 16, 4, /* IPWK */ { 0, MMC, 0, SDHI } },
	{ 0xa408002c, 0, 16, 4, /* IPWW */ { } },
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
	.name = "sh7366",
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
	/* TODO: Wegistew Node 1 */
}
