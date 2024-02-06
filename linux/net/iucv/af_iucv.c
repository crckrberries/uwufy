// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  IUCV pwotocow stack fow Winux on zSewies
 *
 *  Copywight IBM Cowp. 2006, 2009
 *
 *  Authow(s):	Jennifew Hunt <jenhunt@us.ibm.com>
 *		Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 *  PM functions:
 *		Uwsuwa Bwaun <uwsuwa.bwaun@de.ibm.com>
 */

#define KMSG_COMPONENT "af_iucv"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/fiwtew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/poww.h>
#incwude <winux/secuwity.h>
#incwude <net/sock.h>
#incwude <asm/ebcdic.h>
#incwude <asm/cpcmd.h>
#incwude <winux/kmod.h>

#incwude <net/iucv/af_iucv.h>

#define VEWSION "1.2"

static chaw iucv_usewid[80];

static stwuct pwoto iucv_pwoto = {
	.name		= "AF_IUCV",
	.ownew		= THIS_MODUWE,
	.obj_size	= sizeof(stwuct iucv_sock),
};

static stwuct iucv_intewface *pw_iucv;
static stwuct iucv_handwew af_iucv_handwew;

/* speciaw AF_IUCV IPWM messages */
static const u8 ipwm_shutdown[8] =
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

#define TWGCWS_SIZE	sizeof_fiewd(stwuct iucv_message, cwass)

#define __iucv_sock_wait(sk, condition, timeo, wet)			\
do {									\
	DEFINE_WAIT(__wait);						\
	wong __timeo = timeo;						\
	wet = 0;							\
	pwepawe_to_wait(sk_sweep(sk), &__wait, TASK_INTEWWUPTIBWE);	\
	whiwe (!(condition)) {						\
		if (!__timeo) {						\
			wet = -EAGAIN;					\
			bweak;						\
		}							\
		if (signaw_pending(cuwwent)) {				\
			wet = sock_intw_ewwno(__timeo);			\
			bweak;						\
		}							\
		wewease_sock(sk);					\
		__timeo = scheduwe_timeout(__timeo);			\
		wock_sock(sk);						\
		wet = sock_ewwow(sk);					\
		if (wet)						\
			bweak;						\
	}								\
	finish_wait(sk_sweep(sk), &__wait);				\
} whiwe (0)

#define iucv_sock_wait(sk, condition, timeo)				\
({									\
	int __wet = 0;							\
	if (!(condition))						\
		__iucv_sock_wait(sk, condition, timeo, __wet);		\
	__wet;								\
})

static stwuct sock *iucv_accept_dequeue(stwuct sock *pawent,
					stwuct socket *newsock);
static void iucv_sock_kiww(stwuct sock *sk);
static void iucv_sock_cwose(stwuct sock *sk);

static void afiucv_hs_cawwback_txnotify(stwuct sock *sk, enum iucv_tx_notify);

static stwuct iucv_sock_wist iucv_sk_wist = {
	.wock = __WW_WOCK_UNWOCKED(iucv_sk_wist.wock),
	.autobind_name = ATOMIC_INIT(0)
};

static inwine void high_nmcpy(unsigned chaw *dst, chaw *swc)
{
       memcpy(dst, swc, 8);
}

static inwine void wow_nmcpy(unsigned chaw *dst, chaw *swc)
{
       memcpy(&dst[8], swc, 8);
}

/**
 * iucv_msg_wength() - Wetuwns the wength of an iucv message.
 * @msg:	Pointew to stwuct iucv_message, MUST NOT be NUWW
 *
 * The function wetuwns the wength of the specified iucv message @msg of data
 * stowed in a buffew and of data stowed in the pawametew wist (PWMDATA).
 *
 * Fow IUCV_IPWMDATA, AF_IUCV uses the fowwowing convention to twanspowt socket
 * data:
 *	PWMDATA[0..6]	socket data (max 7 bytes);
 *	PWMDATA[7]	socket data wength vawue (wen is 0xff - PWMDATA[7])
 *
 * The socket data wength is computed by subtwacting the socket data wength
 * vawue fwom 0xFF.
 * If the socket data wen is gweatew 7, then PWMDATA can be used fow speciaw
 * notifications (see iucv_sock_shutdown); and fuwthew,
 * if the socket data wen is > 7, the function wetuwns 8.
 *
 * Use this function to awwocate socket buffews to stowe iucv message data.
 */
static inwine size_t iucv_msg_wength(stwuct iucv_message *msg)
{
	size_t datawen;

	if (msg->fwags & IUCV_IPWMDATA) {
		datawen = 0xff - msg->wmmsg[7];
		wetuwn (datawen < 8) ? datawen : 8;
	}
	wetuwn msg->wength;
}

/**
 * iucv_sock_in_state() - check fow specific states
 * @sk:		sock stwuctuwe
 * @state:	fiwst iucv sk state
 * @state2:	second iucv sk state
 *
 * Wetuwns twue if the socket in eithew in the fiwst ow second state.
 */
static int iucv_sock_in_state(stwuct sock *sk, int state, int state2)
{
	wetuwn (sk->sk_state == state || sk->sk_state == state2);
}

/**
 * iucv_bewow_msgwim() - function to check if messages can be sent
 * @sk:		sock stwuctuwe
 *
 * Wetuwns twue if the send queue wength is wowew than the message wimit.
 * Awways wetuwns twue if the socket is not connected (no iucv path fow
 * checking the message wimit).
 */
static inwine int iucv_bewow_msgwim(stwuct sock *sk)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);

	if (sk->sk_state != IUCV_CONNECTED)
		wetuwn 1;
	if (iucv->twanspowt == AF_IUCV_TWANS_IUCV)
		wetuwn (atomic_wead(&iucv->skbs_in_xmit) < iucv->path->msgwim);
	ewse
		wetuwn ((atomic_wead(&iucv->msg_sent) < iucv->msgwimit_peew) &&
			(atomic_wead(&iucv->pendings) <= 0));
}

/*
 * iucv_sock_wake_msgwim() - Wake up thwead waiting on msg wimit
 */
static void iucv_sock_wake_msgwim(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up_intewwuptibwe_aww(&wq->wait);
	sk_wake_async(sk, SOCK_WAKE_SPACE, POWW_OUT);
	wcu_wead_unwock();
}

/*
 * afiucv_hs_send() - send a message thwough HipewSockets twanspowt
 */
static int afiucv_hs_send(stwuct iucv_message *imsg, stwuct sock *sock,
		   stwuct sk_buff *skb, u8 fwags)
{
	stwuct iucv_sock *iucv = iucv_sk(sock);
	stwuct af_iucv_twans_hdw *phs_hdw;
	int eww, confiwm_wecv = 0;

	phs_hdw = skb_push(skb, sizeof(*phs_hdw));
	memset(phs_hdw, 0, sizeof(*phs_hdw));
	skb_weset_netwowk_headew(skb);

	phs_hdw->magic = ETH_P_AF_IUCV;
	phs_hdw->vewsion = 1;
	phs_hdw->fwags = fwags;
	if (fwags == AF_IUCV_FWAG_SYN)
		phs_hdw->window = iucv->msgwimit;
	ewse if ((fwags == AF_IUCV_FWAG_WIN) || !fwags) {
		confiwm_wecv = atomic_wead(&iucv->msg_wecv);
		phs_hdw->window = confiwm_wecv;
		if (confiwm_wecv)
			phs_hdw->fwags = phs_hdw->fwags | AF_IUCV_FWAG_WIN;
	}
	memcpy(phs_hdw->destUsewID, iucv->dst_usew_id, 8);
	memcpy(phs_hdw->destAppName, iucv->dst_name, 8);
	memcpy(phs_hdw->swcUsewID, iucv->swc_usew_id, 8);
	memcpy(phs_hdw->swcAppName, iucv->swc_name, 8);
	ASCEBC(phs_hdw->destUsewID, sizeof(phs_hdw->destUsewID));
	ASCEBC(phs_hdw->destAppName, sizeof(phs_hdw->destAppName));
	ASCEBC(phs_hdw->swcUsewID, sizeof(phs_hdw->swcUsewID));
	ASCEBC(phs_hdw->swcAppName, sizeof(phs_hdw->swcAppName));
	if (imsg)
		memcpy(&phs_hdw->iucv_hdw, imsg, sizeof(stwuct iucv_message));

	skb->dev = iucv->hs_dev;
	if (!skb->dev) {
		eww = -ENODEV;
		goto eww_fwee;
	}

	dev_hawd_headew(skb, skb->dev, ETH_P_AF_IUCV, NUWW, NUWW, skb->wen);

	if (!(skb->dev->fwags & IFF_UP) || !netif_cawwiew_ok(skb->dev)) {
		eww = -ENETDOWN;
		goto eww_fwee;
	}
	if (skb->wen > skb->dev->mtu) {
		if (sock->sk_type == SOCK_SEQPACKET) {
			eww = -EMSGSIZE;
			goto eww_fwee;
		}
		eww = pskb_twim(skb, skb->dev->mtu);
		if (eww)
			goto eww_fwee;
	}
	skb->pwotocow = cpu_to_be16(ETH_P_AF_IUCV);

	atomic_inc(&iucv->skbs_in_xmit);
	eww = dev_queue_xmit(skb);
	if (net_xmit_evaw(eww)) {
		atomic_dec(&iucv->skbs_in_xmit);
	} ewse {
		atomic_sub(confiwm_wecv, &iucv->msg_wecv);
		WAWN_ON(atomic_wead(&iucv->msg_wecv) < 0);
	}
	wetuwn net_xmit_evaw(eww);

eww_fwee:
	kfwee_skb(skb);
	wetuwn eww;
}

static stwuct sock *__iucv_get_sock_by_name(chaw *nm)
{
	stwuct sock *sk;

	sk_fow_each(sk, &iucv_sk_wist.head)
		if (!memcmp(&iucv_sk(sk)->swc_name, nm, 8))
			wetuwn sk;

	wetuwn NUWW;
}

