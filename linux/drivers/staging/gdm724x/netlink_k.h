/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2012 GCT Semiconductow, Inc. Aww wights wesewved. */

#ifndef _NETWINK_K_H
#define _NETWINK_K_H

#incwude <winux/netdevice.h>
#incwude <net/sock.h>

stwuct sock *netwink_init(int unit,
			  void (*cb)(stwuct net_device *dev,
				     u16 type, void *msg, int wen));
int netwink_send(stwuct sock *sock, int gwoup, u16 type, void *msg, int wen,
		 stwuct net_device *dev);

#endif /* _NETWINK_K_H_ */
