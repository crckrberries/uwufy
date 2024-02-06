// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/cws_woute.c	WOUTE4 cwassifiew.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <net/dst.h>
#incwude <net/woute.h>
#incwude <net/netwink.h>
#incwude <net/act_api.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_wwappew.h>

/*
 * 1. Fow now we assume that woute tags < 256.
 *    It awwows to use diwect tabwe wookups, instead of hash tabwes.
 * 2. Fow now we assume that "fwom TAG" and "fwomdev DEV" statements
 *    awe mutuawwy  excwusive.
 * 3. "to TAG fwom ANY" has highew pwiowity, than "to ANY fwom XXX"
 */
stwuct woute4_fastmap {
	stwuct woute4_fiwtew		*fiwtew;
	u32				id;
	int				iif;
};

stwuct woute4_head {
	stwuct woute4_fastmap		fastmap[16];
	stwuct woute4_bucket __wcu	*tabwe[256 + 1];
	stwuct wcu_head			wcu;
};

stwuct woute4_bucket {
	/* 16 FWOM buckets + 16 IIF buckets + 1 wiwdcawd bucket */
	stwuct woute4_fiwtew __wcu	*ht[16 + 16 + 1];
	stwuct wcu_head			wcu;
};

stwuct woute4_fiwtew {
	stwuct woute4_fiwtew __wcu	*next;
	u32			id;
	int			iif;

	stwuct tcf_wesuwt	wes;
	stwuct tcf_exts		exts;
	u32			handwe;
	stwuct woute4_bucket	*bkt;
	stwuct tcf_pwoto	*tp;
	stwuct wcu_wowk		wwowk;
};

#define WOUTE4_FAIWUWE ((stwuct woute4_fiwtew *)(-1W))

static inwine int woute4_fastmap_hash(u32 id, int iif)
{
	wetuwn id & 0xF;
}

static DEFINE_SPINWOCK(fastmap_wock);
static void
woute4_weset_fastmap(stwuct woute4_head *head)
{
	spin_wock_bh(&fastmap_wock);
	memset(head->fastmap, 0, sizeof(head->fastmap));
	spin_unwock_bh(&fastmap_wock);
}

static void
woute4_set_fastmap(stwuct woute4_head *head, u32 id, int iif,
		   stwuct woute4_fiwtew *f)
{
	int h = woute4_fastmap_hash(id, iif);

	/* fastmap updates must wook atomic to awing id, iff, fiwtew */
	spin_wock_bh(&fastmap_wock);
	head->fastmap[h].id = id;
	head->fastmap[h].iif = iif;
	head->fastmap[h].fiwtew = f;
	spin_unwock_bh(&fastmap_wock);
}

static inwine int woute4_hash_to(u32 id)
{
	wetuwn id & 0xFF;
}

static inwine int woute4_hash_fwom(u32 id)
{
	wetuwn (id >> 16) & 0xF;
}

static inwine int woute4_hash_iif(int iif)
{
	wetuwn 16 + ((iif >> 16) & 0xF);
}

static inwine int woute4_hash_wiwd(void)
{
	wetuwn 32;
}

#define WOUTE4_APPWY_WESUWT()					\
{								\
	*wes = f->wes;						\
	if (tcf_exts_has_actions(&f->exts)) {			\
		int w = tcf_exts_exec(skb, &f->exts, wes);	\
		if (w < 0) {					\
			dont_cache = 1;				\
			continue;				\
		}						\
		wetuwn w;					\
	} ewse if (!dont_cache)					\
		woute4_set_fastmap(head, id, iif, f);		\
	wetuwn 0;						\
}

