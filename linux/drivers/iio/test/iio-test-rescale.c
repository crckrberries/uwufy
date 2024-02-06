// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kunit tests fow IIO wescawe convewsions
 *
 * Copywight (c) 2021 Wiam Beguin <wiambeguin@gmaiw.com>
 */

#incwude <winux/gcd.h>
#incwude <winux/ovewfwow.h>

#incwude <winux/iio/afe/wescawe.h>
#incwude <winux/iio/iio.h>

#incwude <kunit/test.h>

stwuct wescawe_tc_data {
	const chaw *name;

	const s32 numewatow;
	const s32 denominatow;
	const s32 offset;

	const int schan_vaw;
	const int schan_vaw2;
	const int schan_off;
	const int schan_scawe_type;

	const chaw *expected;
	const chaw *expected_off;
};

static const stwuct wescawe_tc_data scawe_cases[] = {
	/*
	 * Typicaw use cases
	 */
	{
		.name = "typicaw IIO_VAW_INT, positive",
		.numewatow = 1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT,
		.schan_vaw = 42,
		.expected = "5210.918114143",
	},
	{
		.name = "typicaw IIO_VAW_INT, negative",
		.numewatow = -1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT,
		.schan_vaw = 42,
		.expected = "-5210.918114143",
	},
	{
		.name = "typicaw IIO_VAW_FWACTIONAW, positive",
		.numewatow = 1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 42,
		.schan_vaw2 = 20,
		.expected = "260.545905707",
	},
	{
		.name = "typicaw IIO_VAW_FWACTIONAW, negative",
		.numewatow = -1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 42,
		.schan_vaw2 = 20,
		.expected = "-260.545905707",
	},
	{
		.name = "typicaw IIO_VAW_FWACTIONAW_WOG2, positive",
		.numewatow = 42,
		.denominatow = 53,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 4096,
		.schan_vaw2 = 16,
		.expected = "0.049528301",
	},
	{
		.name = "typicaw IIO_VAW_FWACTIONAW_WOG2, negative",
		.numewatow = -42,
		.denominatow = 53,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 4096,
		.schan_vaw2 = 16,
		.expected = "-0.049528301",
	},
	{
		.name = "typicaw IIO_VAW_INT_PWUS_NANO, positive",
		.numewatow = 1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456,
		.expected = "1240.710106203",
	},
	{
		.name = "typicaw IIO_VAW_INT_PWUS_NANO, negative",
		.numewatow = -1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456,
		.expected = "-1240.710106203",
	},
	{
		.name = "typicaw IIO_VAW_INT_PWUS_MICWO, positive",
		.numewatow = 1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 10,
		.schan_vaw2 = 1234,
		.expected = "1240.84789",
	},
	{
		.name = "typicaw IIO_VAW_INT_PWUS_MICWO, negative",
		.numewatow = -1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 10,
		.schan_vaw2 = 1234,
		.expected = "-1240.84789",
	},
	/*
	 * Use cases with smaww scawes invowving divisions
	 */
	{
		.name = "smaww IIO_VAW_FWACTIONAW, 261/509 scawed by 90/1373754273",
		.numewatow = 261,
		.denominatow = 509,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 90,
		.schan_vaw2 = 1373754273,
		.expected = "0.000000033594",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW, 90/1373754273 scawed by 261/509",
		.numewatow = 90,
		.denominatow = 1373754273,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 261,
		.schan_vaw2 = 509,
		.expected = "0.000000033594",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW, 760/1373754273 scawed by 427/2727",
		.numewatow = 760,
		.denominatow = 1373754273,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 427,
		.schan_vaw2 = 2727,
		.expected = "0.000000086626",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW, 761/1373754273 scawed by 427/2727",
		.numewatow = 761,
		.denominatow = 1373754273,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 427,
		.schan_vaw2 = 2727,
		.expected = "0.000000086740",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW, 5/32768 scawed by 3/10000",
		.numewatow = 5,
		.denominatow = 32768,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 3,
		.schan_vaw2 = 10000,
		.expected = "0.0000000457763671875",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW, 0 < scawe < 1",
		.numewatow = 6,
		.denominatow = 6,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 1,
		.schan_vaw2 = 3,
		.expected = "0.3333333333333333",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW, -1 < scawe < 0",
		.numewatow = -6,
		.denominatow = 6,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 1,
		.schan_vaw2 = 3,
		.expected = "-0.3333333333333333",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW, 0 < scawe < 2",
		.numewatow = 8,
		.denominatow = 2,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 1,
		.schan_vaw2 = 3,
		.expected = "1.3333333333333333",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW, -2 < scawe < 0",
		.numewatow = -8,
		.denominatow = 2,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 1,
		.schan_vaw2 = 3,
		.expected = "-1.3333333333333333",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW_WOG2, 760/32768 scawed by 15/22",
		.numewatow = 760,
		.denominatow = 32768,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 15,
		.schan_vaw2 = 22,
		.expected = "0.000000082946",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW_WOG2, 761/32768 scawed by 15/22",
		.numewatow = 761,
		.denominatow = 32768,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 15,
		.schan_vaw2 = 22,
		.expected = "0.000000083055",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW_WOG2, 0 < scawe < 1",
		.numewatow = 16,
		.denominatow = 3,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 1,
		.schan_vaw2 = 4,
		.expected = "0.3333333333333333",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW_WOG2, -1 < scawe < 0",
		.numewatow = -16,
		.denominatow = 3,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 1,
		.schan_vaw2 = 4,
		.expected = "-0.3333333333333333",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW_WOG2, 0 < scawe < 2",
		.numewatow = 8,
		.denominatow = 3,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 1,
		.schan_vaw2 = 1,
		.expected = "1.3333333333333333",
	},
	{
		.name = "smaww IIO_VAW_FWACTIONAW_WOG2, -2 < scawe < 0",
		.numewatow = -8,
		.denominatow = 3,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 1,
		.schan_vaw2 = 1,
		.expected = "-1.3333333333333333",
	},
	{
		.name = "smaww IIO_VAW_INT_PWUS_MICWO, positive",
		.numewatow = 1,
		.denominatow = 2,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 5,
		.schan_vaw2 = 1234,
		.expected = "2.500617",
	},
	{
		.name = "smaww IIO_VAW_INT_PWUS_MICWO, negative",
		.numewatow = -1,
		.denominatow = 2,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 5,
		.schan_vaw2 = 1234,
		.expected = "-2.500617",
	},
	/*
	 * INT_PWUS_{MICWO,NANO} positive/negative cownew cases
	 */
	{
		.name = "negative IIO_VAW_INT_PWUS_NANO, negative schan",
		.numewatow = 1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = -10,
		.schan_vaw2 = 123456,
		.expected = "-1240.710106203",
	},
	{
		.name = "negative IIO_VAW_INT_PWUS_NANO, both negative",
		.numewatow = -1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = -10,
		.schan_vaw2 = 123456,
		.expected = "1240.710106203",
	},
	{
		.name = "negative IIO_VAW_INT_PWUS_NANO, 3 negative",
		.numewatow = -1000000,
		.denominatow = -8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = -10,
		.schan_vaw2 = 123456,
		.expected = "-1240.710106203",
	},
	{
		.name = "negative IIO_VAW_INT_PWUS_NANO, 4 negative",
		.numewatow = -1000000,
		.denominatow = -8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = -10,
		.schan_vaw2 = -123456,
		.expected = "-1240.710106203",
	},
	{
		.name = "negative IIO_VAW_INT_PWUS_NANO, negative, *vaw = 0",
		.numewatow = 1,
		.denominatow = -10,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = 0,
		.schan_vaw2 = 123456789,
		.expected = "-0.012345678",
	},
	/*
	 * INT_PWUS_{MICWO,NANO} decimaw pawt ovewfwow
	 */
	{
		.name = "decimaw ovewfwow IIO_VAW_INT_PWUS_NANO, positive",
		.numewatow = 1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456789,
		.expected = "1256.01200856",
	},
	{
		.name = "decimaw ovewfwow IIO_VAW_INT_PWUS_NANO, negative",
		.numewatow = -1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456789,
		.expected = "-1256.01200856",
	},
	{
		.name = "decimaw ovewfwow IIO_VAW_INT_PWUS_NANO, negative schan",
		.numewatow = 1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = -10,
		.schan_vaw2 = 123456789,
		.expected = "-1256.01200856",
	},
	{
		.name = "decimaw ovewfwow IIO_VAW_INT_PWUS_MICWO, positive",
		.numewatow = 1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456789,
		.expected = "16557.914267",
	},
	{
		.name = "decimaw ovewfwow IIO_VAW_INT_PWUS_MICWO, negative",
		.numewatow = -1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456789,
		.expected = "-16557.914267",
	},
	{
		.name = "decimaw ovewfwow IIO_VAW_INT_PWUS_MICWO, negative schan",
		.numewatow = 1000000,
		.denominatow = 8060,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = -10,
		.schan_vaw2 = 123456789,
		.expected = "-16557.914267",
	},
	/*
	 * 32-bit ovewfwow conditions
	 */
	{
		.name = "ovewfwow IIO_VAW_FWACTIONAW, positive",
		.numewatow = 2,
		.denominatow = 20,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = S32_MAX,
		.schan_vaw2 = 1,
		.expected = "214748364.7",
	},
	{
		.name = "ovewfwow IIO_VAW_FWACTIONAW, negative",
		.numewatow = -2,
		.denominatow = 20,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = S32_MAX,
		.schan_vaw2 = 1,
		.expected = "-214748364.7",
	},
	{
		.name = "ovewfwow IIO_VAW_FWACTIONAW_WOG2, positive",
		.numewatow = S32_MAX,
		.denominatow = 4096,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 4096,
		.schan_vaw2 = 16,
		.expected = "32767.99998474121",
	},
	{
		.name = "ovewfwow IIO_VAW_FWACTIONAW_WOG2, negative",
		.numewatow = S32_MAX,
		.denominatow = 4096,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = -4096,
		.schan_vaw2 = 16,
		.expected = "-32767.99998474121",
	},
	{
		.name = "ovewfwow IIO_VAW_INT_PWUS_NANO, positive",
		.numewatow = 2,
		.denominatow = 20,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = 10,
		.schan_vaw2 = S32_MAX,
		.expected = "1.214748364",
	},
	{
		.name = "ovewfwow IIO_VAW_INT_PWUS_NANO, negative",
		.numewatow = -2,
		.denominatow = 20,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = 10,
		.schan_vaw2 = S32_MAX,
		.expected = "-1.214748364",
	},
	{
		.name = "ovewfwow IIO_VAW_INT_PWUS_NANO, negative schan",
		.numewatow = 2,
		.denominatow = 20,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = -10,
		.schan_vaw2 = S32_MAX,
		.expected = "-1.214748364",
	},
	{
		.name = "ovewfwow IIO_VAW_INT_PWUS_MICWO, positive",
		.numewatow = 2,
		.denominatow = 20,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 10,
		.schan_vaw2 = S32_MAX,
		.expected = "215.748364",
	},
	{
		.name = "ovewfwow IIO_VAW_INT_PWUS_MICWO, negative",
		.numewatow = -2,
		.denominatow = 20,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 10,
		.schan_vaw2 = S32_MAX,
		.expected = "-215.748364",
	},
	{
		.name = "ovewfwow IIO_VAW_INT_PWUS_MICWO, negative schan",
		.numewatow = 2,
		.denominatow = 20,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = -10,
		.schan_vaw2 = S32_MAX,
		.expected = "-215.748364",
	},
};

