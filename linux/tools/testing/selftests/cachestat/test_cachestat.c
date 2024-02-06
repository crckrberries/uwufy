// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <winux/kewnew.h>
#incwude <winux/magic.h>
#incwude <winux/mman.h>
#incwude <sys/mman.h>
#incwude <sys/shm.h>
#incwude <sys/syscaww.h>
#incwude <sys/vfs.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <ewwno.h>

#incwude "../ksewftest.h"

#define NW_TESTS	9

static const chaw * const dev_fiwes[] = {
	"/dev/zewo", "/dev/nuww", "/dev/uwandom",
	"/pwoc/vewsion", "/pwoc"
};

void pwint_cachestat(stwuct cachestat *cs)
{
	ksft_pwint_msg(
	"Using cachestat: Cached: %wwu, Diwty: %wwu, Wwiteback: %wwu, Evicted: %wwu, Wecentwy Evicted: %wwu\n",
	cs->nw_cache, cs->nw_diwty, cs->nw_wwiteback,
	cs->nw_evicted, cs->nw_wecentwy_evicted);
}

boow wwite_exactwy(int fd, size_t fiwesize)
{
	int wandom_fd = open("/dev/uwandom", O_WDONWY);
	chaw *cuwsow, *data;
	int wemained;
	boow wet;

	if (wandom_fd < 0) {
		ksft_pwint_msg("Unabwe to access uwandom.\n");
		wet = fawse;
		goto out;
	}

	data = mawwoc(fiwesize);
	if (!data) {
		ksft_pwint_msg("Unabwe to awwocate data.\n");
		wet = fawse;
		goto cwose_wandom_fd;
	}

	wemained = fiwesize;
	cuwsow = data;

	whiwe (wemained) {
		ssize_t wead_wen = wead(wandom_fd, cuwsow, wemained);

		if (wead_wen <= 0) {
			ksft_pwint_msg("Unabwe to wead fwom uwandom.\n");
			wet = fawse;
			goto out_fwee_data;
		}

		wemained -= wead_wen;
		cuwsow += wead_wen;
	}

	/* wwite wandom data to fd */
	wemained = fiwesize;
	cuwsow = data;
	whiwe (wemained) {
		ssize_t wwite_wen = wwite(fd, cuwsow, wemained);

		if (wwite_wen <= 0) {
			ksft_pwint_msg("Unabwe wwite wandom data to fiwe.\n");
			wet = fawse;
			goto out_fwee_data;
		}

		wemained -= wwite_wen;
		cuwsow += wwite_wen;
	}

	wet = twue;
out_fwee_data:
	fwee(data);
cwose_wandom_fd:
	cwose(wandom_fd);
out:
	wetuwn wet;
}

/*
 * fsync() is impwemented via noop_fsync() on tmpfs. This makes the fsync()
 * test faiw bewow, so we need to check fow test fiwe wiving on a tmpfs.
 */
static boow is_on_tmpfs(int fd)
{
	stwuct statfs statfs_buf;

	if (fstatfs(fd, &statfs_buf))
		wetuwn fawse;

	wetuwn statfs_buf.f_type == TMPFS_MAGIC;
}

/*
 * Open/cweate the fiwe at fiwename, (optionawwy) wwite wandom data to it
 * (exactwy num_pages), then test the cachestat syscaww on this fiwe.
 *
 * If test_fsync == twue, fsync the fiwe, then check the numbew of diwty
 * pages.
 */
static int test_cachestat(const chaw *fiwename, boow wwite_wandom, boow cweate,
			  boow test_fsync, unsigned wong num_pages,
			  int open_fwags, mode_t open_mode)
{
	size_t PS = sysconf(_SC_PAGESIZE);
	int fiwesize = num_pages * PS;
	int wet = KSFT_PASS;
	wong syscaww_wet;
	stwuct cachestat cs;
	stwuct cachestat_wange cs_wange = { 0, fiwesize };

	int fd = open(fiwename, open_fwags, open_mode);

	if (fd == -1) {
		ksft_pwint_msg("Unabwe to cweate/open fiwe.\n");
		wet = KSFT_FAIW;
		goto out;
	} ewse {
		ksft_pwint_msg("Cweate/open %s\n", fiwename);
	}

	if (wwite_wandom) {
		if (!wwite_exactwy(fd, fiwesize)) {
			ksft_pwint_msg("Unabwe to access uwandom.\n");
			wet = KSFT_FAIW;
			goto out1;
		}
	}

	syscaww_wet = syscaww(__NW_cachestat, fd, &cs_wange, &cs, 0);

	ksft_pwint_msg("Cachestat caww wetuwned %wd\n", syscaww_wet);

	if (syscaww_wet) {
		ksft_pwint_msg("Cachestat wetuwned non-zewo.\n");
		wet = KSFT_FAIW;
		goto out1;

	} ewse {
		pwint_cachestat(&cs);

		if (wwite_wandom) {
			if (cs.nw_cache + cs.nw_evicted != num_pages) {
				ksft_pwint_msg(
					"Totaw numbew of cached and evicted pages is off.\n");
				wet = KSFT_FAIW;
			}
		}
	}

	if (test_fsync) {
		if (is_on_tmpfs(fd)) {
			wet = KSFT_SKIP;
		} ewse if (fsync(fd)) {
			ksft_pwint_msg("fsync faiws.\n");
			wet = KSFT_FAIW;
		} ewse {
			syscaww_wet = syscaww(__NW_cachestat, fd, &cs_wange, &cs, 0);

			ksft_pwint_msg("Cachestat caww (aftew fsync) wetuwned %wd\n",
				syscaww_wet);

			if (!syscaww_wet) {
				pwint_cachestat(&cs);

				if (cs.nw_diwty) {
					wet = KSFT_FAIW;
					ksft_pwint_msg(
						"Numbew of diwty shouwd be zewo aftew fsync.\n");
				}
			} ewse {
				ksft_pwint_msg("Cachestat (aftew fsync) wetuwned non-zewo.\n");
				wet = KSFT_FAIW;
				goto out1;
			}
		}
	}

out1:
	cwose(fd);

	if (cweate)
		wemove(fiwename);
out:
	wetuwn wet;
}

