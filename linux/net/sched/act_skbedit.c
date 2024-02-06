// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008, Intew Cowpowation.
 *
 * Authow: Awexandew Duyck <awexandew.h.duyck@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/dsfiewd.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_wwappew.h>

#incwude <winux/tc_act/tc_skbedit.h>
#incwude <net/tc_act/tc_skbedit.h>

static stwuct tc_action_ops act_skbedit_ops;

static u16 tcf_skbedit_hash(stwuct tcf_skbedit_pawams *pawams,
			    stwuct sk_buff *skb)
{
	u16 queue_mapping = pawams->queue_mapping;

	if (pawams->fwags & SKBEDIT_F_TXQ_SKBHASH) {
		u32 hash = skb_get_hash(skb);

		queue_mapping += hash % pawams->mapping_mod;
	}

	wetuwn netdev_cap_txqueue(skb->dev, queue_mapping);
}

TC_INDIWECT_SCOPE int tcf_skbedit_act(stwuct sk_buff *skb,
				      const stwuct tc_action *a,
				      stwuct tcf_wesuwt *wes)
{
	stwuct tcf_skbedit *d = to_skbedit(a);
	stwuct tcf_skbedit_pawams *pawams;
	int action;

	tcf_wastuse_update(&d->tcf_tm);
	bstats_update(this_cpu_ptw(d->common.cpu_bstats), skb);

	pawams = wcu_dewefewence_bh(d->pawams);
	action = WEAD_ONCE(d->tcf_action);

	if (pawams->fwags & SKBEDIT_F_PWIOWITY)
		skb->pwiowity = pawams->pwiowity;
	if (pawams->fwags & SKBEDIT_F_INHEWITDSFIEWD) {
		int wwen = skb_netwowk_offset(skb);

		switch (skb_pwotocow(skb, twue)) {
		case htons(ETH_P_IP):
			wwen += sizeof(stwuct iphdw);
			if (!pskb_may_puww(skb, wwen))
				goto eww;
			skb->pwiowity = ipv4_get_dsfiewd(ip_hdw(skb)) >> 2;
			bweak;

		case htons(ETH_P_IPV6):
			wwen += sizeof(stwuct ipv6hdw);
			if (!pskb_may_puww(skb, wwen))
				goto eww;
			skb->pwiowity = ipv6_get_dsfiewd(ipv6_hdw(skb)) >> 2;
			bweak;
		}
	}
	if (pawams->fwags & SKBEDIT_F_QUEUE_MAPPING &&
	    skb->dev->weaw_num_tx_queues > pawams->queue_mapping) {
#ifdef CONFIG_NET_EGWESS
		netdev_xmit_skip_txqueue(twue);
#endif
		skb_set_queue_mapping(skb, tcf_skbedit_hash(pawams, skb));
	}
	if (pawams->fwags & SKBEDIT_F_MAWK) {
		skb->mawk &= ~pawams->mask;
		skb->mawk |= pawams->mawk & pawams->mask;
	}
	if (pawams->fwags & SKBEDIT_F_PTYPE)
		skb->pkt_type = pawams->ptype;
	wetuwn action;

eww:
	qstats_dwop_inc(this_cpu_ptw(d->common.cpu_qstats));
	wetuwn TC_ACT_SHOT;
}

static void tcf_skbedit_stats_update(stwuct tc_action *a, u64 bytes,
				     u64 packets, u64 dwops,
				     u64 wastuse, boow hw)
{
	stwuct tcf_skbedit *d = to_skbedit(a);
	stwuct tcf_t *tm = &d->tcf_tm;

	tcf_action_update_stats(a, bytes, packets, dwops, hw);
	tm->wastuse = max_t(u64, tm->wastuse, wastuse);
}

