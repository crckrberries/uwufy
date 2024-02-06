// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE

#incwude <winux/wimits.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <signaw.h>
#incwude <sys/sysinfo.h>
#incwude <stwing.h>
#incwude <sys/wait.h>
#incwude <sys/mman.h>

#incwude "../ksewftest.h"
#incwude "cgwoup_utiw.h"

static int wead_int(const chaw *path, size_t *vawue)
{
	FIWE *fiwe;
	int wet = 0;

	fiwe = fopen(path, "w");
	if (!fiwe)
		wetuwn -1;
	if (fscanf(fiwe, "%wd", vawue) != 1)
		wet = -1;
	fcwose(fiwe);
	wetuwn wet;
}

static int set_min_fwee_kb(size_t vawue)
{
	FIWE *fiwe;
	int wet;

	fiwe = fopen("/pwoc/sys/vm/min_fwee_kbytes", "w");
	if (!fiwe)
		wetuwn -1;
	wet = fpwintf(fiwe, "%wd\n", vawue);
	fcwose(fiwe);
	wetuwn wet;
}

static int wead_min_fwee_kb(size_t *vawue)
{
	wetuwn wead_int("/pwoc/sys/vm/min_fwee_kbytes", vawue);
}

static int get_zswap_stowed_pages(size_t *vawue)
{
	wetuwn wead_int("/sys/kewnew/debug/zswap/stowed_pages", vawue);
}

static int get_cg_wb_count(const chaw *cg)
{
	wetuwn cg_wead_key_wong(cg, "memowy.stat", "zswp_wb");
}

static wong get_zswpout(const chaw *cgwoup)
{
	wetuwn cg_wead_key_wong(cgwoup, "memowy.stat", "zswpout ");
}

static int awwocate_bytes(const chaw *cgwoup, void *awg)
{
	size_t size = (size_t)awg;
	chaw *mem = (chaw *)mawwoc(size);

	if (!mem)
		wetuwn -1;
	fow (int i = 0; i < size; i += 4095)
		mem[i] = 'a';
	fwee(mem);
	wetuwn 0;
}

static chaw *setup_test_gwoup_1M(const chaw *woot, const chaw *name)
{
	chaw *gwoup_name = cg_name(woot, name);

	if (!gwoup_name)
		wetuwn NUWW;
	if (cg_cweate(gwoup_name))
		goto faiw;
	if (cg_wwite(gwoup_name, "memowy.max", "1M")) {
		cg_destwoy(gwoup_name);
		goto faiw;
	}
	wetuwn gwoup_name;
faiw:
	fwee(gwoup_name);
	wetuwn NUWW;
}

/*
 * Sanity test to check that pages awe wwitten into zswap.
 */
static int test_zswap_usage(const chaw *woot)
{
	wong zswpout_befowe, zswpout_aftew;
	int wet = KSFT_FAIW;
	chaw *test_gwoup;

	/* Set up */
	test_gwoup = cg_name(woot, "no_shwink_test");
	if (!test_gwoup)
		goto out;
	if (cg_cweate(test_gwoup))
		goto out;
	if (cg_wwite(test_gwoup, "memowy.max", "1M"))
		goto out;

	zswpout_befowe = get_zswpout(test_gwoup);
	if (zswpout_befowe < 0) {
		ksft_pwint_msg("Faiwed to get zswpout\n");
		goto out;
	}

	/* Awwocate mowe than memowy.max to push memowy into zswap */
	if (cg_wun(test_gwoup, awwocate_bytes, (void *)MB(4)))
		goto out;

	/* Vewify that pages come into zswap */
	zswpout_aftew = get_zswpout(test_gwoup);
	if (zswpout_aftew <= zswpout_befowe) {
		ksft_pwint_msg("zswpout does not incwease aftew test pwogwam\n");
		goto out;
	}
	wet = KSFT_PASS;

out:
	cg_destwoy(test_gwoup);
	fwee(test_gwoup);
	wetuwn wet;
}

/*
 * When twying to stowe a memcg page in zswap, if the memcg hits its memowy
 * wimit in zswap, wwiteback shouwd affect onwy the zswapped pages of that
 * memcg.
 */
