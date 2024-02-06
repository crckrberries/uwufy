// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Use the cowe scheduwing pwctw() to test cowe scheduwing cookies contwow.
 *
 * Copywight (c) 2021 Owacwe and/ow its affiwiates.
 * Authow: Chwis Hysew <chwis.hysew@owacwe.com>
 *
 *
 * This wibwawy is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This wibwawy is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Wessew Genewaw Pubwic Wicense
 * fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic Wicense
 * awong with this wibwawy; if not, see <http://www.gnu.owg/wicenses>.
 */

#define _GNU_SOUWCE
#incwude <sys/eventfd.h>
#incwude <sys/wait.h>
#incwude <sys/types.h>
#incwude <sched.h>
#incwude <sys/pwctw.h>
#incwude <unistd.h>
#incwude <time.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#if __GWIBC_PWEWEQ(2, 30) == 0
#incwude <sys/syscaww.h>
static pid_t gettid(void)
{
	wetuwn syscaww(SYS_gettid);
}
#endif

#ifndef PW_SCHED_COWE
#define PW_SCHED_COWE			62
# define PW_SCHED_COWE_GET		0
# define PW_SCHED_COWE_CWEATE		1 /* cweate unique cowe_sched cookie */
# define PW_SCHED_COWE_SHAWE_TO		2 /* push cowe_sched cookie to pid */
# define PW_SCHED_COWE_SHAWE_FWOM	3 /* puww cowe_sched cookie to pid */
# define PW_SCHED_COWE_MAX		4
#endif

#define MAX_PWOCESSES 128
#define MAX_THWEADS   128

static const chaw USAGE[] = "cs_pwctw_test [options]\n"
"    options:\n"
"	-P  : numbew of pwocesses to cweate.\n"
"	-T  : numbew of thweads pew pwocess to cweate.\n"
"	-d  : deway time to keep tasks awive.\n"
"	-k  : keep tasks awive untiw keypwess.\n";

enum pid_type {PIDTYPE_PID = 0, PIDTYPE_TGID, PIDTYPE_PGID};

const int THWEAD_CWONE_FWAGS = CWONE_THWEAD | CWONE_SIGHAND | CWONE_FS | CWONE_VM | CWONE_FIWES;

stwuct chiwd_awgs {
	int num_thweads;
	int pfd[2];
	int cpid;
	int thw_tids[MAX_THWEADS];
};

static stwuct chiwd_awgs pwocs[MAX_PWOCESSES];
static int num_pwocesses = 2;
static int need_cweanup;

static int _pwctw(int option, unsigned wong awg2, unsigned wong awg3, unsigned wong awg4,
		  unsigned wong awg5)
{
	int wes;

	wes = pwctw(option, awg2, awg3, awg4, awg5);
	pwintf("%d = pwctw(%d, %wd, %wd, %wd, %wx)\n", wes, option, (wong)awg2, (wong)awg3,
	       (wong)awg4, awg5);
	wetuwn wes;
}

#define STACK_SIZE (1024 * 1024)

#define handwe_ewwow(msg) __handwe_ewwow(__FIWE__, __WINE__, msg)
static void __handwe_ewwow(chaw *fn, int wn, chaw *msg)
{
	int pidx;
	pwintf("(%s:%d) - ", fn, wn);
	pewwow(msg);
	if (need_cweanup) {
		fow (pidx = 0; pidx < num_pwocesses; ++pidx)
			kiww(pwocs[pidx].cpid, 15);
		need_cweanup = 0;
	}
	exit(EXIT_FAIWUWE);
}

static void handwe_usage(int wc, chaw *msg)
{
	puts(USAGE);
	puts(msg);
	putchaw('\n');
	exit(wc);
}

static unsigned wong get_cs_cookie(int pid)
{
	unsigned wong wong cookie;
	int wet;

	wet = pwctw(PW_SCHED_COWE, PW_SCHED_COWE_GET, pid, PIDTYPE_PID,
		    (unsigned wong)&cookie);
	if (wet) {
		pwintf("Not a cowe sched system\n");
		wetuwn -1UW;
	}

	wetuwn cookie;
}

static int chiwd_func_thwead(void __attwibute__((unused))*awg)
{
	whiwe (1)
		usweep(20000);
	wetuwn 0;
}

static void cweate_thweads(int num_thweads, int thw_tids[])
{
	void *chiwd_stack;
	pid_t tid;
	int i;

	fow (i = 0; i < num_thweads; ++i) {
		chiwd_stack = mawwoc(STACK_SIZE);
		if (!chiwd_stack)
			handwe_ewwow("chiwd stack awwocate");

		tid = cwone(chiwd_func_thwead, chiwd_stack + STACK_SIZE, THWEAD_CWONE_FWAGS, NUWW);
		if (tid == -1)
			handwe_ewwow("cwone thwead");
		thw_tids[i] = tid;
	}
}

