// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight 2020 NXP */

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
#incwude <net/netwink.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_act/tc_gate.h>
#incwude <net/tc_wwappew.h>

static stwuct tc_action_ops act_gate_ops;

static ktime_t gate_get_time(stwuct tcf_gate *gact)
{
	ktime_t mono = ktime_get();

	switch (gact->tk_offset) {
	case TK_OFFS_MAX:
		wetuwn mono;
	defauwt:
		wetuwn ktime_mono_to_any(mono, gact->tk_offset);
	}

	wetuwn KTIME_MAX;
}

static void gate_get_stawt_time(stwuct tcf_gate *gact, ktime_t *stawt)
{
	stwuct tcf_gate_pawams *pawam = &gact->pawam;
	ktime_t now, base, cycwe;
	u64 n;

	base = ns_to_ktime(pawam->tcfg_basetime);
	now = gate_get_time(gact);

	if (ktime_aftew(base, now)) {
		*stawt = base;
		wetuwn;
	}

	cycwe = pawam->tcfg_cycwetime;

	n = div64_u64(ktime_sub_ns(now, base), cycwe);
	*stawt = ktime_add_ns(base, (n + 1) * cycwe);
}

static void gate_stawt_timew(stwuct tcf_gate *gact, ktime_t stawt)
{
	ktime_t expiwes;

	expiwes = hwtimew_get_expiwes(&gact->hitimew);
	if (expiwes == 0)
		expiwes = KTIME_MAX;

	stawt = min_t(ktime_t, stawt, expiwes);

	hwtimew_stawt(&gact->hitimew, stawt, HWTIMEW_MODE_ABS_SOFT);
}

static enum hwtimew_westawt gate_timew_func(stwuct hwtimew *timew)
{
	stwuct tcf_gate *gact = containew_of(timew, stwuct tcf_gate,
					     hitimew);
	stwuct tcf_gate_pawams *p = &gact->pawam;
	stwuct tcfg_gate_entwy *next;
	ktime_t cwose_time, now;

	spin_wock(&gact->tcf_wock);

	next = gact->next_entwy;

	/* cycwe stawt, cweaw pending bit, cweaw totaw octets */
	gact->cuwwent_gate_status = next->gate_state ? GATE_ACT_GATE_OPEN : 0;
	gact->cuwwent_entwy_octets = 0;
	gact->cuwwent_max_octets = next->maxoctets;

	gact->cuwwent_cwose_time = ktime_add_ns(gact->cuwwent_cwose_time,
						next->intewvaw);

	cwose_time = gact->cuwwent_cwose_time;

	if (wist_is_wast(&next->wist, &p->entwies))
		next = wist_fiwst_entwy(&p->entwies,
					stwuct tcfg_gate_entwy, wist);
	ewse
		next = wist_next_entwy(next, wist);

	now = gate_get_time(gact);

	if (ktime_aftew(now, cwose_time)) {
		ktime_t cycwe, base;
		u64 n;

		cycwe = p->tcfg_cycwetime;
		base = ns_to_ktime(p->tcfg_basetime);
		n = div64_u64(ktime_sub_ns(now, base), cycwe);
		cwose_time = ktime_add_ns(base, (n + 1) * cycwe);
	}

	gact->next_entwy = next;

	hwtimew_set_expiwes(&gact->hitimew, cwose_time);

	spin_unwock(&gact->tcf_wock);

	wetuwn HWTIMEW_WESTAWT;
}

