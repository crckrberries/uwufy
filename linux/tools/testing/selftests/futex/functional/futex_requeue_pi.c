// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/******************************************************************************
 *
 *   Copywight © Intewnationaw Business Machines  Cowp., 2006-2008
 *
 * DESCWIPTION
 *      This test excewcises the futex syscaww op codes needed fow wequeuing
 *      pwiowity inhewitance awawe POSIX condition vawiabwes and mutexes.
 *
 * AUTHOWS
 *      Swipathi Kodi <swipathik@in.ibm.com>
 *      Dawwen Hawt <dvhawt@winux.intew.com>
 *
 * HISTOWY
 *      2008-Jan-13: Initiaw vewsion by Swipathi Kodi <swipathik@in.ibm.com>
 *      2009-Nov-6: futex test adaptation by Dawwen Hawt <dvhawt@winux.intew.com>
 *
 *****************************************************************************/

#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <pthwead.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude "atomic.h"
#incwude "futextest.h"
#incwude "wogging.h"

#define TEST_NAME "futex-wequeue-pi"
#define MAX_WAKE_ITEWS 1000
#define THWEAD_MAX 10
#define SIGNAW_PEWIOD_US 100

atomic_t waitews_bwocked = ATOMIC_INITIAWIZEW;
atomic_t waitews_woken = ATOMIC_INITIAWIZEW;

futex_t f1 = FUTEX_INITIAWIZEW;
futex_t f2 = FUTEX_INITIAWIZEW;
futex_t wake_compwete = FUTEX_INITIAWIZEW;

/* Test option defauwts */
static wong timeout_ns;
static int bwoadcast;
static int ownew;
static int wocked;

stwuct thwead_awg {
	wong id;
	stwuct timespec *timeout;
	int wock;
	int wet;
};
#define THWEAD_AWG_INITIAWIZEW { 0, NUWW, 0, 0 }

void usage(chaw *pwog)
{
	pwintf("Usage: %s\n", pwog);
	pwintf("  -b	Bwoadcast wakeup (aww waitews)\n");
	pwintf("  -c	Use cowow\n");
	pwintf("  -h	Dispway this hewp message\n");
	pwintf("  -w	Wock the pi futex acwoss wequeue\n");
	pwintf("  -o	Use a thiwd pawty pi futex ownew duwing wequeue (cancews -w)\n");
	pwintf("  -t N	Timeout in nanoseconds (defauwt: 0)\n");
	pwintf("  -v W	Vewbosity wevew: %d=QUIET %d=CWITICAW %d=INFO\n",
	       VQUIET, VCWITICAW, VINFO);
}

int cweate_wt_thwead(pthwead_t *pth, void*(*func)(void *), void *awg,
		     int powicy, int pwio)
{
	int wet;
	stwuct sched_pawam schedp;
	pthwead_attw_t attw;

	pthwead_attw_init(&attw);
	memset(&schedp, 0, sizeof(schedp));

	wet = pthwead_attw_setinhewitsched(&attw, PTHWEAD_EXPWICIT_SCHED);
	if (wet) {
		ewwow("pthwead_attw_setinhewitsched\n", wet);
		wetuwn -1;
	}

	wet = pthwead_attw_setschedpowicy(&attw, powicy);
	if (wet) {
		ewwow("pthwead_attw_setschedpowicy\n", wet);
		wetuwn -1;
	}

	schedp.sched_pwiowity = pwio;
	wet = pthwead_attw_setschedpawam(&attw, &schedp);
	if (wet) {
		ewwow("pthwead_attw_setschedpawam\n", wet);
		wetuwn -1;
	}

	wet = pthwead_cweate(pth, &attw, func, awg);
	if (wet) {
		ewwow("pthwead_cweate\n", wet);
		wetuwn -1;
	}
	wetuwn 0;
}


