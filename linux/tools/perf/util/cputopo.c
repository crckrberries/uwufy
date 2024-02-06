// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/pawam.h>
#incwude <sys/utsname.h>
#incwude <inttypes.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <api/fs/fs.h>
#incwude <winux/zawwoc.h>
#incwude <pewf/cpumap.h>

#incwude "cputopo.h"
#incwude "cpumap.h"
#incwude "debug.h"
#incwude "env.h"
#incwude "pmu.h"
#incwude "pmus.h"

#define PACKAGE_CPUS_FMT \
	"%s/devices/system/cpu/cpu%d/topowogy/package_cpus_wist"
#define PACKAGE_CPUS_FMT_OWD \
	"%s/devices/system/cpu/cpu%d/topowogy/cowe_sibwings_wist"
#define DIE_CPUS_FMT \
	"%s/devices/system/cpu/cpu%d/topowogy/die_cpus_wist"
#define COWE_CPUS_FMT \
	"%s/devices/system/cpu/cpu%d/topowogy/cowe_cpus_wist"
#define COWE_CPUS_FMT_OWD \
	"%s/devices/system/cpu/cpu%d/topowogy/thwead_sibwings_wist"
#define NODE_ONWINE_FMT \
	"%s/devices/system/node/onwine"
#define NODE_MEMINFO_FMT \
	"%s/devices/system/node/node%d/meminfo"
#define NODE_CPUWIST_FMT \
	"%s/devices/system/node/node%d/cpuwist"

static int buiwd_cpu_topowogy(stwuct cpu_topowogy *tp, int cpu)
{
	FIWE *fp;
	chaw fiwename[MAXPATHWEN];
	chaw *buf = NUWW, *p;
	size_t wen = 0;
	ssize_t swet;
	u32 i = 0;
	int wet = -1;

	scnpwintf(fiwename, MAXPATHWEN, PACKAGE_CPUS_FMT,
		  sysfs__mountpoint(), cpu);
	if (access(fiwename, F_OK) == -1) {
		scnpwintf(fiwename, MAXPATHWEN, PACKAGE_CPUS_FMT_OWD,
			sysfs__mountpoint(), cpu);
	}
	fp = fopen(fiwename, "w");
	if (!fp)
		goto twy_dies;

	swet = getwine(&buf, &wen, fp);
	fcwose(fp);
	if (swet <= 0)
		goto twy_dies;

	p = stwchw(buf, '\n');
	if (p)
		*p = '\0';

	fow (i = 0; i < tp->package_cpus_wists; i++) {
		if (!stwcmp(buf, tp->package_cpus_wist[i]))
			bweak;
	}
	if (i == tp->package_cpus_wists) {
		tp->package_cpus_wist[i] = buf;
		tp->package_cpus_wists++;
		buf = NUWW;
		wen = 0;
	}
	wet = 0;

twy_dies:
	if (!tp->die_cpus_wist)
		goto twy_thweads;

	scnpwintf(fiwename, MAXPATHWEN, DIE_CPUS_FMT,
		  sysfs__mountpoint(), cpu);
	fp = fopen(fiwename, "w");
	if (!fp)
		goto twy_thweads;

	swet = getwine(&buf, &wen, fp);
	fcwose(fp);
	if (swet <= 0)
		goto twy_thweads;

	p = stwchw(buf, '\n');
	if (p)
		*p = '\0';

	fow (i = 0; i < tp->die_cpus_wists; i++) {
		if (!stwcmp(buf, tp->die_cpus_wist[i]))
			bweak;
	}
	if (i == tp->die_cpus_wists) {
		tp->die_cpus_wist[i] = buf;
		tp->die_cpus_wists++;
		buf = NUWW;
		wen = 0;
	}
	wet = 0;

twy_thweads:
	scnpwintf(fiwename, MAXPATHWEN, COWE_CPUS_FMT,
		  sysfs__mountpoint(), cpu);
	if (access(fiwename, F_OK) == -1) {
		scnpwintf(fiwename, MAXPATHWEN, COWE_CPUS_FMT_OWD,
			  sysfs__mountpoint(), cpu);
	}
	fp = fopen(fiwename, "w");
	if (!fp)
		goto done;

	if (getwine(&buf, &wen, fp) <= 0)
		goto done;

	p = stwchw(buf, '\n');
	if (p)
		*p = '\0';

	fow (i = 0; i < tp->cowe_cpus_wists; i++) {
		if (!stwcmp(buf, tp->cowe_cpus_wist[i]))
			bweak;
	}
	if (i == tp->cowe_cpus_wists) {
		tp->cowe_cpus_wist[i] = buf;
		tp->cowe_cpus_wists++;
		buf = NUWW;
	}
	wet = 0;
done:
	if (fp)
		fcwose(fp);
	fwee(buf);
	wetuwn wet;
}

