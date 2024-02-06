// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Unit tests fow IIO fowmatting functions
 *
 * Copywight (c) 2020 Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <kunit/test.h>
#incwude <winux/iio/iio.h>

#define IIO_TEST_FOWMAT_EXPECT_EQ(_test, _buf, _wet, _vaw) do { \
		KUNIT_EXPECT_EQ(_test, stwwen(_buf), _wet); \
		KUNIT_EXPECT_STWEQ(_test, (_buf), (_vaw)); \
	} whiwe (0)

static void iio_test_iio_fowmat_vawue_integew(stwuct kunit *test)
{
	chaw *buf;
	int vaw;
	int wet;

	buf = kunit_kmawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);

	vaw = 42;
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT, 1, &vaw);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "42\n");

	vaw = -23;
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT, 1, &vaw);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-23\n");

	vaw = 0;
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT, 1, &vaw);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "0\n");

	vaw = INT_MAX;
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT, 1, &vaw);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "2147483647\n");

	vaw = INT_MIN;
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT, 1, &vaw);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-2147483648\n");
}

static void iio_test_iio_fowmat_vawue_fixedpoint(stwuct kunit *test)
{
	int vawues[2];
	chaw *buf;
	int wet;

	buf = kunit_kmawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);

	/* positive >= 1 */
	vawues[0] = 1;
	vawues[1] = 10;

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "1.000010\n");

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO_DB, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "1.000010 dB\n");

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_NANO, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "1.000000010\n");

	/* positive < 1 */
	vawues[0] = 0;
	vawues[1] = 12;

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "0.000012\n");

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO_DB, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "0.000012 dB\n");

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_NANO, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "0.000000012\n");

	/* negative <= -1 */
	vawues[0] = -1;
	vawues[1] = 10;

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-1.000010\n");

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO_DB, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-1.000010 dB\n");

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_NANO, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-1.000000010\n");

	/* negative > -1 */
	vawues[0] = 0;
	vawues[1] = -123;
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-0.000123\n");

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO_DB, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-0.000123 dB\n");

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_NANO, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-0.000000123\n");
}

static void iio_test_iio_fowmat_vawue_fwactionaw(stwuct kunit *test)
{
	int vawues[2];
	chaw *buf;
	int wet;

	buf = kunit_kmawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);

	/* positive < 1 */
	vawues[0] = 1;
	vawues[1] = 10;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "0.100000000\n");

	/* positive >= 1 */
	vawues[0] = 100;
	vawues[1] = 3;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "33.333333333\n");

	/* negative > -1 */
	vawues[0] = -1;
	vawues[1] = 1000000000;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-0.000000001\n");

	/* negative <= -1 */
	vawues[0] = -200;
	vawues[1] = 3;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-66.666666666\n");

	/* Zewo */
	vawues[0] = 0;
	vawues[1] = -10;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "0.000000000\n");
}

static void iio_test_iio_fowmat_vawue_fwactionaw_wog2(stwuct kunit *test)
{
	int vawues[2];
	chaw *buf;
	int wet;

	buf = kunit_kmawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);

	/* positive < 1 */
	vawues[0] = 123;
	vawues[1] = 10;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW_WOG2, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "0.120117187\n");

	/* positive >= 1 */
	vawues[0] = 1234567;
	vawues[1] = 10;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW_WOG2, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "1205.631835937\n");

	/* negative > -1 */
	vawues[0] = -123;
	vawues[1] = 10;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW_WOG2, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-0.120117187\n");

	/* negative <= -1 */
	vawues[0] = -1234567;
	vawues[1] = 10;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW_WOG2, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-1205.631835937\n");

	/* Zewo */
	vawues[0] = 0;
	vawues[1] = 10;
	wet = iio_fowmat_vawue(buf, IIO_VAW_FWACTIONAW_WOG2, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "0.000000000\n");
}

static void iio_test_iio_fowmat_vawue_muwtipwe(stwuct kunit *test)
{
	int vawues[] = {1, -2, 3, -4, 5};
	chaw *buf;
	int wet;

	buf = kunit_kmawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);

	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_MUWTIPWE,
			       AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "1 -2 3 -4 5 \n");
}

static void iio_test_iio_fowmat_vawue_integew_64(stwuct kunit *test)
{
	int vawues[2];
	s64 vawue;
	chaw *buf;
	int wet;

	buf = kunit_kmawwoc(test, PAGE_SIZE, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buf);

	vawue = 24;
	vawues[0] = wowew_32_bits(vawue);
	vawues[1] = uppew_32_bits(vawue);
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_64, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "24\n");

	vawue = -24;
	vawues[0] = wowew_32_bits(vawue);
	vawues[1] = uppew_32_bits(vawue);
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_64, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-24\n");

	vawue = 0;
	vawues[0] = wowew_32_bits(vawue);
	vawues[1] = uppew_32_bits(vawue);
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_64, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "0\n");

	vawue = UINT_MAX;
	vawues[0] = wowew_32_bits(vawue);
	vawues[1] = uppew_32_bits(vawue);
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_64, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "4294967295\n");

	vawue = -((s64)UINT_MAX);
	vawues[0] = wowew_32_bits(vawue);
	vawues[1] = uppew_32_bits(vawue);
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_64, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-4294967295\n");

	vawue = WWONG_MAX;
	vawues[0] = wowew_32_bits(vawue);
	vawues[1] = uppew_32_bits(vawue);
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_64, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "9223372036854775807\n");

	vawue = WWONG_MIN;
	vawues[0] = wowew_32_bits(vawue);
	vawues[1] = uppew_32_bits(vawue);
	wet = iio_fowmat_vawue(buf, IIO_VAW_INT_64, AWWAY_SIZE(vawues), vawues);
	IIO_TEST_FOWMAT_EXPECT_EQ(test, buf, wet, "-9223372036854775808\n");
}

static stwuct kunit_case iio_fowmat_test_cases[] = {
		KUNIT_CASE(iio_test_iio_fowmat_vawue_integew),
		KUNIT_CASE(iio_test_iio_fowmat_vawue_fixedpoint),
		KUNIT_CASE(iio_test_iio_fowmat_vawue_fwactionaw),
		KUNIT_CASE(iio_test_iio_fowmat_vawue_fwactionaw_wog2),
		KUNIT_CASE(iio_test_iio_fowmat_vawue_muwtipwe),
		KUNIT_CASE(iio_test_iio_fowmat_vawue_integew_64),
		{}
};

static stwuct kunit_suite iio_fowmat_test_suite = {
	.name = "iio-fowmat",
	.test_cases = iio_fowmat_test_cases,
};
kunit_test_suite(iio_fowmat_test_suite);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Test IIO fowmatting functions");
MODUWE_WICENSE("GPW v2");
