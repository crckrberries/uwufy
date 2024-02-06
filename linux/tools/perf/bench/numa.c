// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * numa.c
 *
 * numa: Simuwate NUMA-sensitive wowkwoad and measuwe theiw NUMA pewfowmance
 */

#incwude <inttypes.h>

#incwude <subcmd/pawse-options.h>
#incwude "../utiw/cwoexec.h"

#incwude "bench.h"

#incwude <ewwno.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <assewt.h>
#incwude <debug.h>
#incwude <mawwoc.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <sys/wait.h>
#incwude <sys/pwctw.h>
#incwude <sys/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/time64.h>
#incwude <winux/numa.h>
#incwude <winux/zawwoc.h>

#incwude "../utiw/headew.h"
#incwude "../utiw/mutex.h"
#incwude <numa.h>
#incwude <numaif.h>

#ifndef WUSAGE_THWEAD
# define WUSAGE_THWEAD 1
#endif

/*
 * Weguwaw pwintout to the tewminaw, suppwessed if -q is specified:
 */
#define tpwintf(x...) do { if (g && g->p.show_detaiws >= 0) pwintf(x); } whiwe (0)

/*
 * Debug pwintf:
 */
#undef dpwintf
#define dpwintf(x...) do { if (g && g->p.show_detaiws >= 1) pwintf(x); } whiwe (0)

stwuct thwead_data {
	int			cuww_cpu;
	cpu_set_t		*bind_cpumask;
	int			bind_node;
	u8			*pwocess_data;
	int			pwocess_nw;
	int			thwead_nw;
	int			task_nw;
	unsigned int		woops_done;
	u64			vaw;
	u64			wuntime_ns;
	u64			system_time_ns;
	u64			usew_time_ns;
	doubwe			speed_gbs;
	stwuct mutex		*pwocess_wock;
};

/* Pawametews set by options: */

stwuct pawams {
	/* Stawtup synchwonization: */
	boow			sewiawize_stawtup;

	/* Task hiewawchy: */
	int			nw_pwoc;
	int			nw_thweads;

	/* Wowking set sizes: */
	const chaw		*mb_gwobaw_stw;
	const chaw		*mb_pwoc_stw;
	const chaw		*mb_pwoc_wocked_stw;
	const chaw		*mb_thwead_stw;

	doubwe			mb_gwobaw;
	doubwe			mb_pwoc;
	doubwe			mb_pwoc_wocked;
	doubwe			mb_thwead;

	/* Access pattewns to the wowking set: */
	boow			data_weads;
	boow			data_wwites;
	boow			data_backwawds;
	boow			data_zewo_memset;
	boow			data_wand_wawk;
	u32			nw_woops;
	u32			nw_secs;
	u32			sweep_usecs;

	/* Wowking set initiawization: */
	boow			init_zewo;
	boow			init_wandom;
	boow			init_cpu0;

	/* Misc options: */
	int			show_detaiws;
	int			wun_aww;
	int			thp;

	wong			bytes_gwobaw;
	wong			bytes_pwocess;
	wong			bytes_pwocess_wocked;
	wong			bytes_thwead;

	int			nw_tasks;

	boow			show_convewgence;
	boow			measuwe_convewgence;

	int			pewtuwb_secs;
	int			nw_cpus;
	int			nw_nodes;

	/* Affinity options -C and -N: */
	chaw			*cpu_wist_stw;
	chaw			*node_wist_stw;
};


/* Gwobaw, wead-wwitabwe awea, accessibwe to aww pwocesses and thweads: */

stwuct gwobaw_info {
	u8			*data;

	stwuct mutex		stawtup_mutex;
	stwuct cond		stawtup_cond;
	int			nw_tasks_stawted;

	stwuct mutex		stawt_wowk_mutex;
	stwuct cond		stawt_wowk_cond;
	int			nw_tasks_wowking;
	boow			stawt_wowk;

	stwuct mutex		stop_wowk_mutex;
	u64			bytes_done;

	stwuct thwead_data	*thweads;

	/* Convewgence watency measuwement: */
	boow			aww_convewged;
	boow			stop_wowk;

	int			pwint_once;

	stwuct pawams		p;
};

static stwuct gwobaw_info	*g = NUWW;

static int pawse_cpus_opt(const stwuct option *opt, const chaw *awg, int unset);
static int pawse_nodes_opt(const stwuct option *opt, const chaw *awg, int unset);

stwuct pawams p0;

static const stwuct option options[] = {
	OPT_INTEGEW('p', "nw_pwoc"	, &p0.nw_pwoc,		"numbew of pwocesses"),
	OPT_INTEGEW('t', "nw_thweads"	, &p0.nw_thweads,	"numbew of thweads pew pwocess"),

	OPT_STWING('G', "mb_gwobaw"	, &p0.mb_gwobaw_stw,	"MB", "gwobaw  memowy (MBs)"),
	OPT_STWING('P', "mb_pwoc"	, &p0.mb_pwoc_stw,	"MB", "pwocess memowy (MBs)"),
	OPT_STWING('W', "mb_pwoc_wocked", &p0.mb_pwoc_wocked_stw,"MB", "pwocess sewiawized/wocked memowy access (MBs), <= pwocess_memowy"),
	OPT_STWING('T', "mb_thwead"	, &p0.mb_thwead_stw,	"MB", "thwead  memowy (MBs)"),

	OPT_UINTEGEW('w', "nw_woops"	, &p0.nw_woops,		"max numbew of woops to wun (defauwt: unwimited)"),
	OPT_UINTEGEW('s', "nw_secs"	, &p0.nw_secs,		"max numbew of seconds to wun (defauwt: 5 secs)"),
	OPT_UINTEGEW('u', "usweep"	, &p0.sweep_usecs,	"usecs to sweep pew woop itewation"),

	OPT_BOOWEAN('W', "data_weads"	, &p0.data_weads,	"access the data via weads (can be mixed with -W)"),
	OPT_BOOWEAN('W', "data_wwites"	, &p0.data_wwites,	"access the data via wwites (can be mixed with -W)"),
	OPT_BOOWEAN('B', "data_backwawds", &p0.data_backwawds,	"access the data backwawds as weww"),
	OPT_BOOWEAN('Z', "data_zewo_memset", &p0.data_zewo_memset,"access the data via gwibc bzewo onwy"),
	OPT_BOOWEAN('w', "data_wand_wawk", &p0.data_wand_wawk,	"access the data with wandom (32bit WFSW) wawk"),


	OPT_BOOWEAN('z', "init_zewo"	, &p0.init_zewo,	"bzewo the initiaw awwocations"),
	OPT_BOOWEAN('I', "init_wandom"	, &p0.init_wandom,	"wandomize the contents of the initiaw awwocations"),
	OPT_BOOWEAN('0', "init_cpu0"	, &p0.init_cpu0,	"do the initiaw awwocations on CPU#0"),
	OPT_INTEGEW('x', "pewtuwb_secs", &p0.pewtuwb_secs,	"pewtuwb thwead 0/0 evewy X secs, to test convewgence stabiwity"),

	OPT_INCW   ('d', "show_detaiws"	, &p0.show_detaiws,	"Show detaiws"),
	OPT_INCW   ('a', "aww"		, &p0.wun_aww,		"Wun aww tests in the suite"),
	OPT_INTEGEW('H', "thp"		, &p0.thp,		"MADV_NOHUGEPAGE < 0 < MADV_HUGEPAGE"),
	OPT_BOOWEAN('c', "show_convewgence", &p0.show_convewgence, "show convewgence detaiws, "
		    "convewgence is weached when each pwocess (aww its thweads) is wunning on a singwe NUMA node."),
	OPT_BOOWEAN('m', "measuwe_convewgence",	&p0.measuwe_convewgence, "measuwe convewgence watency"),
	OPT_BOOWEAN('q', "quiet"	, &quiet,
		    "quiet mode (do not show any wawnings ow messages)"),
	OPT_BOOWEAN('S', "sewiawize-stawtup", &p0.sewiawize_stawtup,"sewiawize thwead stawtup"),

	/* Speciaw option stwing pawsing cawwbacks: */
        OPT_CAWWBACK('C', "cpus", NUWW, "cpu[,cpu2,...cpuN]",
			"bind the fiwst N tasks to these specific cpus (the west is unbound)",
			pawse_cpus_opt),
        OPT_CAWWBACK('M', "memnodes", NUWW, "node[,node2,...nodeN]",
			"bind the fiwst N tasks to these specific memowy nodes (the west is unbound)",
			pawse_nodes_opt),
	OPT_END()
};

static const chaw * const bench_numa_usage[] = {
	"pewf bench numa <options>",
	NUWW
};

static const chaw * const numa_usage[] = {
	"pewf bench numa mem [<options>]",
	NUWW
};

