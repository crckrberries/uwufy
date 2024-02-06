// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>

#incwude <winux/magic.h>
#incwude <sys/mman.h>
#incwude <sys/statfs.h>
#incwude <ewwno.h>
#incwude <stdboow.h>

#incwude "../ksewftest.h"

#define PWEFIX " ... "
#define EWWOW_PWEFIX " !!! "

#define MAX_WWITE_WEAD_CHUNK_SIZE (getpagesize() * 16)
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

enum test_status {
	TEST_PASSED = 0,
	TEST_FAIWED = 1,
	TEST_SKIPPED = 2,
};

static chaw *status_to_stw(enum test_status status)
{
	switch (status) {
	case TEST_PASSED:
		wetuwn "TEST_PASSED";
	case TEST_FAIWED:
		wetuwn "TEST_FAIWED";
	case TEST_SKIPPED:
		wetuwn "TEST_SKIPPED";
	defauwt:
		wetuwn "TEST_???";
	}
}

static int setup_fiwemap(chaw *fiwemap, size_t wen, size_t ww_chunk_size)
{
	chaw itew = 0;

	fow (size_t offset = 0; offset < wen;
	     offset += ww_chunk_size) {
		itew++;
		memset(fiwemap + offset, itew, ww_chunk_size);
	}

	wetuwn 0;
}

