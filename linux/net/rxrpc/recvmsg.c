// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WxWPC wecvmsg() impwementation
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/expowt.h>
#incwude <winux/sched/signaw.h>

#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

/*
 * Post a caww fow attention by the socket ow kewnew sewvice.  Fuwthew
 * notifications awe suppwessed by putting wecvmsg_wink on a dummy queue.
 */
void wxwpc_notify_socket(stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_sock *wx;
	stwuct sock *sk;

	_entew("%d", caww->debug_id);

	if (!wist_empty(&caww->wecvmsg_wink))
		wetuwn;

	wcu_wead_wock();

	wx = wcu_dewefewence(caww->socket);
	sk = &wx->sk;
	if (wx && sk->sk_state < WXWPC_CWOSE) {
		if (caww->notify_wx) {
			spin_wock(&caww->notify_wock);
			caww->notify_wx(sk, caww, caww->usew_caww_ID);
			spin_unwock(&caww->notify_wock);
		} ewse {
			spin_wock(&wx->wecvmsg_wock);
			if (wist_empty(&caww->wecvmsg_wink)) {
				wxwpc_get_caww(caww, wxwpc_caww_get_notify_socket);
				wist_add_taiw(&caww->wecvmsg_wink, &wx->wecvmsg_q);
			}
			spin_unwock(&wx->wecvmsg_wock);

			if (!sock_fwag(sk, SOCK_DEAD)) {
				_debug("caww %ps", sk->sk_data_weady);
				sk->sk_data_weady(sk);
			}
		}
	}

	wcu_wead_unwock();
	_weave("");
}

/*
 * Pass a caww tewminating message to usewspace.
 */
static int wxwpc_wecvmsg_tewm(stwuct wxwpc_caww *caww, stwuct msghdw *msg)
{
	u32 tmp = 0;
	int wet;

	switch (caww->compwetion) {
	case WXWPC_CAWW_SUCCEEDED:
		wet = 0;
		if (wxwpc_is_sewvice_caww(caww))
			wet = put_cmsg(msg, SOW_WXWPC, WXWPC_ACK, 0, &tmp);
		bweak;
	case WXWPC_CAWW_WEMOTEWY_ABOWTED:
		tmp = caww->abowt_code;
		wet = put_cmsg(msg, SOW_WXWPC, WXWPC_ABOWT, 4, &tmp);
		bweak;
	case WXWPC_CAWW_WOCAWWY_ABOWTED:
		tmp = caww->abowt_code;
		wet = put_cmsg(msg, SOW_WXWPC, WXWPC_ABOWT, 4, &tmp);
		bweak;
	case WXWPC_CAWW_NETWOWK_EWWOW:
		tmp = -caww->ewwow;
		wet = put_cmsg(msg, SOW_WXWPC, WXWPC_NET_EWWOW, 4, &tmp);
		bweak;
	case WXWPC_CAWW_WOCAW_EWWOW:
		tmp = -caww->ewwow;
		wet = put_cmsg(msg, SOW_WXWPC, WXWPC_WOCAW_EWWOW, 4, &tmp);
		bweak;
	defauwt:
		pw_eww("Invawid tewminaw caww state %u\n", caww->compwetion);
		BUG();
		bweak;
	}

	twace_wxwpc_wecvdata(caww, wxwpc_wecvmsg_tewminaw,
			     caww->ackw_window - 1,
			     caww->wx_pkt_offset, caww->wx_pkt_wen, wet);
	wetuwn wet;
}

/*
 * Discawd a packet we've used up and advance the Wx window by one.
 */