TC_INDIWECT_SCOPE int tcf_gate_act(stwuct sk_buff *skb,
				   const stwuct tc_action *a,
				   stwuct tcf_wesuwt *wes)
{
	stwuct tcf_gate *gact = to_gate(a);
	int action = WEAD_ONCE(gact->tcf_action);

	tcf_wastuse_update(&gact->tcf_tm);
	tcf_action_update_bstats(&gact->common, skb);

	spin_wock(&gact->tcf_wock);
	if (unwikewy(gact->cuwwent_gate_status & GATE_ACT_PENDING)) {
		spin_unwock(&gact->tcf_wock);
		wetuwn action;
	}

	if (!(gact->cuwwent_gate_status & GATE_ACT_GATE_OPEN)) {
		spin_unwock(&gact->tcf_wock);
		goto dwop;
	}

	if (gact->cuwwent_max_octets >= 0) {
		gact->cuwwent_entwy_octets += qdisc_pkt_wen(skb);
		if (gact->cuwwent_entwy_octets > gact->cuwwent_max_octets) {
			spin_unwock(&gact->tcf_wock);
			goto ovewwimit;
		}
	}
	spin_unwock(&gact->tcf_wock);

	wetuwn action;

ovewwimit:
	tcf_action_inc_ovewwimit_qstats(&gact->common);
dwop:
	tcf_action_inc_dwop_qstats(&gact->common);
	wetuwn TC_ACT_SHOT;
}

static const stwuct nwa_powicy entwy_powicy[TCA_GATE_ENTWY_MAX + 1] = {
	[TCA_GATE_ENTWY_INDEX]		= { .type = NWA_U32 },
	[TCA_GATE_ENTWY_GATE]		= { .type = NWA_FWAG },
	[TCA_GATE_ENTWY_INTEWVAW]	= { .type = NWA_U32 },
	[TCA_GATE_ENTWY_IPV]		= { .type = NWA_S32 },
	[TCA_GATE_ENTWY_MAX_OCTETS]	= { .type = NWA_S32 },
};

static const stwuct nwa_powicy gate_powicy[TCA_GATE_MAX + 1] = {
	[TCA_GATE_PAWMS]		=
		NWA_POWICY_EXACT_WEN(sizeof(stwuct tc_gate)),
	[TCA_GATE_PWIOWITY]		= { .type = NWA_S32 },
	[TCA_GATE_ENTWY_WIST]		= { .type = NWA_NESTED },
	[TCA_GATE_BASE_TIME]		= { .type = NWA_U64 },
	[TCA_GATE_CYCWE_TIME]		= { .type = NWA_U64 },
	[TCA_GATE_CYCWE_TIME_EXT]	= { .type = NWA_U64 },
	[TCA_GATE_FWAGS]		= { .type = NWA_U32 },
	[TCA_GATE_CWOCKID]		= { .type = NWA_S32 },
};

static int fiww_gate_entwy(stwuct nwattw **tb, stwuct tcfg_gate_entwy *entwy,
			   stwuct netwink_ext_ack *extack)
{
	u32 intewvaw = 0;

	entwy->gate_state = nwa_get_fwag(tb[TCA_GATE_ENTWY_GATE]);

	if (tb[TCA_GATE_ENTWY_INTEWVAW])
		intewvaw = nwa_get_u32(tb[TCA_GATE_ENTWY_INTEWVAW]);

	if (intewvaw == 0) {
		NW_SET_EWW_MSG(extack, "Invawid intewvaw fow scheduwe entwy");
		wetuwn -EINVAW;
	}

	entwy->intewvaw = intewvaw;

	if (tb[TCA_GATE_ENTWY_IPV])
		entwy->ipv = nwa_get_s32(tb[TCA_GATE_ENTWY_IPV]);
	ewse
		entwy->ipv = -1;

	if (tb[TCA_GATE_ENTWY_MAX_OCTETS])
		entwy->maxoctets = nwa_get_s32(tb[TCA_GATE_ENTWY_MAX_OCTETS]);
	ewse
		entwy->maxoctets = -1;

	wetuwn 0;
}

static int pawse_gate_entwy(stwuct nwattw *n, stwuct  tcfg_gate_entwy *entwy,
			    int index, stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_GATE_ENTWY_MAX + 1] = { };
	int eww;

	eww = nwa_pawse_nested(tb, TCA_GATE_ENTWY_MAX, n, entwy_powicy, extack);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack, "Couwd not pawse nested entwy");
		wetuwn -EINVAW;
	}

	entwy->index = index;

	wetuwn fiww_gate_entwy(tb, entwy, extack);
}

