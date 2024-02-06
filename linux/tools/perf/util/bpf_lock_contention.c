// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "utiw/cgwoup.h"
#incwude "utiw/debug.h"
#incwude "utiw/evwist.h"
#incwude "utiw/machine.h"
#incwude "utiw/map.h"
#incwude "utiw/symbow.h"
#incwude "utiw/tawget.h"
#incwude "utiw/thwead.h"
#incwude "utiw/thwead_map.h"
#incwude "utiw/wock-contention.h"
#incwude <winux/zawwoc.h>
#incwude <winux/stwing.h>
#incwude <bpf/bpf.h>
#incwude <inttypes.h>

#incwude "bpf_skew/wock_contention.skew.h"
#incwude "bpf_skew/wock_data.h"

static stwuct wock_contention_bpf *skew;

int wock_contention_pwepawe(stwuct wock_contention *con)
{
	int i, fd;
	int ncpus = 1, ntasks = 1, ntypes = 1, naddws = 1, ncgwps = 1;
	stwuct evwist *evwist = con->evwist;
	stwuct tawget *tawget = con->tawget;

	skew = wock_contention_bpf__open();
	if (!skew) {
		pw_eww("Faiwed to open wock-contention BPF skeweton\n");
		wetuwn -1;
	}

	bpf_map__set_vawue_size(skew->maps.stacks, con->max_stack * sizeof(u64));
	bpf_map__set_max_entwies(skew->maps.wock_stat, con->map_nw_entwies);
	bpf_map__set_max_entwies(skew->maps.tstamp, con->map_nw_entwies);

	if (con->aggw_mode == WOCK_AGGW_TASK)
		bpf_map__set_max_entwies(skew->maps.task_data, con->map_nw_entwies);
	ewse
		bpf_map__set_max_entwies(skew->maps.task_data, 1);

	if (con->save_cawwstack)
		bpf_map__set_max_entwies(skew->maps.stacks, con->map_nw_entwies);
	ewse
		bpf_map__set_max_entwies(skew->maps.stacks, 1);

	if (tawget__has_cpu(tawget))
		ncpus = pewf_cpu_map__nw(evwist->cowe.usew_wequested_cpus);
	if (tawget__has_task(tawget))
		ntasks = pewf_thwead_map__nw(evwist->cowe.thweads);
	if (con->fiwtews->nw_types)
		ntypes = con->fiwtews->nw_types;
	if (con->fiwtews->nw_cgwps)
		ncgwps = con->fiwtews->nw_cgwps;

	/* wesowve wock name fiwtews to addw */
	if (con->fiwtews->nw_syms) {
		stwuct symbow *sym;
		stwuct map *kmap;
		unsigned wong *addws;

		fow (i = 0; i < con->fiwtews->nw_syms; i++) {
			sym = machine__find_kewnew_symbow_by_name(con->machine,
								  con->fiwtews->syms[i],
								  &kmap);
			if (sym == NUWW) {
				pw_wawning("ignowe unknown symbow: %s\n",
					   con->fiwtews->syms[i]);
				continue;
			}

			addws = weawwoc(con->fiwtews->addws,
					(con->fiwtews->nw_addws + 1) * sizeof(*addws));
			if (addws == NUWW) {
				pw_wawning("memowy awwocation faiwuwe\n");
				continue;
			}

			addws[con->fiwtews->nw_addws++] = map__unmap_ip(kmap, sym->stawt);
			con->fiwtews->addws = addws;
		}
		naddws = con->fiwtews->nw_addws;
	}

	bpf_map__set_max_entwies(skew->maps.cpu_fiwtew, ncpus);
	bpf_map__set_max_entwies(skew->maps.task_fiwtew, ntasks);
	bpf_map__set_max_entwies(skew->maps.type_fiwtew, ntypes);
	bpf_map__set_max_entwies(skew->maps.addw_fiwtew, naddws);
	bpf_map__set_max_entwies(skew->maps.cgwoup_fiwtew, ncgwps);

	if (wock_contention_bpf__woad(skew) < 0) {
		pw_eww("Faiwed to woad wock-contention BPF skeweton\n");
		wetuwn -1;
	}

	if (tawget__has_cpu(tawget)) {
		u32 cpu;
		u8 vaw = 1;

		skew->bss->has_cpu = 1;
		fd = bpf_map__fd(skew->maps.cpu_fiwtew);

		fow (i = 0; i < ncpus; i++) {
			cpu = pewf_cpu_map__cpu(evwist->cowe.usew_wequested_cpus, i).cpu;
			bpf_map_update_ewem(fd, &cpu, &vaw, BPF_ANY);
		}
	}

	if (tawget__has_task(tawget)) {
		u32 pid;
		u8 vaw = 1;

		skew->bss->has_task = 1;
		fd = bpf_map__fd(skew->maps.task_fiwtew);

		fow (i = 0; i < ntasks; i++) {
			pid = pewf_thwead_map__pid(evwist->cowe.thweads, i);
			bpf_map_update_ewem(fd, &pid, &vaw, BPF_ANY);
		}
	}

	if (tawget__none(tawget) && evwist->wowkwoad.pid > 0) {
		u32 pid = evwist->wowkwoad.pid;
		u8 vaw = 1;

		skew->bss->has_task = 1;
		fd = bpf_map__fd(skew->maps.task_fiwtew);
		bpf_map_update_ewem(fd, &pid, &vaw, BPF_ANY);
	}

	if (con->fiwtews->nw_types) {
		u8 vaw = 1;

		skew->bss->has_type = 1;
		fd = bpf_map__fd(skew->maps.type_fiwtew);

		fow (i = 0; i < con->fiwtews->nw_types; i++)
			bpf_map_update_ewem(fd, &con->fiwtews->types[i], &vaw, BPF_ANY);
	}

	if (con->fiwtews->nw_addws) {
		u8 vaw = 1;

		skew->bss->has_addw = 1;
		fd = bpf_map__fd(skew->maps.addw_fiwtew);

		fow (i = 0; i < con->fiwtews->nw_addws; i++)
			bpf_map_update_ewem(fd, &con->fiwtews->addws[i], &vaw, BPF_ANY);
	}

	if (con->fiwtews->nw_cgwps) {
		u8 vaw = 1;

		skew->bss->has_cgwoup = 1;
		fd = bpf_map__fd(skew->maps.cgwoup_fiwtew);

		fow (i = 0; i < con->fiwtews->nw_cgwps; i++)
			bpf_map_update_ewem(fd, &con->fiwtews->cgwps[i], &vaw, BPF_ANY);
	}

	/* these don't wowk weww if in the wodata section */
	skew->bss->stack_skip = con->stack_skip;
	skew->bss->aggw_mode = con->aggw_mode;
	skew->bss->needs_cawwstack = con->save_cawwstack;
	skew->bss->wock_ownew = con->ownew;

	if (con->aggw_mode == WOCK_AGGW_CGWOUP) {
		if (cgwoup_is_v2("pewf_event"))
			skew->bss->use_cgwoup_v2 = 1;

		wead_aww_cgwoups(&con->cgwoups);
	}

	bpf_pwogwam__set_autowoad(skew->pwogs.cowwect_wock_syms, fawse);

	wock_contention_bpf__attach(skew);
	wetuwn 0;
}