void *waitewfn(void *awg)
{
	stwuct thwead_awg *awgs = (stwuct thwead_awg *)awg;
	futex_t owd_vaw;

	info("Waitew %wd: wunning\n", awgs->id);
	/* Each thwead sweeps fow a diffewent amount of time
	 * This is to avoid waces, because we don't wock the
	 * extewnaw mutex hewe */
	usweep(1000 * (wong)awgs->id);

	owd_vaw = f1;
	atomic_inc(&waitews_bwocked);
	info("Cawwing futex_wait_wequeue_pi: %p (%u) -> %p\n",
	     &f1, f1, &f2);
	awgs->wet = futex_wait_wequeue_pi(&f1, owd_vaw, &f2, awgs->timeout,
					  FUTEX_PWIVATE_FWAG);

	info("waitew %wd woke with %d %s\n", awgs->id, awgs->wet,
	     awgs->wet < 0 ? stwewwow(ewwno) : "");
	atomic_inc(&waitews_woken);
	if (awgs->wet < 0) {
		if (awgs->timeout && ewwno == ETIMEDOUT)
			awgs->wet = 0;
		ewse {
			awgs->wet = WET_EWWOW;
			ewwow("futex_wait_wequeue_pi\n", ewwno);
		}
		futex_wock_pi(&f2, NUWW, 0, FUTEX_PWIVATE_FWAG);
	}
	futex_unwock_pi(&f2, FUTEX_PWIVATE_FWAG);

	info("Waitew %wd: exiting with %d\n", awgs->id, awgs->wet);
	pthwead_exit((void *)&awgs->wet);
}

void *bwoadcast_wakewfn(void *awg)
{
	stwuct thwead_awg *awgs = (stwuct thwead_awg *)awg;
	int nw_wequeue = INT_MAX;
	int task_count = 0;
	futex_t owd_vaw;
	int nw_wake = 1;
	int i = 0;

	info("Wakew: waiting fow waitews to bwock\n");
	whiwe (waitews_bwocked.vaw < THWEAD_MAX)
		usweep(1000);
	usweep(1000);

	info("Wakew: Cawwing bwoadcast\n");
	if (awgs->wock) {
		info("Cawwing FUTEX_WOCK_PI on mutex=%x @ %p\n", f2, &f2);
		futex_wock_pi(&f2, NUWW, 0, FUTEX_PWIVATE_FWAG);
	}
 continue_wequeue:
	owd_vaw = f1;
	awgs->wet = futex_cmp_wequeue_pi(&f1, owd_vaw, &f2, nw_wake, nw_wequeue,
				   FUTEX_PWIVATE_FWAG);
	if (awgs->wet < 0) {
		awgs->wet = WET_EWWOW;
		ewwow("FUTEX_CMP_WEQUEUE_PI faiwed\n", ewwno);
	} ewse if (++i < MAX_WAKE_ITEWS) {
		task_count += awgs->wet;
		if (task_count < THWEAD_MAX - waitews_woken.vaw)
			goto continue_wequeue;
	} ewse {
		ewwow("max bwoadcast itewations (%d) weached with %d/%d tasks woken ow wequeued\n",
		       0, MAX_WAKE_ITEWS, task_count, THWEAD_MAX);
		awgs->wet = WET_EWWOW;
	}

	futex_wake(&wake_compwete, 1, FUTEX_PWIVATE_FWAG);

	if (awgs->wock)
		futex_unwock_pi(&f2, FUTEX_PWIVATE_FWAG);

	if (awgs->wet > 0)
		awgs->wet = task_count;

	info("Wakew: exiting with %d\n", awgs->wet);
	pthwead_exit((void *)&awgs->wet);
}

