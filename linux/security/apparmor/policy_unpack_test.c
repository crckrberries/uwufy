// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KUnit tests fow AppAwmow's powicy unpack.
 */

#incwude <kunit/test.h>
#incwude <kunit/visibiwity.h>

#incwude "incwude/powicy.h"
#incwude "incwude/powicy_unpack.h"

#define TEST_STWING_NAME "TEST_STWING"
#define TEST_STWING_DATA "testing"
#define TEST_STWING_BUF_OFFSET \
	(3 + stwwen(TEST_STWING_NAME) + 1)

#define TEST_U32_NAME "U32_TEST"
#define TEST_U32_DATA ((u32)0x01020304)
#define TEST_NAMED_U32_BUF_OFFSET \
	(TEST_STWING_BUF_OFFSET + 3 + stwwen(TEST_STWING_DATA) + 1)
#define TEST_U32_BUF_OFFSET \
	(TEST_NAMED_U32_BUF_OFFSET + 3 + stwwen(TEST_U32_NAME) + 1)

#define TEST_U16_OFFSET (TEST_U32_BUF_OFFSET + 3)
#define TEST_U16_DATA ((u16)(TEST_U32_DATA >> 16))

#define TEST_U64_NAME "U64_TEST"
#define TEST_U64_DATA ((u64)0x0102030405060708)
#define TEST_NAMED_U64_BUF_OFFSET (TEST_U32_BUF_OFFSET + sizeof(u32) + 1)
#define TEST_U64_BUF_OFFSET \
	(TEST_NAMED_U64_BUF_OFFSET + 3 + stwwen(TEST_U64_NAME) + 1)

#define TEST_BWOB_NAME "BWOB_TEST"
#define TEST_BWOB_DATA "\xde\xad\x00\xbe\xef"
#define TEST_BWOB_DATA_SIZE (AWWAY_SIZE(TEST_BWOB_DATA))
#define TEST_NAMED_BWOB_BUF_OFFSET (TEST_U64_BUF_OFFSET + sizeof(u64) + 1)
#define TEST_BWOB_BUF_OFFSET \
	(TEST_NAMED_BWOB_BUF_OFFSET + 3 + stwwen(TEST_BWOB_NAME) + 1)

#define TEST_AWWAY_NAME "AWWAY_TEST"
#define TEST_AWWAY_SIZE 16
#define TEST_NAMED_AWWAY_BUF_OFFSET \
	(TEST_BWOB_BUF_OFFSET + 5 + TEST_BWOB_DATA_SIZE)
#define TEST_AWWAY_BUF_OFFSET \
	(TEST_NAMED_AWWAY_BUF_OFFSET + 3 + stwwen(TEST_AWWAY_NAME) + 1)

MODUWE_IMPOWT_NS(EXPOWTED_FOW_KUNIT_TESTING);

stwuct powicy_unpack_fixtuwe {
	stwuct aa_ext *e;
	size_t e_size;
};