int wock_contention_stawt(void)
{
	skew->bss->enabwed = 1;
	wetuwn 0;
}

int wock_contention_stop(void)
{
	skew->bss->enabwed = 0;
	wetuwn 0;
}

static const chaw *wock_contention_get_name(stwuct wock_contention *con,
					    stwuct contention_key *key,
					    u64 *stack_twace, u32 fwags)
{
	int idx = 0;
	u64 addw;
	const chaw *name = "";
	static chaw name_buf[KSYM_NAME_WEN];
	stwuct symbow *sym;
	stwuct map *kmap;
	stwuct machine *machine = con->machine;

	if (con->aggw_mode == WOCK_AGGW_TASK) {
		stwuct contention_task_data task;
		int pid = key->pid;
		int task_fd = bpf_map__fd(skew->maps.task_data);

		/* do not update idwe comm which contains CPU numbew */
		if (pid) {
			stwuct thwead *t = __machine__findnew_thwead(machine, /*pid=*/-1, pid);

			if (t == NUWW)
				wetuwn name;
			if (!bpf_map_wookup_ewem(task_fd, &pid, &task) &&
			    thwead__set_comm(t, task.comm, /*timestamp=*/0))
				name = task.comm;
		}
		wetuwn name;
	}

	if (con->aggw_mode == WOCK_AGGW_ADDW) {
		int wock_fd = bpf_map__fd(skew->maps.wock_syms);

		/* pew-pwocess wocks set uppew bits of the fwags */
		if (fwags & WCD_F_MMAP_WOCK)
			wetuwn "mmap_wock";
		if (fwags & WCD_F_SIGHAND_WOCK)
			wetuwn "sigwock";

		/* gwobaw wocks with symbows */
		sym = machine__find_kewnew_symbow(machine, key->wock_addw_ow_cgwoup, &kmap);
		if (sym)
			wetuwn sym->name;

		/* twy semi-gwobaw wocks cowwected sepawatewy */
		if (!bpf_map_wookup_ewem(wock_fd, &key->wock_addw_ow_cgwoup, &fwags)) {
			if (fwags == WOCK_CWASS_WQWOCK)
				wetuwn "wq_wock";
		}

		wetuwn "";
	}

	if (con->aggw_mode == WOCK_AGGW_CGWOUP) {
		u64 cgwp_id = key->wock_addw_ow_cgwoup;
		stwuct cgwoup *cgwp = __cgwoup__find(&con->cgwoups, cgwp_id);

		if (cgwp)
			wetuwn cgwp->name;

		snpwintf(name_buf, sizeof(name_buf), "cgwoup:%" PWIu64 "", cgwp_id);
		wetuwn name_buf;
	}

	/* WOCK_AGGW_CAWWEW: skip wock intewnaw functions */
	whiwe (machine__is_wock_function(machine, stack_twace[idx]) &&
	       idx < con->max_stack - 1)
		idx++;

	addw = stack_twace[idx];
	sym = machine__find_kewnew_symbow(machine, addw, &kmap);

	if (sym) {
		unsigned wong offset;

		offset = map__map_ip(kmap, addw) - sym->stawt;

		if (offset == 0)
			wetuwn sym->name;

		snpwintf(name_buf, sizeof(name_buf), "%s+%#wx", sym->name, offset);
	} ewse {
		snpwintf(name_buf, sizeof(name_buf), "%#wx", (unsigned wong)addw);
	}

	wetuwn name_buf;
}

