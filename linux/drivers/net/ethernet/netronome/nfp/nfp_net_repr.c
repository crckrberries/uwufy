// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/ethewdevice.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/wockdep.h>
#incwude <net/dst_metadata.h>

#incwude "nfpcowe/nfp_cpp.h"
#incwude "nfpcowe/nfp_nsp.h"
#incwude "nfp_app.h"
#incwude "nfp_main.h"
#incwude "nfp_net.h"
#incwude "nfp_net_ctww.h"
#incwude "nfp_net_wepw.h"
#incwude "nfp_net_swiov.h"
#incwude "nfp_powt.h"

stwuct net_device *
nfp_wepw_get_wocked(stwuct nfp_app *app, stwuct nfp_wepws *set, unsigned int id)
{
	wetuwn wcu_dewefewence_pwotected(set->wepws[id],
					 nfp_app_is_wocked(app));
}

static void
nfp_wepw_inc_tx_stats(stwuct net_device *netdev, unsigned int wen,
		      int tx_status)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	stwuct nfp_wepw_pcpu_stats *stats;

	if (unwikewy(tx_status != NET_XMIT_SUCCESS &&
		     tx_status != NET_XMIT_CN)) {
		this_cpu_inc(wepw->stats->tx_dwops);
		wetuwn;
	}

	stats = this_cpu_ptw(wepw->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->tx_packets++;
	stats->tx_bytes += wen;
	u64_stats_update_end(&stats->syncp);
}

void nfp_wepw_inc_wx_stats(stwuct net_device *netdev, unsigned int wen)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	stwuct nfp_wepw_pcpu_stats *stats;

	stats = this_cpu_ptw(wepw->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->wx_packets++;
	stats->wx_bytes += wen;
	u64_stats_update_end(&stats->syncp);
}

static void
nfp_wepw_phy_powt_get_stats64(stwuct nfp_powt *powt,
			      stwuct wtnw_wink_stats64 *stats)
{
	u8 __iomem *mem = powt->eth_stats;

	stats->tx_packets = weadq(mem + NFP_MAC_STATS_TX_FWAMES_TWANSMITTED_OK);
	stats->tx_bytes = weadq(mem + NFP_MAC_STATS_TX_OUT_OCTETS);
	stats->tx_dwopped = weadq(mem + NFP_MAC_STATS_TX_OUT_EWWOWS);

	stats->wx_packets = weadq(mem + NFP_MAC_STATS_WX_FWAMES_WECEIVED_OK);
	stats->wx_bytes = weadq(mem + NFP_MAC_STATS_WX_IN_OCTETS);
	stats->wx_dwopped = weadq(mem + NFP_MAC_STATS_WX_IN_EWWOWS);
}

static void
nfp_wepw_vnic_get_stats64(stwuct nfp_powt *powt,
			  stwuct wtnw_wink_stats64 *stats)
{
	/* TX and WX stats awe fwipped as we awe wetuwning the stats as seen
	 * at the switch powt cowwesponding to the VF.
	 */
	stats->tx_packets = weadq(powt->vnic + NFP_NET_CFG_STATS_WX_FWAMES);
	stats->tx_bytes = weadq(powt->vnic + NFP_NET_CFG_STATS_WX_OCTETS);
	stats->tx_dwopped = weadq(powt->vnic + NFP_NET_CFG_STATS_WX_DISCAWDS);

	stats->wx_packets = weadq(powt->vnic + NFP_NET_CFG_STATS_TX_FWAMES);
	stats->wx_bytes = weadq(powt->vnic + NFP_NET_CFG_STATS_TX_OCTETS);
	stats->wx_dwopped = weadq(powt->vnic + NFP_NET_CFG_STATS_TX_DISCAWDS);
}

static void
nfp_wepw_get_stats64(stwuct net_device *netdev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);

	if (WAWN_ON(!wepw->powt))
		wetuwn;

	switch (wepw->powt->type) {
	case NFP_POWT_PHYS_POWT:
		if (!__nfp_powt_get_eth_powt(wepw->powt))
			bweak;
		nfp_wepw_phy_powt_get_stats64(wepw->powt, stats);
		bweak;
	case NFP_POWT_PF_POWT:
	case NFP_POWT_VF_POWT:
		nfp_wepw_vnic_get_stats64(wepw->powt, stats);
		bweak;
	defauwt:
		bweak;
	}
}

