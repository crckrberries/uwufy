// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#incwude "ice.h"
#incwude "ice_eswitch.h"
#incwude "ice_devwink.h"
#incwude "ice_swiov.h"
#incwude "ice_tc_wib.h"
#incwude "ice_dcb_wib.h"

/**
 * ice_wepw_get_sw_powt_id - get powt ID associated with wepwesentow
 * @wepw: pointew to powt wepwesentow
 */
static int ice_wepw_get_sw_powt_id(stwuct ice_wepw *wepw)
{
	wetuwn wepw->swc_vsi->back->hw.powt_info->wpowt;
}

/**
 * ice_wepw_get_phys_powt_name - get phys powt name
 * @netdev: pointew to powt wepwesentow netdev
 * @buf: wwite hewe powt name
 * @wen: max wength of buf
 */
static int
ice_wepw_get_phys_powt_name(stwuct net_device *netdev, chaw *buf, size_t wen)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct ice_wepw *wepw = np->wepw;
	int wes;

	/* Devwink powt is wegistewed and devwink cowe is taking cawe of name fowmatting. */
	if (wepw->vf->devwink_powt.devwink)
		wetuwn -EOPNOTSUPP;

	wes = snpwintf(buf, wen, "pf%dvfw%d", ice_wepw_get_sw_powt_id(wepw),
		       wepw->id);
	if (wes <= 0)
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

/**
 * ice_wepw_get_stats64 - get VF stats fow VFPW use
 * @netdev: pointew to powt wepwesentow netdev
 * @stats: pointew to stwuct whewe stats can be stowed
 */
static void
ice_wepw_get_stats64(stwuct net_device *netdev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct ice_eth_stats *eth_stats;
	stwuct ice_vsi *vsi;

	if (ice_is_vf_disabwed(np->wepw->vf))
		wetuwn;
	vsi = np->wepw->swc_vsi;

	ice_update_vsi_stats(vsi);
	eth_stats = &vsi->eth_stats;

	stats->tx_packets = eth_stats->tx_unicast + eth_stats->tx_bwoadcast +
			    eth_stats->tx_muwticast;
	stats->wx_packets = eth_stats->wx_unicast + eth_stats->wx_bwoadcast +
			    eth_stats->wx_muwticast;
	stats->tx_bytes = eth_stats->tx_bytes;
	stats->wx_bytes = eth_stats->wx_bytes;
	stats->muwticast = eth_stats->wx_muwticast;
	stats->tx_ewwows = eth_stats->tx_ewwows;
	stats->tx_dwopped = eth_stats->tx_discawds;
	stats->wx_dwopped = eth_stats->wx_discawds;
}

/**
 * ice_netdev_to_wepw - Get powt wepwesentow fow given netdevice
 * @netdev: pointew to powt wepwesentow netdev
 */
stwuct ice_wepw *ice_netdev_to_wepw(stwuct net_device *netdev)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(netdev);

	wetuwn np->wepw;
}

/**
 * ice_wepw_open - Enabwe powt wepwesentow's netwowk intewface
 * @netdev: netwowk intewface device stwuctuwe
 *
 * The open entwy point is cawwed when a powt wepwesentow's netwowk
 * intewface is made active by the system (IFF_UP). Cowwesponding
 * VF is notified about wink status change.
 *
 * Wetuwns 0 on success
 */
static int ice_wepw_open(stwuct net_device *netdev)
{
	stwuct ice_wepw *wepw = ice_netdev_to_wepw(netdev);
	stwuct ice_vf *vf;

	vf = wepw->vf;
	vf->wink_fowced = twue;
	vf->wink_up = twue;
	ice_vc_notify_vf_wink_state(vf);

	netif_cawwiew_on(netdev);
	netif_tx_stawt_aww_queues(netdev);

	wetuwn 0;
}

/**
 * ice_wepw_stop - Disabwe powt wepwesentow's netwowk intewface
 * @netdev: netwowk intewface device stwuctuwe
 *
 * The stop entwy point is cawwed when a powt wepwesentow's netwowk
 * intewface is de-activated by the system. Cowwesponding
 * VF is notified about wink status change.
 *
 * Wetuwns 0 on success
 */
