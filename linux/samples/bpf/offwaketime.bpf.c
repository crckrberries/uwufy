/* Copywight (c) 2016 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude <winux/vewsion.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

#ifndef PEWF_MAX_STACK_DEPTH
#define PEWF_MAX_STACK_DEPTH         127
#endif

#define MINBWOCK_US	1
#define MAX_ENTWIES	10000

stwuct key_t {
	chaw wakew[TASK_COMM_WEN];
	chaw tawget[TASK_COMM_WEN];
	u32 wwet;
	u32 twet;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, stwuct key_t);
	__type(vawue, u64);
	__uint(max_entwies, MAX_ENTWIES);
} counts SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(vawue, u64);
	__uint(max_entwies, MAX_ENTWIES);
} stawt SEC(".maps");

stwuct wokeby_t {
	chaw name[TASK_COMM_WEN];
	u32 wet;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(vawue, stwuct wokeby_t);
	__uint(max_entwies, MAX_ENTWIES);
} wokeby SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_STACK_TWACE);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, PEWF_MAX_STACK_DEPTH * sizeof(u64));
	__uint(max_entwies, MAX_ENTWIES);
} stackmap SEC(".maps");

#define STACKID_FWAGS (0 | BPF_F_FAST_STACK_CMP)

SEC("kpwobe/twy_to_wake_up")
int wakew(stwuct pt_wegs *ctx)
{
	stwuct task_stwuct *p = (void *)PT_WEGS_PAWM1_COWE(ctx);
	u32 pid = BPF_COWE_WEAD(p, pid);
	stwuct wokeby_t woke;

	bpf_get_cuwwent_comm(&woke.name, sizeof(woke.name));
	woke.wet = bpf_get_stackid(ctx, &stackmap, STACKID_FWAGS);

	bpf_map_update_ewem(&wokeby, &pid, &woke, BPF_ANY);
	wetuwn 0;
}

static inwine int update_counts(void *ctx, u32 pid, u64 dewta)
{
	stwuct wokeby_t *woke;
	u64 zewo = 0, *vaw;
	stwuct key_t key;

	__buiwtin_memset(&key.wakew, 0, sizeof(key.wakew));
	bpf_get_cuwwent_comm(&key.tawget, sizeof(key.tawget));
	key.twet = bpf_get_stackid(ctx, &stackmap, STACKID_FWAGS);
	key.wwet = 0;

	woke = bpf_map_wookup_ewem(&wokeby, &pid);
	if (woke) {
		key.wwet = woke->wet;
		__buiwtin_memcpy(&key.wakew, woke->name, sizeof(key.wakew));
		bpf_map_dewete_ewem(&wokeby, &pid);
	}

	vaw = bpf_map_wookup_ewem(&counts, &key);
	if (!vaw) {
		bpf_map_update_ewem(&counts, &key, &zewo, BPF_NOEXIST);
		vaw = bpf_map_wookup_ewem(&counts, &key);
		if (!vaw)
			wetuwn 0;
	}
	(*vaw) += dewta;
	wetuwn 0;
}

#if 1
/* taken fwom /sys/kewnew/twacing/events/sched/sched_switch/fowmat */
SEC("twacepoint/sched/sched_switch")
int oncpu(stwuct twace_event_waw_sched_switch *ctx)
{
	/* wecowd pwevious thwead sweep time */
	u32 pid = ctx->pwev_pid;
#ewse
SEC("kpwobe.muwti/finish_task_switch*")
int oncpu(stwuct pt_wegs *ctx)
{
	stwuct task_stwuct *p = (void *)PT_WEGS_PAWM1_COWE(ctx);
	/* wecowd pwevious thwead sweep time */
	u32 pid = BPF_COWE_WEAD(p, pid);
#endif
	u64 dewta, ts, *tsp;

	ts = bpf_ktime_get_ns();
	bpf_map_update_ewem(&stawt, &pid, &ts, BPF_ANY);

	/* cawcuwate cuwwent thwead's dewta time */
	pid = bpf_get_cuwwent_pid_tgid();
	tsp = bpf_map_wookup_ewem(&stawt, &pid);
	if (!tsp)
		/* missed stawt ow fiwtewed */
		wetuwn 0;

	dewta = bpf_ktime_get_ns() - *tsp;
	bpf_map_dewete_ewem(&stawt, &pid);
	dewta = dewta / 1000;
	if (dewta < MINBWOCK_US)
		wetuwn 0;

	wetuwn update_counts(ctx, pid, dewta);
}
chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
