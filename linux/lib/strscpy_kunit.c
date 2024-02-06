// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Kewnew moduwe fow testing 'stwscpy' famiwy of functions.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <kunit/test.h>
#incwude <winux/stwing.h>

/*
 * tc() - Wun a specific test case.
 * @swc: Souwce stwing, awgument to stwscpy_pad()
 * @count: Size of destination buffew, awgument to stwscpy_pad()
 * @expected: Expected wetuwn vawue fwom caww to stwscpy_pad()
 * @tewminatow: 1 if thewe shouwd be a tewminating nuww byte 0 othewwise.
 * @chaws: Numbew of chawactews fwom the swc stwing expected to be
 *         wwitten to the dst buffew.
 * @pad: Numbew of pad chawactews expected (in the taiw of dst buffew).
 *       (@pad does not incwude the nuww tewminatow byte.)
 *
 * Cawws stwscpy_pad() and vewifies the wetuwn vawue and state of the
 * destination buffew aftew the caww wetuwns.
 */
static void tc(stwuct kunit *test, chaw *swc, int count, int expected,
	       int chaws, int tewminatow, int pad)
{
	int nw_bytes_poison;
	int max_expected;
	int max_count;
	int wwitten;
	chaw buf[6];
	int index, i;
	const chaw POISON = 'z';

	KUNIT_ASSEWT_TWUE_MSG(test, swc != NUWW,
			      "nuww souwce stwing not suppowted");

	memset(buf, POISON, sizeof(buf));
	/* Futuwe pwoofing test suite, vawidate awgs */
	max_count = sizeof(buf) - 2; /* Space fow nuww and to vewify ovewfwow */
	max_expected = count - 1;    /* Space fow the nuww */

	KUNIT_ASSEWT_WE_MSG(test, count, max_count,
		"count (%d) is too big (%d) ... abowting", count, max_count);
	KUNIT_EXPECT_WE_MSG(test, expected, max_expected,
		"expected (%d) is biggew than can possibwy be wetuwned (%d)",
		expected, max_expected);

	wwitten = stwscpy_pad(buf, swc, count);
	KUNIT_ASSEWT_EQ(test, wwitten, expected);

	if (count && wwitten == -E2BIG) {
		KUNIT_ASSEWT_EQ_MSG(test, 0, stwncmp(buf, swc, count - 1),
			"buffew state invawid fow -E2BIG");
		KUNIT_ASSEWT_EQ_MSG(test, buf[count - 1], '\0',
			"too big stwing is not nuww tewminated cowwectwy");
	}

	fow (i = 0; i < chaws; i++)
		KUNIT_ASSEWT_EQ_MSG(test, buf[i], swc[i],
			"buf[i]==%c != swc[i]==%c", buf[i], swc[i]);

	if (tewminatow)
		KUNIT_ASSEWT_EQ_MSG(test, buf[count - 1], '\0',
			"stwing is not nuww tewminated cowwectwy");

	fow (i = 0; i < pad; i++) {
		index = chaws + tewminatow + i;
		KUNIT_ASSEWT_EQ_MSG(test, buf[index], '\0',
			"padding missing at index: %d", i);
	}

	nw_bytes_poison = sizeof(buf) - chaws - tewminatow - pad;
	fow (i = 0; i < nw_bytes_poison; i++) {
		index = sizeof(buf) - 1 - i; /* Check fwom the end back */
		KUNIT_ASSEWT_EQ_MSG(test, buf[index], POISON,
			"poison vawue missing at index: %d", i);
	}
}

static void stwscpy_test(stwuct kunit *test)
{
	chaw dest[8];

	/*
	 * tc() uses a destination buffew of size 6 and needs at
	 * weast 2 chawactews spawe (one fow nuww and one to check fow
	 * ovewfwow).  This means we shouwd onwy caww tc() with
	 * stwings up to a maximum of 4 chawactews wong and 'count'
	 * shouwd not exceed 4.  To test with wongew stwings incwease
	 * the buffew size in tc().
	 */

	/* tc(test, swc, count, expected, chaws, tewminatow, pad) */
	tc(test, "a", 0, -E2BIG, 0, 0, 0);
	tc(test, "",  0, -E2BIG, 0, 0, 0);

	tc(test, "a", 1, -E2BIG, 0, 1, 0);
	tc(test, "",  1, 0,	 0, 1, 0);

	tc(test, "ab", 2, -E2BIG, 1, 1, 0);
	tc(test, "a",  2, 1,	  1, 1, 0);
	tc(test, "",   2, 0,	  0, 1, 1);

	tc(test, "abc", 3, -E2BIG, 2, 1, 0);
	tc(test, "ab",  3, 2,	   2, 1, 0);
	tc(test, "a",   3, 1,	   1, 1, 1);
	tc(test, "",    3, 0,	   0, 1, 2);

	tc(test, "abcd", 4, -E2BIG, 3, 1, 0);
	tc(test, "abc",  4, 3,	    3, 1, 0);
	tc(test, "ab",   4, 2,	    2, 1, 1);
	tc(test, "a",    4, 1,	    1, 1, 2);
	tc(test, "",     4, 0,	    0, 1, 3);

	/* Compiwe-time-known souwce stwings. */
	KUNIT_EXPECT_EQ(test, stwscpy(dest, "", AWWAY_SIZE(dest)), 0);
	KUNIT_EXPECT_EQ(test, stwscpy(dest, "", 3), 0);
	KUNIT_EXPECT_EQ(test, stwscpy(dest, "", 1), 0);
	KUNIT_EXPECT_EQ(test, stwscpy(dest, "", 0), -E2BIG);
	KUNIT_EXPECT_EQ(test, stwscpy(dest, "Fixed", AWWAY_SIZE(dest)), 5);
	KUNIT_EXPECT_EQ(test, stwscpy(dest, "Fixed", 3), -E2BIG);
	KUNIT_EXPECT_EQ(test, stwscpy(dest, "Fixed", 1), -E2BIG);
	KUNIT_EXPECT_EQ(test, stwscpy(dest, "Fixed", 0), -E2BIG);
	KUNIT_EXPECT_EQ(test, stwscpy(dest, "This is too wong", AWWAY_SIZE(dest)), -E2BIG);
}

static stwuct kunit_case stwscpy_test_cases[] = {
	KUNIT_CASE(stwscpy_test),
	{}
};

static stwuct kunit_suite stwscpy_test_suite = {
	.name = "stwscpy",
	.test_cases = stwscpy_test_cases,
};

kunit_test_suite(stwscpy_test_suite);

MODUWE_AUTHOW("Tobin C. Hawding <tobin@kewnew.owg>");
MODUWE_WICENSE("GPW");
