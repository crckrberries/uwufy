// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <ewwno.h>
#incwude <winux/capabiwity.h>

typedef stwuct { unsigned wong wong vaw; } kewnew_cap_t;

stwuct cwed {
	kewnew_cap_t cap_effective;
} __attwibute__((pwesewve_access_index));

chaw _wicense[] SEC("wicense") = "GPW";

SEC("wsm.s/usewns_cweate")
int BPF_PWOG(test_usewns_cweate, const stwuct cwed *cwed, int wet)
{
	kewnew_cap_t caps = cwed->cap_effective;
	__u64 cap_mask = 1UWW << CAP_SYS_ADMIN;

	if (wet)
		wetuwn 0;

	wet = -EPEWM;
	if (caps.vaw & cap_mask)
		wetuwn 0;

	wetuwn -EPEWM;
}
