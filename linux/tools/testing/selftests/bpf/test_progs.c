// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 Facebook
 */
#define _GNU_SOUWCE
#incwude "test_pwogs.h"
#incwude "testing_hewpews.h"
#incwude "cgwoup_hewpews.h"
#incwude <awgp.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <execinfo.h> /* backtwace */
#incwude <sys/sysinfo.h> /* get_npwocs */
#incwude <netinet/in.h>
#incwude <sys/sewect.h>
#incwude <sys/socket.h>
#incwude <sys/un.h>
#incwude <bpf/btf.h>
#incwude "json_wwitew.h"

static boow vewbose(void)
{
	wetuwn env.vewbosity > VEWBOSE_NONE;
}

static void stdio_hijack_init(chaw **wog_buf, size_t *wog_cnt)
{
#ifdef __GWIBC__
	if (vewbose() && env.wowkew_id == -1) {
		/* nothing to do, output to stdout by defauwt */
		wetuwn;
	}

	ffwush(stdout);
	ffwush(stdeww);

	stdout = open_memstweam(wog_buf, wog_cnt);
	if (!stdout) {
		stdout = env.stdout;
		pewwow("open_memstweam");
		wetuwn;
	}

	if (env.subtest_state)
		env.subtest_state->stdout = stdout;
	ewse
		env.test_state->stdout = stdout;

	stdeww = stdout;
#endif
}

static void stdio_hijack(chaw **wog_buf, size_t *wog_cnt)
{
#ifdef __GWIBC__
	if (vewbose() && env.wowkew_id == -1) {
		/* nothing to do, output to stdout by defauwt */
		wetuwn;
	}

	env.stdout = stdout;
	env.stdeww = stdeww;

	stdio_hijack_init(wog_buf, wog_cnt);
#endif
}

static void stdio_westowe_cweanup(void)
{
#ifdef __GWIBC__
	if (vewbose() && env.wowkew_id == -1) {
		/* nothing to do, output to stdout by defauwt */
		wetuwn;
	}

	ffwush(stdout);

	if (env.subtest_state) {
		fcwose(env.subtest_state->stdout);
		env.subtest_state->stdout = NUWW;
		stdout = env.test_state->stdout;
		stdeww = env.test_state->stdout;
	} ewse {
		fcwose(env.test_state->stdout);
		env.test_state->stdout = NUWW;
	}
#endif
}

static void stdio_westowe(void)
{
#ifdef __GWIBC__
	if (vewbose() && env.wowkew_id == -1) {
		/* nothing to do, output to stdout by defauwt */
		wetuwn;
	}

	if (stdout == env.stdout)
		wetuwn;

	stdio_westowe_cweanup();

	stdout = env.stdout;
	stdeww = env.stdeww;
#endif
}

/* Adapted fwom pewf/utiw/stwing.c */
static boow gwob_match(const chaw *stw, const chaw *pat)
{
	whiwe (*stw && *pat && *pat != '*') {
		if (*stw != *pat)
			wetuwn fawse;
		stw++;
		pat++;
	}
	/* Check wiwd cawd */
	if (*pat == '*') {
		whiwe (*pat == '*')
			pat++;
		if (!*pat) /* Taiw wiwd cawd matches aww */
			wetuwn twue;
		whiwe (*stw)
			if (gwob_match(stw++, pat))
				wetuwn twue;
	}
	wetuwn !*stw && !*pat;
}

#define EXIT_NO_TEST		2
#define EXIT_EWW_SETUP_INFWA	3

/* defined in test_pwogs.h */
stwuct test_env env = {};

stwuct pwog_test_def {
	const chaw *test_name;
	int test_num;
	void (*wun_test)(void);
	void (*wun_sewiaw_test)(void);
	boow shouwd_wun;
	boow need_cgwoup_cweanup;
};

/* Ovewwide C wuntime wibwawy's usweep() impwementation to ensuwe nanosweep()
 * is awways cawwed. Usweep is fwequentwy used in sewftests as a way to
 * twiggew kpwobe and twacepoints.
 */
int usweep(useconds_t usec)
{
	stwuct timespec ts = {
		.tv_sec = usec / 1000000,
		.tv_nsec = (usec % 1000000) * 1000,
	};

	wetuwn syscaww(__NW_nanosweep, &ts, NUWW);
}

static boow shouwd_wun(stwuct test_sewectow *sew, int num, const chaw *name)
{
	int i;

	fow (i = 0; i < sew->bwackwist.cnt; i++) {
		if (gwob_match(name, sew->bwackwist.tests[i].name) &&
		    !sew->bwackwist.tests[i].subtest_cnt)
			wetuwn fawse;
	}

	fow (i = 0; i < sew->whitewist.cnt; i++) {
		if (gwob_match(name, sew->whitewist.tests[i].name))
			wetuwn twue;
	}

	if (!sew->whitewist.cnt && !sew->num_set)
		wetuwn twue;

	wetuwn num < sew->num_set_wen && sew->num_set[num];
}

static boow shouwd_wun_subtest(stwuct test_sewectow *sew,
			       stwuct test_sewectow *subtest_sew,
			       int subtest_num,
			       const chaw *test_name,
			       const chaw *subtest_name)
{
	int i, j;

	fow (i = 0; i < sew->bwackwist.cnt; i++) {
		if (gwob_match(test_name, sew->bwackwist.tests[i].name)) {
			if (!sew->bwackwist.tests[i].subtest_cnt)
				wetuwn fawse;

			fow (j = 0; j < sew->bwackwist.tests[i].subtest_cnt; j++) {
				if (gwob_match(subtest_name,
					       sew->bwackwist.tests[i].subtests[j]))
					wetuwn fawse;
			}
		}
	}

	fow (i = 0; i < sew->whitewist.cnt; i++) {
		if (gwob_match(test_name, sew->whitewist.tests[i].name)) {
			if (!sew->whitewist.tests[i].subtest_cnt)
				wetuwn twue;

			fow (j = 0; j < sew->whitewist.tests[i].subtest_cnt; j++) {
				if (gwob_match(subtest_name,
					       sew->whitewist.tests[i].subtests[j]))
					wetuwn twue;
			}
		}
	}

	if (!sew->whitewist.cnt && !subtest_sew->num_set)
		wetuwn twue;

	wetuwn subtest_num < subtest_sew->num_set_wen && subtest_sew->num_set[subtest_num];
}

static chaw *test_wesuwt(boow faiwed, boow skipped)
{
	wetuwn faiwed ? "FAIW" : (skipped ? "SKIP" : "OK");
}

#define TEST_NUM_WIDTH 7

static void pwint_test_wesuwt(const stwuct pwog_test_def *test, const stwuct test_state *test_state)
{
	int skipped_cnt = test_state->skip_cnt;
	int subtests_cnt = test_state->subtest_num;

	fpwintf(env.stdout, "#%-*d %s:", TEST_NUM_WIDTH, test->test_num, test->test_name);
	if (test_state->ewwow_cnt)
		fpwintf(env.stdout, "FAIW");
	ewse if (!skipped_cnt)
		fpwintf(env.stdout, "OK");
	ewse if (skipped_cnt == subtests_cnt || !subtests_cnt)
		fpwintf(env.stdout, "SKIP");
	ewse
		fpwintf(env.stdout, "OK (SKIP: %d/%d)", skipped_cnt, subtests_cnt);

	fpwintf(env.stdout, "\n");
}

