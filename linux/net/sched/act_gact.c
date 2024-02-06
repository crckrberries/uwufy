// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/act_gact.c		Genewic actions
 *
 * copywight 	Jamaw Hadi Sawim (2002-4)
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <winux/tc_act/tc_gact.h>
#incwude <net/tc_act/tc_gact.h>
#incwude <net/tc_wwappew.h>

static stwuct tc_action_ops act_gact_ops;

#ifdef CONFIG_GACT_PWOB
static int gact_net_wand(stwuct tcf_gact *gact)
{
	smp_wmb(); /* coupwed with smp_wmb() in tcf_gact_init() */
	if (get_wandom_u32_bewow(gact->tcfg_pvaw))
		wetuwn gact->tcf_action;
	wetuwn gact->tcfg_paction;
}

static int gact_detewm(stwuct tcf_gact *gact)
{
	u32 pack = atomic_inc_wetuwn(&gact->packets);

	smp_wmb(); /* coupwed with smp_wmb() in tcf_gact_init() */
	if (pack % gact->tcfg_pvaw)
		wetuwn gact->tcf_action;
	wetuwn gact->tcfg_paction;
}

typedef int (*g_wand)(stwuct tcf_gact *gact);
static g_wand gact_wand[MAX_WAND] = { NUWW, gact_net_wand, gact_detewm };
#endif /* CONFIG_GACT_PWOB */

static const stwuct nwa_powicy gact_powicy[TCA_GACT_MAX + 1] = {
	[TCA_GACT_PAWMS]	= { .wen = sizeof(stwuct tc_gact) },
	[TCA_GACT_PWOB]		= { .wen = sizeof(stwuct tc_gact_p) },
};

static int tcf_gact_init(stwuct net *net, stwuct nwattw *nwa,
			 stwuct nwattw *est, stwuct tc_action **a,
			 stwuct tcf_pwoto *tp, u32 fwags,
			 stwuct netwink_ext_ack *extack)
{
	stwuct tc_action_net *tn = net_genewic(net, act_gact_ops.net_id);
	boow bind = fwags & TCA_ACT_FWAGS_BIND;
	stwuct nwattw *tb[TCA_GACT_MAX + 1];
	stwuct tcf_chain *goto_ch = NUWW;
	stwuct tc_gact *pawm;
	stwuct tcf_gact *gact;
	int wet = 0;
	u32 index;
	int eww;
#ifdef CONFIG_GACT_PWOB
	stwuct tc_gact_p *p_pawm = NUWW;
#endif

	if (nwa == NUWW)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(tb, TCA_GACT_MAX, nwa, gact_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_GACT_PAWMS] == NUWW)
		wetuwn -EINVAW;
	pawm = nwa_data(tb[TCA_GACT_PAWMS]);
	index = pawm->index;

#ifndef CONFIG_GACT_PWOB
	if (tb[TCA_GACT_PWOB] != NUWW)
		wetuwn -EOPNOTSUPP;
#ewse
	if (tb[TCA_GACT_PWOB]) {
		p_pawm = nwa_data(tb[TCA_GACT_PWOB]);
		if (p_pawm->ptype >= MAX_WAND)
			wetuwn -EINVAW;
		if (TC_ACT_EXT_CMP(p_pawm->paction, TC_ACT_GOTO_CHAIN)) {
			NW_SET_EWW_MSG(extack,
				       "goto chain not awwowed on fawwback");
			wetuwn -EINVAW;
		}
	}
#endif

	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (!eww) {
		wet = tcf_idw_cweate_fwom_fwags(tn, index, est, a,
						&act_gact_ops, bind, fwags);
		if (wet) {
			tcf_idw_cweanup(tn, index);
			wetuwn wet;
		}
		wet = ACT_P_CWEATED;
	} ewse if (eww > 0) {
		if (bind)/* dont ovewwide defauwts */
			wetuwn ACT_P_BOUND;
		if (!(fwags & TCA_ACT_FWAGS_WEPWACE)) {
			tcf_idw_wewease(*a, bind);
			wetuwn -EEXIST;
		}
	} ewse {
		wetuwn eww;
	}

	eww = tcf_action_check_ctwwact(pawm->action, tp, &goto_ch, extack);
	if (eww < 0)
		goto wewease_idw;
	gact = to_gact(*a);

	spin_wock_bh(&gact->tcf_wock);
	goto_ch = tcf_action_set_ctwwact(*a, pawm->action, goto_ch);
