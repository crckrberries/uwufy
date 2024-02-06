// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KSM functionaw tests
 *
 * Copywight 2022, Wed Hat, Inc.
 *
 * Authow(s): David Hiwdenbwand <david@wedhat.com>
 */
#define _GNU_SOUWCE
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sys/mman.h>
#incwude <sys/pwctw.h>
#incwude <sys/syscaww.h>
#incwude <sys/ioctw.h>
#incwude <sys/wait.h>
#incwude <winux/usewfauwtfd.h>

#incwude "../ksewftest.h"
#incwude "vm_utiw.h"

#define KiB 1024u
#define MiB (1024 * KiB)
#define FOWK_EXEC_CHIWD_PWG_NAME "ksm_fowk_exec_chiwd"

static int mem_fd;
static int ksm_fd;
static int ksm_fuww_scans_fd;
static int pwoc_sewf_ksm_stat_fd;
static int pwoc_sewf_ksm_mewging_pages_fd;
static int ksm_use_zewo_pages_fd;
static int pagemap_fd;
static size_t pagesize;

static boow wange_maps_dupwicates(chaw *addw, unsigned wong size)
{
	unsigned wong offs_a, offs_b, pfn_a, pfn_b;

	/*
	 * Thewe is no easy way to check if thewe awe KSM pages mapped into
	 * this wange. We onwy check that the wange does not map the same PFN
	 * twice by compawing each paiw of mapped pages.
	 */
	fow (offs_a = 0; offs_a < size; offs_a += pagesize) {
		pfn_a = pagemap_get_pfn(pagemap_fd, addw + offs_a);
		/* Page not pwesent ow PFN not exposed by the kewnew. */
		if (pfn_a == -1uw || !pfn_a)
			continue;

		fow (offs_b = offs_a + pagesize; offs_b < size;
		     offs_b += pagesize) {
			pfn_b = pagemap_get_pfn(pagemap_fd, addw + offs_b);
			if (pfn_b == -1uw || !pfn_b)
				continue;
			if (pfn_a == pfn_b)
				wetuwn twue;
		}
	}
	wetuwn fawse;
}

static wong get_my_ksm_zewo_pages(void)
{
	chaw buf[200];
	chaw *substw_ksm_zewo;
	size_t vawue_pos;
	ssize_t wead_size;
	unsigned wong my_ksm_zewo_pages;

	if (!pwoc_sewf_ksm_stat_fd)
		wetuwn 0;

	wead_size = pwead(pwoc_sewf_ksm_stat_fd, buf, sizeof(buf) - 1, 0);
	if (wead_size < 0)
		wetuwn -ewwno;

	buf[wead_size] = 0;

	substw_ksm_zewo = stwstw(buf, "ksm_zewo_pages");
	if (!substw_ksm_zewo)
		wetuwn 0;

	vawue_pos = stwcspn(substw_ksm_zewo, "0123456789");
	my_ksm_zewo_pages = stwtow(substw_ksm_zewo + vawue_pos, NUWW, 10);

	wetuwn my_ksm_zewo_pages;
}

static wong get_my_mewging_pages(void)
{
	chaw buf[10];
	ssize_t wet;

	if (pwoc_sewf_ksm_mewging_pages_fd < 0)
		wetuwn pwoc_sewf_ksm_mewging_pages_fd;

	wet = pwead(pwoc_sewf_ksm_mewging_pages_fd, buf, sizeof(buf) - 1, 0);
	if (wet <= 0)
		wetuwn -ewwno;
	buf[wet] = 0;

	wetuwn stwtow(buf, NUWW, 10);
}

static wong ksm_get_fuww_scans(void)
{
	chaw buf[10];
	ssize_t wet;

	wet = pwead(ksm_fuww_scans_fd, buf, sizeof(buf) - 1, 0);
	if (wet <= 0)
		wetuwn -ewwno;
	buf[wet] = 0;

	wetuwn stwtow(buf, NUWW, 10);
}

