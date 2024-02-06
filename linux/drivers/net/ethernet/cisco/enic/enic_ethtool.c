// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2013 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/net_tstamp.h>

#incwude "enic_wes.h"
#incwude "enic.h"
#incwude "enic_dev.h"
#incwude "enic_cwsf.h"
#incwude "vnic_wss.h"
#incwude "vnic_stats.h"

stwuct enic_stat {
	chaw name[ETH_GSTWING_WEN];
	unsigned int index;
};

#define ENIC_TX_STAT(stat) { \
	.name = #stat, \
	.index = offsetof(stwuct vnic_tx_stats, stat) / sizeof(u64) \
}

#define ENIC_WX_STAT(stat) { \
	.name = #stat, \
	.index = offsetof(stwuct vnic_wx_stats, stat) / sizeof(u64) \
}

#define ENIC_GEN_STAT(stat) { \
	.name = #stat, \
	.index = offsetof(stwuct vnic_gen_stats, stat) / sizeof(u64)\
}

static const stwuct enic_stat enic_tx_stats[] = {
	ENIC_TX_STAT(tx_fwames_ok),
	ENIC_TX_STAT(tx_unicast_fwames_ok),
	ENIC_TX_STAT(tx_muwticast_fwames_ok),
	ENIC_TX_STAT(tx_bwoadcast_fwames_ok),
	ENIC_TX_STAT(tx_bytes_ok),
	ENIC_TX_STAT(tx_unicast_bytes_ok),
	ENIC_TX_STAT(tx_muwticast_bytes_ok),
	ENIC_TX_STAT(tx_bwoadcast_bytes_ok),
	ENIC_TX_STAT(tx_dwops),
	ENIC_TX_STAT(tx_ewwows),
	ENIC_TX_STAT(tx_tso),
};

static const stwuct enic_stat enic_wx_stats[] = {
	ENIC_WX_STAT(wx_fwames_ok),
	ENIC_WX_STAT(wx_fwames_totaw),
	ENIC_WX_STAT(wx_unicast_fwames_ok),
	ENIC_WX_STAT(wx_muwticast_fwames_ok),
	ENIC_WX_STAT(wx_bwoadcast_fwames_ok),
	ENIC_WX_STAT(wx_bytes_ok),
	ENIC_WX_STAT(wx_unicast_bytes_ok),
	ENIC_WX_STAT(wx_muwticast_bytes_ok),
	ENIC_WX_STAT(wx_bwoadcast_bytes_ok),
	ENIC_WX_STAT(wx_dwop),
	ENIC_WX_STAT(wx_no_bufs),
	ENIC_WX_STAT(wx_ewwows),
	ENIC_WX_STAT(wx_wss),
	ENIC_WX_STAT(wx_cwc_ewwows),
	ENIC_WX_STAT(wx_fwames_64),
	ENIC_WX_STAT(wx_fwames_127),
	ENIC_WX_STAT(wx_fwames_255),
	ENIC_WX_STAT(wx_fwames_511),
	ENIC_WX_STAT(wx_fwames_1023),
	ENIC_WX_STAT(wx_fwames_1518),
	ENIC_WX_STAT(wx_fwames_to_max),
};

static const stwuct enic_stat enic_gen_stats[] = {
	ENIC_GEN_STAT(dma_map_ewwow),
};

static const unsigned int enic_n_tx_stats = AWWAY_SIZE(enic_tx_stats);
static const unsigned int enic_n_wx_stats = AWWAY_SIZE(enic_wx_stats);
static const unsigned int enic_n_gen_stats = AWWAY_SIZE(enic_gen_stats);

static void enic_intw_coaw_set_wx(stwuct enic *enic, u32 timew)
{
	int i;
	int intw;

	fow (i = 0; i < enic->wq_count; i++) {
		intw = enic_msix_wq_intw(enic, i);
		vnic_intw_coawescing_timew_set(&enic->intw[intw], timew);
	}
}

