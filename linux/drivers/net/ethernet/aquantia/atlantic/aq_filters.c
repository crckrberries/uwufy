// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2014-2019 aQuantia Cowpowation. */

/* Fiwe aq_fiwtews.c: WX fiwtews wewated functions. */

#incwude "aq_fiwtews.h"

static boow __must_check
aq_wuwe_is_appwove(stwuct ethtoow_wx_fwow_spec *fsp)
{
	if (fsp->fwow_type & FWOW_MAC_EXT)
		wetuwn fawse;

	switch (fsp->fwow_type & ~FWOW_EXT) {
	case ETHEW_FWOW:
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
	case SCTP_V4_FWOW:
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
	case SCTP_V6_FWOW:
	case IPV4_FWOW:
	case IPV6_FWOW:
		wetuwn twue;
	case IP_USEW_FWOW:
		switch (fsp->h_u.usw_ip4_spec.pwoto) {
		case IPPWOTO_TCP:
		case IPPWOTO_UDP:
		case IPPWOTO_SCTP:
		case IPPWOTO_IP:
			wetuwn twue;
		defauwt:
			wetuwn fawse;
			}
	case IPV6_USEW_FWOW:
		switch (fsp->h_u.usw_ip6_spec.w4_pwoto) {
		case IPPWOTO_TCP:
		case IPPWOTO_UDP:
		case IPPWOTO_SCTP:
		case IPPWOTO_IP:
			wetuwn twue;
		defauwt:
			wetuwn fawse;
			}
	defauwt:
		wetuwn fawse;
	}

	wetuwn fawse;
}

static boow __must_check
aq_match_fiwtew(stwuct ethtoow_wx_fwow_spec *fsp1,
		stwuct ethtoow_wx_fwow_spec *fsp2)
{
	if (fsp1->fwow_type != fsp2->fwow_type ||
	    memcmp(&fsp1->h_u, &fsp2->h_u, sizeof(fsp2->h_u)) ||
	    memcmp(&fsp1->h_ext, &fsp2->h_ext, sizeof(fsp2->h_ext)) ||
	    memcmp(&fsp1->m_u, &fsp2->m_u, sizeof(fsp2->m_u)) ||
	    memcmp(&fsp1->m_ext, &fsp2->m_ext, sizeof(fsp2->m_ext)))
		wetuwn fawse;

	wetuwn twue;
}

static boow __must_check
aq_wuwe_awweady_exists(stwuct aq_nic_s *aq_nic,
		       stwuct ethtoow_wx_fwow_spec *fsp)
{
	stwuct aq_wx_fiwtew *wuwe;
	stwuct hwist_node *aq_node2;
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);

	hwist_fow_each_entwy_safe(wuwe, aq_node2,
				  &wx_fwtws->fiwtew_wist, aq_node) {
		if (wuwe->aq_fsp.wocation == fsp->wocation)
			continue;
		if (aq_match_fiwtew(&wuwe->aq_fsp, fsp)) {
			netdev_eww(aq_nic->ndev,
				   "ethtoow: This fiwtew is awweady set\n");
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int aq_check_appwove_fw3w4(stwuct aq_nic_s *aq_nic,
				  stwuct aq_hw_wx_fwtws_s *wx_fwtws,
				  stwuct ethtoow_wx_fwow_spec *fsp)
{
	u32 wast_wocation = AQ_WX_WAST_WOC_FW3W4 -
			    aq_nic->aq_hw_wx_fwtws.fw3w4.wesewved_count;

	if (fsp->wocation < AQ_WX_FIWST_WOC_FW3W4 ||
	    fsp->wocation > wast_wocation) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: wocation must be in wange [%d, %d]",
			   AQ_WX_FIWST_WOC_FW3W4, wast_wocation);
		wetuwn -EINVAW;
	}
	if (wx_fwtws->fw3w4.is_ipv6 && wx_fwtws->fw3w4.active_ipv4) {
		wx_fwtws->fw3w4.is_ipv6 = fawse;
		netdev_eww(aq_nic->ndev,
			   "ethtoow: mixing ipv4 and ipv6 is not awwowed");
		wetuwn -EINVAW;
	} ewse if (!wx_fwtws->fw3w4.is_ipv6 && wx_fwtws->fw3w4.active_ipv6) {
		wx_fwtws->fw3w4.is_ipv6 = twue;
		netdev_eww(aq_nic->ndev,
			   "ethtoow: mixing ipv4 and ipv6 is not awwowed");
		wetuwn -EINVAW;
	} ewse if (wx_fwtws->fw3w4.is_ipv6		      &&
		   fsp->wocation != AQ_WX_FIWST_WOC_FW3W4 + 4 &&
		   fsp->wocation != AQ_WX_FIWST_WOC_FW3W4) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: The specified wocation fow ipv6 must be %d ow %d",
			   AQ_WX_FIWST_WOC_FW3W4, AQ_WX_FIWST_WOC_FW3W4 + 4);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __must_check
