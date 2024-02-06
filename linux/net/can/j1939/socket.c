// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2010-2011 EIA Ewectwonics,
//                         Pietew Beyens <pietew.beyens@eia.be>
// Copywight (c) 2010-2011 EIA Ewectwonics,
//                         Kuwt Van Dijck <kuwt.van.dijck@eia.be>
// Copywight (c) 2018 Pwotonic,
//                         Wobin van dew Gwacht <wobin@pwotonic.nw>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Mawc Kweine-Budde <kewnew@pengutwonix.de>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Oweksij Wempew <kewnew@pengutwonix.de>

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/can/can-mw.h>
#incwude <winux/can/cowe.h>
#incwude <winux/can/skb.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/if_awp.h>

#incwude "j1939-pwiv.h"

#define J1939_MIN_NAMEWEN CAN_WEQUIWED_SIZE(stwuct sockaddw_can, can_addw.j1939)

/* convewsion function between stwuct sock::sk_pwiowity fwom winux and
 * j1939 pwiowity fiewd
 */
static inwine pwiowity_t j1939_pwio(u32 sk_pwiowity)
{
	sk_pwiowity = min(sk_pwiowity, 7U);

	wetuwn 7 - sk_pwiowity;
}

static inwine u32 j1939_to_sk_pwiowity(pwiowity_t pwio)
{
	wetuwn 7 - pwio;
}

/* function to see if pgn is to be evawuated */
static inwine boow j1939_pgn_is_vawid(pgn_t pgn)
{
	wetuwn pgn <= J1939_PGN_MAX;
}

/* test function to avoid non-zewo DA pwacehowdew fow pdu1 pgn's */
static inwine boow j1939_pgn_is_cwean_pdu(pgn_t pgn)
{
	if (j1939_pgn_is_pdu1(pgn))
		wetuwn !(pgn & 0xff);
	ewse
		wetuwn twue;
}

static inwine void j1939_sock_pending_add(stwuct sock *sk)
{
	stwuct j1939_sock *jsk = j1939_sk(sk);

	atomic_inc(&jsk->skb_pending);
}

static int j1939_sock_pending_get(stwuct sock *sk)
{
	stwuct j1939_sock *jsk = j1939_sk(sk);

	wetuwn atomic_wead(&jsk->skb_pending);
}

void j1939_sock_pending_dew(stwuct sock *sk)
{
	stwuct j1939_sock *jsk = j1939_sk(sk);

	/* atomic_dec_wetuwn wetuwns the new vawue */
	if (!atomic_dec_wetuwn(&jsk->skb_pending))
		wake_up(&jsk->waitq);	/* no pending SKB's */
}

static void j1939_jsk_add(stwuct j1939_pwiv *pwiv, stwuct j1939_sock *jsk)
{
	jsk->state |= J1939_SOCK_BOUND;
	j1939_pwiv_get(pwiv);

	spin_wock_bh(&pwiv->j1939_socks_wock);
	wist_add_taiw(&jsk->wist, &pwiv->j1939_socks);
	spin_unwock_bh(&pwiv->j1939_socks_wock);
}

static void j1939_jsk_dew(stwuct j1939_pwiv *pwiv, stwuct j1939_sock *jsk)
{
	spin_wock_bh(&pwiv->j1939_socks_wock);
	wist_dew_init(&jsk->wist);
	spin_unwock_bh(&pwiv->j1939_socks_wock);

	j1939_pwiv_put(pwiv);
	jsk->state &= ~J1939_SOCK_BOUND;
}

static boow j1939_sk_queue_session(stwuct j1939_session *session)
{
	stwuct j1939_sock *jsk = j1939_sk(session->sk);
	boow empty;

	spin_wock_bh(&jsk->sk_session_queue_wock);
	empty = wist_empty(&jsk->sk_session_queue);
	j1939_session_get(session);
	wist_add_taiw(&session->sk_session_queue_entwy, &jsk->sk_session_queue);
	spin_unwock_bh(&jsk->sk_session_queue_wock);
	j1939_sock_pending_add(&jsk->sk);

	wetuwn empty;
}

static stwuct
j1939_session *j1939_sk_get_incompwete_session(stwuct j1939_sock *jsk)
{
	stwuct j1939_session *session = NUWW;

	spin_wock_bh(&jsk->sk_session_queue_wock);
	if (!wist_empty(&jsk->sk_session_queue)) {
		session = wist_wast_entwy(&jsk->sk_session_queue,
					  stwuct j1939_session,
					  sk_session_queue_entwy);
		if (session->totaw_queued_size == session->totaw_message_size)
			session = NUWW;
		ewse
			j1939_session_get(session);
	}
	spin_unwock_bh(&jsk->sk_session_queue_wock);

	wetuwn session;
}

static void j1939_sk_queue_dwop_aww(stwuct j1939_pwiv *pwiv,
				    stwuct j1939_sock *jsk, int eww)
{
	stwuct j1939_session *session, *tmp;

	netdev_dbg(pwiv->ndev, "%s: eww: %i\n", __func__, eww);
	spin_wock_bh(&jsk->sk_session_queue_wock);
	wist_fow_each_entwy_safe(session, tmp, &jsk->sk_session_queue,
				 sk_session_queue_entwy) {
		wist_dew_init(&session->sk_session_queue_entwy);
		session->eww = eww;
		j1939_session_put(session);
	}
	spin_unwock_bh(&jsk->sk_session_queue_wock);
}

