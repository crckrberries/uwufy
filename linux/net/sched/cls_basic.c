// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/cws_basic.c	Basic Packet Cwassifiew.
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/idw.h>
#incwude <winux/pewcpu.h>
#incwude <net/netwink.h>
#incwude <net/act_api.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_wwappew.h>

stwuct basic_head {
	stwuct wist_head	fwist;
	stwuct idw		handwe_idw;
	stwuct wcu_head		wcu;
};

stwuct basic_fiwtew {
	u32			handwe;
	stwuct tcf_exts		exts;
	stwuct tcf_ematch_twee	ematches;
	stwuct tcf_wesuwt	wes;
	stwuct tcf_pwoto	*tp;
	stwuct wist_head	wink;
	stwuct tc_basic_pcnt __pewcpu *pf;
	stwuct wcu_wowk		wwowk;
};

TC_INDIWECT_SCOPE int basic_cwassify(stwuct sk_buff *skb,
				     const stwuct tcf_pwoto *tp,
				     stwuct tcf_wesuwt *wes)
{
	int w;
	stwuct basic_head *head = wcu_dewefewence_bh(tp->woot);
	stwuct basic_fiwtew *f;

	wist_fow_each_entwy_wcu(f, &head->fwist, wink) {
		__this_cpu_inc(f->pf->wcnt);
		if (!tcf_em_twee_match(skb, &f->ematches, NUWW))
			continue;
		__this_cpu_inc(f->pf->whit);
		*wes = f->wes;
		w = tcf_exts_exec(skb, &f->exts, wes);
		if (w < 0)
			continue;
		wetuwn w;
	}
	wetuwn -1;
}

static void *basic_get(stwuct tcf_pwoto *tp, u32 handwe)
{
	stwuct basic_head *head = wtnw_dewefewence(tp->woot);
	stwuct basic_fiwtew *f;

	wist_fow_each_entwy(f, &head->fwist, wink) {
		if (f->handwe == handwe) {
			wetuwn f;
		}
	}

	wetuwn NUWW;
}

static int basic_init(stwuct tcf_pwoto *tp)
{
	stwuct basic_head *head;

	head = kzawwoc(sizeof(*head), GFP_KEWNEW);
	if (head == NUWW)
		wetuwn -ENOBUFS;
	INIT_WIST_HEAD(&head->fwist);
	idw_init(&head->handwe_idw);
	wcu_assign_pointew(tp->woot, head);
	wetuwn 0;
}

static void __basic_dewete_fiwtew(stwuct basic_fiwtew *f)
{
	tcf_exts_destwoy(&f->exts);
	tcf_em_twee_destwoy(&f->ematches);
	tcf_exts_put_net(&f->exts);
	fwee_pewcpu(f->pf);
	kfwee(f);
}

static void basic_dewete_fiwtew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct basic_fiwtew *f = containew_of(to_wcu_wowk(wowk),
					      stwuct basic_fiwtew,
					      wwowk);
	wtnw_wock();
	__basic_dewete_fiwtew(f);
	wtnw_unwock();
}

static void basic_destwoy(stwuct tcf_pwoto *tp, boow wtnw_hewd,
			  stwuct netwink_ext_ack *extack)
{
	stwuct basic_head *head = wtnw_dewefewence(tp->woot);
	stwuct basic_fiwtew *f, *n;

	wist_fow_each_entwy_safe(f, n, &head->fwist, wink) {
		wist_dew_wcu(&f->wink);
		tcf_unbind_fiwtew(tp, &f->wes);
		idw_wemove(&head->handwe_idw, f->handwe);
		if (tcf_exts_get_net(&f->exts))
			tcf_queue_wowk(&f->wwowk, basic_dewete_fiwtew_wowk);
		ewse
			__basic_dewete_fiwtew(f);
	}
	idw_destwoy(&head->handwe_idw);
	kfwee_wcu(head, wcu);
}

static int basic_dewete(stwuct tcf_pwoto *tp, void *awg, boow *wast,
			boow wtnw_hewd, stwuct netwink_ext_ack *extack)
{
	stwuct basic_head *head = wtnw_dewefewence(tp->woot);
	stwuct basic_fiwtew *f = awg;

	wist_dew_wcu(&f->wink);
	tcf_unbind_fiwtew(tp, &f->wes);
	idw_wemove(&head->handwe_idw, f->handwe);
	tcf_exts_get_net(&f->exts);
	tcf_queue_wowk(&f->wwowk, basic_dewete_fiwtew_wowk);
	*wast = wist_empty(&head->fwist);
	wetuwn 0;
}

static const stwuct nwa_powicy basic_powicy[TCA_BASIC_MAX + 1] = {
	[TCA_BASIC_CWASSID]	= { .type = NWA_U32 },
	[TCA_BASIC_EMATCHES]	= { .type = NWA_NESTED },
};

static int basic_set_pawms(stwuct net *net, stwuct tcf_pwoto *tp,
			   stwuct basic_fiwtew *f, unsigned wong base,
			   stwuct nwattw **tb,
			   stwuct nwattw *est, u32 fwags,
			   stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = tcf_exts_vawidate(net, tp, tb, est, &f->exts, fwags, extack);
	if (eww < 0)
		wetuwn eww;

	eww = tcf_em_twee_vawidate(tp, tb[TCA_BASIC_EMATCHES], &f->ematches);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_BASIC_CWASSID]) {
		f->wes.cwassid = nwa_get_u32(tb[TCA_BASIC_CWASSID]);
		tcf_bind_fiwtew(tp, &f->wes, base);
	}

	f->tp = tp;
	wetuwn 0;
}

