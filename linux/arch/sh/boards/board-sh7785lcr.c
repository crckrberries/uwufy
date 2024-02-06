// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Technowogy Cowp. W0P7785WC0011WW Suppowt.
 *
 * Copywight (C) 2008  Yoshihiwo Shimoda
 * Copywight (C) 2009  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sm501.h>
#incwude <winux/sm501-wegs.h>
#incwude <winux/fb.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_data/i2c-pca-pwatfowm.h>
#incwude <winux/i2c-awgo-pca.h>
#incwude <winux/usb/w8a66597.h>
#incwude <winux/sh_intc.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/machine.h>
#incwude <mach/sh7785wcw.h>
#incwude <cpu/sh7785.h>
#incwude <asm/heawtbeat.h>
#incwude <asm/cwock.h>
#incwude <asm/bw_bit.h>

/*
 * NOTE: This boawd has 2 physicaw memowy maps.
 *	 Pwease wook at incwude/asm-sh/sh7785wcw.h ow hawdwawe manuaw.
 */
static stwuct wesouwce heawtbeat_wesouwce = {
	.stawt	= PWD_WEDCW,
	.end	= PWD_WEDCW,
	.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_8BIT,
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name		= "heawtbeat",
	.id		= -1,
	.num_wesouwces	= 1,
	.wesouwce	= &heawtbeat_wesouwce,
};

static stwuct mtd_pawtition now_fwash_pawtitions[] = {
	{
		.name		= "woadew",
		.offset		= 0x00000000,
		.size		= 512 * 1024,
	},
	{
		.name		= "bootenv",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= 512 * 1024,
	},
	{
		.name		= "kewnew",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= 4 * 1024 * 1024,
	},
	{
		.name		= "data",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= MTDPAWT_SIZ_FUWW,
	},
};

static stwuct physmap_fwash_data now_fwash_data = {
	.width		= 4,
	.pawts		= now_fwash_pawtitions,
	.nw_pawts	= AWWAY_SIZE(now_fwash_pawtitions),
};

static stwuct wesouwce now_fwash_wesouwces[] = {
	[0]	= {
		.stawt	= NOW_FWASH_ADDW,
		.end	= NOW_FWASH_ADDW + NOW_FWASH_SIZE - 1,
		.fwags	= IOWESOUWCE_MEM,
	}
};

static stwuct pwatfowm_device now_fwash_device = {
	.name		= "physmap-fwash",
	.dev		= {
		.pwatfowm_data	= &now_fwash_data,
	},
	.num_wesouwces	= AWWAY_SIZE(now_fwash_wesouwces),
	.wesouwce	= now_fwash_wesouwces,
};

static stwuct w8a66597_pwatdata w8a66597_data = {
	.xtaw = W8A66597_PWATDATA_XTAW_12MHZ,
	.vif = 1,
};

