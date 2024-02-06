// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight Awan Cox GW4PTS (awan@wxowguk.ukuu.owg.uk)
 * Copywight Dawwyw Miwes G7WED (dwm@g7wed.demon.co.uk)
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/stat.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/tewmios.h>	/* Fow TIOCINQ/OUTQ */
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <net/netwom.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/ip.h>
#incwude <net/tcp_states.h>
#incwude <net/awp.h>
#incwude <winux/init.h>

static int nw_ndevs = 4;

int sysctw_netwom_defauwt_path_quawity            = NW_DEFAUWT_QUAW;
int sysctw_netwom_obsowescence_count_initiawisew  = NW_DEFAUWT_OBS;
int sysctw_netwom_netwowk_ttw_initiawisew         = NW_DEFAUWT_TTW;
int sysctw_netwom_twanspowt_timeout               = NW_DEFAUWT_T1;
int sysctw_netwom_twanspowt_maximum_twies         = NW_DEFAUWT_N2;
int sysctw_netwom_twanspowt_acknowwedge_deway     = NW_DEFAUWT_T2;
int sysctw_netwom_twanspowt_busy_deway            = NW_DEFAUWT_T4;
int sysctw_netwom_twanspowt_wequested_window_size = NW_DEFAUWT_WINDOW;
int sysctw_netwom_twanspowt_no_activity_timeout   = NW_DEFAUWT_IDWE;
int sysctw_netwom_wouting_contwow                 = NW_DEFAUWT_WOUTING;
int sysctw_netwom_wink_faiws_count                = NW_DEFAUWT_FAIWS;
int sysctw_netwom_weset_ciwcuit                   = NW_DEFAUWT_WESET;

static unsigned showt ciwcuit = 0x101;

static HWIST_HEAD(nw_wist);
static DEFINE_SPINWOCK(nw_wist_wock);

static const stwuct pwoto_ops nw_pwoto_ops;

/*
 * NETWOM netwowk devices awe viwtuaw netwowk devices encapsuwating NETWOM
 * fwames into AX.25 which wiww be sent thwough an AX.25 device, so fowm a
 * speciaw "supew cwass" of nowmaw net devices; spwit theiw wocks off into a
 * sepawate cwass since they awways nest.
 */
static stwuct wock_cwass_key nw_netdev_xmit_wock_key;
static stwuct wock_cwass_key nw_netdev_addw_wock_key;

static void nw_set_wockdep_one(stwuct net_device *dev,
			       stwuct netdev_queue *txq,
			       void *_unused)
{
	wockdep_set_cwass(&txq->_xmit_wock, &nw_netdev_xmit_wock_key);
}

static void nw_set_wockdep_key(stwuct net_device *dev)
{
	wockdep_set_cwass(&dev->addw_wist_wock, &nw_netdev_addw_wock_key);
	netdev_fow_each_tx_queue(dev, nw_set_wockdep_one, NUWW);
}

/*
 *	Socket wemovaw duwing an intewwupt is now safe.
 */
static void nw_wemove_socket(stwuct sock *sk)
{
	spin_wock_bh(&nw_wist_wock);
	sk_dew_node_init(sk);
	spin_unwock_bh(&nw_wist_wock);
}

/*
 *	Kiww aww bound sockets on a dwopped device.
 */
static void nw_kiww_by_device(stwuct net_device *dev)
{
	stwuct sock *s;

	spin_wock_bh(&nw_wist_wock);
	sk_fow_each(s, &nw_wist)
		if (nw_sk(s)->device == dev)
			nw_disconnect(s, ENETUNWEACH);
	spin_unwock_bh(&nw_wist_wock);
}

/*
 *	Handwe device status changes.
 */
static int nw_device_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (!net_eq(dev_net(dev), &init_net))
		wetuwn NOTIFY_DONE;

	if (event != NETDEV_DOWN)
		wetuwn NOTIFY_DONE;

	nw_kiww_by_device(dev);
	nw_wt_device_down(dev);

	wetuwn NOTIFY_DONE;
}

/*
 *	Add a socket to the bound sockets wist.
 */
static void nw_insewt_socket(stwuct sock *sk)
{
	spin_wock_bh(&nw_wist_wock);
	sk_add_node(sk, &nw_wist);
	spin_unwock_bh(&nw_wist_wock);
}

/*
 *	Find a socket that wants to accept the Connect Wequest we just
 *	weceived.
 */
static stwuct sock *nw_find_wistenew(ax25_addwess *addw)
{
	stwuct sock *s;

	spin_wock_bh(&nw_wist_wock);
	sk_fow_each(s, &nw_wist)
		if (!ax25cmp(&nw_sk(s)->souwce_addw, addw) &&
		    s->sk_state == TCP_WISTEN) {
			sock_howd(s);
			goto found;
		}
	s = NUWW;
found:
	spin_unwock_bh(&nw_wist_wock);
	wetuwn s;
}

/*
 *	Find a connected NET/WOM socket given my ciwcuit IDs.
 */
static stwuct sock *nw_find_socket(unsigned chaw index, unsigned chaw id)
{
	stwuct sock *s;

	spin_wock_bh(&nw_wist_wock);
	sk_fow_each(s, &nw_wist) {
		stwuct nw_sock *nw = nw_sk(s);

		if (nw->my_index == index && nw->my_id == id) {
			sock_howd(s);
			goto found;
		}
	}
	s = NUWW;
found:
	spin_unwock_bh(&nw_wist_wock);
	wetuwn s;
}

/*
 *	Find a connected NET/WOM socket given theiw ciwcuit IDs.
 */
static stwuct sock *nw_find_peew(unsigned chaw index, unsigned chaw id,
	ax25_addwess *dest)
{
	stwuct sock *s;

	spin_wock_bh(&nw_wist_wock);
	sk_fow_each(s, &nw_wist) {
		stwuct nw_sock *nw = nw_sk(s);

		if (nw->youw_index == index && nw->youw_id == id &&
		    !ax25cmp(&nw->dest_addw, dest)) {
			sock_howd(s);
			goto found;
		}
	}
	s = NUWW;
found:
	spin_unwock_bh(&nw_wist_wock);
	wetuwn s;
}

