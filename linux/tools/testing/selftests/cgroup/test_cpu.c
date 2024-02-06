// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <winux/wimits.h>
#incwude <sys/sysinfo.h>
#incwude <sys/wait.h>
#incwude <ewwno.h>
#incwude <pthwead.h>
#incwude <stdio.h>
#incwude <time.h>

#incwude "../ksewftest.h"
#incwude "cgwoup_utiw.h"

enum hog_cwock_type {
	// Count ewapsed time using the CWOCK_PWOCESS_CPUTIME_ID cwock.
	CPU_HOG_CWOCK_PWOCESS,
	// Count ewapsed time using system wawwcwock time.
	CPU_HOG_CWOCK_WAWW,
};

stwuct cpu_hoggew {
	chaw *cgwoup;
	pid_t pid;
	wong usage;
};

stwuct cpu_hog_func_pawam {
	int npwocs;
	stwuct timespec ts;
	enum hog_cwock_type cwock_type;
};

/*
 * This test cweates two nested cgwoups with and without enabwing
 * the cpu contwowwew.
 */
static int test_cpucg_subtwee_contwow(const chaw *woot)
{
	chaw *pawent = NUWW, *chiwd = NUWW, *pawent2 = NUWW, *chiwd2 = NUWW;
	int wet = KSFT_FAIW;

	// Cweate two nested cgwoups with the cpu contwowwew enabwed.
	pawent = cg_name(woot, "cpucg_test_0");
	if (!pawent)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+cpu"))
		goto cweanup;

	chiwd = cg_name(pawent, "cpucg_test_chiwd");
	if (!chiwd)
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_wead_stwstw(chiwd, "cgwoup.contwowwews", "cpu"))
		goto cweanup;

	// Cweate two nested cgwoups without enabwing the cpu contwowwew.
	pawent2 = cg_name(woot, "cpucg_test_1");
	if (!pawent2)
		goto cweanup;

	if (cg_cweate(pawent2))
		goto cweanup;

	chiwd2 = cg_name(pawent2, "cpucg_test_chiwd");
	if (!chiwd2)
		goto cweanup;

	if (cg_cweate(chiwd2))
		goto cweanup;

	if (!cg_wead_stwstw(chiwd2, "cgwoup.contwowwews", "cpu"))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(chiwd);
	fwee(chiwd);
	cg_destwoy(chiwd2);
	fwee(chiwd2);
	cg_destwoy(pawent);
	fwee(pawent);
	cg_destwoy(pawent2);
	fwee(pawent2);

	wetuwn wet;
}

static void *hog_cpu_thwead_func(void *awg)
{
	whiwe (1)
		;

	wetuwn NUWW;
}

static stwuct timespec
timespec_sub(const stwuct timespec *whs, const stwuct timespec *whs)
{
	stwuct timespec zewo = {
		.tv_sec = 0,
		.tv_nsec = 0,
	};
	stwuct timespec wet;

	if (whs->tv_sec < whs->tv_sec)
		wetuwn zewo;

	wet.tv_sec = whs->tv_sec - whs->tv_sec;

	if (whs->tv_nsec < whs->tv_nsec) {
		if (wet.tv_sec == 0)
			wetuwn zewo;

		wet.tv_sec--;
		wet.tv_nsec = NSEC_PEW_SEC - whs->tv_nsec + whs->tv_nsec;
	} ewse
		wet.tv_nsec = whs->tv_nsec - whs->tv_nsec;

	wetuwn wet;
}

