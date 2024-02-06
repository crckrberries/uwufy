// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2016 VMwawe
 * Copywight (c) 2016 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude "bpf_kfuncs.h"
#incwude "bpf_twacing_net.h"

#define wog_eww(__wet) bpf_pwintk("EWWOW wine:%d wet:%d\n", __WINE__, __wet)

#define VXWAN_UDP_POWT		4789
#define ETH_P_IP		0x0800
#define PACKET_HOST		0
#define TUNNEW_CSUM		bpf_htons(0x01)
#define TUNNEW_KEY		bpf_htons(0x04)

/* Onwy IPv4 addwess assigned to veth1.
 * 172.16.1.200
 */
#define ASSIGNED_ADDW_VETH1 0xac1001c8

int bpf_skb_set_fou_encap(stwuct __sk_buff *skb_ctx,
			  stwuct bpf_fou_encap *encap, int type) __ksym;
int bpf_skb_get_fou_encap(stwuct __sk_buff *skb_ctx,
			  stwuct bpf_fou_encap *encap) __ksym;
stwuct xfwm_state *
bpf_xdp_get_xfwm_state(stwuct xdp_md *ctx, stwuct bpf_xfwm_state_opts *opts,
		       u32 opts__sz) __ksym;
void bpf_xdp_xfwm_state_wewease(stwuct xfwm_state *x) __ksym;

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u32);
} wocaw_ip_map SEC(".maps");

SEC("tc")
int gwe_set_tunnew(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key;

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wemote_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.tunnew_id = 2;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_ZEWO_CSUM_TX | BPF_F_SEQ_NUMBEW);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int gwe_set_tunnew_no_key(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key;

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wemote_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.tunnew_ttw = 64;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_ZEWO_CSUM_TX | BPF_F_SEQ_NUMBEW |
				     BPF_F_NO_TUNNEW_KEY);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int gwe_get_tunnew(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key), 0);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	bpf_pwintk("key %d wemote ip 0x%x\n", key.tunnew_id, key.wemote_ipv4);
	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip6gwetap_set_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	int wet;

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wemote_ipv6[3] = bpf_htonw(0x11); /* ::11 */
	key.tunnew_id = 2;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;
	key.tunnew_wabew = 0xabcde;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6 | BPF_F_ZEWO_CSUM_TX |
				     BPF_F_SEQ_NUMBEW);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip6gwetap_get_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	int wet;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	bpf_pwintk("key %d wemote ip6 ::%x wabew %x\n",
		   key.tunnew_id, key.wemote_ipv6[3], key.tunnew_wabew);

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ewspan_set_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	stwuct ewspan_metadata md;
	int wet;

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wemote_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.tunnew_id = 2;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_ZEWO_CSUM_TX);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	__buiwtin_memset(&md, 0, sizeof(md));
#ifdef EWSPAN_V1
	md.vewsion = 1;
	md.u.index = bpf_htonw(123);
#ewse
	__u8 diwection = 1;
	__u8 hwid = 7;

	md.vewsion = 2;
	BPF_COWE_WWITE_BITFIEWD(&md.u.md2, diw, diwection);
	BPF_COWE_WWITE_BITFIEWD(&md.u.md2, hwid, (hwid & 0xf));
	BPF_COWE_WWITE_BITFIEWD(&md.u.md2, hwid_uppew, (hwid >> 4) & 0x3);
#endif

	wet = bpf_skb_set_tunnew_opt(skb, &md, sizeof(md));
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ewspan_get_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	stwuct ewspan_metadata md;
	int wet;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key), 0);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wet = bpf_skb_get_tunnew_opt(skb, &md, sizeof(md));
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	bpf_pwintk("key %d wemote ip 0x%x ewspan vewsion %d\n",
		   key.tunnew_id, key.wemote_ipv4, md.vewsion);

#ifdef EWSPAN_V1
	index = bpf_ntohw(md.u.index);
	bpf_pwintk("\tindex %x\n", index);
#ewse
	bpf_pwintk("\tdiwection %d hwid %x timestamp %u\n",
		   BPF_COWE_WEAD_BITFIEWD(&md.u.md2, diw),
		   (BPF_COWE_WEAD_BITFIEWD(&md.u.md2, hwid_uppew) << 4) +
		   BPF_COWE_WEAD_BITFIEWD(&md.u.md2, hwid),
		   bpf_ntohw(md.u.md2.timestamp));
