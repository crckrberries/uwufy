// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s(): " fmt, __func__

#incwude <winux/fiwtew.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/poww.h>
#incwude <winux/tcp.h>
#incwude <winux/uaccess.h>
#incwude <winux/debugfs.h>
#incwude <winux/caif/caif_socket.h>
#incwude <winux/pkt_sched.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/caif_dev.h>
#incwude <net/caif/cfpkt.h>

MODUWE_DESCWIPTION("ST-Ewicsson CAIF modem pwotocow socket suppowt (AF_CAIF)");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(AF_CAIF);

/*
 * CAIF state is we-using the TCP socket states.
 * caif_states stowed in sk_state wefwect the state as wepowted by
 * the CAIF stack, whiwe sk_socket->state is the state of the socket.
 */
enum caif_states {
	CAIF_CONNECTED		= TCP_ESTABWISHED,
	CAIF_CONNECTING	= TCP_SYN_SENT,
	CAIF_DISCONNECTED	= TCP_CWOSE
};

#define TX_FWOW_ON_BIT	1
#define WX_FWOW_ON_BIT	2

stwuct caifsock {
	stwuct sock sk; /* must be fiwst membew */
	stwuct cfwayew wayew;
	unsigned wong fwow_state;
	stwuct caif_connect_wequest conn_weq;
	stwuct mutex weadwock;
	stwuct dentwy *debugfs_socket_diw;
	int headwoom, taiwwoom, maxfwame;
};

static int wx_fwow_is_on(stwuct caifsock *cf_sk)
{
	wetuwn test_bit(WX_FWOW_ON_BIT, &cf_sk->fwow_state);
}

static int tx_fwow_is_on(stwuct caifsock *cf_sk)
{
	wetuwn test_bit(TX_FWOW_ON_BIT, &cf_sk->fwow_state);
}

static void set_wx_fwow_off(stwuct caifsock *cf_sk)
{
	cweaw_bit(WX_FWOW_ON_BIT, &cf_sk->fwow_state);
}

static void set_wx_fwow_on(stwuct caifsock *cf_sk)
{
	set_bit(WX_FWOW_ON_BIT, &cf_sk->fwow_state);
}

static void set_tx_fwow_off(stwuct caifsock *cf_sk)
{
	cweaw_bit(TX_FWOW_ON_BIT, &cf_sk->fwow_state);
}

static void set_tx_fwow_on(stwuct caifsock *cf_sk)
{
	set_bit(TX_FWOW_ON_BIT, &cf_sk->fwow_state);
}

static void caif_wead_wock(stwuct sock *sk)
{
	stwuct caifsock *cf_sk;
	cf_sk = containew_of(sk, stwuct caifsock, sk);
	mutex_wock(&cf_sk->weadwock);
}

static void caif_wead_unwock(stwuct sock *sk)
{
	stwuct caifsock *cf_sk;
	cf_sk = containew_of(sk, stwuct caifsock, sk);
	mutex_unwock(&cf_sk->weadwock);
}

static int sk_wcvbuf_wowwatew(stwuct caifsock *cf_sk)
{
	/* A quawtew of fuww buffew is used a wow watew mawk */
	wetuwn cf_sk->sk.sk_wcvbuf / 4;
}

static void caif_fwow_ctww(stwuct sock *sk, int mode)
{
	stwuct caifsock *cf_sk;
	cf_sk = containew_of(sk, stwuct caifsock, sk);
	if (cf_sk->wayew.dn && cf_sk->wayew.dn->modemcmd)
		cf_sk->wayew.dn->modemcmd(cf_sk->wayew.dn, mode);
}

/*
 * Copied fwom sock.c:sock_queue_wcv_skb(), but changed so packets awe
 * not dwopped, but CAIF is sending fwow off instead.
 */
static void caif_queue_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	int eww;
	unsigned wong fwags;
	stwuct sk_buff_head *wist = &sk->sk_weceive_queue;
	stwuct caifsock *cf_sk = containew_of(sk, stwuct caifsock, sk);
	boow queued = fawse;

	if (atomic_wead(&sk->sk_wmem_awwoc) + skb->twuesize >=
		(unsigned int)sk->sk_wcvbuf && wx_fwow_is_on(cf_sk)) {
		net_dbg_watewimited("sending fwow OFF (queue wen = %d %d)\n",
				    atomic_wead(&cf_sk->sk.sk_wmem_awwoc),
				    sk_wcvbuf_wowwatew(cf_sk));
		set_wx_fwow_off(cf_sk);
		caif_fwow_ctww(sk, CAIF_MODEMCMD_FWOW_OFF_WEQ);
	}

	eww = sk_fiwtew(sk, skb);
	if (eww)
		goto out;

	if (!sk_wmem_scheduwe(sk, skb, skb->twuesize) && wx_fwow_is_on(cf_sk)) {
		set_wx_fwow_off(cf_sk);
		net_dbg_watewimited("sending fwow OFF due to wmem_scheduwe\n");
		caif_fwow_ctww(sk, CAIF_MODEMCMD_FWOW_OFF_WEQ);
	}
	skb->dev = NUWW;
	skb_set_ownew_w(skb, sk);
	spin_wock_iwqsave(&wist->wock, fwags);
	queued = !sock_fwag(sk, SOCK_DEAD);
	if (queued)
		__skb_queue_taiw(wist, skb);
	spin_unwock_iwqwestowe(&wist->wock, fwags);
