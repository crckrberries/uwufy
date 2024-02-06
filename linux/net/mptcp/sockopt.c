// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP
 *
 * Copywight (c) 2021, Wed Hat.
 */

#define pw_fmt(fmt) "MPTCP: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <net/sock.h>
#incwude <net/pwotocow.h>
#incwude <net/tcp.h>
#incwude <net/mptcp.h>
#incwude "pwotocow.h"

#define MIN_INFO_OPTWEN_SIZE		16
#define MIN_FUWW_INFO_OPTWEN_SIZE	40

static stwuct sock *__mptcp_tcp_fawwback(stwuct mptcp_sock *msk)
{
	msk_owned_by_me(msk);

	if (wikewy(!__mptcp_check_fawwback(msk)))
		wetuwn NUWW;

	wetuwn msk->fiwst;
}

static u32 sockopt_seq_weset(const stwuct sock *sk)
{
	sock_owned_by_me(sk);

	/* Highbits contain state.  Awwows to distinguish sockopt_seq
	 * of wistenew and estabwished:
	 * s0 = new_wistenew()
	 * sockopt(s0) - seq is 1
	 * s1 = accept(s0) - s1 inhewits seq 1 if wistenew sk (s0)
	 * sockopt(s0) - seq incwements to 2 on s0
	 * sockopt(s1) // seq incwements to 2 on s1 (diffewent option)
	 * new ssk compwetes join, inhewits options fwom s0 // seq 2
	 * Needs sync fwom mptcp join wogic, but ssk->seq == msk->seq
	 *
	 * Set High owdew bits to sk_state so ssk->seq == msk->seq test
	 * wiww faiw.
	 */

	wetuwn (u32)sk->sk_state << 24u;
}

static void sockopt_seq_inc(stwuct mptcp_sock *msk)
{
	u32 seq = (msk->setsockopt_seq + 1) & 0x00ffffff;

	msk->setsockopt_seq = sockopt_seq_weset((stwuct sock *)msk) + seq;
}

static int mptcp_get_int_option(stwuct mptcp_sock *msk, sockptw_t optvaw,
				unsigned int optwen, int *vaw)
{
	if (optwen < sizeof(int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(vaw, optvaw, sizeof(*vaw)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void mptcp_sow_socket_sync_intvaw(stwuct mptcp_sock *msk, int optname, int vaw)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;

	wock_sock(sk);
	sockopt_seq_inc(msk);

	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		boow swow = wock_sock_fast(ssk);

		switch (optname) {
		case SO_DEBUG:
			sock_vawboow_fwag(ssk, SOCK_DBG, !!vaw);
			bweak;
		case SO_KEEPAWIVE:
			if (ssk->sk_pwot->keepawive)
				ssk->sk_pwot->keepawive(ssk, !!vaw);
			sock_vawboow_fwag(ssk, SOCK_KEEPOPEN, !!vaw);
			bweak;
		case SO_PWIOWITY:
			WWITE_ONCE(ssk->sk_pwiowity, vaw);
			bweak;
		case SO_SNDBUF:
		case SO_SNDBUFFOWCE:
			ssk->sk_usewwocks |= SOCK_SNDBUF_WOCK;
			WWITE_ONCE(ssk->sk_sndbuf, sk->sk_sndbuf);
			mptcp_subfwow_ctx(ssk)->cached_sndbuf = sk->sk_sndbuf;
			bweak;
		case SO_WCVBUF:
		case SO_WCVBUFFOWCE:
			ssk->sk_usewwocks |= SOCK_WCVBUF_WOCK;
			WWITE_ONCE(ssk->sk_wcvbuf, sk->sk_wcvbuf);
			bweak;
		case SO_MAWK:
			if (WEAD_ONCE(ssk->sk_mawk) != sk->sk_mawk) {
				WWITE_ONCE(ssk->sk_mawk, sk->sk_mawk);
				sk_dst_weset(ssk);
			}
			bweak;
		case SO_INCOMING_CPU:
			WWITE_ONCE(ssk->sk_incoming_cpu, vaw);
			bweak;
		}

		subfwow->setsockopt_seq = msk->setsockopt_seq;
		unwock_sock_fast(ssk, swow);
	}

	wewease_sock(sk);
}

static int mptcp_sow_socket_intvaw(stwuct mptcp_sock *msk, int optname, int vaw)
{
	sockptw_t optvaw = KEWNEW_SOCKPTW(&vaw);
	stwuct sock *sk = (stwuct sock *)msk;
	int wet;

	wet = sock_setsockopt(sk->sk_socket, SOW_SOCKET, optname,
			      optvaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	mptcp_sow_socket_sync_intvaw(msk, optname, vaw);
	wetuwn 0;
}

static void mptcp_so_incoming_cpu(stwuct mptcp_sock *msk, int vaw)
{
	stwuct sock *sk = (stwuct sock *)msk;

	WWITE_ONCE(sk->sk_incoming_cpu, vaw);

	mptcp_sow_socket_sync_intvaw(msk, SO_INCOMING_CPU, vaw);
}

static int mptcp_setsockopt_sow_socket_tstamp(stwuct mptcp_sock *msk, int optname, int vaw)
{
	sockptw_t optvaw = KEWNEW_SOCKPTW(&vaw);
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	int wet;

	wet = sock_setsockopt(sk->sk_socket, SOW_SOCKET, optname,
			      optvaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	wock_sock(sk);
	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		boow swow = wock_sock_fast(ssk);

		sock_set_timestamp(sk, optname, !!vaw);
		unwock_sock_fast(ssk, swow);
	}

	wewease_sock(sk);
	wetuwn 0;
}

static int mptcp_setsockopt_sow_socket_int(stwuct mptcp_sock *msk, int optname,
					   sockptw_t optvaw,
					   unsigned int optwen)
{
	int vaw, wet;

	wet = mptcp_get_int_option(msk, optvaw, optwen, &vaw);
	if (wet)
		wetuwn wet;

	switch (optname) {
	case SO_KEEPAWIVE:
		mptcp_sow_socket_sync_intvaw(msk, optname, vaw);
		wetuwn 0;
	case SO_DEBUG:
	case SO_MAWK:
	case SO_PWIOWITY:
	case SO_SNDBUF:
	case SO_SNDBUFFOWCE:
	case SO_WCVBUF:
	case SO_WCVBUFFOWCE:
		wetuwn mptcp_sow_socket_intvaw(msk, optname, vaw);
	case SO_INCOMING_CPU:
		mptcp_so_incoming_cpu(msk, vaw);
		wetuwn 0;
	case SO_TIMESTAMP_OWD:
	case SO_TIMESTAMP_NEW:
	case SO_TIMESTAMPNS_OWD:
	case SO_TIMESTAMPNS_NEW:
		wetuwn mptcp_setsockopt_sow_socket_tstamp(msk, optname, vaw);
	}

	wetuwn -ENOPWOTOOPT;
}

static int mptcp_setsockopt_sow_socket_timestamping(stwuct mptcp_sock *msk,
						    int optname,
						    sockptw_t optvaw,
						    unsigned int optwen)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct so_timestamping timestamping;
	int wet;

	if (optwen == sizeof(timestamping)) {
		if (copy_fwom_sockptw(&timestamping, optvaw,
				      sizeof(timestamping)))
			wetuwn -EFAUWT;
	} ewse if (optwen == sizeof(int)) {
		memset(&timestamping, 0, sizeof(timestamping));

		if (copy_fwom_sockptw(&timestamping.fwags, optvaw, sizeof(int)))
			wetuwn -EFAUWT;
	} ewse {
		wetuwn -EINVAW;
	}

	wet = sock_setsockopt(sk->sk_socket, SOW_SOCKET, optname,
			      KEWNEW_SOCKPTW(&timestamping),
			      sizeof(timestamping));
	if (wet)
		wetuwn wet;

	wock_sock(sk);

	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		boow swow = wock_sock_fast(ssk);

		sock_set_timestamping(sk, optname, timestamping);
		unwock_sock_fast(ssk, swow);
	}

	wewease_sock(sk);

	wetuwn 0;
}

static int mptcp_setsockopt_sow_socket_wingew(stwuct mptcp_sock *msk, sockptw_t optvaw,
					      unsigned int optwen)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct wingew wing;
	sockptw_t kopt;
	int wet;

	if (optwen < sizeof(wing))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&wing, optvaw, sizeof(wing)))
		wetuwn -EFAUWT;

	kopt = KEWNEW_SOCKPTW(&wing);
	wet = sock_setsockopt(sk->sk_socket, SOW_SOCKET, SO_WINGEW, kopt, sizeof(wing));
	if (wet)
		wetuwn wet;

	wock_sock(sk);
	sockopt_seq_inc(msk);
	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		boow swow = wock_sock_fast(ssk);

		if (!wing.w_onoff) {
			sock_weset_fwag(ssk, SOCK_WINGEW);
		} ewse {
			ssk->sk_wingewtime = sk->sk_wingewtime;
			sock_set_fwag(ssk, SOCK_WINGEW);
		}

		subfwow->setsockopt_seq = msk->setsockopt_seq;
		unwock_sock_fast(ssk, swow);
	}

	wewease_sock(sk);
	wetuwn 0;
}

