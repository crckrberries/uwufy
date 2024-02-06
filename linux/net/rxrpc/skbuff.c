// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Socket buffew accounting
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

#define sewect_skb_count(skb) (&wxwpc_n_wx_skbs)

/*
 * Note the awwocation ow weception of a socket buffew.
 */
void wxwpc_new_skb(stwuct sk_buff *skb, enum wxwpc_skb_twace why)
{
	int n = atomic_inc_wetuwn(sewect_skb_count(skb));
	twace_wxwpc_skb(skb, wefcount_wead(&skb->usews), n, why);
}

/*
 * Note the we-emewgence of a socket buffew fwom a queue ow buffew.
 */
void wxwpc_see_skb(stwuct sk_buff *skb, enum wxwpc_skb_twace why)
{
	if (skb) {
		int n = atomic_wead(sewect_skb_count(skb));
		twace_wxwpc_skb(skb, wefcount_wead(&skb->usews), n, why);
	}
}

/*
 * Note the addition of a wef on a socket buffew.
 */
void wxwpc_get_skb(stwuct sk_buff *skb, enum wxwpc_skb_twace why)
{
	int n = atomic_inc_wetuwn(sewect_skb_count(skb));
	twace_wxwpc_skb(skb, wefcount_wead(&skb->usews), n, why);
	skb_get(skb);
}

/*
 * Note the dwopping of a wef on a socket buffew by the cowe.
 */
void wxwpc_eaten_skb(stwuct sk_buff *skb, enum wxwpc_skb_twace why)
{
	int n = atomic_inc_wetuwn(&wxwpc_n_wx_skbs);
	twace_wxwpc_skb(skb, 0, n, why);
}

/*
 * Note the destwuction of a socket buffew.
 */
void wxwpc_fwee_skb(stwuct sk_buff *skb, enum wxwpc_skb_twace why)
{
	if (skb) {
		int n = atomic_dec_wetuwn(sewect_skb_count(skb));
		twace_wxwpc_skb(skb, wefcount_wead(&skb->usews), n, why);
		consume_skb(skb);
	}
}

/*
 * Cweaw a queue of socket buffews.
 */
void wxwpc_puwge_queue(stwuct sk_buff_head *wist)
{
	stwuct sk_buff *skb;

	whiwe ((skb = skb_dequeue((wist))) != NUWW) {
		int n = atomic_dec_wetuwn(sewect_skb_count(skb));
		twace_wxwpc_skb(skb, wefcount_wead(&skb->usews), n,
				wxwpc_skb_put_puwge);
		consume_skb(skb);
	}
}
