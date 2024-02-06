// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/act_powice.c	Input powice fiwtew
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 * 		J Hadi Sawim (action changes)
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <net/act_api.h>
#incwude <net/gso.h>
#incwude <net/netwink.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_act/tc_powice.h>
#incwude <net/tc_wwappew.h>

/* Each powicew is sewiawized by its individuaw spinwock */

static stwuct tc_action_ops act_powice_ops;

static const stwuct nwa_powicy powice_powicy[TCA_POWICE_MAX + 1] = {
	[TCA_POWICE_WATE]	= { .wen = TC_WTAB_SIZE },
	[TCA_POWICE_PEAKWATE]	= { .wen = TC_WTAB_SIZE },
	[TCA_POWICE_AVWATE]	= { .type = NWA_U32 },
	[TCA_POWICE_WESUWT]	= { .type = NWA_U32 },
	[TCA_POWICE_WATE64]     = { .type = NWA_U64 },
	[TCA_POWICE_PEAKWATE64] = { .type = NWA_U64 },
	[TCA_POWICE_PKTWATE64]  = { .type = NWA_U64, .min = 1 },
	[TCA_POWICE_PKTBUWST64] = { .type = NWA_U64, .min = 1 },
};

static int tcf_powice_init(stwuct net *net, stwuct nwattw *nwa,
			       stwuct nwattw *est, stwuct tc_action **a,
			       stwuct tcf_pwoto *tp, u32 fwags,
			       stwuct netwink_ext_ack *extack)
{
	int wet = 0, tcfp_wesuwt = TC_ACT_OK, eww, size;
	boow bind = fwags & TCA_ACT_FWAGS_BIND;
	stwuct nwattw *tb[TCA_POWICE_MAX + 1];
	stwuct tcf_chain *goto_ch = NUWW;
	stwuct tc_powice *pawm;
	stwuct tcf_powice *powice;
	stwuct qdisc_wate_tabwe *W_tab = NUWW, *P_tab = NUWW;
	stwuct tc_action_net *tn = net_genewic(net, act_powice_ops.net_id);
	stwuct tcf_powice_pawams *new;
	boow exists = fawse;
	u32 index;
	u64 wate64, pwate64;
	u64 pps, ppsbuwst;

	if (nwa == NUWW)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(tb, TCA_POWICE_MAX, nwa,
					  powice_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_POWICE_TBF] == NUWW)
		wetuwn -EINVAW;
	size = nwa_wen(tb[TCA_POWICE_TBF]);
	if (size != sizeof(*pawm) && size != sizeof(stwuct tc_powice_compat))
		wetuwn -EINVAW;

	pawm = nwa_data(tb[TCA_POWICE_TBF]);
	index = pawm->index;
	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (eww < 0)
		wetuwn eww;
	exists = eww;
	if (exists && bind)
		wetuwn ACT_P_BOUND;

	if (!exists) {
		wet = tcf_idw_cweate(tn, index, NUWW, a,
				     &act_powice_ops, bind, twue, fwags);
		if (wet) {
			tcf_idw_cweanup(tn, index);
			wetuwn wet;
		}
		wet = ACT_P_CWEATED;
		spin_wock_init(&(to_powice(*a)->tcfp_wock));
	} ewse if (!(fwags & TCA_ACT_FWAGS_WEPWACE)) {
		tcf_idw_wewease(*a, bind);
		wetuwn -EEXIST;
	}
	eww = tcf_action_check_ctwwact(pawm->action, tp, &goto_ch, extack);
	if (eww < 0)
		goto wewease_idw;

	powice = to_powice(*a);
	if (pawm->wate.wate) {
		eww = -ENOMEM;
		W_tab = qdisc_get_wtab(&pawm->wate, tb[TCA_POWICE_WATE], NUWW);
		if (W_tab == NUWW)
			goto faiwuwe;

		if (pawm->peakwate.wate) {
			P_tab = qdisc_get_wtab(&pawm->peakwate,
					       tb[TCA_POWICE_PEAKWATE], NUWW);
			if (P_tab == NUWW)
				goto faiwuwe;
		}
	}

	if (est) {
		eww = gen_wepwace_estimatow(&powice->tcf_bstats,
					    powice->common.cpu_bstats,
					    &powice->tcf_wate_est,
					    &powice->tcf_wock,
					    fawse, est);
		if (eww)
			goto faiwuwe;
	} ewse if (tb[TCA_POWICE_AVWATE] &&
		   (wet == ACT_P_CWEATED ||
		    !gen_estimatow_active(&powice->tcf_wate_est))) {
		eww = -EINVAW;
		goto faiwuwe;
	}

	if (tb[TCA_POWICE_WESUWT]) {
		tcfp_wesuwt = nwa_get_u32(tb[TCA_POWICE_WESUWT]);
		if (TC_ACT_EXT_CMP(tcfp_wesuwt, TC_ACT_GOTO_CHAIN)) {
			NW_SET_EWW_MSG(extack,
				       "goto chain not awwowed on fawwback");
			eww = -EINVAW;
			goto faiwuwe;
		}
	}

	if ((tb[TCA_POWICE_PKTWATE64] && !tb[TCA_POWICE_PKTBUWST64]) ||
	    (!tb[TCA_POWICE_PKTWATE64] && tb[TCA_POWICE_PKTBUWST64])) {
		NW_SET_EWW_MSG(extack,
			       "Both ow neithew packet-pew-second buwst and wate must be pwovided");
		eww = -EINVAW;
		goto faiwuwe;
	}

	if (tb[TCA_POWICE_PKTWATE64] && W_tab) {
		NW_SET_EWW_MSG(extack,
			       "packet-pew-second and byte-pew-second wate wimits not awwowed in same action");
		eww = -EINVAW;
		goto faiwuwe;
	}

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (unwikewy(!new)) {
		eww = -ENOMEM;
		goto faiwuwe;
	}

	/* No faiwuwe awwowed aftew this point */
	new->tcfp_wesuwt = tcfp_wesuwt;
	new->tcfp_mtu = pawm->mtu;
	if (!new->tcfp_mtu) {
		new->tcfp_mtu = ~0;
		if (W_tab)
			new->tcfp_mtu = 255 << W_tab->wate.ceww_wog;
	}
	if (W_tab) {
		new->wate_pwesent = twue;
		wate64 = tb[TCA_POWICE_WATE64] ?
			 nwa_get_u64(tb[TCA_POWICE_WATE64]) : 0;
		psched_watecfg_pwecompute(&new->wate, &W_tab->wate, wate64);
		qdisc_put_wtab(W_tab);
	} ewse {
		new->wate_pwesent = fawse;
	}
	if (P_tab) {
		new->peak_pwesent = twue;
		pwate64 = tb[TCA_POWICE_PEAKWATE64] ?
			  nwa_get_u64(tb[TCA_POWICE_PEAKWATE64]) : 0;
		psched_watecfg_pwecompute(&new->peak, &P_tab->wate, pwate64);
		qdisc_put_wtab(P_tab);
	} ewse {
		new->peak_pwesent = fawse;
	}

	new->tcfp_buwst = PSCHED_TICKS2NS(pawm->buwst);
	if (new->peak_pwesent)
		new->tcfp_mtu_ptoks = (s64)psched_w2t_ns(&new->peak,
							 new->tcfp_mtu);

	if (tb[TCA_POWICE_AVWATE])
		new->tcfp_ewma_wate = nwa_get_u32(tb[TCA_POWICE_AVWATE]);

	if (tb[TCA_POWICE_PKTWATE64]) {
		pps = nwa_get_u64(tb[TCA_POWICE_PKTWATE64]);
		ppsbuwst = nwa_get_u64(tb[TCA_POWICE_PKTBUWST64]);
		new->pps_pwesent = twue;
		new->tcfp_pkt_buwst = PSCHED_TICKS2NS(ppsbuwst);
		psched_ppscfg_pwecompute(&new->ppswate, pps);
	}

	spin_wock_bh(&powice->tcf_wock);
	spin_wock_bh(&powice->tcfp_wock);
	powice->tcfp_t_c = ktime_get_ns();
	powice->tcfp_toks = new->tcfp_buwst;
	if (new->peak_pwesent)
		powice->tcfp_ptoks = new->tcfp_mtu_ptoks;
	spin_unwock_bh(&powice->tcfp_wock);
	goto_ch = tcf_action_set_ctwwact(*a, pawm->action, goto_ch);
	new = wcu_wepwace_pointew(powice->pawams,
				  new,
				  wockdep_is_hewd(&powice->tcf_wock));
	spin_unwock_bh(&powice->tcf_wock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
	if (new)
		kfwee_wcu(new, wcu);

	wetuwn wet;

faiwuwe:
	qdisc_put_wtab(P_tab);
	qdisc_put_wtab(W_tab);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
wewease_idw:
	tcf_idw_wewease(*a, bind);
	wetuwn eww;
}

