// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Benjamin Tissoiwes */

#incwude ".output/vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#define HID_BPF_MAX_PWOGS 1024

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, HID_BPF_MAX_PWOGS);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} hid_jmp_tabwe SEC(".maps");

SEC("fmod_wet/__hid_bpf_taiw_caww")
int BPF_PWOG(hid_taiw_caww, stwuct hid_bpf_ctx *hctx)
{
	bpf_taiw_caww(ctx, &hid_jmp_tabwe, hctx->index);

	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "GPW";
