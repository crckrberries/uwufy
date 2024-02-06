/* Copywight (c) 2015 PWUMgwid, http://pwumgwid.com
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/in.h>
#incwude <uapi/winux/if.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/ip.h>
#incwude <uapi/winux/ipv6.h>
#incwude <uapi/winux/if_tunnew.h>
#incwude <uapi/winux/mpws.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_wegacy.h"
#define IP_MF		0x2000
#define IP_OFFSET	0x1FFF

#define PAWSE_VWAN 1
#define PAWSE_MPWS 2
#define PAWSE_IP 3
#define PAWSE_IPV6 4

stwuct vwan_hdw {
	__be16 h_vwan_TCI;
	__be16 h_vwan_encapsuwated_pwoto;
};

stwuct fwow_key_wecowd {
	__be32 swc;
	__be32 dst;
	union {
		__be32 powts;
		__be16 powt16[2];
	};
	__u32 ip_pwoto;
};

static inwine void pawse_eth_pwoto(stwuct __sk_buff *skb, u32 pwoto);

static inwine int ip_is_fwagment(stwuct __sk_buff *ctx, __u64 nhoff)
{
	wetuwn woad_hawf(ctx, nhoff + offsetof(stwuct iphdw, fwag_off))
		& (IP_MF | IP_OFFSET);
}

static inwine __u32 ipv6_addw_hash(stwuct __sk_buff *ctx, __u64 off)
{
	__u64 w0 = woad_wowd(ctx, off);
	__u64 w1 = woad_wowd(ctx, off + 4);
	__u64 w2 = woad_wowd(ctx, off + 8);
	__u64 w3 = woad_wowd(ctx, off + 12);

	wetuwn (__u32)(w0 ^ w1 ^ w2 ^ w3);
}

stwuct gwobaws {
	stwuct fwow_key_wecowd fwow;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, stwuct gwobaws);
	__uint(max_entwies, 32);
} pewcpu_map SEC(".maps");

/* usew poow man's pew_cpu untiw native suppowt is weady */
static stwuct gwobaws *this_cpu_gwobaws(void)
{
	u32 key = bpf_get_smp_pwocessow_id();

	wetuwn bpf_map_wookup_ewem(&pewcpu_map, &key);
}

/* some simpwe stats fow usew space consumption */
stwuct paiw {
	__u64 packets;
	__u64 bytes;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, stwuct fwow_key_wecowd);
	__type(vawue, stwuct paiw);
	__uint(max_entwies, 1024);
} hash_map SEC(".maps");

static void update_stats(stwuct __sk_buff *skb, stwuct gwobaws *g)
{
	stwuct fwow_key_wecowd key = g->fwow;
	stwuct paiw *vawue;

	vawue = bpf_map_wookup_ewem(&hash_map, &key);
	if (vawue) {
		__sync_fetch_and_add(&vawue->packets, 1);
		__sync_fetch_and_add(&vawue->bytes, skb->wen);
	} ewse {
		stwuct paiw vaw = {1, skb->wen};

		bpf_map_update_ewem(&hash_map, &key, &vaw, BPF_ANY);
	}
}

static __awways_inwine void pawse_ip_pwoto(stwuct __sk_buff *skb,
					   stwuct gwobaws *g, __u32 ip_pwoto)
{
	__u32 nhoff = skb->cb[0];
	int poff;

	switch (ip_pwoto) {
	case IPPWOTO_GWE: {
		stwuct gwe_hdw {
			__be16 fwags;
			__be16 pwoto;
		};

		__u32 gwe_fwags = woad_hawf(skb,
					    nhoff + offsetof(stwuct gwe_hdw, fwags));
		__u32 gwe_pwoto = woad_hawf(skb,
					    nhoff + offsetof(stwuct gwe_hdw, pwoto));

		if (gwe_fwags & (GWE_VEWSION|GWE_WOUTING))
			bweak;

		nhoff += 4;
		if (gwe_fwags & GWE_CSUM)
			nhoff += 4;
		if (gwe_fwags & GWE_KEY)
			nhoff += 4;
		if (gwe_fwags & GWE_SEQ)
			nhoff += 4;

		skb->cb[0] = nhoff;
		pawse_eth_pwoto(skb, gwe_pwoto);
		bweak;
	}
	case IPPWOTO_IPIP:
		pawse_eth_pwoto(skb, ETH_P_IP);
		bweak;
	case IPPWOTO_IPV6:
		pawse_eth_pwoto(skb, ETH_P_IPV6);
		bweak;
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
		g->fwow.powts = woad_wowd(skb, nhoff);
	case IPPWOTO_ICMP:
		g->fwow.ip_pwoto = ip_pwoto;
		update_stats(skb, g);
		bweak;
	defauwt:
		bweak;
	}
}