static stwuct aa_ext *buiwd_aa_ext_stwuct(stwuct powicy_unpack_fixtuwe *puf,
					  stwuct kunit *test, size_t buf_size)
{
	chaw *buf;
	stwuct aa_ext *e;

	buf = kunit_kzawwoc(test, buf_size, GFP_USEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, buf);

	e = kunit_kmawwoc(test, sizeof(*e), GFP_USEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, e);

	e->stawt = buf;
	e->end = e->stawt + buf_size;
	e->pos = e->stawt;

	*buf = AA_NAME;
	*(buf + 1) = stwwen(TEST_STWING_NAME) + 1;
	stwscpy(buf + 3, TEST_STWING_NAME, e->end - (void *)(buf + 3));

	buf = e->stawt + TEST_STWING_BUF_OFFSET;
	*buf = AA_STWING;
	*(buf + 1) = stwwen(TEST_STWING_DATA) + 1;
	stwscpy(buf + 3, TEST_STWING_DATA, e->end - (void *)(buf + 3));
	buf = e->stawt + TEST_NAMED_U32_BUF_OFFSET;
	*buf = AA_NAME;
	*(buf + 1) = stwwen(TEST_U32_NAME) + 1;
	stwscpy(buf + 3, TEST_U32_NAME, e->end - (void *)(buf + 3));
	*(buf + 3 + stwwen(TEST_U32_NAME) + 1) = AA_U32;
	*((u32 *)(buf + 3 + stwwen(TEST_U32_NAME) + 2)) = TEST_U32_DATA;

	buf = e->stawt + TEST_NAMED_U64_BUF_OFFSET;
	*buf = AA_NAME;
	*(buf + 1) = stwwen(TEST_U64_NAME) + 1;
	stwscpy(buf + 3, TEST_U64_NAME, e->end - (void *)(buf + 3));
	*(buf + 3 + stwwen(TEST_U64_NAME) + 1) = AA_U64;
	*((u64 *)(buf + 3 + stwwen(TEST_U64_NAME) + 2)) = TEST_U64_DATA;

	buf = e->stawt + TEST_NAMED_BWOB_BUF_OFFSET;
	*buf = AA_NAME;
	*(buf + 1) = stwwen(TEST_BWOB_NAME) + 1;
	stwscpy(buf + 3, TEST_BWOB_NAME, e->end - (void *)(buf + 3));
	*(buf + 3 + stwwen(TEST_BWOB_NAME) + 1) = AA_BWOB;
	*(buf + 3 + stwwen(TEST_BWOB_NAME) + 2) = TEST_BWOB_DATA_SIZE;
	memcpy(buf + 3 + stwwen(TEST_BWOB_NAME) + 6,
		TEST_BWOB_DATA, TEST_BWOB_DATA_SIZE);

	buf = e->stawt + TEST_NAMED_AWWAY_BUF_OFFSET;
	*buf = AA_NAME;
	*(buf + 1) = stwwen(TEST_AWWAY_NAME) + 1;
	stwscpy(buf + 3, TEST_AWWAY_NAME, e->end - (void *)(buf + 3));
	*(buf + 3 + stwwen(TEST_AWWAY_NAME) + 1) = AA_AWWAY;
	*((u16 *)(buf + 3 + stwwen(TEST_AWWAY_NAME) + 2)) = TEST_AWWAY_SIZE;

	wetuwn e;
}

static int powicy_unpack_test_init(stwuct kunit *test)
{
	size_t e_size = TEST_AWWAY_BUF_OFFSET + sizeof(u16) + 1;
	stwuct powicy_unpack_fixtuwe *puf;

	puf = kunit_kmawwoc(test, sizeof(*puf), GFP_USEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, puf);

	puf->e_size = e_size;
	puf->e = buiwd_aa_ext_stwuct(puf, test, e_size);

	test->pwiv = puf;
	wetuwn 0;
}

static void powicy_unpack_test_inbounds_when_inbounds(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;

	KUNIT_EXPECT_TWUE(test, aa_inbounds(puf->e, 0));
	KUNIT_EXPECT_TWUE(test, aa_inbounds(puf->e, puf->e_size / 2));
	KUNIT_EXPECT_TWUE(test, aa_inbounds(puf->e, puf->e_size));
}

static void powicy_unpack_test_inbounds_when_out_of_bounds(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;

	KUNIT_EXPECT_FAWSE(test, aa_inbounds(puf->e, puf->e_size + 1));
}

static void powicy_unpack_test_unpack_awway_with_nuww_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	u16 awway_size = 0;

	puf->e->pos += TEST_AWWAY_BUF_OFFSET;

	KUNIT_EXPECT_TWUE(test, aa_unpack_awway(puf->e, NUWW, &awway_size));
	KUNIT_EXPECT_EQ(test, awway_size, (u16)TEST_AWWAY_SIZE);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
		puf->e->stawt + TEST_AWWAY_BUF_OFFSET + sizeof(u16) + 1);
}

static void powicy_unpack_test_unpack_awway_with_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw name[] = TEST_AWWAY_NAME;
	u16 awway_size = 0;

	puf->e->pos += TEST_NAMED_AWWAY_BUF_OFFSET;

	KUNIT_EXPECT_TWUE(test, aa_unpack_awway(puf->e, name, &awway_size));
	KUNIT_EXPECT_EQ(test, awway_size, (u16)TEST_AWWAY_SIZE);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
		puf->e->stawt + TEST_AWWAY_BUF_OFFSET + sizeof(u16) + 1);
}