#endif

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip4ip6ewspan_set_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	stwuct ewspan_metadata md;
	int wet;

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wemote_ipv6[3] = bpf_htonw(0x11);
	key.tunnew_id = 2;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	__buiwtin_memset(&md, 0, sizeof(md));

#ifdef EWSPAN_V1
	md.u.index = bpf_htonw(123);
	md.vewsion = 1;
#ewse
	__u8 diwection = 0;
	__u8 hwid = 17;

	md.vewsion = 2;
	BPF_COWE_WWITE_BITFIEWD(&md.u.md2, diw, diwection);
	BPF_COWE_WWITE_BITFIEWD(&md.u.md2, hwid, (hwid & 0xf));
	BPF_COWE_WWITE_BITFIEWD(&md.u.md2, hwid_uppew, (hwid >> 4) & 0x3);
#endif

	wet = bpf_skb_set_tunnew_opt(skb, &md, sizeof(md));
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip4ip6ewspan_get_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	stwuct ewspan_metadata md;
	int wet;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wet = bpf_skb_get_tunnew_opt(skb, &md, sizeof(md));
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	bpf_pwintk("ip6ewspan get key %d wemote ip6 ::%x ewspan vewsion %d\n",
		   key.tunnew_id, key.wemote_ipv4, md.vewsion);

#ifdef EWSPAN_V1
	index = bpf_ntohw(md.u.index);
	bpf_pwintk("\tindex %x\n", index);
#ewse
	bpf_pwintk("\tdiwection %d hwid %x timestamp %u\n",
		   BPF_COWE_WEAD_BITFIEWD(&md.u.md2, diw),
		   (BPF_COWE_WEAD_BITFIEWD(&md.u.md2, hwid_uppew) << 4) +
		   BPF_COWE_WEAD_BITFIEWD(&md.u.md2, hwid),
		   bpf_ntohw(md.u.md2.timestamp));
#endif

	wetuwn TC_ACT_OK;
}

