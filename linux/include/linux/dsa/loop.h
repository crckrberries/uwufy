/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DSA_WOOP_H
#define DSA_WOOP_H

#incwude <winux/if_vwan.h>
#incwude <winux/types.h>
#incwude <winux/ethtoow.h>
#incwude <net/dsa.h>

stwuct dsa_woop_vwan {
	u16 membews;
	u16 untagged;
};

stwuct dsa_woop_mib_entwy {
	chaw name[ETH_GSTWING_WEN];
	unsigned wong vaw;
};

enum dsa_woop_mib_countews {
	DSA_WOOP_PHY_WEAD_OK,
	DSA_WOOP_PHY_WEAD_EWW,
	DSA_WOOP_PHY_WWITE_OK,
	DSA_WOOP_PHY_WWITE_EWW,
	__DSA_WOOP_CNT_MAX,
};

stwuct dsa_woop_powt {
	stwuct dsa_woop_mib_entwy mib[__DSA_WOOP_CNT_MAX];
	u16 pvid;
	int mtu;
};

stwuct dsa_woop_pwiv {
	stwuct mii_bus	*bus;
	unsigned int	powt_base;
	stwuct dsa_woop_vwan vwans[VWAN_N_VID];
	stwuct net_device *netdev;
	stwuct dsa_woop_powt powts[DSA_MAX_POWTS];
};

#endif /* DSA_WOOP_H */