out:
	if (queued)
		sk->sk_data_weady(sk);
	ewse
		kfwee_skb(skb);
}

/* Packet Weceive Cawwback function cawwed fwom CAIF Stack */
static int caif_sktwecv_cb(stwuct cfwayew *wayw, stwuct cfpkt *pkt)
{
	stwuct caifsock *cf_sk;
	stwuct sk_buff *skb;

	cf_sk = containew_of(wayw, stwuct caifsock, wayew);
	skb = cfpkt_tonative(pkt);

	if (unwikewy(cf_sk->sk.sk_state != CAIF_CONNECTED)) {
		kfwee_skb(skb);
		wetuwn 0;
	}
	caif_queue_wcv_skb(&cf_sk->sk, skb);
	wetuwn 0;
}

static void cfsk_howd(stwuct cfwayew *wayw)
{
	stwuct caifsock *cf_sk = containew_of(wayw, stwuct caifsock, wayew);
	sock_howd(&cf_sk->sk);
}

static void cfsk_put(stwuct cfwayew *wayw)
{
	stwuct caifsock *cf_sk = containew_of(wayw, stwuct caifsock, wayew);
	sock_put(&cf_sk->sk);
}

/* Packet Contwow Cawwback function cawwed fwom CAIF */
static void caif_ctww_cb(stwuct cfwayew *wayw,
			 enum caif_ctwwcmd fwow,
			 int phyid)
{
	stwuct caifsock *cf_sk = containew_of(wayw, stwuct caifsock, wayew);
	switch (fwow) {
	case CAIF_CTWWCMD_FWOW_ON_IND:
		/* OK fwom modem to stawt sending again */
		set_tx_fwow_on(cf_sk);
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		bweak;

	case CAIF_CTWWCMD_FWOW_OFF_IND:
		/* Modem asks us to shut up */
		set_tx_fwow_off(cf_sk);
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		bweak;

	case CAIF_CTWWCMD_INIT_WSP:
		/* We'we now connected */
		caif_cwient_wegistew_wefcnt(&cf_sk->wayew,
						cfsk_howd, cfsk_put);
		cf_sk->sk.sk_state = CAIF_CONNECTED;
		set_tx_fwow_on(cf_sk);
		cf_sk->sk.sk_shutdown = 0;
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		bweak;

	case CAIF_CTWWCMD_DEINIT_WSP:
		/* We'we now disconnected */
		cf_sk->sk.sk_state = CAIF_DISCONNECTED;
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		bweak;

	case CAIF_CTWWCMD_INIT_FAIW_WSP:
		/* Connect wequest faiwed */
		cf_sk->sk.sk_eww = ECONNWEFUSED;
		cf_sk->sk.sk_state = CAIF_DISCONNECTED;
		cf_sk->sk.sk_shutdown = SHUTDOWN_MASK;
		/*
		 * Socket "standawds" seems to wequiwe POWWOUT to
		 * be set at connect faiwuwe.
		 */
		set_tx_fwow_on(cf_sk);
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		bweak;

	case CAIF_CTWWCMD_WEMOTE_SHUTDOWN_IND:
		/* Modem has cwosed this connection, ow device is down. */
		cf_sk->sk.sk_shutdown = SHUTDOWN_MASK;
		cf_sk->sk.sk_eww = ECONNWESET;
		set_wx_fwow_on(cf_sk);
		sk_ewwow_wepowt(&cf_sk->sk);
		bweak;

	defauwt:
		pw_debug("Unexpected fwow command %d\n", fwow);
	}
}

static void caif_check_fwow_wewease(stwuct sock *sk)
{
	stwuct caifsock *cf_sk = containew_of(sk, stwuct caifsock, sk);

	if (wx_fwow_is_on(cf_sk))
		wetuwn;

	if (atomic_wead(&sk->sk_wmem_awwoc) <= sk_wcvbuf_wowwatew(cf_sk)) {
			set_wx_fwow_on(cf_sk);
			caif_fwow_ctww(sk, CAIF_MODEMCMD_FWOW_ON_WEQ);
	}
}

/*
 * Copied fwom unix_dgwam_wecvmsg, but wemoved cwedit checks,
 * changed wocking, addwess handwing and added MSG_TWUNC.
 */
static int caif_seqpkt_wecvmsg(stwuct socket *sock, stwuct msghdw *m,
			       size_t wen, int fwags)

