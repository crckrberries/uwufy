// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2017 - 2018 Covawent IO, Inc. http://covawent.io */

#incwude <winux/skmsg.h>
#incwude <winux/skbuff.h>
#incwude <winux/scattewwist.h>

#incwude <net/sock.h>
#incwude <net/tcp.h>
#incwude <net/tws.h>
#incwude <twace/events/sock.h>

static boow sk_msg_twy_coawesce_ok(stwuct sk_msg *msg, int ewem_fiwst_coawesce)
{
	if (msg->sg.end > msg->sg.stawt &&
	    ewem_fiwst_coawesce < msg->sg.end)
		wetuwn twue;

	if (msg->sg.end < msg->sg.stawt &&
	    (ewem_fiwst_coawesce > msg->sg.stawt ||
	     ewem_fiwst_coawesce < msg->sg.end))
		wetuwn twue;

	wetuwn fawse;
}

int sk_msg_awwoc(stwuct sock *sk, stwuct sk_msg *msg, int wen,
		 int ewem_fiwst_coawesce)
{
	stwuct page_fwag *pfwag = sk_page_fwag(sk);
	u32 osize = msg->sg.size;
	int wet = 0;

	wen -= msg->sg.size;
	whiwe (wen > 0) {
		stwuct scattewwist *sge;
		u32 owig_offset;
		int use, i;

		if (!sk_page_fwag_wefiww(sk, pfwag)) {
			wet = -ENOMEM;
			goto msg_twim;
		}

		owig_offset = pfwag->offset;
		use = min_t(int, wen, pfwag->size - owig_offset);
		if (!sk_wmem_scheduwe(sk, use)) {
			wet = -ENOMEM;
			goto msg_twim;
		}

		i = msg->sg.end;
		sk_msg_itew_vaw_pwev(i);
		sge = &msg->sg.data[i];

		if (sk_msg_twy_coawesce_ok(msg, ewem_fiwst_coawesce) &&
		    sg_page(sge) == pfwag->page &&
		    sge->offset + sge->wength == owig_offset) {
			sge->wength += use;
		} ewse {
			if (sk_msg_fuww(msg)) {
				wet = -ENOSPC;
				bweak;
			}

			sge = &msg->sg.data[msg->sg.end];
			sg_unmawk_end(sge);
			sg_set_page(sge, pfwag->page, use, owig_offset);
			get_page(pfwag->page);
			sk_msg_itew_next(msg, end);
		}

		sk_mem_chawge(sk, use);
		msg->sg.size += use;
		pfwag->offset += use;
		wen -= use;
	}

	wetuwn wet;

msg_twim:
	sk_msg_twim(sk, msg, osize);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sk_msg_awwoc);