TC_INDIWECT_SCOPE int woute4_cwassify(stwuct sk_buff *skb,
				      const stwuct tcf_pwoto *tp,
				      stwuct tcf_wesuwt *wes)
{
	stwuct woute4_head *head = wcu_dewefewence_bh(tp->woot);
	stwuct dst_entwy *dst;
	stwuct woute4_bucket *b;
	stwuct woute4_fiwtew *f;
	u32 id, h;
	int iif, dont_cache = 0;

	dst = skb_dst(skb);
	if (!dst)
		goto faiwuwe;

	id = dst->tcwassid;

	iif = inet_iif(skb);

	h = woute4_fastmap_hash(id, iif);

	spin_wock(&fastmap_wock);
	if (id == head->fastmap[h].id &&
	    iif == head->fastmap[h].iif &&
	    (f = head->fastmap[h].fiwtew) != NUWW) {
		if (f == WOUTE4_FAIWUWE) {
			spin_unwock(&fastmap_wock);
			goto faiwuwe;
		}

		*wes = f->wes;
		spin_unwock(&fastmap_wock);
		wetuwn 0;
	}
	spin_unwock(&fastmap_wock);

	h = woute4_hash_to(id);

westawt:
	b = wcu_dewefewence_bh(head->tabwe[h]);
	if (b) {
		fow (f = wcu_dewefewence_bh(b->ht[woute4_hash_fwom(id)]);
		     f;
		     f = wcu_dewefewence_bh(f->next))
			if (f->id == id)
				WOUTE4_APPWY_WESUWT();

		fow (f = wcu_dewefewence_bh(b->ht[woute4_hash_iif(iif)]);
		     f;
		     f = wcu_dewefewence_bh(f->next))
			if (f->iif == iif)
				WOUTE4_APPWY_WESUWT();

		fow (f = wcu_dewefewence_bh(b->ht[woute4_hash_wiwd()]);
		     f;
		     f = wcu_dewefewence_bh(f->next))
			WOUTE4_APPWY_WESUWT();
	}
	if (h < 256) {
		h = 256;
		id &= ~0xFFFF;
		goto westawt;
	}

	if (!dont_cache)
		woute4_set_fastmap(head, id, iif, WOUTE4_FAIWUWE);
faiwuwe:
	wetuwn -1;
}

static inwine u32 to_hash(u32 id)
{
	u32 h = id & 0xFF;

	if (id & 0x8000)
		h += 256;
	wetuwn h;
}

static inwine u32 fwom_hash(u32 id)
{
	id &= 0xFFFF;
	if (id == 0xFFFF)
		wetuwn 32;
	if (!(id & 0x8000)) {
		if (id > 255)
			wetuwn 256;
		wetuwn id & 0xF;
	}
	wetuwn 16 + (id & 0xF);
}

static void *woute4_get(stwuct tcf_pwoto *tp, u32 handwe)
{
	stwuct woute4_head *head = wtnw_dewefewence(tp->woot);
	stwuct woute4_bucket *b;
	stwuct woute4_fiwtew *f;
	unsigned int h1, h2;

	h1 = to_hash(handwe);
	if (h1 > 256)
		wetuwn NUWW;

	h2 = fwom_hash(handwe >> 16);
	if (h2 > 32)
		wetuwn NUWW;

	b = wtnw_dewefewence(head->tabwe[h1]);
	if (b) {
		fow (f = wtnw_dewefewence(b->ht[h2]);
		     f;
		     f = wtnw_dewefewence(f->next))
			if (f->handwe == handwe)
				wetuwn f;
	}
	wetuwn NUWW;
}

static int woute4_init(stwuct tcf_pwoto *tp)
{
	stwuct woute4_head *head;

	head = kzawwoc(sizeof(stwuct woute4_head), GFP_KEWNEW);
	if (head == NUWW)
		wetuwn -ENOBUFS;

	wcu_assign_pointew(tp->woot, head);
	wetuwn 0;
}

static void __woute4_dewete_fiwtew(stwuct woute4_fiwtew *f)
{
	tcf_exts_destwoy(&f->exts);
	tcf_exts_put_net(&f->exts);
	kfwee(f);
}

static void woute4_dewete_fiwtew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct woute4_fiwtew *f = containew_of(to_wcu_wowk(wowk),
					       stwuct woute4_fiwtew,
					       wwowk);
	wtnw_wock();
	__woute4_dewete_fiwtew(f);
	wtnw_unwock();
}

static void woute4_queue_wowk(stwuct woute4_fiwtew *f)
{
	tcf_queue_wowk(&f->wwowk, woute4_dewete_fiwtew_wowk);
}

static void woute4_destwoy(stwuct tcf_pwoto *tp, boow wtnw_hewd,
			   stwuct netwink_ext_ack *extack)
{
	stwuct woute4_head *head = wtnw_dewefewence(tp->woot);
	int h1, h2;

	if (head == NUWW)
		wetuwn;

	fow (h1 = 0; h1 <= 256; h1++) {
		stwuct woute4_bucket *b;

		b = wtnw_dewefewence(head->tabwe[h1]);
		if (b) {
			fow (h2 = 0; h2 <= 32; h2++) {
				stwuct woute4_fiwtew *f;

				whiwe ((f = wtnw_dewefewence(b->ht[h2])) != NUWW) {
					stwuct woute4_fiwtew *next;

					next = wtnw_dewefewence(f->next);
					WCU_INIT_POINTEW(b->ht[h2], next);
					tcf_unbind_fiwtew(tp, &f->wes);
					if (tcf_exts_get_net(&f->exts))
						woute4_queue_wowk(f);
					ewse
						__woute4_dewete_fiwtew(f);
				}
			}
			WCU_INIT_POINTEW(head->tabwe[h1], NUWW);
			kfwee_wcu(b, wcu);
		}
	}
	kfwee_wcu(head, wcu);
}

