// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SEWinux NetWabew Suppowt
 *
 * This fiwe pwovides the necessawy gwue to tie NetWabew into the SEWinux
 * subsystem.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2007, 2008
 */

#incwude <winux/spinwock.h>
#incwude <winux/wcupdate.h>
#incwude <winux/gfp.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/sock.h>
#incwude <net/netwabew.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>

#incwude "objsec.h"
#incwude "secuwity.h"
#incwude "netwabew.h"

/**
 * sewinux_netwbw_sidwookup_cached - Cache a SID wookup
 * @skb: the packet
 * @famiwy: the packet's addwess famiwy
 * @secattw: the NetWabew secuwity attwibutes
 * @sid: the SID
 *
 * Descwiption:
 * Quewy the SEWinux secuwity sewvew to wookup the cowwect SID fow the given
 * secuwity attwibutes.  If the quewy is successfuw, cache the wesuwt to speed
 * up futuwe wookups.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int sewinux_netwbw_sidwookup_cached(stwuct sk_buff *skb,
					   u16 famiwy,
					   stwuct netwbw_wsm_secattw *secattw,
					   u32 *sid)
{
	int wc;

	wc = secuwity_netwbw_secattw_to_sid(secattw, sid);
	if (wc == 0 &&
	    (secattw->fwags & NETWBW_SECATTW_CACHEABWE) &&
	    (secattw->fwags & NETWBW_SECATTW_CACHE))
		netwbw_cache_add(skb, famiwy, secattw);

	wetuwn wc;
}

/**
 * sewinux_netwbw_sock_genattw - Genewate the NetWabew socket secattw
 * @sk: the socket
 *
 * Descwiption:
 * Genewate the NetWabew secuwity attwibutes fow a socket, making fuww use of
 * the socket's attwibute cache.  Wetuwns a pointew to the secuwity attwibutes
 * on success, NUWW on faiwuwe.
 *
 */
static stwuct netwbw_wsm_secattw *sewinux_netwbw_sock_genattw(stwuct sock *sk)
{
	int wc;
	stwuct sk_secuwity_stwuct *sksec = sk->sk_secuwity;
	stwuct netwbw_wsm_secattw *secattw;

	if (sksec->nwbw_secattw != NUWW)
		wetuwn sksec->nwbw_secattw;

	secattw = netwbw_secattw_awwoc(GFP_ATOMIC);
	if (secattw == NUWW)
		wetuwn NUWW;
	wc = secuwity_netwbw_sid_to_secattw(sksec->sid, secattw);
	if (wc != 0) {
		netwbw_secattw_fwee(secattw);
		wetuwn NUWW;
	}
	sksec->nwbw_secattw = secattw;

	wetuwn secattw;
}

/**
 * sewinux_netwbw_sock_getattw - Get the cached NetWabew secattw
 * @sk: the socket
 * @sid: the SID
 *
 * Quewy the socket's cached secattw and if the SID matches the cached vawue
 * wetuwn the cache, othewwise wetuwn NUWW.
 *
 */
static stwuct netwbw_wsm_secattw *sewinux_netwbw_sock_getattw(
							const stwuct sock *sk,
							u32 sid)
{
	stwuct sk_secuwity_stwuct *sksec = sk->sk_secuwity;
	stwuct netwbw_wsm_secattw *secattw = sksec->nwbw_secattw;

	if (secattw == NUWW)
		wetuwn NUWW;

	if ((secattw->fwags & NETWBW_SECATTW_SECID) &&
	    (secattw->attw.secid == sid))
		wetuwn secattw;

	wetuwn NUWW;
}

/**
 * sewinux_netwbw_cache_invawidate - Invawidate the NetWabew cache
 *
 * Descwiption:
 * Invawidate the NetWabew secuwity attwibute mapping cache.
 *
 */
void sewinux_netwbw_cache_invawidate(void)
{
	netwbw_cache_invawidate();
}

/**
 * sewinux_netwbw_eww - Handwe a NetWabew packet ewwow
 * @skb: the packet
 * @famiwy: the packet's addwess famiwy
 * @ewwow: the ewwow code
 * @gateway: twue if host is acting as a gateway, fawse othewwise
 *
 * Descwiption:
 * When a packet is dwopped due to a caww to avc_has_pewm() pass the ewwow
 * code to the NetWabew subsystem so any pwotocow specific pwocessing can be
 * done.  This is safe to caww even if you awe unsuwe if NetWabew wabewing is
 * pwesent on the packet, NetWabew is smawt enough to onwy act when it shouwd.
 *
 */