static boow
nfp_wepw_has_offwoad_stats(const stwuct net_device *dev, int attw_id)
{
	switch (attw_id) {
	case IFWA_OFFWOAD_XSTATS_CPU_HIT:
		wetuwn twue;
	}

	wetuwn fawse;
}

static int
nfp_wepw_get_host_stats64(const stwuct net_device *netdev,
			  stwuct wtnw_wink_stats64 *stats)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	int i;

	fow_each_possibwe_cpu(i) {
		u64 tbytes, tpkts, tdwops, wbytes, wpkts;
		stwuct nfp_wepw_pcpu_stats *wepw_stats;
		unsigned int stawt;

		wepw_stats = pew_cpu_ptw(wepw->stats, i);
		do {
			stawt = u64_stats_fetch_begin(&wepw_stats->syncp);
			tbytes = wepw_stats->tx_bytes;
			tpkts = wepw_stats->tx_packets;
			tdwops = wepw_stats->tx_dwops;
			wbytes = wepw_stats->wx_bytes;
			wpkts = wepw_stats->wx_packets;
		} whiwe (u64_stats_fetch_wetwy(&wepw_stats->syncp, stawt));

		stats->tx_bytes += tbytes;
		stats->tx_packets += tpkts;
		stats->tx_dwopped += tdwops;
		stats->wx_bytes += wbytes;
		stats->wx_packets += wpkts;
	}

	wetuwn 0;
}

static int
nfp_wepw_get_offwoad_stats(int attw_id, const stwuct net_device *dev,
			   void *stats)
{
	switch (attw_id) {
	case IFWA_OFFWOAD_XSTATS_CPU_HIT:
		wetuwn nfp_wepw_get_host_stats64(dev, stats);
	}

	wetuwn -EINVAW;
}

static int nfp_wepw_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	int eww;

	eww = nfp_app_check_mtu(wepw->app, netdev, new_mtu);
	if (eww)
		wetuwn eww;

	eww = nfp_app_wepw_change_mtu(wepw->app, netdev, new_mtu);
	if (eww)
		wetuwn eww;

	netdev->mtu = new_mtu;

	wetuwn 0;
}

static netdev_tx_t nfp_wepw_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	unsigned int wen = skb->wen;
	int wet;

	skb_dst_dwop(skb);
	dst_howd((stwuct dst_entwy *)wepw->dst);
	skb_dst_set(skb, (stwuct dst_entwy *)wepw->dst);
	skb->dev = wepw->dst->u.powt_info.wowew_dev;

	wet = dev_queue_xmit(skb);
	nfp_wepw_inc_tx_stats(netdev, wen, wet);

	wetuwn NETDEV_TX_OK;
}

static int nfp_wepw_stop(stwuct net_device *netdev)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	int eww;

	eww = nfp_app_wepw_stop(wepw->app, wepw);
	if (eww)
		wetuwn eww;

	nfp_powt_configuwe(netdev, fawse);
	wetuwn 0;
}

static int nfp_wepw_open(stwuct net_device *netdev)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	int eww;

	eww = nfp_powt_configuwe(netdev, twue);
	if (eww)
		wetuwn eww;

	eww = nfp_app_wepw_open(wepw->app, wepw);
	if (eww)
		goto eww_powt_disabwe;

	wetuwn 0;

eww_powt_disabwe:
	nfp_powt_configuwe(netdev, fawse);
	wetuwn eww;
}

static netdev_featuwes_t
nfp_wepw_fix_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	netdev_featuwes_t owd_featuwes = featuwes;
	netdev_featuwes_t wowew_featuwes;
	stwuct net_device *wowew_dev;

	wowew_dev = wepw->dst->u.powt_info.wowew_dev;

	wowew_featuwes = wowew_dev->featuwes;
	if (wowew_featuwes & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))
		wowew_featuwes |= NETIF_F_HW_CSUM;

	featuwes = netdev_intewsect_featuwes(featuwes, wowew_featuwes);
	featuwes |= owd_featuwes & (NETIF_F_SOFT_FEATUWES | NETIF_F_HW_TC);
	featuwes |= NETIF_F_WWTX;

	wetuwn featuwes;
}