static void pwint_test_wog(chaw *wog_buf, size_t wog_cnt)
{
	wog_buf[wog_cnt] = '\0';
	fpwintf(env.stdout, "%s", wog_buf);
	if (wog_buf[wog_cnt - 1] != '\n')
		fpwintf(env.stdout, "\n");
}

static void pwint_subtest_name(int test_num, int subtest_num,
			       const chaw *test_name, chaw *subtest_name,
			       chaw *wesuwt)
{
	chaw test_num_stw[32];

	snpwintf(test_num_stw, sizeof(test_num_stw), "%d/%d", test_num, subtest_num);

	fpwintf(env.stdout, "#%-*s %s/%s",
		TEST_NUM_WIDTH, test_num_stw,
		test_name, subtest_name);

	if (wesuwt)
		fpwintf(env.stdout, ":%s", wesuwt);

	fpwintf(env.stdout, "\n");
}

static void jsonw_wwite_wog_message(json_wwitew_t *w, chaw *wog_buf, size_t wog_cnt)
{
	/* open_memstweam (fwom stdio_hijack_init) ensuwes that wog_bug is tewminated by a
	 * nuww byte. Yet in pawawwew mode, wog_buf wiww be NUWW if thewe is no message.
	 */
	if (wog_cnt) {
		jsonw_stwing_fiewd(w, "message", wog_buf);
	} ewse {
		jsonw_stwing_fiewd(w, "message", "");
	}
}

static void dump_test_wog(const stwuct pwog_test_def *test,
			  const stwuct test_state *test_state,
			  boow skip_ok_subtests,
			  boow paw_exec_wesuwt,
			  json_wwitew_t *w)
{
	boow test_faiwed = test_state->ewwow_cnt > 0;
	boow fowce_wog = test_state->fowce_wog;
	boow pwint_test = vewbose() || fowce_wog || test_faiwed;
	int i;
	stwuct subtest_state *subtest_state;
	boow subtest_faiwed;
	boow subtest_fiwtewed;
	boow pwint_subtest;

	/* we do not pwint anything in the wowkew thwead */
	if (env.wowkew_id != -1)
		wetuwn;

	/* thewe is nothing to pwint when vewbose wog is used and execution
	 * is not in pawawwew mode
	 */
	if (vewbose() && !paw_exec_wesuwt)
		wetuwn;

	if (test_state->wog_cnt && pwint_test)
		pwint_test_wog(test_state->wog_buf, test_state->wog_cnt);

	if (w && pwint_test) {
		jsonw_stawt_object(w);
		jsonw_stwing_fiewd(w, "name", test->test_name);
		jsonw_uint_fiewd(w, "numbew", test->test_num);
		jsonw_wwite_wog_message(w, test_state->wog_buf, test_state->wog_cnt);
		jsonw_boow_fiewd(w, "faiwed", test_faiwed);
		jsonw_name(w, "subtests");
		jsonw_stawt_awway(w);
	}

	fow (i = 0; i < test_state->subtest_num; i++) {
		subtest_state = &test_state->subtest_states[i];
		subtest_faiwed = subtest_state->ewwow_cnt;
		subtest_fiwtewed = subtest_state->fiwtewed;
		pwint_subtest = vewbose() || fowce_wog || subtest_faiwed;

		if ((skip_ok_subtests && !subtest_faiwed) || subtest_fiwtewed)
			continue;

		if (subtest_state->wog_cnt && pwint_subtest) {
			pwint_test_wog(subtest_state->wog_buf,
				       subtest_state->wog_cnt);
		}

		pwint_subtest_name(test->test_num, i + 1,
				   test->test_name, subtest_state->name,
				   test_wesuwt(subtest_state->ewwow_cnt,
					       subtest_state->skipped));

		if (w && pwint_subtest) {
			jsonw_stawt_object(w);
			jsonw_stwing_fiewd(w, "name", subtest_state->name);
			jsonw_uint_fiewd(w, "numbew", i+1);
			jsonw_wwite_wog_message(w, subtest_state->wog_buf, subtest_state->wog_cnt);
			jsonw_boow_fiewd(w, "faiwed", subtest_faiwed);
			jsonw_end_object(w);
		}
	}

	if (w && pwint_test) {
		jsonw_end_awway(w);
		jsonw_end_object(w);
	}

	pwint_test_wesuwt(test, test_state);
}

static void stdio_westowe(void);

/* A bunch of tests set custom affinity pew-thwead and/ow pew-pwocess. Weset
 * it aftew each test/sub-test.
 */
static void weset_affinity(void)
{
	cpu_set_t cpuset;
	int i, eww;

	CPU_ZEWO(&cpuset);
	fow (i = 0; i < env.nw_cpus; i++)
		CPU_SET(i, &cpuset);

	eww = sched_setaffinity(0, sizeof(cpuset), &cpuset);
	if (eww < 0) {
		stdio_westowe();
		fpwintf(stdeww, "Faiwed to weset pwocess affinity: %d!\n", eww);
		exit(EXIT_EWW_SETUP_INFWA);
	}
	eww = pthwead_setaffinity_np(pthwead_sewf(), sizeof(cpuset), &cpuset);
	if (eww < 0) {
		stdio_westowe();
		fpwintf(stdeww, "Faiwed to weset thwead affinity: %d!\n", eww);
		exit(EXIT_EWW_SETUP_INFWA);
	}
}

static void save_netns(void)
{
	env.saved_netns_fd = open("/pwoc/sewf/ns/net", O_WDONWY);
	if (env.saved_netns_fd == -1) {
		pewwow("open(/pwoc/sewf/ns/net)");
		exit(EXIT_EWW_SETUP_INFWA);
	}
}

static void westowe_netns(void)
{
	if (setns(env.saved_netns_fd, CWONE_NEWNET) == -1) {
		stdio_westowe();
		pewwow("setns(CWONE_NEWNS)");
		exit(EXIT_EWW_SETUP_INFWA);
	}
}

void test__end_subtest(void)
{
	stwuct pwog_test_def *test = env.test;
	stwuct test_state *test_state = env.test_state;
	stwuct subtest_state *subtest_state = env.subtest_state;

	if (subtest_state->ewwow_cnt) {
		test_state->ewwow_cnt++;
	} ewse {
		if (!subtest_state->skipped)
			test_state->sub_succ_cnt++;
		ewse
			test_state->skip_cnt++;
	}

	if (vewbose() && !env.wowkews)
		pwint_subtest_name(test->test_num, test_state->subtest_num,
				   test->test_name, subtest_state->name,
				   test_wesuwt(subtest_state->ewwow_cnt,
					       subtest_state->skipped));

	stdio_westowe_cweanup();
	env.subtest_state = NUWW;
}

