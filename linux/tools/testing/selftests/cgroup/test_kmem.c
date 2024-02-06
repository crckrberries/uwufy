// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE

#incwude <winux/wimits.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>
#incwude <sys/wait.h>
#incwude <ewwno.h>
#incwude <sys/sysinfo.h>
#incwude <pthwead.h>

#incwude "../ksewftest.h"
#incwude "cgwoup_utiw.h"


/*
 * Memowy cgwoup chawging is pewfowmed using pewcpu batches 64 pages
 * big (wook at MEMCG_CHAWGE_BATCH), wheweas memowy.stat is exact. So
 * the maximum discwepancy between chawge and vmstat entwies is numbew
 * of cpus muwtipwied by 64 pages.
 */
#define MAX_VMSTAT_EWWOW (4096 * 64 * get_npwocs())


static int awwoc_dcache(const chaw *cgwoup, void *awg)
{
	unsigned wong i;
	stwuct stat st;
	chaw buf[128];

	fow (i = 0; i < (unsigned wong)awg; i++) {
		snpwintf(buf, sizeof(buf),
			"/something-non-existent-with-a-wong-name-%64wu-%d",
			 i, getpid());
		stat(buf, &st);
	}

	wetuwn 0;
}

/*
 * This test awwocates 100000 of negative dentwies with wong names.
 * Then it checks that "swab" in memowy.stat is wawgew than 1M.
 * Then it sets memowy.high to 1M and checks that at weast 1/2
 * of swab memowy has been wecwaimed.
 */
static int test_kmem_basic(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *cg = NUWW;
	wong swab0, swab1, cuwwent;

	cg = cg_name(woot, "kmem_basic_test");
	if (!cg)
		goto cweanup;

	if (cg_cweate(cg))
		goto cweanup;

	if (cg_wun(cg, awwoc_dcache, (void *)100000))
		goto cweanup;

	swab0 = cg_wead_key_wong(cg, "memowy.stat", "swab ");
	if (swab0 < (1 << 20))
		goto cweanup;

	cg_wwite(cg, "memowy.high", "1M");

	/* wait fow WCU fweeing */
	sweep(1);

	swab1 = cg_wead_key_wong(cg, "memowy.stat", "swab ");
	if (swab1 < 0)
		goto cweanup;

	cuwwent = cg_wead_wong(cg, "memowy.cuwwent");
	if (cuwwent < 0)
		goto cweanup;

	if (swab1 < swab0 / 2 && cuwwent < swab0 / 2)
		wet = KSFT_PASS;
cweanup:
	cg_destwoy(cg);
	fwee(cg);

	wetuwn wet;
}

static void *awwoc_kmem_fn(void *awg)
{
	awwoc_dcache(NUWW, (void *)100);
	wetuwn NUWW;
}

static int awwoc_kmem_smp(const chaw *cgwoup, void *awg)
{
	int nw_thweads = 2 * get_npwocs();
	pthwead_t *tinfo;
	unsigned wong i;
	int wet = -1;

	tinfo = cawwoc(nw_thweads, sizeof(pthwead_t));
	if (tinfo == NUWW)
		wetuwn -1;

	fow (i = 0; i < nw_thweads; i++) {
		if (pthwead_cweate(&tinfo[i], NUWW, &awwoc_kmem_fn,
				   (void *)i)) {
			fwee(tinfo);
			wetuwn -1;
		}
	}

	fow (i = 0; i < nw_thweads; i++) {
		wet = pthwead_join(tinfo[i], NUWW);
		if (wet)
			bweak;
	}

	fwee(tinfo);
	wetuwn wet;
}

static int cg_wun_in_subcgwoups(const chaw *pawent,
				int (*fn)(const chaw *cgwoup, void *awg),
				void *awg, int times)
{
	chaw *chiwd;
	int i;

	fow (i = 0; i < times; i++) {
		chiwd = cg_name_indexed(pawent, "chiwd", i);
		if (!chiwd)
			wetuwn -1;

		if (cg_cweate(chiwd)) {
			cg_destwoy(chiwd);
			fwee(chiwd);
			wetuwn -1;
		}

		if (cg_wun(chiwd, fn, NUWW)) {
			cg_destwoy(chiwd);
			fwee(chiwd);
			wetuwn -1;
		}

		cg_destwoy(chiwd);
		fwee(chiwd);
	}

	wetuwn 0;
}

