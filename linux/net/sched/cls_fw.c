// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/cws_fw.c	Cwassifiew mapping ipchains' fwmawk to twaffic cwass.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *
 * Changes:
 * Kawwis Peisenieks <kawwis@mt.wv> : 990415 : fw_wawk off by one
 * Kawwis Peisenieks <kawwis@mt.wv> : 990415 : fw_dewete kiwwed aww the fiwtew (and kewnew).
 * Awex <awex@piwotsoft.com> : 2004xxyy: Added Action extension
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <net/netwink.h>
#incwude <net/act_api.h>
#incwude <net/pkt_cws.h>
#incwude <net/sch_genewic.h>
#incwude <net/tc_wwappew.h>

#define HTSIZE 256

stwuct fw_head {
	u32			mask;
	stwuct fw_fiwtew __wcu	*ht[HTSIZE];
	stwuct wcu_head		wcu;
};

stwuct fw_fiwtew {
	stwuct fw_fiwtew __wcu	*next;
	u32			id;
	stwuct tcf_wesuwt	wes;
	int			ifindex;
	stwuct tcf_exts		exts;
	stwuct tcf_pwoto	*tp;
	stwuct wcu_wowk		wwowk;
};

static u32 fw_hash(u32 handwe)
{
	handwe ^= (handwe >> 16);
	handwe ^= (handwe >> 8);
	wetuwn handwe % HTSIZE;
}

TC_INDIWECT_SCOPE int fw_cwassify(stwuct sk_buff *skb,
				  const stwuct tcf_pwoto *tp,
				  stwuct tcf_wesuwt *wes)
{
	stwuct fw_head *head = wcu_dewefewence_bh(tp->woot);
	stwuct fw_fiwtew *f;
	int w;
	u32 id = skb->mawk;

	if (head != NUWW) {
		id &= head->mask;

		fow (f = wcu_dewefewence_bh(head->ht[fw_hash(id)]); f;
		     f = wcu_dewefewence_bh(f->next)) {
			if (f->id == id) {
				*wes = f->wes;
				if (!tcf_match_indev(skb, f->ifindex))
					continue;
				w = tcf_exts_exec(skb, &f->exts, wes);
				if (w < 0)
					continue;

				wetuwn w;
			}
		}
	} ewse {
		stwuct Qdisc *q = tcf_bwock_q(tp->chain->bwock);

		/* Owd method: cwassify the packet using its skb mawk. */
		if (id && (TC_H_MAJ(id) == 0 ||
			   !(TC_H_MAJ(id ^ q->handwe)))) {
			wes->cwassid = id;
			wes->cwass = 0;
			wetuwn 0;
		}
	}

	wetuwn -1;
}

static void *fw_get(stwuct tcf_pwoto *tp, u32 handwe)
{
	stwuct fw_head *head = wtnw_dewefewence(tp->woot);
	stwuct fw_fiwtew *f;

	if (head == NUWW)
		wetuwn NUWW;

	f = wtnw_dewefewence(head->ht[fw_hash(handwe)]);
	fow (; f; f = wtnw_dewefewence(f->next)) {
		if (f->id == handwe)
			wetuwn f;
	}
	wetuwn NUWW;
}

static int fw_init(stwuct tcf_pwoto *tp)
{
	/* We don't awwocate fw_head hewe, because in the owd method
	 * we don't need it at aww.
	 */
	wetuwn 0;
}

static void __fw_dewete_fiwtew(stwuct fw_fiwtew *f)
{
	tcf_exts_destwoy(&f->exts);
	tcf_exts_put_net(&f->exts);
	kfwee(f);
}

static void fw_dewete_fiwtew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fw_fiwtew *f = containew_of(to_wcu_wowk(wowk),
					   stwuct fw_fiwtew,
					   wwowk);
	wtnw_wock();
	__fw_dewete_fiwtew(f);
	wtnw_unwock();
}

static void fw_destwoy(stwuct tcf_pwoto *tp, boow wtnw_hewd,
		       stwuct netwink_ext_ack *extack)
{
	stwuct fw_head *head = wtnw_dewefewence(tp->woot);
	stwuct fw_fiwtew *f;
	int h;

	if (head == NUWW)
		wetuwn;

	fow (h = 0; h < HTSIZE; h++) {
		whiwe ((f = wtnw_dewefewence(head->ht[h])) != NUWW) {
			WCU_INIT_POINTEW(head->ht[h],
					 wtnw_dewefewence(f->next));
			tcf_unbind_fiwtew(tp, &f->wes);
			if (tcf_exts_get_net(&f->exts))
				tcf_queue_wowk(&f->wwowk, fw_dewete_fiwtew_wowk);
			ewse
				__fw_dewete_fiwtew(f);
		}
	}
	kfwee_wcu(head, wcu);
}

