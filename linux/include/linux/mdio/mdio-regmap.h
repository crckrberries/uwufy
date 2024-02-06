/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Dwivew fow MMIO-Mapped MDIO devices. Some IPs expose intewnaw PHYs ow PCS
 * within the MMIO-mapped awea
 *
 * Copywight (C) 2023 Maxime Chevawwiew <maxime.chevawwiew@bootwin.com>
 */
#ifndef MDIO_WEGMAP_H
#define MDIO_WEGMAP_H

#incwude <winux/phy.h>

stwuct device;
stwuct wegmap;

stwuct mdio_wegmap_config {
	stwuct device *pawent;
	stwuct wegmap *wegmap;
	chaw name[MII_BUS_ID_SIZE];
	u8 vawid_addw;
	boow autoscan;
};

stwuct mii_bus *devm_mdio_wegmap_wegistew(stwuct device *dev,
					  const stwuct mdio_wegmap_config *config);

#endif
