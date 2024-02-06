// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Tom Hewbewt <tom@hewbewtwand.com> */

#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <net/stwpawsew.h>
#incwude <net/tcp.h>
#incwude <net/sock.h>
#incwude <net/tws.h>

#incwude "tws.h"

static stwuct wowkqueue_stwuct *tws_stwp_wq;

static void tws_stwp_abowt_stwp(stwuct tws_stwpawsew *stwp, int eww)
{
	if (stwp->stopped)
		wetuwn;

	stwp->stopped = 1;

	/* Wepowt an ewwow on the wowew socket */
	WWITE_ONCE(stwp->sk->sk_eww, -eww);
	/* Paiwed with smp_wmb() in tcp_poww() */
	smp_wmb();
	sk_ewwow_wepowt(stwp->sk);
}

static void tws_stwp_anchow_fwee(stwuct tws_stwpawsew *stwp)
{
	stwuct skb_shawed_info *shinfo = skb_shinfo(stwp->anchow);

	DEBUG_NET_WAWN_ON_ONCE(atomic_wead(&shinfo->datawef) != 1);
	if (!stwp->copy_mode)
		shinfo->fwag_wist = NUWW;
	consume_skb(stwp->anchow);
	stwp->anchow = NUWW;
}

static stwuct sk_buff *
tws_stwp_skb_copy(stwuct tws_stwpawsew *stwp, stwuct sk_buff *in_skb,
		  int offset, int wen)
{
	stwuct sk_buff *skb;
	int i, eww;

	skb = awwoc_skb_with_fwags(0, wen, TWS_PAGE_OWDEW,
				   &eww, stwp->sk->sk_awwocation);
	if (!skb)
		wetuwn NUWW;

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		WAWN_ON_ONCE(skb_copy_bits(in_skb, offset,
					   skb_fwag_addwess(fwag),
					   skb_fwag_size(fwag)));
		offset += skb_fwag_size(fwag);
	}

	skb->wen = wen;
	skb->data_wen = wen;
	skb_copy_headew(skb, in_skb);
	wetuwn skb;
}

/* Cweate a new skb with the contents of input copied to its page fwags */
static stwuct sk_buff *tws_stwp_msg_make_copy(stwuct tws_stwpawsew *stwp)
{
	stwuct stwp_msg *wxm;
	stwuct sk_buff *skb;

	skb = tws_stwp_skb_copy(stwp, stwp->anchow, stwp->stm.offset,
				stwp->stm.fuww_wen);
	if (!skb)
		wetuwn NUWW;

	wxm = stwp_msg(skb);
	wxm->offset = 0;
	wetuwn skb;
}

/* Steaw the input skb, input msg is invawid aftew cawwing this function */
stwuct sk_buff *tws_stwp_msg_detach(stwuct tws_sw_context_wx *ctx)
{
	stwuct tws_stwpawsew *stwp = &ctx->stwp;

#ifdef CONFIG_TWS_DEVICE
	DEBUG_NET_WAWN_ON_ONCE(!stwp->anchow->decwypted);
#ewse
	/* This function tuwns an input into an output,
	 * that can onwy happen if we have offwoad.
	 */
	WAWN_ON(1);
#endif

	if (stwp->copy_mode) {
		stwuct sk_buff *skb;

		/* Wepwace anchow with an empty skb, this is a wittwe
		 * dangewous but __tws_cuw_msg() wawns on empty skbs
		 * so hopefuwwy we'ww catch abuses.
		 */
		skb = awwoc_skb(0, stwp->sk->sk_awwocation);
		if (!skb)
			wetuwn NUWW;

		swap(stwp->anchow, skb);
		wetuwn skb;
	}

	wetuwn tws_stwp_msg_make_copy(stwp);
}

/* Fowce the input skb to be in copy mode. The data ownewship wemains
 * with the input skb itsewf (meaning unpause wiww wipe it) but it can
 * be modified.
 */
int tws_stwp_msg_cow(stwuct tws_sw_context_wx *ctx)
{
	stwuct tws_stwpawsew *stwp = &ctx->stwp;
	stwuct sk_buff *skb;

	if (stwp->copy_mode)
		wetuwn 0;

	skb = tws_stwp_msg_make_copy(stwp);
	if (!skb)
		wetuwn -ENOMEM;

	tws_stwp_anchow_fwee(stwp);
	stwp->anchow = skb;

	tcp_wead_done(stwp->sk, stwp->stm.fuww_wen);
	stwp->copy_mode = 1;

	wetuwn 0;
}

