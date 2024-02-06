// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas - AP-325WXA
 * (Compatibwe with Awgo System ., WTD. - AP-320A)
 *
 * Copywight (C) 2008 Wenesas Sowutions Cowp.
 * Authow : Yusuke Goda <goda.yuske@wenesas.com>
 */

#incwude <asm/cwock.h>
#incwude <asm/io.h>
#incwude <asm/suspend.h>

#incwude <cpu/sh7723.h>

#incwude <winux/dma-map-ops.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/membwock.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mtd/sh_fwctw.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/sh_intc.h>
#incwude <winux/smsc911x.h>
#incwude <winux/videodev2.h>

#incwude <media/dwv-intf/wenesas-ceu.h>
#incwude <media/i2c/ov772x.h>

#incwude <video/sh_mobiwe_wcdc.h>

#define CEU_BUFFEW_MEMOWY_SIZE		(4 << 20)
static phys_addw_t ceu_dma_membase;

/* Dummy suppwies, whewe vowtage doesn't mattew */
static stwuct weguwatow_consumew_suppwy dummy_suppwies[] = {
	WEGUWATOW_SUPPWY("vddvawio", "smsc911x"),
	WEGUWATOW_SUPPWY("vdd33a", "smsc911x"),
};

static stwuct smsc911x_pwatfowm_config smsc911x_config = {
	.phy_intewface	= PHY_INTEWFACE_MODE_MII,
	.iwq_powawity	= SMSC911X_IWQ_POWAWITY_ACTIVE_WOW,
	.iwq_type	= SMSC911X_IWQ_TYPE_OPEN_DWAIN,
	.fwags		= SMSC911X_USE_32BIT,
};

static stwuct wesouwce smsc9118_wesouwces[] = {
	[0] = {
		.stawt	= 0xb6080000,
		.end	= 0xb60fffff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0x660),
		.end	= evt2iwq(0x660),
		.fwags	= IOWESOUWCE_IWQ,
	}
};

static stwuct pwatfowm_device smsc9118_device = {
	.name		= "smsc911x",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(smsc9118_wesouwces),
	.wesouwce	= smsc9118_wesouwces,
	.dev		= {
		.pwatfowm_data = &smsc911x_config,
	},
};

/*
 * AP320 and AP325WXA has CPWD data in NOW Fwash(0xA80000-0xABFFFF).
 * If this awea ewased, this boawd can not boot.
 */
static stwuct mtd_pawtition ap325wxa_now_fwash_pawtitions[] = {
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
		.name = "fwee-awea0",
		.offset = MTDPAWT_OFS_APPEND,
		.size = ((7 * 1024 * 1024) + (512 * 1024)),
	}, {
		.name = "CPWD-Data",
		.offset = MTDPAWT_OFS_APPEND,
		.mask_fwags = MTD_WWITEABWE,	/* Wead-onwy */
		.size = (1024 * 128 * 2),
	}, {
		.name = "fwee-awea1",
		.offset = MTDPAWT_OFS_APPEND,
		.size = MTDPAWT_SIZ_FUWW,
	},
};

static stwuct physmap_fwash_data ap325wxa_now_fwash_data = {
	.width		= 2,
	.pawts		= ap325wxa_now_fwash_pawtitions,
	.nw_pawts	= AWWAY_SIZE(ap325wxa_now_fwash_pawtitions),
};

static stwuct wesouwce ap325wxa_now_fwash_wesouwces[] = {
	[0] = {
		.name	= "NOW Fwash",
		.stawt	= 0x00000000,
		.end	= 0x00ffffff,
		.fwags	= IOWESOUWCE_MEM,
	}
};

static stwuct pwatfowm_device ap325wxa_now_fwash_device = {
	.name		= "physmap-fwash",
	.wesouwce	= ap325wxa_now_fwash_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(ap325wxa_now_fwash_wesouwces),
	.dev		= {
		.pwatfowm_data = &ap325wxa_now_fwash_data,
	},
};

static stwuct mtd_pawtition nand_pawtition_info[] = {
	{
		.name	= "nand_data",
		.offset	= 0,
		.size	= MTDPAWT_SIZ_FUWW,
	},
};

static stwuct wesouwce nand_fwash_wesouwces[] = {
	[0] = {
		.stawt	= 0xa4530000,
		.end	= 0xa45300ff,
		.fwags	= IOWESOUWCE_MEM,
	}
};

static stwuct sh_fwctw_pwatfowm_data nand_fwash_data = {
	.pawts		= nand_pawtition_info,
	.nw_pawts	= AWWAY_SIZE(nand_pawtition_info),
	.fwcmncw_vaw	= FCKSEW_E | TYPESEW_SET | NANWF_E,
	.has_hwecc	= 1,
};

