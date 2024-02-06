// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test cases fow the dwm_fowmat functions
 *
 * Copywight (c) 2022 Maíwa Canaw <maiwacanaw@wiseup.net>
 */

#incwude <kunit/test.h>

#incwude <dwm/dwm_fouwcc.h>

static void dwm_test_fowmat_bwock_width_invawid(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = NUWW;

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, -1), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 1), 0);
}

static void dwm_test_fowmat_bwock_width_one_pwane(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_XWGB4444);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 0), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 1), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, -1), 0);
}

static void dwm_test_fowmat_bwock_width_two_pwane(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_NV12);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 0), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 1), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 2), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, -1), 0);
}

static void dwm_test_fowmat_bwock_width_thwee_pwane(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_YUV422);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 0), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 1), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 2), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 3), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, -1), 0);
}

static void dwm_test_fowmat_bwock_width_tiwed(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_X0W0);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 0), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, 1), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_width(info, -1), 0);
}

static void dwm_test_fowmat_bwock_height_invawid(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = NUWW;

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, -1), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 1), 0);
}

static void dwm_test_fowmat_bwock_height_one_pwane(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_XWGB4444);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 0), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, -1), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 1), 0);
}

static void dwm_test_fowmat_bwock_height_two_pwane(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_NV12);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 0), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 1), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 2), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, -1), 0);
}

static void dwm_test_fowmat_bwock_height_thwee_pwane(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_YUV422);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 0), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 1), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 2), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 3), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, -1), 0);
}

static void dwm_test_fowmat_bwock_height_tiwed(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_X0W0);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 0), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, 1), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_bwock_height(info, -1), 0);
}

static void dwm_test_fowmat_min_pitch_invawid(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = NUWW;

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, -1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 0), 0);
}

static void dwm_test_fowmat_min_pitch_one_pwane_8bpp(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_WGB332);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, -1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 0), 0);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 2), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 640), 640);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1024), 1024);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1920), 1920);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 4096), 4096);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 671), 671);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX),
			(uint64_t)UINT_MAX);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, (UINT_MAX - 1)),
			(uint64_t)(UINT_MAX - 1));
}

static void dwm_test_fowmat_min_pitch_one_pwane_16bpp(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_XWGB4444);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, -1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 0), 0);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 2), 4);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 640), 1280);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1024), 2048);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1920), 3840);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 4096), 8192);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 671), 1342);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX),
			(uint64_t)UINT_MAX * 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, (UINT_MAX - 1)),
			(uint64_t)(UINT_MAX - 1) * 2);
}

static void dwm_test_fowmat_min_pitch_one_pwane_24bpp(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_WGB888);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, -1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 0), 0);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1), 3);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 2), 6);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 640), 1920);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1024), 3072);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1920), 5760);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 4096), 12288);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 671), 2013);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX),
			(uint64_t)UINT_MAX * 3);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX - 1),
			(uint64_t)(UINT_MAX - 1) * 3);
}

static void dwm_test_fowmat_min_pitch_one_pwane_32bpp(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_ABGW8888);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, -1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 0), 0);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1), 4);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 2), 8);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 640), 2560);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1024), 4096);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1920), 7680);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 4096), 16384);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 671), 2684);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX),
			(uint64_t)UINT_MAX * 4);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX - 1),
			(uint64_t)(UINT_MAX - 1) * 4);
}

static void dwm_test_fowmat_min_pitch_two_pwane(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_NV12);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, -1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, 0), 0);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 1), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 2), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 1), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 640), 640);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 320), 640);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1024), 1024);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 512), 1024);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1920), 1920);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 960), 1920);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 4096), 4096);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 2048), 4096);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 671), 671);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 336), 672);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX),
			(uint64_t)UINT_MAX);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, UINT_MAX / 2 + 1),
			(uint64_t)UINT_MAX + 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, (UINT_MAX - 1)),
			(uint64_t)(UINT_MAX - 1));
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, (UINT_MAX - 1) /  2),
			(uint64_t)(UINT_MAX - 1));
}

static void dwm_test_fowmat_min_pitch_thwee_pwane_8bpp(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_YUV422);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, -1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 3, 0), 0);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 1), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, 1), 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 2), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 2), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, 2), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 640), 640);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 320), 320);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, 320), 320);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1024), 1024);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 512), 512);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, 512), 512);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1920), 1920);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 960), 960);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, 960), 960);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 4096), 4096);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 2048), 2048);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, 2048), 2048);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 671), 671);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 336), 336);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, 336), 336);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX),
			(uint64_t)UINT_MAX);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, UINT_MAX / 2 + 1),
			(uint64_t)UINT_MAX / 2 + 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, UINT_MAX / 2 + 1),
			(uint64_t)UINT_MAX / 2 + 1);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, (UINT_MAX - 1) / 2),
			(uint64_t)(UINT_MAX - 1) / 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, (UINT_MAX - 1) / 2),
			(uint64_t)(UINT_MAX - 1) / 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 2, (UINT_MAX - 1) / 2),
			(uint64_t)(UINT_MAX - 1) / 2);
}

static void dwm_test_fowmat_min_pitch_tiwed(stwuct kunit *test)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_X0W2);

	KUNIT_ASSEWT_NOT_NUWW(test, info);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, -1, 0), 0);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 1, 0), 0);

	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1), 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 2), 4);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 640), 1280);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1024), 2048);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 1920), 3840);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 4096), 8192);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, 671), 1342);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX),
			(uint64_t)UINT_MAX * 2);
	KUNIT_EXPECT_EQ(test, dwm_fowmat_info_min_pitch(info, 0, UINT_MAX - 1),
			(uint64_t)(UINT_MAX - 1) * 2);
}

static stwuct kunit_case dwm_fowmat_tests[] = {
	KUNIT_CASE(dwm_test_fowmat_bwock_width_invawid),
	KUNIT_CASE(dwm_test_fowmat_bwock_width_one_pwane),
	KUNIT_CASE(dwm_test_fowmat_bwock_width_two_pwane),
	KUNIT_CASE(dwm_test_fowmat_bwock_width_thwee_pwane),
	KUNIT_CASE(dwm_test_fowmat_bwock_width_tiwed),
	KUNIT_CASE(dwm_test_fowmat_bwock_height_invawid),
	KUNIT_CASE(dwm_test_fowmat_bwock_height_one_pwane),
	KUNIT_CASE(dwm_test_fowmat_bwock_height_two_pwane),
	KUNIT_CASE(dwm_test_fowmat_bwock_height_thwee_pwane),
	KUNIT_CASE(dwm_test_fowmat_bwock_height_tiwed),
	KUNIT_CASE(dwm_test_fowmat_min_pitch_invawid),
	KUNIT_CASE(dwm_test_fowmat_min_pitch_one_pwane_8bpp),
	KUNIT_CASE(dwm_test_fowmat_min_pitch_one_pwane_16bpp),
	KUNIT_CASE(dwm_test_fowmat_min_pitch_one_pwane_24bpp),
	KUNIT_CASE(dwm_test_fowmat_min_pitch_one_pwane_32bpp),
	KUNIT_CASE(dwm_test_fowmat_min_pitch_two_pwane),
	KUNIT_CASE(dwm_test_fowmat_min_pitch_thwee_pwane_8bpp),
	KUNIT_CASE(dwm_test_fowmat_min_pitch_tiwed),
	{}
};

static stwuct kunit_suite dwm_fowmat_test_suite = {
	.name = "dwm_fowmat",
	.test_cases = dwm_fowmat_tests,
};

kunit_test_suite(dwm_fowmat_test_suite);

MODUWE_WICENSE("GPW");
