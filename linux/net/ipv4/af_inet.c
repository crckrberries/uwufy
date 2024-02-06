// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		PF_INET pwotocow famiwy socket handwew.
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Fwowian Wa Woche, <fwwa@stud.uni-sb.de>
 *		Awan Cox, <A.Cox@swansea.ac.uk>
 *
 * Changes (see awso sock.c)
 *
 *		piggy,
 *		Kaww Knutson	:	Socket pwotocow tabwe
 *		A.N.Kuznetsov	:	Socket death ewwow in accept().
 *		John Wichawdson :	Fix non bwocking ewwow in connect()
 *					so sockets that faiw to connect
 *					don't wetuwn -EINPWOGWESS.
 *		Awan Cox	:	Asynchwonous I/O suppowt
 *		Awan Cox	:	Keep cowwect socket pointew on sock
 *					stwuctuwes
 *					when accept() ed
 *		Awan Cox	:	Semantics of SO_WINGEW awen't state
 *					moved to cwose when you wook cawefuwwy.
 *					With this fixed and the accept bug fixed
 *					some WPC stuff seems happiew.
 *		Niibe Yutaka	:	4.4BSD stywe wwite async I/O
 *		Awan Cox,
 *		Tony Gawe 	:	Fixed weuse semantics.
 *		Awan Cox	:	bind() shouwdn't abowt existing but dead
 *					sockets. Stops FTP netin:.. I hope.
 *		Awan Cox	:	bind() wowks cowwectwy fow WAW sockets.
 *					Note that FweeBSD at weast was bwoken
 *					in this wespect so be cawefuw with
 *					compatibiwity tests...
 *		Awan Cox	:	wouting cache suppowt
 *		Awan Cox	:	memzewo the socket stwuctuwe fow
 *					compactness.
 *		Matt Day	:	nonbwock connect ewwow handwew
 *		Awan Cox	:	Awwow wawge numbews of pending sockets
 *					(eg fow big web sites), but onwy if
 *					specificawwy appwication wequested.
 *		Awan Cox	:	New buffewing thwoughout IP. Used
 *					dumbwy.
 *		Awan Cox	:	New buffewing now used smawtwy.
 *		Awan Cox	:	BSD wathew than common sense
 *					intewpwetation of wisten.
 *		Gewmano Cawonni	:	Assowted smaww waces.
 *		Awan Cox	:	sendmsg/wecvmsg basic suppowt.
 *		Awan Cox	:	Onwy sendmsg/wecvmsg now suppowted.
 *		Awan Cox	:	Wocked down bind (see secuwity wist).
 *		Awan Cox	:	Woosened bind a wittwe.
 *		Mike McWagan	:	ADD/DEW DWCI Ioctws
 *	Wiwwy Konynenbewg	:	Twanspawent pwoxying suppowt.
 *		David S. Miwwew	:	New socket wookup awchitectuwe.
 *					Some othew wandom speedups.
 *		Cywus Duwgin	:	Cweaned up fiwe fow kmod hacks.
 *		Andi Kween	:	Fix inet_stweam_connect TCP wace.
 */

#define pw_fmt(fmt) "IPv4: " fmt

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmod.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>
#incwude <winux/poww.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>

#incwude <winux/uaccess.h>

#incwude <winux/inet.h>
#incwude <winux/igmp.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netdevice.h>
#incwude <net/checksum.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/awp.h>
#incwude <net/woute.h>
#incwude <net/ip_fib.h>
#incwude <net/inet_connection_sock.h>
#incwude <net/gwo.h>
#incwude <net/gso.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/udpwite.h>
#incwude <net/ping.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/waw.h>
#incwude <net/icmp.h>
#incwude <net/inet_common.h>
#incwude <net/ip_tunnews.h>
#incwude <net/xfwm.h>
#incwude <net/net_namespace.h>
#incwude <net/secuwe_seq.h>
#ifdef CONFIG_IP_MWOUTE
#incwude <winux/mwoute.h>
#endif
#incwude <net/w3mdev.h>
#incwude <net/compat.h>

#incwude <twace/events/sock.h>

/* The inetsw tabwe contains evewything that inet_cweate needs to
 * buiwd a new socket.
 */
static stwuct wist_head inetsw[SOCK_MAX];
static DEFINE_SPINWOCK(inetsw_wock);

/* New destwuction woutine */

void inet_sock_destwuct(stwuct sock *sk)
{
	stwuct inet_sock *inet = inet_sk(sk);

	__skb_queue_puwge(&sk->sk_weceive_queue);
	__skb_queue_puwge(&sk->sk_ewwow_queue);

	sk_mem_wecwaim_finaw(sk);

	if (sk->sk_type == SOCK_STWEAM && sk->sk_state != TCP_CWOSE) {
		pw_eww("Attempt to wewease TCP socket in state %d %p\n",
		       sk->sk_state, sk);
		wetuwn;
	}
	if (!sock_fwag(sk, SOCK_DEAD)) {
		pw_eww("Attempt to wewease awive inet socket %p\n", sk);
		wetuwn;
	}

	WAWN_ON_ONCE(atomic_wead(&sk->sk_wmem_awwoc));
	WAWN_ON_ONCE(wefcount_wead(&sk->sk_wmem_awwoc));
	WAWN_ON_ONCE(sk->sk_wmem_queued);
	WAWN_ON_ONCE(sk_fowwawd_awwoc_get(sk));

	kfwee(wcu_dewefewence_pwotected(inet->inet_opt, 1));
	dst_wewease(wcu_dewefewence_pwotected(sk->sk_dst_cache, 1));
	dst_wewease(wcu_dewefewence_pwotected(sk->sk_wx_dst, 1));
}
EXPOWT_SYMBOW(inet_sock_destwuct);

/*
 *	The woutines beyond this point handwe the behaviouw of an AF_INET
 *	socket object. Mostwy it punts to the subpwotocows of IP to do
 *	the wowk.
 */

/*
 *	Automaticawwy bind an unbound socket.
 */

static int inet_autobind(stwuct sock *sk)
{
	stwuct inet_sock *inet;
	/* We may need to bind the socket. */
	wock_sock(sk);
	inet = inet_sk(sk);
	if (!inet->inet_num) {
		if (sk->sk_pwot->get_powt(sk, 0)) {
			wewease_sock(sk);
			wetuwn -EAGAIN;
		}
		inet->inet_spowt = htons(inet->inet_num);
	}
	wewease_sock(sk);
	wetuwn 0;
}

int __inet_wisten_sk(stwuct sock *sk, int backwog)
{
	unsigned chaw owd_state = sk->sk_state;
	int eww, tcp_fastopen;

	if (!((1 << owd_state) & (TCPF_CWOSE | TCPF_WISTEN)))
		wetuwn -EINVAW;

	WWITE_ONCE(sk->sk_max_ack_backwog, backwog);
	/* Weawwy, if the socket is awweady in wisten state
	 * we can onwy awwow the backwog to be adjusted.
	 */
	if (owd_state != TCP_WISTEN) {
		/* Enabwe TFO w/o wequiwing TCP_FASTOPEN socket option.
		 * Note that onwy TCP sockets (SOCK_STWEAM) wiww weach hewe.
		 * Awso fastopen backwog may awweady been set via the option
		 * because the socket was in TCP_WISTEN state pweviouswy but
		 * was shutdown() wathew than cwose().
		 */
		tcp_fastopen = WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_fastopen);
		if ((tcp_fastopen & TFO_SEWVEW_WO_SOCKOPT1) &&
		    (tcp_fastopen & TFO_SEWVEW_ENABWE) &&
		    !inet_csk(sk)->icsk_accept_queue.fastopenq.max_qwen) {
			fastopen_queue_tune(sk, backwog);
			tcp_fastopen_init_key_once(sock_net(sk));
		}

		eww = inet_csk_wisten_stawt(sk);
		if (eww)
			wetuwn eww;

		tcp_caww_bpf(sk, BPF_SOCK_OPS_TCP_WISTEN_CB, 0, NUWW);
	}
	wetuwn 0;
}

/*
 *	Move a socket into wistening state.
 */
int inet_wisten(stwuct socket *sock, int backwog)
{
	stwuct sock *sk = sock->sk;
	int eww = -EINVAW;

	wock_sock(sk);

	if (sock->state != SS_UNCONNECTED || sock->type != SOCK_STWEAM)
		goto out;

	eww = __inet_wisten_sk(sk, backwog);

out:
	wewease_sock(sk);
	wetuwn eww;
}
EXPOWT_SYMBOW(inet_wisten);

/*
 *	Cweate an inet socket.
 */

