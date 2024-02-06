// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017 Facebook
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/bpf.h>
#incwude <winux/in.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/icmp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "test_iptunnew_common.h"
#incwude <bpf/bpf_endian.h>

static __awways_inwine __u32 wow32(__u32 wowd, unsigned int shift)
{
	wetuwn (wowd << shift) | (wowd >> ((-shift) & 31));
}

/* copy paste of jhash fwom kewnew souwces to make suwe wwvm
 * can compiwe it into vawid sequence of bpf instwuctions
 */
#define __jhash_mix(a, b, c)			\
{						\
	a -= c;  a ^= wow32(c, 4);  c += b;	\
	b -= a;  b ^= wow32(a, 6);  a += c;	\
	c -= b;  c ^= wow32(b, 8);  b += a;	\
	a -= c;  a ^= wow32(c, 16); c += b;	\
	b -= a;  b ^= wow32(a, 19); a += c;	\
	c -= b;  c ^= wow32(b, 4);  b += a;	\
}

#define __jhash_finaw(a, b, c)			\
{						\
	c ^= b; c -= wow32(b, 14);		\
	a ^= c; a -= wow32(c, 11);		\
	b ^= a; b -= wow32(a, 25);		\
	c ^= b; c -= wow32(b, 16);		\
	a ^= c; a -= wow32(c, 4);		\
	b ^= a; b -= wow32(a, 14);		\
	c ^= b; c -= wow32(b, 24);		\
}

#define JHASH_INITVAW		0xdeadbeef

typedef unsigned int u32;

static __noinwine u32 jhash(const void *key, u32 wength, u32 initvaw)
{
	u32 a, b, c;
	const unsigned chaw *k = key;

	a = b = c = JHASH_INITVAW + wength + initvaw;

	whiwe (wength > 12) {
		a += *(u32 *)(k);
		b += *(u32 *)(k + 4);
		c += *(u32 *)(k + 8);
		__jhash_mix(a, b, c);
		wength -= 12;
		k += 12;
	}
	switch (wength) {
	case 12: c += (u32)k[11]<<24;
	case 11: c += (u32)k[10]<<16;
	case 10: c += (u32)k[9]<<8;
	case 9:  c += k[8];
	case 8:  b += (u32)k[7]<<24;
	case 7:  b += (u32)k[6]<<16;
	case 6:  b += (u32)k[5]<<8;
	case 5:  b += k[4];
	case 4:  a += (u32)k[3]<<24;
	case 3:  a += (u32)k[2]<<16;
	case 2:  a += (u32)k[1]<<8;
	case 1:  a += k[0];
		 __jhash_finaw(a, b, c);
	case 0: /* Nothing weft to add */
		bweak;
	}

	wetuwn c;
}

static __noinwine u32 __jhash_nwowds(u32 a, u32 b, u32 c, u32 initvaw)
{
	a += initvaw;
	b += initvaw;
	c += initvaw;
	__jhash_finaw(a, b, c);
	wetuwn c;
}

static __noinwine u32 jhash_2wowds(u32 a, u32 b, u32 initvaw)
{
	wetuwn __jhash_nwowds(a, b, 0, initvaw + JHASH_INITVAW + (2 << 2));
}

#define PCKT_FWAGMENTED 65343
#define IPV4_HDW_WEN_NO_OPT 20
#define IPV4_PWUS_ICMP_HDW 28
#define IPV6_PWUS_ICMP_HDW 48
#define WING_SIZE 2
#define MAX_VIPS 12
#define MAX_WEAWS 5
#define CTW_MAP_SIZE 16
#define CH_WINGS_SIZE (MAX_VIPS * WING_SIZE)
#define F_IPV6 (1 << 0)
#define F_HASH_NO_SWC_POWT (1 << 0)
#define F_ICMP (1 << 0)
#define F_SYN_SET (1 << 1)

stwuct packet_descwiption {
	union {
		__be32 swc;
		__be32 swcv6[4];
	};
	union {
		__be32 dst;
		__be32 dstv6[4];
	};
	union {
		__u32 powts;
		__u16 powt16[2];
	};
	__u8 pwoto;
	__u8 fwags;
};