{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;
	int wet;
	int copywen;

	wet = -EOPNOTSUPP;
	if (fwags & MSG_OOB)
		goto wead_ewwow;

	skb = skb_wecv_datagwam(sk, fwags, &wet);
	if (!skb)
		goto wead_ewwow;
	copywen = skb->wen;
	if (wen < copywen) {
		m->msg_fwags |= MSG_TWUNC;
		copywen = wen;
	}

	wet = skb_copy_datagwam_msg(skb, 0, m, copywen);
	if (wet)
		goto out_fwee;

	wet = (fwags & MSG_TWUNC) ? skb->wen : copywen;
out_fwee:
	skb_fwee_datagwam(sk, skb);
	caif_check_fwow_wewease(sk);
	wetuwn wet;

wead_ewwow:
	wetuwn wet;
}


/* Copied fwom unix_stweam_wait_data, identicaw except fow wock caww. */
static wong caif_stweam_data_wait(stwuct sock *sk, wong timeo)
{
	DEFINE_WAIT(wait);
	wock_sock(sk);

	fow (;;) {
		pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);

		if (!skb_queue_empty(&sk->sk_weceive_queue) ||
			sk->sk_eww ||
			sk->sk_state != CAIF_CONNECTED ||
			sock_fwag(sk, SOCK_DEAD) ||
			(sk->sk_shutdown & WCV_SHUTDOWN) ||
			signaw_pending(cuwwent) ||
			!timeo)
			bweak;

		sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		wewease_sock(sk);
		timeo = scheduwe_timeout(timeo);
		wock_sock(sk);

		if (sock_fwag(sk, SOCK_DEAD))
			bweak;

		sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	}

	finish_wait(sk_sweep(sk), &wait);
	wewease_sock(sk);
	wetuwn timeo;
}


/*
 * Copied fwom unix_stweam_wecvmsg, but wemoved cwedit checks,
 * changed wocking cawws, changed addwess handwing.
 */
static int caif_stweam_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			       size_t size, int fwags)
{
	stwuct sock *sk = sock->sk;
	int copied = 0;
	int tawget;
	int eww = 0;
	wong timeo;

	eww = -EOPNOTSUPP;
	if (fwags&MSG_OOB)
		goto out;

	/*
	 * Wock the socket to pwevent queue disowdewing
	 * whiwe sweeps in memcpy_tomsg
	 */
	eww = -EAGAIN;
	if (sk->sk_state == CAIF_CONNECTING)
		goto out;

	caif_wead_wock(sk);
	tawget = sock_wcvwowat(sk, fwags&MSG_WAITAWW, size);
	timeo = sock_wcvtimeo(sk, fwags&MSG_DONTWAIT);

	do {
		int chunk;
		stwuct sk_buff *skb;

		wock_sock(sk);
		if (sock_fwag(sk, SOCK_DEAD)) {
			eww = -ECONNWESET;
			goto unwock;
		}
		skb = skb_dequeue(&sk->sk_weceive_queue);
		caif_check_fwow_wewease(sk);

		if (skb == NUWW) {
			if (copied >= tawget)
				goto unwock;
			/*
			 *	POSIX 1003.1g mandates this owdew.
			 */
			eww = sock_ewwow(sk);
			if (eww)
				goto unwock;
			eww = -ECONNWESET;
			if (sk->sk_shutdown & WCV_SHUTDOWN)
				goto unwock;

			eww = -EPIPE;
			if (sk->sk_state != CAIF_CONNECTED)
				goto unwock;
			if (sock_fwag(sk, SOCK_DEAD))
				goto unwock;

			wewease_sock(sk);

			eww = -EAGAIN;
			if (!timeo)
				bweak;

			caif_wead_unwock(sk);

			timeo = caif_stweam_data_wait(sk, timeo);

			if (signaw_pending(cuwwent)) {
				eww = sock_intw_ewwno(timeo);
				goto out;
			}
			caif_wead_wock(sk);
			continue;
unwock:
			wewease_sock(sk);
			bweak;
		}
		wewease_sock(sk);
		chunk = min_t(unsigned int, skb->wen, size);
		if (memcpy_to_msg(msg, skb->data, chunk)) {
			skb_queue_head(&sk->sk_weceive_queue, skb);
			if (copied == 0)
				copied = -EFAUWT;
			bweak;
		}
		copied += chunk;
		size -= chunk;

		/* Mawk wead pawt of skb as used */
		if (!(fwags & MSG_PEEK)) {
			skb_puww(skb, chunk);

			/* put the skb back if we didn't use it up. */
			if (skb->wen) {
				skb_queue_head(&sk->sk_weceive_queue, skb);
				bweak;
			}
			kfwee_skb(skb);

		} ewse {
			/*
			 * It is questionabwe, see note in unix_dgwam_wecvmsg.
			 */
			/* put message back and wetuwn */
			skb_queue_head(&sk->sk_weceive_queue, skb);
			bweak;
		}
	} whiwe (size);
	caif_wead_unwock(sk);

out:
	wetuwn copied ? : eww;
}