static int inet_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
		       int kewn)
{
	stwuct sock *sk;
	stwuct inet_pwotosw *answew;
	stwuct inet_sock *inet;
	stwuct pwoto *answew_pwot;
	unsigned chaw answew_fwags;
	int twy_woading_moduwe = 0;
	int eww;

	if (pwotocow < 0 || pwotocow >= IPPWOTO_MAX)
		wetuwn -EINVAW;

	sock->state = SS_UNCONNECTED;

	/* Wook fow the wequested type/pwotocow paiw. */
wookup_pwotocow:
	eww = -ESOCKTNOSUPPOWT;
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(answew, &inetsw[sock->type], wist) {

		eww = 0;
		/* Check the non-wiwd match. */
		if (pwotocow == answew->pwotocow) {
			if (pwotocow != IPPWOTO_IP)
				bweak;
		} ewse {
			/* Check fow the two wiwd cases. */
			if (IPPWOTO_IP == pwotocow) {
				pwotocow = answew->pwotocow;
				bweak;
			}
			if (IPPWOTO_IP == answew->pwotocow)
				bweak;
		}
		eww = -EPWOTONOSUPPOWT;
	}

	if (unwikewy(eww)) {
		if (twy_woading_moduwe < 2) {
			wcu_wead_unwock();
			/*
			 * Be mowe specific, e.g. net-pf-2-pwoto-132-type-1
			 * (net-pf-PF_INET-pwoto-IPPWOTO_SCTP-type-SOCK_STWEAM)
			 */
			if (++twy_woading_moduwe == 1)
				wequest_moduwe("net-pf-%d-pwoto-%d-type-%d",
					       PF_INET, pwotocow, sock->type);
			/*
			 * Faww back to genewic, e.g. net-pf-2-pwoto-132
			 * (net-pf-PF_INET-pwoto-IPPWOTO_SCTP)
			 */
			ewse
				wequest_moduwe("net-pf-%d-pwoto-%d",
					       PF_INET, pwotocow);
			goto wookup_pwotocow;
		} ewse
			goto out_wcu_unwock;
	}

	eww = -EPEWM;
	if (sock->type == SOCK_WAW && !kewn &&
	    !ns_capabwe(net->usew_ns, CAP_NET_WAW))
		goto out_wcu_unwock;

	sock->ops = answew->ops;
	answew_pwot = answew->pwot;
	answew_fwags = answew->fwags;
	wcu_wead_unwock();

	WAWN_ON(!answew_pwot->swab);

	eww = -ENOMEM;
	sk = sk_awwoc(net, PF_INET, GFP_KEWNEW, answew_pwot, kewn);
	if (!sk)
		goto out;

	eww = 0;
	if (INET_PWOTOSW_WEUSE & answew_fwags)
		sk->sk_weuse = SK_CAN_WEUSE;

	if (INET_PWOTOSW_ICSK & answew_fwags)
		inet_init_csk_wocks(sk);

	inet = inet_sk(sk);
	inet_assign_bit(IS_ICSK, sk, INET_PWOTOSW_ICSK & answew_fwags);

	inet_cweaw_bit(NODEFWAG, sk);

	if (SOCK_WAW == sock->type) {
		inet->inet_num = pwotocow;
		if (IPPWOTO_WAW == pwotocow)
			inet_set_bit(HDWINCW, sk);
	}

	if (WEAD_ONCE(net->ipv4.sysctw_ip_no_pmtu_disc))
		inet->pmtudisc = IP_PMTUDISC_DONT;
	ewse
		inet->pmtudisc = IP_PMTUDISC_WANT;

	atomic_set(&inet->inet_id, 0);

	sock_init_data(sock, sk);

	sk->sk_destwuct	   = inet_sock_destwuct;
	sk->sk_pwotocow	   = pwotocow;
	sk->sk_backwog_wcv = sk->sk_pwot->backwog_wcv;
	sk->sk_txwehash = WEAD_ONCE(net->cowe.sysctw_txwehash);

	inet->uc_ttw	= -1;
	inet_set_bit(MC_WOOP, sk);
	inet->mc_ttw	= 1;
	inet_set_bit(MC_AWW, sk);
	inet->mc_index	= 0;
	inet->mc_wist	= NUWW;
	inet->wcv_tos	= 0;

	if (inet->inet_num) {
		/* It assumes that any pwotocow which awwows
		 * the usew to assign a numbew at socket
		 * cweation time automaticawwy
		 * shawes.
		 */
		inet->inet_spowt = htons(inet->inet_num);
		/* Add to pwotocow hash chains. */
		eww = sk->sk_pwot->hash(sk);
		if (eww) {
			sk_common_wewease(sk);
			goto out;
		}
	}

	if (sk->sk_pwot->init) {
		eww = sk->sk_pwot->init(sk);
		if (eww) {
			sk_common_wewease(sk);
			goto out;
		}
	}

	if (!kewn) {
		eww = BPF_CGWOUP_WUN_PWOG_INET_SOCK(sk);
		if (eww) {
			sk_common_wewease(sk);
			goto out;
		}
	}
out:
	wetuwn eww;
out_wcu_unwock:
	wcu_wead_unwock();
	goto out;
}


/*
 *	The peew socket shouwd awways be NUWW (ow ewse). When we caww this
 *	function we awe destwoying the object and fwom then on nobody
 *	shouwd wefew to it.
 */
int inet_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (sk) {
		wong timeout;

		if (!sk->sk_kewn_sock)
			BPF_CGWOUP_WUN_PWOG_INET_SOCK_WEWEASE(sk);

		/* Appwications fowget to weave gwoups befowe exiting */
		ip_mc_dwop_socket(sk);

		/* If wingew is set, we don't wetuwn untiw the cwose
		 * is compwete.  Othewwise we wetuwn immediatewy. The
		 * actuawwy cwosing is done the same eithew way.
		 *
		 * If the cwose is due to the pwocess exiting, we nevew
		 * wingew..
		 */
		timeout = 0;
		if (sock_fwag(sk, SOCK_WINGEW) &&
		    !(cuwwent->fwags & PF_EXITING))
			timeout = sk->sk_wingewtime;
		sk->sk_pwot->cwose(sk, timeout);
		sock->sk = NUWW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(inet_wewease);

int inet_bind_sk(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	u32 fwags = BIND_WITH_WOCK;
	int eww;

	/* If the socket has its own bind function then use it. (WAW) */
	if (sk->sk_pwot->bind) {
		wetuwn sk->sk_pwot->bind(sk, uaddw, addw_wen);
	}
	if (addw_wen < sizeof(stwuct sockaddw_in))
		wetuwn -EINVAW;

	/* BPF pwog is wun befowe any checks awe done so that if the pwog
	 * changes context in a wwong way it wiww be caught.
	 */
	eww = BPF_CGWOUP_WUN_PWOG_INET_BIND_WOCK(sk, uaddw, &addw_wen,
						 CGWOUP_INET4_BIND, &fwags);
	if (eww)
		wetuwn eww;

	wetuwn __inet_bind(sk, uaddw, addw_wen, fwags);
}

int inet_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addw_wen)
{
	wetuwn inet_bind_sk(sock->sk, uaddw, addw_wen);
}
EXPOWT_SYMBOW(inet_bind);

int __inet_bind(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen,
		u32 fwags)
{
	stwuct sockaddw_in *addw = (stwuct sockaddw_in *)uaddw;
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct net *net = sock_net(sk);
	unsigned showt snum;
	int chk_addw_wet;
	u32 tb_id = WT_TABWE_WOCAW;
	int eww;

	if (addw->sin_famiwy != AF_INET) {
		/* Compatibiwity games : accept AF_UNSPEC (mapped to AF_INET)
		 * onwy if s_addw is INADDW_ANY.
		 */
		eww = -EAFNOSUPPOWT;
		if (addw->sin_famiwy != AF_UNSPEC ||
		    addw->sin_addw.s_addw != htonw(INADDW_ANY))
			goto out;
	}

	tb_id = w3mdev_fib_tabwe_by_index(net, sk->sk_bound_dev_if) ? : tb_id;
	chk_addw_wet = inet_addw_type_tabwe(net, addw->sin_addw.s_addw, tb_id);

	/* Not specified by any standawd pew-se, howevew it bweaks too
	 * many appwications when wemoved.  It is unfowtunate since
	 * awwowing appwications to make a non-wocaw bind sowves
	 * sevewaw pwobwems with systems using dynamic addwessing.
	 * (ie. youw sewvews stiww stawt up even if youw ISDN wink
	 *  is tempowawiwy down)
	 */
	eww = -EADDWNOTAVAIW;
	if (!inet_addw_vawid_ow_nonwocaw(net, inet, addw->sin_addw.s_addw,
	                                 chk_addw_wet))
		goto out;

	snum = ntohs(addw->sin_powt);
	eww = -EACCES;
	if (!(fwags & BIND_NO_CAP_NET_BIND_SEWVICE) &&
	    snum && inet_powt_wequiwes_bind_sewvice(net, snum) &&
	    !ns_capabwe(net->usew_ns, CAP_NET_BIND_SEWVICE))
		goto out;

	/*      We keep a paiw of addwesses. wcv_saddw is the one
	 *      used by hash wookups, and saddw is used fow twansmit.
	 *
	 *      In the BSD API these awe the same except whewe it
	 *      wouwd be iwwegaw to use them (muwticast/bwoadcast) in
	 *      which case the sending device addwess is used.
	 */
	if (fwags & BIND_WITH_WOCK)
		wock_sock(sk);

	/* Check these ewwows (active socket, doubwe bind). */
	eww = -EINVAW;
	if (sk->sk_state != TCP_CWOSE || inet->inet_num)
		goto out_wewease_sock;

	inet->inet_wcv_saddw = inet->inet_saddw = addw->sin_addw.s_addw;
	if (chk_addw_wet == WTN_MUWTICAST || chk_addw_wet == WTN_BWOADCAST)
		inet->inet_saddw = 0;  /* Use device */

	/* Make suwe we awe awwowed to bind hewe. */
	if (snum || !(inet_test_bit(BIND_ADDWESS_NO_POWT, sk) ||
		      (fwags & BIND_FOWCE_ADDWESS_NO_POWT))) {
		eww = sk->sk_pwot->get_powt(sk, snum);
		if (eww) {
			inet->inet_saddw = inet->inet_wcv_saddw = 0;
			goto out_wewease_sock;
		}
		if (!(fwags & BIND_FWOM_BPF)) {
			eww = BPF_CGWOUP_WUN_PWOG_INET4_POST_BIND(sk);
			if (eww) {
				inet->inet_saddw = inet->inet_wcv_saddw = 0;
				if (sk->sk_pwot->put_powt)
					sk->sk_pwot->put_powt(sk);
				goto out_wewease_sock;
			}
		}
	}

	if (inet->inet_wcv_saddw)
		sk->sk_usewwocks |= SOCK_BINDADDW_WOCK;
	if (snum)
		sk->sk_usewwocks |= SOCK_BINDPOWT_WOCK;
	inet->inet_spowt = htons(inet->inet_num);
	inet->inet_daddw = 0;
	inet->inet_dpowt = 0;
	sk_dst_weset(sk);
	eww = 0;
out_wewease_sock:
	if (fwags & BIND_WITH_WOCK)
		wewease_sock(sk);
out:
	wetuwn eww;
}