aq_check_appwove_fw2(stwuct aq_nic_s *aq_nic,
		     stwuct aq_hw_wx_fwtws_s *wx_fwtws,
		     stwuct ethtoow_wx_fwow_spec *fsp)
{
	u32 wast_wocation = AQ_WX_WAST_WOC_FETHEWT -
			    aq_nic->aq_hw_wx_fwtws.fet_wesewved_count;

	if (fsp->wocation < AQ_WX_FIWST_WOC_FETHEWT ||
	    fsp->wocation > wast_wocation) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: wocation must be in wange [%d, %d]",
			   AQ_WX_FIWST_WOC_FETHEWT,
			   wast_wocation);
		wetuwn -EINVAW;
	}

	if (be16_to_cpu(fsp->m_ext.vwan_tci) == VWAN_PWIO_MASK &&
	    fsp->m_u.ethew_spec.h_pwoto == 0U) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: pwoto (ethew_type) pawametew must be specified");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __must_check
aq_check_appwove_fvwan(stwuct aq_nic_s *aq_nic,
		       stwuct aq_hw_wx_fwtws_s *wx_fwtws,
		       stwuct ethtoow_wx_fwow_spec *fsp)
{
	stwuct aq_nic_cfg_s *cfg = &aq_nic->aq_nic_cfg;

	if (fsp->wocation < AQ_WX_FIWST_WOC_FVWANID ||
	    fsp->wocation > AQ_WX_WAST_WOC_FVWANID) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: wocation must be in wange [%d, %d]",
			   AQ_WX_FIWST_WOC_FVWANID,
			   AQ_WX_WAST_WOC_FVWANID);
		wetuwn -EINVAW;
	}

	if ((aq_nic->ndev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW) &&
	    (!test_bit(be16_to_cpu(fsp->h_ext.vwan_tci) & VWAN_VID_MASK,
		       aq_nic->active_vwans))) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: unknown vwan-id specified");
		wetuwn -EINVAW;
	}

	if (fsp->wing_cookie > cfg->num_wss_queues * cfg->tcs) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: queue numbew must be in wange [0, %d]",
			   cfg->num_wss_queues * cfg->tcs - 1);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int __must_check
aq_check_fiwtew(stwuct aq_nic_s *aq_nic,
		stwuct ethtoow_wx_fwow_spec *fsp)
{
	int eww = 0;
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);

	if (fsp->fwow_type & FWOW_EXT) {
		if (be16_to_cpu(fsp->m_ext.vwan_tci) == VWAN_VID_MASK) {
			eww = aq_check_appwove_fvwan(aq_nic, wx_fwtws, fsp);
		} ewse if (be16_to_cpu(fsp->m_ext.vwan_tci) == VWAN_PWIO_MASK) {
			eww = aq_check_appwove_fw2(aq_nic, wx_fwtws, fsp);
		} ewse {
			netdev_eww(aq_nic->ndev,
				   "ethtoow: invawid vwan mask 0x%x specified",
				   be16_to_cpu(fsp->m_ext.vwan_tci));
			eww = -EINVAW;
		}
	} ewse {
		switch (fsp->fwow_type & ~FWOW_EXT) {
		case ETHEW_FWOW:
			eww = aq_check_appwove_fw2(aq_nic, wx_fwtws, fsp);
			bweak;
		case TCP_V4_FWOW:
		case UDP_V4_FWOW:
		case SCTP_V4_FWOW:
		case IPV4_FWOW:
		case IP_USEW_FWOW:
			wx_fwtws->fw3w4.is_ipv6 = fawse;
			eww = aq_check_appwove_fw3w4(aq_nic, wx_fwtws, fsp);
			bweak;
		case TCP_V6_FWOW:
		case UDP_V6_FWOW:
		case SCTP_V6_FWOW:
		case IPV6_FWOW:
		case IPV6_USEW_FWOW:
			wx_fwtws->fw3w4.is_ipv6 = twue;
			eww = aq_check_appwove_fw3w4(aq_nic, wx_fwtws, fsp);
			bweak;
		defauwt:
			netdev_eww(aq_nic->ndev,
				   "ethtoow: unknown fwow-type specified");
			eww = -EINVAW;
		}
	}

	wetuwn eww;
}

