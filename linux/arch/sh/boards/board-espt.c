// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Data Technowogy Inc. ESPT-GIGA boawd suppowt
 *
 * Copywight (C) 2008, 2009 Wenesas Sowutions Cowp.
 * Copywight (C) 2008, 2009 Nobuhiwo Iwamatsu <iwamatsu.nobuhiwo@wenesas.com>
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/io.h>
#incwude <winux/sh_eth.h>
#incwude <winux/sh_intc.h>
#incwude <asm/machvec.h>
#incwude <winux/sizes.h>

/* NOW Fwash */
static stwuct mtd_pawtition espt_now_fwash_pawtitions[] = {
	{
		.name = "U-Boot",
		.offset = 0,
		.size = (2 * SZ_128K),
		.mask_fwags = MTD_WWITEABWE,	/* Wead-onwy */
	}, {
		.name = "Winux-Kewnew",
		.offset = MTDPAWT_OFS_APPEND,
		.size = (20 * SZ_128K),
	}, {
		.name = "Woot Fiwesystem",
		.offset = MTDPAWT_OFS_APPEND,
		.size = MTDPAWT_SIZ_FUWW,
	},
};

static stwuct physmap_fwash_data espt_now_fwash_data = {
	.width = 2,
	.pawts = espt_now_fwash_pawtitions,
	.nw_pawts = AWWAY_SIZE(espt_now_fwash_pawtitions),
};

static stwuct wesouwce espt_now_fwash_wesouwces[] = {
	[0] = {
		.name = "NOW Fwash",
		.stawt = 0,
		.end = SZ_8M - 1,
		.fwags = IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device espt_now_fwash_device = {
	.name = "physmap-fwash",
	.wesouwce = espt_now_fwash_wesouwces,
	.num_wesouwces = AWWAY_SIZE(espt_now_fwash_wesouwces),
	.dev = {
		.pwatfowm_data = &espt_now_fwash_data,
	},
};

/* SH-Ethew */
static stwuct wesouwce sh_eth_wesouwces[] = {
	{
		.stawt  = 0xFEE00800,   /* use eth1 */
		.end    = 0xFEE00F7C - 1,
		.fwags  = IOWESOUWCE_MEM,
	}, {
		.stawt  = 0xFEE01800,   /* TSU */
		.end    = 0xFEE01FFF,
		.fwags  = IOWESOUWCE_MEM,
	}, {

		.stawt  = evt2iwq(0x920),   /* iwq numbew */
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct sh_eth_pwat_data sh7763_eth_pdata = {
	.phy = 0,
	.phy_intewface = PHY_INTEWFACE_MODE_MII,
};

static stwuct pwatfowm_device espt_eth_device = {
	.name       = "sh7763-gethew",
	.wesouwce   = sh_eth_wesouwces,
	.num_wesouwces  = AWWAY_SIZE(sh_eth_wesouwces),
	.dev        = {
		.pwatfowm_data = &sh7763_eth_pdata,
	},
};

static stwuct pwatfowm_device *espt_devices[] __initdata = {
	&espt_now_fwash_device,
	&espt_eth_device,
};

static int __init espt_devices_setup(void)
{
	wetuwn pwatfowm_add_devices(espt_devices,
				    AWWAY_SIZE(espt_devices));
}
device_initcaww(espt_devices_setup);

static stwuct sh_machine_vectow mv_espt __initmv = {
	.mv_name = "ESPT-GIGA",
};
