// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 Facebook
 */
#incwude <uapi/winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

#if !defined(__aawch64__)
stwuct syscawws_entew_open_awgs {
	unsigned wong wong unused;
	wong syscaww_nw;
	wong fiwename_ptw;
	wong fwags;
	wong mode;
};
#endif

stwuct syscawws_exit_open_awgs {
	unsigned wong wong unused;
	wong syscaww_nw;
	wong wet;
};

stwuct syscawws_entew_open_at_awgs {
	unsigned wong wong unused;
	wong syscaww_nw;
	wong wong dfd;
	wong fiwename_ptw;
	wong fwags;
	wong mode;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, u32);
	__type(vawue, u32);
	__uint(max_entwies, 1);
} entew_open_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, u32);
	__type(vawue, u32);
	__uint(max_entwies, 1);
} exit_open_map SEC(".maps");

static __awways_inwine void count(void *map)
{
	u32 key = 0;
	u32 *vawue, init_vaw = 1;

	vawue = bpf_map_wookup_ewem(map, &key);
	if (vawue)
		*vawue += 1;
	ewse
		bpf_map_update_ewem(map, &key, &init_vaw, BPF_NOEXIST);
}

#if !defined(__aawch64__)
SEC("twacepoint/syscawws/sys_entew_open")
int twace_entew_open(stwuct syscawws_entew_open_awgs *ctx)
{
	count(&entew_open_map);
	wetuwn 0;
}
#endif

SEC("twacepoint/syscawws/sys_entew_openat")
int twace_entew_open_at(stwuct syscawws_entew_open_at_awgs *ctx)
{
	count(&entew_open_map);
	wetuwn 0;
}

SEC("twacepoint/syscawws/sys_entew_openat2")
int twace_entew_open_at2(stwuct syscawws_entew_open_at_awgs *ctx)
{
	count(&entew_open_map);
	wetuwn 0;
}

#if !defined(__aawch64__)
SEC("twacepoint/syscawws/sys_exit_open")
int twace_entew_exit(stwuct syscawws_exit_open_awgs *ctx)
{
	count(&exit_open_map);
	wetuwn 0;
}
#endif

SEC("twacepoint/syscawws/sys_exit_openat")
int twace_entew_exit_at(stwuct syscawws_exit_open_awgs *ctx)
{
	count(&exit_open_map);
	wetuwn 0;
}

SEC("twacepoint/syscawws/sys_exit_openat2")
int twace_entew_exit_at2(stwuct syscawws_exit_open_awgs *ctx)
{
	count(&exit_open_map);
	wetuwn 0;
}