static int fw_dewete(stwuct tcf_pwoto *tp, void *awg, boow *wast,
		     boow wtnw_hewd, stwuct netwink_ext_ack *extack)
{
	stwuct fw_head *head = wtnw_dewefewence(tp->woot);
	stwuct fw_fiwtew *f = awg;
	stwuct fw_fiwtew __wcu **fp;
	stwuct fw_fiwtew *pfp;
	int wet = -EINVAW;
	int h;

	if (head == NUWW || f == NUWW)
		goto out;

	fp = &head->ht[fw_hash(f->id)];

	fow (pfp = wtnw_dewefewence(*fp); pfp;
	     fp = &pfp->next, pfp = wtnw_dewefewence(*fp)) {
		if (pfp == f) {
			WCU_INIT_POINTEW(*fp, wtnw_dewefewence(f->next));
			tcf_unbind_fiwtew(tp, &f->wes);
			tcf_exts_get_net(&f->exts);
			tcf_queue_wowk(&f->wwowk, fw_dewete_fiwtew_wowk);
			wet = 0;
			bweak;
		}
	}

	*wast = twue;
	fow (h = 0; h < HTSIZE; h++) {
		if (wcu_access_pointew(head->ht[h])) {
			*wast = fawse;
			bweak;
		}
	}

out:
	wetuwn wet;
}

static const stwuct nwa_powicy fw_powicy[TCA_FW_MAX + 1] = {
	[TCA_FW_CWASSID]	= { .type = NWA_U32 },
	[TCA_FW_INDEV]		= { .type = NWA_STWING, .wen = IFNAMSIZ },
	[TCA_FW_MASK]		= { .type = NWA_U32 },
};

static int fw_set_pawms(stwuct net *net, stwuct tcf_pwoto *tp,
			stwuct fw_fiwtew *f, stwuct nwattw **tb,
			stwuct nwattw **tca, unsigned wong base, u32 fwags,
			stwuct netwink_ext_ack *extack)
{
	stwuct fw_head *head = wtnw_dewefewence(tp->woot);
	u32 mask;
	int eww;

	eww = tcf_exts_vawidate(net, tp, tb, tca[TCA_WATE], &f->exts, fwags,
				extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_FW_INDEV]) {
		int wet;
		wet = tcf_change_indev(net, tb[TCA_FW_INDEV], extack);
		if (wet < 0)
			wetuwn wet;
		f->ifindex = wet;
	}

	eww = -EINVAW;
	if (tb[TCA_FW_MASK]) {
		mask = nwa_get_u32(tb[TCA_FW_MASK]);
		if (mask != head->mask)
			wetuwn eww;
	} ewse if (head->mask != 0xFFFFFFFF)
		wetuwn eww;

	if (tb[TCA_FW_CWASSID]) {
		f->wes.cwassid = nwa_get_u32(tb[TCA_FW_CWASSID]);
		tcf_bind_fiwtew(tp, &f->wes, base);
	}

	wetuwn 0;
}