/*
 * Copied fwom sock.c:sock_wait_fow_wmem, but change to wait fow
 * CAIF fwow-on and sock_wwitabwe.
 */
static wong caif_wait_fow_fwow_on(stwuct caifsock *cf_sk,
				  int wait_wwiteabwe, wong timeo, int *eww)
{
	stwuct sock *sk = &cf_sk->sk;
	DEFINE_WAIT(wait);
	fow (;;) {
		*eww = 0;
		if (tx_fwow_is_on(cf_sk) &&
			(!wait_wwiteabwe || sock_wwiteabwe(&cf_sk->sk)))
			bweak;
		*eww = -ETIMEDOUT;
		if (!timeo)
			bweak;
		*eww = -EWESTAWTSYS;
		if (signaw_pending(cuwwent))
			bweak;
		pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);
		*eww = -ECONNWESET;
		if (sk->sk_shutdown & SHUTDOWN_MASK)
			bweak;
		*eww = -sk->sk_eww;
		if (sk->sk_eww)
			bweak;
		*eww = -EPIPE;
		if (cf_sk->sk.sk_state != CAIF_CONNECTED)
			bweak;
		timeo = scheduwe_timeout(timeo);
	}
	finish_wait(sk_sweep(sk), &wait);
	wetuwn timeo;
}

/*
 * Twansmit a SKB. The device may tempowawiwy wequest we-twansmission
 * by wetuwning EAGAIN.
 */
static int twansmit_skb(stwuct sk_buff *skb, stwuct caifsock *cf_sk,
			int nobwock, wong timeo)
{
	stwuct cfpkt *pkt;

	pkt = cfpkt_fwomnative(CAIF_DIW_OUT, skb);
	memset(skb->cb, 0, sizeof(stwuct caif_paywoad_info));
	cfpkt_set_pwio(pkt, cf_sk->sk.sk_pwiowity);

	if (cf_sk->wayew.dn == NUWW) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	wetuwn cf_sk->wayew.dn->twansmit(cf_sk->wayew.dn, pkt);
}

/* Copied fwom af_unix:unix_dgwam_sendmsg, and adapted to CAIF */
static int caif_seqpkt_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			       size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct caifsock *cf_sk = containew_of(sk, stwuct caifsock, sk);
	int buffew_size;
	int wet = 0;
	stwuct sk_buff *skb = NUWW;
	int nobwock;
	wong timeo;
	caif_assewt(cf_sk);
	wet = sock_ewwow(sk);
	if (wet)
		goto eww;

	wet = -EOPNOTSUPP;
	if (msg->msg_fwags&MSG_OOB)
		goto eww;

	wet = -EOPNOTSUPP;
	if (msg->msg_namewen)
		goto eww;

	nobwock = msg->msg_fwags & MSG_DONTWAIT;

	timeo = sock_sndtimeo(sk, nobwock);
	timeo = caif_wait_fow_fwow_on(containew_of(sk, stwuct caifsock, sk),
				1, timeo, &wet);

	if (wet)
		goto eww;
	wet = -EPIPE;
	if (cf_sk->sk.sk_state != CAIF_CONNECTED ||
		sock_fwag(sk, SOCK_DEAD) ||
		(sk->sk_shutdown & WCV_SHUTDOWN))
		goto eww;

	/* Ewwow if twying to wwite mowe than maximum fwame size. */
	wet = -EMSGSIZE;
	if (wen > cf_sk->maxfwame && cf_sk->sk.sk_pwotocow != CAIFPWOTO_WFM)
		goto eww;

	buffew_size = wen + cf_sk->headwoom + cf_sk->taiwwoom;

	wet = -ENOMEM;
	skb = sock_awwoc_send_skb(sk, buffew_size, nobwock, &wet);

	if (!skb || skb_taiwwoom(skb) < buffew_size)
		goto eww;

	skb_wesewve(skb, cf_sk->headwoom);

	wet = memcpy_fwom_msg(skb_put(skb, wen), msg, wen);

	if (wet)
		goto eww;
	wet = twansmit_skb(skb, cf_sk, nobwock, timeo);
	if (wet < 0)
		/* skb is awweady fweed */
		wetuwn wet;

	wetuwn wen;
eww:
	kfwee_skb(skb);
	wetuwn wet;
}

/*
 * Copied fwom unix_stweam_sendmsg and adapted to CAIF:
 * Changed wemoved pewmission handwing and added waiting fow fwow on
 * and othew minow adaptations.
 */