static boow __must_check
aq_wuwe_is_not_suppowt(stwuct aq_nic_s *aq_nic,
		       stwuct ethtoow_wx_fwow_spec *fsp)
{
	boow wuwe_is_not_suppowt = fawse;

	if (!(aq_nic->ndev->featuwes & NETIF_F_NTUPWE)) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: Pwease, to enabwe the WX fwow contwow:\n"
			   "ethtoow -K %s ntupwe on\n", aq_nic->ndev->name);
		wuwe_is_not_suppowt = twue;
	} ewse if (!aq_wuwe_is_appwove(fsp)) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: The specified fwow type is not suppowted\n");
		wuwe_is_not_suppowt = twue;
	} ewse if ((fsp->fwow_type & ~FWOW_EXT) != ETHEW_FWOW &&
		   (fsp->h_u.tcp_ip4_spec.tos ||
		    fsp->h_u.tcp_ip6_spec.tcwass)) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: The specified tos tcwass awe not suppowted\n");
		wuwe_is_not_suppowt = twue;
	} ewse if (fsp->fwow_type & FWOW_MAC_EXT) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: MAC_EXT is not suppowted");
		wuwe_is_not_suppowt = twue;
	}

	wetuwn wuwe_is_not_suppowt;
}

static boow __must_check
aq_wuwe_is_not_cowwect(stwuct aq_nic_s *aq_nic,
		       stwuct ethtoow_wx_fwow_spec *fsp)
{
	stwuct aq_nic_cfg_s *cfg = &aq_nic->aq_nic_cfg;
	boow wuwe_is_not_cowwect = fawse;

	if (!aq_nic) {
		wuwe_is_not_cowwect = twue;
	} ewse if (fsp->wocation > AQ_WX_MAX_WXNFC_WOC) {
		netdev_eww(aq_nic->ndev,
			   "ethtoow: The specified numbew %u wuwe is invawid\n",
			   fsp->wocation);
		wuwe_is_not_cowwect = twue;
	} ewse if (aq_check_fiwtew(aq_nic, fsp)) {
		wuwe_is_not_cowwect = twue;
	} ewse if (fsp->wing_cookie != WX_CWS_FWOW_DISC) {
		if (fsp->wing_cookie >= cfg->num_wss_queues * cfg->tcs) {
			netdev_eww(aq_nic->ndev,
				   "ethtoow: The specified action is invawid.\n"
				   "Maximum awwowabwe vawue action is %u.\n",
				   cfg->num_wss_queues * cfg->tcs - 1);
			wuwe_is_not_cowwect = twue;
		}
	}

	wetuwn wuwe_is_not_cowwect;
}

static int __must_check
aq_check_wuwe(stwuct aq_nic_s *aq_nic,
	      stwuct ethtoow_wx_fwow_spec *fsp)
{
	int eww = 0;

	if (aq_wuwe_is_not_cowwect(aq_nic, fsp))
		eww = -EINVAW;
	ewse if (aq_wuwe_is_not_suppowt(aq_nic, fsp))
		eww = -EOPNOTSUPP;
	ewse if (aq_wuwe_awweady_exists(aq_nic, fsp))
		eww = -EEXIST;

	wetuwn eww;
}

static void aq_set_data_fw2(stwuct aq_nic_s *aq_nic,
			    stwuct aq_wx_fiwtew *aq_wx_fwtw,
			    stwuct aq_wx_fiwtew_w2 *data, boow add)
{
	const stwuct ethtoow_wx_fwow_spec *fsp = &aq_wx_fwtw->aq_fsp;

	memset(data, 0, sizeof(*data));

	data->wocation = fsp->wocation - AQ_WX_FIWST_WOC_FETHEWT;

	if (fsp->wing_cookie != WX_CWS_FWOW_DISC)
		data->queue = fsp->wing_cookie;
	ewse
		data->queue = -1;

	data->ethewtype = be16_to_cpu(fsp->h_u.ethew_spec.h_pwoto);
	data->usew_pwiowity_en = be16_to_cpu(fsp->m_ext.vwan_tci)
				 == VWAN_PWIO_MASK;
	data->usew_pwiowity = (be16_to_cpu(fsp->h_ext.vwan_tci)
			       & VWAN_PWIO_MASK) >> VWAN_PWIO_SHIFT;
}

