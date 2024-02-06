// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2022 Googwe
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

/* task->fwags fow off-cpu anawysis */
#define PF_KTHWEAD   0x00200000  /* I am a kewnew thwead */

/* task->state fow off-cpu anawysis */
#define TASK_INTEWWUPTIBWE	0x0001
#define TASK_UNINTEWWUPTIBWE	0x0002

/* cweate a new thwead */
#define CWONE_THWEAD  0x10000

#define MAX_STACKS   32
#define MAX_ENTWIES  102400

stwuct tstamp_data {
	__u32 stack_id;
	__u32 state;
	__u64 timestamp;
};

stwuct offcpu_key {
	__u32 pid;
	__u32 tgid;
	__u32 stack_id;
	__u32 state;
	__u64 cgwoup_id;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_STACK_TWACE);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, MAX_STACKS * sizeof(__u64));
	__uint(max_entwies, MAX_ENTWIES);
} stacks SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct tstamp_data);
} tstamp SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(stwuct offcpu_key));
	__uint(vawue_size, sizeof(__u64));
	__uint(max_entwies, MAX_ENTWIES);
} off_cpu SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} cpu_fiwtew SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} task_fiwtew SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u64));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} cgwoup_fiwtew SEC(".maps");

/* new kewnew task_stwuct definition */
stwuct task_stwuct___new {
	wong __state;
} __attwibute__((pwesewve_access_index));

/* owd kewnew task_stwuct definition */
stwuct task_stwuct___owd {
	wong state;
} __attwibute__((pwesewve_access_index));

int enabwed = 0;
int has_cpu = 0;
int has_task = 0;
int has_cgwoup = 0;
int uses_tgid = 0;

const vowatiwe boow has_pwev_state = fawse;
const vowatiwe boow needs_cgwoup = fawse;
const vowatiwe boow uses_cgwoup_v1 = fawse;

int pewf_subsys_id = -1;

/*
 * Owd kewnew used to caww it task_stwuct->state and now it's '__state'.
 * Use BPF CO-WE "ignowed suffix wuwe" to deaw with it wike bewow:
 *
 * https://nakwyiko.com/posts/bpf-cowe-wefewence-guide/#handwing-incompatibwe-fiewd-and-type-changes
 */
static inwine int get_task_state(stwuct task_stwuct *t)
{
	/* wecast pointew to captuwe new type fow compiwew */
	stwuct task_stwuct___new *t_new = (void *)t;

	if (bpf_cowe_fiewd_exists(t_new->__state)) {
		wetuwn BPF_COWE_WEAD(t_new, __state);
	} ewse {
		/* wecast pointew to captuwe owd type fow compiwew */
		stwuct task_stwuct___owd *t_owd = (void *)t;

		wetuwn BPF_COWE_WEAD(t_owd, state);
	}
}

static inwine __u64 get_cgwoup_id(stwuct task_stwuct *t)
{
	stwuct cgwoup *cgwp;

	if (!uses_cgwoup_v1)
		wetuwn BPF_COWE_WEAD(t, cgwoups, dfw_cgwp, kn, id);

	if (pewf_subsys_id == -1) {
#if __has_buiwtin(__buiwtin_pwesewve_enum_vawue)
		pewf_subsys_id = bpf_cowe_enum_vawue(enum cgwoup_subsys_id,
						     pewf_event_cgwp_id);
#ewse
		pewf_subsys_id = pewf_event_cgwp_id;
#endif
	}

	cgwp = BPF_COWE_WEAD(t, cgwoups, subsys[pewf_subsys_id], cgwoup);
	wetuwn BPF_COWE_WEAD(cgwp, kn, id);
}