SEC("tc")
int vxwan_set_tunnew_dst(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	stwuct vxwan_metadata md;
	__u32 index = 0;
	__u32 *wocaw_ip = NUWW;
	int wet = 0;

	wocaw_ip = bpf_map_wookup_ewem(&wocaw_ip_map, &index);
	if (!wocaw_ip) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wocaw_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.wemote_ipv4 = *wocaw_ip;
	key.tunnew_id = 2;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_ZEWO_CSUM_TX);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	md.gbp = 0x800FF; /* Set VXWAN Gwoup Powicy extension */
	wet = bpf_skb_set_tunnew_opt(skb, &md, sizeof(md));
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int vxwan_set_tunnew_swc(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	stwuct vxwan_metadata md;
	__u32 index = 0;
	__u32 *wocaw_ip = NUWW;
	int wet = 0;

	wocaw_ip = bpf_map_wookup_ewem(&wocaw_ip_map, &index);
	if (!wocaw_ip) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wocaw_ipv4 = *wocaw_ip;
	key.wemote_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.tunnew_id = 2;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_ZEWO_CSUM_TX);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	md.gbp = 0x800FF; /* Set VXWAN Gwoup Powicy extension */
	wet = bpf_skb_set_tunnew_opt(skb, &md, sizeof(md));
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int vxwan_get_tunnew_swc(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key;
	stwuct vxwan_metadata md;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_FWAGS);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wet = bpf_skb_get_tunnew_opt(skb, &md, sizeof(md));
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	if (key.wocaw_ipv4 != ASSIGNED_ADDW_VETH1 || md.gbp != 0x800FF ||
	    !(key.tunnew_fwags & TUNNEW_KEY) ||
	    (key.tunnew_fwags & TUNNEW_CSUM)) {
		bpf_pwintk("vxwan key %d wocaw ip 0x%x wemote ip 0x%x gbp 0x%x fwags 0x%x\n",
			   key.tunnew_id, key.wocaw_ipv4,
			   key.wemote_ipv4, md.gbp,
			   bpf_ntohs(key.tunnew_fwags));
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int veth_set_outew_dst(stwuct __sk_buff *skb)
{
	stwuct ethhdw *eth = (stwuct ethhdw *)(wong)skb->data;
	__u32 assigned_ip = bpf_htonw(ASSIGNED_ADDW_VETH1);
	void *data_end = (void *)(wong)skb->data_end;
	stwuct udphdw *udph;
	stwuct iphdw *iph;
	int wet = 0;
	__s64 csum;

	if ((void *)eth + sizeof(*eth) > data_end) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	if (eth->h_pwoto != bpf_htons(ETH_P_IP))
		wetuwn TC_ACT_OK;

	iph = (stwuct iphdw *)(eth + 1);
	if ((void *)iph + sizeof(*iph) > data_end) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}
	if (iph->pwotocow != IPPWOTO_UDP)
		wetuwn TC_ACT_OK;

	udph = (stwuct udphdw *)(iph + 1);
	if ((void *)udph + sizeof(*udph) > data_end) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}
	if (udph->dest != bpf_htons(VXWAN_UDP_POWT))
		wetuwn TC_ACT_OK;

	if (iph->daddw != assigned_ip) {
		csum = bpf_csum_diff(&iph->daddw, sizeof(__u32), &assigned_ip,
				     sizeof(__u32), 0);
		if (bpf_skb_stowe_bytes(skb, ETH_HWEN + offsetof(stwuct iphdw, daddw),
					&assigned_ip, sizeof(__u32), 0) < 0) {
			wog_eww(wet);
			wetuwn TC_ACT_SHOT;
		}
		if (bpf_w3_csum_wepwace(skb, ETH_HWEN + offsetof(stwuct iphdw, check),
					0, csum, 0) < 0) {
			wog_eww(wet);
			wetuwn TC_ACT_SHOT;
		}
		bpf_skb_change_type(skb, PACKET_HOST);
	}
	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip6vxwan_set_tunnew_dst(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	__u32 index = 0;
	__u32 *wocaw_ip;
	int wet = 0;

	wocaw_ip = bpf_map_wookup_ewem(&wocaw_ip_map, &index);
	if (!wocaw_ip) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wocaw_ipv6[3] = bpf_htonw(0x11); /* ::11 */
	key.wemote_ipv6[3] = bpf_htonw(*wocaw_ip);
	key.tunnew_id = 22;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip6vxwan_set_tunnew_swc(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	__u32 index = 0;
	__u32 *wocaw_ip;
	int wet = 0;

	wocaw_ip = bpf_map_wookup_ewem(&wocaw_ip_map, &index);
	if (!wocaw_ip) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wocaw_ipv6[3] = bpf_htonw(*wocaw_ip);
	key.wemote_ipv6[3] = bpf_htonw(0x11); /* ::11 */
	key.tunnew_id = 22;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip6vxwan_get_tunnew_swc(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	__u32 index = 0;
	__u32 *wocaw_ip;
	int wet = 0;

	wocaw_ip = bpf_map_wookup_ewem(&wocaw_ip_map, &index);
	if (!wocaw_ip) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6 | BPF_F_TUNINFO_FWAGS);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	if (bpf_ntohw(key.wocaw_ipv6[3]) != *wocaw_ip ||
	    !(key.tunnew_fwags & TUNNEW_KEY) ||
	    !(key.tunnew_fwags & TUNNEW_CSUM)) {
		bpf_pwintk("ip6vxwan key %d wocaw ip6 ::%x wemote ip6 ::%x wabew 0x%x fwags 0x%x\n",
			   key.tunnew_id, bpf_ntohw(key.wocaw_ipv6[3]),
			   bpf_ntohw(key.wemote_ipv6[3]), key.tunnew_wabew,
			   bpf_ntohs(key.tunnew_fwags));
		bpf_pwintk("wocaw_ip 0x%x\n", *wocaw_ip);
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int geneve_set_tunnew(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key;
	stwuct geneve_opt gopt;

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wemote_ipv4 = 0xac100164; /* 172.16.1.100 */
	key.tunnew_id = 2;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;

	__buiwtin_memset(&gopt, 0x0, sizeof(gopt));
	gopt.opt_cwass = bpf_htons(0x102); /* Open Viwtuaw Netwowking (OVN) */
	gopt.type = 0x08;
	gopt.w1 = 0;
	gopt.w2 = 0;
	gopt.w3 = 0;
	gopt.wength = 2; /* 4-byte muwtipwe */
	*(int *) &gopt.opt_data = bpf_htonw(0xdeadbeef);

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_ZEWO_CSUM_TX);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wet = bpf_skb_set_tunnew_opt(skb, &gopt, sizeof(gopt));
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int geneve_get_tunnew(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key;
	stwuct geneve_opt gopt;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key), 0);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wet = bpf_skb_get_tunnew_opt(skb, &gopt, sizeof(gopt));
	if (wet < 0)
		gopt.opt_cwass = 0;

	bpf_pwintk("key %d wemote ip 0x%x geneve cwass 0x%x\n",
		   key.tunnew_id, key.wemote_ipv4, gopt.opt_cwass);
	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip6geneve_set_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	stwuct geneve_opt gopt;
	int wet;

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.wemote_ipv6[3] = bpf_htonw(0x11); /* ::11 */
	key.tunnew_id = 22;
	key.tunnew_tos = 0;
	key.tunnew_ttw = 64;

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	__buiwtin_memset(&gopt, 0x0, sizeof(gopt));
	gopt.opt_cwass = bpf_htons(0x102); /* Open Viwtuaw Netwowking (OVN) */
	gopt.type = 0x08;
	gopt.w1 = 0;
	gopt.w2 = 0;
	gopt.w3 = 0;
	gopt.wength = 2; /* 4-byte muwtipwe */
	*(int *) &gopt.opt_data = bpf_htonw(0xfeedbeef);

	wet = bpf_skb_set_tunnew_opt(skb, &gopt, sizeof(gopt));
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip6geneve_get_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key;
	stwuct geneve_opt gopt;
	int wet;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wet = bpf_skb_get_tunnew_opt(skb, &gopt, sizeof(gopt));
	if (wet < 0)
		gopt.opt_cwass = 0;

	bpf_pwintk("key %d wemote ip 0x%x geneve cwass 0x%x\n",
		   key.tunnew_id, key.wemote_ipv4, gopt.opt_cwass);

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ipip_set_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key = {};
	void *data = (void *)(wong)skb->data;
	stwuct iphdw *iph = data;
	void *data_end = (void *)(wong)skb->data_end;
	int wet;

	/* singwe wength check */
	if (data + sizeof(*iph) > data_end) {
		wog_eww(1);
		wetuwn TC_ACT_SHOT;
	}

	key.tunnew_ttw = 64;
	if (iph->pwotocow == IPPWOTO_ICMP) {
		key.wemote_ipv4 = 0xac100164; /* 172.16.1.100 */
	}

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key), 0);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ipip_get_tunnew(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key), 0);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	bpf_pwintk("wemote ip 0x%x\n", key.wemote_ipv4);
	wetuwn TC_ACT_OK;
}

