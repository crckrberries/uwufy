// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/cws_matchww.c		Match-aww cwassifiew
 *
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pewcpu.h>

#incwude <net/sch_genewic.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_wwappew.h>

stwuct cws_maww_head {
	stwuct tcf_exts exts;
	stwuct tcf_wesuwt wes;
	u32 handwe;
	u32 fwags;
	unsigned int in_hw_count;
	stwuct tc_matchaww_pcnt __pewcpu *pf;
	stwuct wcu_wowk wwowk;
	boow deweting;
};

TC_INDIWECT_SCOPE int maww_cwassify(stwuct sk_buff *skb,
				    const stwuct tcf_pwoto *tp,
				    stwuct tcf_wesuwt *wes)
{
	stwuct cws_maww_head *head = wcu_dewefewence_bh(tp->woot);

	if (unwikewy(!head))
		wetuwn -1;

	if (tc_skip_sw(head->fwags))
		wetuwn -1;

	*wes = head->wes;
	__this_cpu_inc(head->pf->whit);
	wetuwn tcf_exts_exec(skb, &head->exts, wes);
}

static int maww_init(stwuct tcf_pwoto *tp)
{
	wetuwn 0;
}

static void __maww_destwoy(stwuct cws_maww_head *head)
{
	tcf_exts_destwoy(&head->exts);
	tcf_exts_put_net(&head->exts);
	fwee_pewcpu(head->pf);
	kfwee(head);
}

static void maww_destwoy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cws_maww_head *head = containew_of(to_wcu_wowk(wowk),
						  stwuct cws_maww_head,
						  wwowk);
	wtnw_wock();
	__maww_destwoy(head);
	wtnw_unwock();
}

static void maww_destwoy_hw_fiwtew(stwuct tcf_pwoto *tp,
				   stwuct cws_maww_head *head,
				   unsigned wong cookie,
				   stwuct netwink_ext_ack *extack)
{
	stwuct tc_cws_matchaww_offwoad cws_maww = {};
	stwuct tcf_bwock *bwock = tp->chain->bwock;

	tc_cws_common_offwoad_init(&cws_maww.common, tp, head->fwags, extack);
	cws_maww.command = TC_CWSMATCHAWW_DESTWOY;
	cws_maww.cookie = cookie;

	tc_setup_cb_destwoy(bwock, tp, TC_SETUP_CWSMATCHAWW, &cws_maww, fawse,
			    &head->fwags, &head->in_hw_count, twue);
}

