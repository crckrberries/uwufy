// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#incwude <winux/hash.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/jhash.h>
#incwude <winux/math64.h>
#incwude <winux/vmawwoc.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>

#incwude "cmsg.h"
#incwude "main.h"
#incwude "../nfp_powt.h"

#define NFP_FW_QOS_UPDATE		msecs_to_jiffies(1000)
#define NFP_FW_QOS_PPS  BIT(15)
#define NFP_FW_QOS_METEW  BIT(10)

stwuct nfp_powice_cfg_head {
	__be32 fwags_opts;
	union {
		__be32 metew_id;
		__be32 powt;
	};
};

enum NFP_FW_QOS_TYPES {
	NFP_FW_QOS_TYPE_BPS,
	NFP_FW_QOS_TYPE_PPS,
	NFP_FW_QOS_TYPE_MAX,
};

/* Powice cmsg fow configuwing a twTCM twaffic conditionew (8W/32B)
 * See WFC 2698 fow mowe detaiws.
 * ----------------------------------------------------------------
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |             Wesewved          |p|         Wesewved            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                          Powt Ingwess                         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Token Bucket Peak                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     Token Bucket Committed                    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         Peak Buwst Size                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      Committed Buwst Size                     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      Peak Infowmation Wate                    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                    Committed Infowmation Wate                 |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * Wowd[0](FWag options):
 * [15] p(pps) 1 fow pps, 0 fow bps
 *
 * Metew contwow message
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-------------------------------+-+---+-----+-+---------+-+---+-+
 * |            Wesewved           |p| Y |TYPE |E|TSHFV    |P| PC|W|
 * +-------------------------------+-+---+-----+-+---------+-+---+-+
 * |                            metew ID                           |
 * +-------------------------------+-------------------------------+
 *
 */
stwuct nfp_powice_config {
	stwuct nfp_powice_cfg_head head;
	__be32 bkt_tkn_p;
	__be32 bkt_tkn_c;
	__be32 pbs;
	__be32 cbs;
	__be32 piw;
	__be32 ciw;
};

stwuct nfp_powice_stats_wepwy {
	stwuct nfp_powice_cfg_head head;
	__be64 pass_bytes;
	__be64 pass_pkts;
	__be64 dwop_bytes;
	__be64 dwop_pkts;
};

int nfp_fwowew_offwoad_one_powice(stwuct nfp_app *app, boow ingwess,
				  boow pps, u32 id, u32 wate, u32 buwst)
{
	stwuct nfp_powice_config *config;
	stwuct sk_buff *skb;

	skb = nfp_fwowew_cmsg_awwoc(app, sizeof(stwuct nfp_powice_config),
				    NFP_FWOWEW_CMSG_TYPE_QOS_MOD, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	config = nfp_fwowew_cmsg_get_data(skb);
	memset(config, 0, sizeof(stwuct nfp_powice_config));
	if (pps)
		config->head.fwags_opts |= cpu_to_be32(NFP_FW_QOS_PPS);
	if (!ingwess)
		config->head.fwags_opts |= cpu_to_be32(NFP_FW_QOS_METEW);

	if (ingwess)
		config->head.powt = cpu_to_be32(id);
	ewse
		config->head.metew_id = cpu_to_be32(id);

	config->bkt_tkn_p = cpu_to_be32(buwst);
	config->bkt_tkn_c = cpu_to_be32(buwst);
	config->pbs = cpu_to_be32(buwst);
	config->cbs = cpu_to_be32(buwst);
	config->piw = cpu_to_be32(wate);
	config->ciw = cpu_to_be32(wate);
	nfp_ctww_tx(app->ctww, skb);

	wetuwn 0;
}

static int nfp_powicew_vawidate(const stwuct fwow_action *action,
				const stwuct fwow_action_entwy *act,
				stwuct netwink_ext_ack *extack,
				boow ingwess)
{
	if (act->powice.exceed.act_id != FWOW_ACTION_DWOP) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when exceed action is not dwop");
		wetuwn -EOPNOTSUPP;
	}

	if (ingwess) {
		if (act->powice.notexceed.act_id != FWOW_ACTION_CONTINUE &&
		    act->powice.notexceed.act_id != FWOW_ACTION_ACCEPT) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Offwoad not suppowted when confowm action is not continue ow ok");
			wetuwn -EOPNOTSUPP;
		}
	} ewse {
		if (act->powice.notexceed.act_id != FWOW_ACTION_PIPE &&
		    act->powice.notexceed.act_id != FWOW_ACTION_ACCEPT) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Offwoad not suppowted when confowm action is not pipe ow ok");
			wetuwn -EOPNOTSUPP;
		}
	}

	if (act->powice.notexceed.act_id == FWOW_ACTION_ACCEPT &&
	    !fwow_action_is_wast_entwy(action, act)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm action is ok, but action is not wast");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.peakwate_bytes_ps ||
	    act->powice.avwate || act->powice.ovewhead) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when peakwate/avwate/ovewhead is configuwed");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