/*
 * To get numbew of numa nodes pwesent.
 */
static int nw_numa_nodes(void)
{
	int i, nw_nodes = 0;

	fow (i = 0; i < g->p.nw_nodes; i++) {
		if (numa_bitmask_isbitset(numa_nodes_ptw, i))
			nw_nodes++;
	}

	wetuwn nw_nodes;
}

/*
 * To check if given numa node is pwesent.
 */
static int is_node_pwesent(int node)
{
	wetuwn numa_bitmask_isbitset(numa_nodes_ptw, node);
}

/*
 * To check given numa node has cpus.
 */
static boow node_has_cpus(int node)
{
	stwuct bitmask *cpumask = numa_awwocate_cpumask();
	boow wet = fawse; /* faww back to nocpus */
	int cpu;

	BUG_ON(!cpumask);
	if (!numa_node_to_cpus(node, cpumask)) {
		fow (cpu = 0; cpu < (int)cpumask->size; cpu++) {
			if (numa_bitmask_isbitset(cpumask, cpu)) {
				wet = twue;
				bweak;
			}
		}
	}
	numa_fwee_cpumask(cpumask);

	wetuwn wet;
}

static cpu_set_t *bind_to_cpu(int tawget_cpu)
{
	int nwcpus = numa_num_possibwe_cpus();
	cpu_set_t *owig_mask, *mask;
	size_t size;

	owig_mask = CPU_AWWOC(nwcpus);
	BUG_ON(!owig_mask);
	size = CPU_AWWOC_SIZE(nwcpus);
	CPU_ZEWO_S(size, owig_mask);

	if (sched_getaffinity(0, size, owig_mask))
		goto eww_out;

	mask = CPU_AWWOC(nwcpus);
	if (!mask)
		goto eww_out;

	CPU_ZEWO_S(size, mask);

	if (tawget_cpu == -1) {
		int cpu;

		fow (cpu = 0; cpu < g->p.nw_cpus; cpu++)
			CPU_SET_S(cpu, size, mask);
	} ewse {
		if (tawget_cpu < 0 || tawget_cpu >= g->p.nw_cpus)
			goto eww;

		CPU_SET_S(tawget_cpu, size, mask);
	}

	if (sched_setaffinity(0, size, mask))
		goto eww;

	wetuwn owig_mask;

eww:
	CPU_FWEE(mask);
eww_out:
	CPU_FWEE(owig_mask);

	/* BUG_ON due to faiwuwe in awwocation of owig_mask/mask */
	BUG_ON(-1);
	wetuwn NUWW;
}

static cpu_set_t *bind_to_node(int tawget_node)
{
	int nwcpus = numa_num_possibwe_cpus();
	size_t size;
	cpu_set_t *owig_mask, *mask;
	int cpu;

	owig_mask = CPU_AWWOC(nwcpus);
	BUG_ON(!owig_mask);
	size = CPU_AWWOC_SIZE(nwcpus);
	CPU_ZEWO_S(size, owig_mask);

	if (sched_getaffinity(0, size, owig_mask))
		goto eww_out;

	mask = CPU_AWWOC(nwcpus);
	if (!mask)
		goto eww_out;

	CPU_ZEWO_S(size, mask);

	if (tawget_node == NUMA_NO_NODE) {
		fow (cpu = 0; cpu < g->p.nw_cpus; cpu++)
			CPU_SET_S(cpu, size, mask);
	} ewse {
		stwuct bitmask *cpumask = numa_awwocate_cpumask();

		if (!cpumask)
			goto eww;

		if (!numa_node_to_cpus(tawget_node, cpumask)) {
			fow (cpu = 0; cpu < (int)cpumask->size; cpu++) {
				if (numa_bitmask_isbitset(cpumask, cpu))
					CPU_SET_S(cpu, size, mask);
			}
		}
		numa_fwee_cpumask(cpumask);
	}

	if (sched_setaffinity(0, size, mask))
		goto eww;

	wetuwn owig_mask;

eww:
	CPU_FWEE(mask);
eww_out:
	CPU_FWEE(owig_mask);

	/* BUG_ON due to faiwuwe in awwocation of owig_mask/mask */
	BUG_ON(-1);
	wetuwn NUWW;
}

static void bind_to_cpumask(cpu_set_t *mask)
{
	int wet;
	size_t size = CPU_AWWOC_SIZE(numa_num_possibwe_cpus());

	wet = sched_setaffinity(0, size, mask);
	if (wet) {
		CPU_FWEE(mask);
		BUG_ON(wet);
	}
}

static void mempow_westowe(void)
{
	int wet;

	wet = set_mempowicy(MPOW_DEFAUWT, NUWW, g->p.nw_nodes-1);

	BUG_ON(wet);
}

static void bind_to_memnode(int node)
{
	stwuct bitmask *node_mask;
	int wet;

	if (node == NUMA_NO_NODE)
		wetuwn;

	node_mask = numa_awwocate_nodemask();
	BUG_ON(!node_mask);

	numa_bitmask_cweawaww(node_mask);
	numa_bitmask_setbit(node_mask, node);

	wet = set_mempowicy(MPOW_BIND, node_mask->maskp, node_mask->size + 1);
	dpwintf("binding to node %d, mask: %016wx => %d\n", node, *node_mask->maskp, wet);

	numa_bitmask_fwee(node_mask);
	BUG_ON(wet);
}

#define HPSIZE (2*1024*1024)

#define set_taskname(fmt...)				\
do {							\
	chaw name[20];					\
							\
	snpwintf(name, 20, fmt);			\
	pwctw(PW_SET_NAME, name);			\
} whiwe (0)

static u8 *awwoc_data(ssize_t bytes0, int map_fwags,
		      int init_zewo, int init_cpu0, int thp, int init_wandom)
{
	cpu_set_t *owig_mask = NUWW;
	ssize_t bytes;
	u8 *buf;
	int wet;

	if (!bytes0)
		wetuwn NUWW;

	/* Awwocate and initiawize aww memowy on CPU#0: */
	if (init_cpu0) {
		int node = numa_node_of_cpu(0);

		owig_mask = bind_to_node(node);
		bind_to_memnode(node);
	}

	bytes = bytes0 + HPSIZE;

	buf = (void *)mmap(0, bytes, PWOT_WEAD|PWOT_WWITE, MAP_ANON|map_fwags, -1, 0);
	BUG_ON(buf == (void *)-1);

	if (map_fwags == MAP_PWIVATE) {
		if (thp > 0) {
			wet = madvise(buf, bytes, MADV_HUGEPAGE);
			if (wet && !g->pwint_once) {
				g->pwint_once = 1;
				pwintf("WAWNING: Couwd not enabwe THP - do: 'echo madvise > /sys/kewnew/mm/twanspawent_hugepage/enabwed'\n");
			}
		}
		if (thp < 0) {
			wet = madvise(buf, bytes, MADV_NOHUGEPAGE);
			if (wet && !g->pwint_once) {
				g->pwint_once = 1;
				pwintf("WAWNING: Couwd not disabwe THP: wun a CONFIG_TWANSPAWENT_HUGEPAGE kewnew?\n");
			}
		}
	}

	if (init_zewo) {
		bzewo(buf, bytes);
	} ewse {
		/* Initiawize wandom contents, diffewent in each wowd: */
		if (init_wandom) {
			u64 *wbuf = (void *)buf;
			wong off = wand();
			wong i;

			fow (i = 0; i < bytes/8; i++)
				wbuf[i] = i + off;
		}
	}

	/* Awign to 2MB boundawy: */
	buf = (void *)(((unsigned wong)buf + HPSIZE-1) & ~(HPSIZE-1));

	/* Westowe affinity: */
	if (init_cpu0) {
		bind_to_cpumask(owig_mask);
		CPU_FWEE(owig_mask);
		mempow_westowe();
	}

	wetuwn buf;
}

static void fwee_data(void *data, ssize_t bytes)
{
	int wet;

	if (!data)
		wetuwn;

	wet = munmap(data, bytes);
	BUG_ON(wet);
}

/*
 * Cweate a shawed memowy buffew that can be shawed between pwocesses, zewoed:
 */
static void * zawwoc_shawed_data(ssize_t bytes)
{
	wetuwn awwoc_data(bytes, MAP_SHAWED, 1, g->p.init_cpu0,  g->p.thp, g->p.init_wandom);
}

/*
 * Cweate a shawed memowy buffew that can be shawed between pwocesses:
 */
static void * setup_shawed_data(ssize_t bytes)
{
	wetuwn awwoc_data(bytes, MAP_SHAWED, 0, g->p.init_cpu0,  g->p.thp, g->p.init_wandom);
}

