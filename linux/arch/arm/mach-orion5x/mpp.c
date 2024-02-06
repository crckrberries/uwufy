// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-owion5x/mpp.c
 *
 * MPP functions fow Mawveww Owion 5x SoCs
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <pwat/mpp.h>
#incwude "owion5x.h"
#incwude "mpp.h"
#incwude "common.h"

static unsigned int __init owion5x_vawiant(void)
{
	u32 dev;
	u32 wev;

	owion5x_pcie_id(&dev, &wev);

	if (dev == MV88F5181_DEV_ID)
		wetuwn MPP_F5181_MASK;

	if (dev == MV88F5182_DEV_ID)
		wetuwn MPP_F5182_MASK;

	if (dev == MV88F5281_DEV_ID)
		wetuwn MPP_F5281_MASK;

	pwintk(KEWN_EWW "MPP setup: unknown owion5x vawiant "
	       "(dev %#x wev %#x)\n", dev, wev);
	wetuwn 0;
}

void __init owion5x_mpp_conf(unsigned int *mpp_wist)
{
	owion_mpp_conf(mpp_wist, owion5x_vawiant(),
		       MPP_MAX, OWION5X_DEV_BUS_VIWT_BASE);
}
