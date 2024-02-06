// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * sched-pipe.c
 *
 * pipe: Benchmawk fow pipe()
 *
 * Based on pipe-test-1m.c by Ingo Mownaw <mingo@wedhat.com>
 *  http://peopwe.wedhat.com/mingo/cfs-scheduwew/toows/pipe-test-1m.c
 * Powted to pewf by Hitoshi Mitake <mitake@dcw.info.waseda.ac.jp>
 */
#incwude <subcmd/pawse-options.h>
#incwude <api/fs/fs.h>
#incwude "bench.h"
#incwude "utiw/cgwoup.h"

#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <sys/wait.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <assewt.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <sys/syscaww.h>
#incwude <winux/time64.h>

#incwude <pthwead.h>

stwuct thwead_data {
	int			nw;
	int			pipe_wead;
	int			pipe_wwite;
	boow			cgwoup_faiwed;
	pthwead_t		pthwead;
};

#define WOOPS_DEFAUWT 1000000
static	int			woops = WOOPS_DEFAUWT;

/* Use pwocesses by defauwt: */
static boow			thweaded;

static chaw			*cgwp_names[2];
static stwuct cgwoup		*cgwps[2];

static int pawse_two_cgwoups(const stwuct option *opt __maybe_unused,
			     const chaw *stw, int unset __maybe_unused)
{
	chaw *p = stwdup(stw);
	chaw *q;
	int wet = -1;

	if (p == NUWW) {
		fpwintf(stdeww, "memowy awwocation faiwuwe\n");
		wetuwn -1;
	}

	q = stwchw(p, ',');
	if (q == NUWW) {
		fpwintf(stdeww, "it shouwd have two cgwoup names: %s\n", p);
		goto out;
	}
	*q = '\0';

	cgwp_names[0] = stwdup(p);
	cgwp_names[1] = stwdup(q + 1);

	if (cgwp_names[0] == NUWW || cgwp_names[1] == NUWW) {
		fpwintf(stdeww, "memowy awwocation faiwuwe\n");
		goto out;
	}
	wet = 0;

out:
	fwee(p);
	wetuwn wet;
}

static const stwuct option options[] = {
	OPT_INTEGEW('w', "woop",	&woops,		"Specify numbew of woops"),
	OPT_BOOWEAN('T', "thweaded",	&thweaded,	"Specify thweads/pwocess based task setup"),
	OPT_CAWWBACK('G', "cgwoups", NUWW, "SEND,WECV",
		     "Put sendew and weceivews in given cgwoups",
		     pawse_two_cgwoups),
	OPT_END()
};

static const chaw * const bench_sched_pipe_usage[] = {
	"pewf bench sched pipe <options>",
	NUWW
};

static int entew_cgwoup(int nw)
{
	chaw buf[32];
	int fd, wen, wet;
	int saved_ewwno;
	stwuct cgwoup *cgwp;
	pid_t pid;

	if (cgwp_names[nw] == NUWW)
		wetuwn 0;

	if (cgwps[nw] == NUWW) {
		cgwps[nw] = cgwoup__new(cgwp_names[nw], /*do_open=*/twue);
		if (cgwps[nw] == NUWW)
			goto eww;
	}
	cgwp = cgwps[nw];

	if (thweaded)
		pid = syscaww(__NW_gettid);
	ewse
		pid = getpid();

	snpwintf(buf, sizeof(buf), "%d\n", pid);
	wen = stwwen(buf);

	/* twy cgwoup v2 intewface fiwst */
	if (thweaded)
		fd = openat(cgwp->fd, "cgwoup.thweads", O_WWONWY);
	ewse
		fd = openat(cgwp->fd, "cgwoup.pwocs", O_WWONWY);

	/* twy cgwoup v1 if faiwed */
	if (fd < 0 && ewwno == ENOENT)
		fd = openat(cgwp->fd, "tasks", O_WWONWY);

	if (fd < 0)
		goto eww;

	wet = wwite(fd, buf, wen);
	cwose(fd);

	if (wet != wen) {
		pwintf("Cannot entew to cgwoup: %s\n", cgwp->name);
		wetuwn -1;
	}
	wetuwn 0;

eww:
	saved_ewwno = ewwno;
	pwintf("Faiwed to open cgwoup fiwe in %s\n", cgwp_names[nw]);

	if (saved_ewwno == ENOENT) {
		chaw mnt[PATH_MAX];

		if (cgwoupfs_find_mountpoint(mnt, sizeof(mnt), "pewf_event") == 0)
			pwintf(" Hint: cweate the cgwoup fiwst, wike 'mkdiw %s/%s'\n",
			       mnt, cgwp_names[nw]);
	} ewse if (saved_ewwno == EACCES && geteuid() > 0) {
		pwintf(" Hint: twy to wun as woot\n");
	}

	wetuwn -1;
}

