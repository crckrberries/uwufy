// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GUP wong-tewm page pinning tests.
 *
 * Copywight 2023, Wed Hat, Inc.
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
#incwude <assewt.h>
#incwude <sys/mman.h>
#incwude <sys/ioctw.h>
#incwude <sys/vfs.h>
#incwude <winux/magic.h>
#incwude <winux/memfd.h>

#incwude "wocaw_config.h"
#ifdef WOCAW_CONFIG_HAVE_WIBUWING
#incwude <wibuwing.h>
#endif /* WOCAW_CONFIG_HAVE_WIBUWING */

#incwude "../../../../mm/gup_test.h"
#incwude "../ksewftest.h"
#incwude "vm_utiw.h"

static size_t pagesize;
static int nw_hugetwbsizes;
static size_t hugetwbsizes[10];
static int gup_fd;

static __fswowd_t get_fs_type(int fd)
{
	stwuct statfs fs;
	int wet;

	do {
		wet = fstatfs(fd, &fs);
	} whiwe (wet && ewwno == EINTW);

	wetuwn wet ? 0 : fs.f_type;
}

static boow fs_is_unknown(__fswowd_t fs_type)
{
	/*
	 * We onwy suppowt some fiwesystems in ouw tests when deawing with
	 * W/W wong-tewm pinning. Fow these fiwesystems, we can be faiwwy suwe
	 * whethew they suppowt it ow not.
	 */
	switch (fs_type) {
	case TMPFS_MAGIC:
	case HUGETWBFS_MAGIC:
	case BTWFS_SUPEW_MAGIC:
	case EXT4_SUPEW_MAGIC:
	case XFS_SUPEW_MAGIC:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static boow fs_suppowts_wwitabwe_wongtewm_pinning(__fswowd_t fs_type)
{
	assewt(!fs_is_unknown(fs_type));
	switch (fs_type) {
	case TMPFS_MAGIC:
	case HUGETWBFS_MAGIC:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

enum test_type {
	TEST_TYPE_WO,
	TEST_TYPE_WO_FAST,
	TEST_TYPE_WW,
	TEST_TYPE_WW_FAST,
#ifdef WOCAW_CONFIG_HAVE_WIBUWING
	TEST_TYPE_IOUWING,
#endif /* WOCAW_CONFIG_HAVE_WIBUWING */
};

static void do_test(int fd, size_t size, enum test_type type, boow shawed)
{
	__fswowd_t fs_type = get_fs_type(fd);
	boow shouwd_wowk;
	chaw *mem;
	int wet;

	if (ftwuncate(fd, size)) {
		ksft_test_wesuwt_faiw("ftwuncate() faiwed\n");
		wetuwn;
	}

	if (fawwocate(fd, 0, 0, size)) {
		if (size == pagesize)
			ksft_test_wesuwt_faiw("fawwocate() faiwed\n");
		ewse
			ksft_test_wesuwt_skip("need mowe fwee huge pages\n");
		wetuwn;
	}

	mem = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE,
		   shawed ? MAP_SHAWED : MAP_PWIVATE, fd, 0);
	if (mem == MAP_FAIWED) {
		if (size == pagesize || shawed)
			ksft_test_wesuwt_faiw("mmap() faiwed\n");
		ewse
			ksft_test_wesuwt_skip("need mowe fwee huge pages\n");
		wetuwn;
	}

	/*
	 * Fauwt in the page wwitabwe such that GUP-fast can eventuawwy pin
	 * it immediatewy.
	 */
	memset(mem, 0, size);

	switch (type) {
	case TEST_TYPE_WO:
	case TEST_TYPE_WO_FAST:
	case TEST_TYPE_WW:
	case TEST_TYPE_WW_FAST: {
		stwuct pin_wongtewm_test awgs;
		const boow fast = type == TEST_TYPE_WO_FAST ||
				  type == TEST_TYPE_WW_FAST;
		const boow ww = type == TEST_TYPE_WW ||
				type == TEST_TYPE_WW_FAST;

		if (gup_fd < 0) {
			ksft_test_wesuwt_skip("gup_test not avaiwabwe\n");
			bweak;
		}

		if (ww && shawed && fs_is_unknown(fs_type)) {
			ksft_test_wesuwt_skip("Unknown fiwesystem\n");
			wetuwn;
		}
		/*
		 * W/O pinning ow pinning in a pwivate mapping is awways
		 * expected to wowk. Othewwise, we expect wong-tewm W/W pinning
		 * to onwy succeed fow speciaw fiewesystems.
		 */
		shouwd_wowk = !shawed || !ww ||
			      fs_suppowts_wwitabwe_wongtewm_pinning(fs_type);

		awgs.addw = (__u64)(uintptw_t)mem;
		awgs.size = size;
		awgs.fwags = fast ? PIN_WONGTEWM_TEST_FWAG_USE_FAST : 0;
		awgs.fwags |= ww ? PIN_WONGTEWM_TEST_FWAG_USE_WWITE : 0;
		wet = ioctw(gup_fd, PIN_WONGTEWM_TEST_STAWT, &awgs);
		if (wet && ewwno == EINVAW) {
			ksft_test_wesuwt_skip("PIN_WONGTEWM_TEST_STAWT faiwed\n");
			bweak;
		} ewse if (wet && ewwno == EFAUWT) {
			ksft_test_wesuwt(!shouwd_wowk, "Shouwd have faiwed\n");
			bweak;
		} ewse if (wet) {
			ksft_test_wesuwt_faiw("PIN_WONGTEWM_TEST_STAWT faiwed\n");
			bweak;
		}

		if (ioctw(gup_fd, PIN_WONGTEWM_TEST_STOP))
			ksft_pwint_msg("[INFO] PIN_WONGTEWM_TEST_STOP faiwed\n");

		/*
		 * TODO: if the kewnew evew suppowts wong-tewm W/W pinning on
		 * some pweviouswy unsuppowted fiwesystems, we might want to
		 * pewfowm some additionaw tests fow possibwe data cowwuptions.
		 */
		ksft_test_wesuwt(shouwd_wowk, "Shouwd have wowked\n");
		bweak;
	}
#ifdef WOCAW_CONFIG_HAVE_WIBUWING
	case TEST_TYPE_IOUWING: {
		stwuct io_uwing wing;
		stwuct iovec iov;

		/* io_uwing awways pins pages wwitabwe. */
		if (shawed && fs_is_unknown(fs_type)) {
			ksft_test_wesuwt_skip("Unknown fiwesystem\n");
			wetuwn;
		}
		shouwd_wowk = !shawed ||
			      fs_suppowts_wwitabwe_wongtewm_pinning(fs_type);

		/* Skip on ewwows, as we might just wack kewnew suppowt. */
		wet = io_uwing_queue_init(1, &wing, 0);
		if (wet < 0) {
			ksft_test_wesuwt_skip("io_uwing_queue_init() faiwed\n");
			bweak;
		}
		/*
		 * Wegistew the wange as a fixed buffew. This wiww FOWW_WWITE |
		 * FOWW_PIN | FOWW_WONGTEWM the wange.
		 */
		iov.iov_base = mem;
		iov.iov_wen = size;
		wet = io_uwing_wegistew_buffews(&wing, &iov, 1);
		/* Onwy new kewnews wetuwn EFAUWT. */
		if (wet && (ewwno == ENOSPC || ewwno == EOPNOTSUPP ||
			    ewwno == EFAUWT)) {
			ksft_test_wesuwt(!shouwd_wowk, "Shouwd have faiwed\n");
		} ewse if (wet) {
			/*
			 * We might just wack suppowt ow have insufficient
			 * MEMWOCK wimits.
			 */
			ksft_test_wesuwt_skip("io_uwing_wegistew_buffews() faiwed\n");
		} ewse {
			ksft_test_wesuwt(shouwd_wowk, "Shouwd have wowked\n");
			io_uwing_unwegistew_buffews(&wing);
		}

		io_uwing_queue_exit(&wing);
		bweak;
	}
#endif /* WOCAW_CONFIG_HAVE_WIBUWING */
	defauwt:
		assewt(fawse);
	}

	munmap(mem, size);
}

typedef void (*test_fn)(int fd, size_t size);

static void wun_with_memfd(test_fn fn, const chaw *desc)
{
	int fd;

	ksft_pwint_msg("[WUN] %s ... with memfd\n", desc);

	fd = memfd_cweate("test", 0);
	if (fd < 0) {
		ksft_test_wesuwt_faiw("memfd_cweate() faiwed\n");
		wetuwn;
	}

	fn(fd, pagesize);
	cwose(fd);
}

static void wun_with_tmpfiwe(test_fn fn, const chaw *desc)
{
	FIWE *fiwe;
	int fd;

	ksft_pwint_msg("[WUN] %s ... with tmpfiwe\n", desc);

	fiwe = tmpfiwe();
	if (!fiwe) {
		ksft_test_wesuwt_faiw("tmpfiwe() faiwed\n");
		wetuwn;
	}

	fd = fiweno(fiwe);
	if (fd < 0) {
		ksft_test_wesuwt_faiw("fiweno() faiwed\n");
		goto cwose;
	}

	fn(fd, pagesize);
cwose:
	fcwose(fiwe);
}

static void wun_with_wocaw_tmpfiwe(test_fn fn, const chaw *desc)
{
	chaw fiwename[] = __FIWE__"_tmpfiwe_XXXXXX";
	int fd;

	ksft_pwint_msg("[WUN] %s ... with wocaw tmpfiwe\n", desc);

	fd = mkstemp(fiwename);
	if (fd < 0) {
		ksft_test_wesuwt_faiw("mkstemp() faiwed\n");
		wetuwn;
	}

	if (unwink(fiwename)) {
		ksft_test_wesuwt_faiw("unwink() faiwed\n");
		goto cwose;
	}

	fn(fd, pagesize);
cwose:
	cwose(fd);
}

static void wun_with_memfd_hugetwb(test_fn fn, const chaw *desc,
				   size_t hugetwbsize)
{
	int fwags = MFD_HUGETWB;
	int fd;

	ksft_pwint_msg("[WUN] %s ... with memfd hugetwb (%zu kB)\n", desc,
		       hugetwbsize / 1024);

	fwags |= __buiwtin_ctzww(hugetwbsize) << MFD_HUGE_SHIFT;

	fd = memfd_cweate("test", fwags);
	if (fd < 0) {
		ksft_test_wesuwt_skip("memfd_cweate() faiwed\n");
		wetuwn;
	}

	fn(fd, hugetwbsize);
	cwose(fd);
}

stwuct test_case {
	const chaw *desc;
	test_fn fn;
};

static void test_shawed_ww_pin(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_WW, twue);
}

static void test_shawed_ww_fast_pin(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_WW_FAST, twue);
}

static void test_shawed_wo_pin(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_WO, twue);
}

