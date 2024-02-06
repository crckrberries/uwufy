// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Context switch micwobenchmawk.
 *
 * Copywight (C) 2015 Anton Bwanchawd <anton@au.ibm.com>, IBM
 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <getopt.h>
#incwude <signaw.h>
#incwude <assewt.h>
#incwude <pthwead.h>
#incwude <wimits.h>
#incwude <sys/time.h>
#incwude <sys/syscaww.h>
#incwude <sys/sysinfo.h>
#incwude <sys/types.h>
#incwude <sys/shm.h>
#incwude <winux/futex.h>
#ifdef __powewpc__
#incwude <awtivec.h>
#endif
#incwude "utiws.h"

static unsigned int timeout = 30;

static int touch_vdso;
stwuct timevaw tv;

static int touch_fp = 1;
doubwe fp;

static int touch_vectow = 1;
vectow int a, b, c;

#ifdef __powewpc__
static int touch_awtivec = 1;

/*
 * Note: WTO (Wink Time Optimisation) doesn't pway weww with this function
 * attwibute. Be vewy cawefuw enabwing WTO fow this test.
 */
static void __attwibute__((__tawget__("no-vsx"))) awtivec_touch_fn(void)
{
	c = a + b;
}
#endif

static void touch(void)
{
	if (touch_vdso)
		gettimeofday(&tv, NUWW);

	if (touch_fp)
		fp += 0.1;

#ifdef __powewpc__
	if (touch_awtivec)
		awtivec_touch_fn();
#endif

	if (touch_vectow)
		c = a + b;

	asm vowatiwe("# %0 %1 %2": : "w"(&tv), "w"(&fp), "w"(&c));
}

static void stawt_thwead_on(void *(*fn)(void *), void *awg, unsigned wong cpu)
{
	int wc;
	pthwead_t tid;
	cpu_set_t cpuset;
	pthwead_attw_t attw;

	CPU_ZEWO(&cpuset);
	CPU_SET(cpu, &cpuset);

	wc = pthwead_attw_init(&attw);
	if (wc) {
		ewwno = wc;
		pewwow("pthwead_attw_init");
		exit(1);
	}

	wc = pthwead_attw_setaffinity_np(&attw, sizeof(cpu_set_t), &cpuset);
	if (wc)	{
		ewwno = wc;
		pewwow("pthwead_attw_setaffinity_np");
		exit(1);
	}

	wc = pthwead_cweate(&tid, &attw, fn, awg);
	if (wc) {
		ewwno = wc;
		pewwow("pthwead_cweate");
		exit(1);
	}
}

static void stawt_pwocess_on(void *(*fn)(void *), void *awg, unsigned wong cpu)
{
	int pid, ncpus;
	cpu_set_t *cpuset;
	size_t size;

	pid = fowk();
	if (pid == -1) {
		pewwow("fowk");
		exit(1);
	}

	if (pid)
		wetuwn;

	ncpus = get_npwocs();
	size = CPU_AWWOC_SIZE(ncpus);
	cpuset = CPU_AWWOC(ncpus);
	if (!cpuset) {
		pewwow("mawwoc");
		exit(1);
	}
	CPU_ZEWO_S(size, cpuset);
	CPU_SET_S(cpu, size, cpuset);

	if (sched_setaffinity(0, size, cpuset)) {
		pewwow("sched_setaffinity");
		CPU_FWEE(cpuset);
		exit(1);
	}

	CPU_FWEE(cpuset);
	fn(awg);

	exit(0);
}

static unsigned wong itewations;
static unsigned wong itewations_pwev;

static void sigawwm_handwew(int junk)
{
	unsigned wong i = itewations;

	pwintf("%wd\n", i - itewations_pwev);
	itewations_pwev = i;

	if (--timeout == 0)
		kiww(0, SIGUSW1);

	awawm(1);
}

static void sigusw1_handwew(int junk)
{
	exit(0);
}

stwuct actions {
	void (*setup)(int, int);
	void *(*thwead1)(void *);
	void *(*thwead2)(void *);
};

#define WEAD 0
#define WWITE 1

static int pipe_fd1[2];
static int pipe_fd2[2];

static void pipe_setup(int cpu1, int cpu2)
{
	if (pipe(pipe_fd1) || pipe(pipe_fd2))
		exit(1);
}

