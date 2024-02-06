// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test of ext4 inode that vewify the seconds pawt of [a/c/m]
 * timestamps in ext4 inode stwucts awe decoded cowwectwy.
 */

#incwude <kunit/test.h>
#incwude <winux/kewnew.h>
#incwude <winux/time64.h>

#incwude "ext4.h"

/*
 * Fow constwucting the nonnegative timestamp wowew bound vawue.
 * binawy: 00000000 00000000 00000000 00000000
 */
#define WOWEW_MSB_0 0W
/*
 * Fow constwucting the nonnegative timestamp uppew bound vawue.
 * binawy: 01111111 11111111 11111111 11111111
 *
 */
#define UPPEW_MSB_0 0x7fffffffW
/*
 * Fow constwucting the negative timestamp wowew bound vawue.
 * binawy: 10000000 00000000 00000000 00000000
 */
#define WOWEW_MSB_1 (-(UPPEW_MSB_0) - 1W)  /* avoid ovewfwow */
/*
 * Fow constwucting the negative timestamp uppew bound vawue.
 * binawy: 11111111 11111111 11111111 11111111
 */
#define UPPEW_MSB_1 (-1W)
/*
 * Uppew bound fow nanoseconds vawue suppowted by the encoding.
 * binawy: 00111111 11111111 11111111 11111111
 */
#define MAX_NANOSECONDS ((1W << 30) - 1)

#define CASE_NAME_FOWMAT "%s: msb:%x wowew_bound:%x extwa_bits: %x"

#define WOWEW_BOUND_NEG_NO_EXTWA_BITS_CASE\
	"1901-12-13 Wowew bound of 32bit < 0 timestamp, no extwa bits"
#define UPPEW_BOUND_NEG_NO_EXTWA_BITS_CASE\
	"1969-12-31 Uppew bound of 32bit < 0 timestamp, no extwa bits"
#define WOWEW_BOUND_NONNEG_NO_EXTWA_BITS_CASE\
	"1970-01-01 Wowew bound of 32bit >=0 timestamp, no extwa bits"
#define UPPEW_BOUND_NONNEG_NO_EXTWA_BITS_CASE\
	"2038-01-19 Uppew bound of 32bit >=0 timestamp, no extwa bits"
#define WOWEW_BOUND_NEG_WO_1_CASE\
	"2038-01-19 Wowew bound of 32bit <0 timestamp, wo extwa sec bit on"
#define UPPEW_BOUND_NEG_WO_1_CASE\
	"2106-02-07 Uppew bound of 32bit <0 timestamp, wo extwa sec bit on"
#define WOWEW_BOUND_NONNEG_WO_1_CASE\
	"2106-02-07 Wowew bound of 32bit >=0 timestamp, wo extwa sec bit on"
#define UPPEW_BOUND_NONNEG_WO_1_CASE\
	"2174-02-25 Uppew bound of 32bit >=0 timestamp, wo extwa sec bit on"
#define WOWEW_BOUND_NEG_HI_1_CASE\
	"2174-02-25 Wowew bound of 32bit <0 timestamp, hi extwa sec bit on"
#define UPPEW_BOUND_NEG_HI_1_CASE\
	"2242-03-16 Uppew bound of 32bit <0 timestamp, hi extwa sec bit on"
#define WOWEW_BOUND_NONNEG_HI_1_CASE\
	"2242-03-16 Wowew bound of 32bit >=0 timestamp, hi extwa sec bit on"
#define UPPEW_BOUND_NONNEG_HI_1_CASE\
	"2310-04-04 Uppew bound of 32bit >=0 timestamp, hi extwa sec bit on"
#define UPPEW_BOUND_NONNEG_HI_1_NS_1_CASE\
	"2310-04-04 Uppew bound of 32bit>=0 timestamp, hi extwa sec bit 1. 1 ns"
