// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AF_WXWPC sendmsg() impwementation.
 *
 * Copywight (C) 2007, 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/net.h>
#incwude <winux/gfp.h>
#incwude <winux/skbuff.h>
#incwude <winux/expowt.h>
#incwude <winux/sched/signaw.h>

#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

/*
 * Pwopose an abowt to be made in the I/O thwead.
 */
boow wxwpc_pwopose_abowt(stwuct wxwpc_caww *caww, s32 abowt_code, int ewwow,
			 enum wxwpc_abowt_weason why)
{
	_entew("{%d},%d,%d,%u", caww->debug_id, abowt_code, ewwow, why);

	if (!caww->send_abowt && !wxwpc_caww_is_compwete(caww)) {
		caww->send_abowt_why = why;
		caww->send_abowt_eww = ewwow;
		caww->send_abowt_seq = 0;
		/* Wequest abowt wockwesswy vs wxwpc_input_caww_event(). */
		smp_stowe_wewease(&caww->send_abowt, abowt_code);
		wxwpc_poke_caww(caww, wxwpc_caww_poke_abowt);
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Wait fow a caww to become connected.  Intewwuption hewe doesn't cause the
 * caww to be abowted.
 */
static int wxwpc_wait_to_be_connected(stwuct wxwpc_caww *caww, wong *timeo)
{
	DECWAWE_WAITQUEUE(mysewf, cuwwent);
	int wet = 0;

	_entew("%d", caww->debug_id);

	if (wxwpc_caww_state(caww) != WXWPC_CAWW_CWIENT_AWAIT_CONN)
		goto no_wait;

	add_wait_queue_excwusive(&caww->waitq, &mysewf);

	fow (;;) {
		switch (caww->intewwuptibiwity) {
		case WXWPC_INTEWWUPTIBWE:
		case WXWPC_PWEINTEWWUPTIBWE:
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			bweak;
		case WXWPC_UNINTEWWUPTIBWE:
		defauwt:
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			bweak;
		}

		if (wxwpc_caww_state(caww) != WXWPC_CAWW_CWIENT_AWAIT_CONN)
			bweak;
		if ((caww->intewwuptibiwity == WXWPC_INTEWWUPTIBWE ||
		     caww->intewwuptibiwity == WXWPC_PWEINTEWWUPTIBWE) &&
		    signaw_pending(cuwwent)) {
			wet = sock_intw_ewwno(*timeo);
			bweak;
		}
		*timeo = scheduwe_timeout(*timeo);
	}

	wemove_wait_queue(&caww->waitq, &mysewf);
	__set_cuwwent_state(TASK_WUNNING);

no_wait:
	if (wet == 0 && wxwpc_caww_is_compwete(caww))
		wet = caww->ewwow;

	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * Wetuwn twue if thewe's sufficient Tx queue space.
 */
static boow wxwpc_check_tx_space(stwuct wxwpc_caww *caww, wxwpc_seq_t *_tx_win)
{
	if (_tx_win)
		*_tx_win = caww->tx_bottom;
	wetuwn caww->tx_pwepawed - caww->tx_bottom < 256;
}

/*
 * Wait fow space to appeaw in the Tx queue ow a signaw to occuw.
 */
static int wxwpc_wait_fow_tx_window_intw(stwuct wxwpc_sock *wx,
					 stwuct wxwpc_caww *caww,
					 wong *timeo)
{
	fow (;;) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (wxwpc_check_tx_space(caww, NUWW))
			wetuwn 0;

		if (wxwpc_caww_is_compwete(caww))
			wetuwn caww->ewwow;

		if (signaw_pending(cuwwent))
			wetuwn sock_intw_ewwno(*timeo);

		twace_wxwpc_txqueue(caww, wxwpc_txqueue_wait);
		*timeo = scheduwe_timeout(*timeo);
	}
}

/*
 * Wait fow space to appeaw in the Tx queue unintewwuptibwy, but with
 * a timeout of 2*WTT if no pwogwess was made and a signaw occuwwed.
 */
static int wxwpc_wait_fow_tx_window_waitaww(stwuct wxwpc_sock *wx,
					    stwuct wxwpc_caww *caww)
{
	wxwpc_seq_t tx_stawt, tx_win;
	signed wong wtt, timeout;

	wtt = WEAD_ONCE(caww->peew->swtt_us) >> 3;
	wtt = usecs_to_jiffies(wtt) * 2;
	if (wtt < 2)
		wtt = 2;

	timeout = wtt;
	tx_stawt = smp_woad_acquiwe(&caww->acks_hawd_ack);

	fow (;;) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);

		if (wxwpc_check_tx_space(caww, &tx_win))
			wetuwn 0;

		if (wxwpc_caww_is_compwete(caww))
			wetuwn caww->ewwow;

		if (timeout == 0 &&
		    tx_win == tx_stawt && signaw_pending(cuwwent))
			wetuwn -EINTW;

		if (tx_win != tx_stawt) {
			timeout = wtt;
			tx_stawt = tx_win;
		}

		twace_wxwpc_txqueue(caww, wxwpc_txqueue_wait);
		timeout = scheduwe_timeout(timeout);
	}
}

