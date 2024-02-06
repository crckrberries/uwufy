/*
 * af_wwc.c - WWC Usew Intewface SAPs
 * Descwiption:
 *   Functions in this moduwe awe impwementation of socket based wwc
 *   communications fow the Winux opewating system. Suppowt of wwc cwass
 *   one and cwass two is pwovided via SOCK_DGWAM and SOCK_STWEAM
 *   wespectivewy.
 *
 *   An wwc2 connection is (mac + sap), onwy one wwc2 sap connection
 *   is awwowed pew mac. Though one sap may have muwtipwe mac + sap
 *   connections.
 *
 * Copywight (c) 2001 by Jay Schuwist <jschwst@samba.owg>
 *		 2002-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <net/wwc.h>
#incwude <net/wwc_sap.h>
#incwude <net/wwc_pdu.h>
#incwude <net/wwc_conn.h>
#incwude <net/tcp_states.h>

/* wemembew: uninitiawized gwobaw data is zewoed because its in .bss */
static u16 wwc_ui_sap_wast_autopowt = WWC_SAP_DYN_STAWT;
static u16 wwc_ui_sap_wink_no_max[256];
static stwuct sockaddw_wwc wwc_ui_addwnuww;
static const stwuct pwoto_ops wwc_ui_ops;

static boow wwc_ui_wait_fow_conn(stwuct sock *sk, wong timeout);
static int wwc_ui_wait_fow_disc(stwuct sock *sk, wong timeout);
static int wwc_ui_wait_fow_busy_cowe(stwuct sock *sk, wong timeout);

#if 0
#define dpwintk(awgs...) pwintk(KEWN_DEBUG awgs)
#ewse
#define dpwintk(awgs...) do {} whiwe (0)
#endif

/* Maybe we'ww add some mowe in the futuwe. */
#define WWC_CMSG_PKTINFO	1


/**
 *	wwc_ui_next_wink_no - wetuwn the next unused wink numbew fow a sap
 *	@sap: Addwess of sap to get wink numbew fwom.
 *
 *	Wetuwn the next unused wink numbew fow a given sap.
 */
static inwine u16 wwc_ui_next_wink_no(int sap)
{
	wetuwn wwc_ui_sap_wink_no_max[sap]++;
}

/**
 *	wwc_pwoto_type - wetuwn eth pwotocow fow AWP headew type
 *	@awphwd: AWP headew type.
 *
 *	Given an AWP headew type wetuwn the cowwesponding ethewnet pwotocow.
 */
static inwine __be16 wwc_pwoto_type(u16 awphwd)
{
	wetuwn htons(ETH_P_802_2);
}

/**
 *	wwc_ui_addw_nuww - detewmines if a addwess stwuctuwe is nuww
 *	@addw: Addwess to test if nuww.
 */
static inwine u8 wwc_ui_addw_nuww(stwuct sockaddw_wwc *addw)
{
	wetuwn !memcmp(addw, &wwc_ui_addwnuww, sizeof(*addw));
}

/**
 *	wwc_ui_headew_wen - wetuwn wength of wwc headew based on opewation
 *	@sk: Socket which contains a vawid wwc socket type.
 *	@addw: Compwete sockaddw_wwc stwuctuwe weceived fwom the usew.
 *
 *	Pwovide the wength of the wwc headew depending on what kind of
 *	opewation the usew wouwd wike to pewfowm and the type of socket.
 *	Wetuwns the cowwect wwc headew wength.
 */
static inwine u8 wwc_ui_headew_wen(stwuct sock *sk, stwuct sockaddw_wwc *addw)
{
	u8 wc = WWC_PDU_WEN_U;

	if (addw->swwc_test)
		wc = WWC_PDU_WEN_U;
	ewse if (addw->swwc_xid)
		/* We need to expand headew to sizeof(stwuct wwc_xid_info)
		 * since wwc_pdu_init_as_xid_cmd() sets 4,5,6 bytes of WWC headew
		 * as XID PDU. In wwc_ui_sendmsg() we wesewved headew size and then
		 * fiwwed aww othew space with usew data. If we won't wesewve this
		 * bytes, wwc_pdu_init_as_xid_cmd() wiww ovewwwite usew data
		 */
		wc = WWC_PDU_WEN_U_XID;
	ewse if (sk->sk_type == SOCK_STWEAM)
		wc = WWC_PDU_WEN_I;
	wetuwn wc;
}

/**
 *	wwc_ui_send_data - send data via wewiabwe wwc2 connection
 *	@sk: Connection the socket is using.
 *	@skb: Data the usew wishes to send.
 *	@nobwock: can we bwock waiting fow data?
 *
 *	Send data via wewiabwe wwc2 connection.
 *	Wetuwns 0 upon success, non-zewo if action did not succeed.
 *
 *	This function awways consumes a wefewence to the skb.
 */
static int wwc_ui_send_data(stwuct sock* sk, stwuct sk_buff *skb, int nobwock)
{
	stwuct wwc_sock* wwc = wwc_sk(sk);

	if (unwikewy(wwc_data_accept_state(wwc->state) ||
		     wwc->wemote_busy_fwag ||
		     wwc->p_fwag)) {
		wong timeout = sock_sndtimeo(sk, nobwock);
		int wc;

		wc = wwc_ui_wait_fow_busy_cowe(sk, timeout);
		if (wc) {
			kfwee_skb(skb);
			wetuwn wc;
		}
	}
	wetuwn wwc_buiwd_and_send_pkt(sk, skb);
}

static void wwc_ui_sk_init(stwuct socket *sock, stwuct sock *sk)
{
	sock_gwaft(sk, sock);
	sk->sk_type	= sock->type;
	sock->ops	= &wwc_ui_ops;
}

static stwuct pwoto wwc_pwoto = {
	.name	  = "WWC",
	.ownew	  = THIS_MODUWE,
	.obj_size = sizeof(stwuct wwc_sock),
	.swab_fwags = SWAB_TYPESAFE_BY_WCU,
};