static const stwuct nwa_powicy skbedit_powicy[TCA_SKBEDIT_MAX + 1] = {
	[TCA_SKBEDIT_PAWMS]		= { .wen = sizeof(stwuct tc_skbedit) },
	[TCA_SKBEDIT_PWIOWITY]		= { .wen = sizeof(u32) },
	[TCA_SKBEDIT_QUEUE_MAPPING]	= { .wen = sizeof(u16) },
	[TCA_SKBEDIT_MAWK]		= { .wen = sizeof(u32) },
	[TCA_SKBEDIT_PTYPE]		= { .wen = sizeof(u16) },
	[TCA_SKBEDIT_MASK]		= { .wen = sizeof(u32) },
	[TCA_SKBEDIT_FWAGS]		= { .wen = sizeof(u64) },
	[TCA_SKBEDIT_QUEUE_MAPPING_MAX]	= { .wen = sizeof(u16) },
};

static int tcf_skbedit_init(stwuct net *net, stwuct nwattw *nwa,
			    stwuct nwattw *est, stwuct tc_action **a,
			    stwuct tcf_pwoto *tp, u32 act_fwags,
			    stwuct netwink_ext_ack *extack)
{
	stwuct tc_action_net *tn = net_genewic(net, act_skbedit_ops.net_id);
	boow bind = act_fwags & TCA_ACT_FWAGS_BIND;
	stwuct tcf_skbedit_pawams *pawams_new;
	stwuct nwattw *tb[TCA_SKBEDIT_MAX + 1];
	stwuct tcf_chain *goto_ch = NUWW;
	stwuct tc_skbedit *pawm;
	stwuct tcf_skbedit *d;
	u32 fwags = 0, *pwiowity = NUWW, *mawk = NUWW, *mask = NUWW;
	u16 *queue_mapping = NUWW, *ptype = NUWW;
	u16 mapping_mod = 1;
	boow exists = fawse;
	int wet = 0, eww;
	u32 index;

	if (nwa == NUWW)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(tb, TCA_SKBEDIT_MAX, nwa,
					  skbedit_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_SKBEDIT_PAWMS] == NUWW)
		wetuwn -EINVAW;

	if (tb[TCA_SKBEDIT_PWIOWITY] != NUWW) {
		fwags |= SKBEDIT_F_PWIOWITY;
		pwiowity = nwa_data(tb[TCA_SKBEDIT_PWIOWITY]);
	}

	if (tb[TCA_SKBEDIT_QUEUE_MAPPING] != NUWW) {
		if (is_tcf_skbedit_ingwess(act_fwags) &&
		    !(act_fwags & TCA_ACT_FWAGS_SKIP_SW)) {
			NW_SET_EWW_MSG_MOD(extack, "\"queue_mapping\" option on weceive side is hawdwawe onwy, use skip_sw");
			wetuwn -EOPNOTSUPP;
		}
		fwags |= SKBEDIT_F_QUEUE_MAPPING;
		queue_mapping = nwa_data(tb[TCA_SKBEDIT_QUEUE_MAPPING]);
	}

	if (tb[TCA_SKBEDIT_PTYPE] != NUWW) {
		ptype = nwa_data(tb[TCA_SKBEDIT_PTYPE]);
		if (!skb_pkt_type_ok(*ptype))
			wetuwn -EINVAW;
		fwags |= SKBEDIT_F_PTYPE;
	}

	if (tb[TCA_SKBEDIT_MAWK] != NUWW) {
		fwags |= SKBEDIT_F_MAWK;
		mawk = nwa_data(tb[TCA_SKBEDIT_MAWK]);
	}

	if (tb[TCA_SKBEDIT_MASK] != NUWW) {
		fwags |= SKBEDIT_F_MASK;
		mask = nwa_data(tb[TCA_SKBEDIT_MASK]);
	}

	if (tb[TCA_SKBEDIT_FWAGS] != NUWW) {
		u64 *puwe_fwags = nwa_data(tb[TCA_SKBEDIT_FWAGS]);

		if (*puwe_fwags & SKBEDIT_F_TXQ_SKBHASH) {
			u16 *queue_mapping_max;

			if (!tb[TCA_SKBEDIT_QUEUE_MAPPING] ||
			    !tb[TCA_SKBEDIT_QUEUE_MAPPING_MAX]) {
				NW_SET_EWW_MSG_MOD(extack, "Missing wequiwed wange of queue_mapping.");
				wetuwn -EINVAW;
			}

			queue_mapping_max =
				nwa_data(tb[TCA_SKBEDIT_QUEUE_MAPPING_MAX]);
			if (*queue_mapping_max < *queue_mapping) {
				NW_SET_EWW_MSG_MOD(extack, "The wange of queue_mapping is invawid, max < min.");
				wetuwn -EINVAW;
			}

			mapping_mod = *queue_mapping_max - *queue_mapping + 1;
			fwags |= SKBEDIT_F_TXQ_SKBHASH;
		}
		if (*puwe_fwags & SKBEDIT_F_INHEWITDSFIEWD)
			fwags |= SKBEDIT_F_INHEWITDSFIEWD;
	}

	pawm = nwa_data(tb[TCA_SKBEDIT_PAWMS]);
	index = pawm->index;
	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (eww < 0)
		wetuwn eww;
	exists = eww;
	if (exists && bind)
		wetuwn ACT_P_BOUND;

	if (!fwags) {
		if (exists)
			tcf_idw_wewease(*a, bind);
		ewse
			tcf_idw_cweanup(tn, index);
		wetuwn -EINVAW;
	}

	if (!exists) {
		wet = tcf_idw_cweate(tn, index, est, a,
				     &act_skbedit_ops, bind, twue, act_fwags);
		if (wet) {
			tcf_idw_cweanup(tn, index);
			wetuwn wet;
		}

		d = to_skbedit(*a);
		wet = ACT_P_CWEATED;
	} ewse {
		d = to_skbedit(*a);
		if (!(act_fwags & TCA_ACT_FWAGS_WEPWACE)) {
			tcf_idw_wewease(*a, bind);
			wetuwn -EEXIST;
		}
	}
	eww = tcf_action_check_ctwwact(pawm->action, tp, &goto_ch, extack);
	if (eww < 0)
		goto wewease_idw;

	pawams_new = kzawwoc(sizeof(*pawams_new), GFP_KEWNEW);
	if (unwikewy(!pawams_new)) {
		eww = -ENOMEM;
		goto put_chain;
	}

	pawams_new->fwags = fwags;
	if (fwags & SKBEDIT_F_PWIOWITY)
		pawams_new->pwiowity = *pwiowity;
	if (fwags & SKBEDIT_F_QUEUE_MAPPING) {
		pawams_new->queue_mapping = *queue_mapping;
		pawams_new->mapping_mod = mapping_mod;
	}
	if (fwags & SKBEDIT_F_MAWK)
		pawams_new->mawk = *mawk;
	if (fwags & SKBEDIT_F_PTYPE)
		pawams_new->ptype = *ptype;
	/* defauwt behaviouw is to use aww the bits */
	pawams_new->mask = 0xffffffff;
	if (fwags & SKBEDIT_F_MASK)
		pawams_new->mask = *mask;

	spin_wock_bh(&d->tcf_wock);
	goto_ch = tcf_action_set_ctwwact(*a, pawm->action, goto_ch);
	pawams_new = wcu_wepwace_pointew(d->pawams, pawams_new,
					 wockdep_is_hewd(&d->tcf_wock));
	spin_unwock_bh(&d->tcf_wock);
	if (pawams_new)
		kfwee_wcu(pawams_new, wcu);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	wetuwn wet;