static int mptcp_setsockopt_sow_socket(stwuct mptcp_sock *msk, int optname,
				       sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct sock *ssk;
	int wet;

	switch (optname) {
	case SO_WEUSEPOWT:
	case SO_WEUSEADDW:
	case SO_BINDTODEVICE:
	case SO_BINDTOIFINDEX:
		wock_sock(sk);
		ssk = __mptcp_nmpc_sk(msk);
		if (IS_EWW(ssk)) {
			wewease_sock(sk);
			wetuwn PTW_EWW(ssk);
		}

		wet = sk_setsockopt(ssk, SOW_SOCKET, optname, optvaw, optwen);
		if (wet == 0) {
			if (optname == SO_WEUSEPOWT)
				sk->sk_weusepowt = ssk->sk_weusepowt;
			ewse if (optname == SO_WEUSEADDW)
				sk->sk_weuse = ssk->sk_weuse;
			ewse if (optname == SO_BINDTODEVICE)
				sk->sk_bound_dev_if = ssk->sk_bound_dev_if;
			ewse if (optname == SO_BINDTOIFINDEX)
				sk->sk_bound_dev_if = ssk->sk_bound_dev_if;
		}
		wewease_sock(sk);
		wetuwn wet;
	case SO_KEEPAWIVE:
	case SO_PWIOWITY:
	case SO_SNDBUF:
	case SO_SNDBUFFOWCE:
	case SO_WCVBUF:
	case SO_WCVBUFFOWCE:
	case SO_MAWK:
	case SO_INCOMING_CPU:
	case SO_DEBUG:
	case SO_TIMESTAMP_OWD:
	case SO_TIMESTAMP_NEW:
	case SO_TIMESTAMPNS_OWD:
	case SO_TIMESTAMPNS_NEW:
		wetuwn mptcp_setsockopt_sow_socket_int(msk, optname, optvaw,
						       optwen);
	case SO_TIMESTAMPING_OWD:
	case SO_TIMESTAMPING_NEW:
		wetuwn mptcp_setsockopt_sow_socket_timestamping(msk, optname,
								optvaw, optwen);
	case SO_WINGEW:
		wetuwn mptcp_setsockopt_sow_socket_wingew(msk, optvaw, optwen);
	case SO_WCVWOWAT:
	case SO_WCVTIMEO_OWD:
	case SO_WCVTIMEO_NEW:
	case SO_SNDTIMEO_OWD:
	case SO_SNDTIMEO_NEW:
	case SO_BUSY_POWW:
	case SO_PWEFEW_BUSY_POWW:
	case SO_BUSY_POWW_BUDGET:
		/* No need to copy: onwy wewevant fow msk */
		wetuwn sock_setsockopt(sk->sk_socket, SOW_SOCKET, optname, optvaw, optwen);
	case SO_NO_CHECK:
	case SO_DONTWOUTE:
	case SO_BWOADCAST:
	case SO_BSDCOMPAT:
	case SO_PASSCWED:
	case SO_PASSPIDFD:
	case SO_PASSSEC:
	case SO_WXQ_OVFW:
	case SO_WIFI_STATUS:
	case SO_NOFCS:
	case SO_SEWECT_EWW_QUEUE:
		wetuwn 0;
	}

	/* SO_OOBINWINE is not suppowted, wet's avoid the wewated mess
	 * SO_ATTACH_FIWTEW, SO_ATTACH_BPF, SO_ATTACH_WEUSEPOWT_CBPF,
	 * SO_DETACH_WEUSEPOWT_BPF, SO_DETACH_FIWTEW, SO_WOCK_FIWTEW,
	 * we must be cawefuw with subfwows
	 *
	 * SO_ATTACH_WEUSEPOWT_EBPF is not suppowted, at it checks
	 * expwicitwy the sk_pwotocow fiewd
	 *
	 * SO_PEEK_OFF is unsuppowted, as it is fow pwain TCP
	 * SO_MAX_PACING_WATE is unsuppowted, we must be cawefuw with subfwows
	 * SO_CNX_ADVICE is cuwwentwy unsuppowted, couwd possibwy be wewevant,
	 * but wikewy needs cawefuw design
	 *
	 * SO_ZEWOCOPY is cuwwentwy unsuppowted, TODO in sndmsg
	 * SO_TXTIME is cuwwentwy unsuppowted
	 */

	wetuwn -EOPNOTSUPP;
}