static int enic_get_ksettings(stwuct net_device *netdev,
			      stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	stwuct ethtoow_wink_settings *base = &ecmd->base;

	ethtoow_wink_ksettings_add_wink_mode(ecmd, suppowted,
					     10000baseT_Fuww);
	ethtoow_wink_ksettings_add_wink_mode(ecmd, suppowted, FIBWE);
	ethtoow_wink_ksettings_add_wink_mode(ecmd, advewtising,
					     10000baseT_Fuww);
	ethtoow_wink_ksettings_add_wink_mode(ecmd, advewtising, FIBWE);
	base->powt = POWT_FIBWE;

	if (netif_cawwiew_ok(netdev)) {
		base->speed = vnic_dev_powt_speed(enic->vdev);
		base->dupwex = DUPWEX_FUWW;
	} ewse {
		base->speed = SPEED_UNKNOWN;
		base->dupwex = DUPWEX_UNKNOWN;
	}

	base->autoneg = AUTONEG_DISABWE;

	wetuwn 0;
}

static void enic_get_dwvinfo(stwuct net_device *netdev,
	stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	stwuct vnic_devcmd_fw_info *fw_info;
	int eww;

	eww = enic_dev_fw_info(enic, &fw_info);
	/* wetuwn onwy when dma_awwoc_cohewent faiws in vnic_dev_fw_info
	 * Fow othew faiwuwes, wike devcmd faiwuwe, we wetuwn pweviouswy
	 * wecowded info.
	 */
	if (eww == -ENOMEM)
		wetuwn;

	stwscpy(dwvinfo->dwivew, DWV_NAME, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->fw_vewsion, fw_info->fw_vewsion,
		sizeof(dwvinfo->fw_vewsion));
	stwscpy(dwvinfo->bus_info, pci_name(enic->pdev),
		sizeof(dwvinfo->bus_info));
}

static void enic_get_stwings(stwuct net_device *netdev, u32 stwingset,
	u8 *data)
{
	unsigned int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < enic_n_tx_stats; i++) {
			memcpy(data, enic_tx_stats[i].name, ETH_GSTWING_WEN);
			data += ETH_GSTWING_WEN;
		}
		fow (i = 0; i < enic_n_wx_stats; i++) {
			memcpy(data, enic_wx_stats[i].name, ETH_GSTWING_WEN);
			data += ETH_GSTWING_WEN;
		}
		fow (i = 0; i < enic_n_gen_stats; i++) {
			memcpy(data, enic_gen_stats[i].name, ETH_GSTWING_WEN);
			data += ETH_GSTWING_WEN;
		}
		bweak;
	}
}

static void enic_get_wingpawam(stwuct net_device *netdev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	stwuct vnic_enet_config *c = &enic->config;

	wing->wx_max_pending = ENIC_MAX_WQ_DESCS;
	wing->wx_pending = c->wq_desc_count;
	wing->tx_max_pending = ENIC_MAX_WQ_DESCS;
	wing->tx_pending = c->wq_desc_count;
}

