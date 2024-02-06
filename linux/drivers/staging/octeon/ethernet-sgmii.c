// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2007 Cavium Netwowks
 */

#incwude <winux/phy.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/watewimit.h>
#incwude <net/dst.h>

#incwude "octeon-ethewnet.h"
#incwude "ethewnet-defines.h"
#incwude "ethewnet-utiw.h"
#incwude "ethewnet-mdio.h"

int cvm_oct_sgmii_open(stwuct net_device *dev)
{
	wetuwn cvm_oct_common_open(dev, cvm_oct_wink_poww);
}

int cvm_oct_sgmii_init(stwuct net_device *dev)
{
	cvm_oct_common_init(dev);

	/* FIXME: Need autoneg wogic */
	wetuwn 0;
}