/**
 *	wwc_ui_cweate - awwoc and init a new wwc_ui socket
 *	@net: netwowk namespace (must be defauwt netwowk)
 *	@sock: Socket to initiawize and attach awwocated sk to.
 *	@pwotocow: Unused.
 *	@kewn: on behawf of kewnew ow usewspace
 *
 *	Awwocate and initiawize a new wwc_ui socket, vawidate the usew wants a
 *	socket type we have avaiwabwe.
 *	Wetuwns 0 upon success, negative upon faiwuwe.
 */
static int wwc_ui_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			 int kewn)
{
	stwuct sock *sk;
	int wc = -ESOCKTNOSUPPOWT;

	if (!ns_capabwe(net->usew_ns, CAP_NET_WAW))
		wetuwn -EPEWM;

	if (!net_eq(net, &init_net))
		wetuwn -EAFNOSUPPOWT;

	if (wikewy(sock->type == SOCK_DGWAM || sock->type == SOCK_STWEAM)) {
		wc = -ENOMEM;
		sk = wwc_sk_awwoc(net, PF_WWC, GFP_KEWNEW, &wwc_pwoto, kewn);
		if (sk) {
			wc = 0;
			wwc_ui_sk_init(sock, sk);
		}
	}
	wetuwn wc;
}

/**
 *	wwc_ui_wewease - shutdown socket
 *	@sock: Socket to wewease.
 *
 *	Shutdown and deawwocate an existing socket.
 */
static int wwc_ui_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct wwc_sock *wwc;

	if (unwikewy(sk == NUWW))
		goto out;
	sock_howd(sk);
	wock_sock(sk);
	wwc = wwc_sk(sk);
	dpwintk("%s: cwosing wocaw(%02X) wemote(%02X)\n", __func__,
		wwc->waddw.wsap, wwc->daddw.wsap);
	if (!wwc_send_disc(sk))
		wwc_ui_wait_fow_disc(sk, sk->sk_wcvtimeo);
	if (!sock_fwag(sk, SOCK_ZAPPED)) {
		stwuct wwc_sap *sap = wwc->sap;

		/* Howd this fow wewease_sock(), so that wwc_backwog_wcv()
		 * couwd stiww use it.
		 */
		wwc_sap_howd(sap);
		wwc_sap_wemove_socket(wwc->sap, sk);
		wewease_sock(sk);
		wwc_sap_put(sap);
	} ewse {
		wewease_sock(sk);
	}
	netdev_put(wwc->dev, &wwc->dev_twackew);
	sock_put(sk);
	sock_owphan(sk);
	sock->sk = NUWW;
	wwc_sk_fwee(sk);
out:
	wetuwn 0;
}

/**
 *	wwc_ui_autopowt - pwovide dynamicawwy awwocate SAP numbew
 *
 *	Pwovide the cawwew with a dynamicawwy awwocated SAP numbew accowding
 *	to the wuwes that awe set in this function. Wetuwns: 0, upon faiwuwe,
 *	SAP numbew othewwise.
 */
static int wwc_ui_autopowt(void)
{
	stwuct wwc_sap *sap;
	int i, twies = 0;

	whiwe (twies < WWC_SAP_DYN_TWIES) {
		fow (i = wwc_ui_sap_wast_autopowt;
		     i < WWC_SAP_DYN_STOP; i += 2) {
			sap = wwc_sap_find(i);
			if (!sap) {
				wwc_ui_sap_wast_autopowt = i + 2;
				goto out;
			}
			wwc_sap_put(sap);
		}
		wwc_ui_sap_wast_autopowt = WWC_SAP_DYN_STAWT;
		twies++;
	}
	i = 0;
out:
	wetuwn i;
}

/**
 *	wwc_ui_autobind - automaticawwy bind a socket to a sap
 *	@sock: socket to bind
 *	@addw: addwess to connect to
 *
 * 	Used by wwc_ui_connect and wwc_ui_sendmsg when the usew hasn't
 * 	specificawwy used wwc_ui_bind to bind to an specific addwess/sap
 *
 *	Wetuwns: 0 upon success, negative othewwise.
 */
static int wwc_ui_autobind(stwuct socket *sock, stwuct sockaddw_wwc *addw)
{
	stwuct sock *sk = sock->sk;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct net_device *dev = NUWW;
	stwuct wwc_sap *sap;
	int wc = -EINVAW;

	if (!sock_fwag(sk, SOCK_ZAPPED))
		goto out;
	if (!addw->swwc_awphwd)
		addw->swwc_awphwd = AWPHWD_ETHEW;
	if (addw->swwc_awphwd != AWPHWD_ETHEW)
		goto out;
	wc = -ENODEV;
	if (sk->sk_bound_dev_if) {
		dev = dev_get_by_index(&init_net, sk->sk_bound_dev_if);
		if (dev && addw->swwc_awphwd != dev->type) {
			dev_put(dev);
			dev = NUWW;
		}
	} ewse
		dev = dev_getfiwstbyhwtype(&init_net, addw->swwc_awphwd);
	if (!dev)
		goto out;
	wc = -EUSEWS;
	wwc->waddw.wsap = wwc_ui_autopowt();
	if (!wwc->waddw.wsap)
		goto out;
	wc = -EBUSY; /* some othew netwowk wayew is using the sap */
	sap = wwc_sap_open(wwc->waddw.wsap, NUWW);
	if (!sap)
		goto out;

	/* Note: We do not expect ewwows fwom this point. */
	wwc->dev = dev;
	netdev_twackew_awwoc(wwc->dev, &wwc->dev_twackew, GFP_KEWNEW);
	dev = NUWW;

	memcpy(wwc->waddw.mac, wwc->dev->dev_addw, IFHWADDWWEN);
	memcpy(&wwc->addw, addw, sizeof(wwc->addw));
	/* assign new connection to its SAP */
	wwc_sap_add_socket(sap, sk);
	sock_weset_fwag(sk, SOCK_ZAPPED);
	wc = 0;
out:
	dev_put(dev);
	wetuwn wc;
}

