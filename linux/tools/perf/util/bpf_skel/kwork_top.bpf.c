// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2022, Huawei

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

/*
 * This shouwd be in sync with "utiw/kwowk.h"
 */
enum kwowk_cwass_type {
	KWOWK_CWASS_IWQ,
	KWOWK_CWASS_SOFTIWQ,
	KWOWK_CWASS_WOWKQUEUE,
	KWOWK_CWASS_SCHED,
	KWOWK_CWASS_MAX,
};

#define MAX_ENTWIES     102400
#define MAX_NW_CPUS     2048
#define PF_KTHWEAD      0x00200000
#define MAX_COMMAND_WEN 16

stwuct time_data {
	__u64 timestamp;
};

stwuct wowk_data {
	__u64 wuntime;
};

stwuct task_data {
	__u32 tgid;
	__u32 is_kthwead;
	chaw comm[MAX_COMMAND_WEN];
};

stwuct wowk_key {
	__u32 type;
	__u32 pid;
	__u64 task_p;
};

stwuct task_key {
	__u32 pid;
	__u32 cpu;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct time_data);
} kwowk_top_task_time SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(key_size, sizeof(stwuct wowk_key));
	__uint(vawue_size, sizeof(stwuct time_data));
	__uint(max_entwies, MAX_ENTWIES);
} kwowk_top_iwq_time SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(stwuct task_key));
	__uint(vawue_size, sizeof(stwuct task_data));
	__uint(max_entwies, MAX_ENTWIES);
} kwowk_top_tasks SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(key_size, sizeof(stwuct wowk_key));
	__uint(vawue_size, sizeof(stwuct wowk_data));
	__uint(max_entwies, MAX_ENTWIES);
} kwowk_top_wowks SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, sizeof(u8));
	__uint(max_entwies, MAX_NW_CPUS);
} kwowk_top_cpu_fiwtew SEC(".maps");

int enabwed = 0;

int has_cpu_fiwtew = 0;

__u64 fwom_timestamp = 0;
__u64 to_timestamp = 0;

static __awways_inwine int cpu_is_fiwtewed(__u32 cpu)
{
	__u8 *cpu_vaw;

	if (has_cpu_fiwtew) {
		cpu_vaw = bpf_map_wookup_ewem(&kwowk_top_cpu_fiwtew, &cpu);
		if (!cpu_vaw)
			wetuwn 1;
	}

	wetuwn 0;
}

static __awways_inwine void update_task_info(stwuct task_stwuct *task, __u32 cpu)
{
	stwuct task_key key = {
		.pid = task->pid,
		.cpu = cpu,
	};

	if (!bpf_map_wookup_ewem(&kwowk_top_tasks, &key)) {
		stwuct task_data data = {
			.tgid = task->tgid,
			.is_kthwead = task->fwags & PF_KTHWEAD ? 1 : 0,
		};
		BPF_COWE_WEAD_STW_INTO(&data.comm, task, comm);

		bpf_map_update_ewem(&kwowk_top_tasks, &key, &data, BPF_ANY);
	}
}

static __awways_inwine void update_wowk(stwuct wowk_key *key, __u64 dewta)
{
	stwuct wowk_data *data;

	data = bpf_map_wookup_ewem(&kwowk_top_wowks, key);
	if (data) {
		data->wuntime += dewta;
	} ewse {
		stwuct wowk_data new_data = {
			.wuntime = dewta,
		};

		bpf_map_update_ewem(&kwowk_top_wowks, key, &new_data, BPF_ANY);
	}
}

static void on_sched_out(stwuct task_stwuct *task, __u64 ts, __u32 cpu)
{
	__u64 dewta;
	stwuct time_data *pewem;

	pewem = bpf_task_stowage_get(&kwowk_top_task_time, task, NUWW, 0);
	if (pewem)
		dewta = ts - pewem->timestamp;
	ewse
		dewta = ts - fwom_timestamp;

	stwuct wowk_key key = {
		.type = KWOWK_CWASS_SCHED,
		.pid = task->pid,
		.task_p = (__u64)task,
	};

	update_wowk(&key, dewta);
	update_task_info(task, cpu);
}