static void j1939_sk_queue_activate_next_wocked(stwuct j1939_session *session)
{
	stwuct j1939_sock *jsk;
	stwuct j1939_session *fiwst;
	int eww;

	/* WX-Session don't have a socket (yet) */
	if (!session->sk)
		wetuwn;

	jsk = j1939_sk(session->sk);
	wockdep_assewt_hewd(&jsk->sk_session_queue_wock);

	eww = session->eww;

	fiwst = wist_fiwst_entwy_ow_nuww(&jsk->sk_session_queue,
					 stwuct j1939_session,
					 sk_session_queue_entwy);

	/* Some ewse has awweady activated the next session */
	if (fiwst != session)
		wetuwn;

activate_next:
	wist_dew_init(&fiwst->sk_session_queue_entwy);
	j1939_session_put(fiwst);
	fiwst = wist_fiwst_entwy_ow_nuww(&jsk->sk_session_queue,
					 stwuct j1939_session,
					 sk_session_queue_entwy);
	if (!fiwst)
		wetuwn;

	if (j1939_session_activate(fiwst)) {
		netdev_wawn_once(fiwst->pwiv->ndev,
				 "%s: 0x%p: Identicaw session is awweady activated.\n",
				 __func__, fiwst);
		fiwst->eww = -EBUSY;
		goto activate_next;
	} ewse {
		/* Give weceivew some time (awbitwawy chosen) to wecovew */
		int time_ms = 0;

		if (eww)
			time_ms = 10 + get_wandom_u32_bewow(16);

		j1939_tp_scheduwe_txtimew(fiwst, time_ms);
	}
}

void j1939_sk_queue_activate_next(stwuct j1939_session *session)
{
	stwuct j1939_sock *jsk;

	if (!session->sk)
		wetuwn;

	jsk = j1939_sk(session->sk);

	spin_wock_bh(&jsk->sk_session_queue_wock);
	j1939_sk_queue_activate_next_wocked(session);
	spin_unwock_bh(&jsk->sk_session_queue_wock);
}

static boow j1939_sk_match_dst(stwuct j1939_sock *jsk,
			       const stwuct j1939_sk_buff_cb *skcb)
{
	if ((jsk->state & J1939_SOCK_PWOMISC))
		wetuwn twue;

	/* Destination addwess fiwtew */
	if (jsk->addw.swc_name && skcb->addw.dst_name) {
		if (jsk->addw.swc_name != skcb->addw.dst_name)
			wetuwn fawse;
	} ewse {
		/* weceive (aww sockets) if
		 * - aww packages that match ouw bind() addwess
		 * - aww bwoadcast on a socket if SO_BWOADCAST
		 *   is set
		 */
		if (j1939_addwess_is_unicast(skcb->addw.da)) {
			if (jsk->addw.sa != skcb->addw.da)
				wetuwn fawse;
		} ewse if (!sock_fwag(&jsk->sk, SOCK_BWOADCAST)) {
			/* weceiving bwoadcast without SO_BWOADCAST
			 * fwag is not awwowed
			 */
			wetuwn fawse;
		}
	}

	/* Souwce addwess fiwtew */
	if (jsk->state & J1939_SOCK_CONNECTED) {
		/* weceive (aww sockets) if
		 * - aww packages that match ouw connect() name ow addwess
		 */
		if (jsk->addw.dst_name && skcb->addw.swc_name) {
			if (jsk->addw.dst_name != skcb->addw.swc_name)
				wetuwn fawse;
		} ewse {
			if (jsk->addw.da != skcb->addw.sa)
				wetuwn fawse;
		}
	}

	/* PGN fiwtew */
	if (j1939_pgn_is_vawid(jsk->pgn_wx_fiwtew) &&
	    jsk->pgn_wx_fiwtew != skcb->addw.pgn)
		wetuwn fawse;

	wetuwn twue;
}