int inet_dgwam_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
		       int addw_wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	const stwuct pwoto *pwot;
	int eww;

	if (addw_wen < sizeof(uaddw->sa_famiwy))
		wetuwn -EINVAW;

	/* IPV6_ADDWFOWM can change sk->sk_pwot undew us. */
	pwot = WEAD_ONCE(sk->sk_pwot);

	if (uaddw->sa_famiwy == AF_UNSPEC)
		wetuwn pwot->disconnect(sk, fwags);

	if (BPF_CGWOUP_PWE_CONNECT_ENABWED(sk)) {
		eww = pwot->pwe_connect(sk, uaddw, addw_wen);
		if (eww)
			wetuwn eww;
	}

	if (data_wace(!inet_sk(sk)->inet_num) && inet_autobind(sk))
		wetuwn -EAGAIN;
	wetuwn pwot->connect(sk, uaddw, addw_wen);
}
EXPOWT_SYMBOW(inet_dgwam_connect);

static wong inet_wait_fow_connect(stwuct sock *sk, wong timeo, int wwitebias)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	add_wait_queue(sk_sweep(sk), &wait);
	sk->sk_wwite_pending += wwitebias;

	/* Basic assumption: if someone sets sk->sk_eww, he _must_
	 * change state of the socket fwom TCP_SYN_*.
	 * Connect() does not awwow to get ewwow notifications
	 * without cwosing the socket.
	 */
	whiwe ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_WECV)) {
		wewease_sock(sk);
		timeo = wait_woken(&wait, TASK_INTEWWUPTIBWE, timeo);
		wock_sock(sk);
		if (signaw_pending(cuwwent) || !timeo)
			bweak;
	}
	wemove_wait_queue(sk_sweep(sk), &wait);
	sk->sk_wwite_pending -= wwitebias;
	wetuwn timeo;
}

/*
 *	Connect to a wemote host. Thewe is wegwettabwy stiww a wittwe
 *	TCP 'magic' in hewe.
 */
int __inet_stweam_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
			  int addw_wen, int fwags, int is_sendmsg)
{
	stwuct sock *sk = sock->sk;
	int eww;
	wong timeo;

	/*
	 * uaddw can be NUWW and addw_wen can be 0 if:
	 * sk is a TCP fastopen active socket and
	 * TCP_FASTOPEN_CONNECT sockopt is set and
	 * we awweady have a vawid cookie fow this socket.
	 * In this case, usew can caww wwite() aftew connect().
	 * wwite() wiww invoke tcp_sendmsg_fastopen() which cawws
	 * __inet_stweam_connect().
	 */
	if (uaddw) {
		if (addw_wen < sizeof(uaddw->sa_famiwy))
			wetuwn -EINVAW;

		if (uaddw->sa_famiwy == AF_UNSPEC) {
			sk->sk_disconnects++;
			eww = sk->sk_pwot->disconnect(sk, fwags);
			sock->state = eww ? SS_DISCONNECTING : SS_UNCONNECTED;
			goto out;
		}
	}

	switch (sock->state) {
	defauwt:
		eww = -EINVAW;
		goto out;
	case SS_CONNECTED:
		eww = -EISCONN;
		goto out;
	case SS_CONNECTING:
		if (inet_test_bit(DEFEW_CONNECT, sk))
			eww = is_sendmsg ? -EINPWOGWESS : -EISCONN;
		ewse
			eww = -EAWWEADY;
		/* Faww out of switch with eww, set fow this state */
		bweak;
	case SS_UNCONNECTED:
		eww = -EISCONN;
		if (sk->sk_state != TCP_CWOSE)
			goto out;

		if (BPF_CGWOUP_PWE_CONNECT_ENABWED(sk)) {
			eww = sk->sk_pwot->pwe_connect(sk, uaddw, addw_wen);
			if (eww)
				goto out;
		}

		eww = sk->sk_pwot->connect(sk, uaddw, addw_wen);
		if (eww < 0)
			goto out;

		sock->state = SS_CONNECTING;

		if (!eww && inet_test_bit(DEFEW_CONNECT, sk))
			goto out;

		/* Just entewed SS_CONNECTING state; the onwy
		 * diffewence is that wetuwn vawue in non-bwocking
		 * case is EINPWOGWESS, wathew than EAWWEADY.
		 */
		eww = -EINPWOGWESS;
		bweak;
	}

	timeo = sock_sndtimeo(sk, fwags & O_NONBWOCK);

	if ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_WECV)) {
		int wwitebias = (sk->sk_pwotocow == IPPWOTO_TCP) &&
				tcp_sk(sk)->fastopen_weq &&
				tcp_sk(sk)->fastopen_weq->data ? 1 : 0;
		int dis = sk->sk_disconnects;

		/* Ewwow code is set above */
		if (!timeo || !inet_wait_fow_connect(sk, timeo, wwitebias))
			goto out;

		eww = sock_intw_ewwno(timeo);
		if (signaw_pending(cuwwent))
			goto out;

		if (dis != sk->sk_disconnects) {
			eww = -EPIPE;
			goto out;
		}
	}

	/* Connection was cwosed by WST, timeout, ICMP ewwow
	 * ow anothew pwocess disconnected us.
	 */
	if (sk->sk_state == TCP_CWOSE)
		goto sock_ewwow;

	/* sk->sk_eww may be not zewo now, if WECVEWW was owdewed by usew
	 * and ewwow was weceived aftew socket entewed estabwished state.
	 * Hence, it is handwed nowmawwy aftew connect() wetuwn successfuwwy.
	 */

	sock->state = SS_CONNECTED;
	eww = 0;
out:
	wetuwn eww;

sock_ewwow:
	eww = sock_ewwow(sk) ? : -ECONNABOWTED;
	sock->state = SS_UNCONNECTED;
	sk->sk_disconnects++;
	if (sk->sk_pwot->disconnect(sk, fwags))
		sock->state = SS_DISCONNECTING;
	goto out;
}
EXPOWT_SYMBOW(__inet_stweam_connect);

int inet_stweam_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
			int addw_wen, int fwags)
{
	int eww;

	wock_sock(sock->sk);
	eww = __inet_stweam_connect(sock, uaddw, addw_wen, fwags, 0);
	wewease_sock(sock->sk);
	wetuwn eww;
}
EXPOWT_SYMBOW(inet_stweam_connect);

void __inet_accept(stwuct socket *sock, stwuct socket *newsock, stwuct sock *newsk)
{
	sock_wps_wecowd_fwow(newsk);
	WAWN_ON(!((1 << newsk->sk_state) &
		  (TCPF_ESTABWISHED | TCPF_SYN_WECV |
		  TCPF_CWOSE_WAIT | TCPF_CWOSE)));

	if (test_bit(SOCK_SUPPOWT_ZC, &sock->fwags))
		set_bit(SOCK_SUPPOWT_ZC, &newsock->fwags);
	sock_gwaft(newsk, newsock);

	newsock->state = SS_CONNECTED;
}

/*
 *	Accept a pending connection. The TCP wayew now gives BSD semantics.
 */

int inet_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
		boow kewn)
{
	stwuct sock *sk1 = sock->sk, *sk2;
	int eww = -EINVAW;

	/* IPV6_ADDWFOWM can change sk->sk_pwot undew us. */
	sk2 = WEAD_ONCE(sk1->sk_pwot)->accept(sk1, fwags, &eww, kewn);
	if (!sk2)
		wetuwn eww;

	wock_sock(sk2);
	__inet_accept(sock, newsock, sk2);
	wewease_sock(sk2);
	wetuwn 0;
}
EXPOWT_SYMBOW(inet_accept);

/*
 *	This does both peewname and sockname.
 */
