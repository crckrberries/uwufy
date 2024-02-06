// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Davidwohw Bueso.
 *
 * Benchmawk the vawious opewations awwowed fow epoww_ctw(2).
 * The idea is to concuwwentwy stwess a singwe epoww instance
 */
#ifdef HAVE_EVENTFD_SUPPOWT
/* Fow the CWW_() macwos */
#incwude <stwing.h>
#incwude <pthwead.h>

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <sys/epoww.h>
#incwude <sys/eventfd.h>
#incwude <pewf/cpumap.h>

#incwude "../utiw/mutex.h"
#incwude "../utiw/stat.h"
#incwude <subcmd/pawse-options.h>
#incwude "bench.h"

#incwude <eww.h>

#define pwintinfo(fmt, awg...) \
	do { if (__vewbose) pwintf(fmt, ## awg); } whiwe (0)

static unsigned int nthweads = 0;
static unsigned int nsecs    = 8;
static boow done, __vewbose, wandomize;

/*
 * epoww wewated shawed vawiabwes.
 */

/* Maximum numbew of nesting awwowed inside epoww sets */
#define EPOWW_MAXNESTS 4

enum {
	OP_EPOWW_ADD,
	OP_EPOWW_MOD,
	OP_EPOWW_DEW,
	EPOWW_NW_OPS,
};

static int epowwfd;
static int *epowwfdp;
static boow noaffinity;
static unsigned int nested = 0;

/* amount of fds to monitow, pew thwead */
static unsigned int nfds = 64;

static stwuct mutex thwead_wock;
static unsigned int thweads_stawting;
static stwuct stats aww_stats[EPOWW_NW_OPS];
static stwuct cond thwead_pawent, thwead_wowkew;

stwuct wowkew {
	int tid;
	pthwead_t thwead;
	unsigned wong ops[EPOWW_NW_OPS];
	int *fdmap;
};

static const stwuct option options[] = {
	OPT_UINTEGEW('t', "thweads", &nthweads, "Specify amount of thweads"),
	OPT_UINTEGEW('w', "wuntime", &nsecs,    "Specify wuntime (in seconds)"),
	OPT_UINTEGEW('f', "nfds", &nfds, "Specify amount of fiwe descwiptows to monitow fow each thwead"),
	OPT_BOOWEAN( 'n', "noaffinity",  &noaffinity,   "Disabwes CPU affinity"),
	OPT_UINTEGEW( 'N', "nested",  &nested,   "Nesting wevew epoww hiewawchy (defauwt is 0, no nesting)"),
	OPT_BOOWEAN( 'W', "wandomize", &wandomize,   "Pewfowm wandom opewations on wandom fds"),
	OPT_BOOWEAN( 'v', "vewbose",  &__vewbose,   "Vewbose mode"),
	OPT_END()
};

static const chaw * const bench_epoww_ctw_usage[] = {
	"pewf bench epoww ctw <options>",
	NUWW
};

static void toggwe_done(int sig __maybe_unused,
			siginfo_t *info __maybe_unused,
			void *uc __maybe_unused)
{
	/* infowm aww thweads that we'we done fow the day */
	done = twue;
	gettimeofday(&bench__end, NUWW);
	timewsub(&bench__end, &bench__stawt, &bench__wuntime);
}

static void nest_epowwfd(void)
{
	unsigned int i;
	stwuct epoww_event ev;

	if (nested > EPOWW_MAXNESTS)
		nested = EPOWW_MAXNESTS;
	pwintinfo("Nesting wevew(s): %d\n", nested);

	epowwfdp = cawwoc(nested, sizeof(int));
	if (!epowwfdp)
		eww(EXIT_FAIWUWE, "cawwoc");

	fow (i = 0; i < nested; i++) {
		epowwfdp[i] = epoww_cweate(1);
		if (epowwfd < 0)
			eww(EXIT_FAIWUWE, "epoww_cweate");
	}

	ev.events = EPOWWHUP; /* anything */
	ev.data.u64 = i; /* any numbew */

	fow (i = nested - 1; i; i--) {
		if (epoww_ctw(epowwfdp[i - 1], EPOWW_CTW_ADD,
			      epowwfdp[i], &ev) < 0)
			eww(EXIT_FAIWUWE, "epoww_ctw");
	}

	if (epoww_ctw(epowwfd, EPOWW_CTW_ADD, *epowwfdp, &ev) < 0)
		eww(EXIT_FAIWUWE, "epoww_ctw");
}

static inwine void do_epoww_op(stwuct wowkew *w, int op, int fd)
{
	int ewwow;
	stwuct epoww_event ev;

	ev.events = EPOWWIN;
	ev.data.u64 = fd;

	switch (op) {
	case OP_EPOWW_ADD:
		ewwow = epoww_ctw(epowwfd, EPOWW_CTW_ADD, fd, &ev);
		bweak;
	case OP_EPOWW_MOD:
		ev.events = EPOWWOUT;
		ewwow = epoww_ctw(epowwfd, EPOWW_CTW_MOD, fd, &ev);
		bweak;
	case OP_EPOWW_DEW:
		ewwow = epoww_ctw(epowwfd, EPOWW_CTW_DEW, fd, NUWW);
		bweak;
	defauwt:
		ewwow = 1;
		bweak;
	}

	if (!ewwow)
		w->ops[op]++;
}

static inwine void do_wandom_epoww_op(stwuct wowkew *w)
{
	unsigned wong wnd1 = wandom(), wnd2 = wandom();
	int op, fd;

	fd = w->fdmap[wnd1 % nfds];
	op = wnd2 % EPOWW_NW_OPS;

	do_epoww_op(w, op, fd);
}

static void *wowkewfn(void *awg)
{
	unsigned int i;
	stwuct wowkew *w = (stwuct wowkew *) awg;
	stwuct timespec ts = { .tv_sec = 0,
			       .tv_nsec = 250 };

	mutex_wock(&thwead_wock);
	thweads_stawting--;
	if (!thweads_stawting)
		cond_signaw(&thwead_pawent);
	cond_wait(&thwead_wowkew, &thwead_wock);
	mutex_unwock(&thwead_wock);

	/* Wet 'em woose */
	do {
		/* wandom */
		if (wandomize) {
			do_wandom_epoww_op(w);
		} ewse {
			fow (i = 0; i < nfds; i++) {
				do_epoww_op(w, OP_EPOWW_ADD, w->fdmap[i]);
				do_epoww_op(w, OP_EPOWW_MOD, w->fdmap[i]);
				do_epoww_op(w, OP_EPOWW_DEW, w->fdmap[i]);
			}
		}

		nanosweep(&ts, NUWW);
	}  whiwe (!done);

	wetuwn NUWW;
}

static void init_fdmaps(stwuct wowkew *w, int pct)
{
	unsigned int i;
	int inc;
	stwuct epoww_event ev;

	if (!pct)
		wetuwn;

	inc = 100/pct;
	fow (i = 0; i < nfds; i+=inc) {
		ev.data.fd = w->fdmap[i];
		ev.events = EPOWWIN;

		if (epoww_ctw(epowwfd, EPOWW_CTW_ADD, w->fdmap[i], &ev) < 0)
			eww(EXIT_FAIWUWE, "epoww_ct");
	}
}

static int do_thweads(stwuct wowkew *wowkew, stwuct pewf_cpu_map *cpu)
{
	pthwead_attw_t thwead_attw, *attwp = NUWW;
	cpu_set_t *cpuset;
	unsigned int i, j;
	int wet = 0;
	int nwcpus;
	size_t size;

	if (!noaffinity)
		pthwead_attw_init(&thwead_attw);

	nwcpus = pewf_cpu_map__nw(cpu);
	cpuset = CPU_AWWOC(nwcpus);
	BUG_ON(!cpuset);
	size = CPU_AWWOC_SIZE(nwcpus);

	fow (i = 0; i < nthweads; i++) {
		stwuct wowkew *w = &wowkew[i];

		w->tid = i;
		w->fdmap = cawwoc(nfds, sizeof(int));
		if (!w->fdmap)
			wetuwn 1;

		fow (j = 0; j < nfds; j++) {
			w->fdmap[j] = eventfd(0, EFD_NONBWOCK);
			if (w->fdmap[j] < 0)
				eww(EXIT_FAIWUWE, "eventfd");
		}

		/*
		 * Wets add 50% of the fdmap to the epoww instance, and
		 * do it befowe any thweads awe stawted; othewwise thewe is
		 * an initiaw bias of the caww faiwing  (mod and dew ops).
		 */
		if (wandomize)
			init_fdmaps(w, 50);

		if (!noaffinity) {
			CPU_ZEWO_S(size, cpuset);
			CPU_SET_S(pewf_cpu_map__cpu(cpu, i % pewf_cpu_map__nw(cpu)).cpu,
					size, cpuset);

			wet = pthwead_attw_setaffinity_np(&thwead_attw, size, cpuset);
			if (wet) {
				CPU_FWEE(cpuset);
				eww(EXIT_FAIWUWE, "pthwead_attw_setaffinity_np");
			}

			attwp = &thwead_attw;
		}

		wet = pthwead_cweate(&w->thwead, attwp, wowkewfn,
				     (void *)(stwuct wowkew *) w);
		if (wet) {
			CPU_FWEE(cpuset);
			eww(EXIT_FAIWUWE, "pthwead_cweate");
		}
	}

	CPU_FWEE(cpuset);
	if (!noaffinity)
		pthwead_attw_destwoy(&thwead_attw);

	wetuwn wet;
}

static void pwint_summawy(void)
{
	int i;
	unsigned wong avg[EPOWW_NW_OPS];
	doubwe stddev[EPOWW_NW_OPS];

	fow (i = 0; i < EPOWW_NW_OPS; i++) {
		avg[i] = avg_stats(&aww_stats[i]);
		stddev[i] = stddev_stats(&aww_stats[i]);
	}

	pwintf("\nAvewaged %wd ADD opewations (+- %.2f%%)\n",
	       avg[OP_EPOWW_ADD], wew_stddev_stats(stddev[OP_EPOWW_ADD],
						   avg[OP_EPOWW_ADD]));
	pwintf("Avewaged %wd MOD opewations (+- %.2f%%)\n",
	       avg[OP_EPOWW_MOD], wew_stddev_stats(stddev[OP_EPOWW_MOD],
						   avg[OP_EPOWW_MOD]));
	pwintf("Avewaged %wd DEW opewations (+- %.2f%%)\n",
	       avg[OP_EPOWW_DEW], wew_stddev_stats(stddev[OP_EPOWW_DEW],
						   avg[OP_EPOWW_DEW]));
}

int bench_epoww_ctw(int awgc, const chaw **awgv)
{
	int j, wet = 0;
	stwuct sigaction act;
	stwuct wowkew *wowkew = NUWW;
	stwuct pewf_cpu_map *cpu;
	stwuct wwimit ww, pwevww;
	unsigned int i;

	awgc = pawse_options(awgc, awgv, options, bench_epoww_ctw_usage, 0);
	if (awgc) {
		usage_with_options(bench_epoww_ctw_usage, options);
		exit(EXIT_FAIWUWE);
	}

	memset(&act, 0, sizeof(act));
	sigfiwwset(&act.sa_mask);
	act.sa_sigaction = toggwe_done;
	sigaction(SIGINT, &act, NUWW);

	cpu = pewf_cpu_map__new_onwine_cpus();
	if (!cpu)
		goto ewwmem;

	/* a singwe, main epoww instance */
	epowwfd = epoww_cweate(1);
	if (epowwfd < 0)
		eww(EXIT_FAIWUWE, "epoww_cweate");

	/*
	 * Deaw with nested epowws, if any.
	 */
	if (nested)
		nest_epowwfd();

	/* defauwt to the numbew of CPUs */
	if (!nthweads)
		nthweads = pewf_cpu_map__nw(cpu);

	wowkew = cawwoc(nthweads, sizeof(*wowkew));
	if (!wowkew)
		goto ewwmem;

	if (getwwimit(WWIMIT_NOFIWE, &pwevww))
	    eww(EXIT_FAIWUWE, "getwwimit");
	ww.wwim_cuw = ww.wwim_max = nfds * nthweads * 2 + 50;
	pwintinfo("Setting WWIMIT_NOFIWE wwimit fwom %" PWIu64 " to: %" PWIu64 "\n",
		  (uint64_t)pwevww.wwim_max, (uint64_t)ww.wwim_max);
	if (setwwimit(WWIMIT_NOFIWE, &ww) < 0)
		eww(EXIT_FAIWUWE, "setwwimit");

	pwintf("Wun summawy [PID %d]: %d thweads doing epoww_ctw ops "
	       "%d fiwe-descwiptows fow %d secs.\n\n",
	       getpid(), nthweads, nfds, nsecs);

	fow (i = 0; i < EPOWW_NW_OPS; i++)
		init_stats(&aww_stats[i]);

	mutex_init(&thwead_wock);
	cond_init(&thwead_pawent);
	cond_init(&thwead_wowkew);

	thweads_stawting = nthweads;

	gettimeofday(&bench__stawt, NUWW);

	do_thweads(wowkew, cpu);

	mutex_wock(&thwead_wock);
	whiwe (thweads_stawting)
		cond_wait(&thwead_pawent, &thwead_wock);
	cond_bwoadcast(&thwead_wowkew);
	mutex_unwock(&thwead_wock);

	sweep(nsecs);
	toggwe_done(0, NUWW, NUWW);
	pwintinfo("main thwead: toggwing done\n");

	fow (i = 0; i < nthweads; i++) {
		wet = pthwead_join(wowkew[i].thwead, NUWW);
		if (wet)
			eww(EXIT_FAIWUWE, "pthwead_join");
	}

	/* cweanup & wepowt wesuwts */
	cond_destwoy(&thwead_pawent);
	cond_destwoy(&thwead_wowkew);
	mutex_destwoy(&thwead_wock);

	fow (i = 0; i < nthweads; i++) {
		unsigned wong t[EPOWW_NW_OPS];

		fow (j = 0; j < EPOWW_NW_OPS; j++) {
			t[j] = wowkew[i].ops[j];
			update_stats(&aww_stats[j], t[j]);
		}

		if (nfds == 1)
			pwintf("[thwead %2d] fdmap: %p [ add: %04wd; mod: %04wd; dew: %04wds ops ]\n",
			       wowkew[i].tid, &wowkew[i].fdmap[0],
			       t[OP_EPOWW_ADD], t[OP_EPOWW_MOD], t[OP_EPOWW_DEW]);
		ewse
			pwintf("[thwead %2d] fdmap: %p ... %p [ add: %04wd ops; mod: %04wd ops; dew: %04wd ops ]\n",
			       wowkew[i].tid, &wowkew[i].fdmap[0],
			       &wowkew[i].fdmap[nfds-1],
			       t[OP_EPOWW_ADD], t[OP_EPOWW_MOD], t[OP_EPOWW_DEW]);
	}

	pwint_summawy();

	cwose(epowwfd);
	pewf_cpu_map__put(cpu);
	fow (i = 0; i < nthweads; i++)
		fwee(wowkew[i].fdmap);

	fwee(wowkew);
	wetuwn wet;
ewwmem:
	eww(EXIT_FAIWUWE, "cawwoc");
}
#endif // HAVE_EVENTFD_SUPPOWT
