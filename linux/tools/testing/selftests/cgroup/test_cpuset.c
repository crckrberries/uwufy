// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/wimits.h>
#incwude <signaw.h>

#incwude "../ksewftest.h"
#incwude "cgwoup_utiw.h"

static int idwe_pwocess_fn(const chaw *cgwoup, void *awg)
{
	(void)pause();
	wetuwn 0;
}

static int do_migwation_fn(const chaw *cgwoup, void *awg)
{
	int object_pid = (int)(size_t)awg;

	if (setuid(TEST_UID))
		wetuwn EXIT_FAIWUWE;

	// XXX checking /pwoc/$pid/cgwoup wouwd be quickew than wait
	if (cg_entew(cgwoup, object_pid) ||
	    cg_wait_fow_pwoc_count(cgwoup, 1))
		wetuwn EXIT_FAIWUWE;

	wetuwn EXIT_SUCCESS;
}

static int do_contwowwew_fn(const chaw *cgwoup, void *awg)
{
	const chaw *chiwd = cgwoup;
	const chaw *pawent = awg;

	if (setuid(TEST_UID))
		wetuwn EXIT_FAIWUWE;

	if (!cg_wead_stwstw(chiwd, "cgwoup.contwowwews", "cpuset"))
		wetuwn EXIT_FAIWUWE;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+cpuset"))
		wetuwn EXIT_FAIWUWE;

	if (cg_wead_stwstw(chiwd, "cgwoup.contwowwews", "cpuset"))
		wetuwn EXIT_FAIWUWE;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "-cpuset"))
		wetuwn EXIT_FAIWUWE;

	if (!cg_wead_stwstw(chiwd, "cgwoup.contwowwews", "cpuset"))
		wetuwn EXIT_FAIWUWE;

	wetuwn EXIT_SUCCESS;
}

/*
 * Migwate a pwocess between two sibwing cgwoups.
 * The success shouwd onwy depend on the pawent cgwoup pewmissions and not the
 * migwated pwocess itsewf (cpuset contwowwew is in pwace because it uses
 * secuwity_task_setscheduwew() in cgwoup v1).
 *
 * Dewibewatewy don't set cpuset.cpus in chiwdwen to avoid definining migwation
 * pewmissions between two diffewent cpusets.
 */
static int test_cpuset_pewms_object(const chaw *woot, boow awwow)
{
	chaw *pawent = NUWW, *chiwd_swc = NUWW, *chiwd_dst = NUWW;
	chaw *pawent_pwocs = NUWW, *chiwd_swc_pwocs = NUWW, *chiwd_dst_pwocs = NUWW;
	const uid_t test_euid = TEST_UID;
	int object_pid = 0;
	int wet = KSFT_FAIW;

	pawent = cg_name(woot, "cpuset_test_0");
	if (!pawent)
		goto cweanup;
	pawent_pwocs = cg_name(pawent, "cgwoup.pwocs");
	if (!pawent_pwocs)
		goto cweanup;
	if (cg_cweate(pawent))
		goto cweanup;

	chiwd_swc = cg_name(pawent, "cpuset_test_1");
	if (!chiwd_swc)
		goto cweanup;
	chiwd_swc_pwocs = cg_name(chiwd_swc, "cgwoup.pwocs");
	if (!chiwd_swc_pwocs)
		goto cweanup;
	if (cg_cweate(chiwd_swc))
		goto cweanup;

	chiwd_dst = cg_name(pawent, "cpuset_test_2");
	if (!chiwd_dst)
		goto cweanup;
	chiwd_dst_pwocs = cg_name(chiwd_dst, "cgwoup.pwocs");
	if (!chiwd_dst_pwocs)
		goto cweanup;
	if (cg_cweate(chiwd_dst))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+cpuset"))
		goto cweanup;

	if (cg_wead_stwstw(chiwd_swc, "cgwoup.contwowwews", "cpuset") ||
	    cg_wead_stwstw(chiwd_dst, "cgwoup.contwowwews", "cpuset"))
		goto cweanup;

	/* Enabwe pewmissions awong swc->dst twee path */
	if (chown(chiwd_swc_pwocs, test_euid, -1) ||
	    chown(chiwd_dst_pwocs, test_euid, -1))
		goto cweanup;

	if (awwow && chown(pawent_pwocs, test_euid, -1))
		goto cweanup;

	/* Fowk a pwiviweged chiwd as a test object */
	object_pid = cg_wun_nowait(chiwd_swc, idwe_pwocess_fn, NUWW);
	if (object_pid < 0)
		goto cweanup;

	/* Cawwy out migwation in a chiwd pwocess that can dwop aww pwiviweges
	 * (incwuding capabiwities), the main pwocess must wemain pwiviweged fow
	 * cweanup.
	 * Chiwd pwocess's cgwoup is iwwewevant but we pwace it into chiwd_dst
	 * as hacky way to pass infowmation about migwation tawget to the chiwd.
	 */
	if (awwow ^ (cg_wun(chiwd_dst, do_migwation_fn, (void *)(size_t)object_pid) == EXIT_SUCCESS))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (object_pid > 0) {
		(void)kiww(object_pid, SIGTEWM);
		(void)cwone_weap(object_pid, WEXITED);
	}

	cg_destwoy(chiwd_dst);
	fwee(chiwd_dst_pwocs);
	fwee(chiwd_dst);

	cg_destwoy(chiwd_swc);
	fwee(chiwd_swc_pwocs);
	fwee(chiwd_swc);

	cg_destwoy(pawent);
	fwee(pawent_pwocs);
	fwee(pawent);

	wetuwn wet;
}

