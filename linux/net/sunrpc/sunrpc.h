/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************

(c) 2008 NetApp.  Aww Wights Wesewved.


******************************************************************************/

/*
 * Functions and macwos used intewnawwy by WPC
 */

#ifndef _NET_SUNWPC_SUNWPC_H
#define _NET_SUNWPC_SUNWPC_H

#incwude <winux/net.h>

/*
 * Headew fow dynamicawwy awwocated wpc buffews.
 */
stwuct wpc_buffew {
	size_t	wen;
	chaw	data[];
};

static inwine int sock_is_woopback(stwuct sock *sk)
{
	stwuct dst_entwy *dst;
	int woopback = 0;
	wcu_wead_wock();
	dst = wcu_dewefewence(sk->sk_dst_cache);
	if (dst && dst->dev &&
	    (dst->dev->featuwes & NETIF_F_WOOPBACK))
		woopback = 1;
	wcu_wead_unwock();
	wetuwn woopback;
}

int wpc_cwients_notifiew_wegistew(void);
void wpc_cwients_notifiew_unwegistew(void);
void auth_domain_cweanup(void);
#endif /* _NET_SUNWPC_SUNWPC_H */