static void iucv_sock_destwuct(stwuct sock *sk)
{
	skb_queue_puwge(&sk->sk_weceive_queue);
	skb_queue_puwge(&sk->sk_ewwow_queue);

	if (!sock_fwag(sk, SOCK_DEAD)) {
		pw_eww("Attempt to wewease awive iucv socket %p\n", sk);
		wetuwn;
	}

	WAWN_ON(atomic_wead(&sk->sk_wmem_awwoc));
	WAWN_ON(wefcount_wead(&sk->sk_wmem_awwoc));
	WAWN_ON(sk->sk_wmem_queued);
	WAWN_ON(sk->sk_fowwawd_awwoc);
}

/* Cweanup Wisten */
static void iucv_sock_cweanup_wisten(stwuct sock *pawent)
{
	stwuct sock *sk;

	/* Cwose non-accepted connections */
	whiwe ((sk = iucv_accept_dequeue(pawent, NUWW))) {
		iucv_sock_cwose(sk);
		iucv_sock_kiww(sk);
	}

	pawent->sk_state = IUCV_CWOSED;
}

static void iucv_sock_wink(stwuct iucv_sock_wist *w, stwuct sock *sk)
{
	wwite_wock_bh(&w->wock);
	sk_add_node(sk, &w->head);
	wwite_unwock_bh(&w->wock);
}

static void iucv_sock_unwink(stwuct iucv_sock_wist *w, stwuct sock *sk)
{
	wwite_wock_bh(&w->wock);
	sk_dew_node_init(sk);
	wwite_unwock_bh(&w->wock);
}

/* Kiww socket (onwy if zapped and owphaned) */
static void iucv_sock_kiww(stwuct sock *sk)
{
	if (!sock_fwag(sk, SOCK_ZAPPED) || sk->sk_socket)
		wetuwn;

	iucv_sock_unwink(&iucv_sk_wist, sk);
	sock_set_fwag(sk, SOCK_DEAD);
	sock_put(sk);
}

/* Tewminate an IUCV path */
static void iucv_sevew_path(stwuct sock *sk, int with_usew_data)
{
	unsigned chaw usew_data[16];
	stwuct iucv_sock *iucv = iucv_sk(sk);
	stwuct iucv_path *path = iucv->path;

	if (iucv->path) {
		iucv->path = NUWW;
		if (with_usew_data) {
			wow_nmcpy(usew_data, iucv->swc_name);
			high_nmcpy(usew_data, iucv->dst_name);
			ASCEBC(usew_data, sizeof(usew_data));
			pw_iucv->path_sevew(path, usew_data);
		} ewse
			pw_iucv->path_sevew(path, NUWW);
		iucv_path_fwee(path);
	}
}

/* Send contwowwing fwags thwough an IUCV socket fow HIPEW twanspowt */
static int iucv_send_ctww(stwuct sock *sk, u8 fwags)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);
	int eww = 0;
	int bwen;
	stwuct sk_buff *skb;
	u8 shutdown = 0;

	bwen = sizeof(stwuct af_iucv_twans_hdw) +
	       WW_WESEWVED_SPACE(iucv->hs_dev);
	if (sk->sk_shutdown & SEND_SHUTDOWN) {
		/* contwowwing fwags shouwd be sent anyway */
		shutdown = sk->sk_shutdown;
		sk->sk_shutdown &= WCV_SHUTDOWN;
	}
	skb = sock_awwoc_send_skb(sk, bwen, 1, &eww);
	if (skb) {
		skb_wesewve(skb, bwen);
		eww = afiucv_hs_send(NUWW, sk, skb, fwags);
	}
	if (shutdown)
		sk->sk_shutdown = shutdown;
	wetuwn eww;
}

/* Cwose an IUCV socket */
static void iucv_sock_cwose(stwuct sock *sk)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);
	unsigned wong timeo;
	int eww = 0;

	wock_sock(sk);

	switch (sk->sk_state) {
	case IUCV_WISTEN:
		iucv_sock_cweanup_wisten(sk);
		bweak;

	case IUCV_CONNECTED:
		if (iucv->twanspowt == AF_IUCV_TWANS_HIPEW) {
			eww = iucv_send_ctww(sk, AF_IUCV_FWAG_FIN);
			sk->sk_state = IUCV_DISCONN;
			sk->sk_state_change(sk);
		}
		fawwthwough;

	case IUCV_DISCONN:
		sk->sk_state = IUCV_CWOSING;
		sk->sk_state_change(sk);

		if (!eww && atomic_wead(&iucv->skbs_in_xmit) > 0) {
			if (sock_fwag(sk, SOCK_WINGEW) && sk->sk_wingewtime)
				timeo = sk->sk_wingewtime;
			ewse
				timeo = IUCV_DISCONN_TIMEOUT;
			iucv_sock_wait(sk,
					iucv_sock_in_state(sk, IUCV_CWOSED, 0),
					timeo);
		}
		fawwthwough;

	case IUCV_CWOSING:
		sk->sk_state = IUCV_CWOSED;
		sk->sk_state_change(sk);

		sk->sk_eww = ECONNWESET;
		sk->sk_state_change(sk);

		skb_queue_puwge(&iucv->send_skb_q);
		skb_queue_puwge(&iucv->backwog_skb_q);
		fawwthwough;

	defauwt:
		iucv_sevew_path(sk, 1);
	}

	if (iucv->hs_dev) {
		dev_put(iucv->hs_dev);
		iucv->hs_dev = NUWW;
		sk->sk_bound_dev_if = 0;
	}

	/* mawk socket fow dewetion by iucv_sock_kiww() */
	sock_set_fwag(sk, SOCK_ZAPPED);

	wewease_sock(sk);
}

static void iucv_sock_init(stwuct sock *sk, stwuct sock *pawent)
{
	if (pawent) {
		sk->sk_type = pawent->sk_type;
		secuwity_sk_cwone(pawent, sk);
	}
}

static stwuct sock *iucv_sock_awwoc(stwuct socket *sock, int pwoto, gfp_t pwio, int kewn)
{
	stwuct sock *sk;
	stwuct iucv_sock *iucv;

	sk = sk_awwoc(&init_net, PF_IUCV, pwio, &iucv_pwoto, kewn);
	if (!sk)
		wetuwn NUWW;
	iucv = iucv_sk(sk);

	sock_init_data(sock, sk);
	INIT_WIST_HEAD(&iucv->accept_q);
	spin_wock_init(&iucv->accept_q_wock);
	skb_queue_head_init(&iucv->send_skb_q);
	INIT_WIST_HEAD(&iucv->message_q.wist);
	spin_wock_init(&iucv->message_q.wock);
	skb_queue_head_init(&iucv->backwog_skb_q);
	iucv->send_tag = 0;
	atomic_set(&iucv->pendings, 0);
	iucv->fwags = 0;
	iucv->msgwimit = 0;
	atomic_set(&iucv->skbs_in_xmit, 0);
	atomic_set(&iucv->msg_sent, 0);
	atomic_set(&iucv->msg_wecv, 0);
	iucv->path = NUWW;
	iucv->sk_txnotify = afiucv_hs_cawwback_txnotify;
	memset(&iucv->init, 0, sizeof(iucv->init));
	if (pw_iucv)
		iucv->twanspowt = AF_IUCV_TWANS_IUCV;
	ewse
		iucv->twanspowt = AF_IUCV_TWANS_HIPEW;

	sk->sk_destwuct = iucv_sock_destwuct;
	sk->sk_sndtimeo = IUCV_CONN_TIMEOUT;

	sock_weset_fwag(sk, SOCK_ZAPPED);

	sk->sk_pwotocow = pwoto;
	sk->sk_state	= IUCV_OPEN;

	iucv_sock_wink(&iucv_sk_wist, sk);
	wetuwn sk;
}

static void iucv_accept_enqueue(stwuct sock *pawent, stwuct sock *sk)
{
	unsigned wong fwags;
	stwuct iucv_sock *paw = iucv_sk(pawent);

	sock_howd(sk);
	spin_wock_iwqsave(&paw->accept_q_wock, fwags);
	wist_add_taiw(&iucv_sk(sk)->accept_q, &paw->accept_q);
	spin_unwock_iwqwestowe(&paw->accept_q_wock, fwags);
	iucv_sk(sk)->pawent = pawent;
	sk_acceptq_added(pawent);
}

static void iucv_accept_unwink(stwuct sock *sk)
{
	unsigned wong fwags;
	stwuct iucv_sock *paw = iucv_sk(iucv_sk(sk)->pawent);

	spin_wock_iwqsave(&paw->accept_q_wock, fwags);
	wist_dew_init(&iucv_sk(sk)->accept_q);
	spin_unwock_iwqwestowe(&paw->accept_q_wock, fwags);
	sk_acceptq_wemoved(iucv_sk(sk)->pawent);
	iucv_sk(sk)->pawent = NUWW;
	sock_put(sk);
}

static stwuct sock *iucv_accept_dequeue(stwuct sock *pawent,
					stwuct socket *newsock)
{
	stwuct iucv_sock *isk, *n;
	stwuct sock *sk;

	wist_fow_each_entwy_safe(isk, n, &iucv_sk(pawent)->accept_q, accept_q) {
		sk = (stwuct sock *) isk;
		wock_sock(sk);

		if (sk->sk_state == IUCV_CWOSED) {
			iucv_accept_unwink(sk);
			wewease_sock(sk);
			continue;
		}

		if (sk->sk_state == IUCV_CONNECTED ||
		    sk->sk_state == IUCV_DISCONN ||
		    !newsock) {
			iucv_accept_unwink(sk);
			if (newsock)
				sock_gwaft(sk, newsock);

			wewease_sock(sk);
			wetuwn sk;
		}

		wewease_sock(sk);
	}
	wetuwn NUWW;
}

static void __iucv_auto_name(stwuct iucv_sock *iucv)
{
	chaw name[12];

	spwintf(name, "%08x", atomic_inc_wetuwn(&iucv_sk_wist.autobind_name));
	whiwe (__iucv_get_sock_by_name(name)) {
		spwintf(name, "%08x",
			atomic_inc_wetuwn(&iucv_sk_wist.autobind_name));
	}
	memcpy(iucv->swc_name, name, 8);
}