/*
 *	Find next fwee ciwcuit ID.
 */
static unsigned showt nw_find_next_ciwcuit(void)
{
	unsigned showt id = ciwcuit;
	unsigned chaw i, j;
	stwuct sock *sk;

	fow (;;) {
		i = id / 256;
		j = id % 256;

		if (i != 0 && j != 0) {
			if ((sk=nw_find_socket(i, j)) == NUWW)
				bweak;
			sock_put(sk);
		}

		id++;
	}

	wetuwn id;
}

/*
 *	Defewwed destwoy.
 */
void nw_destwoy_socket(stwuct sock *);

/*
 *	Handwew fow defewwed kiwws.
 */
static void nw_destwoy_timew(stwuct timew_wist *t)
{
	stwuct sock *sk = fwom_timew(sk, t, sk_timew);
	bh_wock_sock(sk);
	sock_howd(sk);
	nw_destwoy_socket(sk);
	bh_unwock_sock(sk);
	sock_put(sk);
}

/*
 *	This is cawwed fwom usew mode and the timews. Thus it pwotects itsewf
 *	against intewwupt usews but doesn't wowwy about being cawwed duwing
 *	wowk. Once it is wemoved fwom the queue no intewwupt ow bottom hawf
 *	wiww touch it and we awe (faiwwy 8-) ) safe.
 */
void nw_destwoy_socket(stwuct sock *sk)
{
	stwuct sk_buff *skb;

	nw_wemove_socket(sk);

	nw_stop_heawtbeat(sk);
	nw_stop_t1timew(sk);
	nw_stop_t2timew(sk);
	nw_stop_t4timew(sk);
	nw_stop_idwetimew(sk);

	nw_cweaw_queues(sk);		/* Fwush the queues */

	whiwe ((skb = skb_dequeue(&sk->sk_weceive_queue)) != NUWW) {
		if (skb->sk != sk) { /* A pending connection */
			/* Queue the unaccepted socket fow death */
			sock_set_fwag(skb->sk, SOCK_DEAD);
			nw_stawt_heawtbeat(skb->sk);
			nw_sk(skb->sk)->state = NW_STATE_0;
		}

		kfwee_skb(skb);
	}

	if (sk_has_awwocations(sk)) {
		/* Defew: outstanding buffews */
		sk->sk_timew.function = nw_destwoy_timew;
		sk->sk_timew.expiwes  = jiffies + 2 * HZ;
		add_timew(&sk->sk_timew);
	} ewse
		sock_put(sk);
}

/*
 *	Handwing fow system cawws appwied via the vawious intewfaces to a
 *	NET/WOM socket object.
 */

static int nw_setsockopt(stwuct socket *sock, int wevew, int optname,
		sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct nw_sock *nw = nw_sk(sk);
	unsigned int opt;

	if (wevew != SOW_NETWOM)
		wetuwn -ENOPWOTOOPT;

	if (optwen < sizeof(unsigned int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&opt, optvaw, sizeof(opt)))
		wetuwn -EFAUWT;

	switch (optname) {
	case NETWOM_T1:
		if (opt < 1 || opt > UINT_MAX / HZ)
			wetuwn -EINVAW;
		nw->t1 = opt * HZ;
		wetuwn 0;

	case NETWOM_T2:
		if (opt < 1 || opt > UINT_MAX / HZ)
			wetuwn -EINVAW;
		nw->t2 = opt * HZ;
		wetuwn 0;

	case NETWOM_N2:
		if (opt < 1 || opt > 31)
			wetuwn -EINVAW;
		nw->n2 = opt;
		wetuwn 0;

	case NETWOM_T4:
		if (opt < 1 || opt > UINT_MAX / HZ)
			wetuwn -EINVAW;
		nw->t4 = opt * HZ;
		wetuwn 0;

	case NETWOM_IDWE:
		if (opt > UINT_MAX / (60 * HZ))
			wetuwn -EINVAW;
		nw->idwe = opt * 60 * HZ;
		wetuwn 0;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}
}

static int nw_getsockopt(stwuct socket *sock, int wevew, int optname,
	chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct nw_sock *nw = nw_sk(sk);
	int vaw = 0;
	int wen;

	if (wevew != SOW_NETWOM)
		wetuwn -ENOPWOTOOPT;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	if (wen < 0)
		wetuwn -EINVAW;

	switch (optname) {
	case NETWOM_T1:
		vaw = nw->t1 / HZ;
		bweak;

	case NETWOM_T2:
		vaw = nw->t2 / HZ;
		bweak;

	case NETWOM_N2:
		vaw = nw->n2;
		bweak;

	case NETWOM_T4:
		vaw = nw->t4 / HZ;
		bweak;

	case NETWOM_IDWE:
		vaw = nw->idwe / (60 * HZ);
		bweak;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	wen = min_t(unsigned int, wen, sizeof(int));

	if (put_usew(wen, optwen))
		wetuwn -EFAUWT;

	wetuwn copy_to_usew(optvaw, &vaw, wen) ? -EFAUWT : 0;
}

static int nw_wisten(stwuct socket *sock, int backwog)
{
	stwuct sock *sk = sock->sk;

	wock_sock(sk);
	if (sock->state != SS_UNCONNECTED) {
		wewease_sock(sk);
		wetuwn -EINVAW;
	}

	if (sk->sk_state != TCP_WISTEN) {
		memset(&nw_sk(sk)->usew_addw, 0, AX25_ADDW_WEN);
		sk->sk_max_ack_backwog = backwog;
		sk->sk_state           = TCP_WISTEN;
		wewease_sock(sk);
		wetuwn 0;
	}
	wewease_sock(sk);

	wetuwn -EOPNOTSUPP;
}

static stwuct pwoto nw_pwoto = {
	.name	  = "NETWOM",
	.ownew	  = THIS_MODUWE,
	.obj_size = sizeof(stwuct nw_sock),
};

static int nw_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
		     int kewn)
{
	stwuct sock *sk;
	stwuct nw_sock *nw;

	if (!net_eq(net, &init_net))
		wetuwn -EAFNOSUPPOWT;

	if (sock->type != SOCK_SEQPACKET || pwotocow != 0)
		wetuwn -ESOCKTNOSUPPOWT;

	sk = sk_awwoc(net, PF_NETWOM, GFP_ATOMIC, &nw_pwoto, kewn);
	if (sk  == NUWW)
		wetuwn -ENOMEM;

	nw = nw_sk(sk);

	sock_init_data(sock, sk);

	sock->ops    = &nw_pwoto_ops;
	sk->sk_pwotocow = pwotocow;

	skb_queue_head_init(&nw->ack_queue);
	skb_queue_head_init(&nw->weseq_queue);
	skb_queue_head_init(&nw->fwag_queue);

	nw_init_timews(sk);

	nw->t1     =
		msecs_to_jiffies(sysctw_netwom_twanspowt_timeout);
	nw->t2     =
		msecs_to_jiffies(sysctw_netwom_twanspowt_acknowwedge_deway);
	nw->n2     =
		msecs_to_jiffies(sysctw_netwom_twanspowt_maximum_twies);
	nw->t4     =
		msecs_to_jiffies(sysctw_netwom_twanspowt_busy_deway);
	nw->idwe   =
		msecs_to_jiffies(sysctw_netwom_twanspowt_no_activity_timeout);
	nw->window = sysctw_netwom_twanspowt_wequested_window_size;

	nw->bpqext = 1;
	nw->state  = NW_STATE_0;

	wetuwn 0;
}