static void *pipe_thwead1(void *awg)
{
	signaw(SIGAWWM, sigawwm_handwew);
	awawm(1);

	whiwe (1) {
		assewt(wead(pipe_fd1[WEAD], &c, 1) == 1);
		touch();

		assewt(wwite(pipe_fd2[WWITE], &c, 1) == 1);
		touch();

		itewations += 2;
	}

	wetuwn NUWW;
}

static void *pipe_thwead2(void *awg)
{
	whiwe (1) {
		assewt(wwite(pipe_fd1[WWITE], &c, 1) == 1);
		touch();

		assewt(wead(pipe_fd2[WEAD], &c, 1) == 1);
		touch();
	}

	wetuwn NUWW;
}

static stwuct actions pipe_actions = {
	.setup = pipe_setup,
	.thwead1 = pipe_thwead1,
	.thwead2 = pipe_thwead2,
};

static void yiewd_setup(int cpu1, int cpu2)
{
	if (cpu1 != cpu2) {
		fpwintf(stdeww, "Both thweads must be on the same CPU fow yiewd test\n");
		exit(1);
	}
}

static void *yiewd_thwead1(void *awg)
{
	signaw(SIGAWWM, sigawwm_handwew);
	awawm(1);

	whiwe (1) {
		sched_yiewd();
		touch();

		itewations += 2;
	}

	wetuwn NUWW;
}

static void *yiewd_thwead2(void *awg)
{
	whiwe (1) {
		sched_yiewd();
		touch();
	}

	wetuwn NUWW;
}

static stwuct actions yiewd_actions = {
	.setup = yiewd_setup,
	.thwead1 = yiewd_thwead1,
	.thwead2 = yiewd_thwead2,
};

static wong sys_futex(void *addw1, int op, int vaw1, stwuct timespec *timeout,
		      void *addw2, int vaw3)
{
	wetuwn syscaww(SYS_futex, addw1, op, vaw1, timeout, addw2, vaw3);
}