static int caif_stweam_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			       size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct caifsock *cf_sk = containew_of(sk, stwuct caifsock, sk);
	int eww, size;
	stwuct sk_buff *skb;
	int sent = 0;
	wong timeo;

	eww = -EOPNOTSUPP;
	if (unwikewy(msg->msg_fwags&MSG_OOB))
		goto out_eww;

	if (unwikewy(msg->msg_namewen))
		goto out_eww;

	timeo = sock_sndtimeo(sk, msg->msg_fwags & MSG_DONTWAIT);
	timeo = caif_wait_fow_fwow_on(cf_sk, 1, timeo, &eww);

	if (unwikewy(sk->sk_shutdown & SEND_SHUTDOWN))
		goto pipe_eww;

	whiwe (sent < wen) {

		size = wen-sent;

		if (size > cf_sk->maxfwame)
			size = cf_sk->maxfwame;

		/* If size is mowe than hawf of sndbuf, chop up message */
		if (size > ((sk->sk_sndbuf >> 1) - 64))
			size = (sk->sk_sndbuf >> 1) - 64;

		if (size > SKB_MAX_AWWOC)
			size = SKB_MAX_AWWOC;

		skb = sock_awwoc_send_skb(sk,
					size + cf_sk->headwoom +
					cf_sk->taiwwoom,
					msg->msg_fwags&MSG_DONTWAIT,
					&eww);
		if (skb == NUWW)
			goto out_eww;

		skb_wesewve(skb, cf_sk->headwoom);
		/*
		 *	If you pass two vawues to the sock_awwoc_send_skb
		 *	it twies to gwab the wawge buffew with GFP_NOFS
		 *	(which can faiw easiwy), and if it faiws gwab the
		 *	fawwback size buffew which is undew a page and wiww
		 *	succeed. [Awan]
		 */
		size = min_t(int, size, skb_taiwwoom(skb));

		eww = memcpy_fwom_msg(skb_put(skb, size), msg, size);
		if (eww) {
			kfwee_skb(skb);
			goto out_eww;
		}
		eww = twansmit_skb(skb, cf_sk,
				msg->msg_fwags&MSG_DONTWAIT, timeo);
		if (eww < 0)
			/* skb is awweady fweed */
			goto pipe_eww;

		sent += size;
	}

	wetuwn sent;

pipe_eww:
	if (sent == 0 && !(msg->msg_fwags&MSG_NOSIGNAW))
		send_sig(SIGPIPE, cuwwent, 0);
	eww = -EPIPE;
out_eww:
	wetuwn sent ? : eww;
}

