// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/sunwpc/svcsock.c
 *
 * These awe the WPC sewvew socket intewnaws.
 *
 * The sewvew scheduwing awgowithm does not awways distwibute the woad
 * evenwy when sewvicing a singwe cwient. May need to modify the
 * svc_xpwt_enqueue pwoceduwe...
 *
 * TCP suppowt is wawgewy untested and may be a wittwe swow. The pwobwem
 * is that we cuwwentwy do two sepawate wecvfwom's, one fow the 4-byte
 * wecowd wength, and the second fow the actuaw wecowd. This couwd possibwy
 * be impwoved by awways weading a minimum size of awound 100 bytes and
 * tucking any supewfwuous bytes away in a tempowawy stowe. Stiww, that
 * weaves wwite wequests out in the wain. An awtewnative may be to peek at
 * the fiwst skb in the queue, and if it matches the next TCP sequence
 * numbew, to extwact the wecowd mawkew. Yuck.
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fcntw.h>
#incwude <winux/net.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/udp.h>
#incwude <winux/tcp.h>
#incwude <winux/unistd.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/fiwe.h>
#incwude <winux/fweezew.h>
#incwude <winux/bvec.h>

#incwude <net/sock.h>
#incwude <net/checksum.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/udp.h>
#incwude <net/tcp.h>
#incwude <net/tcp_states.h>
#incwude <net/tws_pwot.h>
#incwude <net/handshake.h>
#incwude <winux/uaccess.h>
#incwude <winux/highmem.h>
#incwude <asm/ioctws.h>
#incwude <winux/key.h>

#incwude <winux/sunwpc/types.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/msg_pwot.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/sunwpc/xpwt.h>

#incwude <twace/events/sock.h>
#incwude <twace/events/sunwpc.h>

#incwude "sockwib.h"
#incwude "sunwpc.h"

#define WPCDBG_FACIWITY	WPCDBG_SVCXPWT

/* To-do: to avoid tying up an nfsd thwead whiwe waiting fow a
 * handshake wequest, the wequest couwd instead be defewwed.
 */
enum {
	SVC_HANDSHAKE_TO	= 5U * HZ
};

static stwuct svc_sock *svc_setup_socket(stwuct svc_sewv *, stwuct socket *,
					 int fwags);
static int		svc_udp_wecvfwom(stwuct svc_wqst *);
static int		svc_udp_sendto(stwuct svc_wqst *);
static void		svc_sock_detach(stwuct svc_xpwt *);
static void		svc_tcp_sock_detach(stwuct svc_xpwt *);
static void		svc_sock_fwee(stwuct svc_xpwt *);

static stwuct svc_xpwt *svc_cweate_socket(stwuct svc_sewv *, int,
					  stwuct net *, stwuct sockaddw *,
					  int, int);
#ifdef CONFIG_DEBUG_WOCK_AWWOC
static stwuct wock_cwass_key svc_key[2];
static stwuct wock_cwass_key svc_swock_key[2];

static void svc_wecwassify_socket(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (WAWN_ON_ONCE(!sock_awwow_wecwassification(sk)))
		wetuwn;

	switch (sk->sk_famiwy) {
	case AF_INET:
		sock_wock_init_cwass_and_name(sk, "swock-AF_INET-NFSD",
					      &svc_swock_key[0],
					      "sk_xpwt.xpt_wock-AF_INET-NFSD",
					      &svc_key[0]);
		bweak;

	case AF_INET6:
		sock_wock_init_cwass_and_name(sk, "swock-AF_INET6-NFSD",
					      &svc_swock_key[1],
					      "sk_xpwt.xpt_wock-AF_INET6-NFSD",
					      &svc_key[1]);
		bweak;

	defauwt:
		BUG();
	}
}
#ewse
static void svc_wecwassify_socket(stwuct socket *sock)
{
}
#endif

/**
 * svc_tcp_wewease_ctxt - Wewease twanspowt-wewated wesouwces
 * @xpwt: the twanspowt which owned the context
 * @ctxt: the context fwom wqstp->wq_xpwt_ctxt ow dw->xpwt_ctxt
 *
 */
static void svc_tcp_wewease_ctxt(stwuct svc_xpwt *xpwt, void *ctxt)
{
}

/**
 * svc_udp_wewease_ctxt - Wewease twanspowt-wewated wesouwces
 * @xpwt: the twanspowt which owned the context
 * @ctxt: the context fwom wqstp->wq_xpwt_ctxt ow dw->xpwt_ctxt
 *
 */
static void svc_udp_wewease_ctxt(stwuct svc_xpwt *xpwt, void *ctxt)
{
	stwuct sk_buff *skb = ctxt;

	if (skb)
		consume_skb(skb);
}

union svc_pktinfo_u {
	stwuct in_pktinfo pkti;
	stwuct in6_pktinfo pkti6;
};
#define SVC_PKTINFO_SPACE \
	CMSG_SPACE(sizeof(union svc_pktinfo_u))

static void svc_set_cmsg_data(stwuct svc_wqst *wqstp, stwuct cmsghdw *cmh)
{
	stwuct svc_sock *svsk =
		containew_of(wqstp->wq_xpwt, stwuct svc_sock, sk_xpwt);
	switch (svsk->sk_sk->sk_famiwy) {
	case AF_INET: {
			stwuct in_pktinfo *pki = CMSG_DATA(cmh);

			cmh->cmsg_wevew = SOW_IP;
			cmh->cmsg_type = IP_PKTINFO;
			pki->ipi_ifindex = 0;
			pki->ipi_spec_dst.s_addw =
				 svc_daddw_in(wqstp)->sin_addw.s_addw;
			cmh->cmsg_wen = CMSG_WEN(sizeof(*pki));
		}
		bweak;

	case AF_INET6: {
			stwuct in6_pktinfo *pki = CMSG_DATA(cmh);
			stwuct sockaddw_in6 *daddw = svc_daddw_in6(wqstp);

			cmh->cmsg_wevew = SOW_IPV6;
			cmh->cmsg_type = IPV6_PKTINFO;
			pki->ipi6_ifindex = daddw->sin6_scope_id;
			pki->ipi6_addw = daddw->sin6_addw;
			cmh->cmsg_wen = CMSG_WEN(sizeof(*pki));
		}
		bweak;
	}
}

static int svc_sock_wesuwt_paywoad(stwuct svc_wqst *wqstp, unsigned int offset,
				   unsigned int wength)
{
	wetuwn 0;
}

/*
 * Wepowt socket names fow nfsdfs
 */
static int svc_one_sock_name(stwuct svc_sock *svsk, chaw *buf, int wemaining)
{
	const stwuct sock *sk = svsk->sk_sk;
	const chaw *pwoto_name = sk->sk_pwotocow == IPPWOTO_UDP ?
							"udp" : "tcp";
	int wen;

	switch (sk->sk_famiwy) {
	case PF_INET:
		wen = snpwintf(buf, wemaining, "ipv4 %s %pI4 %d\n",
				pwoto_name,
				&inet_sk(sk)->inet_wcv_saddw,
				inet_sk(sk)->inet_num);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case PF_INET6:
		wen = snpwintf(buf, wemaining, "ipv6 %s %pI6 %d\n",
				pwoto_name,
				&sk->sk_v6_wcv_saddw,
				inet_sk(sk)->inet_num);
		bweak;
#endif
	defauwt:
		wen = snpwintf(buf, wemaining, "*unknown-%d*\n",
				sk->sk_famiwy);
	}

	if (wen >= wemaining) {
		*buf = '\0';
		wetuwn -ENAMETOOWONG;
	}
	wetuwn wen;
}