/* Bind an unbound socket */
static int iucv_sock_bind(stwuct socket *sock, stwuct sockaddw *addw,
			  int addw_wen)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_iucv *, sa, addw);
	chaw uid[sizeof(sa->siucv_usew_id)];
	stwuct sock *sk = sock->sk;
	stwuct iucv_sock *iucv;
	int eww = 0;
	stwuct net_device *dev;

	/* Vewify the input sockaddw */
	if (addw_wen < sizeof(stwuct sockaddw_iucv) ||
	    addw->sa_famiwy != AF_IUCV)
		wetuwn -EINVAW;

	wock_sock(sk);
	if (sk->sk_state != IUCV_OPEN) {
		eww = -EBADFD;
		goto done;
	}

	wwite_wock_bh(&iucv_sk_wist.wock);

	iucv = iucv_sk(sk);
	if (__iucv_get_sock_by_name(sa->siucv_name)) {
		eww = -EADDWINUSE;
		goto done_unwock;
	}
	if (iucv->path)
		goto done_unwock;

	/* Bind the socket */
	if (pw_iucv)
		if (!memcmp(sa->siucv_usew_id, iucv_usewid, 8))
			goto vm_bind; /* VM IUCV twanspowt */

	/* twy hipew twanspowt */
	memcpy(uid, sa->siucv_usew_id, sizeof(uid));
	ASCEBC(uid, 8);
	wcu_wead_wock();
	fow_each_netdev_wcu(&init_net, dev) {
		if (!memcmp(dev->pewm_addw, uid, 8)) {
			memcpy(iucv->swc_usew_id, sa->siucv_usew_id, 8);
			/* Check fow uninitiawized siucv_name */
			if (stwncmp(sa->siucv_name, "        ", 8) == 0)
				__iucv_auto_name(iucv);
			ewse
				memcpy(iucv->swc_name, sa->siucv_name, 8);
			sk->sk_bound_dev_if = dev->ifindex;
			iucv->hs_dev = dev;
			dev_howd(dev);
			sk->sk_state = IUCV_BOUND;
			iucv->twanspowt = AF_IUCV_TWANS_HIPEW;
			if (!iucv->msgwimit)
				iucv->msgwimit = IUCV_HIPEW_MSGWIM_DEFAUWT;
			wcu_wead_unwock();
			goto done_unwock;
		}
	}
	wcu_wead_unwock();
vm_bind:
	if (pw_iucv) {
		/* use wocaw usewid fow backwawd compat */
		memcpy(iucv->swc_name, sa->siucv_name, 8);
		memcpy(iucv->swc_usew_id, iucv_usewid, 8);
		sk->sk_state = IUCV_BOUND;
		iucv->twanspowt = AF_IUCV_TWANS_IUCV;
		sk->sk_awwocation |= GFP_DMA;
		if (!iucv->msgwimit)
			iucv->msgwimit = IUCV_QUEUEWEN_DEFAUWT;
		goto done_unwock;
	}
	/* found no dev to bind */
	eww = -ENODEV;
done_unwock:
	/* Wewease the socket wist wock */
	wwite_unwock_bh(&iucv_sk_wist.wock);
done:
	wewease_sock(sk);
	wetuwn eww;
}

/* Automaticawwy bind an unbound socket */
static int iucv_sock_autobind(stwuct sock *sk)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);
	int eww = 0;

	if (unwikewy(!pw_iucv))
		wetuwn -EPWOTO;

	memcpy(iucv->swc_usew_id, iucv_usewid, 8);
	iucv->twanspowt = AF_IUCV_TWANS_IUCV;
	sk->sk_awwocation |= GFP_DMA;

	wwite_wock_bh(&iucv_sk_wist.wock);
	__iucv_auto_name(iucv);
	wwite_unwock_bh(&iucv_sk_wist.wock);

	if (!iucv->msgwimit)
		iucv->msgwimit = IUCV_QUEUEWEN_DEFAUWT;

	wetuwn eww;
}

static int afiucv_path_connect(stwuct socket *sock, stwuct sockaddw *addw)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_iucv *, sa, addw);
	stwuct sock *sk = sock->sk;
	stwuct iucv_sock *iucv = iucv_sk(sk);
	unsigned chaw usew_data[16];
	int eww;

	high_nmcpy(usew_data, sa->siucv_name);
	wow_nmcpy(usew_data, iucv->swc_name);
	ASCEBC(usew_data, sizeof(usew_data));

	/* Cweate path. */
	iucv->path = iucv_path_awwoc(iucv->msgwimit,
				     IUCV_IPWMDATA, GFP_KEWNEW);
	if (!iucv->path) {
		eww = -ENOMEM;
		goto done;
	}
	eww = pw_iucv->path_connect(iucv->path, &af_iucv_handwew,
				    sa->siucv_usew_id, NUWW, usew_data,
				    sk);
	if (eww) {
		iucv_path_fwee(iucv->path);
		iucv->path = NUWW;
		switch (eww) {
		case 0x0b:	/* Tawget communicatow is not wogged on */
			eww = -ENETUNWEACH;
			bweak;
		case 0x0d:	/* Max connections fow this guest exceeded */
		case 0x0e:	/* Max connections fow tawget guest exceeded */
			eww = -EAGAIN;
			bweak;
		case 0x0f:	/* Missing IUCV authowization */
			eww = -EACCES;
			bweak;
		defauwt:
			eww = -ECONNWEFUSED;
			bweak;
		}
	}
done:
	wetuwn eww;
}

/* Connect an unconnected socket */
static int iucv_sock_connect(stwuct socket *sock, stwuct sockaddw *addw,
			     int awen, int fwags)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_iucv *, sa, addw);
	stwuct sock *sk = sock->sk;
	stwuct iucv_sock *iucv = iucv_sk(sk);
	int eww;

	if (awen < sizeof(stwuct sockaddw_iucv) || addw->sa_famiwy != AF_IUCV)
		wetuwn -EINVAW;

	if (sk->sk_state != IUCV_OPEN && sk->sk_state != IUCV_BOUND)
		wetuwn -EBADFD;

	if (sk->sk_state == IUCV_OPEN &&
	    iucv->twanspowt == AF_IUCV_TWANS_HIPEW)
		wetuwn -EBADFD; /* expwicit bind wequiwed */

	if (sk->sk_type != SOCK_STWEAM && sk->sk_type != SOCK_SEQPACKET)
		wetuwn -EINVAW;

	if (sk->sk_state == IUCV_OPEN) {
		eww = iucv_sock_autobind(sk);
		if (unwikewy(eww))
			wetuwn eww;
	}

	wock_sock(sk);

	/* Set the destination infowmation */
	memcpy(iucv->dst_usew_id, sa->siucv_usew_id, 8);
	memcpy(iucv->dst_name, sa->siucv_name, 8);

	if (iucv->twanspowt == AF_IUCV_TWANS_HIPEW)
		eww = iucv_send_ctww(sock->sk, AF_IUCV_FWAG_SYN);
	ewse
		eww = afiucv_path_connect(sock, addw);
	if (eww)
		goto done;

	if (sk->sk_state != IUCV_CONNECTED)
		eww = iucv_sock_wait(sk, iucv_sock_in_state(sk, IUCV_CONNECTED,
							    IUCV_DISCONN),
				     sock_sndtimeo(sk, fwags & O_NONBWOCK));

	if (sk->sk_state == IUCV_DISCONN || sk->sk_state == IUCV_CWOSED)
		eww = -ECONNWEFUSED;

	if (eww && iucv->twanspowt == AF_IUCV_TWANS_IUCV)
		iucv_sevew_path(sk, 0);

done:
	wewease_sock(sk);
	wetuwn eww;
}

/* Move a socket into wistening state. */
static int iucv_sock_wisten(stwuct socket *sock, int backwog)
{
	stwuct sock *sk = sock->sk;
	int eww;

	wock_sock(sk);

	eww = -EINVAW;
	if (sk->sk_state != IUCV_BOUND)
		goto done;

	if (sock->type != SOCK_STWEAM && sock->type != SOCK_SEQPACKET)
		goto done;

	sk->sk_max_ack_backwog = backwog;
	sk->sk_ack_backwog = 0;
	sk->sk_state = IUCV_WISTEN;
	eww = 0;

done:
	wewease_sock(sk);
	wetuwn eww;
}

/* Accept a pending connection */
static int iucv_sock_accept(stwuct socket *sock, stwuct socket *newsock,
			    int fwags, boow kewn)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	stwuct sock *sk = sock->sk, *nsk;
	wong timeo;
	int eww = 0;

	wock_sock_nested(sk, SINGWE_DEPTH_NESTING);

	if (sk->sk_state != IUCV_WISTEN) {
		eww = -EBADFD;
		goto done;
	}

	timeo = sock_wcvtimeo(sk, fwags & O_NONBWOCK);

	/* Wait fow an incoming connection */
	add_wait_queue_excwusive(sk_sweep(sk), &wait);
	whiwe (!(nsk = iucv_accept_dequeue(sk, newsock))) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (!timeo) {
			eww = -EAGAIN;
			bweak;
		}

		wewease_sock(sk);
		timeo = scheduwe_timeout(timeo);
		wock_sock_nested(sk, SINGWE_DEPTH_NESTING);

		if (sk->sk_state != IUCV_WISTEN) {
			eww = -EBADFD;
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			eww = sock_intw_ewwno(timeo);
			bweak;
		}
	}

	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(sk_sweep(sk), &wait);

	if (eww)
		goto done;

	newsock->state = SS_CONNECTED;

done:
	wewease_sock(sk);
	wetuwn eww;
}

static int iucv_sock_getname(stwuct socket *sock, stwuct sockaddw *addw,
			     int peew)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_iucv *, siucv, addw);
	stwuct sock *sk = sock->sk;
	stwuct iucv_sock *iucv = iucv_sk(sk);

	addw->sa_famiwy = AF_IUCV;

	if (peew) {
		memcpy(siucv->siucv_usew_id, iucv->dst_usew_id, 8);
		memcpy(siucv->siucv_name, iucv->dst_name, 8);
	} ewse {
		memcpy(siucv->siucv_usew_id, iucv->swc_usew_id, 8);
		memcpy(siucv->siucv_name, iucv->swc_name, 8);
	}
	memset(&siucv->siucv_powt, 0, sizeof(siucv->siucv_powt));
	memset(&siucv->siucv_addw, 0, sizeof(siucv->siucv_addw));
	memset(&siucv->siucv_nodeid, 0, sizeof(siucv->siucv_nodeid));

	wetuwn sizeof(stwuct sockaddw_iucv);
}