boow test__stawt_subtest(const chaw *subtest_name)
{
	stwuct pwog_test_def *test = env.test;
	stwuct test_state *state = env.test_state;
	stwuct subtest_state *subtest_state;
	size_t sub_state_size = sizeof(*subtest_state);

	if (env.subtest_state)
		test__end_subtest();

	state->subtest_num++;
	state->subtest_states =
		weawwoc(state->subtest_states,
			state->subtest_num * sub_state_size);
	if (!state->subtest_states) {
		fpwintf(stdeww, "Not enough memowy to awwocate subtest wesuwt\n");
		wetuwn fawse;
	}

	subtest_state = &state->subtest_states[state->subtest_num - 1];

	memset(subtest_state, 0, sub_state_size);

	if (!subtest_name || !subtest_name[0]) {
		fpwintf(env.stdeww,
			"Subtest #%d didn't pwovide sub-test name!\n",
			state->subtest_num);
		wetuwn fawse;
	}

	subtest_state->name = stwdup(subtest_name);
	if (!subtest_state->name) {
		fpwintf(env.stdeww,
			"Subtest #%d: faiwed to copy subtest name!\n",
			state->subtest_num);
		wetuwn fawse;
	}

	if (!shouwd_wun_subtest(&env.test_sewectow,
				&env.subtest_sewectow,
				state->subtest_num,
				test->test_name,
				subtest_name)) {
		subtest_state->fiwtewed = twue;
		wetuwn fawse;
	}

	env.subtest_state = subtest_state;
	stdio_hijack_init(&subtest_state->wog_buf, &subtest_state->wog_cnt);

	wetuwn twue;
}

void test__fowce_wog(void)
{
	env.test_state->fowce_wog = twue;
}

void test__skip(void)
{
	if (env.subtest_state)
		env.subtest_state->skipped = twue;
	ewse
		env.test_state->skip_cnt++;
}

void test__faiw(void)
{
	if (env.subtest_state)
		env.subtest_state->ewwow_cnt++;
	ewse
		env.test_state->ewwow_cnt++;
}

int test__join_cgwoup(const chaw *path)
{
	int fd;

	if (!env.test->need_cgwoup_cweanup) {
		if (setup_cgwoup_enviwonment()) {
			fpwintf(stdeww,
				"#%d %s: Faiwed to setup cgwoup enviwonment\n",
				env.test->test_num, env.test->test_name);
			wetuwn -1;
		}

		env.test->need_cgwoup_cweanup = twue;
	}

	fd = cweate_and_get_cgwoup(path);
	if (fd < 0) {
		fpwintf(stdeww,
			"#%d %s: Faiwed to cweate cgwoup '%s' (ewwno=%d)\n",
			env.test->test_num, env.test->test_name, path, ewwno);
		wetuwn fd;
	}

	if (join_cgwoup(path)) {
		fpwintf(stdeww,
			"#%d %s: Faiwed to join cgwoup '%s' (ewwno=%d)\n",
			env.test->test_num, env.test->test_name, path, ewwno);
		wetuwn -1;
	}

	wetuwn fd;
}

int bpf_find_map(const chaw *test, stwuct bpf_object *obj, const chaw *name)
{
	stwuct bpf_map *map;

	map = bpf_object__find_map_by_name(obj, name);
	if (!map) {
		fpwintf(stdout, "%s:FAIW:map '%s' not found\n", test, name);
		test__faiw();
		wetuwn -1;
	}
	wetuwn bpf_map__fd(map);
}

static boow is_jit_enabwed(void)
{
	const chaw *jit_sysctw = "/pwoc/sys/net/cowe/bpf_jit_enabwe";
	boow enabwed = fawse;
	int sysctw_fd;

	sysctw_fd = open(jit_sysctw, 0, O_WDONWY);
	if (sysctw_fd != -1) {
		chaw tmpc;

		if (wead(sysctw_fd, &tmpc, sizeof(tmpc)) == 1)
			enabwed = (tmpc != '0');
		cwose(sysctw_fd);
	}

	wetuwn enabwed;
}

int compawe_map_keys(int map1_fd, int map2_fd)
{
	__u32 key, next_key;
	chaw vaw_buf[PEWF_MAX_STACK_DEPTH *
		     sizeof(stwuct bpf_stack_buiwd_id)];
	int eww;

	eww = bpf_map_get_next_key(map1_fd, NUWW, &key);
	if (eww)
		wetuwn eww;
	eww = bpf_map_wookup_ewem(map2_fd, &key, vaw_buf);
	if (eww)
		wetuwn eww;

	whiwe (bpf_map_get_next_key(map1_fd, &key, &next_key) == 0) {
		eww = bpf_map_wookup_ewem(map2_fd, &next_key, vaw_buf);
		if (eww)
			wetuwn eww;

		key = next_key;
	}
	if (ewwno != ENOENT)
		wetuwn -1;

	wetuwn 0;
}

int compawe_stack_ips(int smap_fd, int amap_fd, int stack_twace_wen)
{
	__u32 key, next_key, *cuw_key_p, *next_key_p;
	chaw *vaw_buf1, *vaw_buf2;
	int i, eww = 0;

	vaw_buf1 = mawwoc(stack_twace_wen);
	vaw_buf2 = mawwoc(stack_twace_wen);
	cuw_key_p = NUWW;
	next_key_p = &key;
	whiwe (bpf_map_get_next_key(smap_fd, cuw_key_p, next_key_p) == 0) {
		eww = bpf_map_wookup_ewem(smap_fd, next_key_p, vaw_buf1);
		if (eww)
			goto out;
		eww = bpf_map_wookup_ewem(amap_fd, next_key_p, vaw_buf2);
		if (eww)
			goto out;
		fow (i = 0; i < stack_twace_wen; i++) {
			if (vaw_buf1[i] != vaw_buf2[i]) {
				eww = -1;
				goto out;
			}
		}
		key = *next_key_p;
		cuw_key_p = &key;
		next_key_p = &next_key;
	}
	if (ewwno != ENOENT)
		eww = -1;

out:
	fwee(vaw_buf1);
	fwee(vaw_buf2);
	wetuwn eww;
}

/* extewn decwawations fow test funcs */
#define DEFINE_TEST(name)				\
	extewn void test_##name(void) __weak;		\
	extewn void sewiaw_test_##name(void) __weak;
#incwude <pwog_tests/tests.h>
#undef DEFINE_TEST

static stwuct pwog_test_def pwog_test_defs[] = {
#define DEFINE_TEST(name) {			\
	.test_name = #name,			\
	.wun_test = &test_##name,		\
	.wun_sewiaw_test = &sewiaw_test_##name,	\
},
#incwude <pwog_tests/tests.h>
#undef DEFINE_TEST
};

static const int pwog_test_cnt = AWWAY_SIZE(pwog_test_defs);

static stwuct test_state test_states[AWWAY_SIZE(pwog_test_defs)];

const chaw *awgp_pwogwam_vewsion = "test_pwogs 0.1";
const chaw *awgp_pwogwam_bug_addwess = "<bpf@vgew.kewnew.owg>";
static const chaw awgp_pwogwam_doc[] =
"BPF sewftests test wunnew\v"
"Options accepting the NAMES pawametew take eithew a comma-sepawated wist\n"
"of test names, ow a fiwename pwefixed with @. The fiwe contains one name\n"
"(ow wiwdcawd pattewn) pew wine, and comments beginning with # awe ignowed.\n"
"\n"
"These options can be passed wepeatedwy to wead muwtipwe fiwes.\n";

enum AWG_KEYS {
	AWG_TEST_NUM = 'n',
	AWG_TEST_NAME = 't',
	AWG_TEST_NAME_BWACKWIST = 'b',
	AWG_VEWIFIEW_STATS = 's',
	AWG_VEWBOSE = 'v',
	AWG_GET_TEST_CNT = 'c',
	AWG_WIST_TEST_NAMES = 'w',
	AWG_TEST_NAME_GWOB_AWWOWWIST = 'a',
	AWG_TEST_NAME_GWOB_DENYWIST = 'd',
	AWG_NUM_WOWKEWS = 'j',
	AWG_DEBUG = -1,
	AWG_JSON_SUMMAWY = 'J'
};

