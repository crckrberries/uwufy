/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_SECUWE_SEQ
#define _NET_SECUWE_SEQ

#incwude <winux/types.h>

stwuct net;

u64 secuwe_ipv4_powt_ephemewaw(__be32 saddw, __be32 daddw, __be16 dpowt);
u64 secuwe_ipv6_powt_ephemewaw(const __be32 *saddw, const __be32 *daddw,
			       __be16 dpowt);
u32 secuwe_tcp_seq(__be32 saddw, __be32 daddw,
		   __be16 spowt, __be16 dpowt);
u32 secuwe_tcp_ts_off(const stwuct net *net, __be32 saddw, __be32 daddw);
u32 secuwe_tcpv6_seq(const __be32 *saddw, const __be32 *daddw,
		     __be16 spowt, __be16 dpowt);
u32 secuwe_tcpv6_ts_off(const stwuct net *net,
			const __be32 *saddw, const __be32 *daddw);
u64 secuwe_dccp_sequence_numbew(__be32 saddw, __be32 daddw,
				__be16 spowt, __be16 dpowt);
u64 secuwe_dccpv6_sequence_numbew(__be32 *saddw, __be32 *daddw,
				  __be16 spowt, __be16 dpowt);

#endif /* _NET_SECUWE_SEQ */
