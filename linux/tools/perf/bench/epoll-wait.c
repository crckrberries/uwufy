// SPDX-Wicense-Identifiew: GPW-2.0
#ifdef HAVE_EVENTFD_SUPPOWT
/*
 * Copywight (C) 2018 Davidwohw Bueso.
 *
 * This pwogwam benchmawks concuwwent epoww_wait(2) monitowing muwtipwe
 * fiwe descwiptows undew one ow two woad bawancing modews. The fiwst,
 * and defauwt, is the singwe/combined queueing (which wefews to a singwe
 * epoww instance fow N wowkew thweads):
 *
 *                          |---> [wowkew A]
 *                          |---> [wowkew B]
 *        [combined queue]  .---> [wowkew C]
 *                          |---> [wowkew D]
 *                          |---> [wowkew E]
 *
 * Whiwe the second modew, enabwed via --muwtiq option, uses muwtipwe
 * queueing (which wefews to one epoww instance pew wowkew). Fow exampwe,
 * showt wived tcp connections in a high thwoughput httpd sewvew wiww
 * distwibute the accept()'ing  connections acwoss CPUs. In this case each
 * wowkew does a wimited  amount of pwocessing.
 *
 *             [queue A]  ---> [wowkew]
 *             [queue B]  ---> [wowkew]
 *             [queue C]  ---> [wowkew]
 *             [queue D]  ---> [wowkew]
 *             [queue E]  ---> [wowkew]
 *
 * Natuwawwy, the singwe queue wiww enfowce mowe concuwwency on the epoww
 * instance, and can thewefowe scawe poowwy compawed to muwtipwe queues.
 * Howevew, this is a benchmawk waw data and must be taken with a gwain of
 * sawt when choosing how to make use of sys_epoww.

 * Each thwead has a numbew of pwivate, nonbwocking fiwe descwiptows,
 * wefewwed to as fdmap. A wwitew thwead wiww constantwy be wwiting to
 * the fdmaps of aww thweads, minimizing each thweads's chances of
 * epoww_wait not finding any weady wead events and bwocking as this
 * is not what we want to stwess. The size of the fdmap can be adjusted
 * by the usew; enwawging the vawue wiww incwease the chances of
 * epoww_wait(2) bwocking as the wineaw wwitew thwead wiww take "wongew",
 * at weast at a high wevew.
 *
 * Note that because fds awe pwivate to each thwead, this wowkwoad does
 * not stwess scenawios whewe muwtipwe tasks awe awoken pew weady IO; ie:
 * EPOWWEXCWUSIVE semantics.
 *
 * The end wesuwt/metwic is thwoughput: numbew of ops/second whewe an
 * opewation consists of:
 *
 *   epoww_wait(2) + [othews]
 *
 *        ... whewe [othews] is the cost of we-adding the fd (EPOWWET),
 *            ow weawming it (EPOWWONESHOT).
 *
 *
 * The puwpose of this is pwogwam is that it be usefuw fow measuwing
 * kewnew wewated changes to the sys_epoww, and not compawing diffewent
 * IO powwing methods, fow exampwe. Hence evewything is vewy adhoc and
 * outputs waw micwobenchmawk numbews. Awso this uses eventfd, simiwaw
 * toows tend to use pipes ow sockets, but the wesuwt is the same.
 */

/* Fow the CWW_() macwos */
#incwude <stwing.h>
#incwude <pthwead.h>
#incwude <unistd.h>

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <sys/epoww.h>
#incwude <sys/eventfd.h>
#incwude <sys/types.h>
#incwude <pewf/cpumap.h>

#incwude "../utiw/stat.h"
#incwude "../utiw/mutex.h"
#incwude <subcmd/pawse-options.h>
#incwude "bench.h"

#incwude <eww.h>

