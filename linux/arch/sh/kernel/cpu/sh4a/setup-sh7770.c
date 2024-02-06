// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7770 Setup
 *
 *  Copywight (C) 2006 - 2008  Pauw Mundt
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <winux/io.h>
#incwude <asm/pwatfowm_eawwy.h>

static stwuct pwat_sci_powt scif0_pwatfowm_data = {
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif0_wesouwces[] = {
	DEFINE_WES_MEM(0xff923000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x9a0)),
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
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif1_wesouwces[] = {
	DEFINE_WES_MEM(0xff924000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x9c0)),
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
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif2_wesouwces[] = {
	DEFINE_WES_MEM(0xff925000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0x9e0)),
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
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif3_wesouwces[] = {
	DEFINE_WES_MEM(0xff926000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xa00)),
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
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif4_wesouwces[] = {
	DEFINE_WES_MEM(0xff927000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xa20)),
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
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif5_wesouwces[] = {
	DEFINE_WES_MEM(0xff928000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xa40)),
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

static stwuct pwat_sci_powt scif6_pwatfowm_data = {
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif6_wesouwces[] = {
	DEFINE_WES_MEM(0xff929000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xa60)),
};

static stwuct pwatfowm_device scif6_device = {
	.name		= "sh-sci",
	.id		= 6,
	.wesouwce	= scif6_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif6_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif6_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif7_pwatfowm_data = {
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif7_wesouwces[] = {
	DEFINE_WES_MEM(0xff92a000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xa80)),
};

static stwuct pwatfowm_device scif7_device = {
	.name		= "sh-sci",
	.id		= 7,
	.wesouwce	= scif7_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif7_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif7_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif8_pwatfowm_data = {
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif8_wesouwces[] = {
	DEFINE_WES_MEM(0xff92b000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xaa0)),
};

static stwuct pwatfowm_device scif8_device = {
	.name		= "sh-sci",
	.id		= 8,
	.wesouwce	= scif8_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif8_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif8_pwatfowm_data,
	},
};

static stwuct pwat_sci_powt scif9_pwatfowm_data = {
	.scscw		= SCSCW_WEIE | SCSCW_TOIE,
	.type		= POWT_SCIF,
};

static stwuct wesouwce scif9_wesouwces[] = {
	DEFINE_WES_MEM(0xff92c000, 0x100),
	DEFINE_WES_IWQ(evt2iwq(0xac0)),
};

static stwuct pwatfowm_device scif9_device = {
	.name		= "sh-sci",
	.id		= 9,
	.wesouwce	= scif9_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(scif9_wesouwces),
	.dev		= {
		.pwatfowm_data	= &scif9_pwatfowm_data,
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

static stwuct sh_timew_config tmu1_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu1_wesouwces[] = {
	DEFINE_WES_MEM(0xffd81000, 0x30),
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

static stwuct sh_timew_config tmu2_pwatfowm_data = {
	.channews_mask = 7,
};

static stwuct wesouwce tmu2_wesouwces[] = {
	DEFINE_WES_MEM(0xffd82000, 0x2c),
	DEFINE_WES_IWQ(evt2iwq(0x4c0)),
	DEFINE_WES_IWQ(evt2iwq(0x4e0)),
	DEFINE_WES_IWQ(evt2iwq(0x500)),
};

static stwuct pwatfowm_device tmu2_device = {
	.name		= "sh-tmu",
	.id		= 2,
	.dev = {
		.pwatfowm_data	= &tmu2_pwatfowm_data,
	},
	.wesouwce	= tmu2_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(tmu2_wesouwces),
};

static stwuct pwatfowm_device *sh7770_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&scif6_device,
	&scif7_device,
	&scif8_device,
	&scif9_device,
	&tmu0_device,
	&tmu1_device,
	&tmu2_device,
};

static int __init sh7770_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sh7770_devices,
				    AWWAY_SIZE(sh7770_devices));
}
awch_initcaww(sh7770_devices_setup);

static stwuct pwatfowm_device *sh7770_eawwy_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&scif6_device,
	&scif7_device,
	&scif8_device,
	&scif9_device,
	&tmu0_device,
	&tmu1_device,
	&tmu2_device,
};

void __init pwat_eawwy_device_setup(void)
{
	sh_eawwy_pwatfowm_add_devices(sh7770_eawwy_devices,
				   AWWAY_SIZE(sh7770_eawwy_devices));
}

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWW_WWWW, IWW_WWWH, IWW_WWHW, IWW_WWHH,
	IWW_WHWW, IWW_WHWH, IWW_WHHW, IWW_WHHH,
	IWW_HWWW, IWW_HWWH, IWW_HWHW, IWW_HWHH,
	IWW_HHWW, IWW_HHWH, IWW_HHHW,

	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5,

	GPIO,
	TMU0, TMU1, TMU2, TMU2_TICPI,
	TMU3, TMU4, TMU5, TMU5_TICPI,
	TMU6, TMU7, TMU8,
	HAC, IPI, SPDIF, HUDI, I2C,
	DMAC0_DMINT0, DMAC0_DMINT1, DMAC0_DMINT2,
	I2S0, I2S1, I2S2, I2S3,
	SWC_WX, SWC_TX, SWC_SPDIF,
	DU, VIDEO_IN, WEMOTE, YUV, USB, ATAPI, CAN, GPS, GFX2D,
	GFX3D_MBX, GFX3D_DMAC,
	EXBUS_ATA,
	SPI0, SPI1,
	SCIF089, SCIF1234, SCIF567,
	ADC,
	BBDMAC_0_3, BBDMAC_4_7, BBDMAC_8_10, BBDMAC_11_14,
	BBDMAC_15_18, BBDMAC_19_22, BBDMAC_23_26, BBDMAC_27,
	BBDMAC_28, BBDMAC_29, BBDMAC_30, BBDMAC_31,

	/* intewwupt gwoups */
	TMU, DMAC, I2S, SWC, GFX3D, SPI, SCIF, BBDMAC,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(GPIO, 0x3e0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2_TICPI, 0x460),
	INTC_VECT(TMU3, 0x480), INTC_VECT(TMU4, 0x4a0),
	INTC_VECT(TMU5, 0x4c0), INTC_VECT(TMU5_TICPI, 0x4e0),
	INTC_VECT(TMU6, 0x500), INTC_VECT(TMU7, 0x520),
	INTC_VECT(TMU8, 0x540),
	INTC_VECT(HAC, 0x580), INTC_VECT(IPI, 0x5c0),
	INTC_VECT(SPDIF, 0x5e0),
	INTC_VECT(HUDI, 0x600), INTC_VECT(I2C, 0x620),
	INTC_VECT(DMAC0_DMINT0, 0x640), INTC_VECT(DMAC0_DMINT1, 0x660),
	INTC_VECT(DMAC0_DMINT2, 0x680),
	INTC_VECT(I2S0, 0x6a0), INTC_VECT(I2S1, 0x6c0),
	INTC_VECT(I2S2, 0x6e0), INTC_VECT(I2S3, 0x700),
	INTC_VECT(SWC_WX, 0x720), INTC_VECT(SWC_TX, 0x740),
	INTC_VECT(SWC_SPDIF, 0x760),
	INTC_VECT(DU, 0x780), INTC_VECT(VIDEO_IN, 0x7a0),
	INTC_VECT(WEMOTE, 0x7c0), INTC_VECT(YUV, 0x7e0),
	INTC_VECT(USB, 0x840), INTC_VECT(ATAPI, 0x860),
	INTC_VECT(CAN, 0x880), INTC_VECT(GPS, 0x8a0),
	INTC_VECT(GFX2D, 0x8c0),
	INTC_VECT(GFX3D_MBX, 0x900), INTC_VECT(GFX3D_DMAC, 0x920),
	INTC_VECT(EXBUS_ATA, 0x940),
	INTC_VECT(SPI0, 0x960), INTC_VECT(SPI1, 0x980),
	INTC_VECT(SCIF089, 0x9a0), INTC_VECT(SCIF1234, 0x9c0),
	INTC_VECT(SCIF1234, 0x9e0), INTC_VECT(SCIF1234, 0xa00),
	INTC_VECT(SCIF1234, 0xa20), INTC_VECT(SCIF567, 0xa40),
	INTC_VECT(SCIF567, 0xa60), INTC_VECT(SCIF567, 0xa80),
	INTC_VECT(SCIF089, 0xaa0), INTC_VECT(SCIF089, 0xac0),
	INTC_VECT(ADC, 0xb20),
	INTC_VECT(BBDMAC_0_3, 0xba0), INTC_VECT(BBDMAC_0_3, 0xbc0),
	INTC_VECT(BBDMAC_0_3, 0xbe0), INTC_VECT(BBDMAC_0_3, 0xc00),
	INTC_VECT(BBDMAC_4_7, 0xc20), INTC_VECT(BBDMAC_4_7, 0xc40),
	INTC_VECT(BBDMAC_4_7, 0xc60), INTC_VECT(BBDMAC_4_7, 0xc80),
	INTC_VECT(BBDMAC_8_10, 0xca0), INTC_VECT(BBDMAC_8_10, 0xcc0),
	INTC_VECT(BBDMAC_8_10, 0xce0), INTC_VECT(BBDMAC_11_14, 0xd00),
	INTC_VECT(BBDMAC_11_14, 0xd20), INTC_VECT(BBDMAC_11_14, 0xd40),
	INTC_VECT(BBDMAC_11_14, 0xd60), INTC_VECT(BBDMAC_15_18, 0xd80),
	INTC_VECT(BBDMAC_15_18, 0xda0), INTC_VECT(BBDMAC_15_18, 0xdc0),
	INTC_VECT(BBDMAC_15_18, 0xde0), INTC_VECT(BBDMAC_19_22, 0xe00),
	INTC_VECT(BBDMAC_19_22, 0xe20), INTC_VECT(BBDMAC_19_22, 0xe40),
	INTC_VECT(BBDMAC_19_22, 0xe60), INTC_VECT(BBDMAC_23_26, 0xe80),
	INTC_VECT(BBDMAC_23_26, 0xea0), INTC_VECT(BBDMAC_23_26, 0xec0),
	INTC_VECT(BBDMAC_23_26, 0xee0), INTC_VECT(BBDMAC_27, 0xf00),
	INTC_VECT(BBDMAC_28, 0xf20), INTC_VECT(BBDMAC_29, 0xf40),
	INTC_VECT(BBDMAC_30, 0xf60), INTC_VECT(BBDMAC_31, 0xf80),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(TMU, TMU0, TMU1, TMU2, TMU2_TICPI, TMU3, TMU4, TMU5,
		   TMU5_TICPI, TMU6, TMU7, TMU8),
	INTC_GWOUP(DMAC, DMAC0_DMINT0, DMAC0_DMINT1, DMAC0_DMINT2),
	INTC_GWOUP(I2S, I2S0, I2S1, I2S2, I2S3),
	INTC_GWOUP(SWC, SWC_WX, SWC_TX, SWC_SPDIF),
	INTC_GWOUP(GFX3D, GFX3D_MBX, GFX3D_DMAC),
	INTC_GWOUP(SPI, SPI0, SPI1),
	INTC_GWOUP(SCIF, SCIF089, SCIF1234, SCIF567),
	INTC_GWOUP(BBDMAC,
		   BBDMAC_0_3, BBDMAC_4_7, BBDMAC_8_10, BBDMAC_11_14,
		   BBDMAC_15_18, BBDMAC_19_22, BBDMAC_23_26, BBDMAC_27,
		   BBDMAC_28, BBDMAC_29, BBDMAC_30, BBDMAC_31),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xffe00040, 0xffe00044, 32, /* INT2MSKW / INT2MSKCW */
	  { 0, BBDMAC, ADC, SCIF, SPI, EXBUS_ATA, GFX3D, GFX2D,
	    GPS, CAN, ATAPI, USB, YUV, WEMOTE, VIDEO_IN, DU, SWC, I2S,
	    DMAC, I2C, HUDI, SPDIF, IPI, HAC, TMU, GPIO } },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xffe00000, 0, 32, 8, /* INT2PWI0 */ { GPIO, TMU0, 0, HAC } },
	{ 0xffe00004, 0, 32, 8, /* INT2PWI1 */ { IPI, SPDIF, HUDI, I2C } },
	{ 0xffe00008, 0, 32, 8, /* INT2PWI2 */ { DMAC, I2S, SWC, DU } },
	{ 0xffe0000c, 0, 32, 8, /* INT2PWI3 */ { VIDEO_IN, WEMOTE, YUV, USB } },
	{ 0xffe00010, 0, 32, 8, /* INT2PWI4 */ { ATAPI, CAN, GPS, GFX2D } },
	{ 0xffe00014, 0, 32, 8, /* INT2PWI5 */ { 0, GFX3D, EXBUS_ATA, SPI } },
	{ 0xffe00018, 0, 32, 8, /* INT2PWI6 */ { SCIF1234, SCIF567, SCIF089 } },
	{ 0xffe0001c, 0, 32, 8, /* INT2PWI7 */ { ADC, 0, 0, BBDMAC_0_3 } },
	{ 0xffe00020, 0, 32, 8, /* INT2PWI8 */
	  { BBDMAC_4_7, BBDMAC_8_10, BBDMAC_11_14, BBDMAC_15_18 } },
	{ 0xffe00024, 0, 32, 8, /* INT2PWI9 */
	  { BBDMAC_19_22, BBDMAC_23_26, BBDMAC_27, BBDMAC_28 } },
	{ 0xffe00028, 0, 32, 8, /* INT2PWI10 */
	  { BBDMAC_29, BBDMAC_30, BBDMAC_31 } },
	{ 0xffe0002c, 0, 32, 8, /* INT2PWI11 */
	  { TMU1, TMU2, TMU2_TICPI, TMU3 } },
	{ 0xffe00030, 0, 32, 8, /* INT2PWI12 */
	  { TMU4, TMU5, TMU5_TICPI, TMU6 } },
	{ 0xffe00034, 0, 32, 8, /* INT2PWI13 */
	  { TMU7, TMU8 } },
};