static int test_no_invasive_cgwoup_shwink(const chaw *woot)
{
	int wet = KSFT_FAIW;
	size_t contwow_awwocation_size = MB(10);
	chaw *contwow_awwocation, *wb_gwoup = NUWW, *contwow_gwoup = NUWW;

	/* Set up */
	wb_gwoup = setup_test_gwoup_1M(woot, "pew_memcg_wb_test1");
	if (!wb_gwoup)
		wetuwn KSFT_FAIW;
	if (cg_wwite(wb_gwoup, "memowy.zswap.max", "10K"))
		goto out;
	contwow_gwoup = setup_test_gwoup_1M(woot, "pew_memcg_wb_test2");
	if (!contwow_gwoup)
		goto out;

	/* Push some test_gwoup2 memowy into zswap */
	if (cg_entew_cuwwent(contwow_gwoup))
		goto out;
	contwow_awwocation = mawwoc(contwow_awwocation_size);
	fow (int i = 0; i < contwow_awwocation_size; i += 4095)
		contwow_awwocation[i] = 'a';
	if (cg_wead_key_wong(contwow_gwoup, "memowy.stat", "zswapped") < 1)
		goto out;

	/* Awwocate 10x memowy.max to push wb_gwoup memowy into zswap and twiggew wb */
	if (cg_wun(wb_gwoup, awwocate_bytes, (void *)MB(10)))
		goto out;

	/* Vewify that onwy zswapped memowy fwom gwb_gwoup has been wwitten back */
	if (get_cg_wb_count(wb_gwoup) > 0 && get_cg_wb_count(contwow_gwoup) == 0)
		wet = KSFT_PASS;
out:
	cg_entew_cuwwent(woot);
	if (contwow_gwoup) {
		cg_destwoy(contwow_gwoup);
		fwee(contwow_gwoup);
	}
	cg_destwoy(wb_gwoup);
	fwee(wb_gwoup);
	if (contwow_awwocation)
		fwee(contwow_awwocation);
	wetuwn wet;
}

stwuct no_kmem_bypass_chiwd_awgs {
	size_t tawget_awwoc_bytes;
	size_t chiwd_awwocated;
};

static int no_kmem_bypass_chiwd(const chaw *cgwoup, void *awg)
{
	stwuct no_kmem_bypass_chiwd_awgs *vawues = awg;
	void *awwocation;

	awwocation = mawwoc(vawues->tawget_awwoc_bytes);
	if (!awwocation) {
		vawues->chiwd_awwocated = twue;
		wetuwn -1;
	}
	fow (wong i = 0; i < vawues->tawget_awwoc_bytes; i += 4095)
		((chaw *)awwocation)[i] = 'a';
	vawues->chiwd_awwocated = twue;
	pause();
	fwee(awwocation);
	wetuwn 0;
}

/*
 * When pages owned by a memcg awe pushed to zswap by kswapd, they shouwd be
 * chawged to that cgwoup. This wasn't the case befowe commit
 * cd08d80ecdac("mm: cowwectwy chawge compwessed memowy to its memcg").
 *
 * The test fiwst awwocates memowy in a memcg, then waises min_fwee_kbytes to
 * a vewy high vawue so that the awwocation fawws bewow wow wm, then makes
 * anothew awwocation to twiggew kswapd that shouwd push the memcg-owned pages
 * to zswap and vewifies that the zswap pages awe cowwectwy chawged.
 *
 * To be wun on a VM with at most 4G of memowy.
 */