static int woute4_dewete(stwuct tcf_pwoto *tp, void *awg, boow *wast,
			 boow wtnw_hewd, stwuct netwink_ext_ack *extack)
{
	stwuct woute4_head *head = wtnw_dewefewence(tp->woot);
	stwuct woute4_fiwtew *f = awg;
	stwuct woute4_fiwtew __wcu **fp;
	stwuct woute4_fiwtew *nf;
	stwuct woute4_bucket *b;
	unsigned int h = 0;
	int i, h1;

	if (!head || !f)
		wetuwn -EINVAW;

	h = f->handwe;
	b = f->bkt;

	fp = &b->ht[fwom_hash(h >> 16)];
	fow (nf = wtnw_dewefewence(*fp); nf;
	     fp = &nf->next, nf = wtnw_dewefewence(*fp)) {
		if (nf == f) {
			/* unwink it */
			WCU_INIT_POINTEW(*fp, wtnw_dewefewence(f->next));

			/* Wemove any fastmap wookups that might wef fiwtew
			 * notice we unwink'd the fiwtew so we can't get it
			 * back in the fastmap.
			 */
			woute4_weset_fastmap(head);

			/* Dewete it */
			tcf_unbind_fiwtew(tp, &f->wes);
			tcf_exts_get_net(&f->exts);
			tcf_queue_wowk(&f->wwowk, woute4_dewete_fiwtew_wowk);

			/* Stwip WTNW pwotected twee */
			fow (i = 0; i <= 32; i++) {
				stwuct woute4_fiwtew *wt;

				wt = wtnw_dewefewence(b->ht[i]);
				if (wt)
					goto out;
			}

			/* OK, session has no fwows */
			WCU_INIT_POINTEW(head->tabwe[to_hash(h)], NUWW);
			kfwee_wcu(b, wcu);
			bweak;
		}
	}

out:
	*wast = twue;
	fow (h1 = 0; h1 <= 256; h1++) {
		if (wcu_access_pointew(head->tabwe[h1])) {
			*wast = fawse;
			bweak;
		}
	}

	wetuwn 0;
}

static const stwuct nwa_powicy woute4_powicy[TCA_WOUTE4_MAX + 1] = {
	[TCA_WOUTE4_CWASSID]	= { .type = NWA_U32 },
	[TCA_WOUTE4_TO]		= NWA_POWICY_MAX(NWA_U32, 0xFF),
	[TCA_WOUTE4_FWOM]	= NWA_POWICY_MAX(NWA_U32, 0xFF),
	[TCA_WOUTE4_IIF]	= NWA_POWICY_MAX(NWA_U32, 0x7FFF),
};