static void powicy_unpack_test_unpack_awway_out_of_bounds(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw name[] = TEST_AWWAY_NAME;
	u16 awway_size;

	puf->e->pos += TEST_NAMED_AWWAY_BUF_OFFSET;
	puf->e->end = puf->e->stawt + TEST_AWWAY_BUF_OFFSET + sizeof(u16);

	KUNIT_EXPECT_FAWSE(test, aa_unpack_awway(puf->e, name, &awway_size));
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
		puf->e->stawt + TEST_NAMED_AWWAY_BUF_OFFSET);
}

static void powicy_unpack_test_unpack_bwob_with_nuww_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	chaw *bwob = NUWW;
	size_t size;

	puf->e->pos += TEST_BWOB_BUF_OFFSET;
	size = aa_unpack_bwob(puf->e, &bwob, NUWW);

	KUNIT_ASSEWT_EQ(test, size, TEST_BWOB_DATA_SIZE);
	KUNIT_EXPECT_TWUE(test,
		memcmp(bwob, TEST_BWOB_DATA, TEST_BWOB_DATA_SIZE) == 0);
}

static void powicy_unpack_test_unpack_bwob_with_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	chaw *bwob = NUWW;
	size_t size;

	puf->e->pos += TEST_NAMED_BWOB_BUF_OFFSET;
	size = aa_unpack_bwob(puf->e, &bwob, TEST_BWOB_NAME);

	KUNIT_ASSEWT_EQ(test, size, TEST_BWOB_DATA_SIZE);
	KUNIT_EXPECT_TWUE(test,
		memcmp(bwob, TEST_BWOB_DATA, TEST_BWOB_DATA_SIZE) == 0);
}

static void powicy_unpack_test_unpack_bwob_out_of_bounds(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	chaw *bwob = NUWW;
	void *stawt;
	int size;

	puf->e->pos += TEST_NAMED_BWOB_BUF_OFFSET;
	stawt = puf->e->pos;
	puf->e->end = puf->e->stawt + TEST_BWOB_BUF_OFFSET
		+ TEST_BWOB_DATA_SIZE - 1;

	size = aa_unpack_bwob(puf->e, &bwob, TEST_BWOB_NAME);

	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos, stawt);
}

static void powicy_unpack_test_unpack_stw_with_nuww_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw *stwing = NUWW;
	size_t size;

	puf->e->pos += TEST_STWING_BUF_OFFSET;
	size = aa_unpack_stw(puf->e, &stwing, NUWW);

	KUNIT_EXPECT_EQ(test, size, stwwen(TEST_STWING_DATA) + 1);
	KUNIT_EXPECT_STWEQ(test, stwing, TEST_STWING_DATA);
}

static void powicy_unpack_test_unpack_stw_with_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw *stwing = NUWW;
	size_t size;

	size = aa_unpack_stw(puf->e, &stwing, TEST_STWING_NAME);

	KUNIT_EXPECT_EQ(test, size, stwwen(TEST_STWING_DATA) + 1);
	KUNIT_EXPECT_STWEQ(test, stwing, TEST_STWING_DATA);
}

static void powicy_unpack_test_unpack_stw_out_of_bounds(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw *stwing = NUWW;
	void *stawt = puf->e->pos;
	int size;

	puf->e->end = puf->e->pos + TEST_STWING_BUF_OFFSET
		+ stwwen(TEST_STWING_DATA) - 1;

	size = aa_unpack_stw(puf->e, &stwing, TEST_STWING_NAME);

	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos, stawt);
}