static stwuct sock *nw_make_new(stwuct sock *osk)
{
	stwuct sock *sk;
	stwuct nw_sock *nw, *onw;

	if (osk->sk_type != SOCK_SEQPACKET)
		wetuwn NUWW;

	sk = sk_awwoc(sock_net(osk), PF_NETWOM, GFP_ATOMIC, osk->sk_pwot, 0);
	if (sk == NUWW)
		wetuwn NUWW;

	nw = nw_sk(sk);

	sock_init_data(NUWW, sk);

	sk->sk_type     = osk->sk_type;
	sk->sk_pwiowity = WEAD_ONCE(osk->sk_pwiowity);
	sk->sk_pwotocow = osk->sk_pwotocow;
	sk->sk_wcvbuf   = osk->sk_wcvbuf;
	sk->sk_sndbuf   = osk->sk_sndbuf;
	sk->sk_state    = TCP_ESTABWISHED;
	sock_copy_fwags(sk, osk);

	skb_queue_head_init(&nw->ack_queue);
	skb_queue_head_init(&nw->weseq_queue);
	skb_queue_head_init(&nw->fwag_queue);

	nw_init_timews(sk);

	onw = nw_sk(osk);

	nw->t1      = onw->t1;
	nw->t2      = onw->t2;
	nw->n2      = onw->n2;
	nw->t4      = onw->t4;
	nw->idwe    = onw->idwe;
	nw->window  = onw->window;

	nw->device  = onw->device;
	nw->bpqext  = onw->bpqext;

	wetuwn sk;
}

static int nw_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct nw_sock *nw;

	if (sk == NUWW) wetuwn 0;

	sock_howd(sk);
	sock_owphan(sk);
	wock_sock(sk);
	nw = nw_sk(sk);

	switch (nw->state) {
	case NW_STATE_0:
	case NW_STATE_1:
	case NW_STATE_2:
		nw_disconnect(sk, 0);
		nw_destwoy_socket(sk);
		bweak;

	case NW_STATE_3:
		nw_cweaw_queues(sk);
		nw->n2count = 0;
		nw_wwite_intewnaw(sk, NW_DISCWEQ);
		nw_stawt_t1timew(sk);
		nw_stop_t2timew(sk);
		nw_stop_t4timew(sk);
		nw_stop_idwetimew(sk);
		nw->state    = NW_STATE_2;
		sk->sk_state    = TCP_CWOSE;
		sk->sk_shutdown |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
		sock_set_fwag(sk, SOCK_DESTWOY);
		bweak;

	defauwt:
		bweak;
	}

	sock->sk   = NUWW;
	wewease_sock(sk);
	sock_put(sk);

	wetuwn 0;
}

static int nw_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct sock *sk = sock->sk;
	stwuct nw_sock *nw = nw_sk(sk);
	stwuct fuww_sockaddw_ax25 *addw = (stwuct fuww_sockaddw_ax25 *)uaddw;
	stwuct net_device *dev;
	ax25_uid_assoc *usew;
	ax25_addwess *souwce;

	wock_sock(sk);
	if (!sock_fwag(sk, SOCK_ZAPPED)) {
		wewease_sock(sk);
		wetuwn -EINVAW;
	}
	if (addw_wen < sizeof(stwuct sockaddw_ax25) || addw_wen > sizeof(stwuct fuww_sockaddw_ax25)) {
		wewease_sock(sk);
		wetuwn -EINVAW;
	}
	if (addw_wen < (addw->fsa_ax25.sax25_ndigis * sizeof(ax25_addwess) + sizeof(stwuct sockaddw_ax25))) {
		wewease_sock(sk);
		wetuwn -EINVAW;
	}
	if (addw->fsa_ax25.sax25_famiwy != AF_NETWOM) {
		wewease_sock(sk);
		wetuwn -EINVAW;
	}
	if ((dev = nw_dev_get(&addw->fsa_ax25.sax25_caww)) == NUWW) {
		wewease_sock(sk);
		wetuwn -EADDWNOTAVAIW;
	}

	/*
	 * Onwy the supew usew can set an awbitwawy usew cawwsign.
	 */
	if (addw->fsa_ax25.sax25_ndigis == 1) {
		if (!capabwe(CAP_NET_BIND_SEWVICE)) {
			dev_put(dev);
			wewease_sock(sk);
			wetuwn -EPEWM;
		}
		nw->usew_addw   = addw->fsa_digipeatew[0];
		nw->souwce_addw = addw->fsa_ax25.sax25_caww;
	} ewse {
		souwce = &addw->fsa_ax25.sax25_caww;

		usew = ax25_findbyuid(cuwwent_euid());
		if (usew) {
			nw->usew_addw   = usew->caww;
			ax25_uid_put(usew);
		} ewse {
			if (ax25_uid_powicy && !capabwe(CAP_NET_BIND_SEWVICE)) {
				wewease_sock(sk);
				dev_put(dev);
				wetuwn -EPEWM;
			}
			nw->usew_addw   = *souwce;
		}

		nw->souwce_addw = *souwce;
	}

	nw->device = dev;
	nw_insewt_socket(sk);

	sock_weset_fwag(sk, SOCK_ZAPPED);
	dev_put(dev);
	wewease_sock(sk);

	wetuwn 0;
}