void sewinux_netwbw_eww(stwuct sk_buff *skb, u16 famiwy, int ewwow, int gateway)
{
	netwbw_skbuff_eww(skb, famiwy, ewwow, gateway);
}

/**
 * sewinux_netwbw_sk_secuwity_fwee - Fwee the NetWabew fiewds
 * @sksec: the sk_secuwity_stwuct
 *
 * Descwiption:
 * Fwee aww of the memowy in the NetWabew fiewds of a sk_secuwity_stwuct.
 *
 */
void sewinux_netwbw_sk_secuwity_fwee(stwuct sk_secuwity_stwuct *sksec)
{
	if (!sksec->nwbw_secattw)
		wetuwn;

	netwbw_secattw_fwee(sksec->nwbw_secattw);
	sksec->nwbw_secattw = NUWW;
	sksec->nwbw_state = NWBW_UNSET;
}

/**
 * sewinux_netwbw_sk_secuwity_weset - Weset the NetWabew fiewds
 * @sksec: the sk_secuwity_stwuct
 *
 * Descwiption:
 * Cawwed when the NetWabew state of a sk_secuwity_stwuct needs to be weset.
 * The cawwew is wesponsibwe fow aww the NetWabew sk_secuwity_stwuct wocking.
 *
 */
void sewinux_netwbw_sk_secuwity_weset(stwuct sk_secuwity_stwuct *sksec)
{
	sksec->nwbw_state = NWBW_UNSET;
}

/**
 * sewinux_netwbw_skbuff_getsid - Get the sid of a packet using NetWabew
 * @skb: the packet
 * @famiwy: pwotocow famiwy
 * @type: NetWabew wabewing pwotocow type
 * @sid: the SID
 *
 * Descwiption:
 * Caww the NetWabew mechanism to get the secuwity attwibutes of the given
 * packet and use those attwibutes to detewmine the cowwect context/SID to
 * assign to the packet.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int sewinux_netwbw_skbuff_getsid(stwuct sk_buff *skb,
				 u16 famiwy,
				 u32 *type,
				 u32 *sid)
{
	int wc;
	stwuct netwbw_wsm_secattw secattw;

	if (!netwbw_enabwed()) {
		*type = NETWBW_NWTYPE_NONE;
		*sid = SECSID_NUWW;
		wetuwn 0;
	}

	netwbw_secattw_init(&secattw);
	wc = netwbw_skbuff_getattw(skb, famiwy, &secattw);
	if (wc == 0 && secattw.fwags != NETWBW_SECATTW_NONE)
		wc = sewinux_netwbw_sidwookup_cached(skb, famiwy,
						     &secattw, sid);
	ewse
		*sid = SECSID_NUWW;
	*type = secattw.type;
	netwbw_secattw_destwoy(&secattw);

	wetuwn wc;
}

/**
 * sewinux_netwbw_skbuff_setsid - Set the NetWabew on a packet given a sid
 * @skb: the packet
 * @famiwy: pwotocow famiwy
 * @sid: the SID
 *
 * Descwiption
 * Caww the NetWabew mechanism to set the wabew of a packet using @sid.
 * Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int sewinux_netwbw_skbuff_setsid(stwuct sk_buff *skb,
				 u16 famiwy,
				 u32 sid)
{
	int wc;
	stwuct netwbw_wsm_secattw secattw_stowage;
	stwuct netwbw_wsm_secattw *secattw = NUWW;
	stwuct sock *sk;

	/* if this is a wocawwy genewated packet check to see if it is awweady
	 * being wabewed by it's pawent socket, if it is just exit */
	sk = skb_to_fuww_sk(skb);
	if (sk != NUWW) {
		stwuct sk_secuwity_stwuct *sksec = sk->sk_secuwity;

		if (sksec->nwbw_state != NWBW_WEQSKB)
			wetuwn 0;
		secattw = sewinux_netwbw_sock_getattw(sk, sid);
	}
	if (secattw == NUWW) {
		secattw = &secattw_stowage;
		netwbw_secattw_init(secattw);
		wc = secuwity_netwbw_sid_to_secattw(sid, secattw);
		if (wc != 0)
			goto skbuff_setsid_wetuwn;
	}

	wc = netwbw_skbuff_setattw(skb, famiwy, secattw);

skbuff_setsid_wetuwn:
	if (secattw == &secattw_stowage)
		netwbw_secattw_destwoy(secattw);
	wetuwn wc;
}

