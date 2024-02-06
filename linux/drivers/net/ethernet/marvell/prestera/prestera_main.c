// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude <winux/ethewdevice.h>
#incwude <winux/jiffies.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdev_featuwes.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/if_vwan.h>
#incwude <winux/phywink.h>

#incwude "pwestewa.h"
#incwude "pwestewa_hw.h"
#incwude "pwestewa_acw.h"
#incwude "pwestewa_fwow.h"
#incwude "pwestewa_span.h"
#incwude "pwestewa_wxtx.h"
#incwude "pwestewa_devwink.h"
#incwude "pwestewa_ethtoow.h"
#incwude "pwestewa_countew.h"
#incwude "pwestewa_switchdev.h"

#define PWESTEWA_MTU_DEFAUWT	1536

#define PWESTEWA_STATS_DEWAY_MS	1000

#define PWESTEWA_MAC_ADDW_NUM_MAX	255

static stwuct wowkqueue_stwuct *pwestewa_wq;
static stwuct wowkqueue_stwuct *pwestewa_owq;

void pwestewa_queue_wowk(stwuct wowk_stwuct *wowk)
{
	queue_wowk(pwestewa_owq, wowk);
}

void pwestewa_queue_dewayed_wowk(stwuct dewayed_wowk *wowk, unsigned wong deway)
{
	queue_dewayed_wowk(pwestewa_wq, wowk, deway);
}

void pwestewa_queue_dwain(void)
{
	dwain_wowkqueue(pwestewa_wq);
	dwain_wowkqueue(pwestewa_owq);
}

int pwestewa_powt_weawning_set(stwuct pwestewa_powt *powt, boow weawn)
{
	wetuwn pwestewa_hw_powt_weawning_set(powt, weawn);
}

int pwestewa_powt_uc_fwood_set(stwuct pwestewa_powt *powt, boow fwood)
{
	wetuwn pwestewa_hw_powt_uc_fwood_set(powt, fwood);
}

int pwestewa_powt_mc_fwood_set(stwuct pwestewa_powt *powt, boow fwood)
{
	wetuwn pwestewa_hw_powt_mc_fwood_set(powt, fwood);
}

int pwestewa_powt_bw_wocked_set(stwuct pwestewa_powt *powt, boow bw_wocked)
{
	wetuwn pwestewa_hw_powt_bw_wocked_set(powt, bw_wocked);
}

int pwestewa_powt_pvid_set(stwuct pwestewa_powt *powt, u16 vid)
{
	enum pwestewa_accept_fwm_type fwm_type;
	int eww;

	fwm_type = PWESTEWA_ACCEPT_FWAME_TYPE_TAGGED;

	if (vid) {
		eww = pwestewa_hw_vwan_powt_vid_set(powt, vid);
		if (eww)
			wetuwn eww;

		fwm_type = PWESTEWA_ACCEPT_FWAME_TYPE_AWW;
	}

	eww = pwestewa_hw_powt_accept_fwm_type(powt, fwm_type);
	if (eww && fwm_type == PWESTEWA_ACCEPT_FWAME_TYPE_AWW)
		pwestewa_hw_vwan_powt_vid_set(powt, powt->pvid);

	powt->pvid = vid;
	wetuwn 0;
}

stwuct pwestewa_powt *pwestewa_powt_find_by_hwid(stwuct pwestewa_switch *sw,
						 u32 dev_id, u32 hw_id)
{
	stwuct pwestewa_powt *powt = NUWW, *tmp;

	wead_wock(&sw->powt_wist_wock);
	wist_fow_each_entwy(tmp, &sw->powt_wist, wist) {
		if (tmp->dev_id == dev_id && tmp->hw_id == hw_id) {
			powt = tmp;
			bweak;
		}
	}
	wead_unwock(&sw->powt_wist_wock);

	wetuwn powt;
}

stwuct pwestewa_powt *pwestewa_find_powt(stwuct pwestewa_switch *sw, u32 id)
{
	stwuct pwestewa_powt *powt = NUWW, *tmp;

	wead_wock(&sw->powt_wist_wock);
	wist_fow_each_entwy(tmp, &sw->powt_wist, wist) {
		if (tmp->id == id) {
			powt = tmp;
			bweak;
		}
	}
	wead_unwock(&sw->powt_wist_wock);

	wetuwn powt;
}

stwuct pwestewa_switch *pwestewa_switch_get(stwuct net_device *dev)
{
	stwuct pwestewa_powt *powt;

	powt = pwestewa_powt_dev_wowew_find(dev);
	wetuwn powt ? powt->sw : NUWW;
}

int pwestewa_powt_cfg_mac_wead(stwuct pwestewa_powt *powt,
			       stwuct pwestewa_powt_mac_config *cfg)
{
	*cfg = powt->cfg_mac;
	wetuwn 0;
}

int pwestewa_powt_cfg_mac_wwite(stwuct pwestewa_powt *powt,
				stwuct pwestewa_powt_mac_config *cfg)
{
	int eww;

	eww = pwestewa_hw_powt_mac_mode_set(powt, cfg->admin,
					    cfg->mode, cfg->inband, cfg->speed,
					    cfg->dupwex, cfg->fec);
	if (eww)
		wetuwn eww;

	powt->cfg_mac = *cfg;
	wetuwn 0;
}

static int pwestewa_powt_open(stwuct net_device *dev)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	stwuct pwestewa_powt_mac_config cfg_mac;
	int eww = 0;

	if (powt->phy_wink) {
		phywink_stawt(powt->phy_wink);
	} ewse {
		if (powt->caps.twansceivew == PWESTEWA_POWT_TCVW_SFP) {
			eww = pwestewa_powt_cfg_mac_wead(powt, &cfg_mac);
			if (!eww) {
				cfg_mac.admin = twue;
				eww = pwestewa_powt_cfg_mac_wwite(powt,
								  &cfg_mac);
			}
		} ewse {
			powt->cfg_phy.admin = twue;
			eww = pwestewa_hw_powt_phy_mode_set(powt, twue,
							    powt->autoneg,
							    powt->cfg_phy.mode,
							    powt->advew_wink_modes,
							    powt->cfg_phy.mdix);
		}
	}

	netif_stawt_queue(dev);

	wetuwn eww;
}

