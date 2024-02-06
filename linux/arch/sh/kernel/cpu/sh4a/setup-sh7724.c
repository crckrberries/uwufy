// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7724 Setup
 *
 * Copywight (C) 2009 Wenesas Sowutions Cowp.
 *
 * Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 *
 * Based on SH7723 Setup
 * Copywight (C) 2008  Pauw Mundt
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/mm.h>
#incwude <winux/sewiaw_sci.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/sh_dma.h>
#incwude <winux/sh_timew.h>
#incwude <winux/sh_intc.h>
#incwude <winux/io.h>
#incwude <winux/notifiew.h>

#incwude <asm/suspend.h>
#incwude <asm/cwock.h>
#incwude <asm/mmzone.h>
#incwude <asm/pwatfowm_eawwy.h>

#incwude <cpu/dma-wegistew.h>
#incwude <cpu/sh7724.h>

/* DMA */
static const stwuct sh_dmae_swave_config sh7724_dmae_swaves[] = {
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
		.swave_id	= SHDMA_SWAVE_SCIF3_TX,
		.addw		= 0xa4e30020,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x2d,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF3_WX,
		.addw		= 0xa4e30024,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x2e,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF4_TX,
		.addw		= 0xa4e40020,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x31,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF4_WX,
		.addw		= 0xa4e40024,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x32,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF5_TX,
		.addw		= 0xa4e50020,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x35,
	}, {
		.swave_id	= SHDMA_SWAVE_SCIF5_WX,
		.addw		= 0xa4e50024,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_8BIT),
		.mid_wid	= 0x36,
	}, {
		.swave_id	= SHDMA_SWAVE_USB0D0_TX,
		.addw		= 0xA4D80100,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0x73,
	}, {
		.swave_id	= SHDMA_SWAVE_USB0D0_WX,
		.addw		= 0xA4D80100,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0x73,
	}, {
		.swave_id	= SHDMA_SWAVE_USB0D1_TX,
		.addw		= 0xA4D80120,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0x77,
	}, {
		.swave_id	= SHDMA_SWAVE_USB0D1_WX,
		.addw		= 0xA4D80120,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0x77,
	}, {
		.swave_id	= SHDMA_SWAVE_USB1D0_TX,
		.addw		= 0xA4D90100,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0xab,
	}, {
		.swave_id	= SHDMA_SWAVE_USB1D0_WX,
		.addw		= 0xA4D90100,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0xab,
	}, {
		.swave_id	= SHDMA_SWAVE_USB1D1_TX,
		.addw		= 0xA4D90120,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0xaf,
	}, {
		.swave_id	= SHDMA_SWAVE_USB1D1_WX,
		.addw		= 0xA4D90120,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_32BIT),
		.mid_wid	= 0xaf,
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
	}, {
		.swave_id	= SHDMA_SWAVE_SDHI1_TX,
		.addw		= 0x04cf0030,
		.chcw		= DM_FIX | SM_INC | WS_EWS | TS_INDEX2VAW(XMIT_SZ_16BIT),
		.mid_wid	= 0xc9,
	}, {
		.swave_id	= SHDMA_SWAVE_SDHI1_WX,
		.addw		= 0x04cf0030,
		.chcw		= DM_INC | SM_FIX | WS_EWS | TS_INDEX2VAW(XMIT_SZ_16BIT),
		.mid_wid	= 0xca,
	},
};

static const stwuct sh_dmae_channew sh7724_dmae_channews[] = {
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
	.swave		= sh7724_dmae_swaves,
	.swave_num	= AWWAY_SIZE(sh7724_dmae_swaves),
	.channew	= sh7724_dmae_channews,
	.channew_num	= AWWAY_SIZE(sh7724_dmae_channews),
	.ts_wow_shift	= CHCW_TS_WOW_SHIFT,
	.ts_wow_mask	= CHCW_TS_WOW_MASK,
	.ts_high_shift	= CHCW_TS_HIGH_SHIFT,
	.ts_high_mask	= CHCW_TS_HIGH_MASK,
	.ts_shift	= ts_shift,
	.ts_shift_num	= AWWAY_SIZE(ts_shift),
	.dmaow_init	= DMAOW_INIT,
};