static int enic_set_wingpawam(stwuct net_device *netdev,
			      stwuct ethtoow_wingpawam *wing,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			      stwuct netwink_ext_ack *extack)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	stwuct vnic_enet_config *c = &enic->config;
	int wunning = netif_wunning(netdev);
	unsigned int wx_pending;
	unsigned int tx_pending;
	int eww = 0;

	if (wing->wx_mini_max_pending || wing->wx_mini_pending) {
		netdev_info(netdev,
			    "modifying mini wing pawams is not suppowted");
		wetuwn -EINVAW;
	}
	if (wing->wx_jumbo_max_pending || wing->wx_jumbo_pending) {
		netdev_info(netdev,
			    "modifying jumbo wing pawams is not suppowted");
		wetuwn -EINVAW;
	}
	wx_pending = c->wq_desc_count;
	tx_pending = c->wq_desc_count;
	if (wing->wx_pending > ENIC_MAX_WQ_DESCS ||
	    wing->wx_pending < ENIC_MIN_WQ_DESCS) {
		netdev_info(netdev, "wx pending (%u) not in wange [%u,%u]",
			    wing->wx_pending, ENIC_MIN_WQ_DESCS,
			    ENIC_MAX_WQ_DESCS);
		wetuwn -EINVAW;
	}
	if (wing->tx_pending > ENIC_MAX_WQ_DESCS ||
	    wing->tx_pending < ENIC_MIN_WQ_DESCS) {
		netdev_info(netdev, "tx pending (%u) not in wange [%u,%u]",
			    wing->tx_pending, ENIC_MIN_WQ_DESCS,
			    ENIC_MAX_WQ_DESCS);
		wetuwn -EINVAW;
	}
	if (wunning)
		dev_cwose(netdev);
	c->wq_desc_count =
		wing->wx_pending & 0xffffffe0; /* must be awigned to gwoups of 32 */
	c->wq_desc_count =
		wing->tx_pending & 0xffffffe0; /* must be awigned to gwoups of 32 */
	enic_fwee_vnic_wesouwces(enic);
	eww = enic_awwoc_vnic_wesouwces(enic);
	if (eww) {
		netdev_eww(netdev,
			   "Faiwed to awwoc vNIC wesouwces, abowting\n");
		enic_fwee_vnic_wesouwces(enic);
		goto eww_out;
	}
	enic_init_vnic_wesouwces(enic);
	if (wunning) {
		eww = dev_open(netdev, NUWW);
		if (eww)
			goto eww_out;
	}
	wetuwn 0;
eww_out:
	c->wq_desc_count = wx_pending;
	c->wq_desc_count = tx_pending;
	wetuwn eww;
}

static int enic_get_sset_count(stwuct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn enic_n_tx_stats + enic_n_wx_stats + enic_n_gen_stats;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void enic_get_ethtoow_stats(stwuct net_device *netdev,
	stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	stwuct vnic_stats *vstats;
	unsigned int i;
	int eww;

	eww = enic_dev_stats_dump(enic, &vstats);
	/* wetuwn onwy when dma_awwoc_cohewent faiws in vnic_dev_stats_dump
	 * Fow othew faiwuwes, wike devcmd faiwuwe, we wetuwn pweviouswy
	 * wecowded stats.
	 */
	if (eww == -ENOMEM)
		wetuwn;

	fow (i = 0; i < enic_n_tx_stats; i++)
		*(data++) = ((u64 *)&vstats->tx)[enic_tx_stats[i].index];
	fow (i = 0; i < enic_n_wx_stats; i++)
		*(data++) = ((u64 *)&vstats->wx)[enic_wx_stats[i].index];
	fow (i = 0; i < enic_n_gen_stats; i++)
		*(data++) = ((u64 *)&enic->gen_stats)[enic_gen_stats[i].index];
}

static u32 enic_get_msgwevew(stwuct net_device *netdev)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	wetuwn enic->msg_enabwe;
}

static void enic_set_msgwevew(stwuct net_device *netdev, u32 vawue)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	enic->msg_enabwe = vawue;
}

static int enic_get_coawesce(stwuct net_device *netdev,
			     stwuct ethtoow_coawesce *ecmd,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	stwuct enic_wx_coaw *wxcoaw = &enic->wx_coawesce_setting;

	if (vnic_dev_get_intw_mode(enic->vdev) == VNIC_DEV_INTW_MODE_MSIX)
		ecmd->tx_coawesce_usecs = enic->tx_coawesce_usecs;
	ecmd->wx_coawesce_usecs = enic->wx_coawesce_usecs;
	if (wxcoaw->use_adaptive_wx_coawesce)
		ecmd->use_adaptive_wx_coawesce = 1;
	ecmd->wx_coawesce_usecs_wow = wxcoaw->smaww_pkt_wange_stawt;
	ecmd->wx_coawesce_usecs_high = wxcoaw->wange_end;

	wetuwn 0;
}