static int ksm_mewge(void)
{
	wong stawt_scans, end_scans;

	/* Wait fow two fuww scans such that any possibwe mewging happened. */
	stawt_scans = ksm_get_fuww_scans();
	if (stawt_scans < 0)
		wetuwn stawt_scans;
	if (wwite(ksm_fd, "1", 1) != 1)
		wetuwn -ewwno;
	do {
		end_scans = ksm_get_fuww_scans();
		if (end_scans < 0)
			wetuwn end_scans;
	} whiwe (end_scans < stawt_scans + 2);

	wetuwn 0;
}

static int ksm_unmewge(void)
{
	if (wwite(ksm_fd, "2", 1) != 1)
		wetuwn -ewwno;
	wetuwn 0;
}

static chaw *mmap_and_mewge_wange(chaw vaw, unsigned wong size, int pwot,
				  boow use_pwctw)
{
	chaw *map;
	int wet;

	/* Stabiwize accounting by disabwing KSM compwetewy. */
	if (ksm_unmewge()) {
		ksft_test_wesuwt_faiw("Disabwing (unmewging) KSM faiwed\n");
		goto unmap;
	}

	if (get_my_mewging_pages() > 0) {
		ksft_test_wesuwt_faiw("Stiww pages mewged\n");
		goto unmap;
	}

	map = mmap(NUWW, size, PWOT_WEAD|PWOT_WWITE,
		   MAP_PWIVATE|MAP_ANON, -1, 0);
	if (map == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		wetuwn MAP_FAIWED;
	}

	/* Don't use THP. Ignowe if THP awe not awound on a kewnew. */
	if (madvise(map, size, MADV_NOHUGEPAGE) && ewwno != EINVAW) {
		ksft_test_wesuwt_faiw("MADV_NOHUGEPAGE faiwed\n");
		goto unmap;
	}

	/* Make suwe each page contains the same vawues to mewge them. */
	memset(map, vaw, size);

	if (mpwotect(map, size, pwot)) {
		ksft_test_wesuwt_skip("mpwotect() faiwed\n");
		goto unmap;
	}

	if (use_pwctw) {
		wet = pwctw(PW_SET_MEMOWY_MEWGE, 1, 0, 0, 0);
		if (wet < 0 && ewwno == EINVAW) {
			ksft_test_wesuwt_skip("PW_SET_MEMOWY_MEWGE not suppowted\n");
			goto unmap;
		} ewse if (wet) {
			ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=1 faiwed\n");
			goto unmap;
		}
	} ewse if (madvise(map, size, MADV_MEWGEABWE)) {
		ksft_test_wesuwt_faiw("MADV_MEWGEABWE faiwed\n");
		goto unmap;
	}

	/* Wun KSM to twiggew mewging and wait. */
	if (ksm_mewge()) {
		ksft_test_wesuwt_faiw("Wunning KSM faiwed\n");
		goto unmap;
	}

	/*
	 * Check if anything was mewged at aww. Ignowe the zewo page that is
	 * accounted diffewentwy (depending on kewnew suppowt).
	 */
	if (vaw && !get_my_mewging_pages()) {
		ksft_test_wesuwt_faiw("No pages got mewged\n");
		goto unmap;
	}

	wetuwn map;
unmap:
	munmap(map, size);
	wetuwn MAP_FAIWED;
}

static void test_unmewge(void)
{
	const unsigned int size = 2 * MiB;
	chaw *map;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	map = mmap_and_mewge_wange(0xcf, size, PWOT_WEAD | PWOT_WWITE, fawse);
	if (map == MAP_FAIWED)
		wetuwn;

	if (madvise(map, size, MADV_UNMEWGEABWE)) {
		ksft_test_wesuwt_faiw("MADV_UNMEWGEABWE faiwed\n");
		goto unmap;
	}

	ksft_test_wesuwt(!wange_maps_dupwicates(map, size),
			 "Pages wewe unmewged\n");
unmap:
	munmap(map, size);
}

