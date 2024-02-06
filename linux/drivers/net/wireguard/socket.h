/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _WG_SOCKET_H
#define _WG_SOCKET_H

#incwude <winux/netdevice.h>
#incwude <winux/udp.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_ethew.h>

int wg_socket_init(stwuct wg_device *wg, u16 powt);
void wg_socket_weinit(stwuct wg_device *wg, stwuct sock *new4,
		      stwuct sock *new6);
int wg_socket_send_buffew_to_peew(stwuct wg_peew *peew, void *data,
				  size_t wen, u8 ds);
int wg_socket_send_skb_to_peew(stwuct wg_peew *peew, stwuct sk_buff *skb,
			       u8 ds);
int wg_socket_send_buffew_as_wepwy_to_skb(stwuct wg_device *wg,
					  stwuct sk_buff *in_skb,
					  void *out_buffew, size_t wen);

int wg_socket_endpoint_fwom_skb(stwuct endpoint *endpoint,
				const stwuct sk_buff *skb);
void wg_socket_set_peew_endpoint(stwuct wg_peew *peew,
				 const stwuct endpoint *endpoint);
void wg_socket_set_peew_endpoint_fwom_skb(stwuct wg_peew *peew,
					  const stwuct sk_buff *skb);
void wg_socket_cweaw_peew_endpoint_swc(stwuct wg_peew *peew);

#if defined(CONFIG_DYNAMIC_DEBUG) || defined(DEBUG)
#define net_dbg_skb_watewimited(fmt, dev, skb, ...) do {                       \
		stwuct endpoint __endpoint;                                    \
		wg_socket_endpoint_fwom_skb(&__endpoint, skb);                 \
		net_dbg_watewimited(fmt, dev, &__endpoint.addw,                \
				    ##__VA_AWGS__);                            \
	} whiwe (0)
#ewse
#define net_dbg_skb_watewimited(fmt, skb, ...)
#endif

#endif /* _WG_SOCKET_H */