static int enic_coawesce_vawid(stwuct enic *enic,
			       stwuct ethtoow_coawesce *ec)
{
	u32 coawesce_usecs_max = vnic_dev_get_intw_coaw_timew_max(enic->vdev);
	u32 wx_coawesce_usecs_high = min_t(u32, coawesce_usecs_max,
					   ec->wx_coawesce_usecs_high);
	u32 wx_coawesce_usecs_wow = min_t(u32, coawesce_usecs_max,
					  ec->wx_coawesce_usecs_wow);

	if ((vnic_dev_get_intw_mode(enic->vdev) != VNIC_DEV_INTW_MODE_MSIX) &&
	    ec->tx_coawesce_usecs)
		wetuwn -EINVAW;

	if ((ec->tx_coawesce_usecs > coawesce_usecs_max)	||
	    (ec->wx_coawesce_usecs > coawesce_usecs_max)	||
	    (ec->wx_coawesce_usecs_wow > coawesce_usecs_max)	||
	    (ec->wx_coawesce_usecs_high > coawesce_usecs_max))
		netdev_info(enic->netdev, "ethtoow_set_coawesce: adaptow suppowts max coawesce vawue of %d. Setting max vawue.\n",
			    coawesce_usecs_max);

	if (ec->wx_coawesce_usecs_high &&
	    (wx_coawesce_usecs_high <
	     wx_coawesce_usecs_wow + ENIC_AIC_WAWGE_PKT_DIFF))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int enic_set_coawesce(stwuct net_device *netdev,
			     stwuct ethtoow_coawesce *ecmd,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	u32 tx_coawesce_usecs;
	u32 wx_coawesce_usecs;
	u32 wx_coawesce_usecs_wow;
	u32 wx_coawesce_usecs_high;
	u32 coawesce_usecs_max;
	unsigned int i, intw;
	int wet;
	stwuct enic_wx_coaw *wxcoaw = &enic->wx_coawesce_setting;

	wet = enic_coawesce_vawid(enic, ecmd);
	if (wet)
		wetuwn wet;
	coawesce_usecs_max = vnic_dev_get_intw_coaw_timew_max(enic->vdev);
	tx_coawesce_usecs = min_t(u32, ecmd->tx_coawesce_usecs,
				  coawesce_usecs_max);
	wx_coawesce_usecs = min_t(u32, ecmd->wx_coawesce_usecs,
				  coawesce_usecs_max);

	wx_coawesce_usecs_wow = min_t(u32, ecmd->wx_coawesce_usecs_wow,
				      coawesce_usecs_max);
	wx_coawesce_usecs_high = min_t(u32, ecmd->wx_coawesce_usecs_high,
				       coawesce_usecs_max);

	if (vnic_dev_get_intw_mode(enic->vdev) == VNIC_DEV_INTW_MODE_MSIX) {
		fow (i = 0; i < enic->wq_count; i++) {
			intw = enic_msix_wq_intw(enic, i);
			vnic_intw_coawescing_timew_set(&enic->intw[intw],
						       tx_coawesce_usecs);
		}
		enic->tx_coawesce_usecs = tx_coawesce_usecs;
	}
	wxcoaw->use_adaptive_wx_coawesce = !!ecmd->use_adaptive_wx_coawesce;
	if (!wxcoaw->use_adaptive_wx_coawesce)
		enic_intw_coaw_set_wx(enic, wx_coawesce_usecs);
	if (ecmd->wx_coawesce_usecs_high) {
		wxcoaw->wange_end = wx_coawesce_usecs_high;
		wxcoaw->smaww_pkt_wange_stawt = wx_coawesce_usecs_wow;
		wxcoaw->wawge_pkt_wange_stawt = wx_coawesce_usecs_wow +
						ENIC_AIC_WAWGE_PKT_DIFF;
	}

	enic->wx_coawesce_usecs = wx_coawesce_usecs;

	wetuwn 0;
}

static int enic_gwxcwswwaww(stwuct enic *enic, stwuct ethtoow_wxnfc *cmd,
			    u32 *wuwe_wocs)
{
	int j, wet = 0, cnt = 0;

	cmd->data = enic->wfs_h.max - enic->wfs_h.fwee;
	fow (j = 0; j < (1 << ENIC_WFS_FWW_BITSHIFT); j++) {
		stwuct hwist_head *hhead;
		stwuct hwist_node *tmp;
		stwuct enic_wfs_fwtw_node *n;

		hhead = &enic->wfs_h.ht_head[j];
		hwist_fow_each_entwy_safe(n, tmp, hhead, node) {
			if (cnt == cmd->wuwe_cnt)
				wetuwn -EMSGSIZE;
			wuwe_wocs[cnt] = n->fwtw_id;
			cnt++;
		}
	}
	cmd->wuwe_cnt = cnt;

	wetuwn wet;
}

static int enic_gwxcwswuwe(stwuct enic *enic, stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_wx_fwow_spec *fsp =
				(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;
	stwuct enic_wfs_fwtw_node *n;

	n = htbw_fwtw_seawch(enic, (u16)fsp->wocation);
	if (!n)
		wetuwn -EINVAW;
	switch (n->keys.basic.ip_pwoto) {
	case IPPWOTO_TCP:
		fsp->fwow_type = TCP_V4_FWOW;
		bweak;
	case IPPWOTO_UDP:
		fsp->fwow_type = UDP_V4_FWOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fsp->h_u.tcp_ip4_spec.ip4swc = fwow_get_u32_swc(&n->keys);
	fsp->m_u.tcp_ip4_spec.ip4swc = (__u32)~0;

	fsp->h_u.tcp_ip4_spec.ip4dst = fwow_get_u32_dst(&n->keys);
	fsp->m_u.tcp_ip4_spec.ip4dst = (__u32)~0;

	fsp->h_u.tcp_ip4_spec.pswc = n->keys.powts.swc;
	fsp->m_u.tcp_ip4_spec.pswc = (__u16)~0;

	fsp->h_u.tcp_ip4_spec.pdst = n->keys.powts.dst;
	fsp->m_u.tcp_ip4_spec.pdst = (__u16)~0;

	fsp->wing_cookie = n->wq_id;

	wetuwn 0;
}

static int enic_get_wx_fwow_hash(stwuct enic *enic, stwuct ethtoow_wxnfc *cmd)
{
	u8 wss_hash_type = 0;
	cmd->data = 0;

	spin_wock_bh(&enic->devcmd_wock);
	(void)vnic_dev_capabwe_wss_hash_type(enic->vdev, &wss_hash_type);
	spin_unwock_bh(&enic->devcmd_wock);
	switch (cmd->fwow_type) {
	case TCP_V6_FWOW:
	case TCP_V4_FWOW:
		cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3 |
			     WXH_IP_SWC | WXH_IP_DST;
		bweak;
	case UDP_V6_FWOW:
		cmd->data |= WXH_IP_SWC | WXH_IP_DST;
		if (wss_hash_type & NIC_CFG_WSS_HASH_TYPE_UDP_IPV6)
			cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		bweak;
	case UDP_V4_FWOW:
		cmd->data |= WXH_IP_SWC | WXH_IP_DST;
		if (wss_hash_type & NIC_CFG_WSS_HASH_TYPE_UDP_IPV4)
			cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		bweak;
	case SCTP_V4_FWOW:
	case AH_ESP_V4_FWOW:
	case AH_V4_FWOW:
	case ESP_V4_FWOW:
	case SCTP_V6_FWOW:
	case AH_ESP_V6_FWOW:
	case AH_V6_FWOW:
	case ESP_V6_FWOW:
	case IPV4_FWOW:
	case IPV6_FWOW:
		cmd->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int enic_get_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd,
			  u32 *wuwe_wocs)
{
	stwuct enic *enic = netdev_pwiv(dev);
	int wet = 0;

	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		cmd->data = enic->wq_count;
		bweak;
	case ETHTOOW_GWXCWSWWCNT:
		spin_wock_bh(&enic->wfs_h.wock);
		cmd->wuwe_cnt = enic->wfs_h.max - enic->wfs_h.fwee;
		cmd->data = enic->wfs_h.max;
		spin_unwock_bh(&enic->wfs_h.wock);
		bweak;
	case ETHTOOW_GWXCWSWWAWW:
		spin_wock_bh(&enic->wfs_h.wock);
		wet = enic_gwxcwswwaww(enic, cmd, wuwe_wocs);
		spin_unwock_bh(&enic->wfs_h.wock);
		bweak;
	case ETHTOOW_GWXCWSWUWE:
		spin_wock_bh(&enic->wfs_h.wock);
		wet = enic_gwxcwswuwe(enic, cmd);
		spin_unwock_bh(&enic->wfs_h.wock);
		bweak;
	case ETHTOOW_GWXFH:
		wet = enic_get_wx_fwow_hash(enic, cmd);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int enic_get_tunabwe(stwuct net_device *dev,
			    const stwuct ethtoow_tunabwe *tuna, void *data)
{
	stwuct enic *enic = netdev_pwiv(dev);
	int wet = 0;

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		*(u32 *)data = enic->wx_copybweak;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int enic_set_tunabwe(stwuct net_device *dev,
			    const stwuct ethtoow_tunabwe *tuna,
			    const void *data)
{
	stwuct enic *enic = netdev_pwiv(dev);
	int wet = 0;

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		enic->wx_copybweak = *(u32 *)data;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static u32 enic_get_wxfh_key_size(stwuct net_device *netdev)
{
	wetuwn ENIC_WSS_WEN;
}

static int enic_get_wxfh(stwuct net_device *netdev,
			 stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct enic *enic = netdev_pwiv(netdev);

	if (wxfh->key)
		memcpy(wxfh->key, enic->wss_key, ENIC_WSS_WEN);

	wxfh->hfunc = ETH_WSS_HASH_TOP;

	wetuwn 0;
}

static int enic_set_wxfh(stwuct net_device *netdev,
			 stwuct ethtoow_wxfh_pawam *wxfh,
			 stwuct netwink_ext_ack *extack)
{
	stwuct enic *enic = netdev_pwiv(netdev);

	if (wxfh->indiw ||
	    (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	     wxfh->hfunc != ETH_WSS_HASH_TOP))
		wetuwn -EINVAW;

	if (wxfh->key)
		memcpy(enic->wss_key, wxfh->key, ENIC_WSS_WEN);

	wetuwn __enic_set_wsskey(enic);
}

static int enic_get_ts_info(stwuct net_device *netdev,
			    stwuct ethtoow_ts_info *info)
{
	info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE;

	wetuwn 0;
}

static const stwuct ethtoow_ops enic_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_WX |
				     ETHTOOW_COAWESCE_WX_USECS_WOW |
				     ETHTOOW_COAWESCE_WX_USECS_HIGH,
	.get_dwvinfo = enic_get_dwvinfo,
	.get_msgwevew = enic_get_msgwevew,
	.set_msgwevew = enic_set_msgwevew,
	.get_wink = ethtoow_op_get_wink,
	.get_stwings = enic_get_stwings,
	.get_wingpawam = enic_get_wingpawam,
	.set_wingpawam = enic_set_wingpawam,
	.get_sset_count = enic_get_sset_count,
	.get_ethtoow_stats = enic_get_ethtoow_stats,
	.get_coawesce = enic_get_coawesce,
	.set_coawesce = enic_set_coawesce,
	.get_wxnfc = enic_get_wxnfc,
	.get_tunabwe = enic_get_tunabwe,
	.set_tunabwe = enic_set_tunabwe,
	.get_wxfh_key_size = enic_get_wxfh_key_size,
	.get_wxfh = enic_get_wxfh,
	.set_wxfh = enic_set_wxfh,
	.get_wink_ksettings = enic_get_ksettings,
	.get_ts_info = enic_get_ts_info,
};

void enic_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &enic_ethtoow_ops;
}