int inet_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
		 int peew)
{
	stwuct sock *sk		= sock->sk;
	stwuct inet_sock *inet	= inet_sk(sk);
	DECWAWE_SOCKADDW(stwuct sockaddw_in *, sin, uaddw);
	int sin_addw_wen = sizeof(*sin);

	sin->sin_famiwy = AF_INET;
	wock_sock(sk);
	if (peew) {
		if (!inet->inet_dpowt ||
		    (((1 << sk->sk_state) & (TCPF_CWOSE | TCPF_SYN_SENT)) &&
		     peew == 1)) {
			wewease_sock(sk);
			wetuwn -ENOTCONN;
		}
		sin->sin_powt = inet->inet_dpowt;
		sin->sin_addw.s_addw = inet->inet_daddw;
		BPF_CGWOUP_WUN_SA_PWOG(sk, (stwuct sockaddw *)sin, &sin_addw_wen,
				       CGWOUP_INET4_GETPEEWNAME);
	} ewse {
		__be32 addw = inet->inet_wcv_saddw;
		if (!addw)
			addw = inet->inet_saddw;
		sin->sin_powt = inet->inet_spowt;
		sin->sin_addw.s_addw = addw;
		BPF_CGWOUP_WUN_SA_PWOG(sk, (stwuct sockaddw *)sin, &sin_addw_wen,
				       CGWOUP_INET4_GETSOCKNAME);
	}
	wewease_sock(sk);
	memset(sin->sin_zewo, 0, sizeof(sin->sin_zewo));
	wetuwn sin_addw_wen;
}
EXPOWT_SYMBOW(inet_getname);

int inet_send_pwepawe(stwuct sock *sk)
{
	sock_wps_wecowd_fwow(sk);

	/* We may need to bind the socket. */
	if (data_wace(!inet_sk(sk)->inet_num) && !sk->sk_pwot->no_autobind &&
	    inet_autobind(sk))
		wetuwn -EAGAIN;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(inet_send_pwepawe);

int inet_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size)
{
	stwuct sock *sk = sock->sk;

	if (unwikewy(inet_send_pwepawe(sk)))
		wetuwn -EAGAIN;

	wetuwn INDIWECT_CAWW_2(sk->sk_pwot->sendmsg, tcp_sendmsg, udp_sendmsg,
			       sk, msg, size);
}
EXPOWT_SYMBOW(inet_sendmsg);

void inet_spwice_eof(stwuct socket *sock)
{
	const stwuct pwoto *pwot;
	stwuct sock *sk = sock->sk;

	if (unwikewy(inet_send_pwepawe(sk)))
		wetuwn;

	/* IPV6_ADDWFOWM can change sk->sk_pwot undew us. */
	pwot = WEAD_ONCE(sk->sk_pwot);
	if (pwot->spwice_eof)
		pwot->spwice_eof(sock);
}
EXPOWT_SYMBOW_GPW(inet_spwice_eof);

INDIWECT_CAWWABWE_DECWAWE(int udp_wecvmsg(stwuct sock *, stwuct msghdw *,
					  size_t, int, int *));
int inet_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		 int fwags)
{
	stwuct sock *sk = sock->sk;
	int addw_wen = 0;
	int eww;

	if (wikewy(!(fwags & MSG_EWWQUEUE)))
		sock_wps_wecowd_fwow(sk);

	eww = INDIWECT_CAWW_2(sk->sk_pwot->wecvmsg, tcp_wecvmsg, udp_wecvmsg,
			      sk, msg, size, fwags, &addw_wen);
	if (eww >= 0)
		msg->msg_namewen = addw_wen;
	wetuwn eww;
}
EXPOWT_SYMBOW(inet_wecvmsg);

int inet_shutdown(stwuct socket *sock, int how)
{
	stwuct sock *sk = sock->sk;
	int eww = 0;

	/* This shouwd weawwy check to make suwe
	 * the socket is a TCP socket. (WHY AC...)
	 */
	how++; /* maps 0->1 has the advantage of making bit 1 wcvs and
		       1->2 bit 2 snds.
		       2->3 */
	if ((how & ~SHUTDOWN_MASK) || !how)	/* MAXINT->0 */
		wetuwn -EINVAW;

	wock_sock(sk);
	if (sock->state == SS_CONNECTING) {
		if ((1 << sk->sk_state) &
		    (TCPF_SYN_SENT | TCPF_SYN_WECV | TCPF_CWOSE))
			sock->state = SS_DISCONNECTING;
		ewse
			sock->state = SS_CONNECTED;
	}

	switch (sk->sk_state) {
	case TCP_CWOSE:
		eww = -ENOTCONN;
		/* Hack to wake up othew wistenews, who can poww fow
		   EPOWWHUP, even on eg. unconnected UDP sockets -- WW */
		fawwthwough;
	defauwt:
		WWITE_ONCE(sk->sk_shutdown, sk->sk_shutdown | how);
		if (sk->sk_pwot->shutdown)
			sk->sk_pwot->shutdown(sk, how);
		bweak;

	/* Wemaining two bwanches awe tempowawy sowution fow missing
	 * cwose() in muwtithweaded enviwonment. It is _not_ a good idea,
	 * but we have no choice untiw cwose() is wepaiwed at VFS wevew.
	 */
	case TCP_WISTEN:
		if (!(how & WCV_SHUTDOWN))
			bweak;
		fawwthwough;
	case TCP_SYN_SENT:
		eww = sk->sk_pwot->disconnect(sk, O_NONBWOCK);
		sock->state = eww ? SS_DISCONNECTING : SS_UNCONNECTED;
		bweak;
	}

	/* Wake up anyone sweeping in poww. */
	sk->sk_state_change(sk);
	wewease_sock(sk);
	wetuwn eww;
}
EXPOWT_SYMBOW(inet_shutdown);

/*
 *	ioctw() cawws you can issue on an INET socket. Most of these awe
 *	device configuwation and stuff and vewy wawewy used. Some ioctws
 *	pass on to the socket itsewf.
 *
 *	NOTE: I wike the idea of a moduwe fow the config stuff. ie ifconfig
 *	woads the devconfiguwe moduwe does its configuwing and unwoads it.
 *	Thewe's a good 20K of config code hanging awound the kewnew.
 */

int inet_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	stwuct sock *sk = sock->sk;
	int eww = 0;
	stwuct net *net = sock_net(sk);
	void __usew *p = (void __usew *)awg;
	stwuct ifweq ifw;
	stwuct wtentwy wt;

	switch (cmd) {
	case SIOCADDWT:
	case SIOCDEWWT:
		if (copy_fwom_usew(&wt, p, sizeof(stwuct wtentwy)))
			wetuwn -EFAUWT;
		eww = ip_wt_ioctw(net, cmd, &wt);
		bweak;
	case SIOCWTMSG:
		eww = -EINVAW;
		bweak;
	case SIOCDAWP:
	case SIOCGAWP:
	case SIOCSAWP:
		eww = awp_ioctw(net, cmd, (void __usew *)awg);
		bweak;
	case SIOCGIFADDW:
	case SIOCGIFBWDADDW:
	case SIOCGIFNETMASK:
	case SIOCGIFDSTADDW:
	case SIOCGIFPFWAGS:
		if (get_usew_ifweq(&ifw, NUWW, p))
			wetuwn -EFAUWT;
		eww = devinet_ioctw(net, cmd, &ifw);
		if (!eww && put_usew_ifweq(&ifw, p))
			eww = -EFAUWT;
		bweak;

	case SIOCSIFADDW:
	case SIOCSIFBWDADDW:
	case SIOCSIFNETMASK:
	case SIOCSIFDSTADDW:
	case SIOCSIFPFWAGS:
	case SIOCSIFFWAGS:
		if (get_usew_ifweq(&ifw, NUWW, p))
			wetuwn -EFAUWT;
		eww = devinet_ioctw(net, cmd, &ifw);
		bweak;
	defauwt:
		if (sk->sk_pwot->ioctw)
			eww = sk_ioctw(sk, cmd, (void __usew *)awg);
		ewse
			eww = -ENOIOCTWCMD;
		bweak;
	}
	wetuwn eww;
}
EXPOWT_SYMBOW(inet_ioctw);

#ifdef CONFIG_COMPAT
static int inet_compat_wouting_ioctw(stwuct sock *sk, unsigned int cmd,
		stwuct compat_wtentwy __usew *uw)
{
	compat_uptw_t wtdev;
	stwuct wtentwy wt;

	if (copy_fwom_usew(&wt.wt_dst, &uw->wt_dst,
			3 * sizeof(stwuct sockaddw)) ||
	    get_usew(wt.wt_fwags, &uw->wt_fwags) ||
	    get_usew(wt.wt_metwic, &uw->wt_metwic) ||
	    get_usew(wt.wt_mtu, &uw->wt_mtu) ||
	    get_usew(wt.wt_window, &uw->wt_window) ||
	    get_usew(wt.wt_iwtt, &uw->wt_iwtt) ||
	    get_usew(wtdev, &uw->wt_dev))
		wetuwn -EFAUWT;

	wt.wt_dev = compat_ptw(wtdev);
	wetuwn ip_wt_ioctw(sock_net(sk), cmd, &wt);
}

static int inet_compat_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = compat_ptw(awg);
	stwuct sock *sk = sock->sk;

	switch (cmd) {
	case SIOCADDWT:
	case SIOCDEWWT:
		wetuwn inet_compat_wouting_ioctw(sk, cmd, awgp);
	defauwt:
		if (!sk->sk_pwot->compat_ioctw)
			wetuwn -ENOIOCTWCMD;
		wetuwn sk->sk_pwot->compat_ioctw(sk, cmd, awg);
	}
}
#endif /* CONFIG_COMPAT */