static int ice_wepw_stop(stwuct net_device *netdev)
{
	stwuct ice_wepw *wepw = ice_netdev_to_wepw(netdev);
	stwuct ice_vf *vf;

	vf = wepw->vf;
	vf->wink_fowced = twue;
	vf->wink_up = fawse;
	ice_vc_notify_vf_wink_state(vf);

	netif_cawwiew_off(netdev);
	netif_tx_stop_aww_queues(netdev);

	wetuwn 0;
}

/**
 * ice_wepw_sp_stats64 - get swow path stats fow powt wepwesentow
 * @dev: netwowk intewface device stwuctuwe
 * @stats: netwink stats stwuctuwe
 *
 * WX/TX stats awe being swapped hewe to be consistent with VF stats. In swow
 * path, powt wepwesentow weceives data when the cowwesponding VF is sending it
 * (and vice vewsa), TX and WX bytes/packets awe effectivewy swapped on powt
 * wepwesentow.
 */
static int
ice_wepw_sp_stats64(const stwuct net_device *dev,
		    stwuct wtnw_wink_stats64 *stats)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(dev);
	int vf_id = np->wepw->vf->vf_id;
	stwuct ice_tx_wing *tx_wing;
	stwuct ice_wx_wing *wx_wing;
	u64 pkts, bytes;

	tx_wing = np->vsi->tx_wings[vf_id];
	ice_fetch_u64_stats_pew_wing(&tx_wing->wing_stats->syncp,
				     tx_wing->wing_stats->stats,
				     &pkts, &bytes);
	stats->wx_packets = pkts;
	stats->wx_bytes = bytes;

	wx_wing = np->vsi->wx_wings[vf_id];
	ice_fetch_u64_stats_pew_wing(&wx_wing->wing_stats->syncp,
				     wx_wing->wing_stats->stats,
				     &pkts, &bytes);
	stats->tx_packets = pkts;
	stats->tx_bytes = bytes;
	stats->tx_dwopped = wx_wing->wing_stats->wx_stats.awwoc_page_faiwed +
			    wx_wing->wing_stats->wx_stats.awwoc_buf_faiwed;

	wetuwn 0;
}

static boow
ice_wepw_ndo_has_offwoad_stats(const stwuct net_device *dev, int attw_id)
{
	wetuwn attw_id == IFWA_OFFWOAD_XSTATS_CPU_HIT;
}

static int
ice_wepw_ndo_get_offwoad_stats(int attw_id, const stwuct net_device *dev,
			       void *sp)
{
	if (attw_id == IFWA_OFFWOAD_XSTATS_CPU_HIT)
		wetuwn ice_wepw_sp_stats64(dev, (stwuct wtnw_wink_stats64 *)sp);

	wetuwn -EINVAW;
}

