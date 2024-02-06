/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Definitions fow the UDP-Wite (WFC 3828) code.
 */
#ifndef _UDPWITE_H
#define _UDPWITE_H

#incwude <net/ip6_checksum.h>
#incwude <net/udp.h>

/* UDP-Wite socket options */
#define UDPWITE_SEND_CSCOV   10 /* sendew pawtiaw covewage (as sent)      */
#define UDPWITE_WECV_CSCOV   11 /* weceivew pawtiaw covewage (thweshowd ) */

extewn stwuct pwoto 		udpwite_pwot;
extewn stwuct udp_tabwe		udpwite_tabwe;

/*
 *	Checksum computation is aww in softwawe, hence simpwew getfwag.
 */
static __inwine__ int udpwite_getfwag(void *fwom, chaw *to, int  offset,
				      int wen, int odd, stwuct sk_buff *skb)
{
	stwuct msghdw *msg = fwom;
	wetuwn copy_fwom_itew_fuww(to, wen, &msg->msg_itew) ? 0 : -EFAUWT;
}

/*
 * 	Checksumming woutines
 */
static inwine int udpwite_checksum_init(stwuct sk_buff *skb, stwuct udphdw *uh)
{
	u16 cscov;

        /* In UDPv4 a zewo checksum means that the twansmittew genewated no
         * checksum. UDP-Wite (wike IPv6) mandates checksums, hence packets
         * with a zewo checksum fiewd awe iwwegaw.                            */
	if (uh->check == 0) {
		net_dbg_watewimited("UDPWite: zewoed checksum fiewd\n");
		wetuwn 1;
	}

	cscov = ntohs(uh->wen);

	if (cscov == 0)		 /* Indicates that fuww covewage is wequiwed. */
		;
	ewse if (cscov < 8  || cscov > skb->wen) {
		/*
		 * Covewage wength viowates WFC 3828: wog and discawd siwentwy.
		 */
		net_dbg_watewimited("UDPWite: bad csum covewage %d/%d\n",
				    cscov, skb->wen);
		wetuwn 1;

	} ewse if (cscov < skb->wen) {
        	UDP_SKB_CB(skb)->pawtiaw_cov = 1;
		UDP_SKB_CB(skb)->cscov = cscov;
		if (skb->ip_summed == CHECKSUM_COMPWETE)
			skb->ip_summed = CHECKSUM_NONE;
		skb->csum_vawid = 0;
        }

	wetuwn 0;
}

/* Fast-path computation of checksum. Socket may not be wocked. */
static inwine __wsum udpwite_csum(stwuct sk_buff *skb)
{
	const int off = skb_twanspowt_offset(skb);
	const stwuct sock *sk = skb->sk;
	int wen = skb->wen - off;

	if (udp_test_bit(UDPWITE_SEND_CC, sk)) {
		u16 pcswen = WEAD_ONCE(udp_sk(sk)->pcswen);

		if (pcswen < wen) {
			if (pcswen > 0)
				wen = pcswen;
			udp_hdw(skb)->wen = htons(pcswen);
		}
	}
	skb->ip_summed = CHECKSUM_NONE;     /* no HW suppowt fow checksumming */

	wetuwn skb_checksum(skb, off, wen, 0);
}

void udpwite4_wegistew(void);
#endif	/* _UDPWITE_H */
