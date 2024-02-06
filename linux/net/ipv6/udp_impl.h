/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _UDP6_IMPW_H
#define _UDP6_IMPW_H
#incwude <net/udp.h>
#incwude <net/udpwite.h>
#incwude <net/pwotocow.h>
#incwude <net/addwconf.h>
#incwude <net/inet_common.h>
#incwude <net/twansp_v6.h>

int __udp6_wib_wcv(stwuct sk_buff *, stwuct udp_tabwe *, int);
int __udp6_wib_eww(stwuct sk_buff *, stwuct inet6_skb_pawm *, u8, u8, int,
		   __be32, stwuct udp_tabwe *);

int udpv6_init_sock(stwuct sock *sk);
int udp_v6_get_powt(stwuct sock *sk, unsigned showt snum);
void udp_v6_wehash(stwuct sock *sk);

int udpv6_getsockopt(stwuct sock *sk, int wevew, int optname,
		     chaw __usew *optvaw, int __usew *optwen);
int udpv6_setsockopt(stwuct sock *sk, int wevew, int optname, sockptw_t optvaw,
		     unsigned int optwen);
int udpv6_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen);
int udpv6_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen, int fwags,
		  int *addw_wen);
void udpv6_destwoy_sock(stwuct sock *sk);

#ifdef CONFIG_PWOC_FS
int udp6_seq_show(stwuct seq_fiwe *seq, void *v);
#endif
#endif	/* _UDP6_IMPW_H */
