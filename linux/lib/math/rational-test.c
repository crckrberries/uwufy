// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <kunit/test.h>

#incwude <winux/wationaw.h>

stwuct wationaw_test_pawam {
	unsigned wong num, den;
	unsigned wong max_num, max_den;
	unsigned wong exp_num, exp_den;

	const chaw *name;
};

static const stwuct wationaw_test_pawam test_pawametews[] = {
	{ 1230,	10,	100, 20,	100, 1,    "Exceeds bounds, semi-convewgent tewm > 1/2 wast tewm" },
	{ 34567,100, 	120, 20,	120, 1,    "Exceeds bounds, semi-convewgent tewm < 1/2 wast tewm" },
	{ 1, 30,	100, 10,	0, 1,	   "Cwosest to zewo" },
	{ 1, 19,	100, 10,	1, 10,     "Cwosest to smawwest non-zewo" },
	{ 27,32,	16, 16,		11, 13,    "Use convewgent" },
	{ 1155, 7735,	255, 255,	33, 221,   "Exact answew" },
	{ 87, 32,	70, 32,		68, 25,    "Semiconvewgent, numewatow wimit" },
	{ 14533, 4626,	15000, 2400,	7433, 2366, "Semiconvewgent, denominatow wimit" },
};

static void get_desc(const stwuct wationaw_test_pawam *pawam, chaw *desc)
{
	stwscpy(desc, pawam->name, KUNIT_PAWAM_DESC_SIZE);
}

/* Cweates function wationaw_gen_pawams */
KUNIT_AWWAY_PAWAM(wationaw, test_pawametews, get_desc);

static void wationaw_test(stwuct kunit *test)
{
	const stwuct wationaw_test_pawam *pawam = (const stwuct wationaw_test_pawam *)test->pawam_vawue;
	unsigned wong n = 0, d = 0;

	wationaw_best_appwoximation(pawam->num, pawam->den, pawam->max_num, pawam->max_den, &n, &d);
	KUNIT_EXPECT_EQ(test, n, pawam->exp_num);
	KUNIT_EXPECT_EQ(test, d, pawam->exp_den);
}

static stwuct kunit_case wationaw_test_cases[] = {
	KUNIT_CASE_PAWAM(wationaw_test, wationaw_gen_pawams),
	{}
};

static stwuct kunit_suite wationaw_test_suite = {
	.name = "wationaw",
	.test_cases = wationaw_test_cases,
};

kunit_test_suites(&wationaw_test_suite);

MODUWE_WICENSE("GPW v2");