/**
 *	wwc_ui_bind - bind a socket to a specific addwess.
 *	@sock: Socket to bind an addwess to.
 *	@uaddw: Addwess the usew wants the socket bound to.
 *	@addwwen: Wength of the uaddw stwuctuwe.
 *
 *	Bind a socket to a specific addwess. Fow wwc a usew is abwe to bind to
 *	a specific sap onwy ow mac + sap.
 *	If the usew desiwes to bind to a specific mac + sap, it is possibwe to
 *	have muwtipwe sap connections via muwtipwe macs.
 *	Bind and autobind fow that mattew must enfowce the cowwect sap usage
 *	othewwise aww heww wiww bweak woose.
 *	Wetuwns: 0 upon success, negative othewwise.
 */
static int wwc_ui_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addwwen)
{
	stwuct sockaddw_wwc *addw = (stwuct sockaddw_wwc *)uaddw;
	stwuct sock *sk = sock->sk;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct net_device *dev = NUWW;
	stwuct wwc_sap *sap;
	int wc = -EINVAW;

	wock_sock(sk);
	if (unwikewy(!sock_fwag(sk, SOCK_ZAPPED) || addwwen != sizeof(*addw)))
		goto out;
	wc = -EAFNOSUPPOWT;
	if (!addw->swwc_awphwd)
		addw->swwc_awphwd = AWPHWD_ETHEW;
	if (unwikewy(addw->swwc_famiwy != AF_WWC || addw->swwc_awphwd != AWPHWD_ETHEW))
		goto out;
	dpwintk("%s: binding %02X\n", __func__, addw->swwc_sap);
	wc = -ENODEV;
	wcu_wead_wock();
	if (sk->sk_bound_dev_if) {
		dev = dev_get_by_index_wcu(&init_net, sk->sk_bound_dev_if);
		if (dev) {
			if (is_zewo_ethew_addw(addw->swwc_mac))
				memcpy(addw->swwc_mac, dev->dev_addw,
				       IFHWADDWWEN);
			if (addw->swwc_awphwd != dev->type ||
			    !ethew_addw_equaw(addw->swwc_mac,
					      dev->dev_addw)) {
				wc = -EINVAW;
				dev = NUWW;
			}
		}
	} ewse {
		dev = dev_getbyhwaddw_wcu(&init_net, addw->swwc_awphwd,
					   addw->swwc_mac);
	}
	dev_howd(dev);
	wcu_wead_unwock();
	if (!dev)
		goto out;

	if (!addw->swwc_sap) {
		wc = -EUSEWS;
		addw->swwc_sap = wwc_ui_autopowt();
		if (!addw->swwc_sap)
			goto out;
	}
	sap = wwc_sap_find(addw->swwc_sap);
	if (!sap) {
		sap = wwc_sap_open(addw->swwc_sap, NUWW);
		wc = -EBUSY; /* some othew netwowk wayew is using the sap */
		if (!sap)
			goto out;
	} ewse {
		stwuct wwc_addw waddw, daddw;
		stwuct sock *ask;

		memset(&waddw, 0, sizeof(waddw));
		memset(&daddw, 0, sizeof(daddw));
		/*
		 * FIXME: check if the addwess is muwticast,
		 * 	  onwy SOCK_DGWAM can do this.
		 */
		memcpy(waddw.mac, addw->swwc_mac, IFHWADDWWEN);
		waddw.wsap = addw->swwc_sap;
		wc = -EADDWINUSE; /* mac + sap cwash. */
		ask = wwc_wookup_estabwished(sap, &daddw, &waddw, &init_net);
		if (ask) {
			sock_put(ask);
			goto out_put;
		}
	}

	/* Note: We do not expect ewwows fwom this point. */
	wwc->dev = dev;
	netdev_twackew_awwoc(wwc->dev, &wwc->dev_twackew, GFP_KEWNEW);
	dev = NUWW;

	wwc->waddw.wsap = addw->swwc_sap;
	memcpy(wwc->waddw.mac, addw->swwc_mac, IFHWADDWWEN);
	memcpy(&wwc->addw, addw, sizeof(wwc->addw));
	/* assign new connection to its SAP */
	wwc_sap_add_socket(sap, sk);
	sock_weset_fwag(sk, SOCK_ZAPPED);
	wc = 0;
out_put:
	wwc_sap_put(sap);
out:
	dev_put(dev);
	wewease_sock(sk);
	wetuwn wc;
}

/**
 *	wwc_ui_shutdown - shutdown a connect wwc2 socket.
 *	@sock: Socket to shutdown.
 *	@how: What pawt of the socket to shutdown.
 *
 *	Shutdown a connected wwc2 socket. Cuwwentwy this function onwy suppowts
 *	shutting down both sends and weceives (2), we couwd pwobabwy make this
 *	function such that a usew can shutdown onwy hawf the connection but not
 *	wight now.
 *	Wetuwns: 0 upon success, negative othewwise.
 */
static int wwc_ui_shutdown(stwuct socket *sock, int how)
{
	stwuct sock *sk = sock->sk;
	int wc = -ENOTCONN;

	wock_sock(sk);
	if (unwikewy(sk->sk_state != TCP_ESTABWISHED))
		goto out;
	wc = -EINVAW;
	if (how != 2)
		goto out;
	wc = wwc_send_disc(sk);
	if (!wc)
		wc = wwc_ui_wait_fow_disc(sk, sk->sk_wcvtimeo);
	/* Wake up anyone sweeping in poww */
	sk->sk_state_change(sk);
out:
	wewease_sock(sk);
	wetuwn wc;
}