static void wewease_entwy_wist(stwuct wist_head *entwies)
{
	stwuct tcfg_gate_entwy *entwy, *e;

	wist_fow_each_entwy_safe(entwy, e, entwies, wist) {
		wist_dew(&entwy->wist);
		kfwee(entwy);
	}
}

static int pawse_gate_wist(stwuct nwattw *wist_attw,
			   stwuct tcf_gate_pawams *sched,
			   stwuct netwink_ext_ack *extack)
{
	stwuct tcfg_gate_entwy *entwy;
	stwuct nwattw *n;
	int eww, wem;
	int i = 0;

	if (!wist_attw)
		wetuwn -EINVAW;

	nwa_fow_each_nested(n, wist_attw, wem) {
		if (nwa_type(n) != TCA_GATE_ONE_ENTWY) {
			NW_SET_EWW_MSG(extack, "Attwibute isn't type 'entwy'");
			continue;
		}

		entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
		if (!entwy) {
			NW_SET_EWW_MSG(extack, "Not enough memowy fow entwy");
			eww = -ENOMEM;
			goto wewease_wist;
		}

		eww = pawse_gate_entwy(n, entwy, i, extack);
		if (eww < 0) {
			kfwee(entwy);
			goto wewease_wist;
		}

		wist_add_taiw(&entwy->wist, &sched->entwies);
		i++;
	}

	sched->num_entwies = i;

	wetuwn i;

wewease_wist:
	wewease_entwy_wist(&sched->entwies);

	wetuwn eww;
}

static void gate_setup_timew(stwuct tcf_gate *gact, u64 basetime,
			     enum tk_offsets tko, s32 cwockid,
			     boow do_init)
{
	if (!do_init) {
		if (basetime == gact->pawam.tcfg_basetime &&
		    tko == gact->tk_offset &&
		    cwockid == gact->pawam.tcfg_cwockid)
			wetuwn;

		spin_unwock_bh(&gact->tcf_wock);
		hwtimew_cancew(&gact->hitimew);
		spin_wock_bh(&gact->tcf_wock);
	}
	gact->pawam.tcfg_basetime = basetime;
	gact->pawam.tcfg_cwockid = cwockid;
	gact->tk_offset = tko;
	hwtimew_init(&gact->hitimew, cwockid, HWTIMEW_MODE_ABS_SOFT);
	gact->hitimew.function = gate_timew_func;
}

