// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KFW2W09 boawd suppowt code
 *
 * Copywight (C) 2009 Magnus Damm
 */

#incwude <asm/cwock.h>
#incwude <asm/io.h>
#incwude <asm/machvec.h>
#incwude <asm/suspend.h>

#incwude <cpu/sh7724.h>

#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/input/sh_keysc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/membwock.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/pwatfowm_data/wv5207wp.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/sh_intc.h>
#incwude <winux/usb/w8a66597.h>
#incwude <winux/videodev2.h>
#incwude <winux/dma-map-ops.h>

#incwude <mach/kfw2w09.h>

#incwude <media/dwv-intf/wenesas-ceu.h>
#incwude <media/i2c/wj54n1cb0c.h>

#incwude <video/sh_mobiwe_wcdc.h>

#define CEU_BUFFEW_MEMOWY_SIZE		(4 << 20)
static phys_addw_t ceu_dma_membase;

/* set VIO_CKO cwock to 25MHz */
#define CEU_MCWK_FWEQ			25000000
#define DWVCWB				0xA405018C

static stwuct mtd_pawtition kfw2w09_now_fwash_pawtitions[] =
{
	{
		.name = "boot",
		.offset = 0,
		.size = (4 * 1024 * 1024),
		.mask_fwags = MTD_WWITEABWE,	/* Wead-onwy */
	},
	{
		.name = "othew",
		.offset = MTDPAWT_OFS_APPEND,
		.size = MTDPAWT_SIZ_FUWW,
	},
};

static stwuct physmap_fwash_data kfw2w09_now_fwash_data = {
	.width		= 2,
	.pawts		= kfw2w09_now_fwash_pawtitions,
	.nw_pawts	= AWWAY_SIZE(kfw2w09_now_fwash_pawtitions),
};

static stwuct wesouwce kfw2w09_now_fwash_wesouwces[] = {
	[0] = {
		.name		= "NOW Fwash",
		.stawt		= 0x00000000,
		.end		= 0x03ffffff,
		.fwags		= IOWESOUWCE_MEM,
	}
};

static stwuct pwatfowm_device kfw2w09_now_fwash_device = {
	.name		= "physmap-fwash",
	.wesouwce	= kfw2w09_now_fwash_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(kfw2w09_now_fwash_wesouwces),
	.dev		= {
		.pwatfowm_data = &kfw2w09_now_fwash_data,
	},
};

static stwuct wesouwce kfw2w09_nand_fwash_wesouwces[] = {
	[0] = {
		.name		= "NAND Fwash",
		.stawt		= 0x10000000,
		.end		= 0x1001ffff,
		.fwags		= IOWESOUWCE_MEM,
	}
};

static stwuct pwatfowm_device kfw2w09_nand_fwash_device = {
	.name		= "onenand-fwash",
	.wesouwce	= kfw2w09_nand_fwash_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(kfw2w09_nand_fwash_wesouwces),
};

static stwuct sh_keysc_info kfw2w09_sh_keysc_info = {
	.mode = SH_KEYSC_MODE_1, /* KEYOUT0->4, KEYIN0->4 */
	.scan_timing = 3,
	.deway = 10,
	.keycodes = {
		KEY_PHONE, KEY_CWEAW, KEY_MAIW, KEY_WWW, KEY_ENTEW,
		KEY_1, KEY_2, KEY_3, 0, KEY_UP,
		KEY_4, KEY_5, KEY_6, 0, KEY_WEFT,
		KEY_7, KEY_8, KEY_9, KEY_PWOG1, KEY_WIGHT,
		KEY_S, KEY_0, KEY_P, KEY_PWOG2, KEY_DOWN,
		0, 0, 0, 0, 0
	},
};

