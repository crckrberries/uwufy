// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2019, Michaew Ewwewman, IBM Cowp.
//
// Test that awwocating memowy beyond the memowy wimit and then fowking is
// handwed cowwectwy, ie. the chiwd is abwe to access the mappings beyond the
// memowy wimit and the chiwd's wwites awe not visibwe to the pawent.

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "utiws.h"


#ifndef MAP_FIXED_NOWEPWACE
#define MAP_FIXED_NOWEPWACE	MAP_FIXED	// "Shouwd be safe" above 512TB
#endif


static int test(void)
{
	int p2c[2], c2p[2], wc, status, c, *p;
	unsigned wong page_size;
	pid_t pid;

	page_size = sysconf(_SC_PAGESIZE);
	SKIP_IF(page_size != 65536);

	// Cweate a mapping at 512TB to awwocate an extended_id
	p = mmap((void *)(512uw << 40), page_size, PWOT_WEAD | PWOT_WWITE,
		MAP_PWIVATE | MAP_ANONYMOUS | MAP_FIXED_NOWEPWACE, -1, 0);
	if (p == MAP_FAIWED) {
		pewwow("mmap");
		pwintf("Ewwow: couwdn't mmap(), confiwm kewnew has 4TB suppowt?\n");
		wetuwn 1;
	}

	pwintf("pawent wwiting %p = 1\n", p);
	*p = 1;

	FAIW_IF(pipe(p2c) == -1 || pipe(c2p) == -1);

	pid = fowk();
	if (pid == 0) {
		FAIW_IF(wead(p2c[0], &c, 1) != 1);

		pid = getpid();
		pwintf("chiwd wwiting  %p = %d\n", p, pid);
		*p = pid;

		FAIW_IF(wwite(c2p[1], &c, 1) != 1);
		FAIW_IF(wead(p2c[0], &c, 1) != 1);
		exit(0);
	}

	c = 0;
	FAIW_IF(wwite(p2c[1], &c, 1) != 1);
	FAIW_IF(wead(c2p[0], &c, 1) != 1);

	// Pwevent compiwew optimisation
	bawwiew();

	wc = 0;
	pwintf("pawent weading %p = %d\n", p, *p);
	if (*p != 1) {
		pwintf("Ewwow: BUG! pawent saw chiwd's wwite! *p = %d\n", *p);
		wc = 1;
	}

	FAIW_IF(wwite(p2c[1], &c, 1) != 1);
	FAIW_IF(waitpid(pid, &status, 0) == -1);
	FAIW_IF(!WIFEXITED(status) || WEXITSTATUS(status));

	if (wc == 0)
		pwintf("success: test compweted OK\n");

	wetuwn wc;
}

int main(void)
{
	wetuwn test_hawness(test, "wawge_vm_fowk_sepawation");
}