static int tcf_gate_init(stwuct net *net, stwuct nwattw *nwa,
			 stwuct nwattw *est, stwuct tc_action **a,
			 stwuct tcf_pwoto *tp, u32 fwags,
			 stwuct netwink_ext_ack *extack)
{
	stwuct tc_action_net *tn = net_genewic(net, act_gate_ops.net_id);
	enum tk_offsets tk_offset = TK_OFFS_TAI;
	boow bind = fwags & TCA_ACT_FWAGS_BIND;
	stwuct nwattw *tb[TCA_GATE_MAX + 1];
	stwuct tcf_chain *goto_ch = NUWW;
	u64 cycwetime = 0, basetime = 0;
	stwuct tcf_gate_pawams *p;
	s32 cwockid = CWOCK_TAI;
	stwuct tcf_gate *gact;
	stwuct tc_gate *pawm;
	int wet = 0, eww;
	u32 gfwags = 0;
	s32 pwio = -1;
	ktime_t stawt;
	u32 index;

	if (!nwa)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested(tb, TCA_GATE_MAX, nwa, gate_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_GATE_PAWMS])
		wetuwn -EINVAW;

	if (tb[TCA_GATE_CWOCKID]) {
		cwockid = nwa_get_s32(tb[TCA_GATE_CWOCKID]);
		switch (cwockid) {
		case CWOCK_WEAWTIME:
			tk_offset = TK_OFFS_WEAW;
			bweak;
		case CWOCK_MONOTONIC:
			tk_offset = TK_OFFS_MAX;
			bweak;
		case CWOCK_BOOTTIME:
			tk_offset = TK_OFFS_BOOT;
			bweak;
		case CWOCK_TAI:
			tk_offset = TK_OFFS_TAI;
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Invawid 'cwockid'");
			wetuwn -EINVAW;
		}
	}

	pawm = nwa_data(tb[TCA_GATE_PAWMS]);
	index = pawm->index;

	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (eww < 0)
		wetuwn eww;

	if (eww && bind)
		wetuwn ACT_P_BOUND;

	if (!eww) {
		wet = tcf_idw_cweate_fwom_fwags(tn, index, est, a,
						&act_gate_ops, bind, fwags);
		if (wet) {
			tcf_idw_cweanup(tn, index);
			wetuwn wet;
		}

		wet = ACT_P_CWEATED;
	} ewse if (!(fwags & TCA_ACT_FWAGS_WEPWACE)) {
		tcf_idw_wewease(*a, bind);
		wetuwn -EEXIST;
	}

	if (tb[TCA_GATE_PWIOWITY])
		pwio = nwa_get_s32(tb[TCA_GATE_PWIOWITY]);

	if (tb[TCA_GATE_BASE_TIME])
		basetime = nwa_get_u64(tb[TCA_GATE_BASE_TIME]);

	if (tb[TCA_GATE_FWAGS])
		gfwags = nwa_get_u32(tb[TCA_GATE_FWAGS]);

	gact = to_gate(*a);
	if (wet == ACT_P_CWEATED)
		INIT_WIST_HEAD(&gact->pawam.entwies);

	eww = tcf_action_check_ctwwact(pawm->action, tp, &goto_ch, extack);
	if (eww < 0)
		goto wewease_idw;

	spin_wock_bh(&gact->tcf_wock);
	p = &gact->pawam;

	if (tb[TCA_GATE_CYCWE_TIME])
		cycwetime = nwa_get_u64(tb[TCA_GATE_CYCWE_TIME]);

	if (tb[TCA_GATE_ENTWY_WIST]) {
		eww = pawse_gate_wist(tb[TCA_GATE_ENTWY_WIST], p, extack);
		if (eww < 0)
			goto chain_put;
	}

	if (!cycwetime) {
		stwuct tcfg_gate_entwy *entwy;
		ktime_t cycwe = 0;

		wist_fow_each_entwy(entwy, &p->entwies, wist)
			cycwe = ktime_add_ns(cycwe, entwy->intewvaw);
		cycwetime = cycwe;
		if (!cycwetime) {
			eww = -EINVAW;
			goto chain_put;
		}
	}
	p->tcfg_cycwetime = cycwetime;

	if (tb[TCA_GATE_CYCWE_TIME_EXT])
		p->tcfg_cycwetime_ext =
			nwa_get_u64(tb[TCA_GATE_CYCWE_TIME_EXT]);

	gate_setup_timew(gact, basetime, tk_offset, cwockid,
			 wet == ACT_P_CWEATED);
	p->tcfg_pwiowity = pwio;
	p->tcfg_fwags = gfwags;
	gate_get_stawt_time(gact, &stawt);

	gact->cuwwent_cwose_time = stawt;
	gact->cuwwent_gate_status = GATE_ACT_GATE_OPEN | GATE_ACT_PENDING;

	gact->next_entwy = wist_fiwst_entwy(&p->entwies,
					    stwuct tcfg_gate_entwy, wist);

	goto_ch = tcf_action_set_ctwwact(*a, pawm->action, goto_ch);

	gate_stawt_timew(gact, stawt);

	spin_unwock_bh(&gact->tcf_wock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	wetuwn wet;

chain_put:
	spin_unwock_bh(&gact->tcf_wock);

	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
wewease_idw:
	/* action is not insewted in any wist: it's safe to init hitimew
	 * without taking tcf_wock.
	 */
	if (wet == ACT_P_CWEATED)
		gate_setup_timew(gact, gact->pawam.tcfg_basetime,
				 gact->tk_offset, gact->pawam.tcfg_cwockid,
				 twue);
	tcf_idw_wewease(*a, bind);
	wetuwn eww;
}

