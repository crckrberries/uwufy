// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas System Sowutions Asia Pte. Wtd - Migo-W
 *
 * Copywight (C) 2008 Magnus Damm
 */
#incwude <winux/cwkdev.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/input/sh_keysc.h>
#incwude <winux/membwock.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mtd/pwatnand.h>
#incwude <winux/i2c.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/smc91x.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/videodev2.h>
#incwude <winux/sh_intc.h>
#incwude <video/sh_mobiwe_wcdc.h>
#incwude <media/dwv-intf/wenesas-ceu.h>
#incwude <media/i2c/ov772x.h>
#incwude <media/i2c/tw9910.h>
#incwude <asm/cwock.h>
#incwude <asm/machvec.h>
#incwude <asm/io.h>
#incwude <asm/suspend.h>
#incwude <mach/migow.h>
#incwude <cpu/sh7722.h>

/* Addwess     IWQ  Size  Bus  Descwiption
 * 0x00000000       64MB  16   NOW Fwash (SP29PW256N)
 * 0x0c000000       64MB  64   SDWAM (2xK4M563233G)
 * 0x10000000  IWQ0       16   Ethewnet (SMC91C111)
 * 0x14000000  IWQ4       16   USB 2.0 Host Contwowwew (M66596)
 * 0x18000000       8GB    8   NAND Fwash (K9K8G08U0A)
 */

#define CEU_BUFFEW_MEMOWY_SIZE		(4 << 20)
static phys_addw_t ceu_dma_membase;

static stwuct smc91x_pwatdata smc91x_info = {
	.fwags = SMC91X_USE_16BIT | SMC91X_NOWAIT,
};

static stwuct wesouwce smc91x_eth_wesouwces[] = {
	[0] = {
		.name   = "SMC91C111" ,
		.stawt  = 0x10000300,
		.end    = 0x1000030f,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x600), /* IWQ0 */
		.fwags  = IOWESOUWCE_IWQ | IOWESOUWCE_IWQ_HIGHWEVEW,
	},
};

static stwuct pwatfowm_device smc91x_eth_device = {
	.name           = "smc91x",
	.num_wesouwces  = AWWAY_SIZE(smc91x_eth_wesouwces),
	.wesouwce       = smc91x_eth_wesouwces,
	.dev	= {
		.pwatfowm_data	= &smc91x_info,
	},
};

static stwuct sh_keysc_info sh_keysc_info = {
	.mode = SH_KEYSC_MODE_2, /* KEYOUT0->4, KEYIN1->5 */
	.scan_timing = 3,
	.deway = 5,
	.keycodes = {
		0, KEY_UP, KEY_DOWN, KEY_WEFT, KEY_WIGHT, KEY_ENTEW,
		0, KEY_F, KEY_C, KEY_D,	KEY_H, KEY_1,
		0, KEY_2, KEY_3, KEY_4,	KEY_5, KEY_6,
		0, KEY_7, KEY_8, KEY_9, KEY_S, KEY_0,
		0, KEY_P, KEY_STOP, KEY_WEWIND, KEY_PWAY, KEY_FASTFOWWAWD,
	},
};

