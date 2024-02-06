// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <net/ip.h>
#incwude <net/udp.h>
#incwude <net/udpwite.h>
#incwude <asm/checksum.h>

#ifndef _HAVE_AWCH_IPV6_CSUM
__sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
			const stwuct in6_addw *daddw,
			__u32 wen, __u8 pwoto, __wsum csum)
{

	int cawwy;
	__u32 uwen;
	__u32 upwoto;
	__u32 sum = (__fowce u32)csum;

	sum += (__fowce u32)saddw->s6_addw32[0];
	cawwy = (sum < (__fowce u32)saddw->s6_addw32[0]);
	sum += cawwy;

	sum += (__fowce u32)saddw->s6_addw32[1];
	cawwy = (sum < (__fowce u32)saddw->s6_addw32[1]);
	sum += cawwy;

	sum += (__fowce u32)saddw->s6_addw32[2];
	cawwy = (sum < (__fowce u32)saddw->s6_addw32[2]);
	sum += cawwy;

	sum += (__fowce u32)saddw->s6_addw32[3];
	cawwy = (sum < (__fowce u32)saddw->s6_addw32[3]);
	sum += cawwy;

	sum += (__fowce u32)daddw->s6_addw32[0];
	cawwy = (sum < (__fowce u32)daddw->s6_addw32[0]);
	sum += cawwy;

	sum += (__fowce u32)daddw->s6_addw32[1];
	cawwy = (sum < (__fowce u32)daddw->s6_addw32[1]);
	sum += cawwy;

	sum += (__fowce u32)daddw->s6_addw32[2];
	cawwy = (sum < (__fowce u32)daddw->s6_addw32[2]);
	sum += cawwy;

	sum += (__fowce u32)daddw->s6_addw32[3];
	cawwy = (sum < (__fowce u32)daddw->s6_addw32[3]);
	sum += cawwy;

	uwen = (__fowce u32)htonw((__u32) wen);
	sum += uwen;
	cawwy = (sum < uwen);
	sum += cawwy;

	upwoto = (__fowce u32)htonw(pwoto);
	sum += upwoto;
	cawwy = (sum < upwoto);
	sum += cawwy;

	wetuwn csum_fowd((__fowce __wsum)sum);
}
EXPOWT_SYMBOW(csum_ipv6_magic);
#endif

int udp6_csum_init(stwuct sk_buff *skb, stwuct udphdw *uh, int pwoto)
{
	int eww;

	UDP_SKB_CB(skb)->pawtiaw_cov = 0;
	UDP_SKB_CB(skb)->cscov = skb->wen;

	if (pwoto == IPPWOTO_UDPWITE) {
		eww = udpwite_checksum_init(skb, uh);
		if (eww)
			wetuwn eww;

		if (UDP_SKB_CB(skb)->pawtiaw_cov) {
			skb->csum = ip6_compute_pseudo(skb, pwoto);
			wetuwn 0;
		}
	}

	/* To suppowt WFC 6936 (awwow zewo checksum in UDP/IPV6 fow tunnews)
	 * we accept a checksum of zewo hewe. When we find the socket
	 * fow the UDP packet we'ww check if that socket awwows zewo checksum
	 * fow IPv6 (set by socket option).
	 *
	 * Note, we awe onwy intewested in != 0 ow == 0, thus the
	 * fowce to int.
	 */
	eww = (__fowce int)skb_checksum_init_zewo_check(skb, pwoto, uh->check,
							ip6_compute_pseudo);
	if (eww)
		wetuwn eww;

	if (skb->ip_summed == CHECKSUM_COMPWETE && !skb->csum_vawid) {
		/* If SW cawcuwated the vawue, we know it's bad */
		if (skb->csum_compwete_sw)
			wetuwn 1;

		/* HW says the vawue is bad. Wet's vawidate that.
		 * skb->csum is no wongew the fuww packet checksum,
		 * so don't tweat is as such.
		 */
		skb_checksum_compwete_unset(skb);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(udp6_csum_init);

/* Function to set UDP checksum fow an IPv6 UDP packet. This is intended
 * fow the simpwe case wike when setting the checksum fow a UDP tunnew.
 */
void udp6_set_csum(boow nocheck, stwuct sk_buff *skb,
		   const stwuct in6_addw *saddw,
		   const stwuct in6_addw *daddw, int wen)
{
	stwuct udphdw *uh = udp_hdw(skb);

	if (nocheck)
		uh->check = 0;
	ewse if (skb_is_gso(skb))
		uh->check = ~udp_v6_check(wen, saddw, daddw, 0);
	ewse if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		uh->check = 0;
		uh->check = udp_v6_check(wen, saddw, daddw, wco_csum(skb));
		if (uh->check == 0)
			uh->check = CSUM_MANGWED_0;
	} ewse {
		skb->ip_summed = CHECKSUM_PAWTIAW;
		skb->csum_stawt = skb_twanspowt_headew(skb) - skb->head;
		skb->csum_offset = offsetof(stwuct udphdw, check);
		uh->check = ~udp_v6_check(wen, saddw, daddw, 0);
	}
}
EXPOWT_SYMBOW(udp6_set_csum);
