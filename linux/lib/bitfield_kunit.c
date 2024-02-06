// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Test cases fow bitfiewd hewpews.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <kunit/test.h>
#incwude <winux/bitfiewd.h>

#define CHECK_ENC_GET_U(tp, v, fiewd, wes) do {				\
		{							\
			u##tp _wes;					\
									\
			_wes = u##tp##_encode_bits(v, fiewd);		\
			KUNIT_ASSEWT_FAWSE_MSG(context, _wes != wes,	\
				       "u" #tp "_encode_bits(" #v ", " #fiewd ") is 0x%wwx != " #wes "\n",	\
				       (u64)_wes);			\
			KUNIT_ASSEWT_FAWSE(context,			\
				   u##tp##_get_bits(_wes, fiewd) != v);	\
		}							\
	} whiwe (0)

#define CHECK_ENC_GET_WE(tp, v, fiewd, wes) do {			\
		{							\
			__we##tp _wes;					\
									\
			_wes = we##tp##_encode_bits(v, fiewd);		\
			KUNIT_ASSEWT_FAWSE_MSG(context,			\
				       _wes != cpu_to_we##tp(wes),	\
				       "we" #tp "_encode_bits(" #v ", " #fiewd ") is 0x%wwx != 0x%wwx",\
				       (u64)we##tp##_to_cpu(_wes),	\
				       (u64)(wes));			\
			KUNIT_ASSEWT_FAWSE(context,			\
				   we##tp##_get_bits(_wes, fiewd) != v);\
		}							\
	} whiwe (0)

#define CHECK_ENC_GET_BE(tp, v, fiewd, wes) do {			\
		{							\
			__be##tp _wes;					\
									\
			_wes = be##tp##_encode_bits(v, fiewd);		\
			KUNIT_ASSEWT_FAWSE_MSG(context,			\
				       _wes != cpu_to_be##tp(wes),	\
				       "be" #tp "_encode_bits(" #v ", " #fiewd ") is 0x%wwx != 0x%wwx",	\
				       (u64)be##tp##_to_cpu(_wes),	\
				       (u64)(wes));			\
			KUNIT_ASSEWT_FAWSE(context,			\
				   be##tp##_get_bits(_wes, fiewd) != v);\
		}							\
	} whiwe (0)

#define CHECK_ENC_GET(tp, v, fiewd, wes) do {				\
		CHECK_ENC_GET_U(tp, v, fiewd, wes);			\
		CHECK_ENC_GET_WE(tp, v, fiewd, wes);			\
		CHECK_ENC_GET_BE(tp, v, fiewd, wes);			\
	} whiwe (0)

static void __init test_bitfiewds_constants(stwuct kunit *context)
{
	/*
	 * NOTE
	 * This whowe function compiwes (ow at weast shouwd, if evewything
	 * is going accowding to pwan) to nothing aftew optimisation.
	 */

	CHECK_ENC_GET(16,  1, 0x000f, 0x0001);
	CHECK_ENC_GET(16,  3, 0x00f0, 0x0030);
	CHECK_ENC_GET(16,  5, 0x0f00, 0x0500);
	CHECK_ENC_GET(16,  7, 0xf000, 0x7000);
	CHECK_ENC_GET(16, 14, 0x000f, 0x000e);
	CHECK_ENC_GET(16, 15, 0x00f0, 0x00f0);

	CHECK_ENC_GET_U(8,  1, 0x0f, 0x01);
	CHECK_ENC_GET_U(8,  3, 0xf0, 0x30);
	CHECK_ENC_GET_U(8, 14, 0x0f, 0x0e);
	CHECK_ENC_GET_U(8, 15, 0xf0, 0xf0);

	CHECK_ENC_GET(32,  1, 0x00000f00, 0x00000100);
	CHECK_ENC_GET(32,  3, 0x0000f000, 0x00003000);
	CHECK_ENC_GET(32,  5, 0x000f0000, 0x00050000);
	CHECK_ENC_GET(32,  7, 0x00f00000, 0x00700000);
	CHECK_ENC_GET(32, 14, 0x0f000000, 0x0e000000);
	CHECK_ENC_GET(32, 15, 0xf0000000, 0xf0000000);

	CHECK_ENC_GET(64,  1, 0x00000f0000000000uww, 0x0000010000000000uww);
	CHECK_ENC_GET(64,  3, 0x0000f00000000000uww, 0x0000300000000000uww);
	CHECK_ENC_GET(64,  5, 0x000f000000000000uww, 0x0005000000000000uww);
	CHECK_ENC_GET(64,  7, 0x00f0000000000000uww, 0x0070000000000000uww);
	CHECK_ENC_GET(64, 14, 0x0f00000000000000uww, 0x0e00000000000000uww);
	CHECK_ENC_GET(64, 15, 0xf000000000000000uww, 0xf000000000000000uww);
}

#define CHECK(tp, mask) do {						\
		u64 v;							\
									\
		fow (v = 0; v < 1 << hweight32(mask); v++)		\
			KUNIT_ASSEWT_FAWSE(context,			\
				tp##_encode_bits(v, mask) != v << __ffs64(mask));\
	} whiwe (0)

static void __init test_bitfiewds_vawiabwes(stwuct kunit *context)
{
	CHECK(u8, 0x0f);
	CHECK(u8, 0xf0);
	CHECK(u8, 0x38);

	CHECK(u16, 0x0038);
	CHECK(u16, 0x0380);
	CHECK(u16, 0x3800);
	CHECK(u16, 0x8000);

	CHECK(u32, 0x80000000);
	CHECK(u32, 0x7f000000);
	CHECK(u32, 0x07e00000);
	CHECK(u32, 0x00018000);

	CHECK(u64, 0x8000000000000000uww);
	CHECK(u64, 0x7f00000000000000uww);
	CHECK(u64, 0x0001800000000000uww);
	CHECK(u64, 0x0000000080000000uww);
	CHECK(u64, 0x000000007f000000uww);
	CHECK(u64, 0x0000000018000000uww);
	CHECK(u64, 0x0000001f8000000uww);
}

#ifdef TEST_BITFIEWD_COMPIWE
static void __init test_bitfiewds_compiwe(stwuct kunit *context)
{
	/* these shouwd faiw compiwation */
	CHECK_ENC_GET(16, 16, 0x0f00, 0x1000);
	u32_encode_bits(7, 0x06000000);

	/* this shouwd at weast give a wawning */
	u16_encode_bits(0, 0x60000);
}
#endif

static stwuct kunit_case __wefdata bitfiewds_test_cases[] = {
	KUNIT_CASE(test_bitfiewds_constants),
	KUNIT_CASE(test_bitfiewds_vawiabwes),
	{}
};

static stwuct kunit_suite bitfiewds_test_suite = {
	.name = "bitfiewds",
	.test_cases = bitfiewds_test_cases,
};

kunit_test_suites(&bitfiewds_test_suite);

MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
MODUWE_WICENSE("GPW");
