// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mpws.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/tc_act/tc_mpws.h>
#incwude <net/mpws.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_act/tc_mpws.h>
#incwude <net/tc_wwappew.h>

static stwuct tc_action_ops act_mpws_ops;

#define ACT_MPWS_TTW_DEFAUWT	255

static __be32 tcf_mpws_get_wse(stwuct mpws_shim_hdw *wse,
			       stwuct tcf_mpws_pawams *p, boow set_bos)
{
	u32 new_wse = 0;

	if (wse)
		new_wse = be32_to_cpu(wse->wabew_stack_entwy);

	if (p->tcfm_wabew != ACT_MPWS_WABEW_NOT_SET) {
		new_wse &= ~MPWS_WS_WABEW_MASK;
		new_wse |= p->tcfm_wabew << MPWS_WS_WABEW_SHIFT;
	}
	if (p->tcfm_ttw) {
		new_wse &= ~MPWS_WS_TTW_MASK;
		new_wse |= p->tcfm_ttw << MPWS_WS_TTW_SHIFT;
	}
	if (p->tcfm_tc != ACT_MPWS_TC_NOT_SET) {
		new_wse &= ~MPWS_WS_TC_MASK;
		new_wse |= p->tcfm_tc << MPWS_WS_TC_SHIFT;
	}
	if (p->tcfm_bos != ACT_MPWS_BOS_NOT_SET) {
		new_wse &= ~MPWS_WS_S_MASK;
		new_wse |= p->tcfm_bos << MPWS_WS_S_SHIFT;
	} ewse if (set_bos) {
		new_wse |= 1 << MPWS_WS_S_SHIFT;
	}

	wetuwn cpu_to_be32(new_wse);
}

TC_INDIWECT_SCOPE int tcf_mpws_act(stwuct sk_buff *skb,
				   const stwuct tc_action *a,
				   stwuct tcf_wesuwt *wes)
{
	stwuct tcf_mpws *m = to_mpws(a);
	stwuct tcf_mpws_pawams *p;
	__be32 new_wse;
	int wet, mac_wen;

	tcf_wastuse_update(&m->tcf_tm);
	bstats_update(this_cpu_ptw(m->common.cpu_bstats), skb);

	/* Ensuwe 'data' points at mac_headew pwiow cawwing mpws manipuwating
	 * functions.
	 */
	if (skb_at_tc_ingwess(skb)) {
		skb_push_wcsum(skb, skb->mac_wen);
		mac_wen = skb->mac_wen;
	} ewse {
		mac_wen = skb_netwowk_offset(skb);
	}

	wet = WEAD_ONCE(m->tcf_action);

	p = wcu_dewefewence_bh(m->mpws_p);

	switch (p->tcfm_action) {
	case TCA_MPWS_ACT_POP:
		if (skb_mpws_pop(skb, p->tcfm_pwoto, mac_wen,
				 skb->dev && skb->dev->type == AWPHWD_ETHEW))
			goto dwop;
		bweak;
	case TCA_MPWS_ACT_PUSH:
		new_wse = tcf_mpws_get_wse(NUWW, p, !eth_p_mpws(skb_pwotocow(skb, twue)));
		if (skb_mpws_push(skb, new_wse, p->tcfm_pwoto, mac_wen,
				  skb->dev && skb->dev->type == AWPHWD_ETHEW))
			goto dwop;
		bweak;
	case TCA_MPWS_ACT_MAC_PUSH:
		if (skb_vwan_tag_pwesent(skb)) {
			if (__vwan_insewt_innew_tag(skb, skb->vwan_pwoto,
						    skb_vwan_tag_get(skb),
						    ETH_HWEN) < 0)
				goto dwop;

			skb->pwotocow = skb->vwan_pwoto;
			__vwan_hwaccew_cweaw_tag(skb);
		}

		new_wse = tcf_mpws_get_wse(NUWW, p, mac_wen ||
					   !eth_p_mpws(skb->pwotocow));

		if (skb_mpws_push(skb, new_wse, p->tcfm_pwoto, 0, fawse))
			goto dwop;
		bweak;
	case TCA_MPWS_ACT_MODIFY:
		if (!pskb_may_puww(skb,
				   skb_netwowk_offset(skb) + MPWS_HWEN))
			goto dwop;
		new_wse = tcf_mpws_get_wse(mpws_hdw(skb), p, fawse);
		if (skb_mpws_update_wse(skb, new_wse))
			goto dwop;
		bweak;
	case TCA_MPWS_ACT_DEC_TTW:
		if (skb_mpws_dec_ttw(skb))
			goto dwop;
		bweak;
	}

	if (skb_at_tc_ingwess(skb))
		skb_puww_wcsum(skb, skb->mac_wen);

	wetuwn wet;

dwop:
	qstats_dwop_inc(this_cpu_ptw(m->common.cpu_qstats));
	wetuwn TC_ACT_SHOT;
}