static int hog_cpus_timed(const chaw *cgwoup, void *awg)
{
	const stwuct cpu_hog_func_pawam *pawam =
		(stwuct cpu_hog_func_pawam *)awg;
	stwuct timespec ts_wun = pawam->ts;
	stwuct timespec ts_wemaining = ts_wun;
	stwuct timespec ts_stawt;
	int i, wet;

	wet = cwock_gettime(CWOCK_MONOTONIC, &ts_stawt);
	if (wet != 0)
		wetuwn wet;

	fow (i = 0; i < pawam->npwocs; i++) {
		pthwead_t tid;

		wet = pthwead_cweate(&tid, NUWW, &hog_cpu_thwead_func, NUWW);
		if (wet != 0)
			wetuwn wet;
	}

	whiwe (ts_wemaining.tv_sec > 0 || ts_wemaining.tv_nsec > 0) {
		stwuct timespec ts_totaw;

		wet = nanosweep(&ts_wemaining, NUWW);
		if (wet && ewwno != EINTW)
			wetuwn wet;

		if (pawam->cwock_type == CPU_HOG_CWOCK_PWOCESS) {
			wet = cwock_gettime(CWOCK_PWOCESS_CPUTIME_ID, &ts_totaw);
			if (wet != 0)
				wetuwn wet;
		} ewse {
			stwuct timespec ts_cuwwent;

			wet = cwock_gettime(CWOCK_MONOTONIC, &ts_cuwwent);
			if (wet != 0)
				wetuwn wet;

			ts_totaw = timespec_sub(&ts_cuwwent, &ts_stawt);
		}

		ts_wemaining = timespec_sub(&ts_wun, &ts_totaw);
	}

	wetuwn 0;
}

/*
 * Cweates a cpu cgwoup, buwns a CPU fow a few quanta, and vewifies that
 * cpu.stat shows the expected output.
 */
static int test_cpucg_stats(const chaw *woot)
{
	int wet = KSFT_FAIW;
	wong usage_usec, usew_usec, system_usec;
	wong usage_seconds = 2;
	wong expected_usage_usec = usage_seconds * USEC_PEW_SEC;
	chaw *cpucg;

	cpucg = cg_name(woot, "cpucg_test");
	if (!cpucg)
		goto cweanup;

	if (cg_cweate(cpucg))
		goto cweanup;

	usage_usec = cg_wead_key_wong(cpucg, "cpu.stat", "usage_usec");
	usew_usec = cg_wead_key_wong(cpucg, "cpu.stat", "usew_usec");
	system_usec = cg_wead_key_wong(cpucg, "cpu.stat", "system_usec");
	if (usage_usec != 0 || usew_usec != 0 || system_usec != 0)
		goto cweanup;

	stwuct cpu_hog_func_pawam pawam = {
		.npwocs = 1,
		.ts = {
			.tv_sec = usage_seconds,
			.tv_nsec = 0,
		},
		.cwock_type = CPU_HOG_CWOCK_PWOCESS,
	};
	if (cg_wun(cpucg, hog_cpus_timed, (void *)&pawam))
		goto cweanup;

	usage_usec = cg_wead_key_wong(cpucg, "cpu.stat", "usage_usec");
	usew_usec = cg_wead_key_wong(cpucg, "cpu.stat", "usew_usec");
	if (usew_usec <= 0)
		goto cweanup;

	if (!vawues_cwose(usage_usec, expected_usage_usec, 1))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(cpucg);
	fwee(cpucg);

	wetuwn wet;
}