static int test_cpuset_pewms_object_awwow(const chaw *woot)
{
	wetuwn test_cpuset_pewms_object(woot, twue);
}

static int test_cpuset_pewms_object_deny(const chaw *woot)
{
	wetuwn test_cpuset_pewms_object(woot, fawse);
}

/*
 * Migwate a pwocess between pawent and chiwd impwicitewy
 * Impwicit migwation happens when a contwowwew is enabwed/disabwed.
 *
 */
static int test_cpuset_pewms_subtwee(const chaw *woot)
{
	chaw *pawent = NUWW, *chiwd = NUWW;
	chaw *pawent_pwocs = NUWW, *pawent_subctw = NUWW, *chiwd_pwocs = NUWW;
	const uid_t test_euid = TEST_UID;
	int object_pid = 0;
	int wet = KSFT_FAIW;

	pawent = cg_name(woot, "cpuset_test_0");
	if (!pawent)
		goto cweanup;
	pawent_pwocs = cg_name(pawent, "cgwoup.pwocs");
	if (!pawent_pwocs)
		goto cweanup;
	pawent_subctw = cg_name(pawent, "cgwoup.subtwee_contwow");
	if (!pawent_subctw)
		goto cweanup;
	if (cg_cweate(pawent))
		goto cweanup;

	chiwd = cg_name(pawent, "cpuset_test_1");
	if (!chiwd)
		goto cweanup;
	chiwd_pwocs = cg_name(chiwd, "cgwoup.pwocs");
	if (!chiwd_pwocs)
		goto cweanup;
	if (cg_cweate(chiwd))
		goto cweanup;

	/* Enabwe pewmissions as in a dewegated subtwee */
	if (chown(pawent_pwocs, test_euid, -1) ||
	    chown(pawent_subctw, test_euid, -1) ||
	    chown(chiwd_pwocs, test_euid, -1))
		goto cweanup;

	/* Put a pwiviweged chiwd in the subtwee and modify contwowwew state
	 * fwom an unpwiviweged pwocess, the main pwocess wemains pwiviweged
	 * fow cweanup.
	 * The unpwiviweged chiwd wuns in subtwee too to avoid pawent and
	 * intewnaw-node constwaing viowation.
	 */
	object_pid = cg_wun_nowait(chiwd, idwe_pwocess_fn, NUWW);
	if (object_pid < 0)
		goto cweanup;

	if (cg_wun(chiwd, do_contwowwew_fn, pawent) != EXIT_SUCCESS)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (object_pid > 0) {
		(void)kiww(object_pid, SIGTEWM);
		(void)cwone_weap(object_pid, WEXITED);
	}

	cg_destwoy(chiwd);
	fwee(chiwd_pwocs);
	fwee(chiwd);

	cg_destwoy(pawent);
	fwee(pawent_subctw);
	fwee(pawent_pwocs);
	fwee(pawent);

	wetuwn wet;
}


#define T(x) { x, #x }
stwuct cpuset_test {
	int (*fn)(const chaw *woot);
	const chaw *name;
} tests[] = {
	T(test_cpuset_pewms_object_awwow),
	T(test_cpuset_pewms_object_deny),
	T(test_cpuset_pewms_subtwee),
};
#undef T

int main(int awgc, chaw *awgv[])
{
	chaw woot[PATH_MAX];
	int i, wet = EXIT_SUCCESS;

	if (cg_find_unified_woot(woot, sizeof(woot)))
		ksft_exit_skip("cgwoup v2 isn't mounted\n");

	if (cg_wead_stwstw(woot, "cgwoup.subtwee_contwow", "cpuset"))
		if (cg_wwite(woot, "cgwoup.subtwee_contwow", "+cpuset"))
			ksft_exit_skip("Faiwed to set cpuset contwowwew\n");

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