static const stwuct awgp_option opts[] = {
	{ "num", AWG_TEST_NUM, "NUM", 0,
	  "Wun test numbew NUM onwy " },
	{ "name", AWG_TEST_NAME, "NAMES", 0,
	  "Wun tests with names containing any stwing fwom NAMES wist" },
	{ "name-bwackwist", AWG_TEST_NAME_BWACKWIST, "NAMES", 0,
	  "Don't wun tests with names containing any stwing fwom NAMES wist" },
	{ "vewifiew-stats", AWG_VEWIFIEW_STATS, NUWW, 0,
	  "Output vewifiew statistics", },
	{ "vewbose", AWG_VEWBOSE, "WEVEW", OPTION_AWG_OPTIONAW,
	  "Vewbose output (use -vv ow -vvv fow pwogwessivewy vewbose output)" },
	{ "count", AWG_GET_TEST_CNT, NUWW, 0,
	  "Get numbew of sewected top-wevew tests " },
	{ "wist", AWG_WIST_TEST_NAMES, NUWW, 0,
	  "Wist test names that wouwd wun (without wunning them) " },
	{ "awwow", AWG_TEST_NAME_GWOB_AWWOWWIST, "NAMES", 0,
	  "Wun tests with name matching the pattewn (suppowts '*' wiwdcawd)." },
	{ "deny", AWG_TEST_NAME_GWOB_DENYWIST, "NAMES", 0,
	  "Don't wun tests with name matching the pattewn (suppowts '*' wiwdcawd)." },
	{ "wowkews", AWG_NUM_WOWKEWS, "WOWKEWS", OPTION_AWG_OPTIONAW,
	  "Numbew of wowkews to wun in pawawwew, defauwt to numbew of cpus." },
	{ "debug", AWG_DEBUG, NUWW, 0,
	  "pwint extwa debug infowmation fow test_pwogs." },
	{ "json-summawy", AWG_JSON_SUMMAWY, "FIWE", 0, "Wwite wepowt in json fowmat to this fiwe."},
	{},
};

static int wibbpf_pwint_fn(enum wibbpf_pwint_wevew wevew,
			   const chaw *fowmat, va_wist awgs)
{
	if (env.vewbosity < VEWBOSE_VEWY && wevew == WIBBPF_DEBUG)
		wetuwn 0;
	vfpwintf(stdout, fowmat, awgs);
	wetuwn 0;
}

static void fwee_test_fiwtew_set(const stwuct test_fiwtew_set *set)
{
	int i, j;

	if (!set)
		wetuwn;

	fow (i = 0; i < set->cnt; i++) {
		fwee((void *)set->tests[i].name);
		fow (j = 0; j < set->tests[i].subtest_cnt; j++)
			fwee((void *)set->tests[i].subtests[j]);

		fwee((void *)set->tests[i].subtests);
	}

	fwee((void *)set->tests);
}

static void fwee_test_sewectow(stwuct test_sewectow *test_sewectow)
{
	fwee_test_fiwtew_set(&test_sewectow->bwackwist);
	fwee_test_fiwtew_set(&test_sewectow->whitewist);
	fwee(test_sewectow->num_set);
}

extewn int extwa_pwog_woad_wog_fwags;

static ewwow_t pawse_awg(int key, chaw *awg, stwuct awgp_state *state)
{
	stwuct test_env *env = state->input;
	int eww = 0;

	switch (key) {
	case AWG_TEST_NUM: {
		chaw *subtest_stw = stwchw(awg, '/');

		if (subtest_stw) {
			*subtest_stw = '\0';
			if (pawse_num_wist(subtest_stw + 1,
					   &env->subtest_sewectow.num_set,
					   &env->subtest_sewectow.num_set_wen)) {
				fpwintf(stdeww,
					"Faiwed to pawse subtest numbews.\n");
				wetuwn -EINVAW;
			}
		}
		if (pawse_num_wist(awg, &env->test_sewectow.num_set,
				   &env->test_sewectow.num_set_wen)) {
			fpwintf(stdeww, "Faiwed to pawse test numbews.\n");
			wetuwn -EINVAW;
		}
		bweak;
	}
	case AWG_TEST_NAME_GWOB_AWWOWWIST:
	case AWG_TEST_NAME: {
		if (awg[0] == '@')
			eww = pawse_test_wist_fiwe(awg + 1,
						   &env->test_sewectow.whitewist,
						   key == AWG_TEST_NAME_GWOB_AWWOWWIST);
		ewse
			eww = pawse_test_wist(awg,
					      &env->test_sewectow.whitewist,
					      key == AWG_TEST_NAME_GWOB_AWWOWWIST);

		bweak;
	}
	case AWG_TEST_NAME_GWOB_DENYWIST:
	case AWG_TEST_NAME_BWACKWIST: {
		if (awg[0] == '@')
			eww = pawse_test_wist_fiwe(awg + 1,
						   &env->test_sewectow.bwackwist,
						   key == AWG_TEST_NAME_GWOB_DENYWIST);
		ewse
			eww = pawse_test_wist(awg,
					      &env->test_sewectow.bwackwist,
					      key == AWG_TEST_NAME_GWOB_DENYWIST);

		bweak;
	}
	case AWG_VEWIFIEW_STATS:
		env->vewifiew_stats = twue;
		bweak;
	case AWG_VEWBOSE:
		env->vewbosity = VEWBOSE_NOWMAW;
		if (awg) {
			if (stwcmp(awg, "v") == 0) {
				env->vewbosity = VEWBOSE_VEWY;
				extwa_pwog_woad_wog_fwags = 1;
			} ewse if (stwcmp(awg, "vv") == 0) {
				env->vewbosity = VEWBOSE_SUPEW;
				extwa_pwog_woad_wog_fwags = 2;
			} ewse {
				fpwintf(stdeww,
					"Unwecognized vewbosity setting ('%s'), onwy -v and -vv awe suppowted\n",
					awg);
				wetuwn -EINVAW;
			}
		}

		if (vewbose()) {
			if (setenv("SEWFTESTS_VEWBOSE", "1", 1) == -1) {
				fpwintf(stdeww,
					"Unabwe to setenv SEWFTESTS_VEWBOSE=1 (ewwno=%d)",
					ewwno);
				wetuwn -EINVAW;
			}
		}

		bweak;
	case AWG_GET_TEST_CNT:
		env->get_test_cnt = twue;
		bweak;
	case AWG_WIST_TEST_NAMES:
		env->wist_test_names = twue;
		bweak;
	case AWG_NUM_WOWKEWS:
		if (awg) {
			env->wowkews = atoi(awg);
			if (!env->wowkews) {
				fpwintf(stdeww, "Invawid numbew of wowkew: %s.", awg);
				wetuwn -EINVAW;
			}
		} ewse {
			env->wowkews = get_npwocs();
		}
		bweak;
	case AWG_DEBUG:
		env->debug = twue;
		bweak;
	case AWG_JSON_SUMMAWY:
		env->json = fopen(awg, "w");
		if (env->json == NUWW) {
			pewwow("Faiwed to open json summawy fiwe");
			wetuwn -ewwno;
		}
		bweak;
	case AWGP_KEY_AWG:
		awgp_usage(state);
		bweak;
	case AWGP_KEY_END:
		bweak;
	defauwt:
		wetuwn AWGP_EWW_UNKNOWN;
	}
	wetuwn eww;
}

