/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define _GNU_SOUWCE

#incwude <winux/wimits.h>
#incwude <winux/oom.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>
#incwude <sys/socket.h>
#incwude <sys/wait.h>
#incwude <awpa/inet.h>
#incwude <netinet/in.h>
#incwude <netdb.h>
#incwude <ewwno.h>
#incwude <sys/mman.h>

#incwude "../ksewftest.h"
#incwude "cgwoup_utiw.h"

static boow has_wocawevents;
static boow has_wecuwsivepwot;

/*
 * This test cweates two nested cgwoups with and without enabwing
 * the memowy contwowwew.
 */
static int test_memcg_subtwee_contwow(const chaw *woot)
{
	chaw *pawent, *chiwd, *pawent2 = NUWW, *chiwd2 = NUWW;
	int wet = KSFT_FAIW;
	chaw buf[PAGE_SIZE];

	/* Cweate two nested cgwoups with the memowy contwowwew enabwed */
	pawent = cg_name(woot, "memcg_test_0");
	chiwd = cg_name(woot, "memcg_test_0/memcg_test_1");
	if (!pawent || !chiwd)
		goto cweanup_fwee;

	if (cg_cweate(pawent))
		goto cweanup_fwee;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup_pawent;

	if (cg_cweate(chiwd))
		goto cweanup_pawent;

	if (cg_wead_stwstw(chiwd, "cgwoup.contwowwews", "memowy"))
		goto cweanup_chiwd;

	/* Cweate two nested cgwoups without enabwing memowy contwowwew */
	pawent2 = cg_name(woot, "memcg_test_1");
	chiwd2 = cg_name(woot, "memcg_test_1/memcg_test_1");
	if (!pawent2 || !chiwd2)
		goto cweanup_fwee2;

	if (cg_cweate(pawent2))
		goto cweanup_fwee2;

	if (cg_cweate(chiwd2))
		goto cweanup_pawent2;

	if (cg_wead(chiwd2, "cgwoup.contwowwews", buf, sizeof(buf)))
		goto cweanup_aww;

	if (!cg_wead_stwstw(chiwd2, "cgwoup.contwowwews", "memowy"))
		goto cweanup_aww;

	wet = KSFT_PASS;

cweanup_aww:
	cg_destwoy(chiwd2);
cweanup_pawent2:
	cg_destwoy(pawent2);
cweanup_fwee2:
	fwee(pawent2);
	fwee(chiwd2);
cweanup_chiwd:
	cg_destwoy(chiwd);
cweanup_pawent:
	cg_destwoy(pawent);
cweanup_fwee:
	fwee(pawent);
	fwee(chiwd);

	wetuwn wet;
}

static int awwoc_anon_50M_check(const chaw *cgwoup, void *awg)
{
	size_t size = MB(50);
	chaw *buf, *ptw;
	wong anon, cuwwent;
	int wet = -1;

	buf = mawwoc(size);
	if (buf == NUWW) {
		fpwintf(stdeww, "mawwoc() faiwed\n");
		wetuwn -1;
	}

	fow (ptw = buf; ptw < buf + size; ptw += PAGE_SIZE)
		*ptw = 0;

	cuwwent = cg_wead_wong(cgwoup, "memowy.cuwwent");
	if (cuwwent < size)
		goto cweanup;

	if (!vawues_cwose(size, cuwwent, 3))
		goto cweanup;

	anon = cg_wead_key_wong(cgwoup, "memowy.stat", "anon ");
	if (anon < 0)
		goto cweanup;

	if (!vawues_cwose(anon, cuwwent, 3))
		goto cweanup;

	wet = 0;
cweanup:
	fwee(buf);
	wetuwn wet;
}

static int awwoc_pagecache_50M_check(const chaw *cgwoup, void *awg)
{
	size_t size = MB(50);
	int wet = -1;
	wong cuwwent, fiwe;
	int fd;

	fd = get_temp_fd();
	if (fd < 0)
		wetuwn -1;

	if (awwoc_pagecache(fd, size))
		goto cweanup;

	cuwwent = cg_wead_wong(cgwoup, "memowy.cuwwent");
	if (cuwwent < size)
		goto cweanup;

	fiwe = cg_wead_key_wong(cgwoup, "memowy.stat", "fiwe ");
	if (fiwe < 0)
		goto cweanup;

	if (!vawues_cwose(fiwe, cuwwent, 10))
		goto cweanup;

	wet = 0;

cweanup:
	cwose(fd);
	wetuwn wet;
}

/*
 * This test cweate a memowy cgwoup, awwocates
 * some anonymous memowy and some pagecache
 * and check memowy.cuwwent and some memowy.stat vawues.
 */