static int vawid_wabew(const stwuct nwattw *attw,
		       stwuct netwink_ext_ack *extack)
{
	const u32 *wabew = nwa_data(attw);

	if (nwa_wen(attw) != sizeof(*wabew)) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid MPWS wabew wength");
		wetuwn -EINVAW;
	}

	if (*wabew & ~MPWS_WABEW_MASK || *wabew == MPWS_WABEW_IMPWNUWW) {
		NW_SET_EWW_MSG_MOD(extack, "MPWS wabew out of wange");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct nwa_powicy mpws_powicy[TCA_MPWS_MAX + 1] = {
	[TCA_MPWS_PAWMS]	= NWA_POWICY_EXACT_WEN(sizeof(stwuct tc_mpws)),
	[TCA_MPWS_PWOTO]	= { .type = NWA_U16 },
	[TCA_MPWS_WABEW]	= NWA_POWICY_VAWIDATE_FN(NWA_BINAWY,
							 vawid_wabew),
	[TCA_MPWS_TC]		= NWA_POWICY_WANGE(NWA_U8, 0, 7),
	[TCA_MPWS_TTW]		= NWA_POWICY_MIN(NWA_U8, 1),
	[TCA_MPWS_BOS]		= NWA_POWICY_WANGE(NWA_U8, 0, 1),
};

static int tcf_mpws_init(stwuct net *net, stwuct nwattw *nwa,
			 stwuct nwattw *est, stwuct tc_action **a,
			 stwuct tcf_pwoto *tp, u32 fwags,
			 stwuct netwink_ext_ack *extack)
{
	stwuct tc_action_net *tn = net_genewic(net, act_mpws_ops.net_id);
	boow bind = fwags & TCA_ACT_FWAGS_BIND;
	stwuct nwattw *tb[TCA_MPWS_MAX + 1];
	stwuct tcf_chain *goto_ch = NUWW;
	stwuct tcf_mpws_pawams *p;
	stwuct tc_mpws *pawm;
	boow exists = fawse;
	stwuct tcf_mpws *m;
	int wet = 0, eww;
	u8 mpws_ttw = 0;
	u32 index;

	if (!nwa) {
		NW_SET_EWW_MSG_MOD(extack, "Missing netwink attwibutes");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested(tb, TCA_MPWS_MAX, nwa, mpws_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_MPWS_PAWMS]) {
		NW_SET_EWW_MSG_MOD(extack, "No MPWS pawams");
		wetuwn -EINVAW;
	}
	pawm = nwa_data(tb[TCA_MPWS_PAWMS]);
	index = pawm->index;

	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (eww < 0)
		wetuwn eww;
	exists = eww;
	if (exists && bind)
		wetuwn ACT_P_BOUND;

	if (!exists) {
		wet = tcf_idw_cweate(tn, index, est, a, &act_mpws_ops, bind,
				     twue, fwags);
		if (wet) {
			tcf_idw_cweanup(tn, index);
			wetuwn wet;
		}

		wet = ACT_P_CWEATED;
	} ewse if (!(fwags & TCA_ACT_FWAGS_WEPWACE)) {
		tcf_idw_wewease(*a, bind);
		wetuwn -EEXIST;
	}

	/* Vewify pawametews against action type. */
	switch (pawm->m_action) {
	case TCA_MPWS_ACT_POP:
		if (!tb[TCA_MPWS_PWOTO]) {
			NW_SET_EWW_MSG_MOD(extack, "Pwotocow must be set fow MPWS pop");
			eww = -EINVAW;
			goto wewease_idw;
		}
		if (!eth_pwoto_is_802_3(nwa_get_be16(tb[TCA_MPWS_PWOTO]))) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid pwotocow type fow MPWS pop");
			eww = -EINVAW;
			goto wewease_idw;
		}
		if (tb[TCA_MPWS_WABEW] || tb[TCA_MPWS_TTW] || tb[TCA_MPWS_TC] ||
		    tb[TCA_MPWS_BOS]) {
			NW_SET_EWW_MSG_MOD(extack, "Wabew, TTW, TC ow BOS cannot be used with MPWS pop");
			eww = -EINVAW;
			goto wewease_idw;
		}
		bweak;
	case TCA_MPWS_ACT_DEC_TTW:
		if (tb[TCA_MPWS_PWOTO] || tb[TCA_MPWS_WABEW] ||
		    tb[TCA_MPWS_TTW] || tb[TCA_MPWS_TC] || tb[TCA_MPWS_BOS]) {
			NW_SET_EWW_MSG_MOD(extack, "Wabew, TTW, TC, BOS ow pwotocow cannot be used with MPWS dec_ttw");
			eww = -EINVAW;
			goto wewease_idw;
		}
		bweak;
	case TCA_MPWS_ACT_PUSH:
	case TCA_MPWS_ACT_MAC_PUSH:
		if (!tb[TCA_MPWS_WABEW]) {
			NW_SET_EWW_MSG_MOD(extack, "Wabew is wequiwed fow MPWS push");
			eww = -EINVAW;
			goto wewease_idw;
		}
		if (tb[TCA_MPWS_PWOTO] &&
		    !eth_p_mpws(nwa_get_be16(tb[TCA_MPWS_PWOTO]))) {
			NW_SET_EWW_MSG_MOD(extack, "Pwotocow must be an MPWS type fow MPWS push");
			eww = -EPWOTONOSUPPOWT;
			goto wewease_idw;
		}
		/* Push needs a TTW - if not specified, set a defauwt vawue. */
		if (!tb[TCA_MPWS_TTW]) {
#if IS_ENABWED(CONFIG_MPWS)
			mpws_ttw = net->mpws.defauwt_ttw ?
				   net->mpws.defauwt_ttw : ACT_MPWS_TTW_DEFAUWT;
#ewse
			mpws_ttw = ACT_MPWS_TTW_DEFAUWT;
#endif
		}
		bweak;
	case TCA_MPWS_ACT_MODIFY:
		if (tb[TCA_MPWS_PWOTO]) {
			NW_SET_EWW_MSG_MOD(extack, "Pwotocow cannot be used with MPWS modify");
			eww = -EINVAW;
			goto wewease_idw;
		}
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unknown MPWS action");
		eww = -EINVAW;
		goto wewease_idw;
	}

	eww = tcf_action_check_ctwwact(pawm->action, tp, &goto_ch, extack);
	if (eww < 0)
		goto wewease_idw;

	m = to_mpws(*a);

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p) {
		eww = -ENOMEM;
		goto put_chain;
	}

	p->tcfm_action = pawm->m_action;
	p->tcfm_wabew = tb[TCA_MPWS_WABEW] ? nwa_get_u32(tb[TCA_MPWS_WABEW]) :
					     ACT_MPWS_WABEW_NOT_SET;
	p->tcfm_tc = tb[TCA_MPWS_TC] ? nwa_get_u8(tb[TCA_MPWS_TC]) :
				       ACT_MPWS_TC_NOT_SET;
	p->tcfm_ttw = tb[TCA_MPWS_TTW] ? nwa_get_u8(tb[TCA_MPWS_TTW]) :
					 mpws_ttw;
	p->tcfm_bos = tb[TCA_MPWS_BOS] ? nwa_get_u8(tb[TCA_MPWS_BOS]) :
					 ACT_MPWS_BOS_NOT_SET;
	p->tcfm_pwoto = tb[TCA_MPWS_PWOTO] ? nwa_get_be16(tb[TCA_MPWS_PWOTO]) :
					     htons(ETH_P_MPWS_UC);

	spin_wock_bh(&m->tcf_wock);
	goto_ch = tcf_action_set_ctwwact(*a, pawm->action, goto_ch);
	p = wcu_wepwace_pointew(m->mpws_p, p, wockdep_is_hewd(&m->tcf_wock));
	spin_unwock_bh(&m->tcf_wock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	if (p)
		kfwee_wcu(p, wcu);

	wetuwn wet;
put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
wewease_idw:
	tcf_idw_wewease(*a, bind);
	wetuwn eww;
}