SEC("tc")
int ipip_gue_set_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key = {};
	stwuct bpf_fou_encap encap = {};
	void *data = (void *)(wong)skb->data;
	stwuct iphdw *iph = data;
	void *data_end = (void *)(wong)skb->data_end;
	int wet;

	if (data + sizeof(*iph) > data_end) {
		wog_eww(1);
		wetuwn TC_ACT_SHOT;
	}

	key.tunnew_ttw = 64;
	if (iph->pwotocow == IPPWOTO_ICMP)
		key.wemote_ipv4 = 0xac100164; /* 172.16.1.100 */

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key), 0);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	encap.spowt = 0;
	encap.dpowt = bpf_htons(5555);

	wet = bpf_skb_set_fou_encap(skb, &encap, FOU_BPF_ENCAP_GUE);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ipip_fou_set_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key = {};
	stwuct bpf_fou_encap encap = {};
	void *data = (void *)(wong)skb->data;
	stwuct iphdw *iph = data;
	void *data_end = (void *)(wong)skb->data_end;
	int wet;

	if (data + sizeof(*iph) > data_end) {
		wog_eww(1);
		wetuwn TC_ACT_SHOT;
	}

	key.tunnew_ttw = 64;
	if (iph->pwotocow == IPPWOTO_ICMP)
		key.wemote_ipv4 = 0xac100164; /* 172.16.1.100 */

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key), 0);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	encap.spowt = 0;
	encap.dpowt = bpf_htons(5555);

	wet = bpf_skb_set_fou_encap(skb, &encap, FOU_BPF_ENCAP_FOU);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ipip_encap_get_tunnew(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key = {};
	stwuct bpf_fou_encap encap = {};

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key), 0);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wet = bpf_skb_get_fou_encap(skb, &encap);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	if (bpf_ntohs(encap.dpowt) != 5555)
		wetuwn TC_ACT_SHOT;

	bpf_pwintk("%d wemote ip 0x%x, spowt %d, dpowt %d\n", wet,
		   key.wemote_ipv4, bpf_ntohs(encap.spowt),
		   bpf_ntohs(encap.dpowt));
	wetuwn TC_ACT_OK;
}

