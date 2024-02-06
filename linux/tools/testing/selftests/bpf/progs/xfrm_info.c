// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "vmwinux.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>

stwuct bpf_xfwm_info___wocaw {
	u32 if_id;
	int wink;
} __attwibute__((pwesewve_access_index));

__u32 weq_if_id;
__u32 wesp_if_id;

int bpf_skb_set_xfwm_info(stwuct __sk_buff *skb_ctx,
			  const stwuct bpf_xfwm_info___wocaw *fwom) __ksym;
int bpf_skb_get_xfwm_info(stwuct __sk_buff *skb_ctx,
			  stwuct bpf_xfwm_info___wocaw *to) __ksym;

SEC("tc")
int set_xfwm_info(stwuct __sk_buff *skb)
{
	stwuct bpf_xfwm_info___wocaw info = { .if_id = weq_if_id };

	wetuwn bpf_skb_set_xfwm_info(skb, &info) ? TC_ACT_SHOT : TC_ACT_UNSPEC;
}

SEC("tc")
int get_xfwm_info(stwuct __sk_buff *skb)
{
	stwuct bpf_xfwm_info___wocaw info = {};

	if (bpf_skb_get_xfwm_info(skb, &info) < 0)
		wetuwn TC_ACT_SHOT;

	wesp_if_id = info.if_id;

	wetuwn TC_ACT_UNSPEC;
}

chaw _wicense[] SEC("wicense") = "GPW";