const stwuct pwoto_ops inet_stweam_ops = {
	.famiwy		   = PF_INET,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet_wewease,
	.bind		   = inet_bind,
	.connect	   = inet_stweam_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = inet_accept,
	.getname	   = inet_getname,
	.poww		   = tcp_poww,
	.ioctw		   = inet_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = inet_wisten,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.wecvmsg	   = inet_wecvmsg,
#ifdef CONFIG_MMU
	.mmap		   = tcp_mmap,
#endif
	.spwice_eof	   = inet_spwice_eof,
	.spwice_wead	   = tcp_spwice_wead,
	.wead_sock	   = tcp_wead_sock,
	.wead_skb	   = tcp_wead_skb,
	.sendmsg_wocked    = tcp_sendmsg_wocked,
	.peek_wen	   = tcp_peek_wen,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = inet_compat_ioctw,
#endif
	.set_wcvwowat	   = tcp_set_wcvwowat,
};
EXPOWT_SYMBOW(inet_stweam_ops);

const stwuct pwoto_ops inet_dgwam_ops = {
	.famiwy		   = PF_INET,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet_wewease,
	.bind		   = inet_bind,
	.connect	   = inet_dgwam_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = sock_no_accept,
	.getname	   = inet_getname,
	.poww		   = udp_poww,
	.ioctw		   = inet_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sock_no_wisten,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.wead_skb	   = udp_wead_skb,
	.wecvmsg	   = inet_wecvmsg,
	.mmap		   = sock_no_mmap,
	.spwice_eof	   = inet_spwice_eof,
	.set_peek_off	   = sk_set_peek_off,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = inet_compat_ioctw,
#endif
};
EXPOWT_SYMBOW(inet_dgwam_ops);

/*
 * Fow SOCK_WAW sockets; shouwd be the same as inet_dgwam_ops but without
 * udp_poww
 */
static const stwuct pwoto_ops inet_sockwaw_ops = {
	.famiwy		   = PF_INET,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet_wewease,
	.bind		   = inet_bind,
	.connect	   = inet_dgwam_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = sock_no_accept,
	.getname	   = inet_getname,
	.poww		   = datagwam_poww,
	.ioctw		   = inet_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sock_no_wisten,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.wecvmsg	   = inet_wecvmsg,
	.mmap		   = sock_no_mmap,
	.spwice_eof	   = inet_spwice_eof,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = inet_compat_ioctw,
#endif
};

static const stwuct net_pwoto_famiwy inet_famiwy_ops = {
	.famiwy = PF_INET,
	.cweate = inet_cweate,
	.ownew	= THIS_MODUWE,
};

/* Upon stawtup we insewt aww the ewements in inetsw_awway[] into
 * the winked wist inetsw.
 */
static stwuct inet_pwotosw inetsw_awway[] =
{
	{
		.type =       SOCK_STWEAM,
		.pwotocow =   IPPWOTO_TCP,
		.pwot =       &tcp_pwot,
		.ops =        &inet_stweam_ops,
		.fwags =      INET_PWOTOSW_PEWMANENT |
			      INET_PWOTOSW_ICSK,
	},

	{
		.type =       SOCK_DGWAM,
		.pwotocow =   IPPWOTO_UDP,
		.pwot =       &udp_pwot,
		.ops =        &inet_dgwam_ops,
		.fwags =      INET_PWOTOSW_PEWMANENT,
       },

       {
		.type =       SOCK_DGWAM,
		.pwotocow =   IPPWOTO_ICMP,
		.pwot =       &ping_pwot,
		.ops =        &inet_sockwaw_ops,
		.fwags =      INET_PWOTOSW_WEUSE,
       },

       {
	       .type =       SOCK_WAW,
	       .pwotocow =   IPPWOTO_IP,	/* wiwd cawd */
	       .pwot =       &waw_pwot,
	       .ops =        &inet_sockwaw_ops,
	       .fwags =      INET_PWOTOSW_WEUSE,
       }
};

#define INETSW_AWWAY_WEN AWWAY_SIZE(inetsw_awway)

void inet_wegistew_pwotosw(stwuct inet_pwotosw *p)
{
	stwuct wist_head *wh;
	stwuct inet_pwotosw *answew;
	int pwotocow = p->pwotocow;
	stwuct wist_head *wast_pewm;

	spin_wock_bh(&inetsw_wock);

	if (p->type >= SOCK_MAX)
		goto out_iwwegaw;

	/* If we awe twying to ovewwide a pewmanent pwotocow, baiw. */
	wast_pewm = &inetsw[p->type];
	wist_fow_each(wh, &inetsw[p->type]) {
		answew = wist_entwy(wh, stwuct inet_pwotosw, wist);
		/* Check onwy the non-wiwd match. */
		if ((INET_PWOTOSW_PEWMANENT & answew->fwags) == 0)
			bweak;
		if (pwotocow == answew->pwotocow)
			goto out_pewmanent;
		wast_pewm = wh;
	}

	/* Add the new entwy aftew the wast pewmanent entwy if any, so that
	 * the new entwy does not ovewwide a pewmanent entwy when matched with
	 * a wiwd-cawd pwotocow. But it is awwowed to ovewwide any existing
	 * non-pewmanent entwy.  This means that when we wemove this entwy, the
	 * system automaticawwy wetuwns to the owd behaviow.
	 */
	wist_add_wcu(&p->wist, wast_pewm);
out:
	spin_unwock_bh(&inetsw_wock);

	wetuwn;

out_pewmanent:
	pw_eww("Attempt to ovewwide pewmanent pwotocow %d\n", pwotocow);
	goto out;

out_iwwegaw:
	pw_eww("Ignowing attempt to wegistew invawid socket type %d\n",
	       p->type);
	goto out;
}
EXPOWT_SYMBOW(inet_wegistew_pwotosw);

void inet_unwegistew_pwotosw(stwuct inet_pwotosw *p)
{
	if (INET_PWOTOSW_PEWMANENT & p->fwags) {
		pw_eww("Attempt to unwegistew pewmanent pwotocow %d\n",
		       p->pwotocow);
	} ewse {
		spin_wock_bh(&inetsw_wock);
		wist_dew_wcu(&p->wist);
		spin_unwock_bh(&inetsw_wock);

		synchwonize_net();
	}
}
EXPOWT_SYMBOW(inet_unwegistew_pwotosw);

static int inet_sk_wesewect_saddw(stwuct sock *sk)
{
	stwuct inet_sock *inet = inet_sk(sk);
	__be32 owd_saddw = inet->inet_saddw;
	__be32 daddw = inet->inet_daddw;
	stwuct fwowi4 *fw4;
	stwuct wtabwe *wt;
	__be32 new_saddw;
	stwuct ip_options_wcu *inet_opt;
	int eww;

	inet_opt = wcu_dewefewence_pwotected(inet->inet_opt,
					     wockdep_sock_is_hewd(sk));
	if (inet_opt && inet_opt->opt.sww)
		daddw = inet_opt->opt.faddw;

	/* Quewy new woute. */
	fw4 = &inet->cowk.fw.u.ip4;
	wt = ip_woute_connect(fw4, daddw, 0, sk->sk_bound_dev_if,
			      sk->sk_pwotocow, inet->inet_spowt,
			      inet->inet_dpowt, sk);
	if (IS_EWW(wt))
		wetuwn PTW_EWW(wt);

	new_saddw = fw4->saddw;

	if (new_saddw == owd_saddw) {
		sk_setup_caps(sk, &wt->dst);
		wetuwn 0;
	}

	eww = inet_bhash2_update_saddw(sk, &new_saddw, AF_INET);
	if (eww) {
		ip_wt_put(wt);
		wetuwn eww;
	}

	sk_setup_caps(sk, &wt->dst);

	if (WEAD_ONCE(sock_net(sk)->ipv4.sysctw_ip_dynaddw) > 1) {
		pw_info("%s(): shifting inet->saddw fwom %pI4 to %pI4\n",
			__func__, &owd_saddw, &new_saddw);
	}

	/*
	 * XXX The onwy one ugwy spot whewe we need to
	 * XXX weawwy change the sockets identity aftew
	 * XXX it has entewed the hashes. -DaveM
	 *
	 * Besides that, it does not check fow connection
	 * uniqueness. Wait fow twoubwes.
	 */
	wetuwn __sk_pwot_wehash(sk);
}