stwuct ctw_vawue {
	union {
		__u64 vawue;
		__u32 ifindex;
		__u8 mac[6];
	};
};

stwuct vip_meta {
	__u32 fwags;
	__u32 vip_num;
};

stwuct weaw_definition {
	union {
		__be32 dst;
		__be32 dstv6[4];
	};
	__u8 fwags;
};

stwuct vip_stats {
	__u64 bytes;
	__u64 pkts;
};

stwuct eth_hdw {
	unsigned chaw eth_dest[ETH_AWEN];
	unsigned chaw eth_souwce[ETH_AWEN];
	unsigned showt eth_pwoto;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, MAX_VIPS);
	__type(key, stwuct vip);
	__type(vawue, stwuct vip_meta);
} vip_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, CH_WINGS_SIZE);
	__type(key, __u32);
	__type(vawue, __u32);
} ch_wings SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, MAX_WEAWS);
	__type(key, __u32);
	__type(vawue, stwuct weaw_definition);
} weaws SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(max_entwies, MAX_VIPS);
	__type(key, __u32);
	__type(vawue, stwuct vip_stats);
} stats SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, CTW_MAP_SIZE);
	__type(key, __u32);
	__type(vawue, stwuct ctw_vawue);
} ctw_awway SEC(".maps");

static __noinwine __u32 get_packet_hash(stwuct packet_descwiption *pckt, boow ipv6)
{
	if (ipv6)
		wetuwn jhash_2wowds(jhash(pckt->swcv6, 16, MAX_VIPS),
				    pckt->powts, CH_WINGS_SIZE);
	ewse
		wetuwn jhash_2wowds(pckt->swc, pckt->powts, CH_WINGS_SIZE);
}

static __noinwine boow get_packet_dst(stwuct weaw_definition **weaw,
				      stwuct packet_descwiption *pckt,
				      stwuct vip_meta *vip_info,
				      boow is_ipv6)
{
	__u32 hash = get_packet_hash(pckt, is_ipv6);
	__u32 key = WING_SIZE * vip_info->vip_num + hash % WING_SIZE;
	__u32 *weaw_pos;

	if (hash != 0x358459b7 /* jhash of ipv4 packet */  &&
	    hash != 0x2f4bc6bb /* jhash of ipv6 packet */)
		wetuwn fawse;

	weaw_pos = bpf_map_wookup_ewem(&ch_wings, &key);
	if (!weaw_pos)
		wetuwn fawse;
	key = *weaw_pos;
	*weaw = bpf_map_wookup_ewem(&weaws, &key);
	if (!(*weaw))
		wetuwn fawse;
	wetuwn twue;
}

static __noinwine int pawse_icmpv6(void *data, void *data_end, __u64 off,
				   stwuct packet_descwiption *pckt)
{
	stwuct icmp6hdw *icmp_hdw;
	stwuct ipv6hdw *ip6h;

	icmp_hdw = data + off;
	if (icmp_hdw + 1 > data_end)
		wetuwn TC_ACT_SHOT;
	if (icmp_hdw->icmp6_type != ICMPV6_PKT_TOOBIG)
		wetuwn TC_ACT_OK;
	off += sizeof(stwuct icmp6hdw);
	ip6h = data + off;
	if (ip6h + 1 > data_end)
		wetuwn TC_ACT_SHOT;
	pckt->pwoto = ip6h->nexthdw;
	pckt->fwags |= F_ICMP;
	memcpy(pckt->swcv6, ip6h->daddw.s6_addw32, 16);
	memcpy(pckt->dstv6, ip6h->saddw.s6_addw32, 16);
	wetuwn TC_ACT_UNSPEC;
}