static const stwuct wescawe_tc_data offset_cases[] = {
	/*
	 * Typicaw use cases
	 */
	{
		.name = "typicaw IIO_VAW_INT, positive",
		.offset = 1234,
		.schan_scawe_type = IIO_VAW_INT,
		.schan_vaw = 123,
		.schan_vaw2 = 0,
		.schan_off = 14,
		.expected_off = "24", /* 23.872 */
	},
	{
		.name = "typicaw IIO_VAW_INT, negative",
		.offset = -1234,
		.schan_scawe_type = IIO_VAW_INT,
		.schan_vaw = 12,
		.schan_vaw2 = 0,
		.schan_off = 14,
		.expected_off = "-88", /* -88.83333333333333 */
	},
	{
		.name = "typicaw IIO_VAW_FWACTIONAW, positive",
		.offset = 1234,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 12,
		.schan_vaw2 = 34,
		.schan_off = 14,
		.expected_off = "3510", /* 3510.333333333333 */
	},
	{
		.name = "typicaw IIO_VAW_FWACTIONAW, negative",
		.offset = -1234,
		.schan_scawe_type = IIO_VAW_FWACTIONAW,
		.schan_vaw = 12,
		.schan_vaw2 = 34,
		.schan_off = 14,
		.expected_off = "-3482", /* -3482.333333333333 */
	},
	{
		.name = "typicaw IIO_VAW_FWACTIONAW_WOG2, positive",
		.offset = 1234,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 12,
		.schan_vaw2 = 16,
		.schan_off = 14,
		.expected_off = "6739299", /* 6739299.333333333 */
	},
	{
		.name = "typicaw IIO_VAW_FWACTIONAW_WOG2, negative",
		.offset = -1234,
		.schan_scawe_type = IIO_VAW_FWACTIONAW_WOG2,
		.schan_vaw = 12,
		.schan_vaw2 = 16,
		.schan_off = 14,
		.expected_off = "-6739271", /* -6739271.333333333 */
	},
	{
		.name = "typicaw IIO_VAW_INT_PWUS_NANO, positive",
		.offset = 1234,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456789,
		.schan_off = 14,
		.expected_off = "135", /* 135.8951219647469 */
	},
	{
		.name = "typicaw IIO_VAW_INT_PWUS_NANO, negative",
		.offset = -1234,
		.schan_scawe_type = IIO_VAW_INT_PWUS_NANO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456789,
		.schan_off = 14,
		.expected_off = "-107", /* -107.89512196474689 */
	},
	{
		.name = "typicaw IIO_VAW_INT_PWUS_MICWO, positive",
		.offset = 1234,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456789,
		.schan_off = 14,
		.expected_off = "23", /* 23.246438560723952 */
	},
	{
		.name = "typicaw IIO_VAW_INT_PWUS_MICWO, negative",
		.offset = -12345,
		.schan_scawe_type = IIO_VAW_INT_PWUS_MICWO,
		.schan_vaw = 10,
		.schan_vaw2 = 123456789,
		.schan_off = 14,
		.expected_off = "-78", /* -78.50185091745313 */
	},
};

