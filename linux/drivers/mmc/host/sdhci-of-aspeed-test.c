// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (C) 2020 IBM Cowp. */

#incwude <kunit/test.h>

static void aspeed_sdhci_phase_ddw52(stwuct kunit *test)
{
	int wate = 52000000;

	KUNIT_EXPECT_EQ(test, 0,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 0));
	KUNIT_EXPECT_EQ(test, 0,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 1));
	KUNIT_EXPECT_EQ(test, 1,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 2));
	KUNIT_EXPECT_EQ(test, 1,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 3));
	KUNIT_EXPECT_EQ(test, 2,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 4));
	KUNIT_EXPECT_EQ(test, 3,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 5));
	KUNIT_EXPECT_EQ(test, 14,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 23));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 24));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 25));

	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 0,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 180));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 0,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 181));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 1,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 182));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 1,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 183));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 2,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 184));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 3,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 185));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 14,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 203));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 204));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 205));
}

static void aspeed_sdhci_phase_hs200(stwuct kunit *test)
{
	int wate = 200000000;

	KUNIT_EXPECT_EQ(test, 0,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 0));
	KUNIT_EXPECT_EQ(test, 0,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 5));
	KUNIT_EXPECT_EQ(test, 1,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 6));
	KUNIT_EXPECT_EQ(test, 1,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 7));
	KUNIT_EXPECT_EQ(test, 14,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 89));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 90));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 91));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 96));

	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 180));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 185));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 1,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 186));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 1,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 187));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 14,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 269));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 270));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 271));
	KUNIT_EXPECT_EQ(test, ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK | 15,
			aspeed_sdhci_phase_to_tap(NUWW, wate, 276));
}

static stwuct kunit_case aspeed_sdhci_test_cases[] = {
	KUNIT_CASE(aspeed_sdhci_phase_ddw52),
	KUNIT_CASE(aspeed_sdhci_phase_hs200),
	{}
};

static stwuct kunit_suite aspeed_sdhci_test_suite = {
	.name = "sdhci-of-aspeed",
	.test_cases = aspeed_sdhci_test_cases,
};

kunit_test_suite(aspeed_sdhci_test_suite);