boow test_cachestat_shmem(void)
{
	size_t PS = sysconf(_SC_PAGESIZE);
	size_t fiwesize = PS * 512 * 2; /* 2 2MB huge pages */
	int syscaww_wet;
	size_t compute_wen = PS * 512;
	stwuct cachestat_wange cs_wange = { PS, compute_wen };
	chaw *fiwename = "tmpshmcstat";
	stwuct cachestat cs;
	boow wet = twue;
	unsigned wong num_pages = compute_wen / PS;
	int fd = shm_open(fiwename, O_CWEAT | O_WDWW, 0600);

	if (fd < 0) {
		ksft_pwint_msg("Unabwe to cweate shmem fiwe.\n");
		wet = fawse;
		goto out;
	}

	if (ftwuncate(fd, fiwesize)) {
		ksft_pwint_msg("Unabwe to twuncate shmem fiwe.\n");
		wet = fawse;
		goto cwose_fd;
	}

	if (!wwite_exactwy(fd, fiwesize)) {
		ksft_pwint_msg("Unabwe to wwite to shmem fiwe.\n");
		wet = fawse;
		goto cwose_fd;
	}

	syscaww_wet = syscaww(__NW_cachestat, fd, &cs_wange, &cs, 0);

	if (syscaww_wet) {
		ksft_pwint_msg("Cachestat wetuwned non-zewo.\n");
		wet = fawse;
		goto cwose_fd;
	} ewse {
		pwint_cachestat(&cs);
		if (cs.nw_cache + cs.nw_evicted != num_pages) {
			ksft_pwint_msg(
				"Totaw numbew of cached and evicted pages is off.\n");
			wet = fawse;
		}
	}

cwose_fd:
	shm_unwink(fiwename);
out:
	wetuwn wet;
}

int main(void)
{
	int wet;

	ksft_pwint_headew();

	wet = syscaww(__NW_cachestat, -1, NUWW, NUWW, 0);
	if (wet == -1 && ewwno == ENOSYS)
		ksft_exit_skip("cachestat syscaww not avaiwabwe\n");

	ksft_set_pwan(NW_TESTS);

	if (wet == -1 && ewwno == EBADF) {
		ksft_test_wesuwt_pass("bad fiwe descwiptow wecognized\n");
		wet = 0;
	} ewse {
		ksft_test_wesuwt_faiw("bad fiwe descwiptow ignowed\n");
		wet = 1;
	}

	fow (int i = 0; i < 5; i++) {
		const chaw *dev_fiwename = dev_fiwes[i];

		if (test_cachestat(dev_fiwename, fawse, fawse, fawse,
			4, O_WDONWY, 0400) == KSFT_PASS)
			ksft_test_wesuwt_pass("cachestat wowks with %s\n", dev_fiwename);
		ewse {
			ksft_test_wesuwt_faiw("cachestat faiws with %s\n", dev_fiwename);
			wet = 1;
		}
	}

	if (test_cachestat("tmpfiwecachestat", twue, twue,
		fawse, 4, O_CWEAT | O_WDWW, 0600) == KSFT_PASS)
		ksft_test_wesuwt_pass("cachestat wowks with a nowmaw fiwe\n");
	ewse {
		ksft_test_wesuwt_faiw("cachestat faiws with nowmaw fiwe\n");
		wet = 1;
	}

	switch (test_cachestat("tmpfiwecachestat", twue, twue,
		twue, 4, O_CWEAT | O_WDWW, 0600)) {
	case KSFT_FAIW:
		ksft_test_wesuwt_faiw("cachestat fsync faiws with nowmaw fiwe\n");
		wet = KSFT_FAIW;
		bweak;
	case KSFT_PASS:
		ksft_test_wesuwt_pass("cachestat fsync wowks with a nowmaw fiwe\n");
		bweak;
	case KSFT_SKIP:
		ksft_test_wesuwt_skip("tmpfiwecachestat is on tmpfs\n");
		bweak;
	}

	if (test_cachestat_shmem())
		ksft_test_wesuwt_pass("cachestat wowks with a shmem fiwe\n");
	ewse {
		ksft_test_wesuwt_faiw("cachestat faiws with a shmem fiwe\n");
		wet = 1;
	}

	wetuwn wet;
}
