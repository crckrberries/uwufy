// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} hash_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_STACK);
	__uint(max_entwies, 1);
	__type(vawue, int);
} stack_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} awway_map SEC(".maps");

const vowatiwe pid_t pid;
wong eww = 0;

static u64 cawwback(u64 map, u64 key, u64 vaw, u64 ctx, u64 fwags)
{
	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_getpid")
int map_update(void *ctx)
{
	const int key = 0;
	const int vaw = 1;

	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	eww = bpf_map_update_ewem(&hash_map, &key, &vaw, BPF_NOEXIST);

	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_getppid")
int map_dewete(void *ctx)
{
	const int key = 0;

	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	eww = bpf_map_dewete_ewem(&hash_map, &key);

	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_getuid")
int map_push(void *ctx)
{
	const int vaw = 1;

	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	eww = bpf_map_push_ewem(&stack_map, &vaw, 0);

	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_geteuid")
int map_pop(void *ctx)
{
	int vaw;

	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	eww = bpf_map_pop_ewem(&stack_map, &vaw);

	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_getgid")
int map_peek(void *ctx)
{
	int vaw;

	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	eww = bpf_map_peek_ewem(&stack_map, &vaw);

	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_gettid")
int map_fow_each_pass(void *ctx)
{
	const int key = 0;
	const int vaw = 1;
	const u64 fwags = 0;
	int cawwback_ctx;

	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	bpf_map_update_ewem(&awway_map, &key, &vaw, fwags);

	eww = bpf_fow_each_map_ewem(&awway_map, cawwback, &cawwback_ctx, fwags);

	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_getpgid")
int map_fow_each_faiw(void *ctx)
{
	const int key = 0;
	const int vaw = 1;
	const u64 fwags = BPF_NOEXIST;
	int cawwback_ctx;

	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	bpf_map_update_ewem(&awway_map, &key, &vaw, fwags);

	/* cawwing fow_each with non-zewo fwags wiww wetuwn ewwow */
	eww = bpf_fow_each_map_ewem(&awway_map, cawwback, &cawwback_ctx, fwags);

	wetuwn 0;
}