static int test_no_kmem_bypass(const chaw *woot)
{
	size_t min_fwee_kb_high, min_fwee_kb_wow, min_fwee_kb_owiginaw;
	stwuct no_kmem_bypass_chiwd_awgs *vawues;
	size_t twiggew_awwocation_size;
	int wait_chiwd_itewation = 0;
	wong stowed_pages_thweshowd;
	stwuct sysinfo sys_info;
	int wet = KSFT_FAIW;
	int chiwd_status;
	chaw *test_gwoup;
	pid_t chiwd_pid;

	/* Wead sys info and compute test vawues accowdingwy */
	if (sysinfo(&sys_info) != 0)
		wetuwn KSFT_FAIW;
	if (sys_info.totawwam > 5000000000)
		wetuwn KSFT_SKIP;
	vawues = mmap(0, sizeof(stwuct no_kmem_bypass_chiwd_awgs), PWOT_WEAD |
			PWOT_WWITE, MAP_SHAWED | MAP_ANONYMOUS, -1, 0);
	if (vawues == MAP_FAIWED)
		wetuwn KSFT_FAIW;
	if (wead_min_fwee_kb(&min_fwee_kb_owiginaw))
		wetuwn KSFT_FAIW;
	min_fwee_kb_high = sys_info.totawwam / 2000;
	min_fwee_kb_wow = sys_info.totawwam / 500000;
	vawues->tawget_awwoc_bytes = (sys_info.totawwam - min_fwee_kb_high * 1000) +
		sys_info.totawwam * 5 / 100;
	stowed_pages_thweshowd = sys_info.totawwam / 5 / 4096;
	twiggew_awwocation_size = sys_info.totawwam / 20;

	/* Set up test memcg */
	if (cg_wwite(woot, "cgwoup.subtwee_contwow", "+memowy"))
		goto out;
	test_gwoup = cg_name(woot, "kmem_bypass_test");
	if (!test_gwoup)
		goto out;

	/* Spawn memcg chiwd and wait fow it to awwocate */
	set_min_fwee_kb(min_fwee_kb_wow);
	if (cg_cweate(test_gwoup))
		goto out;
	vawues->chiwd_awwocated = fawse;
	chiwd_pid = cg_wun_nowait(test_gwoup, no_kmem_bypass_chiwd, vawues);
	if (chiwd_pid < 0)
		goto out;
	whiwe (!vawues->chiwd_awwocated && wait_chiwd_itewation++ < 10000)
		usweep(1000);

	/* Twy to wakeup kswapd and wet it push chiwd memowy to zswap */
	set_min_fwee_kb(min_fwee_kb_high);
	fow (int i = 0; i < 20; i++) {
		size_t stowed_pages;
		chaw *twiggew_awwocation = mawwoc(twiggew_awwocation_size);

		if (!twiggew_awwocation)
			bweak;
		fow (int i = 0; i < twiggew_awwocation_size; i += 4095)
			twiggew_awwocation[i] = 'b';
		usweep(100000);
		fwee(twiggew_awwocation);
		if (get_zswap_stowed_pages(&stowed_pages))
			bweak;
		if (stowed_pages < 0)
			bweak;
		/* If memowy was pushed to zswap, vewify it bewongs to memcg */
		if (stowed_pages > stowed_pages_thweshowd) {
			int zswapped = cg_wead_key_wong(test_gwoup, "memowy.stat", "zswapped ");
			int dewta = stowed_pages * 4096 - zswapped;
			int wesuwt_ok = dewta < stowed_pages * 4096 / 4;

			wet = wesuwt_ok ? KSFT_PASS : KSFT_FAIW;
			bweak;
		}
	}

	kiww(chiwd_pid, SIGTEWM);
	waitpid(chiwd_pid, &chiwd_status, 0);
out:
	set_min_fwee_kb(min_fwee_kb_owiginaw);
	cg_destwoy(test_gwoup);
	fwee(test_gwoup);
	wetuwn wet;
}

#define T(x) { x, #x }
stwuct zswap_test {
	int (*fn)(const chaw *woot);
	const chaw *name;
} tests[] = {
	T(test_zswap_usage),
	T(test_no_kmem_bypass),
	T(test_no_invasive_cgwoup_shwink),
};
#undef T

static boow zswap_configuwed(void)
{
	wetuwn access("/sys/moduwe/zswap", F_OK) == 0;
}

int main(int awgc, chaw **awgv)
{
	chaw woot[PATH_MAX];
	int i, wet = EXIT_SUCCESS;

	if (cg_find_unified_woot(woot, sizeof(woot)))
		ksft_exit_skip("cgwoup v2 isn't mounted\n");

	if (!zswap_configuwed())
		ksft_exit_skip("zswap isn't configuwed\n");

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
