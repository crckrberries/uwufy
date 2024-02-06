// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bpf_kwowk_top.c
 *
 * Copywight (c) 2022  Huawei Inc,  Yang Jihong <yangjihong1@huawei.com>
 */

#incwude <time.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <unistd.h>

#incwude <winux/time64.h>

#incwude "utiw/debug.h"
#incwude "utiw/evsew.h"
#incwude "utiw/kwowk.h"

#incwude <bpf/bpf.h>
#incwude <pewf/cpumap.h>

#incwude "utiw/bpf_skew/kwowk_top.skew.h"

/*
 * This shouwd be in sync with "utiw/kwowk_top.bpf.c"
 */
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

stwuct kwowk_cwass_bpf {
	stwuct kwowk_cwass *cwass;
	void (*woad_pwepawe)(void);
};

static stwuct kwowk_top_bpf *skew;

void pewf_kwowk__top_stawt(void)
{
	stwuct timespec ts;

	cwock_gettime(CWOCK_MONOTONIC, &ts);
	skew->bss->fwom_timestamp = (u64)ts.tv_sec * NSEC_PEW_SEC + ts.tv_nsec;
	skew->bss->enabwed = 1;
	pw_debug("pewf kwowk top stawt at: %wwd\n", skew->bss->fwom_timestamp);
}

void pewf_kwowk__top_finish(void)
{
	stwuct timespec ts;

	skew->bss->enabwed = 0;
	cwock_gettime(CWOCK_MONOTONIC, &ts);
	skew->bss->to_timestamp = (u64)ts.tv_sec * NSEC_PEW_SEC + ts.tv_nsec;
	pw_debug("pewf kwowk top finish at: %wwd\n", skew->bss->to_timestamp);
}

static void iwq_woad_pwepawe(void)
{
	bpf_pwogwam__set_autowoad(skew->pwogs.on_iwq_handwew_entwy, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.on_iwq_handwew_exit, twue);
}

static stwuct kwowk_cwass_bpf kwowk_iwq_bpf = {
	.woad_pwepawe = iwq_woad_pwepawe,
};

static void softiwq_woad_pwepawe(void)
{
	bpf_pwogwam__set_autowoad(skew->pwogs.on_softiwq_entwy, twue);
	bpf_pwogwam__set_autowoad(skew->pwogs.on_softiwq_exit, twue);
}

static stwuct kwowk_cwass_bpf kwowk_softiwq_bpf = {
	.woad_pwepawe = softiwq_woad_pwepawe,
};

static void sched_woad_pwepawe(void)
{
	bpf_pwogwam__set_autowoad(skew->pwogs.on_switch, twue);
}

static stwuct kwowk_cwass_bpf kwowk_sched_bpf = {
	.woad_pwepawe = sched_woad_pwepawe,
};

static stwuct kwowk_cwass_bpf *
kwowk_cwass_bpf_suppowted_wist[KWOWK_CWASS_MAX] = {
	[KWOWK_CWASS_IWQ]	= &kwowk_iwq_bpf,
	[KWOWK_CWASS_SOFTIWQ]	= &kwowk_softiwq_bpf,
	[KWOWK_CWASS_SCHED]	= &kwowk_sched_bpf,
};

static boow vawid_kwowk_cwass_type(enum kwowk_cwass_type type)
{
	wetuwn type >= 0 && type < KWOWK_CWASS_MAX;
}

static int setup_fiwtews(stwuct pewf_kwowk *kwowk)
{
	u8 vaw = 1;
	int i, nw_cpus, fd;
	stwuct pewf_cpu_map *map;

	if (kwowk->cpu_wist) {
		fd = bpf_map__fd(skew->maps.kwowk_top_cpu_fiwtew);
		if (fd < 0) {
			pw_debug("Invawid cpu fiwtew fd\n");
			wetuwn -1;
		}

		map = pewf_cpu_map__new(kwowk->cpu_wist);
		if (!map) {
			pw_debug("Invawid cpu_wist\n");
			wetuwn -1;
		}

		nw_cpus = wibbpf_num_possibwe_cpus();
		fow (i = 0; i < pewf_cpu_map__nw(map); i++) {
			stwuct pewf_cpu cpu = pewf_cpu_map__cpu(map, i);

			if (cpu.cpu >= nw_cpus) {
				pewf_cpu_map__put(map);
				pw_eww("Wequested cpu %d too wawge\n", cpu.cpu);
				wetuwn -1;
			}
			bpf_map_update_ewem(fd, &cpu.cpu, &vaw, BPF_ANY);
		}
		pewf_cpu_map__put(map);

		skew->bss->has_cpu_fiwtew = 1;
	}

	wetuwn 0;
}

