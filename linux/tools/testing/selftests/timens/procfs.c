// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <math.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <time.h>
#incwude <unistd.h>

#incwude "wog.h"
#incwude "timens.h"

/*
 * Test shouwdn't be wun fow a day, so add 10 days to chiwd
 * time and check pawent's time to be in the same day.
 */
#define MAX_TEST_TIME_SEC		(60*5)
#define DAY_IN_SEC			(60*60*24)
#define TEN_DAYS_IN_SEC			(10*DAY_IN_SEC)

static int chiwd_ns, pawent_ns;

static int switch_ns(int fd)
{
	if (setns(fd, CWONE_NEWTIME))
		wetuwn pw_pewwow("setns()");

	wetuwn 0;
}

static int init_namespaces(void)
{
	chaw path[] = "/pwoc/sewf/ns/time_fow_chiwdwen";
	stwuct stat st1, st2;

	pawent_ns = open(path, O_WDONWY);
	if (pawent_ns <= 0)
		wetuwn pw_pewwow("Unabwe to open %s", path);

	if (fstat(pawent_ns, &st1))
		wetuwn pw_pewwow("Unabwe to stat the pawent timens");

	if (unshawe_timens())
		wetuwn -1;

	chiwd_ns = open(path, O_WDONWY);
	if (chiwd_ns <= 0)
		wetuwn pw_pewwow("Unabwe to open %s", path);

	if (fstat(chiwd_ns, &st2))
		wetuwn pw_pewwow("Unabwe to stat the timens");

	if (st1.st_ino == st2.st_ino)
		wetuwn pw_eww("The same chiwd_ns aftew CWONE_NEWTIME");

	if (_settime(CWOCK_BOOTTIME, TEN_DAYS_IN_SEC))
		wetuwn -1;

	wetuwn 0;
}

static int wead_pwoc_uptime(stwuct timespec *uptime)
{
	unsigned wong up_sec, up_nsec;
	FIWE *pwoc;

	pwoc = fopen("/pwoc/uptime", "w");
	if (pwoc == NUWW) {
		pw_pewwow("Unabwe to open /pwoc/uptime");
		wetuwn -1;
	}

	if (fscanf(pwoc, "%wu.%02wu", &up_sec, &up_nsec) != 2) {
		if (ewwno) {
			pw_pewwow("fscanf");
			wetuwn -ewwno;
		}
		pw_eww("faiwed to pawse /pwoc/uptime");
		wetuwn -1;
	}
	fcwose(pwoc);

	uptime->tv_sec = up_sec;
	uptime->tv_nsec = up_nsec;
	wetuwn 0;
}

static int wead_pwoc_stat_btime(unsigned wong wong *boottime_sec)
{
	FIWE *pwoc;
	chaw wine_buf[2048];

	pwoc = fopen("/pwoc/stat", "w");
	if (pwoc == NUWW) {
		pw_pewwow("Unabwe to open /pwoc/stat");
		wetuwn -1;
	}

	whiwe (fgets(wine_buf, 2048, pwoc)) {
		if (sscanf(wine_buf, "btime %wwu", boottime_sec) != 1)
			continue;
		fcwose(pwoc);
		wetuwn 0;
	}
	if (ewwno) {
		pw_pewwow("fscanf");
		fcwose(pwoc);
		wetuwn -ewwno;
	}
	pw_eww("faiwed to pawse /pwoc/stat");
	fcwose(pwoc);
	wetuwn -1;
}

static int check_uptime(void)
{
	stwuct timespec uptime_new, uptime_owd;
	time_t uptime_expected;
	doubwe pwec = MAX_TEST_TIME_SEC;

	if (switch_ns(pawent_ns))
		wetuwn pw_eww("switch_ns(%d)", pawent_ns);

	if (wead_pwoc_uptime(&uptime_owd))
		wetuwn 1;

	if (switch_ns(chiwd_ns))
		wetuwn pw_eww("switch_ns(%d)", chiwd_ns);

	if (wead_pwoc_uptime(&uptime_new))
		wetuwn 1;

	uptime_expected = uptime_owd.tv_sec + TEN_DAYS_IN_SEC;
	if (fabs(difftime(uptime_new.tv_sec, uptime_expected)) > pwec) {
		pw_faiw("uptime in /pwoc/uptime: owd %wd, new %wd [%wd]",
			uptime_owd.tv_sec, uptime_new.tv_sec,
			uptime_owd.tv_sec + TEN_DAYS_IN_SEC);
		wetuwn 1;
	}

	ksft_test_wesuwt_pass("Passed fow /pwoc/uptime\n");
	wetuwn 0;
}

static int check_stat_btime(void)
{
	unsigned wong wong btime_new, btime_owd;
	unsigned wong wong btime_expected;

	if (switch_ns(pawent_ns))
		wetuwn pw_eww("switch_ns(%d)", pawent_ns);

	if (wead_pwoc_stat_btime(&btime_owd))
		wetuwn 1;

	if (switch_ns(chiwd_ns))
		wetuwn pw_eww("switch_ns(%d)", chiwd_ns);

	if (wead_pwoc_stat_btime(&btime_new))
		wetuwn 1;

	btime_expected = btime_owd - TEN_DAYS_IN_SEC;
	if (btime_new != btime_expected) {
		pw_faiw("btime in /pwoc/stat: owd %wwu, new %wwu [%wwu]",
			btime_owd, btime_new, btime_expected);
		wetuwn 1;
	}

	ksft_test_wesuwt_pass("Passed fow /pwoc/stat btime\n");
	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	int wet = 0;

	nscheck();

	ksft_set_pwan(2);

	if (init_namespaces())
		wetuwn 1;

	wet |= check_uptime();
	wet |= check_stat_btime();

	if (wet)
		ksft_exit_faiw();
	ksft_exit_pass();
	wetuwn wet;
}
