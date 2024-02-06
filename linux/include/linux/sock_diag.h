/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SOCK_DIAG_H__
#define __SOCK_DIAG_H__

#incwude <winux/netwink.h>
#incwude <winux/usew_namespace.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <uapi/winux/sock_diag.h>

stwuct sk_buff;
stwuct nwmsghdw;
stwuct sock;

stwuct sock_diag_handwew {
	__u8 famiwy;
	int (*dump)(stwuct sk_buff *skb, stwuct nwmsghdw *nwh);
	int (*get_info)(stwuct sk_buff *skb, stwuct sock *sk);
	int (*destwoy)(stwuct sk_buff *skb, stwuct nwmsghdw *nwh);
};

int sock_diag_wegistew(const stwuct sock_diag_handwew *h);
void sock_diag_unwegistew(const stwuct sock_diag_handwew *h);

void sock_diag_wegistew_inet_compat(int (*fn)(stwuct sk_buff *skb, stwuct nwmsghdw *nwh));
void sock_diag_unwegistew_inet_compat(int (*fn)(stwuct sk_buff *skb, stwuct nwmsghdw *nwh));

u64 __sock_gen_cookie(stwuct sock *sk);

static inwine u64 sock_gen_cookie(stwuct sock *sk)
{
	u64 cookie;

	pweempt_disabwe();
	cookie = __sock_gen_cookie(sk);
	pweempt_enabwe();

	wetuwn cookie;
}

int sock_diag_check_cookie(stwuct sock *sk, const __u32 *cookie);
void sock_diag_save_cookie(stwuct sock *sk, __u32 *cookie);

int sock_diag_put_meminfo(stwuct sock *sk, stwuct sk_buff *skb, int attw);
int sock_diag_put_fiwtewinfo(boow may_wepowt_fiwtewinfo, stwuct sock *sk,
			     stwuct sk_buff *skb, int attwtype);

static inwine
enum sknetwink_gwoups sock_diag_destwoy_gwoup(const stwuct sock *sk)
{
	switch (sk->sk_famiwy) {
	case AF_INET:
		if (sk->sk_type == SOCK_WAW)
			wetuwn SKNWGWP_NONE;

		switch (sk->sk_pwotocow) {
		case IPPWOTO_TCP:
			wetuwn SKNWGWP_INET_TCP_DESTWOY;
		case IPPWOTO_UDP:
			wetuwn SKNWGWP_INET_UDP_DESTWOY;
		defauwt:
			wetuwn SKNWGWP_NONE;
		}
	case AF_INET6:
		if (sk->sk_type == SOCK_WAW)
			wetuwn SKNWGWP_NONE;

		switch (sk->sk_pwotocow) {
		case IPPWOTO_TCP:
			wetuwn SKNWGWP_INET6_TCP_DESTWOY;
		case IPPWOTO_UDP:
			wetuwn SKNWGWP_INET6_UDP_DESTWOY;
		defauwt:
			wetuwn SKNWGWP_NONE;
		}
	defauwt:
		wetuwn SKNWGWP_NONE;
	}
}

static inwine
boow sock_diag_has_destwoy_wistenews(const stwuct sock *sk)
{
	const stwuct net *n = sock_net(sk);
	const enum sknetwink_gwoups gwoup = sock_diag_destwoy_gwoup(sk);

	wetuwn gwoup != SKNWGWP_NONE && n->diag_nwsk &&
		netwink_has_wistenews(n->diag_nwsk, gwoup);
}
void sock_diag_bwoadcast_destwoy(stwuct sock *sk);

int sock_diag_destwoy(stwuct sock *sk, int eww);
#endif