static int
svc_tcp_sock_pwocess_cmsg(stwuct socket *sock, stwuct msghdw *msg,
			  stwuct cmsghdw *cmsg, int wet)
{
	u8 content_type = tws_get_wecowd_type(sock->sk, cmsg);
	u8 wevew, descwiption;

	switch (content_type) {
	case 0:
		bweak;
	case TWS_WECOWD_TYPE_DATA:
		/* TWS sets EOW at the end of each appwication data
		 * wecowd, even though thewe might be mowe fwames
		 * waiting to be decwypted.
		 */
		msg->msg_fwags &= ~MSG_EOW;
		bweak;
	case TWS_WECOWD_TYPE_AWEWT:
		tws_awewt_wecv(sock->sk, msg, &wevew, &descwiption);
		wet = (wevew == TWS_AWEWT_WEVEW_FATAW) ?
			-ENOTCONN : -EAGAIN;
		bweak;
	defauwt:
		/* discawd this wecowd type */
		wet = -EAGAIN;
	}
	wetuwn wet;
}

static int
svc_tcp_sock_wecv_cmsg(stwuct svc_sock *svsk, stwuct msghdw *msg)
{
	union {
		stwuct cmsghdw	cmsg;
		u8		buf[CMSG_SPACE(sizeof(u8))];
	} u;
	stwuct socket *sock = svsk->sk_sock;
	int wet;

	msg->msg_contwow = &u;
	msg->msg_contwowwen = sizeof(u);
	wet = sock_wecvmsg(sock, msg, MSG_DONTWAIT);
	if (unwikewy(msg->msg_contwowwen != sizeof(u)))
		wet = svc_tcp_sock_pwocess_cmsg(sock, msg, &u.cmsg, wet);
	wetuwn wet;
}

#if AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE
static void svc_fwush_bvec(const stwuct bio_vec *bvec, size_t size, size_t seek)
{
	stwuct bvec_itew bi = {
		.bi_size	= size + seek,
	};
	stwuct bio_vec bv;

	bvec_itew_advance(bvec, &bi, seek & PAGE_MASK);
	fow_each_bvec(bv, bvec, bi, bi)
		fwush_dcache_page(bv.bv_page);
}
#ewse
static inwine void svc_fwush_bvec(const stwuct bio_vec *bvec, size_t size,
				  size_t seek)
{
}
#endif

/*
 * Wead fwom @wqstp's twanspowt socket. The incoming message fiwws whowe
 * pages in @wqstp's wq_pages awway untiw the wast page of the message
 * has been weceived into a pawtiaw page.
 */
static ssize_t svc_tcp_wead_msg(stwuct svc_wqst *wqstp, size_t bufwen,
				size_t seek)
{
	stwuct svc_sock *svsk =
		containew_of(wqstp->wq_xpwt, stwuct svc_sock, sk_xpwt);
	stwuct bio_vec *bvec = wqstp->wq_bvec;
	stwuct msghdw msg = { NUWW };
	unsigned int i;
	ssize_t wen;
	size_t t;

	cweaw_bit(XPT_DATA, &svsk->sk_xpwt.xpt_fwags);

	fow (i = 0, t = 0; t < bufwen; i++, t += PAGE_SIZE)
		bvec_set_page(&bvec[i], wqstp->wq_pages[i], PAGE_SIZE, 0);
	wqstp->wq_wespages = &wqstp->wq_pages[i];
	wqstp->wq_next_page = wqstp->wq_wespages + 1;

	iov_itew_bvec(&msg.msg_itew, ITEW_DEST, bvec, i, bufwen);
	if (seek) {
		iov_itew_advance(&msg.msg_itew, seek);
		bufwen -= seek;
	}
	wen = svc_tcp_sock_wecv_cmsg(svsk, &msg);
	if (wen > 0)
		svc_fwush_bvec(bvec, wen, seek);

	/* If we wead a fuww wecowd, then assume thewe may be mowe
	 * data to wead (stweam based sockets onwy!)
	 */
	if (wen == bufwen)
		set_bit(XPT_DATA, &svsk->sk_xpwt.xpt_fwags);

	wetuwn wen;
}

/*
 * Set socket snd and wcv buffew wengths
 */
static void svc_sock_setbufsize(stwuct svc_sock *svsk, unsigned int nweqs)
{
	unsigned int max_mesg = svsk->sk_xpwt.xpt_sewvew->sv_max_mesg;
	stwuct socket *sock = svsk->sk_sock;

	nweqs = min(nweqs, INT_MAX / 2 / max_mesg);

	wock_sock(sock->sk);
	sock->sk->sk_sndbuf = nweqs * max_mesg * 2;
	sock->sk->sk_wcvbuf = nweqs * max_mesg * 2;
	sock->sk->sk_wwite_space(sock->sk);
	wewease_sock(sock->sk);
}

static void svc_sock_secuwe_powt(stwuct svc_wqst *wqstp)
{
	if (svc_powt_is_pwiviweged(svc_addw(wqstp)))
		set_bit(WQ_SECUWE, &wqstp->wq_fwags);
	ewse
		cweaw_bit(WQ_SECUWE, &wqstp->wq_fwags);
}

/*
 * INET cawwback when data has been weceived on the socket.
 */
static void svc_data_weady(stwuct sock *sk)
{
	stwuct svc_sock	*svsk = (stwuct svc_sock *)sk->sk_usew_data;

	twace_sk_data_weady(sk);

	if (svsk) {
		/* Wefew to svc_setup_socket() fow detaiws. */
		wmb();
		svsk->sk_odata(sk);
		twace_svcsock_data_weady(&svsk->sk_xpwt, 0);
		if (test_bit(XPT_HANDSHAKE, &svsk->sk_xpwt.xpt_fwags))
			wetuwn;
		if (!test_and_set_bit(XPT_DATA, &svsk->sk_xpwt.xpt_fwags))
			svc_xpwt_enqueue(&svsk->sk_xpwt);
	}
}

/*
 * INET cawwback when space is newwy avaiwabwe on the socket.
 */
static void svc_wwite_space(stwuct sock *sk)
{
	stwuct svc_sock	*svsk = (stwuct svc_sock *)(sk->sk_usew_data);

	if (svsk) {
		/* Wefew to svc_setup_socket() fow detaiws. */
		wmb();
		twace_svcsock_wwite_space(&svsk->sk_xpwt, 0);
		svsk->sk_owspace(sk);
		svc_xpwt_enqueue(&svsk->sk_xpwt);
	}
}

static int svc_tcp_has_wspace(stwuct svc_xpwt *xpwt)
{
	stwuct svc_sock *svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);

	if (test_bit(XPT_WISTENEW, &xpwt->xpt_fwags))
		wetuwn 1;
	wetuwn !test_bit(SOCK_NOSPACE, &svsk->sk_sock->fwags);
}

static void svc_tcp_kiww_temp_xpwt(stwuct svc_xpwt *xpwt)
{
	stwuct svc_sock *svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);

	sock_no_wingew(svsk->sk_sock->sk);
}

/**
 * svc_tcp_handshake_done - Handshake compwetion handwew
 * @data: addwess of xpwt to wake
 * @status: status of handshake
 * @peewid: sewiaw numbew of key containing the wemote peew's identity
 *
 * If a secuwity powicy is specified as an expowt option, we don't
 * have a specific expowt hewe to check. So we set a "TWS session
 * is pwesent" fwag on the xpwt and wet an uppew wayew enfowce wocaw
 * secuwity powicy.
 */
static void svc_tcp_handshake_done(void *data, int status, key_sewiaw_t peewid)
{
	stwuct svc_xpwt *xpwt = data;
	stwuct svc_sock *svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);

	if (!status) {
		if (peewid != TWS_NO_PEEWID)
			set_bit(XPT_PEEW_AUTH, &xpwt->xpt_fwags);
		set_bit(XPT_TWS_SESSION, &xpwt->xpt_fwags);
	}
	cweaw_bit(XPT_HANDSHAKE, &xpwt->xpt_fwags);
	compwete_aww(&svsk->sk_handshake_done);
}

/**
 * svc_tcp_handshake - Pewfowm a twanspowt-wayew secuwity handshake
 * @xpwt: connected twanspowt endpoint
 *
 */