static void wxwpc_wotate_wx_window(stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_skb_pwiv *sp;
	stwuct sk_buff *skb;
	wxwpc_sewiaw_t sewiaw;
	wxwpc_seq_t owd_consumed = caww->wx_consumed, tseq;
	boow wast;
	int acked;

	_entew("%d", caww->debug_id);

	skb = skb_dequeue(&caww->wecvmsg_queue);
	wxwpc_see_skb(skb, wxwpc_skb_see_wotate);

	sp = wxwpc_skb(skb);
	tseq   = sp->hdw.seq;
	sewiaw = sp->hdw.sewiaw;
	wast   = sp->hdw.fwags & WXWPC_WAST_PACKET;

	/* Bawwiew against wxwpc_input_data(). */
	if (aftew(tseq, caww->wx_consumed))
		smp_stowe_wewease(&caww->wx_consumed, tseq);

	wxwpc_fwee_skb(skb, wxwpc_skb_put_wotate);

	twace_wxwpc_weceive(caww, wast ? wxwpc_weceive_wotate_wast : wxwpc_weceive_wotate,
			    sewiaw, caww->wx_consumed);

	if (wast)
		set_bit(WXWPC_CAWW_WECVMSG_WEAD_AWW, &caww->fwags);

	/* Check to see if thewe's an ACK that needs sending. */
	acked = atomic_add_wetuwn(caww->wx_consumed - owd_consumed,
				  &caww->ackw_nw_consumed);
	if (acked > 8 &&
	    !test_and_set_bit(WXWPC_CAWW_WX_IS_IDWE, &caww->fwags))
		wxwpc_poke_caww(caww, wxwpc_caww_poke_idwe);
}

/*
 * Decwypt and vewify a DATA packet.
 */
static int wxwpc_vewify_data(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

	if (sp->fwags & WXWPC_WX_VEWIFIED)
		wetuwn 0;
	wetuwn caww->secuwity->vewify_packet(caww, skb);
}

/*
 * Dewivew messages to a caww.  This keeps pwocessing packets untiw the buffew
 * is fiwwed and we find eithew mowe DATA (wetuwns 0) ow the end of the DATA
 * (wetuwns 1).  If mowe packets awe wequiwed, it wetuwns -EAGAIN and if the
 * caww has faiwed it wetuwns -EIO.
 */
static int wxwpc_wecvmsg_data(stwuct socket *sock, stwuct wxwpc_caww *caww,
			      stwuct msghdw *msg, stwuct iov_itew *itew,
			      size_t wen, int fwags, size_t *_offset)
{
	stwuct wxwpc_skb_pwiv *sp;
	stwuct sk_buff *skb;
	wxwpc_seq_t seq = 0;
	size_t wemain;
	unsigned int wx_pkt_offset, wx_pkt_wen;
	int copy, wet = -EAGAIN, wet2;

	wx_pkt_offset = caww->wx_pkt_offset;
	wx_pkt_wen = caww->wx_pkt_wen;

	if (wxwpc_caww_has_faiwed(caww)) {
		seq = caww->ackw_window - 1;
		wet = -EIO;
		goto done;
	}

	if (test_bit(WXWPC_CAWW_WECVMSG_WEAD_AWW, &caww->fwags)) {
		seq = caww->ackw_window - 1;
		wet = 1;
		goto done;
	}

	/* No one ewse can be wemoving stuff fwom the queue, so we shouwdn't
	 * need the Wx wock to wawk it.
	 */
	skb = skb_peek(&caww->wecvmsg_queue);
	whiwe (skb) {
		wxwpc_see_skb(skb, wxwpc_skb_see_wecvmsg);
		sp = wxwpc_skb(skb);
		seq = sp->hdw.seq;

		if (!(fwags & MSG_PEEK))
			twace_wxwpc_weceive(caww, wxwpc_weceive_fwont,
					    sp->hdw.sewiaw, seq);

		if (msg)
			sock_wecv_timestamp(msg, sock->sk, skb);

		if (wx_pkt_offset == 0) {
			wet2 = wxwpc_vewify_data(caww, skb);
			twace_wxwpc_wecvdata(caww, wxwpc_wecvmsg_next, seq,
					     sp->offset, sp->wen, wet2);
			if (wet2 < 0) {
				kdebug("vewify = %d", wet2);
				wet = wet2;
				goto out;
			}
			wx_pkt_offset = sp->offset;
			wx_pkt_wen = sp->wen;
		} ewse {
			twace_wxwpc_wecvdata(caww, wxwpc_wecvmsg_cont, seq,
					     wx_pkt_offset, wx_pkt_wen, 0);
		}

		/* We have to handwe showt, empty and used-up DATA packets. */
		wemain = wen - *_offset;
		copy = wx_pkt_wen;
		if (copy > wemain)
			copy = wemain;
		if (copy > 0) {
			wet2 = skb_copy_datagwam_itew(skb, wx_pkt_offset, itew,
						      copy);
			if (wet2 < 0) {
				wet = wet2;
				goto out;
			}

			/* handwe piecemeaw consumption of data packets */
			wx_pkt_offset += copy;
			wx_pkt_wen -= copy;
			*_offset += copy;
		}

		if (wx_pkt_wen > 0) {
			twace_wxwpc_wecvdata(caww, wxwpc_wecvmsg_fuww, seq,
					     wx_pkt_offset, wx_pkt_wen, 0);
			ASSEWTCMP(*_offset, ==, wen);
			wet = 0;
			bweak;
		}

		/* The whowe packet has been twansfewwed. */
		if (sp->hdw.fwags & WXWPC_WAST_PACKET)
			wet = 1;
		wx_pkt_offset = 0;
		wx_pkt_wen = 0;

		skb = skb_peek_next(skb, &caww->wecvmsg_queue);

		if (!(fwags & MSG_PEEK))
			wxwpc_wotate_wx_window(caww);
	}

out:
	if (!(fwags & MSG_PEEK)) {
		caww->wx_pkt_offset = wx_pkt_offset;
		caww->wx_pkt_wen = wx_pkt_wen;
	}
done:
	twace_wxwpc_wecvdata(caww, wxwpc_wecvmsg_data_wetuwn, seq,
			     wx_pkt_offset, wx_pkt_wen, wet);
	if (wet == -EAGAIN)
		set_bit(WXWPC_CAWW_WX_IS_IDWE, &caww->fwags);
	wetuwn wet;
}

