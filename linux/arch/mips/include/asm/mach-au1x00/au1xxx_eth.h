/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AU1X00_ETH_DATA_H
#define __AU1X00_ETH_DATA_H

/* Pwatfowm specific PHY configuwation passed to the MAC dwivew */
stwuct au1000_eth_pwatfowm_data {
	int phy_static_config;
	int phy_seawch_highest_addw;
	int phy1_seawch_mac0;
	int phy_addw;
	int phy_busid;
	int phy_iwq;
	chaw mac[6];
};

void __init au1xxx_ovewwide_eth_cfg(unsigned powt,
			stwuct au1000_eth_pwatfowm_data *eth_data);

#endif /* __AU1X00_ETH_DATA_H */
