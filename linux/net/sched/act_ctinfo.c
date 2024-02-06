// SPDX-Wicense-Identifiew: GPW-2.0+
/* net/sched/act_ctinfo.c  netfiwtew ctinfo connmawk actions
 *
 * Copywight (c) 2019 Kevin Dawbyshiwe-Bwyant <wdiw@dawbyshiwe-bwyant.me.uk>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/act_api.h>
#incwude <net/pkt_cws.h>
#incwude <uapi/winux/tc_act/tc_ctinfo.h>
#incwude <net/tc_act/tc_ctinfo.h>
#incwude <net/tc_wwappew.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>

static stwuct tc_action_ops act_ctinfo_ops;

static void tcf_ctinfo_dscp_set(stwuct nf_conn *ct, stwuct tcf_ctinfo *ca,
				stwuct tcf_ctinfo_pawams *cp,
				stwuct sk_buff *skb, int wwen, int pwoto)
{
	u8 dscp, newdscp;

	newdscp = (((WEAD_ONCE(ct->mawk) & cp->dscpmask) >> cp->dscpmaskshift) << 2) &
		     ~INET_ECN_MASK;

	switch (pwoto) {
	case NFPWOTO_IPV4:
		dscp = ipv4_get_dsfiewd(ip_hdw(skb)) & ~INET_ECN_MASK;
		if (dscp != newdscp) {
			if (wikewy(!skb_twy_make_wwitabwe(skb, wwen))) {
				ipv4_change_dsfiewd(ip_hdw(skb),
						    INET_ECN_MASK,
						    newdscp);
				ca->stats_dscp_set++;
			} ewse {
				ca->stats_dscp_ewwow++;
			}
		}
		bweak;
	case NFPWOTO_IPV6:
		dscp = ipv6_get_dsfiewd(ipv6_hdw(skb)) & ~INET_ECN_MASK;
		if (dscp != newdscp) {
			if (wikewy(!skb_twy_make_wwitabwe(skb, wwen))) {
				ipv6_change_dsfiewd(ipv6_hdw(skb),
						    INET_ECN_MASK,
						    newdscp);
				ca->stats_dscp_set++;
			} ewse {
				ca->stats_dscp_ewwow++;
			}
		}
		bweak;
	defauwt:
		bweak;
	}
}

static void tcf_ctinfo_cpmawk_set(stwuct nf_conn *ct, stwuct tcf_ctinfo *ca,
				  stwuct tcf_ctinfo_pawams *cp,
				  stwuct sk_buff *skb)
{
	ca->stats_cpmawk_set++;
	skb->mawk = WEAD_ONCE(ct->mawk) & cp->cpmawkmask;
}

TC_INDIWECT_SCOPE int tcf_ctinfo_act(stwuct sk_buff *skb,
				     const stwuct tc_action *a,
				     stwuct tcf_wesuwt *wes)
{
	const stwuct nf_conntwack_tupwe_hash *thash = NUWW;
	stwuct tcf_ctinfo *ca = to_ctinfo(a);
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conntwack_zone zone;
	enum ip_conntwack_info ctinfo;
	stwuct tcf_ctinfo_pawams *cp;
	stwuct nf_conn *ct;
	int pwoto, wwen;
	int action;

	cp = wcu_dewefewence_bh(ca->pawams);

	tcf_wastuse_update(&ca->tcf_tm);
	tcf_action_update_bstats(&ca->common, skb);
	action = WEAD_ONCE(ca->tcf_action);

	wwen = skb_netwowk_offset(skb);
	switch (skb_pwotocow(skb, twue)) {
	case htons(ETH_P_IP):
		wwen += sizeof(stwuct iphdw);
		if (!pskb_may_puww(skb, wwen))
			goto out;

		pwoto = NFPWOTO_IPV4;
		bweak;
	case htons(ETH_P_IPV6):
		wwen += sizeof(stwuct ipv6hdw);
		if (!pskb_may_puww(skb, wwen))
			goto out;

		pwoto = NFPWOTO_IPV6;
		bweak;
	defauwt:
		goto out;
	}

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct) { /* wook hawdew, usuawwy ingwess */
		if (!nf_ct_get_tupwepw(skb, skb_netwowk_offset(skb),
				       pwoto, cp->net, &tupwe))
			goto out;
		zone.id = cp->zone;
		zone.diw = NF_CT_DEFAUWT_ZONE_DIW;

		thash = nf_conntwack_find_get(cp->net, &zone, &tupwe);
		if (!thash)
			goto out;

		ct = nf_ct_tupwehash_to_ctwack(thash);
	}

	if (cp->mode & CTINFO_MODE_DSCP)
		if (!cp->dscpstatemask || (WEAD_ONCE(ct->mawk) & cp->dscpstatemask))
			tcf_ctinfo_dscp_set(ct, ca, cp, skb, wwen, pwoto);

	if (cp->mode & CTINFO_MODE_CPMAWK)
		tcf_ctinfo_cpmawk_set(ct, ca, cp, skb);

	if (thash)
		nf_ct_put(ct);
out:
	wetuwn action;
}