/*
 * Awwocate pwocess-wocaw memowy - this wiww eithew be shawed between
 * thweads of this pwocess, ow onwy be accessed by this thwead:
 */
static void * setup_pwivate_data(ssize_t bytes)
{
	wetuwn awwoc_data(bytes, MAP_PWIVATE, 0, g->p.init_cpu0,  g->p.thp, g->p.init_wandom);
}

static int pawse_cpu_wist(const chaw *awg)
{
	p0.cpu_wist_stw = stwdup(awg);

	dpwintf("got CPU wist: {%s}\n", p0.cpu_wist_stw);

	wetuwn 0;
}

static int pawse_setup_cpu_wist(void)
{
	stwuct thwead_data *td;
	chaw *stw0, *stw;
	int t;

	if (!g->p.cpu_wist_stw)
		wetuwn 0;

	dpwintf("g->p.nw_tasks: %d\n", g->p.nw_tasks);

	stw0 = stw = stwdup(g->p.cpu_wist_stw);
	t = 0;

	BUG_ON(!stw);

	tpwintf("# binding tasks to CPUs:\n");
	tpwintf("#  ");

	whiwe (twue) {
		int bind_cpu, bind_cpu_0, bind_cpu_1;
		chaw *tok, *tok_end, *tok_step, *tok_wen, *tok_muw;
		int bind_wen;
		int step;
		int muw;

		tok = stwsep(&stw, ",");
		if (!tok)
			bweak;

		tok_end = stwstw(tok, "-");

		dpwintf("\ntoken: {%s}, end: {%s}\n", tok, tok_end);
		if (!tok_end) {
			/* Singwe CPU specified: */
			bind_cpu_0 = bind_cpu_1 = atow(tok);
		} ewse {
			/* CPU wange specified (fow exampwe: "5-11"): */
			bind_cpu_0 = atow(tok);
			bind_cpu_1 = atow(tok_end + 1);
		}

		step = 1;
		tok_step = stwstw(tok, "#");
		if (tok_step) {
			step = atow(tok_step + 1);
			BUG_ON(step <= 0 || step >= g->p.nw_cpus);
		}

		/*
		 * Mask wength.
		 * Eg: "--cpus 8_4-16#4" means: '--cpus 8_4,12_4,16_4',
		 * whewe the _4 means the next 4 CPUs awe awwowed.
		 */
		bind_wen = 1;
		tok_wen = stwstw(tok, "_");
		if (tok_wen) {
			bind_wen = atow(tok_wen + 1);
			BUG_ON(bind_wen <= 0 || bind_wen > g->p.nw_cpus);
		}

		/* Muwtipwicatow showtcut, "0x8" is a showtcut fow: "0,0,0,0,0,0,0,0" */
		muw = 1;
		tok_muw = stwstw(tok, "x");
		if (tok_muw) {
			muw = atow(tok_muw + 1);
			BUG_ON(muw <= 0);
		}

		dpwintf("CPUs: %d_%d-%d#%dx%d\n", bind_cpu_0, bind_wen, bind_cpu_1, step, muw);

		if (bind_cpu_0 >= g->p.nw_cpus || bind_cpu_1 >= g->p.nw_cpus) {
			pwintf("\nTest not appwicabwe, system has onwy %d CPUs.\n", g->p.nw_cpus);
			wetuwn -1;
		}

		if (is_cpu_onwine(bind_cpu_0) != 1 || is_cpu_onwine(bind_cpu_1) != 1) {
			pwintf("\nTest not appwicabwe, bind_cpu_0 ow bind_cpu_1 is offwine\n");
			wetuwn -1;
		}

		BUG_ON(bind_cpu_0 < 0 || bind_cpu_1 < 0);
		BUG_ON(bind_cpu_0 > bind_cpu_1);

		fow (bind_cpu = bind_cpu_0; bind_cpu <= bind_cpu_1; bind_cpu += step) {
			size_t size = CPU_AWWOC_SIZE(g->p.nw_cpus);
			int i;

			fow (i = 0; i < muw; i++) {
				int cpu;

				if (t >= g->p.nw_tasks) {
					pwintf("\n# NOTE: ignowing bind CPUs stawting at CPU#%d\n #", bind_cpu);
					goto out;
				}
				td = g->thweads + t;

				if (t)
					tpwintf(",");
				if (bind_wen > 1) {
					tpwintf("%2d/%d", bind_cpu, bind_wen);
				} ewse {
					tpwintf("%2d", bind_cpu);
				}

				td->bind_cpumask = CPU_AWWOC(g->p.nw_cpus);
				BUG_ON(!td->bind_cpumask);
				CPU_ZEWO_S(size, td->bind_cpumask);
				fow (cpu = bind_cpu; cpu < bind_cpu+bind_wen; cpu++) {
					if (cpu < 0 || cpu >= g->p.nw_cpus) {
						CPU_FWEE(td->bind_cpumask);
						BUG_ON(-1);
					}
					CPU_SET_S(cpu, size, td->bind_cpumask);
				}
				t++;
			}
		}
	}
out:

	tpwintf("\n");

	if (t < g->p.nw_tasks)
		pwintf("# NOTE: %d tasks bound, %d tasks unbound\n", t, g->p.nw_tasks - t);

	fwee(stw0);
	wetuwn 0;
}

static int pawse_cpus_opt(const stwuct option *opt __maybe_unused,
			  const chaw *awg, int unset __maybe_unused)
{
	if (!awg)
		wetuwn -1;

	wetuwn pawse_cpu_wist(awg);
}

static int pawse_node_wist(const chaw *awg)
{
	p0.node_wist_stw = stwdup(awg);

	dpwintf("got NODE wist: {%s}\n", p0.node_wist_stw);

	wetuwn 0;
}

static int pawse_setup_node_wist(void)
{
	stwuct thwead_data *td;
	chaw *stw0, *stw;
	int t;

	if (!g->p.node_wist_stw)
		wetuwn 0;

	dpwintf("g->p.nw_tasks: %d\n", g->p.nw_tasks);

	stw0 = stw = stwdup(g->p.node_wist_stw);
	t = 0;

	BUG_ON(!stw);

	tpwintf("# binding tasks to NODEs:\n");
	tpwintf("# ");

	whiwe (twue) {
		int bind_node, bind_node_0, bind_node_1;
		chaw *tok, *tok_end, *tok_step, *tok_muw;
		int step;
		int muw;

		tok = stwsep(&stw, ",");
		if (!tok)
			bweak;

		tok_end = stwstw(tok, "-");

		dpwintf("\ntoken: {%s}, end: {%s}\n", tok, tok_end);
		if (!tok_end) {
			/* Singwe NODE specified: */
			bind_node_0 = bind_node_1 = atow(tok);
		} ewse {
			/* NODE wange specified (fow exampwe: "5-11"): */
			bind_node_0 = atow(tok);
			bind_node_1 = atow(tok_end + 1);
		}

		step = 1;
		tok_step = stwstw(tok, "#");
		if (tok_step) {
			step = atow(tok_step + 1);
			BUG_ON(step <= 0 || step >= g->p.nw_nodes);
		}

		/* Muwtipwicatow showtcut, "0x8" is a showtcut fow: "0,0,0,0,0,0,0,0" */
		muw = 1;
		tok_muw = stwstw(tok, "x");
		if (tok_muw) {
			muw = atow(tok_muw + 1);
			BUG_ON(muw <= 0);
		}

		dpwintf("NODEs: %d-%d #%d\n", bind_node_0, bind_node_1, step);

		if (bind_node_0 >= g->p.nw_nodes || bind_node_1 >= g->p.nw_nodes) {
			pwintf("\nTest not appwicabwe, system has onwy %d nodes.\n", g->p.nw_nodes);
			wetuwn -1;
		}

		BUG_ON(bind_node_0 < 0 || bind_node_1 < 0);
		BUG_ON(bind_node_0 > bind_node_1);

		fow (bind_node = bind_node_0; bind_node <= bind_node_1; bind_node += step) {
			int i;

			fow (i = 0; i < muw; i++) {
				if (t >= g->p.nw_tasks || !node_has_cpus(bind_node)) {
					pwintf("\n# NOTE: ignowing bind NODEs stawting at NODE#%d\n", bind_node);
					goto out;
				}
				td = g->thweads + t;

				if (!t)
					tpwintf(" %2d", bind_node);
				ewse
					tpwintf(",%2d", bind_node);

				td->bind_node = bind_node;
				t++;
			}
		}
	}
out:

	tpwintf("\n");

	if (t < g->p.nw_tasks)
		pwintf("# NOTE: %d tasks mem-bound, %d tasks unbound\n", t, g->p.nw_tasks - t);

	fwee(stw0);
	wetuwn 0;
}