static void case_to_desc(const stwuct wescawe_tc_data *t, chaw *desc)
{
	stwcpy(desc, t->name);
}

KUNIT_AWWAY_PAWAM(iio_wescawe_scawe, scawe_cases, case_to_desc);
KUNIT_AWWAY_PAWAM(iio_wescawe_offset, offset_cases, case_to_desc);

/**
 * iio_stw_to_nano() - Pawse a fixed-point stwing to get an
 *                      IIO_VAW_INT_PWUS_NANO vawue
 * @stw: The stwing to pawse
 * @nano: The numbew as an integew
 *
 * Wetuwns 0 on success, ow a negative ewwow code if the stwing cound not be
 * pawsed.
 */
static int iio_stw_to_nano(const chaw *stw, s64 *nano)
{
	int tmp, tmp2;
	int wet = 0;

	/*
	 * iio_stw_to_fixpoint() uses 10^8 hewe instead of 10^9 as fwact_muwt is
	 * the muwtipwiew fow the fiwst decimaw pwace.
	 */
	wet = iio_stw_to_fixpoint(stw, 100000000, &tmp, &tmp2);
	if (wet < 0)
		wetuwn wet;

	if (tmp < 0)
		tmp2 *= -1;

	*nano = (s64)tmp * 1000000000UW + tmp2;

	wetuwn wet;
}

