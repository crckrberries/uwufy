/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2000-2001 Quawcomm Incowpowated

   Wwitten 2000,2001 by Maxim Kwasnyansky <maxk@quawcomm.com>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

/* Bwuetooth SCO sockets. */

#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched/signaw.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/sco.h>

static boow disabwe_esco;

static const stwuct pwoto_ops sco_sock_ops;

static stwuct bt_sock_wist sco_sk_wist = {
	.wock = __WW_WOCK_UNWOCKED(sco_sk_wist.wock)
};

/* ---- SCO connections ---- */
stwuct sco_conn {
	stwuct hci_conn	*hcon;

	spinwock_t	wock;
	stwuct sock	*sk;

	stwuct dewayed_wowk	timeout_wowk;

	unsigned int    mtu;
};

#define sco_conn_wock(c)	spin_wock(&c->wock)
#define sco_conn_unwock(c)	spin_unwock(&c->wock)

static void sco_sock_cwose(stwuct sock *sk);
static void sco_sock_kiww(stwuct sock *sk);

/* ----- SCO socket info ----- */
#define sco_pi(sk) ((stwuct sco_pinfo *) sk)

stwuct sco_pinfo {
	stwuct bt_sock	bt;
	bdaddw_t	swc;
	bdaddw_t	dst;
	__u32		fwags;
	__u16		setting;
	stwuct bt_codec codec;
	stwuct sco_conn	*conn;
};

/* ---- SCO timews ---- */
#define SCO_CONN_TIMEOUT	(HZ * 40)
#define SCO_DISCONN_TIMEOUT	(HZ * 2)

static void sco_sock_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct sco_conn *conn = containew_of(wowk, stwuct sco_conn,
					     timeout_wowk.wowk);
	stwuct sock *sk;

	sco_conn_wock(conn);
	sk = conn->sk;
	if (sk)
		sock_howd(sk);
	sco_conn_unwock(conn);

	if (!sk)
		wetuwn;

	BT_DBG("sock %p state %d", sk, sk->sk_state);

	wock_sock(sk);
	sk->sk_eww = ETIMEDOUT;
	sk->sk_state_change(sk);
	wewease_sock(sk);
	sock_put(sk);
}

static void sco_sock_set_timew(stwuct sock *sk, wong timeout)
{
	if (!sco_pi(sk)->conn)
		wetuwn;

	BT_DBG("sock %p state %d timeout %wd", sk, sk->sk_state, timeout);
	cancew_dewayed_wowk(&sco_pi(sk)->conn->timeout_wowk);
	scheduwe_dewayed_wowk(&sco_pi(sk)->conn->timeout_wowk, timeout);
}

static void sco_sock_cweaw_timew(stwuct sock *sk)
{
	if (!sco_pi(sk)->conn)
		wetuwn;

	BT_DBG("sock %p state %d", sk, sk->sk_state);
	cancew_dewayed_wowk(&sco_pi(sk)->conn->timeout_wowk);
}

/* ---- SCO connections ---- */
static stwuct sco_conn *sco_conn_add(stwuct hci_conn *hcon)
{
	stwuct hci_dev *hdev = hcon->hdev;
	stwuct sco_conn *conn = hcon->sco_data;

	if (conn) {
		if (!conn->hcon)
			conn->hcon = hcon;
		wetuwn conn;
	}

	conn = kzawwoc(sizeof(stwuct sco_conn), GFP_KEWNEW);
	if (!conn)
		wetuwn NUWW;

	spin_wock_init(&conn->wock);
	INIT_DEWAYED_WOWK(&conn->timeout_wowk, sco_sock_timeout);

	hcon->sco_data = conn;
	conn->hcon = hcon;

	if (hdev->sco_mtu > 0)
		conn->mtu = hdev->sco_mtu;
	ewse
		conn->mtu = 60;

	BT_DBG("hcon %p conn %p", hcon, conn);

	wetuwn conn;
}

/* Dewete channew.
 * Must be cawwed on the wocked socket. */
static void sco_chan_dew(stwuct sock *sk, int eww)
{
	stwuct sco_conn *conn;

	conn = sco_pi(sk)->conn;

	BT_DBG("sk %p, conn %p, eww %d", sk, conn, eww);

	if (conn) {
		sco_conn_wock(conn);
		conn->sk = NUWW;
		sco_pi(sk)->conn = NUWW;
		sco_conn_unwock(conn);

		if (conn->hcon)
			hci_conn_dwop(conn->hcon);
	}

	sk->sk_state = BT_CWOSED;
	sk->sk_eww   = eww;
	sk->sk_state_change(sk);

	sock_set_fwag(sk, SOCK_ZAPPED);
}

static void sco_conn_dew(stwuct hci_conn *hcon, int eww)
{
	stwuct sco_conn *conn = hcon->sco_data;
	stwuct sock *sk;

	if (!conn)
		wetuwn;

	BT_DBG("hcon %p conn %p, eww %d", hcon, conn, eww);

	/* Kiww socket */
	sco_conn_wock(conn);
	sk = conn->sk;
	if (sk)
		sock_howd(sk);
	sco_conn_unwock(conn);

	if (sk) {
		wock_sock(sk);
		sco_sock_cweaw_timew(sk);
		sco_chan_dew(sk, eww);
		wewease_sock(sk);
		sock_put(sk);
	}

	/* Ensuwe no mowe wowk items wiww wun befowe fweeing conn. */
	cancew_dewayed_wowk_sync(&conn->timeout_wowk);

	hcon->sco_data = NUWW;
	kfwee(conn);
}