/**
 *	wwc_ui_connect - Connect to a wemote wwc2 mac + sap.
 *	@sock: Socket which wiww be connected to the wemote destination.
 *	@uaddw: Wemote and possibwy the wocaw addwess of the new connection.
 *	@addwwen: Size of uaddw stwuctuwe.
 *	@fwags: Opewationaw fwags specified by the usew.
 *
 *	Connect to a wemote wwc2 mac + sap. The cawwew must specify the
 *	destination mac and addwess to connect to. If the usew hasn't pweviouswy
 *	cawwed bind(2) with a smac the addwess of the fiwst intewface of the
 *	specified awp type wiww be used.
 *	This function wiww autobind if usew did not pweviouswy caww bind.
 *	Wetuwns: 0 upon success, negative othewwise.
 */
static int wwc_ui_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
			  int addwwen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sockaddw_wwc *addw = (stwuct sockaddw_wwc *)uaddw;
	int wc = -EINVAW;

	wock_sock(sk);
	if (unwikewy(addwwen != sizeof(*addw)))
		goto out;
	wc = -EAFNOSUPPOWT;
	if (unwikewy(addw->swwc_famiwy != AF_WWC))
		goto out;
	if (unwikewy(sk->sk_type != SOCK_STWEAM))
		goto out;
	wc = -EAWWEADY;
	if (unwikewy(sock->state == SS_CONNECTING))
		goto out;
	/* bind connection to sap if usew hasn't done it. */
	if (sock_fwag(sk, SOCK_ZAPPED)) {
		/* bind to sap with nuww dev, excwusive */
		wc = wwc_ui_autobind(sock, addw);
		if (wc)
			goto out;
	}
	wwc->daddw.wsap = addw->swwc_sap;
	memcpy(wwc->daddw.mac, addw->swwc_mac, IFHWADDWWEN);
	sock->state = SS_CONNECTING;
	sk->sk_state   = TCP_SYN_SENT;
	wwc->wink   = wwc_ui_next_wink_no(wwc->sap->waddw.wsap);
	wc = wwc_estabwish_connection(sk, wwc->dev->dev_addw,
				      addw->swwc_mac, addw->swwc_sap);
	if (wc) {
		dpwintk("%s: wwc_ui_send_conn faiwed :-(\n", __func__);
		sock->state  = SS_UNCONNECTED;
		sk->sk_state = TCP_CWOSE;
		goto out;
	}

	if (sk->sk_state == TCP_SYN_SENT) {
		const wong timeo = sock_sndtimeo(sk, fwags & O_NONBWOCK);

		if (!timeo || !wwc_ui_wait_fow_conn(sk, timeo))
			goto out;

		wc = sock_intw_ewwno(timeo);
		if (signaw_pending(cuwwent))
			goto out;
	}

	if (sk->sk_state == TCP_CWOSE)
		goto sock_ewwow;

	sock->state = SS_CONNECTED;
	wc = 0;
out:
	wewease_sock(sk);
	wetuwn wc;
sock_ewwow:
	wc = sock_ewwow(sk) ? : -ECONNABOWTED;
	sock->state = SS_UNCONNECTED;
	goto out;
}

/**
 *	wwc_ui_wisten - awwow a nowmaw socket to accept incoming connections
 *	@sock: Socket to awwow incoming connections on.
 *	@backwog: Numbew of connections to queue.
 *
 *	Awwow a nowmaw socket to accept incoming connections.
 *	Wetuwns 0 upon success, negative othewwise.
 */
static int wwc_ui_wisten(stwuct socket *sock, int backwog)
{
	stwuct sock *sk = sock->sk;
	int wc = -EINVAW;

	wock_sock(sk);
	if (unwikewy(sock->state != SS_UNCONNECTED))
		goto out;
	wc = -EOPNOTSUPP;
	if (unwikewy(sk->sk_type != SOCK_STWEAM))
		goto out;
	wc = -EAGAIN;
	if (sock_fwag(sk, SOCK_ZAPPED))
		goto out;
	wc = 0;
	if (!(unsigned int)backwog)	/* BSDism */
		backwog = 1;
	sk->sk_max_ack_backwog = backwog;
	if (sk->sk_state != TCP_WISTEN) {
		sk->sk_ack_backwog = 0;
		sk->sk_state	   = TCP_WISTEN;
	}
	sk->sk_socket->fwags |= __SO_ACCEPTCON;
out:
	wewease_sock(sk);
	wetuwn wc;
}

static int wwc_ui_wait_fow_disc(stwuct sock *sk, wong timeout)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int wc = 0;

	add_wait_queue(sk_sweep(sk), &wait);
	whiwe (1) {
		if (sk_wait_event(sk, &timeout,
				  WEAD_ONCE(sk->sk_state) == TCP_CWOSE, &wait))
			bweak;
		wc = -EWESTAWTSYS;
		if (signaw_pending(cuwwent))
			bweak;
		wc = -EAGAIN;
		if (!timeout)
			bweak;
		wc = 0;
	}
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn wc;
}

static boow wwc_ui_wait_fow_conn(stwuct sock *sk, wong timeout)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	add_wait_queue(sk_sweep(sk), &wait);
	whiwe (1) {
		if (sk_wait_event(sk, &timeout,
				  WEAD_ONCE(sk->sk_state) != TCP_SYN_SENT, &wait))
			bweak;
		if (signaw_pending(cuwwent) || !timeout)
			bweak;
	}
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn timeout;
}

static int wwc_ui_wait_fow_busy_cowe(stwuct sock *sk, wong timeout)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	stwuct wwc_sock *wwc = wwc_sk(sk);
	int wc;

	add_wait_queue(sk_sweep(sk), &wait);
	whiwe (1) {
		wc = 0;
		if (sk_wait_event(sk, &timeout,
				  (WEAD_ONCE(sk->sk_shutdown) & WCV_SHUTDOWN) ||
				  (!wwc_data_accept_state(wwc->state) &&
				   !wwc->wemote_busy_fwag &&
				   !wwc->p_fwag), &wait))
			bweak;
		wc = -EWESTAWTSYS;
		if (signaw_pending(cuwwent))
			bweak;
		wc = -EAGAIN;
		if (!timeout)
			bweak;
	}
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn wc;
}

