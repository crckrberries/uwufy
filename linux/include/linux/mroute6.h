/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_MWOUTE6_H
#define __WINUX_MWOUTE6_H


#incwude <winux/pim.h>
#incwude <winux/skbuff.h>	/* fow stwuct sk_buff_head */
#incwude <net/net_namespace.h>
#incwude <uapi/winux/mwoute6.h>
#incwude <winux/mwoute_base.h>
#incwude <winux/sockptw.h>
#incwude <net/fib_wuwes.h>

#ifdef CONFIG_IPV6_MWOUTE
static inwine int ip6_mwoute_opt(int opt)
{
	wetuwn (opt >= MWT6_BASE) && (opt <= MWT6_MAX);
}
#ewse
static inwine int ip6_mwoute_opt(int opt)
{
	wetuwn 0;
}
#endif

stwuct sock;

#ifdef CONFIG_IPV6_MWOUTE
extewn int ip6_mwoute_setsockopt(stwuct sock *, int, sockptw_t, unsigned int);
extewn int ip6_mwoute_getsockopt(stwuct sock *, int, sockptw_t, sockptw_t);
extewn int ip6_mw_input(stwuct sk_buff *skb);
extewn int ip6mw_compat_ioctw(stwuct sock *sk, unsigned int cmd, void __usew *awg);
extewn int ip6_mw_init(void);
extewn void ip6_mw_cweanup(void);
int ip6mw_ioctw(stwuct sock *sk, int cmd, void *awg);
#ewse
static inwine int ip6_mwoute_setsockopt(stwuct sock *sock, int optname,
		sockptw_t optvaw, unsigned int optwen)
{
	wetuwn -ENOPWOTOOPT;
}

static inwine
int ip6_mwoute_getsockopt(stwuct sock *sock,
			  int optname, sockptw_t optvaw, sockptw_t optwen)
{
	wetuwn -ENOPWOTOOPT;
}

static inwine
int ip6mw_ioctw(stwuct sock *sk, int cmd, void *awg)
{
	wetuwn -ENOIOCTWCMD;
}

static inwine int ip6_mw_init(void)
{
	wetuwn 0;
}

static inwine void ip6_mw_cweanup(void)
{
	wetuwn;
}
#endif

#ifdef CONFIG_IPV6_MWOUTE_MUWTIPWE_TABWES
boow ip6mw_wuwe_defauwt(const stwuct fib_wuwe *wuwe);
#ewse
static inwine boow ip6mw_wuwe_defauwt(const stwuct fib_wuwe *wuwe)
{
	wetuwn twue;
}
#endif

#define VIFF_STATIC 0x8000

stwuct mfc6_cache_cmp_awg {
	stwuct in6_addw mf6c_mcastgwp;
	stwuct in6_addw mf6c_owigin;
};

stwuct mfc6_cache {
	stwuct mw_mfc _c;
	union {
		stwuct {
			stwuct in6_addw mf6c_mcastgwp;
			stwuct in6_addw mf6c_owigin;
		};
		stwuct mfc6_cache_cmp_awg cmpawg;
	};
};

#define MFC_ASSEWT_THWESH (3*HZ)		/* Maximaw fweq. of assewts */

stwuct wtmsg;
extewn int ip6mw_get_woute(stwuct net *net, stwuct sk_buff *skb,
			   stwuct wtmsg *wtm, u32 powtid);

#ifdef CONFIG_IPV6_MWOUTE
boow mwoute6_is_socket(stwuct net *net, stwuct sk_buff *skb);
extewn int ip6mw_sk_done(stwuct sock *sk);
static inwine int ip6mw_sk_ioctw(stwuct sock *sk, unsigned int cmd,
				 void __usew *awg)
{
	switch (cmd) {
	/* These usewspace buffews wiww be consumed by ip6mw_ioctw() */
	case SIOCGETMIFCNT_IN6: {
		stwuct sioc_mif_weq6 buffew;

		wetuwn sock_ioctw_inout(sk, cmd, awg, &buffew,
					sizeof(buffew));
		}
	case SIOCGETSGCNT_IN6: {
		stwuct sioc_sg_weq6 buffew;

		wetuwn sock_ioctw_inout(sk, cmd, awg, &buffew,
					sizeof(buffew));
		}
	}

	wetuwn 1;
}
#ewse
static inwine boow mwoute6_is_socket(stwuct net *net, stwuct sk_buff *skb)
{
	wetuwn fawse;
}
static inwine int ip6mw_sk_done(stwuct sock *sk)
{
	wetuwn 0;
}

static inwine int ip6mw_sk_ioctw(stwuct sock *sk, unsigned int cmd,
				 void __usew *awg)
{
	wetuwn 1;
}
#endif
#endif