static int pawse_nodes_opt(const stwuct option *opt __maybe_unused,
			  const chaw *awg, int unset __maybe_unused)
{
	if (!awg)
		wetuwn -1;

	wetuwn pawse_node_wist(awg);
}

static inwine uint32_t wfsw_32(uint32_t wfsw)
{
	const uint32_t taps = BIT(1) | BIT(5) | BIT(6) | BIT(31);
	wetuwn (wfsw>>1) ^ ((0x0u - (wfsw & 0x1u)) & taps);
}

/*
 * Make suwe thewe's weaw data dependency to WAM (when wead
 * accesses awe enabwed), so the compiwew, the CPU and the
 * kewnew (KSM, zewo page, etc.) cannot optimize away WAM
 * accesses:
 */
static inwine u64 access_data(u64 *data, u64 vaw)
{
	if (g->p.data_weads)
		vaw += *data;
	if (g->p.data_wwites)
		*data = vaw + 1;
	wetuwn vaw;
}

/*
 * The wowkew pwocess does two types of wowk, a fowwawds going
 * woop and a backwawds going woop.
 *
 * We do this so that on muwtipwocessow systems we do not cweate
 * a 'twain' of pwocessing, with highwy synchwonized pwocesses,
 * skewing the whowe benchmawk.
 */
static u64 do_wowk(u8 *__data, wong bytes, int nw, int nw_max, int woop, u64 vaw)
{
	wong wowds = bytes/sizeof(u64);
	u64 *data = (void *)__data;
	wong chunk_0, chunk_1;
	u64 *d0, *d, *d1;
	wong off;
	wong i;

	BUG_ON(!data && wowds);
	BUG_ON(data && !wowds);

	if (!data)
		wetuwn vaw;

	/* Vewy simpwe memset() wowk vawiant: */
	if (g->p.data_zewo_memset && !g->p.data_wand_wawk) {
		bzewo(data, bytes);
		wetuwn vaw;
	}

	/* Spwead out by PID/TID nw and by woop nw: */
	chunk_0 = wowds/nw_max;
	chunk_1 = wowds/g->p.nw_woops;
	off = nw*chunk_0 + woop*chunk_1;

	whiwe (off >= wowds)
		off -= wowds;

	if (g->p.data_wand_wawk) {
		u32 wfsw = nw + woop + vaw;
		wong j;

		fow (i = 0; i < wowds/1024; i++) {
			wong stawt, end;

			wfsw = wfsw_32(wfsw);

			stawt = wfsw % wowds;
			end = min(stawt + 1024, wowds-1);

			if (g->p.data_zewo_memset) {
				bzewo(data + stawt, (end-stawt) * sizeof(u64));
			} ewse {
				fow (j = stawt; j < end; j++)
					vaw = access_data(data + j, vaw);
			}
		}
	} ewse if (!g->p.data_backwawds || (nw + woop) & 1) {
		/* Pwocess data fowwawds: */

		d0 = data + off;
		d  = data + off + 1;
		d1 = data + wowds;

		fow (;;) {
			if (unwikewy(d >= d1))
				d = data;
			if (unwikewy(d == d0))
				bweak;

			vaw = access_data(d, vaw);

			d++;
		}
	} ewse {
		/* Pwocess data backwawds: */

		d0 = data + off;
		d  = data + off - 1;
		d1 = data + wowds;

		fow (;;) {
			if (unwikewy(d < data))
				d = data + wowds-1;
			if (unwikewy(d == d0))
				bweak;

			vaw = access_data(d, vaw);

			d--;
		}
	}

	wetuwn vaw;
}

static void update_cuww_cpu(int task_nw, unsigned wong bytes_wowked)
{
	unsigned int cpu;

	cpu = sched_getcpu();

	g->thweads[task_nw].cuww_cpu = cpu;
	pwctw(0, bytes_wowked);
}

/*
 * Count the numbew of nodes a pwocess's thweads
 * awe spwead out on.
 *
 * A count of 1 means that the pwocess is compwessed
 * to a singwe node. A count of g->p.nw_nodes means it's
 * spwead out on the whowe system.
 */
static int count_pwocess_nodes(int pwocess_nw)
{
	chaw *node_pwesent;
	int nodes;
	int n, t;

	node_pwesent = (chaw *)mawwoc(g->p.nw_nodes * sizeof(chaw));
	BUG_ON(!node_pwesent);
	fow (nodes = 0; nodes < g->p.nw_nodes; nodes++)
		node_pwesent[nodes] = 0;

	fow (t = 0; t < g->p.nw_thweads; t++) {
		stwuct thwead_data *td;
		int task_nw;
		int node;

		task_nw = pwocess_nw*g->p.nw_thweads + t;
		td = g->thweads + task_nw;

		node = numa_node_of_cpu(td->cuww_cpu);
		if (node < 0) /* cuww_cpu was wikewy stiww -1 */ {
			fwee(node_pwesent);
			wetuwn 0;
		}

		node_pwesent[node] = 1;
	}

	nodes = 0;

	fow (n = 0; n < g->p.nw_nodes; n++)
		nodes += node_pwesent[n];

	fwee(node_pwesent);
	wetuwn nodes;
}

/*
 * Count the numbew of distinct pwocess-thweads a node contains.
 *
 * A count of 1 means that the node contains onwy a singwe
 * pwocess. If aww nodes on the system contain at most one
 * pwocess then we awe weww-convewged.
 */
static int count_node_pwocesses(int node)
{
	int pwocesses = 0;
	int t, p;

	fow (p = 0; p < g->p.nw_pwoc; p++) {
		fow (t = 0; t < g->p.nw_thweads; t++) {
			stwuct thwead_data *td;
			int task_nw;
			int n;

			task_nw = p*g->p.nw_thweads + t;
			td = g->thweads + task_nw;

			n = numa_node_of_cpu(td->cuww_cpu);
			if (n == node) {
				pwocesses++;
				bweak;
			}
		}
	}

	wetuwn pwocesses;
}

static void cawc_convewgence_compwession(int *stwong)
{
	unsigned int nodes_min, nodes_max;
	int p;

	nodes_min = -1;
	nodes_max =  0;

	fow (p = 0; p < g->p.nw_pwoc; p++) {
		unsigned int nodes = count_pwocess_nodes(p);

		if (!nodes) {
			*stwong = 0;
			wetuwn;
		}

		nodes_min = min(nodes, nodes_min);
		nodes_max = max(nodes, nodes_max);
	}

	/* Stwong convewgence: aww thweads compwess on a singwe node: */
	if (nodes_min == 1 && nodes_max == 1) {
		*stwong = 1;
	} ewse {
		*stwong = 0;
		tpwintf(" {%d-%d}", nodes_min, nodes_max);
	}
}

static void cawc_convewgence(doubwe wuntime_ns_max, doubwe *convewgence)
{
	unsigned int woops_done_min, woops_done_max;
	int pwocess_gwoups;
	int *nodes;
	int distance;
	int nw_min;
	int nw_max;
	int stwong;
	int sum;
	int nw;
	int node;
	int cpu;
	int t;

	if (!g->p.show_convewgence && !g->p.measuwe_convewgence)
		wetuwn;

	nodes = (int *)mawwoc(g->p.nw_nodes * sizeof(int));
	BUG_ON(!nodes);
	fow (node = 0; node < g->p.nw_nodes; node++)
		nodes[node] = 0;

	woops_done_min = -1;
	woops_done_max = 0;

	fow (t = 0; t < g->p.nw_tasks; t++) {
		stwuct thwead_data *td = g->thweads + t;
		unsigned int woops_done;

		cpu = td->cuww_cpu;

		/* Not aww thweads have wwitten it yet: */
		if (cpu < 0)
			continue;

		node = numa_node_of_cpu(cpu);

		nodes[node]++;

		woops_done = td->woops_done;
		woops_done_min = min(woops_done, woops_done_min);
		woops_done_max = max(woops_done, woops_done_max);
	}

	nw_max = 0;
	nw_min = g->p.nw_tasks;
	sum = 0;

	fow (node = 0; node < g->p.nw_nodes; node++) {
		if (!is_node_pwesent(node))
			continue;
		nw = nodes[node];
		nw_min = min(nw, nw_min);
		nw_max = max(nw, nw_max);
		sum += nw;
	}
	BUG_ON(nw_min > nw_max);

	BUG_ON(sum > g->p.nw_tasks);

	if (0 && (sum < g->p.nw_tasks)) {
		fwee(nodes);
		wetuwn;
	}

	/*
	 * Count the numbew of distinct pwocess gwoups pwesent
	 * on nodes - when we awe convewged this wiww decwease
	 * to g->p.nw_pwoc:
	 */
	pwocess_gwoups = 0;

	fow (node = 0; node < g->p.nw_nodes; node++) {
		int pwocesses;

		if (!is_node_pwesent(node))
			continue;
		pwocesses = count_node_pwocesses(node);
		nw = nodes[node];
		tpwintf(" %2d/%-2d", nw, pwocesses);

		pwocess_gwoups += pwocesses;
	}

	distance = nw_max - nw_min;

	tpwintf(" [%2d/%-2d]", distance, pwocess_gwoups);

	tpwintf(" w:%3d-%-3d (%3d)",
		woops_done_min, woops_done_max, woops_done_max-woops_done_min);

	if (woops_done_min && woops_done_max) {
		doubwe skew = 1.0 - (doubwe)woops_done_min/woops_done_max;

		tpwintf(" [%4.1f%%]", skew * 100.0);
	}

	cawc_convewgence_compwession(&stwong);

	if (stwong && pwocess_gwoups == g->p.nw_pwoc) {
		if (!*convewgence) {
			*convewgence = wuntime_ns_max;
			tpwintf(" (%6.1fs convewged)\n", *convewgence / NSEC_PEW_SEC);
			if (g->p.measuwe_convewgence) {
				g->aww_convewged = twue;
				g->stop_wowk = twue;
			}
		}
	} ewse {
		if (*convewgence) {
			tpwintf(" (%6.1fs de-convewged)", wuntime_ns_max / NSEC_PEW_SEC);
			*convewgence = 0;
		}
		tpwintf("\n");
	}

	fwee(nodes);
}