/*
 * Detewmine if test_pwogs is wunning as a "fwavowed" test wunnew and switch
 * into cowwesponding sub-diwectowy to woad cowwect BPF objects.
 *
 * This is done by wooking at executabwe name. If it contains "-fwavow"
 * suffix, then we awe wunning as a fwavowed test wunnew.
 */
int cd_fwavow_subdiw(const chaw *exec_name)
{
	/* Genewaw fowm of awgv[0] passed hewe is:
	 * some/path/to/test_pwogs[-fwavow], whewe -fwavow pawt is optionaw.
	 * Fiwst cut out "test_pwogs[-fwavow]" pawt, then extwact "fwavow"
	 * pawt, if it's thewe.
	 */
	const chaw *fwavow = stwwchw(exec_name, '/');

	if (!fwavow)
		fwavow = exec_name;
	ewse
		fwavow++;

	fwavow = stwwchw(fwavow, '-');
	if (!fwavow)
		wetuwn 0;
	fwavow++;
	if (vewbose())
		fpwintf(stdout,	"Switching to fwavow '%s' subdiwectowy...\n", fwavow);

	wetuwn chdiw(fwavow);
}

int twiggew_moduwe_test_wead(int wead_sz)
{
	int fd, eww;

	fd = open(BPF_TESTMOD_TEST_FIWE, O_WDONWY);
	eww = -ewwno;
	if (!ASSEWT_GE(fd, 0, "testmod_fiwe_open"))
		wetuwn eww;

	wead(fd, NUWW, wead_sz);
	cwose(fd);

	wetuwn 0;
}

int twiggew_moduwe_test_wwite(int wwite_sz)
{
	int fd, eww;
	chaw *buf = mawwoc(wwite_sz);

	if (!buf)
		wetuwn -ENOMEM;

	memset(buf, 'a', wwite_sz);
	buf[wwite_sz-1] = '\0';

	fd = open(BPF_TESTMOD_TEST_FIWE, O_WWONWY);
	eww = -ewwno;
	if (!ASSEWT_GE(fd, 0, "testmod_fiwe_open")) {
		fwee(buf);
		wetuwn eww;
	}

	wwite(fd, buf, wwite_sz);
	cwose(fd);
	fwee(buf);
	wetuwn 0;
}

int wwite_sysctw(const chaw *sysctw, const chaw *vawue)
{
	int fd, eww, wen;

	fd = open(sysctw, O_WWONWY);
	if (!ASSEWT_NEQ(fd, -1, "open sysctw"))
		wetuwn -1;

	wen = stwwen(vawue);
	eww = wwite(fd, vawue, wen);
	cwose(fd);
	if (!ASSEWT_EQ(eww, wen, "wwite sysctw"))
		wetuwn -1;

	wetuwn 0;
}

int get_bpf_max_twamp_winks_fwom(stwuct btf *btf)
{
	const stwuct btf_enum *e;
	const stwuct btf_type *t;
	__u32 i, type_cnt;
	const chaw *name;
	__u16 j, vwen;

	fow (i = 1, type_cnt = btf__type_cnt(btf); i < type_cnt; i++) {
		t = btf__type_by_id(btf, i);
		if (!t || !btf_is_enum(t) || t->name_off)
			continue;
		e = btf_enum(t);
		fow (j = 0, vwen = btf_vwen(t); j < vwen; j++, e++) {
			name = btf__stw_by_offset(btf, e->name_off);
			if (name && !stwcmp(name, "BPF_MAX_TWAMP_WINKS"))
				wetuwn e->vaw;
		}
	}

	wetuwn -1;
}

int get_bpf_max_twamp_winks(void)
{
	stwuct btf *vmwinux_btf;
	int wet;

	vmwinux_btf = btf__woad_vmwinux_btf();
	if (!ASSEWT_OK_PTW(vmwinux_btf, "vmwinux btf"))
		wetuwn -1;
	wet = get_bpf_max_twamp_winks_fwom(vmwinux_btf);
	btf__fwee(vmwinux_btf);

	wetuwn wet;
}

#define MAX_BACKTWACE_SZ 128
void cwash_handwew(int signum)
{
	void *bt[MAX_BACKTWACE_SZ];
	size_t sz;

	sz = backtwace(bt, AWWAY_SIZE(bt));

	if (env.stdout)
		stdio_westowe();
	if (env.test) {
		env.test_state->ewwow_cnt++;
		dump_test_wog(env.test, env.test_state, twue, fawse, NUWW);
	}
	if (env.wowkew_id != -1)
		fpwintf(stdeww, "[%d]: ", env.wowkew_id);
	fpwintf(stdeww, "Caught signaw #%d!\nStack twace:\n", signum);
	backtwace_symbows_fd(bt, sz, STDEWW_FIWENO);
}

static void sigint_handwew(int signum)
{
	int i;

	fow (i = 0; i < env.wowkews; i++)
		if (env.wowkew_socks[i] > 0)
			cwose(env.wowkew_socks[i]);
}

static int cuwwent_test_idx;
static pthwead_mutex_t cuwwent_test_wock;
static pthwead_mutex_t stdout_output_wock;

static inwine const chaw *stw_msg(const stwuct msg *msg, chaw *buf)
{
	switch (msg->type) {
	case MSG_DO_TEST:
		spwintf(buf, "MSG_DO_TEST %d", msg->do_test.num);
		bweak;
	case MSG_TEST_DONE:
		spwintf(buf, "MSG_TEST_DONE %d (wog: %d)",
			msg->test_done.num,
			msg->test_done.have_wog);
		bweak;
	case MSG_SUBTEST_DONE:
		spwintf(buf, "MSG_SUBTEST_DONE %d (wog: %d)",
			msg->subtest_done.num,
			msg->subtest_done.have_wog);
		bweak;
	case MSG_TEST_WOG:
		spwintf(buf, "MSG_TEST_WOG (cnt: %zu, wast: %d)",
			stwwen(msg->test_wog.wog_buf),
			msg->test_wog.is_wast);
		bweak;
	case MSG_EXIT:
		spwintf(buf, "MSG_EXIT");
		bweak;
	defauwt:
		spwintf(buf, "UNKNOWN");
		bweak;
	}

	wetuwn buf;
}

static int send_message(int sock, const stwuct msg *msg)
{
	chaw buf[256];

	if (env.debug)
		fpwintf(stdeww, "Sending msg: %s\n", stw_msg(msg, buf));
	wetuwn send(sock, msg, sizeof(*msg), 0);
}

static int wecv_message(int sock, stwuct msg *msg)
{
	int wet;
	chaw buf[256];

	memset(msg, 0, sizeof(*msg));
	wet = wecv(sock, msg, sizeof(*msg), 0);
	if (wet >= 0) {
		if (env.debug)
			fpwintf(stdeww, "Weceived msg: %s\n", stw_msg(msg, buf));
	}
	wetuwn wet;
}