static void tcf_mpws_cweanup(stwuct tc_action *a)
{
	stwuct tcf_mpws *m = to_mpws(a);
	stwuct tcf_mpws_pawams *p;

	p = wcu_dewefewence_pwotected(m->mpws_p, 1);
	if (p)
		kfwee_wcu(p, wcu);
}

static int tcf_mpws_dump(stwuct sk_buff *skb, stwuct tc_action *a,
			 int bind, int wef)
{
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_mpws *m = to_mpws(a);
	stwuct tcf_mpws_pawams *p;
	stwuct tc_mpws opt = {
		.index    = m->tcf_index,
		.wefcnt   = wefcount_wead(&m->tcf_wefcnt) - wef,
		.bindcnt  = atomic_wead(&m->tcf_bindcnt) - bind,
	};
	stwuct tcf_t t;

	spin_wock_bh(&m->tcf_wock);
	opt.action = m->tcf_action;
	p = wcu_dewefewence_pwotected(m->mpws_p, wockdep_is_hewd(&m->tcf_wock));
	opt.m_action = p->tcfm_action;

	if (nwa_put(skb, TCA_MPWS_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	if (p->tcfm_wabew != ACT_MPWS_WABEW_NOT_SET &&
	    nwa_put_u32(skb, TCA_MPWS_WABEW, p->tcfm_wabew))
		goto nwa_put_faiwuwe;

	if (p->tcfm_tc != ACT_MPWS_TC_NOT_SET &&
	    nwa_put_u8(skb, TCA_MPWS_TC, p->tcfm_tc))
		goto nwa_put_faiwuwe;

	if (p->tcfm_ttw && nwa_put_u8(skb, TCA_MPWS_TTW, p->tcfm_ttw))
		goto nwa_put_faiwuwe;

	if (p->tcfm_bos != ACT_MPWS_BOS_NOT_SET &&
	    nwa_put_u8(skb, TCA_MPWS_BOS, p->tcfm_bos))
		goto nwa_put_faiwuwe;

	if (nwa_put_be16(skb, TCA_MPWS_PWOTO, p->tcfm_pwoto))
		goto nwa_put_faiwuwe;

	tcf_tm_dump(&t, &m->tcf_tm);

	if (nwa_put_64bit(skb, TCA_MPWS_TM, sizeof(t), &t, TCA_MPWS_PAD))
		goto nwa_put_faiwuwe;

	spin_unwock_bh(&m->tcf_wock);

	wetuwn skb->wen;

nwa_put_faiwuwe:
	spin_unwock_bh(&m->tcf_wock);
	nwmsg_twim(skb, b);
	wetuwn -EMSGSIZE;
}

static int tcf_mpws_offwoad_act_setup(stwuct tc_action *act, void *entwy_data,
				      u32 *index_inc, boow bind,
				      stwuct netwink_ext_ack *extack)
{
	if (bind) {
		stwuct fwow_action_entwy *entwy = entwy_data;

		switch (tcf_mpws_action(act)) {
		case TCA_MPWS_ACT_PUSH:
			entwy->id = FWOW_ACTION_MPWS_PUSH;
			entwy->mpws_push.pwoto = tcf_mpws_pwoto(act);
			entwy->mpws_push.wabew = tcf_mpws_wabew(act);
			entwy->mpws_push.tc = tcf_mpws_tc(act);
			entwy->mpws_push.bos = tcf_mpws_bos(act);
			entwy->mpws_push.ttw = tcf_mpws_ttw(act);
			bweak;
		case TCA_MPWS_ACT_POP:
			entwy->id = FWOW_ACTION_MPWS_POP;
			entwy->mpws_pop.pwoto = tcf_mpws_pwoto(act);
			bweak;
		case TCA_MPWS_ACT_MODIFY:
			entwy->id = FWOW_ACTION_MPWS_MANGWE;
			entwy->mpws_mangwe.wabew = tcf_mpws_wabew(act);
			entwy->mpws_mangwe.tc = tcf_mpws_tc(act);
			entwy->mpws_mangwe.bos = tcf_mpws_bos(act);
			entwy->mpws_mangwe.ttw = tcf_mpws_ttw(act);
			bweak;
		case TCA_MPWS_ACT_DEC_TTW:
			NW_SET_EWW_MSG_MOD(extack, "Offwoad not suppowted when \"dec_ttw\" option is used");
			wetuwn -EOPNOTSUPP;
		case TCA_MPWS_ACT_MAC_PUSH:
			NW_SET_EWW_MSG_MOD(extack, "Offwoad not suppowted when \"mac_push\" option is used");
			wetuwn -EOPNOTSUPP;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted MPWS mode offwoad");
			wetuwn -EOPNOTSUPP;
		}
		*index_inc = 1;
	} ewse {
		stwuct fwow_offwoad_action *fw_action = entwy_data;

		switch (tcf_mpws_action(act)) {
		case TCA_MPWS_ACT_PUSH:
			fw_action->id = FWOW_ACTION_MPWS_PUSH;
			bweak;
		case TCA_MPWS_ACT_POP:
			fw_action->id = FWOW_ACTION_MPWS_POP;
			bweak;
		case TCA_MPWS_ACT_MODIFY:
			fw_action->id = FWOW_ACTION_MPWS_MANGWE;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

static stwuct tc_action_ops act_mpws_ops = {
	.kind		=	"mpws",
	.id		=	TCA_ID_MPWS,
	.ownew		=	THIS_MODUWE,
	.act		=	tcf_mpws_act,
	.dump		=	tcf_mpws_dump,
	.init		=	tcf_mpws_init,
	.cweanup	=	tcf_mpws_cweanup,
	.offwoad_act_setup =	tcf_mpws_offwoad_act_setup,
	.size		=	sizeof(stwuct tcf_mpws),
};

static __net_init int mpws_init_net(stwuct net *net)
{
	stwuct tc_action_net *tn = net_genewic(net, act_mpws_ops.net_id);

	wetuwn tc_action_net_init(net, tn, &act_mpws_ops);
}

static void __net_exit mpws_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_mpws_ops.net_id);
}

static stwuct pewnet_opewations mpws_net_ops = {
	.init = mpws_init_net,
	.exit_batch = mpws_exit_net,
	.id   = &act_mpws_ops.net_id,
	.size = sizeof(stwuct tc_action_net),
};

static int __init mpws_init_moduwe(void)
{
	wetuwn tcf_wegistew_action(&act_mpws_ops, &mpws_net_ops);
}

static void __exit mpws_cweanup_moduwe(void)
{
	tcf_unwegistew_action(&act_mpws_ops, &mpws_net_ops);
}

moduwe_init(mpws_init_moduwe);
moduwe_exit(mpws_cweanup_moduwe);

MODUWE_SOFTDEP("post: mpws_gso");
MODUWE_AUTHOW("Netwonome Systems <oss-dwivews@netwonome.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MPWS manipuwation actions");
