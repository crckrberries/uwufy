/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew */
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#ifndef __MEMAC_H
#define __MEMAC_H

#incwude "fman_mac.h"

#incwude <winux/netdevice.h>
#incwude <winux/phy_fixed.h>

stwuct mac_device;

int memac_initiawization(stwuct mac_device *mac_dev,
			 stwuct device_node *mac_node,
			 stwuct fman_mac_pawams *pawams);

#endif /* __MEMAC_H */