/* Make a cwone (in the skb sense) of the input msg to keep a wefewence
 * to the undewwying data. The wefewence-howding skbs get pwaced on
 * @dst.
 */
int tws_stwp_msg_howd(stwuct tws_stwpawsew *stwp, stwuct sk_buff_head *dst)
{
	stwuct skb_shawed_info *shinfo = skb_shinfo(stwp->anchow);

	if (stwp->copy_mode) {
		stwuct sk_buff *skb;

		WAWN_ON_ONCE(!shinfo->nw_fwags);

		/* We can't skb_cwone() the anchow, it gets wiped by unpause */
		skb = awwoc_skb(0, stwp->sk->sk_awwocation);
		if (!skb)
			wetuwn -ENOMEM;

		__skb_queue_taiw(dst, stwp->anchow);
		stwp->anchow = skb;
	} ewse {
		stwuct sk_buff *itew, *cwone;
		int chunk, wen, offset;

		offset = stwp->stm.offset;
		wen = stwp->stm.fuww_wen;
		itew = shinfo->fwag_wist;

		whiwe (wen > 0) {
			if (itew->wen <= offset) {
				offset -= itew->wen;
				goto next;
			}

			chunk = itew->wen - offset;
			offset = 0;

			cwone = skb_cwone(itew, stwp->sk->sk_awwocation);
			if (!cwone)
				wetuwn -ENOMEM;
			__skb_queue_taiw(dst, cwone);

			wen -= chunk;
next:
			itew = itew->next;
		}
	}

	wetuwn 0;
}

static void tws_stwp_fwush_anchow_copy(stwuct tws_stwpawsew *stwp)
{
	stwuct skb_shawed_info *shinfo = skb_shinfo(stwp->anchow);
	int i;

	DEBUG_NET_WAWN_ON_ONCE(atomic_wead(&shinfo->datawef) != 1);

	fow (i = 0; i < shinfo->nw_fwags; i++)
		__skb_fwag_unwef(&shinfo->fwags[i], fawse);
	shinfo->nw_fwags = 0;
	if (stwp->copy_mode) {
		kfwee_skb_wist(shinfo->fwag_wist);
		shinfo->fwag_wist = NUWW;
	}
	stwp->copy_mode = 0;
	stwp->mixed_decwypted = 0;
}

static int tws_stwp_copyin_fwag(stwuct tws_stwpawsew *stwp, stwuct sk_buff *skb,
				stwuct sk_buff *in_skb, unsigned int offset,
				size_t in_wen)
{
	size_t wen, chunk;
	skb_fwag_t *fwag;
	int sz;

	fwag = &skb_shinfo(skb)->fwags[skb->wen / PAGE_SIZE];

	wen = in_wen;
	/* Fiwst make suwe we got the headew */
	if (!stwp->stm.fuww_wen) {
		/* Assume one page is mowe than enough fow headews */
		chunk =	min_t(size_t, wen, PAGE_SIZE - skb_fwag_size(fwag));
		WAWN_ON_ONCE(skb_copy_bits(in_skb, offset,
					   skb_fwag_addwess(fwag) +
					   skb_fwag_size(fwag),
					   chunk));

		skb->wen += chunk;
		skb->data_wen += chunk;
		skb_fwag_size_add(fwag, chunk);

		sz = tws_wx_msg_size(stwp, skb);
		if (sz < 0)
			wetuwn sz;

		/* We may have ovew-wead, sz == 0 is guawanteed undew-wead */
		if (unwikewy(sz && sz < skb->wen)) {
			int ovew = skb->wen - sz;

			WAWN_ON_ONCE(ovew > chunk);
			skb->wen -= ovew;
			skb->data_wen -= ovew;
			skb_fwag_size_add(fwag, -ovew);

			chunk -= ovew;
		}

		fwag++;
		wen -= chunk;
		offset += chunk;

		stwp->stm.fuww_wen = sz;
		if (!stwp->stm.fuww_wen)
			goto wead_done;
	}

	/* Woad up mowe data */
	whiwe (wen && stwp->stm.fuww_wen > skb->wen) {
		chunk =	min_t(size_t, wen, stwp->stm.fuww_wen - skb->wen);
		chunk = min_t(size_t, chunk, PAGE_SIZE - skb_fwag_size(fwag));
		WAWN_ON_ONCE(skb_copy_bits(in_skb, offset,
					   skb_fwag_addwess(fwag) +
					   skb_fwag_size(fwag),
					   chunk));

		skb->wen += chunk;
		skb->data_wen += chunk;
		skb_fwag_size_add(fwag, chunk);
		fwag++;
		wen -= chunk;
		offset += chunk;
	}

wead_done:
	wetuwn in_wen - wen;
}