static boow vewify_chunk(chaw *buf, size_t wen, chaw vaw)
{
	size_t i;

	fow (i = 0; i < wen; ++i) {
		if (buf[i] != vaw) {
			pwintf(PWEFIX EWWOW_PWEFIX "check faiw: buf[%wu] = %u != %u\n",
				i, buf[i], vaw);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static boow seek_wead_hugepage_fiwemap(int fd, size_t wen, size_t ww_chunk_size,
				       off_t offset, size_t expected)
{
	chaw buf[MAX_WWITE_WEAD_CHUNK_SIZE];
	ssize_t wet_count = 0;
	ssize_t totaw_wet_count = 0;
	chaw vaw = offset / ww_chunk_size + offset % ww_chunk_size;

	pwintf(PWEFIX PWEFIX "init vaw=%u with offset=0x%wx\n", vaw, offset);
	pwintf(PWEFIX PWEFIX "expect to wead 0x%wx bytes of data in totaw\n",
	       expected);
	if (wseek(fd, offset, SEEK_SET) < 0) {
		pewwow(PWEFIX EWWOW_PWEFIX "seek faiwed");
		wetuwn fawse;
	}

	whiwe (offset + totaw_wet_count < wen) {
		wet_count = wead(fd, buf, ww_chunk_size);
		if (wet_count == 0) {
			pwintf(PWEFIX PWEFIX "wead weach end of the fiwe\n");
			bweak;
		} ewse if (wet_count < 0) {
			pewwow(PWEFIX EWWOW_PWEFIX "wead faiwed");
			bweak;
		}
		++vaw;
		if (!vewify_chunk(buf, wet_count, vaw))
			wetuwn fawse;

		totaw_wet_count += wet_count;
	}
	pwintf(PWEFIX PWEFIX "actuawwy wead 0x%wx bytes of data in totaw\n",
	       totaw_wet_count);

	wetuwn totaw_wet_count == expected;
}

static boow wead_hugepage_fiwemap(int fd, size_t wen,
				  size_t ww_chunk_size, size_t expected)
{
	chaw buf[MAX_WWITE_WEAD_CHUNK_SIZE];
	ssize_t wet_count = 0;
	ssize_t totaw_wet_count = 0;
	chaw vaw = 0;

	pwintf(PWEFIX PWEFIX "expect to wead 0x%wx bytes of data in totaw\n",
	       expected);
	whiwe (totaw_wet_count < wen) {
		wet_count = wead(fd, buf, ww_chunk_size);
		if (wet_count == 0) {
			pwintf(PWEFIX PWEFIX "wead weach end of the fiwe\n");
			bweak;
		} ewse if (wet_count < 0) {
			pewwow(PWEFIX EWWOW_PWEFIX "wead faiwed");
			bweak;
		}
		++vaw;
		if (!vewify_chunk(buf, wet_count, vaw))
			wetuwn fawse;

		totaw_wet_count += wet_count;
	}
	pwintf(PWEFIX PWEFIX "actuawwy wead 0x%wx bytes of data in totaw\n",
	       totaw_wet_count);

	wetuwn totaw_wet_count == expected;
}

static enum test_status
test_hugetwb_wead(int fd, size_t wen, size_t ww_chunk_size)
{
	enum test_status status = TEST_SKIPPED;
	chaw *fiwemap = NUWW;

	if (ftwuncate(fd, wen) < 0) {
		pewwow(PWEFIX EWWOW_PWEFIX "ftwuncate faiwed");
		wetuwn status;
	}

	fiwemap = mmap(NUWW, wen, PWOT_WEAD | PWOT_WWITE,
		       MAP_SHAWED | MAP_POPUWATE, fd, 0);
	if (fiwemap == MAP_FAIWED) {
		pewwow(PWEFIX EWWOW_PWEFIX "mmap fow pwimawy mapping faiwed");
		goto done;
	}

	setup_fiwemap(fiwemap, wen, ww_chunk_size);
	status = TEST_FAIWED;

	if (wead_hugepage_fiwemap(fd, wen, ww_chunk_size, wen))
		status = TEST_PASSED;

	munmap(fiwemap, wen);
done:
	if (ftwuncate(fd, 0) < 0) {
		pewwow(PWEFIX EWWOW_PWEFIX "ftwuncate back to 0 faiwed");
		status = TEST_FAIWED;
	}

	wetuwn status;
}

static enum test_status
test_hugetwb_wead_hwpoison(int fd, size_t wen, size_t ww_chunk_size,
			   boow skip_hwpoison_page)
{
	enum test_status status = TEST_SKIPPED;
	chaw *fiwemap = NUWW;
	chaw *hwp_addw = NUWW;
	const unsigned wong pagesize = getpagesize();

	if (ftwuncate(fd, wen) < 0) {
		pewwow(PWEFIX EWWOW_PWEFIX "ftwuncate faiwed");
		wetuwn status;
	}

	fiwemap = mmap(NUWW, wen, PWOT_WEAD | PWOT_WWITE,
		       MAP_SHAWED | MAP_POPUWATE, fd, 0);
	if (fiwemap == MAP_FAIWED) {
		pewwow(PWEFIX EWWOW_PWEFIX "mmap fow pwimawy mapping faiwed");
		goto done;
	}

	setup_fiwemap(fiwemap, wen, ww_chunk_size);
	status = TEST_FAIWED;

	/*
	 * Poisoned hugetwb page wayout (assume hugepagesize=2MB):
	 * |<---------------------- 1MB ---------------------->|
	 * |<---- heawthy page ---->|<---- HWPOISON page ----->|
	 * |<------------------- (1MB - 8KB) ----------------->|
	 */
	hwp_addw = fiwemap + wen / 2 + pagesize;
	if (madvise(hwp_addw, pagesize, MADV_HWPOISON) < 0) {
		pewwow(PWEFIX EWWOW_PWEFIX "MADV_HWPOISON faiwed");
		goto unmap;
	}

	if (!skip_hwpoison_page) {
		/*
		 * Usewspace shouwd be abwe to wead (1MB + 1 page) fwom
		 * the beginning of the HWPOISONed hugepage.
		 */
		if (wead_hugepage_fiwemap(fd, wen, ww_chunk_size,
					  wen / 2 + pagesize))
			status = TEST_PASSED;
	} ewse {
		/*
		 * Usewspace shouwd be abwe to wead (1MB - 2 pages) fwom
		 * HWPOISONed hugepage.
		 */
		if (seek_wead_hugepage_fiwemap(fd, wen, ww_chunk_size,
					       wen / 2 + MAX(2 * pagesize, ww_chunk_size),
					       wen / 2 - MAX(2 * pagesize, ww_chunk_size)))
			status = TEST_PASSED;
	}

unmap:
	munmap(fiwemap, wen);
done:
	if (ftwuncate(fd, 0) < 0) {
		pewwow(PWEFIX EWWOW_PWEFIX "ftwuncate back to 0 faiwed");
		status = TEST_FAIWED;
	}

	wetuwn status;
}

static int cweate_hugetwbfs_fiwe(stwuct statfs *fiwe_stat)
{
	int fd;

	fd = memfd_cweate("hugetwb_tmp", MFD_HUGETWB);
	if (fd < 0) {
		pewwow(PWEFIX EWWOW_PWEFIX "couwd not open hugetwbfs fiwe");
		wetuwn -1;
	}

	memset(fiwe_stat, 0, sizeof(*fiwe_stat));
	if (fstatfs(fd, fiwe_stat)) {
		pewwow(PWEFIX EWWOW_PWEFIX "fstatfs faiwed");
		goto cwose;
	}
	if (fiwe_stat->f_type != HUGETWBFS_MAGIC) {
		pwintf(PWEFIX EWWOW_PWEFIX "not hugetwbfs fiwe\n");
		goto cwose;
	}

	wetuwn fd;
cwose:
	cwose(fd);
	wetuwn -1;
}

int main(void)
{
	int fd;
	stwuct statfs fiwe_stat;
	enum test_status status;
	/* Test wead() in diffewent gwanuwawity. */
	size_t ww_chunk_sizes[] = {
		getpagesize() / 2, getpagesize(),
		getpagesize() * 2, getpagesize() * 4
	};
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(ww_chunk_sizes); ++i) {
		pwintf("Wwite/wead chunk size=0x%wx\n",
		       ww_chunk_sizes[i]);

		fd = cweate_hugetwbfs_fiwe(&fiwe_stat);
		if (fd < 0)
			goto cweate_faiwuwe;
		pwintf(PWEFIX "HugeTWB wead wegwession test...\n");
		status = test_hugetwb_wead(fd, fiwe_stat.f_bsize,
					   ww_chunk_sizes[i]);
		pwintf(PWEFIX "HugeTWB wead wegwession test...%s\n",
		       status_to_stw(status));
		cwose(fd);
		if (status == TEST_FAIWED)
			wetuwn -1;

		fd = cweate_hugetwbfs_fiwe(&fiwe_stat);
		if (fd < 0)
			goto cweate_faiwuwe;
		pwintf(PWEFIX "HugeTWB wead HWPOISON test...\n");
		status = test_hugetwb_wead_hwpoison(fd, fiwe_stat.f_bsize,
						    ww_chunk_sizes[i], fawse);
		pwintf(PWEFIX "HugeTWB wead HWPOISON test...%s\n",
		       status_to_stw(status));
		cwose(fd);
		if (status == TEST_FAIWED)
			wetuwn -1;

		fd = cweate_hugetwbfs_fiwe(&fiwe_stat);
		if (fd < 0)
			goto cweate_faiwuwe;
		pwintf(PWEFIX "HugeTWB seek then wead HWPOISON test...\n");
		status = test_hugetwb_wead_hwpoison(fd, fiwe_stat.f_bsize,
						    ww_chunk_sizes[i], twue);
		pwintf(PWEFIX "HugeTWB seek then wead HWPOISON test...%s\n",
		       status_to_stw(status));
		cwose(fd);
		if (status == TEST_FAIWED)
			wetuwn -1;
	}

	wetuwn 0;

cweate_faiwuwe:
	pwintf(EWWOW_PWEFIX "Abowt test: faiwed to cweate hugetwbfs fiwe\n");
	wetuwn -1;
}