static DECWAWE_INTC_DESC(intc_desc, "sh7770", vectows, gwoups,
			 mask_wegistews, pwio_wegistews, NUWW);

/* Suppowt fow extewnaw intewwupt pins in IWQ mode */
static stwuct intc_vect iwq_vectows[] __initdata = {
	INTC_VECT(IWQ0, 0x240), INTC_VECT(IWQ1, 0x280),
	INTC_VECT(IWQ2, 0x2c0), INTC_VECT(IWQ3, 0x300),
	INTC_VECT(IWQ4, 0x340), INTC_VECT(IWQ5, 0x380),
};

static stwuct intc_mask_weg iwq_mask_wegistews[] __initdata = {
	{ 0xffd00044, 0xffd00064, 32, /* INTMSK0 / INTMSKCWW0 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, } },
};

static stwuct intc_pwio_weg iwq_pwio_wegistews[] __initdata = {
	{ 0xffd00010, 0, 32, 4, /* INTPWI */ { IWQ0, IWQ1, IWQ2, IWQ3,
					       IWQ4, IWQ5, } },
};

static stwuct intc_sense_weg iwq_sense_wegistews[] __initdata = {
	{ 0xffd0001c, 32, 2, /* ICW1 */   { IWQ0, IWQ1, IWQ2, IWQ3,
					    IWQ4, IWQ5, } },
};

static DECWAWE_INTC_DESC(intc_iwq_desc, "sh7770-iwq", iwq_vectows,
			 NUWW, iwq_mask_wegistews, iwq_pwio_wegistews,
			 iwq_sense_wegistews);

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

static DECWAWE_INTC_DESC(intc_iww7654_desc, "sh7780-iww7654", iww_vectows,
			 NUWW, iww7654_mask_wegistews, NUWW, NUWW);

static DECWAWE_INTC_DESC(intc_iww3210_desc, "sh7780-iww3210", iww_vectows,
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

	/* sewect IWW mode fow IWW3-0 + IWW7-4 */
	__waw_wwitew(__waw_weadw(INTC_ICW0) & ~0x00c00000, INTC_ICW0);

	/* disabwe howding function, ie enabwe "SH-4 Mode" */
	__waw_wwitew(__waw_weadw(INTC_ICW0) | 0x00200000, INTC_ICW0);

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