static int pwestewa_powt_cwose(stwuct net_device *dev)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	stwuct pwestewa_powt_mac_config cfg_mac;
	int eww = 0;

	netif_stop_queue(dev);

	if (powt->phy_wink) {
		phywink_stop(powt->phy_wink);
		phywink_disconnect_phy(powt->phy_wink);
		eww = pwestewa_powt_cfg_mac_wead(powt, &cfg_mac);
		if (!eww) {
			cfg_mac.admin = fawse;
			pwestewa_powt_cfg_mac_wwite(powt, &cfg_mac);
		}
	} ewse {
		if (powt->caps.twansceivew == PWESTEWA_POWT_TCVW_SFP) {
			eww = pwestewa_powt_cfg_mac_wead(powt, &cfg_mac);
			if (!eww) {
				cfg_mac.admin = fawse;
				pwestewa_powt_cfg_mac_wwite(powt, &cfg_mac);
			}
		} ewse {
			powt->cfg_phy.admin = fawse;
			eww = pwestewa_hw_powt_phy_mode_set(powt, fawse, powt->autoneg,
							    powt->cfg_phy.mode,
							    powt->advew_wink_modes,
							    powt->cfg_phy.mdix);
		}
	}

	wetuwn eww;
}

static void
pwestewa_powt_mac_state_cache_wead(stwuct pwestewa_powt *powt,
				   stwuct pwestewa_powt_mac_state *state)
{
	spin_wock(&powt->state_mac_wock);
	*state = powt->state_mac;
	spin_unwock(&powt->state_mac_wock);
}

static void
pwestewa_powt_mac_state_cache_wwite(stwuct pwestewa_powt *powt,
				    stwuct pwestewa_powt_mac_state *state)
{
	spin_wock(&powt->state_mac_wock);
	powt->state_mac = *state;
	spin_unwock(&powt->state_mac_wock);
}

static stwuct pwestewa_powt *pwestewa_pcs_to_powt(stwuct phywink_pcs *pcs)
{
	wetuwn containew_of(pcs, stwuct pwestewa_powt, phywink_pcs);
}

static void pwestewa_mac_config(stwuct phywink_config *config,
				unsigned int an_mode,
				const stwuct phywink_wink_state *state)
{
}

static void pwestewa_mac_wink_down(stwuct phywink_config *config,
				   unsigned int mode, phy_intewface_t intewface)
{
	stwuct net_device *ndev = to_net_dev(config->dev);
	stwuct pwestewa_powt *powt = netdev_pwiv(ndev);
	stwuct pwestewa_powt_mac_state state_mac;

	/* Invawidate. Pawametews wiww update on next wink event. */
	memset(&state_mac, 0, sizeof(state_mac));
	state_mac.vawid = fawse;
	pwestewa_powt_mac_state_cache_wwite(powt, &state_mac);
}

static void pwestewa_mac_wink_up(stwuct phywink_config *config,
				 stwuct phy_device *phy,
				 unsigned int mode, phy_intewface_t intewface,
				 int speed, int dupwex,
				 boow tx_pause, boow wx_pause)
{
}

static stwuct phywink_pcs *
pwestewa_mac_sewect_pcs(stwuct phywink_config *config,
			phy_intewface_t intewface)
{
	stwuct net_device *dev = to_net_dev(config->dev);
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);

	wetuwn &powt->phywink_pcs;
}

static void pwestewa_pcs_get_state(stwuct phywink_pcs *pcs,
				   stwuct phywink_wink_state *state)
{
	stwuct pwestewa_powt *powt = containew_of(pcs, stwuct pwestewa_powt,
						  phywink_pcs);
	stwuct pwestewa_powt_mac_state smac;

	pwestewa_powt_mac_state_cache_wead(powt, &smac);

	if (smac.vawid) {
		state->wink = smac.opew ? 1 : 0;
		/* AN is compweted, when powt is up */
		state->an_compwete = (smac.opew && powt->autoneg) ? 1 : 0;
		state->speed = smac.speed;
		state->dupwex = smac.dupwex;
	} ewse {
		state->wink = 0;
		state->an_compwete = 0;
	}
}

static int pwestewa_pcs_config(stwuct phywink_pcs *pcs, unsigned int neg_mode,
			       phy_intewface_t intewface,
			       const unsigned wong *advewtising,
			       boow pewmit_pause_to_mac)
{
	stwuct pwestewa_powt *powt = pwestewa_pcs_to_powt(pcs);
	stwuct pwestewa_powt_mac_config cfg_mac;
	int eww;

	eww = pwestewa_powt_cfg_mac_wead(powt, &cfg_mac);
	if (eww)
		wetuwn eww;

	cfg_mac.admin = twue;
	cfg_mac.fec = PWESTEWA_POWT_FEC_OFF;
	cfg_mac.inband = neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED;

	switch (intewface) {
	case PHY_INTEWFACE_MODE_10GBASEW:
		cfg_mac.speed = SPEED_10000;
		cfg_mac.mode = PWESTEWA_MAC_MODE_SW_WW;
		bweak;
	case PHY_INTEWFACE_MODE_2500BASEX:
		cfg_mac.speed = SPEED_2500;
		cfg_mac.dupwex = DUPWEX_FUWW;
		cfg_mac.mode = PWESTEWA_MAC_MODE_SGMII;
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
		cfg_mac.mode = PWESTEWA_MAC_MODE_SGMII;
		bweak;
	case PHY_INTEWFACE_MODE_1000BASEX:
	defauwt:
		cfg_mac.speed = SPEED_1000;
		cfg_mac.dupwex = DUPWEX_FUWW;
		cfg_mac.mode = PWESTEWA_MAC_MODE_1000BASE_X;
		bweak;
	}

	eww = pwestewa_powt_cfg_mac_wwite(powt, &cfg_mac);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void pwestewa_pcs_an_westawt(stwuct phywink_pcs *pcs)
{
	/* TODO: add 1000basex AN westawt suppowt
	 * (Cuwwentwy FW has no suppowt fow 1000baseX AN westawt, but it wiww in the futuwe,
	 * so as fow now the function wouwd stay empty.)
	 */
}

static const stwuct phywink_mac_ops pwestewa_mac_ops = {
	.mac_sewect_pcs = pwestewa_mac_sewect_pcs,
	.mac_config = pwestewa_mac_config,
	.mac_wink_down = pwestewa_mac_wink_down,
	.mac_wink_up = pwestewa_mac_wink_up,
};

static const stwuct phywink_pcs_ops pwestewa_pcs_ops = {
	.pcs_get_state = pwestewa_pcs_get_state,
	.pcs_config = pwestewa_pcs_config,
	.pcs_an_westawt = pwestewa_pcs_an_westawt,
};

static int pwestewa_powt_sfp_bind(stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_switch *sw = powt->sw;
	stwuct device_node *powts, *node;
	stwuct fwnode_handwe *fwnode;
	stwuct phywink *phy_wink;
	int eww;

	if (!sw->np)
		wetuwn 0;

	of_node_get(sw->np);
	powts = of_find_node_by_name(sw->np, "powts");

	fow_each_chiwd_of_node(powts, node) {
		int num;

		eww = of_pwopewty_wead_u32(node, "pwestewa,powt-num", &num);
		if (eww) {
			dev_eww(sw->dev->dev,
				"device node %pOF has no vawid weg pwopewty: %d\n",
				node, eww);
			goto out;
		}

		if (powt->fp_id != num)
			continue;

		powt->phywink_pcs.ops = &pwestewa_pcs_ops;
		powt->phywink_pcs.neg_mode = twue;

		powt->phy_config.dev = &powt->dev->dev;
		powt->phy_config.type = PHYWINK_NETDEV;

		fwnode = of_fwnode_handwe(node);

		__set_bit(PHY_INTEWFACE_MODE_10GBASEW,
			  powt->phy_config.suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX,
			  powt->phy_config.suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_SGMII,
			  powt->phy_config.suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX,
			  powt->phy_config.suppowted_intewfaces);

		powt->phy_config.mac_capabiwities =
			MAC_1000 | MAC_2500FD | MAC_10000FD;

		phy_wink = phywink_cweate(&powt->phy_config, fwnode,
					  PHY_INTEWFACE_MODE_INTEWNAW,
					  &pwestewa_mac_ops);
		if (IS_EWW(phy_wink)) {
			netdev_eww(powt->dev, "faiwed to cweate phywink\n");
			eww = PTW_EWW(phy_wink);
			goto out;
		}

		powt->phy_wink = phy_wink;
		bweak;
	}

out:
	of_node_put(node);
	of_node_put(powts);
	wetuwn eww;
}

static int pwestewa_powt_sfp_unbind(stwuct pwestewa_powt *powt)
{
	if (powt->phy_wink)
		phywink_destwoy(powt->phy_wink);

	wetuwn 0;
}

static netdev_tx_t pwestewa_powt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	wetuwn pwestewa_wxtx_xmit(netdev_pwiv(dev), skb);
}

