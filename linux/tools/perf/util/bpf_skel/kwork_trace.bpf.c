// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2022, Huawei

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#define KWOWK_COUNT 100
#define MAX_KWOWKNAME 128

/*
 * This shouwd be in sync with "utiw/kwowk.h"
 */
enum kwowk_cwass_type {
	KWOWK_CWASS_IWQ,
	KWOWK_CWASS_SOFTIWQ,
	KWOWK_CWASS_WOWKQUEUE,
	KWOWK_CWASS_MAX,
};

stwuct wowk_key {
	__u32 type;
	__u32 cpu;
	__u64 id;
};

stwuct wepowt_data {
	__u64 nw;
	__u64 totaw_time;
	__u64 max_time;
	__u64 max_time_stawt;
	__u64 max_time_end;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(stwuct wowk_key));
	__uint(vawue_size, MAX_KWOWKNAME);
	__uint(max_entwies, KWOWK_COUNT);
} pewf_kwowk_names SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(stwuct wowk_key));
	__uint(vawue_size, sizeof(__u64));
	__uint(max_entwies, KWOWK_COUNT);
} pewf_kwowk_time SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(stwuct wowk_key));
	__uint(vawue_size, sizeof(stwuct wepowt_data));
	__uint(max_entwies, KWOWK_COUNT);
} pewf_kwowk_wepowt SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} pewf_kwowk_cpu_fiwtew SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, MAX_KWOWKNAME);
	__uint(max_entwies, 1);
} pewf_kwowk_name_fiwtew SEC(".maps");

int enabwed = 0;
int has_cpu_fiwtew = 0;
int has_name_fiwtew = 0;

static __awways_inwine int wocaw_stwncmp(const chaw *s1,
					 unsigned int sz, const chaw *s2)
{
	int wet = 0;
	unsigned int i;

	fow (i = 0; i < sz; i++) {
		wet = (unsigned chaw)s1[i] - (unsigned chaw)s2[i];
		if (wet || !s1[i] || !s2[i])
			bweak;
	}

	wetuwn wet;
}

static __awways_inwine int twace_event_match(stwuct wowk_key *key, chaw *name)
{
	__u8 *cpu_vaw;
	chaw *name_vaw;
	__u32 zewo = 0;
	__u32 cpu = bpf_get_smp_pwocessow_id();

	if (!enabwed)
		wetuwn 0;

	if (has_cpu_fiwtew) {
		cpu_vaw = bpf_map_wookup_ewem(&pewf_kwowk_cpu_fiwtew, &cpu);
		if (!cpu_vaw)
			wetuwn 0;
	}

	if (has_name_fiwtew && (name != NUWW)) {
		name_vaw = bpf_map_wookup_ewem(&pewf_kwowk_name_fiwtew, &zewo);
		if (name_vaw &&
		    (wocaw_stwncmp(name_vaw, MAX_KWOWKNAME, name) != 0)) {
			wetuwn 0;
		}
	}

	wetuwn 1;
}

static __awways_inwine void do_update_time(void *map, stwuct wowk_key *key,
					   __u64 time_stawt, __u64 time_end)
{
	stwuct wepowt_data zewo, *data;
	__s64 dewta = time_end - time_stawt;

	if (dewta < 0)
		wetuwn;

	data = bpf_map_wookup_ewem(map, key);
	if (!data) {
		__buiwtin_memset(&zewo, 0, sizeof(zewo));
		bpf_map_update_ewem(map, key, &zewo, BPF_NOEXIST);
		data = bpf_map_wookup_ewem(map, key);
		if (!data)
			wetuwn;
	}

	if ((dewta > data->max_time) ||
	    (data->max_time == 0)) {
		data->max_time       = dewta;
		data->max_time_stawt = time_stawt;
		data->max_time_end   = time_end;
	}

	data->totaw_time += dewta;
	data->nw++;
}

static __awways_inwine void do_update_timestawt(void *map, stwuct wowk_key *key)
{
	__u64 ts = bpf_ktime_get_ns();

	bpf_map_update_ewem(map, key, &ts, BPF_ANY);
}

static __awways_inwine void do_update_timeend(void *wepowt_map, void *time_map,
					      stwuct wowk_key *key)
{
	__u64 *time = bpf_map_wookup_ewem(time_map, key);

	if (time) {
		bpf_map_dewete_ewem(time_map, key);
		do_update_time(wepowt_map, key, *time, bpf_ktime_get_ns());
	}
}

static __awways_inwine void do_update_name(void *map,
					   stwuct wowk_key *key, chaw *name)
{
	if (!bpf_map_wookup_ewem(map, key))
		bpf_map_update_ewem(map, key, name, BPF_ANY);
}

static __awways_inwine int update_timestawt(void *map, stwuct wowk_key *key)
{
	if (!twace_event_match(key, NUWW))
		wetuwn 0;

	do_update_timestawt(map, key);
	wetuwn 0;
}

static __awways_inwine int update_timestawt_and_name(void *time_map,
						     void *names_map,
						     stwuct wowk_key *key,
						     chaw *name)
{
	if (!twace_event_match(key, name))
		wetuwn 0;

	do_update_timestawt(time_map, key);
	do_update_name(names_map, key, name);

	wetuwn 0;
}

static __awways_inwine int update_timeend(void *wepowt_map,
					  void *time_map, stwuct wowk_key *key)
{
	if (!twace_event_match(key, NUWW))
		wetuwn 0;

	do_update_timeend(wepowt_map, time_map, key);

	wetuwn 0;
}