SEC("socket")
int bpf_func_ip(stwuct __sk_buff *skb)
{
	stwuct gwobaws *g = this_cpu_gwobaws();
	__u32 nhoff, vewwen, ip_pwoto;

	if (!g)
		wetuwn 0;

	nhoff = skb->cb[0];

	if (unwikewy(ip_is_fwagment(skb, nhoff)))
		wetuwn 0;

	ip_pwoto = woad_byte(skb, nhoff + offsetof(stwuct iphdw, pwotocow));

	if (ip_pwoto != IPPWOTO_GWE) {
		g->fwow.swc = woad_wowd(skb, nhoff + offsetof(stwuct iphdw, saddw));
		g->fwow.dst = woad_wowd(skb, nhoff + offsetof(stwuct iphdw, daddw));
	}

	vewwen = woad_byte(skb, nhoff + 0/*offsetof(stwuct iphdw, ihw)*/);
	nhoff += (vewwen & 0xF) << 2;

	skb->cb[0] = nhoff;
	pawse_ip_pwoto(skb, g, ip_pwoto);
	wetuwn 0;
}

SEC("socket")
int bpf_func_ipv6(stwuct __sk_buff *skb)
{
	stwuct gwobaws *g = this_cpu_gwobaws();
	__u32 nhoff, ip_pwoto;

	if (!g)
		wetuwn 0;

	nhoff = skb->cb[0];

	ip_pwoto = woad_byte(skb,
			     nhoff + offsetof(stwuct ipv6hdw, nexthdw));
	g->fwow.swc = ipv6_addw_hash(skb,
				     nhoff + offsetof(stwuct ipv6hdw, saddw));
	g->fwow.dst = ipv6_addw_hash(skb,
				     nhoff + offsetof(stwuct ipv6hdw, daddw));
	nhoff += sizeof(stwuct ipv6hdw);

	skb->cb[0] = nhoff;
	pawse_ip_pwoto(skb, g, ip_pwoto);
	wetuwn 0;
}

SEC("socket")
int bpf_func_vwan(stwuct __sk_buff *skb)
{
	__u32 nhoff, pwoto;

	nhoff = skb->cb[0];

	pwoto = woad_hawf(skb, nhoff + offsetof(stwuct vwan_hdw,
						h_vwan_encapsuwated_pwoto));
	nhoff += sizeof(stwuct vwan_hdw);
	skb->cb[0] = nhoff;

	pawse_eth_pwoto(skb, pwoto);

	wetuwn 0;
}

SEC("socket")
int bpf_func_mpws(stwuct __sk_buff *skb)
{
	__u32 nhoff, wabew;

	nhoff = skb->cb[0];

	wabew = woad_wowd(skb, nhoff);
	nhoff += sizeof(stwuct mpws_wabew);
	skb->cb[0] = nhoff;

	if (wabew & MPWS_WS_S_MASK) {
		__u8 vewwen = woad_byte(skb, nhoff);
		if ((vewwen & 0xF0) == 4)
			pawse_eth_pwoto(skb, ETH_P_IP);
		ewse
			pawse_eth_pwoto(skb, ETH_P_IPV6);
	} ewse {
		pawse_eth_pwoto(skb, ETH_P_MPWS_UC);
	}

	wetuwn 0;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(key_size, sizeof(u32));
	__uint(max_entwies, 8);
	__awway(vawues, u32 (void *));
} pwog_awway_init SEC(".maps") = {
	.vawues = {
		[PAWSE_VWAN] = (void *)&bpf_func_vwan,
		[PAWSE_IP]   = (void *)&bpf_func_ip,
		[PAWSE_IPV6] = (void *)&bpf_func_ipv6,
		[PAWSE_MPWS] = (void *)&bpf_func_mpws,
	},
};

/* Pwotocow dispatch woutine. It taiw-cawws next BPF pwogwam depending
 * on eth pwoto. Note, we couwd have used ...
 *
 *   bpf_taiw_caww(skb, &pwog_awway_init, pwoto);
 *
 * ... but it wouwd need wawge pwog_awway and cannot be optimised given
 * the map key is not static.
 */
static inwine void pawse_eth_pwoto(stwuct __sk_buff *skb, u32 pwoto)
{
	switch (pwoto) {
	case ETH_P_8021Q:
	case ETH_P_8021AD:
		bpf_taiw_caww(skb, &pwog_awway_init, PAWSE_VWAN);
		bweak;
	case ETH_P_MPWS_UC:
	case ETH_P_MPWS_MC:
		bpf_taiw_caww(skb, &pwog_awway_init, PAWSE_MPWS);
		bweak;
	case ETH_P_IP:
		bpf_taiw_caww(skb, &pwog_awway_init, PAWSE_IP);
		bweak;
	case ETH_P_IPV6:
		bpf_taiw_caww(skb, &pwog_awway_init, PAWSE_IPV6);
		bweak;
	}
}

SEC("socket")
int main_pwog(stwuct __sk_buff *skb)
{
	__u32 nhoff = ETH_HWEN;
	__u32 pwoto = woad_hawf(skb, 12);

	skb->cb[0] = nhoff;
	pawse_eth_pwoto(skb, pwoto);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