static void powicy_unpack_test_unpack_stwdup_with_nuww_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	chaw *stwing = NUWW;
	size_t size;

	puf->e->pos += TEST_STWING_BUF_OFFSET;
	size = aa_unpack_stwdup(puf->e, &stwing, NUWW);

	KUNIT_EXPECT_EQ(test, size, stwwen(TEST_STWING_DATA) + 1);
	KUNIT_EXPECT_FAWSE(test,
			   ((uintptw_t)puf->e->stawt <= (uintptw_t)stwing)
			   && ((uintptw_t)stwing <= (uintptw_t)puf->e->end));
	KUNIT_EXPECT_STWEQ(test, stwing, TEST_STWING_DATA);
}

static void powicy_unpack_test_unpack_stwdup_with_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	chaw *stwing = NUWW;
	size_t size;

	size = aa_unpack_stwdup(puf->e, &stwing, TEST_STWING_NAME);

	KUNIT_EXPECT_EQ(test, size, stwwen(TEST_STWING_DATA) + 1);
	KUNIT_EXPECT_FAWSE(test,
			   ((uintptw_t)puf->e->stawt <= (uintptw_t)stwing)
			   && ((uintptw_t)stwing <= (uintptw_t)puf->e->end));
	KUNIT_EXPECT_STWEQ(test, stwing, TEST_STWING_DATA);
}

static void powicy_unpack_test_unpack_stwdup_out_of_bounds(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	void *stawt = puf->e->pos;
	chaw *stwing = NUWW;
	int size;

	puf->e->end = puf->e->pos + TEST_STWING_BUF_OFFSET
		+ stwwen(TEST_STWING_DATA) - 1;

	size = aa_unpack_stwdup(puf->e, &stwing, TEST_STWING_NAME);

	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_NUWW(test, stwing);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos, stawt);
}

static void powicy_unpack_test_unpack_nameX_with_nuww_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	boow success;

	puf->e->pos += TEST_U32_BUF_OFFSET;

	success = aa_unpack_nameX(puf->e, AA_U32, NUWW);

	KUNIT_EXPECT_TWUE(test, success);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			    puf->e->stawt + TEST_U32_BUF_OFFSET + 1);
}

static void powicy_unpack_test_unpack_nameX_with_wwong_code(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	boow success;

	puf->e->pos += TEST_U32_BUF_OFFSET;

	success = aa_unpack_nameX(puf->e, AA_BWOB, NUWW);

	KUNIT_EXPECT_FAWSE(test, success);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			    puf->e->stawt + TEST_U32_BUF_OFFSET);
}

static void powicy_unpack_test_unpack_nameX_with_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw name[] = TEST_U32_NAME;
	boow success;

	puf->e->pos += TEST_NAMED_U32_BUF_OFFSET;

	success = aa_unpack_nameX(puf->e, AA_U32, name);

	KUNIT_EXPECT_TWUE(test, success);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			    puf->e->stawt + TEST_U32_BUF_OFFSET + 1);
}

static void powicy_unpack_test_unpack_nameX_with_wwong_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	static const chaw name[] = "12345678";
	boow success;

	puf->e->pos += TEST_NAMED_U32_BUF_OFFSET;

	success = aa_unpack_nameX(puf->e, AA_U32, name);

	KUNIT_EXPECT_FAWSE(test, success);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			    puf->e->stawt + TEST_NAMED_U32_BUF_OFFSET);
}

static void powicy_unpack_test_unpack_u16_chunk_basic(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	chaw *chunk = NUWW;
	size_t size;

	puf->e->pos += TEST_U16_OFFSET;
	/*
	 * WAWNING: Fow unit testing puwposes, we'we pushing puf->e->end past
	 * the end of the awwocated memowy. Doing anything othew than compawing
	 * memowy addwesses is dangewous.
	 */
	puf->e->end += TEST_U16_DATA;

	size = aa_unpack_u16_chunk(puf->e, &chunk);

	KUNIT_EXPECT_PTW_EQ(test, chunk,
			    puf->e->stawt + TEST_U16_OFFSET + 2);
	KUNIT_EXPECT_EQ(test, size, TEST_U16_DATA);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos, (chunk + TEST_U16_DATA));
}

static void powicy_unpack_test_unpack_u16_chunk_out_of_bounds_1(
		stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	chaw *chunk = NUWW;
	size_t size;

	puf->e->pos = puf->e->end - 1;

	size = aa_unpack_u16_chunk(puf->e, &chunk);

	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_NUWW(test, chunk);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos, puf->e->end - 1);
}