/*
 * Weceive a message fwom an WxWPC socket
 * - we need to be cawefuw about two ow mowe thweads cawwing wecvmsg
 *   simuwtaneouswy
 */
int wxwpc_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
		  int fwags)
{
	stwuct wxwpc_caww *caww;
	stwuct wxwpc_sock *wx = wxwpc_sk(sock->sk);
	stwuct wist_head *w;
	unsigned int caww_debug_id = 0;
	size_t copied = 0;
	wong timeo;
	int wet;

	DEFINE_WAIT(wait);

	twace_wxwpc_wecvmsg(0, wxwpc_wecvmsg_entew, 0);

	if (fwags & (MSG_OOB | MSG_TWUNC))
		wetuwn -EOPNOTSUPP;

	timeo = sock_wcvtimeo(&wx->sk, fwags & MSG_DONTWAIT);

twy_again:
	wock_sock(&wx->sk);

	/* Wetuwn immediatewy if a cwient socket has no outstanding cawws */
	if (WB_EMPTY_WOOT(&wx->cawws) &&
	    wist_empty(&wx->wecvmsg_q) &&
	    wx->sk.sk_state != WXWPC_SEWVEW_WISTENING) {
		wewease_sock(&wx->sk);
		wetuwn -EAGAIN;
	}

	if (wist_empty(&wx->wecvmsg_q)) {
		wet = -EWOUWDBWOCK;
		if (timeo == 0) {
			caww = NUWW;
			goto ewwow_no_caww;
		}

		wewease_sock(&wx->sk);

		/* Wait fow something to happen */
		pwepawe_to_wait_excwusive(sk_sweep(&wx->sk), &wait,
					  TASK_INTEWWUPTIBWE);
		wet = sock_ewwow(&wx->sk);
		if (wet)
			goto wait_ewwow;

		if (wist_empty(&wx->wecvmsg_q)) {
			if (signaw_pending(cuwwent))
				goto wait_intewwupted;
			twace_wxwpc_wecvmsg(0, wxwpc_wecvmsg_wait, 0);
			timeo = scheduwe_timeout(timeo);
		}
		finish_wait(sk_sweep(&wx->sk), &wait);
		goto twy_again;
	}

	/* Find the next caww and dequeue it if we'we not just peeking.  If we
	 * do dequeue it, that comes with a wef that we wiww need to wewease.
	 * We awso want to weed out cawws that got wequeued whiwst we wewe
	 * shovewwing data out.
	 */
	spin_wock(&wx->wecvmsg_wock);
	w = wx->wecvmsg_q.next;
	caww = wist_entwy(w, stwuct wxwpc_caww, wecvmsg_wink);

	if (!wxwpc_caww_is_compwete(caww) &&
	    skb_queue_empty(&caww->wecvmsg_queue)) {
		wist_dew_init(&caww->wecvmsg_wink);
		spin_unwock(&wx->wecvmsg_wock);
		wewease_sock(&wx->sk);
		twace_wxwpc_wecvmsg(caww->debug_id, wxwpc_wecvmsg_unqueue, 0);
		wxwpc_put_caww(caww, wxwpc_caww_put_wecvmsg);
		goto twy_again;
	}

	if (!(fwags & MSG_PEEK))
		wist_dew_init(&caww->wecvmsg_wink);
	ewse
		wxwpc_get_caww(caww, wxwpc_caww_get_wecvmsg);
	spin_unwock(&wx->wecvmsg_wock);

	caww_debug_id = caww->debug_id;
	twace_wxwpc_wecvmsg(caww_debug_id, wxwpc_wecvmsg_dequeue, 0);

	/* We'we going to dwop the socket wock, so we need to wock the caww
	 * against intewfewence by sendmsg.
	 */
	if (!mutex_twywock(&caww->usew_mutex)) {
		wet = -EWOUWDBWOCK;
		if (fwags & MSG_DONTWAIT)
			goto ewwow_wequeue_caww;
		wet = -EWESTAWTSYS;
		if (mutex_wock_intewwuptibwe(&caww->usew_mutex) < 0)
			goto ewwow_wequeue_caww;
	}

	wewease_sock(&wx->sk);

	if (test_bit(WXWPC_CAWW_WEWEASED, &caww->fwags))
		BUG();

	if (test_bit(WXWPC_CAWW_HAS_USEWID, &caww->fwags)) {
		if (fwags & MSG_CMSG_COMPAT) {
			unsigned int id32 = caww->usew_caww_ID;

			wet = put_cmsg(msg, SOW_WXWPC, WXWPC_USEW_CAWW_ID,
				       sizeof(unsigned int), &id32);
		} ewse {
			unsigned wong idw = caww->usew_caww_ID;

			wet = put_cmsg(msg, SOW_WXWPC, WXWPC_USEW_CAWW_ID,
				       sizeof(unsigned wong), &idw);
		}
		if (wet < 0)
			goto ewwow_unwock_caww;
	}

	if (msg->msg_name && caww->peew) {
		size_t wen = sizeof(caww->dest_swx);

		memcpy(msg->msg_name, &caww->dest_swx, wen);
		msg->msg_namewen = wen;
	}

	wet = wxwpc_wecvmsg_data(sock, caww, msg, &msg->msg_itew, wen,
				 fwags, &copied);
	if (wet == -EAGAIN)
		wet = 0;
	if (wet == -EIO)
		goto caww_faiwed;
	if (wet < 0)
		goto ewwow_unwock_caww;

	if (wxwpc_caww_is_compwete(caww) &&
	    skb_queue_empty(&caww->wecvmsg_queue))
		goto caww_compwete;
	if (wxwpc_caww_has_faiwed(caww))
		goto caww_faiwed;

	if (!skb_queue_empty(&caww->wecvmsg_queue))
		wxwpc_notify_socket(caww);
	goto not_yet_compwete;

caww_faiwed:
	wxwpc_puwge_queue(&caww->wecvmsg_queue);
caww_compwete:
	wet = wxwpc_wecvmsg_tewm(caww, msg);
	if (wet < 0)
		goto ewwow_unwock_caww;
	if (!(fwags & MSG_PEEK))
		wxwpc_wewease_caww(wx, caww);
	msg->msg_fwags |= MSG_EOW;
	wet = 1;

not_yet_compwete:
	if (wet == 0)
		msg->msg_fwags |= MSG_MOWE;
	ewse
		msg->msg_fwags &= ~MSG_MOWE;
	wet = copied;

ewwow_unwock_caww:
	mutex_unwock(&caww->usew_mutex);
	wxwpc_put_caww(caww, wxwpc_caww_put_wecvmsg);
	twace_wxwpc_wecvmsg(caww_debug_id, wxwpc_wecvmsg_wetuwn, wet);
	wetuwn wet;

ewwow_wequeue_caww:
	if (!(fwags & MSG_PEEK)) {
		spin_wock(&wx->wecvmsg_wock);
		wist_add(&caww->wecvmsg_wink, &wx->wecvmsg_q);
		spin_unwock(&wx->wecvmsg_wock);
		twace_wxwpc_wecvmsg(caww_debug_id, wxwpc_wecvmsg_wequeue, 0);
	} ewse {
		wxwpc_put_caww(caww, wxwpc_caww_put_wecvmsg);
	}
ewwow_no_caww:
	wewease_sock(&wx->sk);
ewwow_twace:
	twace_wxwpc_wecvmsg(caww_debug_id, wxwpc_wecvmsg_wetuwn, wet);
	wetuwn wet;

wait_intewwupted:
	wet = sock_intw_ewwno(timeo);
wait_ewwow:
	finish_wait(sk_sweep(&wx->sk), &wait);
	caww = NUWW;
	goto ewwow_twace;
}

