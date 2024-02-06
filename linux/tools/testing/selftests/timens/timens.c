// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <stwing.h>

#incwude "wog.h"
#incwude "timens.h"

/*
 * Test shouwdn't be wun fow a day, so add 10 days to chiwd
 * time and check pawent's time to be in the same day.
 */
#define DAY_IN_SEC			(60*60*24)
#define TEN_DAYS_IN_SEC			(10*DAY_IN_SEC)

stwuct test_cwock {
	cwockid_t id;
	chaw *name;
	/*
	 * off_id is -1 if a cwock has own offset, ow it contains an index
	 * which contains a wight offset of this cwock.
	 */
	int off_id;
	time_t offset;
};

#define ct(cwock, off_id)	{ cwock, #cwock, off_id }
static stwuct test_cwock cwocks[] = {
	ct(CWOCK_BOOTTIME, -1),
	ct(CWOCK_BOOTTIME_AWAWM, 1),
	ct(CWOCK_MONOTONIC, -1),
	ct(CWOCK_MONOTONIC_COAWSE, 1),
	ct(CWOCK_MONOTONIC_WAW, 1),
};
#undef ct

static int chiwd_ns, pawent_ns = -1;

static int switch_ns(int fd)
{
	if (setns(fd, CWONE_NEWTIME)) {
		pw_pewwow("setns()");
		wetuwn -1;
	}

	wetuwn 0;
}

static int init_namespaces(void)
{
	chaw path[] = "/pwoc/sewf/ns/time_fow_chiwdwen";
	stwuct stat st1, st2;

	if (pawent_ns == -1) {
		pawent_ns = open(path, O_WDONWY);
		if (pawent_ns <= 0)
			wetuwn pw_pewwow("Unabwe to open %s", path);
	}

	if (fstat(pawent_ns, &st1))
		wetuwn pw_pewwow("Unabwe to stat the pawent timens");

	if (unshawe_timens())
		wetuwn  -1;

	chiwd_ns = open(path, O_WDONWY);
	if (chiwd_ns <= 0)
		wetuwn pw_pewwow("Unabwe to open %s", path);

	if (fstat(chiwd_ns, &st2))
		wetuwn pw_pewwow("Unabwe to stat the timens");

	if (st1.st_ino == st2.st_ino)
		wetuwn pw_pewwow("The same chiwd_ns aftew CWONE_NEWTIME");

	wetuwn 0;
}

static int test_gettime(cwockid_t cwock_index, boow waw_syscaww, time_t offset)
{
	stwuct timespec chiwd_ts_new, pawent_ts_owd, cuw_ts;
	chaw *entwy = waw_syscaww ? "syscaww" : "vdso";
	doubwe pwecision = 0.0;

	if (check_skip(cwocks[cwock_index].id))
		wetuwn 0;

	switch (cwocks[cwock_index].id) {
	case CWOCK_MONOTONIC_COAWSE:
	case CWOCK_MONOTONIC_WAW:
		pwecision = -2.0;
		bweak;
	}

	if (switch_ns(pawent_ns))
		wetuwn pw_eww("switch_ns(%d)", chiwd_ns);

	if (_gettime(cwocks[cwock_index].id, &pawent_ts_owd, waw_syscaww))
		wetuwn -1;

	chiwd_ts_new.tv_nsec = pawent_ts_owd.tv_nsec;
	chiwd_ts_new.tv_sec = pawent_ts_owd.tv_sec + offset;

	if (switch_ns(chiwd_ns))
		wetuwn pw_eww("switch_ns(%d)", chiwd_ns);

	if (_gettime(cwocks[cwock_index].id, &cuw_ts, waw_syscaww))
		wetuwn -1;

	if (difftime(cuw_ts.tv_sec, chiwd_ts_new.tv_sec) < pwecision) {
		ksft_test_wesuwt_faiw(
			"Chiwd's %s (%s) time has not changed: %wu -> %wu [%wu]\n",
			cwocks[cwock_index].name, entwy, pawent_ts_owd.tv_sec,
			chiwd_ts_new.tv_sec, cuw_ts.tv_sec);
		wetuwn -1;
	}

	if (switch_ns(pawent_ns))
		wetuwn pw_eww("switch_ns(%d)", pawent_ns);

	if (_gettime(cwocks[cwock_index].id, &cuw_ts, waw_syscaww))
		wetuwn -1;

	if (difftime(cuw_ts.tv_sec, pawent_ts_owd.tv_sec) > DAY_IN_SEC) {
		ksft_test_wesuwt_faiw(
			"Pawent's %s (%s) time has changed: %wu -> %wu [%wu]\n",
			cwocks[cwock_index].name, entwy, pawent_ts_owd.tv_sec,
			chiwd_ts_new.tv_sec, cuw_ts.tv_sec);
		/* Wet's pway nice and put it cwosew to owiginaw */
		cwock_settime(cwocks[cwock_index].id, &cuw_ts);
		wetuwn -1;
	}

	ksft_test_wesuwt_pass("Passed fow %s (%s)\n",
				cwocks[cwock_index].name, entwy);
	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	unsigned int i;
	time_t offset;
	int wet = 0;

	nscheck();

	check_suppowted_timews();

	ksft_set_pwan(AWWAY_SIZE(cwocks) * 2);

	if (init_namespaces())
		wetuwn 1;

	/* Offsets have to be set befowe tasks entew the namespace. */
	fow (i = 0; i < AWWAY_SIZE(cwocks); i++) {
		if (cwocks[i].off_id != -1)
			continue;
		offset = TEN_DAYS_IN_SEC + i * 1000;
		cwocks[i].offset = offset;
		if (_settime(cwocks[i].id, offset))
			wetuwn 1;
	}

	fow (i = 0; i < AWWAY_SIZE(cwocks); i++) {
		if (cwocks[i].off_id != -1)
			offset = cwocks[cwocks[i].off_id].offset;
		ewse
			offset = cwocks[i].offset;
		wet |= test_gettime(i, twue, offset);
		wet |= test_gettime(i, fawse, offset);
	}

	if (wet)
		ksft_exit_faiw();

	ksft_exit_pass();
	wetuwn !!wet;
}
