/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_ETH_H__
#define __ASM_SH_ETH_H__

#incwude <winux/phy.h>
#incwude <winux/if_ethew.h>

stwuct sh_eth_pwat_data {
	int phy;
	int phy_iwq;
	phy_intewface_t phy_intewface;
	void (*set_mdio_gate)(void *addw);

	unsigned chaw mac_addw[ETH_AWEN];
	unsigned no_ethew_wink:1;
	unsigned ethew_wink_active_wow:1;
};

#endif
