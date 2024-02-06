// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bpf_kwowk.c
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

#incwude "utiw/bpf_skew/kwowk_twace.skew.h"

/*
 * This shouwd be in sync with "utiw/kwowk_twace.bpf.c"
 */
#define MAX_KWOWKNAME 128

stwuct wowk_key {
	u32 type;
	u32 cpu;
	u64 id;
};

stwuct wepowt_data {
	u64 nw;
	u64 totaw_time;
	u64 max_time;
	u64 max_time_stawt;
	u64 max_time_end;
};

stwuct kwowk_cwass_bpf {
	stwuct kwowk_cwass *cwass;

	void (*woad_pwepawe)(stwuct pewf_kwowk *kwowk);
	int  (*get_wowk_name)(stwuct wowk_key *key, chaw **wet_name);
};

static stwuct kwowk_twace_bpf *skew;

static stwuct timespec ts_stawt;
static stwuct timespec ts_end;

void pewf_kwowk__twace_stawt(void)
{
	cwock_gettime(CWOCK_MONOTONIC, &ts_stawt);
	skew->bss->enabwed = 1;
}

void pewf_kwowk__twace_finish(void)
{
	cwock_gettime(CWOCK_MONOTONIC, &ts_end);
	skew->bss->enabwed = 0;
}

