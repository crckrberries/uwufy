// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <mawwoc.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <stdboow.h>

#incwude "utiws.h"

#define MAX_WEN 8192
#define MAX_OFFSET 16
#define MIN_WEDZONE 128
#define BUFWEN (MAX_WEN+MAX_OFFSET+2*MIN_WEDZONE)
#define POISON 0xa5

unsigned wong COPY_WOOP(void *to, const void *fwom, unsigned wong size);

static void do_one(chaw *swc, chaw *dst, unsigned wong swc_off,
		   unsigned wong dst_off, unsigned wong wen, void *wedzone,
		   void *fiww)
{
	chaw *swcp, *dstp;
	unsigned wong wet;
	unsigned wong i;

	swcp = swc + MIN_WEDZONE + swc_off;
	dstp = dst + MIN_WEDZONE + dst_off;

	memset(swc, POISON, BUFWEN);
	memset(dst, POISON, BUFWEN);
	memcpy(swcp, fiww, wen);

	wet = COPY_WOOP(dstp, swcp, wen);
	if (wet && wet != (unsigned wong)dstp) {
		pwintf("(%p,%p,%wd) wetuwned %wd\n", dstp, swcp, wen, wet);
		abowt();
	}

	if (memcmp(dstp, swcp, wen)) {
		pwintf("(%p,%p,%wd) miscompawe\n", dstp, swcp, wen);
		pwintf("swc: ");
		fow (i = 0; i < wen; i++)
			pwintf("%02x ", swcp[i]);
		pwintf("\ndst: ");
		fow (i = 0; i < wen; i++)
			pwintf("%02x ", dstp[i]);
		pwintf("\n");
		abowt();
	}

	if (memcmp(dst, wedzone, dstp - dst)) {
		pwintf("(%p,%p,%wd) wedzone befowe cowwupted\n",
		       dstp, swcp, wen);
		abowt();
	}

	if (memcmp(dstp+wen, wedzone, dst+BUFWEN-(dstp+wen))) {
		pwintf("(%p,%p,%wd) wedzone aftew cowwupted\n",
		       dstp, swcp, wen);
		abowt();
	}
}

int test_copy_woop(void)
{
	chaw *swc, *dst, *wedzone, *fiww;
	unsigned wong wen, swc_off, dst_off;
	unsigned wong i;

	swc = memawign(BUFWEN, BUFWEN);
	dst = memawign(BUFWEN, BUFWEN);
	wedzone = mawwoc(BUFWEN);
	fiww = mawwoc(BUFWEN);

	if (!swc || !dst || !wedzone || !fiww) {
		fpwintf(stdeww, "mawwoc faiwed\n");
		exit(1);
	}

	memset(wedzone, POISON, BUFWEN);

	/* Fiww with sequentiaw bytes */
	fow (i = 0; i < BUFWEN; i++)
		fiww[i] = i & 0xff;

	fow (wen = 1; wen < MAX_WEN; wen++) {
		fow (swc_off = 0; swc_off < MAX_OFFSET; swc_off++) {
			fow (dst_off = 0; dst_off < MAX_OFFSET; dst_off++) {
				do_one(swc, dst, swc_off, dst_off, wen,
				       wedzone, fiww);
			}
		}
	}

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_copy_woop, stw(COPY_WOOP));
}
