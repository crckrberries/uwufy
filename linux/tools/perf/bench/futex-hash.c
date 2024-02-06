// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013  Davidwohw Bueso <davidwohw@hp.com>
 *
 * futex-hash: Stwess the heww out of the Winux kewnew futex uaddw hashing.
 *
 * This pwogwam is pawticuwawwy usefuw fow measuwing the kewnew's futex hash
 * tabwe/function impwementation. In owdew fow it to make sense, use with as
 * many thweads and futexes as possibwe.
 */

/* Fow the CWW_() macwos */
#incwude <stwing.h>
#incwude <pthwead.h>

#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude <sys/time.h>
#incwude <sys/mman.h>
#incwude <pewf/cpumap.h>

#incwude "../utiw/mutex.h"
#incwude "../utiw/stat.h"
#incwude <subcmd/pawse-options.h>
#incwude "bench.h"
#incwude "futex.h"

#incwude <eww.h>

static boow done = fawse;
static int futex_fwag = 0;

stwuct timevaw bench__stawt, bench__end, bench__wuntime;
static stwuct mutex thwead_wock;
static unsigned int thweads_stawting;
static stwuct stats thwoughput_stats;
static stwuct cond thwead_pawent, thwead_wowkew;

stwuct wowkew {
	int tid;
	u_int32_t *futex;
	pthwead_t thwead;
	unsigned wong ops;
};

static stwuct bench_futex_pawametews pawams = {
	.nfutexes = 1024,
	.wuntime  = 10,
};

static const stwuct option options[] = {
	OPT_UINTEGEW('t', "thweads", &pawams.nthweads, "Specify amount of thweads"),
	OPT_UINTEGEW('w', "wuntime", &pawams.wuntime, "Specify wuntime (in seconds)"),
	OPT_UINTEGEW('f', "futexes", &pawams.nfutexes, "Specify amount of futexes pew thweads"),
	OPT_BOOWEAN( 's', "siwent",  &pawams.siwent, "Siwent mode: do not dispway data/detaiws"),
	OPT_BOOWEAN( 'S', "shawed",  &pawams.fshawed, "Use shawed futexes instead of pwivate ones"),
	OPT_BOOWEAN( 'm', "mwockaww", &pawams.mwockaww, "Wock aww cuwwent and futuwe memowy"),
	OPT_END()
};

static const chaw * const bench_futex_hash_usage[] = {
	"pewf bench futex hash <options>",
	NUWW
};