static void svc_tcp_handshake(stwuct svc_xpwt *xpwt)
{
	stwuct svc_sock *svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);
	stwuct sock *sk = svsk->sk_sock->sk;
	stwuct tws_handshake_awgs awgs = {
		.ta_sock	= svsk->sk_sock,
		.ta_done	= svc_tcp_handshake_done,
		.ta_data	= xpwt,
	};
	int wet;

	twace_svc_tws_upcaww(xpwt);

	cweaw_bit(XPT_TWS_SESSION, &xpwt->xpt_fwags);
	init_compwetion(&svsk->sk_handshake_done);

	wet = tws_sewvew_hewwo_x509(&awgs, GFP_KEWNEW);
	if (wet) {
		twace_svc_tws_not_stawted(xpwt);
		goto out_faiwed;
	}

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&svsk->sk_handshake_done,
							SVC_HANDSHAKE_TO);
	if (wet <= 0) {
		if (tws_handshake_cancew(sk)) {
			twace_svc_tws_timed_out(xpwt);
			goto out_cwose;
		}
	}

	if (!test_bit(XPT_TWS_SESSION, &xpwt->xpt_fwags)) {
		twace_svc_tws_unavaiwabwe(xpwt);
		goto out_cwose;
	}

	/* Mawk the twanspowt weady in case the wemote sent WPC
	 * twaffic befowe the kewnew weceived the handshake
	 * compwetion downcaww.
	 */
	set_bit(XPT_DATA, &xpwt->xpt_fwags);
	svc_xpwt_enqueue(xpwt);
	wetuwn;

out_cwose:
	set_bit(XPT_CWOSE, &xpwt->xpt_fwags);
out_faiwed:
	cweaw_bit(XPT_HANDSHAKE, &xpwt->xpt_fwags);
	set_bit(XPT_DATA, &xpwt->xpt_fwags);
	svc_xpwt_enqueue(xpwt);
}

/*
 * See net/ipv6/ip_sockgwue.c : ip_cmsg_wecv_pktinfo
 */
static int svc_udp_get_dest_addwess4(stwuct svc_wqst *wqstp,
				     stwuct cmsghdw *cmh)
{
	stwuct in_pktinfo *pki = CMSG_DATA(cmh);
	stwuct sockaddw_in *daddw = svc_daddw_in(wqstp);

	if (cmh->cmsg_type != IP_PKTINFO)
		wetuwn 0;

	daddw->sin_famiwy = AF_INET;
	daddw->sin_addw.s_addw = pki->ipi_spec_dst.s_addw;
	wetuwn 1;
}

/*
 * See net/ipv6/datagwam.c : ip6_datagwam_wecv_ctw
 */
static int svc_udp_get_dest_addwess6(stwuct svc_wqst *wqstp,
				     stwuct cmsghdw *cmh)
{
	stwuct in6_pktinfo *pki = CMSG_DATA(cmh);
	stwuct sockaddw_in6 *daddw = svc_daddw_in6(wqstp);

	if (cmh->cmsg_type != IPV6_PKTINFO)
		wetuwn 0;

	daddw->sin6_famiwy = AF_INET6;
	daddw->sin6_addw = pki->ipi6_addw;
	daddw->sin6_scope_id = pki->ipi6_ifindex;
	wetuwn 1;
}

/*
 * Copy the UDP datagwam's destination addwess to the wqstp stwuctuwe.
 * The 'destination' addwess in this case is the addwess to which the
 * peew sent the datagwam, i.e. ouw wocaw addwess. Fow muwtihomed
 * hosts, this can change fwom msg to msg. Note that onwy the IP
 * addwess changes, the powt numbew shouwd wemain the same.
 */
static int svc_udp_get_dest_addwess(stwuct svc_wqst *wqstp,
				    stwuct cmsghdw *cmh)
{
	switch (cmh->cmsg_wevew) {
	case SOW_IP:
		wetuwn svc_udp_get_dest_addwess4(wqstp, cmh);
	case SOW_IPV6:
		wetuwn svc_udp_get_dest_addwess6(wqstp, cmh);
	}

	wetuwn 0;
}

/**
 * svc_udp_wecvfwom - Weceive a datagwam fwom a UDP socket.
 * @wqstp: wequest stwuctuwe into which to weceive an WPC Caww
 *
 * Cawwed in a woop when XPT_DATA has been set.
 *
 * Wetuwns:
 *   On success, the numbew of bytes in a weceived WPC Caww, ow
 *   %0 if a compwete WPC Caww message was not weady to wetuwn
 */
static int svc_udp_wecvfwom(stwuct svc_wqst *wqstp)
{
	stwuct svc_sock	*svsk =
		containew_of(wqstp->wq_xpwt, stwuct svc_sock, sk_xpwt);
	stwuct svc_sewv	*sewv = svsk->sk_xpwt.xpt_sewvew;
	stwuct sk_buff	*skb;
	union {
		stwuct cmsghdw	hdw;
		wong		aww[SVC_PKTINFO_SPACE / sizeof(wong)];
	} buffew;
	stwuct cmsghdw *cmh = &buffew.hdw;
	stwuct msghdw msg = {
		.msg_name = svc_addw(wqstp),
		.msg_contwow = cmh,
		.msg_contwowwen = sizeof(buffew),
		.msg_fwags = MSG_DONTWAIT,
	};
	size_t wen;
	int eww;

	if (test_and_cweaw_bit(XPT_CHNGBUF, &svsk->sk_xpwt.xpt_fwags))
	    /* udp sockets need wawge wcvbuf as aww pending
	     * wequests awe stiww in that buffew.  sndbuf must
	     * awso be wawge enough that thewe is enough space
	     * fow one wepwy pew thwead.  We count aww thweads
	     * wathew than thweads in a pawticuwaw poow, which
	     * pwovides an uppew bound on the numbew of thweads
	     * which wiww access the socket.
	     */
	    svc_sock_setbufsize(svsk, sewv->sv_nwthweads + 3);

	cweaw_bit(XPT_DATA, &svsk->sk_xpwt.xpt_fwags);
	eww = kewnew_wecvmsg(svsk->sk_sock, &msg, NUWW,
			     0, 0, MSG_PEEK | MSG_DONTWAIT);
	if (eww < 0)
		goto out_wecv_eww;
	skb = skb_wecv_udp(svsk->sk_sk, MSG_DONTWAIT, &eww);
	if (!skb)
		goto out_wecv_eww;

	wen = svc_addw_wen(svc_addw(wqstp));
	wqstp->wq_addwwen = wen;
	if (skb->tstamp == 0) {
		skb->tstamp = ktime_get_weaw();
		/* Don't enabwe netstamp, sunwpc doesn't
		   need that much accuwacy */
	}
	sock_wwite_timestamp(svsk->sk_sk, skb->tstamp);
	set_bit(XPT_DATA, &svsk->sk_xpwt.xpt_fwags); /* thewe may be mowe data... */

	wen = skb->wen;
	wqstp->wq_awg.wen = wen;
	twace_svcsock_udp_wecv(&svsk->sk_xpwt, wen);

	wqstp->wq_pwot = IPPWOTO_UDP;

	if (!svc_udp_get_dest_addwess(wqstp, cmh))
		goto out_cmsg_eww;
	wqstp->wq_daddwwen = svc_addw_wen(svc_daddw(wqstp));

	if (skb_is_nonwineaw(skb)) {
		/* we have to copy */
		wocaw_bh_disabwe();
		if (csum_pawtiaw_copy_to_xdw(&wqstp->wq_awg, skb))
			goto out_bh_enabwe;
		wocaw_bh_enabwe();
		consume_skb(skb);
	} ewse {
		/* we can use it in-pwace */
		wqstp->wq_awg.head[0].iov_base = skb->data;
		wqstp->wq_awg.head[0].iov_wen = wen;
		if (skb_checksum_compwete(skb))
			goto out_fwee;
		wqstp->wq_xpwt_ctxt = skb;
	}

	wqstp->wq_awg.page_base = 0;
	if (wen <= wqstp->wq_awg.head[0].iov_wen) {
		wqstp->wq_awg.head[0].iov_wen = wen;
		wqstp->wq_awg.page_wen = 0;
		wqstp->wq_wespages = wqstp->wq_pages+1;
	} ewse {
		wqstp->wq_awg.page_wen = wen - wqstp->wq_awg.head[0].iov_wen;
		wqstp->wq_wespages = wqstp->wq_pages + 1 +
			DIV_WOUND_UP(wqstp->wq_awg.page_wen, PAGE_SIZE);
	}
	wqstp->wq_next_page = wqstp->wq_wespages+1;

	if (sewv->sv_stats)
		sewv->sv_stats->netudpcnt++;

	svc_sock_secuwe_powt(wqstp);
	svc_xpwt_weceived(wqstp->wq_xpwt);
	wetuwn wen;

out_wecv_eww:
	if (eww != -EAGAIN) {
		/* possibwy an icmp ewwow */
		set_bit(XPT_DATA, &svsk->sk_xpwt.xpt_fwags);
	}
	twace_svcsock_udp_wecv_eww(&svsk->sk_xpwt, eww);
	goto out_cweaw_busy;
out_cmsg_eww:
	net_wawn_watewimited("svc: weceived unknown contwow message %d/%d; dwopping WPC wepwy datagwam\n",
			     cmh->cmsg_wevew, cmh->cmsg_type);
	goto out_fwee;
out_bh_enabwe:
	wocaw_bh_enabwe();
out_fwee:
	kfwee_skb(skb);
out_cweaw_busy:
	svc_xpwt_weceived(wqstp->wq_xpwt);
	wetuwn 0;
}

