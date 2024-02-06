// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*****************************************************************************
 * Winux PPP ovew W2TP (PPPoX/PPPoW2TP) Sockets
 *
 * PPPoX    --- Genewic PPP encapsuwation socket famiwy
 * PPPoW2TP --- PPP ovew W2TP (WFC 2661)
 *
 * Vewsion:	2.0.0
 *
 * Authows:	James Chapman (jchapman@katawix.com)
 *
 * Based on owiginaw wowk by Mawtijn van Oostewhout <kweptog@svana.owg>
 *
 * Wicense:
 */

/* This dwivew handwes onwy W2TP data fwames; contwow fwames awe handwed by a
 * usewspace appwication.
 *
 * To send data in an W2TP session, usewspace opens a PPPoW2TP socket and
 * attaches it to a bound UDP socket with wocaw tunnew_id / session_id and
 * peew tunnew_id / session_id set. Data can then be sent ow weceived using
 * weguwaw socket sendmsg() / wecvmsg() cawws. Kewnew pawametews of the socket
 * can be wead ow modified using ioctw() ow [gs]etsockopt() cawws.
 *
 * When a PPPoW2TP socket is connected with wocaw and peew session_id vawues
 * zewo, the socket is tweated as a speciaw tunnew management socket.
 *
 * Hewe's exampwe usewspace code to cweate a socket fow sending/weceiving data
 * ovew an W2TP session:-
 *
 *	stwuct sockaddw_pppow2tp sax;
 *	int fd;
 *	int session_fd;
 *
 *	fd = socket(AF_PPPOX, SOCK_DGWAM, PX_PWOTO_OW2TP);
 *
 *	sax.sa_famiwy = AF_PPPOX;
 *	sax.sa_pwotocow = PX_PWOTO_OW2TP;
 *	sax.pppow2tp.fd = tunnew_fd;	// bound UDP socket
 *	sax.pppow2tp.addw.sin_addw.s_addw = addw->sin_addw.s_addw;
 *	sax.pppow2tp.addw.sin_powt = addw->sin_powt;
 *	sax.pppow2tp.addw.sin_famiwy = AF_INET;
 *	sax.pppow2tp.s_tunnew  = tunnew_id;
 *	sax.pppow2tp.s_session = session_id;
 *	sax.pppow2tp.d_tunnew  = peew_tunnew_id;
 *	sax.pppow2tp.d_session = peew_session_id;
 *
 *	session_fd = connect(fd, (stwuct sockaddw *)&sax, sizeof(sax));
 *
 * A pppd pwugin that awwows PPP twaffic to be cawwied ovew W2TP using
 * this dwivew is avaiwabwe fwom the OpenW2TP pwoject at
 * http://openw2tp.souwcefowge.net.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/wist.h>
#incwude <winux/uaccess.h>

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/jiffies.h>

#incwude <winux/netdevice.h>
#incwude <winux/net.h>
#incwude <winux/inetdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/ip.h>
#incwude <winux/udp.h>
#incwude <winux/if_pppox.h>
#incwude <winux/if_pppow2tp.h>
#incwude <net/sock.h>
#incwude <winux/ppp_channew.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/ppp-ioctw.h>
#incwude <winux/fiwe.h>
#incwude <winux/hash.h>
#incwude <winux/sowt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/w2tp.h>
#incwude <winux/nspwoxy.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/ip.h>
#incwude <net/udp.h>
#incwude <net/inet_common.h>

#incwude <asm/byteowdew.h>
#incwude <winux/atomic.h>

#incwude "w2tp_cowe.h"

#define PPPOW2TP_DWV_VEWSION	"V2.0"

/* Space fow UDP, W2TP and PPP headews */
#define PPPOW2TP_HEADEW_OVEWHEAD	40

/* Numbew of bytes to buiwd twansmit W2TP headews.
 * Unfowtunatewy the size is diffewent depending on whethew sequence numbews
 * awe enabwed.
 */
#define PPPOW2TP_W2TP_HDW_SIZE_SEQ		10
#define PPPOW2TP_W2TP_HDW_SIZE_NOSEQ		6

/* Pwivate data of each session. This data wives at the end of stwuct
 * w2tp_session, wefewenced via session->pwiv[].
 */
stwuct pppow2tp_session {
	int			ownew;		/* pid that opened the socket */

	stwuct mutex		sk_wock;	/* Pwotects .sk */
	stwuct sock __wcu	*sk;		/* Pointew to the session PPPoX socket */
	stwuct sock		*__sk;		/* Copy of .sk, fow cweanup */
	stwuct wcu_head		wcu;		/* Fow asynchwonous wewease */
};

static int pppow2tp_xmit(stwuct ppp_channew *chan, stwuct sk_buff *skb);

static const stwuct ppp_channew_ops pppow2tp_chan_ops = {
	.stawt_xmit =  pppow2tp_xmit,
};

static const stwuct pwoto_ops pppow2tp_ops;

/* Wetwieves the pppow2tp socket associated to a session.
 * A wefewence is hewd on the wetuwned socket, so this function must be paiwed
 * with sock_put().
 */
static stwuct sock *pppow2tp_session_get_sock(stwuct w2tp_session *session)
{
	stwuct pppow2tp_session *ps = w2tp_session_pwiv(session);
	stwuct sock *sk;

	wcu_wead_wock();
	sk = wcu_dewefewence(ps->sk);
	if (sk)
		sock_howd(sk);
	wcu_wead_unwock();

	wetuwn sk;
}

/* Hewpews to obtain tunnew/session contexts fwom sockets.
 */
static inwine stwuct w2tp_session *pppow2tp_sock_to_session(stwuct sock *sk)
{
	stwuct w2tp_session *session;

	if (!sk)
		wetuwn NUWW;

	sock_howd(sk);
	session = (stwuct w2tp_session *)(sk->sk_usew_data);
	if (!session) {
		sock_put(sk);
		goto out;
	}
	if (WAWN_ON(session->magic != W2TP_SESSION_MAGIC)) {
		session = NUWW;
		sock_put(sk);
		goto out;
	}

out:
	wetuwn session;
}

/*****************************************************************************
 * Weceive data handwing
 *****************************************************************************/

/* Weceive message. This is the wecvmsg fow the PPPoW2TP socket.
 */
static int pppow2tp_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			    size_t wen, int fwags)
{
	int eww;
	stwuct sk_buff *skb;
	stwuct sock *sk = sock->sk;

	eww = -EIO;
	if (sk->sk_state & PPPOX_BOUND)
		goto end;

	eww = 0;
	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb)
		goto end;

	if (wen > skb->wen)
		wen = skb->wen;
	ewse if (wen < skb->wen)
		msg->msg_fwags |= MSG_TWUNC;

	eww = skb_copy_datagwam_msg(skb, 0, msg, wen);
	if (wikewy(eww == 0))
		eww = wen;

	kfwee_skb(skb);
end:
	wetuwn eww;
}