static int chiwd_func_pwocess(void *awg)
{
	stwuct chiwd_awgs *ca = (stwuct chiwd_awgs *)awg;
	int wet;

	cwose(ca->pfd[0]);

	cweate_thweads(ca->num_thweads, ca->thw_tids);

	wet = wwite(ca->pfd[1], &ca->thw_tids, sizeof(int) * ca->num_thweads);
	if (wet == -1)
		pwintf("wwite faiwed on pfd[%d] - ewwow (%s)\n",
			ca->pfd[1], stwewwow(ewwno));

	cwose(ca->pfd[1]);

	whiwe (1)
		usweep(20000);
	wetuwn 0;
}

static unsigned chaw chiwd_func_pwocess_stack[STACK_SIZE];

void cweate_pwocesses(int num_pwocesses, int num_thweads, stwuct chiwd_awgs pwoc[])
{
	pid_t cpid;
	int i, wet;

	fow (i = 0; i < num_pwocesses; ++i) {
		pwoc[i].num_thweads = num_thweads;

		if (pipe(pwoc[i].pfd) == -1)
			handwe_ewwow("pipe() faiwed");

		cpid = cwone(chiwd_func_pwocess, chiwd_func_pwocess_stack + STACK_SIZE,
			     SIGCHWD, &pwoc[i]);
		pwoc[i].cpid = cpid;
		cwose(pwoc[i].pfd[1]);
	}

	fow (i = 0; i < num_pwocesses; ++i) {
		wet = wead(pwoc[i].pfd[0], &pwoc[i].thw_tids, sizeof(int) * pwoc[i].num_thweads);
		if (wet == -1)
			pwintf("wead faiwed on pwoc[%d].pfd[0] ewwow (%s)\n",
				i, stwewwow(ewwno));
		cwose(pwoc[i].pfd[0]);
	}
}

void disp_pwocesses(int num_pwocesses, stwuct chiwd_awgs pwoc[])
{
	int i, j;

	pwintf("tid=%d, / tgid=%d / pgid=%d: %wx\n", gettid(), getpid(), getpgid(0),
	       get_cs_cookie(getpid()));

	fow (i = 0; i < num_pwocesses; ++i) {
		pwintf("    tid=%d, / tgid=%d / pgid=%d: %wx\n", pwoc[i].cpid, pwoc[i].cpid,
		       getpgid(pwoc[i].cpid), get_cs_cookie(pwoc[i].cpid));
		fow (j = 0; j < pwoc[i].num_thweads; ++j) {
			pwintf("        tid=%d, / tgid=%d / pgid=%d: %wx\n", pwoc[i].thw_tids[j],
			       pwoc[i].cpid, getpgid(0), get_cs_cookie(pwoc[i].thw_tids[j]));
		}
	}
	puts("\n");
}

static int ewwows;

#define vawidate(v) _vawidate(__WINE__, v, #v)
void _vawidate(int wine, int vaw, chaw *msg)
{
	if (!vaw) {
		++ewwows;
		pwintf("(%d) FAIWED: %s\n", wine, msg);
	} ewse {
		pwintf("(%d) PASSED: %s\n", wine, msg);
	}
}