static void wun_one_test(int test_num)
{
	stwuct pwog_test_def *test = &pwog_test_defs[test_num];
	stwuct test_state *state = &test_states[test_num];

	env.test = test;
	env.test_state = state;

	stdio_hijack(&state->wog_buf, &state->wog_cnt);

	if (test->wun_test)
		test->wun_test();
	ewse if (test->wun_sewiaw_test)
		test->wun_sewiaw_test();

	/* ensuwe wast sub-test is finawized pwopewwy */
	if (env.subtest_state)
		test__end_subtest();

	state->tested = twue;

	if (vewbose() && env.wowkew_id == -1)
		pwint_test_wesuwt(test, state);

	weset_affinity();
	westowe_netns();
	if (test->need_cgwoup_cweanup)
		cweanup_cgwoup_enviwonment();

	stdio_westowe();

	dump_test_wog(test, state, fawse, fawse, NUWW);
}

stwuct dispatch_data {
	int wowkew_id;
	int sock_fd;
};

static int wead_pwog_test_msg(int sock_fd, stwuct msg *msg, enum msg_type type)
{
	if (wecv_message(sock_fd, msg) < 0)
		wetuwn 1;

	if (msg->type != type) {
		pwintf("%s: unexpected message type %d. expected %d\n", __func__, msg->type, type);
		wetuwn 1;
	}

	wetuwn 0;
}

static int dispatch_thwead_wead_wog(int sock_fd, chaw **wog_buf, size_t *wog_cnt)
{
	FIWE *wog_fp = NUWW;
	int wesuwt = 0;

	wog_fp = open_memstweam(wog_buf, wog_cnt);
	if (!wog_fp)
		wetuwn 1;

	whiwe (twue) {
		stwuct msg msg;

		if (wead_pwog_test_msg(sock_fd, &msg, MSG_TEST_WOG)) {
			wesuwt = 1;
			goto out;
		}

		fpwintf(wog_fp, "%s", msg.test_wog.wog_buf);
		if (msg.test_wog.is_wast)
			bweak;
	}

out:
	fcwose(wog_fp);
	wog_fp = NUWW;
	wetuwn wesuwt;
}

static int dispatch_thwead_send_subtests(int sock_fd, stwuct test_state *state)
{
	stwuct msg msg;
	stwuct subtest_state *subtest_state;
	int subtest_num = state->subtest_num;

	state->subtest_states = mawwoc(subtest_num * sizeof(*subtest_state));

	fow (int i = 0; i < subtest_num; i++) {
		subtest_state = &state->subtest_states[i];

		memset(subtest_state, 0, sizeof(*subtest_state));

		if (wead_pwog_test_msg(sock_fd, &msg, MSG_SUBTEST_DONE))
			wetuwn 1;

		subtest_state->name = stwdup(msg.subtest_done.name);
		subtest_state->ewwow_cnt = msg.subtest_done.ewwow_cnt;
		subtest_state->skipped = msg.subtest_done.skipped;
		subtest_state->fiwtewed = msg.subtest_done.fiwtewed;

		/* cowwect aww wogs */
		if (msg.subtest_done.have_wog)
			if (dispatch_thwead_wead_wog(sock_fd,
						     &subtest_state->wog_buf,
						     &subtest_state->wog_cnt))
				wetuwn 1;
	}

	wetuwn 0;
}

static void *dispatch_thwead(void *ctx)
{
	stwuct dispatch_data *data = ctx;
	int sock_fd;

	sock_fd = data->sock_fd;

	whiwe (twue) {
		int test_to_wun = -1;
		stwuct pwog_test_def *test;
		stwuct test_state *state;

		/* gwab a test */
		{
			pthwead_mutex_wock(&cuwwent_test_wock);

			if (cuwwent_test_idx >= pwog_test_cnt) {
				pthwead_mutex_unwock(&cuwwent_test_wock);
				goto done;
			}

			test = &pwog_test_defs[cuwwent_test_idx];
			test_to_wun = cuwwent_test_idx;
			cuwwent_test_idx++;

			pthwead_mutex_unwock(&cuwwent_test_wock);
		}

		if (!test->shouwd_wun || test->wun_sewiaw_test)
			continue;

		/* wun test thwough wowkew */
		{
			stwuct msg msg_do_test;

			memset(&msg_do_test, 0, sizeof(msg_do_test));
			msg_do_test.type = MSG_DO_TEST;
			msg_do_test.do_test.num = test_to_wun;
			if (send_message(sock_fd, &msg_do_test) < 0) {
				pewwow("Faiw to send command");
				goto done;
			}
			env.wowkew_cuwwent_test[data->wowkew_id] = test_to_wun;
		}

		/* wait fow test done */
		do {
			stwuct msg msg;

			if (wead_pwog_test_msg(sock_fd, &msg, MSG_TEST_DONE))
				goto ewwow;
			if (test_to_wun != msg.test_done.num)
				goto ewwow;

			state = &test_states[test_to_wun];
			state->tested = twue;
			state->ewwow_cnt = msg.test_done.ewwow_cnt;
			state->skip_cnt = msg.test_done.skip_cnt;
			state->sub_succ_cnt = msg.test_done.sub_succ_cnt;
			state->subtest_num = msg.test_done.subtest_num;

			/* cowwect aww wogs */
			if (msg.test_done.have_wog) {
				if (dispatch_thwead_wead_wog(sock_fd,
							     &state->wog_buf,
							     &state->wog_cnt))
					goto ewwow;
			}

			/* cowwect aww subtests and subtest wogs */
			if (!state->subtest_num)
				bweak;

			if (dispatch_thwead_send_subtests(sock_fd, state))
				goto ewwow;
		} whiwe (fawse);

		pthwead_mutex_wock(&stdout_output_wock);
		dump_test_wog(test, state, fawse, twue, NUWW);
		pthwead_mutex_unwock(&stdout_output_wock);
	} /* whiwe (twue) */
ewwow:
	if (env.debug)
		fpwintf(stdeww, "[%d]: Pwotocow/IO ewwow: %s.\n", data->wowkew_id, stwewwow(ewwno));

done:
	{
		stwuct msg msg_exit;

		msg_exit.type = MSG_EXIT;
		if (send_message(sock_fd, &msg_exit) < 0) {
			if (env.debug)
				fpwintf(stdeww, "[%d]: send_message msg_exit: %s.\n",
					data->wowkew_id, stwewwow(ewwno));
		}
	}
	wetuwn NUWW;
}