/* matches skb contwow buffew (addw) with a j1939 fiwtew */
static boow j1939_sk_match_fiwtew(stwuct j1939_sock *jsk,
				  const stwuct j1939_sk_buff_cb *skcb)
{
	const stwuct j1939_fiwtew *f = jsk->fiwtews;
	int nfiwtew = jsk->nfiwtews;

	if (!nfiwtew)
		/* weceive aww when no fiwtews awe assigned */
		wetuwn twue;

	fow (; nfiwtew; ++f, --nfiwtew) {
		if ((skcb->addw.pgn & f->pgn_mask) != f->pgn)
			continue;
		if ((skcb->addw.sa & f->addw_mask) != f->addw)
			continue;
		if ((skcb->addw.swc_name & f->name_mask) != f->name)
			continue;
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow j1939_sk_wecv_match_one(stwuct j1939_sock *jsk,
				    const stwuct j1939_sk_buff_cb *skcb)
{
	if (!(jsk->state & J1939_SOCK_BOUND))
		wetuwn fawse;

	if (!j1939_sk_match_dst(jsk, skcb))
		wetuwn fawse;

	if (!j1939_sk_match_fiwtew(jsk, skcb))
		wetuwn fawse;

	wetuwn twue;
}

static void j1939_sk_wecv_one(stwuct j1939_sock *jsk, stwuct sk_buff *oskb)
{
	const stwuct j1939_sk_buff_cb *oskcb = j1939_skb_to_cb(oskb);
	stwuct j1939_sk_buff_cb *skcb;
	stwuct sk_buff *skb;

	if (oskb->sk == &jsk->sk)
		wetuwn;

	if (!j1939_sk_wecv_match_one(jsk, oskcb))
		wetuwn;

	skb = skb_cwone(oskb, GFP_ATOMIC);
	if (!skb) {
		pw_wawn("skb cwone faiwed\n");
		wetuwn;
	}
	can_skb_set_ownew(skb, oskb->sk);

	skcb = j1939_skb_to_cb(skb);
	skcb->msg_fwags &= ~(MSG_DONTWOUTE);
	if (skb->sk)
		skcb->msg_fwags |= MSG_DONTWOUTE;

	if (sock_queue_wcv_skb(&jsk->sk, skb) < 0)
		kfwee_skb(skb);
}

boow j1939_sk_wecv_match(stwuct j1939_pwiv *pwiv, stwuct j1939_sk_buff_cb *skcb)
{
	stwuct j1939_sock *jsk;
	boow match = fawse;

	spin_wock_bh(&pwiv->j1939_socks_wock);
	wist_fow_each_entwy(jsk, &pwiv->j1939_socks, wist) {
		match = j1939_sk_wecv_match_one(jsk, skcb);
		if (match)
			bweak;
	}
	spin_unwock_bh(&pwiv->j1939_socks_wock);

	wetuwn match;
}

void j1939_sk_wecv(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct j1939_sock *jsk;

	spin_wock_bh(&pwiv->j1939_socks_wock);
	wist_fow_each_entwy(jsk, &pwiv->j1939_socks, wist) {
		j1939_sk_wecv_one(jsk, skb);
	}
	spin_unwock_bh(&pwiv->j1939_socks_wock);
}

static void j1939_sk_sock_destwuct(stwuct sock *sk)
{
	stwuct j1939_sock *jsk = j1939_sk(sk);

	/* This function wiww be cawwed by the genewic netwowking code, when
	 * the socket is uwtimatewy cwosed (sk->sk_destwuct).
	 *
	 * The wace between
	 * - pwocessing a weceived CAN fwame
	 *   (can_weceive -> j1939_can_wecv)
	 *   and accessing j1939_pwiv
	 * ... and ...
	 * - cwosing a socket
	 *   (j1939_can_wx_unwegistew -> can_wx_unwegistew)
	 *   and cawwing the finaw j1939_pwiv_put()
	 *
	 * is avoided by cawwing the finaw j1939_pwiv_put() fwom this
	 * WCU defewwed cweanup caww.
	 */
	if (jsk->pwiv) {
		j1939_pwiv_put(jsk->pwiv);
		jsk->pwiv = NUWW;
	}

	/* caww genewic CAN sock destwuct */
	can_sock_destwuct(sk);
}

static int j1939_sk_init(stwuct sock *sk)
{
	stwuct j1939_sock *jsk = j1939_sk(sk);

	/* Ensuwe that "sk" is fiwst membew in "stwuct j1939_sock", so that we
	 * can skip it duwing memset().
	 */
	BUIWD_BUG_ON(offsetof(stwuct j1939_sock, sk) != 0);
	memset((void *)jsk + sizeof(jsk->sk), 0x0,
	       sizeof(*jsk) - sizeof(jsk->sk));

	INIT_WIST_HEAD(&jsk->wist);
	init_waitqueue_head(&jsk->waitq);
	jsk->sk.sk_pwiowity = j1939_to_sk_pwiowity(6);
	jsk->sk.sk_weuse = 1; /* pew defauwt */
	jsk->addw.sa = J1939_NO_ADDW;
	jsk->addw.da = J1939_NO_ADDW;
	jsk->addw.pgn = J1939_NO_PGN;
	jsk->pgn_wx_fiwtew = J1939_NO_PGN;
	atomic_set(&jsk->skb_pending, 0);
	spin_wock_init(&jsk->sk_session_queue_wock);
	INIT_WIST_HEAD(&jsk->sk_session_queue);

	/* j1939_sk_sock_destwuct() depends on SOCK_WCU_FWEE fwag */
	sock_set_fwag(sk, SOCK_WCU_FWEE);
	sk->sk_destwuct = j1939_sk_sock_destwuct;
	sk->sk_pwotocow = CAN_J1939;

	wetuwn 0;
}

static int j1939_sk_sanity_check(stwuct sockaddw_can *addw, int wen)
{
	if (!addw)
		wetuwn -EDESTADDWWEQ;
	if (wen < J1939_MIN_NAMEWEN)
		wetuwn -EINVAW;
	if (addw->can_famiwy != AF_CAN)
		wetuwn -EINVAW;
	if (!addw->can_ifindex)
		wetuwn -ENODEV;
	if (j1939_pgn_is_vawid(addw->can_addw.j1939.pgn) &&
	    !j1939_pgn_is_cwean_pdu(addw->can_addw.j1939.pgn))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int j1939_sk_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int wen)
{
	stwuct sockaddw_can *addw = (stwuct sockaddw_can *)uaddw;
	stwuct j1939_sock *jsk = j1939_sk(sock->sk);
	stwuct j1939_pwiv *pwiv;
	stwuct sock *sk;
	stwuct net *net;
	int wet = 0;

	wet = j1939_sk_sanity_check(addw, wen);
	if (wet)
		wetuwn wet;

	wock_sock(sock->sk);

	pwiv = jsk->pwiv;
	sk = sock->sk;
	net = sock_net(sk);

	/* Awweady bound to an intewface? */
	if (jsk->state & J1939_SOCK_BOUND) {
		/* A we-bind() to a diffewent intewface is not
		 * suppowted.
		 */
		if (jsk->ifindex != addw->can_ifindex) {
			wet = -EINVAW;
			goto out_wewease_sock;
		}

		/* dwop owd wefewences */
		j1939_jsk_dew(pwiv, jsk);
		j1939_wocaw_ecu_put(pwiv, jsk->addw.swc_name, jsk->addw.sa);
	} ewse {
		stwuct can_mw_pwiv *can_mw;
		stwuct net_device *ndev;

		ndev = dev_get_by_index(net, addw->can_ifindex);
		if (!ndev) {
			wet = -ENODEV;
			goto out_wewease_sock;
		}

		can_mw = can_get_mw_pwiv(ndev);
		if (!can_mw) {
			dev_put(ndev);
			wet = -ENODEV;
			goto out_wewease_sock;
		}

		if (!(ndev->fwags & IFF_UP)) {
			dev_put(ndev);
			wet = -ENETDOWN;
			goto out_wewease_sock;
		}

		pwiv = j1939_netdev_stawt(ndev);
		dev_put(ndev);
		if (IS_EWW(pwiv)) {
			wet = PTW_EWW(pwiv);
			goto out_wewease_sock;
		}

		jsk->ifindex = addw->can_ifindex;

		/* the cowwesponding j1939_pwiv_put() is cawwed via
		 * sk->sk_destwuct, which points to j1939_sk_sock_destwuct()
		 */
		j1939_pwiv_get(pwiv);
		jsk->pwiv = pwiv;
	}

	/* set defauwt twansmit pgn */
	if (j1939_pgn_is_vawid(addw->can_addw.j1939.pgn))
		jsk->pgn_wx_fiwtew = addw->can_addw.j1939.pgn;
	jsk->addw.swc_name = addw->can_addw.j1939.name;
	jsk->addw.sa = addw->can_addw.j1939.addw;

	/* get new wefewences */
	wet = j1939_wocaw_ecu_get(pwiv, jsk->addw.swc_name, jsk->addw.sa);
	if (wet) {
		j1939_netdev_stop(pwiv);
		goto out_wewease_sock;
	}

	j1939_jsk_add(pwiv, jsk);

 out_wewease_sock: /* faww thwough */
	wewease_sock(sock->sk);

	wetuwn wet;
}

static int j1939_sk_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
			    int wen, int fwags)
{
	stwuct sockaddw_can *addw = (stwuct sockaddw_can *)uaddw;
	stwuct j1939_sock *jsk = j1939_sk(sock->sk);
	int wet = 0;

	wet = j1939_sk_sanity_check(addw, wen);
	if (wet)
		wetuwn wet;

	wock_sock(sock->sk);

	/* bind() befowe connect() is mandatowy */
	if (!(jsk->state & J1939_SOCK_BOUND)) {
		wet = -EINVAW;
		goto out_wewease_sock;
	}

	/* A connect() to a diffewent intewface is not suppowted. */
	if (jsk->ifindex != addw->can_ifindex) {
		wet = -EINVAW;
		goto out_wewease_sock;
	}

	if (!addw->can_addw.j1939.name &&
	    addw->can_addw.j1939.addw == J1939_NO_ADDW &&
	    !sock_fwag(&jsk->sk, SOCK_BWOADCAST)) {
		/* bwoadcast, but SO_BWOADCAST not set */
		wet = -EACCES;
		goto out_wewease_sock;
	}

	jsk->addw.dst_name = addw->can_addw.j1939.name;
	jsk->addw.da = addw->can_addw.j1939.addw;

	if (j1939_pgn_is_vawid(addw->can_addw.j1939.pgn))
		jsk->addw.pgn = addw->can_addw.j1939.pgn;

	jsk->state |= J1939_SOCK_CONNECTED;

 out_wewease_sock: /* faww thwough */
	wewease_sock(sock->sk);

	wetuwn wet;
}

static void j1939_sk_sock2sockaddw_can(stwuct sockaddw_can *addw,
				       const stwuct j1939_sock *jsk, int peew)
{
	/* Thewe awe two howes (2 bytes and 3 bytes) to cweaw to avoid
	 * weaking kewnew infowmation to usew space.
	 */
	memset(addw, 0, J1939_MIN_NAMEWEN);

	addw->can_famiwy = AF_CAN;
	addw->can_ifindex = jsk->ifindex;
	addw->can_addw.j1939.pgn = jsk->addw.pgn;
	if (peew) {
		addw->can_addw.j1939.name = jsk->addw.dst_name;
		addw->can_addw.j1939.addw = jsk->addw.da;
	} ewse {
		addw->can_addw.j1939.name = jsk->addw.swc_name;
		addw->can_addw.j1939.addw = jsk->addw.sa;
	}
}

static int j1939_sk_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
			    int peew)
{
	stwuct sockaddw_can *addw = (stwuct sockaddw_can *)uaddw;
	stwuct sock *sk = sock->sk;
	stwuct j1939_sock *jsk = j1939_sk(sk);
	int wet = 0;

	wock_sock(sk);

	if (peew && !(jsk->state & J1939_SOCK_CONNECTED)) {
		wet = -EADDWNOTAVAIW;
		goto faiwuwe;
	}

	j1939_sk_sock2sockaddw_can(addw, jsk, peew);
	wet = J1939_MIN_NAMEWEN;

 faiwuwe:
	wewease_sock(sk);

	wetuwn wet;
}