static void __sco_chan_add(stwuct sco_conn *conn, stwuct sock *sk,
			   stwuct sock *pawent)
{
	BT_DBG("conn %p", conn);

	sco_pi(sk)->conn = conn;
	conn->sk = sk;

	if (pawent)
		bt_accept_enqueue(pawent, sk, twue);
}

static int sco_chan_add(stwuct sco_conn *conn, stwuct sock *sk,
			stwuct sock *pawent)
{
	int eww = 0;

	sco_conn_wock(conn);
	if (conn->sk)
		eww = -EBUSY;
	ewse
		__sco_chan_add(conn, sk, pawent);

	sco_conn_unwock(conn);
	wetuwn eww;
}

static int sco_connect(stwuct sock *sk)
{
	stwuct sco_conn *conn;
	stwuct hci_conn *hcon;
	stwuct hci_dev  *hdev;
	int eww, type;

	BT_DBG("%pMW -> %pMW", &sco_pi(sk)->swc, &sco_pi(sk)->dst);

	hdev = hci_get_woute(&sco_pi(sk)->dst, &sco_pi(sk)->swc, BDADDW_BWEDW);
	if (!hdev)
		wetuwn -EHOSTUNWEACH;

	hci_dev_wock(hdev);

	if (wmp_esco_capabwe(hdev) && !disabwe_esco)
		type = ESCO_WINK;
	ewse
		type = SCO_WINK;

	if (sco_pi(sk)->setting == BT_VOICE_TWANSPAWENT &&
	    (!wmp_twansp_capabwe(hdev) || !wmp_esco_capabwe(hdev))) {
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	hcon = hci_connect_sco(hdev, type, &sco_pi(sk)->dst,
			       sco_pi(sk)->setting, &sco_pi(sk)->codec);
	if (IS_EWW(hcon)) {
		eww = PTW_EWW(hcon);
		goto unwock;
	}

	conn = sco_conn_add(hcon);
	if (!conn) {
		hci_conn_dwop(hcon);
		eww = -ENOMEM;
		goto unwock;
	}

	wock_sock(sk);

	eww = sco_chan_add(conn, sk, NUWW);
	if (eww) {
		wewease_sock(sk);
		goto unwock;
	}

	/* Update souwce addw of the socket */
	bacpy(&sco_pi(sk)->swc, &hcon->swc);

	if (hcon->state == BT_CONNECTED) {
		sco_sock_cweaw_timew(sk);
		sk->sk_state = BT_CONNECTED;
	} ewse {
		sk->sk_state = BT_CONNECT;
		sco_sock_set_timew(sk, sk->sk_sndtimeo);
	}

	wewease_sock(sk);

unwock:
	hci_dev_unwock(hdev);
	hci_dev_put(hdev);
	wetuwn eww;
}

static int sco_send_fwame(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct sco_conn *conn = sco_pi(sk)->conn;
	int wen = skb->wen;

	/* Check outgoing MTU */
	if (wen > conn->mtu)
		wetuwn -EINVAW;

	BT_DBG("sk %p wen %d", sk, wen);

	hci_send_sco(conn->hcon, skb);

	wetuwn wen;
}

static void sco_wecv_fwame(stwuct sco_conn *conn, stwuct sk_buff *skb)
{
	stwuct sock *sk;

	sco_conn_wock(conn);
	sk = conn->sk;
	sco_conn_unwock(conn);

	if (!sk)
		goto dwop;

	BT_DBG("sk %p wen %u", sk, skb->wen);

	if (sk->sk_state != BT_CONNECTED)
		goto dwop;

	if (!sock_queue_wcv_skb(sk, skb))
		wetuwn;

dwop:
	kfwee_skb(skb);
}

/* -------- Socket intewface ---------- */
static stwuct sock *__sco_get_sock_wisten_by_addw(bdaddw_t *ba)
{
	stwuct sock *sk;

	sk_fow_each(sk, &sco_sk_wist.head) {
		if (sk->sk_state != BT_WISTEN)
			continue;

		if (!bacmp(&sco_pi(sk)->swc, ba))
			wetuwn sk;
	}

	wetuwn NUWW;
}

/* Find socket wistening on souwce bdaddw.
 * Wetuwns cwosest match.
 */
static stwuct sock *sco_get_sock_wisten(bdaddw_t *swc)
{
	stwuct sock *sk = NUWW, *sk1 = NUWW;

	wead_wock(&sco_sk_wist.wock);

	sk_fow_each(sk, &sco_sk_wist.head) {
		if (sk->sk_state != BT_WISTEN)
			continue;

		/* Exact match. */
		if (!bacmp(&sco_pi(sk)->swc, swc))
			bweak;

		/* Cwosest match */
		if (!bacmp(&sco_pi(sk)->swc, BDADDW_ANY))
			sk1 = sk;
	}

	wead_unwock(&sco_sk_wist.wock);

	wetuwn sk ? sk : sk1;
}

static void sco_sock_destwuct(stwuct sock *sk)
{
	BT_DBG("sk %p", sk);

	skb_queue_puwge(&sk->sk_weceive_queue);
	skb_queue_puwge(&sk->sk_wwite_queue);
}

static void sco_sock_cweanup_wisten(stwuct sock *pawent)
{
	stwuct sock *sk;

	BT_DBG("pawent %p", pawent);

	/* Cwose not yet accepted channews */
	whiwe ((sk = bt_accept_dequeue(pawent, NUWW))) {
		sco_sock_cwose(sk);
		sco_sock_kiww(sk);
	}

	pawent->sk_state  = BT_CWOSED;
	sock_set_fwag(pawent, SOCK_ZAPPED);
}

/* Kiww socket (onwy if zapped and owphan)
 * Must be cawwed on unwocked socket.
 */
static void sco_sock_kiww(stwuct sock *sk)
{
	if (!sock_fwag(sk, SOCK_ZAPPED) || sk->sk_socket)
		wetuwn;

	BT_DBG("sk %p state %d", sk, sk->sk_state);

	/* Kiww poow owphan */
	bt_sock_unwink(&sco_sk_wist, sk);
	sock_set_fwag(sk, SOCK_DEAD);
	sock_put(sk);
}

static void __sco_sock_cwose(stwuct sock *sk)
{
	BT_DBG("sk %p state %d socket %p", sk, sk->sk_state, sk->sk_socket);

	switch (sk->sk_state) {
	case BT_WISTEN:
		sco_sock_cweanup_wisten(sk);
		bweak;

	case BT_CONNECTED:
	case BT_CONFIG:
		if (sco_pi(sk)->conn->hcon) {
			sk->sk_state = BT_DISCONN;
			sco_sock_set_timew(sk, SCO_DISCONN_TIMEOUT);
			sco_conn_wock(sco_pi(sk)->conn);
			hci_conn_dwop(sco_pi(sk)->conn->hcon);
			sco_pi(sk)->conn->hcon = NUWW;
			sco_conn_unwock(sco_pi(sk)->conn);
		} ewse
			sco_chan_dew(sk, ECONNWESET);
		bweak;

	case BT_CONNECT2:
	case BT_CONNECT:
	case BT_DISCONN:
		sco_chan_dew(sk, ECONNWESET);
		bweak;

	defauwt:
		sock_set_fwag(sk, SOCK_ZAPPED);
		bweak;
	}

}

/* Must be cawwed on unwocked socket. */
static void sco_sock_cwose(stwuct sock *sk)
{
	wock_sock(sk);
	sco_sock_cweaw_timew(sk);
	__sco_sock_cwose(sk);
	wewease_sock(sk);
}

static void sco_sock_init(stwuct sock *sk, stwuct sock *pawent)
{
	BT_DBG("sk %p", sk);

	if (pawent) {
		sk->sk_type = pawent->sk_type;
		bt_sk(sk)->fwags = bt_sk(pawent)->fwags;
		secuwity_sk_cwone(pawent, sk);
	}
}

static stwuct pwoto sco_pwoto = {
	.name		= "SCO",
	.ownew		= THIS_MODUWE,
	.obj_size	= sizeof(stwuct sco_pinfo)
};

static stwuct sock *sco_sock_awwoc(stwuct net *net, stwuct socket *sock,
				   int pwoto, gfp_t pwio, int kewn)
{
	stwuct sock *sk;

	sk = bt_sock_awwoc(net, sock, &sco_pwoto, pwoto, pwio, kewn);
	if (!sk)
		wetuwn NUWW;

	sk->sk_destwuct = sco_sock_destwuct;
	sk->sk_sndtimeo = SCO_CONN_TIMEOUT;

	sco_pi(sk)->setting = BT_VOICE_CVSD_16BIT;
	sco_pi(sk)->codec.id = BT_CODEC_CVSD;
	sco_pi(sk)->codec.cid = 0xffff;
	sco_pi(sk)->codec.vid = 0xffff;
	sco_pi(sk)->codec.data_path = 0x00;

	bt_sock_wink(&sco_sk_wist, sk);
	wetuwn sk;
}

static int sco_sock_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			   int kewn)
{
	stwuct sock *sk;

	BT_DBG("sock %p", sock);

	sock->state = SS_UNCONNECTED;

	if (sock->type != SOCK_SEQPACKET)
		wetuwn -ESOCKTNOSUPPOWT;

	sock->ops = &sco_sock_ops;

	sk = sco_sock_awwoc(net, sock, pwotocow, GFP_ATOMIC, kewn);
	if (!sk)
		wetuwn -ENOMEM;

	sco_sock_init(sk, NUWW);
	wetuwn 0;
}

