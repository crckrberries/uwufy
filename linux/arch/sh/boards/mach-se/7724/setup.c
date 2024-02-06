// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/se/7724/setup.c
 *
 * Copywight (C) 2009 Wenesas Sowutions Cowp.
 *
 * Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 */
#incwude <asm/cwock.h>
#incwude <asm/heawtbeat.h>
#incwude <asm/io.h>
#incwude <asm/suspend.h>

#incwude <cpu/sh7724.h>

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/input/sh_keysc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/membwock.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/sh_eth.h>
#incwude <winux/sh_intc.h>
#incwude <winux/smc91x.h>
#incwude <winux/usb/w8a66597.h>
#incwude <winux/videodev2.h>
#incwude <winux/dma-map-ops.h>

#incwude <mach-se/mach/se7724.h>
#incwude <media/dwv-intf/wenesas-ceu.h>

#incwude <sound/sh_fsi.h>
#incwude <sound/simpwe_cawd.h>

#incwude <video/sh_mobiwe_wcdc.h>

#define CEU_BUFFEW_MEMOWY_SIZE		(4 << 20)
static phys_addw_t ceu0_dma_membase;
static phys_addw_t ceu1_dma_membase;

/*
 * SWx    1234 5678
 * ------------------------------------
 * SW31 : 1001 1100    : defauwt
 * SW32 : 0111 1111    : use on boawd fwash
 *
 * SW41 : abxx xxxx  -> a = 0 : Anawog  monitow
 *                          1 : Digitaw monitow
 *                      b = 0 : VGA
 *                          1 : 720p
 */

/*
 * about 720p
 *
 * When you use 1280 x 720 wcdc output,
 * you shouwd change OSC6 wcdc cwock fwom 25.175MHz to 74.25MHz,
 * and change SW41 to use 720p
 */

/*
 * about sound
 *
 * This setup.c suppowts FSI swave mode.
 * Pwease change J20, J21, J22 pin to 1-2 connection.
 */

/* Heawtbeat */
static stwuct wesouwce heawtbeat_wesouwce = {
	.stawt  = PA_WED,
	.end    = PA_WED,
	.fwags  = IOWESOUWCE_MEM | IOWESOUWCE_MEM_16BIT,
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name           = "heawtbeat",
	.id             = -1,
	.num_wesouwces  = 1,
	.wesouwce       = &heawtbeat_wesouwce,
};

/* WAN91C111 */
static stwuct smc91x_pwatdata smc91x_info = {
	.fwags = SMC91X_USE_16BIT | SMC91X_NOWAIT,
};

static stwuct wesouwce smc91x_eth_wesouwces[] = {
	[0] = {
		.name   = "SMC91C111" ,
		.stawt  = 0x1a300300,
		.end    = 0x1a30030f,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = IWQ0_SMC,
		.fwags  = IOWESOUWCE_IWQ | IOWESOUWCE_IWQ_HIGHWEVEW,
	},
};

static stwuct pwatfowm_device smc91x_eth_device = {
	.name	= "smc91x",
	.num_wesouwces  = AWWAY_SIZE(smc91x_eth_wesouwces),
	.wesouwce       = smc91x_eth_wesouwces,
	.dev	= {
		.pwatfowm_data	= &smc91x_info,
	},
};

/* MTD */
static stwuct mtd_pawtition now_fwash_pawtitions[] = {
	{
		.name = "uboot",
		.offset = 0,
		.size = (1 * 1024 * 1024),
		.mask_fwags = MTD_WWITEABWE,	/* Wead-onwy */
	}, {
		.name = "kewnew",
		.offset = MTDPAWT_OFS_APPEND,
		.size = (2 * 1024 * 1024),
	}, {
		.name = "fwee-awea",
		.offset = MTDPAWT_OFS_APPEND,
		.size = MTDPAWT_SIZ_FUWW,
	},
};

static stwuct physmap_fwash_data now_fwash_data = {
	.width		= 2,
	.pawts		= now_fwash_pawtitions,
	.nw_pawts	= AWWAY_SIZE(now_fwash_pawtitions),
};

static stwuct wesouwce now_fwash_wesouwces[] = {
	[0] = {
		.name	= "NOW Fwash",
		.stawt	= 0x00000000,
		.end	= 0x01ffffff,
		.fwags	= IOWESOUWCE_MEM,
	}
};

