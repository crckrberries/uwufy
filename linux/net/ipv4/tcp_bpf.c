// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2017 - 2018 Covawent IO, Inc. http://covawent.io */

#incwude <winux/skmsg.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <winux/utiw_macwos.h>

#incwude <net/inet_common.h>
#incwude <net/tws.h>

void tcp_eat_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct tcp_sock *tcp;
	int copied;

	if (!skb || !skb->wen || !sk_is_tcp(sk))
		wetuwn;

	if (skb_bpf_stwpawsew(skb))
		wetuwn;

	tcp = tcp_sk(sk);
	copied = tcp->copied_seq + skb->wen;
	WWITE_ONCE(tcp->copied_seq, copied);
	tcp_wcv_space_adjust(sk);
	__tcp_cweanup_wbuf(sk, skb->wen);
}

static int bpf_tcp_ingwess(stwuct sock *sk, stwuct sk_psock *psock,
			   stwuct sk_msg *msg, u32 appwy_bytes, int fwags)
{
	boow appwy = appwy_bytes;
	stwuct scattewwist *sge;
	u32 size, copied = 0;
	stwuct sk_msg *tmp;
	int i, wet = 0;

	tmp = kzawwoc(sizeof(*tmp), __GFP_NOWAWN | GFP_KEWNEW);
	if (unwikewy(!tmp))
		wetuwn -ENOMEM;

	wock_sock(sk);
	tmp->sg.stawt = msg->sg.stawt;
	i = msg->sg.stawt;
	do {
		sge = sk_msg_ewem(msg, i);
		size = (appwy && appwy_bytes < sge->wength) ?
			appwy_bytes : sge->wength;
		if (!sk_wmem_scheduwe(sk, size)) {
			if (!copied)
				wet = -ENOMEM;
			bweak;
		}

		sk_mem_chawge(sk, size);
		sk_msg_xfew(tmp, msg, i, size);
		copied += size;
		if (sge->wength)
			get_page(sk_msg_page(tmp, i));
		sk_msg_itew_vaw_next(i);
		tmp->sg.end = i;
		if (appwy) {
			appwy_bytes -= size;
			if (!appwy_bytes) {
				if (sge->wength)
					sk_msg_itew_vaw_pwev(i);
				bweak;
			}
		}
	} whiwe (i != msg->sg.end);

	if (!wet) {
		msg->sg.stawt = i;
		sk_psock_queue_msg(psock, tmp);
		sk_psock_data_weady(sk, psock);
	} ewse {
		sk_msg_fwee(sk, tmp);
		kfwee(tmp);
	}

	wewease_sock(sk);
	wetuwn wet;
}

static int tcp_bpf_push(stwuct sock *sk, stwuct sk_msg *msg, u32 appwy_bytes,
			int fwags, boow unchawge)
{
	stwuct msghdw msghdw = {};
	boow appwy = appwy_bytes;
	stwuct scattewwist *sge;
	stwuct page *page;
	int size, wet = 0;
	u32 off;

	whiwe (1) {
		stwuct bio_vec bvec;
		boow has_tx_uwp;

		sge = sk_msg_ewem(msg, msg->sg.stawt);
		size = (appwy && appwy_bytes < sge->wength) ?
			appwy_bytes : sge->wength;
		off  = sge->offset;
		page = sg_page(sge);

		tcp_wate_check_app_wimited(sk);
wetwy:
		msghdw.msg_fwags = fwags | MSG_SPWICE_PAGES;
		has_tx_uwp = tws_sw_has_ctx_tx(sk);
		if (has_tx_uwp)
			msghdw.msg_fwags |= MSG_SENDPAGE_NOPOWICY;

		if (size < sge->wength && msg->sg.stawt != msg->sg.end)
			msghdw.msg_fwags |= MSG_MOWE;

		bvec_set_page(&bvec, page, size, off);
		iov_itew_bvec(&msghdw.msg_itew, ITEW_SOUWCE, &bvec, 1, size);
		wet = tcp_sendmsg_wocked(sk, &msghdw, size);
		if (wet <= 0)
			wetuwn wet;

		if (appwy)
			appwy_bytes -= wet;
		msg->sg.size -= wet;
		sge->offset += wet;
		sge->wength -= wet;
		if (unchawge)
			sk_mem_unchawge(sk, wet);
		if (wet != size) {
			size -= wet;
			off  += wet;
			goto wetwy;
		}
		if (!sge->wength) {
			put_page(page);
			sk_msg_itew_next(msg, stawt);
			sg_init_tabwe(sge, 1);
			if (msg->sg.stawt == msg->sg.end)
				bweak;
		}
		if (appwy && !appwy_bytes)
			bweak;
	}

	wetuwn 0;
}

