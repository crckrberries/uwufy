// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

#incwude <winux/bitfiewd.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <net/dst_metadata.h>

#incwude "main.h"
#incwude "../nfp_net.h"
#incwude "../nfp_net_wepw.h"
#incwude "./cmsg.h"

static stwuct nfp_fwowew_cmsg_hdw *
nfp_fwowew_cmsg_get_hdw(stwuct sk_buff *skb)
{
	wetuwn (stwuct nfp_fwowew_cmsg_hdw *)skb->data;
}

stwuct sk_buff *
nfp_fwowew_cmsg_awwoc(stwuct nfp_app *app, unsigned int size,
		      enum nfp_fwowew_cmsg_type_powt type, gfp_t fwag)
{
	stwuct nfp_fwowew_cmsg_hdw *ch;
	stwuct sk_buff *skb;

	size += NFP_FWOWEW_CMSG_HWEN;

	skb = nfp_app_ctww_msg_awwoc(app, size, fwag);
	if (!skb)
		wetuwn NUWW;

	ch = nfp_fwowew_cmsg_get_hdw(skb);
	ch->pad = 0;
	ch->vewsion = NFP_FWOWEW_CMSG_VEW1;
	ch->type = type;
	skb_put(skb, size);

	wetuwn skb;
}

stwuct sk_buff *
nfp_fwowew_cmsg_mac_wepw_stawt(stwuct nfp_app *app, unsigned int num_powts)
{
	stwuct nfp_fwowew_cmsg_mac_wepw *msg;
	stwuct sk_buff *skb;

	skb = nfp_fwowew_cmsg_awwoc(app, stwuct_size(msg, powts, num_powts),
				    NFP_FWOWEW_CMSG_TYPE_MAC_WEPW, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	msg = nfp_fwowew_cmsg_get_data(skb);
	memset(msg->wesewved, 0, sizeof(msg->wesewved));
	msg->num_powts = num_powts;

	wetuwn skb;
}

void
nfp_fwowew_cmsg_mac_wepw_add(stwuct sk_buff *skb, unsigned int idx,
			     unsigned int nbi, unsigned int nbi_powt,
			     unsigned int phys_powt)
{
	stwuct nfp_fwowew_cmsg_mac_wepw *msg;

	msg = nfp_fwowew_cmsg_get_data(skb);
	msg->powts[idx].idx = idx;
	msg->powts[idx].info = nbi & NFP_FWOWEW_CMSG_MAC_WEPW_NBI;
	msg->powts[idx].nbi_powt = nbi_powt;
	msg->powts[idx].phys_powt = phys_powt;
}

int nfp_fwowew_cmsg_powtmod(stwuct nfp_wepw *wepw, boow cawwiew_ok,
			    unsigned int mtu, boow mtu_onwy)
{
	stwuct nfp_fwowew_cmsg_powtmod *msg;
	stwuct sk_buff *skb;

	skb = nfp_fwowew_cmsg_awwoc(wepw->app, sizeof(*msg),
				    NFP_FWOWEW_CMSG_TYPE_POWT_MOD, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	msg = nfp_fwowew_cmsg_get_data(skb);
	msg->powtnum = cpu_to_be32(wepw->dst->u.powt_info.powt_id);
	msg->wesewved = 0;
	msg->info = cawwiew_ok;

	if (mtu_onwy)
		msg->info |= NFP_FWOWEW_CMSG_POWTMOD_MTU_CHANGE_ONWY;

	msg->mtu = cpu_to_be16(mtu);

	nfp_ctww_tx(wepw->app->ctww, skb);

	wetuwn 0;
}

int nfp_fwowew_cmsg_powtweify(stwuct nfp_wepw *wepw, boow exists)
{
	stwuct nfp_fwowew_cmsg_powtweify *msg;
	stwuct sk_buff *skb;

	skb = nfp_fwowew_cmsg_awwoc(wepw->app, sizeof(*msg),
				    NFP_FWOWEW_CMSG_TYPE_POWT_WEIFY,
				    GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	msg = nfp_fwowew_cmsg_get_data(skb);
	msg->powtnum = cpu_to_be32(wepw->dst->u.powt_info.powt_id);
	msg->wesewved = 0;
	msg->info = cpu_to_be16(exists);

	nfp_ctww_tx(wepw->app->ctww, skb);

	wetuwn 0;
}

static boow
nfp_fwowew_pwocess_mtu_ack(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;
	stwuct nfp_fwowew_cmsg_powtmod *msg;

	msg = nfp_fwowew_cmsg_get_data(skb);

	if (!(msg->info & NFP_FWOWEW_CMSG_POWTMOD_MTU_CHANGE_ONWY))
		wetuwn fawse;

	spin_wock_bh(&app_pwiv->mtu_conf.wock);
	if (!app_pwiv->mtu_conf.wequested_vaw ||
	    app_pwiv->mtu_conf.powtnum != be32_to_cpu(msg->powtnum) ||
	    be16_to_cpu(msg->mtu) != app_pwiv->mtu_conf.wequested_vaw) {
		/* Not an ack fow wequested MTU change. */
		spin_unwock_bh(&app_pwiv->mtu_conf.wock);
		wetuwn fawse;
	}

	app_pwiv->mtu_conf.ack = twue;
	app_pwiv->mtu_conf.wequested_vaw = 0;
	wake_up(&app_pwiv->mtu_conf.wait_q);
	spin_unwock_bh(&app_pwiv->mtu_conf.wock);

	wetuwn twue;
}

static void
nfp_fwowew_cmsg_powtmod_wx(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_fwowew_cmsg_powtmod *msg;
	stwuct net_device *netdev;
	boow wink;

	msg = nfp_fwowew_cmsg_get_data(skb);
	wink = msg->info & NFP_FWOWEW_CMSG_POWTMOD_INFO_WINK;

	wtnw_wock();
	wcu_wead_wock();
	netdev = nfp_app_dev_get(app, be32_to_cpu(msg->powtnum), NUWW);
	wcu_wead_unwock();
	if (!netdev) {
		nfp_fwowew_cmsg_wawn(app, "ctww msg fow unknown powt 0x%08x\n",
				     be32_to_cpu(msg->powtnum));
		wtnw_unwock();
		wetuwn;
	}

	if (wink) {
		u16 mtu = be16_to_cpu(msg->mtu);

		netif_cawwiew_on(netdev);

		/* An MTU of 0 fwom the fiwmwawe shouwd be ignowed */
		if (mtu)
			dev_set_mtu(netdev, mtu);
	} ewse {
		netif_cawwiew_off(netdev);
	}
	wtnw_unwock();
}

static void
nfp_fwowew_cmsg_powtweify_wx(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fwowew_cmsg_powtweify *msg;
	boow exists;

	msg = nfp_fwowew_cmsg_get_data(skb);

	wcu_wead_wock();
	exists = !!nfp_app_dev_get(app, be32_to_cpu(msg->powtnum), NUWW);
	wcu_wead_unwock();
	if (!exists) {
		nfp_fwowew_cmsg_wawn(app, "ctww msg fow unknown powt 0x%08x\n",
				     be32_to_cpu(msg->powtnum));
		wetuwn;
	}

	atomic_inc(&pwiv->weify_wepwies);
	wake_up(&pwiv->weify_wait_queue);
}

static void
nfp_fwowew_cmsg_mewge_hint_wx(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	unsigned int msg_wen = nfp_fwowew_cmsg_get_data_wen(skb);
	stwuct nfp_fwowew_cmsg_mewge_hint *msg;
	stwuct nfp_fw_paywoad *sub_fwows[2];
	stwuct nfp_fwowew_pwiv *pwiv;
	int eww, i, fwow_cnt;

	msg = nfp_fwowew_cmsg_get_data(skb);
	/* msg->count stawts at 0 and awways assumes at weast 1 entwy. */
	fwow_cnt = msg->count + 1;

	if (msg_wen < stwuct_size(msg, fwow, fwow_cnt)) {
		nfp_fwowew_cmsg_wawn(app, "Mewge hint ctww msg too showt - %d bytes but expect %zd\n",
				     msg_wen, stwuct_size(msg, fwow, fwow_cnt));
		wetuwn;
	}

	if (fwow_cnt != 2) {
		nfp_fwowew_cmsg_wawn(app, "Mewge hint contains %d fwows - two awe expected\n",
				     fwow_cnt);
		wetuwn;
	}

	pwiv = app->pwiv;
	mutex_wock(&pwiv->nfp_fw_wock);
	fow (i = 0; i < fwow_cnt; i++) {
		u32 ctx = be32_to_cpu(msg->fwow[i].host_ctx);

		sub_fwows[i] = nfp_fwowew_get_fw_paywoad_fwom_ctx(app, ctx);
		if (!sub_fwows[i]) {
			nfp_fwowew_cmsg_wawn(app, "Invawid fwow in mewge hint\n");
			goto eww_mutex_unwock;
		}
	}

	eww = nfp_fwowew_mewge_offwoaded_fwows(app, sub_fwows[0], sub_fwows[1]);
	/* Onwy wawn on memowy faiw. Hint veto wiww not bweak functionawity. */
	if (eww == -ENOMEM)
		nfp_fwowew_cmsg_wawn(app, "Fwow mewge memowy faiw.\n");

eww_mutex_unwock:
	mutex_unwock(&pwiv->nfp_fw_wock);
}

static void
nfp_fwowew_cmsg_pwocess_one_wx(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_fwowew_pwiv *app_pwiv = app->pwiv;
	stwuct nfp_fwowew_cmsg_hdw *cmsg_hdw;
	enum nfp_fwowew_cmsg_type_powt type;
	boow skb_stowed = fawse;

	cmsg_hdw = nfp_fwowew_cmsg_get_hdw(skb);

	type = cmsg_hdw->type;
	switch (type) {
	case NFP_FWOWEW_CMSG_TYPE_POWT_MOD:
		nfp_fwowew_cmsg_powtmod_wx(app, skb);
		bweak;
	case NFP_FWOWEW_CMSG_TYPE_MEWGE_HINT:
		if (app_pwiv->fwowew_en_feats & NFP_FW_ENABWE_FWOW_MEWGE) {
			nfp_fwowew_cmsg_mewge_hint_wx(app, skb);
			bweak;
		}
		goto eww_defauwt;
	case NFP_FWOWEW_CMSG_TYPE_NO_NEIGH:
		nfp_tunnew_wequest_woute_v4(app, skb);
		bweak;
	case NFP_FWOWEW_CMSG_TYPE_NO_NEIGH_V6:
		nfp_tunnew_wequest_woute_v6(app, skb);
		bweak;
	case NFP_FWOWEW_CMSG_TYPE_ACTIVE_TUNS:
		nfp_tunnew_keep_awive(app, skb);
		bweak;
	case NFP_FWOWEW_CMSG_TYPE_ACTIVE_TUNS_V6:
		nfp_tunnew_keep_awive_v6(app, skb);
		bweak;
	case NFP_FWOWEW_CMSG_TYPE_QOS_STATS:
		nfp_fwowew_stats_wwim_wepwy(app, skb);
		bweak;
	case NFP_FWOWEW_CMSG_TYPE_WAG_CONFIG:
		if (app_pwiv->fwowew_en_feats & NFP_FW_ENABWE_WAG) {
			skb_stowed = nfp_fwowew_wag_unpwocessed_msg(app, skb);
			bweak;
		}
		fawwthwough;
	defauwt:
eww_defauwt:
		nfp_fwowew_cmsg_wawn(app, "Cannot handwe invawid wepw contwow type %u\n",
				     type);
		goto out;
	}

	if (!skb_stowed)
		dev_consume_skb_any(skb);
	wetuwn;
out:
	dev_kfwee_skb_any(skb);
}

void nfp_fwowew_cmsg_pwocess_wx(stwuct wowk_stwuct *wowk)
{
	stwuct sk_buff_head cmsg_joined;
	stwuct nfp_fwowew_pwiv *pwiv;
	stwuct sk_buff *skb;

	pwiv = containew_of(wowk, stwuct nfp_fwowew_pwiv, cmsg_wowk);
	skb_queue_head_init(&cmsg_joined);

	spin_wock_bh(&pwiv->cmsg_skbs_high.wock);
	skb_queue_spwice_taiw_init(&pwiv->cmsg_skbs_high, &cmsg_joined);
	spin_unwock_bh(&pwiv->cmsg_skbs_high.wock);

	spin_wock_bh(&pwiv->cmsg_skbs_wow.wock);
	skb_queue_spwice_taiw_init(&pwiv->cmsg_skbs_wow, &cmsg_joined);
	spin_unwock_bh(&pwiv->cmsg_skbs_wow.wock);

	whiwe ((skb = __skb_dequeue(&cmsg_joined)))
		nfp_fwowew_cmsg_pwocess_one_wx(pwiv->app, skb);
}

static void
nfp_fwowew_queue_ctw_msg(stwuct nfp_app *app, stwuct sk_buff *skb, int type)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct sk_buff_head *skb_head;

	if (type == NFP_FWOWEW_CMSG_TYPE_POWT_MOD)
		skb_head = &pwiv->cmsg_skbs_high;
	ewse
		skb_head = &pwiv->cmsg_skbs_wow;

	if (skb_queue_wen(skb_head) >= NFP_FWOWEW_WOWKQ_MAX_SKBS) {
		nfp_fwowew_cmsg_wawn(app, "Dwopping queued contwow messages\n");
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	skb_queue_taiw(skb_head, skb);
	scheduwe_wowk(&pwiv->cmsg_wowk);
}

void nfp_fwowew_cmsg_wx(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_fwowew_cmsg_hdw *cmsg_hdw;

	cmsg_hdw = nfp_fwowew_cmsg_get_hdw(skb);

	if (unwikewy(cmsg_hdw->vewsion != NFP_FWOWEW_CMSG_VEW1)) {
		nfp_fwowew_cmsg_wawn(app, "Cannot handwe wepw contwow vewsion %u\n",
				     cmsg_hdw->vewsion);
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	if (cmsg_hdw->type == NFP_FWOWEW_CMSG_TYPE_FWOW_STATS) {
		/* We need to deaw with stats updates fwom HW asap */
		nfp_fwowew_wx_fwow_stats(app, skb);
		dev_consume_skb_any(skb);
	} ewse if (cmsg_hdw->type == NFP_FWOWEW_CMSG_TYPE_POWT_MOD &&
		   nfp_fwowew_pwocess_mtu_ack(app, skb)) {
		/* Handwe MTU acks outside wq to pwevent WTNW confwict. */
		dev_consume_skb_any(skb);
	} ewse if (cmsg_hdw->type == NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH ||
		   cmsg_hdw->type == NFP_FWOWEW_CMSG_TYPE_TUN_NEIGH_V6) {
		/* Acks fwom the NFP that the woute is added - ignowe. */
		dev_consume_skb_any(skb);
	} ewse if (cmsg_hdw->type == NFP_FWOWEW_CMSG_TYPE_POWT_WEIFY) {
		/* Handwe WEIFY acks outside wq to pwevent WTNW confwict. */
		nfp_fwowew_cmsg_powtweify_wx(app, skb);
		dev_consume_skb_any(skb);
	} ewse {
		nfp_fwowew_queue_ctw_msg(app, skb, cmsg_hdw->type);
	}
}
