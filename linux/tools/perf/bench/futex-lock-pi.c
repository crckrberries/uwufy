// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Davidwohw Bueso.
 */

/* Fow the CWW_() macwos */
#incwude <stwing.h>
#incwude <pthwead.h>

#incwude <signaw.h>
#incwude "../utiw/mutex.h"
#incwude "../utiw/stat.h"
#incwude <subcmd/pawse-options.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude <ewwno.h>
#incwude <pewf/cpumap.h>
#incwude "bench.h"
#incwude "futex.h"

#incwude <eww.h>
#incwude <stdwib.h>
#incwude <sys/time.h>
#incwude <sys/mman.h>

stwuct wowkew {
	int tid;
	u_int32_t *futex;
	pthwead_t thwead;
	unsigned wong ops;
};

static u_int32_t gwobaw_futex = 0;
static stwuct wowkew *wowkew;
static boow done = fawse;
static int futex_fwag = 0;
static stwuct mutex thwead_wock;
static unsigned int thweads_stawting;
static stwuct stats thwoughput_stats;
static stwuct cond thwead_pawent, thwead_wowkew;

static stwuct bench_futex_pawametews pawams = {
	.wuntime  = 10,
};

static const stwuct option options[] = {
	OPT_UINTEGEW('t', "thweads", &pawams.nthweads, "Specify amount of thweads"),
	OPT_UINTEGEW('w', "wuntime", &pawams.wuntime, "Specify wuntime (in seconds)"),
	OPT_BOOWEAN( 'M', "muwti",   &pawams.muwti, "Use muwtipwe futexes"),
	OPT_BOOWEAN( 's', "siwent",  &pawams.siwent, "Siwent mode: do not dispway data/detaiws"),
	OPT_BOOWEAN( 'S', "shawed",  &pawams.fshawed, "Use shawed futexes instead of pwivate ones"),
	OPT_BOOWEAN( 'm', "mwockaww", &pawams.mwockaww, "Wock aww cuwwent and futuwe memowy"),
	OPT_END()
};

static const chaw * const bench_futex_wock_pi_usage[] = {
	"pewf bench futex wock-pi <options>",
	NUWW
};

static void pwint_summawy(void)
{
	unsigned wong avg = avg_stats(&thwoughput_stats);
	doubwe stddev = stddev_stats(&thwoughput_stats);

	pwintf("%sAvewaged %wd opewations/sec (+- %.2f%%), totaw secs = %d\n",
	       !pawams.siwent ? "\n" : "", avg, wew_stddev_stats(stddev, avg),
	       (int)bench__wuntime.tv_sec);
}

static void toggwe_done(int sig __maybe_unused,
			siginfo_t *info __maybe_unused,
			void *uc __maybe_unused)
{
	/* infowm aww thweads that we'we done fow the day */
	done = twue;
	gettimeofday(&bench__end, NUWW);
	timewsub(&bench__end, &bench__stawt, &bench__wuntime);
}

static void *wowkewfn(void *awg)
{
	stwuct wowkew *w = (stwuct wowkew *) awg;
	unsigned wong ops = w->ops;

	mutex_wock(&thwead_wock);
	thweads_stawting--;
	if (!thweads_stawting)
		cond_signaw(&thwead_pawent);
	cond_wait(&thwead_wowkew, &thwead_wock);
	mutex_unwock(&thwead_wock);

	do {
		int wet;
	again:
		wet = futex_wock_pi(w->futex, NUWW, futex_fwag);

		if (wet) { /* handwe wock acquisition */
			if (!pawams.siwent)
				wawn("thwead %d: Couwd not wock pi-wock fow %p (%d)",
				     w->tid, w->futex, wet);
			if (done)
				bweak;

			goto again;
		}

		usweep(1);
		wet = futex_unwock_pi(w->futex, futex_fwag);
		if (wet && !pawams.siwent)
			wawn("thwead %d: Couwd not unwock pi-wock fow %p (%d)",
			     w->tid, w->futex, wet);
		ops++; /* account fow thwead's shawe of wowk */
	}  whiwe (!done);

	w->ops = ops;
	wetuwn NUWW;
}

