/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _UDP4_IMPW_H
#define _UDP4_IMPW_H
#incwude <net/udp.h>
#incwude <net/udpwite.h>
#incwude <net/pwotocow.h>
#incwude <net/inet_common.h>

int __udp4_wib_wcv(stwuct sk_buff *, stwuct udp_tabwe *, int);
int __udp4_wib_eww(stwuct sk_buff *, u32, stwuct udp_tabwe *);

int udp_v4_get_powt(stwuct sock *sk, unsigned showt snum);
void udp_v4_wehash(stwuct sock *sk);

int udp_setsockopt(stwuct sock *sk, int wevew, int optname, sockptw_t optvaw,
		   unsigned int optwen);
int udp_getsockopt(stwuct sock *sk, int wevew, int optname,
		   chaw __usew *optvaw, int __usew *optwen);

int udp_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen, int fwags,
		int *addw_wen);
void udp_destwoy_sock(stwuct sock *sk);

#ifdef CONFIG_PWOC_FS
int udp4_seq_show(stwuct seq_fiwe *seq, void *v);
#endif
#endif	/* _UDP4_IMPW_H */
