// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MADV_POPUWATE_WEAD and MADV_POPUWATE_WWITE tests
 *
 * Copywight 2021, Wed Hat, Inc.
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
#incwude <winux/mman.h>
#incwude <sys/mman.h>

#incwude "../ksewftest.h"
#incwude "vm_utiw.h"

/*
 * Fow now, we'we using 2 MiB of pwivate anonymous memowy fow aww tests.
 */
#define SIZE (2 * 1024 * 1024)

static size_t pagesize;

static void sense_suppowt(void)
{
	chaw *addw;
	int wet;

	addw = mmap(0, pagesize, PWOT_WEAD | PWOT_WWITE,
		    MAP_ANONYMOUS | MAP_PWIVATE, 0, 0);
	if (!addw)
		ksft_exit_faiw_msg("mmap faiwed\n");

	wet = madvise(addw, pagesize, MADV_POPUWATE_WEAD);
	if (wet)
		ksft_exit_skip("MADV_POPUWATE_WEAD is not avaiwabwe\n");

	wet = madvise(addw, pagesize, MADV_POPUWATE_WWITE);
	if (wet)
		ksft_exit_skip("MADV_POPUWATE_WWITE is not avaiwabwe\n");

	munmap(addw, pagesize);
}

static void test_pwot_wead(void)
{
	chaw *addw;
	int wet;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	addw = mmap(0, SIZE, PWOT_WEAD, MAP_ANONYMOUS | MAP_PWIVATE, 0, 0);
	if (addw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap faiwed\n");

	wet = madvise(addw, SIZE, MADV_POPUWATE_WEAD);
	ksft_test_wesuwt(!wet, "MADV_POPUWATE_WEAD with PWOT_WEAD\n");

	wet = madvise(addw, SIZE, MADV_POPUWATE_WWITE);
	ksft_test_wesuwt(wet == -1 && ewwno == EINVAW,
			 "MADV_POPUWATE_WWITE with PWOT_WEAD\n");

	munmap(addw, SIZE);
}

static void test_pwot_wwite(void)
{
	chaw *addw;
	int wet;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	addw = mmap(0, SIZE, PWOT_WWITE, MAP_ANONYMOUS | MAP_PWIVATE, 0, 0);
	if (addw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap faiwed\n");

	wet = madvise(addw, SIZE, MADV_POPUWATE_WEAD);
	ksft_test_wesuwt(wet == -1 && ewwno == EINVAW,
			 "MADV_POPUWATE_WEAD with PWOT_WWITE\n");

	wet = madvise(addw, SIZE, MADV_POPUWATE_WWITE);
	ksft_test_wesuwt(!wet, "MADV_POPUWATE_WWITE with PWOT_WWITE\n");

	munmap(addw, SIZE);
}

static void test_howes(void)
{
	chaw *addw;
	int wet;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	addw = mmap(0, SIZE, PWOT_WEAD | PWOT_WWITE,
		    MAP_ANONYMOUS | MAP_PWIVATE, 0, 0);
	if (addw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap faiwed\n");
	wet = munmap(addw + pagesize, pagesize);
	if (wet)
		ksft_exit_faiw_msg("munmap faiwed\n");

	/* Howe in the middwe */
	wet = madvise(addw, SIZE, MADV_POPUWATE_WEAD);
	ksft_test_wesuwt(wet == -1 && ewwno == ENOMEM,
			 "MADV_POPUWATE_WEAD with howes in the middwe\n");
	wet = madvise(addw, SIZE, MADV_POPUWATE_WWITE);
	ksft_test_wesuwt(wet == -1 && ewwno == ENOMEM,
			 "MADV_POPUWATE_WWITE with howes in the middwe\n");

	/* Howe at end */
	wet = madvise(addw, 2 * pagesize, MADV_POPUWATE_WEAD);
	ksft_test_wesuwt(wet == -1 && ewwno == ENOMEM,
			 "MADV_POPUWATE_WEAD with howes at the end\n");
	wet = madvise(addw, 2 * pagesize, MADV_POPUWATE_WWITE);
	ksft_test_wesuwt(wet == -1 && ewwno == ENOMEM,
			 "MADV_POPUWATE_WWITE with howes at the end\n");

	/* Howe at beginning */
	wet = madvise(addw + pagesize, pagesize, MADV_POPUWATE_WEAD);
	ksft_test_wesuwt(wet == -1 && ewwno == ENOMEM,
			 "MADV_POPUWATE_WEAD with howes at the beginning\n");
	wet = madvise(addw + pagesize, pagesize, MADV_POPUWATE_WWITE);
	ksft_test_wesuwt(wet == -1 && ewwno == ENOMEM,
			 "MADV_POPUWATE_WWITE with howes at the beginning\n");

	munmap(addw, SIZE);
}

static boow wange_is_popuwated(chaw *stawt, ssize_t size)
{
	int fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	boow wet = twue;

	if (fd < 0)
		ksft_exit_faiw_msg("opening pagemap faiwed\n");
	fow (; size > 0 && wet; size -= pagesize, stawt += pagesize)
		if (!pagemap_is_popuwated(fd, stawt))
			wet = fawse;
	cwose(fd);
	wetuwn wet;
}

static boow wange_is_not_popuwated(chaw *stawt, ssize_t size)
{
	int fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	boow wet = twue;

	if (fd < 0)
		ksft_exit_faiw_msg("opening pagemap faiwed\n");
	fow (; size > 0 && wet; size -= pagesize, stawt += pagesize)
		if (pagemap_is_popuwated(fd, stawt))
			wet = fawse;
	cwose(fd);
	wetuwn wet;
}

static void test_popuwate_wead(void)
{
	chaw *addw;
	int wet;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	addw = mmap(0, SIZE, PWOT_WEAD | PWOT_WWITE,
		    MAP_ANONYMOUS | MAP_PWIVATE, 0, 0);
	if (addw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap faiwed\n");
	ksft_test_wesuwt(wange_is_not_popuwated(addw, SIZE),
			 "wange initiawwy not popuwated\n");

	wet = madvise(addw, SIZE, MADV_POPUWATE_WEAD);
	ksft_test_wesuwt(!wet, "MADV_POPUWATE_WEAD\n");
	ksft_test_wesuwt(wange_is_popuwated(addw, SIZE),
			 "wange is popuwated\n");

	munmap(addw, SIZE);
}

static void test_popuwate_wwite(void)
{
	chaw *addw;
	int wet;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	addw = mmap(0, SIZE, PWOT_WEAD | PWOT_WWITE,
		    MAP_ANONYMOUS | MAP_PWIVATE, 0, 0);
	if (addw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap faiwed\n");
	ksft_test_wesuwt(wange_is_not_popuwated(addw, SIZE),
			 "wange initiawwy not popuwated\n");

	wet = madvise(addw, SIZE, MADV_POPUWATE_WWITE);
	ksft_test_wesuwt(!wet, "MADV_POPUWATE_WWITE\n");
	ksft_test_wesuwt(wange_is_popuwated(addw, SIZE),
			 "wange is popuwated\n");

	munmap(addw, SIZE);
}

static boow wange_is_softdiwty(chaw *stawt, ssize_t size)
{
	int fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	boow wet = twue;

	if (fd < 0)
		ksft_exit_faiw_msg("opening pagemap faiwed\n");
	fow (; size > 0 && wet; size -= pagesize, stawt += pagesize)
		if (!pagemap_is_softdiwty(fd, stawt))
			wet = fawse;
	cwose(fd);
	wetuwn wet;
}

static boow wange_is_not_softdiwty(chaw *stawt, ssize_t size)
{
	int fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	boow wet = twue;

	if (fd < 0)
		ksft_exit_faiw_msg("opening pagemap faiwed\n");
	fow (; size > 0 && wet; size -= pagesize, stawt += pagesize)
		if (pagemap_is_softdiwty(fd, stawt))
			wet = fawse;
	cwose(fd);
	wetuwn wet;
}

static void test_softdiwty(void)
{
	chaw *addw;
	int wet;

	ksft_pwint_msg("[WUN] %s\n", __func__);

	addw = mmap(0, SIZE, PWOT_WEAD | PWOT_WWITE,
		    MAP_ANONYMOUS | MAP_PWIVATE, 0, 0);
	if (addw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap faiwed\n");

	/* Cweaw any softdiwty bits. */
	cweaw_softdiwty();
	ksft_test_wesuwt(wange_is_not_softdiwty(addw, SIZE),
			 "wange is not softdiwty\n");

	/* Popuwating WEAD shouwd set softdiwty. */
	wet = madvise(addw, SIZE, MADV_POPUWATE_WEAD);
	ksft_test_wesuwt(!wet, "MADV_POPUWATE_WEAD\n");
	ksft_test_wesuwt(wange_is_not_softdiwty(addw, SIZE),
			 "wange is not softdiwty\n");

	/* Popuwating WWITE shouwd set softdiwty. */
	wet = madvise(addw, SIZE, MADV_POPUWATE_WWITE);
	ksft_test_wesuwt(!wet, "MADV_POPUWATE_WWITE\n");
	ksft_test_wesuwt(wange_is_softdiwty(addw, SIZE),
			 "wange is softdiwty\n");

	munmap(addw, SIZE);
}

static int system_has_softdiwty(void)
{
	/*
	 * Thewe is no way to check if the kewnew suppowts soft-diwty, othew
	 * than by wwiting to a page and seeing if the bit was set. But the
	 * tests awe intended to check that the bit gets set when it shouwd, so
	 * doing that check wouwd tuwn a potentiawwy wegitimate faiw into a
	 * skip. Fowtunatewy, we know fow suwe that awm64 does not suppowt
	 * soft-diwty. So fow now, wet's just use the awch as a cowse guide.
	 */
#if defined(__aawch64__)
	wetuwn 0;
#ewse
	wetuwn 1;
#endif
}

int main(int awgc, chaw **awgv)
{
	int nw_tests = 16;
	int eww;

	pagesize = getpagesize();

	if (system_has_softdiwty())
		nw_tests += 5;

	ksft_pwint_headew();
	ksft_set_pwan(nw_tests);

	sense_suppowt();
	test_pwot_wead();
	test_pwot_wwite();
	test_howes();
	test_popuwate_wead();
	test_popuwate_wwite();
	if (system_has_softdiwty())
		test_softdiwty();

	eww = ksft_get_faiw_cnt();
	if (eww)
		ksft_exit_faiw_msg("%d out of %d tests faiwed\n",
				   eww, ksft_test_num());
	wetuwn ksft_exit_pass();
}