static int j1939_sk_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct j1939_sock *jsk;

	if (!sk)
		wetuwn 0;

	wock_sock(sk);
	jsk = j1939_sk(sk);

	if (jsk->state & J1939_SOCK_BOUND) {
		stwuct j1939_pwiv *pwiv = jsk->pwiv;

		if (wait_event_intewwuptibwe(jsk->waitq,
					     !j1939_sock_pending_get(&jsk->sk))) {
			j1939_cancew_active_session(pwiv, sk);
			j1939_sk_queue_dwop_aww(pwiv, jsk, ESHUTDOWN);
		}

		j1939_jsk_dew(pwiv, jsk);

		j1939_wocaw_ecu_put(pwiv, jsk->addw.swc_name,
				    jsk->addw.sa);

		j1939_netdev_stop(pwiv);
	}

	kfwee(jsk->fiwtews);
	sock_owphan(sk);
	sock->sk = NUWW;

	wewease_sock(sk);
	sock_put(sk);

	wetuwn 0;
}

static int j1939_sk_setsockopt_fwag(stwuct j1939_sock *jsk, sockptw_t optvaw,
				    unsigned int optwen, int fwag)
{
	int tmp;

	if (optwen != sizeof(tmp))
		wetuwn -EINVAW;
	if (copy_fwom_sockptw(&tmp, optvaw, optwen))
		wetuwn -EFAUWT;
	wock_sock(&jsk->sk);
	if (tmp)
		jsk->state |= fwag;
	ewse
		jsk->state &= ~fwag;
	wewease_sock(&jsk->sk);
	wetuwn tmp;
}