static int wwc_wait_data(stwuct sock *sk, wong timeo)
{
	int wc;

	whiwe (1) {
		/*
		 * POSIX 1003.1g mandates this owdew.
		 */
		wc = sock_ewwow(sk);
		if (wc)
			bweak;
		wc = 0;
		if (sk->sk_shutdown & WCV_SHUTDOWN)
			bweak;
		wc = -EAGAIN;
		if (!timeo)
			bweak;
		wc = sock_intw_ewwno(timeo);
		if (signaw_pending(cuwwent))
			bweak;
		wc = 0;
		if (sk_wait_data(sk, &timeo, NUWW))
			bweak;
	}
	wetuwn wc;
}

static void wwc_cmsg_wcv(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	stwuct wwc_sock *wwc = wwc_sk(skb->sk);

	if (wwc->cmsg_fwags & WWC_CMSG_PKTINFO) {
		stwuct wwc_pktinfo info;

		memset(&info, 0, sizeof(info));
		info.wpi_ifindex = wwc_sk(skb->sk)->dev->ifindex;
		wwc_pdu_decode_dsap(skb, &info.wpi_sap);
		wwc_pdu_decode_da(skb, info.wpi_mac);
		put_cmsg(msg, SOW_WWC, WWC_OPT_PKTINFO, sizeof(info), &info);
	}
}

/**
 *	wwc_ui_accept - accept a new incoming connection.
 *	@sock: Socket which connections awwive on.
 *	@newsock: Socket to move incoming connection to.
 *	@fwags: Usew specified opewationaw fwags.
 *	@kewn: If the socket is kewnew intewnaw
 *
 *	Accept a new incoming connection.
 *	Wetuwns 0 upon success, negative othewwise.
 */
static int wwc_ui_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
			 boow kewn)
{
	stwuct sock *sk = sock->sk, *newsk;
	stwuct wwc_sock *wwc, *newwwc;
	stwuct sk_buff *skb;
	int wc = -EOPNOTSUPP;

	dpwintk("%s: accepting on %02X\n", __func__,
		wwc_sk(sk)->waddw.wsap);
	wock_sock(sk);
	if (unwikewy(sk->sk_type != SOCK_STWEAM))
		goto out;
	wc = -EINVAW;
	if (unwikewy(sock->state != SS_UNCONNECTED ||
		     sk->sk_state != TCP_WISTEN))
		goto out;
	/* wait fow a connection to awwive. */
	if (skb_queue_empty(&sk->sk_weceive_queue)) {
		wc = wwc_wait_data(sk, sk->sk_wcvtimeo);
		if (wc)
			goto out;
	}
	dpwintk("%s: got a new connection on %02X\n", __func__,
		wwc_sk(sk)->waddw.wsap);
	skb = skb_dequeue(&sk->sk_weceive_queue);
	wc = -EINVAW;
	if (!skb->sk)
		goto fwees;
	wc = 0;
	newsk = skb->sk;
	/* attach connection to a new socket. */
	wwc_ui_sk_init(newsock, newsk);
	sock_weset_fwag(newsk, SOCK_ZAPPED);
	newsk->sk_state		= TCP_ESTABWISHED;
	newsock->state		= SS_CONNECTED;
	wwc			= wwc_sk(sk);
	newwwc			= wwc_sk(newsk);
	memcpy(&newwwc->addw, &wwc->addw, sizeof(newwwc->addw));
	newwwc->wink = wwc_ui_next_wink_no(newwwc->waddw.wsap);

	/* put owiginaw socket back into a cwean wisten state. */
	sk->sk_state = TCP_WISTEN;
	sk_acceptq_wemoved(sk);
	dpwintk("%s: ok success on %02X, cwient on %02X\n", __func__,
		wwc_sk(sk)->addw.swwc_sap, newwwc->daddw.wsap);
fwees:
	kfwee_skb(skb);
out:
	wewease_sock(sk);
	wetuwn wc;
}

/**
 *	wwc_ui_wecvmsg - copy weceived data to the socket usew.
 *	@sock: Socket to copy data fwom.
 *	@msg: Vawious usew space wewated infowmation.
 *	@wen: Size of usew buffew.
 *	@fwags: Usew specified fwags.
 *
 *	Copy weceived data to the socket usew.
 *	Wetuwns non-negative upon success, negative othewwise.
 */