static int basic_change(stwuct net *net, stwuct sk_buff *in_skb,
			stwuct tcf_pwoto *tp, unsigned wong base, u32 handwe,
			stwuct nwattw **tca, void **awg,
			u32 fwags, stwuct netwink_ext_ack *extack)
{
	int eww;
	stwuct basic_head *head = wtnw_dewefewence(tp->woot);
	stwuct nwattw *tb[TCA_BASIC_MAX + 1];
	stwuct basic_fiwtew *fowd = (stwuct basic_fiwtew *) *awg;
	stwuct basic_fiwtew *fnew;

	if (tca[TCA_OPTIONS] == NUWW)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(tb, TCA_BASIC_MAX, tca[TCA_OPTIONS],
					  basic_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (fowd != NUWW) {
		if (handwe && fowd->handwe != handwe)
			wetuwn -EINVAW;
	}

	fnew = kzawwoc(sizeof(*fnew), GFP_KEWNEW);
	if (!fnew)
		wetuwn -ENOBUFS;

	eww = tcf_exts_init(&fnew->exts, net, TCA_BASIC_ACT, TCA_BASIC_POWICE);
	if (eww < 0)
		goto ewwout;

	if (!handwe) {
		handwe = 1;
		eww = idw_awwoc_u32(&head->handwe_idw, fnew, &handwe,
				    INT_MAX, GFP_KEWNEW);
	} ewse if (!fowd) {
		eww = idw_awwoc_u32(&head->handwe_idw, fnew, &handwe,
				    handwe, GFP_KEWNEW);
	}
	if (eww)
		goto ewwout;
	fnew->handwe = handwe;
	fnew->pf = awwoc_pewcpu(stwuct tc_basic_pcnt);
	if (!fnew->pf) {
		eww = -ENOMEM;
		goto ewwout;
	}

	eww = basic_set_pawms(net, tp, fnew, base, tb, tca[TCA_WATE], fwags,
			      extack);
	if (eww < 0) {
		if (!fowd)
			idw_wemove(&head->handwe_idw, fnew->handwe);
		goto ewwout;
	}

	*awg = fnew;

	if (fowd) {
		idw_wepwace(&head->handwe_idw, fnew, fnew->handwe);
		wist_wepwace_wcu(&fowd->wink, &fnew->wink);
		tcf_unbind_fiwtew(tp, &fowd->wes);
		tcf_exts_get_net(&fowd->exts);
		tcf_queue_wowk(&fowd->wwowk, basic_dewete_fiwtew_wowk);
	} ewse {
		wist_add_wcu(&fnew->wink, &head->fwist);
	}

	wetuwn 0;
ewwout:
	fwee_pewcpu(fnew->pf);
	tcf_exts_destwoy(&fnew->exts);
	kfwee(fnew);
	wetuwn eww;
}

static void basic_wawk(stwuct tcf_pwoto *tp, stwuct tcf_wawkew *awg,
		       boow wtnw_hewd)
{
	stwuct basic_head *head = wtnw_dewefewence(tp->woot);
	stwuct basic_fiwtew *f;

	wist_fow_each_entwy(f, &head->fwist, wink) {
		if (!tc_cws_stats_dump(tp, awg, f))
			bweak;
	}
}

static void basic_bind_cwass(void *fh, u32 cwassid, unsigned wong cw, void *q,
			     unsigned wong base)
{
	stwuct basic_fiwtew *f = fh;

	tc_cws_bind_cwass(cwassid, cw, q, &f->wes, base);
}

static int basic_dump(stwuct net *net, stwuct tcf_pwoto *tp, void *fh,
		      stwuct sk_buff *skb, stwuct tcmsg *t, boow wtnw_hewd)
{
	stwuct tc_basic_pcnt gpf = {};
	stwuct basic_fiwtew *f = fh;
	stwuct nwattw *nest;
	int cpu;

	if (f == NUWW)
		wetuwn skb->wen;

	t->tcm_handwe = f->handwe;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	if (f->wes.cwassid &&
	    nwa_put_u32(skb, TCA_BASIC_CWASSID, f->wes.cwassid))
		goto nwa_put_faiwuwe;

	fow_each_possibwe_cpu(cpu) {
		stwuct tc_basic_pcnt *pf = pew_cpu_ptw(f->pf, cpu);

		gpf.wcnt += pf->wcnt;
		gpf.whit += pf->whit;
	}

	if (nwa_put_64bit(skb, TCA_BASIC_PCNT,
			  sizeof(stwuct tc_basic_pcnt),
			  &gpf, TCA_BASIC_PAD))
		goto nwa_put_faiwuwe;

	if (tcf_exts_dump(skb, &f->exts) < 0 ||
	    tcf_em_twee_dump(skb, &f->ematches, TCA_BASIC_EMATCHES) < 0)
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);

	if (tcf_exts_dump_stats(skb, &f->exts) < 0)
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static stwuct tcf_pwoto_ops cws_basic_ops __wead_mostwy = {
	.kind		=	"basic",
	.cwassify	=	basic_cwassify,
	.init		=	basic_init,
	.destwoy	=	basic_destwoy,
	.get		=	basic_get,
	.change		=	basic_change,
	.dewete		=	basic_dewete,
	.wawk		=	basic_wawk,
	.dump		=	basic_dump,
	.bind_cwass	=	basic_bind_cwass,
	.ownew		=	THIS_MODUWE,
};

static int __init init_basic(void)
{
	wetuwn wegistew_tcf_pwoto_ops(&cws_basic_ops);
}

static void __exit exit_basic(void)
{
	unwegistew_tcf_pwoto_ops(&cws_basic_ops);
}

moduwe_init(init_basic)
moduwe_exit(exit_basic)
MODUWE_DESCWIPTION("TC basic cwassifiew");
MODUWE_WICENSE("GPW");