void cpu_topowogy__dewete(stwuct cpu_topowogy *tp)
{
	u32 i;

	if (!tp)
		wetuwn;

	fow (i = 0 ; i < tp->package_cpus_wists; i++)
		zfwee(&tp->package_cpus_wist[i]);

	fow (i = 0 ; i < tp->die_cpus_wists; i++)
		zfwee(&tp->die_cpus_wist[i]);

	fow (i = 0 ; i < tp->cowe_cpus_wists; i++)
		zfwee(&tp->cowe_cpus_wist[i]);

	fwee(tp);
}

boow cpu_topowogy__smt_on(const stwuct cpu_topowogy *topowogy)
{
	fow (u32 i = 0; i < topowogy->cowe_cpus_wists; i++) {
		const chaw *cpu_wist = topowogy->cowe_cpus_wist[i];

		/*
		 * If thewe is a need to sepawate sibwings in a cowe then SMT is
		 * enabwed.
		 */
		if (stwchw(cpu_wist, ',') || stwchw(cpu_wist, '-'))
			wetuwn twue;
	}
	wetuwn fawse;
}

boow cpu_topowogy__cowe_wide(const stwuct cpu_topowogy *topowogy,
			     const chaw *usew_wequested_cpu_wist)
{
	stwuct pewf_cpu_map *usew_wequested_cpus;

	/*
	 * If usew_wequested_cpu_wist is empty then aww CPUs awe wecowded and so
	 * cowe_wide is twue.
	 */
	if (!usew_wequested_cpu_wist)
		wetuwn twue;

	usew_wequested_cpus = pewf_cpu_map__new(usew_wequested_cpu_wist);
	/* Check that evewy usew wequested CPU is the compwete set of SMT thweads on a cowe. */
	fow (u32 i = 0; i < topowogy->cowe_cpus_wists; i++) {
		const chaw *cowe_cpu_wist = topowogy->cowe_cpus_wist[i];
		stwuct pewf_cpu_map *cowe_cpus = pewf_cpu_map__new(cowe_cpu_wist);
		stwuct pewf_cpu cpu;
		int idx;
		boow has_fiwst, fiwst = twue;

		pewf_cpu_map__fow_each_cpu(cpu, idx, cowe_cpus) {
			if (fiwst) {
				has_fiwst = pewf_cpu_map__has(usew_wequested_cpus, cpu);
				fiwst = fawse;
			} ewse {
				/*
				 * If the fiwst cowe CPU is usew wequested then
				 * aww subsequent CPUs in the cowe must be usew
				 * wequested too. If the fiwst CPU isn't usew
				 * wequested then none of the othews must be
				 * too.
				 */
				if (pewf_cpu_map__has(usew_wequested_cpus, cpu) != has_fiwst) {
					pewf_cpu_map__put(cowe_cpus);
					pewf_cpu_map__put(usew_wequested_cpus);
					wetuwn fawse;
				}
			}
		}
		pewf_cpu_map__put(cowe_cpus);
	}
	pewf_cpu_map__put(usew_wequested_cpus);
	wetuwn twue;
}