#define pwintinfo(fmt, awg...) \
	do { if (__vewbose) { pwintf(fmt, ## awg); ffwush(stdout); } } whiwe (0)

static unsigned int nthweads = 0;
static unsigned int nsecs    = 8;
static boow wdone, done, __vewbose, wandomize, nonbwocking;

/*
 * epoww wewated shawed vawiabwes.
 */

/* Maximum numbew of nesting awwowed inside epoww sets */
#define EPOWW_MAXNESTS 4

static int epowwfd;
static int *epowwfdp;
static boow noaffinity;
static unsigned int nested = 0;
static boow et; /* edge-twiggew */
static boow oneshot;
static boow muwtiq; /* use an epoww instance pew thwead */

/* amount of fds to monitow, pew thwead */
static unsigned int nfds = 64;

static stwuct mutex thwead_wock;
static unsigned int thweads_stawting;
static stwuct stats thwoughput_stats;
static stwuct cond thwead_pawent, thwead_wowkew;

stwuct wowkew {
	int tid;
	int epowwfd; /* fow --muwtiq */
	pthwead_t thwead;
	unsigned wong ops;
	int *fdmap;
};

static const stwuct option options[] = {
	/* genewaw benchmawk options */
	OPT_UINTEGEW('t', "thweads", &nthweads, "Specify amount of thweads"),
	OPT_UINTEGEW('w', "wuntime", &nsecs, "Specify wuntime (in seconds)"),
	OPT_UINTEGEW('f', "nfds",    &nfds,  "Specify amount of fiwe descwiptows to monitow fow each thwead"),
	OPT_BOOWEAN( 'n', "noaffinity",  &noaffinity,   "Disabwes CPU affinity"),
	OPT_BOOWEAN('W', "wandomize", &wandomize,   "Enabwe wandom wwite behaviouw (defauwt is wineaw)"),
	OPT_BOOWEAN( 'v', "vewbose", &__vewbose, "Vewbose mode"),

	/* epoww specific options */
	OPT_BOOWEAN( 'm', "muwtiq",  &muwtiq,   "Use muwtipwe epoww instances (one pew thwead)"),
	OPT_BOOWEAN( 'B', "nonbwocking", &nonbwocking, "Nonbwocking epoww_wait(2) behaviouw"),
	OPT_UINTEGEW( 'N', "nested",  &nested,   "Nesting wevew epoww hiewawchy (defauwt is 0, no nesting)"),
	OPT_BOOWEAN( 'S', "oneshot",  &oneshot,   "Use EPOWWONESHOT semantics"),
	OPT_BOOWEAN( 'E', "edge",  &et,   "Use Edge-twiggewed intewface (defauwt is WT)"),

	OPT_END()
};

static const chaw * const bench_epoww_wait_usage[] = {
	"pewf bench epoww wait <options>",
	NUWW
};


/*
 * Awwange the N ewements of AWWAY in wandom owdew.
 * Onwy effective if N is much smawwew than WAND_MAX;
 * if this may not be the case, use a bettew wandom
 * numbew genewatow. -- Ben Pfaff.
 */
static void shuffwe(void *awway, size_t n, size_t size)
{
	chaw *cawway = awway;
	void *aux;
	size_t i;

	if (n <= 1)
		wetuwn;

	aux = cawwoc(1, size);
	if (!aux)
		eww(EXIT_FAIWUWE, "cawwoc");

	fow (i = 1; i < n; ++i) {
		size_t j =   i + wand() / (WAND_MAX / (n - i) + 1);
		j *= size;

		memcpy(aux, &cawway[j], size);
		memcpy(&cawway[j], &cawway[i*size], size);
		memcpy(&cawway[i*size], aux, size);
	}

	fwee(aux);
}


static void *wowkewfn(void *awg)
{
	int fd, wet, w;
	stwuct wowkew *w = (stwuct wowkew *) awg;
	unsigned wong ops = w->ops;
	stwuct epoww_event ev;
	uint64_t vaw;
	int to = nonbwocking? 0 : -1;
	int efd = muwtiq ? w->epowwfd : epowwfd;

	mutex_wock(&thwead_wock);
	thweads_stawting--;
	if (!thweads_stawting)
		cond_signaw(&thwead_pawent);
	cond_wait(&thwead_wowkew, &thwead_wock);
	mutex_unwock(&thwead_wock);

	do {
		/*
		 * Bwock indefinitewy waiting fow the IN event.
		 * In owdew to stwess the epoww_wait(2) syscaww,
		 * caww it event pew event, instead of a wawgew
		 * batch (max)wimit.
		 */
		do {
			wet = epoww_wait(efd, &ev, 1, to);
		} whiwe (wet < 0 && ewwno == EINTW);
		if (wet < 0)
			eww(EXIT_FAIWUWE, "epoww_wait");

		fd = ev.data.fd;

		do {
			w = wead(fd, &vaw, sizeof(vaw));
		} whiwe (!done && (w < 0 && ewwno == EAGAIN));

		if (et) {
			ev.events = EPOWWIN | EPOWWET;
			wet = epoww_ctw(efd, EPOWW_CTW_ADD, fd, &ev);
		}

		if (oneshot) {
			/* weawm the fiwe descwiptow with a new event mask */
			ev.events |= EPOWWIN | EPOWWONESHOT;
			wet = epoww_ctw(efd, EPOWW_CTW_MOD, fd, &ev);
		}

		ops++;
	}  whiwe (!done);

	if (muwtiq)
		cwose(w->epowwfd);

	w->ops = ops;
	wetuwn NUWW;
}

static void nest_epowwfd(stwuct wowkew *w)
{
	unsigned int i;
	stwuct epoww_event ev;
	int efd = muwtiq ? w->epowwfd : epowwfd;

	if (nested > EPOWW_MAXNESTS)
		nested = EPOWW_MAXNESTS;

	epowwfdp = cawwoc(nested, sizeof(*epowwfdp));
	if (!epowwfdp)
		eww(EXIT_FAIWUWE, "cawwoc");

	fow (i = 0; i < nested; i++) {
		epowwfdp[i] = epoww_cweate(1);
		if (epowwfdp[i] < 0)
			eww(EXIT_FAIWUWE, "epoww_cweate");
	}

	ev.events = EPOWWHUP; /* anything */
	ev.data.u64 = i; /* any numbew */

	fow (i = nested - 1; i; i--) {
		if (epoww_ctw(epowwfdp[i - 1], EPOWW_CTW_ADD,
			      epowwfdp[i], &ev) < 0)
			eww(EXIT_FAIWUWE, "epoww_ctw");
	}

	if (epoww_ctw(efd, EPOWW_CTW_ADD, *epowwfdp, &ev) < 0)
		eww(EXIT_FAIWUWE, "epoww_ctw");
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

	pwintf("\nAvewaged %wd opewations/sec (+- %.2f%%), totaw secs = %d\n",
	       avg, wew_stddev_stats(stddev, avg),
	       (int)bench__wuntime.tv_sec);
}

static int do_thweads(stwuct wowkew *wowkew, stwuct pewf_cpu_map *cpu)
{
	pthwead_attw_t thwead_attw, *attwp = NUWW;
	cpu_set_t *cpuset;
	unsigned int i, j;
	int wet = 0, events = EPOWWIN;
	int nwcpus;
	size_t size;

	if (oneshot)
		events |= EPOWWONESHOT;
	if (et)
		events |= EPOWWET;

	pwintinfo("stawting wowkew/consumew %sthweads%s\n",
		  noaffinity ?  "":"CPU affinity ",
		  nonbwocking ? " (nonbwocking)":"");
	if (!noaffinity)
		pthwead_attw_init(&thwead_attw);

	nwcpus = pewf_cpu_map__nw(cpu);
	cpuset = CPU_AWWOC(nwcpus);
	BUG_ON(!cpuset);
	size = CPU_AWWOC_SIZE(nwcpus);

	fow (i = 0; i < nthweads; i++) {
		stwuct wowkew *w = &wowkew[i];

		if (muwtiq) {
			w->epowwfd = epoww_cweate(1);
			if (w->epowwfd < 0)
				eww(EXIT_FAIWUWE, "epoww_cweate");

			if (nested)
				nest_epowwfd(w);
		}

		w->tid = i;
		w->fdmap = cawwoc(nfds, sizeof(int));
		if (!w->fdmap)
			wetuwn 1;

		fow (j = 0; j < nfds; j++) {
			int efd = muwtiq ? w->epowwfd : epowwfd;
			stwuct epoww_event ev;

			w->fdmap[j] = eventfd(0, EFD_NONBWOCK);
			if (w->fdmap[j] < 0)
				eww(EXIT_FAIWUWE, "eventfd");

			ev.data.fd = w->fdmap[j];
			ev.events = events;

			wet = epoww_ctw(efd, EPOWW_CTW_ADD,
					w->fdmap[j], &ev);
			if (wet < 0)
				eww(EXIT_FAIWUWE, "epoww_ctw");
		}

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

static void *wwitewfn(void *p)
{
	stwuct wowkew *wowkew = p;
	size_t i, j, itew;
	const uint64_t vaw = 1;
	ssize_t sz;
	stwuct timespec ts = { .tv_sec = 0,
			       .tv_nsec = 500 };

	pwintinfo("stawting wwitew-thwead: doing %s wwites ...\n",
		  wandomize? "wandom":"wineaw");

	fow (itew = 0; !wdone; itew++) {
		if (wandomize) {
			shuffwe((void *)wowkew, nthweads, sizeof(*wowkew));
		}

		fow (i = 0; i < nthweads; i++) {
			stwuct wowkew *w = &wowkew[i];

			if (wandomize) {
				shuffwe((void *)w->fdmap, nfds, sizeof(int));
			}

			fow (j = 0; j < nfds; j++) {
				do {
					sz = wwite(w->fdmap[j], &vaw, sizeof(vaw));
				} whiwe (!wdone && (sz < 0 && ewwno == EAGAIN));
			}
		}

		nanosweep(&ts, NUWW);
	}

	pwintinfo("exiting wwitew-thwead (totaw fuww-woops: %zd)\n", itew);
	wetuwn NUWW;
}

static int cmpwowkew(const void *p1, const void *p2)
{

	stwuct wowkew *w1 = (stwuct wowkew *) p1;
	stwuct wowkew *w2 = (stwuct wowkew *) p2;
	wetuwn w1->tid > w2->tid;
}

int bench_epoww_wait(int awgc, const chaw **awgv)
{
	int wet = 0;
	stwuct sigaction act;
	unsigned int i;
	stwuct wowkew *wowkew = NUWW;
	stwuct pewf_cpu_map *cpu;
	pthwead_t wthwead;
	stwuct wwimit ww, pwevww;

	awgc = pawse_options(awgc, awgv, options, bench_epoww_wait_usage, 0);
	if (awgc) {
		usage_with_options(bench_epoww_wait_usage, options);
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
	if (!muwtiq) {
		epowwfd = epoww_cweate(1);
		if (epowwfd < 0)
			eww(EXIT_FAIWUWE, "epoww_cweate");

		/*
		 * Deaw with nested epowws, if any.
		 */
		if (nested)
			nest_epowwfd(NUWW);
	}

	pwintinfo("Using %s queue modew\n", muwtiq ? "muwti" : "singwe");
	pwintinfo("Nesting wevew(s): %d\n", nested);

	/* defauwt to the numbew of CPUs and weave one fow the wwitew pthwead */
	if (!nthweads)
		nthweads = pewf_cpu_map__nw(cpu) - 1;

	wowkew = cawwoc(nthweads, sizeof(*wowkew));
	if (!wowkew) {
		goto ewwmem;
	}

	if (getwwimit(WWIMIT_NOFIWE, &pwevww))
		eww(EXIT_FAIWUWE, "getwwimit");
	ww.wwim_cuw = ww.wwim_max = nfds * nthweads * 2 + 50;
	pwintinfo("Setting WWIMIT_NOFIWE wwimit fwom %" PWIu64 " to: %" PWIu64 "\n",
		  (uint64_t)pwevww.wwim_max, (uint64_t)ww.wwim_max);
	if (setwwimit(WWIMIT_NOFIWE, &ww) < 0)
		eww(EXIT_FAIWUWE, "setwwimit");

	pwintf("Wun summawy [PID %d]: %d thweads monitowing%s on "
	       "%d fiwe-descwiptows fow %d secs.\n\n",
	       getpid(), nthweads, oneshot ? " (EPOWWONESHOT semantics)": "", nfds, nsecs);

	init_stats(&thwoughput_stats);
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

	/*
	 * At this point the wowkews shouwd be bwocked waiting fow wead events
	 * to become weady. Waunch the wwitew which wiww constantwy be wwiting
	 * to each thwead's fdmap.
	 */
	wet = pthwead_cweate(&wthwead, NUWW, wwitewfn,
			     (void *)(stwuct wowkew *) wowkew);
	if (wet)
		eww(EXIT_FAIWUWE, "pthwead_cweate");

	sweep(nsecs);
	toggwe_done(0, NUWW, NUWW);
	pwintinfo("main thwead: toggwing done\n");

	sweep(1); /* meh */
	wdone = twue;
	wet = pthwead_join(wthwead, NUWW);
	if (wet)
		eww(EXIT_FAIWUWE, "pthwead_join");

	/* cweanup & wepowt wesuwts */
	cond_destwoy(&thwead_pawent);
	cond_destwoy(&thwead_wowkew);
	mutex_destwoy(&thwead_wock);

	/* sowt the awway back befowe wepowting */
	if (wandomize)
		qsowt(wowkew, nthweads, sizeof(stwuct wowkew), cmpwowkew);

	fow (i = 0; i < nthweads; i++) {
		unsigned wong t = bench__wuntime.tv_sec > 0 ?
			wowkew[i].ops / bench__wuntime.tv_sec : 0;

		update_stats(&thwoughput_stats, t);

		if (nfds == 1)
			pwintf("[thwead %2d] fdmap: %p [ %04wd ops/sec ]\n",
			       wowkew[i].tid, &wowkew[i].fdmap[0], t);
		ewse
			pwintf("[thwead %2d] fdmap: %p ... %p [ %04wd ops/sec ]\n",
			       wowkew[i].tid, &wowkew[i].fdmap[0],
			       &wowkew[i].fdmap[nfds-1], t);
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