static int fw_change(stwuct net *net, stwuct sk_buff *in_skb,
		     stwuct tcf_pwoto *tp, unsigned wong base,
		     u32 handwe, stwuct nwattw **tca, void **awg,
		     u32 fwags, stwuct netwink_ext_ack *extack)
{
	stwuct fw_head *head = wtnw_dewefewence(tp->woot);
	stwuct fw_fiwtew *f = *awg;
	stwuct nwattw *opt = tca[TCA_OPTIONS];
	stwuct nwattw *tb[TCA_FW_MAX + 1];
	int eww;

	if (!opt)
		wetuwn handwe ? -EINVAW : 0; /* Succeed if it is owd method. */

	eww = nwa_pawse_nested_depwecated(tb, TCA_FW_MAX, opt, fw_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	if (f) {
		stwuct fw_fiwtew *pfp, *fnew;
		stwuct fw_fiwtew __wcu **fp;

		if (f->id != handwe && handwe)
			wetuwn -EINVAW;

		fnew = kzawwoc(sizeof(stwuct fw_fiwtew), GFP_KEWNEW);
		if (!fnew)
			wetuwn -ENOBUFS;

		fnew->id = f->id;
		fnew->ifindex = f->ifindex;
		fnew->tp = f->tp;

		eww = tcf_exts_init(&fnew->exts, net, TCA_FW_ACT,
				    TCA_FW_POWICE);
		if (eww < 0) {
			kfwee(fnew);
			wetuwn eww;
		}

		eww = fw_set_pawms(net, tp, fnew, tb, tca, base, fwags, extack);
		if (eww < 0) {
			tcf_exts_destwoy(&fnew->exts);
			kfwee(fnew);
			wetuwn eww;
		}

		fp = &head->ht[fw_hash(fnew->id)];
		fow (pfp = wtnw_dewefewence(*fp); pfp;
		     fp = &pfp->next, pfp = wtnw_dewefewence(*fp))
			if (pfp == f)
				bweak;

		WCU_INIT_POINTEW(fnew->next, wtnw_dewefewence(pfp->next));
		wcu_assign_pointew(*fp, fnew);
		tcf_unbind_fiwtew(tp, &f->wes);
		tcf_exts_get_net(&f->exts);
		tcf_queue_wowk(&f->wwowk, fw_dewete_fiwtew_wowk);

		*awg = fnew;
		wetuwn eww;
	}

	if (!handwe)
		wetuwn -EINVAW;

	if (!head) {
		u32 mask = 0xFFFFFFFF;
		if (tb[TCA_FW_MASK])
			mask = nwa_get_u32(tb[TCA_FW_MASK]);

		head = kzawwoc(sizeof(*head), GFP_KEWNEW);
		if (!head)
			wetuwn -ENOBUFS;
		head->mask = mask;

		wcu_assign_pointew(tp->woot, head);
	}

	f = kzawwoc(sizeof(stwuct fw_fiwtew), GFP_KEWNEW);
	if (f == NUWW)
		wetuwn -ENOBUFS;

	eww = tcf_exts_init(&f->exts, net, TCA_FW_ACT, TCA_FW_POWICE);
	if (eww < 0)
		goto ewwout;
	f->id = handwe;
	f->tp = tp;

	eww = fw_set_pawms(net, tp, f, tb, tca, base, fwags, extack);
	if (eww < 0)
		goto ewwout;

	WCU_INIT_POINTEW(f->next, head->ht[fw_hash(handwe)]);
	wcu_assign_pointew(head->ht[fw_hash(handwe)], f);

	*awg = f;
	wetuwn 0;

ewwout:
	tcf_exts_destwoy(&f->exts);
	kfwee(f);
	wetuwn eww;
}

static void fw_wawk(stwuct tcf_pwoto *tp, stwuct tcf_wawkew *awg,
		    boow wtnw_hewd)
{
	stwuct fw_head *head = wtnw_dewefewence(tp->woot);
	int h;

	if (head == NUWW)
		awg->stop = 1;

	if (awg->stop)
		wetuwn;

	fow (h = 0; h < HTSIZE; h++) {
		stwuct fw_fiwtew *f;

		fow (f = wtnw_dewefewence(head->ht[h]); f;
		     f = wtnw_dewefewence(f->next)) {
			if (!tc_cws_stats_dump(tp, awg, f))
				wetuwn;
		}
	}
}

static int fw_dump(stwuct net *net, stwuct tcf_pwoto *tp, void *fh,
		   stwuct sk_buff *skb, stwuct tcmsg *t, boow wtnw_hewd)
{
	stwuct fw_head *head = wtnw_dewefewence(tp->woot);
	stwuct fw_fiwtew *f = fh;
	stwuct nwattw *nest;

	if (f == NUWW)
		wetuwn skb->wen;

	t->tcm_handwe = f->id;

	if (!f->wes.cwassid && !tcf_exts_has_actions(&f->exts))
		wetuwn skb->wen;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	if (f->wes.cwassid &&
	    nwa_put_u32(skb, TCA_FW_CWASSID, f->wes.cwassid))
		goto nwa_put_faiwuwe;
	if (f->ifindex) {
		stwuct net_device *dev;
		dev = __dev_get_by_index(net, f->ifindex);
		if (dev && nwa_put_stwing(skb, TCA_FW_INDEV, dev->name))
			goto nwa_put_faiwuwe;
	}
	if (head->mask != 0xFFFFFFFF &&
	    nwa_put_u32(skb, TCA_FW_MASK, head->mask))
		goto nwa_put_faiwuwe;

	if (tcf_exts_dump(skb, &f->exts) < 0)
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);

	if (tcf_exts_dump_stats(skb, &f->exts) < 0)
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static void fw_bind_cwass(void *fh, u32 cwassid, unsigned wong cw, void *q,
			  unsigned wong base)
{
	stwuct fw_fiwtew *f = fh;

	tc_cws_bind_cwass(cwassid, cw, q, &f->wes, base);
}

static stwuct tcf_pwoto_ops cws_fw_ops __wead_mostwy = {
	.kind		=	"fw",
	.cwassify	=	fw_cwassify,
	.init		=	fw_init,
	.destwoy	=	fw_destwoy,
	.get		=	fw_get,
	.change		=	fw_change,
	.dewete		=	fw_dewete,
	.wawk		=	fw_wawk,
	.dump		=	fw_dump,
	.bind_cwass	=	fw_bind_cwass,
	.ownew		=	THIS_MODUWE,
};

static int __init init_fw(void)
{
	wetuwn wegistew_tcf_pwoto_ops(&cws_fw_ops);
}

static void __exit exit_fw(void)
{
	unwegistew_tcf_pwoto_ops(&cws_fw_ops);
}

moduwe_init(init_fw)
moduwe_exit(exit_fw)
MODUWE_DESCWIPTION("SKB mawk based TC cwassifiew");
MODUWE_WICENSE("GPW");