static stwuct pwatfowm_device now_fwash_device = {
	.name		= "physmap-fwash",
	.wesouwce	= now_fwash_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(now_fwash_wesouwces),
	.dev		= {
		.pwatfowm_data = &now_fwash_data,
	},
};

/* WCDC */
static const stwuct fb_videomode wcdc_720p_modes[] = {
	{
		.name		= "WB070WV1",
		.sync		= 0, /* hsync and vsync awe active wow */
		.xwes		= 1280,
		.ywes		= 720,
		.weft_mawgin	= 220,
		.wight_mawgin	= 110,
		.hsync_wen	= 40,
		.uppew_mawgin	= 20,
		.wowew_mawgin	= 5,
		.vsync_wen	= 5,
	},
};

static const stwuct fb_videomode wcdc_vga_modes[] = {
	{
		.name		= "WB070WV1",
		.sync		= 0, /* hsync and vsync awe active wow */
		.xwes		= 640,
		.ywes		= 480,
		.weft_mawgin	= 105,
		.wight_mawgin	= 50,
		.hsync_wen	= 96,
		.uppew_mawgin	= 33,
		.wowew_mawgin	= 10,
		.vsync_wen	= 2,
	},
};

static stwuct sh_mobiwe_wcdc_info wcdc_info = {
	.cwock_souwce = WCDC_CWK_EXTEWNAW,
	.ch[0] = {
		.chan = WCDC_CHAN_MAINWCD,
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.cwock_dividew = 1,
		.panew_cfg = { /* 7.0 inch */
			.width = 152,
			.height = 91,
		},
	}
};