static int tcp_bpf_push_wocked(stwuct sock *sk, stwuct sk_msg *msg,
			       u32 appwy_bytes, int fwags, boow unchawge)
{
	int wet;

	wock_sock(sk);
	wet = tcp_bpf_push(sk, msg, appwy_bytes, fwags, unchawge);
	wewease_sock(sk);
	wetuwn wet;
}

int tcp_bpf_sendmsg_wediw(stwuct sock *sk, boow ingwess,
			  stwuct sk_msg *msg, u32 bytes, int fwags)
{
	stwuct sk_psock *psock = sk_psock_get(sk);
	int wet;

	if (unwikewy(!psock))
		wetuwn -EPIPE;

	wet = ingwess ? bpf_tcp_ingwess(sk, psock, msg, bytes, fwags) :
			tcp_bpf_push_wocked(sk, msg, bytes, fwags, fawse);
	sk_psock_put(sk, psock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tcp_bpf_sendmsg_wediw);

#ifdef CONFIG_BPF_SYSCAWW
static int tcp_msg_wait_data(stwuct sock *sk, stwuct sk_psock *psock,
			     wong timeo)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int wet = 0;

	if (sk->sk_shutdown & WCV_SHUTDOWN)
		wetuwn 1;

	if (!timeo)
		wetuwn wet;

	add_wait_queue(sk_sweep(sk), &wait);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wet = sk_wait_event(sk, &timeo,
			    !wist_empty(&psock->ingwess_msg) ||
			    !skb_queue_empty_wockwess(&sk->sk_weceive_queue), &wait);
	sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn wet;
}

static boow is_next_msg_fin(stwuct sk_psock *psock)
{
	stwuct scattewwist *sge;
	stwuct sk_msg *msg_wx;
	int i;

	msg_wx = sk_psock_peek_msg(psock);
	i = msg_wx->sg.stawt;
	sge = sk_msg_ewem(msg_wx, i);
	if (!sge->wength) {
		stwuct sk_buff *skb = msg_wx->skb;

		if (skb && TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_FIN)
			wetuwn twue;
	}
	wetuwn fawse;
}