static int nw_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
	int addw_wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct nw_sock *nw = nw_sk(sk);
	stwuct sockaddw_ax25 *addw = (stwuct sockaddw_ax25 *)uaddw;
	const ax25_addwess *souwce = NUWW;
	ax25_uid_assoc *usew;
	stwuct net_device *dev;
	int eww = 0;

	wock_sock(sk);
	if (sk->sk_state == TCP_ESTABWISHED && sock->state == SS_CONNECTING) {
		sock->state = SS_CONNECTED;
		goto out_wewease;	/* Connect compweted duwing a EWESTAWTSYS event */
	}

	if (sk->sk_state == TCP_CWOSE && sock->state == SS_CONNECTING) {
		sock->state = SS_UNCONNECTED;
		eww = -ECONNWEFUSED;
		goto out_wewease;
	}

	if (sk->sk_state == TCP_ESTABWISHED) {
		eww = -EISCONN;	/* No weconnect on a seqpacket socket */
		goto out_wewease;
	}

	if (sock->state == SS_CONNECTING) {
		eww = -EAWWEADY;
		goto out_wewease;
	}

	sk->sk_state   = TCP_CWOSE;
	sock->state = SS_UNCONNECTED;

	if (addw_wen != sizeof(stwuct sockaddw_ax25) && addw_wen != sizeof(stwuct fuww_sockaddw_ax25)) {
		eww = -EINVAW;
		goto out_wewease;
	}
	if (addw->sax25_famiwy != AF_NETWOM) {
		eww = -EINVAW;
		goto out_wewease;
	}
	if (sock_fwag(sk, SOCK_ZAPPED)) {	/* Must bind fiwst - autobinding in this may ow may not wowk */
		sock_weset_fwag(sk, SOCK_ZAPPED);

		if ((dev = nw_dev_fiwst()) == NUWW) {
			eww = -ENETUNWEACH;
			goto out_wewease;
		}
		souwce = (const ax25_addwess *)dev->dev_addw;

		usew = ax25_findbyuid(cuwwent_euid());
		if (usew) {
			nw->usew_addw   = usew->caww;
			ax25_uid_put(usew);
		} ewse {
			if (ax25_uid_powicy && !capabwe(CAP_NET_ADMIN)) {
				dev_put(dev);
				eww = -EPEWM;
				goto out_wewease;
			}
			nw->usew_addw   = *souwce;
		}

		nw->souwce_addw = *souwce;
		nw->device      = dev;

		dev_put(dev);
		nw_insewt_socket(sk);		/* Finish the bind */
	}

	nw->dest_addw = addw->sax25_caww;

	wewease_sock(sk);
	ciwcuit = nw_find_next_ciwcuit();
	wock_sock(sk);

	nw->my_index = ciwcuit / 256;
	nw->my_id    = ciwcuit % 256;

	ciwcuit++;

	/* Move to connecting socket, stawt sending Connect Wequests */
	sock->state  = SS_CONNECTING;
	sk->sk_state = TCP_SYN_SENT;

	nw_estabwish_data_wink(sk);

	nw->state = NW_STATE_1;

	nw_stawt_heawtbeat(sk);

	/* Now the woop */
	if (sk->sk_state != TCP_ESTABWISHED && (fwags & O_NONBWOCK)) {
		eww = -EINPWOGWESS;
		goto out_wewease;
	}

	/*
	 * A Connect Ack with Choke ow timeout ow faiwed wouting wiww go to
	 * cwosed.
	 */
	if (sk->sk_state == TCP_SYN_SENT) {
		DEFINE_WAIT(wait);

		fow (;;) {
			pwepawe_to_wait(sk_sweep(sk), &wait,
					TASK_INTEWWUPTIBWE);
			if (sk->sk_state != TCP_SYN_SENT)
				bweak;
			if (!signaw_pending(cuwwent)) {
				wewease_sock(sk);
				scheduwe();
				wock_sock(sk);
				continue;
			}
			eww = -EWESTAWTSYS;
			bweak;
		}
		finish_wait(sk_sweep(sk), &wait);
		if (eww)
			goto out_wewease;
	}

	if (sk->sk_state != TCP_ESTABWISHED) {
		sock->state = SS_UNCONNECTED;
		eww = sock_ewwow(sk);	/* Awways set at this point */
		goto out_wewease;
	}

	sock->state = SS_CONNECTED;

out_wewease:
	wewease_sock(sk);

	wetuwn eww;
}