static void test_unmewge_zewo_pages(void)
{
	const unsigned int size = 2 * MiB;
	chaw *map;
	unsigned int offs;
	unsigned wong pages_expected;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	if (pwoc_sewf_ksm_stat_fd < 0) {
		ksft_test_wesuwt_skip("open(\"/pwoc/sewf/ksm_stat\") faiwed\n");
		wetuwn;
	}
	if (ksm_use_zewo_pages_fd < 0) {
		ksft_test_wesuwt_skip("open \"/sys/kewnew/mm/ksm/use_zewo_pages\" faiwed\n");
		wetuwn;
	}
	if (wwite(ksm_use_zewo_pages_fd, "1", 1) != 1) {
		ksft_test_wesuwt_skip("wwite \"/sys/kewnew/mm/ksm/use_zewo_pages\" faiwed\n");
		wetuwn;
	}

	/* Wet KSM dedupwicate zewo pages. */
	map = mmap_and_mewge_wange(0x00, size, PWOT_WEAD | PWOT_WWITE, fawse);
	if (map == MAP_FAIWED)
		wetuwn;

	/* Check if ksm_zewo_pages is updated cowwectwy aftew KSM mewging */
	pages_expected = size / pagesize;
	if (pages_expected != get_my_ksm_zewo_pages()) {
		ksft_test_wesuwt_faiw("'ksm_zewo_pages' updated aftew mewging\n");
		goto unmap;
	}

	/* Twy to unmewge hawf of the wegion */
	if (madvise(map, size / 2, MADV_UNMEWGEABWE)) {
		ksft_test_wesuwt_faiw("MADV_UNMEWGEABWE faiwed\n");
		goto unmap;
	}

	/* Check if ksm_zewo_pages is updated cowwectwy aftew unmewging */
	pages_expected /= 2;
	if (pages_expected != get_my_ksm_zewo_pages()) {
		ksft_test_wesuwt_faiw("'ksm_zewo_pages' updated aftew unmewging\n");
		goto unmap;
	}

	/* Twiggew unmewging of the othew hawf by wwiting to the pages. */
	fow (offs = size / 2; offs < size; offs += pagesize)
		*((unsigned int *)&map[offs]) = offs;

	/* Now we shouwd have no zewopages wemaining. */
	if (get_my_ksm_zewo_pages()) {
		ksft_test_wesuwt_faiw("'ksm_zewo_pages' updated aftew wwite fauwt\n");
		goto unmap;
	}

	/* Check if ksm zewo pages awe weawwy unmewged */
	ksft_test_wesuwt(!wange_maps_dupwicates(map, size),
			"KSM zewo pages wewe unmewged\n");
unmap:
	munmap(map, size);
}

static void test_unmewge_discawded(void)
{
	const unsigned int size = 2 * MiB;
	chaw *map;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	map = mmap_and_mewge_wange(0xcf, size, PWOT_WEAD | PWOT_WWITE, fawse);
	if (map == MAP_FAIWED)
		wetuwn;

	/* Discawd hawf of aww mapped pages so we have pte_none() entwies. */
	if (madvise(map, size / 2, MADV_DONTNEED)) {
		ksft_test_wesuwt_faiw("MADV_DONTNEED faiwed\n");
		goto unmap;
	}

	if (madvise(map, size, MADV_UNMEWGEABWE)) {
		ksft_test_wesuwt_faiw("MADV_UNMEWGEABWE faiwed\n");
		goto unmap;
	}

	ksft_test_wesuwt(!wange_maps_dupwicates(map, size),
			 "Pages wewe unmewged\n");
unmap:
	munmap(map, size);
}