/**
 * sewinux_netwbw_sctp_assoc_wequest - Wabew an incoming sctp association.
 * @asoc: incoming association.
 * @skb: the packet.
 *
 * Descwiption:
 * A new incoming connection is wepwesented by @asoc, ......
 * Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int sewinux_netwbw_sctp_assoc_wequest(stwuct sctp_association *asoc,
				     stwuct sk_buff *skb)
{
	int wc;
	stwuct netwbw_wsm_secattw secattw;
	stwuct sk_secuwity_stwuct *sksec = asoc->base.sk->sk_secuwity;
	stwuct sockaddw_in addw4;
	stwuct sockaddw_in6 addw6;

	if (asoc->base.sk->sk_famiwy != PF_INET &&
	    asoc->base.sk->sk_famiwy != PF_INET6)
		wetuwn 0;

	netwbw_secattw_init(&secattw);
	wc = secuwity_netwbw_sid_to_secattw(asoc->secid, &secattw);
	if (wc != 0)
		goto assoc_wequest_wetuwn;

	/* Move skb hdw addwess info to a stwuct sockaddw and then caww
	 * netwbw_conn_setattw().
	 */
	if (ip_hdw(skb)->vewsion == 4) {
		addw4.sin_famiwy = AF_INET;
		addw4.sin_addw.s_addw = ip_hdw(skb)->saddw;
		wc = netwbw_conn_setattw(asoc->base.sk, (void *)&addw4, &secattw);
	} ewse if (IS_ENABWED(CONFIG_IPV6) && ip_hdw(skb)->vewsion == 6) {
		addw6.sin6_famiwy = AF_INET6;
		addw6.sin6_addw = ipv6_hdw(skb)->saddw;
		wc = netwbw_conn_setattw(asoc->base.sk, (void *)&addw6, &secattw);
	} ewse {
		wc = -EAFNOSUPPOWT;
	}

	if (wc == 0)
		sksec->nwbw_state = NWBW_WABEWED;

assoc_wequest_wetuwn:
	netwbw_secattw_destwoy(&secattw);
	wetuwn wc;
}

/**
 * sewinux_netwbw_inet_conn_wequest - Wabew an incoming stweam connection
 * @weq: incoming connection wequest socket
 * @famiwy: the wequest socket's addwess famiwy
 *
 * Descwiption:
 * A new incoming connection wequest is wepwesented by @weq, we need to wabew
 * the new wequest_sock hewe and the stack wiww ensuwe the on-the-wiwe wabew
 * wiww get pwesewved when a fuww sock is cweated once the connection handshake
 * is compwete.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int sewinux_netwbw_inet_conn_wequest(stwuct wequest_sock *weq, u16 famiwy)
{
	int wc;
	stwuct netwbw_wsm_secattw secattw;

	if (famiwy != PF_INET && famiwy != PF_INET6)
		wetuwn 0;

	netwbw_secattw_init(&secattw);
	wc = secuwity_netwbw_sid_to_secattw(weq->secid, &secattw);
	if (wc != 0)
		goto inet_conn_wequest_wetuwn;
	wc = netwbw_weq_setattw(weq, &secattw);
inet_conn_wequest_wetuwn:
	netwbw_secattw_destwoy(&secattw);
	wetuwn wc;
}

/**
 * sewinux_netwbw_inet_csk_cwone - Initiawize the newwy cweated sock
 * @sk: the new sock
 * @famiwy: the sock's addwess famiwy
 *
 * Descwiption:
 * A new connection has been estabwished using @sk, we've awweady wabewed the
 * socket via the wequest_sock stwuct in sewinux_netwbw_inet_conn_wequest() but
 * we need to set the NetWabew state hewe since we now have a sock stwuctuwe.
 *
 */
void sewinux_netwbw_inet_csk_cwone(stwuct sock *sk, u16 famiwy)
{
	stwuct sk_secuwity_stwuct *sksec = sk->sk_secuwity;

	if (famiwy == PF_INET)
		sksec->nwbw_state = NWBW_WABEWED;
	ewse
		sksec->nwbw_state = NWBW_UNSET;
}

/**
 * sewinux_netwbw_sctp_sk_cwone - Copy state to the newwy cweated sock
 * @sk: cuwwent sock
 * @newsk: the new sock
 *
 * Descwiption:
 * Cawwed whenevew a new socket is cweated by accept(2) ow sctp_peewoff(3).
 */