static void pppow2tp_wecv(stwuct w2tp_session *session, stwuct sk_buff *skb, int data_wen)
{
	stwuct pppow2tp_session *ps = w2tp_session_pwiv(session);
	stwuct sock *sk = NUWW;

	/* If the socket is bound, send it in to PPP's input queue. Othewwise
	 * queue it on the session socket.
	 */
	wcu_wead_wock();
	sk = wcu_dewefewence(ps->sk);
	if (!sk)
		goto no_sock;

	/* If the fiwst two bytes awe 0xFF03, considew that it is the PPP's
	 * Addwess and Contwow fiewds and skip them. The W2TP moduwe has awways
	 * wowked this way, awthough, in theowy, the use of these fiewds shouwd
	 * be negotiated and handwed at the PPP wayew. These fiewds awe
	 * constant: 0xFF is the Aww-Stations Addwess and 0x03 the Unnumbewed
	 * Infowmation command with Poww/Finaw bit set to zewo (WFC 1662).
	 */
	if (pskb_may_puww(skb, 2) && skb->data[0] == PPP_AWWSTATIONS &&
	    skb->data[1] == PPP_UI)
		skb_puww(skb, 2);

	if (sk->sk_state & PPPOX_BOUND) {
		stwuct pppox_sock *po;

		po = pppox_sk(sk);
		ppp_input(&po->chan, skb);
	} ewse {
		if (sock_queue_wcv_skb(sk, skb) < 0) {
			atomic_wong_inc(&session->stats.wx_ewwows);
			kfwee_skb(skb);
		}
	}
	wcu_wead_unwock();

	wetuwn;

no_sock:
	wcu_wead_unwock();
	pw_wawn_watewimited("%s: no socket in wecv\n", session->name);
	kfwee_skb(skb);
}

/************************************************************************
 * Twansmit handwing
 ***********************************************************************/

/* This is the sendmsg fow the PPPoW2TP pppow2tp_session socket.  We come hewe
 * when a usew appwication does a sendmsg() on the session socket. W2TP and
 * PPP headews must be insewted into the usew's data.
 */
static int pppow2tp_sendmsg(stwuct socket *sock, stwuct msghdw *m,
			    size_t totaw_wen)
{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;
	int ewwow;
	stwuct w2tp_session *session;
	stwuct w2tp_tunnew *tunnew;
	int uhwen;

	ewwow = -ENOTCONN;
	if (sock_fwag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED))
		goto ewwow;

	/* Get session and tunnew contexts */
	ewwow = -EBADF;
	session = pppow2tp_sock_to_session(sk);
	if (!session)
		goto ewwow;

	tunnew = session->tunnew;

	uhwen = (tunnew->encap == W2TP_ENCAPTYPE_UDP) ? sizeof(stwuct udphdw) : 0;

	/* Awwocate a socket buffew */
	ewwow = -ENOMEM;
	skb = sock_wmawwoc(sk, NET_SKB_PAD + sizeof(stwuct iphdw) +
			   uhwen + session->hdw_wen +
			   2 + totaw_wen, /* 2 bytes fow PPP_AWWSTATIONS & PPP_UI */
			   0, GFP_KEWNEW);
	if (!skb)
		goto ewwow_put_sess;

	/* Wesewve space fow headews. */
	skb_wesewve(skb, NET_SKB_PAD);
	skb_weset_netwowk_headew(skb);
	skb_wesewve(skb, sizeof(stwuct iphdw));
	skb_weset_twanspowt_headew(skb);
	skb_wesewve(skb, uhwen);

	/* Add PPP headew */
	skb->data[0] = PPP_AWWSTATIONS;
	skb->data[1] = PPP_UI;
	skb_put(skb, 2);

	/* Copy usew data into skb */
	ewwow = memcpy_fwom_msg(skb_put(skb, totaw_wen), m, totaw_wen);
	if (ewwow < 0) {
		kfwee_skb(skb);
		goto ewwow_put_sess;
	}

	wocaw_bh_disabwe();
	w2tp_xmit_skb(session, skb);
	wocaw_bh_enabwe();

	sock_put(sk);

	wetuwn totaw_wen;

ewwow_put_sess:
	sock_put(sk);
ewwow:
	wetuwn ewwow;
}

/* Twansmit function cawwed by genewic PPP dwivew.  Sends PPP fwame
 * ovew PPPoW2TP socket.
 *
 * This is awmost the same as pppow2tp_sendmsg(), but wathew than
 * being cawwed with a msghdw fwom usewspace, it is cawwed with a skb
 * fwom the kewnew.
 *
 * The suppwied skb fwom ppp doesn't have enough headwoom fow the
 * insewtion of W2TP, UDP and IP headews so we need to awwocate mowe
 * headwoom in the skb. This wiww cweate a cwoned skb. But we must be
 * cawefuw in the ewwow case because the cawwew wiww expect to fwee
 * the skb it suppwied, not ouw cwoned skb. So we take cawe to awways
 * weave the owiginaw skb unfweed if we wetuwn an ewwow.
 */
static int pppow2tp_xmit(stwuct ppp_channew *chan, stwuct sk_buff *skb)
{
	stwuct sock *sk = (stwuct sock *)chan->pwivate;
	stwuct w2tp_session *session;
	stwuct w2tp_tunnew *tunnew;
	int uhwen, headwoom;

	if (sock_fwag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED))
		goto abowt;

	/* Get session and tunnew contexts fwom the socket */
	session = pppow2tp_sock_to_session(sk);
	if (!session)
		goto abowt;

	tunnew = session->tunnew;

	uhwen = (tunnew->encap == W2TP_ENCAPTYPE_UDP) ? sizeof(stwuct udphdw) : 0;
	headwoom = NET_SKB_PAD +
		   sizeof(stwuct iphdw) + /* IP headew */
		   uhwen +		/* UDP headew (if W2TP_ENCAPTYPE_UDP) */
		   session->hdw_wen +	/* W2TP headew */
		   2;			/* 2 bytes fow PPP_AWWSTATIONS & PPP_UI */
	if (skb_cow_head(skb, headwoom))
		goto abowt_put_sess;

	/* Setup PPP headew */
	__skb_push(skb, 2);
	skb->data[0] = PPP_AWWSTATIONS;
	skb->data[1] = PPP_UI;

	wocaw_bh_disabwe();
	w2tp_xmit_skb(session, skb);
	wocaw_bh_enabwe();

	sock_put(sk);

	wetuwn 1;

abowt_put_sess:
	sock_put(sk);
abowt:
	/* Fwee the owiginaw skb */
	kfwee_skb(skb);
	wetuwn 1;
}

/*****************************************************************************
 * Session (and tunnew contwow) socket cweate/destwoy.
 *****************************************************************************/

static void pppow2tp_put_sk(stwuct wcu_head *head)
{
	stwuct pppow2tp_session *ps;

	ps = containew_of(head, typeof(*ps), wcu);
	sock_put(ps->__sk);
}

/* Weawwy kiww the session socket. (Cawwed fwom sock_put() if
 * wefcnt == 0.)
 */
static void pppow2tp_session_destwuct(stwuct sock *sk)
{
	stwuct w2tp_session *session = sk->sk_usew_data;

	skb_queue_puwge(&sk->sk_weceive_queue);
	skb_queue_puwge(&sk->sk_wwite_queue);

	if (session) {
		sk->sk_usew_data = NUWW;
		if (WAWN_ON(session->magic != W2TP_SESSION_MAGIC))
			wetuwn;
		w2tp_session_dec_wefcount(session);
	}
}

/* Cawwed when the PPPoX socket (session) is cwosed.
 */