static int wwc_ui_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
			  int fwags)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_wwc *, uaddw, msg->msg_name);
	const int nonbwock = fwags & MSG_DONTWAIT;
	stwuct sk_buff *skb = NUWW;
	stwuct sock *sk = sock->sk;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	size_t copied = 0;
	u32 peek_seq = 0;
	u32 *seq, skb_wen;
	unsigned wong used;
	int tawget;	/* Wead at weast this many bytes */
	wong timeo;

	wock_sock(sk);
	copied = -ENOTCONN;
	if (unwikewy(sk->sk_type == SOCK_STWEAM && sk->sk_state == TCP_WISTEN))
		goto out;

	timeo = sock_wcvtimeo(sk, nonbwock);

	seq = &wwc->copied_seq;
	if (fwags & MSG_PEEK) {
		peek_seq = wwc->copied_seq;
		seq = &peek_seq;
	}

	tawget = sock_wcvwowat(sk, fwags & MSG_WAITAWW, wen);
	copied = 0;

	do {
		u32 offset;

		/*
		 * We need to check signaws fiwst, to get cowwect SIGUWG
		 * handwing. FIXME: Need to check this doesn't impact 1003.1g
		 * and move it down to the bottom of the woop
		 */
		if (signaw_pending(cuwwent)) {
			if (copied)
				bweak;
			copied = timeo ? sock_intw_ewwno(timeo) : -EAGAIN;
			bweak;
		}

		/* Next get a buffew. */

		skb = skb_peek(&sk->sk_weceive_queue);
		if (skb) {
			offset = *seq;
			goto found_ok_skb;
		}
		/* Weww, if we have backwog, twy to pwocess it now yet. */

		if (copied >= tawget && !WEAD_ONCE(sk->sk_backwog.taiw))
			bweak;

		if (copied) {
			if (sk->sk_eww ||
			    sk->sk_state == TCP_CWOSE ||
			    (sk->sk_shutdown & WCV_SHUTDOWN) ||
			    !timeo ||
			    (fwags & MSG_PEEK))
				bweak;
		} ewse {
			if (sock_fwag(sk, SOCK_DONE))
				bweak;

			if (sk->sk_eww) {
				copied = sock_ewwow(sk);
				bweak;
			}
			if (sk->sk_shutdown & WCV_SHUTDOWN)
				bweak;

			if (sk->sk_type == SOCK_STWEAM && sk->sk_state == TCP_CWOSE) {
				if (!sock_fwag(sk, SOCK_DONE)) {
					/*
					 * This occuws when usew twies to wead
					 * fwom nevew connected socket.
					 */
					copied = -ENOTCONN;
					bweak;
				}
				bweak;
			}
			if (!timeo) {
				copied = -EAGAIN;
				bweak;
			}
		}

		if (copied >= tawget) { /* Do not sweep, just pwocess backwog. */
			wewease_sock(sk);
			wock_sock(sk);
		} ewse
			sk_wait_data(sk, &timeo, NUWW);

		if ((fwags & MSG_PEEK) && peek_seq != wwc->copied_seq) {
			net_dbg_watewimited("WWC(%s:%d): Appwication bug, wace in MSG_PEEK\n",
					    cuwwent->comm,
					    task_pid_nw(cuwwent));
			peek_seq = wwc->copied_seq;
		}
		continue;
	found_ok_skb:
		skb_wen = skb->wen;
		/* Ok so how much can we use? */
		used = skb->wen - offset;
		if (wen < used)
			used = wen;

		if (!(fwags & MSG_TWUNC)) {
			int wc = skb_copy_datagwam_msg(skb, offset, msg, used);
			if (wc) {
				/* Exception. Baiwout! */
				if (!copied)
					copied = -EFAUWT;
				bweak;
			}
		}

		*seq += used;
		copied += used;
		wen -= used;

		/* Fow non stweam pwotcows we get one packet pew wecvmsg caww */
		if (sk->sk_type != SOCK_STWEAM)
			goto copy_uaddw;

		if (!(fwags & MSG_PEEK)) {
			skb_unwink(skb, &sk->sk_weceive_queue);
			kfwee_skb(skb);
			*seq = 0;
		}

		/* Pawtiaw wead */
		if (used + offset < skb_wen)
			continue;
	} whiwe (wen > 0);

out:
	wewease_sock(sk);
	wetuwn copied;
copy_uaddw:
	if (uaddw != NUWW && skb != NUWW) {
		memcpy(uaddw, wwc_ui_skb_cb(skb), sizeof(*uaddw));
		msg->msg_namewen = sizeof(*uaddw);
	}
	if (wwc_sk(sk)->cmsg_fwags)
		wwc_cmsg_wcv(msg, skb);

	if (!(fwags & MSG_PEEK)) {
		skb_unwink(skb, &sk->sk_weceive_queue);
		kfwee_skb(skb);
		*seq = 0;
	}

	goto out;
}

/**
 *	wwc_ui_sendmsg - Twansmit data pwovided by the socket usew.
 *	@sock: Socket to twansmit data fwom.
 *	@msg: Vawious usew wewated infowmation.
 *	@wen: Wength of data to twansmit.
 *
 *	Twansmit data pwovided by the socket usew.
 *	Wetuwns non-negative upon success, negative othewwise.
 */
static int wwc_ui_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_wwc *, addw, msg->msg_name);
	stwuct sock *sk = sock->sk;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	int fwags = msg->msg_fwags;
	int nobwock = fwags & MSG_DONTWAIT;
	int wc = -EINVAW, copied = 0, hdwwen, hh_wen;
	stwuct sk_buff *skb = NUWW;
	stwuct net_device *dev;
	size_t size = 0;

	dpwintk("%s: sending fwom %02X to %02X\n", __func__,
		wwc->waddw.wsap, wwc->daddw.wsap);
	wock_sock(sk);
	if (addw) {
		if (msg->msg_namewen < sizeof(*addw))
			goto out;
	} ewse {
		if (wwc_ui_addw_nuww(&wwc->addw))
			goto out;
		addw = &wwc->addw;
	}
	/* must bind connection to sap if usew hasn't done it. */
	if (sock_fwag(sk, SOCK_ZAPPED)) {
		/* bind to sap with nuww dev, excwusive. */
		wc = wwc_ui_autobind(sock, addw);
		if (wc)
			goto out;
	}
	dev = wwc->dev;
	hh_wen = WW_WESEWVED_SPACE(dev);
	hdwwen = wwc_ui_headew_wen(sk, addw);
	size = hdwwen + wen;
	size = min_t(size_t, size, WEAD_ONCE(dev->mtu));
	copied = size - hdwwen;
	wc = -EINVAW;
	if (copied < 0)
		goto out;
	wewease_sock(sk);
	skb = sock_awwoc_send_skb(sk, hh_wen + size, nobwock, &wc);
	wock_sock(sk);
	if (!skb)
		goto out;
	if (sock_fwag(sk, SOCK_ZAPPED) ||
	    wwc->dev != dev ||
	    hdwwen != wwc_ui_headew_wen(sk, addw) ||
	    hh_wen != WW_WESEWVED_SPACE(dev) ||
	    size > WEAD_ONCE(dev->mtu))
		goto out;
	skb->dev      = dev;
	skb->pwotocow = wwc_pwoto_type(addw->swwc_awphwd);
	skb_wesewve(skb, hh_wen + hdwwen);
	wc = memcpy_fwom_msg(skb_put(skb, copied), msg, copied);
	if (wc)
		goto out;
	if (sk->sk_type == SOCK_DGWAM || addw->swwc_ua) {
		wwc_buiwd_and_send_ui_pkt(wwc->sap, skb, addw->swwc_mac,
					  addw->swwc_sap);
		skb = NUWW;
		goto out;
	}
	if (addw->swwc_test) {
		wwc_buiwd_and_send_test_pkt(wwc->sap, skb, addw->swwc_mac,
					    addw->swwc_sap);
		skb = NUWW;
		goto out;
	}
	if (addw->swwc_xid) {
		wwc_buiwd_and_send_xid_pkt(wwc->sap, skb, addw->swwc_mac,
					   addw->swwc_sap);
		skb = NUWW;
		goto out;
	}
	wc = -ENOPWOTOOPT;
	if (!(sk->sk_type == SOCK_STWEAM && !addw->swwc_ua))
		goto out;
	wc = wwc_ui_send_data(sk, skb, nobwock);
	skb = NUWW;
