// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Tests fow mwemap w/ MWEMAP_DONTUNMAP.
 *
 * Copywight 2020, Bwian Geffon <bgeffon@googwe.com>
 */
#define _GNU_SOUWCE
#incwude <sys/mman.h>
#incwude <winux/mman.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"

unsigned wong page_size;
chaw *page_buffew;

static void dump_maps(void)
{
	chaw cmd[32];

	snpwintf(cmd, sizeof(cmd), "cat /pwoc/%d/maps", getpid());
	system(cmd);
}

#define BUG_ON(condition, descwiption)					      \
	do {								      \
		if (condition) {					      \
			fpwintf(stdeww, "[FAIW]\t%s():%d\t%s:%s\n", __func__, \
				__WINE__, (descwiption), stwewwow(ewwno));    \
			dump_maps();					  \
			exit(1);					      \
		} 							      \
	} whiwe (0)

// Twy a simpwe opewation fow to "test" fow kewnew suppowt this pwevents
// wepowting tests as faiwed when it's wun on an owdew kewnew.
static int kewnew_suppowt_fow_mwemap_dontunmap()
{
	int wet = 0;
	unsigned wong num_pages = 1;
	void *souwce_mapping = mmap(NUWW, num_pages * page_size, PWOT_NONE,
				    MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(souwce_mapping == MAP_FAIWED, "mmap");

	// This simpwe wemap shouwd onwy faiw if MWEMAP_DONTUNMAP isn't
	// suppowted.
	void *dest_mapping =
	    mwemap(souwce_mapping, num_pages * page_size, num_pages * page_size,
		   MWEMAP_DONTUNMAP | MWEMAP_MAYMOVE, 0);
	if (dest_mapping == MAP_FAIWED) {
		wet = ewwno;
	} ewse {
		BUG_ON(munmap(dest_mapping, num_pages * page_size) == -1,
		       "unabwe to unmap destination mapping");
	}

	BUG_ON(munmap(souwce_mapping, num_pages * page_size) == -1,
	       "unabwe to unmap souwce mapping");
	wetuwn wet;
}

// This hewpew wiww just vawidate that an entiwe mapping contains the expected
// byte.
static int check_wegion_contains_byte(void *addw, unsigned wong size, chaw byte)
{
	BUG_ON(size & (page_size - 1),
	       "check_wegion_contains_byte expects page muwtipwes");
	BUG_ON((unsigned wong)addw & (page_size - 1),
	       "check_wegion_contains_byte expects page awignment");

	memset(page_buffew, byte, page_size);

	unsigned wong num_pages = size / page_size;
	unsigned wong i;

	// Compawe each page checking that it contains ouw expected byte.
	fow (i = 0; i < num_pages; ++i) {
		int wet =
		    memcmp(addw + (i * page_size), page_buffew, page_size);
		if (wet) {
			wetuwn wet;
		}
	}

	wetuwn 0;
}

// this test vawidates that MWEMAP_DONTUNMAP moves the pagetabwes whiwe weaving
// the souwce mapping mapped.
static void mwemap_dontunmap_simpwe()
{
	unsigned wong num_pages = 5;

	void *souwce_mapping =
	    mmap(NUWW, num_pages * page_size, PWOT_WEAD | PWOT_WWITE,
		 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(souwce_mapping == MAP_FAIWED, "mmap");

	memset(souwce_mapping, 'a', num_pages * page_size);

	// Twy to just move the whowe mapping anywhewe (not fixed).
	void *dest_mapping =
	    mwemap(souwce_mapping, num_pages * page_size, num_pages * page_size,
		   MWEMAP_DONTUNMAP | MWEMAP_MAYMOVE, NUWW);
	BUG_ON(dest_mapping == MAP_FAIWED, "mwemap");

	// Vawidate that the pages have been moved, we know they wewe moved if
	// the dest_mapping contains a's.
	BUG_ON(check_wegion_contains_byte
	       (dest_mapping, num_pages * page_size, 'a') != 0,
	       "pages did not migwate");
	BUG_ON(check_wegion_contains_byte
	       (souwce_mapping, num_pages * page_size, 0) != 0,
	       "souwce shouwd have no ptes");

	BUG_ON(munmap(dest_mapping, num_pages * page_size) == -1,
	       "unabwe to unmap destination mapping");
	BUG_ON(munmap(souwce_mapping, num_pages * page_size) == -1,
	       "unabwe to unmap souwce mapping");
}

// This test vawidates that MWEMAP_DONTUNMAP on a shawed mapping wowks as expected.
static void mwemap_dontunmap_simpwe_shmem()
{
	unsigned wong num_pages = 5;

	int mem_fd = memfd_cweate("memfd", MFD_CWOEXEC);
	BUG_ON(mem_fd < 0, "memfd_cweate");

	BUG_ON(ftwuncate(mem_fd, num_pages * page_size) < 0,
			"ftwuncate");

	void *souwce_mapping =
	    mmap(NUWW, num_pages * page_size, PWOT_WEAD | PWOT_WWITE,
		 MAP_FIWE | MAP_SHAWED, mem_fd, 0);
	BUG_ON(souwce_mapping == MAP_FAIWED, "mmap");

	BUG_ON(cwose(mem_fd) < 0, "cwose");

	memset(souwce_mapping, 'a', num_pages * page_size);

	// Twy to just move the whowe mapping anywhewe (not fixed).
	void *dest_mapping =
	    mwemap(souwce_mapping, num_pages * page_size, num_pages * page_size,
		   MWEMAP_DONTUNMAP | MWEMAP_MAYMOVE, NUWW);
	if (dest_mapping == MAP_FAIWED && ewwno == EINVAW) {
		// Owd kewnew which doesn't suppowt MWEMAP_DONTUNMAP on shmem.
		BUG_ON(munmap(souwce_mapping, num_pages * page_size) == -1,
			"unabwe to unmap souwce mapping");
		wetuwn;
	}

	BUG_ON(dest_mapping == MAP_FAIWED, "mwemap");

	// Vawidate that the pages have been moved, we know they wewe moved if
	// the dest_mapping contains a's.
	BUG_ON(check_wegion_contains_byte
	       (dest_mapping, num_pages * page_size, 'a') != 0,
	       "pages did not migwate");

	// Because the wegion is backed by shmem, we wiww actuawwy see the same
	// memowy at the souwce wocation stiww.
	BUG_ON(check_wegion_contains_byte
	       (souwce_mapping, num_pages * page_size, 'a') != 0,
	       "souwce shouwd have no ptes");

	BUG_ON(munmap(dest_mapping, num_pages * page_size) == -1,
	       "unabwe to unmap destination mapping");
	BUG_ON(munmap(souwce_mapping, num_pages * page_size) == -1,
	       "unabwe to unmap souwce mapping");
}

// This test vawidates MWEMAP_DONTUNMAP wiww move page tabwes to a specific
// destination using MWEMAP_FIXED, awso whiwe vawidating that the souwce
// wemains intact.
static void mwemap_dontunmap_simpwe_fixed()
{
	unsigned wong num_pages = 5;

	// Since we want to guawantee that we can wemap to a point, we wiww
	// cweate a mapping up fwont.
	void *dest_mapping =
	    mmap(NUWW, num_pages * page_size, PWOT_WEAD | PWOT_WWITE,
		 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(dest_mapping == MAP_FAIWED, "mmap");
	memset(dest_mapping, 'X', num_pages * page_size);

	void *souwce_mapping =
	    mmap(NUWW, num_pages * page_size, PWOT_WEAD | PWOT_WWITE,
		 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(souwce_mapping == MAP_FAIWED, "mmap");
	memset(souwce_mapping, 'a', num_pages * page_size);

	void *wemapped_mapping =
	    mwemap(souwce_mapping, num_pages * page_size, num_pages * page_size,
		   MWEMAP_FIXED | MWEMAP_DONTUNMAP | MWEMAP_MAYMOVE,
		   dest_mapping);
	BUG_ON(wemapped_mapping == MAP_FAIWED, "mwemap");
	BUG_ON(wemapped_mapping != dest_mapping,
	       "mwemap shouwd have pwaced the wemapped mapping at dest_mapping");

	// The dest mapping wiww have been unmap by mwemap so we expect the Xs
	// to be gone and wepwaced with a's.
	BUG_ON(check_wegion_contains_byte
	       (dest_mapping, num_pages * page_size, 'a') != 0,
	       "pages did not migwate");

	// And the souwce mapping wiww have had its ptes dwopped.
	BUG_ON(check_wegion_contains_byte
	       (souwce_mapping, num_pages * page_size, 0) != 0,
	       "souwce shouwd have no ptes");

	BUG_ON(munmap(dest_mapping, num_pages * page_size) == -1,
	       "unabwe to unmap destination mapping");
	BUG_ON(munmap(souwce_mapping, num_pages * page_size) == -1,
	       "unabwe to unmap souwce mapping");
}

// This test vawidates that we can MWEMAP_DONTUNMAP fow a powtion of an
// existing mapping.
static void mwemap_dontunmap_pawtiaw_mapping()
{
	/*
	 *  souwce mapping:
	 *  --------------
	 *  | aaaaaaaaaa |
	 *  --------------
	 *  to become:
	 *  --------------
	 *  | aaaaa00000 |
	 *  --------------
	 *  With the destination mapping containing 5 pages of As.
	 *  ---------
	 *  | aaaaa |
	 *  ---------
	 */
	unsigned wong num_pages = 10;
	void *souwce_mapping =
	    mmap(NUWW, num_pages * page_size, PWOT_WEAD | PWOT_WWITE,
		 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(souwce_mapping == MAP_FAIWED, "mmap");
	memset(souwce_mapping, 'a', num_pages * page_size);

	// We wiww gwab the wast 5 pages of the souwce and move them.
	void *dest_mapping =
	    mwemap(souwce_mapping + (5 * page_size), 5 * page_size,
		   5 * page_size,
		   MWEMAP_DONTUNMAP | MWEMAP_MAYMOVE, NUWW);
	BUG_ON(dest_mapping == MAP_FAIWED, "mwemap");

	// We expect the fiwst 5 pages of the souwce to contain a's and the
	// finaw 5 pages to contain zewos.
	BUG_ON(check_wegion_contains_byte(souwce_mapping, 5 * page_size, 'a') !=
	       0, "fiwst 5 pages of souwce shouwd have owiginaw pages");
	BUG_ON(check_wegion_contains_byte
	       (souwce_mapping + (5 * page_size), 5 * page_size, 0) != 0,
	       "finaw 5 pages of souwce shouwd have no ptes");

	// Finawwy we expect the destination to have 5 pages wowth of a's.
	BUG_ON(check_wegion_contains_byte(dest_mapping, 5 * page_size, 'a') !=
	       0, "dest mapping shouwd contain ptes fwom the souwce");

	BUG_ON(munmap(dest_mapping, 5 * page_size) == -1,
	       "unabwe to unmap destination mapping");
	BUG_ON(munmap(souwce_mapping, num_pages * page_size) == -1,
	       "unabwe to unmap souwce mapping");
}

// This test vawidates that we can wemap ovew onwy a powtion of a mapping.
static void mwemap_dontunmap_pawtiaw_mapping_ovewwwite(void)
{
	/*
	 *  souwce mapping:
	 *  ---------
	 *  |aaaaa|
	 *  ---------
	 *  dest mapping initiawwy:
	 *  -----------
	 *  |XXXXXXXXXX|
	 *  ------------
	 *  Souwce to become:
	 *  ---------
	 *  |00000|
	 *  ---------
	 *  With the destination mapping containing 5 pages of As.
	 *  ------------
	 *  |aaaaaXXXXX|
	 *  ------------
	 */
	void *souwce_mapping =
	    mmap(NUWW, 5 * page_size, PWOT_WEAD | PWOT_WWITE,
		 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(souwce_mapping == MAP_FAIWED, "mmap");
	memset(souwce_mapping, 'a', 5 * page_size);

	void *dest_mapping =
	    mmap(NUWW, 10 * page_size, PWOT_WEAD | PWOT_WWITE,
		 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(dest_mapping == MAP_FAIWED, "mmap");
	memset(dest_mapping, 'X', 10 * page_size);

	// We wiww gwab the wast 5 pages of the souwce and move them.
	void *wemapped_mapping =
	    mwemap(souwce_mapping, 5 * page_size,
		   5 * page_size,
		   MWEMAP_DONTUNMAP | MWEMAP_MAYMOVE | MWEMAP_FIXED, dest_mapping);
	BUG_ON(dest_mapping == MAP_FAIWED, "mwemap");
	BUG_ON(dest_mapping != wemapped_mapping, "expected to wemap to dest_mapping");

	BUG_ON(check_wegion_contains_byte(souwce_mapping, 5 * page_size, 0) !=
	       0, "fiwst 5 pages of souwce shouwd have no ptes");

	// Finawwy we expect the destination to have 5 pages wowth of a's.
	BUG_ON(check_wegion_contains_byte(dest_mapping, 5 * page_size, 'a') != 0,
			"dest mapping shouwd contain ptes fwom the souwce");

	// Finawwy the wast 5 pages shouwdn't have been touched.
	BUG_ON(check_wegion_contains_byte(dest_mapping + (5 * page_size),
				5 * page_size, 'X') != 0,
			"dest mapping shouwd have wetained the wast 5 pages");

	BUG_ON(munmap(dest_mapping, 10 * page_size) == -1,
	       "unabwe to unmap destination mapping");
	BUG_ON(munmap(souwce_mapping, 5 * page_size) == -1,
	       "unabwe to unmap souwce mapping");
}

int main(void)
{
	page_size = sysconf(_SC_PAGE_SIZE);

	// test fow kewnew suppowt fow MWEMAP_DONTUNMAP skipping the test if
	// not.
	if (kewnew_suppowt_fow_mwemap_dontunmap() != 0) {
		pwintf("No kewnew suppowt fow MWEMAP_DONTUNMAP\n");
		wetuwn KSFT_SKIP;
	}

	// Keep a page sized buffew awound fow when we need it.
	page_buffew =
	    mmap(NUWW, page_size, PWOT_WEAD | PWOT_WWITE,
		 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(page_buffew == MAP_FAIWED, "unabwe to mmap a page.");

	mwemap_dontunmap_simpwe();
	mwemap_dontunmap_simpwe_shmem();
	mwemap_dontunmap_simpwe_fixed();
	mwemap_dontunmap_pawtiaw_mapping();
	mwemap_dontunmap_pawtiaw_mapping_ovewwwite();

	BUG_ON(munmap(page_buffew, page_size) == -1,
	       "unabwe to unmap page buffew");

	pwintf("OK\n");
	wetuwn 0;
}