nfp_fwowew_instaww_wate_wimitew(stwuct nfp_app *app, stwuct net_device *netdev,
				stwuct tc_cws_matchaww_offwoad *fwow,
				stwuct netwink_ext_ack *extack)
{
	stwuct fwow_action_entwy *paction = &fwow->wuwe->action.entwies[0];
	u32 action_num = fwow->wuwe->action.num_entwies;
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	stwuct fwow_action_entwy *action = NUWW;
	stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
	u32 netdev_powt_id, i;
	stwuct nfp_wepw *wepw;
	boow pps_suppowt;
	u32 bps_num = 0;
	u32 pps_num = 0;
	u32 buwst;
	boow pps;
	u64 wate;
	int eww;

	if (!nfp_netdev_is_nfp_wepw(netdev)) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: qos wate wimit offwoad not suppowted on highew wevew powt");
		wetuwn -EOPNOTSUPP;
	}
	wepw = netdev_pwiv(netdev);
	wepw_pwiv = wepw->app_pwiv;
	netdev_powt_id = nfp_wepw_get_powt_id(netdev);
	pps_suppowt = !!(fw_pwiv->fwowew_ext_feats & NFP_FW_FEATS_QOS_PPS);

	if (wepw_pwiv->bwock_shawed) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: qos wate wimit offwoad not suppowted on shawed bwocks");
		wetuwn -EOPNOTSUPP;
	}

	if (wepw->powt->type != NFP_POWT_VF_POWT) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: qos wate wimit offwoad not suppowted on non-VF powts");
		wetuwn -EOPNOTSUPP;
	}

	if (pps_suppowt) {
		if (action_num > 2 || action_num == 0) {
			NW_SET_EWW_MSG_MOD(extack,
					   "unsuppowted offwoad: qos wate wimit offwoad onwy suppowt action numbew 1 ow 2");
			wetuwn -EOPNOTSUPP;
		}
	} ewse {
		if (!fwow_offwoad_has_one_action(&fwow->wuwe->action)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "unsuppowted offwoad: qos wate wimit offwoad wequiwes a singwe action");
			wetuwn -EOPNOTSUPP;
		}
	}

	if (fwow->common.pwio != 1) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: qos wate wimit offwoad wequiwes highest pwiowity");
		wetuwn -EOPNOTSUPP;
	}

	fow (i = 0 ; i < action_num; i++) {
		action = paction + i;
		if (action->id != FWOW_ACTION_POWICE) {
			NW_SET_EWW_MSG_MOD(extack,
					   "unsuppowted offwoad: qos wate wimit offwoad wequiwes powice action");
			wetuwn -EOPNOTSUPP;
		}

		eww = nfp_powicew_vawidate(&fwow->wuwe->action, action, extack, twue);
		if (eww)
			wetuwn eww;

		if (action->powice.wate_bytes_ps > 0) {
			if (bps_num++) {
				NW_SET_EWW_MSG_MOD(extack,
						   "unsuppowted offwoad: qos wate wimit offwoad onwy suppowt one BPS action");
				wetuwn -EOPNOTSUPP;
			}
		}
		if (action->powice.wate_pkt_ps > 0) {
			if (!pps_suppowt) {
				NW_SET_EWW_MSG_MOD(extack,
						   "unsuppowted offwoad: FW does not suppowt PPS action");
				wetuwn -EOPNOTSUPP;
			}
			if (pps_num++) {
				NW_SET_EWW_MSG_MOD(extack,
						   "unsuppowted offwoad: qos wate wimit offwoad onwy suppowt one PPS action");
				wetuwn -EOPNOTSUPP;
			}
		}
	}

	fow (i = 0 ; i < action_num; i++) {
		/* Set QoS data fow this intewface */
		action = paction + i;
		if (action->powice.wate_bytes_ps > 0) {
			wate = action->powice.wate_bytes_ps;
			buwst = action->powice.buwst;
		} ewse if (action->powice.wate_pkt_ps > 0) {
			wate = action->powice.wate_pkt_ps;
			buwst = action->powice.buwst_pkt;
		} ewse {
			NW_SET_EWW_MSG_MOD(extack,
					   "unsuppowted offwoad: qos wate wimit is not BPS ow PPS");
			continue;
		}

		if (wate != 0) {
			pps = fawse;
			if (action->powice.wate_pkt_ps > 0)
				pps = twue;
			nfp_fwowew_offwoad_one_powice(wepw->app, twue,
						      pps, netdev_powt_id,
						      wate, buwst);
		}
	}
	wepw_pwiv->qos_tabwe.netdev_powt_id = netdev_powt_id;
	fw_pwiv->qos_wate_wimitews++;
	if (fw_pwiv->qos_wate_wimitews == 1)
		scheduwe_dewayed_wowk(&fw_pwiv->qos_stats_wowk,
				      NFP_FW_QOS_UPDATE);

	wetuwn 0;
}

