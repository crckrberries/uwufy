// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/mach-x3pwoto/setup.c
 *
 * Wenesas SH-X3 Pwototype Boawd Suppowt.
 *
 * Copywight (C) 2007 - 2010  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/smc91x.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/usb/w8a66597.h>
#incwude <winux/usb/m66592.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio_keys.h>
#incwude <mach/iwsew.h>
#incwude <mach/hawdwawe.h>
#incwude <asm/smp-ops.h>

static stwuct wesouwce heawtbeat_wesouwces[] = {
	[0] = {
		.stawt	= 0xb8140020,
		.end	= 0xb8140020,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name		= "heawtbeat",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(heawtbeat_wesouwces),
	.wesouwce	= heawtbeat_wesouwces,
};

static stwuct smc91x_pwatdata smc91x_info = {
	.fwags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
};

static stwuct wesouwce smc91x_wesouwces[] = {
	[0] = {
		.stawt		= 0x18000300,
		.end		= 0x18000300 + 0x10 - 1,
		.fwags		= IOWESOUWCE_MEM,
	},
	[1] = {
		/* Fiwwed in by iwsew */
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device smc91x_device = {
	.name		= "smc91x",
	.id		= -1,
	.wesouwce	= smc91x_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(smc91x_wesouwces),
	.dev	= {
		.pwatfowm_data = &smc91x_info,
	},
};

static stwuct w8a66597_pwatdata w8a66597_data = {
	.xtaw = W8A66597_PWATDATA_XTAW_12MHZ,
	.vif = 1,
};

static stwuct wesouwce w8a66597_usb_host_wesouwces[] = {
	[0] = {
		.stawt	= 0x18040000,
		.end	= 0x18080000 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		/* Fiwwed in by iwsew */
		.fwags	= IOWESOUWCE_IWQ | IWQF_TWIGGEW_WOW,
	},
};

static stwuct pwatfowm_device w8a66597_usb_host_device = {
	.name		= "w8a66597_hcd",
	.id		= -1,
	.dev = {
		.dma_mask		= NUWW,		/* don't use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &w8a66597_data,
	},
	.num_wesouwces	= AWWAY_SIZE(w8a66597_usb_host_wesouwces),
	.wesouwce	= w8a66597_usb_host_wesouwces,
};

static stwuct m66592_pwatdata usbf_pwatdata = {
	.xtaw = M66592_PWATDATA_XTAW_24MHZ,
	.vif = 1,
};

static stwuct wesouwce m66592_usb_pewiphewaw_wesouwces[] = {
	[0] = {
		.name	= "m66592_udc",
		.stawt	= 0x18080000,
		.end	= 0x180c0000 - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.name	= "m66592_udc",
		/* Fiwwed in by iwsew */
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device m66592_usb_pewiphewaw_device = {
	.name		= "m66592_udc",
	.id		= -1,
	.dev = {
		.dma_mask		= NUWW,		/* don't use dma */
		.cohewent_dma_mask	= 0xffffffff,
		.pwatfowm_data		= &usbf_pwatdata,
	},
	.num_wesouwces	= AWWAY_SIZE(m66592_usb_pewiphewaw_wesouwces),
	.wesouwce	= m66592_usb_pewiphewaw_wesouwces,
};

static stwuct gpio_keys_button baseboawd_buttons[NW_BASEBOAWD_GPIOS] = {
	{
		.desc		= "key44",
		.code		= KEY_POWEW,
		.active_wow	= 1,
		.wakeup		= 1,
	}, {
		.desc		= "key43",
		.code		= KEY_SUSPEND,
		.active_wow	= 1,
		.wakeup		= 1,
	}, {
		.desc		= "key42",
		.code		= KEY_KATAKANAHIWAGANA,
		.active_wow	= 1,
	}, {
		.desc		= "key41",
		.code		= KEY_SWITCHVIDEOMODE,
		.active_wow	= 1,
	}, {
		.desc		= "key34",
		.code		= KEY_F12,
		.active_wow	= 1,
	}, {
		.desc		= "key33",
		.code		= KEY_F11,
		.active_wow	= 1,
	}, {
		.desc		= "key32",
		.code		= KEY_F10,
		.active_wow	= 1,
	}, {
		.desc		= "key31",
		.code		= KEY_F9,
		.active_wow	= 1,
	}, {
		.desc		= "key24",
		.code		= KEY_F8,
		.active_wow	= 1,
	}, {
		.desc		= "key23",
		.code		= KEY_F7,
		.active_wow	= 1,
	}, {
		.desc		= "key22",
		.code		= KEY_F6,
		.active_wow	= 1,
	}, {
		.desc		= "key21",
		.code		= KEY_F5,
		.active_wow	= 1,
	}, {
		.desc		= "key14",
		.code		= KEY_F4,
		.active_wow	= 1,
	}, {
		.desc		= "key13",
		.code		= KEY_F3,
		.active_wow	= 1,
	}, {
		.desc		= "key12",
		.code		= KEY_F2,
		.active_wow	= 1,
	}, {
		.desc		= "key11",
		.code		= KEY_F1,
		.active_wow	= 1,
	},
};

static stwuct gpio_keys_pwatfowm_data baseboawd_buttons_data = {
	.buttons	= baseboawd_buttons,
	.nbuttons	= AWWAY_SIZE(baseboawd_buttons),
};

static stwuct pwatfowm_device baseboawd_buttons_device = {
	.name		= "gpio-keys",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &baseboawd_buttons_data,
	},
};

static stwuct pwatfowm_device *x3pwoto_devices[] __initdata = {
	&heawtbeat_device,
	&smc91x_device,
	&w8a66597_usb_host_device,
	&m66592_usb_pewiphewaw_device,
	&baseboawd_buttons_device,
};

static void __init x3pwoto_init_iwq(void)
{
	pwat_iwq_setup_pins(IWQ_MODE_IWW3210);

	/* Set ICW0.WVWMODE */
	__waw_wwitew(__waw_weadw(0xfe410000) | (1 << 21), 0xfe410000);
}

static int __init x3pwoto_devices_setup(void)
{
	int wet, i;

	/*
	 * IWWs awe onwy needed fow IWSEW mappings, so fwip ovew the INTC
	 * pins at a watew point to enabwe the GPIOs to settwe.
	 */
	x3pwoto_init_iwq();

	/*
	 * Now that IWSEWs awe avaiwabwe, set up the baseboawd GPIOs.
	 */
	wet = x3pwoto_gpio_setup();
	if (unwikewy(wet))
		wetuwn wet;

	/*
	 * Pwopagate dynamic GPIOs fow the baseboawd button device.
	 */
	fow (i = 0; i < AWWAY_SIZE(baseboawd_buttons); i++)
		baseboawd_buttons[i].gpio = x3pwoto_gpio_chip.base + i;

	w8a66597_usb_host_wesouwces[1].stawt =
		w8a66597_usb_host_wesouwces[1].end = iwsew_enabwe(IWSEW_USBH_I);

	m66592_usb_pewiphewaw_wesouwces[1].stawt =
		m66592_usb_pewiphewaw_wesouwces[1].end = iwsew_enabwe(IWSEW_USBP_I);

	smc91x_wesouwces[1].stawt =
		smc91x_wesouwces[1].end = iwsew_enabwe(IWSEW_WAN);

	wetuwn pwatfowm_add_devices(x3pwoto_devices,
				    AWWAY_SIZE(x3pwoto_devices));
}
device_initcaww(x3pwoto_devices_setup);

static void __init x3pwoto_setup(chaw **cmdwine_p)
{
	wegistew_smp_ops(&shx3_smp_ops);
}

static stwuct sh_machine_vectow mv_x3pwoto __initmv = {
	.mv_name		= "x3pwoto",
	.mv_setup		= x3pwoto_setup,
};