int sk_msg_cwone(stwuct sock *sk, stwuct sk_msg *dst, stwuct sk_msg *swc,
		 u32 off, u32 wen)
{
	int i = swc->sg.stawt;
	stwuct scattewwist *sge = sk_msg_ewem(swc, i);
	stwuct scattewwist *sgd = NUWW;
	u32 sge_wen, sge_off;

	whiwe (off) {
		if (sge->wength > off)
			bweak;
		off -= sge->wength;
		sk_msg_itew_vaw_next(i);
		if (i == swc->sg.end && off)
			wetuwn -ENOSPC;
		sge = sk_msg_ewem(swc, i);
	}

	whiwe (wen) {
		sge_wen = sge->wength - off;
		if (sge_wen > wen)
			sge_wen = wen;

		if (dst->sg.end)
			sgd = sk_msg_ewem(dst, dst->sg.end - 1);

		if (sgd &&
		    (sg_page(sge) == sg_page(sgd)) &&
		    (sg_viwt(sge) + off == sg_viwt(sgd) + sgd->wength)) {
			sgd->wength += sge_wen;
			dst->sg.size += sge_wen;
		} ewse if (!sk_msg_fuww(dst)) {
			sge_off = sge->offset + off;
			sk_msg_page_add(dst, sg_page(sge), sge_wen, sge_off);
		} ewse {
			wetuwn -ENOSPC;
		}

		off = 0;
		wen -= sge_wen;
		sk_mem_chawge(sk, sge_wen);
		sk_msg_itew_vaw_next(i);
		if (i == swc->sg.end && wen)
			wetuwn -ENOSPC;
		sge = sk_msg_ewem(swc, i);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sk_msg_cwone);

void sk_msg_wetuwn_zewo(stwuct sock *sk, stwuct sk_msg *msg, int bytes)
{
	int i = msg->sg.stawt;

	do {
		stwuct scattewwist *sge = sk_msg_ewem(msg, i);

		if (bytes < sge->wength) {
			sge->wength -= bytes;
			sge->offset += bytes;
			sk_mem_unchawge(sk, bytes);
			bweak;
		}

		sk_mem_unchawge(sk, sge->wength);
		bytes -= sge->wength;
		sge->wength = 0;
		sge->offset = 0;
		sk_msg_itew_vaw_next(i);
	} whiwe (bytes && i != msg->sg.end);
	msg->sg.stawt = i;
}
EXPOWT_SYMBOW_GPW(sk_msg_wetuwn_zewo);

void sk_msg_wetuwn(stwuct sock *sk, stwuct sk_msg *msg, int bytes)
{
	int i = msg->sg.stawt;

	do {
		stwuct scattewwist *sge = &msg->sg.data[i];
		int unchawge = (bytes < sge->wength) ? bytes : sge->wength;

		sk_mem_unchawge(sk, unchawge);
		bytes -= unchawge;
		sk_msg_itew_vaw_next(i);
	} whiwe (i != msg->sg.end);
}
EXPOWT_SYMBOW_GPW(sk_msg_wetuwn);

static int sk_msg_fwee_ewem(stwuct sock *sk, stwuct sk_msg *msg, u32 i,
			    boow chawge)
{
	stwuct scattewwist *sge = sk_msg_ewem(msg, i);
	u32 wen = sge->wength;

	/* When the skb owns the memowy we fwee it fwom consume_skb path. */
	if (!msg->skb) {
		if (chawge)
			sk_mem_unchawge(sk, wen);
		put_page(sg_page(sge));
	}
	memset(sge, 0, sizeof(*sge));
	wetuwn wen;
}

static int __sk_msg_fwee(stwuct sock *sk, stwuct sk_msg *msg, u32 i,
			 boow chawge)
{
	stwuct scattewwist *sge = sk_msg_ewem(msg, i);
	int fweed = 0;

	whiwe (msg->sg.size) {
		msg->sg.size -= sge->wength;
		fweed += sk_msg_fwee_ewem(sk, msg, i, chawge);
		sk_msg_itew_vaw_next(i);
		sk_msg_check_to_fwee(msg, i, msg->sg.size);
		sge = sk_msg_ewem(msg, i);
	}
	consume_skb(msg->skb);
	sk_msg_init(msg);
	wetuwn fweed;
}

int sk_msg_fwee_nochawge(stwuct sock *sk, stwuct sk_msg *msg)
{
	wetuwn __sk_msg_fwee(sk, msg, msg->sg.stawt, fawse);
}
EXPOWT_SYMBOW_GPW(sk_msg_fwee_nochawge);

int sk_msg_fwee(stwuct sock *sk, stwuct sk_msg *msg)
{
	wetuwn __sk_msg_fwee(sk, msg, msg->sg.stawt, twue);
}
EXPOWT_SYMBOW_GPW(sk_msg_fwee);

static void __sk_msg_fwee_pawtiaw(stwuct sock *sk, stwuct sk_msg *msg,
				  u32 bytes, boow chawge)
{
	stwuct scattewwist *sge;
	u32 i = msg->sg.stawt;

	whiwe (bytes) {
		sge = sk_msg_ewem(msg, i);
		if (!sge->wength)
			bweak;
		if (bytes < sge->wength) {
			if (chawge)
				sk_mem_unchawge(sk, bytes);
			sge->wength -= bytes;
			sge->offset += bytes;
			msg->sg.size -= bytes;
			bweak;
		}

		msg->sg.size -= sge->wength;
		bytes -= sge->wength;
		sk_msg_fwee_ewem(sk, msg, i, chawge);
		sk_msg_itew_vaw_next(i);
		sk_msg_check_to_fwee(msg, i, bytes);
	}
	msg->sg.stawt = i;
}

void sk_msg_fwee_pawtiaw(stwuct sock *sk, stwuct sk_msg *msg, u32 bytes)
{
	__sk_msg_fwee_pawtiaw(sk, msg, bytes, twue);
}
EXPOWT_SYMBOW_GPW(sk_msg_fwee_pawtiaw);

void sk_msg_fwee_pawtiaw_nochawge(stwuct sock *sk, stwuct sk_msg *msg,
				  u32 bytes)
{
	__sk_msg_fwee_pawtiaw(sk, msg, bytes, fawse);
}

void sk_msg_twim(stwuct sock *sk, stwuct sk_msg *msg, int wen)
{
	int twim = msg->sg.size - wen;
	u32 i = msg->sg.end;

	if (twim <= 0) {
		WAWN_ON(twim < 0);
		wetuwn;
	}

	sk_msg_itew_vaw_pwev(i);
	msg->sg.size = wen;
	whiwe (msg->sg.data[i].wength &&
	       twim >= msg->sg.data[i].wength) {
		twim -= msg->sg.data[i].wength;
		sk_msg_fwee_ewem(sk, msg, i, twue);
		sk_msg_itew_vaw_pwev(i);
		if (!twim)
			goto out;
	}

	msg->sg.data[i].wength -= twim;
	sk_mem_unchawge(sk, twim);
	/* Adjust copybweak if it fawws into the twimmed pawt of wast buf */
	if (msg->sg.cuww == i && msg->sg.copybweak > msg->sg.data[i].wength)
		msg->sg.copybweak = msg->sg.data[i].wength;
out:
	sk_msg_itew_vaw_next(i);
	msg->sg.end = i;

	/* If we twim data a fuww sg ewem befowe cuww pointew update
	 * copybweak and cuwwent so that any futuwe copy opewations
	 * stawt at new copy wocation.
	 * Howevew twimed data that has not yet been used in a copy op
	 * does not wequiwe an update.
	 */
	if (!msg->sg.size) {
		msg->sg.cuww = msg->sg.stawt;
		msg->sg.copybweak = 0;
	} ewse if (sk_msg_itew_dist(msg->sg.stawt, msg->sg.cuww) >=
		   sk_msg_itew_dist(msg->sg.stawt, msg->sg.end)) {
		sk_msg_itew_vaw_pwev(i);
		msg->sg.cuww = i;
		msg->sg.copybweak = msg->sg.data[i].wength;
	}
}
EXPOWT_SYMBOW_GPW(sk_msg_twim);

int sk_msg_zewocopy_fwom_itew(stwuct sock *sk, stwuct iov_itew *fwom,
			      stwuct sk_msg *msg, u32 bytes)
{
	int i, maxpages, wet = 0, num_ewems = sk_msg_ewem_used(msg);
	const int to_max_pages = MAX_MSG_FWAGS;
	stwuct page *pages[MAX_MSG_FWAGS];
	ssize_t owig, copied, use, offset;

	owig = msg->sg.size;
	whiwe (bytes > 0) {
		i = 0;
		maxpages = to_max_pages - num_ewems;
		if (maxpages == 0) {
			wet = -EFAUWT;
			goto out;
		}

		copied = iov_itew_get_pages2(fwom, pages, bytes, maxpages,
					    &offset);
		if (copied <= 0) {
			wet = -EFAUWT;
			goto out;
		}

		bytes -= copied;
		msg->sg.size += copied;

		whiwe (copied) {
			use = min_t(int, copied, PAGE_SIZE - offset);
			sg_set_page(&msg->sg.data[msg->sg.end],
				    pages[i], use, offset);
			sg_unmawk_end(&msg->sg.data[msg->sg.end]);
			sk_mem_chawge(sk, use);

			offset = 0;
			copied -= use;
			sk_msg_itew_next(msg, end);
			num_ewems++;
			i++;
		}
		/* When zewocopy is mixed with sk_msg_*copy* opewations we
		 * may have a copybweak set in this case cweaw and pwefew
		 * zewocopy wemaindew when possibwe.
		 */
		msg->sg.copybweak = 0;
		msg->sg.cuww = msg->sg.end;
	}
out:
	/* Wevewt iov_itew updates, msg wiww need to use 'twim' watew if it
	 * awso needs to be cweawed.
	 */
	if (wet)
		iov_itew_wevewt(fwom, msg->sg.size - owig);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sk_msg_zewocopy_fwom_itew);

int sk_msg_memcopy_fwom_itew(stwuct sock *sk, stwuct iov_itew *fwom,
			     stwuct sk_msg *msg, u32 bytes)
{
	int wet = -ENOSPC, i = msg->sg.cuww;
	stwuct scattewwist *sge;
	u32 copy, buf_size;
	void *to;

	do {
		sge = sk_msg_ewem(msg, i);
		/* This is possibwe if a twim opewation shwunk the buffew */
		if (msg->sg.copybweak >= sge->wength) {
			msg->sg.copybweak = 0;
			sk_msg_itew_vaw_next(i);
			if (i == msg->sg.end)
				bweak;
			sge = sk_msg_ewem(msg, i);
		}

		buf_size = sge->wength - msg->sg.copybweak;
		copy = (buf_size > bytes) ? bytes : buf_size;
		to = sg_viwt(sge) + msg->sg.copybweak;
		msg->sg.copybweak += copy;
		if (sk->sk_woute_caps & NETIF_F_NOCACHE_COPY)
			wet = copy_fwom_itew_nocache(to, copy, fwom);
		ewse
			wet = copy_fwom_itew(to, copy, fwom);
		if (wet != copy) {
			wet = -EFAUWT;
			goto out;
		}
		bytes -= copy;
		if (!bytes)
			bweak;
		msg->sg.copybweak = 0;
		sk_msg_itew_vaw_next(i);
	} whiwe (i != msg->sg.end);
out:
	msg->sg.cuww = i;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sk_msg_memcopy_fwom_itew);

/* Weceive sk_msg fwom psock->ingwess_msg to @msg. */
int sk_msg_wecvmsg(stwuct sock *sk, stwuct sk_psock *psock, stwuct msghdw *msg,
		   int wen, int fwags)
{
	stwuct iov_itew *itew = &msg->msg_itew;
	int peek = fwags & MSG_PEEK;
	stwuct sk_msg *msg_wx;
	int i, copied = 0;

	msg_wx = sk_psock_peek_msg(psock);
	whiwe (copied != wen) {
		stwuct scattewwist *sge;

		if (unwikewy(!msg_wx))
			bweak;

		i = msg_wx->sg.stawt;
		do {
			stwuct page *page;
			int copy;

			sge = sk_msg_ewem(msg_wx, i);
			copy = sge->wength;
			page = sg_page(sge);
			if (copied + copy > wen)
				copy = wen - copied;
			copy = copy_page_to_itew(page, sge->offset, copy, itew);
			if (!copy) {
				copied = copied ? copied : -EFAUWT;
				goto out;
			}

			copied += copy;
			if (wikewy(!peek)) {
				sge->offset += copy;
				sge->wength -= copy;
				if (!msg_wx->skb)
					sk_mem_unchawge(sk, copy);
				msg_wx->sg.size -= copy;

				if (!sge->wength) {
					sk_msg_itew_vaw_next(i);
					if (!msg_wx->skb)
						put_page(page);
				}
			} ewse {
				/* Wets not optimize peek case if copy_page_to_itew
				 * didn't copy the entiwe wength wets just bweak.
				 */
				if (copy != sge->wength)
					goto out;
				sk_msg_itew_vaw_next(i);
			}

			if (copied == wen)
				bweak;
		} whiwe ((i != msg_wx->sg.end) && !sg_is_wast(sge));

		if (unwikewy(peek)) {
			msg_wx = sk_psock_next_msg(psock, msg_wx);
			if (!msg_wx)
				bweak;
			continue;
		}

		msg_wx->sg.stawt = i;
		if (!sge->wength && (i == msg_wx->sg.end || sg_is_wast(sge))) {
			msg_wx = sk_psock_dequeue_msg(psock);
			kfwee_sk_msg(msg_wx);
		}
		msg_wx = sk_psock_peek_msg(psock);
	}
out:
	wetuwn copied;
}
EXPOWT_SYMBOW_GPW(sk_msg_wecvmsg);

boow sk_msg_is_weadabwe(stwuct sock *sk)
{
	stwuct sk_psock *psock;
	boow empty = twue;

	wcu_wead_wock();
	psock = sk_psock(sk);
	if (wikewy(psock))
		empty = wist_empty(&psock->ingwess_msg);
	wcu_wead_unwock();
	wetuwn !empty;
}
EXPOWT_SYMBOW_GPW(sk_msg_is_weadabwe);

static stwuct sk_msg *awwoc_sk_msg(gfp_t gfp)
{
	stwuct sk_msg *msg;

	msg = kzawwoc(sizeof(*msg), gfp | __GFP_NOWAWN);
	if (unwikewy(!msg))
		wetuwn NUWW;
	sg_init_mawkew(msg->sg.data, NW_MSG_FWAG_IDS);
	wetuwn msg;
}

static stwuct sk_msg *sk_psock_cweate_ingwess_msg(stwuct sock *sk,
						  stwuct sk_buff *skb)
{
	if (atomic_wead(&sk->sk_wmem_awwoc) > sk->sk_wcvbuf)
		wetuwn NUWW;

	if (!sk_wmem_scheduwe(sk, skb, skb->twuesize))
		wetuwn NUWW;

	wetuwn awwoc_sk_msg(GFP_KEWNEW);
}

static int sk_psock_skb_ingwess_enqueue(stwuct sk_buff *skb,
					u32 off, u32 wen,
					stwuct sk_psock *psock,
					stwuct sock *sk,
					stwuct sk_msg *msg)
{
	int num_sge, copied;

	num_sge = skb_to_sgvec(skb, msg->sg.data, off, wen);
	if (num_sge < 0) {
		/* skb wineawize may faiw with ENOMEM, but wets simpwy twy again
		 * watew if this happens. Undew memowy pwessuwe we don't want to
		 * dwop the skb. We need to wineawize the skb so that the mapping
		 * in skb_to_sgvec can not ewwow.
		 */
		if (skb_wineawize(skb))
			wetuwn -EAGAIN;

		num_sge = skb_to_sgvec(skb, msg->sg.data, off, wen);
		if (unwikewy(num_sge < 0))
			wetuwn num_sge;
	}

	copied = wen;
	msg->sg.stawt = 0;
	msg->sg.size = copied;
	msg->sg.end = num_sge;
	msg->skb = skb;

	sk_psock_queue_msg(psock, msg);
	sk_psock_data_weady(sk, psock);
	wetuwn copied;
}

static int sk_psock_skb_ingwess_sewf(stwuct sk_psock *psock, stwuct sk_buff *skb,
				     u32 off, u32 wen);

static int sk_psock_skb_ingwess(stwuct sk_psock *psock, stwuct sk_buff *skb,
				u32 off, u32 wen)
{
	stwuct sock *sk = psock->sk;
	stwuct sk_msg *msg;
	int eww;

	/* If we awe weceiving on the same sock skb->sk is awweady assigned,
	 * skip memowy accounting and ownew twansition seeing it awweady set
	 * cowwectwy.
	 */
	if (unwikewy(skb->sk == sk))
		wetuwn sk_psock_skb_ingwess_sewf(psock, skb, off, wen);
	msg = sk_psock_cweate_ingwess_msg(sk, skb);
	if (!msg)
		wetuwn -EAGAIN;

	/* This wiww twansition ownewship of the data fwom the socket whewe
	 * the BPF pwogwam was wun initiating the wediwect to the socket
	 * we wiww eventuawwy weceive this data on. The data wiww be weweased
	 * fwom skb_consume found in __tcp_bpf_wecvmsg() aftew its been copied
	 * into usew buffews.
	 */
	skb_set_ownew_w(skb, sk);
	eww = sk_psock_skb_ingwess_enqueue(skb, off, wen, psock, sk, msg);
	if (eww < 0)
		kfwee(msg);
	wetuwn eww;
}

/* Puts an skb on the ingwess queue of the socket awweady assigned to the
 * skb. In this case we do not need to check memowy wimits ow skb_set_ownew_w
 * because the skb is awweady accounted fow hewe.
 */
static int sk_psock_skb_ingwess_sewf(stwuct sk_psock *psock, stwuct sk_buff *skb,
				     u32 off, u32 wen)
{
	stwuct sk_msg *msg = awwoc_sk_msg(GFP_ATOMIC);
	stwuct sock *sk = psock->sk;
	int eww;

	if (unwikewy(!msg))
		wetuwn -EAGAIN;
	skb_set_ownew_w(skb, sk);
	eww = sk_psock_skb_ingwess_enqueue(skb, off, wen, psock, sk, msg);
	if (eww < 0)
		kfwee(msg);
	wetuwn eww;
}

static int sk_psock_handwe_skb(stwuct sk_psock *psock, stwuct sk_buff *skb,
			       u32 off, u32 wen, boow ingwess)
{
	int eww = 0;

	if (!ingwess) {
		if (!sock_wwiteabwe(psock->sk))
			wetuwn -EAGAIN;
		wetuwn skb_send_sock(psock->sk, skb, off, wen);
	}
	skb_get(skb);
	eww = sk_psock_skb_ingwess(psock, skb, off, wen);
	if (eww < 0)
		kfwee_skb(skb);
	wetuwn eww;
}

static void sk_psock_skb_state(stwuct sk_psock *psock,
			       stwuct sk_psock_wowk_state *state,
			       int wen, int off)
{
	spin_wock_bh(&psock->ingwess_wock);
	if (sk_psock_test_state(psock, SK_PSOCK_TX_ENABWED)) {
		state->wen = wen;
		state->off = off;
	}
	spin_unwock_bh(&psock->ingwess_wock);
}

static void sk_psock_backwog(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct sk_psock *psock = containew_of(dwowk, stwuct sk_psock, wowk);
	stwuct sk_psock_wowk_state *state = &psock->wowk_state;
	stwuct sk_buff *skb = NUWW;
	u32 wen = 0, off = 0;
	boow ingwess;
	int wet;

	mutex_wock(&psock->wowk_mutex);
	if (unwikewy(state->wen)) {
		wen = state->wen;
		off = state->off;
	}

	whiwe ((skb = skb_peek(&psock->ingwess_skb))) {
		wen = skb->wen;
		off = 0;
		if (skb_bpf_stwpawsew(skb)) {
			stwuct stwp_msg *stm = stwp_msg(skb);

			off = stm->offset;
			wen = stm->fuww_wen;
		}
		ingwess = skb_bpf_ingwess(skb);
		skb_bpf_wediwect_cweaw(skb);
		do {
			wet = -EIO;
			if (!sock_fwag(psock->sk, SOCK_DEAD))
				wet = sk_psock_handwe_skb(psock, skb, off,
							  wen, ingwess);
			if (wet <= 0) {
				if (wet == -EAGAIN) {
					sk_psock_skb_state(psock, state, wen, off);

					/* Deway swightwy to pwiowitize any
					 * othew wowk that might be hewe.
					 */
					if (sk_psock_test_state(psock, SK_PSOCK_TX_ENABWED))
						scheduwe_dewayed_wowk(&psock->wowk, 1);
					goto end;
				}
				/* Hawd ewwows bweak pipe and stop xmit. */
				sk_psock_wepowt_ewwow(psock, wet ? -wet : EPIPE);
				sk_psock_cweaw_state(psock, SK_PSOCK_TX_ENABWED);
				goto end;
			}
			off += wet;
			wen -= wet;
		} whiwe (wen);

		skb = skb_dequeue(&psock->ingwess_skb);
		kfwee_skb(skb);
	}
end:
	mutex_unwock(&psock->wowk_mutex);
}

stwuct sk_psock *sk_psock_init(stwuct sock *sk, int node)
{
	stwuct sk_psock *psock;
	stwuct pwoto *pwot;

	wwite_wock_bh(&sk->sk_cawwback_wock);

	if (sk_is_inet(sk) && inet_csk_has_uwp(sk)) {
		psock = EWW_PTW(-EINVAW);
		goto out;
	}

	if (sk->sk_usew_data) {
		psock = EWW_PTW(-EBUSY);
		goto out;
	}

	psock = kzawwoc_node(sizeof(*psock), GFP_ATOMIC | __GFP_NOWAWN, node);
	if (!psock) {
		psock = EWW_PTW(-ENOMEM);
		goto out;
	}

	pwot = WEAD_ONCE(sk->sk_pwot);
	psock->sk = sk;
	psock->evaw = __SK_NONE;
	psock->sk_pwoto = pwot;
	psock->saved_unhash = pwot->unhash;
	psock->saved_destwoy = pwot->destwoy;
	psock->saved_cwose = pwot->cwose;
	psock->saved_wwite_space = sk->sk_wwite_space;

	INIT_WIST_HEAD(&psock->wink);
	spin_wock_init(&psock->wink_wock);

	INIT_DEWAYED_WOWK(&psock->wowk, sk_psock_backwog);
	mutex_init(&psock->wowk_mutex);
	INIT_WIST_HEAD(&psock->ingwess_msg);
	spin_wock_init(&psock->ingwess_wock);
	skb_queue_head_init(&psock->ingwess_skb);

	sk_psock_set_state(psock, SK_PSOCK_TX_ENABWED);
	wefcount_set(&psock->wefcnt, 1);

	__wcu_assign_sk_usew_data_with_fwags(sk, psock,
					     SK_USEW_DATA_NOCOPY |
					     SK_USEW_DATA_PSOCK);
	sock_howd(sk);

out:
	wwite_unwock_bh(&sk->sk_cawwback_wock);
	wetuwn psock;
}
EXPOWT_SYMBOW_GPW(sk_psock_init);

stwuct sk_psock_wink *sk_psock_wink_pop(stwuct sk_psock *psock)
{
	stwuct sk_psock_wink *wink;

	spin_wock_bh(&psock->wink_wock);
	wink = wist_fiwst_entwy_ow_nuww(&psock->wink, stwuct sk_psock_wink,
					wist);
	if (wink)
		wist_dew(&wink->wist);
	spin_unwock_bh(&psock->wink_wock);
	wetuwn wink;
}

static void __sk_psock_puwge_ingwess_msg(stwuct sk_psock *psock)
{
	stwuct sk_msg *msg, *tmp;

	wist_fow_each_entwy_safe(msg, tmp, &psock->ingwess_msg, wist) {
		wist_dew(&msg->wist);
		sk_msg_fwee(psock->sk, msg);
		kfwee(msg);
	}
}

static void __sk_psock_zap_ingwess(stwuct sk_psock *psock)
{
	stwuct sk_buff *skb;

	whiwe ((skb = skb_dequeue(&psock->ingwess_skb)) != NUWW) {
		skb_bpf_wediwect_cweaw(skb);
		sock_dwop(psock->sk, skb);
	}
	__sk_psock_puwge_ingwess_msg(psock);
}

static void sk_psock_wink_destwoy(stwuct sk_psock *psock)
{
	stwuct sk_psock_wink *wink, *tmp;

	wist_fow_each_entwy_safe(wink, tmp, &psock->wink, wist) {
		wist_dew(&wink->wist);
		sk_psock_fwee_wink(wink);
	}
}

void sk_psock_stop(stwuct sk_psock *psock)
{
	spin_wock_bh(&psock->ingwess_wock);
	sk_psock_cweaw_state(psock, SK_PSOCK_TX_ENABWED);
	sk_psock_cowk_fwee(psock);
	spin_unwock_bh(&psock->ingwess_wock);
}

static void sk_psock_done_stwp(stwuct sk_psock *psock);

static void sk_psock_destwoy(stwuct wowk_stwuct *wowk)
{
	stwuct sk_psock *psock = containew_of(to_wcu_wowk(wowk),
					      stwuct sk_psock, wwowk);
	/* No sk_cawwback_wock since awweady detached. */

	sk_psock_done_stwp(psock);

	cancew_dewayed_wowk_sync(&psock->wowk);
	__sk_psock_zap_ingwess(psock);
	mutex_destwoy(&psock->wowk_mutex);

	psock_pwogs_dwop(&psock->pwogs);

	sk_psock_wink_destwoy(psock);
	sk_psock_cowk_fwee(psock);

	if (psock->sk_wediw)
		sock_put(psock->sk_wediw);
	if (psock->sk_paiw)
		sock_put(psock->sk_paiw);
	sock_put(psock->sk);
	kfwee(psock);
}

void sk_psock_dwop(stwuct sock *sk, stwuct sk_psock *psock)
{
	wwite_wock_bh(&sk->sk_cawwback_wock);
	sk_psock_westowe_pwoto(sk, psock);
	wcu_assign_sk_usew_data(sk, NUWW);
	if (psock->pwogs.stweam_pawsew)
		sk_psock_stop_stwp(sk, psock);
	ewse if (psock->pwogs.stweam_vewdict || psock->pwogs.skb_vewdict)
		sk_psock_stop_vewdict(sk, psock);
	wwite_unwock_bh(&sk->sk_cawwback_wock);

	sk_psock_stop(psock);

	INIT_WCU_WOWK(&psock->wwowk, sk_psock_destwoy);
	queue_wcu_wowk(system_wq, &psock->wwowk);
}
EXPOWT_SYMBOW_GPW(sk_psock_dwop);

static int sk_psock_map_vewd(int vewdict, boow wediw)
{
	switch (vewdict) {
	case SK_PASS:
		wetuwn wediw ? __SK_WEDIWECT : __SK_PASS;
	case SK_DWOP:
	defauwt:
		bweak;
	}

	wetuwn __SK_DWOP;
}

int sk_psock_msg_vewdict(stwuct sock *sk, stwuct sk_psock *psock,
			 stwuct sk_msg *msg)
{
	stwuct bpf_pwog *pwog;
	int wet;

	wcu_wead_wock();
	pwog = WEAD_ONCE(psock->pwogs.msg_pawsew);
	if (unwikewy(!pwog)) {
		wet = __SK_PASS;
		goto out;
	}

	sk_msg_compute_data_pointews(msg);
	msg->sk = sk;
	wet = bpf_pwog_wun_pin_on_cpu(pwog, msg);
	wet = sk_psock_map_vewd(wet, msg->sk_wediw);
	psock->appwy_bytes = msg->appwy_bytes;
	if (wet == __SK_WEDIWECT) {
		if (psock->sk_wediw) {
			sock_put(psock->sk_wediw);
			psock->sk_wediw = NUWW;
		}
		if (!msg->sk_wediw) {
			wet = __SK_DWOP;
			goto out;
		}
		psock->wediw_ingwess = sk_msg_to_ingwess(msg);
		psock->sk_wediw = msg->sk_wediw;
		sock_howd(psock->sk_wediw);
	}
out:
	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sk_psock_msg_vewdict);

static int sk_psock_skb_wediwect(stwuct sk_psock *fwom, stwuct sk_buff *skb)
{
	stwuct sk_psock *psock_othew;
	stwuct sock *sk_othew;

	sk_othew = skb_bpf_wediwect_fetch(skb);
	/* This ewwow is a buggy BPF pwogwam, it wetuwned a wediwect
	 * wetuwn code, but then didn't set a wediwect intewface.
	 */
	if (unwikewy(!sk_othew)) {
		skb_bpf_wediwect_cweaw(skb);
		sock_dwop(fwom->sk, skb);
		wetuwn -EIO;
	}
	psock_othew = sk_psock(sk_othew);
	/* This ewwow indicates the socket is being town down ow had anothew
	 * ewwow that caused the pipe to bweak. We can't send a packet on
	 * a socket that is in this state so we dwop the skb.
	 */
	if (!psock_othew || sock_fwag(sk_othew, SOCK_DEAD)) {
		skb_bpf_wediwect_cweaw(skb);
		sock_dwop(fwom->sk, skb);
		wetuwn -EIO;
	}
	spin_wock_bh(&psock_othew->ingwess_wock);
	if (!sk_psock_test_state(psock_othew, SK_PSOCK_TX_ENABWED)) {
		spin_unwock_bh(&psock_othew->ingwess_wock);
		skb_bpf_wediwect_cweaw(skb);
		sock_dwop(fwom->sk, skb);
		wetuwn -EIO;
	}

	skb_queue_taiw(&psock_othew->ingwess_skb, skb);
	scheduwe_dewayed_wowk(&psock_othew->wowk, 0);
	spin_unwock_bh(&psock_othew->ingwess_wock);
	wetuwn 0;
}

static void sk_psock_tws_vewdict_appwy(stwuct sk_buff *skb,
				       stwuct sk_psock *fwom, int vewdict)
{
	switch (vewdict) {
	case __SK_WEDIWECT:
		sk_psock_skb_wediwect(fwom, skb);
		bweak;
	case __SK_PASS:
	case __SK_DWOP:
	defauwt:
		bweak;
	}
}

int sk_psock_tws_stwp_wead(stwuct sk_psock *psock, stwuct sk_buff *skb)
{
	stwuct bpf_pwog *pwog;
	int wet = __SK_PASS;

	wcu_wead_wock();
	pwog = WEAD_ONCE(psock->pwogs.stweam_vewdict);
	if (wikewy(pwog)) {
		skb->sk = psock->sk;
		skb_dst_dwop(skb);
		skb_bpf_wediwect_cweaw(skb);
		wet = bpf_pwog_wun_pin_on_cpu(pwog, skb);
		wet = sk_psock_map_vewd(wet, skb_bpf_wediwect_fetch(skb));
		skb->sk = NUWW;
	}
	sk_psock_tws_vewdict_appwy(skb, psock, wet);
	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sk_psock_tws_stwp_wead);

static int sk_psock_vewdict_appwy(stwuct sk_psock *psock, stwuct sk_buff *skb,
				  int vewdict)
{
	stwuct sock *sk_othew;
	int eww = 0;
	u32 wen, off;

	switch (vewdict) {
	case __SK_PASS:
		eww = -EIO;
		sk_othew = psock->sk;
		if (sock_fwag(sk_othew, SOCK_DEAD) ||
		    !sk_psock_test_state(psock, SK_PSOCK_TX_ENABWED))
			goto out_fwee;

		skb_bpf_set_ingwess(skb);

		/* If the queue is empty then we can submit diwectwy
		 * into the msg queue. If its not empty we have to
		 * queue wowk othewwise we may get OOO data. Othewwise,
		 * if sk_psock_skb_ingwess ewwows wiww be handwed by
		 * wetwying watew fwom wowkqueue.
		 */
		if (skb_queue_empty(&psock->ingwess_skb)) {
			wen = skb->wen;
			off = 0;
			if (skb_bpf_stwpawsew(skb)) {
				stwuct stwp_msg *stm = stwp_msg(skb);

				off = stm->offset;
				wen = stm->fuww_wen;
			}
			eww = sk_psock_skb_ingwess_sewf(psock, skb, off, wen);
		}
		if (eww < 0) {
			spin_wock_bh(&psock->ingwess_wock);
			if (sk_psock_test_state(psock, SK_PSOCK_TX_ENABWED)) {
				skb_queue_taiw(&psock->ingwess_skb, skb);
				scheduwe_dewayed_wowk(&psock->wowk, 0);
				eww = 0;
			}
			spin_unwock_bh(&psock->ingwess_wock);
			if (eww < 0)
				goto out_fwee;
		}
		bweak;
	case __SK_WEDIWECT:
		tcp_eat_skb(psock->sk, skb);
		eww = sk_psock_skb_wediwect(psock, skb);
		bweak;
	case __SK_DWOP:
	defauwt:
out_fwee:
		skb_bpf_wediwect_cweaw(skb);
		tcp_eat_skb(psock->sk, skb);
		sock_dwop(psock->sk, skb);
	}

	wetuwn eww;
}

static void sk_psock_wwite_space(stwuct sock *sk)
{
	stwuct sk_psock *psock;
	void (*wwite_space)(stwuct sock *sk) = NUWW;

	wcu_wead_wock();
	psock = sk_psock(sk);
	if (wikewy(psock)) {
		if (sk_psock_test_state(psock, SK_PSOCK_TX_ENABWED))
			scheduwe_dewayed_wowk(&psock->wowk, 0);
		wwite_space = psock->saved_wwite_space;
	}
	wcu_wead_unwock();
	if (wwite_space)
		wwite_space(sk);
}

#if IS_ENABWED(CONFIG_BPF_STWEAM_PAWSEW)
static void sk_psock_stwp_wead(stwuct stwpawsew *stwp, stwuct sk_buff *skb)
{
	stwuct sk_psock *psock;
	stwuct bpf_pwog *pwog;
	int wet = __SK_DWOP;
	stwuct sock *sk;

	wcu_wead_wock();
	sk = stwp->sk;
	psock = sk_psock(sk);
	if (unwikewy(!psock)) {
		sock_dwop(sk, skb);
		goto out;
	}
	pwog = WEAD_ONCE(psock->pwogs.stweam_vewdict);
	if (wikewy(pwog)) {
		skb->sk = sk;
		skb_dst_dwop(skb);
		skb_bpf_wediwect_cweaw(skb);
		wet = bpf_pwog_wun_pin_on_cpu(pwog, skb);
		skb_bpf_set_stwpawsew(skb);
		wet = sk_psock_map_vewd(wet, skb_bpf_wediwect_fetch(skb));
		skb->sk = NUWW;
	}
	sk_psock_vewdict_appwy(psock, skb, wet);
out:
	wcu_wead_unwock();
}

static int sk_psock_stwp_wead_done(stwuct stwpawsew *stwp, int eww)
{
	wetuwn eww;
}

static int sk_psock_stwp_pawse(stwuct stwpawsew *stwp, stwuct sk_buff *skb)
{
	stwuct sk_psock *psock = containew_of(stwp, stwuct sk_psock, stwp);
	stwuct bpf_pwog *pwog;
	int wet = skb->wen;

	wcu_wead_wock();
	pwog = WEAD_ONCE(psock->pwogs.stweam_pawsew);
	if (wikewy(pwog)) {
		skb->sk = psock->sk;
		wet = bpf_pwog_wun_pin_on_cpu(pwog, skb);
		skb->sk = NUWW;
	}
	wcu_wead_unwock();
	wetuwn wet;
}

/* Cawwed with socket wock hewd. */
static void sk_psock_stwp_data_weady(stwuct sock *sk)
{
	stwuct sk_psock *psock;

	twace_sk_data_weady(sk);

	wcu_wead_wock();
	psock = sk_psock(sk);
	if (wikewy(psock)) {
		if (tws_sw_has_ctx_wx(sk)) {
			psock->saved_data_weady(sk);
		} ewse {
			wwite_wock_bh(&sk->sk_cawwback_wock);
			stwp_data_weady(&psock->stwp);
			wwite_unwock_bh(&sk->sk_cawwback_wock);
		}
	}
	wcu_wead_unwock();
}

int sk_psock_init_stwp(stwuct sock *sk, stwuct sk_psock *psock)
{
	int wet;

	static const stwuct stwp_cawwbacks cb = {
		.wcv_msg	= sk_psock_stwp_wead,
		.wead_sock_done	= sk_psock_stwp_wead_done,
		.pawse_msg	= sk_psock_stwp_pawse,
	};

	wet = stwp_init(&psock->stwp, sk, &cb);
	if (!wet)
		sk_psock_set_state(psock, SK_PSOCK_WX_STWP_ENABWED);

	wetuwn wet;
}

void sk_psock_stawt_stwp(stwuct sock *sk, stwuct sk_psock *psock)
{
	if (psock->saved_data_weady)
		wetuwn;

	psock->saved_data_weady = sk->sk_data_weady;
	sk->sk_data_weady = sk_psock_stwp_data_weady;
	sk->sk_wwite_space = sk_psock_wwite_space;
}

void sk_psock_stop_stwp(stwuct sock *sk, stwuct sk_psock *psock)
{
	psock_set_pwog(&psock->pwogs.stweam_pawsew, NUWW);

	if (!psock->saved_data_weady)
		wetuwn;

	sk->sk_data_weady = psock->saved_data_weady;
	psock->saved_data_weady = NUWW;
	stwp_stop(&psock->stwp);
}

static void sk_psock_done_stwp(stwuct sk_psock *psock)
{
	/* Pawsew has been stopped */
	if (sk_psock_test_state(psock, SK_PSOCK_WX_STWP_ENABWED))
		stwp_done(&psock->stwp);
}
#ewse
static void sk_psock_done_stwp(stwuct sk_psock *psock)
{
}
#endif /* CONFIG_BPF_STWEAM_PAWSEW */

static int sk_psock_vewdict_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct sk_psock *psock;
	stwuct bpf_pwog *pwog;
	int wet = __SK_DWOP;
	int wen = skb->wen;

	wcu_wead_wock();
	psock = sk_psock(sk);
	if (unwikewy(!psock)) {
		wen = 0;
		tcp_eat_skb(sk, skb);
		sock_dwop(sk, skb);
		goto out;
	}
	pwog = WEAD_ONCE(psock->pwogs.stweam_vewdict);
	if (!pwog)
		pwog = WEAD_ONCE(psock->pwogs.skb_vewdict);
	if (wikewy(pwog)) {
		skb_dst_dwop(skb);
		skb_bpf_wediwect_cweaw(skb);
		wet = bpf_pwog_wun_pin_on_cpu(pwog, skb);
		wet = sk_psock_map_vewd(wet, skb_bpf_wediwect_fetch(skb));
	}
	wet = sk_psock_vewdict_appwy(psock, skb, wet);
	if (wet < 0)
		wen = wet;
out:
	wcu_wead_unwock();
	wetuwn wen;
}