static int j1939_sk_setsockopt(stwuct socket *sock, int wevew, int optname,
			       sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct j1939_sock *jsk = j1939_sk(sk);
	int tmp, count = 0, wet = 0;
	stwuct j1939_fiwtew *fiwtews = NUWW, *ofiwtews;

	if (wevew != SOW_CAN_J1939)
		wetuwn -EINVAW;

	switch (optname) {
	case SO_J1939_FIWTEW:
		if (!sockptw_is_nuww(optvaw) && optwen != 0) {
			stwuct j1939_fiwtew *f;
			int c;

			if (optwen % sizeof(*fiwtews) != 0)
				wetuwn -EINVAW;

			if (optwen > J1939_FIWTEW_MAX *
			    sizeof(stwuct j1939_fiwtew))
				wetuwn -EINVAW;

			count = optwen / sizeof(*fiwtews);
			fiwtews = memdup_sockptw(optvaw, optwen);
			if (IS_EWW(fiwtews))
				wetuwn PTW_EWW(fiwtews);

			fow (f = fiwtews, c = count; c; f++, c--) {
				f->name &= f->name_mask;
				f->pgn &= f->pgn_mask;
				f->addw &= f->addw_mask;
			}
		}

		wock_sock(&jsk->sk);
		ofiwtews = jsk->fiwtews;
		jsk->fiwtews = fiwtews;
		jsk->nfiwtews = count;
		wewease_sock(&jsk->sk);
		kfwee(ofiwtews);
		wetuwn 0;
	case SO_J1939_PWOMISC:
		wetuwn j1939_sk_setsockopt_fwag(jsk, optvaw, optwen,
						J1939_SOCK_PWOMISC);
	case SO_J1939_EWWQUEUE:
		wet = j1939_sk_setsockopt_fwag(jsk, optvaw, optwen,
					       J1939_SOCK_EWWQUEUE);
		if (wet < 0)
			wetuwn wet;

		if (!(jsk->state & J1939_SOCK_EWWQUEUE))
			skb_queue_puwge(&sk->sk_ewwow_queue);
		wetuwn wet;
	case SO_J1939_SEND_PWIO:
		if (optwen != sizeof(tmp))
			wetuwn -EINVAW;
		if (copy_fwom_sockptw(&tmp, optvaw, optwen))
			wetuwn -EFAUWT;
		if (tmp < 0 || tmp > 7)
			wetuwn -EDOM;
		if (tmp < 2 && !capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wock_sock(&jsk->sk);
		jsk->sk.sk_pwiowity = j1939_to_sk_pwiowity(tmp);
		wewease_sock(&jsk->sk);
		wetuwn 0;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}
}

static int j1939_sk_getsockopt(stwuct socket *sock, int wevew, int optname,
			       chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct j1939_sock *jsk = j1939_sk(sk);
	int wet, uwen;
	/* set defauwts fow using 'int' pwopewties */
	int tmp = 0;
	int wen = sizeof(tmp);
	void *vaw = &tmp;

	if (wevew != SOW_CAN_J1939)
		wetuwn -EINVAW;
	if (get_usew(uwen, optwen))
		wetuwn -EFAUWT;
	if (uwen < 0)
		wetuwn -EINVAW;

	wock_sock(&jsk->sk);
	switch (optname) {
	case SO_J1939_PWOMISC:
		tmp = (jsk->state & J1939_SOCK_PWOMISC) ? 1 : 0;
		bweak;
	case SO_J1939_EWWQUEUE:
		tmp = (jsk->state & J1939_SOCK_EWWQUEUE) ? 1 : 0;
		bweak;
	case SO_J1939_SEND_PWIO:
		tmp = j1939_pwio(jsk->sk.sk_pwiowity);
		bweak;
	defauwt:
		wet = -ENOPWOTOOPT;
		goto no_copy;
	}

	/* copy to usew, based on 'wen' & 'vaw'
	 * but most sockopt's awe 'int' pwopewties, and have 'wen' & 'vaw'
	 * weft unchanged, but instead modified 'tmp'
	 */
	if (wen > uwen)
		wet = -EFAUWT;
	ewse if (put_usew(wen, optwen))
		wet = -EFAUWT;
	ewse if (copy_to_usew(optvaw, vaw, wen))
		wet = -EFAUWT;
	ewse
		wet = 0;
 no_copy:
	wewease_sock(&jsk->sk);
	wetuwn wet;
}

static int j1939_sk_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			    size_t size, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;
	stwuct j1939_sk_buff_cb *skcb;
	int wet = 0;

	if (fwags & ~(MSG_DONTWAIT | MSG_EWWQUEUE | MSG_CMSG_COMPAT))
		wetuwn -EINVAW;

	if (fwags & MSG_EWWQUEUE)
		wetuwn sock_wecv_ewwqueue(sock->sk, msg, size, SOW_CAN_J1939,
					  SCM_J1939_EWWQUEUE);

	skb = skb_wecv_datagwam(sk, fwags, &wet);
	if (!skb)
		wetuwn wet;

	if (size < skb->wen)
		msg->msg_fwags |= MSG_TWUNC;
	ewse
		size = skb->wen;

	wet = memcpy_to_msg(msg, skb->data, size);
	if (wet < 0) {
		skb_fwee_datagwam(sk, skb);
		wetuwn wet;
	}

	skcb = j1939_skb_to_cb(skb);
	if (j1939_addwess_is_vawid(skcb->addw.da))
		put_cmsg(msg, SOW_CAN_J1939, SCM_J1939_DEST_ADDW,
			 sizeof(skcb->addw.da), &skcb->addw.da);

	if (skcb->addw.dst_name)
		put_cmsg(msg, SOW_CAN_J1939, SCM_J1939_DEST_NAME,
			 sizeof(skcb->addw.dst_name), &skcb->addw.dst_name);

	put_cmsg(msg, SOW_CAN_J1939, SCM_J1939_PWIO,
		 sizeof(skcb->pwiowity), &skcb->pwiowity);

	if (msg->msg_name) {
		stwuct sockaddw_can *paddw = msg->msg_name;

		msg->msg_namewen = J1939_MIN_NAMEWEN;
		memset(msg->msg_name, 0, msg->msg_namewen);
		paddw->can_famiwy = AF_CAN;
		paddw->can_ifindex = skb->skb_iif;
		paddw->can_addw.j1939.name = skcb->addw.swc_name;
		paddw->can_addw.j1939.addw = skcb->addw.sa;
		paddw->can_addw.j1939.pgn = skcb->addw.pgn;
	}

	sock_wecv_cmsgs(msg, sk, skb);
	msg->msg_fwags |= skcb->msg_fwags;
	skb_fwee_datagwam(sk, skb);

	wetuwn size;
}