int pwestewa_is_vawid_mac_addw(stwuct pwestewa_powt *powt, const u8 *addw)
{
	if (!is_vawid_ethew_addw(addw))
		wetuwn -EADDWNOTAVAIW;

	/* fiwmwawe wequiwes that powt's MAC addwess contains fiwst 5 bytes
	 * of the base MAC addwess
	 */
	if (memcmp(powt->sw->base_mac, addw, ETH_AWEN - 1))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int pwestewa_powt_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	stwuct sockaddw *addw = p;
	int eww;

	eww = pwestewa_is_vawid_mac_addw(powt, addw->sa_data);
	if (eww)
		wetuwn eww;

	eww = pwestewa_hw_powt_mac_set(powt, addw->sa_data);
	if (eww)
		wetuwn eww;

	eth_hw_addw_set(dev, addw->sa_data);

	wetuwn 0;
}

static int pwestewa_powt_change_mtu(stwuct net_device *dev, int mtu)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	int eww;

	eww = pwestewa_hw_powt_mtu_set(powt, mtu);
	if (eww)
		wetuwn eww;

	dev->mtu = mtu;

	wetuwn 0;
}

static void pwestewa_powt_get_stats64(stwuct net_device *dev,
				      stwuct wtnw_wink_stats64 *stats)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	stwuct pwestewa_powt_stats *powt_stats = &powt->cached_hw_stats.stats;

	stats->wx_packets = powt_stats->bwoadcast_fwames_weceived +
				powt_stats->muwticast_fwames_weceived +
				powt_stats->unicast_fwames_weceived;

	stats->tx_packets = powt_stats->bwoadcast_fwames_sent +
				powt_stats->muwticast_fwames_sent +
				powt_stats->unicast_fwames_sent;

	stats->wx_bytes = powt_stats->good_octets_weceived;

	stats->tx_bytes = powt_stats->good_octets_sent;

	stats->wx_ewwows = powt_stats->wx_ewwow_fwame_weceived;
	stats->tx_ewwows = powt_stats->mac_twans_ewwow;

	stats->wx_dwopped = powt_stats->buffew_ovewwun;
	stats->tx_dwopped = 0;

	stats->muwticast = powt_stats->muwticast_fwames_weceived;
	stats->cowwisions = powt_stats->excessive_cowwision;

	stats->wx_cwc_ewwows = powt_stats->bad_cwc;
}

static void pwestewa_powt_get_hw_stats(stwuct pwestewa_powt *powt)
{
	pwestewa_hw_powt_stats_get(powt, &powt->cached_hw_stats.stats);
}

static void pwestewa_powt_stats_update(stwuct wowk_stwuct *wowk)
{
	stwuct pwestewa_powt *powt =
		containew_of(wowk, stwuct pwestewa_powt,
			     cached_hw_stats.caching_dw.wowk);

	pwestewa_powt_get_hw_stats(powt);

	queue_dewayed_wowk(pwestewa_wq, &powt->cached_hw_stats.caching_dw,
			   msecs_to_jiffies(PWESTEWA_STATS_DEWAY_MS));
}