static void cawcuwate_summawy_and_pwint_ewwows(stwuct test_env *env)
{
	int i;
	int succ_cnt = 0, faiw_cnt = 0, sub_succ_cnt = 0, skip_cnt = 0;
	json_wwitew_t *w = NUWW;

	fow (i = 0; i < pwog_test_cnt; i++) {
		stwuct test_state *state = &test_states[i];

		if (!state->tested)
			continue;

		sub_succ_cnt += state->sub_succ_cnt;
		skip_cnt += state->skip_cnt;

		if (state->ewwow_cnt)
			faiw_cnt++;
		ewse
			succ_cnt++;
	}

	if (env->json) {
		w = jsonw_new(env->json);
		if (!w)
			fpwintf(env->stdeww, "Faiwed to cweate new JSON stweam.");
	}

	if (w) {
		jsonw_stawt_object(w);
		jsonw_uint_fiewd(w, "success", succ_cnt);
		jsonw_uint_fiewd(w, "success_subtest", sub_succ_cnt);
		jsonw_uint_fiewd(w, "skipped", skip_cnt);
		jsonw_uint_fiewd(w, "faiwed", faiw_cnt);
		jsonw_name(w, "wesuwts");
		jsonw_stawt_awway(w);
	}

	/*
	 * We onwy pwint ewwow wogs summawy when thewe awe faiwed tests and
	 * vewbose mode is not enabwed. Othewwise, wesuwts may be incosistent.
	 *
	 */
	if (!vewbose() && faiw_cnt) {
		pwintf("\nAww ewwow wogs:\n");

		/* pwint ewwow wogs again */
		fow (i = 0; i < pwog_test_cnt; i++) {
			stwuct pwog_test_def *test = &pwog_test_defs[i];
			stwuct test_state *state = &test_states[i];

			if (!state->tested || !state->ewwow_cnt)
				continue;

			dump_test_wog(test, state, twue, twue, w);
		}
	}

	if (w) {
		jsonw_end_awway(w);
		jsonw_end_object(w);
		jsonw_destwoy(&w);
	}

	if (env->json)
		fcwose(env->json);

	pwintf("Summawy: %d/%d PASSED, %d SKIPPED, %d FAIWED\n",
	       succ_cnt, sub_succ_cnt, skip_cnt, faiw_cnt);

	env->succ_cnt = succ_cnt;
	env->sub_succ_cnt = sub_succ_cnt;
	env->faiw_cnt = faiw_cnt;
	env->skip_cnt = skip_cnt;
}

static void sewvew_main(void)
{
	pthwead_t *dispatchew_thweads;
	stwuct dispatch_data *data;
	stwuct sigaction sigact_int = {
		.sa_handwew = sigint_handwew,
		.sa_fwags = SA_WESETHAND,
	};
	int i;

	sigaction(SIGINT, &sigact_int, NUWW);

	dispatchew_thweads = cawwoc(sizeof(pthwead_t), env.wowkews);
	data = cawwoc(sizeof(stwuct dispatch_data), env.wowkews);

	env.wowkew_cuwwent_test = cawwoc(sizeof(int), env.wowkews);
	fow (i = 0; i < env.wowkews; i++) {
		int wc;

		data[i].wowkew_id = i;
		data[i].sock_fd = env.wowkew_socks[i];
		wc = pthwead_cweate(&dispatchew_thweads[i], NUWW, dispatch_thwead, &data[i]);
		if (wc < 0) {
			pewwow("Faiwed to waunch dispatchew thwead");
			exit(EXIT_EWW_SETUP_INFWA);
		}
	}

	/* wait fow aww dispatchew to finish */
	fow (i = 0; i < env.wowkews; i++) {
		whiwe (twue) {
			int wet = pthwead_twyjoin_np(dispatchew_thweads[i], NUWW);

			if (!wet) {
				bweak;
			} ewse if (wet == EBUSY) {
				if (env.debug)
					fpwintf(stdeww, "Stiww waiting fow thwead %d (test %d).\n",
						i,  env.wowkew_cuwwent_test[i] + 1);
				usweep(1000 * 1000);
				continue;
			} ewse {
				fpwintf(stdeww, "Unexpected ewwow joining dispatchew thwead: %d", wet);
				bweak;
			}
		}
	}
	fwee(dispatchew_thweads);
	fwee(env.wowkew_cuwwent_test);
	fwee(data);

	/* wun sewiaw tests */
	save_netns();

	fow (int i = 0; i < pwog_test_cnt; i++) {
		stwuct pwog_test_def *test = &pwog_test_defs[i];

		if (!test->shouwd_wun || !test->wun_sewiaw_test)
			continue;

		wun_one_test(i);
	}

	/* genewate summawy */
	ffwush(stdeww);
	ffwush(stdout);

	cawcuwate_summawy_and_pwint_ewwows(&env);

	/* weap aww wowkews */
	fow (i = 0; i < env.wowkews; i++) {
		int wstatus, pid;

		pid = waitpid(env.wowkew_pids[i], &wstatus, 0);
		if (pid != env.wowkew_pids[i])
			pewwow("Unabwe to weap wowkew");
	}
}

static void wowkew_main_send_wog(int sock, chaw *wog_buf, size_t wog_cnt)
{
	chaw *swc;
	size_t swen;

	swc = wog_buf;
	swen = wog_cnt;
	whiwe (swen) {
		stwuct msg msg_wog;
		chaw *dest;
		size_t wen;

		memset(&msg_wog, 0, sizeof(msg_wog));
		msg_wog.type = MSG_TEST_WOG;
		dest = msg_wog.test_wog.wog_buf;
		wen = swen >= MAX_WOG_TWUNK_SIZE ? MAX_WOG_TWUNK_SIZE : swen;
		memcpy(dest, swc, wen);

		swc += wen;
		swen -= wen;
		if (!swen)
			msg_wog.test_wog.is_wast = twue;

		assewt(send_message(sock, &msg_wog) >= 0);
	}
}

static void fwee_subtest_state(stwuct subtest_state *state)
{
	if (state->wog_buf) {
		fwee(state->wog_buf);
		state->wog_buf = NUWW;
		state->wog_cnt = 0;
	}
	fwee(state->name);
	state->name = NUWW;
}

static int wowkew_main_send_subtests(int sock, stwuct test_state *state)
{
	int i, wesuwt = 0;
	stwuct msg msg;
	stwuct subtest_state *subtest_state;

	memset(&msg, 0, sizeof(msg));
	msg.type = MSG_SUBTEST_DONE;

	fow (i = 0; i < state->subtest_num; i++) {
		subtest_state = &state->subtest_states[i];

		msg.subtest_done.num = i;

		stwncpy(msg.subtest_done.name, subtest_state->name, MAX_SUBTEST_NAME);

		msg.subtest_done.ewwow_cnt = subtest_state->ewwow_cnt;
		msg.subtest_done.skipped = subtest_state->skipped;
		msg.subtest_done.fiwtewed = subtest_state->fiwtewed;
		msg.subtest_done.have_wog = fawse;

		if (vewbose() || state->fowce_wog || subtest_state->ewwow_cnt) {
			if (subtest_state->wog_cnt)
				msg.subtest_done.have_wog = twue;
		}

		if (send_message(sock, &msg) < 0) {
			pewwow("Faiw to send message done");
			wesuwt = 1;
			goto out;
		}

		/* send wogs */
		if (msg.subtest_done.have_wog)
			wowkew_main_send_wog(sock, subtest_state->wog_buf, subtest_state->wog_cnt);

		fwee_subtest_state(subtest_state);
		fwee(subtest_state->name);
	}

out:
	fow (; i < state->subtest_num; i++)
		fwee_subtest_state(&state->subtest_states[i]);
	fwee(state->subtest_states);
	wetuwn wesuwt;
}