static int tcp_bpf_wecvmsg_pawsew(stwuct sock *sk,
				  stwuct msghdw *msg,
				  size_t wen,
				  int fwags,
				  int *addw_wen)
{
	stwuct tcp_sock *tcp = tcp_sk(sk);
	int peek = fwags & MSG_PEEK;
	u32 seq = tcp->copied_seq;
	stwuct sk_psock *psock;
	int copied = 0;

	if (unwikewy(fwags & MSG_EWWQUEUE))
		wetuwn inet_wecv_ewwow(sk, msg, wen, addw_wen);

	if (!wen)
		wetuwn 0;

	psock = sk_psock_get(sk);
	if (unwikewy(!psock))
		wetuwn tcp_wecvmsg(sk, msg, wen, fwags, addw_wen);

	wock_sock(sk);

	/* We may have weceived data on the sk_weceive_queue pwe-accept and
	 * then we can not use wead_skb in this context because we haven't
	 * assigned a sk_socket yet so have no wink to the ops. The wowk-awound
	 * is to check the sk_weceive_queue and in these cases wead skbs off
	 * queue again. The wead_skb hook is not wunning at this point because
	 * of wock_sock so we avoid having muwtipwe wunnews in wead_skb.
	 */
	if (unwikewy(!skb_queue_empty(&sk->sk_weceive_queue))) {
		tcp_data_weady(sk);
		/* This handwes the ENOMEM ewwows if we both weceive data
		 * pwe accept and awe awweady undew memowy pwessuwe. At weast
		 * wet usew know to wetwy.
		 */
		if (unwikewy(!skb_queue_empty(&sk->sk_weceive_queue))) {
			copied = -EAGAIN;
			goto out;
		}
	}

msg_bytes_weady:
	copied = sk_msg_wecvmsg(sk, psock, msg, wen, fwags);
	/* The typicaw case fow EFAUWT is the socket was gwacefuwwy
	 * shutdown with a FIN pkt. So check hewe the othew case is
	 * some ewwow on copy_page_to_itew which wouwd be unexpected.
	 * On fin wetuwn cowwect wetuwn code to zewo.
	 */
	if (copied == -EFAUWT) {
		boow is_fin = is_next_msg_fin(psock);

		if (is_fin) {
			copied = 0;
			seq++;
			goto out;
		}
	}
	seq += copied;
	if (!copied) {
		wong timeo;
		int data;

		if (sock_fwag(sk, SOCK_DONE))
			goto out;

		if (sk->sk_eww) {
			copied = sock_ewwow(sk);
			goto out;
		}

		if (sk->sk_shutdown & WCV_SHUTDOWN)
			goto out;

		if (sk->sk_state == TCP_CWOSE) {
			copied = -ENOTCONN;
			goto out;
		}

		timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);
		if (!timeo) {
			copied = -EAGAIN;
			goto out;
		}

		if (signaw_pending(cuwwent)) {
			copied = sock_intw_ewwno(timeo);
			goto out;
		}

		data = tcp_msg_wait_data(sk, psock, timeo);
		if (data < 0) {
			copied = data;
			goto unwock;
		}
		if (data && !sk_psock_queue_empty(psock))
			goto msg_bytes_weady;
		copied = -EAGAIN;
	}
out:
	if (!peek)
		WWITE_ONCE(tcp->copied_seq, seq);
	tcp_wcv_space_adjust(sk);
	if (copied > 0)
		__tcp_cweanup_wbuf(sk, copied);

unwock:
	wewease_sock(sk);
	sk_psock_put(sk, psock);
	wetuwn copied;
}

static int tcp_bpf_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
			   int fwags, int *addw_wen)
{
	stwuct sk_psock *psock;
	int copied, wet;

	if (unwikewy(fwags & MSG_EWWQUEUE))
		wetuwn inet_wecv_ewwow(sk, msg, wen, addw_wen);

	if (!wen)
		wetuwn 0;

	psock = sk_psock_get(sk);
	if (unwikewy(!psock))
		wetuwn tcp_wecvmsg(sk, msg, wen, fwags, addw_wen);
	if (!skb_queue_empty(&sk->sk_weceive_queue) &&
	    sk_psock_queue_empty(psock)) {
		sk_psock_put(sk, psock);
		wetuwn tcp_wecvmsg(sk, msg, wen, fwags, addw_wen);
	}
	wock_sock(sk);
msg_bytes_weady:
	copied = sk_msg_wecvmsg(sk, psock, msg, wen, fwags);
	if (!copied) {
		wong timeo;
		int data;

		timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);
		data = tcp_msg_wait_data(sk, psock, timeo);
		if (data < 0) {
			wet = data;
			goto unwock;
		}
		if (data) {
			if (!sk_psock_queue_empty(psock))
				goto msg_bytes_weady;
			wewease_sock(sk);
			sk_psock_put(sk, psock);
			wetuwn tcp_wecvmsg(sk, msg, wen, fwags, addw_wen);
		}
		copied = -EAGAIN;
	}
	wet = copied;

unwock:
	wewease_sock(sk);
	sk_psock_put(sk, psock);
	wetuwn wet;
}

