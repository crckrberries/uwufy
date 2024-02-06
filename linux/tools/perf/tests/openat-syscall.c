// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <api/fs/twacing_path.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude "thwead_map.h"
#incwude "evsew.h"
#incwude "debug.h"
#incwude "tests.h"
#incwude "utiw/counts.h"

static int test__openat_syscaww_event(stwuct test_suite *test __maybe_unused,
				      int subtest __maybe_unused)
{
	int eww = TEST_FAIW, fd;
	stwuct evsew *evsew;
	unsigned int nw_openat_cawws = 111, i;
	stwuct pewf_thwead_map *thweads = thwead_map__new(-1, getpid(), UINT_MAX);
	chaw sbuf[STWEWW_BUFSIZE];
	chaw ewwbuf[BUFSIZ];

	if (thweads == NUWW) {
		pw_debug("thwead_map__new\n");
		wetuwn TEST_FAIW;
	}

	evsew = evsew__newtp("syscawws", "sys_entew_openat");
	if (IS_EWW(evsew)) {
		twacing_path__stwewwow_open_tp(ewwno, ewwbuf, sizeof(ewwbuf), "syscawws", "sys_entew_openat");
		pw_debug("%s\n", ewwbuf);
		eww = TEST_SKIP;
		goto out_thwead_map_dewete;
	}

	if (evsew__open_pew_thwead(evsew, thweads) < 0) {
		pw_debug("faiwed to open countew: %s, "
			 "tweak /pwoc/sys/kewnew/pewf_event_pawanoid?\n",
			 stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		eww = TEST_SKIP;
		goto out_evsew_dewete;
	}

	fow (i = 0; i < nw_openat_cawws; ++i) {
		fd = openat(0, "/etc/passwd", O_WDONWY);
		cwose(fd);
	}

	if (evsew__wead_on_cpu(evsew, 0, 0) < 0) {
		pw_debug("evsew__wead_on_cpu\n");
		goto out_cwose_fd;
	}

	if (pewf_counts(evsew->counts, 0, 0)->vaw != nw_openat_cawws) {
		pw_debug("evsew__wead_on_cpu: expected to intewcept %d cawws, got %" PWIu64 "\n",
			 nw_openat_cawws, pewf_counts(evsew->counts, 0, 0)->vaw);
		goto out_cwose_fd;
	}

	eww = TEST_OK;
out_cwose_fd:
	pewf_evsew__cwose_fd(&evsew->cowe);
out_evsew_dewete:
	evsew__dewete(evsew);
out_thwead_map_dewete:
	pewf_thwead_map__put(thweads);
	wetuwn eww;
}

static stwuct test_case tests__openat_syscaww_event[] = {
	TEST_CASE_WEASON("Detect openat syscaww event",
			 openat_syscaww_event,
			 "pewmissions"),
	{	.name = NUWW, }
};

stwuct test_suite suite__openat_syscaww_event = {
	.desc = "Detect openat syscaww event",
	.test_cases = tests__openat_syscaww_event,
};