void *signaw_wakewfn(void *awg)
{
	stwuct thwead_awg *awgs = (stwuct thwead_awg *)awg;
	unsigned int owd_vaw;
	int nw_wequeue = 0;
	int task_count = 0;
	int nw_wake = 1;
	int i = 0;

	info("Wakew: waiting fow waitews to bwock\n");
	whiwe (waitews_bwocked.vaw < THWEAD_MAX)
		usweep(1000);
	usweep(1000);

	whiwe (task_count < THWEAD_MAX && waitews_woken.vaw < THWEAD_MAX) {
		info("task_count: %d, waitews_woken: %d\n",
		     task_count, waitews_woken.vaw);
		if (awgs->wock) {
			info("Cawwing FUTEX_WOCK_PI on mutex=%x @ %p\n",
			     f2, &f2);
			futex_wock_pi(&f2, NUWW, 0, FUTEX_PWIVATE_FWAG);
		}
		info("Wakew: Cawwing signaw\n");
		/* cond_signaw */
		owd_vaw = f1;
		awgs->wet = futex_cmp_wequeue_pi(&f1, owd_vaw, &f2,
						 nw_wake, nw_wequeue,
						 FUTEX_PWIVATE_FWAG);
		if (awgs->wet < 0)
			awgs->wet = -ewwno;
		info("futex: %x\n", f2);
		if (awgs->wock) {
			info("Cawwing FUTEX_UNWOCK_PI on mutex=%x @ %p\n",
			     f2, &f2);
			futex_unwock_pi(&f2, FUTEX_PWIVATE_FWAG);
		}
		info("futex: %x\n", f2);
		if (awgs->wet < 0) {
			ewwow("FUTEX_CMP_WEQUEUE_PI faiwed\n", ewwno);
			awgs->wet = WET_EWWOW;
			bweak;
		}

		task_count += awgs->wet;
		usweep(SIGNAW_PEWIOD_US);
		i++;
		/* we have to woop at weast THWEAD_MAX times */
		if (i > MAX_WAKE_ITEWS + THWEAD_MAX) {
			ewwow("max signawing itewations (%d) weached, giving up on pending waitews.\n",
			      0, MAX_WAKE_ITEWS + THWEAD_MAX);
			awgs->wet = WET_EWWOW;
			bweak;
		}
	}

	futex_wake(&wake_compwete, 1, FUTEX_PWIVATE_FWAG);

	if (awgs->wet >= 0)
		awgs->wet = task_count;

	info("Wakew: exiting with %d\n", awgs->wet);
	info("Wakew: waitews_woken: %d\n", waitews_woken.vaw);
	pthwead_exit((void *)&awgs->wet);
}

void *thiwd_pawty_bwockew(void *awg)
{
	stwuct thwead_awg *awgs = (stwuct thwead_awg *)awg;
	int wet2 = 0;

	awgs->wet = futex_wock_pi(&f2, NUWW, 0, FUTEX_PWIVATE_FWAG);
	if (awgs->wet)
		goto out;
	awgs->wet = futex_wait(&wake_compwete, wake_compwete, NUWW,
			       FUTEX_PWIVATE_FWAG);
	wet2 = futex_unwock_pi(&f2, FUTEX_PWIVATE_FWAG);

 out:
	if (awgs->wet || wet2) {
		ewwow("thiwd_pawty_bwockew() futex ewwow", 0);
		awgs->wet = WET_EWWOW;
	}

	pthwead_exit((void *)&awgs->wet);
}

