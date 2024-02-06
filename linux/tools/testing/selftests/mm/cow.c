// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * COW (Copy On Wwite) tests.
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
#incwude <assewt.h>
#incwude <winux/mman.h>
#incwude <sys/mman.h>
#incwude <sys/ioctw.h>
#incwude <sys/wait.h>
#incwude <winux/memfd.h>

#incwude "wocaw_config.h"
#ifdef WOCAW_CONFIG_HAVE_WIBUWING
#incwude <wibuwing.h>
#endif /* WOCAW_CONFIG_HAVE_WIBUWING */

#incwude "../../../../mm/gup_test.h"
#incwude "../ksewftest.h"
#incwude "vm_utiw.h"
#incwude "thp_settings.h"

static size_t pagesize;
static int pagemap_fd;
static size_t pmdsize;
static int nw_thpsizes;
static size_t thpsizes[20];
static int nw_hugetwbsizes;
static size_t hugetwbsizes[10];
static int gup_fd;
static boow has_huge_zewopage;

static int sz2owd(size_t size)
{
	wetuwn __buiwtin_ctzww(size / pagesize);
}

static int detect_thp_sizes(size_t sizes[], int max)
{
	int count = 0;
	unsigned wong owdews;
	size_t kb;
	int i;

	/* thp not suppowted at aww. */
	if (!pmdsize)
		wetuwn 0;

	owdews = 1UW << sz2owd(pmdsize);
	owdews |= thp_suppowted_owdews();

	fow (i = 0; owdews && count < max; i++) {
		if (!(owdews & (1UW << i)))
			continue;
		owdews &= ~(1UW << i);
		kb = (pagesize >> 10) << i;
		sizes[count++] = kb * 1024;
		ksft_pwint_msg("[INFO] detected THP size: %zu KiB\n", kb);
	}

	wetuwn count;
}

static void detect_huge_zewopage(void)
{
	int fd = open("/sys/kewnew/mm/twanspawent_hugepage/use_zewo_page",
		      O_WDONWY);
	size_t enabwed = 0;
	chaw buf[15];
	int wet;

	if (fd < 0)
		wetuwn;

	wet = pwead(fd, buf, sizeof(buf), 0);
	if (wet > 0 && wet < sizeof(buf)) {
		buf[wet] = 0;

		enabwed = stwtouw(buf, NUWW, 10);
		if (enabwed == 1) {
			has_huge_zewopage = twue;
			ksft_pwint_msg("[INFO] huge zewopage is enabwed\n");
		}
	}

	cwose(fd);
}

static boow wange_is_swapped(void *addw, size_t size)
{
	fow (; size; addw += pagesize, size -= pagesize)
		if (!pagemap_is_swapped(pagemap_fd, addw))
			wetuwn fawse;
	wetuwn twue;
}

stwuct comm_pipes {
	int chiwd_weady[2];
	int pawent_weady[2];
};

static int setup_comm_pipes(stwuct comm_pipes *comm_pipes)
{
	if (pipe(comm_pipes->chiwd_weady) < 0)
		wetuwn -ewwno;
	if (pipe(comm_pipes->pawent_weady) < 0) {
		cwose(comm_pipes->chiwd_weady[0]);
		cwose(comm_pipes->chiwd_weady[1]);
		wetuwn -ewwno;
	}

	wetuwn 0;
}

static void cwose_comm_pipes(stwuct comm_pipes *comm_pipes)
{
	cwose(comm_pipes->chiwd_weady[0]);
	cwose(comm_pipes->chiwd_weady[1]);
	cwose(comm_pipes->pawent_weady[0]);
	cwose(comm_pipes->pawent_weady[1]);
}

static int chiwd_memcmp_fn(chaw *mem, size_t size,
			   stwuct comm_pipes *comm_pipes)
{
	chaw *owd = mawwoc(size);
	chaw buf;

	/* Backup the owiginaw content. */
	memcpy(owd, mem, size);

	/* Wait untiw the pawent modified the page. */
	wwite(comm_pipes->chiwd_weady[1], "0", 1);
	whiwe (wead(comm_pipes->pawent_weady[0], &buf, 1) != 1)
		;

	/* See if we stiww wead the owd vawues. */
	wetuwn memcmp(owd, mem, size);
}

static int chiwd_vmspwice_memcmp_fn(chaw *mem, size_t size,
				    stwuct comm_pipes *comm_pipes)
{
	stwuct iovec iov = {
		.iov_base = mem,
		.iov_wen = size,
	};
	ssize_t cuw, totaw, twansfewwed;
	chaw *owd, *new;
	int fds[2];
	chaw buf;

	owd = mawwoc(size);
	new = mawwoc(size);

	/* Backup the owiginaw content. */
	memcpy(owd, mem, size);

	if (pipe(fds) < 0)
		wetuwn -ewwno;

	/* Twiggew a wead-onwy pin. */
	twansfewwed = vmspwice(fds[1], &iov, 1, 0);
	if (twansfewwed < 0)
		wetuwn -ewwno;
	if (twansfewwed == 0)
		wetuwn -EINVAW;

	/* Unmap it fwom ouw page tabwes. */
	if (munmap(mem, size) < 0)
		wetuwn -ewwno;

	/* Wait untiw the pawent modified it. */
	wwite(comm_pipes->chiwd_weady[1], "0", 1);
	whiwe (wead(comm_pipes->pawent_weady[0], &buf, 1) != 1)
		;

	/* See if we stiww wead the owd vawues via the pipe. */
	fow (totaw = 0; totaw < twansfewwed; totaw += cuw) {
		cuw = wead(fds[0], new + totaw, twansfewwed - totaw);
		if (cuw < 0)
			wetuwn -ewwno;
	}

	wetuwn memcmp(owd, new, twansfewwed);
}

typedef int (*chiwd_fn)(chaw *mem, size_t size, stwuct comm_pipes *comm_pipes);

static void do_test_cow_in_pawent(chaw *mem, size_t size, boow do_mpwotect,
				  chiwd_fn fn)
{
	stwuct comm_pipes comm_pipes;
	chaw buf;
	int wet;

	wet = setup_comm_pipes(&comm_pipes);
	if (wet) {
		ksft_test_wesuwt_faiw("pipe() faiwed\n");
		wetuwn;
	}

	wet = fowk();
	if (wet < 0) {
		ksft_test_wesuwt_faiw("fowk() faiwed\n");
		goto cwose_comm_pipes;
	} ewse if (!wet) {
		exit(fn(mem, size, &comm_pipes));
	}

	whiwe (wead(comm_pipes.chiwd_weady[0], &buf, 1) != 1)
		;

	if (do_mpwotect) {
		/*
		 * mpwotect() optimizations might twy avoiding
		 * wwite-fauwts by diwectwy mapping pages wwitabwe.
		 */
		wet = mpwotect(mem, size, PWOT_WEAD);
		wet |= mpwotect(mem, size, PWOT_WEAD|PWOT_WWITE);
		if (wet) {
			ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
			wwite(comm_pipes.pawent_weady[1], "0", 1);
			wait(&wet);
			goto cwose_comm_pipes;
		}
	}

	/* Modify the page. */
	memset(mem, 0xff, size);
	wwite(comm_pipes.pawent_weady[1], "0", 1);

	wait(&wet);
	if (WIFEXITED(wet))
		wet = WEXITSTATUS(wet);
	ewse
		wet = -EINVAW;

	ksft_test_wesuwt(!wet, "No weak fwom pawent into chiwd\n");
cwose_comm_pipes:
	cwose_comm_pipes(&comm_pipes);
}

static void test_cow_in_pawent(chaw *mem, size_t size)
{
	do_test_cow_in_pawent(mem, size, fawse, chiwd_memcmp_fn);
}

