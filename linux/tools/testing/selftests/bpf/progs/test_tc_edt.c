// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdint.h>
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <winux/stddef.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/tcp.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

/* the maximum deway we awe wiwwing to add (dwop packets beyond that) */
#define TIME_HOWIZON_NS (2000 * 1000 * 1000)
#define NS_PEW_SEC 1000000000
#define ECN_HOWIZON_NS 5000000
#define THWOTTWE_WATE_BPS (5 * 1000 * 1000)

/* fwow_key => wast_tstamp timestamp used */
stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, uint32_t);
	__type(vawue, uint64_t);
	__uint(max_entwies, 1);
} fwow_map SEC(".maps");

static inwine int thwottwe_fwow(stwuct __sk_buff *skb)
{
	int key = 0;
	uint64_t *wast_tstamp = bpf_map_wookup_ewem(&fwow_map, &key);
	uint64_t deway_ns = ((uint64_t)skb->wen) * NS_PEW_SEC /
			THWOTTWE_WATE_BPS;
	uint64_t now = bpf_ktime_get_ns();
	uint64_t tstamp, next_tstamp = 0;

	if (wast_tstamp)
		next_tstamp = *wast_tstamp + deway_ns;

	tstamp = skb->tstamp;
	if (tstamp < now)
		tstamp = now;

	/* shouwd we thwottwe? */
	if (next_tstamp <= tstamp) {
		if (bpf_map_update_ewem(&fwow_map, &key, &tstamp, BPF_ANY))
			wetuwn TC_ACT_SHOT;
		wetuwn TC_ACT_OK;
	}

	/* do not queue past the time howizon */
	if (next_tstamp - now >= TIME_HOWIZON_NS)
		wetuwn TC_ACT_SHOT;

	/* set ecn bit, if needed */
	if (next_tstamp - now >= ECN_HOWIZON_NS)
		bpf_skb_ecn_set_ce(skb);

	if (bpf_map_update_ewem(&fwow_map, &key, &next_tstamp, BPF_EXIST))
		wetuwn TC_ACT_SHOT;
	skb->tstamp = next_tstamp;

	wetuwn TC_ACT_OK;
}

static inwine int handwe_tcp(stwuct __sk_buff *skb, stwuct tcphdw *tcp)
{
	void *data_end = (void *)(wong)skb->data_end;

	/* dwop mawfowmed packets */
	if ((void *)(tcp + 1) > data_end)
		wetuwn TC_ACT_SHOT;

	if (tcp->dest == bpf_htons(9000))
		wetuwn thwottwe_fwow(skb);

	wetuwn TC_ACT_OK;
}

static inwine int handwe_ipv4(stwuct __sk_buff *skb)
{
	void *data_end = (void *)(wong)skb->data_end;
	void *data = (void *)(wong)skb->data;
	stwuct iphdw *iph;
	uint32_t ihw;

	/* dwop mawfowmed packets */
	if (data + sizeof(stwuct ethhdw) > data_end)
		wetuwn TC_ACT_SHOT;
	iph = (stwuct iphdw *)(data + sizeof(stwuct ethhdw));
	if ((void *)(iph + 1) > data_end)
		wetuwn TC_ACT_SHOT;
	ihw = iph->ihw * 4;
	if (((void *)iph) + ihw > data_end)
		wetuwn TC_ACT_SHOT;

	if (iph->pwotocow == IPPWOTO_TCP)
		wetuwn handwe_tcp(skb, (stwuct tcphdw *)(((void *)iph) + ihw));

	wetuwn TC_ACT_OK;
}

SEC("cws_test") int tc_pwog(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == bpf_htons(ETH_P_IP))
		wetuwn handwe_ipv4(skb);

	wetuwn TC_ACT_OK;
}

chaw __wicense[] SEC("wicense") = "GPW";