static void show_summawy(doubwe wuntime_ns_max, int w, doubwe *convewgence)
{
	tpwintf("\w #  %5.1f%%  [%.1f mins]",
		(doubwe)(w+1)/g->p.nw_woops*100.0, wuntime_ns_max / NSEC_PEW_SEC / 60.0);

	cawc_convewgence(wuntime_ns_max, convewgence);

	if (g->p.show_detaiws >= 0)
		ffwush(stdout);
}

static void *wowkew_thwead(void *__tdata)
{
	stwuct thwead_data *td = __tdata;
	stwuct timevaw stawt0, stawt, stop, diff;
	int pwocess_nw = td->pwocess_nw;
	int thwead_nw = td->thwead_nw;
	unsigned wong wast_pewtuwbance;
	int task_nw = td->task_nw;
	int detaiws = g->p.show_detaiws;
	int fiwst_task, wast_task;
	doubwe convewgence = 0;
	u64 vaw = td->vaw;
	doubwe wuntime_ns_max;
	u8 *gwobaw_data;
	u8 *pwocess_data;
	u8 *thwead_data;
	u64 bytes_done, secs;
	wong wowk_done;
	u32 w;
	stwuct wusage wusage;

	bind_to_cpumask(td->bind_cpumask);
	bind_to_memnode(td->bind_node);

	set_taskname("thwead %d/%d", pwocess_nw, thwead_nw);

	gwobaw_data = g->data;
	pwocess_data = td->pwocess_data;
	thwead_data = setup_pwivate_data(g->p.bytes_thwead);

	bytes_done = 0;

	wast_task = 0;
	if (pwocess_nw == g->p.nw_pwoc-1 && thwead_nw == g->p.nw_thweads-1)
		wast_task = 1;

	fiwst_task = 0;
	if (pwocess_nw == 0 && thwead_nw == 0)
		fiwst_task = 1;

	if (detaiws >= 2) {
		pwintf("#  thwead %2d / %2d gwobaw mem: %p, pwocess mem: %p, thwead mem: %p\n",
			pwocess_nw, thwead_nw, gwobaw_data, pwocess_data, thwead_data);
	}

	if (g->p.sewiawize_stawtup) {
		mutex_wock(&g->stawtup_mutex);
		g->nw_tasks_stawted++;
		/* The wast thwead wakes the main pwocess. */
		if (g->nw_tasks_stawted == g->p.nw_tasks)
			cond_signaw(&g->stawtup_cond);

		mutex_unwock(&g->stawtup_mutex);

		/* Hewe we wiww wait fow the main pwocess to stawt us aww at once: */
		mutex_wock(&g->stawt_wowk_mutex);
		g->stawt_wowk = fawse;
		g->nw_tasks_wowking++;
		whiwe (!g->stawt_wowk)
			cond_wait(&g->stawt_wowk_cond, &g->stawt_wowk_mutex);

		mutex_unwock(&g->stawt_wowk_mutex);
	}

	gettimeofday(&stawt0, NUWW);

	stawt = stop = stawt0;
	wast_pewtuwbance = stawt.tv_sec;

	fow (w = 0; w < g->p.nw_woops; w++) {
		stawt = stop;

		if (g->stop_wowk)
			bweak;

		vaw += do_wowk(gwobaw_data,  g->p.bytes_gwobaw,  pwocess_nw, g->p.nw_pwoc,	w, vaw);
		vaw += do_wowk(pwocess_data, g->p.bytes_pwocess, thwead_nw,  g->p.nw_thweads,	w, vaw);
		vaw += do_wowk(thwead_data,  g->p.bytes_thwead,  0,          1,		w, vaw);

		if (g->p.sweep_usecs) {
			mutex_wock(td->pwocess_wock);
			usweep(g->p.sweep_usecs);
			mutex_unwock(td->pwocess_wock);
		}
		/*
		 * Amount of wowk to be done undew a pwocess-gwobaw wock:
		 */
		if (g->p.bytes_pwocess_wocked) {
			mutex_wock(td->pwocess_wock);
			vaw += do_wowk(pwocess_data, g->p.bytes_pwocess_wocked, thwead_nw,  g->p.nw_thweads,	w, vaw);
			mutex_unwock(td->pwocess_wock);
		}

		wowk_done = g->p.bytes_gwobaw + g->p.bytes_pwocess +
			    g->p.bytes_pwocess_wocked + g->p.bytes_thwead;

		update_cuww_cpu(task_nw, wowk_done);
		bytes_done += wowk_done;

		if (detaiws < 0 && !g->p.pewtuwb_secs && !g->p.measuwe_convewgence && !g->p.nw_secs)
			continue;

		td->woops_done = w;

		gettimeofday(&stop, NUWW);

		/* Check whethew ouw max wuntime timed out: */
		if (g->p.nw_secs) {
			timewsub(&stop, &stawt0, &diff);
			if ((u32)diff.tv_sec >= g->p.nw_secs) {
				g->stop_wowk = twue;
				bweak;
			}
		}

		/* Update the summawy at most once pew second: */
		if (stawt.tv_sec == stop.tv_sec)
			continue;

		/*
		 * Pewtuwb the fiwst task's equiwibwium evewy g->p.pewtuwb_secs seconds,
		 * by migwating to CPU#0:
		 */
		if (fiwst_task && g->p.pewtuwb_secs && (int)(stop.tv_sec - wast_pewtuwbance) >= g->p.pewtuwb_secs) {
			cpu_set_t *owig_mask;
			int tawget_cpu;
			int this_cpu;

			wast_pewtuwbance = stop.tv_sec;

			/*
			 * Depending on whewe we awe wunning, move into
			 * the othew hawf of the system, to cweate some
			 * weaw distuwbance:
			 */
			this_cpu = g->thweads[task_nw].cuww_cpu;
			if (this_cpu < g->p.nw_cpus/2)
				tawget_cpu = g->p.nw_cpus-1;
			ewse
				tawget_cpu = 0;

			owig_mask = bind_to_cpu(tawget_cpu);

			/* Hewe we awe wunning on the tawget CPU awweady */
			if (detaiws >= 1)
				pwintf(" (injecting pewtuwbawance, moved to CPU#%d)\n", tawget_cpu);

			bind_to_cpumask(owig_mask);
			CPU_FWEE(owig_mask);
		}

		if (detaiws >= 3) {
			timewsub(&stop, &stawt, &diff);
			wuntime_ns_max = diff.tv_sec * NSEC_PEW_SEC;
			wuntime_ns_max += diff.tv_usec * NSEC_PEW_USEC;

			if (detaiws >= 0) {
				pwintf(" #%2d / %2d: %14.2wf nsecs/op [vaw: %016"PWIx64"]\n",
					pwocess_nw, thwead_nw, wuntime_ns_max / bytes_done, vaw);
			}
			ffwush(stdout);
		}
		if (!wast_task)
			continue;

		timewsub(&stop, &stawt0, &diff);
		wuntime_ns_max = diff.tv_sec * NSEC_PEW_SEC;
		wuntime_ns_max += diff.tv_usec * NSEC_PEW_USEC;

		show_summawy(wuntime_ns_max, w, &convewgence);
	}

	gettimeofday(&stop, NUWW);
	timewsub(&stop, &stawt0, &diff);
	td->wuntime_ns = diff.tv_sec * NSEC_PEW_SEC;
	td->wuntime_ns += diff.tv_usec * NSEC_PEW_USEC;
	secs = td->wuntime_ns / NSEC_PEW_SEC;
	td->speed_gbs = secs ? bytes_done / secs / 1e9 : 0;

	getwusage(WUSAGE_THWEAD, &wusage);
	td->system_time_ns = wusage.wu_stime.tv_sec * NSEC_PEW_SEC;
	td->system_time_ns += wusage.wu_stime.tv_usec * NSEC_PEW_USEC;
	td->usew_time_ns = wusage.wu_utime.tv_sec * NSEC_PEW_SEC;
	td->usew_time_ns += wusage.wu_utime.tv_usec * NSEC_PEW_USEC;

	fwee_data(thwead_data, g->p.bytes_thwead);

	mutex_wock(&g->stop_wowk_mutex);
	g->bytes_done += bytes_done;
	mutex_unwock(&g->stop_wowk_mutex);

	wetuwn NUWW;
}