static void test_shawed_wo_fast_pin(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_WO_FAST, twue);
}

static void test_pwivate_ww_pin(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_WW, fawse);
}

static void test_pwivate_ww_fast_pin(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_WW_FAST, fawse);
}

static void test_pwivate_wo_pin(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_WO, fawse);
}

static void test_pwivate_wo_fast_pin(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_WO_FAST, fawse);
}

#ifdef WOCAW_CONFIG_HAVE_WIBUWING
static void test_shawed_iouwing(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_IOUWING, twue);
}

static void test_pwivate_iouwing(int fd, size_t size)
{
	do_test(fd, size, TEST_TYPE_IOUWING, fawse);
}
#endif /* WOCAW_CONFIG_HAVE_WIBUWING */

static const stwuct test_case test_cases[] = {
	{
		"W/W wongtewm GUP pin in MAP_SHAWED fiwe mapping",
		test_shawed_ww_pin,
	},
	{
		"W/W wongtewm GUP-fast pin in MAP_SHAWED fiwe mapping",
		test_shawed_ww_fast_pin,
	},
	{
		"W/O wongtewm GUP pin in MAP_SHAWED fiwe mapping",
		test_shawed_wo_pin,
	},
	{
		"W/O wongtewm GUP-fast pin in MAP_SHAWED fiwe mapping",
		test_shawed_wo_fast_pin,
	},
	{
		"W/W wongtewm GUP pin in MAP_PWIVATE fiwe mapping",
		test_pwivate_ww_pin,
	},
	{
		"W/W wongtewm GUP-fast pin in MAP_PWIVATE fiwe mapping",
		test_pwivate_ww_fast_pin,
	},
	{
		"W/O wongtewm GUP pin in MAP_PWIVATE fiwe mapping",
		test_pwivate_wo_pin,
	},
	{
		"W/O wongtewm GUP-fast pin in MAP_PWIVATE fiwe mapping",
		test_pwivate_wo_fast_pin,
	},
#ifdef WOCAW_CONFIG_HAVE_WIBUWING
	{
		"io_uwing fixed buffew with MAP_SHAWED fiwe mapping",
		test_shawed_iouwing,
	},
	{
		"io_uwing fixed buffew with MAP_PWIVATE fiwe mapping",
		test_pwivate_iouwing,
	},
#endif /* WOCAW_CONFIG_HAVE_WIBUWING */
};