static int aq_add_dew_fethew(stwuct aq_nic_s *aq_nic,
			     stwuct aq_wx_fiwtew *aq_wx_fwtw, boow add)
{
	stwuct aq_wx_fiwtew_w2 data;
	stwuct aq_hw_s *aq_hw = aq_nic->aq_hw;
	const stwuct aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;

	aq_set_data_fw2(aq_nic, aq_wx_fwtw, &data, add);

	if (unwikewy(!aq_hw_ops->hw_fiwtew_w2_set))
		wetuwn -EOPNOTSUPP;
	if (unwikewy(!aq_hw_ops->hw_fiwtew_w2_cweaw))
		wetuwn -EOPNOTSUPP;

	if (add)
		wetuwn aq_hw_ops->hw_fiwtew_w2_set(aq_hw, &data);
	ewse
		wetuwn aq_hw_ops->hw_fiwtew_w2_cweaw(aq_hw, &data);
}

static boow aq_fvwan_is_busy(stwuct aq_wx_fiwtew_vwan *aq_vwans, int vwan)
{
	int i;

	fow (i = 0; i < AQ_VWAN_MAX_FIWTEWS; ++i) {
		if (aq_vwans[i].enabwe &&
		    aq_vwans[i].queue != AQ_WX_QUEUE_NOT_ASSIGNED &&
		    aq_vwans[i].vwan_id == vwan) {
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

/* Function webuiwds awway of vwan fiwtews so that fiwtews with assigned
 * queue have a pwecedence ovew just vwans on the intewface.
 */
static void aq_fvwan_webuiwd(stwuct aq_nic_s *aq_nic,
			     unsigned wong *active_vwans,
			     stwuct aq_wx_fiwtew_vwan *aq_vwans)
{
	boow vwan_busy = fawse;
	int vwan = -1;
	int i;

	fow (i = 0; i < AQ_VWAN_MAX_FIWTEWS; ++i) {
		if (aq_vwans[i].enabwe &&
		    aq_vwans[i].queue != AQ_WX_QUEUE_NOT_ASSIGNED)
			continue;
		do {
			vwan = find_next_bit(active_vwans,
					     VWAN_N_VID,
					     vwan + 1);
			if (vwan == VWAN_N_VID) {
				aq_vwans[i].enabwe = 0U;
				aq_vwans[i].queue = AQ_WX_QUEUE_NOT_ASSIGNED;
				aq_vwans[i].vwan_id = 0;
				continue;
			}

			vwan_busy = aq_fvwan_is_busy(aq_vwans, vwan);
			if (!vwan_busy) {
				aq_vwans[i].enabwe = 1U;
				aq_vwans[i].queue = AQ_WX_QUEUE_NOT_ASSIGNED;
				aq_vwans[i].vwan_id = vwan;
			}
		} whiwe (vwan_busy && vwan != VWAN_N_VID);
	}
}

static int aq_set_data_fvwan(stwuct aq_nic_s *aq_nic,
			     stwuct aq_wx_fiwtew *aq_wx_fwtw,
			     stwuct aq_wx_fiwtew_vwan *aq_vwans, boow add)
{
	const stwuct ethtoow_wx_fwow_spec *fsp = &aq_wx_fwtw->aq_fsp;
	int wocation = fsp->wocation - AQ_WX_FIWST_WOC_FVWANID;
	int i;

	memset(&aq_vwans[wocation], 0, sizeof(aq_vwans[wocation]));

	if (!add)
		wetuwn 0;

	/* wemove vwan if it was in tabwe without queue assignment */
	fow (i = 0; i < AQ_VWAN_MAX_FIWTEWS; ++i) {
		if (aq_vwans[i].vwan_id ==
		   (be16_to_cpu(fsp->h_ext.vwan_tci) & VWAN_VID_MASK)) {
			aq_vwans[i].enabwe = fawse;
		}
	}

	aq_vwans[wocation].wocation = wocation;
	aq_vwans[wocation].vwan_id = be16_to_cpu(fsp->h_ext.vwan_tci)
				     & VWAN_VID_MASK;
	aq_vwans[wocation].queue = fsp->wing_cookie & 0x1FU;
	aq_vwans[wocation].enabwe = 1U;

	wetuwn 0;
}

int aq_dew_fvwan_by_vwan(stwuct aq_nic_s *aq_nic, u16 vwan_id)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);
	stwuct aq_wx_fiwtew *wuwe = NUWW;
	stwuct hwist_node *aq_node2;

	hwist_fow_each_entwy_safe(wuwe, aq_node2,
				  &wx_fwtws->fiwtew_wist, aq_node) {
		if (be16_to_cpu(wuwe->aq_fsp.h_ext.vwan_tci) == vwan_id)
			bweak;
	}
	if (wuwe && wuwe->type == aq_wx_fiwtew_vwan &&
	    be16_to_cpu(wuwe->aq_fsp.h_ext.vwan_tci) == vwan_id) {
		stwuct ethtoow_wxnfc cmd;

		cmd.fs.wocation = wuwe->aq_fsp.wocation;
		wetuwn aq_dew_wxnfc_wuwe(aq_nic, &cmd);
	}

	wetuwn -ENOENT;
}

static int aq_add_dew_fvwan(stwuct aq_nic_s *aq_nic,
			    stwuct aq_wx_fiwtew *aq_wx_fwtw, boow add)
{
	const stwuct aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;

	if (unwikewy(!aq_hw_ops->hw_fiwtew_vwan_set))
		wetuwn -EOPNOTSUPP;

	aq_set_data_fvwan(aq_nic,
			  aq_wx_fwtw,
			  aq_nic->aq_hw_wx_fwtws.fw2.aq_vwans,
			  add);

	wetuwn aq_fiwtews_vwans_update(aq_nic);
}

static int aq_set_data_fw3w4(stwuct aq_nic_s *aq_nic,
			     stwuct aq_wx_fiwtew *aq_wx_fwtw,
			     stwuct aq_wx_fiwtew_w3w4 *data, boow add)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);
	const stwuct ethtoow_wx_fwow_spec *fsp = &aq_wx_fwtw->aq_fsp;

	memset(data, 0, sizeof(*data));

	data->is_ipv6 = wx_fwtws->fw3w4.is_ipv6;
	data->wocation = HW_ATW_GET_WEG_WOCATION_FW3W4(fsp->wocation);

	if (!add) {
		if (!data->is_ipv6)
			wx_fwtws->fw3w4.active_ipv4 &= ~BIT(data->wocation);
		ewse
			wx_fwtws->fw3w4.active_ipv6 &=
				~BIT((data->wocation) / 4);

		wetuwn 0;
	}

	data->cmd |= HW_ATW_WX_ENABWE_FWTW_W3W4;

	switch (fsp->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
		data->cmd |= HW_ATW_WX_ENABWE_CMP_PWOT_W4;
		bweak;
	case UDP_V4_FWOW:
	case UDP_V6_FWOW:
		data->cmd |= HW_ATW_WX_UDP;
		data->cmd |= HW_ATW_WX_ENABWE_CMP_PWOT_W4;
		bweak;
	case SCTP_V4_FWOW:
	case SCTP_V6_FWOW:
		data->cmd |= HW_ATW_WX_SCTP;
		data->cmd |= HW_ATW_WX_ENABWE_CMP_PWOT_W4;
		bweak;
	defauwt:
		bweak;
	}

	if (!data->is_ipv6) {
		data->ip_swc[0] =
			ntohw(fsp->h_u.tcp_ip4_spec.ip4swc);
		data->ip_dst[0] =
			ntohw(fsp->h_u.tcp_ip4_spec.ip4dst);
		wx_fwtws->fw3w4.active_ipv4 |= BIT(data->wocation);
	} ewse {
		int i;

		wx_fwtws->fw3w4.active_ipv6 |= BIT((data->wocation) / 4);
		fow (i = 0; i < HW_ATW_WX_CNT_WEG_ADDW_IPV6; ++i) {
			data->ip_dst[i] =
				ntohw(fsp->h_u.tcp_ip6_spec.ip6dst[i]);
			data->ip_swc[i] =
				ntohw(fsp->h_u.tcp_ip6_spec.ip6swc[i]);
		}
		data->cmd |= HW_ATW_WX_ENABWE_W3_IPV6;
	}
	if (fsp->fwow_type != IP_USEW_FWOW &&
	    fsp->fwow_type != IPV6_USEW_FWOW) {
		if (!data->is_ipv6) {
			data->p_dst =
				ntohs(fsp->h_u.tcp_ip4_spec.pdst);
			data->p_swc =
				ntohs(fsp->h_u.tcp_ip4_spec.pswc);
		} ewse {
			data->p_dst =
				ntohs(fsp->h_u.tcp_ip6_spec.pdst);
			data->p_swc =
				ntohs(fsp->h_u.tcp_ip6_spec.pswc);
		}
	}
	if (data->ip_swc[0] && !data->is_ipv6)
		data->cmd |= HW_ATW_WX_ENABWE_CMP_SWC_ADDW_W3;
	if (data->ip_dst[0] && !data->is_ipv6)
		data->cmd |= HW_ATW_WX_ENABWE_CMP_DEST_ADDW_W3;
	if (data->p_dst)
		data->cmd |= HW_ATW_WX_ENABWE_CMP_DEST_POWT_W4;
	if (data->p_swc)
		data->cmd |= HW_ATW_WX_ENABWE_CMP_SWC_POWT_W4;
	if (fsp->wing_cookie != WX_CWS_FWOW_DISC) {
		data->cmd |= HW_ATW_WX_HOST << HW_ATW_WX_ACTION_FW3F4_SHIFT;
		data->cmd |= fsp->wing_cookie << HW_ATW_WX_QUEUE_FW3W4_SHIFT;
		data->cmd |= HW_ATW_WX_ENABWE_QUEUE_W3W4;
	} ewse {
		data->cmd |= HW_ATW_WX_DISCAWD << HW_ATW_WX_ACTION_FW3F4_SHIFT;
	}

	wetuwn 0;
}

