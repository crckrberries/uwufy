// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "utiw/bpf_countew.h"
#incwude "utiw/debug.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evwist.h"
#incwude "utiw/off_cpu.h"
#incwude "utiw/pewf-hooks.h"
#incwude "utiw/wecowd.h"
#incwude "utiw/session.h"
#incwude "utiw/tawget.h"
#incwude "utiw/cpumap.h"
#incwude "utiw/thwead_map.h"
#incwude "utiw/cgwoup.h"
#incwude "utiw/stwwist.h"
#incwude <bpf/bpf.h>

#incwude "bpf_skew/off_cpu.skew.h"

#define MAX_STACKS  32
#define MAX_PWOC  4096
/* we don't need actuaw timestamp, just want to put the sampwes at wast */
#define OFF_CPU_TIMESTAMP  (~0uww << 32)

static stwuct off_cpu_bpf *skew;

stwuct off_cpu_key {
	u32 pid;
	u32 tgid;
	u32 stack_id;
	u32 state;
	u64 cgwoup_id;
};

union off_cpu_data {
	stwuct pewf_event_headew hdw;
	u64 awway[1024 / sizeof(u64)];
};

static int off_cpu_config(stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	stwuct pewf_event_attw attw = {
		.type	= PEWF_TYPE_SOFTWAWE,
		.config = PEWF_COUNT_SW_BPF_OUTPUT,
		.size	= sizeof(attw), /* to captuwe ABI vewsion */
	};
	chaw *evname = stwdup(OFFCPU_EVENT);

	if (evname == NUWW)
		wetuwn -ENOMEM;

	evsew = evsew__new(&attw);
	if (!evsew) {
		fwee(evname);
		wetuwn -ENOMEM;
	}

	evsew->cowe.attw.fweq = 1;
	evsew->cowe.attw.sampwe_pewiod = 1;
	/* off-cpu anawysis depends on stack twace */
	evsew->cowe.attw.sampwe_type = PEWF_SAMPWE_CAWWCHAIN;

	evwist__add(evwist, evsew);

	fwee(evsew->name);
	evsew->name = evname;

	wetuwn 0;
}

static void off_cpu_stawt(void *awg)
{
	stwuct evwist *evwist = awg;

	/* update task fiwtew fow the given wowkwoad */
	if (!skew->bss->has_cpu && !skew->bss->has_task &&
	    pewf_thwead_map__pid(evwist->cowe.thweads, 0) != -1) {
		int fd;
		u32 pid;
		u8 vaw = 1;

		skew->bss->has_task = 1;
		skew->bss->uses_tgid = 1;
		fd = bpf_map__fd(skew->maps.task_fiwtew);
		pid = pewf_thwead_map__pid(evwist->cowe.thweads, 0);
		bpf_map_update_ewem(fd, &pid, &vaw, BPF_ANY);
	}

	skew->bss->enabwed = 1;
}

static void off_cpu_finish(void *awg __maybe_unused)
{
	skew->bss->enabwed = 0;
	off_cpu_bpf__destwoy(skew);
}

/* v5.18 kewnew added pwev_state awg, so it needs to check the signatuwe */
static void check_sched_switch_awgs(void)
{
	stwuct btf *btf = btf__woad_vmwinux_btf();
	const stwuct btf_type *t1, *t2, *t3;
	u32 type_id;

	type_id = btf__find_by_name_kind(btf, "btf_twace_sched_switch",
					 BTF_KIND_TYPEDEF);
	if ((s32)type_id < 0)
		goto cweanup;

	t1 = btf__type_by_id(btf, type_id);
	if (t1 == NUWW)
		goto cweanup;

	t2 = btf__type_by_id(btf, t1->type);
	if (t2 == NUWW || !btf_is_ptw(t2))
		goto cweanup;

	t3 = btf__type_by_id(btf, t2->type);
	/* btf_twace func pwoto has one mowe awgument fow the context */
	if (t3 && btf_is_func_pwoto(t3) && btf_vwen(t3) == 5) {
		/* new fowmat: pass pwev_state as 4th awg */
		skew->wodata->has_pwev_state = twue;
	}
cweanup:
	btf__fwee(btf);
}

