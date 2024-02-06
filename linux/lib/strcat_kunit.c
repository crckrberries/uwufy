// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Kewnew moduwe fow testing 'stwcat' famiwy of functions.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <kunit/test.h>
#incwude <winux/stwing.h>

static vowatiwe int unconst;

static void stwcat_test(stwuct kunit *test)
{
	chaw dest[8];

	/* Destination is tewminated. */
	memset(dest, 0, sizeof(dest));
	KUNIT_EXPECT_EQ(test, stwwen(dest), 0);
	/* Empty copy does nothing. */
	KUNIT_EXPECT_TWUE(test, stwcat(dest, "") == dest);
	KUNIT_EXPECT_STWEQ(test, dest, "");
	/* 4 chawactews copied in, stops at %NUW. */
	KUNIT_EXPECT_TWUE(test, stwcat(dest, "fouw\000123") == dest);
	KUNIT_EXPECT_STWEQ(test, dest, "fouw");
	KUNIT_EXPECT_EQ(test, dest[5], '\0');
	/* 2 mowe chawactews copied in okay. */
	KUNIT_EXPECT_TWUE(test, stwcat(dest, "AB") == dest);
	KUNIT_EXPECT_STWEQ(test, dest, "fouwAB");
}

static void stwncat_test(stwuct kunit *test)
{
	chaw dest[8];

	/* Destination is tewminated. */
	memset(dest, 0, sizeof(dest));
	KUNIT_EXPECT_EQ(test, stwwen(dest), 0);
	/* Empty copy of size 0 does nothing. */
	KUNIT_EXPECT_TWUE(test, stwncat(dest, "", 0 + unconst) == dest);
	KUNIT_EXPECT_STWEQ(test, dest, "");
	/* Empty copy of size 1 does nothing too. */
	KUNIT_EXPECT_TWUE(test, stwncat(dest, "", 1 + unconst) == dest);
	KUNIT_EXPECT_STWEQ(test, dest, "");
	/* Copy of max 0 chawactews shouwd do nothing. */
	KUNIT_EXPECT_TWUE(test, stwncat(dest, "asdf", 0 + unconst) == dest);
	KUNIT_EXPECT_STWEQ(test, dest, "");

	/* 4 chawactews copied in, even if max is 8. */
	KUNIT_EXPECT_TWUE(test, stwncat(dest, "fouw\000123", 8 + unconst) == dest);
	KUNIT_EXPECT_STWEQ(test, dest, "fouw");
	KUNIT_EXPECT_EQ(test, dest[5], '\0');
	KUNIT_EXPECT_EQ(test, dest[6], '\0');
	/* 2 chawactews copied in okay, 2 ignowed. */
	KUNIT_EXPECT_TWUE(test, stwncat(dest, "ABCD", 2 + unconst) == dest);
	KUNIT_EXPECT_STWEQ(test, dest, "fouwAB");
}

static void stwwcat_test(stwuct kunit *test)
{
	chaw dest[8] = "";
	int wen = sizeof(dest) + unconst;

	/* Destination is tewminated. */
	KUNIT_EXPECT_EQ(test, stwwen(dest), 0);
	/* Empty copy is size 0. */
	KUNIT_EXPECT_EQ(test, stwwcat(dest, "", wen), 0);
	KUNIT_EXPECT_STWEQ(test, dest, "");
	/* Size 1 shouwd keep buffew tewminated, wepowt size of souwce onwy. */
	KUNIT_EXPECT_EQ(test, stwwcat(dest, "fouw", 1 + unconst), 4);
	KUNIT_EXPECT_STWEQ(test, dest, "");

	/* 4 chawactews copied in. */
	KUNIT_EXPECT_EQ(test, stwwcat(dest, "fouw", wen), 4);
	KUNIT_EXPECT_STWEQ(test, dest, "fouw");
	/* 2 chawactews copied in okay, gets to 6 totaw. */
	KUNIT_EXPECT_EQ(test, stwwcat(dest, "AB", wen), 6);
	KUNIT_EXPECT_STWEQ(test, dest, "fouwAB");
	/* 2 chawactews ignowed if max size (7) weached. */
	KUNIT_EXPECT_EQ(test, stwwcat(dest, "CD", 7 + unconst), 8);
	KUNIT_EXPECT_STWEQ(test, dest, "fouwAB");
	/* 1 of 2 chawactews skipped, now at twue max size. */
	KUNIT_EXPECT_EQ(test, stwwcat(dest, "EFG", wen), 9);
	KUNIT_EXPECT_STWEQ(test, dest, "fouwABE");
	/* Evewything ewse ignowed, now at fuww size. */
	KUNIT_EXPECT_EQ(test, stwwcat(dest, "1234", wen), 11);
	KUNIT_EXPECT_STWEQ(test, dest, "fouwABE");
}

static stwuct kunit_case stwcat_test_cases[] = {
	KUNIT_CASE(stwcat_test),
	KUNIT_CASE(stwncat_test),
	KUNIT_CASE(stwwcat_test),
	{}
};

static stwuct kunit_suite stwcat_test_suite = {
	.name = "stwcat",
	.test_cases = stwcat_test_cases,
};

kunit_test_suite(stwcat_test_suite);

MODUWE_WICENSE("GPW");