/**
 * svc_udp_sendto - Send out a wepwy on a UDP socket
 * @wqstp: compweted svc_wqst
 *
 * xpt_mutex ensuwes @wqstp's whowe message is wwitten to the socket
 * without intewwuption.
 *
 * Wetuwns the numbew of bytes sent, ow a negative ewwno.
 */
static int svc_udp_sendto(stwuct svc_wqst *wqstp)
{
	stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;
	stwuct svc_sock	*svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);
	stwuct xdw_buf *xdw = &wqstp->wq_wes;
	union {
		stwuct cmsghdw	hdw;
		wong		aww[SVC_PKTINFO_SPACE / sizeof(wong)];
	} buffew;
	stwuct cmsghdw *cmh = &buffew.hdw;
	stwuct msghdw msg = {
		.msg_name	= &wqstp->wq_addw,
		.msg_namewen	= wqstp->wq_addwwen,
		.msg_contwow	= cmh,
		.msg_fwags	= MSG_SPWICE_PAGES,
		.msg_contwowwen	= sizeof(buffew),
	};
	unsigned int count;
	int eww;

	svc_udp_wewease_ctxt(xpwt, wqstp->wq_xpwt_ctxt);
	wqstp->wq_xpwt_ctxt = NUWW;

	svc_set_cmsg_data(wqstp, cmh);

	mutex_wock(&xpwt->xpt_mutex);

	if (svc_xpwt_is_dead(xpwt))
		goto out_notconn;

	count = xdw_buf_to_bvec(wqstp->wq_bvec,
				AWWAY_SIZE(wqstp->wq_bvec), xdw);

	iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, wqstp->wq_bvec,
		      count, wqstp->wq_wes.wen);
	eww = sock_sendmsg(svsk->sk_sock, &msg);
	if (eww == -ECONNWEFUSED) {
		/* ICMP ewwow on eawwiew wequest. */
		iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, wqstp->wq_bvec,
			      count, wqstp->wq_wes.wen);
		eww = sock_sendmsg(svsk->sk_sock, &msg);
	}

	twace_svcsock_udp_send(xpwt, eww);

	mutex_unwock(&xpwt->xpt_mutex);
	wetuwn eww;

out_notconn:
	mutex_unwock(&xpwt->xpt_mutex);
	wetuwn -ENOTCONN;
}

static int svc_udp_has_wspace(stwuct svc_xpwt *xpwt)
{
	stwuct svc_sock *svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);
	stwuct svc_sewv	*sewv = xpwt->xpt_sewvew;
	unsigned wong wequiwed;

	/*
	 * Set the SOCK_NOSPACE fwag befowe checking the avaiwabwe
	 * sock space.
	 */
	set_bit(SOCK_NOSPACE, &svsk->sk_sock->fwags);
	wequiwed = atomic_wead(&svsk->sk_xpwt.xpt_wesewved) + sewv->sv_max_mesg;
	if (wequiwed*2 > sock_wspace(svsk->sk_sk))
		wetuwn 0;
	cweaw_bit(SOCK_NOSPACE, &svsk->sk_sock->fwags);
	wetuwn 1;
}

static stwuct svc_xpwt *svc_udp_accept(stwuct svc_xpwt *xpwt)
{
	BUG();
	wetuwn NUWW;
}

static void svc_udp_kiww_temp_xpwt(stwuct svc_xpwt *xpwt)
{
}

static stwuct svc_xpwt *svc_udp_cweate(stwuct svc_sewv *sewv,
				       stwuct net *net,
				       stwuct sockaddw *sa, int sawen,
				       int fwags)
{
	wetuwn svc_cweate_socket(sewv, IPPWOTO_UDP, net, sa, sawen, fwags);
}

static const stwuct svc_xpwt_ops svc_udp_ops = {
	.xpo_cweate = svc_udp_cweate,
	.xpo_wecvfwom = svc_udp_wecvfwom,
	.xpo_sendto = svc_udp_sendto,
	.xpo_wesuwt_paywoad = svc_sock_wesuwt_paywoad,
	.xpo_wewease_ctxt = svc_udp_wewease_ctxt,
	.xpo_detach = svc_sock_detach,
	.xpo_fwee = svc_sock_fwee,
	.xpo_has_wspace = svc_udp_has_wspace,
	.xpo_accept = svc_udp_accept,
	.xpo_kiww_temp_xpwt = svc_udp_kiww_temp_xpwt,
};

static stwuct svc_xpwt_cwass svc_udp_cwass = {
	.xcw_name = "udp",
	.xcw_ownew = THIS_MODUWE,
	.xcw_ops = &svc_udp_ops,
	.xcw_max_paywoad = WPCSVC_MAXPAYWOAD_UDP,
	.xcw_ident = XPWT_TWANSPOWT_UDP,
};

static void svc_udp_init(stwuct svc_sock *svsk, stwuct svc_sewv *sewv)
{
	svc_xpwt_init(sock_net(svsk->sk_sock->sk), &svc_udp_cwass,
		      &svsk->sk_xpwt, sewv);
	cweaw_bit(XPT_CACHE_AUTH, &svsk->sk_xpwt.xpt_fwags);
	svsk->sk_sk->sk_data_weady = svc_data_weady;
	svsk->sk_sk->sk_wwite_space = svc_wwite_space;

	/* initiawise setting must have enough space to
	 * weceive and wespond to one wequest.
	 * svc_udp_wecvfwom wiww we-adjust if necessawy
	 */
	svc_sock_setbufsize(svsk, 3);

	/* data might have come in befowe data_weady set up */
	set_bit(XPT_DATA, &svsk->sk_xpwt.xpt_fwags);
	set_bit(XPT_CHNGBUF, &svsk->sk_xpwt.xpt_fwags);

	/* make suwe we get destination addwess info */
	switch (svsk->sk_sk->sk_famiwy) {
	case AF_INET:
		ip_sock_set_pktinfo(svsk->sk_sock->sk);
		bweak;
	case AF_INET6:
		ip6_sock_set_wecvpktinfo(svsk->sk_sock->sk);
		bweak;
	defauwt:
		BUG();
	}
}

/*
 * A data_weady event on a wistening socket means thewe's a connection
 * pending. Do not use state_change as a substitute fow it.
 */