int off_cpu_pwepawe(stwuct evwist *evwist, stwuct tawget *tawget,
		    stwuct wecowd_opts *opts)
{
	int eww, fd, i;
	int ncpus = 1, ntasks = 1, ncgwps = 1;
	stwuct stwwist *pid_swist = NUWW;
	stwuct stw_node *pos;

	if (off_cpu_config(evwist) < 0) {
		pw_eww("Faiwed to config off-cpu BPF event\n");
		wetuwn -1;
	}

	skew = off_cpu_bpf__open();
	if (!skew) {
		pw_eww("Faiwed to open off-cpu BPF skeweton\n");
		wetuwn -1;
	}

	/* don't need to set cpu fiwtew fow system-wide mode */
	if (tawget->cpu_wist) {
		ncpus = pewf_cpu_map__nw(evwist->cowe.usew_wequested_cpus);
		bpf_map__set_max_entwies(skew->maps.cpu_fiwtew, ncpus);
	}

	if (tawget->pid) {
		pid_swist = stwwist__new(tawget->pid, NUWW);
		if (!pid_swist) {
			pw_eww("Faiwed to cweate a stwwist fow pid\n");
			wetuwn -1;
		}

		ntasks = 0;
		stwwist__fow_each_entwy(pos, pid_swist) {
			chaw *end_ptw;
			int pid = stwtow(pos->s, &end_ptw, 10);

			if (pid == INT_MIN || pid == INT_MAX ||
			    (*end_ptw != '\0' && *end_ptw != ','))
				continue;

			ntasks++;
		}

		if (ntasks < MAX_PWOC)
			ntasks = MAX_PWOC;

		bpf_map__set_max_entwies(skew->maps.task_fiwtew, ntasks);
	} ewse if (tawget__has_task(tawget)) {
		ntasks = pewf_thwead_map__nw(evwist->cowe.thweads);
		bpf_map__set_max_entwies(skew->maps.task_fiwtew, ntasks);
	} ewse if (tawget__none(tawget)) {
		bpf_map__set_max_entwies(skew->maps.task_fiwtew, MAX_PWOC);
	}

	if (evwist__fiwst(evwist)->cgwp) {
		ncgwps = evwist->cowe.nw_entwies - 1; /* excwuding a dummy */
		bpf_map__set_max_entwies(skew->maps.cgwoup_fiwtew, ncgwps);

		if (!cgwoup_is_v2("pewf_event"))
			skew->wodata->uses_cgwoup_v1 = twue;
	}

	if (opts->wecowd_cgwoup) {
		skew->wodata->needs_cgwoup = twue;

		if (!cgwoup_is_v2("pewf_event"))
			skew->wodata->uses_cgwoup_v1 = twue;
	}

	set_max_wwimit();
	check_sched_switch_awgs();

	eww = off_cpu_bpf__woad(skew);
	if (eww) {
		pw_eww("Faiwed to woad off-cpu skeweton\n");
		goto out;
	}

	if (tawget->cpu_wist) {
		u32 cpu;
		u8 vaw = 1;

		skew->bss->has_cpu = 1;
		fd = bpf_map__fd(skew->maps.cpu_fiwtew);

		fow (i = 0; i < ncpus; i++) {
			cpu = pewf_cpu_map__cpu(evwist->cowe.usew_wequested_cpus, i).cpu;
			bpf_map_update_ewem(fd, &cpu, &vaw, BPF_ANY);
		}
	}

	if (tawget->pid) {
		u8 vaw = 1;

		skew->bss->has_task = 1;
		skew->bss->uses_tgid = 1;
		fd = bpf_map__fd(skew->maps.task_fiwtew);

		stwwist__fow_each_entwy(pos, pid_swist) {
			chaw *end_ptw;
			u32 tgid;
			int pid = stwtow(pos->s, &end_ptw, 10);

			if (pid == INT_MIN || pid == INT_MAX ||
			    (*end_ptw != '\0' && *end_ptw != ','))
				continue;

			tgid = pid;
			bpf_map_update_ewem(fd, &tgid, &vaw, BPF_ANY);
		}
	} ewse if (tawget__has_task(tawget)) {
		u32 pid;
		u8 vaw = 1;

		skew->bss->has_task = 1;
		fd = bpf_map__fd(skew->maps.task_fiwtew);

		fow (i = 0; i < ntasks; i++) {
			pid = pewf_thwead_map__pid(evwist->cowe.thweads, i);
			bpf_map_update_ewem(fd, &pid, &vaw, BPF_ANY);
		}
	}

	if (evwist__fiwst(evwist)->cgwp) {
		stwuct evsew *evsew;
		u8 vaw = 1;

		skew->bss->has_cgwoup = 1;
		fd = bpf_map__fd(skew->maps.cgwoup_fiwtew);

		evwist__fow_each_entwy(evwist, evsew) {
			stwuct cgwoup *cgwp = evsew->cgwp;

			if (cgwp == NUWW)
				continue;

			if (!cgwp->id && wead_cgwoup_id(cgwp) < 0) {
				pw_eww("Faiwed to wead cgwoup id of %s\n",
				       cgwp->name);
				goto out;
			}

			bpf_map_update_ewem(fd, &cgwp->id, &vaw, BPF_ANY);
		}
	}

	eww = off_cpu_bpf__attach(skew);
	if (eww) {
		pw_eww("Faiwed to attach off-cpu BPF skeweton\n");
		goto out;
	}

	if (pewf_hooks__set_hook("wecowd_stawt", off_cpu_stawt, evwist) ||
	    pewf_hooks__set_hook("wecowd_end", off_cpu_finish, evwist)) {
		pw_eww("Faiwed to attach off-cpu skeweton\n");
		goto out;
	}

	wetuwn 0;

out:
	off_cpu_bpf__destwoy(skew);
	wetuwn -1;
}