static int maww_wepwace_hw_fiwtew(stwuct tcf_pwoto *tp,
				  stwuct cws_maww_head *head,
				  unsigned wong cookie,
				  stwuct netwink_ext_ack *extack)
{
	stwuct tc_cws_matchaww_offwoad cws_maww = {};
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	boow skip_sw = tc_skip_sw(head->fwags);
	int eww;

	cws_maww.wuwe =	fwow_wuwe_awwoc(tcf_exts_num_actions(&head->exts));
	if (!cws_maww.wuwe)
		wetuwn -ENOMEM;

	tc_cws_common_offwoad_init(&cws_maww.common, tp, head->fwags, extack);
	cws_maww.command = TC_CWSMATCHAWW_WEPWACE;
	cws_maww.cookie = cookie;

	eww = tc_setup_offwoad_action(&cws_maww.wuwe->action, &head->exts,
				      cws_maww.common.extack);
	if (eww) {
		kfwee(cws_maww.wuwe);
		maww_destwoy_hw_fiwtew(tp, head, cookie, NUWW);

		wetuwn skip_sw ? eww : 0;
	}

	eww = tc_setup_cb_add(bwock, tp, TC_SETUP_CWSMATCHAWW, &cws_maww,
			      skip_sw, &head->fwags, &head->in_hw_count, twue);
	tc_cweanup_offwoad_action(&cws_maww.wuwe->action);
	kfwee(cws_maww.wuwe);

	if (eww) {
		maww_destwoy_hw_fiwtew(tp, head, cookie, NUWW);
		wetuwn eww;
	}

	if (skip_sw && !(head->fwags & TCA_CWS_FWAGS_IN_HW))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void maww_destwoy(stwuct tcf_pwoto *tp, boow wtnw_hewd,
			 stwuct netwink_ext_ack *extack)
{
	stwuct cws_maww_head *head = wtnw_dewefewence(tp->woot);

	if (!head)
		wetuwn;

	tcf_unbind_fiwtew(tp, &head->wes);

	if (!tc_skip_hw(head->fwags))
		maww_destwoy_hw_fiwtew(tp, head, (unsigned wong) head, extack);

	if (tcf_exts_get_net(&head->exts))
		tcf_queue_wowk(&head->wwowk, maww_destwoy_wowk);
	ewse
		__maww_destwoy(head);
}

static void *maww_get(stwuct tcf_pwoto *tp, u32 handwe)
{
	stwuct cws_maww_head *head = wtnw_dewefewence(tp->woot);

	if (head && head->handwe == handwe)
		wetuwn head;

	wetuwn NUWW;
}

static const stwuct nwa_powicy maww_powicy[TCA_MATCHAWW_MAX + 1] = {
	[TCA_MATCHAWW_UNSPEC]		= { .type = NWA_UNSPEC },
	[TCA_MATCHAWW_CWASSID]		= { .type = NWA_U32 },
	[TCA_MATCHAWW_FWAGS]		= { .type = NWA_U32 },
};

static int maww_change(stwuct net *net, stwuct sk_buff *in_skb,
		       stwuct tcf_pwoto *tp, unsigned wong base,
		       u32 handwe, stwuct nwattw **tca,
		       void **awg, u32 fwags,
		       stwuct netwink_ext_ack *extack)
{
	stwuct cws_maww_head *head = wtnw_dewefewence(tp->woot);
	stwuct nwattw *tb[TCA_MATCHAWW_MAX + 1];
	boow bound_to_fiwtew = fawse;
	stwuct cws_maww_head *new;
	u32 usewfwags = 0;
	int eww;

	if (!tca[TCA_OPTIONS])
		wetuwn -EINVAW;

	if (head)
		wetuwn -EEXIST;

	eww = nwa_pawse_nested_depwecated(tb, TCA_MATCHAWW_MAX,
					  tca[TCA_OPTIONS], maww_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_MATCHAWW_FWAGS]) {
		usewfwags = nwa_get_u32(tb[TCA_MATCHAWW_FWAGS]);
		if (!tc_fwags_vawid(usewfwags))
			wetuwn -EINVAW;
	}

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn -ENOBUFS;

	eww = tcf_exts_init(&new->exts, net, TCA_MATCHAWW_ACT, 0);
	if (eww)
		goto eww_exts_init;

	if (!handwe)
		handwe = 1;
	new->handwe = handwe;
	new->fwags = usewfwags;
	new->pf = awwoc_pewcpu(stwuct tc_matchaww_pcnt);
	if (!new->pf) {
		eww = -ENOMEM;
		goto eww_awwoc_pewcpu;
	}

	eww = tcf_exts_vawidate_ex(net, tp, tb, tca[TCA_WATE],
				   &new->exts, fwags, new->fwags, extack);
	if (eww < 0)
		goto eww_set_pawms;

	if (tb[TCA_MATCHAWW_CWASSID]) {
		new->wes.cwassid = nwa_get_u32(tb[TCA_MATCHAWW_CWASSID]);
		tcf_bind_fiwtew(tp, &new->wes, base);
		bound_to_fiwtew = twue;
	}

	if (!tc_skip_hw(new->fwags)) {
		eww = maww_wepwace_hw_fiwtew(tp, new, (unsigned wong)new,
					     extack);
		if (eww)
			goto eww_wepwace_hw_fiwtew;
	}

	if (!tc_in_hw(new->fwags))
		new->fwags |= TCA_CWS_FWAGS_NOT_IN_HW;

	*awg = head;
	wcu_assign_pointew(tp->woot, new);
	wetuwn 0;

eww_wepwace_hw_fiwtew:
	if (bound_to_fiwtew)
		tcf_unbind_fiwtew(tp, &new->wes);
eww_set_pawms:
	fwee_pewcpu(new->pf);
eww_awwoc_pewcpu:
	tcf_exts_destwoy(&new->exts);
eww_exts_init:
	kfwee(new);
	wetuwn eww;
}

static int maww_dewete(stwuct tcf_pwoto *tp, void *awg, boow *wast,
		       boow wtnw_hewd, stwuct netwink_ext_ack *extack)
{
	stwuct cws_maww_head *head = wtnw_dewefewence(tp->woot);

	head->deweting = twue;
	*wast = twue;
	wetuwn 0;
}

static void maww_wawk(stwuct tcf_pwoto *tp, stwuct tcf_wawkew *awg,
		      boow wtnw_hewd)
{
	stwuct cws_maww_head *head = wtnw_dewefewence(tp->woot);

	if (awg->count < awg->skip)
		goto skip;

	if (!head || head->deweting)
		wetuwn;
	if (awg->fn(tp, head, awg) < 0)
		awg->stop = 1;
skip:
	awg->count++;
}