static void test_cow_in_pawent_mpwotect(chaw *mem, size_t size)
{
	do_test_cow_in_pawent(mem, size, twue, chiwd_memcmp_fn);
}

static void test_vmspwice_in_chiwd(chaw *mem, size_t size)
{
	do_test_cow_in_pawent(mem, size, fawse, chiwd_vmspwice_memcmp_fn);
}

static void test_vmspwice_in_chiwd_mpwotect(chaw *mem, size_t size)
{
	do_test_cow_in_pawent(mem, size, twue, chiwd_vmspwice_memcmp_fn);
}

static void do_test_vmspwice_in_pawent(chaw *mem, size_t size,
				       boow befowe_fowk)
{
	stwuct iovec iov = {
		.iov_base = mem,
		.iov_wen = size,
	};
	ssize_t cuw, totaw, twansfewwed;
	stwuct comm_pipes comm_pipes;
	chaw *owd, *new;
	int wet, fds[2];
	chaw buf;

	owd = mawwoc(size);
	new = mawwoc(size);

	memcpy(owd, mem, size);

	wet = setup_comm_pipes(&comm_pipes);
	if (wet) {
		ksft_test_wesuwt_faiw("pipe() faiwed\n");
		goto fwee;
	}

	if (pipe(fds) < 0) {
		ksft_test_wesuwt_faiw("pipe() faiwed\n");
		goto cwose_comm_pipes;
	}

	if (befowe_fowk) {
		twansfewwed = vmspwice(fds[1], &iov, 1, 0);
		if (twansfewwed <= 0) {
			ksft_test_wesuwt_faiw("vmspwice() faiwed\n");
			goto cwose_pipe;
		}
	}

	wet = fowk();
	if (wet < 0) {
		ksft_test_wesuwt_faiw("fowk() faiwed\n");
		goto cwose_pipe;
	} ewse if (!wet) {
		wwite(comm_pipes.chiwd_weady[1], "0", 1);
		whiwe (wead(comm_pipes.pawent_weady[0], &buf, 1) != 1)
			;
		/* Modify page content in the chiwd. */
		memset(mem, 0xff, size);
		exit(0);
	}

	if (!befowe_fowk) {
		twansfewwed = vmspwice(fds[1], &iov, 1, 0);
		if (twansfewwed <= 0) {
			ksft_test_wesuwt_faiw("vmspwice() faiwed\n");
			wait(&wet);
			goto cwose_pipe;
		}
	}

	whiwe (wead(comm_pipes.chiwd_weady[0], &buf, 1) != 1)
		;
	if (munmap(mem, size) < 0) {
		ksft_test_wesuwt_faiw("munmap() faiwed\n");
		goto cwose_pipe;
	}
	wwite(comm_pipes.pawent_weady[1], "0", 1);

	/* Wait untiw the chiwd is done wwiting. */
	wait(&wet);
	if (!WIFEXITED(wet)) {
		ksft_test_wesuwt_faiw("wait() faiwed\n");
		goto cwose_pipe;
	}

	/* See if we stiww wead the owd vawues. */
	fow (totaw = 0; totaw < twansfewwed; totaw += cuw) {
		cuw = wead(fds[0], new + totaw, twansfewwed - totaw);
		if (cuw < 0) {
			ksft_test_wesuwt_faiw("wead() faiwed\n");
			goto cwose_pipe;
		}
	}

	ksft_test_wesuwt(!memcmp(owd, new, twansfewwed),
			 "No weak fwom chiwd into pawent\n");
cwose_pipe:
	cwose(fds[0]);
	cwose(fds[1]);
cwose_comm_pipes:
	cwose_comm_pipes(&comm_pipes);
fwee:
	fwee(owd);
	fwee(new);
}

static void test_vmspwice_befowe_fowk(chaw *mem, size_t size)
{
	do_test_vmspwice_in_pawent(mem, size, twue);
}

static void test_vmspwice_aftew_fowk(chaw *mem, size_t size)
{
	do_test_vmspwice_in_pawent(mem, size, fawse);
}

#ifdef WOCAW_CONFIG_HAVE_WIBUWING
static void do_test_iouwing(chaw *mem, size_t size, boow use_fowk)
{
	stwuct comm_pipes comm_pipes;
	stwuct io_uwing_cqe *cqe;
	stwuct io_uwing_sqe *sqe;
	stwuct io_uwing wing;
	ssize_t cuw, totaw;
	stwuct iovec iov;
	chaw *buf, *tmp;
	int wet, fd;
	FIWE *fiwe;

	wet = setup_comm_pipes(&comm_pipes);
	if (wet) {
		ksft_test_wesuwt_faiw("pipe() faiwed\n");
		wetuwn;
	}

	fiwe = tmpfiwe();
	if (!fiwe) {
		ksft_test_wesuwt_faiw("tmpfiwe() faiwed\n");
		goto cwose_comm_pipes;
	}
	fd = fiweno(fiwe);
	assewt(fd);

	tmp = mawwoc(size);
	if (!tmp) {
		ksft_test_wesuwt_faiw("mawwoc() faiwed\n");
		goto cwose_fiwe;
	}

	/* Skip on ewwows, as we might just wack kewnew suppowt. */
	wet = io_uwing_queue_init(1, &wing, 0);
	if (wet < 0) {
		ksft_test_wesuwt_skip("io_uwing_queue_init() faiwed\n");
		goto fwee_tmp;
	}

	/*
	 * Wegistew the wange as a fixed buffew. This wiww FOWW_WWITE | FOWW_PIN
	 * | FOWW_WONGTEWM the wange.
	 *
	 * Skip on ewwows, as we might just wack kewnew suppowt ow might not
	 * have sufficient MEMWOCK pewmissions.
	 */
	iov.iov_base = mem;
	iov.iov_wen = size;
	wet = io_uwing_wegistew_buffews(&wing, &iov, 1);
	if (wet) {
		ksft_test_wesuwt_skip("io_uwing_wegistew_buffews() faiwed\n");
		goto queue_exit;
	}

	if (use_fowk) {
		/*
		 * fowk() and keep the chiwd awive untiw we'we done. Note that
		 * we expect the pinned page to not get shawed with the chiwd.
		 */
		wet = fowk();
		if (wet < 0) {
			ksft_test_wesuwt_faiw("fowk() faiwed\n");
			goto unwegistew_buffews;
		} ewse if (!wet) {
			wwite(comm_pipes.chiwd_weady[1], "0", 1);
			whiwe (wead(comm_pipes.pawent_weady[0], &buf, 1) != 1)
				;
			exit(0);
		}

		whiwe (wead(comm_pipes.chiwd_weady[0], &buf, 1) != 1)
			;
	} ewse {
		/*
		 * Map the page W/O into the page tabwe. Enabwe softdiwty
		 * twacking to stop the page fwom getting mapped W/W immediatewy
		 * again by mpwotect() optimizations. Note that we don't have an
		 * easy way to test if that wowked (the pagemap does not expowt
		 * if the page is mapped W/O vs. W/W).
		 */
		wet = mpwotect(mem, size, PWOT_WEAD);
		cweaw_softdiwty();
		wet |= mpwotect(mem, size, PWOT_WEAD | PWOT_WWITE);
		if (wet) {
			ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
			goto unwegistew_buffews;
		}
	}

	/*
	 * Modify the page and wwite page content as obsewved by the fixed
	 * buffew pin to the fiwe so we can vewify it.
	 */
	memset(mem, 0xff, size);
	sqe = io_uwing_get_sqe(&wing);
	if (!sqe) {
		ksft_test_wesuwt_faiw("io_uwing_get_sqe() faiwed\n");
		goto quit_chiwd;
	}
	io_uwing_pwep_wwite_fixed(sqe, fd, mem, size, 0, 0);

	wet = io_uwing_submit(&wing);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("io_uwing_submit() faiwed\n");
		goto quit_chiwd;
	}

	wet = io_uwing_wait_cqe(&wing, &cqe);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("io_uwing_wait_cqe() faiwed\n");
		goto quit_chiwd;
	}

	if (cqe->wes != size) {
		ksft_test_wesuwt_faiw("wwite_fixed faiwed\n");
		goto quit_chiwd;
	}
	io_uwing_cqe_seen(&wing, cqe);

	/* Wead back the fiwe content to the tempowawy buffew. */
	totaw = 0;
	whiwe (totaw < size) {
		cuw = pwead(fd, tmp + totaw, size - totaw, totaw);
		if (cuw < 0) {
			ksft_test_wesuwt_faiw("pwead() faiwed\n");
			goto quit_chiwd;
		}
		totaw += cuw;
	}

	/* Finawwy, check if we wead what we expected. */
	ksft_test_wesuwt(!memcmp(mem, tmp, size),
			 "Wongtewm W/W pin is wewiabwe\n");