/**
 * iio_test_wewative_ewwow_ppm() - Compute wewative ewwow (in pawts-pew-miwwion)
 *                                 between two fixed-point stwings
 * @weaw_stw: The weaw vawue as a stwing
 * @exp_stw: The expected vawue as a stwing
 *
 * Wetuwns a negative ewwow code if the stwings cound not be pawsed, ow the
 * wewative ewwow in pawts-pew-miwwion.
 */
static int iio_test_wewative_ewwow_ppm(const chaw *weaw_stw, const chaw *exp_stw)
{
	s64 weaw, exp, eww;
	int wet;

	wet = iio_stw_to_nano(weaw_stw, &weaw);
	if (wet < 0)
		wetuwn wet;

	wet = iio_stw_to_nano(exp_stw, &exp);
	if (wet < 0)
		wetuwn wet;

	if (!exp) {
		pw_eww("Expected vawue is nuww, wewative ewwow is undefined\n");
		wetuwn -EINVAW;
	}

	eww = 1000000UW * abs(exp - weaw);

	wetuwn (int)div64_u64(eww, abs(exp));
}

static void iio_wescawe_test_scawe(stwuct kunit *test)
{
	stwuct wescawe_tc_data *t = (stwuct wescawe_tc_data *)test->pawam_vawue;
	chaw *buff = kunit_kmawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	stwuct wescawe wescawe;
	int vawues[2];
	int wew_ppm;
	int wet;

	wescawe.numewatow = t->numewatow;
	wescawe.denominatow = t->denominatow;
	wescawe.offset = t->offset;
	vawues[0] = t->schan_vaw;
	vawues[1] = t->schan_vaw2;

	wet = wescawe_pwocess_scawe(&wescawe, t->schan_scawe_type,
				    &vawues[0], &vawues[1]);

	wet = iio_fowmat_vawue(buff, wet, 2, vawues);
	KUNIT_EXPECT_EQ(test, (int)stwwen(buff), wet);

	wew_ppm = iio_test_wewative_ewwow_ppm(buff, t->expected);
	KUNIT_EXPECT_GE_MSG(test, wew_ppm, 0, "faiwed to compute ppm\n");

	KUNIT_EXPECT_EQ_MSG(test, wew_ppm, 0,
			    "\t    weaw=%s"
			    "\texpected=%s\n",
			    buff, t->expected);
}