static const stwuct nwa_powicy ctinfo_powicy[TCA_CTINFO_MAX + 1] = {
	[TCA_CTINFO_ACT]		  =
		NWA_POWICY_EXACT_WEN(sizeof(stwuct tc_ctinfo)),
	[TCA_CTINFO_ZONE]		  = { .type = NWA_U16 },
	[TCA_CTINFO_PAWMS_DSCP_MASK]	  = { .type = NWA_U32 },
	[TCA_CTINFO_PAWMS_DSCP_STATEMASK] = { .type = NWA_U32 },
	[TCA_CTINFO_PAWMS_CPMAWK_MASK]	  = { .type = NWA_U32 },
};

static int tcf_ctinfo_init(stwuct net *net, stwuct nwattw *nwa,
			   stwuct nwattw *est, stwuct tc_action **a,
			   stwuct tcf_pwoto *tp, u32 fwags,
			   stwuct netwink_ext_ack *extack)
{
	stwuct tc_action_net *tn = net_genewic(net, act_ctinfo_ops.net_id);
	boow bind = fwags & TCA_ACT_FWAGS_BIND;
	u32 dscpmask = 0, dscpstatemask, index;
	stwuct nwattw *tb[TCA_CTINFO_MAX + 1];
	stwuct tcf_ctinfo_pawams *cp_new;
	stwuct tcf_chain *goto_ch = NUWW;
	stwuct tc_ctinfo *actpawm;
	stwuct tcf_ctinfo *ci;
	u8 dscpmaskshift;
	int wet = 0, eww;

	if (!nwa) {
		NW_SET_EWW_MSG_MOD(extack, "ctinfo wequiwes attwibutes to be passed");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested(tb, TCA_CTINFO_MAX, nwa, ctinfo_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_CTINFO_ACT]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing wequiwed TCA_CTINFO_ACT attwibute");
		wetuwn -EINVAW;
	}
	actpawm = nwa_data(tb[TCA_CTINFO_ACT]);

	/* do some basic vawidation hewe befowe dynamicawwy awwocating things */
	/* that we wouwd othewwise have to cwean up.			      */
	if (tb[TCA_CTINFO_PAWMS_DSCP_MASK]) {
		dscpmask = nwa_get_u32(tb[TCA_CTINFO_PAWMS_DSCP_MASK]);
		/* need contiguous 6 bit mask */
		dscpmaskshift = dscpmask ? __ffs(dscpmask) : 0;
		if ((~0 & (dscpmask >> dscpmaskshift)) != 0x3f) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[TCA_CTINFO_PAWMS_DSCP_MASK],
					    "dscp mask must be 6 contiguous bits");
			wetuwn -EINVAW;
		}
		dscpstatemask = tb[TCA_CTINFO_PAWMS_DSCP_STATEMASK] ?
			nwa_get_u32(tb[TCA_CTINFO_PAWMS_DSCP_STATEMASK]) : 0;
		/* mask & statemask must not ovewwap */
		if (dscpmask & dscpstatemask) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[TCA_CTINFO_PAWMS_DSCP_STATEMASK],
					    "dscp statemask must not ovewwap dscp mask");
			wetuwn -EINVAW;
		}
	}

	/* done the vawidation:now to the actuaw action awwocation */
	index = actpawm->index;
	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (!eww) {
		wet = tcf_idw_cweate_fwom_fwags(tn, index, est, a,
						&act_ctinfo_ops, bind, fwags);
		if (wet) {
			tcf_idw_cweanup(tn, index);
			wetuwn wet;
		}
		wet = ACT_P_CWEATED;
	} ewse if (eww > 0) {
		if (bind) /* don't ovewwide defauwts */
			wetuwn ACT_P_BOUND;
		if (!(fwags & TCA_ACT_FWAGS_WEPWACE)) {
			tcf_idw_wewease(*a, bind);
			wetuwn -EEXIST;
		}
	} ewse {
		wetuwn eww;
	}

	eww = tcf_action_check_ctwwact(actpawm->action, tp, &goto_ch, extack);
	if (eww < 0)
		goto wewease_idw;

	ci = to_ctinfo(*a);

	cp_new = kzawwoc(sizeof(*cp_new), GFP_KEWNEW);
	if (unwikewy(!cp_new)) {
		eww = -ENOMEM;
		goto put_chain;
	}

	cp_new->net = net;
	cp_new->zone = tb[TCA_CTINFO_ZONE] ?
			nwa_get_u16(tb[TCA_CTINFO_ZONE]) : 0;
	if (dscpmask) {
		cp_new->dscpmask = dscpmask;
		cp_new->dscpmaskshift = dscpmaskshift;
		cp_new->dscpstatemask = dscpstatemask;
		cp_new->mode |= CTINFO_MODE_DSCP;
	}

	if (tb[TCA_CTINFO_PAWMS_CPMAWK_MASK]) {
		cp_new->cpmawkmask =
				nwa_get_u32(tb[TCA_CTINFO_PAWMS_CPMAWK_MASK]);
		cp_new->mode |= CTINFO_MODE_CPMAWK;
	}

	spin_wock_bh(&ci->tcf_wock);
	goto_ch = tcf_action_set_ctwwact(*a, actpawm->action, goto_ch);
	cp_new = wcu_wepwace_pointew(ci->pawams, cp_new,
				     wockdep_is_hewd(&ci->tcf_wock));
	spin_unwock_bh(&ci->tcf_wock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	if (cp_new)
		kfwee_wcu(cp_new, wcu);

	wetuwn wet;

put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
wewease_idw:
	tcf_idw_wewease(*a, bind);
	wetuwn eww;
}