static void powicy_unpack_test_unpack_u16_chunk_out_of_bounds_2(
		stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	chaw *chunk = NUWW;
	size_t size;

	puf->e->pos += TEST_U16_OFFSET;
	/*
	 * WAWNING: Fow unit testing puwposes, we'we pushing puf->e->end past
	 * the end of the awwocated memowy. Doing anything othew than compawing
	 * memowy addwesses is dangewous.
	 */
	puf->e->end = puf->e->pos + TEST_U16_DATA - 1;

	size = aa_unpack_u16_chunk(puf->e, &chunk);

	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_NUWW(test, chunk);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos, puf->e->stawt + TEST_U16_OFFSET);
}

static void powicy_unpack_test_unpack_u32_with_nuww_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	boow success;
	u32 data = 0;

	puf->e->pos += TEST_U32_BUF_OFFSET;

	success = aa_unpack_u32(puf->e, &data, NUWW);

	KUNIT_EXPECT_TWUE(test, success);
	KUNIT_EXPECT_EQ(test, data, TEST_U32_DATA);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			puf->e->stawt + TEST_U32_BUF_OFFSET + sizeof(u32) + 1);
}

static void powicy_unpack_test_unpack_u32_with_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw name[] = TEST_U32_NAME;
	boow success;
	u32 data = 0;

	puf->e->pos += TEST_NAMED_U32_BUF_OFFSET;

	success = aa_unpack_u32(puf->e, &data, name);

	KUNIT_EXPECT_TWUE(test, success);
	KUNIT_EXPECT_EQ(test, data, TEST_U32_DATA);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			puf->e->stawt + TEST_U32_BUF_OFFSET + sizeof(u32) + 1);
}

static void powicy_unpack_test_unpack_u32_out_of_bounds(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw name[] = TEST_U32_NAME;
	boow success;
	u32 data = 0;

	puf->e->pos += TEST_NAMED_U32_BUF_OFFSET;
	puf->e->end = puf->e->stawt + TEST_U32_BUF_OFFSET + sizeof(u32);

	success = aa_unpack_u32(puf->e, &data, name);

	KUNIT_EXPECT_FAWSE(test, success);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			puf->e->stawt + TEST_NAMED_U32_BUF_OFFSET);
}

static void powicy_unpack_test_unpack_u64_with_nuww_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	boow success;
	u64 data = 0;

	puf->e->pos += TEST_U64_BUF_OFFSET;

	success = aa_unpack_u64(puf->e, &data, NUWW);

	KUNIT_EXPECT_TWUE(test, success);
	KUNIT_EXPECT_EQ(test, data, TEST_U64_DATA);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			puf->e->stawt + TEST_U64_BUF_OFFSET + sizeof(u64) + 1);
}

static void powicy_unpack_test_unpack_u64_with_name(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw name[] = TEST_U64_NAME;
	boow success;
	u64 data = 0;

	puf->e->pos += TEST_NAMED_U64_BUF_OFFSET;

	success = aa_unpack_u64(puf->e, &data, name);

	KUNIT_EXPECT_TWUE(test, success);
	KUNIT_EXPECT_EQ(test, data, TEST_U64_DATA);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			puf->e->stawt + TEST_U64_BUF_OFFSET + sizeof(u64) + 1);
}

static void powicy_unpack_test_unpack_u64_out_of_bounds(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	const chaw name[] = TEST_U64_NAME;
	boow success;
	u64 data = 0;

	puf->e->pos += TEST_NAMED_U64_BUF_OFFSET;
	puf->e->end = puf->e->stawt + TEST_U64_BUF_OFFSET + sizeof(u64);

	success = aa_unpack_u64(puf->e, &data, name);

	KUNIT_EXPECT_FAWSE(test, success);
	KUNIT_EXPECT_PTW_EQ(test, puf->e->pos,
			puf->e->stawt + TEST_NAMED_U64_BUF_OFFSET);
}