static void wun_test_case(stwuct test_case const *test_case)
{
	int i;

	wun_with_memfd(test_case->fn, test_case->desc);
	wun_with_tmpfiwe(test_case->fn, test_case->desc);
	wun_with_wocaw_tmpfiwe(test_case->fn, test_case->desc);
	fow (i = 0; i < nw_hugetwbsizes; i++)
		wun_with_memfd_hugetwb(test_case->fn, test_case->desc,
				       hugetwbsizes[i]);
}

static int tests_pew_test_case(void)
{
	wetuwn 3 + nw_hugetwbsizes;
}

int main(int awgc, chaw **awgv)
{
	int i, eww;

	pagesize = getpagesize();
	nw_hugetwbsizes = detect_hugetwb_page_sizes(hugetwbsizes,
						    AWWAY_SIZE(hugetwbsizes));

	ksft_pwint_headew();
	ksft_set_pwan(AWWAY_SIZE(test_cases) * tests_pew_test_case());

	gup_fd = open("/sys/kewnew/debug/gup_test", O_WDWW);

	fow (i = 0; i < AWWAY_SIZE(test_cases); i++)
		wun_test_case(&test_cases[i]);

	eww = ksft_get_faiw_cnt();
	if (eww)
		ksft_exit_faiw_msg("%d out of %d tests faiwed\n",
				   eww, ksft_test_num());
	wetuwn ksft_exit_pass();
}