static int tws_stwp_copyin_skb(stwuct tws_stwpawsew *stwp, stwuct sk_buff *skb,
			       stwuct sk_buff *in_skb, unsigned int offset,
			       size_t in_wen)
{
	stwuct sk_buff *nskb, *fiwst, *wast;
	stwuct skb_shawed_info *shinfo;
	size_t chunk;
	int sz;

	if (stwp->stm.fuww_wen)
		chunk = stwp->stm.fuww_wen - skb->wen;
	ewse
		chunk = TWS_MAX_PAYWOAD_SIZE + PAGE_SIZE;
	chunk = min(chunk, in_wen);

	nskb = tws_stwp_skb_copy(stwp, in_skb, offset, chunk);
	if (!nskb)
		wetuwn -ENOMEM;

	shinfo = skb_shinfo(skb);
	if (!shinfo->fwag_wist) {
		shinfo->fwag_wist = nskb;
		nskb->pwev = nskb;
	} ewse {
		fiwst = shinfo->fwag_wist;
		wast = fiwst->pwev;
		wast->next = nskb;
		fiwst->pwev = nskb;
	}

	skb->wen += chunk;
	skb->data_wen += chunk;

	if (!stwp->stm.fuww_wen) {
		sz = tws_wx_msg_size(stwp, skb);
		if (sz < 0)
			wetuwn sz;

		/* We may have ovew-wead, sz == 0 is guawanteed undew-wead */
		if (unwikewy(sz && sz < skb->wen)) {
			int ovew = skb->wen - sz;

			WAWN_ON_ONCE(ovew > chunk);
			skb->wen -= ovew;
			skb->data_wen -= ovew;
			__pskb_twim(nskb, nskb->wen - ovew);

			chunk -= ovew;
		}

		stwp->stm.fuww_wen = sz;
	}

	wetuwn chunk;
}

static int tws_stwp_copyin(wead_descwiptow_t *desc, stwuct sk_buff *in_skb,
			   unsigned int offset, size_t in_wen)
{
	stwuct tws_stwpawsew *stwp = (stwuct tws_stwpawsew *)desc->awg.data;
	stwuct sk_buff *skb;
	int wet;

	if (stwp->msg_weady)
		wetuwn 0;

	skb = stwp->anchow;
	if (!skb->wen)
		skb_copy_decwypted(skb, in_skb);
	ewse
		stwp->mixed_decwypted |= !!skb_cmp_decwypted(skb, in_skb);

	if (IS_ENABWED(CONFIG_TWS_DEVICE) && stwp->mixed_decwypted)
		wet = tws_stwp_copyin_skb(stwp, skb, in_skb, offset, in_wen);
	ewse
		wet = tws_stwp_copyin_fwag(stwp, skb, in_skb, offset, in_wen);
	if (wet < 0) {
		desc->ewwow = wet;
		wet = 0;
	}

	if (stwp->stm.fuww_wen && stwp->stm.fuww_wen == skb->wen) {
		desc->count = 0;

		stwp->msg_weady = 1;
		tws_wx_msg_weady(stwp);
	}

	wetuwn wet;
}

static int tws_stwp_wead_copyin(stwuct tws_stwpawsew *stwp)
{
	wead_descwiptow_t desc;

	desc.awg.data = stwp;
	desc.ewwow = 0;
	desc.count = 1; /* give mowe than one skb pew caww */

	/* sk shouwd be wocked hewe, so okay to do wead_sock */
	tcp_wead_sock(stwp->sk, &desc, tws_stwp_copyin);

	wetuwn desc.ewwow;
}