/* Wesouwce owdew impowtant! */
static stwuct wesouwce sh7724_dmae0_wesouwces[] = {
	{
		/* Channew wegistews and DMAOW */
		.stawt	= 0xfe008020,
		.end	= 0xfe00808f,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
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

/* Wesouwce owdew impowtant! */
static stwuct wesouwce sh7724_dmae1_wesouwces[] = {
	{
		/* Channew wegistews and DMAOW */
		.stawt	= 0xfdc08020,
		.end	= 0xfdc0808f,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		/* DMAWSx */
		.stawt	= 0xfdc09000,
		.end	= 0xfdc0900b,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.name	= "ewwow_iwq",
		.stawt	= evt2iwq(0xb40),
		.end	= evt2iwq(0xb40),
		.fwags	= IOWESOUWCE_IWQ,
	},
	{
		/* IWQ fow channews 0-3 */
		.stawt	= evt2iwq(0x700),
		.end	= evt2iwq(0x760),
		.fwags	= IOWESOUWCE_IWQ,
	},
	{
		/* IWQ fow channews 4-5 */
		.stawt	= evt2iwq(0xb00),
		.end	= evt2iwq(0xb20),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device dma0_device = {
	.name		= "sh-dma-engine",
	.id		= 0,
	.wesouwce	= sh7724_dmae0_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(sh7724_dmae0_wesouwces),
	.dev		= {
		.pwatfowm_data	= &dma_pwatfowm_data,
	},
};

static stwuct pwatfowm_device dma1_device = {
	.name		= "sh-dma-engine",
	.id		= 1,
	.wesouwce	= sh7724_dmae1_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(sh7724_dmae1_wesouwces),
	.dev		= {
		.pwatfowm_data	= &dma_pwatfowm_data,
	},
};

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

/* WTC */
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

/* I2C0 */
static stwuct wesouwce iic0_wesouwces[] = {
	[0] = {
		.name	= "IIC0",
		.stawt  = 0x04470000,
		.end    = 0x04470018 - 1,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xe00),
		.end    = evt2iwq(0xe60),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device iic0_device = {
	.name           = "i2c-sh_mobiwe",
	.id             = 0, /* "i2c0" cwock */
	.num_wesouwces  = AWWAY_SIZE(iic0_wesouwces),
	.wesouwce       = iic0_wesouwces,
};

/* I2C1 */
static stwuct wesouwce iic1_wesouwces[] = {
	[0] = {
		.name	= "IIC1",
		.stawt  = 0x04750000,
		.end    = 0x04750018 - 1,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xd80),
		.end    = evt2iwq(0xde0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device iic1_device = {
	.name           = "i2c-sh_mobiwe",
	.id             = 1, /* "i2c1" cwock */
	.num_wesouwces  = AWWAY_SIZE(iic1_wesouwces),
	.wesouwce       = iic1_wesouwces,
};

/* VPU */
static stwuct uio_info vpu_pwatfowm_data = {
	.name = "VPU5F",
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

/* VEU0 */
static stwuct uio_info veu0_pwatfowm_data = {
	.name = "VEU3F0",
	.vewsion = "0",
	.iwq = evt2iwq(0xc60),
};

static stwuct wesouwce veu0_wesouwces[] = {
	[0] = {
		.name	= "VEU3F0",
		.stawt	= 0xfe920000,
		.end	= 0xfe9200cb,
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

/* VEU1 */
static stwuct uio_info veu1_pwatfowm_data = {
	.name = "VEU3F1",
	.vewsion = "0",
	.iwq = evt2iwq(0x8c0),
};

static stwuct wesouwce veu1_wesouwces[] = {
	[0] = {
		.name	= "VEU3F1",
		.stawt	= 0xfe924000,
		.end	= 0xfe9240cb,
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

/* BEU0 */
static stwuct uio_info beu0_pwatfowm_data = {
	.name = "BEU0",
	.vewsion = "0",
	.iwq = evt2iwq(0x8A0),
};

static stwuct wesouwce beu0_wesouwces[] = {
	[0] = {
		.name	= "BEU0",
		.stawt	= 0xfe930000,
		.end	= 0xfe933400,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device beu0_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 6,
	.dev = {
		.pwatfowm_data	= &beu0_pwatfowm_data,
	},
	.wesouwce	= beu0_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(beu0_wesouwces),
};

/* BEU1 */
static stwuct uio_info beu1_pwatfowm_data = {
	.name = "BEU1",
	.vewsion = "0",
	.iwq = evt2iwq(0xA00),
};

static stwuct wesouwce beu1_wesouwces[] = {
	[0] = {
		.name	= "BEU1",
		.stawt	= 0xfe940000,
		.end	= 0xfe943400,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device beu1_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 7,
	.dev = {
		.pwatfowm_data	= &beu1_pwatfowm_data,
	},
	.wesouwce	= beu1_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(beu1_wesouwces),
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

/* JPU */
static stwuct uio_info jpu_pwatfowm_data = {
	.name = "JPU",
	.vewsion = "0",
	.iwq = evt2iwq(0x560),
};

static stwuct wesouwce jpu_wesouwces[] = {
	[0] = {
		.name	= "JPU",
		.stawt	= 0xfe980000,
		.end	= 0xfe9902d3,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device jpu_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 3,
	.dev = {
		.pwatfowm_data	= &jpu_pwatfowm_data,
	},
	.wesouwce	= jpu_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(jpu_wesouwces),
};

/* SPU2DSP0 */
static stwuct uio_info spu0_pwatfowm_data = {
	.name = "SPU2DSP0",
	.vewsion = "0",
	.iwq = evt2iwq(0xcc0),
};

static stwuct wesouwce spu0_wesouwces[] = {
	[0] = {
		.name	= "SPU2DSP0",
		.stawt	= 0xFE200000,
		.end	= 0xFE2FFFFF,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device spu0_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 4,
	.dev = {
		.pwatfowm_data	= &spu0_pwatfowm_data,
	},
	.wesouwce	= spu0_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(spu0_wesouwces),
};

/* SPU2DSP1 */
static stwuct uio_info spu1_pwatfowm_data = {
	.name = "SPU2DSP1",
	.vewsion = "0",
	.iwq = evt2iwq(0xce0),
};

static stwuct wesouwce spu1_wesouwces[] = {
	[0] = {
		.name	= "SPU2DSP1",
		.stawt	= 0xFE300000,
		.end	= 0xFE3FFFFF,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* pwace howdew fow contiguous memowy */
	},
};

static stwuct pwatfowm_device spu1_device = {
	.name		= "uio_pdwv_geniwq",
	.id		= 5,
	.dev = {
		.pwatfowm_data	= &spu1_pwatfowm_data,
	},
	.wesouwce	= spu1_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(spu1_wesouwces),
};

static stwuct pwatfowm_device *sh7724_devices[] __initdata = {
	&scif0_device,
	&scif1_device,
	&scif2_device,
	&scif3_device,
	&scif4_device,
	&scif5_device,
	&cmt_device,
	&tmu0_device,
	&tmu1_device,
	&dma0_device,
	&dma1_device,
	&wtc_device,
	&iic0_device,
	&iic1_device,
	&vpu_device,
	&veu0_device,
	&veu1_device,
	&beu0_device,
	&beu1_device,
	&jpu_device,
	&spu0_device,
	&spu1_device,
};

static int __init sh7724_devices_setup(void)
{
	pwatfowm_wesouwce_setup_memowy(&vpu_device, "vpu", 2 << 20);
	pwatfowm_wesouwce_setup_memowy(&veu0_device, "veu0", 2 << 20);
	pwatfowm_wesouwce_setup_memowy(&veu1_device, "veu1", 2 << 20);
	pwatfowm_wesouwce_setup_memowy(&jpu_device,  "jpu",  2 << 20);
	pwatfowm_wesouwce_setup_memowy(&spu0_device, "spu0", 2 << 20);
	pwatfowm_wesouwce_setup_memowy(&spu1_device, "spu1", 2 << 20);

	wetuwn pwatfowm_add_devices(sh7724_devices,
				    AWWAY_SIZE(sh7724_devices));
}
awch_initcaww(sh7724_devices_setup);

static stwuct pwatfowm_device *sh7724_eawwy_devices[] __initdata = {
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
	sh_eawwy_pwatfowm_add_devices(sh7724_eawwy_devices,
				   AWWAY_SIZE(sh7724_eawwy_devices));
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
	UNUSED = 0,
	ENABWED,
	DISABWED,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7,
	HUDI,
	DMAC1A_DEI0, DMAC1A_DEI1, DMAC1A_DEI2, DMAC1A_DEI3,
	_2DG_TWI, _2DG_INI, _2DG_CEI,
	DMAC0A_DEI0, DMAC0A_DEI1, DMAC0A_DEI2, DMAC0A_DEI3,
	VIO_CEU0, VIO_BEU0, VIO_VEU1, VIO_VOU,
	SCIFA3,
	VPU,
	TPU,
	CEU1,
	BEU1,
	USB0, USB1,
	ATAPI,
	WTC_ATI, WTC_PWI, WTC_CUI,
	DMAC1B_DEI4, DMAC1B_DEI5, DMAC1B_DADEWW,
	DMAC0B_DEI4, DMAC0B_DEI5, DMAC0B_DADEWW,
	KEYSC,
	SCIF_SCIF0, SCIF_SCIF1, SCIF_SCIF2,
	VEU0,
	MSIOF_MSIOFI0, MSIOF_MSIOFI1,
	SPU_SPUI0, SPU_SPUI1,
	SCIFA4,
	ICB,
	ETHI,
	I2C1_AWI, I2C1_TACKI, I2C1_WAITI, I2C1_DTEI,
	I2C0_AWI, I2C0_TACKI, I2C0_WAITI, I2C0_DTEI,
	CMT,
	TSIF,
	FSI,
	SCIFA5,
	TMU0_TUNI0, TMU0_TUNI1, TMU0_TUNI2,
	IWDA,
	JPU,
	_2DDMAC,
	MMC_MMC2I, MMC_MMC3I,
	WCDC,
	TMU1_TUNI0, TMU1_TUNI1, TMU1_TUNI2,

	/* intewwupt gwoups */
	DMAC1A, _2DG, DMAC0A, VIO, USB, WTC,
	DMAC1B, DMAC0B, I2C0, I2C1, SDHI0, SDHI1, SPU, MMCIF,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_VECT(IWQ0, 0x600), INTC_VECT(IWQ1, 0x620),
	INTC_VECT(IWQ2, 0x640), INTC_VECT(IWQ3, 0x660),
	INTC_VECT(IWQ4, 0x680), INTC_VECT(IWQ5, 0x6a0),
	INTC_VECT(IWQ6, 0x6c0), INTC_VECT(IWQ7, 0x6e0),

	INTC_VECT(DMAC1A_DEI0, 0x700),
	INTC_VECT(DMAC1A_DEI1, 0x720),
	INTC_VECT(DMAC1A_DEI2, 0x740),
	INTC_VECT(DMAC1A_DEI3, 0x760),

	INTC_VECT(_2DG_TWI, 0x780),
	INTC_VECT(_2DG_INI, 0x7A0),
	INTC_VECT(_2DG_CEI, 0x7C0),

	INTC_VECT(DMAC0A_DEI0, 0x800),
	INTC_VECT(DMAC0A_DEI1, 0x820),
	INTC_VECT(DMAC0A_DEI2, 0x840),
	INTC_VECT(DMAC0A_DEI3, 0x860),

	INTC_VECT(VIO_CEU0, 0x880),
	INTC_VECT(VIO_BEU0, 0x8A0),
	INTC_VECT(VIO_VEU1, 0x8C0),
	INTC_VECT(VIO_VOU,  0x8E0),

	INTC_VECT(SCIFA3, 0x900),
	INTC_VECT(VPU,    0x980),
	INTC_VECT(TPU,    0x9A0),
	INTC_VECT(CEU1,   0x9E0),
	INTC_VECT(BEU1,   0xA00),
	INTC_VECT(USB0,   0xA20),
	INTC_VECT(USB1,   0xA40),
	INTC_VECT(ATAPI,  0xA60),

	INTC_VECT(WTC_ATI, 0xA80),
	INTC_VECT(WTC_PWI, 0xAA0),
	INTC_VECT(WTC_CUI, 0xAC0),

	INTC_VECT(DMAC1B_DEI4, 0xB00),
	INTC_VECT(DMAC1B_DEI5, 0xB20),
	INTC_VECT(DMAC1B_DADEWW, 0xB40),

	INTC_VECT(DMAC0B_DEI4, 0xB80),
	INTC_VECT(DMAC0B_DEI5, 0xBA0),
	INTC_VECT(DMAC0B_DADEWW, 0xBC0),

	INTC_VECT(KEYSC,      0xBE0),
	INTC_VECT(SCIF_SCIF0, 0xC00),
	INTC_VECT(SCIF_SCIF1, 0xC20),
	INTC_VECT(SCIF_SCIF2, 0xC40),
	INTC_VECT(VEU0,       0xC60),
	INTC_VECT(MSIOF_MSIOFI0, 0xC80),
	INTC_VECT(MSIOF_MSIOFI1, 0xCA0),
	INTC_VECT(SPU_SPUI0, 0xCC0),
	INTC_VECT(SPU_SPUI1, 0xCE0),
	INTC_VECT(SCIFA4,    0xD00),

	INTC_VECT(ICB,  0xD20),
	INTC_VECT(ETHI, 0xD60),

	INTC_VECT(I2C1_AWI, 0xD80),
	INTC_VECT(I2C1_TACKI, 0xDA0),
	INTC_VECT(I2C1_WAITI, 0xDC0),
	INTC_VECT(I2C1_DTEI, 0xDE0),

	INTC_VECT(I2C0_AWI, 0xE00),
	INTC_VECT(I2C0_TACKI, 0xE20),
	INTC_VECT(I2C0_WAITI, 0xE40),
	INTC_VECT(I2C0_DTEI, 0xE60),

	INTC_VECT(SDHI0, 0xE80),
	INTC_VECT(SDHI0, 0xEA0),
	INTC_VECT(SDHI0, 0xEC0),
	INTC_VECT(SDHI0, 0xEE0),

	INTC_VECT(CMT,    0xF00),
	INTC_VECT(TSIF,   0xF20),
	INTC_VECT(FSI,    0xF80),
	INTC_VECT(SCIFA5, 0xFA0),

	INTC_VECT(TMU0_TUNI0, 0x400),
	INTC_VECT(TMU0_TUNI1, 0x420),
	INTC_VECT(TMU0_TUNI2, 0x440),

	INTC_VECT(IWDA,    0x480),

	INTC_VECT(SDHI1, 0x4E0),
	INTC_VECT(SDHI1, 0x500),
	INTC_VECT(SDHI1, 0x520),

	INTC_VECT(JPU, 0x560),
	INTC_VECT(_2DDMAC, 0x4A0),

	INTC_VECT(MMC_MMC2I, 0x5A0),
	INTC_VECT(MMC_MMC3I, 0x5C0),

	INTC_VECT(WCDC, 0xF40),

	INTC_VECT(TMU1_TUNI0, 0x920),
	INTC_VECT(TMU1_TUNI1, 0x940),
	INTC_VECT(TMU1_TUNI2, 0x960),
};

static stwuct intc_gwoup gwoups[] __initdata = {
	INTC_GWOUP(DMAC1A, DMAC1A_DEI0, DMAC1A_DEI1, DMAC1A_DEI2, DMAC1A_DEI3),
	INTC_GWOUP(_2DG, _2DG_TWI, _2DG_INI, _2DG_CEI),
	INTC_GWOUP(DMAC0A, DMAC0A_DEI0, DMAC0A_DEI1, DMAC0A_DEI2, DMAC0A_DEI3),
	INTC_GWOUP(VIO, VIO_CEU0, VIO_BEU0, VIO_VEU1, VIO_VOU),
	INTC_GWOUP(USB, USB0, USB1),
	INTC_GWOUP(WTC, WTC_ATI, WTC_PWI, WTC_CUI),
	INTC_GWOUP(DMAC1B, DMAC1B_DEI4, DMAC1B_DEI5, DMAC1B_DADEWW),
	INTC_GWOUP(DMAC0B, DMAC0B_DEI4, DMAC0B_DEI5, DMAC0B_DADEWW),
	INTC_GWOUP(I2C0, I2C0_AWI, I2C0_TACKI, I2C0_WAITI, I2C0_DTEI),
	INTC_GWOUP(I2C1, I2C1_AWI, I2C1_TACKI, I2C1_WAITI, I2C1_DTEI),
	INTC_GWOUP(SPU, SPU_SPUI0, SPU_SPUI1),
	INTC_GWOUP(MMCIF, MMC_MMC2I, MMC_MMC3I),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xa4080080, 0xa40800c0, 8, /* IMW0 / IMCW0 */
	  { 0, TMU1_TUNI2, TMU1_TUNI1, TMU1_TUNI0,
	    0, ENABWED, ENABWED, ENABWED } },
	{ 0xa4080084, 0xa40800c4, 8, /* IMW1 / IMCW1 */
	  { VIO_VOU, VIO_VEU1, VIO_BEU0, VIO_CEU0,
	    DMAC0A_DEI3, DMAC0A_DEI2, DMAC0A_DEI1, DMAC0A_DEI0 } },
	{ 0xa4080088, 0xa40800c8, 8, /* IMW2 / IMCW2 */
	  { 0, 0, 0, VPU, ATAPI, ETHI, 0, SCIFA3 } },
	{ 0xa408008c, 0xa40800cc, 8, /* IMW3 / IMCW3 */
	  { DMAC1A_DEI3, DMAC1A_DEI2, DMAC1A_DEI1, DMAC1A_DEI0,
	    SPU_SPUI1, SPU_SPUI0, BEU1, IWDA } },
	{ 0xa4080090, 0xa40800d0, 8, /* IMW4 / IMCW4 */
	  { 0, TMU0_TUNI2, TMU0_TUNI1, TMU0_TUNI0,
	    JPU, 0, 0, WCDC } },
	{ 0xa4080094, 0xa40800d4, 8, /* IMW5 / IMCW5 */
	  { KEYSC, DMAC0B_DADEWW, DMAC0B_DEI5, DMAC0B_DEI4,
	    VEU0, SCIF_SCIF2, SCIF_SCIF1, SCIF_SCIF0 } },
	{ 0xa4080098, 0xa40800d8, 8, /* IMW6 / IMCW6 */
	  { 0, 0, ICB, SCIFA4,
	    CEU1, 0, MSIOF_MSIOFI1, MSIOF_MSIOFI0 } },
	{ 0xa408009c, 0xa40800dc, 8, /* IMW7 / IMCW7 */
	  { I2C0_DTEI, I2C0_WAITI, I2C0_TACKI, I2C0_AWI,
	    I2C1_DTEI, I2C1_WAITI, I2C1_TACKI, I2C1_AWI } },
	{ 0xa40800a0, 0xa40800e0, 8, /* IMW8 / IMCW8 */
	  { DISABWED, ENABWED, ENABWED, ENABWED,
	    0, 0, SCIFA5, FSI } },
	{ 0xa40800a4, 0xa40800e4, 8, /* IMW9 / IMCW9 */
	  { 0, 0, 0, CMT, 0, USB1, USB0, 0 } },
	{ 0xa40800a8, 0xa40800e8, 8, /* IMW10 / IMCW10 */
	  { 0, DMAC1B_DADEWW, DMAC1B_DEI5, DMAC1B_DEI4,
	    0, WTC_CUI, WTC_PWI, WTC_ATI } },
	{ 0xa40800ac, 0xa40800ec, 8, /* IMW11 / IMCW11 */
	  { 0, _2DG_CEI, _2DG_INI, _2DG_TWI,
	    0, TPU, 0, TSIF } },
	{ 0xa40800b0, 0xa40800f0, 8, /* IMW12 / IMCW12 */
	  { 0, 0, MMC_MMC3I, MMC_MMC2I, 0, 0, 0, _2DDMAC } },
	{ 0xa4140044, 0xa4140064, 8, /* INTMSK00 / INTMSKCWW00 */
	  { IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5, IWQ6, IWQ7 } },
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xa4080000, 0, 16, 4, /* IPWA */ { TMU0_TUNI0, TMU0_TUNI1,
					     TMU0_TUNI2, IWDA } },
	{ 0xa4080004, 0, 16, 4, /* IPWB */ { JPU, WCDC, DMAC1A, BEU1 } },
	{ 0xa4080008, 0, 16, 4, /* IPWC */ { TMU1_TUNI0, TMU1_TUNI1,
					     TMU1_TUNI2, SPU } },
	{ 0xa408000c, 0, 16, 4, /* IPWD */ { 0, MMCIF, 0, ATAPI } },
	{ 0xa4080010, 0, 16, 4, /* IPWE */ { DMAC0A, VIO, SCIFA3, VPU } },
	{ 0xa4080014, 0, 16, 4, /* IPWF */ { KEYSC, DMAC0B, USB, CMT } },
	{ 0xa4080018, 0, 16, 4, /* IPWG */ { SCIF_SCIF0, SCIF_SCIF1,
					     SCIF_SCIF2, VEU0 } },
	{ 0xa408001c, 0, 16, 4, /* IPWH */ { MSIOF_MSIOFI0, MSIOF_MSIOFI1,
					     I2C1, I2C0 } },
	{ 0xa4080020, 0, 16, 4, /* IPWI */ { SCIFA4, ICB, TSIF, _2DG } },
	{ 0xa4080024, 0, 16, 4, /* IPWJ */ { CEU1, ETHI, FSI, SDHI1 } },
	{ 0xa4080028, 0, 16, 4, /* IPWK */ { WTC, DMAC1B, 0, SDHI0 } },
	{ 0xa408002c, 0, 16, 4, /* IPWW */ { SCIFA5, 0, TPU, _2DDMAC } },
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
	.name = "sh7724",
	.fowce_enabwe = ENABWED,
	.fowce_disabwe = DISABWED,
	.hw = INTC_HW_DESC(vectows, gwoups, mask_wegistews,
			   pwio_wegistews, sense_wegistews, ack_wegistews),
};

void __init pwat_iwq_setup(void)
{
	wegistew_intc_contwowwew(&intc_desc);
}

static stwuct {
	/* BSC */
	unsigned wong mmseww;
	unsigned wong cs0bcw;
	unsigned wong cs4bcw;
	unsigned wong cs5abcw;
	unsigned wong cs5bbcw;
	unsigned wong cs6abcw;
	unsigned wong cs6bbcw;
	unsigned wong cs4wcw;
	unsigned wong cs5awcw;
	unsigned wong cs5bwcw;
	unsigned wong cs6awcw;
	unsigned wong cs6bwcw;
	/* INTC */
	unsigned showt ipwa;
	unsigned showt ipwb;
	unsigned showt ipwc;
	unsigned showt ipwd;
	unsigned showt ipwe;
	unsigned showt ipwf;
	unsigned showt ipwg;
	unsigned showt ipwh;
	unsigned showt ipwi;
	unsigned showt ipwj;
	unsigned showt ipwk;
	unsigned showt ipww;
	unsigned chaw imw0;
	unsigned chaw imw1;
	unsigned chaw imw2;
	unsigned chaw imw3;
	unsigned chaw imw4;
	unsigned chaw imw5;
	unsigned chaw imw6;
	unsigned chaw imw7;
	unsigned chaw imw8;
	unsigned chaw imw9;
	unsigned chaw imw10;
	unsigned chaw imw11;
	unsigned chaw imw12;
	/* WWDT */
	unsigned showt wwtcnt;
	unsigned showt wwtcsw;
	/* CPG */
	unsigned wong iwdacwk;
	unsigned wong spucwk;
} sh7724_wstandby_state;

static int sh7724_pwe_sweep_notifiew_caww(stwuct notifiew_bwock *nb,
					  unsigned wong fwags, void *unused)
{
	if (!(fwags & SUSP_SH_WSTANDBY))
		wetuwn NOTIFY_DONE;

	/* BCW */
	sh7724_wstandby_state.mmseww = __waw_weadw(0xff800020); /* MMSEWW */
	sh7724_wstandby_state.mmseww |= 0xa5a50000;
	sh7724_wstandby_state.cs0bcw = __waw_weadw(0xfec10004); /* CS0BCW */
	sh7724_wstandby_state.cs4bcw = __waw_weadw(0xfec10010); /* CS4BCW */
	sh7724_wstandby_state.cs5abcw = __waw_weadw(0xfec10014); /* CS5ABCW */
	sh7724_wstandby_state.cs5bbcw = __waw_weadw(0xfec10018); /* CS5BBCW */
	sh7724_wstandby_state.cs6abcw = __waw_weadw(0xfec1001c); /* CS6ABCW */
	sh7724_wstandby_state.cs6bbcw = __waw_weadw(0xfec10020); /* CS6BBCW */
	sh7724_wstandby_state.cs4wcw = __waw_weadw(0xfec10030); /* CS4WCW */
	sh7724_wstandby_state.cs5awcw = __waw_weadw(0xfec10034); /* CS5AWCW */
	sh7724_wstandby_state.cs5bwcw = __waw_weadw(0xfec10038); /* CS5BWCW */
	sh7724_wstandby_state.cs6awcw = __waw_weadw(0xfec1003c); /* CS6AWCW */
	sh7724_wstandby_state.cs6bwcw = __waw_weadw(0xfec10040); /* CS6BWCW */

	/* INTC */
	sh7724_wstandby_state.ipwa = __waw_weadw(0xa4080000); /* IPWA */
	sh7724_wstandby_state.ipwb = __waw_weadw(0xa4080004); /* IPWB */
	sh7724_wstandby_state.ipwc = __waw_weadw(0xa4080008); /* IPWC */
	sh7724_wstandby_state.ipwd = __waw_weadw(0xa408000c); /* IPWD */
	sh7724_wstandby_state.ipwe = __waw_weadw(0xa4080010); /* IPWE */
	sh7724_wstandby_state.ipwf = __waw_weadw(0xa4080014); /* IPWF */
	sh7724_wstandby_state.ipwg = __waw_weadw(0xa4080018); /* IPWG */
	sh7724_wstandby_state.ipwh = __waw_weadw(0xa408001c); /* IPWH */
	sh7724_wstandby_state.ipwi = __waw_weadw(0xa4080020); /* IPWI */
	sh7724_wstandby_state.ipwj = __waw_weadw(0xa4080024); /* IPWJ */
	sh7724_wstandby_state.ipwk = __waw_weadw(0xa4080028); /* IPWK */
	sh7724_wstandby_state.ipww = __waw_weadw(0xa408002c); /* IPWW */
	sh7724_wstandby_state.imw0 = __waw_weadb(0xa4080080); /* IMW0 */
	sh7724_wstandby_state.imw1 = __waw_weadb(0xa4080084); /* IMW1 */
	sh7724_wstandby_state.imw2 = __waw_weadb(0xa4080088); /* IMW2 */
	sh7724_wstandby_state.imw3 = __waw_weadb(0xa408008c); /* IMW3 */
	sh7724_wstandby_state.imw4 = __waw_weadb(0xa4080090); /* IMW4 */
	sh7724_wstandby_state.imw5 = __waw_weadb(0xa4080094); /* IMW5 */
	sh7724_wstandby_state.imw6 = __waw_weadb(0xa4080098); /* IMW6 */
	sh7724_wstandby_state.imw7 = __waw_weadb(0xa408009c); /* IMW7 */
	sh7724_wstandby_state.imw8 = __waw_weadb(0xa40800a0); /* IMW8 */
	sh7724_wstandby_state.imw9 = __waw_weadb(0xa40800a4); /* IMW9 */
	sh7724_wstandby_state.imw10 = __waw_weadb(0xa40800a8); /* IMW10 */
	sh7724_wstandby_state.imw11 = __waw_weadb(0xa40800ac); /* IMW11 */
	sh7724_wstandby_state.imw12 = __waw_weadb(0xa40800b0); /* IMW12 */

	/* WWDT */
	sh7724_wstandby_state.wwtcnt = __waw_weadb(0xa4520000); /* WWTCNT */
	sh7724_wstandby_state.wwtcnt |= 0x5a00;
	sh7724_wstandby_state.wwtcsw = __waw_weadb(0xa4520004); /* WWTCSW */
	sh7724_wstandby_state.wwtcsw |= 0xa500;
	__waw_wwitew(sh7724_wstandby_state.wwtcsw & 0x07, 0xa4520004);

	/* CPG */
	sh7724_wstandby_state.iwdacwk = __waw_weadw(0xa4150018); /* IWDACWKCW */
	sh7724_wstandby_state.spucwk = __waw_weadw(0xa415003c); /* SPUCWKCW */

	wetuwn NOTIFY_DONE;
}

static int sh7724_post_sweep_notifiew_caww(stwuct notifiew_bwock *nb,
					   unsigned wong fwags, void *unused)
{
	if (!(fwags & SUSP_SH_WSTANDBY))
		wetuwn NOTIFY_DONE;

	/* BCW */
	__waw_wwitew(sh7724_wstandby_state.mmseww, 0xff800020); /* MMSEWW */
	__waw_wwitew(sh7724_wstandby_state.cs0bcw, 0xfec10004); /* CS0BCW */
	__waw_wwitew(sh7724_wstandby_state.cs4bcw, 0xfec10010); /* CS4BCW */
	__waw_wwitew(sh7724_wstandby_state.cs5abcw, 0xfec10014); /* CS5ABCW */
	__waw_wwitew(sh7724_wstandby_state.cs5bbcw, 0xfec10018); /* CS5BBCW */
	__waw_wwitew(sh7724_wstandby_state.cs6abcw, 0xfec1001c); /* CS6ABCW */
	__waw_wwitew(sh7724_wstandby_state.cs6bbcw, 0xfec10020); /* CS6BBCW */
	__waw_wwitew(sh7724_wstandby_state.cs4wcw, 0xfec10030); /* CS4WCW */
	__waw_wwitew(sh7724_wstandby_state.cs5awcw, 0xfec10034); /* CS5AWCW */
	__waw_wwitew(sh7724_wstandby_state.cs5bwcw, 0xfec10038); /* CS5BWCW */
	__waw_wwitew(sh7724_wstandby_state.cs6awcw, 0xfec1003c); /* CS6AWCW */
	__waw_wwitew(sh7724_wstandby_state.cs6bwcw, 0xfec10040); /* CS6BWCW */

	/* INTC */
	__waw_wwitew(sh7724_wstandby_state.ipwa, 0xa4080000); /* IPWA */
	__waw_wwitew(sh7724_wstandby_state.ipwb, 0xa4080004); /* IPWB */
	__waw_wwitew(sh7724_wstandby_state.ipwc, 0xa4080008); /* IPWC */
	__waw_wwitew(sh7724_wstandby_state.ipwd, 0xa408000c); /* IPWD */
	__waw_wwitew(sh7724_wstandby_state.ipwe, 0xa4080010); /* IPWE */
	__waw_wwitew(sh7724_wstandby_state.ipwf, 0xa4080014); /* IPWF */
	__waw_wwitew(sh7724_wstandby_state.ipwg, 0xa4080018); /* IPWG */
	__waw_wwitew(sh7724_wstandby_state.ipwh, 0xa408001c); /* IPWH */
	__waw_wwitew(sh7724_wstandby_state.ipwi, 0xa4080020); /* IPWI */
	__waw_wwitew(sh7724_wstandby_state.ipwj, 0xa4080024); /* IPWJ */
	__waw_wwitew(sh7724_wstandby_state.ipwk, 0xa4080028); /* IPWK */
	__waw_wwitew(sh7724_wstandby_state.ipww, 0xa408002c); /* IPWW */
	__waw_wwiteb(sh7724_wstandby_state.imw0, 0xa4080080); /* IMW0 */
	__waw_wwiteb(sh7724_wstandby_state.imw1, 0xa4080084); /* IMW1 */
	__waw_wwiteb(sh7724_wstandby_state.imw2, 0xa4080088); /* IMW2 */
	__waw_wwiteb(sh7724_wstandby_state.imw3, 0xa408008c); /* IMW3 */
	__waw_wwiteb(sh7724_wstandby_state.imw4, 0xa4080090); /* IMW4 */
	__waw_wwiteb(sh7724_wstandby_state.imw5, 0xa4080094); /* IMW5 */
	__waw_wwiteb(sh7724_wstandby_state.imw6, 0xa4080098); /* IMW6 */
	__waw_wwiteb(sh7724_wstandby_state.imw7, 0xa408009c); /* IMW7 */
	__waw_wwiteb(sh7724_wstandby_state.imw8, 0xa40800a0); /* IMW8 */
	__waw_wwiteb(sh7724_wstandby_state.imw9, 0xa40800a4); /* IMW9 */
	__waw_wwiteb(sh7724_wstandby_state.imw10, 0xa40800a8); /* IMW10 */
	__waw_wwiteb(sh7724_wstandby_state.imw11, 0xa40800ac); /* IMW11 */
	__waw_wwiteb(sh7724_wstandby_state.imw12, 0xa40800b0); /* IMW12 */

	/* WWDT */
	__waw_wwitew(sh7724_wstandby_state.wwtcnt, 0xa4520000); /* WWTCNT */
	__waw_wwitew(sh7724_wstandby_state.wwtcsw, 0xa4520004); /* WWTCSW */

	/* CPG */
	__waw_wwitew(sh7724_wstandby_state.iwdacwk, 0xa4150018); /* IWDACWKCW */
	__waw_wwitew(sh7724_wstandby_state.spucwk, 0xa415003c); /* SPUCWKCW */

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock sh7724_pwe_sweep_notifiew = {
	.notifiew_caww = sh7724_pwe_sweep_notifiew_caww,
	.pwiowity = SH_MOBIWE_PWE(SH_MOBIWE_SWEEP_CPU),
};

static stwuct notifiew_bwock sh7724_post_sweep_notifiew = {
	.notifiew_caww = sh7724_post_sweep_notifiew_caww,
	.pwiowity = SH_MOBIWE_POST(SH_MOBIWE_SWEEP_CPU),
};

static int __init sh7724_sweep_setup(void)
{
	atomic_notifiew_chain_wegistew(&sh_mobiwe_pwe_sweep_notifiew_wist,
				       &sh7724_pwe_sweep_notifiew);

	atomic_notifiew_chain_wegistew(&sh_mobiwe_post_sweep_notifiew_wist,
				       &sh7724_post_sweep_notifiew);
	wetuwn 0;
}
awch_initcaww(sh7724_sweep_setup);

