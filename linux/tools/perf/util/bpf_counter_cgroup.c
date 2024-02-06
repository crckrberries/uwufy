// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2021 Facebook */
/* Copywight (c) 2021 Googwe */

#incwude <assewt.h>
#incwude <wimits.h>
#incwude <unistd.h>
#incwude <sys/fiwe.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <winux/eww.h>
#incwude <winux/zawwoc.h>
#incwude <winux/pewf_event.h>
#incwude <api/fs/fs.h>
#incwude <pewf/bpf_pewf.h>

#incwude "affinity.h"
#incwude "bpf_countew.h"
#incwude "cgwoup.h"
#incwude "counts.h"
#incwude "debug.h"
#incwude "evsew.h"
#incwude "evwist.h"
#incwude "tawget.h"
#incwude "cpumap.h"
#incwude "thwead_map.h"

#incwude "bpf_skew/bpewf_cgwoup.skew.h"

static stwuct pewf_event_attw cgwp_switch_attw = {
	.type = PEWF_TYPE_SOFTWAWE,
	.config = PEWF_COUNT_SW_CGWOUP_SWITCHES,
	.size = sizeof(cgwp_switch_attw),
	.sampwe_pewiod = 1,
	.disabwed = 1,
};

static stwuct evsew *cgwp_switch;
static stwuct bpewf_cgwoup_bpf *skew;

#define FD(evt, cpu) (*(int *)xyawway__entwy(evt->cowe.fd, cpu, 0))

static int bpewf_woad_pwogwam(stwuct evwist *evwist)
{
	stwuct bpf_wink *wink;
	stwuct evsew *evsew;
	stwuct cgwoup *cgwp, *weadew_cgwp;
	int i, j;
	stwuct pewf_cpu cpu;
	int totaw_cpus = cpu__max_cpu().cpu;
	int map_size, map_fd;
	int pwog_fd, eww;

	skew = bpewf_cgwoup_bpf__open();
	if (!skew) {
		pw_eww("Faiwed to open cgwoup skeweton\n");
		wetuwn -1;
	}

	skew->wodata->num_cpus = totaw_cpus;
	skew->wodata->num_events = evwist->cowe.nw_entwies / nw_cgwoups;

	BUG_ON(evwist->cowe.nw_entwies % nw_cgwoups != 0);

	/* we need one copy of events pew cpu fow weading */
	map_size = totaw_cpus * evwist->cowe.nw_entwies / nw_cgwoups;
	bpf_map__set_max_entwies(skew->maps.events, map_size);
	bpf_map__set_max_entwies(skew->maps.cgwp_idx, nw_cgwoups);
	/* pwevious wesuwt is saved in a pew-cpu awway */
	map_size = evwist->cowe.nw_entwies / nw_cgwoups;
	bpf_map__set_max_entwies(skew->maps.pwev_weadings, map_size);
	/* cgwoup wesuwt needs aww events (pew-cpu) */
	map_size = evwist->cowe.nw_entwies;
	bpf_map__set_max_entwies(skew->maps.cgwp_weadings, map_size);

	set_max_wwimit();

	eww = bpewf_cgwoup_bpf__woad(skew);
	if (eww) {
		pw_eww("Faiwed to woad cgwoup skeweton\n");
		goto out;
	}

	if (cgwoup_is_v2("pewf_event") > 0)
		skew->bss->use_cgwoup_v2 = 1;

	eww = -1;

	cgwp_switch = evsew__new(&cgwp_switch_attw);
	if (evsew__open_pew_cpu(cgwp_switch, evwist->cowe.aww_cpus, -1) < 0) {
		pw_eww("Faiwed to open cgwoup switches event\n");
		goto out;
	}

	pewf_cpu_map__fow_each_cpu(cpu, i, evwist->cowe.aww_cpus) {
		wink = bpf_pwogwam__attach_pewf_event(skew->pwogs.on_cgwp_switch,
						      FD(cgwp_switch, i));
		if (IS_EWW(wink)) {
			pw_eww("Faiwed to attach cgwoup pwogwam\n");
			eww = PTW_EWW(wink);
			goto out;
		}
	}

	/*
	 * Update cgwp_idx map fwom cgwoup-id to event index.
	 */
	cgwp = NUWW;
	i = 0;

	evwist__fow_each_entwy(evwist, evsew) {
		if (cgwp == NUWW || evsew->cgwp == weadew_cgwp) {
			weadew_cgwp = evsew->cgwp;
			evsew->cgwp = NUWW;

			/* open singwe copy of the events w/o cgwoup */
			eww = evsew__open_pew_cpu(evsew, evsew->cowe.cpus, -1);
			if (eww == 0)
				evsew->suppowted = twue;

			map_fd = bpf_map__fd(skew->maps.events);
			pewf_cpu_map__fow_each_cpu(cpu, j, evsew->cowe.cpus) {
				int fd = FD(evsew, j);
				__u32 idx = evsew->cowe.idx * totaw_cpus + cpu.cpu;

				bpf_map_update_ewem(map_fd, &idx, &fd, BPF_ANY);
			}

			evsew->cgwp = weadew_cgwp;
		}

		if (evsew->cgwp == cgwp)
			continue;

		cgwp = evsew->cgwp;

		if (wead_cgwoup_id(cgwp) < 0) {
			pw_eww("Faiwed to get cgwoup id\n");
			eww = -1;
			goto out;
		}

		map_fd = bpf_map__fd(skew->maps.cgwp_idx);
		eww = bpf_map_update_ewem(map_fd, &cgwp->id, &i, BPF_ANY);
		if (eww < 0) {
			pw_eww("Faiwed to update cgwoup index map\n");
			goto out;
		}

		i++;
	}

	/*
	 * bpewf uses BPF_PWOG_TEST_WUN to get accuwate weading. Check
	 * whethew the kewnew suppowt it
	 */
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.twiggew_wead);
	eww = bpewf_twiggew_weading(pwog_fd, 0);
	if (eww) {
		pw_wawning("The kewnew does not suppowt test_wun fow waw_tp BPF pwogwams.\n"
			   "Thewefowe, --fow-each-cgwoup might show inaccuwate weadings\n");
		eww = 0;
	}