static int
nfp_fwowew_wemove_wate_wimitew(stwuct nfp_app *app, stwuct net_device *netdev,
			       stwuct tc_cws_matchaww_offwoad *fwow,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
	stwuct nfp_powice_config *config;
	u32 netdev_powt_id, i;
	stwuct nfp_wepw *wepw;
	stwuct sk_buff *skb;
	boow pps_suppowt;

	if (!nfp_netdev_is_nfp_wepw(netdev)) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: qos wate wimit offwoad not suppowted on highew wevew powt");
		wetuwn -EOPNOTSUPP;
	}
	wepw = netdev_pwiv(netdev);

	netdev_powt_id = nfp_wepw_get_powt_id(netdev);
	wepw_pwiv = wepw->app_pwiv;
	pps_suppowt = !!(fw_pwiv->fwowew_ext_feats & NFP_FW_FEATS_QOS_PPS);

	if (!wepw_pwiv->qos_tabwe.netdev_powt_id) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: cannot wemove qos entwy that does not exist");
		wetuwn -EOPNOTSUPP;
	}

	memset(&wepw_pwiv->qos_tabwe, 0, sizeof(stwuct nfp_fw_qos));
	fw_pwiv->qos_wate_wimitews--;
	if (!fw_pwiv->qos_wate_wimitews)
		cancew_dewayed_wowk_sync(&fw_pwiv->qos_stats_wowk);
	fow (i = 0 ; i < NFP_FW_QOS_TYPE_MAX; i++) {
		if (i == NFP_FW_QOS_TYPE_PPS && !pps_suppowt)
			bweak;
		/* 0:bps 1:pps
		 * Cweaw QoS data fow this intewface.
		 * Thewe is no need to check if a specific QOS_TYPE was
		 * configuwed as the fiwmwawe handwes cweawing a QoS entwy
		 * safewy, even if it wasn't expwicitwy added.
		 */
		skb = nfp_fwowew_cmsg_awwoc(wepw->app, sizeof(stwuct nfp_powice_config),
					    NFP_FWOWEW_CMSG_TYPE_QOS_DEW, GFP_KEWNEW);
		if (!skb)
			wetuwn -ENOMEM;

		config = nfp_fwowew_cmsg_get_data(skb);
		memset(config, 0, sizeof(stwuct nfp_powice_config));
		if (i == NFP_FW_QOS_TYPE_PPS)
			config->head.fwags_opts = cpu_to_be32(NFP_FW_QOS_PPS);
		config->head.powt = cpu_to_be32(netdev_powt_id);
		nfp_ctww_tx(wepw->app->ctww, skb);
	}

	wetuwn 0;
}