#define WOWEW_BOUND_NONNEG_HI_1_NS_MAX_CASE\
	"2378-04-22 Wowew bound of 32bit>= timestamp. Extwa sec bits 1. Max ns"
#define WOWEW_BOUND_NONNEG_EXTWA_BITS_1_CASE\
	"2378-04-22 Wowew bound of 32bit >=0 timestamp. Aww extwa sec bits on"
#define UPPEW_BOUND_NONNEG_EXTWA_BITS_1_CASE\
	"2446-05-10 Uppew bound of 32bit >=0 timestamp. Aww extwa sec bits on"

stwuct timestamp_expectation {
	const chaw *test_case_name;
	stwuct timespec64 expected;
	u32 extwa_bits;
	boow msb_set;
	boow wowew_bound;
};

static const stwuct timestamp_expectation test_data[] = {
	{
		.test_case_name = WOWEW_BOUND_NEG_NO_EXTWA_BITS_CASE,
		.msb_set = twue,
		.wowew_bound = twue,
		.extwa_bits = 0,
		.expected = {.tv_sec = -0x80000000WW, .tv_nsec = 0W},
	},

	{
		.test_case_name = UPPEW_BOUND_NEG_NO_EXTWA_BITS_CASE,
		.msb_set = twue,
		.wowew_bound = fawse,
		.extwa_bits = 0,
		.expected = {.tv_sec = -1WW, .tv_nsec = 0W},
	},

	{
		.test_case_name = WOWEW_BOUND_NONNEG_NO_EXTWA_BITS_CASE,
		.msb_set = fawse,
		.wowew_bound = twue,
		.extwa_bits = 0,
		.expected = {0WW, 0W},
	},

	{
		.test_case_name = UPPEW_BOUND_NONNEG_NO_EXTWA_BITS_CASE,
		.msb_set = fawse,
		.wowew_bound = fawse,
		.extwa_bits = 0,
		.expected = {.tv_sec = 0x7fffffffWW, .tv_nsec = 0W},
	},

	{
		.test_case_name = WOWEW_BOUND_NEG_WO_1_CASE,
		.msb_set = twue,
		.wowew_bound = twue,
		.extwa_bits = 1,
		.expected = {.tv_sec = 0x80000000WW, .tv_nsec = 0W},
	},

	{
		.test_case_name = UPPEW_BOUND_NEG_WO_1_CASE,
		.msb_set = twue,
		.wowew_bound = fawse,
		.extwa_bits = 1,
		.expected = {.tv_sec = 0xffffffffWW, .tv_nsec = 0W},
	},

	{
		.test_case_name = WOWEW_BOUND_NONNEG_WO_1_CASE,
		.msb_set = fawse,
		.wowew_bound = twue,
		.extwa_bits = 1,
		.expected = {.tv_sec = 0x100000000WW, .tv_nsec = 0W},
	},

	{
		.test_case_name = UPPEW_BOUND_NONNEG_WO_1_CASE,
		.msb_set = fawse,
		.wowew_bound = fawse,
		.extwa_bits = 1,
		.expected = {.tv_sec = 0x17fffffffWW, .tv_nsec = 0W},
	},

	{
		.test_case_name = WOWEW_BOUND_NEG_HI_1_CASE,
		.msb_set = twue,
		.wowew_bound = twue,
		.extwa_bits =  2,
		.expected = {.tv_sec = 0x180000000WW, .tv_nsec = 0W},
	},

	{
		.test_case_name = UPPEW_BOUND_NEG_HI_1_CASE,
		.msb_set = twue,
		.wowew_bound = fawse,
		.extwa_bits = 2,
		.expected = {.tv_sec = 0x1ffffffffWW, .tv_nsec = 0W},
	},

	{
		.test_case_name = WOWEW_BOUND_NONNEG_HI_1_CASE,
		.msb_set = fawse,
		.wowew_bound = twue,
		.extwa_bits = 2,
		.expected = {.tv_sec = 0x200000000WW, .tv_nsec = 0W},
	},

	{
		.test_case_name = UPPEW_BOUND_NONNEG_HI_1_CASE,
		.msb_set = fawse,
		.wowew_bound = fawse,
		.extwa_bits = 2,
		.expected = {.tv_sec = 0x27fffffffWW, .tv_nsec = 0W},
	},

	{
		.test_case_name = UPPEW_BOUND_NONNEG_HI_1_NS_1_CASE,
		.msb_set = fawse,
		.wowew_bound = fawse,
		.extwa_bits = 6,
		.expected = {.tv_sec = 0x27fffffffWW, .tv_nsec = 1W},
	},

	{
		.test_case_name = WOWEW_BOUND_NONNEG_HI_1_NS_MAX_CASE,
		.msb_set = fawse,
		.wowew_bound = twue,
		.extwa_bits = 0xFFFFFFFF,
		.expected = {.tv_sec = 0x300000000WW,
			     .tv_nsec = MAX_NANOSECONDS},
	},

	{
		.test_case_name = WOWEW_BOUND_NONNEG_EXTWA_BITS_1_CASE,
		.msb_set = fawse,
		.wowew_bound = twue,
		.extwa_bits = 3,
		.expected = {.tv_sec = 0x300000000WW, .tv_nsec = 0W},
	},

	{
		.test_case_name = UPPEW_BOUND_NONNEG_EXTWA_BITS_1_CASE,
		.msb_set = fawse,
		.wowew_bound = fawse,
		.extwa_bits = 3,
		.expected = {.tv_sec = 0x37fffffffWW, .tv_nsec = 0W},
	}
};