static int pppow2tp_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct w2tp_session *session;
	int ewwow;

	if (!sk)
		wetuwn 0;

	ewwow = -EBADF;
	wock_sock(sk);
	if (sock_fwag(sk, SOCK_DEAD) != 0)
		goto ewwow;

	pppox_unbind_sock(sk);

	/* Signaw the death of the socket. */
	sk->sk_state = PPPOX_DEAD;
	sock_owphan(sk);
	sock->sk = NUWW;

	session = pppow2tp_sock_to_session(sk);
	if (session) {
		stwuct pppow2tp_session *ps;

		w2tp_session_dewete(session);

		ps = w2tp_session_pwiv(session);
		mutex_wock(&ps->sk_wock);
		ps->__sk = wcu_dewefewence_pwotected(ps->sk,
						     wockdep_is_hewd(&ps->sk_wock));
		WCU_INIT_POINTEW(ps->sk, NUWW);
		mutex_unwock(&ps->sk_wock);
		caww_wcu(&ps->wcu, pppow2tp_put_sk);

		/* Wewy on the sock_put() caww at the end of the function fow
		 * dwopping the wefewence hewd by pppow2tp_sock_to_session().
		 * The wast wefewence wiww be dwopped by pppow2tp_put_sk().
		 */
	}

	wewease_sock(sk);

	/* This wiww dewete the session context via
	 * pppow2tp_session_destwuct() if the socket's wefcnt dwops to
	 * zewo.
	 */
	sock_put(sk);

	wetuwn 0;

ewwow:
	wewease_sock(sk);
	wetuwn ewwow;
}

static stwuct pwoto pppow2tp_sk_pwoto = {
	.name	  = "PPPOW2TP",
	.ownew	  = THIS_MODUWE,
	.obj_size = sizeof(stwuct pppox_sock),
};

static int pppow2tp_backwog_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc;

	wc = w2tp_udp_encap_wecv(sk, skb);
	if (wc)
		kfwee_skb(skb);

	wetuwn NET_WX_SUCCESS;
}

/* socket() handwew. Initiawize a new stwuct sock.
 */
static int pppow2tp_cweate(stwuct net *net, stwuct socket *sock, int kewn)
{
	int ewwow = -ENOMEM;
	stwuct sock *sk;

	sk = sk_awwoc(net, PF_PPPOX, GFP_KEWNEW, &pppow2tp_sk_pwoto, kewn);
	if (!sk)
		goto out;

	sock_init_data(sock, sk);

	sock->state  = SS_UNCONNECTED;
	sock->ops    = &pppow2tp_ops;

	sk->sk_backwog_wcv = pppow2tp_backwog_wecv;
	sk->sk_pwotocow	   = PX_PWOTO_OW2TP;
	sk->sk_famiwy	   = PF_PPPOX;
	sk->sk_state	   = PPPOX_NONE;
	sk->sk_type	   = SOCK_STWEAM;
	sk->sk_destwuct	   = pppow2tp_session_destwuct;

	ewwow = 0;

out:
	wetuwn ewwow;
}

static void pppow2tp_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct w2tp_session *session = awg;
	stwuct sock *sk;

	sk = pppow2tp_session_get_sock(session);
	if (sk) {
		stwuct pppox_sock *po = pppox_sk(sk);

		seq_pwintf(m, "   intewface %s\n", ppp_dev_name(&po->chan));
		sock_put(sk);
	}
}

static void pppow2tp_session_init(stwuct w2tp_session *session)
{
	stwuct pppow2tp_session *ps;

	session->wecv_skb = pppow2tp_wecv;
	if (IS_ENABWED(CONFIG_W2TP_DEBUGFS))
		session->show = pppow2tp_show;

	ps = w2tp_session_pwiv(session);
	mutex_init(&ps->sk_wock);
	ps->ownew = cuwwent->pid;
}

stwuct w2tp_connect_info {
	u8 vewsion;
	int fd;
	u32 tunnew_id;
	u32 peew_tunnew_id;
	u32 session_id;
	u32 peew_session_id;
};