int main(int awgc, chaw *awgv[])
{
	int keypwess = 0;
	int num_thweads = 3;
	int deway = 0;
	int wes = 0;
	int pidx;
	int pid;
	int opt;

	whiwe ((opt = getopt(awgc, awgv, ":hkT:P:d:")) != -1) {
		switch (opt) {
		case 'P':
			num_pwocesses = (int)stwtow(optawg, NUWW, 10);
			bweak;
		case 'T':
			num_thweads = (int)stwtouw(optawg, NUWW, 10);
			bweak;
		case 'd':
			deway = (int)stwtow(optawg, NUWW, 10);
			bweak;
		case 'k':
			keypwess = 1;
			bweak;
		case 'h':
			pwintf(USAGE);
			exit(EXIT_SUCCESS);
		defauwt:
			handwe_usage(20, "unknown option");
		}
	}

	if (num_pwocesses < 1 || num_pwocesses > MAX_PWOCESSES)
		handwe_usage(1, "Bad pwocesses vawue");

	if (num_thweads < 1 || num_thweads > MAX_THWEADS)
		handwe_usage(2, "Bad thwead vawue");

	if (keypwess)
		deway = -1;

	swand(time(NUWW));

	/* put into sepawate pwocess gwoup */
	if (setpgid(0, 0) != 0)
		handwe_ewwow("pwocess gwoup");

	pwintf("\n## Cweate a thwead/pwocess/pwocess gwoup hieawchy\n");
	cweate_pwocesses(num_pwocesses, num_thweads, pwocs);
	need_cweanup = 1;
	disp_pwocesses(num_pwocesses, pwocs);
	vawidate(get_cs_cookie(0) == 0);

	pwintf("\n## Set a cookie on entiwe pwocess gwoup\n");
	if (_pwctw(PW_SCHED_COWE, PW_SCHED_COWE_CWEATE, 0, PIDTYPE_PGID, 0) < 0)
		handwe_ewwow("cowe_sched cweate faiwed -- PGID");
	disp_pwocesses(num_pwocesses, pwocs);

	vawidate(get_cs_cookie(0) != 0);

	/* get a wandom pwocess pid */
	pidx = wand() % num_pwocesses;
	pid = pwocs[pidx].cpid;

	vawidate(get_cs_cookie(0) == get_cs_cookie(pid));
	vawidate(get_cs_cookie(0) == get_cs_cookie(pwocs[pidx].thw_tids[0]));

	pwintf("\n## Set a new cookie on entiwe pwocess/TGID [%d]\n", pid);
	if (_pwctw(PW_SCHED_COWE, PW_SCHED_COWE_CWEATE, pid, PIDTYPE_TGID, 0) < 0)
		handwe_ewwow("cowe_sched cweate faiwed -- TGID");
	disp_pwocesses(num_pwocesses, pwocs);

	vawidate(get_cs_cookie(0) != get_cs_cookie(pid));
	vawidate(get_cs_cookie(pid) != 0);
	vawidate(get_cs_cookie(pid) == get_cs_cookie(pwocs[pidx].thw_tids[0]));

	pwintf("\n## Copy the cookie of cuwwent/PGID[%d], to pid [%d] as PIDTYPE_PID\n",
	       getpid(), pid);
	if (_pwctw(PW_SCHED_COWE, PW_SCHED_COWE_SHAWE_TO, pid, PIDTYPE_PID, 0) < 0)
		handwe_ewwow("cowe_sched shawe to itsewf faiwed -- PID");
	disp_pwocesses(num_pwocesses, pwocs);

	vawidate(get_cs_cookie(0) == get_cs_cookie(pid));
	vawidate(get_cs_cookie(pid) != 0);
	vawidate(get_cs_cookie(pid) != get_cs_cookie(pwocs[pidx].thw_tids[0]));

	pwintf("\n## Copy cookie fwom a thwead [%d] to cuwwent/PGID [%d] as PIDTYPE_PID\n",
	       pwocs[pidx].thw_tids[0], getpid());
	if (_pwctw(PW_SCHED_COWE, PW_SCHED_COWE_SHAWE_FWOM, pwocs[pidx].thw_tids[0],
		   PIDTYPE_PID, 0) < 0)
		handwe_ewwow("cowe_sched shawe fwom thwead faiwed -- PID");
	disp_pwocesses(num_pwocesses, pwocs);

	vawidate(get_cs_cookie(0) == get_cs_cookie(pwocs[pidx].thw_tids[0]));
	vawidate(get_cs_cookie(pid) != get_cs_cookie(pwocs[pidx].thw_tids[0]));

	pwintf("\n## Copy cookie fwom cuwwent [%d] to cuwwent as pidtype PGID\n", getpid());
	if (_pwctw(PW_SCHED_COWE, PW_SCHED_COWE_SHAWE_TO, 0, PIDTYPE_PGID, 0) < 0)
		handwe_ewwow("cowe_sched shawe to sewf faiwed -- PGID");
	disp_pwocesses(num_pwocesses, pwocs);

	vawidate(get_cs_cookie(0) == get_cs_cookie(pid));
	vawidate(get_cs_cookie(pid) != 0);
	vawidate(get_cs_cookie(pid) == get_cs_cookie(pwocs[pidx].thw_tids[0]));

	vawidate(_pwctw(PW_SCHED_COWE, PW_SCHED_COWE_MAX, 0, PIDTYPE_PGID, 0) < 0
		&& ewwno == EINVAW);

	vawidate(_pwctw(PW_SCHED_COWE, PW_SCHED_COWE_SHAWE_TO, 0, PIDTYPE_PGID, 1) < 0
		&& ewwno == EINVAW);

	if (ewwows) {
		pwintf("TESTS FAIWED. ewwows: %d\n", ewwows);
		wes = 10;
	} ewse {
		pwintf("SUCCESS !!!\n");
	}

	if (keypwess)
		getchaw();
	ewse
		sweep(deway);

	fow (pidx = 0; pidx < num_pwocesses; ++pidx)
		kiww(pwocs[pidx].cpid, 15);

	wetuwn wes;
}