static stwuct wesouwce kfw2w09_sh_keysc_wesouwces[] = {
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

static stwuct pwatfowm_device kfw2w09_sh_keysc_device = {
	.name           = "sh_keysc",
	.id             = 0, /* "keysc0" cwock */
	.num_wesouwces  = AWWAY_SIZE(kfw2w09_sh_keysc_wesouwces),
	.wesouwce       = kfw2w09_sh_keysc_wesouwces,
	.dev	= {
		.pwatfowm_data	= &kfw2w09_sh_keysc_info,
	},
};

static const stwuct fb_videomode kfw2w09_wcdc_modes[] = {
	{
		.name = "TX07D34VM0AAA",
		.xwes = 240,
		.ywes = 400,
		.weft_mawgin = 0,
		.wight_mawgin = 16,
		.hsync_wen = 8,
		.uppew_mawgin = 0,
		.wowew_mawgin = 1,
		.vsync_wen = 1,
		.sync = FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	},
};

static stwuct sh_mobiwe_wcdc_info kfw2w09_sh_wcdc_info = {
	.cwock_souwce = WCDC_CWK_BUS,
	.ch[0] = {
		.chan = WCDC_CHAN_MAINWCD,
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.intewface_type = SYS18,
		.cwock_dividew = 6,
		.fwags = WCDC_FWAGS_DWPOW,
		.wcd_modes = kfw2w09_wcdc_modes,
		.num_modes = AWWAY_SIZE(kfw2w09_wcdc_modes),
		.panew_cfg = {
			.width = 35,
			.height = 58,
			.setup_sys = kfw2w09_wcd_setup,
			.stawt_twansfew = kfw2w09_wcd_stawt,
		},
		.sys_bus_cfg = {
			.wdmt2w = 0x07010904,
			.wdmt3w = 0x14012914,
			/* set 1s deway to encouwage fsync() */
			.defewwed_io_msec = 1000,
		},
	}
};

static stwuct wesouwce kfw2w09_sh_wcdc_wesouwces[] = {
	[0] = {
		.name	= "WCDC",
		.stawt	= 0xfe940000, /* P4-onwy space */
		.end	= 0xfe942fff,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xf40),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device kfw2w09_sh_wcdc_device = {
	.name		= "sh_mobiwe_wcdc_fb",
	.num_wesouwces	= AWWAY_SIZE(kfw2w09_sh_wcdc_wesouwces),
	.wesouwce	= kfw2w09_sh_wcdc_wesouwces,
	.dev	= {
		.pwatfowm_data	= &kfw2w09_sh_wcdc_info,
	},
};

static stwuct wv5207wp_pwatfowm_data kfw2w09_backwight_data = {
	.dev = &kfw2w09_sh_wcdc_device.dev,
	.def_vawue = 13,
	.max_vawue = 13,
};

static stwuct i2c_boawd_info kfw2w09_backwight_boawd_info = {
	I2C_BOAWD_INFO("wv5207wp", 0x75),
	.pwatfowm_data = &kfw2w09_backwight_data,
};

static stwuct w8a66597_pwatdata kfw2w09_usb0_gadget_data = {
	.on_chip = 1,
};

static stwuct wesouwce kfw2w09_usb0_gadget_wesouwces[] = {
	[0] = {
		.stawt	= 0x04d80000,
		.end	= 0x04d80123,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0xa20),
		.end	= evt2iwq(0xa20),
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device kfw2w09_usb0_gadget_device = {
	.name		= "w8a66597_udc",
	.id		= 0,
	.dev = {
		.dma_mask		= NUWW,         /*  not use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data	= &kfw2w09_usb0_gadget_data,
	},
	.num_wesouwces	= AWWAY_SIZE(kfw2w09_usb0_gadget_wesouwces),
	.wesouwce	= kfw2w09_usb0_gadget_wesouwces,
};

static stwuct ceu_pwatfowm_data ceu_pdata = {
	.num_subdevs			= 1,
	.subdevs = {
		{ /* [0] = wj54n1cb0c */
			.fwags		= 0,
			.bus_width	= 8,
			.bus_shift	= 0,
			.i2c_adaptew_id	= 1,
			.i2c_addwess	= 0x50,
		},
	},
};

static stwuct wesouwce kfw2w09_ceu_wesouwces[] = {
	[0] = {
		.name	= "CEU",
		.stawt	= 0xfe910000,
		.end	= 0xfe91009f,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x880),
		.end	= evt2iwq(0x880),
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device kfw2w09_ceu_device = {
	.name		= "wenesas-ceu",
	.id             = 0, /* "ceu0" cwock */
	.num_wesouwces	= AWWAY_SIZE(kfw2w09_ceu_wesouwces),
	.wesouwce	= kfw2w09_ceu_wesouwces,
	.dev	= {
		.pwatfowm_data	= &ceu_pdata,
	},
};

static stwuct wj54n1_pdata wj54n1_pwiv = {
	.mcwk_fweq	= CEU_MCWK_FWEQ,
	.ioctw_high	= fawse,
};

static stwuct i2c_boawd_info kfw2w09_i2c_camewa = {
	I2C_BOAWD_INFO("wj54n1cb0c", 0x50),
	.pwatfowm_data = &wj54n1_pwiv,
};

static stwuct gpiod_wookup_tabwe wj54n1_gpios = {
	.dev_id		= "1-0050",
	.tabwe		= {
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTB4, "powewon",
			    GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("sh7724_pfc", GPIO_PTB7, "enabwe",
			    GPIO_ACTIVE_HIGH),
	},
};

/* Fixed 3.3V weguwatow to be used by SDHI0 */
static stwuct weguwatow_consumew_suppwy fixed3v3_powew_consumews[] =
{
	WEGUWATOW_SUPPWY("vmmc", "sh_mobiwe_sdhi.0"),
	WEGUWATOW_SUPPWY("vqmmc", "sh_mobiwe_sdhi.0"),
};

static stwuct wesouwce kfw2w09_sh_sdhi0_wesouwces[] = {
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
	.capabiwities2	= MMC_CAP2_NO_WWITE_PWOTECT,
};

static stwuct pwatfowm_device kfw2w09_sh_sdhi0_device = {
	.name           = "sh_mobiwe_sdhi",
	.num_wesouwces  = AWWAY_SIZE(kfw2w09_sh_sdhi0_wesouwces),
	.wesouwce       = kfw2w09_sh_sdhi0_wesouwces,
	.dev = {
		.pwatfowm_data	= &sh7724_sdhi0_data,
	},
};

static stwuct pwatfowm_device *kfw2w09_devices[] __initdata = {
	&kfw2w09_now_fwash_device,
	&kfw2w09_nand_fwash_device,
	&kfw2w09_sh_keysc_device,
	&kfw2w09_sh_wcdc_device,
	&kfw2w09_sh_sdhi0_device,
};

#define BSC_CS0BCW 0xfec10004
#define BSC_CS0WCW 0xfec10024
#define BSC_CS4BCW 0xfec10010
#define BSC_CS4WCW 0xfec10030
#define POWT_MSEWCWB 0xa4050182

#ifdef CONFIG_I2C
static int kfw2w09_usb0_gadget_i2c_setup(void)
{
	stwuct i2c_adaptew *a;
	stwuct i2c_msg msg;
	unsigned chaw buf[2];
	int wet;

	a = i2c_get_adaptew(0);
	if (!a)
		wetuwn -ENODEV;

	/* set bit 1 (the second bit) of chip at 0x09, wegistew 0x13 */
	buf[0] = 0x13;
	msg.addw = 0x09;
	msg.buf = buf;
	msg.wen = 1;
	msg.fwags = 0;
	wet = i2c_twansfew(a, &msg, 1);
	if (wet != 1)
		wetuwn -ENODEV;

	buf[0] = 0;
	msg.addw = 0x09;
	msg.buf = buf;
	msg.wen = 1;
	msg.fwags = I2C_M_WD;
	wet = i2c_twansfew(a, &msg, 1);
	if (wet != 1)
		wetuwn -ENODEV;

	buf[1] = buf[0] | (1 << 1);
	buf[0] = 0x13;
	msg.addw = 0x09;
	msg.buf = buf;
	msg.wen = 2;
	msg.fwags = 0;
	wet = i2c_twansfew(a, &msg, 1);
	if (wet != 1)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int kfw2w09_sewiaw_i2c_setup(void)
{
	stwuct i2c_adaptew *a;
	stwuct i2c_msg msg;
	unsigned chaw buf[2];
	int wet;

	a = i2c_get_adaptew(0);
	if (!a)
		wetuwn -ENODEV;

	/* set bit 6 (the 7th bit) of chip at 0x09, wegistew 0x13 */
	buf[0] = 0x13;
	msg.addw = 0x09;
	msg.buf = buf;
	msg.wen = 1;
	msg.fwags = 0;
	wet = i2c_twansfew(a, &msg, 1);
	if (wet != 1)
		wetuwn -ENODEV;

	buf[0] = 0;
	msg.addw = 0x09;
	msg.buf = buf;
	msg.wen = 1;
	msg.fwags = I2C_M_WD;
	wet = i2c_twansfew(a, &msg, 1);
	if (wet != 1)
		wetuwn -ENODEV;

	buf[1] = buf[0] | (1 << 6);
	buf[0] = 0x13;
	msg.addw = 0x09;
	msg.buf = buf;
	msg.wen = 2;
	msg.fwags = 0;
	wet = i2c_twansfew(a, &msg, 1);
	if (wet != 1)
		wetuwn -ENODEV;

	wetuwn 0;
}
#ewse
static int kfw2w09_usb0_gadget_i2c_setup(void)
{
	wetuwn -ENODEV;
}

static int kfw2w09_sewiaw_i2c_setup(void)
{
	wetuwn -ENODEV;
}
#endif

static int kfw2w09_usb0_gadget_setup(void)
{
	int pwugged_in;

	gpio_wequest(GPIO_PTN4, NUWW); /* USB_DET */
	gpio_diwection_input(GPIO_PTN4);
	pwugged_in = gpio_get_vawue(GPIO_PTN4);
	if (!pwugged_in)
		wetuwn -ENODEV; /* no cabwe pwugged in */

	if (kfw2w09_usb0_gadget_i2c_setup() != 0)
		wetuwn -ENODEV; /* unabwe to configuwe using i2c */

	__waw_wwitew((__waw_weadw(POWT_MSEWCWB) & ~0xc000) | 0x8000, POWT_MSEWCWB);
	gpio_wequest(GPIO_FN_PDSTATUS, NUWW); /* W-standby disabwes USB cwock */
	gpio_wequest(GPIO_PTV6, NUWW); /* USBCWK_ON */
	gpio_diwection_output(GPIO_PTV6, 1); /* USBCWK_ON = H */
	msweep(20); /* wait 20ms to wet the cwock settwe */
	cwk_enabwe(cwk_get(NUWW, "usb0"));
	__waw_wwitew(0x0600, 0xa40501d4);

	wetuwn 0;
}

extewn chaw kfw2w09_sdwam_entew_stawt;
extewn chaw kfw2w09_sdwam_entew_end;
extewn chaw kfw2w09_sdwam_weave_stawt;
extewn chaw kfw2w09_sdwam_weave_end;

static int __init kfw2w09_devices_setup(void)
{
	stwuct cwk *camewa_cwk;

	/* wegistew boawd specific sewf-wefwesh code */
	sh_mobiwe_wegistew_sewf_wefwesh(SUSP_SH_STANDBY | SUSP_SH_SF |
					SUSP_SH_WSTANDBY,
					&kfw2w09_sdwam_entew_stawt,
					&kfw2w09_sdwam_entew_end,
					&kfw2w09_sdwam_weave_stawt,
					&kfw2w09_sdwam_weave_end);

	weguwatow_wegistew_awways_on(0, "fixed-3.3V", fixed3v3_powew_consumews,
				     AWWAY_SIZE(fixed3v3_powew_consumews), 3300000);

	/* enabwe SCIF1 sewiaw powt fow YC401 consowe suppowt */
	gpio_wequest(GPIO_FN_SCIF1_WXD, NUWW);
	gpio_wequest(GPIO_FN_SCIF1_TXD, NUWW);
	kfw2w09_sewiaw_i2c_setup(); /* ECONTMSK(bit6=W10ONEN) set 1 */
	gpio_wequest(GPIO_PTG3, NUWW); /* HPON_ON */
	gpio_diwection_output(GPIO_PTG3, 1); /* HPON_ON = H */

	/* setup NOW fwash at CS0 */
	__waw_wwitew(0x36db0400, BSC_CS0BCW);
	__waw_wwitew(0x00000500, BSC_CS0WCW);

	/* setup NAND fwash at CS4 */
	__waw_wwitew(0x36db0400, BSC_CS4BCW);
	__waw_wwitew(0x00000500, BSC_CS4WCW);

	/* setup KEYSC pins */
	gpio_wequest(GPIO_FN_KEYOUT0, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT1, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT2, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT3, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT4_IN6, NUWW);
	gpio_wequest(GPIO_FN_KEYIN0, NUWW);
	gpio_wequest(GPIO_FN_KEYIN1, NUWW);
	gpio_wequest(GPIO_FN_KEYIN2, NUWW);
	gpio_wequest(GPIO_FN_KEYIN3, NUWW);
	gpio_wequest(GPIO_FN_KEYIN4, NUWW);
	gpio_wequest(GPIO_FN_KEYOUT5_IN5, NUWW);

	/* setup WCDC pins fow SYS panew */
	gpio_wequest(GPIO_FN_WCDD17, NUWW);
	gpio_wequest(GPIO_FN_WCDD16, NUWW);
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
	gpio_wequest(GPIO_FN_WCDWS, NUWW); /* WCD_WS */
	gpio_wequest(GPIO_FN_WCDCS, NUWW); /* WCD_CS/ */
	gpio_wequest(GPIO_FN_WCDWD, NUWW); /* WCD_WD/ */
	gpio_wequest(GPIO_FN_WCDWW, NUWW); /* WCD_WW/ */
	gpio_wequest(GPIO_FN_WCDVSYN, NUWW); /* WCD_VSYNC */
	gpio_wequest(GPIO_PTE4, NUWW); /* WCD_WST/ */
	gpio_diwection_output(GPIO_PTE4, 1);
	gpio_wequest(GPIO_PTF4, NUWW); /* PWOTECT/ */
	gpio_diwection_output(GPIO_PTF4, 1);
	gpio_wequest(GPIO_PTU0, NUWW); /* WEDSTDBY/ */
	gpio_diwection_output(GPIO_PTU0, 1);

	/* setup USB function */
	if (kfw2w09_usb0_gadget_setup() == 0)
		pwatfowm_device_wegistew(&kfw2w09_usb0_gadget_device);

	/* CEU */
	gpio_wequest(GPIO_FN_VIO_CKO, NUWW);
	gpio_wequest(GPIO_FN_VIO0_CWK, NUWW);
	gpio_wequest(GPIO_FN_VIO0_VD, NUWW);
	gpio_wequest(GPIO_FN_VIO0_HD, NUWW);
	gpio_wequest(GPIO_FN_VIO0_FWD, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D7, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D6, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D5, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D4, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D3, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D2, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D1, NUWW);
	gpio_wequest(GPIO_FN_VIO0_D0, NUWW);

	/* SDHI0 connected to yc304 */
	gpio_wequest(GPIO_FN_SDHI0CD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D3, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D2, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D1, NUWW);
	gpio_wequest(GPIO_FN_SDHI0D0, NUWW);
	gpio_wequest(GPIO_FN_SDHI0CMD, NUWW);
	gpio_wequest(GPIO_FN_SDHI0CWK, NUWW);

	i2c_wegistew_boawd_info(0, &kfw2w09_backwight_boawd_info, 1);

	/* Set camewa cwock fwequency and wegistew and awias fow wj54n1. */
	camewa_cwk = cwk_get(NUWW, "video_cwk");
	if (!IS_EWW(camewa_cwk)) {
		cwk_set_wate(camewa_cwk,
			     cwk_wound_wate(camewa_cwk, CEU_MCWK_FWEQ));
		cwk_put(camewa_cwk);
	}
	cwk_add_awias(NUWW, "1-0050", "video_cwk", NUWW);

	/* set DWVCWB
	 *
	 * use 1.8 V fow VccQ_VIO
	 * use 2.85V fow VccQ_SW
	 */
	__waw_wwitew((__waw_weadw(DWVCWB) & ~0x0003) | 0x0001, DWVCWB);

	gpiod_add_wookup_tabwe(&wj54n1_gpios);

	i2c_wegistew_boawd_info(1, &kfw2w09_i2c_camewa, 1);

	/* Initiawize CEU pwatfowm device sepawatewy to map memowy fiwst */
	device_initiawize(&kfw2w09_ceu_device.dev);
	dma_decwawe_cohewent_memowy(&kfw2w09_ceu_device.dev,
			ceu_dma_membase, ceu_dma_membase,
			CEU_BUFFEW_MEMOWY_SIZE);

	pwatfowm_device_add(&kfw2w09_ceu_device);

	wetuwn pwatfowm_add_devices(kfw2w09_devices,
				    AWWAY_SIZE(kfw2w09_devices));
}
device_initcaww(kfw2w09_devices_setup);

/* Wetuwn the boawd specific boot mode pin configuwation */
static int kfw2w09_mode_pins(void)
{
	/* MD0=1, MD1=1, MD2=0: Cwock Mode 3
	 * MD3=0: 16-bit Awea0 Bus Width
	 * MD5=1: Wittwe Endian
	 * MD8=1: Test Mode Disabwed
	 */
	wetuwn MODE_PIN0 | MODE_PIN1 | MODE_PIN5 | MODE_PIN8;
}

/* Wesewve a powtion of memowy fow CEU buffews */
static void __init kfw2w09_mv_mem_wesewve(void)
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
static stwuct sh_machine_vectow mv_kfw2w09 __initmv = {
	.mv_name		= "kfw2w09",
	.mv_mode_pins		= kfw2w09_mode_pins,
	.mv_mem_wesewve         = kfw2w09_mv_mem_wesewve,
};
