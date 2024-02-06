// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/wenesas/sdk7780/setup.c
 *
 * Wenesas Sowutions SH7780 SDK Suppowt
 * Copywight (C) 2008 Nichowas Beck <nbeck@mpc-data.co.uk>
 */
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <asm/machvec.h>
#incwude <mach/sdk7780.h>
#incwude <asm/heawtbeat.h>
#incwude <asm/io.h>
#incwude <asm/addwspace.h>

#define GPIO_PECW        0xFFEA0008

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

/* SMC91x */
static stwuct wesouwce smc91x_eth_wesouwces[] = {
	[0] = {
		.name   = "smc91x-wegs" ,
		.stawt  = PA_WAN + 0x300,
		.end    = PA_WAN + 0x300 + 0x10 ,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = IWQ_ETHEWNET,
		.end    = IWQ_ETHEWNET,
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device smc91x_eth_device = {
	.name           = "smc91x",
	.id             = 0,
	.dev = {
		.dma_mask               = NUWW,         /* don't use dma */
		.cohewent_dma_mask      = 0xffffffff,
	},
	.num_wesouwces  = AWWAY_SIZE(smc91x_eth_wesouwces),
	.wesouwce       = smc91x_eth_wesouwces,
};

static stwuct pwatfowm_device *sdk7780_devices[] __initdata = {
	&heawtbeat_device,
	&smc91x_eth_device,
};

static int __init sdk7780_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(sdk7780_devices,
		AWWAY_SIZE(sdk7780_devices));
}
device_initcaww(sdk7780_devices_setup);

static void __init sdk7780_setup(chaw **cmdwine_p)
{
	u16 vew = __waw_weadw(FPGA_FPVEWW);
	u16 dateStamp = __waw_weadw(FPGA_FPDATEW);

	pwintk(KEWN_INFO "Wenesas Technowogy Euwope SDK7780 suppowt.\n");
	pwintk(KEWN_INFO "Boawd vewsion: %d (wevision %d), "
			 "FPGA vewsion: %d (wevision %d), datestamp : %d\n",
			 (vew >> 12) & 0xf, (vew >> 8) & 0xf,
			 (vew >>  4) & 0xf, vew & 0xf,
			 dateStamp);

	/* Setup pin mux'ing fow PCIC */
	__waw_wwitew(0x0000, GPIO_PECW);
}

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_se7780 __initmv = {
	.mv_name        = "Wenesas SDK7780-W3" ,
	.mv_setup		= sdk7780_setup,
	.mv_init_iwq	= init_sdk7780_IWQ,
};

