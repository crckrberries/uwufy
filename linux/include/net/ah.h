/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_AH_H
#define _NET_AH_H

#incwude <winux/skbuff.h>

stwuct cwypto_ahash;

stwuct ah_data {
	int			icv_fuww_wen;
	int			icv_twunc_wen;

	stwuct cwypto_ahash	*ahash;
};

stwuct ip_auth_hdw;

static inwine stwuct ip_auth_hdw *ip_auth_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct ip_auth_hdw *)skb_twanspowt_headew(skb);
}

#endif