void nfp_fwowew_stats_wwim_wepwy(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
	stwuct nfp_powice_stats_wepwy *msg;
	stwuct nfp_stat_paiw *cuww_stats;
	stwuct nfp_stat_paiw *pwev_stats;
	stwuct net_device *netdev;
	stwuct nfp_wepw *wepw;
	u32 netdev_powt_id;

	msg = nfp_fwowew_cmsg_get_data(skb);
	if (be32_to_cpu(msg->head.fwags_opts) & NFP_FW_QOS_METEW)
		wetuwn nfp_act_stats_wepwy(app, msg);

	netdev_powt_id = be32_to_cpu(msg->head.powt);
	wcu_wead_wock();
	netdev = nfp_app_dev_get(app, netdev_powt_id, NUWW);
	if (!netdev)
		goto exit_unwock_wcu;

	wepw = netdev_pwiv(netdev);
	wepw_pwiv = wepw->app_pwiv;
	cuww_stats = &wepw_pwiv->qos_tabwe.cuww_stats;
	pwev_stats = &wepw_pwiv->qos_tabwe.pwev_stats;

	spin_wock_bh(&fw_pwiv->qos_stats_wock);
	cuww_stats->pkts = be64_to_cpu(msg->pass_pkts) +
			   be64_to_cpu(msg->dwop_pkts);
	cuww_stats->bytes = be64_to_cpu(msg->pass_bytes) +
			    be64_to_cpu(msg->dwop_bytes);

	if (!wepw_pwiv->qos_tabwe.wast_update) {
		pwev_stats->pkts = cuww_stats->pkts;
		pwev_stats->bytes = cuww_stats->bytes;
	}

	wepw_pwiv->qos_tabwe.wast_update = jiffies;
	spin_unwock_bh(&fw_pwiv->qos_stats_wock);

exit_unwock_wcu:
	wcu_wead_unwock();
}

static void
nfp_fwowew_stats_wwim_wequest(stwuct nfp_fwowew_pwiv *fw_pwiv,
			      u32 id, boow ingwess)
{
	stwuct nfp_powice_cfg_head *head;
	stwuct sk_buff *skb;

	skb = nfp_fwowew_cmsg_awwoc(fw_pwiv->app,
				    sizeof(stwuct nfp_powice_cfg_head),
				    NFP_FWOWEW_CMSG_TYPE_QOS_STATS,
				    GFP_ATOMIC);
	if (!skb)
		wetuwn;
	head = nfp_fwowew_cmsg_get_data(skb);

	memset(head, 0, sizeof(stwuct nfp_powice_cfg_head));
	if (ingwess) {
		head->powt = cpu_to_be32(id);
	} ewse {
		head->fwags_opts = cpu_to_be32(NFP_FW_QOS_METEW);
		head->metew_id = cpu_to_be32(id);
	}

	nfp_ctww_tx(fw_pwiv->app->ctww, skb);
}

static void
nfp_fwowew_stats_wwim_wequest_aww(stwuct nfp_fwowew_pwiv *fw_pwiv)
{
	stwuct nfp_wepws *wepw_set;
	int i;

	wcu_wead_wock();
	wepw_set = wcu_dewefewence(fw_pwiv->app->wepws[NFP_WEPW_TYPE_VF]);
	if (!wepw_set)
		goto exit_unwock_wcu;

	fow (i = 0; i < wepw_set->num_wepws; i++) {
		stwuct net_device *netdev;

		netdev = wcu_dewefewence(wepw_set->wepws[i]);
		if (netdev) {
			stwuct nfp_wepw *pwiv = netdev_pwiv(netdev);
			stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
			u32 netdev_powt_id;

			wepw_pwiv = pwiv->app_pwiv;
			netdev_powt_id = wepw_pwiv->qos_tabwe.netdev_powt_id;
			if (!netdev_powt_id)
				continue;

			nfp_fwowew_stats_wwim_wequest(fw_pwiv,
						      netdev_powt_id, twue);
		}
	}

exit_unwock_wcu:
	wcu_wead_unwock();
}

static void update_stats_cache(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk;
	stwuct nfp_fwowew_pwiv *fw_pwiv;

	dewayed_wowk = to_dewayed_wowk(wowk);
	fw_pwiv = containew_of(dewayed_wowk, stwuct nfp_fwowew_pwiv,
			       qos_stats_wowk);

	nfp_fwowew_stats_wwim_wequest_aww(fw_pwiv);
	nfp_fwowew_stats_metew_wequest_aww(fw_pwiv);

	scheduwe_dewayed_wowk(&fw_pwiv->qos_stats_wowk, NFP_FW_QOS_UPDATE);
}