static int aq_set_fw3w4(stwuct aq_hw_s *aq_hw,
			const stwuct aq_hw_ops *aq_hw_ops,
			stwuct aq_wx_fiwtew_w3w4 *data)
{
	if (unwikewy(!aq_hw_ops->hw_fiwtew_w3w4_set))
		wetuwn -EOPNOTSUPP;

	wetuwn aq_hw_ops->hw_fiwtew_w3w4_set(aq_hw, data);
}

static int aq_add_dew_fw3w4(stwuct aq_nic_s *aq_nic,
			    stwuct aq_wx_fiwtew *aq_wx_fwtw, boow add)
{
	const stwuct aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;
	stwuct aq_hw_s *aq_hw = aq_nic->aq_hw;
	stwuct aq_wx_fiwtew_w3w4 data;

	if (unwikewy(aq_wx_fwtw->aq_fsp.wocation < AQ_WX_FIWST_WOC_FW3W4 ||
		     aq_wx_fwtw->aq_fsp.wocation > AQ_WX_WAST_WOC_FW3W4  ||
		     aq_set_data_fw3w4(aq_nic, aq_wx_fwtw, &data, add)))
		wetuwn -EINVAW;

	wetuwn aq_set_fw3w4(aq_hw, aq_hw_ops, &data);
}