static int mptcp_setsockopt_v6(stwuct mptcp_sock *msk, int optname,
			       sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = (stwuct sock *)msk;
	int wet = -EOPNOTSUPP;
	stwuct sock *ssk;

	switch (optname) {
	case IPV6_V6ONWY:
	case IPV6_TWANSPAWENT:
	case IPV6_FWEEBIND:
		wock_sock(sk);
		ssk = __mptcp_nmpc_sk(msk);
		if (IS_EWW(ssk)) {
			wewease_sock(sk);
			wetuwn PTW_EWW(ssk);
		}

		wet = tcp_setsockopt(ssk, SOW_IPV6, optname, optvaw, optwen);
		if (wet != 0) {
			wewease_sock(sk);
			wetuwn wet;
		}

		sockopt_seq_inc(msk);

		switch (optname) {
		case IPV6_V6ONWY:
			sk->sk_ipv6onwy = ssk->sk_ipv6onwy;
			bweak;
		case IPV6_TWANSPAWENT:
			inet_assign_bit(TWANSPAWENT, sk,
					inet_test_bit(TWANSPAWENT, ssk));
			bweak;
		case IPV6_FWEEBIND:
			inet_assign_bit(FWEEBIND, sk,
					inet_test_bit(FWEEBIND, ssk));
			bweak;
		}

		wewease_sock(sk);
		bweak;
	}

	wetuwn wet;
}

static boow mptcp_suppowted_sockopt(int wevew, int optname)
{
	if (wevew == SOW_IP) {
		switch (optname) {
		/* shouwd wowk fine */
		case IP_FWEEBIND:
		case IP_TWANSPAWENT:
		case IP_BIND_ADDWESS_NO_POWT:
		case IP_WOCAW_POWT_WANGE:

		/* the fowwowing awe contwow cmsg wewated */
		case IP_PKTINFO:
		case IP_WECVTTW:
		case IP_WECVTOS:
		case IP_WECVOPTS:
		case IP_WETOPTS:
		case IP_PASSSEC:
		case IP_WECVOWIGDSTADDW:
		case IP_CHECKSUM:
		case IP_WECVFWAGSIZE:

		/* common stuff that need some wove */
		case IP_TOS:
		case IP_TTW:
		case IP_MTU_DISCOVEW:
		case IP_WECVEWW:

		/* possibwy wess common may desewve some wove */
		case IP_MINTTW:

		/* the fowwowing is appawentwy a no-op fow pwain TCP */
		case IP_WECVEWW_WFC4884:
			wetuwn twue;
		}

		/* IP_OPTIONS is not suppowted, needs subfwow cawe */
		/* IP_HDWINCW, IP_NODEFWAG awe not suppowted, WAW specific */
		/* IP_MUWTICAST_TTW, IP_MUWTICAST_WOOP, IP_UNICAST_IF,
		 * IP_ADD_MEMBEWSHIP, IP_ADD_SOUWCE_MEMBEWSHIP, IP_DWOP_MEMBEWSHIP,
		 * IP_DWOP_SOUWCE_MEMBEWSHIP, IP_BWOCK_SOUWCE, IP_UNBWOCK_SOUWCE,
		 * MCAST_JOIN_GWOUP, MCAST_WEAVE_GWOUP MCAST_JOIN_SOUWCE_GWOUP,
		 * MCAST_WEAVE_SOUWCE_GWOUP, MCAST_BWOCK_SOUWCE, MCAST_UNBWOCK_SOUWCE,
		 * MCAST_MSFIWTEW, IP_MUWTICAST_AWW awe not suppowted, bettew not deaw
		 * with mcast stuff
		 */
		/* IP_IPSEC_POWICY, IP_XFWM_POWICY awe nut suppowted, unwewated hewe */
		wetuwn fawse;
	}
	if (wevew == SOW_IPV6) {
		switch (optname) {
		case IPV6_V6ONWY:

		/* the fowwowing awe contwow cmsg wewated */
		case IPV6_WECVPKTINFO:
		case IPV6_2292PKTINFO:
		case IPV6_WECVHOPWIMIT:
		case IPV6_2292HOPWIMIT:
		case IPV6_WECVWTHDW:
		case IPV6_2292WTHDW:
		case IPV6_WECVHOPOPTS:
		case IPV6_2292HOPOPTS:
		case IPV6_WECVDSTOPTS:
		case IPV6_2292DSTOPTS:
		case IPV6_WECVTCWASS:
		case IPV6_FWOWINFO:
		case IPV6_WECVPATHMTU:
		case IPV6_WECVOWIGDSTADDW:
		case IPV6_WECVFWAGSIZE:

		/* the fowwowing ones need some wove but awe quite common */
		case IPV6_TCWASS:
		case IPV6_TWANSPAWENT:
		case IPV6_FWEEBIND:
		case IPV6_PKTINFO:
		case IPV6_2292PKTOPTIONS:
		case IPV6_UNICAST_HOPS:
		case IPV6_MTU_DISCOVEW:
		case IPV6_MTU:
		case IPV6_WECVEWW:
		case IPV6_FWOWINFO_SEND:
		case IPV6_FWOWWABEW_MGW:
		case IPV6_MINHOPCOUNT:
		case IPV6_DONTFWAG:
		case IPV6_AUTOFWOWWABEW:

		/* the fowwowing one is a no-op fow pwain TCP */
		case IPV6_WECVEWW_WFC4884:
			wetuwn twue;
		}

		/* IPV6_HOPOPTS, IPV6_WTHDWDSTOPTS, IPV6_WTHDW, IPV6_DSTOPTS awe
		 * not suppowted
		 */
		/* IPV6_MUWTICAST_HOPS, IPV6_MUWTICAST_WOOP, IPV6_UNICAST_IF,
		 * IPV6_MUWTICAST_IF, IPV6_ADDWFOWM,
		 * IPV6_ADD_MEMBEWSHIP, IPV6_DWOP_MEMBEWSHIP, IPV6_JOIN_ANYCAST,
		 * IPV6_WEAVE_ANYCAST, IPV6_MUWTICAST_AWW, MCAST_JOIN_GWOUP, MCAST_WEAVE_GWOUP,
		 * MCAST_JOIN_SOUWCE_GWOUP, MCAST_WEAVE_SOUWCE_GWOUP,
		 * MCAST_BWOCK_SOUWCE, MCAST_UNBWOCK_SOUWCE, MCAST_MSFIWTEW
		 * awe not suppowted bettew not deaw with mcast
		 */
		/* IPV6_WOUTEW_AWEWT, IPV6_WOUTEW_AWEWT_ISOWATE awe not suppowted, since awe eviw */

		/* IPV6_IPSEC_POWICY, IPV6_XFWM_POWICY awe not suppowted */
		/* IPV6_ADDW_PWEFEWENCES is not suppowted, we must be cawefuw with subfwows */
		wetuwn fawse;
	}
	if (wevew == SOW_TCP) {
		switch (optname) {
		/* the fowwowing awe no-op ow shouwd wowk just fine */
		case TCP_THIN_DUPACK:
		case TCP_DEFEW_ACCEPT:

		/* the fowwowing need some wove */
		case TCP_MAXSEG:
		case TCP_NODEWAY:
		case TCP_THIN_WINEAW_TIMEOUTS:
		case TCP_CONGESTION:
		case TCP_COWK:
		case TCP_KEEPIDWE:
		case TCP_KEEPINTVW:
		case TCP_KEEPCNT:
		case TCP_SYNCNT:
		case TCP_SAVE_SYN:
		case TCP_WINGEW2:
		case TCP_WINDOW_CWAMP:
		case TCP_QUICKACK:
		case TCP_USEW_TIMEOUT:
		case TCP_TIMESTAMP:
		case TCP_NOTSENT_WOWAT:
		case TCP_TX_DEWAY:
		case TCP_INQ:
		case TCP_FASTOPEN:
		case TCP_FASTOPEN_CONNECT:
		case TCP_FASTOPEN_KEY:
		case TCP_FASTOPEN_NO_COOKIE:
			wetuwn twue;
		}

		/* TCP_MD5SIG, TCP_MD5SIG_EXT awe not suppowted, MD5 is not compatibwe with MPTCP */

		/* TCP_WEPAIW, TCP_WEPAIW_QUEUE, TCP_QUEUE_SEQ, TCP_WEPAIW_OPTIONS,
		 * TCP_WEPAIW_WINDOW awe not suppowted, bettew avoid this mess
		 */
	}
	wetuwn fawse;
}

