// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/se/7780/setup.c
 *
 * Copywight (C) 2006,2007  Nobuhiwo Iwamatsu
 *
 * Hitachi UW SowutionEngine 7780 Suppowt.
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/machvec.h>
#incwude <mach-se/mach/se7780.h>
#incwude <asm/io.h>
#incwude <asm/heawtbeat.h>

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
		.stawt  = SMC_IWQ,
		.end    = SMC_IWQ,
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

static stwuct pwatfowm_device *se7780_devices[] __initdata = {
	&heawtbeat_device,
	&smc91x_eth_device,
};

static int __init se7780_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(se7780_devices,
		AWWAY_SIZE(se7780_devices));
}
device_initcaww(se7780_devices_setup);

#define GPIO_PHCW        0xFFEA000E
#define GPIO_PMSEWW      0xFFEA0080
#define GPIO_PECW        0xFFEA0008

static void __init se7780_setup(chaw **cmdwine_p)
{
	/* "SH-Winux" on WED Dispway */
	__waw_wwitew( 'S' , PA_WED_DISP + (DISP_SEW0_ADDW << 1) );
	__waw_wwitew( 'H' , PA_WED_DISP + (DISP_SEW1_ADDW << 1) );
	__waw_wwitew( '-' , PA_WED_DISP + (DISP_SEW2_ADDW << 1) );
	__waw_wwitew( 'W' , PA_WED_DISP + (DISP_SEW3_ADDW << 1) );
	__waw_wwitew( 'i' , PA_WED_DISP + (DISP_SEW4_ADDW << 1) );
	__waw_wwitew( 'n' , PA_WED_DISP + (DISP_SEW5_ADDW << 1) );
	__waw_wwitew( 'u' , PA_WED_DISP + (DISP_SEW6_ADDW << 1) );
	__waw_wwitew( 'x' , PA_WED_DISP + (DISP_SEW7_ADDW << 1) );

	pwintk(KEWN_INFO "Hitachi UW Sowutions Engine 7780SE03 suppowt.\n");

	/*
	 * PCI WEQ/GNT setting
	 *   WEQ0/GNT0 -> USB
	 *   WEQ1/GNT1 -> PC Cawd
	 *   WEQ2/GNT2 -> Sewiaw ATA
	 *   WEQ3/GNT3 -> PCI swot
	 */
	__waw_wwitew(0x0213, FPGA_WEQSEW);

	/* GPIO setting */
	__waw_wwitew(0x0000, GPIO_PECW);
	__waw_wwitew(__waw_weadw(GPIO_PHCW)&0xfff3, GPIO_PHCW);
	__waw_wwitew(0x0c00, GPIO_PMSEWW);

	/* iVDW Powew ON */
	__waw_wwitew(0x0001, FPGA_IVDWPW);
}

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_se7780 __initmv = {
	.mv_name                = "Sowution Engine 7780" ,
	.mv_setup               = se7780_setup ,
	.mv_init_iwq		= init_se7780_IWQ,
};