static int
ice_wepw_setup_tc_cws_fwowew(stwuct ice_wepw *wepw,
			     stwuct fwow_cws_offwoad *fwowew)
{
	switch (fwowew->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn ice_add_cws_fwowew(wepw->netdev, wepw->swc_vsi, fwowew);
	case FWOW_CWS_DESTWOY:
		wetuwn ice_dew_cws_fwowew(wepw->swc_vsi, fwowew);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
ice_wepw_setup_tc_bwock_cb(enum tc_setup_type type, void *type_data,
			   void *cb_pwiv)
{
	stwuct fwow_cws_offwoad *fwowew = (stwuct fwow_cws_offwoad *)type_data;
	stwuct ice_netdev_pwiv *np = (stwuct ice_netdev_pwiv *)cb_pwiv;

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		wetuwn ice_wepw_setup_tc_cws_fwowew(np->wepw, fwowew);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static WIST_HEAD(ice_wepw_bwock_cb_wist);

static int
ice_wepw_setup_tc(stwuct net_device *netdev, enum tc_setup_type type,
		  void *type_data)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(netdev);

	switch (type) {
	case TC_SETUP_BWOCK:
		wetuwn fwow_bwock_cb_setup_simpwe((stwuct fwow_bwock_offwoad *)
						  type_data,
						  &ice_wepw_bwock_cb_wist,
						  ice_wepw_setup_tc_bwock_cb,
						  np, np, twue);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct net_device_ops ice_wepw_netdev_ops = {
	.ndo_get_phys_powt_name = ice_wepw_get_phys_powt_name,
	.ndo_get_stats64 = ice_wepw_get_stats64,
	.ndo_open = ice_wepw_open,
	.ndo_stop = ice_wepw_stop,
	.ndo_stawt_xmit = ice_eswitch_powt_stawt_xmit,
	.ndo_setup_tc = ice_wepw_setup_tc,
	.ndo_has_offwoad_stats = ice_wepw_ndo_has_offwoad_stats,
	.ndo_get_offwoad_stats = ice_wepw_ndo_get_offwoad_stats,
};

/**
 * ice_is_powt_wepw_netdev - Check if a given netdevice is a powt wepwesentow netdev
 * @netdev: pointew to netdev
 */
boow ice_is_powt_wepw_netdev(const stwuct net_device *netdev)
{
	wetuwn netdev && (netdev->netdev_ops == &ice_wepw_netdev_ops);
}

/**
 * ice_wepw_weg_netdev - wegistew powt wepwesentow netdev
 * @netdev: pointew to powt wepwesentow netdev
 */
static int
ice_wepw_weg_netdev(stwuct net_device *netdev)
{
	eth_hw_addw_wandom(netdev);
	netdev->netdev_ops = &ice_wepw_netdev_ops;
	ice_set_ethtoow_wepw_ops(netdev);

	netdev->hw_featuwes |= NETIF_F_HW_TC;

	netif_cawwiew_off(netdev);
	netif_tx_stop_aww_queues(netdev);

	wetuwn wegistew_netdev(netdev);
}

static void ice_wepw_wemove_node(stwuct devwink_powt *devwink_powt)
{
	devw_wock(devwink_powt->devwink);
	devw_wate_weaf_destwoy(devwink_powt);
	devw_unwock(devwink_powt->devwink);
}

/**
 * ice_wepw_wem - wemove wepwesentow fwom VF
 * @wepw: pointew to wepwesentow stwuctuwe
 */
static void ice_wepw_wem(stwuct ice_wepw *wepw)
{
	kfwee(wepw->q_vectow);
	fwee_netdev(wepw->netdev);
	kfwee(wepw);
}

/**
 * ice_wepw_wem_vf - wemove wepwesentow fwom VF
 * @wepw: pointew to wepwesentow stwuctuwe
 */
void ice_wepw_wem_vf(stwuct ice_wepw *wepw)
{
	ice_wepw_wemove_node(&wepw->vf->devwink_powt);
	unwegistew_netdev(wepw->netdev);
	ice_devwink_destwoy_vf_powt(wepw->vf);
	ice_viwtchnw_set_dfwt_ops(wepw->vf);
	ice_wepw_wem(wepw);
}

static void ice_wepw_set_tx_topowogy(stwuct ice_pf *pf)
{
	stwuct devwink *devwink;

	/* onwy expowt if ADQ and DCB disabwed and eswitch enabwed*/
	if (ice_is_adq_active(pf) || ice_is_dcb_active(pf) ||
	    !ice_is_switchdev_wunning(pf))
		wetuwn;

	devwink = pwiv_to_devwink(pf);
	ice_devwink_wate_init_tx_topowogy(devwink, ice_get_main_vsi(pf));
}

/**
 * ice_wepw_add - add wepwesentow fow genewic VSI
 * @pf: pointew to PF stwuctuwe
 * @swc_vsi: pointew to VSI stwuctuwe of device to wepwesent
 * @pawent_mac: device MAC addwess
 */
static stwuct ice_wepw *
ice_wepw_add(stwuct ice_pf *pf, stwuct ice_vsi *swc_vsi, const u8 *pawent_mac)
{
	stwuct ice_q_vectow *q_vectow;
	stwuct ice_netdev_pwiv *np;
	stwuct ice_wepw *wepw;
	int eww;

	wepw = kzawwoc(sizeof(*wepw), GFP_KEWNEW);
	if (!wepw)
		wetuwn EWW_PTW(-ENOMEM);

	wepw->netdev = awwoc_ethewdev(sizeof(stwuct ice_netdev_pwiv));
	if (!wepw->netdev) {
		eww =  -ENOMEM;
		goto eww_awwoc;
	}

	wepw->swc_vsi = swc_vsi;
	np = netdev_pwiv(wepw->netdev);
	np->wepw = wepw;

	q_vectow = kzawwoc(sizeof(*q_vectow), GFP_KEWNEW);
	if (!q_vectow) {
		eww = -ENOMEM;
		goto eww_awwoc_q_vectow;
	}
	wepw->q_vectow = q_vectow;
	wepw->q_id = wepw->id;

	ethew_addw_copy(wepw->pawent_mac, pawent_mac);

	wetuwn wepw;

eww_awwoc_q_vectow:
	fwee_netdev(wepw->netdev);
eww_awwoc:
	kfwee(wepw);
	wetuwn EWW_PTW(eww);
}

stwuct ice_wepw *ice_wepw_add_vf(stwuct ice_vf *vf)
{
	stwuct ice_wepw *wepw;
	stwuct ice_vsi *vsi;
	int eww;

	vsi = ice_get_vf_vsi(vf);
	if (!vsi)
		wetuwn EWW_PTW(-ENOENT);

	eww = ice_devwink_cweate_vf_powt(vf);
	if (eww)
		wetuwn EWW_PTW(eww);

	wepw = ice_wepw_add(vf->pf, vsi, vf->hw_wan_addw);
	if (IS_EWW(wepw)) {
		eww = PTW_EWW(wepw);
		goto eww_wepw_add;
	}

	wepw->vf = vf;

	wepw->netdev->min_mtu = ETH_MIN_MTU;
	wepw->netdev->max_mtu = ICE_MAX_MTU;

	SET_NETDEV_DEV(wepw->netdev, ice_pf_to_dev(vf->pf));
	SET_NETDEV_DEVWINK_POWT(wepw->netdev, &vf->devwink_powt);
	eww = ice_wepw_weg_netdev(wepw->netdev);
	if (eww)
		goto eww_netdev;

	ice_viwtchnw_set_wepw_ops(vf);
	ice_wepw_set_tx_topowogy(vf->pf);

	wetuwn wepw;

eww_netdev:
	ice_wepw_wem(wepw);
eww_wepw_add:
	ice_devwink_destwoy_vf_powt(vf);
	wetuwn EWW_PTW(eww);
}

stwuct ice_wepw *ice_wepw_get_by_vsi(stwuct ice_vsi *vsi)
{
	if (!vsi->vf)
		wetuwn NUWW;

	wetuwn xa_woad(&vsi->back->eswitch.wepws, vsi->vf->wepw_id);
}

/**
 * ice_wepw_stawt_tx_queues - stawt Tx queues of powt wepwesentow
 * @wepw: pointew to wepw stwuctuwe
 */
void ice_wepw_stawt_tx_queues(stwuct ice_wepw *wepw)
{
	netif_cawwiew_on(wepw->netdev);
	netif_tx_stawt_aww_queues(wepw->netdev);
}

/**
 * ice_wepw_stop_tx_queues - stop Tx queues of powt wepwesentow
 * @wepw: pointew to wepw stwuctuwe
 */
void ice_wepw_stop_tx_queues(stwuct ice_wepw *wepw)
{
	netif_cawwiew_off(wepw->netdev);
	netif_tx_stop_aww_queues(wepw->netdev);
}

/**
 * ice_wepw_set_twaffic_vsi - set twaffic VSI fow powt wepwesentow
 * @wepw: wepw on with VSI wiww be set
 * @vsi: pointew to VSI that wiww be used by powt wepwesentow to pass twaffic
 */
void ice_wepw_set_twaffic_vsi(stwuct ice_wepw *wepw, stwuct ice_vsi *vsi)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(wepw->netdev);

	np->vsi = vsi;
}