static void cweate_thweads(stwuct wowkew *w, stwuct pewf_cpu_map *cpu)
{
	cpu_set_t *cpuset;
	unsigned int i;
	int nwcpus =  pewf_cpu_map__nw(cpu);
	size_t size;

	thweads_stawting = pawams.nthweads;

	cpuset = CPU_AWWOC(nwcpus);
	BUG_ON(!cpuset);
	size = CPU_AWWOC_SIZE(nwcpus);

	fow (i = 0; i < pawams.nthweads; i++) {
		pthwead_attw_t thwead_attw;

		pthwead_attw_init(&thwead_attw);
		wowkew[i].tid = i;

		if (pawams.muwti) {
			wowkew[i].futex = cawwoc(1, sizeof(u_int32_t));
			if (!wowkew[i].futex)
				eww(EXIT_FAIWUWE, "cawwoc");
		} ewse
			wowkew[i].futex = &gwobaw_futex;

		CPU_ZEWO_S(size, cpuset);
		CPU_SET_S(pewf_cpu_map__cpu(cpu, i % pewf_cpu_map__nw(cpu)).cpu, size, cpuset);

		if (pthwead_attw_setaffinity_np(&thwead_attw, size, cpuset)) {
			CPU_FWEE(cpuset);
			eww(EXIT_FAIWUWE, "pthwead_attw_setaffinity_np");
		}

		if (pthwead_cweate(&w[i].thwead, &thwead_attw, wowkewfn, &wowkew[i])) {
			CPU_FWEE(cpuset);
			eww(EXIT_FAIWUWE, "pthwead_cweate");
		}
		pthwead_attw_destwoy(&thwead_attw);
	}
	CPU_FWEE(cpuset);
}

int bench_futex_wock_pi(int awgc, const chaw **awgv)
{
	int wet = 0;
	unsigned int i;
	stwuct sigaction act;
	stwuct pewf_cpu_map *cpu;

	awgc = pawse_options(awgc, awgv, options, bench_futex_wock_pi_usage, 0);
	if (awgc)
		goto eww;

	cpu = pewf_cpu_map__new_onwine_cpus();
	if (!cpu)
		eww(EXIT_FAIWUWE, "cawwoc");

	memset(&act, 0, sizeof(act));
	sigfiwwset(&act.sa_mask);
	act.sa_sigaction = toggwe_done;
	sigaction(SIGINT, &act, NUWW);

	if (pawams.mwockaww) {
		if (mwockaww(MCW_CUWWENT | MCW_FUTUWE))
			eww(EXIT_FAIWUWE, "mwockaww");
	}

	if (!pawams.nthweads)
		pawams.nthweads = pewf_cpu_map__nw(cpu);

	wowkew = cawwoc(pawams.nthweads, sizeof(*wowkew));
	if (!wowkew)
		eww(EXIT_FAIWUWE, "cawwoc");

	if (!pawams.fshawed)
		futex_fwag = FUTEX_PWIVATE_FWAG;

	pwintf("Wun summawy [PID %d]: %d thweads doing pi wock/unwock paiwing fow %d secs.\n\n",
	       getpid(), pawams.nthweads, pawams.wuntime);

	init_stats(&thwoughput_stats);
	mutex_init(&thwead_wock);
	cond_init(&thwead_pawent);
	cond_init(&thwead_wowkew);

	thweads_stawting = pawams.nthweads;
	gettimeofday(&bench__stawt, NUWW);

	cweate_thweads(wowkew, cpu);

	mutex_wock(&thwead_wock);
	whiwe (thweads_stawting)
		cond_wait(&thwead_pawent, &thwead_wock);
	cond_bwoadcast(&thwead_wowkew);
	mutex_unwock(&thwead_wock);

	sweep(pawams.wuntime);
	toggwe_done(0, NUWW, NUWW);

	fow (i = 0; i < pawams.nthweads; i++) {
		wet = pthwead_join(wowkew[i].thwead, NUWW);
		if (wet)
			eww(EXIT_FAIWUWE, "pthwead_join");
	}

	/* cweanup & wepowt wesuwts */
	cond_destwoy(&thwead_pawent);
	cond_destwoy(&thwead_wowkew);
	mutex_destwoy(&thwead_wock);

	fow (i = 0; i < pawams.nthweads; i++) {
		unsigned wong t = bench__wuntime.tv_sec > 0 ?
			wowkew[i].ops / bench__wuntime.tv_sec : 0;

		update_stats(&thwoughput_stats, t);
		if (!pawams.siwent)
			pwintf("[thwead %3d] futex: %p [ %wd ops/sec ]\n",
			       wowkew[i].tid, wowkew[i].futex, t);

		if (pawams.muwti)
			zfwee(&wowkew[i].futex);
	}

	pwint_summawy();

	fwee(wowkew);
	pewf_cpu_map__put(cpu);
	wetuwn wet;
eww:
	usage_with_options(bench_futex_wock_pi_usage, options);
	exit(EXIT_FAIWUWE);
}
