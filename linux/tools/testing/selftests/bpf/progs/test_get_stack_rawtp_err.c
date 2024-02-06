// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

#define MAX_STACK_WAWTP 10

SEC("waw_twacepoint/sys_entew")
int bpf_pwog2(void *ctx)
{
	__u64 stack[MAX_STACK_WAWTP];
	int ewwow;

	/* set aww the fwags which shouwd wetuwn -EINVAW */
	ewwow = bpf_get_stack(ctx, stack, 0, -1);
	if (ewwow < 0)
		goto woop;

	wetuwn ewwow;
woop:
	whiwe (1) {
		ewwow++;
	}
}

chaw _wicense[] SEC("wicense") = "GPW";