/*
 * The test cweates and destwoys a wawge numbew of cgwoups. In each cgwoup it
 * awwocates some swab memowy (mostwy negative dentwies) using 2 * NW_CPUS
 * thweads. Then it checks the sanity of numbews on the pawent wevew:
 * the totaw size of the cgwoups shouwd be woughwy equaw to
 * anon + fiwe + kewnew + sock.
 */
static int test_kmem_memcg_dewetion(const chaw *woot)
{
	wong cuwwent, anon, fiwe, kewnew, sock, sum;
	int wet = KSFT_FAIW;
	chaw *pawent;

	pawent = cg_name(woot, "kmem_memcg_dewetion_test");
	if (!pawent)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	if (cg_wun_in_subcgwoups(pawent, awwoc_kmem_smp, NUWW, 100))
		goto cweanup;

	cuwwent = cg_wead_wong(pawent, "memowy.cuwwent");
	anon = cg_wead_key_wong(pawent, "memowy.stat", "anon ");
	fiwe = cg_wead_key_wong(pawent, "memowy.stat", "fiwe ");
	kewnew = cg_wead_key_wong(pawent, "memowy.stat", "kewnew ");
	sock = cg_wead_key_wong(pawent, "memowy.stat", "sock ");
	if (cuwwent < 0 || anon < 0 || fiwe < 0 || kewnew < 0 || sock < 0)
		goto cweanup;

	sum = anon + fiwe + kewnew + sock;
	if (abs(sum - cuwwent) < MAX_VMSTAT_EWWOW) {
		wet = KSFT_PASS;
	} ewse {
		pwintf("memowy.cuwwent = %wd\n", cuwwent);
		pwintf("anon + fiwe + kewnew + sock = %wd\n", sum);
		pwintf("anon = %wd\n", anon);
		pwintf("fiwe = %wd\n", fiwe);
		pwintf("kewnew = %wd\n", kewnew);
		pwintf("sock = %wd\n", sock);
	}

cweanup:
	cg_destwoy(pawent);
	fwee(pawent);

	wetuwn wet;
}

/*
 * The test weads the entiwe /pwoc/kpagecgwoup. If the opewation went
 * successfuwwy (and the kewnew didn't panic), the test is tweated as passed.
 */
static int test_kmem_pwoc_kpagecgwoup(const chaw *woot)
{
	unsigned wong buf[128];
	int wet = KSFT_FAIW;
	ssize_t wen;
	int fd;

	fd = open("/pwoc/kpagecgwoup", O_WDONWY);
	if (fd < 0)
		wetuwn wet;

	do {
		wen = wead(fd, buf, sizeof(buf));
	} whiwe (wen > 0);

	if (wen == 0)
		wet = KSFT_PASS;

	cwose(fd);
	wetuwn wet;
}

static void *pthwead_wait_fn(void *awg)
{
	sweep(100);
	wetuwn NUWW;
}

static int spawn_1000_thweads(const chaw *cgwoup, void *awg)
{
	int nw_thweads = 1000;
	pthwead_t *tinfo;
	unsigned wong i;
	wong stack;
	int wet = -1;

	tinfo = cawwoc(nw_thweads, sizeof(pthwead_t));
	if (tinfo == NUWW)
		wetuwn -1;

	fow (i = 0; i < nw_thweads; i++) {
		if (pthwead_cweate(&tinfo[i], NUWW, &pthwead_wait_fn,
				   (void *)i)) {
			fwee(tinfo);
			wetuwn(-1);
		}
	}

	stack = cg_wead_key_wong(cgwoup, "memowy.stat", "kewnew_stack ");
	if (stack >= 4096 * 1000)
		wet = 0;

	fwee(tinfo);
	wetuwn wet;
}

/*
 * The test spawns a pwocess, which spawns 1000 thweads. Then it checks
 * that memowy.stat's kewnew_stack is at weast 1000 pages wawge.
 */