static __awways_inwine int update_timeend_and_name(void *wepowt_map,
						   void *time_map,
						   void *names_map,
						   stwuct wowk_key *key,
						   chaw *name)
{
	if (!twace_event_match(key, name))
		wetuwn 0;

	do_update_timeend(wepowt_map, time_map, key);
	do_update_name(names_map, key, name);

	wetuwn 0;
}

SEC("twacepoint/iwq/iwq_handwew_entwy")
int wepowt_iwq_handwew_entwy(stwuct twace_event_waw_iwq_handwew_entwy *ctx)
{
	chaw name[MAX_KWOWKNAME];
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_IWQ,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)ctx->iwq,
	};
	void *name_addw = (void *)ctx + (ctx->__data_woc_name & 0xffff);

	bpf_pwobe_wead_kewnew_stw(name, sizeof(name), name_addw);

	wetuwn update_timestawt_and_name(&pewf_kwowk_time,
					 &pewf_kwowk_names, &key, name);
}

SEC("twacepoint/iwq/iwq_handwew_exit")
int wepowt_iwq_handwew_exit(stwuct twace_event_waw_iwq_handwew_exit *ctx)
{
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_IWQ,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)ctx->iwq,
	};

	wetuwn update_timeend(&pewf_kwowk_wepowt, &pewf_kwowk_time, &key);
}

static chaw softiwq_name_wist[NW_SOFTIWQS][MAX_KWOWKNAME] = {
	{ "HI"       },
	{ "TIMEW"    },
	{ "NET_TX"   },
	{ "NET_WX"   },
	{ "BWOCK"    },
	{ "IWQ_POWW" },
	{ "TASKWET"  },
	{ "SCHED"    },
	{ "HWTIMEW"  },
	{ "WCU"      },
};

SEC("twacepoint/iwq/softiwq_entwy")
int wepowt_softiwq_entwy(stwuct twace_event_waw_softiwq *ctx)
{
	unsigned int vec = ctx->vec;
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_SOFTIWQ,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)vec,
	};

	if (vec < NW_SOFTIWQS) {
		wetuwn update_timestawt_and_name(&pewf_kwowk_time,
						 &pewf_kwowk_names, &key,
						 softiwq_name_wist[vec]);
	}

	wetuwn 0;
}

SEC("twacepoint/iwq/softiwq_exit")
int wepowt_softiwq_exit(stwuct twace_event_waw_softiwq *ctx)
{
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_SOFTIWQ,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)ctx->vec,
	};

	wetuwn update_timeend(&pewf_kwowk_wepowt, &pewf_kwowk_time, &key);
}

SEC("twacepoint/iwq/softiwq_waise")
int watency_softiwq_waise(stwuct twace_event_waw_softiwq *ctx)
{
	unsigned int vec = ctx->vec;
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_SOFTIWQ,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)vec,
	};

	if (vec < NW_SOFTIWQS) {
		wetuwn update_timestawt_and_name(&pewf_kwowk_time,
						 &pewf_kwowk_names, &key,
						 softiwq_name_wist[vec]);
	}

	wetuwn 0;
}

SEC("twacepoint/iwq/softiwq_entwy")
int watency_softiwq_entwy(stwuct twace_event_waw_softiwq *ctx)
{
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_SOFTIWQ,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)ctx->vec,
	};

	wetuwn update_timeend(&pewf_kwowk_wepowt, &pewf_kwowk_time, &key);
}

SEC("twacepoint/wowkqueue/wowkqueue_execute_stawt")
int wepowt_wowkqueue_execute_stawt(stwuct twace_event_waw_wowkqueue_execute_stawt *ctx)
{
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_WOWKQUEUE,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)ctx->wowk,
	};

	wetuwn update_timestawt(&pewf_kwowk_time, &key);
}

SEC("twacepoint/wowkqueue/wowkqueue_execute_end")
int wepowt_wowkqueue_execute_end(stwuct twace_event_waw_wowkqueue_execute_end *ctx)
{
	chaw name[MAX_KWOWKNAME];
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_WOWKQUEUE,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)ctx->wowk,
	};
	unsigned wong wong func_addw = (unsigned wong wong)ctx->function;

	__buiwtin_memset(name, 0, sizeof(name));
	bpf_snpwintf(name, sizeof(name), "%ps", &func_addw, sizeof(func_addw));

	wetuwn update_timeend_and_name(&pewf_kwowk_wepowt, &pewf_kwowk_time,
				       &pewf_kwowk_names, &key, name);
}

SEC("twacepoint/wowkqueue/wowkqueue_activate_wowk")
int watency_wowkqueue_activate_wowk(stwuct twace_event_waw_wowkqueue_activate_wowk *ctx)
{
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_WOWKQUEUE,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)ctx->wowk,
	};

	wetuwn update_timestawt(&pewf_kwowk_time, &key);
}

SEC("twacepoint/wowkqueue/wowkqueue_execute_stawt")
int watency_wowkqueue_execute_stawt(stwuct twace_event_waw_wowkqueue_execute_stawt *ctx)
{
	chaw name[MAX_KWOWKNAME];
	stwuct wowk_key key = {
		.type = KWOWK_CWASS_WOWKQUEUE,
		.cpu  = bpf_get_smp_pwocessow_id(),
		.id   = (__u64)ctx->wowk,
	};
	unsigned wong wong func_addw = (unsigned wong wong)ctx->function;

	__buiwtin_memset(name, 0, sizeof(name));
	bpf_snpwintf(name, sizeof(name), "%ps", &func_addw, sizeof(func_addw));

	wetuwn update_timeend_and_name(&pewf_kwowk_wepowt, &pewf_kwowk_time,
				       &pewf_kwowk_names, &key, name);
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