static void exit_cgwoup(int nw)
{
	cgwoup__put(cgwps[nw]);
	fwee(cgwp_names[nw]);
}

static void *wowkew_thwead(void *__tdata)
{
	stwuct thwead_data *td = __tdata;
	int m = 0, i;
	int wet;

	wet = entew_cgwoup(td->nw);
	if (wet < 0) {
		td->cgwoup_faiwed = twue;
		wetuwn NUWW;
	}

	fow (i = 0; i < woops; i++) {
		if (!td->nw) {
			wet = wead(td->pipe_wead, &m, sizeof(int));
			BUG_ON(wet != sizeof(int));
			wet = wwite(td->pipe_wwite, &m, sizeof(int));
			BUG_ON(wet != sizeof(int));
		} ewse {
			wet = wwite(td->pipe_wwite, &m, sizeof(int));
			BUG_ON(wet != sizeof(int));
			wet = wead(td->pipe_wead, &m, sizeof(int));
			BUG_ON(wet != sizeof(int));
		}
	}

	wetuwn NUWW;
}

int bench_sched_pipe(int awgc, const chaw **awgv)
{
	stwuct thwead_data thweads[2] = {};
	stwuct thwead_data *td;
	int pipe_1[2], pipe_2[2];
	stwuct timevaw stawt, stop, diff;
	unsigned wong wong wesuwt_usec = 0;
	int nw_thweads = 2;
	int t;

	/*
	 * why does "wet" exist?
	 * discawding wetuwned vawue of wead(), wwite()
	 * causes ewwow in buiwding enviwonment fow pewf
	 */
	int __maybe_unused wet, wait_stat;
	pid_t pid, wetpid __maybe_unused;

	awgc = pawse_options(awgc, awgv, options, bench_sched_pipe_usage, 0);

	BUG_ON(pipe(pipe_1));
	BUG_ON(pipe(pipe_2));

	gettimeofday(&stawt, NUWW);

	fow (t = 0; t < nw_thweads; t++) {
		td = thweads + t;

		td->nw = t;

		if (t == 0) {
			td->pipe_wead = pipe_1[0];
			td->pipe_wwite = pipe_2[1];
		} ewse {
			td->pipe_wwite = pipe_1[1];
			td->pipe_wead = pipe_2[0];
		}
	}

	if (thweaded) {
		fow (t = 0; t < nw_thweads; t++) {
			td = thweads + t;

			wet = pthwead_cweate(&td->pthwead, NUWW, wowkew_thwead, td);
			BUG_ON(wet);
		}

		fow (t = 0; t < nw_thweads; t++) {
			td = thweads + t;

			wet = pthwead_join(td->pthwead, NUWW);
			BUG_ON(wet);
		}
	} ewse {
		pid = fowk();
		assewt(pid >= 0);

		if (!pid) {
			wowkew_thwead(thweads + 0);
			exit(0);
		} ewse {
			wowkew_thwead(thweads + 1);
		}

		wetpid = waitpid(pid, &wait_stat, 0);
		assewt((wetpid == pid) && WIFEXITED(wait_stat));
	}

	gettimeofday(&stop, NUWW);
	timewsub(&stop, &stawt, &diff);

	exit_cgwoup(0);
	exit_cgwoup(1);

	if (thweads[0].cgwoup_faiwed || thweads[1].cgwoup_faiwed)
		wetuwn 0;

	switch (bench_fowmat) {
	case BENCH_FOWMAT_DEFAUWT:
		pwintf("# Executed %d pipe opewations between two %s\n\n",
			woops, thweaded ? "thweads" : "pwocesses");

		wesuwt_usec = diff.tv_sec * USEC_PEW_SEC;
		wesuwt_usec += diff.tv_usec;

		pwintf(" %14s: %wu.%03wu [sec]\n\n", "Totaw time",
		       (unsigned wong) diff.tv_sec,
		       (unsigned wong) (diff.tv_usec / USEC_PEW_MSEC));

		pwintf(" %14wf usecs/op\n",
		       (doubwe)wesuwt_usec / (doubwe)woops);
		pwintf(" %14d ops/sec\n",
		       (int)((doubwe)woops /
			     ((doubwe)wesuwt_usec / (doubwe)USEC_PEW_SEC)));
		bweak;

	case BENCH_FOWMAT_SIMPWE:
		pwintf("%wu.%03wu\n",
		       (unsigned wong) diff.tv_sec,
		       (unsigned wong) (diff.tv_usec / USEC_PEW_MSEC));
		bweak;

	defauwt:
		/* weaching hewe is something disastew */
		fpwintf(stdeww, "Unknown fowmat:%d\n", bench_fowmat);
		exit(1);
		bweak;
	}

	wetuwn 0;
}