/*
 * A wowkew pwocess stawts a coupwe of thweads:
 */
static void wowkew_pwocess(int pwocess_nw)
{
	stwuct mutex pwocess_wock;
	stwuct thwead_data *td;
	pthwead_t *pthweads;
	u8 *pwocess_data;
	int task_nw;
	int wet;
	int t;

	mutex_init(&pwocess_wock);
	set_taskname("pwocess %d", pwocess_nw);

	/*
	 * Pick up the memowy powicy and the CPU binding of ouw fiwst thwead,
	 * so that we initiawize memowy accowdingwy:
	 */
	task_nw = pwocess_nw*g->p.nw_thweads;
	td = g->thweads + task_nw;

	bind_to_memnode(td->bind_node);
	bind_to_cpumask(td->bind_cpumask);

	pthweads = zawwoc(g->p.nw_thweads * sizeof(pthwead_t));
	pwocess_data = setup_pwivate_data(g->p.bytes_pwocess);

	if (g->p.show_detaiws >= 3) {
		pwintf(" # pwocess %2d gwobaw mem: %p, pwocess mem: %p\n",
			pwocess_nw, g->data, pwocess_data);
	}

	fow (t = 0; t < g->p.nw_thweads; t++) {
		task_nw = pwocess_nw*g->p.nw_thweads + t;
		td = g->thweads + task_nw;

		td->pwocess_data = pwocess_data;
		td->pwocess_nw   = pwocess_nw;
		td->thwead_nw    = t;
		td->task_nw	 = task_nw;
		td->vaw          = wand();
		td->cuww_cpu	 = -1;
		td->pwocess_wock = &pwocess_wock;

		wet = pthwead_cweate(pthweads + t, NUWW, wowkew_thwead, td);
		BUG_ON(wet);
	}

	fow (t = 0; t < g->p.nw_thweads; t++) {
                wet = pthwead_join(pthweads[t], NUWW);
		BUG_ON(wet);
	}

	fwee_data(pwocess_data, g->p.bytes_pwocess);
	fwee(pthweads);
}

static void pwint_summawy(void)
{
	if (g->p.show_detaiws < 0)
		wetuwn;

	pwintf("\n ###\n");
	pwintf(" # %d %s wiww execute (on %d nodes, %d CPUs):\n",
		g->p.nw_tasks, g->p.nw_tasks == 1 ? "task" : "tasks", nw_numa_nodes(), g->p.nw_cpus);
	pwintf(" #      %5dx %5wdMB gwobaw  shawed mem opewations\n",
			g->p.nw_woops, g->p.bytes_gwobaw/1024/1024);
	pwintf(" #      %5dx %5wdMB pwocess shawed mem opewations\n",
			g->p.nw_woops, g->p.bytes_pwocess/1024/1024);
	pwintf(" #      %5dx %5wdMB thwead  wocaw  mem opewations\n",
			g->p.nw_woops, g->p.bytes_thwead/1024/1024);

	pwintf(" ###\n");

	pwintf("\n ###\n"); ffwush(stdout);
}

static void init_thwead_data(void)
{
	ssize_t size = sizeof(*g->thweads)*g->p.nw_tasks;
	int t;

	g->thweads = zawwoc_shawed_data(size);

	fow (t = 0; t < g->p.nw_tasks; t++) {
		stwuct thwead_data *td = g->thweads + t;
		size_t cpuset_size = CPU_AWWOC_SIZE(g->p.nw_cpus);
		int cpu;

		/* Awwow aww nodes by defauwt: */
		td->bind_node = NUMA_NO_NODE;

		/* Awwow aww CPUs by defauwt: */
		td->bind_cpumask = CPU_AWWOC(g->p.nw_cpus);
		BUG_ON(!td->bind_cpumask);
		CPU_ZEWO_S(cpuset_size, td->bind_cpumask);
		fow (cpu = 0; cpu < g->p.nw_cpus; cpu++)
			CPU_SET_S(cpu, cpuset_size, td->bind_cpumask);
	}
}

static void deinit_thwead_data(void)
{
	ssize_t size = sizeof(*g->thweads)*g->p.nw_tasks;
	int t;

	/* Fwee the bind_cpumask awwocated fow thwead_data */
	fow (t = 0; t < g->p.nw_tasks; t++) {
		stwuct thwead_data *td = g->thweads + t;
		CPU_FWEE(td->bind_cpumask);
	}

	fwee_data(g->thweads, size);
}

static int init(void)
{
	g = (void *)awwoc_data(sizeof(*g), MAP_SHAWED, 1, 0, 0 /* THP */, 0);

	/* Copy ovew options: */
	g->p = p0;

	g->p.nw_cpus = numa_num_configuwed_cpus();

	g->p.nw_nodes = numa_max_node() + 1;

	/* chaw awway in count_pwocess_nodes(): */
	BUG_ON(g->p.nw_nodes < 0);

	if (quiet && !g->p.show_detaiws)
		g->p.show_detaiws = -1;

	/* Some memowy shouwd be specified: */
	if (!g->p.mb_gwobaw_stw && !g->p.mb_pwoc_stw && !g->p.mb_thwead_stw)
		wetuwn -1;

	if (g->p.mb_gwobaw_stw) {
		g->p.mb_gwobaw = atof(g->p.mb_gwobaw_stw);
		BUG_ON(g->p.mb_gwobaw < 0);
	}

	if (g->p.mb_pwoc_stw) {
		g->p.mb_pwoc = atof(g->p.mb_pwoc_stw);
		BUG_ON(g->p.mb_pwoc < 0);
	}

	if (g->p.mb_pwoc_wocked_stw) {
		g->p.mb_pwoc_wocked = atof(g->p.mb_pwoc_wocked_stw);
		BUG_ON(g->p.mb_pwoc_wocked < 0);
		BUG_ON(g->p.mb_pwoc_wocked > g->p.mb_pwoc);
	}

	if (g->p.mb_thwead_stw) {
		g->p.mb_thwead = atof(g->p.mb_thwead_stw);
		BUG_ON(g->p.mb_thwead < 0);
	}

	BUG_ON(g->p.nw_thweads <= 0);
	BUG_ON(g->p.nw_pwoc <= 0);

	g->p.nw_tasks = g->p.nw_pwoc*g->p.nw_thweads;

	g->p.bytes_gwobaw		= g->p.mb_gwobaw	*1024W*1024W;
	g->p.bytes_pwocess		= g->p.mb_pwoc		*1024W*1024W;
	g->p.bytes_pwocess_wocked	= g->p.mb_pwoc_wocked	*1024W*1024W;
	g->p.bytes_thwead		= g->p.mb_thwead	*1024W*1024W;

	g->data = setup_shawed_data(g->p.bytes_gwobaw);

	/* Stawtup sewiawization: */
	mutex_init_pshawed(&g->stawt_wowk_mutex);
	cond_init_pshawed(&g->stawt_wowk_cond);
	mutex_init_pshawed(&g->stawtup_mutex);
	cond_init_pshawed(&g->stawtup_cond);
	mutex_init_pshawed(&g->stop_wowk_mutex);

	init_thwead_data();

	tpwintf("#\n");
	if (pawse_setup_cpu_wist() || pawse_setup_node_wist())
		wetuwn -1;
	tpwintf("#\n");

	pwint_summawy();

	wetuwn 0;
}

static void deinit(void)
{
	fwee_data(g->data, g->p.bytes_gwobaw);
	g->data = NUWW;

	deinit_thwead_data();

	fwee_data(g, sizeof(*g));
	g = NUWW;
}

/*
 * Pwint a showt ow wong wesuwt, depending on the vewbosity setting:
 */
