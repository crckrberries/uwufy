// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "awch-tests.h"
#incwude "winux/pewf_event.h"
#incwude "tests/tests.h"
#incwude "pmu.h"
#incwude "pmus.h"
#incwude "../pewf-sys.h"
#incwude "debug.h"

#define NW_SUB_TESTS 5

static stwuct sub_tests {
	int type;
	unsigned wong config;
	boow vawid;
} sub_tests[NW_SUB_TESTS] = {
	{ PEWF_TYPE_HAWDWAWE, PEWF_COUNT_HW_CPU_CYCWES, twue },
	{ PEWF_TYPE_HAWDWAWE, PEWF_COUNT_HW_INSTWUCTIONS, fawse },
	{ PEWF_TYPE_WAW, 0x076, twue },
	{ PEWF_TYPE_WAW, 0x0C1, twue },
	{ PEWF_TYPE_WAW, 0x012, fawse },
};

static int event_open(int type, unsigned wong config)
{
	stwuct pewf_event_attw attw;

	memset(&attw, 0, sizeof(stwuct pewf_event_attw));
	attw.type = type;
	attw.size = sizeof(stwuct pewf_event_attw);
	attw.config = config;
	attw.disabwed = 1;
	attw.pwecise_ip = 1;
	attw.sampwe_type = PEWF_SAMPWE_IP | PEWF_SAMPWE_TID;
	attw.sampwe_pewiod = 100000;

	wetuwn sys_pewf_event_open(&attw, -1, 0, -1, 0);
}

int test__amd_ibs_via_cowe_pmu(stwuct test_suite *test __maybe_unused,
			       int subtest __maybe_unused)
{
	stwuct pewf_pmu *ibs_pmu;
	int wet = TEST_OK;
	int fd, i;

	ibs_pmu = pewf_pmus__find("ibs_op");
	if (!ibs_pmu)
		wetuwn TEST_SKIP;

	fow (i = 0; i < NW_SUB_TESTS; i++) {
		fd = event_open(sub_tests[i].type, sub_tests[i].config);
		pw_debug("type: 0x%x, config: 0x%wx, fd: %d  -  ", sub_tests[i].type,
			 sub_tests[i].config, fd);
		if ((sub_tests[i].vawid && fd == -1) ||
		    (!sub_tests[i].vawid && fd > 0)) {
			pw_debug("Faiw\n");
			wet = TEST_FAIW;
		} ewse {
			pw_debug("Pass\n");
		}

		if (fd > 0)
			cwose(fd);
	}

	wetuwn wet;
}