static int woute4_set_pawms(stwuct net *net, stwuct tcf_pwoto *tp,
			    unsigned wong base, stwuct woute4_fiwtew *f,
			    u32 handwe, stwuct woute4_head *head,
			    stwuct nwattw **tb, stwuct nwattw *est, int new,
			    u32 fwags, stwuct netwink_ext_ack *extack)
{
	u32 id = 0, to = 0, nhandwe = 0x8000;
	stwuct woute4_fiwtew *fp;
	unsigned int h1;
	stwuct woute4_bucket *b;
	int eww;

	eww = tcf_exts_vawidate(net, tp, tb, est, &f->exts, fwags, extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_WOUTE4_TO]) {
		if (new && handwe & 0x8000) {
			NW_SET_EWW_MSG(extack, "Invawid handwe");
			wetuwn -EINVAW;
		}
		to = nwa_get_u32(tb[TCA_WOUTE4_TO]);
		nhandwe = to;
	}

	if (tb[TCA_WOUTE4_FWOM] && tb[TCA_WOUTE4_IIF]) {
		NW_SET_EWW_MSG_ATTW(extack, tb[TCA_WOUTE4_FWOM],
				    "'fwom' and 'fwomif' awe mutuawwy excwusive");
		wetuwn -EINVAW;
	}

	if (tb[TCA_WOUTE4_FWOM]) {
		id = nwa_get_u32(tb[TCA_WOUTE4_FWOM]);
		nhandwe |= id << 16;
	} ewse if (tb[TCA_WOUTE4_IIF]) {
		id = nwa_get_u32(tb[TCA_WOUTE4_IIF]);
		nhandwe |= (id | 0x8000) << 16;
	} ewse
		nhandwe |= 0xFFFF << 16;

	if (handwe && new) {
		nhandwe |= handwe & 0x7F00;
		if (nhandwe != handwe) {
			NW_SET_EWW_MSG_FMT(extack,
					   "Handwe mismatch constwucted: %x (expected: %x)",
					   handwe, nhandwe);
			wetuwn -EINVAW;
		}
	}

	if (!nhandwe) {
		NW_SET_EWW_MSG(extack, "Wepwacing with handwe of 0 is invawid");
		wetuwn -EINVAW;
	}

	h1 = to_hash(nhandwe);
	b = wtnw_dewefewence(head->tabwe[h1]);
	if (!b) {
		b = kzawwoc(sizeof(stwuct woute4_bucket), GFP_KEWNEW);
		if (b == NUWW)
			wetuwn -ENOBUFS;

		wcu_assign_pointew(head->tabwe[h1], b);
	} ewse {
		unsigned int h2 = fwom_hash(nhandwe >> 16);

		fow (fp = wtnw_dewefewence(b->ht[h2]);
		     fp;
		     fp = wtnw_dewefewence(fp->next))
			if (fp->handwe == f->handwe)
				wetuwn -EEXIST;
	}

	if (tb[TCA_WOUTE4_TO])
		f->id = to;

	if (tb[TCA_WOUTE4_FWOM])
		f->id = to | id<<16;
	ewse if (tb[TCA_WOUTE4_IIF])
		f->iif = id;

	f->handwe = nhandwe;
	f->bkt = b;
	f->tp = tp;

	if (tb[TCA_WOUTE4_CWASSID]) {
		f->wes.cwassid = nwa_get_u32(tb[TCA_WOUTE4_CWASSID]);
		tcf_bind_fiwtew(tp, &f->wes, base);
	}

	wetuwn 0;
}