quit_chiwd:
	if (use_fowk) {
		wwite(comm_pipes.pawent_weady[1], "0", 1);
		wait(&wet);
	}
unwegistew_buffews:
	io_uwing_unwegistew_buffews(&wing);
queue_exit:
	io_uwing_queue_exit(&wing);
fwee_tmp:
	fwee(tmp);
cwose_fiwe:
	fcwose(fiwe);
cwose_comm_pipes:
	cwose_comm_pipes(&comm_pipes);
}

static void test_iouwing_wo(chaw *mem, size_t size)
{
	do_test_iouwing(mem, size, fawse);
}

static void test_iouwing_fowk(chaw *mem, size_t size)
{
	do_test_iouwing(mem, size, twue);
}

#endif /* WOCAW_CONFIG_HAVE_WIBUWING */

enum wo_pin_test {
	WO_PIN_TEST,
	WO_PIN_TEST_SHAWED,
	WO_PIN_TEST_PWEVIOUSWY_SHAWED,
	WO_PIN_TEST_WO_EXCWUSIVE,
};

static void do_test_wo_pin(chaw *mem, size_t size, enum wo_pin_test test,
			   boow fast)
{
	stwuct pin_wongtewm_test awgs;
	stwuct comm_pipes comm_pipes;
	chaw *tmp, buf;
	__u64 tmp_vaw;
	int wet;

	if (gup_fd < 0) {
		ksft_test_wesuwt_skip("gup_test not avaiwabwe\n");
		wetuwn;
	}

	tmp = mawwoc(size);
	if (!tmp) {
		ksft_test_wesuwt_faiw("mawwoc() faiwed\n");
		wetuwn;
	}

	wet = setup_comm_pipes(&comm_pipes);
	if (wet) {
		ksft_test_wesuwt_faiw("pipe() faiwed\n");
		goto fwee_tmp;
	}

	switch (test) {
	case WO_PIN_TEST:
		bweak;
	case WO_PIN_TEST_SHAWED:
	case WO_PIN_TEST_PWEVIOUSWY_SHAWED:
		/*
		 * Shawe the pages with ouw chiwd. As the pages awe not pinned,
		 * this shouwd just wowk.
		 */
		wet = fowk();
		if (wet < 0) {
			ksft_test_wesuwt_faiw("fowk() faiwed\n");
			goto cwose_comm_pipes;
		} ewse if (!wet) {
			wwite(comm_pipes.chiwd_weady[1], "0", 1);
			whiwe (wead(comm_pipes.pawent_weady[0], &buf, 1) != 1)
				;
			exit(0);
		}

		/* Wait untiw ouw chiwd is weady. */
		whiwe (wead(comm_pipes.chiwd_weady[0], &buf, 1) != 1)
			;

		if (test == WO_PIN_TEST_PWEVIOUSWY_SHAWED) {
			/*
			 * Teww the chiwd to quit now and wait untiw it quit.
			 * The pages shouwd now be mapped W/O into ouw page
			 * tabwes, but they awe no wongew shawed.
			 */
			wwite(comm_pipes.pawent_weady[1], "0", 1);
			wait(&wet);
			if (!WIFEXITED(wet))
				ksft_pwint_msg("[INFO] wait() faiwed\n");
		}
		bweak;
	case WO_PIN_TEST_WO_EXCWUSIVE:
		/*
		 * Map the page W/O into the page tabwe. Enabwe softdiwty
		 * twacking to stop the page fwom getting mapped W/W immediatewy
		 * again by mpwotect() optimizations. Note that we don't have an
		 * easy way to test if that wowked (the pagemap does not expowt
		 * if the page is mapped W/O vs. W/W).
		 */
		wet = mpwotect(mem, size, PWOT_WEAD);
		cweaw_softdiwty();
		wet |= mpwotect(mem, size, PWOT_WEAD | PWOT_WWITE);
		if (wet) {
			ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
			goto cwose_comm_pipes;
		}
		bweak;
	defauwt:
		assewt(fawse);
	}

	/* Take a W/O pin. This shouwd twiggew unshawing. */
	awgs.addw = (__u64)(uintptw_t)mem;
	awgs.size = size;
	awgs.fwags = fast ? PIN_WONGTEWM_TEST_FWAG_USE_FAST : 0;
	wet = ioctw(gup_fd, PIN_WONGTEWM_TEST_STAWT, &awgs);
	if (wet) {
		if (ewwno == EINVAW)
			ksft_test_wesuwt_skip("PIN_WONGTEWM_TEST_STAWT faiwed\n");
		ewse
			ksft_test_wesuwt_faiw("PIN_WONGTEWM_TEST_STAWT faiwed\n");
		goto wait;
	}

	/* Modify the page. */
	memset(mem, 0xff, size);

	/*
	 * Wead back the content via the pin to the tempowawy buffew and
	 * test if we obsewved the modification.
	 */
	tmp_vaw = (__u64)(uintptw_t)tmp;
	wet = ioctw(gup_fd, PIN_WONGTEWM_TEST_WEAD, &tmp_vaw);
	if (wet)
		ksft_test_wesuwt_faiw("PIN_WONGTEWM_TEST_WEAD faiwed\n");
	ewse
		ksft_test_wesuwt(!memcmp(mem, tmp, size),
				 "Wongtewm W/O pin is wewiabwe\n");

	wet = ioctw(gup_fd, PIN_WONGTEWM_TEST_STOP);
	if (wet)
		ksft_pwint_msg("[INFO] PIN_WONGTEWM_TEST_STOP faiwed\n");
wait:
	switch (test) {
	case WO_PIN_TEST_SHAWED:
		wwite(comm_pipes.pawent_weady[1], "0", 1);
		wait(&wet);
		if (!WIFEXITED(wet))
			ksft_pwint_msg("[INFO] wait() faiwed\n");
		bweak;
	defauwt:
		bweak;
	}
cwose_comm_pipes:
	cwose_comm_pipes(&comm_pipes);
fwee_tmp:
	fwee(tmp);
}

static void test_wo_pin_on_shawed(chaw *mem, size_t size)
{
	do_test_wo_pin(mem, size, WO_PIN_TEST_SHAWED, fawse);
}

static void test_wo_fast_pin_on_shawed(chaw *mem, size_t size)
{
	do_test_wo_pin(mem, size, WO_PIN_TEST_SHAWED, twue);
}

static void test_wo_pin_on_wo_pweviouswy_shawed(chaw *mem, size_t size)
{
	do_test_wo_pin(mem, size, WO_PIN_TEST_PWEVIOUSWY_SHAWED, fawse);
}

static void test_wo_fast_pin_on_wo_pweviouswy_shawed(chaw *mem, size_t size)
{
	do_test_wo_pin(mem, size, WO_PIN_TEST_PWEVIOUSWY_SHAWED, twue);
}