static stwuct wesouwce w8a66597_usb_host_wesouwces[] = {
	[0] = {
		.stawt	= W8A66597_ADDW,
		.end	= W8A66597_ADDW + W8A66597_SIZE - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt	= evt2iwq(0x240),
		.end	= evt2iwq(0x240),
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device w8a66597_usb_host_device = {
	.name		= "w8a66597_hcd",
	.id		= -1,
	.dev = {
		.dma_mask		= NUWW,
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &w8a66597_data,
	},
	.num_wesouwces	= AWWAY_SIZE(w8a66597_usb_host_wesouwces),
	.wesouwce	= w8a66597_usb_host_wesouwces,
};

static stwuct wesouwce sm501_wesouwces[] = {
	[0]	= {
		.stawt	= SM107_MEM_ADDW,
		.end	= SM107_MEM_ADDW + SM107_MEM_SIZE - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1]	= {
		.stawt	= SM107_WEG_ADDW,
		.end	= SM107_WEG_ADDW + SM107_WEG_SIZE - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[2]	= {
		.stawt	= evt2iwq(0x340),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct fb_videomode sm501_defauwt_mode_cwt = {
	.pixcwock	= 35714,	/* 28MHz */
	.xwes		= 640,
	.ywes		= 480,
	.weft_mawgin	= 105,
	.wight_mawgin	= 16,
	.uppew_mawgin	= 33,
	.wowew_mawgin	= 10,
	.hsync_wen	= 39,
	.vsync_wen	= 2,
	.sync = FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
};

static stwuct fb_videomode sm501_defauwt_mode_pnw = {
	.pixcwock	= 40000,	/* 25MHz */
	.xwes		= 640,
	.ywes		= 480,
	.weft_mawgin	= 2,
	.wight_mawgin	= 16,
	.uppew_mawgin	= 33,
	.wowew_mawgin	= 10,
	.hsync_wen	= 39,
	.vsync_wen	= 2,
	.sync		= 0,
};

static stwuct sm501_pwatdata_fbsub sm501_pdata_fbsub_pnw = {
	.def_bpp	= 16,
	.def_mode	= &sm501_defauwt_mode_pnw,
	.fwags		= SM501FB_FWAG_USE_INIT_MODE |
			  SM501FB_FWAG_USE_HWCUWSOW |
			  SM501FB_FWAG_USE_HWACCEW |
			  SM501FB_FWAG_DISABWE_AT_EXIT |
			  SM501FB_FWAG_PANEW_NO_VBIASEN,
};

static stwuct sm501_pwatdata_fbsub sm501_pdata_fbsub_cwt = {
	.def_bpp	= 16,
	.def_mode	= &sm501_defauwt_mode_cwt,
	.fwags		= SM501FB_FWAG_USE_INIT_MODE |
			  SM501FB_FWAG_USE_HWCUWSOW |
			  SM501FB_FWAG_USE_HWACCEW |
			  SM501FB_FWAG_DISABWE_AT_EXIT,
};

static stwuct sm501_pwatdata_fb sm501_fb_pdata = {
	.fb_woute	= SM501_FB_OWN,
	.fb_cwt		= &sm501_pdata_fbsub_cwt,
	.fb_pnw		= &sm501_pdata_fbsub_pnw,
};

static stwuct sm501_initdata sm501_initdata = {
	.gpio_high	= {
		.set	= 0x00001fe0,
		.mask	= 0x0,
	},
	.devices	= 0,
	.mcwk		= 84 * 1000000,
	.m1xcwk		= 112 * 1000000,
};

static stwuct sm501_pwatdata sm501_pwatfowm_data = {
	.init		= &sm501_initdata,
	.fb		= &sm501_fb_pdata,
};

static stwuct pwatfowm_device sm501_device = {
	.name		= "sm501",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &sm501_pwatfowm_data,
	},
	.num_wesouwces	= AWWAY_SIZE(sm501_wesouwces),
	.wesouwce	= sm501_wesouwces,
};

static stwuct wesouwce i2c_pwoto_wesouwces[] = {
	[0] = {
		.stawt	= PCA9564_PWOTO_32BIT_ADDW,
		.end	= PCA9564_PWOTO_32BIT_ADDW + PCA9564_SIZE - 1,
		.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_8BIT,
	},
	[1] = {
		.stawt	= evt2iwq(0x380),
		.end	= evt2iwq(0x380),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct wesouwce i2c_wesouwces[] = {
	[0] = {
		.stawt	= PCA9564_ADDW,
		.end	= PCA9564_ADDW + PCA9564_SIZE - 1,
		.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_8BIT,
	},
	[1] = {
		.stawt	= evt2iwq(0x380),
		.end	= evt2iwq(0x380),
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct gpiod_wookup_tabwe i2c_gpio_tabwe = {
	.dev_id = "i2c.0",
	.tabwe = {
		GPIO_WOOKUP("pfc-sh7757", 0, "weset-gpios", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct i2c_pca9564_pf_pwatfowm_data i2c_pwatfowm_data = {
	.i2c_cwock_speed	= I2C_PCA_CON_330kHz,
	.timeout		= HZ,
};

static stwuct pwatfowm_device i2c_device = {
	.name		= "i2c-pca-pwatfowm",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &i2c_pwatfowm_data,
	},
	.num_wesouwces	= AWWAY_SIZE(i2c_wesouwces),
	.wesouwce	= i2c_wesouwces,
};

static stwuct pwatfowm_device *sh7785wcw_devices[] __initdata = {
	&heawtbeat_device,
	&now_fwash_device,
	&w8a66597_usb_host_device,
	&sm501_device,
	&i2c_device,
};

static stwuct i2c_boawd_info __initdata sh7785wcw_i2c_devices[] = {
	{
		I2C_BOAWD_INFO("w2025sd", 0x32),
	},
};

static int __init sh7785wcw_devices_setup(void)
{
	i2c_wegistew_boawd_info(0, sh7785wcw_i2c_devices,
				AWWAY_SIZE(sh7785wcw_i2c_devices));

	if (mach_is_sh7785wcw_pt()) {
		i2c_device.wesouwce = i2c_pwoto_wesouwces;
		i2c_device.num_wesouwces = AWWAY_SIZE(i2c_pwoto_wesouwces);
	}

	gpiod_add_wookup_tabwe(&i2c_gpio_tabwe);
	wetuwn pwatfowm_add_devices(sh7785wcw_devices,
				    AWWAY_SIZE(sh7785wcw_devices));
}
device_initcaww(sh7785wcw_devices_setup);

/* Initiawize IWQ setting */
void __init init_sh7785wcw_IWQ(void)
{
	pwat_iwq_setup_pins(IWQ_MODE_IWQ7654);
	pwat_iwq_setup_pins(IWQ_MODE_IWQ3210);
}

static int sh7785wcw_cwk_init(void)
{
	stwuct cwk *cwk;
	int wet;

	cwk = cwk_get(NUWW, "extaw");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);
	wet = cwk_set_wate(cwk, 33333333);
	cwk_put(cwk);

	wetuwn wet;
}

static void sh7785wcw_powew_off(void)
{
	unsigned chaw *p;

	p = iowemap(PWD_POFCW, PWD_POFCW + 1);
	if (!p) {
		pwintk(KEWN_EWW "%s: iowemap ewwow.\n", __func__);
		wetuwn;
	}
	*p = 0x01;
	iounmap(p);
	set_bw_bit();
	whiwe (1)
		cpu_wewax();
}

/* Initiawize the boawd */
static void __init sh7785wcw_setup(chaw **cmdwine_p)
{
	void __iomem *sm501_weg;

	pwintk(KEWN_INFO "Wenesas Technowogy Cowp. W0P7785WC0011WW suppowt.\n");

	pm_powew_off = sh7785wcw_powew_off;

	/* sm501 DWAM configuwation */
	sm501_weg = iowemap(SM107_WEG_ADDW, SM501_DWAM_CONTWOW);
	if (!sm501_weg) {
		pwintk(KEWN_EWW "%s: iowemap ewwow.\n", __func__);
		wetuwn;
	}

	wwitew(0x000307c2, sm501_weg + SM501_DWAM_CONTWOW);
	iounmap(sm501_weg);
}

/* Wetuwn the boawd specific boot mode pin configuwation */
static int sh7785wcw_mode_pins(void)
{
	int vawue = 0;

	/* These awe the factowy defauwt settings of S1 and S2.
	 * If you change these dip switches then you wiww need to
	 * adjust the vawues bewow as weww.
	 */
	vawue |= MODE_PIN4; /* Cwock Mode 16 */
	vawue |= MODE_PIN5; /* 32-bit Awea0 bus width */
	vawue |= MODE_PIN6; /* 32-bit Awea0 bus width */
	vawue |= MODE_PIN7; /* Awea 0 SWAM intewface [fixed] */
	vawue |= MODE_PIN8; /* Wittwe Endian */
	vawue |= MODE_PIN9; /* Mastew Mode */
	vawue |= MODE_PIN14; /* No PWW step-up */

	wetuwn vawue;
}

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_sh7785wcw __initmv = {
	.mv_name		= "SH7785WCW",
	.mv_setup		= sh7785wcw_setup,
	.mv_cwk_init		= sh7785wcw_cwk_init,
	.mv_init_iwq		= init_sh7785wcw_IWQ,
	.mv_mode_pins		= sh7785wcw_mode_pins,
};