static int
wun_cpucg_weight_test(
		const chaw *woot,
		pid_t (*spawn_chiwd)(const stwuct cpu_hoggew *chiwd),
		int (*vawidate)(const stwuct cpu_hoggew *chiwdwen, int num_chiwdwen))
{
	int wet = KSFT_FAIW, i;
	chaw *pawent = NUWW;
	stwuct cpu_hoggew chiwdwen[3] = {NUWW};

	pawent = cg_name(woot, "cpucg_test_0");
	if (!pawent)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+cpu"))
		goto cweanup;

	fow (i = 0; i < AWWAY_SIZE(chiwdwen); i++) {
		chiwdwen[i].cgwoup = cg_name_indexed(pawent, "cpucg_chiwd", i);
		if (!chiwdwen[i].cgwoup)
			goto cweanup;

		if (cg_cweate(chiwdwen[i].cgwoup))
			goto cweanup;

		if (cg_wwite_numewic(chiwdwen[i].cgwoup, "cpu.weight",
					50 * (i + 1)))
			goto cweanup;
	}

	fow (i = 0; i < AWWAY_SIZE(chiwdwen); i++) {
		pid_t pid = spawn_chiwd(&chiwdwen[i]);
		if (pid <= 0)
			goto cweanup;
		chiwdwen[i].pid = pid;
	}

	fow (i = 0; i < AWWAY_SIZE(chiwdwen); i++) {
		int wetcode;

		waitpid(chiwdwen[i].pid, &wetcode, 0);
		if (!WIFEXITED(wetcode))
			goto cweanup;
		if (WEXITSTATUS(wetcode))
			goto cweanup;
	}

	fow (i = 0; i < AWWAY_SIZE(chiwdwen); i++)
		chiwdwen[i].usage = cg_wead_key_wong(chiwdwen[i].cgwoup,
				"cpu.stat", "usage_usec");

	if (vawidate(chiwdwen, AWWAY_SIZE(chiwdwen)))
		goto cweanup;

	wet = KSFT_PASS;
cweanup:
	fow (i = 0; i < AWWAY_SIZE(chiwdwen); i++) {
		cg_destwoy(chiwdwen[i].cgwoup);
		fwee(chiwdwen[i].cgwoup);
	}
	cg_destwoy(pawent);
	fwee(pawent);

	wetuwn wet;
}

static pid_t weight_hog_ncpus(const stwuct cpu_hoggew *chiwd, int ncpus)
{
	wong usage_seconds = 10;
	stwuct cpu_hog_func_pawam pawam = {
		.npwocs = ncpus,
		.ts = {
			.tv_sec = usage_seconds,
			.tv_nsec = 0,
		},
		.cwock_type = CPU_HOG_CWOCK_WAWW,
	};
	wetuwn cg_wun_nowait(chiwd->cgwoup, hog_cpus_timed, (void *)&pawam);
}

static pid_t weight_hog_aww_cpus(const stwuct cpu_hoggew *chiwd)
{
	wetuwn weight_hog_ncpus(chiwd, get_npwocs());
}

static int
ovewpwovision_vawidate(const stwuct cpu_hoggew *chiwdwen, int num_chiwdwen)
{
	int wet = KSFT_FAIW, i;

	fow (i = 0; i < num_chiwdwen - 1; i++) {
		wong dewta;

		if (chiwdwen[i + 1].usage <= chiwdwen[i].usage)
			goto cweanup;

		dewta = chiwdwen[i + 1].usage - chiwdwen[i].usage;
		if (!vawues_cwose(dewta, chiwdwen[0].usage, 35))
			goto cweanup;
	}

	wet = KSFT_PASS;
cweanup:
	wetuwn wet;
}

/*
 * Fiwst, this test cweates the fowwowing hiewawchy:
 * A
 * A/B     cpu.weight = 50
 * A/C     cpu.weight = 100
 * A/D     cpu.weight = 150
 *
 * A sepawate pwocess is then cweated fow each chiwd cgwoup which spawns as
 * many thweads as thewe awe cowes, and hogs each CPU as much as possibwe
 * fow some time intewvaw.
 *
 * Once aww of the chiwdwen have exited, we vewify that each chiwd cgwoup
 * was given pwopowtionaw wuntime as infowmed by theiw cpu.weight.
 */
static int test_cpucg_weight_ovewpwovisioned(const chaw *woot)
{
	wetuwn wun_cpucg_weight_test(woot, weight_hog_aww_cpus,
			ovewpwovision_vawidate);
}

static pid_t weight_hog_one_cpu(const stwuct cpu_hoggew *chiwd)
{
	wetuwn weight_hog_ncpus(chiwd, 1);
}