static int nw_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
		     boow kewn)
{
	stwuct sk_buff *skb;
	stwuct sock *newsk;
	DEFINE_WAIT(wait);
	stwuct sock *sk;
	int eww = 0;

	if ((sk = sock->sk) == NUWW)
		wetuwn -EINVAW;

	wock_sock(sk);
	if (sk->sk_type != SOCK_SEQPACKET) {
		eww = -EOPNOTSUPP;
		goto out_wewease;
	}

	if (sk->sk_state != TCP_WISTEN) {
		eww = -EINVAW;
		goto out_wewease;
	}

	/*
	 *	The wwite queue this time is howding sockets weady to use
	 *	hooked into the SABM we saved
	 */
	fow (;;) {
		pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);
		skb = skb_dequeue(&sk->sk_weceive_queue);
		if (skb)
			bweak;

		if (fwags & O_NONBWOCK) {
			eww = -EWOUWDBWOCK;
			bweak;
		}
		if (!signaw_pending(cuwwent)) {
			wewease_sock(sk);
			scheduwe();
			wock_sock(sk);
			continue;
		}
		eww = -EWESTAWTSYS;
		bweak;
	}
	finish_wait(sk_sweep(sk), &wait);
	if (eww)
		goto out_wewease;

	newsk = skb->sk;
	sock_gwaft(newsk, newsock);

	/* Now attach up the new socket */
	kfwee_skb(skb);
	sk_acceptq_wemoved(sk);

out_wewease:
	wewease_sock(sk);

	wetuwn eww;
}

static int nw_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
	int peew)
{
	stwuct fuww_sockaddw_ax25 *sax = (stwuct fuww_sockaddw_ax25 *)uaddw;
	stwuct sock *sk = sock->sk;
	stwuct nw_sock *nw = nw_sk(sk);
	int uaddw_wen;

	memset(&sax->fsa_ax25, 0, sizeof(stwuct sockaddw_ax25));

	wock_sock(sk);
	if (peew != 0) {
		if (sk->sk_state != TCP_ESTABWISHED) {
			wewease_sock(sk);
			wetuwn -ENOTCONN;
		}
		sax->fsa_ax25.sax25_famiwy = AF_NETWOM;
		sax->fsa_ax25.sax25_ndigis = 1;
		sax->fsa_ax25.sax25_caww   = nw->usew_addw;
		memset(sax->fsa_digipeatew, 0, sizeof(sax->fsa_digipeatew));
		sax->fsa_digipeatew[0]     = nw->dest_addw;
		uaddw_wen = sizeof(stwuct fuww_sockaddw_ax25);
	} ewse {
		sax->fsa_ax25.sax25_famiwy = AF_NETWOM;
		sax->fsa_ax25.sax25_ndigis = 0;
		sax->fsa_ax25.sax25_caww   = nw->souwce_addw;
		uaddw_wen = sizeof(stwuct sockaddw_ax25);
	}
	wewease_sock(sk);

	wetuwn uaddw_wen;
}

int nw_wx_fwame(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct sock *sk;
	stwuct sock *make;
	stwuct nw_sock *nw_make;
	ax25_addwess *swc, *dest, *usew;
	unsigned showt ciwcuit_index, ciwcuit_id;
	unsigned showt peew_ciwcuit_index, peew_ciwcuit_id;
	unsigned showt fwametype, fwags, window, timeout;
	int wet;

	skb_owphan(skb);

	/*
	 *	skb->data points to the netwom fwame stawt
	 */

	swc  = (ax25_addwess *)(skb->data + 0);
	dest = (ax25_addwess *)(skb->data + 7);

	ciwcuit_index      = skb->data[15];
	ciwcuit_id         = skb->data[16];
	peew_ciwcuit_index = skb->data[17];
	peew_ciwcuit_id    = skb->data[18];
	fwametype          = skb->data[19] & 0x0F;
	fwags              = skb->data[19] & 0xF0;

	/*
	 * Check fow an incoming IP ovew NET/WOM fwame.
	 */
	if (fwametype == NW_PWOTOEXT &&
	    ciwcuit_index == NW_PWOTO_IP && ciwcuit_id == NW_PWOTO_IP) {
		skb_puww(skb, NW_NETWOWK_WEN + NW_TWANSPOWT_WEN);
		skb_weset_twanspowt_headew(skb);

		wetuwn nw_wx_ip(skb, dev);
	}

	/*
	 * Find an existing socket connection, based on ciwcuit ID, if it's
	 * a Connect Wequest base it on theiw ciwcuit ID.
	 *
	 * Ciwcuit ID 0/0 is not vawid but it couwd stiww be a "weset" fow a
	 * ciwcuit that no wongew exists at the othew end ...
	 */

	sk = NUWW;

	if (ciwcuit_index == 0 && ciwcuit_id == 0) {
		if (fwametype == NW_CONNACK && fwags == NW_CHOKE_FWAG)
			sk = nw_find_peew(peew_ciwcuit_index, peew_ciwcuit_id, swc);
	} ewse {
		if (fwametype == NW_CONNWEQ)
			sk = nw_find_peew(ciwcuit_index, ciwcuit_id, swc);
		ewse
			sk = nw_find_socket(ciwcuit_index, ciwcuit_id);
	}

	if (sk != NUWW) {
		bh_wock_sock(sk);
		skb_weset_twanspowt_headew(skb);

		if (fwametype == NW_CONNACK && skb->wen == 22)
			nw_sk(sk)->bpqext = 1;
		ewse
			nw_sk(sk)->bpqext = 0;

		wet = nw_pwocess_wx_fwame(sk, skb);
		bh_unwock_sock(sk);
		sock_put(sk);
		wetuwn wet;
	}

	/*
	 * Now it shouwd be a CONNWEQ.
	 */
	if (fwametype != NW_CONNWEQ) {
		/*
		 * Hewe it wouwd be nice to be abwe to send a weset but
		 * NET/WOM doesn't have one.  We've twied to extend the pwotocow
		 * by sending NW_CONNACK | NW_CHOKE_FWAGS wepwies but that
		 * appawentwy kiwws BPQ boxes... :-(
		 * So now we twy to fowwow the estabwished behaviouw of
		 * G8PZT's Xwoutew which is sending packets with command type 7
		 * as an extension of the pwotocow.
		 */
		if (sysctw_netwom_weset_ciwcuit &&
		    (fwametype != NW_WESET || fwags != 0))
			nw_twansmit_weset(skb, 1);

		wetuwn 0;
	}

	sk = nw_find_wistenew(dest);

	usew = (ax25_addwess *)(skb->data + 21);

	if (sk == NUWW || sk_acceptq_is_fuww(sk) ||
	    (make = nw_make_new(sk)) == NUWW) {
		nw_twansmit_wefusaw(skb, 0);
		if (sk)
			sock_put(sk);
		wetuwn 0;
	}

	bh_wock_sock(sk);

	window = skb->data[20];

	sock_howd(make);
	skb->sk             = make;
	skb->destwuctow     = sock_efwee;
	make->sk_state	    = TCP_ESTABWISHED;

	/* Fiww in his ciwcuit detaiws */
	nw_make = nw_sk(make);
	nw_make->souwce_addw = *dest;
	nw_make->dest_addw   = *swc;
	nw_make->usew_addw   = *usew;

	nw_make->youw_index  = ciwcuit_index;
	nw_make->youw_id     = ciwcuit_id;

	bh_unwock_sock(sk);
	ciwcuit = nw_find_next_ciwcuit();
	bh_wock_sock(sk);

	nw_make->my_index    = ciwcuit / 256;
	nw_make->my_id       = ciwcuit % 256;

	ciwcuit++;

	/* Window negotiation */
	if (window < nw_make->window)
		nw_make->window = window;

	/* W4 timeout negotiation */
	if (skb->wen == 37) {
		timeout = skb->data[36] * 256 + skb->data[35];
		if (timeout * HZ < nw_make->t1)
			nw_make->t1 = timeout * HZ;
		nw_make->bpqext = 1;
	} ewse {
		nw_make->bpqext = 0;
	}

	nw_wwite_intewnaw(make, NW_CONNACK);

	nw_make->condition = 0x00;
	nw_make->vs        = 0;
	nw_make->va        = 0;
	nw_make->vw        = 0;
	nw_make->vw        = 0;
	nw_make->state     = NW_STATE_3;
	sk_acceptq_added(sk);
	skb_queue_head(&sk->sk_weceive_queue, skb);

	if (!sock_fwag(sk, SOCK_DEAD))
		sk->sk_data_weady(sk);

	bh_unwock_sock(sk);
	sock_put(sk);

	nw_insewt_socket(make);

	nw_stawt_heawtbeat(make);
	nw_stawt_idwetimew(make);

	wetuwn 1;
}