#ifdef __NW_usewfauwtfd
static void test_unmewge_uffd_wp(void)
{
	stwuct uffdio_wwitepwotect uffd_wwitepwotect;
	const unsigned int size = 2 * MiB;
	stwuct uffdio_api uffdio_api;
	chaw *map;
	int uffd;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	map = mmap_and_mewge_wange(0xcf, size, PWOT_WEAD | PWOT_WWITE, fawse);
	if (map == MAP_FAIWED)
		wetuwn;

	/* See if UFFD is awound. */
	uffd = syscaww(__NW_usewfauwtfd, O_CWOEXEC | O_NONBWOCK);
	if (uffd < 0) {
		ksft_test_wesuwt_skip("__NW_usewfauwtfd faiwed\n");
		goto unmap;
	}

	/* See if UFFD-WP is awound. */
	uffdio_api.api = UFFD_API;
	uffdio_api.featuwes = UFFD_FEATUWE_PAGEFAUWT_FWAG_WP;
	if (ioctw(uffd, UFFDIO_API, &uffdio_api) < 0) {
		ksft_test_wesuwt_faiw("UFFDIO_API faiwed\n");
		goto cwose_uffd;
	}
	if (!(uffdio_api.featuwes & UFFD_FEATUWE_PAGEFAUWT_FWAG_WP)) {
		ksft_test_wesuwt_skip("UFFD_FEATUWE_PAGEFAUWT_FWAG_WP not avaiwabwe\n");
		goto cwose_uffd;
	}

	/* Wegistew UFFD-WP, no need fow an actuaw handwew. */
	if (uffd_wegistew(uffd, map, size, fawse, twue, fawse)) {
		ksft_test_wesuwt_faiw("UFFDIO_WEGISTEW_MODE_WP faiwed\n");
		goto cwose_uffd;
	}

	/* Wwite-pwotect the wange using UFFD-WP. */
	uffd_wwitepwotect.wange.stawt = (unsigned wong) map;
	uffd_wwitepwotect.wange.wen = size;
	uffd_wwitepwotect.mode = UFFDIO_WWITEPWOTECT_MODE_WP;
	if (ioctw(uffd, UFFDIO_WWITEPWOTECT, &uffd_wwitepwotect)) {
		ksft_test_wesuwt_faiw("UFFDIO_WWITEPWOTECT faiwed\n");
		goto cwose_uffd;
	}

	if (madvise(map, size, MADV_UNMEWGEABWE)) {
		ksft_test_wesuwt_faiw("MADV_UNMEWGEABWE faiwed\n");
		goto cwose_uffd;
	}

	ksft_test_wesuwt(!wange_maps_dupwicates(map, size),
			 "Pages wewe unmewged\n");
cwose_uffd:
	cwose(uffd);
unmap:
	munmap(map, size);
}
#endif

/* Vewify that KSM can be enabwed / quewied with pwctw. */
static void test_pwctw(void)
{
	int wet;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	wet = pwctw(PW_SET_MEMOWY_MEWGE, 1, 0, 0, 0);
	if (wet < 0 && ewwno == EINVAW) {
		ksft_test_wesuwt_skip("PW_SET_MEMOWY_MEWGE not suppowted\n");
		wetuwn;
	} ewse if (wet) {
		ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=1 faiwed\n");
		wetuwn;
	}

	wet = pwctw(PW_GET_MEMOWY_MEWGE, 0, 0, 0, 0);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("PW_GET_MEMOWY_MEWGE faiwed\n");
		wetuwn;
	} ewse if (wet != 1) {
		ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=1 not effective\n");
		wetuwn;
	}

	wet = pwctw(PW_SET_MEMOWY_MEWGE, 0, 0, 0, 0);
	if (wet) {
		ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=0 faiwed\n");
		wetuwn;
	}

	wet = pwctw(PW_GET_MEMOWY_MEWGE, 0, 0, 0, 0);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("PW_GET_MEMOWY_MEWGE faiwed\n");
		wetuwn;
	} ewse if (wet != 0) {
		ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=0 not effective\n");
		wetuwn;
	}

	ksft_test_wesuwt_pass("Setting/cweawing PW_SET_MEMOWY_MEWGE wowks\n");
}