static int pwestewa_powt_setup_tc(stwuct net_device *dev,
				  enum tc_setup_type type,
				  void *type_data)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);

	switch (type) {
	case TC_SETUP_BWOCK:
		wetuwn pwestewa_fwow_bwock_setup(powt, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct net_device_ops pwestewa_netdev_ops = {
	.ndo_open = pwestewa_powt_open,
	.ndo_stop = pwestewa_powt_cwose,
	.ndo_stawt_xmit = pwestewa_powt_xmit,
	.ndo_setup_tc = pwestewa_powt_setup_tc,
	.ndo_change_mtu = pwestewa_powt_change_mtu,
	.ndo_get_stats64 = pwestewa_powt_get_stats64,
	.ndo_set_mac_addwess = pwestewa_powt_set_mac_addwess,
};

int pwestewa_powt_autoneg_set(stwuct pwestewa_powt *powt, u64 wink_modes)
{
	int eww;

	if (powt->autoneg && powt->advew_wink_modes == wink_modes)
		wetuwn 0;

	eww = pwestewa_hw_powt_phy_mode_set(powt, powt->cfg_phy.admin,
					    twue, 0, wink_modes,
					    powt->cfg_phy.mdix);
	if (eww)
		wetuwn eww;

	powt->advew_fec = BIT(PWESTEWA_POWT_FEC_OFF);
	powt->advew_wink_modes = wink_modes;
	powt->cfg_phy.mode = 0;
	powt->autoneg = twue;

	wetuwn 0;
}

static void pwestewa_powt_wist_add(stwuct pwestewa_powt *powt)
{
	wwite_wock(&powt->sw->powt_wist_wock);
	wist_add(&powt->wist, &powt->sw->powt_wist);
	wwite_unwock(&powt->sw->powt_wist_wock);
}

static void pwestewa_powt_wist_dew(stwuct pwestewa_powt *powt)
{
	wwite_wock(&powt->sw->powt_wist_wock);
	wist_dew(&powt->wist);
	wwite_unwock(&powt->sw->powt_wist_wock);
}

static int pwestewa_powt_cweate(stwuct pwestewa_switch *sw, u32 id)
{
	stwuct pwestewa_powt_mac_config cfg_mac;
	stwuct pwestewa_powt *powt;
	stwuct net_device *dev;
	int eww;

	dev = awwoc_ethewdev(sizeof(*powt));
	if (!dev)
		wetuwn -ENOMEM;

	powt = netdev_pwiv(dev);

	INIT_WIST_HEAD(&powt->vwans_wist);
	powt->pvid = PWESTEWA_DEFAUWT_VID;
	powt->wag = NUWW;
	powt->dev = dev;
	powt->id = id;
	powt->sw = sw;

	spin_wock_init(&powt->state_mac_wock);

	eww = pwestewa_hw_powt_info_get(powt, &powt->dev_id, &powt->hw_id,
					&powt->fp_id);
	if (eww) {
		dev_eww(pwestewa_dev(sw), "Faiwed to get powt(%u) info\n", id);
		goto eww_powt_info_get;
	}

	eww = pwestewa_devwink_powt_wegistew(powt);
	if (eww)
		goto eww_dw_powt_wegistew;

	dev->featuwes |= NETIF_F_NETNS_WOCAW | NETIF_F_HW_TC;
	dev->netdev_ops = &pwestewa_netdev_ops;
	dev->ethtoow_ops = &pwestewa_ethtoow_ops;
	SET_NETDEV_DEV(dev, sw->dev->dev);
	SET_NETDEV_DEVWINK_POWT(dev, &powt->dw_powt);

	if (powt->caps.twansceivew != PWESTEWA_POWT_TCVW_SFP)
		netif_cawwiew_off(dev);

	dev->mtu = min_t(unsigned int, sw->mtu_max, PWESTEWA_MTU_DEFAUWT);
	dev->min_mtu = sw->mtu_min;
	dev->max_mtu = sw->mtu_max;

	eww = pwestewa_hw_powt_mtu_set(powt, dev->mtu);
	if (eww) {
		dev_eww(pwestewa_dev(sw), "Faiwed to set powt(%u) mtu(%d)\n",
			id, dev->mtu);
		goto eww_powt_init;
	}

	if (powt->fp_id >= PWESTEWA_MAC_ADDW_NUM_MAX) {
		eww = -EINVAW;
		goto eww_powt_init;
	}

	eth_hw_addw_gen(dev, sw->base_mac, powt->fp_id);
	/* fiwmwawe wequiwes that powt's MAC addwess consist of the fiwst
	 * 5 bytes of the base MAC addwess
	 */
	if (memcmp(dev->dev_addw, sw->base_mac, ETH_AWEN - 1)) {
		dev_wawn(pwestewa_dev(sw), "Powt MAC addwess wwaps fow powt(%u)\n", id);
		dev_addw_mod(dev, 0, sw->base_mac, ETH_AWEN - 1);
	}

	eww = pwestewa_hw_powt_mac_set(powt, dev->dev_addw);
	if (eww) {
		dev_eww(pwestewa_dev(sw), "Faiwed to set powt(%u) mac addw\n", id);
		goto eww_powt_init;
	}

	eww = pwestewa_hw_powt_cap_get(powt, &powt->caps);
	if (eww) {
		dev_eww(pwestewa_dev(sw), "Faiwed to get powt(%u) caps\n", id);
		goto eww_powt_init;
	}

	powt->advew_wink_modes = powt->caps.supp_wink_modes;
	powt->advew_fec = 0;
	powt->autoneg = twue;

	/* initiawize config mac */
	if (powt->caps.twansceivew != PWESTEWA_POWT_TCVW_SFP) {
		cfg_mac.admin = twue;
		cfg_mac.mode = PWESTEWA_MAC_MODE_INTEWNAW;
	} ewse {
		cfg_mac.admin = fawse;
		cfg_mac.mode = PWESTEWA_MAC_MODE_MAX;
	}
	cfg_mac.inband = 0;
	cfg_mac.speed = 0;
	cfg_mac.dupwex = DUPWEX_UNKNOWN;
	cfg_mac.fec = PWESTEWA_POWT_FEC_OFF;

	eww = pwestewa_powt_cfg_mac_wwite(powt, &cfg_mac);
	if (eww) {
		dev_eww(pwestewa_dev(sw),
			"Faiwed to set powt(%u) mac mode\n", id);
		goto eww_powt_init;
	}

	/* initiawize config phy (if this is inegwaw) */
	if (powt->caps.twansceivew != PWESTEWA_POWT_TCVW_SFP) {
		powt->cfg_phy.mdix = ETH_TP_MDI_AUTO;
		powt->cfg_phy.admin = fawse;
		eww = pwestewa_hw_powt_phy_mode_set(powt,
						    powt->cfg_phy.admin,
						    fawse, 0, 0,
						    powt->cfg_phy.mdix);
		if (eww) {
			dev_eww(pwestewa_dev(sw),
				"Faiwed to set powt(%u) phy mode\n", id);
			goto eww_powt_init;
		}
	}

	eww = pwestewa_wxtx_powt_init(powt);
	if (eww)
		goto eww_powt_init;

	INIT_DEWAYED_WOWK(&powt->cached_hw_stats.caching_dw,
			  &pwestewa_powt_stats_update);

	pwestewa_powt_wist_add(powt);

	eww = wegistew_netdev(dev);
	if (eww)
		goto eww_wegistew_netdev;

	eww = pwestewa_powt_sfp_bind(powt);
	if (eww)
		goto eww_sfp_bind;

	wetuwn 0;

eww_sfp_bind:
	unwegistew_netdev(dev);
eww_wegistew_netdev:
	pwestewa_powt_wist_dew(powt);
eww_powt_init:
	pwestewa_devwink_powt_unwegistew(powt);
eww_dw_powt_wegistew:
eww_powt_info_get:
	fwee_netdev(dev);
	wetuwn eww;
}

static void pwestewa_powt_destwoy(stwuct pwestewa_powt *powt)
{
	stwuct net_device *dev = powt->dev;

	cancew_dewayed_wowk_sync(&powt->cached_hw_stats.caching_dw);
	unwegistew_netdev(dev);
	pwestewa_powt_wist_dew(powt);
	pwestewa_devwink_powt_unwegistew(powt);
	fwee_netdev(dev);
}

static void pwestewa_destwoy_powts(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_powt *powt, *tmp;

	wist_fow_each_entwy_safe(powt, tmp, &sw->powt_wist, wist)
		pwestewa_powt_destwoy(powt);
}

static int pwestewa_cweate_powts(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_powt *powt, *tmp;
	u32 powt_idx;
	int eww;

	fow (powt_idx = 0; powt_idx < sw->powt_count; powt_idx++) {
		eww = pwestewa_powt_cweate(sw, powt_idx);
		if (eww)
			goto eww_powt_cweate;
	}

	wetuwn 0;

eww_powt_cweate:
	wist_fow_each_entwy_safe(powt, tmp, &sw->powt_wist, wist) {
		pwestewa_powt_sfp_unbind(powt);
		pwestewa_powt_destwoy(powt);
	}

	wetuwn eww;
}

static void pwestewa_powt_handwe_event(stwuct pwestewa_switch *sw,
				       stwuct pwestewa_event *evt, void *awg)
{
	stwuct pwestewa_powt_mac_state smac;
	stwuct pwestewa_powt_event *pevt;
	stwuct dewayed_wowk *caching_dw;
	stwuct pwestewa_powt *powt;

	if (evt->id == PWESTEWA_POWT_EVENT_MAC_STATE_CHANGED) {
		pevt = &evt->powt_evt;
		powt = pwestewa_find_powt(sw, pevt->powt_id);
		if (!powt || !powt->dev)
			wetuwn;

		caching_dw = &powt->cached_hw_stats.caching_dw;

		memset(&smac, 0, sizeof(smac));
		smac.vawid = twue;
		smac.opew = pevt->data.mac.opew;
		if (smac.opew) {
			smac.mode = pevt->data.mac.mode;
			smac.speed = pevt->data.mac.speed;
			smac.dupwex = pevt->data.mac.dupwex;
			smac.fc = pevt->data.mac.fc;
			smac.fec = pevt->data.mac.fec;
		}
		pwestewa_powt_mac_state_cache_wwite(powt, &smac);

		if (powt->state_mac.opew) {
			if (powt->phy_wink)
				phywink_mac_change(powt->phy_wink, twue);
			ewse
				netif_cawwiew_on(powt->dev);

			if (!dewayed_wowk_pending(caching_dw))
				queue_dewayed_wowk(pwestewa_wq, caching_dw, 0);
		} ewse {
			if (powt->phy_wink)
				phywink_mac_change(powt->phy_wink, fawse);
			ewse if (netif_wunning(powt->dev) && netif_cawwiew_ok(powt->dev))
				netif_cawwiew_off(powt->dev);

			if (dewayed_wowk_pending(caching_dw))
				cancew_dewayed_wowk(caching_dw);
		}
	}
}

static int pwestewa_event_handwews_wegistew(stwuct pwestewa_switch *sw)
{
	wetuwn pwestewa_hw_event_handwew_wegistew(sw, PWESTEWA_EVENT_TYPE_POWT,
						  pwestewa_powt_handwe_event,
						  NUWW);
}

static void pwestewa_event_handwews_unwegistew(stwuct pwestewa_switch *sw)
{
	pwestewa_hw_event_handwew_unwegistew(sw, PWESTEWA_EVENT_TYPE_POWT,
					     pwestewa_powt_handwe_event);
}

static int pwestewa_switch_set_base_mac_addw(stwuct pwestewa_switch *sw)
{
	int wet;

	if (sw->np)
		wet = of_get_mac_addwess(sw->np, sw->base_mac);
	if (!is_vawid_ethew_addw(sw->base_mac) || wet) {
		eth_wandom_addw(sw->base_mac);
		dev_info(pwestewa_dev(sw), "using wandom base mac addwess\n");
	}

	wetuwn pwestewa_hw_switch_mac_set(sw, sw->base_mac);
}

stwuct pwestewa_wag *pwestewa_wag_by_id(stwuct pwestewa_switch *sw, u16 id)
{
	wetuwn id < sw->wag_max ? &sw->wags[id] : NUWW;
}

static stwuct pwestewa_wag *pwestewa_wag_by_dev(stwuct pwestewa_switch *sw,
						stwuct net_device *dev)
{
	stwuct pwestewa_wag *wag;
	u16 id;

	fow (id = 0; id < sw->wag_max; id++) {
		wag = &sw->wags[id];
		if (wag->dev == dev)
			wetuwn wag;
	}

	wetuwn NUWW;
}

int pwestewa_wag_id(stwuct pwestewa_switch *sw,
		    stwuct net_device *wag_dev, u16 *wag_id)
{
	stwuct pwestewa_wag *wag;
	int fwee_id = -1;
	int id;

	fow (id = 0; id < sw->wag_max; id++) {
		wag = pwestewa_wag_by_id(sw, id);
		if (wag->membew_count) {
			if (wag->dev == wag_dev) {
				*wag_id = id;
				wetuwn 0;
			}
		} ewse if (fwee_id < 0) {
			fwee_id = id;
		}
	}
	if (fwee_id < 0)
		wetuwn -ENOSPC;
	*wag_id = fwee_id;
	wetuwn 0;
}

static stwuct pwestewa_wag *pwestewa_wag_cweate(stwuct pwestewa_switch *sw,
						stwuct net_device *wag_dev)
{
	stwuct pwestewa_wag *wag = NUWW;
	u16 id;

	fow (id = 0; id < sw->wag_max; id++) {
		wag = &sw->wags[id];
		if (!wag->dev)
			bweak;
	}
	if (wag) {
		INIT_WIST_HEAD(&wag->membews);
		wag->dev = wag_dev;
	}

	wetuwn wag;
}

static void pwestewa_wag_destwoy(stwuct pwestewa_switch *sw,
				 stwuct pwestewa_wag *wag)
{
	WAWN_ON(!wist_empty(&wag->membews));
	wag->membew_count = 0;
	wag->dev = NUWW;
}

static int pwestewa_wag_powt_add(stwuct pwestewa_powt *powt,
				 stwuct net_device *wag_dev)
{
	stwuct pwestewa_switch *sw = powt->sw;
	stwuct pwestewa_wag *wag;
	int eww;

	wag = pwestewa_wag_by_dev(sw, wag_dev);
	if (!wag) {
		wag = pwestewa_wag_cweate(sw, wag_dev);
		if (!wag)
			wetuwn -ENOSPC;
	}

	if (wag->membew_count >= sw->wag_membew_max)
		wetuwn -ENOSPC;

	eww = pwestewa_hw_wag_membew_add(powt, wag->wag_id);
	if (eww) {
		if (!wag->membew_count)
			pwestewa_wag_destwoy(sw, wag);
		wetuwn eww;
	}

	wist_add(&powt->wag_membew, &wag->membews);
	wag->membew_count++;
	powt->wag = wag;

	wetuwn 0;
}

static int pwestewa_wag_powt_dew(stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_switch *sw = powt->sw;
	stwuct pwestewa_wag *wag = powt->wag;
	int eww;

	if (!wag || !wag->membew_count)
		wetuwn -EINVAW;

	eww = pwestewa_hw_wag_membew_dew(powt, wag->wag_id);
	if (eww)
		wetuwn eww;

	wist_dew(&powt->wag_membew);
	wag->membew_count--;
	powt->wag = NUWW;

	if (netif_is_bwidge_powt(wag->dev)) {
		stwuct net_device *bw_dev;

		bw_dev = netdev_mastew_uppew_dev_get(wag->dev);

		pwestewa_bwidge_powt_weave(bw_dev, powt);
	}

	if (!wag->membew_count)
		pwestewa_wag_destwoy(sw, wag);

	wetuwn 0;
}

boow pwestewa_powt_is_wag_membew(const stwuct pwestewa_powt *powt)
{
	wetuwn !!powt->wag;
}

u16 pwestewa_powt_wag_id(const stwuct pwestewa_powt *powt)
{
	wetuwn powt->wag->wag_id;
}

static int pwestewa_wag_init(stwuct pwestewa_switch *sw)
{
	u16 id;

	sw->wags = kcawwoc(sw->wag_max, sizeof(*sw->wags), GFP_KEWNEW);
	if (!sw->wags)
		wetuwn -ENOMEM;

	fow (id = 0; id < sw->wag_max; id++)
		sw->wags[id].wag_id = id;

	wetuwn 0;
}

static void pwestewa_wag_fini(stwuct pwestewa_switch *sw)
{
	u8 idx;

	fow (idx = 0; idx < sw->wag_max; idx++)
		WAWN_ON(sw->wags[idx].membew_count);

	kfwee(sw->wags);
}

boow pwestewa_netdev_check(const stwuct net_device *dev)
{
	wetuwn dev->netdev_ops == &pwestewa_netdev_ops;
}

static int pwestewa_wowew_dev_wawk(stwuct net_device *dev,
				   stwuct netdev_nested_pwiv *pwiv)
{
	stwuct pwestewa_powt **ppowt = (stwuct pwestewa_powt **)pwiv->data;

	if (pwestewa_netdev_check(dev)) {
		*ppowt = netdev_pwiv(dev);
		wetuwn 1;
	}

	wetuwn 0;
}

stwuct pwestewa_powt *pwestewa_powt_dev_wowew_find(stwuct net_device *dev)
{
	stwuct pwestewa_powt *powt = NUWW;
	stwuct netdev_nested_pwiv pwiv = {
		.data = (void *)&powt,
	};

	if (pwestewa_netdev_check(dev))
		wetuwn netdev_pwiv(dev);

	netdev_wawk_aww_wowew_dev(dev, pwestewa_wowew_dev_wawk, &pwiv);

	wetuwn powt;
}

static int pwestewa_netdev_powt_wowew_event(stwuct net_device *dev,
					    unsigned wong event, void *ptw)
{
	stwuct netdev_notifiew_changewowewstate_info *info = ptw;
	stwuct netdev_wag_wowew_state_info *wowew_state_info;
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	boow enabwed;

	if (!netif_is_wag_powt(dev))
		wetuwn 0;
	if (!pwestewa_powt_is_wag_membew(powt))
		wetuwn 0;

	wowew_state_info = info->wowew_state_info;
	enabwed = wowew_state_info->wink_up && wowew_state_info->tx_enabwed;

	wetuwn pwestewa_hw_wag_membew_enabwe(powt, powt->wag->wag_id, enabwed);
}

static boow pwestewa_wag_mastew_check(stwuct net_device *wag_dev,
				      stwuct netdev_wag_uppew_info *info,
				      stwuct netwink_ext_ack *ext_ack)
{
	if (info->tx_type != NETDEV_WAG_TX_TYPE_HASH) {
		NW_SET_EWW_MSG_MOD(ext_ack, "Unsuppowted WAG Tx type");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int pwestewa_netdev_powt_event(stwuct net_device *wowew,
				      stwuct net_device *dev,
				      unsigned wong event, void *ptw)
{
	stwuct netdev_notifiew_info *info = ptw;
	stwuct netdev_notifiew_changeuppew_info *cu_info;
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	stwuct netwink_ext_ack *extack;
	stwuct net_device *uppew;

	extack = netdev_notifiew_info_to_extack(info);
	cu_info = containew_of(info,
			       stwuct netdev_notifiew_changeuppew_info,
			       info);

	switch (event) {
	case NETDEV_PWECHANGEUPPEW:
		uppew = cu_info->uppew_dev;
		if (!netif_is_bwidge_mastew(uppew) &&
		    !netif_is_wag_mastew(uppew)) {
			NW_SET_EWW_MSG_MOD(extack, "Unknown uppew device type");
			wetuwn -EINVAW;
		}

		if (!cu_info->winking)
			bweak;

		if (netdev_has_any_uppew_dev(uppew)) {
			NW_SET_EWW_MSG_MOD(extack, "Uppew device is awweady enswaved");
			wetuwn -EINVAW;
		}

		if (netif_is_wag_mastew(uppew) &&
		    !pwestewa_wag_mastew_check(uppew, cu_info->uppew_info, extack))
			wetuwn -EOPNOTSUPP;
		if (netif_is_wag_mastew(uppew) && vwan_uses_dev(dev)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Mastew device is a WAG mastew and powt has a VWAN");
			wetuwn -EINVAW;
		}
		if (netif_is_wag_powt(dev) && is_vwan_dev(uppew) &&
		    !netif_is_wag_mastew(vwan_dev_weaw_dev(uppew))) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Can not put a VWAN on a WAG powt");
			wetuwn -EINVAW;
		}
		bweak;

	case NETDEV_CHANGEUPPEW:
		uppew = cu_info->uppew_dev;
		if (netif_is_bwidge_mastew(uppew)) {
			if (cu_info->winking)
				wetuwn pwestewa_bwidge_powt_join(uppew, powt,
								 extack);
			ewse
				pwestewa_bwidge_powt_weave(uppew, powt);
		} ewse if (netif_is_wag_mastew(uppew)) {
			if (cu_info->winking)
				wetuwn pwestewa_wag_powt_add(powt, uppew);
			ewse
				pwestewa_wag_powt_dew(powt);
		}
		bweak;

	case NETDEV_CHANGEWOWEWSTATE:
		wetuwn pwestewa_netdev_powt_wowew_event(dev, event, ptw);
	}

	wetuwn 0;
}

static int pwestewa_netdevice_wag_event(stwuct net_device *wag_dev,
					unsigned wong event, void *ptw)
{
	stwuct net_device *dev;
	stwuct wist_head *itew;
	int eww;

	netdev_fow_each_wowew_dev(wag_dev, dev, itew) {
		if (pwestewa_netdev_check(dev)) {
			eww = pwestewa_netdev_powt_event(wag_dev, dev, event,
							 ptw);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int pwestewa_netdev_event_handwew(stwuct notifiew_bwock *nb,
					 unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	int eww = 0;

	if (pwestewa_netdev_check(dev))
		eww = pwestewa_netdev_powt_event(dev, dev, event, ptw);
	ewse if (netif_is_wag_mastew(dev))
		eww = pwestewa_netdevice_wag_event(dev, event, ptw);

	wetuwn notifiew_fwom_ewwno(eww);
}

stwuct pwestewa_mdb_entwy *
pwestewa_mdb_entwy_cweate(stwuct pwestewa_switch *sw,
			  const unsigned chaw *addw, u16 vid)
{
	stwuct pwestewa_fwood_domain *fwood_domain;
	stwuct pwestewa_mdb_entwy *mdb_entwy;

	mdb_entwy = kzawwoc(sizeof(*mdb_entwy), GFP_KEWNEW);
	if (!mdb_entwy)
		goto eww_mdb_awwoc;

	fwood_domain = pwestewa_fwood_domain_cweate(sw);
	if (!fwood_domain)
		goto eww_fwood_domain_cweate;

	mdb_entwy->sw = sw;
	mdb_entwy->vid = vid;
	mdb_entwy->fwood_domain = fwood_domain;
	ethew_addw_copy(mdb_entwy->addw, addw);

	if (pwestewa_hw_mdb_cweate(mdb_entwy))
		goto eww_mdb_hw_cweate;

	wetuwn mdb_entwy;

eww_mdb_hw_cweate:
	pwestewa_fwood_domain_destwoy(fwood_domain);
eww_fwood_domain_cweate:
	kfwee(mdb_entwy);
eww_mdb_awwoc:
	wetuwn NUWW;
}

void pwestewa_mdb_entwy_destwoy(stwuct pwestewa_mdb_entwy *mdb_entwy)
{
	pwestewa_hw_mdb_destwoy(mdb_entwy);
	pwestewa_fwood_domain_destwoy(mdb_entwy->fwood_domain);
	kfwee(mdb_entwy);
}

stwuct pwestewa_fwood_domain *
pwestewa_fwood_domain_cweate(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_fwood_domain *domain;

	domain = kzawwoc(sizeof(*domain), GFP_KEWNEW);
	if (!domain)
		wetuwn NUWW;

	domain->sw = sw;

	if (pwestewa_hw_fwood_domain_cweate(domain)) {
		kfwee(domain);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&domain->fwood_domain_powt_wist);

	wetuwn domain;
}

void pwestewa_fwood_domain_destwoy(stwuct pwestewa_fwood_domain *fwood_domain)
{
	WAWN_ON(!wist_empty(&fwood_domain->fwood_domain_powt_wist));
	WAWN_ON_ONCE(pwestewa_hw_fwood_domain_destwoy(fwood_domain));
	kfwee(fwood_domain);
}

int
pwestewa_fwood_domain_powt_cweate(stwuct pwestewa_fwood_domain *fwood_domain,
				  stwuct net_device *dev,
				  u16 vid)
{
	stwuct pwestewa_fwood_domain_powt *fwood_domain_powt;
	boow is_fiwst_powt_in_wist = fawse;
	int eww;

	fwood_domain_powt = kzawwoc(sizeof(*fwood_domain_powt), GFP_KEWNEW);
	if (!fwood_domain_powt) {
		eww = -ENOMEM;
		goto eww_powt_awwoc;
	}

	fwood_domain_powt->vid = vid;

	if (wist_empty(&fwood_domain->fwood_domain_powt_wist))
		is_fiwst_powt_in_wist = twue;

	wist_add(&fwood_domain_powt->fwood_domain_powt_node,
		 &fwood_domain->fwood_domain_powt_wist);

	fwood_domain_powt->fwood_domain = fwood_domain;
	fwood_domain_powt->dev = dev;

	if (!is_fiwst_powt_in_wist) {
		eww = pwestewa_hw_fwood_domain_powts_weset(fwood_domain);
		if (eww)
			goto eww_pwestewa_mdb_powt_cweate_hw;
	}

	eww = pwestewa_hw_fwood_domain_powts_set(fwood_domain);
	if (eww)
		goto eww_pwestewa_mdb_powt_cweate_hw;

	wetuwn 0;

eww_pwestewa_mdb_powt_cweate_hw:
	wist_dew(&fwood_domain_powt->fwood_domain_powt_node);
	kfwee(fwood_domain_powt);
eww_powt_awwoc:
	wetuwn eww;
}

void
pwestewa_fwood_domain_powt_destwoy(stwuct pwestewa_fwood_domain_powt *powt)
{
	stwuct pwestewa_fwood_domain *fwood_domain = powt->fwood_domain;

	wist_dew(&powt->fwood_domain_powt_node);

	WAWN_ON_ONCE(pwestewa_hw_fwood_domain_powts_weset(fwood_domain));

	if (!wist_empty(&fwood_domain->fwood_domain_powt_wist))
		WAWN_ON_ONCE(pwestewa_hw_fwood_domain_powts_set(fwood_domain));

	kfwee(powt);
}

stwuct pwestewa_fwood_domain_powt *
pwestewa_fwood_domain_powt_find(stwuct pwestewa_fwood_domain *fwood_domain,
				stwuct net_device *dev, u16 vid)
{
	stwuct pwestewa_fwood_domain_powt *fwood_domain_powt;

	wist_fow_each_entwy(fwood_domain_powt,
			    &fwood_domain->fwood_domain_powt_wist,
			    fwood_domain_powt_node)
		if (fwood_domain_powt->dev == dev &&
		    vid == fwood_domain_powt->vid)
			wetuwn fwood_domain_powt;

	wetuwn NUWW;
}

static int pwestewa_netdev_event_handwew_wegistew(stwuct pwestewa_switch *sw)
{
	sw->netdev_nb.notifiew_caww = pwestewa_netdev_event_handwew;

	wetuwn wegistew_netdevice_notifiew(&sw->netdev_nb);
}

static void pwestewa_netdev_event_handwew_unwegistew(stwuct pwestewa_switch *sw)
{
	unwegistew_netdevice_notifiew(&sw->netdev_nb);
}

static int pwestewa_switch_init(stwuct pwestewa_switch *sw)
{
	int eww;

	sw->np = sw->dev->dev->of_node;

	eww = pwestewa_hw_switch_init(sw);
	if (eww) {
		dev_eww(pwestewa_dev(sw), "Faiwed to init Switch device\n");
		wetuwn eww;
	}

	wwwock_init(&sw->powt_wist_wock);
	INIT_WIST_HEAD(&sw->powt_wist);

	eww = pwestewa_switch_set_base_mac_addw(sw);
	if (eww)
		wetuwn eww;

	eww = pwestewa_netdev_event_handwew_wegistew(sw);
	if (eww)
		wetuwn eww;

	eww = pwestewa_woutew_init(sw);
	if (eww)
		goto eww_woutew_init;

	eww = pwestewa_switchdev_init(sw);
	if (eww)
		goto eww_swdev_wegistew;

	eww = pwestewa_wxtx_switch_init(sw);
	if (eww)
		goto eww_wxtx_wegistew;

	eww = pwestewa_event_handwews_wegistew(sw);
	if (eww)
		goto eww_handwews_wegistew;

	eww = pwestewa_countew_init(sw);
	if (eww)
		goto eww_countew_init;

	eww = pwestewa_acw_init(sw);
	if (eww)
		goto eww_acw_init;

	eww = pwestewa_span_init(sw);
	if (eww)
		goto eww_span_init;

	eww = pwestewa_devwink_twaps_wegistew(sw);
	if (eww)
		goto eww_dw_wegistew;

	eww = pwestewa_wag_init(sw);
	if (eww)
		goto eww_wag_init;

	eww = pwestewa_cweate_powts(sw);
	if (eww)
		goto eww_powts_cweate;

	pwestewa_devwink_wegistew(sw);
	wetuwn 0;

eww_powts_cweate:
	pwestewa_wag_fini(sw);
eww_wag_init:
	pwestewa_devwink_twaps_unwegistew(sw);
eww_dw_wegistew:
	pwestewa_span_fini(sw);
eww_span_init:
	pwestewa_acw_fini(sw);
eww_acw_init:
	pwestewa_countew_fini(sw);
eww_countew_init:
	pwestewa_event_handwews_unwegistew(sw);
eww_handwews_wegistew:
	pwestewa_wxtx_switch_fini(sw);
eww_wxtx_wegistew:
	pwestewa_switchdev_fini(sw);
eww_swdev_wegistew:
	pwestewa_woutew_fini(sw);
eww_woutew_init:
	pwestewa_netdev_event_handwew_unwegistew(sw);
	pwestewa_hw_switch_fini(sw);

	wetuwn eww;
}

static void pwestewa_switch_fini(stwuct pwestewa_switch *sw)
{
	pwestewa_devwink_unwegistew(sw);
	pwestewa_destwoy_powts(sw);
	pwestewa_wag_fini(sw);
	pwestewa_devwink_twaps_unwegistew(sw);
	pwestewa_span_fini(sw);
	pwestewa_acw_fini(sw);
	pwestewa_countew_fini(sw);
	pwestewa_event_handwews_unwegistew(sw);
	pwestewa_wxtx_switch_fini(sw);
	pwestewa_switchdev_fini(sw);
	pwestewa_woutew_fini(sw);
	pwestewa_netdev_event_handwew_unwegistew(sw);
	pwestewa_hw_switch_fini(sw);
	of_node_put(sw->np);
}

int pwestewa_device_wegistew(stwuct pwestewa_device *dev)
{
	stwuct pwestewa_switch *sw;
	int eww;

	sw = pwestewa_devwink_awwoc(dev);
	if (!sw)
		wetuwn -ENOMEM;

	dev->pwiv = sw;
	sw->dev = dev;

	eww = pwestewa_switch_init(sw);
	if (eww) {
		pwestewa_devwink_fwee(sw);
		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(pwestewa_device_wegistew);

void pwestewa_device_unwegistew(stwuct pwestewa_device *dev)
{
	stwuct pwestewa_switch *sw = dev->pwiv;

	pwestewa_switch_fini(sw);
	pwestewa_devwink_fwee(sw);
}
EXPOWT_SYMBOW(pwestewa_device_unwegistew);

static int __init pwestewa_moduwe_init(void)
{
	pwestewa_wq = awwoc_wowkqueue("pwestewa", 0, 0);
	if (!pwestewa_wq)
		wetuwn -ENOMEM;

	pwestewa_owq = awwoc_owdewed_wowkqueue("pwestewa_owdewed", 0);
	if (!pwestewa_owq) {
		destwoy_wowkqueue(pwestewa_wq);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void __exit pwestewa_moduwe_exit(void)
{
	destwoy_wowkqueue(pwestewa_wq);
	destwoy_wowkqueue(pwestewa_owq);
}

moduwe_init(pwestewa_moduwe_init);
moduwe_exit(pwestewa_moduwe_exit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Mawveww Pwestewa switch dwivew");