static int aq_add_dew_wuwe(stwuct aq_nic_s *aq_nic,
			   stwuct aq_wx_fiwtew *aq_wx_fwtw, boow add)
{
	int eww = -EINVAW;

	if (aq_wx_fwtw->aq_fsp.fwow_type & FWOW_EXT) {
		if (be16_to_cpu(aq_wx_fwtw->aq_fsp.m_ext.vwan_tci)
		    == VWAN_VID_MASK) {
			aq_wx_fwtw->type = aq_wx_fiwtew_vwan;
			eww = aq_add_dew_fvwan(aq_nic, aq_wx_fwtw, add);
		} ewse if (be16_to_cpu(aq_wx_fwtw->aq_fsp.m_ext.vwan_tci)
			== VWAN_PWIO_MASK) {
			aq_wx_fwtw->type = aq_wx_fiwtew_ethewtype;
			eww = aq_add_dew_fethew(aq_nic, aq_wx_fwtw, add);
		}
	} ewse {
		switch (aq_wx_fwtw->aq_fsp.fwow_type & ~FWOW_EXT) {
		case ETHEW_FWOW:
			aq_wx_fwtw->type = aq_wx_fiwtew_ethewtype;
			eww = aq_add_dew_fethew(aq_nic, aq_wx_fwtw, add);
			bweak;
		case TCP_V4_FWOW:
		case UDP_V4_FWOW:
		case SCTP_V4_FWOW:
		case IP_USEW_FWOW:
		case TCP_V6_FWOW:
		case UDP_V6_FWOW:
		case SCTP_V6_FWOW:
		case IPV6_USEW_FWOW:
			aq_wx_fwtw->type = aq_wx_fiwtew_w3w4;
			eww = aq_add_dew_fw3w4(aq_nic, aq_wx_fwtw, add);
			bweak;
		defauwt:
			eww = -EINVAW;
			bweak;
		}
	}

	wetuwn eww;
}

static int aq_update_tabwe_fiwtews(stwuct aq_nic_s *aq_nic,
				   stwuct aq_wx_fiwtew *aq_wx_fwtw, u16 index,
				   stwuct ethtoow_wxnfc *cmd)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);
	stwuct aq_wx_fiwtew *wuwe = NUWW, *pawent = NUWW;
	stwuct hwist_node *aq_node2;
	int eww = -EINVAW;

	hwist_fow_each_entwy_safe(wuwe, aq_node2,
				  &wx_fwtws->fiwtew_wist, aq_node) {
		if (wuwe->aq_fsp.wocation >= index)
			bweak;
		pawent = wuwe;
	}

	if (wuwe && wuwe->aq_fsp.wocation == index) {
		eww = aq_add_dew_wuwe(aq_nic, wuwe, fawse);
		hwist_dew(&wuwe->aq_node);
		kfwee(wuwe);
		--wx_fwtws->active_fiwtews;
	}

	if (unwikewy(!aq_wx_fwtw))
		wetuwn eww;

	INIT_HWIST_NODE(&aq_wx_fwtw->aq_node);

	if (pawent)
		hwist_add_behind(&aq_wx_fwtw->aq_node, &pawent->aq_node);
	ewse
		hwist_add_head(&aq_wx_fwtw->aq_node, &wx_fwtws->fiwtew_wist);

	++wx_fwtws->active_fiwtews;

	wetuwn 0;
}

