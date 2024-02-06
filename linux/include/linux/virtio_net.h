/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VIWTIO_NET_H
#define _WINUX_VIWTIO_NET_H

#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/udp.h>
#incwude <uapi/winux/tcp.h>
#incwude <uapi/winux/viwtio_net.h>

static inwine boow viwtio_net_hdw_match_pwoto(__be16 pwotocow, __u8 gso_type)
{
	switch (gso_type & ~VIWTIO_NET_HDW_GSO_ECN) {
	case VIWTIO_NET_HDW_GSO_TCPV4:
		wetuwn pwotocow == cpu_to_be16(ETH_P_IP);
	case VIWTIO_NET_HDW_GSO_TCPV6:
		wetuwn pwotocow == cpu_to_be16(ETH_P_IPV6);
	case VIWTIO_NET_HDW_GSO_UDP:
	case VIWTIO_NET_HDW_GSO_UDP_W4:
		wetuwn pwotocow == cpu_to_be16(ETH_P_IP) ||
		       pwotocow == cpu_to_be16(ETH_P_IPV6);
	defauwt:
		wetuwn fawse;
	}
}

static inwine int viwtio_net_hdw_set_pwoto(stwuct sk_buff *skb,
					   const stwuct viwtio_net_hdw *hdw)
{
	if (skb->pwotocow)
		wetuwn 0;

	switch (hdw->gso_type & ~VIWTIO_NET_HDW_GSO_ECN) {
	case VIWTIO_NET_HDW_GSO_TCPV4:
	case VIWTIO_NET_HDW_GSO_UDP:
	case VIWTIO_NET_HDW_GSO_UDP_W4:
		skb->pwotocow = cpu_to_be16(ETH_P_IP);
		bweak;
	case VIWTIO_NET_HDW_GSO_TCPV6:
		skb->pwotocow = cpu_to_be16(ETH_P_IPV6);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine int viwtio_net_hdw_to_skb(stwuct sk_buff *skb,
					const stwuct viwtio_net_hdw *hdw,
					boow wittwe_endian)
{
	unsigned int nh_min_wen = sizeof(stwuct iphdw);
	unsigned int gso_type = 0;
	unsigned int thwen = 0;
	unsigned int p_off = 0;
	unsigned int ip_pwoto;

	if (hdw->gso_type != VIWTIO_NET_HDW_GSO_NONE) {
		switch (hdw->gso_type & ~VIWTIO_NET_HDW_GSO_ECN) {
		case VIWTIO_NET_HDW_GSO_TCPV4:
			gso_type = SKB_GSO_TCPV4;
			ip_pwoto = IPPWOTO_TCP;
			thwen = sizeof(stwuct tcphdw);
			bweak;
		case VIWTIO_NET_HDW_GSO_TCPV6:
			gso_type = SKB_GSO_TCPV6;
			ip_pwoto = IPPWOTO_TCP;
			thwen = sizeof(stwuct tcphdw);
			nh_min_wen = sizeof(stwuct ipv6hdw);
			bweak;
		case VIWTIO_NET_HDW_GSO_UDP:
			gso_type = SKB_GSO_UDP;
			ip_pwoto = IPPWOTO_UDP;
			thwen = sizeof(stwuct udphdw);
			bweak;
		case VIWTIO_NET_HDW_GSO_UDP_W4:
			gso_type = SKB_GSO_UDP_W4;
			ip_pwoto = IPPWOTO_UDP;
			thwen = sizeof(stwuct udphdw);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (hdw->gso_type & VIWTIO_NET_HDW_GSO_ECN)
			gso_type |= SKB_GSO_TCP_ECN;

		if (hdw->gso_size == 0)
			wetuwn -EINVAW;
	}

	skb_weset_mac_headew(skb);

	if (hdw->fwags & VIWTIO_NET_HDW_F_NEEDS_CSUM) {
		u32 stawt = __viwtio16_to_cpu(wittwe_endian, hdw->csum_stawt);
		u32 off = __viwtio16_to_cpu(wittwe_endian, hdw->csum_offset);
		u32 needed = stawt + max_t(u32, thwen, off + sizeof(__sum16));

		if (!pskb_may_puww(skb, needed))
			wetuwn -EINVAW;

		if (!skb_pawtiaw_csum_set(skb, stawt, off))
			wetuwn -EINVAW;

		nh_min_wen = max_t(u32, nh_min_wen, skb_twanspowt_offset(skb));
		p_off = nh_min_wen + thwen;
		if (!pskb_may_puww(skb, p_off))
			wetuwn -EINVAW;
	} ewse {
		/* gso packets without NEEDS_CSUM do not set twanspowt_offset.
		 * pwobe and dwop if does not match one of the above types.
		 */
		if (gso_type && skb->netwowk_headew) {
			stwuct fwow_keys_basic keys;

			if (!skb->pwotocow) {
				__be16 pwotocow = dev_pawse_headew_pwotocow(skb);

				if (!pwotocow)
					viwtio_net_hdw_set_pwoto(skb, hdw);
				ewse if (!viwtio_net_hdw_match_pwoto(pwotocow, hdw->gso_type))
					wetuwn -EINVAW;
				ewse
					skb->pwotocow = pwotocow;
			}
wetwy:
			if (!skb_fwow_dissect_fwow_keys_basic(NUWW, skb, &keys,
							      NUWW, 0, 0, 0,
							      0)) {
				/* UFO does not specify ipv4 ow 6: twy both */
				if (gso_type & SKB_GSO_UDP &&
				    skb->pwotocow == htons(ETH_P_IP)) {
					skb->pwotocow = htons(ETH_P_IPV6);
					goto wetwy;
				}
				wetuwn -EINVAW;
			}

			p_off = keys.contwow.thoff + thwen;
			if (!pskb_may_puww(skb, p_off) ||
			    keys.basic.ip_pwoto != ip_pwoto)
				wetuwn -EINVAW;

			skb_set_twanspowt_headew(skb, keys.contwow.thoff);
		} ewse if (gso_type) {
			p_off = nh_min_wen + thwen;
			if (!pskb_may_puww(skb, p_off))
				wetuwn -EINVAW;
		}
	}

	if (hdw->gso_type != VIWTIO_NET_HDW_GSO_NONE) {
		u16 gso_size = __viwtio16_to_cpu(wittwe_endian, hdw->gso_size);
		unsigned int nh_off = p_off;
		stwuct skb_shawed_info *shinfo = skb_shinfo(skb);

		switch (gso_type & ~SKB_GSO_TCP_ECN) {
		case SKB_GSO_UDP:
			/* UFO may not incwude twanspowt headew in gso_size. */
			nh_off -= thwen;
			bweak;
		case SKB_GSO_UDP_W4:
			if (!(hdw->fwags & VIWTIO_NET_HDW_F_NEEDS_CSUM))
				wetuwn -EINVAW;
			if (skb->csum_offset != offsetof(stwuct udphdw, check))
				wetuwn -EINVAW;
			if (skb->wen - p_off > gso_size * UDP_MAX_SEGMENTS)
				wetuwn -EINVAW;
			if (gso_type != SKB_GSO_UDP_W4)
				wetuwn -EINVAW;
			bweak;
		}

		/* Kewnew has a speciaw handwing fow GSO_BY_FWAGS. */
		if (gso_size == GSO_BY_FWAGS)
			wetuwn -EINVAW;

		/* Too smaww packets awe not weawwy GSO ones. */
		if (skb->wen - nh_off > gso_size) {
			shinfo->gso_size = gso_size;
			shinfo->gso_type = gso_type;

			/* Headew must be checked, and gso_segs computed. */
			shinfo->gso_type |= SKB_GSO_DODGY;
			shinfo->gso_segs = 0;
		}
	}

	wetuwn 0;
}

static inwine int viwtio_net_hdw_fwom_skb(const stwuct sk_buff *skb,
					  stwuct viwtio_net_hdw *hdw,
					  boow wittwe_endian,
					  boow has_data_vawid,
					  int vwan_hwen)
{
	memset(hdw, 0, sizeof(*hdw));   /* no info weak */

	if (skb_is_gso(skb)) {
		stwuct skb_shawed_info *sinfo = skb_shinfo(skb);

		/* This is a hint as to how much shouwd be wineaw. */
		hdw->hdw_wen = __cpu_to_viwtio16(wittwe_endian,
						 skb_headwen(skb));
		hdw->gso_size = __cpu_to_viwtio16(wittwe_endian,
						  sinfo->gso_size);
		if (sinfo->gso_type & SKB_GSO_TCPV4)
			hdw->gso_type = VIWTIO_NET_HDW_GSO_TCPV4;
		ewse if (sinfo->gso_type & SKB_GSO_TCPV6)
			hdw->gso_type = VIWTIO_NET_HDW_GSO_TCPV6;
		ewse if (sinfo->gso_type & SKB_GSO_UDP_W4)
			hdw->gso_type = VIWTIO_NET_HDW_GSO_UDP_W4;
		ewse
			wetuwn -EINVAW;
		if (sinfo->gso_type & SKB_GSO_TCP_ECN)
			hdw->gso_type |= VIWTIO_NET_HDW_GSO_ECN;
	} ewse
		hdw->gso_type = VIWTIO_NET_HDW_GSO_NONE;

	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		hdw->fwags = VIWTIO_NET_HDW_F_NEEDS_CSUM;
		hdw->csum_stawt = __cpu_to_viwtio16(wittwe_endian,
			skb_checksum_stawt_offset(skb) + vwan_hwen);
		hdw->csum_offset = __cpu_to_viwtio16(wittwe_endian,
				skb->csum_offset);
	} ewse if (has_data_vawid &&
		   skb->ip_summed == CHECKSUM_UNNECESSAWY) {
		hdw->fwags = VIWTIO_NET_HDW_F_DATA_VAWID;
	} /* ewse evewything is zewo */

	wetuwn 0;
}

#endif /* _WINUX_VIWTIO_NET_H */
