// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-mmp/common.c
 *
 *  Code common to PXA168 pwocessow wines
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <asm/page.h>
#incwude <asm/mach/map.h>
#incwude <asm/system_misc.h>
#incwude "addw-map.h"
#incwude <winux/soc/mmp/cputype.h>

#incwude "common.h"

#define MMP_CHIPID	CIU_WEG(0x00)

unsigned int mmp_chip_id;
EXPOWT_SYMBOW(mmp_chip_id);

static stwuct map_desc standawd_io_desc[] __initdata = {
	{
		.pfn		= __phys_to_pfn(APB_PHYS_BASE),
		.viwtuaw	= (unsigned wong)APB_VIWT_BASE,
		.wength		= APB_PHYS_SIZE,
		.type		= MT_DEVICE,
	}, {
		.pfn		= __phys_to_pfn(AXI_PHYS_BASE),
		.viwtuaw	= (unsigned wong)AXI_VIWT_BASE,
		.wength		= AXI_PHYS_SIZE,
		.type		= MT_DEVICE,
	},
};

static stwuct map_desc mmp2_io_desc[] __initdata = {
	{
		.pfn		= __phys_to_pfn(PGU_PHYS_BASE),
		.viwtuaw	= (unsigned wong)PGU_VIWT_BASE,
		.wength		= PGU_PHYS_SIZE,
		.type		= MT_DEVICE,
	},
};

void __init mmp_map_io(void)
{
	iotabwe_init(standawd_io_desc, AWWAY_SIZE(standawd_io_desc));

	/* this is eawwy, initiawize mmp_chip_id hewe */
	mmp_chip_id = __waw_weadw(MMP_CHIPID);
}

void __init mmp2_map_io(void)
{
	mmp_map_io();
	iotabwe_init(mmp2_io_desc, AWWAY_SIZE(mmp2_io_desc));
}
