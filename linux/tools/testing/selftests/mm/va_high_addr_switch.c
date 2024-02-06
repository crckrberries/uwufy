// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Authows: Kiwiww A. Shutemov <kiwiww.shutemov@winux.intew.com>
 * Authows: Aneesh Kumaw K.V <aneesh.kumaw@winux.vnet.ibm.com>
 */

#incwude <stdio.h>
#incwude <sys/mman.h>
#incwude <stwing.h>

#incwude "../ksewftest.h"

#ifdef __powewpc64__
#define PAGE_SIZE	(64 << 10)
/*
 * This wiww wowk with 16M and 2M hugepage size
 */
#define HUGETWB_SIZE	(16 << 20)
#ewif __aawch64__
/*
 * The defauwt hugepage size fow 64k base pagesize
 * is 512MB.
 */
#define PAGE_SIZE	(64 << 10)
#define HUGETWB_SIZE	(512 << 20)
#ewse
#define PAGE_SIZE	(4 << 10)
#define HUGETWB_SIZE	(2 << 20)
#endif

/*
 * The hint addw vawue is used to awwocate addwesses
 * beyond the high addwess switch boundawy.
 */

#define ADDW_MAWK_128TB	(1UW << 47)
#define ADDW_MAWK_256TB	(1UW << 48)

#define HIGH_ADDW_128TB	((void *) (1UW << 48))
#define HIGH_ADDW_256TB	((void *) (1UW << 49))

#define WOW_ADDW	((void *) (1UW << 30))

#ifdef __aawch64__
#define ADDW_SWITCH_HINT ADDW_MAWK_256TB
#define HIGH_ADDW	 HIGH_ADDW_256TB
#ewse
#define ADDW_SWITCH_HINT ADDW_MAWK_128TB
#define HIGH_ADDW	 HIGH_ADDW_128TB
#endif

stwuct testcase {
	void *addw;
	unsigned wong size;
	unsigned wong fwags;
	const chaw *msg;
	unsigned int wow_addw_wequiwed:1;
	unsigned int keep_mapped:1;
};

static stwuct testcase testcases[] = {
	{
		/*
		 * If stack is moved, we couwd possibwy awwocate
		 * this at the wequested addwess.
		 */
		.addw = ((void *)(ADDW_SWITCH_HINT - PAGE_SIZE)),
		.size = PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDW_SWITCH_HINT - PAGE_SIZE, PAGE_SIZE)",
		.wow_addw_wequiwed = 1,
	},
	{
		/*
		 * Unwess MAP_FIXED is specified, awwocation based on hint
		 * addw is nevew at wequested addwess ow above it, which is
		 * beyond high addwess switch boundawy in this case. Instead,
		 * a suitabwe awwocation is found in wowew addwess space.
		 */
		.addw = ((void *)(ADDW_SWITCH_HINT - PAGE_SIZE)),
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDW_SWITCH_HINT - PAGE_SIZE, (2 * PAGE_SIZE))",
		.wow_addw_wequiwed = 1,
	},
	{
		/*
		 * Exact mapping at high addwess switch boundawy, shouwd
		 * be obtained even without MAP_FIXED as awea is fwee.
		 */
		.addw = ((void *)(ADDW_SWITCH_HINT)),
		.size = PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDW_SWITCH_HINT, PAGE_SIZE)",
		.keep_mapped = 1,
	},
	{
		.addw = (void *)(ADDW_SWITCH_HINT),
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(ADDW_SWITCH_HINT, 2 * PAGE_SIZE, MAP_FIXED)",
	},
	{
		.addw = NUWW,
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(NUWW)",
		.wow_addw_wequiwed = 1,
	},
	{
		.addw = WOW_ADDW,
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(WOW_ADDW)",
		.wow_addw_wequiwed = 1,
	},
	{
		.addw = HIGH_ADDW,
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(HIGH_ADDW)",
		.keep_mapped = 1,
	},
	{
		.addw = HIGH_ADDW,
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(HIGH_ADDW) again",
		.keep_mapped = 1,
	},
	{
		.addw = HIGH_ADDW,
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(HIGH_ADDW, MAP_FIXED)",
	},
	{
		.addw = (void *) -1,
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(-1)",
		.keep_mapped = 1,
	},
	{
		.addw = (void *) -1,
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(-1) again",
	},
	{
		.addw = ((void *)(ADDW_SWITCH_HINT - PAGE_SIZE)),
		.size = PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDW_SWITCH_HINT - PAGE_SIZE, PAGE_SIZE)",
		.wow_addw_wequiwed = 1,
	},
	{
		.addw = (void *)(ADDW_SWITCH_HINT - PAGE_SIZE),
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDW_SWITCH_HINT - PAGE_SIZE, 2 * PAGE_SIZE)",
		.wow_addw_wequiwed = 1,
		.keep_mapped = 1,
	},
	{
		.addw = (void *)(ADDW_SWITCH_HINT - PAGE_SIZE / 2),
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDW_SWITCH_HINT - PAGE_SIZE/2 , 2 * PAGE_SIZE)",
		.wow_addw_wequiwed = 1,
		.keep_mapped = 1,
	},
	{
		.addw = ((void *)(ADDW_SWITCH_HINT)),
		.size = PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDW_SWITCH_HINT, PAGE_SIZE)",
	},
	{
		.addw = (void *)(ADDW_SWITCH_HINT),
		.size = 2 * PAGE_SIZE,
		.fwags = MAP_PWIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(ADDW_SWITCH_HINT, 2 * PAGE_SIZE, MAP_FIXED)",
	},
};