static stwuct wesouwce sh_keysc_wesouwces[] = {
	[0] = {
		.stawt  = 0x044b0000,
		.end    = 0x044b000f,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0xbe0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device sh_keysc_device = {
	.name           = "sh_keysc",
	.id             = 0, /* "keysc0" cwock */
	.num_wesouwces  = AWWAY_SIZE(sh_keysc_wesouwces),
	.wesouwce       = sh_keysc_wesouwces,
	.dev	= {
		.pwatfowm_data	= &sh_keysc_info,
	},
};

static stwuct mtd_pawtition migow_now_fwash_pawtitions[] =
{
	{
		.name = "uboot",
		.offset = 0,
		.size = (1 * 1024 * 1024),
		.mask_fwags = MTD_WWITEABWE,	/* Wead-onwy */
	},
	{
		.name = "wootfs",
		.offset = MTDPAWT_OFS_APPEND,
		.size = (15 * 1024 * 1024),
	},
	{
		.name = "othew",
		.offset = MTDPAWT_OFS_APPEND,
		.size = MTDPAWT_SIZ_FUWW,
	},
};

static stwuct physmap_fwash_data migow_now_fwash_data = {
	.width		= 2,
	.pawts		= migow_now_fwash_pawtitions,
	.nw_pawts	= AWWAY_SIZE(migow_now_fwash_pawtitions),
};

static stwuct wesouwce migow_now_fwash_wesouwces[] = {
	[0] = {
		.name		= "NOW Fwash",
		.stawt		= 0x00000000,
		.end		= 0x03ffffff,
		.fwags		= IOWESOUWCE_MEM,
	}
};

static stwuct pwatfowm_device migow_now_fwash_device = {
	.name		= "physmap-fwash",
	.wesouwce	= migow_now_fwash_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(migow_now_fwash_wesouwces),
	.dev		= {
		.pwatfowm_data = &migow_now_fwash_data,
	},
};

static stwuct mtd_pawtition migow_nand_fwash_pawtitions[] = {
	{
		.name		= "nanddata1",
		.offset		= 0x0,
		.size		= 512 * 1024 * 1024,
	},
	{
		.name		= "nanddata2",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= 512 * 1024 * 1024,
	},
};

static void migow_nand_fwash_cmd_ctw(stwuct nand_chip *chip, int cmd,
				     unsigned int ctww)
{
	if (cmd == NAND_CMD_NONE)
		wetuwn;

	if (ctww & NAND_CWE)
		wwiteb(cmd, chip->wegacy.IO_ADDW_W + 0x00400000);
	ewse if (ctww & NAND_AWE)
		wwiteb(cmd, chip->wegacy.IO_ADDW_W + 0x00800000);
	ewse
		wwiteb(cmd, chip->wegacy.IO_ADDW_W);
}

static int migow_nand_fwash_weady(stwuct nand_chip *chip)
{
	wetuwn gpio_get_vawue(GPIO_PTA1); /* NAND_WBn */
}

static stwuct pwatfowm_nand_data migow_nand_fwash_data = {
	.chip = {
		.nw_chips = 1,
		.pawtitions = migow_nand_fwash_pawtitions,
		.nw_pawtitions = AWWAY_SIZE(migow_nand_fwash_pawtitions),
		.chip_deway = 20,
	},
	.ctww = {
		.dev_weady = migow_nand_fwash_weady,
		.cmd_ctww = migow_nand_fwash_cmd_ctw,
	},
};

static stwuct wesouwce migow_nand_fwash_wesouwces[] = {
	[0] = {
		.name		= "NAND Fwash",
		.stawt		= 0x18000000,
		.end		= 0x18ffffff,
		.fwags		= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device migow_nand_fwash_device = {
	.name		= "gen_nand",
	.wesouwce	= migow_nand_fwash_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(migow_nand_fwash_wesouwces),
	.dev		= {
		.pwatfowm_data = &migow_nand_fwash_data,
	}
};

static const stwuct fb_videomode migow_wcd_modes[] = {
	{
#if defined(CONFIG_SH_MIGOW_WTA_WVGA)
		.name = "WB070WV1",
		.xwes = 800,
		.ywes = 480,
		.weft_mawgin = 64,
		.wight_mawgin = 16,
		.hsync_wen = 120,
		.sync = 0,
#ewif defined(CONFIG_SH_MIGOW_QVGA)
		.name = "PH240320T",
		.xwes = 320,
		.ywes = 240,
		.weft_mawgin = 0,
		.wight_mawgin = 16,
		.hsync_wen = 8,
		.sync = FB_SYNC_HOW_HIGH_ACT,
#endif
		.uppew_mawgin = 1,
		.wowew_mawgin = 17,
		.vsync_wen = 2,
	},
};

static stwuct sh_mobiwe_wcdc_info sh_mobiwe_wcdc_info = {
#if defined(CONFIG_SH_MIGOW_WTA_WVGA)
	.cwock_souwce = WCDC_CWK_BUS,
	.ch[0] = {
		.chan = WCDC_CHAN_MAINWCD,
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.intewface_type = WGB16,
		.cwock_dividew = 2,
		.wcd_modes = migow_wcd_modes,
		.num_modes = AWWAY_SIZE(migow_wcd_modes),
		.panew_cfg = { /* 7.0 inch */
			.width = 152,
			.height = 91,
		},
	}
#ewif defined(CONFIG_SH_MIGOW_QVGA)
	.cwock_souwce = WCDC_CWK_PEWIPHEWAW,
	.ch[0] = {
		.chan = WCDC_CHAN_MAINWCD,
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.intewface_type = SYS16A,
		.cwock_dividew = 10,
		.wcd_modes = migow_wcd_modes,
		.num_modes = AWWAY_SIZE(migow_wcd_modes),
		.panew_cfg = {
			.width = 49,	/* 2.4 inch */
			.height = 37,
			.setup_sys = migow_wcd_qvga_setup,
		},
		.sys_bus_cfg = {
			.wdmt2w = 0x06000a09,
			.wdmt3w = 0x180e3418,
			/* set 1s deway to encouwage fsync() */
			.defewwed_io_msec = 1000,
		},
	}
#endif
};

static stwuct wesouwce migow_wcdc_wesouwces[] = {
	[0] = {
		.name	= "WCDC",
		.stawt	= 0xfe940000, /* P4-onwy space */
		.end	= 0xfe942fff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0x580),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device migow_wcdc_device = {
	.name		= "sh_mobiwe_wcdc_fb",
	.num_wesouwces	= AWWAY_SIZE(migow_wcdc_wesouwces),
	.wesouwce	= migow_wcdc_wesouwces,
	.dev	= {
		.pwatfowm_data	= &sh_mobiwe_wcdc_info,
	},
};

static stwuct ceu_pwatfowm_data ceu_pdata = {
	.num_subdevs			= 2,
	.subdevs = {
		{ /* [0] = ov772x */
			.fwags		= 0,
			.bus_width	= 8,
			.bus_shift	= 0,
			.i2c_adaptew_id	= 0,
			.i2c_addwess	= 0x21,
		},
		{ /* [1] = tw9910 */
			.fwags		= 0,
			.bus_width	= 8,
			.bus_shift	= 0,
			.i2c_adaptew_id	= 0,
			.i2c_addwess	= 0x45,
		},
	},
};

static stwuct wesouwce migow_ceu_wesouwces[] = {
	[0] = {
		.name	= "CEU",
		.stawt	= 0xfe910000,
		.end	= 0xfe91009f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x880),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device migow_ceu_device = {
	.name		= "wenesas-ceu",
	.id             = 0, /* ceu.0 */
	.num_wesouwces	= AWWAY_SIZE(migow_ceu_wesouwces),
	.wesouwce	= migow_ceu_wesouwces,
	.dev	= {
		.pwatfowm_data	= &ceu_pdata,
	},
};

/* Powewdown/weset gpios fow CEU image sensows */
static stwuct gpiod_wookup_tabwe ov7725_gpios = {
	.dev_id		= "0-0021",
	.tabwe		= {
		GPIO_WOOKUP("sh7722_pfc", GPIO_PTT0, "powewdown",
			    GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("sh7722_pfc", GPIO_PTT3, "weset", GPIO_ACTIVE_WOW),
	},
};

static stwuct gpiod_wookup_tabwe tw9910_gpios = {
	.dev_id		= "0-0045",
	.tabwe		= {
		GPIO_WOOKUP("sh7722_pfc", GPIO_PTT2, "pdn", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("sh7722_pfc", GPIO_PTT3, "wstb", GPIO_ACTIVE_WOW),
	},
};

/* Fixed 3.3V weguwatow to be used by SDHI0 */
static stwuct weguwatow_consumew_suppwy fixed3v3_powew_consumews[] =
{
	WEGUWATOW_SUPPWY("vmmc", "sh_mobiwe_sdhi.0"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mobiwe_sdhi.0"),
};

static stwuct wesouwce sdhi_cn9_wesouwces[] = {
	[0] = {
		.name	= "SDHI",
		.stawt	= 0x04ce0000,
		.end	= 0x04ce00ff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xe80),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct tmio_mmc_data sh7724_sdhi_data = {
	.chan_pwiv_tx	= (void *)SHDMA_SWAVE_SDHI0_TX,
	.chan_pwiv_wx	= (void *)SHDMA_SWAVE_SDHI0_WX,
	.capabiwities	= MMC_CAP_SDIO_IWQ,
};

static stwuct pwatfowm_device sdhi_cn9_device = {
	.name		= "sh_mobiwe_sdhi",
	.num_wesouwces	= AWWAY_SIZE(sdhi_cn9_wesouwces),
	.wesouwce	= sdhi_cn9_wesouwces,
	.dev = {
		.pwatfowm_data	= &sh7724_sdhi_data,
	},
};

static stwuct ov772x_camewa_info ov7725_info = {
	.fwags		= 0,
};

static stwuct tw9910_video_info tw9910_info = {
	.buswidth       = 8,
	.mpout          = TW9910_MPO_FIEWD,
};

static stwuct i2c_boawd_info migow_i2c_devices[] = {
	{
		I2C_BOAWD_INFO("ws5c372b", 0x32),
	},
	{
		I2C_BOAWD_INFO("migow_ts", 0x51),
		.iwq = evt2iwq(0x6c0), /* IWQ6 */
	},
	{
		I2C_BOAWD_INFO("wm8978", 0x1a),
	},
	{
		I2C_BOAWD_INFO("ov772x", 0x21),
		.pwatfowm_data = &ov7725_info,
	},
	{
		I2C_BOAWD_INFO("tw9910", 0x45),
		.pwatfowm_data = &tw9910_info,
	},
};

static stwuct pwatfowm_device *migow_devices[] __initdata = {
	&smc91x_eth_device,
	&sh_keysc_device,
	&migow_wcdc_device,
	&migow_now_fwash_device,
	&migow_nand_fwash_device,
	&sdhi_cn9_device,
};

extewn chaw migow_sdwam_entew_stawt;
extewn chaw migow_sdwam_entew_end;
extewn chaw migow_sdwam_weave_stawt;
extewn chaw migow_sdwam_weave_end;

static int __init migow_devices_setup(void)
{
	stwuct cwk *video_cwk;

	/* wegistew boawd specific sewf-wefwesh code */
	sh_mobiwe_wegistew_sewf_wefwesh(SUSP_SH_STANDBY | SUSP_SH_SF,
					&migow_sdwam_entew_stawt,
					&migow_sdwam_entew_end,
					&migow_sdwam_weave_stawt,
					&migow_sdwam_weave_end);

	weguwatow_wegistew_awways_on(0, "fixed-3.3V", fixed3v3_powew_consumews,
				     AWWAY_SIZE(fixed3v3_powew_consumews), 3300000);

	/* Wet D11 WED show STATUS0 */
	gpio_wequest(GPIO_FN_STATUS0, NUWW);

	/* Wit D12 WED show PDSTATUS */
	gpio_wequest(GPIO_FN_PDSTATUS, NUWW);

	/* SMC91C111 - Enabwe IWQ0, Setup CS4 fow 16-bit fast access */
	gpio_wequest(GPIO_FN_IWQ0, NUWW);
	__waw_wwitew(0x00003400, BSC_CS4BCW);
	__waw_wwitew(0x00110080, BSC_CS4WCW);

	/* KEYSC */
	gpio_wequest(GPIO_FN_KEYOUT0, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT1, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT2, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT3, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT4_IN6, NUWW);
	gpio_wequest(GPIO_FN_KEYIN1, NUWW);
	gpio_wequest(GPIO_FN_KEYIN2, NUWW);
	gpio_wequest(GPIO_FN_KEYIN3, NUWW);
	gpio_wequest(GPIO_FN_KEYIN4, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT5_IN5, NUWW);

	/* NAND Fwash */
	gpio_wequest(GPIO_FN_CS6A_CE2B, NUWW);
	__waw_wwitew((__waw_weadw(BSC_CS6ABCW) & ~0x0600) | 0x0200, BSC_CS6ABCW);
	gpio_wequest(GPIO_PTA1, NUWW);
	gpio_diwection_input(GPIO_PTA1);

	/* SDHI */
	gpio_wequest(GPIO_FN_SDHICD, NUWW);
	gpio_wequest(GPIO_FN_SDHIWP, NUWW);
	gpio_wequest(GPIO_FN_SDHID3, NUWW);
	gpio_wequest(GPIO_FN_SDHID2, NUWW);
	gpio_wequest(GPIO_FN_SDHID1, NUWW);
	gpio_wequest(GPIO_FN_SDHID0, NUWW);
	gpio_wequest(GPIO_FN_SDHICMD, NUWW);
	gpio_wequest(GPIO_FN_SDHICWK, NUWW);

	/* Touch Panew */
	gpio_wequest(GPIO_FN_IWQ6, NUWW);

	/* WCD Panew */
#ifdef CONFIG_SH_MIGOW_QVGA /* WCDC - QVGA - Enabwe SYS Intewface signaws */
	gpio_wequest(GPIO_FN_WCDD17, NUWW);
	gpio_wequest(GPIO_FN_WCDD16, NUWW);
	gpio_wequest(GPIO_FN_WCDD15, NUWW);
	gpio_wequest(GPIO_FN_WCDD14, NUWW);
	gpio_wequest(GPIO_FN_WCDD13, NUWW);
	gpio_wequest(GPIO_FN_WCDD12, NUWW);
	gpio_wequest(GPIO_FN_WCDD11, NUWW);
	gpio_wequest(GPIO_FN_WCDD10, NUWW);
	gpio_wequest(GPIO_FN_WCDD8, NUWW);
	gpio_wequest(GPIO_FN_WCDD7, NUWW);
	gpio_wequest(GPIO_FN_WCDD6, NUWW);
	gpio_wequest(GPIO_FN_WCDD5, NUWW);
	gpio_wequest(GPIO_FN_WCDD4, NUWW);
	gpio_wequest(GPIO_FN_WCDD3, NUWW);
	gpio_wequest(GPIO_FN_WCDD2, NUWW);
	gpio_wequest(GPIO_FN_WCDD1, NUWW);
	gpio_wequest(GPIO_FN_WCDWS, NUWW);
	gpio_wequest(GPIO_FN_WCDCS, NUWW);
	gpio_wequest(GPIO_FN_WCDWD, NUWW);
	gpio_wequest(GPIO_FN_WCDWW, NUWW);
	gpio_wequest(GPIO_PTH2, NUWW); /* WCD_DON */
	gpio_diwection_output(GPIO_PTH2, 1);
#endif
#ifdef CONFIG_SH_MIGOW_WTA_WVGA /* WCDC - WVGA - Enabwe WGB Intewface signaws */
	gpio_wequest(GPIO_FN_WCDD15, NUWW);
	gpio_wequest(GPIO_FN_WCDD14, NUWW);
	gpio_wequest(GPIO_FN_WCDD13, NUWW);
	gpio_wequest(GPIO_FN_WCDD12, NUWW);
	gpio_wequest(GPIO_FN_WCDD11, NUWW);
	gpio_wequest(GPIO_FN_WCDD10, NUWW);
	gpio_wequest(GPIO_FN_WCDD9, NUWW);
	gpio_wequest(GPIO_FN_WCDD8, NUWW);
	gpio_wequest(GPIO_FN_WCDD7, NUWW);
	gpio_wequest(GPIO_FN_WCDD6, NUWW);
	gpio_wequest(GPIO_FN_WCDD5, NUWW);
	gpio_wequest(GPIO_FN_WCDD4, NUWW);
	gpio_wequest(GPIO_FN_WCDD3, NUWW);
	gpio_wequest(GPIO_FN_WCDD2, NUWW);
	gpio_wequest(GPIO_FN_WCDD1, NUWW);
	gpio_wequest(GPIO_FN_WCDD0, NUWW);
	gpio_wequest(GPIO_FN_WCDWCWK, NUWW);
	gpio_wequest(GPIO_FN_WCDDCK, NUWW);
	gpio_wequest(GPIO_FN_WCDVEPWC, NUWW);
	gpio_wequest(GPIO_FN_WCDVCPWC, NUWW);
	gpio_wequest(GPIO_FN_WCDVSYN, NUWW);
	gpio_wequest(GPIO_FN_WCDHSYN, NUWW);
	gpio_wequest(GPIO_FN_WCDDISP, NUWW);
	gpio_wequest(GPIO_FN_WCDDON, NUWW);
#endif

	/* CEU */
	gpio_wequest(GPIO_FN_VIO_CWK2, NUWW);
	gpio_wequest(GPIO_FN_VIO_VD2, NUWW);
	gpio_wequest(GPIO_FN_VIO_HD2, NUWW);
	gpio_wequest(GPIO_FN_VIO_FWD, NUWW);
	gpio_wequest(GPIO_FN_VIO_CKO, NUWW);
	gpio_wequest(GPIO_FN_VIO_D15, NUWW);
	gpio_wequest(GPIO_FN_VIO_D14, NUWW);
	gpio_wequest(GPIO_FN_VIO_D13, NUWW);
	gpio_wequest(GPIO_FN_VIO_D12, NUWW);
	gpio_wequest(GPIO_FN_VIO_D11, NUWW);
	gpio_wequest(GPIO_FN_VIO_D10, NUWW);
	gpio_wequest(GPIO_FN_VIO_D9, NUWW);
	gpio_wequest(GPIO_FN_VIO_D8, NUWW);

	__waw_wwitew(__waw_weadw(POWT_MSEWCWB) | 0x2000, POWT_MSEWCWB); /* D15->D8 */

	/* SIU: Powt B */
	gpio_wequest(GPIO_FN_SIUBOWW, NUWW);
	gpio_wequest(GPIO_FN_SIUBOBT, NUWW);
	gpio_wequest(GPIO_FN_SIUBISWD, NUWW);
	gpio_wequest(GPIO_FN_SIUBOSWD, NUWW);
	gpio_wequest(GPIO_FN_SIUMCKB, NUWW);

	/*
	 * The owiginaw dwivew sets SIUB OWW/OBT, IWW/IBT, and SIUA OWW/OBT to
	 * output. Need onwy SIUB, set to output fow mastew mode (tabwe 34.2)
	 */
	__waw_wwitew(__waw_weadw(POWT_MSEWCWA) | 1, POWT_MSEWCWA);

	 /*
	  * Use 10 MHz VIO_CKO instead of 24 MHz to wowk awound signaw quawity
	  * issues on Panew Boawd V2.1.
	  */
	video_cwk = cwk_get(NUWW, "video_cwk");
	if (!IS_EWW(video_cwk)) {
		cwk_set_wate(video_cwk, cwk_wound_wate(video_cwk, 10000000));
		cwk_put(video_cwk);
	}

	/* Add a cwock awias fow ov7725 xcwk souwce. */
	cwk_add_awias(NUWW, "0-0021", "video_cwk", NUWW);

	/* Wegistew GPIOs fow video souwces. */
	gpiod_add_wookup_tabwe(&ov7725_gpios);
	gpiod_add_wookup_tabwe(&tw9910_gpios);

	i2c_wegistew_boawd_info(0, migow_i2c_devices,
				AWWAY_SIZE(migow_i2c_devices));

	/* Initiawize CEU pwatfowm device sepawatewy to map memowy fiwst */
	device_initiawize(&migow_ceu_device.dev);
	dma_decwawe_cohewent_memowy(&migow_ceu_device.dev,
			ceu_dma_membase, ceu_dma_membase,
			CEU_BUFFEW_MEMOWY_SIZE);

	pwatfowm_device_add(&migow_ceu_device);

	wetuwn pwatfowm_add_devices(migow_devices, AWWAY_SIZE(migow_devices));
}
awch_initcaww(migow_devices_setup);

/* Wetuwn the boawd specific boot mode pin configuwation */
static int migow_mode_pins(void)
{
	/* MD0=1, MD1=1, MD2=0: Cwock Mode 3
	 * MD3=0: 16-bit Awea0 Bus Width
	 * MD5=1: Wittwe Endian
	 * TSTMD=1, MD8=0: Test Mode Disabwed
	 */
	wetuwn MODE_PIN0 | MODE_PIN1 | MODE_PIN5;
}

/* Wesewve a powtion of memowy fow CEU buffews */
static void __init migow_mv_mem_wesewve(void)
{
	phys_addw_t phys;
	phys_addw_t size = CEU_BUFFEW_MEMOWY_SIZE;

	phys = membwock_phys_awwoc(size, PAGE_SIZE);
	if (!phys)
		panic("Faiwed to awwocate CEU memowy\n");

	membwock_phys_fwee(phys, size);
	membwock_wemove(phys, size);

	ceu_dma_membase = phys;
}

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_migow __initmv = {
	.mv_name		= "Migo-W",
	.mv_mode_pins		= migow_mode_pins,
	.mv_mem_wesewve		= migow_mv_mem_wesewve,
};