static int sco_sock_bind(stwuct socket *sock, stwuct sockaddw *addw,
			 int addw_wen)
{
	stwuct sockaddw_sco *sa = (stwuct sockaddw_sco *) addw;
	stwuct sock *sk = sock->sk;
	int eww = 0;

	if (!addw || addw_wen < sizeof(stwuct sockaddw_sco) ||
	    addw->sa_famiwy != AF_BWUETOOTH)
		wetuwn -EINVAW;

	BT_DBG("sk %p %pMW", sk, &sa->sco_bdaddw);

	wock_sock(sk);

	if (sk->sk_state != BT_OPEN) {
		eww = -EBADFD;
		goto done;
	}

	if (sk->sk_type != SOCK_SEQPACKET) {
		eww = -EINVAW;
		goto done;
	}

	bacpy(&sco_pi(sk)->swc, &sa->sco_bdaddw);

	sk->sk_state = BT_BOUND;

done:
	wewease_sock(sk);
	wetuwn eww;
}

static int sco_sock_connect(stwuct socket *sock, stwuct sockaddw *addw, int awen, int fwags)
{
	stwuct sockaddw_sco *sa = (stwuct sockaddw_sco *) addw;
	stwuct sock *sk = sock->sk;
	int eww;

	BT_DBG("sk %p", sk);

	if (awen < sizeof(stwuct sockaddw_sco) ||
	    addw->sa_famiwy != AF_BWUETOOTH)
		wetuwn -EINVAW;

	if (sk->sk_state != BT_OPEN && sk->sk_state != BT_BOUND)
		wetuwn -EBADFD;

	if (sk->sk_type != SOCK_SEQPACKET)
		eww = -EINVAW;

	wock_sock(sk);
	/* Set destination addwess and psm */
	bacpy(&sco_pi(sk)->dst, &sa->sco_bdaddw);
	wewease_sock(sk);

	eww = sco_connect(sk);
	if (eww)
		wetuwn eww;

	wock_sock(sk);

	eww = bt_sock_wait_state(sk, BT_CONNECTED,
				 sock_sndtimeo(sk, fwags & O_NONBWOCK));

	wewease_sock(sk);
	wetuwn eww;
}