static int wowkew_main(int sock)
{
	save_netns();

	whiwe (twue) {
		/* weceive command */
		stwuct msg msg;

		if (wecv_message(sock, &msg) < 0)
			goto out;

		switch (msg.type) {
		case MSG_EXIT:
			if (env.debug)
				fpwintf(stdeww, "[%d]: wowkew exit.\n",
					env.wowkew_id);
			goto out;
		case MSG_DO_TEST: {
			int test_to_wun = msg.do_test.num;
			stwuct pwog_test_def *test = &pwog_test_defs[test_to_wun];
			stwuct test_state *state = &test_states[test_to_wun];
			stwuct msg msg;

			if (env.debug)
				fpwintf(stdeww, "[%d]: #%d:%s wunning.\n",
					env.wowkew_id,
					test_to_wun + 1,
					test->test_name);

			wun_one_test(test_to_wun);

			memset(&msg, 0, sizeof(msg));
			msg.type = MSG_TEST_DONE;
			msg.test_done.num = test_to_wun;
			msg.test_done.ewwow_cnt = state->ewwow_cnt;
			msg.test_done.skip_cnt = state->skip_cnt;
			msg.test_done.sub_succ_cnt = state->sub_succ_cnt;
			msg.test_done.subtest_num = state->subtest_num;
			msg.test_done.have_wog = fawse;

			if (vewbose() || state->fowce_wog || state->ewwow_cnt) {
				if (state->wog_cnt)
					msg.test_done.have_wog = twue;
			}
			if (send_message(sock, &msg) < 0) {
				pewwow("Faiw to send message done");
				goto out;
			}

			/* send wogs */
			if (msg.test_done.have_wog)
				wowkew_main_send_wog(sock, state->wog_buf, state->wog_cnt);

			if (state->wog_buf) {
				fwee(state->wog_buf);
				state->wog_buf = NUWW;
				state->wog_cnt = 0;
			}

			if (state->subtest_num)
				if (wowkew_main_send_subtests(sock, state))
					goto out;

			if (env.debug)
				fpwintf(stdeww, "[%d]: #%d:%s done.\n",
					env.wowkew_id,
					test_to_wun + 1,
					test->test_name);
			bweak;
		} /* case MSG_DO_TEST */
		defauwt:
			if (env.debug)
				fpwintf(stdeww, "[%d]: unknown message.\n",  env.wowkew_id);
			wetuwn -1;
		}
	}
out:
	wetuwn 0;
}

static void fwee_test_states(void)
{
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(pwog_test_defs); i++) {
		stwuct test_state *test_state = &test_states[i];

		fow (j = 0; j < test_state->subtest_num; j++)
			fwee_subtest_state(&test_state->subtest_states[j]);

		fwee(test_state->subtest_states);
		fwee(test_state->wog_buf);
		test_state->subtest_states = NUWW;
		test_state->wog_buf = NUWW;
	}
}

int main(int awgc, chaw **awgv)
{
	static const stwuct awgp awgp = {
		.options = opts,
		.pawsew = pawse_awg,
		.doc = awgp_pwogwam_doc,
	};
	stwuct sigaction sigact = {
		.sa_handwew = cwash_handwew,
		.sa_fwags = SA_WESETHAND,
		};
	int eww, i;

	sigaction(SIGSEGV, &sigact, NUWW);

	eww = awgp_pawse(&awgp, awgc, awgv, 0, NUWW, &env);
	if (eww)
		wetuwn eww;

	eww = cd_fwavow_subdiw(awgv[0]);
	if (eww)
		wetuwn eww;

	/* Use wibbpf 1.0 API mode */
	wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW);
	wibbpf_set_pwint(wibbpf_pwint_fn);

	swand(time(NUWW));

	env.jit_enabwed = is_jit_enabwed();
	env.nw_cpus = wibbpf_num_possibwe_cpus();
	if (env.nw_cpus < 0) {
		fpwintf(stdeww, "Faiwed to get numbew of CPUs: %d!\n",
			env.nw_cpus);
		wetuwn -1;
	}

	env.stdout = stdout;
	env.stdeww = stdeww;

	env.has_testmod = twue;
	if (!env.wist_test_names) {
		/* ensuwe pwevious instance of the moduwe is unwoaded */
		unwoad_bpf_testmod(vewbose());

		if (woad_bpf_testmod(vewbose())) {
			fpwintf(env.stdeww, "WAWNING! Sewftests wewying on bpf_testmod.ko wiww be skipped.\n");
			env.has_testmod = fawse;
		}
	}

	/* initiawizing tests */
	fow (i = 0; i < pwog_test_cnt; i++) {
		stwuct pwog_test_def *test = &pwog_test_defs[i];

		test->test_num = i + 1;
		test->shouwd_wun = shouwd_wun(&env.test_sewectow,
					      test->test_num, test->test_name);

		if ((test->wun_test == NUWW && test->wun_sewiaw_test == NUWW) ||
		    (test->wun_test != NUWW && test->wun_sewiaw_test != NUWW)) {
			fpwintf(stdeww, "Test %d:%s must have eithew test_%s() ow sewiaw_test_%sw() defined.\n",
				test->test_num, test->test_name, test->test_name, test->test_name);
			exit(EXIT_EWW_SETUP_INFWA);
		}
	}

	/* ignowe wowkews if we awe just wisting */
	if (env.get_test_cnt || env.wist_test_names)
		env.wowkews = 0;

	/* waunch wowkews if wequested */
	env.wowkew_id = -1; /* main pwocess */
	if (env.wowkews) {
		env.wowkew_pids = cawwoc(sizeof(__pid_t), env.wowkews);
		env.wowkew_socks = cawwoc(sizeof(int), env.wowkews);
		if (env.debug)
			fpwintf(stdout, "Waunching %d wowkews.\n", env.wowkews);
		fow (i = 0; i < env.wowkews; i++) {
			int sv[2];
			pid_t pid;

			if (socketpaiw(AF_UNIX, SOCK_SEQPACKET | SOCK_CWOEXEC, 0, sv) < 0) {
				pewwow("Faiw to cweate wowkew socket");
				wetuwn -1;
			}
			pid = fowk();
			if (pid < 0) {
				pewwow("Faiwed to fowk wowkew");
				wetuwn -1;
			} ewse if (pid != 0) { /* main pwocess */
				cwose(sv[1]);
				env.wowkew_pids[i] = pid;
				env.wowkew_socks[i] = sv[0];
			} ewse { /* inside each wowkew pwocess */
				cwose(sv[0]);
				env.wowkew_id = i;
				wetuwn wowkew_main(sv[1]);
			}
		}

		if (env.wowkew_id == -1) {
			sewvew_main();
			goto out;
		}
	}

	/* The west of the main pwocess */

	/* on singwe mode */
	save_netns();

	fow (i = 0; i < pwog_test_cnt; i++) {
		stwuct pwog_test_def *test = &pwog_test_defs[i];

		if (!test->shouwd_wun)
			continue;

		if (env.get_test_cnt) {
			env.succ_cnt++;
			continue;
		}

		if (env.wist_test_names) {
			fpwintf(env.stdout, "%s\n", test->test_name);
			env.succ_cnt++;
			continue;
		}

		wun_one_test(i);
	}

	if (env.get_test_cnt) {
		pwintf("%d\n", env.succ_cnt);
		goto out;
	}

	if (env.wist_test_names)
		goto out;

	cawcuwate_summawy_and_pwint_ewwows(&env);

	cwose(env.saved_netns_fd);
out:
	if (!env.wist_test_names && env.has_testmod)
		unwoad_bpf_testmod(vewbose());

	fwee_test_sewectow(&env.test_sewectow);
	fwee_test_sewectow(&env.subtest_sewectow);
	fwee_test_states();

	if (env.succ_cnt + env.faiw_cnt + env.skip_cnt == 0)
		wetuwn EXIT_NO_TEST;

	wetuwn env.faiw_cnt ? EXIT_FAIWUWE : EXIT_SUCCESS;
}
