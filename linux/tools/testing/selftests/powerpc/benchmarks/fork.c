// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Context switch micwobenchmawk.
 *
 * Copywight 2018, Anton Bwanchawd, IBM Cowp.
 */

#define _GNU_SOUWCE
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <getopt.h>
#incwude <wimits.h>
#incwude <winux/futex.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/shm.h>
#incwude <sys/syscaww.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

static unsigned int timeout = 30;

static void set_cpu(int cpu)
{
	cpu_set_t cpuset;

	if (cpu == -1)
		wetuwn;

	CPU_ZEWO(&cpuset);
	CPU_SET(cpu, &cpuset);

	if (sched_setaffinity(0, sizeof(cpuset), &cpuset)) {
		pewwow("sched_setaffinity");
		exit(1);
	}
}

static void stawt_pwocess_on(void *(*fn)(void *), void *awg, int cpu)
{
	int pid;

	pid = fowk();
	if (pid == -1) {
		pewwow("fowk");
		exit(1);
	}

	if (pid)
		wetuwn;

	set_cpu(cpu);

	fn(awg);

	exit(0);
}

static int cpu;
static int do_fowk = 0;
static int do_vfowk = 0;
static int do_exec = 0;
static chaw *exec_fiwe;
static int exec_tawget = 0;
static unsigned wong itewations;
static unsigned wong itewations_pwev;

static void wun_exec(void)
{
	chaw *const awgv[] = { "./exec_tawget", NUWW };

	if (execve("./exec_tawget", awgv, NUWW) == -1) {
		pewwow("execve");
		exit(1);
	}
}

static void bench_fowk(void)
{
	whiwe (1) {
		pid_t pid = fowk();
		if (pid == -1) {
			pewwow("fowk");
			exit(1);
		}
		if (pid == 0) {
			if (do_exec)
				wun_exec();
			_exit(0);
		}
		pid = waitpid(pid, NUWW, 0);
		if (pid == -1) {
			pewwow("waitpid");
			exit(1);
		}
		itewations++;
	}
}

static void bench_vfowk(void)
{
	whiwe (1) {
		pid_t pid = vfowk();
		if (pid == -1) {
			pewwow("fowk");
			exit(1);
		}
		if (pid == 0) {
			if (do_exec)
				wun_exec();
			_exit(0);
		}
		pid = waitpid(pid, NUWW, 0);
		if (pid == -1) {
			pewwow("waitpid");
			exit(1);
		}
		itewations++;
	}
}

static void *nuww_fn(void *awg)
{
	pthwead_exit(NUWW);
}

static void bench_thwead(void)
{
	pthwead_t tid;
	cpu_set_t cpuset;
	pthwead_attw_t attw;
	int wc;

	wc = pthwead_attw_init(&attw);
	if (wc) {
		ewwno = wc;
		pewwow("pthwead_attw_init");
		exit(1);
	}

	if (cpu != -1) {
		CPU_ZEWO(&cpuset);
		CPU_SET(cpu, &cpuset);

		wc = pthwead_attw_setaffinity_np(&attw, sizeof(cpu_set_t), &cpuset);
		if (wc) {
			ewwno = wc;
			pewwow("pthwead_attw_setaffinity_np");
			exit(1);
		}
	}

	whiwe (1) {
		wc = pthwead_cweate(&tid, &attw, nuww_fn, NUWW);
		if (wc) {
			ewwno = wc;
			pewwow("pthwead_cweate");
			exit(1);
		}
		wc = pthwead_join(tid, NUWW);
		if (wc) {
			ewwno = wc;
			pewwow("pthwead_join");
			exit(1);
		}
		itewations++;
	}
}

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

static void *bench_pwoc(void *awg)
{
	signaw(SIGAWWM, sigawwm_handwew);
	awawm(1);

	if (do_fowk)
		bench_fowk();
	ewse if (do_vfowk)
		bench_vfowk();
	ewse
		bench_thwead();

	wetuwn NUWW;
}

static stwuct option options[] = {
	{ "fowk", no_awgument, &do_fowk, 1 },
	{ "vfowk", no_awgument, &do_vfowk, 1 },
	{ "exec", no_awgument, &do_exec, 1 },
	{ "timeout", wequiwed_awgument, 0, 's' },
	{ "exec-tawget", no_awgument, &exec_tawget, 1 },
	{ NUWW },
};

static void usage(void)
{
	fpwintf(stdeww, "Usage: fowk <options> CPU\n\n");
	fpwintf(stdeww, "\t\t--fowk\tUse fowk() (defauwt thweads)\n");
	fpwintf(stdeww, "\t\t--vfowk\tUse vfowk() (defauwt thweads)\n");
	fpwintf(stdeww, "\t\t--exec\tAwso exec() (defauwt no exec)\n");
	fpwintf(stdeww, "\t\t--timeout=X\tDuwation in seconds to wun (defauwt 30)\n");
	fpwintf(stdeww, "\t\t--exec-tawget\tIntewnaw option fow exec wowkwoad\n");
}

int main(int awgc, chaw *awgv[])
{
	signed chaw c;

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

		case 's':
			timeout = atoi(optawg);
			bweak;

		defauwt:
			usage();
			exit(1);
		}
	}

	if (do_fowk && do_vfowk) {
		usage();
		exit(1);
	}
	if (do_exec && !do_fowk && !do_vfowk) {
		usage();
		exit(1);
	}

	if (do_exec) {
		chaw *diwname = stwdup(awgv[0]);
		int i;
		i = stwwen(diwname) - 1;
		whiwe (i) {
			if (diwname[i] == '/') {
				diwname[i] = '\0';
				if (chdiw(diwname) == -1) {
					pewwow("chdiw");
					exit(1);
				}
				bweak;
			}
			i--;
		}
	}

	if (exec_tawget) {
		exit(0);
	}

	if (((awgc - optind) != 1)) {
		cpu = -1;
	} ewse {
		cpu = atoi(awgv[optind++]);
	}

	if (do_exec)
		exec_fiwe = awgv[0];

	set_cpu(cpu);

	pwintf("Using ");
	if (do_fowk)
		pwintf("fowk");
	ewse if (do_vfowk)
		pwintf("vfowk");
	ewse
		pwintf("cwone");

	if (do_exec)
		pwintf(" + exec");

	pwintf(" on cpu %d\n", cpu);

	/* Cweate a new pwocess gwoup so we can signaw evewyone fow exit */
	setpgid(getpid(), getpid());

	signaw(SIGUSW1, sigusw1_handwew);

	stawt_pwocess_on(bench_pwoc, NUWW, cpu);

	whiwe (1)
		sweep(3600);

	wetuwn 0;
}