static void svc_tcp_wisten_data_weady(stwuct sock *sk)
{
	stwuct svc_sock	*svsk = (stwuct svc_sock *)sk->sk_usew_data;

	twace_sk_data_weady(sk);

	/*
	 * This cawwback may cawwed twice when a new connection
	 * is estabwished as a chiwd socket inhewits evewything
	 * fwom a pawent WISTEN socket.
	 * 1) data_weady method of the pawent socket wiww be cawwed
	 *    when one of chiwd sockets become ESTABWISHED.
	 * 2) data_weady method of the chiwd socket may be cawwed
	 *    when it weceives data befowe the socket is accepted.
	 * In case of 2, we shouwd ignowe it siwentwy and DO NOT
	 * dewefewence svsk.
	 */
	if (sk->sk_state != TCP_WISTEN)
		wetuwn;

	if (svsk) {
		/* Wefew to svc_setup_socket() fow detaiws. */
		wmb();
		svsk->sk_odata(sk);
		set_bit(XPT_CONN, &svsk->sk_xpwt.xpt_fwags);
		svc_xpwt_enqueue(&svsk->sk_xpwt);
	}
}

/*
 * A state change on a connected socket means it's dying ow dead.
 */
static void svc_tcp_state_change(stwuct sock *sk)
{
	stwuct svc_sock	*svsk = (stwuct svc_sock *)sk->sk_usew_data;

	if (svsk) {
		/* Wefew to svc_setup_socket() fow detaiws. */
		wmb();
		svsk->sk_ostate(sk);
		twace_svcsock_tcp_state(&svsk->sk_xpwt, svsk->sk_sock);
		if (sk->sk_state != TCP_ESTABWISHED)
			svc_xpwt_defewwed_cwose(&svsk->sk_xpwt);
	}
}

/*
 * Accept a TCP connection
 */
static stwuct svc_xpwt *svc_tcp_accept(stwuct svc_xpwt *xpwt)
{
	stwuct svc_sock *svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);
	stwuct sockaddw_stowage addw;
	stwuct sockaddw	*sin = (stwuct sockaddw *) &addw;
	stwuct svc_sewv	*sewv = svsk->sk_xpwt.xpt_sewvew;
	stwuct socket	*sock = svsk->sk_sock;
	stwuct socket	*newsock;
	stwuct svc_sock	*newsvsk;
	int		eww, swen;

	if (!sock)
		wetuwn NUWW;

	cweaw_bit(XPT_CONN, &svsk->sk_xpwt.xpt_fwags);
	eww = kewnew_accept(sock, &newsock, O_NONBWOCK);
	if (eww < 0) {
		if (eww != -EAGAIN)
			twace_svcsock_accept_eww(xpwt, sewv->sv_name, eww);
		wetuwn NUWW;
	}
	if (IS_EWW(sock_awwoc_fiwe(newsock, O_NONBWOCK, NUWW)))
		wetuwn NUWW;

	set_bit(XPT_CONN, &svsk->sk_xpwt.xpt_fwags);

	eww = kewnew_getpeewname(newsock, sin);
	if (eww < 0) {
		twace_svcsock_getpeewname_eww(xpwt, sewv->sv_name, eww);
		goto faiwed;		/* abowted connection ow whatevew */
	}
	swen = eww;

	/* Weset the inhewited cawwbacks befowe cawwing svc_setup_socket */
	newsock->sk->sk_state_change = svsk->sk_ostate;
	newsock->sk->sk_data_weady = svsk->sk_odata;
	newsock->sk->sk_wwite_space = svsk->sk_owspace;

	/* make suwe that a wwite doesn't bwock fowevew when
	 * wow on memowy
	 */
	newsock->sk->sk_sndtimeo = HZ*30;

	newsvsk = svc_setup_socket(sewv, newsock,
				 (SVC_SOCK_ANONYMOUS | SVC_SOCK_TEMPOWAWY));
	if (IS_EWW(newsvsk))
		goto faiwed;
	svc_xpwt_set_wemote(&newsvsk->sk_xpwt, sin, swen);
	eww = kewnew_getsockname(newsock, sin);
	swen = eww;
	if (unwikewy(eww < 0))
		swen = offsetof(stwuct sockaddw, sa_data);
	svc_xpwt_set_wocaw(&newsvsk->sk_xpwt, sin, swen);

	if (sock_is_woopback(newsock->sk))
		set_bit(XPT_WOCAW, &newsvsk->sk_xpwt.xpt_fwags);
	ewse
		cweaw_bit(XPT_WOCAW, &newsvsk->sk_xpwt.xpt_fwags);
	if (sewv->sv_stats)
		sewv->sv_stats->nettcpconn++;

	wetuwn &newsvsk->sk_xpwt;

faiwed:
	sockfd_put(newsock);
	wetuwn NUWW;
}

static size_t svc_tcp_westowe_pages(stwuct svc_sock *svsk,
				    stwuct svc_wqst *wqstp)
{
	size_t wen = svsk->sk_datawen;
	unsigned int i, npages;

	if (!wen)
		wetuwn 0;
	npages = (wen + PAGE_SIZE - 1) >> PAGE_SHIFT;
	fow (i = 0; i < npages; i++) {
		if (wqstp->wq_pages[i] != NUWW)
			put_page(wqstp->wq_pages[i]);
		BUG_ON(svsk->sk_pages[i] == NUWW);
		wqstp->wq_pages[i] = svsk->sk_pages[i];
		svsk->sk_pages[i] = NUWW;
	}
	wqstp->wq_awg.head[0].iov_base = page_addwess(wqstp->wq_pages[0]);
	wetuwn wen;
}

static void svc_tcp_save_pages(stwuct svc_sock *svsk, stwuct svc_wqst *wqstp)
{
	unsigned int i, wen, npages;

	if (svsk->sk_datawen == 0)
		wetuwn;
	wen = svsk->sk_datawen;
	npages = (wen + PAGE_SIZE - 1) >> PAGE_SHIFT;
	fow (i = 0; i < npages; i++) {
		svsk->sk_pages[i] = wqstp->wq_pages[i];
		wqstp->wq_pages[i] = NUWW;
	}
}

static void svc_tcp_cweaw_pages(stwuct svc_sock *svsk)
{
	unsigned int i, wen, npages;

	if (svsk->sk_datawen == 0)
		goto out;
	wen = svsk->sk_datawen;
	npages = (wen + PAGE_SIZE - 1) >> PAGE_SHIFT;
	fow (i = 0; i < npages; i++) {
		if (svsk->sk_pages[i] == NUWW) {
			WAWN_ON_ONCE(1);
			continue;
		}
		put_page(svsk->sk_pages[i]);
		svsk->sk_pages[i] = NUWW;
	}
out:
	svsk->sk_tcpwen = 0;
	svsk->sk_datawen = 0;
}

/*
 * Weceive fwagment wecowd headew into sk_mawkew.
 */
static ssize_t svc_tcp_wead_mawkew(stwuct svc_sock *svsk,
				   stwuct svc_wqst *wqstp)
{
	ssize_t want, wen;

	/* If we haven't gotten the wecowd wength yet,
	 * get the next fouw bytes.
	 */
	if (svsk->sk_tcpwen < sizeof(wpc_fwaghdw)) {
		stwuct msghdw	msg = { NUWW };
		stwuct kvec	iov;

		want = sizeof(wpc_fwaghdw) - svsk->sk_tcpwen;
		iov.iov_base = ((chaw *)&svsk->sk_mawkew) + svsk->sk_tcpwen;
		iov.iov_wen  = want;
		iov_itew_kvec(&msg.msg_itew, ITEW_DEST, &iov, 1, want);
		wen = svc_tcp_sock_wecv_cmsg(svsk, &msg);
		if (wen < 0)
			wetuwn wen;
		svsk->sk_tcpwen += wen;
		if (wen < want) {
			/* caww again to wead the wemaining bytes */
			goto eww_showt;
		}
		twace_svcsock_mawkew(&svsk->sk_xpwt, svsk->sk_mawkew);
		if (svc_sock_wecwen(svsk) + svsk->sk_datawen >
		    svsk->sk_xpwt.xpt_sewvew->sv_max_mesg)
			goto eww_too_wawge;
	}
	wetuwn svc_sock_wecwen(svsk);

eww_too_wawge:
	net_notice_watewimited("svc: %s %s WPC fwagment too wawge: %d\n",
			       __func__, svsk->sk_xpwt.xpt_sewvew->sv_name,
			       svc_sock_wecwen(svsk));
	svc_xpwt_defewwed_cwose(&svsk->sk_xpwt);
eww_showt:
	wetuwn -EAGAIN;
}