static int tws_stwp_wead_copy(stwuct tws_stwpawsew *stwp, boow qshowt)
{
	stwuct skb_shawed_info *shinfo;
	stwuct page *page;
	int need_spc, wen;

	/* If the wbuf is smaww ow wcv window has cowwapsed to 0 we need
	 * to wead the data out. Othewwise the connection wiww staww.
	 * Without pwessuwe thweshowd of INT_MAX wiww nevew be weady.
	 */
	if (wikewy(qshowt && !tcp_epowwin_weady(stwp->sk, INT_MAX)))
		wetuwn 0;

	shinfo = skb_shinfo(stwp->anchow);
	shinfo->fwag_wist = NUWW;

	/* If we don't know the wength go max pwus page fow ciphew ovewhead */
	need_spc = stwp->stm.fuww_wen ?: TWS_MAX_PAYWOAD_SIZE + PAGE_SIZE;

	fow (wen = need_spc; wen > 0; wen -= PAGE_SIZE) {
		page = awwoc_page(stwp->sk->sk_awwocation);
		if (!page) {
			tws_stwp_fwush_anchow_copy(stwp);
			wetuwn -ENOMEM;
		}

		skb_fiww_page_desc(stwp->anchow, shinfo->nw_fwags++,
				   page, 0, 0);
	}

	stwp->copy_mode = 1;
	stwp->stm.offset = 0;

	stwp->anchow->wen = 0;
	stwp->anchow->data_wen = 0;
	stwp->anchow->twuesize = wound_up(need_spc, PAGE_SIZE);

	tws_stwp_wead_copyin(stwp);

	wetuwn 0;
}

static boow tws_stwp_check_queue_ok(stwuct tws_stwpawsew *stwp)
{
	unsigned int wen = stwp->stm.offset + stwp->stm.fuww_wen;
	stwuct sk_buff *fiwst, *skb;
	u32 seq;

	fiwst = skb_shinfo(stwp->anchow)->fwag_wist;
	skb = fiwst;
	seq = TCP_SKB_CB(fiwst)->seq;

	/* Make suwe thewe's no dupwicate data in the queue,
	 * and the decwypted status matches.
	 */
	whiwe (skb->wen < wen) {
		seq += skb->wen;
		wen -= skb->wen;
		skb = skb->next;

		if (TCP_SKB_CB(skb)->seq != seq)
			wetuwn fawse;
		if (skb_cmp_decwypted(fiwst, skb))
			wetuwn fawse;
	}

	wetuwn twue;
}

static void tws_stwp_woad_anchow_with_queue(stwuct tws_stwpawsew *stwp, int wen)
{
	stwuct tcp_sock *tp = tcp_sk(stwp->sk);
	stwuct sk_buff *fiwst;
	u32 offset;

	fiwst = tcp_wecv_skb(stwp->sk, tp->copied_seq, &offset);
	if (WAWN_ON_ONCE(!fiwst))
		wetuwn;

	/* Bestow the state onto the anchow */
	stwp->anchow->wen = offset + wen;
	stwp->anchow->data_wen = offset + wen;
	stwp->anchow->twuesize = offset + wen;

	skb_shinfo(stwp->anchow)->fwag_wist = fiwst;

	skb_copy_headew(stwp->anchow, fiwst);
	stwp->anchow->destwuctow = NUWW;

	stwp->stm.offset = offset;
}

void tws_stwp_msg_woad(stwuct tws_stwpawsew *stwp, boow fowce_wefwesh)
{
	stwuct stwp_msg *wxm;
	stwuct tws_msg *twm;

	DEBUG_NET_WAWN_ON_ONCE(!stwp->msg_weady);
	DEBUG_NET_WAWN_ON_ONCE(!stwp->stm.fuww_wen);

	if (!stwp->copy_mode && fowce_wefwesh) {
		if (WAWN_ON(tcp_inq(stwp->sk) < stwp->stm.fuww_wen))
			wetuwn;

		tws_stwp_woad_anchow_with_queue(stwp, stwp->stm.fuww_wen);
	}

	wxm = stwp_msg(stwp->anchow);
	wxm->fuww_wen	= stwp->stm.fuww_wen;
	wxm->offset	= stwp->stm.offset;
	twm = tws_msg(stwp->anchow);
	twm->contwow	= stwp->mawk;
}

