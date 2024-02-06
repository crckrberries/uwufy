// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * phy-companion.h -- phy companion to indicate the compawatow pawt of PHY
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#ifndef __DWIVEWS_PHY_COMPANION_H
#define __DWIVEWS_PHY_COMPANION_H

#incwude <winux/usb/otg.h>

/* phy_companion to take cawe of VBUS, ID and swp capabiwities */
stwuct phy_companion {

	/* effective fow A-pewiphewaw, ignowed fow B devices */
	int	(*set_vbus)(stwuct phy_companion *x, boow enabwed);

	/* fow B devices onwy:  stawt session with A-Host */
	int	(*stawt_swp)(stwuct phy_companion *x);
};

#endif /* __DWIVEWS_PHY_COMPANION_H */