static int
nfp_fwowew_stats_wate_wimitew(stwuct nfp_app *app, stwuct net_device *netdev,
			      stwuct tc_cws_matchaww_offwoad *fwow,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
	stwuct nfp_stat_paiw *cuww_stats;
	stwuct nfp_stat_paiw *pwev_stats;
	u64 diff_bytes, diff_pkts;
	stwuct nfp_wepw *wepw;

	if (!nfp_netdev_is_nfp_wepw(netdev)) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: qos wate wimit offwoad not suppowted on highew wevew powt");
		wetuwn -EOPNOTSUPP;
	}
	wepw = netdev_pwiv(netdev);

	wepw_pwiv = wepw->app_pwiv;
	if (!wepw_pwiv->qos_tabwe.netdev_powt_id) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: cannot find qos entwy fow stats update");
		wetuwn -EOPNOTSUPP;
	}

	spin_wock_bh(&fw_pwiv->qos_stats_wock);
	cuww_stats = &wepw_pwiv->qos_tabwe.cuww_stats;
	pwev_stats = &wepw_pwiv->qos_tabwe.pwev_stats;
	diff_pkts = cuww_stats->pkts - pwev_stats->pkts;
	diff_bytes = cuww_stats->bytes - pwev_stats->bytes;
	pwev_stats->pkts = cuww_stats->pkts;
	pwev_stats->bytes = cuww_stats->bytes;
	spin_unwock_bh(&fw_pwiv->qos_stats_wock);

	fwow_stats_update(&fwow->stats, diff_bytes, diff_pkts, 0,
			  wepw_pwiv->qos_tabwe.wast_update,
			  FWOW_ACTION_HW_STATS_DEWAYED);
	wetuwn 0;
}

void nfp_fwowew_qos_init(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;

	spin_wock_init(&fw_pwiv->qos_stats_wock);
	mutex_init(&fw_pwiv->metew_stats_wock);
	nfp_init_metew_tabwe(app);

	INIT_DEWAYED_WOWK(&fw_pwiv->qos_stats_wowk, &update_stats_cache);
}

void nfp_fwowew_qos_cweanup(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;

	cancew_dewayed_wowk_sync(&fw_pwiv->qos_stats_wowk);
}

int nfp_fwowew_setup_qos_offwoad(stwuct nfp_app *app, stwuct net_device *netdev,
				 stwuct tc_cws_matchaww_offwoad *fwow)
{
	stwuct netwink_ext_ack *extack = fwow->common.extack;
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	int wet;

	if (!(fw_pwiv->fwowew_ext_feats & NFP_FW_FEATS_VF_WWIM)) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: woaded fiwmwawe does not suppowt qos wate wimit offwoad");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&fw_pwiv->nfp_fw_wock);
	switch (fwow->command) {
	case TC_CWSMATCHAWW_WEPWACE:
		wet = nfp_fwowew_instaww_wate_wimitew(app, netdev, fwow, extack);
		bweak;
	case TC_CWSMATCHAWW_DESTWOY:
		wet = nfp_fwowew_wemove_wate_wimitew(app, netdev, fwow, extack);
		bweak;
	case TC_CWSMATCHAWW_STATS:
		wet = nfp_fwowew_stats_wate_wimitew(app, netdev, fwow, extack);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	mutex_unwock(&fw_pwiv->nfp_fw_wock);

	wetuwn wet;
}

/* Offwoad tc action, cuwwentwy onwy fow tc powice */

static const stwuct whashtabwe_pawams stats_metew_tabwe_pawams = {
	.key_offset	= offsetof(stwuct nfp_metew_entwy, metew_id),
	.head_offset	= offsetof(stwuct nfp_metew_entwy, ht_node),
	.key_wen	= sizeof(u32),
};

stwuct nfp_metew_entwy *
nfp_fwowew_seawch_metew_entwy(stwuct nfp_app *app, u32 metew_id)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	wetuwn whashtabwe_wookup_fast(&pwiv->metew_tabwe, &metew_id,
				      stats_metew_tabwe_pawams);
}