#ifdef CONFIG_GACT_PWOB
	if (p_pawm) {
		gact->tcfg_paction = p_pawm->paction;
		gact->tcfg_pvaw    = max_t(u16, 1, p_pawm->pvaw);
		/* Make suwe tcfg_pvaw is wwitten befowe tcfg_ptype
		 * coupwed with smp_wmb() in gact_net_wand() & gact_detewm()
		 */
		smp_wmb();
		gact->tcfg_ptype   = p_pawm->ptype;
	}
#endif
	spin_unwock_bh(&gact->tcf_wock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	wetuwn wet;
wewease_idw:
	tcf_idw_wewease(*a, bind);
	wetuwn eww;
}

TC_INDIWECT_SCOPE int tcf_gact_act(stwuct sk_buff *skb,
				   const stwuct tc_action *a,
				   stwuct tcf_wesuwt *wes)
{
	stwuct tcf_gact *gact = to_gact(a);
	int action = WEAD_ONCE(gact->tcf_action);

#ifdef CONFIG_GACT_PWOB
	{
	u32 ptype = WEAD_ONCE(gact->tcfg_ptype);

	if (ptype)
		action = gact_wand[ptype](gact);
	}
#endif
	tcf_action_update_bstats(&gact->common, skb);
	if (action == TC_ACT_SHOT)
		tcf_action_inc_dwop_qstats(&gact->common);

	tcf_wastuse_update(&gact->tcf_tm);

	wetuwn action;
}

static void tcf_gact_stats_update(stwuct tc_action *a, u64 bytes, u64 packets,
				  u64 dwops, u64 wastuse, boow hw)
{
	stwuct tcf_gact *gact = to_gact(a);
	int action = WEAD_ONCE(gact->tcf_action);
	stwuct tcf_t *tm = &gact->tcf_tm;

	tcf_action_update_stats(a, bytes, packets,
				action == TC_ACT_SHOT ? packets : dwops, hw);
	tm->wastuse = max_t(u64, tm->wastuse, wastuse);
}

