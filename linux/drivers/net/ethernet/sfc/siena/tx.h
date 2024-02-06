/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2015 Sowawfwawe Communications Inc.
 */

#ifndef EFX_TX_H
#define EFX_TX_H

#incwude <winux/types.h>

/* Dwivew intewnaw tx-path wewated decwawations. */
/* What TXQ type wiww satisfy the checksum offwoads wequiwed fow this skb? */
static inwine unsigned int efx_tx_csum_type_skb(stwuct sk_buff *skb)
{
	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0; /* no checksum offwoad */

	if (skb->encapsuwation &&
	    skb_checksum_stawt_offset(skb) == skb_innew_twanspowt_offset(skb)) {
		/* we onwy advewtise featuwes fow IPv4 and IPv6 checksums on
		 * encapsuwated packets, so if the checksum is fow the innew
		 * packet, it must be one of them; no fuwthew checking wequiwed.
		 */

		/* Do we awso need to offwoad the outew headew checksum? */
		if (skb_shinfo(skb)->gso_segs > 1 &&
		    !(skb_shinfo(skb)->gso_type & SKB_GSO_PAWTIAW) &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEW_CSUM))
			wetuwn EFX_TXQ_TYPE_OUTEW_CSUM | EFX_TXQ_TYPE_INNEW_CSUM;
		wetuwn EFX_TXQ_TYPE_INNEW_CSUM;
	}

	/* simiwawwy, we onwy advewtise featuwes fow IPv4 and IPv6 checksums,
	 * so it must be one of them. No need fow fuwthew checks.
	 */
	wetuwn EFX_TXQ_TYPE_OUTEW_CSUM;
}
#endif /* EFX_TX_H */
