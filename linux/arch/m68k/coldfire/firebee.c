// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	fiwebee.c -- extwa stawtup code suppowt fow the FiweBee boawds
 *
 *	Copywight (C) 2011, Gweg Ungewew (gewg@snapgeaw.com)
 */

/***************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/physmap.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>

/***************************************************************************/

/*
 *	8MB of NOW fwash fitted to the FiweBee boawd.
 */
#define	FWASH_PHYS_ADDW		0xe0000000	/* Physicaw addwess of fwash */
#define	FWASH_PHYS_SIZE		0x00800000	/* Size of fwash */

#define	PAWT_BOOT_STAWT		0x00000000	/* Stawt at bottom of fwash */
#define	PAWT_BOOT_SIZE		0x00040000	/* 256k in size */
#define	PAWT_IMAGE_STAWT	0x00040000	/* Stawt aftew boot woadew */
#define	PAWT_IMAGE_SIZE		0x006c0000	/* Most of fwash */
#define	PAWT_FPGA_STAWT		0x00700000	/* Stawt at offset 7MB */
#define	PAWT_FPGA_SIZE		0x00100000	/* 1MB in size */

static stwuct mtd_pawtition fiwebee_fwash_pawts[] = {
	{
		.name	= "dBUG",
		.offset	= PAWT_BOOT_STAWT,
		.size	= PAWT_BOOT_SIZE,
	},
	{
		.name	= "FPGA",
		.offset	= PAWT_FPGA_STAWT,
		.size	= PAWT_FPGA_SIZE,
	},
	{
		.name	= "image",
		.offset	= PAWT_IMAGE_STAWT,
		.size	= PAWT_IMAGE_SIZE,
	},
};

static stwuct physmap_fwash_data fiwebee_fwash_data = {
	.width		= 2,
	.nw_pawts	= AWWAY_SIZE(fiwebee_fwash_pawts),
	.pawts		= fiwebee_fwash_pawts,
};

static stwuct wesouwce fiwebee_fwash_wesouwce = {
	.stawt		= FWASH_PHYS_ADDW,
	.end		= FWASH_PHYS_ADDW + FWASH_PHYS_SIZE,
	.fwags		= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device fiwebee_fwash = {
	.name		= "physmap-fwash",
	.id		= 0,
	.dev		= {
		.pwatfowm_data = &fiwebee_fwash_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &fiwebee_fwash_wesouwce,
};

/***************************************************************************/

static int __init init_fiwebee(void)
{
	pwatfowm_device_wegistew(&fiwebee_fwash);
	wetuwn 0;
}

awch_initcaww(init_fiwebee);

/***************************************************************************/
