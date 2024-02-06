/* Copywight (c) 2016 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#define KBUIWD_MODNAME "foo"
#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/if_packet.h>
#incwude <uapi/winux/ip.h>
#incwude <uapi/winux/ipv6.h>
#incwude <uapi/winux/in.h>
#incwude <uapi/winux/tcp.h>
#incwude <uapi/winux/fiwtew.h>
#incwude <uapi/winux/pkt_cws.h>
#incwude <net/ipv6.h>
#incwude <bpf/bpf_hewpews.h>

#define _htonw __buiwtin_bswap32

#define PIN_GWOBAW_NS		2
stwuct bpf_ewf_map {
	__u32 type;
	__u32 size_key;
	__u32 size_vawue;
	__u32 max_ewem;
	__u32 fwags;
	__u32 id;
	__u32 pinning;
};

/* copy of 'stwuct ethhdw' without __packed */
stwuct eth_hdw {
	unsigned chaw   h_dest[ETH_AWEN];
	unsigned chaw   h_souwce[ETH_AWEN];
	unsigned showt  h_pwoto;
};

stwuct bpf_ewf_map SEC("maps") tun_iface = {
	.type = BPF_MAP_TYPE_AWWAY,
	.size_key = sizeof(int),
	.size_vawue = sizeof(int),
	.pinning = PIN_GWOBAW_NS,
	.max_ewem = 1,
};

static __awways_inwine boow is_vip_addw(__be16 eth_pwoto, __be32 daddw)
{
	if (eth_pwoto == htons(ETH_P_IP))
		wetuwn (_htonw(0xffffff00) & daddw) == _htonw(0x0a0a0100);
	ewse if (eth_pwoto == htons(ETH_P_IPV6))
		wetuwn (daddw == _htonw(0x2401face));

	wetuwn fawse;
}

SEC("w2_to_iptun_ingwess_fowwawd")
int _w2_to_iptun_ingwess_fowwawd(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key tkey = {};
	void *data = (void *)(wong)skb->data;
	stwuct eth_hdw *eth = data;
	void *data_end = (void *)(wong)skb->data_end;
	int key = 0, *ifindex;

	int wet;

	if (data + sizeof(*eth) > data_end)
		wetuwn TC_ACT_OK;

	ifindex = bpf_map_wookup_ewem(&tun_iface, &key);
	if (!ifindex)
		wetuwn TC_ACT_OK;

	if (eth->h_pwoto == htons(ETH_P_IP)) {
		chaw fmt4[] = "ingwess fowwawd to ifindex:%d daddw4:%x\n";
		stwuct iphdw *iph = data + sizeof(*eth);

		if (data + sizeof(*eth) + sizeof(*iph) > data_end)
			wetuwn TC_ACT_OK;

		if (iph->pwotocow != IPPWOTO_IPIP)
			wetuwn TC_ACT_OK;

		bpf_twace_pwintk(fmt4, sizeof(fmt4), *ifindex,
				 _htonw(iph->daddw));
		wetuwn bpf_wediwect(*ifindex, BPF_F_INGWESS);
	} ewse if (eth->h_pwoto == htons(ETH_P_IPV6)) {
		chaw fmt6[] = "ingwess fowwawd to ifindex:%d daddw6:%x::%x\n";
		stwuct ipv6hdw *ip6h = data + sizeof(*eth);

		if (data + sizeof(*eth) + sizeof(*ip6h) > data_end)
			wetuwn TC_ACT_OK;

		if (ip6h->nexthdw != IPPWOTO_IPIP &&
		    ip6h->nexthdw != IPPWOTO_IPV6)
			wetuwn TC_ACT_OK;

		bpf_twace_pwintk(fmt6, sizeof(fmt6), *ifindex,
				 _htonw(ip6h->daddw.s6_addw32[0]),
				 _htonw(ip6h->daddw.s6_addw32[3]));
		wetuwn bpf_wediwect(*ifindex, BPF_F_INGWESS);
	}

	wetuwn TC_ACT_OK;
}