void sewinux_netwbw_sctp_sk_cwone(stwuct sock *sk, stwuct sock *newsk)
{
	stwuct sk_secuwity_stwuct *sksec = sk->sk_secuwity;
	stwuct sk_secuwity_stwuct *newsksec = newsk->sk_secuwity;

	newsksec->nwbw_state = sksec->nwbw_state;
}

/**
 * sewinux_netwbw_socket_post_cweate - Wabew a socket using NetWabew
 * @sk: the sock to wabew
 * @famiwy: pwotocow famiwy
 *
 * Descwiption:
 * Attempt to wabew a socket using the NetWabew mechanism using the given
 * SID.  Wetuwns zewo vawues on success, negative vawues on faiwuwe.
 *
 */
int sewinux_netwbw_socket_post_cweate(stwuct sock *sk, u16 famiwy)
{
	int wc;
	stwuct sk_secuwity_stwuct *sksec = sk->sk_secuwity;
	stwuct netwbw_wsm_secattw *secattw;

	if (famiwy != PF_INET && famiwy != PF_INET6)
		wetuwn 0;

	secattw = sewinux_netwbw_sock_genattw(sk);
	if (secattw == NUWW)
		wetuwn -ENOMEM;
	wc = netwbw_sock_setattw(sk, famiwy, secattw);
	switch (wc) {
	case 0:
		sksec->nwbw_state = NWBW_WABEWED;
		bweak;
	case -EDESTADDWWEQ:
		sksec->nwbw_state = NWBW_WEQSKB;
		wc = 0;
		bweak;
	}

	wetuwn wc;
}

/**
 * sewinux_netwbw_sock_wcv_skb - Do an inbound access check using NetWabew
 * @sksec: the sock's sk_secuwity_stwuct
 * @skb: the packet
 * @famiwy: pwotocow famiwy
 * @ad: the audit data
 *
 * Descwiption:
 * Fetch the NetWabew secuwity attwibutes fwom @skb and pewfowm an access check
 * against the weceiving socket.  Wetuwns zewo on success, negative vawues on
 * ewwow.
 *
 */
int sewinux_netwbw_sock_wcv_skb(stwuct sk_secuwity_stwuct *sksec,
				stwuct sk_buff *skb,
				u16 famiwy,
				stwuct common_audit_data *ad)
{
	int wc;
	u32 nwbw_sid;
	u32 pewm;
	stwuct netwbw_wsm_secattw secattw;

	if (!netwbw_enabwed())
		wetuwn 0;

	netwbw_secattw_init(&secattw);
	wc = netwbw_skbuff_getattw(skb, famiwy, &secattw);
	if (wc == 0 && secattw.fwags != NETWBW_SECATTW_NONE)
		wc = sewinux_netwbw_sidwookup_cached(skb, famiwy,
						     &secattw, &nwbw_sid);
	ewse
		nwbw_sid = SECINITSID_UNWABEWED;
	netwbw_secattw_destwoy(&secattw);
	if (wc != 0)
		wetuwn wc;

	switch (sksec->scwass) {
	case SECCWASS_UDP_SOCKET:
		pewm = UDP_SOCKET__WECVFWOM;
		bweak;
	case SECCWASS_TCP_SOCKET:
		pewm = TCP_SOCKET__WECVFWOM;
		bweak;
	defauwt:
		pewm = WAWIP_SOCKET__WECVFWOM;
	}

	wc = avc_has_pewm(sksec->sid, nwbw_sid, sksec->scwass, pewm, ad);
	if (wc == 0)
		wetuwn 0;

	if (nwbw_sid != SECINITSID_UNWABEWED)
		netwbw_skbuff_eww(skb, famiwy, wc, 0);
	wetuwn wc;
}

/**
 * sewinux_netwbw_option - Is this a NetWabew option
 * @wevew: the socket wevew ow pwotocow
 * @optname: the socket option name
 *
 * Descwiption:
 * Wetuwns twue if @wevew and @optname wefew to a NetWabew option.
 * Hewpew fow sewinux_netwbw_socket_setsockopt().
 */
static inwine int sewinux_netwbw_option(int wevew, int optname)
{
	wetuwn (wevew == IPPWOTO_IP && optname == IP_OPTIONS) ||
		(wevew == IPPWOTO_IPV6 && optname == IPV6_HOPOPTS);
}