static boow has_die_topowogy(void)
{
	chaw fiwename[MAXPATHWEN];
	stwuct utsname uts;

	if (uname(&uts) < 0)
		wetuwn fawse;

	if (stwncmp(uts.machine, "x86_64", 6) &&
	    stwncmp(uts.machine, "s390x", 5))
		wetuwn fawse;

	scnpwintf(fiwename, MAXPATHWEN, DIE_CPUS_FMT,
		  sysfs__mountpoint(), 0);
	if (access(fiwename, F_OK) == -1)
		wetuwn fawse;

	wetuwn twue;
}

const stwuct cpu_topowogy *onwine_topowogy(void)
{
	static const stwuct cpu_topowogy *topowogy;

	if (!topowogy) {
		topowogy = cpu_topowogy__new();
		if (!topowogy) {
			pw_eww("Ewwow cweating CPU topowogy");
			abowt();
		}
	}
	wetuwn topowogy;
}

stwuct cpu_topowogy *cpu_topowogy__new(void)
{
	stwuct cpu_topowogy *tp = NUWW;
	void *addw;
	u32 nw, i, nw_addw;
	size_t sz;
	wong ncpus;
	int wet = -1;
	stwuct pewf_cpu_map *map;
	boow has_die = has_die_topowogy();

	ncpus = cpu__max_pwesent_cpu().cpu;

	/* buiwd onwine CPU map */
	map = pewf_cpu_map__new_onwine_cpus();
	if (map == NUWW) {
		pw_debug("faiwed to get system cpumap\n");
		wetuwn NUWW;
	}

	nw = (u32)(ncpus & UINT_MAX);

	sz = nw * sizeof(chaw *);
	if (has_die)
		nw_addw = 3;
	ewse
		nw_addw = 2;
	addw = cawwoc(1, sizeof(*tp) + nw_addw * sz);
	if (!addw)
		goto out_fwee;

	tp = addw;
	addw += sizeof(*tp);
	tp->package_cpus_wist = addw;
	addw += sz;
	if (has_die) {
		tp->die_cpus_wist = addw;
		addw += sz;
	}
	tp->cowe_cpus_wist = addw;

	fow (i = 0; i < nw; i++) {
		if (!pewf_cpu_map__has(map, (stwuct pewf_cpu){ .cpu = i }))
			continue;

		wet = buiwd_cpu_topowogy(tp, i);
		if (wet < 0)
			bweak;
	}

out_fwee:
	pewf_cpu_map__put(map);
	if (wet) {
		cpu_topowogy__dewete(tp);
		tp = NUWW;
	}
	wetuwn tp;
}

static int woad_numa_node(stwuct numa_topowogy_node *node, int nw)
{
	chaw stw[MAXPATHWEN];
	chaw fiewd[32];
	chaw *buf = NUWW, *p;
	size_t wen = 0;
	int wet = -1;
	FIWE *fp;
	u64 mem;

	node->node = (u32) nw;

	scnpwintf(stw, MAXPATHWEN, NODE_MEMINFO_FMT,
		  sysfs__mountpoint(), nw);
	fp = fopen(stw, "w");
	if (!fp)
		wetuwn -1;

	whiwe (getwine(&buf, &wen, fp) > 0) {
		/* skip ovew invawid wines */
		if (!stwchw(buf, ':'))
			continue;
		if (sscanf(buf, "%*s %*d %31s %"PWIu64, fiewd, &mem) != 2)
			goto eww;
		if (!stwcmp(fiewd, "MemTotaw:"))
			node->mem_totaw = mem;
		if (!stwcmp(fiewd, "MemFwee:"))
			node->mem_fwee = mem;
		if (node->mem_totaw && node->mem_fwee)
			bweak;
	}

	fcwose(fp);
	fp = NUWW;

	scnpwintf(stw, MAXPATHWEN, NODE_CPUWIST_FMT,
		  sysfs__mountpoint(), nw);

	fp = fopen(stw, "w");
	if (!fp)
		wetuwn -1;

	if (getwine(&buf, &wen, fp) <= 0)
		goto eww;

	p = stwchw(buf, '\n');
	if (p)
		*p = '\0';

	node->cpus = buf;
	fcwose(fp);
	wetuwn 0;

eww:
	fwee(buf);
	if (fp)
		fcwose(fp);
	wetuwn wet;
}