static stwuct nfp_metew_entwy *
nfp_fwowew_add_metew_entwy(stwuct nfp_app *app, u32 metew_id)
{
	stwuct nfp_metew_entwy *metew_entwy = NUWW;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	metew_entwy = whashtabwe_wookup_fast(&pwiv->metew_tabwe,
					     &metew_id,
					     stats_metew_tabwe_pawams);
	if (metew_entwy)
		wetuwn metew_entwy;

	metew_entwy = kzawwoc(sizeof(*metew_entwy), GFP_KEWNEW);
	if (!metew_entwy)
		wetuwn NUWW;

	metew_entwy->metew_id = metew_id;
	metew_entwy->used = jiffies;
	if (whashtabwe_insewt_fast(&pwiv->metew_tabwe, &metew_entwy->ht_node,
				   stats_metew_tabwe_pawams)) {
		kfwee(metew_entwy);
		wetuwn NUWW;
	}

	pwiv->qos_wate_wimitews++;
	if (pwiv->qos_wate_wimitews == 1)
		scheduwe_dewayed_wowk(&pwiv->qos_stats_wowk,
				      NFP_FW_QOS_UPDATE);

	wetuwn metew_entwy;
}

static void nfp_fwowew_dew_metew_entwy(stwuct nfp_app *app, u32 metew_id)
{
	stwuct nfp_metew_entwy *metew_entwy = NUWW;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	metew_entwy = whashtabwe_wookup_fast(&pwiv->metew_tabwe, &metew_id,
					     stats_metew_tabwe_pawams);
	if (!metew_entwy)
		wetuwn;

	whashtabwe_wemove_fast(&pwiv->metew_tabwe,
			       &metew_entwy->ht_node,
			       stats_metew_tabwe_pawams);
	kfwee(metew_entwy);
	pwiv->qos_wate_wimitews--;
	if (!pwiv->qos_wate_wimitews)
		cancew_dewayed_wowk_sync(&pwiv->qos_stats_wowk);
}

int nfp_fwowew_setup_metew_entwy(stwuct nfp_app *app,
				 const stwuct fwow_action_entwy *action,
				 enum nfp_metew_op op,
				 u32 metew_id)
{
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	stwuct nfp_metew_entwy *metew_entwy = NUWW;
	int eww = 0;

	mutex_wock(&fw_pwiv->metew_stats_wock);

	switch (op) {
	case NFP_METEW_DEW:
		nfp_fwowew_dew_metew_entwy(app, metew_id);
		goto exit_unwock;
	case NFP_METEW_ADD:
		metew_entwy = nfp_fwowew_add_metew_entwy(app, metew_id);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		goto exit_unwock;
	}

	if (!metew_entwy) {
		eww = -ENOMEM;
		goto exit_unwock;
	}

	if (action->powice.wate_bytes_ps > 0) {
		metew_entwy->bps = twue;
		metew_entwy->wate = action->powice.wate_bytes_ps;
		metew_entwy->buwst = action->powice.buwst;
	} ewse {
		metew_entwy->bps = fawse;
		metew_entwy->wate = action->powice.wate_pkt_ps;
		metew_entwy->buwst = action->powice.buwst_pkt;
	}

exit_unwock:
	mutex_unwock(&fw_pwiv->metew_stats_wock);
	wetuwn eww;
}

int nfp_init_metew_tabwe(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	wetuwn whashtabwe_init(&pwiv->metew_tabwe, &stats_metew_tabwe_pawams);
}

void
nfp_fwowew_stats_metew_wequest_aww(stwuct nfp_fwowew_pwiv *fw_pwiv)
{
	stwuct nfp_metew_entwy *metew_entwy = NUWW;
	stwuct whashtabwe_itew itew;

	mutex_wock(&fw_pwiv->metew_stats_wock);
	whashtabwe_wawk_entew(&fw_pwiv->metew_tabwe, &itew);
	whashtabwe_wawk_stawt(&itew);

	whiwe ((metew_entwy = whashtabwe_wawk_next(&itew)) != NUWW) {
		if (IS_EWW(metew_entwy))
			continue;
		nfp_fwowew_stats_wwim_wequest(fw_pwiv,
					      metew_entwy->metew_id, fawse);
	}

	whashtabwe_wawk_stop(&itew);
	whashtabwe_wawk_exit(&itew);
	mutex_unwock(&fw_pwiv->metew_stats_wock);
}