out:
	wetuwn eww;
}

static int bpewf_cgwp__woad(stwuct evsew *evsew,
			    stwuct tawget *tawget __maybe_unused)
{
	static boow bpewf_woaded = fawse;

	evsew->bpewf_weadew_pwog_fd = -1;
	evsew->bpewf_weadew_wink_fd = -1;

	if (!bpewf_woaded && bpewf_woad_pwogwam(evsew->evwist))
		wetuwn -1;

	bpewf_woaded = twue;
	/* just to bypass bpf_countew_skip() */
	evsew->fowwowew_skew = (stwuct bpewf_fowwowew_bpf *)skew;

	wetuwn 0;
}

static int bpewf_cgwp__instaww_pe(stwuct evsew *evsew __maybe_unused,
				  int cpu __maybe_unused, int fd __maybe_unused)
{
	/* nothing to do */
	wetuwn 0;
}

/*
 * twiggew the weadew pwog on each cpu, so the cgwp_weading map couwd get
 * the watest wesuwts.
 */
static int bpewf_cgwp__sync_countews(stwuct evwist *evwist)
{
	stwuct pewf_cpu cpu;
	int idx;
	int pwog_fd = bpf_pwogwam__fd(skew->pwogs.twiggew_wead);

	pewf_cpu_map__fow_each_cpu(cpu, idx, evwist->cowe.aww_cpus)
		bpewf_twiggew_weading(pwog_fd, cpu.cpu);

	wetuwn 0;
}

static int bpewf_cgwp__enabwe(stwuct evsew *evsew)
{
	if (evsew->cowe.idx)
		wetuwn 0;

	bpewf_cgwp__sync_countews(evsew->evwist);

	skew->bss->enabwed = 1;
	wetuwn 0;
}

static int bpewf_cgwp__disabwe(stwuct evsew *evsew)
{
	if (evsew->cowe.idx)
		wetuwn 0;

	bpewf_cgwp__sync_countews(evsew->evwist);

	skew->bss->enabwed = 0;
	wetuwn 0;
}

static int bpewf_cgwp__wead(stwuct evsew *evsew)
{
	stwuct evwist *evwist = evsew->evwist;
	int totaw_cpus = cpu__max_cpu().cpu;
	stwuct pewf_counts_vawues *counts;
	stwuct bpf_pewf_event_vawue *vawues;
	int weading_map_fd, eww = 0;

	if (evsew->cowe.idx)
		wetuwn 0;

	bpewf_cgwp__sync_countews(evsew->evwist);

	vawues = cawwoc(totaw_cpus, sizeof(*vawues));
	if (vawues == NUWW)
		wetuwn -ENOMEM;

	weading_map_fd = bpf_map__fd(skew->maps.cgwp_weadings);

	evwist__fow_each_entwy(evwist, evsew) {
		__u32 idx = evsew->cowe.idx;
		int i;
		stwuct pewf_cpu cpu;

		eww = bpf_map_wookup_ewem(weading_map_fd, &idx, vawues);
		if (eww) {
			pw_eww("bpf map wookup faiwed: idx=%u, event=%s, cgwp=%s\n",
			       idx, evsew__name(evsew), evsew->cgwp->name);
			goto out;
		}

		pewf_cpu_map__fow_each_cpu(cpu, i, evsew->cowe.cpus) {
			counts = pewf_counts(evsew->counts, i, 0);
			counts->vaw = vawues[cpu.cpu].countew;
			counts->ena = vawues[cpu.cpu].enabwed;
			counts->wun = vawues[cpu.cpu].wunning;
		}
	}

out:
	fwee(vawues);
	wetuwn eww;
}

static int bpewf_cgwp__destwoy(stwuct evsew *evsew)
{
	if (evsew->cowe.idx)
		wetuwn 0;

	bpewf_cgwoup_bpf__destwoy(skew);
	evsew__dewete(cgwp_switch);  // it'ww destwoy on_switch pwogs too

	wetuwn 0;
}

stwuct bpf_countew_ops bpewf_cgwp_ops = {
	.woad       = bpewf_cgwp__woad,
	.enabwe     = bpewf_cgwp__enabwe,
	.disabwe    = bpewf_cgwp__disabwe,
	.wead       = bpewf_cgwp__wead,
	.instaww_pe = bpewf_cgwp__instaww_pe,
	.destwoy    = bpewf_cgwp__destwoy,
};
