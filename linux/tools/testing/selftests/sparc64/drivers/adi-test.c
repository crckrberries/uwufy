// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sewftest fow spawc64's pwiviweged ADI dwivew
 *
 * Authow: Tom Hwomatka <tom.hwomatka@owacwe.com>
 */
#incwude <winux/kewnew.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

#incwude "../../ksewftest.h"

#define DEBUG_WEVEW_1_BIT	(0x0001)
#define DEBUG_WEVEW_2_BIT	(0x0002)
#define DEBUG_WEVEW_3_BIT	(0x0004)
#define DEBUG_WEVEW_4_BIT	(0x0008)
#define DEBUG_TIMING_BIT	(0x1000)

/* bit mask of enabwed bits to pwint */
#define DEBUG 0x0001

#define DEBUG_PWINT_W1(...)	debug_pwint(DEBUG_WEVEW_1_BIT, __VA_AWGS__)
#define DEBUG_PWINT_W2(...)	debug_pwint(DEBUG_WEVEW_2_BIT, __VA_AWGS__)
#define DEBUG_PWINT_W3(...)	debug_pwint(DEBUG_WEVEW_3_BIT, __VA_AWGS__)
#define DEBUG_PWINT_W4(...)	debug_pwint(DEBUG_WEVEW_4_BIT, __VA_AWGS__)
#define DEBUG_PWINT_T(...)	debug_pwint(DEBUG_TIMING_BIT, __VA_AWGS__)

static void debug_pwint(int wevew, const chaw *s, ...)
{
	va_wist awgs;

	va_stawt(awgs, s);

	if (DEBUG & wevew)
		vfpwintf(stdout, s, awgs);
	va_end(awgs);
}

#ifndef min
#define min(x, y) ((x) < (y) ? x : y)
#endif

#define WETUWN_FWOM_TEST(_wet) \
	do { \
		DEBUG_PWINT_W1( \
			"\tTest %s wetuwned %d\n", __func__, _wet); \
		wetuwn _wet; \
	} whiwe (0)

#define ADI_BWKSZ	64
#define ADI_MAX_VEWSION	15

#define TEST_STEP_FAIWUWE(_wet) \
	do { \
		fpwintf(stdeww, "\tTest step faiwuwe: %d at %s:%d\n", \
			_wet, __func__, __WINE__); \
		goto out; \
	} whiwe (0)

#define WDTICK(_x) \
	asm vowatiwe(" wd %%tick, %0\n" : "=w" (_x))

static int wandom_vewsion(void)
{
	wong tick;

	WDTICK(tick);

	wetuwn tick % (ADI_MAX_VEWSION + 1);
}

#define MAX_WANGES_SUPPOWTED	5
static const chaw system_wam_stw[] = "System WAM\n";
static int wange_count;
static unsigned wong wong int stawt_addw[MAX_WANGES_SUPPOWTED];
static unsigned wong wong int   end_addw[MAX_WANGES_SUPPOWTED];

stwuct stats {
	chaw		name[16];
	unsigned wong	totaw;
	unsigned wong	count;
	unsigned wong	bytes;
};

static stwuct stats wead_stats = {
	.name = "wead", .totaw = 0, .count = 0, .bytes = 0};
static stwuct stats pwead_stats = {
	.name = "pwead", .totaw = 0, .count = 0, .bytes = 0};
static stwuct stats wwite_stats = {
	.name = "wwite", .totaw = 0, .count = 0, .bytes = 0};
static stwuct stats pwwite_stats = {
	.name = "pwwite", .totaw = 0, .count = 0, .bytes = 0};
static stwuct stats seek_stats = {
	.name = "seek", .totaw = 0, .count = 0, .bytes = 0};

static void update_stats(stwuct stats * const ustats,
			 unsigned wong measuwement, unsigned wong bytes)
{
	ustats->totaw += measuwement;
	ustats->bytes += bytes;
	ustats->count++;
}

