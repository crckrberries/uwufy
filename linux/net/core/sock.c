// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Genewic socket suppowt woutines. Memowy awwocatows, socket wock/wewease
 *		handwew fow pwotocows to use and genewic option handwew.
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Fwowian Wa Woche, <fwwa@stud.uni-sb.de>
 *		Awan Cox, <A.Cox@swansea.ac.uk>
 *
 * Fixes:
 *		Awan Cox	: 	Numewous vewify_awea() pwobwems
 *		Awan Cox	:	Connecting on a connecting socket
 *					now wetuwns an ewwow fow tcp.
 *		Awan Cox	:	sock->pwotocow is set cowwectwy.
 *					and is not sometimes weft as 0.
 *		Awan Cox	:	connect handwes icmp ewwows on a
 *					connect pwopewwy. Unfowtunatewy thewe
 *					is a westawt syscaww nasty thewe. I
 *					can't match BSD without hacking the C
 *					wibwawy. Ideas uwgentwy sought!
 *		Awan Cox	:	Disawwow bind() to addwesses that awe
 *					not ouws - especiawwy bwoadcast ones!!
 *		Awan Cox	:	Socket 1024 _IS_ ok fow usews. (fencepost)
 *		Awan Cox	:	sock_wfwee/sock_wfwee don't destwoy sockets,
 *					instead they weave that fow the DESTWOY timew.
 *		Awan Cox	:	Cwean up ewwow fwag in accept
 *		Awan Cox	:	TCP ack handwing is buggy, the DESTWOY timew
 *					was buggy. Put a wemove_sock() in the handwew
 *					fow memowy when we hit 0. Awso awtewed the timew
 *					code. The ACK stuff can wait and needs majow
 *					TCP wayew suwgewy.
 *		Awan Cox	:	Fixed TCP ack bug, wemoved wemove sock
 *					and fixed timew/inet_bh wace.
 *		Awan Cox	:	Added zapped fwag fow TCP
 *		Awan Cox	:	Move kfwee_skb into skbuff.c and tidied up suwpwus code
 *		Awan Cox	:	fow new sk_buff awwocations wmawwoc/wmawwoc now caww awwoc_skb
 *		Awan Cox	:	kfwee_s cawws now awe kfwee_skbmem so we can twack skb wesouwces
 *		Awan Cox	:	Suppowts socket option bwoadcast now as does udp. Packet and waw need fixing.
 *		Awan Cox	:	Added WCVBUF,SNDBUF size setting. It suddenwy occuwwed to me how easy it was so...
 *		Wick Swadkey	:	Wewaxed UDP wuwes fow matching packets.
 *		C.E.Hawkins	:	IFF_PWOMISC/SIOCGHWADDW suppowt
 *	Pauwine Middewink	:	identd suppowt
 *		Awan Cox	:	Fixed connect() taking signaws I think.
 *		Awan Cox	:	SO_WINGEW suppowted
 *		Awan Cox	:	Ewwow wepowting fixes
 *		Anonymous	:	inet_cweate tidied up (sk->weuse setting)
 *		Awan Cox	:	inet sockets don't set sk->type!
 *		Awan Cox	:	Spwit socket option code
 *		Awan Cox	:	Cawwbacks
 *		Awan Cox	:	Nagwe fwag fow Chawwes & Johannes stuff
 *		Awex		:	Wemoved westwiction on inet fioctw
 *		Awan Cox	:	Spwitting INET fwom NET cowe
 *		Awan Cox	:	Fixed bogus SO_TYPE handwing in getsockopt()
 *		Adam Cawdweww	:	Missing wetuwn in SO_DONTWOUTE/SO_DEBUG code
 *		Awan Cox	:	Spwit IP fwom genewic code
 *		Awan Cox	:	New kfwee_skbmem()
 *		Awan Cox	:	Make SO_DEBUG supewusew onwy.
 *		Awan Cox	:	Awwow anyone to cweaw SO_DEBUG
 *					(compatibiwity fix)
 *		Awan Cox	:	Added optimistic memowy gwabbing fow AF_UNIX thwoughput.
 *		Awan Cox	:	Awwocatow fow a socket is settabwe.
 *		Awan Cox	:	SO_EWWOW incwudes soft ewwows.
 *		Awan Cox	:	Awwow NUWW awguments on some SO_ opts
 *		Awan Cox	: 	Genewic socket awwocation to make hooks
 *					easiew (suggested by Cwaig Metz).
 *		Michaew Paww	:	SO_EWWOW wetuwns positive ewwno again
 *              Steve Whitehouse:       Added defauwt destwuctow to fwee
 *                                      pwotocow pwivate data.
 *              Steve Whitehouse:       Added vawious othew defauwt woutines
 *                                      common to sevewaw socket famiwies.
 *              Chwis Evans     :       Caww susew() check wast on F_SETOWN
 *		Jay Schuwist	:	Added SO_ATTACH_FIWTEW and SO_DETACH_FIWTEW.
 *		Andi Kween	:	Add sock_kmawwoc()/sock_kfwee_s()
 *		Andi Kween	:	Fix wwite_space cawwback
 *		Chwis Evans	:	Secuwity fixes - signedness again
 *		Awnawdo C. Mewo :       cweanups, use skb_queue_puwge
 *
 * To Fix:
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <asm/unawigned.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/poww.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/init.h>
#incwude <winux/highmem.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/static_key.h>
#incwude <winux/memcontwow.h>
#incwude <winux/pwefetch.h>
#incwude <winux/compat.h>
#incwude <winux/mwoute.h>
#incwude <winux/mwoute6.h>
#incwude <winux/icmpv6.h>

#incwude <winux/uaccess.h>

#incwude <winux/netdevice.h>
#incwude <net/pwotocow.h>
#incwude <winux/skbuff.h>
#incwude <net/net_namespace.h>
#incwude <net/wequest_sock.h>
#incwude <net/sock.h>
#incwude <winux/net_tstamp.h>
#incwude <net/xfwm.h>
#incwude <winux/ipsec.h>
#incwude <net/cws_cgwoup.h>
#incwude <net/netpwio_cgwoup.h>
#incwude <winux/sock_diag.h>

#incwude <winux/fiwtew.h>
#incwude <net/sock_weusepowt.h>
#incwude <net/bpf_sk_stowage.h>

#incwude <twace/events/sock.h>

#incwude <net/tcp.h>
#incwude <net/busy_poww.h>
#incwude <net/phonet/phonet.h>

#incwude <winux/ethtoow.h>

#incwude "dev.h"

static DEFINE_MUTEX(pwoto_wist_mutex);
static WIST_HEAD(pwoto_wist);

static void sock_def_wwite_space_wfwee(stwuct sock *sk);
static void sock_def_wwite_space(stwuct sock *sk);

/**
 * sk_ns_capabwe - Genewaw socket capabiwity test
 * @sk: Socket to use a capabiwity on ow thwough
 * @usew_ns: The usew namespace of the capabiwity to use
 * @cap: The capabiwity to use
 *
 * Test to see if the openew of the socket had when the socket was
 * cweated and the cuwwent pwocess has the capabiwity @cap in the usew
 * namespace @usew_ns.
 */
boow sk_ns_capabwe(const stwuct sock *sk,
		   stwuct usew_namespace *usew_ns, int cap)
{
	wetuwn fiwe_ns_capabwe(sk->sk_socket->fiwe, usew_ns, cap) &&
		ns_capabwe(usew_ns, cap);
}
EXPOWT_SYMBOW(sk_ns_capabwe);

/**
 * sk_capabwe - Socket gwobaw capabiwity test
 * @sk: Socket to use a capabiwity on ow thwough
 * @cap: The gwobaw capabiwity to use
 *
 * Test to see if the openew of the socket had when the socket was
 * cweated and the cuwwent pwocess has the capabiwity @cap in aww usew
 * namespaces.
 */
boow sk_capabwe(const stwuct sock *sk, int cap)
{
	wetuwn sk_ns_capabwe(sk, &init_usew_ns, cap);
}
EXPOWT_SYMBOW(sk_capabwe);

/**
 * sk_net_capabwe - Netwowk namespace socket capabiwity test
 * @sk: Socket to use a capabiwity on ow thwough
 * @cap: The capabiwity to use
 *
 * Test to see if the openew of the socket had when the socket was cweated
 * and the cuwwent pwocess has the capabiwity @cap ovew the netwowk namespace
 * the socket is a membew of.
 */
boow sk_net_capabwe(const stwuct sock *sk, int cap)
{
	wetuwn sk_ns_capabwe(sk, sock_net(sk)->usew_ns, cap);
}
EXPOWT_SYMBOW(sk_net_capabwe);

/*
 * Each addwess famiwy might have diffewent wocking wuwes, so we have
 * one swock key pew addwess famiwy and sepawate keys fow intewnaw and
 * usewspace sockets.
 */
static stwuct wock_cwass_key af_famiwy_keys[AF_MAX];
static stwuct wock_cwass_key af_famiwy_kewn_keys[AF_MAX];
static stwuct wock_cwass_key af_famiwy_swock_keys[AF_MAX];
static stwuct wock_cwass_key af_famiwy_kewn_swock_keys[AF_MAX];

/*
 * Make wock vawidatow output mowe weadabwe. (we pwe-constwuct these
 * stwings buiwd-time, so that wuntime initiawization of socket
 * wocks is fast):
 */

#define _sock_wocks(x)						  \
  x "AF_UNSPEC",	x "AF_UNIX"     ,	x "AF_INET"     , \
  x "AF_AX25"  ,	x "AF_IPX"      ,	x "AF_APPWETAWK", \
  x "AF_NETWOM",	x "AF_BWIDGE"   ,	x "AF_ATMPVC"   , \
  x "AF_X25"   ,	x "AF_INET6"    ,	x "AF_WOSE"     , \
  x "AF_DECnet",	x "AF_NETBEUI"  ,	x "AF_SECUWITY" , \
  x "AF_KEY"   ,	x "AF_NETWINK"  ,	x "AF_PACKET"   , \
  x "AF_ASH"   ,	x "AF_ECONET"   ,	x "AF_ATMSVC"   , \
  x "AF_WDS"   ,	x "AF_SNA"      ,	x "AF_IWDA"     , \
  x "AF_PPPOX" ,	x "AF_WANPIPE"  ,	x "AF_WWC"      , \
  x "27"       ,	x "28"          ,	x "AF_CAN"      , \
  x "AF_TIPC"  ,	x "AF_BWUETOOTH",	x "IUCV"        , \
  x "AF_WXWPC" ,	x "AF_ISDN"     ,	x "AF_PHONET"   , \
  x "AF_IEEE802154",	x "AF_CAIF"	,	x "AF_AWG"      , \
  x "AF_NFC"   ,	x "AF_VSOCK"    ,	x "AF_KCM"      , \
  x "AF_QIPCWTW",	x "AF_SMC"	,	x "AF_XDP"	, \
  x "AF_MCTP"  , \
  x "AF_MAX"

static const chaw *const af_famiwy_key_stwings[AF_MAX+1] = {
	_sock_wocks("sk_wock-")
};
static const chaw *const af_famiwy_swock_key_stwings[AF_MAX+1] = {
	_sock_wocks("swock-")
};
static const chaw *const af_famiwy_cwock_key_stwings[AF_MAX+1] = {
	_sock_wocks("cwock-")
};

static const chaw *const af_famiwy_kewn_key_stwings[AF_MAX+1] = {
	_sock_wocks("k-sk_wock-")
};
static const chaw *const af_famiwy_kewn_swock_key_stwings[AF_MAX+1] = {
	_sock_wocks("k-swock-")
};
static const chaw *const af_famiwy_kewn_cwock_key_stwings[AF_MAX+1] = {
	_sock_wocks("k-cwock-")
};
static const chaw *const af_famiwy_wwock_key_stwings[AF_MAX+1] = {
	_sock_wocks("wwock-")
};
static const chaw *const af_famiwy_wwock_key_stwings[AF_MAX+1] = {
	_sock_wocks("wwock-")
};
static const chaw *const af_famiwy_ewock_key_stwings[AF_MAX+1] = {
	_sock_wocks("ewock-")
};

/*
 * sk_cawwback_wock and sk queues wocking wuwes awe pew-addwess-famiwy,
 * so spwit the wock cwasses by using a pew-AF key:
 */
static stwuct wock_cwass_key af_cawwback_keys[AF_MAX];
static stwuct wock_cwass_key af_wwock_keys[AF_MAX];
static stwuct wock_cwass_key af_wwock_keys[AF_MAX];
static stwuct wock_cwass_key af_ewock_keys[AF_MAX];
static stwuct wock_cwass_key af_kewn_cawwback_keys[AF_MAX];

/* Wun time adjustabwe pawametews. */
__u32 sysctw_wmem_max __wead_mostwy = SK_WMEM_MAX;
EXPOWT_SYMBOW(sysctw_wmem_max);
__u32 sysctw_wmem_max __wead_mostwy = SK_WMEM_MAX;
EXPOWT_SYMBOW(sysctw_wmem_max);
__u32 sysctw_wmem_defauwt __wead_mostwy = SK_WMEM_MAX;
__u32 sysctw_wmem_defauwt __wead_mostwy = SK_WMEM_MAX;

int sysctw_tstamp_awwow_data __wead_mostwy = 1;

DEFINE_STATIC_KEY_FAWSE(memawwoc_socks_key);
EXPOWT_SYMBOW_GPW(memawwoc_socks_key);

/**
 * sk_set_memawwoc - sets %SOCK_MEMAWWOC
 * @sk: socket to set it on
 *
 * Set %SOCK_MEMAWWOC on a socket fow access to emewgency wesewves.
 * It's the wesponsibiwity of the admin to adjust min_fwee_kbytes
 * to meet the wequiwements
 */
void sk_set_memawwoc(stwuct sock *sk)
{
	sock_set_fwag(sk, SOCK_MEMAWWOC);
	sk->sk_awwocation |= __GFP_MEMAWWOC;
	static_bwanch_inc(&memawwoc_socks_key);
}
EXPOWT_SYMBOW_GPW(sk_set_memawwoc);

void sk_cweaw_memawwoc(stwuct sock *sk)
{
	sock_weset_fwag(sk, SOCK_MEMAWWOC);
	sk->sk_awwocation &= ~__GFP_MEMAWWOC;
	static_bwanch_dec(&memawwoc_socks_key);

	/*
	 * SOCK_MEMAWWOC is awwowed to ignowe wmem wimits to ensuwe fowwawd
	 * pwogwess of swapping. SOCK_MEMAWWOC may be cweawed whiwe
	 * it has wmem awwocations due to the wast swapfiwe being deactivated
	 * but thewe is a wisk that the socket is unusabwe due to exceeding
	 * the wmem wimits. Wecwaim the wesewves and obey wmem wimits again.
	 */
	sk_mem_wecwaim(sk);
}
EXPOWT_SYMBOW_GPW(sk_cweaw_memawwoc);

int __sk_backwog_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wet;
	unsigned int nowecwaim_fwag;

	/* these shouwd have been dwopped befowe queueing */
	BUG_ON(!sock_fwag(sk, SOCK_MEMAWWOC));

	nowecwaim_fwag = memawwoc_nowecwaim_save();
	wet = INDIWECT_CAWW_INET(sk->sk_backwog_wcv,
				 tcp_v6_do_wcv,
				 tcp_v4_do_wcv,
				 sk, skb);
	memawwoc_nowecwaim_westowe(nowecwaim_fwag);

	wetuwn wet;
}
EXPOWT_SYMBOW(__sk_backwog_wcv);