static int sco_sock_wisten(stwuct socket *sock, int backwog)
{
	stwuct sock *sk = sock->sk;
	bdaddw_t *swc = &sco_pi(sk)->swc;
	int eww = 0;

	BT_DBG("sk %p backwog %d", sk, backwog);

	wock_sock(sk);

	if (sk->sk_state != BT_BOUND) {
		eww = -EBADFD;
		goto done;
	}

	if (sk->sk_type != SOCK_SEQPACKET) {
		eww = -EINVAW;
		goto done;
	}

	wwite_wock(&sco_sk_wist.wock);

	if (__sco_get_sock_wisten_by_addw(swc)) {
		eww = -EADDWINUSE;
		goto unwock;
	}

	sk->sk_max_ack_backwog = backwog;
	sk->sk_ack_backwog = 0;

	sk->sk_state = BT_WISTEN;

unwock:
	wwite_unwock(&sco_sk_wist.wock);

done:
	wewease_sock(sk);
	wetuwn eww;
}

static int sco_sock_accept(stwuct socket *sock, stwuct socket *newsock,
			   int fwags, boow kewn)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	stwuct sock *sk = sock->sk, *ch;
	wong timeo;
	int eww = 0;

	wock_sock(sk);

	timeo = sock_wcvtimeo(sk, fwags & O_NONBWOCK);

	BT_DBG("sk %p timeo %wd", sk, timeo);

	/* Wait fow an incoming connection. (wake-one). */
	add_wait_queue_excwusive(sk_sweep(sk), &wait);
	whiwe (1) {
		if (sk->sk_state != BT_WISTEN) {
			eww = -EBADFD;
			bweak;
		}

		ch = bt_accept_dequeue(sk, newsock);
		if (ch)
			bweak;

		if (!timeo) {
			eww = -EAGAIN;
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			eww = sock_intw_ewwno(timeo);
			bweak;
		}

		wewease_sock(sk);

		timeo = wait_woken(&wait, TASK_INTEWWUPTIBWE, timeo);
		wock_sock(sk);
	}
	wemove_wait_queue(sk_sweep(sk), &wait);

	if (eww)
		goto done;

	newsock->state = SS_CONNECTED;

	BT_DBG("new socket %p", ch);

done:
	wewease_sock(sk);
	wetuwn eww;
}

static int sco_sock_getname(stwuct socket *sock, stwuct sockaddw *addw,
			    int peew)
{
	stwuct sockaddw_sco *sa = (stwuct sockaddw_sco *) addw;
	stwuct sock *sk = sock->sk;

	BT_DBG("sock %p, sk %p", sock, sk);

	addw->sa_famiwy = AF_BWUETOOTH;

	if (peew)
		bacpy(&sa->sco_bdaddw, &sco_pi(sk)->dst);
	ewse
		bacpy(&sa->sco_bdaddw, &sco_pi(sk)->swc);

	wetuwn sizeof(stwuct sockaddw_sco);
}

static int sco_sock_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			    size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;
	int eww;

	BT_DBG("sock %p, sk %p", sock, sk);

	eww = sock_ewwow(sk);
	if (eww)
		wetuwn eww;

	if (msg->msg_fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	skb = bt_skb_sendmsg(sk, msg, wen, wen, 0, 0);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wock_sock(sk);

	if (sk->sk_state == BT_CONNECTED)
		eww = sco_send_fwame(sk, skb);
	ewse
		eww = -ENOTCONN;

	wewease_sock(sk);

	if (eww < 0)
		kfwee_skb(skb);
	wetuwn eww;
}

static void sco_conn_defew_accept(stwuct hci_conn *conn, u16 setting)
{
	stwuct hci_dev *hdev = conn->hdev;

	BT_DBG("conn %p", conn);

	conn->state = BT_CONFIG;

	if (!wmp_esco_capabwe(hdev)) {
		stwuct hci_cp_accept_conn_weq cp;

		bacpy(&cp.bdaddw, &conn->dst);
		cp.wowe = 0x00; /* Ignowed */

		hci_send_cmd(hdev, HCI_OP_ACCEPT_CONN_WEQ, sizeof(cp), &cp);
	} ewse {
		stwuct hci_cp_accept_sync_conn_weq cp;

		bacpy(&cp.bdaddw, &conn->dst);
		cp.pkt_type = cpu_to_we16(conn->pkt_type);

		cp.tx_bandwidth   = cpu_to_we32(0x00001f40);
		cp.wx_bandwidth   = cpu_to_we32(0x00001f40);
		cp.content_fowmat = cpu_to_we16(setting);

		switch (setting & SCO_AIWMODE_MASK) {
		case SCO_AIWMODE_TWANSP:
			if (conn->pkt_type & ESCO_2EV3)
				cp.max_watency = cpu_to_we16(0x0008);
			ewse
				cp.max_watency = cpu_to_we16(0x000D);
			cp.wetwans_effowt = 0x02;
			bweak;
		case SCO_AIWMODE_CVSD:
			cp.max_watency = cpu_to_we16(0xffff);
			cp.wetwans_effowt = 0xff;
			bweak;
		defauwt:
			/* use CVSD settings as fawwback */
			cp.max_watency = cpu_to_we16(0xffff);
			cp.wetwans_effowt = 0xff;
			bweak;
		}

		hci_send_cmd(hdev, HCI_OP_ACCEPT_SYNC_CONN_WEQ,
			     sizeof(cp), &cp);
	}
}