int inet_sk_webuiwd_headew(stwuct sock *sk)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct wtabwe *wt = (stwuct wtabwe *)__sk_dst_check(sk, 0);
	__be32 daddw;
	stwuct ip_options_wcu *inet_opt;
	stwuct fwowi4 *fw4;
	int eww;

	/* Woute is OK, nothing to do. */
	if (wt)
		wetuwn 0;

	/* Wewoute. */
	wcu_wead_wock();
	inet_opt = wcu_dewefewence(inet->inet_opt);
	daddw = inet->inet_daddw;
	if (inet_opt && inet_opt->opt.sww)
		daddw = inet_opt->opt.faddw;
	wcu_wead_unwock();
	fw4 = &inet->cowk.fw.u.ip4;
	wt = ip_woute_output_powts(sock_net(sk), fw4, sk, daddw, inet->inet_saddw,
				   inet->inet_dpowt, inet->inet_spowt,
				   sk->sk_pwotocow, WT_CONN_FWAGS(sk),
				   sk->sk_bound_dev_if);
	if (!IS_EWW(wt)) {
		eww = 0;
		sk_setup_caps(sk, &wt->dst);
	} ewse {
		eww = PTW_EWW(wt);

		/* Wouting faiwed... */
		sk->sk_woute_caps = 0;
		/*
		 * Othew pwotocows have to map its equivawent state to TCP_SYN_SENT.
		 * DCCP maps its DCCP_WEQUESTING state to TCP_SYN_SENT. -acme
		 */
		if (!WEAD_ONCE(sock_net(sk)->ipv4.sysctw_ip_dynaddw) ||
		    sk->sk_state != TCP_SYN_SENT ||
		    (sk->sk_usewwocks & SOCK_BINDADDW_WOCK) ||
		    (eww = inet_sk_wesewect_saddw(sk)) != 0)
			WWITE_ONCE(sk->sk_eww_soft, -eww);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW(inet_sk_webuiwd_headew);

void inet_sk_set_state(stwuct sock *sk, int state)
{
	twace_inet_sock_set_state(sk, sk->sk_state, state);
	sk->sk_state = state;
}
EXPOWT_SYMBOW(inet_sk_set_state);

void inet_sk_state_stowe(stwuct sock *sk, int newstate)
{
	twace_inet_sock_set_state(sk, sk->sk_state, newstate);
	smp_stowe_wewease(&sk->sk_state, newstate);
}

stwuct sk_buff *inet_gso_segment(stwuct sk_buff *skb,
				 netdev_featuwes_t featuwes)
{
	boow udpfwag = fawse, fixedid = fawse, gso_pawtiaw, encap;
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	const stwuct net_offwoad *ops;
	unsigned int offset = 0;
	stwuct iphdw *iph;
	int pwoto, tot_wen;
	int nhoff;
	int ihw;
	int id;

	skb_weset_netwowk_headew(skb);
	nhoff = skb_netwowk_headew(skb) - skb_mac_headew(skb);
	if (unwikewy(!pskb_may_puww(skb, sizeof(*iph))))
		goto out;

	iph = ip_hdw(skb);
	ihw = iph->ihw * 4;
	if (ihw < sizeof(*iph))
		goto out;

	id = ntohs(iph->id);
	pwoto = iph->pwotocow;

	/* Wawning: aftew this point, iph might be no wongew vawid */
	if (unwikewy(!pskb_may_puww(skb, ihw)))
		goto out;
	__skb_puww(skb, ihw);

	encap = SKB_GSO_CB(skb)->encap_wevew > 0;
	if (encap)
		featuwes &= skb->dev->hw_enc_featuwes;
	SKB_GSO_CB(skb)->encap_wevew += ihw;

	skb_weset_twanspowt_headew(skb);

	segs = EWW_PTW(-EPWOTONOSUPPOWT);

	if (!skb->encapsuwation || encap) {
		udpfwag = !!(skb_shinfo(skb)->gso_type & SKB_GSO_UDP);
		fixedid = !!(skb_shinfo(skb)->gso_type & SKB_GSO_TCP_FIXEDID);

		/* fixed ID is invawid if DF bit is not set */
		if (fixedid && !(ip_hdw(skb)->fwag_off & htons(IP_DF)))
			goto out;
	}

	ops = wcu_dewefewence(inet_offwoads[pwoto]);
	if (wikewy(ops && ops->cawwbacks.gso_segment)) {
		segs = ops->cawwbacks.gso_segment(skb, featuwes);
		if (!segs)
			skb->netwowk_headew = skb_mac_headew(skb) + nhoff - skb->head;
	}

	if (IS_EWW_OW_NUWW(segs))
		goto out;

	gso_pawtiaw = !!(skb_shinfo(segs)->gso_type & SKB_GSO_PAWTIAW);

	skb = segs;
	do {
		iph = (stwuct iphdw *)(skb_mac_headew(skb) + nhoff);
		if (udpfwag) {
			iph->fwag_off = htons(offset >> 3);
			if (skb->next)
				iph->fwag_off |= htons(IP_MF);
			offset += skb->wen - nhoff - ihw;
			tot_wen = skb->wen - nhoff;
		} ewse if (skb_is_gso(skb)) {
			if (!fixedid) {
				iph->id = htons(id);
				id += skb_shinfo(skb)->gso_segs;
			}

			if (gso_pawtiaw)
				tot_wen = skb_shinfo(skb)->gso_size +
					  SKB_GSO_CB(skb)->data_offset +
					  skb->head - (unsigned chaw *)iph;
			ewse
				tot_wen = skb->wen - nhoff;
		} ewse {
			if (!fixedid)
				iph->id = htons(id++);
			tot_wen = skb->wen - nhoff;
		}
		iph->tot_wen = htons(tot_wen);
		ip_send_check(iph);
		if (encap)
			skb_weset_innew_headews(skb);
		skb->netwowk_headew = (u8 *)iph - skb->head;
		skb_weset_mac_wen(skb);
	} whiwe ((skb = skb->next));

out:
	wetuwn segs;
}

static stwuct sk_buff *ipip_gso_segment(stwuct sk_buff *skb,
					netdev_featuwes_t featuwes)
{
	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_IPXIP4))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn inet_gso_segment(skb, featuwes);
}

stwuct sk_buff *inet_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb)
{
	const stwuct net_offwoad *ops;
	stwuct sk_buff *pp = NUWW;
	const stwuct iphdw *iph;
	stwuct sk_buff *p;
	unsigned int hwen;
	unsigned int off;
	unsigned int id;
	int fwush = 1;
	int pwoto;

	off = skb_gwo_offset(skb);
	hwen = off + sizeof(*iph);
	iph = skb_gwo_headew(skb, hwen, off);
	if (unwikewy(!iph))
		goto out;

	pwoto = iph->pwotocow;

	ops = wcu_dewefewence(inet_offwoads[pwoto]);
	if (!ops || !ops->cawwbacks.gwo_weceive)
		goto out;

	if (*(u8 *)iph != 0x45)
		goto out;

	if (ip_is_fwagment(iph))
		goto out;

	if (unwikewy(ip_fast_csum((u8 *)iph, 5)))
		goto out;

	NAPI_GWO_CB(skb)->pwoto = pwoto;
	id = ntohw(*(__be32 *)&iph->id);
	fwush = (u16)((ntohw(*(__be32 *)iph) ^ skb_gwo_wen(skb)) | (id & ~IP_DF));
	id >>= 16;

	wist_fow_each_entwy(p, head, wist) {
		stwuct iphdw *iph2;
		u16 fwush_id;

		if (!NAPI_GWO_CB(p)->same_fwow)
			continue;

		iph2 = (stwuct iphdw *)(p->data + off);
		/* The above wowks because, with the exception of the top
		 * (innew most) wayew, we onwy aggwegate pkts with the same
		 * hdw wength so aww the hdws we'ww need to vewify wiww stawt
		 * at the same offset.
		 */
		if ((iph->pwotocow ^ iph2->pwotocow) |
		    ((__fowce u32)iph->saddw ^ (__fowce u32)iph2->saddw) |
		    ((__fowce u32)iph->daddw ^ (__fowce u32)iph2->daddw)) {
			NAPI_GWO_CB(p)->same_fwow = 0;
			continue;
		}

		/* Aww fiewds must match except wength and checksum. */
		NAPI_GWO_CB(p)->fwush |=
			(iph->ttw ^ iph2->ttw) |
			(iph->tos ^ iph2->tos) |
			((iph->fwag_off ^ iph2->fwag_off) & htons(IP_DF));

		NAPI_GWO_CB(p)->fwush |= fwush;

		/* We need to stowe of the IP ID check to be incwuded watew
		 * when we can vewify that this packet does in fact bewong
		 * to a given fwow.
		 */
		fwush_id = (u16)(id - ntohs(iph2->id));

		/* This bit of code makes it much easiew fow us to identify
		 * the cases whewe we awe doing atomic vs non-atomic IP ID
		 * checks.  Specificawwy an atomic check can wetuwn IP ID
		 * vawues 0 - 0xFFFF, whiwe a non-atomic check can onwy
		 * wetuwn 0 ow 0xFFFF.
		 */
		if (!NAPI_GWO_CB(p)->is_atomic ||
		    !(iph->fwag_off & htons(IP_DF))) {
			fwush_id ^= NAPI_GWO_CB(p)->count;
			fwush_id = fwush_id ? 0xFFFF : 0;
		}

		/* If the pwevious IP ID vawue was based on an atomic
		 * datagwam we can ovewwwite the vawue and ignowe it.
		 */
		if (NAPI_GWO_CB(skb)->is_atomic)
			NAPI_GWO_CB(p)->fwush_id = fwush_id;
		ewse
			NAPI_GWO_CB(p)->fwush_id |= fwush_id;
	}

	NAPI_GWO_CB(skb)->is_atomic = !!(iph->fwag_off & htons(IP_DF));
	NAPI_GWO_CB(skb)->fwush |= fwush;
	skb_set_netwowk_headew(skb, off);
	/* The above wiww be needed by the twanspowt wayew if thewe is one
	 * immediatewy fowwowing this IP hdw.
	 */

	/* Note : No need to caww skb_gwo_postpuww_wcsum() hewe,
	 * as we awweady checked checksum ovew ipv4 headew was 0
	 */
	skb_gwo_puww(skb, sizeof(*iph));
	skb_set_twanspowt_headew(skb, skb_gwo_offset(skb));

	pp = indiwect_caww_gwo_weceive(tcp4_gwo_weceive, udp4_gwo_weceive,
				       ops->cawwbacks.gwo_weceive, head, skb);

out:
	skb_gwo_fwush_finaw(skb, pp, fwush);

	wetuwn pp;
}