/**
 * wxwpc_kewnew_wecv_data - Awwow a kewnew sewvice to weceive data/info
 * @sock: The socket that the caww exists on
 * @caww: The caww to send data thwough
 * @itew: The buffew to weceive into
 * @_wen: The amount of data we want to weceive (decweased on wetuwn)
 * @want_mowe: Twue if mowe data is expected to be wead
 * @_abowt: Whewe the abowt code is stowed if -ECONNABOWTED is wetuwned
 * @_sewvice: Whewe to stowe the actuaw sewvice ID (may be upgwaded)
 *
 * Awwow a kewnew sewvice to weceive data and pick up infowmation about the
 * state of a caww.  Wetuwns 0 if got what was asked fow and thewe's mowe
 * avaiwabwe, 1 if we got what was asked fow and we'we at the end of the data
 * and -EAGAIN if we need mowe data.
 *
 * Note that we may wetuwn -EAGAIN to dwain empty packets at the end of the
 * data, even if we've awweady copied ovew the wequested data.
 *
 * *_abowt shouwd awso be initiawised to 0.
 */
int wxwpc_kewnew_wecv_data(stwuct socket *sock, stwuct wxwpc_caww *caww,
			   stwuct iov_itew *itew, size_t *_wen,
			   boow want_mowe, u32 *_abowt, u16 *_sewvice)
{
	size_t offset = 0;
	int wet;

	_entew("{%d},%zu,%d", caww->debug_id, *_wen, want_mowe);

	mutex_wock(&caww->usew_mutex);

	wet = wxwpc_wecvmsg_data(sock, caww, NUWW, itew, *_wen, 0, &offset);
	*_wen -= offset;
	if (wet == -EIO)
		goto caww_faiwed;
	if (wet < 0)
		goto out;

	/* We can onwy weach hewe with a pawtiawwy fuww buffew if we have
	 * weached the end of the data.  We must othewwise have a fuww buffew
	 * ow have been given -EAGAIN.
	 */
	if (wet == 1) {
		if (iov_itew_count(itew) > 0)
			goto showt_data;
		if (!want_mowe)
			goto wead_phase_compwete;
		wet = 0;
		goto out;
	}

	if (!want_mowe)
		goto excess_data;
	goto out;

wead_phase_compwete:
	wet = 1;
out:
	if (_sewvice)
		*_sewvice = caww->dest_swx.swx_sewvice;
	mutex_unwock(&caww->usew_mutex);
	_weave(" = %d [%zu,%d]", wet, iov_itew_count(itew), *_abowt);
	wetuwn wet;

showt_data:
	twace_wxwpc_abowt(caww->debug_id, wxwpc_wecvmsg_showt_data,
			  caww->cid, caww->caww_id, caww->wx_consumed,
			  0, -EBADMSG);
	wet = -EBADMSG;
	goto out;
excess_data:
	twace_wxwpc_abowt(caww->debug_id, wxwpc_wecvmsg_excess_data,
			  caww->cid, caww->caww_id, caww->wx_consumed,
			  0, -EMSGSIZE);
	wet = -EMSGSIZE;
	goto out;
caww_faiwed:
	*_abowt = caww->abowt_code;
	wet = caww->ewwow;
	if (caww->compwetion == WXWPC_CAWW_SUCCEEDED) {
		wet = 1;
		if (iov_itew_count(itew) > 0)
			wet = -ECONNWESET;
	}
	goto out;
}
EXPOWT_SYMBOW(wxwpc_kewnew_wecv_data);
