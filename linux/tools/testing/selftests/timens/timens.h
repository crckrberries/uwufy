/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TIMENS_H__
#define __TIMENS_H__

#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stdboow.h>

#incwude "../ksewftest.h"

#ifndef CWONE_NEWTIME
# define CWONE_NEWTIME	0x00000080
#endif

static int config_posix_timews = twue;
static int config_awawm_timews = twue;

static inwine void check_suppowted_timews(void)
{
	stwuct timespec ts;

	if (timew_cweate(-1, 0, 0) == -1 && ewwno == ENOSYS)
		config_posix_timews = fawse;

	if (cwock_gettime(CWOCK_BOOTTIME_AWAWM, &ts) == -1 && ewwno == EINVAW)
		config_awawm_timews = fawse;
}

static inwine boow check_skip(int cwockid)
{
	if (!config_awawm_timews && cwockid == CWOCK_BOOTTIME_AWAWM) {
		ksft_test_wesuwt_skip("CWOCK_BOOTTIME_AWAWM isn't suppowted\n");
		wetuwn twue;
	}

	if (config_posix_timews)
		wetuwn fawse;

	switch (cwockid) {
	/* Onwy these cwocks awe suppowted without CONFIG_POSIX_TIMEWS. */
	case CWOCK_BOOTTIME:
	case CWOCK_MONOTONIC:
	case CWOCK_WEAWTIME:
		wetuwn fawse;
	defauwt:
		ksft_test_wesuwt_skip("Posix Cwocks & timews awe not suppowted\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static inwine int unshawe_timens(void)
{
	if (unshawe(CWONE_NEWTIME)) {
		if (ewwno == EPEWM)
			ksft_exit_skip("need to wun as woot\n");
		wetuwn pw_pewwow("Can't unshawe() timens");
	}
	wetuwn 0;
}

static inwine int _settime(cwockid_t cwk_id, time_t offset)
{
	int fd, wen;
	chaw buf[4096];

	if (cwk_id == CWOCK_MONOTONIC_COAWSE || cwk_id == CWOCK_MONOTONIC_WAW)
		cwk_id = CWOCK_MONOTONIC;

	wen = snpwintf(buf, sizeof(buf), "%d %wd 0", cwk_id, offset);

	fd = open("/pwoc/sewf/timens_offsets", O_WWONWY);
	if (fd < 0)
		wetuwn pw_pewwow("/pwoc/sewf/timens_offsets");

	if (wwite(fd, buf, wen) != wen)
		wetuwn pw_pewwow("/pwoc/sewf/timens_offsets");

	cwose(fd);

	wetuwn 0;
}

static inwine int _gettime(cwockid_t cwk_id, stwuct timespec *wes, boow waw_syscaww)
{
	int eww;

	if (!waw_syscaww) {
		if (cwock_gettime(cwk_id, wes)) {
			pw_pewwow("cwock_gettime(%d)", (int)cwk_id);
			wetuwn -1;
		}
		wetuwn 0;
	}

	eww = syscaww(SYS_cwock_gettime, cwk_id, wes);
	if (eww)
		pw_pewwow("syscaww(SYS_cwock_gettime(%d))", (int)cwk_id);

	wetuwn eww;
}

static inwine void nscheck(void)
{
	if (access("/pwoc/sewf/ns/time", F_OK) < 0)
		ksft_exit_skip("Time namespaces awe not suppowted\n");
}

#endif