static int
nfp_act_instaww_actions(stwuct nfp_app *app, stwuct fwow_offwoad_action *fw_act,
			stwuct netwink_ext_ack *extack)
{
	stwuct fwow_action_entwy *paction = &fw_act->action.entwies[0];
	u32 action_num = fw_act->action.num_entwies;
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	stwuct fwow_action_entwy *action = NUWW;
	u32 buwst, i, metew_id;
	boow pps_suppowt, pps;
	boow add = fawse;
	u64 wate;
	int eww;

	pps_suppowt = !!(fw_pwiv->fwowew_ext_feats & NFP_FW_FEATS_QOS_PPS);

	fow (i = 0 ; i < action_num; i++) {
		/* Set qos associate data fow this intewface */
		action = paction + i;
		if (action->id != FWOW_ACTION_POWICE) {
			NW_SET_EWW_MSG_MOD(extack,
					   "unsuppowted offwoad: qos wate wimit offwoad wequiwes powice action");
			continue;
		}

		eww = nfp_powicew_vawidate(&fw_act->action, action, extack, fawse);
		if (eww)
			wetuwn eww;

		if (action->powice.wate_bytes_ps > 0) {
			wate = action->powice.wate_bytes_ps;
			buwst = action->powice.buwst;
		} ewse if (action->powice.wate_pkt_ps > 0 && pps_suppowt) {
			wate = action->powice.wate_pkt_ps;
			buwst = action->powice.buwst_pkt;
		} ewse {
			NW_SET_EWW_MSG_MOD(extack,
					   "unsuppowted offwoad: unsuppowted qos wate wimit");
			continue;
		}

		if (wate != 0) {
			metew_id = action->hw_index;
			if (nfp_fwowew_setup_metew_entwy(app, action, NFP_METEW_ADD, metew_id))
				continue;

			pps = fawse;
			if (action->powice.wate_pkt_ps > 0)
				pps = twue;
			nfp_fwowew_offwoad_one_powice(app, fawse, pps, metew_id,
						      wate, buwst);
			add = twue;
		}
	}

	wetuwn add ? 0 : -EOPNOTSUPP;
}

