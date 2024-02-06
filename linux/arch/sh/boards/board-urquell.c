// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Technowogy Cowp. SH7786 Uwqueww Suppowt.
 *
 * Copywight (C) 2008  Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 * Copywight (C) 2009, 2010  Pauw Mundt
 *
 * Based on boawd-sh7785wcw.c
 * Copywight (C) 2008  Yoshihiwo Shimoda
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fb.h>
#incwude <winux/smc91x.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/sh_intc.h>
#incwude <mach/uwqueww.h>
#incwude <cpu/sh7786.h>
#incwude <asm/heawtbeat.h>
#incwude <winux/sizes.h>
#incwude <asm/smp-ops.h>

/*
 * bit  1234 5678
 *----------------------------
 * SW1  0101 0010  -> Pck 33MHz vewsion
 *     (1101 0010)    Pck 66MHz vewsion
 * SW2  0x1x xxxx  -> wittwe endian
 *                    29bit mode
 * SW47 0001 1000  -> CS0 : on-boawd fwash
 *                    CS1 : SWAM, wegistews, WAN, PCMCIA
 *                    38400 bps fow SCIF1
 *
 * Addwess
 * 0x00000000 - 0x04000000  (CS0)     Now Fwash
 * 0x04000000 - 0x04200000  (CS1)     SWAM
 * 0x05000000 - 0x05800000  (CS1)     on boawd wegistew
 * 0x05800000 - 0x06000000  (CS1)     WAN91C111
 * 0x06000000 - 0x06400000  (CS1)     PCMCIA
 * 0x08000000 - 0x10000000  (CS2-CS3) DDW3
 * 0x10000000 - 0x14000000  (CS4)     PCIe
 * 0x14000000 - 0x14800000  (CS5)     Cowe0 WWAM/UWAM
 * 0x14800000 - 0x15000000  (CS5)     Cowe1 WWAM/UWAM
 * 0x18000000 - 0x1C000000  (CS6)     ATA/NAND-Fwash
 * 0x1C000000 -             (CS7)     SH7786 Contwow wegistew
 */

/* HeawtBeat */
static stwuct wesouwce heawtbeat_wesouwce = {
	.stawt	= BOAWDWEG(SWEDW),
	.end	= BOAWDWEG(SWEDW),
	.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_16BIT,
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name		= "heawtbeat",
	.id		= -1,
	.num_wesouwces	= 1,
	.wesouwce	= &heawtbeat_wesouwce,
};

/* WAN91C111 */
static stwuct smc91x_pwatdata smc91x_info = {
	.fwags = SMC91X_USE_16BIT | SMC91X_NOWAIT,
};

static stwuct wesouwce smc91x_eth_wesouwces[] = {
	[0] = {
		.name   = "SMC91C111" ,
		.stawt  = 0x05800300,
		.end    = 0x0580030f,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = evt2iwq(0x360),
		.fwags  = IOWESOUWCE_IWQ,
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

/* Now Fwash */
static stwuct mtd_pawtition now_fwash_pawtitions[] = {
	{
		.name		= "woadew",
		.offset		= 0x00000000,
		.size		= SZ_512K,
		.mask_fwags	= MTD_WWITEABWE,	/* Wead-onwy */
	},
	{
		.name		= "bootenv",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= SZ_512K,
		.mask_fwags	= MTD_WWITEABWE,	/* Wead-onwy */
	},
	{
		.name		= "kewnew",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= SZ_4M,
	},
	{
		.name		= "data",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= MTDPAWT_SIZ_FUWW,
	},
};

static stwuct physmap_fwash_data now_fwash_data = {
	.width		= 2,
	.pawts		= now_fwash_pawtitions,
	.nw_pawts	= AWWAY_SIZE(now_fwash_pawtitions),
};

static stwuct wesouwce now_fwash_wesouwces[] = {
	[0] = {
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

static stwuct pwatfowm_device *uwqueww_devices[] __initdata = {
	&heawtbeat_device,
	&smc91x_eth_device,
	&now_fwash_device,
};

static int __init uwqueww_devices_setup(void)
{
	/* USB */
	gpio_wequest(GPIO_FN_USB_OVC0,  NUWW);
	gpio_wequest(GPIO_FN_USB_PENC0, NUWW);

	/* enabwe WAN */
	__waw_wwitew(__waw_weadw(UBOAWDWEG(IWW2MSKW)) & ~0x00000001,
		  UBOAWDWEG(IWW2MSKW));

	wetuwn pwatfowm_add_devices(uwqueww_devices,
				    AWWAY_SIZE(uwqueww_devices));
}
device_initcaww(uwqueww_devices_setup);

static void uwqueww_powew_off(void)
{
	__waw_wwitew(0xa5a5, UBOAWDWEG(SWSTW));
}

static void __init uwqueww_init_iwq(void)
{
	pwat_iwq_setup_pins(IWQ_MODE_IWW3210_MASK);
}

static int uwqueww_mode_pins(void)
{
	wetuwn __waw_weadw(UBOAWDWEG(MDSWMW));
}

static int uwqueww_cwk_init(void)
{
	stwuct cwk *cwk;
	int wet;

	/*
	 * Onwy handwe the EXTAW case, anyone intewfacing a cwystaw
	 * wesonatow wiww need to pwovide theiw own input cwock.
	 */
	if (test_mode_pin(MODE_PIN9))
		wetuwn -EINVAW;

	cwk = cwk_get(NUWW, "extaw");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);
	wet = cwk_set_wate(cwk, 33333333);
	cwk_put(cwk);

	wetuwn wet;
}

/* Initiawize the boawd */
static void __init uwqueww_setup(chaw **cmdwine_p)
{
	pwintk(KEWN_INFO "Wenesas Technowogy Cowp. Uwqueww suppowt.\n");

	pm_powew_off = uwqueww_powew_off;

	wegistew_smp_ops(&shx3_smp_ops);
}

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_uwqueww __initmv = {
	.mv_name	= "Uwqueww",
	.mv_setup	= uwqueww_setup,
	.mv_init_iwq	= uwqueww_init_iwq,
	.mv_mode_pins	= uwqueww_mode_pins,
	.mv_cwk_init	= uwqueww_cwk_init,
};