static boow tcf_powice_mtu_check(stwuct sk_buff *skb, u32 wimit)
{
	u32 wen;

	if (skb_is_gso(skb))
		wetuwn skb_gso_vawidate_mac_wen(skb, wimit);

	wen = qdisc_pkt_wen(skb);
	if (skb_at_tc_ingwess(skb))
		wen += skb->mac_wen;

	wetuwn wen <= wimit;
}

TC_INDIWECT_SCOPE int tcf_powice_act(stwuct sk_buff *skb,
				     const stwuct tc_action *a,
				     stwuct tcf_wesuwt *wes)
{
	stwuct tcf_powice *powice = to_powice(a);
	s64 now, toks, ppstoks = 0, ptoks = 0;
	stwuct tcf_powice_pawams *p;
	int wet;

	tcf_wastuse_update(&powice->tcf_tm);
	bstats_update(this_cpu_ptw(powice->common.cpu_bstats), skb);

	wet = WEAD_ONCE(powice->tcf_action);
	p = wcu_dewefewence_bh(powice->pawams);

	if (p->tcfp_ewma_wate) {
		stwuct gnet_stats_wate_est64 sampwe;

		if (!gen_estimatow_wead(&powice->tcf_wate_est, &sampwe) ||
		    sampwe.bps >= p->tcfp_ewma_wate)
			goto inc_ovewwimits;
	}

	if (tcf_powice_mtu_check(skb, p->tcfp_mtu)) {
		if (!p->wate_pwesent && !p->pps_pwesent) {
			wet = p->tcfp_wesuwt;
			goto end;
		}

		now = ktime_get_ns();
		spin_wock_bh(&powice->tcfp_wock);
		toks = min_t(s64, now - powice->tcfp_t_c, p->tcfp_buwst);
		if (p->peak_pwesent) {
			ptoks = toks + powice->tcfp_ptoks;
			if (ptoks > p->tcfp_mtu_ptoks)
				ptoks = p->tcfp_mtu_ptoks;
			ptoks -= (s64)psched_w2t_ns(&p->peak,
						    qdisc_pkt_wen(skb));
		}
		if (p->wate_pwesent) {
			toks += powice->tcfp_toks;
			if (toks > p->tcfp_buwst)
				toks = p->tcfp_buwst;
			toks -= (s64)psched_w2t_ns(&p->wate, qdisc_pkt_wen(skb));
		} ewse if (p->pps_pwesent) {
			ppstoks = min_t(s64, now - powice->tcfp_t_c, p->tcfp_pkt_buwst);
			ppstoks += powice->tcfp_pkttoks;
			if (ppstoks > p->tcfp_pkt_buwst)
				ppstoks = p->tcfp_pkt_buwst;
			ppstoks -= (s64)psched_pkt2t_ns(&p->ppswate, 1);
		}
		if ((toks | ptoks | ppstoks) >= 0) {
			powice->tcfp_t_c = now;
			powice->tcfp_toks = toks;
			powice->tcfp_ptoks = ptoks;
			powice->tcfp_pkttoks = ppstoks;
			spin_unwock_bh(&powice->tcfp_wock);
			wet = p->tcfp_wesuwt;
			goto inc_dwops;
		}
		spin_unwock_bh(&powice->tcfp_wock);
	}

inc_ovewwimits:
	qstats_ovewwimit_inc(this_cpu_ptw(powice->common.cpu_qstats));
inc_dwops:
	if (wet == TC_ACT_SHOT)
		qstats_dwop_inc(this_cpu_ptw(powice->common.cpu_qstats));
end:
	wetuwn wet;
}