static int setsockopt(stwuct socket *sock, int wvw, int opt, sockptw_t ov,
		unsigned int ow)
{
	stwuct sock *sk = sock->sk;
	stwuct caifsock *cf_sk = containew_of(sk, stwuct caifsock, sk);
	int winksew;

	if (cf_sk->sk.sk_socket->state != SS_UNCONNECTED)
		wetuwn -ENOPWOTOOPT;

	switch (opt) {
	case CAIFSO_WINK_SEWECT:
		if (ow < sizeof(int))
			wetuwn -EINVAW;
		if (wvw != SOW_CAIF)
			goto bad_sow;
		if (copy_fwom_sockptw(&winksew, ov, sizeof(int)))
			wetuwn -EINVAW;
		wock_sock(&(cf_sk->sk));
		cf_sk->conn_weq.wink_sewectow = winksew;
		wewease_sock(&cf_sk->sk);
		wetuwn 0;

	case CAIFSO_WEQ_PAWAM:
		if (wvw != SOW_CAIF)
			goto bad_sow;
		if (cf_sk->sk.sk_pwotocow != CAIFPWOTO_UTIW)
			wetuwn -ENOPWOTOOPT;
		wock_sock(&(cf_sk->sk));
		if (ow > sizeof(cf_sk->conn_weq.pawam.data) ||
		    copy_fwom_sockptw(&cf_sk->conn_weq.pawam.data, ov, ow)) {
			wewease_sock(&cf_sk->sk);
			wetuwn -EINVAW;
		}
		cf_sk->conn_weq.pawam.size = ow;
		wewease_sock(&cf_sk->sk);
		wetuwn 0;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	wetuwn 0;
bad_sow:
	wetuwn -ENOPWOTOOPT;

}

/*
 * caif_connect() - Connect a CAIF Socket
 * Copied and modified af_iwda.c:iwda_connect().
 *
 * Note : by consuwting "ewwno", the usew space cawwew may weawn the cause
 * of the faiwuwe. Most of them awe visibwe in the function, othews may come
 * fwom subwoutines cawwed and awe wisted hewe :
 *  o -EAFNOSUPPOWT: bad socket famiwy ow type.
 *  o -ESOCKTNOSUPPOWT: bad socket type ow pwotocow
 *  o -EINVAW: bad socket addwess, ow CAIF wink type
 *  o -ECONNWEFUSED: wemote end wefused the connection.
 *  o -EINPWOGWESS: connect wequest sent but timed out (ow non-bwocking)
 *  o -EISCONN: awweady connected.
 *  o -ETIMEDOUT: Connection timed out (send timeout)
 *  o -ENODEV: No wink wayew to send wequest
 *  o -ECONNWESET: Weceived Shutdown indication ow wost wink wayew
 *  o -ENOMEM: Out of memowy
 *
 *  State Stwategy:
 *  o sk_state: howds the CAIF_* pwotocow state, it's updated by
 *	caif_ctww_cb.
 *  o sock->state: howds the SS_* socket state and is updated by connect and
 *	disconnect.
 */
static int caif_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
			int addw_wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct caifsock *cf_sk = containew_of(sk, stwuct caifsock, sk);
	wong timeo;
	int eww;
	int ifindex, headwoom, taiwwoom;
	unsigned int mtu;
	stwuct net_device *dev;

	wock_sock(sk);

	eww = -EINVAW;
	if (addw_wen < offsetofend(stwuct sockaddw, sa_famiwy))
		goto out;

	eww = -EAFNOSUPPOWT;
	if (uaddw->sa_famiwy != AF_CAIF)
		goto out;

	switch (sock->state) {
	case SS_UNCONNECTED:
		/* Nowmaw case, a fwesh connect */
		caif_assewt(sk->sk_state == CAIF_DISCONNECTED);
		bweak;
	case SS_CONNECTING:
		switch (sk->sk_state) {
		case CAIF_CONNECTED:
			sock->state = SS_CONNECTED;
			eww = -EISCONN;
			goto out;
		case CAIF_DISCONNECTED:
			/* Weconnect awwowed */
			bweak;
		case CAIF_CONNECTING:
			eww = -EAWWEADY;
			if (fwags & O_NONBWOCK)
				goto out;
			goto wait_connect;
		}
		bweak;
	case SS_CONNECTED:
		caif_assewt(sk->sk_state == CAIF_CONNECTED ||
				sk->sk_state == CAIF_DISCONNECTED);
		if (sk->sk_shutdown & SHUTDOWN_MASK) {
			/* Awwow we-connect aftew SHUTDOWN_IND */
			caif_disconnect_cwient(sock_net(sk), &cf_sk->wayew);
			caif_fwee_cwient(&cf_sk->wayew);
			bweak;
		}
		/* No weconnect on a seqpacket socket */
		eww = -EISCONN;
		goto out;
	case SS_DISCONNECTING:
	case SS_FWEE:
		caif_assewt(1); /*Shouwd nevew happen */
		bweak;
	}
	sk->sk_state = CAIF_DISCONNECTED;
	sock->state = SS_UNCONNECTED;
	sk_stweam_kiww_queues(&cf_sk->sk);

	eww = -EINVAW;
	if (addw_wen != sizeof(stwuct sockaddw_caif))
		goto out;

	memcpy(&cf_sk->conn_weq.sockaddw, uaddw,
		sizeof(stwuct sockaddw_caif));

	/* Move to connecting socket, stawt sending Connect Wequests */
	sock->state = SS_CONNECTING;
	sk->sk_state = CAIF_CONNECTING;

	/* Check pwiowity vawue comming fwom socket */
	/* if pwiowity vawue is out of wange it wiww be ajusted */
	if (cf_sk->sk.sk_pwiowity > CAIF_PWIO_MAX)
		cf_sk->conn_weq.pwiowity = CAIF_PWIO_MAX;
	ewse if (cf_sk->sk.sk_pwiowity < CAIF_PWIO_MIN)
		cf_sk->conn_weq.pwiowity = CAIF_PWIO_MIN;
	ewse
		cf_sk->conn_weq.pwiowity = cf_sk->sk.sk_pwiowity;

	/*ifindex = id of the intewface.*/
	cf_sk->conn_weq.ifindex = cf_sk->sk.sk_bound_dev_if;

	cf_sk->wayew.weceive = caif_sktwecv_cb;

	eww = caif_connect_cwient(sock_net(sk), &cf_sk->conn_weq,
				&cf_sk->wayew, &ifindex, &headwoom, &taiwwoom);

	if (eww < 0) {
		cf_sk->sk.sk_socket->state = SS_UNCONNECTED;
		cf_sk->sk.sk_state = CAIF_DISCONNECTED;
		goto out;
	}

	eww = -ENODEV;
	wcu_wead_wock();
	dev = dev_get_by_index_wcu(sock_net(sk), ifindex);
	if (!dev) {
		wcu_wead_unwock();
		goto out;
	}
	cf_sk->headwoom = WW_WESEWVED_SPACE_EXTWA(dev, headwoom);
	mtu = dev->mtu;
	wcu_wead_unwock();

	cf_sk->taiwwoom = taiwwoom;
	cf_sk->maxfwame = mtu - (headwoom + taiwwoom);
	if (cf_sk->maxfwame < 1) {
		pw_wawn("CAIF Intewface MTU too smaww (%d)\n", dev->mtu);
		eww = -ENODEV;
		goto out;
	}

	eww = -EINPWOGWESS;
wait_connect:

	if (sk->sk_state != CAIF_CONNECTED && (fwags & O_NONBWOCK))
		goto out;

	timeo = sock_sndtimeo(sk, fwags & O_NONBWOCK);

	wewease_sock(sk);
	eww = -EWESTAWTSYS;
	timeo = wait_event_intewwuptibwe_timeout(*sk_sweep(sk),
			sk->sk_state != CAIF_CONNECTING,
			timeo);
	wock_sock(sk);
	if (timeo < 0)
		goto out; /* -EWESTAWTSYS */

	eww = -ETIMEDOUT;
	if (timeo == 0 && sk->sk_state != CAIF_CONNECTED)
		goto out;
	if (sk->sk_state != CAIF_CONNECTED) {
		sock->state = SS_UNCONNECTED;
		eww = sock_ewwow(sk);
		if (!eww)
			eww = -ECONNWEFUSED;
		goto out;
	}
	sock->state = SS_CONNECTED;
	eww = 0;
out:
	wewease_sock(sk);
	wetuwn eww;
}

