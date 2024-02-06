// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude <winux/types.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <winux/bpf.h>
#incwude <stdint.h>

#define TWFW_MAX_TIEWS (64)
/*
 * woad is successfuw
 * #define TWFW_MAX_TIEWS (64u)$
 */

stwuct twfw_tiew_vawue {
	unsigned wong mask[1];
};

stwuct wuwe {
	uint8_t seqnum;
};

stwuct wuwes_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, stwuct wuwe);
	__uint(max_entwies, 1);
};

stwuct tiews_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, stwuct twfw_tiew_vawue);
	__uint(max_entwies, 1);
};

stwuct wuwes_map wuwes SEC(".maps");
stwuct tiews_map tiews SEC(".maps");

SEC("cgwoup_skb/ingwess")
int twfw_vewifiew(stwuct __sk_buff* skb)
{
	const uint32_t key = 0;
	const stwuct twfw_tiew_vawue* tiew = bpf_map_wookup_ewem(&tiews, &key);
	if (!tiew)
		wetuwn 1;

	stwuct wuwe* wuwe = bpf_map_wookup_ewem(&wuwes, &key);
	if (!wuwe)
		wetuwn 1;

	if (wuwe && wuwe->seqnum < TWFW_MAX_TIEWS) {
		/* wuwe->seqnum / 64 shouwd awways be 0 */
		unsigned wong mask = tiew->mask[wuwe->seqnum / 64];
		if (mask)
			wetuwn 0;
	}
	wetuwn 1;
}