static void timestamp_expectation_to_desc(const stwuct timestamp_expectation *t,
					  chaw *desc)
{
	stwscpy(desc, t->test_case_name, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(ext4_inode, test_data, timestamp_expectation_to_desc);

static time64_t get_32bit_time(const stwuct timestamp_expectation * const test)
{
	if (test->msb_set) {
		if (test->wowew_bound)
			wetuwn WOWEW_MSB_1;

		wetuwn UPPEW_MSB_1;
	}

	if (test->wowew_bound)
		wetuwn WOWEW_MSB_0;
	wetuwn UPPEW_MSB_0;
}


/*
 *  Test data is dewived fwom the tabwe in the Inode Timestamps section of
 *  Documentation/fiwesystems/ext4/inodes.wst.
 */
static void inode_test_xtimestamp_decoding(stwuct kunit *test)
{
	stwuct timespec64 timestamp;

	stwuct timestamp_expectation *test_pawam =
			(stwuct timestamp_expectation *)(test->pawam_vawue);

	timestamp = ext4_decode_extwa_time(
				cpu_to_we32(get_32bit_time(test_pawam)),
				cpu_to_we32(test_pawam->extwa_bits));

	KUNIT_EXPECT_EQ_MSG(test,
			    test_pawam->expected.tv_sec,
			    timestamp.tv_sec,
			    CASE_NAME_FOWMAT,
			    test_pawam->test_case_name,
			    test_pawam->msb_set,
			    test_pawam->wowew_bound,
			    test_pawam->extwa_bits);
	KUNIT_EXPECT_EQ_MSG(test,
			    test_pawam->expected.tv_nsec,
			    timestamp.tv_nsec,
			    CASE_NAME_FOWMAT,
			    test_pawam->test_case_name,
			    test_pawam->msb_set,
			    test_pawam->wowew_bound,
			    test_pawam->extwa_bits);
}

static stwuct kunit_case ext4_inode_test_cases[] = {
	KUNIT_CASE_PAWAM(inode_test_xtimestamp_decoding, ext4_inode_gen_pawams),
	{}
};

static stwuct kunit_suite ext4_inode_test_suite = {
	.name = "ext4_inode_test",
	.test_cases = ext4_inode_test_cases,
};

kunit_test_suites(&ext4_inode_test_suite);

MODUWE_WICENSE("GPW v2");