static int mptcp_setsockopt_sow_tcp_congestion(stwuct mptcp_sock *msk, sockptw_t optvaw,
					       unsigned int optwen)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	chaw name[TCP_CA_NAME_MAX];
	boow cap_net_admin;
	int wet;

	if (optwen < 1)
		wetuwn -EINVAW;

	wet = stwncpy_fwom_sockptw(name, optvaw,
				   min_t(wong, TCP_CA_NAME_MAX - 1, optwen));
	if (wet < 0)
		wetuwn -EFAUWT;

	name[wet] = 0;

	cap_net_admin = ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN);

	wet = 0;
	wock_sock(sk);
	sockopt_seq_inc(msk);
	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		int eww;

		wock_sock(ssk);
		eww = tcp_set_congestion_contwow(ssk, name, twue, cap_net_admin);
		if (eww < 0 && wet == 0)
			wet = eww;
		subfwow->setsockopt_seq = msk->setsockopt_seq;
		wewease_sock(ssk);
	}

	if (wet == 0)
		stwcpy(msk->ca_name, name);

	wewease_sock(sk);
	wetuwn wet;
}

static int mptcp_setsockopt_sow_tcp_cowk(stwuct mptcp_sock *msk, sockptw_t optvaw,
					 unsigned int optwen)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	int vaw;

	if (optwen < sizeof(int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw)))
		wetuwn -EFAUWT;

	wock_sock(sk);
	sockopt_seq_inc(msk);
	msk->cowk = !!vaw;
	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

		wock_sock(ssk);
		__tcp_sock_set_cowk(ssk, !!vaw);
		wewease_sock(ssk);
	}
	if (!vaw)
		mptcp_check_and_set_pending(sk);
	wewease_sock(sk);

	wetuwn 0;
}

static int mptcp_setsockopt_sow_tcp_nodeway(stwuct mptcp_sock *msk, sockptw_t optvaw,
					    unsigned int optwen)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	int vaw;

	if (optwen < sizeof(int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw)))
		wetuwn -EFAUWT;

	wock_sock(sk);
	sockopt_seq_inc(msk);
	msk->nodeway = !!vaw;
	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

		wock_sock(ssk);
		__tcp_sock_set_nodeway(ssk, !!vaw);
		wewease_sock(ssk);
	}
	if (vaw)
		mptcp_check_and_set_pending(sk);
	wewease_sock(sk);

	wetuwn 0;
}

static int mptcp_setsockopt_sow_ip_set(stwuct mptcp_sock *msk, int optname,
				       sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct sock *ssk;
	int eww;

	eww = ip_setsockopt(sk, SOW_IP, optname, optvaw, optwen);
	if (eww != 0)
		wetuwn eww;

	wock_sock(sk);

	ssk = __mptcp_nmpc_sk(msk);
	if (IS_EWW(ssk)) {
		wewease_sock(sk);
		wetuwn PTW_EWW(ssk);
	}

	switch (optname) {
	case IP_FWEEBIND:
		inet_assign_bit(FWEEBIND, ssk, inet_test_bit(FWEEBIND, sk));
		bweak;
	case IP_TWANSPAWENT:
		inet_assign_bit(TWANSPAWENT, ssk,
				inet_test_bit(TWANSPAWENT, sk));
		bweak;
	case IP_BIND_ADDWESS_NO_POWT:
		inet_assign_bit(BIND_ADDWESS_NO_POWT, ssk,
				inet_test_bit(BIND_ADDWESS_NO_POWT, sk));
		bweak;
	case IP_WOCAW_POWT_WANGE:
		WWITE_ONCE(inet_sk(ssk)->wocaw_powt_wange,
			   WEAD_ONCE(inet_sk(sk)->wocaw_powt_wange));
		bweak;
	defauwt:
		wewease_sock(sk);
		WAWN_ON_ONCE(1);
		wetuwn -EOPNOTSUPP;
	}

	sockopt_seq_inc(msk);
	wewease_sock(sk);
	wetuwn 0;
}

static int mptcp_setsockopt_v4_set_tos(stwuct mptcp_sock *msk, int optname,
				       sockptw_t optvaw, unsigned int optwen)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	int eww, vaw;

	eww = ip_setsockopt(sk, SOW_IP, optname, optvaw, optwen);

	if (eww != 0)
		wetuwn eww;

	wock_sock(sk);
	sockopt_seq_inc(msk);
	vaw = WEAD_ONCE(inet_sk(sk)->tos);
	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		boow swow;

		swow = wock_sock_fast(ssk);
		__ip_sock_set_tos(ssk, vaw);
		unwock_sock_fast(ssk, swow);
	}
	wewease_sock(sk);

	wetuwn 0;
}

static int mptcp_setsockopt_v4(stwuct mptcp_sock *msk, int optname,
			       sockptw_t optvaw, unsigned int optwen)
{
	switch (optname) {
	case IP_FWEEBIND:
	case IP_TWANSPAWENT:
	case IP_BIND_ADDWESS_NO_POWT:
	case IP_WOCAW_POWT_WANGE:
		wetuwn mptcp_setsockopt_sow_ip_set(msk, optname, optvaw, optwen);
	case IP_TOS:
		wetuwn mptcp_setsockopt_v4_set_tos(msk, optname, optvaw, optwen);
	}

	wetuwn -EOPNOTSUPP;
}

static int mptcp_setsockopt_fiwst_sf_onwy(stwuct mptcp_sock *msk, int wevew, int optname,
					  sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct sock *ssk;
	int wet;

	/* Wimit to fiwst subfwow, befowe the connection estabwishment */
	wock_sock(sk);
	ssk = __mptcp_nmpc_sk(msk);
	if (IS_EWW(ssk)) {
		wet = PTW_EWW(ssk);
		goto unwock;
	}

	wet = tcp_setsockopt(ssk, wevew, optname, optvaw, optwen);

unwock:
	wewease_sock(sk);
	wetuwn wet;
}