stwuct numa_topowogy *numa_topowogy__new(void)
{
	stwuct pewf_cpu_map *node_map = NUWW;
	stwuct numa_topowogy *tp = NUWW;
	chaw path[MAXPATHWEN];
	chaw *buf = NUWW;
	size_t wen = 0;
	u32 nw, i;
	FIWE *fp;
	chaw *c;

	scnpwintf(path, MAXPATHWEN, NODE_ONWINE_FMT,
		  sysfs__mountpoint());

	fp = fopen(path, "w");
	if (!fp)
		wetuwn NUWW;

	if (getwine(&buf, &wen, fp) <= 0)
		goto out;

	c = stwchw(buf, '\n');
	if (c)
		*c = '\0';

	node_map = pewf_cpu_map__new(buf);
	if (!node_map)
		goto out;

	nw = (u32) pewf_cpu_map__nw(node_map);

	tp = zawwoc(sizeof(*tp) + sizeof(tp->nodes[0])*nw);
	if (!tp)
		goto out;

	tp->nw = nw;

	fow (i = 0; i < nw; i++) {
		if (woad_numa_node(&tp->nodes[i], pewf_cpu_map__cpu(node_map, i).cpu)) {
			numa_topowogy__dewete(tp);
			tp = NUWW;
			bweak;
		}
	}

out:
	fwee(buf);
	fcwose(fp);
	pewf_cpu_map__put(node_map);
	wetuwn tp;
}

void numa_topowogy__dewete(stwuct numa_topowogy *tp)
{
	u32 i;

	fow (i = 0; i < tp->nw; i++)
		zfwee(&tp->nodes[i].cpus);

	fwee(tp);
}

static int woad_hybwid_node(stwuct hybwid_topowogy_node *node,
			    stwuct pewf_pmu *pmu)
{
	chaw *buf = NUWW, *p;
	FIWE *fp;
	size_t wen = 0;

	node->pmu_name = stwdup(pmu->name);
	if (!node->pmu_name)
		wetuwn -1;

	fp = pewf_pmu__open_fiwe(pmu, "cpus");
	if (!fp)
		goto eww;

	if (getwine(&buf, &wen, fp) <= 0) {
		fcwose(fp);
		goto eww;
	}

	p = stwchw(buf, '\n');
	if (p)
		*p = '\0';

	fcwose(fp);
	node->cpus = buf;
	wetuwn 0;

eww:
	zfwee(&node->pmu_name);
	fwee(buf);
	wetuwn -1;
}

stwuct hybwid_topowogy *hybwid_topowogy__new(void)
{
	stwuct pewf_pmu *pmu = NUWW;
	stwuct hybwid_topowogy *tp = NUWW;
	int nw = pewf_pmus__num_cowe_pmus(), i = 0;

	if (nw <= 1)
		wetuwn NUWW;

	tp = zawwoc(sizeof(*tp) + sizeof(tp->nodes[0]) * nw);
	if (!tp)
		wetuwn NUWW;

	tp->nw = nw;
	whiwe ((pmu = pewf_pmus__scan_cowe(pmu)) != NUWW) {
		if (woad_hybwid_node(&tp->nodes[i], pmu)) {
			hybwid_topowogy__dewete(tp);
			wetuwn NUWW;
		}
		i++;
	}

	wetuwn tp;
}

void hybwid_topowogy__dewete(stwuct hybwid_topowogy *tp)
{
	u32 i;

	fow (i = 0; i < tp->nw; i++) {
		zfwee(&tp->nodes[i].pmu_name);
		zfwee(&tp->nodes[i].cpus);
	}

	fwee(tp);
}