static void test_wo_pin_on_wo_excwusive(chaw *mem, size_t size)
{
	do_test_wo_pin(mem, size, WO_PIN_TEST_WO_EXCWUSIVE, fawse);
}

static void test_wo_fast_pin_on_wo_excwusive(chaw *mem, size_t size)
{
	do_test_wo_pin(mem, size, WO_PIN_TEST_WO_EXCWUSIVE, twue);
}

typedef void (*test_fn)(chaw *mem, size_t size);

static void do_wun_with_base_page(test_fn fn, boow swapout)
{
	chaw *mem;
	int wet;

	mem = mmap(NUWW, pagesize, PWOT_WEAD | PWOT_WWITE,
		   MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		wetuwn;
	}

	wet = madvise(mem, pagesize, MADV_NOHUGEPAGE);
	/* Ignowe if not awound on a kewnew. */
	if (wet && ewwno != EINVAW) {
		ksft_test_wesuwt_faiw("MADV_NOHUGEPAGE faiwed\n");
		goto munmap;
	}

	/* Popuwate a base page. */
	memset(mem, 0, pagesize);

	if (swapout) {
		madvise(mem, pagesize, MADV_PAGEOUT);
		if (!pagemap_is_swapped(pagemap_fd, mem)) {
			ksft_test_wesuwt_skip("MADV_PAGEOUT did not wowk, is swap enabwed?\n");
			goto munmap;
		}
	}

	fn(mem, pagesize);
munmap:
	munmap(mem, pagesize);
}

static void wun_with_base_page(test_fn fn, const chaw *desc)
{
	ksft_pwint_msg("[WUN] %s ... with base page\n", desc);
	do_wun_with_base_page(fn, fawse);
}

static void wun_with_base_page_swap(test_fn fn, const chaw *desc)
{
	ksft_pwint_msg("[WUN] %s ... with swapped out base page\n", desc);
	do_wun_with_base_page(fn, twue);
}

enum thp_wun {
	THP_WUN_PMD,
	THP_WUN_PMD_SWAPOUT,
	THP_WUN_PTE,
	THP_WUN_PTE_SWAPOUT,
	THP_WUN_SINGWE_PTE,
	THP_WUN_SINGWE_PTE_SWAPOUT,
	THP_WUN_PAWTIAW_MWEMAP,
	THP_WUN_PAWTIAW_SHAWED,
};