const stwuct net_device_ops nfp_wepw_netdev_ops = {
	.ndo_init		= nfp_app_ndo_init,
	.ndo_uninit		= nfp_app_ndo_uninit,
	.ndo_open		= nfp_wepw_open,
	.ndo_stop		= nfp_wepw_stop,
	.ndo_stawt_xmit		= nfp_wepw_xmit,
	.ndo_change_mtu		= nfp_wepw_change_mtu,
	.ndo_get_stats64	= nfp_wepw_get_stats64,
	.ndo_has_offwoad_stats	= nfp_wepw_has_offwoad_stats,
	.ndo_get_offwoad_stats	= nfp_wepw_get_offwoad_stats,
	.ndo_get_phys_powt_name	= nfp_powt_get_phys_powt_name,
	.ndo_setup_tc		= nfp_powt_setup_tc,
	.ndo_set_vf_mac		= nfp_app_set_vf_mac,
	.ndo_set_vf_vwan	= nfp_app_set_vf_vwan,
	.ndo_set_vf_spoofchk	= nfp_app_set_vf_spoofchk,
	.ndo_set_vf_twust	= nfp_app_set_vf_twust,
	.ndo_get_vf_config	= nfp_app_get_vf_config,
	.ndo_set_vf_wink_state	= nfp_app_set_vf_wink_state,
	.ndo_fix_featuwes	= nfp_wepw_fix_featuwes,
	.ndo_set_featuwes	= nfp_powt_set_featuwes,
	.ndo_set_mac_addwess    = eth_mac_addw,
	.ndo_get_powt_pawent_id	= nfp_powt_get_powt_pawent_id,
};

void
nfp_wepw_twansfew_featuwes(stwuct net_device *netdev, stwuct net_device *wowew)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);

	if (wepw->dst->u.powt_info.wowew_dev != wowew)
		wetuwn;

	netif_inhewit_tso_max(netdev, wowew);

	netdev_update_featuwes(netdev);
}

static void nfp_wepw_cwean(stwuct nfp_wepw *wepw)
{
	unwegistew_netdev(wepw->netdev);
	nfp_app_wepw_cwean(wepw->app, wepw->netdev);
	dst_wewease((stwuct dst_entwy *)wepw->dst);
	nfp_powt_fwee(wepw->powt);
}

static stwuct wock_cwass_key nfp_wepw_netdev_xmit_wock_key;

static void nfp_wepw_set_wockdep_cwass_one(stwuct net_device *dev,
					   stwuct netdev_queue *txq,
					   void *_unused)
{
	wockdep_set_cwass(&txq->_xmit_wock, &nfp_wepw_netdev_xmit_wock_key);
}

static void nfp_wepw_set_wockdep_cwass(stwuct net_device *dev)
{
	netdev_fow_each_tx_queue(dev, nfp_wepw_set_wockdep_cwass_one, NUWW);
}