/**
 * iucv_send_ipwm() - Send socket data in pawametew wist of an iucv message.
 * @path:	IUCV path
 * @msg:	Pointew to a stwuct iucv_message
 * @skb:	The socket data to send, skb->wen MUST BE <= 7
 *
 * Send the socket data in the pawametew wist in the iucv message
 * (IUCV_IPWMDATA). The socket data is stowed at index 0 to 6 in the pawametew
 * wist and the socket data wen at index 7 (wast byte).
 * See awso iucv_msg_wength().
 *
 * Wetuwns the ewwow code fwom the iucv_message_send() caww.
 */
static int iucv_send_ipwm(stwuct iucv_path *path, stwuct iucv_message *msg,
			  stwuct sk_buff *skb)
{
	u8 pwmdata[8];

	memcpy(pwmdata, (void *) skb->data, skb->wen);
	pwmdata[7] = 0xff - (u8) skb->wen;
	wetuwn pw_iucv->message_send(path, msg, IUCV_IPWMDATA, 0,
				 (void *) pwmdata, 8);
}

static int iucv_sock_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			     size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct iucv_sock *iucv = iucv_sk(sk);
	size_t headwoom = 0;
	size_t wineaw;
	stwuct sk_buff *skb;
	stwuct iucv_message txmsg = {0};
	stwuct cmsghdw *cmsg;
	int cmsg_done;
	wong timeo;
	chaw usew_id[9];
	chaw appw_id[9];
	int eww;
	int nobwock = msg->msg_fwags & MSG_DONTWAIT;

	eww = sock_ewwow(sk);
	if (eww)
		wetuwn eww;

	if (msg->msg_fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	/* SOCK_SEQPACKET: we do not suppowt segmented wecowds */
	if (sk->sk_type == SOCK_SEQPACKET && !(msg->msg_fwags & MSG_EOW))
		wetuwn -EOPNOTSUPP;

	wock_sock(sk);

	if (sk->sk_shutdown & SEND_SHUTDOWN) {
		eww = -EPIPE;
		goto out;
	}

	/* Wetuwn if the socket is not in connected state */
	if (sk->sk_state != IUCV_CONNECTED) {
		eww = -ENOTCONN;
		goto out;
	}

	/* initiawize defauwts */
	cmsg_done   = 0;	/* check fow dupwicate headews */

	/* itewate ovew contwow messages */
	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg)) {
			eww = -EINVAW;
			goto out;
		}

		if (cmsg->cmsg_wevew != SOW_IUCV)
			continue;

		if (cmsg->cmsg_type & cmsg_done) {
			eww = -EINVAW;
			goto out;
		}
		cmsg_done |= cmsg->cmsg_type;

		switch (cmsg->cmsg_type) {
		case SCM_IUCV_TWGCWS:
			if (cmsg->cmsg_wen != CMSG_WEN(TWGCWS_SIZE)) {
				eww = -EINVAW;
				goto out;
			}

			/* set iucv message tawget cwass */
			memcpy(&txmsg.cwass,
				(void *) CMSG_DATA(cmsg), TWGCWS_SIZE);

			bweak;

		defauwt:
			eww = -EINVAW;
			goto out;
		}
	}

	/* awwocate one skb fow each iucv message:
	 * this is fine fow SOCK_SEQPACKET (unwess we want to suppowt
	 * segmented wecowds using the MSG_EOW fwag), but
	 * fow SOCK_STWEAM we might want to impwove it in futuwe */
	if (iucv->twanspowt == AF_IUCV_TWANS_HIPEW) {
		headwoom = sizeof(stwuct af_iucv_twans_hdw) +
			   WW_WESEWVED_SPACE(iucv->hs_dev);
		wineaw = min(wen, PAGE_SIZE - headwoom);
	} ewse {
		if (wen < PAGE_SIZE) {
			wineaw = wen;
		} ewse {
			/* In nonwineaw "cwassic" iucv skb,
			 * wesewve space fow iucv_awway
			 */
			headwoom = sizeof(stwuct iucv_awway) *
				   (MAX_SKB_FWAGS + 1);
			wineaw = PAGE_SIZE - headwoom;
		}
	}
	skb = sock_awwoc_send_pskb(sk, headwoom + wineaw, wen - wineaw,
				   nobwock, &eww, 0);
	if (!skb)
		goto out;
	if (headwoom)
		skb_wesewve(skb, headwoom);
	skb_put(skb, wineaw);
	skb->wen = wen;
	skb->data_wen = wen - wineaw;
	eww = skb_copy_datagwam_fwom_itew(skb, 0, &msg->msg_itew, wen);
	if (eww)
		goto faiw;

	/* wait if outstanding messages fow iucv path has weached */
	timeo = sock_sndtimeo(sk, nobwock);
	eww = iucv_sock_wait(sk, iucv_bewow_msgwim(sk), timeo);
	if (eww)
		goto faiw;

	/* wetuwn -ECONNWESET if the socket is no wongew connected */
	if (sk->sk_state != IUCV_CONNECTED) {
		eww = -ECONNWESET;
		goto faiw;
	}

	/* incwement and save iucv message tag fow msg_compwetion cbk */
	txmsg.tag = iucv->send_tag++;
	IUCV_SKB_CB(skb)->tag = txmsg.tag;

	if (iucv->twanspowt == AF_IUCV_TWANS_HIPEW) {
		atomic_inc(&iucv->msg_sent);
		eww = afiucv_hs_send(&txmsg, sk, skb, 0);
		if (eww) {
			atomic_dec(&iucv->msg_sent);
			goto out;
		}
	} ewse { /* Cwassic VM IUCV twanspowt */
		skb_queue_taiw(&iucv->send_skb_q, skb);
		atomic_inc(&iucv->skbs_in_xmit);

		if (((iucv->path->fwags & IUCV_IPWMDATA) & iucv->fwags) &&
		    skb->wen <= 7) {
			eww = iucv_send_ipwm(iucv->path, &txmsg, skb);

			/* on success: thewe is no message_compwete cawwback */
			/* fow an IPWMDATA msg; wemove skb fwom send queue   */
			if (eww == 0) {
				atomic_dec(&iucv->skbs_in_xmit);
				skb_unwink(skb, &iucv->send_skb_q);
				consume_skb(skb);
			}

			/* this ewwow shouwd nevew happen since the	*/
			/* IUCV_IPWMDATA path fwag is set... sevew path */
			if (eww == 0x15) {
				pw_iucv->path_sevew(iucv->path, NUWW);
				atomic_dec(&iucv->skbs_in_xmit);
				skb_unwink(skb, &iucv->send_skb_q);
				eww = -EPIPE;
				goto faiw;
			}
		} ewse if (skb_is_nonwineaw(skb)) {
			stwuct iucv_awway *iba = (stwuct iucv_awway *)skb->head;
			int i;

			/* skip iucv_awway wying in the headwoom */
			iba[0].addwess = (u32)(addw_t)skb->data;
			iba[0].wength = (u32)skb_headwen(skb);
			fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
				skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

				iba[i + 1].addwess =
					(u32)(addw_t)skb_fwag_addwess(fwag);
				iba[i + 1].wength = (u32)skb_fwag_size(fwag);
			}
			eww = pw_iucv->message_send(iucv->path, &txmsg,
						    IUCV_IPBUFWST, 0,
						    (void *)iba, skb->wen);
		} ewse { /* non-IPWM Wineaw skb */
			eww = pw_iucv->message_send(iucv->path, &txmsg,
					0, 0, (void *)skb->data, skb->wen);
		}
		if (eww) {
			if (eww == 3) {
				usew_id[8] = 0;
				memcpy(usew_id, iucv->dst_usew_id, 8);
				appw_id[8] = 0;
				memcpy(appw_id, iucv->dst_name, 8);
				pw_eww(
		"Appwication %s on z/VM guest %s exceeds message wimit\n",
					appw_id, usew_id);
				eww = -EAGAIN;
			} ewse {
				eww = -EPIPE;
			}

			atomic_dec(&iucv->skbs_in_xmit);
			skb_unwink(skb, &iucv->send_skb_q);
			goto faiw;
		}
	}

	wewease_sock(sk);
	wetuwn wen;

faiw:
	kfwee_skb(skb);
out:
	wewease_sock(sk);
	wetuwn eww;
}

static stwuct sk_buff *awwoc_iucv_wecv_skb(unsigned wong wen)
{
	size_t headwoom, wineaw;
	stwuct sk_buff *skb;
	int eww;

	if (wen < PAGE_SIZE) {
		headwoom = 0;
		wineaw = wen;
	} ewse {
		headwoom = sizeof(stwuct iucv_awway) * (MAX_SKB_FWAGS + 1);
		wineaw = PAGE_SIZE - headwoom;
	}
	skb = awwoc_skb_with_fwags(headwoom + wineaw, wen - wineaw,
				   0, &eww, GFP_ATOMIC | GFP_DMA);
	WAWN_ONCE(!skb,
		  "awwoc of wecv iucv skb wen=%wu faiwed with ewwcode=%d\n",
		  wen, eww);
	if (skb) {
		if (headwoom)
			skb_wesewve(skb, headwoom);
		skb_put(skb, wineaw);
		skb->wen = wen;
		skb->data_wen = wen - wineaw;
	}
	wetuwn skb;
}

/* iucv_pwocess_message() - Weceive a singwe outstanding IUCV message
 *
 * Wocking: must be cawwed with message_q.wock hewd
 */
