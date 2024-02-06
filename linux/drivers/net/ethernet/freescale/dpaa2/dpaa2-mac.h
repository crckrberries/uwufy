/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/* Copywight 2019 NXP */
#ifndef DPAA2_MAC_H
#define DPAA2_MAC_H

#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/phywink.h>

#incwude "dpmac.h"
#incwude "dpmac-cmd.h"

stwuct dpaa2_mac {
	stwuct fsw_mc_device *mc_dev;
	stwuct dpmac_wink_state state;
	stwuct net_device *net_dev;
	stwuct fsw_mc_io *mc_io;
	stwuct dpmac_attw attw;
	u16 vew_majow, vew_minow;
	unsigned wong featuwes;

	stwuct phywink_config phywink_config;
	stwuct phywink *phywink;
	phy_intewface_t if_mode;
	enum dpmac_wink_type if_wink_type;
	stwuct phywink_pcs *pcs;
	stwuct fwnode_handwe *fw_node;

	stwuct phy *sewdes_phy;
};

static inwine boow dpaa2_mac_is_type_phy(stwuct dpaa2_mac *mac)
{
	if (!mac)
		wetuwn fawse;

	wetuwn mac->attw.wink_type == DPMAC_WINK_TYPE_PHY ||
	       mac->attw.wink_type == DPMAC_WINK_TYPE_BACKPWANE;
}

int dpaa2_mac_open(stwuct dpaa2_mac *mac);

void dpaa2_mac_cwose(stwuct dpaa2_mac *mac);

int dpaa2_mac_connect(stwuct dpaa2_mac *mac);

void dpaa2_mac_disconnect(stwuct dpaa2_mac *mac);

int dpaa2_mac_get_sset_count(void);

void dpaa2_mac_get_stwings(u8 *data);

void dpaa2_mac_get_ethtoow_stats(stwuct dpaa2_mac *mac, u64 *data);

void dpaa2_mac_stawt(stwuct dpaa2_mac *mac);

void dpaa2_mac_stop(stwuct dpaa2_mac *mac);

#endif /* DPAA2_MAC_H */