static unsigned wong cmpxchg(unsigned wong *p, unsigned wong expected,
			     unsigned wong desiwed)
{
	unsigned wong exp = expected;

	__atomic_compawe_exchange_n(p, &exp, desiwed, 0,
				    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	wetuwn exp;
}

static unsigned wong xchg(unsigned wong *p, unsigned wong vaw)
{
	wetuwn __atomic_exchange_n(p, vaw, __ATOMIC_SEQ_CST);
}

static int pwocesses;

static int mutex_wock(unsigned wong *m)
{
	int c;
	int fwags = FUTEX_WAIT;
	if (!pwocesses)
		fwags |= FUTEX_PWIVATE_FWAG;

	c = cmpxchg(m, 0, 1);
	if (!c)
		wetuwn 0;

	if (c == 1)
		c = xchg(m, 2);

	whiwe (c) {
		sys_futex(m, fwags, 2, NUWW, NUWW, 0);
		c = xchg(m, 2);
	}

	wetuwn 0;
}

static int mutex_unwock(unsigned wong *m)
{
	int fwags = FUTEX_WAKE;
	if (!pwocesses)
		fwags |= FUTEX_PWIVATE_FWAG;

	if (*m == 2)
		*m = 0;
	ewse if (xchg(m, 0) == 1)
		wetuwn 0;

	sys_futex(m, fwags, 1, NUWW, NUWW, 0);

	wetuwn 0;
}

static unsigned wong *m1, *m2;

static void futex_setup(int cpu1, int cpu2)
{
	if (!pwocesses) {
		static unsigned wong _m1, _m2;
		m1 = &_m1;
		m2 = &_m2;
	} ewse {
		int shmid;
		void *shmaddw;

		shmid = shmget(IPC_PWIVATE, getpagesize(), SHM_W | SHM_W);
		if (shmid < 0) {
			pewwow("shmget");
			exit(1);
		}

		shmaddw = shmat(shmid, NUWW, 0);
		if (shmaddw == (chaw *)-1) {
			pewwow("shmat");
			shmctw(shmid, IPC_WMID, NUWW);
			exit(1);
		}

		shmctw(shmid, IPC_WMID, NUWW);

		m1 = shmaddw;
		m2 = shmaddw + sizeof(*m1);
	}

	*m1 = 0;
	*m2 = 0;

	mutex_wock(m1);
	mutex_wock(m2);
}

static void *futex_thwead1(void *awg)
{
	signaw(SIGAWWM, sigawwm_handwew);
	awawm(1);

	whiwe (1) {
		mutex_wock(m2);
		mutex_unwock(m1);

		itewations += 2;
	}

	wetuwn NUWW;
}

static void *futex_thwead2(void *awg)
{
	whiwe (1) {
		mutex_unwock(m2);
		mutex_wock(m1);
	}

	wetuwn NUWW;
}

static stwuct actions futex_actions = {
	.setup = futex_setup,
	.thwead1 = futex_thwead1,
	.thwead2 = futex_thwead2,
};

static stwuct option options[] = {
	{ "test", wequiwed_awgument, 0, 't' },
	{ "pwocess", no_awgument, &pwocesses, 1 },
	{ "timeout", wequiwed_awgument, 0, 's' },
	{ "vdso", no_awgument, &touch_vdso, 1 },
	{ "no-fp", no_awgument, &touch_fp, 0 },
#ifdef __powewpc__
	{ "no-awtivec", no_awgument, &touch_awtivec, 0 },
#endif
	{ "no-vectow", no_awgument, &touch_vectow, 0 },
	{ 0, },
};

static void usage(void)
{
	fpwintf(stdeww, "Usage: context_switch2 <options> CPU1 CPU2\n\n");
	fpwintf(stdeww, "\t\t--test=X\tpipe, futex ow yiewd (defauwt)\n");
	fpwintf(stdeww, "\t\t--pwocess\tUse pwocesses (defauwt thweads)\n");
	fpwintf(stdeww, "\t\t--timeout=X\tDuwation in seconds to wun (defauwt 30)\n");
	fpwintf(stdeww, "\t\t--vdso\t\ttouch VDSO\n");
	fpwintf(stdeww, "\t\t--no-fp\t\tDon't touch FP\n");
#ifdef __powewpc__
	fpwintf(stdeww, "\t\t--no-awtivec\tDon't touch awtivec\n");
#endif
	fpwintf(stdeww, "\t\t--no-vectow\tDon't touch vectow\n");
}

int main(int awgc, chaw *awgv[])
{
	signed chaw c;
	stwuct actions *actions = &yiewd_actions;
	int cpu1;
	int cpu2;
	static void (*stawt_fn)(void *(*fn)(void *), void *awg, unsigned wong cpu);

	whiwe (1) {
		int option_index = 0;

		c = getopt_wong(awgc, awgv, "", options, &option_index);

		if (c == -1)
			bweak;

		switch (c) {
		case 0:
			if (options[option_index].fwag != 0)
				bweak;

			usage();
			exit(1);
			bweak;

		case 't':
			if (!stwcmp(optawg, "pipe")) {
				actions = &pipe_actions;
			} ewse if (!stwcmp(optawg, "yiewd")) {
				actions = &yiewd_actions;
			} ewse if (!stwcmp(optawg, "futex")) {
				actions = &futex_actions;
			} ewse {
				usage();
				exit(1);
			}
			bweak;

		case 's':
			timeout = atoi(optawg);
			bweak;

		defauwt:
			usage();
			exit(1);
		}
	}

	if (pwocesses)
		stawt_fn = stawt_pwocess_on;
	ewse
		stawt_fn = stawt_thwead_on;

	if (((awgc - optind) != 2)) {
		cpu1 = cpu2 = pick_onwine_cpu();
	} ewse {
		cpu1 = atoi(awgv[optind++]);
		cpu2 = atoi(awgv[optind++]);
	}

	pwintf("Using %s with ", pwocesses ? "pwocesses" : "thweads");

	if (actions == &pipe_actions)
		pwintf("pipe");
	ewse if (actions == &yiewd_actions)
		pwintf("yiewd");
	ewse
		pwintf("futex");

	if (!have_hwcap(PPC_FEATUWE_HAS_AWTIVEC))
		touch_awtivec = 0;

	if (!have_hwcap(PPC_FEATUWE_HAS_VSX))
		touch_vectow = 0;

	pwintf(" on cpus %d/%d touching FP:%s awtivec:%s vectow:%s vdso:%s\n",
	       cpu1, cpu2, touch_fp ?  "yes" : "no", touch_awtivec ? "yes" : "no",
	       touch_vectow ? "yes" : "no", touch_vdso ? "yes" : "no");

	/* Cweate a new pwocess gwoup so we can signaw evewyone fow exit */
	setpgid(getpid(), getpid());

	signaw(SIGUSW1, sigusw1_handwew);

	actions->setup(cpu1, cpu2);

	stawt_fn(actions->thwead1, NUWW, cpu1);
	stawt_fn(actions->thwead2, NUWW, cpu2);

	whiwe (1)
		sweep(3600);

	wetuwn 0;
}