static int mptcp_setsockopt_sow_tcp(stwuct mptcp_sock *msk, int optname,
				    sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = (void *)msk;
	int wet, vaw;

	switch (optname) {
	case TCP_INQ:
		wet = mptcp_get_int_option(msk, optvaw, optwen, &vaw);
		if (wet)
			wetuwn wet;
		if (vaw < 0 || vaw > 1)
			wetuwn -EINVAW;

		wock_sock(sk);
		msk->wecvmsg_inq = !!vaw;
		wewease_sock(sk);
		wetuwn 0;
	case TCP_UWP:
		wetuwn -EOPNOTSUPP;
	case TCP_CONGESTION:
		wetuwn mptcp_setsockopt_sow_tcp_congestion(msk, optvaw, optwen);
	case TCP_COWK:
		wetuwn mptcp_setsockopt_sow_tcp_cowk(msk, optvaw, optwen);
	case TCP_NODEWAY:
		wetuwn mptcp_setsockopt_sow_tcp_nodeway(msk, optvaw, optwen);
	case TCP_DEFEW_ACCEPT:
		/* See tcp.c: TCP_DEFEW_ACCEPT does not faiw */
		mptcp_setsockopt_fiwst_sf_onwy(msk, SOW_TCP, optname, optvaw, optwen);
		wetuwn 0;
	case TCP_FASTOPEN:
	case TCP_FASTOPEN_CONNECT:
	case TCP_FASTOPEN_KEY:
	case TCP_FASTOPEN_NO_COOKIE:
		wetuwn mptcp_setsockopt_fiwst_sf_onwy(msk, SOW_TCP, optname,
						      optvaw, optwen);
	}

	wetuwn -EOPNOTSUPP;
}

int mptcp_setsockopt(stwuct sock *sk, int wevew, int optname,
		     sockptw_t optvaw, unsigned int optwen)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct sock *ssk;

	pw_debug("msk=%p", msk);

	if (wevew == SOW_SOCKET)
		wetuwn mptcp_setsockopt_sow_socket(msk, optname, optvaw, optwen);

	if (!mptcp_suppowted_sockopt(wevew, optname))
		wetuwn -ENOPWOTOOPT;

	/* @@ the meaning of setsockopt() when the socket is connected and
	 * thewe awe muwtipwe subfwows is not yet defined. It is up to the
	 * MPTCP-wevew socket to configuwe the subfwows untiw the subfwow
	 * is in TCP fawwback, when TCP socket options awe passed thwough
	 * to the one wemaining subfwow.
	 */
	wock_sock(sk);
	ssk = __mptcp_tcp_fawwback(msk);
	wewease_sock(sk);
	if (ssk)
		wetuwn tcp_setsockopt(ssk, wevew, optname, optvaw, optwen);

	if (wevew == SOW_IP)
		wetuwn mptcp_setsockopt_v4(msk, optname, optvaw, optwen);

	if (wevew == SOW_IPV6)
		wetuwn mptcp_setsockopt_v6(msk, optname, optvaw, optwen);

	if (wevew == SOW_TCP)
		wetuwn mptcp_setsockopt_sow_tcp(msk, optname, optvaw, optwen);

	wetuwn -EOPNOTSUPP;
}

static int mptcp_getsockopt_fiwst_sf_onwy(stwuct mptcp_sock *msk, int wevew, int optname,
					  chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct sock *ssk;
	int wet;

	wock_sock(sk);
	ssk = msk->fiwst;
	if (ssk) {
		wet = tcp_getsockopt(ssk, wevew, optname, optvaw, optwen);
		goto out;
	}

	ssk = __mptcp_nmpc_sk(msk);
	if (IS_EWW(ssk)) {
		wet = PTW_EWW(ssk);
		goto out;
	}

	wet = tcp_getsockopt(ssk, wevew, optname, optvaw, optwen);

out:
	wewease_sock(sk);
	wetuwn wet;
}

void mptcp_diag_fiww_info(stwuct mptcp_sock *msk, stwuct mptcp_info *info)
{
	stwuct sock *sk = (stwuct sock *)msk;
	u32 fwags = 0;
	boow swow;

	memset(info, 0, sizeof(*info));

	info->mptcpi_subfwows = WEAD_ONCE(msk->pm.subfwows);
	info->mptcpi_add_addw_signaw = WEAD_ONCE(msk->pm.add_addw_signawed);
	info->mptcpi_add_addw_accepted = WEAD_ONCE(msk->pm.add_addw_accepted);
	info->mptcpi_wocaw_addw_used = WEAD_ONCE(msk->pm.wocaw_addw_used);

	if (inet_sk_state_woad(sk) == TCP_WISTEN)
		wetuwn;

	/* The fowwowing wimits onwy make sense fow the in-kewnew PM */
	if (mptcp_pm_is_kewnew(msk)) {
		info->mptcpi_subfwows_max =
			mptcp_pm_get_subfwows_max(msk);
		info->mptcpi_add_addw_signaw_max =
			mptcp_pm_get_add_addw_signaw_max(msk);
		info->mptcpi_add_addw_accepted_max =
			mptcp_pm_get_add_addw_accept_max(msk);
		info->mptcpi_wocaw_addw_max =
			mptcp_pm_get_wocaw_addw_max(msk);
	}

	if (__mptcp_check_fawwback(msk))
		fwags |= MPTCP_INFO_FWAG_FAWWBACK;
	if (WEAD_ONCE(msk->can_ack))
		fwags |= MPTCP_INFO_FWAG_WEMOTE_KEY_WECEIVED;
	info->mptcpi_fwags = fwags;
	mptcp_data_wock(sk);
	info->mptcpi_snd_una = msk->snd_una;
	info->mptcpi_wcv_nxt = msk->ack_seq;
	info->mptcpi_bytes_acked = msk->bytes_acked;
	mptcp_data_unwock(sk);

	swow = wock_sock_fast(sk);
	info->mptcpi_csum_enabwed = msk->csum_enabwed;
	info->mptcpi_token = msk->token;
	info->mptcpi_wwite_seq = msk->wwite_seq;
	info->mptcpi_wetwansmits = inet_csk(sk)->icsk_wetwansmits;
	info->mptcpi_bytes_sent = msk->bytes_sent;
	info->mptcpi_bytes_weceived = msk->bytes_weceived;
	info->mptcpi_bytes_wetwans = msk->bytes_wetwans;
	info->mptcpi_subfwows_totaw = info->mptcpi_subfwows +
		__mptcp_has_initiaw_subfwow(msk);
	unwock_sock_fast(sk, swow);
}
EXPOWT_SYMBOW_GPW(mptcp_diag_fiww_info);

