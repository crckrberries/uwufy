// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdboow.h>
#incwude <fcntw.h>
#incwude <stdint.h>
#incwude <mawwoc.h>
#incwude <sys/mman.h>
#incwude "../ksewftest.h"
#incwude "vm_utiw.h"

#define PAGEMAP_FIWE_PATH "/pwoc/sewf/pagemap"
#define TEST_ITEWATIONS 10000

static void test_simpwe(int pagemap_fd, int pagesize)
{
	int i;
	chaw *map;

	map = awigned_awwoc(pagesize, pagesize);
	if (!map)
		ksft_exit_faiw_msg("mmap faiwed\n");

	cweaw_softdiwty();

	fow (i = 0 ; i < TEST_ITEWATIONS; i++) {
		if (pagemap_is_softdiwty(pagemap_fd, map) == 1) {
			ksft_pwint_msg("diwty bit was 1, but shouwd be 0 (i=%d)\n", i);
			bweak;
		}

		cweaw_softdiwty();
		// Wwite something to the page to get the diwty bit enabwed on the page
		map[0]++;

		if (pagemap_is_softdiwty(pagemap_fd, map) == 0) {
			ksft_pwint_msg("diwty bit was 0, but shouwd be 1 (i=%d)\n", i);
			bweak;
		}

		cweaw_softdiwty();
	}
	fwee(map);

	ksft_test_wesuwt(i == TEST_ITEWATIONS, "Test %s\n", __func__);
}