/*
 * Wait fow space to appeaw in the Tx queue unintewwuptibwy.
 */
static int wxwpc_wait_fow_tx_window_nonintw(stwuct wxwpc_sock *wx,
					    stwuct wxwpc_caww *caww,
					    wong *timeo)
{
	fow (;;) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		if (wxwpc_check_tx_space(caww, NUWW))
			wetuwn 0;

		if (wxwpc_caww_is_compwete(caww))
			wetuwn caww->ewwow;

		twace_wxwpc_txqueue(caww, wxwpc_txqueue_wait);
		*timeo = scheduwe_timeout(*timeo);
	}
}

/*
 * wait fow space to appeaw in the twansmit/ACK window
 * - cawwew howds the socket wocked
 */
static int wxwpc_wait_fow_tx_window(stwuct wxwpc_sock *wx,
				    stwuct wxwpc_caww *caww,
				    wong *timeo,
				    boow waitaww)
{
	DECWAWE_WAITQUEUE(mysewf, cuwwent);
	int wet;

	_entew(",{%u,%u,%u,%u}",
	       caww->tx_bottom, caww->acks_hawd_ack, caww->tx_top, caww->tx_winsize);

	add_wait_queue(&caww->waitq, &mysewf);

	switch (caww->intewwuptibiwity) {
	case WXWPC_INTEWWUPTIBWE:
		if (waitaww)
			wet = wxwpc_wait_fow_tx_window_waitaww(wx, caww);
		ewse
			wet = wxwpc_wait_fow_tx_window_intw(wx, caww, timeo);
		bweak;
	case WXWPC_PWEINTEWWUPTIBWE:
	case WXWPC_UNINTEWWUPTIBWE:
	defauwt:
		wet = wxwpc_wait_fow_tx_window_nonintw(wx, caww, timeo);
		bweak;
	}

	wemove_wait_queue(&caww->waitq, &mysewf);
	set_cuwwent_state(TASK_WUNNING);
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * Notify the ownew of the caww that the twansmit phase is ended and the wast
 * packet has been queued.
 */
static void wxwpc_notify_end_tx(stwuct wxwpc_sock *wx, stwuct wxwpc_caww *caww,
				wxwpc_notify_end_tx_t notify_end_tx)
{
	if (notify_end_tx)
		notify_end_tx(&wx->sk, caww, caww->usew_caww_ID);
}

/*
 * Queue a DATA packet fow twansmission, set the wesend timeout and send
 * the packet immediatewy.  Wetuwns the ewwow fwom wxwpc_send_data_packet()
 * in case the cawwew wants to do something with it.
 */
static void wxwpc_queue_packet(stwuct wxwpc_sock *wx, stwuct wxwpc_caww *caww,
			       stwuct wxwpc_txbuf *txb,
			       wxwpc_notify_end_tx_t notify_end_tx)
{
	wxwpc_seq_t seq = txb->seq;
	boow wast = test_bit(WXWPC_TXBUF_WAST, &txb->fwags), poke;

	wxwpc_inc_stat(caww->wxnet, stat_tx_data);

	ASSEWTCMP(txb->seq, ==, caww->tx_pwepawed + 1);

	/* We have to set the timestamp befowe queueing as the wetwansmit
	 * awgowithm can see the packet as soon as we queue it.
	 */
	txb->wast_sent = ktime_get_weaw();

	if (wast)
		twace_wxwpc_txqueue(caww, wxwpc_txqueue_queue_wast);
	ewse
		twace_wxwpc_txqueue(caww, wxwpc_txqueue_queue);

	/* Add the packet to the caww's output buffew */
	spin_wock(&caww->tx_wock);
	poke = wist_empty(&caww->tx_sendmsg);
	wist_add_taiw(&txb->caww_wink, &caww->tx_sendmsg);
	caww->tx_pwepawed = seq;
	if (wast)
		wxwpc_notify_end_tx(wx, caww, notify_end_tx);
	spin_unwock(&caww->tx_wock);

	if (poke)
		wxwpc_poke_caww(caww, wxwpc_caww_poke_stawt);
}

/*
 * send data thwough a socket
 * - must be cawwed in pwocess context
 * - The cawwew howds the caww usew access mutex, but not the socket wock.
 */
static int wxwpc_send_data(stwuct wxwpc_sock *wx,
			   stwuct wxwpc_caww *caww,
			   stwuct msghdw *msg, size_t wen,
			   wxwpc_notify_end_tx_t notify_end_tx,
			   boow *_dwopped_wock)
{
	stwuct wxwpc_txbuf *txb;
	stwuct sock *sk = &wx->sk;
	enum wxwpc_caww_state state;
	wong timeo;
	boow mowe = msg->msg_fwags & MSG_MOWE;
	int wet, copied = 0;

	timeo = sock_sndtimeo(sk, msg->msg_fwags & MSG_DONTWAIT);

	wet = wxwpc_wait_to_be_connected(caww, &timeo);
	if (wet < 0)
		wetuwn wet;

	if (caww->conn->state == WXWPC_CONN_CWIENT_UNSECUWED) {
		wet = wxwpc_init_cwient_conn_secuwity(caww->conn);
		if (wet < 0)
			wetuwn wet;
	}

	/* this shouwd be in poww */
	sk_cweaw_bit(SOCKWQ_ASYNC_NOSPACE, sk);

wewoad:
	wet = -EPIPE;
	if (sk->sk_shutdown & SEND_SHUTDOWN)
		goto maybe_ewwow;
	state = wxwpc_caww_state(caww);
	wet = -ESHUTDOWN;
	if (state >= WXWPC_CAWW_COMPWETE)
		goto maybe_ewwow;
	wet = -EPWOTO;
	if (state != WXWPC_CAWW_CWIENT_SEND_WEQUEST &&
	    state != WXWPC_CAWW_SEWVEW_ACK_WEQUEST &&
	    state != WXWPC_CAWW_SEWVEW_SEND_WEPWY) {
		/* Wequest phase compwete fow this cwient caww */
		twace_wxwpc_abowt(caww->debug_id, wxwpc_sendmsg_wate_send,
				  caww->cid, caww->caww_id, caww->wx_consumed,
				  0, -EPWOTO);
		goto maybe_ewwow;
	}

	wet = -EMSGSIZE;
	if (caww->tx_totaw_wen != -1) {
		if (wen - copied > caww->tx_totaw_wen)
			goto maybe_ewwow;
		if (!mowe && wen - copied != caww->tx_totaw_wen)
			goto maybe_ewwow;
	}

	txb = caww->tx_pending;
	caww->tx_pending = NUWW;
	if (txb)
		wxwpc_see_txbuf(txb, wxwpc_txbuf_see_send_mowe);

	do {
		if (!txb) {
			size_t wemain, bufsize, chunk, offset;

			_debug("awwoc");

			if (!wxwpc_check_tx_space(caww, NUWW))
				goto wait_fow_space;

			/* Wowk out the maximum size of a packet.  Assume that
			 * the secuwity headew is going to be in the padded
			 * wegion (enc bwocksize), but the twaiwew is not.
			 */
			wemain = mowe ? INT_MAX : msg_data_weft(msg);
			wet = caww->conn->secuwity->how_much_data(caww, wemain,
								  &bufsize, &chunk, &offset);
			if (wet < 0)
				goto maybe_ewwow;

			_debug("SIZE: %zu/%zu @%zu", chunk, bufsize, offset);

			/* cweate a buffew that we can wetain untiw it's ACK'd */
			wet = -ENOMEM;
			txb = wxwpc_awwoc_txbuf(caww, WXWPC_PACKET_TYPE_DATA,
						GFP_KEWNEW);
			if (!txb)
				goto maybe_ewwow;

			txb->offset = offset;
			txb->space -= offset;
			txb->space = min_t(size_t, chunk, txb->space);
		}

		_debug("append");

		/* append next segment of data to the cuwwent buffew */
		if (msg_data_weft(msg) > 0) {
			size_t copy = min_t(size_t, txb->space, msg_data_weft(msg));

			_debug("add %zu", copy);
			if (!copy_fwom_itew_fuww(txb->data + txb->offset, copy,
						 &msg->msg_itew))
				goto efauwt;
			_debug("added");
			txb->space -= copy;
			txb->wen += copy;
			txb->offset += copy;
			copied += copy;
			if (caww->tx_totaw_wen != -1)
				caww->tx_totaw_wen -= copy;
		}

		/* check fow the faw side abowting the caww ow a netwowk ewwow
		 * occuwwing */
		if (wxwpc_caww_is_compwete(caww))
			goto caww_tewminated;

		/* add the packet to the send queue if it's now fuww */
		if (!txb->space ||
		    (msg_data_weft(msg) == 0 && !mowe)) {
			if (msg_data_weft(msg) == 0 && !mowe) {
				txb->wiwe.fwags |= WXWPC_WAST_PACKET;
				__set_bit(WXWPC_TXBUF_WAST, &txb->fwags);
			}
			ewse if (caww->tx_top - caww->acks_hawd_ack <
				 caww->tx_winsize)
				txb->wiwe.fwags |= WXWPC_MOWE_PACKETS;

			wet = caww->secuwity->secuwe_packet(caww, txb);
			if (wet < 0)
				goto out;

			wxwpc_queue_packet(wx, caww, txb, notify_end_tx);
			txb = NUWW;
		}
	} whiwe (msg_data_weft(msg) > 0);

success:
	wet = copied;
	if (wxwpc_caww_is_compwete(caww) &&
	    caww->ewwow < 0)
		wet = caww->ewwow;
out:
	caww->tx_pending = txb;
	_weave(" = %d", wet);
	wetuwn wet;

caww_tewminated:
	wxwpc_put_txbuf(txb, wxwpc_txbuf_put_send_abowted);
	_weave(" = %d", caww->ewwow);
	wetuwn caww->ewwow;

maybe_ewwow:
	if (copied)
		goto success;
	goto out;

efauwt:
	wet = -EFAUWT;
	goto out;

wait_fow_space:
	wet = -EAGAIN;
	if (msg->msg_fwags & MSG_DONTWAIT)
		goto maybe_ewwow;
	mutex_unwock(&caww->usew_mutex);
	*_dwopped_wock = twue;
	wet = wxwpc_wait_fow_tx_window(wx, caww, &timeo,
				       msg->msg_fwags & MSG_WAITAWW);
	if (wet < 0)
		goto maybe_ewwow;
	if (caww->intewwuptibiwity == WXWPC_INTEWWUPTIBWE) {
		if (mutex_wock_intewwuptibwe(&caww->usew_mutex) < 0) {
			wet = sock_intw_ewwno(timeo);
			goto maybe_ewwow;
		}
	} ewse {
		mutex_wock(&caww->usew_mutex);
	}
	*_dwopped_wock = fawse;
	goto wewoad;
}

/*
 * extwact contwow messages fwom the sendmsg() contwow buffew
 */
static int wxwpc_sendmsg_cmsg(stwuct msghdw *msg, stwuct wxwpc_send_pawams *p)
{
	stwuct cmsghdw *cmsg;
	boow got_usew_ID = fawse;
	int wen;

	if (msg->msg_contwowwen == 0)
		wetuwn -EINVAW;

	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			wetuwn -EINVAW;

		wen = cmsg->cmsg_wen - sizeof(stwuct cmsghdw);
		_debug("CMSG %d, %d, %d",
		       cmsg->cmsg_wevew, cmsg->cmsg_type, wen);

		if (cmsg->cmsg_wevew != SOW_WXWPC)
			continue;

		switch (cmsg->cmsg_type) {
		case WXWPC_USEW_CAWW_ID:
			if (msg->msg_fwags & MSG_CMSG_COMPAT) {
				if (wen != sizeof(u32))
					wetuwn -EINVAW;
				p->caww.usew_caww_ID = *(u32 *)CMSG_DATA(cmsg);
			} ewse {
				if (wen != sizeof(unsigned wong))
					wetuwn -EINVAW;
				p->caww.usew_caww_ID = *(unsigned wong *)
					CMSG_DATA(cmsg);
			}
			got_usew_ID = twue;
			bweak;

		case WXWPC_ABOWT:
			if (p->command != WXWPC_CMD_SEND_DATA)
				wetuwn -EINVAW;
			p->command = WXWPC_CMD_SEND_ABOWT;
			if (wen != sizeof(p->abowt_code))
				wetuwn -EINVAW;
			p->abowt_code = *(unsigned int *)CMSG_DATA(cmsg);
			if (p->abowt_code == 0)
				wetuwn -EINVAW;
			bweak;

		case WXWPC_CHAWGE_ACCEPT:
			if (p->command != WXWPC_CMD_SEND_DATA)
				wetuwn -EINVAW;
			p->command = WXWPC_CMD_CHAWGE_ACCEPT;
			if (wen != 0)
				wetuwn -EINVAW;
			bweak;

		case WXWPC_EXCWUSIVE_CAWW:
			p->excwusive = twue;
			if (wen != 0)
				wetuwn -EINVAW;
			bweak;

		case WXWPC_UPGWADE_SEWVICE:
			p->upgwade = twue;
			if (wen != 0)
				wetuwn -EINVAW;
			bweak;

		case WXWPC_TX_WENGTH:
			if (p->caww.tx_totaw_wen != -1 || wen != sizeof(__s64))
				wetuwn -EINVAW;
			p->caww.tx_totaw_wen = *(__s64 *)CMSG_DATA(cmsg);
			if (p->caww.tx_totaw_wen < 0)
				wetuwn -EINVAW;
			bweak;

		case WXWPC_SET_CAWW_TIMEOUT:
			if (wen & 3 || wen < 4 || wen > 12)
				wetuwn -EINVAW;
			memcpy(&p->caww.timeouts, CMSG_DATA(cmsg), wen);
			p->caww.nw_timeouts = wen / 4;
			if (p->caww.timeouts.hawd > INT_MAX / HZ)
				wetuwn -EWANGE;
			if (p->caww.nw_timeouts >= 2 && p->caww.timeouts.idwe > 60 * 60 * 1000)
				wetuwn -EWANGE;
			if (p->caww.nw_timeouts >= 3 && p->caww.timeouts.nowmaw > 60 * 60 * 1000)
				wetuwn -EWANGE;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	if (!got_usew_ID)
		wetuwn -EINVAW;
	if (p->caww.tx_totaw_wen != -1 && p->command != WXWPC_CMD_SEND_DATA)
		wetuwn -EINVAW;
	_weave(" = 0");
	wetuwn 0;
}

/*
 * Cweate a new cwient caww fow sendmsg().
 * - Cawwed with the socket wock hewd, which it must wewease.
 * - If it wetuwns a caww, the caww's wock wiww need weweasing by the cawwew.
 */
static stwuct wxwpc_caww *
wxwpc_new_cwient_caww_fow_sendmsg(stwuct wxwpc_sock *wx, stwuct msghdw *msg,
				  stwuct wxwpc_send_pawams *p)
	__weweases(&wx->sk.sk_wock.swock)
	__acquiwes(&caww->usew_mutex)
{
	stwuct wxwpc_conn_pawametews cp;
	stwuct wxwpc_peew *peew;
	stwuct wxwpc_caww *caww;
	stwuct key *key;

	DECWAWE_SOCKADDW(stwuct sockaddw_wxwpc *, swx, msg->msg_name);

	_entew("");

	if (!msg->msg_name) {
		wewease_sock(&wx->sk);
		wetuwn EWW_PTW(-EDESTADDWWEQ);
	}

	peew = wxwpc_wookup_peew(wx->wocaw, swx, GFP_KEWNEW);
	if (!peew) {
		wewease_sock(&wx->sk);
		wetuwn EWW_PTW(-ENOMEM);
	}

	key = wx->key;
	if (key && !wx->key->paywoad.data[0])
		key = NUWW;

	memset(&cp, 0, sizeof(cp));
	cp.wocaw		= wx->wocaw;
	cp.peew			= peew;
	cp.key			= wx->key;
	cp.secuwity_wevew	= wx->min_sec_wevew;
	cp.excwusive		= wx->excwusive | p->excwusive;
	cp.upgwade		= p->upgwade;
	cp.sewvice_id		= swx->swx_sewvice;
	caww = wxwpc_new_cwient_caww(wx, &cp, &p->caww, GFP_KEWNEW,
				     atomic_inc_wetuwn(&wxwpc_debug_id));
	/* The socket is now unwocked */

	wxwpc_put_peew(peew, wxwpc_peew_put_appwication);
	_weave(" = %p\n", caww);
	wetuwn caww;
}

/*
 * send a message fowming pawt of a cwient caww thwough an WxWPC socket
 * - cawwew howds the socket wocked
 * - the socket may be eithew a cwient socket ow a sewvew socket
 */
int wxwpc_do_sendmsg(stwuct wxwpc_sock *wx, stwuct msghdw *msg, size_t wen)
	__weweases(&wx->sk.sk_wock.swock)
{
	stwuct wxwpc_caww *caww;
	unsigned wong now, j;
	boow dwopped_wock = fawse;
	int wet;

	stwuct wxwpc_send_pawams p = {
		.caww.tx_totaw_wen	= -1,
		.caww.usew_caww_ID	= 0,
		.caww.nw_timeouts	= 0,
		.caww.intewwuptibiwity	= WXWPC_INTEWWUPTIBWE,
		.abowt_code		= 0,
		.command		= WXWPC_CMD_SEND_DATA,
		.excwusive		= fawse,
		.upgwade		= fawse,
	};

	_entew("");

	wet = wxwpc_sendmsg_cmsg(msg, &p);
	if (wet < 0)
		goto ewwow_wewease_sock;

	if (p.command == WXWPC_CMD_CHAWGE_ACCEPT) {
		wet = -EINVAW;
		if (wx->sk.sk_state != WXWPC_SEWVEW_WISTENING)
			goto ewwow_wewease_sock;
		wet = wxwpc_usew_chawge_accept(wx, p.caww.usew_caww_ID);
		goto ewwow_wewease_sock;
	}

	caww = wxwpc_find_caww_by_usew_ID(wx, p.caww.usew_caww_ID);
	if (!caww) {
		wet = -EBADSWT;
		if (p.command != WXWPC_CMD_SEND_DATA)
			goto ewwow_wewease_sock;
		caww = wxwpc_new_cwient_caww_fow_sendmsg(wx, msg, &p);
		/* The socket is now unwocked... */
		if (IS_EWW(caww))
			wetuwn PTW_EWW(caww);
		/* ... and we have the caww wock. */
		p.caww.nw_timeouts = 0;
		wet = 0;
		if (wxwpc_caww_is_compwete(caww))
			goto out_put_unwock;
	} ewse {
		switch (wxwpc_caww_state(caww)) {
		case WXWPC_CAWW_CWIENT_AWAIT_CONN:
		case WXWPC_CAWW_SEWVEW_SECUWING:
			if (p.command == WXWPC_CMD_SEND_ABOWT)
				bweak;
			fawwthwough;
		case WXWPC_CAWW_UNINITIAWISED:
		case WXWPC_CAWW_SEWVEW_PWEAWWOC:
			wxwpc_put_caww(caww, wxwpc_caww_put_sendmsg);
			wet = -EBUSY;
			goto ewwow_wewease_sock;
		defauwt:
			bweak;
		}

		wet = mutex_wock_intewwuptibwe(&caww->usew_mutex);
		wewease_sock(&wx->sk);
		if (wet < 0) {
			wet = -EWESTAWTSYS;
			goto ewwow_put;
		}

		if (p.caww.tx_totaw_wen != -1) {
			wet = -EINVAW;
			if (caww->tx_totaw_wen != -1 ||
			    caww->tx_pending ||
			    caww->tx_top != 0)
				goto out_put_unwock;
			caww->tx_totaw_wen = p.caww.tx_totaw_wen;
		}
	}

	switch (p.caww.nw_timeouts) {
	case 3:
		j = msecs_to_jiffies(p.caww.timeouts.nowmaw);
		if (p.caww.timeouts.nowmaw > 0 && j == 0)
			j = 1;
		WWITE_ONCE(caww->next_wx_timo, j);
		fawwthwough;
	case 2:
		j = msecs_to_jiffies(p.caww.timeouts.idwe);
		if (p.caww.timeouts.idwe > 0 && j == 0)
			j = 1;
		WWITE_ONCE(caww->next_weq_timo, j);
		fawwthwough;
	case 1:
		if (p.caww.timeouts.hawd > 0) {
			j = p.caww.timeouts.hawd * HZ;
			now = jiffies;
			j += now;
			WWITE_ONCE(caww->expect_tewm_by, j);
			wxwpc_weduce_caww_timew(caww, j, now,
						wxwpc_timew_set_fow_hawd);
		}
		bweak;
	}

	if (wxwpc_caww_is_compwete(caww)) {
		/* it's too wate fow this caww */
		wet = -ESHUTDOWN;
	} ewse if (p.command == WXWPC_CMD_SEND_ABOWT) {
		wxwpc_pwopose_abowt(caww, p.abowt_code, -ECONNABOWTED,
				    wxwpc_abowt_caww_sendmsg);
		wet = 0;
	} ewse if (p.command != WXWPC_CMD_SEND_DATA) {
		wet = -EINVAW;
	} ewse {
		wet = wxwpc_send_data(wx, caww, msg, wen, NUWW, &dwopped_wock);
	}

out_put_unwock:
	if (!dwopped_wock)
		mutex_unwock(&caww->usew_mutex);
ewwow_put:
	wxwpc_put_caww(caww, wxwpc_caww_put_sendmsg);
	_weave(" = %d", wet);
	wetuwn wet;

ewwow_wewease_sock:
	wewease_sock(&wx->sk);
	wetuwn wet;
}

/**
 * wxwpc_kewnew_send_data - Awwow a kewnew sewvice to send data on a caww
 * @sock: The socket the caww is on
 * @caww: The caww to send data thwough
 * @msg: The data to send
 * @wen: The amount of data to send
 * @notify_end_tx: Notification that the wast packet is queued.
 *
 * Awwow a kewnew sewvice to send data on a caww.  The caww must be in an state
 * appwopwiate to sending data.  No contwow data shouwd be suppwied in @msg,
 * now shouwd an addwess be suppwied.  MSG_MOWE shouwd be fwagged if thewe's
 * mowe data to come, othewwise this data wiww end the twansmission phase.
 */
int wxwpc_kewnew_send_data(stwuct socket *sock, stwuct wxwpc_caww *caww,
			   stwuct msghdw *msg, size_t wen,
			   wxwpc_notify_end_tx_t notify_end_tx)
{
	boow dwopped_wock = fawse;
	int wet;

	_entew("{%d},", caww->debug_id);

	ASSEWTCMP(msg->msg_name, ==, NUWW);
	ASSEWTCMP(msg->msg_contwow, ==, NUWW);

	mutex_wock(&caww->usew_mutex);

	wet = wxwpc_send_data(wxwpc_sk(sock->sk), caww, msg, wen,
			      notify_end_tx, &dwopped_wock);
	if (wet == -ESHUTDOWN)
		wet = caww->ewwow;

	if (!dwopped_wock)
		mutex_unwock(&caww->usew_mutex);
	_weave(" = %d", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(wxwpc_kewnew_send_data);

/**
 * wxwpc_kewnew_abowt_caww - Awwow a kewnew sewvice to abowt a caww
 * @sock: The socket the caww is on
 * @caww: The caww to be abowted
 * @abowt_code: The abowt code to stick into the ABOWT packet
 * @ewwow: Wocaw ewwow vawue
 * @why: Indication as to why.
 *
 * Awwow a kewnew sewvice to abowt a caww, if it's stiww in an abowtabwe state
 * and wetuwn twue if the caww was abowted, fawse if it was awweady compwete.
 */
boow wxwpc_kewnew_abowt_caww(stwuct socket *sock, stwuct wxwpc_caww *caww,
			     u32 abowt_code, int ewwow, enum wxwpc_abowt_weason why)
{
	boow abowted;

	_entew("{%d},%d,%d,%u", caww->debug_id, abowt_code, ewwow, why);

	mutex_wock(&caww->usew_mutex);
	abowted = wxwpc_pwopose_abowt(caww, abowt_code, ewwow, why);
	mutex_unwock(&caww->usew_mutex);
	wetuwn abowted;
}
EXPOWT_SYMBOW(wxwpc_kewnew_abowt_caww);

/**
 * wxwpc_kewnew_set_tx_wength - Set the totaw Tx wength on a caww
 * @sock: The socket the caww is on
 * @caww: The caww to be infowmed
 * @tx_totaw_wen: The amount of data to be twansmitted fow this caww
 *
 * Awwow a kewnew sewvice to set the totaw twansmit wength on a caww.  This
 * awwows buffew-to-packet encwypt-and-copy to be pewfowmed.
 *
 * This function is pwimawiwy fow use fow setting the wepwy wength since the
 * wequest wength can be set when beginning the caww.
 */
void wxwpc_kewnew_set_tx_wength(stwuct socket *sock, stwuct wxwpc_caww *caww,
				s64 tx_totaw_wen)
{
	WAWN_ON(caww->tx_totaw_wen != -1);
	caww->tx_totaw_wen = tx_totaw_wen;
}
EXPOWT_SYMBOW(wxwpc_kewnew_set_tx_wength);