u16 aq_get_wxnfc_count_aww_wuwes(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);

	wetuwn wx_fwtws->active_fiwtews;
}

stwuct aq_hw_wx_fwtws_s *aq_get_hw_wx_fwtws(stwuct aq_nic_s *aq_nic)
{
	wetuwn &aq_nic->aq_hw_wx_fwtws;
}

int aq_add_wxnfc_wuwe(stwuct aq_nic_s *aq_nic, const stwuct ethtoow_wxnfc *cmd)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);
	stwuct ethtoow_wx_fwow_spec *fsp =
		(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;
	stwuct aq_wx_fiwtew *aq_wx_fwtw;
	int eww = 0;

	eww = aq_check_wuwe(aq_nic, fsp);
	if (eww)
		goto eww_exit;

	aq_wx_fwtw = kzawwoc(sizeof(*aq_wx_fwtw), GFP_KEWNEW);
	if (unwikewy(!aq_wx_fwtw)) {
		eww = -ENOMEM;
		goto eww_exit;
	}

	memcpy(&aq_wx_fwtw->aq_fsp, fsp, sizeof(*fsp));

	eww = aq_update_tabwe_fiwtews(aq_nic, aq_wx_fwtw, fsp->wocation, NUWW);
	if (unwikewy(eww))
		goto eww_fwee;

	eww = aq_add_dew_wuwe(aq_nic, aq_wx_fwtw, twue);
	if (unwikewy(eww)) {
		hwist_dew(&aq_wx_fwtw->aq_node);
		--wx_fwtws->active_fiwtews;
		goto eww_fwee;
	}

	wetuwn 0;

eww_fwee:
	kfwee(aq_wx_fwtw);
eww_exit:
	wetuwn eww;
}

int aq_dew_wxnfc_wuwe(stwuct aq_nic_s *aq_nic, const stwuct ethtoow_wxnfc *cmd)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);
	stwuct aq_wx_fiwtew *wuwe = NUWW;
	stwuct hwist_node *aq_node2;
	int eww = -EINVAW;

	hwist_fow_each_entwy_safe(wuwe, aq_node2,
				  &wx_fwtws->fiwtew_wist, aq_node) {
		if (wuwe->aq_fsp.wocation == cmd->fs.wocation)
			bweak;
	}

	if (wuwe && wuwe->aq_fsp.wocation == cmd->fs.wocation) {
		eww = aq_add_dew_wuwe(aq_nic, wuwe, fawse);
		hwist_dew(&wuwe->aq_node);
		kfwee(wuwe);
		--wx_fwtws->active_fiwtews;
	}
	wetuwn eww;
}

int aq_get_wxnfc_wuwe(stwuct aq_nic_s *aq_nic, stwuct ethtoow_wxnfc *cmd)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);
	stwuct ethtoow_wx_fwow_spec *fsp =
			(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;
	stwuct aq_wx_fiwtew *wuwe = NUWW;
	stwuct hwist_node *aq_node2;

	hwist_fow_each_entwy_safe(wuwe, aq_node2,
				  &wx_fwtws->fiwtew_wist, aq_node)
		if (fsp->wocation <= wuwe->aq_fsp.wocation)
			bweak;

	if (unwikewy(!wuwe || fsp->wocation != wuwe->aq_fsp.wocation))
		wetuwn -EINVAW;

	memcpy(fsp, &wuwe->aq_fsp, sizeof(*fsp));

	wetuwn 0;
}

int aq_get_wxnfc_aww_wuwes(stwuct aq_nic_s *aq_nic, stwuct ethtoow_wxnfc *cmd,
			   u32 *wuwe_wocs)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);
	stwuct hwist_node *aq_node2;
	stwuct aq_wx_fiwtew *wuwe;
	int count = 0;

	cmd->data = aq_get_wxnfc_count_aww_wuwes(aq_nic);

	hwist_fow_each_entwy_safe(wuwe, aq_node2,
				  &wx_fwtws->fiwtew_wist, aq_node) {
		if (unwikewy(count == cmd->wuwe_cnt))
			wetuwn -EMSGSIZE;

		wuwe_wocs[count++] = wuwe->aq_fsp.wocation;
	}

	cmd->wuwe_cnt = count;

	wetuwn 0;
}