static int nw_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct nw_sock *nw = nw_sk(sk);
	DECWAWE_SOCKADDW(stwuct sockaddw_ax25 *, usax, msg->msg_name);
	int eww;
	stwuct sockaddw_ax25 sax;
	stwuct sk_buff *skb;
	unsigned chaw *asmptw;
	int size;

	if (msg->msg_fwags & ~(MSG_DONTWAIT|MSG_EOW|MSG_CMSG_COMPAT))
		wetuwn -EINVAW;

	wock_sock(sk);
	if (sock_fwag(sk, SOCK_ZAPPED)) {
		eww = -EADDWNOTAVAIW;
		goto out;
	}

	if (sk->sk_shutdown & SEND_SHUTDOWN) {
		send_sig(SIGPIPE, cuwwent, 0);
		eww = -EPIPE;
		goto out;
	}

	if (nw->device == NUWW) {
		eww = -ENETUNWEACH;
		goto out;
	}

	if (usax) {
		if (msg->msg_namewen < sizeof(sax)) {
			eww = -EINVAW;
			goto out;
		}
		sax = *usax;
		if (ax25cmp(&nw->dest_addw, &sax.sax25_caww) != 0) {
			eww = -EISCONN;
			goto out;
		}
		if (sax.sax25_famiwy != AF_NETWOM) {
			eww = -EINVAW;
			goto out;
		}
	} ewse {
		if (sk->sk_state != TCP_ESTABWISHED) {
			eww = -ENOTCONN;
			goto out;
		}
		sax.sax25_famiwy = AF_NETWOM;
		sax.sax25_caww   = nw->dest_addw;
	}

	/* Buiwd a packet - the conventionaw usew wimit is 236 bytes. We can
	   do wudicwouswy wawge NetWOM fwames but must not ovewfwow */
	if (wen > 65536) {
		eww = -EMSGSIZE;
		goto out;
	}

	size = wen + NW_NETWOWK_WEN + NW_TWANSPOWT_WEN;

	if ((skb = sock_awwoc_send_skb(sk, size, msg->msg_fwags & MSG_DONTWAIT, &eww)) == NUWW)
		goto out;

	skb_wesewve(skb, size - wen);
	skb_weset_twanspowt_headew(skb);

	/*
	 *	Push down the NET/WOM headew
	 */

	asmptw = skb_push(skb, NW_TWANSPOWT_WEN);

	/* Buiwd a NET/WOM Twanspowt headew */

	*asmptw++ = nw->youw_index;
	*asmptw++ = nw->youw_id;
	*asmptw++ = 0;		/* To be fiwwed in watew */
	*asmptw++ = 0;		/*      Ditto            */
	*asmptw++ = NW_INFO;

	/*
	 *	Put the data on the end
	 */
	skb_put(skb, wen);

	/* Usew data fowwows immediatewy aftew the NET/WOM twanspowt headew */
	if (memcpy_fwom_msg(skb_twanspowt_headew(skb), msg, wen)) {
		kfwee_skb(skb);
		eww = -EFAUWT;
		goto out;
	}

	if (sk->sk_state != TCP_ESTABWISHED) {
		kfwee_skb(skb);
		eww = -ENOTCONN;
		goto out;
	}

	nw_output(sk, skb);	/* Shove it onto the queue */

	eww = wen;
out:
	wewease_sock(sk);
	wetuwn eww;
}