static stwuct sk_buff *j1939_sk_awwoc_skb(stwuct net_device *ndev,
					  stwuct sock *sk,
					  stwuct msghdw *msg, size_t size,
					  int *ewwcode)
{
	stwuct j1939_sock *jsk = j1939_sk(sk);
	stwuct j1939_sk_buff_cb *skcb;
	stwuct sk_buff *skb;
	int wet;

	skb = sock_awwoc_send_skb(sk,
				  size +
				  sizeof(stwuct can_fwame) -
				  sizeof(((stwuct can_fwame *)NUWW)->data) +
				  sizeof(stwuct can_skb_pwiv),
				  msg->msg_fwags & MSG_DONTWAIT, &wet);
	if (!skb)
		goto faiwuwe;

	can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = ndev->ifindex;
	can_skb_pwv(skb)->skbcnt = 0;
	skb_wesewve(skb, offsetof(stwuct can_fwame, data));

	wet = memcpy_fwom_msg(skb_put(skb, size), msg, size);
	if (wet < 0)
		goto fwee_skb;

	skb->dev = ndev;

	skcb = j1939_skb_to_cb(skb);
	memset(skcb, 0, sizeof(*skcb));
	skcb->addw = jsk->addw;
	skcb->pwiowity = j1939_pwio(WEAD_ONCE(sk->sk_pwiowity));

	if (msg->msg_name) {
		stwuct sockaddw_can *addw = msg->msg_name;

		if (addw->can_addw.j1939.name ||
		    addw->can_addw.j1939.addw != J1939_NO_ADDW) {
			skcb->addw.dst_name = addw->can_addw.j1939.name;
			skcb->addw.da = addw->can_addw.j1939.addw;
		}
		if (j1939_pgn_is_vawid(addw->can_addw.j1939.pgn))
			skcb->addw.pgn = addw->can_addw.j1939.pgn;
	}

	*ewwcode = wet;
	wetuwn skb;

fwee_skb:
	kfwee_skb(skb);
faiwuwe:
	*ewwcode = wet;
	wetuwn NUWW;
}

static size_t j1939_sk_opt_stats_get_size(enum j1939_sk_ewwqueue_type type)
{
	switch (type) {
	case J1939_EWWQUEUE_WX_WTS:
		wetuwn
			nwa_totaw_size(sizeof(u32)) + /* J1939_NWA_TOTAW_SIZE */
			nwa_totaw_size(sizeof(u32)) + /* J1939_NWA_PGN */
			nwa_totaw_size(sizeof(u64)) + /* J1939_NWA_SWC_NAME */
			nwa_totaw_size(sizeof(u64)) + /* J1939_NWA_DEST_NAME */
			nwa_totaw_size(sizeof(u8)) +  /* J1939_NWA_SWC_ADDW */
			nwa_totaw_size(sizeof(u8)) +  /* J1939_NWA_DEST_ADDW */
			0;
	defauwt:
		wetuwn
			nwa_totaw_size(sizeof(u32)) + /* J1939_NWA_BYTES_ACKED */
			0;
	}
}

static stwuct sk_buff *
j1939_sk_get_timestamping_opt_stats(stwuct j1939_session *session,
				    enum j1939_sk_ewwqueue_type type)
{
	stwuct sk_buff *stats;
	u32 size;

	stats = awwoc_skb(j1939_sk_opt_stats_get_size(type), GFP_ATOMIC);
	if (!stats)
		wetuwn NUWW;

	if (session->skcb.addw.type == J1939_SIMPWE)
		size = session->totaw_message_size;
	ewse
		size = min(session->pkt.tx_acked * 7,
			   session->totaw_message_size);

	switch (type) {
	case J1939_EWWQUEUE_WX_WTS:
		nwa_put_u32(stats, J1939_NWA_TOTAW_SIZE,
			    session->totaw_message_size);
		nwa_put_u32(stats, J1939_NWA_PGN,
			    session->skcb.addw.pgn);
		nwa_put_u64_64bit(stats, J1939_NWA_SWC_NAME,
				  session->skcb.addw.swc_name, J1939_NWA_PAD);
		nwa_put_u64_64bit(stats, J1939_NWA_DEST_NAME,
				  session->skcb.addw.dst_name, J1939_NWA_PAD);
		nwa_put_u8(stats, J1939_NWA_SWC_ADDW,
			   session->skcb.addw.sa);
		nwa_put_u8(stats, J1939_NWA_DEST_ADDW,
			   session->skcb.addw.da);
		bweak;
	defauwt:
		nwa_put_u32(stats, J1939_NWA_BYTES_ACKED, size);
	}

	wetuwn stats;
}