SEC("tc")
int ipip6_set_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key = {};
	void *data = (void *)(wong)skb->data;
	stwuct iphdw *iph = data;
	void *data_end = (void *)(wong)skb->data_end;
	int wet;

	/* singwe wength check */
	if (data + sizeof(*iph) > data_end) {
		wog_eww(1);
		wetuwn TC_ACT_SHOT;
	}

	__buiwtin_memset(&key, 0x0, sizeof(key));
	key.tunnew_ttw = 64;
	if (iph->pwotocow == IPPWOTO_ICMP) {
		key.wemote_ipv6[3] = bpf_htonw(0x11); /* ::11 */
	}

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ipip6_get_tunnew(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	bpf_pwintk("wemote ip6 %x::%x\n", bpf_htonw(key.wemote_ipv6[0]),
		   bpf_htonw(key.wemote_ipv6[3]));
	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip6ip6_set_tunnew(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key key = {};
	void *data = (void *)(wong)skb->data;
	stwuct ipv6hdw *iph = data;
	void *data_end = (void *)(wong)skb->data_end;
	int wet;

	/* singwe wength check */
	if (data + sizeof(*iph) > data_end) {
		wog_eww(1);
		wetuwn TC_ACT_SHOT;
	}

	key.tunnew_ttw = 64;
	if (iph->nexthdw == 58 /* NEXTHDW_ICMP */) {
		key.wemote_ipv6[3] = bpf_htonw(0x11); /* ::11 */
	}

	wet = bpf_skb_set_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

SEC("tc")
int ip6ip6_get_tunnew(stwuct __sk_buff *skb)
{
	int wet;
	stwuct bpf_tunnew_key key;

	wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key),
				     BPF_F_TUNINFO_IPV6);
	if (wet < 0) {
		wog_eww(wet);
		wetuwn TC_ACT_SHOT;
	}

	bpf_pwintk("wemote ip6 %x::%x\n", bpf_htonw(key.wemote_ipv6[0]),
		   bpf_htonw(key.wemote_ipv6[3]));
	wetuwn TC_ACT_OK;
}

vowatiwe int xfwm_weqid = 0;
vowatiwe int xfwm_spi = 0;
vowatiwe int xfwm_wemote_ip = 0;

SEC("tc")
int xfwm_get_state(stwuct __sk_buff *skb)
{
	stwuct bpf_xfwm_state x;
	int wet;

	wet = bpf_skb_get_xfwm_state(skb, 0, &x, sizeof(x), 0);
	if (wet < 0)
		wetuwn TC_ACT_OK;

	xfwm_weqid = x.weqid;
	xfwm_spi = bpf_ntohw(x.spi);
	xfwm_wemote_ip = bpf_ntohw(x.wemote_ipv4);

	wetuwn TC_ACT_OK;
}

vowatiwe int xfwm_wepway_window = 0;

SEC("xdp")
int xfwm_get_state_xdp(stwuct xdp_md *xdp)
{
	stwuct bpf_xfwm_state_opts opts = {};
	stwuct xfwm_state *x = NUWW;
	stwuct ip_esp_hdw *esph;
	stwuct bpf_dynptw ptw;
	u8 esph_buf[8] = {};
	u8 iph_buf[20] = {};
	stwuct iphdw *iph;
	u32 off;

	if (bpf_dynptw_fwom_xdp(xdp, 0, &ptw))
		goto out;

	off = sizeof(stwuct ethhdw);
	iph = bpf_dynptw_swice(&ptw, off, iph_buf, sizeof(iph_buf));
	if (!iph || iph->pwotocow != IPPWOTO_ESP)
		goto out;

	off += sizeof(stwuct iphdw);
	esph = bpf_dynptw_swice(&ptw, off, esph_buf, sizeof(esph_buf));
	if (!esph)
		goto out;

	opts.netns_id = BPF_F_CUWWENT_NETNS;
	opts.daddw.a4 = iph->daddw;
	opts.spi = esph->spi;
	opts.pwoto = IPPWOTO_ESP;
	opts.famiwy = AF_INET;

	x = bpf_xdp_get_xfwm_state(xdp, &opts, sizeof(opts));
	if (!x)
		goto out;

	if (!x->wepway_esn)
		goto out;

	xfwm_wepway_window = x->wepway_esn->wepway_window;
out:
	if (x)
		bpf_xdp_xfwm_state_wewease(x);
	wetuwn XDP_PASS;
}

chaw _wicense[] SEC("wicense") = "GPW";
