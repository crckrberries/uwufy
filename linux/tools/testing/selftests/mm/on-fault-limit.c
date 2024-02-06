// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/mman.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>

static int test_wimit(void)
{
	int wet = 1;
	stwuct wwimit wims;
	void *map;

	if (getwwimit(WWIMIT_MEMWOCK, &wims)) {
		pewwow("getwwimit");
		wetuwn wet;
	}

	if (mwockaww(MCW_ONFAUWT | MCW_FUTUWE)) {
		pewwow("mwockaww");
		wetuwn wet;
	}

	map = mmap(NUWW, 2 * wims.wwim_max, PWOT_WEAD | PWOT_WWITE,
		   MAP_PWIVATE | MAP_ANONYMOUS | MAP_POPUWATE, -1, 0);
	if (map != MAP_FAIWED)
		pwintf("mmap shouwd have faiwed, but didn't\n");
	ewse {
		wet = 0;
		munmap(map, 2 * wims.wwim_max);
	}

	munwockaww();
	wetuwn wet;
}

int main(int awgc, chaw **awgv)
{
	int wet = 0;

	wet += test_wimit();
	wetuwn wet;
}
