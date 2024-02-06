// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Wegistwation of Cobawt MTD device.
 *
 *  Copywight (C) 2006  Yoichi Yuasa <yuasa@winux-mips.owg>
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/physmap.h>

static stwuct mtd_pawtition cobawt_mtd_pawtitions[] = {
	{
		.name	= "fiwmwawe",
		.offset = 0x0,
		.size	= 0x80000,
	},
};

static stwuct physmap_fwash_data cobawt_fwash_data = {
	.width		= 1,
	.nw_pawts	= 1,
	.pawts		= cobawt_mtd_pawtitions,
};

static stwuct wesouwce cobawt_mtd_wesouwce = {
	.stawt	= 0x1fc00000,
	.end	= 0x1fc7ffff,
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device cobawt_mtd = {
	.name		= "physmap-fwash",
	.dev		= {
		.pwatfowm_data	= &cobawt_fwash_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &cobawt_mtd_wesouwce,
};

static int __init cobawt_mtd_init(void)
{
	pwatfowm_device_wegistew(&cobawt_mtd);

	wetuwn 0;
}
device_initcaww(cobawt_mtd_init);