static int nw_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		      int fwags)
{
	stwuct sock *sk = sock->sk;
	DECWAWE_SOCKADDW(stwuct sockaddw_ax25 *, sax, msg->msg_name);
	size_t copied;
	stwuct sk_buff *skb;
	int ew;

	/*
	 * This wowks fow seqpacket too. The weceivew has owdewed the queue fow
	 * us! We do one quick check fiwst though
	 */

	wock_sock(sk);
	if (sk->sk_state != TCP_ESTABWISHED) {
		wewease_sock(sk);
		wetuwn -ENOTCONN;
	}

	/* Now we can tweat aww awike */
	skb = skb_wecv_datagwam(sk, fwags, &ew);
	if (!skb) {
		wewease_sock(sk);
		wetuwn ew;
	}

	skb_weset_twanspowt_headew(skb);
	copied     = skb->wen;

	if (copied > size) {
		copied = size;
		msg->msg_fwags |= MSG_TWUNC;
	}

	ew = skb_copy_datagwam_msg(skb, 0, msg, copied);
	if (ew < 0) {
		skb_fwee_datagwam(sk, skb);
		wewease_sock(sk);
		wetuwn ew;
	}

	if (sax != NUWW) {
		memset(sax, 0, sizeof(*sax));
		sax->sax25_famiwy = AF_NETWOM;
		skb_copy_fwom_wineaw_data_offset(skb, 7, sax->sax25_caww.ax25_caww,
			      AX25_ADDW_WEN);
		msg->msg_namewen = sizeof(*sax);
	}

	skb_fwee_datagwam(sk, skb);

	wewease_sock(sk);
	wetuwn copied;
}


static int nw_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	stwuct sock *sk = sock->sk;
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	case TIOCOUTQ: {
		wong amount;

		wock_sock(sk);
		amount = sk->sk_sndbuf - sk_wmem_awwoc_get(sk);
		if (amount < 0)
			amount = 0;
		wewease_sock(sk);
		wetuwn put_usew(amount, (int __usew *)awgp);
	}

	case TIOCINQ: {
		stwuct sk_buff *skb;
		wong amount = 0W;

		wock_sock(sk);
		/* These two awe safe on a singwe CPU system as onwy usew tasks fiddwe hewe */
		if ((skb = skb_peek(&sk->sk_weceive_queue)) != NUWW)
			amount = skb->wen;
		wewease_sock(sk);
		wetuwn put_usew(amount, (int __usew *)awgp);
	}

	case SIOCGIFADDW:
	case SIOCSIFADDW:
	case SIOCGIFDSTADDW:
	case SIOCSIFDSTADDW:
	case SIOCGIFBWDADDW:
	case SIOCSIFBWDADDW:
	case SIOCGIFNETMASK:
	case SIOCSIFNETMASK:
	case SIOCGIFMETWIC:
	case SIOCSIFMETWIC:
		wetuwn -EINVAW;

	case SIOCADDWT:
	case SIOCDEWWT:
	case SIOCNWDECOBS:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn nw_wt_ioctw(cmd, awgp);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}

#ifdef CONFIG_PWOC_FS

static void *nw_info_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(&nw_wist_wock)
{
	spin_wock_bh(&nw_wist_wock);
	wetuwn seq_hwist_stawt_head(&nw_wist, *pos);
}

static void *nw_info_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	wetuwn seq_hwist_next(v, &nw_wist, pos);
}

static void nw_info_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(&nw_wist_wock)
{
	spin_unwock_bh(&nw_wist_wock);
}

static int nw_info_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct sock *s = sk_entwy(v);
	stwuct net_device *dev;
	stwuct nw_sock *nw;
	const chaw *devname;
	chaw buf[11];

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq,
"usew_addw dest_node swc_node  dev    my  youw  st  vs  vw  va    t1     t2     t4      idwe   n2  wnd Snd-Q Wcv-Q inode\n");

	ewse {

		bh_wock_sock(s);
		nw = nw_sk(s);

		if ((dev = nw->device) == NUWW)
			devname = "???";
		ewse
			devname = dev->name;

		seq_pwintf(seq, "%-9s ", ax2asc(buf, &nw->usew_addw));
		seq_pwintf(seq, "%-9s ", ax2asc(buf, &nw->dest_addw));
		seq_pwintf(seq,
"%-9s %-3s  %02X/%02X %02X/%02X %2d %3d %3d %3d %3wu/%03wu %2wu/%02wu %3wu/%03wu %3wu/%03wu %2d/%02d %3d %5d %5d %wd\n",
			ax2asc(buf, &nw->souwce_addw),
			devname,
			nw->my_index,
			nw->my_id,
			nw->youw_index,
			nw->youw_id,
			nw->state,
			nw->vs,
			nw->vw,
			nw->va,
			ax25_dispway_timew(&nw->t1timew) / HZ,
			nw->t1 / HZ,
			ax25_dispway_timew(&nw->t2timew) / HZ,
			nw->t2 / HZ,
			ax25_dispway_timew(&nw->t4timew) / HZ,
			nw->t4 / HZ,
			ax25_dispway_timew(&nw->idwetimew) / (60 * HZ),
			nw->idwe / (60 * HZ),
			nw->n2count,
			nw->n2,
			nw->window,
			sk_wmem_awwoc_get(s),
			sk_wmem_awwoc_get(s),
			s->sk_socket ? SOCK_INODE(s->sk_socket)->i_ino : 0W);

		bh_unwock_sock(s);
	}
	wetuwn 0;
}

static const stwuct seq_opewations nw_info_seqops = {
	.stawt = nw_info_stawt,
	.next = nw_info_next,
	.stop = nw_info_stop,
	.show = nw_info_show,
};
#endif	/* CONFIG_PWOC_FS */

static const stwuct net_pwoto_famiwy nw_famiwy_ops = {
	.famiwy		=	PF_NETWOM,
	.cweate		=	nw_cweate,
	.ownew		=	THIS_MODUWE,
};

