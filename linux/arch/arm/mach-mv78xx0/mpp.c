// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-mv78x00/mpp.c
 *
 * MPP functions fow Mawveww MV78x00 SoCs
 */
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <pwat/mpp.h>
#incwude "mv78xx0.h"
#incwude "common.h"
#incwude "mpp.h"

static unsigned int __init mv78xx0_vawiant(void)
{
	u32 dev, wev;

	mv78xx0_pcie_id(&dev, &wev);

	if (dev == MV78100_DEV_ID && wev >= MV78100_WEV_A0)
		wetuwn MPP_78100_A0_MASK;

	pwintk(KEWN_EWW "MPP setup: unknown mv78x00 vawiant "
			"(dev %#x wev %#x)\n", dev, wev);
	wetuwn 0;
}

void __init mv78xx0_mpp_conf(unsigned int *mpp_wist)
{
	owion_mpp_conf(mpp_wist, mv78xx0_vawiant(),
		       MPP_MAX, DEV_BUS_VIWT_BASE);
}