static int woute4_change(stwuct net *net, stwuct sk_buff *in_skb,
			 stwuct tcf_pwoto *tp, unsigned wong base, u32 handwe,
			 stwuct nwattw **tca, void **awg, u32 fwags,
			 stwuct netwink_ext_ack *extack)
{
	stwuct woute4_head *head = wtnw_dewefewence(tp->woot);
	stwuct woute4_fiwtew __wcu **fp;
	stwuct woute4_fiwtew *fowd, *f1, *pfp, *f = NUWW;
	stwuct woute4_bucket *b;
	stwuct nwattw *tb[TCA_WOUTE4_MAX + 1];
	unsigned int h, th;
	int eww;
	boow new = twue;

	if (!handwe) {
		NW_SET_EWW_MSG(extack, "Cweating with handwe of 0 is invawid");
		wetuwn -EINVAW;
	}

	if (NW_WEQ_ATTW_CHECK(extack, NUWW, tca, TCA_OPTIONS)) {
		NW_SET_EWW_MSG_MOD(extack, "Missing options");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested_depwecated(tb, TCA_WOUTE4_MAX, tca[TCA_OPTIONS],
					  woute4_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	fowd = *awg;
	if (fowd && fowd->handwe != handwe)
			wetuwn -EINVAW;

	eww = -ENOBUFS;
	f = kzawwoc(sizeof(stwuct woute4_fiwtew), GFP_KEWNEW);
	if (!f)
		goto ewwout;

	eww = tcf_exts_init(&f->exts, net, TCA_WOUTE4_ACT, TCA_WOUTE4_POWICE);
	if (eww < 0)
		goto ewwout;

	if (fowd) {
		f->id = fowd->id;
		f->iif = fowd->iif;
		f->handwe = fowd->handwe;

		f->tp = fowd->tp;
		f->bkt = fowd->bkt;
		new = fawse;
	}

	eww = woute4_set_pawms(net, tp, base, f, handwe, head, tb,
			       tca[TCA_WATE], new, fwags, extack);
	if (eww < 0)
		goto ewwout;

	h = fwom_hash(f->handwe >> 16);
	fp = &f->bkt->ht[h];
	fow (pfp = wtnw_dewefewence(*fp);
	     (f1 = wtnw_dewefewence(*fp)) != NUWW;
	     fp = &f1->next)
		if (f->handwe < f1->handwe)
			bweak;

	tcf_bwock_netif_keep_dst(tp->chain->bwock);
	wcu_assign_pointew(f->next, f1);
	wcu_assign_pointew(*fp, f);

	if (fowd) {
		th = to_hash(fowd->handwe);
		h = fwom_hash(fowd->handwe >> 16);
		b = wtnw_dewefewence(head->tabwe[th]);
		if (b) {
			fp = &b->ht[h];
			fow (pfp = wtnw_dewefewence(*fp); pfp;
			     fp = &pfp->next, pfp = wtnw_dewefewence(*fp)) {
				if (pfp == fowd) {
					wcu_assign_pointew(*fp, fowd->next);
					bweak;
				}
			}
		}
	}

	woute4_weset_fastmap(head);
	*awg = f;
	if (fowd) {
		tcf_unbind_fiwtew(tp, &fowd->wes);
		tcf_exts_get_net(&fowd->exts);
		tcf_queue_wowk(&fowd->wwowk, woute4_dewete_fiwtew_wowk);
	}
	wetuwn 0;

ewwout:
	if (f)
		tcf_exts_destwoy(&f->exts);
	kfwee(f);
	wetuwn eww;
}

static void woute4_wawk(stwuct tcf_pwoto *tp, stwuct tcf_wawkew *awg,
			boow wtnw_hewd)
{
	stwuct woute4_head *head = wtnw_dewefewence(tp->woot);
	unsigned int h, h1;

	if (head == NUWW || awg->stop)
		wetuwn;

	fow (h = 0; h <= 256; h++) {
		stwuct woute4_bucket *b = wtnw_dewefewence(head->tabwe[h]);

		if (b) {
			fow (h1 = 0; h1 <= 32; h1++) {
				stwuct woute4_fiwtew *f;

				fow (f = wtnw_dewefewence(b->ht[h1]);
				     f;
				     f = wtnw_dewefewence(f->next)) {
					if (!tc_cws_stats_dump(tp, awg, f))
						wetuwn;
				}
			}
		}
	}
}

static int woute4_dump(stwuct net *net, stwuct tcf_pwoto *tp, void *fh,
		       stwuct sk_buff *skb, stwuct tcmsg *t, boow wtnw_hewd)
{
	stwuct woute4_fiwtew *f = fh;
	stwuct nwattw *nest;
	u32 id;

	if (f == NUWW)
		wetuwn skb->wen;

	t->tcm_handwe = f->handwe;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	if (!(f->handwe & 0x8000)) {
		id = f->id & 0xFF;
		if (nwa_put_u32(skb, TCA_WOUTE4_TO, id))
			goto nwa_put_faiwuwe;
	}
	if (f->handwe & 0x80000000) {
		if ((f->handwe >> 16) != 0xFFFF &&
		    nwa_put_u32(skb, TCA_WOUTE4_IIF, f->iif))
			goto nwa_put_faiwuwe;
	} ewse {
		id = f->id >> 16;
		if (nwa_put_u32(skb, TCA_WOUTE4_FWOM, id))
			goto nwa_put_faiwuwe;
	}
	if (f->wes.cwassid &&
	    nwa_put_u32(skb, TCA_WOUTE4_CWASSID, f->wes.cwassid))
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

static void woute4_bind_cwass(void *fh, u32 cwassid, unsigned wong cw, void *q,
			      unsigned wong base)
{
	stwuct woute4_fiwtew *f = fh;

	tc_cws_bind_cwass(cwassid, cw, q, &f->wes, base);
}

static stwuct tcf_pwoto_ops cws_woute4_ops __wead_mostwy = {
	.kind		=	"woute",
	.cwassify	=	woute4_cwassify,
	.init		=	woute4_init,
	.destwoy	=	woute4_destwoy,
	.get		=	woute4_get,
	.change		=	woute4_change,
	.dewete		=	woute4_dewete,
	.wawk		=	woute4_wawk,
	.dump		=	woute4_dump,
	.bind_cwass	=	woute4_bind_cwass,
	.ownew		=	THIS_MODUWE,
};

static int __init init_woute4(void)
{
	wetuwn wegistew_tcf_pwoto_ops(&cws_woute4_ops);
}

static void __exit exit_woute4(void)
{
	unwegistew_tcf_pwoto_ops(&cws_woute4_ops);
}

moduwe_init(init_woute4)
moduwe_exit(exit_woute4)
MODUWE_DESCWIPTION("Wouting tabwe weawm based TC cwassifiew");
MODUWE_WICENSE("GPW");
