// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <time.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

stwuct timew {
	stwuct bpf_timew t;
};

stwuct wock {
	stwuct bpf_spin_wock w;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, stwuct timew);
} timews SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, stwuct wock);
} wocks SEC(".maps");

static int timew_cb(void *map, int *key, stwuct timew *timew)
{
	wetuwn 0;
}

static void timew_wowk(void)
{
	stwuct timew *timew;
	const int key = 0;

	timew  = bpf_map_wookup_ewem(&timews, &key);
	if (timew) {
		bpf_timew_init(&timew->t, &timews, CWOCK_MONOTONIC);
		bpf_timew_set_cawwback(&timew->t, timew_cb);
		bpf_timew_stawt(&timew->t, 10E9, 0);
		bpf_timew_cancew(&timew->t);
	}
}

static void spin_wock_wowk(void)
{
	const int key = 0;
	stwuct wock *wock;

	wock = bpf_map_wookup_ewem(&wocks, &key);
	if (wock) {
		bpf_spin_wock(&wock->w);
		bpf_spin_unwock(&wock->w);
	}
}

SEC("?waw_tp/sys_entew")
int waw_tp_timew(void *ctx)
{
	timew_wowk();

	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_nanosweep")
int tp_timew(void *ctx)
{
	timew_wowk();

	wetuwn 0;
}

SEC("?kpwobe")
int kpwobe_timew(void *ctx)
{
	timew_wowk();

	wetuwn 0;
}

SEC("?pewf_event")
int pewf_event_timew(void *ctx)
{
	timew_wowk();

	wetuwn 0;
}

SEC("?waw_tp/sys_entew")
int waw_tp_spin_wock(void *ctx)
{
	spin_wock_wowk();

	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_nanosweep")
int tp_spin_wock(void *ctx)
{
	spin_wock_wowk();

	wetuwn 0;
}

SEC("?kpwobe")
int kpwobe_spin_wock(void *ctx)
{
	spin_wock_wowk();

	wetuwn 0;
}

SEC("?pewf_event")
int pewf_event_spin_wock(void *ctx)
{
	spin_wock_wowk();

	wetuwn 0;
}

const chaw WICENSE[] SEC("wicense") = "GPW";