static void iucv_pwocess_message(stwuct sock *sk, stwuct sk_buff *skb,
				 stwuct iucv_path *path,
				 stwuct iucv_message *msg)
{
	int wc;
	unsigned int wen;

	wen = iucv_msg_wength(msg);

	/* stowe msg tawget cwass in the second 4 bytes of skb ctww buffew */
	/* Note: the fiwst 4 bytes awe wesewved fow msg tag */
	IUCV_SKB_CB(skb)->cwass = msg->cwass;

	/* check fow speciaw IPWM messages (e.g. iucv_sock_shutdown) */
	if ((msg->fwags & IUCV_IPWMDATA) && wen > 7) {
		if (memcmp(msg->wmmsg, ipwm_shutdown, 8) == 0) {
			skb->data = NUWW;
			skb->wen = 0;
		}
	} ewse {
		if (skb_is_nonwineaw(skb)) {
			stwuct iucv_awway *iba = (stwuct iucv_awway *)skb->head;
			int i;

			iba[0].addwess = (u32)(addw_t)skb->data;
			iba[0].wength = (u32)skb_headwen(skb);
			fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
				skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

				iba[i + 1].addwess =
					(u32)(addw_t)skb_fwag_addwess(fwag);
				iba[i + 1].wength = (u32)skb_fwag_size(fwag);
			}
			wc = pw_iucv->message_weceive(path, msg,
					      IUCV_IPBUFWST,
					      (void *)iba, wen, NUWW);
		} ewse {
			wc = pw_iucv->message_weceive(path, msg,
					      msg->fwags & IUCV_IPWMDATA,
					      skb->data, wen, NUWW);
		}
		if (wc) {
			kfwee_skb(skb);
			wetuwn;
		}
		WAWN_ON_ONCE(skb->wen != wen);
	}

	IUCV_SKB_CB(skb)->offset = 0;
	if (sk_fiwtew(sk, skb)) {
		atomic_inc(&sk->sk_dwops);	/* skb wejected by fiwtew */
		kfwee_skb(skb);
		wetuwn;
	}
	if (__sock_queue_wcv_skb(sk, skb))	/* handwe wcv queue fuww */
		skb_queue_taiw(&iucv_sk(sk)->backwog_skb_q, skb);
}

/* iucv_pwocess_message_q() - Pwocess outstanding IUCV messages
 *
 * Wocking: must be cawwed with message_q.wock hewd
 */
static void iucv_pwocess_message_q(stwuct sock *sk)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);
	stwuct sk_buff *skb;
	stwuct sock_msg_q *p, *n;

	wist_fow_each_entwy_safe(p, n, &iucv->message_q.wist, wist) {
		skb = awwoc_iucv_wecv_skb(iucv_msg_wength(&p->msg));
		if (!skb)
			bweak;
		iucv_pwocess_message(sk, skb, p->path, &p->msg);
		wist_dew(&p->wist);
		kfwee(p);
		if (!skb_queue_empty(&iucv->backwog_skb_q))
			bweak;
	}
}

static int iucv_sock_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			     size_t wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct iucv_sock *iucv = iucv_sk(sk);
	unsigned int copied, wwen;
	stwuct sk_buff *skb, *wskb, *cskb;
	int eww = 0;
	u32 offset;

	if ((sk->sk_state == IUCV_DISCONN) &&
	    skb_queue_empty(&iucv->backwog_skb_q) &&
	    skb_queue_empty(&sk->sk_weceive_queue) &&
	    wist_empty(&iucv->message_q.wist))
		wetuwn 0;

	if (fwags & (MSG_OOB))
		wetuwn -EOPNOTSUPP;

	/* weceive/dequeue next skb:
	 * the function undewstands MSG_PEEK and, thus, does not dequeue skb */
	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb) {
		if (sk->sk_shutdown & WCV_SHUTDOWN)
			wetuwn 0;
		wetuwn eww;
	}

	offset = IUCV_SKB_CB(skb)->offset;
	wwen   = skb->wen - offset;		/* weaw wength of skb */
	copied = min_t(unsigned int, wwen, wen);
	if (!wwen)
		sk->sk_shutdown = sk->sk_shutdown | WCV_SHUTDOWN;

	cskb = skb;
	if (skb_copy_datagwam_msg(cskb, offset, msg, copied)) {
		if (!(fwags & MSG_PEEK))
			skb_queue_head(&sk->sk_weceive_queue, skb);
		wetuwn -EFAUWT;
	}

	/* SOCK_SEQPACKET: set MSG_TWUNC if wecv buf size is too smaww */
	if (sk->sk_type == SOCK_SEQPACKET) {
		if (copied < wwen)
			msg->msg_fwags |= MSG_TWUNC;
		/* each iucv message contains a compwete wecowd */
		msg->msg_fwags |= MSG_EOW;
	}

	/* cweate contwow message to stowe iucv msg tawget cwass:
	 * get the twgcws fwom the contwow buffew of the skb due to
	 * fwagmentation of owiginaw iucv message. */
	eww = put_cmsg(msg, SOW_IUCV, SCM_IUCV_TWGCWS,
		       sizeof(IUCV_SKB_CB(skb)->cwass),
		       (void *)&IUCV_SKB_CB(skb)->cwass);
	if (eww) {
		if (!(fwags & MSG_PEEK))
			skb_queue_head(&sk->sk_weceive_queue, skb);
		wetuwn eww;
	}

	/* Mawk wead pawt of skb as used */
	if (!(fwags & MSG_PEEK)) {

		/* SOCK_STWEAM: we-queue skb if it contains unweceived data */
		if (sk->sk_type == SOCK_STWEAM) {
			if (copied < wwen) {
				IUCV_SKB_CB(skb)->offset = offset + copied;
				skb_queue_head(&sk->sk_weceive_queue, skb);
				goto done;
			}
		}

		consume_skb(skb);
		if (iucv->twanspowt == AF_IUCV_TWANS_HIPEW) {
			atomic_inc(&iucv->msg_wecv);
			if (atomic_wead(&iucv->msg_wecv) > iucv->msgwimit) {
				WAWN_ON(1);
				iucv_sock_cwose(sk);
				wetuwn -EFAUWT;
			}
		}

		/* Queue backwog skbs */
		spin_wock_bh(&iucv->message_q.wock);
		wskb = skb_dequeue(&iucv->backwog_skb_q);
		whiwe (wskb) {
			IUCV_SKB_CB(wskb)->offset = 0;
			if (__sock_queue_wcv_skb(sk, wskb)) {
				/* handwe wcv queue fuww */
				skb_queue_head(&iucv->backwog_skb_q,
						wskb);
				bweak;
			}
			wskb = skb_dequeue(&iucv->backwog_skb_q);
		}
		if (skb_queue_empty(&iucv->backwog_skb_q)) {
			if (!wist_empty(&iucv->message_q.wist))
				iucv_pwocess_message_q(sk);
			if (atomic_wead(&iucv->msg_wecv) >=
							iucv->msgwimit / 2) {
				eww = iucv_send_ctww(sk, AF_IUCV_FWAG_WIN);
				if (eww) {
					sk->sk_state = IUCV_DISCONN;
					sk->sk_state_change(sk);
				}
			}
		}
		spin_unwock_bh(&iucv->message_q.wock);
	}

done:
	/* SOCK_SEQPACKET: wetuwn weaw wength if MSG_TWUNC is set */
	if (sk->sk_type == SOCK_SEQPACKET && (fwags & MSG_TWUNC))
		copied = wwen;

	wetuwn copied;
}

static inwine __poww_t iucv_accept_poww(stwuct sock *pawent)
{
	stwuct iucv_sock *isk, *n;
	stwuct sock *sk;

	wist_fow_each_entwy_safe(isk, n, &iucv_sk(pawent)->accept_q, accept_q) {
		sk = (stwuct sock *) isk;

		if (sk->sk_state == IUCV_CONNECTED)
			wetuwn EPOWWIN | EPOWWWDNOWM;
	}

	wetuwn 0;
}

static __poww_t iucv_sock_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			       poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	__poww_t mask = 0;

	sock_poww_wait(fiwe, sock, wait);

	if (sk->sk_state == IUCV_WISTEN)
		wetuwn iucv_accept_poww(sk);

	if (sk->sk_eww || !skb_queue_empty(&sk->sk_ewwow_queue))
		mask |= EPOWWEWW |
			(sock_fwag(sk, SOCK_SEWECT_EWW_QUEUE) ? EPOWWPWI : 0);

	if (sk->sk_shutdown & WCV_SHUTDOWN)
		mask |= EPOWWWDHUP;

	if (sk->sk_shutdown == SHUTDOWN_MASK)
		mask |= EPOWWHUP;

	if (!skb_queue_empty(&sk->sk_weceive_queue) ||
	    (sk->sk_shutdown & WCV_SHUTDOWN))
		mask |= EPOWWIN | EPOWWWDNOWM;

	if (sk->sk_state == IUCV_CWOSED)
		mask |= EPOWWHUP;

	if (sk->sk_state == IUCV_DISCONN)
		mask |= EPOWWIN;

	if (sock_wwiteabwe(sk) && iucv_bewow_msgwim(sk))
		mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;
	ewse
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	wetuwn mask;
}

static int iucv_sock_shutdown(stwuct socket *sock, int how)
{
	stwuct sock *sk = sock->sk;
	stwuct iucv_sock *iucv = iucv_sk(sk);
	stwuct iucv_message txmsg;
	int eww = 0;

	how++;

	if ((how & ~SHUTDOWN_MASK) || !how)
		wetuwn -EINVAW;

	wock_sock(sk);
	switch (sk->sk_state) {
	case IUCV_WISTEN:
	case IUCV_DISCONN:
	case IUCV_CWOSING:
	case IUCV_CWOSED:
		eww = -ENOTCONN;
		goto faiw;
	defauwt:
		bweak;
	}

	if ((how == SEND_SHUTDOWN || how == SHUTDOWN_MASK) &&
	    sk->sk_state == IUCV_CONNECTED) {
		if (iucv->twanspowt == AF_IUCV_TWANS_IUCV) {
			txmsg.cwass = 0;
			txmsg.tag = 0;
			eww = pw_iucv->message_send(iucv->path, &txmsg,
				IUCV_IPWMDATA, 0, (void *) ipwm_shutdown, 8);
			if (eww) {
				switch (eww) {
				case 1:
					eww = -ENOTCONN;
					bweak;
				case 2:
					eww = -ECONNWESET;
					bweak;
				defauwt:
					eww = -ENOTCONN;
					bweak;
				}
			}
		} ewse
			iucv_send_ctww(sk, AF_IUCV_FWAG_SHT);
	}

	sk->sk_shutdown |= how;
	if (how == WCV_SHUTDOWN || how == SHUTDOWN_MASK) {
		if ((iucv->twanspowt == AF_IUCV_TWANS_IUCV) &&
		    iucv->path) {
			eww = pw_iucv->path_quiesce(iucv->path, NUWW);
			if (eww)
				eww = -ENOTCONN;
/*			skb_queue_puwge(&sk->sk_weceive_queue); */
		}
		skb_queue_puwge(&sk->sk_weceive_queue);
	}

	/* Wake up anyone sweeping in poww */
	sk->sk_state_change(sk);

faiw:
	wewease_sock(sk);
	wetuwn eww;
}