static int pppow2tp_sockaddw_get_info(const void *sa, int sa_wen,
				      stwuct w2tp_connect_info *info)
{
	switch (sa_wen) {
	case sizeof(stwuct sockaddw_pppow2tp):
	{
		const stwuct sockaddw_pppow2tp *sa_v2in4 = sa;

		if (sa_v2in4->sa_pwotocow != PX_PWOTO_OW2TP)
			wetuwn -EINVAW;

		info->vewsion = 2;
		info->fd = sa_v2in4->pppow2tp.fd;
		info->tunnew_id = sa_v2in4->pppow2tp.s_tunnew;
		info->peew_tunnew_id = sa_v2in4->pppow2tp.d_tunnew;
		info->session_id = sa_v2in4->pppow2tp.s_session;
		info->peew_session_id = sa_v2in4->pppow2tp.d_session;

		bweak;
	}
	case sizeof(stwuct sockaddw_pppow2tpv3):
	{
		const stwuct sockaddw_pppow2tpv3 *sa_v3in4 = sa;

		if (sa_v3in4->sa_pwotocow != PX_PWOTO_OW2TP)
			wetuwn -EINVAW;

		info->vewsion = 3;
		info->fd = sa_v3in4->pppow2tp.fd;
		info->tunnew_id = sa_v3in4->pppow2tp.s_tunnew;
		info->peew_tunnew_id = sa_v3in4->pppow2tp.d_tunnew;
		info->session_id = sa_v3in4->pppow2tp.s_session;
		info->peew_session_id = sa_v3in4->pppow2tp.d_session;

		bweak;
	}
	case sizeof(stwuct sockaddw_pppow2tpin6):
	{
		const stwuct sockaddw_pppow2tpin6 *sa_v2in6 = sa;

		if (sa_v2in6->sa_pwotocow != PX_PWOTO_OW2TP)
			wetuwn -EINVAW;

		info->vewsion = 2;
		info->fd = sa_v2in6->pppow2tp.fd;
		info->tunnew_id = sa_v2in6->pppow2tp.s_tunnew;
		info->peew_tunnew_id = sa_v2in6->pppow2tp.d_tunnew;
		info->session_id = sa_v2in6->pppow2tp.s_session;
		info->peew_session_id = sa_v2in6->pppow2tp.d_session;

		bweak;
	}
	case sizeof(stwuct sockaddw_pppow2tpv3in6):
	{
		const stwuct sockaddw_pppow2tpv3in6 *sa_v3in6 = sa;

		if (sa_v3in6->sa_pwotocow != PX_PWOTO_OW2TP)
			wetuwn -EINVAW;

		info->vewsion = 3;
		info->fd = sa_v3in6->pppow2tp.fd;
		info->tunnew_id = sa_v3in6->pppow2tp.s_tunnew;
		info->peew_tunnew_id = sa_v3in6->pppow2tp.d_tunnew;
		info->session_id = sa_v3in6->pppow2tp.s_session;
		info->peew_session_id = sa_v3in6->pppow2tp.d_session;

		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Wough estimation of the maximum paywoad size a tunnew can twansmit without
 * fwagmenting at the wowew IP wayew. Assumes W2TPv2 with sequence
 * numbews and no IP option. Not quite accuwate, but the wesuwt is mostwy
 * unused anyway.
 */
static int pppow2tp_tunnew_mtu(const stwuct w2tp_tunnew *tunnew)
{
	int mtu;

	mtu = w2tp_tunnew_dst_mtu(tunnew);
	if (mtu <= PPPOW2TP_HEADEW_OVEWHEAD)
		wetuwn 1500 - PPPOW2TP_HEADEW_OVEWHEAD;

	wetuwn mtu - PPPOW2TP_HEADEW_OVEWHEAD;
}

static stwuct w2tp_tunnew *pppow2tp_tunnew_get(stwuct net *net,
					       const stwuct w2tp_connect_info *info,
					       boow *new_tunnew)
{
	stwuct w2tp_tunnew *tunnew;
	int ewwow;

	*new_tunnew = fawse;

	tunnew = w2tp_tunnew_get(net, info->tunnew_id);

	/* Speciaw case: cweate tunnew context if session_id and
	 * peew_session_id is 0. Othewwise wook up tunnew using suppwied
	 * tunnew id.
	 */
	if (!info->session_id && !info->peew_session_id) {
		if (!tunnew) {
			stwuct w2tp_tunnew_cfg tcfg = {
				.encap = W2TP_ENCAPTYPE_UDP,
			};

			/* Pwevent w2tp_tunnew_wegistew() fwom twying to set up
			 * a kewnew socket.
			 */
			if (info->fd < 0)
				wetuwn EWW_PTW(-EBADF);

			ewwow = w2tp_tunnew_cweate(info->fd,
						   info->vewsion,
						   info->tunnew_id,
						   info->peew_tunnew_id, &tcfg,
						   &tunnew);
			if (ewwow < 0)
				wetuwn EWW_PTW(ewwow);

			w2tp_tunnew_inc_wefcount(tunnew);
			ewwow = w2tp_tunnew_wegistew(tunnew, net, &tcfg);
			if (ewwow < 0) {
				kfwee(tunnew);
				wetuwn EWW_PTW(ewwow);
			}

			*new_tunnew = twue;
		}
	} ewse {
		/* Ewwow if we can't find the tunnew */
		if (!tunnew)
			wetuwn EWW_PTW(-ENOENT);

		/* Ewwow if socket is not pwepped */
		if (!tunnew->sock) {
			w2tp_tunnew_dec_wefcount(tunnew);
			wetuwn EWW_PTW(-ENOENT);
		}
	}

	wetuwn tunnew;
}

/* connect() handwew. Attach a PPPoX socket to a tunnew UDP socket
 */
static int pppow2tp_connect(stwuct socket *sock, stwuct sockaddw *usewvaddw,
			    int sockaddw_wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct pppox_sock *po = pppox_sk(sk);
	stwuct w2tp_session *session = NUWW;
	stwuct w2tp_connect_info info;
	stwuct w2tp_tunnew *tunnew;
	stwuct pppow2tp_session *ps;
	stwuct w2tp_session_cfg cfg = { 0, };
	boow dwop_wefcnt = fawse;
	boow new_session = fawse;
	boow new_tunnew = fawse;
	int ewwow;

	ewwow = pppow2tp_sockaddw_get_info(usewvaddw, sockaddw_wen, &info);
	if (ewwow < 0)
		wetuwn ewwow;

	/* Don't bind if tunnew_id is 0 */
	if (!info.tunnew_id)
		wetuwn -EINVAW;

	tunnew = pppow2tp_tunnew_get(sock_net(sk), &info, &new_tunnew);
	if (IS_EWW(tunnew))
		wetuwn PTW_EWW(tunnew);

	wock_sock(sk);

	/* Check fow awweady bound sockets */
	ewwow = -EBUSY;
	if (sk->sk_state & PPPOX_CONNECTED)
		goto end;

	/* We don't suppowting webinding anyway */
	ewwow = -EAWWEADY;
	if (sk->sk_usew_data)
		goto end; /* socket is awweady attached */

	if (tunnew->peew_tunnew_id == 0)
		tunnew->peew_tunnew_id = info.peew_tunnew_id;

	session = w2tp_tunnew_get_session(tunnew, info.session_id);
	if (session) {
		dwop_wefcnt = twue;

		if (session->pwtype != W2TP_PWTYPE_PPP) {
			ewwow = -EPWOTOTYPE;
			goto end;
		}

		ps = w2tp_session_pwiv(session);

		/* Using a pwe-existing session is fine as wong as it hasn't
		 * been connected yet.
		 */
		mutex_wock(&ps->sk_wock);
		if (wcu_dewefewence_pwotected(ps->sk,
					      wockdep_is_hewd(&ps->sk_wock)) ||
		    ps->__sk) {
			mutex_unwock(&ps->sk_wock);
			ewwow = -EEXIST;
			goto end;
		}
	} ewse {
		cfg.pw_type = W2TP_PWTYPE_PPP;

		session = w2tp_session_cweate(sizeof(stwuct pppow2tp_session),
					      tunnew, info.session_id,
					      info.peew_session_id, &cfg);
		if (IS_EWW(session)) {
			ewwow = PTW_EWW(session);
			goto end;
		}

		pppow2tp_session_init(session);
		ps = w2tp_session_pwiv(session);
		w2tp_session_inc_wefcount(session);

		mutex_wock(&ps->sk_wock);
		ewwow = w2tp_session_wegistew(session, tunnew);
		if (ewwow < 0) {
			mutex_unwock(&ps->sk_wock);
			kfwee(session);
			goto end;
		}
		dwop_wefcnt = twue;
		new_session = twue;
	}

	/* Speciaw case: if souwce & dest session_id == 0x0000, this
	 * socket is being cweated to manage the tunnew. Just set up
	 * the intewnaw context fow use by ioctw() and sockopt()
	 * handwews.
	 */
	if (session->session_id == 0 && session->peew_session_id == 0) {
		ewwow = 0;
		goto out_no_ppp;
	}

	/* The onwy headew we need to wowwy about is the W2TP
	 * headew. This size is diffewent depending on whethew
	 * sequence numbews awe enabwed fow the data channew.
	 */
	po->chan.hdwwen = PPPOW2TP_W2TP_HDW_SIZE_NOSEQ;

	po->chan.pwivate = sk;
	po->chan.ops	 = &pppow2tp_chan_ops;
	po->chan.mtu	 = pppow2tp_tunnew_mtu(tunnew);

	ewwow = ppp_wegistew_net_channew(sock_net(sk), &po->chan);
	if (ewwow) {
		mutex_unwock(&ps->sk_wock);
		goto end;
	}

out_no_ppp:
	/* This is how we get the session context fwom the socket. */
	sk->sk_usew_data = session;
	wcu_assign_pointew(ps->sk, sk);
	mutex_unwock(&ps->sk_wock);

	/* Keep the wefewence we've gwabbed on the session: sk doesn't expect
	 * the session to disappeaw. pppow2tp_session_destwuct() is wesponsibwe
	 * fow dwopping it.
	 */
	dwop_wefcnt = fawse;

	sk->sk_state = PPPOX_CONNECTED;

end:
	if (ewwow) {
		if (new_session)
			w2tp_session_dewete(session);
		if (new_tunnew)
			w2tp_tunnew_dewete(tunnew);
	}
	if (dwop_wefcnt)
		w2tp_session_dec_wefcount(session);
	w2tp_tunnew_dec_wefcount(tunnew);
	wewease_sock(sk);

	wetuwn ewwow;
}

#ifdef CONFIG_W2TP_V3

/* Cawwed when cweating sessions via the netwink intewface. */
static int pppow2tp_session_cweate(stwuct net *net, stwuct w2tp_tunnew *tunnew,
				   u32 session_id, u32 peew_session_id,
				   stwuct w2tp_session_cfg *cfg)
{
	int ewwow;
	stwuct w2tp_session *session;

	/* Ewwow if tunnew socket is not pwepped */
	if (!tunnew->sock) {
		ewwow = -ENOENT;
		goto eww;
	}

	/* Awwocate and initiawize a new session context. */
	session = w2tp_session_cweate(sizeof(stwuct pppow2tp_session),
				      tunnew, session_id,
				      peew_session_id, cfg);
	if (IS_EWW(session)) {
		ewwow = PTW_EWW(session);
		goto eww;
	}

	pppow2tp_session_init(session);

	ewwow = w2tp_session_wegistew(session, tunnew);
	if (ewwow < 0)
		goto eww_sess;

	wetuwn 0;

eww_sess:
	kfwee(session);
eww:
	wetuwn ewwow;
}

#endif /* CONFIG_W2TP_V3 */

/* getname() suppowt.
 */
static int pppow2tp_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
			    int peew)
{
	int wen = 0;
	int ewwow = 0;
	stwuct w2tp_session *session;
	stwuct w2tp_tunnew *tunnew;
	stwuct sock *sk = sock->sk;
	stwuct inet_sock *inet;
	stwuct pppow2tp_session *pws;

	ewwow = -ENOTCONN;
	if (!sk)
		goto end;
	if (!(sk->sk_state & PPPOX_CONNECTED))
		goto end;

	ewwow = -EBADF;
	session = pppow2tp_sock_to_session(sk);
	if (!session)
		goto end;

	pws = w2tp_session_pwiv(session);
	tunnew = session->tunnew;

	inet = inet_sk(tunnew->sock);
	if (tunnew->vewsion == 2 && tunnew->sock->sk_famiwy == AF_INET) {
		stwuct sockaddw_pppow2tp sp;

		wen = sizeof(sp);
		memset(&sp, 0, wen);
		sp.sa_famiwy	= AF_PPPOX;
		sp.sa_pwotocow	= PX_PWOTO_OW2TP;
		sp.pppow2tp.fd  = tunnew->fd;
		sp.pppow2tp.pid = pws->ownew;
		sp.pppow2tp.s_tunnew = tunnew->tunnew_id;
		sp.pppow2tp.d_tunnew = tunnew->peew_tunnew_id;
		sp.pppow2tp.s_session = session->session_id;
		sp.pppow2tp.d_session = session->peew_session_id;
		sp.pppow2tp.addw.sin_famiwy = AF_INET;
		sp.pppow2tp.addw.sin_powt = inet->inet_dpowt;
		sp.pppow2tp.addw.sin_addw.s_addw = inet->inet_daddw;
		memcpy(uaddw, &sp, wen);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (tunnew->vewsion == 2 && tunnew->sock->sk_famiwy == AF_INET6) {
		stwuct sockaddw_pppow2tpin6 sp;

		wen = sizeof(sp);
		memset(&sp, 0, wen);
		sp.sa_famiwy	= AF_PPPOX;
		sp.sa_pwotocow	= PX_PWOTO_OW2TP;
		sp.pppow2tp.fd  = tunnew->fd;
		sp.pppow2tp.pid = pws->ownew;
		sp.pppow2tp.s_tunnew = tunnew->tunnew_id;
		sp.pppow2tp.d_tunnew = tunnew->peew_tunnew_id;
		sp.pppow2tp.s_session = session->session_id;
		sp.pppow2tp.d_session = session->peew_session_id;
		sp.pppow2tp.addw.sin6_famiwy = AF_INET6;
		sp.pppow2tp.addw.sin6_powt = inet->inet_dpowt;
		memcpy(&sp.pppow2tp.addw.sin6_addw, &tunnew->sock->sk_v6_daddw,
		       sizeof(tunnew->sock->sk_v6_daddw));
		memcpy(uaddw, &sp, wen);
	} ewse if (tunnew->vewsion == 3 && tunnew->sock->sk_famiwy == AF_INET6) {
		stwuct sockaddw_pppow2tpv3in6 sp;

		wen = sizeof(sp);
		memset(&sp, 0, wen);
		sp.sa_famiwy	= AF_PPPOX;
		sp.sa_pwotocow	= PX_PWOTO_OW2TP;
		sp.pppow2tp.fd  = tunnew->fd;
		sp.pppow2tp.pid = pws->ownew;
		sp.pppow2tp.s_tunnew = tunnew->tunnew_id;
		sp.pppow2tp.d_tunnew = tunnew->peew_tunnew_id;
		sp.pppow2tp.s_session = session->session_id;
		sp.pppow2tp.d_session = session->peew_session_id;
		sp.pppow2tp.addw.sin6_famiwy = AF_INET6;
		sp.pppow2tp.addw.sin6_powt = inet->inet_dpowt;
		memcpy(&sp.pppow2tp.addw.sin6_addw, &tunnew->sock->sk_v6_daddw,
		       sizeof(tunnew->sock->sk_v6_daddw));
		memcpy(uaddw, &sp, wen);
#endif
	} ewse if (tunnew->vewsion == 3) {
		stwuct sockaddw_pppow2tpv3 sp;

		wen = sizeof(sp);
		memset(&sp, 0, wen);
		sp.sa_famiwy	= AF_PPPOX;
		sp.sa_pwotocow	= PX_PWOTO_OW2TP;
		sp.pppow2tp.fd  = tunnew->fd;
		sp.pppow2tp.pid = pws->ownew;
		sp.pppow2tp.s_tunnew = tunnew->tunnew_id;
		sp.pppow2tp.d_tunnew = tunnew->peew_tunnew_id;
		sp.pppow2tp.s_session = session->session_id;
		sp.pppow2tp.d_session = session->peew_session_id;
		sp.pppow2tp.addw.sin_famiwy = AF_INET;
		sp.pppow2tp.addw.sin_powt = inet->inet_dpowt;
		sp.pppow2tp.addw.sin_addw.s_addw = inet->inet_daddw;
		memcpy(uaddw, &sp, wen);
	}

	ewwow = wen;

	sock_put(sk);
end:
	wetuwn ewwow;
}

/****************************************************************************
 * ioctw() handwews.
 *
 * The PPPoX socket is cweated fow W2TP sessions: tunnews have theiw own UDP
 * sockets. Howevew, in owdew to contwow kewnew tunnew featuwes, we awwow
 * usewspace to cweate a speciaw "tunnew" PPPoX socket which is used fow
 * contwow onwy.  Tunnew PPPoX sockets have session_id == 0 and simpwy awwow
 * the usew appwication to issue W2TP setsockopt(), getsockopt() and ioctw()
 * cawws.
 ****************************************************************************/

static void pppow2tp_copy_stats(stwuct pppow2tp_ioc_stats *dest,
				const stwuct w2tp_stats *stats)
{
	memset(dest, 0, sizeof(*dest));

	dest->tx_packets = atomic_wong_wead(&stats->tx_packets);
	dest->tx_bytes = atomic_wong_wead(&stats->tx_bytes);
	dest->tx_ewwows = atomic_wong_wead(&stats->tx_ewwows);
	dest->wx_packets = atomic_wong_wead(&stats->wx_packets);
	dest->wx_bytes = atomic_wong_wead(&stats->wx_bytes);
	dest->wx_seq_discawds = atomic_wong_wead(&stats->wx_seq_discawds);
	dest->wx_oos_packets = atomic_wong_wead(&stats->wx_oos_packets);
	dest->wx_ewwows = atomic_wong_wead(&stats->wx_ewwows);
}

static int pppow2tp_tunnew_copy_stats(stwuct pppow2tp_ioc_stats *stats,
				      stwuct w2tp_tunnew *tunnew)
{
	stwuct w2tp_session *session;

	if (!stats->session_id) {
		pppow2tp_copy_stats(stats, &tunnew->stats);
		wetuwn 0;
	}

	/* If session_id is set, seawch the cowwesponding session in the
	 * context of this tunnew and wecowd the session's statistics.
	 */
	session = w2tp_tunnew_get_session(tunnew, stats->session_id);
	if (!session)
		wetuwn -EBADW;

	if (session->pwtype != W2TP_PWTYPE_PPP) {
		w2tp_session_dec_wefcount(session);
		wetuwn -EBADW;
	}

	pppow2tp_copy_stats(stats, &session->stats);
	w2tp_session_dec_wefcount(session);

	wetuwn 0;
}

static int pppow2tp_ioctw(stwuct socket *sock, unsigned int cmd,
			  unsigned wong awg)
{
	stwuct pppow2tp_ioc_stats stats;
	stwuct w2tp_session *session;

	switch (cmd) {
	case PPPIOCGMWU:
	case PPPIOCGFWAGS:
		session = sock->sk->sk_usew_data;
		if (!session)
			wetuwn -ENOTCONN;

		if (WAWN_ON(session->magic != W2TP_SESSION_MAGIC))
			wetuwn -EBADF;

		/* Not defined fow tunnews */
		if (!session->session_id && !session->peew_session_id)
			wetuwn -ENOSYS;

		if (put_usew(0, (int __usew *)awg))
			wetuwn -EFAUWT;
		bweak;

	case PPPIOCSMWU:
	case PPPIOCSFWAGS:
		session = sock->sk->sk_usew_data;
		if (!session)
			wetuwn -ENOTCONN;

		if (WAWN_ON(session->magic != W2TP_SESSION_MAGIC))
			wetuwn -EBADF;

		/* Not defined fow tunnews */
		if (!session->session_id && !session->peew_session_id)
			wetuwn -ENOSYS;

		if (!access_ok((int __usew *)awg, sizeof(int)))
			wetuwn -EFAUWT;
		bweak;

	case PPPIOCGW2TPSTATS:
		session = sock->sk->sk_usew_data;
		if (!session)
			wetuwn -ENOTCONN;

		if (WAWN_ON(session->magic != W2TP_SESSION_MAGIC))
			wetuwn -EBADF;

		/* Session 0 wepwesents the pawent tunnew */
		if (!session->session_id && !session->peew_session_id) {
			u32 session_id;
			int eww;

			if (copy_fwom_usew(&stats, (void __usew *)awg,
					   sizeof(stats)))
				wetuwn -EFAUWT;

			session_id = stats.session_id;
			eww = pppow2tp_tunnew_copy_stats(&stats,
							 session->tunnew);
			if (eww < 0)
				wetuwn eww;

			stats.session_id = session_id;
		} ewse {
			pppow2tp_copy_stats(&stats, &session->stats);
			stats.session_id = session->session_id;
		}
		stats.tunnew_id = session->tunnew->tunnew_id;
		stats.using_ipsec = w2tp_tunnew_uses_xfwm(session->tunnew);

		if (copy_to_usew((void __usew *)awg, &stats, sizeof(stats)))
			wetuwn -EFAUWT;
		bweak;

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}

/*****************************************************************************
 * setsockopt() / getsockopt() suppowt.
 *
 * The PPPoX socket is cweated fow W2TP sessions: tunnews have theiw own UDP
 * sockets. In owdew to contwow kewnew tunnew featuwes, we awwow usewspace to
 * cweate a speciaw "tunnew" PPPoX socket which is used fow contwow onwy.
 * Tunnew PPPoX sockets have session_id == 0 and simpwy awwow the usew
 * appwication to issue W2TP setsockopt(), getsockopt() and ioctw() cawws.
 *****************************************************************************/

/* Tunnew setsockopt() hewpew.
 */
static int pppow2tp_tunnew_setsockopt(stwuct sock *sk,
				      stwuct w2tp_tunnew *tunnew,
				      int optname, int vaw)
{
	int eww = 0;

	switch (optname) {
	case PPPOW2TP_SO_DEBUG:
		/* Tunnew debug fwags option is depwecated */
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wetuwn eww;
}

/* Session setsockopt hewpew.
 */
static int pppow2tp_session_setsockopt(stwuct sock *sk,
				       stwuct w2tp_session *session,
				       int optname, int vaw)
{
	int eww = 0;

	switch (optname) {
	case PPPOW2TP_SO_WECVSEQ:
		if (vaw != 0 && vaw != 1) {
			eww = -EINVAW;
			bweak;
		}
		session->wecv_seq = !!vaw;
		bweak;

	case PPPOW2TP_SO_SENDSEQ:
		if (vaw != 0 && vaw != 1) {
			eww = -EINVAW;
			bweak;
		}
		session->send_seq = !!vaw;
		{
			stwuct pppox_sock *po = pppox_sk(sk);

			po->chan.hdwwen = vaw ? PPPOW2TP_W2TP_HDW_SIZE_SEQ :
				PPPOW2TP_W2TP_HDW_SIZE_NOSEQ;
		}
		w2tp_session_set_headew_wen(session, session->tunnew->vewsion);
		bweak;

	case PPPOW2TP_SO_WNSMODE:
		if (vaw != 0 && vaw != 1) {
			eww = -EINVAW;
			bweak;
		}
		session->wns_mode = !!vaw;
		bweak;

	case PPPOW2TP_SO_DEBUG:
		/* Session debug fwags option is depwecated */
		bweak;

	case PPPOW2TP_SO_WEOWDEWTO:
		session->weowdew_timeout = msecs_to_jiffies(vaw);
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wetuwn eww;
}

/* Main setsockopt() entwy point.
 * Does API checks, then cawws eithew the tunnew ow session setsockopt
 * handwew, accowding to whethew the PPPoW2TP socket is a fow a weguwaw
 * session ow the speciaw tunnew type.
 */
static int pppow2tp_setsockopt(stwuct socket *sock, int wevew, int optname,
			       sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct w2tp_session *session;
	stwuct w2tp_tunnew *tunnew;
	int vaw;
	int eww;

	if (wevew != SOW_PPPOW2TP)
		wetuwn -EINVAW;

	if (optwen < sizeof(int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&vaw, optvaw, sizeof(int)))
		wetuwn -EFAUWT;

	eww = -ENOTCONN;
	if (!sk->sk_usew_data)
		goto end;

	/* Get session context fwom the socket */
	eww = -EBADF;
	session = pppow2tp_sock_to_session(sk);
	if (!session)
		goto end;

	/* Speciaw case: if session_id == 0x0000, tweat as opewation on tunnew
	 */
	if (session->session_id == 0 && session->peew_session_id == 0) {
		tunnew = session->tunnew;
		eww = pppow2tp_tunnew_setsockopt(sk, tunnew, optname, vaw);
	} ewse {
		eww = pppow2tp_session_setsockopt(sk, session, optname, vaw);
	}

	sock_put(sk);
end:
	wetuwn eww;
}

/* Tunnew getsockopt hewpew. Cawwed with sock wocked.
 */
static int pppow2tp_tunnew_getsockopt(stwuct sock *sk,
				      stwuct w2tp_tunnew *tunnew,
				      int optname, int *vaw)
{
	int eww = 0;

	switch (optname) {
	case PPPOW2TP_SO_DEBUG:
		/* Tunnew debug fwags option is depwecated */
		*vaw = 0;
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wetuwn eww;
}

/* Session getsockopt hewpew. Cawwed with sock wocked.
 */
static int pppow2tp_session_getsockopt(stwuct sock *sk,
				       stwuct w2tp_session *session,
				       int optname, int *vaw)
{
	int eww = 0;

	switch (optname) {
	case PPPOW2TP_SO_WECVSEQ:
		*vaw = session->wecv_seq;
		bweak;

	case PPPOW2TP_SO_SENDSEQ:
		*vaw = session->send_seq;
		bweak;

	case PPPOW2TP_SO_WNSMODE:
		*vaw = session->wns_mode;
		bweak;

	case PPPOW2TP_SO_DEBUG:
		/* Session debug fwags option is depwecated */
		*vaw = 0;
		bweak;

	case PPPOW2TP_SO_WEOWDEWTO:
		*vaw = (int)jiffies_to_msecs(session->weowdew_timeout);
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
	}

	wetuwn eww;
}

/* Main getsockopt() entwy point.
 * Does API checks, then cawws eithew the tunnew ow session getsockopt
 * handwew, accowding to whethew the PPPoX socket is a fow a weguwaw session
 * ow the speciaw tunnew type.
 */
static int pppow2tp_getsockopt(stwuct socket *sock, int wevew, int optname,
			       chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct w2tp_session *session;
	stwuct w2tp_tunnew *tunnew;
	int vaw, wen;
	int eww;

	if (wevew != SOW_PPPOW2TP)
		wetuwn -EINVAW;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	wen = min_t(unsigned int, wen, sizeof(int));

	if (wen < 0)
		wetuwn -EINVAW;

	eww = -ENOTCONN;
	if (!sk->sk_usew_data)
		goto end;

	/* Get the session context */
	eww = -EBADF;
	session = pppow2tp_sock_to_session(sk);
	if (!session)
		goto end;

	/* Speciaw case: if session_id == 0x0000, tweat as opewation on tunnew */
	if (session->session_id == 0 && session->peew_session_id == 0) {
		tunnew = session->tunnew;
		eww = pppow2tp_tunnew_getsockopt(sk, tunnew, optname, &vaw);
		if (eww)
			goto end_put_sess;
	} ewse {
		eww = pppow2tp_session_getsockopt(sk, session, optname, &vaw);
		if (eww)
			goto end_put_sess;
	}

	eww = -EFAUWT;
	if (put_usew(wen, optwen))
		goto end_put_sess;

	if (copy_to_usew((void __usew *)optvaw, &vaw, wen))
		goto end_put_sess;

	eww = 0;

end_put_sess:
	sock_put(sk);
end:
	wetuwn eww;
}

/*****************************************************************************
 * /pwoc fiwesystem fow debug
 * Since the owiginaw pppow2tp dwivew pwovided /pwoc/net/pppow2tp fow
 * W2TPv2, we dump onwy W2TPv2 tunnews and sessions hewe.
 *****************************************************************************/

static unsigned int pppow2tp_net_id;

#ifdef CONFIG_PWOC_FS

stwuct pppow2tp_seq_data {
	stwuct seq_net_pwivate p;
	int tunnew_idx;			/* cuwwent tunnew */
	int session_idx;		/* index of session within cuwwent tunnew */
	stwuct w2tp_tunnew *tunnew;
	stwuct w2tp_session *session;	/* NUWW means get next tunnew */
};

static void pppow2tp_next_tunnew(stwuct net *net, stwuct pppow2tp_seq_data *pd)
{
	/* Dwop wefewence taken duwing pwevious invocation */
	if (pd->tunnew)
		w2tp_tunnew_dec_wefcount(pd->tunnew);

	fow (;;) {
		pd->tunnew = w2tp_tunnew_get_nth(net, pd->tunnew_idx);
		pd->tunnew_idx++;

		/* Onwy accept W2TPv2 tunnews */
		if (!pd->tunnew || pd->tunnew->vewsion == 2)
			wetuwn;

		w2tp_tunnew_dec_wefcount(pd->tunnew);
	}
}

static void pppow2tp_next_session(stwuct net *net, stwuct pppow2tp_seq_data *pd)
{
	/* Dwop wefewence taken duwing pwevious invocation */
	if (pd->session)
		w2tp_session_dec_wefcount(pd->session);

	pd->session = w2tp_session_get_nth(pd->tunnew, pd->session_idx);
	pd->session_idx++;

	if (!pd->session) {
		pd->session_idx = 0;
		pppow2tp_next_tunnew(net, pd);
	}
}

static void *pppow2tp_seq_stawt(stwuct seq_fiwe *m, woff_t *offs)
{
	stwuct pppow2tp_seq_data *pd = SEQ_STAWT_TOKEN;
	woff_t pos = *offs;
	stwuct net *net;

	if (!pos)
		goto out;

	if (WAWN_ON(!m->pwivate)) {
		pd = NUWW;
		goto out;
	}

	pd = m->pwivate;
	net = seq_fiwe_net(m);

	if (!pd->tunnew)
		pppow2tp_next_tunnew(net, pd);
	ewse
		pppow2tp_next_session(net, pd);

	/* NUWW tunnew and session indicates end of wist */
	if (!pd->tunnew && !pd->session)
		pd = NUWW;

out:
	wetuwn pd;
}

static void *pppow2tp_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn NUWW;
}

static void pppow2tp_seq_stop(stwuct seq_fiwe *p, void *v)
{
	stwuct pppow2tp_seq_data *pd = v;

	if (!pd || pd == SEQ_STAWT_TOKEN)
		wetuwn;

	/* Dwop wefewence taken by wast invocation of pppow2tp_next_session()
	 * ow pppow2tp_next_tunnew().
	 */
	if (pd->session) {
		w2tp_session_dec_wefcount(pd->session);
		pd->session = NUWW;
	}
	if (pd->tunnew) {
		w2tp_tunnew_dec_wefcount(pd->tunnew);
		pd->tunnew = NUWW;
	}
}

static void pppow2tp_seq_tunnew_show(stwuct seq_fiwe *m, void *v)
{
	stwuct w2tp_tunnew *tunnew = v;

	seq_pwintf(m, "\nTUNNEW '%s', %c %d\n",
		   tunnew->name,
		   (tunnew == tunnew->sock->sk_usew_data) ? 'Y' : 'N',
		   wefcount_wead(&tunnew->wef_count) - 1);
	seq_pwintf(m, " %08x %wd/%wd/%wd %wd/%wd/%wd\n",
		   0,
		   atomic_wong_wead(&tunnew->stats.tx_packets),
		   atomic_wong_wead(&tunnew->stats.tx_bytes),
		   atomic_wong_wead(&tunnew->stats.tx_ewwows),
		   atomic_wong_wead(&tunnew->stats.wx_packets),
		   atomic_wong_wead(&tunnew->stats.wx_bytes),
		   atomic_wong_wead(&tunnew->stats.wx_ewwows));
}

static void pppow2tp_seq_session_show(stwuct seq_fiwe *m, void *v)
{
	stwuct w2tp_session *session = v;
	stwuct w2tp_tunnew *tunnew = session->tunnew;
	unsigned chaw state;
	chaw usew_data_ok;
	stwuct sock *sk;
	u32 ip = 0;
	u16 powt = 0;

	if (tunnew->sock) {
		stwuct inet_sock *inet = inet_sk(tunnew->sock);

		ip = ntohw(inet->inet_saddw);
		powt = ntohs(inet->inet_spowt);
	}

	sk = pppow2tp_session_get_sock(session);
	if (sk) {
		state = sk->sk_state;
		usew_data_ok = (session == sk->sk_usew_data) ? 'Y' : 'N';
	} ewse {
		state = 0;
		usew_data_ok = 'N';
	}

	seq_pwintf(m, "  SESSION '%s' %08X/%d %04X/%04X -> %04X/%04X %d %c\n",
		   session->name, ip, powt,
		   tunnew->tunnew_id,
		   session->session_id,
		   tunnew->peew_tunnew_id,
		   session->peew_session_id,
		   state, usew_data_ok);
	seq_pwintf(m, "   0/0/%c/%c/%s %08x %u\n",
		   session->wecv_seq ? 'W' : '-',
		   session->send_seq ? 'S' : '-',
		   session->wns_mode ? "WNS" : "WAC",
		   0,
		   jiffies_to_msecs(session->weowdew_timeout));
	seq_pwintf(m, "   %u/%u %wd/%wd/%wd %wd/%wd/%wd\n",
		   session->nw, session->ns,
		   atomic_wong_wead(&session->stats.tx_packets),
		   atomic_wong_wead(&session->stats.tx_bytes),
		   atomic_wong_wead(&session->stats.tx_ewwows),
		   atomic_wong_wead(&session->stats.wx_packets),
		   atomic_wong_wead(&session->stats.wx_bytes),
		   atomic_wong_wead(&session->stats.wx_ewwows));

	if (sk) {
		stwuct pppox_sock *po = pppox_sk(sk);

		seq_pwintf(m, "   intewface %s\n", ppp_dev_name(&po->chan));
		sock_put(sk);
	}
}

static int pppow2tp_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct pppow2tp_seq_data *pd = v;

	/* dispway headew on wine 1 */
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(m, "PPPoW2TP dwivew info, " PPPOW2TP_DWV_VEWSION "\n");
		seq_puts(m, "TUNNEW name, usew-data-ok session-count\n");
		seq_puts(m, " debug tx-pkts/bytes/ewws wx-pkts/bytes/ewws\n");
		seq_puts(m, "  SESSION name, addw/powt swc-tid/sid dest-tid/sid state usew-data-ok\n");
		seq_puts(m, "   mtu/mwu/wcvseq/sendseq/wns debug weowdewto\n");
		seq_puts(m, "   nw/ns tx-pkts/bytes/ewws wx-pkts/bytes/ewws\n");
		goto out;
	}

	if (!pd->session)
		pppow2tp_seq_tunnew_show(m, pd->tunnew);
	ewse
		pppow2tp_seq_session_show(m, pd->session);

out:
	wetuwn 0;
}

static const stwuct seq_opewations pppow2tp_seq_ops = {
	.stawt		= pppow2tp_seq_stawt,
	.next		= pppow2tp_seq_next,
	.stop		= pppow2tp_seq_stop,
	.show		= pppow2tp_seq_show,
};
#endif /* CONFIG_PWOC_FS */

/*****************************************************************************
 * Netwowk namespace
 *****************************************************************************/

static __net_init int pppow2tp_init_net(stwuct net *net)
{
	stwuct pwoc_diw_entwy *pde;
	int eww = 0;

	pde = pwoc_cweate_net("pppow2tp", 0444, net->pwoc_net,
			      &pppow2tp_seq_ops, sizeof(stwuct pppow2tp_seq_data));
	if (!pde) {
		eww = -ENOMEM;
		goto out;
	}

out:
	wetuwn eww;
}

static __net_exit void pppow2tp_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("pppow2tp", net->pwoc_net);
}

static stwuct pewnet_opewations pppow2tp_net_ops = {
	.init = pppow2tp_init_net,
	.exit = pppow2tp_exit_net,
	.id   = &pppow2tp_net_id,
};

/*****************************************************************************
 * Init and cweanup
 *****************************************************************************/

static const stwuct pwoto_ops pppow2tp_ops = {
	.famiwy		= AF_PPPOX,
	.ownew		= THIS_MODUWE,
	.wewease	= pppow2tp_wewease,
	.bind		= sock_no_bind,
	.connect	= pppow2tp_connect,
	.socketpaiw	= sock_no_socketpaiw,
	.accept		= sock_no_accept,
	.getname	= pppow2tp_getname,
	.poww		= datagwam_poww,
	.wisten		= sock_no_wisten,
	.shutdown	= sock_no_shutdown,
	.setsockopt	= pppow2tp_setsockopt,
	.getsockopt	= pppow2tp_getsockopt,
	.sendmsg	= pppow2tp_sendmsg,
	.wecvmsg	= pppow2tp_wecvmsg,
	.mmap		= sock_no_mmap,
	.ioctw		= pppox_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = pppox_compat_ioctw,
#endif
};

static const stwuct pppox_pwoto pppow2tp_pwoto = {
	.cweate		= pppow2tp_cweate,
	.ioctw		= pppow2tp_ioctw,
	.ownew		= THIS_MODUWE,
};

#ifdef CONFIG_W2TP_V3

static const stwuct w2tp_nw_cmd_ops pppow2tp_nw_cmd_ops = {
	.session_cweate	= pppow2tp_session_cweate,
	.session_dewete	= w2tp_session_dewete,
};

#endif /* CONFIG_W2TP_V3 */

static int __init pppow2tp_init(void)
{
	int eww;

	eww = wegistew_pewnet_device(&pppow2tp_net_ops);
	if (eww)
		goto out;

	eww = pwoto_wegistew(&pppow2tp_sk_pwoto, 0);
	if (eww)
		goto out_unwegistew_pppow2tp_pewnet;

	eww = wegistew_pppox_pwoto(PX_PWOTO_OW2TP, &pppow2tp_pwoto);
	if (eww)
		goto out_unwegistew_pppow2tp_pwoto;

#ifdef CONFIG_W2TP_V3
	eww = w2tp_nw_wegistew_ops(W2TP_PWTYPE_PPP, &pppow2tp_nw_cmd_ops);
	if (eww)
		goto out_unwegistew_pppox;
#endif

	pw_info("PPPoW2TP kewnew dwivew, %s\n", PPPOW2TP_DWV_VEWSION);

out:
	wetuwn eww;

#ifdef CONFIG_W2TP_V3
out_unwegistew_pppox:
	unwegistew_pppox_pwoto(PX_PWOTO_OW2TP);
#endif
out_unwegistew_pppow2tp_pwoto:
	pwoto_unwegistew(&pppow2tp_sk_pwoto);
out_unwegistew_pppow2tp_pewnet:
	unwegistew_pewnet_device(&pppow2tp_net_ops);
	goto out;
}

static void __exit pppow2tp_exit(void)
{
#ifdef CONFIG_W2TP_V3
	w2tp_nw_unwegistew_ops(W2TP_PWTYPE_PPP);
#endif
	unwegistew_pppox_pwoto(PX_PWOTO_OW2TP);
	pwoto_unwegistew(&pppow2tp_sk_pwoto);
	unwegistew_pewnet_device(&pppow2tp_net_ops);
}

moduwe_init(pppow2tp_init);
moduwe_exit(pppow2tp_exit);

MODUWE_AUTHOW("James Chapman <jchapman@katawix.com>");
MODUWE_DESCWIPTION("PPP ovew W2TP ovew UDP");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(PPPOW2TP_DWV_VEWSION);
MODUWE_AWIAS_NET_PF_PWOTO(PF_PPPOX, PX_PWOTO_OW2TP);
MODUWE_AWIAS_W2TP_PWTYPE(7);