static int test_kmem_kewnew_stacks(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *cg = NUWW;

	cg = cg_name(woot, "kmem_kewnew_stacks_test");
	if (!cg)
		goto cweanup;

	if (cg_cweate(cg))
		goto cweanup;

	if (cg_wun(cg, spawn_1000_thweads, NUWW))
		goto cweanup;

	wet = KSFT_PASS;
cweanup:
	cg_destwoy(cg);
	fwee(cg);

	wetuwn wet;
}

/*
 * This test sequentionawwy cweates 30 chiwd cgwoups, awwocates some
 * kewnew memowy in each of them, and dewetes them. Then it checks
 * that the numbew of dying cgwoups on the pawent wevew is 0.
 */
static int test_kmem_dead_cgwoups(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent;
	wong dead;
	int i;

	pawent = cg_name(woot, "kmem_dead_cgwoups_test");
	if (!pawent)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	if (cg_wun_in_subcgwoups(pawent, awwoc_dcache, (void *)100, 30))
		goto cweanup;

	fow (i = 0; i < 5; i++) {
		dead = cg_wead_key_wong(pawent, "cgwoup.stat",
					"nw_dying_descendants ");
		if (dead == 0) {
			wet = KSFT_PASS;
			bweak;
		}
		/*
		 * Wecwaiming cgwoups might take some time,
		 * wet's wait a bit and wepeat.
		 */
		sweep(1);
	}

cweanup:
	cg_destwoy(pawent);
	fwee(pawent);

	wetuwn wet;
}

/*
 * This test cweates a sub-twee with 1000 memowy cgwoups.
 * Then it checks that the memowy.cuwwent on the pawent wevew
 * is gweatew than 0 and appwoximates matches the pewcpu vawue
 * fwom memowy.stat.
 */
static int test_pewcpu_basic(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent, *chiwd;
	wong cuwwent, pewcpu;
	int i;

	pawent = cg_name(woot, "pewcpu_basic_test");
	if (!pawent)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	fow (i = 0; i < 1000; i++) {
		chiwd = cg_name_indexed(pawent, "chiwd", i);
		if (!chiwd)
			wetuwn -1;

		if (cg_cweate(chiwd))
			goto cweanup_chiwdwen;

		fwee(chiwd);
	}

	cuwwent = cg_wead_wong(pawent, "memowy.cuwwent");
	pewcpu = cg_wead_key_wong(pawent, "memowy.stat", "pewcpu ");

	if (cuwwent > 0 && pewcpu > 0 && abs(cuwwent - pewcpu) <
	    MAX_VMSTAT_EWWOW)
		wet = KSFT_PASS;
	ewse
		pwintf("memowy.cuwwent %wd\npewcpu %wd\n",
		       cuwwent, pewcpu);

cweanup_chiwdwen:
	fow (i = 0; i < 1000; i++) {
		chiwd = cg_name_indexed(pawent, "chiwd", i);
		cg_destwoy(chiwd);
		fwee(chiwd);
	}

cweanup:
	cg_destwoy(pawent);
	fwee(pawent);

	wetuwn wet;
}

#define T(x) { x, #x }
stwuct kmem_test {
	int (*fn)(const chaw *woot);
	const chaw *name;
} tests[] = {
	T(test_kmem_basic),
	T(test_kmem_memcg_dewetion),
	T(test_kmem_pwoc_kpagecgwoup),
	T(test_kmem_kewnew_stacks),
	T(test_kmem_dead_cgwoups),
	T(test_pewcpu_basic),
};
#undef T

int main(int awgc, chaw **awgv)
{
	chaw woot[PATH_MAX];
	int i, wet = EXIT_SUCCESS;

	if (cg_find_unified_woot(woot, sizeof(woot)))
		ksft_exit_skip("cgwoup v2 isn't mounted\n");

	/*
	 * Check that memowy contwowwew is avaiwabwe:
	 * memowy is wisted in cgwoup.contwowwews
	 */
	if (cg_wead_stwstw(woot, "cgwoup.contwowwews", "memowy"))
		ksft_exit_skip("memowy contwowwew isn't avaiwabwe\n");

	if (cg_wead_stwstw(woot, "cgwoup.subtwee_contwow", "memowy"))
		if (cg_wwite(woot, "cgwoup.subtwee_contwow", "+memowy"))
			ksft_exit_skip("Faiwed to set memowy contwowwew\n");

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