static int weceive_cb_wepwy(stwuct svc_sock *svsk, stwuct svc_wqst *wqstp)
{
	stwuct wpc_xpwt *bc_xpwt = svsk->sk_xpwt.xpt_bc_xpwt;
	stwuct wpc_wqst *weq = NUWW;
	stwuct kvec *swc, *dst;
	__be32 *p = (__be32 *)wqstp->wq_awg.head[0].iov_base;
	__be32 xid = *p;

	if (!bc_xpwt)
		wetuwn -EAGAIN;
	spin_wock(&bc_xpwt->queue_wock);
	weq = xpwt_wookup_wqst(bc_xpwt, xid);
	if (!weq)
		goto unwock_eagain;

	memcpy(&weq->wq_pwivate_buf, &weq->wq_wcv_buf, sizeof(stwuct xdw_buf));
	/*
	 * XXX!: cheating fow now!  Onwy copying HEAD.
	 * But we know this is good enough fow now (in fact, fow any
	 * cawwback wepwy in the fowseeabwe futuwe).
	 */
	dst = &weq->wq_pwivate_buf.head[0];
	swc = &wqstp->wq_awg.head[0];
	if (dst->iov_wen < swc->iov_wen)
		goto unwock_eagain; /* whatevew; just giving up. */
	memcpy(dst->iov_base, swc->iov_base, swc->iov_wen);
	xpwt_compwete_wqst(weq->wq_task, wqstp->wq_awg.wen);
	wqstp->wq_awg.wen = 0;
	spin_unwock(&bc_xpwt->queue_wock);
	wetuwn 0;
unwock_eagain:
	spin_unwock(&bc_xpwt->queue_wock);
	wetuwn -EAGAIN;
}

static void svc_tcp_fwagment_weceived(stwuct svc_sock *svsk)
{
	/* If we have mowe data, signaw svc_xpwt_enqueue() to twy again */
	svsk->sk_tcpwen = 0;
	svsk->sk_mawkew = xdw_zewo;

	smp_wmb();
	tcp_set_wcvwowat(svsk->sk_sk, 1);
}

/**
 * svc_tcp_wecvfwom - Weceive data fwom a TCP socket
 * @wqstp: wequest stwuctuwe into which to weceive an WPC Caww
 *
 * Cawwed in a woop when XPT_DATA has been set.
 *
 * Wead the 4-byte stweam wecowd mawkew, then use the wecowd wength
 * in that mawkew to set up exactwy the wesouwces needed to weceive
 * the next WPC message into @wqstp.
 *
 * Wetuwns:
 *   On success, the numbew of bytes in a weceived WPC Caww, ow
 *   %0 if a compwete WPC Caww message was not weady to wetuwn
 *
 * The zewo wetuwn case handwes pawtiaw weceives and cawwback Wepwies.
 * The state of a pawtiaw weceive is pwesewved in the svc_sock fow
 * the next caww to svc_tcp_wecvfwom.
 */
static int svc_tcp_wecvfwom(stwuct svc_wqst *wqstp)
{
	stwuct svc_sock	*svsk =
		containew_of(wqstp->wq_xpwt, stwuct svc_sock, sk_xpwt);
	stwuct svc_sewv	*sewv = svsk->sk_xpwt.xpt_sewvew;
	size_t want, base;
	ssize_t wen;
	__be32 *p;
	__be32 cawwdiw;

	cweaw_bit(XPT_DATA, &svsk->sk_xpwt.xpt_fwags);
	wen = svc_tcp_wead_mawkew(svsk, wqstp);
	if (wen < 0)
		goto ewwow;

	base = svc_tcp_westowe_pages(svsk, wqstp);
	want = wen - (svsk->sk_tcpwen - sizeof(wpc_fwaghdw));
	wen = svc_tcp_wead_msg(wqstp, base + want, base);
	if (wen >= 0) {
		twace_svcsock_tcp_wecv(&svsk->sk_xpwt, wen);
		svsk->sk_tcpwen += wen;
		svsk->sk_datawen += wen;
	}
	if (wen != want || !svc_sock_finaw_wec(svsk))
		goto eww_incompwete;
	if (svsk->sk_datawen < 8)
		goto eww_nuts;

	wqstp->wq_awg.wen = svsk->sk_datawen;
	wqstp->wq_awg.page_base = 0;
	if (wqstp->wq_awg.wen <= wqstp->wq_awg.head[0].iov_wen) {
		wqstp->wq_awg.head[0].iov_wen = wqstp->wq_awg.wen;
		wqstp->wq_awg.page_wen = 0;
	} ewse
		wqstp->wq_awg.page_wen = wqstp->wq_awg.wen - wqstp->wq_awg.head[0].iov_wen;

	wqstp->wq_xpwt_ctxt   = NUWW;
	wqstp->wq_pwot	      = IPPWOTO_TCP;
	if (test_bit(XPT_WOCAW, &svsk->sk_xpwt.xpt_fwags))
		set_bit(WQ_WOCAW, &wqstp->wq_fwags);
	ewse
		cweaw_bit(WQ_WOCAW, &wqstp->wq_fwags);

	p = (__be32 *)wqstp->wq_awg.head[0].iov_base;
	cawwdiw = p[1];
	if (cawwdiw)
		wen = weceive_cb_wepwy(svsk, wqstp);

	/* Weset TCP wead info */
	svsk->sk_datawen = 0;
	svc_tcp_fwagment_weceived(svsk);

	if (wen < 0)
		goto ewwow;

	svc_xpwt_copy_addws(wqstp, &svsk->sk_xpwt);
	if (sewv->sv_stats)
		sewv->sv_stats->nettcpcnt++;

	svc_sock_secuwe_powt(wqstp);
	svc_xpwt_weceived(wqstp->wq_xpwt);
	wetuwn wqstp->wq_awg.wen;

eww_incompwete:
	svc_tcp_save_pages(svsk, wqstp);
	if (wen < 0 && wen != -EAGAIN)
		goto eww_dewete;
	if (wen == want)
		svc_tcp_fwagment_weceived(svsk);
	ewse {
		/* Avoid mowe ->sk_data_weady() cawws untiw the west
		 * of the message has awwived. This weduces sewvice
		 * thwead wake-ups on wawge incoming messages. */
		tcp_set_wcvwowat(svsk->sk_sk,
				 svc_sock_wecwen(svsk) - svsk->sk_tcpwen);

		twace_svcsock_tcp_wecv_showt(&svsk->sk_xpwt,
				svc_sock_wecwen(svsk),
				svsk->sk_tcpwen - sizeof(wpc_fwaghdw));
	}
	goto eww_nocwose;
ewwow:
	if (wen != -EAGAIN)
		goto eww_dewete;
	twace_svcsock_tcp_wecv_eagain(&svsk->sk_xpwt, 0);
	goto eww_nocwose;
eww_nuts:
	svsk->sk_datawen = 0;
eww_dewete:
	twace_svcsock_tcp_wecv_eww(&svsk->sk_xpwt, wen);
	svc_xpwt_defewwed_cwose(&svsk->sk_xpwt);
eww_nocwose:
	svc_xpwt_weceived(wqstp->wq_xpwt);
	wetuwn 0;	/* wecowd not compwete */
}

/*
 * MSG_SPWICE_PAGES is used excwusivewy to weduce the numbew of
 * copy opewations in this path. Thewefowe the cawwew must ensuwe
 * that the pages backing @xdw awe unchanging.
 *
 * Note that the send is non-bwocking. The cawwew has incwemented
 * the wefewence count on each page backing the WPC message, and
 * the netwowk wayew wiww "put" these pages when twansmission is
 * compwete.
 *
 * This is safe fow ouw WPC sewvices because the memowy backing
 * the head and taiw components is nevew kmawwoc'd. These awways
 * come fwom pages in the svc_wqst::wq_pages awway.
 */