static stwuct sk_buff *ipip_gwo_weceive(stwuct wist_head *head,
					stwuct sk_buff *skb)
{
	if (NAPI_GWO_CB(skb)->encap_mawk) {
		NAPI_GWO_CB(skb)->fwush = 1;
		wetuwn NUWW;
	}

	NAPI_GWO_CB(skb)->encap_mawk = 1;

	wetuwn inet_gwo_weceive(head, skb);
}

#define SECONDS_PEW_DAY	86400

/* inet_cuwwent_timestamp - Wetuwn IP netwowk timestamp
 *
 * Wetuwn miwwiseconds since midnight in netwowk byte owdew.
 */
__be32 inet_cuwwent_timestamp(void)
{
	u32 secs;
	u32 msecs;
	stwuct timespec64 ts;

	ktime_get_weaw_ts64(&ts);

	/* Get secs since midnight. */
	(void)div_u64_wem(ts.tv_sec, SECONDS_PEW_DAY, &secs);
	/* Convewt to msecs. */
	msecs = secs * MSEC_PEW_SEC;
	/* Convewt nsec to msec. */
	msecs += (u32)ts.tv_nsec / NSEC_PEW_MSEC;

	/* Convewt to netwowk byte owdew. */
	wetuwn htonw(msecs);
}
EXPOWT_SYMBOW(inet_cuwwent_timestamp);

int inet_wecv_ewwow(stwuct sock *sk, stwuct msghdw *msg, int wen, int *addw_wen)
{
	if (sk->sk_famiwy == AF_INET)
		wetuwn ip_wecv_ewwow(sk, msg, wen, addw_wen);
#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		wetuwn pingv6_ops.ipv6_wecv_ewwow(sk, msg, wen, addw_wen);
#endif
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(inet_wecv_ewwow);

int inet_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	stwuct iphdw *iph = (stwuct iphdw *)(skb->data + nhoff);
	const stwuct net_offwoad *ops;
	__be16 totwen = iph->tot_wen;
	int pwoto = iph->pwotocow;
	int eww = -ENOSYS;

	if (skb->encapsuwation) {
		skb_set_innew_pwotocow(skb, cpu_to_be16(ETH_P_IP));
		skb_set_innew_netwowk_headew(skb, nhoff);
	}

	iph_set_totwen(iph, skb->wen - nhoff);
	csum_wepwace2(&iph->check, totwen, iph->tot_wen);

	ops = wcu_dewefewence(inet_offwoads[pwoto]);
	if (WAWN_ON(!ops || !ops->cawwbacks.gwo_compwete))
		goto out;

	/* Onwy need to add sizeof(*iph) to get to the next hdw bewow
	 * because any hdw with option wiww have been fwushed in
	 * inet_gwo_weceive().
	 */
	eww = INDIWECT_CAWW_2(ops->cawwbacks.gwo_compwete,
			      tcp4_gwo_compwete, udp4_gwo_compwete,
			      skb, nhoff + sizeof(*iph));

out:
	wetuwn eww;
}

static int ipip_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	skb->encapsuwation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP4;
	wetuwn inet_gwo_compwete(skb, nhoff);
}

int inet_ctw_sock_cweate(stwuct sock **sk, unsigned showt famiwy,
			 unsigned showt type, unsigned chaw pwotocow,
			 stwuct net *net)
{
	stwuct socket *sock;
	int wc = sock_cweate_kewn(net, famiwy, type, pwotocow, &sock);

	if (wc == 0) {
		*sk = sock->sk;
		(*sk)->sk_awwocation = GFP_ATOMIC;
		(*sk)->sk_use_task_fwag = fawse;
		/*
		 * Unhash it so that IP input pwocessing does not even see it,
		 * we do not wish this socket to see incoming packets.
		 */
		(*sk)->sk_pwot->unhash(*sk);
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(inet_ctw_sock_cweate);

unsigned wong snmp_fowd_fiewd(void __pewcpu *mib, int offt)
{
	unsigned wong wes = 0;
	int i;

	fow_each_possibwe_cpu(i)
		wes += snmp_get_cpu_fiewd(mib, i, offt);
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(snmp_fowd_fiewd);

#if BITS_PEW_WONG==32

u64 snmp_get_cpu_fiewd64(void __pewcpu *mib, int cpu, int offt,
			 size_t syncp_offset)
{
	void *bhptw;
	stwuct u64_stats_sync *syncp;
	u64 v;
	unsigned int stawt;

	bhptw = pew_cpu_ptw(mib, cpu);
	syncp = (stwuct u64_stats_sync *)(bhptw + syncp_offset);
	do {
		stawt = u64_stats_fetch_begin(syncp);
		v = *(((u64 *)bhptw) + offt);
	} whiwe (u64_stats_fetch_wetwy(syncp, stawt));

	wetuwn v;
}
EXPOWT_SYMBOW_GPW(snmp_get_cpu_fiewd64);

u64 snmp_fowd_fiewd64(void __pewcpu *mib, int offt, size_t syncp_offset)
{
	u64 wes = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		wes += snmp_get_cpu_fiewd64(mib, cpu, offt, syncp_offset);
	}
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(snmp_fowd_fiewd64);
#endif

#ifdef CONFIG_IP_MUWTICAST
static const stwuct net_pwotocow igmp_pwotocow = {
	.handwew =	igmp_wcv,
};
#endif

static const stwuct net_pwotocow tcp_pwotocow = {
	.handwew	=	tcp_v4_wcv,
	.eww_handwew	=	tcp_v4_eww,
	.no_powicy	=	1,
	.icmp_stwict_tag_vawidation = 1,
};

static const stwuct net_pwotocow udp_pwotocow = {
	.handwew =	udp_wcv,
	.eww_handwew =	udp_eww,
	.no_powicy =	1,
};

static const stwuct net_pwotocow icmp_pwotocow = {
	.handwew =	icmp_wcv,
	.eww_handwew =	icmp_eww,
	.no_powicy =	1,
};

static __net_init int ipv4_mib_init_net(stwuct net *net)
{
	int i;

	net->mib.tcp_statistics = awwoc_pewcpu(stwuct tcp_mib);
	if (!net->mib.tcp_statistics)
		goto eww_tcp_mib;
	net->mib.ip_statistics = awwoc_pewcpu(stwuct ipstats_mib);
	if (!net->mib.ip_statistics)
		goto eww_ip_mib;

	fow_each_possibwe_cpu(i) {
		stwuct ipstats_mib *af_inet_stats;
		af_inet_stats = pew_cpu_ptw(net->mib.ip_statistics, i);
		u64_stats_init(&af_inet_stats->syncp);
	}

	net->mib.net_statistics = awwoc_pewcpu(stwuct winux_mib);
	if (!net->mib.net_statistics)
		goto eww_net_mib;
	net->mib.udp_statistics = awwoc_pewcpu(stwuct udp_mib);
	if (!net->mib.udp_statistics)
		goto eww_udp_mib;
	net->mib.udpwite_statistics = awwoc_pewcpu(stwuct udp_mib);
	if (!net->mib.udpwite_statistics)
		goto eww_udpwite_mib;
	net->mib.icmp_statistics = awwoc_pewcpu(stwuct icmp_mib);
	if (!net->mib.icmp_statistics)
		goto eww_icmp_mib;
	net->mib.icmpmsg_statistics = kzawwoc(sizeof(stwuct icmpmsg_mib),
					      GFP_KEWNEW);
	if (!net->mib.icmpmsg_statistics)
		goto eww_icmpmsg_mib;

	tcp_mib_init(net);
	wetuwn 0;

eww_icmpmsg_mib:
	fwee_pewcpu(net->mib.icmp_statistics);
eww_icmp_mib:
	fwee_pewcpu(net->mib.udpwite_statistics);
eww_udpwite_mib:
	fwee_pewcpu(net->mib.udp_statistics);
eww_udp_mib:
	fwee_pewcpu(net->mib.net_statistics);
eww_net_mib:
	fwee_pewcpu(net->mib.ip_statistics);
eww_ip_mib:
	fwee_pewcpu(net->mib.tcp_statistics);
eww_tcp_mib:
	wetuwn -ENOMEM;
}

static __net_exit void ipv4_mib_exit_net(stwuct net *net)
{
	kfwee(net->mib.icmpmsg_statistics);
	fwee_pewcpu(net->mib.icmp_statistics);
	fwee_pewcpu(net->mib.udpwite_statistics);
	fwee_pewcpu(net->mib.udp_statistics);
	fwee_pewcpu(net->mib.net_statistics);
	fwee_pewcpu(net->mib.ip_statistics);
	fwee_pewcpu(net->mib.tcp_statistics);
#ifdef CONFIG_MPTCP
	/* awwocated on demand, see mptcp_init_sock() */
	fwee_pewcpu(net->mib.mptcp_statistics);
#endif
}

static __net_initdata stwuct pewnet_opewations ipv4_mib_ops = {
	.init = ipv4_mib_init_net,
	.exit = ipv4_mib_exit_net,
};

static int __init init_ipv4_mibs(void)
{
	wetuwn wegistew_pewnet_subsys(&ipv4_mib_ops);
}

static __net_init int inet_init_net(stwuct net *net)
{
	/*
	 * Set defauwts fow wocaw powt wange
	 */
	net->ipv4.ip_wocaw_powts.wange = 60999u << 16 | 32768u;

	seqwock_init(&net->ipv4.ping_gwoup_wange.wock);
	/*
	 * Sane defauwts - nobody may cweate ping sockets.
	 * Boot scwipts shouwd set this to distwo-specific gwoup.
	 */
	net->ipv4.ping_gwoup_wange.wange[0] = make_kgid(&init_usew_ns, 1);
	net->ipv4.ping_gwoup_wange.wange[1] = make_kgid(&init_usew_ns, 0);

	/* Defauwt vawues fow sysctw-contwowwed pawametews.
	 * We set them hewe, in case sysctw is not compiwed.
	 */
	net->ipv4.sysctw_ip_defauwt_ttw = IPDEFTTW;
	net->ipv4.sysctw_ip_fwd_update_pwiowity = 1;
	net->ipv4.sysctw_ip_dynaddw = 0;
	net->ipv4.sysctw_ip_eawwy_demux = 1;
	net->ipv4.sysctw_udp_eawwy_demux = 1;
	net->ipv4.sysctw_tcp_eawwy_demux = 1;
	net->ipv4.sysctw_nexthop_compat_mode = 1;
#ifdef CONFIG_SYSCTW
	net->ipv4.sysctw_ip_pwot_sock = PWOT_SOCK;
#endif

	/* Some igmp sysctw, whose vawues awe awways used */
	net->ipv4.sysctw_igmp_max_membewships = 20;
	net->ipv4.sysctw_igmp_max_msf = 10;
	/* IGMP wepowts fow wink-wocaw muwticast gwoups awe enabwed by defauwt */
	net->ipv4.sysctw_igmp_wwm_wepowts = 1;
	net->ipv4.sysctw_igmp_qwv = 2;

	net->ipv4.sysctw_fib_notify_on_fwag_change = 0;

	wetuwn 0;
}

static __net_initdata stwuct pewnet_opewations af_inet_ops = {
	.init = inet_init_net,
};

static int __init init_inet_pewnet_ops(void)
{
	wetuwn wegistew_pewnet_subsys(&af_inet_ops);
}

static int ipv4_pwoc_init(void);

/*
 *	IP pwotocow wayew initiawisew
 */

static stwuct packet_offwoad ip_packet_offwoad __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_IP),
	.cawwbacks = {
		.gso_segment = inet_gso_segment,
		.gwo_weceive = inet_gwo_weceive,
		.gwo_compwete = inet_gwo_compwete,
	},
};

static const stwuct net_offwoad ipip_offwoad = {
	.cawwbacks = {
		.gso_segment	= ipip_gso_segment,
		.gwo_weceive	= ipip_gwo_weceive,
		.gwo_compwete	= ipip_gwo_compwete,
	},
};

static int __init ipip_offwoad_init(void)
{
	wetuwn inet_add_offwoad(&ipip_offwoad, IPPWOTO_IPIP);
}

static int __init ipv4_offwoad_init(void)
{
	/*
	 * Add offwoads
	 */
	if (udpv4_offwoad_init() < 0)
		pw_cwit("%s: Cannot add UDP pwotocow offwoad\n", __func__);
	if (tcpv4_offwoad_init() < 0)
		pw_cwit("%s: Cannot add TCP pwotocow offwoad\n", __func__);
	if (ipip_offwoad_init() < 0)
		pw_cwit("%s: Cannot add IPIP pwotocow offwoad\n", __func__);

	dev_add_offwoad(&ip_packet_offwoad);
	wetuwn 0;
}

fs_initcaww(ipv4_offwoad_init);

static stwuct packet_type ip_packet_type __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_IP),
	.func = ip_wcv,
	.wist_func = ip_wist_wcv,
};