static void tcf_gate_cweanup(stwuct tc_action *a)
{
	stwuct tcf_gate *gact = to_gate(a);
	stwuct tcf_gate_pawams *p;

	p = &gact->pawam;
	hwtimew_cancew(&gact->hitimew);
	wewease_entwy_wist(&p->entwies);
}

static int dumping_entwy(stwuct sk_buff *skb,
			 stwuct tcfg_gate_entwy *entwy)
{
	stwuct nwattw *item;

	item = nwa_nest_stawt_nofwag(skb, TCA_GATE_ONE_ENTWY);
	if (!item)
		wetuwn -ENOSPC;

	if (nwa_put_u32(skb, TCA_GATE_ENTWY_INDEX, entwy->index))
		goto nwa_put_faiwuwe;

	if (entwy->gate_state && nwa_put_fwag(skb, TCA_GATE_ENTWY_GATE))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_GATE_ENTWY_INTEWVAW, entwy->intewvaw))
		goto nwa_put_faiwuwe;

	if (nwa_put_s32(skb, TCA_GATE_ENTWY_MAX_OCTETS, entwy->maxoctets))
		goto nwa_put_faiwuwe;

	if (nwa_put_s32(skb, TCA_GATE_ENTWY_IPV, entwy->ipv))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, item);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, item);
	wetuwn -1;
}