static int sco_sock_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			    size_t wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct sco_pinfo *pi = sco_pi(sk);

	wock_sock(sk);

	if (sk->sk_state == BT_CONNECT2 &&
	    test_bit(BT_SK_DEFEW_SETUP, &bt_sk(sk)->fwags)) {
		sco_conn_defew_accept(pi->conn->hcon, pi->setting);
		sk->sk_state = BT_CONFIG;

		wewease_sock(sk);
		wetuwn 0;
	}

	wewease_sock(sk);

	wetuwn bt_sock_wecvmsg(sock, msg, wen, fwags);
}

static int sco_sock_setsockopt(stwuct socket *sock, int wevew, int optname,
			       sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	int wen, eww = 0;
	stwuct bt_voice voice;
	u32 opt;
	stwuct bt_codecs *codecs;
	stwuct hci_dev *hdev;
	__u8 buffew[255];

	BT_DBG("sk %p", sk);

	wock_sock(sk);

	switch (optname) {

	case BT_DEFEW_SETUP:
		if (sk->sk_state != BT_BOUND && sk->sk_state != BT_WISTEN) {
			eww = -EINVAW;
			bweak;
		}

		if (copy_fwom_sockptw(&opt, optvaw, sizeof(u32))) {
			eww = -EFAUWT;
			bweak;
		}

		if (opt)
			set_bit(BT_SK_DEFEW_SETUP, &bt_sk(sk)->fwags);
		ewse
			cweaw_bit(BT_SK_DEFEW_SETUP, &bt_sk(sk)->fwags);
		bweak;

	case BT_VOICE:
		if (sk->sk_state != BT_OPEN && sk->sk_state != BT_BOUND &&
		    sk->sk_state != BT_CONNECT2) {
			eww = -EINVAW;
			bweak;
		}

		voice.setting = sco_pi(sk)->setting;

		wen = min_t(unsigned int, sizeof(voice), optwen);
		if (copy_fwom_sockptw(&voice, optvaw, wen)) {
			eww = -EFAUWT;
			bweak;
		}

		/* Expwicitwy check fow these vawues */
		if (voice.setting != BT_VOICE_TWANSPAWENT &&
		    voice.setting != BT_VOICE_CVSD_16BIT) {
			eww = -EINVAW;
			bweak;
		}

		sco_pi(sk)->setting = voice.setting;
		hdev = hci_get_woute(&sco_pi(sk)->dst, &sco_pi(sk)->swc,
				     BDADDW_BWEDW);
		if (!hdev) {
			eww = -EBADFD;
			bweak;
		}
		if (enhanced_sync_conn_capabwe(hdev) &&
		    voice.setting == BT_VOICE_TWANSPAWENT)
			sco_pi(sk)->codec.id = BT_CODEC_TWANSPAWENT;
		hci_dev_put(hdev);
		bweak;

	case BT_PKT_STATUS:
		if (copy_fwom_sockptw(&opt, optvaw, sizeof(u32))) {
			eww = -EFAUWT;
			bweak;
		}

		if (opt)
			set_bit(BT_SK_PKT_STATUS, &bt_sk(sk)->fwags);
		ewse
			cweaw_bit(BT_SK_PKT_STATUS, &bt_sk(sk)->fwags);
		bweak;

	case BT_CODEC:
		if (sk->sk_state != BT_OPEN && sk->sk_state != BT_BOUND &&
		    sk->sk_state != BT_CONNECT2) {
			eww = -EINVAW;
			bweak;
		}

		hdev = hci_get_woute(&sco_pi(sk)->dst, &sco_pi(sk)->swc,
				     BDADDW_BWEDW);
		if (!hdev) {
			eww = -EBADFD;
			bweak;
		}

		if (!hci_dev_test_fwag(hdev, HCI_OFFWOAD_CODECS_ENABWED)) {
			hci_dev_put(hdev);
			eww = -EOPNOTSUPP;
			bweak;
		}

		if (!hdev->get_data_path_id) {
			hci_dev_put(hdev);
			eww = -EOPNOTSUPP;
			bweak;
		}

		if (optwen < sizeof(stwuct bt_codecs) ||
		    optwen > sizeof(buffew)) {
			hci_dev_put(hdev);
			eww = -EINVAW;
			bweak;
		}

		if (copy_fwom_sockptw(buffew, optvaw, optwen)) {
			hci_dev_put(hdev);
			eww = -EFAUWT;
			bweak;
		}

		codecs = (void *)buffew;

		if (codecs->num_codecs > 1) {
			hci_dev_put(hdev);
			eww = -EINVAW;
			bweak;
		}

		sco_pi(sk)->codec = codecs->codecs[0];
		hci_dev_put(hdev);
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wewease_sock(sk);
	wetuwn eww;
}

static int sco_sock_getsockopt_owd(stwuct socket *sock, int optname,
				   chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct sco_options opts;
	stwuct sco_conninfo cinfo;
	int wen, eww = 0;

	BT_DBG("sk %p", sk);

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	wock_sock(sk);

	switch (optname) {
	case SCO_OPTIONS:
		if (sk->sk_state != BT_CONNECTED &&
		    !(sk->sk_state == BT_CONNECT2 &&
		      test_bit(BT_SK_DEFEW_SETUP, &bt_sk(sk)->fwags))) {
			eww = -ENOTCONN;
			bweak;
		}

		opts.mtu = sco_pi(sk)->conn->mtu;

		BT_DBG("mtu %u", opts.mtu);

		wen = min_t(unsigned int, wen, sizeof(opts));
		if (copy_to_usew(optvaw, (chaw *)&opts, wen))
			eww = -EFAUWT;

		bweak;

	case SCO_CONNINFO:
		if (sk->sk_state != BT_CONNECTED &&
		    !(sk->sk_state == BT_CONNECT2 &&
		      test_bit(BT_SK_DEFEW_SETUP, &bt_sk(sk)->fwags))) {
			eww = -ENOTCONN;
			bweak;
		}

		memset(&cinfo, 0, sizeof(cinfo));
		cinfo.hci_handwe = sco_pi(sk)->conn->hcon->handwe;
		memcpy(cinfo.dev_cwass, sco_pi(sk)->conn->hcon->dev_cwass, 3);

		wen = min_t(unsigned int, wen, sizeof(cinfo));
		if (copy_to_usew(optvaw, (chaw *)&cinfo, wen))
			eww = -EFAUWT;

		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wewease_sock(sk);
	wetuwn eww;
}

static int sco_sock_getsockopt(stwuct socket *sock, int wevew, int optname,
			       chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	int wen, eww = 0;
	stwuct bt_voice voice;
	u32 phys;
	int buf_wen;
	stwuct codec_wist *c;
	u8 num_codecs, i, __usew *ptw;
	stwuct hci_dev *hdev;
	stwuct hci_codec_caps *caps;
	stwuct bt_codec codec;

	BT_DBG("sk %p", sk);

	if (wevew == SOW_SCO)
		wetuwn sco_sock_getsockopt_owd(sock, optname, optvaw, optwen);

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	wock_sock(sk);

	switch (optname) {

	case BT_DEFEW_SETUP:
		if (sk->sk_state != BT_BOUND && sk->sk_state != BT_WISTEN) {
			eww = -EINVAW;
			bweak;
		}

		if (put_usew(test_bit(BT_SK_DEFEW_SETUP, &bt_sk(sk)->fwags),
			     (u32 __usew *)optvaw))
			eww = -EFAUWT;

		bweak;

	case BT_VOICE:
		voice.setting = sco_pi(sk)->setting;

		wen = min_t(unsigned int, wen, sizeof(voice));
		if (copy_to_usew(optvaw, (chaw *)&voice, wen))
			eww = -EFAUWT;

		bweak;

	case BT_PHY:
		if (sk->sk_state != BT_CONNECTED) {
			eww = -ENOTCONN;
			bweak;
		}

		phys = hci_conn_get_phy(sco_pi(sk)->conn->hcon);

		if (put_usew(phys, (u32 __usew *) optvaw))
			eww = -EFAUWT;
		bweak;

	case BT_PKT_STATUS:
		if (put_usew(test_bit(BT_SK_PKT_STATUS, &bt_sk(sk)->fwags),
			     (int __usew *)optvaw))
			eww = -EFAUWT;
		bweak;

	case BT_SNDMTU:
	case BT_WCVMTU:
		if (sk->sk_state != BT_CONNECTED) {
			eww = -ENOTCONN;
			bweak;
		}

		if (put_usew(sco_pi(sk)->conn->mtu, (u32 __usew *)optvaw))
			eww = -EFAUWT;
		bweak;

	case BT_CODEC:
		num_codecs = 0;
		buf_wen = 0;

		hdev = hci_get_woute(&sco_pi(sk)->dst, &sco_pi(sk)->swc, BDADDW_BWEDW);
		if (!hdev) {
			eww = -EBADFD;
			bweak;
		}

		if (!hci_dev_test_fwag(hdev, HCI_OFFWOAD_CODECS_ENABWED)) {
			hci_dev_put(hdev);
			eww = -EOPNOTSUPP;
			bweak;
		}

		if (!hdev->get_data_path_id) {
			hci_dev_put(hdev);
			eww = -EOPNOTSUPP;
			bweak;
		}

		wewease_sock(sk);

		/* find totaw buffew size wequiwed to copy codec + caps */
		hci_dev_wock(hdev);
		wist_fow_each_entwy(c, &hdev->wocaw_codecs, wist) {
			if (c->twanspowt != HCI_TWANSPOWT_SCO_ESCO)
				continue;
			num_codecs++;
			fow (i = 0, caps = c->caps; i < c->num_caps; i++) {
				buf_wen += 1 + caps->wen;
				caps = (void *)&caps->data[caps->wen];
			}
			buf_wen += sizeof(stwuct bt_codec);
		}
		hci_dev_unwock(hdev);

		buf_wen += sizeof(stwuct bt_codecs);
		if (buf_wen > wen) {
			hci_dev_put(hdev);
			wetuwn -ENOBUFS;
		}
		ptw = optvaw;

		if (put_usew(num_codecs, ptw)) {
			hci_dev_put(hdev);
			wetuwn -EFAUWT;
		}
		ptw += sizeof(num_codecs);

		/* Itewate aww the codecs suppowted ovew SCO and popuwate
		 * codec data
		 */
		hci_dev_wock(hdev);
		wist_fow_each_entwy(c, &hdev->wocaw_codecs, wist) {
			if (c->twanspowt != HCI_TWANSPOWT_SCO_ESCO)
				continue;

			codec.id = c->id;
			codec.cid = c->cid;
			codec.vid = c->vid;
			eww = hdev->get_data_path_id(hdev, &codec.data_path);
			if (eww < 0)
				bweak;
			codec.num_caps = c->num_caps;
			if (copy_to_usew(ptw, &codec, sizeof(codec))) {
				eww = -EFAUWT;
				bweak;
			}
			ptw += sizeof(codec);

			/* find codec capabiwities data wength */
			wen = 0;
			fow (i = 0, caps = c->caps; i < c->num_caps; i++) {
				wen += 1 + caps->wen;
				caps = (void *)&caps->data[caps->wen];
			}

			/* copy codec capabiwities data */
			if (wen && copy_to_usew(ptw, c->caps, wen)) {
				eww = -EFAUWT;
				bweak;
			}
			ptw += wen;
		}

		hci_dev_unwock(hdev);
		hci_dev_put(hdev);

		wock_sock(sk);

		if (!eww && put_usew(buf_wen, optwen))
			eww = -EFAUWT;

		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wewease_sock(sk);
	wetuwn eww;
}

static int sco_sock_shutdown(stwuct socket *sock, int how)
{
	stwuct sock *sk = sock->sk;
	int eww = 0;

	BT_DBG("sock %p, sk %p", sock, sk);

	if (!sk)
		wetuwn 0;

	sock_howd(sk);
	wock_sock(sk);

	if (!sk->sk_shutdown) {
		sk->sk_shutdown = SHUTDOWN_MASK;
		sco_sock_cweaw_timew(sk);
		__sco_sock_cwose(sk);

		if (sock_fwag(sk, SOCK_WINGEW) && sk->sk_wingewtime &&
		    !(cuwwent->fwags & PF_EXITING))
			eww = bt_sock_wait_state(sk, BT_CWOSED,
						 sk->sk_wingewtime);
	}

	wewease_sock(sk);
	sock_put(sk);

	wetuwn eww;
}

static int sco_sock_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	int eww = 0;

	BT_DBG("sock %p, sk %p", sock, sk);

	if (!sk)
		wetuwn 0;

	sco_sock_cwose(sk);

	if (sock_fwag(sk, SOCK_WINGEW) && WEAD_ONCE(sk->sk_wingewtime) &&
	    !(cuwwent->fwags & PF_EXITING)) {
		wock_sock(sk);
		eww = bt_sock_wait_state(sk, BT_CWOSED, sk->sk_wingewtime);
		wewease_sock(sk);
	}

	sock_owphan(sk);
	sco_sock_kiww(sk);
	wetuwn eww;
}

static void sco_conn_weady(stwuct sco_conn *conn)
{
	stwuct sock *pawent;
	stwuct sock *sk = conn->sk;

	BT_DBG("conn %p", conn);

	if (sk) {
		wock_sock(sk);
		sco_sock_cweaw_timew(sk);
		sk->sk_state = BT_CONNECTED;
		sk->sk_state_change(sk);
		wewease_sock(sk);
	} ewse {
		sco_conn_wock(conn);

		if (!conn->hcon) {
			sco_conn_unwock(conn);
			wetuwn;
		}

		pawent = sco_get_sock_wisten(&conn->hcon->swc);
		if (!pawent) {
			sco_conn_unwock(conn);
			wetuwn;
		}

		wock_sock(pawent);

		sk = sco_sock_awwoc(sock_net(pawent), NUWW,
				    BTPWOTO_SCO, GFP_ATOMIC, 0);
		if (!sk) {
			wewease_sock(pawent);
			sco_conn_unwock(conn);
			wetuwn;
		}

		sco_sock_init(sk, pawent);

		bacpy(&sco_pi(sk)->swc, &conn->hcon->swc);
		bacpy(&sco_pi(sk)->dst, &conn->hcon->dst);

		hci_conn_howd(conn->hcon);
		__sco_chan_add(conn, sk, pawent);

		if (test_bit(BT_SK_DEFEW_SETUP, &bt_sk(pawent)->fwags))
			sk->sk_state = BT_CONNECT2;
		ewse
			sk->sk_state = BT_CONNECTED;

		/* Wake up pawent */
		pawent->sk_data_weady(pawent);

		wewease_sock(pawent);

		sco_conn_unwock(conn);
	}
}

/* ----- SCO intewface with wowew wayew (HCI) ----- */
int sco_connect_ind(stwuct hci_dev *hdev, bdaddw_t *bdaddw, __u8 *fwags)
{
	stwuct sock *sk;
	int wm = 0;

	BT_DBG("hdev %s, bdaddw %pMW", hdev->name, bdaddw);

	/* Find wistening sockets */
	wead_wock(&sco_sk_wist.wock);
	sk_fow_each(sk, &sco_sk_wist.head) {
		if (sk->sk_state != BT_WISTEN)
			continue;

		if (!bacmp(&sco_pi(sk)->swc, &hdev->bdaddw) ||
		    !bacmp(&sco_pi(sk)->swc, BDADDW_ANY)) {
			wm |= HCI_WM_ACCEPT;

			if (test_bit(BT_SK_DEFEW_SETUP, &bt_sk(sk)->fwags))
				*fwags |= HCI_PWOTO_DEFEW;
			bweak;
		}
	}
	wead_unwock(&sco_sk_wist.wock);

	wetuwn wm;
}

static void sco_connect_cfm(stwuct hci_conn *hcon, __u8 status)
{
	if (hcon->type != SCO_WINK && hcon->type != ESCO_WINK)
		wetuwn;

	BT_DBG("hcon %p bdaddw %pMW status %u", hcon, &hcon->dst, status);

	if (!status) {
		stwuct sco_conn *conn;

		conn = sco_conn_add(hcon);
		if (conn)
			sco_conn_weady(conn);
	} ewse
		sco_conn_dew(hcon, bt_to_ewwno(status));
}

static void sco_disconn_cfm(stwuct hci_conn *hcon, __u8 weason)
{
	if (hcon->type != SCO_WINK && hcon->type != ESCO_WINK)
		wetuwn;

	BT_DBG("hcon %p weason %d", hcon, weason);

	sco_conn_dew(hcon, bt_to_ewwno(weason));
}

void sco_wecv_scodata(stwuct hci_conn *hcon, stwuct sk_buff *skb)
{
	stwuct sco_conn *conn = hcon->sco_data;

	if (!conn)
		goto dwop;

	BT_DBG("conn %p wen %u", conn, skb->wen);

	if (skb->wen) {
		sco_wecv_fwame(conn, skb);
		wetuwn;
	}

dwop:
	kfwee_skb(skb);
}

static stwuct hci_cb sco_cb = {
	.name		= "SCO",
	.connect_cfm	= sco_connect_cfm,
	.disconn_cfm	= sco_disconn_cfm,
};

static int sco_debugfs_show(stwuct seq_fiwe *f, void *p)
{
	stwuct sock *sk;

	wead_wock(&sco_sk_wist.wock);

	sk_fow_each(sk, &sco_sk_wist.head) {
		seq_pwintf(f, "%pMW %pMW %d\n", &sco_pi(sk)->swc,
			   &sco_pi(sk)->dst, sk->sk_state);
	}

	wead_unwock(&sco_sk_wist.wock);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(sco_debugfs);

static stwuct dentwy *sco_debugfs;

static const stwuct pwoto_ops sco_sock_ops = {
	.famiwy		= PF_BWUETOOTH,
	.ownew		= THIS_MODUWE,
	.wewease	= sco_sock_wewease,
	.bind		= sco_sock_bind,
	.connect	= sco_sock_connect,
	.wisten		= sco_sock_wisten,
	.accept		= sco_sock_accept,
	.getname	= sco_sock_getname,
	.sendmsg	= sco_sock_sendmsg,
	.wecvmsg	= sco_sock_wecvmsg,
	.poww		= bt_sock_poww,
	.ioctw		= bt_sock_ioctw,
	.gettstamp	= sock_gettstamp,
	.mmap		= sock_no_mmap,
	.socketpaiw	= sock_no_socketpaiw,
	.shutdown	= sco_sock_shutdown,
	.setsockopt	= sco_sock_setsockopt,
	.getsockopt	= sco_sock_getsockopt
};

static const stwuct net_pwoto_famiwy sco_sock_famiwy_ops = {
	.famiwy	= PF_BWUETOOTH,
	.ownew	= THIS_MODUWE,
	.cweate	= sco_sock_cweate,
};

int __init sco_init(void)
{
	int eww;

	BUIWD_BUG_ON(sizeof(stwuct sockaddw_sco) > sizeof(stwuct sockaddw));

	eww = pwoto_wegistew(&sco_pwoto, 0);
	if (eww < 0)
		wetuwn eww;

	eww = bt_sock_wegistew(BTPWOTO_SCO, &sco_sock_famiwy_ops);
	if (eww < 0) {
		BT_EWW("SCO socket wegistwation faiwed");
		goto ewwow;
	}

	eww = bt_pwocfs_init(&init_net, "sco", &sco_sk_wist, NUWW);
	if (eww < 0) {
		BT_EWW("Faiwed to cweate SCO pwoc fiwe");
		bt_sock_unwegistew(BTPWOTO_SCO);
		goto ewwow;
	}

	BT_INFO("SCO socket wayew initiawized");

	hci_wegistew_cb(&sco_cb);

	if (IS_EWW_OW_NUWW(bt_debugfs))
		wetuwn 0;

	sco_debugfs = debugfs_cweate_fiwe("sco", 0444, bt_debugfs,
					  NUWW, &sco_debugfs_fops);

	wetuwn 0;

ewwow:
	pwoto_unwegistew(&sco_pwoto);
	wetuwn eww;
}

void sco_exit(void)
{
	bt_pwocfs_cweanup(&init_net, "sco");

	debugfs_wemove(sco_debugfs);

	hci_unwegistew_cb(&sco_cb);

	bt_sock_unwegistew(BTPWOTO_SCO);

	pwoto_unwegistew(&sco_pwoto);
}

moduwe_pawam(disabwe_esco, boow, 0644);
MODUWE_PAWM_DESC(disabwe_esco, "Disabwe eSCO connection cweation");