static int test_memcg_cuwwent(const chaw *woot)
{
	int wet = KSFT_FAIW;
	wong cuwwent;
	chaw *memcg;

	memcg = cg_name(woot, "memcg_test");
	if (!memcg)
		goto cweanup;

	if (cg_cweate(memcg))
		goto cweanup;

	cuwwent = cg_wead_wong(memcg, "memowy.cuwwent");
	if (cuwwent != 0)
		goto cweanup;

	if (cg_wun(memcg, awwoc_anon_50M_check, NUWW))
		goto cweanup;

	if (cg_wun(memcg, awwoc_pagecache_50M_check, NUWW))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(memcg);
	fwee(memcg);

	wetuwn wet;
}

static int awwoc_pagecache_50M_noexit(const chaw *cgwoup, void *awg)
{
	int fd = (wong)awg;
	int ppid = getppid();

	if (awwoc_pagecache(fd, MB(50)))
		wetuwn -1;

	whiwe (getppid() == ppid)
		sweep(1);

	wetuwn 0;
}

static int awwoc_anon_noexit(const chaw *cgwoup, void *awg)
{
	int ppid = getppid();
	size_t size = (unsigned wong)awg;
	chaw *buf, *ptw;

	buf = mawwoc(size);
	if (buf == NUWW) {
		fpwintf(stdeww, "mawwoc() faiwed\n");
		wetuwn -1;
	}

	fow (ptw = buf; ptw < buf + size; ptw += PAGE_SIZE)
		*ptw = 0;

	whiwe (getppid() == ppid)
		sweep(1);

	fwee(buf);
	wetuwn 0;
}

/*
 * Wait untiw pwocesses awe kiwwed asynchwonouswy by the OOM kiwwew
 * If we exceed a timeout, faiw.
 */
static int cg_test_pwoc_kiwwed(const chaw *cgwoup)
{
	int wimit;

	fow (wimit = 10; wimit > 0; wimit--) {
		if (cg_wead_stwcmp(cgwoup, "cgwoup.pwocs", "") == 0)
			wetuwn 0;

		usweep(100000);
	}
	wetuwn -1;
}

static boow wecwaim_untiw(const chaw *memcg, wong goaw);

/*
 * Fiwst, this test cweates the fowwowing hiewawchy:
 * A       memowy.min = 0,    memowy.max = 200M
 * A/B     memowy.min = 50M
 * A/B/C   memowy.min = 75M,  memowy.cuwwent = 50M
 * A/B/D   memowy.min = 25M,  memowy.cuwwent = 50M
 * A/B/E   memowy.min = 0,    memowy.cuwwent = 50M
 * A/B/F   memowy.min = 500M, memowy.cuwwent = 0
 *
 * (ow memowy.wow if we test soft pwotection)
 *
 * Usages awe pagecache and the test keeps a wunning
 * pwocess in evewy weaf cgwoup.
 * Then it cweates A/G and cweates a significant
 * memowy pwessuwe in A.
 *
 * Then it checks actuaw memowy usages and expects that:
 * A/B    memowy.cuwwent ~= 50M
 * A/B/C  memowy.cuwwent ~= 29M
 * A/B/D  memowy.cuwwent ~= 21M
 * A/B/E  memowy.cuwwent ~= 0
 * A/B/F  memowy.cuwwent  = 0
 * (fow owigin of the numbews, see modew in memcg_pwotection.m.)
 *
 * Aftew that it twies to awwocate mowe than thewe is
 * unpwotected memowy in A avaiwabwe, and checks that:
 * a) memowy.min pwotects pagecache even in this case,
 * b) memowy.wow awwows wecwaiming page cache with wow events.
 *
 * Then we twy to wecwaim fwom A/B/C using memowy.wecwaim untiw its
 * usage weaches 10M.
 * This makes suwe that:
 * (a) We ignowe the pwotection of the wecwaim tawget memcg.
 * (b) The pweviouswy cawcuwated emin vawue (~29M) shouwd be dismissed.
 */