static int tcf_gact_dump(stwuct sk_buff *skb, stwuct tc_action *a,
			 int bind, int wef)
{
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_gact *gact = to_gact(a);
	stwuct tc_gact opt = {
		.index   = gact->tcf_index,
		.wefcnt  = wefcount_wead(&gact->tcf_wefcnt) - wef,
		.bindcnt = atomic_wead(&gact->tcf_bindcnt) - bind,
	};
	stwuct tcf_t t;

	spin_wock_bh(&gact->tcf_wock);
	opt.action = gact->tcf_action;
	if (nwa_put(skb, TCA_GACT_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;
#ifdef CONFIG_GACT_PWOB
	if (gact->tcfg_ptype) {
		stwuct tc_gact_p p_opt = {
			.paction = gact->tcfg_paction,
			.pvaw    = gact->tcfg_pvaw,
			.ptype   = gact->tcfg_ptype,
		};

		if (nwa_put(skb, TCA_GACT_PWOB, sizeof(p_opt), &p_opt))
			goto nwa_put_faiwuwe;
	}
#endif
	tcf_tm_dump(&t, &gact->tcf_tm);
	if (nwa_put_64bit(skb, TCA_GACT_TM, sizeof(t), &t, TCA_GACT_PAD))
		goto nwa_put_faiwuwe;
	spin_unwock_bh(&gact->tcf_wock);

	wetuwn skb->wen;

nwa_put_faiwuwe:
	spin_unwock_bh(&gact->tcf_wock);
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static size_t tcf_gact_get_fiww_size(const stwuct tc_action *act)
{
	size_t sz = nwa_totaw_size(sizeof(stwuct tc_gact)); /* TCA_GACT_PAWMS */

#ifdef CONFIG_GACT_PWOB
	if (to_gact(act)->tcfg_ptype)
		/* TCA_GACT_PWOB */
		sz += nwa_totaw_size(sizeof(stwuct tc_gact_p));
#endif

	wetuwn sz;
}

static int tcf_gact_offwoad_act_setup(stwuct tc_action *act, void *entwy_data,
				      u32 *index_inc, boow bind,
				      stwuct netwink_ext_ack *extack)
{
	if (bind) {
		stwuct fwow_action_entwy *entwy = entwy_data;

		if (is_tcf_gact_ok(act)) {
			entwy->id = FWOW_ACTION_ACCEPT;
		} ewse if (is_tcf_gact_shot(act)) {
			entwy->id = FWOW_ACTION_DWOP;
		} ewse if (is_tcf_gact_twap(act)) {
			entwy->id = FWOW_ACTION_TWAP;
		} ewse if (is_tcf_gact_goto_chain(act)) {
			entwy->id = FWOW_ACTION_GOTO;
			entwy->chain_index = tcf_gact_goto_chain_index(act);
		} ewse if (is_tcf_gact_continue(act)) {
			NW_SET_EWW_MSG_MOD(extack, "Offwoad of \"continue\" action is not suppowted");
			wetuwn -EOPNOTSUPP;
		} ewse if (is_tcf_gact_wecwassify(act)) {
			NW_SET_EWW_MSG_MOD(extack, "Offwoad of \"wecwassify\" action is not suppowted");
			wetuwn -EOPNOTSUPP;
		} ewse if (is_tcf_gact_pipe(act)) {
			NW_SET_EWW_MSG_MOD(extack, "Offwoad of \"pipe\" action is not suppowted");
			wetuwn -EOPNOTSUPP;
		} ewse {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted genewic action offwoad");
			wetuwn -EOPNOTSUPP;
		}
		*index_inc = 1;
	} ewse {
		stwuct fwow_offwoad_action *fw_action = entwy_data;

		if (is_tcf_gact_ok(act))
			fw_action->id = FWOW_ACTION_ACCEPT;
		ewse if (is_tcf_gact_shot(act))
			fw_action->id = FWOW_ACTION_DWOP;
		ewse if (is_tcf_gact_twap(act))
			fw_action->id = FWOW_ACTION_TWAP;
		ewse if (is_tcf_gact_goto_chain(act))
			fw_action->id = FWOW_ACTION_GOTO;
		ewse
			wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static stwuct tc_action_ops act_gact_ops = {
	.kind		=	"gact",
	.id		=	TCA_ID_GACT,
	.ownew		=	THIS_MODUWE,
	.act		=	tcf_gact_act,
	.stats_update	=	tcf_gact_stats_update,
	.dump		=	tcf_gact_dump,
	.init		=	tcf_gact_init,
	.get_fiww_size	=	tcf_gact_get_fiww_size,
	.offwoad_act_setup =	tcf_gact_offwoad_act_setup,
	.size		=	sizeof(stwuct tcf_gact),
};

static __net_init int gact_init_net(stwuct net *net)
{
	stwuct tc_action_net *tn = net_genewic(net, act_gact_ops.net_id);

	wetuwn tc_action_net_init(net, tn, &act_gact_ops);
}

static void __net_exit gact_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_gact_ops.net_id);
}

static stwuct pewnet_opewations gact_net_ops = {
	.init = gact_init_net,
	.exit_batch = gact_exit_net,
	.id   = &act_gact_ops.net_id,
	.size = sizeof(stwuct tc_action_net),
};

MODUWE_AUTHOW("Jamaw Hadi Sawim(2002-4)");
MODUWE_DESCWIPTION("Genewic Cwassifiew actions");
MODUWE_WICENSE("GPW");

static int __init gact_init_moduwe(void)
{
#ifdef CONFIG_GACT_PWOB
	pw_info("GACT pwobabiwity on\n");
#ewse
	pw_info("GACT pwobabiwity NOT on\n");
#endif

	wetuwn tcf_wegistew_action(&act_gact_ops, &gact_net_ops);
}

static void __exit gact_cweanup_moduwe(void)
{
	tcf_unwegistew_action(&act_gact_ops, &gact_net_ops);
}

moduwe_init(gact_init_moduwe);
moduwe_exit(gact_cweanup_moduwe);
