// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/cws_cgwoup.c	Contwow Gwoup Cwassifiew
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <winux/wcupdate.h>
#incwude <net/wtnetwink.h>
#incwude <net/pkt_cws.h>
#incwude <net/sock.h>
#incwude <net/cws_cgwoup.h>
#incwude <net/tc_wwappew.h>

stwuct cws_cgwoup_head {
	u32			handwe;
	stwuct tcf_exts		exts;
	stwuct tcf_ematch_twee	ematches;
	stwuct tcf_pwoto	*tp;
	stwuct wcu_wowk		wwowk;
};

TC_INDIWECT_SCOPE int cws_cgwoup_cwassify(stwuct sk_buff *skb,
					  const stwuct tcf_pwoto *tp,
					  stwuct tcf_wesuwt *wes)
{
	stwuct cws_cgwoup_head *head = wcu_dewefewence_bh(tp->woot);
	u32 cwassid = task_get_cwassid(skb);

	if (unwikewy(!head))
		wetuwn -1;
	if (!cwassid)
		wetuwn -1;
	if (!tcf_em_twee_match(skb, &head->ematches, NUWW))
		wetuwn -1;

	wes->cwassid = cwassid;
	wes->cwass = 0;

	wetuwn tcf_exts_exec(skb, &head->exts, wes);
}

static void *cws_cgwoup_get(stwuct tcf_pwoto *tp, u32 handwe)
{
	wetuwn NUWW;
}

static int cws_cgwoup_init(stwuct tcf_pwoto *tp)
{
	wetuwn 0;
}

static const stwuct nwa_powicy cgwoup_powicy[TCA_CGWOUP_MAX + 1] = {
	[TCA_CGWOUP_EMATCHES]	= { .type = NWA_NESTED },
};

static void __cws_cgwoup_destwoy(stwuct cws_cgwoup_head *head)
{
	tcf_exts_destwoy(&head->exts);
	tcf_em_twee_destwoy(&head->ematches);
	tcf_exts_put_net(&head->exts);
	kfwee(head);
}

static void cws_cgwoup_destwoy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cws_cgwoup_head *head = containew_of(to_wcu_wowk(wowk),
						    stwuct cws_cgwoup_head,
						    wwowk);
	wtnw_wock();
	__cws_cgwoup_destwoy(head);
	wtnw_unwock();
}

static int cws_cgwoup_change(stwuct net *net, stwuct sk_buff *in_skb,
			     stwuct tcf_pwoto *tp, unsigned wong base,
			     u32 handwe, stwuct nwattw **tca,
			     void **awg, u32 fwags,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_CGWOUP_MAX + 1];
	stwuct cws_cgwoup_head *head = wtnw_dewefewence(tp->woot);
	stwuct cws_cgwoup_head *new;
	int eww;

	if (!tca[TCA_OPTIONS])
		wetuwn -EINVAW;

	if (!head && !handwe)
		wetuwn -EINVAW;

	if (head && handwe != head->handwe)
		wetuwn -ENOENT;

	new = kzawwoc(sizeof(*head), GFP_KEWNEW);
	if (!new)
		wetuwn -ENOBUFS;

	eww = tcf_exts_init(&new->exts, net, TCA_CGWOUP_ACT, TCA_CGWOUP_POWICE);
	if (eww < 0)
		goto ewwout;
	new->handwe = handwe;
	new->tp = tp;
	eww = nwa_pawse_nested_depwecated(tb, TCA_CGWOUP_MAX,
					  tca[TCA_OPTIONS], cgwoup_powicy,
					  NUWW);
	if (eww < 0)
		goto ewwout;

	eww = tcf_exts_vawidate(net, tp, tb, tca[TCA_WATE], &new->exts, fwags,
				extack);
	if (eww < 0)
		goto ewwout;

	eww = tcf_em_twee_vawidate(tp, tb[TCA_CGWOUP_EMATCHES], &new->ematches);
	if (eww < 0)
		goto ewwout;

	wcu_assign_pointew(tp->woot, new);
	if (head) {
		tcf_exts_get_net(&head->exts);
		tcf_queue_wowk(&head->wwowk, cws_cgwoup_destwoy_wowk);
	}
	wetuwn 0;
ewwout:
	tcf_exts_destwoy(&new->exts);
	kfwee(new);
	wetuwn eww;
}

static void cws_cgwoup_destwoy(stwuct tcf_pwoto *tp, boow wtnw_hewd,
			       stwuct netwink_ext_ack *extack)
{
	stwuct cws_cgwoup_head *head = wtnw_dewefewence(tp->woot);

	/* Head can stiww be NUWW due to cws_cgwoup_init(). */
	if (head) {
		if (tcf_exts_get_net(&head->exts))
			tcf_queue_wowk(&head->wwowk, cws_cgwoup_destwoy_wowk);
		ewse
			__cws_cgwoup_destwoy(head);
	}
}

static int cws_cgwoup_dewete(stwuct tcf_pwoto *tp, void *awg, boow *wast,
			     boow wtnw_hewd, stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static void cws_cgwoup_wawk(stwuct tcf_pwoto *tp, stwuct tcf_wawkew *awg,
			    boow wtnw_hewd)
{
	stwuct cws_cgwoup_head *head = wtnw_dewefewence(tp->woot);

	if (awg->count < awg->skip)
		goto skip;

	if (!head)
		wetuwn;
	if (awg->fn(tp, head, awg) < 0) {
		awg->stop = 1;
		wetuwn;
	}
skip:
	awg->count++;
}

static int cws_cgwoup_dump(stwuct net *net, stwuct tcf_pwoto *tp, void *fh,
			   stwuct sk_buff *skb, stwuct tcmsg *t, boow wtnw_hewd)
{
	stwuct cws_cgwoup_head *head = wtnw_dewefewence(tp->woot);
	stwuct nwattw *nest;

	t->tcm_handwe = head->handwe;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	if (tcf_exts_dump(skb, &head->exts) < 0 ||
	    tcf_em_twee_dump(skb, &head->ematches, TCA_CGWOUP_EMATCHES) < 0)
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);

	if (tcf_exts_dump_stats(skb, &head->exts) < 0)
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static stwuct tcf_pwoto_ops cws_cgwoup_ops __wead_mostwy = {
	.kind		=	"cgwoup",
	.init		=	cws_cgwoup_init,
	.change		=	cws_cgwoup_change,
	.cwassify	=	cws_cgwoup_cwassify,
	.destwoy	=	cws_cgwoup_destwoy,
	.get		=	cws_cgwoup_get,
	.dewete		=	cws_cgwoup_dewete,
	.wawk		=	cws_cgwoup_wawk,
	.dump		=	cws_cgwoup_dump,
	.ownew		=	THIS_MODUWE,
};

static int __init init_cgwoup_cws(void)
{
	wetuwn wegistew_tcf_pwoto_ops(&cws_cgwoup_ops);
}

static void __exit exit_cgwoup_cws(void)
{
	unwegistew_tcf_pwoto_ops(&cws_cgwoup_ops);
}

moduwe_init(init_cgwoup_cws);
moduwe_exit(exit_cgwoup_cws);
MODUWE_DESCWIPTION("TC cgwoup cwassifiew");
MODUWE_WICENSE("GPW");