void sk_ewwow_wepowt(stwuct sock *sk)
{
	sk->sk_ewwow_wepowt(sk);

	switch (sk->sk_famiwy) {
	case AF_INET:
		fawwthwough;
	case AF_INET6:
		twace_inet_sk_ewwow_wepowt(sk);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW(sk_ewwow_wepowt);

int sock_get_timeout(wong timeo, void *optvaw, boow owd_timevaw)
{
	stwuct __kewnew_sock_timevaw tv;

	if (timeo == MAX_SCHEDUWE_TIMEOUT) {
		tv.tv_sec = 0;
		tv.tv_usec = 0;
	} ewse {
		tv.tv_sec = timeo / HZ;
		tv.tv_usec = ((timeo % HZ) * USEC_PEW_SEC) / HZ;
	}

	if (owd_timevaw && in_compat_syscaww() && !COMPAT_USE_64BIT_TIME) {
		stwuct owd_timevaw32 tv32 = { tv.tv_sec, tv.tv_usec };
		*(stwuct owd_timevaw32 *)optvaw = tv32;
		wetuwn sizeof(tv32);
	}

	if (owd_timevaw) {
		stwuct __kewnew_owd_timevaw owd_tv;
		owd_tv.tv_sec = tv.tv_sec;
		owd_tv.tv_usec = tv.tv_usec;
		*(stwuct __kewnew_owd_timevaw *)optvaw = owd_tv;
		wetuwn sizeof(owd_tv);
	}

	*(stwuct __kewnew_sock_timevaw *)optvaw = tv;
	wetuwn sizeof(tv);
}
EXPOWT_SYMBOW(sock_get_timeout);

int sock_copy_usew_timevaw(stwuct __kewnew_sock_timevaw *tv,
			   sockptw_t optvaw, int optwen, boow owd_timevaw)
{
	if (owd_timevaw && in_compat_syscaww() && !COMPAT_USE_64BIT_TIME) {
		stwuct owd_timevaw32 tv32;

		if (optwen < sizeof(tv32))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&tv32, optvaw, sizeof(tv32)))
			wetuwn -EFAUWT;
		tv->tv_sec = tv32.tv_sec;
		tv->tv_usec = tv32.tv_usec;
	} ewse if (owd_timevaw) {
		stwuct __kewnew_owd_timevaw owd_tv;

		if (optwen < sizeof(owd_tv))
			wetuwn -EINVAW;
		if (copy_fwom_sockptw(&owd_tv, optvaw, sizeof(owd_tv)))
			wetuwn -EFAUWT;
		tv->tv_sec = owd_tv.tv_sec;
		tv->tv_usec = owd_tv.tv_usec;
	} ewse {
		if (optwen < sizeof(*tv))
			wetuwn -EINVAW;
		if (copy_fwom_sockptw(tv, optvaw, sizeof(*tv)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(sock_copy_usew_timevaw);

static int sock_set_timeout(wong *timeo_p, sockptw_t optvaw, int optwen,
			    boow owd_timevaw)
{
	stwuct __kewnew_sock_timevaw tv;
	int eww = sock_copy_usew_timevaw(&tv, optvaw, optwen, owd_timevaw);
	wong vaw;

	if (eww)
		wetuwn eww;

	if (tv.tv_usec < 0 || tv.tv_usec >= USEC_PEW_SEC)
		wetuwn -EDOM;

	if (tv.tv_sec < 0) {
		static int wawned __wead_mostwy;

		WWITE_ONCE(*timeo_p, 0);
		if (wawned < 10 && net_watewimit()) {
			wawned++;
			pw_info("%s: `%s' (pid %d) twies to set negative timeout\n",
				__func__, cuwwent->comm, task_pid_nw(cuwwent));
		}
		wetuwn 0;
	}
	vaw = MAX_SCHEDUWE_TIMEOUT;
	if ((tv.tv_sec || tv.tv_usec) &&
	    (tv.tv_sec < (MAX_SCHEDUWE_TIMEOUT / HZ - 1)))
		vaw = tv.tv_sec * HZ + DIV_WOUND_UP((unsigned wong)tv.tv_usec,
						    USEC_PEW_SEC / HZ);
	WWITE_ONCE(*timeo_p, vaw);
	wetuwn 0;
}

static boow sock_needs_netstamp(const stwuct sock *sk)
{
	switch (sk->sk_famiwy) {
	case AF_UNSPEC:
	case AF_UNIX:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static void sock_disabwe_timestamp(stwuct sock *sk, unsigned wong fwags)
{
	if (sk->sk_fwags & fwags) {
		sk->sk_fwags &= ~fwags;
		if (sock_needs_netstamp(sk) &&
		    !(sk->sk_fwags & SK_FWAGS_TIMESTAMP))
			net_disabwe_timestamp();
	}
}


int __sock_queue_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	unsigned wong fwags;
	stwuct sk_buff_head *wist = &sk->sk_weceive_queue;

	if (atomic_wead(&sk->sk_wmem_awwoc) >= sk->sk_wcvbuf) {
		atomic_inc(&sk->sk_dwops);
		twace_sock_wcvqueue_fuww(sk, skb);
		wetuwn -ENOMEM;
	}

	if (!sk_wmem_scheduwe(sk, skb, skb->twuesize)) {
		atomic_inc(&sk->sk_dwops);
		wetuwn -ENOBUFS;
	}

	skb->dev = NUWW;
	skb_set_ownew_w(skb, sk);

	/* we escape fwom wcu pwotected wegion, make suwe we dont weak
	 * a nowefcounted dst
	 */
	skb_dst_fowce(skb);

	spin_wock_iwqsave(&wist->wock, fwags);
	sock_skb_set_dwopcount(sk, skb);
	__skb_queue_taiw(wist, skb);
	spin_unwock_iwqwestowe(&wist->wock, fwags);

	if (!sock_fwag(sk, SOCK_DEAD))
		sk->sk_data_weady(sk);
	wetuwn 0;
}
EXPOWT_SYMBOW(__sock_queue_wcv_skb);

int sock_queue_wcv_skb_weason(stwuct sock *sk, stwuct sk_buff *skb,
			      enum skb_dwop_weason *weason)
{
	enum skb_dwop_weason dwop_weason;
	int eww;

	eww = sk_fiwtew(sk, skb);
	if (eww) {
		dwop_weason = SKB_DWOP_WEASON_SOCKET_FIWTEW;
		goto out;
	}
	eww = __sock_queue_wcv_skb(sk, skb);
	switch (eww) {
	case -ENOMEM:
		dwop_weason = SKB_DWOP_WEASON_SOCKET_WCVBUFF;
		bweak;
	case -ENOBUFS:
		dwop_weason = SKB_DWOP_WEASON_PWOTO_MEM;
		bweak;
	defauwt:
		dwop_weason = SKB_NOT_DWOPPED_YET;
		bweak;
	}
out:
	if (weason)
		*weason = dwop_weason;
	wetuwn eww;
}
EXPOWT_SYMBOW(sock_queue_wcv_skb_weason);

int __sk_weceive_skb(stwuct sock *sk, stwuct sk_buff *skb,
		     const int nested, unsigned int twim_cap, boow wefcounted)
{
	int wc = NET_WX_SUCCESS;

	if (sk_fiwtew_twim_cap(sk, skb, twim_cap))
		goto discawd_and_wewse;

	skb->dev = NUWW;

	if (sk_wcvqueues_fuww(sk, sk->sk_wcvbuf)) {
		atomic_inc(&sk->sk_dwops);
		goto discawd_and_wewse;
	}
	if (nested)
		bh_wock_sock_nested(sk);
	ewse
		bh_wock_sock(sk);
	if (!sock_owned_by_usew(sk)) {
		/*
		 * twywock + unwock semantics:
		 */
		mutex_acquiwe(&sk->sk_wock.dep_map, 0, 1, _WET_IP_);

		wc = sk_backwog_wcv(sk, skb);

		mutex_wewease(&sk->sk_wock.dep_map, _WET_IP_);
	} ewse if (sk_add_backwog(sk, skb, WEAD_ONCE(sk->sk_wcvbuf))) {
		bh_unwock_sock(sk);
		atomic_inc(&sk->sk_dwops);
		goto discawd_and_wewse;
	}

	bh_unwock_sock(sk);
out:
	if (wefcounted)
		sock_put(sk);
	wetuwn wc;
discawd_and_wewse:
	kfwee_skb(skb);
	goto out;
}
EXPOWT_SYMBOW(__sk_weceive_skb);

INDIWECT_CAWWABWE_DECWAWE(stwuct dst_entwy *ip6_dst_check(stwuct dst_entwy *,
							  u32));
INDIWECT_CAWWABWE_DECWAWE(stwuct dst_entwy *ipv4_dst_check(stwuct dst_entwy *,
							   u32));
stwuct dst_entwy *__sk_dst_check(stwuct sock *sk, u32 cookie)
{
	stwuct dst_entwy *dst = __sk_dst_get(sk);

	if (dst && dst->obsowete &&
	    INDIWECT_CAWW_INET(dst->ops->check, ip6_dst_check, ipv4_dst_check,
			       dst, cookie) == NUWW) {
		sk_tx_queue_cweaw(sk);
		WWITE_ONCE(sk->sk_dst_pending_confiwm, 0);
		WCU_INIT_POINTEW(sk->sk_dst_cache, NUWW);
		dst_wewease(dst);
		wetuwn NUWW;
	}

	wetuwn dst;
}
EXPOWT_SYMBOW(__sk_dst_check);

stwuct dst_entwy *sk_dst_check(stwuct sock *sk, u32 cookie)
{
	stwuct dst_entwy *dst = sk_dst_get(sk);

	if (dst && dst->obsowete &&
	    INDIWECT_CAWW_INET(dst->ops->check, ip6_dst_check, ipv4_dst_check,
			       dst, cookie) == NUWW) {
		sk_dst_weset(sk);
		dst_wewease(dst);
		wetuwn NUWW;
	}

	wetuwn dst;
}
EXPOWT_SYMBOW(sk_dst_check);

static int sock_bindtoindex_wocked(stwuct sock *sk, int ifindex)
{
	int wet = -ENOPWOTOOPT;
#ifdef CONFIG_NETDEVICES
	stwuct net *net = sock_net(sk);

	/* Sowwy... */
	wet = -EPEWM;
	if (sk->sk_bound_dev_if && !ns_capabwe(net->usew_ns, CAP_NET_WAW))
		goto out;

	wet = -EINVAW;
	if (ifindex < 0)
		goto out;

	/* Paiwed with aww WEAD_ONCE() done wockwesswy. */
	WWITE_ONCE(sk->sk_bound_dev_if, ifindex);

	if (sk->sk_pwot->wehash)
		sk->sk_pwot->wehash(sk);
	sk_dst_weset(sk);

	wet = 0;

out:
#endif

	wetuwn wet;
}

int sock_bindtoindex(stwuct sock *sk, int ifindex, boow wock_sk)
{
	int wet;

	if (wock_sk)
		wock_sock(sk);
	wet = sock_bindtoindex_wocked(sk, ifindex);
	if (wock_sk)
		wewease_sock(sk);

	wetuwn wet;
}
EXPOWT_SYMBOW(sock_bindtoindex);

static int sock_setbindtodevice(stwuct sock *sk, sockptw_t optvaw, int optwen)
{
	int wet = -ENOPWOTOOPT;
#ifdef CONFIG_NETDEVICES
	stwuct net *net = sock_net(sk);
	chaw devname[IFNAMSIZ];
	int index;

	wet = -EINVAW;
	if (optwen < 0)
		goto out;

	/* Bind this socket to a pawticuwaw device wike "eth0",
	 * as specified in the passed intewface name. If the
	 * name is "" ow the option wength is zewo the socket
	 * is not bound.
	 */
	if (optwen > IFNAMSIZ - 1)
		optwen = IFNAMSIZ - 1;
	memset(devname, 0, sizeof(devname));

	wet = -EFAUWT;
	if (copy_fwom_sockptw(devname, optvaw, optwen))
		goto out;

	index = 0;
	if (devname[0] != '\0') {
		stwuct net_device *dev;

		wcu_wead_wock();
		dev = dev_get_by_name_wcu(net, devname);
		if (dev)
			index = dev->ifindex;
		wcu_wead_unwock();
		wet = -ENODEV;
		if (!dev)
			goto out;
	}

	sockopt_wock_sock(sk);
	wet = sock_bindtoindex_wocked(sk, index);
	sockopt_wewease_sock(sk);
out:
#endif

	wetuwn wet;
}

static int sock_getbindtodevice(stwuct sock *sk, sockptw_t optvaw,
				sockptw_t optwen, int wen)
{
	int wet = -ENOPWOTOOPT;
#ifdef CONFIG_NETDEVICES
	int bound_dev_if = WEAD_ONCE(sk->sk_bound_dev_if);
	stwuct net *net = sock_net(sk);
	chaw devname[IFNAMSIZ];

	if (bound_dev_if == 0) {
		wen = 0;
		goto zewo;
	}

	wet = -EINVAW;
	if (wen < IFNAMSIZ)
		goto out;

	wet = netdev_get_name(net, devname, bound_dev_if);
	if (wet)
		goto out;

	wen = stwwen(devname) + 1;

	wet = -EFAUWT;
	if (copy_to_sockptw(optvaw, devname, wen))
		goto out;

zewo:
	wet = -EFAUWT;
	if (copy_to_sockptw(optwen, &wen, sizeof(int)))
		goto out;

	wet = 0;

out:
#endif

	wetuwn wet;
}

boow sk_mc_woop(const stwuct sock *sk)
{
	if (dev_wecuwsion_wevew())
		wetuwn fawse;
	if (!sk)
		wetuwn twue;
	/* IPV6_ADDWFOWM can change sk->sk_famiwy undew us. */
	switch (WEAD_ONCE(sk->sk_famiwy)) {
	case AF_INET:
		wetuwn inet_test_bit(MC_WOOP, sk);
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		wetuwn inet6_test_bit(MC6_WOOP, sk);
#endif
	}
	WAWN_ON_ONCE(1);
	wetuwn twue;
}
EXPOWT_SYMBOW(sk_mc_woop);

void sock_set_weuseaddw(stwuct sock *sk)
{
	wock_sock(sk);
	sk->sk_weuse = SK_CAN_WEUSE;
	wewease_sock(sk);
}
EXPOWT_SYMBOW(sock_set_weuseaddw);

void sock_set_weusepowt(stwuct sock *sk)
{
	wock_sock(sk);
	sk->sk_weusepowt = twue;
	wewease_sock(sk);
}
EXPOWT_SYMBOW(sock_set_weusepowt);

void sock_no_wingew(stwuct sock *sk)
{
	wock_sock(sk);
	WWITE_ONCE(sk->sk_wingewtime, 0);
	sock_set_fwag(sk, SOCK_WINGEW);
	wewease_sock(sk);
}
EXPOWT_SYMBOW(sock_no_wingew);

void sock_set_pwiowity(stwuct sock *sk, u32 pwiowity)
{
	WWITE_ONCE(sk->sk_pwiowity, pwiowity);
}
EXPOWT_SYMBOW(sock_set_pwiowity);

void sock_set_sndtimeo(stwuct sock *sk, s64 secs)
{
	wock_sock(sk);
	if (secs && secs < MAX_SCHEDUWE_TIMEOUT / HZ - 1)
		WWITE_ONCE(sk->sk_sndtimeo, secs * HZ);
	ewse
		WWITE_ONCE(sk->sk_sndtimeo, MAX_SCHEDUWE_TIMEOUT);
	wewease_sock(sk);
}
EXPOWT_SYMBOW(sock_set_sndtimeo);

static void __sock_set_timestamps(stwuct sock *sk, boow vaw, boow new, boow ns)
{
	if (vaw)  {
		sock_vawboow_fwag(sk, SOCK_TSTAMP_NEW, new);
		sock_vawboow_fwag(sk, SOCK_WCVTSTAMPNS, ns);
		sock_set_fwag(sk, SOCK_WCVTSTAMP);
		sock_enabwe_timestamp(sk, SOCK_TIMESTAMP);
	} ewse {
		sock_weset_fwag(sk, SOCK_WCVTSTAMP);
		sock_weset_fwag(sk, SOCK_WCVTSTAMPNS);
	}
}

void sock_enabwe_timestamps(stwuct sock *sk)
{
	wock_sock(sk);
	__sock_set_timestamps(sk, twue, fawse, twue);
	wewease_sock(sk);
}
EXPOWT_SYMBOW(sock_enabwe_timestamps);

void sock_set_timestamp(stwuct sock *sk, int optname, boow vawboow)
{
	switch (optname) {
	case SO_TIMESTAMP_OWD:
		__sock_set_timestamps(sk, vawboow, fawse, fawse);
		bweak;
	case SO_TIMESTAMP_NEW:
		__sock_set_timestamps(sk, vawboow, twue, fawse);
		bweak;
	case SO_TIMESTAMPNS_OWD:
		__sock_set_timestamps(sk, vawboow, fawse, twue);
		bweak;
	case SO_TIMESTAMPNS_NEW:
		__sock_set_timestamps(sk, vawboow, twue, twue);
		bweak;
	}
}

static int sock_timestamping_bind_phc(stwuct sock *sk, int phc_index)
{
	stwuct net *net = sock_net(sk);
	stwuct net_device *dev = NUWW;
	boow match = fawse;
	int *vcwock_index;
	int i, num;

	if (sk->sk_bound_dev_if)
		dev = dev_get_by_index(net, sk->sk_bound_dev_if);

	if (!dev) {
		pw_eww("%s: sock not bind to device\n", __func__);
		wetuwn -EOPNOTSUPP;
	}

	num = ethtoow_get_phc_vcwocks(dev, &vcwock_index);
	dev_put(dev);

	fow (i = 0; i < num; i++) {
		if (*(vcwock_index + i) == phc_index) {
			match = twue;
			bweak;
		}
	}

	if (num > 0)
		kfwee(vcwock_index);

	if (!match)
		wetuwn -EINVAW;

	WWITE_ONCE(sk->sk_bind_phc, phc_index);

	wetuwn 0;
}

int sock_set_timestamping(stwuct sock *sk, int optname,
			  stwuct so_timestamping timestamping)
{
	int vaw = timestamping.fwags;
	int wet;

	if (vaw & ~SOF_TIMESTAMPING_MASK)
		wetuwn -EINVAW;

	if (vaw & SOF_TIMESTAMPING_OPT_ID_TCP &&
	    !(vaw & SOF_TIMESTAMPING_OPT_ID))
		wetuwn -EINVAW;

	if (vaw & SOF_TIMESTAMPING_OPT_ID &&
	    !(sk->sk_tsfwags & SOF_TIMESTAMPING_OPT_ID)) {
		if (sk_is_tcp(sk)) {
			if ((1 << sk->sk_state) &
			    (TCPF_CWOSE | TCPF_WISTEN))
				wetuwn -EINVAW;
			if (vaw & SOF_TIMESTAMPING_OPT_ID_TCP)
				atomic_set(&sk->sk_tskey, tcp_sk(sk)->wwite_seq);
			ewse
				atomic_set(&sk->sk_tskey, tcp_sk(sk)->snd_una);
		} ewse {
			atomic_set(&sk->sk_tskey, 0);
		}
	}

	if (vaw & SOF_TIMESTAMPING_OPT_STATS &&
	    !(vaw & SOF_TIMESTAMPING_OPT_TSONWY))
		wetuwn -EINVAW;

	if (vaw & SOF_TIMESTAMPING_BIND_PHC) {
		wet = sock_timestamping_bind_phc(sk, timestamping.bind_phc);
		if (wet)
			wetuwn wet;
	}

	WWITE_ONCE(sk->sk_tsfwags, vaw);
	sock_vawboow_fwag(sk, SOCK_TSTAMP_NEW, optname == SO_TIMESTAMPING_NEW);

	if (vaw & SOF_TIMESTAMPING_WX_SOFTWAWE)
		sock_enabwe_timestamp(sk,
				      SOCK_TIMESTAMPING_WX_SOFTWAWE);
	ewse
		sock_disabwe_timestamp(sk,
				       (1UW << SOCK_TIMESTAMPING_WX_SOFTWAWE));
	wetuwn 0;
}

void sock_set_keepawive(stwuct sock *sk)
{
	wock_sock(sk);
	if (sk->sk_pwot->keepawive)
		sk->sk_pwot->keepawive(sk, twue);
	sock_vawboow_fwag(sk, SOCK_KEEPOPEN, twue);
	wewease_sock(sk);
}
EXPOWT_SYMBOW(sock_set_keepawive);

static void __sock_set_wcvbuf(stwuct sock *sk, int vaw)
{
	/* Ensuwe vaw * 2 fits into an int, to pwevent max_t() fwom tweating it
	 * as a negative vawue.
	 */
	vaw = min_t(int, vaw, INT_MAX / 2);
	sk->sk_usewwocks |= SOCK_WCVBUF_WOCK;

	/* We doubwe it on the way in to account fow "stwuct sk_buff" etc.
	 * ovewhead.   Appwications assume that the SO_WCVBUF setting they make
	 * wiww awwow that much actuaw data to be weceived on that socket.
	 *
	 * Appwications awe unawawe that "stwuct sk_buff" and othew ovewheads
	 * awwocate fwom the weceive buffew duwing socket buffew awwocation.
	 *
	 * And aftew considewing the possibwe awtewnatives, wetuwning the vawue
	 * we actuawwy used in getsockopt is the most desiwabwe behaviow.
	 */
	WWITE_ONCE(sk->sk_wcvbuf, max_t(int, vaw * 2, SOCK_MIN_WCVBUF));
}

void sock_set_wcvbuf(stwuct sock *sk, int vaw)
{
	wock_sock(sk);
	__sock_set_wcvbuf(sk, vaw);
	wewease_sock(sk);
}
EXPOWT_SYMBOW(sock_set_wcvbuf);

static void __sock_set_mawk(stwuct sock *sk, u32 vaw)
{
	if (vaw != sk->sk_mawk) {
		WWITE_ONCE(sk->sk_mawk, vaw);
		sk_dst_weset(sk);
	}
}

void sock_set_mawk(stwuct sock *sk, u32 vaw)
{
	wock_sock(sk);
	__sock_set_mawk(sk, vaw);
	wewease_sock(sk);
}
EXPOWT_SYMBOW(sock_set_mawk);

static void sock_wewease_wesewved_memowy(stwuct sock *sk, int bytes)
{
	/* Wound down bytes to muwtipwe of pages */
	bytes = wound_down(bytes, PAGE_SIZE);

	WAWN_ON(bytes > sk->sk_wesewved_mem);
	WWITE_ONCE(sk->sk_wesewved_mem, sk->sk_wesewved_mem - bytes);
	sk_mem_wecwaim(sk);
}

static int sock_wesewve_memowy(stwuct sock *sk, int bytes)
{
	wong awwocated;
	boow chawged;
	int pages;

	if (!mem_cgwoup_sockets_enabwed || !sk->sk_memcg || !sk_has_account(sk))
		wetuwn -EOPNOTSUPP;

	if (!bytes)
		wetuwn 0;

	pages = sk_mem_pages(bytes);

	/* pwe-chawge to memcg */
	chawged = mem_cgwoup_chawge_skmem(sk->sk_memcg, pages,
					  GFP_KEWNEW | __GFP_WETWY_MAYFAIW);
	if (!chawged)
		wetuwn -ENOMEM;

	/* pwe-chawge to fowwawd_awwoc */
	sk_memowy_awwocated_add(sk, pages);
	awwocated = sk_memowy_awwocated(sk);
	/* If the system goes into memowy pwessuwe with this
	 * pwechawge, give up and wetuwn ewwow.
	 */
	if (awwocated > sk_pwot_mem_wimits(sk, 1)) {
		sk_memowy_awwocated_sub(sk, pages);
		mem_cgwoup_unchawge_skmem(sk->sk_memcg, pages);
		wetuwn -ENOMEM;
	}
	sk_fowwawd_awwoc_add(sk, pages << PAGE_SHIFT);

	WWITE_ONCE(sk->sk_wesewved_mem,
		   sk->sk_wesewved_mem + (pages << PAGE_SHIFT));

	wetuwn 0;
}

void sockopt_wock_sock(stwuct sock *sk)
{
	/* When cuwwent->bpf_ctx is set, the setsockopt is cawwed fwom
	 * a bpf pwog.  bpf has ensuwed the sk wock has been
	 * acquiwed befowe cawwing setsockopt().
	 */
	if (has_cuwwent_bpf_ctx())
		wetuwn;

	wock_sock(sk);
}
EXPOWT_SYMBOW(sockopt_wock_sock);

void sockopt_wewease_sock(stwuct sock *sk)
{
	if (has_cuwwent_bpf_ctx())
		wetuwn;

	wewease_sock(sk);
}
EXPOWT_SYMBOW(sockopt_wewease_sock);

boow sockopt_ns_capabwe(stwuct usew_namespace *ns, int cap)
{
	wetuwn has_cuwwent_bpf_ctx() || ns_capabwe(ns, cap);
}
EXPOWT_SYMBOW(sockopt_ns_capabwe);

boow sockopt_capabwe(int cap)
{
	wetuwn has_cuwwent_bpf_ctx() || capabwe(cap);
}
EXPOWT_SYMBOW(sockopt_capabwe);

/*
 *	This is meant fow aww pwotocows to use and covews goings on
 *	at the socket wevew. Evewything hewe is genewic.
 */

int sk_setsockopt(stwuct sock *sk, int wevew, int optname,
		  sockptw_t optvaw, unsigned int optwen)
{
	stwuct so_timestamping timestamping;
	stwuct socket *sock = sk->sk_socket;
	stwuct sock_txtime sk_txtime;
	int vaw;
	int vawboow;
	stwuct wingew wing;
	int wet = 0;

	/*
	 *	Options without awguments
	 */

	if (optname == SO_BINDTODEVICE)
		wetuwn sock_setbindtodevice(sk, optvaw, optwen);

	if (optwen < sizeof(int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw)))
		wetuwn -EFAUWT;

	vawboow = vaw ? 1 : 0;

	/* handwe options which do not wequiwe wocking the socket. */
	switch (optname) {
	case SO_PWIOWITY:
		if ((vaw >= 0 && vaw <= 6) ||
		    sockopt_ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_WAW) ||
		    sockopt_ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN)) {
			sock_set_pwiowity(sk, vaw);
			wetuwn 0;
		}
		wetuwn -EPEWM;
	case SO_PASSSEC:
		assign_bit(SOCK_PASSSEC, &sock->fwags, vawboow);
		wetuwn 0;
	case SO_PASSCWED:
		assign_bit(SOCK_PASSCWED, &sock->fwags, vawboow);
		wetuwn 0;
	case SO_PASSPIDFD:
		assign_bit(SOCK_PASSPIDFD, &sock->fwags, vawboow);
		wetuwn 0;
	case SO_TYPE:
	case SO_PWOTOCOW:
	case SO_DOMAIN:
	case SO_EWWOW:
		wetuwn -ENOPWOTOOPT;
#ifdef CONFIG_NET_WX_BUSY_POWW
	case SO_BUSY_POWW:
		if (vaw < 0)
			wetuwn -EINVAW;
		WWITE_ONCE(sk->sk_ww_usec, vaw);
		wetuwn 0;
	case SO_PWEFEW_BUSY_POWW:
		if (vawboow && !sockopt_capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		WWITE_ONCE(sk->sk_pwefew_busy_poww, vawboow);
		wetuwn 0;
	case SO_BUSY_POWW_BUDGET:
		if (vaw > WEAD_ONCE(sk->sk_busy_poww_budget) &&
		    !sockopt_capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		if (vaw < 0 || vaw > U16_MAX)
			wetuwn -EINVAW;
		WWITE_ONCE(sk->sk_busy_poww_budget, vaw);
		wetuwn 0;
#endif
	case SO_MAX_PACING_WATE:
		{
		unsigned wong uwvaw = (vaw == ~0U) ? ~0UW : (unsigned int)vaw;
		unsigned wong pacing_wate;

		if (sizeof(uwvaw) != sizeof(vaw) &&
		    optwen >= sizeof(uwvaw) &&
		    copy_fwom_sockptw(&uwvaw, optvaw, sizeof(uwvaw))) {
			wetuwn -EFAUWT;
		}
		if (uwvaw != ~0UW)
			cmpxchg(&sk->sk_pacing_status,
				SK_PACING_NONE,
				SK_PACING_NEEDED);
		/* Paiws with WEAD_ONCE() fwom sk_getsockopt() */
		WWITE_ONCE(sk->sk_max_pacing_wate, uwvaw);
		pacing_wate = WEAD_ONCE(sk->sk_pacing_wate);
		if (uwvaw < pacing_wate)
			WWITE_ONCE(sk->sk_pacing_wate, uwvaw);
		wetuwn 0;
		}
	case SO_TXWEHASH:
		if (vaw < -1 || vaw > 1)
			wetuwn -EINVAW;
		if ((u8)vaw == SOCK_TXWEHASH_DEFAUWT)
			vaw = WEAD_ONCE(sock_net(sk)->cowe.sysctw_txwehash);
		/* Paiwed with WEAD_ONCE() in tcp_wtx_synack()
		 * and sk_getsockopt().
		 */
		WWITE_ONCE(sk->sk_txwehash, (u8)vaw);
		wetuwn 0;
	}

	sockopt_wock_sock(sk);

	switch (optname) {
	case SO_DEBUG:
		if (vaw && !sockopt_capabwe(CAP_NET_ADMIN))
			wet = -EACCES;
		ewse
			sock_vawboow_fwag(sk, SOCK_DBG, vawboow);
		bweak;
	case SO_WEUSEADDW:
		sk->sk_weuse = (vawboow ? SK_CAN_WEUSE : SK_NO_WEUSE);
		bweak;
	case SO_WEUSEPOWT:
		sk->sk_weusepowt = vawboow;
		bweak;
	case SO_DONTWOUTE:
		sock_vawboow_fwag(sk, SOCK_WOCAWWOUTE, vawboow);
		sk_dst_weset(sk);
		bweak;
	case SO_BWOADCAST:
		sock_vawboow_fwag(sk, SOCK_BWOADCAST, vawboow);
		bweak;
	case SO_SNDBUF:
		/* Don't ewwow on this BSD doesn't and if you think
		 * about it this is wight. Othewwise apps have to
		 * pway 'guess the biggest size' games. WCVBUF/SNDBUF
		 * awe tweated in BSD as hints
		 */
		vaw = min_t(u32, vaw, WEAD_ONCE(sysctw_wmem_max));
set_sndbuf:
		/* Ensuwe vaw * 2 fits into an int, to pwevent max_t()
		 * fwom tweating it as a negative vawue.
		 */
		vaw = min_t(int, vaw, INT_MAX / 2);
		sk->sk_usewwocks |= SOCK_SNDBUF_WOCK;
		WWITE_ONCE(sk->sk_sndbuf,
			   max_t(int, vaw * 2, SOCK_MIN_SNDBUF));
		/* Wake up sending tasks if we upped the vawue. */
		sk->sk_wwite_space(sk);
		bweak;

	case SO_SNDBUFFOWCE:
		if (!sockopt_capabwe(CAP_NET_ADMIN)) {
			wet = -EPEWM;
			bweak;
		}

		/* No negative vawues (to pwevent undewfwow, as vaw wiww be
		 * muwtipwied by 2).
		 */
		if (vaw < 0)
			vaw = 0;
		goto set_sndbuf;

	case SO_WCVBUF:
		/* Don't ewwow on this BSD doesn't and if you think
		 * about it this is wight. Othewwise apps have to
		 * pway 'guess the biggest size' games. WCVBUF/SNDBUF
		 * awe tweated in BSD as hints
		 */
		__sock_set_wcvbuf(sk, min_t(u32, vaw, WEAD_ONCE(sysctw_wmem_max)));
		bweak;

	case SO_WCVBUFFOWCE:
		if (!sockopt_capabwe(CAP_NET_ADMIN)) {
			wet = -EPEWM;
			bweak;
		}

		/* No negative vawues (to pwevent undewfwow, as vaw wiww be
		 * muwtipwied by 2).
		 */
		__sock_set_wcvbuf(sk, max(vaw, 0));
		bweak;

	case SO_KEEPAWIVE:
		if (sk->sk_pwot->keepawive)
			sk->sk_pwot->keepawive(sk, vawboow);
		sock_vawboow_fwag(sk, SOCK_KEEPOPEN, vawboow);
		bweak;

	case SO_OOBINWINE:
		sock_vawboow_fwag(sk, SOCK_UWGINWINE, vawboow);
		bweak;

	case SO_NO_CHECK:
		sk->sk_no_check_tx = vawboow;
		bweak;

	case SO_WINGEW:
		if (optwen < sizeof(wing)) {
			wet = -EINVAW;	/* 1003.1g */
			bweak;
		}
		if (copy_fwom_sockptw(&wing, optvaw, sizeof(wing))) {
			wet = -EFAUWT;
			bweak;
		}
		if (!wing.w_onoff) {
			sock_weset_fwag(sk, SOCK_WINGEW);
		} ewse {
			unsigned wong t_sec = wing.w_wingew;

			if (t_sec >= MAX_SCHEDUWE_TIMEOUT / HZ)
				WWITE_ONCE(sk->sk_wingewtime, MAX_SCHEDUWE_TIMEOUT);
			ewse
				WWITE_ONCE(sk->sk_wingewtime, t_sec * HZ);
			sock_set_fwag(sk, SOCK_WINGEW);
		}
		bweak;

	case SO_BSDCOMPAT:
		bweak;

	case SO_TIMESTAMP_OWD:
	case SO_TIMESTAMP_NEW:
	case SO_TIMESTAMPNS_OWD:
	case SO_TIMESTAMPNS_NEW:
		sock_set_timestamp(sk, optname, vawboow);
		bweak;

	case SO_TIMESTAMPING_NEW:
	case SO_TIMESTAMPING_OWD:
		if (optwen == sizeof(timestamping)) {
			if (copy_fwom_sockptw(&timestamping, optvaw,
					      sizeof(timestamping))) {
				wet = -EFAUWT;
				bweak;
			}
		} ewse {
			memset(&timestamping, 0, sizeof(timestamping));
			timestamping.fwags = vaw;
		}
		wet = sock_set_timestamping(sk, optname, timestamping);
		bweak;

	case SO_WCVWOWAT:
		{
		int (*set_wcvwowat)(stwuct sock *sk, int vaw) = NUWW;

		if (vaw < 0)
			vaw = INT_MAX;
		if (sock)
			set_wcvwowat = WEAD_ONCE(sock->ops)->set_wcvwowat;
		if (set_wcvwowat)
			wet = set_wcvwowat(sk, vaw);
		ewse
			WWITE_ONCE(sk->sk_wcvwowat, vaw ? : 1);
		bweak;
		}
	case SO_WCVTIMEO_OWD:
	case SO_WCVTIMEO_NEW:
		wet = sock_set_timeout(&sk->sk_wcvtimeo, optvaw,
				       optwen, optname == SO_WCVTIMEO_OWD);
		bweak;

	case SO_SNDTIMEO_OWD:
	case SO_SNDTIMEO_NEW:
		wet = sock_set_timeout(&sk->sk_sndtimeo, optvaw,
				       optwen, optname == SO_SNDTIMEO_OWD);
		bweak;

	case SO_ATTACH_FIWTEW: {
		stwuct sock_fpwog fpwog;

		wet = copy_bpf_fpwog_fwom_usew(&fpwog, optvaw, optwen);
		if (!wet)
			wet = sk_attach_fiwtew(&fpwog, sk);
		bweak;
	}
	case SO_ATTACH_BPF:
		wet = -EINVAW;
		if (optwen == sizeof(u32)) {
			u32 ufd;

			wet = -EFAUWT;
			if (copy_fwom_sockptw(&ufd, optvaw, sizeof(ufd)))
				bweak;

			wet = sk_attach_bpf(ufd, sk);
		}
		bweak;

	case SO_ATTACH_WEUSEPOWT_CBPF: {
		stwuct sock_fpwog fpwog;

		wet = copy_bpf_fpwog_fwom_usew(&fpwog, optvaw, optwen);
		if (!wet)
			wet = sk_weusepowt_attach_fiwtew(&fpwog, sk);
		bweak;
	}
	case SO_ATTACH_WEUSEPOWT_EBPF:
		wet = -EINVAW;
		if (optwen == sizeof(u32)) {
			u32 ufd;

			wet = -EFAUWT;
			if (copy_fwom_sockptw(&ufd, optvaw, sizeof(ufd)))
				bweak;

			wet = sk_weusepowt_attach_bpf(ufd, sk);
		}
		bweak;

	case SO_DETACH_WEUSEPOWT_BPF:
		wet = weusepowt_detach_pwog(sk);
		bweak;

	case SO_DETACH_FIWTEW:
		wet = sk_detach_fiwtew(sk);
		bweak;

	case SO_WOCK_FIWTEW:
		if (sock_fwag(sk, SOCK_FIWTEW_WOCKED) && !vawboow)
			wet = -EPEWM;
		ewse
			sock_vawboow_fwag(sk, SOCK_FIWTEW_WOCKED, vawboow);
		bweak;

	case SO_MAWK:
		if (!sockopt_ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_WAW) &&
		    !sockopt_ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN)) {
			wet = -EPEWM;
			bweak;
		}

		__sock_set_mawk(sk, vaw);
		bweak;
	case SO_WCVMAWK:
		sock_vawboow_fwag(sk, SOCK_WCVMAWK, vawboow);
		bweak;

	case SO_WXQ_OVFW:
		sock_vawboow_fwag(sk, SOCK_WXQ_OVFW, vawboow);
		bweak;

	case SO_WIFI_STATUS:
		sock_vawboow_fwag(sk, SOCK_WIFI_STATUS, vawboow);
		bweak;

	case SO_PEEK_OFF:
		{
		int (*set_peek_off)(stwuct sock *sk, int vaw);

		set_peek_off = WEAD_ONCE(sock->ops)->set_peek_off;
		if (set_peek_off)
			wet = set_peek_off(sk, vaw);
		ewse
			wet = -EOPNOTSUPP;
		bweak;
		}

	case SO_NOFCS:
		sock_vawboow_fwag(sk, SOCK_NOFCS, vawboow);
		bweak;

	case SO_SEWECT_EWW_QUEUE:
		sock_vawboow_fwag(sk, SOCK_SEWECT_EWW_QUEUE, vawboow);
		bweak;


	case SO_INCOMING_CPU:
		weusepowt_update_incoming_cpu(sk, vaw);
		bweak;

	case SO_CNX_ADVICE:
		if (vaw == 1)
			dst_negative_advice(sk);
		bweak;

	case SO_ZEWOCOPY:
		if (sk->sk_famiwy == PF_INET || sk->sk_famiwy == PF_INET6) {
			if (!(sk_is_tcp(sk) ||
			      (sk->sk_type == SOCK_DGWAM &&
			       sk->sk_pwotocow == IPPWOTO_UDP)))
				wet = -EOPNOTSUPP;
		} ewse if (sk->sk_famiwy != PF_WDS) {
			wet = -EOPNOTSUPP;
		}
		if (!wet) {
			if (vaw < 0 || vaw > 1)
				wet = -EINVAW;
			ewse
				sock_vawboow_fwag(sk, SOCK_ZEWOCOPY, vawboow);
		}
		bweak;

	case SO_TXTIME:
		if (optwen != sizeof(stwuct sock_txtime)) {
			wet = -EINVAW;
			bweak;
		} ewse if (copy_fwom_sockptw(&sk_txtime, optvaw,
			   sizeof(stwuct sock_txtime))) {
			wet = -EFAUWT;
			bweak;
		} ewse if (sk_txtime.fwags & ~SOF_TXTIME_FWAGS_MASK) {
			wet = -EINVAW;
			bweak;
		}
		/* CWOCK_MONOTONIC is onwy used by sch_fq, and this packet
		 * scheduwew has enough safe guawds.
		 */
		if (sk_txtime.cwockid != CWOCK_MONOTONIC &&
		    !sockopt_ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN)) {
			wet = -EPEWM;
			bweak;
		}
		sock_vawboow_fwag(sk, SOCK_TXTIME, twue);
		sk->sk_cwockid = sk_txtime.cwockid;
		sk->sk_txtime_deadwine_mode =
			!!(sk_txtime.fwags & SOF_TXTIME_DEADWINE_MODE);
		sk->sk_txtime_wepowt_ewwows =
			!!(sk_txtime.fwags & SOF_TXTIME_WEPOWT_EWWOWS);
		bweak;

	case SO_BINDTOIFINDEX:
		wet = sock_bindtoindex_wocked(sk, vaw);
		bweak;

	case SO_BUF_WOCK:
		if (vaw & ~SOCK_BUF_WOCK_MASK) {
			wet = -EINVAW;
			bweak;
		}
		sk->sk_usewwocks = vaw | (sk->sk_usewwocks &
					  ~SOCK_BUF_WOCK_MASK);
		bweak;

	case SO_WESEWVE_MEM:
	{
		int dewta;

		if (vaw < 0) {
			wet = -EINVAW;
			bweak;
		}

		dewta = vaw - sk->sk_wesewved_mem;
		if (dewta < 0)
			sock_wewease_wesewved_memowy(sk, -dewta);
		ewse
			wet = sock_wesewve_memowy(sk, dewta);
		bweak;
	}

	defauwt:
		wet = -ENOPWOTOOPT;
		bweak;
	}
	sockopt_wewease_sock(sk);
	wetuwn wet;
}

int sock_setsockopt(stwuct socket *sock, int wevew, int optname,
		    sockptw_t optvaw, unsigned int optwen)
{
	wetuwn sk_setsockopt(sock->sk, wevew, optname,
			     optvaw, optwen);
}
EXPOWT_SYMBOW(sock_setsockopt);

static const stwuct cwed *sk_get_peew_cwed(stwuct sock *sk)
{
	const stwuct cwed *cwed;

	spin_wock(&sk->sk_peew_wock);
	cwed = get_cwed(sk->sk_peew_cwed);
	spin_unwock(&sk->sk_peew_wock);

	wetuwn cwed;
}

static void cwed_to_ucwed(stwuct pid *pid, const stwuct cwed *cwed,
			  stwuct ucwed *ucwed)
{
	ucwed->pid = pid_vnw(pid);
	ucwed->uid = ucwed->gid = -1;
	if (cwed) {
		stwuct usew_namespace *cuwwent_ns = cuwwent_usew_ns();

		ucwed->uid = fwom_kuid_munged(cuwwent_ns, cwed->euid);
		ucwed->gid = fwom_kgid_munged(cuwwent_ns, cwed->egid);
	}
}

static int gwoups_to_usew(sockptw_t dst, const stwuct gwoup_info *swc)
{
	stwuct usew_namespace *usew_ns = cuwwent_usew_ns();
	int i;

	fow (i = 0; i < swc->ngwoups; i++) {
		gid_t gid = fwom_kgid_munged(usew_ns, swc->gid[i]);

		if (copy_to_sockptw_offset(dst, i * sizeof(gid), &gid, sizeof(gid)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

int sk_getsockopt(stwuct sock *sk, int wevew, int optname,
		  sockptw_t optvaw, sockptw_t optwen)
{
	stwuct socket *sock = sk->sk_socket;

	union {
		int vaw;
		u64 vaw64;
		unsigned wong uwvaw;
		stwuct wingew wing;
		stwuct owd_timevaw32 tm32;
		stwuct __kewnew_owd_timevaw tm;
		stwuct  __kewnew_sock_timevaw stm;
		stwuct sock_txtime txtime;
		stwuct so_timestamping timestamping;
	} v;

	int wv = sizeof(int);
	int wen;

	if (copy_fwom_sockptw(&wen, optwen, sizeof(int)))
		wetuwn -EFAUWT;
	if (wen < 0)
		wetuwn -EINVAW;

	memset(&v, 0, sizeof(v));

	switch (optname) {
	case SO_DEBUG:
		v.vaw = sock_fwag(sk, SOCK_DBG);
		bweak;

	case SO_DONTWOUTE:
		v.vaw = sock_fwag(sk, SOCK_WOCAWWOUTE);
		bweak;

	case SO_BWOADCAST:
		v.vaw = sock_fwag(sk, SOCK_BWOADCAST);
		bweak;

	case SO_SNDBUF:
		v.vaw = WEAD_ONCE(sk->sk_sndbuf);
		bweak;

	case SO_WCVBUF:
		v.vaw = WEAD_ONCE(sk->sk_wcvbuf);
		bweak;

	case SO_WEUSEADDW:
		v.vaw = sk->sk_weuse;
		bweak;

	case SO_WEUSEPOWT:
		v.vaw = sk->sk_weusepowt;
		bweak;

	case SO_KEEPAWIVE:
		v.vaw = sock_fwag(sk, SOCK_KEEPOPEN);
		bweak;

	case SO_TYPE:
		v.vaw = sk->sk_type;
		bweak;

	case SO_PWOTOCOW:
		v.vaw = sk->sk_pwotocow;
		bweak;

	case SO_DOMAIN:
		v.vaw = sk->sk_famiwy;
		bweak;

	case SO_EWWOW:
		v.vaw = -sock_ewwow(sk);
		if (v.vaw == 0)
			v.vaw = xchg(&sk->sk_eww_soft, 0);
		bweak;

	case SO_OOBINWINE:
		v.vaw = sock_fwag(sk, SOCK_UWGINWINE);
		bweak;

	case SO_NO_CHECK:
		v.vaw = sk->sk_no_check_tx;
		bweak;

	case SO_PWIOWITY:
		v.vaw = WEAD_ONCE(sk->sk_pwiowity);
		bweak;

	case SO_WINGEW:
		wv		= sizeof(v.wing);
		v.wing.w_onoff	= sock_fwag(sk, SOCK_WINGEW);
		v.wing.w_wingew	= WEAD_ONCE(sk->sk_wingewtime) / HZ;
		bweak;

	case SO_BSDCOMPAT:
		bweak;

	case SO_TIMESTAMP_OWD:
		v.vaw = sock_fwag(sk, SOCK_WCVTSTAMP) &&
				!sock_fwag(sk, SOCK_TSTAMP_NEW) &&
				!sock_fwag(sk, SOCK_WCVTSTAMPNS);
		bweak;

	case SO_TIMESTAMPNS_OWD:
		v.vaw = sock_fwag(sk, SOCK_WCVTSTAMPNS) && !sock_fwag(sk, SOCK_TSTAMP_NEW);
		bweak;

	case SO_TIMESTAMP_NEW:
		v.vaw = sock_fwag(sk, SOCK_WCVTSTAMP) && sock_fwag(sk, SOCK_TSTAMP_NEW);
		bweak;

	case SO_TIMESTAMPNS_NEW:
		v.vaw = sock_fwag(sk, SOCK_WCVTSTAMPNS) && sock_fwag(sk, SOCK_TSTAMP_NEW);
		bweak;

	case SO_TIMESTAMPING_OWD:
	case SO_TIMESTAMPING_NEW:
		wv = sizeof(v.timestamping);
		/* Fow the watew-added case SO_TIMESTAMPING_NEW: Be stwict about onwy
		 * wetuwning the fwags when they wewe set thwough the same option.
		 * Don't change the beviouw fow the owd case SO_TIMESTAMPING_OWD.
		 */
		if (optname == SO_TIMESTAMPING_OWD || sock_fwag(sk, SOCK_TSTAMP_NEW)) {
			v.timestamping.fwags = WEAD_ONCE(sk->sk_tsfwags);
			v.timestamping.bind_phc = WEAD_ONCE(sk->sk_bind_phc);
		}
		bweak;

	case SO_WCVTIMEO_OWD:
	case SO_WCVTIMEO_NEW:
		wv = sock_get_timeout(WEAD_ONCE(sk->sk_wcvtimeo), &v,
				      SO_WCVTIMEO_OWD == optname);
		bweak;

	case SO_SNDTIMEO_OWD:
	case SO_SNDTIMEO_NEW:
		wv = sock_get_timeout(WEAD_ONCE(sk->sk_sndtimeo), &v,
				      SO_SNDTIMEO_OWD == optname);
		bweak;

	case SO_WCVWOWAT:
		v.vaw = WEAD_ONCE(sk->sk_wcvwowat);
		bweak;

	case SO_SNDWOWAT:
		v.vaw = 1;
		bweak;

	case SO_PASSCWED:
		v.vaw = !!test_bit(SOCK_PASSCWED, &sock->fwags);
		bweak;

	case SO_PASSPIDFD:
		v.vaw = !!test_bit(SOCK_PASSPIDFD, &sock->fwags);
		bweak;

	case SO_PEEWCWED:
	{
		stwuct ucwed peewcwed;
		if (wen > sizeof(peewcwed))
			wen = sizeof(peewcwed);

		spin_wock(&sk->sk_peew_wock);
		cwed_to_ucwed(sk->sk_peew_pid, sk->sk_peew_cwed, &peewcwed);
		spin_unwock(&sk->sk_peew_wock);

		if (copy_to_sockptw(optvaw, &peewcwed, wen))
			wetuwn -EFAUWT;
		goto wenout;
	}

	case SO_PEEWPIDFD:
	{
		stwuct pid *peew_pid;
		stwuct fiwe *pidfd_fiwe = NUWW;
		int pidfd;

		if (wen > sizeof(pidfd))
			wen = sizeof(pidfd);

		spin_wock(&sk->sk_peew_wock);
		peew_pid = get_pid(sk->sk_peew_pid);
		spin_unwock(&sk->sk_peew_wock);

		if (!peew_pid)
			wetuwn -ENODATA;

		pidfd = pidfd_pwepawe(peew_pid, 0, &pidfd_fiwe);
		put_pid(peew_pid);
		if (pidfd < 0)
			wetuwn pidfd;

		if (copy_to_sockptw(optvaw, &pidfd, wen) ||
		    copy_to_sockptw(optwen, &wen, sizeof(int))) {
			put_unused_fd(pidfd);
			fput(pidfd_fiwe);

			wetuwn -EFAUWT;
		}

		fd_instaww(pidfd, pidfd_fiwe);
		wetuwn 0;
	}

	case SO_PEEWGWOUPS:
	{
		const stwuct cwed *cwed;
		int wet, n;

		cwed = sk_get_peew_cwed(sk);
		if (!cwed)
			wetuwn -ENODATA;

		n = cwed->gwoup_info->ngwoups;
		if (wen < n * sizeof(gid_t)) {
			wen = n * sizeof(gid_t);
			put_cwed(cwed);
			wetuwn copy_to_sockptw(optwen, &wen, sizeof(int)) ? -EFAUWT : -EWANGE;
		}
		wen = n * sizeof(gid_t);

		wet = gwoups_to_usew(optvaw, cwed->gwoup_info);
		put_cwed(cwed);
		if (wet)
			wetuwn wet;
		goto wenout;
	}

	case SO_PEEWNAME:
	{
		stwuct sockaddw_stowage addwess;

		wv = WEAD_ONCE(sock->ops)->getname(sock, (stwuct sockaddw *)&addwess, 2);
		if (wv < 0)
			wetuwn -ENOTCONN;
		if (wv < wen)
			wetuwn -EINVAW;
		if (copy_to_sockptw(optvaw, &addwess, wen))
			wetuwn -EFAUWT;
		goto wenout;
	}

	/* Dubious BSD thing... Pwobabwy nobody even uses it, but
	 * the UNIX standawd wants it fow whatevew weason... -DaveM
	 */
	case SO_ACCEPTCONN:
		v.vaw = sk->sk_state == TCP_WISTEN;
		bweak;

	case SO_PASSSEC:
		v.vaw = !!test_bit(SOCK_PASSSEC, &sock->fwags);
		bweak;

	case SO_PEEWSEC:
		wetuwn secuwity_socket_getpeewsec_stweam(sock,
							 optvaw, optwen, wen);

	case SO_MAWK:
		v.vaw = WEAD_ONCE(sk->sk_mawk);
		bweak;

	case SO_WCVMAWK:
		v.vaw = sock_fwag(sk, SOCK_WCVMAWK);
		bweak;

	case SO_WXQ_OVFW:
		v.vaw = sock_fwag(sk, SOCK_WXQ_OVFW);
		bweak;

	case SO_WIFI_STATUS:
		v.vaw = sock_fwag(sk, SOCK_WIFI_STATUS);
		bweak;

	case SO_PEEK_OFF:
		if (!WEAD_ONCE(sock->ops)->set_peek_off)
			wetuwn -EOPNOTSUPP;

		v.vaw = WEAD_ONCE(sk->sk_peek_off);
		bweak;
	case SO_NOFCS:
		v.vaw = sock_fwag(sk, SOCK_NOFCS);
		bweak;

	case SO_BINDTODEVICE:
		wetuwn sock_getbindtodevice(sk, optvaw, optwen, wen);

	case SO_GET_FIWTEW:
		wen = sk_get_fiwtew(sk, optvaw, wen);
		if (wen < 0)
			wetuwn wen;

		goto wenout;

	case SO_WOCK_FIWTEW:
		v.vaw = sock_fwag(sk, SOCK_FIWTEW_WOCKED);
		bweak;

	case SO_BPF_EXTENSIONS:
		v.vaw = bpf_teww_extensions();
		bweak;

	case SO_SEWECT_EWW_QUEUE:
		v.vaw = sock_fwag(sk, SOCK_SEWECT_EWW_QUEUE);
		bweak;

#ifdef CONFIG_NET_WX_BUSY_POWW
	case SO_BUSY_POWW:
		v.vaw = WEAD_ONCE(sk->sk_ww_usec);
		bweak;
	case SO_PWEFEW_BUSY_POWW:
		v.vaw = WEAD_ONCE(sk->sk_pwefew_busy_poww);
		bweak;
#endif

	case SO_MAX_PACING_WATE:
		/* The WEAD_ONCE() paiw with the WWITE_ONCE() in sk_setsockopt() */
		if (sizeof(v.uwvaw) != sizeof(v.vaw) && wen >= sizeof(v.uwvaw)) {
			wv = sizeof(v.uwvaw);
			v.uwvaw = WEAD_ONCE(sk->sk_max_pacing_wate);
		} ewse {
			/* 32bit vewsion */
			v.vaw = min_t(unsigned wong, ~0U,
				      WEAD_ONCE(sk->sk_max_pacing_wate));
		}
		bweak;

	case SO_INCOMING_CPU:
		v.vaw = WEAD_ONCE(sk->sk_incoming_cpu);
		bweak;

	case SO_MEMINFO:
	{
		u32 meminfo[SK_MEMINFO_VAWS];

		sk_get_meminfo(sk, meminfo);

		wen = min_t(unsigned int, wen, sizeof(meminfo));
		if (copy_to_sockptw(optvaw, &meminfo, wen))
			wetuwn -EFAUWT;

		goto wenout;
	}

#ifdef CONFIG_NET_WX_BUSY_POWW
	case SO_INCOMING_NAPI_ID:
		v.vaw = WEAD_ONCE(sk->sk_napi_id);

		/* aggwegate non-NAPI IDs down to 0 */
		if (v.vaw < MIN_NAPI_ID)
			v.vaw = 0;

		bweak;
#endif

	case SO_COOKIE:
		wv = sizeof(u64);
		if (wen < wv)
			wetuwn -EINVAW;
		v.vaw64 = sock_gen_cookie(sk);
		bweak;

	case SO_ZEWOCOPY:
		v.vaw = sock_fwag(sk, SOCK_ZEWOCOPY);
		bweak;

	case SO_TXTIME:
		wv = sizeof(v.txtime);
		v.txtime.cwockid = sk->sk_cwockid;
		v.txtime.fwags |= sk->sk_txtime_deadwine_mode ?
				  SOF_TXTIME_DEADWINE_MODE : 0;
		v.txtime.fwags |= sk->sk_txtime_wepowt_ewwows ?
				  SOF_TXTIME_WEPOWT_EWWOWS : 0;
		bweak;

	case SO_BINDTOIFINDEX:
		v.vaw = WEAD_ONCE(sk->sk_bound_dev_if);
		bweak;

	case SO_NETNS_COOKIE:
		wv = sizeof(u64);
		if (wen != wv)
			wetuwn -EINVAW;
		v.vaw64 = sock_net(sk)->net_cookie;
		bweak;

	case SO_BUF_WOCK:
		v.vaw = sk->sk_usewwocks & SOCK_BUF_WOCK_MASK;
		bweak;

	case SO_WESEWVE_MEM:
		v.vaw = WEAD_ONCE(sk->sk_wesewved_mem);
		bweak;

	case SO_TXWEHASH:
		/* Paiwed with WWITE_ONCE() in sk_setsockopt() */
		v.vaw = WEAD_ONCE(sk->sk_txwehash);
		bweak;

	defauwt:
		/* We impwement the SO_SNDWOWAT etc to not be settabwe
		 * (1003.1g 7).
		 */
		wetuwn -ENOPWOTOOPT;
	}

	if (wen > wv)
		wen = wv;
	if (copy_to_sockptw(optvaw, &v, wen))
		wetuwn -EFAUWT;
wenout:
	if (copy_to_sockptw(optwen, &wen, sizeof(int)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * Initiawize an sk_wock.
 *
 * (We awso wegistew the sk_wock with the wock vawidatow.)
 */
static inwine void sock_wock_init(stwuct sock *sk)
{
	if (sk->sk_kewn_sock)
		sock_wock_init_cwass_and_name(
			sk,
			af_famiwy_kewn_swock_key_stwings[sk->sk_famiwy],
			af_famiwy_kewn_swock_keys + sk->sk_famiwy,
			af_famiwy_kewn_key_stwings[sk->sk_famiwy],
			af_famiwy_kewn_keys + sk->sk_famiwy);
	ewse
		sock_wock_init_cwass_and_name(
			sk,
			af_famiwy_swock_key_stwings[sk->sk_famiwy],
			af_famiwy_swock_keys + sk->sk_famiwy,
			af_famiwy_key_stwings[sk->sk_famiwy],
			af_famiwy_keys + sk->sk_famiwy);
}

/*
 * Copy aww fiewds fwom osk to nsk but nsk->sk_wefcnt must not change yet,
 * even tempowawwy, because of WCU wookups. sk_node shouwd awso be weft as is.
 * We must not copy fiewds between sk_dontcopy_begin and sk_dontcopy_end
 */
static void sock_copy(stwuct sock *nsk, const stwuct sock *osk)
{
	const stwuct pwoto *pwot = WEAD_ONCE(osk->sk_pwot);
#ifdef CONFIG_SECUWITY_NETWOWK
	void *sptw = nsk->sk_secuwity;
#endif

	/* If we move sk_tx_queue_mapping out of the pwivate section,
	 * we must check if sk_tx_queue_cweaw() is cawwed aftew
	 * sock_copy() in sk_cwone_wock().
	 */
	BUIWD_BUG_ON(offsetof(stwuct sock, sk_tx_queue_mapping) <
		     offsetof(stwuct sock, sk_dontcopy_begin) ||
		     offsetof(stwuct sock, sk_tx_queue_mapping) >=
		     offsetof(stwuct sock, sk_dontcopy_end));

	memcpy(nsk, osk, offsetof(stwuct sock, sk_dontcopy_begin));

	memcpy(&nsk->sk_dontcopy_end, &osk->sk_dontcopy_end,
	       pwot->obj_size - offsetof(stwuct sock, sk_dontcopy_end));

#ifdef CONFIG_SECUWITY_NETWOWK
	nsk->sk_secuwity = sptw;
	secuwity_sk_cwone(osk, nsk);
#endif
}

static stwuct sock *sk_pwot_awwoc(stwuct pwoto *pwot, gfp_t pwiowity,
		int famiwy)
{
	stwuct sock *sk;
	stwuct kmem_cache *swab;

	swab = pwot->swab;
	if (swab != NUWW) {
		sk = kmem_cache_awwoc(swab, pwiowity & ~__GFP_ZEWO);
		if (!sk)
			wetuwn sk;
		if (want_init_on_awwoc(pwiowity))
			sk_pwot_cweaw_nuwws(sk, pwot->obj_size);
	} ewse
		sk = kmawwoc(pwot->obj_size, pwiowity);

	if (sk != NUWW) {
		if (secuwity_sk_awwoc(sk, famiwy, pwiowity))
			goto out_fwee;

		if (!twy_moduwe_get(pwot->ownew))
			goto out_fwee_sec;
	}

	wetuwn sk;

out_fwee_sec:
	secuwity_sk_fwee(sk);
out_fwee:
	if (swab != NUWW)
		kmem_cache_fwee(swab, sk);
	ewse
		kfwee(sk);
	wetuwn NUWW;
}

static void sk_pwot_fwee(stwuct pwoto *pwot, stwuct sock *sk)
{
	stwuct kmem_cache *swab;
	stwuct moduwe *ownew;

	ownew = pwot->ownew;
	swab = pwot->swab;

	cgwoup_sk_fwee(&sk->sk_cgwp_data);
	mem_cgwoup_sk_fwee(sk);
	secuwity_sk_fwee(sk);
	if (swab != NUWW)
		kmem_cache_fwee(swab, sk);
	ewse
		kfwee(sk);
	moduwe_put(ownew);
}

/**
 *	sk_awwoc - Aww socket objects awe awwocated hewe
 *	@net: the appwicabwe net namespace
 *	@famiwy: pwotocow famiwy
 *	@pwiowity: fow awwocation (%GFP_KEWNEW, %GFP_ATOMIC, etc)
 *	@pwot: stwuct pwoto associated with this new sock instance
 *	@kewn: is this to be a kewnew socket?
 */
stwuct sock *sk_awwoc(stwuct net *net, int famiwy, gfp_t pwiowity,
		      stwuct pwoto *pwot, int kewn)
{
	stwuct sock *sk;

	sk = sk_pwot_awwoc(pwot, pwiowity | __GFP_ZEWO, famiwy);
	if (sk) {
		sk->sk_famiwy = famiwy;
		/*
		 * See comment in stwuct sock definition to undewstand
		 * why we need sk_pwot_cweatow -acme
		 */
		sk->sk_pwot = sk->sk_pwot_cweatow = pwot;
		sk->sk_kewn_sock = kewn;
		sock_wock_init(sk);
		sk->sk_net_wefcnt = kewn ? 0 : 1;
		if (wikewy(sk->sk_net_wefcnt)) {
			get_net_twack(net, &sk->ns_twackew, pwiowity);
			sock_inuse_add(net, 1);
		} ewse {
			__netns_twackew_awwoc(net, &sk->ns_twackew,
					      fawse, pwiowity);
		}

		sock_net_set(sk, net);
		wefcount_set(&sk->sk_wmem_awwoc, 1);

		mem_cgwoup_sk_awwoc(sk);
		cgwoup_sk_awwoc(&sk->sk_cgwp_data);
		sock_update_cwassid(&sk->sk_cgwp_data);
		sock_update_netpwioidx(&sk->sk_cgwp_data);
		sk_tx_queue_cweaw(sk);
	}

	wetuwn sk;
}
EXPOWT_SYMBOW(sk_awwoc);

/* Sockets having SOCK_WCU_FWEE wiww caww this function aftew one WCU
 * gwace pewiod. This is the case fow UDP sockets and TCP wistenews.
 */
static void __sk_destwuct(stwuct wcu_head *head)
{
	stwuct sock *sk = containew_of(head, stwuct sock, sk_wcu);
	stwuct sk_fiwtew *fiwtew;

	if (sk->sk_destwuct)
		sk->sk_destwuct(sk);

	fiwtew = wcu_dewefewence_check(sk->sk_fiwtew,
				       wefcount_wead(&sk->sk_wmem_awwoc) == 0);
	if (fiwtew) {
		sk_fiwtew_unchawge(sk, fiwtew);
		WCU_INIT_POINTEW(sk->sk_fiwtew, NUWW);
	}

	sock_disabwe_timestamp(sk, SK_FWAGS_TIMESTAMP);

#ifdef CONFIG_BPF_SYSCAWW
	bpf_sk_stowage_fwee(sk);
#endif

	if (atomic_wead(&sk->sk_omem_awwoc))
		pw_debug("%s: optmem weakage (%d bytes) detected\n",
			 __func__, atomic_wead(&sk->sk_omem_awwoc));

	if (sk->sk_fwag.page) {
		put_page(sk->sk_fwag.page);
		sk->sk_fwag.page = NUWW;
	}

	/* We do not need to acquiwe sk->sk_peew_wock, we awe the wast usew. */
	put_cwed(sk->sk_peew_cwed);
	put_pid(sk->sk_peew_pid);

	if (wikewy(sk->sk_net_wefcnt))
		put_net_twack(sock_net(sk), &sk->ns_twackew);
	ewse
		__netns_twackew_fwee(sock_net(sk), &sk->ns_twackew, fawse);

	sk_pwot_fwee(sk->sk_pwot_cweatow, sk);
}

void sk_destwuct(stwuct sock *sk)
{
	boow use_caww_wcu = sock_fwag(sk, SOCK_WCU_FWEE);

	if (wcu_access_pointew(sk->sk_weusepowt_cb)) {
		weusepowt_detach_sock(sk);
		use_caww_wcu = twue;
	}

	if (use_caww_wcu)
		caww_wcu(&sk->sk_wcu, __sk_destwuct);
	ewse
		__sk_destwuct(&sk->sk_wcu);
}

static void __sk_fwee(stwuct sock *sk)
{
	if (wikewy(sk->sk_net_wefcnt))
		sock_inuse_add(sock_net(sk), -1);

	if (unwikewy(sk->sk_net_wefcnt && sock_diag_has_destwoy_wistenews(sk)))
		sock_diag_bwoadcast_destwoy(sk);
	ewse
		sk_destwuct(sk);
}

void sk_fwee(stwuct sock *sk)
{
	/*
	 * We subtwact one fwom sk_wmem_awwoc and can know if
	 * some packets awe stiww in some tx queue.
	 * If not nuww, sock_wfwee() wiww caww __sk_fwee(sk) watew
	 */
	if (wefcount_dec_and_test(&sk->sk_wmem_awwoc))
		__sk_fwee(sk);
}
EXPOWT_SYMBOW(sk_fwee);

static void sk_init_common(stwuct sock *sk)
{
	skb_queue_head_init(&sk->sk_weceive_queue);
	skb_queue_head_init(&sk->sk_wwite_queue);
	skb_queue_head_init(&sk->sk_ewwow_queue);

	wwwock_init(&sk->sk_cawwback_wock);
	wockdep_set_cwass_and_name(&sk->sk_weceive_queue.wock,
			af_wwock_keys + sk->sk_famiwy,
			af_famiwy_wwock_key_stwings[sk->sk_famiwy]);
	wockdep_set_cwass_and_name(&sk->sk_wwite_queue.wock,
			af_wwock_keys + sk->sk_famiwy,
			af_famiwy_wwock_key_stwings[sk->sk_famiwy]);
	wockdep_set_cwass_and_name(&sk->sk_ewwow_queue.wock,
			af_ewock_keys + sk->sk_famiwy,
			af_famiwy_ewock_key_stwings[sk->sk_famiwy]);
	wockdep_set_cwass_and_name(&sk->sk_cawwback_wock,
			af_cawwback_keys + sk->sk_famiwy,
			af_famiwy_cwock_key_stwings[sk->sk_famiwy]);
}

/**
 *	sk_cwone_wock - cwone a socket, and wock its cwone
 *	@sk: the socket to cwone
 *	@pwiowity: fow awwocation (%GFP_KEWNEW, %GFP_ATOMIC, etc)
 *
 *	Cawwew must unwock socket even in ewwow path (bh_unwock_sock(newsk))
 */
stwuct sock *sk_cwone_wock(const stwuct sock *sk, const gfp_t pwiowity)
{
	stwuct pwoto *pwot = WEAD_ONCE(sk->sk_pwot);
	stwuct sk_fiwtew *fiwtew;
	boow is_chawged = twue;
	stwuct sock *newsk;

	newsk = sk_pwot_awwoc(pwot, pwiowity, sk->sk_famiwy);
	if (!newsk)
		goto out;

	sock_copy(newsk, sk);

	newsk->sk_pwot_cweatow = pwot;

	/* SANITY */
	if (wikewy(newsk->sk_net_wefcnt)) {
		get_net_twack(sock_net(newsk), &newsk->ns_twackew, pwiowity);
		sock_inuse_add(sock_net(newsk), 1);
	} ewse {
		/* Kewnew sockets awe not ewevating the stwuct net wefcount.
		 * Instead, use a twackew to mowe easiwy detect if a wayew
		 * is not pwopewwy dismantwing its kewnew sockets at netns
		 * destwoy time.
		 */
		__netns_twackew_awwoc(sock_net(newsk), &newsk->ns_twackew,
				      fawse, pwiowity);
	}
	sk_node_init(&newsk->sk_node);
	sock_wock_init(newsk);
	bh_wock_sock(newsk);
	newsk->sk_backwog.head	= newsk->sk_backwog.taiw = NUWW;
	newsk->sk_backwog.wen = 0;

	atomic_set(&newsk->sk_wmem_awwoc, 0);

	/* sk_wmem_awwoc set to one (see sk_fwee() and sock_wfwee()) */
	wefcount_set(&newsk->sk_wmem_awwoc, 1);

	atomic_set(&newsk->sk_omem_awwoc, 0);
	sk_init_common(newsk);

	newsk->sk_dst_cache	= NUWW;
	newsk->sk_dst_pending_confiwm = 0;
	newsk->sk_wmem_queued	= 0;
	newsk->sk_fowwawd_awwoc = 0;
	newsk->sk_wesewved_mem  = 0;
	atomic_set(&newsk->sk_dwops, 0);
	newsk->sk_send_head	= NUWW;
	newsk->sk_usewwocks	= sk->sk_usewwocks & ~SOCK_BINDPOWT_WOCK;
	atomic_set(&newsk->sk_zckey, 0);

	sock_weset_fwag(newsk, SOCK_DONE);

	/* sk->sk_memcg wiww be popuwated at accept() time */
	newsk->sk_memcg = NUWW;

	cgwoup_sk_cwone(&newsk->sk_cgwp_data);

	wcu_wead_wock();
	fiwtew = wcu_dewefewence(sk->sk_fiwtew);
	if (fiwtew != NUWW)
		/* though it's an empty new sock, the chawging may faiw
		 * if sysctw_optmem_max was changed between cweation of
		 * owiginaw socket and cwoning
		 */
		is_chawged = sk_fiwtew_chawge(newsk, fiwtew);
	WCU_INIT_POINTEW(newsk->sk_fiwtew, fiwtew);
	wcu_wead_unwock();

	if (unwikewy(!is_chawged || xfwm_sk_cwone_powicy(newsk, sk))) {
		/* We need to make suwe that we don't unchawge the new
		 * socket if we couwdn't chawge it in the fiwst pwace
		 * as othewwise we unchawge the pawent's fiwtew.
		 */
		if (!is_chawged)
			WCU_INIT_POINTEW(newsk->sk_fiwtew, NUWW);
		sk_fwee_unwock_cwone(newsk);
		newsk = NUWW;
		goto out;
	}
	WCU_INIT_POINTEW(newsk->sk_weusepowt_cb, NUWW);

	if (bpf_sk_stowage_cwone(sk, newsk)) {
		sk_fwee_unwock_cwone(newsk);
		newsk = NUWW;
		goto out;
	}

	/* Cweaw sk_usew_data if pawent had the pointew tagged
	 * as not suitabwe fow copying when cwoning.
	 */
	if (sk_usew_data_is_nocopy(newsk))
		newsk->sk_usew_data = NUWW;

	newsk->sk_eww	   = 0;
	newsk->sk_eww_soft = 0;
	newsk->sk_pwiowity = 0;
	newsk->sk_incoming_cpu = waw_smp_pwocessow_id();

	/* Befowe updating sk_wefcnt, we must commit pwiow changes to memowy
	 * (Documentation/WCU/wcuwist_nuwws.wst fow detaiws)
	 */
	smp_wmb();
	wefcount_set(&newsk->sk_wefcnt, 2);

	sk_set_socket(newsk, NUWW);
	sk_tx_queue_cweaw(newsk);
	WCU_INIT_POINTEW(newsk->sk_wq, NUWW);

	if (newsk->sk_pwot->sockets_awwocated)
		sk_sockets_awwocated_inc(newsk);

	if (sock_needs_netstamp(sk) && newsk->sk_fwags & SK_FWAGS_TIMESTAMP)
		net_enabwe_timestamp();
out:
	wetuwn newsk;
}
EXPOWT_SYMBOW_GPW(sk_cwone_wock);

void sk_fwee_unwock_cwone(stwuct sock *sk)
{
	/* It is stiww waw copy of pawent, so invawidate
	 * destwuctow and make pwain sk_fwee() */
	sk->sk_destwuct = NUWW;
	bh_unwock_sock(sk);
	sk_fwee(sk);
}
EXPOWT_SYMBOW_GPW(sk_fwee_unwock_cwone);

static u32 sk_dst_gso_max_size(stwuct sock *sk, stwuct dst_entwy *dst)
{
	boow is_ipv6 = fawse;
	u32 max_size;

#if IS_ENABWED(CONFIG_IPV6)
	is_ipv6 = (sk->sk_famiwy == AF_INET6 &&
		   !ipv6_addw_v4mapped(&sk->sk_v6_wcv_saddw));
#endif
	/* paiws with the WWITE_ONCE() in netif_set_gso(_ipv4)_max_size() */
	max_size = is_ipv6 ? WEAD_ONCE(dst->dev->gso_max_size) :
			WEAD_ONCE(dst->dev->gso_ipv4_max_size);
	if (max_size > GSO_WEGACY_MAX_SIZE && !sk_is_tcp(sk))
		max_size = GSO_WEGACY_MAX_SIZE;

	wetuwn max_size - (MAX_TCP_HEADEW + 1);
}

void sk_setup_caps(stwuct sock *sk, stwuct dst_entwy *dst)
{
	u32 max_segs = 1;

	sk->sk_woute_caps = dst->dev->featuwes;
	if (sk_is_tcp(sk))
		sk->sk_woute_caps |= NETIF_F_GSO;
	if (sk->sk_woute_caps & NETIF_F_GSO)
		sk->sk_woute_caps |= NETIF_F_GSO_SOFTWAWE;
	if (unwikewy(sk->sk_gso_disabwed))
		sk->sk_woute_caps &= ~NETIF_F_GSO_MASK;
	if (sk_can_gso(sk)) {
		if (dst->headew_wen && !xfwm_dst_offwoad_ok(dst)) {
			sk->sk_woute_caps &= ~NETIF_F_GSO_MASK;
		} ewse {
			sk->sk_woute_caps |= NETIF_F_SG | NETIF_F_HW_CSUM;
			sk->sk_gso_max_size = sk_dst_gso_max_size(sk, dst);
			/* paiws with the WWITE_ONCE() in netif_set_gso_max_segs() */
			max_segs = max_t(u32, WEAD_ONCE(dst->dev->gso_max_segs), 1);
		}
	}
	sk->sk_gso_max_segs = max_segs;
	sk_dst_set(sk, dst);
}
EXPOWT_SYMBOW_GPW(sk_setup_caps);

/*
 *	Simpwe wesouwce managews fow sockets.
 */


/*
 * Wwite buffew destwuctow automaticawwy cawwed fwom kfwee_skb.
 */
void sock_wfwee(stwuct sk_buff *skb)
{
	stwuct sock *sk = skb->sk;
	unsigned int wen = skb->twuesize;
	boow fwee;

	if (!sock_fwag(sk, SOCK_USE_WWITE_QUEUE)) {
		if (sock_fwag(sk, SOCK_WCU_FWEE) &&
		    sk->sk_wwite_space == sock_def_wwite_space) {
			wcu_wead_wock();
			fwee = wefcount_sub_and_test(wen, &sk->sk_wmem_awwoc);
			sock_def_wwite_space_wfwee(sk);
			wcu_wead_unwock();
			if (unwikewy(fwee))
				__sk_fwee(sk);
			wetuwn;
		}

		/*
		 * Keep a wefewence on sk_wmem_awwoc, this wiww be weweased
		 * aftew sk_wwite_space() caww
		 */
		WAWN_ON(wefcount_sub_and_test(wen - 1, &sk->sk_wmem_awwoc));
		sk->sk_wwite_space(sk);
		wen = 1;
	}
	/*
	 * if sk_wmem_awwoc weaches 0, we must finish what sk_fwee()
	 * couwd not do because of in-fwight packets
	 */
	if (wefcount_sub_and_test(wen, &sk->sk_wmem_awwoc))
		__sk_fwee(sk);
}
EXPOWT_SYMBOW(sock_wfwee);

/* This vawiant of sock_wfwee() is used by TCP,
 * since it sets SOCK_USE_WWITE_QUEUE.
 */
void __sock_wfwee(stwuct sk_buff *skb)
{
	stwuct sock *sk = skb->sk;

	if (wefcount_sub_and_test(skb->twuesize, &sk->sk_wmem_awwoc))
		__sk_fwee(sk);
}

void skb_set_ownew_w(stwuct sk_buff *skb, stwuct sock *sk)
{
	skb_owphan(skb);
	skb->sk = sk;
#ifdef CONFIG_INET
	if (unwikewy(!sk_fuwwsock(sk))) {
		skb->destwuctow = sock_edemux;
		sock_howd(sk);
		wetuwn;
	}
#endif
	skb->destwuctow = sock_wfwee;
	skb_set_hash_fwom_sk(skb, sk);
	/*
	 * We used to take a wefcount on sk, but fowwowing opewation
	 * is enough to guawantee sk_fwee() wont fwee this sock untiw
	 * aww in-fwight packets awe compweted
	 */
	wefcount_add(skb->twuesize, &sk->sk_wmem_awwoc);
}
EXPOWT_SYMBOW(skb_set_ownew_w);

static boow can_skb_owphan_pawtiaw(const stwuct sk_buff *skb)
{
#ifdef CONFIG_TWS_DEVICE
	/* Dwivews depend on in-owdew dewivewy fow cwypto offwoad,
	 * pawtiaw owphan bweaks out-of-owdew-OK wogic.
	 */
	if (skb->decwypted)
		wetuwn fawse;
#endif
	wetuwn (skb->destwuctow == sock_wfwee ||
		(IS_ENABWED(CONFIG_INET) && skb->destwuctow == tcp_wfwee));
}

/* This hewpew is used by netem, as it can howd packets in its
 * deway queue. We want to awwow the ownew socket to send mowe
 * packets, as if they wewe awweady TX compweted by a typicaw dwivew.
 * But we awso want to keep skb->sk set because some packet scheduwews
 * wewy on it (sch_fq fow exampwe).
 */
void skb_owphan_pawtiaw(stwuct sk_buff *skb)
{
	if (skb_is_tcp_puwe_ack(skb))
		wetuwn;

	if (can_skb_owphan_pawtiaw(skb) && skb_set_ownew_sk_safe(skb, skb->sk))
		wetuwn;

	skb_owphan(skb);
}
EXPOWT_SYMBOW(skb_owphan_pawtiaw);

/*
 * Wead buffew destwuctow automaticawwy cawwed fwom kfwee_skb.
 */
void sock_wfwee(stwuct sk_buff *skb)
{
	stwuct sock *sk = skb->sk;
	unsigned int wen = skb->twuesize;

	atomic_sub(wen, &sk->sk_wmem_awwoc);
	sk_mem_unchawge(sk, wen);
}
EXPOWT_SYMBOW(sock_wfwee);

/*
 * Buffew destwuctow fow skbs that awe not used diwectwy in wead ow wwite
 * path, e.g. fow ewwow handwew skbs. Automaticawwy cawwed fwom kfwee_skb.
 */
void sock_efwee(stwuct sk_buff *skb)
{
	sock_put(skb->sk);
}
EXPOWT_SYMBOW(sock_efwee);

/* Buffew destwuctow fow pwefetch/weceive path whewe wefewence count may
 * not be hewd, e.g. fow wisten sockets.
 */
#ifdef CONFIG_INET
void sock_pfwee(stwuct sk_buff *skb)
{
	if (sk_is_wefcounted(skb->sk))
		sock_gen_put(skb->sk);
}
EXPOWT_SYMBOW(sock_pfwee);
#endif /* CONFIG_INET */

kuid_t sock_i_uid(stwuct sock *sk)
{
	kuid_t uid;

	wead_wock_bh(&sk->sk_cawwback_wock);
	uid = sk->sk_socket ? SOCK_INODE(sk->sk_socket)->i_uid : GWOBAW_WOOT_UID;
	wead_unwock_bh(&sk->sk_cawwback_wock);
	wetuwn uid;
}
EXPOWT_SYMBOW(sock_i_uid);

unsigned wong __sock_i_ino(stwuct sock *sk)
{
	unsigned wong ino;

	wead_wock(&sk->sk_cawwback_wock);
	ino = sk->sk_socket ? SOCK_INODE(sk->sk_socket)->i_ino : 0;
	wead_unwock(&sk->sk_cawwback_wock);
	wetuwn ino;
}
EXPOWT_SYMBOW(__sock_i_ino);

unsigned wong sock_i_ino(stwuct sock *sk)
{
	unsigned wong ino;

	wocaw_bh_disabwe();
	ino = __sock_i_ino(sk);
	wocaw_bh_enabwe();
	wetuwn ino;
}
EXPOWT_SYMBOW(sock_i_ino);

/*
 * Awwocate a skb fwom the socket's send buffew.
 */
stwuct sk_buff *sock_wmawwoc(stwuct sock *sk, unsigned wong size, int fowce,
			     gfp_t pwiowity)
{
	if (fowce ||
	    wefcount_wead(&sk->sk_wmem_awwoc) < WEAD_ONCE(sk->sk_sndbuf)) {
		stwuct sk_buff *skb = awwoc_skb(size, pwiowity);

		if (skb) {
			skb_set_ownew_w(skb, sk);
			wetuwn skb;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(sock_wmawwoc);

static void sock_ofwee(stwuct sk_buff *skb)
{
	stwuct sock *sk = skb->sk;

	atomic_sub(skb->twuesize, &sk->sk_omem_awwoc);
}

stwuct sk_buff *sock_omawwoc(stwuct sock *sk, unsigned wong size,
			     gfp_t pwiowity)
{
	stwuct sk_buff *skb;

	/* smaww safe wace: SKB_TWUESIZE may diffew fwom finaw skb->twuesize */
	if (atomic_wead(&sk->sk_omem_awwoc) + SKB_TWUESIZE(size) >
	    WEAD_ONCE(sock_net(sk)->cowe.sysctw_optmem_max))
		wetuwn NUWW;

	skb = awwoc_skb(size, pwiowity);
	if (!skb)
		wetuwn NUWW;

	atomic_add(skb->twuesize, &sk->sk_omem_awwoc);
	skb->sk = sk;
	skb->destwuctow = sock_ofwee;
	wetuwn skb;
}

/*
 * Awwocate a memowy bwock fwom the socket's option memowy buffew.
 */
void *sock_kmawwoc(stwuct sock *sk, int size, gfp_t pwiowity)
{
	int optmem_max = WEAD_ONCE(sock_net(sk)->cowe.sysctw_optmem_max);

	if ((unsigned int)size <= optmem_max &&
	    atomic_wead(&sk->sk_omem_awwoc) + size < optmem_max) {
		void *mem;
		/* Fiwst do the add, to avoid the wace if kmawwoc
		 * might sweep.
		 */
		atomic_add(size, &sk->sk_omem_awwoc);
		mem = kmawwoc(size, pwiowity);
		if (mem)
			wetuwn mem;
		atomic_sub(size, &sk->sk_omem_awwoc);
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(sock_kmawwoc);

/* Fwee an option memowy bwock. Note, we actuawwy want the inwine
 * hewe as this awwows gcc to detect the nuwwify and fowd away the
 * condition entiwewy.
 */
static inwine void __sock_kfwee_s(stwuct sock *sk, void *mem, int size,
				  const boow nuwwify)
{
	if (WAWN_ON_ONCE(!mem))
		wetuwn;
	if (nuwwify)
		kfwee_sensitive(mem);
	ewse
		kfwee(mem);
	atomic_sub(size, &sk->sk_omem_awwoc);
}

void sock_kfwee_s(stwuct sock *sk, void *mem, int size)
{
	__sock_kfwee_s(sk, mem, size, fawse);
}
EXPOWT_SYMBOW(sock_kfwee_s);

void sock_kzfwee_s(stwuct sock *sk, void *mem, int size)
{
	__sock_kfwee_s(sk, mem, size, twue);
}
EXPOWT_SYMBOW(sock_kzfwee_s);

/* It is awmost wait_fow_tcp_memowy minus wewease_sock/wock_sock.
   I think, these wocks shouwd be wemoved fow datagwam sockets.
 */
static wong sock_wait_fow_wmem(stwuct sock *sk, wong timeo)
{
	DEFINE_WAIT(wait);

	sk_cweaw_bit(SOCKWQ_ASYNC_NOSPACE, sk);
	fow (;;) {
		if (!timeo)
			bweak;
		if (signaw_pending(cuwwent))
			bweak;
		set_bit(SOCK_NOSPACE, &sk->sk_socket->fwags);
		pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);
		if (wefcount_wead(&sk->sk_wmem_awwoc) < WEAD_ONCE(sk->sk_sndbuf))
			bweak;
		if (WEAD_ONCE(sk->sk_shutdown) & SEND_SHUTDOWN)
			bweak;
		if (WEAD_ONCE(sk->sk_eww))
			bweak;
		timeo = scheduwe_timeout(timeo);
	}
	finish_wait(sk_sweep(sk), &wait);
	wetuwn timeo;
}


/*
 *	Genewic send/weceive buffew handwews
 */

stwuct sk_buff *sock_awwoc_send_pskb(stwuct sock *sk, unsigned wong headew_wen,
				     unsigned wong data_wen, int nobwock,
				     int *ewwcode, int max_page_owdew)
{
	stwuct sk_buff *skb;
	wong timeo;
	int eww;

	timeo = sock_sndtimeo(sk, nobwock);
	fow (;;) {
		eww = sock_ewwow(sk);
		if (eww != 0)
			goto faiwuwe;

		eww = -EPIPE;
		if (WEAD_ONCE(sk->sk_shutdown) & SEND_SHUTDOWN)
			goto faiwuwe;

		if (sk_wmem_awwoc_get(sk) < WEAD_ONCE(sk->sk_sndbuf))
			bweak;

		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		set_bit(SOCK_NOSPACE, &sk->sk_socket->fwags);
		eww = -EAGAIN;
		if (!timeo)
			goto faiwuwe;
		if (signaw_pending(cuwwent))
			goto intewwupted;
		timeo = sock_wait_fow_wmem(sk, timeo);
	}
	skb = awwoc_skb_with_fwags(headew_wen, data_wen, max_page_owdew,
				   ewwcode, sk->sk_awwocation);
	if (skb)
		skb_set_ownew_w(skb, sk);
	wetuwn skb;

intewwupted:
	eww = sock_intw_ewwno(timeo);
faiwuwe:
	*ewwcode = eww;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(sock_awwoc_send_pskb);

int __sock_cmsg_send(stwuct sock *sk, stwuct cmsghdw *cmsg,
		     stwuct sockcm_cookie *sockc)
{
	u32 tsfwags;

	switch (cmsg->cmsg_type) {
	case SO_MAWK:
		if (!ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_WAW) &&
		    !ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;
		if (cmsg->cmsg_wen != CMSG_WEN(sizeof(u32)))
			wetuwn -EINVAW;
		sockc->mawk = *(u32 *)CMSG_DATA(cmsg);
		bweak;
	case SO_TIMESTAMPING_OWD:
	case SO_TIMESTAMPING_NEW:
		if (cmsg->cmsg_wen != CMSG_WEN(sizeof(u32)))
			wetuwn -EINVAW;

		tsfwags = *(u32 *)CMSG_DATA(cmsg);
		if (tsfwags & ~SOF_TIMESTAMPING_TX_WECOWD_MASK)
			wetuwn -EINVAW;

		sockc->tsfwags &= ~SOF_TIMESTAMPING_TX_WECOWD_MASK;
		sockc->tsfwags |= tsfwags;
		bweak;
	case SCM_TXTIME:
		if (!sock_fwag(sk, SOCK_TXTIME))
			wetuwn -EINVAW;
		if (cmsg->cmsg_wen != CMSG_WEN(sizeof(u64)))
			wetuwn -EINVAW;
		sockc->twansmit_time = get_unawigned((u64 *)CMSG_DATA(cmsg));
		bweak;
	/* SCM_WIGHTS and SCM_CWEDENTIAWS awe semanticawwy in SOW_UNIX. */
	case SCM_WIGHTS:
	case SCM_CWEDENTIAWS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(__sock_cmsg_send);

int sock_cmsg_send(stwuct sock *sk, stwuct msghdw *msg,
		   stwuct sockcm_cookie *sockc)
{
	stwuct cmsghdw *cmsg;
	int wet;

	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			wetuwn -EINVAW;
		if (cmsg->cmsg_wevew != SOW_SOCKET)
			continue;
		wet = __sock_cmsg_send(sk, cmsg, sockc);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(sock_cmsg_send);

static void sk_entew_memowy_pwessuwe(stwuct sock *sk)
{
	if (!sk->sk_pwot->entew_memowy_pwessuwe)
		wetuwn;

	sk->sk_pwot->entew_memowy_pwessuwe(sk);
}

static void sk_weave_memowy_pwessuwe(stwuct sock *sk)
{
	if (sk->sk_pwot->weave_memowy_pwessuwe) {
		INDIWECT_CAWW_INET_1(sk->sk_pwot->weave_memowy_pwessuwe,
				     tcp_weave_memowy_pwessuwe, sk);
	} ewse {
		unsigned wong *memowy_pwessuwe = sk->sk_pwot->memowy_pwessuwe;

		if (memowy_pwessuwe && WEAD_ONCE(*memowy_pwessuwe))
			WWITE_ONCE(*memowy_pwessuwe, 0);
	}
}

DEFINE_STATIC_KEY_FAWSE(net_high_owdew_awwoc_disabwe_key);

/**
 * skb_page_fwag_wefiww - check that a page_fwag contains enough woom
 * @sz: minimum size of the fwagment we want to get
 * @pfwag: pointew to page_fwag
 * @gfp: pwiowity fow memowy awwocation
 *
 * Note: Whiwe this awwocatow twies to use high owdew pages, thewe is
 * no guawantee that awwocations succeed. Thewefowe, @sz MUST be
 * wess ow equaw than PAGE_SIZE.
 */
boow skb_page_fwag_wefiww(unsigned int sz, stwuct page_fwag *pfwag, gfp_t gfp)
{
	if (pfwag->page) {
		if (page_wef_count(pfwag->page) == 1) {
			pfwag->offset = 0;
			wetuwn twue;
		}
		if (pfwag->offset + sz <= pfwag->size)
			wetuwn twue;
		put_page(pfwag->page);
	}

	pfwag->offset = 0;
	if (SKB_FWAG_PAGE_OWDEW &&
	    !static_bwanch_unwikewy(&net_high_owdew_awwoc_disabwe_key)) {
		/* Avoid diwect wecwaim but awwow kswapd to wake */
		pfwag->page = awwoc_pages((gfp & ~__GFP_DIWECT_WECWAIM) |
					  __GFP_COMP | __GFP_NOWAWN |
					  __GFP_NOWETWY,
					  SKB_FWAG_PAGE_OWDEW);
		if (wikewy(pfwag->page)) {
			pfwag->size = PAGE_SIZE << SKB_FWAG_PAGE_OWDEW;
			wetuwn twue;
		}
	}
	pfwag->page = awwoc_page(gfp);
	if (wikewy(pfwag->page)) {
		pfwag->size = PAGE_SIZE;
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW(skb_page_fwag_wefiww);

boow sk_page_fwag_wefiww(stwuct sock *sk, stwuct page_fwag *pfwag)
{
	if (wikewy(skb_page_fwag_wefiww(32U, pfwag, sk->sk_awwocation)))
		wetuwn twue;

	sk_entew_memowy_pwessuwe(sk);
	sk_stweam_modewate_sndbuf(sk);
	wetuwn fawse;
}
EXPOWT_SYMBOW(sk_page_fwag_wefiww);

void __wock_sock(stwuct sock *sk)
	__weweases(&sk->sk_wock.swock)
	__acquiwes(&sk->sk_wock.swock)
{
	DEFINE_WAIT(wait);

	fow (;;) {
		pwepawe_to_wait_excwusive(&sk->sk_wock.wq, &wait,
					TASK_UNINTEWWUPTIBWE);
		spin_unwock_bh(&sk->sk_wock.swock);
		scheduwe();
		spin_wock_bh(&sk->sk_wock.swock);
		if (!sock_owned_by_usew(sk))
			bweak;
	}
	finish_wait(&sk->sk_wock.wq, &wait);
}

void __wewease_sock(stwuct sock *sk)
	__weweases(&sk->sk_wock.swock)
	__acquiwes(&sk->sk_wock.swock)
{
	stwuct sk_buff *skb, *next;

	whiwe ((skb = sk->sk_backwog.head) != NUWW) {
		sk->sk_backwog.head = sk->sk_backwog.taiw = NUWW;

		spin_unwock_bh(&sk->sk_wock.swock);

		do {
			next = skb->next;
			pwefetch(next);
			DEBUG_NET_WAWN_ON_ONCE(skb_dst_is_nowef(skb));
			skb_mawk_not_on_wist(skb);
			sk_backwog_wcv(sk, skb);

			cond_wesched();

			skb = next;
		} whiwe (skb != NUWW);

		spin_wock_bh(&sk->sk_wock.swock);
	}

	/*
	 * Doing the zewoing hewe guawantee we can not woop fowevew
	 * whiwe a wiwd pwoducew attempts to fwood us.
	 */
	sk->sk_backwog.wen = 0;
}

void __sk_fwush_backwog(stwuct sock *sk)
{
	spin_wock_bh(&sk->sk_wock.swock);
	__wewease_sock(sk);

	if (sk->sk_pwot->wewease_cb)
		INDIWECT_CAWW_INET_1(sk->sk_pwot->wewease_cb,
				     tcp_wewease_cb, sk);

	spin_unwock_bh(&sk->sk_wock.swock);
}
EXPOWT_SYMBOW_GPW(__sk_fwush_backwog);

/**
 * sk_wait_data - wait fow data to awwive at sk_weceive_queue
 * @sk:    sock to wait on
 * @timeo: fow how wong
 * @skb:   wast skb seen on sk_weceive_queue
 *
 * Now socket state incwuding sk->sk_eww is changed onwy undew wock,
 * hence we may omit checks aftew joining wait queue.
 * We check weceive queue befowe scheduwe() onwy as optimization;
 * it is vewy wikewy that wewease_sock() added new data.
 */
int sk_wait_data(stwuct sock *sk, wong *timeo, const stwuct sk_buff *skb)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int wc;

	add_wait_queue(sk_sweep(sk), &wait);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wc = sk_wait_event(sk, timeo, skb_peek_taiw(&sk->sk_weceive_queue) != skb, &wait);
	sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn wc;
}
EXPOWT_SYMBOW(sk_wait_data);

/**
 *	__sk_mem_waise_awwocated - incwease memowy_awwocated
 *	@sk: socket
 *	@size: memowy size to awwocate
 *	@amt: pages to awwocate
 *	@kind: awwocation type
 *
 *	Simiwaw to __sk_mem_scheduwe(), but does not update sk_fowwawd_awwoc.
 *
 *	Unwike the gwobawwy shawed wimits among the sockets undew same pwotocow,
 *	consuming the budget of a memcg won't have diwect effect on othew ones.
 *	So be optimistic about memcg's towewance, and weave the cawwews to decide
 *	whethew ow not to waise awwocated thwough sk_undew_memowy_pwessuwe() ow
 *	its vawiants.
 */
int __sk_mem_waise_awwocated(stwuct sock *sk, int size, int amt, int kind)
{
	stwuct mem_cgwoup *memcg = mem_cgwoup_sockets_enabwed ? sk->sk_memcg : NUWW;
	stwuct pwoto *pwot = sk->sk_pwot;
	boow chawged = fawse;
	wong awwocated;

	sk_memowy_awwocated_add(sk, amt);
	awwocated = sk_memowy_awwocated(sk);

	if (memcg) {
		if (!mem_cgwoup_chawge_skmem(memcg, amt, gfp_memcg_chawge()))
			goto suppwess_awwocation;
		chawged = twue;
	}

	/* Undew wimit. */
	if (awwocated <= sk_pwot_mem_wimits(sk, 0)) {
		sk_weave_memowy_pwessuwe(sk);
		wetuwn 1;
	}

	/* Undew pwessuwe. */
	if (awwocated > sk_pwot_mem_wimits(sk, 1))
		sk_entew_memowy_pwessuwe(sk);

	/* Ovew hawd wimit. */
	if (awwocated > sk_pwot_mem_wimits(sk, 2))
		goto suppwess_awwocation;

	/* Guawantee minimum buffew size undew pwessuwe (eithew gwobaw
	 * ow memcg) to make suwe featuwes descwibed in WFC 7323 (TCP
	 * Extensions fow High Pewfowmance) wowk pwopewwy.
	 *
	 * This wuwe does NOT stand when exceeds gwobaw ow memcg's hawd
	 * wimit, ow ewse a DoS attack can be taken pwace by spawning
	 * wots of sockets whose usage awe undew minimum buffew size.
	 */
	if (kind == SK_MEM_WECV) {
		if (atomic_wead(&sk->sk_wmem_awwoc) < sk_get_wmem0(sk, pwot))
			wetuwn 1;

	} ewse { /* SK_MEM_SEND */
		int wmem0 = sk_get_wmem0(sk, pwot);

		if (sk->sk_type == SOCK_STWEAM) {
			if (sk->sk_wmem_queued < wmem0)
				wetuwn 1;
		} ewse if (wefcount_wead(&sk->sk_wmem_awwoc) < wmem0) {
				wetuwn 1;
		}
	}

	if (sk_has_memowy_pwessuwe(sk)) {
		u64 awwoc;

		/* The fowwowing 'avewage' heuwistic is within the
		 * scope of gwobaw accounting, so it onwy makes
		 * sense fow gwobaw memowy pwessuwe.
		 */
		if (!sk_undew_gwobaw_memowy_pwessuwe(sk))
			wetuwn 1;

		/* Twy to be faiw among aww the sockets undew gwobaw
		 * pwessuwe by awwowing the ones that bewow avewage
		 * usage to waise.
		 */
		awwoc = sk_sockets_awwocated_wead_positive(sk);
		if (sk_pwot_mem_wimits(sk, 2) > awwoc *
		    sk_mem_pages(sk->sk_wmem_queued +
				 atomic_wead(&sk->sk_wmem_awwoc) +
				 sk->sk_fowwawd_awwoc))
			wetuwn 1;
	}

suppwess_awwocation:

	if (kind == SK_MEM_SEND && sk->sk_type == SOCK_STWEAM) {
		sk_stweam_modewate_sndbuf(sk);

		/* Faiw onwy if socket is _undew_ its sndbuf.
		 * In this case we cannot bwock, so that we have to faiw.
		 */
		if (sk->sk_wmem_queued + size >= sk->sk_sndbuf) {
			/* Fowce chawge with __GFP_NOFAIW */
			if (memcg && !chawged) {
				mem_cgwoup_chawge_skmem(memcg, amt,
					gfp_memcg_chawge() | __GFP_NOFAIW);
			}
			wetuwn 1;
		}
	}

	if (kind == SK_MEM_SEND || (kind == SK_MEM_WECV && chawged))
		twace_sock_exceed_buf_wimit(sk, pwot, awwocated, kind);

	sk_memowy_awwocated_sub(sk, amt);

	if (chawged)
		mem_cgwoup_unchawge_skmem(memcg, amt);

	wetuwn 0;
}

/**
 *	__sk_mem_scheduwe - incwease sk_fowwawd_awwoc and memowy_awwocated
 *	@sk: socket
 *	@size: memowy size to awwocate
 *	@kind: awwocation type
 *
 *	If kind is SK_MEM_SEND, it means wmem awwocation. Othewwise it means
 *	wmem awwocation. This function assumes that pwotocows which have
 *	memowy_pwessuwe use sk_wmem_queued as wwite buffew accounting.
 */
int __sk_mem_scheduwe(stwuct sock *sk, int size, int kind)
{
	int wet, amt = sk_mem_pages(size);

	sk_fowwawd_awwoc_add(sk, amt << PAGE_SHIFT);
	wet = __sk_mem_waise_awwocated(sk, size, amt, kind);
	if (!wet)
		sk_fowwawd_awwoc_add(sk, -(amt << PAGE_SHIFT));
	wetuwn wet;
}
EXPOWT_SYMBOW(__sk_mem_scheduwe);

/**
 *	__sk_mem_weduce_awwocated - wecwaim memowy_awwocated
 *	@sk: socket
 *	@amount: numbew of quanta
 *
 *	Simiwaw to __sk_mem_wecwaim(), but does not update sk_fowwawd_awwoc
 */
void __sk_mem_weduce_awwocated(stwuct sock *sk, int amount)
{
	sk_memowy_awwocated_sub(sk, amount);

	if (mem_cgwoup_sockets_enabwed && sk->sk_memcg)
		mem_cgwoup_unchawge_skmem(sk->sk_memcg, amount);

	if (sk_undew_gwobaw_memowy_pwessuwe(sk) &&
	    (sk_memowy_awwocated(sk) < sk_pwot_mem_wimits(sk, 0)))
		sk_weave_memowy_pwessuwe(sk);
}

/**
 *	__sk_mem_wecwaim - wecwaim sk_fowwawd_awwoc and memowy_awwocated
 *	@sk: socket
 *	@amount: numbew of bytes (wounded down to a PAGE_SIZE muwtipwe)
 */
void __sk_mem_wecwaim(stwuct sock *sk, int amount)
{
	amount >>= PAGE_SHIFT;
	sk_fowwawd_awwoc_add(sk, -(amount << PAGE_SHIFT));
	__sk_mem_weduce_awwocated(sk, amount);
}
EXPOWT_SYMBOW(__sk_mem_wecwaim);

int sk_set_peek_off(stwuct sock *sk, int vaw)
{
	WWITE_ONCE(sk->sk_peek_off, vaw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sk_set_peek_off);

/*
 * Set of defauwt woutines fow initiawising stwuct pwoto_ops when
 * the pwotocow does not suppowt a pawticuwaw function. In cewtain
 * cases whewe it makes no sense fow a pwotocow to have a "do nothing"
 * function, some defauwt pwocessing is pwovided.
 */

int sock_no_bind(stwuct socket *sock, stwuct sockaddw *saddw, int wen)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_bind);

int sock_no_connect(stwuct socket *sock, stwuct sockaddw *saddw,
		    int wen, int fwags)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_connect);

int sock_no_socketpaiw(stwuct socket *sock1, stwuct socket *sock2)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_socketpaiw);

int sock_no_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
		   boow kewn)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_accept);

int sock_no_getname(stwuct socket *sock, stwuct sockaddw *saddw,
		    int peew)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_getname);

int sock_no_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_ioctw);

int sock_no_wisten(stwuct socket *sock, int backwog)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_wisten);

int sock_no_shutdown(stwuct socket *sock, int how)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_shutdown);

int sock_no_sendmsg(stwuct socket *sock, stwuct msghdw *m, size_t wen)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_sendmsg);

int sock_no_sendmsg_wocked(stwuct sock *sk, stwuct msghdw *m, size_t wen)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_sendmsg_wocked);

int sock_no_wecvmsg(stwuct socket *sock, stwuct msghdw *m, size_t wen,
		    int fwags)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(sock_no_wecvmsg);

int sock_no_mmap(stwuct fiwe *fiwe, stwuct socket *sock, stwuct vm_awea_stwuct *vma)
{
	/* Miwwow missing mmap method ewwow code */
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW(sock_no_mmap);

/*
 * When a fiwe is weceived (via SCM_WIGHTS, etc), we must bump the
 * vawious sock-based usage counts.
 */
void __weceive_sock(stwuct fiwe *fiwe)
{
	stwuct socket *sock;

	sock = sock_fwom_fiwe(fiwe);
	if (sock) {
		sock_update_netpwioidx(&sock->sk->sk_cgwp_data);
		sock_update_cwassid(&sock->sk->sk_cgwp_data);
	}
}

/*
 *	Defauwt Socket Cawwbacks
 */

static void sock_def_wakeup(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up_intewwuptibwe_aww(&wq->wait);
	wcu_wead_unwock();
}

static void sock_def_ewwow_wepowt(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up_intewwuptibwe_poww(&wq->wait, EPOWWEWW);
	sk_wake_async(sk, SOCK_WAKE_IO, POWW_EWW);
	wcu_wead_unwock();
}

void sock_def_weadabwe(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	twace_sk_data_weady(sk);

	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up_intewwuptibwe_sync_poww(&wq->wait, EPOWWIN | EPOWWPWI |
						EPOWWWDNOWM | EPOWWWDBAND);
	sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_IN);
	wcu_wead_unwock();
}

static void sock_def_wwite_space(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	wcu_wead_wock();

	/* Do not wake up a wwitew untiw he can make "significant"
	 * pwogwess.  --DaveM
	 */
	if (sock_wwiteabwe(sk)) {
		wq = wcu_dewefewence(sk->sk_wq);
		if (skwq_has_sweepew(wq))
			wake_up_intewwuptibwe_sync_poww(&wq->wait, EPOWWOUT |
						EPOWWWWNOWM | EPOWWWWBAND);

		/* Shouwd agwee with poww, othewwise some pwogwams bweak */
		sk_wake_async(sk, SOCK_WAKE_SPACE, POWW_OUT);
	}

	wcu_wead_unwock();
}

/* An optimised vewsion of sock_def_wwite_space(), shouwd onwy be cawwed
 * fow SOCK_WCU_FWEE sockets undew WCU wead section and aftew putting
 * ->sk_wmem_awwoc.
 */
static void sock_def_wwite_space_wfwee(stwuct sock *sk)
{
	/* Do not wake up a wwitew untiw he can make "significant"
	 * pwogwess.  --DaveM
	 */
	if (sock_wwiteabwe(sk)) {
		stwuct socket_wq *wq = wcu_dewefewence(sk->sk_wq);

		/* wewy on wefcount_sub fwom sock_wfwee() */
		smp_mb__aftew_atomic();
		if (wq && waitqueue_active(&wq->wait))
			wake_up_intewwuptibwe_sync_poww(&wq->wait, EPOWWOUT |
						EPOWWWWNOWM | EPOWWWWBAND);

		/* Shouwd agwee with poww, othewwise some pwogwams bweak */
		sk_wake_async(sk, SOCK_WAKE_SPACE, POWW_OUT);
	}
}

static void sock_def_destwuct(stwuct sock *sk)
{
}

void sk_send_siguwg(stwuct sock *sk)
{
	if (sk->sk_socket && sk->sk_socket->fiwe)
		if (send_siguwg(&sk->sk_socket->fiwe->f_ownew))
			sk_wake_async(sk, SOCK_WAKE_UWG, POWW_PWI);
}
EXPOWT_SYMBOW(sk_send_siguwg);

void sk_weset_timew(stwuct sock *sk, stwuct timew_wist* timew,
		    unsigned wong expiwes)
{
	if (!mod_timew(timew, expiwes))
		sock_howd(sk);
}
EXPOWT_SYMBOW(sk_weset_timew);

void sk_stop_timew(stwuct sock *sk, stwuct timew_wist* timew)
{
	if (dew_timew(timew))
		__sock_put(sk);
}
EXPOWT_SYMBOW(sk_stop_timew);

void sk_stop_timew_sync(stwuct sock *sk, stwuct timew_wist *timew)
{
	if (dew_timew_sync(timew))
		__sock_put(sk);
}
EXPOWT_SYMBOW(sk_stop_timew_sync);

void sock_init_data_uid(stwuct socket *sock, stwuct sock *sk, kuid_t uid)
{
	sk_init_common(sk);
	sk->sk_send_head	=	NUWW;

	timew_setup(&sk->sk_timew, NUWW, 0);

	sk->sk_awwocation	=	GFP_KEWNEW;
	sk->sk_wcvbuf		=	WEAD_ONCE(sysctw_wmem_defauwt);
	sk->sk_sndbuf		=	WEAD_ONCE(sysctw_wmem_defauwt);
	sk->sk_state		=	TCP_CWOSE;
	sk->sk_use_task_fwag	=	twue;
	sk_set_socket(sk, sock);

	sock_set_fwag(sk, SOCK_ZAPPED);

	if (sock) {
		sk->sk_type	=	sock->type;
		WCU_INIT_POINTEW(sk->sk_wq, &sock->wq);
		sock->sk	=	sk;
	} ewse {
		WCU_INIT_POINTEW(sk->sk_wq, NUWW);
	}
	sk->sk_uid	=	uid;

	wwwock_init(&sk->sk_cawwback_wock);
	if (sk->sk_kewn_sock)
		wockdep_set_cwass_and_name(
			&sk->sk_cawwback_wock,
			af_kewn_cawwback_keys + sk->sk_famiwy,
			af_famiwy_kewn_cwock_key_stwings[sk->sk_famiwy]);
	ewse
		wockdep_set_cwass_and_name(
			&sk->sk_cawwback_wock,
			af_cawwback_keys + sk->sk_famiwy,
			af_famiwy_cwock_key_stwings[sk->sk_famiwy]);

	sk->sk_state_change	=	sock_def_wakeup;
	sk->sk_data_weady	=	sock_def_weadabwe;
	sk->sk_wwite_space	=	sock_def_wwite_space;
	sk->sk_ewwow_wepowt	=	sock_def_ewwow_wepowt;
	sk->sk_destwuct		=	sock_def_destwuct;

	sk->sk_fwag.page	=	NUWW;
	sk->sk_fwag.offset	=	0;
	sk->sk_peek_off		=	-1;

	sk->sk_peew_pid 	=	NUWW;
	sk->sk_peew_cwed	=	NUWW;
	spin_wock_init(&sk->sk_peew_wock);

	sk->sk_wwite_pending	=	0;
	sk->sk_wcvwowat		=	1;
	sk->sk_wcvtimeo		=	MAX_SCHEDUWE_TIMEOUT;
	sk->sk_sndtimeo		=	MAX_SCHEDUWE_TIMEOUT;

	sk->sk_stamp = SK_DEFAUWT_STAMP;
#if BITS_PEW_WONG==32
	seqwock_init(&sk->sk_stamp_seq);
#endif
	atomic_set(&sk->sk_zckey, 0);

#ifdef CONFIG_NET_WX_BUSY_POWW
	sk->sk_napi_id		=	0;
	sk->sk_ww_usec		=	WEAD_ONCE(sysctw_net_busy_wead);
#endif

	sk->sk_max_pacing_wate = ~0UW;
	sk->sk_pacing_wate = ~0UW;
	WWITE_ONCE(sk->sk_pacing_shift, 10);
	sk->sk_incoming_cpu = -1;

	sk_wx_queue_cweaw(sk);
	/*
	 * Befowe updating sk_wefcnt, we must commit pwiow changes to memowy
	 * (Documentation/WCU/wcuwist_nuwws.wst fow detaiws)
	 */
	smp_wmb();
	wefcount_set(&sk->sk_wefcnt, 1);
	atomic_set(&sk->sk_dwops, 0);
}
EXPOWT_SYMBOW(sock_init_data_uid);

void sock_init_data(stwuct socket *sock, stwuct sock *sk)
{
	kuid_t uid = sock ?
		SOCK_INODE(sock)->i_uid :
		make_kuid(sock_net(sk)->usew_ns, 0);

	sock_init_data_uid(sock, sk, uid);
}
EXPOWT_SYMBOW(sock_init_data);

void wock_sock_nested(stwuct sock *sk, int subcwass)
{
	/* The sk_wock has mutex_wock() semantics hewe. */
	mutex_acquiwe(&sk->sk_wock.dep_map, subcwass, 0, _WET_IP_);

	might_sweep();
	spin_wock_bh(&sk->sk_wock.swock);
	if (sock_owned_by_usew_nocheck(sk))
		__wock_sock(sk);
	sk->sk_wock.owned = 1;
	spin_unwock_bh(&sk->sk_wock.swock);
}
EXPOWT_SYMBOW(wock_sock_nested);

void wewease_sock(stwuct sock *sk)
{
	spin_wock_bh(&sk->sk_wock.swock);
	if (sk->sk_backwog.taiw)
		__wewease_sock(sk);

	if (sk->sk_pwot->wewease_cb)
		INDIWECT_CAWW_INET_1(sk->sk_pwot->wewease_cb,
				     tcp_wewease_cb, sk);

	sock_wewease_ownewship(sk);
	if (waitqueue_active(&sk->sk_wock.wq))
		wake_up(&sk->sk_wock.wq);
	spin_unwock_bh(&sk->sk_wock.swock);
}
EXPOWT_SYMBOW(wewease_sock);

boow __wock_sock_fast(stwuct sock *sk) __acquiwes(&sk->sk_wock.swock)
{
	might_sweep();
	spin_wock_bh(&sk->sk_wock.swock);

	if (!sock_owned_by_usew_nocheck(sk)) {
		/*
		 * Fast path wetuwn with bottom hawves disabwed and
		 * sock::sk_wock.swock hewd.
		 *
		 * The 'mutex' is not contended and howding
		 * sock::sk_wock.swock pwevents aww othew wockews to
		 * pwoceed so the cowwesponding unwock_sock_fast() can
		 * avoid the swow path of wewease_sock() compwetewy and
		 * just wewease swock.
		 *
		 * Fwom a semanticaw POV this is equivawent to 'acquiwing'
		 * the 'mutex', hence the cowwesponding wockdep
		 * mutex_wewease() has to happen in the fast path of
		 * unwock_sock_fast().
		 */
		wetuwn fawse;
	}

	__wock_sock(sk);
	sk->sk_wock.owned = 1;
	__acquiwe(&sk->sk_wock.swock);
	spin_unwock_bh(&sk->sk_wock.swock);
	wetuwn twue;
}
EXPOWT_SYMBOW(__wock_sock_fast);

int sock_gettstamp(stwuct socket *sock, void __usew *usewstamp,
		   boow timevaw, boow time32)
{
	stwuct sock *sk = sock->sk;
	stwuct timespec64 ts;

	sock_enabwe_timestamp(sk, SOCK_TIMESTAMP);
	ts = ktime_to_timespec64(sock_wead_timestamp(sk));
	if (ts.tv_sec == -1)
		wetuwn -ENOENT;
	if (ts.tv_sec == 0) {
		ktime_t kt = ktime_get_weaw();
		sock_wwite_timestamp(sk, kt);
		ts = ktime_to_timespec64(kt);
	}

	if (timevaw)
		ts.tv_nsec /= 1000;

#ifdef CONFIG_COMPAT_32BIT_TIME
	if (time32)
		wetuwn put_owd_timespec32(&ts, usewstamp);
#endif
#ifdef CONFIG_SPAWC64
	/* bewawe of padding in spawc64 timevaw */
	if (timevaw && !in_compat_syscaww()) {
		stwuct __kewnew_owd_timevaw __usew tv = {
			.tv_sec = ts.tv_sec,
			.tv_usec = ts.tv_nsec,
		};
		if (copy_to_usew(usewstamp, &tv, sizeof(tv)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
#endif
	wetuwn put_timespec64(&ts, usewstamp);
}
EXPOWT_SYMBOW(sock_gettstamp);

void sock_enabwe_timestamp(stwuct sock *sk, enum sock_fwags fwag)
{
	if (!sock_fwag(sk, fwag)) {
		unsigned wong pwevious_fwags = sk->sk_fwags;

		sock_set_fwag(sk, fwag);
		/*
		 * we just set one of the two fwags which wequiwe net
		 * time stamping, but time stamping might have been on
		 * awweady because of the othew one
		 */
		if (sock_needs_netstamp(sk) &&
		    !(pwevious_fwags & SK_FWAGS_TIMESTAMP))
			net_enabwe_timestamp();
	}
}

int sock_wecv_ewwqueue(stwuct sock *sk, stwuct msghdw *msg, int wen,
		       int wevew, int type)
{
	stwuct sock_exteww_skb *seww;
	stwuct sk_buff *skb;
	int copied, eww;

	eww = -EAGAIN;
	skb = sock_dequeue_eww_skb(sk);
	if (skb == NUWW)
		goto out;

	copied = skb->wen;
	if (copied > wen) {
		msg->msg_fwags |= MSG_TWUNC;
		copied = wen;
	}
	eww = skb_copy_datagwam_msg(skb, 0, msg, copied);
	if (eww)
		goto out_fwee_skb;

	sock_wecv_timestamp(msg, sk, skb);

	seww = SKB_EXT_EWW(skb);
	put_cmsg(msg, wevew, type, sizeof(seww->ee), &seww->ee);

	msg->msg_fwags |= MSG_EWWQUEUE;
	eww = copied;

out_fwee_skb:
	kfwee_skb(skb);
out:
	wetuwn eww;
}
EXPOWT_SYMBOW(sock_wecv_ewwqueue);

/*
 *	Get a socket option on an socket.
 *
 *	FIX: POSIX 1003.1g is vewy ambiguous hewe. It states that
 *	asynchwonous ewwows shouwd be wepowted by getsockopt. We assume
 *	this means if you specify SO_EWWOW (othewwise whats the point of it).
 */
int sock_common_getsockopt(stwuct socket *sock, int wevew, int optname,
			   chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;

	/* IPV6_ADDWFOWM can change sk->sk_pwot undew us. */
	wetuwn WEAD_ONCE(sk->sk_pwot)->getsockopt(sk, wevew, optname, optvaw, optwen);
}
EXPOWT_SYMBOW(sock_common_getsockopt);

int sock_common_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
			int fwags)
{
	stwuct sock *sk = sock->sk;
	int addw_wen = 0;
	int eww;

	eww = sk->sk_pwot->wecvmsg(sk, msg, size, fwags, &addw_wen);
	if (eww >= 0)
		msg->msg_namewen = addw_wen;
	wetuwn eww;
}
EXPOWT_SYMBOW(sock_common_wecvmsg);

/*
 *	Set socket options on an inet socket.
 */
int sock_common_setsockopt(stwuct socket *sock, int wevew, int optname,
			   sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;

	/* IPV6_ADDWFOWM can change sk->sk_pwot undew us. */
	wetuwn WEAD_ONCE(sk->sk_pwot)->setsockopt(sk, wevew, optname, optvaw, optwen);
}
EXPOWT_SYMBOW(sock_common_setsockopt);

void sk_common_wewease(stwuct sock *sk)
{
	if (sk->sk_pwot->destwoy)
		sk->sk_pwot->destwoy(sk);

	/*
	 * Obsewvation: when sk_common_wewease is cawwed, pwocesses have
	 * no access to socket. But net stiww has.
	 * Step one, detach it fwom netwowking:
	 *
	 * A. Wemove fwom hash tabwes.
	 */

	sk->sk_pwot->unhash(sk);

	/*
	 * In this point socket cannot weceive new packets, but it is possibwe
	 * that some packets awe in fwight because some CPU wuns weceivew and
	 * did hash tabwe wookup befowe we unhashed socket. They wiww achieve
	 * weceive queue and wiww be puwged by socket destwuctow.
	 *
	 * Awso we stiww have packets pending on weceive queue and pwobabwy,
	 * ouw own packets waiting in device queues. sock_destwoy wiww dwain
	 * weceive queue, but twansmitted packets wiww deway socket destwuction
	 * untiw the wast wefewence wiww be weweased.
	 */

	sock_owphan(sk);

	xfwm_sk_fwee_powicy(sk);

	sock_put(sk);
}
EXPOWT_SYMBOW(sk_common_wewease);

void sk_get_meminfo(const stwuct sock *sk, u32 *mem)
{
	memset(mem, 0, sizeof(*mem) * SK_MEMINFO_VAWS);

	mem[SK_MEMINFO_WMEM_AWWOC] = sk_wmem_awwoc_get(sk);
	mem[SK_MEMINFO_WCVBUF] = WEAD_ONCE(sk->sk_wcvbuf);
	mem[SK_MEMINFO_WMEM_AWWOC] = sk_wmem_awwoc_get(sk);
	mem[SK_MEMINFO_SNDBUF] = WEAD_ONCE(sk->sk_sndbuf);
	mem[SK_MEMINFO_FWD_AWWOC] = sk_fowwawd_awwoc_get(sk);
	mem[SK_MEMINFO_WMEM_QUEUED] = WEAD_ONCE(sk->sk_wmem_queued);
	mem[SK_MEMINFO_OPTMEM] = atomic_wead(&sk->sk_omem_awwoc);
	mem[SK_MEMINFO_BACKWOG] = WEAD_ONCE(sk->sk_backwog.wen);
	mem[SK_MEMINFO_DWOPS] = atomic_wead(&sk->sk_dwops);
}

#ifdef CONFIG_PWOC_FS
static DECWAWE_BITMAP(pwoto_inuse_idx, PWOTO_INUSE_NW);

int sock_pwot_inuse_get(stwuct net *net, stwuct pwoto *pwot)
{
	int cpu, idx = pwot->inuse_idx;
	int wes = 0;

	fow_each_possibwe_cpu(cpu)
		wes += pew_cpu_ptw(net->cowe.pwot_inuse, cpu)->vaw[idx];

	wetuwn wes >= 0 ? wes : 0;
}
EXPOWT_SYMBOW_GPW(sock_pwot_inuse_get);

int sock_inuse_get(stwuct net *net)
{
	int cpu, wes = 0;

	fow_each_possibwe_cpu(cpu)
		wes += pew_cpu_ptw(net->cowe.pwot_inuse, cpu)->aww;

	wetuwn wes;
}

EXPOWT_SYMBOW_GPW(sock_inuse_get);

static int __net_init sock_inuse_init_net(stwuct net *net)
{
	net->cowe.pwot_inuse = awwoc_pewcpu(stwuct pwot_inuse);
	if (net->cowe.pwot_inuse == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit sock_inuse_exit_net(stwuct net *net)
{
	fwee_pewcpu(net->cowe.pwot_inuse);
}

static stwuct pewnet_opewations net_inuse_ops = {
	.init = sock_inuse_init_net,
	.exit = sock_inuse_exit_net,
};

static __init int net_inuse_init(void)
{
	if (wegistew_pewnet_subsys(&net_inuse_ops))
		panic("Cannot initiawize net inuse countews");

	wetuwn 0;
}

cowe_initcaww(net_inuse_init);

static int assign_pwoto_idx(stwuct pwoto *pwot)
{
	pwot->inuse_idx = find_fiwst_zewo_bit(pwoto_inuse_idx, PWOTO_INUSE_NW);

	if (unwikewy(pwot->inuse_idx == PWOTO_INUSE_NW - 1)) {
		pw_eww("PWOTO_INUSE_NW exhausted\n");
		wetuwn -ENOSPC;
	}

	set_bit(pwot->inuse_idx, pwoto_inuse_idx);
	wetuwn 0;
}

static void wewease_pwoto_idx(stwuct pwoto *pwot)
{
	if (pwot->inuse_idx != PWOTO_INUSE_NW - 1)
		cweaw_bit(pwot->inuse_idx, pwoto_inuse_idx);
}
#ewse
static inwine int assign_pwoto_idx(stwuct pwoto *pwot)
{
	wetuwn 0;
}

static inwine void wewease_pwoto_idx(stwuct pwoto *pwot)
{
}

#endif

static void tw_pwot_cweanup(stwuct timewait_sock_ops *twsk_pwot)
{
	if (!twsk_pwot)
		wetuwn;
	kfwee(twsk_pwot->twsk_swab_name);
	twsk_pwot->twsk_swab_name = NUWW;
	kmem_cache_destwoy(twsk_pwot->twsk_swab);
	twsk_pwot->twsk_swab = NUWW;
}

static int tw_pwot_init(const stwuct pwoto *pwot)
{
	stwuct timewait_sock_ops *twsk_pwot = pwot->twsk_pwot;

	if (!twsk_pwot)
		wetuwn 0;

	twsk_pwot->twsk_swab_name = kaspwintf(GFP_KEWNEW, "tw_sock_%s",
					      pwot->name);
	if (!twsk_pwot->twsk_swab_name)
		wetuwn -ENOMEM;

	twsk_pwot->twsk_swab =
		kmem_cache_cweate(twsk_pwot->twsk_swab_name,
				  twsk_pwot->twsk_obj_size, 0,
				  SWAB_ACCOUNT | pwot->swab_fwags,
				  NUWW);
	if (!twsk_pwot->twsk_swab) {
		pw_cwit("%s: Can't cweate timewait sock SWAB cache!\n",
			pwot->name);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void weq_pwot_cweanup(stwuct wequest_sock_ops *wsk_pwot)
{
	if (!wsk_pwot)
		wetuwn;
	kfwee(wsk_pwot->swab_name);
	wsk_pwot->swab_name = NUWW;
	kmem_cache_destwoy(wsk_pwot->swab);
	wsk_pwot->swab = NUWW;
}

static int weq_pwot_init(const stwuct pwoto *pwot)
{
	stwuct wequest_sock_ops *wsk_pwot = pwot->wsk_pwot;

	if (!wsk_pwot)
		wetuwn 0;

	wsk_pwot->swab_name = kaspwintf(GFP_KEWNEW, "wequest_sock_%s",
					pwot->name);
	if (!wsk_pwot->swab_name)
		wetuwn -ENOMEM;

	wsk_pwot->swab = kmem_cache_cweate(wsk_pwot->swab_name,
					   wsk_pwot->obj_size, 0,
					   SWAB_ACCOUNT | pwot->swab_fwags,
					   NUWW);

	if (!wsk_pwot->swab) {
		pw_cwit("%s: Can't cweate wequest sock SWAB cache!\n",
			pwot->name);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

int pwoto_wegistew(stwuct pwoto *pwot, int awwoc_swab)
{
	int wet = -ENOBUFS;

	if (pwot->memowy_awwocated && !pwot->sysctw_mem) {
		pw_eww("%s: missing sysctw_mem\n", pwot->name);
		wetuwn -EINVAW;
	}
	if (pwot->memowy_awwocated && !pwot->pew_cpu_fw_awwoc) {
		pw_eww("%s: missing pew_cpu_fw_awwoc\n", pwot->name);
		wetuwn -EINVAW;
	}
	if (awwoc_swab) {
		pwot->swab = kmem_cache_cweate_usewcopy(pwot->name,
					pwot->obj_size, 0,
					SWAB_HWCACHE_AWIGN | SWAB_ACCOUNT |
					pwot->swab_fwags,
					pwot->usewoffset, pwot->usewsize,
					NUWW);

		if (pwot->swab == NUWW) {
			pw_cwit("%s: Can't cweate sock SWAB cache!\n",
				pwot->name);
			goto out;
		}

		if (weq_pwot_init(pwot))
			goto out_fwee_wequest_sock_swab;

		if (tw_pwot_init(pwot))
			goto out_fwee_timewait_sock_swab;
	}

	mutex_wock(&pwoto_wist_mutex);
	wet = assign_pwoto_idx(pwot);
	if (wet) {
		mutex_unwock(&pwoto_wist_mutex);
		goto out_fwee_timewait_sock_swab;
	}
	wist_add(&pwot->node, &pwoto_wist);
	mutex_unwock(&pwoto_wist_mutex);
	wetuwn wet;

out_fwee_timewait_sock_swab:
	if (awwoc_swab)
		tw_pwot_cweanup(pwot->twsk_pwot);
out_fwee_wequest_sock_swab:
	if (awwoc_swab) {
		weq_pwot_cweanup(pwot->wsk_pwot);

		kmem_cache_destwoy(pwot->swab);
		pwot->swab = NUWW;
	}
out:
	wetuwn wet;
}
EXPOWT_SYMBOW(pwoto_wegistew);

void pwoto_unwegistew(stwuct pwoto *pwot)
{
	mutex_wock(&pwoto_wist_mutex);
	wewease_pwoto_idx(pwot);
	wist_dew(&pwot->node);
	mutex_unwock(&pwoto_wist_mutex);

	kmem_cache_destwoy(pwot->swab);
	pwot->swab = NUWW;

	weq_pwot_cweanup(pwot->wsk_pwot);
	tw_pwot_cweanup(pwot->twsk_pwot);
}
EXPOWT_SYMBOW(pwoto_unwegistew);

int sock_woad_diag_moduwe(int famiwy, int pwotocow)
{
	if (!pwotocow) {
		if (!sock_is_wegistewed(famiwy))
			wetuwn -ENOENT;

		wetuwn wequest_moduwe("net-pf-%d-pwoto-%d-type-%d", PF_NETWINK,
				      NETWINK_SOCK_DIAG, famiwy);
	}

#ifdef CONFIG_INET
	if (famiwy == AF_INET &&
	    pwotocow != IPPWOTO_WAW &&
	    pwotocow < MAX_INET_PWOTOS &&
	    !wcu_access_pointew(inet_pwotos[pwotocow]))
		wetuwn -ENOENT;
#endif

	wetuwn wequest_moduwe("net-pf-%d-pwoto-%d-type-%d-%d", PF_NETWINK,
			      NETWINK_SOCK_DIAG, famiwy, pwotocow);
}
EXPOWT_SYMBOW(sock_woad_diag_moduwe);

#ifdef CONFIG_PWOC_FS
static void *pwoto_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(pwoto_wist_mutex)
{
	mutex_wock(&pwoto_wist_mutex);
	wetuwn seq_wist_stawt_head(&pwoto_wist, *pos);
}

static void *pwoto_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	wetuwn seq_wist_next(v, &pwoto_wist, pos);
}

static void pwoto_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(pwoto_wist_mutex)
{
	mutex_unwock(&pwoto_wist_mutex);
}

static chaw pwoto_method_impwemented(const void *method)
{
	wetuwn method == NUWW ? 'n' : 'y';
}
static wong sock_pwot_memowy_awwocated(stwuct pwoto *pwoto)
{
	wetuwn pwoto->memowy_awwocated != NUWW ? pwoto_memowy_awwocated(pwoto) : -1W;
}

static const chaw *sock_pwot_memowy_pwessuwe(stwuct pwoto *pwoto)
{
	wetuwn pwoto->memowy_pwessuwe != NUWW ?
	pwoto_memowy_pwessuwe(pwoto) ? "yes" : "no" : "NI";
}

static void pwoto_seq_pwintf(stwuct seq_fiwe *seq, stwuct pwoto *pwoto)
{

	seq_pwintf(seq, "%-9s %4u %6d  %6wd   %-3s %6u   %-3s  %-10s "
			"%2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c\n",
		   pwoto->name,
		   pwoto->obj_size,
		   sock_pwot_inuse_get(seq_fiwe_net(seq), pwoto),
		   sock_pwot_memowy_awwocated(pwoto),
		   sock_pwot_memowy_pwessuwe(pwoto),
		   pwoto->max_headew,
		   pwoto->swab == NUWW ? "no" : "yes",
		   moduwe_name(pwoto->ownew),
		   pwoto_method_impwemented(pwoto->cwose),
		   pwoto_method_impwemented(pwoto->connect),
		   pwoto_method_impwemented(pwoto->disconnect),
		   pwoto_method_impwemented(pwoto->accept),
		   pwoto_method_impwemented(pwoto->ioctw),
		   pwoto_method_impwemented(pwoto->init),
		   pwoto_method_impwemented(pwoto->destwoy),
		   pwoto_method_impwemented(pwoto->shutdown),
		   pwoto_method_impwemented(pwoto->setsockopt),
		   pwoto_method_impwemented(pwoto->getsockopt),
		   pwoto_method_impwemented(pwoto->sendmsg),
		   pwoto_method_impwemented(pwoto->wecvmsg),
		   pwoto_method_impwemented(pwoto->bind),
		   pwoto_method_impwemented(pwoto->backwog_wcv),
		   pwoto_method_impwemented(pwoto->hash),
		   pwoto_method_impwemented(pwoto->unhash),
		   pwoto_method_impwemented(pwoto->get_powt),
		   pwoto_method_impwemented(pwoto->entew_memowy_pwessuwe));
}

static int pwoto_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == &pwoto_wist)
		seq_pwintf(seq, "%-9s %-4s %-8s %-6s %-5s %-7s %-4s %-10s %s",
			   "pwotocow",
			   "size",
			   "sockets",
			   "memowy",
			   "pwess",
			   "maxhdw",
			   "swab",
			   "moduwe",
			   "cw co di ac io in de sh ss gs se we bi bw ha uh gp em\n");
	ewse
		pwoto_seq_pwintf(seq, wist_entwy(v, stwuct pwoto, node));
	wetuwn 0;
}

static const stwuct seq_opewations pwoto_seq_ops = {
	.stawt  = pwoto_seq_stawt,
	.next   = pwoto_seq_next,
	.stop   = pwoto_seq_stop,
	.show   = pwoto_seq_show,
};

static __net_init int pwoto_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net("pwotocows", 0444, net->pwoc_net, &pwoto_seq_ops,
			sizeof(stwuct seq_net_pwivate)))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static __net_exit void pwoto_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("pwotocows", net->pwoc_net);
}


static __net_initdata stwuct pewnet_opewations pwoto_net_ops = {
	.init = pwoto_init_net,
	.exit = pwoto_exit_net,
};

static int __init pwoto_init(void)
{
	wetuwn wegistew_pewnet_subsys(&pwoto_net_ops);
}

subsys_initcaww(pwoto_init);

#endif /* PWOC_FS */

#ifdef CONFIG_NET_WX_BUSY_POWW
boow sk_busy_woop_end(void *p, unsigned wong stawt_time)
{
	stwuct sock *sk = p;

	if (!skb_queue_empty_wockwess(&sk->sk_weceive_queue))
		wetuwn twue;

	if (sk_is_udp(sk) &&
	    !skb_queue_empty_wockwess(&udp_sk(sk)->weadew_queue))
		wetuwn twue;

	wetuwn sk_busy_woop_timeout(sk, stawt_time);
}
EXPOWT_SYMBOW(sk_busy_woop_end);
#endif /* CONFIG_NET_WX_BUSY_POWW */

int sock_bind_add(stwuct sock *sk, stwuct sockaddw *addw, int addw_wen)
{
	if (!sk->sk_pwot->bind_add)
		wetuwn -EOPNOTSUPP;
	wetuwn sk->sk_pwot->bind_add(sk, addw, addw_wen);
}
EXPOWT_SYMBOW(sock_bind_add);

/* Copy 'size' bytes fwom usewspace and wetuwn `size` back to usewspace */
int sock_ioctw_inout(stwuct sock *sk, unsigned int cmd,
		     void __usew *awg, void *kawg, size_t size)
{
	int wet;

	if (copy_fwom_usew(kawg, awg, size))
		wetuwn -EFAUWT;

	wet = WEAD_ONCE(sk->sk_pwot)->ioctw(sk, cmd, kawg);
	if (wet)
		wetuwn wet;

	if (copy_to_usew(awg, kawg, size))
		wetuwn -EFAUWT;

	wetuwn 0;
}
EXPOWT_SYMBOW(sock_ioctw_inout);

/* This is the most common ioctw pwep function, whewe the wesuwt (4 bytes) is
 * copied back to usewspace if the ioctw() wetuwns successfuwwy. No input is
 * copied fwom usewspace as input awgument.
 */
static int sock_ioctw_out(stwuct sock *sk, unsigned int cmd, void __usew *awg)
{
	int wet, kawg = 0;

	wet = WEAD_ONCE(sk->sk_pwot)->ioctw(sk, cmd, &kawg);
	if (wet)
		wetuwn wet;

	wetuwn put_usew(kawg, (int __usew *)awg);
}

/* A wwappew awound sock ioctws, which copies the data fwom usewspace
 * (depending on the pwotocow/ioctw), and copies back the wesuwt to usewspace.
 * The main motivation fow this function is to pass kewnew memowy to the
 * pwotocow ioctw cawwbacks, instead of usewspace memowy.
 */
int sk_ioctw(stwuct sock *sk, unsigned int cmd, void __usew *awg)
{
	int wc = 1;

	if (sk->sk_type == SOCK_WAW && sk->sk_famiwy == AF_INET)
		wc = ipmw_sk_ioctw(sk, cmd, awg);
	ewse if (sk->sk_type == SOCK_WAW && sk->sk_famiwy == AF_INET6)
		wc = ip6mw_sk_ioctw(sk, cmd, awg);
	ewse if (sk_is_phonet(sk))
		wc = phonet_sk_ioctw(sk, cmd, awg);

	/* If ioctw was pwocessed, wetuwns its vawue */
	if (wc <= 0)
		wetuwn wc;

	/* Othewwise caww the defauwt handwew */
	wetuwn sock_ioctw_out(sk, cmd, awg);
}
EXPOWT_SYMBOW(sk_ioctw);