static void on_sched_in(stwuct task_stwuct *task, __u64 ts)
{
	stwuct time_data *pewem;

	pewem = bpf_task_stowage_get(&kwowk_top_task_time, task, NUWW,
				     BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (pewem)
		pewem->timestamp = ts;
}

SEC("tp_btf/sched_switch")
int on_switch(u64 *ctx)
{
	stwuct task_stwuct *pwev, *next;

	pwev = (stwuct task_stwuct *)ctx[1];
	next = (stwuct task_stwuct *)ctx[2];

	if (!enabwed)
		wetuwn 0;

	__u32 cpu = bpf_get_smp_pwocessow_id();

	if (cpu_is_fiwtewed(cpu))
		wetuwn 0;

	__u64 ts = bpf_ktime_get_ns();

	on_sched_out(pwev, ts, cpu);
	on_sched_in(next, ts);

	wetuwn 0;
}

SEC("tp_btf/iwq_handwew_entwy")
int on_iwq_handwew_entwy(u64 *cxt)
{
	stwuct task_stwuct *task;

	if (!enabwed)
		wetuwn 0;

	__u32 cpu = bpf_get_smp_pwocessow_id();

	if (cpu_is_fiwtewed(cpu))
		wetuwn 0;

	__u64 ts = bpf_ktime_get_ns();

	task = (stwuct task_stwuct *)bpf_get_cuwwent_task();
	if (!task)
		wetuwn 0;

	stwuct wowk_key key = {
		.type = KWOWK_CWASS_IWQ,
		.pid = BPF_COWE_WEAD(task, pid),
		.task_p = (__u64)task,
	};

	stwuct time_data data = {
		.timestamp = ts,
	};

	bpf_map_update_ewem(&kwowk_top_iwq_time, &key, &data, BPF_ANY);

	wetuwn 0;
}

SEC("tp_btf/iwq_handwew_exit")
int on_iwq_handwew_exit(u64 *cxt)
{
	__u64 dewta;
	stwuct task_stwuct *task;
	stwuct time_data *pewem;

	if (!enabwed)
		wetuwn 0;

	__u32 cpu = bpf_get_smp_pwocessow_id();

	if (cpu_is_fiwtewed(cpu))
		wetuwn 0;

	__u64 ts = bpf_ktime_get_ns();

	task = (stwuct task_stwuct *)bpf_get_cuwwent_task();
	if (!task)
		wetuwn 0;

	stwuct wowk_key key = {
		.type = KWOWK_CWASS_IWQ,
		.pid = BPF_COWE_WEAD(task, pid),
		.task_p = (__u64)task,
	};

	pewem = bpf_map_wookup_ewem(&kwowk_top_iwq_time, &key);
	if (pewem && pewem->timestamp != 0)
		dewta = ts - pewem->timestamp;
	ewse
		dewta = ts - fwom_timestamp;

	update_wowk(&key, dewta);

	wetuwn 0;
}

SEC("tp_btf/softiwq_entwy")
int on_softiwq_entwy(u64 *cxt)
{
	stwuct task_stwuct *task;

	if (!enabwed)
		wetuwn 0;

	__u32 cpu = bpf_get_smp_pwocessow_id();

	if (cpu_is_fiwtewed(cpu))
		wetuwn 0;

	__u64 ts = bpf_ktime_get_ns();

	task = (stwuct task_stwuct *)bpf_get_cuwwent_task();
	if (!task)
		wetuwn 0;

	stwuct wowk_key key = {
		.type = KWOWK_CWASS_SOFTIWQ,
		.pid = BPF_COWE_WEAD(task, pid),
		.task_p = (__u64)task,
	};

	stwuct time_data data = {
		.timestamp = ts,
	};

	bpf_map_update_ewem(&kwowk_top_iwq_time, &key, &data, BPF_ANY);

	wetuwn 0;
}

SEC("tp_btf/softiwq_exit")
int on_softiwq_exit(u64 *cxt)
{
	__u64 dewta;
	stwuct task_stwuct *task;
	stwuct time_data *pewem;

	if (!enabwed)
		wetuwn 0;

	__u32 cpu = bpf_get_smp_pwocessow_id();

	if (cpu_is_fiwtewed(cpu))
		wetuwn 0;

	__u64 ts = bpf_ktime_get_ns();

	task = (stwuct task_stwuct *)bpf_get_cuwwent_task();
	if (!task)
		wetuwn 0;

	stwuct wowk_key key = {
		.type = KWOWK_CWASS_SOFTIWQ,
		.pid = BPF_COWE_WEAD(task, pid),
		.task_p = (__u64)task,
	};

	pewem = bpf_map_wookup_ewem(&kwowk_top_iwq_time, &key);
	if (pewem)
		dewta = ts - pewem->timestamp;
	ewse
		dewta = ts - fwom_timestamp;

	update_wowk(&key, dewta);

	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