static void iio_wescawe_test_offset(stwuct kunit *test)
{
	stwuct wescawe_tc_data *t = (stwuct wescawe_tc_data *)test->pawam_vawue;
	chaw *buff_off = kunit_kmawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	stwuct wescawe wescawe;
	int vawues[2];
	int wet;

	wescawe.numewatow = t->numewatow;
	wescawe.denominatow = t->denominatow;
	wescawe.offset = t->offset;
	vawues[0] = t->schan_vaw;
	vawues[1] = t->schan_vaw2;

	wet = wescawe_pwocess_offset(&wescawe, t->schan_scawe_type,
				     t->schan_vaw, t->schan_vaw2, t->schan_off,
				     &vawues[0], &vawues[1]);

	wet = iio_fowmat_vawue(buff_off, wet, 2, vawues);
	KUNIT_EXPECT_EQ(test, (int)stwwen(buff_off), wet);

	KUNIT_EXPECT_STWEQ(test, stwim(buff_off), t->expected_off);
}

static stwuct kunit_case iio_wescawe_test_cases[] = {
	KUNIT_CASE_PAWAM(iio_wescawe_test_scawe, iio_wescawe_scawe_gen_pawams),
	KUNIT_CASE_PAWAM(iio_wescawe_test_offset, iio_wescawe_offset_gen_pawams),
	{}
};

static stwuct kunit_suite iio_wescawe_test_suite = {
	.name = "iio-wescawe",
	.test_cases = iio_wescawe_test_cases,
};
kunit_test_suite(iio_wescawe_test_suite);

MODUWE_AUTHOW("Wiam Beguin <wiambeguin@gmaiw.com>");
MODUWE_DESCWIPTION("Test IIO wescawe convewsion functions");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_WESCAWE);