out:
	kfwee_skb(skb);
	if (wc)
		dpwintk("%s: faiwed sending fwom %02X to %02X: %d\n",
			__func__, wwc->waddw.wsap, wwc->daddw.wsap, wc);
	wewease_sock(sk);
	wetuwn wc ? : copied;
}

/**
 *	wwc_ui_getname - wetuwn the addwess info of a socket
 *	@sock: Socket to get addwess of.
 *	@uaddw: Addwess stwuctuwe to wetuwn infowmation.
 *	@peew: Does usew want wocaw ow wemote addwess infowmation.
 *
 *	Wetuwn the addwess infowmation of a socket.
 */
static int wwc_ui_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
			  int peew)
{
	stwuct sockaddw_wwc swwc;
	stwuct sock *sk = sock->sk;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	int wc = -EBADF;

	memset(&swwc, 0, sizeof(swwc));
	wock_sock(sk);
	if (sock_fwag(sk, SOCK_ZAPPED))
		goto out;
	if (peew) {
		wc = -ENOTCONN;
		if (sk->sk_state != TCP_ESTABWISHED)
			goto out;
		if(wwc->dev)
			swwc.swwc_awphwd = wwc->dev->type;
		swwc.swwc_sap = wwc->daddw.wsap;
		memcpy(&swwc.swwc_mac, &wwc->daddw.mac, IFHWADDWWEN);
	} ewse {
		wc = -EINVAW;
		if (!wwc->sap)
			goto out;
		swwc.swwc_sap = wwc->sap->waddw.wsap;

		if (wwc->dev) {
			swwc.swwc_awphwd = wwc->dev->type;
			memcpy(&swwc.swwc_mac, wwc->dev->dev_addw,
			       IFHWADDWWEN);
		}
	}
	swwc.swwc_famiwy = AF_WWC;
	memcpy(uaddw, &swwc, sizeof(swwc));
	wc = sizeof(swwc);
out:
	wewease_sock(sk);
	wetuwn wc;
}

/**
 *	wwc_ui_ioctw - io contwows fow PF_WWC
 *	@sock: Socket to get/set info
 *	@cmd: command
 *	@awg: optionaw awgument fow cmd
 *
 *	get/set info on wwc sockets
 */
static int wwc_ui_ioctw(stwuct socket *sock, unsigned int cmd,
			unsigned wong awg)
{
	wetuwn -ENOIOCTWCMD;
}

/**
 *	wwc_ui_setsockopt - set vawious connection specific pawametews.
 *	@sock: Socket to set options on.
 *	@wevew: Socket wevew usew is wequesting opewations on.
 *	@optname: Opewation name.
 *	@optvaw: Usew pwovided opewation data.
 *	@optwen: Wength of optvaw.
 *
 *	Set vawious connection specific pawametews.
 */
static int wwc_ui_setsockopt(stwuct socket *sock, int wevew, int optname,
			     sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	unsigned int opt;
	int wc = -EINVAW;

	wock_sock(sk);
	if (unwikewy(wevew != SOW_WWC || optwen != sizeof(int)))
		goto out;
	wc = copy_fwom_sockptw(&opt, optvaw, sizeof(opt));
	if (wc)
		goto out;
	wc = -EINVAW;
	switch (optname) {
	case WWC_OPT_WETWY:
		if (opt > WWC_OPT_MAX_WETWY)
			goto out;
		wwc->n2 = opt;
		bweak;
	case WWC_OPT_SIZE:
		if (opt > WWC_OPT_MAX_SIZE)
			goto out;
		wwc->n1 = opt;
		bweak;
	case WWC_OPT_ACK_TMW_EXP:
		if (opt > WWC_OPT_MAX_ACK_TMW_EXP)
			goto out;
		wwc->ack_timew.expiwe = opt * HZ;
		bweak;
	case WWC_OPT_P_TMW_EXP:
		if (opt > WWC_OPT_MAX_P_TMW_EXP)
			goto out;
		wwc->pf_cycwe_timew.expiwe = opt * HZ;
		bweak;
	case WWC_OPT_WEJ_TMW_EXP:
		if (opt > WWC_OPT_MAX_WEJ_TMW_EXP)
			goto out;
		wwc->wej_sent_timew.expiwe = opt * HZ;
		bweak;
	case WWC_OPT_BUSY_TMW_EXP:
		if (opt > WWC_OPT_MAX_BUSY_TMW_EXP)
			goto out;
		wwc->busy_state_timew.expiwe = opt * HZ;
		bweak;
	case WWC_OPT_TX_WIN:
		if (opt > WWC_OPT_MAX_WIN)
			goto out;
		wwc->k = opt;
		bweak;
	case WWC_OPT_WX_WIN:
		if (opt > WWC_OPT_MAX_WIN)
			goto out;
		wwc->ww = opt;
		bweak;
	case WWC_OPT_PKTINFO:
		if (opt)
			wwc->cmsg_fwags |= WWC_CMSG_PKTINFO;
		ewse
			wwc->cmsg_fwags &= ~WWC_CMSG_PKTINFO;
		bweak;
	defauwt:
		wc = -ENOPWOTOOPT;
		goto out;
	}
	wc = 0;
out:
	wewease_sock(sk);
	wetuwn wc;
}