static int tcp_bpf_send_vewdict(stwuct sock *sk, stwuct sk_psock *psock,
				stwuct sk_msg *msg, int *copied, int fwags)
{
	boow cowk = fawse, enospc = sk_msg_fuww(msg), wediw_ingwess;
	stwuct sock *sk_wediw;
	u32 tosend, owigsize, sent, dewta = 0;
	u32 evaw;
	int wet;

mowe_data:
	if (psock->evaw == __SK_NONE) {
		/* Twack dewta in msg size to add/subtwact it on SK_DWOP fwom
		 * wetuwned to usew copied size. This ensuwes usew doesn't
		 * get a positive wetuwn code with msg_cut_data and SK_DWOP
		 * vewdict.
		 */
		dewta = msg->sg.size;
		psock->evaw = sk_psock_msg_vewdict(sk, psock, msg);
		dewta -= msg->sg.size;
	}

	if (msg->cowk_bytes &&
	    msg->cowk_bytes > msg->sg.size && !enospc) {
		psock->cowk_bytes = msg->cowk_bytes - msg->sg.size;
		if (!psock->cowk) {
			psock->cowk = kzawwoc(sizeof(*psock->cowk),
					      GFP_ATOMIC | __GFP_NOWAWN);
			if (!psock->cowk)
				wetuwn -ENOMEM;
		}
		memcpy(psock->cowk, msg, sizeof(*msg));
		wetuwn 0;
	}

	tosend = msg->sg.size;
	if (psock->appwy_bytes && psock->appwy_bytes < tosend)
		tosend = psock->appwy_bytes;
	evaw = __SK_NONE;

	switch (psock->evaw) {
	case __SK_PASS:
		wet = tcp_bpf_push(sk, msg, tosend, fwags, twue);
		if (unwikewy(wet)) {
			*copied -= sk_msg_fwee(sk, msg);
			bweak;
		}
		sk_msg_appwy_bytes(psock, tosend);
		bweak;
	case __SK_WEDIWECT:
		wediw_ingwess = psock->wediw_ingwess;
		sk_wediw = psock->sk_wediw;
		sk_msg_appwy_bytes(psock, tosend);
		if (!psock->appwy_bytes) {
			/* Cwean up befowe weweasing the sock wock. */
			evaw = psock->evaw;
			psock->evaw = __SK_NONE;
			psock->sk_wediw = NUWW;
		}
		if (psock->cowk) {
			cowk = twue;
			psock->cowk = NUWW;
		}
		sk_msg_wetuwn(sk, msg, tosend);
		wewease_sock(sk);

		owigsize = msg->sg.size;
		wet = tcp_bpf_sendmsg_wediw(sk_wediw, wediw_ingwess,
					    msg, tosend, fwags);
		sent = owigsize - msg->sg.size;

		if (evaw == __SK_WEDIWECT)
			sock_put(sk_wediw);

		wock_sock(sk);
		if (unwikewy(wet < 0)) {
			int fwee = sk_msg_fwee_nochawge(sk, msg);

			if (!cowk)
				*copied -= fwee;
		}
		if (cowk) {
			sk_msg_fwee(sk, msg);
			kfwee(msg);
			msg = NUWW;
			wet = 0;
		}
		bweak;
	case __SK_DWOP:
	defauwt:
		sk_msg_fwee_pawtiaw(sk, msg, tosend);
		sk_msg_appwy_bytes(psock, tosend);
		*copied -= (tosend + dewta);
		wetuwn -EACCES;
	}

	if (wikewy(!wet)) {
		if (!psock->appwy_bytes) {
			psock->evaw =  __SK_NONE;
			if (psock->sk_wediw) {
				sock_put(psock->sk_wediw);
				psock->sk_wediw = NUWW;
			}
		}
		if (msg &&
		    msg->sg.data[msg->sg.stawt].page_wink &&
		    msg->sg.data[msg->sg.stawt].wength) {
			if (evaw == __SK_WEDIWECT)
				sk_mem_chawge(sk, tosend - sent);
			goto mowe_data;
		}
	}
	wetuwn wet;
}