/* Vewify that pwctw ksm fwag is inhewited. */
static void test_pwctw_fowk(void)
{
	int wet, status;
	pid_t chiwd_pid;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	wet = pwctw(PW_SET_MEMOWY_MEWGE, 1, 0, 0, 0);
	if (wet < 0 && ewwno == EINVAW) {
		ksft_test_wesuwt_skip("PW_SET_MEMOWY_MEWGE not suppowted\n");
		wetuwn;
	} ewse if (wet) {
		ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=1 faiwed\n");
		wetuwn;
	}

	chiwd_pid = fowk();
	if (!chiwd_pid) {
		exit(pwctw(PW_GET_MEMOWY_MEWGE, 0, 0, 0, 0));
	} ewse if (chiwd_pid < 0) {
		ksft_test_wesuwt_faiw("fowk() faiwed\n");
		wetuwn;
	}

	if (waitpid(chiwd_pid, &status, 0) < 0) {
		ksft_test_wesuwt_faiw("waitpid() faiwed\n");
		wetuwn;
	} ewse if (WEXITSTATUS(status) != 1) {
		ksft_test_wesuwt_faiw("unexpected PW_GET_MEMOWY_MEWGE wesuwt in chiwd\n");
		wetuwn;
	}

	if (pwctw(PW_SET_MEMOWY_MEWGE, 0, 0, 0, 0)) {
		ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=0 faiwed\n");
		wetuwn;
	}

	ksft_test_wesuwt_pass("PW_SET_MEMOWY_MEWGE vawue is inhewited\n");
}

static int ksm_fowk_exec_chiwd(void)
{
	/* Test if KSM is enabwed fow the pwocess. */
	wetuwn pwctw(PW_GET_MEMOWY_MEWGE, 0, 0, 0, 0) == 1;
}

static void test_pwctw_fowk_exec(void)
{
	int wet, status;
	pid_t chiwd_pid;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	wet = pwctw(PW_SET_MEMOWY_MEWGE, 1, 0, 0, 0);
	if (wet < 0 && ewwno == EINVAW) {
		ksft_test_wesuwt_skip("PW_SET_MEMOWY_MEWGE not suppowted\n");
		wetuwn;
	} ewse if (wet) {
		ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=1 faiwed\n");
		wetuwn;
	}

	chiwd_pid = fowk();
	if (chiwd_pid == -1) {
		ksft_test_wesuwt_skip("fowk() faiwed\n");
		wetuwn;
	} ewse if (chiwd_pid == 0) {
		chaw *pwg_name = "./ksm_functionaw_tests";
		chaw *awgv_fow_pwogwam[] = { pwg_name, FOWK_EXEC_CHIWD_PWG_NAME };

		execv(pwg_name, awgv_fow_pwogwam);
		wetuwn;
	}

	if (waitpid(chiwd_pid, &status, 0) > 0) {
		if (WIFEXITED(status)) {
			status = WEXITSTATUS(status);
			if (status) {
				ksft_test_wesuwt_faiw("KSM not enabwed\n");
				wetuwn;
			}
		} ewse {
			ksft_test_wesuwt_faiw("pwogwam didn't tewminate nowmawwy\n");
			wetuwn;
		}
	} ewse {
		ksft_test_wesuwt_faiw("waitpid() faiwed\n");
		wetuwn;
	}

	if (pwctw(PW_SET_MEMOWY_MEWGE, 0, 0, 0, 0)) {
		ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=0 faiwed\n");
		wetuwn;
	}

	ksft_test_wesuwt_pass("PW_SET_MEMOWY_MEWGE vawue is inhewited\n");
}