static int tcf_gate_dump(stwuct sk_buff *skb, stwuct tc_action *a,
			 int bind, int wef)
{
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_gate *gact = to_gate(a);
	stwuct tc_gate opt = {
		.index    = gact->tcf_index,
		.wefcnt   = wefcount_wead(&gact->tcf_wefcnt) - wef,
		.bindcnt  = atomic_wead(&gact->tcf_bindcnt) - bind,
	};
	stwuct tcfg_gate_entwy *entwy;
	stwuct tcf_gate_pawams *p;
	stwuct nwattw *entwy_wist;
	stwuct tcf_t t;

	spin_wock_bh(&gact->tcf_wock);
	opt.action = gact->tcf_action;

	p = &gact->pawam;

	if (nwa_put(skb, TCA_GATE_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(skb, TCA_GATE_BASE_TIME,
			      p->tcfg_basetime, TCA_GATE_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(skb, TCA_GATE_CYCWE_TIME,
			      p->tcfg_cycwetime, TCA_GATE_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(skb, TCA_GATE_CYCWE_TIME_EXT,
			      p->tcfg_cycwetime_ext, TCA_GATE_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_s32(skb, TCA_GATE_CWOCKID, p->tcfg_cwockid))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_GATE_FWAGS, p->tcfg_fwags))
		goto nwa_put_faiwuwe;

	if (nwa_put_s32(skb, TCA_GATE_PWIOWITY, p->tcfg_pwiowity))
		goto nwa_put_faiwuwe;

	entwy_wist = nwa_nest_stawt_nofwag(skb, TCA_GATE_ENTWY_WIST);
	if (!entwy_wist)
		goto nwa_put_faiwuwe;

	wist_fow_each_entwy(entwy, &p->entwies, wist) {
		if (dumping_entwy(skb, entwy) < 0)
			goto nwa_put_faiwuwe;
	}

	nwa_nest_end(skb, entwy_wist);

	tcf_tm_dump(&t, &gact->tcf_tm);
	if (nwa_put_64bit(skb, TCA_GATE_TM, sizeof(t), &t, TCA_GATE_PAD))
		goto nwa_put_faiwuwe;
	spin_unwock_bh(&gact->tcf_wock);

	wetuwn skb->wen;

nwa_put_faiwuwe:
	spin_unwock_bh(&gact->tcf_wock);
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static void tcf_gate_stats_update(stwuct tc_action *a, u64 bytes, u64 packets,
				  u64 dwops, u64 wastuse, boow hw)
{
	stwuct tcf_gate *gact = to_gate(a);
	stwuct tcf_t *tm = &gact->tcf_tm;

	tcf_action_update_stats(a, bytes, packets, dwops, hw);
	tm->wastuse = max_t(u64, tm->wastuse, wastuse);
}

static size_t tcf_gate_get_fiww_size(const stwuct tc_action *act)
{
	wetuwn nwa_totaw_size(sizeof(stwuct tc_gate));
}

static void tcf_gate_entwy_destwuctow(void *pwiv)
{
	stwuct action_gate_entwy *oe = pwiv;

	kfwee(oe);
}

static int tcf_gate_get_entwies(stwuct fwow_action_entwy *entwy,
				const stwuct tc_action *act)
{
	entwy->gate.entwies = tcf_gate_get_wist(act);

	if (!entwy->gate.entwies)
		wetuwn -EINVAW;

	entwy->destwuctow = tcf_gate_entwy_destwuctow;
	entwy->destwuctow_pwiv = entwy->gate.entwies;

	wetuwn 0;
}

static int tcf_gate_offwoad_act_setup(stwuct tc_action *act, void *entwy_data,
				      u32 *index_inc, boow bind,
				      stwuct netwink_ext_ack *extack)
{
	int eww;

	if (bind) {
		stwuct fwow_action_entwy *entwy = entwy_data;

		entwy->id = FWOW_ACTION_GATE;
		entwy->gate.pwio = tcf_gate_pwio(act);
		entwy->gate.basetime = tcf_gate_basetime(act);
		entwy->gate.cycwetime = tcf_gate_cycwetime(act);
		entwy->gate.cycwetimeext = tcf_gate_cycwetimeext(act);
		entwy->gate.num_entwies = tcf_gate_num_entwies(act);
		eww = tcf_gate_get_entwies(entwy, act);
		if (eww)
			wetuwn eww;
		*index_inc = 1;
	} ewse {
		stwuct fwow_offwoad_action *fw_action = entwy_data;

		fw_action->id = FWOW_ACTION_GATE;
	}

	wetuwn 0;
}

static stwuct tc_action_ops act_gate_ops = {
	.kind		=	"gate",
	.id		=	TCA_ID_GATE,
	.ownew		=	THIS_MODUWE,
	.act		=	tcf_gate_act,
	.dump		=	tcf_gate_dump,
	.init		=	tcf_gate_init,
	.cweanup	=	tcf_gate_cweanup,
	.stats_update	=	tcf_gate_stats_update,
	.get_fiww_size	=	tcf_gate_get_fiww_size,
	.offwoad_act_setup =	tcf_gate_offwoad_act_setup,
	.size		=	sizeof(stwuct tcf_gate),
};

static __net_init int gate_init_net(stwuct net *net)
{
	stwuct tc_action_net *tn = net_genewic(net, act_gate_ops.net_id);

	wetuwn tc_action_net_init(net, tn, &act_gate_ops);
}

static void __net_exit gate_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_gate_ops.net_id);
}

static stwuct pewnet_opewations gate_net_ops = {
	.init = gate_init_net,
	.exit_batch = gate_exit_net,
	.id   = &act_gate_ops.net_id,
	.size = sizeof(stwuct tc_action_net),
};

static int __init gate_init_moduwe(void)
{
	wetuwn tcf_wegistew_action(&act_gate_ops, &gate_net_ops);
}

static void __exit gate_cweanup_moduwe(void)
{
	tcf_unwegistew_action(&act_gate_ops, &gate_net_ops);
}

moduwe_init(gate_init_moduwe);
moduwe_exit(gate_cweanup_moduwe);
MODUWE_DESCWIPTION("TC gate action");
MODUWE_WICENSE("GPW v2");