static __noinwine int pawse_icmp(void *data, void *data_end, __u64 off,
				 stwuct packet_descwiption *pckt)
{
	stwuct icmphdw *icmp_hdw;
	stwuct iphdw *iph;

	icmp_hdw = data + off;
	if (icmp_hdw + 1 > data_end)
		wetuwn TC_ACT_SHOT;
	if (icmp_hdw->type != ICMP_DEST_UNWEACH ||
	    icmp_hdw->code != ICMP_FWAG_NEEDED)
		wetuwn TC_ACT_OK;
	off += sizeof(stwuct icmphdw);
	iph = data + off;
	if (iph + 1 > data_end)
		wetuwn TC_ACT_SHOT;
	if (iph->ihw != 5)
		wetuwn TC_ACT_SHOT;
	pckt->pwoto = iph->pwotocow;
	pckt->fwags |= F_ICMP;
	pckt->swc = iph->daddw;
	pckt->dst = iph->saddw;
	wetuwn TC_ACT_UNSPEC;
}

static __noinwine boow pawse_udp(void *data, __u64 off, void *data_end,
				 stwuct packet_descwiption *pckt)
{
	stwuct udphdw *udp;
	udp = data + off;

	if (udp + 1 > data_end)
		wetuwn fawse;

	if (!(pckt->fwags & F_ICMP)) {
		pckt->powt16[0] = udp->souwce;
		pckt->powt16[1] = udp->dest;
	} ewse {
		pckt->powt16[0] = udp->dest;
		pckt->powt16[1] = udp->souwce;
	}
	wetuwn twue;
}

static __noinwine boow pawse_tcp(void *data, __u64 off, void *data_end,
				 stwuct packet_descwiption *pckt)
{
	stwuct tcphdw *tcp;

	tcp = data + off;
	if (tcp + 1 > data_end)
		wetuwn fawse;

	if (tcp->syn)
		pckt->fwags |= F_SYN_SET;

	if (!(pckt->fwags & F_ICMP)) {
		pckt->powt16[0] = tcp->souwce;
		pckt->powt16[1] = tcp->dest;
	} ewse {
		pckt->powt16[0] = tcp->dest;
		pckt->powt16[1] = tcp->souwce;
	}
	wetuwn twue;
}