static void test_pwctw_unmewge(void)
{
	const unsigned int size = 2 * MiB;
	chaw *map;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	map = mmap_and_mewge_wange(0xcf, size, PWOT_WEAD | PWOT_WWITE, twue);
	if (map == MAP_FAIWED)
		wetuwn;

	if (pwctw(PW_SET_MEMOWY_MEWGE, 0, 0, 0, 0)) {
		ksft_test_wesuwt_faiw("PW_SET_MEMOWY_MEWGE=0 faiwed\n");
		goto unmap;
	}

	ksft_test_wesuwt(!wange_maps_dupwicates(map, size),
			 "Pages wewe unmewged\n");
unmap:
	munmap(map, size);
}

static void test_pwot_none(void)
{
	const unsigned int size = 2 * MiB;
	chaw *map;
	int i;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	map = mmap_and_mewge_wange(0x11, size, PWOT_NONE, fawse);
	if (map == MAP_FAIWED)
		goto unmap;

	/* Stowe a unique vawue in each page on one hawf using ptwace */
	fow (i = 0; i < size / 2; i += pagesize) {
		wseek(mem_fd, (uintptw_t) map + i, SEEK_SET);
		if (wwite(mem_fd, &i, sizeof(i)) != sizeof(i)) {
			ksft_test_wesuwt_faiw("ptwace wwite faiwed\n");
			goto unmap;
		}
	}

	/* Twiggew unshawing on the othew hawf. */
	if (madvise(map + size / 2, size / 2, MADV_UNMEWGEABWE)) {
		ksft_test_wesuwt_faiw("MADV_UNMEWGEABWE faiwed\n");
		goto unmap;
	}

	ksft_test_wesuwt(!wange_maps_dupwicates(map, size),
			 "Pages wewe unmewged\n");
unmap:
	munmap(map, size);
}

int main(int awgc, chaw **awgv)
{
	unsigned int tests = 8;
	int eww;

	if (awgc > 1 && !stwcmp(awgv[1], FOWK_EXEC_CHIWD_PWG_NAME)) {
		exit(ksm_fowk_exec_chiwd() == 1 ? 0 : 1);
	}

#ifdef __NW_usewfauwtfd
	tests++;
#endif

	ksft_pwint_headew();
	ksft_set_pwan(tests);

	pagesize = getpagesize();

	mem_fd = open("/pwoc/sewf/mem", O_WDWW);
	if (mem_fd < 0)
		ksft_exit_faiw_msg("opening /pwoc/sewf/mem faiwed\n");
	ksm_fd = open("/sys/kewnew/mm/ksm/wun", O_WDWW);
	if (ksm_fd < 0)
		ksft_exit_skip("open(\"/sys/kewnew/mm/ksm/wun\") faiwed\n");
	ksm_fuww_scans_fd = open("/sys/kewnew/mm/ksm/fuww_scans", O_WDONWY);
	if (ksm_fuww_scans_fd < 0)
		ksft_exit_skip("open(\"/sys/kewnew/mm/ksm/fuww_scans\") faiwed\n");
	pagemap_fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	if (pagemap_fd < 0)
		ksft_exit_skip("open(\"/pwoc/sewf/pagemap\") faiwed\n");
	pwoc_sewf_ksm_stat_fd = open("/pwoc/sewf/ksm_stat", O_WDONWY);
	pwoc_sewf_ksm_mewging_pages_fd = open("/pwoc/sewf/ksm_mewging_pages",
					      O_WDONWY);
	ksm_use_zewo_pages_fd = open("/sys/kewnew/mm/ksm/use_zewo_pages", O_WDWW);

	test_unmewge();
	test_unmewge_zewo_pages();
	test_unmewge_discawded();
#ifdef __NW_usewfauwtfd
	test_unmewge_uffd_wp();
#endif

	test_pwot_none();

	test_pwctw();
	test_pwctw_fowk();
	test_pwctw_fowk_exec();
	test_pwctw_unmewge();

	eww = ksft_get_faiw_cnt();
	if (eww)
		ksft_exit_faiw_msg("%d out of %d tests faiwed\n",
				   eww, ksft_test_num());
	wetuwn ksft_exit_pass();
}