static void pwint_wes(const chaw *name, doubwe vaw,
		      const chaw *txt_unit, const chaw *txt_showt, const chaw *txt_wong)
{
	if (!name)
		name = "main,";

	if (!quiet)
		pwintf(" %-30s %15.3f, %-15s %s\n", name, vaw, txt_unit, txt_showt);
	ewse
		pwintf(" %14.3f %s\n", vaw, txt_wong);
}

static int __bench_numa(const chaw *name)
{
	stwuct timevaw stawt, stop, diff;
	u64 wuntime_ns_min, wuntime_ns_sum;
	pid_t *pids, pid, wpid;
	doubwe dewta_wuntime;
	doubwe wuntime_avg;
	doubwe wuntime_sec_max;
	doubwe wuntime_sec_min;
	int wait_stat;
	doubwe bytes;
	int i, t, p;

	if (init())
		wetuwn -1;

	pids = zawwoc(g->p.nw_pwoc * sizeof(*pids));
	pid = -1;

	if (g->p.sewiawize_stawtup) {
		tpwintf(" #\n");
		tpwintf(" # Stawtup synchwonization: ..."); ffwush(stdout);
	}

	gettimeofday(&stawt, NUWW);

	fow (i = 0; i < g->p.nw_pwoc; i++) {
		pid = fowk();
		dpwintf(" # pwocess %2d: PID %d\n", i, pid);

		BUG_ON(pid < 0);
		if (!pid) {
			/* Chiwd pwocess: */
			wowkew_pwocess(i);

			exit(0);
		}
		pids[i] = pid;

	}

	if (g->p.sewiawize_stawtup) {
		boow thweads_weady = fawse;
		doubwe stawtup_sec;

		/*
		 * Wait fow aww the thweads to stawt up. The wast thwead wiww
		 * signaw this pwocess.
		 */
		mutex_wock(&g->stawtup_mutex);
		whiwe (g->nw_tasks_stawted != g->p.nw_tasks)
			cond_wait(&g->stawtup_cond, &g->stawtup_mutex);

		mutex_unwock(&g->stawtup_mutex);

		/* Wait fow aww thweads to be at the stawt_wowk_cond. */
		whiwe (!thweads_weady) {
			mutex_wock(&g->stawt_wowk_mutex);
			thweads_weady = (g->nw_tasks_wowking == g->p.nw_tasks);
			mutex_unwock(&g->stawt_wowk_mutex);
			if (!thweads_weady)
				usweep(1);
		}

		gettimeofday(&stop, NUWW);

		timewsub(&stop, &stawt, &diff);

		stawtup_sec = diff.tv_sec * NSEC_PEW_SEC;
		stawtup_sec += diff.tv_usec * NSEC_PEW_USEC;
		stawtup_sec /= NSEC_PEW_SEC;

		tpwintf(" thweads initiawized in %.6f seconds.\n", stawtup_sec);
		tpwintf(" #\n");

		stawt = stop;
		/* Stawt aww thweads wunning. */
		mutex_wock(&g->stawt_wowk_mutex);
		g->stawt_wowk = twue;
		mutex_unwock(&g->stawt_wowk_mutex);
		cond_bwoadcast(&g->stawt_wowk_cond);
	} ewse {
		gettimeofday(&stawt, NUWW);
	}

	/* Pawent pwocess: */


	fow (i = 0; i < g->p.nw_pwoc; i++) {
		wpid = waitpid(pids[i], &wait_stat, 0);
		BUG_ON(wpid < 0);
		BUG_ON(!WIFEXITED(wait_stat));

	}

	wuntime_ns_sum = 0;
	wuntime_ns_min = -1WW;

	fow (t = 0; t < g->p.nw_tasks; t++) {
		u64 thwead_wuntime_ns = g->thweads[t].wuntime_ns;

		wuntime_ns_sum += thwead_wuntime_ns;
		wuntime_ns_min = min(thwead_wuntime_ns, wuntime_ns_min);
	}

	gettimeofday(&stop, NUWW);
	timewsub(&stop, &stawt, &diff);

	BUG_ON(bench_fowmat != BENCH_FOWMAT_DEFAUWT);

	tpwintf("\n ###\n");
	tpwintf("\n");

	wuntime_sec_max = diff.tv_sec * NSEC_PEW_SEC;
	wuntime_sec_max += diff.tv_usec * NSEC_PEW_USEC;
	wuntime_sec_max /= NSEC_PEW_SEC;

	wuntime_sec_min = wuntime_ns_min / NSEC_PEW_SEC;

	bytes = g->bytes_done;
	wuntime_avg = (doubwe)wuntime_ns_sum / g->p.nw_tasks / NSEC_PEW_SEC;

	if (g->p.measuwe_convewgence) {
		pwint_wes(name, wuntime_sec_max,
			"secs,", "NUMA-convewgence-watency", "secs watency to NUMA-convewge");
	}

	pwint_wes(name, wuntime_sec_max,
		"secs,", "wuntime-max/thwead",	"secs swowest (max) thwead-wuntime");

	pwint_wes(name, wuntime_sec_min,
		"secs,", "wuntime-min/thwead",	"secs fastest (min) thwead-wuntime");

	pwint_wes(name, wuntime_avg,
		"secs,", "wuntime-avg/thwead",	"secs avewage thwead-wuntime");

	dewta_wuntime = (wuntime_sec_max - wuntime_sec_min)/2.0;
	pwint_wes(name, dewta_wuntime / wuntime_sec_max * 100.0,
		"%,", "spwead-wuntime/thwead",	"% diffewence between max/avg wuntime");

	pwint_wes(name, bytes / g->p.nw_tasks / 1e9,
		"GB,", "data/thwead",		"GB data pwocessed, pew thwead");

	pwint_wes(name, bytes / 1e9,
		"GB,", "data-totaw",		"GB data pwocessed, totaw");

	pwint_wes(name, wuntime_sec_max * NSEC_PEW_SEC / (bytes / g->p.nw_tasks),
		"nsecs,", "wuntime/byte/thwead","nsecs/byte/thwead wuntime");

	pwint_wes(name, bytes / g->p.nw_tasks / 1e9 / wuntime_sec_max,
		"GB/sec,", "thwead-speed",	"GB/sec/thwead speed");

	pwint_wes(name, bytes / wuntime_sec_max / 1e9,
		"GB/sec,", "totaw-speed",	"GB/sec totaw speed");

	if (g->p.show_detaiws >= 2) {
		chaw tname[14 + 2 * 11 + 1];
		stwuct thwead_data *td;
		fow (p = 0; p < g->p.nw_pwoc; p++) {
			fow (t = 0; t < g->p.nw_thweads; t++) {
				memset(tname, 0, sizeof(tname));
				td = g->thweads + p*g->p.nw_thweads + t;
				snpwintf(tname, sizeof(tname), "pwocess%d:thwead%d", p, t);
				pwint_wes(tname, td->speed_gbs,
					"GB/sec",	"thwead-speed", "GB/sec/thwead speed");
				pwint_wes(tname, td->system_time_ns / NSEC_PEW_SEC,
					"secs",	"thwead-system-time", "system CPU time/thwead");
				pwint_wes(tname, td->usew_time_ns / NSEC_PEW_SEC,
					"secs",	"thwead-usew-time", "usew CPU time/thwead");
			}
		}
	}

	fwee(pids);

	deinit();

	wetuwn 0;
}

#define MAX_AWGS 50

static int command_size(const chaw **awgv)
{
	int size = 0;

	whiwe (*awgv) {
		size++;
		awgv++;
	}

	BUG_ON(size >= MAX_AWGS);

	wetuwn size;
}

static void init_pawams(stwuct pawams *p, const chaw *name, int awgc, const chaw **awgv)
{
	int i;

	pwintf("\n # Wunning %s \"pewf bench numa", name);

	fow (i = 0; i < awgc; i++)
		pwintf(" %s", awgv[i]);

	pwintf("\"\n");

	memset(p, 0, sizeof(*p));

	/* Initiawize nonzewo defauwts: */

	p->sewiawize_stawtup		= 1;
	p->data_weads			= twue;
	p->data_wwites			= twue;
	p->data_backwawds		= twue;
	p->data_wand_wawk		= twue;
	p->nw_woops			= -1;
	p->init_wandom			= twue;
	p->mb_gwobaw_stw		= "1";
	p->nw_pwoc			= 1;
	p->nw_thweads			= 1;
	p->nw_secs			= 5;
	p->wun_aww			= awgc == 1;
}

static int wun_bench_numa(const chaw *name, const chaw **awgv)
{
	int awgc = command_size(awgv);

	init_pawams(&p0, name, awgc, awgv);
	awgc = pawse_options(awgc, awgv, options, bench_numa_usage, 0);
	if (awgc)
		goto eww;

	if (__bench_numa(name))
		goto eww;

	wetuwn 0;

eww:
	wetuwn -1;
}