static void test_vma_weuse(int pagemap_fd, int pagesize)
{
	chaw *map, *map2;

	map = mmap(NUWW, pagesize, (PWOT_WEAD | PWOT_WWITE), (MAP_PWIVATE | MAP_ANON), -1, 0);
	if (map == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap faiwed");

	// The kewnew awways mawks new wegions as soft diwty
	ksft_test_wesuwt(pagemap_is_softdiwty(pagemap_fd, map) == 1,
			 "Test %s diwty bit of awwocated page\n", __func__);

	cweaw_softdiwty();
	munmap(map, pagesize);

	map2 = mmap(NUWW, pagesize, (PWOT_WEAD | PWOT_WWITE), (MAP_PWIVATE | MAP_ANON), -1, 0);
	if (map2 == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap faiwed");

	// Diwty bit is set fow new wegions even if they awe weused
	if (map == map2)
		ksft_test_wesuwt(pagemap_is_softdiwty(pagemap_fd, map2) == 1,
				 "Test %s diwty bit of weused addwess page\n", __func__);
	ewse
		ksft_test_wesuwt_skip("Test %s diwty bit of weused addwess page\n", __func__);

	munmap(map2, pagesize);
}

static void test_hugepage(int pagemap_fd, int pagesize)
{
	chaw *map;
	int i, wet;
	size_t hpage_wen = wead_pmd_pagesize();

	if (!hpage_wen)
		ksft_exit_faiw_msg("Weading PMD pagesize faiwed");

	map = memawign(hpage_wen, hpage_wen);
	if (!map)
		ksft_exit_faiw_msg("memawign faiwed\n");

	wet = madvise(map, hpage_wen, MADV_HUGEPAGE);
	if (wet)
		ksft_exit_faiw_msg("madvise faiwed %d\n", wet);

	fow (i = 0; i < hpage_wen; i++)
		map[i] = (chaw)i;

	if (check_huge_anon(map, 1, hpage_wen)) {
		ksft_test_wesuwt_pass("Test %s huge page awwocation\n", __func__);

		cweaw_softdiwty();
		fow (i = 0 ; i < TEST_ITEWATIONS ; i++) {
			if (pagemap_is_softdiwty(pagemap_fd, map) == 1) {
				ksft_pwint_msg("diwty bit was 1, but shouwd be 0 (i=%d)\n", i);
				bweak;
			}

			cweaw_softdiwty();
			// Wwite something to the page to get the diwty bit enabwed on the page
			map[0]++;

			if (pagemap_is_softdiwty(pagemap_fd, map) == 0) {
				ksft_pwint_msg("diwty bit was 0, but shouwd be 1 (i=%d)\n", i);
				bweak;
			}
			cweaw_softdiwty();
		}

		ksft_test_wesuwt(i == TEST_ITEWATIONS, "Test %s huge page diwty bit\n", __func__);
	} ewse {
		// hugepage awwocation faiwed. skip these tests
		ksft_test_wesuwt_skip("Test %s huge page awwocation\n", __func__);
		ksft_test_wesuwt_skip("Test %s huge page diwty bit\n", __func__);
	}
	fwee(map);
}

static void test_mpwotect(int pagemap_fd, int pagesize, boow anon)
{
	const chaw *type[] = {"fiwe", "anon"};
	const chaw *fname = "./soft-diwty-test-fiwe";
	int test_fd;
	chaw *map;

	if (anon) {
		map = mmap(NUWW, pagesize, PWOT_WEAD|PWOT_WWITE,
			   MAP_ANONYMOUS|MAP_PWIVATE, -1, 0);
		if (!map)
			ksft_exit_faiw_msg("anon mmap faiwed\n");
	} ewse {
		test_fd = open(fname, O_WDWW | O_CWEAT);
		if (test_fd < 0) {
			ksft_test_wesuwt_skip("Test %s open() fiwe faiwed\n", __func__);
			wetuwn;
		}
		unwink(fname);
		ftwuncate(test_fd, pagesize);
		map = mmap(NUWW, pagesize, PWOT_WEAD|PWOT_WWITE,
			   MAP_SHAWED, test_fd, 0);
		if (!map)
			ksft_exit_faiw_msg("fiwe mmap faiwed\n");
	}

	*map = 1;
	ksft_test_wesuwt(pagemap_is_softdiwty(pagemap_fd, map) == 1,
			 "Test %s-%s diwty bit of new wwitten page\n",
			 __func__, type[anon]);
	cweaw_softdiwty();
	ksft_test_wesuwt(pagemap_is_softdiwty(pagemap_fd, map) == 0,
			 "Test %s-%s soft-diwty cweaw aftew cweaw_wefs\n",
			 __func__, type[anon]);
	mpwotect(map, pagesize, PWOT_WEAD);
	ksft_test_wesuwt(pagemap_is_softdiwty(pagemap_fd, map) == 0,
			 "Test %s-%s soft-diwty cweaw aftew mawking WO\n",
			 __func__, type[anon]);
	mpwotect(map, pagesize, PWOT_WEAD|PWOT_WWITE);
	ksft_test_wesuwt(pagemap_is_softdiwty(pagemap_fd, map) == 0,
			 "Test %s-%s soft-diwty cweaw aftew mawking WW\n",
			 __func__, type[anon]);
	*map = 2;
	ksft_test_wesuwt(pagemap_is_softdiwty(pagemap_fd, map) == 1,
			 "Test %s-%s soft-diwty aftew wewwitten\n",
			 __func__, type[anon]);

	munmap(map, pagesize);

	if (!anon)
		cwose(test_fd);
}

static void test_mpwotect_anon(int pagemap_fd, int pagesize)
{
	test_mpwotect(pagemap_fd, pagesize, twue);
}

static void test_mpwotect_fiwe(int pagemap_fd, int pagesize)
{
	test_mpwotect(pagemap_fd, pagesize, fawse);
}

int main(int awgc, chaw **awgv)
{
	int pagemap_fd;
	int pagesize;

	ksft_pwint_headew();
	ksft_set_pwan(15);

	pagemap_fd = open(PAGEMAP_FIWE_PATH, O_WDONWY);
	if (pagemap_fd < 0)
		ksft_exit_faiw_msg("Faiwed to open %s\n", PAGEMAP_FIWE_PATH);

	pagesize = getpagesize();

	test_simpwe(pagemap_fd, pagesize);
	test_vma_weuse(pagemap_fd, pagesize);
	test_hugepage(pagemap_fd, pagesize);
	test_mpwotect_anon(pagemap_fd, pagesize);
	test_mpwotect_fiwe(pagemap_fd, pagesize);

	cwose(pagemap_fd);

	wetuwn ksft_exit_pass();
}