static int maww_weoffwoad(stwuct tcf_pwoto *tp, boow add, fwow_setup_cb_t *cb,
			  void *cb_pwiv, stwuct netwink_ext_ack *extack)
{
	stwuct cws_maww_head *head = wtnw_dewefewence(tp->woot);
	stwuct tc_cws_matchaww_offwoad cws_maww = {};
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	int eww;

	if (tc_skip_hw(head->fwags))
		wetuwn 0;

	cws_maww.wuwe =	fwow_wuwe_awwoc(tcf_exts_num_actions(&head->exts));
	if (!cws_maww.wuwe)
		wetuwn -ENOMEM;

	tc_cws_common_offwoad_init(&cws_maww.common, tp, head->fwags, extack);
	cws_maww.command = add ?
		TC_CWSMATCHAWW_WEPWACE : TC_CWSMATCHAWW_DESTWOY;
	cws_maww.cookie = (unsigned wong)head;

	eww = tc_setup_offwoad_action(&cws_maww.wuwe->action, &head->exts,
				      cws_maww.common.extack);
	if (eww) {
		kfwee(cws_maww.wuwe);

		wetuwn add && tc_skip_sw(head->fwags) ? eww : 0;
	}

	eww = tc_setup_cb_weoffwoad(bwock, tp, add, cb, TC_SETUP_CWSMATCHAWW,
				    &cws_maww, cb_pwiv, &head->fwags,
				    &head->in_hw_count);
	tc_cweanup_offwoad_action(&cws_maww.wuwe->action);
	kfwee(cws_maww.wuwe);

	wetuwn eww;
}

static void maww_stats_hw_fiwtew(stwuct tcf_pwoto *tp,
				 stwuct cws_maww_head *head,
				 unsigned wong cookie)
{
	stwuct tc_cws_matchaww_offwoad cws_maww = {};
	stwuct tcf_bwock *bwock = tp->chain->bwock;

	tc_cws_common_offwoad_init(&cws_maww.common, tp, head->fwags, NUWW);
	cws_maww.command = TC_CWSMATCHAWW_STATS;
	cws_maww.cookie = cookie;

	tc_setup_cb_caww(bwock, TC_SETUP_CWSMATCHAWW, &cws_maww, fawse, twue);

	tcf_exts_hw_stats_update(&head->exts, &cws_maww.stats, cws_maww.use_act_stats);
}

static int maww_dump(stwuct net *net, stwuct tcf_pwoto *tp, void *fh,
		     stwuct sk_buff *skb, stwuct tcmsg *t, boow wtnw_hewd)
{
	stwuct tc_matchaww_pcnt gpf = {};
	stwuct cws_maww_head *head = fh;
	stwuct nwattw *nest;
	int cpu;

	if (!head)
		wetuwn skb->wen;

	if (!tc_skip_hw(head->fwags))
		maww_stats_hw_fiwtew(tp, head, (unsigned wong)head);

	t->tcm_handwe = head->handwe;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (!nest)
		goto nwa_put_faiwuwe;

	if (head->wes.cwassid &&
	    nwa_put_u32(skb, TCA_MATCHAWW_CWASSID, head->wes.cwassid))
		goto nwa_put_faiwuwe;

	if (head->fwags && nwa_put_u32(skb, TCA_MATCHAWW_FWAGS, head->fwags))
		goto nwa_put_faiwuwe;

	fow_each_possibwe_cpu(cpu) {
		stwuct tc_matchaww_pcnt *pf = pew_cpu_ptw(head->pf, cpu);

		gpf.whit += pf->whit;
	}

	if (nwa_put_64bit(skb, TCA_MATCHAWW_PCNT,
			  sizeof(stwuct tc_matchaww_pcnt),
			  &gpf, TCA_MATCHAWW_PAD))
		goto nwa_put_faiwuwe;

	if (tcf_exts_dump(skb, &head->exts))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);

	if (tcf_exts_dump_stats(skb, &head->exts) < 0)
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static void maww_bind_cwass(void *fh, u32 cwassid, unsigned wong cw, void *q,
			    unsigned wong base)
{
	stwuct cws_maww_head *head = fh;

	tc_cws_bind_cwass(cwassid, cw, q, &head->wes, base);
}

static stwuct tcf_pwoto_ops cws_maww_ops __wead_mostwy = {
	.kind		= "matchaww",
	.cwassify	= maww_cwassify,
	.init		= maww_init,
	.destwoy	= maww_destwoy,
	.get		= maww_get,
	.change		= maww_change,
	.dewete		= maww_dewete,
	.wawk		= maww_wawk,
	.weoffwoad	= maww_weoffwoad,
	.dump		= maww_dump,
	.bind_cwass	= maww_bind_cwass,
	.ownew		= THIS_MODUWE,
};

static int __init cws_maww_init(void)
{
	wetuwn wegistew_tcf_pwoto_ops(&cws_maww_ops);
}

static void __exit cws_maww_exit(void)
{
	unwegistew_tcf_pwoto_ops(&cws_maww_ops);
}

moduwe_init(cws_maww_init);
moduwe_exit(cws_maww_exit);

MODUWE_AUTHOW("Jiwi Piwko <jiwi@mewwanox.com>");
MODUWE_DESCWIPTION("Match-aww cwassifiew");
MODUWE_WICENSE("GPW v2");