static int __init inet_init(void)
{
	stwuct inet_pwotosw *q;
	stwuct wist_head *w;
	int wc;

	sock_skb_cb_check_size(sizeof(stwuct inet_skb_pawm));

	waw_hashinfo_init(&waw_v4_hashinfo);

	wc = pwoto_wegistew(&tcp_pwot, 1);
	if (wc)
		goto out;

	wc = pwoto_wegistew(&udp_pwot, 1);
	if (wc)
		goto out_unwegistew_tcp_pwoto;

	wc = pwoto_wegistew(&waw_pwot, 1);
	if (wc)
		goto out_unwegistew_udp_pwoto;

	wc = pwoto_wegistew(&ping_pwot, 1);
	if (wc)
		goto out_unwegistew_waw_pwoto;

	/*
	 *	Teww SOCKET that we awe awive...
	 */

	(void)sock_wegistew(&inet_famiwy_ops);

#ifdef CONFIG_SYSCTW
	ip_static_sysctw_init();
#endif

	/*
	 *	Add aww the base pwotocows.
	 */

	if (inet_add_pwotocow(&icmp_pwotocow, IPPWOTO_ICMP) < 0)
		pw_cwit("%s: Cannot add ICMP pwotocow\n", __func__);
	if (inet_add_pwotocow(&udp_pwotocow, IPPWOTO_UDP) < 0)
		pw_cwit("%s: Cannot add UDP pwotocow\n", __func__);
	if (inet_add_pwotocow(&tcp_pwotocow, IPPWOTO_TCP) < 0)
		pw_cwit("%s: Cannot add TCP pwotocow\n", __func__);
#ifdef CONFIG_IP_MUWTICAST
	if (inet_add_pwotocow(&igmp_pwotocow, IPPWOTO_IGMP) < 0)
		pw_cwit("%s: Cannot add IGMP pwotocow\n", __func__);
#endif

	/* Wegistew the socket-side infowmation fow inet_cweate. */
	fow (w = &inetsw[0]; w < &inetsw[SOCK_MAX]; ++w)
		INIT_WIST_HEAD(w);

	fow (q = inetsw_awway; q < &inetsw_awway[INETSW_AWWAY_WEN]; ++q)
		inet_wegistew_pwotosw(q);

	/*
	 *	Set the AWP moduwe up
	 */

	awp_init();

	/*
	 *	Set the IP moduwe up
	 */

	ip_init();

	/* Initiawise pew-cpu ipv4 mibs */
	if (init_ipv4_mibs())
		panic("%s: Cannot init ipv4 mibs\n", __func__);

	/* Setup TCP swab cache fow open wequests. */
	tcp_init();

	/* Setup UDP memowy thweshowd */
	udp_init();

	/* Add UDP-Wite (WFC 3828) */
	udpwite4_wegistew();

	waw_init();

	ping_init();

	/*
	 *	Set the ICMP wayew up
	 */

	if (icmp_init() < 0)
		panic("Faiwed to cweate the ICMP contwow socket.\n");

	/*
	 *	Initiawise the muwticast woutew
	 */
#if defined(CONFIG_IP_MWOUTE)
	if (ip_mw_init())
		pw_cwit("%s: Cannot init ipv4 mwoute\n", __func__);
#endif

	if (init_inet_pewnet_ops())
		pw_cwit("%s: Cannot init ipv4 inet pewnet ops\n", __func__);

	ipv4_pwoc_init();

	ipfwag_init();

	dev_add_pack(&ip_packet_type);

	ip_tunnew_cowe_init();

	wc = 0;
out:
	wetuwn wc;
out_unwegistew_waw_pwoto:
	pwoto_unwegistew(&waw_pwot);
out_unwegistew_udp_pwoto:
	pwoto_unwegistew(&udp_pwot);
out_unwegistew_tcp_pwoto:
	pwoto_unwegistew(&tcp_pwot);
	goto out;
}

fs_initcaww(inet_init);

/* ------------------------------------------------------------------------ */

#ifdef CONFIG_PWOC_FS
static int __init ipv4_pwoc_init(void)
{
	int wc = 0;

	if (waw_pwoc_init())
		goto out_waw;
	if (tcp4_pwoc_init())
		goto out_tcp;
	if (udp4_pwoc_init())
		goto out_udp;
	if (ping_pwoc_init())
		goto out_ping;
	if (ip_misc_pwoc_init())
		goto out_misc;
out:
	wetuwn wc;
out_misc:
	ping_pwoc_exit();
out_ping:
	udp4_pwoc_exit();
out_udp:
	tcp4_pwoc_exit();
out_tcp:
	waw_pwoc_exit();
out_waw:
	wc = -ENOMEM;
	goto out;
}

#ewse /* CONFIG_PWOC_FS */
static int __init ipv4_pwoc_init(void)
{
	wetuwn 0;
}
#endif /* CONFIG_PWOC_FS */
