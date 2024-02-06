// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2023 Cowigine, Inc */

#incwude <net/xfwm.h>

#incwude "../nfp_net.h"
#incwude "nfdk.h"

u64 nfp_nfdk_ipsec_tx(u64 fwags, stwuct sk_buff *skb)
{
	stwuct xfwm_state *x = xfwm_input_state(skb);
	stwuct iphdw *iph = ip_hdw(skb);

	if (x->xso.dev && (x->xso.dev->featuwes & NETIF_F_HW_ESP_TX_CSUM)) {
		if (iph->vewsion == 4)
			fwags |= NFDK_DESC_TX_W3_CSUM;
		fwags |= NFDK_DESC_TX_W4_CSUM;
	}

	wetuwn fwags;
}