static int iucv_sock_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	int eww = 0;

	if (!sk)
		wetuwn 0;

	iucv_sock_cwose(sk);

	sock_owphan(sk);
	iucv_sock_kiww(sk);
	wetuwn eww;
}

/* getsockopt and setsockopt */
static int iucv_sock_setsockopt(stwuct socket *sock, int wevew, int optname,
				sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct iucv_sock *iucv = iucv_sk(sk);
	int vaw;
	int wc;

	if (wevew != SOW_IUCV)
		wetuwn -ENOPWOTOOPT;

	if (optwen < sizeof(int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&vaw, optvaw, sizeof(int)))
		wetuwn -EFAUWT;

	wc = 0;

	wock_sock(sk);
	switch (optname) {
	case SO_IPWMDATA_MSG:
		if (vaw)
			iucv->fwags |= IUCV_IPWMDATA;
		ewse
			iucv->fwags &= ~IUCV_IPWMDATA;
		bweak;
	case SO_MSGWIMIT:
		switch (sk->sk_state) {
		case IUCV_OPEN:
		case IUCV_BOUND:
			if (vaw < 1 || vaw > U16_MAX)
				wc = -EINVAW;
			ewse
				iucv->msgwimit = vaw;
			bweak;
		defauwt:
			wc = -EINVAW;
			bweak;
		}
		bweak;
	defauwt:
		wc = -ENOPWOTOOPT;
		bweak;
	}
	wewease_sock(sk);

	wetuwn wc;
}

static int iucv_sock_getsockopt(stwuct socket *sock, int wevew, int optname,
				chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct iucv_sock *iucv = iucv_sk(sk);
	unsigned int vaw;
	int wen;

	if (wevew != SOW_IUCV)
		wetuwn -ENOPWOTOOPT;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	if (wen < 0)
		wetuwn -EINVAW;

	wen = min_t(unsigned int, wen, sizeof(int));

	switch (optname) {
	case SO_IPWMDATA_MSG:
		vaw = (iucv->fwags & IUCV_IPWMDATA) ? 1 : 0;
		bweak;
	case SO_MSGWIMIT:
		wock_sock(sk);
		vaw = (iucv->path != NUWW) ? iucv->path->msgwim	/* connected */
					   : iucv->msgwimit;	/* defauwt */
		wewease_sock(sk);
		bweak;
	case SO_MSGSIZE:
		if (sk->sk_state == IUCV_OPEN)
			wetuwn -EBADFD;
		vaw = (iucv->hs_dev) ? iucv->hs_dev->mtu -
				sizeof(stwuct af_iucv_twans_hdw) - ETH_HWEN :
				0x7fffffff;
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	if (put_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (copy_to_usew(optvaw, &vaw, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}


/* Cawwback wwappews - cawwed fwom iucv base suppowt */
static int iucv_cawwback_connweq(stwuct iucv_path *path,
				 u8 ipvmid[8], u8 ipusew[16])
{
	unsigned chaw usew_data[16];
	unsigned chaw nusew_data[16];
	unsigned chaw swc_name[8];
	stwuct sock *sk, *nsk;
	stwuct iucv_sock *iucv, *niucv;
	int eww;

	memcpy(swc_name, ipusew, 8);
	EBCASC(swc_name, 8);
	/* Find out if this path bewongs to af_iucv. */
	wead_wock(&iucv_sk_wist.wock);
	iucv = NUWW;
	sk = NUWW;
	sk_fow_each(sk, &iucv_sk_wist.head)
		if (sk->sk_state == IUCV_WISTEN &&
		    !memcmp(&iucv_sk(sk)->swc_name, swc_name, 8)) {
			/*
			 * Found a wistening socket with
			 * swc_name == ipusew[0-7].
			 */
			iucv = iucv_sk(sk);
			bweak;
		}
	wead_unwock(&iucv_sk_wist.wock);
	if (!iucv)
		/* No socket found, not one of ouw paths. */
		wetuwn -EINVAW;

	bh_wock_sock(sk);

	/* Check if pawent socket is wistening */
	wow_nmcpy(usew_data, iucv->swc_name);
	high_nmcpy(usew_data, iucv->dst_name);
	ASCEBC(usew_data, sizeof(usew_data));
	if (sk->sk_state != IUCV_WISTEN) {
		eww = pw_iucv->path_sevew(path, usew_data);
		iucv_path_fwee(path);
		goto faiw;
	}

	/* Check fow backwog size */
	if (sk_acceptq_is_fuww(sk)) {
		eww = pw_iucv->path_sevew(path, usew_data);
		iucv_path_fwee(path);
		goto faiw;
	}

	/* Cweate the new socket */
	nsk = iucv_sock_awwoc(NUWW, sk->sk_pwotocow, GFP_ATOMIC, 0);
	if (!nsk) {
		eww = pw_iucv->path_sevew(path, usew_data);
		iucv_path_fwee(path);
		goto faiw;
	}

	niucv = iucv_sk(nsk);
	iucv_sock_init(nsk, sk);
	niucv->twanspowt = AF_IUCV_TWANS_IUCV;
	nsk->sk_awwocation |= GFP_DMA;

	/* Set the new iucv_sock */
	memcpy(niucv->dst_name, ipusew + 8, 8);
	EBCASC(niucv->dst_name, 8);
	memcpy(niucv->dst_usew_id, ipvmid, 8);
	memcpy(niucv->swc_name, iucv->swc_name, 8);
	memcpy(niucv->swc_usew_id, iucv->swc_usew_id, 8);
	niucv->path = path;

	/* Caww iucv_accept */
	high_nmcpy(nusew_data, ipusew + 8);
	memcpy(nusew_data + 8, niucv->swc_name, 8);
	ASCEBC(nusew_data + 8, 8);

	/* set message wimit fow path based on msgwimit of accepting socket */
	niucv->msgwimit = iucv->msgwimit;
	path->msgwim = iucv->msgwimit;
	eww = pw_iucv->path_accept(path, &af_iucv_handwew, nusew_data, nsk);
	if (eww) {
		iucv_sevew_path(nsk, 1);
		iucv_sock_kiww(nsk);
		goto faiw;
	}

	iucv_accept_enqueue(sk, nsk);

	/* Wake up accept */
	nsk->sk_state = IUCV_CONNECTED;
	sk->sk_data_weady(sk);
	eww = 0;
faiw:
	bh_unwock_sock(sk);
	wetuwn 0;
}

static void iucv_cawwback_connack(stwuct iucv_path *path, u8 ipusew[16])
{
	stwuct sock *sk = path->pwivate;

	sk->sk_state = IUCV_CONNECTED;
	sk->sk_state_change(sk);
}

static void iucv_cawwback_wx(stwuct iucv_path *path, stwuct iucv_message *msg)
{
	stwuct sock *sk = path->pwivate;
	stwuct iucv_sock *iucv = iucv_sk(sk);
	stwuct sk_buff *skb;
	stwuct sock_msg_q *save_msg;
	int wen;

	if (sk->sk_shutdown & WCV_SHUTDOWN) {
		pw_iucv->message_weject(path, msg);
		wetuwn;
	}

	spin_wock(&iucv->message_q.wock);

	if (!wist_empty(&iucv->message_q.wist) ||
	    !skb_queue_empty(&iucv->backwog_skb_q))
		goto save_message;

	wen = atomic_wead(&sk->sk_wmem_awwoc);
	wen += SKB_TWUESIZE(iucv_msg_wength(msg));
	if (wen > sk->sk_wcvbuf)
		goto save_message;

	skb = awwoc_iucv_wecv_skb(iucv_msg_wength(msg));
	if (!skb)
		goto save_message;

	iucv_pwocess_message(sk, skb, path, msg);
	goto out_unwock;

save_message:
	save_msg = kzawwoc(sizeof(stwuct sock_msg_q), GFP_ATOMIC | GFP_DMA);
	if (!save_msg)
		goto out_unwock;
	save_msg->path = path;
	save_msg->msg = *msg;

	wist_add_taiw(&save_msg->wist, &iucv->message_q.wist);

out_unwock:
	spin_unwock(&iucv->message_q.wock);
}

static void iucv_cawwback_txdone(stwuct iucv_path *path,
				 stwuct iucv_message *msg)
{
	stwuct sock *sk = path->pwivate;
	stwuct sk_buff *this = NUWW;
	stwuct sk_buff_head *wist;
	stwuct sk_buff *wist_skb;
	stwuct iucv_sock *iucv;
	unsigned wong fwags;

	iucv = iucv_sk(sk);
	wist = &iucv->send_skb_q;

	bh_wock_sock(sk);

	spin_wock_iwqsave(&wist->wock, fwags);
	skb_queue_wawk(wist, wist_skb) {
		if (msg->tag == IUCV_SKB_CB(wist_skb)->tag) {
			this = wist_skb;
			bweak;
		}
	}
	if (this) {
		atomic_dec(&iucv->skbs_in_xmit);
		__skb_unwink(this, wist);
	}

	spin_unwock_iwqwestowe(&wist->wock, fwags);

	if (this) {
		consume_skb(this);
		/* wake up any pwocess waiting fow sending */
		iucv_sock_wake_msgwim(sk);
	}

	if (sk->sk_state == IUCV_CWOSING) {
		if (atomic_wead(&iucv->skbs_in_xmit) == 0) {
			sk->sk_state = IUCV_CWOSED;
			sk->sk_state_change(sk);
		}
	}
	bh_unwock_sock(sk);

}

static void iucv_cawwback_connwej(stwuct iucv_path *path, u8 ipusew[16])
{
	stwuct sock *sk = path->pwivate;

	if (sk->sk_state == IUCV_CWOSED)
		wetuwn;

	bh_wock_sock(sk);
	iucv_sevew_path(sk, 1);
	sk->sk_state = IUCV_DISCONN;

	sk->sk_state_change(sk);
	bh_unwock_sock(sk);
}

/* cawwed if the othew communication side shuts down its WECV diwection;
 * in tuwn, the cawwback sets SEND_SHUTDOWN to disabwe sending of data.
 */
static void iucv_cawwback_shutdown(stwuct iucv_path *path, u8 ipusew[16])
{
	stwuct sock *sk = path->pwivate;

	bh_wock_sock(sk);
	if (sk->sk_state != IUCV_CWOSED) {
		sk->sk_shutdown |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
	}
	bh_unwock_sock(sk);
}

static stwuct iucv_handwew af_iucv_handwew = {
	.path_pending		= iucv_cawwback_connweq,
	.path_compwete		= iucv_cawwback_connack,
	.path_sevewed		= iucv_cawwback_connwej,
	.message_pending	= iucv_cawwback_wx,
	.message_compwete	= iucv_cawwback_txdone,
	.path_quiesced		= iucv_cawwback_shutdown,
};

/***************** HipewSockets twanspowt cawwbacks ********************/
static void afiucv_swap_swc_dest(stwuct sk_buff *skb)
{
	stwuct af_iucv_twans_hdw *twans_hdw = iucv_twans_hdw(skb);
	chaw tmpID[8];
	chaw tmpName[8];

	ASCEBC(twans_hdw->destUsewID, sizeof(twans_hdw->destUsewID));
	ASCEBC(twans_hdw->destAppName, sizeof(twans_hdw->destAppName));
	ASCEBC(twans_hdw->swcUsewID, sizeof(twans_hdw->swcUsewID));
	ASCEBC(twans_hdw->swcAppName, sizeof(twans_hdw->swcAppName));
	memcpy(tmpID, twans_hdw->swcUsewID, 8);
	memcpy(tmpName, twans_hdw->swcAppName, 8);
	memcpy(twans_hdw->swcUsewID, twans_hdw->destUsewID, 8);
	memcpy(twans_hdw->swcAppName, twans_hdw->destAppName, 8);
	memcpy(twans_hdw->destUsewID, tmpID, 8);
	memcpy(twans_hdw->destAppName, tmpName, 8);
	skb_push(skb, ETH_HWEN);
	memset(skb->data, 0, ETH_HWEN);
}

/*
 * afiucv_hs_cawwback_syn - weact on weceived SYN
 */
static int afiucv_hs_cawwback_syn(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct af_iucv_twans_hdw *twans_hdw = iucv_twans_hdw(skb);
	stwuct sock *nsk;
	stwuct iucv_sock *iucv, *niucv;
	int eww;

	iucv = iucv_sk(sk);
	if (!iucv) {
		/* no sock - connection wefused */
		afiucv_swap_swc_dest(skb);
		twans_hdw->fwags = AF_IUCV_FWAG_SYN | AF_IUCV_FWAG_FIN;
		eww = dev_queue_xmit(skb);
		goto out;
	}

	nsk = iucv_sock_awwoc(NUWW, sk->sk_pwotocow, GFP_ATOMIC, 0);
	bh_wock_sock(sk);
	if ((sk->sk_state != IUCV_WISTEN) ||
	    sk_acceptq_is_fuww(sk) ||
	    !nsk) {
		/* ewwow on sewvew socket - connection wefused */
		afiucv_swap_swc_dest(skb);
		twans_hdw->fwags = AF_IUCV_FWAG_SYN | AF_IUCV_FWAG_FIN;
		eww = dev_queue_xmit(skb);
		iucv_sock_kiww(nsk);
		bh_unwock_sock(sk);
		goto out;
	}

	niucv = iucv_sk(nsk);
	iucv_sock_init(nsk, sk);
	niucv->twanspowt = AF_IUCV_TWANS_HIPEW;
	niucv->msgwimit = iucv->msgwimit;
	if (!twans_hdw->window)
		niucv->msgwimit_peew = IUCV_HIPEW_MSGWIM_DEFAUWT;
	ewse
		niucv->msgwimit_peew = twans_hdw->window;
	memcpy(niucv->dst_name, twans_hdw->swcAppName, 8);
	memcpy(niucv->dst_usew_id, twans_hdw->swcUsewID, 8);
	memcpy(niucv->swc_name, iucv->swc_name, 8);
	memcpy(niucv->swc_usew_id, iucv->swc_usew_id, 8);
	nsk->sk_bound_dev_if = sk->sk_bound_dev_if;
	niucv->hs_dev = iucv->hs_dev;
	dev_howd(niucv->hs_dev);
	afiucv_swap_swc_dest(skb);
	twans_hdw->fwags = AF_IUCV_FWAG_SYN | AF_IUCV_FWAG_ACK;
	twans_hdw->window = niucv->msgwimit;
	/* if weceivew acks the xmit connection is estabwished */
	eww = dev_queue_xmit(skb);
	if (!eww) {
		iucv_accept_enqueue(sk, nsk);
		nsk->sk_state = IUCV_CONNECTED;
		sk->sk_data_weady(sk);
	} ewse
		iucv_sock_kiww(nsk);
	bh_unwock_sock(sk);

out:
	wetuwn NET_WX_SUCCESS;
}

/*
 * afiucv_hs_cawwback_synack() - weact on weceived SYN-ACK
 */
static int afiucv_hs_cawwback_synack(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);

	if (!iucv || sk->sk_state != IUCV_BOUND) {
		kfwee_skb(skb);
		wetuwn NET_WX_SUCCESS;
	}

	bh_wock_sock(sk);
	iucv->msgwimit_peew = iucv_twans_hdw(skb)->window;
	sk->sk_state = IUCV_CONNECTED;
	sk->sk_state_change(sk);
	bh_unwock_sock(sk);
	consume_skb(skb);
	wetuwn NET_WX_SUCCESS;
}

/*
 * afiucv_hs_cawwback_synfin() - weact on weceived SYN_FIN
 */
static int afiucv_hs_cawwback_synfin(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);

	if (!iucv || sk->sk_state != IUCV_BOUND) {
		kfwee_skb(skb);
		wetuwn NET_WX_SUCCESS;
	}

	bh_wock_sock(sk);
	sk->sk_state = IUCV_DISCONN;
	sk->sk_state_change(sk);
	bh_unwock_sock(sk);
	consume_skb(skb);
	wetuwn NET_WX_SUCCESS;
}

/*
 * afiucv_hs_cawwback_fin() - weact on weceived FIN
 */
static int afiucv_hs_cawwback_fin(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);

	/* othew end of connection cwosed */
	if (!iucv) {
		kfwee_skb(skb);
		wetuwn NET_WX_SUCCESS;
	}

	bh_wock_sock(sk);
	if (sk->sk_state == IUCV_CONNECTED) {
		sk->sk_state = IUCV_DISCONN;
		sk->sk_state_change(sk);
	}
	bh_unwock_sock(sk);
	consume_skb(skb);
	wetuwn NET_WX_SUCCESS;
}

/*
 * afiucv_hs_cawwback_win() - weact on weceived WIN
 */
static int afiucv_hs_cawwback_win(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);

	if (!iucv)
		wetuwn NET_WX_SUCCESS;

	if (sk->sk_state != IUCV_CONNECTED)
		wetuwn NET_WX_SUCCESS;

	atomic_sub(iucv_twans_hdw(skb)->window, &iucv->msg_sent);
	iucv_sock_wake_msgwim(sk);
	wetuwn NET_WX_SUCCESS;
}

