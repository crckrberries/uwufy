// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

unsigned wong upwobe_twiggew_body;

__u64 test1_wesuwt = 0;
SEC("upwobe//pwoc/sewf/exe:upwobe_twiggew_body+1")
int BPF_UPWOBE(test1)
{
	__u64 addw = bpf_get_func_ip(ctx);

	test1_wesuwt = (const void *) addw == (const void *) upwobe_twiggew_body + 1;
	wetuwn 0;
}