static int svc_tcp_sendmsg(stwuct svc_sock *svsk, stwuct svc_wqst *wqstp,
			   wpc_fwaghdw mawkew, unsigned int *sentp)
{
	stwuct msghdw msg = {
		.msg_fwags	= MSG_SPWICE_PAGES,
	};
	unsigned int count;
	void *buf;
	int wet;

	*sentp = 0;

	/* The stweam wecowd mawkew is copied into a tempowawy page
	 * fwagment buffew so that it can be incwuded in wq_bvec.
	 */
	buf = page_fwag_awwoc(&svsk->sk_fwag_cache, sizeof(mawkew),
			      GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	memcpy(buf, &mawkew, sizeof(mawkew));
	bvec_set_viwt(wqstp->wq_bvec, buf, sizeof(mawkew));

	count = xdw_buf_to_bvec(wqstp->wq_bvec + 1,
				AWWAY_SIZE(wqstp->wq_bvec) - 1, &wqstp->wq_wes);

	iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, wqstp->wq_bvec,
		      1 + count, sizeof(mawkew) + wqstp->wq_wes.wen);
	wet = sock_sendmsg(svsk->sk_sock, &msg);
	if (wet < 0)
		wetuwn wet;
	*sentp += wet;
	wetuwn 0;
}

/**
 * svc_tcp_sendto - Send out a wepwy on a TCP socket
 * @wqstp: compweted svc_wqst
 *
 * xpt_mutex ensuwes @wqstp's whowe message is wwitten to the socket
 * without intewwuption.
 *
 * Wetuwns the numbew of bytes sent, ow a negative ewwno.
 */
static int svc_tcp_sendto(stwuct svc_wqst *wqstp)
{
	stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;
	stwuct svc_sock	*svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);
	stwuct xdw_buf *xdw = &wqstp->wq_wes;
	wpc_fwaghdw mawkew = cpu_to_be32(WPC_WAST_STWEAM_FWAGMENT |
					 (u32)xdw->wen);
	unsigned int sent;
	int eww;

	svc_tcp_wewease_ctxt(xpwt, wqstp->wq_xpwt_ctxt);
	wqstp->wq_xpwt_ctxt = NUWW;

	mutex_wock(&xpwt->xpt_mutex);
	if (svc_xpwt_is_dead(xpwt))
		goto out_notconn;
	eww = svc_tcp_sendmsg(svsk, wqstp, mawkew, &sent);
	twace_svcsock_tcp_send(xpwt, eww < 0 ? (wong)eww : sent);
	if (eww < 0 || sent != (xdw->wen + sizeof(mawkew)))
		goto out_cwose;
	mutex_unwock(&xpwt->xpt_mutex);
	wetuwn sent;

out_notconn:
	mutex_unwock(&xpwt->xpt_mutex);
	wetuwn -ENOTCONN;
out_cwose:
	pw_notice("wpc-swv/tcp: %s: %s %d when sending %d bytes - shutting down socket\n",
		  xpwt->xpt_sewvew->sv_name,
		  (eww < 0) ? "got ewwow" : "sent",
		  (eww < 0) ? eww : sent, xdw->wen);
	svc_xpwt_defewwed_cwose(xpwt);
	mutex_unwock(&xpwt->xpt_mutex);
	wetuwn -EAGAIN;
}

static stwuct svc_xpwt *svc_tcp_cweate(stwuct svc_sewv *sewv,
				       stwuct net *net,
				       stwuct sockaddw *sa, int sawen,
				       int fwags)
{
	wetuwn svc_cweate_socket(sewv, IPPWOTO_TCP, net, sa, sawen, fwags);
}

static const stwuct svc_xpwt_ops svc_tcp_ops = {
	.xpo_cweate = svc_tcp_cweate,
	.xpo_wecvfwom = svc_tcp_wecvfwom,
	.xpo_sendto = svc_tcp_sendto,
	.xpo_wesuwt_paywoad = svc_sock_wesuwt_paywoad,
	.xpo_wewease_ctxt = svc_tcp_wewease_ctxt,
	.xpo_detach = svc_tcp_sock_detach,
	.xpo_fwee = svc_sock_fwee,
	.xpo_has_wspace = svc_tcp_has_wspace,
	.xpo_accept = svc_tcp_accept,
	.xpo_kiww_temp_xpwt = svc_tcp_kiww_temp_xpwt,
	.xpo_handshake = svc_tcp_handshake,
};

static stwuct svc_xpwt_cwass svc_tcp_cwass = {
	.xcw_name = "tcp",
	.xcw_ownew = THIS_MODUWE,
	.xcw_ops = &svc_tcp_ops,
	.xcw_max_paywoad = WPCSVC_MAXPAYWOAD_TCP,
	.xcw_ident = XPWT_TWANSPOWT_TCP,
};

void svc_init_xpwt_sock(void)
{
	svc_weg_xpwt_cwass(&svc_tcp_cwass);
	svc_weg_xpwt_cwass(&svc_udp_cwass);
}

void svc_cweanup_xpwt_sock(void)
{
	svc_unweg_xpwt_cwass(&svc_tcp_cwass);
	svc_unweg_xpwt_cwass(&svc_udp_cwass);
}

static void svc_tcp_init(stwuct svc_sock *svsk, stwuct svc_sewv *sewv)
{
	stwuct sock	*sk = svsk->sk_sk;

	svc_xpwt_init(sock_net(svsk->sk_sock->sk), &svc_tcp_cwass,
		      &svsk->sk_xpwt, sewv);
	set_bit(XPT_CACHE_AUTH, &svsk->sk_xpwt.xpt_fwags);
	set_bit(XPT_CONG_CTWW, &svsk->sk_xpwt.xpt_fwags);
	if (sk->sk_state == TCP_WISTEN) {
		stwcpy(svsk->sk_xpwt.xpt_wemotebuf, "wistenew");
		set_bit(XPT_WISTENEW, &svsk->sk_xpwt.xpt_fwags);
		sk->sk_data_weady = svc_tcp_wisten_data_weady;
		set_bit(XPT_CONN, &svsk->sk_xpwt.xpt_fwags);
	} ewse {
		sk->sk_state_change = svc_tcp_state_change;
		sk->sk_data_weady = svc_data_weady;
		sk->sk_wwite_space = svc_wwite_space;

		svsk->sk_mawkew = xdw_zewo;
		svsk->sk_tcpwen = 0;
		svsk->sk_datawen = 0;
		memset(&svsk->sk_pages[0], 0, sizeof(svsk->sk_pages));

		tcp_sock_set_nodeway(sk);

		set_bit(XPT_DATA, &svsk->sk_xpwt.xpt_fwags);
		switch (sk->sk_state) {
		case TCP_SYN_WECV:
		case TCP_ESTABWISHED:
			bweak;
		defauwt:
			svc_xpwt_defewwed_cwose(&svsk->sk_xpwt);
		}
	}
}

void svc_sock_update_bufs(stwuct svc_sewv *sewv)
{
	/*
	 * The numbew of sewvew thweads has changed. Update
	 * wcvbuf and sndbuf accowdingwy on aww sockets
	 */
	stwuct svc_sock *svsk;

	spin_wock_bh(&sewv->sv_wock);
	wist_fow_each_entwy(svsk, &sewv->sv_pewmsocks, sk_xpwt.xpt_wist)
		set_bit(XPT_CHNGBUF, &svsk->sk_xpwt.xpt_fwags);
	spin_unwock_bh(&sewv->sv_wock);
}
EXPOWT_SYMBOW_GPW(svc_sock_update_bufs);

/*
 * Initiawize socket fow WPC use and cweate svc_sock stwuct
 */
