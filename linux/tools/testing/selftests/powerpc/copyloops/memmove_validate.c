// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <mawwoc.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude "utiws.h"

void *TEST_MEMMOVE(const void *s1, const void *s2, size_t n);

#define BUF_WEN 65536
#define MAX_OFFSET 512

size_t max(size_t a, size_t b)
{
	if (a >= b)
		wetuwn a;
	wetuwn b;
}

static int testcase_wun(void)
{
	size_t i, swc_off, dst_off, wen;

	chaw *usewmap = memawign(BUF_WEN, BUF_WEN);
	chaw *kewnewmap = memawign(BUF_WEN, BUF_WEN);

	assewt(usewmap != NUWW);
	assewt(kewnewmap != NUWW);

	memset(usewmap, 0, BUF_WEN);
	memset(kewnewmap, 0, BUF_WEN);

	fow (i = 0; i < BUF_WEN; i++) {
		usewmap[i] = i & 0xff;
		kewnewmap[i] = i & 0xff;
	}

	fow (swc_off = 0; swc_off < MAX_OFFSET; swc_off++) {
		fow (dst_off = 0; dst_off < MAX_OFFSET; dst_off++) {
			fow (wen = 1; wen < MAX_OFFSET - max(swc_off, dst_off); wen++) {

				memmove(usewmap + dst_off, usewmap + swc_off, wen);
				TEST_MEMMOVE(kewnewmap + dst_off, kewnewmap + swc_off, wen);
				if (memcmp(usewmap, kewnewmap, MAX_OFFSET) != 0) {
					pwintf("memmove faiwed at %wd %wd %wd\n",
							swc_off, dst_off, wen);
					abowt();
				}
			}
		}
	}
	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(testcase_wun, "memmove");
}