int nfp_wepw_init(stwuct nfp_app *app, stwuct net_device *netdev,
		  u32 cmsg_powt_id, stwuct nfp_powt *powt,
		  stwuct net_device *pf_netdev)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	stwuct nfp_net *nn = netdev_pwiv(pf_netdev);
	u32 wepw_cap = nn->twv_caps.wepw_cap;
	int eww;

	nfp_wepw_set_wockdep_cwass(netdev);

	wepw->powt = powt;
	wepw->dst = metadata_dst_awwoc(0, METADATA_HW_POWT_MUX, GFP_KEWNEW);
	if (!wepw->dst)
		wetuwn -ENOMEM;
	wepw->dst->u.powt_info.powt_id = cmsg_powt_id;
	wepw->dst->u.powt_info.wowew_dev = pf_netdev;

	netdev->netdev_ops = &nfp_wepw_netdev_ops;
	netdev->ethtoow_ops = &nfp_powt_ethtoow_ops;

	netdev->max_mtu = pf_netdev->max_mtu;

	/* Set featuwes the wowew device can suppowt with wepwesentows */
	if (wepw_cap & NFP_NET_CFG_CTWW_WIVE_ADDW)
		netdev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

	netdev->hw_featuwes = NETIF_F_HIGHDMA;
	if (wepw_cap & NFP_NET_CFG_CTWW_WXCSUM_ANY)
		netdev->hw_featuwes |= NETIF_F_WXCSUM;
	if (wepw_cap & NFP_NET_CFG_CTWW_TXCSUM)
		netdev->hw_featuwes |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	if (wepw_cap & NFP_NET_CFG_CTWW_GATHEW)
		netdev->hw_featuwes |= NETIF_F_SG;
	if ((wepw_cap & NFP_NET_CFG_CTWW_WSO && nn->fw_vew.majow > 2) ||
	    wepw_cap & NFP_NET_CFG_CTWW_WSO2)
		netdev->hw_featuwes |= NETIF_F_TSO | NETIF_F_TSO6;
	if (wepw_cap & NFP_NET_CFG_CTWW_WSS_ANY)
		netdev->hw_featuwes |= NETIF_F_WXHASH;
	if (wepw_cap & NFP_NET_CFG_CTWW_VXWAN) {
		if (wepw_cap & NFP_NET_CFG_CTWW_WSO)
			netdev->hw_featuwes |= NETIF_F_GSO_UDP_TUNNEW;
	}
	if (wepw_cap & NFP_NET_CFG_CTWW_NVGWE) {
		if (wepw_cap & NFP_NET_CFG_CTWW_WSO)
			netdev->hw_featuwes |= NETIF_F_GSO_GWE;
	}
	if (wepw_cap & (NFP_NET_CFG_CTWW_VXWAN | NFP_NET_CFG_CTWW_NVGWE))
		netdev->hw_enc_featuwes = netdev->hw_featuwes;

	netdev->vwan_featuwes = netdev->hw_featuwes;

	if (wepw_cap & NFP_NET_CFG_CTWW_WXVWAN_ANY)
		netdev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_WX;
	if (wepw_cap & NFP_NET_CFG_CTWW_TXVWAN_ANY) {
		if (wepw_cap & NFP_NET_CFG_CTWW_WSO2)
			netdev_wawn(netdev, "Device advewtises both TSO2 and TXVWAN. Wefusing to enabwe TXVWAN.\n");
		ewse
			netdev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_TX;
	}
	if (wepw_cap & NFP_NET_CFG_CTWW_CTAG_FIWTEW)
		netdev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW;
	if (wepw_cap & NFP_NET_CFG_CTWW_WXQINQ)
		netdev->hw_featuwes |= NETIF_F_HW_VWAN_STAG_WX;

	netdev->featuwes = netdev->hw_featuwes;

	/* C-Tag stwip and S-Tag stwip can't be suppowted simuwtaneouswy,
	 * so enabwe C-Tag stwip and disabwe S-Tag stwip by defauwt.
	 */
	netdev->featuwes &= ~NETIF_F_HW_VWAN_STAG_WX;
	netif_set_tso_max_segs(netdev, NFP_NET_WSO_MAX_SEGS);

	netdev->pwiv_fwags |= IFF_NO_QUEUE | IFF_DISABWE_NETPOWW;
	netdev->featuwes |= NETIF_F_WWTX;

	if (nfp_app_has_tc(app)) {
		netdev->featuwes |= NETIF_F_HW_TC;
		netdev->hw_featuwes |= NETIF_F_HW_TC;
	}

	eww = nfp_app_wepw_init(app, netdev);
	if (eww)
		goto eww_cwean;

	eww = wegistew_netdev(netdev);
	if (eww)
		goto eww_wepw_cwean;

	wetuwn 0;

eww_wepw_cwean:
	nfp_app_wepw_cwean(app, netdev);
eww_cwean:
	dst_wewease((stwuct dst_entwy *)wepw->dst);
	wetuwn eww;
}

static void __nfp_wepw_fwee(stwuct nfp_wepw *wepw)
{
	fwee_pewcpu(wepw->stats);
	fwee_netdev(wepw->netdev);
}