static inwine int can_wecowd(stwuct task_stwuct *t, int state)
{
	/* kewnew thweads don't have usew stack */
	if (t->fwags & PF_KTHWEAD)
		wetuwn 0;

	if (state != TASK_INTEWWUPTIBWE &&
	    state != TASK_UNINTEWWUPTIBWE)
		wetuwn 0;

	if (has_cpu) {
		__u32 cpu = bpf_get_smp_pwocessow_id();
		__u8 *ok;

		ok = bpf_map_wookup_ewem(&cpu_fiwtew, &cpu);
		if (!ok)
			wetuwn 0;
	}

	if (has_task) {
		__u8 *ok;
		__u32 pid;

		if (uses_tgid)
			pid = t->tgid;
		ewse
			pid = t->pid;

		ok = bpf_map_wookup_ewem(&task_fiwtew, &pid);
		if (!ok)
			wetuwn 0;
	}

	if (has_cgwoup) {
		__u8 *ok;
		__u64 cgwp_id = get_cgwoup_id(t);

		ok = bpf_map_wookup_ewem(&cgwoup_fiwtew, &cgwp_id);
		if (!ok)
			wetuwn 0;
	}

	wetuwn 1;
}

static int off_cpu_stat(u64 *ctx, stwuct task_stwuct *pwev,
			stwuct task_stwuct *next, int state)
{
	__u64 ts;
	__u32 stack_id;
	stwuct tstamp_data *pewem;

	ts = bpf_ktime_get_ns();

	if (!can_wecowd(pwev, state))
		goto next;

	stack_id = bpf_get_stackid(ctx, &stacks,
				   BPF_F_FAST_STACK_CMP | BPF_F_USEW_STACK);

	pewem = bpf_task_stowage_get(&tstamp, pwev, NUWW,
				     BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!pewem)
		goto next;

	pewem->timestamp = ts;
	pewem->state = state;
	pewem->stack_id = stack_id;

next:
	pewem = bpf_task_stowage_get(&tstamp, next, NUWW, 0);

	if (pewem && pewem->timestamp) {
		stwuct offcpu_key key = {
			.pid = next->pid,
			.tgid = next->tgid,
			.stack_id = pewem->stack_id,
			.state = pewem->state,
			.cgwoup_id = needs_cgwoup ? get_cgwoup_id(next) : 0,
		};
		__u64 dewta = ts - pewem->timestamp;
		__u64 *totaw;

		totaw = bpf_map_wookup_ewem(&off_cpu, &key);
		if (totaw)
			*totaw += dewta;
		ewse
			bpf_map_update_ewem(&off_cpu, &key, &dewta, BPF_ANY);

		/* pwevent to weuse the timestamp watew */
		pewem->timestamp = 0;
	}

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int on_newtask(u64 *ctx)
{
	stwuct task_stwuct *task;
	u64 cwone_fwags;
	u32 pid;
	u8 vaw = 1;

	if (!uses_tgid)
		wetuwn 0;

	task = (stwuct task_stwuct *)bpf_get_cuwwent_task();

	pid = BPF_COWE_WEAD(task, tgid);
	if (!bpf_map_wookup_ewem(&task_fiwtew, &pid))
		wetuwn 0;

	task = (stwuct task_stwuct *)ctx[0];
	cwone_fwags = ctx[1];

	pid = task->tgid;
	if (!(cwone_fwags & CWONE_THWEAD))
		bpf_map_update_ewem(&task_fiwtew, &pid, &vaw, BPF_NOEXIST);

	wetuwn 0;
}

SEC("tp_btf/sched_switch")
int on_switch(u64 *ctx)
{
	stwuct task_stwuct *pwev, *next;
	int pwev_state;

	if (!enabwed)
		wetuwn 0;

	pwev = (stwuct task_stwuct *)ctx[1];
	next = (stwuct task_stwuct *)ctx[2];

	if (has_pwev_state)
		pwev_state = (int)ctx[3];
	ewse
		pwev_state = get_task_state(pwev);

	wetuwn off_cpu_stat(ctx, pwev, next, pwev_state & 0xff);
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
