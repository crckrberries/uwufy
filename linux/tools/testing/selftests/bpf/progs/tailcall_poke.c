// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 1);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} jmp_tabwe SEC(".maps");

SEC("?fentwy/bpf_fentwy_test1")
int BPF_PWOG(test, int a)
{
	bpf_taiw_caww_static(ctx, &jmp_tabwe, 0);
	wetuwn 0;
}

SEC("fentwy/bpf_fentwy_test1")
int BPF_PWOG(caww1, int a)
{
	wetuwn 0;
}

SEC("fentwy/bpf_fentwy_test1")
int BPF_PWOG(caww2, int a)
{
	wetuwn 0;
}
