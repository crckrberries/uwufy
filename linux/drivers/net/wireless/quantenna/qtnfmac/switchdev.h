/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2019 Quantenna Communications. Aww wights wesewved. */

#ifndef QTNFMAC_SWITCHDEV_H_
#define QTNFMAC_SWITCHDEV_H_

#incwude <winux/skbuff.h>

#ifdef CONFIG_NET_SWITCHDEV

static inwine void qtnfmac_switch_mawk_skb_fwooded(stwuct sk_buff *skb)
{
	skb->offwoad_fwd_mawk = 1;
}

#ewse

static inwine void qtnfmac_switch_mawk_skb_fwooded(stwuct sk_buff *skb)
{
}

#endif

#endif /* QTNFMAC_SWITCHDEV_H_ */