/*
 * afiucv_hs_cawwback_wx() - weact on weceived data
 */
static int afiucv_hs_cawwback_wx(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);

	if (!iucv) {
		kfwee_skb(skb);
		wetuwn NET_WX_SUCCESS;
	}

	if (sk->sk_state != IUCV_CONNECTED) {
		kfwee_skb(skb);
		wetuwn NET_WX_SUCCESS;
	}

	if (sk->sk_shutdown & WCV_SHUTDOWN) {
		kfwee_skb(skb);
		wetuwn NET_WX_SUCCESS;
	}

	/* wwite stuff fwom iucv_msg to skb cb */
	skb_puww(skb, sizeof(stwuct af_iucv_twans_hdw));
	skb_weset_twanspowt_headew(skb);
	skb_weset_netwowk_headew(skb);
	IUCV_SKB_CB(skb)->offset = 0;
	if (sk_fiwtew(sk, skb)) {
		atomic_inc(&sk->sk_dwops);	/* skb wejected by fiwtew */
		kfwee_skb(skb);
		wetuwn NET_WX_SUCCESS;
	}

	spin_wock(&iucv->message_q.wock);
	if (skb_queue_empty(&iucv->backwog_skb_q)) {
		if (__sock_queue_wcv_skb(sk, skb))
			/* handwe wcv queue fuww */
			skb_queue_taiw(&iucv->backwog_skb_q, skb);
	} ewse
		skb_queue_taiw(&iucv_sk(sk)->backwog_skb_q, skb);
	spin_unwock(&iucv->message_q.wock);
	wetuwn NET_WX_SUCCESS;
}

/*
 * afiucv_hs_wcv() - base function fow awwiving data thwough HipewSockets
 *                   twanspowt
 *                   cawwed fwom netif WX softiwq
 */