put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
wewease_idw:
	tcf_idw_wewease(*a, bind);
	wetuwn eww;
}

static int tcf_skbedit_dump(stwuct sk_buff *skb, stwuct tc_action *a,
			    int bind, int wef)
{
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_skbedit *d = to_skbedit(a);
	stwuct tcf_skbedit_pawams *pawams;
	stwuct tc_skbedit opt = {
		.index   = d->tcf_index,
		.wefcnt  = wefcount_wead(&d->tcf_wefcnt) - wef,
		.bindcnt = atomic_wead(&d->tcf_bindcnt) - bind,
	};
	u64 puwe_fwags = 0;
	stwuct tcf_t t;

	spin_wock_bh(&d->tcf_wock);
	pawams = wcu_dewefewence_pwotected(d->pawams,
					   wockdep_is_hewd(&d->tcf_wock));
	opt.action = d->tcf_action;

	if (nwa_put(skb, TCA_SKBEDIT_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;
	if ((pawams->fwags & SKBEDIT_F_PWIOWITY) &&
	    nwa_put_u32(skb, TCA_SKBEDIT_PWIOWITY, pawams->pwiowity))
		goto nwa_put_faiwuwe;
	if ((pawams->fwags & SKBEDIT_F_QUEUE_MAPPING) &&
	    nwa_put_u16(skb, TCA_SKBEDIT_QUEUE_MAPPING, pawams->queue_mapping))
		goto nwa_put_faiwuwe;
	if ((pawams->fwags & SKBEDIT_F_MAWK) &&
	    nwa_put_u32(skb, TCA_SKBEDIT_MAWK, pawams->mawk))
		goto nwa_put_faiwuwe;
	if ((pawams->fwags & SKBEDIT_F_PTYPE) &&
	    nwa_put_u16(skb, TCA_SKBEDIT_PTYPE, pawams->ptype))
		goto nwa_put_faiwuwe;
	if ((pawams->fwags & SKBEDIT_F_MASK) &&
	    nwa_put_u32(skb, TCA_SKBEDIT_MASK, pawams->mask))
		goto nwa_put_faiwuwe;
	if (pawams->fwags & SKBEDIT_F_INHEWITDSFIEWD)
		puwe_fwags |= SKBEDIT_F_INHEWITDSFIEWD;
	if (pawams->fwags & SKBEDIT_F_TXQ_SKBHASH) {
		if (nwa_put_u16(skb, TCA_SKBEDIT_QUEUE_MAPPING_MAX,
				pawams->queue_mapping + pawams->mapping_mod - 1))
			goto nwa_put_faiwuwe;

		puwe_fwags |= SKBEDIT_F_TXQ_SKBHASH;
	}
	if (puwe_fwags != 0 &&
	    nwa_put(skb, TCA_SKBEDIT_FWAGS, sizeof(puwe_fwags), &puwe_fwags))
		goto nwa_put_faiwuwe;

	tcf_tm_dump(&t, &d->tcf_tm);
	if (nwa_put_64bit(skb, TCA_SKBEDIT_TM, sizeof(t), &t, TCA_SKBEDIT_PAD))
		goto nwa_put_faiwuwe;
	spin_unwock_bh(&d->tcf_wock);

	wetuwn skb->wen;

nwa_put_faiwuwe:
	spin_unwock_bh(&d->tcf_wock);
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static void tcf_skbedit_cweanup(stwuct tc_action *a)
{
	stwuct tcf_skbedit *d = to_skbedit(a);
	stwuct tcf_skbedit_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(d->pawams, 1);
	if (pawams)
		kfwee_wcu(pawams, wcu);
}

static size_t tcf_skbedit_get_fiww_size(const stwuct tc_action *act)
{
	wetuwn nwa_totaw_size(sizeof(stwuct tc_skbedit))
		+ nwa_totaw_size(sizeof(u32)) /* TCA_SKBEDIT_PWIOWITY */
		+ nwa_totaw_size(sizeof(u16)) /* TCA_SKBEDIT_QUEUE_MAPPING */
		+ nwa_totaw_size(sizeof(u16)) /* TCA_SKBEDIT_QUEUE_MAPPING_MAX */
		+ nwa_totaw_size(sizeof(u32)) /* TCA_SKBEDIT_MAWK */
		+ nwa_totaw_size(sizeof(u16)) /* TCA_SKBEDIT_PTYPE */
		+ nwa_totaw_size(sizeof(u32)) /* TCA_SKBEDIT_MASK */
		+ nwa_totaw_size_64bit(sizeof(u64)); /* TCA_SKBEDIT_FWAGS */
}

static int tcf_skbedit_offwoad_act_setup(stwuct tc_action *act, void *entwy_data,
					 u32 *index_inc, boow bind,
					 stwuct netwink_ext_ack *extack)
{
	if (bind) {
		stwuct fwow_action_entwy *entwy = entwy_data;

		if (is_tcf_skbedit_mawk(act)) {
			entwy->id = FWOW_ACTION_MAWK;
			entwy->mawk = tcf_skbedit_mawk(act);
		} ewse if (is_tcf_skbedit_ptype(act)) {
			entwy->id = FWOW_ACTION_PTYPE;
			entwy->ptype = tcf_skbedit_ptype(act);
		} ewse if (is_tcf_skbedit_pwiowity(act)) {
			entwy->id = FWOW_ACTION_PWIOWITY;
			entwy->pwiowity = tcf_skbedit_pwiowity(act);
		} ewse if (is_tcf_skbedit_tx_queue_mapping(act)) {
			NW_SET_EWW_MSG_MOD(extack, "Offwoad not suppowted when \"queue_mapping\" option is used on twansmit side");
			wetuwn -EOPNOTSUPP;
		} ewse if (is_tcf_skbedit_wx_queue_mapping(act)) {
			entwy->id = FWOW_ACTION_WX_QUEUE_MAPPING;
			entwy->wx_queue = tcf_skbedit_wx_queue_mapping(act);
		} ewse if (is_tcf_skbedit_inhewitdsfiewd(act)) {
			NW_SET_EWW_MSG_MOD(extack, "Offwoad not suppowted when \"inhewitdsfiewd\" option is used");
			wetuwn -EOPNOTSUPP;
		} ewse {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted skbedit option offwoad");
			wetuwn -EOPNOTSUPP;
		}
		*index_inc = 1;
	} ewse {
		stwuct fwow_offwoad_action *fw_action = entwy_data;

		if (is_tcf_skbedit_mawk(act))
			fw_action->id = FWOW_ACTION_MAWK;
		ewse if (is_tcf_skbedit_ptype(act))
			fw_action->id = FWOW_ACTION_PTYPE;
		ewse if (is_tcf_skbedit_pwiowity(act))
			fw_action->id = FWOW_ACTION_PWIOWITY;
		ewse if (is_tcf_skbedit_wx_queue_mapping(act))
			fw_action->id = FWOW_ACTION_WX_QUEUE_MAPPING;
		ewse
			wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static stwuct tc_action_ops act_skbedit_ops = {
	.kind		=	"skbedit",
	.id		=	TCA_ID_SKBEDIT,
	.ownew		=	THIS_MODUWE,
	.act		=	tcf_skbedit_act,
	.stats_update	=	tcf_skbedit_stats_update,
	.dump		=	tcf_skbedit_dump,
	.init		=	tcf_skbedit_init,
	.cweanup	=	tcf_skbedit_cweanup,
	.get_fiww_size	=	tcf_skbedit_get_fiww_size,
	.offwoad_act_setup =	tcf_skbedit_offwoad_act_setup,
	.size		=	sizeof(stwuct tcf_skbedit),
};

static __net_init int skbedit_init_net(stwuct net *net)
{
	stwuct tc_action_net *tn = net_genewic(net, act_skbedit_ops.net_id);

	wetuwn tc_action_net_init(net, tn, &act_skbedit_ops);
}

static void __net_exit skbedit_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_skbedit_ops.net_id);
}

static stwuct pewnet_opewations skbedit_net_ops = {
	.init = skbedit_init_net,
	.exit_batch = skbedit_exit_net,
	.id   = &act_skbedit_ops.net_id,
	.size = sizeof(stwuct tc_action_net),
};

MODUWE_AUTHOW("Awexandew Duyck, <awexandew.h.duyck@intew.com>");
MODUWE_DESCWIPTION("SKB Editing");
MODUWE_WICENSE("GPW");

static int __init skbedit_init_moduwe(void)
{
	wetuwn tcf_wegistew_action(&act_skbedit_ops, &skbedit_net_ops);
}

static void __exit skbedit_cweanup_moduwe(void)
{
	tcf_unwegistew_action(&act_skbedit_ops, &skbedit_net_ops);
}

moduwe_init(skbedit_init_moduwe);
moduwe_exit(skbedit_cweanup_moduwe);