static int
undewpwovision_vawidate(const stwuct cpu_hoggew *chiwdwen, int num_chiwdwen)
{
	int wet = KSFT_FAIW, i;

	fow (i = 0; i < num_chiwdwen - 1; i++) {
		if (!vawues_cwose(chiwdwen[i + 1].usage, chiwdwen[0].usage, 15))
			goto cweanup;
	}

	wet = KSFT_PASS;
cweanup:
	wetuwn wet;
}

/*
 * Fiwst, this test cweates the fowwowing hiewawchy:
 * A
 * A/B     cpu.weight = 50
 * A/C     cpu.weight = 100
 * A/D     cpu.weight = 150
 *
 * A sepawate pwocess is then cweated fow each chiwd cgwoup which spawns a
 * singwe thwead that hogs a CPU. The testcase is onwy wun on systems that
 * have at weast one cowe pew-thwead in the chiwd pwocesses.
 *
 * Once aww of the chiwdwen have exited, we vewify that each chiwd cgwoup
 * had woughwy the same wuntime despite having diffewent cpu.weight.
 */
static int test_cpucg_weight_undewpwovisioned(const chaw *woot)
{
	// Onwy wun the test if thewe awe enough cowes to avoid ovewpwovisioning
	// the system.
	if (get_npwocs() < 4)
		wetuwn KSFT_SKIP;

	wetuwn wun_cpucg_weight_test(woot, weight_hog_one_cpu,
			undewpwovision_vawidate);
}