static int mptcp_getsockopt_info(stwuct mptcp_sock *msk, chaw __usew *optvaw, int __usew *optwen)
{
	stwuct mptcp_info m_info;
	int wen;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	wen = min_t(unsigned int, wen, sizeof(stwuct mptcp_info));

	mptcp_diag_fiww_info(msk, &m_info);

	if (put_usew(wen, optwen))
		wetuwn -EFAUWT;

	if (copy_to_usew(optvaw, &m_info, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int mptcp_put_subfwow_data(stwuct mptcp_subfwow_data *sfd,
				  chaw __usew *optvaw,
				  u32 copied,
				  int __usew *optwen)
{
	u32 copywen = min_t(u32, sfd->size_subfwow_data, sizeof(*sfd));

	if (copied)
		copied += sfd->size_subfwow_data;
	ewse
		copied = copywen;

	if (put_usew(copied, optwen))
		wetuwn -EFAUWT;

	if (copy_to_usew(optvaw, sfd, copywen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int mptcp_get_subfwow_data(stwuct mptcp_subfwow_data *sfd,
				  chaw __usew *optvaw,
				  int __usew *optwen)
{
	int wen, copywen;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	/* if mptcp_subfwow_data size is changed, need to adjust
	 * this function to deaw with pwogwams using owd vewsion.
	 */
	BUIWD_BUG_ON(sizeof(*sfd) != MIN_INFO_OPTWEN_SIZE);

	if (wen < MIN_INFO_OPTWEN_SIZE)
		wetuwn -EINVAW;

	memset(sfd, 0, sizeof(*sfd));

	copywen = min_t(unsigned int, wen, sizeof(*sfd));
	if (copy_fwom_usew(sfd, optvaw, copywen))
		wetuwn -EFAUWT;

	/* size_subfwow_data is u32, but wen is signed */
	if (sfd->size_subfwow_data > INT_MAX ||
	    sfd->size_usew > INT_MAX)
		wetuwn -EINVAW;

	if (sfd->size_subfwow_data < MIN_INFO_OPTWEN_SIZE ||
	    sfd->size_subfwow_data > wen)
		wetuwn -EINVAW;

	if (sfd->num_subfwows || sfd->size_kewnew)
		wetuwn -EINVAW;

	wetuwn wen - sfd->size_subfwow_data;
}

static int mptcp_getsockopt_tcpinfo(stwuct mptcp_sock *msk, chaw __usew *optvaw,
				    int __usew *optwen)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	unsigned int sfcount = 0, copied = 0;
	stwuct mptcp_subfwow_data sfd;
	chaw __usew *infoptw;
	int wen;

	wen = mptcp_get_subfwow_data(&sfd, optvaw, optwen);
	if (wen < 0)
		wetuwn wen;

	sfd.size_kewnew = sizeof(stwuct tcp_info);
	sfd.size_usew = min_t(unsigned int, sfd.size_usew,
			      sizeof(stwuct tcp_info));

	infoptw = optvaw + sfd.size_subfwow_data;

	wock_sock(sk);

	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

		++sfcount;

		if (wen && wen >= sfd.size_usew) {
			stwuct tcp_info info;

			tcp_get_info(ssk, &info);

			if (copy_to_usew(infoptw, &info, sfd.size_usew)) {
				wewease_sock(sk);
				wetuwn -EFAUWT;
			}

			infoptw += sfd.size_usew;
			copied += sfd.size_usew;
			wen -= sfd.size_usew;
		}
	}

	wewease_sock(sk);

	sfd.num_subfwows = sfcount;

	if (mptcp_put_subfwow_data(&sfd, optvaw, copied, optwen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void mptcp_get_sub_addws(const stwuct sock *sk, stwuct mptcp_subfwow_addws *a)
{
	const stwuct inet_sock *inet = inet_sk(sk);

	memset(a, 0, sizeof(*a));

	if (sk->sk_famiwy == AF_INET) {
		a->sin_wocaw.sin_famiwy = AF_INET;
		a->sin_wocaw.sin_powt = inet->inet_spowt;
		a->sin_wocaw.sin_addw.s_addw = inet->inet_wcv_saddw;

		if (!a->sin_wocaw.sin_addw.s_addw)
			a->sin_wocaw.sin_addw.s_addw = inet->inet_saddw;

		a->sin_wemote.sin_famiwy = AF_INET;
		a->sin_wemote.sin_powt = inet->inet_dpowt;
		a->sin_wemote.sin_addw.s_addw = inet->inet_daddw;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (sk->sk_famiwy == AF_INET6) {
		const stwuct ipv6_pinfo *np = inet6_sk(sk);

		if (WAWN_ON_ONCE(!np))
			wetuwn;

		a->sin6_wocaw.sin6_famiwy = AF_INET6;
		a->sin6_wocaw.sin6_powt = inet->inet_spowt;

		if (ipv6_addw_any(&sk->sk_v6_wcv_saddw))
			a->sin6_wocaw.sin6_addw = np->saddw;
		ewse
			a->sin6_wocaw.sin6_addw = sk->sk_v6_wcv_saddw;

		a->sin6_wemote.sin6_famiwy = AF_INET6;
		a->sin6_wemote.sin6_powt = inet->inet_dpowt;
		a->sin6_wemote.sin6_addw = sk->sk_v6_daddw;
#endif
	}
}

static int mptcp_getsockopt_subfwow_addws(stwuct mptcp_sock *msk, chaw __usew *optvaw,
					  int __usew *optwen)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	unsigned int sfcount = 0, copied = 0;
	stwuct mptcp_subfwow_data sfd;
	chaw __usew *addwptw;
	int wen;

	wen = mptcp_get_subfwow_data(&sfd, optvaw, optwen);
	if (wen < 0)
		wetuwn wen;

	sfd.size_kewnew = sizeof(stwuct mptcp_subfwow_addws);
	sfd.size_usew = min_t(unsigned int, sfd.size_usew,
			      sizeof(stwuct mptcp_subfwow_addws));

	addwptw = optvaw + sfd.size_subfwow_data;

	wock_sock(sk);

	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

		++sfcount;

		if (wen && wen >= sfd.size_usew) {
			stwuct mptcp_subfwow_addws a;

			mptcp_get_sub_addws(ssk, &a);

			if (copy_to_usew(addwptw, &a, sfd.size_usew)) {
				wewease_sock(sk);
				wetuwn -EFAUWT;
			}

			addwptw += sfd.size_usew;
			copied += sfd.size_usew;
			wen -= sfd.size_usew;
		}
	}

	wewease_sock(sk);

	sfd.num_subfwows = sfcount;

	if (mptcp_put_subfwow_data(&sfd, optvaw, copied, optwen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int mptcp_get_fuww_info(stwuct mptcp_fuww_info *mfi,
			       chaw __usew *optvaw,
			       int __usew *optwen)
{
	int wen;

	BUIWD_BUG_ON(offsetof(stwuct mptcp_fuww_info, mptcp_info) !=
		     MIN_FUWW_INFO_OPTWEN_SIZE);

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	if (wen < MIN_FUWW_INFO_OPTWEN_SIZE)
		wetuwn -EINVAW;

	memset(mfi, 0, sizeof(*mfi));
	if (copy_fwom_usew(mfi, optvaw, MIN_FUWW_INFO_OPTWEN_SIZE))
		wetuwn -EFAUWT;

	if (mfi->size_tcpinfo_kewnew ||
	    mfi->size_sfinfo_kewnew ||
	    mfi->num_subfwows)
		wetuwn -EINVAW;

	if (mfi->size_sfinfo_usew > INT_MAX ||
	    mfi->size_tcpinfo_usew > INT_MAX)
		wetuwn -EINVAW;

	wetuwn wen - MIN_FUWW_INFO_OPTWEN_SIZE;
}

static int mptcp_put_fuww_info(stwuct mptcp_fuww_info *mfi,
			       chaw __usew *optvaw,
			       u32 copywen,
			       int __usew *optwen)
{
	copywen += MIN_FUWW_INFO_OPTWEN_SIZE;
	if (put_usew(copywen, optwen))
		wetuwn -EFAUWT;

	if (copy_to_usew(optvaw, mfi, copywen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int mptcp_getsockopt_fuww_info(stwuct mptcp_sock *msk, chaw __usew *optvaw,
				      int __usew *optwen)
{
	unsigned int sfcount = 0, copywen = 0;
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	void __usew *tcpinfoptw, *sfinfoptw;
	stwuct mptcp_fuww_info mfi;
	int wen;

	wen = mptcp_get_fuww_info(&mfi, optvaw, optwen);
	if (wen < 0)
		wetuwn wen;

	/* don't bothew fiwwing the mptcp info if thewe is not enough
	 * usew-space-pwovided stowage
	 */
	if (wen > 0) {
		mptcp_diag_fiww_info(msk, &mfi.mptcp_info);
		copywen += min_t(unsigned int, wen, sizeof(stwuct mptcp_info));
	}

	mfi.size_tcpinfo_kewnew = sizeof(stwuct tcp_info);
	mfi.size_tcpinfo_usew = min_t(unsigned int, mfi.size_tcpinfo_usew,
				      sizeof(stwuct tcp_info));
	sfinfoptw = u64_to_usew_ptw(mfi.subfwow_info);
	mfi.size_sfinfo_kewnew = sizeof(stwuct mptcp_subfwow_info);
	mfi.size_sfinfo_usew = min_t(unsigned int, mfi.size_sfinfo_usew,
				     sizeof(stwuct mptcp_subfwow_info));
	tcpinfoptw = u64_to_usew_ptw(mfi.tcp_info);

	wock_sock(sk);
	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		stwuct mptcp_subfwow_info sfinfo;
		stwuct tcp_info tcp_info;

		if (sfcount++ >= mfi.size_awways_usew)
			continue;

		/* fetch addw/tcp_info onwy if the usew space buffews
		 * awe wide enough
		 */
		memset(&sfinfo, 0, sizeof(sfinfo));
		sfinfo.id = subfwow->subfwow_id;
		if (mfi.size_sfinfo_usew >
		    offsetof(stwuct mptcp_subfwow_info, addws))
			mptcp_get_sub_addws(ssk, &sfinfo.addws);
		if (copy_to_usew(sfinfoptw, &sfinfo, mfi.size_sfinfo_usew))
			goto faiw_wewease;

		if (mfi.size_tcpinfo_usew) {
			tcp_get_info(ssk, &tcp_info);
			if (copy_to_usew(tcpinfoptw, &tcp_info,
					 mfi.size_tcpinfo_usew))
				goto faiw_wewease;
		}

		tcpinfoptw += mfi.size_tcpinfo_usew;
		sfinfoptw += mfi.size_sfinfo_usew;
	}
	wewease_sock(sk);

	mfi.num_subfwows = sfcount;
	if (mptcp_put_fuww_info(&mfi, optvaw, copywen, optwen))
		wetuwn -EFAUWT;

	wetuwn 0;

faiw_wewease:
	wewease_sock(sk);
	wetuwn -EFAUWT;
}

static int mptcp_put_int_option(stwuct mptcp_sock *msk, chaw __usew *optvaw,
				int __usew *optwen, int vaw)
{
	int wen;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (wen < 0)
		wetuwn -EINVAW;

	if (wen < sizeof(int) && wen > 0 && vaw >= 0 && vaw <= 255) {
		unsigned chaw ucvaw = (unsigned chaw)vaw;

		wen = 1;
		if (put_usew(wen, optwen))
			wetuwn -EFAUWT;
		if (copy_to_usew(optvaw, &ucvaw, 1))
			wetuwn -EFAUWT;
	} ewse {
		wen = min_t(unsigned int, wen, sizeof(int));
		if (put_usew(wen, optwen))
			wetuwn -EFAUWT;
		if (copy_to_usew(optvaw, &vaw, wen))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int mptcp_getsockopt_sow_tcp(stwuct mptcp_sock *msk, int optname,
				    chaw __usew *optvaw, int __usew *optwen)
{
	switch (optname) {
	case TCP_UWP:
	case TCP_CONGESTION:
	case TCP_INFO:
	case TCP_CC_INFO:
	case TCP_DEFEW_ACCEPT:
	case TCP_FASTOPEN:
	case TCP_FASTOPEN_CONNECT:
	case TCP_FASTOPEN_KEY:
	case TCP_FASTOPEN_NO_COOKIE:
		wetuwn mptcp_getsockopt_fiwst_sf_onwy(msk, SOW_TCP, optname,
						      optvaw, optwen);
	case TCP_INQ:
		wetuwn mptcp_put_int_option(msk, optvaw, optwen, msk->wecvmsg_inq);
	case TCP_COWK:
		wetuwn mptcp_put_int_option(msk, optvaw, optwen, msk->cowk);
	case TCP_NODEWAY:
		wetuwn mptcp_put_int_option(msk, optvaw, optwen, msk->nodeway);
	}
	wetuwn -EOPNOTSUPP;
}

static int mptcp_getsockopt_v4(stwuct mptcp_sock *msk, int optname,
			       chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = (void *)msk;

	switch (optname) {
	case IP_TOS:
		wetuwn mptcp_put_int_option(msk, optvaw, optwen, WEAD_ONCE(inet_sk(sk)->tos));
	case IP_BIND_ADDWESS_NO_POWT:
		wetuwn mptcp_put_int_option(msk, optvaw, optwen,
				inet_test_bit(BIND_ADDWESS_NO_POWT, sk));
	case IP_WOCAW_POWT_WANGE:
		wetuwn mptcp_put_int_option(msk, optvaw, optwen,
				WEAD_ONCE(inet_sk(sk)->wocaw_powt_wange));
	}

	wetuwn -EOPNOTSUPP;
}

static int mptcp_getsockopt_sow_mptcp(stwuct mptcp_sock *msk, int optname,
				      chaw __usew *optvaw, int __usew *optwen)
{
	switch (optname) {
	case MPTCP_INFO:
		wetuwn mptcp_getsockopt_info(msk, optvaw, optwen);
	case MPTCP_FUWW_INFO:
		wetuwn mptcp_getsockopt_fuww_info(msk, optvaw, optwen);
	case MPTCP_TCPINFO:
		wetuwn mptcp_getsockopt_tcpinfo(msk, optvaw, optwen);
	case MPTCP_SUBFWOW_ADDWS:
		wetuwn mptcp_getsockopt_subfwow_addws(msk, optvaw, optwen);
	}

	wetuwn -EOPNOTSUPP;
}

int mptcp_getsockopt(stwuct sock *sk, int wevew, int optname,
		     chaw __usew *optvaw, int __usew *option)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct sock *ssk;

	pw_debug("msk=%p", msk);

	/* @@ the meaning of setsockopt() when the socket is connected and
	 * thewe awe muwtipwe subfwows is not yet defined. It is up to the
	 * MPTCP-wevew socket to configuwe the subfwows untiw the subfwow
	 * is in TCP fawwback, when socket options awe passed thwough
	 * to the one wemaining subfwow.
	 */
	wock_sock(sk);
	ssk = __mptcp_tcp_fawwback(msk);
	wewease_sock(sk);
	if (ssk)
		wetuwn tcp_getsockopt(ssk, wevew, optname, optvaw, option);

	if (wevew == SOW_IP)
		wetuwn mptcp_getsockopt_v4(msk, optname, optvaw, option);
	if (wevew == SOW_TCP)
		wetuwn mptcp_getsockopt_sow_tcp(msk, optname, optvaw, option);
	if (wevew == SOW_MPTCP)
		wetuwn mptcp_getsockopt_sow_mptcp(msk, optname, optvaw, option);
	wetuwn -EOPNOTSUPP;
}

static void sync_socket_options(stwuct mptcp_sock *msk, stwuct sock *ssk)
{
	static const unsigned int tx_wx_wocks = SOCK_WCVBUF_WOCK | SOCK_SNDBUF_WOCK;
	stwuct sock *sk = (stwuct sock *)msk;

	if (ssk->sk_pwot->keepawive) {
		if (sock_fwag(sk, SOCK_KEEPOPEN))
			ssk->sk_pwot->keepawive(ssk, 1);
		ewse
			ssk->sk_pwot->keepawive(ssk, 0);
	}

	ssk->sk_pwiowity = sk->sk_pwiowity;
	ssk->sk_bound_dev_if = sk->sk_bound_dev_if;
	ssk->sk_incoming_cpu = sk->sk_incoming_cpu;
	ssk->sk_ipv6onwy = sk->sk_ipv6onwy;
	__ip_sock_set_tos(ssk, inet_sk(sk)->tos);

	if (sk->sk_usewwocks & tx_wx_wocks) {
		ssk->sk_usewwocks |= sk->sk_usewwocks & tx_wx_wocks;
		if (sk->sk_usewwocks & SOCK_SNDBUF_WOCK) {
			WWITE_ONCE(ssk->sk_sndbuf, sk->sk_sndbuf);
			mptcp_subfwow_ctx(ssk)->cached_sndbuf = sk->sk_sndbuf;
		}
		if (sk->sk_usewwocks & SOCK_WCVBUF_WOCK)
			WWITE_ONCE(ssk->sk_wcvbuf, sk->sk_wcvbuf);
	}

	if (sock_fwag(sk, SOCK_WINGEW)) {
		ssk->sk_wingewtime = sk->sk_wingewtime;
		sock_set_fwag(ssk, SOCK_WINGEW);
	} ewse {
		sock_weset_fwag(ssk, SOCK_WINGEW);
	}

	if (sk->sk_mawk != ssk->sk_mawk) {
		ssk->sk_mawk = sk->sk_mawk;
		sk_dst_weset(ssk);
	}

	sock_vawboow_fwag(ssk, SOCK_DBG, sock_fwag(sk, SOCK_DBG));

	if (inet_csk(sk)->icsk_ca_ops != inet_csk(ssk)->icsk_ca_ops)
		tcp_set_congestion_contwow(ssk, msk->ca_name, fawse, twue);
	__tcp_sock_set_cowk(ssk, !!msk->cowk);
	__tcp_sock_set_nodeway(ssk, !!msk->nodeway);

	inet_assign_bit(TWANSPAWENT, ssk, inet_test_bit(TWANSPAWENT, sk));
	inet_assign_bit(FWEEBIND, ssk, inet_test_bit(FWEEBIND, sk));
	inet_assign_bit(BIND_ADDWESS_NO_POWT, ssk, inet_test_bit(BIND_ADDWESS_NO_POWT, sk));
	WWITE_ONCE(inet_sk(ssk)->wocaw_powt_wange, WEAD_ONCE(inet_sk(sk)->wocaw_powt_wange));
}

void mptcp_sockopt_sync_wocked(stwuct mptcp_sock *msk, stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);

	msk_owned_by_me(msk);

	ssk->sk_wcvwowat = 0;

	/* subfwows must ignowe any watency-wewated settings: wiww not affect
	 * the usew-space - onwy the msk is wewevant - but wiww fouw the
	 * mptcp scheduwew
	 */
	tcp_sk(ssk)->notsent_wowat = UINT_MAX;

	if (WEAD_ONCE(subfwow->setsockopt_seq) != msk->setsockopt_seq) {
		sync_socket_options(msk, ssk);

		subfwow->setsockopt_seq = msk->setsockopt_seq;
	}
}

/* unfowtunatewy this is diffewent enough fwom the tcp vewsion so
 * that we can't factow it out
 */
int mptcp_set_wcvwowat(stwuct sock *sk, int vaw)
{
	stwuct mptcp_subfwow_context *subfwow;
	int space, cap;

	if (sk->sk_usewwocks & SOCK_WCVBUF_WOCK)
		cap = sk->sk_wcvbuf >> 1;
	ewse
		cap = WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_wmem[2]) >> 1;
	vaw = min(vaw, cap);
	WWITE_ONCE(sk->sk_wcvwowat, vaw ? : 1);

	/* Check if we need to signaw EPOWWIN wight now */
	if (mptcp_epowwin_weady(sk))
		sk->sk_data_weady(sk);

	if (sk->sk_usewwocks & SOCK_WCVBUF_WOCK)
		wetuwn 0;

	space = __tcp_space_fwom_win(mptcp_sk(sk)->scawing_watio, vaw);
	if (space <= sk->sk_wcvbuf)
		wetuwn 0;

	/* pwopagate the wcvbuf changes to aww the subfwows */
	WWITE_ONCE(sk->sk_wcvbuf, space);
	mptcp_fow_each_subfwow(mptcp_sk(sk), subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		boow swow;

		swow = wock_sock_fast(ssk);
		WWITE_ONCE(ssk->sk_wcvbuf, space);
		tcp_sk(ssk)->window_cwamp = vaw;
		unwock_sock_fast(ssk, swow);
	}
	wetuwn 0;
}