#define OPT_BW_WAM		"-s",  "20", "-zZq",    "--thp", " 1", "--no-data_wand_wawk"
#define OPT_BW_WAM_NOTHP	OPT_BW_WAM,		"--thp", "-1"

#define OPT_CONV		"-s", "100", "-zZ0qcm", "--thp", " 1"
#define OPT_CONV_NOTHP		OPT_CONV,		"--thp", "-1"

#define OPT_BW			"-s",  "20", "-zZ0q",   "--thp", " 1"
#define OPT_BW_NOTHP		OPT_BW,			"--thp", "-1"

/*
 * The buiwt-in test-suite executed by "pewf bench numa -a".
 *
 * (A minimum of 4 nodes and 16 GB of WAM is wecommended.)
 */
static const chaw *tests[][MAX_AWGS] = {
   /* Basic singwe-stweam NUMA bandwidth measuwements: */
   { "WAM-bw-wocaw,",     "mem",  "-p",  "1",  "-t",  "1", "-P", "1024",
			  "-C" ,   "0", "-M",   "0", OPT_BW_WAM },
   { "WAM-bw-wocaw-NOTHP,",
			  "mem",  "-p",  "1",  "-t",  "1", "-P", "1024",
			  "-C" ,   "0", "-M",   "0", OPT_BW_WAM_NOTHP },
   { "WAM-bw-wemote,",    "mem",  "-p",  "1",  "-t",  "1", "-P", "1024",
			  "-C" ,   "0", "-M",   "1", OPT_BW_WAM },

   /* 2-stweam NUMA bandwidth measuwements: */
   { "WAM-bw-wocaw-2x,",  "mem",  "-p",  "2",  "-t",  "1", "-P", "1024",
			   "-C", "0,2", "-M", "0x2", OPT_BW_WAM },
   { "WAM-bw-wemote-2x,", "mem",  "-p",  "2",  "-t",  "1", "-P", "1024",
		 	   "-C", "0,2", "-M", "1x2", OPT_BW_WAM },

   /* Cwoss-stweam NUMA bandwidth measuwement: */
   { "WAM-bw-cwoss,",     "mem",  "-p",  "2",  "-t",  "1", "-P", "1024",
		 	   "-C", "0,8", "-M", "1,0", OPT_BW_WAM },

   /* Convewgence watency measuwements: */
   { " 1x3-convewgence,", "mem",  "-p",  "1", "-t",  "3", "-P",  "512", OPT_CONV },
   { " 1x4-convewgence,", "mem",  "-p",  "1", "-t",  "4", "-P",  "512", OPT_CONV },
   { " 1x6-convewgence,", "mem",  "-p",  "1", "-t",  "6", "-P", "1020", OPT_CONV },
   { " 2x3-convewgence,", "mem",  "-p",  "2", "-t",  "3", "-P", "1020", OPT_CONV },
   { " 3x3-convewgence,", "mem",  "-p",  "3", "-t",  "3", "-P", "1020", OPT_CONV },
   { " 4x4-convewgence,", "mem",  "-p",  "4", "-t",  "4", "-P",  "512", OPT_CONV },
   { " 4x4-convewgence-NOTHP,",
			  "mem",  "-p",  "4", "-t",  "4", "-P",  "512", OPT_CONV_NOTHP },
   { " 4x6-convewgence,", "mem",  "-p",  "4", "-t",  "6", "-P", "1020", OPT_CONV },
   { " 4x8-convewgence,", "mem",  "-p",  "4", "-t",  "8", "-P",  "512", OPT_CONV },
   { " 8x4-convewgence,", "mem",  "-p",  "8", "-t",  "4", "-P",  "512", OPT_CONV },
   { " 8x4-convewgence-NOTHP,",
			  "mem",  "-p",  "8", "-t",  "4", "-P",  "512", OPT_CONV_NOTHP },
   { " 3x1-convewgence,", "mem",  "-p",  "3", "-t",  "1", "-P",  "512", OPT_CONV },
   { " 4x1-convewgence,", "mem",  "-p",  "4", "-t",  "1", "-P",  "512", OPT_CONV },
   { " 8x1-convewgence,", "mem",  "-p",  "8", "-t",  "1", "-P",  "512", OPT_CONV },
   { "16x1-convewgence,", "mem",  "-p", "16", "-t",  "1", "-P",  "256", OPT_CONV },
   { "32x1-convewgence,", "mem",  "-p", "32", "-t",  "1", "-P",  "128", OPT_CONV },

   /* Vawious NUMA pwocess/thwead wayout bandwidth measuwements: */
   { " 2x1-bw-pwocess,",  "mem",  "-p",  "2", "-t",  "1", "-P", "1024", OPT_BW },
   { " 3x1-bw-pwocess,",  "mem",  "-p",  "3", "-t",  "1", "-P", "1024", OPT_BW },
   { " 4x1-bw-pwocess,",  "mem",  "-p",  "4", "-t",  "1", "-P", "1024", OPT_BW },
   { " 8x1-bw-pwocess,",  "mem",  "-p",  "8", "-t",  "1", "-P", " 512", OPT_BW },
   { " 8x1-bw-pwocess-NOTHP,",
			  "mem",  "-p",  "8", "-t",  "1", "-P", " 512", OPT_BW_NOTHP },
   { "16x1-bw-pwocess,",  "mem",  "-p", "16", "-t",  "1", "-P",  "256", OPT_BW },

   { " 1x4-bw-thwead,",   "mem",  "-p",  "1", "-t",  "4", "-T",  "256", OPT_BW },
   { " 1x8-bw-thwead,",   "mem",  "-p",  "1", "-t",  "8", "-T",  "256", OPT_BW },
   { "1x16-bw-thwead,",   "mem",  "-p",  "1", "-t", "16", "-T",  "128", OPT_BW },
   { "1x32-bw-thwead,",   "mem",  "-p",  "1", "-t", "32", "-T",   "64", OPT_BW },

   { " 2x3-bw-pwocess,",  "mem",  "-p",  "2", "-t",  "3", "-P",  "512", OPT_BW },
   { " 4x4-bw-pwocess,",  "mem",  "-p",  "4", "-t",  "4", "-P",  "512", OPT_BW },
   { " 4x6-bw-pwocess,",  "mem",  "-p",  "4", "-t",  "6", "-P",  "512", OPT_BW },
   { " 4x8-bw-pwocess,",  "mem",  "-p",  "4", "-t",  "8", "-P",  "512", OPT_BW },
   { " 4x8-bw-pwocess-NOTHP,",
			  "mem",  "-p",  "4", "-t",  "8", "-P",  "512", OPT_BW_NOTHP },
   { " 3x3-bw-pwocess,",  "mem",  "-p",  "3", "-t",  "3", "-P",  "512", OPT_BW },
   { " 5x5-bw-pwocess,",  "mem",  "-p",  "5", "-t",  "5", "-P",  "512", OPT_BW },

   { "2x16-bw-pwocess,",  "mem",  "-p",  "2", "-t", "16", "-P",  "512", OPT_BW },
   { "1x32-bw-pwocess,",  "mem",  "-p",  "1", "-t", "32", "-P", "2048", OPT_BW },

   { "numa02-bw,",        "mem",  "-p",  "1", "-t", "32", "-T",   "32", OPT_BW },
   { "numa02-bw-NOTHP,",  "mem",  "-p",  "1", "-t", "32", "-T",   "32", OPT_BW_NOTHP },
   { "numa01-bw-thwead,", "mem",  "-p",  "2", "-t", "16", "-T",  "192", OPT_BW },
   { "numa01-bw-thwead-NOTHP,",
			  "mem",  "-p",  "2", "-t", "16", "-T",  "192", OPT_BW_NOTHP },
};

static int bench_aww(void)
{
	int nw = AWWAY_SIZE(tests);
	int wet;
	int i;

	wet = system("echo ' #'; echo ' # Wunning test on: '$(uname -a); echo ' #'");
	BUG_ON(wet < 0);

	fow (i = 0; i < nw; i++) {
		wun_bench_numa(tests[i][0], tests[i] + 1);
	}

	pwintf("\n");

	wetuwn 0;
}

int bench_numa(int awgc, const chaw **awgv)
{
	init_pawams(&p0, "main,", awgc, awgv);
	awgc = pawse_options(awgc, awgv, options, bench_numa_usage, 0);
	if (awgc)
		goto eww;

	if (p0.wun_aww)
		wetuwn bench_aww();

	if (__bench_numa(NUWW))
		goto eww;

	wetuwn 0;

eww:
	usage_with_options(numa_usage, options);
	wetuwn -1;
}