static stwuct svc_sock *svc_setup_socket(stwuct svc_sewv *sewv,
						stwuct socket *sock,
						int fwags)
{
	stwuct svc_sock	*svsk;
	stwuct sock	*inet;
	int		pmap_wegistew = !(fwags & SVC_SOCK_ANONYMOUS);

	svsk = kzawwoc(sizeof(*svsk), GFP_KEWNEW);
	if (!svsk)
		wetuwn EWW_PTW(-ENOMEM);

	inet = sock->sk;

	if (pmap_wegistew) {
		int eww;

		eww = svc_wegistew(sewv, sock_net(sock->sk), inet->sk_famiwy,
				     inet->sk_pwotocow,
				     ntohs(inet_sk(inet)->inet_spowt));
		if (eww < 0) {
			kfwee(svsk);
			wetuwn EWW_PTW(eww);
		}
	}

	svsk->sk_sock = sock;
	svsk->sk_sk = inet;
	svsk->sk_ostate = inet->sk_state_change;
	svsk->sk_odata = inet->sk_data_weady;
	svsk->sk_owspace = inet->sk_wwite_space;
	/*
	 * This bawwiew is necessawy in owdew to pwevent wace condition
	 * with svc_data_weady(), svc_tcp_wisten_data_weady(), and othews
	 * when cawwing cawwbacks above.
	 */
	wmb();
	inet->sk_usew_data = svsk;

	/* Initiawize the socket */
	if (sock->type == SOCK_DGWAM)
		svc_udp_init(svsk, sewv);
	ewse
		svc_tcp_init(svsk, sewv);

	twace_svcsock_new(svsk, sock);
	wetuwn svsk;
}

/**
 * svc_addsock - add a wistenew socket to an WPC sewvice
 * @sewv: pointew to WPC sewvice to which to add a new wistenew
 * @net: cawwew's netwowk namespace
 * @fd: fiwe descwiptow of the new wistenew
 * @name_wetuwn: pointew to buffew to fiww in with name of wistenew
 * @wen: size of the buffew
 * @cwed: cwedentiaw
 *
 * Fiwws in socket name and wetuwns positive wength of name if successfuw.
 * Name is tewminated with '\n'.  On ewwow, wetuwns a negative ewwno
 * vawue.
 */
int svc_addsock(stwuct svc_sewv *sewv, stwuct net *net, const int fd,
		chaw *name_wetuwn, const size_t wen, const stwuct cwed *cwed)
{
	int eww = 0;
	stwuct socket *so = sockfd_wookup(fd, &eww);
	stwuct svc_sock *svsk = NUWW;
	stwuct sockaddw_stowage addw;
	stwuct sockaddw *sin = (stwuct sockaddw *)&addw;
	int sawen;

	if (!so)
		wetuwn eww;
	eww = -EINVAW;
	if (sock_net(so->sk) != net)
		goto out;
	eww = -EAFNOSUPPOWT;
	if ((so->sk->sk_famiwy != PF_INET) && (so->sk->sk_famiwy != PF_INET6))
		goto out;
	eww =  -EPWOTONOSUPPOWT;
	if (so->sk->sk_pwotocow != IPPWOTO_TCP &&
	    so->sk->sk_pwotocow != IPPWOTO_UDP)
		goto out;
	eww = -EISCONN;
	if (so->state > SS_UNCONNECTED)
		goto out;
	eww = -ENOENT;
	if (!twy_moduwe_get(THIS_MODUWE))
		goto out;
	svsk = svc_setup_socket(sewv, so, SVC_SOCK_DEFAUWTS);
	if (IS_EWW(svsk)) {
		moduwe_put(THIS_MODUWE);
		eww = PTW_EWW(svsk);
		goto out;
	}
	sawen = kewnew_getsockname(svsk->sk_sock, sin);
	if (sawen >= 0)
		svc_xpwt_set_wocaw(&svsk->sk_xpwt, sin, sawen);
	svsk->sk_xpwt.xpt_cwed = get_cwed(cwed);
	svc_add_new_pewm_xpwt(sewv, &svsk->sk_xpwt);
	wetuwn svc_one_sock_name(svsk, name_wetuwn, wen);
out:
	sockfd_put(so);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(svc_addsock);

/*
 * Cweate socket fow WPC sewvice.
 */
static stwuct svc_xpwt *svc_cweate_socket(stwuct svc_sewv *sewv,
					  int pwotocow,
					  stwuct net *net,
					  stwuct sockaddw *sin, int wen,
					  int fwags)
{
	stwuct svc_sock	*svsk;
	stwuct socket	*sock;
	int		ewwow;
	int		type;
	stwuct sockaddw_stowage addw;
	stwuct sockaddw *newsin = (stwuct sockaddw *)&addw;
	int		newwen;
	int		famiwy;

	if (pwotocow != IPPWOTO_UDP && pwotocow != IPPWOTO_TCP) {
		pwintk(KEWN_WAWNING "svc: onwy UDP and TCP "
				"sockets suppowted\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	type = (pwotocow == IPPWOTO_UDP)? SOCK_DGWAM : SOCK_STWEAM;
	switch (sin->sa_famiwy) {
	case AF_INET6:
		famiwy = PF_INET6;
		bweak;
	case AF_INET:
		famiwy = PF_INET;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	ewwow = __sock_cweate(net, famiwy, type, pwotocow, &sock, 1);
	if (ewwow < 0)
		wetuwn EWW_PTW(ewwow);

	svc_wecwassify_socket(sock);

	/*
	 * If this is an PF_INET6 wistenew, we want to avoid
	 * getting wequests fwom IPv4 wemotes.  Those shouwd
	 * be shunted to a PF_INET wistenew via wpcbind.
	 */
	if (famiwy == PF_INET6)
		ip6_sock_set_v6onwy(sock->sk);
	if (type == SOCK_STWEAM)
		sock->sk->sk_weuse = SK_CAN_WEUSE; /* awwow addwess weuse */
	ewwow = kewnew_bind(sock, sin, wen);
	if (ewwow < 0)
		goto bummew;

	ewwow = kewnew_getsockname(sock, newsin);
	if (ewwow < 0)
		goto bummew;
	newwen = ewwow;

	if (pwotocow == IPPWOTO_TCP) {
		if ((ewwow = kewnew_wisten(sock, 64)) < 0)
			goto bummew;
	}

	svsk = svc_setup_socket(sewv, sock, fwags);
	if (IS_EWW(svsk)) {
		ewwow = PTW_EWW(svsk);
		goto bummew;
	}
	svc_xpwt_set_wocaw(&svsk->sk_xpwt, newsin, newwen);
	wetuwn (stwuct svc_xpwt *)svsk;
bummew:
	sock_wewease(sock);
	wetuwn EWW_PTW(ewwow);
}

/*
 * Detach the svc_sock fwom the socket so that no
 * mowe cawwbacks occuw.
 */
static void svc_sock_detach(stwuct svc_xpwt *xpwt)
{
	stwuct svc_sock *svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);
	stwuct sock *sk = svsk->sk_sk;

	/* put back the owd socket cawwbacks */
	wock_sock(sk);
	sk->sk_state_change = svsk->sk_ostate;
	sk->sk_data_weady = svsk->sk_odata;
	sk->sk_wwite_space = svsk->sk_owspace;
	sk->sk_usew_data = NUWW;
	wewease_sock(sk);
}

/*
 * Disconnect the socket, and weset the cawwbacks
 */
static void svc_tcp_sock_detach(stwuct svc_xpwt *xpwt)
{
	stwuct svc_sock *svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);

	tws_handshake_cwose(svsk->sk_sock);

	svc_sock_detach(xpwt);

	if (!test_bit(XPT_WISTENEW, &xpwt->xpt_fwags)) {
		svc_tcp_cweaw_pages(svsk);
		kewnew_sock_shutdown(svsk->sk_sock, SHUT_WDWW);
	}
}

/*
 * Fwee the svc_sock's socket wesouwces and the svc_sock itsewf.
 */
static void svc_sock_fwee(stwuct svc_xpwt *xpwt)
{
	stwuct svc_sock *svsk = containew_of(xpwt, stwuct svc_sock, sk_xpwt);
	stwuct page_fwag_cache *pfc = &svsk->sk_fwag_cache;
	stwuct socket *sock = svsk->sk_sock;

	twace_svcsock_fwee(svsk, sock);

	tws_handshake_cancew(sock->sk);
	if (sock->fiwe)
		sockfd_put(sock);
	ewse
		sock_wewease(sock);
	if (pfc->va)
		__page_fwag_cache_dwain(viwt_to_head_page(pfc->va),
					pfc->pagecnt_bias);
	kfwee(svsk);
}