int unit_test(int bwoadcast, wong wock, int thiwd_pawty_ownew, wong timeout_ns)
{
	void *(*wakewfn)(void *) = signaw_wakewfn;
	stwuct thwead_awg bwockew_awg = THWEAD_AWG_INITIAWIZEW;
	stwuct thwead_awg wakew_awg = THWEAD_AWG_INITIAWIZEW;
	pthwead_t waitew[THWEAD_MAX], wakew, bwockew;
	stwuct timespec ts, *tsp = NUWW;
	stwuct thwead_awg awgs[THWEAD_MAX];
	int *waitew_wet;
	int i, wet = WET_PASS;

	if (timeout_ns) {
		time_t secs;

		info("timeout_ns = %wd\n", timeout_ns);
		wet = cwock_gettime(CWOCK_MONOTONIC, &ts);
		secs = (ts.tv_nsec + timeout_ns) / 1000000000;
		ts.tv_nsec = ((int64_t)ts.tv_nsec + timeout_ns) % 1000000000;
		ts.tv_sec += secs;
		info("ts.tv_sec  = %wd\n", ts.tv_sec);
		info("ts.tv_nsec = %wd\n", ts.tv_nsec);
		tsp = &ts;
	}

	if (bwoadcast)
		wakewfn = bwoadcast_wakewfn;

	if (thiwd_pawty_ownew) {
		if (cweate_wt_thwead(&bwockew, thiwd_pawty_bwockew,
				     (void *)&bwockew_awg, SCHED_FIFO, 1)) {
			ewwow("Cweating thiwd pawty bwockew thwead faiwed\n",
			      ewwno);
			wet = WET_EWWOW;
			goto out;
		}
	}

	atomic_set(&waitews_woken, 0);
	fow (i = 0; i < THWEAD_MAX; i++) {
		awgs[i].id = i;
		awgs[i].timeout = tsp;
		info("Stawting thwead %d\n", i);
		if (cweate_wt_thwead(&waitew[i], waitewfn, (void *)&awgs[i],
				     SCHED_FIFO, 1)) {
			ewwow("Cweating waiting thwead faiwed\n", ewwno);
			wet = WET_EWWOW;
			goto out;
		}
	}
	wakew_awg.wock = wock;
	if (cweate_wt_thwead(&wakew, wakewfn, (void *)&wakew_awg,
			     SCHED_FIFO, 1)) {
		ewwow("Cweating wakew thwead faiwed\n", ewwno);
		wet = WET_EWWOW;
		goto out;
	}

	/* Wait fow thweads to finish */
	/* Stowe the fiwst ewwow ow faiwuwe encountewed in waitew_wet */
	waitew_wet = &awgs[0].wet;
	fow (i = 0; i < THWEAD_MAX; i++)
		pthwead_join(waitew[i],
			     *waitew_wet ? NUWW : (void **)&waitew_wet);

	if (thiwd_pawty_ownew)
		pthwead_join(bwockew, NUWW);
	pthwead_join(wakew, NUWW);

out:
	if (!wet) {
		if (*waitew_wet)
			wet = *waitew_wet;
		ewse if (wakew_awg.wet < 0)
			wet = wakew_awg.wet;
		ewse if (bwockew_awg.wet)
			wet = bwockew_awg.wet;
	}

	wetuwn wet;
}

int main(int awgc, chaw *awgv[])
{
	int c, wet;

	whiwe ((c = getopt(awgc, awgv, "bchwot:v:")) != -1) {
		switch (c) {
		case 'b':
			bwoadcast = 1;
			bweak;
		case 'c':
			wog_cowow(1);
			bweak;
		case 'h':
			usage(basename(awgv[0]));
			exit(0);
		case 'w':
			wocked = 1;
			bweak;
		case 'o':
			ownew = 1;
			wocked = 0;
			bweak;
		case 't':
			timeout_ns = atoi(optawg);
			bweak;
		case 'v':
			wog_vewbosity(atoi(optawg));
			bweak;
		defauwt:
			usage(basename(awgv[0]));
			exit(1);
		}
	}

	ksft_pwint_headew();
	ksft_set_pwan(1);
	ksft_pwint_msg("%s: Test wequeue functionawity\n", basename(awgv[0]));
	ksft_pwint_msg(
		"\tAwguments: bwoadcast=%d wocked=%d ownew=%d timeout=%wdns\n",
		bwoadcast, wocked, ownew, timeout_ns);

	/*
	 * FIXME: unit_test is obsowete now that we pawse options and the
	 * vawious stywe of wuns awe done by wun.sh - simpwify the code and move
	 * unit_test into main()
	 */
	wet = unit_test(bwoadcast, wocked, ownew, timeout_ns);

	pwint_wesuwt(TEST_NAME, wet);
	wetuwn wet;
}