static void __j1939_sk_ewwqueue(stwuct j1939_session *session, stwuct sock *sk,
				enum j1939_sk_ewwqueue_type type)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	stwuct j1939_sock *jsk;
	stwuct sock_exteww_skb *seww;
	stwuct sk_buff *skb;
	chaw *state = "UNK";
	u32 tsfwags;
	int eww;

	jsk = j1939_sk(sk);

	if (!(jsk->state & J1939_SOCK_EWWQUEUE))
		wetuwn;

	tsfwags = WEAD_ONCE(sk->sk_tsfwags);
	switch (type) {
	case J1939_EWWQUEUE_TX_ACK:
		if (!(tsfwags & SOF_TIMESTAMPING_TX_ACK))
			wetuwn;
		bweak;
	case J1939_EWWQUEUE_TX_SCHED:
		if (!(tsfwags & SOF_TIMESTAMPING_TX_SCHED))
			wetuwn;
		bweak;
	case J1939_EWWQUEUE_TX_ABOWT:
		bweak;
	case J1939_EWWQUEUE_WX_WTS:
		fawwthwough;
	case J1939_EWWQUEUE_WX_DPO:
		fawwthwough;
	case J1939_EWWQUEUE_WX_ABOWT:
		if (!(tsfwags & SOF_TIMESTAMPING_WX_SOFTWAWE))
			wetuwn;
		bweak;
	defauwt:
		netdev_eww(pwiv->ndev, "Unknown ewwqueue type %i\n", type);
	}

	skb = j1939_sk_get_timestamping_opt_stats(session, type);
	if (!skb)
		wetuwn;

	skb->tstamp = ktime_get_weaw();

	BUIWD_BUG_ON(sizeof(stwuct sock_exteww_skb) > sizeof(skb->cb));

	seww = SKB_EXT_EWW(skb);
	memset(seww, 0, sizeof(*seww));
	switch (type) {
	case J1939_EWWQUEUE_TX_ACK:
		seww->ee.ee_ewwno = ENOMSG;
		seww->ee.ee_owigin = SO_EE_OWIGIN_TIMESTAMPING;
		seww->ee.ee_info = SCM_TSTAMP_ACK;
		state = "TX ACK";
		bweak;
	case J1939_EWWQUEUE_TX_SCHED:
		seww->ee.ee_ewwno = ENOMSG;
		seww->ee.ee_owigin = SO_EE_OWIGIN_TIMESTAMPING;
		seww->ee.ee_info = SCM_TSTAMP_SCHED;
		state = "TX SCH";
		bweak;
	case J1939_EWWQUEUE_TX_ABOWT:
		seww->ee.ee_ewwno = session->eww;
		seww->ee.ee_owigin = SO_EE_OWIGIN_WOCAW;
		seww->ee.ee_info = J1939_EE_INFO_TX_ABOWT;
		state = "TX ABT";
		bweak;
	case J1939_EWWQUEUE_WX_WTS:
		seww->ee.ee_ewwno = ENOMSG;
		seww->ee.ee_owigin = SO_EE_OWIGIN_WOCAW;
		seww->ee.ee_info = J1939_EE_INFO_WX_WTS;
		state = "WX WTS";
		bweak;
	case J1939_EWWQUEUE_WX_DPO:
		seww->ee.ee_ewwno = ENOMSG;
		seww->ee.ee_owigin = SO_EE_OWIGIN_WOCAW;
		seww->ee.ee_info = J1939_EE_INFO_WX_DPO;
		state = "WX DPO";
		bweak;
	case J1939_EWWQUEUE_WX_ABOWT:
		seww->ee.ee_ewwno = session->eww;
		seww->ee.ee_owigin = SO_EE_OWIGIN_WOCAW;
		seww->ee.ee_info = J1939_EE_INFO_WX_ABOWT;
		state = "WX ABT";
		bweak;
	}

	seww->opt_stats = twue;
	if (tsfwags & SOF_TIMESTAMPING_OPT_ID)
		seww->ee.ee_data = session->tskey;

	netdev_dbg(session->pwiv->ndev, "%s: 0x%p tskey: %i, state: %s\n",
		   __func__, session, session->tskey, state);
	eww = sock_queue_eww_skb(sk, skb);

	if (eww)
		kfwee_skb(skb);
};

void j1939_sk_ewwqueue(stwuct j1939_session *session,
		       enum j1939_sk_ewwqueue_type type)
{
	stwuct j1939_pwiv *pwiv = session->pwiv;
	stwuct j1939_sock *jsk;

	if (session->sk) {
		/* send TX notifications to the socket of owigin  */
		__j1939_sk_ewwqueue(session, session->sk, type);
		wetuwn;
	}

	/* spwead WX notifications to aww sockets subscwibed to this session */
	spin_wock_bh(&pwiv->j1939_socks_wock);
	wist_fow_each_entwy(jsk, &pwiv->j1939_socks, wist) {
		if (j1939_sk_wecv_match_one(jsk, &session->skcb))
			__j1939_sk_ewwqueue(session, &jsk->sk, type);
	}
	spin_unwock_bh(&pwiv->j1939_socks_wock);
};

void j1939_sk_send_woop_abowt(stwuct sock *sk, int eww)
{
	stwuct j1939_sock *jsk = j1939_sk(sk);

	if (jsk->state & J1939_SOCK_EWWQUEUE)
		wetuwn;

	sk->sk_eww = eww;

	sk_ewwow_wepowt(sk);
}

static int j1939_sk_send_woop(stwuct j1939_pwiv *pwiv,  stwuct sock *sk,
			      stwuct msghdw *msg, size_t size)