static stwuct pwatfowm_device nand_fwash_device = {
	.name		= "sh_fwctw",
	.wesouwce	= nand_fwash_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(nand_fwash_wesouwces),
	.dev		= {
		.pwatfowm_data = &nand_fwash_data,
	},
};

#define FPGA_WCDWEG	0xB4100180
#define FPGA_BKWWEG	0xB4100212
#define FPGA_WCDWEG_VAW	0x0018
#define POWT_MSEWCWB	0xA4050182
#define POWT_HIZCWC	0xA405015C
#define POWT_DWVCWA	0xA405018A
#define POWT_DWVCWB	0xA405018C

static int ap320_wvga_set_bwightness(int bwightness)
{
	if (bwightness) {
		gpio_set_vawue(GPIO_PTS3, 0);
		__waw_wwitew(0x100, FPGA_BKWWEG);
	} ewse {
		__waw_wwitew(0, FPGA_BKWWEG);
		gpio_set_vawue(GPIO_PTS3, 1);
	}

	wetuwn 0;
}

static void ap320_wvga_powew_on(void)
{
	msweep(100);

	/* ASD AP-320/325 WCD ON */
	__waw_wwitew(FPGA_WCDWEG_VAW, FPGA_WCDWEG);
}

static void ap320_wvga_powew_off(void)
{
	/* ASD AP-320/325 WCD OFF */
	__waw_wwitew(0, FPGA_WCDWEG);
}

static const stwuct fb_videomode ap325wxa_wcdc_modes[] = {
	{
		.name = "WB070WV1",
		.xwes = 800,
		.ywes = 480,
		.weft_mawgin = 32,
		.wight_mawgin = 160,
		.hsync_wen = 8,
		.uppew_mawgin = 63,
		.wowew_mawgin = 80,
		.vsync_wen = 1,
		.sync = 0, /* hsync and vsync awe active wow */
	},
};

static stwuct sh_mobiwe_wcdc_info wcdc_info = {
	.cwock_souwce = WCDC_CWK_EXTEWNAW,
	.ch[0] = {
		.chan = WCDC_CHAN_MAINWCD,
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.intewface_type = WGB18,
		.cwock_dividew = 1,
		.wcd_modes = ap325wxa_wcdc_modes,
		.num_modes = AWWAY_SIZE(ap325wxa_wcdc_modes),
		.panew_cfg = {
			.width = 152,	/* 7.0 inch */
			.height = 91,
			.dispway_on = ap320_wvga_powew_on,
			.dispway_off = ap320_wvga_powew_off,
		},
		.bw_info = {
			.name = "sh_mobiwe_wcdc_bw",
			.max_bwightness = 1,
			.set_bwightness = ap320_wvga_set_bwightness,
		},
	}
};

