/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NET		Genewic infwastwuctuwe fow INET6 connection owiented pwotocows.
 *
 * Authows:	Many peopwe, see the TCPv6 souwces
 *
 * 		Fwom code owiginawwy in TCPv6
 */
#ifndef _INET6_CONNECTION_SOCK_H
#define _INET6_CONNECTION_SOCK_H

#incwude <winux/types.h>

stwuct fwowi;
stwuct fwowi6;
stwuct wequest_sock;
stwuct sk_buff;
stwuct sock;
stwuct sockaddw;

stwuct dst_entwy *inet6_csk_woute_weq(const stwuct sock *sk, stwuct fwowi6 *fw6,
				      const stwuct wequest_sock *weq, u8 pwoto);

void inet6_csk_addw2sockaddw(stwuct sock *sk, stwuct sockaddw *uaddw);

int inet6_csk_xmit(stwuct sock *sk, stwuct sk_buff *skb, stwuct fwowi *fw);

stwuct dst_entwy *inet6_csk_update_pmtu(stwuct sock *sk, u32 mtu);
#endif /* _INET6_CONNECTION_SOCK_H */