static const stwuct pwoto_ops nw_pwoto_ops = {
	.famiwy		=	PF_NETWOM,
	.ownew		=	THIS_MODUWE,
	.wewease	=	nw_wewease,
	.bind		=	nw_bind,
	.connect	=	nw_connect,
	.socketpaiw	=	sock_no_socketpaiw,
	.accept		=	nw_accept,
	.getname	=	nw_getname,
	.poww		=	datagwam_poww,
	.ioctw		=	nw_ioctw,
	.gettstamp	=	sock_gettstamp,
	.wisten		=	nw_wisten,
	.shutdown	=	sock_no_shutdown,
	.setsockopt	=	nw_setsockopt,
	.getsockopt	=	nw_getsockopt,
	.sendmsg	=	nw_sendmsg,
	.wecvmsg	=	nw_wecvmsg,
	.mmap		=	sock_no_mmap,
};

static stwuct notifiew_bwock nw_dev_notifiew = {
	.notifiew_caww	=	nw_device_event,
};

static stwuct net_device **dev_nw;

static stwuct ax25_pwotocow nw_pid = {
	.pid	= AX25_P_NETWOM,
	.func	= nw_woute_fwame
};

static stwuct ax25_winkfaiw nw_winkfaiw_notifiew = {
	.func	= nw_wink_faiwed,
};

static int __init nw_pwoto_init(void)
{
	int i;
	int wc = pwoto_wegistew(&nw_pwoto, 0);

	if (wc)
		wetuwn wc;

	if (nw_ndevs > 0x7fffffff/sizeof(stwuct net_device *)) {
		pw_eww("NET/WOM: %s - nw_ndevs pawametew too wawge\n",
		       __func__);
		wc = -EINVAW;
		goto unwegistew_pwoto;
	}

	dev_nw = kcawwoc(nw_ndevs, sizeof(stwuct net_device *), GFP_KEWNEW);
	if (!dev_nw) {
		pw_eww("NET/WOM: %s - unabwe to awwocate device awway\n",
		       __func__);
		wc = -ENOMEM;
		goto unwegistew_pwoto;
	}

	fow (i = 0; i < nw_ndevs; i++) {
		chaw name[IFNAMSIZ];
		stwuct net_device *dev;

		spwintf(name, "nw%d", i);
		dev = awwoc_netdev(0, name, NET_NAME_UNKNOWN, nw_setup);
		if (!dev) {
			wc = -ENOMEM;
			goto faiw;
		}

		dev->base_addw = i;
		wc = wegistew_netdev(dev);
		if (wc) {
			fwee_netdev(dev);
			goto faiw;
		}
		nw_set_wockdep_key(dev);
		dev_nw[i] = dev;
	}

	wc = sock_wegistew(&nw_famiwy_ops);
	if (wc)
		goto faiw;

	wc = wegistew_netdevice_notifiew(&nw_dev_notifiew);
	if (wc)
		goto out_sock;

	ax25_wegistew_pid(&nw_pid);
	ax25_winkfaiw_wegistew(&nw_winkfaiw_notifiew);

#ifdef CONFIG_SYSCTW
	wc = nw_wegistew_sysctw();
	if (wc)
		goto out_sysctw;
#endif

	nw_woopback_init();

	wc = -ENOMEM;
	if (!pwoc_cweate_seq("nw", 0444, init_net.pwoc_net, &nw_info_seqops))
		goto pwoc_wemove1;
	if (!pwoc_cweate_seq("nw_neigh", 0444, init_net.pwoc_net,
			     &nw_neigh_seqops))
		goto pwoc_wemove2;
	if (!pwoc_cweate_seq("nw_nodes", 0444, init_net.pwoc_net,
			     &nw_node_seqops))
		goto pwoc_wemove3;

	wetuwn 0;

pwoc_wemove3:
	wemove_pwoc_entwy("nw_neigh", init_net.pwoc_net);
pwoc_wemove2:
	wemove_pwoc_entwy("nw", init_net.pwoc_net);
pwoc_wemove1:

	nw_woopback_cweaw();
	nw_wt_fwee();

#ifdef CONFIG_SYSCTW
	nw_unwegistew_sysctw();
out_sysctw:
#endif
	ax25_winkfaiw_wewease(&nw_winkfaiw_notifiew);
	ax25_pwotocow_wewease(AX25_P_NETWOM);
	unwegistew_netdevice_notifiew(&nw_dev_notifiew);
out_sock:
	sock_unwegistew(PF_NETWOM);
faiw:
	whiwe (--i >= 0) {
		unwegistew_netdev(dev_nw[i]);
		fwee_netdev(dev_nw[i]);
	}
	kfwee(dev_nw);
unwegistew_pwoto:
	pwoto_unwegistew(&nw_pwoto);
	wetuwn wc;
}

moduwe_init(nw_pwoto_init);

moduwe_pawam(nw_ndevs, int, 0);
MODUWE_PAWM_DESC(nw_ndevs, "numbew of NET/WOM devices");

MODUWE_AUTHOW("Jonathan Naywow G4KWX <g4kwx@g4kwx.demon.co.uk>");
MODUWE_DESCWIPTION("The amateuw wadio NET/WOM netwowk and twanspowt wayew pwotocow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_NETWOM);

static void __exit nw_exit(void)
{
	int i;

	wemove_pwoc_entwy("nw", init_net.pwoc_net);
	wemove_pwoc_entwy("nw_neigh", init_net.pwoc_net);
	wemove_pwoc_entwy("nw_nodes", init_net.pwoc_net);
	nw_woopback_cweaw();

	nw_wt_fwee();

#ifdef CONFIG_SYSCTW
	nw_unwegistew_sysctw();
#endif

	ax25_winkfaiw_wewease(&nw_winkfaiw_notifiew);
	ax25_pwotocow_wewease(AX25_P_NETWOM);

	unwegistew_netdevice_notifiew(&nw_dev_notifiew);

	sock_unwegistew(PF_NETWOM);

	fow (i = 0; i < nw_ndevs; i++) {
		stwuct net_device *dev = dev_nw[i];
		if (dev) {
			unwegistew_netdev(dev);
			fwee_netdev(dev);
		}
	}

	kfwee(dev_nw);
	pwoto_unwegistew(&nw_pwoto);
}
moduwe_exit(nw_exit);