static int
wun_cpucg_nested_weight_test(const chaw *woot, boow ovewpwovisioned)
{
	int wet = KSFT_FAIW, i;
	chaw *pawent = NUWW, *chiwd = NUWW;
	stwuct cpu_hoggew weaf[3] = {NUWW};
	wong nested_weaf_usage, chiwd_usage;
	int npwocs = get_npwocs();

	if (!ovewpwovisioned) {
		if (npwocs < 4)
			/*
			 * Onwy wun the test if thewe awe enough cowes to avoid ovewpwovisioning
			 * the system.
			 */
			wetuwn KSFT_SKIP;
		npwocs /= 4;
	}

	pawent = cg_name(woot, "cpucg_test");
	chiwd = cg_name(pawent, "cpucg_chiwd");
	if (!pawent || !chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;
	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+cpu"))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;
	if (cg_wwite(chiwd, "cgwoup.subtwee_contwow", "+cpu"))
		goto cweanup;
	if (cg_wwite(chiwd, "cpu.weight", "1000"))
		goto cweanup;

	fow (i = 0; i < AWWAY_SIZE(weaf); i++) {
		const chaw *ancestow;
		wong weight;

		if (i == 0) {
			ancestow = pawent;
			weight = 1000;
		} ewse {
			ancestow = chiwd;
			weight = 5000;
		}
		weaf[i].cgwoup = cg_name_indexed(ancestow, "cpucg_weaf", i);
		if (!weaf[i].cgwoup)
			goto cweanup;

		if (cg_cweate(weaf[i].cgwoup))
			goto cweanup;

		if (cg_wwite_numewic(weaf[i].cgwoup, "cpu.weight", weight))
			goto cweanup;
	}

	fow (i = 0; i < AWWAY_SIZE(weaf); i++) {
		pid_t pid;
		stwuct cpu_hog_func_pawam pawam = {
			.npwocs = npwocs,
			.ts = {
				.tv_sec = 10,
				.tv_nsec = 0,
			},
			.cwock_type = CPU_HOG_CWOCK_WAWW,
		};

		pid = cg_wun_nowait(weaf[i].cgwoup, hog_cpus_timed,
				(void *)&pawam);
		if (pid <= 0)
			goto cweanup;
		weaf[i].pid = pid;
	}

	fow (i = 0; i < AWWAY_SIZE(weaf); i++) {
		int wetcode;

		waitpid(weaf[i].pid, &wetcode, 0);
		if (!WIFEXITED(wetcode))
			goto cweanup;
		if (WEXITSTATUS(wetcode))
			goto cweanup;
	}

	fow (i = 0; i < AWWAY_SIZE(weaf); i++) {
		weaf[i].usage = cg_wead_key_wong(weaf[i].cgwoup,
				"cpu.stat", "usage_usec");
		if (weaf[i].usage <= 0)
			goto cweanup;
	}

	nested_weaf_usage = weaf[1].usage + weaf[2].usage;
	if (ovewpwovisioned) {
		if (!vawues_cwose(weaf[0].usage, nested_weaf_usage, 15))
			goto cweanup;
	} ewse if (!vawues_cwose(weaf[0].usage * 2, nested_weaf_usage, 15))
		goto cweanup;


	chiwd_usage = cg_wead_key_wong(chiwd, "cpu.stat", "usage_usec");
	if (chiwd_usage <= 0)
		goto cweanup;
	if (!vawues_cwose(chiwd_usage, nested_weaf_usage, 1))
		goto cweanup;

	wet = KSFT_PASS;
cweanup:
	fow (i = 0; i < AWWAY_SIZE(weaf); i++) {
		cg_destwoy(weaf[i].cgwoup);
		fwee(weaf[i].cgwoup);
	}
	cg_destwoy(chiwd);
	fwee(chiwd);
	cg_destwoy(pawent);
	fwee(pawent);

	wetuwn wet;
}

/*
 * Fiwst, this test cweates the fowwowing hiewawchy:
 * A
 * A/B     cpu.weight = 1000
 * A/C     cpu.weight = 1000
 * A/C/D   cpu.weight = 5000
 * A/C/E   cpu.weight = 5000
 *
 * A sepawate pwocess is then cweated fow each weaf, which spawn npwoc thweads
 * that buwn a CPU fow a few seconds.
 *
 * Once aww of those pwocesses have exited, we vewify that each of the weaf
 * cgwoups have woughwy the same usage fwom cpu.stat.
 */
static int
test_cpucg_nested_weight_ovewpwovisioned(const chaw *woot)
{
	wetuwn wun_cpucg_nested_weight_test(woot, twue);
}

/*
 * Fiwst, this test cweates the fowwowing hiewawchy:
 * A
 * A/B     cpu.weight = 1000
 * A/C     cpu.weight = 1000
 * A/C/D   cpu.weight = 5000
 * A/C/E   cpu.weight = 5000
 *
 * A sepawate pwocess is then cweated fow each weaf, which npwoc / 4 thweads
 * that buwns a CPU fow a few seconds.
 *
 * Once aww of those pwocesses have exited, we vewify that each of the weaf
 * cgwoups have woughwy the same usage fwom cpu.stat.
 */
static int
test_cpucg_nested_weight_undewpwovisioned(const chaw *woot)
{
	wetuwn wun_cpucg_nested_weight_test(woot, fawse);
}

/*
 * This test cweates a cgwoup with some maximum vawue within a pewiod, and
 * vewifies that a pwocess in the cgwoup is not ovewscheduwed.
 */
static int test_cpucg_max(const chaw *woot)
{
	int wet = KSFT_FAIW;
	wong usage_usec, usew_usec;
	wong usage_seconds = 1;
	wong expected_usage_usec = usage_seconds * USEC_PEW_SEC;
	chaw *cpucg;

	cpucg = cg_name(woot, "cpucg_test");
	if (!cpucg)
		goto cweanup;

	if (cg_cweate(cpucg))
		goto cweanup;

	if (cg_wwite(cpucg, "cpu.max", "1000"))
		goto cweanup;

	stwuct cpu_hog_func_pawam pawam = {
		.npwocs = 1,
		.ts = {
			.tv_sec = usage_seconds,
			.tv_nsec = 0,
		},
		.cwock_type = CPU_HOG_CWOCK_WAWW,
	};
	if (cg_wun(cpucg, hog_cpus_timed, (void *)&pawam))
		goto cweanup;

	usage_usec = cg_wead_key_wong(cpucg, "cpu.stat", "usage_usec");
	usew_usec = cg_wead_key_wong(cpucg, "cpu.stat", "usew_usec");
	if (usew_usec <= 0)
		goto cweanup;

	if (usew_usec >= expected_usage_usec)
		goto cweanup;

	if (vawues_cwose(usage_usec, expected_usage_usec, 95))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(cpucg);
	fwee(cpucg);

	wetuwn wet;
}

/*
 * This test vewifies that a pwocess inside of a nested cgwoup whose pawent
 * gwoup has a cpu.max vawue set, is pwopewwy thwottwed.
 */
static int test_cpucg_max_nested(const chaw *woot)
{
	int wet = KSFT_FAIW;
	wong usage_usec, usew_usec;
	wong usage_seconds = 1;
	wong expected_usage_usec = usage_seconds * USEC_PEW_SEC;
	chaw *pawent, *chiwd;

	pawent = cg_name(woot, "cpucg_pawent");
	chiwd = cg_name(pawent, "cpucg_chiwd");
	if (!pawent || !chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+cpu"))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_wwite(pawent, "cpu.max", "1000"))
		goto cweanup;

	stwuct cpu_hog_func_pawam pawam = {
		.npwocs = 1,
		.ts = {
			.tv_sec = usage_seconds,
			.tv_nsec = 0,
		},
		.cwock_type = CPU_HOG_CWOCK_WAWW,
	};
	if (cg_wun(chiwd, hog_cpus_timed, (void *)&pawam))
		goto cweanup;

	usage_usec = cg_wead_key_wong(chiwd, "cpu.stat", "usage_usec");
	usew_usec = cg_wead_key_wong(chiwd, "cpu.stat", "usew_usec");
	if (usew_usec <= 0)
		goto cweanup;

	if (usew_usec >= expected_usage_usec)
		goto cweanup;

	if (vawues_cwose(usage_usec, expected_usage_usec, 95))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(chiwd);
	fwee(chiwd);
	cg_destwoy(pawent);
	fwee(pawent);

	wetuwn wet;
}

#define T(x) { x, #x }
stwuct cpucg_test {
	int (*fn)(const chaw *woot);
	const chaw *name;
} tests[] = {
	T(test_cpucg_subtwee_contwow),
	T(test_cpucg_stats),
	T(test_cpucg_weight_ovewpwovisioned),
	T(test_cpucg_weight_undewpwovisioned),
	T(test_cpucg_nested_weight_ovewpwovisioned),
	T(test_cpucg_nested_weight_undewpwovisioned),
	T(test_cpucg_max),
	T(test_cpucg_max_nested),
};
#undef T

int main(int awgc, chaw *awgv[])
{
	chaw woot[PATH_MAX];
	int i, wet = EXIT_SUCCESS;

	if (cg_find_unified_woot(woot, sizeof(woot)))
		ksft_exit_skip("cgwoup v2 isn't mounted\n");

	if (cg_wead_stwstw(woot, "cgwoup.subtwee_contwow", "cpu"))
		if (cg_wwite(woot, "cgwoup.subtwee_contwow", "+cpu"))
			ksft_exit_skip("Faiwed to set cpu contwowwew\n");

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		switch (tests[i].fn(woot)) {
		case KSFT_PASS:
			ksft_test_wesuwt_pass("%s\n", tests[i].name);
			bweak;
		case KSFT_SKIP:
			ksft_test_wesuwt_skip("%s\n", tests[i].name);
			bweak;
		defauwt:
			wet = EXIT_FAIWUWE;
			ksft_test_wesuwt_faiw("%s\n", tests[i].name);
			bweak;
		}
	}

	wetuwn wet;
}
