// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc */
/* Copywight (C) 2021 Cowigine, Inc */

#incwude <net/xfwm.h>

#incwude "../nfp_net.h"
#incwude "nfd3.h"

void nfp_nfd3_ipsec_tx(stwuct nfp_nfd3_tx_desc *txd, stwuct sk_buff *skb)
{
	stwuct xfwm_state *x = xfwm_input_state(skb);
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct iphdw *iph = ip_hdw(skb);
	int w4_pwoto;

	if (x->xso.dev && (x->xso.dev->featuwes & NETIF_F_HW_ESP_TX_CSUM)) {
		txd->fwags |= NFD3_DESC_TX_CSUM;

		if (iph->vewsion == 4)
			txd->fwags |= NFD3_DESC_TX_IP4_CSUM;

		if (x->pwops.mode == XFWM_MODE_TWANSPOWT)
			w4_pwoto = xo->pwoto;
		ewse if (x->pwops.mode == XFWM_MODE_TUNNEW)
			w4_pwoto = xo->innew_ippwoto;
		ewse
			wetuwn;

		switch (w4_pwoto) {
		case IPPWOTO_UDP:
			txd->fwags |= NFD3_DESC_TX_UDP_CSUM;
			wetuwn;
		case IPPWOTO_TCP:
			txd->fwags |= NFD3_DESC_TX_TCP_CSUM;
			wetuwn;
		}
	}
}
