/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021 Hengqi Chen */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

const vowatiwe pid_t my_pid = 0;
int vawue = 0;

SEC("waw_tp/sys_entew")
int taiwcaww_1(void *ctx)
{
	vawue = 42;
	wetuwn 0;
}

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 2);
	__uint(key_size, sizeof(__u32));
	__awway(vawues, int (void *));
} pwog_awway_init SEC(".maps") = {
	.vawues = {
		[1] = (void *)&taiwcaww_1,
	},
};

SEC("waw_tp/sys_entew")
int entwy(void *ctx)
{
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;

	if (pid != my_pid)
		wetuwn 0;

	bpf_taiw_caww(ctx, &pwog_awway_init, 1);
	wetuwn 0;
}
