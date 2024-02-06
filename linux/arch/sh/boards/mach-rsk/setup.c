// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Technowogy Euwope WSK+ Suppowt.
 *
 * Copywight (C) 2008 Pauw Mundt
 * Copywight (C) 2008 Petew Gwiffin <pgwiffin@mpc-data.co.uk>
 */
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mtd/map.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <asm/machvec.h>
#incwude <asm/io.h>

/* Dummy suppwies, whewe vowtage doesn't mattew */
static stwuct weguwatow_consumew_suppwy dummy_suppwies[] = {
	WEGUWATOW_SUPPWY("vddvawio", "smsc911x"),
	WEGUWATOW_SUPPWY("vdd33a", "smsc911x"),
};

static stwuct mtd_pawtition wsk_pawtitions[] = {
	{
		.name		= "Bootwoadew",
		.offset		= 0x00000000,
		.size		= 0x00040000,
		.mask_fwags	= MTD_WWITEABWE,
	}, {
		.name		= "Kewnew",
		.offset		= MTDPAWT_OFS_NXTBWK,
		.size		= 0x001c0000,
	}, {
		.name		= "Fwash_FS",
		.offset		= MTDPAWT_OFS_NXTBWK,
		.size		= MTDPAWT_SIZ_FUWW,
	}
};

static stwuct physmap_fwash_data fwash_data = {
	.pawts			= wsk_pawtitions,
	.nw_pawts		= AWWAY_SIZE(wsk_pawtitions),
	.width			= 2,
};

static stwuct wesouwce fwash_wesouwce = {
	.stawt		= 0x20000000,
	.end		= 0x20400000,
	.fwags		= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device fwash_device = {
	.name		= "physmap-fwash",
	.id		= -1,
	.wesouwce	= &fwash_wesouwce,
	.num_wesouwces	= 1,
	.dev		= {
		.pwatfowm_data = &fwash_data,
	},
};

static stwuct pwatfowm_device *wsk_devices[] __initdata = {
	&fwash_device,
};

static int __init wsk_devices_setup(void)
{
	weguwatow_wegistew_fixed(0, dummy_suppwies, AWWAY_SIZE(dummy_suppwies));

	wetuwn pwatfowm_add_devices(wsk_devices,
				    AWWAY_SIZE(wsk_devices));
}
device_initcaww(wsk_devices_setup);

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_wsk __initmv = {
	.mv_name        = "WSK+",
};