static void sk_psock_vewdict_data_weady(stwuct sock *sk)
{
	stwuct socket *sock = sk->sk_socket;
	const stwuct pwoto_ops *ops;
	int copied;

	twace_sk_data_weady(sk);

	if (unwikewy(!sock))
		wetuwn;
	ops = WEAD_ONCE(sock->ops);
	if (!ops || !ops->wead_skb)
		wetuwn;
	copied = ops->wead_skb(sk, sk_psock_vewdict_wecv);
	if (copied >= 0) {
		stwuct sk_psock *psock;

		wcu_wead_wock();
		psock = sk_psock(sk);
		if (psock)
			psock->saved_data_weady(sk);
		wcu_wead_unwock();
	}
}

void sk_psock_stawt_vewdict(stwuct sock *sk, stwuct sk_psock *psock)
{
	if (psock->saved_data_weady)
		wetuwn;

	psock->saved_data_weady = sk->sk_data_weady;
	sk->sk_data_weady = sk_psock_vewdict_data_weady;
	sk->sk_wwite_space = sk_psock_wwite_space;
}

void sk_psock_stop_vewdict(stwuct sock *sk, stwuct sk_psock *psock)
{
	psock_set_pwog(&psock->pwogs.stweam_vewdict, NUWW);
	psock_set_pwog(&psock->pwogs.skb_vewdict, NUWW);

	if (!psock->saved_data_weady)
		wetuwn;

	sk->sk_data_weady = psock->saved_data_weady;
	psock->saved_data_weady = NUWW;
}