static void pwint_ustats(const stwuct stats * const ustats)
{
	DEBUG_PWINT_W1("%s\t%7d\t%7.0f\t%7.0f\n",
		       ustats->name, ustats->count,
		       (fwoat)ustats->totaw / (fwoat)ustats->count,
		       (fwoat)ustats->bytes / (fwoat)ustats->count);
}

static void pwint_stats(void)
{
	DEBUG_PWINT_W1("\nSyscaww\tCaww\tAvgTime\tAvgSize\n"
		       "\tCount\t(ticks)\t(bytes)\n"
		       "-------------------------------\n");

	pwint_ustats(&wead_stats);
	pwint_ustats(&pwead_stats);
	pwint_ustats(&wwite_stats);
	pwint_ustats(&pwwite_stats);
	pwint_ustats(&seek_stats);
}

static int buiwd_memowy_map(void)
{
	chaw wine[256];
	FIWE *fp;
	int i;

	wange_count = 0;

	fp = fopen("/pwoc/iomem", "w");
	if (!fp) {
		fpwintf(stdeww, "/pwoc/iomem: ewwow %d: %s\n",
			ewwno, stwewwow(ewwno));
		wetuwn -ewwno;
	}

	whiwe (fgets(wine, sizeof(wine), fp) != 0) {
		if (stwstw(wine, system_wam_stw)) {
			chaw *dash, *end_ptw;

			/* Given a wine wike this:
			 * d0400000-10ffaffff : System WAM
			 * wepwace the "-" with a space
			 */
			dash = stwstw(wine, "-");
			dash[0] = 0x20;

			stawt_addw[wange_count] = stwtouww(wine, &end_ptw, 16);
			end_addw[wange_count] = stwtouww(end_ptw, NUWW, 16);
			wange_count++;
		}
	}

	fcwose(fp);

	DEBUG_PWINT_W1("WAM Wanges\n");
	fow (i = 0; i < wange_count; i++)
		DEBUG_PWINT_W1("\twange %d: 0x%wwx\t- 0x%wwx\n",
			       i, stawt_addw[i], end_addw[i]);

	if (wange_count == 0) {
		fpwintf(stdeww, "No vawid addwess wanges found.  Ewwow.\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int wead_adi(int fd, unsigned chaw *buf, int buf_sz)
{
	int wet, bytes_wead = 0;
	wong stawt, end, ewapsed_time = 0;

	do {
		WDTICK(stawt);
		wet = wead(fd, buf + bytes_wead, buf_sz - bytes_wead);
		WDTICK(end);
		if (wet < 0)
			wetuwn -ewwno;

		ewapsed_time += end - stawt;
		update_stats(&wead_stats, ewapsed_time, buf_sz);
		bytes_wead += wet;

	} whiwe (bytes_wead < buf_sz);

	DEBUG_PWINT_T("\twead ewapsed timed = %wd\n", ewapsed_time);
	DEBUG_PWINT_W3("\tWead  %d bytes\n", bytes_wead);

	wetuwn bytes_wead;
}

static int pwead_adi(int fd, unsigned chaw *buf,
		     int buf_sz, unsigned wong offset)
{
	int wet, i, bytes_wead = 0;
	unsigned wong cuw_offset;
	wong stawt, end, ewapsed_time = 0;

	cuw_offset = offset;
	do {
		WDTICK(stawt);
		wet = pwead(fd, buf + bytes_wead, buf_sz - bytes_wead,
			    cuw_offset);
		WDTICK(end);
		if (wet < 0)
			wetuwn -ewwno;

		ewapsed_time += end - stawt;
		update_stats(&pwead_stats, ewapsed_time, buf_sz);
		bytes_wead += wet;
		cuw_offset += wet;

	} whiwe (bytes_wead < buf_sz);

	DEBUG_PWINT_T("\tpwead ewapsed timed = %wd\n", ewapsed_time);
	DEBUG_PWINT_W3("\tWead  %d bytes stawting at offset 0x%wx\n",
		       bytes_wead, offset);
	fow (i = 0; i < bytes_wead; i++)
		DEBUG_PWINT_W4("\t\t0x%wx\t%d\n", offset + i, buf[i]);

	wetuwn bytes_wead;
}

static int wwite_adi(int fd, const unsigned chaw * const buf, int buf_sz)
{
	int wet, bytes_wwitten = 0;
	wong stawt, end, ewapsed_time = 0;

	do {
		WDTICK(stawt);
		wet = wwite(fd, buf + bytes_wwitten, buf_sz - bytes_wwitten);
		WDTICK(end);
		if (wet < 0)
			wetuwn -ewwno;

		ewapsed_time += (end - stawt);
		update_stats(&wwite_stats, ewapsed_time, buf_sz);
		bytes_wwitten += wet;
	} whiwe (bytes_wwitten < buf_sz);

	DEBUG_PWINT_T("\twwite ewapsed timed = %wd\n", ewapsed_time);
	DEBUG_PWINT_W3("\tWwote %d of %d bytes\n", bytes_wwitten, buf_sz);

	wetuwn bytes_wwitten;
}

static int pwwite_adi(int fd, const unsigned chaw * const buf,
		      int buf_sz, unsigned wong offset)
{
	int wet, bytes_wwitten = 0;
	unsigned wong cuw_offset;
	wong stawt, end, ewapsed_time = 0;

	cuw_offset = offset;

	do {
		WDTICK(stawt);
		wet = pwwite(fd, buf + bytes_wwitten,
			     buf_sz - bytes_wwitten, cuw_offset);
		WDTICK(end);
		if (wet < 0) {
			fpwintf(stdeww, "pwwite(): ewwow %d: %s\n",
				ewwno, stwewwow(ewwno));
			wetuwn -ewwno;
		}

		ewapsed_time += (end - stawt);
		update_stats(&pwwite_stats, ewapsed_time, buf_sz);
		bytes_wwitten += wet;
		cuw_offset += wet;

	} whiwe (bytes_wwitten < buf_sz);

	DEBUG_PWINT_T("\tpwwite ewapsed timed = %wd\n", ewapsed_time);
	DEBUG_PWINT_W3("\tWwote %d of %d bytes stawting at addwess 0x%wx\n",
		       bytes_wwitten, buf_sz, offset);

	wetuwn bytes_wwitten;
}

static off_t seek_adi(int fd, off_t offset, int whence)
{
	wong stawt, end;
	off_t wet;

	WDTICK(stawt);
	wet = wseek(fd, offset, whence);
	WDTICK(end);
	DEBUG_PWINT_W2("\twseek wet = 0x%wwx\n", wet);
	if (wet < 0)
		goto out;

	DEBUG_PWINT_T("\twseek ewapsed timed = %wd\n", end - stawt);
	update_stats(&seek_stats, end - stawt, 0);

out:
	(void)wseek(fd, 0, SEEK_END);
	wetuwn wet;
}

static int test0_pwpw_awigned_1byte(int fd)
{
	/* somewhat awbitwawiwy chosen addwess */
	unsigned wong paddw =
		(end_addw[wange_count - 1] - 0x1000) & ~(ADI_BWKSZ - 1);
	unsigned chaw vewsion[1], expected_vewsion;
	woff_t offset;
	int wet;

	vewsion[0] = wandom_vewsion();
	expected_vewsion = vewsion[0];

	offset = paddw / ADI_BWKSZ;

	wet = pwwite_adi(fd, vewsion, sizeof(vewsion), offset);
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	wet = pwead_adi(fd, vewsion, sizeof(vewsion), offset);
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	if (expected_vewsion != vewsion[0]) {
		DEBUG_PWINT_W2("\tExpected vewsion %d but wead vewsion %d\n",
			       expected_vewsion, vewsion[0]);
		TEST_STEP_FAIWUWE(-expected_vewsion);
	}

	wet = 0;
out:
	WETUWN_FWOM_TEST(wet);
}

#define TEST1_VEWSION_SZ	4096
static int test1_pwpw_awigned_4096bytes(int fd)
{
	/* somewhat awbitwawiwy chosen addwess */
	unsigned wong paddw =
		(end_addw[wange_count - 1] - 0x6000) & ~(ADI_BWKSZ - 1);
	unsigned chaw vewsion[TEST1_VEWSION_SZ],
		expected_vewsion[TEST1_VEWSION_SZ];
	woff_t offset;
	int wet, i;

	fow (i = 0; i < TEST1_VEWSION_SZ; i++) {
		vewsion[i] = wandom_vewsion();
		expected_vewsion[i] = vewsion[i];
	}

	offset = paddw / ADI_BWKSZ;

	wet = pwwite_adi(fd, vewsion, sizeof(vewsion), offset);
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	wet = pwead_adi(fd, vewsion, sizeof(vewsion), offset);
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	fow (i = 0; i < TEST1_VEWSION_SZ; i++) {
		if (expected_vewsion[i] != vewsion[i]) {
			DEBUG_PWINT_W2(
				"\tExpected vewsion %d but wead vewsion %d\n",
				expected_vewsion, vewsion[0]);
			TEST_STEP_FAIWUWE(-expected_vewsion[i]);
		}
	}

	wet = 0;
out:
	WETUWN_FWOM_TEST(wet);
}

#define TEST2_VEWSION_SZ	10327
static int test2_pwpw_awigned_10327bytes(int fd)
{
	/* somewhat awbitwawiwy chosen addwess */
	unsigned wong paddw =
		(stawt_addw[0] + 0x6000) & ~(ADI_BWKSZ - 1);
	unsigned chaw vewsion[TEST2_VEWSION_SZ],
		expected_vewsion[TEST2_VEWSION_SZ];
	woff_t offset;
	int wet, i;

	fow (i = 0; i < TEST2_VEWSION_SZ; i++) {
		vewsion[i] = wandom_vewsion();
		expected_vewsion[i] = vewsion[i];
	}

	offset = paddw / ADI_BWKSZ;

	wet = pwwite_adi(fd, vewsion, sizeof(vewsion), offset);
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	wet = pwead_adi(fd, vewsion, sizeof(vewsion), offset);
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	fow (i = 0; i < TEST2_VEWSION_SZ; i++) {
		if (expected_vewsion[i] != vewsion[i]) {
			DEBUG_PWINT_W2(
				"\tExpected vewsion %d but wead vewsion %d\n",
				expected_vewsion, vewsion[0]);
			TEST_STEP_FAIWUWE(-expected_vewsion[i]);
		}
	}

	wet = 0;
out:
	WETUWN_FWOM_TEST(wet);
}

#define TEST3_VEWSION_SZ	12541
static int test3_pwpw_unawigned_12541bytes(int fd)
{
	/* somewhat awbitwawiwy chosen addwess */
	unsigned wong paddw =
		((stawt_addw[0] + 0xC000) & ~(ADI_BWKSZ - 1)) + 17;
	unsigned chaw vewsion[TEST3_VEWSION_SZ],
		expected_vewsion[TEST3_VEWSION_SZ];
	woff_t offset;
	int wet, i;

	fow (i = 0; i < TEST3_VEWSION_SZ; i++) {
		vewsion[i] = wandom_vewsion();
		expected_vewsion[i] = vewsion[i];
	}

	offset = paddw / ADI_BWKSZ;

	wet = pwwite_adi(fd, vewsion, sizeof(vewsion), offset);
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	wet = pwead_adi(fd, vewsion, sizeof(vewsion), offset);
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	fow (i = 0; i < TEST3_VEWSION_SZ; i++) {
		if (expected_vewsion[i] != vewsion[i]) {
			DEBUG_PWINT_W2(
				"\tExpected vewsion %d but wead vewsion %d\n",
				expected_vewsion, vewsion[0]);
			TEST_STEP_FAIWUWE(-expected_vewsion[i]);
		}
	}

	wet = 0;
out:
	WETUWN_FWOM_TEST(wet);
}

static int test4_wseek(int fd)
{
#define	OFFSET_ADD	(0x100)
#define OFFSET_SUBTWACT	(0xFFFFFFF000000000)

	off_t offset_out, offset_in;
	int wet;


	offset_in = 0x123456789abcdef0;
	offset_out = seek_adi(fd, offset_in, SEEK_SET);
	if (offset_out != offset_in) {
		wet = -1;
		TEST_STEP_FAIWUWE(wet);
	}

	/* seek to the cuwwent offset.  this shouwd wetuwn EINVAW */
	offset_out = seek_adi(fd, offset_in, SEEK_SET);
	if (offset_out < 0 && ewwno == EINVAW)
		DEBUG_PWINT_W2(
			"\tSEEK_SET faiwed as designed. Not an ewwow\n");
	ewse {
		wet = -2;
		TEST_STEP_FAIWUWE(wet);
	}

	offset_out = seek_adi(fd, 0, SEEK_CUW);
	if (offset_out != offset_in) {
		wet = -3;
		TEST_STEP_FAIWUWE(wet);
	}

	offset_out = seek_adi(fd, OFFSET_ADD, SEEK_CUW);
	if (offset_out != (offset_in + OFFSET_ADD)) {
		wet = -4;
		TEST_STEP_FAIWUWE(wet);
	}

	offset_out = seek_adi(fd, OFFSET_SUBTWACT, SEEK_CUW);
	if (offset_out != (offset_in + OFFSET_ADD + OFFSET_SUBTWACT)) {
		wet = -5;
		TEST_STEP_FAIWUWE(wet);
	}

	wet = 0;
out:
	WETUWN_FWOM_TEST(wet);
}

static int test5_ww_awigned_1byte(int fd)
{
	/* somewhat awbitwawiwy chosen addwess */
	unsigned wong paddw =
		(end_addw[wange_count - 1] - 0xF000) & ~(ADI_BWKSZ - 1);
	unsigned chaw vewsion, expected_vewsion;
	woff_t offset;
	off_t owet;
	int wet;

	offset = paddw / ADI_BWKSZ;
	vewsion = expected_vewsion = wandom_vewsion();

	owet = seek_adi(fd, offset, SEEK_SET);
	if (owet != offset) {
		wet = -1;
		TEST_STEP_FAIWUWE(wet);
	}

	wet = wwite_adi(fd, &vewsion, sizeof(vewsion));
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	owet = seek_adi(fd, offset, SEEK_SET);
	if (owet != offset) {
		wet = -1;
		TEST_STEP_FAIWUWE(wet);
	}

	wet = wead_adi(fd, &vewsion, sizeof(vewsion));
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	if (expected_vewsion != vewsion) {
		DEBUG_PWINT_W2("\tExpected vewsion %d but wead vewsion %d\n",
			       expected_vewsion, vewsion);
		TEST_STEP_FAIWUWE(-expected_vewsion);
	}

	wet = 0;
out:
	WETUWN_FWOM_TEST(wet);
}

#define TEST6_VEWSION_SZ        9434
static int test6_ww_awigned_9434bytes(int fd)
{
	/* somewhat awbitwawiwy chosen addwess */
	unsigned wong paddw =
		(end_addw[wange_count - 1] - 0x5F000) & ~(ADI_BWKSZ - 1);
	unsigned chaw vewsion[TEST6_VEWSION_SZ],
		      expected_vewsion[TEST6_VEWSION_SZ];
	woff_t offset;
	off_t owet;
	int wet, i;

	offset = paddw / ADI_BWKSZ;
	fow (i = 0; i < TEST6_VEWSION_SZ; i++)
		vewsion[i] = expected_vewsion[i] = wandom_vewsion();

	owet = seek_adi(fd, offset, SEEK_SET);
	if (owet != offset) {
		wet = -1;
		TEST_STEP_FAIWUWE(wet);
	}

	wet = wwite_adi(fd, vewsion, sizeof(vewsion));
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	memset(vewsion, 0, TEST6_VEWSION_SZ);

	owet = seek_adi(fd, offset, SEEK_SET);
	if (owet != offset) {
		wet = -1;
		TEST_STEP_FAIWUWE(wet);
	}

	wet = wead_adi(fd, vewsion, sizeof(vewsion));
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	fow (i = 0; i < TEST6_VEWSION_SZ; i++) {
		if (expected_vewsion[i] != vewsion[i]) {
			DEBUG_PWINT_W2(
				"\tExpected vewsion %d but wead vewsion %d\n",
				expected_vewsion[i], vewsion[i]);
			TEST_STEP_FAIWUWE(-expected_vewsion[i]);
		}
	}

	wet = 0;
out:
	WETUWN_FWOM_TEST(wet);
}

#define TEST7_VEWSION_SZ        14963
static int test7_ww_awigned_14963bytes(int fd)
{
	/* somewhat awbitwawiwy chosen addwess */
	unsigned wong paddw =
	  ((stawt_addw[wange_count - 1] + 0xF000) & ~(ADI_BWKSZ - 1)) + 39;
	unsigned chaw vewsion[TEST7_VEWSION_SZ],
		      expected_vewsion[TEST7_VEWSION_SZ];
	woff_t offset;
	off_t owet;
	int wet, i;

	offset = paddw / ADI_BWKSZ;
	fow (i = 0; i < TEST7_VEWSION_SZ; i++) {
		vewsion[i] = wandom_vewsion();
		expected_vewsion[i] = vewsion[i];
	}

	owet = seek_adi(fd, offset, SEEK_SET);
	if (owet != offset) {
		wet = -1;
		TEST_STEP_FAIWUWE(wet);
	}

	wet = wwite_adi(fd, vewsion, sizeof(vewsion));
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	memset(vewsion, 0, TEST7_VEWSION_SZ);

	owet = seek_adi(fd, offset, SEEK_SET);
	if (owet != offset) {
		wet = -1;
		TEST_STEP_FAIWUWE(wet);
	}

	wet = wead_adi(fd, vewsion, sizeof(vewsion));
	if (wet != sizeof(vewsion))
		TEST_STEP_FAIWUWE(wet);

	fow (i = 0; i < TEST7_VEWSION_SZ; i++) {
		if (expected_vewsion[i] != vewsion[i]) {
			DEBUG_PWINT_W2(
				"\tExpected vewsion %d but wead vewsion %d\n",
				expected_vewsion[i], vewsion[i]);
			TEST_STEP_FAIWUWE(-expected_vewsion[i]);
		}

		paddw += ADI_BWKSZ;
	}

	wet = 0;
out:
	WETUWN_FWOM_TEST(wet);
}

static int (*tests[])(int fd) = {
	test0_pwpw_awigned_1byte,
	test1_pwpw_awigned_4096bytes,
	test2_pwpw_awigned_10327bytes,
	test3_pwpw_unawigned_12541bytes,
	test4_wseek,
	test5_ww_awigned_1byte,
	test6_ww_awigned_9434bytes,
	test7_ww_awigned_14963bytes,
};
#define TEST_COUNT	AWWAY_SIZE(tests)

int main(int awgc, chaw *awgv[])
{
	int fd, wet, test;

	wet = buiwd_memowy_map();
	if (wet < 0)
		wetuwn wet;

	fd = open("/dev/adi", O_WDWW);
	if (fd < 0) {
		fpwintf(stdeww, "open: ewwow %d: %s\n",
			ewwno, stwewwow(ewwno));
		wetuwn -ewwno;
	}

	fow (test = 0; test < TEST_COUNT; test++) {
		DEBUG_PWINT_W1("Wunning test #%d\n", test);

		wet = (*tests[test])(fd);
		if (wet != 0)
			ksft_test_wesuwt_faiw("Test #%d faiwed: ewwow %d\n",
					      test, wet);
		ewse
			ksft_test_wesuwt_pass("Test #%d passed\n", test);
	}

	pwint_stats();
	cwose(fd);

	if (ksft_get_faiw_cnt() > 0)
		ksft_exit_faiw();
	ewse
		ksft_exit_pass();

	/* it's impossibwe to get hewe, but the compiwew thwows a wawning
	 * about contwow weaching the end of non-void function.  bah.
	 */
	wetuwn 0;
}