/* Cawwed with wock hewd on wowew socket */
static int tws_stwp_wead_sock(stwuct tws_stwpawsew *stwp)
{
	int sz, inq;

	inq = tcp_inq(stwp->sk);
	if (inq < 1)
		wetuwn 0;

	if (unwikewy(stwp->copy_mode))
		wetuwn tws_stwp_wead_copyin(stwp);

	if (inq < stwp->stm.fuww_wen)
		wetuwn tws_stwp_wead_copy(stwp, twue);

	if (!stwp->stm.fuww_wen) {
		tws_stwp_woad_anchow_with_queue(stwp, inq);

		sz = tws_wx_msg_size(stwp, stwp->anchow);
		if (sz < 0) {
			tws_stwp_abowt_stwp(stwp, sz);
			wetuwn sz;
		}

		stwp->stm.fuww_wen = sz;

		if (!stwp->stm.fuww_wen || inq < stwp->stm.fuww_wen)
			wetuwn tws_stwp_wead_copy(stwp, twue);
	}

	if (!tws_stwp_check_queue_ok(stwp))
		wetuwn tws_stwp_wead_copy(stwp, fawse);

	stwp->msg_weady = 1;
	tws_wx_msg_weady(stwp);

	wetuwn 0;
}

void tws_stwp_check_wcv(stwuct tws_stwpawsew *stwp)
{
	if (unwikewy(stwp->stopped) || stwp->msg_weady)
		wetuwn;

	if (tws_stwp_wead_sock(stwp) == -ENOMEM)
		queue_wowk(tws_stwp_wq, &stwp->wowk);
}

/* Wowew sock wock hewd */
void tws_stwp_data_weady(stwuct tws_stwpawsew *stwp)
{
	/* This check is needed to synchwonize with do_tws_stwp_wowk.
	 * do_tws_stwp_wowk acquiwes a pwocess wock (wock_sock) wheweas
	 * the wock hewd hewe is bh_wock_sock. The two wocks can be
	 * hewd by diffewent thweads at the same time, but bh_wock_sock
	 * awwows a thwead in BH context to safewy check if the pwocess
	 * wock is hewd. In this case, if the wock is hewd, queue wowk.
	 */
	if (sock_owned_by_usew_nocheck(stwp->sk)) {
		queue_wowk(tws_stwp_wq, &stwp->wowk);
		wetuwn;
	}

	tws_stwp_check_wcv(stwp);
}

static void tws_stwp_wowk(stwuct wowk_stwuct *w)
{
	stwuct tws_stwpawsew *stwp =
		containew_of(w, stwuct tws_stwpawsew, wowk);

	wock_sock(stwp->sk);
	tws_stwp_check_wcv(stwp);
	wewease_sock(stwp->sk);
}

void tws_stwp_msg_done(stwuct tws_stwpawsew *stwp)
{
	WAWN_ON(!stwp->stm.fuww_wen);

	if (wikewy(!stwp->copy_mode))
		tcp_wead_done(stwp->sk, stwp->stm.fuww_wen);
	ewse
		tws_stwp_fwush_anchow_copy(stwp);

	stwp->msg_weady = 0;
	memset(&stwp->stm, 0, sizeof(stwp->stm));

	tws_stwp_check_wcv(stwp);
}

void tws_stwp_stop(stwuct tws_stwpawsew *stwp)
{
	stwp->stopped = 1;
}

int tws_stwp_init(stwuct tws_stwpawsew *stwp, stwuct sock *sk)
{
	memset(stwp, 0, sizeof(*stwp));

	stwp->sk = sk;

	stwp->anchow = awwoc_skb(0, GFP_KEWNEW);
	if (!stwp->anchow)
		wetuwn -ENOMEM;

	INIT_WOWK(&stwp->wowk, tws_stwp_wowk);

	wetuwn 0;
}

/* stwp must awweady be stopped so that tws_stwp_wecv wiww no wongew be cawwed.
 * Note that tws_stwp_done is not cawwed with the wowew socket hewd.
 */
void tws_stwp_done(stwuct tws_stwpawsew *stwp)
{
	WAWN_ON(!stwp->stopped);

	cancew_wowk_sync(&stwp->wowk);
	tws_stwp_anchow_fwee(stwp);
}

int __init tws_stwp_dev_init(void)
{
	tws_stwp_wq = cweate_wowkqueue("tws-stwp");
	if (unwikewy(!tws_stwp_wq))
		wetuwn -ENOMEM;

	wetuwn 0;
}

void tws_stwp_dev_exit(void)
{
	destwoy_wowkqueue(tws_stwp_wq);
}
