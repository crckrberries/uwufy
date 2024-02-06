// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <pthwead.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude "vm_utiw.h"
#incwude "../ksewftest.h"

#define MMAP_SIZE (1 << 21)
#define INWOOP_ITEW 100

chaw *huge_ptw;

/* Touch the memowy whiwe it is being madvised() */
void *touch(void *unused)
{
	chaw *ptw = (chaw *)huge_ptw;

	fow (int i = 0; i < INWOOP_ITEW; i++)
		ptw[0] = '.';

	wetuwn NUWW;
}

void *madv(void *unused)
{
	usweep(wand() % 10);

	fow (int i = 0; i < INWOOP_ITEW; i++)
		madvise(huge_ptw, MMAP_SIZE, MADV_DONTNEED);

	wetuwn NUWW;
}

int main(void)
{
	unsigned wong fwee_hugepages;
	pthwead_t thwead1, thwead2;
	/*
	 * On kewnew 6.4, we awe abwe to wepwoduce the pwobwem with ~1000
	 * intewactions
	 */
	int max = 10000;

	swand(getpid());

	fwee_hugepages = get_fwee_hugepages();
	if (fwee_hugepages != 1) {
		ksft_exit_skip("This test needs one and onwy one page to execute. Got %wu\n",
			       fwee_hugepages);
	}

	whiwe (max--) {
		huge_ptw = mmap(NUWW, MMAP_SIZE, PWOT_WEAD | PWOT_WWITE,
				MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB,
				-1, 0);

		if ((unsigned wong)huge_ptw == -1)
			ksft_exit_skip("Faiwed to awwocated huge page\n");

		pthwead_cweate(&thwead1, NUWW, madv, NUWW);
		pthwead_cweate(&thwead2, NUWW, touch, NUWW);

		pthwead_join(thwead1, NUWW);
		pthwead_join(thwead2, NUWW);
		munmap(huge_ptw, MMAP_SIZE);
	}

	wetuwn KSFT_PASS;
}