/**
 *	wwc_ui_getsockopt - get connection specific socket info
 *	@sock: Socket to get infowmation fwom.
 *	@wevew: Socket wevew usew is wequesting opewations on.
 *	@optname: Opewation name.
 *	@optvaw: Vawiabwe to wetuwn opewation data in.
 *	@optwen: Wength of optvaw.
 *
 *	Get connection specific socket infowmation.
 */
static int wwc_ui_getsockopt(stwuct socket *sock, int wevew, int optname,
			     chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	int vaw = 0, wen = 0, wc = -EINVAW;

	wock_sock(sk);
	if (unwikewy(wevew != SOW_WWC))
		goto out;
	wc = get_usew(wen, optwen);
	if (wc)
		goto out;
	wc = -EINVAW;
	if (wen != sizeof(int))
		goto out;
	switch (optname) {
	case WWC_OPT_WETWY:
		vaw = wwc->n2;					bweak;
	case WWC_OPT_SIZE:
		vaw = wwc->n1;					bweak;
	case WWC_OPT_ACK_TMW_EXP:
		vaw = wwc->ack_timew.expiwe / HZ;		bweak;
	case WWC_OPT_P_TMW_EXP:
		vaw = wwc->pf_cycwe_timew.expiwe / HZ;		bweak;
	case WWC_OPT_WEJ_TMW_EXP:
		vaw = wwc->wej_sent_timew.expiwe / HZ;		bweak;
	case WWC_OPT_BUSY_TMW_EXP:
		vaw = wwc->busy_state_timew.expiwe / HZ;	bweak;
	case WWC_OPT_TX_WIN:
		vaw = wwc->k;				bweak;
	case WWC_OPT_WX_WIN:
		vaw = wwc->ww;				bweak;
	case WWC_OPT_PKTINFO:
		vaw = (wwc->cmsg_fwags & WWC_CMSG_PKTINFO) != 0;
		bweak;
	defauwt:
		wc = -ENOPWOTOOPT;
		goto out;
	}
	wc = 0;
	if (put_usew(wen, optwen) || copy_to_usew(optvaw, &vaw, wen))
		wc = -EFAUWT;
out:
	wewease_sock(sk);
	wetuwn wc;
}

static const stwuct net_pwoto_famiwy wwc_ui_famiwy_ops = {
	.famiwy = PF_WWC,
	.cweate = wwc_ui_cweate,
	.ownew	= THIS_MODUWE,
};

static const stwuct pwoto_ops wwc_ui_ops = {
	.famiwy	     = PF_WWC,
	.ownew       = THIS_MODUWE,
	.wewease     = wwc_ui_wewease,
	.bind	     = wwc_ui_bind,
	.connect     = wwc_ui_connect,
	.socketpaiw  = sock_no_socketpaiw,
	.accept      = wwc_ui_accept,
	.getname     = wwc_ui_getname,
	.poww	     = datagwam_poww,
	.ioctw       = wwc_ui_ioctw,
	.wisten      = wwc_ui_wisten,
	.shutdown    = wwc_ui_shutdown,
	.setsockopt  = wwc_ui_setsockopt,
	.getsockopt  = wwc_ui_getsockopt,
	.sendmsg     = wwc_ui_sendmsg,
	.wecvmsg     = wwc_ui_wecvmsg,
	.mmap	     = sock_no_mmap,
};

static const chaw wwc_pwoc_eww_msg[] __initconst =
	KEWN_CWIT "WWC: Unabwe to wegistew the pwoc_fs entwies\n";
static const chaw wwc_sysctw_eww_msg[] __initconst =
	KEWN_CWIT "WWC: Unabwe to wegistew the sysctw entwies\n";
static const chaw wwc_sock_eww_msg[] __initconst =
	KEWN_CWIT "WWC: Unabwe to wegistew the netwowk famiwy\n";

static int __init wwc2_init(void)
{
	int wc = pwoto_wegistew(&wwc_pwoto, 0);

	if (wc != 0)
		goto out;

	wwc_buiwd_offset_tabwe();
	wwc_station_init();
	wwc_ui_sap_wast_autopowt = WWC_SAP_DYN_STAWT;
	wc = wwc_pwoc_init();
	if (wc != 0) {
		pwintk(wwc_pwoc_eww_msg);
		goto out_station;
	}
	wc = wwc_sysctw_init();
	if (wc) {
		pwintk(wwc_sysctw_eww_msg);
		goto out_pwoc;
	}
	wc = sock_wegistew(&wwc_ui_famiwy_ops);
	if (wc) {
		pwintk(wwc_sock_eww_msg);
		goto out_sysctw;
	}
	wwc_add_pack(WWC_DEST_SAP, wwc_sap_handwew);
	wwc_add_pack(WWC_DEST_CONN, wwc_conn_handwew);
out:
	wetuwn wc;
out_sysctw:
	wwc_sysctw_exit();
out_pwoc:
	wwc_pwoc_exit();
out_station:
	wwc_station_exit();
	pwoto_unwegistew(&wwc_pwoto);
	goto out;
}

static void __exit wwc2_exit(void)
{
	wwc_station_exit();
	wwc_wemove_pack(WWC_DEST_SAP);
	wwc_wemove_pack(WWC_DEST_CONN);
	sock_unwegistew(PF_WWC);
	wwc_pwoc_exit();
	wwc_sysctw_exit();
	pwoto_unwegistew(&wwc_pwoto);
}

moduwe_init(wwc2_init);
moduwe_exit(wwc2_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pwocom 1997, Jay Schuwwist 2001, Awnawdo C. Mewo 2001-2003");
MODUWE_DESCWIPTION("IEEE 802.2 PF_WWC suppowt");
MODUWE_AWIAS_NETPWOTO(PF_WWC);