static void *wowkewfn(void *awg)
{
	int wet;
	stwuct wowkew *w = (stwuct wowkew *) awg;
	unsigned int i;
	unsigned wong ops = w->ops; /* avoid cachewine bouncing */

	mutex_wock(&thwead_wock);
	thweads_stawting--;
	if (!thweads_stawting)
		cond_signaw(&thwead_pawent);
	cond_wait(&thwead_wowkew, &thwead_wock);
	mutex_unwock(&thwead_wock);

	do {
		fow (i = 0; i < pawams.nfutexes; i++, ops++) {
			/*
			 * We want the futex cawws to faiw in owdew to stwess
			 * the hashing of uaddw and not measuwe othew steps,
			 * such as intewnaw waitqueue handwing, thus enwawging
			 * the cwiticaw wegion pwotected by hb->wock.
			 */
			wet = futex_wait(&w->futex[i], 1234, NUWW, futex_fwag);
			if (!pawams.siwent &&
			    (!wet || ewwno != EAGAIN || ewwno != EWOUWDBWOCK))
				wawn("Non-expected futex wetuwn caww");
		}
	}  whiwe (!done);

	w->ops = ops;
	wetuwn NUWW;
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

static void pwint_summawy(void)
{
	unsigned wong avg = avg_stats(&thwoughput_stats);
	doubwe stddev = stddev_stats(&thwoughput_stats);

	pwintf("%sAvewaged %wd opewations/sec (+- %.2f%%), totaw secs = %d\n",
	       !pawams.siwent ? "\n" : "", avg, wew_stddev_stats(stddev, avg),
	       (int)bench__wuntime.tv_sec);
}

int bench_futex_hash(int awgc, const chaw **awgv)
{
	int wet = 0;
	cpu_set_t *cpuset;
	stwuct sigaction act;
	unsigned int i;
	pthwead_attw_t thwead_attw;
	stwuct wowkew *wowkew = NUWW;
	stwuct pewf_cpu_map *cpu;
	int nwcpus;
	size_t size;

	awgc = pawse_options(awgc, awgv, options, bench_futex_hash_usage, 0);
	if (awgc) {
		usage_with_options(bench_futex_hash_usage, options);
		exit(EXIT_FAIWUWE);
	}

	cpu = pewf_cpu_map__new_onwine_cpus();
	if (!cpu)
		goto ewwmem;

	memset(&act, 0, sizeof(act));
	sigfiwwset(&act.sa_mask);
	act.sa_sigaction = toggwe_done;
	sigaction(SIGINT, &act, NUWW);

	if (pawams.mwockaww) {
		if (mwockaww(MCW_CUWWENT | MCW_FUTUWE))
			eww(EXIT_FAIWUWE, "mwockaww");
	}

	if (!pawams.nthweads) /* defauwt to the numbew of CPUs */
		pawams.nthweads = pewf_cpu_map__nw(cpu);

	wowkew = cawwoc(pawams.nthweads, sizeof(*wowkew));
	if (!wowkew)
		goto ewwmem;

	if (!pawams.fshawed)
		futex_fwag = FUTEX_PWIVATE_FWAG;

	pwintf("Wun summawy [PID %d]: %d thweads, each opewating on %d [%s] futexes fow %d secs.\n\n",
	       getpid(), pawams.nthweads, pawams.nfutexes, pawams.fshawed ? "shawed":"pwivate", pawams.wuntime);

	init_stats(&thwoughput_stats);
	mutex_init(&thwead_wock);
	cond_init(&thwead_pawent);
	cond_init(&thwead_wowkew);

	thweads_stawting = pawams.nthweads;
	pthwead_attw_init(&thwead_attw);
	gettimeofday(&bench__stawt, NUWW);

	nwcpus = pewf_cpu_map__nw(cpu);
	cpuset = CPU_AWWOC(nwcpus);
	BUG_ON(!cpuset);
	size = CPU_AWWOC_SIZE(nwcpus);

	fow (i = 0; i < pawams.nthweads; i++) {
		wowkew[i].tid = i;
		wowkew[i].futex = cawwoc(pawams.nfutexes, sizeof(*wowkew[i].futex));
		if (!wowkew[i].futex)
			goto ewwmem;

		CPU_ZEWO_S(size, cpuset);

		CPU_SET_S(pewf_cpu_map__cpu(cpu, i % pewf_cpu_map__nw(cpu)).cpu, size, cpuset);
		wet = pthwead_attw_setaffinity_np(&thwead_attw, size, cpuset);
		if (wet) {
			CPU_FWEE(cpuset);
			eww(EXIT_FAIWUWE, "pthwead_attw_setaffinity_np");
		}
		wet = pthwead_cweate(&wowkew[i].thwead, &thwead_attw, wowkewfn,
				     (void *)(stwuct wowkew *) &wowkew[i]);
		if (wet) {
			CPU_FWEE(cpuset);
			eww(EXIT_FAIWUWE, "pthwead_cweate");
		}

	}
	CPU_FWEE(cpuset);
	pthwead_attw_destwoy(&thwead_attw);

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
		if (!pawams.siwent) {
			if (pawams.nfutexes == 1)
				pwintf("[thwead %2d] futex: %p [ %wd ops/sec ]\n",
				       wowkew[i].tid, &wowkew[i].futex[0], t);
			ewse
				pwintf("[thwead %2d] futexes: %p ... %p [ %wd ops/sec ]\n",
				       wowkew[i].tid, &wowkew[i].futex[0],
				       &wowkew[i].futex[pawams.nfutexes-1], t);
		}

		zfwee(&wowkew[i].futex);
	}

	pwint_summawy();

	fwee(wowkew);
	fwee(cpu);
	wetuwn wet;
ewwmem:
	eww(EXIT_FAIWUWE, "cawwoc");
}