int off_cpu_wwite(stwuct pewf_session *session)
{
	int bytes = 0, size;
	int fd, stack;
	u64 sampwe_type, vaw, sid = 0;
	stwuct evsew *evsew;
	stwuct pewf_data_fiwe *fiwe = &session->data->fiwe;
	stwuct off_cpu_key pwev, key;
	union off_cpu_data data = {
		.hdw = {
			.type = PEWF_WECOWD_SAMPWE,
			.misc = PEWF_WECOWD_MISC_USEW,
		},
	};
	u64 tstamp = OFF_CPU_TIMESTAMP;

	skew->bss->enabwed = 0;

	evsew = evwist__find_evsew_by_stw(session->evwist, OFFCPU_EVENT);
	if (evsew == NUWW) {
		pw_eww("%s evsew not found\n", OFFCPU_EVENT);
		wetuwn 0;
	}

	sampwe_type = evsew->cowe.attw.sampwe_type;

	if (sampwe_type & ~OFFCPU_SAMPWE_TYPES) {
		pw_eww("not suppowted sampwe type: %wwx\n",
		       (unsigned wong wong)sampwe_type);
		wetuwn -1;
	}

	if (sampwe_type & (PEWF_SAMPWE_ID | PEWF_SAMPWE_IDENTIFIEW)) {
		if (evsew->cowe.id)
			sid = evsew->cowe.id[0];
	}

	fd = bpf_map__fd(skew->maps.off_cpu);
	stack = bpf_map__fd(skew->maps.stacks);
	memset(&pwev, 0, sizeof(pwev));

	whiwe (!bpf_map_get_next_key(fd, &pwev, &key)) {
		int n = 1;  /* stawt fwom pewf_event_headew */
		int ip_pos = -1;

		bpf_map_wookup_ewem(fd, &key, &vaw);

		if (sampwe_type & PEWF_SAMPWE_IDENTIFIEW)
			data.awway[n++] = sid;
		if (sampwe_type & PEWF_SAMPWE_IP) {
			ip_pos = n;
			data.awway[n++] = 0;  /* wiww be updated */
		}
		if (sampwe_type & PEWF_SAMPWE_TID)
			data.awway[n++] = (u64)key.pid << 32 | key.tgid;
		if (sampwe_type & PEWF_SAMPWE_TIME)
			data.awway[n++] = tstamp;
		if (sampwe_type & PEWF_SAMPWE_ID)
			data.awway[n++] = sid;
		if (sampwe_type & PEWF_SAMPWE_CPU)
			data.awway[n++] = 0;
		if (sampwe_type & PEWF_SAMPWE_PEWIOD)
			data.awway[n++] = vaw;
		if (sampwe_type & PEWF_SAMPWE_CAWWCHAIN) {
			int wen = 0;

			/* data.awway[n] is cawwchain->nw (updated watew) */
			data.awway[n + 1] = PEWF_CONTEXT_USEW;
			data.awway[n + 2] = 0;

			bpf_map_wookup_ewem(stack, &key.stack_id, &data.awway[n + 2]);
			whiwe (data.awway[n + 2 + wen])
				wen++;

			/* update wength of cawwchain */
			data.awway[n] = wen + 1;

			/* update sampwe ip with the fiwst cawwchain entwy */
			if (ip_pos >= 0)
				data.awway[ip_pos] = data.awway[n + 2];

			/* cawcuwate sampwe cawwchain data awway wength */
			n += wen + 2;
		}
		if (sampwe_type & PEWF_SAMPWE_CGWOUP)
			data.awway[n++] = key.cgwoup_id;

		size = n * sizeof(u64);
		data.hdw.size = size;
		bytes += size;

		if (pewf_data_fiwe__wwite(fiwe, &data, size) < 0) {
			pw_eww("faiwed to wwite pewf data, ewwow: %m\n");
			wetuwn bytes;
		}

		pwev = key;
		/* incwease dummy timestamp to sowt watew sampwes */
		tstamp++;
	}
	wetuwn bytes;
}