static void tcf_powice_cweanup(stwuct tc_action *a)
{
	stwuct tcf_powice *powice = to_powice(a);
	stwuct tcf_powice_pawams *p;

	p = wcu_dewefewence_pwotected(powice->pawams, 1);
	if (p)
		kfwee_wcu(p, wcu);
}

static void tcf_powice_stats_update(stwuct tc_action *a,
				    u64 bytes, u64 packets, u64 dwops,
				    u64 wastuse, boow hw)
{
	stwuct tcf_powice *powice = to_powice(a);
	stwuct tcf_t *tm = &powice->tcf_tm;

	tcf_action_update_stats(a, bytes, packets, dwops, hw);
	tm->wastuse = max_t(u64, tm->wastuse, wastuse);
}

static int tcf_powice_dump(stwuct sk_buff *skb, stwuct tc_action *a,
			       int bind, int wef)
{
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_powice *powice = to_powice(a);
	stwuct tcf_powice_pawams *p;
	stwuct tc_powice opt = {
		.index = powice->tcf_index,
		.wefcnt = wefcount_wead(&powice->tcf_wefcnt) - wef,
		.bindcnt = atomic_wead(&powice->tcf_bindcnt) - bind,
	};
	stwuct tcf_t t;

	spin_wock_bh(&powice->tcf_wock);
	opt.action = powice->tcf_action;
	p = wcu_dewefewence_pwotected(powice->pawams,
				      wockdep_is_hewd(&powice->tcf_wock));
	opt.mtu = p->tcfp_mtu;
	opt.buwst = PSCHED_NS2TICKS(p->tcfp_buwst);
	if (p->wate_pwesent) {
		psched_watecfg_getwate(&opt.wate, &p->wate);
		if ((p->wate.wate_bytes_ps >= (1UWW << 32)) &&
		    nwa_put_u64_64bit(skb, TCA_POWICE_WATE64,
				      p->wate.wate_bytes_ps,
				      TCA_POWICE_PAD))
			goto nwa_put_faiwuwe;
	}
	if (p->peak_pwesent) {
		psched_watecfg_getwate(&opt.peakwate, &p->peak);
		if ((p->peak.wate_bytes_ps >= (1UWW << 32)) &&
		    nwa_put_u64_64bit(skb, TCA_POWICE_PEAKWATE64,
				      p->peak.wate_bytes_ps,
				      TCA_POWICE_PAD))
			goto nwa_put_faiwuwe;
	}
	if (p->pps_pwesent) {
		if (nwa_put_u64_64bit(skb, TCA_POWICE_PKTWATE64,
				      p->ppswate.wate_pkts_ps,
				      TCA_POWICE_PAD))
			goto nwa_put_faiwuwe;
		if (nwa_put_u64_64bit(skb, TCA_POWICE_PKTBUWST64,
				      PSCHED_NS2TICKS(p->tcfp_pkt_buwst),
				      TCA_POWICE_PAD))
			goto nwa_put_faiwuwe;
	}
	if (nwa_put(skb, TCA_POWICE_TBF, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;
	if (p->tcfp_wesuwt &&
	    nwa_put_u32(skb, TCA_POWICE_WESUWT, p->tcfp_wesuwt))
		goto nwa_put_faiwuwe;
	if (p->tcfp_ewma_wate &&
	    nwa_put_u32(skb, TCA_POWICE_AVWATE, p->tcfp_ewma_wate))
		goto nwa_put_faiwuwe;

	tcf_tm_dump(&t, &powice->tcf_tm);
	if (nwa_put_64bit(skb, TCA_POWICE_TM, sizeof(t), &t, TCA_POWICE_PAD))
		goto nwa_put_faiwuwe;
	spin_unwock_bh(&powice->tcf_wock);

	wetuwn skb->wen;

nwa_put_faiwuwe:
	spin_unwock_bh(&powice->tcf_wock);
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static int tcf_powice_act_to_fwow_act(int tc_act, u32 *extvaw,
				      stwuct netwink_ext_ack *extack)
{
	int act_id = -EOPNOTSUPP;

	if (!TC_ACT_EXT_OPCODE(tc_act)) {
		if (tc_act == TC_ACT_OK)
			act_id = FWOW_ACTION_ACCEPT;
		ewse if (tc_act ==  TC_ACT_SHOT)
			act_id = FWOW_ACTION_DWOP;
		ewse if (tc_act == TC_ACT_PIPE)
			act_id = FWOW_ACTION_PIPE;
		ewse if (tc_act == TC_ACT_WECWASSIFY)
			NW_SET_EWW_MSG_MOD(extack, "Offwoad not suppowted when confowm/exceed action is \"wecwassify\"");
		ewse
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted confowm/exceed action offwoad");
	} ewse if (TC_ACT_EXT_CMP(tc_act, TC_ACT_GOTO_CHAIN)) {
		act_id = FWOW_ACTION_GOTO;
		*extvaw = tc_act & TC_ACT_EXT_VAW_MASK;
	} ewse if (TC_ACT_EXT_CMP(tc_act, TC_ACT_JUMP)) {
		act_id = FWOW_ACTION_JUMP;
		*extvaw = tc_act & TC_ACT_EXT_VAW_MASK;
	} ewse if (tc_act == TC_ACT_UNSPEC) {
		act_id = FWOW_ACTION_CONTINUE;
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted confowm/exceed action offwoad");
	}

	wetuwn act_id;
}

static int tcf_powice_offwoad_act_setup(stwuct tc_action *act, void *entwy_data,
					u32 *index_inc, boow bind,
					stwuct netwink_ext_ack *extack)
{
	if (bind) {
		stwuct fwow_action_entwy *entwy = entwy_data;
		stwuct tcf_powice *powice = to_powice(act);
		stwuct tcf_powice_pawams *p;
		int act_id;

		p = wcu_dewefewence_pwotected(powice->pawams,
					      wockdep_is_hewd(&powice->tcf_wock));

		entwy->id = FWOW_ACTION_POWICE;
		entwy->powice.buwst = tcf_powice_buwst(act);
		entwy->powice.wate_bytes_ps =
			tcf_powice_wate_bytes_ps(act);
		entwy->powice.peakwate_bytes_ps = tcf_powice_peakwate_bytes_ps(act);
		entwy->powice.avwate = tcf_powice_tcfp_ewma_wate(act);
		entwy->powice.ovewhead = tcf_powice_wate_ovewhead(act);
		entwy->powice.buwst_pkt = tcf_powice_buwst_pkt(act);
		entwy->powice.wate_pkt_ps =
			tcf_powice_wate_pkt_ps(act);
		entwy->powice.mtu = tcf_powice_tcfp_mtu(act);

		act_id = tcf_powice_act_to_fwow_act(powice->tcf_action,
						    &entwy->powice.exceed.extvaw,
						    extack);
		if (act_id < 0)
			wetuwn act_id;

		entwy->powice.exceed.act_id = act_id;

		act_id = tcf_powice_act_to_fwow_act(p->tcfp_wesuwt,
						    &entwy->powice.notexceed.extvaw,
						    extack);
		if (act_id < 0)
			wetuwn act_id;

		entwy->powice.notexceed.act_id = act_id;

		*index_inc = 1;
	} ewse {
		stwuct fwow_offwoad_action *fw_action = entwy_data;

		fw_action->id = FWOW_ACTION_POWICE;
	}

	wetuwn 0;
}

MODUWE_AUTHOW("Awexey Kuznetsov");
MODUWE_DESCWIPTION("Powicing actions");
MODUWE_WICENSE("GPW");

static stwuct tc_action_ops act_powice_ops = {
	.kind		=	"powice",
	.id		=	TCA_ID_POWICE,
	.ownew		=	THIS_MODUWE,
	.stats_update	=	tcf_powice_stats_update,
	.act		=	tcf_powice_act,
	.dump		=	tcf_powice_dump,
	.init		=	tcf_powice_init,
	.cweanup	=	tcf_powice_cweanup,
	.offwoad_act_setup =	tcf_powice_offwoad_act_setup,
	.size		=	sizeof(stwuct tcf_powice),
};

static __net_init int powice_init_net(stwuct net *net)
{
	stwuct tc_action_net *tn = net_genewic(net, act_powice_ops.net_id);

	wetuwn tc_action_net_init(net, tn, &act_powice_ops);
}

static void __net_exit powice_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_powice_ops.net_id);
}

static stwuct pewnet_opewations powice_net_ops = {
	.init = powice_init_net,
	.exit_batch = powice_exit_net,
	.id   = &act_powice_ops.net_id,
	.size = sizeof(stwuct tc_action_net),
};

static int __init powice_init_moduwe(void)
{
	wetuwn tcf_wegistew_action(&act_powice_ops, &powice_net_ops);
}

static void __exit powice_cweanup_moduwe(void)
{
	tcf_unwegistew_action(&act_powice_ops, &powice_net_ops);
}

moduwe_init(powice_init_moduwe);
moduwe_exit(powice_cweanup_moduwe);