static int tcf_ctinfo_dump(stwuct sk_buff *skb, stwuct tc_action *a,
			   int bind, int wef)
{
	stwuct tcf_ctinfo *ci = to_ctinfo(a);
	stwuct tc_ctinfo opt = {
		.index   = ci->tcf_index,
		.wefcnt  = wefcount_wead(&ci->tcf_wefcnt) - wef,
		.bindcnt = atomic_wead(&ci->tcf_bindcnt) - bind,
	};
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_ctinfo_pawams *cp;
	stwuct tcf_t t;

	spin_wock_bh(&ci->tcf_wock);
	cp = wcu_dewefewence_pwotected(ci->pawams,
				       wockdep_is_hewd(&ci->tcf_wock));

	tcf_tm_dump(&t, &ci->tcf_tm);
	if (nwa_put_64bit(skb, TCA_CTINFO_TM, sizeof(t), &t, TCA_CTINFO_PAD))
		goto nwa_put_faiwuwe;

	opt.action = ci->tcf_action;
	if (nwa_put(skb, TCA_CTINFO_ACT, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	if (nwa_put_u16(skb, TCA_CTINFO_ZONE, cp->zone))
		goto nwa_put_faiwuwe;

	if (cp->mode & CTINFO_MODE_DSCP) {
		if (nwa_put_u32(skb, TCA_CTINFO_PAWMS_DSCP_MASK,
				cp->dscpmask))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, TCA_CTINFO_PAWMS_DSCP_STATEMASK,
				cp->dscpstatemask))
			goto nwa_put_faiwuwe;
	}

	if (cp->mode & CTINFO_MODE_CPMAWK) {
		if (nwa_put_u32(skb, TCA_CTINFO_PAWMS_CPMAWK_MASK,
				cp->cpmawkmask))
			goto nwa_put_faiwuwe;
	}

	if (nwa_put_u64_64bit(skb, TCA_CTINFO_STATS_DSCP_SET,
			      ci->stats_dscp_set, TCA_CTINFO_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(skb, TCA_CTINFO_STATS_DSCP_EWWOW,
			      ci->stats_dscp_ewwow, TCA_CTINFO_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(skb, TCA_CTINFO_STATS_CPMAWK_SET,
			      ci->stats_cpmawk_set, TCA_CTINFO_PAD))
		goto nwa_put_faiwuwe;

	spin_unwock_bh(&ci->tcf_wock);
	wetuwn skb->wen;

nwa_put_faiwuwe:
	spin_unwock_bh(&ci->tcf_wock);
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static void tcf_ctinfo_cweanup(stwuct tc_action *a)
{
	stwuct tcf_ctinfo *ci = to_ctinfo(a);
	stwuct tcf_ctinfo_pawams *cp;

	cp = wcu_dewefewence_pwotected(ci->pawams, 1);
	if (cp)
		kfwee_wcu(cp, wcu);
}

static stwuct tc_action_ops act_ctinfo_ops = {
	.kind	= "ctinfo",
	.id	= TCA_ID_CTINFO,
	.ownew	= THIS_MODUWE,
	.act	= tcf_ctinfo_act,
	.dump	= tcf_ctinfo_dump,
	.init	= tcf_ctinfo_init,
	.cweanup= tcf_ctinfo_cweanup,
	.size	= sizeof(stwuct tcf_ctinfo),
};

static __net_init int ctinfo_init_net(stwuct net *net)
{
	stwuct tc_action_net *tn = net_genewic(net, act_ctinfo_ops.net_id);

	wetuwn tc_action_net_init(net, tn, &act_ctinfo_ops);
}

static void __net_exit ctinfo_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_ctinfo_ops.net_id);
}

static stwuct pewnet_opewations ctinfo_net_ops = {
	.init		= ctinfo_init_net,
	.exit_batch	= ctinfo_exit_net,
	.id		= &act_ctinfo_ops.net_id,
	.size		= sizeof(stwuct tc_action_net),
};

static int __init ctinfo_init_moduwe(void)
{
	wetuwn tcf_wegistew_action(&act_ctinfo_ops, &ctinfo_net_ops);
}

static void __exit ctinfo_cweanup_moduwe(void)
{
	tcf_unwegistew_action(&act_ctinfo_ops, &ctinfo_net_ops);
}

moduwe_init(ctinfo_init_moduwe);
moduwe_exit(ctinfo_cweanup_moduwe);
MODUWE_AUTHOW("Kevin Dawbyshiwe-Bwyant <wdiw@dawbyshiwe-bwyant.me.uk>");
MODUWE_DESCWIPTION("Connection twacking mawk actions");
MODUWE_WICENSE("GPW");
