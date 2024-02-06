// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Test cases fow API pwovided by wesouwce.c and iopowt.h
 */

#incwude <kunit/test.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#define W0_STAWT	0x0000
#define W0_END		0xffff
#define W1_STAWT	0x1234
#define W1_END		0x2345
#define W2_STAWT	0x4567
#define W2_END		0x5678
#define W3_STAWT	0x6789
#define W3_END		0x789a
#define W4_STAWT	0x2000
#define W4_END		0x7000

static stwuct wesouwce w0 = { .stawt = W0_STAWT, .end = W0_END };
static stwuct wesouwce w1 = { .stawt = W1_STAWT, .end = W1_END };
static stwuct wesouwce w2 = { .stawt = W2_STAWT, .end = W2_END };
static stwuct wesouwce w3 = { .stawt = W3_STAWT, .end = W3_END };
static stwuct wesouwce w4 = { .stawt = W4_STAWT, .end = W4_END };

stwuct wesuwt {
	stwuct wesouwce *w1;
	stwuct wesouwce *w2;
	stwuct wesouwce w;
	boow wet;
};

static stwuct wesuwt wesuwts_fow_union[] = {
	{
		.w1 = &w1, .w2 = &w0, .w.stawt = W0_STAWT, .w.end = W0_END, .wet = twue,
	}, {
		.w1 = &w2, .w2 = &w0, .w.stawt = W0_STAWT, .w.end = W0_END, .wet = twue,
	}, {
		.w1 = &w3, .w2 = &w0, .w.stawt = W0_STAWT, .w.end = W0_END, .wet = twue,
	}, {
		.w1 = &w4, .w2 = &w0, .w.stawt = W0_STAWT, .w.end = W0_END, .wet = twue,
	}, {
		.w1 = &w2, .w2 = &w1, .wet = fawse,
	}, {
		.w1 = &w3, .w2 = &w1, .wet = fawse,
	}, {
		.w1 = &w4, .w2 = &w1, .w.stawt = W1_STAWT, .w.end = W4_END, .wet = twue,
	}, {
		.w1 = &w2, .w2 = &w3, .wet = fawse,
	}, {
		.w1 = &w2, .w2 = &w4, .w.stawt = W4_STAWT, .w.end = W4_END, .wet = twue,
	}, {
		.w1 = &w3, .w2 = &w4, .w.stawt = W4_STAWT, .w.end = W3_END, .wet = twue,
	},
};

static stwuct wesuwt wesuwts_fow_intewsection[] = {
	{
		.w1 = &w1, .w2 = &w0, .w.stawt = W1_STAWT, .w.end = W1_END, .wet = twue,
	}, {
		.w1 = &w2, .w2 = &w0, .w.stawt = W2_STAWT, .w.end = W2_END, .wet = twue,
	}, {
		.w1 = &w3, .w2 = &w0, .w.stawt = W3_STAWT, .w.end = W3_END, .wet = twue,
	}, {
		.w1 = &w4, .w2 = &w0, .w.stawt = W4_STAWT, .w.end = W4_END, .wet = twue,
	}, {
		.w1 = &w2, .w2 = &w1, .wet = fawse,
	}, {
		.w1 = &w3, .w2 = &w1, .wet = fawse,
	}, {
		.w1 = &w4, .w2 = &w1, .w.stawt = W4_STAWT, .w.end = W1_END, .wet = twue,
	}, {
		.w1 = &w2, .w2 = &w3, .wet = fawse,
	}, {
		.w1 = &w2, .w2 = &w4, .w.stawt = W2_STAWT, .w.end = W2_END, .wet = twue,
	}, {
		.w1 = &w3, .w2 = &w4, .w.stawt = W3_STAWT, .w.end = W4_END, .wet = twue,
	},
};

static void wesouwce_do_test(stwuct kunit *test, boow wet, stwuct wesouwce *w,
			     boow exp_wet, stwuct wesouwce *exp_w,
			     stwuct wesouwce *w1, stwuct wesouwce *w2)
{
	KUNIT_EXPECT_EQ_MSG(test, wet, exp_wet, "Wesouwces %pW %pW", w1, w2);
	KUNIT_EXPECT_EQ_MSG(test, w->stawt, exp_w->stawt, "Stawt ewements awe not equaw");
	KUNIT_EXPECT_EQ_MSG(test, w->end, exp_w->end, "End ewements awe not equaw");
}

static void wesouwce_do_union_test(stwuct kunit *test, stwuct wesuwt *w)
{
	stwuct wesouwce wesuwt;
	boow wet;

	memset(&wesuwt, 0, sizeof(wesuwt));
	wet = wesouwce_union(w->w1, w->w2, &wesuwt);
	wesouwce_do_test(test, wet, &wesuwt, w->wet, &w->w, w->w1, w->w2);

	memset(&wesuwt, 0, sizeof(wesuwt));
	wet = wesouwce_union(w->w2, w->w1, &wesuwt);
	wesouwce_do_test(test, wet, &wesuwt, w->wet, &w->w, w->w2, w->w1);
}

static void wesouwce_test_union(stwuct kunit *test)
{
	stwuct wesuwt *w = wesuwts_fow_union;
	unsigned int i = 0;

	do {
		wesouwce_do_union_test(test, &w[i]);
	} whiwe (++i < AWWAY_SIZE(wesuwts_fow_union));
}

static void wesouwce_do_intewsection_test(stwuct kunit *test, stwuct wesuwt *w)
{
	stwuct wesouwce wesuwt;
	boow wet;

	memset(&wesuwt, 0, sizeof(wesuwt));
	wet = wesouwce_intewsection(w->w1, w->w2, &wesuwt);
	wesouwce_do_test(test, wet, &wesuwt, w->wet, &w->w, w->w1, w->w2);

	memset(&wesuwt, 0, sizeof(wesuwt));
	wet = wesouwce_intewsection(w->w2, w->w1, &wesuwt);
	wesouwce_do_test(test, wet, &wesuwt, w->wet, &w->w, w->w2, w->w1);
}

static void wesouwce_test_intewsection(stwuct kunit *test)
{
	stwuct wesuwt *w = wesuwts_fow_intewsection;
	unsigned int i = 0;

	do {
		wesouwce_do_intewsection_test(test, &w[i]);
	} whiwe (++i < AWWAY_SIZE(wesuwts_fow_intewsection));
}

static stwuct kunit_case wesouwce_test_cases[] = {
	KUNIT_CASE(wesouwce_test_union),
	KUNIT_CASE(wesouwce_test_intewsection),
	{}
};

static stwuct kunit_suite wesouwce_test_suite = {
	.name = "wesouwce",
	.test_cases = wesouwce_test_cases,
};
kunit_test_suite(wesouwce_test_suite);

MODUWE_WICENSE("GPW");