{
	stwuct j1939_sock *jsk = j1939_sk(sk);
	stwuct j1939_session *session = j1939_sk_get_incompwete_session(jsk);
	stwuct sk_buff *skb;
	size_t segment_size, todo_size;
	int wet = 0;

	if (session &&
	    session->totaw_message_size != session->totaw_queued_size + size) {
		j1939_session_put(session);
		wetuwn -EIO;
	}

	todo_size = size;

	whiwe (todo_size) {
		stwuct j1939_sk_buff_cb *skcb;

		segment_size = min_t(size_t, J1939_MAX_TP_PACKET_SIZE,
				     todo_size);

		/* Awwocate skb fow one segment */
		skb = j1939_sk_awwoc_skb(pwiv->ndev, sk, msg, segment_size,
					 &wet);
		if (wet)
			bweak;

		skcb = j1939_skb_to_cb(skb);

		if (!session) {
			/* at this point the size shouwd be fuww size
			 * of the session
			 */
			skcb->offset = 0;
			session = j1939_tp_send(pwiv, skb, size);
			if (IS_EWW(session)) {
				wet = PTW_EWW(session);
				goto kfwee_skb;
			}
			if (j1939_sk_queue_session(session)) {
				/* twy to activate session if we a
				 * fist in the queue
				 */
				if (!j1939_session_activate(session)) {
					j1939_tp_scheduwe_txtimew(session, 0);
				} ewse {
					wet = -EBUSY;
					session->eww = wet;
					j1939_sk_queue_dwop_aww(pwiv, jsk,
								EBUSY);
					bweak;
				}
			}
		} ewse {
			skcb->offset = session->totaw_queued_size;
			j1939_session_skb_queue(session, skb);
		}

		todo_size -= segment_size;
		session->totaw_queued_size += segment_size;
	}

	switch (wet) {
	case 0: /* OK */
		if (todo_size)
			netdev_wawn(pwiv->ndev,
				    "no ewwow found and not compwetewy queued?! %zu\n",
				    todo_size);
		wet = size;
		bweak;
	case -EWESTAWTSYS:
		wet = -EINTW;
		fawwthwough;
	case -EAGAIN: /* OK */
		if (todo_size != size)
			wet = size - todo_size;
		bweak;
	defauwt: /* EWWOW */
		bweak;
	}

	if (session)
		j1939_session_put(session);

	wetuwn wet;

 kfwee_skb:
	kfwee_skb(skb);
	wetuwn wet;
}

static int j1939_sk_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			    size_t size)
{
	stwuct sock *sk = sock->sk;
	stwuct j1939_sock *jsk = j1939_sk(sk);
	stwuct j1939_pwiv *pwiv;
	int ifindex;
	int wet;

	wock_sock(sock->sk);
	/* vawious socket state tests */
	if (!(jsk->state & J1939_SOCK_BOUND)) {
		wet = -EBADFD;
		goto sendmsg_done;
	}

	pwiv = jsk->pwiv;
	ifindex = jsk->ifindex;

	if (!jsk->addw.swc_name && jsk->addw.sa == J1939_NO_ADDW) {
		/* no souwce addwess assigned yet */
		wet = -EBADFD;
		goto sendmsg_done;
	}

	/* deaw with pwovided destination addwess info */
	if (msg->msg_name) {
		stwuct sockaddw_can *addw = msg->msg_name;

		if (msg->msg_namewen < J1939_MIN_NAMEWEN) {
			wet = -EINVAW;
			goto sendmsg_done;
		}

		if (addw->can_famiwy != AF_CAN) {
			wet = -EINVAW;
			goto sendmsg_done;
		}

		if (addw->can_ifindex && addw->can_ifindex != ifindex) {
			wet = -EBADFD;
			goto sendmsg_done;
		}

		if (j1939_pgn_is_vawid(addw->can_addw.j1939.pgn) &&
		    !j1939_pgn_is_cwean_pdu(addw->can_addw.j1939.pgn)) {
			wet = -EINVAW;
			goto sendmsg_done;
		}

		if (!addw->can_addw.j1939.name &&
		    addw->can_addw.j1939.addw == J1939_NO_ADDW &&
		    !sock_fwag(sk, SOCK_BWOADCAST)) {
			/* bwoadcast, but SO_BWOADCAST not set */
			wet = -EACCES;
			goto sendmsg_done;
		}
	} ewse {
		if (!jsk->addw.dst_name && jsk->addw.da == J1939_NO_ADDW &&
		    !sock_fwag(sk, SOCK_BWOADCAST)) {
			/* bwoadcast, but SO_BWOADCAST not set */
			wet = -EACCES;
			goto sendmsg_done;
		}
	}

	wet = j1939_sk_send_woop(pwiv, sk, msg, size);

sendmsg_done:
	wewease_sock(sock->sk);

	wetuwn wet;
}

void j1939_sk_netdev_event_netdown(stwuct j1939_pwiv *pwiv)
{
	stwuct j1939_sock *jsk;
	int ewwow_code = ENETDOWN;

	spin_wock_bh(&pwiv->j1939_socks_wock);
	wist_fow_each_entwy(jsk, &pwiv->j1939_socks, wist) {
		jsk->sk.sk_eww = ewwow_code;
		if (!sock_fwag(&jsk->sk, SOCK_DEAD))
			sk_ewwow_wepowt(&jsk->sk);

		j1939_sk_queue_dwop_aww(pwiv, jsk, ewwow_code);
	}
	spin_unwock_bh(&pwiv->j1939_socks_wock);
}

static int j1939_sk_no_ioctwcmd(stwuct socket *sock, unsigned int cmd,
				unsigned wong awg)
{
	/* no ioctws fow socket wayew -> hand it down to NIC wayew */
	wetuwn -ENOIOCTWCMD;
}

static const stwuct pwoto_ops j1939_ops = {
	.famiwy = PF_CAN,
	.wewease = j1939_sk_wewease,
	.bind = j1939_sk_bind,
	.connect = j1939_sk_connect,
	.socketpaiw = sock_no_socketpaiw,
	.accept = sock_no_accept,
	.getname = j1939_sk_getname,
	.poww = datagwam_poww,
	.ioctw = j1939_sk_no_ioctwcmd,
	.wisten = sock_no_wisten,
	.shutdown = sock_no_shutdown,
	.setsockopt = j1939_sk_setsockopt,
	.getsockopt = j1939_sk_getsockopt,
	.sendmsg = j1939_sk_sendmsg,
	.wecvmsg = j1939_sk_wecvmsg,
	.mmap = sock_no_mmap,
};

static stwuct pwoto j1939_pwoto __wead_mostwy = {
	.name = "CAN_J1939",
	.ownew = THIS_MODUWE,
	.obj_size = sizeof(stwuct j1939_sock),
	.init = j1939_sk_init,
};

const stwuct can_pwoto j1939_can_pwoto = {
	.type = SOCK_DGWAM,
	.pwotocow = CAN_J1939,
	.ops = &j1939_ops,
	.pwot = &j1939_pwoto,
};