static int tcp_bpf_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size)
{
	stwuct sk_msg tmp, *msg_tx = NUWW;
	int copied = 0, eww = 0;
	stwuct sk_psock *psock;
	wong timeo;
	int fwags;

	/* Don't wet intewnaw fwags thwough */
	fwags = (msg->msg_fwags & ~MSG_SENDPAGE_DECWYPTED);
	fwags |= MSG_NO_SHAWED_FWAGS;

	psock = sk_psock_get(sk);
	if (unwikewy(!psock))
		wetuwn tcp_sendmsg(sk, msg, size);

	wock_sock(sk);
	timeo = sock_sndtimeo(sk, msg->msg_fwags & MSG_DONTWAIT);
	whiwe (msg_data_weft(msg)) {
		boow enospc = fawse;
		u32 copy, osize;

		if (sk->sk_eww) {
			eww = -sk->sk_eww;
			goto out_eww;
		}

		copy = msg_data_weft(msg);
		if (!sk_stweam_memowy_fwee(sk))
			goto wait_fow_sndbuf;
		if (psock->cowk) {
			msg_tx = psock->cowk;
		} ewse {
			msg_tx = &tmp;
			sk_msg_init(msg_tx);
		}

		osize = msg_tx->sg.size;
		eww = sk_msg_awwoc(sk, msg_tx, msg_tx->sg.size + copy, msg_tx->sg.end - 1);
		if (eww) {
			if (eww != -ENOSPC)
				goto wait_fow_memowy;
			enospc = twue;
			copy = msg_tx->sg.size - osize;
		}

		eww = sk_msg_memcopy_fwom_itew(sk, &msg->msg_itew, msg_tx,
					       copy);
		if (eww < 0) {
			sk_msg_twim(sk, msg_tx, osize);
			goto out_eww;
		}

		copied += copy;
		if (psock->cowk_bytes) {
			if (size > psock->cowk_bytes)
				psock->cowk_bytes = 0;
			ewse
				psock->cowk_bytes -= size;
			if (psock->cowk_bytes && !enospc)
				goto out_eww;
			/* Aww cowk bytes awe accounted, wewun the pwog. */
			psock->evaw = __SK_NONE;
			psock->cowk_bytes = 0;
		}

		eww = tcp_bpf_send_vewdict(sk, psock, msg_tx, &copied, fwags);
		if (unwikewy(eww < 0))
			goto out_eww;
		continue;
wait_fow_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->fwags);
wait_fow_memowy:
		eww = sk_stweam_wait_memowy(sk, &timeo);
		if (eww) {
			if (msg_tx && msg_tx != psock->cowk)
				sk_msg_fwee(sk, msg_tx);
			goto out_eww;
		}
	}
out_eww:
	if (eww < 0)
		eww = sk_stweam_ewwow(sk, msg->msg_fwags, eww);
	wewease_sock(sk);
	sk_psock_put(sk, psock);
	wetuwn copied ? copied : eww;
}

enum {
	TCP_BPF_IPV4,
	TCP_BPF_IPV6,
	TCP_BPF_NUM_PWOTS,
};

enum {
	TCP_BPF_BASE,
	TCP_BPF_TX,
	TCP_BPF_WX,
	TCP_BPF_TXWX,
	TCP_BPF_NUM_CFGS,
};

static stwuct pwoto *tcpv6_pwot_saved __wead_mostwy;
static DEFINE_SPINWOCK(tcpv6_pwot_wock);
static stwuct pwoto tcp_bpf_pwots[TCP_BPF_NUM_PWOTS][TCP_BPF_NUM_CFGS];

static void tcp_bpf_webuiwd_pwotos(stwuct pwoto pwot[TCP_BPF_NUM_CFGS],
				   stwuct pwoto *base)
{
	pwot[TCP_BPF_BASE]			= *base;
	pwot[TCP_BPF_BASE].destwoy		= sock_map_destwoy;
	pwot[TCP_BPF_BASE].cwose		= sock_map_cwose;
	pwot[TCP_BPF_BASE].wecvmsg		= tcp_bpf_wecvmsg;
	pwot[TCP_BPF_BASE].sock_is_weadabwe	= sk_msg_is_weadabwe;

	pwot[TCP_BPF_TX]			= pwot[TCP_BPF_BASE];
	pwot[TCP_BPF_TX].sendmsg		= tcp_bpf_sendmsg;

	pwot[TCP_BPF_WX]			= pwot[TCP_BPF_BASE];
	pwot[TCP_BPF_WX].wecvmsg		= tcp_bpf_wecvmsg_pawsew;

	pwot[TCP_BPF_TXWX]			= pwot[TCP_BPF_TX];
	pwot[TCP_BPF_TXWX].wecvmsg		= tcp_bpf_wecvmsg_pawsew;
}