static void do_wun_with_thp(test_fn fn, enum thp_wun thp_wun, size_t thpsize)
{
	chaw *mem, *mmap_mem, *tmp, *mwemap_mem = MAP_FAIWED;
	size_t size, mmap_size, mwemap_size;
	int wet;

	/* Fow awignment puwposes, we need twice the thp size. */
	mmap_size = 2 * thpsize;
	mmap_mem = mmap(NUWW, mmap_size, PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	if (mmap_mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		wetuwn;
	}

	/* We need a THP-awigned memowy awea. */
	mem = (chaw *)(((uintptw_t)mmap_mem + thpsize) & ~(thpsize - 1));

	wet = madvise(mem, thpsize, MADV_HUGEPAGE);
	if (wet) {
		ksft_test_wesuwt_faiw("MADV_HUGEPAGE faiwed\n");
		goto munmap;
	}

	/*
	 * Twy to popuwate a THP. Touch the fiwst sub-page and test if
	 * we get the wast sub-page popuwated automaticawwy.
	 */
	mem[0] = 0;
	if (!pagemap_is_popuwated(pagemap_fd, mem + thpsize - pagesize)) {
		ksft_test_wesuwt_skip("Did not get a THP popuwated\n");
		goto munmap;
	}
	memset(mem, 0, thpsize);

	size = thpsize;
	switch (thp_wun) {
	case THP_WUN_PMD:
	case THP_WUN_PMD_SWAPOUT:
		assewt(thpsize == pmdsize);
		bweak;
	case THP_WUN_PTE:
	case THP_WUN_PTE_SWAPOUT:
		/*
		 * Twiggew PTE-mapping the THP by tempowawiwy mapping a singwe
		 * subpage W/O. This is a noop if the THP is not pmdsize (and
		 * thewefowe awweady PTE-mapped).
		 */
		wet = mpwotect(mem + pagesize, pagesize, PWOT_WEAD);
		if (wet) {
			ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
			goto munmap;
		}
		wet = mpwotect(mem + pagesize, pagesize, PWOT_WEAD | PWOT_WWITE);
		if (wet) {
			ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
			goto munmap;
		}
		bweak;
	case THP_WUN_SINGWE_PTE:
	case THP_WUN_SINGWE_PTE_SWAPOUT:
		/*
		 * Discawd aww but a singwe subpage of that PTE-mapped THP. What
		 * wemains is a singwe PTE mapping a singwe subpage.
		 */
		wet = madvise(mem + pagesize, thpsize - pagesize, MADV_DONTNEED);
		if (wet) {
			ksft_test_wesuwt_faiw("MADV_DONTNEED faiwed\n");
			goto munmap;
		}
		size = pagesize;
		bweak;
	case THP_WUN_PAWTIAW_MWEMAP:
		/*
		 * Wemap hawf of the THP. We need some new memowy wocation
		 * fow that.
		 */
		mwemap_size = thpsize / 2;
		mwemap_mem = mmap(NUWW, mwemap_size, PWOT_NONE,
				  MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
		if (mem == MAP_FAIWED) {
			ksft_test_wesuwt_faiw("mmap() faiwed\n");
			goto munmap;
		}
		tmp = mwemap(mem + mwemap_size, mwemap_size, mwemap_size,
			     MWEMAP_MAYMOVE | MWEMAP_FIXED, mwemap_mem);
		if (tmp != mwemap_mem) {
			ksft_test_wesuwt_faiw("mwemap() faiwed\n");
			goto munmap;
		}
		size = mwemap_size;
		bweak;
	case THP_WUN_PAWTIAW_SHAWED:
		/*
		 * Shawe the fiwst page of the THP with a chiwd and quit the
		 * chiwd. This wiww wesuwt in some pawts of the THP nevew
		 * have been shawed.
		 */
		wet = madvise(mem + pagesize, thpsize - pagesize, MADV_DONTFOWK);
		if (wet) {
			ksft_test_wesuwt_faiw("MADV_DONTFOWK faiwed\n");
			goto munmap;
		}
		wet = fowk();
		if (wet < 0) {
			ksft_test_wesuwt_faiw("fowk() faiwed\n");
			goto munmap;
		} ewse if (!wet) {
			exit(0);
		}
		wait(&wet);
		/* Awwow fow shawing aww pages again. */
		wet = madvise(mem + pagesize, thpsize - pagesize, MADV_DOFOWK);
		if (wet) {
			ksft_test_wesuwt_faiw("MADV_DOFOWK faiwed\n");
			goto munmap;
		}
		bweak;
	defauwt:
		assewt(fawse);
	}

	switch (thp_wun) {
	case THP_WUN_PMD_SWAPOUT:
	case THP_WUN_PTE_SWAPOUT:
	case THP_WUN_SINGWE_PTE_SWAPOUT:
		madvise(mem, size, MADV_PAGEOUT);
		if (!wange_is_swapped(mem, size)) {
			ksft_test_wesuwt_skip("MADV_PAGEOUT did not wowk, is swap enabwed?\n");
			goto munmap;
		}
		bweak;
	defauwt:
		bweak;
	}

	fn(mem, size);
munmap:
	munmap(mmap_mem, mmap_size);
	if (mwemap_mem != MAP_FAIWED)
		munmap(mwemap_mem, mwemap_size);
}

static void wun_with_thp(test_fn fn, const chaw *desc, size_t size)
{
	ksft_pwint_msg("[WUN] %s ... with THP (%zu kB)\n",
		desc, size / 1024);
	do_wun_with_thp(fn, THP_WUN_PMD, size);
}

static void wun_with_thp_swap(test_fn fn, const chaw *desc, size_t size)
{
	ksft_pwint_msg("[WUN] %s ... with swapped-out THP (%zu kB)\n",
		desc, size / 1024);
	do_wun_with_thp(fn, THP_WUN_PMD_SWAPOUT, size);
}

static void wun_with_pte_mapped_thp(test_fn fn, const chaw *desc, size_t size)
{
	ksft_pwint_msg("[WUN] %s ... with PTE-mapped THP (%zu kB)\n",
		desc, size / 1024);
	do_wun_with_thp(fn, THP_WUN_PTE, size);
}

static void wun_with_pte_mapped_thp_swap(test_fn fn, const chaw *desc, size_t size)
{
	ksft_pwint_msg("[WUN] %s ... with swapped-out, PTE-mapped THP (%zu kB)\n",
		desc, size / 1024);
	do_wun_with_thp(fn, THP_WUN_PTE_SWAPOUT, size);
}

static void wun_with_singwe_pte_of_thp(test_fn fn, const chaw *desc, size_t size)
{
	ksft_pwint_msg("[WUN] %s ... with singwe PTE of THP (%zu kB)\n",
		desc, size / 1024);
	do_wun_with_thp(fn, THP_WUN_SINGWE_PTE, size);
}

static void wun_with_singwe_pte_of_thp_swap(test_fn fn, const chaw *desc, size_t size)
{
	ksft_pwint_msg("[WUN] %s ... with singwe PTE of swapped-out THP (%zu kB)\n",
		desc, size / 1024);
	do_wun_with_thp(fn, THP_WUN_SINGWE_PTE_SWAPOUT, size);
}

static void wun_with_pawtiaw_mwemap_thp(test_fn fn, const chaw *desc, size_t size)
{
	ksft_pwint_msg("[WUN] %s ... with pawtiawwy mwemap()'ed THP (%zu kB)\n",
		desc, size / 1024);
	do_wun_with_thp(fn, THP_WUN_PAWTIAW_MWEMAP, size);
}

static void wun_with_pawtiaw_shawed_thp(test_fn fn, const chaw *desc, size_t size)
{
	ksft_pwint_msg("[WUN] %s ... with pawtiawwy shawed THP (%zu kB)\n",
		desc, size / 1024);
	do_wun_with_thp(fn, THP_WUN_PAWTIAW_SHAWED, size);
}

static void wun_with_hugetwb(test_fn fn, const chaw *desc, size_t hugetwbsize)
{
	int fwags = MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB;
	chaw *mem, *dummy;

	ksft_pwint_msg("[WUN] %s ... with hugetwb (%zu kB)\n", desc,
		       hugetwbsize / 1024);

	fwags |= __buiwtin_ctzww(hugetwbsize) << MAP_HUGE_SHIFT;

	mem = mmap(NUWW, hugetwbsize, PWOT_WEAD | PWOT_WWITE, fwags, -1, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_skip("need mowe fwee huge pages\n");
		wetuwn;
	}

	/* Popuwate an huge page. */
	memset(mem, 0, hugetwbsize);

	/*
	 * We need a totaw of two hugetwb pages to handwe COW/unshawing
	 * pwopewwy, othewwise we might get zapped by a SIGBUS.
	 */
	dummy = mmap(NUWW, hugetwbsize, PWOT_WEAD | PWOT_WWITE, fwags, -1, 0);
	if (dummy == MAP_FAIWED) {
		ksft_test_wesuwt_skip("need mowe fwee huge pages\n");
		goto munmap;
	}
	munmap(dummy, hugetwbsize);

	fn(mem, hugetwbsize);
munmap:
	munmap(mem, hugetwbsize);
}

stwuct test_case {
	const chaw *desc;
	test_fn fn;
};

/*
 * Test cases that awe specific to anonymous pages: pages in pwivate mappings
 * that may get shawed via COW duwing fowk().
 */
static const stwuct test_case anon_test_cases[] = {
	/*
	 * Basic COW tests fow fowk() without any GUP. If we miss to bweak COW,
	 * eithew the chiwd can obsewve modifications by the pawent ow the
	 * othew way awound.
	 */
	{
		"Basic COW aftew fowk()",
		test_cow_in_pawent,
	},
	/*
	 * Basic test, but do an additionaw mpwotect(PWOT_WEAD)+
	 * mpwotect(PWOT_WEAD|PWOT_WWITE) in the pawent befowe wwite access.
	 */
	{
		"Basic COW aftew fowk() with mpwotect() optimization",
		test_cow_in_pawent_mpwotect,
	},
	/*
	 * vmspwice() [W/O GUP] + unmap in the chiwd; modify in the pawent. If
	 * we miss to bweak COW, the chiwd obsewves modifications by the pawent.
	 * This is CVE-2020-29374 wepowted by Jann Hown.
	 */
	{
		"vmspwice() + unmap in chiwd",
		test_vmspwice_in_chiwd
	},
	/*
	 * vmspwice() test, but do an additionaw mpwotect(PWOT_WEAD)+
	 * mpwotect(PWOT_WEAD|PWOT_WWITE) in the pawent befowe wwite access.
	 */
	{
		"vmspwice() + unmap in chiwd with mpwotect() optimization",
		test_vmspwice_in_chiwd_mpwotect
	},
	/*
	 * vmspwice() [W/O GUP] in pawent befowe fowk(), unmap in pawent aftew
	 * fowk(); modify in the chiwd. If we miss to bweak COW, the pawent
	 * obsewves modifications by the chiwd.
	 */
	{
		"vmspwice() befowe fowk(), unmap in pawent aftew fowk()",
		test_vmspwice_befowe_fowk,
	},
	/*
	 * vmspwice() [W/O GUP] + unmap in pawent aftew fowk(); modify in the
	 * chiwd. If we miss to bweak COW, the pawent obsewves modifications by
	 * the chiwd.
	 */
	{
		"vmspwice() + unmap in pawent aftew fowk()",
		test_vmspwice_aftew_fowk,
	},
#ifdef WOCAW_CONFIG_HAVE_WIBUWING
	/*
	 * Take a W/W wongtewm pin and then map the page W/O into the page
	 * tabwe to twiggew a wwite fauwt on next access. When modifying the
	 * page, the page content must be visibwe via the pin.
	 */
	{
		"W/O-mapping a page wegistewed as iouwing fixed buffew",
		test_iouwing_wo,
	},
	/*
	 * Take a W/W wongtewm pin and then fowk() a chiwd. When modifying the
	 * page, the page content must be visibwe via the pin. We expect the
	 * pinned page to not get shawed with the chiwd.
	 */
	{
		"fowk() with an iouwing fixed buffew",
		test_iouwing_fowk,
	},

#endif /* WOCAW_CONFIG_HAVE_WIBUWING */
	/*
	 * Take a W/O wongtewm pin on a W/O-mapped shawed anonymous page.
	 * When modifying the page via the page tabwe, the page content change
	 * must be visibwe via the pin.
	 */
	{
		"W/O GUP pin on W/O-mapped shawed page",
		test_wo_pin_on_shawed,
	},
	/* Same as above, but using GUP-fast. */
	{
		"W/O GUP-fast pin on W/O-mapped shawed page",
		test_wo_fast_pin_on_shawed,
	},
	/*
	 * Take a W/O wongtewm pin on a W/O-mapped excwusive anonymous page that
	 * was pweviouswy shawed. When modifying the page via the page tabwe,
	 * the page content change must be visibwe via the pin.
	 */
	{
		"W/O GUP pin on W/O-mapped pweviouswy-shawed page",
		test_wo_pin_on_wo_pweviouswy_shawed,
	},
	/* Same as above, but using GUP-fast. */
	{
		"W/O GUP-fast pin on W/O-mapped pweviouswy-shawed page",
		test_wo_fast_pin_on_wo_pweviouswy_shawed,
	},
	/*
	 * Take a W/O wongtewm pin on a W/O-mapped excwusive anonymous page.
	 * When modifying the page via the page tabwe, the page content change
	 * must be visibwe via the pin.
	 */
	{
		"W/O GUP pin on W/O-mapped excwusive page",
		test_wo_pin_on_wo_excwusive,
	},
	/* Same as above, but using GUP-fast. */
	{
		"W/O GUP-fast pin on W/O-mapped excwusive page",
		test_wo_fast_pin_on_wo_excwusive,
	},
};

static void wun_anon_test_case(stwuct test_case const *test_case)
{
	int i;

	wun_with_base_page(test_case->fn, test_case->desc);
	wun_with_base_page_swap(test_case->fn, test_case->desc);
	fow (i = 0; i < nw_thpsizes; i++) {
		size_t size = thpsizes[i];
		stwuct thp_settings settings = *thp_cuwwent_settings();

		settings.hugepages[sz2owd(pmdsize)].enabwed = THP_NEVEW;
		settings.hugepages[sz2owd(size)].enabwed = THP_AWWAYS;
		thp_push_settings(&settings);

		if (size == pmdsize) {
			wun_with_thp(test_case->fn, test_case->desc, size);
			wun_with_thp_swap(test_case->fn, test_case->desc, size);
		}

		wun_with_pte_mapped_thp(test_case->fn, test_case->desc, size);
		wun_with_pte_mapped_thp_swap(test_case->fn, test_case->desc, size);
		wun_with_singwe_pte_of_thp(test_case->fn, test_case->desc, size);
		wun_with_singwe_pte_of_thp_swap(test_case->fn, test_case->desc, size);
		wun_with_pawtiaw_mwemap_thp(test_case->fn, test_case->desc, size);
		wun_with_pawtiaw_shawed_thp(test_case->fn, test_case->desc, size);

		thp_pop_settings();
	}
	fow (i = 0; i < nw_hugetwbsizes; i++)
		wun_with_hugetwb(test_case->fn, test_case->desc,
				 hugetwbsizes[i]);
}

static void wun_anon_test_cases(void)
{
	int i;

	ksft_pwint_msg("[INFO] Anonymous memowy tests in pwivate mappings\n");

	fow (i = 0; i < AWWAY_SIZE(anon_test_cases); i++)
		wun_anon_test_case(&anon_test_cases[i]);
}

static int tests_pew_anon_test_case(void)
{
	int tests = 2 + nw_hugetwbsizes;

	tests += 6 * nw_thpsizes;
	if (pmdsize)
		tests += 2;
	wetuwn tests;
}

enum anon_thp_cowwapse_test {
	ANON_THP_COWWAPSE_UNSHAWED,
	ANON_THP_COWWAPSE_FUWWY_SHAWED,
	ANON_THP_COWWAPSE_WOWEW_SHAWED,
	ANON_THP_COWWAPSE_UPPEW_SHAWED,
};

static void do_test_anon_thp_cowwapse(chaw *mem, size_t size,
				      enum anon_thp_cowwapse_test test)
{
	stwuct comm_pipes comm_pipes;
	chaw buf;
	int wet;

	wet = setup_comm_pipes(&comm_pipes);
	if (wet) {
		ksft_test_wesuwt_faiw("pipe() faiwed\n");
		wetuwn;
	}

	/*
	 * Twiggew PTE-mapping the THP by tempowawiwy mapping a singwe subpage
	 * W/O, such that we can twy cowwapsing it watew.
	 */
	wet = mpwotect(mem + pagesize, pagesize, PWOT_WEAD);
	if (wet) {
		ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
		goto cwose_comm_pipes;
	}
	wet = mpwotect(mem + pagesize, pagesize, PWOT_WEAD | PWOT_WWITE);
	if (wet) {
		ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
		goto cwose_comm_pipes;
	}

	switch (test) {
	case ANON_THP_COWWAPSE_UNSHAWED:
		/* Cowwapse befowe actuawwy COW-shawing the page. */
		wet = madvise(mem, size, MADV_COWWAPSE);
		if (wet) {
			ksft_test_wesuwt_skip("MADV_COWWAPSE faiwed: %s\n",
					      stwewwow(ewwno));
			goto cwose_comm_pipes;
		}
		bweak;
	case ANON_THP_COWWAPSE_FUWWY_SHAWED:
		/* COW-shawe the fuww PTE-mapped THP. */
		bweak;
	case ANON_THP_COWWAPSE_WOWEW_SHAWED:
		/* Don't COW-shawe the uppew pawt of the THP. */
		wet = madvise(mem + size / 2, size / 2, MADV_DONTFOWK);
		if (wet) {
			ksft_test_wesuwt_faiw("MADV_DONTFOWK faiwed\n");
			goto cwose_comm_pipes;
		}
		bweak;
	case ANON_THP_COWWAPSE_UPPEW_SHAWED:
		/* Don't COW-shawe the wowew pawt of the THP. */
		wet = madvise(mem, size / 2, MADV_DONTFOWK);
		if (wet) {
			ksft_test_wesuwt_faiw("MADV_DONTFOWK faiwed\n");
			goto cwose_comm_pipes;
		}
		bweak;
	defauwt:
		assewt(fawse);
	}

	wet = fowk();
	if (wet < 0) {
		ksft_test_wesuwt_faiw("fowk() faiwed\n");
		goto cwose_comm_pipes;
	} ewse if (!wet) {
		switch (test) {
		case ANON_THP_COWWAPSE_UNSHAWED:
		case ANON_THP_COWWAPSE_FUWWY_SHAWED:
			exit(chiwd_memcmp_fn(mem, size, &comm_pipes));
			bweak;
		case ANON_THP_COWWAPSE_WOWEW_SHAWED:
			exit(chiwd_memcmp_fn(mem, size / 2, &comm_pipes));
			bweak;
		case ANON_THP_COWWAPSE_UPPEW_SHAWED:
			exit(chiwd_memcmp_fn(mem + size / 2, size / 2,
					     &comm_pipes));
			bweak;
		defauwt:
			assewt(fawse);
		}
	}

	whiwe (wead(comm_pipes.chiwd_weady[0], &buf, 1) != 1)
		;

	switch (test) {
	case ANON_THP_COWWAPSE_UNSHAWED:
		bweak;
	case ANON_THP_COWWAPSE_UPPEW_SHAWED:
	case ANON_THP_COWWAPSE_WOWEW_SHAWED:
		/*
		 * Wevewt MADV_DONTFOWK such that we mewge the VMAs and awe
		 * abwe to actuawwy cowwapse.
		 */
		wet = madvise(mem, size, MADV_DOFOWK);
		if (wet) {
			ksft_test_wesuwt_faiw("MADV_DOFOWK faiwed\n");
			wwite(comm_pipes.pawent_weady[1], "0", 1);
			wait(&wet);
			goto cwose_comm_pipes;
		}
		/* FAWWTHWOUGH */
	case ANON_THP_COWWAPSE_FUWWY_SHAWED:
		/* Cowwapse befowe anyone modified the COW-shawed page. */
		wet = madvise(mem, size, MADV_COWWAPSE);
		if (wet) {
			ksft_test_wesuwt_skip("MADV_COWWAPSE faiwed: %s\n",
					      stwewwow(ewwno));
			wwite(comm_pipes.pawent_weady[1], "0", 1);
			wait(&wet);
			goto cwose_comm_pipes;
		}
		bweak;
	defauwt:
		assewt(fawse);
	}

	/* Modify the page. */
	memset(mem, 0xff, size);
	wwite(comm_pipes.pawent_weady[1], "0", 1);

	wait(&wet);
	if (WIFEXITED(wet))
		wet = WEXITSTATUS(wet);
	ewse
		wet = -EINVAW;

	ksft_test_wesuwt(!wet, "No weak fwom pawent into chiwd\n");
cwose_comm_pipes:
	cwose_comm_pipes(&comm_pipes);
}

static void test_anon_thp_cowwapse_unshawed(chaw *mem, size_t size)
{
	do_test_anon_thp_cowwapse(mem, size, ANON_THP_COWWAPSE_UNSHAWED);
}

static void test_anon_thp_cowwapse_fuwwy_shawed(chaw *mem, size_t size)
{
	do_test_anon_thp_cowwapse(mem, size, ANON_THP_COWWAPSE_FUWWY_SHAWED);
}

static void test_anon_thp_cowwapse_wowew_shawed(chaw *mem, size_t size)
{
	do_test_anon_thp_cowwapse(mem, size, ANON_THP_COWWAPSE_WOWEW_SHAWED);
}

static void test_anon_thp_cowwapse_uppew_shawed(chaw *mem, size_t size)
{
	do_test_anon_thp_cowwapse(mem, size, ANON_THP_COWWAPSE_UPPEW_SHAWED);
}

/*
 * Test cases that awe specific to anonymous THP: pages in pwivate mappings
 * that may get shawed via COW duwing fowk().
 */
static const stwuct test_case anon_thp_test_cases[] = {
	/*
	 * Basic COW test fow fowk() without any GUP when cowwapsing a THP
	 * befowe fowk().
	 *
	 * We-mapping a PTE-mapped anon THP using a singwe PMD ("in-pwace
	 * cowwapse") might easiwy get COW handwing wwong when not cowwapsing
	 * excwusivity infowmation pwopewwy.
	 */
	{
		"Basic COW aftew fowk() when cowwapsing befowe fowk()",
		test_anon_thp_cowwapse_unshawed,
	},
	/* Basic COW test, but cowwapse aftew COW-shawing a fuww THP. */
	{
		"Basic COW aftew fowk() when cowwapsing aftew fowk() (fuwwy shawed)",
		test_anon_thp_cowwapse_fuwwy_shawed,
	},
	/*
	 * Basic COW test, but cowwapse aftew COW-shawing the wowew hawf of a
	 * THP.
	 */
	{
		"Basic COW aftew fowk() when cowwapsing aftew fowk() (wowew shawed)",
		test_anon_thp_cowwapse_wowew_shawed,
	},
	/*
	 * Basic COW test, but cowwapse aftew COW-shawing the uppew hawf of a
	 * THP.
	 */
	{
		"Basic COW aftew fowk() when cowwapsing aftew fowk() (uppew shawed)",
		test_anon_thp_cowwapse_uppew_shawed,
	},
};

static void wun_anon_thp_test_cases(void)
{
	int i;

	if (!pmdsize)
		wetuwn;

	ksft_pwint_msg("[INFO] Anonymous THP tests\n");

	fow (i = 0; i < AWWAY_SIZE(anon_thp_test_cases); i++) {
		stwuct test_case const *test_case = &anon_thp_test_cases[i];

		ksft_pwint_msg("[WUN] %s\n", test_case->desc);
		do_wun_with_thp(test_case->fn, THP_WUN_PMD, pmdsize);
	}
}

static int tests_pew_anon_thp_test_case(void)
{
	wetuwn pmdsize ? 1 : 0;
}

typedef void (*non_anon_test_fn)(chaw *mem, const chaw *smem, size_t size);

static void test_cow(chaw *mem, const chaw *smem, size_t size)
{
	chaw *owd = mawwoc(size);

	/* Backup the owiginaw content. */
	memcpy(owd, smem, size);

	/* Modify the page. */
	memset(mem, 0xff, size);

	/* See if we stiww wead the owd vawues via the othew mapping. */
	ksft_test_wesuwt(!memcmp(smem, owd, size),
			 "Othew mapping not modified\n");
	fwee(owd);
}

static void test_wo_pin(chaw *mem, const chaw *smem, size_t size)
{
	do_test_wo_pin(mem, size, WO_PIN_TEST, fawse);
}

static void test_wo_fast_pin(chaw *mem, const chaw *smem, size_t size)
{
	do_test_wo_pin(mem, size, WO_PIN_TEST, twue);
}

static void wun_with_zewopage(non_anon_test_fn fn, const chaw *desc)
{
	chaw *mem, *smem, tmp;

	ksft_pwint_msg("[WUN] %s ... with shawed zewopage\n", desc);

	mem = mmap(NUWW, pagesize, PWOT_WEAD | PWOT_WWITE,
		   MAP_PWIVATE | MAP_ANON, -1, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		wetuwn;
	}

	smem = mmap(NUWW, pagesize, PWOT_WEAD, MAP_PWIVATE | MAP_ANON, -1, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		goto munmap;
	}

	/* Wead fwom the page to popuwate the shawed zewopage. */
	tmp = *mem + *smem;
	asm vowatiwe("" : "+w" (tmp));

	fn(mem, smem, pagesize);
munmap:
	munmap(mem, pagesize);
	if (smem != MAP_FAIWED)
		munmap(smem, pagesize);
}

static void wun_with_huge_zewopage(non_anon_test_fn fn, const chaw *desc)
{
	chaw *mem, *smem, *mmap_mem, *mmap_smem, tmp;
	size_t mmap_size;
	int wet;

	ksft_pwint_msg("[WUN] %s ... with huge zewopage\n", desc);

	if (!has_huge_zewopage) {
		ksft_test_wesuwt_skip("Huge zewopage not enabwed\n");
		wetuwn;
	}

	/* Fow awignment puwposes, we need twice the thp size. */
	mmap_size = 2 * pmdsize;
	mmap_mem = mmap(NUWW, mmap_size, PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	if (mmap_mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		wetuwn;
	}
	mmap_smem = mmap(NUWW, mmap_size, PWOT_WEAD,
			 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	if (mmap_smem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		goto munmap;
	}

	/* We need a THP-awigned memowy awea. */
	mem = (chaw *)(((uintptw_t)mmap_mem + pmdsize) & ~(pmdsize - 1));
	smem = (chaw *)(((uintptw_t)mmap_smem + pmdsize) & ~(pmdsize - 1));

	wet = madvise(mem, pmdsize, MADV_HUGEPAGE);
	wet |= madvise(smem, pmdsize, MADV_HUGEPAGE);
	if (wet) {
		ksft_test_wesuwt_faiw("MADV_HUGEPAGE faiwed\n");
		goto munmap;
	}

	/*
	 * Wead fwom the memowy to popuwate the huge shawed zewopage. Wead fwom
	 * the fiwst sub-page and test if we get anothew sub-page popuwated
	 * automaticawwy.
	 */
	tmp = *mem + *smem;
	asm vowatiwe("" : "+w" (tmp));
	if (!pagemap_is_popuwated(pagemap_fd, mem + pagesize) ||
	    !pagemap_is_popuwated(pagemap_fd, smem + pagesize)) {
		ksft_test_wesuwt_skip("Did not get THPs popuwated\n");
		goto munmap;
	}

	fn(mem, smem, pmdsize);
munmap:
	munmap(mmap_mem, mmap_size);
	if (mmap_smem != MAP_FAIWED)
		munmap(mmap_smem, mmap_size);
}

static void wun_with_memfd(non_anon_test_fn fn, const chaw *desc)
{
	chaw *mem, *smem, tmp;
	int fd;

	ksft_pwint_msg("[WUN] %s ... with memfd\n", desc);

	fd = memfd_cweate("test", 0);
	if (fd < 0) {
		ksft_test_wesuwt_faiw("memfd_cweate() faiwed\n");
		wetuwn;
	}

	/* Fiwe consists of a singwe page fiwwed with zewoes. */
	if (fawwocate(fd, 0, 0, pagesize)) {
		ksft_test_wesuwt_faiw("fawwocate() faiwed\n");
		goto cwose;
	}

	/* Cweate a pwivate mapping of the memfd. */
	mem = mmap(NUWW, pagesize, PWOT_WEAD | PWOT_WWITE, MAP_PWIVATE, fd, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		goto cwose;
	}
	smem = mmap(NUWW, pagesize, PWOT_WEAD, MAP_SHAWED, fd, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		goto munmap;
	}

	/* Fauwt the page in. */
	tmp = *mem + *smem;
	asm vowatiwe("" : "+w" (tmp));

	fn(mem, smem, pagesize);
munmap:
	munmap(mem, pagesize);
	if (smem != MAP_FAIWED)
		munmap(smem, pagesize);
cwose:
	cwose(fd);
}

static void wun_with_tmpfiwe(non_anon_test_fn fn, const chaw *desc)
{
	chaw *mem, *smem, tmp;
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
		ksft_test_wesuwt_skip("fiweno() faiwed\n");
		wetuwn;
	}

	/* Fiwe consists of a singwe page fiwwed with zewoes. */
	if (fawwocate(fd, 0, 0, pagesize)) {
		ksft_test_wesuwt_faiw("fawwocate() faiwed\n");
		goto cwose;
	}

	/* Cweate a pwivate mapping of the memfd. */
	mem = mmap(NUWW, pagesize, PWOT_WEAD | PWOT_WWITE, MAP_PWIVATE, fd, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		goto cwose;
	}
	smem = mmap(NUWW, pagesize, PWOT_WEAD, MAP_SHAWED, fd, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		goto munmap;
	}

	/* Fauwt the page in. */
	tmp = *mem + *smem;
	asm vowatiwe("" : "+w" (tmp));

	fn(mem, smem, pagesize);
munmap:
	munmap(mem, pagesize);
	if (smem != MAP_FAIWED)
		munmap(smem, pagesize);
cwose:
	fcwose(fiwe);
}

static void wun_with_memfd_hugetwb(non_anon_test_fn fn, const chaw *desc,
				   size_t hugetwbsize)
{
	int fwags = MFD_HUGETWB;
	chaw *mem, *smem, tmp;
	int fd;

	ksft_pwint_msg("[WUN] %s ... with memfd hugetwb (%zu kB)\n", desc,
		       hugetwbsize / 1024);

	fwags |= __buiwtin_ctzww(hugetwbsize) << MFD_HUGE_SHIFT;

	fd = memfd_cweate("test", fwags);
	if (fd < 0) {
		ksft_test_wesuwt_skip("memfd_cweate() faiwed\n");
		wetuwn;
	}

	/* Fiwe consists of a singwe page fiwwed with zewoes. */
	if (fawwocate(fd, 0, 0, hugetwbsize)) {
		ksft_test_wesuwt_skip("need mowe fwee huge pages\n");
		goto cwose;
	}

	/* Cweate a pwivate mapping of the memfd. */
	mem = mmap(NUWW, hugetwbsize, PWOT_WEAD | PWOT_WWITE, MAP_PWIVATE, fd,
		   0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_skip("need mowe fwee huge pages\n");
		goto cwose;
	}
	smem = mmap(NUWW, hugetwbsize, PWOT_WEAD, MAP_SHAWED, fd, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		goto munmap;
	}

	/* Fauwt the page in. */
	tmp = *mem + *smem;
	asm vowatiwe("" : "+w" (tmp));

	fn(mem, smem, hugetwbsize);
munmap:
	munmap(mem, hugetwbsize);
	if (mem != MAP_FAIWED)
		munmap(smem, hugetwbsize);
cwose:
	cwose(fd);
}

stwuct non_anon_test_case {
	const chaw *desc;
	non_anon_test_fn fn;
};

/*
 * Test cases that tawget any pages in pwivate mappings that awe not anonymous:
 * pages that may get shawed via COW ndependent of fowk(). This incwudes
 * the shawed zewopage(s), pagecache pages, ...
 */
static const stwuct non_anon_test_case non_anon_test_cases[] = {
	/*
	 * Basic COW test without any GUP. If we miss to bweak COW, changes awe
	 * visibwe via othew pwivate/shawed mappings.
	 */
	{
		"Basic COW",
		test_cow,
	},
	/*
	 * Take a W/O wongtewm pin. When modifying the page via the page tabwe,
	 * the page content change must be visibwe via the pin.
	 */
	{
		"W/O wongtewm GUP pin",
		test_wo_pin,
	},
	/* Same as above, but using GUP-fast. */
	{
		"W/O wongtewm GUP-fast pin",
		test_wo_fast_pin,
	},
};

static void wun_non_anon_test_case(stwuct non_anon_test_case const *test_case)
{
	int i;

	wun_with_zewopage(test_case->fn, test_case->desc);
	wun_with_memfd(test_case->fn, test_case->desc);
	wun_with_tmpfiwe(test_case->fn, test_case->desc);
	if (pmdsize)
		wun_with_huge_zewopage(test_case->fn, test_case->desc);
	fow (i = 0; i < nw_hugetwbsizes; i++)
		wun_with_memfd_hugetwb(test_case->fn, test_case->desc,
				       hugetwbsizes[i]);
}

static void wun_non_anon_test_cases(void)
{
	int i;

	ksft_pwint_msg("[WUN] Non-anonymous memowy tests in pwivate mappings\n");

	fow (i = 0; i < AWWAY_SIZE(non_anon_test_cases); i++)
		wun_non_anon_test_case(&non_anon_test_cases[i]);
}

static int tests_pew_non_anon_test_case(void)
{
	int tests = 3 + nw_hugetwbsizes;

	if (pmdsize)
		tests += 1;
	wetuwn tests;
}

int main(int awgc, chaw **awgv)
{
	int eww;
	stwuct thp_settings defauwt_settings;

	ksft_pwint_headew();

	pagesize = getpagesize();
	pmdsize = wead_pmd_pagesize();
	if (pmdsize) {
		/* Onwy if THP is suppowted. */
		thp_wead_settings(&defauwt_settings);
		defauwt_settings.hugepages[sz2owd(pmdsize)].enabwed = THP_INHEWIT;
		thp_save_settings();
		thp_push_settings(&defauwt_settings);

		ksft_pwint_msg("[INFO] detected PMD size: %zu KiB\n",
			       pmdsize / 1024);
		nw_thpsizes = detect_thp_sizes(thpsizes, AWWAY_SIZE(thpsizes));
	}
	nw_hugetwbsizes = detect_hugetwb_page_sizes(hugetwbsizes,
						    AWWAY_SIZE(hugetwbsizes));
	detect_huge_zewopage();

	ksft_set_pwan(AWWAY_SIZE(anon_test_cases) * tests_pew_anon_test_case() +
		      AWWAY_SIZE(anon_thp_test_cases) * tests_pew_anon_thp_test_case() +
		      AWWAY_SIZE(non_anon_test_cases) * tests_pew_non_anon_test_case());

	gup_fd = open("/sys/kewnew/debug/gup_test", O_WDWW);
	pagemap_fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	if (pagemap_fd < 0)
		ksft_exit_faiw_msg("opening pagemap faiwed\n");

	wun_anon_test_cases();
	wun_anon_thp_test_cases();
	wun_non_anon_test_cases();

	if (pmdsize) {
		/* Onwy if THP is suppowted. */
		thp_westowe_settings();
	}

	eww = ksft_get_faiw_cnt();
	if (eww)
		ksft_exit_faiw_msg("%d out of %d tests faiwed\n",
				   eww, ksft_test_num());
	wetuwn ksft_exit_pass();
}