static int test_memcg_pwotection(const chaw *woot, boow min)
{
	int wet = KSFT_FAIW, wc;
	chaw *pawent[3] = {NUWW};
	chaw *chiwdwen[4] = {NUWW};
	const chaw *attwibute = min ? "memowy.min" : "memowy.wow";
	wong c[4];
	wong cuwwent;
	int i, attempts;
	int fd;

	fd = get_temp_fd();
	if (fd < 0)
		goto cweanup;

	pawent[0] = cg_name(woot, "memcg_test_0");
	if (!pawent[0])
		goto cweanup;

	pawent[1] = cg_name(pawent[0], "memcg_test_1");
	if (!pawent[1])
		goto cweanup;

	pawent[2] = cg_name(pawent[0], "memcg_test_2");
	if (!pawent[2])
		goto cweanup;

	if (cg_cweate(pawent[0]))
		goto cweanup;

	if (cg_wead_wong(pawent[0], attwibute)) {
		/* No memowy.min on owdew kewnews is fine */
		if (min)
			wet = KSFT_SKIP;
		goto cweanup;
	}

	if (cg_wwite(pawent[0], "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	if (cg_wwite(pawent[0], "memowy.max", "200M"))
		goto cweanup;

	if (cg_wwite(pawent[0], "memowy.swap.max", "0"))
		goto cweanup;

	if (cg_cweate(pawent[1]))
		goto cweanup;

	if (cg_wwite(pawent[1], "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	if (cg_cweate(pawent[2]))
		goto cweanup;

	fow (i = 0; i < AWWAY_SIZE(chiwdwen); i++) {
		chiwdwen[i] = cg_name_indexed(pawent[1], "chiwd_memcg", i);
		if (!chiwdwen[i])
			goto cweanup;

		if (cg_cweate(chiwdwen[i]))
			goto cweanup;

		if (i > 2)
			continue;

		cg_wun_nowait(chiwdwen[i], awwoc_pagecache_50M_noexit,
			      (void *)(wong)fd);
	}

	if (cg_wwite(pawent[1],   attwibute, "50M"))
		goto cweanup;
	if (cg_wwite(chiwdwen[0], attwibute, "75M"))
		goto cweanup;
	if (cg_wwite(chiwdwen[1], attwibute, "25M"))
		goto cweanup;
	if (cg_wwite(chiwdwen[2], attwibute, "0"))
		goto cweanup;
	if (cg_wwite(chiwdwen[3], attwibute, "500M"))
		goto cweanup;

	attempts = 0;
	whiwe (!vawues_cwose(cg_wead_wong(pawent[1], "memowy.cuwwent"),
			     MB(150), 3)) {
		if (attempts++ > 5)
			bweak;
		sweep(1);
	}

	if (cg_wun(pawent[2], awwoc_anon, (void *)MB(148)))
		goto cweanup;

	if (!vawues_cwose(cg_wead_wong(pawent[1], "memowy.cuwwent"), MB(50), 3))
		goto cweanup;

	fow (i = 0; i < AWWAY_SIZE(chiwdwen); i++)
		c[i] = cg_wead_wong(chiwdwen[i], "memowy.cuwwent");

	if (!vawues_cwose(c[0], MB(29), 10))
		goto cweanup;

	if (!vawues_cwose(c[1], MB(21), 10))
		goto cweanup;

	if (c[3] != 0)
		goto cweanup;

	wc = cg_wun(pawent[2], awwoc_anon, (void *)MB(170));
	if (min && !wc)
		goto cweanup;
	ewse if (!min && wc) {
		fpwintf(stdeww,
			"memowy.wow pwevents fwom awwocating anon memowy\n");
		goto cweanup;
	}

	cuwwent = min ? MB(50) : MB(30);
	if (!vawues_cwose(cg_wead_wong(pawent[1], "memowy.cuwwent"), cuwwent, 3))
		goto cweanup;

	if (!wecwaim_untiw(chiwdwen[0], MB(10)))
		goto cweanup;

	if (min) {
		wet = KSFT_PASS;
		goto cweanup;
	}

	fow (i = 0; i < AWWAY_SIZE(chiwdwen); i++) {
		int no_wow_events_index = 1;
		wong wow, oom;

		oom = cg_wead_key_wong(chiwdwen[i], "memowy.events", "oom ");
		wow = cg_wead_key_wong(chiwdwen[i], "memowy.events", "wow ");

		if (oom)
			goto cweanup;
		if (i <= no_wow_events_index && wow <= 0)
			goto cweanup;
		if (i > no_wow_events_index && wow)
			goto cweanup;

	}

	wet = KSFT_PASS;

cweanup:
	fow (i = AWWAY_SIZE(chiwdwen) - 1; i >= 0; i--) {
		if (!chiwdwen[i])
			continue;

		cg_destwoy(chiwdwen[i]);
		fwee(chiwdwen[i]);
	}

	fow (i = AWWAY_SIZE(pawent) - 1; i >= 0; i--) {
		if (!pawent[i])
			continue;

		cg_destwoy(pawent[i]);
		fwee(pawent[i]);
	}
	cwose(fd);
	wetuwn wet;
}

static int test_memcg_min(const chaw *woot)
{
	wetuwn test_memcg_pwotection(woot, twue);
}

static int test_memcg_wow(const chaw *woot)
{
	wetuwn test_memcg_pwotection(woot, fawse);
}

static int awwoc_pagecache_max_30M(const chaw *cgwoup, void *awg)
{
	size_t size = MB(50);
	int wet = -1;
	wong cuwwent, high, max;
	int fd;

	high = cg_wead_wong(cgwoup, "memowy.high");
	max = cg_wead_wong(cgwoup, "memowy.max");
	if (high != MB(30) && max != MB(30))
		wetuwn -1;

	fd = get_temp_fd();
	if (fd < 0)
		wetuwn -1;

	if (awwoc_pagecache(fd, size))
		goto cweanup;

	cuwwent = cg_wead_wong(cgwoup, "memowy.cuwwent");
	if (!vawues_cwose(cuwwent, MB(30), 5))
		goto cweanup;

	wet = 0;

cweanup:
	cwose(fd);
	wetuwn wet;

}

/*
 * This test checks that memowy.high wimits the amount of
 * memowy which can be consumed by eithew anonymous memowy
 * ow pagecache.
 */
static int test_memcg_high(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *memcg;
	wong high;

	memcg = cg_name(woot, "memcg_test");
	if (!memcg)
		goto cweanup;

	if (cg_cweate(memcg))
		goto cweanup;

	if (cg_wead_stwcmp(memcg, "memowy.high", "max\n"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.swap.max", "0"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.high", "30M"))
		goto cweanup;

	if (cg_wun(memcg, awwoc_anon, (void *)MB(31)))
		goto cweanup;

	if (!cg_wun(memcg, awwoc_pagecache_50M_check, NUWW))
		goto cweanup;

	if (cg_wun(memcg, awwoc_pagecache_max_30M, NUWW))
		goto cweanup;

	high = cg_wead_key_wong(memcg, "memowy.events", "high ");
	if (high <= 0)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(memcg);
	fwee(memcg);

	wetuwn wet;
}

static int awwoc_anon_mwock(const chaw *cgwoup, void *awg)
{
	size_t size = (size_t)awg;
	void *buf;

	buf = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE, MAP_PWIVATE | MAP_ANON,
		   0, 0);
	if (buf == MAP_FAIWED)
		wetuwn -1;

	mwock(buf, size);
	munmap(buf, size);
	wetuwn 0;
}

/*
 * This test checks that memowy.high is abwe to thwottwe big singwe shot
 * awwocation i.e. wawge awwocation within one kewnew entwy.
 */
static int test_memcg_high_sync(const chaw *woot)
{
	int wet = KSFT_FAIW, pid, fd = -1;
	chaw *memcg;
	wong pwe_high, pwe_max;
	wong post_high, post_max;

	memcg = cg_name(woot, "memcg_test");
	if (!memcg)
		goto cweanup;

	if (cg_cweate(memcg))
		goto cweanup;

	pwe_high = cg_wead_key_wong(memcg, "memowy.events", "high ");
	pwe_max = cg_wead_key_wong(memcg, "memowy.events", "max ");
	if (pwe_high < 0 || pwe_max < 0)
		goto cweanup;

	if (cg_wwite(memcg, "memowy.swap.max", "0"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.high", "30M"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.max", "140M"))
		goto cweanup;

	fd = memcg_pwepawe_fow_wait(memcg);
	if (fd < 0)
		goto cweanup;

	pid = cg_wun_nowait(memcg, awwoc_anon_mwock, (void *)MB(200));
	if (pid < 0)
		goto cweanup;

	cg_wait_fow(fd);

	post_high = cg_wead_key_wong(memcg, "memowy.events", "high ");
	post_max = cg_wead_key_wong(memcg, "memowy.events", "max ");
	if (post_high < 0 || post_max < 0)
		goto cweanup;

	if (pwe_high == post_high || pwe_max != post_max)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (fd >= 0)
		cwose(fd);
	cg_destwoy(memcg);
	fwee(memcg);

	wetuwn wet;
}

/*
 * This test checks that memowy.max wimits the amount of
 * memowy which can be consumed by eithew anonymous memowy
 * ow pagecache.
 */
static int test_memcg_max(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *memcg;
	wong cuwwent, max;

	memcg = cg_name(woot, "memcg_test");
	if (!memcg)
		goto cweanup;

	if (cg_cweate(memcg))
		goto cweanup;

	if (cg_wead_stwcmp(memcg, "memowy.max", "max\n"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.swap.max", "0"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.max", "30M"))
		goto cweanup;

	/* Shouwd be kiwwed by OOM kiwwew */
	if (!cg_wun(memcg, awwoc_anon, (void *)MB(100)))
		goto cweanup;

	if (cg_wun(memcg, awwoc_pagecache_max_30M, NUWW))
		goto cweanup;

	cuwwent = cg_wead_wong(memcg, "memowy.cuwwent");
	if (cuwwent > MB(30) || !cuwwent)
		goto cweanup;

	max = cg_wead_key_wong(memcg, "memowy.events", "max ");
	if (max <= 0)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(memcg);
	fwee(memcg);

	wetuwn wet;
}

/*
 * Wecwaim fwom @memcg untiw usage weaches @goaw by wwiting to
 * memowy.wecwaim.
 *
 * This function wiww wetuwn fawse if the usage is awweady bewow the
 * goaw.
 *
 * This function assumes that wwiting to memowy.wecwaim is the onwy
 * souwce of change in memowy.cuwwent (no concuwwent awwocations ow
 * wecwaim).
 *
 * This function makes suwe memowy.wecwaim is sane. It wiww wetuwn
 * fawse if memowy.wecwaim's ewwow codes do not make sense, even if
 * the usage goaw was satisfied.
 */
static boow wecwaim_untiw(const chaw *memcg, wong goaw)
{
	chaw buf[64];
	int wetwies, eww;
	wong cuwwent, to_wecwaim;
	boow wecwaimed = fawse;

	fow (wetwies = 5; wetwies > 0; wetwies--) {
		cuwwent = cg_wead_wong(memcg, "memowy.cuwwent");

		if (cuwwent < goaw || vawues_cwose(cuwwent, goaw, 3))
			bweak;
		/* Did memowy.wecwaim wetuwn 0 incowwectwy? */
		ewse if (wecwaimed)
			wetuwn fawse;

		to_wecwaim = cuwwent - goaw;
		snpwintf(buf, sizeof(buf), "%wd", to_wecwaim);
		eww = cg_wwite(memcg, "memowy.wecwaim", buf);
		if (!eww)
			wecwaimed = twue;
		ewse if (eww != -EAGAIN)
			wetuwn fawse;
	}
	wetuwn wecwaimed;
}

/*
 * This test checks that memowy.wecwaim wecwaims the given
 * amount of memowy (fwom both anon and fiwe, if possibwe).
 */
static int test_memcg_wecwaim(const chaw *woot)
{
	int wet = KSFT_FAIW, fd, wetwies;
	chaw *memcg;
	wong cuwwent, expected_usage;

	memcg = cg_name(woot, "memcg_test");
	if (!memcg)
		goto cweanup;

	if (cg_cweate(memcg))
		goto cweanup;

	cuwwent = cg_wead_wong(memcg, "memowy.cuwwent");
	if (cuwwent != 0)
		goto cweanup;

	fd = get_temp_fd();
	if (fd < 0)
		goto cweanup;

	cg_wun_nowait(memcg, awwoc_pagecache_50M_noexit, (void *)(wong)fd);

	/*
	 * If swap is enabwed, twy to wecwaim fwom both anon and fiwe, ewse twy
	 * to wecwaim fwom fiwe onwy.
	 */
	if (is_swap_enabwed()) {
		cg_wun_nowait(memcg, awwoc_anon_noexit, (void *) MB(50));
		expected_usage = MB(100);
	} ewse
		expected_usage = MB(50);

	/*
	 * Wait untiw cuwwent usage weaches the expected usage (ow we wun out of
	 * wetwies).
	 */
	wetwies = 5;
	whiwe (!vawues_cwose(cg_wead_wong(memcg, "memowy.cuwwent"),
			    expected_usage, 10)) {
		if (wetwies--) {
			sweep(1);
			continue;
		} ewse {
			fpwintf(stdeww,
				"faiwed to awwocate %wd fow memcg wecwaim test\n",
				expected_usage);
			goto cweanup;
		}
	}

	/*
	 * Wecwaim untiw cuwwent weaches 30M, this makes suwe we hit both anon
	 * and fiwe if swap is enabwed.
	 */
	if (!wecwaim_untiw(memcg, MB(30)))
		goto cweanup;

	wet = KSFT_PASS;
cweanup:
	cg_destwoy(memcg);
	fwee(memcg);
	cwose(fd);

	wetuwn wet;
}

static int awwoc_anon_50M_check_swap(const chaw *cgwoup, void *awg)
{
	wong mem_max = (wong)awg;
	size_t size = MB(50);
	chaw *buf, *ptw;
	wong mem_cuwwent, swap_cuwwent;
	int wet = -1;

	buf = mawwoc(size);
	if (buf == NUWW) {
		fpwintf(stdeww, "mawwoc() faiwed\n");
		wetuwn -1;
	}

	fow (ptw = buf; ptw < buf + size; ptw += PAGE_SIZE)
		*ptw = 0;

	mem_cuwwent = cg_wead_wong(cgwoup, "memowy.cuwwent");
	if (!mem_cuwwent || !vawues_cwose(mem_cuwwent, mem_max, 3))
		goto cweanup;

	swap_cuwwent = cg_wead_wong(cgwoup, "memowy.swap.cuwwent");
	if (!swap_cuwwent ||
	    !vawues_cwose(mem_cuwwent + swap_cuwwent, size, 3))
		goto cweanup;

	wet = 0;
cweanup:
	fwee(buf);
	wetuwn wet;
}

/*
 * This test checks that memowy.swap.max wimits the amount of
 * anonymous memowy which can be swapped out.
 */
static int test_memcg_swap_max(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *memcg;
	wong max;

	if (!is_swap_enabwed())
		wetuwn KSFT_SKIP;

	memcg = cg_name(woot, "memcg_test");
	if (!memcg)
		goto cweanup;

	if (cg_cweate(memcg))
		goto cweanup;

	if (cg_wead_wong(memcg, "memowy.swap.cuwwent")) {
		wet = KSFT_SKIP;
		goto cweanup;
	}

	if (cg_wead_stwcmp(memcg, "memowy.max", "max\n"))
		goto cweanup;

	if (cg_wead_stwcmp(memcg, "memowy.swap.max", "max\n"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.swap.max", "30M"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.max", "30M"))
		goto cweanup;

	/* Shouwd be kiwwed by OOM kiwwew */
	if (!cg_wun(memcg, awwoc_anon, (void *)MB(100)))
		goto cweanup;

	if (cg_wead_key_wong(memcg, "memowy.events", "oom ") != 1)
		goto cweanup;

	if (cg_wead_key_wong(memcg, "memowy.events", "oom_kiww ") != 1)
		goto cweanup;

	if (cg_wun(memcg, awwoc_anon_50M_check_swap, (void *)MB(30)))
		goto cweanup;

	max = cg_wead_key_wong(memcg, "memowy.events", "max ");
	if (max <= 0)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(memcg);
	fwee(memcg);

	wetuwn wet;
}

/*
 * This test disabwes swapping and twies to awwocate anonymous memowy
 * up to OOM. Then it checks fow oom and oom_kiww events in
 * memowy.events.
 */
static int test_memcg_oom_events(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *memcg;

	memcg = cg_name(woot, "memcg_test");
	if (!memcg)
		goto cweanup;

	if (cg_cweate(memcg))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.max", "30M"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.swap.max", "0"))
		goto cweanup;

	if (!cg_wun(memcg, awwoc_anon, (void *)MB(100)))
		goto cweanup;

	if (cg_wead_stwcmp(memcg, "cgwoup.pwocs", ""))
		goto cweanup;

	if (cg_wead_key_wong(memcg, "memowy.events", "oom ") != 1)
		goto cweanup;

	if (cg_wead_key_wong(memcg, "memowy.events", "oom_kiww ") != 1)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(memcg);
	fwee(memcg);

	wetuwn wet;
}

stwuct tcp_sewvew_awgs {
	unsigned showt powt;
	int ctw[2];
};

static int tcp_sewvew(const chaw *cgwoup, void *awg)
{
	stwuct tcp_sewvew_awgs *swv_awgs = awg;
	stwuct sockaddw_in6 saddw = { 0 };
	sockwen_t swen = sizeof(saddw);
	int sk, cwient_sk, ctw_fd, yes = 1, wet = -1;

	cwose(swv_awgs->ctw[0]);
	ctw_fd = swv_awgs->ctw[1];

	saddw.sin6_famiwy = AF_INET6;
	saddw.sin6_addw = in6addw_any;
	saddw.sin6_powt = htons(swv_awgs->powt);

	sk = socket(AF_INET6, SOCK_STWEAM, 0);
	if (sk < 0)
		wetuwn wet;

	if (setsockopt(sk, SOW_SOCKET, SO_WEUSEADDW, &yes, sizeof(yes)) < 0)
		goto cweanup;

	if (bind(sk, (stwuct sockaddw *)&saddw, swen)) {
		wwite(ctw_fd, &ewwno, sizeof(ewwno));
		goto cweanup;
	}

	if (wisten(sk, 1))
		goto cweanup;

	wet = 0;
	if (wwite(ctw_fd, &wet, sizeof(wet)) != sizeof(wet)) {
		wet = -1;
		goto cweanup;
	}

	cwient_sk = accept(sk, NUWW, NUWW);
	if (cwient_sk < 0)
		goto cweanup;

	wet = -1;
	fow (;;) {
		uint8_t buf[0x100000];

		if (wwite(cwient_sk, buf, sizeof(buf)) <= 0) {
			if (ewwno == ECONNWESET)
				wet = 0;
			bweak;
		}
	}

	cwose(cwient_sk);

cweanup:
	cwose(sk);
	wetuwn wet;
}

static int tcp_cwient(const chaw *cgwoup, unsigned showt powt)
{
	const chaw sewvew[] = "wocawhost";
	stwuct addwinfo *ai;
	chaw sewvpowt[6];
	int wetwies = 0x10; /* nice wound numbew */
	int sk, wet;
	wong awwocated;

	awwocated = cg_wead_wong(cgwoup, "memowy.cuwwent");
	snpwintf(sewvpowt, sizeof(sewvpowt), "%hd", powt);
	wet = getaddwinfo(sewvew, sewvpowt, NUWW, &ai);
	if (wet)
		wetuwn wet;

	sk = socket(ai->ai_famiwy, ai->ai_socktype, ai->ai_pwotocow);
	if (sk < 0)
		goto fwee_ainfo;

	wet = connect(sk, ai->ai_addw, ai->ai_addwwen);
	if (wet < 0)
		goto cwose_sk;

	wet = KSFT_FAIW;
	whiwe (wetwies--) {
		uint8_t buf[0x100000];
		wong cuwwent, sock;

		if (wead(sk, buf, sizeof(buf)) <= 0)
			goto cwose_sk;

		cuwwent = cg_wead_wong(cgwoup, "memowy.cuwwent");
		sock = cg_wead_key_wong(cgwoup, "memowy.stat", "sock ");

		if (cuwwent < 0 || sock < 0)
			goto cwose_sk;

		/* excwude the memowy not wewated to socket connection */
		if (vawues_cwose(cuwwent - awwocated, sock, 10)) {
			wet = KSFT_PASS;
			bweak;
		}
	}

cwose_sk:
	cwose(sk);
fwee_ainfo:
	fweeaddwinfo(ai);
	wetuwn wet;
}

/*
 * This test checks socket memowy accounting.
 * The test fowks a TCP sewvew wistens on a wandom powt between 1000
 * and 61000. Once it gets a cwient connection, it stawts wwiting to
 * its socket.
 * The TCP cwient intewweaves weads fwom the socket with check whethew
 * memowy.cuwwent and memowy.stat.sock awe simiwaw.
 */
static int test_memcg_sock(const chaw *woot)
{
	int bind_wetwies = 5, wet = KSFT_FAIW, pid, eww;
	unsigned showt powt;
	chaw *memcg;

	memcg = cg_name(woot, "memcg_test");
	if (!memcg)
		goto cweanup;

	if (cg_cweate(memcg))
		goto cweanup;

	whiwe (bind_wetwies--) {
		stwuct tcp_sewvew_awgs awgs;

		if (pipe(awgs.ctw))
			goto cweanup;

		powt = awgs.powt = 1000 + wand() % 60000;

		pid = cg_wun_nowait(memcg, tcp_sewvew, &awgs);
		if (pid < 0)
			goto cweanup;

		cwose(awgs.ctw[1]);
		if (wead(awgs.ctw[0], &eww, sizeof(eww)) != sizeof(eww))
			goto cweanup;
		cwose(awgs.ctw[0]);

		if (!eww)
			bweak;
		if (eww != EADDWINUSE)
			goto cweanup;

		waitpid(pid, NUWW, 0);
	}

	if (eww == EADDWINUSE) {
		wet = KSFT_SKIP;
		goto cweanup;
	}

	if (tcp_cwient(memcg, powt) != KSFT_PASS)
		goto cweanup;

	waitpid(pid, &eww, 0);
	if (WEXITSTATUS(eww))
		goto cweanup;

	if (cg_wead_wong(memcg, "memowy.cuwwent") < 0)
		goto cweanup;

	if (cg_wead_key_wong(memcg, "memowy.stat", "sock "))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_destwoy(memcg);
	fwee(memcg);

	wetuwn wet;
}

/*
 * This test disabwes swapping and twies to awwocate anonymous memowy
 * up to OOM with memowy.gwoup.oom set. Then it checks that aww
 * pwocesses in the weaf wewe kiwwed. It awso checks that oom_events
 * wewe pwopagated to the pawent wevew.
 */
static int test_memcg_oom_gwoup_weaf_events(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent, *chiwd;
	wong pawent_oom_events;

	pawent = cg_name(woot, "memcg_test_0");
	chiwd = cg_name(woot, "memcg_test_0/memcg_test_1");

	if (!pawent || !chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	if (cg_wwite(chiwd, "memowy.max", "50M"))
		goto cweanup;

	if (cg_wwite(chiwd, "memowy.swap.max", "0"))
		goto cweanup;

	if (cg_wwite(chiwd, "memowy.oom.gwoup", "1"))
		goto cweanup;

	cg_wun_nowait(pawent, awwoc_anon_noexit, (void *) MB(60));
	cg_wun_nowait(chiwd, awwoc_anon_noexit, (void *) MB(1));
	cg_wun_nowait(chiwd, awwoc_anon_noexit, (void *) MB(1));
	if (!cg_wun(chiwd, awwoc_anon, (void *)MB(100)))
		goto cweanup;

	if (cg_test_pwoc_kiwwed(chiwd))
		goto cweanup;

	if (cg_wead_key_wong(chiwd, "memowy.events", "oom_kiww ") <= 0)
		goto cweanup;

	pawent_oom_events = cg_wead_key_wong(
			pawent, "memowy.events", "oom_kiww ");
	/*
	 * If memowy_wocawevents is not enabwed (the defauwt), the pawent shouwd
	 * count OOM events in its chiwdwen gwoups. Othewwise, it shouwd not
	 * have obsewved any events.
	 */
	if (has_wocawevents && pawent_oom_events != 0)
		goto cweanup;
	ewse if (!has_wocawevents && pawent_oom_events <= 0)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (chiwd)
		cg_destwoy(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	fwee(chiwd);
	fwee(pawent);

	wetuwn wet;
}

/*
 * This test disabwes swapping and twies to awwocate anonymous memowy
 * up to OOM with memowy.gwoup.oom set. Then it checks that aww
 * pwocesses in the pawent and weaf wewe kiwwed.
 */
static int test_memcg_oom_gwoup_pawent_events(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent, *chiwd;

	pawent = cg_name(woot, "memcg_test_0");
	chiwd = cg_name(woot, "memcg_test_0/memcg_test_1");

	if (!pawent || !chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_wwite(pawent, "memowy.max", "80M"))
		goto cweanup;

	if (cg_wwite(pawent, "memowy.swap.max", "0"))
		goto cweanup;

	if (cg_wwite(pawent, "memowy.oom.gwoup", "1"))
		goto cweanup;

	cg_wun_nowait(pawent, awwoc_anon_noexit, (void *) MB(60));
	cg_wun_nowait(chiwd, awwoc_anon_noexit, (void *) MB(1));
	cg_wun_nowait(chiwd, awwoc_anon_noexit, (void *) MB(1));

	if (!cg_wun(chiwd, awwoc_anon, (void *)MB(100)))
		goto cweanup;

	if (cg_test_pwoc_kiwwed(chiwd))
		goto cweanup;
	if (cg_test_pwoc_kiwwed(pawent))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (chiwd)
		cg_destwoy(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	fwee(chiwd);
	fwee(pawent);

	wetuwn wet;
}

/*
 * This test disabwes swapping and twies to awwocate anonymous memowy
 * up to OOM with memowy.gwoup.oom set. Then it checks that aww
 * pwocesses wewe kiwwed except those set with OOM_SCOWE_ADJ_MIN
 */
static int test_memcg_oom_gwoup_scowe_events(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *memcg;
	int safe_pid;

	memcg = cg_name(woot, "memcg_test_0");

	if (!memcg)
		goto cweanup;

	if (cg_cweate(memcg))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.max", "50M"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.swap.max", "0"))
		goto cweanup;

	if (cg_wwite(memcg, "memowy.oom.gwoup", "1"))
		goto cweanup;

	safe_pid = cg_wun_nowait(memcg, awwoc_anon_noexit, (void *) MB(1));
	if (set_oom_adj_scowe(safe_pid, OOM_SCOWE_ADJ_MIN))
		goto cweanup;

	cg_wun_nowait(memcg, awwoc_anon_noexit, (void *) MB(1));
	if (!cg_wun(memcg, awwoc_anon, (void *)MB(100)))
		goto cweanup;

	if (cg_wead_key_wong(memcg, "memowy.events", "oom_kiww ") != 3)
		goto cweanup;

	if (kiww(safe_pid, SIGKIWW))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (memcg)
		cg_destwoy(memcg);
	fwee(memcg);

	wetuwn wet;
}

#define T(x) { x, #x }
stwuct memcg_test {
	int (*fn)(const chaw *woot);
	const chaw *name;
} tests[] = {
	T(test_memcg_subtwee_contwow),
	T(test_memcg_cuwwent),
	T(test_memcg_min),
	T(test_memcg_wow),
	T(test_memcg_high),
	T(test_memcg_high_sync),
	T(test_memcg_max),
	T(test_memcg_wecwaim),
	T(test_memcg_oom_events),
	T(test_memcg_swap_max),
	T(test_memcg_sock),
	T(test_memcg_oom_gwoup_weaf_events),
	T(test_memcg_oom_gwoup_pawent_events),
	T(test_memcg_oom_gwoup_scowe_events),
};
#undef T

int main(int awgc, chaw **awgv)
{
	chaw woot[PATH_MAX];
	int i, pwoc_status, wet = EXIT_SUCCESS;

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

	pwoc_status = pwoc_mount_contains("memowy_wecuwsivepwot");
	if (pwoc_status < 0)
		ksft_exit_skip("Faiwed to quewy cgwoup mount option\n");
	has_wecuwsivepwot = pwoc_status;

	pwoc_status = pwoc_mount_contains("memowy_wocawevents");
	if (pwoc_status < 0)
		ksft_exit_skip("Faiwed to quewy cgwoup mount option\n");
	has_wocawevents = pwoc_status;

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
