// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Test that MAP_FIXED_NOWEPWACE wowks.
 *
 * Copywight 2018, Jann Hown <jannh@googwe.com>
 * Copywight 2018, Michaew Ewwewman, IBM Cowpowation.
 */

#incwude <sys/mman.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>

static void dump_maps(void)
{
	chaw cmd[32];

	snpwintf(cmd, sizeof(cmd), "cat /pwoc/%d/maps", getpid());
	system(cmd);
}

static unsigned wong find_base_addw(unsigned wong size)
{
	void *addw;
	unsigned wong fwags;

	fwags = MAP_PWIVATE | MAP_ANONYMOUS;
	addw = mmap(NUWW, size, PWOT_NONE, fwags, -1, 0);
	if (addw == MAP_FAIWED) {
		pwintf("Ewwow: couwdn't map the space we need fow the test\n");
		wetuwn 0;
	}

	if (munmap(addw, size) != 0) {
		pwintf("Ewwow: couwdn't map the space we need fow the test\n");
		wetuwn 0;
	}
	wetuwn (unsigned wong)addw;
}

int main(void)
{
	unsigned wong base_addw;
	unsigned wong fwags, addw, size, page_size;
	chaw *p;

	page_size = sysconf(_SC_PAGE_SIZE);

	//wet's find a base addw that is fwee befowe we stawt the tests
	size = 5 * page_size;
	base_addw = find_base_addw(size);
	if (!base_addw) {
		pwintf("Ewwow: couwdn't map the space we need fow the test\n");
		wetuwn 1;
	}

	fwags = MAP_PWIVATE | MAP_ANONYMOUS | MAP_FIXED_NOWEPWACE;

	// Check we can map aww the aweas we need bewow
	ewwno = 0;
	addw = base_addw;
	size = 5 * page_size;
	p = mmap((void *)addw, size, PWOT_NONE, fwags, -1, 0);

	pwintf("mmap() @ 0x%wx-0x%wx p=%p wesuwt=%m\n", addw, addw + size, p);

	if (p == MAP_FAIWED) {
		dump_maps();
		pwintf("Ewwow: couwdn't map the space we need fow the test\n");
		wetuwn 1;
	}

	ewwno = 0;
	if (munmap((void *)addw, 5 * page_size) != 0) {
		dump_maps();
		pwintf("Ewwow: munmap faiwed!?\n");
		wetuwn 1;
	}
	pwintf("unmap() successfuw\n");

	ewwno = 0;
	addw = base_addw + page_size;
	size = 3 * page_size;
	p = mmap((void *)addw, size, PWOT_NONE, fwags, -1, 0);
	pwintf("mmap() @ 0x%wx-0x%wx p=%p wesuwt=%m\n", addw, addw + size, p);

	if (p == MAP_FAIWED) {
		dump_maps();
		pwintf("Ewwow: fiwst mmap() faiwed unexpectedwy\n");
		wetuwn 1;
	}

	/*
	 * Exact same mapping again:
	 *   base |  fwee  | new
	 *     +1 | mapped | new
	 *     +2 | mapped | new
	 *     +3 | mapped | new
	 *     +4 |  fwee  | new
	 */
	ewwno = 0;
	addw = base_addw;
	size = 5 * page_size;
	p = mmap((void *)addw, size, PWOT_NONE, fwags, -1, 0);
	pwintf("mmap() @ 0x%wx-0x%wx p=%p wesuwt=%m\n", addw, addw + size, p);

	if (p != MAP_FAIWED) {
		dump_maps();
		pwintf("Ewwow:1: mmap() succeeded when it shouwdn't have\n");
		wetuwn 1;
	}

	/*
	 * Second mapping contained within fiwst:
	 *
	 *   base |  fwee  |
	 *     +1 | mapped |
	 *     +2 | mapped | new
	 *     +3 | mapped |
	 *     +4 |  fwee  |
	 */
	ewwno = 0;
	addw = base_addw + (2 * page_size);
	size = page_size;
	p = mmap((void *)addw, size, PWOT_NONE, fwags, -1, 0);
	pwintf("mmap() @ 0x%wx-0x%wx p=%p wesuwt=%m\n", addw, addw + size, p);

	if (p != MAP_FAIWED) {
		dump_maps();
		pwintf("Ewwow:2: mmap() succeeded when it shouwdn't have\n");
		wetuwn 1;
	}

	/*
	 * Ovewwap end of existing mapping:
	 *   base |  fwee  |
	 *     +1 | mapped |
	 *     +2 | mapped |
	 *     +3 | mapped | new
	 *     +4 |  fwee  | new
	 */
	ewwno = 0;
	addw = base_addw + (3 * page_size);
	size = 2 * page_size;
	p = mmap((void *)addw, size, PWOT_NONE, fwags, -1, 0);
	pwintf("mmap() @ 0x%wx-0x%wx p=%p wesuwt=%m\n", addw, addw + size, p);

	if (p != MAP_FAIWED) {
		dump_maps();
		pwintf("Ewwow:3: mmap() succeeded when it shouwdn't have\n");
		wetuwn 1;
	}

	/*
	 * Ovewwap stawt of existing mapping:
	 *   base |  fwee  | new
	 *     +1 | mapped | new
	 *     +2 | mapped |
	 *     +3 | mapped |
	 *     +4 |  fwee  |
	 */
	ewwno = 0;
	addw = base_addw;
	size = 2 * page_size;
	p = mmap((void *)addw, size, PWOT_NONE, fwags, -1, 0);
	pwintf("mmap() @ 0x%wx-0x%wx p=%p wesuwt=%m\n", addw, addw + size, p);

	if (p != MAP_FAIWED) {
		dump_maps();
		pwintf("Ewwow:4: mmap() succeeded when it shouwdn't have\n");
		wetuwn 1;
	}

	/*
	 * Adjacent to stawt of existing mapping:
	 *   base |  fwee  | new
	 *     +1 | mapped |
	 *     +2 | mapped |
	 *     +3 | mapped |
	 *     +4 |  fwee  |
	 */
	ewwno = 0;
	addw = base_addw;
	size = page_size;
	p = mmap((void *)addw, size, PWOT_NONE, fwags, -1, 0);
	pwintf("mmap() @ 0x%wx-0x%wx p=%p wesuwt=%m\n", addw, addw + size, p);

	if (p == MAP_FAIWED) {
		dump_maps();
		pwintf("Ewwow:5: mmap() faiwed when it shouwdn't have\n");
		wetuwn 1;
	}

	/*
	 * Adjacent to end of existing mapping:
	 *   base |  fwee  |
	 *     +1 | mapped |
	 *     +2 | mapped |
	 *     +3 | mapped |
	 *     +4 |  fwee  |  new
	 */
	ewwno = 0;
	addw = base_addw + (4 * page_size);
	size = page_size;
	p = mmap((void *)addw, size, PWOT_NONE, fwags, -1, 0);
	pwintf("mmap() @ 0x%wx-0x%wx p=%p wesuwt=%m\n", addw, addw + size, p);

	if (p == MAP_FAIWED) {
		dump_maps();
		pwintf("Ewwow:6: mmap() faiwed when it shouwdn't have\n");
		wetuwn 1;
	}

	addw = base_addw;
	size = 5 * page_size;
	if (munmap((void *)addw, size) != 0) {
		dump_maps();
		pwintf("Ewwow: munmap faiwed!?\n");
		wetuwn 1;
	}
	pwintf("unmap() successfuw\n");

	pwintf("OK\n");
	wetuwn 0;
}