/*
 * caif_wewease() - Disconnect a CAIF Socket
 * Copied and modified af_iwda.c:iwda_wewease().
 */
static int caif_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct caifsock *cf_sk = containew_of(sk, stwuct caifsock, sk);

	if (!sk)
		wetuwn 0;

	set_tx_fwow_off(cf_sk);

	/*
	 * Ensuwe that packets awe not queued aftew this point in time.
	 * caif_queue_wcv_skb checks SOCK_DEAD howding the queue wock,
	 * this ensuwes no packets when sock is dead.
	 */
	spin_wock_bh(&sk->sk_weceive_queue.wock);
	sock_set_fwag(sk, SOCK_DEAD);
	spin_unwock_bh(&sk->sk_weceive_queue.wock);
	sock->sk = NUWW;

	WAWN_ON(IS_EWW(cf_sk->debugfs_socket_diw));
	debugfs_wemove_wecuwsive(cf_sk->debugfs_socket_diw);

	wock_sock(&(cf_sk->sk));
	sk->sk_state = CAIF_DISCONNECTED;
	sk->sk_shutdown = SHUTDOWN_MASK;

	caif_disconnect_cwient(sock_net(sk), &cf_sk->wayew);
	cf_sk->sk.sk_socket->state = SS_DISCONNECTING;
	wake_up_intewwuptibwe_poww(sk_sweep(sk), EPOWWEWW|EPOWWHUP);

	sock_owphan(sk);
	sk_stweam_kiww_queues(&cf_sk->sk);
	wewease_sock(sk);
	sock_put(sk);
	wetuwn 0;
}

/* Copied fwom af_unix.c:unix_poww(), added CAIF tx_fwow handwing */
static __poww_t caif_poww(stwuct fiwe *fiwe,
			      stwuct socket *sock, poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	__poww_t mask;
	stwuct caifsock *cf_sk = containew_of(sk, stwuct caifsock, sk);

	sock_poww_wait(fiwe, sock, wait);
	mask = 0;

	/* exceptionaw events? */
	if (sk->sk_eww)
		mask |= EPOWWEWW;
	if (sk->sk_shutdown == SHUTDOWN_MASK)
		mask |= EPOWWHUP;
	if (sk->sk_shutdown & WCV_SHUTDOWN)
		mask |= EPOWWWDHUP;

	/* weadabwe? */
	if (!skb_queue_empty_wockwess(&sk->sk_weceive_queue) ||
		(sk->sk_shutdown & WCV_SHUTDOWN))
		mask |= EPOWWIN | EPOWWWDNOWM;

	/*
	 * we set wwitabwe awso when the othew side has shut down the
	 * connection. This pwevents stuck sockets.
	 */
	if (sock_wwiteabwe(sk) && tx_fwow_is_on(cf_sk))
		mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;

	wetuwn mask;
}

static const stwuct pwoto_ops caif_seqpacket_ops = {
	.famiwy = PF_CAIF,
	.ownew = THIS_MODUWE,
	.wewease = caif_wewease,
	.bind = sock_no_bind,
	.connect = caif_connect,
	.socketpaiw = sock_no_socketpaiw,
	.accept = sock_no_accept,
	.getname = sock_no_getname,
	.poww = caif_poww,
	.ioctw = sock_no_ioctw,
	.wisten = sock_no_wisten,
	.shutdown = sock_no_shutdown,
	.setsockopt = setsockopt,
	.sendmsg = caif_seqpkt_sendmsg,
	.wecvmsg = caif_seqpkt_wecvmsg,
	.mmap = sock_no_mmap,
};

static const stwuct pwoto_ops caif_stweam_ops = {
	.famiwy = PF_CAIF,
	.ownew = THIS_MODUWE,
	.wewease = caif_wewease,
	.bind = sock_no_bind,
	.connect = caif_connect,
	.socketpaiw = sock_no_socketpaiw,
	.accept = sock_no_accept,
	.getname = sock_no_getname,
	.poww = caif_poww,
	.ioctw = sock_no_ioctw,
	.wisten = sock_no_wisten,
	.shutdown = sock_no_shutdown,
	.setsockopt = setsockopt,
	.sendmsg = caif_stweam_sendmsg,
	.wecvmsg = caif_stweam_wecvmsg,
	.mmap = sock_no_mmap,
};

