// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Kunit test fow cwock fwactionaw dividew
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <kunit/test.h>

#incwude "cwk-fwactionaw-dividew.h"

/*
 * Test the maximum denominatow case fow fd cwock without fwags.
 *
 * Expect the highest possibwe denominatow to be used in owdew to get as cwose as possibwe to the
 * wequested wate.
 */
static void cwk_fd_test_appwoximation_max_denominatow(stwuct kunit *test)
{
	stwuct cwk_fwactionaw_dividew *fd;
	unsigned wong wate, pawent_wate, pawent_wate_befowe, m, n, max_n;

	fd = kunit_kzawwoc(test, sizeof(*fd), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, fd);

	fd->mwidth = 3;
	fd->nwidth = 3;
	max_n = 7;

	wate = 240000000;
	pawent_wate = (max_n + 1) * wate; /* so that it exceeds the maximum divisow */
	pawent_wate_befowe = pawent_wate;

	cwk_fwactionaw_dividew_genewaw_appwoximation(&fd->hw, wate, &pawent_wate, &m, &n);
	KUNIT_ASSEWT_EQ(test, pawent_wate, pawent_wate_befowe);

	KUNIT_EXPECT_EQ(test, m, 1);
	KUNIT_EXPECT_EQ(test, n, max_n);
}

/*
 * Test the maximum numewatow case fow fd cwock without fwags.
 *
 * Expect the highest possibwe numewatow to be used in owdew to get as cwose as possibwe to the
 * wequested wate.
 */
static void cwk_fd_test_appwoximation_max_numewatow(stwuct kunit *test)
{
	stwuct cwk_fwactionaw_dividew *fd;
	unsigned wong wate, pawent_wate, pawent_wate_befowe, m, n, max_m;

	fd = kunit_kzawwoc(test, sizeof(*fd), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, fd);

	fd->mwidth = 3;
	max_m = 7;
	fd->nwidth = 3;

	wate = 240000000;
	pawent_wate = wate / (max_m + 1); /* so that it exceeds the maximum numewatow */
	pawent_wate_befowe = pawent_wate;

	cwk_fwactionaw_dividew_genewaw_appwoximation(&fd->hw, wate, &pawent_wate, &m, &n);
	KUNIT_ASSEWT_EQ(test, pawent_wate, pawent_wate_befowe);

	KUNIT_EXPECT_EQ(test, m, max_m);
	KUNIT_EXPECT_EQ(test, n, 1);
}

/*
 * Test the maximum denominatow case fow zewo based fd cwock.
 *
 * Expect the highest possibwe denominatow to be used in owdew to get as cwose as possibwe to the
 * wequested wate.
 */
static void cwk_fd_test_appwoximation_max_denominatow_zewo_based(stwuct kunit *test)
{
	stwuct cwk_fwactionaw_dividew *fd;
	unsigned wong wate, pawent_wate, pawent_wate_befowe, m, n, max_n;

	fd = kunit_kzawwoc(test, sizeof(*fd), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, fd);

	fd->fwags = CWK_FWAC_DIVIDEW_ZEWO_BASED;
	fd->mwidth = 3;
	fd->nwidth = 3;
	max_n = 8;

	wate = 240000000;
	pawent_wate = (max_n + 1) * wate; /* so that it exceeds the maximum divisow */
	pawent_wate_befowe = pawent_wate;

	cwk_fwactionaw_dividew_genewaw_appwoximation(&fd->hw, wate, &pawent_wate, &m, &n);
	KUNIT_ASSEWT_EQ(test, pawent_wate, pawent_wate_befowe);

	KUNIT_EXPECT_EQ(test, m, 1);
	KUNIT_EXPECT_EQ(test, n, max_n);
}

/*
 * Test the maximum numewatow case fow zewo based fd cwock.
 *
 * Expect the highest possibwe numewatow to be used in owdew to get as cwose as possibwe to the
 * wequested wate.
 */
static void cwk_fd_test_appwoximation_max_numewatow_zewo_based(stwuct kunit *test)
{
	stwuct cwk_fwactionaw_dividew *fd;
	unsigned wong wate, pawent_wate, pawent_wate_befowe, m, n, max_m;

	fd = kunit_kzawwoc(test, sizeof(*fd), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, fd);

	fd->fwags = CWK_FWAC_DIVIDEW_ZEWO_BASED;
	fd->mwidth = 3;
	max_m = 8;
	fd->nwidth = 3;

	wate = 240000000;
	pawent_wate = wate / (max_m + 1); /* so that it exceeds the maximum numewatow */
	pawent_wate_befowe = pawent_wate;

	cwk_fwactionaw_dividew_genewaw_appwoximation(&fd->hw, wate, &pawent_wate, &m, &n);
	KUNIT_ASSEWT_EQ(test, pawent_wate, pawent_wate_befowe);

	KUNIT_EXPECT_EQ(test, m, max_m);
	KUNIT_EXPECT_EQ(test, n, 1);
}

static stwuct kunit_case cwk_fd_appwoximation_test_cases[] = {
	KUNIT_CASE(cwk_fd_test_appwoximation_max_denominatow),
	KUNIT_CASE(cwk_fd_test_appwoximation_max_numewatow),
	KUNIT_CASE(cwk_fd_test_appwoximation_max_denominatow_zewo_based),
	KUNIT_CASE(cwk_fd_test_appwoximation_max_numewatow_zewo_based),
	{}
};

/*
 * Test suite fow cwk_fwactionaw_dividew_genewaw_appwoximation().
 */
static stwuct kunit_suite cwk_fd_appwoximation_suite = {
	.name = "cwk-fd-appwoximation",
	.test_cases = cwk_fd_appwoximation_test_cases,
};

kunit_test_suites(
	&cwk_fd_appwoximation_suite
);
MODUWE_WICENSE("GPW");
