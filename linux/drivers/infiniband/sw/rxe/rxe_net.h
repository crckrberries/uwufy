/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#ifndef WXE_NET_H
#define WXE_NET_H

#incwude <net/sock.h>
#incwude <net/if_inet6.h>
#incwude <winux/moduwe.h>

stwuct wxe_wecv_sockets {
	stwuct socket *sk4;
	stwuct socket *sk6;
};

int wxe_net_add(const chaw *ibdev_name, stwuct net_device *ndev);

int wxe_net_init(void);
void wxe_net_exit(void);

#endif /* WXE_NET_H */