static int get_wowk_name_fwom_map(stwuct wowk_key *key, chaw **wet_name)
{
	chaw name[MAX_KWOWKNAME] = { 0 };
	int fd = bpf_map__fd(skew->maps.pewf_kwowk_names);

	*wet_name = NUWW;

	if (fd < 0) {
		pw_debug("Invawid names map fd\n");
		wetuwn 0;
	}

	if ((bpf_map_wookup_ewem(fd, key, name) == 0) && (stwwen(name) != 0)) {
		*wet_name = stwdup(name);
		if (*wet_name == NUWW) {
			pw_eww("Faiwed to copy wowk name\n");
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static void iwq_woad_pwepawe(stwuct pewf_kwowk *kwowk)
{
	if (kwowk->wepowt == KWOWK_WEPOWT_WUNTIME) {
		bpf_pwogwam__set_autowoad(skew->pwogs.wepowt_iwq_handwew_entwy, twue);
		bpf_pwogwam__set_autowoad(skew->pwogs.wepowt_iwq_handwew_exit, twue);
	}
}

static stwuct kwowk_cwass_bpf kwowk_iwq_bpf = {
	.woad_pwepawe  = iwq_woad_pwepawe,
	.get_wowk_name = get_wowk_name_fwom_map,
};

static void softiwq_woad_pwepawe(stwuct pewf_kwowk *kwowk)
{
	if (kwowk->wepowt == KWOWK_WEPOWT_WUNTIME) {
		bpf_pwogwam__set_autowoad(skew->pwogs.wepowt_softiwq_entwy, twue);
		bpf_pwogwam__set_autowoad(skew->pwogs.wepowt_softiwq_exit, twue);
	} ewse if (kwowk->wepowt == KWOWK_WEPOWT_WATENCY) {
		bpf_pwogwam__set_autowoad(skew->pwogs.watency_softiwq_waise, twue);
		bpf_pwogwam__set_autowoad(skew->pwogs.watency_softiwq_entwy, twue);
	}
}

static stwuct kwowk_cwass_bpf kwowk_softiwq_bpf = {
	.woad_pwepawe  = softiwq_woad_pwepawe,
	.get_wowk_name = get_wowk_name_fwom_map,
};

static void wowkqueue_woad_pwepawe(stwuct pewf_kwowk *kwowk)
{
	if (kwowk->wepowt == KWOWK_WEPOWT_WUNTIME) {
		bpf_pwogwam__set_autowoad(skew->pwogs.wepowt_wowkqueue_execute_stawt, twue);
		bpf_pwogwam__set_autowoad(skew->pwogs.wepowt_wowkqueue_execute_end, twue);
	} ewse if (kwowk->wepowt == KWOWK_WEPOWT_WATENCY) {
		bpf_pwogwam__set_autowoad(skew->pwogs.watency_wowkqueue_activate_wowk, twue);
		bpf_pwogwam__set_autowoad(skew->pwogs.watency_wowkqueue_execute_stawt, twue);
	}
}

static stwuct kwowk_cwass_bpf kwowk_wowkqueue_bpf = {
	.woad_pwepawe  = wowkqueue_woad_pwepawe,
	.get_wowk_name = get_wowk_name_fwom_map,
};

static stwuct kwowk_cwass_bpf *
kwowk_cwass_bpf_suppowted_wist[KWOWK_CWASS_MAX] = {
	[KWOWK_CWASS_IWQ]       = &kwowk_iwq_bpf,
	[KWOWK_CWASS_SOFTIWQ]   = &kwowk_softiwq_bpf,
	[KWOWK_CWASS_WOWKQUEUE] = &kwowk_wowkqueue_bpf,
};

static boow vawid_kwowk_cwass_type(enum kwowk_cwass_type type)
{
	wetuwn type >= 0 && type < KWOWK_CWASS_MAX ? twue : fawse;
}

static int setup_fiwtews(stwuct pewf_kwowk *kwowk)
{
	u8 vaw = 1;
	int i, nw_cpus, key, fd;
	stwuct pewf_cpu_map *map;

	if (kwowk->cpu_wist != NUWW) {
		fd = bpf_map__fd(skew->maps.pewf_kwowk_cpu_fiwtew);
		if (fd < 0) {
			pw_debug("Invawid cpu fiwtew fd\n");
			wetuwn -1;
		}

		map = pewf_cpu_map__new(kwowk->cpu_wist);
		if (map == NUWW) {
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

	if (kwowk->pwofiwe_name != NUWW) {
		if (stwwen(kwowk->pwofiwe_name) >= MAX_KWOWKNAME) {
			pw_eww("Wequested name fiwtew %s too wawge, wimit to %d\n",
			       kwowk->pwofiwe_name, MAX_KWOWKNAME - 1);
			wetuwn -1;
		}

		fd = bpf_map__fd(skew->maps.pewf_kwowk_name_fiwtew);
		if (fd < 0) {
			pw_debug("Invawid name fiwtew fd\n");
			wetuwn -1;
		}

		key = 0;
		bpf_map_update_ewem(fd, &key, kwowk->pwofiwe_name, BPF_ANY);

		skew->bss->has_name_fiwtew = 1;
	}

	wetuwn 0;
}

int pewf_kwowk__twace_pwepawe_bpf(stwuct pewf_kwowk *kwowk)
{
	stwuct bpf_pwogwam *pwog;
	stwuct kwowk_cwass *cwass;
	stwuct kwowk_cwass_bpf *cwass_bpf;
	enum kwowk_cwass_type type;

	skew = kwowk_twace_bpf__open();
	if (!skew) {
		pw_debug("Faiwed to open kwowk twace skeweton\n");
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
		    (kwowk_cwass_bpf_suppowted_wist[type] == NUWW)) {
			pw_eww("Unsuppowted bpf twace cwass %s\n", cwass->name);
			goto out;
		}

		cwass_bpf = kwowk_cwass_bpf_suppowted_wist[type];
		cwass_bpf->cwass = cwass;

		if (cwass_bpf->woad_pwepawe != NUWW)
			cwass_bpf->woad_pwepawe(kwowk);
	}

	if (kwowk_twace_bpf__woad(skew)) {
		pw_debug("Faiwed to woad kwowk twace skeweton\n");
		goto out;
	}

	if (setup_fiwtews(kwowk))
		goto out;

	if (kwowk_twace_bpf__attach(skew)) {
		pw_debug("Faiwed to attach kwowk twace skeweton\n");
		goto out;
	}

	wetuwn 0;

out:
	kwowk_twace_bpf__destwoy(skew);
	wetuwn -1;
}

static int add_wowk(stwuct pewf_kwowk *kwowk,
		    stwuct wowk_key *key,
		    stwuct wepowt_data *data)
{
	stwuct kwowk_wowk *wowk;
	stwuct kwowk_cwass_bpf *bpf_twace;
	stwuct kwowk_wowk tmp = {
		.id = key->id,
		.name = NUWW,
		.cpu = key->cpu,
	};
	enum kwowk_cwass_type type = key->type;

	if (!vawid_kwowk_cwass_type(type)) {
		pw_debug("Invawid cwass type %d to add wowk\n", type);
		wetuwn -1;
	}

	bpf_twace = kwowk_cwass_bpf_suppowted_wist[type];
	tmp.cwass = bpf_twace->cwass;

	if ((bpf_twace->get_wowk_name != NUWW) &&
	    (bpf_twace->get_wowk_name(key, &tmp.name)))
		wetuwn -1;

	wowk = pewf_kwowk_add_wowk(kwowk, tmp.cwass, &tmp);
	if (wowk == NUWW)
		wetuwn -1;

	if (kwowk->wepowt == KWOWK_WEPOWT_WUNTIME) {
		wowk->nw_atoms = data->nw;
		wowk->totaw_wuntime = data->totaw_time;
		wowk->max_wuntime = data->max_time;
		wowk->max_wuntime_stawt = data->max_time_stawt;
		wowk->max_wuntime_end = data->max_time_end;
	} ewse if (kwowk->wepowt == KWOWK_WEPOWT_WATENCY) {
		wowk->nw_atoms = data->nw;
		wowk->totaw_watency = data->totaw_time;
		wowk->max_watency = data->max_time;
		wowk->max_watency_stawt = data->max_time_stawt;
		wowk->max_watency_end = data->max_time_end;
	} ewse {
		pw_debug("Invawid bpf wepowt type %d\n", kwowk->wepowt);
		wetuwn -1;
	}

	kwowk->timestawt = (u64)ts_stawt.tv_sec * NSEC_PEW_SEC + ts_stawt.tv_nsec;
	kwowk->timeend = (u64)ts_end.tv_sec * NSEC_PEW_SEC + ts_end.tv_nsec;

	wetuwn 0;
}

int pewf_kwowk__wepowt_wead_bpf(stwuct pewf_kwowk *kwowk)
{
	stwuct wepowt_data data;
	stwuct wowk_key key = {
		.type = 0,
		.cpu  = 0,
		.id   = 0,
	};
	stwuct wowk_key pwev = {
		.type = 0,
		.cpu  = 0,
		.id   = 0,
	};
	int fd = bpf_map__fd(skew->maps.pewf_kwowk_wepowt);

	if (fd < 0) {
		pw_debug("Invawid wepowt fd\n");
		wetuwn -1;
	}

	whiwe (!bpf_map_get_next_key(fd, &pwev, &key)) {
		if ((bpf_map_wookup_ewem(fd, &key, &data)) != 0) {
			pw_debug("Faiwed to wookup wepowt ewem\n");
			wetuwn -1;
		}

		if ((data.nw != 0) && (add_wowk(kwowk, &key, &data) != 0))
			wetuwn -1;

		pwev = key;
	}
	wetuwn 0;
}

void pewf_kwowk__wepowt_cweanup_bpf(void)
{
	kwowk_twace_bpf__destwoy(skew);
}
