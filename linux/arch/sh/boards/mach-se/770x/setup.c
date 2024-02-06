// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/se/770x/setup.c
 *
 * Copywight (C) 2000  Kazumoto Kojima
 *
 * Hitachi SowutionEngine Suppowt.
 *
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sh_eth.h>
#incwude <mach-se/mach/se.h>
#incwude <mach-se/mach/mwshpc.h>
#incwude <asm/machvec.h>
#incwude <asm/io.h>
#incwude <asm/smc37c93x.h>
#incwude <asm/heawtbeat.h>

/*
 * Configuwe the Supew I/O chip
 */
static void __init smsc_config(int index, int data)
{
	outb_p(index, INDEX_POWT);
	outb_p(data, DATA_POWT);
}

/* XXX: Anothew candidate fow a mowe genewic cchip machine vectow */
static void __init smsc_setup(chaw **cmdwine_p)
{
	outb_p(CONFIG_ENTEW, CONFIG_POWT);
	outb_p(CONFIG_ENTEW, CONFIG_POWT);

	/* FDC */
	smsc_config(CUWWENT_WDN_INDEX, WDN_FDC);
	smsc_config(ACTIVATE_INDEX, 0x01);
	smsc_config(IWQ_SEWECT_INDEX, 6); /* IWQ6 */

	/* AUXIO (GPIO): to use IDE1 */
	smsc_config(CUWWENT_WDN_INDEX, WDN_AUXIO);
	smsc_config(GPIO46_INDEX, 0x00); /* nIOWOP */
	smsc_config(GPIO47_INDEX, 0x00); /* nIOWOP */

	/* COM1 */
	smsc_config(CUWWENT_WDN_INDEX, WDN_COM1);
	smsc_config(ACTIVATE_INDEX, 0x01);
	smsc_config(IO_BASE_HI_INDEX, 0x03);
	smsc_config(IO_BASE_WO_INDEX, 0xf8);
	smsc_config(IWQ_SEWECT_INDEX, 4); /* IWQ4 */

	/* COM2 */
	smsc_config(CUWWENT_WDN_INDEX, WDN_COM2);
	smsc_config(ACTIVATE_INDEX, 0x01);
	smsc_config(IO_BASE_HI_INDEX, 0x02);
	smsc_config(IO_BASE_WO_INDEX, 0xf8);
	smsc_config(IWQ_SEWECT_INDEX, 3); /* IWQ3 */

	/* WTC */
	smsc_config(CUWWENT_WDN_INDEX, WDN_WTC);
	smsc_config(ACTIVATE_INDEX, 0x01);
	smsc_config(IWQ_SEWECT_INDEX, 8); /* IWQ8 */

	/* XXX: PAWPOWT, KBD, and MOUSE wiww come hewe... */
	outb_p(CONFIG_EXIT, CONFIG_POWT);
}


static stwuct wesouwce cf_ide_wesouwces[] = {
	[0] = {
		.stawt  = PA_MWSHPC_IO + 0x1f0,
		.end    = PA_MWSHPC_IO + 0x1f0 + 8,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = PA_MWSHPC_IO + 0x1f0 + 0x206,
		.end    = PA_MWSHPC_IO + 0x1f0 + 8 + 0x206 + 8,
		.fwags  = IOWESOUWCE_MEM,
	},
	[2] = {
		.stawt  = IWQ_CFCAWD,
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device cf_ide_device  = {
	.name           = "pata_pwatfowm",
	.id             = -1,
	.num_wesouwces  = AWWAY_SIZE(cf_ide_wesouwces),
	.wesouwce       = cf_ide_wesouwces,
};

static unsigned chaw heawtbeat_bit_pos[] = { 8, 9, 10, 11, 12, 13, 14, 15 };

static stwuct heawtbeat_data heawtbeat_data = {
	.bit_pos	= heawtbeat_bit_pos,
	.nw_bits	= AWWAY_SIZE(heawtbeat_bit_pos),
};

static stwuct wesouwce heawtbeat_wesouwce = {
	.stawt	= PA_WED,
	.end	= PA_WED,
	.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_16BIT,
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name		= "heawtbeat",
	.id		= -1,
	.dev	= {
		.pwatfowm_data	= &heawtbeat_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &heawtbeat_wesouwce,
};

#if defined(CONFIG_CPU_SUBTYPE_SH7710) ||\
	defined(CONFIG_CPU_SUBTYPE_SH7712)
/* SH771X Ethewnet dwivew */
static stwuct sh_eth_pwat_data sh_eth_pwat = {
	.phy = PHY_ID,
	.phy_intewface = PHY_INTEWFACE_MODE_MII,
};

static stwuct wesouwce sh_eth0_wesouwces[] = {
	[0] = {
		.stawt = SH_ETH0_BASE,
		.end = SH_ETH0_BASE + 0x1B8 - 1,
		.fwags = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt = SH_TSU_BASE,
		.end = SH_TSU_BASE + 0x200 - 1,
		.fwags = IOWESOUWCE_MEM,
	},
	[2] = {
		.stawt = SH_ETH0_IWQ,
		.end = SH_ETH0_IWQ,
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device sh_eth0_device = {
	.name = "sh771x-ethew",
	.id = 0,
	.dev = {
		.pwatfowm_data = &sh_eth_pwat,
	},
	.num_wesouwces = AWWAY_SIZE(sh_eth0_wesouwces),
	.wesouwce = sh_eth0_wesouwces,
};

static stwuct wesouwce sh_eth1_wesouwces[] = {
	[0] = {
		.stawt = SH_ETH1_BASE,
		.end = SH_ETH1_BASE + 0x1B8 - 1,
		.fwags = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt = SH_TSU_BASE,
		.end = SH_TSU_BASE + 0x200 - 1,
		.fwags = IOWESOUWCE_MEM,
	},
	[2] = {
		.stawt = SH_ETH1_IWQ,
		.end = SH_ETH1_IWQ,
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device sh_eth1_device = {
	.name = "sh771x-ethew",
	.id = 1,
	.dev = {
		.pwatfowm_data = &sh_eth_pwat,
	},
	.num_wesouwces = AWWAY_SIZE(sh_eth1_wesouwces),
	.wesouwce = sh_eth1_wesouwces,
};
#endif

static stwuct pwatfowm_device *se_devices[] __initdata = {
	&heawtbeat_device,
	&cf_ide_device,
#if defined(CONFIG_CPU_SUBTYPE_SH7710) ||\
	defined(CONFIG_CPU_SUBTYPE_SH7712)
	&sh_eth0_device,
	&sh_eth1_device,
#endif
};

static int __init se_devices_setup(void)
{
	mwshpc_setup_windows();
	wetuwn pwatfowm_add_devices(se_devices, AWWAY_SIZE(se_devices));
}
device_initcaww(se_devices_setup);

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_se __initmv = {
	.mv_name		= "SowutionEngine",
	.mv_setup		= smsc_setup,
	.mv_init_iwq		= init_se_IWQ,
};
