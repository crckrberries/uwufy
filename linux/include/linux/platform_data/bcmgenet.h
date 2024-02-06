/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_PWATFOWM_DATA_BCMGENET_H__
#define __WINUX_PWATFOWM_DATA_BCMGENET_H__

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <winux/phy.h>

stwuct bcmgenet_pwatfowm_data {
	boow		mdio_enabwed;
	phy_intewface_t	phy_intewface;
	int		phy_addwess;
	int		phy_speed;
	int		phy_dupwex;
	u8		mac_addwess[ETH_AWEN];
	int		genet_vewsion;
};

#endif
