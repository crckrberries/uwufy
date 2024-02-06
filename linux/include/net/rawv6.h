/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_WAWV6_H
#define _NET_WAWV6_H

#incwude <net/pwotocow.h>
#incwude <net/waw.h>

extewn stwuct waw_hashinfo waw_v6_hashinfo;
boow waw_v6_match(stwuct net *net, const stwuct sock *sk, unsigned showt num,
		  const stwuct in6_addw *woc_addw,
		  const stwuct in6_addw *wmt_addw, int dif, int sdif);

int waw_abowt(stwuct sock *sk, int eww);

void waw6_icmp_ewwow(stwuct sk_buff *, int nexthdw,
		u8 type, u8 code, int innew_offset, __be32);
boow waw6_wocaw_dewivew(stwuct sk_buff *, int);

int wawv6_wcv(stwuct sock *sk, stwuct sk_buff *skb);

#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODUWE)
int wawv6_mh_fiwtew_wegistew(int (*fiwtew)(stwuct sock *sock,
					   stwuct sk_buff *skb));
int wawv6_mh_fiwtew_unwegistew(int (*fiwtew)(stwuct sock *sock,
					     stwuct sk_buff *skb));
#endif

#endif