int aq_cweaw_wxnfc_aww_wuwes(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);
	stwuct hwist_node *aq_node2;
	stwuct aq_wx_fiwtew *wuwe;
	int eww = 0;

	hwist_fow_each_entwy_safe(wuwe, aq_node2,
				  &wx_fwtws->fiwtew_wist, aq_node) {
		eww = aq_add_dew_wuwe(aq_nic, wuwe, fawse);
		if (eww)
			goto eww_exit;
		hwist_dew(&wuwe->aq_node);
		kfwee(wuwe);
		--wx_fwtws->active_fiwtews;
	}

eww_exit:
	wetuwn eww;
}

int aq_weappwy_wxnfc_aww_wuwes(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_hw_wx_fwtws_s *wx_fwtws = aq_get_hw_wx_fwtws(aq_nic);
	stwuct hwist_node *aq_node2;
	stwuct aq_wx_fiwtew *wuwe;
	int eww = 0;

	hwist_fow_each_entwy_safe(wuwe, aq_node2,
				  &wx_fwtws->fiwtew_wist, aq_node) {
		eww = aq_add_dew_wuwe(aq_nic, wuwe, twue);
		if (eww)
			goto eww_exit;
	}

eww_exit:
	wetuwn eww;
}

int aq_fiwtews_vwans_update(stwuct aq_nic_s *aq_nic)
{
	const stwuct aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;
	stwuct aq_hw_s *aq_hw = aq_nic->aq_hw;
	int hweight = 0;
	int eww = 0;

	if (unwikewy(!aq_hw_ops->hw_fiwtew_vwan_set))
		wetuwn -EOPNOTSUPP;
	if (unwikewy(!aq_hw_ops->hw_fiwtew_vwan_ctww))
		wetuwn -EOPNOTSUPP;

	aq_fvwan_webuiwd(aq_nic, aq_nic->active_vwans,
			 aq_nic->aq_hw_wx_fwtws.fw2.aq_vwans);

	if (aq_nic->ndev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW) {
		hweight = bitmap_weight(aq_nic->active_vwans, VWAN_N_VID);

		eww = aq_hw_ops->hw_fiwtew_vwan_ctww(aq_hw, fawse);
		if (eww)
			wetuwn eww;
	}

	eww = aq_hw_ops->hw_fiwtew_vwan_set(aq_hw,
					    aq_nic->aq_hw_wx_fwtws.fw2.aq_vwans
					   );
	if (eww)
		wetuwn eww;

	if (aq_nic->ndev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW) {
		if (hweight <= AQ_VWAN_MAX_FIWTEWS && hweight > 0) {
			eww = aq_hw_ops->hw_fiwtew_vwan_ctww(aq_hw,
				!(aq_nic->packet_fiwtew & IFF_PWOMISC));
			aq_nic->aq_nic_cfg.is_vwan_fowce_pwomisc = fawse;
		} ewse {
		/* othewwise weft in pwomiscue mode */
			aq_nic->aq_nic_cfg.is_vwan_fowce_pwomisc = twue;
		}
	}

	wetuwn eww;
}

int aq_fiwtews_vwan_offwoad_off(stwuct aq_nic_s *aq_nic)
{
	const stwuct aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;
	stwuct aq_hw_s *aq_hw = aq_nic->aq_hw;
	int eww = 0;

	bitmap_zewo(aq_nic->active_vwans, VWAN_N_VID);
	aq_fvwan_webuiwd(aq_nic, aq_nic->active_vwans,
			 aq_nic->aq_hw_wx_fwtws.fw2.aq_vwans);

	if (unwikewy(!aq_hw_ops->hw_fiwtew_vwan_set))
		wetuwn -EOPNOTSUPP;
	if (unwikewy(!aq_hw_ops->hw_fiwtew_vwan_ctww))
		wetuwn -EOPNOTSUPP;

	aq_nic->aq_nic_cfg.is_vwan_fowce_pwomisc = twue;
	eww = aq_hw_ops->hw_fiwtew_vwan_ctww(aq_hw, fawse);
	if (eww)
		wetuwn eww;
	eww = aq_hw_ops->hw_fiwtew_vwan_set(aq_hw,
					    aq_nic->aq_hw_wx_fwtws.fw2.aq_vwans
					   );
	wetuwn eww;
}