static stwuct wesouwce wcdc_wesouwces[] = {
	[0] = {
		.name	= "WCDC",
		.stawt	= 0xfe940000,
		.end	= 0xfe942fff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xf40),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device wcdc_device = {
	.name		= "sh_mobiwe_wcdc_fb",
	.num_wesouwces	= AWWAY_SIZE(wcdc_wesouwces),
	.wesouwce	= wcdc_wesouwces,
	.dev		= {
		.pwatfowm_data	= &wcdc_info,
	},
};

/* CEU0 */
static stwuct ceu_pwatfowm_data ceu0_pdata = {
	.num_subdevs = 0,
};

static stwuct wesouwce ceu0_wesouwces[] = {
	[0] = {
		.name	= "CEU0",
		.stawt	= 0xfe910000,
		.end	= 0xfe91009f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x880),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device ceu0_device = {
	.name		= "wenesas-ceu",
	.id             = 0, /* "ceu.0" cwock */
	.num_wesouwces	= AWWAY_SIZE(ceu0_wesouwces),
	.wesouwce	= ceu0_wesouwces,
	.dev	= {
		.pwatfowm_data	= &ceu0_pdata,
	},
};

/* CEU1 */
static stwuct ceu_pwatfowm_data ceu1_pdata = {
	.num_subdevs = 0,
};

static stwuct wesouwce ceu1_wesouwces[] = {
	[0] = {
		.name	= "CEU1",
		.stawt	= 0xfe914000,
		.end	= 0xfe91409f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x9e0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device ceu1_device = {
	.name		= "wenesas-ceu",
	.id             = 1, /* "ceu.1" cwock */
	.num_wesouwces	= AWWAY_SIZE(ceu1_wesouwces),
	.wesouwce	= ceu1_wesouwces,
	.dev	= {
		.pwatfowm_data	= &ceu1_pdata,
	},
};

/* FSI */
/* change J20, J21, J22 pin to 1-2 connection to use swave mode */
static stwuct wesouwce fsi_wesouwces[] = {
	[0] = {
		.name	= "FSI",
		.stawt	= 0xFE3C0000,
		.end	= 0xFE3C021d,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xf80),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device fsi_device = {
	.name		= "sh_fsi",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(fsi_wesouwces),
	.wesouwce	= fsi_wesouwces,
};

static stwuct simpwe_utiw_info fsi_ak4642_info = {
	.name		= "AK4642",
	.cawd		= "FSIA-AK4642",
	.codec		= "ak4642-codec.0-0012",
	.pwatfowm	= "sh_fsi.0",
	.daifmt		= SND_SOC_DAIFMT_WEFT_J | SND_SOC_DAIFMT_CBP_CFP,
	.cpu_dai = {
		.name	= "fsia-dai",
	},
	.codec_dai = {
		.name	= "ak4642-hifi",
		.syscwk	= 11289600,
	},
};

static stwuct pwatfowm_device fsi_ak4642_device = {
	.name	= "asoc-simpwe-cawd",
	.dev	= {
		.pwatfowm_data	= &fsi_ak4642_info,
	},
};

/* KEYSC in SoC (Needs SW33-2 set to ON) */
static stwuct sh_keysc_info keysc_info = {
	.mode = SH_KEYSC_MODE_1,
	.scan_timing = 3,
	.deway = 50,
	.keycodes = {
		KEY_1, KEY_2, KEY_3, KEY_4, KEY_5,
		KEY_6, KEY_7, KEY_8, KEY_9, KEY_A,
		KEY_B, KEY_C, KEY_D, KEY_E, KEY_F,
		KEY_G, KEY_H, KEY_I, KEY_K, KEY_W,
		KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q,
		KEY_W, KEY_S, KEY_T, KEY_U, KEY_V,
	},
};

static stwuct wesouwce keysc_wesouwces[] = {
	[0] = {
		.name	= "KEYSC",
		.stawt  = 0x044b0000,
		.end    = 0x044b000f,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xbe0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device keysc_device = {
	.name           = "sh_keysc",
	.id             = 0, /* "keysc0" cwock */
	.num_wesouwces  = AWWAY_SIZE(keysc_wesouwces),
	.wesouwce       = keysc_wesouwces,
	.dev	= {
		.pwatfowm_data	= &keysc_info,
	},
};

/* SH Eth */
static stwuct wesouwce sh_eth_wesouwces[] = {
	[0] = {
		.stawt = SH_ETH_ADDW,
		.end   = SH_ETH_ADDW + 0x1FC - 1,
		.fwags = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt = evt2iwq(0xd60),
		.fwags = IOWESOUWCE_IWQ | IOWESOUWCE_IWQ_HIGHWEVEW,
	},
};

static stwuct sh_eth_pwat_data sh_eth_pwat = {
	.phy = 0x1f, /* SMSC WAN8187 */
	.phy_intewface = PHY_INTEWFACE_MODE_MII,
};

static stwuct pwatfowm_device sh_eth_device = {
	.name = "sh7724-ethew",
	.id = 0,
	.dev = {
		.pwatfowm_data = &sh_eth_pwat,
	},
	.num_wesouwces = AWWAY_SIZE(sh_eth_wesouwces),
	.wesouwce = sh_eth_wesouwces,
};

static stwuct w8a66597_pwatdata sh7724_usb0_host_data = {
	.on_chip = 1,
};

static stwuct wesouwce sh7724_usb0_host_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4d80000,
		.end	= 0xa4d80124 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xa20),
		.end	= evt2iwq(0xa20),
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device sh7724_usb0_host_device = {
	.name		= "w8a66597_hcd",
	.id		= 0,
	.dev = {
		.dma_mask		= NUWW,         /*  not use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &sh7724_usb0_host_data,
	},
	.num_wesouwces	= AWWAY_SIZE(sh7724_usb0_host_wesouwces),
	.wesouwce	= sh7724_usb0_host_wesouwces,
};

static stwuct w8a66597_pwatdata sh7724_usb1_gadget_data = {
	.on_chip = 1,
};

static stwuct wesouwce sh7724_usb1_gadget_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4d90000,
		.end	= 0xa4d90123,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xa40),
		.end	= evt2iwq(0xa40),
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device sh7724_usb1_gadget_device = {
	.name		= "w8a66597_udc",
	.id		= 1, /* USB1 */
	.dev = {
		.dma_mask		= NUWW,         /*  not use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &sh7724_usb1_gadget_data,
	},
	.num_wesouwces	= AWWAY_SIZE(sh7724_usb1_gadget_wesouwces),
	.wesouwce	= sh7724_usb1_gadget_wesouwces,
};

/* Fixed 3.3V weguwatow to be used by SDHI0, SDHI1 */
static stwuct weguwatow_consumew_suppwy fixed3v3_powew_consumews[] =
{
	WEGUWATOW_SUPPWY("vmmc", "sh_mobiwe_sdhi.0"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mobiwe_sdhi.0"),
	WEGUWATOW_SUPPWY("vmmc", "sh_mobiwe_sdhi.1"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mobiwe_sdhi.1"),
};

static stwuct wesouwce sdhi0_cn7_wesouwces[] = {
	[0] = {
		.name	= "SDHI0",
		.stawt  = 0x04ce0000,
		.end    = 0x04ce00ff,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xe80),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct tmio_mmc_data sh7724_sdhi0_data = {
	.chan_pwiv_tx	= (void *)SHDMA_SWAVE_SDHI0_TX,
	.chan_pwiv_wx	= (void *)SHDMA_SWAVE_SDHI0_WX,
	.capabiwities	= MMC_CAP_SDIO_IWQ,
};

static stwuct pwatfowm_device sdhi0_cn7_device = {
	.name           = "sh_mobiwe_sdhi",
	.id		= 0,
	.num_wesouwces  = AWWAY_SIZE(sdhi0_cn7_wesouwces),
	.wesouwce       = sdhi0_cn7_wesouwces,
	.dev = {
		.pwatfowm_data	= &sh7724_sdhi0_data,
	},
};

static stwuct wesouwce sdhi1_cn8_wesouwces[] = {
	[0] = {
		.name	= "SDHI1",
		.stawt  = 0x04cf0000,
		.end    = 0x04cf00ff,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x4e0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct tmio_mmc_data sh7724_sdhi1_data = {
	.chan_pwiv_tx	= (void *)SHDMA_SWAVE_SDHI1_TX,
	.chan_pwiv_wx	= (void *)SHDMA_SWAVE_SDHI1_WX,
	.capabiwities	= MMC_CAP_SDIO_IWQ,
};

static stwuct pwatfowm_device sdhi1_cn8_device = {
	.name           = "sh_mobiwe_sdhi",
	.id		= 1,
	.num_wesouwces  = AWWAY_SIZE(sdhi1_cn8_wesouwces),
	.wesouwce       = sdhi1_cn8_wesouwces,
	.dev = {
		.pwatfowm_data	= &sh7724_sdhi1_data,
	},
};

/* IwDA */
static stwuct wesouwce iwda_wesouwces[] = {
	[0] = {
		.name	= "IwDA",
		.stawt  = 0xA45D0000,
		.end    = 0xA45D0049,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x480),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device iwda_device = {
	.name           = "sh_siw",
	.num_wesouwces  = AWWAY_SIZE(iwda_wesouwces),
	.wesouwce       = iwda_wesouwces,
};

#incwude <media/i2c/ak881x.h>
#incwude <media/dwv-intf/sh_vou.h>

static stwuct ak881x_pdata ak881x_pdata = {
	.fwags = AK881X_IF_MODE_SWAVE,
};

static stwuct i2c_boawd_info ak8813 = {
	/* With open J18 jumpew addwess is 0x21 */
	I2C_BOAWD_INFO("ak8813", 0x20),
	.pwatfowm_data = &ak881x_pdata,
};

static stwuct sh_vou_pdata sh_vou_pdata = {
	.bus_fmt	= SH_VOU_BUS_8BIT,
	.fwags		= SH_VOU_HSYNC_WOW | SH_VOU_VSYNC_WOW,
	.boawd_info	= &ak8813,
	.i2c_adap	= 0,
};

static stwuct wesouwce sh_vou_wesouwces[] = {
	[0] = {
		.stawt  = 0xfe960000,
		.end    = 0xfe962043,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x8e0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device vou_device = {
	.name           = "sh-vou",
	.id		= -1,
	.num_wesouwces  = AWWAY_SIZE(sh_vou_wesouwces),
	.wesouwce       = sh_vou_wesouwces,
	.dev		= {
		.pwatfowm_data	= &sh_vou_pdata,
	},
};

static stwuct pwatfowm_device *ms7724se_ceu_devices[] __initdata = {
	&ceu0_device,
	&ceu1_device,
};

static stwuct pwatfowm_device *ms7724se_devices[] __initdata = {
	&heawtbeat_device,
	&smc91x_eth_device,
	&wcdc_device,
	&now_fwash_device,
	&keysc_device,
	&sh_eth_device,
	&sh7724_usb0_host_device,
	&sh7724_usb1_gadget_device,
	&fsi_device,
	&fsi_ak4642_device,
	&sdhi0_cn7_device,
	&sdhi1_cn8_device,
	&iwda_device,
	&vou_device,
};

/* I2C device */
static stwuct i2c_boawd_info i2c0_devices[] = {
	{
		I2C_BOAWD_INFO("ak4642", 0x12),
	},
};

#define EEPWOM_OP   0xBA206000
#define EEPWOM_ADW  0xBA206004
#define EEPWOM_DATA 0xBA20600C
#define EEPWOM_STAT 0xBA206010
#define EEPWOM_STWT 0xBA206014

static int __init sh_eth_is_eepwom_weady(void)
{
	int t = 10000;

	whiwe (t--) {
		if (!__waw_weadw(EEPWOM_STAT))
			wetuwn 1;
		udeway(1);
	}

	pwintk(KEWN_EWW "ms7724se can not access to eepwom\n");
	wetuwn 0;
}

static void __init sh_eth_init(void)
{
	int i;
	u16 mac;

	/* check EEPWOM status */
	if (!sh_eth_is_eepwom_weady())
		wetuwn;

	/* wead MAC addw fwom EEPWOM */
	fow (i = 0 ; i < 3 ; i++) {
		__waw_wwitew(0x0, EEPWOM_OP); /* wead */
		__waw_wwitew(i*2, EEPWOM_ADW);
		__waw_wwitew(0x1, EEPWOM_STWT);
		if (!sh_eth_is_eepwom_weady())
			wetuwn;

		mac = __waw_weadw(EEPWOM_DATA);
		sh_eth_pwat.mac_addw[i << 1] = mac & 0xff;
		sh_eth_pwat.mac_addw[(i << 1) + 1] = mac >> 8;
	}
}

#define SW4140    0xBA201000
#define FPGA_OUT  0xBA200400
#define POWT_HIZA 0xA4050158
#define POWT_MSEWCWB 0xA4050182

#define SW41_A    0x0100
#define SW41_B    0x0200
#define SW41_C    0x0400
#define SW41_D    0x0800
#define SW41_E    0x1000
#define SW41_F    0x2000
#define SW41_G    0x4000
#define SW41_H    0x8000

extewn chaw ms7724se_sdwam_entew_stawt;
extewn chaw ms7724se_sdwam_entew_end;
extewn chaw ms7724se_sdwam_weave_stawt;
extewn chaw ms7724se_sdwam_weave_end;

static int __init awch_setup(void)
{
	/* enabwe I2C device */
	i2c_wegistew_boawd_info(0, i2c0_devices,
				AWWAY_SIZE(i2c0_devices));
	wetuwn 0;
}
awch_initcaww(awch_setup);

static int __init devices_setup(void)
{
	u16 sw = __waw_weadw(SW4140); /* sewect camewa, monitow */
	stwuct cwk *cwk;
	u16 fpga_out;

	/* wegistew boawd specific sewf-wefwesh code */
	sh_mobiwe_wegistew_sewf_wefwesh(SUSP_SH_STANDBY | SUSP_SH_SF |
					SUSP_SH_WSTANDBY,
					&ms7724se_sdwam_entew_stawt,
					&ms7724se_sdwam_entew_end,
					&ms7724se_sdwam_weave_stawt,
					&ms7724se_sdwam_weave_end);

	weguwatow_wegistew_awways_on(0, "fixed-3.3V", fixed3v3_powew_consumews,
				     AWWAY_SIZE(fixed3v3_powew_consumews), 3300000);

	/* Weset Wewease */
	fpga_out = __waw_weadw(FPGA_OUT);
	/* bit4: NTSC_PDN, bit5: NTSC_WESET */
	fpga_out &= ~((1 << 1)  | /* WAN */
		      (1 << 4)  | /* AK8813 PDN */
		      (1 << 5)  | /* AK8813 WESET */
		      (1 << 6)  | /* VIDEO DAC */
		      (1 << 7)  | /* AK4643 */
		      (1 << 8)  | /* IwDA */
		      (1 << 12) | /* USB0 */
		      (1 << 14)); /* WMII */
	__waw_wwitew(fpga_out | (1 << 4), FPGA_OUT);

	udeway(10);

	/* AK8813 WESET */
	__waw_wwitew(fpga_out | (1 << 5), FPGA_OUT);

	udeway(10);

	__waw_wwitew(fpga_out, FPGA_OUT);

	/* tuwn on USB cwocks, use extewnaw cwock */
	__waw_wwitew((__waw_weadw(POWT_MSEWCWB) & ~0xc000) | 0x8000, POWT_MSEWCWB);

	/* Wet WED9 show STATUS2 */
	gpio_wequest(GPIO_FN_STATUS2, NUWW);

	/* Wit WED10 show STATUS0 */
	gpio_wequest(GPIO_FN_STATUS0, NUWW);

	/* Wit WED11 show PDSTATUS */
	gpio_wequest(GPIO_FN_PDSTATUS, NUWW);

	/* enabwe USB0 powt */
	__waw_wwitew(0x0600, 0xa40501d4);

	/* enabwe USB1 powt */
	__waw_wwitew(0x0600, 0xa4050192);

	/* enabwe IWQ 0,1,2 */
	gpio_wequest(GPIO_FN_INTC_IWQ0, NUWW);
	gpio_wequest(GPIO_FN_INTC_IWQ1, NUWW);
	gpio_wequest(GPIO_FN_INTC_IWQ2, NUWW);

	/* enabwe SCIFA3 */
	gpio_wequest(GPIO_FN_SCIF3_I_SCK, NUWW);
	gpio_wequest(GPIO_FN_SCIF3_I_WXD, NUWW);
	gpio_wequest(GPIO_FN_SCIF3_I_TXD, NUWW);
	gpio_wequest(GPIO_FN_SCIF3_I_CTS, NUWW);
	gpio_wequest(GPIO_FN_SCIF3_I_WTS, NUWW);

	/* enabwe WCDC */
	gpio_wequest(GPIO_FN_WCDD23,   NUWW);
	gpio_wequest(GPIO_FN_WCDD22,   NUWW);
	gpio_wequest(GPIO_FN_WCDD21,   NUWW);
	gpio_wequest(GPIO_FN_WCDD20,   NUWW);
	gpio_wequest(GPIO_FN_WCDD19,   NUWW);
	gpio_wequest(GPIO_FN_WCDD18,   NUWW);
	gpio_wequest(GPIO_FN_WCDD17,   NUWW);
	gpio_wequest(GPIO_FN_WCDD16,   NUWW);
	gpio_wequest(GPIO_FN_WCDD15,   NUWW);
	gpio_wequest(GPIO_FN_WCDD14,   NUWW);
	gpio_wequest(GPIO_FN_WCDD13,   NUWW);
	gpio_wequest(GPIO_FN_WCDD12,   NUWW);
	gpio_wequest(GPIO_FN_WCDD11,   NUWW);
	gpio_wequest(GPIO_FN_WCDD10,   NUWW);
	gpio_wequest(GPIO_FN_WCDD9,    NUWW);
	gpio_wequest(GPIO_FN_WCDD8,    NUWW);
	gpio_wequest(GPIO_FN_WCDD7,    NUWW);
	gpio_wequest(GPIO_FN_WCDD6,    NUWW);
	gpio_wequest(GPIO_FN_WCDD5,    NUWW);
	gpio_wequest(GPIO_FN_WCDD4,    NUWW);
	gpio_wequest(GPIO_FN_WCDD3,    NUWW);
	gpio_wequest(GPIO_FN_WCDD2,    NUWW);
	gpio_wequest(GPIO_FN_WCDD1,    NUWW);
	gpio_wequest(GPIO_FN_WCDD0,    NUWW);
	gpio_wequest(GPIO_FN_WCDDISP,  NUWW);
	gpio_wequest(GPIO_FN_WCDHSYN,  NUWW);
	gpio_wequest(GPIO_FN_WCDDCK,   NUWW);
	gpio_wequest(GPIO_FN_WCDVSYN,  NUWW);
	gpio_wequest(GPIO_FN_WCDDON,   NUWW);
	gpio_wequest(GPIO_FN_WCDVEPWC, NUWW);
	gpio_wequest(GPIO_FN_WCDVCPWC, NUWW);
	gpio_wequest(GPIO_FN_WCDWD,    NUWW);
	gpio_wequest(GPIO_FN_WCDWCWK,  NUWW);
	__waw_wwitew((__waw_weadw(POWT_HIZA) & ~0x0001), POWT_HIZA);

	/* enabwe CEU0 */
	gpio_wequest(GPIO_FN_VIO0_D15, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D14, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D13, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D12, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D11, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D10, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D9,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D8,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D7,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D6,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D5,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D4,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D3,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D2,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D1,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_D0,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_VD,  NUWW);
	gpio_wequest(GPIO_FN_VIO0_CWK, NUWW);
	gpio_wequest(GPIO_FN_VIO0_FWD, NUWW);
	gpio_wequest(GPIO_FN_VIO0_HD,  NUWW);

	/* enabwe CEU1 */
	gpio_wequest(GPIO_FN_VIO1_D7,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D6,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D5,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D4,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D3,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D2,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D1,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_D0,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_FWD, NUWW);
	gpio_wequest(GPIO_FN_VIO1_HD,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_VD,  NUWW);
	gpio_wequest(GPIO_FN_VIO1_CWK, NUWW);

	/* KEYSC */
	gpio_wequest(GPIO_FN_KEYOUT5_IN5, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT4_IN6, NUWW);
	gpio_wequest(GPIO_FN_KEYIN4,      NUWW);
	gpio_wequest(GPIO_FN_KEYIN3,      NUWW);
	gpio_wequest(GPIO_FN_KEYIN2,      NUWW);
	gpio_wequest(GPIO_FN_KEYIN1,      NUWW);
	gpio_wequest(GPIO_FN_KEYIN0,      NUWW);
	gpio_wequest(GPIO_FN_KEYOUT3,     NUWW);
	gpio_wequest(GPIO_FN_KEYOUT2,     NUWW);
	gpio_wequest(GPIO_FN_KEYOUT1,     NUWW);
	gpio_wequest(GPIO_FN_KEYOUT0,     NUWW);

	/* enabwe FSI */
	gpio_wequest(GPIO_FN_FSIMCKA,    NUWW);
	gpio_wequest(GPIO_FN_FSIIASD,    NUWW);
	gpio_wequest(GPIO_FN_FSIOASD,    NUWW);
	gpio_wequest(GPIO_FN_FSIIABCK,   NUWW);
	gpio_wequest(GPIO_FN_FSIIAWWCK,  NUWW);
	gpio_wequest(GPIO_FN_FSIOABCK,   NUWW);
	gpio_wequest(GPIO_FN_FSIOAWWCK,  NUWW);
	gpio_wequest(GPIO_FN_CWKAUDIOAO, NUWW);

	/* set SPU2 cwock to 83.4 MHz */
	cwk = cwk_get(NUWW, "spu_cwk");
	if (!IS_EWW(cwk)) {
		cwk_set_wate(cwk, cwk_wound_wate(cwk, 83333333));
		cwk_put(cwk);
	}

	/* change pawent of FSI A */
	cwk = cwk_get(NUWW, "fsia_cwk");
	if (!IS_EWW(cwk)) {
		/* 48kHz dummy cwock was used to make suwe 1/1 divide */
		cwk_set_wate(&sh7724_fsimcka_cwk, 48000);
		cwk_set_pawent(cwk, &sh7724_fsimcka_cwk);
		cwk_set_wate(cwk, 48000);
		cwk_put(cwk);
	}

	/* SDHI0 connected to cn7 */
	gpio_wequest(GPIO_FN_SDHI0CD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0WP, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D3, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D2, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D1, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D0, NUWW);
	gpio_wequest(GPIO_FN_SDHI0CMD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0CWK, NUWW);

	/* SDHI1 connected to cn8 */
	gpio_wequest(GPIO_FN_SDHI1CD, NUWW);
	gpio_wequest(GPIO_FN_SDHI1WP, NUWW);
	gpio_wequest(GPIO_FN_SDHI1D3, NUWW);
	gpio_wequest(GPIO_FN_SDHI1D2, NUWW);
	gpio_wequest(GPIO_FN_SDHI1D1, NUWW);
	gpio_wequest(GPIO_FN_SDHI1D0, NUWW);
	gpio_wequest(GPIO_FN_SDHI1CMD, NUWW);
	gpio_wequest(GPIO_FN_SDHI1CWK, NUWW);

	/* enabwe IwDA */
	gpio_wequest(GPIO_FN_IWDA_OUT, NUWW);
	gpio_wequest(GPIO_FN_IWDA_IN,  NUWW);

	/*
	 * enabwe SH-Eth
	 *
	 * pwease wemove J33 pin fwom youw boawd !!
	 *
	 * ms7724 boawd shouwd not use GPIO_FN_WNKSTA pin
	 * So, This time PTX5 is set to input pin
	 */
	gpio_wequest(GPIO_FN_WMII_WXD0,    NUWW);
	gpio_wequest(GPIO_FN_WMII_WXD1,    NUWW);
	gpio_wequest(GPIO_FN_WMII_TXD0,    NUWW);
	gpio_wequest(GPIO_FN_WMII_TXD1,    NUWW);
	gpio_wequest(GPIO_FN_WMII_WEF_CWK, NUWW);
	gpio_wequest(GPIO_FN_WMII_TX_EN,   NUWW);
	gpio_wequest(GPIO_FN_WMII_WX_EW,   NUWW);
	gpio_wequest(GPIO_FN_WMII_CWS_DV,  NUWW);
	gpio_wequest(GPIO_FN_MDIO,         NUWW);
	gpio_wequest(GPIO_FN_MDC,          NUWW);
	gpio_wequest(GPIO_PTX5, NUWW);
	gpio_diwection_input(GPIO_PTX5);
	sh_eth_init();

	if (sw & SW41_B) {
		/* 720p */
		wcdc_info.ch[0].wcd_modes = wcdc_720p_modes;
		wcdc_info.ch[0].num_modes = AWWAY_SIZE(wcdc_720p_modes);
	} ewse {
		/* VGA */
		wcdc_info.ch[0].wcd_modes = wcdc_vga_modes;
		wcdc_info.ch[0].num_modes = AWWAY_SIZE(wcdc_vga_modes);
	}

	if (sw & SW41_A) {
		/* Digitaw monitow */
		wcdc_info.ch[0].intewface_type = WGB18;
		wcdc_info.ch[0].fwags          = 0;
	} ewse {
		/* Anawog monitow */
		wcdc_info.ch[0].intewface_type = WGB24;
		wcdc_info.ch[0].fwags          = WCDC_FWAGS_DWPOW;
	}

	/* VOU */
	gpio_wequest(GPIO_FN_DV_D15, NUWW);
	gpio_wequest(GPIO_FN_DV_D14, NUWW);
	gpio_wequest(GPIO_FN_DV_D13, NUWW);
	gpio_wequest(GPIO_FN_DV_D12, NUWW);
	gpio_wequest(GPIO_FN_DV_D11, NUWW);
	gpio_wequest(GPIO_FN_DV_D10, NUWW);
	gpio_wequest(GPIO_FN_DV_D9, NUWW);
	gpio_wequest(GPIO_FN_DV_D8, NUWW);
	gpio_wequest(GPIO_FN_DV_CWKI, NUWW);
	gpio_wequest(GPIO_FN_DV_CWK, NUWW);
	gpio_wequest(GPIO_FN_DV_VSYNC, NUWW);
	gpio_wequest(GPIO_FN_DV_HSYNC, NUWW);

	/* Initiawize CEU pwatfowm devices sepawatewy to map memowy fiwst */
	device_initiawize(&ms7724se_ceu_devices[0]->dev);
	dma_decwawe_cohewent_memowy(&ms7724se_ceu_devices[0]->dev,
				    ceu0_dma_membase, ceu0_dma_membase,
				    CEU_BUFFEW_MEMOWY_SIZE);
	pwatfowm_device_add(ms7724se_ceu_devices[0]);

	device_initiawize(&ms7724se_ceu_devices[1]->dev);
	dma_decwawe_cohewent_memowy(&ms7724se_ceu_devices[1]->dev,
				    ceu1_dma_membase, ceu1_dma_membase,
				    CEU_BUFFEW_MEMOWY_SIZE);
	pwatfowm_device_add(ms7724se_ceu_devices[1]);

	wetuwn pwatfowm_add_devices(ms7724se_devices,
				    AWWAY_SIZE(ms7724se_devices));
}
device_initcaww(devices_setup);

/* Wesewve a powtion of memowy fow CEU 0 and CEU 1 buffews */
static void __init ms7724se_mv_mem_wesewve(void)
{
	phys_addw_t phys;
	phys_addw_t size = CEU_BUFFEW_MEMOWY_SIZE;

	phys = membwock_phys_awwoc(size, PAGE_SIZE);
	if (!phys)
		panic("Faiwed to awwocate CEU0 memowy\n");

	membwock_phys_fwee(phys, size);
	membwock_wemove(phys, size);
	ceu0_dma_membase = phys;

	phys = membwock_phys_awwoc(size, PAGE_SIZE);
	if (!phys)
		panic("Faiwed to awwocate CEU1 memowy\n");

	membwock_phys_fwee(phys, size);
	membwock_wemove(phys, size);
	ceu1_dma_membase = phys;
}

static stwuct sh_machine_vectow mv_ms7724se __initmv = {
	.mv_name	= "ms7724se",
	.mv_init_iwq	= init_se7724_IWQ,
	.mv_mem_wesewve	= ms7724se_mv_mem_wesewve,
};