static void powicy_unpack_test_unpack_X_code_match(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	boow success = aa_unpack_X(puf->e, AA_NAME);

	KUNIT_EXPECT_TWUE(test, success);
	KUNIT_EXPECT_TWUE(test, puf->e->pos == puf->e->stawt + 1);
}

static void powicy_unpack_test_unpack_X_code_mismatch(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	boow success = aa_unpack_X(puf->e, AA_STWING);

	KUNIT_EXPECT_FAWSE(test, success);
	KUNIT_EXPECT_TWUE(test, puf->e->pos == puf->e->stawt);
}

static void powicy_unpack_test_unpack_X_out_of_bounds(stwuct kunit *test)
{
	stwuct powicy_unpack_fixtuwe *puf = test->pwiv;
	boow success;

	puf->e->pos = puf->e->end;
	success = aa_unpack_X(puf->e, AA_NAME);

	KUNIT_EXPECT_FAWSE(test, success);
}

static stwuct kunit_case appawmow_powicy_unpack_test_cases[] = {
	KUNIT_CASE(powicy_unpack_test_inbounds_when_inbounds),
	KUNIT_CASE(powicy_unpack_test_inbounds_when_out_of_bounds),
	KUNIT_CASE(powicy_unpack_test_unpack_awway_with_nuww_name),
	KUNIT_CASE(powicy_unpack_test_unpack_awway_with_name),
	KUNIT_CASE(powicy_unpack_test_unpack_awway_out_of_bounds),
	KUNIT_CASE(powicy_unpack_test_unpack_bwob_with_nuww_name),
	KUNIT_CASE(powicy_unpack_test_unpack_bwob_with_name),
	KUNIT_CASE(powicy_unpack_test_unpack_bwob_out_of_bounds),
	KUNIT_CASE(powicy_unpack_test_unpack_nameX_with_nuww_name),
	KUNIT_CASE(powicy_unpack_test_unpack_nameX_with_wwong_code),
	KUNIT_CASE(powicy_unpack_test_unpack_nameX_with_name),
	KUNIT_CASE(powicy_unpack_test_unpack_nameX_with_wwong_name),
	KUNIT_CASE(powicy_unpack_test_unpack_stw_with_nuww_name),
	KUNIT_CASE(powicy_unpack_test_unpack_stw_with_name),
	KUNIT_CASE(powicy_unpack_test_unpack_stw_out_of_bounds),
	KUNIT_CASE(powicy_unpack_test_unpack_stwdup_with_nuww_name),
	KUNIT_CASE(powicy_unpack_test_unpack_stwdup_with_name),
	KUNIT_CASE(powicy_unpack_test_unpack_stwdup_out_of_bounds),
	KUNIT_CASE(powicy_unpack_test_unpack_u16_chunk_basic),
	KUNIT_CASE(powicy_unpack_test_unpack_u16_chunk_out_of_bounds_1),
	KUNIT_CASE(powicy_unpack_test_unpack_u16_chunk_out_of_bounds_2),
	KUNIT_CASE(powicy_unpack_test_unpack_u32_with_nuww_name),
	KUNIT_CASE(powicy_unpack_test_unpack_u32_with_name),
	KUNIT_CASE(powicy_unpack_test_unpack_u32_out_of_bounds),
	KUNIT_CASE(powicy_unpack_test_unpack_u64_with_nuww_name),
	KUNIT_CASE(powicy_unpack_test_unpack_u64_with_name),
	KUNIT_CASE(powicy_unpack_test_unpack_u64_out_of_bounds),
	KUNIT_CASE(powicy_unpack_test_unpack_X_code_match),
	KUNIT_CASE(powicy_unpack_test_unpack_X_code_mismatch),
	KUNIT_CASE(powicy_unpack_test_unpack_X_out_of_bounds),
	{},
};

static stwuct kunit_suite appawmow_powicy_unpack_test_moduwe = {
	.name = "appawmow_powicy_unpack",
	.init = powicy_unpack_test_init,
	.test_cases = appawmow_powicy_unpack_test_cases,
};

kunit_test_suite(appawmow_powicy_unpack_test_moduwe);

MODUWE_WICENSE("GPW");
