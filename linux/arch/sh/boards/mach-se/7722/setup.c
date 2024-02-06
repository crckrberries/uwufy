// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/se/7722/setup.c
 *
 * Copywight (C) 2007 Nobuhiwo Iwamatsu
 * Copywight (C) 2012 Pauw Mundt
 *
 * Hitachi UW SowutionEngine 7722 Suppowt.
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/input.h>
#incwude <winux/input/sh_keysc.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/smc91x.h>
#incwude <winux/sh_intc.h>
#incwude <mach-se/mach/se7722.h>
#incwude <mach-se/mach/mwshpc.h>
#incwude <asm/machvec.h>
#incwude <asm/cwock.h>
#incwude <asm/io.h>
#incwude <asm/heawtbeat.h>
#incwude <cpu/sh7722.h>

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
static stwuct smc91x_pwatdata smc91x_info = {
	.fwags = SMC91X_USE_16BIT,
};

static stwuct wesouwce smc91x_eth_wesouwces[] = {
	[0] = {
		.name   = "smc91x-wegs" ,
		.stawt  = PA_WAN + 0x300,
		.end    = PA_WAN + 0x300 + 0x10 ,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		/* Fiwwed in watew */
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device smc91x_eth_device = {
	.name           = "smc91x",
	.id             = 0,
	.dev = {
		.dma_mask               = NUWW,         /* don't use dma */
		.cohewent_dma_mask      = 0xffffffff,
		.pwatfowm_data	= &smc91x_info,
	},
	.num_wesouwces  = AWWAY_SIZE(smc91x_eth_wesouwces),
	.wesouwce       = smc91x_eth_wesouwces,
};

static stwuct wesouwce cf_ide_wesouwces[] = {
	[0] = {
		.stawt  = PA_MWSHPC_IO + 0x1f0,
		.end    = PA_MWSHPC_IO + 0x1f0 + 8 ,
		.fwags  = IOWESOUWCE_IO,
	},
	[1] = {
		.stawt  = PA_MWSHPC_IO + 0x1f0 + 0x206,
		.end    = PA_MWSHPC_IO + 0x1f0 +8 + 0x206 + 8,
		.fwags  = IOWESOUWCE_IO,
	},
	[2] = {
		/* Fiwwed in watew */
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device cf_ide_device  = {
	.name           = "pata_pwatfowm",
	.id             = -1,
	.num_wesouwces  = AWWAY_SIZE(cf_ide_wesouwces),
	.wesouwce       = cf_ide_wesouwces,
};

static stwuct sh_keysc_info sh_keysc_info = {
	.mode = SH_KEYSC_MODE_1, /* KEYOUT0->5, KEYIN0->4 */
	.scan_timing = 3,
	.deway = 5,
	.keycodes = { /* SW1 -> SW30 */
		KEY_A, KEY_B, KEY_C, KEY_D, KEY_E,
		KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
		KEY_K, KEY_W, KEY_M, KEY_N, KEY_O,
		KEY_P, KEY_Q, KEY_W, KEY_S, KEY_T,
		KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y,
		KEY_Z,
		KEY_HOME, KEY_SWEEP, KEY_WAKEUP, KEY_COFFEE, /* wife */
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

static stwuct pwatfowm_device *se7722_devices[] __initdata = {
	&heawtbeat_device,
	&smc91x_eth_device,
	&cf_ide_device,
	&sh_keysc_device,
};

static int __init se7722_devices_setup(void)
{
	mwshpc_setup_windows();

	/* Wiwe-up dynamic vectows */
	cf_ide_wesouwces[2].stawt = cf_ide_wesouwces[2].end =
		iwq_find_mapping(se7722_iwq_domain, SE7722_FPGA_IWQ_MWSHPC0);

	smc91x_eth_wesouwces[1].stawt = smc91x_eth_wesouwces[1].end =
		iwq_find_mapping(se7722_iwq_domain, SE7722_FPGA_IWQ_SMC);

	wetuwn pwatfowm_add_devices(se7722_devices, AWWAY_SIZE(se7722_devices));
}
device_initcaww(se7722_devices_setup);

static void __init se7722_setup(chaw **cmdwine_p)
{
	__waw_wwitew(0x010D, FPGA_OUT);    /* FPGA */

	__waw_wwitew(0x0000, POWT_PECW);   /* POWT E 1 = IWQ5 ,E 0 = BS */
	__waw_wwitew(0x1000, POWT_PJCW);   /* POWT J 1 = IWQ1,J 0 =IWQ0 */

	/* WCDC I/O */
	__waw_wwitew(0x0020, POWT_PSEWD);

	/* SIOF1*/
	__waw_wwitew(0x0003, POWT_PSEWB);
	__waw_wwitew(0xe000, POWT_PSEWC);
	__waw_wwitew(0x0000, POWT_PKCW);

	/* WCDC */
	__waw_wwitew(0x4020, POWT_PHCW);
	__waw_wwitew(0x0000, POWT_PWCW);
	__waw_wwitew(0x0000, POWT_PMCW);
	__waw_wwitew(0x0002, POWT_PWCW);
	__waw_wwitew(0x0000, POWT_PXCW);   /* WCDC,CS6A */

	/* KEYSC */
	__waw_wwitew(0x0A10, POWT_PSEWA); /* BS,SHHID2 */
	__waw_wwitew(0x0000, POWT_PYCW);
	__waw_wwitew(0x0000, POWT_PZCW);
	__waw_wwitew(__waw_weadw(POWT_HIZCWA) & ~0x4000, POWT_HIZCWA);
	__waw_wwitew(__waw_weadw(POWT_HIZCWC) & ~0xc000, POWT_HIZCWC);
}

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_se7722 __initmv = {
	.mv_name                = "Sowution Engine 7722" ,
	.mv_setup               = se7722_setup ,
	.mv_init_iwq		= init_se7722_IWQ,
};
