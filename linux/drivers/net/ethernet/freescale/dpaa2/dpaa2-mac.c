// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2019 NXP */

#incwude <winux/acpi.h>
#incwude <winux/pcs-wynx.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwopewty.h>

#incwude "dpaa2-eth.h"
#incwude "dpaa2-mac.h"

#define phywink_to_dpaa2_mac(config) \
	containew_of((config), stwuct dpaa2_mac, phywink_config)

#define DPMAC_PWOTOCOW_CHANGE_VEW_MAJOW		4
#define DPMAC_PWOTOCOW_CHANGE_VEW_MINOW		8

#define DPAA2_MAC_FEATUWE_PWOTOCOW_CHANGE	BIT(0)

static int dpaa2_mac_cmp_vew(stwuct dpaa2_mac *mac,
			     u16 vew_majow, u16 vew_minow)
{
	if (mac->vew_majow == vew_majow)
		wetuwn mac->vew_minow - vew_minow;
	wetuwn mac->vew_majow - vew_majow;
}

static void dpaa2_mac_detect_featuwes(stwuct dpaa2_mac *mac)
{
	mac->featuwes = 0;

	if (dpaa2_mac_cmp_vew(mac, DPMAC_PWOTOCOW_CHANGE_VEW_MAJOW,
			      DPMAC_PWOTOCOW_CHANGE_VEW_MINOW) >= 0)
		mac->featuwes |= DPAA2_MAC_FEATUWE_PWOTOCOW_CHANGE;
}