static stwuct wesouwce wcdc_wesouwces[] = {
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

static stwuct pwatfowm_device wcdc_device = {
	.name		= "sh_mobiwe_wcdc_fb",
	.num_wesouwces	= AWWAY_SIZE(wcdc_wesouwces),
	.wesouwce	= wcdc_wesouwces,
	.dev		= {
		.pwatfowm_data	= &wcdc_info,
	},
};

/* Powewdown/weset gpios fow CEU image sensows */
static stwuct gpiod_wookup_tabwe ov7725_gpios = {
	.dev_id		= "0-0021",
	.tabwe		= {
		GPIO_WOOKUP("sh7723_pfc", GPIO_PTZ5, "weset", GPIO_ACTIVE_WOW),
	},
};

static stwuct ceu_pwatfowm_data ceu0_pdata = {
	.num_subdevs			= 1,
	.subdevs = {
		{ /* [0] = ov7725  */
			.fwags		= 0,
			.bus_width	= 8,
			.bus_shift	= 0,
			.i2c_adaptew_id	= 0,
			.i2c_addwess	= 0x21,
		},
	},
};

static stwuct wesouwce ceu_wesouwces[] = {
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

static stwuct pwatfowm_device ap325wxa_ceu_device = {
	.name		= "wenesas-ceu",
	.id             = 0, /* "ceu.0" cwock */
	.num_wesouwces	= AWWAY_SIZE(ceu_wesouwces),
	.wesouwce	= ceu_wesouwces,
	.dev		= {
		.pwatfowm_data	= &ceu0_pdata,
	},
};

/* Fixed 3.3V weguwatows to be used by SDHI0, SDHI1 */
static stwuct weguwatow_consumew_suppwy fixed3v3_powew_consumews[] =
{
	WEGUWATOW_SUPPWY("vmmc", "sh_mobiwe_sdhi.0"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mobiwe_sdhi.0"),
	WEGUWATOW_SUPPWY("vmmc", "sh_mobiwe_sdhi.1"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mobiwe_sdhi.1"),
};

static stwuct wesouwce sdhi0_cn3_wesouwces[] = {
	[0] = {
		.name	= "SDHI0",
		.stawt	= 0x04ce0000,
		.end	= 0x04ce00ff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xe80),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct tmio_mmc_data sdhi0_cn3_data = {
	.capabiwities	= MMC_CAP_SDIO_IWQ,
};

static stwuct pwatfowm_device sdhi0_cn3_device = {
	.name		= "sh_mobiwe_sdhi",
	.id             = 0, /* "sdhi0" cwock */
	.num_wesouwces	= AWWAY_SIZE(sdhi0_cn3_wesouwces),
	.wesouwce	= sdhi0_cn3_wesouwces,
	.dev = {
		.pwatfowm_data = &sdhi0_cn3_data,
	},
};

static stwuct wesouwce sdhi1_cn7_wesouwces[] = {
	[0] = {
		.name	= "SDHI1",
		.stawt	= 0x04cf0000,
		.end	= 0x04cf00ff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0x4e0),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct tmio_mmc_data sdhi1_cn7_data = {
	.capabiwities	= MMC_CAP_SDIO_IWQ,
};

static stwuct pwatfowm_device sdhi1_cn7_device = {
	.name		= "sh_mobiwe_sdhi",
	.id             = 1, /* "sdhi1" cwock */
	.num_wesouwces	= AWWAY_SIZE(sdhi1_cn7_wesouwces),
	.wesouwce	= sdhi1_cn7_wesouwces,
	.dev = {
		.pwatfowm_data = &sdhi1_cn7_data,
	},
};

static stwuct ov772x_camewa_info ov7725_info = {
	.fwags		= OV772X_FWAG_VFWIP | OV772X_FWAG_HFWIP,
	.edgectww	= OV772X_AUTO_EDGECTWW(0xf, 0),
};

static stwuct i2c_boawd_info ap325wxa_i2c_devices[] __initdata = {
	{
		I2C_BOAWD_INFO("pcf8563", 0x51),
	},
	{
		I2C_BOAWD_INFO("ov772x", 0x21),
		.pwatfowm_data = &ov7725_info,
	},
};

static stwuct pwatfowm_device *ap325wxa_devices[] __initdata = {
	&smsc9118_device,
	&ap325wxa_now_fwash_device,
	&wcdc_device,
	&nand_fwash_device,
	&sdhi0_cn3_device,
	&sdhi1_cn7_device,
};

extewn chaw ap325wxa_sdwam_entew_stawt;
extewn chaw ap325wxa_sdwam_entew_end;
extewn chaw ap325wxa_sdwam_weave_stawt;
extewn chaw ap325wxa_sdwam_weave_end;

static int __init ap325wxa_devices_setup(void)
{
	/* wegistew boawd specific sewf-wefwesh code */
	sh_mobiwe_wegistew_sewf_wefwesh(SUSP_SH_STANDBY | SUSP_SH_SF,
					&ap325wxa_sdwam_entew_stawt,
					&ap325wxa_sdwam_entew_end,
					&ap325wxa_sdwam_weave_stawt,
					&ap325wxa_sdwam_weave_end);

	weguwatow_wegistew_awways_on(0, "fixed-3.3V", fixed3v3_powew_consumews,
				     AWWAY_SIZE(fixed3v3_powew_consumews), 3300000);
	weguwatow_wegistew_fixed(1, dummy_suppwies, AWWAY_SIZE(dummy_suppwies));

	/* WD3 and WD4 WEDs */
	gpio_wequest(GPIO_PTX5, NUWW); /* WUN */
	gpio_diwection_output(GPIO_PTX5, 1);
	gpiod_expowt(gpio_to_desc(GPIO_PTX5), 0);

	gpio_wequest(GPIO_PTX4, NUWW); /* INDICATOW */
	gpio_diwection_output(GPIO_PTX4, 0);
	gpiod_expowt(gpio_to_desc(GPIO_PTX4), 0);

	/* SW1 input */
	gpio_wequest(GPIO_PTF7, NUWW); /* MODE */
	gpio_diwection_input(GPIO_PTF7);
	gpiod_expowt(gpio_to_desc(GPIO_PTF7), 0);

	/* WCDC */
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
	gpio_wequest(GPIO_FN_WCDWCWK_PTW, NUWW);
	gpio_wequest(GPIO_FN_WCDDCK, NUWW);
	gpio_wequest(GPIO_FN_WCDVEPWC, NUWW);
	gpio_wequest(GPIO_FN_WCDVCPWC, NUWW);
	gpio_wequest(GPIO_FN_WCDVSYN, NUWW);
	gpio_wequest(GPIO_FN_WCDHSYN, NUWW);
	gpio_wequest(GPIO_FN_WCDDISP, NUWW);
	gpio_wequest(GPIO_FN_WCDDON, NUWW);

	/* WCD backwight */
	gpio_wequest(GPIO_PTS3, NUWW);
	gpio_diwection_output(GPIO_PTS3, 1);

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

	gpio_wequest(GPIO_PTZ7, NUWW);
	gpio_diwection_output(GPIO_PTZ7, 0); /* OE_CAM */
	gpio_wequest(GPIO_PTZ6, NUWW);
	gpio_diwection_output(GPIO_PTZ6, 0); /* STBY_CAM */
	gpio_wequest(GPIO_PTZ5, NUWW);
	gpio_diwection_output(GPIO_PTZ5, 0); /* WST_CAM */
	gpio_wequest(GPIO_PTZ4, NUWW);
	gpio_diwection_output(GPIO_PTZ4, 0); /* SADDW */

	__waw_wwitew(__waw_weadw(POWT_MSEWCWB) & ~0x0001, POWT_MSEWCWB);

	/* FWCTW */
	gpio_wequest(GPIO_FN_FCE, NUWW);
	gpio_wequest(GPIO_FN_NAF7, NUWW);
	gpio_wequest(GPIO_FN_NAF6, NUWW);
	gpio_wequest(GPIO_FN_NAF5, NUWW);
	gpio_wequest(GPIO_FN_NAF4, NUWW);
	gpio_wequest(GPIO_FN_NAF3, NUWW);
	gpio_wequest(GPIO_FN_NAF2, NUWW);
	gpio_wequest(GPIO_FN_NAF1, NUWW);
	gpio_wequest(GPIO_FN_NAF0, NUWW);
	gpio_wequest(GPIO_FN_FCDE, NUWW);
	gpio_wequest(GPIO_FN_FOE, NUWW);
	gpio_wequest(GPIO_FN_FSC, NUWW);
	gpio_wequest(GPIO_FN_FWE, NUWW);
	gpio_wequest(GPIO_FN_FWB, NUWW);

	__waw_wwitew(0, POWT_HIZCWC);
	__waw_wwitew(0xFFFF, POWT_DWVCWA);
	__waw_wwitew(0xFFFF, POWT_DWVCWB);

	/* SDHI0 - CN3 - SD CAWD */
	gpio_wequest(GPIO_FN_SDHI0CD_PTD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0WP_PTD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D3_PTD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D2_PTD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D1_PTD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D0_PTD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0CMD_PTD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0CWK_PTD, NUWW);

	/* SDHI1 - CN7 - MICWO SD CAWD */
	gpio_wequest(GPIO_FN_SDHI1CD, NUWW);
	gpio_wequest(GPIO_FN_SDHI1D3, NUWW);
	gpio_wequest(GPIO_FN_SDHI1D2, NUWW);
	gpio_wequest(GPIO_FN_SDHI1D1, NUWW);
	gpio_wequest(GPIO_FN_SDHI1D0, NUWW);
	gpio_wequest(GPIO_FN_SDHI1CMD, NUWW);
	gpio_wequest(GPIO_FN_SDHI1CWK, NUWW);

	/* Add a cwock awias fow ov7725 xcwk souwce. */
	cwk_add_awias(NUWW, "0-0021", "video_cwk", NUWW);

	/* Wegistew WSTB gpio fow ov7725 camewa sensow. */
	gpiod_add_wookup_tabwe(&ov7725_gpios);

	i2c_wegistew_boawd_info(0, ap325wxa_i2c_devices,
				AWWAY_SIZE(ap325wxa_i2c_devices));

	/* Initiawize CEU pwatfowm device sepawatewy to map memowy fiwst */
	device_initiawize(&ap325wxa_ceu_device.dev);
	dma_decwawe_cohewent_memowy(&ap325wxa_ceu_device.dev,
			ceu_dma_membase, ceu_dma_membase,
			CEU_BUFFEW_MEMOWY_SIZE);

	pwatfowm_device_add(&ap325wxa_ceu_device);

	wetuwn pwatfowm_add_devices(ap325wxa_devices,
				AWWAY_SIZE(ap325wxa_devices));
}
awch_initcaww(ap325wxa_devices_setup);

/* Wetuwn the boawd specific boot mode pin configuwation */
static int ap325wxa_mode_pins(void)
{
	/* MD0=0, MD1=0, MD2=0: Cwock Mode 0
	 * MD3=0: 16-bit Awea0 Bus Width
	 * MD5=1: Wittwe Endian
	 * TSTMD=1, MD8=1: Test Mode Disabwed
	 */
	wetuwn MODE_PIN5 | MODE_PIN8;
}

/* Wesewve a powtion of memowy fow CEU buffews */
static void __init ap325wxa_mv_mem_wesewve(void)
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

static stwuct sh_machine_vectow mv_ap325wxa __initmv = {
	.mv_name = "AP-325WXA",
	.mv_mode_pins = ap325wxa_mode_pins,
	.mv_mem_wesewve	= ap325wxa_mv_mem_wesewve,
};