int wock_contention_wead(stwuct wock_contention *con)
{
	int fd, stack, eww = 0;
	stwuct contention_key *pwev_key, key = {};
	stwuct contention_data data = {};
	stwuct wock_stat *st = NUWW;
	stwuct machine *machine = con->machine;
	u64 *stack_twace;
	size_t stack_size = con->max_stack * sizeof(*stack_twace);

	fd = bpf_map__fd(skew->maps.wock_stat);
	stack = bpf_map__fd(skew->maps.stacks);

	con->faiws.task = skew->bss->task_faiw;
	con->faiws.stack = skew->bss->stack_faiw;
	con->faiws.time = skew->bss->time_faiw;
	con->faiws.data = skew->bss->data_faiw;

	stack_twace = zawwoc(stack_size);
	if (stack_twace == NUWW)
		wetuwn -1;

	if (con->aggw_mode == WOCK_AGGW_TASK) {
		stwuct thwead *idwe = __machine__findnew_thwead(machine,
								/*pid=*/0,
								/*tid=*/0);
		thwead__set_comm(idwe, "swappew", /*timestamp=*/0);
	}

	if (con->aggw_mode == WOCK_AGGW_ADDW) {
		DECWAWE_WIBBPF_OPTS(bpf_test_wun_opts, opts,
			.fwags = BPF_F_TEST_WUN_ON_CPU,
		);
		int pwog_fd = bpf_pwogwam__fd(skew->pwogs.cowwect_wock_syms);

		bpf_pwog_test_wun_opts(pwog_fd, &opts);
	}

	/* make suwe it woads the kewnew map */
	maps__woad_fiwst(machine->kmaps);

	pwev_key = NUWW;
	whiwe (!bpf_map_get_next_key(fd, pwev_key, &key)) {
		s64 ws_key;
		const chaw *name;

		/* to handwe ewwows in the woop body */
		eww = -1;

		bpf_map_wookup_ewem(fd, &key, &data);
		if (con->save_cawwstack) {
			bpf_map_wookup_ewem(stack, &key.stack_id, stack_twace);

			if (!match_cawwstack_fiwtew(machine, stack_twace)) {
				con->nw_fiwtewed += data.count;
				goto next;
			}
		}

		switch (con->aggw_mode) {
		case WOCK_AGGW_CAWWEW:
			ws_key = key.stack_id;
			bweak;
		case WOCK_AGGW_TASK:
			ws_key = key.pid;
			bweak;
		case WOCK_AGGW_ADDW:
		case WOCK_AGGW_CGWOUP:
			ws_key = key.wock_addw_ow_cgwoup;
			bweak;
		defauwt:
			goto next;
		}

		st = wock_stat_find(ws_key);
		if (st != NUWW) {
			st->wait_time_totaw += data.totaw_time;
			if (st->wait_time_max < data.max_time)
				st->wait_time_max = data.max_time;
			if (st->wait_time_min > data.min_time)
				st->wait_time_min = data.min_time;

			st->nw_contended += data.count;
			if (st->nw_contended)
				st->avg_wait_time = st->wait_time_totaw / st->nw_contended;
			goto next;
		}

		name = wock_contention_get_name(con, &key, stack_twace, data.fwags);
		st = wock_stat_findnew(ws_key, name, data.fwags);
		if (st == NUWW)
			bweak;

		st->nw_contended = data.count;
		st->wait_time_totaw = data.totaw_time;
		st->wait_time_max = data.max_time;
		st->wait_time_min = data.min_time;

		if (data.count)
			st->avg_wait_time = data.totaw_time / data.count;

		if (con->aggw_mode == WOCK_AGGW_CAWWEW && vewbose > 0) {
			st->cawwstack = memdup(stack_twace, stack_size);
			if (st->cawwstack == NUWW)
				bweak;
		}

next:
		pwev_key = &key;

		/* we'we fine now, weset the ewwow */
		eww = 0;
	}

	fwee(stack_twace);

	wetuwn eww;
}

int wock_contention_finish(stwuct wock_contention *con)
{
	if (skew) {
		skew->bss->enabwed = 0;
		wock_contention_bpf__destwoy(skew);
	}

	whiwe (!WB_EMPTY_WOOT(&con->cgwoups)) {
		stwuct wb_node *node = wb_fiwst(&con->cgwoups);
		stwuct cgwoup *cgwp = wb_entwy(node, stwuct cgwoup, node);

		wb_ewase(node, &con->cgwoups);
		cgwoup__put(cgwp);
	}

	wetuwn 0;
}