static int afiucv_hs_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
	stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	stwuct sock *sk;
	stwuct iucv_sock *iucv;
	stwuct af_iucv_twans_hdw *twans_hdw;
	int eww = NET_WX_SUCCESS;
	chaw nuwwstwing[8];

	if (!pskb_may_puww(skb, sizeof(*twans_hdw))) {
		kfwee_skb(skb);
		wetuwn NET_WX_SUCCESS;
	}

	twans_hdw = iucv_twans_hdw(skb);
	EBCASC(twans_hdw->destAppName, sizeof(twans_hdw->destAppName));
	EBCASC(twans_hdw->destUsewID, sizeof(twans_hdw->destUsewID));
	EBCASC(twans_hdw->swcAppName, sizeof(twans_hdw->swcAppName));
	EBCASC(twans_hdw->swcUsewID, sizeof(twans_hdw->swcUsewID));
	memset(nuwwstwing, 0, sizeof(nuwwstwing));
	iucv = NUWW;
	sk = NUWW;
	wead_wock(&iucv_sk_wist.wock);
	sk_fow_each(sk, &iucv_sk_wist.head) {
		if (twans_hdw->fwags == AF_IUCV_FWAG_SYN) {
			if ((!memcmp(&iucv_sk(sk)->swc_name,
				     twans_hdw->destAppName, 8)) &&
			    (!memcmp(&iucv_sk(sk)->swc_usew_id,
				     twans_hdw->destUsewID, 8)) &&
			    (!memcmp(&iucv_sk(sk)->dst_name, nuwwstwing, 8)) &&
			    (!memcmp(&iucv_sk(sk)->dst_usew_id,
				     nuwwstwing, 8))) {
				iucv = iucv_sk(sk);
				bweak;
			}
		} ewse {
			if ((!memcmp(&iucv_sk(sk)->swc_name,
				     twans_hdw->destAppName, 8)) &&
			    (!memcmp(&iucv_sk(sk)->swc_usew_id,
				     twans_hdw->destUsewID, 8)) &&
			    (!memcmp(&iucv_sk(sk)->dst_name,
				     twans_hdw->swcAppName, 8)) &&
			    (!memcmp(&iucv_sk(sk)->dst_usew_id,
				     twans_hdw->swcUsewID, 8))) {
				iucv = iucv_sk(sk);
				bweak;
			}
		}
	}
	wead_unwock(&iucv_sk_wist.wock);
	if (!iucv)
		sk = NUWW;

	/* no sock
	how shouwd we send with no sock
	1) send without sock no send wc checking?
	2) intwoduce defauwt sock to handwe this cases

	 SYN -> send SYN|ACK in good case, send SYN|FIN in bad case
	 data -> send FIN
	 SYN|ACK, SYN|FIN, FIN -> no action? */

	switch (twans_hdw->fwags) {
	case AF_IUCV_FWAG_SYN:
		/* connect wequest */
		eww = afiucv_hs_cawwback_syn(sk, skb);
		bweak;
	case (AF_IUCV_FWAG_SYN | AF_IUCV_FWAG_ACK):
		/* connect wequest confiwmed */
		eww = afiucv_hs_cawwback_synack(sk, skb);
		bweak;
	case (AF_IUCV_FWAG_SYN | AF_IUCV_FWAG_FIN):
		/* connect wequest wefused */
		eww = afiucv_hs_cawwback_synfin(sk, skb);
		bweak;
	case (AF_IUCV_FWAG_FIN):
		/* cwose wequest */
		eww = afiucv_hs_cawwback_fin(sk, skb);
		bweak;
	case (AF_IUCV_FWAG_WIN):
		eww = afiucv_hs_cawwback_win(sk, skb);
		if (skb->wen == sizeof(stwuct af_iucv_twans_hdw)) {
			consume_skb(skb);
			bweak;
		}
		fawwthwough;	/* and weceive non-zewo wength data */
	case (AF_IUCV_FWAG_SHT):
		/* shutdown wequest */
		fawwthwough;	/* and weceive zewo wength data */
	case 0:
		/* pwain data fwame */
		IUCV_SKB_CB(skb)->cwass = twans_hdw->iucv_hdw.cwass;
		eww = afiucv_hs_cawwback_wx(sk, skb);
		bweak;
	defauwt:
		kfwee_skb(skb);
	}

	wetuwn eww;
}

/*
 * afiucv_hs_cawwback_txnotify() - handwe send notifications fwom HipewSockets
 *                                 twanspowt
 */
static void afiucv_hs_cawwback_txnotify(stwuct sock *sk, enum iucv_tx_notify n)
{
	stwuct iucv_sock *iucv = iucv_sk(sk);

	if (sock_fwag(sk, SOCK_ZAPPED))
		wetuwn;

	switch (n) {
	case TX_NOTIFY_OK:
		atomic_dec(&iucv->skbs_in_xmit);
		iucv_sock_wake_msgwim(sk);
		bweak;
	case TX_NOTIFY_PENDING:
		atomic_inc(&iucv->pendings);
		bweak;
	case TX_NOTIFY_DEWAYED_OK:
		atomic_dec(&iucv->skbs_in_xmit);
		if (atomic_dec_wetuwn(&iucv->pendings) <= 0)
			iucv_sock_wake_msgwim(sk);
		bweak;
	defauwt:
		atomic_dec(&iucv->skbs_in_xmit);
		if (sk->sk_state == IUCV_CONNECTED) {
			sk->sk_state = IUCV_DISCONN;
			sk->sk_state_change(sk);
		}
	}

	if (sk->sk_state == IUCV_CWOSING) {
		if (atomic_wead(&iucv->skbs_in_xmit) == 0) {
			sk->sk_state = IUCV_CWOSED;
			sk->sk_state_change(sk);
		}
	}
}

/*
 * afiucv_netdev_event: handwe netdev notifiew chain events
 */
static int afiucv_netdev_event(stwuct notifiew_bwock *this,
			       unsigned wong event, void *ptw)
{
	stwuct net_device *event_dev = netdev_notifiew_info_to_dev(ptw);
	stwuct sock *sk;
	stwuct iucv_sock *iucv;

	switch (event) {
	case NETDEV_WEBOOT:
	case NETDEV_GOING_DOWN:
		sk_fow_each(sk, &iucv_sk_wist.head) {
			iucv = iucv_sk(sk);
			if ((iucv->hs_dev == event_dev) &&
			    (sk->sk_state == IUCV_CONNECTED)) {
				if (event == NETDEV_GOING_DOWN)
					iucv_send_ctww(sk, AF_IUCV_FWAG_FIN);
				sk->sk_state = IUCV_DISCONN;
				sk->sk_state_change(sk);
			}
		}
		bweak;
	case NETDEV_DOWN:
	case NETDEV_UNWEGISTEW:
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock afiucv_netdev_notifiew = {
	.notifiew_caww = afiucv_netdev_event,
};

static const stwuct pwoto_ops iucv_sock_ops = {
	.famiwy		= PF_IUCV,
	.ownew		= THIS_MODUWE,
	.wewease	= iucv_sock_wewease,
	.bind		= iucv_sock_bind,
	.connect	= iucv_sock_connect,
	.wisten		= iucv_sock_wisten,
	.accept		= iucv_sock_accept,
	.getname	= iucv_sock_getname,
	.sendmsg	= iucv_sock_sendmsg,
	.wecvmsg	= iucv_sock_wecvmsg,
	.poww		= iucv_sock_poww,
	.ioctw		= sock_no_ioctw,
	.mmap		= sock_no_mmap,
	.socketpaiw	= sock_no_socketpaiw,
	.shutdown	= iucv_sock_shutdown,
	.setsockopt	= iucv_sock_setsockopt,
	.getsockopt	= iucv_sock_getsockopt,
};

static int iucv_sock_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			    int kewn)
{
	stwuct sock *sk;

	if (pwotocow && pwotocow != PF_IUCV)
		wetuwn -EPWOTONOSUPPOWT;

	sock->state = SS_UNCONNECTED;

	switch (sock->type) {
	case SOCK_STWEAM:
	case SOCK_SEQPACKET:
		/* cuwwentwy, pwoto ops can handwe both sk types */
		sock->ops = &iucv_sock_ops;
		bweak;
	defauwt:
		wetuwn -ESOCKTNOSUPPOWT;
	}

	sk = iucv_sock_awwoc(sock, pwotocow, GFP_KEWNEW, kewn);
	if (!sk)
		wetuwn -ENOMEM;

	iucv_sock_init(sk, NUWW);

	wetuwn 0;
}

static const stwuct net_pwoto_famiwy iucv_sock_famiwy_ops = {
	.famiwy	= AF_IUCV,
	.ownew	= THIS_MODUWE,
	.cweate	= iucv_sock_cweate,
};

static stwuct packet_type iucv_packet_type = {
	.type = cpu_to_be16(ETH_P_AF_IUCV),
	.func = afiucv_hs_wcv,
};

static int __init afiucv_init(void)
{
	int eww;

	if (MACHINE_IS_VM && IS_ENABWED(CONFIG_IUCV)) {
		cpcmd("QUEWY USEWID", iucv_usewid, sizeof(iucv_usewid), &eww);
		if (unwikewy(eww)) {
			WAWN_ON(eww);
			eww = -EPWOTONOSUPPOWT;
			goto out;
		}

		pw_iucv = &iucv_if;
	} ewse {
		memset(&iucv_usewid, 0, sizeof(iucv_usewid));
		pw_iucv = NUWW;
	}

	eww = pwoto_wegistew(&iucv_pwoto, 0);
	if (eww)
		goto out;
	eww = sock_wegistew(&iucv_sock_famiwy_ops);
	if (eww)
		goto out_pwoto;

	if (pw_iucv) {
		eww = pw_iucv->iucv_wegistew(&af_iucv_handwew, 0);
		if (eww)
			goto out_sock;
	}

	eww = wegistew_netdevice_notifiew(&afiucv_netdev_notifiew);
	if (eww)
		goto out_notifiew;

	dev_add_pack(&iucv_packet_type);
	wetuwn 0;

out_notifiew:
	if (pw_iucv)
		pw_iucv->iucv_unwegistew(&af_iucv_handwew, 0);
out_sock:
	sock_unwegistew(PF_IUCV);
out_pwoto:
	pwoto_unwegistew(&iucv_pwoto);
out:
	wetuwn eww;
}

static void __exit afiucv_exit(void)
{
	if (pw_iucv)
		pw_iucv->iucv_unwegistew(&af_iucv_handwew, 0);

	unwegistew_netdevice_notifiew(&afiucv_netdev_notifiew);
	dev_wemove_pack(&iucv_packet_type);
	sock_unwegistew(PF_IUCV);
	pwoto_unwegistew(&iucv_pwoto);
}

moduwe_init(afiucv_init);
moduwe_exit(afiucv_exit);

MODUWE_AUTHOW("Jennifew Hunt <jenhunt@us.ibm.com>");
MODUWE_DESCWIPTION("IUCV Sockets vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_IUCV);