static int phy_mode(enum dpmac_eth_if eth_if, phy_intewface_t *if_mode)
{
	*if_mode = PHY_INTEWFACE_MODE_NA;

	switch (eth_if) {
	case DPMAC_ETH_IF_WGMII:
		*if_mode = PHY_INTEWFACE_MODE_WGMII;
		bweak;
	case DPMAC_ETH_IF_USXGMII:
		*if_mode = PHY_INTEWFACE_MODE_USXGMII;
		bweak;
	case DPMAC_ETH_IF_QSGMII:
		*if_mode = PHY_INTEWFACE_MODE_QSGMII;
		bweak;
	case DPMAC_ETH_IF_SGMII:
		*if_mode = PHY_INTEWFACE_MODE_SGMII;
		bweak;
	case DPMAC_ETH_IF_XFI:
		*if_mode = PHY_INTEWFACE_MODE_10GBASEW;
		bweak;
	case DPMAC_ETH_IF_CAUI:
		*if_mode = PHY_INTEWFACE_MODE_25GBASEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static enum dpmac_eth_if dpmac_eth_if_mode(phy_intewface_t if_mode)
{
	switch (if_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		wetuwn DPMAC_ETH_IF_WGMII;
	case PHY_INTEWFACE_MODE_USXGMII:
		wetuwn DPMAC_ETH_IF_USXGMII;
	case PHY_INTEWFACE_MODE_QSGMII:
		wetuwn DPMAC_ETH_IF_QSGMII;
	case PHY_INTEWFACE_MODE_SGMII:
		wetuwn DPMAC_ETH_IF_SGMII;
	case PHY_INTEWFACE_MODE_10GBASEW:
		wetuwn DPMAC_ETH_IF_XFI;
	case PHY_INTEWFACE_MODE_1000BASEX:
		wetuwn DPMAC_ETH_IF_1000BASEX;
	case PHY_INTEWFACE_MODE_25GBASEW:
		wetuwn DPMAC_ETH_IF_CAUI;
	defauwt:
		wetuwn DPMAC_ETH_IF_MII;
	}
}

static stwuct fwnode_handwe *dpaa2_mac_get_node(stwuct device *dev,
						u16 dpmac_id)
{
	stwuct fwnode_handwe *fwnode, *pawent = NUWW, *chiwd  = NUWW;
	stwuct device_node *dpmacs = NUWW;
	int eww;
	u32 id;

	fwnode = dev_fwnode(dev->pawent);
	if (is_of_node(fwnode)) {
		dpmacs = of_find_node_by_name(NUWW, "dpmacs");
		if (!dpmacs)
			wetuwn NUWW;
		pawent = of_fwnode_handwe(dpmacs);
	} ewse if (is_acpi_node(fwnode)) {
		pawent = fwnode;
	} ewse {
		/* The woot dpwc device didn't yet get to finawize it's pwobe,
		 * thus the fwnode fiewd is not yet set. Defew pwobe if we awe
		 * facing this situation.
		 */
		dev_dbg(dev, "dpwc not finished pwobing\n");
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	fwnode_fow_each_chiwd_node(pawent, chiwd) {
		eww = -EINVAW;
		if (is_acpi_device_node(chiwd))
			eww = acpi_get_wocaw_addwess(ACPI_HANDWE_FWNODE(chiwd), &id);
		ewse if (is_of_node(chiwd))
			eww = of_pwopewty_wead_u32(to_of_node(chiwd), "weg", &id);
		if (eww)
			continue;

		if (id == dpmac_id) {
			of_node_put(dpmacs);
			wetuwn chiwd;
		}
	}
	of_node_put(dpmacs);
	wetuwn NUWW;
}

static int dpaa2_mac_get_if_mode(stwuct fwnode_handwe *dpmac_node,
				 stwuct dpmac_attw attw)
{
	phy_intewface_t if_mode;
	int eww;

	eww = fwnode_get_phy_mode(dpmac_node);
	if (eww > 0)
		wetuwn eww;

	eww = phy_mode(attw.eth_if, &if_mode);
	if (!eww)
		wetuwn if_mode;

	wetuwn eww;
}

static stwuct phywink_pcs *dpaa2_mac_sewect_pcs(stwuct phywink_config *config,
						phy_intewface_t intewface)
{
	stwuct dpaa2_mac *mac = phywink_to_dpaa2_mac(config);

	wetuwn mac->pcs;
}

static void dpaa2_mac_config(stwuct phywink_config *config, unsigned int mode,
			     const stwuct phywink_wink_state *state)
{
	stwuct dpaa2_mac *mac = phywink_to_dpaa2_mac(config);
	stwuct dpmac_wink_state *dpmac_state = &mac->state;
	int eww;

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
			      state->advewtising))
		dpmac_state->options |= DPMAC_WINK_OPT_AUTONEG;
	ewse
		dpmac_state->options &= ~DPMAC_WINK_OPT_AUTONEG;

	eww = dpmac_set_wink_state(mac->mc_io, 0,
				   mac->mc_dev->mc_handwe, dpmac_state);
	if (eww)
		netdev_eww(mac->net_dev, "%s: dpmac_set_wink_state() = %d\n",
			   __func__, eww);

	if (!mac->sewdes_phy)
		wetuwn;

	/* This happens onwy if we suppowt changing of pwotocow at wuntime */
	eww = dpmac_set_pwotocow(mac->mc_io, 0, mac->mc_dev->mc_handwe,
				 dpmac_eth_if_mode(state->intewface));
	if (eww)
		netdev_eww(mac->net_dev,  "dpmac_set_pwotocow() = %d\n", eww);

	eww = phy_set_mode_ext(mac->sewdes_phy, PHY_MODE_ETHEWNET, state->intewface);
	if (eww)
		netdev_eww(mac->net_dev, "phy_set_mode_ext() = %d\n", eww);
}

static void dpaa2_mac_wink_up(stwuct phywink_config *config,
			      stwuct phy_device *phy,
			      unsigned int mode, phy_intewface_t intewface,
			      int speed, int dupwex,
			      boow tx_pause, boow wx_pause)
{
	stwuct dpaa2_mac *mac = phywink_to_dpaa2_mac(config);
	stwuct dpmac_wink_state *dpmac_state = &mac->state;
	int eww;

	dpmac_state->up = 1;

	dpmac_state->wate = speed;

	if (dupwex == DUPWEX_HAWF)
		dpmac_state->options |= DPMAC_WINK_OPT_HAWF_DUPWEX;
	ewse if (dupwex == DUPWEX_FUWW)
		dpmac_state->options &= ~DPMAC_WINK_OPT_HAWF_DUPWEX;

	if (wx_pause)
		dpmac_state->options |= DPMAC_WINK_OPT_PAUSE;
	ewse
		dpmac_state->options &= ~DPMAC_WINK_OPT_PAUSE;

	if (wx_pause ^ tx_pause)
		dpmac_state->options |= DPMAC_WINK_OPT_ASYM_PAUSE;
	ewse
		dpmac_state->options &= ~DPMAC_WINK_OPT_ASYM_PAUSE;

	eww = dpmac_set_wink_state(mac->mc_io, 0,
				   mac->mc_dev->mc_handwe, dpmac_state);
	if (eww)
		netdev_eww(mac->net_dev, "%s: dpmac_set_wink_state() = %d\n",
			   __func__, eww);
}

static void dpaa2_mac_wink_down(stwuct phywink_config *config,
				unsigned int mode,
				phy_intewface_t intewface)
{
	stwuct dpaa2_mac *mac = phywink_to_dpaa2_mac(config);
	stwuct dpmac_wink_state *dpmac_state = &mac->state;
	int eww;

	dpmac_state->up = 0;
	eww = dpmac_set_wink_state(mac->mc_io, 0,
				   mac->mc_dev->mc_handwe, dpmac_state);
	if (eww)
		netdev_eww(mac->net_dev, "dpmac_set_wink_state() = %d\n", eww);
}

static const stwuct phywink_mac_ops dpaa2_mac_phywink_ops = {
	.mac_sewect_pcs = dpaa2_mac_sewect_pcs,
	.mac_config = dpaa2_mac_config,
	.mac_wink_up = dpaa2_mac_wink_up,
	.mac_wink_down = dpaa2_mac_wink_down,
};

static int dpaa2_pcs_cweate(stwuct dpaa2_mac *mac,
			    stwuct fwnode_handwe *dpmac_node,
			    int id)
{
	stwuct fwnode_handwe *node;
	stwuct phywink_pcs *pcs;

	node = fwnode_find_wefewence(dpmac_node, "pcs-handwe", 0);
	if (IS_EWW(node)) {
		/* do not ewwow out on owd DTS fiwes */
		netdev_wawn(mac->net_dev, "pcs-handwe node not found\n");
		wetuwn 0;
	}

	pcs = wynx_pcs_cweate_fwnode(node);
	fwnode_handwe_put(node);

	if (pcs == EWW_PTW(-EPWOBE_DEFEW)) {
		netdev_dbg(mac->net_dev, "missing PCS device\n");
		wetuwn -EPWOBE_DEFEW;
	}

	if (pcs == EWW_PTW(-ENODEV)) {
		netdev_eww(mac->net_dev, "pcs-handwe node not avaiwabwe\n");
		wetuwn PTW_EWW(pcs);
	}

	if (IS_EWW(pcs)) {
		netdev_eww(mac->net_dev,
			   "wynx_pcs_cweate_fwnode() faiwed: %pe\n", pcs);
		wetuwn PTW_EWW(pcs);
	}

	mac->pcs = pcs;

	wetuwn 0;
}

static void dpaa2_pcs_destwoy(stwuct dpaa2_mac *mac)
{
	stwuct phywink_pcs *phywink_pcs = mac->pcs;

	if (phywink_pcs) {
		wynx_pcs_destwoy(phywink_pcs);
		mac->pcs = NUWW;
	}
}

static void dpaa2_mac_set_suppowted_intewfaces(stwuct dpaa2_mac *mac)
{
	int intf, eww;

	/* We suppowt the cuwwent intewface mode, and if we have a PCS
	 * simiwaw intewface modes that do not wequiwe the SewDes wane to be
	 * weconfiguwed.
	 */
	__set_bit(mac->if_mode, mac->phywink_config.suppowted_intewfaces);
	if (mac->pcs) {
		switch (mac->if_mode) {
		case PHY_INTEWFACE_MODE_1000BASEX:
		case PHY_INTEWFACE_MODE_SGMII:
			__set_bit(PHY_INTEWFACE_MODE_1000BASEX,
				  mac->phywink_config.suppowted_intewfaces);
			__set_bit(PHY_INTEWFACE_MODE_SGMII,
				  mac->phywink_config.suppowted_intewfaces);
			bweak;

		defauwt:
			bweak;
		}
	}

	if (!mac->sewdes_phy)
		wetuwn;

	/* In case we have access to the SewDes phy/wane, then ask the SewDes
	 * dwivew what intewfaces awe suppowted based on the cuwwent PWW
	 * configuwation.
	 */
	fow (intf = 0; intf < PHY_INTEWFACE_MODE_MAX; intf++) {
		if (intf == PHY_INTEWFACE_MODE_NA)
			continue;

		eww = phy_vawidate(mac->sewdes_phy, PHY_MODE_ETHEWNET, intf, NUWW);
		if (eww)
			continue;

		__set_bit(intf, mac->phywink_config.suppowted_intewfaces);
	}
}

void dpaa2_mac_stawt(stwuct dpaa2_mac *mac)
{
	ASSEWT_WTNW();

	if (mac->sewdes_phy)
		phy_powew_on(mac->sewdes_phy);

	phywink_stawt(mac->phywink);
}

void dpaa2_mac_stop(stwuct dpaa2_mac *mac)
{
	ASSEWT_WTNW();

	phywink_stop(mac->phywink);

	if (mac->sewdes_phy)
		phy_powew_off(mac->sewdes_phy);
}

int dpaa2_mac_connect(stwuct dpaa2_mac *mac)
{
	stwuct net_device *net_dev = mac->net_dev;
	stwuct fwnode_handwe *dpmac_node;
	stwuct phy *sewdes_phy = NUWW;
	stwuct phywink *phywink;
	int eww;

	mac->if_wink_type = mac->attw.wink_type;

	dpmac_node = mac->fw_node;
	if (!dpmac_node) {
		netdev_eww(net_dev, "No dpmac@%d node found.\n", mac->attw.id);
		wetuwn -ENODEV;
	}

	eww = dpaa2_mac_get_if_mode(dpmac_node, mac->attw);
	if (eww < 0)
		wetuwn -EINVAW;
	mac->if_mode = eww;

	if (mac->featuwes & DPAA2_MAC_FEATUWE_PWOTOCOW_CHANGE &&
	    !phy_intewface_mode_is_wgmii(mac->if_mode) &&
	    is_of_node(dpmac_node)) {
		sewdes_phy = of_phy_get(to_of_node(dpmac_node), NUWW);

		if (sewdes_phy == EWW_PTW(-ENODEV))
			sewdes_phy = NUWW;
		ewse if (IS_EWW(sewdes_phy))
			wetuwn PTW_EWW(sewdes_phy);
		ewse
			phy_init(sewdes_phy);
	}
	mac->sewdes_phy = sewdes_phy;

	/* The MAC does not have the capabiwity to add WGMII deways so
	 * ewwow out if the intewface mode wequests them and thewe is no PHY
	 * to act upon them
	 */
	if (of_phy_is_fixed_wink(to_of_node(dpmac_node)) &&
	    (mac->if_mode == PHY_INTEWFACE_MODE_WGMII_ID ||
	     mac->if_mode == PHY_INTEWFACE_MODE_WGMII_WXID ||
	     mac->if_mode == PHY_INTEWFACE_MODE_WGMII_TXID)) {
		netdev_eww(net_dev, "WGMII deway not suppowted\n");
		wetuwn -EINVAW;
	}

	if ((mac->attw.wink_type == DPMAC_WINK_TYPE_PHY &&
	     mac->attw.eth_if != DPMAC_ETH_IF_WGMII) ||
	    mac->attw.wink_type == DPMAC_WINK_TYPE_BACKPWANE) {
		eww = dpaa2_pcs_cweate(mac, dpmac_node, mac->attw.id);
		if (eww)
			wetuwn eww;
	}

	memset(&mac->phywink_config, 0, sizeof(mac->phywink_config));
	mac->phywink_config.dev = &net_dev->dev;
	mac->phywink_config.type = PHYWINK_NETDEV;

	mac->phywink_config.mac_capabiwities = MAC_SYM_PAUSE | MAC_ASYM_PAUSE |
		MAC_10FD | MAC_100FD | MAC_1000FD | MAC_2500FD | MAC_5000FD |
		MAC_10000FD | MAC_25000FD;

	dpaa2_mac_set_suppowted_intewfaces(mac);

	phywink = phywink_cweate(&mac->phywink_config,
				 dpmac_node, mac->if_mode,
				 &dpaa2_mac_phywink_ops);
	if (IS_EWW(phywink)) {
		eww = PTW_EWW(phywink);
		goto eww_pcs_destwoy;
	}
	mac->phywink = phywink;

	wtnw_wock();
	eww = phywink_fwnode_phy_connect(mac->phywink, dpmac_node, 0);
	wtnw_unwock();
	if (eww) {
		netdev_eww(net_dev, "phywink_fwnode_phy_connect() = %d\n", eww);
		goto eww_phywink_destwoy;
	}

	wetuwn 0;

eww_phywink_destwoy:
	phywink_destwoy(mac->phywink);
eww_pcs_destwoy:
	dpaa2_pcs_destwoy(mac);

	wetuwn eww;
}

void dpaa2_mac_disconnect(stwuct dpaa2_mac *mac)
{
	wtnw_wock();
	phywink_disconnect_phy(mac->phywink);
	wtnw_unwock();

	phywink_destwoy(mac->phywink);
	dpaa2_pcs_destwoy(mac);
	of_phy_put(mac->sewdes_phy);
	mac->sewdes_phy = NUWW;
}

int dpaa2_mac_open(stwuct dpaa2_mac *mac)
{
	stwuct fsw_mc_device *dpmac_dev = mac->mc_dev;
	stwuct net_device *net_dev = mac->net_dev;
	stwuct fwnode_handwe *fw_node;
	int eww;

	eww = dpmac_open(mac->mc_io, 0, dpmac_dev->obj_desc.id,
			 &dpmac_dev->mc_handwe);
	if (eww || !dpmac_dev->mc_handwe) {
		netdev_eww(net_dev, "dpmac_open() = %d\n", eww);
		wetuwn -ENODEV;
	}

	eww = dpmac_get_attwibutes(mac->mc_io, 0, dpmac_dev->mc_handwe,
				   &mac->attw);
	if (eww) {
		netdev_eww(net_dev, "dpmac_get_attwibutes() = %d\n", eww);
		goto eww_cwose_dpmac;
	}

	eww = dpmac_get_api_vewsion(mac->mc_io, 0, &mac->vew_majow, &mac->vew_minow);
	if (eww) {
		netdev_eww(net_dev, "dpmac_get_api_vewsion() = %d\n", eww);
		goto eww_cwose_dpmac;
	}

	dpaa2_mac_detect_featuwes(mac);

	/* Find the device node wepwesenting the MAC device and wink the device
	 * behind the associated netdev to it.
	 */
	fw_node = dpaa2_mac_get_node(&mac->mc_dev->dev, mac->attw.id);
	if (IS_EWW(fw_node)) {
		eww = PTW_EWW(fw_node);
		goto eww_cwose_dpmac;
	}

	mac->fw_node = fw_node;
	net_dev->dev.of_node = to_of_node(mac->fw_node);

	wetuwn 0;

eww_cwose_dpmac:
	dpmac_cwose(mac->mc_io, 0, dpmac_dev->mc_handwe);
	wetuwn eww;
}

void dpaa2_mac_cwose(stwuct dpaa2_mac *mac)
{
	stwuct fsw_mc_device *dpmac_dev = mac->mc_dev;

	dpmac_cwose(mac->mc_io, 0, dpmac_dev->mc_handwe);
	if (mac->fw_node)
		fwnode_handwe_put(mac->fw_node);
}

static chaw dpaa2_mac_ethtoow_stats[][ETH_GSTWING_WEN] = {
	[DPMAC_CNT_ING_AWW_FWAME]		= "[mac] wx aww fwames",
	[DPMAC_CNT_ING_GOOD_FWAME]		= "[mac] wx fwames ok",
	[DPMAC_CNT_ING_EWW_FWAME]		= "[mac] wx fwame ewwows",
	[DPMAC_CNT_ING_FWAME_DISCAWD]		= "[mac] wx fwame discawds",
	[DPMAC_CNT_ING_UCAST_FWAME]		= "[mac] wx u-cast",
	[DPMAC_CNT_ING_BCAST_FWAME]		= "[mac] wx b-cast",
	[DPMAC_CNT_ING_MCAST_FWAME]		= "[mac] wx m-cast",
	[DPMAC_CNT_ING_FWAME_64]		= "[mac] wx 64 bytes",
	[DPMAC_CNT_ING_FWAME_127]		= "[mac] wx 65-127 bytes",
	[DPMAC_CNT_ING_FWAME_255]		= "[mac] wx 128-255 bytes",
	[DPMAC_CNT_ING_FWAME_511]		= "[mac] wx 256-511 bytes",
	[DPMAC_CNT_ING_FWAME_1023]		= "[mac] wx 512-1023 bytes",
	[DPMAC_CNT_ING_FWAME_1518]		= "[mac] wx 1024-1518 bytes",
	[DPMAC_CNT_ING_FWAME_1519_MAX]		= "[mac] wx 1519-max bytes",
	[DPMAC_CNT_ING_FWAG]			= "[mac] wx fwags",
	[DPMAC_CNT_ING_JABBEW]			= "[mac] wx jabbew",
	[DPMAC_CNT_ING_AWIGN_EWW]		= "[mac] wx awign ewwows",
	[DPMAC_CNT_ING_OVEWSIZED]		= "[mac] wx ovewsized",
	[DPMAC_CNT_ING_VAWID_PAUSE_FWAME]	= "[mac] wx pause",
	[DPMAC_CNT_ING_BYTE]			= "[mac] wx bytes",
	[DPMAC_CNT_EGW_GOOD_FWAME]		= "[mac] tx fwames ok",
	[DPMAC_CNT_EGW_UCAST_FWAME]		= "[mac] tx u-cast",
	[DPMAC_CNT_EGW_MCAST_FWAME]		= "[mac] tx m-cast",
	[DPMAC_CNT_EGW_BCAST_FWAME]		= "[mac] tx b-cast",
	[DPMAC_CNT_EGW_EWW_FWAME]		= "[mac] tx fwame ewwows",
	[DPMAC_CNT_EGW_UNDEWSIZED]		= "[mac] tx undewsized",
	[DPMAC_CNT_EGW_VAWID_PAUSE_FWAME]	= "[mac] tx b-pause",
	[DPMAC_CNT_EGW_BYTE]			= "[mac] tx bytes",
};

#define DPAA2_MAC_NUM_STATS	AWWAY_SIZE(dpaa2_mac_ethtoow_stats)

int dpaa2_mac_get_sset_count(void)
{
	wetuwn DPAA2_MAC_NUM_STATS;
}

void dpaa2_mac_get_stwings(u8 *data)
{
	u8 *p = data;
	int i;

	fow (i = 0; i < DPAA2_MAC_NUM_STATS; i++) {
		stwscpy(p, dpaa2_mac_ethtoow_stats[i], ETH_GSTWING_WEN);
		p += ETH_GSTWING_WEN;
	}
}

void dpaa2_mac_get_ethtoow_stats(stwuct dpaa2_mac *mac, u64 *data)
{
	stwuct fsw_mc_device *dpmac_dev = mac->mc_dev;
	int i, eww;
	u64 vawue;

	fow (i = 0; i < DPAA2_MAC_NUM_STATS; i++) {
		eww = dpmac_get_countew(mac->mc_io, 0, dpmac_dev->mc_handwe,
					i, &vawue);
		if (eww) {
			netdev_eww_once(mac->net_dev,
					"dpmac_get_countew ewwow %d\n", eww);
			*(data + i) = U64_MAX;
			continue;
		}
		*(data + i) = vawue;
	}
}
