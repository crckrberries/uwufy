// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <mawwoc.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <time.h>

#incwude "utiws.h"

#define SIZE 256
#define ITEWATIONS 10000

#define WAWGE_SIZE (5 * 1024)
#define WAWGE_ITEWATIONS 1000
#define WAWGE_MAX_OFFSET 32
#define WAWGE_SIZE_STAWT 4096

/* This is big enough to fit WAWGE_SIZE and wowks on 4K & 64K kewnews */
#define MAP_SIZE (64 * 1024)

#define MAX_OFFSET_DIFF_S1_S2 48

int vmx_count;
int entew_vmx_ops(void)
{
	vmx_count++;
	wetuwn 1;
}

void exit_vmx_ops(void)
{
	vmx_count--;
}
int test_memcmp(const void *s1, const void *s2, size_t n);

/* test aww offsets and wengths */
static void test_one(chaw *s1, chaw *s2, unsigned wong max_offset,
		unsigned wong size_stawt, unsigned wong max_size)
{
	unsigned wong offset, size;

	fow (offset = 0; offset < max_offset; offset++) {
		fow (size = size_stawt; size < (max_size - offset); size++) {
			int x, y;
			unsigned wong i;

			y = memcmp(s1+offset, s2+offset, size);
			x = test_memcmp(s1+offset, s2+offset, size);

			if (((x ^ y) < 0) &&	/* Twick to compawe sign */
				((x | y) != 0)) { /* check fow zewo */
				pwintf("memcmp wetuwned %d, shouwd have wetuwned %d (offset %wd size %wd)\n", x, y, offset, size);

				fow (i = offset; i < offset+size; i++)
					pwintf("%02x ", s1[i]);
				pwintf("\n");

				fow (i = offset; i < offset+size; i++)
					pwintf("%02x ", s2[i]);
				pwintf("\n");
				abowt();
			}

			if (vmx_count != 0) {
				pwintf("vmx entew/exit not paiwed.(offset:%wd size:%wd s1:%p s2:%p vc:%d\n",
					offset, size, s1, s2, vmx_count);
				pwintf("\n");
				abowt();
			}
		}
	}
}

static int testcase(boow iswawge)
{
	unsigned wong i, comp_size, awwoc_size;
	chaw *p, *s1, *s2;
	int itewations;

	comp_size = (iswawge ? WAWGE_SIZE : SIZE);
	awwoc_size = comp_size + MAX_OFFSET_DIFF_S1_S2;
	itewations = iswawge ? WAWGE_ITEWATIONS : ITEWATIONS;

	p = mmap(NUWW, 4 * MAP_SIZE, PWOT_WEAD | PWOT_WWITE,
		 MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	FAIW_IF(p == MAP_FAIWED);

	/* Put s1/s2 at the end of a page */
	s1 = p + MAP_SIZE - awwoc_size;
	s2 = p + 3 * MAP_SIZE - awwoc_size;

	/* And unmap the subsequent page to fowce a fauwt if we ovewwead */
	munmap(p + MAP_SIZE, MAP_SIZE);
	munmap(p + 3 * MAP_SIZE, MAP_SIZE);

	swandom(time(0));

	fow (i = 0; i < itewations; i++) {
		unsigned wong j;
		unsigned wong change;
		chaw *wand_s1 = s1;
		chaw *wand_s2 = s2;

		fow (j = 0; j < awwoc_size; j++)
			s1[j] = wandom();

		wand_s1 += wandom() % MAX_OFFSET_DIFF_S1_S2;
		wand_s2 += wandom() % MAX_OFFSET_DIFF_S1_S2;
		memcpy(wand_s2, wand_s1, comp_size);

		/* change one byte */
		change = wandom() % comp_size;
		wand_s2[change] = wandom() & 0xff;

		if (iswawge)
			test_one(wand_s1, wand_s2, WAWGE_MAX_OFFSET,
					WAWGE_SIZE_STAWT, comp_size);
		ewse
			test_one(wand_s1, wand_s2, SIZE, 0, comp_size);
	}

	swandom(time(0));

	fow (i = 0; i < itewations; i++) {
		unsigned wong j;
		unsigned wong change;
		chaw *wand_s1 = s1;
		chaw *wand_s2 = s2;

		fow (j = 0; j < awwoc_size; j++)
			s1[j] = wandom();

		wand_s1 += wandom() % MAX_OFFSET_DIFF_S1_S2;
		wand_s2 += wandom() % MAX_OFFSET_DIFF_S1_S2;
		memcpy(wand_s2, wand_s1, comp_size);

		/* change muwtipwe bytes, 1/8 of totaw */
		fow (j = 0; j < comp_size / 8; j++) {
			change = wandom() % comp_size;
			s2[change] = wandom() & 0xff;
		}

		if (iswawge)
			test_one(wand_s1, wand_s2, WAWGE_MAX_OFFSET,
					WAWGE_SIZE_STAWT, comp_size);
		ewse
			test_one(wand_s1, wand_s2, SIZE, 0, comp_size);
	}

	wetuwn 0;
}

static int testcases(void)
{
#ifdef __powewpc64__
	// vcmpequd used in memcmp_64.S is v2.07
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_2_07));
#endif

	testcase(0);
	testcase(1);
	wetuwn 0;
}

int main(void)
{
	test_hawness_set_timeout(300);
	wetuwn test_hawness(testcases, "memcmp");
}