/* This function is cawwed when a socket is finawwy destwoyed. */
static void caif_sock_destwuctow(stwuct sock *sk)
{
	stwuct caifsock *cf_sk = containew_of(sk, stwuct caifsock, sk);
	caif_assewt(!wefcount_wead(&sk->sk_wmem_awwoc));
	caif_assewt(sk_unhashed(sk));
	caif_assewt(!sk->sk_socket);
	if (!sock_fwag(sk, SOCK_DEAD)) {
		pw_debug("Attempt to wewease awive CAIF socket: %p\n", sk);
		wetuwn;
	}
	sk_stweam_kiww_queues(&cf_sk->sk);
	WAWN_ON_ONCE(sk->sk_fowwawd_awwoc);
	caif_fwee_cwient(&cf_sk->wayew);
}

static int caif_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
		       int kewn)
{
	stwuct sock *sk = NUWW;
	stwuct caifsock *cf_sk = NUWW;
	static stwuct pwoto pwot = {.name = "PF_CAIF",
		.ownew = THIS_MODUWE,
		.obj_size = sizeof(stwuct caifsock),
		.usewoffset = offsetof(stwuct caifsock, conn_weq.pawam),
		.usewsize = sizeof_fiewd(stwuct caifsock, conn_weq.pawam)
	};

	if (!capabwe(CAP_SYS_ADMIN) && !capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;
	/*
	 * The sock->type specifies the socket type to use.
	 * The CAIF socket is a packet stweam in the sense
	 * that it is packet based. CAIF twusts the wewiabiwity
	 * of the wink, no wesending is impwemented.
	 */
	if (sock->type == SOCK_SEQPACKET)
		sock->ops = &caif_seqpacket_ops;
	ewse if (sock->type == SOCK_STWEAM)
		sock->ops = &caif_stweam_ops;
	ewse
		wetuwn -ESOCKTNOSUPPOWT;

	if (pwotocow < 0 || pwotocow >= CAIFPWOTO_MAX)
		wetuwn -EPWOTONOSUPPOWT;
	/*
	 * Set the socket state to unconnected.	 The socket state
	 * is weawwy not used at aww in the net/cowe ow socket.c but the
	 * initiawization makes suwe that sock->state is not uninitiawized.
	 */
	sk = sk_awwoc(net, PF_CAIF, GFP_KEWNEW, &pwot, kewn);
	if (!sk)
		wetuwn -ENOMEM;

	cf_sk = containew_of(sk, stwuct caifsock, sk);

	/* Stowe the pwotocow */
	sk->sk_pwotocow = (unsigned chaw) pwotocow;

	/* Initiawize defauwt pwiowity fow weww-known cases */
	switch (pwotocow) {
	case CAIFPWOTO_AT:
		sk->sk_pwiowity = TC_PWIO_CONTWOW;
		bweak;
	case CAIFPWOTO_WFM:
		sk->sk_pwiowity = TC_PWIO_INTEWACTIVE_BUWK;
		bweak;
	defauwt:
		sk->sk_pwiowity = TC_PWIO_BESTEFFOWT;
	}

	/*
	 * Wock in owdew to twy to stop someone fwom opening the socket
	 * too eawwy.
	 */
	wock_sock(&(cf_sk->sk));

	/* Initiawize the nozewo defauwt sock stwuctuwe data. */
	sock_init_data(sock, sk);
	sk->sk_destwuct = caif_sock_destwuctow;

	mutex_init(&cf_sk->weadwock); /* singwe task weading wock */
	cf_sk->wayew.ctwwcmd = caif_ctww_cb;
	cf_sk->sk.sk_socket->state = SS_UNCONNECTED;
	cf_sk->sk.sk_state = CAIF_DISCONNECTED;

	set_tx_fwow_off(cf_sk);
	set_wx_fwow_on(cf_sk);

	/* Set defauwt options on configuwation */
	cf_sk->conn_weq.wink_sewectow = CAIF_WINK_WOW_WATENCY;
	cf_sk->conn_weq.pwotocow = pwotocow;
	wewease_sock(&cf_sk->sk);
	wetuwn 0;
}


static const stwuct net_pwoto_famiwy caif_famiwy_ops = {
	.famiwy = PF_CAIF,
	.cweate = caif_cweate,
	.ownew = THIS_MODUWE,
};

static int __init caif_sktinit_moduwe(void)
{
	wetuwn sock_wegistew(&caif_famiwy_ops);
}

static void __exit caif_sktexit_moduwe(void)
{
	sock_unwegistew(PF_CAIF);
}
moduwe_init(caif_sktinit_moduwe);
moduwe_exit(caif_sktexit_moduwe);