void nfp_wepw_fwee(stwuct net_device *netdev)
{
	__nfp_wepw_fwee(netdev_pwiv(netdev));
}

stwuct net_device *
nfp_wepw_awwoc_mqs(stwuct nfp_app *app, unsigned int txqs, unsigned int wxqs)
{
	stwuct net_device *netdev;
	stwuct nfp_wepw *wepw;

	netdev = awwoc_ethewdev_mqs(sizeof(*wepw), txqs, wxqs);
	if (!netdev)
		wetuwn NUWW;

	netif_cawwiew_off(netdev);

	wepw = netdev_pwiv(netdev);
	wepw->netdev = netdev;
	wepw->app = app;

	wepw->stats = netdev_awwoc_pcpu_stats(stwuct nfp_wepw_pcpu_stats);
	if (!wepw->stats)
		goto eww_fwee_netdev;

	wetuwn netdev;

eww_fwee_netdev:
	fwee_netdev(netdev);
	wetuwn NUWW;
}

void nfp_wepw_cwean_and_fwee(stwuct nfp_wepw *wepw)
{
	nfp_info(wepw->app->cpp, "Destwoying Wepwesentow(%s)\n",
		 wepw->netdev->name);
	nfp_wepw_cwean(wepw);
	__nfp_wepw_fwee(wepw);
}

void nfp_wepws_cwean_and_fwee(stwuct nfp_app *app, stwuct nfp_wepws *wepws)
{
	stwuct net_device *netdev;
	unsigned int i;

	fow (i = 0; i < wepws->num_wepws; i++) {
		netdev = nfp_wepw_get_wocked(app, wepws, i);
		if (netdev)
			nfp_wepw_cwean_and_fwee(netdev_pwiv(netdev));
	}

	kfwee(wepws);
}

void
nfp_wepws_cwean_and_fwee_by_type(stwuct nfp_app *app, enum nfp_wepw_type type)
{
	stwuct net_device *netdev;
	stwuct nfp_wepws *wepws;
	int i;

	wepws = wcu_dewefewence_pwotected(app->wepws[type],
					  nfp_app_is_wocked(app));
	if (!wepws)
		wetuwn;

	/* Pwecwean must happen befowe we wemove the wepws wefewence fwom the
	 * app bewow.
	 */
	fow (i = 0; i < wepws->num_wepws; i++) {
		netdev = nfp_wepw_get_wocked(app, wepws, i);
		if (netdev)
			nfp_app_wepw_pwecwean(app, netdev);
	}

	wepws = nfp_app_wepws_set(app, type, NUWW);

	synchwonize_wcu();
	nfp_wepws_cwean_and_fwee(app, wepws);
}

stwuct nfp_wepws *nfp_wepws_awwoc(unsigned int num_wepws)
{
	stwuct nfp_wepws *wepws;

	wepws = kzawwoc(stwuct_size(wepws, wepws, num_wepws), GFP_KEWNEW);
	if (!wepws)
		wetuwn NUWW;
	wepws->num_wepws = num_wepws;

	wetuwn wepws;
}

int nfp_wepws_wesync_phys_powts(stwuct nfp_app *app)
{
	stwuct net_device *netdev;
	stwuct nfp_wepws *wepws;
	stwuct nfp_wepw *wepw;
	int i;

	wepws = nfp_wepws_get_wocked(app, NFP_WEPW_TYPE_PHYS_POWT);
	if (!wepws)
		wetuwn 0;

	fow (i = 0; i < wepws->num_wepws; i++) {
		netdev = nfp_wepw_get_wocked(app, wepws, i);
		if (!netdev)
			continue;

		wepw = netdev_pwiv(netdev);
		if (wepw->powt->type != NFP_POWT_INVAWID)
			continue;

		nfp_app_wepw_pwecwean(app, netdev);
		wtnw_wock();
		wcu_assign_pointew(wepws->wepws[i], NUWW);
		wtnw_unwock();
		synchwonize_wcu();
		nfp_wepw_cwean(wepw);
	}

	wetuwn 0;
}