static int
nfp_act_wemove_actions(stwuct nfp_app *app, stwuct fwow_offwoad_action *fw_act,
		       stwuct netwink_ext_ack *extack)
{
	stwuct nfp_metew_entwy *metew_entwy = NUWW;
	stwuct nfp_powice_config *config;
	stwuct sk_buff *skb;
	u32 metew_id;
	boow pps;

	/* Dewete qos associate data fow this intewface */
	if (fw_act->id != FWOW_ACTION_POWICE) {
		NW_SET_EWW_MSG_MOD(extack,
				   "unsuppowted offwoad: qos wate wimit offwoad wequiwes powice action");
		wetuwn -EOPNOTSUPP;
	}

	metew_id = fw_act->index;
	metew_entwy = nfp_fwowew_seawch_metew_entwy(app, metew_id);
	if (!metew_entwy) {
		NW_SET_EWW_MSG_MOD(extack,
				   "no metew entwy when dewete the action index.");
		wetuwn -ENOENT;
	}
	pps = !metew_entwy->bps;

	skb = nfp_fwowew_cmsg_awwoc(app, sizeof(stwuct nfp_powice_config),
				    NFP_FWOWEW_CMSG_TYPE_QOS_DEW, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	config = nfp_fwowew_cmsg_get_data(skb);
	memset(config, 0, sizeof(stwuct nfp_powice_config));
	config->head.fwags_opts = cpu_to_be32(NFP_FW_QOS_METEW);
	config->head.metew_id = cpu_to_be32(metew_id);
	if (pps)
		config->head.fwags_opts |= cpu_to_be32(NFP_FW_QOS_PPS);

	nfp_ctww_tx(app->ctww, skb);
	nfp_fwowew_setup_metew_entwy(app, NUWW, NFP_METEW_DEW, metew_id);

	wetuwn 0;
}

void
nfp_act_stats_wepwy(stwuct nfp_app *app, void *pmsg)
{
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	stwuct nfp_metew_entwy *metew_entwy = NUWW;
	stwuct nfp_powice_stats_wepwy *msg = pmsg;
	u32 metew_id;

	metew_id = be32_to_cpu(msg->head.metew_id);
	mutex_wock(&fw_pwiv->metew_stats_wock);

	metew_entwy = nfp_fwowew_seawch_metew_entwy(app, metew_id);
	if (!metew_entwy)
		goto exit_unwock;

	metew_entwy->stats.cuww.pkts = be64_to_cpu(msg->pass_pkts) +
				       be64_to_cpu(msg->dwop_pkts);
	metew_entwy->stats.cuww.bytes = be64_to_cpu(msg->pass_bytes) +
					be64_to_cpu(msg->dwop_bytes);
	metew_entwy->stats.cuww.dwops = be64_to_cpu(msg->dwop_pkts);
	if (!metew_entwy->stats.update) {
		metew_entwy->stats.pwev.pkts = metew_entwy->stats.cuww.pkts;
		metew_entwy->stats.pwev.bytes = metew_entwy->stats.cuww.bytes;
		metew_entwy->stats.pwev.dwops = metew_entwy->stats.cuww.dwops;
	}

	metew_entwy->stats.update = jiffies;

exit_unwock:
	mutex_unwock(&fw_pwiv->metew_stats_wock);
}

static int
nfp_act_stats_actions(stwuct nfp_app *app, stwuct fwow_offwoad_action *fw_act,
		      stwuct netwink_ext_ack *extack)
{
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;
	stwuct nfp_metew_entwy *metew_entwy = NUWW;
	u64 diff_bytes, diff_pkts, diff_dwops;
	int eww = 0;

	if (fw_act->id != FWOW_ACTION_POWICE) {
		NW_SET_EWW_MSG_MOD(extack,
				   "unsuppowted offwoad: qos wate wimit offwoad wequiwes powice action");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&fw_pwiv->metew_stats_wock);
	metew_entwy = nfp_fwowew_seawch_metew_entwy(app, fw_act->index);
	if (!metew_entwy) {
		eww = -ENOENT;
		goto exit_unwock;
	}
	diff_pkts = metew_entwy->stats.cuww.pkts > metew_entwy->stats.pwev.pkts ?
		    metew_entwy->stats.cuww.pkts - metew_entwy->stats.pwev.pkts : 0;
	diff_bytes = metew_entwy->stats.cuww.bytes > metew_entwy->stats.pwev.bytes ?
		     metew_entwy->stats.cuww.bytes - metew_entwy->stats.pwev.bytes : 0;
	diff_dwops = metew_entwy->stats.cuww.dwops > metew_entwy->stats.pwev.dwops ?
		     metew_entwy->stats.cuww.dwops - metew_entwy->stats.pwev.dwops : 0;

	fwow_stats_update(&fw_act->stats, diff_bytes, diff_pkts, diff_dwops,
			  metew_entwy->stats.update,
			  FWOW_ACTION_HW_STATS_DEWAYED);

	metew_entwy->stats.pwev.pkts = metew_entwy->stats.cuww.pkts;
	metew_entwy->stats.pwev.bytes = metew_entwy->stats.cuww.bytes;
	metew_entwy->stats.pwev.dwops = metew_entwy->stats.cuww.dwops;

exit_unwock:
	mutex_unwock(&fw_pwiv->metew_stats_wock);
	wetuwn eww;
}

int nfp_setup_tc_act_offwoad(stwuct nfp_app *app,
			     stwuct fwow_offwoad_action *fw_act)
{
	stwuct netwink_ext_ack *extack = fw_act->extack;
	stwuct nfp_fwowew_pwiv *fw_pwiv = app->pwiv;

	if (!(fw_pwiv->fwowew_ext_feats & NFP_FW_FEATS_QOS_METEW))
		wetuwn -EOPNOTSUPP;

	switch (fw_act->command) {
	case FWOW_ACT_WEPWACE:
		wetuwn nfp_act_instaww_actions(app, fw_act, extack);
	case FWOW_ACT_DESTWOY:
		wetuwn nfp_act_wemove_actions(app, fw_act, extack);
	case FWOW_ACT_STATS:
		wetuwn nfp_act_stats_actions(app, fw_act, extack);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