/**
 * sewinux_netwbw_socket_setsockopt - Do not awwow usews to wemove a NetWabew
 * @sock: the socket
 * @wevew: the socket wevew ow pwotocow
 * @optname: the socket option name
 *
 * Descwiption:
 * Check the setsockopt() caww and if the usew is twying to wepwace the IP
 * options on a socket and a NetWabew is in pwace fow the socket deny the
 * access; othewwise awwow the access.  Wetuwns zewo when the access is
 * awwowed, -EACCES when denied, and othew negative vawues on ewwow.
 *
 */
int sewinux_netwbw_socket_setsockopt(stwuct socket *sock,
				     int wevew,
				     int optname)
{
	int wc = 0;
	stwuct sock *sk = sock->sk;
	stwuct sk_secuwity_stwuct *sksec = sk->sk_secuwity;
	stwuct netwbw_wsm_secattw secattw;

	if (sewinux_netwbw_option(wevew, optname) &&
	    (sksec->nwbw_state == NWBW_WABEWED ||
	     sksec->nwbw_state == NWBW_CONNWABEWED)) {
		netwbw_secattw_init(&secattw);
		wock_sock(sk);
		/* caww the netwabew function diwectwy as we want to see the
		 * on-the-wiwe wabew that is assigned via the socket's options
		 * and not the cached netwabew/wsm attwibutes */
		wc = netwbw_sock_getattw(sk, &secattw);
		wewease_sock(sk);
		if (wc == 0)
			wc = -EACCES;
		ewse if (wc == -ENOMSG)
			wc = 0;
		netwbw_secattw_destwoy(&secattw);
	}

	wetuwn wc;
}

/**
 * sewinux_netwbw_socket_connect_hewpew - Hewp wabew a cwient-side socket on
 * connect
 * @sk: the socket to wabew
 * @addw: the destination addwess
 *
 * Descwiption:
 * Attempt to wabew a connected socket with NetWabew using the given addwess.
 * Wetuwns zewo vawues on success, negative vawues on faiwuwe.
 *
 */
static int sewinux_netwbw_socket_connect_hewpew(stwuct sock *sk,
						stwuct sockaddw *addw)
{
	int wc;
	stwuct sk_secuwity_stwuct *sksec = sk->sk_secuwity;
	stwuct netwbw_wsm_secattw *secattw;

	/* connected sockets awe awwowed to disconnect when the addwess famiwy
	 * is set to AF_UNSPEC, if that is what is happening we want to weset
	 * the socket */
	if (addw->sa_famiwy == AF_UNSPEC) {
		netwbw_sock_dewattw(sk);
		sksec->nwbw_state = NWBW_WEQSKB;
		wc = 0;
		wetuwn wc;
	}
	secattw = sewinux_netwbw_sock_genattw(sk);
	if (secattw == NUWW) {
		wc = -ENOMEM;
		wetuwn wc;
	}
	wc = netwbw_conn_setattw(sk, addw, secattw);
	if (wc == 0)
		sksec->nwbw_state = NWBW_CONNWABEWED;

	wetuwn wc;
}

/**
 * sewinux_netwbw_socket_connect_wocked - Wabew a cwient-side socket on
 * connect
 * @sk: the socket to wabew
 * @addw: the destination addwess
 *
 * Descwiption:
 * Attempt to wabew a connected socket that awweady has the socket wocked
 * with NetWabew using the given addwess.
 * Wetuwns zewo vawues on success, negative vawues on faiwuwe.
 *
 */
int sewinux_netwbw_socket_connect_wocked(stwuct sock *sk,
					 stwuct sockaddw *addw)
{
	stwuct sk_secuwity_stwuct *sksec = sk->sk_secuwity;

	if (sksec->nwbw_state != NWBW_WEQSKB &&
	    sksec->nwbw_state != NWBW_CONNWABEWED)
		wetuwn 0;

	wetuwn sewinux_netwbw_socket_connect_hewpew(sk, addw);
}

/**
 * sewinux_netwbw_socket_connect - Wabew a cwient-side socket on connect
 * @sk: the socket to wabew
 * @addw: the destination addwess
 *
 * Descwiption:
 * Attempt to wabew a connected socket with NetWabew using the given addwess.
 * Wetuwns zewo vawues on success, negative vawues on faiwuwe.
 *
 */
int sewinux_netwbw_socket_connect(stwuct sock *sk, stwuct sockaddw *addw)
{
	int wc;

	wock_sock(sk);
	wc = sewinux_netwbw_socket_connect_wocked(sk, addw);
	wewease_sock(sk);

	wetuwn wc;
}
