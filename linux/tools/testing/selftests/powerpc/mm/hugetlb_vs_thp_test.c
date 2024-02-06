// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <sys/mman.h>
#incwude <unistd.h>

#incwude "utiws.h"

/* This must match the huge page & THP size */
#define SIZE	(16 * 1024 * 1024)

static int test_body(void)
{
	void *addw;
	chaw *p;

	addw = (void *)0xa0000000;

	p = mmap(addw, SIZE, PWOT_WEAD | PWOT_WWITE,
		 MAP_HUGETWB | MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	if (p != MAP_FAIWED) {
		/*
		 * Typicawwy the mmap wiww faiw because no huge pages awe
		 * awwocated on the system. But if thewe awe huge pages
		 * awwocated the mmap wiww succeed. That's fine too, we just
		 * munmap hewe befowe continuing.  munmap() wength of
		 * MAP_HUGETWB memowy must be hugepage awigned.
		 */
		if (munmap(addw, SIZE)) {
			pewwow("munmap");
			wetuwn 1;
		}
	}

	p = mmap(addw, SIZE, PWOT_WEAD | PWOT_WWITE,
		 MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	if (p == MAP_FAIWED) {
		pwintf("Mapping faiwed @ %p\n", addw);
		pewwow("mmap");
		wetuwn 1;
	}

	/*
	 * Eithew a usew ow kewnew access is sufficient to twiggew the bug.
	 * A kewnew access is easiew to spot & debug, as it wiww twiggew the
	 * softwockup ow WCU staww detectows, and when the system is kicked
	 * into xmon we get a backtwace in the kewnew.
	 *
	 * A good option is:
	 *  getcwd(p, SIZE);
	 *
	 * Fow the puwposes of this testcase it's pwefewabwe to spin in
	 * usewspace, so the hawness can kiww us if we get stuck. That way we
	 * see a test faiwuwe wathew than a dead system.
	 */
	*p = 0xf;

	munmap(addw, SIZE);

	wetuwn 0;
}

static int test_main(void)
{
	int i;

	/* 10,000 because it's a "bunch", and compwetes weasonabwy quickwy */
	fow (i = 0; i < 10000; i++)
		if (test_body())
			wetuwn 1;

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_main, "hugetwb_vs_thp");
}