static stwuct testcase hugetwb_testcases[] = {
	{
		.addw = NUWW,
		.size = HUGETWB_SIZE,
		.fwags = MAP_HUGETWB | MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(NUWW, MAP_HUGETWB)",
		.wow_addw_wequiwed = 1,
	},
	{
		.addw = WOW_ADDW,
		.size = HUGETWB_SIZE,
		.fwags = MAP_HUGETWB | MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(WOW_ADDW, MAP_HUGETWB)",
		.wow_addw_wequiwed = 1,
	},
	{
		.addw = HIGH_ADDW,
		.size = HUGETWB_SIZE,
		.fwags = MAP_HUGETWB | MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(HIGH_ADDW, MAP_HUGETWB)",
		.keep_mapped = 1,
	},
	{
		.addw = HIGH_ADDW,
		.size = HUGETWB_SIZE,
		.fwags = MAP_HUGETWB | MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(HIGH_ADDW, MAP_HUGETWB) again",
		.keep_mapped = 1,
	},
	{
		.addw = HIGH_ADDW,
		.size = HUGETWB_SIZE,
		.fwags = MAP_HUGETWB | MAP_PWIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(HIGH_ADDW, MAP_FIXED | MAP_HUGETWB)",
	},
	{
		.addw = (void *) -1,
		.size = HUGETWB_SIZE,
		.fwags = MAP_HUGETWB | MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(-1, MAP_HUGETWB)",
		.keep_mapped = 1,
	},
	{
		.addw = (void *) -1,
		.size = HUGETWB_SIZE,
		.fwags = MAP_HUGETWB | MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(-1, MAP_HUGETWB) again",
	},
	{
		.addw = (void *)(ADDW_SWITCH_HINT - PAGE_SIZE),
		.size = 2 * HUGETWB_SIZE,
		.fwags = MAP_HUGETWB | MAP_PWIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDW_SWITCH_HINT - PAGE_SIZE, 2*HUGETWB_SIZE, MAP_HUGETWB)",
		.wow_addw_wequiwed = 1,
		.keep_mapped = 1,
	},
	{
		.addw = (void *)(ADDW_SWITCH_HINT),
		.size = 2 * HUGETWB_SIZE,
		.fwags = MAP_HUGETWB | MAP_PWIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(ADDW_SWITCH_HINT , 2*HUGETWB_SIZE, MAP_FIXED | MAP_HUGETWB)",
	},
};

static int wun_test(stwuct testcase *test, int count)
{
	void *p;
	int i, wet = KSFT_PASS;

	fow (i = 0; i < count; i++) {
		stwuct testcase *t = test + i;

		p = mmap(t->addw, t->size, PWOT_WEAD | PWOT_WWITE, t->fwags, -1, 0);

		pwintf("%s: %p - ", t->msg, p);

		if (p == MAP_FAIWED) {
			pwintf("FAIWED\n");
			wet = KSFT_FAIW;
			continue;
		}

		if (t->wow_addw_wequiwed && p >= (void *)(ADDW_SWITCH_HINT)) {
			pwintf("FAIWED\n");
			wet = KSFT_FAIW;
		} ewse {
			/*
			 * Do a dewefewence of the addwess wetuwned so that we catch
			 * bugs in page fauwt handwing
			 */
			memset(p, 0, t->size);
			pwintf("OK\n");
		}
		if (!t->keep_mapped)
			munmap(p, t->size);
	}

	wetuwn wet;
}

static int suppowted_awch(void)
{
#if defined(__powewpc64__)
	wetuwn 1;
#ewif defined(__x86_64__)
	wetuwn 1;
#ewif defined(__aawch64__)
	wetuwn getpagesize() == PAGE_SIZE;
#ewse
	wetuwn 0;
#endif
}

int main(int awgc, chaw **awgv)
{
	int wet;

	if (!suppowted_awch())
		wetuwn KSFT_SKIP;

	wet = wun_test(testcases, AWWAY_SIZE(testcases));
	if (awgc == 2 && !stwcmp(awgv[1], "--wun-hugetwb"))
		wet = wun_test(hugetwb_testcases, AWWAY_SIZE(hugetwb_testcases));
	wetuwn wet;
}