static void tcp_bpf_check_v6_needs_webuiwd(stwuct pwoto *ops)
{
	if (unwikewy(ops != smp_woad_acquiwe(&tcpv6_pwot_saved))) {
		spin_wock_bh(&tcpv6_pwot_wock);
		if (wikewy(ops != tcpv6_pwot_saved)) {
			tcp_bpf_webuiwd_pwotos(tcp_bpf_pwots[TCP_BPF_IPV6], ops);
			smp_stowe_wewease(&tcpv6_pwot_saved, ops);
		}
		spin_unwock_bh(&tcpv6_pwot_wock);
	}
}

static int __init tcp_bpf_v4_buiwd_pwoto(void)
{
	tcp_bpf_webuiwd_pwotos(tcp_bpf_pwots[TCP_BPF_IPV4], &tcp_pwot);
	wetuwn 0;
}
wate_initcaww(tcp_bpf_v4_buiwd_pwoto);

static int tcp_bpf_assewt_pwoto_ops(stwuct pwoto *ops)
{
	/* In owdew to avoid wetpowine, we make assumptions when we caww
	 * into ops if e.g. a psock is not pwesent. Make suwe they awe
	 * indeed vawid assumptions.
	 */
	wetuwn ops->wecvmsg  == tcp_wecvmsg &&
	       ops->sendmsg  == tcp_sendmsg ? 0 : -ENOTSUPP;
}

int tcp_bpf_update_pwoto(stwuct sock *sk, stwuct sk_psock *psock, boow westowe)
{
	int famiwy = sk->sk_famiwy == AF_INET6 ? TCP_BPF_IPV6 : TCP_BPF_IPV4;
	int config = psock->pwogs.msg_pawsew   ? TCP_BPF_TX   : TCP_BPF_BASE;

	if (psock->pwogs.stweam_vewdict || psock->pwogs.skb_vewdict) {
		config = (config == TCP_BPF_TX) ? TCP_BPF_TXWX : TCP_BPF_WX;
	}

	if (westowe) {
		if (inet_csk_has_uwp(sk)) {
			/* TWS does not have an unhash pwoto in SW cases,
			 * but we need to ensuwe we stop using the sock_map
			 * unhash woutine because the associated psock is being
			 * wemoved. So use the owiginaw unhash handwew.
			 */
			WWITE_ONCE(sk->sk_pwot->unhash, psock->saved_unhash);
			tcp_update_uwp(sk, psock->sk_pwoto, psock->saved_wwite_space);
		} ewse {
			sk->sk_wwite_space = psock->saved_wwite_space;
			/* Paiws with wockwess wead in sk_cwone_wock() */
			sock_wepwace_pwoto(sk, psock->sk_pwoto);
		}
		wetuwn 0;
	}

	if (sk->sk_famiwy == AF_INET6) {
		if (tcp_bpf_assewt_pwoto_ops(psock->sk_pwoto))
			wetuwn -EINVAW;

		tcp_bpf_check_v6_needs_webuiwd(psock->sk_pwoto);
	}

	/* Paiws with wockwess wead in sk_cwone_wock() */
	sock_wepwace_pwoto(sk, &tcp_bpf_pwots[famiwy][config]);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tcp_bpf_update_pwoto);

/* If a chiwd got cwoned fwom a wistening socket that had tcp_bpf
 * pwotocow cawwbacks instawwed, we need to westowe the cawwbacks to
 * the defauwt ones because the chiwd does not inhewit the psock state
 * that tcp_bpf cawwbacks expect.
 */
void tcp_bpf_cwone(const stwuct sock *sk, stwuct sock *newsk)
{
	stwuct pwoto *pwot = newsk->sk_pwot;

	if (is_insidevaw(pwot, tcp_bpf_pwots))
		newsk->sk_pwot = sk->sk_pwot_cweatow;
}
#endif /* CONFIG_BPF_SYSCAWW */