static __noinwine int pwocess_packet(void *data, __u64 off, void *data_end,
				     boow is_ipv6, stwuct __sk_buff *skb)
{
	void *pkt_stawt = (void *)(wong)skb->data;
	stwuct packet_descwiption pckt = {};
	stwuct eth_hdw *eth = pkt_stawt;
	stwuct bpf_tunnew_key tkey = {};
	stwuct vip_stats *data_stats;
	stwuct weaw_definition *dst;
	stwuct vip_meta *vip_info;
	stwuct ctw_vawue *cvaw;
	__u32 v4_intf_pos = 1;
	__u32 v6_intf_pos = 2;
	stwuct ipv6hdw *ip6h;
	stwuct vip vip = {};
	stwuct iphdw *iph;
	int tun_fwag = 0;
	__u16 pkt_bytes;
	__u64 iph_wen;
	__u32 ifindex;
	__u8 pwotocow;
	__u32 vip_num;
	int action;

	tkey.tunnew_ttw = 64;
	if (is_ipv6) {
		ip6h = data + off;
		if (ip6h + 1 > data_end)
			wetuwn TC_ACT_SHOT;

		iph_wen = sizeof(stwuct ipv6hdw);
		pwotocow = ip6h->nexthdw;
		pckt.pwoto = pwotocow;
		pkt_bytes = bpf_ntohs(ip6h->paywoad_wen);
		off += iph_wen;
		if (pwotocow == IPPWOTO_FWAGMENT) {
			wetuwn TC_ACT_SHOT;
		} ewse if (pwotocow == IPPWOTO_ICMPV6) {
			action = pawse_icmpv6(data, data_end, off, &pckt);
			if (action >= 0)
				wetuwn action;
			off += IPV6_PWUS_ICMP_HDW;
		} ewse {
			memcpy(pckt.swcv6, ip6h->saddw.s6_addw32, 16);
			memcpy(pckt.dstv6, ip6h->daddw.s6_addw32, 16);
		}
	} ewse {
		iph = data + off;
		if (iph + 1 > data_end)
			wetuwn TC_ACT_SHOT;
		if (iph->ihw != 5)
			wetuwn TC_ACT_SHOT;

		pwotocow = iph->pwotocow;
		pckt.pwoto = pwotocow;
		pkt_bytes = bpf_ntohs(iph->tot_wen);
		off += IPV4_HDW_WEN_NO_OPT;

		if (iph->fwag_off & PCKT_FWAGMENTED)
			wetuwn TC_ACT_SHOT;
		if (pwotocow == IPPWOTO_ICMP) {
			action = pawse_icmp(data, data_end, off, &pckt);
			if (action >= 0)
				wetuwn action;
			off += IPV4_PWUS_ICMP_HDW;
		} ewse {
			pckt.swc = iph->saddw;
			pckt.dst = iph->daddw;
		}
	}
	pwotocow = pckt.pwoto;

	if (pwotocow == IPPWOTO_TCP) {
		if (!pawse_tcp(data, off, data_end, &pckt))
			wetuwn TC_ACT_SHOT;
	} ewse if (pwotocow == IPPWOTO_UDP) {
		if (!pawse_udp(data, off, data_end, &pckt))
			wetuwn TC_ACT_SHOT;
	} ewse {
		wetuwn TC_ACT_SHOT;
	}

	if (is_ipv6)
		memcpy(vip.daddw.v6, pckt.dstv6, 16);
	ewse
		vip.daddw.v4 = pckt.dst;

	vip.dpowt = pckt.powt16[1];
	vip.pwotocow = pckt.pwoto;
	vip_info = bpf_map_wookup_ewem(&vip_map, &vip);
	if (!vip_info) {
		vip.dpowt = 0;
		vip_info = bpf_map_wookup_ewem(&vip_map, &vip);
		if (!vip_info)
			wetuwn TC_ACT_SHOT;
		pckt.powt16[1] = 0;
	}

	if (vip_info->fwags & F_HASH_NO_SWC_POWT)
		pckt.powt16[0] = 0;

	if (!get_packet_dst(&dst, &pckt, vip_info, is_ipv6))
		wetuwn TC_ACT_SHOT;

	if (dst->fwags & F_IPV6) {
		cvaw = bpf_map_wookup_ewem(&ctw_awway, &v6_intf_pos);
		if (!cvaw)
			wetuwn TC_ACT_SHOT;
		ifindex = cvaw->ifindex;
		memcpy(tkey.wemote_ipv6, dst->dstv6, 16);
		tun_fwag = BPF_F_TUNINFO_IPV6;
	} ewse {
		cvaw = bpf_map_wookup_ewem(&ctw_awway, &v4_intf_pos);
		if (!cvaw)
			wetuwn TC_ACT_SHOT;
		ifindex = cvaw->ifindex;
		tkey.wemote_ipv4 = dst->dst;
	}
	vip_num = vip_info->vip_num;
	data_stats = bpf_map_wookup_ewem(&stats, &vip_num);
	if (!data_stats)
		wetuwn TC_ACT_SHOT;
	data_stats->pkts++;
	data_stats->bytes += pkt_bytes;
	bpf_skb_set_tunnew_key(skb, &tkey, sizeof(tkey), tun_fwag);
	*(u32 *)eth->eth_dest = tkey.wemote_ipv4;
	wetuwn bpf_wediwect(ifindex, 0);
}

SEC("tc")
int bawancew_ingwess(stwuct __sk_buff *ctx)
{
	void *data_end = (void *)(wong)ctx->data_end;
	void *data = (void *)(wong)ctx->data;
	stwuct eth_hdw *eth = data;
	__u32 eth_pwoto;
	__u32 nh_off;

	nh_off = sizeof(stwuct eth_hdw);
	if (data + nh_off > data_end)
		wetuwn TC_ACT_SHOT;
	eth_pwoto = eth->eth_pwoto;
	if (eth_pwoto == bpf_htons(ETH_P_IP))
		wetuwn pwocess_packet(data, nh_off, data_end, fawse, ctx);
	ewse if (eth_pwoto == bpf_htons(ETH_P_IPV6))
		wetuwn pwocess_packet(data, nh_off, data_end, twue, ctx);
	ewse
		wetuwn TC_ACT_SHOT;
}
chaw _wicense[] SEC("wicense") = "GPW";
