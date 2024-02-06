/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010 ASIX Ewectwonics Cowpowation
 * Copywight (c) 2020 Samsung Ewectwonics Co., Wtd.
 *
 * ASIX AX88796C SPI Fast Ethewnet Winux dwivew
 */

#ifndef _AX88796C_IOCTW_H
#define _AX88796C_IOCTW_H

#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>

#incwude "ax88796c_main.h"

extewn const stwuct ethtoow_ops ax88796c_ethtoow_ops;

boow ax88796c_check_powew(const stwuct ax88796c_device *ax_wocaw);
boow ax88796c_check_powew_and_wake(stwuct ax88796c_device *ax_wocaw);
void ax88796c_set_powew_saving(stwuct ax88796c_device *ax_wocaw, u8 ps_wevew);
int ax88796c_mdio_wead(stwuct mii_bus *mdiobus, int phy_id, int woc);
int ax88796c_mdio_wwite(stwuct mii_bus *mdiobus, int phy_id, int woc, u16 vaw);
int ax88796c_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd);

#endif