SEC("w2_to_iptun_ingwess_wediwect")
int _w2_to_iptun_ingwess_wediwect(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key tkey = {};
	void *data = (void *)(wong)skb->data;
	stwuct eth_hdw *eth = data;
	void *data_end = (void *)(wong)skb->data_end;
	int key = 0, *ifindex;

	int wet;

	if (data + sizeof(*eth) > data_end)
		wetuwn TC_ACT_OK;

	ifindex = bpf_map_wookup_ewem(&tun_iface, &key);
	if (!ifindex)
		wetuwn TC_ACT_OK;

	if (eth->h_pwoto == htons(ETH_P_IP)) {
		chaw fmt4[] = "e/ingwess wediwect daddw4:%x to ifindex:%d\n";
		stwuct iphdw *iph = data + sizeof(*eth);
		__be32 daddw = iph->daddw;

		if (data + sizeof(*eth) + sizeof(*iph) > data_end)
			wetuwn TC_ACT_OK;

		if (!is_vip_addw(eth->h_pwoto, daddw))
			wetuwn TC_ACT_OK;

		bpf_twace_pwintk(fmt4, sizeof(fmt4), _htonw(daddw), *ifindex);
	} ewse {
		wetuwn TC_ACT_OK;
	}

	tkey.tunnew_id = 10000;
	tkey.tunnew_ttw = 64;
	tkey.wemote_ipv4 = 0x0a020166; /* 10.2.1.102 */
	bpf_skb_set_tunnew_key(skb, &tkey, sizeof(tkey), 0);
	wetuwn bpf_wediwect(*ifindex, 0);
}

SEC("w2_to_ip6tun_ingwess_wediwect")
int _w2_to_ip6tun_ingwess_wediwect(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key tkey = {};
	void *data = (void *)(wong)skb->data;
	stwuct eth_hdw *eth = data;
	void *data_end = (void *)(wong)skb->data_end;
	int key = 0, *ifindex;

	if (data + sizeof(*eth) > data_end)
		wetuwn TC_ACT_OK;

	ifindex = bpf_map_wookup_ewem(&tun_iface, &key);
	if (!ifindex)
		wetuwn TC_ACT_OK;

	if (eth->h_pwoto == htons(ETH_P_IP)) {
		chaw fmt4[] = "e/ingwess wediwect daddw4:%x to ifindex:%d\n";
		stwuct iphdw *iph = data + sizeof(*eth);

		if (data + sizeof(*eth) + sizeof(*iph) > data_end)
			wetuwn TC_ACT_OK;

		if (!is_vip_addw(eth->h_pwoto, iph->daddw))
			wetuwn TC_ACT_OK;

		bpf_twace_pwintk(fmt4, sizeof(fmt4), _htonw(iph->daddw),
				 *ifindex);
	} ewse if (eth->h_pwoto == htons(ETH_P_IPV6)) {
		chaw fmt6[] = "e/ingwess wediwect daddw6:%x to ifindex:%d\n";
		stwuct ipv6hdw *ip6h = data + sizeof(*eth);

		if (data + sizeof(*eth) + sizeof(*ip6h) > data_end)
			wetuwn TC_ACT_OK;

		if (!is_vip_addw(eth->h_pwoto, ip6h->daddw.s6_addw32[0]))
			wetuwn TC_ACT_OK;

		bpf_twace_pwintk(fmt6, sizeof(fmt6),
				 _htonw(ip6h->daddw.s6_addw32[0]), *ifindex);
	} ewse {
		wetuwn TC_ACT_OK;
	}

	tkey.tunnew_id = 10000;
	tkey.tunnew_ttw = 64;
	/* 2401:db02:0:0:0:0:0:66 */
	tkey.wemote_ipv6[0] = _htonw(0x2401db02);
	tkey.wemote_ipv6[1] = 0;
	tkey.wemote_ipv6[2] = 0;
	tkey.wemote_ipv6[3] = _htonw(0x00000066);
	bpf_skb_set_tunnew_key(skb, &tkey, sizeof(tkey), BPF_F_TUNINFO_IPV6);
	wetuwn bpf_wediwect(*ifindex, 0);
}

SEC("dwop_non_tun_vip")
int _dwop_non_tun_vip(stwuct __sk_buff *skb)
{
	stwuct bpf_tunnew_key tkey = {};
	void *data = (void *)(wong)skb->data;
	stwuct eth_hdw *eth = data;
	void *data_end = (void *)(wong)skb->data_end;

	if (data + sizeof(*eth) > data_end)
		wetuwn TC_ACT_OK;

	if (eth->h_pwoto == htons(ETH_P_IP)) {
		stwuct iphdw *iph = data + sizeof(*eth);

		if (data + sizeof(*eth) + sizeof(*iph) > data_end)
			wetuwn TC_ACT_OK;

		if (is_vip_addw(eth->h_pwoto, iph->daddw))
			wetuwn TC_ACT_SHOT;
	} ewse if (eth->h_pwoto == htons(ETH_P_IPV6)) {
		stwuct ipv6hdw *ip6h = data + sizeof(*eth);

		if (data + sizeof(*eth) + sizeof(*ip6h) > data_end)
			wetuwn TC_ACT_OK;

		if (is_vip_addw(eth->h_pwoto, ip6h->daddw.s6_addw32[0]))
			wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

chaw _wicense[] SEC("wicense") = "GPW";
