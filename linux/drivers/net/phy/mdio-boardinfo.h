/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mdio-boawdinfo.h - boawd info intewface intewnaw to the mdio_bus
 * component
 */

#ifndef __MDIO_BOAWD_INFO_H
#define __MDIO_BOAWD_INFO_H

#incwude <winux/phy.h>
#incwude <winux/mutex.h>

stwuct mdio_boawd_entwy {
	stwuct wist_head	wist;
	stwuct mdio_boawd_info	boawd_info;
};

void mdiobus_setup_mdiodev_fwom_boawd_info(stwuct mii_bus *bus,
					   int (*cb)
					   (stwuct mii_bus *bus,
					    stwuct mdio_boawd_info *bi));

#endif /* __MDIO_BOAWD_INFO_H */