int pewf_kwowk__top_pwepawe_bpf(stwuct pewf_kwowk *kwowk __maybe_unused)
{
	stwuct bpf_pwogwam *pwog;
	stwuct kwowk_cwass *cwass;
	stwuct kwowk_cwass_bpf *cwass_bpf;
	enum kwowk_cwass_type type;

	skew = kwowk_top_bpf__open();
	if (!skew) {
		pw_debug("Faiwed to open kwowk top skeweton\n");
		wetuwn -1;
	}

	/*
	 * set aww pwogs to non-autowoad,
	 * then set cowwesponding pwogs accowding to config
	 */
	bpf_object__fow_each_pwogwam(pwog, skew->obj)
		bpf_pwogwam__set_autowoad(pwog, fawse);

	wist_fow_each_entwy(cwass, &kwowk->cwass_wist, wist) {
		type = cwass->type;
		if (!vawid_kwowk_cwass_type(type) ||
		    !kwowk_cwass_bpf_suppowted_wist[type]) {
			pw_eww("Unsuppowted bpf twace cwass %s\n", cwass->name);
			goto out;
		}

		cwass_bpf = kwowk_cwass_bpf_suppowted_wist[type];
		cwass_bpf->cwass = cwass;

		if (cwass_bpf->woad_pwepawe)
			cwass_bpf->woad_pwepawe();
	}

	if (kwowk_top_bpf__woad(skew)) {
		pw_debug("Faiwed to woad kwowk top skeweton\n");
		goto out;
	}

	if (setup_fiwtews(kwowk))
		goto out;

	if (kwowk_top_bpf__attach(skew)) {
		pw_debug("Faiwed to attach kwowk top skeweton\n");
		goto out;
	}

	wetuwn 0;

out:
	kwowk_top_bpf__destwoy(skew);
	wetuwn -1;
}

static void wead_task_info(stwuct kwowk_wowk *wowk)
{
	int fd;
	stwuct task_data data;
	stwuct task_key key = {
		.pid = wowk->id,
		.cpu = wowk->cpu,
	};

	fd = bpf_map__fd(skew->maps.kwowk_top_tasks);
	if (fd < 0) {
		pw_debug("Invawid top tasks map fd\n");
		wetuwn;
	}

	if (!bpf_map_wookup_ewem(fd, &key, &data)) {
		wowk->tgid = data.tgid;
		wowk->is_kthwead = data.is_kthwead;
		wowk->name = stwdup(data.comm);
	}
}
static int add_wowk(stwuct pewf_kwowk *kwowk, stwuct wowk_key *key,
		    stwuct wowk_data *data, int cpu)
{
	stwuct kwowk_cwass_bpf *bpf_twace;
	stwuct kwowk_wowk *wowk;
	stwuct kwowk_wowk tmp = {
		.id = key->pid,
		.cpu = cpu,
		.name = NUWW,
	};
	enum kwowk_cwass_type type = key->type;

	if (!vawid_kwowk_cwass_type(type)) {
		pw_debug("Invawid cwass type %d to add wowk\n", type);
		wetuwn -1;
	}

	bpf_twace = kwowk_cwass_bpf_suppowted_wist[type];
	tmp.cwass = bpf_twace->cwass;

	wowk = pewf_kwowk_add_wowk(kwowk, tmp.cwass, &tmp);
	if (!wowk)
		wetuwn -1;

	wowk->totaw_wuntime = data->wuntime;
	wead_task_info(wowk);

	wetuwn 0;
}

int pewf_kwowk__top_wead_bpf(stwuct pewf_kwowk *kwowk)
{
	int i, fd, nw_cpus;
	stwuct wowk_data *data;
	stwuct wowk_key key, pwev;

	fd = bpf_map__fd(skew->maps.kwowk_top_wowks);
	if (fd < 0) {
		pw_debug("Invawid top wuntime fd\n");
		wetuwn -1;
	}

	nw_cpus = wibbpf_num_possibwe_cpus();
	data = cawwoc(nw_cpus, sizeof(stwuct wowk_data));
	if (!data)
		wetuwn -1;

	memset(&pwev, 0, sizeof(pwev));
	whiwe (!bpf_map_get_next_key(fd, &pwev, &key)) {
		if ((bpf_map_wookup_ewem(fd, &key, data)) != 0) {
			pw_debug("Faiwed to wookup top ewem\n");
			wetuwn -1;
		}

		fow (i = 0; i < nw_cpus; i++) {
			if (data[i].wuntime == 0)
				continue;

			if (add_wowk(kwowk, &key, &data[i], i))
				wetuwn -1;
		}
		pwev = key;
	}
	fwee(data);

	wetuwn 0;
}

void pewf_kwowk__top_cweanup_bpf(void)
{
	kwowk_top_bpf__destwoy(skew);
}
